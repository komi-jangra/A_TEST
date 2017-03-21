/*****************************************************************************
**
**  FILE :
**       SCCP connection oriented API parsing functions.
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
**  Date        Name                Reference       Reason
**  _________________________________________________________________________
**  21Nov'03    Hitesh Sharma                     SPR 12561,12562
**  21Nov'03    Hitesh Sharma                     SPR 12557
**  21Nov'03    Hitesh Sharma                     SPR 12556
**  20Nov'03    Hitesh Sharma                     SPR 12555
**  20Nov'03    Hitesh Sharma                     SPR 12553 
**  08Sep'03    Salil Agrawal                     SPR 12319 
**  08Sep'03    Salil Agrawal                     SPR 12322 
**  08Sep'03    Salil Agrawal                     SPR 12499 
**  21Oct'03	Ganesh Kumar			    Fixed SPR # 12500
**  20Oct'03	Ganesh Kumar			    Fixed SPR # 12566
**  23oct'02    Pawanish			    added CG addr to N-CONN REQ
**  08Jul'02    Suyash Tripathi   		    Fixed SPR # 9126
**  19Jun'02    Suyash Tripathi   		    Fixed SPR # 8841
**  13Sep'01    Aman Kapoor			    Fixed SPR # 4988
**  11Sep'01    Aman Kapoor                         Fixed SPR # 6086
**  25May'01    Rajesh Mehta                        changed conn_id to 4 byte
**                                                  and corr_id to 2 byte in
**                                                  case SCCP_CONNECTION_ID_CHANGES
**                                                   is defined 
**  09Jun'00    Ramu Kandula                        Fixed SPR # 2579
**  07Jun'00    Ramu Kandula                        Fixed SPR # 2613
**  07Jun'00    Ramu Kandula                        Fixed SPR # 2612
**  18Jul'98    Anil Kumar          HSS:20800011    Original
**  18June'2001 Pawanish             		Fixed SPR Original
**
**  Copyright 1998, Hughes Software Systems Inc.
**
*****************************************************************************/

#include "sc_stgl.h"
/* SPR # 4988 */
/* SPR 12319, 12322, 12324 and 12499 */
/* Fix for SPR# 12553,12555,12556,12557 Start */
#define MAX_OPTIONAL_DATA_LEN 128
/* Fix for SPR# 12553,12555,12556,12557 End */
/* SPR # 4988 */
#ifdef SCCP_INCLUDE_CO_SERVICE
 
/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-CONNECT.req API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-CONNECT.req API information elements :
**
**      Fixed elements : logical_user_id
**               corr_id
**               protocol_class
**      Mandatory Variable : called_address
**      Optional elements  : credit
**                 expediate_data_selection
**                 user_data
**                 importance (ITU-T only)
**
*****************************************************************************/

return_t
sccp_parse_n_connect_request_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit   num_elems, num_elems_p;
  U8bit  param_id, param_len;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_CONNECT_REQUEST_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC: Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
  p_info->l_id =  GET_2_BYTE_LE (p_ie);
  p_ie += SCCP_ELEM_LOG_USER_ID_LEN;
  num_elems_p++;

#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->corr_id =  GET_4_BYTE_LE (p_ie);/* Change by Amaresh 2byte 4byte as on dated 20-01-16 */
#else
  p_info->corr_id = *p_ie;
