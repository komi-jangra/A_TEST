/***************************************************************************
**  FUNCTION:
**      common file for some global definitions
**
****************************************************************************
**
**  FILE NAME:
**      s7_def.h
**
**  DESCRIPTION:
**		This files defines the common definitions to be used by
**		all the stack entities or ss7 stack as a whole.
**
**      DATE     NAME              REF#    REASON
**      -------  ----------------  -----   --------------------------------
**      15Jan98  smahajan          -----   Original  
**      01Oct98  smahajan          -----   Added Spanish changes
**					   Added ISUP_STACK_SPANISH &
**					   Moved ISUP_STACK_ITU_Q764 ITU_Q767
**
**      10Feb99  amajumdar         -----   Added BellCore changes
**      17Aug00  vinagpal          -----   SPR4303 : Added STACK_BRITISH
**                                           (same as STACK_TELSP_BT)
**      06Feb02  sabhatia          -----  DEREG Functionality  
**      14Mar02  sabhatia          -----  Adding BLOCKED State 
**      14Mar02  sabhatia          -----  Adding INIT REDN Type
** 		26jun02  saagrawal		   -----  Added SCCP register information
**      18May02  stripathi         -----  SPR 8740 : STACK_CHINESE value
**					  set to 12		
**      29Oct01  saugupta          -----   SPR6810: Added DMTP3_DF_MODULE_ID
**      04Feb01  Niranjan          _____   Indian ISUP Addition 
**               Mandeep
**		12Aug02  sashish		   -----   Fixed SPR 9302 
**      28Oct2002	Pranjal Mishra		SPR 10433
**      24Jan03  sashish           -----   Fixed SPR 11120
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _S7_DEF_H_     /* If this file has not been processed, */
#define _S7_DEF_H_     /* define it as seen--ref '#endif' below. */

extern int printf (const char *, ...);

#ifdef SCCP_MT_SAFE

/** SPR 9302 Start Fix **/
#ifndef __SS7_GET_SLF_THR_ID_FLAG__
#define __SS7_GET_SLF_THR_ID_FLAG__
extern S32bit ss7_get_self_thread_id(void);
#endif
/** SPR 9302 End Fix **/
#if 0
#ifndef SIGTRAN_SCCP_REDN_IF
#define SIGTRAN_SCCP_REDN_IF
#endif
#endif

#ifndef STACK_PRINT
#define STACK_PRINT(X) { printf("<%ld> ",ss7_get_self_thread_id()) ; printf X ;}
#endif
#define STACK_PRINT_HXD printf
#define SS7_HEX_DUMP(p,n)  \
	{ \
		U16bit _stack_dump_cntr_; \
\
		for (_stack_dump_cntr_=0; _stack_dump_cntr_ < n; \
			_stack_dump_cntr_++) \
		{ \
			STACK_PRINT_HXD (" %02x",*((U8bit *)p+_stack_dump_cntr_)); \
		} \
		STACK_PRINT_HXD ("\n"); \
	}
#else
#ifndef STACK_PRINT
#define STACK_PRINT  printf
#endif

#define SS7_HEX_DUMP(p,n)  \
	{ \
		U16bit _stack_dump_cntr_; \
\
		for (_stack_dump_cntr_=0; _stack_dump_cntr_ < n; \
			_stack_dump_cntr_++) \
		{ \
			STACK_PRINT (" %02x",*((U8bit *)p+_stack_dump_cntr_)); \
		} \
		STACK_PRINT ("\n"); \
	}
#endif /* SCCP_MT_SAFE */

#define STACK_ITU	0x01
#define STACK_ETSI	0x02
#define STACK_ANSI	0x03
#define STACK_SPANISH	0x04
#define STACK_BCGR	0x05
#define STACK_TELSP_BT  0x06
#define STACK_BRITISH   0x06 /* SPR4303 : Same as STACK_TELSP_BT */
#define STACK_ITU_INTL  0x07
#define STACK_RUSSIAN   0x08
#define STACK_JT	0x09
/* SPR 8740: Fix start */
/*#define STACK_CHINESE	10 */
#define STACK_CHINESE	12
/* SPR 8740: Fix end */
#define STACK_UK	0x0A	
#define STACK_INDIAN    0x0B

