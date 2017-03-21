#include "scm_localhashdef.h"
#include <scm_encaps.h>
//#include <scm_oamint_error_code.h>

int     Tmp_Tmr[200];
int     Tmp_id;
int     cap_req_api;
U8  *Cap_Hdr, *Cap_Data;


 
scmSksGenConfig                       *ssksGenConfig; 
sMapTraceConfigTableApi              *MapTraceConfigTableApi; 
/*mapInitConfig                         *smapInitConfig;*/
sSccpBehaviorConfigTableApi           *sccpBehaviorConfig;
OamScmSs7StackConfig                  *initconfig;
OamScmAlarmModify                     *scmAlarmModify;
OamScmMtp3TimerConfig                 *scmMtp3TimerConfig;
OamScmSccpTimerConfig                 *scmSccpTimerConfig;
OamScmBssapTimerConfig                *scmBssapTimerConfig; 
OamScmTrunkCicConfig                  *scmTrunkCicConfig; 
OamScmInterfaceConfig                 *scmInterfaceConfig;   
OamScmSs7RouteTestOnConfig            *scmSs7RouteTestOnConfig;  
OamScmLinkSetConfig                   *scmLinkSetConfig; 
OamScmLinkSetAdminState               *scmLinkSetAdminState;
OamScmLinkConfig                      *scmLinkConfig; 
OamScmLinkAdminState                  *scmLinkAdminState;
OamScmSs7RouteConfig                  *scmSs7RouteConfig;
OamScmSs7RouteAdminState              *scmSs7RouteAdminState;
/*OamScmMapSecurityConfig               *scmMapSecurityConfig;  */
OamScmLapdTEIConfig         *sLapdTEIConfigTableApi;
OamScmLapdSAPIConfig        *sLapdSAPIConfigTableApi;
OamScmLapdTimerConfig       *sLapdTimerTableApi;
OamScmLapdTSConfig          *sLapdTSConfigTableApi;
OamScmLapdPegGet            *sLapdPegGetTableApi;    


OamScmMtp3GenPegGet                   *scmMtp3GenPegGet;
OamScmMtp2PegGet                      *scmMtp2PegGet;
OamScmMtp3LinkPegGet                  *scmMtp3LinkPegGet;   
OamScmMtp3RoutePegGet                 *scmMtp3RoutePegGet;
OamScmSccpGenPegGet                   *scmSccpGenPegGet;  
OamScmBssapGenPegGet                  *scmBssapGenPegGet; 
/*OamScmTcapPegGet                      *scmTcapPegGet; 
OamScmMapTimerConfig                  *scmMapTimerConfig;*/
OamScmLinkSetStatusGet                *scmLinkSetStatusGet; 
OamScmLinkStatusGet                   *scmLinkStatusGet;
OamScmRouteStatusGet                  *scmRouteStatusGet;
OamScmSsnStatusGet                    *scmSsnStatusGet; 
OamScmSccpLssnConfig                  *scmSccpLssnConfig;  
OamScmSccpRssnConfig                  *scmSccpRssnConfig;
OamScmSccpCssnConfig                  *scmSccpCssnConfig;  
sksGenConfig                          *sksGenConfigPtrToPtr;


/*AOIP: Oam Structures*/
OamScmBsInterfaceConfig       *scmBsInterfaceConfig = NULL;
OamScmBsTimerConfig           *scmBsTimerConfig     = NULL;


OamScmSccpInitConfig          *ScmSccpInitConfig = NULL;  /*Preconfig message*/
OamScmSccpSpConfig            *ScmSccpSpConfig   = NULL;
OamScmSccpSsConfig            *ScmSccpSsConfig   = NULL;
OamScmSccpCssConfig           *ScmSccpCssConfig  = NULL;
OamScmSccpCspConfig           *ScmSccpCspConfig  = NULL;
OamScmSccpTmrConfig           *ScmSccpTmrConfig  = NULL;


OamScmSctpInitConfig          *ScmSctpInitConfig  = NULL;   /*Preconfig message*/
OamScmSctpConfig              *ScmSctpConfig      = NULL;  
OamScmSctpTimerConfig         *ScmSctpTmrConfig   = NULL;

OamScmM3uaInitConfig          *ScmM3uaInitConfig   = NULL;   /*Preconfig Message*/ 
OamScmM3uaLocalAspConfig      *ScmM3uaLocAspConfig = NULL;
OamScmM3uaRemoteAspConfig     *ScmM3uaRemAspConfig = NULL;
OamScmM3uaLocalAsConfig       *ScmM3uaLocAsConfig  = NULL;
OamScmM3uaRemoteAsConfig      *ScmM3uaRemAsConfig  = NULL;
OamScmM3uaTimerConfig         *ScmM3uaTimerConfig  = NULL;
OamScmM3uaLocalAspAdminConfig *ScmM3uaLAspAdminCfg = NULL;
/*AOIP: END*/

/*AOIP FUNC*/
I_U16 check_self_or_peer_admin_cmd(U16);
/*AOIP FUNC*/

/**********************************************************************************/
/*this function handle the oam command received from oam and after parsing the command,
 it sends the command to respective stack command handler for command action */
/**********************************************************************************/


int process_oam_message(U8* msg_buff)
{
 U8 app_id, interfacetype, ret, peer_update = 0;
 S32 ret_val=0;
 U16 opcode, tr_opcode, resp_opcode, Length, resp_len;
 U32 previous_cmd_status = 0;
 resp_len = sizeof(ScmOamResponse);
 opcode = ((ScmHdr *)msg_buff)->opcode;
 Length = ((ScmHdr *)msg_buff)->len;
  
/* tr_opcode = opcode - BASE_OPCODE_SCM;*/
 tr_opcode = opcode - BASE_OPCODE_SCM_AOIP;
 
  strcpy(g_parameter.function_string, "process_oam_message()");


 oam_transaction_Id[tr_opcode].operation = ((ScmHdr *)msg_buff)->operation;
 oam_transaction_Id[tr_opcode].transaction_Id = ((ScmHdr *)msg_buff)->trid;
 oam_transaction_Id[tr_opcode].pegrfu      = ((ScmHdr *)msg_buff)->spare;/*store peg cmd indication */
 switch( opcode )
 {
  case OAM_SCM_SS7_STACK_CONFIG:
       if(xxx_client_sockfd[ENT_NWSTK] <= 0)
       {
        SCM_printf(SCM_CRITICAL,"NWSTK IS DOWN: 'CAN NOT SEND CMD TO STACK'");
        match_resp_opcode(opcode,  &resp_opcode);
        send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                        ((ScmHdr *)msg_buff)->spare, ERROR_SCM_NWSTK_DOWN, 
                        NULL, resp_len, APP_ID_OAM );
         return 0;
       }
       else   
       {
       //#ifdef GCS_OBSOLETE
        peer_update = 1; /*to support gcs obsolete*/
       //#endif 
        ret = process_nw_stack_init_config_cmd ( msg_buff);
        if (((xxx_client_sockfd[ENT_PEER_SCM] > 0) && (g_parameter.multicmd_standby_respFlag  == 0)) &&
            ((g_roll_back_flag.multi_cmd_roll_back_flag == 0)  && (peer_update == 1)) && 
            ((g_parameter.redundant_status == SCM_ACTIVE) && (g_parameter.config_flag == 0)) &&
            (ret == 1))
        {
         SCM_printf(SCM_DEBUG,"stack init message stored for sync nwstk");
         g_parameter.multicmd_msg = scm_malloc(Length);
         g_parameter.peer_multi_cmdFlag = 1;  
         memcpy(g_parameter.multicmd_msg, msg_buff, Length);
        }   
        return ret;
       } 
       break;

  case OAM_SCM_ALARM_MODIFY:
       SCM_printf(SCM_INFO,"processing cmd:  modify stack alarm level");
       ret = set_stack_alarm_reporting_level ( msg_buff );
       return ret;
  case OAM_SCM_TRUNK_CIC_CONFIG:
       interfacetype = ((OamScmTrunkCicConfig*)msg_buff)->interfaceType;
       if(interfacetype == IF_TYP_BSSAP)
       {
        peer_update = 1;/* no update required in case of cic config for Aif dome 
                           to support gcs obsolete*/
        app_id = APP_ID_NWSTK;  
       }
       else 
       {
        SCM_printf(SCM_MAJOR,"INTERFACE TYPE UNKNOWN");
        if(g_parameter.config_flag == 0)
        {    
         send_resp_to_oam(SCM_OAM_TRUNK_CIC_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, 
                         ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare ,ERROR_WRONG_INTERFACE_TYPE, NULL, 
                         resp_len, APP_ID_OAM);
        }  
        return 0;
       }
       break;
  case OAM_SCM_INTERFACE_CONFIG:
       interfacetype = ((OamScmTrunkCicConfig*)msg_buff)->interfaceType;
       if(interfacetype == IF_TYP_BSSAP)
       {
        app_id = APP_ID_NWSTK;
        peer_update = 1; /* not required dome
                           to support gcs obsolete*/
       }
       else
       if( (interfacetype == IF_TYP_ISUP) || (interfacetype == IF_TYP_OTHER))
       {
        if(g_parameter.config_flag == 0)
        { 
         send_resp_to_oam(  SCM_OAM_INTERFACE_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, 
                          ((ScmHdr *)msg_buff)->trid,
                          ((ScmHdr *)msg_buff)->spare , NO_ERROR, NULL, resp_len, APP_ID_OAM );
        }
        SCM_printf(SCM_MAJOR,"INTERFACE ISUP/OTHER");
        return 1;
 
       }
       else  
       { 
        send_resp_to_oam(  SCM_OAM_INTERFACE_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation,
                        ((ScmHdr *)msg_buff)->trid, 
                        ((ScmHdr *)msg_buff)->spare , ERROR_WRONG_INTERFACE_TYPE, NULL, resp_len, APP_ID_OAM );
        SCM_printf(SCM_MAJOR,"INTERFACE TYPE UNKNOWN");
        return 0;
       }
       break;
  default:  
       app_id = get_entity_appid(opcode, &peer_update, ((ScmHdr *)msg_buff)->operation);
       if(app_id == 0)
       {
        SCM_printf(SCM_MAJOR," Oam message discarded: cause WRONG OPCODE VALUE");
        send_resp_to_oam(  0, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                        ((ScmHdr *)msg_buff)->spare,
                        ERROR_WRONG_OPCODE, NULL, resp_len, APP_ID_OAM);
        return 0;
       }
       break ;  
 }  
 previous_cmd_status = check_if_previous_cmd_in_progress(app_id);   
 if(previous_cmd_status == 0)
 {    
    switch(app_id)
      {
        case APP_ID_SIGTRAN:
        case APP_ID_MAP:
             if(xxx_client_sockfd[ENT_SIGTRAN] <= 0)
              {
               SCM_printf(SCM_CRITICAL,"ENTITY SIGTRAN IS DOWN: 'CAN NOT SEND CMD TO STACK'");
              if(g_parameter.config_flag == 0)
               { 
                match_resp_opcode(opcode,  &resp_opcode);
                send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                                  ((ScmHdr *)msg_buff)->spare, UNKNOWN_CAUSE, NULL, resp_len, 
                                   APP_ID_OAM);
               }
               return 0;  
              }
             else   
              ret_val = process_maptcap_stack_cmd (msg_buff);
            
               SCM_printf(SCM_CRITICAL,"standby_respFlag[%d] roll_back_flag[%d] peer_update[%d] config_flag[%d]\n",
                       g_parameter.maptcap_standby_respFlag, g_roll_back_flag.maptcap_roll_back_flag, peer_update,
                       g_parameter.config_flag);

              if((xxx_client_sockfd[ENT_PEER_SCM] > 0) && (g_parameter.maptcap_standby_respFlag == 0)
                 &&(g_roll_back_flag.maptcap_roll_back_flag == 0) && (peer_update == 1) 
                 && (g_parameter.redundant_status == SCM_ACTIVE) && (g_parameter.config_flag == 0) &&
                 (ret_val != 0) )/*AOIP_HA*/
               {
                /*AOIP: CHANGES-HA*/
                SCM_printf(SCM_DEBUG,"SIGTRAN message stored for sync STACK\n");
                g_parameter.map_tcap_msg = scm_malloc(Length);
                g_parameter.peer_map_tcap_cmdFlag = 1;  
                memcpy(g_parameter.map_tcap_msg, msg_buff, Length);
               }   
              break; 
        case APP_ID_LAPD:
             if(xxx_client_sockfd[ENT_LAPD] <= 0)
               {
                SCM_printf(SCM_CRITICAL,"AN ENTITY CONNECTED TO SCM LAPD DOWN 'CAN NOT SEND CMD TO STACK'");
                if(g_parameter.config_flag == 0)
                {
                  match_resp_opcode(opcode,  &resp_opcode);
                  send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                                  ((ScmHdr *)msg_buff)->spare, 
                                  ERROR_SCM_LAPD_DOWN, NULL, resp_len, APP_ID_OAM);
                }
                return 0;  
               }
             else   
               ret = process_lapd_stack_cmd (msg_buff);
               if((xxx_client_sockfd[ENT_PEER_SCM] > 0) && (g_parameter.lapd_standby_respFlag == 0)
                  &&(g_roll_back_flag.lapd_roll_back_flag == 0) && (peer_update == 1)&& 
                  (g_parameter.redundant_status == SCM_ACTIVE) && (g_parameter.config_flag == 0))
                {
                 g_parameter.lapd_msg = scm_malloc(Length);
                 g_parameter.peer_lapd_cmdFlag = 1;  
                 memcpy(g_parameter.lapd_msg, msg_buff, Length);
                }   
               break;
        case APP_ID_NWSTK:
             if(xxx_client_sockfd[ENT_NWSTK] <= 0)
              {
               SCM_printf(SCM_CRITICAL,"NWSTK IS DOWN: 'CAN NOT SEND CMD TO STACK'");
              if(g_parameter.config_flag == 0)
              { 
               match_resp_opcode(opcode,  &resp_opcode);
               send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                                  ((ScmHdr *)msg_buff)->spare, 
                                  ERROR_SCM_NWSTK_DOWN, NULL, resp_len, APP_ID_OAM );
              }  
               return 0;  
              }
             else   
               ret = process_nw_stack_cmd (msg_buff);
 /*                SCM_printf(SCM_DEBUG," g_parameter.nwstk_standby_respFlag :%d",g_parameter.nwstk_standby_respFlag);
                 SCM_printf(SCM_DEBUG,"g_roll_back_flag.nwstk_roll_back_flag  :%d",g_roll_back_flag.nwstk_roll_back_flag);
                 SCM_printf(SCM_DEBUG,"g_parameter.redundant_status  :%d",g_parameter.redundant_status);
                 SCM_printf(SCM_DEBUG,"g_parameter.config_flag  :%d",g_parameter.config_flag);
                 SCM_printf(SCM_DEBUG," ret :%d", ret);*/
               if( ((xxx_client_sockfd[ENT_PEER_SCM] > 0) && (g_parameter.nwstk_standby_respFlag == 0)) &&
                   ((g_roll_back_flag.nwstk_roll_back_flag == 0)  && (peer_update == 1))&& 
                   ((g_parameter.redundant_status == SCM_ACTIVE) && (g_parameter.config_flag == 0)) &&
                   (ret == 1))
                {
                 SCM_printf(SCM_DEBUG,"Nwstk message stored for sync nwstk");
                 g_parameter.nwstk_msg = scm_malloc(Length);
                 g_parameter.peer_nwstk_cmdFlag = 1;  
                 memcpy(g_parameter.nwstk_msg, msg_buff, Length);
                }   
               break;
        /*AOIP: APPID BSSAP*/
        case APP_ID_BS:
             if(xxx_client_sockfd[ENT_BSSAP] <= 0)
              {
               SCM_printf(SCM_CRITICAL,"ENTITY BSSAP IS DOWN: CAN NOT SEND CMD TO STACK\n");
               if(g_parameter.config_flag == 0)
                {
                  match_resp_opcode(opcode,  &resp_opcode);
                  send_resp_to_oam (resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                                    ((ScmHdr *)msg_buff)->spare, UNKNOWN_CAUSE, NULL, resp_len, APP_ID_OAM); 
                }
               return 0;
               }
             else
               ret = process_bssap_stack_cmd (msg_buff);
               break;
         /*AOIP: END*/
        default:
              SCM_printf (SCM_CRITICAL, "WRONG APP_ID VALUE");
              ret = 0;
              break;
      } 
 }
 else
 {
   SCM_printf(SCM_MAJOR,"PREVIOUS COMMAND IN PROGRESS FOR APP_ID : %d : CAN NOT PROCESS CMD", app_id);
  if(g_parameter.config_flag == 0)
  { 
   match_resp_opcode(opcode,  &resp_opcode);
   send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                      ((ScmHdr *)msg_buff)->spare, 
                      ERROR_PREVIOUS_CMD_IN_PROGRESS, NULL, resp_len, APP_ID_OAM);
  } 
   return 0;
 }
 return ret;
} 

/**********************************************************************************/
/*this function process the alarm level modify command for all stack entity it forms
 the command and send to respective stack entity */
/**********************************************************************************/
int set_stack_alarm_reporting_level (U8* msg_buff )
{
 U8 isup_alarm_level = 0, row_count,alarm_level =0;
 U8 cmd_buff[100];
 U16 Length, loop, resp_len;
 U32 cmd, noe, ctgry, alarm_type;
 signed int ret_val;
 U16 opcode, tr_opcode;
 resp_len = sizeof(ScmOamResponse);
 opcode = ((ScmHdr *)msg_buff)->opcode;
 tr_opcode = opcode - BASE_OPCODE_SCM;
 multi_cmd[0].msg_type = opcode;
 scmAlarmModify = (OamScmAlarmModify*)msg_buff;
 g_parameter.alarm_level = scmAlarmModify->alarmLevel;
 sksGenSetConfig                 NwstkGenSetConfig;    
 strcpy(g_parameter.function_string, "set_stack_alarm_reporting_level()");
 
 if(timer_info[TIMER_MULTICMD].timer_strt_flag == 1)
   {
    SCM_printf(SCM_MAJOR," PREVIOUS COMMAND IN PROGRESS FOR NWSTK : CAN NOT PROCESS OAM CMD"); 
    send_resp_to_oam(  SCM_OAM_ALARM_MODIFY_RESP, ((ScmHdr *)msg_buff)->operation, 
                    ((ScmHdr *)msg_buff)->trid,((ScmHdr *)msg_buff)->spare , ERROR_PREVIOUS_CMD_IN_PROGRESS, NULL, resp_len, APP_ID_OAM);
    return 0;
   }
  switch( g_parameter.alarm_level )
   {
        case ALRM_LVL_CRIT:
             isup_alarm_level = 1;
             break;
        case ALRM_LVL_MAJR:
             isup_alarm_level = 2;
        case ALRM_LVL_MINR:
        case ALRM_LVL_INFO :
        case ALRM_LVL_WARN :
             isup_alarm_level = 3;
   }
  switch( g_parameter.alarm_level )
   {
        case ALRM_LVL_CRIT:
             alarm_level = 0;
             break;
        case ALRM_LVL_MAJR:
             alarm_level = 1;
        case ALRM_LVL_MINR:
             alarm_level = 2;

        case ALRM_LVL_INFO:
        case ALRM_LVL_WARN:
             alarm_level = 3;
   }

 
 ret_val = GetSksGenConfigData(&sksGenConfigPtrToPtr, &row_count);
 if(ret_val == 0)
  {
   start_timer ( TIMER_MULTICMD, APP_ID_NWSTK, transaction_Id[tr_opcode], (U8*)msg_buff );
   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
   for(loop = 0; loop<row_count ;loop++)
    {
     switch(sksGenConfigPtrToPtr[loop].sksGenCfgstackType)
      {
       case  APP_ID_MTP3:
             Length            = sizeof(sksGenSetConfig);
             NwstkGenSetConfig.sksGenCfgAlarmLevel  = alarm_level;
             NwstkGenSetConfig.sksGenCfgTraceLevel  = sksGenConfigPtrToPtr[loop].sksGenCfgTraceLevel;
             NwstkGenSetConfig.sksGenCfgtraceOutput = sksGenConfigPtrToPtr[loop].sksGenCfgtraceOutput;
             NwstkGenSetConfig.sksGenCfgtraceOnOff  = sksGenConfigPtrToPtr[loop].sksGenCfgtraceOnOff;
             memcpy(cmd_buff, &NwstkGenSetConfig, Length);
             form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_MTP3_GENCFG,
                               transaction_Id[MULTI_CMD], Length);
             SCM_printf(SCM_INFO,"SCM -> MTP3: Alarm level modify 'Alarm lvl %d'", alarm_level);
             ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
            if(ret_val <= 0)
              {
               g_parameter.config_cmd_resp = 0;
               SCM_printf (SCM_CRITICAL, "Command send to nwstk failed");
              }
             break;

       case  APP_ID_BSSAP:
              Length            = sizeof(sksGenSetConfig);
             NwstkGenSetConfig.sksGenCfgAlarmLevel  = alarm_level;
             NwstkGenSetConfig.sksGenCfgTraceLevel  = sksGenConfigPtrToPtr[loop].sksGenCfgTraceLevel;
             NwstkGenSetConfig.sksGenCfgtraceOutput = sksGenConfigPtrToPtr[loop].sksGenCfgtraceOutput;
             NwstkGenSetConfig.sksGenCfgtraceOnOff  = sksGenConfigPtrToPtr[loop].sksGenCfgtraceOnOff;
             memcpy(cmd_buff, &NwstkGenSetConfig, Length);
             form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_GENCFG,
                               transaction_Id[MULTI_CMD], Length);
             SCM_printf(SCM_INFO,"SCM -> BSSAP: Alarm level modify 'Alarm lvl %d'", alarm_level);
             ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
            if(ret_val <= 0)
              {
               g_parameter.config_cmd_resp = 0;
               SCM_printf (SCM_CRITICAL, "Command send to nwstk failed");
              }
             break;

        case APP_ID_SCCP:
              Length            = sizeof(sksGenSetConfig);
             NwstkGenSetConfig.sksGenCfgAlarmLevel  = alarm_level;
             NwstkGenSetConfig.sksGenCfgTraceLevel  = sksGenConfigPtrToPtr[loop].sksGenCfgTraceLevel;
             NwstkGenSetConfig.sksGenCfgtraceOutput = sksGenConfigPtrToPtr[loop].sksGenCfgtraceOutput;
             NwstkGenSetConfig.sksGenCfgtraceOnOff  = sksGenConfigPtrToPtr[loop].sksGenCfgtraceOnOff;
             memcpy(cmd_buff, &NwstkGenSetConfig, Length);
             form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_GENCFG,
                               transaction_Id[MULTI_CMD], Length);
             SCM_printf(SCM_INFO,"SCM -> SCCP: Alarm level modify 'Alarm lvl %d'", alarm_level);
             ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
            if(ret_val <= 0)
              {
               g_parameter.config_cmd_resp = 0;
               SCM_printf (SCM_CRITICAL, "Command send to nwstk failed");
              }
             break;
        default:
               break;

       }  
     /*send alarm level modify for isup */
     /*send alarm level modify for maptcap */
     /*send alarm level modify for cap */
     if(loop == row_count-1)
      {
       break;
      }
     else continue;
    }
    /* here send alarm level modify cmd to isup */
    Length = 12;
    ctgry = 4;
    cmd = OAM_ISUP_SS7_SM_SET_ERR_LEVEL;
    noe = 2;
    EXTRACT_32(8,  ALL_ERROR,  cmd_buff);
    cmd_buff[12] = isup_alarm_level;
    /*form_isup_header(cmd_buff, APP_ID_ISUP,  noe, ctgry,
                     transaction_Id[MULTI_CMD], cmd, Length);
    SCM_printf(SCM_INFO,"SCM -> ISUP: Alarm level modify 'Alarm lvl %d'", isup_alarm_level); */
    ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_ISUP, Length);
    /* end here */
    /*here send alarm level modify to map tcap */
     /*tcap */
     ctgry = 4;
     cmd = 0;
     noe = 2;
     Length = 13;
     form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry,
                         transaction_Id[MULTI_CMD],cmd, Length);
     EXTRACT_32(8,  ALL_ERROR,  cmd_buff);
     cmd_buff [12] = isup_alarm_level;
     ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_MAP, Length);
     /*map */ 
     ctgry = 1;
     cmd = MAP_SET_ERROR_LEVEL_REQUEST;
     noe = 2;
     Length = 10;
     alarm_type = MAP_PROTOCOL_ERROR;
     form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry,
                         transaction_Id[MULTI_CMD], cmd, Length);
     cmd_buff[8] = alarm_type;  
     if((isup_alarm_level == ALRM_LVL_MINR) || (isup_alarm_level == ALRM_LVL_WARN)||(isup_alarm_level == ALRM_LVL_MAJR))
       cmd_buff [9] = 2;
     else
      if( isup_alarm_level == ALRM_LVL_CRIT)
     cmd_buff [9] = 1;
      else
     cmd_buff [9] = 0;
     SCM_printf(SCM_INFO,"SCM -> ISUP: Alarm level modify 'Alarm lvl %d'", cmd_buff [9]); 
     ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_MAP, Length);
    /*end here */
    if(ret_val == 0)
     {
      g_parameter.config_cmd_resp = 0;
      stop_timer(TIMER_NWSTK);
     }
  return 1; 
  }
 else
 {
  SCM_printf(SCM_CRITICAL,"READ FROM DB FOR GEN CFG FAILED TO MODIFY ALARM LEVEL: ERROR_CODE: %d", ret_val);
  send_resp_to_oam(  SCM_OAM_ALARM_MODIFY_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                   ((ScmHdr *)msg_buff)->spare , UNKNOWN_CAUSE, NULL, resp_len, APP_ID_OAM);
  return 0;
 }
}