#endif
  p_ie += SCCP_ELEM_CORR_ID_LEN;
  num_elems_p++;
  /* SPR 8841 -Fix Start */
  SET_CORR_ID_PRESENT (p_info);
  /* SPR 8841 -Fix End   */

  p_info->proto_class = *p_ie;
  p_ie += SCCP_ELEM_PROTOCOL_CLASS_LEN;
  num_elems_p++;

  /* Mandatory variable part */
  *(p_ie + 1) = *p_ie;
	/* SPR FIX 8192 Start */
  if (SS7_FAILURE == sccp_decode_sccp_addr ((p_ie + 1), &p_info->cd_addr))
  {
	/* SPR 12566 FIX Start */
	/* return (SS7_SUCCESS); */
	return (SS7_FAILURE);
	/* SPR 12566 FIX End */
  }
	/* SPR FIX 8192 end */
  if (*p_ie != sccp_addr_len (&p_info->cd_addr))
  {
    /* Incorrectly coded address */
    SC_A_TRC (("SCCP::SCOC: Called address length no correct.\n"));
    return (SS7_FAILURE) ;
  }
  p_ie += *p_ie + SCCP_ELEM_LEN_LEN;
  num_elems_p++;

  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      SC_A_TRC (("SCCP::SCOC: Part of the API missing.\n")) ;
      return (SS7_FAILURE);
    }
    num_elems_p++;
    switch (param_id)
    {
	/* SPR Fix 10431 starts **/
      case SCCP_ELEM_CALLING_ADDR :
        p_ie -= SCCP_ELEM_LEN_LEN ;
        *(p_ie + 1) = *p_ie ;
       if(SS7_FAILURE== sccp_decode_sccp_addr ((p_ie + 1), &p_info->cg_addr)) 
		{
			return (SS7_FAILURE);
		}
        if (*p_ie != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          SC_A_TRC (("SCCP::SCOC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }

        p_ie += *p_ie + SCCP_ELEM_LEN_LEN ;
        SC_A_TRC (("SCCP::SCOC: Responding Address Present\n")) ;
        SET_CG_PRESENT (p_info) ;
        break ;
	/* SPR Fix 10431 ends **/
      case SCCP_ELEM_CREDIT:
        if (p_info->proto_class == PROTOCOL_CLASS_2)
        {
          /* credit element present in case of protocol class 3 only */
          SC_A_TRC (("SCCP::SCOC: Unsupported parameter(%d) for CLASS 2.\n",
                     param_id));
          return (SS7_FAILURE);
        }
        p_info->credit = *p_ie;
        p_ie += param_len;
        SET_CREDIT_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: Credit present(%d)\n",p_info->credit));
        break;

      case SCCP_ELEM_EXPEDIATE_DATA_SELECTION:
        p_ie += param_len;
        SET_EXPEDIATE_DATA_SELECTION_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: ED selection present\n"));
        break;

      case SCCP_ELEM_USER_DATA:
        p_info->data.p = p_ie;
        p_info->data.len = param_len;

	/* Fix for SPR # 12553 start */
	if(p_info->data.len > MAX_OPTIONAL_DATA_LEN)
	{
	/* SPR 12319 change of maximum data length from 130 to 128 */
        	SC_A_TRC (("SCCP::SCOC: User Data length (len %d). Exceeds 128 bytes\n",p_info->data.len));
		return SS7_FAILURE;
	}
	/* Fix for SPR # 12553 End */
		
        p_ie += param_len;
        SET_DATA_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: User Data present(len %d)\n",p_info->data.len));
        break;

      case SCCP_ELEM_IMPORTANCE:
        p_info->importance = *p_ie;
        p_ie += param_len;
        SET_IMPORTANCE_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: Importance present(%d)\n",
                   p_info->importance));
        break;

      default:
        SC_A_TRC (("SCCP::SCOC: Unsupported parameter(%d).\n",param_id));
        return (SS7_FAILURE);
    }
  }

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::SCOC: Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }

}
/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-CONNECT.resp API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-CONNECT.resp API information elements :
**
**      Fixed elements : logical_user_id
**               connection_id
**               protocol_class
**      Mandatory Variable : NONE
**      Optional elements  : responding_address 
**                 credit
**                 expediate_data_selection
**                 user_data
**                 importance (ITU-T only)
**
*****************************************************************************/
return_t
sccp_parse_n_connect_response_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;
  U8bit  param_id, param_len;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_CONNECT_RESPONSE_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC: Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
  p_info->l_id =  GET_2_BYTE_LE (p_ie);
  p_ie += SCCP_ELEM_LOG_USER_ID_LEN;
  num_elems_p++;
/* SPR 6086 Fix Starts */
#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->conn_id =  GET_4_BYTE_LE (p_ie);
#else
  p_info->conn_id =  GET_2_BYTE_LE (p_ie);
