#include "scm_localhashdef.h"
#include <scm_encaps.h>

U16 Check_Self_psp_and_Bss_state(U16 *, U16 *, U16 *);



       U8    sub_entity;
       U32   linkset_val = 0;
       U32   linkcode_val = 0;
       U32   dpc_val = 0;
       U32   ni_val = 0;
       U32   pc_val = 0;
       U32   pcm_val = 0;
       U32   ts_val  = 0;
       U32   userpart_val = 0;
       U32   protocol_class_val = 0;
       U32   ssn_val = 0;
       U32   message_type_val = 0;
       U32   isup_alarm_opc = 0;
       U32   isup_alarm_dpc = 0;
       U32   isup_alarm_cic = 0;
       U32   isup_alarm_cpc_state = 0;
       U32   isup_alarm_lm_state = 0;
       U32   isup_alarm_rm_state = 0;
       U32   isup_alarm_trigger_message = 0;
       U32   alarm_infostring [100];
       U32   No_of_element = 0; 
S32 GetCurTimeStamp(U32 *timeStamp)
{
   if(time((time_t *)timeStamp) < 0)
    return (0 );//- errno);
   else
    return 0;
}/*GetCurTime*/


/*************************************************************
* Name:                                                      *  
* void report_alarm_to_oam (U16 , U8 alarm_level, U8 entity) *
*                                                            *
* Description:                                               *
* 1) Fills OamScmAlarmsReport Structure.                     *
* 2) If Active card then Reports Alarm to CFG                *
* 3) If Standby card then Reports Alarm to ACtive Card       *
**************************************************************/

void report_alarm_to_oam ( U16 alarm_id, U8 alarm_level, U8 entity)
{
 U16 Length, ret_val;
 U8 cmd_buff[100];
 strcpy(g_parameter.function_string, "report_alarm_to_oam()");
 Length = sizeof(OamScmAlarmsReport);
 OamScmAlarmsReport  *scmAlarmsReport = NULL;
 scmAlarmsReport = (OamScmAlarmsReport*)scm_malloc(sizeof(OamScmAlarmsReport));
 scmAlarmsReport->alarmdata.moduleName = entity;
 scmAlarmsReport->alarmdata.alarmId    = alarm_id;
 scmAlarmsReport->alarmdata.alarmLevel = alarm_level; 
 scmAlarmsReport->alarmdata.numOfStr = 0; 
 scmAlarmsReport->alarmdata.stringOffset = 0; 
 scmAlarmsReport->alarmdata.numParams  = No_of_element;
 GetCurTimeStamp(&scmAlarmsReport->alarmdata.alarmTime);
 if(No_of_element != 0 )
 {
  scmAlarmsReport->alarmdata.params[0]  = alarm_infostring[0];
 }
 else
 {
  scmAlarmsReport->alarmdata.params[0]  = 0;
 }
 memcpy(cmd_buff, scmAlarmsReport, Length);
 if(No_of_element > 1)
 {
  memcpy(&cmd_buff[Length], &alarm_infostring[1], ((No_of_element - 1)* sizeof(U32)));
 }
 Length = (sizeof(U32) * (No_of_element-1)) + Length;
 form_oam_header(cmd_buff, SCM_OAM_ALARM_IND, 0, 0, 0, Length);
  

 //SCM_DUMP(0, Length, cmd_buff, 15);
    /* SEND ALARM TO OAM */
 SCM_printf (SCM_MAJOR, "\nSCM -> OAM 'Stack Alarm' moduleId: %d", entity);

 
 if((g_parameter.redundant_status != SCM_ACTIVE) && ((entity == MODULE_MTP3) || (entity == MODULE_SCCP)
 ||(entity == MODULE_BSSAP) || (entity == MODULE_MTP2) || (entity == MODULE_SIGTRAN)) && (g_parameter.g_card_state != SCM_AIP))
 {
   SCM_printf (SCM_INFO, "[ALARM - %s #%d] reporting to PEER SCM\n", get_alarm_string(alarm_id), alarm_id);
   ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_PEER_SCM, Length); 
   if(ret_val == 0)
     {
      SCM_printf (SCM_CRITICAL, "[ALARM - %s #%d] Report to peer ACTIVE SCM is failed", get_alarm_string(alarm_id), alarm_id);
     }
 }
 else
 {
   SCM_printf (SCM_INFO, "[ALARM - %s #%d] reporting to OAM", get_alarm_string(alarm_id), alarm_id);
   ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_OAM, Length); 
   if(ret_val == 0)
     {
      SCM_printf (SCM_CRITICAL, "[ALARM - %s #%d] Reprot to OAM is failed", get_alarm_string(alarm_id), alarm_id);
     }
 }

   free(scmAlarmsReport);
   scmAlarmsReport = NULL;
   
} 
void process_scm_alarm(U16 alarm_id)
{
 U8 appId;
 U8  alarm_level;
 strcpy(g_parameter.function_string, "process_scm_alarm()");
 No_of_element = 0;
 alarm_level = ALRM_LVL_MINR;
 switch(alarm_id)
 {
  case SS7_UP:
       if(xxx_client_sockfd [ENT_OAM] < 0)
        {
         SCM_printf(SCM_MAJOR,"\n ss7up alarm can not be sent to oam: cause oam down ");
         return;
        } 
       appId = MODULE_MSC;
       g_parameter.ss7_up_alarm = 0;
       break;
 
  case SS7_DOWN:
       if(xxx_client_sockfd [ENT_OAM] < 0)
        {
         SCM_printf(SCM_MAJOR,"\n ss7down alarm can not be sent to oam: cause oam down ");
         return;
        }
       g_parameter.nwstk_stsUp_sent = 0; 
       appId = MODULE_MSC; 
       break;
 }
 memset(alarm_infostring, 0, 100*sizeof(U32));
 SCM_printf(SCM_MAJOR,"\n SCM ALARM ID : %d", alarm_id);
 SCM_printf(SCM_INFO,"\n SCM ALARM LEVEL : %d", alarm_level);
 report_alarm_to_oam ( alarm_id, alarm_level, appId );
 SCM_printf(SCM_INFO,"\t|||||||||||||||||||||||||||||||||||||||||\n");
 return;

 
} 