/**********************************************************************************/
/*this function handle the initconfig command , it froms multi commands for nwstk and 
 send them to stack as well as it stores the global varriable received in initconfig 
 command*/
/**********************************************************************************/
int process_nw_stack_init_config_cmd (U8* msg_buff)
{
 U8 cmd_buff[100], operation, sio_loop;
 U16 Length, send_success_flag = 0, resp_opcode;
 S32 ret_val;
 U16 opcode, tr_opcode, resp_len;
 resp_len = sizeof(ScmOamResponse);
 opcode = ((ScmHdr *)msg_buff)->opcode;
 tr_opcode = opcode - BASE_OPCODE_SCM;
 operation = ((ScmHdr *)msg_buff)->operation;
 Length = ((ScmHdr *)msg_buff)->len;

 ScmNwstkLinkSetConfig		NwstkLinkSetConfig;
 ScmNwstkSs7RouteConfig	   	NwstkSs7RouteConfig;
 resp_opcode = SCM_OAM_SS7_STACK_CONFIG_RESP;
 strcpy(g_parameter.function_string, "process_nw_stack_init_config_cmd()");

 
 if(multi_cmd[0].lock_flag   == SS7_TRUE)
   {
     SCM_printf(SCM_MAJOR," Previous command init config is in progress : can not process oam cmd"); 
     send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                       ((ScmHdr *)msg_buff)->spare, 
                     ERROR_PREVIOUS_CMD_IN_PROGRESS, NULL, resp_len,  APP_ID_OAM);
     return 0;
   }
 if((g_parameter.config_flag == SS7_TRUE) && (timer_info[TIMER_MULTICMD].timer_strt_flag == 1))
   {
    stop_timer(TIMER_MULTICMD);
   }
  
 SCM_printf(SCM_MAJOR," processing cmd : STACK_INIT_CONFIG ");
 SCM_DUMP(0, Length, msg_buff, 15);
 initconfig = (OamScmSs7StackConfig*)msg_buff;
 if((((ScmHdr *)msg_buff)->operation == SCM_DELETE) && ( initconfig->selfPointCode != g_parameter.opc_value))
 { 
    SCM_printf(SCM_MAJOR," Cmd dropped : SS7_STACK_CONFIG DEL with wrong opc received");
    send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                    ((ScmHdr *)msg_buff)->spare, UNKNOWN_CAUSE, NULL, resp_len,  APP_ID_OAM);
 }
 multi_cmd[0].prv_family      = g_parameter.family;     
 multi_cmd[0].roll_back_flag = 0;
 multi_cmd[0].no_of_res = 0;
 multi_cmd[0].prv_opc_value   = g_parameter.opc_value;
 multi_cmd[0].prv_alarm_level = g_parameter.alarm_level;
 g_parameter.opc_value        = initconfig->selfPointCode;
 g_parameter.alarm_level      = initconfig->alarmLevel;
 SCM_printf(SCM_INFO,"g_parameter.alarm_level : %d:", g_parameter.alarm_level);
 if(initconfig->family == SYS_FAMILY_ITU)
  {
   g_parameter.family = ITU_FAMILY;
  }
 else if(initconfig->family == SYS_FAMILY_ANSI)
  {
   g_parameter.family = ANSI_FAMILY;
  }
 else
  {
  if(g_parameter.config_flag == 0)
   {   
    send_resp_to_oam(resp_opcode, ((ScmHdr *)msg_buff)->operation,
                    ((ScmHdr *)msg_buff)->trid ,((ScmHdr *)msg_buff)->spare ,ERROR_FAMILY_NOT_SUPPORTED, NULL, resp_len, APP_ID_OAM);
   }
   SCM_printf(SCM_MAJOR," WRONG FAMILY TYPE");
   g_parameter.family = ITU_FAMILY;
   SCM_printf(SCM_MAJOR," set default family type i.e. ITU_FAMILY");
   g_parameter.config_cmd_resp = 0;
   SCM_printf(SCM_MAJOR," msc config command : FAILED");
    
   return 0; 
  }
 if( g_parameter.config_flag == SS7_FALSE)
  {
   multi_cmd[0].db_oam_stamp = OAM_STAMP;
   oam_transaction_Id[tr_opcode].transaction_Id = ((ScmHdr *)msg_buff)->trid;/*store oam trid here*/
  }
 else
  multi_cmd[0].db_oam_stamp = DB_STAMP;
  multi_cmd[0].no_of_res         = 0;
  multi_cmd[0].resp_flag         = SS7_TRUE;
  multi_cmd[0].lock_flag         = 1;
  multi_cmd[0].msg_type          = initconfig->scmhdr.opcode;
  multi_cmd[0].stored_msg        = (U8*)scm_malloc(sizeof(OamScmSs7StackConfig));
  memcpy(multi_cmd[0].stored_msg, msg_buff, sizeof(OamScmSs7StackConfig));
  multi_cmd[0].no_of_command_sent= 0;
  multi_cmd[0].roll_back_flag    = SS7_FALSE;
  Length                            = sizeof(ScmNwstkLinkSetConfig);

  start_timer ( TIMER_MULTICMD, APP_ID_NWSTK, transaction_Id[MULTI_CMD], msg_buff);

if(operation == SCM_ADD)
{
  /*first command  linkset add for 0th linkset*/
  NwstkLinkSetConfig.linkSetId = 0;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode  = g_parameter.opc_value;
  NwstkLinkSetConfig.family = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator = 0;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : LinkSet ADD:0"); 
   form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_ADD,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;



  /*3rd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 0;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 03;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO_SSN "); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  
  for(sio_loop = 0; sio_loop <= 5; )
  {
   /*4th command route add dpc sio ssn */
   NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
   NwstkSs7RouteConfig.linkSetId = 0;
   NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
   NwstkSs7RouteConfig.family    = g_parameter.family;
   NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
   NwstkSs7RouteConfig.sio       = sio_loop;
   NwstkSs7RouteConfig.rssn      = 254;
   NwstkSs7RouteConfig.lssn      = 0;
   NwstkSs7RouteConfig.sstTestOn = 0;
   NwstkSs7RouteConfig.networkIndicator = 0;
   Length = sizeof(ScmNwstkSs7RouteConfig);
   memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
   SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO "); 
   form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );


   multi_cmd[0].no_of_command_sent++;
   ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
   if(ret_val > 0)
    {
     send_success_flag ++;
     if(sio_loop == 3)
      {
       sio_loop = sio_loop + 2;
      }
     else
      {
       sio_loop++;
      }
    }
  }

}
else
{  
  /*3rd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 0;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 03;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL : SYS_DPC_SIO_SSN "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );
   
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  
   /*4th command route add dpc sio ssn */
/*   NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
  NwstkSs7RouteConfig.linkSetId = 0;
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
  NwstkSs7RouteConfig.family    = g_parameter.family;
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
  NwstkSs7RouteConfig.sio       = 3;
  NwstkSs7RouteConfig.rssn      = 254;
  NwstkSs7RouteConfig.lssn      = 0;
  NwstkSs7RouteConfig.sstTestOn = 0;
  NwstkSs7RouteConfig.networkIndicator = 0;
  Length = sizeof(ScmNwstkSs7RouteConfig);
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL STYLE: DPC_SIO "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;*/


  for(sio_loop = 0; sio_loop <= 5; )
  {
    /*5th command route add dpc sio ssn */
    NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
    NwstkSs7RouteConfig.linkSetId = 0;
    NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
    NwstkSs7RouteConfig.family    = g_parameter.family;
    NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
    NwstkSs7RouteConfig.sio       = sio_loop;
    NwstkSs7RouteConfig.rssn      = 254;
    NwstkSs7RouteConfig.lssn      = 0;
    NwstkSs7RouteConfig.sstTestOn = 0;
    NwstkSs7RouteConfig.networkIndicator = 0;
    Length = sizeof(ScmNwstkSs7RouteConfig);
    memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL STYLE: DPC_SIO "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

    multi_cmd[0].no_of_command_sent++;
    ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
    if(ret_val > 0)
     {
      send_success_flag ++;
      if(sio_loop == 3)
       {
        sio_loop = sio_loop + 2;
       }
      else
       {
        sio_loop++;
       }
     }
  }

  /*first command  linkset del for 0th linkset*/
  NwstkLinkSetConfig.linkSetId = 0;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode  = g_parameter.opc_value;
  NwstkLinkSetConfig.family = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator = 0;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
      SCM_printf(SCM_INFO," SENDING CMD : LinkSet DEL: 0"); 
      form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_DEL,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;



}

  if(ret_val <= 0)
    stop_timer(TIMER_MULTICMD);
 
  if(send_success_flag < 7)
   {
     SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
     stop_timer (TIMER_MULTICMD);
      if( g_parameter.config_flag == SS7_FALSE  )
        {
         multi_cmd[0].roll_back_flag = 1;
         multi_cmd[0].lock_flag      = 1;
         //process_roll_back(multi_cmd[0].stored_msg);/*make multi_cmd pointer null after processing of                                                      roll back */
         
         if(multi_cmd[0].stored_msg !=  NULL)
          { 
           free(multi_cmd[0].stored_msg);
           multi_cmd[0].stored_msg = NULL;
          } 
         if(send_success_flag == 0)
          {
           return 0;
          }
         }
     else
       {
        g_parameter.config_cmd_resp = 0;
        SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
        return 0;
       }   
   }
   
  return 1; 
}    


int process_nw_stack_init_config_cmd_set2 (U16 opcode, U8 operation)
{
 U8 cmd_buff[100], sio_loop;
 U16 Length, send_success_flag = 0, resp_opcode;
 S32 ret_val;
 U16 tr_opcode, resp_len;
 resp_len = sizeof(ScmOamResponse);
 tr_opcode = opcode - BASE_OPCODE_SCM;

 ScmNwstkLinkSetConfig		NwstkLinkSetConfig;
 ScmNwstkSs7RouteConfig	   	NwstkSs7RouteConfig;
 resp_opcode = SCM_OAM_SS7_STACK_CONFIG_RESP;
 strcpy(g_parameter.function_string, "process_nw_stack_init_config_cmd_set2()");

 SCM_printf(SCM_MAJOR," processing cmd : STACK_INIT_CONFIG CMD SET 2");
 Length                            = sizeof(ScmNwstkLinkSetConfig);
if(operation == SCM_ADD)
{
  /*1st command linkset add for 255th linkset*/ 
  NwstkLinkSetConfig.linkSetId = 255;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode  = g_parameter.opc_value;
  NwstkLinkSetConfig.family = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator = 0x80;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : LinkSet ADD :255 "); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_ADD,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;

  /*2nd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 255;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 0x83;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO_SSN "); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  
  for(sio_loop = 0x80; sio_loop <= 0x85; )
  {
   /*4th command route add dpc sio ssn */
   NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
   NwstkSs7RouteConfig.linkSetId = 255;
   NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
   NwstkSs7RouteConfig.family    = g_parameter.family;
   NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
   NwstkSs7RouteConfig.sio       = sio_loop;
   NwstkSs7RouteConfig.rssn      = 254;
   NwstkSs7RouteConfig.lssn      = 0;
   NwstkSs7RouteConfig.sstTestOn = 0;
   NwstkSs7RouteConfig.networkIndicator = 0;
   Length = sizeof(ScmNwstkSs7RouteConfig);
   memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
   SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO "); 
   form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );


   multi_cmd[0].no_of_command_sent++;
   ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
   if(ret_val > 0)
    {
     send_success_flag ++;
     if(sio_loop == 0x83)
      {
       sio_loop = sio_loop + 2;
      }
     else
      {
       sio_loop++;
      }
    }
  }

}
else
{  
  /*3rd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 255;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 0x83;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL : SYS_DPC_SIO_SSN "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );
   
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  

  for(sio_loop = 0x80; sio_loop <= 0x85; )
  {
    /*5th command route add dpc sio ssn */
    NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
    NwstkSs7RouteConfig.linkSetId = 255;
    NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
    NwstkSs7RouteConfig.family    = g_parameter.family;
    NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
    NwstkSs7RouteConfig.sio       = sio_loop;
    NwstkSs7RouteConfig.rssn      = 254;
    NwstkSs7RouteConfig.lssn      = 0;
    NwstkSs7RouteConfig.sstTestOn = 0;
    NwstkSs7RouteConfig.networkIndicator = 0;
    Length = sizeof(ScmNwstkSs7RouteConfig);
    memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL STYLE: DPC_SIO "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

    multi_cmd[0].no_of_command_sent++;
    ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
    if(ret_val > 0)
     {
      send_success_flag ++;
      if(sio_loop == 0x83)
       {
        sio_loop = sio_loop + 2;
       }
      else
       {
        sio_loop++;
       }
     }
  }


  /*second command linkset del for 255th linkset*/ 
  NwstkLinkSetConfig.linkSetId         = 255;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode    = g_parameter.opc_value;
  NwstkLinkSetConfig.family            = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator  = 0x80;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
      SCM_printf(SCM_INFO," SENDING CMD : LinkSet DEL: 255 "); 
      form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_DEL,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;

}

  if(ret_val <= 0)
    stop_timer(TIMER_MULTICMD);
 
  if(send_success_flag < 7)
   {
     SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
     stop_timer (TIMER_MULTICMD);
      if( g_parameter.config_flag == SS7_FALSE  )
        {
         multi_cmd[0].roll_back_flag = 1;
         multi_cmd[0].lock_flag      = 1;
         //process_roll_back(multi_cmd[0].stored_msg);/*make multi_cmd pointer null after processing of                                                      roll back */
         
         if(multi_cmd[0].stored_msg !=  NULL)
          { 
           free(multi_cmd[0].stored_msg);
           multi_cmd[0].stored_msg = NULL;
          } 
         if(send_success_flag == 0)
          {
           return 0;
          }
         }
     else
       {
        g_parameter.config_cmd_resp = 0;
        SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
        return 0;
       }   
   }
   
  return 1; 
}    


int process_nw_stack_init_config_cmd_set4 (U16 opcode, U8 operation)
{
 U8 cmd_buff[100], sio_loop;
 U16 Length, send_success_flag = 0,  resp_opcode;
 S32 ret_val;
 U16 tr_opcode, resp_len;
 resp_len = sizeof(ScmOamResponse);
 tr_opcode = opcode - BASE_OPCODE_SCM;

 ScmNwstkLinkSetConfig		NwstkLinkSetConfig;
 ScmNwstkSs7RouteConfig	   	NwstkSs7RouteConfig;
 resp_opcode = SCM_OAM_SS7_STACK_CONFIG_RESP;
 strcpy(g_parameter.function_string, "process_nw_stack_init_config_cmd_set4()");

 SCM_printf(SCM_MAJOR," processing cmd : STACK_INIT_CONFIG CMD SET 4");
 Length                            = sizeof(ScmNwstkLinkSetConfig);
if(operation == SCM_ADD)
{

  /*1st command linkset add for 255th linkset*/ 
  NwstkLinkSetConfig.linkSetId = 252;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode  = g_parameter.opc_value;
  NwstkLinkSetConfig.family = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator = 0xc0;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : LinkSet ADD :252 "); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_ADD,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;

  /*2nd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 252;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 0xc3;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO_SSN "); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  
  for(sio_loop = 0xc0; sio_loop <= 0xc5; )
  {
   /*4th command route add dpc sio ssn */
   NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
   NwstkSs7RouteConfig.linkSetId = 252;
   NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
   NwstkSs7RouteConfig.family    = g_parameter.family;
   NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
   NwstkSs7RouteConfig.sio       = sio_loop;
   NwstkSs7RouteConfig.rssn      = 254;
   NwstkSs7RouteConfig.lssn      = 0;
   NwstkSs7RouteConfig.sstTestOn = 0;
   NwstkSs7RouteConfig.networkIndicator = 0;
   Length = sizeof(ScmNwstkSs7RouteConfig);
   memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
   SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO "); 
   form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );


   multi_cmd[0].no_of_command_sent++;
   ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
   if(ret_val > 0)
    {
     send_success_flag ++;
     if(sio_loop == 0xc3)
      {
       sio_loop = sio_loop + 2;
      }
     else
      {
       sio_loop++;
      }
    }
  }

}
else
{  
  /*3rd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 252;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 0xc3;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL : SYS_DPC_SIO_SSN "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );
   
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  

  for(sio_loop = 0xc0; sio_loop <= 0xc5; )
  {
    /*5th command route add dpc sio ssn */
    NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
    NwstkSs7RouteConfig.linkSetId = 252;
    NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
    NwstkSs7RouteConfig.family    = g_parameter.family;
    NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
    NwstkSs7RouteConfig.sio       = sio_loop;
    NwstkSs7RouteConfig.rssn      = 254;
    NwstkSs7RouteConfig.lssn      = 0;
    NwstkSs7RouteConfig.sstTestOn = 0;
    NwstkSs7RouteConfig.networkIndicator = 0;
    Length = sizeof(ScmNwstkSs7RouteConfig);
    memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL STYLE: DPC_SIO "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

    multi_cmd[0].no_of_command_sent++;
    ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
    if(ret_val > 0)
     {
      send_success_flag ++;
      if(sio_loop == 0xc3)
       {
        sio_loop = sio_loop + 2;
       }
      else
       {
        sio_loop++;
       }
     }
  }


  /*second command linkset del for 255th linkset*/ 
  NwstkLinkSetConfig.linkSetId         = 252;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode    = g_parameter.opc_value;
  NwstkLinkSetConfig.family            = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator  = 0xc0;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
      SCM_printf(SCM_INFO," SENDING CMD : LinkSet DEL: 255 "); 
      form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_DEL,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;

}

  if(ret_val <= 0)
    stop_timer(TIMER_MULTICMD);
 
  if(send_success_flag < 7)
   {
     SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
     stop_timer (TIMER_MULTICMD);
      if( g_parameter.config_flag == SS7_FALSE  )
        {
         multi_cmd[0].roll_back_flag = 1;
         multi_cmd[0].lock_flag      = 1;
         //process_roll_back(multi_cmd[0].stored_msg);/*make multi_cmd pointer null after processing of                                                      roll back */
         
         if(multi_cmd[0].stored_msg !=  NULL)
          { 
           free(multi_cmd[0].stored_msg);
           multi_cmd[0].stored_msg = NULL;
          } 
         if(send_success_flag == 0)
          {
           return 0;
          }
         }
     else
       {
        g_parameter.config_cmd_resp = 0;
        SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
        return 0;
       }   
   }
   
  return 1; 
}    


int process_nw_stack_init_config_cmd_set3 (U16 opcode, U8 operation)
{
 U8 cmd_buff[100], sio_loop;
 U16 Length, send_success_flag = 0, resp_opcode;
 S32 ret_val;
 U16 tr_opcode, resp_len;
 resp_len = sizeof(ScmOamResponse);
 tr_opcode = opcode - BASE_OPCODE_SCM;

 ScmNwstkLinkSetConfig		NwstkLinkSetConfig;
 ScmNwstkSs7RouteConfig	   	NwstkSs7RouteConfig;
 resp_opcode = SCM_OAM_SS7_STACK_CONFIG_RESP;
 strcpy(g_parameter.function_string, "process_nw_stack_init_config_cmd_set3()");

 SCM_printf(SCM_MAJOR," processing cmd : STACK_INIT_CONFIG CMD SET 3");
 Length                            = sizeof(ScmNwstkLinkSetConfig);
if(operation == SCM_ADD)
{

  /*1st command linkset add for 255th linkset*/ 
  NwstkLinkSetConfig.linkSetId = 253;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode  = g_parameter.opc_value;
  NwstkLinkSetConfig.family = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator = 0x40;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : LinkSet ADD :253 "); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_ADD,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;

  /*2nd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 253;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 0x43;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO_SSN "); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  
  for(sio_loop = 0x40; sio_loop <= 0x45; )
  {
   /*4th command route add dpc sio ssn */
   NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
   NwstkSs7RouteConfig.linkSetId = 253;
   NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
   NwstkSs7RouteConfig.family    = g_parameter.family;
   NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
   NwstkSs7RouteConfig.sio       = sio_loop;
   NwstkSs7RouteConfig.rssn      = 254;
   NwstkSs7RouteConfig.lssn      = 0;
   NwstkSs7RouteConfig.sstTestOn = 0;
   NwstkSs7RouteConfig.networkIndicator = 0;
   Length = sizeof(ScmNwstkSs7RouteConfig);
   memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
   SCM_printf(SCM_INFO," SENDING CMD : ROUTE ADD STYLE: DPC_SIO "); 
   form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );


   multi_cmd[0].no_of_command_sent++;
   ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
   if(ret_val > 0)
    {
     send_success_flag ++;
     if(sio_loop == 0x43)
      {
       sio_loop = sio_loop + 2;
      }
     else
      {
       sio_loop++;
      }
    }
  }

}
else
{  
  /*3rd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 253;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 0x43;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL : SYS_DPC_SIO_SSN "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );
   
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  

  for(sio_loop = 0x40; sio_loop <= 0x45; )
  {
    /*5th command route add dpc sio ssn */
    NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
    NwstkSs7RouteConfig.linkSetId = 253;
    NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
    NwstkSs7RouteConfig.family    = g_parameter.family;
    NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
    NwstkSs7RouteConfig.sio       = sio_loop;
    NwstkSs7RouteConfig.rssn      = 254;
    NwstkSs7RouteConfig.lssn      = 0;
    NwstkSs7RouteConfig.sstTestOn = 0;
    NwstkSs7RouteConfig.networkIndicator = 0;
    Length = sizeof(ScmNwstkSs7RouteConfig);
    memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL STYLE: DPC_SIO "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

    multi_cmd[0].no_of_command_sent++;
    ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
    if(ret_val > 0)
     {
      send_success_flag ++;
      if(sio_loop == 0x43)
       {
        sio_loop = sio_loop + 2;
       }
      else
       {
        sio_loop++;
       }
     }
  }


  /*second command linkset del for 255th linkset*/ 
  NwstkLinkSetConfig.linkSetId         = 253;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode    = g_parameter.opc_value;
  NwstkLinkSetConfig.family            = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator  = 0x40;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
      SCM_printf(SCM_INFO," SENDING CMD : LinkSet DEL: 255 "); 
      form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_DEL,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;

}

  if(ret_val <= 0)
    stop_timer(TIMER_MULTICMD);
 
  if(send_success_flag < 7)
   {
     SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
     stop_timer (TIMER_MULTICMD);
      if( g_parameter.config_flag == SS7_FALSE  )
        {
         multi_cmd[0].roll_back_flag = 1;
         multi_cmd[0].lock_flag      = 1;
         //process_roll_back(multi_cmd[0].stored_msg);/*make multi_cmd pointer null after processing of                                                      roll back */
         
         if(multi_cmd[0].stored_msg !=  NULL)
          { 
           free(multi_cmd[0].stored_msg);
           multi_cmd[0].stored_msg = NULL;
          } 
         if(send_success_flag == 0)
          {
           return 0;
          }
         }
     else
       {
        g_parameter.config_cmd_resp = 0;
        SCM_printf(SCM_CRITICAL,"BSC CONFIG COMMAND SEND FAILED");
        return 0;
       }   
   }
   
  return 1; 
}    




/**********************************************************************************/
/*this function performs the rollback action for nwstack in case of initconfig command 
 failure and delete the values added, also restore the previous global varriable values
 */
