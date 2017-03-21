/***************************************************************************
**
**  FILE :
**      SCCP connection oriented API parsing functions.
**
******************************************************************************
**
**  FILENAME :
**      sc_coprs.c
**
**  DESCRIPTION :
**     API parsing functionality for handling SCCP connection oriented service
**     user APIs.
**
**  Date        Name           Reference       Reason
**  _________________________________________________________________________
**  11Sep2001 Ramu Kandula                  SPR # 6106 Fix: Changed 
**							  SCCP_ELEM_CORR_ID_LEN to
**							  SCCP_ELEM_IMPORTANCE_LEN
**  24May2001 Rajesh Mehta                  Increased corr_id to 2 byte and
**                                          conn_id to 4 byte if the flag
**                                          SCCP_CONNECTION_ID_CHANGES is defined
**  08Jun2000 Ramu Kandula                  Fixed SPR # 3823   	
**  22Apr2000 Ramu Kandula                  Fixed SPR # 3094   	
**  15Oct'99  Ramu Kandula     SPR #878    	replaced ss7_mem_get with sccp_malloc
**                                          & ss7_mem_free with sccp_free
**  10Aug'99    Sudipta Pattar	-	   		Fixed SPR 1939
**  21Jul'98    Anil Kumar     HSS:20800011 Original
**
**  Copyright 1998, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"
#include "sc_reg.h"
#ifdef SCCP_INCLUDE_CO_SERVICE
void find_ss_in_reg_table(msg_info_t *);

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-CONNECT.ind
**
******************************************************************************
**
**  DESCRIPTION :
**      N-CONNECT.ind API information elements :
**
**          Fixed elements : connection_id
**                           protocol_class
**          Mandatory Variable : called_address
**          Optional elements  : credit
**                               user_data
**                 corr_id
**                               importance (ITU-T only)
**
*****************************************************************************/

void
sccp_build_n_connect_ind_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  U16bit      api_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;
  U8bit       *p_tmp ;

  p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_CONNECT_IND_MIN_NELEM;

  /* Fixed parameter length */
  api_len += (SCCP_ELEM_CONNECTION_ID_LEN +
        SCCP_ELEM_PROTOCOL_CLASS_LEN);

  /* mandatory variable parameter */
  api_len += (SCCP_ELEM_LEN_LEN +
        sccp_addr_len (&p_info->cd_addr));

  /* Optional parameters */
  if (IS_CG_IE_PRESENT (p_info))
  {
	/** SPR # 3094 Fix Start **/
	if ( !(p_info->cg_addr.gti) && !(p_info->cg_addr.pc_ind) )
	{
		p_info->cg_addr.pc_ind = SS7_TRUE;
		p_info->cg_addr.pc = p_info->opc;
	}
	/** SPR # 3094 Fix End **/
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          sccp_addr_len (&p_info->cg_addr));
    num_elem++;
  }

  if (((p_info->proto_class & 0x0f)== PROTOCOL_CLASS_3) &&
    (IS_CREDIT_IE_PRESENT (p_info)))
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          SCCP_ELEM_CREDIT_LEN);
    num_elem++;
  }

  if (IS_DATA_IE_PRESENT (p_info))
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          p_info->data.len);
    num_elem++;
  }

  if ((p_ccb->c_status & SCCP_USER_TYPE_MASK) ==  SCCP_TYPE_A_USER)
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          SCCP_ELEM_CORR_ID_LEN);
    num_elem++;
  }

  if (IS_IMPORTANCE_IE_PRESENT (p_info))
  {
    api_len += (SCCP_ELEM_ID_LEN +
            SCCP_ELEM_LEN_LEN +
            SCCP_ELEM_IMPORTANCE_LEN); /* SPR # 6106 Fix */
    num_elem++;
  }

  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send connect ind\n"));
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_CONNECT_INDICATION,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  *p_elem =  p_info->proto_class;
  p_elem += SCCP_ELEM_PROTOCOL_CLASS_LEN;

  /* Mandatory variable parameter */
  p_tmp = p_elem;
  /* Leave a one byte space as lengths in APIs are two bytes
     and following function assume first byte as a length and
     address is coded in rest of other bytes.
  */
  p_elem = sccp_encode_sccp_addr ((p_elem + 1), &p_info->cd_addr);
  /* Move the length to the first byte of length field */
  *p_tmp = *(p_tmp + 1);
  *(p_tmp + 1) = (U8bit)SS7_NULL;

  /* Optional parameters */
  if (IS_CG_IE_PRESENT (p_info))
  {
    *p_elem = SCCP_ELEM_CALLING_ADDR;
    p_elem += SCCP_ELEM_ID_LEN;
    p_tmp = p_elem;
    /*   Leave a one byte space as lengths in APIs are two bytes
      and following function assume first byte as a length and
      address is coded in rest of other bytes.
    */
    p_elem = sccp_encode_sccp_addr ((p_elem + 1), &p_info->cg_addr);

    /* Move the length to the first byte of length field */
    *p_tmp = *(p_tmp + 1);
    *(p_tmp + 1) = (U8bit)SS7_NULL;
  }

  if (((p_info->proto_class & 0x0f)== PROTOCOL_CLASS_3) &&
    (IS_CREDIT_IE_PRESENT (p_info)))
  {
    *p_elem = SCCP_ELEM_CREDIT;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, SCCP_ELEM_CREDIT_LEN);
    p_elem += SCCP_ELEM_LEN_LEN;

    *p_elem = p_info->credit;
    p_elem += SCCP_ELEM_CREDIT_LEN;
  }

  if (IS_DATA_IE_PRESENT (p_info))
  {
    *p_elem = SCCP_ELEM_USER_DATA;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, p_info->data.len);
    p_elem += SCCP_ELEM_LEN_LEN;

    sccp_memcpy (p_elem, p_info->data.p, p_info->data.len);
    p_elem += p_info->data.len;
  }

  if ((p_ccb->c_status & SCCP_USER_TYPE_MASK) ==  SCCP_TYPE_A_USER)
  {
    *p_elem = SCCP_ELEM_CORR_ID;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, SCCP_ELEM_CREDIT_LEN);
    p_elem += SCCP_ELEM_LEN_LEN;

