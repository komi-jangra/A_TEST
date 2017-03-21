#include "scm_localhashdef.h"
#include <scm_encaps.h>

OamScmSs7StackConfig        *initConfigPtr=NULL;
sksGenConfig                *sksGenConfigPtr=NULL;
scmSksGenConfig              ssksGenConfig;
OamScmLinkSetConfig         *linksetConfigPtr=NULL;
OamScmLinkConfig            *linkConfigPtr=NULL;
OamScmSs7RouteConfig        *ss7RouteConfigPtr=NULL;
OamScmTrunkCicConfig        *trunkCicConfigPtr=NULL;
OamScmTrunkCicConfig        *trunkCicPtr=NULL;
OamScmInterfaceConfig       *interfaceConfigPtr=NULL;
OamScmMtp3TimerConfig       *mtp3TimerConfigPtr=NULL;
OamScmBssapTimerConfig      *bssapTimerConfigPtr=NULL;
OamScmSccpTimerConfig       *sccpTimerConfigPtr=NULL;
sSccpBehaviorConfigTableApi *sccpBehaviorConfigPtr=NULL;
OamScmLapdTEIConfig         *lapdTeiConfigPtr=NULL;
OamScmLapdTimerConfig       *lapdTimerConfigPtr=NULL;
#ifdef RB_GB_PHASE2
OamScmLapdSAPIConfig        *lapdSapiConfigPtr=NULL;
OamScmLapdTSConfig          *lapdTsConfigPtr=NULL;
#endif

#if 0
mapInitConfig               *mapInitConfigPtr = NULL;
OamScmMapTimerConfig        *mapTImerConfigPtr = NULL;
OamScmMapSecurityConfig     *mapSecurityConfigPtr = NULL;
#endif

/*AOIP: VARIABLES*/
OamScmBsInterfaceConfig     *BsintfConfigPtr=NULL;

OamScmSccpInitConfig           *SccpInitConfigPtr=NULL;
OamScmSccpSpConfig             *SccpSpConfigPtr=NULL;
OamScmSccpSsConfig             *SccpSsConfigPtr=NULL;
OamScmSccpCssConfig            *SccpCssConfigPtr=NULL;
OamScmSccpCspConfig            *SccpCspConfigPtr=NULL;
OamScmSccpTmrConfig            *SccpTmrConfigPtr=NULL;

OamScmSctpInitConfig           *SctpInitConfigPtr=NULL;
OamScmSctpConfig               *SctpGenConfigPtr    =NULL;

OamScmM3uaInitConfig           *M3uaInitConfigPtr=NULL;
OamScmM3uaLocalAspConfig       *M3uaLocAspConfigPtr=NULL;
OamScmM3uaRemoteAspConfig      *M3uaRemAspConfigPtr=NULL;
OamScmM3uaLocalAsConfig        *M3uaLocAsConfigPtr=NULL;
OamScmM3uaRemoteAsConfig       *M3uaRemAsConfigPtr=NULL;
/*AOIP: END*/


/*********************************************************************************/
/* This funtion fetch db table and dispatch to respective stack entity*/
/*********************************************************************************/
U8 row_count=0;
int fetch_and_send_nxt_cmd_to_stack(U8 entity)
{
     U8* msg_buff=NULL;
     U8  hdrsize, found;
     U32 ret;
     U16 len, loop, cmd; 
     S32 ret_val =0;
     
     typedef enum  {
                     O_N_E =0, T_W_O, T_H_R_E_E, F_O_U_R, F_I_V_E, S_I_X,
                     S_E_V_E_N, E_I_G_H_T, N_I_N_E, T_E_N, E_L_E_V_E_N, 
                     T_W_E_L_V_E, T_H_I_R_T_E_E_N, F_O_U_R_T_E_E_N
                   };
     hdrsize = sizeof(ScmHdr);
     strcpy(g_parameter.function_string, "fetch_and_send_nxt_cmd_to_stack()");
     ret_val = check_entiy_up(entity);
     if(ret_val != 0)
      {
       SCM_printf(SCM_MAJOR,"ENTITY TO BE CONFIGURE IS DOWN");
       return 0; 
      }

     cmd = g_parameter.no_config_cmd_sent;
     switch ( entity )
       {
        case ENT_LAPD:
             switch ( cmd )
             {
#ifdef RB_GB_PHASE2 
              case O_N_E :
                {
                  SCM_printf(SCM_MAJOR,"FATCH FROM DB: LAPD TS CONFIG  TABLE FOR LAPD"); 
                  ret_val = GetLapdTsConfigData(&lapdTsConfigPtr, &row_count);
                  if((ret_val == 0) && (row_count != 0))
                   {
                    SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
                    len = sizeof(OamScmLapdTSConfig) ;
                    msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
                    memcpy(msg_buff, &lapdTsConfigPtr[g_parameter.no_of_config_row_sent], len );
                    form_scm_header( msg_buff, OAM_SCM_LAPDTS_CONFIG, 0, 0, len);
                    g_parameter.no_of_config_row_sent++;
                    if(g_parameter.no_of_config_row_sent >= row_count)
                     {
                      ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       free(lapdTsConfigPtr);
                       lapdTsConfigPtr=NULL; 
                       msg_buff = NULL;
                      }  
                      break;
                     }
                    else
                    {
                     ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       free(lapdTsConfigPtr);
                       lapdTsConfigPtr = NULL;
                       msg_buff = NULL;
                      }  
                     if(ret == 0)
                     break;
                     else  
                      return ret_val;
                    }
                   }
                  else
                    SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
                 }  
                 break;
#endif  

              case O_N_E :
                 {
                  if(g_parameter.no_of_config_row_sent == 0)
                  {
                   SCM_printf(SCM_MAJOR,"FATCH FROM DB: LAPD TEI CONFIG  TABLE FOR LAPD"); 
                   ret_val = GetLapdTeiConfigData(&lapdTeiConfigPtr, &row_count);
                   if(ret_val == 0)
                   {   
                    SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS: row_count: %d", row_count);
                   }
                  }
                  else
                  {
                   ret_val = 0;    
                  } 
                  if((ret_val == 0) && (row_count != 0))
                   {
                    len = sizeof(OamScmLapdTEIConfig) ;
                    msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
                    memcpy(msg_buff, &lapdTeiConfigPtr[g_parameter.no_of_config_row_sent], len );
                    form_scm_header( msg_buff, OAM_SCM_LAPDTEI_CONFIG, 0, 0, len);
                    g_parameter.no_of_config_row_sent++;
                    if(g_parameter.no_of_config_row_sent >= row_count)
                     {
                      ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       free(lapdTeiConfigPtr);
                       lapdTeiConfigPtr = NULL;
                       msg_buff = NULL;
                      }  
                      break;
                     }
                    else
                    {
                     ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       // free(lapdTeiConfigPtr);
                       // lapdTeiConfigPtr = NULL;
                       msg_buff = NULL;
                      }  
                     if(ret == 0)
                     {
                      free(lapdTeiConfigPtr);
                      lapdTeiConfigPtr = NULL;
                      break;
                     }
                     else  
                      return ret_val;
                    }
                   }
                  else
                    SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
                 }  
                 break;

#ifdef RB_GB_PHASE2 
             case T_H_R_E_E :
                 {
                  SCM_printf(SCM_MAJOR,"FATCH FROM DB: LAPD SAPI CONFIG  TABLE FOR LAPD"); 
                  ret_val = GetLapdSapiConfigData(&lapdSapiConfigPtr, &row_count);
                  if((ret_val == 0) && (row_count != 0))
                   {
                    SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
                    len = sizeof(OamScmLapdSAPIConfig) ;
                    msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
                    memcpy(msg_buff, &lapdSapiConfigPtr[g_parameter.no_of_config_row_sent], len );
                    form_scm_header( msg_buff, OAM_SCM_LAPDSAPI_CONFIG, 0, 0, len);
                    g_parameter.no_of_config_row_sent++;
                    if(g_parameter.no_of_config_row_sent >= row_count)
                     {
                      ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       free(lapdSapiConfigPtr);
                       msg_buff = NULL;
                      }  
                      break;
                     }
                    else
                    {
                     ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       free(lapdSapiConfigPtr);
                       msg_buff = NULL;
                      }  
                     if(ret == 0)
                     break;
                     else  
                      return ret_val;
                    }
                   }
                  else
                    SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
                 }
                break;   


             case F_O_U_R :
                 {
                  SCM_printf(SCM_MAJOR,"FATCH FROM DB: LAPD TIMER CONFIG  TABLE"); 
                  ret_val = GetLapdTimerConfigData(&lapdTimerConfigPtr, &row_count);
                  if((ret_val == 0) && (row_count != 0))
                   {
                    SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
                    len = sizeof(OamScmLapdTimerConfig) ;
                    msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
                    memcpy(msg_buff, &lapdTimerConfigPtr[g_parameter.no_of_config_row_sent], len );
                    form_scm_header( msg_buff, OAM_SCM_LAPDTIMER_CONFIG, 0, 0, len);
                    g_parameter.no_of_config_row_sent++;
                    if(g_parameter.no_of_config_row_sent >= row_count)
                     {
                      ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       free(lapdTimerConfigPtr);
                       lapdTimerConfigPtr = NULL;
                       msg_buff = NULL;
                      }  
                      break;
                     }
                    else
                    {
                     ret = process_lapd_stack_cmd (msg_buff);
                      if(msg_buff != NULL)
                      {
                       free(msg_buff);
                       free(lapdTimerConfigPtr);
                       lapdTimerConfigPtr = NULL;
                       msg_buff = NULL;
                      }  
                     if(ret == 0)
                     break;
                     else  
                      return ret_val;
                    }
                   }
                  else
                    SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
                 }
                break;   