/* Sachin */
#define STACK_JAPANESE 13 


/* definition for ISUP */
#define ISUP_STACK_ITU_Q764 	0x01
#define ISUP_STACK_ETSI     	0x02
#define ISUP_STACK_ANSI     	0x03
#define ISUP_STACK_SPANISH  	0x04
#define ISUP_STACK_BCGR         0x05
#define ISUP_STACK_TELSP_BT     0x06
#define ISUP_STACK_ITU_Q767 	0x07
#define ISUP_STACK_RUSSIAN      0x08
#define ISUP_STACK_UK		0x0A	

/* For Indian Isup*/
#define ISUP_STACK_INDIAN       0x0B


/* definitions for BISUP */
#define BISUP_STACK_ITU_Q2764  0x01



#define INVALID_PROTOCOL_ID	0x00
#define MTP2_PROTOCOL_ID	0x01
#define MTP3_PROTOCOL_ID	0x02
#define SCCP_PROTOCOL_ID	0x03
#define ISUP_PROTOCOL_ID	0x04
#define TCAP_PROTOCOL_ID	0x05


#define SYS_MGMT_ID		0x06	
#define CALL_CONTROL_ID		0x07
#define TIMER_MODULE_ID		0x08
#define GGSN_TCAP_PROTOCOL_ID   0x09

#define BISUP_PROTOCOL_ID       0x09
#define DMTP3_DF_PROTOCOL_ID    0x0A
        
#define HLT_MANAGER_ID          0x0B        

#define SCCP_DMR_ID 		0x0C
#define SCCP_UMR_ID 		0x0D

/* FIX STARTS SPR 10433 */
#define TCAP_DMR_ID		0x0E
#define TCAP_UMR_ID		0x0F
/* FIX STARTS SPR 10433 */

#define CSSF_PROTOCOL_ID	0x10

#define SCCP_M3UA_PROTOCOL_ID	                  0x11
#define SCCP_M3UA_PROTOCOL_ID_ONE	              0x12
#define SCCP_M3UA_PROTOCOL_ID_TWO               0x13
#define SCCP_M3UA_PROTOCOL_ID_THREE             0x14
#define SCCP_M3UA_PROTOCOL_ID_FOUR              0x15

/* Added by Amaresh for EMAP Handelling New entry Added for BSSAP=EMAP start  */
#define BSSAP_MODULE_ID						              0x16 
/* Added by Amaresh for EMAP Handelling  New entry Added for BSSAP=EMAP stop */


/* Added by Amaresh for RM module start  */
#define SCCP_RM_MODULE_ID						              0x17 
#define M3UA_RM_MODULE_ID						              0x18 
/* Added by Amaresh for RM module stop */


#define MAX_PROTOCOL_ID		CSSF_MODULE_ID

#define INVALID_MODULE_ID	INVALID_PROTOCOL_ID
#define MTP2_MODULE_ID		MTP2_PROTOCOL_ID
#define MTP3_MODULE_ID		MTP3_PROTOCOL_ID
#define SCCP_MODULE_ID		SCCP_PROTOCOL_ID
#define ISUP_MODULE_ID		ISUP_PROTOCOL_ID
#define TCAP_MODULE_ID		TCAP_PROTOCOL_ID
#define CSSF_MODULE_ID		CSSF_PROTOCOL_ID
//Following entry is added, so that TCAP can register
//with sccp for different SSNs MAP is handling. Requirement
//arrises as SCCP does not allow one user id to register
//for more than one SSN
#define GGSN_TCAP_MODULE_ID GGSN_TCAP_PROTOCOL_ID

#define SYS_MGMT_MODULE_ID      SYS_MGMT_ID
#define CALL_CONTROL_MODULE_ID	CALL_CONTROL_ID
#define TIMER_SERVER_MODULE_ID	TIMER_MODULE_ID

#define BISUP_MODULE_ID         BISUP_PROTOCOL_ID
#define DMTP3_DF_MODULE_ID      DMTP3_DF_PROTOCOL_ID
        
#define HM_MODULE_ID            HLT_MANAGER_ID
        
