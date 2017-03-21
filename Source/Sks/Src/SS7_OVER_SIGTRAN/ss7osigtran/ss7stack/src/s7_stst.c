/******************************************************************************
**      FUNCTION:
**          Functions for accessing statistics maintained by TCAP / SCCP
**          - code common to both.
**
*******************************************************************************
**
**      FILE NAME:
**          s7_stst.c
**      
**      DESCRIPTION:
**          The Statistics Module provides a functional interface for:
**          (1)Initializing the statistics.
**          (2)Enabling/Disabling collection of statistics.
**          (3)Getting(and optionally)resetting statistics.  
**
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**      
**	26Oct2000  Arun Kumar	     SPR#4543	         Adding Traffic Stats
**      08Jan2000  Rahul Gupta       SPR#2443            Mapping of statistics
**                                                        not done correctly.
**      11May99    Sudipta Pattar    -----------          Fixed SPR 1597
**      10May99    Rahul Gupta       -----------          Fixed SPR 1601
**      15Jan98    GAURAV.TANEJA     HSS:????????         ORIGINAL
**
**
**      Copyright 1998, Hughes Software Systems Ltd.
**
******************************************************************************/

#include "s7_typ.h"
#include "s7_def.h"
#include "s7_stst.h"
#include "s7_error.h"
#include "s7_sm.h"

#include "s7_stpro.h"

extern int ss7_over_sigtran_log_print(const char *format, ...);

#if (defined TCAP_STATS_ENABLED) || (defined SCCP_STATS_ENABLED)

#ifdef TCAP
extern U32bit tcap_stats_flag;
extern ss7_stats_api_t tcap_api_stats;
extern ss7_stats_error_t tcap_error_stats;
extern U32bit tcap_stats_flag;
extern void	tcap_init_stats_q752 (void);

/* SPR # 4543 START */
extern void	tcap_init_stats_traffic (void);
extern void	tcap_get_stats_traffic (pvoid);
/* SPR # 4543 END */

#if 0
extern void	tcap_init_stats_internal (void);
#endif
extern void	tcap_get_stats_q752 (pvoid);
#if 0
extern void	tcap_get_stats_internal (pvoid);
#endif
#endif
#ifdef SCCP
extern U32bit sccp_stats_flag;
extern ss7_stats_api_t sccp_api_stats;
extern ss7_stats_error_t sccp_error_stats;
extern void	sccp_init_stats_q752 (void);
extern void	sccp_init_stats_traffic (void); /* SPR# 4543 */
extern void	sccp_get_stats_traffic (pvoid); /* SPR# 4543 */
#if 0
extern void	sccp_init_stats_internal (void);
#endif
extern void	sccp_get_stats_q752 (pvoid);
#if 0
extern void	sccp_get_stats_internal (pvoid);
#endif
#endif
 
static    U32bit	*p_stats_flag;     
static    ss7_stats_api_t	*p_api_stats;     
static    ss7_stats_error_t	*p_error_stats; 
static    void	(*p_init_stats_q752_fn) (void);
/* SPR# 4543 Start */
static    void	(*p_init_stats_traffic_fn) (void);
static	  void	(*p_get_stats_traffic_fn) (pvoid);
/* SPR# 4543 End */
#if 0
static    void	(*p_init_stats_internal_fn) (void);
#endif
static    void	(*p_get_stats_q752_fn) (pvoid);
#if 0
static    void	(*p_get_stats_internal_fn) (pvoid);
#endif

/* Table to convert global stats type into SCCP/TCAP stats type. To be used 
   until all stack entities are merged later */
/*SPR#2443 Start */
stat_type_t stats_map [] = { SCTC_STATS_API,
			     SCTC_STATS_PROTO_Q752,
			     SCTC_STATS_INVALID,
			     SCTC_STATS_TRAFFIC,   /* SPR# 4543 */
			     SCTC_STATS_ERROR,  
			     SCTC_STATS_ALL,
			     SCTC_STATS_INVALID };
/*SPR#2443 End */
/******************************************************************************
**  GLOBAL FUNCTION:
**     Initializes the specified statistics.
**  DESCRIPTION:
**     This function initializes the statistics specified by stats_type to 
**     zero.It also checks for the validity of module_id. 
**
******************************************************************************/