#endif
           default:
             break;
        }
        break;

        case ENT_NWSTK:
         if(g_parameter.link_config_flag == 1)
           {
            if(g_parameter.no_config_cmd_sent <= 3)/* this will check if all command 
                                                      send which are not sync with peer */
            {
             switch(g_parameter.no_config_cmd_sent)
             {
               case 0:
                      cmd = N_I_N_E;
                      break;
               case 1:
                      cmd = T_E_N;
                      break; 
               case 2:
                      cmd = E_L_E_V_E_N;
                      break;
               case 3:
                      cmd = T_W_E_L_V_E;
                      g_parameter.no_config_cmd_sent = NUM_CMDS_NWSTK;
                      break;
               default:
                    g_parameter.no_config_cmd_sent   =  NUM_CMDS_NWSTK;
                    return 1;  
             }
            }  
            else
             {
              g_parameter.no_config_cmd_sent   =  NUM_CMDS_NWSTK;
              return 1;
             }  
           }
 
         switch ( cmd )
          {
           case O_N_E:
            SCM_printf(SCM_MAJOR,"FATCH FROM DB:  INITCONFIG TABLE"); 
            initConfigPtr = (OamScmSs7StackConfig*)scm_malloc(sizeof(OamScmSs7StackConfig));
            len = sizeof(OamScmSs7StackConfig);
            ret_val = GetInitConfigData(initConfigPtr);        
            if( ret_val == 0)
             {
              msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
              SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS"); 
              memcpy(msg_buff, initConfigPtr, len );
              form_scm_header( msg_buff, OAM_SCM_SS7_STACK_CONFIG, SCM_ADD, 0, len);
              g_parameter.config_cmd_resp = 1;
              process_nw_stack_init_config_cmd (msg_buff);
              if(msg_buff != NULL)
               { 
                free(msg_buff);
                free(initConfigPtr);
                msg_buff = NULL;
                initConfigPtr = NULL; 
               }
             }
            else
            {   
             SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val); 
             free(initConfigPtr);
             initConfigPtr = NULL;
            }
             break;
          case T_W_O:
           SCM_printf(SCM_MAJOR,"FATCH FROM DB:  SKSGENCFG TABLE FOR MTP3"); 
           sksGenConfigPtr = NULL;
           ret_val = GetSksGenConfigData((sksGenConfig**)&sksGenConfigPtr, &row_count);
           if((ret_val == 0) && (row_count != 0))
             {
              for(loop = 0;loop<row_count;loop++)
               {
                if(sksGenConfigPtr[loop].sksGenCfgstackType == APP_ID_MTP3)
                 {
                  found = SS7_TRUE; 
                  break;
                 }
                else
                 if(loop >= row_count)
                  {
                   found = SS7_FALSE;
                   free(sksGenConfigPtr);
                   sksGenConfigPtr = NULL;  
                   SCM_printf(SCM_MAJOR,"NO ENTRY FOUND FOR MTP3 GEN CFG IN DB"); 
                   break;
                  }
                  else
                   { continue;}
                }
            if( found == SS7_TRUE )
             {
              SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS"); 
              msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
              len = sizeof(scmSksGenConfig);
              ssksGenConfig.sksGenCfgalarmLevel  = g_parameter.alarm_level;  
              ssksGenConfig.sksGenCfgTraceLevel  = sksGenConfigPtr[loop].sksGenCfgTraceLevel; 
              ssksGenConfig.sksGenCfgtraceOutput = sksGenConfigPtr[loop].sksGenCfgtraceOutput; 
              ssksGenConfig.sksGenCfgtraceOnOff  = sksGenConfigPtr[loop].sksGenCfgtraceOnOff; 
              memcpy(msg_buff, &ssksGenConfig, len );
              form_scm_header( msg_buff, OAM_SCM_MTP3_GEN_CFG, 0, 0, len);
              ret = process_nw_stack_cmd (msg_buff);
              if(msg_buff != NULL)
               { 
                 free(msg_buff);
                 free(sksGenConfigPtr);
                sksGenConfigPtr= NULL; 
                msg_buff = NULL;
               }
              break;
             }
            else break;
           }
          else
           SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
           break; 
        
       case T_H_R_E_E:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   SKSGENCFG TABLE FOR BSSAP"); 
        ret_val = GetSksGenConfigData(&sksGenConfigPtr, &row_count);
        if((ret_val == 0) && (row_count != 0))
         {
          for(loop = 0;loop<row_count;loop++)
           {
            if(sksGenConfigPtr[loop].sksGenCfgstackType == APP_ID_BSSAP)
             {
              found = SS7_TRUE; 
              break;
             }
            else
             if(loop >= row_count)
              {
               found = SS7_FALSE;
               free(sksGenConfigPtr);
               sksGenConfigPtr= NULL;  
               SCM_printf(SCM_MAJOR,"NO ENTRY FOUND FOR BSSAP GEN CFG IN DB"); 
               break;
              }
           }
          if( found == SS7_TRUE )
           {
            SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS"); 
            msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
            len = sizeof(scmSksGenConfig);
            ssksGenConfig.sksGenCfgalarmLevel  = g_parameter.alarm_level;  
            ssksGenConfig.sksGenCfgTraceLevel  = sksGenConfigPtr[loop].sksGenCfgTraceLevel; 
            ssksGenConfig.sksGenCfgtraceOutput = sksGenConfigPtr[loop].sksGenCfgtraceOutput; 
            ssksGenConfig.sksGenCfgtraceOnOff  = sksGenConfigPtr[loop].sksGenCfgtraceOnOff; 
            memcpy(msg_buff, &ssksGenConfig, len );
            form_scm_header( msg_buff, OAM_SCM_BSSAP_GEN_CFG, 0, 0, len);
            ret = process_nw_stack_cmd (msg_buff);
            if(msg_buff != NULL)
               { 
                free(msg_buff);
                free(sksGenConfigPtr);
                sksGenConfigPtr = NULL;
                msg_buff = NULL;
               }
            break;
           }
          else break;
         }
        else
         SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
         break; 
       case F_O_U_R:    
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   SKSGENCFG TABLE FOR SCCP"); 
        ret_val = GetSksGenConfigData(&sksGenConfigPtr, &row_count);
        if((ret_val == 0) && (row_count != 0))
         {
          for(loop = 0;loop<row_count;loop++)
           {
            if(sksGenConfigPtr[loop].sksGenCfgstackType == APP_ID_SCCP)
             {
              found = SS7_TRUE; 
              break;
             }
            else
             if(loop >= row_count)
              {
               found = SS7_FALSE;
               free(sksGenConfigPtr);
               sksGenConfigPtr = NULL;
               SCM_printf(SCM_MAJOR,"NO ENTRY FOUND FOR SCCP GEN CFG IN DB"); 
               break;
              }
            else continue;
           }
          if( found == SS7_TRUE )
           {
            SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS"); 
            msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
            len = sizeof(scmSksGenConfig);
            ssksGenConfig.sksGenCfgalarmLevel  = g_parameter.alarm_level;  
            ssksGenConfig.sksGenCfgTraceLevel  = sksGenConfigPtr[loop].sksGenCfgTraceLevel; 
            ssksGenConfig.sksGenCfgtraceOutput = sksGenConfigPtr[loop].sksGenCfgtraceOutput; 
            ssksGenConfig.sksGenCfgtraceOnOff  = sksGenConfigPtr[loop].sksGenCfgtraceOnOff; 
            memcpy(msg_buff, &ssksGenConfig, len );
            form_scm_header( msg_buff, OAM_SCM_SCCP_GEN_CFG, 0, 0, len);
            ret = process_nw_stack_cmd (msg_buff);
            if(msg_buff != NULL)
              {
                  free(msg_buff);
                  free(sksGenConfigPtr);
                  sksGenConfigPtr = NULL;
                  msg_buff = NULL;
              }
            break;
           }
          else break;
         }
        else
         SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
         break; 
              
       case F_I_V_E:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   MTP3LINKSET TABLE"); 
        ret_val = GetLinksetConfigData( &linksetConfigPtr, &row_count); 
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          len = sizeof(OamScmLinkSetConfig) ;
           msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
          memcpy(msg_buff, &linksetConfigPtr[g_parameter.no_of_config_row_sent], len );
          form_scm_header( msg_buff, OAM_SCM_LINKSET_CONFIG, 0, 0, len);
          g_parameter.no_of_config_row_sent++;
          if(g_parameter.no_of_config_row_sent >= row_count)
           {
            ret = process_nw_stack_cmd (msg_buff);
            if(msg_buff != NULL)
              {
                  free(msg_buff);
                  free(linksetConfigPtr);
                  linksetConfigPtr  = NULL;
                  msg_buff = NULL;
              }  
            break;
           }
          else
           {
           ret = process_nw_stack_cmd (msg_buff);
           if(msg_buff != NULL)
              {
                  free(msg_buff);
                  free(linksetConfigPtr);
                  linksetConfigPtr  = NULL;
                  msg_buff = NULL;
              }  
          if(ret == 0)
            break;
          else  
          return ret_val;
         }
        }
       else
        SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
         break;
 

       
       case S_I_X:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   ROUTE CONFIG TABLE"); 
        ret_val =  GetSS7RouteConfigData(&ss7RouteConfigPtr, &row_count);
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          msg_buff = (unsigned char*)scm_malloc (100*sizeof(unsigned char));
          len = sizeof(OamScmSs7RouteConfig);
          memcpy(msg_buff, &ss7RouteConfigPtr[g_parameter.no_of_config_row_sent], len);
          form_scm_header( msg_buff, OAM_SCM_SS7ROUTE_CONFIG, 0, 0, len);
          g_parameter.no_of_config_row_sent++;
          if(g_parameter.no_of_config_row_sent >= row_count)
           {
            ret = process_nw_stack_cmd (msg_buff);
            if(msg_buff != NULL)
             {
              free(msg_buff);
              free(ss7RouteConfigPtr);
              msg_buff = NULL;
              ss7RouteConfigPtr  = NULL; 
             }  
            break;
           }  
          else
           ret = process_nw_stack_cmd (msg_buff);
           if(msg_buff != NULL)
             {
              free(msg_buff);
              free(ss7RouteConfigPtr);
              msg_buff = NULL;
              ss7RouteConfigPtr  = NULL;
             }  
           if(ret == 0)
             break;
           return ret_val;
          }
         else
          SCM_printf(SCM_MAJOR,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
          break;
       case S_E_V_E_N:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   TRUNKCICCONFIG TABLE"); 
        ret_val = GetTrunkCicConfigData(&trunkCicConfigPtr, &row_count);
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          fflush(stdout);
          len = sizeof(OamScmTrunkCicConfig) ;
          loop = g_parameter.no_of_config_row_sent;
          for(; loop < row_count; loop++)
           {
            g_parameter.no_of_config_row_sent++; 
            if(trunkCicConfigPtr[loop].interfaceType == IF_TYP_BSSAP)
             {
              SCM_printf(SCM_MAJOR," A-Interface type");
              found = SS7_TRUE;
              break;
             }
            else
             if(loop >= row_count  )
              {
               found = SS7_FALSE;
               free(trunkCicConfigPtr);
               trunkCicConfigPtr = NULL; 
               break;
              }
             else
              {
               continue;
              }
           }
          if( found == SS7_TRUE)
           { 
             msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
             memcpy(msg_buff, &trunkCicConfigPtr[loop], len );
             form_scm_header( msg_buff, OAM_SCM_TRUNK_CIC_CONFIG, 0, 0, len);
             if (g_parameter.no_of_config_row_sent >= (row_count))
               {
                ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(trunkCicConfigPtr);
                  trunkCicConfigPtr = NULL; 
                  msg_buff = NULL;
                 }  
                break;
               }
             else
               ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(trunkCicConfigPtr);
                  trunkCicConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
               if(ret == 0)
                break;
               return ret_val;
             }
             else 
               SCM_printf(SCM_MAJOR,"TABLE ENTRY FOR A INTERFACES NOT FOUND IN DB");
               break;
            }
           else
            SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
            break;

       case E_I_G_H_T:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   BSCINTERFACE TABLE"); 
        ret_val = GetInterfaceConfigData(&interfaceConfigPtr, &row_count);
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          len = sizeof(OamScmInterfaceConfig );
          loop = g_parameter.no_of_config_row_sent;
          for(; loop<row_count; loop++)
           {
            g_parameter.no_of_config_row_sent++; 
            if(interfaceConfigPtr[loop].interfaceType == IF_TYP_BSSAP)
             {
              found = SS7_TRUE;
              break;
             }
            else
             if(loop >= (row_count -1) )
              {
               free(interfaceConfigPtr);
               interfaceConfigPtr = NULL;
               found = SS7_FALSE;
               break;
              }
             else
              {
               continue;
              }
             }
            if( found == SS7_TRUE)
             { 
              msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
              memcpy(msg_buff, &interfaceConfigPtr[loop], len );
              form_scm_header( msg_buff, OAM_SCM_INTERFACE_CONFIG, 0, 0, len);
              if (g_parameter.no_of_config_row_sent >= (row_count ))
               {
                ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(interfaceConfigPtr);
                  interfaceConfigPtr = NULL;  
                  msg_buff = NULL;
                 }  
                break;
               }
              else
               ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(interfaceConfigPtr);
                  interfaceConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
               if(ret == 0)
                break;
               return ret_val;
             }
            else
             SCM_printf(SCM_MAJOR,"TABLE ENTRY FOR A INTERFACES NOT FOUND IN DB");
             break;
            }
           else
            SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
            break;	 
       
       case N_I_N_E:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   MTP3LINK TABLE"); 
        linkConfigPtr = NULL;
        ret_val =  GetLinkConfigData((OamScmLinkConfig**)&linkConfigPtr, 
                                         &row_count);
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
          len = sizeof(OamScmLinkConfig) ;
          memcpy(msg_buff, &linkConfigPtr[g_parameter.no_of_config_row_sent], len );
          form_scm_header( msg_buff, OAM_SCM_LINK_CONFIG, 0, 0, len);
          g_parameter.no_of_config_row_sent++;
          if(g_parameter.no_of_config_row_sent >= row_count)
           {
            ret = process_nw_stack_cmd (msg_buff);
            if(msg_buff != NULL)
             {
              free(msg_buff);
              free(linkConfigPtr);
              msg_buff = NULL;
              linkConfigPtr = NULL;
             }  
            break;
           }
          else
           ret = process_nw_stack_cmd (msg_buff);
           if(msg_buff != NULL)
            {
             free(msg_buff);
             free(linkConfigPtr);
             msg_buff = NULL;
             linkConfigPtr = NULL;
            }
           if(ret == 0)
             break; 
           return ret_val;
         }
        else
         SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
         break;


       case T_E_N:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   MTP3TIMER TABLE"); 
        ret_val =  GetMtp3TimerConfigData(&mtp3TimerConfigPtr, &row_count); 
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          msg_buff = (unsigned char*)scm_malloc (100*sizeof(unsigned char));
          len = sizeof(OamScmMtp3TimerConfig);
          memcpy(msg_buff, &mtp3TimerConfigPtr[g_parameter.no_of_config_row_sent], len);
          form_scm_header( msg_buff, OAM_SCM_MTP3_TIMER_CONFIG, 0, 0, len);
          g_parameter.no_of_config_row_sent++;
          if(g_parameter.no_of_config_row_sent >= row_count)
           {
             ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(mtp3TimerConfigPtr);
                  mtp3TimerConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
            break;
           }  
          else
           ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(mtp3TimerConfigPtr);
                  mtp3TimerConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
           if(ret == 0)
             break;
           return ret_val;
          }
         else
          SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
          break;
       case E_L_E_V_E_N:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   BSSAP TIMER CONFIG TABLE"); 
        ret_val =  GetBssapTimerConfigData(&bssapTimerConfigPtr, &row_count); 
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          msg_buff = (unsigned char*)scm_malloc (100*sizeof(unsigned char));
          len = sizeof(OamScmBssapTimerConfig);
          memcpy(msg_buff, &bssapTimerConfigPtr[g_parameter.no_of_config_row_sent], len);
          form_scm_header( msg_buff, OAM_SCM_BSSAP_TIMER_CONFIG, 0, 0, len);
          g_parameter.no_of_config_row_sent++;
          if(g_parameter.no_of_config_row_sent >= row_count)
           {
            ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(bssapTimerConfigPtr);
                  bssapTimerConfigPtr = NULL;  
                  msg_buff = NULL;
                 }  
            break;
           }  
          else
           ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(bssapTimerConfigPtr);
                  bssapTimerConfigPtr  = NULL; 
                  msg_buff = NULL;
                 }  
           if(ret == 0)
             break;
           return ret_val;
          }
         else
          SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
          break;

       case T_W_E_L_V_E:
        SCM_printf(SCM_MAJOR,"FATCH FROM DB:   SCCPTIMERCONFIG TABLE"); 
        ret_val =  GetSccpTimerConfigData(&sccpTimerConfigPtr, &row_count); 
        if((ret_val == 0) && (row_count != 0))
         {
          SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
          msg_buff = (unsigned char*)scm_malloc (100*sizeof(unsigned char));
          len = sizeof(OamScmSccpTimerConfig);
          memcpy(msg_buff, &sccpTimerConfigPtr[g_parameter.no_of_config_row_sent], len);
          form_scm_header( msg_buff, OAM_SCM_SCCP_TIMER_CONFIG, 0, 0, len);
          g_parameter.no_of_config_row_sent++;
          if(g_parameter.no_of_config_row_sent >= row_count)
           {
             ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(sccpTimerConfigPtr);
                  sccpTimerConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
            break;
           }  
          else
           ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(sccpTimerConfigPtr);
                  sccpTimerConfigPtr  = NULL;
                  msg_buff = NULL;
                 }  
           if(ret == 0)
             break;
           return ret_val;
          }
         else
          SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
          break;

       case T_H_I_R_T_E_E_N:
         SCM_printf(SCM_MAJOR,"FATCH FROM DB:   SCCP BEHAVIOUR CFG TABLE"); 
         ret_val = GetSccpBehaviorConfigData(&sccpBehaviorConfigPtr, &row_count);
        if((ret_val == 0) && (row_count != 0))
           {
            SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
            msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
            len = sizeof(sSccpBehaviorConfigTableApi);
            memcpy(&msg_buff[8], &sccpBehaviorConfigPtr[g_parameter.no_of_config_row_sent], len);
            form_scm_header( msg_buff, OAM_SCM_SCCP_BEHAVIOR_CONFIG, 0, 0, len + 8);
            g_parameter.no_of_config_row_sent++;
            if(g_parameter.no_of_config_row_sent >= row_count)
             {
              process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(sccpBehaviorConfigPtr);
                  sccpBehaviorConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
              break;
             }
            else
             ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(sccpBehaviorConfigPtr);
                  sccpBehaviorConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
             if(ret == 0)
              break;
             return ret_val;
            }
           else
            SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
            break;