/**********************************************************************************/
int process_roll_back(U8* msg_buff)
{
 U8 cmd_buff[100], operation, sio_loop;
 U16 Length, send_success_flag = 0, resp_opcode;
 S32 ret_val;
 U16 opcode, tr_opcode, resp_len;
 resp_len = sizeof(ScmOamResponse);
 opcode = ((ScmHdr *)msg_buff)->opcode;
 tr_opcode = opcode - BASE_OPCODE_SCM;
 operation = ((ScmHdr *)msg_buff)->operation;
 Length = ((ScmHdr *)msg_buff)->len;

 ScmNwstkLinkSetConfig		NwstkLinkSetConfig;
 ScmNwstkSs7RouteConfig	   	NwstkSs7RouteConfig;
 resp_opcode = SCM_OAM_SS7_STACK_CONFIG_RESP;
 strcpy(g_parameter.function_string, "process_nw_stack_init_config_cmd()");

 
 multi_cmd[0].lock_flag   = 0;
 if(timer_info[TIMER_MULTICMD].timer_strt_flag == 1)
 {
  stop_timer(TIMER_MULTICMD);
 }
  
 SCM_printf(SCM_MAJOR," processing cmd : STACK_INIT_ROLLBACK CMD ");
 SCM_DUMP(0, Length, msg_buff, 15);
 initconfig = (OamScmSs7StackConfig*)msg_buff;
if(operation == SCM_DELETE)
{
  /*3rd command route add dpc_sio_ssn */
  NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;  
  NwstkSs7RouteConfig.linkSetId = 0;  
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;  
  NwstkSs7RouteConfig.family    = g_parameter.family;  
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO_SSN;  
  NwstkSs7RouteConfig.sio       = 03;  
  NwstkSs7RouteConfig.rssn      = 254;   
  NwstkSs7RouteConfig.lssn      = 254;  
  NwstkSs7RouteConfig.sstTestOn = 0;  
  NwstkSs7RouteConfig.networkIndicator = 0; 
  Length = sizeof(ScmNwstkSs7RouteConfig); 
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL : SYS_DPC_SIO_SSN "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );
   
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;
 
  
   /*4th command route add dpc sio ssn */
/*   NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
  NwstkSs7RouteConfig.linkSetId = 0;
  NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
  NwstkSs7RouteConfig.family    = g_parameter.family;
  NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
  NwstkSs7RouteConfig.sio       = 3;
  NwstkSs7RouteConfig.rssn      = 254;
  NwstkSs7RouteConfig.lssn      = 0;
  NwstkSs7RouteConfig.sstTestOn = 0;
  NwstkSs7RouteConfig.networkIndicator = 0;
  Length = sizeof(ScmNwstkSs7RouteConfig);
  memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL STYLE: DPC_SIO "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;*/


  for(sio_loop = 0; sio_loop <= 5; )
  {
    /*5th command route add dpc sio ssn */
    NwstkSs7RouteConfig.destinationPointCode = g_parameter.opc_value;
    NwstkSs7RouteConfig.linkSetId = 0;
    NwstkSs7RouteConfig.direction = LOCAL_ROUTE;
    NwstkSs7RouteConfig.family    = g_parameter.family;
    NwstkSs7RouteConfig.style     = SYS_DPC_SIO;
    NwstkSs7RouteConfig.sio       = sio_loop;
    NwstkSs7RouteConfig.rssn      = 254;
    NwstkSs7RouteConfig.lssn      = 0;
    NwstkSs7RouteConfig.sstTestOn = 0;
    NwstkSs7RouteConfig.networkIndicator = 0;
    Length = sizeof(ScmNwstkSs7RouteConfig);
    memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
  
    SCM_printf(SCM_INFO," SENDING CMD : ROUTE DEL STYLE: DPC_SIO "); 
    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                      transaction_Id[MULTI_CMD], sizeof(ScmNwstkSs7RouteConfig) );

    multi_cmd[0].no_of_command_sent++;
    ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
    if(ret_val > 0)
     {
      send_success_flag ++;
      if(sio_loop == 3)
       {
        sio_loop = sio_loop + 2;
       }
      else
       {
        sio_loop++;
       }
     }
  }

  /*first command  linkset del for 0th linkset*/
  NwstkLinkSetConfig.linkSetId = 0;/*linkset id*/
  NwstkLinkSetConfig.adjacentPointCode = 0;
  NwstkLinkSetConfig.localPointCode  = g_parameter.opc_value;
  NwstkLinkSetConfig.family = g_parameter.family;
  NwstkLinkSetConfig.networkIndicator = 0;/*ni value*/
  Length  = sizeof(ScmNwstkLinkSetConfig);
  memcpy(cmd_buff, &NwstkLinkSetConfig, Length);
  SCM_printf(SCM_INFO," SENDING CMD : LinkSet DEL: 0"); 
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_DEL,
                        transaction_Id[MULTI_CMD], sizeof(ScmNwstkLinkSetConfig) );
  multi_cmd[0].no_of_command_sent++;
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
  if(ret_val > 0)
  send_success_flag ++;



}
 process_nw_stack_init_config_cmd_set2 (opcode,  operation);
 process_nw_stack_init_config_cmd_set3 ( opcode, operation);
 process_nw_stack_init_config_cmd_set4 (opcode,  operation);

   
  return 1; 
}

/**********************************************************************************/
/*this function handle the nwstk command received from oam or command fetched from db,
 it processes the command and send to nwstack */
/**********************************************************************************/
int process_nw_stack_cmd (U8 *msg_buff)
{
 U8  hdrsize, family, operation, alarm_level =0, cardFlag;
 U32 opc;
 U16 Length, resp_len;
 U8 timeslot;
 resp_len = sizeof(ScmOamResponse); 
 signed int ret_val = 0;
 S32 dbSts;
 U16 opcode, tr_opcode, resp_opcode;
 opcode = ((ScmHdr *)msg_buff)->opcode;
 tr_opcode = opcode - BASE_OPCODE_SCM;
 hdrsize = 5;
 U8 cmd_buff[100];
 family  = g_parameter.family;
 opc     = g_parameter.opc_value;
 strcpy(g_parameter.function_string, "process_nw_stack_cmd()");
 operation = ((ScmHdr *)msg_buff)->operation;
 ScmNwstkLinkSetConfig		 NwstkLinkSetConfig;
 ScmNwstkSs7RouteConfig	   	 NwstkSs7RouteConfig;
 ScmNwstkSccpLssnConfig		 NwstkSccpLssnConfig;
 ScmNwstkMtp3TimerModify 	 NwstkMtp3TimerModify;
 ScmNwstkSccpTimerModify	 NwstkSccpTimerModify;
 ScmNwstkBssapTimerModify	 NwstkBssapTimerModify;
 ScmNwstkSccpRssnConfig		 NwstkSccpRssnConfig;
 ScmNwstkBssapCicConfig		 NwstkBssapCicConfig;
 ScmNwstkLinkSetAdminStateModify NwstkLinkSetAdminStateModify;
 ScmNwstkLinkConfig		 NwstkLinkConfig;
 ScmNwstkLinkAdminStateModify    NwstkLinkAdminStateModify;
 ScmNwstkSccpCssnConfig		 NwstkSccpCssnConfig;
 ScmNwstkMtp3GenPegGet 		 NwstkMtp3GenPegGet;
 ScmNwstkMtp2PegGet 		 NwstkMtp2PegGet;
 ScmNwstkMtp3LinkPegGet		 NwstkMtp3LinkPegGet;
 ScmNwstkMtp3RoutePegGet	 NwstkMtp3RoutePegGet;
 ScmNwstkSccpGenPegGet		 NwstkSccpGenPegGet;
 ScmNwstkBssapGenPegGet		 NwstkBssapGenPegGet;
 SccpSetBehaviorConfig		 sccpSetBehaviorConfig;
 ScmNwstkLinkStatus		 NwstkLinkStatus;
 ScmNwstkLinkSetStatus		 NwstkLinkSetStatus;
 ScmNwstkRouteStatus		 NwstkRouteStatus;
 ScmNwstkSsnStatus		 NwstkSsnStatus;
 ScmNwstkBssapcfgConfig          NwstkBssapcfgConfig;
 ScmNwstkSs7RouteAdminStateModify       NwstkSs7RouteAdminStateModify;
 sksGenSetConfig                 NwstkGenSetConfig;     

 if( g_parameter.config_flag == SS7_FALSE)
  {
   oam_transaction_Id[tr_opcode].transaction_Id = ((ScmHdr *)msg_buff)->trid;/*store oam trid */ 
   oam_transaction_Id[tr_opcode].operation      = ((ScmHdr *)msg_buff)->operation;/*store oam operation */
   oam_transaction_Id[tr_opcode].pegrfu      = ((ScmHdr *)msg_buff)->spare;/*store peg cmd indication */
  }
 switch( g_parameter.alarm_level )
   {
        case ALRM_LVL_CRIT:
             alarm_level = 0;
             break;
        case ALRM_LVL_MAJR:
             alarm_level = 1;
        case ALRM_LVL_MINR:
             alarm_level = 2;

        case ALRM_LVL_INFO:
        case ALRM_LVL_WARN:
             alarm_level = 3;
   }
 

 switch(opcode)
  {
     case OAM_SCM_MTP3_GEN_CFG:
       ssksGenConfig  = (scmSksGenConfig*)msg_buff;
       Length            = sizeof(sksGenSetConfig);
       NwstkGenSetConfig.sksGenCfgAlarmLevel = alarm_level;
       NwstkGenSetConfig.sksGenCfgTraceLevel = ssksGenConfig->sksGenCfgTraceLevel;
       NwstkGenSetConfig.sksGenCfgtraceOutput = ssksGenConfig->sksGenCfgtraceOutput;
       NwstkGenSetConfig.sksGenCfgtraceOnOff = ssksGenConfig->sksGenCfgtraceOnOff;
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'MTP3_GEN_CFG' 'alarmLvl: %d, traceLvl: %d, traceO/P: %d'", 
                  alarm_level, ssksGenConfig->sksGenCfgTraceLevel, ssksGenConfig->sksGenCfgtraceOutput);
       memcpy(cmd_buff, &NwstkGenSetConfig, Length);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_MTP3_GENCFG,
                        transaction_Id[SCM_NWSTK_MTP3_GENCFG], Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_MTP3_GENCFG], msg_buff);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

      case OAM_SCM_SCCP_GEN_CFG:

       ssksGenConfig  = (scmSksGenConfig*)msg_buff;
       NwstkGenSetConfig.sksGenCfgAlarmLevel = alarm_level;
       NwstkGenSetConfig.sksGenCfgTraceLevel = ssksGenConfig->sksGenCfgTraceLevel;
       NwstkGenSetConfig.sksGenCfgtraceOutput = ssksGenConfig->sksGenCfgtraceOutput;
       NwstkGenSetConfig.sksGenCfgtraceOnOff = ssksGenConfig->sksGenCfgtraceOnOff;
       Length            = sizeof(sksGenSetConfig);
       memcpy(cmd_buff, &NwstkGenSetConfig, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SCCP_GENCFG], msg_buff );
       SCM_printf(SCM_MAJOR,"SCM -> SCCP: 'SCCP_GEN_CFG'  'alarmLvl: %d, traceLvl: %d, traceO/P: %d'",
                  alarm_level, ssksGenConfig->sksGenCfgTraceLevel, ssksGenConfig->sksGenCfgtraceOutput);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_GENCFG,
                        transaction_Id[SCM_NWSTK_SCCP_GENCFG], Length);

       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

    case OAM_SCM_BSSAP_GEN_CFG:

       ssksGenConfig  = (scmSksGenConfig*)msg_buff;
       Length            = sizeof(sksGenSetConfig);
       NwstkGenSetConfig.sksGenCfgAlarmLevel = alarm_level;
       NwstkGenSetConfig.sksGenCfgTraceLevel = ssksGenConfig->sksGenCfgTraceLevel;
       NwstkGenSetConfig.sksGenCfgtraceOutput = ssksGenConfig->sksGenCfgtraceOutput;
       NwstkGenSetConfig.sksGenCfgtraceOnOff = ssksGenConfig->sksGenCfgtraceOnOff;
       SCM_printf(SCM_MAJOR,"alarm level: %d, traceLevel : %d, traceOutPut: %d, traceOnOff: %d", 
                  alarm_level, ssksGenConfig->sksGenCfgTraceLevel, ssksGenConfig->sksGenCfgtraceOutput, 
                  ssksGenConfig->sksGenCfgtraceOnOff);
       Length            = sizeof(sksGenSetConfig);
       memcpy(cmd_buff, &NwstkGenSetConfig, Length);
 
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_BSSAP_GENCFG], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_GENCFG,
                        transaction_Id[SCM_NWSTK_BSSAP_GENCFG], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
      
     case OAM_SCM_LINKSET_CONFIG:
      
       scmLinkSetConfig  = (OamScmLinkSetConfig*)msg_buff;
       NwstkLinkSetConfig.linkSetId = scmLinkSetConfig->linkSetId;
       g_parameter.linksetId = scmLinkSetConfig->linkSetId;
       NwstkLinkSetConfig.adjacentPointCode = scmLinkSetConfig->adjacentPointCode;
       NwstkLinkSetConfig.localPointCode  =  g_parameter.opc_value;
       NwstkLinkSetConfig.family = g_parameter.family;
       NwstkLinkSetConfig.networkIndicator = scmLinkSetConfig->networkIndicator;/*ni value*/
        
       Length  = sizeof(ScmNwstkLinkSetConfig);
       memcpy(cmd_buff, &NwstkLinkSetConfig, Length);

       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_LINKSET_ADD], msg_buff);
       
       if(operation == SCM_DELETE)
        {
          SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINKSET_DEL' ls: %d, apc: %d, opc: %d, family: %d, ni: %d ",
                     scmLinkSetConfig->linkSetId, scmLinkSetConfig->adjacentPointCode, g_parameter.opc_value,
                     g_parameter.family, scmLinkSetConfig->networkIndicator);
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_DEL,
                           transaction_Id[SCM_NWSTK_LINKSET_ADD], Length);
        }
       else
        { 
          SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINKSET_ADD' ls: %d, apc: %d, opc: %d, family: %d, ni: %d ",
                     scmLinkSetConfig->linkSetId, scmLinkSetConfig->adjacentPointCode, g_parameter.opc_value,
                     g_parameter.family, scmLinkSetConfig->networkIndicator);
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_ADD,
                           transaction_Id[SCM_NWSTK_LINKSET_ADD], Length);
        } 
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

  case OAM_SCM_LINK_CONFIG:
       scmLinkConfig  = (OamScmLinkConfig*)msg_buff;
       Length            = sizeof(ScmNwstkLinkConfig);
       if(g_parameter.slot_id == 3)    
        {
          if(scmLinkConfig->cardNum == 3)
            { 
                 NwstkLinkConfig.instanceID = 65524;
                 if( g_parameter.family  == ANSI_FAMILY)
                 {
                  NwstkLinkConfig.instanceID = 65525;
                 }
            }
          else
           if(scmLinkConfig->cardNum == 4) 
            {
              NwstkLinkConfig.instanceID = 20002;
            } 
           else
            {
             SCM_printf(SCM_CRITICAL," link config cmd failed: cause WRONG CARD NUM")
             g_parameter.config_cmd_resp = 0;
             if(g_parameter.config_flag == 0)
              {
               match_resp_opcode(((ScmHdr *)msg_buff)->opcode,  &resp_opcode);
               send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                                ((ScmHdr *)msg_buff)->spare, 
                        WRONG_CARDTYPE, NULL, resp_len, APP_ID_OAM);
              }
             return 0;
            }
         }  
        else  
          if(g_parameter.slot_id == 4)
           {
             if(scmLinkConfig->cardNum == 3)
              {
               NwstkLinkConfig.instanceID = 20002;
              }  
             else
              if( scmLinkConfig->cardNum == 4 )
               {
                NwstkLinkConfig.instanceID = 65524;
                if( g_parameter.family  == ANSI_FAMILY)
                 {
                  NwstkLinkConfig.instanceID = 65525;
                 }
               }
             else
              {
                SCM_printf(SCM_CRITICAL," link config cmd failed: cause WRONG CARD NUM")
               g_parameter.config_cmd_resp = 0;
               if(g_parameter.config_flag == 0)
                {
                 match_resp_opcode(((ScmHdr *)msg_buff)->opcode,  &resp_opcode);
                 send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                               ((ScmHdr *)msg_buff)->spare, 
                          WRONG_CARDTYPE, NULL, resp_len, APP_ID_OAM);
                }
               return 0;   
              } 
           }
          else
           {
            SCM_printf(SCM_CRITICAL,"LINK CONFIG CMD FAILURE : wrong slot id");
            if(g_parameter.config_flag == 0)
              {
               match_resp_opcode(((ScmHdr *)msg_buff)->opcode,  &resp_opcode);
               send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                              ((ScmHdr *)msg_buff)->spare, 
                        WRONG_CARDTYPE, NULL, resp_len, APP_ID_OAM);
              }
            return 0;
           }
               
       NwstkLinkConfig.linkId     = scmLinkConfig->linkId;
       NwstkLinkConfig.linkSetId  = scmLinkConfig->linkSetId;
   //    NwstkLinkConfig.trunkNum   = scmLinkConfig->trunkNum;
           SCM_printf(SCM_INFO,"DB QUERY FOR STREAM TIME SLOT for TrkNum=%d,TrkTs=%d", scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
       dbSts = GetDstStreamTsConfigDataWithTrunkAndTimeslot( &timeslot, scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
        
       if(dbSts == 0)
        {
           g_linkConfigValue.link_value = NwstkLinkConfig.linkId;
           g_linkConfigValue.linkSetId  = NwstkLinkConfig.linkSetId; 
           g_linkConfigValue.instaceId  = NwstkLinkConfig.instanceID; 
         if((timeslot%2) != 0 )
          {
           SCM_printf(SCM_MAJOR," Link cmd failure: cause: 'ODD VALUE OF TIMESLOT i.e.: %d IN DB FOR DEST STREAM MAPPING'", timeslot);
           if(g_parameter.config_flag == 0)
              {
               match_resp_opcode(((ScmHdr *)msg_buff)->opcode,  &resp_opcode);
               send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                               ((ScmHdr *)msg_buff)->spare,  
                        ODD_TSVALUE_IN_STRMMAPTBL, NULL, resp_len, APP_ID_OAM);
              }
           return 0;
          }
      // NOT  REQUIRED  timeslot = timeslot * 2;/* temporary fix for mcc dest stream time slot */ 
         NwstkLinkConfig.timeSlot   = timeslot;
         NwstkLinkConfig.cardNum    = scmLinkConfig->cardNum;
         NwstkLinkConfig.crcFlag    = scmLinkConfig->crcFlag;
         memcpy(cmd_buff, &NwstkLinkConfig, Length);
         if(g_parameter.peer_link_del != 1)
           start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_LINK_ADD], msg_buff);
         if(operation == SCM_DELETE)
          {
           ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_GET,  0,
                                                 scmLinkConfig->linkId,
                                                 scmLinkConfig->linkSetId,
                                                 &cardFlag, 0);
           if(ret_val == 1)
           {
            if((cardFlag == PEER) && (xxx_client_sockfd[ENT_PEER_SCM] > 0)
                && ( g_parameter.peer_link_del  == 0) && (g_parameter.nwstk_standby_respFlag == 0)) 
            {
               g_parameter.peer_link_del = 1;   
               SCM_printf(SCM_INFO,"LINK_DEL COMMAND IS FOR PEER : sent to peer");
              ((OamScmLinkConfig*)msg_buff)->scmhdr.appid   = APP_ID_PEER_SCM;

                                                                     /*opcode changed for
                                                                       distinguishing scm
                                                                       update cmd from oam
                                                                       cmd*/
               SCM_printf(SCM_DEBUG,"((OamScmLinkConfig*)msg_buff)->scmhdr.len: %d", scmLinkConfig->scmhdr.len);

              ret_val = scm_dispatch_buffer(msg_buff, APP_ID_PEER_SCM, scmLinkConfig->scmhdr.len);
            }
            else
            {
              SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINK_DEL:' ln: %d, ls: %d, strmTs: %d, instance: %d",
                         scmLinkConfig->linkId, scmLinkConfig->linkSetId, timeslot,NwstkLinkConfig.instanceID);
              form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_DEL,
                                transaction_Id[SCM_NWSTK_LINK_ADD], Length);
              ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
             }
           } 
           else
           {
             stop_timer(TIMER_NWSTK);
             SCM_printf(SCM_CRITICAL," LINK ENTRY NOT FOUND IN SCM LINKHASH TABLE");
             send_resp_to_oam(  SCM_OAM_LINK_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation,
                         ((ScmHdr *)msg_buff)->trid, 0, LINKCODE_ENTRY_NOTFOUND, NULL, resp_len, APP_ID_OAM );
             ret_val = 0;
           }  
 
          }
         else
          { 
           SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINK_ADD:' ln: %d, ls: %d, strmTs: %d, instance: %d",
                      scmLinkConfig->linkId, scmLinkConfig->linkSetId, timeslot,NwstkLinkConfig.instanceID);
           form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_ADD,
                          transaction_Id[SCM_NWSTK_LINK_ADD], Length);
            ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
          }   
         /* here take decision on the bases of card no msg goes to self nwstk or peer*/
                 break;
        }
        else
         {
           SCM_printf(SCM_MAJOR,"DB QUERY FOR STREAM TIME SLOT FAILURE TrkNum=%d,TrkTs=%d", scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
           SCM_printf(SCM_MAJOR,"LINK CONFIG COMMAND FAILURE");
           if(g_parameter.config_flag == 0)
              {
               match_resp_opcode(((ScmHdr *)msg_buff)->opcode,  &resp_opcode);
               send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                        ((ScmHdr *)msg_buff)->spare, 
                        ODD_TSVALUE_IN_STRMMAPTBL, NULL, resp_len, APP_ID_OAM);
              }
           return 0;
         }  
       
  case OAM_SCM_SS7ROUTE_CONFIG:

       scmSs7RouteConfig = (OamScmSs7RouteConfig*)msg_buff;
       if(scmSs7RouteConfig->style > 3)
        {
         SCM_printf(SCM_MAJOR,"WRONG ROUTE STYLE VALUE");
         g_parameter.config_cmd_resp = 0;
         if(g_parameter.config_flag == 0)
              {
               match_resp_opcode(((ScmHdr *)msg_buff)->opcode,  &resp_opcode);
               send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid , 0, 
                        WRONG_ROUTESTYLE_VAL, NULL, resp_len, APP_ID_OAM);
              }
         return 0;
        }  
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SS7ROUTE_ADD], msg_buff);
       if(scmSs7RouteConfig->sstTestOn == 1)
        {
         Length            = sizeof(ScmNwstkSccpCssnConfig);
         NwstkSccpCssnConfig.sccpConfigssn  =  scmSs7RouteConfig->lssn;
         NwstkSccpCssnConfig.sccpConfigpc   = g_parameter.opc_value;
         NwstkSccpCssnConfig.sccpConfigni   = scmSs7RouteConfig->networkIndicator;
         NwstkSccpCssnConfig.sccpConfigcssn = scmSs7RouteConfig->rssn;
         NwstkSccpCssnConfig.sccpConfigcpc  = scmSs7RouteConfig->destinationPointCode;
         memcpy(cmd_buff, &NwstkSccpCssnConfig, Length);
         if(operation == SCM_DELETE)
          {
           SCM_printf(SCM_MAJOR,"SCM -> MTP3 'CSSN_DEL:' lssn: %d, opc: %d, ni: %d, rssn: %d, dpc: %d",
                      scmSs7RouteConfig->lssn, g_parameter.opc_value, scmSs7RouteConfig->networkIndicator, 
                      scmSs7RouteConfig->rssn, scmSs7RouteConfig->destinationPointCode);         
           form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_CSSN_DEL,
                              transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD], Length );
          }
         else
          {
           SCM_printf(SCM_MAJOR,"SCM -> MTP3 'CSSN_ADD:' lssn: %d, opc: %d, ni: %d, rssn: %d, dpc: %d",
                      scmSs7RouteConfig->lssn, g_parameter.opc_value, scmSs7RouteConfig->networkIndicator, 
                      scmSs7RouteConfig->rssn, scmSs7RouteConfig->destinationPointCode);         
           form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_CSSN_ADD,
                              transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD], Length );
          }
         ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
         timer_info[TIMER_NWSTK].no_of_resp       = 2;
        }
       Length            = sizeof(ScmNwstkSs7RouteConfig);
       NwstkSs7RouteConfig.destinationPointCode = scmSs7RouteConfig->destinationPointCode;
       NwstkSs7RouteConfig.linkSetId            = scmSs7RouteConfig->linkSetId;
       NwstkSs7RouteConfig.direction            = REMOTE_ROUTE;
       NwstkSs7RouteConfig.family               = g_parameter.family;
       NwstkSs7RouteConfig.style                = scmSs7RouteConfig->style;
       NwstkSs7RouteConfig.sio                  = scmSs7RouteConfig->sio;
       NwstkSs7RouteConfig.rssn                 = scmSs7RouteConfig->rssn;
       NwstkSs7RouteConfig.lssn                 = scmSs7RouteConfig->lssn;
       NwstkSs7RouteConfig.sstTestOn            = scmSs7RouteConfig->sstTestOn;
       NwstkSs7RouteConfig.networkIndicator     = scmSs7RouteConfig->networkIndicator;  
       memcpy(cmd_buff, &NwstkSs7RouteConfig, Length);
       if(operation == SCM_DELETE)
        {
         SCM_printf(SCM_MAJOR,"SCM -> MTP3 'SS7_ROUTE_DEL:' lssn: %d, opc: %d, ni: %d, rssn: %d, dpc: %d",
                    scmSs7RouteConfig->lssn, g_parameter.opc_value, scmSs7RouteConfig->networkIndicator, 
                    scmSs7RouteConfig->rssn, scmSs7RouteConfig->destinationPointCode);         
         form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_DEL,
                          transaction_Id[SCM_NWSTK_SS7ROUTE_ADD], Length);
        }
       else
        {   
         SCM_printf(SCM_MAJOR,"SCM -> MTP3 'SS7_ROUTE_ADD:' lssn: %d, opc: %d, ni: %d, rssn: %d, dpc: %d",
                    scmSs7RouteConfig->lssn, g_parameter.opc_value, scmSs7RouteConfig->networkIndicator, 
                    scmSs7RouteConfig->rssn, scmSs7RouteConfig->destinationPointCode);         
         form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SS7ROUTE_ADD,
                          transaction_Id[SCM_NWSTK_SS7ROUTE_ADD], Length);
        }
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
 
       break;