void process_Lapd_alarm(U8* msg_buff)
{
 int alarm_id, alarm_level;
 strcpy(g_parameter.function_string, "process_Lapd_alarm()");
 No_of_element = 2; 
 alarm_id    = msg_buff[5];
 alarm_id    = (((alarm_id << 8)& 0xff00) | msg_buff[4]);
 alarm_level = msg_buff[6];
 memset(alarm_infostring, 0, 100*sizeof(U32));
 alarm_infostring [0] = 0;
 SCM_printf(SCM_MAJOR,"\n LAPD ALARM ID : %d", alarm_id);
 /* mapping for oam alarm Id */
 switch(alarm_level)
 {
   case 1:
        alarm_level = ALRM_LVL_INFO;
        break;
   case 2:
        alarm_level = ALRM_LVL_CRIT;
        break;
        
   case 3:
        alarm_level = ALRM_LVL_MAJR;
        break;
   case 4:
        alarm_level = ALRM_LVL_MINR;
        break;
 }   
 /* end */
 if((alarm_id >= LAPD_MIN_ALARM_VAL && alarm_id <= LAPD_MAX_ALARM_VAL))
  {
   alarm_infostring[0] = (U32)msg_buff[7]; /* LAPD Tei value */
   alarm_infostring[1] = (U32)msg_buff[8]; /* LAPD Sapi value */
   SCM_printf(SCM_INFO,"\n LAPD ALARM LEVEL : %d", alarm_level);
   SCM_printf(SCM_INFO,"\n Alarm Tei Val : %d" , msg_buff[7]);
   SCM_printf(SCM_INFO,"\n Alarm Sapi Val : %d", msg_buff[8]);
   report_alarm_to_oam ( alarm_id, alarm_level, MODULE_LAPD );
   SCM_printf(SCM_INFO,"|||||||||||||||||||||||||||||||||||||||||\n");
  }
 else
 {
   SCM_printf(SCM_INFO,"Alarm Id maping not stored at scm\n");
   SCM_printf(SCM_INFO,"\t|||||||||||||||||||||||||||||||||||||||||\n");
 
 }
 return;
}

int literal_present(U8 chr)
{
 strcpy(g_parameter.function_string, "literal_present()");
      if(chr == '0' || chr == '1' || chr == '2' || chr == '3' || chr == '4' ||
         chr == '5' || chr == '6' || chr == '7' || chr == '8' || chr == '9')
           return (1);
      else
           return (0);
}