/*       case F_O_U_R_T_E_E_N:
         SCM_printf(SCM_MAJOR,"FATCH FROM DB:   MTP2 TIMER CFG TABLE"); 
         ret_val = GetMtp2TimerConfigData(&mtp2TimerConfigPtr, &row_count);
        if((ret_val == 0) && (row_count != 0))
           {
            SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS");
            msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
            len = sizeof(OamScmMtp2TimerConfig);
            memcpy(&msg_buff[8], &mtp2TimerConfigPtr[g_parameter.no_of_config_row_sent], len);
            form_scm_header( msg_buff, OAM_SCM_MTP2_TIMER_CONFIG, 0, 0, len + 8);
            g_parameter.no_of_config_row_sent++;
            if(g_parameter.no_of_config_row_sent >= row_count)
             {
              process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(mtp2TimerConfigPtr);
                  mtp2TimerConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
              break;
             }
            else
             ret = process_nw_stack_cmd (msg_buff);
                if(msg_buff != NULL)
                 {
                  free(msg_buff);
                  free(mtp2TimerConfigPtr);
                  mtp2TimerConfigPtr = NULL;
                  msg_buff = NULL;
                 }  
             if(ret == 0)
              break;
             return ret_val;
            }
           else
            SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
            break;*/



           default:
             break;
        }
       break;

      /*AOIP: BSSAP CONFIG*/
       case ENT_BSSAP:
           switch(cmd) {
          
           case O_N_E:
                      SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:  BSSAP INITF_ADD TABLE AND TIMER TABLE\n");
                      len = sizeof(OamScmBsInterfaceConfig);
                      ret_val = GetBsIntfTbl(&BsintfConfigPtr);      /* Get*() functions are DB WRAPPERS*/ 
                      if( ret_val == 0)
                        {
                                msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                                SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                                memcpy(msg_buff, BsintfConfigPtr, len );
                                form_scm_header (msg_buff,  OAM_SCM_BS_INTERFACE_CONFIG, SCM_ADD, 0, len); 
                                process_bssap_stack_cmd(msg_buff); /*Bypasses the oam function*/
                                if(msg_buff != NULL)
                                {
                                        free(msg_buff);
                                        free(BsintfConfigPtr);
                                        msg_buff = NULL;
                                        BsintfConfigPtr = NULL;
                                }
                        }
                       else
                        {
                                SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
                        }

            break;
            
            case T_W_O:
            /*DUMMY CASE FOR GETTING ALL RESPONSES*/
            break;
            default:
            SCM_printf(SCM_CRITICAL,"UNEXPECTED CASE***\n");
            break;

           }
      break;
      /*AOIP: END*/

      /*AOIP: SIGTRAN CONFIG*/
      case ENT_SIGTRAN:
           
           switch(cmd) {

           case O_N_E:
                SCM_printf(SCM_MAJOR,"FETCH FROM DB:  SCCP_INIT_CFG_TABLE\n");
                len = sizeof(OamScmSccpInitConfig);
                ret_val = GetSpInitConfigData(&SccpInitConfigPtr, &row_count);  /*preconfig table 1*/
                if((ret_val == 0) && (row_count == 1))
                 {
                   msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   memcpy(msg_buff, SccpInitConfigPtr, len );
                   form_scm_header( msg_buff, OAM_SCM_SCCP_INIT_CONFIG, SCM_ADD, 0, len);
                   process_maptcap_stack_cmd (msg_buff);
                   if(msg_buff != NULL)
                    {
                      free(msg_buff);
                      free(SccpInitConfigPtr);
                      msg_buff = NULL;
                      SccpInitConfigPtr = NULL;
                    }
                 }
               else
                 {
                    SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                    SCM_printf(SCM_CRITICAL,"ERR: PRECONF TABLE NOT PRESENT@#@#@#@#\n");                     
                    SCM_printf(SCM_CRITICAL,"STOP FURTHER CONF\n");
                    g_parameter.config_flag        = SS7_FALSE; /*STOP FURTHER CONF*/ 
                    g_parameter.no_config_cmd_sent = 0;
                    g_parameter.entity_cfg         = 0;
                    return 0;
                 }
           break;

           case T_W_O:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   SCTP_INIT_CONFIG_TABLE \n");
                len = sizeof(OamScmSctpInitConfig);
                ret_val = GetSctpInitConfigData(&SctpInitConfigPtr, &row_count);  /*preconfig table 2*/
                if( ret_val == 0)
                 {
                   msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   memcpy(msg_buff, SctpInitConfigPtr, len );
                   form_scm_header( msg_buff, OAM_SCM_SCTP_INIT_CONFIG, SCM_ADD, 0, len);
                   process_maptcap_stack_cmd (msg_buff);
                   if(msg_buff != NULL)
                    {
                      free(msg_buff);
                      free(SctpInitConfigPtr);
                      msg_buff = NULL;
                      SctpInitConfigPtr = NULL;
                    }
                 }
                else
                 {
                    SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                    SCM_printf(SCM_CRITICAL,"ERR: PRECONF TABLE NOT PRESENT@#@#@#@#\n");                     
                    SCM_printf(SCM_CRITICAL,"STOP FURTHER CONF\n");
                    g_parameter.config_flag        = SS7_FALSE; /*STOP FURTHER CONF*/ 
                    g_parameter.no_config_cmd_sent = 0;
                    g_parameter.entity_cfg         = 0;
                    return 0;
                 }  
           break;

           case T_H_R_E_E:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   M3UA_INIT_CONFIG_TABLE \n");
                len = sizeof(OamScmM3uaInitConfig);
                ret_val = GetM3uaInitConfigData( &M3uaInitConfigPtr, &row_count); /*preconfig table 3*/
                if( ret_val == 0 && row_count == 1)
                 {
                   msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   memcpy(msg_buff, M3uaInitConfigPtr, len );
                   form_scm_header( msg_buff, OAM_SCM_M3UA_INIT_CONFIG, SCM_ADD, 0, len);
                   process_maptcap_stack_cmd (msg_buff);
                   if(msg_buff != NULL)
                    {
                      free(msg_buff);
                      free(M3uaInitConfigPtr);
                      msg_buff = NULL;
                      M3uaInitConfigPtr = NULL;
                    }
                 }
               else
                 {
                   SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                   SCM_printf(SCM_CRITICAL,"ERR: PRECONF TABLE NOT PRESENT@#@#@#@#\n");                     
                   SCM_printf(SCM_CRITICAL,"STOP FURTHER CONF\n");
                   g_parameter.config_flag        = SS7_FALSE; /*STOP FURTHER CONF*/ 
                   g_parameter.no_config_cmd_sent = 0;
                   g_parameter.entity_cfg         = 0;
                   return 0;
               }
           break; 

           
           case F_O_U_R:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   SCCP_SP_CONFIG_TABLE\n"); 
                ret_val = GetSpConfigData(&SccpSpConfigPtr, &row_count); 
                if((ret_val == 0) && (row_count !=0))                     /*Must be 2 rows*/
                 {
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   fflush(stdout);
                   len = sizeof(OamScmSccpSpConfig);
                   loop = g_parameter.no_of_config_row_sent;
                   g_parameter.no_of_config_row_sent++; 
                   if(SccpSpConfigPtr[loop].local == 1)
                    {
                      SCM_printf(SCM_INFO,"LOCAL SP FOUND\n");
                      found = SS7_TRUE;
                    }
                   else
                    if(SccpSpConfigPtr[loop].local == 0)
                    {
                      SCM_printf(SCM_INFO," REMOTE SP FOUND\n");
                      found = SS7_TRUE;
                    }
                   else
                    {
                      found = SS7_FALSE;
                      free(SccpSpConfigPtr);
                      SccpSpConfigPtr = NULL; 
                    }
                   if( found == SS7_TRUE)
                    { 
                      msg_buff = (unsigned char*)scm_malloc (80*sizeof(unsigned char));
                      memcpy(msg_buff, &SccpSpConfigPtr[loop], len );
                      form_scm_header( msg_buff, OAM_SCM_SCCP_SP_CONFIG, 0, 0, len);
                      if (g_parameter.no_of_config_row_sent >= (row_count))
                       {
                         ret = process_maptcap_stack_cmd (msg_buff);
                         if(msg_buff != NULL)
                          {
                            free(msg_buff);
                            free(SccpSpConfigPtr);
                            SccpSpConfigPtr = NULL; 
                            msg_buff = NULL;
                          }   
                         break;
                       }
                      else
                      ret = process_maptcap_stack_cmd (msg_buff);

                      if(msg_buff != NULL)
                       {
                         free(msg_buff);
                         free(SccpSpConfigPtr);
                         SccpSpConfigPtr = NULL;
                         msg_buff = NULL;
                       }  
                      if(ret == 0)
                      break;
                      return ret_val;                             /*would return from here till the Last row is not sent*/
                    }
                   else 
                      SCM_printf(SCM_MAJOR,"TABLE ENTRY FOR SCCP SP NOT FOUND IN DB\n");
                      break;
                 }
                else
                   SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
           break;
 
           case F_I_V_E:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   SCCP_SS_CONFIG_TABLE\n");
                ret_val = GetSsConfigData(&SccpSsConfigPtr, &row_count); 
                if( ret_val == 0 && (row_count != 0))
                 {
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   fflush(stdout);
                   len = sizeof(OamScmSccpSsConfig);
                   loop = g_parameter.no_of_config_row_sent;
                   g_parameter.no_of_config_row_sent++;
              
                   if(&SccpSsConfigPtr[loop])
                    {
                      found = SS7_TRUE;
                    }

                   if(found == SS7_TRUE)
                    {
                      msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                      memcpy(msg_buff, &SccpSsConfigPtr[loop], len );
                      form_scm_header( msg_buff, OAM_SCM_SCCP_SS_CONFIG, SCM_ADD, 0, len);
                      if (g_parameter.no_of_config_row_sent >= (row_count))
                       {
                         ret = process_maptcap_stack_cmd (msg_buff);
                         if(msg_buff != NULL)
                          {
                            free(msg_buff);
                            free(SccpSsConfigPtr);
                            SccpSsConfigPtr = NULL;
                            msg_buff = NULL;
                          }
                         break;                                       /*Break When Last row sent*/
                       }
                      else
                         ret = process_maptcap_stack_cmd (msg_buff);

                      if(msg_buff != NULL)
                       {
                         free(msg_buff);
                         free(SccpSsConfigPtr);
                         SccpSsConfigPtr = NULL;
                         msg_buff = NULL;
                       }
                      if(ret == 0)
                      break;
                      return ret_val;                             /*Return from here till the Last row is not sent*/
                    }
                   else
                      SCM_printf(SCM_MAJOR,"TABLE ENTRY FOR SCCP SS NOT FOUND IN DB\n");
                      break;
                 }
               else
                  SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d", ret_val);
           break; 

           case S_I_X:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   SCCP_CSS_CONFIG_TABLE \n");
                len = sizeof(OamScmSccpCssConfig);
                ret_val = GetCssConfigData(&SccpCssConfigPtr, &row_count); 
                if( ret_val == 0 && row_count == 1)
                 {
                   msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   memcpy(msg_buff, SccpCssConfigPtr, len );
                   form_scm_header( msg_buff, OAM_SCM_SCCP_CSS_CONFIG, SCM_ADD, 0, len);
                   process_maptcap_stack_cmd (msg_buff);
                   if(msg_buff != NULL)
                    {
                      free(msg_buff);
                      free(SccpCssConfigPtr);
                      msg_buff = NULL;
                      SccpCssConfigPtr = NULL;
                    }
                 }
               else
                 {
                   SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                 }             
           break;
 
           case S_E_V_E_N:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   SCCP_CSP_CONFIG_TABLE \n");
                len = sizeof(OamScmSccpCspConfig);
                ret_val = GetSccpCspConfigData(&SccpCspConfigPtr, &row_count);
                if( ret_val == 0 && row_count == 1)
                 {
                   msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   memcpy(msg_buff, SccpCspConfigPtr, len );
                   form_scm_header( msg_buff, OAM_SCM_SCCP_CSP_CONFIG, SCM_ADD, 0, len);
                   process_maptcap_stack_cmd (msg_buff);
                   if(msg_buff != NULL)
                    {
                      free(msg_buff);
                      free(SccpCspConfigPtr);
                      msg_buff = NULL;
                      SccpCspConfigPtr = NULL;
                    }
                 }
                else
                 {
                   SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d \n", ret_val);
                 }

            break; 
 
                  /*Now configuring the M3Ua Stack*/

           case E_I_G_H_T:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   M3UA_LOCAL_ASP_CONFIG_TABLE \n");
                ret_val = GetLocalAspConfigData(&M3uaLocAspConfigPtr, &row_count);
                if( ret_val == 0 && row_count!=0)
                 {
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   fflush(stdout);
                   len = sizeof(OamScmM3uaLocalAspConfig);
                   loop = g_parameter.no_of_config_row_sent;
                   g_parameter.no_of_config_row_sent++;
              
                   if(&M3uaLocAspConfigPtr[loop] != NULL)
                    {
                      found = SS7_TRUE;
                    }

                   if(found == SS7_TRUE)
                    {
                      msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                      memcpy(msg_buff, &M3uaLocAspConfigPtr[loop], len );
                      form_scm_header( msg_buff, OAM_SCM_M3UA_LOCAL_ASP_CONFIG, SCM_ADD, 0, len);
                      if (g_parameter.no_of_config_row_sent >= (row_count))
                       {
                         ret = process_maptcap_stack_cmd (msg_buff);
                         if(msg_buff != NULL)
                          {
                            free(msg_buff);
                            free(M3uaLocAspConfigPtr);
                            msg_buff = NULL;
                            M3uaLocAspConfigPtr = NULL;
                          }
                         break;
                       }
                      else
                        ret = process_maptcap_stack_cmd (msg_buff);
                     
                      if(msg_buff != NULL)
                       {
                         free(msg_buff);
                         free(M3uaLocAspConfigPtr);
                         M3uaLocAspConfigPtr = NULL;
                         msg_buff = NULL;
                       }
                      if(ret == 0)
                      break;
                      return ret_val;                             /*Return from here till the Last row is not sent*/
                    }
                   else
                     SCM_printf(SCM_MAJOR,"TABLE ENTRY FOR M3UA NOT FOUND IN DB\n");
                     break;
                 }
                else
                  SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
           break; 

          case N_I_N_E:
               SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   M3UA_REMOTE_ASP_CONFIG_TABLE \n");
               ret_val = GetRemoteAspConfigData( &M3uaRemAspConfigPtr, &row_count); 
               if( ret_val == 0 && row_count != 0)
                {
                  SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                  fflush(stdout);
                  len = sizeof(OamScmM3uaRemoteAspConfig);
                  loop = g_parameter.no_of_config_row_sent;
                  g_parameter.no_of_config_row_sent++;

                  if(&M3uaRemAspConfigPtr[loop])
                   {
                     found = SS7_TRUE;
                   }
                
                  if(found == SS7_TRUE)
                   {
                     msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                     memcpy(msg_buff, &M3uaRemAspConfigPtr[loop], len );
                     form_scm_header( msg_buff, OAM_SCM_M3UA_REMOTE_ASP_CONFIG, SCM_ADD, 0, len);
                     if (g_parameter.no_of_config_row_sent >= (row_count))
                      {
                        ret = process_maptcap_stack_cmd (msg_buff);
                        if(msg_buff != NULL)
                         {
                           free(msg_buff);
                           free(M3uaRemAspConfigPtr);
                           msg_buff = NULL;
                           M3uaRemAspConfigPtr = NULL;
                         }
                        break;
                      }
                     else
                        ret = process_maptcap_stack_cmd (msg_buff);

                     if(msg_buff != NULL)
                      {
                        free(msg_buff);
                        free(M3uaRemAspConfigPtr);
                        M3uaRemAspConfigPtr = NULL;
                        msg_buff = NULL;
                      }
                     if(ret == 0)
                     break;
                     return ret_val;                             /*Return from here till the Last row is not sent*/
                   }
                  else
                     SCM_printf(SCM_MAJOR,"TABLE ENTRY M3UA REM ASP NOT FOUND IN DB\n");
                     break;
                }
               else
                {
                  SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                }

           break; 

           case T_E_N:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   M3UA_LOCAL_AS_CONFIG_TABLE \n");
                len = sizeof(OamScmM3uaLocalAsConfig);
                ret_val = GetLocalAsConfigData( &M3uaLocAsConfigPtr, &row_count);
                if( ret_val == 0)
                 {
                   msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   memcpy(msg_buff, M3uaLocAsConfigPtr, len );
                   form_scm_header( msg_buff, OAM_SCM_M3UA_LOCAL_AS_CONFIG, SCM_ADD, 0, len);
                   process_maptcap_stack_cmd (msg_buff);
                   if(msg_buff != NULL)
                    {
                      free(msg_buff);
                      free(M3uaLocAsConfigPtr);
                      msg_buff = NULL;
                      M3uaLocAsConfigPtr = NULL;
                    }
                 }
                else
                 {
                   SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                 }
           break; 

           case E_L_E_V_E_N:
                SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   M3UA_REMOTE_AS_CONFIG_TABLE \n");
                len = sizeof(OamScmM3uaRemoteAsConfig);
                ret_val = GetRemoteAsConfigData ( &M3uaRemAsConfigPtr, &row_count); 
                if( ret_val == 0)
                 {
                   msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                   memcpy(msg_buff, M3uaRemAsConfigPtr, len );
                   form_scm_header( msg_buff, OAM_SCM_M3UA_REMOTE_AS_CONFIG, SCM_ADD, 0, len);
                   process_maptcap_stack_cmd (msg_buff);
                   if(msg_buff != NULL)
                    {
                      free(msg_buff);
                      free(M3uaRemAsConfigPtr);
                      msg_buff = NULL;
                      M3uaRemAsConfigPtr = NULL;
                    }
                  }
                 else
                  {
                    SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                  }
           break;
        
       /*Now configuring the SCTP stack*/
 
         case T_W_E_L_V_E:
              SCM_printf(SCM_MAJOR,"\nFETCH FROM DB:   SCTP_CONFIG_TABLE \n");
              len = sizeof(OamScmSctpConfig);
              ret_val = GetSctpConfigData( &SctpGenConfigPtr, &row_count);
              if( ret_val == 0 && row_count == 1)
               {
                 msg_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                 SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS\n");
                 memcpy(msg_buff, SctpGenConfigPtr, len );
                 form_scm_header( msg_buff, OAM_SCM_SCTP_GEN_CONFIG, SCM_ADD, 0, len);
                 process_maptcap_stack_cmd (msg_buff);
                 if(msg_buff != NULL)
                  {
                    free(msg_buff);
                    free(SctpGenConfigPtr);
                    msg_buff = NULL;
                    SctpGenConfigPtr = NULL;
                  }
                }
               else
                {
                  SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
                }    
           break; 

   
           case T_H_I_R_T_E_E_N:
           /*DUMMY CASE */
           break;
          }
      
      break;
     /*AOIP: END*/
      
 
      default: 
        SCM_printf(SCM_CRITICAL,"WRONG ENTITY VALUE FOR READING TABLE FROM DB\n");
        break;

      }
      g_parameter.no_config_cmd_sent++;
      g_parameter.no_of_config_row_sent = 0;
      row_count=0;
     return ret_val;
}