#endif
/* SPR 6086 Fix End */
 
  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
  num_elems_p++;

  p_info->proto_class = *p_ie;
  p_ie += SCCP_ELEM_PROTOCOL_CLASS_LEN;
  num_elems_p++;

  /* No Mandatory variable part */


  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      SC_A_TRC (("SCCP::SCOC: Part of the API missing.\n")) ;
      return (SS7_FAILURE);
    }

    num_elems_p++ ;
    switch (param_id)
    {
      case SCCP_ELEM_RESPONDING_ADDR :
        p_ie -= SCCP_ELEM_LEN_LEN ;
        *(p_ie + 1) = *p_ie ;
	/* SPR FIX 8192 start */
       if(SS7_FAILURE== sccp_decode_sccp_addr ((p_ie + 1), &p_info->cg_addr)) 
		{
			return (SS7_FAILURE);
		}
	/*SPR FIX 8192 End */
        if (*p_ie != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          SC_A_TRC (("SCCP::SCOC: Called address length incorrect.\n")) ;
          return (SS7_FAILURE) ;
        }

        p_ie += *p_ie + SCCP_ELEM_LEN_LEN ;
        SC_A_TRC (("SCCP::SCOC: Responding Address Present\n")) ;
        SET_RG_PRESENT (p_info) ;
        break ;

      case SCCP_ELEM_CREDIT :
		if (p_info->proto_class == PROTOCOL_CLASS_2)
		{
          SC_A_TRC (("SCCP::SCOC: Credit not supported for Class 2.\n")) ;
		  return (SS7_FAILURE);
		}
        p_info->credit = *p_ie ;
        p_ie += param_len ;
        SET_CREDIT_PRESENT (p_info) ;
        SC_A_TRC (("SCCP::SCOC: Credit present(%d)\n",p_info->credit)) ;
        break ;

      case SCCP_ELEM_EXPEDIATE_DATA_SELECTION :
        p_ie += param_len ;
        SET_EXPEDIATE_DATA_SELECTION_PRESENT (p_info) ;
        SC_A_TRC (("SCCP::SCOC: ED selection present\n")) ;
        break ;

      case SCCP_ELEM_USER_DATA :
        p_info->data.p = p_ie ;
        p_info->data.len = param_len ;

	/* Fix for SPR # 12555 Start */
	if(p_info->data.len > MAX_OPTIONAL_DATA_LEN)
	{
	/* SPR 12322 change of maximum data length from 130 to 128 */
        	SC_A_TRC (("SCCP::SCOC: User Data length (len %d). Exceeds 128 bytes\n",p_info->data.len));
		return SS7_FAILURE;
	}
	/* Fix for SPR # 12555 End */
        p_ie += param_len ;
        SET_DATA_PRESENT (p_info) ;
        SC_A_TRC (("SCCP::SCOC: User Data present(len %d)\n",
                  p_info->data.len)) ;
        break ;

      case SCCP_ELEM_IMPORTANCE :
          p_info->importance = *p_ie ;
          p_ie += param_len ;
          SET_IMPORTANCE_PRESENT (p_info) ;
          SC_A_TRC (("SCCP::SCOC: Importance present(%d)\n",
                    p_info->importance)) ;
          break ;

      default:
        SC_A_TRC (("SCCP::SCOC: Unsupported parameter(%d).\n",param_id)) ;
        return (SS7_FAILURE) ;
    }
  }

  if (num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::SCOC: Incorrect number of elems(%d).\n",num_elems_p)) ;
    return (SS7_FAILURE) ;
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-CONNECT.req_typ1 API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-CONNECT.req_typ1 API information elements :
**
**      Fixed elements : logical_user_id
**               corr_id
**               protocol_class
**      Mandatory Variable : NONE
**      Optional elements  : credit
**                 expediate_data_selection
**
*****************************************************************************/

return_t
sccp_parse_n_conn_req_type1_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;
  U8bit  param_id, param_len;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_CONNECT_REQUEST_TYPE1_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC: Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
  p_info->l_id =  GET_2_BYTE_LE (p_ie);
  p_ie += SCCP_ELEM_LOG_USER_ID_LEN;
  num_elems_p++;

#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->corr_id =  GET_4_BYTE_LE (p_ie);/* Change by Amaresh 2byte 4byte as on dated 20-01-16 */
#else
  p_info->corr_id = *p_ie;
#endif
  p_ie += SCCP_ELEM_CORR_ID_LEN;
  num_elems_p++;

  p_info->proto_class = *p_ie;
  p_ie += SCCP_ELEM_PROTOCOL_CLASS_LEN;
  num_elems_p++;

  /* No Mandatory variable part */


  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      SC_A_TRC (("SCCP::SCOC: Part of the API missing.\n")) ;
      return (SS7_FAILURE);
    }
    num_elems_p++;
    switch (param_id)
    {
      case SCCP_ELEM_CREDIT:
        p_info->credit = *p_ie;
        p_ie += param_len;
        SET_CREDIT_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: credit present(%d)\n",p_info->credit));
        break;

      case SCCP_ELEM_EXPEDIATE_DATA_SELECTION:
        p_ie += param_len;
        SET_EXPEDIATE_DATA_SELECTION_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC:ED selection present\n"));
        break;

      default:
        SC_A_TRC (("SCCP::SCOC: Unsupported parameter(%d).\n",param_id));
        return (SS7_FAILURE);
    }
  }

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::SCOC: Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-CONNECT.req_typ2 API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-CONNECT.req_typ1 API information elements :
**
**      Fixed elements : logical_user_id
**               corr_id
**               protocol_class
**               opc
**               slr_number
**      Mandatory Variable : NONE
**      Optional elements  : credit
**                 reply_request_indicator
**                 refusal_indicator
**
*****************************************************************************/

