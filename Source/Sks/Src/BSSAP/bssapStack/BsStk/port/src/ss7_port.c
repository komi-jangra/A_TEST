/*******************************************************************************
**      FILE NAME:
**          ss7_port.c
**
**      DESCRIPTION:
**              This files defines all the Porting functions used by BSSAP Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sl.h>

#include <s7_typ.h>
#include <s7_api.h>
#include <s7_def.h>
#include <s7_error.h>
#include <s7_prot.h>
#include "bssap_limits.h"

#ifdef LOGGER_IMR
#if 0
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include <sysxxx_msgstruct.h>
#include "ipcfrm_syslog.h"
#endif

#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_syslog.h>
SysAddr slfAddr;



#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

extern return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
			      src_id_t src_id, dst_id_t dst_id,
			      error_t *p_ecode);
extern sl_module_t ss7_bssap_mid;

sl_pool_t ss7_pool;

#if !defined MTP3
void ss7_send_to_m3ua (unsigned char *, s7_len_t);
#else
void ss7_send_to_mtp3 (unsigned char *, s7_len_t);
#endif

void *ss7_mem_get (s7_len_t noctets);

return_t ss7_start_timer (U32bit timer_duration, pvoid p_timer_buf,
			  s7_len_t size, U8bit timer,
			  timer_id_t *bs_timer_id, error_t *p_error)
{
    sl_time_val tv;
    pvoid   timer_start_buf;
    unsigned char* t_buf;
    s7_len_t         mesg_len;
    mesg_len    = 6 + size;
    timer_start_buf =   ss7_mem_get(mesg_len);
    timer_id_t timer_ret;
    t_buf   = timer_start_buf;

  /* Create the buffer in API format */
    *(t_buf)      =   SS7_TIMER_API_ID;
    *(t_buf + 1)  =   1;
    *(t_buf + 2)  =   1;
    *(t_buf + 3)  =   (mesg_len & 0x00FF);
    *(t_buf + 4)  =   ((mesg_len & 0xFF00) >> 8 );
    *(t_buf + 5)  =   timer;

    ss7_memcpy((void *)(t_buf + 6),(void *)p_timer_buf, size);
    /* Assuming timer_val expresses in 10s of millisecond*/
    tv.s = timer_duration / 100;
    tv.us = (timer_duration % 100) * 10000;
    *bs_timer_id = (timer_id_t)sl_timer_start (&tv, timer_start_buf);
    LOG_PRINT(DEBUG,"start timer key bs_timer_id %ul",*bs_timer_id);
    return SS7_SUCCESS;
}

return_t ss7_stop_timer (timer_id_t timer_id, error_t *p_error)
{
    void *data;
    if(qvTimerRunning((QTIMER *)timer_id))
    {
	    if ((data = sl_timer_get_data ((sl_timer_t)timer_id)))
    	    {
		sl_buf_free (data);
		sl_timer_cancel ((sl_timer_t)timer_id);
    	    }
     }
     else
     {
	LOG_PRINT(DEBUG,"[ENCAPS:: ] Timer Is not Running So no need to STOP \n");
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
    if (noctets < BSSAP_BUF_SIZE)
	{
		p =  sl_buf_alloc (ss7_pool);
        if(p)
          memset (p,0,BSSAP_BUF_SIZE);
        return p;
	}
    else 
    {
        sl_log (SL_LOG_WARN,"WARNING: ss7_mem_get requested [%d] bytes.Using qvMsgAllocBySize\n", noctets);
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
pvoid bs_mem_zero (U8bit *ptr, U32bit size)
{
     return  memset((void *)ptr,0, (size_t)size);
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
	//LOG_PRINT(INFO,"[ENCAPS:: ] Inside the function ss7_dispatch_buffer() \n");
    switch (dst_id)
    {
    case SCCP_MODULE_ID:
	LOG_PRINT(INFO,"DISPATCH BUFFER: SEND Message From BSSAP-->SCCP \n");
       
	bssap_send_to_sccp((const void *)p_buffer);
#if 0
	/* Added by Amaresh start as on dated 22-01-16 for memory leak */
     if(p_buffer)
    {
        bssap_free (p_buffer);
        LOG_PRINT(INFO,"BSSAP::INIT:Free Memory send from bssap \n");
    }
/* Added by Amaresh stop as on dated 22-01-16 for memory leak */
#endif
	break;
    case BSSAP_MODULE_ID:
	LOG_PRINT(INFO,"DISPATCH BUFFER: SEND Message From BSC-APP-->BSSAP \n");
	sl_mq_send (ss7_bssap_mid, 0, p_buffer);
	break;
    case BSSAP_USER_MODULE_ID:
	LOG_PRINT(INFO,"DISPATCH BUFFER: SEND Message From BSSAP-->BSC-APP \n");
      	bssap_send_to_user((const void *)p_buffer,noctets);
	break;
    default:
	sl_log(SL_LOG_ERROR,"DISPATCH BUFFER:Dropping message to entity [%d]\n", dst_id);
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

return_t 
ss7_send_update (module_id_t module_id, U8bit type_of_data, s7_len_t msg_len,
        pvoid p_redn_data, error_t *p_ecode)
{
    ss7_mem_free(p_redn_data);
    return(SS7_SUCCESS);
}