#ifdef SCCP_CONNECTION_ID_CHANGES
    PUT_4_BYTE_LE (p_elem, SCCP_ELEM_CORR_ID_LEN); /* Change by Amaresh 2byte 4byte as on dated 20-01-16 */
#else
    *p_elem = p_info->corr_id;
#endif
    p_elem += SCCP_ELEM_CORR_ID_LEN;
  }

    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      *p_elem = SCCP_ELEM_IMPORTANCE;
      p_elem += SCCP_ELEM_ID_LEN;

      PUT_2_BYTE_LE (p_elem, SCCP_ELEM_IMPORTANCE_LEN);
      p_elem += SCCP_ELEM_LEN_LEN;

      *p_elem = p_info->importance;
      p_elem += SCCP_ELEM_IMPORTANCE_LEN;
    }

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-CONNECT.conf
**
******************************************************************************
**
**  DESCRIPTION :
**      N-CONNECT.conf API information elements :
**
**          Fixed elements : corr_id 
**               connection_id
**                           protocol_class
**          Mandatory Variable : NONE
**          Optional elements  : responding_addr
**                 credit
**                               user_data
**                               importance (ITU-T only)
**
*****************************************************************************/

void
sccp_build_n_connect_conf_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  U16bit      api_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;
  U8bit       *p_tmp ;

  p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_CONNECT_CONF_MIN_NELEM;

  /* Fixed parameter length */
  api_len += (SCCP_ELEM_CORR_ID_LEN +
        SCCP_ELEM_CONNECTION_ID_LEN +
        SCCP_ELEM_PROTOCOL_CLASS_LEN);

  /* No mandatory variable parameter */

  /* Optional parameters */
  if (IS_RG_IE_PRESENT (p_info))
  {
	/** SPR # 3094 Fix Start **/
	if ( !(p_info->cg_addr.gti) && !(p_info->cg_addr.pc_ind) )
	{
		p_info->cg_addr.pc_ind = SS7_TRUE;
		p_info->cg_addr.pc = p_info->opc;
	}
	/** SPR # 3094 Fix End **/
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          sccp_addr_len (&p_info->cg_addr));
    num_elem++;
  }

  if (((p_info->proto_class & 0x0f)== PROTOCOL_CLASS_3) &&
    (IS_CREDIT_IE_PRESENT (p_info)))
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          SCCP_ELEM_CREDIT_LEN);
    num_elem++;
  }
  if (IS_DATA_IE_PRESENT (p_info))
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          p_info->data.len);
    num_elem++;
  }
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      api_len += (SCCP_ELEM_ID_LEN +
            SCCP_ELEM_LEN_LEN +
            SCCP_ELEM_IMPORTANCE_LEN);
      num_elem++;
    }

  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send connect ind\n"));
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_CONNECT_CONFIRM,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
  /* SPR ITU-ATS: pick corr_id from connection block */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_ccb->corr_id); /* Change by Amaresh 2byte 4byte as on dated 20-01-16 */