return_t
sctc_init_stats(module_id_t   module_id,
               stat_type_t  stats_type,
               error_t       *p_ecode)
{
   STACK_PRINT("The stats type is %d\n", stats_type); /* SPR# 4543 */
  /* Convert into TCAP/SCCP #defines */
   if ((stats_type < STATS_API) || (stats_type > STATS_ALL)) {
    /* invalid statistics type received */
    *p_ecode=ESS7_INVALID_STATS_TYPE;
    return SS7_FAILURE;
  }
  stats_type = stats_map [stats_type-1];

  /* check validity of stats_type */
  if(SS7_INVALID_STATS_TYPE(stats_type)) {
  /* invalid statistics type received */
    *p_ecode=ESS7_INVALID_STATS_TYPE;
    return SS7_FAILURE;
  }
  /**********************SPR#1601***********************/
  /* Check if the stats is enabled or disabled */
  switch(module_id)
    {
#ifdef TCAP
    case TCAP_MODULE_ID :
      if ((tcap_stats_flag & (U32bit)stats_type)!= (U32bit)stats_type)
	{
	  *p_ecode=ESS7_STATS_DISABLED;
	  return SS7_FAILURE;
	}
      break;
#endif
#ifdef SCCP
    case SCCP_MODULE_ID :
      if ((sccp_stats_flag & (U32bit)stats_type)!= (U32bit)stats_type)
	{
	  *p_ecode=ESS7_STATS_DISABLED;
	  return SS7_FAILURE;
	}
      break;
#endif
    default :
      *p_ecode=ESS7_INVALID_MODULE_ID;
      return SS7_FAILURE;
    }
  
  /*************************SPR#1601***********************************/


  /* check validity of module_id */
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :
     p_api_stats = &tcap_api_stats;
     p_error_stats = &tcap_error_stats;
     p_init_stats_q752_fn = tcap_init_stats_q752 ;
     p_init_stats_traffic_fn = tcap_init_stats_traffic; /* SPR# 4543 */
#if 0
     p_init_stats_internal_fn = tcap_init_stats_internal ;
#endif
     break;	
#endif
#ifdef SCCP
  case SCCP_MODULE_ID :
     p_api_stats = &sccp_api_stats;
     p_error_stats = &sccp_error_stats;
     p_init_stats_q752_fn = sccp_init_stats_q752 ;
     p_init_stats_traffic_fn = sccp_init_stats_traffic; /* SPR# 4543 */
#if 0
     p_init_stats_internal_fn = sccp_init_stats_internal ;
#endif
     break;	
#endif
  default :
     *p_ecode=ESS7_INVALID_MODULE_ID;
     return SS7_FAILURE;
  }

  if(stats_type & SCTC_STATS_API) {
  /* zero API statistics */
                p_api_stats->in_api_su=0;
                p_api_stats->out_api_su=0;
                p_api_stats->in_api_ll=0;
                p_api_stats->out_api_ll=0;
                p_api_stats->in_api_sm=0;
                p_api_stats->out_api_sm=0;
                p_api_stats->err_api_su=0; 
                p_api_stats->err_api_ll=0;
                p_api_stats->err_api_sm=0;
                p_api_stats->err_out_api_ll=0;
                p_api_stats->err_api_misc=0;
  }

  if(stats_type & SCTC_STATS_ERROR) { 
  /* zero ERROR statistics */       
               p_error_stats->err_api=0;
               p_error_stats->err_msg=0;
               p_error_stats->err_sys=0;
               p_error_stats->err_system_res=0;
  }    
    
  if(stats_type & SCTC_STATS_PROTO_Q752) { 
  /* zero Q752 statistics */       
                (*p_init_stats_q752_fn) ();
  }

/* SPR# 4543 Start */
  if(stats_type & SCTC_STATS_TRAFFIC) { 
  /* zero Traffic statistics */       
                (*p_init_stats_traffic_fn) ();
  }
/* SPR# 4543 End */
#if 0     
  if(stats_type & SCTC_STATS_PROTO_INTERNAL) {
  /* tcap_proto_internal_stats to be initialized later */
                (*p_init_stats_internal_fn) ();
  }  
