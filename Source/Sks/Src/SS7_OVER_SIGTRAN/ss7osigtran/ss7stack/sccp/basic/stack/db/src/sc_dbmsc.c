/***************************************************************************
**  FILE NAME:
**      sc_dbmsc.c
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#  			 REASON
**  -------  ----------------  --------------------------------------------
**  26/2/04  Hitesh Sharma                  Fixed SPR # 13263
**  21/11/03 Hitesh Sharma                  Fixed SPR # 13006 CSR No: 1-908332
**  08/8/02  Prateek Bidwalkar              Fixed SPR # 9502
**  24Jul2002 Salil Agrawal    SPR # 9341   Fixed SPR 
**  17/7/02  Prateek Bidwalkar              Fixed SPR # 9286
**                             SPR # 6307	Fixed SPR 
**  14Feb2000 Ramu Kandula     SPR # 2419        Merged fix from Rel 4.21
**   3/6/98  Sriganesh. Kini   HSS:20800008         Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#include "sc_stgl.h"

/*****************************************************************************
**      FUNCTION :
**
******************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
*****************************************************************************/

#if 0
return_t
sccp_db_check_nw_id
#ifdef ANSI_PROTO
	(U8bit nw_id, error_t * p_ecode)
#else
	(nw_id, p_ecode)
	 U8bit 		nw_id;
	 error_t 	*p_ecode;
#endif
{
	if (nw_id >= MAX_NW_ID)
	{
		*p_ecode = ESCCP_INVALID_NW_ID;
		return SS7_FAILURE;
	}

#if 0
	/* Check if the network is already configured */

#endif

	return SS7_SUCCESS;
}
#endif

/*****************************************************************************
**      FUNCTION :
**	       	Check pc value depending on the configured standard
******************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
*****************************************************************************/

return_t
sccp_db_check_pc
#ifdef ANSI_PROTO
	(U32bit pc, error_t * p_ecode)
#else
	(pc, p_ecode)
	 U32bit 	pc;
	 error_t 	*p_ecode;
#endif
{
	return_t ret_val = SS7_SUCCESS;

	/** The following code already covers the modification for
	*** SPR # 2419 done in Rel 4.21
	*** So the code for SPR # 2419 fix from Rel 4.21 need not be merged 
	*** into the main branch
	**/

        /* Compare the PC size depending on the standard */
/* spr # 9341 starts */
#if 0
/* #ifdef SCCP_CHINESE */
	if(COMPARE_CHINESE)
	{
                if (pc > ANSI_24_BIT_PC_MAX_VAL)
                {
                        *p_ecode = ESCCP_INVALID_PC_VALUE;
                        ret_val = SS7_FAILURE;
                }
	}
/* #else */
#endif 
		
#if defined (SCCP_ANSI) || defined (SCCP_BCGR) || defined (SCCP_CHINESE)
   	if ((COMPARE_ANSI) || (COMPARE_BCGR) || (COMPARE_CHINESE))
   	{
                if (pc > ANSI_24_BIT_PC_MAX_VAL)
                {
                        *p_ecode = ESCCP_INVALID_PC_VALUE;
                        ret_val = SS7_FAILURE;
                }
   	}
#endif
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI)
        if ( (COMPARE_ITU) || COMPARE_ETSI)
        {
			if (pc > ITU_T_14_BIT_PC_MAX_VAL)
			{
				*p_ecode = ESCCP_INVALID_PC_VALUE;
				ret_val = SS7_FAILURE;
			}
		}
		else if((COMPARE_JAPANESE) && (pc > JAPANESE_16_BIT_PC_MAX_VAL))
		{
			*p_ecode = ESCCP_INVALID_PC_VALUE;
			ret_val = SS7_FAILURE;
		} 
		
#endif
/* removed endif to fix spr 9341 */
/* end spr # 9341 */

#if 0
	switch (ITU_T_14_BIT_PC /*sccp_pc_size(nw_id)*/)
	{
		case ITU_T_14_BIT_PC:
			if (pc > ITU_T_14_BIT_PC_MAX_VAL)
			{
				*p_ecode = ESCCP_INVALID_PC_VALUE;
				ret_val = SS7_FAILURE;
			}

			break;

		case ANSI_24_BIT_PC:
			if (pc > ANSI_24_BIT_PC_MAX_VAL)
			{
				*p_ecode = ESCCP_INVALID_PC_VALUE;
				ret_val = SS7_FAILURE;
			}

		default:
			break;
	}
#endif

	return ret_val;
}

