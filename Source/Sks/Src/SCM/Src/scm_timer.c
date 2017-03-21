#include "scm_localhashdef.h"
#include <scm_encaps.h>

//#include <scm_oamint_error_code.h>


/* sigaction struct init*/
/*struct sigaction sig_action =
       {
       (void*)sig_act();
       SS7_NULL;
       0;
       0;
       SS7_NULL;     
       }; */
/*end*/

extern U8 tmr_nxt_cmd_flg;
/*timer value set*/
struct sigaction sig_action;
struct itimerspec timer_value, get_value;
struct timespec current_time;

/*function starts the timer*/ 
int start_timer (U8 timer_Id, U8 api_Id, I_U32  tr_Id, U8 *msg_buff)
 {
   U8 no_of_resp, operation;
   S16 status;
   struct sigevent evp = {0, SIGALRM}; 
   int clock_id = CLOCK_REALTIME;
   U16 opcode;
   ScmHdr *scmhdr=NULL;
   if(msg_buff != NULL)
   {
    scmhdr = (ScmHdr*)msg_buff;
    opcode = scmhdr->opcode;
    operation = scmhdr->operation;
   }
   strcpy(g_parameter.function_string, "start_timer()");
 if((timer_info[timer_Id].timer_strt_flag == 1))
   {
    SCM_printf (SCM_INFO, "\nTIMER ALLREADY IN RUNNING CONDITION = %d\n", timer_Id);
    return 0; 
   }
 if(timer_create (clock_id, &evp, &os_timer_id[timer_Id]) != 0)
  {
   SCM_printf (SCM_CRITICAL, "\nCOULDN'T CREATE TIMER ID %d\n", timer_Id);
   return 0;
  }
 else
  {
   timer_info[timer_Id].api_Id           = api_Id;
   timer_info[timer_Id].opcode           = opcode;
   timer_info[timer_Id].operation        = operation;
   timer_info[timer_Id].tr_Id            = tr_Id;
   timer_info[timer_Id].timer_strt_flag  = 1;
   if(g_parameter.config_flag == 1)
     timer_info[timer_Id].db_oam_stamp     =  DB_STAMP;
   else 
     timer_info[timer_Id].db_oam_stamp     =  OAM_STAMP;

   get_no_of_resp_required(&no_of_resp, opcode);
   timer_info[timer_Id].no_of_resp       = no_of_resp;
   timer_info[timer_Id].no_of_resp_flag  = 0;
   timer_info[timer_Id].resp_flag        = SS7_TRUE;
   timer_info[TIMER_MULTICMD].resp_error_id = 0;
   clock_gettime ( CLOCK_REALTIME, &current_time );
   timer_value.it_interval.tv_sec =0;
   timer_value.it_interval.tv_nsec= 0;
   if ((timer_Id == TIMER_MULTICMD))
    { 
      timer_value.it_value.tv_sec    = TIMER_VAL +2+ current_time.tv_sec;
    }
   else
    {
     timer_value.it_value.tv_sec    = TIMER_VAL + current_time.tv_sec;
     if( timer_Id == TIMER_NWSTK_CONFIG )
     {timer_value.it_value.tv_sec    = 60 +  current_time.tv_sec;} /* explicitly done for check after 8 sec*/
    }
   timer_value.it_value.tv_nsec   = 0 + current_time.tv_nsec; 
   sig_action.sa_handler = (void*)sig_act;
   sigemptyset(&sig_action.sa_mask);
   sigaction(SIGALRM, &sig_action, SS7_NULL);
   status = timer_settime(os_timer_id[timer_Id], TIMER_ABSTIME,&timer_value,NULL);
   if(status == -1)
    {
     SCM_printf (SCM_CRITICAL, "\nCOULDN'T START TIMER ID %d\n", timer_Id); 
     return 0;
    }
   SCM_printf (SCM_INFO, "Successfully started timer Id %d\n", timer_Id);
   timer_info[timer_Id].timer_strt_flag = 1; 
  }
 return 1;
}
/*end here*/

