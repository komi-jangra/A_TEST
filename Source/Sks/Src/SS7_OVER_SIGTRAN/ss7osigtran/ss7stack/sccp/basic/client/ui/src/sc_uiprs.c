/******************************************************************************
**      FUNCTION:
**          Functions for parsing the API's associated with SCCP stack entity.
**
*******************************************************************************
**
**      FILE NAME:
**          sc_uiprs.c
**      
**      DESCRIPTION:
**          The User Interface module provides a functional interface for:
**          (1)Performing syntax and semantic checks on the invoked API. All 
**             static checks on the API header and elements are performed as 
**             a part of this.
**          (2)Validity check on API, based on whether advanced functions are 
**             to be made avaliable to the user or not.         
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**           
**      09Jul'00   Ramu Kandula	               Fixed SPR # 4046
**      07Jun'00   Ramu Kandula	               Fixed SPR # 3783
**      30May'00   Ramu Kandula	               Changed gen_parse_fn to 
**                                             sccp_gen_parse_fn 
**      30May'00   Ramu Kandula	               Changed len_t to s7_len_t 
**      30May'00   Ramu Kandula	               Merged Redn Branch 
**      07Feb'99   Sudipta Pattar			   Adding Ericsson changes
**      16Aug'98   Praneet Khare               Adding UI code for
**                                             SCCP ConnOriented
**      12Feb98    GAURAV.TANEJA               ORIGINAL
**
**      Copyright 1998, Hughes Software Systems, Inc.
**
******************************************************************************/

#include "sc_s7gl.h"

#include "sc_error.h"
#include "sc_api.h"

#include "sc_uiprs.h"
#include "sc_uipro.h"

/*****************************************************************************
**
** Data Structure : sccp_client_standard
**
** Description :
** This data structure stores the standard during initialization
**
******************************************************************************/

U8bit sccp_client_standard = STACK_ITU ;
Boolean fixed_length = SS7_TRUE ;

/*****************************************************************************
**
******************************************************************************/

return_t 
sccp_init_su_client
#ifdef ANSI_PROTO
  (U8bit standard)
#else
  (standard)
  U8bit  standard;
#endif
{
  if (standard == STACK_ITU)
  {
    sccp_client_standard = STACK_ITU;
    return (SS7_SUCCESS);
  }
  else  if (standard == STACK_ETSI)
  {
    sccp_client_standard = STACK_ETSI;
    return (SS7_SUCCESS);
  }
  else if (standard == STACK_ANSI)
  {
    sccp_client_standard = STACK_ANSI;
    return (SS7_SUCCESS);
  }
  else if (standard == STACK_BCGR)
  {
    sccp_client_standard = STACK_BCGR;
    return (SS7_SUCCESS);
  }
  else
  {
    return (SS7_FAILURE);
  }
}
 
/***************************************************************************** 
       Extraction routines for SCCP service user API elements 
*****************************************************************************/

/*****************************************************************************
**  FUNCTION:
**     Extraction routine for U8bit type elements.
**  DESCRIPTION:
**     This function extracts U8bit element from the buffer pointed to by 
**     p_buffer and stores it in the union elem_val_t for further checks.  
**
*****************************************************************************/

void
xtract_U8bit
#ifdef ANSI_PROTO
  (buffer_t     **p_buffer,
   elem_val_t   *p_val)
#else
  (p_buffer, p_val)
  buffer_t     **p_buffer ;
  elem_val_t   *p_val ;
#endif
{
  p_val->U8bit_val=(U8bit)(**p_buffer);
  ++(*p_buffer);
} 

/******************************************************************************
**  FUNCTION:
**     Extraction routine for U16bit type elements.
**  DESCRIPTION:
**     This function extracts U16bit element from the buffer pointed to by 
**     p_buffer and stores it in the union elem_val_t for further checks.  
**
******************************************************************************/

void
xtract_U16bit
#ifdef ANSI_PROTO
  (buffer_t    **p_buffer,
    elem_val_t  *p_val)
#else
  (p_buffer, p_val)
  buffer_t    **p_buffer;
  elem_val_t  *p_val;
#endif
{
  p_val->U16bit_val=(U16bit)(**p_buffer);
  ++(*p_buffer);
  p_val->U16bit_val|=(((U16bit)(**p_buffer))<<8) & 0xff00;
  ++(*p_buffer);
}
/******************************************************************************
**  FUNCTION:
**     Extraction routine for 24bit type elements.
**  DESCRIPTION:
**     This function extracts U16bit element from the buffer pointed to by 
**     p_buffer and stores it in the union elem_val_t for further checks.  
**
******************************************************************************/