void process_alarm_nwstk(U8* msg_buff)
{
     
    #define PV (void *)
    U8 cmd_buff[200];
    char intl_alarm_id[5];
    char intl_severity[5];
    char intl_linkset[5];
    char intl_linkcode[5];
    char intl_dpc[5];
    char intl_ni[5];
    char intl_ts[5];
    char intl_userpart[5];
    char intl_protocol_class[5];
    char intl_ssn[5];
    char intl_message_type[5];
    int rs = 0, Length, AlarmSndFlg =1;
    int counter, alarm_id_val = 0, severity_val = 0,  db_alarm_id_val=0;
    int  v,  double_par ;
    int offset = 0;
    memset(alarm_infostring, 0, 100*sizeof(U32));
    strcpy(g_parameter.function_string, "process_alarm_nwstk()");
    No_of_element = 0;

    SCM_printf(SCM_INFO,"\n\tALARM DATA from NW STACK :\n");
    Length = ((msg_buff[2] << 8) & 0xff00) | msg_buff[3];
    if( Length > 200)
    {
       SCM_printf(SCM_CRITICAL,"\n\tLength Exceed the limit(200Byte) :\n");
       return ;
    } 
    cmd_buff[Length] = '\0';
    cmd_buff[Length + 1] = '\0';
    strncpy(cmd_buff, &msg_buff[4], Length);
    SCM_printf(SCM_INFO,"%s",cmd_buff);
    SCM_printf(SCM_INFO,"\n");
    counter = 0;
    v = 0;
    while(cmd_buff[counter]!='|' &&
          cmd_buff[counter]!='A' &&
          cmd_buff[counter]!='N')
      {
       /* Extract Alarm ID */
        intl_alarm_id[v] = cmd_buff[counter];
        counter = counter + 1;
        v = v + 1;
      }
   intl_alarm_id[v] = '\0';
   alarm_id_val = atoi((char *)intl_alarm_id);
   /* In case of 'A' and 'N' */
   while(cmd_buff[counter]!='|')
         counter = counter + 1;
        counter = counter + 1;
   while(cmd_buff[counter]!='|')
         counter = counter + 1;
   counter = counter + 1;
   v = 0;
   while(cmd_buff[counter]!='|')
      {
        /* Extract Severity */
        intl_severity[v] = cmd_buff[counter];
        counter = counter + 1;
        v = v + 1;
      }

  intl_severity[v] = '\0';
  severity_val = atoi((char *)intl_severity);

  /* DATA RECEIVED FROM NWSTK */
  SCM_printf(SCM_MAJOR,"\tALARM RECEIVED FROM NWSTK\n");
	SCM_printf(SCM_INFO,"\nBUFFER RECEIVED from NWSTACK SOCKET" );
  SCM_DUMP(0, Length, msg_buff, 15);
  SCM_printf(SCM_INFO,"\t|||||||||||||||||||||||||||||||||||||||||\n");
  SCM_printf(SCM_MAJOR,"\n NWSTK -> SCM 'Alarm received' 'Alarm Id : %d, Alarm Lvl: %d'",
             alarm_id_val, severity_val);
  if((alarm_id_val == 9004) || (alarm_id_val == 9005))
   {
     SCM_printf(SCM_MAJOR,"alarm not reported to oam ");
     return;
   }
  if(alarm_id_val != 2900)
   {  

       db_alarm_id_val = alarm_id_val;

          if ( (alarm_id_val >= 2001 && alarm_id_val <= 2528) ||(alarm_id_val == 2800) || (alarm_id_val == 2801) )
          {
               sub_entity = MODULE_MTP3;
          }
          if ( alarm_id_val >= 16   && alarm_id_val <= 686  )
          {
               sub_entity = MODULE_SCCP;
          }
          if ( alarm_id_val >= 5101 && alarm_id_val <= 5141 )
          {
               sub_entity = MODULE_BSSAP;
          }
          if ( alarm_id_val >= 12000 )
          {
               sub_entity = MODULE_MTP2;
          }
           /* it will return no. of element value for mtp3 alarms */ 
           checkNoOfElementToReport(sub_entity, &No_of_element, &double_par, 	alarm_id_val);   
  
       counter = 0;        
  
       /* extract parameter values in named array string */  
       #define CASE_1(C,P) case C: \
               P[v] = cmd_buff[counter]; \
               break;    
       /* extract value from value named array string */ 
      #define CASE_T(P,V) \
              V = atoi((char *)P);

            while(cmd_buff[counter]!='\0')
                 counter = counter + 1;

        /*Alarm String Parsing */     
          
       switch(double_par)
       {
            
         case ALARM_DPC_SSN_NI:
         case ALARM_DPC_NI_LS:
         case ALARM_DPC_LS_LN:
         {     /* bring array offset at first element position */ 
               while((rs = literal_present(cmd_buff[counter]))!=1) counter --;
               while((rs = literal_present(cmd_buff[counter]))==1) counter --;
               while((rs = literal_present(cmd_buff[counter]))!=1) counter --;
               while((rs = literal_present(cmd_buff[counter]))==1) counter --;
               while((rs = literal_present(cmd_buff[counter]))!=1) counter --;
               while((rs = literal_present(cmd_buff[counter]))==1) counter --;
               counter = counter + 1;
               v = 0;
              while(((rs = literal_present(cmd_buff[counter]))==1) && (cmd_buff[counter] != '\0'))
              {
               switch(double_par) 
               {
                CASE_1(ALARM_DPC_SSN_NI, intl_dpc);
                CASE_1(ALARM_DPC_NI_LS,  intl_dpc);
                CASE_1(ALARM_DPC_LS_LN,  intl_dpc);
               }
               counter++;
               v = v+1; 
              }       
              intl_dpc[v] = '\0'; 
              v = 0;
              while(((rs = literal_present(cmd_buff[counter]))!=1) && (cmd_buff[counter] != '\0')) counter ++;
              
              while(((rs = literal_present(cmd_buff[counter]))==1) && (cmd_buff[counter] != '\0'))
              {
               switch(double_par)
               {
                CASE_1(ALARM_DPC_SSN_NI, intl_ssn);
                CASE_1(ALARM_DPC_NI_LS,  intl_ni);
                CASE_1(ALARM_DPC_LS_LN,  intl_linkset);
               }
               counter++;
               v = v+1; 
              }
              intl_ssn[v] = '\0'; 
              intl_ni[v] = '\0'; 
              v = 0;
  
              while(((rs = literal_present(cmd_buff[counter]))!=1) && (cmd_buff[counter] != '\0')) counter ++;
 
              while(((rs = literal_present(cmd_buff[counter]))==1) && (cmd_buff[counter] != '\0'))
              {
               switch(double_par)
               {
                CASE_1(ALARM_DPC_SSN_NI, intl_ni);
                CASE_1(ALARM_DPC_NI_LS,  intl_linkset);
                CASE_1(ALARM_DPC_LS_LN,  intl_linkcode);
               }
               counter++;
               v = v+1; 
              }

              intl_ni[v]  = '\0'; 
              intl_linkset[v] = '\0'; 
              v = 0;
             
             switch(double_par)
              {  
                 case ALARM_DPC_SSN_NI: 
                      CASE_T(intl_dpc, dpc_val);
                      CASE_T(intl_ssn, ssn_val);
                      CASE_T( intl_ni , ni_val);
                      break;
                   
                 case ALARM_DPC_LS_LN:
                      CASE_T( intl_dpc, dpc_val);
                      CASE_T( intl_linkset, linkset_val);
                      CASE_T( intl_linkcode, linkcode_val);
                      break;

                 case ALARM_DPC_NI_LS:
                      CASE_T( intl_dpc, dpc_val);
                      CASE_T( intl_ni , ni_val);
                      CASE_T( intl_linkset, linkset_val);
                      break;
               }
          break;

          } 

         case ALARM_LS_LN:
         case ALARM_DPC_NI:
         case ALARM_PC_SSN:
         case ALARM_DPC_CIC:
          {
               while((rs = literal_present(cmd_buff[counter]))!=1) counter --;
               while((rs = literal_present(cmd_buff[counter]))==1) counter --;
               while((rs = literal_present(cmd_buff[counter]))!=1) counter --;
               while((rs = literal_present(cmd_buff[counter]))==1) counter --;
 
              v = 0;
               counter = counter + 1;
              while(((rs = literal_present(cmd_buff[counter]))==1) && (cmd_buff[counter] != '\0'))
              {
               switch(double_par) 
               {
                CASE_1(ALARM_LS_LN, intl_linkset);
                CASE_1(ALARM_DPC_NI, intl_dpc);
                CASE_1(ALARM_DPC_CIC,  intl_dpc);
                CASE_1(ALARM_PC_SSN,  intl_dpc);
               }
               counter++;
               v = v+1;
              }       
              
              intl_dpc[v]  = '\0'; 
              intl_linkset[v] = '\0'; 
              v = 0;
              while(((rs = literal_present(cmd_buff[counter]))!=1) && (cmd_buff[counter] != '\0')) counter ++;
              
              while(((rs = literal_present(cmd_buff[counter]))==1) && (cmd_buff[counter] != '\0'))
              {
               switch(double_par)
               {
                CASE_1(ALARM_LS_LN, intl_linkcode);
                CASE_1(ALARM_DPC_NI, intl_ni);
                CASE_1(ALARM_DPC_CIC,  intl_ts);
                CASE_1(ALARM_PC_SSN,  intl_ssn);
               }
               counter++;
               v = v+1;
              }
  
              intl_ni[v]  = '\0'; 
              intl_linkcode[v] = '\0'; 
              intl_ts[v] = '\0'; 
              intl_ssn[v] = '\0'; 
              v = 0;

             switch(double_par)
              {
                case ALARM_LS_LN:
                     CASE_T( intl_linkset,linkset_val);
                     CASE_T(intl_linkcode, linkcode_val);
                     break;
                case ALARM_DPC_NI:     
                     CASE_T( intl_dpc, dpc_val);
                     CASE_T( intl_ni, ni_val);
                     break;
                case ALARM_PC_SSN:     
                     CASE_T(  intl_dpc, dpc_val);
                     CASE_T(  intl_ssn, ssn_val);
                     break;
                case ALARM_DPC_CIC:     
                     CASE_T(  intl_dpc, dpc_val);
                     CASE_T(  intl_ts, ts_val);
                     break;
               }
          break;
          } 

         case ALARM_DPC:
         case ALARM_MSGTYPE:
         case ALARM_PROTOCOL_CLS:
         case ALARM_SSN:
         case ALARM_LS:
         case ALARM_UP: 
          {
               while((rs = literal_present(cmd_buff[counter]))!=1) counter --;
               while((rs = literal_present(cmd_buff[counter]))==1) counter --;
              
              v = 0;
               counter = counter + 1;
 
              while(((rs = literal_present(cmd_buff[counter]))==1) && (cmd_buff[counter] != '\0'))
              {
               switch(double_par) 
               {
                CASE_1(ALARM_DPC, intl_dpc);
                CASE_1(ALARM_MSGTYPE, intl_message_type);
                CASE_1(ALARM_PROTOCOL_CLS,  intl_protocol_class);
                CASE_1(ALARM_SSN,  intl_ssn);
                CASE_1(ALARM_LS,  intl_linkset);
                CASE_1(ALARM_UP,  intl_userpart);
               }
               counter++;
               v = v+1;
              }       
              intl_dpc[v] = '\0'; 
              intl_message_type[v] = '\0'; 
              intl_protocol_class[v] = '\0'; 
              intl_ssn[v] = '\0'; 
              intl_linkset[v] = '\0'; 
              intl_userpart[v] = '\0'; 
              
  
             switch(double_par)
              {  
               case ALARM_DPC: 
                   CASE_T( intl_dpc,dpc_val);
                   break;
               case ALARM_MSGTYPE: 
                CASE_T( intl_message_type, message_type_val);
                   break;
               case ALARM_PROTOCOL_CLS: 
                CASE_T(  intl_protocol_class, protocol_class_val);
                   break;
               case ALARM_SSN: 
                CASE_T(  intl_ssn, ssn_val);
                   break;
               case ALARM_LS: 
                CASE_T( intl_linkset, linkset_val);
                   break;
               case ALARM_UP: 
                CASE_T( intl_userpart, userpart_val);
                   break;
               }
          break;
          } 
                
         case ALARM_NO_ELMNT:
              /* no element value */
              break;             
         case ALARM_DISCARDED:
              SCM_printf(SCM_INFO,"\n\t Alarm Discarded 'Cause: no mapping present at OAM'");     
              AlarmSndFlg = 0; 
              break;
       }
     #undef CASE_1
     #undef CASE_T

      /* Discard the alarm */
			 if(AlarmSndFlg  == 0 )
         { 
          return ;  
         } 
 

                /* DISPLAY VALUES */
                switch (double_par)
                {
                 case ALARM_DPC_SSN_NI:         
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  DPC : %d\n",  dpc_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  SSN : %d\n",  ssn_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  NI : %d\n",  ni_val);
                      break;
                 case ALARM_DPC_NI_LS:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  DPC : %d\n",  dpc_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  NI : %d\n",  ni_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  LINKSET ID : %d\n",  linkset_val);
                      break;
                 case ALARM_LS_LN:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  LINKSET ID : %d\n",  linkset_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  LINKCODE ID : %d\n",  linkcode_val);
                      break;
                 case ALARM_DPC_NI:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  DPC : %d\n",  dpc_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  NI : %d\n",  ni_val);
                      break;
                 case ALARM_DPC_LS_LN:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  DPC : %d\n",  dpc_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  LINKSET ID : %d\n",  linkset_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  linkcode: %d\n",  linkcode_val);
                      break;
                 case ALARM_PC_SSN:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  DPC : %d\n",  dpc_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  SSN : %d\n",  ssn_val);
                      break;
                 case ALARM_DPC_CIC:         
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  DPC : %d\n",  dpc_val);
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  CIC : %d\n",  ts_val);
                      break;
                 case ALARM_DPC:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  DPC : %d\n",  dpc_val);
                      break;
                 case ALARM_UP:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  USER PART : %d\n",  userpart_val);
                      break;
                 case ALARM_MSGTYPE:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  MSG TYPE : %d\n",  message_type_val);
                      break;
                 case ALARM_PROTOCOL_CLS:
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  PROTOCOL CLASS : %d\n",  protocol_class_val);
                      break;
                 case ALARM_SSN:         
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  SSN : %d\n",  ssn_val);
                      break;
                 case ALARM_LS:         
                      SCM_printf(SCM_INFO,"\tSCM ALRM :  LINKSET ID : %d\n",  linkset_val);
                      break;
                }
   }
  else
   {
      SCM_printf(SCM_INFO,"\tSCM ALRM :  GTT  Alarm dumped");
    
   }
           /*   parse_gtt_string(gtt_string, msg_buff); */
     
        switch(No_of_element)
         {
          case 0:
              alarm_infostring[0] = 0;
              break;

          case 1:
             switch(double_par)
             {
               case ALARM_DPC:
                    alarm_infostring[0] = dpc_val;/*dpc value */
                    break;
               case ALARM_MSGTYPE:
                    alarm_infostring[0] = message_type_val;/*dpc value */
                    break;
               case ALARM_PROTOCOL_CLS:
                    alarm_infostring[0] = protocol_class_val;/*dpc value */
                    break;
               case ALARM_SSN:
                    alarm_infostring[0] = ssn_val;/*dpc value */
                    break;
               case ALARM_LS:
                    alarm_infostring[0] = linkset_val;/*dpc value */
                    break;
               case ALARM_UP: 
                    alarm_infostring[0] = userpart_val;/*dpc value */
                    break;
             } 
            break;      

          case 2:
             switch(double_par)
             {
               case ALARM_LS_LN:
                   alarm_infostring[0] = linkset_val;/*linkset value */
                   alarm_infostring[1] = linkcode_val;/*linkcodec value */
                   break;
               case ALARM_DPC_NI:
                   alarm_infostring[0] = dpc_val;
                   alarm_infostring[1] = ni_val;
                   break;
               case ALARM_PC_SSN:
                    alarm_infostring[0] = dpc_val;
                    alarm_infostring[1] = ssn_val;
                   break;
               case ALARM_DPC_CIC:
                   alarm_infostring[0] = dpc_val;
                   alarm_infostring[1] = ts_val;
                   break;
              }
             break;
          case 3:
             switch(double_par)
             {
              case ALARM_DPC_NI_LS:  
                   alarm_infostring[0] = dpc_val;
                   alarm_infostring[1] = ni_val;
                   alarm_infostring[2] = linkset_val;
                   break;
              case ALARM_DPC_SSN_NI:  
                   alarm_infostring[0] = dpc_val;
                   alarm_infostring[1] = ssn_val;
                   alarm_infostring[2] = ni_val;
                   break;
               case ALARM_DPC_LS_LN:
                   alarm_infostring[0] = dpc_val;
                   alarm_infostring[1] = linkset_val;/*linkcodec value */
                   alarm_infostring[2] = linkcode_val;/*linkcodec value */
                   break;
             }
         break;
        }     

        SCM_printf(SCM_INFO,"\t|||||||||||||||||||||||||||||||||||||||||\n");

        /* mapping for alarm severity */
        switch(severity_val)
        {
           case 1:
               severity_val = ALRM_LVL_CRIT;
               break;  
           case 2:
               severity_val = ALRM_LVL_MAJR;
               break;  
           case 4:
               severity_val = ALRM_LVL_MINR;
               break;  
           case 8:
               severity_val = ALRM_LVL_INFO;
               break;  
           default:
               severity_val = ALRM_LVL_INFO;
               break;  
              
        }
        report_alarm_to_oam ( alarm_id_val + offset, severity_val,
                              sub_entity );
        

    return ;
}

    
  #define MAP  1
  #define TCAP 0
 /*AOIP*/
  #define SIGTRAN TCAP
 /*AOIP end*/