/*stop the timer started before */
int stop_timer (U8 timer_Id)
{
    S16 status; 
    strcpy(g_parameter.function_string, "stop_timer()");
    switch(timer_Id)
     {
      case TIMER_SIGTRAN:
           if((g_parameter.peer_map_tcap_cmdFlag == 1) && (timer_info[TIMER_SIGTRAN].resp_error_id == 0))
            {
              SCM_printf (SCM_CRITICAL, "\nself card stack responded: waiting for peer card stack response");
             /* modify timer response flag for peer card response */
             timer_info[timer_Id].resp_from_peer_cardFlag = 1;
             return 1;
            }
           break;
      case TIMER_LAPD:
           if((g_parameter.peer_lapd_cmdFlag == 1) && (timer_info[TIMER_NWSTK].resp_error_id == 0))
            {
              SCM_printf (SCM_CRITICAL, "\nself card stack responded: waiting for peer card stack response");
              /* modify timer response flag for peer card response */
              timer_info[timer_Id].resp_from_peer_cardFlag = 1;
              return 1;
            }
           break;
      case TIMER_NWSTK:
           if((g_parameter.peer_nwstk_cmdFlag == 1) && (timer_info[TIMER_NWSTK].resp_error_id == 0))
            {
             SCM_printf (SCM_CRITICAL, "\nself card stack responded: waiting for peer card stack response");
             /* modify timer response flag for peer card response */
             timer_info[timer_Id].resp_from_peer_cardFlag = 1;
             return 1;
            }
           break; 
      case TIMER_MULTICMD:
           if((g_parameter.peer_multi_cmdFlag == 1) && (timer_info[TIMER_MULTICMD].resp_error_id == 0))
            {
             SCM_printf (SCM_CRITICAL, "\nself card stack responded: waiting for peer card stack response");
             /* modify timer response flag for peer card response */
             timer_info[timer_Id].resp_from_peer_cardFlag = 1;
             return 1;
            }
           break; 

 
     }
    if(timer_info[timer_Id].timer_strt_flag == 1)
     {
      timer_info[timer_Id].timer_strt_flag = 0; 
      status = timer_delete(os_timer_id[timer_Id]);
      if(status == -1)
       {
        SCM_printf (SCM_CRITICAL, "\nCAN NOT STOP TIMERID : %d\n", timer_Id);
       }
        SCM_printf (SCM_INFO, "Stop timerId : %d\n", timer_Id);
     }     
   return 1;
}
/*end here */

