/*
 * Porting functions for SS7 stack
 *
 * Copyright 2000, Hughes Software Systems, Ltd.
 */

#include <time.h>
#include <string.h>
#include <stdlib.h>

#include <sl.h>

#include <s7_typ.h>
#include <s7_api.h>
#include <s7_def.h>
#include <s7_error.h>
#include <s7_prot.h>
#include "ss7oversigtran_limits.h"
/*#include "ss7oversigtran_config.h"*/

#define LOGGER_IMR
#ifdef LOGGER_IMR
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include <sysxxx_msgstruct.h>
#include "ipcfrm_syslog.h"
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

#ifndef SIGTRAN_SCM_IF
#define SIGTRAN_SCM_IF
#endif
#if 0
#ifndef SIGTRAN_SCCP_REDN_IF
#define SIGTRAN_SCCP_REDN_IF
#endif
#endif

#define OM_PROCESSING_MTP3_STATUS 21234

extern return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
			      src_id_t src_id, dst_id_t dst_id,
			      error_t *p_ecode);
extern sl_module_t ss7_sccp_mid;
#ifdef MTP3
extern sl_module_t ss7_mtp3_mid;
extern sl_module_t ss7_mtp2_mid;
extern sl_module_t nm_mid;
#endif
extern void sccp_send( const void *        buffer);
/* Added by Amaresh for EMAP Handelling in terms of BSSAP Socket I/F Start */
extern void bssap_send( const void *        buffer);
/* Added by Amaresh for EMAP Handelling in terms of BSSAP Socket I/F Start */
extern void sigtran_scm_if_send( const void *        buffer);

sl_pool_t ss7_pool;
sl_pool_t mtp3_ss7_pool;
#if !defined MTP3
void ss7_send_to_m3ua (unsigned char *, s7_len_t);
#else
void ss7_send_to_mtp3 (unsigned char *, s7_len_t);
#endif

void *ss7_mem_get (s7_len_t noctets);

return_t ss7_start_timer (U32bit timer_duration, pvoid p_timer_buf,
			  s7_len_t size, module_id_t module_id,
			  timer_id_t *p_timer_id, error_t *p_error)
{
    sl_time_val tv;
    unsigned char *buf = sl_buf_alloc (ss7_pool);
	if(!buf)
		return SS7_FAILURE;
    tv.s = timer_duration / 100;
    tv.us = (timer_duration % 100) * 10000;
    *p_timer_id = (timer_id_t)sl_timer_start (&tv, buf);

    buf[0] = SS7_TIMER_API_ID;
    buf[1] = 1;   // Fill the Version
    buf[2] = 1;
    buf[3] = (size + 5 + 8) & 0xff;
    buf[4] = (size + 5 + 8) >> 8;
    
    memcpy (buf + 5, p_timer_buf, size);

    return SS7_SUCCESS;
}

return_t ss7_stop_timer (timer_id_t timer_id, error_t *p_error)
{
    void *data;

    if ((data = sl_timer_get_data ((sl_timer_t)timer_id)))
    {
	sl_buf_free (data);
	sl_timer_cancel ((sl_timer_t)timer_id);
    }
    return SS7_SUCCESS;
}

void ss7_get_absolute_time (U32bit *p_absolute_time)
{
    *p_absolute_time = (U32bit) time (0); //Not returned in ms.
    //U32bit is not long enough to hold the time in milliseconds.
    //Local Manager expects the value to be in seconds.
}

void *ss7_mem_get (s7_len_t noctets)
{
	void *p;
    if (noctets < SS7_OVER_SIGTRAN_SCCP_BUF_SIZE)
	{
		p =  sl_buf_alloc (ss7_pool);
        if(p)
          memset (p,0,SS7_OVER_SIGTRAN_SCCP_BUF_SIZE);
        return p;
	}
    else 
    {
				LOG_PRINT(INFO,"SCCP:WARNING: ss7_mem_get requested [%d] bytes.Using qvMsgAllocBySize\n", noctets);
/*
        sl_log (SL_LOG_WARN,"WARNING: ss7_mem_get requested [%d] bytes.Using qvMsgAllocBySize\n", noctets);*/
		p = qvMsgAllocBySize (noctets);
        if(p)
         memset (p,0,noctets);
        return p;
    }
}

