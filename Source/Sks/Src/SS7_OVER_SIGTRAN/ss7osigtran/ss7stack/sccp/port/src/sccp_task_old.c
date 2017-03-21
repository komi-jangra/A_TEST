/*
 * SCCP module main file
 *
 * Copyright 2000, Hughes Software Systems, Ltd.
 */
#include <time.h>
#include <stdlib.h>
#include <sl.h>
#include <s7_typ.h>
#include <s7_api.h>
#include <s7_def.h>
#include <s7_error.h>
#include <sc_stgl.h>
#include <sccp_port.h>

#ifdef MTP3
#include <m3_glob.h>
#include <common_db.h>
#include <common_syn.h>
#endif

#include "ss7oversigtran.h"

#ifdef MTP3
unsigned int sccp_self_pc;
#endif

#define SCCP_USER_MSG_MAX_SIZE 1024

static int sccp_user_sock[2];
static const int yes = 1;
unsigned char sccp_user_sock_recv(int fd);

t_sp_data sccp_sp_data_list[MAX_SP_DATA_LIST];
t_gt_entry gsn_gtt_table[SS7_OVER_SIGTRAN_SCCP_NUM_GT_ENTRY];
t_gt_list gsn_gtt_list[MAX_GTT_LIST];


extern sl_module_t ss7_tcap_mid;
extern t_sp_data sccp_sp_data_list[];
extern unsigned long scf_p_context;
extern return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
                              src_id_t src_id, dst_id_t dst_id,
                              error_t *p_ecode);

extern void gsn_nm_config_sccp_var (int type, unsigned long value);
extern struct gsn_configdata_t gsn_configdata;
extern unsigned long scf;
unsigned long int user_ip_address;
extern char *host_ip[32];

unsigned long stack_destinations[5] ;

void sccp_initialization (void *unused);
void ss7_sccp_task (void *unused);
sl_module_t ss7_sccp_mid;

U8bit sccp_register_buf_arr[]={0xa6,0x01,0x02,0x0a,0x00,0x01,0x00,0x07,0x05,0x0};
 gsn_config_db_t C;
return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
                              src_id_t src_id, dst_id_t dst_id,
                              error_t *p_ecode);

void ss7_sccp_timer_handler (QTIMER tid, void *buf, void *context)
{
    sccp_process_mesg (buf);
}

int ss7_sccp_msg_handler (void *buf, void *context)
{
	int arg = qvPriority(buf);
    if (arg == 0)
	sccp_process_mesg (buf);
    else
	sl_buf_free (buf);
    return 0;
}
void ss7_sccp_init (void)
{
   ss7_sccp_mid = sl_module_register ("SCCP", sccp_initialization,
				       ss7_sccp_msg_handler,
				       ss7_sccp_timer_handler, 0);
/* ss7_sccp_mid = sl_module_register ("SCCP", sccp_initialization,
                                       ss7_sccp_msg_handler,
                                       ss7_sccp_timer_handler, stack_destinations);*/

	sccp_init_stats_traffic ();
}
return_t send_from_sccp (buffer_t *p_buffer, s7_len_t noctets,
			 src_id_t src_id, dst_id_t dst_id,
			 error_t *p_ecode)
{
    return ss7_dispatch_buffer (p_buffer, noctets, src_id, dst_id,
				p_ecode); 
}

return_t sccp_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
			       src_id_t src_id, dst_id_t dst_id,
			       error_t *p_ecode)
{
    return ss7_dispatch_buffer (p_buffer, noctets, src_id, dst_id,
				p_ecode);
}