#else
  *p_elem = p_ccb->corr_id;
#endif

  p_elem += SCCP_ELEM_CORR_ID_LEN;
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  *p_elem =  p_info->proto_class;
  p_elem += SCCP_ELEM_PROTOCOL_CLASS_LEN;

  /* No Mandatory variable parameter */

  /* Optional parameters */
  if (IS_RG_IE_PRESENT (p_info))
  {
	/* SPR 10686 - Fix Start */
    /**p_elem = SCCP_ELEM_CALLING_ADDR;*/
    *p_elem = SCCP_ELEM_RESPONDING_ADDR;
	/* SPR 10686 - Fix End  */
    p_elem += SCCP_ELEM_ID_LEN;
    p_tmp = p_elem;
    /*   Leave a one byte space as lengths in APIs are two bytes
      and following function assume first byte as a length and
      address is coded in rest of other bytes.
    */
    p_elem = sccp_encode_sccp_addr ((p_elem + 1), &p_info->cg_addr);

    /* Move the length to the first byte of length field */
    *p_tmp = *(p_tmp + 1);
    *(p_tmp + 1) = (U8bit)SS7_NULL;
  }

  if (((p_info->proto_class & 0x0f)== PROTOCOL_CLASS_3) &&
    (IS_CREDIT_IE_PRESENT (p_info)))
  {
    *p_elem = SCCP_ELEM_CREDIT;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, SCCP_ELEM_CREDIT_LEN);
    p_elem += SCCP_ELEM_LEN_LEN;

    *p_elem = p_info->credit;
    p_elem += SCCP_ELEM_CREDIT_LEN;
  }

  if (IS_DATA_IE_PRESENT (p_info))
  {
    *p_elem = SCCP_ELEM_USER_DATA;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, p_info->data.len);
    p_elem += SCCP_ELEM_LEN_LEN;

    sccp_memcpy (p_elem, p_info->data.p, p_info->data.len);
    p_elem += p_info->data.len;
  }
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      *p_elem = SCCP_ELEM_IMPORTANCE;
      p_elem += SCCP_ELEM_ID_LEN;

      PUT_2_BYTE_LE (p_elem, SCCP_ELEM_IMPORTANCE_LEN);
      p_elem += SCCP_ELEM_LEN_LEN;

      *p_elem = p_info->importance;
      p_elem += SCCP_ELEM_IMPORTANCE_LEN;
    }

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-CONNECT.reply
**
******************************************************************************
**
**  DESCRIPTION :
**      N-CONNECT.reply API information elements :
**
**          Fixed elements : corr_id 
**               connection_id
**                           protocol_class
**               slr_number
**          Mandatory Variable : NONE
**          Optional elements  : credit
**
*****************************************************************************/

void
sccp_build_n_connect_reply_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  U16bit      api_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;

  p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_CONNECT_REPLY_MIN_NELEM;

  /* Fixed parameter length */
  api_len += (SCCP_ELEM_CORR_ID_LEN +
        SCCP_ELEM_CONNECTION_ID_LEN +
        SCCP_ELEM_PROTOCOL_CLASS_LEN +
        SCCP_ELEM_LOCAL_REF_LEN);

  /* No mandatory variable parameter */

  /* Optional parameters */
  if (((p_info->proto_class & 0x0f)== PROTOCOL_CLASS_3) &&
    (IS_CREDIT_IE_PRESENT (p_info)))
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          SCCP_ELEM_CREDIT_LEN);
    num_elem++;
  }


  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send connect ind\n"));
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_CONNECT_REPLY,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->corr_id); /* Change by Amaresh 2byte 4byte as on dated 20-01-16 */
#else
  *p_elem = p_info->corr_id;
