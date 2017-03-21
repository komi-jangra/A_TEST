/***************************************************************************
**  FILE NAME:
**      sc_segm.c
**
****************************************************************************
**
**  FUNCTION:
**
**
**  DESCRIPTION:
**
**
**  DATE     NAME              REF#             REASON
**  -------  ----------------  --------------  ----------------------------
**  31Jul2002 Prateek Bidwalkar                 Fixed SPR 9221
**  03Nov2000 Vikas                             Fixed SPR 4524
**  09Mar2000 Ramu Kandula                      Fixed SPR 2779
**  17Feb2000 Ramu Kandula                      Fixed SPR 2618
**  17/2/99  Sudipta Pattar                     Fixed SPR 1343
**  15/2/99  Sudipta Pattar                     Fixed SPR 1342
**  3/6/98   Sriganesh. Kini   ITU-714/713      Original
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/


#include "sc_stgl.h"
#include "sc_sref.h"

/****************************************************************************
** GLOBAL DATA  : segmentation_local_ref
*****************************************************************************
**
** Description:
**  Contains the next SLR to be assigned while segmenting the data
**
*****************************************************************************/
 
U32bit segmentation_local_ref = 0;
 

/*****************************************************************************
**
**      FUNCTION : sccp_handle_changes_needed
**            
******************************************************************************
**
**      DESCRIPTION :
**          The processing in this function corresponds to
**          Q.714/C.12/sheet-6 on the event 
**          Changes needed [ SCRC -> SCLC ]
**      
**          This function does the following :
**          (1) Performs the action Segmentation needed
**              a. Assigns segmentation local reference for non local originator
**              b. Segments the data 
**              c. If the number of segments exceeds 16, sends n_notice
**                 indication to the user
**              d. Calls sccp_route_CL_msg to route the
**                 message
**          
**      RETURNS :
**          SUCCESS/FAILURE depending on whether the routing for each segment
**          is successful or has failed.
**
*****************************************************************************/
void
sccp_handle_changes_needed 
#ifdef ANSI_PROTO
	(msg_info_t * p_info)
#else
	(p_info)
	msg_info_t * p_info;
#endif
{
	U16bit num_bytes_sent = 0;
#ifdef SCCP_TRACE_ENABLED
	U16bit segment_num = 0;
#endif
	data_t full_data;
	U16bit seg_size;
	U16bit max_y; /* Added for SPR 4524 */

	CL_TRC (("SCCP::SCLC: handling changes needed\n"));

	if (SCCP_N_UNITDATA_REQUEST == GET_API_ID(p_info->p_api))
	{
		p_info->segment.slr = sccp_assign_slr();
	}
	
	/** SPR 10882 - Fix Start **/
	/** ITU-1.1.4.4 Spare bits should be set zero on msg creation **/
	p_info->segment.spare_bit = 0;
	/** SPR 10882 - Fix End  **/

	full_data.p = p_info->data.p;
	full_data.len = p_info->data.len;

	p_info->msg_type = XUDT_MSG_TYPE;

	seg_size = sc_opt.seg_size;
    /* SPR 4524 : fix begins */
    /* SPR 4524 : We need to calculate Y (Refer Table19/Q.713)
         and see if seg_size is > Y . Segm is surely there. */
    max_y = sccp_calc_max_y (p_info, SS7_TRUE);
	if (seg_size > max_y)
		seg_size = max_y;
    /* SPR 4524 : fix ends */

	if (p_info->data.len % seg_size)
		p_info->segment.rem_seg = full_data.len / seg_size;
	else
		p_info->segment.rem_seg = (full_data.len / seg_size) - 1;

	CL_TRC (("SCCP::SCLC: Segmenting : total %d segments\n",
	         p_info->segment.rem_seg + 1));

	/* SPR 1343: Start fix
	 * A maximum of 16 segments are allowed 
  	 */
	if ((p_info->segment.rem_seg+1) > MAX_SEG)
	{
		CL_TRC (("SCCP::SCLC: Number of segments exceed 16: "
				"routing failure.\n"));
/* SPR # 9221 Fix Start */	
		SC_STAT_Q752_TS_MSG_TOO_LARGE_FOR_SEGMENTING;
		SC_STAT_Q752_INR_MSG_TOO_LARGE_FOR_SEGMENTING;
/* SPR # 9221 Fix End */	
		/* send n_notice_indication to user if return option set */	
                if (! (p_info->proto_class & RET_OPTN_MASK))
                {
                       CL_TRC (("SCCP::SCLC: return option not set in UDT\n"));
                       return;
                }
 
                CL_TRC (("SCCP::SCLC: return option set in UDT\n"));
 
		/** SPR # 2618 Fix Start **/
		/* SCCP_SEGMENTATION_FAILURE not defn.d in ANSI & GR; using
		** SCCP_ERR_IN_LOCAL_PROCESSING instead;
		*/
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
		if ((COMPARE_ANSI) || (COMPARE_BCGR))
		{
			p_info->ret_cause = SCCP_ERR_IN_LOCAL_PROCESSING; 
		}
#endif

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
		if (( (COMPARE_ITU) || (COMPARE_JAPANESE)) || (COMPARE_ETSI) || (COMPARE_CHINESE))
		{
			p_info->ret_cause = SCCP_SEGMENTATION_FAILURE; 
		}
#endif
		/** SPR # 2618 Fix End **/


                sccp_build_n_notice_ind_api (p_info);
		return;
	}
	/* SPR 1343: End fix */


	/* SPR 1342: Start fix
         * Set protocol class to 1 for the XUDT message
	 */
	/** SPR # 2779 Fix Start **/
	/* The protocol class will be filled as 1 when filling the XUDT msg;
	** The value of the prococol class must be retained to fill the ISDO 
	** bit in the segmentation parameter correctly
	*/
#if 0
	if (p_info->proto_class & RET_OPTN_MASK)
		p_info->proto_class = RET_OPTN_MASK;
	p_info->proto_class |= PROTOCOL_CLASS_1; 
#endif
	/** SPR # 2779 Fix End **/

	/* SPR 1342: End fix */

	p_info->segment.f_bit = 1;

	/* select data */
	do
	{
		if (full_data.len > (num_bytes_sent + seg_size))
			p_info->data.len = seg_size;
		else
			p_info->data.len = full_data.len - num_bytes_sent;

		p_info->data.p = &full_data.p[num_bytes_sent];
		num_bytes_sent += p_info->data.len;

		CL_TRC (("SCCP::SCLC: creating segment num %d of size %d\n",
		         segment_num++, p_info->data.len));

		SET_SEGMENTATION_PRESENT (p_info);
		sccp_route_cl_msg (p_info);
		p_info->segment.f_bit = 0;

	} while ( ! (0 == (p_info->segment.rem_seg--)));
}