/*****************************************************************************
**      FUNCTION :
**         inserts a subsystem in the list of subsystems for a signaling point
******************************************************************************
**
**      DESCRIPTION :
**         
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_insert_ss_in_sp
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss, sp_entry_t * p_sp)
#else
	(p_ss, p_sp)
	 ss_entry_t 	*p_ss;
	 sp_entry_t 	*p_sp;
#endif
{
	SET_NEXT_SS (p_ss, GET_SS_LIST_IN_SP(p_sp));
	SET_SS_LIST_IN_SP (p_sp, p_ss);
	SET_NUM_SS_IN_SP (p_sp, GET_NUM_SS_IN_SP(p_sp) + 1);
}

/*****************************************************************************
**      FUNCTION :
**        checks if a subsystem is a concerned subsystem of another subsystem
******************************************************************************
**
**      DESCRIPTION :
**        goes thru the css list of all other subsystems and checks if
**        this subsystem is in it
**
**      NOTE :
**
*****************************************************************************/

Boolean
sccp_db_is_ss_conc
#ifdef ANSI_PROTO
	(ss_entry_t * p_css)
#else
	(p_css)
	 ss_entry_t *p_css;
#endif
{
	U32bit i, j;
	ss_entry_t * p_ss;
	U8bit * p_css_list;

	p_ss = GET_SS_FROM_ID (0);
	for (i=0; i < MAX_SS; i++, p_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_ss)) continue;

		if ( ! (GET_SS_NW_ID(p_ss) == GET_SS_NW_ID(p_css)))
			continue;

		p_css_list = GET_CSS_LIST(p_ss);
		for (j=0; j < GET_NUM_CSS(p_ss);
		     j++, p_css_list = GET_NEXT_CSS_FROM_LIST(p_css_list))
		{
			if (p_css == GET_CSS_FROM_LIST(p_css_list))
				return SS7_TRUE;
		}
	}

	return SS7_FALSE;
}

/*****************************************************************************
**      FUNCTION :
**        checks if this sp is a concerned sp of some signaling point
******************************************************************************
**
**      DESCRIPTION :
**        goes thru all the subsystems's concerned signaling points list and
**        checks if this sp is in it
**
**      NOTE :
**
*****************************************************************************/

Boolean
sccp_db_is_sp_conc
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	 sp_entry_t *p_sp;
#endif
{
	U32bit i, j;
	ss_entry_t * p_ss;
	U8bit * p_csp_list;

	p_ss = GET_SS_FROM_ID (0);
	for (i=0; i < MAX_SS; i++, p_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_ss)) continue;

		if ( ! (GET_SP_NW_ID(GET_SP_OF_SS(p_ss)) ==
		        GET_SP_NW_ID(p_sp)))
			continue;

		p_csp_list = GET_CSP_LIST(p_ss);
		for (j=0; j < GET_NUM_CSP(p_ss);
		     j++, p_csp_list = GET_NEXT_CSP_FROM_LIST(p_csp_list))
		{
			if (p_sp == GET_CSP_FROM_LIST(p_csp_list))
				return SS7_TRUE;
		}
	}

	return SS7_FALSE;
}


/*****************************************************************************
**      FUNCTION :
**        deletes all subsystems of this signaling point
******************************************************************************
**
**      DESCRIPTION :
**        goes thru the linear list of subsystems and calls function which
**        deletes a given subsystem
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_del_all_ss_of_sp
#ifdef ANSI_PROTO
	(sp_entry_t * p_sp)
#else
	(p_sp)
	 sp_entry_t *p_sp;
#endif
{
	U32bit i, num_ss;
	ss_entry_t * p_ss;
/* SPR # 9286 Fix Start */
	U8bit	del_css;
	error_t ecode;

	del_css = 1;
/* SPR # 9286 Fix End */

	num_ss = GET_NUM_SS_IN_SP(p_sp);

	for (i=0; i < num_ss; i++)
	{
		p_ss = GET_SS_LIST_IN_SP(p_sp);
/* SPR # 9286 Fix Start */
#if 0
		sccp_db_del_ss_from_sp(p_ss);
#endif
		sccp_db_del_ss(GET_ID_FROM_SS(p_ss), del_css, &ecode);
/* SPR # 9286 Fix End */
	}
}

/*****************************************************************************
**      FUNCTION :
**         deletes a subsystem from its signaling point
******************************************************************************
**
**      DESCRIPTION :
**        search for the subsystem from the list of subsystems for the
**        signaling point and deletes it
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_del_ss_from_sp
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss)
#else
	(p_ss)
	 ss_entry_t *p_ss;
#endif
{
	U32bit i;
	sp_entry_t * p_sp;
	ss_entry_t * p_tmp_ss;

/* SPR # 9502 Fix Start */
	sp_id_t		sp_id;