/*function takes action on timer expiry*/
void sig_act()
{
    msgbuf queuebuf;
    timer_t time;
    U8 exp;
    U16 temp, entity; 
    strcpy(g_parameter.function_string, "sig_act()");
    SCM_printf (SCM_CRITICAL, "\nTIMER EXPIRED NO RESPONSE FROM STACK");
     /*if((get_value.it_value.tv_sec==0)&&(get_value.it_value.tv_nsec==0))*/
    #define IS_TIMER_EXP(A,C)        \
     time = A;                      \
     timer_gettime (os_timer_id[A], &get_value);\
     SCM_printf (SCM_INFO, "\n value of get_value.it_interval.tv_sec = %d ", get_value.it_interval.tv_sec);\
     SCM_printf (SCM_INFO, "\n value of get_value.it_interval.tv_nsec = %d ", get_value.it_interval.tv_nsec);\
     SCM_printf (SCM_INFO, "\n value of get_value.it_value.tv_sec = %d ", get_value.it_value.tv_sec);\
     SCM_printf (SCM_INFO, "\n value of get_value.it_value.tv_nsec = %d ", get_value.it_value.tv_nsec);\
     if(get_value.it_value.tv_sec<=0)\
        C = SS7_TRUE;\
     else \
        C = SS7_FALSE;  
    for(temp = 0; temp<=7; temp++)
     {
      if(timer_info[temp].timer_strt_flag == 1)
       {
        SCM_printf (SCM_CRITICAL, "\n TIMER ID %d", temp);
        IS_TIMER_EXP(temp, exp);
       if(exp == SS7_TRUE)
        {
         entity = temp;
         timer_info[entity].entity = temp; 
         break;
        }

       }
     }
    exp  = temp;
    switch(entity)
      {
        case TIMER_NWSTK:
             g_parameter.peer_nwstk_cmdFlag = 0;
             g_parameter.peer_multi_cmdFlag = 0;
             SCM_printf (SCM_CRITICAL, "\nTIMER EXPIRED NWSTK");
             break;
        case TIMER_NWSTK_CONFIG:
             { 
              SCM_printf (SCM_CRITICAL, "\nTIMER EXPIRED WAITING FOR LAPD CONFIG");
              if( g_parameter.no_of_retry_nwstk_cfg_wait == 5)
              {
                SCM_printf (SCM_CRITICAL, "\nCheck lapd port in isil_conf & scm_conf !!");
              }    
              g_parameter.no_of_retry_nwstk_cfg_wait++;
              stop_timer( TIMER_NWSTK_CONFIG);
              start_timer ( TIMER_NWSTK_CONFIG, APP_ID_NWSTK, 0, NULL);
              return;
             }
             break;
        case TIMER_SIGTRAN:
             SCM_printf (SCM_CRITICAL, "\nTIMER EXPIRED SIGTRAN"); /*AOIP: PRINT UPDATED*/
             timer_info[TIMER_SIGTRAN].timer_strt_flag = 0;
            /* changing flag update location after reading timer expirt queue 
             g_parameter.peer_map_tcap_cmdFlag = 0;*/
             timer_delete(os_timer_id[TIMER_SIGTRAN]);
             break;
        case TIMER_LAPD:  
             g_parameter.peer_lapd_cmdFlag = 0;
             SCM_printf (SCM_DEBUG, "\nTIMER EXPIRED LAPD");
             break;
        case TIMER_MULTICMD:
             g_parameter.peer_nwstk_cmdFlag = 0;
             g_parameter.peer_multi_cmdFlag = 0;
             SCM_printf (SCM_CRITICAL, "\nTIMER EXPIRED MULTI CMD");
             break;
        /*AOIP: BSSAP TIMER*/
        case TIMER_BSSAP:
             SCM_printf (SCM_DEBUG, "\nTIMER EXPIRED BSSAP");
             timer_info[TIMER_BSSAP].timer_strt_flag = 0;
             Reconf_Flag = SS7_FALSE;    /*AOIP ADD*/
             timer_delete(os_timer_id[TIMER_BSSAP]);
             break;
        /*AOIP: END*/
        default:
             SCM_printf (SCM_CRITICAL, "\nTIMER EXPIRED UNKNOWN ");
             return;
      }


   queuebuf.mtype = 1; 
   memcpy(&queuebuf.mtext[0], &timer_info[entity], sizeof(timer_exp_ele));
    
   stop_timer (entity);
 if(( msgsnd (g_parameter.timer_event_q_Id, (msgbuf *)&queuebuf, sizeof(msgbuf)-4 , 0 )) == -1)
   {
    SCM_printf (SCM_CRITICAL, "\nMSG SEND TO QUEUE IS FAILURE");
   } 
    return;   
 #undef IS_TIMER_EXP        
}
/*end*/

