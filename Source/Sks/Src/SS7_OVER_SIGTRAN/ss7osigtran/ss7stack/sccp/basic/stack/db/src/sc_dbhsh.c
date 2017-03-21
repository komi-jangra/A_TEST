/***************************************************************************
**  FILE NAME:
**      sc_dbhsh.c
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
**  -------  ----------------  --------------  ----------------------------
** 24Jul2002 Salil Agrawal     SPR # 9341       Fixed
** 14Feb2000 Ramu Kandula      SPR # 2419       Merged the fix from Rel 4.21
**  3/6/98   Sriganesh. Kini   HSS:208000008	Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

#include "sc_dbhsh.h"

sccp_db_hash_tbl_t sccp_db_hash_tbl[HASH_TBL_SIZE];

/*****************************************************************************
**      FUNCTION :
**         initialises hash table
******************************************************************************
**
**      DESCRIPTION :
**         sets the number of hash entries for the hash bucket to zero.
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_init_hash_table
#ifdef ANSI_PROTO
	(void)
#else
	()
#endif
{
	sccp_db_hash_tbl_t * p_hash_tbl_entry;
	U32bit i;

	p_hash_tbl_entry = &sccp_db_hash_tbl[0];
	for (i=0; i < HASH_TBL_SIZE; i++, p_hash_tbl_entry++)
	{
		p_hash_tbl_entry->num_hash_entries = 0;
	}
}

/*****************************************************************************
**      FUNCTION :
**         inserts signaling point in the hash bucket
******************************************************************************
**
**      DESCRIPTION :
**         depending on the hash value it inserts the signaling point
**         at the head of the list of signaling points
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_insert_sp_hash_list
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	 sp_entry_t *p_sp;
#endif
{
	U32bit hash_key;
	U8bit hash_index;
	sccp_db_hash_tbl_t * p_hash_entry;

	hash_key = sccp_db_get_hash_key (p_sp->nw_id, p_sp->pc);

	hash_index = (U8bit)(hash_key % HASH_TBL_SIZE);
	p_hash_entry = &sccp_db_hash_tbl[hash_index];

	p_sp->next_sp_id = p_hash_entry->sp_id;
	p_hash_entry->sp_id = GET_ID_FROM_SP(p_sp);
	p_hash_entry->num_hash_entries++;
}

/*****************************************************************************
**      FUNCTION :
**          deletes a signaling point from hash list
******************************************************************************
**
**      DESCRIPTION :
**         goes thru the linear list of singnaling points and deletes it
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_delete_sp_hash_list
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	 sp_entry_t *p_sp;
#endif
{
	U32bit hash_key, i;
	U8bit hash_index;
	sccp_db_hash_tbl_t * p_hash_entry;
	sp_entry_t * p_tmp_sp;

	hash_key = sccp_db_get_hash_key (GET_SP_NW_ID(p_sp), GET_SP_PC(p_sp));
	hash_index = (U8bit)(hash_key % HASH_TBL_SIZE);
	p_hash_entry = &sccp_db_hash_tbl[hash_index];

	if (! (p_hash_entry->sp_id == GET_ID_FROM_SP(p_sp)))
	{
		p_tmp_sp = GET_SP_FROM_ID(p_hash_entry->sp_id);
		for (i=1; i < p_hash_entry->num_hash_entries; i++)
		{
			if (p_sp == GET_NEXT_SP(p_tmp_sp))
			{
				SET_NEXT_SP (p_tmp_sp, GET_NEXT_SP(p_sp));
				break;
			}
			p_tmp_sp = GET_NEXT_SP(p_tmp_sp);
		}
	}
	else
	{
		p_hash_entry->sp_id = GET_ID_FROM_SP(GET_NEXT_SP(p_sp));
	}

	p_hash_entry->num_hash_entries--;
}

/*****************************************************************************
**      FUNCTION :
**         locates a signaling point in the hash table
******************************************************************************
**
**      DESCRIPTION :
**         depending on hash index does a linear search on the hash bucket
**         list
**
**      NOTE :
**
*****************************************************************************/

sp_entry_t *
sccp_db_locate_sp_hash_list
#ifdef ANSI_PROTO
	(nw_id_t nw_id, pc_t pc)
#else
	(nw_id, pc)
	 nw_id_t 	nw_id;
	 pc_t 		pc;