return_t
sccp_parse_n_conn_req_type2_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;
  U8bit  param_id, param_len;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_CONNECT_REQUEST_TYPE2_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC: Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
  p_info->l_id =  GET_2_BYTE_LE (p_ie);
  p_ie += SCCP_ELEM_LOG_USER_ID_LEN;
  num_elems_p++;

#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->corr_id =  GET_4_BYTE_LE (p_ie);/* Change by Amaresh 2byte 4byte as on dated 20-01-16 */
#else
  p_info->corr_id = *p_ie;
#endif
  p_ie += SCCP_ELEM_CORR_ID_LEN;
  num_elems_p++;

  p_info->proto_class = *p_ie;
  p_ie += SCCP_ELEM_PROTOCOL_CLASS_LEN;
  num_elems_p++;

  p_info->opc = GET_PC(p_ie);

  if ( (COMPARE_ITU) || (COMPARE_JAPANESE) || COMPARE_ETSI)
  	p_ie += SCCP_ELEM_ITU_ETSI_POINT_CODE_LEN;

  if (COMPARE_ANSI || COMPARE_BCGR || COMPARE_CHINESE)  /* SPR # 2612 Fix: added COMPARE_BCGR */
  	p_ie += SCCP_ELEM_ANSI_POINT_CODE_LEN;

  num_elems_p++;

  p_info->slr = GET_3_BYTE_LE(p_ie);
  p_ie += SCCP_ELEM_LOCAL_REF_LEN;
  num_elems_p++;

  /* No Mandatory variable part */


  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      SC_A_TRC (("SCCP::SCOC: Part of the API missing.\n")) ;
      return (SS7_FAILURE);
    }

    num_elems_p++;
    switch (param_id)
    {
      case SCCP_ELEM_CREDIT:
        p_info->credit = *p_ie;
        p_ie += param_len;
        SET_CREDIT_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: credit present(%d)\n",p_info->credit));
        break;

      case SCCP_ELEM_RPLY_REQ_INDICATOR:
        p_ie += param_len;
        SET_RPLY_REQ_INDICATOR_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: Reply_request_ind present\n"));
        break;

      case SCCP_ELEM_REFUSAL_REASON:
        p_ie += param_len;
        SET_REFUSAL_INDICATOR_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: Refusal_ind present\n"));
        break;

      case SCCP_ELEM_LOG_USER_ID_O:
        p_info->l_id_o = GET_2_BYTE_LE (p_ie);
        p_ie += param_len;
        SET_L_ID_O_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC: Logical User Id Outgoing[%d] Present\n", 
            p_info->l_id_o));
        break;

      default:
        SC_A_TRC (("SCCP::SCOC: Unsupported parameter(%d).\n",param_id));
        return (SS7_FAILURE);
    }
  }

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::SCOC: Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-DATA.req API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-DATA.req API information elements :
**
**      Fixed elements : connection_id
**      Mandatory Variable : user_data
**      Optional elements  : importance
**
*****************************************************************************/

