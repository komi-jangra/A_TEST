/***************************************************************************
**  FILE NAME:
**      sc_bcast.h
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
**  20May2002 Salil K Agrawal         Fixed SPR # 8744
**  24Feb2000 Ramu Kandula            Fixed SPR # 2695
**  12May'98 Sriganesh. Kini   -----  Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_BCAST_H_
#define _SC_BCAST_H_

#include "sc_api.h"

#define LBCS_UIS	SCCP_USER_IN_SERVICE
#define LBCS_UOS	SCCP_USER_OUT_OF_SERVICE

#define LBCS_RESUME			SCCP_USER_OUT_OF_SERVICE + 1
#define LBCS_STATUS			SCCP_USER_OUT_OF_SERVICE + 2
#define LBCS_PAUSE			SCCP_USER_OUT_OF_SERVICE + 3
#define LBCS_SCCP_ACCESSIBLE		SCCP_USER_OUT_OF_SERVICE + 4
#define LBCS_SCCP_INACCESSIBLE		SCCP_USER_OUT_OF_SERVICE + 5

/** SPR # 2695 Fix Start **/
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
#define LBCS_RIL			SCCP_USER_OUT_OF_SERVICE + 6
#endif
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
#define LBCS_SP_CONG		SCCP_USER_OUT_OF_SERVICE + 7
#endif
/** SPR # 2695 Fix End **/

#define BCST_SSA	1
#define BCST_SSP	2

/* SPR # 8744 starts */
int sccp_is_local_sp(sp_entry_t * p_sp) ;
/* SPR # 8744 ends */

#endif /* _SC_BCAST_H_ */