void init_global_config_parm()
{
   S32 ret_val; 
   SCM_printf(SCM_MAJOR,"Inittiazing global config pram from DB");
   initConfigPtr = (OamScmSs7StackConfig*)scm_malloc(sizeof(OamScmSs7StackConfig));
   ret_val = GetInitConfigData(initConfigPtr);
   if( ret_val == 0)
    {
     SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS"); 
     g_parameter.opc_value        = initConfigPtr->selfPointCode;
     g_parameter.alarm_level      = initConfigPtr->alarmLevel;
     SCM_printf(SCM_MAJOR,"g_parameter.alarm_level : %d:", g_parameter.alarm_level);

     if(initConfigPtr->family == SYS_FAMILY_ANSI)
     {
       g_parameter.family = ANSI_FAMILY;
     }
     else
     {
       g_parameter.family = ITU_FAMILY;
     }
     free(initConfigPtr);
     initConfigPtr = NULL;   
    }
   else
   {
    SCM_printf(SCM_CRITICAL,"DB READ FOR INITCONFIG TABLE FAILED - ERROR_CODE: %d", ret_val);
    free(initConfigPtr);
    initConfigPtr = NULL;   
   }
 
}
/*********************************************************************************/
/* This funtion check if entity getting config is configured and mark the flag configured*/
/*********************************************************************************/
int check_entity_configured( U8 entity )
{

 strcpy(g_parameter.function_string, "check_entity_configured()");

 switch( entity )
  {
  case ENT_NWSTK:
          if ( g_parameter.no_config_cmd_sent >= NUM_CMDS_NWSTK)
           {
            SCM_printf(SCM_MAJOR,"ALL CONFIG CMD SENT TO NWSTK");
            
            g_parameter.no_config_cmd_sent  = 0;
            g_parameter.entity_cfg          = 0;
            g_parameter.config_flag         = 0; 
            g_parameter.nwstk_cfgComplete   = 1;
            timer_info[TIMER_NWSTK].db_oam_stamp = 0; 
            if(g_parameter.lapd_cfgComplete == 1)
            {
             process_scm_alarm(SS7_UP);
            }
            multi_cmd[0].lock_flag = 0;
            g_parameter.link_config_flag = 0;
            if((xxx_client_sockfd[ENT_PEER_SCM] > 0) && (g_parameter.peer_nwstk_up == 1))
             {
              send_cofigComplete_ind_to_peerScm(ENT_NWSTK); 
             }
            return 1;
           }
          else
            return 0;
          break;
  case ENT_LAPD:
          if ( g_parameter.no_config_cmd_sent >= NUM_CMDS_LAPD)
           {
            SCM_printf(SCM_MAJOR,"ALL CONFIG CMD SENT TO LAPD");
            
            g_parameter.no_config_cmd_sent = 0;
            g_parameter.entity_cfg = 0;
            g_parameter.config_flag = 0; 
            timer_info[TIMER_LAPD].db_oam_stamp = 0; 
            g_parameter.lapd_cfgComplete = 1; 
#ifdef LAPD_HA
            send_lapd_config_complete();
#endif
           if(g_parameter.nwstk_cfgComplete == 1)
           {
            process_scm_alarm(SS7_UP);
           }
           else
            if(g_parameter.nwstk_cfg_wait == 1)
            {
             stop_timer( TIMER_NWSTK_CONFIG);
             g_parameter.nwstk_cfg_wait = 0;
#ifdef NWSTK_REDUNDANCY               
            if((g_parameter.redundant_status == SCM_ACTIVE) && (g_parameter.nwstk_cfgComplete != 1))
            {
             if(g_parameter.nwstk_cfgIndFromPeerCard  ==  1)
              {
                if(write_in_sock_event_q(NWSTK_CONFIG_COMPLETE) == 0)
                {
                 SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL");
                }
              }
             else
              {    
                if(write_in_sock_event_q(ENT_NWSTK) == 0)
                {
                 SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL");
                }
              }
            }
            else       
            if(((g_parameter.nwstk_cfgIndFromPeerCard  ==  1) || (xxx_client_sockfd[ENT_PEER_SCM] <= 0))&& (g_parameter.nwstk_cfgComplete != 1)) 
             { 
               if(write_in_sock_event_q(NWSTK_CONFIG_COMPLETE) == 0)
               {
                SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL");
               }
             }
#else
                if(write_in_sock_event_q(ENT_NWSTK) == 0)
                {
                 SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL");
                }
#endif
            }  
            /* to be decided later */
           // process_scm_alarm(LAPD_UP);
           /* endhere */
            multi_cmd[0].lock_flag = 0;
            g_parameter.link_config_flag = 0;
            return 1;
           }
          else
            return 0;
            break;

/*AOIP SIGTRAN*/
  case ENT_SIGTRAN:
       if ( g_parameter.no_config_cmd_sent >= NUM_CMDS_SIGTRAN) /*AOIP: NO OF SIGTRAN CMD*/
        {
         SCM_printf(SCM_MAJOR,"ALL CONFIG CMD SENT TO SIGTRAN\n");
         g_parameter.no_config_cmd_sent = 0;
         g_parameter.entity_cfg = 0;
         g_parameter.config_flag = 0;
         g_parameter.sigtran_cfgComplete   = 1; 
         if( g_parameter.bssap_cfgComplete == 1)      
          {
            process_scm_alarm(SS7_UP);                         /*BOTH SIGTRAN AND BSSAP ARE UP*/
          }
         
         SCM_printf(SCM_MAJOR,"peer_nwstk_up[%d] bssap_cfg_done[%d] sigtran_cfg_done[%d] peer_scm_fd[%d]\n", 
         g_parameter.peer_nwstk_up, g_parameter.bssap_cfgComplete, g_parameter.sigtran_cfgComplete, xxx_client_sockfd[ENT_PEER_SCM]);
          
         if((xxx_client_sockfd[ENT_PEER_SCM] > 0)  && (g_parameter.bssap_cfgComplete == 1) &&
             (g_parameter.sigtran_cfgComplete == 1)  && (g_parameter.peer_nwstk_up == 1))
          {
            SCM_printf(SCM_MAJOR,"[JOIN] SENDING CONFIG COMPLETE IND TO PEER\n");
            send_cofigComplete_ind_to_peerScm(ENT_SIGTRAN);
          }
         return 1;
        }
       else
        return 0;
       break;

  /*AOIP: BSSAP*/
  case ENT_BSSAP:
    if ( g_parameter.no_config_cmd_sent >= NUM_CMDS_BSSAP) 
      {
         SCM_printf(SCM_MAJOR,"ALL CONFIG CMD SENT TO BSSAP\n");
         g_parameter.no_config_cmd_sent = 0;
         g_parameter.entity_cfg = 0;
         g_parameter.config_flag = 0; 
         g_parameter.bssap_cfgComplete   = 1;
         if( g_parameter.sigtran_cfgComplete == 1)
          {
             process_scm_alarm(SS7_UP);                      /*BSSAP UP & Sigtran also UP*/
          }
         SCM_printf(SCM_MAJOR,"peer_nwstk_up[%d] bssap_cfg[%d] sigtran_cfg[%d] peer_scm_fd[%d]\n", 
         g_parameter.peer_nwstk_up, g_parameter.bssap_cfgComplete, g_parameter.sigtran_cfgComplete, xxx_client_sockfd[ENT_PEER_SCM]);
         if((xxx_client_sockfd[ENT_PEER_SCM] > 0)  && (g_parameter.bssap_cfgComplete == 1) &&
            (g_parameter.sigtran_cfgComplete == 1)  && (g_parameter.peer_nwstk_up == 1))
          {
            SCM_printf(SCM_MAJOR,"[JOIN] SENDING CONFIG COMPLETE IND TO PEER\n");
            send_cofigComplete_ind_to_peerScm(ENT_BSSAP);
          }
         return 1;
      }
    else
    return 0;
    break;  
   /*AOIP: END*/
   default: 
       SCM_printf(SCM_CRITICAL,"DECODING ERROR");
    }
  return 0;
}