#endif
  p_elem += SCCP_ELEM_CORR_ID_LEN;

#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  *p_elem =  p_info->proto_class;
  p_elem += SCCP_ELEM_PROTOCOL_CLASS_LEN;

  PUT_3_BYTE_LE (p_elem, p_info->slr);
  p_elem += SCCP_ELEM_LOCAL_REF_LEN;

  /* No Mandatory variable parameter */

  /* Optional parameters */
  if (((p_info->proto_class & 0x0f)== PROTOCOL_CLASS_3) &&
    (IS_CREDIT_IE_PRESENT (p_info)))
  {
    *p_elem = SCCP_ELEM_CREDIT;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, SCCP_ELEM_CREDIT_LEN);
    p_elem += SCCP_ELEM_LEN_LEN;

    *p_elem = p_info->credit;
    p_elem += SCCP_ELEM_CREDIT_LEN;
  }

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-DATA.ind
**
******************************************************************************
**
**  DESCRIPTION :
**      N-DATA.ind API information elements :
**
**          Fixed elements : connection_id 
**          Mandatory Variable : user_data
**          Optional elements  : importance (ITU-T only)
**
*****************************************************************************/

void
sccp_build_n_data_ind_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  sc_queue_t *p_queue, *p_tmp;
  U16bit      api_len, data_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;

  p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_DATA_IND_MIN_NELEM;

  /* Fixed parameter length */
  api_len += SCCP_ELEM_CONNECTION_ID_LEN;

  /* mandatory variable parameter */
  api_len += (p_info->data.len + SCCP_ELEM_LEN_LEN);
  data_len = p_info->data.len;
  /* add the length from reassembly buffer */
  p_queue = p_ccb->p_recv_queue;
  while (p_queue != (sc_queue_t *) SS7_NULL)
  {
	api_len += p_queue->len;
	data_len += p_queue->len;
	p_queue = p_queue->p_next;
  }

  /* Optional parameters */
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      api_len += (SCCP_ELEM_ID_LEN +
            SCCP_ELEM_LEN_LEN +
            SCCP_ELEM_IMPORTANCE_LEN); /* SPR # 6106 Fix */
      num_elem++;
    }

  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send connect ind\n"));
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_DATA_INDICATION,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;


  /* No Mandatory variable parameter */
  PUT_2_BYTE_LE (p_elem, data_len);
  p_elem += SCCP_ELEM_LEN_LEN;

  /* now collect the data from reassemble queue */
  p_queue = p_ccb->p_recv_queue;
  while (p_queue != (sc_queue_t *)SS7_NULL)
  {
	sccp_memcpy (p_elem, p_queue->p_buf, p_queue->len);
	p_elem += p_queue->len;
	p_tmp = p_queue;
	p_queue = p_queue->p_next;
	sccp_free ((U8bit * )p_tmp);
/* start added during CC compilation */
/* assign pvoid to U8bit * */
/* end added during CC compilation */

  }
  p_ccb->p_recv_queue = (sc_queue_t *)SS7_NULL ;
  /* Put the last segment */
  sccp_memcpy (p_elem, p_info->data.p, p_info->data.len);
  p_elem += p_info->data.len;

  /* Optional parameters */
    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      *p_elem = SCCP_ELEM_IMPORTANCE;
      p_elem += SCCP_ELEM_ID_LEN;

      PUT_2_BYTE_LE (p_elem, SCCP_ELEM_IMPORTANCE_LEN);
      p_elem += SCCP_ELEM_LEN_LEN;

      *p_elem = p_info->importance;
      p_elem += SCCP_ELEM_IMPORTANCE_LEN;
    }

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-ED_DATA.ind
**
******************************************************************************
**
**  DESCRIPTION :
**      N-ED_DATA.ind API information elements :
**
**          Fixed elements : connection_id 
**          Mandatory Variable : user_data
**          Optional elements  : NONE
**
*****************************************************************************/