void sccp_read_cfg()
{
   unsigned char input1[10]="19612242";	
   unsigned char input2[10]="19222243";	
   unsigned char output1[10]="91987654";	
   unsigned char output2[10]="91981234";	
   ss7_mem_zero(&C.sccp_params, sizeof(gsn_config_sccp_params_t));
   C.sccp_params.standard = STACK_ITU;

   C.sccp_params.max_sp = 64;
   C.sccp_params.max_ss = 32;
   C.sccp_params.max_css = 16;
   C.sccp_params.max_csp = 16;

/*
   C.sccp_params.max_sp = SCCP_MAX-SP;
   C.sccp_params.max_ss = SCCP_MAX-SS;  
   C.sccp_params.max_css = SCCP_MAX-CSS;
   C.sccp_params.max_csp = SCCP_MAX-CSP;  */
  
   C.sccp_params.t_reass = 10;
   C.sccp_params.t_stat_info = 10;
   C.sccp_params.t_cong_attack = 60;
   C.sccp_params.t_cong_decay = 10;
   C.sccp_params.seg_parm_z = 160;


 
	sccp_sp_data_list[0].sp_id = 4;
        sccp_sp_data_list[0].nw_id = 0;
        sccp_sp_data_list[0].ssf = 0x00;
        sccp_sp_data_list[0].valid = 1;
        sccp_sp_data_list[0].local = 1;
	sccp_sp_data_list[0].pc = 1;	
	sccp_sp_data_list[0].ssn_data[0].valid = 1;
        sccp_sp_data_list[0].ssn_data[0].ss_id = 5;
        sccp_sp_data_list[0].ssn_data[0].ssn = 7;	
/*	sccp_sp_data_list[0].ssn_data[1].valid = 1;
        sccp_sp_data_list[0].ssn_data[1].ss_id = 1;
        sccp_sp_data_list[0].ssn_data[1].ssn = 8;	*/

	
	sccp_sp_data_list[1].sp_id = 2;
        sccp_sp_data_list[1].nw_id = 0;
        sccp_sp_data_list[1].ssf = 0x00;
        sccp_sp_data_list[1].valid = 1;
        sccp_sp_data_list[1].local = 0;
	sccp_sp_data_list[1].pc = 2;	
	sccp_sp_data_list[1].ssn_data[0].valid = 1;
        sccp_sp_data_list[1].ssn_data[0].ss_id = 1;
        sccp_sp_data_list[1].ssn_data[0].ssn = 6;

#if 0
	gsn_gtt_list[0].gt_len = 15;
        snprintf(gsn_gtt_list[0].input,10,"%s", input1);
        /* gsn_gtt_table[0].pattern_o = 91987;   */
         gsn_gtt_list[0].ssn = 7;
        gsn_gtt_list[0].pc = 1;
        gsn_gtt_list[0].rout_ind = 0;

         gsn_gtt_list[1].gt_len = 15;
         snprintf( gsn_gtt_list[1].input,10,"%s", input2);
         /*gsn_gtt_table[1].pattern_o = 91981;   */
         gsn_gtt_list[1].ssn = 6;
         gsn_gtt_list[1].pc = 2;
        gsn_gtt_list[1].rout_ind = 0;

#endif

	gsn_gtt_table[0].valid = 1;
	snprintf( gsn_gtt_table[0].pattern_i,10,"%s", input1);
       /* gsn_gtt_table[0].pattern_o = 91987; 	*/
	gsn_gtt_table[0].ssn = 7;
        gsn_gtt_table[0].pc = 1;
	
	gsn_gtt_table[1].valid = 1;
	snprintf( gsn_gtt_table[1].pattern_i,10,"%s", input2);
        /*gsn_gtt_table[1].pattern_o = 91981; 	*/
	gsn_gtt_table[1].ssn = 6;
        gsn_gtt_table[1].pc = 2;


}
void sccp_config_tmr_var(int type, unsigned long value)
{
    extern sc_opt_t sc_opt;
    switch(type)
    {
    case OM_ELEMENT_SCCP_T_REASS:
		value *= 100;
		SCCP_NM_SET_TIMER_REQ_BUF(T_REASS_CONFIG_ID, value);
		break;
    case OM_ELEMENT_SCCP_T_STAT_INFO:
		value *= 100;
		SCCP_NM_SET_TIMER_REQ_BUF(T_STAT_INFO_START_CONFIG_ID, value);
		break;
    case OM_ELEMENT_SCCP_T_CONG_ATTACK:
		value /= 10; /* This timer is sent in milliseconds from the NM Agent */
		SCCP_NM_SET_TIMER_REQ_BUF(T_A_CONFIG_ID, value);
		break;
    case OM_ELEMENT_SCCP_T_CONG_DECAY:
		value *= 100;
		SCCP_NM_SET_TIMER_REQ_BUF(T_D_CONFIG_ID, value);
		break;
    case OM_ELEMENT_SCCP_SEG_PAR_Z:
		sc_opt.seg_size = value;
		break;
	default:
		printf("Invalid configuration call from GSN Daemon for Unsupported Sccp element type = %d of value %d\n",type, value);
		return;
	}
	printf("Sccp Configuration for type %d and value %d done\n", type , value);
	return;
}
void sccp_initialization (void *unused)
{
    int                 i = 0, j = 0;
    sc_init_opt_t       sccp_init_options;
    error_t             ecode;
    sc_sp_conf_info_t   sp_conf_info;
    sc_ss_conf_info_t   ss_conf_info;
    sc_css_info_t	p_css_info;
    sc_csp_info_t        p_csp_info;
#ifdef MTP3
    mtp3_cinit_opt_t    mtp3_init_opts;
	time_t				seed;

	time (&seed);
	srand ((unsigned int) seed);  //initialize seed for random sls value generation
#endif
     sccp_read_cfg(); 

    sccp_init_options.standard = C.sccp_params.standard;
    sccp_init_options.max_sp = C.sccp_params.max_sp;
    sccp_init_options.max_ss = C.sccp_params.max_ss;
    sccp_init_options.max_css = C.sccp_params.max_css;
    sccp_init_options.max_csp = C.sccp_params.max_csp;	

    if (sccp_init (&sccp_init_options, &ecode) != SS7_SUCCESS)
    {
        printf("SCCP_INIT: SCCP initialization failed.\nError Code: %d\n", ecode);
        exit (1);
    }

    sccp_config_tmr_var(OM_ELEMENT_SCCP_T_REASS, C.sccp_params.t_reass);
    sccp_config_tmr_var(OM_ELEMENT_SCCP_T_STAT_INFO, C.sccp_params.t_stat_info);
    sccp_config_tmr_var(OM_ELEMENT_SCCP_T_CONG_ATTACK, C.sccp_params.t_cong_attack);
    sccp_config_tmr_var(OM_ELEMENT_SCCP_T_CONG_DECAY, C.sccp_params.t_cong_decay);
    sccp_config_tmr_var(OM_ELEMENT_SCCP_SEG_PAR_Z, C.sccp_params.seg_parm_z);

    /* if (ss7_set_trace_level (SCCP_MODULE_ID, ALL_TRACE, DETAILED_TRACE, &ecode) 
!= SS7_SUCCESS)
    {
        logprintf("SCCP_INIT: ERROR: Could not set trace level.\n");
        exit (1);
    } */
        sp_conf_info.sp_id = sccp_sp_data_list[i].sp_id;
        sp_conf_info.nw_id = sccp_sp_data_list[i].nw_id;
        sp_conf_info.local = sccp_sp_data_list[i].local;
        sp_conf_info.pc    = sccp_sp_data_list[i].pc;
        sp_conf_info.ssf   = sccp_sp_data_list[i].ssf;
        if (sccp_prov_add_sp (&sp_conf_info, &ecode) != SS7_SUCCESS)
        {
            printf("SCCP_INIT: Could not add SP [%d], error code [%d]\n", sp_conf_info.sp_id, ecode);
           /* exit (1);*/
        }
	else
	{
          printf("SCCP_INIT: Adding signalling point (SP-ID=[%d])...\n", sccp_sp_data_list[i].sp_id);
          ss_conf_info.ss_id = sccp_sp_data_list[i].ssn_data[j].ss_id;
          ss_conf_info.sp_id = sccp_sp_data_list[i].sp_id;
          ss_conf_info.ssn   = sccp_sp_data_list[i].ssn_data[j].ssn;
          if (sccp_prov_add_ss (&ss_conf_info, &ecode) != SS7_SUCCESS)
          {
             printf("SCCP_INIT:Couldnot add SS for SP-ID [%d],errorcode[%d]\n",sp_conf_info.sp_id, ecode);
            /* exit (1);*/
          }
	  else
	  {
           printf("Add SS for SP-ID [%d],errorcode[%d]\n",sp_conf_info.sp_id, ecode);
		j = 0;
                     p_css_info.ss_id = sccp_sp_data_list[i].ssn_data[j].ss_id;
                    /* taken from gsn_readcfg.c */
                     p_css_info.css_id = 1;
                     /* add concern sub system*/
                     if(sccp_prov_add_css(&p_css_info, &ecode) != SS7_SUCCESS)
                     {
                        printf("SCCP_INIT: Could not add CSS for SS-ID [%d], error code [%d]\n", sccp_sp_data_list[i].ssn_data[j].ss_id, ecode);
	             }
		    else
		    {				 
                        printf("SCCP_INIT: added CSS for SS-ID [%d], error code [%d]\n", sccp_sp_data_list[i].ssn_data[j].ss_id, ecode);
	         	p_csp_info.csp_id = sp_conf_info.sp_id;
                 	p_csp_info.ss_id = sccp_sp_data_list[i].ssn_data[j].ss_id;
                 	if(sccp_prov_add_csp(&p_csp_info, &ecode) != SS7_SUCCESS)
                 	{
                         printf("SCCP_INIT: Could not add CSP for SS-ID [%d], error code [%d]\n",sp_conf_info.sp_id,ecode);
                        /* exit (1); */
                 	}
			else
			{
                         printf("SCCP_INIT: Added CSP for SS-ID [%d], error code [%d]\n", sp_conf_info.sp_id, ecode);
			}
                            /* exit (1);*/
                    }
		}
           	printf("Add SS for SP-ID [%d],errorcode[%d]\n",sp_conf_info.sp_id, ecode);
	        i++;
	 }			
        sp_conf_info.sp_id = sccp_sp_data_list[i].sp_id;
        sp_conf_info.nw_id = sccp_sp_data_list[i].nw_id;
        sp_conf_info.local = sccp_sp_data_list[i].local;
        sp_conf_info.pc    = sccp_sp_data_list[i].pc;
        sp_conf_info.ssf   = sccp_sp_data_list[i].ssf;
        if (sccp_prov_add_sp (&sp_conf_info, &ecode) != SS7_SUCCESS)
        {
            printf("SCCP_INIT: Could not add SP [%d], error code [%d]\n", sp_conf_info.sp_id, ecode);
        /*    exit (1); */
        }
	else
	{
          printf("SCCP_INIT: Adding signalling point (SP-ID=[%d])...\n", sccp_sp_data_list[i].sp_id);
          printf("SCCP_INIT: Adding signalling point (SP-ID=[%d])...\n", sccp_sp_data_list[i].sp_id);
          ss_conf_info.ss_id = sccp_sp_data_list[i].ssn_data[j].ss_id;
          ss_conf_info.sp_id = sccp_sp_data_list[i].sp_id;
          ss_conf_info.ssn   = sccp_sp_data_list[i].ssn_data[j].ssn;
          if (sccp_prov_add_ss (&ss_conf_info, &ecode) != SS7_SUCCESS)
          {
             printf("SCCP_INIT:Couldnot add SS for SP-ID [%d],errorcode[%d]\n",sp_conf_info.sp_id, ecode);
	  } 
	  else
	  {
           printf("Add SS for SP-ID [%d],errorcode[%d]\n",sp_conf_info.sp_id, ecode);
		j = 0;
           	printf("Add SS for SP-ID [%d],errorcode[%d]\n",sp_conf_info.sp_id, ecode);
	        
	 }
        }			

        if(sccp_sp_data_list[i].local)
        {
                p_csp_info.ss_id = sccp_sp_data_list[i].sp_id;
             /*   p_csp_info.ss_id = 1025;  */
        }
                p_csp_info.csp_id = sp_conf_info.sp_id; 
                p_csp_info.ss_id = sccp_sp_data_list[i].ssn_data[j].ss_id;
                if(sccp_prov_add_csp(&p_csp_info, &ecode) != SS7_SUCCESS)
                {
                        printf("SCCP_INIT: Could not add CSP for SS-ID [%d], error code [%d]\n", ss_conf_info.sp_id, ecode);
                       /* exit (1); */
                }
                    p_css_info.ss_id = sccp_sp_data_list[i].ssn_data[j].ss_id;

                    /* taken from gsn_readcfg.c */
                    p_css_info.css_id = sccp_sp_data_list[1].ssn_data[0].ss_id;
                    /* add concern sub system*/
                    if(sccp_prov_add_css(&p_css_info, &ecode) != SS7_SUCCESS)
                    {
                            printf("SCCP_INIT: Could not add CSS for SS-ID [%d], error code [%d]\n", ss_conf_info.sp_id, ecode);
                           /* exit (1);*/
                    }
/*    sccp_process_mesg((void *)sccp_register_buf_arr);*/
      return 0;
}