return_t ss7_mem_free (pvoid ptr)
{
    sl_buf_free (ptr);
    return SS7_SUCCESS;
}

pvoid ss7_mem_zero (pvoid ptr, U32bit size)
{
    return memset (ptr, 0, size);
}

return_t ss7_memcpy (pvoid dest, pvoid src, s7_len_t noctets)
{
    memcpy (dest, src, noctets);
    return SS7_SUCCESS;
}

void ss7_memmove (U8bit *dest, U8bit *src, s7_len_t noctets)
{
    memmove (dest, src, noctets);
}

U32bit ss7_rand (void)
{
    return (U32bit) rand ();
}

return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
			      src_id_t src_id, dst_id_t dst_id,
			      error_t *p_ecode)
{
  QMODULE destination_module;
	LOG_PRINT(INFO,"[ENCAPS:: ] Inside the function ss7_dispatch_buffer() \n");
	LOG_PRINT(INFO,"[ENCAPS:: ] dst_id for routing message [%d] \n",dst_id);
    switch (dst_id)
    {
    case TCAP_MODULE_ID:
			LOG_PRINT(INFO,"[ENCAPS:: ] SEND Messgae from SCCP to TCAP by calling sccp_send()\n");
      sccp_send((const void *)p_buffer);
	break;
/* Added by Amaresh for EMAP Handelling in terms of BSSAP Socket I/F Start */
    case BSSAP_MODULE_ID:
			LOG_PRINT(INFO,"[ENCAPS:: ] SEND Messgae from SCCP to BSSAP=EMAP by calling bssap_send()\n");
      bssap_send((const void *)p_buffer);
	break;
/* Added by Amaresh for EMAP Handelling in terms of BSSAP Socket I/F Stop */

/* Added by Amaresh for SCCP RM module Handelling in terms of RM I/F Start */
    case SCCP_RM_MODULE_ID:
			LOG_PRINT(INFO,"[ENCAPS:: ]SEND Messgae from SCCP/M3UA to RM-STANDBY/Active card SCCP by calling sccp_rm_send()\n");
      sccp_rm_send((const void *)p_buffer);
	break;
/* Added by Amaresh for EMAP Handelling in terms of BSSAP Socket I/F Stop */
#if defined MTP3
    case MTP2_MODULE_ID:
        sl_mq_send (ss7_mtp2_mid, 0, p_buffer);
        break;
#endif
    case MTP3_MODULE_ID:
#if !defined MTP3
	LOG_PRINT(INFO,"[ENCAPS:: ] SEND Messgae to M3UA by calling ss7_send_to_m3ua()\n");
	ss7_send_to_m3ua (p_buffer, noctets);
#else
	sl_mq_send (ss7_mtp3_mid, 0, p_buffer);
#endif
	break;
  case SCCP_MODULE_ID:
	LOG_PRINT(INFO,"[ENCAPS:: ] SEND Messgae to SCCP by calling sl_mq_send()\n");
	sl_mq_send (ss7_sccp_mid, 0, p_buffer);
	break;
#if defined MTP3
    case SYS_MGMT_ID:
	sl_mq_send (nm_mid, OM_PROCESSING_MTP3_STATUS, p_buffer);
    break;
#endif

#ifdef SIGTRAN_SCM_IF
    case SYS_MGMT_ID:
					if (p_buffer[0] == SCCP_SM_REQUEST_API)
					{
						LOG_PRINT(INFO,"[ENCAPS:: ] SEND Messgae to SCCP by calling sl_mq_send()\n");
						sl_mq_send (ss7_sccp_mid, 0, p_buffer);
					}
					if (p_buffer[0] == SCCP_SM_RESPONSE_API)
					{
						if (p_buffer[5] == 0x05)/* 0x05 = SS7_SM_REDN */
						{
							LOG_PRINT(INFO,"[ENCAPS:: ] SS7_SM_REDN message so drop the message:NOT_TO_SEND \n");
						}
						else
						{
							LOG_PRINT(INFO,"[ENCAPS:: ] SEND Messgae from SCCP to SCM via socket I/F\n");
							sigtran_scm_if_send((const void *)p_buffer);
						}
					}
					if (p_buffer[0] == M3UA_SM_REQUEST_API)
					{
						LOG_PRINT(INFO,"[M3UA_SM_RM]SEND to M3UA by calling sigtran_m3ua_handle_omc_command\n");
						sigtran_m3ua_handle_omc_command(p_buffer);
					/*	sl_mq_send (ss7_sccp_mid, 0, p_buffer);*/
					}
					if (p_buffer[0] == M3UA_SM_RESPONSE_API)
					{
								if (p_buffer[5] == 0x05)/* 0x05 = SS7_SM_REDN */
                {
                    LOG_PRINT(INFO,"[M3UA_RM] SS7_SM_REDN message from Active SCTP\n");
                    sigtran_m3ua_handle_rm_response(p_buffer);
                }
                else
                {
                    LOG_PRINT(INFO,"[M3UA_SM] SEND Messgae from M3UA to SCM via socket I/F\n");
                    sigtran_scm_if_send((const void *)p_buffer);
                }

					}
					if (p_buffer[0] == SCTP_SM_REQUEST_API)
					{
						LOG_PRINT(INFO,"[SCTP_SM_RM]SEND to SCTP by calling sigtran_sctp_handle_omc_command\n");
						sigtran_sctp_handle_omc_command(p_buffer);
					/*	sl_mq_send (ss7_sccp_mid, 0, p_buffer);*/
					}
					if (p_buffer[0] == SCTP_SM_RESPONSE_API)
					{
								if (p_buffer[5] == 0x05)/* 0x05 = SS7_SM_REDN */
            		{
              			LOG_PRINT(INFO,"[SCTP_RM] SS7_SM_REDN message from Active SCTP\n");
									  sigtran_sctp_handle_rm_response(p_buffer);	
            		}
								else
								{
										LOG_PRINT(INFO,"[SCTP_SM] SEND Messgae from SCTP to SCM via socket I/F\n");
										sigtran_scm_if_send((const void *)p_buffer);
								}
					}
					if (p_buffer[0] == 0x63)/*Alarm Id from Sigtran to SCM */
					{
						LOG_PRINT(INFO,"[ALARM_SIGTRAN_SM]SEND ALARM Messgae from SIGTRAN to SCM via socket I/F\n");
						sigtran_scm_if_send((const void *)p_buffer);
					}
 /* New enhancement tbd on next release Amaresh */				
/*		sl_mq_send (nm_mid, OM_PROCESSING_MTP3_STATUS, p_buffer);*/
    break;
#endif  /* SIGTRAN_SCM_IF */

    default:
	sl_log(SL_LOG_ERROR,"Dropping message to entity [%d]\n", dst_id);
        break;
    }

  /*  *p_ecode = 0; */
    return SS7_SUCCESS;
}

return_t ss7_err_handler (error_t error, module_id_t module_id,
			  pvoid p)
{
    sl_log (SL_LOG_ERROR,"ERROR: ss7_err_handler: %d from %d\n", error,
		 module_id);
    return SS7_SUCCESS;
}
#if 0
return_t 
ss7_send_update (module_id_t module_id, U8bit type_of_data, s7_len_t msg_len,
        pvoid p_redn_data, error_t *p_ecode)
{
/*    ss7_mem_free(p_redn_data);*//* Commented by Amaresh as on dated 22-02-16 */
    return(SS7_SUCCESS);
}
#endif /* Commented by Amaresh as on dated 29-02-16 */

