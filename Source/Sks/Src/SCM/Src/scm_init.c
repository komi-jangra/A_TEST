#include "scm_localhashdef.h"
#include <scm_encaps.h>
U8 *configPath, *config;

/***************************************************************************/
/*This function initiallise SCM and set up SCM sever */
/***************************************************************************/


int scm_init()
{
 strcpy(g_parameter.function_string, "scm_init()");
 if((read_configfile()) ==0 )
   {
   SCM_printf(SCM_CRITICAL,"\nunable to read config env variables");
   return 0;
   }
 else
   SCM_printf(SCM_INFO,"\nRead config env variables successfully");
   init_global_variable();


 if (g_parameter.scm_server == 0)
    {
     g_parameter.scm_server = setup_scm_server( xxx_scm_port[ENT_SCM] );
     if (g_parameter.scm_server != 0 )
       {
        FD_SET(g_parameter.scm_server, &scm_server_fd);
        SCM_printf(SCM_MAJOR,"SCM INIT : SETUP COMMON SCM SERVER "
                    "AT PORT[%d]\n", xxx_scm_port[ENT_SCM]);
       }
     else/*AOIP START*/
       {
        SCM_printf(SCM_MAJOR,"SCM INIT : ERROR SCM SERVER CAN NOT OPEN!!!***\n ");
        return 0;
       }
        /*AOIP END*/
    }
  return 1;  
}

void init_global_variable()
{
 U8 loop;
 sem_signal.sem_num =  0;
 sem_signal.sem_op  =  0;
 sem_signal.sem_flg =  0;
 memset(timer_info, 0, (sizeof(timer_exp_ele) * 10));
 memset(&g_roll_back_flag, 0, sizeof(roll_back_flag));
 g_parameter.oam_up = 0;
 g_parameter.peer_link_del = 0;
 g_parameter.nwstk_stsUp_sent = 0;
 g_parameter.peer_link_del_resp = 0;
 g_parameter.peer_nwstk_up = 0;
 g_parameter.ss7_up_alarm = 0;
 g_parameter.noOam_resp_flag = 0;
 g_parameter.link_activated_flag = 0;
 g_parameter.no_of_retry_nwstk_cfg_wait = 0;
 g_parameter.nwstk_cfg_wait = 0;
 g_parameter.nwstk_msg = NULL;
 g_parameter.alarm_level = ALRM_LVL_MAJR;
 g_parameter.multicmd_msg = NULL; 
 memset(xxx_client_sockfd, -1, (9*sizeof(signed int)));
 timer_info[TIMER_MAPTCAP].timer_strt_flag = 0;
 FD_ZERO (&scm_server_fd);
 FD_ZERO (&client_fd);
 FD_ZERO (&server_fds);
 g_parameter.peer_map_tcap_cmdFlag= 0; 
 g_parameter.peer_nwstk_cmdFlag   = 0;
 g_parameter.nwstk_standby_respFlag   = 0;
 g_parameter.multicmd_standby_respFlag   = 0;
 g_parameter.nwstk_cfgIndFromPeerCard  = 0;
 g_parameter.link_config_flag   = 0;
 g_parameter.entity_up          = 0;
 g_parameter.scm_process_flag = 0;
 g_parameter.redundant_status = SCM_ACTIVE;
 g_parameter.g_card_state = SCM_ACTIVE;
 g_parameter.family = ITU_FAMILY;
 g_parameter.peer_nwstk_up = 0;
/*AOIP CHANGES*/
 timer_info[TIMER_BSSAP].timer_strt_flag = 0;
 timer_info[TIMER_SIGTRAN].timer_strt_flag = 0;
 g_parameter.sigtran_cfgComplete = 0;
 g_parameter.bssap_cfgComplete   = 0;
 g_parameter.Conn_Down_alarm_Resp_Pending = 0;
 g_parameter.map_tcap_msg        = NULL;
/*AOIP END*/
/*MANTIS ID:- 0032492*/
g_parameter.scm_scm_up = 0;
g_parameter.stby_bssap_config_wait = 0;
g_parameter.stby_sigtran_config_wait = 0;
/*MANTIS END*/
 init_hash_table();
 init_linkset_hash_table();

 for(loop = 0; loop<5; loop++)
  {
   xxx_severread_sockfd[loop] = -1;
  }
 return;
}