#endif
{
	U32bit hash_key, i;
	U8bit hash_index;
	sccp_db_hash_tbl_t * p_hash_entry;
	sp_entry_t * p_sp;

	hash_key = sccp_db_get_hash_key (nw_id, pc);
	hash_index = (U8bit)(hash_key % HASH_TBL_SIZE);
	p_hash_entry = &sccp_db_hash_tbl[hash_index];

	p_sp = GET_SP_FROM_ID(p_hash_entry->sp_id);

	for (i=0; i < p_hash_entry->num_hash_entries;
	     i++, p_sp = GET_NEXT_SP(p_sp))
	{
		if ((GET_SP_NW_ID(p_sp) == nw_id) && (GET_SP_PC(p_sp) == pc))
		{
			return p_sp;
		}
	}

	return SS7_NULL;
}

/*****************************************************************************
**      FUNCTION :
**         computes hash key
******************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
*****************************************************************************/

U32bit
sccp_db_get_hash_key
#ifdef ANSI_PROTO
	(U8bit nw_id, pc_t pc)
#else
	(nw_id, pc)
	 U8bit 	nw_id;
	 pc_t 	pc;
#endif
{
	/* SPR 9302 - Fix Start */
	U32bit hash_key = 0;
	U32bit pc_size = 0; /** SPR # 2419 fix **/
	/* SPR 9302 - Fix End   */

	/** SPR # 2419 fix START **/
    
/* start # 9341 */
#ifdef SCCP_CHINESE
	if(COMPARE_CHINESE)
	{
		pc_size = ANSI_24_BIT_PC;
	}
#endif 
/* #else */
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
	if ( (COMPARE_ITU) || COMPARE_ETSI)
	{
		pc_size = ITU_T_14_BIT_PC;
	}
	else if(COMPARE_JAPANESE)
	{
		pc_size = JAPANESE_16_BIT_PC;
	}
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR) 
	if (COMPARE_ANSI || COMPARE_BCGR)
	{
		pc_size = ANSI_24_BIT_PC;
	}
#endif
/* #endif */
/* end spr # 9341 */

    /** SPR # 2419 fix Cond. **/


	switch (pc_size) /** SPR # 2419 fix END **/
	{
		case ITU_T_14_BIT_PC:
			hash_key = (nw_id << ITU_T_PC_NUM_BITS) |
		   	        (pc & ITU_T_14_BIT_PC_MASK);
			break;

		case JAPANESE_16_BIT_PC:
			hash_key = (nw_id << JAPANESE_PC_NUM_BITS) |
		   	        (pc & JAPANESE_16_BIT_PC_MASK);
			break;

		case ANSI_24_BIT_PC:
			hash_key = (nw_id << ANSI_PC_NUM_BITS) |
			           (pc & ANSI_24_BIT_PC_MASK);
			break;

		default:
			break;
	}

	return hash_key;
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
sccp_db_locate_cluster_hash_list
#ifdef ANSI_PROTO
        (scmg_info_t    * p_info,
         sp_id_t        * p_sp_list)
#else
        (p_info, p_sp_list)
        scmg_info_t     * p_info; 
        sp_id_t         * p_sp_list;
#endif
{
        U32bit          num_sp = 0, hash_entry;
        U8bit           hash_index;
        sp_entry_t      *p_sp;
        sccp_db_hash_tbl_t *p_hash_entry;
        sp_id_t         *local_sp_list;
 
        local_sp_list = p_sp_list;
        for (hash_index = 0; hash_index < HASH_TBL_SIZE; hash_index++)
        {
                p_hash_entry = &sccp_db_hash_tbl[hash_index];
                p_sp = GET_SP_FROM_ID(p_hash_entry->sp_id);
 
                for (hash_entry = 0; hash_entry < p_hash_entry->num_hash_entries;
                                        p_sp = GET_NEXT_SP(p_sp), hash_entry++)
                {
                        if ((GET_SP_CLUSTER(p_sp) == p_info->cluster) &&
                                (GET_SP_NW_ID(p_sp) == p_info->nw_id))
                        {
                                local_sp_list[num_sp++] = GET_ID_FROM_SP(p_sp);
                        }
                }
        }
        return (num_sp);
}
#endif 