void
xtract_U24bit
#ifdef ANSI_PROTO
  (buffer_t    **p_buffer,
   elem_val_t  *p_val)
#else
  (p_buffer, p_val)
  buffer_t    **p_buffer;
  elem_val_t  *p_val;
#endif
{
  p_val->U32bit_val=(U32bit)(**p_buffer);
  ++(*p_buffer);
  p_val->U32bit_val|=(((U32bit)(**p_buffer))<<8) & 0xff00;
  ++(*p_buffer);
  p_val->U32bit_val|=(((U32bit)(**p_buffer))<<16) & 0xff0000L;
  ++(*p_buffer);
}


/******************************************************************************
**  FUNCTION:
**     Extraction routine for U32bit type elements.
**  DESCRIPTION:
**     This function extracts U32bit element from the buffer pointed to by 
**     p_buffer and stores it in the union elem_val_t for further checks.  
**
******************************************************************************/

void
xtract_U32bit
#ifdef ANSI_PROTO
  (buffer_t    **p_buffer,
   elem_val_t  *p_val)
#else
  (p_buffer, p_val)
  buffer_t    **p_buffer;
  elem_val_t  *p_val;
#endif
{
  U8bit offset;

  p_val->U32bit_val=(U32bit)(**p_buffer);
  for(offset=1;offset<4;++offset)
     p_val->U32bit_val|=((U32bit)(*(*p_buffer+offset)))<<8*offset;   
  *p_buffer+=4;
}

/******************************************************************************
**  FUNCTION:
**     Extraction routine for variable length type elements.
**  DESCRIPTION:
**     This function extracts variable length type elements from the buffer 
**     pointed to by p_buffer and stores it in the union elem_val_t for 
**     further checks.  
**
******************************************************************************/

void
xtract_vl_elem
#ifdef ANSI_PROTO
  (buffer_t   **p_buffer,
   elem_val_t *p_val)
#else
  (p_buffer, p_val)
  buffer_t   **p_buffer;
  elem_val_t *p_val;
#endif
{
  fixed_length = SS7_FALSE ;
  p_val->var_len_val.len=(U16bit)**p_buffer;
  p_val->var_len_val.len|=((U16bit)(*(*p_buffer+1)))<<8;
  p_val->var_len_val.val=((U8bit*)*p_buffer)+2;
  *p_buffer+=(p_val->var_len_val.len+2);
}

/*****************************************************************************
**  FUNCTION:
**     Extraction routine for U8bit type elements.
**  DESCRIPTION:
**     This function extracts U8bit element from the buffer pointed to by 
**     p_buffer and stores it in the union elem_val_t for further checks.  
**
*****************************************************************************/

void
xtract_U8bit_opt
#ifdef ANSI_PROTO
  (buffer_t     **p_buffer,
   elem_val_t   *p_val)
#else
  (p_buffer, p_val)
  buffer_t     **p_buffer ;
  elem_val_t   *p_val ;
#endif
{
  U16bit len;
  fixed_length = SS7_TRUE ;
  len = (U16bit)(**p_buffer) & 0x00ff;
  (*p_buffer)++;
  len |= (U16bit)((**p_buffer) << 8) & 0xff00;
  (*p_buffer)++;
  if (len != 1)
  {
	fixed_length = SS7_FALSE ;
	return;
  }
  p_val->U8bit_val=(U8bit)(**p_buffer);
  ++(*p_buffer);
} 

/******************************************************************************
**  FUNCTION:
**     Extraction routine for U16bit type elements.
**  DESCRIPTION:
**     This function extracts U16bit element from the buffer pointed to by 
**     p_buffer and stores it in the union elem_val_t for further checks.  
**
******************************************************************************/

void
xtract_U16bit_opt
#ifdef ANSI_PROTO
  (buffer_t    **p_buffer,
    elem_val_t  *p_val)
#else
  (p_buffer, p_val)
  buffer_t    **p_buffer;
  elem_val_t  *p_val;
#endif
{
  U16bit len ;
  fixed_length = SS7_TRUE ;
  len = (U16bit)(**p_buffer) & 0x00ff;
  (*p_buffer)++;
  len |= (U16bit)((**p_buffer) << 8) & 0xff00;
  (*p_buffer)++;
  if (len != 2)
  {
	fixed_length = SS7_FALSE ;
	return;
  }
  p_val->U16bit_val=(U16bit)(**p_buffer);
  ++(*p_buffer);
  p_val->U16bit_val|=(((U16bit)(**p_buffer))<<8) & 0xff00;
  ++(*p_buffer);
}

