/***********************************File Header ***************************
       File Name        : oamscfg_alarm_handler.h
       Purpose          : This file contains include files for CFG

       Project          : BSC OAM
       Subsystem        : Oams
       Author           : Aricent Bangalore
       CSCI ID          :
       Version          :
************************************* End **********************************/

#ifndef  __OAMCFG_INCLUDES_H_
#define  __OAMCFG_INCLUDES_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <memory.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <errno.h>
#include <time.h>
#include <sysxxx_typedef.h>
#include <sysxxx_hashdefs.h>
#include <sysxxx_datastruct.h>
#include <sysxxx_msgopcode.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <sysxxx_msgstruct.h>
#include <syscmn_hashdefs.h>
#include <syscmn_datastruct.h>
#include <sysxxx_alarm.h>
#include <oamxxx_tableapidefs.h>
#include <oamomc_errorcodes.h>
#include <oamsnmp_hashdefs.h>
#include <oamxxx_hashdefs.h>
#include <dbsxxx_commondefs.h>
#include <dbsxxx_commonwrappers.h>
#include <dbsxxx_cfg_dbwrapper.h>
#include <dbsxxx_cellh_dbwrapper.h>
#include <dbsxxx_grhm_dbwrapper.h>
#include <syspcu_typedefs.h>
//#if BPM_PRESENT == 1
#include <bpmxxx_commonDef.h>
#include <bpmxxx_OAM_commonDef.h>
//#endif

#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <ipcfrm_msgdef.h>
#include <dsp_global.h>
#include <dsp_pp_com.h>
#include <msg_struct.h>

#include <mgs_common_hashdef.h>
#include <mgs_trau_hashdef.h>
#include <mgs_common_hashdef.h>
#include <mgs_trau_msgstruct.h>
#include <mgs_tsi_msgstruct.h>
#include <oamsxxx_alarmid.h>
#include <sysxxx_slotid.h>
#include <oamsxxx_typedef.h>
#include <oamxxx_datastruct.h>
#include <oamxxx_msgstruct.h>
#include <oamsxxx_hashdef.h>
#include <oamscfg_hashdefs.h>
#include <oams_psapp_msgstruct.h>
#include <oamscfg_type.h>
#include <csappxxx_common_datastruct.h>
#include <oamsxxx_msgstruct.h>
#include "oams_msgstruct.h"
#include <oams_hashdefs.h>
#include <oamscfg_objectHandler_header.h>
#include <dsp_pp_com.h>
#include <dsp_com_api.h>
#include <oamscfg_trau_msgstruct.h>
#include "oamsxxx_mutex.h"
#include <bpmDiaglib.h>
#include<oamscfg_diagnostics_handler.h>
#include <oamscfg_externs.h>
#include <DBLIBError.h>
#include <signal.h>
#include <oamsxxx_listdefs.h>
#include <oamscfg_signal_handler.h>
#include <oamscfg_bss_object_handler.h>
#include <oamscfg_bic_object_handler.h>
#include <oamsxxx_bpmmsgstruct.h>
#include <oamscfg_mlppp_object_handler.h>
#include <oamscfg_msg_handler.h>
#include <oamscfg_responses.h>
#include <oamscfg_trx_object_handler.h>
#include <oamscfg_e1_object_handler.h>
#include <oamscfg_e1timeslot_object_handler.h>
#include <oamscfg_alarm_handler.h>
#include <oamscfg_setdelmsghandler.h>
#include <oamscfg_cell_object_handler.h>
#include <oamscfg_cell_object_consistancy_check.h>
#include <oamscfg_bic_trx_ts_handler.h>
#include <oamscfg_sw_upgrade_handler.h>
#include <swversion_parser.h>
#include <oamscfg_clk_object_handler.h>
#include <oamscfg_stack_object_handler.h>
#include <oamscfg_clean_transient_table.h>
#include <scm_hashdefs.h>
#include <scm_msgdef.h>
#include <oamscfg_ccu_handler.h>
#include <oamxxx_errorcode.h>
#include <oam_typedefs.h>
/*Changes PCU R2.5 Aricent -- START*/
#include <oamscfg_nsvc_object_handler.h>
#include <oamscfg_consistancy_check.h>
#include <oamscfg_mccfr_resource_handler.h>
#include <oamscfg_perf_counter_init.h>
/*Changes PCU R2.5 Aricent -- END*/
#include <csappxxx_common_datastruct.h>
#include<csappxxx_cbsh_cfg_msgstruct.h>
#include<oamscfg_cbs_handler.h>
#include<csappxxx_hashdef.h>
#include<csapp_codec_util.h>
#include<csappxxx_cbsh_cbshcodec_commondef.h>
#ifdef CFG_UTE
#include <oamscfg_ut.h>
#endif 
#include <oamscfg_tsgroup_object_handler.h>
#include <oamscfg_externalport_handler.h>
#include <oamscfg_ha_handler.h>
#endif /*__OAMCFG_INCLUDES_H_*/

/********************************* Change History ***************************
   Release     Patch       Author         Description
   CS2                     Pratibha       Enum Removal Change

************************************** End *********************************/