/**********************************************************************************************************
***********************************************************************************************************
* Name :                                                                                                  *
* void process_sigtran_stack_alarm(S32, U8 *, S32)                                                        *
*                                                                                                         *
* Description:                                                                                            *
* 1) Processes Alarms from Sigtran.                                                                       *
* 2) On Conn DOWN [9011] Triggers Admin command.                                                          *
* 3) Fills Key From Sigtran in the alarm_infostring.                                                          *
* 4) calls "report_alarm_to_oam()"                                                                        *
*                                                                                                         *  
* ALARM Format From Sigtran:                                                                              *
*                                                                                                         *
*      |  API id (1 octet)         | // 0x63 Api-id Fixed for All Alarms from SIGTRAN                     *
*      |---------------------------|                                                                      *
*      |  Version id (1 octet)     | // value always=1                                                    *
*      |---------------------------|                                                                      *
*      |  No. of elements (1 octet)| // its value after length                                            *
*      |---------------------------|                                                                      *
*      |  Length (2 octets) LSB    | // Length means includes header+data                                 *
*      |- - - - - - - - - - - - - -|                                                                      *
*      |               |MSB        |                                                                      *
*      |---------------------------|                                                                      *
*      |  Module-Id(1 octet)       | // value is 0x05 Fixed                                               *
*      |---------------------------|                                                                      *
*      |  Alarm-Id (2 octet)       | // Values are 443,444 then 9000 onwards according to Alarm sheet     *
*      |---------------------------|                                                                      *
*      |  Alarm-level (1 octet)    | // Info,Major,Minor,Critical,Clear,warning as R2.9 BSC Relesae       *
*      |---------------------------|                                                                      *
*      |  Key # 1                  | // slotId,AspId,AsId as per configuration data type                  *
*      |---------------------------|                                                                      *
*      |  Key # 2                  |                                                                      *
*      |---------------------------|                                                                      *
*      |  Key # ...                |                                                                      *
*      |---------------------------|                                                                      *
*      |  Key  # n                 |                                                                      *
*      |___________________________|                                                                      *
*                                                                                                         *
***********************************************************************************************************
***********************************************************************************************************/

