/*****************************************************************************
**
**  FILE :
**    Initialisation file for the SCCP connection oriented part
**
******************************************************************************
**
**  FILENAME :
**    sc_coini.c
**
**  DESCRIPTION :
**
**  Date      Name             Reference     Reason
**  _________________________________________________________________________
**  10Jul2000 Ramu Kandula                   Fixed SPR 4051
**
*****************************************************************************/

#include "sc_stgl.h"

#ifdef SCCP_INCLUDE_CO_SERVICE

return_t (* sccp_co_func_ptr_table [SCCP_MAX_CO_STATES][SCCP_MAX_EVENTS])
          _ARGS_((msg_info_t     *p_info,
                  error_t        *p_ecode)) ;

/*****************************************************************************
**
**  FUNCTION :
**   Initialise the function pointer table for the state machine for the
**   Connection Oriented Part
**
******************************************************************************
**
**  DESCRIPTION :
**    This function will initialise the function pointer table
**    with all the state-event function and putting appropriate
**    pointers for events in states where nothing is to be done or
**    where error has to be reported.
**
*****************************************************************************/

void
sccp_init_co_function_table
#ifdef ANSI_PROTO
  (void)
#else
  ( )
#endif
{
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_N_CONNECT_REQUEST_EVENT] = 
                            sccp_conn_idle_n_conn_req ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_N_CONNECT_RESPONSE_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_N_DISCONNECT_REQ_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_REQUEST_TYPE_1_EVENT] = 
                            sccp_conn_idle_req_type_1 ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_REQUEST_TYPE_2_EVENT] = 
                            sccp_conn_idle_req_type_2 ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_N_RESET_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_N_RESET_RESPONSE_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_N_DATA_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_N_EXP_DATA_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_CR_EVENT] = 
                            sccp_conn_idle_cr ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_CC_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_CREF_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_RLSD_EVENT] = 
                            sccp_conn_idle_rlsd ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_RLC_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_RSR_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_RSC_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_ROUTE_FAIL_EVENT] = 
                            sccp_conn_idle_routefail ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_DT1_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_DT2_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_AK_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_IT_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_ED_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_EA_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_ERR_EVENT] = 
                            sccp_conn_idle_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_CONNEST_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_IAR_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_IAS_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_REL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_REPREL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_INT_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_GAURD_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_RESET_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_REASSEMBLY_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_IDLE][SCCP_T_FREEZE_TIME_OUT] = 
                            sccp_do_nothing ; 

  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_N_CONNECT_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_N_CONNECT_RESPONSE_EVENT] = 
                            sccp_conn_start_n_conn_res ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_N_DISCONNECT_REQ_EVENT] = 
                            sccp_conn_start_n_disc_req ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_REQUEST_TYPE_1_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_REQUEST_TYPE_2_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_N_RESET_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_N_RESET_RESPONSE_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_N_DATA_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_N_EXP_DATA_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_CR_EVENT] = 
                            sccp_conn_start_comm_func ;   
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_CC_EVENT] = 
                            sccp_conn_start_cc ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_CREF_EVENT] = 
                            sccp_conn_start_cref ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_RLSD_EVENT] = 
                            sccp_conn_start_rlsd ;		
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_RLC_EVENT] = 
                            sccp_conn_start_comm_func ;	
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_RSR_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_RSC_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_ROUTE_FAIL_EVENT] = 
                            sccp_conn_start_routefail ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_DT1_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_DT2_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_AK_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_IT_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_ED_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_EA_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_ERR_EVENT] = 
                            sccp_conn_start_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_CONNEST_TIME_OUT] = 
                            sccp_conn_start_t_connest_tmout ;
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_IAR_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_IAS_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_REL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_REPREL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_INT_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_GAURD_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_RESET_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_REASSEMBLY_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_START][SCCP_T_FREEZE_TIME_OUT] = 
                            sccp_do_nothing ; 

  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_N_CONNECT_REQUEST_EVENT] =
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_N_CONNECT_RESPONSE_EVENT]=
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_N_DISCONNECT_REQ_EVENT]= 
                            sccp_conn_estab_n_disc_req ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_REQUEST_TYPE_1_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_REQUEST_TYPE_2_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_N_RESET_REQUEST_EVENT] = 
                            sccp_conn_estab_n_reset_req ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_N_RESET_RESPONSE_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_N_DATA_REQUEST_EVENT] = 
                            sccp_conn_estab_n_data_req ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_N_EXP_DATA_REQUEST_EVENT]=
                            sccp_conn_estab_n_expdata_req ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_CR_EVENT] = 
                            sccp_do_nothing ; 



  /* To fix SPR 1338: ITU-T specifications */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {

  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_CC_EVENT] = 
                            sccp_conn_estab_comm_func_itu ;       

  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_CREF_EVENT] = 
                            sccp_conn_estab_comm_func_itu ;      

  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_RLC_EVENT] = 
                            sccp_conn_estab_comm_func_itu ;     

  }