#endif         
  return SS7_SUCCESS;
}  

/******************************************************************************
**  GLOBAL FUNCTION:
**     Returns the specified statistics.
**  DESCRIPTION:
**     This function copies the specified statistics into p_stats, based on the
**     stats_type. Further if reset_flag is set it initializes the specified
**     statistics to zero. It also checks for the validity of module_id. 
**
******************************************************************************/

return_t  
sctc_get_stats(module_id_t   module_id,
              pvoid         p_stats,
              stat_type_t  stats_type,
              Boolean       reset_flag,
              error_t       *p_ecode)  
{
  stat_type_t stats_type_sav;

  /* Convert into TCAP/SCCP #defines */
   if ((stats_type < STATS_API) || (stats_type > STATS_ALL)) {
    /* invalid statistics type received */
    *p_ecode=ESS7_INVALID_STATS_TYPE;
    return SS7_FAILURE;
  }
  
  /* save original stats type in case we need to init the stats */
  stats_type_sav = stats_type;

  stats_type = stats_map [stats_type-1];

  /* check validity of stats_type */
  if(SS7_INVALID_STATS_TYPE(stats_type)) {
  /* invalid statistics type received */
     *p_ecode=ESS7_INVALID_STATS_TYPE;
     return SS7_FAILURE;
  }         

  /* check validity of module_id */
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :
     p_stats_flag = &tcap_stats_flag;
     p_api_stats = &tcap_api_stats;
     p_error_stats = &tcap_error_stats;
     p_get_stats_q752_fn = tcap_get_stats_q752 ;
     p_get_stats_traffic_fn = tcap_get_stats_traffic ; /* SPR# 4543 */
#if 0
     p_get_stats_internal_fn = tcap_get_stats_internal ;
#endif
     break;	
#endif
#ifdef SCCP
  case SCCP_MODULE_ID :
     p_stats_flag = &sccp_stats_flag;
     p_api_stats = &sccp_api_stats;
     p_error_stats = &sccp_error_stats;
     p_get_stats_q752_fn = sccp_get_stats_q752 ;
     p_get_stats_traffic_fn = sccp_get_stats_traffic ; /* SPR# 4543 */
#if 0
     p_get_stats_internal_fn = sccp_get_stats_internal ;
#endif
     break;	
#endif
  default :
     *p_ecode=ESS7_INVALID_MODULE_ID;
     return SS7_FAILURE;
  }

  /* check state of p_stats_flag */
  if (!(*p_stats_flag & stats_type)) {
    *p_ecode=ESS7_STATS_DISABLED;
    return SS7_FAILURE;
  } 

  if (stats_type & SCTC_STATS_API) {                         
  /* copy API statistics into structure pointed to by p_stats */
    *((ss7_stats_api_t*)p_stats)=*p_api_stats;     
  } 
  else if(stats_type & SCTC_STATS_ERROR) { 
  /* copy error statistics into structure pointed to by p_stats */     
    *((ss7_stats_error_t*)p_stats)=*p_error_stats; 
  }
  else if(stats_type & SCTC_STATS_PROTO_Q752) {
  /* copy Q752 statistics into structure pointed to by p_stats */ 
    (*p_get_stats_q752_fn) (p_stats);
  }

/* SPR# 4543 */
  else if(stats_type & SCTC_STATS_TRAFFIC) {
  /* copy traffic statistics into structure pointed to by p_stats */ 
    (*p_get_stats_traffic_fn) (p_stats);
  }
/* SPR# 4543 */
#if 0           
  else if(stats_type & SCTC_STATS_PROTO_INTERNAL) {
  /* copy internal statistics into structure pointed to by p_stats */   
    (*p_get_stats_internal_fn) (p_stats);
  }
#endif

  if(reset_flag) {
  /* initialize respective statistics to zero after copy */
     if(sctc_init_stats(module_id, stats_type_sav, p_ecode)==SS7_FAILURE)
       return SS7_FAILURE;
  }

  return SS7_SUCCESS;
} 

