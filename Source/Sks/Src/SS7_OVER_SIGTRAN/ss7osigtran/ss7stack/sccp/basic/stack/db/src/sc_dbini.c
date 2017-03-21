/***************************************************************************
**  FILE NAME:
**      sc_dbini.c
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   		REASON
**  -------  ----------------  -------------  -----------------------------
**   3/6/98  Sriganesh. Kini   HSS:20800008   Original
**   24/2/04 Hitesh Sharma                      Fixed SPR No: 13263
**   29/7/04 Hitesh Sharma			Fixed SPR No: 13696 CSR No: 1-1465199
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

sccp_db_t sccp_db;
/* Fix for SPR No: 13263 start */
U32bit SIZEOF_C_SS_SP_ARRAY = 0; 
/* Fix for SPR No: 13263 end */

/*****************************************************************************
**      FUNCTION :
**             initializes the database
******************************************************************************
**
**      DESCRIPTION :
**             sets all signaling points and subsystem as not configured
**             initializes the css csp list to zero.
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_init
#ifdef ANSI_PROTO
	(void)
#else
	()
#endif
{
	/* Fix for SPR No: 13263 start */

        sccp_db.sp = (sp_entry_t *)sccp_malloc( sizeof(sp_entry_t) * MAX_SP ) ;

	if(sccp_db.sp == SS7_NULL)
    	{
        	SC_A_TRC (("SCCP::INIT: malloc failure\n"));
        	return SS7_FAILURE;
    	}
	
        sccp_db.ss = (ss_entry_t *)sccp_malloc( sizeof(ss_entry_t) * MAX_SS ) ;

	if(sccp_db.ss == SS7_NULL)
	{
        	SC_A_TRC (("SCCP::INIT: malloc failure\n"));
        	return SS7_FAILURE;
    	}

        SIZEOF_C_SS_SP_ARRAY = SIZEOF_SP_ID_T * MAX_CSP + SIZEOF_SS_ID_T * MAX_CSS ;
        sccp_db.conc_ss_sp_list =  (U8bit *)sccp_malloc( SIZEOF_C_SS_SP_ARRAY ) ;

	if(sccp_db.conc_ss_sp_list == SS7_NULL)
	{
                SC_A_TRC (("SCCP::INIT: malloc failure\n"));
                return SS7_FAILURE;
        }
/* Fix for SPR No: 13696 start */
        ss7_mem_zero((void *) (sccp_db.sp), (sizeof(sp_entry_t) * MAX_SP));
        ss7_mem_zero((void *) (sccp_db.ss), (sizeof(ss_entry_t) * MAX_SS));
        ss7_mem_zero((void *) (sccp_db.conc_ss_sp_list), sizeof(SIZEOF_C_SS_SP_ARRAY));
/* Fix for SPR No: 13696 stop */
	/* Fix for SPR No: 13263 end */


	sccp_db.end_conc_ss_sp = 0;

	sccp_db_init_hash_table ();
	return SS7_SUCCESS;
}