/******************************************************************************
**  FUNCTION:
**     None. 
**  DESCRIPTION:
**     This function acts like a dummy routine. It does not perform any    
**     comparison checks.
**
******************************************************************************/

return_t 
NULL_func
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  return SS7_SUCCESS;
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_SSN or 
**  DESCRIPTION:
**
******************************************************************************/

return_t 
chk_local_ss
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
U32bit pc;
U8bit  ssn;

  if ((sccp_client_standard == STACK_ANSI) || 
  	(sccp_client_standard == STACK_BCGR))
  {
    pc = (U32bit)(p_val->U32bit_val & 0x00FFFFFFL);
    ssn = (U8bit)((p_val->U32bit_val >> 24) & 0x000000FFL);
  }
  else
  {
	pc = (U32bit)(p_val->U32bit_val & 0x0000FFFFL);
    ssn = (U8bit)((p_val->U32bit_val >> 16) & 0x000000FFL);
  }

  if (!pc)
  {
      *p_ecode=ESCCP_INVALID_POINT_CODE;
      return SS7_FAILURE;
  }
  if ((sccp_client_standard == STACK_ITU) ||
      (sccp_client_standard == STACK_ETSI))
  {
    if (pc & 0xc000)
    {
      *p_ecode=ESCCP_INVALID_POINT_CODE;
      return SS7_FAILURE;
    }
  }

  /* Check if SSN = 0 */
  if (ssn == 0)
  {
     *p_ecode=ESCCP_INVALID_SSN;
     return SS7_FAILURE;
  }

  return SS7_SUCCESS;
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_CALLED_ADDR or 
**     SCCP_ELEM_DESTINATION_ADDR. 
**  DESCRIPTION:
**     Performs static checks on called_addr or calling_addr elements
**     as per ITU-T Q.713 specifications.
**
******************************************************************************/