#define MAX_MODULE_ID           HM_MODULE_ID




/******************************************************
********* stats defines           ********************
******************************************************/


#define STATS_API		0x01
#define STATS_PROTO_Q752	0x02
#define STATS_PROTO_INTERNAL	0x03
#define STATS_TRAFFIC		0x04
#define STATS_ERROR		0x05

/* add more stats definition here */

#define STATS_ALL		STATS_ERROR + 1

#define ISUP_MAX_STATS		STATS_ALL



/******************************************************
********* debug defines           ********************
******************************************************/

/* Common traces */
#define INCOMING_TRACE		    0x01
#define OUTGOING_TRACE		    0x02
#define API_TRACE		        0x03
#define SYSTEM_RESOURCE_TRACE	0x04
#define SYS_ERROR_TRACE		    0x05
#define ALARM_ERROR_TRACE	    0x06
#define INIT_TRACE		        0x07
#define PROTO_EXCEPTION_TRACE	0x08


/* ISUP Specific traces */
#define CALL_PROC_TRACE		    0x09
#define CKT_SUPERVISION_TRACE	0x0A


#define ALL_TRACE		CKT_SUPERVISION_TRACE + 1

#define ISUP_MAX_TRACE	ALL_TRACE

/* MTP2 Specific Traces */

#define FSM_TRACE               (PROTO_EXCEPTION_TRACE + 1)
#define MTP2_SU_TRACE           (FSM_TRACE + 1)
#define MTP2_ALL_TRACE          (MTP2_SU_TRACE + 1)
#define	MTP2_MAX_TRACE			MTP2_ALL_TRACE

/* SCCP Specific Trace flags */
#define SCMG_TRACE              0x40  /* SCCP management trace */
#define SCRC_TRACE              0x80  /* SCCP routing control trace */
#define SCLC_TRACE             0x100  /* SCCP connectionless trace */
#define SCOC_TRACE             0x200  /* SCCP Connection Oriented trace */
#define SCREDN_TRACE           0x400  /* SCCP Rednudancy Module trace */
#define SCRC_GTT_TRACE		   0x800  /* GTT Module trace */

/* TCAP Specific Trace flags */
#define TCO_TRACE               0x40  /* transaction coordinator trace */  
#define TSM_TRACE               0x80  /* transaction state machine trace */   
#define DCO_TRACE              0x100  /* dialogue coordinator trace */   
#define DSM_TRACE              0x200  /* dialogue state machine trace */   
#define CCO_TRACE              0x400  /* component coordinator trace */   
#define ISM_TRACE              0x800  /* transaction state machine trace */   
#define DB_TRACE              0x1000  /* Database module trace               */
#define MP_TRACE              0x2000  /* Message Parsing Module trace        */
#define ASN_TRACE             0x4000  /* ASN module trace                    */
#define UI_TRACE              0x8000  /* User Interface module trace         */
#define ERRP_TRACE            0x10000 /* Error Processing Module trace     */
#define REDN_TRACE            0x20000 /* Redn Module Trace */
#ifdef DISTRIBUTED_TCAP
#define DTCAP_TRACE		0x40000
#endif

/* BISUP Specific traces */
#define BISUP_DB_TRACE        0x09
#define BISUP_MC_TRACE        0x0A
#define BISUP_CC_TRACE        0x0B
#define BISUP_BCC_TRACE       0x0C
#define BISUP_SACF_TRACE      0x0D

#define BISUP_MAX_TRACE (BISUP_SACF_TRACE + 1)

/****************TRACE LEVELS *******************/

#define NO_TRACE                0  /* no trace level*/
#define BRIEF_TRACE             1  /* brief trace level*/
#define MEDIUM_TRACE            2  /* medium trace level*/
#define DETAILED_TRACE          3  /* detailed trace level */


/****************** ERROR DEFINITIONS **********************/


#define STACK_PROTOCOL_ERROR           0x1  /* protocol releated errors */
#define SYSTEM_ERROR             0x2  /* errors in system calls */
#define SYSTEM_RES_ERROR         0x3  /* errors in system resource */
#define API_ERROR                0x4  /* errors in API parsing and checking */
#define NW_ELEMENT_STATUS_ERROR  0x5  /* errors due to DPC INACC or LINK UNAV */
#define ALL_ERROR	             0x6  /* All errors */