return_t
sccp_parse_n_data_request_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;
  U8bit  param_id, param_len;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_DATA_REQUEST_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC:Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
/* SPR 6086 Fix Start */
#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->conn_id =  GET_4_BYTE_LE (p_ie);
#else
  p_info->conn_id =  GET_2_BYTE_LE (p_ie);
#endif
/* SPR 6086 Fix Ends */
  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
  num_elems_p++;

  /* No Mandatory variable part */
  p_info->data.len = GET_2_BYTE_LE (p_ie);
  p_ie += SCCP_ELEM_LEN_LEN;
  if ((p_ie + p_info->data.len) > p_api_end)
  {
    SC_A_TRC (("SCCP::SCRC:Part of the API missing.\n")) ;
    return (SS7_FAILURE);
  }

  /* SPR 12500 FIX Start */
  if(p_info->data.len<MIN_DATA_LEN)
	return (SS7_FAILURE);
  /* SPR 12500 FIX End */

  p_info->data.p = p_ie;
  p_ie += p_info->data.len;
  num_elems_p++;


  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      SC_A_TRC (("SCCP::SCRC:Part of the API missing.\n")) ;
      return (SS7_FAILURE);
    }

    num_elems_p++;
    switch (param_id)
    {
      case SCCP_ELEM_IMPORTANCE:
          p_info->importance = *p_ie;
          p_ie += param_len;
          SET_IMPORTANCE_PRESENT (p_info);
          SC_A_TRC (("SCCP::SCOC: Importance present(%d)",p_info->importance));
          break;

      default:
        SC_A_TRC (("SCCP::Unsupported parameter(%d).\n",param_id));
        return (SS7_FAILURE);
    }
  }

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-ED_DATA.req API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-DATA.req API information elements :
**
**      Fixed elements : connection_id
**      Mandatory Variable : user_data
**      Optional elements  : NONE
**
*****************************************************************************/

return_t
sccp_parse_n_ed_data_request_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_ED_REQUEST_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC:Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->conn_id =  GET_4_BYTE_LE (p_ie);
#else
  p_info->conn_id =  GET_2_BYTE_LE (p_ie);
#endif
  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
  num_elems_p++;

  /* No Mandatory variable part */
  p_info->data.len = GET_2_BYTE_LE (p_ie);

  /* SPR 1771: Start
   * Data length of upto 32 octets are allowed */
  /*Fix for  SPR No : 12561 , 12562 start 
     Data length with Zero value also not allowed */
  if (p_info->data.len == 0 )
  {
    SC_A_TRC (("SCCP::SCOC: 0 octet of user data is not allowed .\n")) ;
    return (SS7_FAILURE);
  }
  /* Fix for SPR No : 12561 ,12562 End */

  if (p_info->data.len > MAX_ED_DATA_LEN) 
  {
    SC_A_TRC (("SCCP::SCOC:More than 32 octets of user data.\n")) ;
    return (SS7_FAILURE);
  }
  /* SPR 1771: End */

  p_ie += SCCP_ELEM_LEN_LEN;
  if ((p_ie + p_info->data.len) > p_api_end)
  {
    SC_A_TRC (("SCCP::SCOC:Part of the API missing.\n")) ;
    return (SS7_FAILURE);
  }

  p_info->data.p = p_ie;
  p_ie += p_info->data.len;
  num_elems_p++;

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-RESET.req API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-DATA.req API information elements :
**
**      Fixed elements : connection_id
**               reason_for_reset
**      Mandatory Variable : NONE
**      Optional elements  : NONE
**
*****************************************************************************/

