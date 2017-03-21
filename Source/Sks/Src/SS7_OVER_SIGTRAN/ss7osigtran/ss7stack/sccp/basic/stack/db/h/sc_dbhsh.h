/***************************************************************************
**  FILE NAME:
**      sc_dbhsh.h
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
**           Sriganesh. Kini   -----  Original
**  21Nov03  knaveen           -----  SPR 13075 
**  27Feb04  Hitesh Sharma     -----  SPR 13263 
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_DBHSH_H_
#define _SC_DBHSH_H_

/* Start Spr 13075 Fix */
/* Start Spr 13263 Fix */
#if 0
#if (MAX_SP < 100)
	#define HASH_TBL_SIZE 11
#elif (MAX_SP < 500)
	#define HASH_TBL_SIZE 31
#elif (MAX_SP < 1000)
	#define HASH_TBL_SIZE 59
#else
	#define HASH_TBL_SIZE 101
#endif
#endif
#define HASH_TBL_SIZE 101
/* Stop Spr 13263 Fix */
/* Stop Spr 13075 Fix */


typedef struct
{
	U32bit num_hash_entries;
	sp_id_t sp_id;
} sccp_db_hash_tbl_t;

#endif