/******************************************************************************
**  GLOBAL FUNCTION:
**     Enables the specified statistics.
**  DESCRIPTION:
**     This function enables the specified statistics in tcap_stats_flag as 
**     per stats_type. It also checks for the validity of module_id. 
**
******************************************************************************/

return_t
sctc_enable_stats(module_id_t  module_id,
                 stat_type_t  stats_type,
                 error_t      *p_ecode)
{

  /* Convert into TCAP/SCCP #defines */
   if ((stats_type < STATS_API) || (stats_type > STATS_ALL)) {
    /* invalid statistics type received */
    *p_ecode=ESS7_INVALID_STATS_TYPE;
    return SS7_FAILURE;
  }
  stats_type = stats_map [stats_type-1];

  /* check validity of stats_type */  
  if(SS7_INVALID_STATS_TYPE(stats_type)) {
  /* invalid statistics type received */
     *p_ecode=ESS7_INVALID_STATS_TYPE;
     return SS7_FAILURE;
  }             

  /* check validity of module_id */
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :

     /* SPR 1597: Return failure if statistics already enabled */
     if ((tcap_stats_flag & (U32bit)stats_type) == (U32bit)stats_type)
     {
	*p_ecode = ESS7_STATS_ALREADY_ENABLED;
	return SS7_FAILURE;
     }

     tcap_stats_flag |= (U32bit)stats_type;
     break;	
#endif
#ifdef SCCP
  case SCCP_MODULE_ID :

     /* SPR 1597: Return failure if statistics already enabled */
     if ((sccp_stats_flag & (U32bit)stats_type) == (U32bit)stats_type)
     {
	*p_ecode = ESS7_STATS_ALREADY_ENABLED;
	return SS7_FAILURE;
     }

     sccp_stats_flag |= (U32bit)stats_type;
     break;	
#endif
  default :
     *p_ecode=ESS7_INVALID_MODULE_ID;
     return SS7_FAILURE;
  }

  return SS7_SUCCESS;
}

/******************************************************************************
**  GLOBAL FUNCTION:
**     Disables the specified statistics.
**  DESCRIPTION:
**     This function disables the specified statistics in tcap_stats_flag as 
**     per stats_type. It also checks for the validity of module_id. 
**
*****************************************************************************/ 
return_t
sctc_disable_stats(module_id_t  module_id,
                  stat_type_t stats_type,
                  error_t      *p_ecode)
{

  /* Convert into TCAP/SCCP #defines */
   if ((stats_type < STATS_API) || (stats_type > STATS_ALL)) {
    /* invalid statistics type received */
    *p_ecode=ESS7_INVALID_STATS_TYPE;
    return SS7_FAILURE;
  }
  stats_type = stats_map [stats_type-1];

  /* check validity of stats_type */  
  if(SS7_INVALID_STATS_TYPE(stats_type)) {
  /* invalid statistics type received */
    *p_ecode=ESS7_INVALID_STATS_TYPE;
    return SS7_FAILURE;
  }             
  
  /* check validity of module_id */
  switch (module_id) {
#ifdef TCAP
  case TCAP_MODULE_ID :

     /* SPR 1597: Return failure if statistics already disabled */
     if ((tcap_stats_flag & (U32bit)stats_type) != (U32bit)stats_type)
     {
	*p_ecode = ESS7_STATS_ALREADY_DISABLED;
	return SS7_FAILURE;
     }

     tcap_stats_flag &= ~((U32bit)stats_type);
     break;	
#endif
#ifdef SCCP
  case SCCP_MODULE_ID :

     /* SPR 1597: Return failure if statistics already disabled */
     if ((sccp_stats_flag & (U32bit)stats_type) != (U32bit)stats_type)
     {
	*p_ecode = ESS7_STATS_ALREADY_DISABLED;
	return SS7_FAILURE;
     }

     sccp_stats_flag &= ~((U32bit)stats_type);
     break;	
#endif
  default :
     *p_ecode=ESS7_INVALID_MODULE_ID;
     return SS7_FAILURE;
  }

  return SS7_SUCCESS;
}
#endif  /* #if (defined TCAP_STATS_ENABLED) || (defined SCCP_STATS_ENABLED) */