void
sccp_build_n_expediate_data_ind_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  U16bit      api_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;

  p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_ED_DATA_IND_NELEM;

  /* Fixed parameter length */
  api_len += SCCP_ELEM_CONNECTION_ID_LEN;

  /* mandatory variable parameter */
  /* SPR 1939: Include length of data length param */
  api_len += (p_info->data.len + SCCP_ELEM_LEN_LEN);

  /* No Optional parameters */

  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send connect ind\n"));
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_EXPEDIATE_DATA_INDICATION,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;


  /* No Mandatory variable parameter */
  PUT_2_BYTE_LE (p_elem, p_info->data.len);
  /* SPR 1939: Increment by parameter length */
  p_elem += SCCP_ELEM_LEN_LEN;
  sccp_memcpy (p_elem, p_info->data.p, p_info->data.len);

  /* No Optional parameters */

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-RESET.ind
**
******************************************************************************
**
**  DESCRIPTION :
**      N-RESET.ind API information elements :
**
**          Fixed elements : connection_id 
**               reason_for_reset
**               reset_originator
**          Mandatory Variable : NONE
**          Optional elements  : NONE
**
*****************************************************************************/

void
sccp_build_n_reset_ind_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  U16bit      api_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;

  p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_RESET_IND_NELEM;

  /* Fixed parameter length */
  api_len += SCCP_ELEM_CONNECTION_ID_LEN;
  api_len += SCCP_ELEM_REASON_FOR_RESET_LEN;
  api_len += SCCP_ELEM_RESET_ORG_LEN;

  /* No mandatory variable parameter */

  /* No Optional parameters */

  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send connect ind\n"));
    return ;
  }

  /* The API ID being filled was corrected */
  sccp_fill_api_header (p_api, SCCP_N_RESET_INDICATION,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  *p_elem = p_info->reset_cause;
  p_elem += SCCP_ELEM_REASON_FOR_RESET_LEN;

  /* SPR # 3823 Fix Start */
  *p_elem = sccp_utl_get_rsr_originator(p_info->reset_cause);
  /* SPR # 3823 Fix end */
  p_elem += SCCP_ELEM_RESET_ORG_LEN;


  /* No Mandatory variable parameter */

  /* No Optional parameters */

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-RESET.conf
**
******************************************************************************
**
**  DESCRIPTION :
**      N-RESET.ind API information elements :
**
**          Fixed elements : connection_id 
**               reason_for_reset
**               reset_originator
**          Mandatory Variable : NONE
**          Optional elements  : NONE
**
*****************************************************************************/

void
sccp_build_n_reset_conf_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  U16bit      api_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;

  p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_RESET_CONF_NELEM;

  /* Fixed parameter length */
  api_len += SCCP_ELEM_CONNECTION_ID_LEN;

  /* No mandatory variable parameter */

  /* No Optional parameters */

  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send connect ind\n"));
    return ;
  }

  /* The API ID being filled was corrected */
  sccp_fill_api_header (p_api, SCCP_N_RESET_CONFIRM,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  /* No Mandatory variable parameter */

  /* No Optional parameters */

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

#endif

/*****************************************************************************
**
**  FUNCTION :
**      Builds the N-DISC.ind
**
******************************************************************************
**
**  DESCRIPTION :
**      N-DISC.ind API information elements :
**
**          Fixed elements : connection_id 
**               reason
**               disc_originator
**          Mandatory Variable : NONE
**          Optional elements  : responding_address
**								 corr_id
**								 user_data
**								 importance (ITU only)
*****************************************************************************/

void
sccp_build_n_disconnect_ind_api
#ifdef ANSI_PROTO
  (msg_info_t  *p_info,
   sccp_ccb_t  *p_ccb)
#else
    (p_info, p_ccb)
    msg_info_t *p_info ;
    sccp_ccb_t *p_ccb ;
#endif
{
  U16bit      api_len ;   
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;
  U8bit       *p_tmp ;

  if(p_ccb == SS7_NULL)
	find_ss_in_reg_table(p_info);
  else
  	p_info->p_ss = p_ccb->p_ss ;

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_DISCONNECT_IND_NELEM;

  /* Fixed parameter length */
  api_len += (SCCP_ELEM_CONNECTION_ID_LEN +
        SCCP_ELEM_REFUSAL_CAUSE_LEN +
		SCCP_ELEM_DISC_ORG_LEN);

  /* No mandatory variable parameter */

  /* Optional parameters */
  if (IS_RG_IE_PRESENT (p_info))
  {
	/** SPR # 3094 Fix Start **/
	if ( !(p_info->cg_addr.gti) && !(p_info->cg_addr.pc_ind) )
	{
		p_info->cg_addr.pc_ind = SS7_TRUE;
		p_info->cg_addr.pc = p_info->opc;
	}
	/** SPR # 3094 Fix End **/
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          sccp_addr_len (&p_info->cg_addr));
    num_elem++;
  }

  if (IS_CORR_ID_IE_PRESENT (p_info))
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          SCCP_ELEM_CORR_ID_LEN);
    num_elem++;
  }

  if (IS_DATA_IE_PRESENT (p_info))
  {
    api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          p_info->data.len);
    num_elem++;
  }

    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      api_len += (SCCP_ELEM_ID_LEN +
            SCCP_ELEM_LEN_LEN +
            SCCP_ELEM_IMPORTANCE_LEN); /* SPR # 6106 Fix */
      num_elem++;
    }

  /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)sccp_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    SC_A_TRC (("SCCP::CO: cannot send disconnect ind\n"));
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_DISCONNECT_INDICATION,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, p_info->conn_id);
#else
  PUT_2_BYTE_LE (p_elem, p_info->conn_id);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  *p_elem =  p_info->rel_cause;
  p_elem += SCCP_ELEM_REFUSAL_CAUSE_LEN;

  *p_elem = p_info->originator ;
  p_elem += SCCP_ELEM_DISC_ORG_LEN;

  /* NO Mandatory variable parameter */

  /* Optional parameters */
  if (IS_RG_IE_PRESENT (p_info))
  {
    *p_elem = SCCP_ELEM_RESPONDING_ADDR;
    p_elem += SCCP_ELEM_ID_LEN;
    p_tmp = p_elem;
    /*   Leave a one byte space as lengths in APIs are two bytes
      and following function assume first byte as a length and
      address is coded in rest of other bytes.
    */
    p_elem = sccp_encode_sccp_addr ((p_elem + 1), &p_info->cg_addr);

    /* Move the length to the first byte of length field */
    *p_tmp = *(p_tmp + 1);
    *(p_tmp + 1) = (U8bit)SS7_NULL;
  }

  if(IS_CORR_ID_IE_PRESENT (p_info))
  {
    *p_elem = SCCP_ELEM_CORR_ID;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, SCCP_ELEM_CORR_ID_LEN);
    p_elem += SCCP_ELEM_LEN_LEN;