return_t 
chk_elem_called_addr
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  /* set local pointer to address_indicator octet */
  U8bit *p_local=p_val->var_len_val.val;

  /* SPR # 3783 Fix Start */

  if ((sccp_client_standard == STACK_ANSI) || 
  	(sccp_client_standard == STACK_BCGR))
  {
  	/* check if ssn is present as per address_indicator */
  	if(*p_local & 0x01)
  	{  
    	/*check if called_addr element has address_indicator+ssn:atleast 2 octets*/ 
    	if(p_val->var_len_val.len<0x2)
    	{
      		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
      		return SS7_FAILURE;
    	}        
    }

  	/* check if both SSN and SPC are present as per addr_indicator octet */
  	if(*p_local & 0x02)
  	{  
    	if(*p_local & 0x01)
    	{  
      		if(p_val->var_len_val.len<0x5)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
    	else
    	{
      		if(p_val->var_len_val.len<0x4)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
  	}
    
	/** SPR # 4046 Fix Start **/
	/** This check must not be done as message return procedure must
	*** be initiated if the address contains insufficient information 
	**/
#if 0
  	if (*p_local & 0x40) /* routing on SSN */
  	{
    	if (!(*p_local & 0x01))
    	{
       		*p_ecode=ESCCP_INVALID_CALLED_ADDR;
       		return SS7_FAILURE;
    	}

    	if ((!(*p_local & 0x02)) && (!(*p_local & 0x3c))) /* atleast one of GT/PC is
                                                        required */
    	{
       		*p_ecode=ESCCP_INVALID_CALLED_ADDR;
       		return SS7_FAILURE;
    	}
  	}
  	else  
  	{
    	if (!(*p_local & 0x3c)) /* GT not present */
    	{
       		*p_ecode=ESCCP_INVALID_CALLED_ADDR;
       		return SS7_FAILURE;
    	}
  	}
#endif
	/** SPR # 4046 Fix End **/

  }
  else if ((sccp_client_standard == STACK_ITU) ||
      		(sccp_client_standard == STACK_ETSI))
  {
  	/* check if signalling point code is present as per address_indicator */
  	if(*p_local & 0x01)
  	{  
    	/*check if called_addr element has address_indicator+spc:atleast 3 octets*/ 
    	if(p_val->var_len_val.len<0x3)
    	{
      		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
      		return SS7_FAILURE;
    	}        
     
      	/* check validity of the most significant octet of SPC */
      	if((*(p_local+2) & 0xc0)!=0x0)
      	{
        	*p_ecode=ESCCP_INVALID_POINT_CODE;
        	return SS7_FAILURE;
      	}
    }

  	/* check if both SSN and SPC are present as per addr_indicator octet */
  	if(*p_local & 0x02)
  	{  
    	if(*p_local & 0x01)
    	{  
      		if(p_val->var_len_val.len<0x4)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
    	else
    	{
      		if(p_val->var_len_val.len<0x2)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
  	}

#if defined (SCCP_ITU) && defined (SCCP_ERICSSON_ITU)
  	/* Ericsson changes - check if GTI is 0000 or 0100 */
  	if (sccp_client_standard == STACK_ITU)
  	{
    	if ((*p_local & 0x3c) && (!(*p_local & 0x10))) 
    	{
			*p_ecode=ESCCP_INVALID_ERICSSON_GTI;
			return SS7_FAILURE;
    	}
  	}
#endif
	
    
	/** SPR # 4046 Fix Start **/
	/** This check must not be done as message return procedure must
	*** be initiated if the address contains insufficient information 
	**/
#if 0
  	if (*p_local & 0x40) /* routing on SSN */
  	{
    	if (!(*p_local & 0x02))
    	{
       		*p_ecode=ESCCP_INVALID_CALLED_ADDR;
       		return SS7_FAILURE;
    	}

    	if ((!(*p_local & 0x01)) && (!(*p_local & 0x3c))) /* atleast one of GT/PC is
                                                        required */
    	{
       		*p_ecode=ESCCP_INVALID_CALLED_ADDR;
       		return SS7_FAILURE;
    	}
  	}
  	else  
  	{
    	if (!(*p_local & 0x3c)) /* GT not present */
    	{
       		*p_ecode=ESCCP_INVALID_CALLED_ADDR;
       		return SS7_FAILURE;
    	}

  	}
#endif

#if defined (SCCP_ITU) && defined (SCCP_ERICSSON_ITU)
		/* Ericsson changes - check if SSN is present while routing on GT */
    	if (sccp_client_standard == STACK_ITU)
    	{
  			if (! (*p_local & 0x40) ) /* routing on GT */
			{
      			if (!(*p_local & 0x02))
      			{
         			*p_ecode=ESCCP_INVALID_CALLED_ADDR;
         			return SS7_FAILURE;
      			}
			}
    	}
#endif

	/** SPR # 4046 Fix End **/
  }
  else
  {
      /* Invalid Client Standard */
      *p_ecode=ESS7_INVALID_STANDARD;
      return SS7_FAILURE;
  }

  /* SPR # 3783 Fix End */

/* no errors in static checks */
  return SS7_SUCCESS;
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_CALLING_ADD or 
**     SCCP_ELEM_RESPONDING_ADDR. 
**  DESCRIPTION:
**     Performs static checks on calling_addr elements
**     as per ITU-T Q.713 specifications.
**
******************************************************************************/

return_t 
chk_elem_calling_addr
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  /* set local pointer to address_indicator octet */
  U8bit *p_local=p_val->var_len_val.val;

  /* SPR # 3783 Fix Start */

  if ((sccp_client_standard == STACK_ANSI) || 
  	(sccp_client_standard == STACK_BCGR))
  {
  	/* check if ssn is present as per address_indicator */
  	if(*p_local & 0x01)
  	{  
    	/*check if called_addr element has address_indicator+ssn:atleast 2 octets*/ 
    	if(p_val->var_len_val.len<0x2)
    	{
      		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
      		return SS7_FAILURE;
    	}        
    }

  	/* check if both SSN and SPC are present as per addr_indicator octet */
  	if(*p_local & 0x02)
  	{  
    	if(*p_local & 0x01)
    	{  
      		if(p_val->var_len_val.len<0x5)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
    	else
    	{
      		if(p_val->var_len_val.len<0x4)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
  	}
  }
  else if ((sccp_client_standard == STACK_ITU) ||
      		(sccp_client_standard == STACK_ETSI))
  {
  	/* check if signalling point code is present as per address_indicator */
  	if(*p_local & 0x01)
  	{  
    	/*check if called_addr element has address_indicator+spc:atleast 3 octets*/ 
    	if(p_val->var_len_val.len<0x3)
    	{
      		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
      		return SS7_FAILURE;
    	}        
     
     	/* check validity of the most significant octet of SPC */
     	if((*(p_local+2) & 0xc0)!=0x0)
     	{
       		*p_ecode=ESCCP_INVALID_POINT_CODE;
       		return SS7_FAILURE;
     	}
  	}

  	/* check if both SSN and SPC are present as per addr_indicator octet */
  	if(*p_local & 0x02)
  	{  
    	if(*p_local & 0x01)
    	{  
      		if(p_val->var_len_val.len<0x4)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
    	else
    	{
      		if(p_val->var_len_val.len<0x2)
      		{
        		*p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
        		return SS7_FAILURE;
      		}
    	}
  	}

#if defined (SCCP_ITU) && defined (SCCP_ERICSSON_ITU)
  	/* Ericsson changes - check if GTI is 0000 or 0100 */
  	if (sccp_client_standard == STACK_ITU)
  	{
    	if ((*p_local & 0x3c) && (!(*p_local & 0x10)))
    	{
        	*p_ecode=ESCCP_INVALID_ERICSSON_GTI;
        	return SS7_FAILURE;
    	}
  	}
#endif
  }
  else
  {
      /* Invalid Client Standard */
      *p_ecode=ESS7_INVALID_STANDARD;
      return SS7_FAILURE;
  }

  /* SPR # 3783 Fix End */

  /* no errors in static checks */
  return SS7_SUCCESS;
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_SEQUENCE_CONTROL 
**  DESCRIPTION:
**     Performs static checks on sequence control element by 
**     considering all possible values.  
**
******************************************************************************/

return_t 
chk_elem_val_seq_ctrl
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if (p_val->U8bit_val>15)
  {
     *p_ecode=ESCCP_INVALID_SEQUENCE_CONTROL;
     return SS7_FAILURE;
  }
  /* no errors in static checks */  
  return SS7_SUCCESS;
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_RETURN_OPTION 
**  DESCRIPTION:
**     Performs static checks on return option element by 
**     considering all possible values.  
**
******************************************************************************/

return_t 
chk_elem_val_return_opt
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if ((p_val->U8bit_val != SCCP_DISCARD_MSG) &&
      (p_val->U8bit_val != SCCP_RETURN_MSG))
  {
     *p_ecode=ESCCP_INVALID_RETURN_OPTION;
     return SS7_FAILURE;
  }
  /* no errors in static checks */  
  return SS7_SUCCESS;
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_IMPORTANCE 
**  DESCRIPTION:
**     Performs static checks on importance element by 
**     considering all possible values.  
**
******************************************************************************/

return_t 
chk_elem_val_importance
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if ((sccp_client_standard == STACK_ITU) ||
	  (sccp_client_standard == STACK_ETSI))
  {
  /* Ericsson changes: importance parameter not supported */
#if defined (SCCP_ITU) && defined (SCCP_ERICSSON_ITU)
    if (sccp_client_standard == STACK_ITU)
    {
       *p_ecode=ESCCP_INVALID_IMPORTANCE;
       return SS7_FAILURE;
    }
#endif 
    if (p_val->U8bit_val > 7)
    {
       *p_ecode=ESCCP_INVALID_IMPORTANCE;
       return SS7_FAILURE;
    }
  }
  else
  {
    if ((p_val->U8bit_val != 0) && (p_val->U8bit_val != 1))
    {
       *p_ecode=ESCCP_INVALID_IMPORTANCE;
       return SS7_FAILURE;
    }
  }

  /* no errors in static checks */  
  return SS7_SUCCESS;
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_AFFECTED_SIGNALLING_POINT 
**  DESCRIPTION:
**     Performs static checks on affected_signalling_point element by 
**     considering all possible values.  
**
******************************************************************************/

return_t 
chk_elem_aff_sig_pt
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
/* check most significant octet of affected SPC */
  if((U8bit)((p_val->U16bit_val>>8) & 0xc0)!=0x0) {
    *p_ecode=ESCCP_INVALID_AFFECTED_SIGNALLING_POINT;
    return SS7_FAILURE;
  } 
/* no errors in static checks */  
  return SS7_SUCCESS;
}                  


/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_AFFECTED_SUBSYSTEM  
**  DESCRIPTION:
**     Performs static checks on the affected subsystem element by 
**     considering all possible values.  
**
******************************************************************************/

return_t
chk_elem_aff_ss
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  U32bit pc;
  U8bit  ssn;

  if ((sccp_client_standard == STACK_ANSI) || 
  	(sccp_client_standard == STACK_BCGR))
  {
    pc = (U32bit)(p_val->U32bit_val & 0x00FFFFFFL);
    ssn = (U8bit)((p_val->U32bit_val >> 24) & 0x000000FFL);
  }
  else
  {
	pc = (U32bit)(p_val->U32bit_val & 0x0000FFFFL);
    if ((p_val->U32bit_val & 0x0000C000L) != 0x00000000L)
    {
      *p_ecode=ESCCP_INVALID_AFFECTED_SUBSYSTEM;
      return SS7_FAILURE;
    }

    ssn = (U8bit)((p_val->U32bit_val >> 16) & 0x000000FFL);
  }

  if(!pc) 
  {
    *p_ecode=ESCCP_INVALID_AFFECTED_SUBSYSTEM;
    return SS7_FAILURE;
  }

  /* no errors in static checks */
  return SS7_SUCCESS; 
}

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_USER_STATUS 
**  DESCRIPTION:
**     Performs static checks on user status element by 
**     considering all possible values.  
**
******************************************************************************/

return_t 
chk_elem_val_user_status
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if ((p_val->U8bit_val != SCCP_USER_IN_SERVICE) &&
      (p_val->U8bit_val != SCCP_USER_OUT_OF_SERVICE))
  {
     *p_ecode=ESCCP_INVALID_IMPORTANCE;
     return SS7_FAILURE;
  }
  /* no errors in static checks */  
  return SS7_SUCCESS;
}                  

#ifdef SCCP_INCLUDE_CO_SERVICE

/******************************************************************************
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_CREDIT 
**  DESCRIPTION:
**     Performs static checks on importance element by 
**     considering all possible values.  
**
******************************************************************************/

return_t 
chk_elem_val_credit
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if ((p_val->U8bit_val < 1) ||
      (p_val->U8bit_val > 127))
  {
    *p_ecode=ESCCP_INVALID_CREDIT;
    return SS7_FAILURE;
  }

  /* no errors in static checks */  
  return SS7_SUCCESS;
} 

/******************************************************************************
**
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_LOG_USER_ID 
**
******************************************************************************/

return_t 
chk_elem_val_log_uid
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if (p_val->U16bit_val >  0xff)
  {
     *p_ecode=ESCCP_INVALID_LOG_UID;
     return SS7_FAILURE;
  }
  /* no errors in static checks */  
  return SS7_SUCCESS;
}                  

/******************************************************************************
**
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_CORR_ID 
**
******************************************************************************/

return_t 
chk_elem_val_corr_id
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if ((p_val->U8bit_val <= 0)||(p_val->U8bit_val > 0xff))
  {
     *p_ecode=ESCCP_INVALID_CORR_ID;
     return SS7_FAILURE;
  }
  /* no errors in static checks */  
  return SS7_SUCCESS;
}                  

/******************************************************************************
**
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_PROTOCOL_CLASS 
**
******************************************************************************/

return_t 
chk_elem_val_proto_class
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if ((p_val->U8bit_val < 2) || (p_val->U8bit_val > 3))
  {
     *p_ecode=ESCCP_INVALID_PROTO_CLASS;
     return SS7_FAILURE;
  }

  /* no errors in static checks */  
  return SS7_SUCCESS;
}                  