#if 0
	p_sp = GET_SP_OF_SS(p_ss);
#endif

	for(sp_id=0;sp_id<MAX_SP;sp_id++)
	{
		p_sp = GET_SP_FROM_ID(sp_id);
		if(IS_SP_CONFIGURED(p_sp) && (GET_NUM_SS_IN_SP(p_sp)>0))
		{
/* SPR # 9502 Fix End */
			/* If first element */
			if (p_ss == GET_SS_LIST_IN_SP(p_sp))
			{
				SET_SS_LIST_IN_SP(p_sp, GET_NEXT_SS(p_ss));
				SET_NUM_SS_IN_SP (p_sp, GET_NUM_SS_IN_SP(p_sp) - 1);
	/* SPR # 9502 Fix Start */
				continue;
	#if 0
				return;
	#endif
	/* SPR # 9502 Fix End */
			}
	
			/* If subsequent element */
			p_tmp_ss = GET_SS_LIST_IN_SP(p_sp);
			for (i=0; i + 1 < GET_NUM_SS_IN_SP(p_sp); i++)
			{
				if (p_ss == GET_NEXT_SS(p_tmp_ss))
				{
					SET_NEXT_SS(p_tmp_ss, GET_NEXT_SS(p_ss));
					SET_NUM_SS_IN_SP (p_sp, GET_NUM_SS_IN_SP(p_sp) - 1);
	/* SPR # 9502 Fix Start */
					break;
	#if 0
					return;
	#endif
	/* SPR # 9502 Fix End */
				}
				p_tmp_ss = GET_NEXT_SS(p_tmp_ss);
			}
/* SPR # 9502 Fix Start */
		}/* end : if(IS_SP_CONFIGURED(p_sp) && (GET_NUM_SS_IN_SP(p_sp)>0))*/
	}/* end : for(sp_id=0;sp_id<MAX_SP;sp_id++)*/
/* SPR # 9502 Fix End */

}

/*****************************************************************************
**      FUNCTION :
**         inserts the concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**         insert the css by moving all other elements in the array down
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_insert_css
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss, ss_entry_t * p_css)
#else
	(p_ss, p_css)
	 ss_entry_t 	*p_ss;
	 ss_entry_t 	*p_css;
#endif
{
	ss_id_t ss_id;
	U8bit * p_byte;
	U32bit i;

	if (GET_NUM_CSS(p_ss) == 0)
	{
		SET_CSS_LIST(p_ss, END_OF_BYTE_ARRAY());
	}

	sccp_memmove (GET_CSS_LIST(p_ss) + SIZEOF_SS_ID_T, GET_CSS_LIST(p_ss),
	              END_OF_BYTE_ARRAY() - GET_CSS_LIST(p_ss));

	p_byte = GET_CSS_LIST(p_ss);
	ss_id  = GET_ID_FROM_SS(p_css);
	for (i=0; i < sizeof(ss_id_t); i++)
	{
               *p_byte++ = (U8bit)ss_id;
        /* SPR 13263 - Fix Start */
                ss_id >>= (sizeof(U8bit) * 8);
        /*      ss_id >>= sizeof(U8bit); */
        /* SPR 13263 - Fix End */
	}

	SET_NUM_CSS (p_ss, GET_NUM_CSS(p_ss) + 1);
	sccp_db.end_conc_ss_sp += SIZEOF_SS_ID_T;
}

/*****************************************************************************
**      FUNCTION :
**        inserts the concerned signaling point in the list
******************************************************************************
**
**      DESCRIPTION :
**        insert by moving all other elements in the list down
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_insert_csp
#ifdef ANSI_PROTO
	(ss_entry_t * p_ss, sp_entry_t * p_csp)
#else
	(p_ss, p_csp)
	 ss_entry_t 	*p_ss;
	 sp_entry_t 	*p_csp;
#endif
{
	sp_id_t sp_id;
	U8bit * p_byte;
	U32bit i;

	if (GET_NUM_CSP(p_ss) == 0)
	{
		SET_CSP_LIST(p_ss, END_OF_BYTE_ARRAY());
	}

	sccp_memmove (GET_CSP_LIST(p_ss) + SIZEOF_SP_ID_T, GET_CSP_LIST(p_ss),
	              END_OF_BYTE_ARRAY() - GET_CSP_LIST(p_ss));

	p_byte = GET_CSP_LIST(p_ss);
	sp_id  = GET_ID_FROM_SP(p_csp);
	for (i=0; i < sizeof(sp_id_t); i++)
	{
		*p_byte++ = (U8bit)sp_id;
	/* SPR 13263 - Fix Start */
		sp_id >>= (sizeof(U8bit) * 8 );
	/*	sp_id >>= sizeof(U8bit);	*/
	/* SPR 13263 - Fix Stop */
	}

	SET_NUM_CSP (p_ss, GET_NUM_CSP(p_ss) + 1);
	sccp_db.end_conc_ss_sp += SIZEOF_SP_ID_T;
}

