/***************************************************************************
**
**  FILE NAME:
**      dsccp_stat.c
**
****************************************************************************
**
**  FUNCTION:
**      Contains functions related to DSCCP  stats processing 
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  24October 2001 Prateek Bidwalkar            Original
**  19Jun 2002     Suyash  Tripathi             SPR # 8985
**  Copyright 2001, Hughes Software Systems
**
***************************************************************************/

#include "sc_stgl.h"
#include "dsccp_stats.h"

#ifdef DISTRIBUTED_SCCP 

/* define a variable to count the mate api's */
dsccp_stats_api_t    dsccp_stats_api;

/* define a variable to keep track of SCLC events */
dsccp_stats_sclc_t	 dsccp_stats_sclc;

/* define a variable to keep track of SCLC events */
dsccp_stats_scoc_t 	 dsccp_stats_scoc;

void dsccp_retrieve_stats (U8bit * p_api);
/*****************************************************************************
**      FUNCTION :
**         dsccp_retrieve_stats
**
******************************************************************************
**
**      DESCRIPTION :
**            gets internal stats
**
**      NOTE :
**
*****************************************************************************/
#ifdef DSCCP_STATS_ENABLED
void
dsccp_retrieve_stats
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	 U8bit * p_api;
#endif
{
/* SPR 8985 - Fix Start */
/* This line of code is added just to remove the "unused parameter" warning */
	p_api = 0;
/* SPR 8985 - Fix End   */
}
#endif

#endif /* DISTRIBUTED_SCCP && DSCCP_STATS_ENABLED*/