/*  case OAM_SCM_SS7ROUTE_TESTON_CONFIG:
       scmSs7RouteTestOnConfig  = (OamScmSs7RouteTestOnConfig*)msg_buff;
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD], msg_buff);
         Length            = sizeof(ScmNwstkSccpCssnConfig);
         NwstkSccpCssnConfig.sccpConfigssn = scmSs7RouteTestOnConfig->lssn;
         NwstkSccpCssnConfig.sccpConfigpc   = g_parameter.opc_value;
         NwstkSccpCssnConfig.sccpConfigni   = scmSs7RouteTestOnConfig->networkIndicator;
         NwstkSccpCssnConfig.sccpConfigcssn   = scmSs7RouteTestOnConfig->rssn;
         NwstkSccpCssnConfig.sccpConfigcpc   = scmSs7RouteTestOnConfig->destinationPointCode;
         memcpy(cmd_buff, &NwstkSccpCssnConfig, Length);
         if(scmSs7RouteTestOnConfig.testOn == 0)
          {
           form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_CSSN_DEL,
                              transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD], Length );
          }
         else
          {
           form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_CSSN_ADD,
                              transaction_Id[SCM_NWSTK_SCCP_CSSN_DEL], Length );
          }
         ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;*/


  case OAM_SCM_INTERFACE_CONFIG:

       scmInterfaceConfig  = (OamScmInterfaceConfig*)msg_buff;
       if(scmInterfaceConfig->interfaceType != IF_TYP_BSSAP)
         {
          return 0;
         }
       Length            = sizeof(ScmNwstkBssapcfgConfig);
       NwstkBssapcfgConfig.interfaceType = scmInterfaceConfig->interfaceType;
       NwstkBssapcfgConfig.interfaceId   = scmInterfaceConfig->interfaceId;
       NwstkBssapcfgConfig.lpc           = g_parameter.opc_value;
       NwstkBssapcfgConfig.rpc           = scmInterfaceConfig->pointCode;
       memcpy(cmd_buff, &NwstkBssapcfgConfig, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_BSSAP_CFG_ADD], msg_buff);
       if(operation == SCM_DELETE)
        {
         SCM_printf(SCM_MAJOR,"SCM -> MTP3 'INTERFACE_DEL:' interfaceType: %d, interfaceId: %d opc: %d, dpc: %d",
                  scmInterfaceConfig->interfaceType, scmInterfaceConfig->interfaceId, g_parameter.opc_value, 
                  scmInterfaceConfig->pointCode);      
         form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_CFG_DEL,
                           transaction_Id[SCM_NWSTK_BSSAP_CFG_ADD], Length);
         
        }
       else
        {
         SCM_printf(SCM_MAJOR,"SCM -> MTP3 'INTERFACE_ADD:' interfaceType: %d, interfaceId: %d opc: %d, dpc: %d",
                  scmInterfaceConfig->interfaceType, scmInterfaceConfig->interfaceId, g_parameter.opc_value, 
                  scmInterfaceConfig->pointCode);      
         form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_CFG_ADD,
                           transaction_Id[SCM_NWSTK_BSSAP_CFG_ADD], Length);
        }   
       /* here take decision on the bases of card no msg goes to self nwstk or pe
er*/
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
  
  /*case OAM_SCM_SS7ROUTE_TESTON_CONFIG:
  case OAM_SCM_LINK_CRCFLAG_CONFIG:*/

  case OAM_SCM_TRUNK_CIC_CONFIG:

       scmTrunkCicConfig  = (OamScmTrunkCicConfig*)msg_buff;
       if(scmTrunkCicConfig->interfaceType != IF_TYP_BSSAP)
         {
          return 0;
         }
       Length            = sizeof(ScmNwstkBssapCicConfig);

       NwstkBssapCicConfig.interfaceType = scmTrunkCicConfig->interfaceType;
       NwstkBssapCicConfig.interfaceId   = scmTrunkCicConfig->interfaceId;
       NwstkBssapCicConfig.startCic      = scmTrunkCicConfig->startCic;
       NwstkBssapCicConfig.endCic        = scmTrunkCicConfig->endCic;
       memcpy(cmd_buff, &NwstkBssapCicConfig, Length);

       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_BSSAP_CIC_ADD], msg_buff);
       if(operation == SCM_DELETE)
        {
         SCM_printf(SCM_MAJOR,"SCM -> MTP3 'TRUNK_CIC_DEL:' interfaceType: %d, iFId: %d startCic: %d, endCic: %d",
                    scmTrunkCicConfig->interfaceType, scmTrunkCicConfig->interfaceId, scmTrunkCicConfig->startCic, 
                    scmTrunkCicConfig->endCic);
         form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_CIC_DEL,
                          transaction_Id[SCM_NWSTK_BSSAP_CIC_ADD], Length);
        }
       else
        {
         SCM_printf(SCM_MAJOR,"SCM -> MTP3 'TRUNK_CIC_ADD:' interfaceType: %d, iFId: %d startCic: %d, endCic: %d",
                    scmTrunkCicConfig->interfaceType, scmTrunkCicConfig->interfaceId, scmTrunkCicConfig->startCic, 
                    scmTrunkCicConfig->endCic);
         form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_CIC_ADD,
                          transaction_Id[SCM_NWSTK_BSSAP_CIC_ADD], Length);
        }  
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

  case OAM_SCM_LSSN_CONFIG:
       scmSccpLssnConfig  = (OamScmSccpLssnConfig*)msg_buff;
       Length            = sizeof(ScmNwstkSccpLssnConfig);
       NwstkSccpLssnConfig.sccpConfiglssn = scmSccpLssnConfig->sccpConfiglssn;
       NwstkSccpLssnConfig.sccpConfigpc   = g_parameter.opc_value;
       NwstkSccpLssnConfig.sccpConfigni   = scmSccpLssnConfig->sccpConfigni;
       memcpy(cmd_buff, &NwstkSccpLssnConfig, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SCCP_LSSN_ADD], msg_buff);
       if(operation == SCM_DELETE)
        {
          SCM_printf(SCM_MAJOR,"processing cmd : OAM_SCM_LSSNDEL_CONFIG:");
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_LSSN_DEL,
                             transaction_Id[SCM_NWSTK_SCCP_LSSN_ADD], Length );
        }
       else
        {
          SCM_printf(SCM_MAJOR,"processing cmd : OAM_SCM_LSSNADD_CONFIG:");
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_LSSN_ADD,
                             transaction_Id[SCM_NWSTK_SCCP_LSSN_ADD], Length );
        }  
       SCM_printf(SCM_INFO,"lssn: %d, opc: %d, nwId: %d",
                   scmSccpLssnConfig->sccpConfiglssn, g_parameter.opc_value, scmSccpLssnConfig->sccpConfigni);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

  case OAM_SCM_RSSN_CONFIG:
       scmSccpRssnConfig  = (OamScmSccpRssnConfig*)msg_buff;
       Length            = sizeof(ScmNwstkSccpRssnConfig);
       NwstkSccpRssnConfig.sccpConfigrssn = scmSccpRssnConfig->sccpConfigrssn;
       NwstkSccpRssnConfig.sccpConfigpc   = scmSccpRssnConfig->sccpConfigpc;
       NwstkSccpRssnConfig.sccpConfigni   = scmSccpRssnConfig->sccpConfigni;
       memcpy(cmd_buff, &NwstkSccpRssnConfig, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SCCP_RSSN_ADD], msg_buff);
       if(operation == SCM_DELETE)
        {
          SCM_printf(SCM_MAJOR,"processing cmd : OAM_SCM_RSSNDEL_CONFIG:");
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_RSSN_DEL,
                             transaction_Id[SCM_NWSTK_SCCP_RSSN_ADD], Length );
        }
       else
        {
          SCM_printf(SCM_MAJOR,"processing cmd : OAM_SCM_RSSNADD_CONFIG:");
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_RSSN_ADD,
                             transaction_Id[SCM_NWSTK_SCCP_RSSN_ADD], Length );
        }  
       SCM_printf(SCM_INFO,"rssn: %d, dpc: %d, nwId: %d",
                  scmSccpRssnConfig->sccpConfigrssn, scmSccpRssnConfig->sccpConfigpc, scmSccpRssnConfig->sccpConfigni);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;


  case OAM_SCM_LINKSET_STATUS_GET:
       scmLinkSetStatusGet  = (ScmOamLinkSetStatusResponse*)msg_buff;
       Length            = sizeof(ScmNwstkLinkSetStatus);
        
       NwstkLinkSetStatus.linkSetId = scmLinkSetStatusGet->linkSetId; 
       NwstkLinkSetStatus.status    = scmLinkSetStatusGet->status; 
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINKSET_STATUS_GET::' linksetId: %d", scmLinkSetStatusGet->linkSetId);
       memcpy(cmd_buff, &NwstkLinkSetStatus, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_LINKSET_STATUS_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_STATUS_GET,
                             transaction_Id[SCM_NWSTK_LINKSET_STATUS_GET], Length );
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
        
  case OAM_SCM_LINK_STATUS_GET:
       scmLinkStatusGet  = (ScmOamLinkStatusResponse*)msg_buff;
       Length            = sizeof(ScmNwstkLinkStatus);
        
       NwstkLinkStatus.linkId = scmLinkStatusGet->linkId; 
       NwstkLinkStatus.linkSetId = scmLinkStatusGet->linkSetId; 
       NwstkLinkStatus.status    = scmLinkStatusGet->status; 
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINK_STATUS_GET::' linkId: %d, linksetId: %d",
                             scmLinkStatusGet->linkSetId, scmLinkStatusGet->status);
       memcpy(cmd_buff, &NwstkLinkStatus, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_LINK_STATUS_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_STATUS_GET,
                             transaction_Id[SCM_NWSTK_LINK_STATUS_GET], Length );
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
  case OAM_SCM_ROUTE_STATUS_GET:
       scmRouteStatusGet  = (ScmOamRouteStatusResponse*)msg_buff;
       Length            = sizeof(ScmNwstkRouteStatus);
        
       NwstkRouteStatus.destinationPointCode = scmRouteStatusGet->destinationPointCode; 
       NwstkRouteStatus.family = g_parameter.family; 
       NwstkRouteStatus.networkIndicator = scmRouteStatusGet->networkIndicator; 
       NwstkRouteStatus.status = scmRouteStatusGet->status; 
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'ROUTE_STATUS_GET:' dpc: %d, family: %d, nwId: %d,", 
                  scmRouteStatusGet->destinationPointCode, g_parameter.family, 
                  scmRouteStatusGet->networkIndicator);           
       memcpy(cmd_buff, &NwstkRouteStatus, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_ROUTE_STATUS_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_ROUTE_STATUS_GET,
                             transaction_Id[SCM_NWSTK_ROUTE_STATUS_GET], Length );
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break; 

  case OAM_SCM_SSN_STATUS_GET:
       scmSsnStatusGet  = (OamScmSsnStatusGet*)msg_buff;
       Length            = sizeof(ScmNwstkSsnStatus);
        
       NwstkSsnStatus.destinationPointCode = scmSsnStatusGet->destinationPointCode; 
       NwstkSsnStatus.networkIndicator = scmSsnStatusGet->networkIndicator; 
       NwstkSsnStatus.ssn = scmSsnStatusGet->ssn; 
       NwstkSsnStatus.status = scmSsnStatusGet->status; 
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'SSN_STATUS_GET:' dpc: %d, nwId: %d, ssn: %d, status: %d", 
                  scmSsnStatusGet->destinationPointCode, scmSsnStatusGet->networkIndicator);   
       memcpy(cmd_buff, &NwstkSsnStatus, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_ROUTE_STATUS_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_ROUTE_STATUS_GET,
                             transaction_Id[SCM_NWSTK_ROUTE_STATUS_GET], Length );
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break; 
  case OAM_SCM_CSSN_CONFIG:
       SCM_printf(SCM_INFO,"processing cmd : OAM_SCM_CSSN_CONFIG:");
       scmSccpCssnConfig  = (OamScmSccpCssnConfig*)msg_buff;
       Length            = sizeof(ScmNwstkSccpCssnConfig);
       NwstkSccpCssnConfig.sccpConfigssn = scmSccpCssnConfig->sccpConfigssn;
       NwstkSccpCssnConfig.sccpConfigpc   = g_parameter.opc_value;
       NwstkSccpCssnConfig.sccpConfigni   = scmSccpCssnConfig->sccpConfigni;
       NwstkSccpCssnConfig.sccpConfigcssn   = scmSccpCssnConfig->sccpConfigcssn;
       NwstkSccpCssnConfig.sccpConfigcpc   = scmSccpCssnConfig->sccpConfigcpc;
       SCM_printf(SCM_INFO,"ssn: %d, opc: %d, nwId: %d, cssn: %d, dpc: %d", 
                  scmSccpCssnConfig->sccpConfigssn, g_parameter.opc_value, 
                  scmSccpCssnConfig->sccpConfigni,scmSccpCssnConfig->sccpConfigcssn,
                  scmSccpCssnConfig->sccpConfigcpc);  
       memcpy(cmd_buff, &NwstkSccpCssnConfig, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD], msg_buff);
       if(operation == SCM_DELETE)
        {
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_CSSN_DEL,
                             transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD], Length );
        }
       else
        {
          form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_CSSN_ADD,
                             transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD], Length );
        }  
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
    
  case OAM_SCM_SCCP_TIMER_CONFIG:
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'SCCP_TIMER_MODIFY'");

       scmSccpTimerConfig  = (OamScmSccpTimerConfig*)msg_buff;
       Length            = sizeof(ScmNwstkSccpTimerModify);

       NwstkSccpTimerModify.sccpTimerstatInfo = scmSccpTimerConfig->sccpTimerstatInfo;
       NwstkSccpTimerModify.sccpTimercoordChg = scmSccpTimerConfig->sccpTimercoordChg;
       NwstkSccpTimerModify.sccpTimerig0reSST = scmSccpTimerConfig->sccpTimerig0reSST;
       NwstkSccpTimerModify.sccpTimerrtgStatInfor = scmSccpTimerConfig->sccpTimerrtgStatInfor;
       NwstkSccpTimerModify.sccpTimerconn = scmSccpTimerConfig->sccpTimerconn;
       NwstkSccpTimerModify.sccpTimerrelease = scmSccpTimerConfig->sccpTimerrelease;
       NwstkSccpTimerModify.sccpTimerreset = scmSccpTimerConfig->sccpTimerreset;
       NwstkSccpTimerModify.sccpTimerias = scmSccpTimerConfig->sccpTimerias;
       NwstkSccpTimerModify.sccpTimeriar = scmSccpTimerConfig->sccpTimeriar;
       NwstkSccpTimerModify.sccpTimerguard = scmSccpTimerConfig->sccpTimerguard;  
       NwstkSccpTimerModify.sccpTimerreassembly = scmSccpTimerConfig->sccpTimerreassembly; 
       NwstkSccpTimerModify.sccpTimerinterval = scmSccpTimerConfig->sccpTimerinterval;
       NwstkSccpTimerModify.sccpTimerrepeatRelease = scmSccpTimerConfig->sccpTimerrepeatRelease;

       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SCCP_TIMER_MODIFY], msg_buff);
       memcpy(cmd_buff, &NwstkSccpTimerModify, Length);
        form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_TIMER_MODIFY,
                           transaction_Id[SCM_NWSTK_SCCP_TIMER_MODIFY], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
  
  case OAM_SCM_BSSAP_TIMER_CONFIG:

       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'BSSAP_TIMER_MODIFY'");
       scmBssapTimerConfig  = (OamScmBssapTimerConfig*)msg_buff;
       NwstkBssapTimerModify.bssapTimerT1 = scmBssapTimerConfig->bssapTimerT1;
       NwstkBssapTimerModify.bssapTimerT4 = scmBssapTimerConfig->bssapTimerT4;
       /*NwstkBssapTimerModify.bssapTimerT7 = scmBssapTimerConfig->bssapTimerT7;
       NwstkBssapTimerModify.bssapTimerT8 = scmBssapTimerConfig->bssapTimerT8;
       hand over related timer which are obsolete in new releases*/
       NwstkBssapTimerModify.bssapTimerT10 = scmBssapTimerConfig->bssapTimerT10;
       NwstkBssapTimerModify.bssapTimerT11 = scmBssapTimerConfig->bssapTimerT11;
       NwstkBssapTimerModify.bssapTimerT13 = scmBssapTimerConfig->bssapTimerT13;
       NwstkBssapTimerModify.bssapTimerT17 = scmBssapTimerConfig->bssapTimerT17;
       NwstkBssapTimerModify.bssapTimerT18 = scmBssapTimerConfig->bssapTimerT18;
       NwstkBssapTimerModify.bssapTimerT19 = scmBssapTimerConfig->bssapTimerT19;
       NwstkBssapTimerModify.bssapTimerT20 = scmBssapTimerConfig->bssapTimerT20;

       Length            = sizeof(ScmNwstkBssapTimerModify);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_BSSAP_TIMER_MODIFY], msg_buff);
       memcpy(cmd_buff, &NwstkBssapTimerModify, Length);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_TIMER_MODIFY,
                        transaction_Id[SCM_NWSTK_BSSAP_TIMER_MODIFY], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

  
  case OAM_SCM_MTP3_TIMER_CONFIG: 
 
#define FILL_TMR_VAL(A,C) \
        NwstkMtp3TimerModify.A = scmMtp3TimerConfig->C; 

       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'MTP3_TIMER_MODIFY'");
       scmMtp3TimerConfig  = (OamScmMtp3TimerConfig*)msg_buff;

       FILL_TMR_VAL(mtp3TimerT1,mtp3TimerT1);
       FILL_TMR_VAL(mtp3TimerT2,mtp3TimerT2);
       FILL_TMR_VAL(mtp3TimerT3,mtp3TimerT3);
       FILL_TMR_VAL(mtp3TimerT4,mtp3TimerT4);
       FILL_TMR_VAL(mtp3TimerT5,mtp3TimerT5);
       FILL_TMR_VAL(mtp3TimerT6,mtp3TimerT6);
       FILL_TMR_VAL(mtp3TimerT7,mtp3TimerT7);
       FILL_TMR_VAL(mtp3TimerT8,mtp3TimerT8);
       //FILL_TMR_VAL(mtp3TimerT9,mtp3TimerT9);
       FILL_TMR_VAL(mtp3TimerT10,mtp3TimerT10);
       FILL_TMR_VAL(mtp3TimerT11,mtp3TimerT11);
       FILL_TMR_VAL(mtp3TimerT12,mtp3TimerT12);
       FILL_TMR_VAL(mtp3TimerT13,mtp3TimerT13);
       FILL_TMR_VAL(mtp3TimerT14,mtp3TimerT14);
       FILL_TMR_VAL(mtp3TimerT15,mtp3TimerT15);
       FILL_TMR_VAL(mtp3TimerT16,mtp3TimerT16);
       FILL_TMR_VAL(mtp3TimerT17,mtp3TimerT17);
       //FILL_TMR_VAL(mtp3TimerT19,mtp3TimerT19);
       FILL_TMR_VAL(mtp3TimerT20,mtp3TimerT22);
       FILL_TMR_VAL(mtp3TimerT21,mtp3TimerT23);
       FILL_TMR_VAL(mtp3TimerT22,mtp3TimerT18);
       FILL_TMR_VAL(mtp3TimerT23,mtp3TimerT18);
       FILL_TMR_VAL(mtp3TimerT24,mtp3TimerT20);
       /* FILL_TMR_VAL(mtp3TimerT25,mtp3TimerT25);
       FILL_TMR_VAL(mtp3TimerT26,mtp3TimerT26);
       FILL_TMR_VAL(mtp3TimerT27,mtp3TimerT27);
       FILL_TMR_VAL(mtp3TimerT28,mtp3TimerT21);
       FILL_TMR_VAL(mtp3TimerT29,mtp3TimerT29);
       FILL_TMR_VAL(mtp3TimerT30,mtp3TimerT30);
       FILL_TMR_VAL(mtp3TimerT31,mtp3TimerT31);
       FILL_TMR_VAL(mtp3TimerT32,mtp3TimerT32);
       FILL_TMR_VAL(mtp3TimerT33,mtp3TimerT33);
       FILL_TMR_VAL(mtp3TimerT34,mtp3TimerT34);*/