/*process scm timer expiry */
void process_timer_exp_queue()
{
 U16  opcode, resp_opcode, tr_opcode, multicmd_flag = 0, timer_id, resp_len, pegrfu;
 U8 api_Id, tr_Id, db_oam_stamp, operation, oam_tr_Id, *msg_buff=NULL, entity;
 resp_len = sizeof(ScmOamResponse);
 
 //timer_exp_ele *((timer_exp_ele*)queuebuf.mtext);
 msgbuf queuebuf;
 strcpy(g_parameter.function_string, "process_timer_exp_queue()");
 while(1)
    {
       /* check timer exiry queue */ 
     if( msgrcv( g_parameter.timer_event_q_Id, (msgbuf *)&queuebuf, 
         sizeof(msgbuf)-4, 0, IPC_NOWAIT) == -1)
      {
      // SCM_printf (SCM_INFO, "\nTIMER EXPIRY QUEUE EMPTY");
       return ;
      }
     else
      {
       SCM_printf (SCM_INFO, "\nPROCESSING MESSAGE FROM TIMER EXPIRY QUEUE ");
       //((timer_exp_ele*)queuebuf.mtext) = scm_malloc(sizeof(timer_exp_ele));
       //((timer_exp_ele*)queuebuf.mtext) = (timer_exp_ele*)&queuebuf.mtext[0];
       api_Id = ((timer_exp_ele*)queuebuf.mtext)->api_Id;
       tr_Id  = ((timer_exp_ele*)queuebuf.mtext)->tr_Id;
       opcode = ((timer_exp_ele*)queuebuf.mtext)->opcode;
       SCM_printf (SCM_CRITICAL, "DEBUG app_id[%d] tr_Id[%d] opcode[%d]\n", ((timer_exp_ele*)queuebuf.mtext)->api_Id, ((timer_exp_ele*)queuebuf.mtext)->tr_Id,  ((timer_exp_ele*)queuebuf.mtext)->opcode);
       if((opcode == OAM_SCM_LINK_CONFIG))
       {
        g_parameter.peer_link_del = 0; 
       } 
       entity = ((timer_exp_ele*)queuebuf.mtext)->entity;
       /*tr_opcode = opcode - BASE_OPCODE_SCM;*/
       tr_opcode = opcode - BASE_OPCODE_SCM_AOIP;
       db_oam_stamp = ((timer_exp_ele*)queuebuf.mtext)->db_oam_stamp;
       match_resp_opcode(opcode, &resp_opcode); 
       check_peer_cmd_flag_and_roll_back( api_Id);
       // timer_info[entity].timer_strt_flag = 0; /* fix for timer start flag corruption */
       g_parameter.config_cmd_resp = 0;
       timer_info[entity].resp_flag = 0;
 
       /* check command type is multiple or single n do rollback if required */
       if((opcode == OAM_SCM_SS7_STACK_CONFIG) || (opcode == OAM_SCM_ALARM_MODIFY))
          {
           if(opcode == OAM_SCM_SS7_STACK_CONFIG)
             {
              multi_cmd[0].resp_flag = 0;/* to discard the pending responses*/
              multicmd_flag = 1;
             } 
           else
            if(opcode == OAM_SCM_ALARM_MODIFY )
             {
               multi_cmd[1].resp_flag = 0;
               multicmd_flag = 0;/*i will implement it later if rollback for alarm cmd is req.*/
             }
            else
             {
               SCM_printf(SCM_CRITICAL, "\nSCM LOGICAL ERROR");
               return ; 
             } 
          if(db_oam_stamp == DB_STAMP)
            {
            timer_info[TIMER_MULTICMD].resp_flag = 0;
            continue;
            }
          else
           {
            oam_tr_Id =  oam_transaction_Id[tr_opcode].transaction_Id;
            operation =  oam_transaction_Id[tr_opcode].operation;
            pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
            if(g_parameter.config_flag == 0)
            {  
             send_resp_to_oam(resp_opcode, operation,oam_tr_Id , pegrfu, 
                             ERROR_SCM_TIMER_EXPIRED, NULL, resp_len, APP_ID_OAM);
            }
            if((multicmd_flag == 1) && (db_oam_stamp != DB_STAMP) && multi_cmd[0].stored_msg!= NULL )
             {
              msg_buff = multi_cmd[0].stored_msg;/*get stored message */   
              if(((ScmHdr*)msg_buff)->operation == SCM_ADD)
              {
               ((ScmHdr*)msg_buff)->operation = SCM_DELETE; 
               g_roll_back_flag.multi_cmd_roll_back_flag = 1;
               process_roll_back(msg_buff);
               g_roll_back_flag.multi_cmd_roll_back_flag = 0;
              }
             }
            continue; 
           }
        }
       /* single command response timer expiry */
      switch (api_Id)
          {
           case APP_ID_NWSTK:
                timer_info[TIMER_NWSTK].resp_flag =0;
                timer_id = TIMER_NWSTK;
                break;
           case APP_ID_LAPD:
                timer_info[TIMER_LAPD].resp_flag =0;
                timer_id = TIMER_LAPD;
                break;
          /*AOIP: case added*/
           case APP_ID_BS:
                timer_info[TIMER_BSSAP].resp_flag =0;
                timer_id = TIMER_BSSAP;
                break;
           case APP_ID_SIGTRAN:
                timer_info[TIMER_SIGTRAN].resp_flag =0;
                timer_id = TIMER_SIGTRAN;
                break;
          /*AOIP: end*/
          }
       if((g_parameter.config_flag == SS7_TRUE) ||(timer_info[TIMER_NWSTK].db_oam_stamp == DB_STAMP))
       {
         g_parameter.config_cmd_resp = 0;
         tmr_nxt_cmd_flg = SS7_TRUE;
         return ;
       }
      else
       {
         oam_tr_Id =  oam_transaction_Id[tr_opcode].transaction_Id;
         operation =  oam_transaction_Id[tr_opcode].operation;
         pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
         match_resp_opcode(opcode, &resp_opcode);  
         if(g_parameter.config_flag == 0)
         {    
          send_resp_to_oam(resp_opcode, operation,oam_tr_Id , pegrfu,
                           ERROR_SCM_TIMER_EXPIRED, NULL, resp_len, APP_ID_OAM);
         }
       }

 
     }
    }
   return ; 
}