/***************************************************************************/
/*This function reads config file for scm client server
  ip adderess and port addresses */
/***************************************************************************/
int read_configfile()
{
 U8  filech, string_arr[100], stack_entity =0, ip_port_flag = 0, port_arr[12];
 U32 tmp_count = 0;
#ifdef SCM_ENV
 U32 loop;
 const char *config =NULL;
 strcpy(g_parameter.function_string, "read_configfile()");
 
/* used if config file not used */
 for(loop = 0; loop < 10; loop ++)
 { 
  xxx_scm_ip[loop] = (U8*)scm_malloc(20*sizeof(U8));
 }
/* comment end here */

 config = getenv("config_PP_IP");
 if(config != NULL)
 {
  strcpy(xxx_scm_ip[ENT_NWSTK], config);
  strcpy(xxx_scm_ip[ENT_NWSTK_DBG], config);
  strcpy(xxx_scm_ip[ENT_LAPD], config);


  config = getenv("config_CP_IP");
  if(config != NULL)
  strcpy(xxx_scm_ip[ENT_OAM], config);
   strcpy(xxx_scm_ip[ENT_SIGTRAN], config);
  if(config != NULL)
  config = getenv("config_PEER_CP_IP");
  if(config != NULL)
  strcpy(xxx_scm_ip[ENT_PEER_SCM], config);

  config = getenv("BSSAP_SERVER_PORT");
  if(config != NULL)
  xxx_scm_port[ENT_NWSTK] = atoi(config); 
  config = getenv("LME_DBG_PORT");
  if(config != NULL)
  xxx_scm_port[ENT_NWSTK_DBG] =atoi(config);
  config = getenv("SCM_LAPD_SERVER_PORT");
  if(config != NULL)
  xxx_scm_port[ENT_LAPD] =atoi(config);
  if(config != NULL)
  xxx_scm_port[ENT_SIGTRAN] =atoi(config);
  config = getenv("SCM_SERVER_PORT");
  if(config != NULL)
  xxx_scm_port[ENT_SCM] =atoi(config);
  config = getenv("SCM_SERVER_PORT");
  if(config != NULL)
  xxx_scm_port[ENT_PEER_SCM] =atoi(config);
  config = getenv("SCMIF_SERVER_PORT");
  if(config != NULL)
  xxx_scm_port[ENT_OAM] =atoi(config);
  SCM_printf (SCM_INFO,"PP IP: %s", xxx_scm_ip[ENT_NWSTK]);
  SCM_printf (SCM_INFO,"CP IP: %s", xxx_scm_ip[ENT_OAM]);
  SCM_printf (SCM_INFO,"ISIL config server Port: %d",  xxx_scm_port[ENT_NWSTK] );
  SCM_printf (SCM_INFO,"ISIL alarm reporting server Port: %d", xxx_scm_port[ENT_NWSTK_DBG]);
  SCM_printf (SCM_INFO,"ISIL LAPD server Port: %d", xxx_scm_port[ENT_LAPD]);
  SCM_printf (SCM_INFO,"SCM server Port: %d", xxx_scm_port[ENT_SCM]);
  SCM_printf (SCM_INFO,"Peer SCM server Port: %d", xxx_scm_port[ENT_PEER_SCM]);
  SCM_printf (SCM_INFO,"OAM server Port: %d", xxx_scm_port[ENT_OAM]);
  SCM_printf (SCM_INFO,"MAP/TCAP server Port: %d", xxx_scm_port[ENT_SIGTRAN]);
  SCM_printf (SCM_INFO,"TCAP server Port: %d", xxx_scm_port[ENT_CAP]);
 }
 else
 {
  SCM_printf (SCM_CRITICAL,"\tSCM EXIT: config env variables not set");
  return 0;
 }
return 1;
#endif 
/* Amaresh Commented the environment set */



#ifdef read_config_file
 FILE *fp;
 configPath = malloc(100);
 config = getenv("CONFIG");
 if(config != NULL)
 {
   strcpy(configPath, config);
   strcat(configPath, "scm_conf");
   SCM_printf(SCM_INFO,"config file path: %s", configPath);
   if((fp = fopen((const char *)configPath, "r")) == NULL)
   {
    return 0;
   }
 }
 else
 {
  SCM_printf (SCM_CRITICAL,"\tSCM EXIT: config path not set");
  return 0;
 }


filech = fgetc(fp); 

while ( filech != '$')
{
 
// ungetc(1, fp);
/* comment portion parsing start */
 while(1)
  {
   //filech = getc(fp); 
   tmp_count++;
   if ( tmp_count > 2000)
     {
      SCM_printf(SCM_CRITICAL,"\nfile in bad format");
      }
   if ( filech == '#')
    {
    while (filech != '\n')
          {
           filech = getc(fp); 
          }
    filech = getc(fp); 
    }
   else 
    break;
  }
/* comment portion parsing end */
/*parsing for spaces and new line start */
 while ( filech == ' '|| filech == '\n' || filech == '\t')
       {
        filech = getc(fp); 
       }
/*end*/
 if(filech == '$')
   {    /*AOIP PRINT*/
        SCM_printf (SCM_INFO,"PP IP: %s", xxx_scm_ip[ENT_NWSTK]);
        SCM_printf (SCM_INFO,"CP IP: %s", xxx_scm_ip[ENT_OAM]);
        SCM_printf (SCM_INFO,"SCM server Port     : %d", xxx_scm_port[ENT_SCM]);
        SCM_printf (SCM_INFO,"SIGTRAN IP          : %s", xxx_scm_ip[ENT_SIGTRAN]);
        SCM_printf (SCM_INFO,"BSSAP IP            : %s", xxx_scm_ip[ENT_BSSAP]);
        SCM_printf (SCM_INFO,"OAM IP              : %s", xxx_scm_ip[ENT_OAM]);
        SCM_printf (SCM_INFO,"PEER SCM IP         : %s", xxx_scm_ip[ENT_PEER_SCM]);
        SCM_printf (SCM_INFO,"SIGTRAN server Port : %d", xxx_scm_port[ENT_SIGTRAN]); /*This is Sigtran Port*/
        SCM_printf (SCM_INFO,"BSSAP server Port   : %d", xxx_scm_port[ENT_BSSAP]); /*This is BSSAP Server Port*/
        SCM_printf (SCM_INFO,"OAM server Port     : %d", xxx_scm_port[ENT_OAM]);
        SCM_printf (SCM_INFO,"PEER SCM server Port: %d", xxx_scm_port[ENT_PEER_SCM]);
        /*AOIP END*/
   return 1;
   } 

 tmp_count = 0;
 //ungetc(1, fp);

/*get the string and store in array */
 while (filech != ' ')
     { 
      string_arr[tmp_count] =filech;
      filech = getc(fp); 
      tmp_count++;
     }
    string_arr[tmp_count] = '\0';
/*end here*/

  match_string (string_arr, &stack_entity, &ip_port_flag);

  /*parsing for spaces and new line start */
 while ( filech == ' '|| filech == '\n' || filech == '\t' || filech == ':' )
       {
        filech = getc(fp); 
       }
  /*end*/

  if (ip_port_flag == IP)
    {
     tmp_count = 0;
      /*get the IP and store in array */
     xxx_scm_ip[stack_entity] = (U8*)scm_malloc(20*sizeof(U8));
     while (filech != ' ')
         {
             if ( filech == '\n')
                 break;  
           //ungetc(1, fp);
           (xxx_scm_ip[stack_entity])[tmp_count] = filech;
           filech = getc(fp);  
           tmp_count++;
         }
     (xxx_scm_ip[stack_entity])[tmp_count] = '\0';
     /*end here*/
    } 
  
  if (ip_port_flag == PORT)
    {
     tmp_count = 0;
     /*get the PORT and store in array */
     while (filech != ' ')
     //while (filech != ' ')
        {
             if ( filech == '\n')
                 break;  
         //ungetc(1, fp);
         port_arr[tmp_count] = filech;
         filech = getc(fp);  
         tmp_count++;
         }
      port_arr[tmp_count] = '\0';
     xxx_scm_port[stack_entity] = atoi((char *) port_arr);
     /*end here*/
    }
   tmp_count = 0;
   
 }
 fclose(fp);
 free(configPath);
 configPath=NULL;
#endif
}