#undef FILL_TMR_VAL

       Length            = sizeof(ScmNwstkMtp3TimerModify);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_MTP3_TIMER_MODIFY], msg_buff);
       memcpy(cmd_buff, &NwstkMtp3TimerModify, Length);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_MTP3_TIMER_MODIFY,
                        transaction_Id[SCM_NWSTK_MTP3_TIMER_MODIFY], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

  
  case OAM_SCM_LINKSET_ADMIN_CONFIG:
       scmLinkSetAdminState = (OamScmLinkSetAdminState*)msg_buff;

       NwstkLinkSetAdminStateModify.linkSetId  = scmLinkSetAdminState->linkSetId;  
       NwstkLinkSetAdminStateModify.adminState  = scmLinkSetAdminState->adminState;  
       g_parameter.linksetId         = scmLinkSetAdminState->linkSetId;
       g_parameter.linkset_admingSts = scmLinkSetAdminState->adminState;
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LS_ADMIN_CONFIG' linkSetId: %d, adminState: %d,",
                  scmLinkSetAdminState->linkSetId, scmLinkSetAdminState->adminState);
       ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_GET,scmLinkSetAdminState->linkSetId, 0);
       if(ret_val == 1)
        {
         Length = sizeof(ScmNwstkLinkSetAdminStateModify);
         memcpy(cmd_buff, &NwstkLinkSetAdminStateModify, Length);
         start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY], msg_buff);
         form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY,
                         transaction_Id[SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY], Length);
         ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
        } 
       else
        {
         SCM_printf(SCM_CRITICAL," LINKSET ENTRY NOT FOUND IN SCM LINKSET HASH TABLE");
         send_resp_to_oam(  SCM_OAM_LINKSET_ADMIN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation,
                         ((ScmHdr *)msg_buff)->trid, 0, LINKSETNOT_EXIST, NULL, resp_len, APP_ID_OAM );
        }
       break;   
  
  case OAM_SCM_LINK_ADMIN_CONFIG:
 
       scmLinkAdminState = (OamScmLinkAdminState*)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LN_ADMIN_CONFIG'.. ln: %d, ls: %d, adminState: %d,",
                     scmLinkAdminState->linkId, scmLinkAdminState->linkSetId,
                     scmLinkAdminState->adminState);
       NwstkLinkAdminStateModify.linkId = scmLinkAdminState->linkId;
       NwstkLinkAdminStateModify.linkSetId = scmLinkAdminState->linkSetId;
       NwstkLinkAdminStateModify.adminState = scmLinkAdminState->adminState;
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


       ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_GET,  0,
                                                 scmLinkAdminState->linkId,
                                                 scmLinkAdminState->linkSetId,
                                                 &cardFlag, scmLinkAdminState->adminState);
      if(ret_val == 1)
       {
          g_parameter.link_activated_flag = 1;
          if(cardFlag == SELF )
           {
             Length  =  sizeof(ScmNwstkLinkAdminStateModify);
             memcpy(cmd_buff, &NwstkLinkAdminStateModify, Length);
             form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_ADMIN_STATE_MODIFY,
                               transaction_Id[SCM_NWSTK_LINK_ADMIN_STATE_MODIFY], Length);
             start_timer ( TIMER_NWSTK, APP_ID_NWSTK, 
                           transaction_Id[SCM_NWSTK_LINK_ADMIN_STATE_MODIFY], msg_buff);
             ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
           } 
          else 
           if((cardFlag == CARD_LINK_UP) && (scmLinkAdminState->adminState == 1))
           {
             send_resp_to_oam(  SCM_OAM_LINK_ADMIN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation,
                              ((ScmHdr *)msg_buff)->trid , 0, NO_ERROR, NULL, resp_len, APP_ID_OAM );
             ret_val = 1; 
           }
          else
           {  
            Length            = sizeof(OamScmLinkAdminState);
            if((xxx_client_sockfd[ENT_PEER_SCM] > 0) && (g_parameter.nwstk_cfgIndFromPeerCard  ==  1))
             { 
              SCM_printf(SCM_INFO,"LINK ACTIVATION COMMAND IS FOR PEER : sent to peer");
              ((OamScmLinkAdminState*)msg_buff)->scmhdr.appid   = APP_ID_PEER_SCM;
              ((OamScmLinkAdminState*)msg_buff)->scmhdr.opcode  = SCM_NWSTK_LINK_ADMIN_STATE_MODIFY;

                                                                     /*opcode changed for
                                                                       distinguishing scm
                                                                       update cmd from oam
                                                                       cmd*/  

              ret_val = scm_dispatch_buffer(msg_buff, APP_ID_PEER_SCM, Length);
              send_resp_to_oam(  SCM_OAM_LINK_ADMIN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation,
                              ((ScmHdr *)msg_buff)->trid , 0, NO_ERROR, NULL, resp_len, APP_ID_OAM );
             /* here i am assuming that nwstk wont nack for timer modify */ 
             g_linkConfigValue.link_value = NwstkLinkAdminStateModify.linkId;
             g_linkConfigValue.linkSetId  = NwstkLinkAdminStateModify.linkSetId; 
             g_linkConfigValue.card_flag  = cardFlag;
             g_linkConfigValue.admin_state  = NwstkLinkAdminStateModify.adminState;
             memcpy(&g_linkConfigValue.scmLinkAdminState, scmLinkAdminState, sizeof(OamScmLinkAdminState));
             ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_MODIFY,  0,
                                                 scmLinkAdminState->linkId, 
                                                 scmLinkAdminState->linkSetId, 
                                                 &cardFlag,
                                                 scmLinkAdminState->adminState);



             }
            else
            {
             SCM_printf(SCM_INFO,"PEER CARD SCM NOT PRESENT: entry is stored in SCM Local DB");
             g_linkConfigValue.link_value = NwstkLinkAdminStateModify.linkId;
             g_linkConfigValue.linkSetId  = NwstkLinkAdminStateModify.linkSetId; 
             g_linkConfigValue.card_flag  = cardFlag;
             g_linkConfigValue.admin_state  = NwstkLinkAdminStateModify.adminState;
             memcpy(&g_linkConfigValue.scmLinkAdminState, scmLinkAdminState, sizeof(OamScmLinkAdminState));
             ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_MODIFY,  0,
                                                 scmLinkAdminState->linkId, 
                                                 scmLinkAdminState->linkSetId, 
                                                 &cardFlag,
                                                 scmLinkAdminState->adminState);

             send_resp_to_oam(  SCM_OAM_LINK_ADMIN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation,
                              ((ScmHdr *)msg_buff)->trid , 0, NO_ERROR, NULL, resp_len, APP_ID_OAM );
             ret_val = 1; 
 
            }
           }
         if(ret_val != 0)
          {
           g_linkConfigValue.link_value = NwstkLinkAdminStateModify.linkId;
           g_linkConfigValue.linkSetId  = NwstkLinkAdminStateModify.linkSetId; 
           g_linkConfigValue.card_flag  = cardFlag;
           g_linkConfigValue.admin_state  = NwstkLinkAdminStateModify.adminState;
           memcpy(&g_linkConfigValue.scmLinkAdminState, scmLinkAdminState, sizeof(OamScmLinkAdminState));
          }
        }
       else
       {
        SCM_printf(SCM_CRITICAL," LINK ENTRY NOT FOUND IN SCM LINKHASH TABLE");
        send_resp_to_oam(  SCM_OAM_LINK_ADMIN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation,
                         ((ScmHdr *)msg_buff)->trid, 0, LINKCODE_ENTRY_NOTFOUND, NULL, resp_len, APP_ID_OAM );
        ret_val = 0; 
       }  
         break;

  case OAM_SCM_SS7ROUTE_ADMIN_CONFIG:
       scmSs7RouteAdminState = (OamScmSs7RouteAdminState*)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'ROUTE_ADMIN_CONFIG' linkSetId: %d, ssn: %d,",
                  scmSs7RouteAdminState->linkSetId,scmSs7RouteAdminState->ssn);
       NwstkSs7RouteAdminStateModify.destinationPointCode = scmSs7RouteAdminState->destinationPointCode;
       NwstkSs7RouteAdminStateModify.linkSetId = scmSs7RouteAdminState->linkSetId;
       NwstkSs7RouteAdminStateModify.direction = REMOTE_ROUTE;
       NwstkSs7RouteAdminStateModify.family = g_parameter.family;
       NwstkSs7RouteAdminStateModify.style = scmSs7RouteAdminState->style;
       NwstkSs7RouteAdminStateModify.sio = scmSs7RouteAdminState->sio;
       NwstkSs7RouteAdminStateModify.rssn = scmSs7RouteAdminState->ssn;
       NwstkSs7RouteAdminStateModify.lssn = 0;
       NwstkSs7RouteAdminStateModify.networkIndicator = scmSs7RouteAdminState->networkIndicator;
       NwstkSs7RouteAdminStateModify.adminState = scmSs7RouteAdminState->adminState;      
       SCM_printf(SCM_INFO,"linksetId: %d, direction: %d," 
                           "family: %d, style: %d, sio: %d,"
                           " ssn: %d, lssn %d, nwId: %d, adminState %d", 
                          scmSs7RouteAdminState->linkSetId, REMOTE_ROUTE, g_parameter.family,
                          scmSs7RouteAdminState->style, scmSs7RouteAdminState->sio, scmSs7RouteAdminState->ssn,
                          NwstkSs7RouteAdminStateModify.lssn, scmSs7RouteAdminState->networkIndicator,
                          scmSs7RouteAdminState->adminState);
       Length            = sizeof(ScmNwstkSs7RouteAdminStateModify);
       memcpy(cmd_buff, &NwstkSs7RouteAdminStateModify, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, transaction_Id[SCM_NWSTK_SS7ROUTE_ADMIN_STATE_MODIFY], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, 
                         SCM_NWSTK_SS7ROUTE_ADMIN_STATE_MODIFY,
                         transaction_Id[SCM_NWSTK_SS7ROUTE_ADMIN_STATE_MODIFY], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
 
  case OAM_SCM_SCCP_BEHAVIOR_CONFIG:
       sccpBehaviorConfig = (sSccpBehaviorConfigTableApi*)&msg_buff[8];
       sccpSetBehaviorConfig.sccpBehaviorConfigps = sccpBehaviorConfig->sccpBehaviorConfigps;
       sccpSetBehaviorConfig.sccpBehaviorConfigus = sccpBehaviorConfig->sccpBehaviorConfigus;
       sccpSetBehaviorConfig.sccpBehaviorConfigpi = sccpBehaviorConfig->sccpBehaviorConfigpi;
       sccpSetBehaviorConfig.sccpBehaviorConfigpe = sccpBehaviorConfig->sccpBehaviorConfigpe;
       SCM_printf(SCM_MAJOR,"SCM - > SCCP 'SCCP_BEHAVIOUR' gps: %d, us: %d, pi: %d, pe: %d",
                  sccpBehaviorConfig->sccpBehaviorConfigps, sccpBehaviorConfig->sccpBehaviorConfigus,
                  sccpBehaviorConfig->sccpBehaviorConfigpi, sccpBehaviorConfig->sccpBehaviorConfigpe);    
       Length            = sizeof(SccpSetBehaviorConfig) ;
       memcpy(cmd_buff, &sccpSetBehaviorConfig, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK,
                      transaction_Id[SCM_NWSTK_SCCP_SET_BEHAV], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_SET_BEHAV,
                        transaction_Id[SCM_NWSTK_SCCP_SET_BEHAV], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

  case OAM_SCM_MTP3_GENPEG_GET:
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 :MTP3_GENPEG_GET:");
       scmMtp3GenPegGet = (OamScmMtp3GenPegGet*)msg_buff;
       NwstkMtp3GenPegGet.pegResetFlag = scmMtp3GenPegGet->pegResetFlag;
       SCM_printf(SCM_INFO,"pegResetFlag: %d",
                  scmMtp3GenPegGet->pegResetFlag);
       Length            = sizeof(ScmNwstkMtp3GenPegGet);
       memcpy(cmd_buff, &NwstkMtp3GenPegGet, Length);  
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, 
                     transaction_Id[SCM_NWSTK_MTP3_GENPEG_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_MTP3_GENPEG_GET,
                        transaction_Id[SCM_NWSTK_MTP3_GENPEG_GET], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;
 
  case OAM_SCM_MTP2_PEG_GET:
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 :MTP2_PEG_GET:");
       scmMtp2PegGet                = (OamScmMtp2PegGet*)msg_buff;
       NwstkMtp2PegGet.pegResetFlag = scmMtp2PegGet->pegResetFlag;
       NwstkMtp2PegGet.linkId       = scmMtp2PegGet->linkId;
       NwstkMtp2PegGet.linkSetId    = scmMtp2PegGet->linkSetId;
       SCM_printf(SCM_INFO,"pegResetFlag: %d, ls: %d, ln: %d",
                  scmMtp2PegGet->pegResetFlag, scmMtp2PegGet->linkId, 
                  scmMtp2PegGet->linkSetId);
       Length            = sizeof(ScmNwstkMtp2PegGet);
       memcpy(cmd_buff, &NwstkMtp2PegGet, Length);  
       ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_GET,  0,
                                                 scmMtp2PegGet->linkId,
                                                 scmMtp2PegGet->linkSetId,
                                                 &cardFlag, 0);
       if( ret_val == 0)
        {
         SCM_printf(SCM_MAJOR,"MTP2 PEG GET FAILURE: cause"
                              " LinkId %d, for linkSetId: %d is not configured",
                               scmMtp2PegGet->linkId, scmMtp2PegGet->linkSetId);
         send_resp_to_oam( SCM_OAM_MTP2_PEG_RESP, ((ScmHdr *)msg_buff)->operation,
                           ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare,
                           PEGS_NOTFOUND, NULL, resp_len , APP_ID_OAM);

        return 0;
        }
       else
        {
         switch(cardFlag)
          {
           case SELF:
                    form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_MTP2_PEG_GET,
                                      transaction_Id[SCM_NWSTK_MTP2_PEG_GET], Length);
                    start_timer ( TIMER_NWSTK, APP_ID_NWSTK, 
                                  transaction_Id[SCM_NWSTK_MTP2_PEG_GET], msg_buff);
                    ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
                break;

          case PEER:
               if((g_parameter.nwstk_cfgIndFromPeerCard  == 1) && (xxx_client_sockfd[ENT_PEER_SCM] > 0))
               {
                SCM_printf(SCM_INFO,"MTP2_PEG_GET CMD IS FOR PEER : sent to peer");
               ((OamScmLinkConfig*)msg_buff)->scmhdr.appid   = APP_ID_PEER_SCM;

                                                                     /*opcode changed for
                                                                       distinguishing scm 
                                                                       update cmd from oam
                                                                       cmd*/
                start_timer ( TIMER_NWSTK, APP_ID_NWSTK, 
                                  transaction_Id[SCM_NWSTK_MTP2_PEG_GET], msg_buff);
                ret_val = scm_dispatch_buffer(msg_buff, APP_ID_PEER_SCM,
                                            ((ScmHdr *)msg_buff)->len);
               }
               else
               {
                SCM_printf(SCM_MAJOR,"MTP2 PEG GET FAILURE: cause"
                              " PEER CARD NOT CONFIGURED YET",
                               scmMtp2PegGet->linkId, scmMtp2PegGet->linkSetId);
                send_resp_to_oam( SCM_OAM_MTP2_PEG_RESP, ((ScmHdr *)msg_buff)->operation,
                              ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare,
                             PEGS_NOTFOUND, NULL, resp_len , APP_ID_OAM);

                return 0;

               }    
                break;

          }
        }

       break;
 
  case OAM_SCM_LINK_PEG_GET:
       scmMtp3LinkPegGet = (OamScmMtp3LinkPegGet*)msg_buff;
       SCM_printf(SCM_INFO,"SCM -> MTP3: 'LINK_PEG_GET' linkSetId: %d, linkId: %d ", 
                            scmMtp3LinkPegGet->linkSetId, scmMtp3LinkPegGet->linkId);
       NwstkMtp3LinkPegGet.pegResetFlag = scmMtp3LinkPegGet->pegResetFlag;
       NwstkMtp3LinkPegGet.linkSetId = scmMtp3LinkPegGet->linkSetId;
       NwstkMtp3LinkPegGet.linkId = scmMtp3LinkPegGet->linkId;
       Length            = sizeof(ScmNwstkMtp3LinkPegGet);
       SCM_printf(SCM_INFO,"pegResetFlag: %d", scmMtp3LinkPegGet->pegResetFlag);    
       memcpy(cmd_buff, &NwstkMtp3LinkPegGet, Length);
       ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_GET,  0,
                                                 scmMtp3LinkPegGet->linkId,
                                                 scmMtp3LinkPegGet->linkSetId,
                                                 &cardFlag, 0);
       if( ret_val == 0)
        {
         SCM_printf(SCM_MAJOR,"LINK PEG GET FAILURE: cause"
                              " LinkId %d, for linkSetId: %d is not configured",
                               scmMtp3LinkPegGet->linkId, scmMtp3LinkPegGet->linkSetId);
         send_resp_to_oam( SCM_OAM_LINK_PEG_RESP, ((ScmHdr *)msg_buff)->operation, 
                           ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare,
                           PEGS_NOTFOUND, NULL, resp_len , APP_ID_OAM);

        return 0;
        }
       else
        {
         switch(cardFlag)
          {
           case SELF:
                form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_MTP3_LINKPEG_GET,
                                  transaction_Id[SCM_NWSTK_MTP3_LINKPEG_GET], Length);
                start_timer ( TIMER_NWSTK, APP_ID_NWSTK,
                        transaction_Id[SCM_NWSTK_MTP3_LINKPEG_GET], msg_buff);
                ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
                break;
                
          case PEER:
               if((g_parameter.nwstk_cfgIndFromPeerCard  == 1) && (xxx_client_sockfd[ENT_PEER_SCM] > 0))
               { 
                SCM_printf(SCM_INFO,"LINK_PEG_GET CMD IS FOR PEER : sent to peer");
                ((OamScmLinkConfig*)msg_buff)->scmhdr.appid   = APP_ID_PEER_SCM;

                                                                     /*opcode changed for
                                                                       distinguishing scm
                                                                       update cmd from oam
                                                                       cmd*/
                start_timer ( TIMER_NWSTK, APP_ID_NWSTK,
                        transaction_Id[SCM_NWSTK_MTP3_LINKPEG_GET], msg_buff);
                ret_val = scm_dispatch_buffer(msg_buff, APP_ID_PEER_SCM, 
                                            ((ScmHdr *)msg_buff)->len); 
               }
                else
               {
                SCM_printf(SCM_MAJOR,"MTP3 LINK PEG GET FAILURE: cause"
                              " PEER CARD NOT CONFIGURED YET",
                               scmMtp3LinkPegGet->linkId, scmMtp3LinkPegGet->linkSetId);
                send_resp_to_oam( SCM_OAM_LINK_PEG_RESP, ((ScmHdr *)msg_buff)->operation,
                           ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare,
                           PEGS_NOTFOUND, NULL, resp_len , APP_ID_OAM);

                return 0;

               }

                break;
             
                  
          }  
        }  
                   
       break;

  case OAM_SCM_SS7ROUTE_PEG_GET:
       SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_SS7ROUTE_PEG_GET:");
       scmMtp3RoutePegGet = (OamScmMtp3RoutePegGet*)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> MTP3: 'SS7ROUTE_PEG_GET' dpc: %d, nwId: %d ", 
                               scmMtp3RoutePegGet->dpc, scmMtp3RoutePegGet->ni);
       NwstkMtp3RoutePegGet.pegResetFlag = scmMtp3RoutePegGet->pegResetFlag;
       NwstkMtp3RoutePegGet.dpc = scmMtp3RoutePegGet->dpc;
       NwstkMtp3RoutePegGet.ni = scmMtp3RoutePegGet->ni;
       Length            = sizeof(ScmNwstkMtp3RoutePegGet);
       SCM_printf(SCM_INFO,"pegResetFlag: %d", scmMtp3RoutePegGet->pegResetFlag);      
       memcpy(cmd_buff, &NwstkMtp3RoutePegGet, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK,
                     transaction_Id[SCM_NWSTK_MTP3_ROUTEPEG_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_MTP3_ROUTEPEG_GET,
                        transaction_Id[SCM_NWSTK_MTP3_ROUTEPEG_GET], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

         
  case OAM_SCM_SCCP_GENPEG_GET:
       SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_SCCP_GENPEG_GET:");
       SCM_printf(SCM_MAJOR,"SCM -> MTP3: 'SCCP_GENPEG_GET'"); 
       scmSccpGenPegGet = (OamScmSccpGenPegGet*)msg_buff;
       NwstkSccpGenPegGet.pegResetFlag = scmSccpGenPegGet->pegResetFlag;
       SCM_printf(SCM_INFO,"pegResetFlag: %d",
                  scmSccpGenPegGet->pegResetFlag);    
       
       Length            = sizeof(ScmNwstkSccpGenPegGet);
       memcpy(cmd_buff, &NwstkSccpGenPegGet, Length);
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, 
                     transaction_Id[SCM_NWSTK_SCCP_GENPEG_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_SCCP_GENPEG_GET,
                        transaction_Id[SCM_NWSTK_SCCP_GENPEG_GET], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
       break;

  case OAM_SCM_BSSAP_GENPEG_GET:
       SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_BSSAP_GENPEG_GET:");
       scmBssapGenPegGet = (OamScmBssapGenPegGet*)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> MTP3: 'BSSAP_GENPEG_GET' BscPC %d", scmBssapGenPegGet->bscPointCode); 
       NwstkBssapGenPegGet.pegResetFlag = scmBssapGenPegGet->pegResetFlag;
       NwstkBssapGenPegGet.bscPointCode = scmBssapGenPegGet->bscPointCode;
       SCM_printf(SCM_INFO,"pegResetFlag: %d",
                  scmBssapGenPegGet->pegResetFlag);   
       Length            = sizeof(ScmNwstkBssapGenPegGet);
       memcpy(cmd_buff, &NwstkBssapGenPegGet, Length); 
       start_timer ( TIMER_NWSTK, APP_ID_NWSTK, 
                     transaction_Id[SCM_NWSTK_BSSAP_GENPEG_GET], msg_buff);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_BSSAP_GENPEG_GET,
                         transaction_Id[SCM_NWSTK_BSSAP_GENPEG_GET], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
      break;
  default:
         SCM_printf (SCM_MAJOR, "COMMAND TYPE IS NOT IMPLEMENTED AT SCM");
         break;
          
 

  }
 if(ret_val <= 0)
  {
   g_parameter.config_cmd_resp = 0;
   stop_timer (TIMER_NWSTK);
   SCM_printf (SCM_CRITICAL, "COMMAND SEND TO NWSTK IS FAILURE");
   return 0;
  } 
 if(g_parameter.config_flag == 1)
  {
   g_parameter.config_cmd_resp = 1;
  }
  return 1; 
}
#ifdef LAPD_HA
void send_lapd_config_complete()
{
 U8 cmd_buff[10], *Lapd_Data;
 U16 Length;
 ScmLapdConfigComplete     Lapd_Config_Complete;
 /* LAPD HEADER */
 cmd_buff [0] = LAPD_SCM_IF_ID;
 Length       = sizeof(ScmLapdConfigComplete);
 cmd_buff [1] = Length & 0xff;
 cmd_buff [2] = (Length >> 8) & 0xff;;
          /* LAPD DATA */
 Lapd_Config_Complete.msgGrpId = LAPD_CONFIG_COMPLETE;
 Lapd_Data = (U8*)&Lapd_Config_Complete;
 memcpy (&cmd_buff[3], Lapd_Data, Length);
 SCM_printf (SCM_INFO,"Sending LAPD config complete event to lapd");
 scm_dispatch_buffer(cmd_buff, APP_ID_LAPD, Length +3);
}
#endif
int process_lapd_stack_cmd (U8* msg_buff)
{
 U8  hdrsize,  family;
 U32  opc, loop;
 U16 Length, resp_len;
 signed int ret_val =0;
 hdrsize = sizeof(ScmHdr);
 U8 cmd_buff[500], *Lapd_Data;
 U16 opcode, tr_opcode;
 resp_len = sizeof(ScmOamResponse);
 opcode = ((ScmHdr *)msg_buff)->opcode;
 tr_opcode = opcode - BASE_OPCODE_SCM;
 strcpy(g_parameter.function_string, "process_lapd_stack_cmd()");
 
#ifdef RB_GB_PHASE2
 ScmLapdTSConfig     Lapd_Ts_Config;
 ScmLapdSapiConfig   Lapd_Sapi_Config; 
#endif
 ScmLapdTeiConfig    Lapd_Tei_Config;
 NwstkScmLapdTimerConfig     Lapd_Timer_Config; 
 ScmLapdPegsShow_t   Lapd_Pegs_Get;

 if( g_parameter.config_flag == SS7_FALSE)
  {
   oam_transaction_Id[tr_opcode].transaction_Id = ((ScmHdr *)msg_buff)->trid;/*store oam trid */ 
   oam_transaction_Id[tr_opcode].operation      = ((ScmHdr *)msg_buff)->operation;/*store oam operation */
   oam_transaction_Id[tr_opcode].pegrfu      = ((ScmHdr *)msg_buff)->spare;/*store peg cmd indication */
  }
 
 family  = g_parameter.family;
 opc     = g_parameter.opc_value;

#define SEND_TO_LAPD_STACK() \
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_LAPD, Length +3);
        


 switch (opcode)
    {
#ifdef RB_GB_PHASE2
     case OAM_SCM_LAPDTS_CONFIG:
          sLapdTSConfigTableApi = (OamScmLapdTSConfig*)msg_buff;
          /* LAPD HEADER */
          cmd_buff [0] = LAPD_SCM_IF_ID;
          Length       = sizeof(ScmLapdTSConfig);
          cmd_buff [1] = Length & 0xff;
          cmd_buff [2] = Length >> 8) & 0xff;;

          /* LAPD DATA */
          Lapd_Ts_Config.msgGrpId = LAPD_SCM_CFG_MSG;
          if(((ScmHdr *)msg_buff)->operation == SCM_ADD)
           { 
            SCM_printf (SCM_INFO,"LAPD_ADD_TS");
            Lapd_Ts_Config.msgType  = LAPD_SCM_CFG_ADD_TS;
           }
          else
           { 
            SCM_printf (SCM_INFO,"LAPD_REM_TS");
            Lapd_Ts_Config.msgType  = LAPD_SCM_CFG_REM_TS;
           } 
          Lapd_Ts_Config.timeSlot = sLapdTSConfigTableApi->lapdtimeslot;
          Lapd_Data = (U8*)&Lapd_Ts_Config;
          memcpy (&cmd_buff[2], Lapd_Data, Length);
          start_timer ( TIMER_LAPD, APP_ID_LAPD,
                        transaction_Id[tr_opcode], msg_buff);
          SEND_TO_LAPD_STACK();
          break;
#endif
     case OAM_SCM_LAPDTEI_CONFIG:
          sLapdTEIConfigTableApi = (OamScmLapdTEIConfig*)msg_buff;
          /* LAPD HEADER */
          cmd_buff [0] = LAPD_SCM_IF_ID;
          Length        = sizeof(ScmLapdTeiConfig);
          cmd_buff [1] = Length & 0xff;
          cmd_buff [2] = (Length >> 8) & 0xff;;
          /* LAPD DATA */
          Lapd_Tei_Config.msgGrpId = LAPD_SCM_CFG_MSG;
          if(((ScmHdr *)msg_buff)->operation == SCM_ADD)
           { 
            SCM_printf (SCM_INFO,"LAPD_ADD_TEI");
            Lapd_Tei_Config.msgType  = LAPD_SCM_CFG_ADD_TEI;
           }
          else
           { 
            SCM_printf (SCM_INFO,"LAPD_REM_TEI");
            Lapd_Tei_Config.msgType  = LAPD_SCM_CFG_REM_TEI;
           } 
          Lapd_Tei_Config.timeSlot = sLapdTEIConfigTableApi->lapdtimeslot;
          Lapd_Tei_Config.lapdTei  = sLapdTEIConfigTableApi->lapdTei;
          Lapd_Tei_Config.appTei   = sLapdTEIConfigTableApi->applTei;
          Lapd_Data = (U8*)&Lapd_Tei_Config;
          memcpy (&cmd_buff[3], Lapd_Data, Length);
          start_timer ( TIMER_LAPD, APP_ID_LAPD,
                        transaction_Id[tr_opcode], msg_buff);
          SEND_TO_LAPD_STACK();
          break;
#ifdef RB_GB_PHASE2
     case OAM_SCM_LAPDSAPI_CONFIG:
          sLapdSAPIConfigTableApi = (OamScmLapdSAPIConfig*)msg_buff;
          /* LAPD HEADER */
          cmd_buff [0] = LAPD_SCM_IF_ID;
          Length        = sizeof(ScmLapdSapiConfig);
          cmd_buff [1] = Length;
          /* LAPD DATA */
          Lapd_Sapi_Config.msgGrpId = LAPD_SCM_CFG_MSG;
          if(((ScmHdr *)msg_buff)->operation == SCM_ADD)
           { 
            SCM_printf (SCM_INFO,"LAPD_ADD_SAPI");
            Lapd_Sapi_Config.msgType  = LAPD_SCM_CFG_ADD_SAPI;
           }
          else
           { 
            SCM_printf (SCM_INFO,"LAPD_REM_SAPI");
            Lapd_Sapi_Config.msgType  = LAPD_SCM_CFG_REM_SAPI;
           } 
          Lapd_Sapi_Config.timeSlot = sLapdSAPIConfigTableApi->lapdtimeslot;
          Lapd_Sapi_Config.sapi     = sLapdSAPIConfigTableApi->lapdSapi;
          Lapd_Data = (U8*)&Lapd_Sapi_Config;
          memcpy (&cmd_buff[2], Lapd_Data, Length);
          start_timer ( TIMER_LAPD, APP_ID_LAPD,
                        transaction_Id[tr_opcode], msg_buff);
          SEND_TO_LAPD_STACK();
          break;
#endif

     case OAM_SCM_LAPDTIMER_CONFIG:
          sLapdTimerTableApi = (OamScmLapdTimerConfig*)msg_buff;

          /* LAPD HEADER */
          cmd_buff [0] = LAPD_SCM_IF_ID;
          Length        = sizeof(NwstkScmLapdTimerConfig);
          cmd_buff [1] = Length & 0xff;
          cmd_buff [2] = (Length >> 8) & 0xff;;

          /* LAPD DATA */
          Lapd_Timer_Config.msgGrpId = LAPD_SCM_TMR_MSG;

          /*SCM_printf (SCM_INFO,"LAPD_TIMER_MODIFY: t200: %d, t203: %d, n200: %d",
                      sLapdTimerTableApi->lapdTimerT200, 
                      sLapdTimerTableApi->lapdTimerT203,
                      sLapdTimerTableApi->N200);*/

          Lapd_Timer_Config.msgType  = LAPD_SCM_TMR_SET;
          memcpy(&Lapd_Timer_Config.lapdTimerDefault, &sLapdTimerTableApi->lapdTimerDefault, sizeof(LapdTimerConfig));
          memcpy(&Lapd_Timer_Config.lapdTimerSatellite, &sLapdTimerTableApi->lapdTimerSatellite, sizeof(LapdTimerConfig));
          Lapd_Timer_Config.noOfLapdTs = sLapdTimerTableApi->noOfLapdTs;


          for(loop=0; loop<sLapdTimerTableApi->noOfLapdTs; loop++) 
          {
           memcpy(&Lapd_Timer_Config.lpdTsdetail[loop], &sLapdTimerTableApi->lpdTsdetail[loop], 
                sizeof(LapdTsDetail)); 
          } 


          SCM_printf (SCM_INFO,"LAPD_TIMER_MODIFY for sat: t200: %d, t203: %d, n200: %d",
                      Lapd_Timer_Config.lapdTimerSatellite.lapdTimerT200,
                      Lapd_Timer_Config.lapdTimerSatellite.lapdTimerT203,
                      Lapd_Timer_Config.lapdTimerSatellite.N200);  

          SCM_printf (SCM_INFO,"LAPD_TIMER_MODIFY ts details: ts %d, satFlag: %d",
                      Lapd_Timer_Config.lpdTsdetail[0].ts,
                      Lapd_Timer_Config.lpdTsdetail[0].satFlag);

          start_timer ( TIMER_LAPD, APP_ID_LAPD,
                        transaction_Id[tr_opcode], msg_buff);
          Lapd_Data = (U8*)&Lapd_Timer_Config;
          memcpy (&cmd_buff[3], Lapd_Data, Length);
          SEND_TO_LAPD_STACK();
          break;

         /* LAPD Pegs Show  */
         case  OAM_SCM_LAPD_PEG_GET:
               sLapdPegGetTableApi = (OamScmLapdPegGet*)msg_buff;
               /* LAPD HEADER */
               cmd_buff [0] = LAPD_SCM_IF_ID;
               Length        = sizeof(ScmLapdPegsShow_t);
               cmd_buff [1] = Length & 0xff;
               cmd_buff [2] = (Length >> 8) & 0xff;;
               /* LAPD DATA */
               Lapd_Pegs_Get.msgGrpId = LAPD_SCM_PEGS_MSG;
               /*SCM_printf (SCM_INFO,"LAPD_PEG_GET: appTei: %d, resetFlg: %d", 
                           sLapdPegGetTableApi->applTei, 
                           sLapdPegGetTableApi->pegResetFlag);*/
               Lapd_Pegs_Get.msgType  = LAPD_SCM_PEGS_SHOW;
               Lapd_Pegs_Get.count    = sLapdPegGetTableApi->count;
               memcpy(Lapd_Pegs_Get.appTeiInfo, sLapdPegGetTableApi->appTeiInfo, 5);
               Lapd_Pegs_Get.pegResetFlag = sLapdPegGetTableApi->pegResetFlag;
               Lapd_Data = (U8*)&Lapd_Pegs_Get;
               memcpy (&cmd_buff[3], Lapd_Data, Length);
               start_timer ( TIMER_LAPD, APP_ID_LAPD,
                        transaction_Id[tr_opcode], msg_buff);
               SEND_TO_LAPD_STACK();
               break;
          default:
                SCM_printf (SCM_MAJOR, "COMMAND TYPE FOR LAPD IS NOT IMPLEMENTED AT SCM");
                send_resp_to_oam(  0, 0, ((ScmHdr *)msg_buff)->trid ,
                                ((ScmHdr *)msg_buff)->spare,
                        ERROR_WRONG_OPCODE, NULL, resp_len, APP_ID_OAM);

                return 0;

    }
    if(ret_val <= 0) 
      {              
        stop_timer (TIMER_LAPD);
        g_parameter.config_cmd_resp = 0;
        SCM_printf (SCM_CRITICAL, "COMMAND SEND TO LAPD IS FAILURE");
        return ret_val;
      }
 if(g_parameter.config_flag == 1)
  {
   g_parameter.config_cmd_resp = 1;
  }
   return 1;
}