#define PROTOCOL_ERROR_ALARM	0x01
#define SYSTEM_ERROR_ALARM	    0x02
#define SYSTEM_RES_ERROR_ALARM	0x03
#define ALL_ERROR_ALARM		    0x04

#define ISUP_MAX_ERROR_TYPES	ALL_ERROR
#define BISUP_MAX_ERROR_TYPES	ALL_ERROR
#define MTP2_MAX_ERROR_TYPES	ALL_ERROR_ALARM


/***************ERROR/EVENT LEVELS **********************/

#define NO_ERROR                0  /* no error reporting */
#define CRITICAL_ERROR          1  /* report critical errors */
#define MAJOR_ERROR             2  /* report major and critical errors */
#define MINOR_ERROR             3  /* report minor,major and critical errors */

#define NO_ERROR_ALARM          NO_ERROR
#define CRITICAL_ERROR_ALARM    CRITICAL_ERROR
#define MAJOR_ERROR_ALARM       MAJOR_ERROR
#define MINOR_ERROR_ALARM       MINOR_ERROR

#define ALL_LEVEL_ERROR_ALARM	0x04


/************************************************
*********** REDN DEFINITIONS ********************
*************************************************/

/****** SCCP redn data types ********************/

#define SCCP_REDN_DATA_SS_ENTRY     0x01
#define SCCP_REDN_DATA_SP_ENTRY     0x02
#define SCCP_REDN_DATA_REG_ENTRY    0x03
#define SCCP_REDN_DATA_SCOC_ENTRY   0x04
#define SCCP_REDN_DATA_SCLC_ENTRY   0x05
#define SCCP_REDN_DATA_ALL          0x06
#define SCCP_REDN_DATA_DEREG_ENTRY    0x07
#define SCCP_REDN_DATA_INIT_ENTRY    0x08
#define SCCP_REDN_DATA_DEINIT_ENTRY    0x09


/****** ISUP redn data types ********************/

#define ISUP_REDN_DATA_DPC	    0x01
#define ISUP_REDN_DATA_CSC_LM	0x02
#define ISUP_REDN_DATA_CSC_RM	0x03
#define ISUP_REDN_DATA_CPC	    0x04

/****** Stack Entity STATES *******/
#define STACK_INITIALIZED        0
#define UNINITIALIZED      1
#define ACTIVE             2
#define STACK_STANDBY      3
#define BLOCKED            4
/* SPR 9284 Fix starts - added DEINITIALIZING state */    
#define DEINITIALIZING     5
/* SPR 9284 fix ends */    
 
    
/****** hashdefine for Maximum buffer size in case of
******* Stats, Redn etc. buffers to be sent across 
********  the stack 
***/
#define SS7_MAX_BUFFER_SIZE 512
        
/* SPR 5586 fix begins */
#ifdef ISUP_DIFFERENT_SEND_TO_FN
#define ISUP_SEND_TO_ISUP_SM send_to_isup_sm
#else
#define ISUP_SEND_TO_ISUP_SM send_to_isup
#endif

#ifdef MTP3_DIFFERENT_SEND_TO_FN
#define MTP3_SEND_TO_MTP3_SM send_to_mtp3_sm
#else
#define MTP3_SEND_TO_MTP3_SM send_to_mtp3
#endif

#ifdef SCCP_DIFFERENT_SEND_TO_FN
#define SCCP_SEND_TO_SCCP_SM send_to_sccp_sm
#else
#define SCCP_SEND_TO_SCCP_SM send_to_sccp
#endif

#ifdef TCAP_DIFFERENT_SEND_TO_FN
#define TCAP_SEND_TO_TCAP_SM send_to_tcap_sm
#else
#define TCAP_SEND_TO_TCAP_SM send_to_tcap
#endif

/* SPR 5586 fix ends */      
  
/* added by salil */
#define SCCP_LOG_USER_ID SCCP_MODULE_ID
#define SCCP_SIO_NUMBER 5        
/* end */

#endif /* _S7_DEF_H_       -- This MUST appear after all code! */