#ifdef read_config_file

int MATCH(U8 *string_cmp, U8* B, U16 C, U16 D, U8* stack_entity, U8* ip_port_flag)
{
  U16 cmp_result;    
  cmp_result = strcmp(string_cmp,B);   
  strcpy(g_parameter.function_string, "MATCH()");
  if(cmp_result == 0)                 
    {                                
     *stack_entity = C;              
     *ip_port_flag = D;                 
     return 1; 
    }
 return 0;
}


void match_string (U8* string_arr, U8* stack_entity, U8* ip_port_flag)
{
  U8  cmp_result=0, tmp_count=0;

  strcpy(g_parameter.function_string, "match_string()");
    while(cmp_result != 1)
      {
       tmp_count++;
      if(tmp_count == 20)
        {
        SCM_printf(SCM_INFO,"\nextra entry scm config file:  '%s'", string_arr);
        return;
        }
      if((cmp_result = MATCH ("MTP3_IP_ADDRESS" , string_arr, ENT_NWSTK, IP, stack_entity, ip_port_flag)) == 1)
        return;;
      if((cmp_result = MATCH ("DBG_IP_ADDRESS"  , string_arr, ENT_NWSTK_DBG, IP, stack_entity, ip_port_flag)) ==1)
        return;
      if((cmp_result = MATCH ("BSSAP_IP_ADDRESS", string_arr, ENT_BSSAP, IP, stack_entity, ip_port_flag)) ==1)       /*AOIP*/
         return;
      if(( cmp_result = MATCH ("SIGTRAN_IP_ADDRESS", string_arr, ENT_SIGTRAN, IP, stack_entity, ip_port_flag)) == 1) /*AOIP*/
        return;
      if((cmp_result = MATCH ("CAP_IP_ADDRESS"  , string_arr, ENT_CAP, IP, stack_entity, ip_port_flag)) == 1)
        return ;
      if((cmp_result = MATCH ("LAPD_IP_ADDRESS" , string_arr, ENT_LAPD, IP, stack_entity, ip_port_flag)) == 1)
        return ;
      if((cmp_result = MATCH ("LME_MTP3_PORT"   , string_arr, ENT_NWSTK, PORT, stack_entity, ip_port_flag)) == 1)
         return;
      if((cmp_result = MATCH ("LME_DBG_PORT"    , string_arr, ENT_NWSTK_DBG, PORT, stack_entity, ip_port_flag)) ==1)
         return;
      if((cmp_result = MATCH ("LME_BSSAP_PORT"  , string_arr, ENT_BSSAP, PORT, stack_entity, ip_port_flag)) ==1)     /*AOIP*/
         return;
      if((cmp_result = MATCH ("LME_SIGTRAN_PORT", string_arr, ENT_SIGTRAN, PORT, stack_entity, ip_port_flag)) ==1)   /*AOIP*/
       return;
      if((cmp_result = MATCH ("LME_CAP_PORT"    , string_arr, ENT_CAP , PORT, stack_entity, ip_port_flag)) == 1)
        return;
      if((cmp_result = MATCH ("LME_LAPD_PORT"   , string_arr, ENT_LAPD, PORT, stack_entity, ip_port_flag)) ==1)
       return;
      if((cmp_result = MATCH ("SCM_SERVER_PORT" , string_arr, ENT_SCM, PORT, stack_entity, ip_port_flag)) ==1)   /*AOIP*/
         return;
      if((cmp_result = MATCH ("PEER_SCM_IP"     , string_arr, ENT_PEER_SCM, IP, stack_entity, ip_port_flag)) == 1)
         return;
      if((cmp_result = MATCH ("PEER_SCM_PORT"   , string_arr, ENT_PEER_SCM, PORT, stack_entity, ip_port_flag)) == 1) 
         return;
     // MATCH ("PEER_SCM_CLIENT_PORT",  NULL, &scm_peer_client_port, PORT, 20, stack_entity, ip_port_flag);/*QUERY*/
      if((cmp_result = MATCH ("OAM_IP",  string_arr,  ENT_OAM, IP, stack_entity, ip_port_flag)) ==1)
        return;
      if((cmp_result = MATCH ("OAM_CLIENT_PORT",  string_arr, ENT_OAM, PORT, stack_entity, ip_port_flag)) == 1)
         return;
 
      }
 return;
              
}

#endif