/**********************************************************************************/
/*this function handle the maptcap command received from oam or command fetched from db,
 it processes the command and send to maptcap */
/**********************************************************************************/
int process_maptcap_stack_cmd (U8* msg_buff)
{
 U8 hdrsize, family,noe, operation, cmd_buff[200], tcap_alarm_level =0, srcPlmn[5], temp;
 U32 ctgry, cmd, opc, ret_val = 0, srcPlmnId, dstPlmnId, tmrStrLen;
 hdrsize = sizeof(ScmHdr);
 U16 opcode, tr_opcode, Length, resp_len;
 resp_len = sizeof(ScmOamResponse);
 opcode = ((ScmHdr *)msg_buff)->opcode;
 operation = ((ScmHdr *)msg_buff)->operation;
 
 /*tr_opcode = opcode - BASE_OPCODE_SCM;*/
 tr_opcode = opcode - BASE_OPCODE_SCM_AOIP;

 U8 asp_modify= 0;
 asp_modify = msg_buff[16];
/*AOIP MEMSET*/
 U16 lv, row_count=0, cmd_state=0, asp_id=0; /*AOIP VARIABLES*/
 memset(cmd_buff, 0, 200);
/*AOIP END*/ 
 strcpy(g_parameter.function_string, "process_maptcap_stack_cmd()");
 if( g_parameter.config_flag == SS7_FALSE)
  {
   oam_transaction_Id[tr_opcode].transaction_Id = ((ScmHdr *)msg_buff)->trid;/*store oam trid */ 
   oam_transaction_Id[tr_opcode].operation      = ((ScmHdr *)msg_buff)->operation;/*store oam operation */
   oam_transaction_Id[tr_opcode].pegrfu      = ((ScmHdr *)msg_buff)->spare;/*store peg cmd indication */
  }
 switch( g_parameter.alarm_level )
   {
        case ALRM_LVL_CRIT:
             tcap_alarm_level = 1;
             break;
        case ALRM_LVL_MAJR:
             tcap_alarm_level = 2;
        case ALRM_LVL_MINR:
        case ALRM_LVL_INFO:
        case ALRM_LVL_WARN:
             tcap_alarm_level = 3;
   }
 
 family  = g_parameter.family;
 opc     = g_parameter.opc_value;
 switch(opcode)
   {
#if 0   /*AOIP REST CASES NOT VALID*/
    case OAM_SCM_MAP_INIT_CONFIG:
         SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_MAP_INIT_CONFIG:");
#if 0
         smapInitConfig  = (mapInitConfig*)msg_buff;
         ctgry = 1;
         cmd = OAM_MAP_INIT;
         noe = 3;
         Length = 19;
         form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry,
                             transaction_Id[tr_opcode],
                             cmd, Length);
        
   EXTRACT_32( 8, smapInitConfig->mapInitConfignumofDsm,      cmd_buff);
   EXTRACT_32(12, smapInitConfig->mapInitConfignumofSSM,      cmd_buff);
   EXTRACT_32(16,  smapInitConfig->mapInitConfigmaxDialogueAge,cmd_buff);
   SCM_printf(SCM_MAJOR,"SCM -> MAP 'MAP INIT' numOfDsm: %d, numOfSsm: %d, maxDialogueAge: %d",
              smapInitConfig->mapInitConfignumofDsm, smapInitConfig->mapInitConfignumofSSM,
              smapInitConfig->mapInitConfigmaxDialogueAge);   
         start_timer ( TIMER_MAPTCAP, APP_ID_TCAP,
                     transaction_Id[tr_opcode], msg_buff);

         ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_MAP, Length);
#endif
     
    break;
    case OAM_SCM_LINK_ADMIN_CONFIG:
           SCM_printf(SCM_INFO,"processing cmd : OAM_SCM_SIGTRAN_ASP_ADMIN_CONFIG:");
           if (asp_modify == 1) 
           {
                ctgry = 1;
                cmd = 19;
                noe = 3;
                Length = 8;
                form_maptcap_header(cmd_buff, SIGTRAN_M3UA_API,  noe, ctgry, 
                                  transaction_Id[tr_opcode],
                                   cmd, Length);
                start_timer ( TIMER_MAPTCAP, APP_ID_TCAP,
                           transaction_Id[tr_opcode], msg_buff);
                SCM_printf(SCM_INFO,"processing cmd : OAM_SCM_SIGTRAN_ASP_ADMIN_CONFIG_UNLOCK:");
                ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_TCAP, Length); 
            }
            if (asp_modify == 0)
            {
                ctgry = 1;
                cmd = 20;
                noe = 3;
                Length = 8;
                form_maptcap_header(cmd_buff, SIGTRAN_M3UA_API,  noe, ctgry, 
                                  transaction_Id[tr_opcode],
                                   cmd, Length);
                start_timer ( TIMER_MAPTCAP, APP_ID_TCAP,
                           transaction_Id[tr_opcode], msg_buff);
                ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_TCAP, Length); 
            }

              break;

    case OAM_SCM_TCAP_ALARM_LEVEL_MODIFY:

              SCM_printf(SCM_INFO,"processing cmd : OAM_SCM_TCAP_ALARM_LEVEL_MODIFY:");
              ctgry = 4;
              cmd = 0;
              noe = 2;
              Length = 13;
              SCM_printf (SCM_MAJOR, "SCM -> TCAP 'TCAP_ALARM_LVL_MODIFY' Alarm level : %d", g_parameter.alarm_level);
              form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry, 
                                  transaction_Id[tr_opcode],
                                   cmd, Length);
              EXTRACT_32(8,  ALL_ERROR,  cmd_buff);
              cmd_buff [12] = tcap_alarm_level;
              start_timer ( TIMER_MAPTCAP, APP_ID_TCAP,
                           transaction_Id[tr_opcode], msg_buff);
              ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_TCAP, Length); 
              break;


    case OAM_SCM_TCAP_TRACE_LEVEL_MODIFY:
              SCM_printf(SCM_INFO,"processing cmd : OAM_SCM_TCAP_TRACE_LEVEL_MODIFY:");
              ctgry = 3;
              cmd = OAM_TCAP_SS7_SM_SET_TRACE_LEVEL;
              noe = 5;
              Length = 13;
              MapTraceConfigTableApi = (sMapTraceConfigTableApi*)msg_buff;
              EXTRACT_32(8,  MapTraceConfigTableApi->trace_flag,  cmd_buff);
              cmd_buff[12] = MapTraceConfigTableApi->trace_level;
              form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry, 
                                  transaction_Id[tr_opcode],
                                   cmd, Length);
              start_timer ( TIMER_MAPTCAP, APP_ID_TCAP,
                           transaction_Id[tr_opcode], msg_buff);
              SCM_printf (SCM_MAJOR, "SCM -> TCAP 'TCAP_TRACE_LVL_MODIFY' TRACE LEVEL : %d", cmd_buff[12]);
              ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_TCAP, Length); 
              break;

    case OAM_SCM_MAP_ALARM_LEVEL_MODIFY:
              SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_MAP_ALARM_LEVEL_MODIFY:");
              ctgry = 1;
              cmd = MAP_SET_ERROR_LEVEL_REQUEST;
              noe = 2;
              Length = 10;
              SCM_printf (SCM_INFO, "SCM -> MAP 'MAP_ALARM_LVL_MODIFY' Alarm level : %d", tcap_alarm_level);
              form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry, 
                                  transaction_Id[tr_opcode],
                                  cmd, Length);
              cmd_buff[8] = MAP_ALL_ERROR;
              if(g_parameter.alarm_level == ALRM_LVL_CRIT)
              cmd_buff [9] = 1;
              if((g_parameter.alarm_level == ALRM_LVL_MINR)|| (g_parameter.alarm_level == ALRM_LVL_MAJR)||(g_parameter.alarm_level == ALRM_LVL_WARN))
              cmd_buff [9] = 2;
              else 
               cmd_buff [9] = 0;
              start_timer ( TIMER_MAPTCAP, APP_ID_MAP, transaction_Id[tr_opcode], msg_buff);
              ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_MAP, Length); 
              break;


         
    case OAM_SCM_MAP_SEC_CONFIG:
        #if 0
         scmMapSecurityConfig = (OamScmMapSecurityConfig*)msg_buff;
         ctgry = 1;
         noe = 13;
         if(operation == SCM_DELETE )
           {
            SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_MAP_SEC_DEL_CONFIG:");
            cmd = OAM_MAP_DEL_PLMN_ID;
           }
         else
           {     
            SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_MAP_SEC_ADD_CONFIG:");
            cmd = OAM_MAP_ADD_PLMN_ID;
           }
         Length = 131;
         form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry, 
                             transaction_Id[tr_opcode],
                             cmd, Length);
         for(temp = 0; temp <5; temp++)
         {
           srcPlmn[temp] = scmMapSecurityConfig->srcPlmnId[temp];   
         }
         srcPlmn[5]='\0';             
         srcPlmnId = atoi(scmMapSecurityConfig->srcPlmnId);
         SCM_printf(SCM_INFO,"srcPlmnId %d", srcPlmnId);
         dstPlmnId = atoi(scmMapSecurityConfig->dstPlmnId);
         EXTRACT_32(8,    srcPlmnId, cmd_buff);
         EXTRACT_32(12,   dstPlmnId, cmd_buff);
            
         if((scmMapSecurityConfig->plmnSecureFlag == 0) ||
            (scmMapSecurityConfig->plmnSecureFlag == 1))  
           {
            /* check success */
           }
         else
          {
           g_parameter.config_cmd_resp = 0;
           SCM_printf(SCM_INFO,"WRONG PLMN SECURE VALUE");
           if(g_parameter.config_flag == 0)
            {
              send_resp_to_oam(SCM_OAM_MAP_SEC_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, 
                               ((ScmHdr *)msg_buff)->trid , 0, ERROR_FALLBACK_VALUE_NOT_SUPPORTED, NULL, resp_len, APP_ID_NWSTK);
            }
           return 0; 
            
          }
            
         cmd_buff [16] = scmMapSecurityConfig->plmnSecureFlag;
         cmd_buff [17] = scmMapSecurityConfig->plmnSecureFlag;
         EXTRACT_32(18,    scmMapSecurityConfig->spi, cmd_buff);
         EXTRACT_32(22,    scmMapSecurityConfig->mea, cmd_buff);
         memcpy(&cmd_buff[26], scmMapSecurityConfig->mek, 16);
         EXTRACT_32(42,    scmMapSecurityConfig->mia, cmd_buff);
         memcpy(&cmd_buff[46], scmMapSecurityConfig->mik, 16);
         cmd_buff[62] = (U8)scmMapSecurityConfig->pPri;   
         //EXTRACT_32(62,    scmMapSecurityConfig->pPri, cmd_buff);
         EXTRACT_16(63,    scmMapSecurityConfig->pPi, cmd_buff);
        SCM_printf(SCM_INFO,"srcPlmnId: %d, dstPlmnId: %d, fallBackeAllowed: %d"
                   "plmnSecureFlag: %d, spi: %d, mea: %d"
                   "mek: %d, mia: %d, mik: %d"
                   "pPri: %d, ppi: %d, commisMode: %d", srcPlmnId, dstPlmnId,
                   scmMapSecurityConfig->fallBackAllowedFlag, scmMapSecurityConfig->plmnSecureFlag,
                   scmMapSecurityConfig->spi, scmMapSecurityConfig->mea, scmMapSecurityConfig->mek,
                   scmMapSecurityConfig->mia, scmMapSecurityConfig->mik, scmMapSecurityConfig->pPri,
                   scmMapSecurityConfig->pPi, scmMapSecurityConfig->enodeCommisMode);
         tmrStrLen = strlen(scmMapSecurityConfig->hardExpiryTimer);
         strcpy(&cmd_buff[65], scmMapSecurityConfig->hardExpiryTimer);
         strcpy((cmd_buff + 65 + tmrStrLen), scmMapSecurityConfig->softExpiryTimer);  
         // memcpy(&cmd_buff[66], scmMapSecurityConfig->hardExpiryTimer, 32);
         // memcpy(&cmd_buff[98], scmMapSecurityConfig->softExpiryTimer, 32);
         tmrStrLen += strlen(scmMapSecurityConfig->softExpiryTimer);
         cmd_buff [65 + tmrStrLen] = (U8)scmMapSecurityConfig->enodeCommisMode;
         start_timer ( TIMER_MAPTCAP, APP_ID_MAP,
                     transaction_Id[tr_opcode], msg_buff);
        SCM_printf(SCM_MAJOR,"SCM -> MAP 'MAP_SEC_CONFIG' srcPlmnId: %d, dstPlmnId: %d",
                    srcPlmnId, dstPlmnId);

#endif
         ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_MAP, Length); 
         break;
         
    case OAM_SCM_MAP_TIMER_CONFIG:
         SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_MAP_TIMER_CONFIG:");
        #if 0 
        scmMapTimerConfig = (OamScmMapTimerConfig*)msg_buff;
         ctgry = 1;
         cmd = OAM_MAP_TIMER_CONFIG;
         noe = 4;
         Length = 40;
         form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry, 
                             transaction_Id[tr_opcode],
                             cmd, Length);
        EXTRACT_32( 8, MAP_TIMER_SMALL,  cmd_buff);
        EXTRACT_32( 12, scmMapTimerConfig->mapTimerSmall,  cmd_buff);
        EXTRACT_32( 16, MAP_TIMER_MEDIUM,  cmd_buff);
        EXTRACT_32( 20, scmMapTimerConfig->mapTimerMedium,  cmd_buff);
        EXTRACT_32( 24, MAP_TIMER_MEDIUM_LARGE,  cmd_buff);
        EXTRACT_32( 28, scmMapTimerConfig->mapTimerMediumLarge,  cmd_buff);
        EXTRACT_32( 32, MAP_TIMER_LARGE,  cmd_buff);
        EXTRACT_32( 36, scmMapTimerConfig->mapTimerLarge,  cmd_buff);
        start_timer ( TIMER_MAPTCAP, APP_ID_MAP,
                     transaction_Id[tr_opcode], msg_buff);
        SCM_printf(SCM_MAJOR,"SCM -> MAP 'MAP_TIMER_MODIFY'");
#endif
        ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_MAP, Length);
        break;

    case OAM_SCM_TCAP_PEG_GET:
         SCM_printf(SCM_INFO,"processing cmd :OAM_SCM_TCAP_PEG_GET:");
         #if 0
         scmTcapPegGet = (OamScmTcapPegGet*)msg_buff;
         ctgry = 2;
         cmd = OAM_TCAP_SS7_SM_GET_STATS;
         noe = 5;
         Length = 10;
         form_maptcap_header(cmd_buff, TCAP_API,  noe, ctgry, 
                             transaction_Id[tr_opcode],
                             cmd, Length);
         cmd_buff [8] = 6;/*here fill the value for all pegs */
         cmd_buff [9] = scmTcapPegGet->pegResetFlag;
         SCM_printf(SCM_INFO,"pegResetFlag: %d", scmTcapPegGet->pegResetFlag);
         start_timer ( TIMER_MAPTCAP, APP_ID_TCAP,
                     transaction_Id[tr_opcode], msg_buff);
        SCM_printf(SCM_MAJOR,"SCM -> TCAP 'TCAP_PEG_GET'");
#endif
        ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_TCAP, Length); 
        break;
