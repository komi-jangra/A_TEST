#ifndef _SCCP_PORT_H
#define _SCCP_PORT_H

#include "ss7oversigtran_limits.h"

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

/*#include "common_type.h" */

#ifndef MAX_HOSTNAME_LEN
#define MAX_HOSTNAME_LEN      GSN_MAX_HOSTNAME_LEN
#endif


typedef unsigned char  U8BIT;
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned long  UInt32;
typedef unsigned int   UBITS;

#define SIGTRAN_MAX_SSN_PER_PC 1 /* instead 9 only 1 for BSC-BSSAP 9*/
/*#define SIGTRAN_MAX_SSN_PER_PC 6 */
#define GSN_MAX_VLR_SUPPORTED 5
#define MAP_MAX_SS7_ADDR_LEN 20
#define	GSN_NULL_SSN		0xFF
#define SGSN_SSN    		149
#define	GSN_NULL_PC		0xFFFF

/* Miscellaneous macros */
#ifdef SINGLE_THREAD
#define SL_MUTEX_DEF(name)
#define SL_MUTEX_INIT(mutex)
#define SL_MUTEX_LOCK(mutex)
#define SL_MUTEX_UNLOCK(mutex)

/* friendly alternate names (?!? :) */
#define SL_LOCK_DEF(name)
#define SL_LOCK_INIT(mutex)
#define SL_LOCK(mutex)
#define SL_UNLOCK(mutex)



#define OM_ELEMENT_SCCP_T_REASS 1
#define OM_ELEMENT_SCCP_T_STAT_INFO 2
#define OM_ELEMENT_SCCP_T_CONG_ATTACK 3
#define OM_ELEMENT_SCCP_T_CONG_DECAY 4
#define OM_ELEMENT_SCCP_SEG_PAR_Z 5


#define MAX_SP_DATA_LIST   20

#define SCCP_MAX-SP 64
#define SCCP_MAX-SS  32
#define SCCP_MAX-CSP 16
#define SCCP_MAX-CSS 16 
#define SS7_API_HEADER_LEN      5
#define API_LEN_LSB  3
#define API_LEN_MSB  4
#define GET_API_LEN(p_api)    (p_api[API_LEN_LSB] | (p_api[API_LEN_MSB] << 8))

typedef	struct	t_gt_entry_ {
	int		valid;
	char		pattern_i[SS7_OVER_SIGTRAN_SCCP_GT_PATTERN_LEN];
	char		pattern_o[SS7_OVER_SIGTRAN_SCCP_GT_PATTERN_LEN];
	unsigned char	ssn;
	unsigned long int	pc;
} t_gt_entry;

extern	t_gt_entry	gsn_gtt_table[SS7_OVER_SIGTRAN_SCCP_NUM_GT_ENTRY];

typedef struct {
    int                 valid;
    unsigned long int   ss_id;
    unsigned int        ssn;
} t_ssn_data;

typedef struct {
    int                 valid;
    unsigned int        nw_id;
    unsigned int        local;
    unsigned int        ssf;
    unsigned long int   sp_id;
    unsigned long int   pc;
    t_ssn_data          ssn_data[SS7_OVER_SIGTRAN_SCCP_MAX_SSN_PER_PC];
} t_sp_data;

#if 0
typedef struct {
   pc_t pc;
   U8bit ssa_received;
   t_ss7_address vlr_no;
} t_gsn_sccp_vlr_data;
#endif

/* SCCP Parameters */
typedef struct
{
        UInt32 t_reass;
        UInt32 t_stat_info;
        UInt32 t_cong_attack;
        UInt32 t_cong_decay;
        UInt32 seg_parm_z;
        UInt32  max_sp;
        UInt32   max_ss;
        UInt32   max_css ;
        UInt32   max_csp ;
        UINT8 standard;         /* Standard to be followed */

}gsn_config_sccp_params_t;

typedef struct
{
   /*gsn_config_m3ua_params_t     m3ua_params;
   gsn_config_sctp_params_t     sctp_params; */
   gsn_config_sccp_params_t     sccp_params;
   UInt32 no_of_gtt;
   UINT8 driver;
}gsn_config_db_t;


/* Added by Amaresh start for redundancy enhancement as on dated 17-03-16 */
typedef struct
{
  unsigned int    curr_state;
  unsigned int    prev_state;
  unsigned int    peer_card_curr_state;
  unsigned char   info ;
}bpmCardState_info_t;

/*extern bpmCardState_info_t bpmCardState;*/

/* Added by Amaresh stop for redundancy enhancement as on dated 17-03-16 */


/* GSN configuration initialisation functions */
/*gsn_return_t gsn_set_config(gsn_config_db_t *);  */
/*gsn_return_t GSN_GET_CONFIG(gsn_config_db_t *);*/
#if 0
struct gsn_configdata_t{
    SL_LOCK_DEF (access);
    gsn_config_db_t entry;
};

struct gsn_configdata_t gsn_configdata; 

#define GSN_GET_CONFIG(data) data = gsn_configdata.entry
#endif

  /*  error_t ecode;\*//* Commented by Amaresh */
#define SCCP_NM_SET_TIMER_REQ_BUF(type, value) \
{\
	error_t ecode;\
	U8bit num_timers = 1;\
	tmr_buffer_t timers[1];\
	timers[0].timer_index = type;\
	timers[0].timer_value = (U32bit)value;\
	if(sccp_init_timers(num_timers, timers, &ecode) == SS7_FAILURE)\
	{\
    LOG_PRINT(DEBUG,"[ENCAPS:: ] -> SCCP TIMER REQ from SCCP_NM_SET_TIMER_REQ_BUF Failed"); \
	}\
	else\
	{\
    LOG_PRINT(DEBUG,"[ENCAPS:: ] -> SCCP TIMER REQ from SCCP_NM_SET_TIMER_REQ_BUF Succeeded"); \
	}\
}


#endif
#endif