/*****************************************************************************
**      FUNCTION :
**        deletes this subsystem as a concerned subsystem
******************************************************************************
**
**      DESCRIPTION :
**        goes thru the all subsystems and calls function to delete this ss
**        as a css in each of them
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_del_all_ss_as_css
#ifdef ANSI_PROTO
	(ss_entry_t * p_css)
#else
	(p_css)
	 ss_entry_t *p_css;
#endif
{
	U32bit i;
	ss_entry_t * p_ss;
	error_t ecode;
	db_css_info_t css_info;

	css_info.css_id = GET_ID_FROM_SS(p_css);
	p_ss = GET_SS_FROM_ID(0);
	for (i=0; i < MAX_SS; i++, p_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_ss)) continue;

		css_info.ss_id = GET_ID_FROM_SS(p_ss);
		sccp_db_del_css (&css_info, &ecode);
	}
        /* Fix for SPR No : 13006 Start */
        css_info.ss_id = css_info.css_id;
        p_css = GET_SS_FROM_ID(0);
        for (i=0; i < MAX_SS; i++, p_css++)
        {
                if ( ! IS_SS_CONFIGURED(p_css)) continue;

                css_info.css_id = GET_ID_FROM_SS(p_css);
                sccp_db_del_css (&css_info, &ecode);
        }
        /* Fix for SPR No : 13006 End */

}

/*****************************************************************************
**      FUNCTION :
**        deletes this signaling point as a concerned signlaing point
******************************************************************************
**
**      DESCRIPTION :
**        goes thru the all subsystems and calls function to delete this sp
**        as a csp in each of them
**
**      NOTE :
**
*****************************************************************************/

void
sccp_db_del_all_sp_as_csp
#ifdef ANSI_PROTO
	(sp_entry_t * p_csp)
#else
	(p_csp)
	 sp_entry_t *p_csp;
#endif
{
	U32bit i;
	ss_entry_t * p_ss;
	error_t ecode;
	db_csp_info_t csp_info;

	csp_info.csp_id = GET_ID_FROM_SP(p_csp);
	p_ss = GET_SS_FROM_ID(0);
	for (i=0; i < MAX_SS; i++, p_ss++)
	{
		if ( ! IS_SS_CONFIGURED(p_ss)) continue;

		csp_info.ss_id = GET_ID_FROM_SS(p_ss);
		sccp_db_del_csp (&csp_info, &ecode);
	}
}

/*****************************************************************************
**      FUNCTION :
**         get the pointer to a subsystem from the css list
******************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
*****************************************************************************/

ss_entry_t *
sccp_db_get_css_from_list
#ifdef ANSI_PROTO
	(U8bit * p_byte)
#else
	(p_byte)
	 U8bit * p_byte;
#endif
{
	ss_id_t ss_id = 0;
	U8bit i;

	for (i=0; i < sizeof(ss_id_t); i++, p_byte++)
	{
		/*  6307 Fix starts */
		ss_id |= (ss_id_t)((*p_byte) << (i * 8));
		/*  6307 Fix ends */
	}

	return (GET_SS_FROM_ID(ss_id));
}

/*****************************************************************************
**      FUNCTION :
**         gets pointer to the signaling point from the id list
******************************************************************************
**
**      DESCRIPTION :
**
**
**      NOTE :
**
*****************************************************************************/

sp_entry_t *
sccp_db_get_csp_from_list
#ifdef ANSI_PROTO
	(U8bit * p_byte)
#else
	(p_byte)
	 U8bit *p_byte;
#endif
{
	sp_id_t sp_id = 0;
	U8bit i;

	for (i=0; i < sizeof(sp_id_t); i++, p_byte++)
	{
		/* SPR 6307 Fix Starts */
		sp_id |= (sp_id_t)((*p_byte) << (i *8));
		/* SPR 6307 Fix ends */
	}

	return (GET_SP_FROM_ID(sp_id));
}