return_t
sccp_parse_n_reset_request_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_RESET_REQUEST_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC:Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->conn_id =  GET_4_BYTE_LE (p_ie);
#else
  p_info->conn_id =  GET_2_BYTE_LE (p_ie);
#endif
  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
  num_elems_p++;

  p_info->reset_cause =  *p_ie;
  p_ie += SCCP_ELEM_RESET_CAUSE_LEN;
  num_elems_p++;

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-RESET.resp API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-DATA.resp API information elements :
**
**      Fixed elements : connection_id
**      Mandatory Variable : NONE
**      Optional elements  : NONE
**
*****************************************************************************/

return_t
sccp_parse_n_reset_resp_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_RESET_RESPONSE_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC:Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->conn_id =  GET_4_BYTE_LE (p_ie);
#else
  p_info->conn_id =  GET_2_BYTE_LE (p_ie);
#endif
  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
  num_elems_p++;

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-DISCONNECT.req API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-DATA.resp API information elements :
**
**      Fixed elements : connection_id
**               disconnect_reason
**      Mandatory Variable : NONE
**      Optional elements  : responding_address
**                 user_data
**                 logical_user_id
**                 corr_id
**                 importance
**
*****************************************************************************/

return_t
sccp_parse_n_disconnect_request_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;
  U8bit  param_id, param_len;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_DISCONNECT_REQUEST_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC:Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->conn_id =  GET_4_BYTE_LE (p_ie);
#else
  p_info->conn_id =  GET_2_BYTE_LE (p_ie);
#endif
  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
  num_elems_p++;

  p_info->rel_cause = *p_ie;
  p_ie += SCCP_ELEM_REFUSAL_CAUSE_LEN;
  num_elems_p++;

  /* No Mandatory variable part */

  /* Optional part */
  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      SC_A_TRC (("SCCP::SCRC:Part of the API missing.\n")) ;
      return (SS7_FAILURE);
    }

    num_elems_p++;
    switch (param_id)
    {
      case SCCP_ELEM_RESPONDING_ADDR:
        p_ie -= SCCP_ELEM_LEN_LEN;
        *(p_ie + 1) = *p_ie;
		/* SPR FIX 8192 start  */
        if (SS7_FAILURE ==sccp_decode_sccp_addr ((p_ie + 1), &p_info->cg_addr))
		{
			return (SS7_FAILURE);
		}
        if (*p_ie != sccp_addr_len (&p_info->cg_addr))
        {
          /* Incorrectly coded address */
          SC_A_TRC (("SCCP::SCOC:Called address length no correct.\n"));
          return (SS7_FAILURE);
        }
        p_ie += *p_ie + SCCP_ELEM_LEN_LEN;
        SET_RG_PRESENT (p_info);
        break;

      case SCCP_ELEM_USER_DATA:
        p_info->data.p = p_ie;
        p_info->data.len = param_len;
	/* Fix for SPR # 12557 Start */
	if(p_info->data.len > MAX_OPTIONAL_DATA_LEN)
	{
	/* SPR 12499 change of maximum data length from 130 to 128 */
        	SC_A_TRC (("SCCP::SCOC: User Data length (len %d). Exceeds 128 bytes\n",p_info->data.len));
		return SS7_FAILURE;
	}
        p_ie += param_len;
	/* Fix for SPR # 12557 End */
        SET_DATA_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC:User Data present(len %d)",p_info->data.len));
        break;

      case SCCP_ELEM_LOG_USER_ID:
        p_info->l_id = GET_2_BYTE_LE(p_ie);
        p_ie += param_len;
/*        SET_L_ID_PRESENT (p_info); */
       /* SC_A_TRC (("SCCP::SCOC:logical user id present(%d)",p_info->credit)); commented Amaresh */
        SC_A_TRC (("SCCP::SCOC:logical user id present(%d)",p_info->l_id));
        break;

      case SCCP_ELEM_CORR_ID:
#ifdef SCCP_CONNECTION_ID_CHANGES
  			p_info->corr_id =  GET_4_BYTE_LE (p_ie);
#else
  			p_info->corr_id =  GET_2_BYTE_LE (p_ie);
#endif
#if 0
#ifdef SCCP_CONNECTION_ID_CHANGES
        p_info->corr_id = GET_2_BYTE_LE(p_ie);
#else
        p_info->corr_id = *p_ie;
#endif
#endif /* Orig code Amaresh Commented */
        p_ie += param_len;
       /* SET_CORR_ID_PRESENT (p_info); */
	/* SPR 9126 - Fix Start */
        /*SC_A_TRC (("SCCP::SCOC:ED selection present"));*/
        SC_A_TRC (("SCCP::SCOC:Correlation id present"));
	/* SPR 9126 - Fix End   */
        break;

      case SCCP_ELEM_IMPORTANCE:
          p_info->importance = *p_ie;
          p_ie += param_len;
          SET_IMPORTANCE_PRESENT (p_info);
          SC_A_TRC (("SCCP::SCOC:Importance present(%d)",p_info->importance));
          break;

      default:
        SC_A_TRC (("SCCP::Unsupported parameter(%d).\n",param_id));
        return (SS7_FAILURE);
    }
  }

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
}

