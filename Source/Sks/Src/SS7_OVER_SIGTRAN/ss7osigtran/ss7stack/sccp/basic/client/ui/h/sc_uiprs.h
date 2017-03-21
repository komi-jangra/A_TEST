/******************************************************************************
**      FUNCTION:
**          Definition of for parsing of APIs.
**
*******************************************************************************
**
**      FILE NAME:
**          sc_uiprs.h
**      
**      DESCRIPTION:
**          This file defines a generic data type which can be associated with
**          all the api elements of the SCCP stack entity.            
**         
**
**       DATE          NAME           REFERENCE            REASON    
**       ----          ----           ---------            ------
**           
**        20May'00    Ramu Kandula                       Changed len_t to 
**                                                       s7_len_t
**      12Feb98    GAURAV.TANEJA     HSS:????????         ORIGINAL
**
**
**      Copyright 1998, Hughes Software Systems, Inc.
**
******************************************************************************/

/* macro to check buffer overflow */
#define BUFFER_OVERFLOW(p_loc_buffer)   p_loc_buffer>p_buffer+buffer_length

/* variable length element type */
typedef struct {
        U16bit len;
        U8bit *val;
} var_len_elem_t;   

/* api generic element type */ 
typedef union {
        U8bit             U8bit_val;           
        U16bit            U16bit_val;
        U32bit            U32bit_val;     
        var_len_elem_t    var_len_val;
} elem_val_t;  

/* SCCP SERVICE USER API ELEMENT INFORMATION */             
typedef struct {
	U8bit	 elem_id;
        U16bit   min_length;
        U16bit   max_length;
        void     (*xtract)(buffer_t**,elem_val_t*);
        return_t (*comp)(elem_val_t*,error_t*);    
} elem_info_t;

/* SCCP SERVICE USER API INFORMATION */   
typedef struct {
        s7_len_t  		min_length;
        s7_len_t  		max_length;
        U8bit  		min_num_elem;
        U8bit  		max_num_elem;
        U8bit     	num_mf;
        elem_info_t     *mf_elem;                  
        U8bit     	num_mv; 
        elem_info_t     *mv_elem;  
        U8bit     	num_opt;
        elem_info_t     *opt_elem;
} api_info_t;

/****************************************************************************
                           extern declarations 
*****************************************************************************/
#if defined (SCCP_ITU) || defined (SCCP_ETSI)
extern  api_info_t    api_itu_etsi_info_table[];
#endif
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
extern  api_info_t    api_ansi_info_table[];
#endif
extern  return_t      (*api_fptr_table[])(buffer_t*,s7_len_t,error_t*);