/************************************************************************/
 /*this function extracts the no. of response required for the command send*/
/***********************************************************************/
int get_no_of_resp_required(U8* no_of_resp, U16 opcode)
{
 strcpy(g_parameter.function_string, "get_no_of_resp_required()");
 switch(opcode)
       {
       case OAM_SCM_LAPDTIMER_CONFIG:
            *no_of_resp = 4 ; 
       case   OAM_SCM_SS7_STACK_CONFIG:
              *no_of_resp = 8;
               break;    
       case   OAM_SCM_ALARM_MODIFY:
              *no_of_resp = 6;
              break; 
      default:
             *no_of_resp =1;
              break;
       }
 return 1;
}

void check_peer_cmd_flag_and_roll_back(U8 app_id)
{
/* #define SET_OPERATION(A)\
        if(A == SCM_ADD)    A = SCM_DELETE;\
        if(A == SCM_DELETE) A = SCM_ADD;*/


#define SET_OPERATION(A)\
        if(A == SCM_ADD) {   A = SCM_DELETE;} else {if(A == SCM_DELETE) A = SCM_ADD;}



 switch(app_id)
  {      
     case APP_ID_MAP:
     case APP_ID_SIGTRAN:
           if(g_parameter.peer_map_tcap_cmdFlag == 1)
            {
             SCM_printf(SCM_CRITICAL, "NO RESPONSE FROM PEER SCM TIMER EXPIRED\n");
             g_parameter.peer_map_tcap_cmdFlag = 0;
             stop_timer(TIMER_SIGTRAN);
             if(g_parameter.map_tcap_msg != NULL)
              {
               g_roll_back_flag.maptcap_roll_back_flag = 1;
               SET_OPERATION(((ScmHdr*)g_parameter.map_tcap_msg)->operation);/*bug fixed*/
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
               /*AOIP end*/
               free(g_parameter.map_tcap_msg) ;
               g_parameter.map_tcap_msg = NULL;
              }
            }
           break;
     case APP_ID_NWSTK:
          if(g_parameter.peer_nwstk_cmdFlag == 1)
            {
             SCM_printf(SCM_CRITICAL, "\nNO RESPONSE FROM PEER SCM TIMER EXPIRED");
             g_parameter.peer_nwstk_cmdFlag = 0;
             stop_timer(TIMER_NWSTK);
             if(g_parameter.nwstk_msg != NULL)
              {
               g_roll_back_flag.nwstk_roll_back_flag = 1;
               SET_OPERATION(((ScmHdr*)g_parameter.nwstk_msg)->operation); 
               //((ScmHdr*)g_parameter.nwstk_msg)->operation = SCM_DELETE;
               process_oam_message(g_parameter.nwstk_msg);
               free(g_parameter.nwstk_msg) ;
               g_parameter.nwstk_msg = NULL;
              }
            }
           break;

    }
#undef SET_OPERATION
 return ; 
}  