#endif

   /*AOIP: SIGTRAN COMMANDS START*/
   case OAM_SCM_SCCP_INIT_CONFIG:
        ScmSccpInitConfig = (OamScmSccpInitConfig*)msg_buff;
        SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN 'SCCP_INIT_CONFIG' 'MAX :: sp[%d] ss[%d] css[%d] csp[%d] standard: [%d]'\n",
                   ScmSccpInitConfig->max_sp, ScmSccpInitConfig->max_ss, ScmSccpInitConfig->max_css,
                  ScmSccpInitConfig->max_csp, ScmSccpInitConfig->standard);
        noe    = (3+5) ;         /*3(category + command + trans_id) + 5 (elements)*/
        ctgry  = SS7_SM_CTRL;
        cmd    = SCCP_SM_INIT_INSTANCE; 
        Length = (8+17);     /*8(len upto tarns_id) + 17(data buffer len)*/
        form_maptcap_header(cmd_buff, SCCP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

         
        EXTRACT_32(  8, ScmSccpInitConfig->max_sp ,  cmd_buff);
        EXTRACT_32( 12, ScmSccpInitConfig->max_ss ,  cmd_buff);
        EXTRACT_32( 16, ScmSccpInitConfig->max_css,  cmd_buff);
        EXTRACT_32( 20, ScmSccpInitConfig->max_csp,  cmd_buff);
        cmd_buff[24] =  ScmSccpInitConfig->standard;
        
        start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
        ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);

        break;
   
   case OAM_SCM_SCCP_SP_CONFIG:
       ScmSccpSpConfig = (OamScmSccpSpConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'SCCP_SP_CONFIG' 'spId[%d] nwId[%d] local[%d] PC[%d]'\n",
                  (operation == SCM_ADD?"ADD":"DELETE"),
                 ScmSccpSpConfig->spId, ScmSccpSpConfig-> nwId, ScmSccpSpConfig->local, ScmSccpSpConfig->pointCode);
       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+4) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? SCCP_SM_ADD_SP: SCCP_SM_DEL_SP); 
               Length = (8+10);
               form_maptcap_header(cmd_buff, SCCP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);
       
               EXTRACT_32(  8, ScmSccpSpConfig->spId      ,  cmd_buff);
               cmd_buff[12] =  ScmSccpSpConfig->nwId;
               cmd_buff[13] =  ScmSccpSpConfig->local;
               EXTRACT_32( 14, ScmSccpSpConfig->pointCode ,  cmd_buff);

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
           break;
           default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
           break;
         }

        break;

   case OAM_SCM_SCCP_SS_CONFIG:
       ScmSccpSsConfig = (OamScmSccpSsConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'SCCP_SS_CONFIG' 'ssId[%d] spId[%d] ssn[%d]'\n",
                 (operation == SCM_ADD?"ADD":"DELETE"),
                 ScmSccpSsConfig->ssId, ScmSccpSsConfig->spId, ScmSccpSsConfig->ssn);
       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+3) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? SCCP_SM_ADD_SS : SCCP_SM_DEL_SS); 
               Length = (8+9);
               form_maptcap_header(cmd_buff, SCCP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

               
               EXTRACT_32( 8, ScmSccpSsConfig->ssId  ,  cmd_buff);
               EXTRACT_32( 12, ScmSccpSsConfig->spId  ,  cmd_buff);
               cmd_buff[16] = ScmSccpSsConfig->ssn;

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }
 
        break;

   case OAM_SCM_SCCP_CSS_CONFIG:

       ScmSccpCssConfig = (OamScmSccpCssConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'SCCP_CSS_CONFIG' 'ssId[%d] CssId[%d] '\n",
                  (operation == SCM_ADD?"ADD":"DELETE"),
                 ScmSccpCssConfig->ssId, ScmSccpCssConfig->cssId);
       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+2) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? SCCP_SM_ADD_CSS : SCCP_SM_DEL_CSS); 
               Length = (8+8);
               form_maptcap_header(cmd_buff, SCCP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

               
               EXTRACT_32( 8, ScmSccpCssConfig->ssId  ,  cmd_buff);
               EXTRACT_32( 12, ScmSccpCssConfig->cssId  ,  cmd_buff);

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }
             
        break;

   case OAM_SCM_SCCP_CSP_CONFIG:
      
       ScmSccpCspConfig = (OamScmSccpCspConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'SCCP_CSP_CONFIG' 'ssId[%d] CspId[%d] profile[%d] '\n",
                 (operation == SCM_ADD?"ADD":"DELETE"),
                 ScmSccpCspConfig->ssId,  ScmSccpCspConfig->cspId,  ScmSccpCspConfig->timerProfileId);
       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+7) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? SCCP_SM_ADD_CSP : SCCP_SM_DEL_CSP); 
               Length = (8+28);
               form_maptcap_header(cmd_buff, SCCP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

               
               ret_val = GetSccpTmrConfigData(&ScmSccpTmrConfig, ScmSccpCspConfig->timerProfileId);
               if(ret_val == 0)
                {
                  EXTRACT_32(  8,  ScmSccpCspConfig->ssId,  cmd_buff);
                  EXTRACT_32( 12, ScmSccpCspConfig->cspId,  cmd_buff);

                  EXTRACT_32( 16, ScmSccpTmrConfig->treass     , cmd_buff);
                  EXTRACT_32( 20, ScmSccpTmrConfig->tstatinfo  , cmd_buff);
                  EXTRACT_32( 24, ScmSccpTmrConfig->tcongattack, cmd_buff);
                  EXTRACT_32( 28, ScmSccpTmrConfig->tcongdecay , cmd_buff);
                  EXTRACT_32( 32, ScmSccpTmrConfig->segparmz   , cmd_buff);

                  if(ScmSccpTmrConfig != NULL)
                   {
                        free(ScmSccpTmrConfig);
                        ScmSccpTmrConfig = NULL;
                   }
                }
               else
                {
                 SCM_printf(SCM_MAJOR,"DB READ FAILURE ERR_CODE %d\n", ret_val);
                 if(g_parameter.config_flag == SS7_FALSE) /*IF CMD NOT FROM DB*/
                  {
                     send_resp_to_oam(SCM_OAM_SCCP_CSP_CONFIG_RESP, 0, ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare, UNKNOWN_CAUSE,
                                         NULL, resp_len, APP_ID_OAM);
                  }
                 return 0;
                }

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }
        
        break;

   case OAM_SCM_SCCP_TMR_CONFIG:
 
       ScmSccpTmrConfig = (OamScmSccpTmrConfig *)msg_buff;
       switch(operation)
         {
          case SCM_ADD:
               SCM_printf(SCM_MAJOR,"SCM RECV SCCP_TMR_ADD CMD ...SEND RESP TO OAM\n");
               send_resp_to_oam(SCM_OAM_SCCP_TMR_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                           ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_SIGTRAN);

               return 0;/*command not replicate at peer*/
          break;

          case SCM_MODIFY:
               noe    = (3+7) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = SCCP_SM_ADD_CSP; 
               Length = (8+28);
               form_maptcap_header(cmd_buff, SCCP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);
         
               ret_val = GetSccpCspToReconfig( &ScmSccpCspConfig , ScmSccpTmrConfig->profileId);
       
               if(ret_val == 0)
                {
                      EXTRACT_32( 8,  ScmSccpCspConfig->ssId ,  cmd_buff);
                      EXTRACT_32( 12, ScmSccpCspConfig->cspId,  cmd_buff);


                      SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN 'SCCP_TMR_CONFIG/ CSP_RECONFIG' 'profileId[%d] treass[%d] ssId[%d]\n",
                            ScmSccpTmrConfig->profileId, ScmSccpTmrConfig->treass, ScmSccpCspConfig->ssId);
              
                      if(ScmSccpCspConfig != NULL)
                      {
                         free(ScmSccpCspConfig);
                         ScmSccpCspConfig=NULL;
                      }


                      EXTRACT_32( 16, ScmSccpTmrConfig->treass      ,  cmd_buff);
                      EXTRACT_32( 20, ScmSccpTmrConfig->tstatinfo   ,  cmd_buff);
                      EXTRACT_32( 24,  ScmSccpTmrConfig->tcongattack,  cmd_buff);
                      EXTRACT_32( 28,  ScmSccpTmrConfig->tcongdecay ,  cmd_buff);
                      EXTRACT_32( 32,  ScmSccpTmrConfig->segparmz   ,  cmd_buff);

                      start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
                      ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
                }
               else
                {
                   SCM_printf(SCM_MAJOR,"DB QUERY SCCP CSP TABLE NOT PRESENT ret[%d]\n", ret_val);
                   SCM_printf(SCM_MAJOR,"SKIP SENDING CSP RECONFIG COMMAND\n");
                   if(g_parameter.config_flag == 0)
                    {
                       send_resp_to_oam(SCM_OAM_SCCP_TMR_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                  ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_OAM);

                    }
                   return 0;
                }
               
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }

         break;
   
 
   case OAM_SCM_SCTP_INIT_CONFIG:
        
       ScmSctpInitConfig = (OamScmSctpInitConfig*)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN 'SCTP_INIT_CONFIG' 'Maxend_pt[%d] local_IP[%s] OutStream[%d] '\n",
                 ScmSctpInitConfig->max_endpoint, ScmSctpInitConfig->local_IP, ScmSctpInitConfig->num_out_streams);
       
       noe    = (3+12) ;  
       ctgry  = SS7_SM_CTRL;
       cmd    = SCTP_API_INIT_STACK_REQ; 
       Length = (8+57);
       form_maptcap_header(cmd_buff, SCTP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

         
        EXTRACT_16(  8, (g_parameter.slot_id-2)           ,  cmd_buff);
        EXTRACT_32( 10, ScmSctpInitConfig->max_endpoint           ,  cmd_buff);
        EXTRACT_32( 14, ScmSctpInitConfig->max_tcb                ,  cmd_buff);
        EXTRACT_32( 18, ScmSctpInitConfig->max_per_assoc_streams  ,  cmd_buff);
        EXTRACT_32( 22, ScmSctpInitConfig->max_per_assoc_tx_buffer,  cmd_buff);
        EXTRACT_32( 26, ScmSctpInitConfig->max_per_assoc_rx_buffer,  cmd_buff);
        memcpy(&(cmd_buff[30]), ScmSctpInitConfig->local_IP, strlen(ScmSctpInitConfig->local_IP));
        EXTRACT_32( 55, ScmSctpInitConfig->stack_type,  cmd_buff);
        cmd_buff[59] = ScmSctpInitConfig->ecn_capable;
        cmd_buff[60] = ScmSctpInitConfig->pmtu_capable;
        EXTRACT_16(61,  ScmSctpInitConfig->num_in_streams, cmd_buff);
        EXTRACT_16(63,  ScmSctpInitConfig->num_out_streams, cmd_buff);
     
        
        start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
        ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
     break;
 
  case OAM_SCM_SCTP_GEN_CONFIG:
        
       ScmSctpConfig = (OamScmSctpConfig*)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'SCTP_GEN_CONFIG' ' assoc_max[%d] path_max[%d] max_init[%d] profile[%d] '\n",
                  (operation == SCM_ADD?"ADD":"MODIFY"),
                 ScmSctpConfig->assoc_max_retrans, ScmSctpConfig->path_max_retrans,ScmSctpConfig->max_init_retrans,
                 ScmSctpConfig->timerProfileId);
       switch(operation)
         {
          case SCM_ADD:
          case SCM_MODIFY:
               noe    = (3+10) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = SCTP_API_CONFIG_STACK_PARAMS_REQ; 
               Length = (8+40);
               form_maptcap_header(cmd_buff, SCTP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

                ret_val =GetSctpTimerData(&ScmSctpTmrConfig);
                if(ret_val == 0)
                 {
                     EXTRACT_32(  8, ScmSctpConfig->assoc_max_retrans  ,  cmd_buff);
                     EXTRACT_32( 12, ScmSctpConfig->path_max_retrans   ,  cmd_buff);
                     EXTRACT_32( 16, ScmSctpConfig->max_init_retrans   ,  cmd_buff);
                     
                     EXTRACT_32( 20  ,ScmSctpTmrConfig->rto_init          , cmd_buff);
                     EXTRACT_32( 24 ,ScmSctpTmrConfig->rto_min           , cmd_buff);
                     EXTRACT_32( 28 ,ScmSctpTmrConfig->rto_max           , cmd_buff);
                     EXTRACT_32( 32 ,ScmSctpTmrConfig->rto_alpha_percent , cmd_buff);
                     EXTRACT_32( 36 ,ScmSctpTmrConfig->rto_beta_percent, cmd_buff);
                     EXTRACT_32( 40 ,ScmSctpTmrConfig->valid_cookie_life , cmd_buff);
                     EXTRACT_32( 44 ,ScmSctpTmrConfig->hb_interval       , cmd_buff);
                     SCM_printf(SCM_MAJOR,"TIMER rto_min[%d] rtomax[%d] ... hb_int[%d]'\n",
                     ScmSctpTmrConfig->rto_min, ScmSctpTmrConfig->rto_max, ScmSctpTmrConfig->hb_interval);

                     if(ScmSctpTmrConfig != NULL)
                       {
                           free(ScmSctpTmrConfig);
                           ScmSctpTmrConfig=NULL;
                       }
                 }
                else
                 {
                      SCM_printf(SCM_MAJOR,"DB QUERY SCTP TIMER FAILURE  ErrCode=%d\n", ret_val);
                      SCM_printf(SCM_MAJOR,"SCTP CONFIG MOFIFY COMMAND FAILURE");
                      if(g_parameter.config_flag == 0)
                       {
                          send_resp_to_oam(SCM_OAM_SCTP_GEN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                ((ScmHdr *)msg_buff)->spare , UNKNOWN_CAUSE, NULL, resp_len, APP_ID_OAM);

                       }
                      return 0;

                  }
               
               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }
                 
       break;
  
  case OAM_SCM_SCTP_TIMER_CONFIG:
       ScmSctpTmrConfig  = (OamScmSctpTimerConfig*)msg_buff;
       switch(operation)
         {
          case SCM_ADD:
               SCM_printf(SCM_MAJOR,"SCM RECV SCTP_TIMER_ADD CMD...SEND RESP TO OAM\n");
               send_resp_to_oam(SCM_OAM_SCTP_TIMER_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                          ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_SIGTRAN);
                
               return 0;/*command not replicate at peer*/
          break;

          case SCM_MODIFY:
               noe    = (10+3) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = SCTP_API_CONFIG_STACK_PARAMS_REQ; 
               Length = (8+40);
               form_maptcap_header(cmd_buff, SCTP_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

               ret_val = GetSctpConfigData(&ScmSctpConfig, &row_count);
               if(ret_val==0 && row_count == 1)
                {
                   EXTRACT_32( 8,  ScmSctpConfig->assoc_max_retrans ,cmd_buff);
                   EXTRACT_32(12,  ScmSctpConfig->path_max_retrans  ,cmd_buff);
                   EXTRACT_32(16,  ScmSctpConfig->max_init_retrans  ,cmd_buff);

                   if(ScmSctpConfig != NULL)
                    {
                        free(ScmSctpConfig);
                        ScmSctpConfig=NULL;
                    }

                   SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN 'RECONFIG_SCTP_COMMAND' 'profile_id[%d] '", ScmSctpTmrConfig->profileId);
   
                     EXTRACT_32( 20 ,ScmSctpTmrConfig->rto_init          , cmd_buff);
                     EXTRACT_32( 24 ,ScmSctpTmrConfig->rto_min           , cmd_buff);
                     EXTRACT_32( 28 ,ScmSctpTmrConfig->rto_max           , cmd_buff);
                     EXTRACT_32( 32 ,ScmSctpTmrConfig->rto_alpha_percent , cmd_buff);
                     EXTRACT_32( 36 ,ScmSctpTmrConfig->rto_beta_percent  , cmd_buff);
                     EXTRACT_32( 40 ,ScmSctpTmrConfig->valid_cookie_life , cmd_buff);
                     EXTRACT_32( 44 ,ScmSctpTmrConfig->hb_interval       , cmd_buff);
 

                }
               else
                {
                   SCM_printf(SCM_MAJOR,"DB QUERY SCTP CONFIG TABLE NOT PRESENT ret [%d] row [%d]\n", ret_val, row_count);
                   SCM_printf(SCM_MAJOR,"SKIP SENDING SCTP RECONFIG COMMAND\n");
                   if(g_parameter.config_flag == 0)
                    {
                       send_resp_to_oam(SCM_OAM_SCTP_TIMER_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                  ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_OAM);

                    }
                   return 0;
                }


               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }
      
       break;

  case OAM_SCM_M3UA_INIT_CONFIG:

       ScmM3uaInitConfig = (OamScmM3uaInitConfig*)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN 'M3UA_INIT_CONFIG' 'max: sp[%d] Rem_sp[%d] as[%d] conn[%d] nw_identity[%d]'",
                   ScmM3uaInitConfig->max_sp, ScmM3uaInitConfig->max_remote_sp, ScmM3uaInitConfig->max_as,
                  ScmM3uaInitConfig->max_conn, ScmM3uaInitConfig->default_nw_identity);

       noe    = (3+9) ;  
       ctgry  = SS7_SM_CTRL;
       cmd    = M3UA_SM_STACK_INIT; 
       Length = (8+24);
       form_maptcap_header(cmd_buff, M3UA_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);
              
       EXTRACT_32(  8, ScmM3uaInitConfig->max_sp                ,  cmd_buff);
       EXTRACT_32( 12, ScmM3uaInitConfig->max_remote_sp         ,  cmd_buff);
       EXTRACT_16( 16, ScmM3uaInitConfig->max_as                ,  cmd_buff);
       EXTRACT_16( 18, ScmM3uaInitConfig->max_remote_as         ,  cmd_buff);
       EXTRACT_16( 20, ScmM3uaInitConfig->max_sg                ,  cmd_buff);
       EXTRACT_32( 22, ScmM3uaInitConfig->max_conn              ,  cmd_buff);
       EXTRACT_16( 26, ScmM3uaInitConfig->max_user_parts_per_asp,  cmd_buff);
       EXTRACT_16( 28, ScmM3uaInitConfig->default_standard_type ,  cmd_buff);
       EXTRACT_16( 30, ScmM3uaInitConfig->default_nw_identity   ,  cmd_buff);

       start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);

       break;

  case OAM_SCM_M3UA_LOCAL_ASP_CONFIG:
    
       ScmM3uaLocAspConfig = (OamScmM3uaLocalAspConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'LOCAL_ASP_CONFIG' 'AspId[%d] port[%d] SlotId[%d]  loc_ip[%s] \n",
                  (operation == SCM_ADD?"ADD":"DEL"),
                  ScmM3uaLocAspConfig->localAspId, ScmM3uaLocAspConfig->localPort, ScmM3uaLocAspConfig->slotId,
                  ScmM3uaLocAspConfig->localIp);

       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+8) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? M3UA_SM_ADD_ASP : M3UA_SM_DEL_ASP); 
               Length = (8+62);
               form_maptcap_header(cmd_buff, M3UA_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

               EXTRACT_16(  8, ScmM3uaLocAspConfig->localAspId   ,  cmd_buff);
               EXTRACT_16( 10, ScmM3uaLocAspConfig->localPort    ,  cmd_buff);
               memcpy(&(cmd_buff[12]), ScmM3uaLocAspConfig->localIp ,strlen(ScmM3uaLocAspConfig->localIp)); /*IP PAcking Ditto*/
               memcpy(&(cmd_buff[37]), ScmM3uaLocAspConfig->name    ,strlen(ScmM3uaLocAspConfig->name));
               EXTRACT_16( 62, ScmM3uaLocAspConfig->slotId       ,  cmd_buff);
               EXTRACT_16( 64, ScmM3uaLocAspConfig->assocType    ,  cmd_buff);
               EXTRACT_16( 66, ScmM3uaLocAspConfig->maxInStream  ,  cmd_buff);
               EXTRACT_16( 68, ScmM3uaLocAspConfig->maxOutStream ,  cmd_buff);

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }

       break;
       
  case OAM_SCM_M3UA_REMOTE_ASP_CONFIG:
  
       ScmM3uaRemAspConfig = (OamScmM3uaRemoteAspConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'REMOTE_ASP_CONFIG' 'AspId[%d] port[%d] rem_ip[%s] \n",
                  (operation == SCM_ADD?"ADD":"DEL"),
                  ScmM3uaRemAspConfig->remAspId, ScmM3uaRemAspConfig->remotePort, ScmM3uaRemAspConfig->remoteIp);
 
       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+4) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? M3UA_SM_ADD_REMOTE_ASP : M3UA_SM_DEL_REMOTE_ASP); 
               Length = (8+54);
               form_maptcap_header(cmd_buff, M3UA_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

               EXTRACT_16(  8        , ScmM3uaRemAspConfig->remAspId    ,  cmd_buff);
               memcpy(&(cmd_buff[10]), ScmM3uaRemAspConfig->name        ,strlen(ScmM3uaRemAspConfig->name));
               EXTRACT_16( 35        , ScmM3uaRemAspConfig->remotePort  ,  cmd_buff);
               memcpy(&(cmd_buff[37]), ScmM3uaRemAspConfig->remoteIp    ,strlen(ScmM3uaRemAspConfig->remoteIp));

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }

      break;

  case OAM_SCM_M3UA_LOCAL_AS_CONFIG:
 
       ScmM3uaLocAsConfig = (OamScmM3uaLocalAsConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'LOCAL_AS_CONFIG' 'AsId[%d] asmode[%d] Numbasp[%d] NumbRc[%d] \n",
                  (operation == SCM_ADD?"ADD":"DEL"),
                  ScmM3uaLocAsConfig->localAsId, ScmM3uaLocAsConfig->asMode, ScmM3uaLocAsConfig->numAsp, 
                  ScmM3uaLocAsConfig->numbRc);
    
       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+10) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? M3UA_SM_ADD_AS : M3UA_SM_DEL_AS); 
               Length = (8+28);
               form_maptcap_header(cmd_buff, M3UA_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);

               EXTRACT_16(  8   , ScmM3uaLocAsConfig->localAsId       ,  cmd_buff);
               EXTRACT_32( 10   , ScmM3uaLocAsConfig->asMode          ,  cmd_buff);
               EXTRACT_32( 14   , ScmM3uaLocAsConfig->sourcePointCode ,  cmd_buff);
               EXTRACT_32( 18   , ScmM3uaLocAsConfig->rkType          ,  cmd_buff);

               cmd_buff[22] = ScmM3uaLocAsConfig->numAsp;
               EXTRACT_16( 23   , ScmM3uaLocAsConfig->localAspId1     ,  cmd_buff);
               EXTRACT_16( 25   , ScmM3uaLocAsConfig->localAspId2     ,  cmd_buff);

               cmd_buff[27] =ScmM3uaLocAsConfig->numbRc;  
               EXTRACT_32( 28   , ScmM3uaLocAsConfig->remAspRc1       ,  cmd_buff);
               EXTRACT_32( 32   , ScmM3uaLocAsConfig->remAspRc2       ,  cmd_buff);

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }
 
       break;

  case OAM_SCM_M3UA_REMOTE_AS_CONFIG:
 
       ScmM3uaRemAsConfig = (OamScmM3uaRemoteAsConfig *)msg_buff;
       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN %s 'REMOTE_AS_CONFIG' 'remAsId[%d] remPC[%d] numbAsp[%d] remAspId1[%d] \n",
                  (operation == SCM_ADD?"ADD":"DEL"),
                  ScmM3uaRemAsConfig->remAsId, ScmM3uaRemAsConfig->remPointCode, ScmM3uaRemAsConfig->numAsp, 
                  ScmM3uaRemAsConfig->remAspId1);
 
       switch(operation)
         {
          case SCM_ADD:
          case SCM_DELETE:
               noe    = (3+11) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = ((operation == SCM_ADD) ? M3UA_SM_ADD_REMOTE_AS : M3UA_SM_DEL_REMOTE_AS); 
               Length = (8+27);
               form_maptcap_header(cmd_buff, M3UA_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);


               ret_val = GetM3uaTmrConfigData(&ScmM3uaTimerConfig, ScmM3uaRemAsConfig->timerProfileId);
               if(ret_val == 0)
                {
                     EXTRACT_16(  8   , ScmM3uaRemAsConfig->remAsId     , cmd_buff);
                     EXTRACT_32( 10   , ScmM3uaRemAsConfig->remAsMode   ,  cmd_buff);
                     EXTRACT_32( 14   , ScmM3uaRemAsConfig->remPointCode,  cmd_buff);
                     EXTRACT_32( 18   , ScmM3uaRemAsConfig->rkType      ,  cmd_buff);
                     cmd_buff[22]= ScmM3uaRemAsConfig->numAsp;
                     EXTRACT_16( 23   , ScmM3uaRemAsConfig->remAspId1   ,  cmd_buff);
                     EXTRACT_16( 25   , ScmM3uaRemAsConfig->remAspId2   ,  cmd_buff);

                     EXTRACT_16(  27   ,  ScmM3uaTimerConfig->tmrAsPend     ,  cmd_buff);
                     EXTRACT_16(  29   , ScmM3uaTimerConfig->tmrRetransLow  ,  cmd_buff);
                     EXTRACT_16(  31   ,ScmM3uaTimerConfig->tmrRetransHigh  ,  cmd_buff);
                     EXTRACT_16(  33   ,  ScmM3uaTimerConfig->tmrRetransMax ,  cmd_buff);                                        
                                          
                     if(ScmM3uaTimerConfig != NULL)
                      {
                          free(ScmM3uaTimerConfig);
                          ScmM3uaTimerConfig = NULL;
                      }
                                          
                }
              else
                {
                     SCM_printf(SCM_MAJOR,"DB QUERY M3UA TIMER FAILURE  ErrCode=%d\n", ret_val);
                     SCM_printf(SCM_MAJOR,"M3UA REMOTE AS CONFIG COMMAND FAILURE\n");
                     if(g_parameter.config_flag == 0)
                      {
                         send_resp_to_oam(SCM_OAM_M3UA_REMOTE_AS_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                               ((ScmHdr *)msg_buff)->spare , UNKNOWN_CAUSE, NULL, resp_len, APP_ID_OAM);

                      }
                     return 0;

                 }

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }

       break;
  
  case OAM_SCM_M3UA_TIMER_CONFIG:
       ScmM3uaTimerConfig = (OamScmM3uaTimerConfig *)msg_buff;
     
       switch(operation)
         {
          case SCM_ADD:
               SCM_printf(SCM_MAJOR,"SCM RECV M3UA_TIMER_ADD CMD...SEND RESP TO OAM\n");
               send_resp_to_oam(SCM_OAM_M3UA_TIMER_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                          ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_SIGTRAN);
               return 0;/*Command not replicate at peer*/
          break;
          case SCM_MODIFY:
               noe    =(3+11) ;  
               ctgry  = SS7_SM_PROV;
               cmd    = M3UA_SM_ADD_REMOTE_AS; 
               Length = (8+27);
               form_maptcap_header(cmd_buff, M3UA_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);
 
               ret_val = GetRemoteAsConfigData(&ScmM3uaRemAsConfig, &row_count);
       
               if(ret_val == 0 && row_count == 1)
                {  
                     EXTRACT_16(  8   , ScmM3uaRemAsConfig->remAsId     , cmd_buff);
                     EXTRACT_32( 10   , ScmM3uaRemAsConfig->remAsMode   ,  cmd_buff);
                     EXTRACT_32( 14   , ScmM3uaRemAsConfig->remPointCode,  cmd_buff);
                     EXTRACT_32( 18   , ScmM3uaRemAsConfig->rkType      ,  cmd_buff);
                     cmd_buff[22]= ScmM3uaRemAsConfig->numAsp;
                     EXTRACT_16( 23   , ScmM3uaRemAsConfig->remAspId1   ,  cmd_buff);
                     EXTRACT_16( 25   , ScmM3uaRemAsConfig->remAspId2   ,  cmd_buff);

                     EXTRACT_16(  27   , ScmM3uaTimerConfig->tmrAsPend      ,  cmd_buff);
                     EXTRACT_16(  29   , ScmM3uaTimerConfig->tmrRetransLow  ,  cmd_buff);
                     EXTRACT_16(  31   , ScmM3uaTimerConfig->tmrRetransHigh ,  cmd_buff);
                     EXTRACT_16(  33   , ScmM3uaTimerConfig->tmrRetransMax  ,  cmd_buff);

       
                       SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN 'RECONFIG_REMOTE_AS' 'remAsId[%d] remPC[%d] numbAsp[%d] profile_ID[%d] \n",
                                 ScmM3uaRemAsConfig->remAsId, ScmM3uaRemAsConfig->remPointCode, ScmM3uaRemAsConfig->numAsp,
                                 ScmM3uaTimerConfig->profileId);
               
                       if(ScmM3uaRemAsConfig != NULL)
                        { 
                             free(ScmM3uaRemAsConfig);
                             ScmM3uaRemAsConfig = NULL;
                        }
                 
                 }
                else
                 {
                       SCM_printf(SCM_MAJOR,"DB QUERY REMOTE AS NOT FOUND ret [%d] row_count [%d] \n", ret_val, row_count);
                       SCM_printf(SCM_MAJOR,"SKIP SENDING REM_AS_RECONFIG COMMAND \n");
                       if(g_parameter.config_flag == 0)
                         {
                           send_resp_to_oam(SCM_OAM_M3UA_TIMER_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                   ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_OAM);
                         }
                       return 0;
                 }

               start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
               ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
          break;
          default:
               SCM_printf(SCM_MAJOR,"INVALID OPERATION *********\n")
          break;
         }
    
       break;

  case OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG: 
       ScmM3uaLAspAdminCfg = (OamScmM3uaLocalAspAdminConfig *)msg_buff;

       /* TEMP_CHANGES if(g_parameter.redundant_status == SCM_ACTIVE && g_parameter.noOam_resp_flag == 0)*/
       if(g_parameter.redundant_status == SCM_ACTIVE)
        { 
            cmd_state = check_self_or_peer_admin_cmd(ScmM3uaLAspAdminCfg->localAspId); /*only ACTIVE card CHECKS*/
        }

       if(cmd_state == PEER_CMD)             /*send cmd to peer*/
        {
             if(g_parameter.data_pull_up == 1 && g_parameter.nwstk_cfgIndFromPeerCard == 1 )/*standby data pull ind and config complete received*/
               {
                  Length = sizeof(OamScmM3uaLocalAspAdminConfig);
                  memcpy(cmd_buff, ScmM3uaLAspAdminCfg, Length);
                  /*NEED PRINT HERE*/
                  SCM_printf(SCM_MAJOR,"SCM -> PEER_SCM || SIGTRAN 'LOCAL_ASP_ADMIN_CONFIG' 'LOCAspId[%d] AdminState[%d #%s]\n",
                              ScmM3uaLAspAdminCfg->localAspId, ScmM3uaLAspAdminCfg->adminState, 
                              ((ScmM3uaLAspAdminCfg->adminState == 1)? "UNLOCK" : "LOCK"));
                  form_oam_header( cmd_buff, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG, (ScmM3uaLAspAdminCfg->scmhdr.operation), 0, 0,Length);
                  
                  start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
                  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_PEER_SCM, Length); 
          
                  if(g_parameter.config_flag == 0 && ret_val == 0) /*failure*/
                   {
                     stop_timer(TIMER_SIGTRAN);
                     send_resp_to_oam(SCM_OAM_M3UA_LOCAL_ASP_ADMIN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                         ((ScmHdr *)msg_buff)->spare , UNKNOWN_CAUSE, NULL, resp_len, APP_ID_OAM);
                   }
                  return ret_val; 
               }
              else
               {
                 SCM_printf(SCM_MAJOR,"ADMIN_CONFIG cmd to PEER SKIPPED 'data_pull[%d] Peer_card_conf[%d] AdminState[%d #%s]'\n", 
                                       g_parameter.data_pull_up, g_parameter.nwstk_cfgIndFromPeerCard, ScmM3uaLAspAdminCfg->adminState,
                                         ((ScmM3uaLAspAdminCfg->adminState == 1)? "UNLOCK" : "LOCK"));
                 send_resp_to_oam(SCM_OAM_M3UA_LOCAL_ASP_ADMIN_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                         ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_OAM);
                 g_parameter.config_cmd_resp = 0;
                 return 0;
               }
         }
       else                                                           /*Standy and Active SAME LEG*/                                                 
         {  
                  noe    = (3+2) ;  
                  ctgry  = SS7_SM_CTRL;
                  cmd    = ((ScmM3uaLAspAdminCfg->adminState == 1)? M3UA_SM_CONNECT : M3UA_SM_DISCONNECT); 
                  Length = (8+3);
                  form_maptcap_header(cmd_buff, M3UA_SM_REQUEST_API,  noe, ctgry, transaction_Id[tr_opcode],cmd, Length);
                             
                  EXTRACT_16( 8, ScmM3uaLAspAdminCfg->localAspId  ,  cmd_buff);
                  cmd_buff[10] = ScmM3uaLAspAdminCfg->adminState;

                  /*MANTIS Id:- 0032193*/
                  if((ScmM3uaLAspAdminCfg->adminState == 1) && g_parameter.redundant_status == SCM_STANDBY)
                    {
                     SCM_printf(SCM_MAJOR,"M3UA_CONN_DOWN Alarm Resp Marked RECVD\n");
                     g_parameter.Conn_Down_alarm_Resp_Pending = 0; 
                    }
                  /*MANTIS End*/ 
                  SCM_printf(SCM_MAJOR,"SCM -> SIGTRAN SELF 'LOCAL_ASP_ADMIN_CONFIG' 'LOCAspId[%d] AdminState[%d #%s]\n",
                              ScmM3uaLAspAdminCfg->localAspId, ScmM3uaLAspAdminCfg->adminState,
                              ((ScmM3uaLAspAdminCfg->adminState == 1)? "UNLOCK" : "LOCK"));
                
                  start_timer (TIMER_SIGTRAN, APP_ID_SIGTRAN, transaction_Id[tr_opcode], msg_buff);
                  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_SIGTRAN, Length);
       }
   
      break;
      /*AOIP: SIGTRAN COMMANDS END */
       
  default:
      SCM_printf (SCM_MAJOR, "COMMAND TYPE IS NOT IMPLEMENTED AT SCM");
      SCM_printf (SCM_MAJOR, "UNKNOWN OPCODE*** %d\n", opcode);
      send_resp_to_oam(  0, 0, ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare, ERROR_WRONG_OPCODE, 
                                NULL, resp_len, APP_ID_OAM);
      return 0;
      break;

    }  

   if(ret_val == 0)
   {
    stop_timer (TIMER_SIGTRAN);
    g_parameter.config_cmd_resp = 0;
    SCM_printf (SCM_CRITICAL, "COMMAND SENT TO SIGTRAN FAILED\n"); /*AOIP: PRINT UPDATED*/
    /*IF FROM OAM THEN MAY SEND RESP TO OAM*/
    return 0;
   }
  if(g_parameter.config_flag == 1)
  {
   g_parameter.config_cmd_resp = 1;
  }
      return ret_val; 
 }

