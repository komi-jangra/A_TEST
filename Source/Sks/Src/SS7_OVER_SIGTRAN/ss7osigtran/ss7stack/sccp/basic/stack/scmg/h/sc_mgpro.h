/******************************************************************************
**
**  Prototypes for the GR changes in SCCP Mangement part
**
******************************************************************************/
 
#ifndef _SC_MGPRO_H
#define _SC_MGPRO_H
 
void sccp_m3_pause_cluster_ind
        _ARGS_ ((U8bit * p_api));
 
void sccp_m3_resume_cluster_ind
        _ARGS_ ((U8bit * p_api));
 
return_t sccp_parse_m3_pause_cluster_ind_api
        _ARGS_ ((U8bit * p_api, scmg_info_t * p_info, error_t * p_ecode));
 
return_t sccp_parse_m3_resume_cluster_ind_api
        _ARGS_ ((U8bit * p_api, scmg_info_t * p_info, error_t * p_ecode));
 
#endif