/******************************************************************************
**
**  FUNCTION:
**     Comparison checks for SCCP_ELEM_EXPEDIATE_DATA_SELECTION 
**
******************************************************************************/

return_t 
chk_elem_val_exp_data
#ifdef ANSI_PROTO
  (elem_val_t  *p_val,
   error_t     *p_ecode)
#else
  (p_val, p_ecode)
  elem_val_t  *p_val;
  error_t     *p_ecode;
#endif
{
  if (p_val->U8bit_val != 0)
  {
     *p_ecode=ESCCP_INVALID_EXP_DATA_SELECTION;
     return SS7_FAILURE;
  }
  /* no errors in static checks */  
  return SS7_SUCCESS;
}

#endif

/******************************************************************************
**  FUNCTION:
**     Parses all types of service user API's of the SCCP stack entity. 
**  DESCRIPTION:
**     This function  performs static  checks on the API header and calls 
**     appropriate extraction and comparison routines for parsing the API.
**
******************************************************************************/

return_t
sccp_gen_parse_fn
#ifdef ANSI_PROTO
  (buffer_t  *p_buffer,
   s7_len_t  noctets,
   error_t   *p_ecode) 
#else
  (p_buffer, noctets, p_ecode)
  buffer_t  *p_buffer;
  s7_len_t  noctets;
  error_t   *p_ecode;