#ifdef SCCP_CONNECTION_ID_CHANGES
   PUT_4_BYTE_LE (p_elem, p_info->corr_id);/* Change by Amaresh 2byte 4byte as on dated 20-01-16 */    
#else
   *p_elem = p_info->corr_id;
#endif
    p_elem += SCCP_ELEM_CORR_ID_LEN;
  }

  if (IS_DATA_IE_PRESENT (p_info))
  {
    *p_elem = SCCP_ELEM_USER_DATA;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, p_info->data.len);
    p_elem += SCCP_ELEM_LEN_LEN;

    sccp_memcpy (p_elem, p_info->data.p, p_info->data.len);
    p_elem += p_info->data.len;
  }

    if (IS_IMPORTANCE_IE_PRESENT (p_info))
    {
      *p_elem = SCCP_ELEM_IMPORTANCE;
      p_elem += SCCP_ELEM_ID_LEN;

      PUT_2_BYTE_LE (p_elem, SCCP_ELEM_IMPORTANCE_LEN);
      p_elem += SCCP_ELEM_LEN_LEN;

      *p_elem = p_info->importance;
      p_elem += SCCP_ELEM_IMPORTANCE_LEN;
    }

  sccp_sendto_tc (p_api, p_info->p_ss) ;

  return;
}

void find_ss_in_reg_table(msg_info_t * p_info)
{
	U16bit count;
	
	for (count = 0; count < MAX_LOCAL_USERS ; count ++)
	{
		if(sccp_reg_table[count].uid == p_info->l_id)
		{
		     p_info->p_ss = sccp_reg_table[count].p_ss;
		     break;
		}
	}
	return;
}

#else

/*****************************************************************************
**	This extern declaration is required as BCC reports error if the 
** source file is empty after preprocessing. This declaration enables compilation
** without SCCP_INCLUDE_CO_SERVICE flag using BCC.
**
*****************************************************************************/

extern return_t sccp_co_dummy _ARGS_ ((void));

#endif