/*****************************************************************************
**
**      FUNCTION : sccp_calc_max_y
**            
******************************************************************************
**
**      DESCRIPTION :
**       It calculates the max value of Y as indicated
**        in Table 19/Q.713. It takes care of ANSI also.
**       It takes as input the p_info structure and a flag
**         indicating if segmentation param is present or not.
**
**        The following two constraints are used to calc the max.
**             1) pointer to opt_arg <= 255 in the XUDT.
**                 pointer = len(clg) + 1 + len(cld) + 1 +
**                       Y + 1(Length Ind for data) + 1(1 byte of pointer itself)       
**                   pointer <= 255. This gives us a constraint on Y after
**                       rearranagement.
**             2) Total length of XUDT <= 268 (itu) or 265 (ANSI) so
**                 that at MTP2 level SIF does not exceed 272.
              
**          
**      RETURNS :
**         max value of Y
**      NOTE : added for SPR4524
*****************************************************************************/
U16bit
sccp_calc_max_y
#ifdef ANSI_PROTO
	(msg_info_t * p_info,
     Boolean      segm_needed)
#else
	(p_info, segm_needed)
	msg_info_t * p_info;
    Boolean      segm_needed;
#endif
{
    U16bit max_y ; /* Return of this function */
    U16bit max_y_for_valid_pointer; /* Max val of y according to
                        pointer constraint */
    U16bit max_sccp_pkt_length = 268; /* Max len of SCCP portion in
                                           SIF */
    U16bit msg_len; /* Actually msg len except data */
    Boolean opt_present = SS7_FALSE; /*Is opt var present */
    U16bit cd_len,cg_len; /*Length of cld,clg addr except Length ind */

#if (defined(SCCP_ANSI) || defined(SCCP_BCGR)) 
    if  ((COMPARE_ANSI || COMPARE_BCGR))
        max_sccp_pkt_length = 265;
#endif

    cd_len = sccp_addr_len(&p_info->cd_addr);
    cg_len = sccp_addr_len(&p_info->cg_addr);
    msg_len = MIN_XUDT_MSG_LEN +
              V_PARAM_LEN_LEN + cd_len +
              V_PARAM_LEN_LEN + cg_len +
              V_PARAM_LEN_LEN ;
  
    /* Optional parameters */
    if (segm_needed)
        msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
				              NW_SEGMENTATION_PARAM_LEN;

#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_ETSI) || defined (SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {
        if (IS_IMPORTANCE_PRESENT(p_info))
            msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                          IMPORTANCE_PARAM_LEN;

    }
#endif

#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
    if ((COMPARE_ANSI) || (COMPARE_BCGR))
    {
        if (IS_ISNI_PRESENT(p_info))
        {
            msg_len += O_PARAM_TYPE_LEN + O_PARAM_LEN_LEN +
                           p_info->isni.len;
        }
    }
#endif

			/* End of opt params byte */
#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_CHINESE)
    if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI || COMPARE_CHINESE)
    {
        if (segm_needed || 
            IS_IMPORTANCE_PRESENT(p_info))
        {
            msg_len++;
            opt_present = SS7_TRUE;
        }
    }
#endif


#if defined(SCCP_ANSI) || defined (SCCP_BCGR)
    if ((COMPARE_ANSI) || (COMPARE_BCGR))
    {
        if (segm_needed || 
            IS_ISNI_PRESENT(p_info))
        {
            msg_len++;
            opt_present = SS7_TRUE;
        }
    }
#endif
        
  max_y = max_sccp_pkt_length - msg_len;

  if (opt_present)
  {
     /* Now is the time to check that the pointer does not
         exceeed 255 */
     max_y_for_valid_pointer = 253 - 
                        ( V_PARAM_LEN_LEN + cd_len +
                          V_PARAM_LEN_LEN + cg_len ); 
     if (max_y > max_y_for_valid_pointer)
         max_y = max_y_for_valid_pointer;
  }
              
  return max_y;                                
}