/*****************************************************************************
**
**  FUNCTION :
**      Handles the N-INFORM.req API from NSU.
**
******************************************************************************
**
**  DESCRIPTION :
**    N-DATA.resp API information elements :
**
**      Fixed elements : connection_id
**               inf_reason
**      Mandatory Variable : NONE
**      Optional elements  : proto_class
**                 credit
**
*****************************************************************************/

return_t
sccp_parse_n_inform_request_api
#ifdef ANSI_PROTO
  (U8bit     *p_api,
   msg_info_t *p_info)
#else
  (p_api, p_info)
  U8bit    *p_api;
  msg_info_t  *p_info;
#endif
{

  U8bit  *p_api_end, *p_ie;
  U8bit  num_elems, num_elems_p;
  U8bit  param_id, param_len;

  num_elems_p = 0;
  p_api_end = p_api + GET_API_LEN (p_api);
  num_elems = GET_API_NELEM(p_api);

  p_ie = p_api + API_HEADER_LEN;

  p_info->flag   = SS7_NULL;
  p_info->route_failure_flag = SS7_FALSE; /* SPR # 2579 Fix */

  p_info->p_api   = p_api;
  p_info->nw_id   = DEFAULT_NW_ID;

  if ((p_ie + SCCP_N_INFORM_REQUEST_MIN_LEN) > p_api_end)
  {
    /* API in error */
    SC_A_TRC (("SCCP:SCOC:Not a complete API.\n"));
    return (SS7_FAILURE);
  }

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  p_info->conn_id =  GET_4_BYTE_LE (p_ie);
#else
  p_info->conn_id =  GET_2_BYTE_LE (p_ie);
#endif
  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
  num_elems_p++;

  p_info->inf_reason = *p_ie;
  p_ie += SCCP_ELEM_INF_REASON_LEN;
  num_elems_p++;

  /* No Mandatory variable part */

  /* Optional part */
  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      SC_A_TRC (("SCCP::SCRC:Part of the API missing.\n")) ;
      return (SS7_FAILURE);
    }

    num_elems_p++;
    switch (param_id)
    {
      case SCCP_ELEM_PROTOCOL_CLASS:
        p_info->proto_class = *p_ie;
        p_ie += param_len;
        SET_PROTOCOL_CLASS_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC:protocol class present(%d)",p_info->credit));
        break;

      case SCCP_ELEM_CREDIT:
        p_info->credit = *p_ie;
        p_ie += param_len;
        SET_CREDIT_PRESENT (p_info);
        SC_A_TRC (("SCCP::SCOC:credit present(%d)", p_info->credit));
        break;

      default:
        SC_A_TRC (("SCCP::Unsupported parameter(%d).\n",param_id));
        return (SS7_FAILURE);
    }
  }

  if ( num_elems_p == num_elems)
    return (SS7_SUCCESS);
  else
  {
    SC_A_TRC (("SCCP::Incorrect number of elems(%d).\n",num_elems_p));
    return (SS7_FAILURE);
  }
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