/***************************************************************************/
/*This function processes the peer scm message recieved from peer
  card i.e. either cmd response or config cmd update from peer card scm*/
/***************************************************************************/



int send_cofigComplete_ind_to_peerScm(U8 entity)
{              
  U8 cmd_buff[10];
  S32 ret_val;
  U16 length;
  length = sizeof(ScmHdr);
  strcpy(g_parameter.function_string, "send_cofigComplete_ind_to_peerScm()");
  switch(entity)
  { 
    case ENT_NWSTK:
         form_oam_header( cmd_buff, NWSTK_CONFIG_COMPLETE, SCM_MODIFY, 0, 0 ,length );
         break;
   /*AOIP_HA*/
    case ENT_SIGTRAN:
    case ENT_BSSAP:
         form_oam_header( cmd_buff, MAPTCAP_CONFIG_COMPLETE, SCM_MODIFY, 0, 0,length);   /*BSSAP AND SIGTRAN CONFIG COMPLETE MSG FRM STANDBY*/
         break; 
   /*AOIP_HA end*/ 
    default:
        return 0;
   } 
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_PEER_SCM, length);
  if(ret_val <= 0)
   {             
    SCM_printf (SCM_CRITICAL, "SCM STACK CONFIG COMPLETE MESSAGE SEND TO PEER SCM FAILED");
    return 0;   
   }          