#endif

  /* To fix SPR 1338: ANSI specifications */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {

  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_CC_EVENT] = 
                            sccp_conn_estab_comm_func_ansi ;  

  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_CREF_EVENT] = 
                            sccp_conn_estab_comm_func_ansi ; 

  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_RLC_EVENT] = 
                            sccp_conn_estab_comm_func_ansi ;

  }
#endif

  /* SPR GR 
   * The IT and ERR event handling comply with specification texts */
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_IT_EVENT] = 
                            sccp_conn_estab_it ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_ERR_EVENT] = 
                            sccp_conn_estab_err ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_ROUTE_FAIL_EVENT] = 
                            sccp_conn_estab_routefail ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_RLSD_EVENT] = 
                            sccp_conn_estab_rlsd ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_RSR_EVENT] = 
                            sccp_conn_estab_rsr ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_RSC_EVENT] = 
                            sccp_conn_estab_rsc ;                 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_DT1_EVENT] = 
                            sccp_conn_estab_dt1 ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_DT2_EVENT] = 
                            sccp_conn_estab_dt2 ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_AK_EVENT] = 
                            sccp_conn_estab_ak ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_ED_EVENT] = 
                            sccp_conn_estab_ed ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_EA_EVENT] = 
                            sccp_conn_estab_ea ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_CONNEST_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_IAR_TIME_OUT] = 
                            sccp_conn_estab_t_iar_tmout ;
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_IAS_TIME_OUT] = 
                            sccp_conn_estab_t_ias_tmout ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_REL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_REPREL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_INT_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_GAURD_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_RESET_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_REASSEMBLY_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_ESTABLISHED][SCCP_T_FREEZE_TIME_OUT] = 
                            sccp_do_nothing ; 

  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_N_CONNECT_REQUEST_EVENT] =
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_N_CONNECT_RESPONSE_EVENT]=
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_N_DISCONNECT_REQ_EVENT]= 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_REQUEST_TYPE_1_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_REQUEST_TYPE_2_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_N_RESET_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_N_RESET_RESPONSE_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_N_DATA_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_N_EXP_DATA_REQUEST_EVENT]=
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_CR_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_CC_EVENT] = 
                            sccp_conn_closing_comm_func ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_CREF_EVENT] = 
                            sccp_conn_closing_comm_func ;
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_RLSD_EVENT] = 
                            sccp_conn_closing_rlc_rlsd_err ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_RLC_EVENT] = 
                            sccp_conn_closing_rlc_rlsd_err ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_RSR_EVENT] = 
                            sccp_conn_closing_comm_func ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_RSC_EVENT] = 
                            sccp_conn_closing_comm_func ;

/* To fix SPR 1338: ITU-T specifications */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_ROUTE_FAIL_EVENT] = 
                            sccp_conn_closing_comm_func ; 	     
  }
#endif 

  /* To fix SPR 1338: ANSI specifications */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_ROUTE_FAIL_EVENT] = 
                            sccp_conn_closing_rlc_rlsd_err ; 
  }