int self_link_rollback( U8* msg_buff )
{
 U8  hdrsize, family, operation;
 U32 opc;
 U16 Length, resp_len;
 U8 timeslot;
 resp_len = sizeof(ScmOamResponse); 
 signed int ret_val = 0;
 S32 dbSts;
 U16 opcode, tr_opcode;
 opcode = ((ScmHdr *)msg_buff)->opcode;
 tr_opcode = opcode - BASE_OPCODE_SCM;
 hdrsize = 5;
 U8 cmd_buff[100];
 family  = g_parameter.family;
 opc     = g_parameter.opc_value;
 strcpy(g_parameter.function_string, "process_nw_stack_cmd()");
 operation = ((ScmHdr *)msg_buff)->operation;
 ScmNwstkLinkConfig    NwstkLinkConfig;

 scmLinkConfig  = (OamScmLinkConfig*)msg_buff;
 Length            = sizeof(ScmNwstkLinkConfig);
 if(g_parameter.slot_id == 3)    
 {
   if(scmLinkConfig->cardNum == 3)
   { 
     NwstkLinkConfig.instanceID = 65524;
   }
   else
   if(scmLinkConfig->cardNum == 4) 
   {
    NwstkLinkConfig.instanceID = 20002;
   } 
   else
   {
    SCM_printf(SCM_CRITICAL," link config cmd failed: cause WRONG CARD NUM")
      return 0;
   }
  }  
  else  
  if(g_parameter.slot_id == 4)
  {
    if(scmLinkConfig->cardNum == 3)
    {
     NwstkLinkConfig.instanceID = 20002;
    }  
    else
    if( scmLinkConfig->cardNum == 4 )
    {
      NwstkLinkConfig.instanceID = 65524;
      if( g_parameter.family  == ANSI_FAMILY)
      {
       NwstkLinkConfig.instanceID = 65525;
      }
    }
    else
    {
      SCM_printf(SCM_CRITICAL," link config cmd failed: cause WRONG CARD NUM")
      return 0;
    }
  }
  else
  {
    SCM_printf(SCM_CRITICAL,"LINK CONFIG CMD FAILURE : wrong slot id");
  }
               
   NwstkLinkConfig.linkId     = scmLinkConfig->linkId;
   NwstkLinkConfig.linkSetId  = scmLinkConfig->linkSetId;
   //    NwstkLinkConfig.trunkNum   = scmLinkConfig->trunkNum;
   SCM_printf(SCM_INFO,"DB QUERY FOR STREAM TIME SLOT for TrkNum=%d,TrkTs=%d", scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
   dbSts = GetDstStreamTsConfigDataWithTrunkAndTimeslot( &timeslot, scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
        
   if(dbSts == 0)
    { 
     if((timeslot%2) != 0 )
     {
      SCM_printf(SCM_MAJOR," Link cmd failure: cause: 'ODD VALUE OF TIMESLOT i.e.: %d IN DB FOR DEST STREAM MAPPING'", timeslot);
      return 0;
     }
      // NOT  REQUIRED  timeslot = timeslot * 2;/* temporary fix for mcc dest stream time slot */ 
     NwstkLinkConfig.timeSlot   = timeslot;
     NwstkLinkConfig.cardNum    = scmLinkConfig->cardNum;
     NwstkLinkConfig.crcFlag    = scmLinkConfig->crcFlag;
     memcpy(cmd_buff, &NwstkLinkConfig, Length);
     if(operation == SCM_DELETE)
     {
      SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINK_DEL:' ln: %d, ls: %d, strmTs: %d, instance: %d",
                       scmLinkConfig->linkId, scmLinkConfig->linkSetId, timeslot,NwstkLinkConfig.instanceID);
      form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_DEL,
                        transaction_Id[SCM_NWSTK_LINK_ADD], Length);
      ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
     }
     else
     { 
       SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINK_ADD:' ln: %d, ls: %d, strmTs: %d, instance: %d",
                 scmLinkConfig->linkId, scmLinkConfig->linkSetId, timeslot,NwstkLinkConfig.instanceID);
       form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_ADD,
                        transaction_Id[SCM_NWSTK_LINK_ADD], Length);
       ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
     }   
     /* here take decision on the bases of card no msg goes to self nwstk or peer*/
     if(ret_val > 0)
     {
      g_linkConfigValue.link_value = NwstkLinkConfig.linkId;
      g_linkConfigValue.linkSetId  = NwstkLinkConfig.linkSetId; 
      g_linkConfigValue.instaceId  = NwstkLinkConfig.instanceID;
     }
    }
    else
    {
     SCM_printf(SCM_MAJOR,"DB QUERY FOR STREAM TIME SLOT FAILURE TrkNum=%d,TrkTs=%d", scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
     return 0;
    }  
 
   return 1;
}

/*AOIP: FUNCTION*/
I_S32 process_bssap_stack_cmd(U8* msg_buff)
{

  U8 cmd_buff[100], operation;
  U16 Length, resp_len; /*check*/ 
  U16 opcode, tr_opcode;
  U32 ret_val = 0;
  opcode = ((ScmHdr *)msg_buff)->opcode;
  operation = ((ScmHdr *)msg_buff)->operation;
  
  /*tr_opcode = opcode - BASE_OPCODE_SCM;*/
  tr_opcode = opcode - BASE_OPCODE_SCM_AOIP;

  ScmBsInterfaceConfig    NwstkBssapcfgConfig;
  OamScmBsTimerConfig     *BssapTimerTable = NULL;
  
  resp_len = sizeof(ScmOamResponse);

  if( g_parameter.config_flag == SS7_FALSE)
  {
   oam_transaction_Id[tr_opcode].transaction_Id = ((ScmHdr *)msg_buff)->trid;      /*store oam trid */
   oam_transaction_Id[tr_opcode].operation      = ((ScmHdr *)msg_buff)->operation; /*store oam operation */
   oam_transaction_Id[tr_opcode].pegrfu      = ((ScmHdr *)msg_buff)->spare;        /*store peg cmd indication */
  }

       
 switch(opcode)
  
 {
       case OAM_SCM_BS_INTERFACE_CONFIG:
            scmBsInterfaceConfig  = ( OamScmBsInterfaceConfig*)msg_buff;
            Length              = sizeof(ScmBsInterfaceConfig);

            NwstkBssapcfgConfig.bscId        = scmBsInterfaceConfig->bscId;
            NwstkBssapcfgConfig.interfaceType= scmBsInterfaceConfig->interfaceType;
            NwstkBssapcfgConfig.ni            = scmBsInterfaceConfig->ni;
            memcpy(NwstkBssapcfgConfig.name, scmBsInterfaceConfig->name, 20); /*20 hardcoded*/
            NwstkBssapcfgConfig.opc           = scmBsInterfaceConfig->opc;
            NwstkBssapcfgConfig.dpc           = scmBsInterfaceConfig->dpc;
            NwstkBssapcfgConfig.variant       = scmBsInterfaceConfig->variant;
      
            if(operation == SCM_ADD) /*READ DB ONLY IF ADD OPERATION*/
             {
	       ret_val = GetBsTimerTbl(&BssapTimerTable, scmBsInterfaceConfig->timerProfileId);	

	       if(ret_val == 0)
		{       
		  NwstkBssapcfgConfig.timer_T1            = BssapTimerTable->timer_T1;
		  NwstkBssapcfgConfig.timer_T4            = BssapTimerTable->timer_T4;
		  NwstkBssapcfgConfig.timer_T10           = BssapTimerTable->timer_T10;
		  NwstkBssapcfgConfig.timer_T11           = BssapTimerTable->timer_T11;
		  NwstkBssapcfgConfig.timer_T13           = BssapTimerTable->timer_T13;
		  NwstkBssapcfgConfig.timer_T17           = BssapTimerTable->timer_T17;
		  NwstkBssapcfgConfig.timer_T18           = BssapTimerTable->timer_T18;
		  NwstkBssapcfgConfig.timer_T25           = BssapTimerTable->timer_T25;
		  NwstkBssapcfgConfig.timer_Trbsc         = BssapTimerTable->timer_Trbsc;
                
                  if(BssapTimerTable != NULL)
                   {
                      free(BssapTimerTable);
                      BssapTimerTable = NULL;
                   }
	       }
	      else
               {
		   SCM_printf(SCM_MAJOR,"DB QUERY FOR BSSAP TIMER FAILURE Timer_Profile=%d\n", scmBsInterfaceConfig->timerProfileId);
		   SCM_printf(SCM_MAJOR,"BSSAP INTF CONFIG COMMAND FAILURE");
		   if(g_parameter.config_flag == 0)
		     {
			   send_resp_to_oam(SCM_OAM_BS_INTERFACE_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
			   ((ScmHdr *)msg_buff)->spare , UNKNOWN_CAUSE, NULL, resp_len, APP_ID_OAM);

		      }
		   return 0;

		 
	       }
             } 
            memcpy(cmd_buff, &NwstkBssapcfgConfig, Length);
            if(operation == SCM_DELETE)
             {
                SCM_printf(SCM_MAJOR,"SCM -> BSSAP 'INTERFACE_DEL:' interfaceType: %d, bsc_Id: %d opc: %d, dpc: %d\n",
                             scmBsInterfaceConfig->interfaceType, scmBsInterfaceConfig->bscId,  scmBsInterfaceConfig->opc,
                             scmBsInterfaceConfig->dpc);
    
                form_nwstk_header(cmd_buff, APP_ID_BS, SCM_BSSAP_INTF_DEL,
                                transaction_Id[SCM_BSSAP_INTF_ADD], Length);
             }
            else 
             if(operation == SCM_ADD)
             {
                SCM_printf(SCM_MAJOR,"SCM -> BSSAP 'INTERFACE_ADD:' interfaceType: %d, bsc_Id: %d opc: %d, dpc: %d\n",
                       scmBsInterfaceConfig->interfaceType,  scmBsInterfaceConfig->bscId, scmBsInterfaceConfig->opc,
                        scmBsInterfaceConfig->dpc);

                form_nwstk_header(cmd_buff, APP_ID_BS, SCM_BSSAP_INTF_ADD,
                        transaction_Id[SCM_BSSAP_INTF_ADD], Length);
             }
            else
             {
                SCM_printf(SCM_MAJOR,"UNKNOWN OPERATION [%d] BSSAP CMD*****\n", operation);
                send_resp_to_oam(  0, 0, ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare, UNKNOWN_CAUSE, 
                                       NULL, resp_len, APP_ID_OAM);
                return 0;
             }
            start_timer (TIMER_BSSAP, APP_ID_BS, transaction_Id[SCM_BSSAP_INTF_ADD], msg_buff);
            ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_BS, Length);
       break;

       case OAM_SCM_BS_TIMER_CONFIG:
            scmBsTimerConfig  = (OamScmBsTimerConfig*)msg_buff;
            Length              = sizeof(ScmBsInterfaceConfig);

            switch(operation)
             {
               case SCM_MODIFY:
                    NwstkBssapcfgConfig.timer_T1    = scmBsTimerConfig->timer_T1;
                    NwstkBssapcfgConfig.timer_T4    = scmBsTimerConfig->timer_T4;
                    NwstkBssapcfgConfig.timer_T10   = scmBsTimerConfig->timer_T10;
                    NwstkBssapcfgConfig.timer_T11   = scmBsTimerConfig->timer_T11;
                    NwstkBssapcfgConfig.timer_T13   = scmBsTimerConfig->timer_T13;
                    NwstkBssapcfgConfig.timer_T17   = scmBsTimerConfig->timer_T17;
                    NwstkBssapcfgConfig.timer_T18   = scmBsTimerConfig->timer_T18;
                    NwstkBssapcfgConfig.timer_T25   = scmBsTimerConfig->timer_T25;
                    NwstkBssapcfgConfig.timer_Trbsc = scmBsTimerConfig->timer_Trbsc;
  
                    /*Here fetching the particular interface corresponding to profile ID*/ 
                    ret_val = GetBssapIntfToReconfig( &scmBsInterfaceConfig, scmBsTimerConfig->profileId);
       
                    if(ret_val == 0)
                     {
                         /*Set true Indicates Reconfiguration Cmd for object to be sent*/
                          Reconf_Flag = SS7_TRUE;
                          NwstkBssapcfgConfig.bscId        = scmBsInterfaceConfig->bscId;
                          NwstkBssapcfgConfig.interfaceType= scmBsInterfaceConfig->interfaceType;
                          NwstkBssapcfgConfig.ni            = scmBsInterfaceConfig->ni;
                          memcpy(NwstkBssapcfgConfig.name, scmBsInterfaceConfig->name, 20); 
                          NwstkBssapcfgConfig.opc           = scmBsInterfaceConfig->opc;
                          NwstkBssapcfgConfig.dpc           = scmBsInterfaceConfig->dpc;
                          NwstkBssapcfgConfig.variant       = scmBsInterfaceConfig->variant;

                          memcpy(cmd_buff, &NwstkBssapcfgConfig, Length);
                          start_timer (TIMER_BSSAP, APP_ID_BS, transaction_Id[SCM_BSSAP_INTF_ADD], msg_buff);
           
                          SCM_printf(SCM_MAJOR,"SCM -> BSSAP 'TIMER CONFIG / INTERFACE_RECONFIG:' TimerProfile: %d IntfId: %d\n",
                                       scmBsTimerConfig->profileId, scmBsInterfaceConfig->bscId);
                   
                          if(scmBsInterfaceConfig != NULL) /*Need to make it free here*/
                           {
                              free(scmBsInterfaceConfig);
                              scmBsInterfaceConfig=NULL;
                           }
      
                          form_nwstk_header(cmd_buff, APP_ID_BS,  SCM_BSSAP_INTF_ADD,
                                       transaction_Id[SCM_BSSAP_INTF_ADD], Length);
  
                          ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_BS, Length);
                     }
                   else
                     {
                          SCM_printf(SCM_MAJOR,"DB QUERY BSSAP INTERFACE NOT FOUND ret[%d]\n", ret_val);
                          SCM_printf(SCM_MAJOR,"SKIP SENDING BSSAP INTF RECONFIG COMMAND\n");
                          if(g_parameter.config_flag == 0)
                           {
                             send_resp_to_oam(SCM_OAM_BS_TIMER_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                       ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_OAM);
                           } 
                          return 0;
  
                     }
               break;
             
               case SCM_ADD:
                    SCM_printf(SCM_MAJOR,"BSSAP RECV TIMER_ADD CMD.....SENDING RESP TO OAM\n");
                    send_resp_to_oam(SCM_OAM_BS_TIMER_CONFIG_RESP, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid,
                                 ((ScmHdr *)msg_buff)->spare , 0, NULL, resp_len, APP_ID_BS);
                    return 0;
               break;
             
               default:
                    SCM_printf(SCM_MAJOR,"UNKNOWN OPERATION BSSAP #$#$#$#$#\n");
                    return 0;                 
               break;
             
             }
       break;


     default:
     SCM_printf(SCM_MAJOR,"UNEXPECTED OPCODE BSSAP CMD*****\n");
     send_resp_to_oam(  0, 0, ((ScmHdr *)msg_buff)->trid , ((ScmHdr *)msg_buff)->spare, ERROR_WRONG_OPCODE, 
                                NULL, resp_len, APP_ID_OAM);
     return 0;
     break; 
 }

 if(ret_val <= 0)
 {
     g_parameter.config_cmd_resp = 0;
     stop_timer (TIMER_BSSAP);
     Reconf_Flag = SS7_FALSE;
     SCM_printf (SCM_CRITICAL, "COMMAND SEND TO BSSAP IS FAILURE");
     return 0;
 }

 if(g_parameter.config_flag == SS7_TRUE)
 {
   g_parameter.config_cmd_resp = SS7_TRUE;    /*Flag maintains cmd-resp sequence*/
 }

return 1;

}

U16 check_self_or_peer_admin_cmd (U16 rcvd_asp_id)
{
SigtranM3uaLAspConfigTableIndices  Lasp_Index;
SigtranM3uaLAspConfigTableApi     *Lasp_Tbl;
I_U16 Self = 1;
I_U16 Peer = 2;
U16 cmd_val  = 0;
I_S32 ret_val  = 0;

Lasp_Index.localAspId = rcvd_asp_id;
ret_val =  getSigtranM3uaLAspConfigTable(&Lasp_Index, &Lasp_Tbl);

SCM_printf (SCM_CRITICAL, "Check Self/Peer Adminstate cmd :: SELFSLOTID[%d] Rcvd ASPID[%d] Found ASPSLOTID[%d]\n",
             g_parameter.slot_id, rcvd_asp_id, Lasp_Tbl->slotId);

if(ret_val == 0)
{
        switch(g_parameter.slot_id)
                {
                 case SLOT_3:
                      if(Lasp_Tbl->slotId == (3-2))
                      cmd_val = Self;
                      else
                      cmd_val = Peer;
                 break;
                         
                 case SLOT_4:
                      if(Lasp_Tbl->slotId == (4-2))
                      cmd_val = Self;
                      else
                      cmd_val = Peer;
                break;
                }

}
else
{
     SCM_printf (SCM_CRITICAL, "DB QUERY FAILED ERR CODE : %d\n", ret_val);
}

if(Lasp_Tbl != NULL)
{
free(Lasp_Tbl);
Lasp_Tbl = NULL;
}

return cmd_val;
}
