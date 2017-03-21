/******************************************************************************
**      FUNCTION:
**
*******************************************************************************
**
**      FILE NAME:
**          sc_disp.h
**
**      DESCRIPTION:
**         This file contains prototypes of functions to send display 
**		   information to the SM
**
**       DATE          NAME           REFERENCE            REASON
**       ----          ----           ---------            ------
**
**      22Oct01    Prateek Bidwalkar                      Original
**      19Dec01    Ashish Sawalkar                      Fixed SPR 7490 
**
**
**      Copyright 2001, Hughes Software Systems, Inc.
**
******************************************************************************/

#ifndef  _SC_DISP_H_
#define  _SC_DISP_H_

/* SPR # 6566 : Fix Start */
/* States for subsystem status */
#define  SCCP_SM_SS_CONFIGURED  0x80
#define  SCCP_SM_SS_REGISTERED  0x40
#define  SCCP_SM_SS_ALLOWED     0x20
/* SPR # 6566 : Fix End */

return_t
sccp_display_parse_ss_status_api
	_ARGS_((U8bit *p_api, pc_t *pc, U8bit *p_ssn));

/* SPR 7490 : Start Fix */
return_t
sccp_display_parse_sp_status_api
	_ARGS_((U8bit *p_api, pc_t *pc));
/* SPR 7490 : End Fix */

#endif  /* _SC_DISP_H_ */