void process_sigtran_stack_alarm(S32 nbytes, U8 *msg_buff, S32 entity)
{

   int alarm_id, alarm_level;
   int entity_alarm;
   int report_entity_id, isup_cpc_state;
   U32   found = 0; 
  /* No_of_element = 0;  *//*ALARM_IMPL Using global variable */
   /*AOIP ALARM*/
   U32 Point_Code = 0;
   U8  SSN        = 0;
   U16 Slot_Id    = 0;  
   U16 AsOrAsp_Id = 0;
   U16  state = 0, no_of_asp = 0, length = 0, ret_val;
   U16 asp_id[2], asp_state[2], lv = 0, tr_opcode = 0;
   U8 *cmd_buff;
   /*AOIP END*/
   /*MANTIS Id:- 0032193*/
   U16 admin_state;
   U16 opr_status, Asp_id;
   U16 Unlocked = 1;
   U16 Disabled = 0;
   /*MANTIS End*/
   memset(alarm_infostring, 0, 100*sizeof(U32));
   strcpy(g_parameter.function_string, "process_sigtran_stack_alarm()");
   
  /*print alarm parms*/
  SCM_DUMP(0, nbytes, msg_buff, 15);

   if(entity == APP_ID_SIGTRAN)
      {
/*      SCM_printf(SCM_MAJOR,"ALARM RECEIVED FROM SIGTRAN\n");*/ /*ALARM_IMPL*/
      }
   else
       SCM_printf(SCM_MAJOR,"ALARM RECEIVED UNKNOWN ENTITY#@#@#@#@\n");
 
       
   SCM_printf(SCM_INFO,"|||||||||||||||||||||||||||||||||||||||||\n");
   SCM_printf(SCM_INFO,"ALARM PARAMETERS :                       \n");

   switch (entity)
   {
         case APP_ID_ISUP:
              entity_alarm = 3;
              break;
         case APP_ID_MAP:
              entity_alarm = msg_buff[5];
              break;
         /*AOIP ALARM*/
         case APP_ID_SIGTRAN:
              entity_alarm = SIGTRAN;
         /*AOIP end*/
   }
   switch (entity_alarm)
   {
           case SIGTRAN: 
                   alarm_id =((msg_buff[7] << 8) & 0x0000ff00) | msg_buff[6];
                   alarm_level = msg_buff[8];
                   /*AOIP ALARM*/
                   SCM_printf(SCM_MAJOR,"SIGTRAN -> SCM 'Alarm received' 'Alarm Id : %d, Alarm Lvl: %d Noe: %d'\n",
                              alarm_id, alarm_level, msg_buff[2]);
                   SCM_printf(SCM_INFO,"|||||||||||||||||||||||||||||||||||||||||\n");
                   
                   switch(alarm_id)
                     {
                        case SSA_MSG_RECV_REM_SUBSYSTEM:
                        case SSP_MSG_RECV_REM_SUBSYSTEM:
                             report_entity_id = MODULE_SCCP;
                             No_of_element = 2;                       /*Depends upon no of Key recvd from STACK*/
                             Point_Code = EVAL_32(9, msg_buff);
                             SSN        = msg_buff[13];
                             
                             alarm_infostring[0]= Point_Code;  
                             alarm_infostring[1]= SSN;  
                             found = SS7_TRUE; 
                             
                        break;

                        case SIGTRAN_DATA_PULL_DONE:    /*9000 Always to be Recvd on Standby*/
                             report_entity_id = MODULE_SIGTRAN; 
                             g_parameter.data_pull_up = DONE;

                             No_of_element = 1;                             
                             Slot_Id = EVAL_16( 9, msg_buff);

                             alarm_infostring[0]= Slot_Id;  
                             found = SS7_TRUE; 

                        break;

                        case M3UA_AS_STATE_DOWN:     /*9001*/
                        case M3UA_AS_STATE_INACTIVE:
                        case M3UA_AS_STATE_ACTIVE:
                        case M3UA_ASP_STATE_DOWN:
                        case M3UA_ASP_STATE_INACTIVE:
                        case M3UA_ASP_STATE_ACTIVE:
                        case M3UA_ASP_STATE_DOWN_SENT:
                        case M3UA_ASP_STATE_UP_SENT:
                        case M3UA_ASP_STATE_ACT_SENT:
                        case M3UA_ASP_STATE_INACT_SENT:
                        case M3UA_CONN_DOWN:        /*9011*/
                        case M3UA_CONN_ESTABLISHED:   
 
                             report_entity_id = MODULE_SIGTRAN; 
                             No_of_element = 2;
                             Slot_Id    = EVAL_16( 9, msg_buff);
                             AsOrAsp_Id = EVAL_16(11, msg_buff);
                                    
                             alarm_infostring[0]= Slot_Id;  
                             alarm_infostring[1]= AsOrAsp_Id;  
                             found = SS7_TRUE;
                         
                          /*MANTIS Id:- 0032193*/ 
                             if((alarm_id == M3UA_CONN_DOWN) && (g_parameter.redundant_status == SCM_STANDBY))
                              {
                                  ret_val = Check_Self_Admin_and_Opr_state(&admin_state, &opr_status, &Asp_id);
                                  if(ret_val == 0)
                                   { 
                                      if((admin_state == Unlocked) && (opr_status == Disabled))
                                       {
                                          SCM_printf(SCM_CRITICAL,"M3UA_CONN_DOWN Alarm Resp Marked PENDING\n");
                                          g_parameter.Conn_Down_alarm_Resp_Pending = 1;
                                       }
                                       else
                                       {
                                          SCM_printf(SCM_CRITICAL,"M3UA_CONN_DOWN Alarm Resp Marked 0\n");
                                          g_parameter.Conn_Down_alarm_Resp_Pending = 0;
                                       }
                                    }
                                   else
                                    {
                                        SCM_printf(SCM_CRITICAL,"Error in checking Admin & opr status: %d\n", ret_val);
                                    }
                              }
                             /*MANTIS end*/
                             /*The retry over 9011 conn down alarm has been blocked here
 
                             if(alarm_id == M3UA_CONN_DOWN) //M3UA conn DOWN
                              { 
                                if((timer_info[TIMER_SIGTRAN].timer_strt_flag == ON) &&
                                  (timer_info[TIMER_SIGTRAN].opcode == OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG))
                                  {
                                    //Admin Lock Command is Triggered from OMC but before adminstate resp 
                                     // 9011(conn Down) is recvd  -- Discard Conn down processing at SCM
                                     SCM_printf(SCM_MAJOR,"Discard 9011 Processing as AdminState Alrdy Sent to Stack\n");
                                     break;
                                  }

                                 if((g_parameter.redundant_status ==  SCM_STANDBY && g_parameter.data_pull_up == DONE) ||
                                    (g_parameter.redundant_status ==  SCM_ACTIVE))
                                  {
                                     length = sizeof(OamScmM3uaLocalAspAdminConfig);
                                     OamScmM3uaLocalAspAdminConfig ScmM3uaLAspAdminCfg;

                                     state = Check_Self_psp_and_Bss_state(&no_of_asp, asp_id, asp_state);
			             if((state == 1) && (no_of_asp == 1 || no_of_asp == 2))
			              {
			                // SCM_printf(SCM_INFO,"Self Asp was UP...\n");
			                 for(lv=0; lv < no_of_asp; lv++)
			                  {
				           //  SCM_printf(SCM_INFO,"SCM -> SELF SIGTRAN(slf gen) ADMINSTATE Asp_id[%d] Adminstate[%d]\n", 
                                           //  asp_id[lv], asp_state[lv]);
 
                                             ScmM3uaLAspAdminCfg.localAspId = asp_id[lv];
                                             ScmM3uaLAspAdminCfg.adminState = asp_state[lv];  //should be 1
                                             cmd_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                                             memcpy(cmd_buff, &ScmM3uaLAspAdminCfg, length);

                                             form_oam_header( cmd_buff, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG, SCM_MODIFY, 0, 0,length);
                                             tr_opcode = OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG - BASE_OPCODE_SCM_AOIP;
                                             g_parameter.noOam_resp_flag = 1;
                                             ret_val =  process_maptcap_stack_cmd(cmd_buff);

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
				                g_parameter.noOam_resp_flag = 1;
				              }
			                   }
			              }
			             else
			              {
			                  SCM_printf(SCM_INFO,"SELF ASP was DOWN... Proceed\n");
			              }

                                  }
                                 else
                                    SCM_printf(SCM_MAJOR,"PULL UP IND NOT RECVD ...SKIP PROCESSING 9011 AT SCM...\n")

                              }
                          */
                        break;
                        
                        default:
                        SCM_printf(SCM_MAJOR,"ALARM_ID UNKNOWN@@@@@@@'\n");
                        break;
                     }
                   
                   /*AOIP End*/ 
                   break;
 
           case MAP: /* MAP */
                   report_entity_id = MODULE_MAP;
                   alarm_id = msg_buff[6];
                   alarm_id = alarm_id | ((msg_buff[7] << 8)  & 0x0000ff00);
                   alarm_id = alarm_id | ((msg_buff[8] << 16) & 0x00ff0000);
                   alarm_id = alarm_id | ((msg_buff[9] << 24) & 0xff000000);
                   alarm_level = msg_buff[10];
                   SCM_printf(SCM_MAJOR,"\n MAP -> SCM 'Alarm received' 'Alarm Id : %d, Alarm Lvl: %d'",
                              alarm_id, alarm_level); 
                   alarm_infostring[0] = '\0';
                   break;

           case 3: /* ISUP */
                   report_entity_id = MODULE_ISUP;
                   alarm_id =((msg_buff[7] << 8) & 0x0000ff00) | msg_buff[6];
                   alarm_level = msg_buff[8];
                   SCM_printf(SCM_MAJOR,"\n ISUP -> SCM 'Alarm received' 'Alarm Id : %d, Alarm Lvl: %d'",
                              alarm_id, alarm_level); 
                               


                   isup_alarm_opc             = EVAL_32(9, msg_buff);
                   isup_alarm_dpc             = EVAL_32(13,msg_buff);
                   isup_alarm_cic             = EVAL_16(17,msg_buff);
                   isup_cpc_state             = msg_buff[19];

                   SCM_printf(SCM_INFO,"  OPC : %d\n", isup_alarm_opc);
                   SCM_printf(SCM_INFO,"  DPC : %d\n", isup_alarm_dpc);
                   SCM_printf(SCM_INFO,"  CIC : %d\n", isup_alarm_cic);
                   SCM_printf(SCM_INFO,"  CPC STATE : %d\n", isup_cpc_state);
                   
                   if((alarm_id == 2206)||(alarm_id == 2207))
                     {
                      alarm_infostring[0]= isup_alarm_dpc;  
                      No_of_element = 1;  
                     }  
                   else 
                     if(alarm_id == 2200)
                      {
                       No_of_element = 4; 
                       alarm_infostring[0]= isup_alarm_opc;  
                       alarm_infostring[1]= isup_alarm_dpc;  
                       alarm_infostring[2]= isup_alarm_cic;  
                       alarm_infostring[3]= isup_cpc_state;  
                      }
                     else
                       {
                        No_of_element = 3; 
                        alarm_infostring[0]= isup_alarm_opc;  
                        alarm_infostring[1]= isup_alarm_dpc;  
                        alarm_infostring[2]= isup_alarm_cic;  
                       }
                
                   break;
   }

/*  
#define CHECK_IF_ALARM_VALID(A,B,C)     \
          switch(A)                  \
          {                           \
          case MODULE_TCAP:       \
          case MODULE_MAP:       \
               switch(C) \
               {                      \
                case TCAP:            \
                     if( (alarm_id >= TCAP_ALRM_RNG1 &&  alarm_id <= TCAP_ALRM_RNG2) || \
                         (alarm_id >= TCAP_ALRM_RNG3 &&  alarm_id <= TCAP_ALRM_RNG4))  \
                         found = SS7_TRUE;                                            \
                case MAP :                                                             \
                     if( (alarm_id >= MAP_ALRM_RNG2  &&  alarm_id <= MAP_ALRM_RNG3) || \
                         (alarm_id == MAP_ALRM_RNG1 ||  alarm_id == MAP_ALRM_RNG4) || \
                         (alarm_id >= MAP_ALRM_RNG7 &&  alarm_id <= MAP_ALRM_RNG8)||  \
                         (alarm_id == MAP_ALRM_RNG5 ||  alarm_id == MAP_ALRM_RNG6)||  \
                         (alarm_id == MAP_ALRM_RNG9 ||  alarm_id == MAP_ALRM_RNG10)||  \
                         (alarm_id == MAP_ALRM_RNG11 ||  alarm_id == MAP_ALRM_RNG12)||  \
                         (alarm_id == MAP_ALRM_RNG13 ||  alarm_id == MAP_ALRM_RNG14))  \
                         found = SS7_TRUE;                                         \
                     break;                                                            \
               }                                                                       \
                break;             \
          case MODULE_ISUP:       \
              if((alarm_id >= ISUP_ALRM_RNG2 &&  alarm_id <= ISUP_ALRM_RNG3)|| \
                  (alarm_id == ISUP_ALRM_RNG1 || alarm_id == ISUP_ALRM_RNG4 || alarm_id == ISUP_ALRM_RNG5 ))        \
                  found = SS7_TRUE;\
                  break;            \
          }   
      
      CHECK_IF_ALARM_VALID(report_entity_id,alarm_id,entity_alarm);*/ /*AOIP ALARM COMMENT RANGE CHECK*/
        
       
     if(found == SS7_TRUE)
      {  
       /* mapping for oam alarm Id */
        switch(alarm_level)
        {
          case 0:
            alarm_level = ALRM_LVL_INFO;
            break;
          case 1:
            alarm_level = ALRM_LVL_CRIT;
            break;
        
          case 2:
           alarm_level = ALRM_LVL_MAJR;
           break;
         case 3:
           alarm_level = ALRM_LVL_MINR;
           break;
        }   
       report_alarm_to_oam ( alarm_id, alarm_level, report_entity_id );
      }
     else
      {        
       SCM_printf(SCM_MAJOR,"\tAlarm Id is unknown to SCM\n");
      }
/*  #undef CHECK_IF_ALARM_VALID*/
     return;
}



