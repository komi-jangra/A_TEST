/***************************************************************************
**
**  FILE NAME:
**      dsccp_scoc.c
**
****************************************************************************
**
**  FUNCTION:
**		Contains functions for processing the N-DISCONNECT req from mate SCCP instances
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24August 2001 Pawanish Modi            Original
**  24October2001 Prateek Bidwalkar        Fixed SPR 6750
**  Copyright 2001, Hughes Software Systems
**
***************************************************************************/

/* SPR # 6750 Fix Start */
#include "sc_stgl.h"
/* SPR # 6750 Fix End */

#ifdef DISTRIBUTED_SCCP
#include "dsccp.h"
/* SPR # 6750 Fix Start */
#if 0
#include "sc_stgl.h"
#endif
/* SPR # 6750 Fix End */
#include "dsccp_proc.h"



/***************************************************************************
**
**      FUNCTION :
**      dsccp_handle_mate_n_disc_req
**       
****************************************************************************
**
**      DESCRIPTION : This function is called from the sccp_process_mesg when a 
**      N-DISCONNECT REQ message from mate is received. When a DSCCP instance
**	  receives a N-DISCONNECT request from a user and a CCB is not found,
**	  it broadcasts the N-DISCONNECT request to other mate DSCCP instances.
**	  When a DSCCP instance receives a N-DISCONNECT request from a mate
**	  instance, it seraches for CCB. If CCB is found, then the request
**	  is processed else the N-DISCONNECT req. is ignored
**
**      NOTE :
**
***************************************************************************/


return_t 
dsccp_handle_mate_n_disc_req
#ifdef ANSI_PROTO
	(U8bit * p_api, error_t *p_ecode)
#else
	(p_api, p_ecode)
	U8bit *p_api;
	error_t *p_ecode;
#endif
{
	U8bit *p_buffer;
	msg_info_t  info ;
	return_t result;
	msg_info_t  *p_info ;


	p_buffer = p_api + DSCCP_DATA_OFFSET;

  	info.p_api = p_buffer ;
	info.event = SCCP_N_DISCONNECT_REQ_EVENT;

	info.dsccp_mate_api = SS7_TRUE;

/* This flag indicates that the API is received from mate. If a CCB is not found, discard the API and do not broadcast to other DSCCP instances **/

	p_info = &info;

	result = sccp_handle_co_mesg(p_info, p_ecode);

	return result;
}
#else /* DISTRIBUTED_SCCP */

/*****************************************************************************
**  This extern declaration is required as ANSI C does not allow an empty 
**  source file. This declaration enables compilation without DISTRIBURTED_SCCP 
**  flag .
*****************************************************************************/

extern return_t dsccp_dummy _ARGS_ ((void));



#endif /* end DISTRIBUTED_SCCP */