return 1;    
} 




S32 check_entiy_up(U8 entity)
 {
  if(xxx_client_sockfd [entity] > 0)
   {
    return 0;  
   }   
  else 
  {
   g_parameter.config_flag = 0;
   g_parameter.no_of_config_row_sent = 0;
   g_parameter.config_cmd_resp = 0;
   g_parameter.no_config_cmd_sent = 0;
   return 1;
  }
 }


/*AOIP : DB ROUTINES*/

I_S32  GetBsIntfTbl(OamScmBsInterfaceConfig **IntfConfigPtrToPtr) 
{
   I_S16 rowSize = 0;
   I_S16 i = 0, j = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   BssapIntfConfigTableApi *IntfTblPtr=NULL;
   OamScmBsInterfaceConfig *IntfConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetBsIntfTbl()");


  dbSts = getallBssapIntfConfigTable((I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_S16*)&rowSize);
  
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(BssapIntfConfigTableApi)), (unsigned char* )DbPtr, 15);
      IntfConfigPtr = calloc (rowCount,sizeof(OamScmBsInterfaceConfig));
      *IntfConfigPtrToPtr = IntfConfigPtr; 
      while (rowCount)
      {
         IntfTblPtr = (BssapIntfConfigTableApi*)(DbPtr + i*rowSize);
         IntfConfigPtr[i].bscId            = (U16)IntfTblPtr->bscId;
         IntfConfigPtr[i].interfaceType     = (U16)IntfTblPtr->interfaceType;
         IntfConfigPtr[i].ni                = (U16)IntfTblPtr->ni;
         IntfConfigPtr[i].opc               = (U32)IntfTblPtr->opc;
         IntfConfigPtr[i].dpc               = (U32)IntfTblPtr->dpc;
         IntfConfigPtr[i].variant           = (U16)IntfTblPtr->variant;
         IntfConfigPtr[i].timerProfileId    = (U16)IntfTblPtr->timerProfileId;
         memcpy( IntfConfigPtr[i].name, IntfTblPtr->name, 20);
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

I_S32  GetBsTimerTbl(OamScmBsTimerConfig  **TmrConfigPtrToPtr, U16 timerProfileId) 
{
   I_S16 rowSize = 0;
   I_S16 i = 0, j = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts, check = 0;
   void       *DbPtr=NULL;
   BssapTmrConfigTableApi  *TmrTblPtr=NULL;
   OamScmBsTimerConfig  * TmrConfigPtr;
   strcpy(g_parameter.function_string, "GetBsTimerTbl()");

   dbSts = getallBssapTmrConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);

   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(BssapTmrConfigTableApi)), (unsigned char* )DbPtr, 15);
      TmrConfigPtr = calloc (rowCount,sizeof(OamScmBsTimerConfig));
      *TmrConfigPtrToPtr = TmrConfigPtr;
      while (rowCount)
      { 
         TmrTblPtr = (BssapTmrConfigTableApi*)(DbPtr + i*rowSize);
                
                if((U16) TmrTblPtr->profileID ==  timerProfileId)
                   {
                     check = 1;
                     SCM_printf (SCM_DEBUG, "Read Timer Profile %d from DB\n", TmrTblPtr->profileID);
                     TmrConfigPtr->timer_T1= (U16)TmrTblPtr->timer_T1;
                     TmrConfigPtr->timer_T4= (U16)TmrTblPtr->timer_T4;
                     TmrConfigPtr->timer_T10= (U16)TmrTblPtr->timer_T10;
                     TmrConfigPtr->timer_T11= (U16)TmrTblPtr->timer_T11;
                     TmrConfigPtr->timer_T13= (U16)TmrTblPtr->timer_T13;
                     TmrConfigPtr->timer_T17= (U16)TmrTblPtr->timer_T17;
                     TmrConfigPtr->timer_T18= (U16)TmrTblPtr->timer_T18;
                     TmrConfigPtr->timer_T25= (U16)TmrTblPtr->timer_T25;
                     TmrConfigPtr->timer_Trbsc= (U16)TmrTblPtr->timer_Trbsc;
                  }
        rowCount--; 
        i++;
      }
    free(DbPtr);
    }
    else
    {
     return dbSts;
    }
  
    if(check == 1)
    return 0;
    else
     {
       SCM_printf (SCM_DEBUG, "BSSAP PROFILE NOT FOUND****\n");
       return -1;
     }
}

I_S32 GetBssapIntfToReconfig(OamScmBsInterfaceConfig **IntfConfigPtrToPtr, U16 timerProfileId)
{
   I_S16 rowSize = 0;
   I_S16 i = 0, j = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   I_U16 check = 0;
   void       *DbPtr=NULL;
   BssapIntfConfigTableApi *IntfTblPtr=NULL;
   OamScmBsInterfaceConfig *IntfConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetBssapIntfToReconfig()");


  dbSts = getallBssapIntfConfigTable((I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_S16*)&rowSize);
  
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(BssapIntfConfigTableApi)), (unsigned char* )DbPtr, 15);
      IntfConfigPtr = calloc (1,sizeof(OamScmBsInterfaceConfig));
      *IntfConfigPtrToPtr = IntfConfigPtr; 
      while (rowCount)
      {
         IntfTblPtr = (BssapIntfConfigTableApi*)(DbPtr + i*rowSize);
         if(IntfTblPtr->timerProfileId == timerProfileId)
          {
                 check = 1;
                 SCM_printf (SCM_DEBUG, "Read Bssap Intf From DB\n");
                 IntfConfigPtr->bscId            = (U16)IntfTblPtr->bscId;
                 IntfConfigPtr->interfaceType     = (U16)IntfTblPtr->interfaceType;
                 IntfConfigPtr->ni                = (U16)IntfTblPtr->ni;
                 IntfConfigPtr->opc               = (U32)IntfTblPtr->opc;
                 IntfConfigPtr->dpc               = (U32)IntfTblPtr->dpc;
                 IntfConfigPtr->variant           = (U16)IntfTblPtr->variant;
                 IntfConfigPtr->timerProfileId    = (U16)IntfTblPtr->timerProfileId;
                 memcpy( IntfConfigPtr[i].name, IntfTblPtr->name, 20);
                 break;
          }
          
          rowCount--; 
          i++;

      }         
         free(DbPtr); 
   }
   else
   {
     return dbSts;  
   }
 
  if(check == 1)
     return 0;
  else
   {
     SCM_printf (SCM_DEBUG, "PROFILE NOT FOUND\n");
     return -1;
   }
}


I_S32 GetSpInitConfigData(OamScmSccpInitConfig **spConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSccpInitConfigTableApi *SccpTblPtr=NULL;
   OamScmSccpInitConfig *SccpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSpInitConfigData()");

   dbSts = getallSigtranSccpInitConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
  
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSccpInitConfigTableApi)), (unsigned char* )DbPtr, 15);
      SccpConfigPtr = calloc (rowCount,sizeof(OamScmSccpInitConfig));
      *spConfigPtrToPtr = SccpConfigPtr;
      while (rowCount)
      { 
         SCM_printf (SCM_DEBUG,"Read Sccp Init Table From DB\n");
         SccpTblPtr = (SigtranSccpInitConfigTableApi*)(DbPtr + i*rowSize);
         SccpConfigPtr[i].max_sp                = (U32)SccpTblPtr->max_sp;
         SccpConfigPtr[i].max_ss                = (U32)SccpTblPtr->max_ss;
         SccpConfigPtr[i].max_css               = (U32)SccpTblPtr->max_css;
         SccpConfigPtr[i].max_csp               = (U32)SccpTblPtr->max_csp;
         SccpConfigPtr[i].standard              = (U8)SccpTblPtr->standard;
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

I_S32 GetSpConfigData(OamScmSccpSpConfig  **SpConfigPtrToPtr, U8 *row_count)
{
   I_U16 rowSize = 0;
   I_S16 i = 0;
   I_U32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSccpSPConfigTableApi *SccpTblPtr=NULL;
   OamScmSccpSpConfig *SccpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSpConfigData()");


  dbSts = getallSigtranSccpSPConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
  *row_count = rowCount;
  SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
  if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSccpSPConfigTableApi)), (unsigned char* )DbPtr, 15);
      SccpConfigPtr = calloc (rowCount,sizeof(OamScmSccpSpConfig));
      *SpConfigPtrToPtr = SccpConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG,"Read Sccp Sp Table From DB\n");
         SccpTblPtr = (SigtranSccpSPConfigTableApi*)(DbPtr + i*rowSize);
         SccpConfigPtr[i].spId      = (U32)SccpTblPtr->spId;
         SccpConfigPtr[i].nwId      = (U8)SccpTblPtr->nwId;
         SccpConfigPtr[i].pointCode = (U32)SccpTblPtr->pointCode;
         SccpConfigPtr[i].local     = (U8)SccpTblPtr->local;
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