#endif

  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_DT1_EVENT] = 
                            sccp_conn_closing_comm_func ; 	     
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_DT2_EVENT] = 
                            sccp_conn_closing_comm_func ; 	     
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_AK_EVENT] = 
                            sccp_conn_closing_comm_func ; 	     
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_IT_EVENT] = 
                            sccp_conn_closing_comm_func ; 	     
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_ED_EVENT] = 
                            sccp_conn_closing_comm_func ; 	     
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_EA_EVENT] = 
                            sccp_conn_closing_comm_func ;
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
  if ((COMPARE_ANSI) || (COMPARE_BCGR))
  {
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_ERR_EVENT] =
                            sccp_conn_closing_comm_func ;
  }
#endif

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
  {
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_ERR_EVENT] = 
                            sccp_conn_closing_rlc_rlsd_err ; 
  }
#endif
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_CONNEST_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_IAR_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_IAS_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_REL_TIME_OUT] = 
                            sccp_conn_closing_t_rel_tmout ;
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_REPREL_TIME_OUT] = 
                            sccp_conn_closing_t_reprel_tmout ;
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_INT_TIME_OUT] = 
                            sccp_conn_closing_t_int_tmout ;
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_GAURD_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_RESET_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_REASSEMBLY_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSING][SCCP_T_FREEZE_TIME_OUT] = 
                            sccp_do_nothing ; 

  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_N_CONNECT_REQUEST_EVENT] =
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_N_CONNECT_RESPONSE_EVENT]=
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_N_DISCONNECT_REQ_EVENT]= 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_REQUEST_TYPE_1_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_REQUEST_TYPE_2_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_N_RESET_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_N_RESET_RESPONSE_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_N_DATA_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_N_EXP_DATA_REQUEST_EVENT]=
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_CR_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_CC_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_CREF_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_RLSD_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_RLC_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_RSR_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_RSC_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_ROUTE_FAIL_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_DT1_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_DT2_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_AK_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_IT_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_ED_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_EA_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_ERR_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_CONNEST_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_IAR_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_IAS_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_REL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_REPREL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_INT_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_GAURD_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_RESET_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_REASSEMBLY_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_CLOSED][SCCP_T_FREEZE_TIME_OUT] = 
                            sccp_conn_closed_t_freeze_tmout ;

  /** SPR # 4051 Fix Start */
  /* According to Table B.4/Q.714 and Table B-4/T1.112.4, If the substate is
  ** Outgoing, a RSR must be sent instead of just discarding an unexpected 
  ** message from peer */

  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_N_CONNECT_REQUEST_EVENT] =
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_N_CONNECT_RESPONSE_EVENT]=
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_N_DISCONNECT_REQ_EVENT]= 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_REQUEST_TYPE_1_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_REQUEST_TYPE_2_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_N_RESET_REQUEST_EVENT] = 
                            sccp_conn_reset_n_reset_req ;
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_N_RESET_RESPONSE_EVENT] = 
                            sccp_conn_reset_n_reset_res ;
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_N_DATA_REQUEST_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_N_EXP_DATA_REQUEST_EVENT]=
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_CR_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_CC_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_CREF_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_RLSD_EVENT] = 
                            sccp_conn_reset_rlsd ;
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_RLC_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_RSR_EVENT] = 
                            sccp_conn_reset_rsr ;
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_RSC_EVENT] = 
                            sccp_conn_reset_rsc ;
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_ROUTE_FAIL_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_DT1_EVENT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_DT2_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_AK_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_IT_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_ED_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_EA_EVENT] = 
                            sccp_conn_reset_rpe ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_ERR_EVENT] = 
                            sccp_conn_reset_rpe ;
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_CONNEST_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_IAR_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_IAS_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_REL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_REPREL_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_INT_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_GAURD_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_RESET_TIME_OUT] = 
                            sccp_conn_reset_t_reset_tmout ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_REASSEMBLY_TIME_OUT] = 
                            sccp_do_nothing ; 
  sccp_co_func_ptr_table [SCCP_CONN_RESET][SCCP_T_FREEZE_TIME_OUT] = 
                            sccp_do_nothing ; 

  /** SPR # 4051 Fix End **/
}

#else

/*****************************************************************************
**	This extern declaration is required as BCC reports error if the 
** source file is empty after preprocessing. This declaration enables compilation
** without SCCP_INCLUDE_CO_SERVICE flag using BCC.
**
*****************************************************************************/

extern return_t sccp_co_dummy _ARGS_ ((void));

#endif
