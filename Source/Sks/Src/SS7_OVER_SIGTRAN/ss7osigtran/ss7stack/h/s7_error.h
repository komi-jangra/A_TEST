/******************************************************************************
** FUNCTION :
**	Global error definations.	
**
*******************************************************************************
**
** FILE NAME :
**             s7_error.h
**
** DESCRIPTION : 
**              Contain global error definitions  and start of module specific
**              error definitions.
**
**      DATE               NAME            REFERENCE        REASON
**      ----               ----            ---------        ------
**      05/12/97           Anil K.         HSS:20800008     Initial
**      18/11/02           rimishra        SPR10636
**
** Copyright 1997, Hughes Software System Ltd.
******************************************************************************/

#ifndef _S7_ERROR_H_
#define _S7_ERROR_H_

#define SS7_GLOBAL_ERR_START	0x0001
#define SS7_GLOBAL_ERR_END	0x00FE

#define SS7_MTP2_ERR_START	0x0101
#define SS7_MTP2_ERR_END	0x02FE

#define SS7_MTP3_ERR_START	0x0301
#define SS7_MTP3_ERR_END	0x05FE

#define SS7_ISUP_ERR_START	0x0601
#define SS7_ISUP_ERR_END	0x08FE

#define SS7_SCCP_ERR_START	0x0901
#define SS7_SCCP_ERR_END	0x0AFE

#define SS7_TCAP_ERR_START	0x0C01
#define SS7_TCAP_ERR_END	0x0EFE

#define SS7_BISUP_ERR_START	0x0F01
#define SS7_BISUP_ERR_END	0x11FE

/* parts not allocated from the above range are reserved and
   should not be used. */

/* Global error definations */
#define ESS7_INVALID_MODULE_ID		(SS7_GLOBAL_ERR_START + 0)
#define ESS7_INVALID_STATS_TYPE		(SS7_GLOBAL_ERR_START + 1)
#define ESS7_STATS_DISABLED		(SS7_GLOBAL_ERR_START + 2)
#define ESS7_INVALID_TRACE_FLAG		(SS7_GLOBAL_ERR_START + 3)
#define ESS7_TRACES_DISABLED		(SS7_GLOBAL_ERR_START + 4)
#define ESS7_INVALID_ERROR_ALRAM	(SS7_GLOBAL_ERR_START + 5)
#define ESS7_ERRORS_DISABLED		(SS7_GLOBAL_ERR_START + 6)
#define ESS7_INVALID_ERROR_ALARM_LEVEL	(SS7_GLOBAL_ERR_START + 7)
#define ESS7_INVALID_STATE		(SS7_GLOBAL_ERR_START + 8)
#define ESS7_INVALID_API_ID             (SS7_GLOBAL_ERR_START + 9)
#define ESS7_INVALID_LENGTH             (SS7_GLOBAL_ERR_START + 10)
#define ESS7_INVALID_EVENT              (SS7_GLOBAL_ERR_START + 11)
#define ESS7_QUEUE_FULL                 (SS7_GLOBAL_ERR_START + 12)
#define EVERSION_ID                     (SS7_GLOBAL_ERR_START + 13)

#define ESS7_INVALID_NUM_API_ELEMENTS   (SS7_GLOBAL_ERR_START + 14)
#define ESS7_MISSING_API_ELEMENT        (SS7_GLOBAL_ERR_START + 15)
#define ESS7_UNKNOWN_API_ELEMENT        (SS7_GLOBAL_ERR_START + 16)
#define ESS7_INVALID_API_ELEMENT_LENGTH (SS7_GLOBAL_ERR_START + 17)
#define ESS7_INVALID_API_ELEMENT        (SS7_GLOBAL_ERR_START + 18)

#define ESS7_FAILURE_TO_SEND_FROM_STACK_ENTITY     (SS7_GLOBAL_ERR_START + 19) 
#define ESS7_FAILURE_TO_SEND_TO_LOWER_LAYER        (SS7_GLOBAL_ERR_START + 20) 
#define ESS7_MEMORY_ALLOCATION_FAILURE             (SS7_GLOBAL_ERR_START + 21) 
#define ESS7_MEMORY_DEALLOCATION_FAILURE           (SS7_GLOBAL_ERR_START + 22) 
#define ESS7_FAILURE_TO_START_TIMER                (SS7_GLOBAL_ERR_START + 23) 
#define ESS7_BUFFER_LENGTH_OUT_OF_RANGE            (SS7_GLOBAL_ERR_START + 24) 
#define ESS7_BUFFER_OVERFLOW                       (SS7_GLOBAL_ERR_START + 25) 

#define ESYS_ERROR                       (SS7_GLOBAL_ERR_START + 26) 
#define EAPI_ERROR                       (SS7_GLOBAL_ERR_START + 27) 

#define	ESS7_INVALID_TRACE_LEVEL	 (SS7_GLOBAL_ERR_START + 28)
#define	ESS7_INVALID_ERROR_FLAG	  	 (SS7_GLOBAL_ERR_START + 29)
#define	ESS7_INVALID_ERROR_LEVEL	 (SS7_GLOBAL_ERR_START + 30)
#define	ESS7_INVALID_STANDARD	 	 (SS7_GLOBAL_ERR_START + 31)
#define ESS7_INVALID_EVENT_OBJ_ID        (SS7_GLOBAL_ERR_START + 32)
#define ESS7_INVALID_EVENT_LEVEL         (SS7_GLOBAL_ERR_START + 33)

#define ESS7_STATS_ALREADY_ENABLED       (SS7_GLOBAL_ERR_START + 34)
#define ESS7_STATS_ALREADY_DISABLED      (SS7_GLOBAL_ERR_START + 35)
#define ESS7_STATS_ALREADY_DISABLED      (SS7_GLOBAL_ERR_START + 35)
#define ESS7_MESSAGE_IN_INVALID_STATE      		(SS7_GLOBAL_ERR_START + 36)
#define ESS7_INVALID_RESET_FLAG           (SS7_GLOBAL_ERR_START + 37)
#endif