#endif
{
  api_info_t     *p_api_info;
  elem_val_t     elem_val;
  buffer_t       *p_loc_buffer=p_buffer;
  U8bit          elem_id;
  U8bit          elem_cnt; 
  U16bit         buffer_length;
  U8bit          num_elem_parsed=0;
  U8bit          opt_elem_cnt; 

#ifdef SCCP_ITU
  if (sccp_client_standard == STACK_ITU)
  {
    p_api_info= &api_itu_etsi_info_table[*p_buffer-SCCP_MIN_API];
  }
#endif
#ifdef SCCP_ETSI
  if (sccp_client_standard == STACK_ETSI)
  {
    switch (*p_buffer)
    {
#ifdef SCCP_INCLUDE_CO_SERVICE
      case SCCP_N_CONNECT_REQUEST:
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
      case SCCP_N_RESET_REQUEST:
      case SCCP_N_RESET_RESPONSE:
      case SCCP_N_EXPEDIATE_DATA_REQUEST:
        *p_ecode = ESCCP_UNSPECIFIED_API_FOR_ETSI ;
        return (SS7_FAILURE) ;
#endif
#endif
      default:
        break ;
    }
    p_api_info= &api_itu_etsi_info_table[*p_buffer-SCCP_MIN_API];
  }
#endif
#if defined(SCCP_ANSI) || defined(SCCP_BCGR)
  if ((sccp_client_standard == STACK_ANSI) ||
   	(sccp_client_standard == STACK_BCGR))
  {
    p_api_info= &api_ansi_info_table[*p_buffer-SCCP_MIN_API];
  }
#endif

  /* skip API ID and version field */
  p_loc_buffer+=2;

  /* check range for number of API elements */
  if((*p_loc_buffer<p_api_info->min_num_elem) ||
     (*p_loc_buffer>p_api_info->max_num_elem)) 
  {
    *p_ecode=ESS7_INVALID_NUM_API_ELEMENTS;
    return SS7_FAILURE;
  }  

  /* First byte of length */  
  ++p_loc_buffer;
  buffer_length =(U16bit)((*p_loc_buffer) & 0x00ff);
  /* Second byte of length */  
  ++p_loc_buffer;
  buffer_length |= ((U16bit)(*p_loc_buffer)<<8) & 0xff00;

  if (buffer_length != noctets)
  {
    *p_ecode=ESS7_BUFFER_LENGTH_OUT_OF_RANGE;
    return SS7_FAILURE;
  }
 
  /* check for API buffer length */
  if((buffer_length<p_api_info->min_length) ||
     (buffer_length>p_api_info->max_length)) 
  {
    *p_ecode=ESS7_BUFFER_LENGTH_OUT_OF_RANGE;
    return SS7_FAILURE;
  }   

  /* advance local buffer pointer to user data*/
  ++p_loc_buffer;

  /* check whether array bound has been exceeded */
  if(BUFFER_OVERFLOW(p_loc_buffer))
  {
    *p_ecode=ESS7_BUFFER_OVERFLOW;
    return SS7_FAILURE;  
  }

  /* check mandatory fixed elements */
  for(elem_cnt=0;elem_cnt<p_api_info->num_mf;++elem_cnt)
  {
     elem_id=p_api_info->mf_elem[elem_cnt].elem_id;

  /* extract element by call to appropriate extraction function */
     (*(p_api_info->mf_elem[elem_cnt].xtract))(&p_loc_buffer,&elem_val);

  /* check element by call to appropriate comparison function */
     if((*(p_api_info->mf_elem[elem_cnt].comp))(&elem_val,p_ecode)
       ==SS7_FAILURE)
       return SS7_FAILURE;

  /* number of elements parsed till now */
     ++num_elem_parsed;
  }


  /* check mandatory variable elements */
  for(elem_cnt=0;elem_cnt<p_api_info->num_mv;++elem_cnt)
  {

    /* check whether array bound has been exceeded */
     if(BUFFER_OVERFLOW(p_loc_buffer))
     {
       *p_ecode=ESS7_BUFFER_OVERFLOW;
       return SS7_FAILURE;
     }

     elem_id=p_api_info->mv_elem[elem_cnt].elem_id;

    /* extract element information by call to appropriate extraction function */
    (*(p_api_info->mv_elem[elem_cnt].xtract))(&p_loc_buffer,&elem_val);

    /* check length of mandatory variable element */
    if((elem_val.var_len_val.len < p_api_info->mv_elem[elem_cnt].min_length) || 
       (elem_val.var_len_val.len > p_api_info->mv_elem[elem_cnt].max_length)) 
    {
       *p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH; 
       return SS7_FAILURE;
     }        

    /* check element by call to appropriate comparison function */
    if((*(p_api_info->mv_elem[elem_cnt].comp))(&elem_val,p_ecode)
       ==SS7_FAILURE)
       return SS7_FAILURE;

    /* number of elements parsed till now */
    ++num_elem_parsed;
  }
 
  /* check whether array bound has been exceeded */
  if(BUFFER_OVERFLOW(p_loc_buffer))
  {
    *p_ecode=ESS7_BUFFER_OVERFLOW;
    return SS7_FAILURE;
  }     
 
  /* check optional elements */
  for(elem_cnt=0; p_loc_buffer<(p_buffer+buffer_length); ++elem_cnt)
  {

    elem_id = *p_loc_buffer;
    ++p_loc_buffer;

    /* check for validity of element id in api_info_table */
    for(opt_elem_cnt=0; opt_elem_cnt<p_api_info->num_opt; ++opt_elem_cnt) 
        if(elem_id==p_api_info->opt_elem[opt_elem_cnt].elem_id)
          break;
        
     if(opt_elem_cnt == p_api_info->num_opt)
     {
       /* Unsupported OPT para */
       *p_ecode=ESS7_INVALID_API_ELEMENT;  
       return SS7_FAILURE;
     }


    /* extract element by call to appropriate extraction function */
    (*(p_api_info->opt_elem[opt_elem_cnt].xtract))(&p_loc_buffer,&elem_val);

    /* check length of optional element */
	if (fixed_length == SS7_FALSE)
	{
      if(( elem_val.var_len_val.len < 
					 p_api_info->opt_elem[opt_elem_cnt].min_length) ||
         ( elem_val.var_len_val.len > 
					 p_api_info->opt_elem[opt_elem_cnt].max_length))
      {
         *p_ecode=ESS7_INVALID_API_ELEMENT_LENGTH;
         return SS7_FAILURE;
      }
	}

    /* check element by call to appropriate comparison function */
    if((*(p_api_info->opt_elem[opt_elem_cnt].comp))(&elem_val,p_ecode)
       ==SS7_FAILURE)
       return SS7_FAILURE;

    /* number of elements parsed till now */
    ++num_elem_parsed;
  }

  if (num_elem_parsed != *(p_buffer + 2))
  {
    *p_ecode=ESS7_INVALID_NUM_API_ELEMENTS;
    return SS7_FAILURE;
  }

  /* no errors in static checks */
  return SS7_SUCCESS;
}