I_S32 GetSsConfigData(OamScmSccpSsConfig  **SpConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSccpSSConfigTableApi *SccpTblPtr=NULL;
   OamScmSccpSsConfig *SccpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSsConfigData()");


  dbSts = getallSigtranSccpSSConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
  *row_count = rowCount;
  SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSccpSSConfigTableApi)), (unsigned char* )DbPtr, 15);
      SccpConfigPtr = calloc (rowCount,sizeof(OamScmSccpSsConfig));
      *SpConfigPtrToPtr = SccpConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read Sccp Ss Table From DB\n");
         SccpTblPtr = (SigtranSccpSSConfigTableApi*)(DbPtr + i*rowSize);
         SccpConfigPtr[i].ssId= (U32)SccpTblPtr->ssId;
         SccpConfigPtr[i].spId= (U32)SccpTblPtr->spId;
         SccpConfigPtr[i].ssn = (U8)SccpTblPtr->ssn;
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

I_S32 GetCssConfigData(OamScmSccpCssConfig **SpConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSccpCSSConfigTableApi *SccpTblPtr=NULL;
   OamScmSccpCssConfig *SccpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetCssConfigData()");


  dbSts = getallSigtranSccpCSSConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
  *row_count = rowCount;
  SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSccpCSSConfigTableApi)), (unsigned char* )DbPtr, 15);
      SccpConfigPtr = calloc (rowCount,sizeof(OamScmSccpCssConfig));
      *SpConfigPtrToPtr = SccpConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read Sccp Css Table From DB\n");
         SccpTblPtr = (SigtranSccpCSSConfigTableApi*)(DbPtr + i*rowSize);
         SccpConfigPtr[i].ssId = (U32)SccpTblPtr->ssId;
         SccpConfigPtr[i].cssId= (U32)SccpTblPtr->cssId;
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


I_S32 GetSccpCspConfigData(OamScmSccpCspConfig  **SpConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSccpCSPConfigTableApi *SccpTblPtr=NULL;
   OamScmSccpCspConfig *SccpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSccpCspConfigData()");

   dbSts = getallSigtranSccpCSPConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSccpCSPConfigTableApi)), (unsigned char* )DbPtr, 15);
      SccpConfigPtr = calloc (rowCount,sizeof(OamScmSccpCspConfig));
      *SpConfigPtrToPtr = SccpConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read Sccp Csp Table From DB\n");
         SccpTblPtr = (SigtranSccpCSPConfigTableApi*)(DbPtr + i*rowSize);
         SccpConfigPtr[i].ssId= (U32)SccpTblPtr->ssId;
         SccpConfigPtr[i].cspId= (U32)SccpTblPtr->cspId;
         SccpConfigPtr[i].timerProfileId= (U32)SccpTblPtr->timerProfileId;
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


I_S32 GetSccpCspToReconfig(OamScmSccpCspConfig  **SpConfigPtrToPtr, U16 profileId)
{
  I_S16 rowSize = 0;
  I_S16 i = 0;
  I_S32 rowCount = 0;
  I_S32 dbSts;
  I_U16 check = 0; /*DOWN*/
  void       *DbPtr=NULL;
  SigtranSccpCSPConfigTableApi *SccpTblPtr=NULL;
  OamScmSccpCspConfig *SccpConfigPtr=NULL;
  strcpy(g_parameter.function_string, "GetSccpCspConfigData()");

  dbSts = getallSigtranSccpCSPConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);

  SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
  if(dbSts == DB_SUCCESS)
   {
     SCM_DUMP(0,(rowCount *sizeof(SigtranSccpCSPConfigTableApi)), (unsigned char* )DbPtr, 15);
     SccpConfigPtr = calloc (1,sizeof(OamScmSccpCspConfig));
    *SpConfigPtrToPtr = SccpConfigPtr;
     while (rowCount)
       {
         SccpTblPtr = (SigtranSccpCSPConfigTableApi*)(DbPtr + i*rowSize);
         if(SccpTblPtr->timerProfileId == profileId)
          {  
            check=1;
            SCM_printf (SCM_DEBUG, "Read Sccp Csp Table From DB [RECONF]\n");
            SccpConfigPtr->ssId           = (U32)SccpTblPtr->ssId;
            SccpConfigPtr->cspId          = (U32)SccpTblPtr->cspId;
            SccpConfigPtr->timerProfileId = (U32)SccpTblPtr->timerProfileId;
            break; 
          }
         rowCount--;
         i++;
       }
     free(DbPtr);
   }
  else
   {
     return dbSts;
   }
  
  if(check)
     return 0;
  else
   {
     SCM_printf (SCM_DEBUG, "PROFILE NOT FOUND\n");
     return -1;
   }
}


I_S32 GetSccpTmrConfigData(OamScmSccpTmrConfig **SpConfigPtrToPtr, I_U16 Profile_ID)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   I_U16 check = 0;
   void       *DbPtr=NULL;
   SigtranSccpTimerTableApi *SccpTblPtr=NULL;
   OamScmSccpTmrConfig *SccpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSccpTmrConfigData()");


   dbSts = getallSigtranSccpTimerTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSccpTimerTableApi)), (unsigned char* )DbPtr, 15);
      SccpConfigPtr = calloc (1,sizeof(OamScmSccpTmrConfig));
      *SpConfigPtrToPtr = SccpConfigPtr;
      while (rowCount)
      {
         SccpTblPtr = (SigtranSccpTimerTableApi*)(DbPtr + i*rowSize);
         if(SccpTblPtr->profileId ==  Profile_ID)
          {   
             check = 1;
             SCM_printf (SCM_DEBUG, "Read Sccp Tmr Table From DB\n"); 
             SccpConfigPtr->profileId   = (U16)SccpTblPtr->profileId;
             SccpConfigPtr->treass      = (U32)SccpTblPtr->treass;
             SccpConfigPtr->tstatinfo   = (U32)SccpTblPtr->tstatinfo;
             SccpConfigPtr->tcongattack = (U32)SccpTblPtr->tcongattack;
             SccpConfigPtr->tcongdecay  = (U32)SccpTblPtr->tcongdecay;
             SccpConfigPtr->segparmz    = (U32)SccpTblPtr->segparmz;
             break;
          }
         rowCount--;
         i++;

      }
         free(DbPtr);

    }
   else
    {
      return dbSts;
    }

   if(check == 1)
       return 0;
   else
    {
       SCM_printf (SCM_DEBUG, "PROFILE NOT FOUND\n");
       return -1;
    }
}


int GetSctpInitConfigData( OamScmSctpInitConfig **SctpConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S16 check = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSctpInitConfigTableApi *SctpTblPtr=NULL;
   OamScmSctpInitConfig *SctpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSctpInitConfigData()");

   dbSts = getallSigtranSctpInitConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSctpInitConfigTableApi)), (unsigned char* )DbPtr, 15);
      SctpConfigPtr = calloc (1,sizeof(OamScmSctpInitConfig ));
      *SctpConfigPtrToPtr = SctpConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read Sctp Init Table From DB\n");
         SctpTblPtr = (SigtranSctpInitConfigTableApi*)(DbPtr + i*rowSize);
         if(SctpTblPtr->slotId == (g_parameter.slot_id-2))
          {  
             check = 1;
             SCM_printf (SCM_DEBUG, "Found relevant slot id\n");
             SctpConfigPtr[0].max_endpoint            = (U32)SctpTblPtr->max_endpoint;
             SctpConfigPtr[0].max_tcb                 = (U32)SctpTblPtr->max_tcb;
             SctpConfigPtr[0].max_per_assoc_streams   = (U32)SctpTblPtr->max_per_assoc_streams;
             SctpConfigPtr[0].max_per_assoc_tx_buffer = (U32)SctpTblPtr->max_per_assoc_tx_buffer;
             SctpConfigPtr[0].max_per_assoc_rx_buffer = (U32)SctpTblPtr->max_per_assoc_rx_buffer;
             SctpConfigPtr[0].stack_type              = (U32)SctpTblPtr->stack_type;
             SctpConfigPtr[0].ecn_capable             = (U8)SctpTblPtr->ecn_capable;
             SctpConfigPtr[0].pmtu_capable            = (U8)SctpTblPtr->pmtu_capable;
             SctpConfigPtr[0].num_in_streams          = (U16)SctpTblPtr->num_in_streams;
             SctpConfigPtr[0].num_out_streams         = (U16)SctpTblPtr->num_out_streams;
             memcpy( &(SctpConfigPtr[0].local_IP[0]), &(SctpTblPtr->local_IP[0]), 25);
          }
         i++; 
         rowCount--;

      }
         free(DbPtr);

   }
   else
   {
      return dbSts;
   }
if(check == 1)
return 0;
else
return -1;
} 

 
I_S32 GetSctpConfigData(OamScmSctpConfig **SctpConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSctpConfigTableApi *SctpTblPtr=NULL;
   OamScmSctpConfig  *SctpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSctpInitConfigData()");

   dbSts = getallSigtranSctpConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSctpConfigTableApi)), (unsigned char* )DbPtr, 15);
      SctpConfigPtr = calloc (rowCount,sizeof(OamScmSctpConfig ));
      *SctpConfigPtrToPtr = SctpConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read Sctp Config Table From DB\n");
         SctpTblPtr = (SigtranSctpConfigTableApi*)(DbPtr + i*rowSize);
         SctpConfigPtr[i].assoc_max_retrans = (U32)SctpTblPtr->assoc_max_retrans;
         SctpConfigPtr[i].path_max_retrans  = (U32)SctpTblPtr->path_max_retrans;
         SctpConfigPtr[i].max_init_retrans  = (U32)SctpTblPtr->max_init_retrans;
         SctpConfigPtr[i].timerProfileId    = (U16)SctpTblPtr->timerProfileId;
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

