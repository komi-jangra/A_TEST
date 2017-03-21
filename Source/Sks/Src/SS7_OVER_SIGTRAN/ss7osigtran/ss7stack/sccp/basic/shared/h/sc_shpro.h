/***************************************************************************
**  FILE NAME:
**      sc_shpro.h
**
****************************************************************************
**
**  FUNCTION:
**      
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  12May'98 Sriganesh. Kini   -----  Original
**  22Jul'02 Suyash Tripathi   -----  SPR # 9302
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/


#ifndef _SC_SHPRO_H_
#define _SC_SHPRO_H_

#include "sc_shgl.h"

void sccp_api_detail_trace
	_ARGS_ ((U8bit * p_api));

/* SPR 9302 - Fix Start */
#ifndef __FLAG_SCCP_DBG_HANDLE_FLAG__
#define __FLAG_SCCP_DBG_HANDLE_FLAG__
/* SPR 9302 - Fix End   */
void sccp_dbg_handle_sm_cmd
	_ARGS_ ((U8bit * p_api));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

/* SPR 9302 - Fix Start */
#ifndef __FLAG_SCCP_ERR_HANDLER_FLAG__
#define __FLAG_SCCP_ERR_HANDLER_FLAG__
/* SPR 9302 - Fix End   */
void sccp_err_handler
	_ARGS_ ((error_t error, U32bit error_type, U8bit error_level));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */


/* SPR 9302 - Fix Start */
#ifndef __FLAG_SCCP_SM_CMD_STD_RESP_FLAG__
#define __FLAG_SCCP_SM_CMD_STD_RESP_FLAG__
/* SPR 9302 - Fix End   */
void sccp_sm_cmd_std_resp
	_ARGS_ ((U8bit * p_api, return_t ret_val, U8bit param,
	             Boolean put_param, error_t ecode));
/* SPR 9302 - Fix Start */
#endif
/* SPR 9302 - Fix End   */

#endif /* _SC_SHPRO_H_ */
