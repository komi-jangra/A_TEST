/******************************************************************************
** FUNCTION :
**	Global type definations.	
**
*******************************************************************************
**
** FILE NAME :
**             s7_typ.h
**
** DESCRIPTION : 
**              Contain global type definitions.
**
**      DATE               NAME            REFERENCE        REASON
**      ----               ----            ---------        ------
**      01/04/98           Anil K.        		    NULL/OK/TRUE/FALSE 
**							    undef first
**      05/12/97           Anil K.         HSS:20800008     Initial
**      25Apr02            Mudit Seth      -----------   SPR 8667 Fix  
**      28Oct02            Suyash Tripathi -----------   SPR 10419 Fix  
**      20Aug03            Hitesh Sharma   -----------   SPR 12497 Fix
**
** Copyright 1997, Hughes Software System Ltd.
******************************************************************************/
#ifndef _S7_TYP_H_
#define _S7_TYP_H_

typedef char 			Boolean;

/* SPR 10419 - Fix Start */
/* This type Ulong will get changed to 64 bit and 32 bit on 64 bit and 32 bit machines accordingly */ 
typedef unsigned long int     	Ulong;
/* SPR 10419 - Fix End   */

#ifndef __GPRS_GLOB_DEF
/* SPR# 7130 Fix starts */
/*typedef unsigned long int     	U32bit;*/
typedef unsigned int            U32bit;
/* SPR# 7130 Fix ends */

typedef unsigned short int 	U16bit;
typedef unsigned char 		U8bit;
typedef long int 		S32bit;
typedef short int 		S16bit;
/* SPR# 8667 Fix starts */
/*typedef char 			S8bit;*/
typedef signed char 	S8bit;
/* SPR# 8667 Fix ends */
#endif

typedef U8bit			return_t;
typedef void*			pvoid;

#ifdef SS7_TRUE
#undef SS7_TRUE
#endif
#define SS7_TRUE                1	

#ifdef SS7_FALSE
#undef SS7_FALSE
#endif
#define SS7_FALSE		0	

#define SS7_SUCCESS			SS7_TRUE
#define SS7_FAILURE			SS7_FALSE

#ifdef SS7_ERROR
#undef SS7_ERROR
#endif
#define SS7_ERROR 		-1

#ifdef OK
#undef OK
#endif
#define OK 			0

#ifdef SS7_NULL
#undef SS7_NULL
#endif
#define SS7_NULL            	0


/* SPR 10419 - Fix Start */
/*typedef U32bit	timer_id_t;*/
typedef Ulong	timer_id_t;
/* SPR 10419 - Fix End   */
typedef U32bit	s7_len_t;
typedef S16bit	error_t;
typedef U8bit	buffer_t;

/* Start SPR 12497 Fix */
/*typedef U8bit   src_id_t;*/
/*typedef U8bit   dst_id_t;*/
typedef U16bit   src_id_t;
typedef U16bit   dst_id_t;
/* Stop SPR 12497 Fix */

typedef U8bit api_id_t;
typedef U8bit stat_type_t;
typedef U8bit module_id_t;
typedef U8bit stack_type_t;

/* DATA TYPE FOR COUNTS */
/* Number of times an event occurred */
typedef U32bit  count_t;

/* DATA TYPE FOR TIME INSTANCES */
/* Used to maintain time of occurrence of the first instance of an event */
typedef U32bit  ss7_time_t;


/* structure for module version */

typedef struct module_version
{
  U8bit major_version;
  U8bit minor_version;
  U8bit standard;
  U8bit standard_version;
}
module_version_t;

typedef U16bit          buf_size_t ;




#endif  /* end of _S7_TYP_H_ */
