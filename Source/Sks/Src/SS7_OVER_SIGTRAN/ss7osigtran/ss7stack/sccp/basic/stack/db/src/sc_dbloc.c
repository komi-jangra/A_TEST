/***************************************************************************
**  FILE NAME:
**      sc_dbloc.c
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
** 21/11/03  knaveen           ---------      SPR 13075 Fixed.
** 26/02/04  Hitesh Sharma     ---------      SPR 13263 Fixed.
**
**  Copyright 1998, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

/*****************************************************************************
**      FUNCTION :
**          finds a signaling point
******************************************************************************
**
**      DESCRIPTION :
**          calls the hash locate function to locate the signaling point
**
**      NOTE :
**
*****************************************************************************/

sp_entry_t *
sccp_db_find_sp
#ifdef ANSI_PROTO
	(nw_id_t nw_id, pc_t pc)
#else
	(nw_id, pc)
	 nw_id_t 	nw_id;
	 pc_t 		pc;
#endif
{
	return sccp_db_locate_sp_hash_list (nw_id, pc);
}

/*****************************************************************************
**      FUNCTION :
**         finds a subsystem of a signaling point
******************************************************************************
**
**      DESCRIPTION :
**         calls function to do linear search of the subsystem list
**
**      NOTE :
**
*****************************************************************************/

ss_entry_t *
sccp_db_find_ss
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp, U8bit ssn)
#else
	(p_sp, ssn)
	 sp_entry_t 	*p_sp;
	 U8bit 		ssn;
#endif
{
	return sccp_db_find_ss_linear (p_sp, ssn);
}

/*****************************************************************************
**      FUNCTION :
**        finds a sp given its id
******************************************************************************
**
**      DESCRIPTION :
**        checks if sp_id is configured and the returns SS7_SUCCESS if sp is
**        configured
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_find_sp_from_id
#ifdef ANSI_PROTO
	(U32bit sp_id,
	 sp_entry_t **p_p_sp,
	 error_t * p_ecode)
#else
	(sp_id, p_p_sp, p_ecode)
	 U32bit 	sp_id;
	 sp_entry_t 	**p_p_sp;
	 error_t 	*p_ecode;
#endif
{
/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
	if ( ! IS_SPID_VALID(sp_id)) 
/*	if ( !((sp_id) < MAX_SP))	*/
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */
	{
		*p_ecode = ESCCP_INVALID_SP_ID;
		return SS7_FAILURE;
	}

	*p_p_sp = GET_SP_FROM_ID(sp_id);

	if ( ! IS_SP_CONFIGURED(*p_p_sp))
	{
		*p_ecode = ESCCP_INVALID_SP_ID;
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         finds subsystem from its id
******************************************************************************
**
**      DESCRIPTION :
**        checks if the id is valid and configured and returns the subsystem
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_find_ss_from_id
#ifdef ANSI_PROTO
	(U32bit ss_id, ss_entry_t ** p_p_ss, error_t * p_ecode)
#else
	(ss_id, p_p_ss, p_ecode)
	 U32bit 	ss_id;
	 ss_entry_t 	**p_p_ss;
	 error_t 	*p_ecode;
#endif
{
	if ( ! IS_SSID_VALID(ss_id))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	*p_p_ss = GET_SS_FROM_ID(ss_id);

	if ( ! IS_SS_CONFIGURED(*p_p_ss))
	{
		*p_ecode = ESCCP_INVALID_SS_ID;
		return SS7_FAILURE;
	}

	return SS7_SUCCESS;
}

/*****************************************************************************
**      FUNCTION :
**         does a linear search of the subsystem list
******************************************************************************
**
**      DESCRIPTION :
**         goes thru the list of subsystem of  a signaling point and
**         returns it if it exists else SS7_NULL
**
**      NOTE :
**
*****************************************************************************/

ss_entry_t *
sccp_db_find_ss_linear
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp, U8bit ssn)
#else
	(p_sp, ssn)
	 sp_entry_t 	*p_sp;
	 U8bit 		ssn;
#endif
{
	ss_entry_t * p_ss;
	U32bit i;

	p_ss = GET_SS_LIST_IN_SP(p_sp);
	for (i=0; i < p_sp->num_ss; i++, p_ss = GET_NEXT_SS(p_ss))
	{
		if (ssn == GET_SS_SSN(p_ss))
			return p_ss;
	}

	return SS7_NULL;
}


/* Function added for GR */
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
 
/*****************************************************************************
**      FUNCTION :
**         Locates all signalling points that are members of a given cluster.
******************************************************************************
**
**      DESCRIPTION :
**         This function goes through all SPs to find a list of SPs with a
**         given network and cluster id. It returns the number of SPs which
**         are members of the cluster.
**
**      NOTE :
**
*****************************************************************************/
 
 
U32bit
sccp_db_find_cluster_list
#ifdef ANSI_PROTO
        (scmg_info_t    * p_info, 
         sp_id_t        * p_sp_list)
#else
        (p_info, p_sp_list)
        scmg_info_t     * p_info;
        sp_id_t         * p_sp_list;
#endif
{
        return (sccp_db_locate_cluster_hash_list(p_info, p_sp_list));
}
 
#endif