/******************************************************************************
* Name:                                                                       *
* U16 Check_Self_psp_and_Bss_state(U16 *, U16 *, U16 *)                       *
*                                                                             *
* Description:                                                                *
* 1) -This function on basis of Slot id finds Self Asp id & Asp ADMIN STATE & * 
*     is copied to Arguments.                                                *   
*    -After this it Finds the adminstate of BSS & Returns same to caller.     *
*                                                                             *
*******************************************************************************/

U16 Check_Self_psp_and_Bss_state(U16 *no_asp, U16 *asp_id, U16 *asp_state) 
{
    U16 Unlocked = 1;
    U16 Locked   = 0;
    U16 lv =0, ret_val =0, index=0;
    U8 row_count=0;
    SigtranM3uaLAspConfigTableApi *M3uaLocAspConfigPtr=NULL;
   /*FOR Bss table*/
    void    *DbPtr=NULL;
    I_U32    bss_rows=0;
    I_U16    bss_size=0;
    I_S32    dbSts;
    BssTableApi *BssTblPtr = NULL;
   /*end*/
    SCM_printf(SCM_MAJOR,"Check SELF card ASP_ADMIN_STATE & ASP_ID :: self_slot[%d] \n", g_parameter.slot_id);
    ret_val = GetLocalAspAdminStatePtr(&M3uaLocAspConfigPtr, &row_count);   /*comment */
    if( ret_val == 0 && (row_count==1 || row_count == 2))
     {
         for(lv=0; lv<row_count; lv++)
          {
             switch(g_parameter.slot_id)
               {

                  case SLOT_3:
                       SCM_printf(SCM_INFO,"[Row %d].localAspId[%d] admin[%d] Slotid[%d] \n", lv, M3uaLocAspConfigPtr[lv].localAspId,
                       M3uaLocAspConfigPtr[lv].adminState, M3uaLocAspConfigPtr[lv].slotId);
                       if(M3uaLocAspConfigPtr[lv].slotId == (3 - 2))     /*BPM Slotid 3 is mapped to Sigtran Slot Id 1*/
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
                       SCM_printf(SCM_INFO,"[Row %d].localAspId[%d] admin[%d] Slotid[%d] \n", lv, M3uaLocAspConfigPtr[lv].localAspId,
                            M3uaLocAspConfigPtr[lv].adminState, M3uaLocAspConfigPtr[lv].slotId);
                       if(M3uaLocAspConfigPtr[lv].slotId == (4 - 2))    /*BPM Slotid 4 is mapped to Sigtran Slot Id 2*/
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
        SCM_printf(SCM_MAJOR,"SELF Asp's Count %d Check Bss Admin State \n", *no_asp);
        dbSts = getallBssTable((I_PVoid *)&DbPtr, (I_U32 *)&bss_rows, (I_U16 *)&bss_size);
        SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, bss_rows, bss_size);
        if(dbSts == DB_SUCCESS)
         {
           /* SCM_DUMP(0, (bss_rows*sizeof(BssTableApi)), (unsigned char* )DbPtr, 15); no dump req*/
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

     return Locked;
}

const char *get_alarm_string(U16 alarm_id)
{
 switch(alarm_id)
  {    
       case SS7_UP:
            return "SS7_UP";

       case SS7_DOWN:
            return "SS7_DOWN";

       case SSA_MSG_RECV_REM_SUBSYSTEM:
            return "SSA";

       case SSP_MSG_RECV_REM_SUBSYSTEM:
            return "SSP";

       case SIGTRAN_DATA_PULL_DONE:
            return "DATA_PULL_DONE";

       case M3UA_AS_STATE_DOWN:     /*9001*/
            return "M3UA_AS_STATE_DOWN";

       case M3UA_AS_STATE_INACTIVE:
            return "M3UA_AS_STATE_INACTIVE";

       case M3UA_AS_STATE_ACTIVE:
            return "M3UA_AS_STATE_ACTIVE";

       case M3UA_ASP_STATE_DOWN:
            return "M3UA_ASP_STATE_DOWN";
      
      case  M3UA_ASP_STATE_INACTIVE:
            return "M3UA_ASP_STATE_INACTIVE";
      
      case  M3UA_ASP_STATE_ACTIVE:
            return "M3UA_ASP_STATE_ACTIVE";
      
      case  M3UA_ASP_STATE_DOWN_SENT:
            return "M3UA_ASP_STATE_DOWN_SENT";
      
      case  M3UA_ASP_STATE_UP_SENT:
            return "M3UA_ASP_STATE_UP_SENT";
      
      case  M3UA_ASP_STATE_ACT_SENT:
            return "M3UA_ASP_STATE_ACT_SENT";
      
      case  M3UA_ASP_STATE_INACT_SENT:
            return "M3UA_ASP_STATE_INACT_SENT";
      
      case  M3UA_CONN_DOWN:        /*9011*/
            return "M3UA_CONN_DOWN";
      
      case M3UA_CONN_ESTABLISHED:
           return "M3UA_CONN_ESTABLISHED";
  
      default:
           return "UNKNOWN_ALARM*#*#*#\n";
   
  }
}


/*MANTIS Id :- 0032193*/
U16 Check_Self_Admin_and_Opr_state(U16 *admin_state, U16 *opr_status, U16 *Asp_id)
{
    U16 Self_Slot;
    U16 lv =0, ret_val =0, index=0;
    U8 row_count=0;
    SigtranM3uaLAspConfigTableApi *M3uaLocAspConfigPtr=NULL; 
    Self_Slot = g_parameter.slot_id; 

   SCM_printf(SCM_MAJOR,"CHECK SELF card ASP_ADMIN_STATE & OPR_STATUS :: self_slot[%d] \n", g_parameter.slot_id);
    ret_val = GetLocalAspAdminStatePtr(&M3uaLocAspConfigPtr, &row_count); 
    if( ret_val == 0 && (row_count==1 || row_count == 2))
     {
         for(lv=0; lv<row_count; lv++)
          {
             switch(Self_Slot)
               {

                  case SLOT_3:
                       SCM_printf(SCM_INFO,"[Row %d].localAspId[%d] admin[%d] Slotid[%d] opr_status[%d] \n", lv, M3uaLocAspConfigPtr[lv].localAspId,
                       M3uaLocAspConfigPtr[lv].adminState, M3uaLocAspConfigPtr[lv].slotId, M3uaLocAspConfigPtr[lv].operationalStatus);
                       if(M3uaLocAspConfigPtr[lv].slotId == (3 - 2))     /*BPM Slotid 3 is mapped to Sigtran Slot Id 1*/
                        {
                           *admin_state = M3uaLocAspConfigPtr[lv].adminState;
                           *opr_status  = M3uaLocAspConfigPtr[lv].operationalStatus;
                           *Asp_id      = M3uaLocAspConfigPtr[lv].localAspId; 
                        }

                  break;
                  case SLOT_4:
                       SCM_printf(SCM_INFO,"[Row %d].localAspId[%d] admin[%d] Slotid[%d] opr_status[%d] \n", lv, M3uaLocAspConfigPtr[lv].localAspId,
                            M3uaLocAspConfigPtr[lv].adminState, M3uaLocAspConfigPtr[lv].slotId, M3uaLocAspConfigPtr[lv].operationalStatus);
                       if(M3uaLocAspConfigPtr[lv].slotId == (4 - 2))    /*BPM Slotid 4 is mapped to Sigtran Slot Id 2*/
                        {
                           *admin_state = M3uaLocAspConfigPtr[lv].adminState;
                           *opr_status   = M3uaLocAspConfigPtr[lv].operationalStatus;
                           *Asp_id      = M3uaLocAspConfigPtr[lv].localAspId; 
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

return 0;
}
/*MANTIS End*/