/******************************************************************************
**  FUNCTION:
**     Parse buffer as per the API_ID and call dispatch_buffer. 
**  DESCRIPTION:
**     The function performs the following tasks:
**     (1) Checks API_ID range and its version.
**     (2) Checks source and destination ids.
**     (3) Uses API_ID as an index into api_fptr_table to call the 
**         appropriate API parsing function.
**     (4) Returns error,if call to the parsing function fails,otherwise
**         it calls the dispatch_buffer function. 
**  NOTE:
**     This function must be called after initialization of api_fptr_table
**     by call to sccp_api_fptr_table_init.  
**
*****************************************************************************/

return_t
send_to_sccp
#ifdef ANSI_PROTO
  (buffer_t    *p_buffer,
   s7_len_t    noctets,
   src_id_t    src_id,
   dst_id_t    dst_id,
   error_t     *p_ecode)
#else
  (p_buffer, noctets, src_id, dst_id, p_ecode)
  buffer_t    *p_buffer;
  s7_len_t    noctets;
  src_id_t    src_id;
  dst_id_t    dst_id;
  error_t     *p_ecode;
#endif
{
 
  /* API_ID range check */ 
  if((*p_buffer<SCCP_MIN_SU_API) || (*p_buffer>SCCP_MAX_SU_API)) {
    *p_ecode=ESS7_INVALID_API_ID;
    return EAPI_ERROR;                     
  }
  
  /* API version ID check */
  if(*(p_buffer+1)!=SCCP_VERSION_NUMBER) {
    *p_ecode=EVERSION_ID;
    return EAPI_ERROR;
  } 

  /* call to appropriate API parsing function as per API_ID  */    
  if(sccp_gen_parse_fn (p_buffer,noctets,p_ecode)==SS7_FAILURE)
    return EAPI_ERROR;

  /* call to dispatch_buffer */
  if(sccp_dispatch_buffer(p_buffer,noctets,src_id,dst_id,p_ecode)==SS7_FAILURE) 
    return ESYS_ERROR; 

  /* no API or system related errors */
  return SS7_SUCCESS;
}