I_S32  GetSctpTimerData( OamScmSctpTimerConfig **SctpConfigPtrToPtr)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranSctpTimerTableApi *SctpTblPtr=NULL;
   OamScmSctpTimerConfig *SctpConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetSctpInitConfigData()");
   
   dbSts = getallSigtranSctpTimerTable((I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranSctpTimerTableApi)), (unsigned char* )DbPtr, 15);
      SctpConfigPtr = calloc (rowCount,sizeof(OamScmSctpTimerConfig));
      *SctpConfigPtrToPtr = SctpConfigPtr;
      while (rowCount)
      {  
         SCM_printf (SCM_DEBUG, "Read Sctp Tmr Table From DB\n");
         SctpTblPtr = (SigtranSctpTimerTableApi*)(DbPtr + i*rowSize);
         SctpConfigPtr[i].rto_init          = (U32)SctpTblPtr->rto_init;
         SctpConfigPtr[i].rto_min           = (U32)SctpTblPtr->rto_min;
         SctpConfigPtr[i].rto_max           = (U32)SctpTblPtr->rto_max;
         SctpConfigPtr[i].rto_alpha_percent = (U32)SctpTblPtr->rto_alpha_percent;
         SctpConfigPtr[i].rto_beta_percent  = (U32)SctpTblPtr->rto_beta_percent;
         SctpConfigPtr[i].valid_cookie_life = (U32)SctpTblPtr->valid_cookie_life;
         SctpConfigPtr[i].hb_interval       = (U32)SctpTblPtr->hb_interval;
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
 

I_S32  GetM3uaInitConfigData (OamScmM3uaInitConfig **M3uaConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranM3uaInitConfigTableApi *M3uaTblPtr=NULL;
   OamScmM3uaInitConfig *M3uaConfigPtr=NULL;
   strcpy(g_parameter.function_string, "M3uaInitTableApi()");

   dbSts = getallSigtranM3uaInitConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranM3uaInitConfigTableApi)), (unsigned char* )DbPtr, 15);
      M3uaConfigPtr = calloc (rowCount,sizeof(OamScmM3uaInitConfig ));
      *M3uaConfigPtrToPtr = M3uaConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read M3ua Init Table From DB\n");
         M3uaTblPtr  = (SigtranM3uaInitConfigTableApi*)(DbPtr + i*rowSize);
         M3uaConfigPtr[i].max_sp                  = (U32)M3uaTblPtr->max_sp;
         M3uaConfigPtr[i].max_remote_sp           = (U32)M3uaTblPtr->max_remote_sp;
         M3uaConfigPtr[i].max_as                  = (U16)M3uaTblPtr->max_as;
         M3uaConfigPtr[i].max_remote_as           = (U16)M3uaTblPtr->max_remote_as;
         M3uaConfigPtr[i].max_sg                  = (U16)M3uaTblPtr->max_sg;
         M3uaConfigPtr[i].max_conn                = (U32)M3uaTblPtr->max_conn;
         M3uaConfigPtr[i].max_user_parts_per_asp  = (U16)M3uaTblPtr->max_user_parts_per_asp;
         M3uaConfigPtr[i].default_standard_type   = (U16)M3uaTblPtr->default_standard_type;
         M3uaConfigPtr[i].default_nw_identity     = (U16)M3uaTblPtr->default_nw_identity;
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

I_S32  GetLocalAspConfigData (OamScmM3uaLocalAspConfig  **M3uaConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranM3uaLAspConfigTableApi *M3uaTblPtr=NULL;
   OamScmM3uaLocalAspConfig *M3uaConfigPtr=NULL;
   strcpy(g_parameter.function_string, "M3uaLocAspTableApi()");

   dbSts = getallSigtranM3uaLAspConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranM3uaLAspConfigTableApi)), (unsigned char* )DbPtr, 15);
      M3uaConfigPtr = calloc (rowCount,sizeof(OamScmM3uaLocalAspConfig));
      *M3uaConfigPtrToPtr = M3uaConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read M3ua Asp Table From DB\n");
         M3uaTblPtr  = (SigtranM3uaLAspConfigTableApi*)(DbPtr + i*rowSize);
         M3uaConfigPtr[i].localAspId   = (U16)M3uaTblPtr->localAspId;
         M3uaConfigPtr[i].localPort    = (U16)M3uaTblPtr->localPort;
         M3uaConfigPtr[i].slotId       = (U16)M3uaTblPtr->slotId;
         M3uaConfigPtr[i].assocType    = (U16)M3uaTblPtr->assocType;
         M3uaConfigPtr[i].maxInStream  = (U16)M3uaTblPtr->maxInStream;
         M3uaConfigPtr[i].maxOutStream = (U16)M3uaTblPtr->maxOutStream;
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


I_S32 GetRemoteAspConfigData(OamScmM3uaRemoteAspConfig  **M3uaConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranM3uaRAspConfigTableApi *M3uaTblPtr=NULL;
   OamScmM3uaRemoteAspConfig *M3uaConfigPtr=NULL;
   strcpy(g_parameter.function_string, "M3uaRemAspTableApi()");

   dbSts = getallSigtranM3uaRAspConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranM3uaRAspConfigTableApi)), (unsigned char* )DbPtr, 15);
      M3uaConfigPtr = calloc (rowCount,sizeof(OamScmM3uaRemoteAspConfig));
      *M3uaConfigPtrToPtr = M3uaConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read M3ua Rem Asp Table From DB\n");
         M3uaTblPtr  = (SigtranM3uaRAspConfigTableApi*)(DbPtr + i*rowSize);
         M3uaConfigPtr[i].remAspId   = (U16)M3uaTblPtr->remAspId;
         M3uaConfigPtr[i].remotePort = (U16)M3uaTblPtr->remotePort;
         memcpy(M3uaConfigPtr[i].name     , M3uaTblPtr->name     , 25);
         memcpy(M3uaConfigPtr[i].remoteIp , M3uaTblPtr->remoteIp , 25);
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

I_S32 GetLocalAsConfigData (OamScmM3uaLocalAsConfig **M3uaConfigPtrToPtr, U8 *row_count) 
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranM3uaLAsConfigTableApi *M3uaTblPtr=NULL;
   OamScmM3uaLocalAsConfig  *M3uaConfigPtr=NULL;
   strcpy(g_parameter.function_string, "M3uaLocAsTableApi()");

   dbSts = getallSigtranM3uaLAsConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranM3uaLAsConfigTableApi)), (unsigned char* )DbPtr, 15);
      M3uaConfigPtr = calloc (rowCount,sizeof(OamScmM3uaLocalAsConfig));
      *M3uaConfigPtrToPtr = M3uaConfigPtr;
      while (rowCount)
      {
         SCM_printf (SCM_DEBUG, "Read M3ua Loc As Table From DB\n");
         M3uaTblPtr  = (SigtranM3uaLAsConfigTableApi*)(DbPtr + i*rowSize);
         M3uaConfigPtr[i].localAsId       = (U16)M3uaTblPtr->localAsId;
         M3uaConfigPtr[i].asMode          = (U32)M3uaTblPtr->asMode;
         M3uaConfigPtr[i].sourcePointCode = (U32)M3uaTblPtr->sourcePointCode;
         M3uaConfigPtr[i].rkType          = (U32)M3uaTblPtr->rkType;
         M3uaConfigPtr[i].numAsp          = (U8)M3uaTblPtr->numAsp;
         M3uaConfigPtr[i].localAspId1     = (U16)M3uaTblPtr->localAspId1;
         M3uaConfigPtr[i].localAspId2     = (U16)M3uaTblPtr->localAspId2;
         M3uaConfigPtr[i].numbRc           = (U8)M3uaTblPtr->numbRc;
         M3uaConfigPtr[i].remAspRc1       = (U32)M3uaTblPtr->remAspRc1;
         M3uaConfigPtr[i].remAspRc2       = (U32)M3uaTblPtr->remAspRc2;
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

I_S32 GetRemoteAsConfigData (OamScmM3uaRemoteAsConfig  **M3uaConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranM3uaRAsConfigTableApi *M3uaTblPtr=NULL;
   OamScmM3uaRemoteAsConfig *M3uaConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetRemoteAsConfigData ()");

   dbSts = getallSigtranM3uaRAsConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(SigtranM3uaRAsConfigTableApi)), (unsigned char* )DbPtr, 15);
      M3uaConfigPtr = calloc (rowCount,sizeof(OamScmM3uaRemoteAsConfig));
      *M3uaConfigPtrToPtr = M3uaConfigPtr;
      while (rowCount)
      { 
         SCM_printf (SCM_DEBUG, "Read M3ua Rem As Table From DB\n");
         M3uaTblPtr  = (SigtranM3uaRAsConfigTableApi*)(DbPtr + i*rowSize);
         M3uaConfigPtr[i].remAsId       = (U16)M3uaTblPtr->remAsId;
         M3uaConfigPtr[i].remAsMode     = (U32)M3uaTblPtr->remAsMode;
         M3uaConfigPtr[i].remPointCode  = (U32)M3uaTblPtr->remPointCode;
         M3uaConfigPtr[i].rkType        = (U32)M3uaTblPtr->rkType;
         M3uaConfigPtr[i].numAsp        = (U8)M3uaTblPtr->numAsp;
         M3uaConfigPtr[i].remAspId1     = (U16)M3uaTblPtr->remAspId1;
         M3uaConfigPtr[i].remAspId2     = (U16)M3uaTblPtr->remAspId2;
         M3uaConfigPtr[i].timerProfileId= (U16)M3uaTblPtr->timerProfileId;
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


I_S32 GetM3uaTmrConfigData(OamScmM3uaTimerConfig  **M3uaConfigPtrToPtr, U16 profileId)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   I_U32 check = 0;
   void       *DbPtr=NULL;
   M3uaTmrConfigTableApi *M3uaTblPtr=NULL;
   OamScmM3uaTimerConfig *M3uaConfigPtr=NULL;
   strcpy(g_parameter.function_string, "GetRemoteAsConfigData ()");

   dbSts = getallM3uaTmrConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);

   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
      SCM_DUMP(0,(rowCount *sizeof(M3uaTmrConfigTableApi)), (unsigned char* )DbPtr, 15);
      M3uaConfigPtr = calloc (1,sizeof(OamScmM3uaTimerConfig));
      *M3uaConfigPtrToPtr = M3uaConfigPtr;
      while (rowCount)
      {
         M3uaTblPtr  = (M3uaTmrConfigTableApi*)(DbPtr + i*rowSize);
         if(M3uaTblPtr->profileId  == profileId)
          {
              check = 1;
              SCM_printf (SCM_DEBUG, "Read M3ua Tmr Table From DB\n");
              M3uaConfigPtr->tmrAsPend       = (U16)M3uaTblPtr->tmrAsPend;
              M3uaConfigPtr->tmrRetransLow   = (U16)M3uaTblPtr->tmrRetransLow;
              M3uaConfigPtr->tmrRetransHigh  = (U16)M3uaTblPtr->tmrRetransHigh;
              M3uaConfigPtr->tmrRetransMax   = (U16)M3uaTblPtr->tmrRetransMax;
              break;
          }

         rowCount--;
         i++;
      }
         free(DbPtr);
   }
   else
   {
      return dbSts;
   }
  
  if(check == 1)
      return 0;
  else
   {
     SCM_printf (SCM_DEBUG, "PROFILE NOT FOUND\n");
     return -1;
   }
}

/*AOIP : DB ROUTINES END*/
