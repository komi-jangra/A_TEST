/***************************************************************************
**  FILE NAME:
**      sc_api.h
**
****************************************************************************
**
**  FUNCTION:
**      
**
**  DESCRIPTION:
**      
**
**  DATE     NAME              REF#   REASON
**  -------  ----------------  -----  -------------------------------------
**  12May'98 Sriganesh. Kini   -----  Original
**  03Dec'01 Ashish Sawalkar   -----  Fixed SPR 7350 
**  24Jan'02 Prateek Bidwalkar -----  Fixed SPR 7470
**  27Feb'02 Sachin Bhatia     -----  Adding Extended API parsing Macros
**  14Mar'02 Sachin Bhatia     -----  Fixed SPR 8596 
**  18Jun'02 Suyash Tripathi   -----  Fixed SPR 8985 
**  24Jul'02 Salil Agrawal     -----  Fixed SPR 9341
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _SC_API_H_
#define _SC_API_H_

#include "sc_s7gl.h"

#define SCCP_MIN_SU_API         SCCP_REGISTER_USER
#ifdef SCCP_INCLUDE_CO_SERVICE
#ifdef SCCP_INCLUDE_CO_CLASS3_SERVICE
#define SCCP_MAX_SU_API         SCCP_N_RESET_RESPONSE
#else
#define SCCP_MAX_SU_API         SCCP_N_INFORM_REQUEST
#endif
#else
/* SPR 8596 Fix Start */
#ifdef BACK_UP_SSN
/* SPR 8596 Fix ends */
#define SCCP_MAX_SU_API         SCCP_N_COORD_RESPONSE
/* SPR 8596 Fix Start */
#else
#define SCCP_MAX_SU_API         SCCP_N_STATE_REQUEST
#endif
/* SPR 8596 Fix ends */

#endif

#define SCCP_VERSION_NUMBER    1

#define GET_4_BYTE_LE(p_byte)   (((((U8bit *)(p_byte))[0]) << 0) | \
                                 ((((U8bit *)(p_byte))[1]) << 8) | \
                                 ((((U8bit *)(p_byte))[2]) << 16) | \
                                 ((((U8bit *)(p_byte))[3]) << 24))

#define GET_3_BYTE_LE(p_byte)   (((((U8bit *)(p_byte))[0]) << 0) | \
								((((U8bit *)(p_byte))[1]) << 8) | \
							  	((((U8bit *)(p_byte))[2]) << 16))

#define GET_2_BYTE_LE(p_byte)   (((((U8bit *)(p_byte))[0]) << 0) | \
                                 ((((U8bit *)(p_byte))[1]) << 8))

#define PUT_4_BYTE_LE(p_byte, val) \
	do \
	{ \
		(p_byte)[0] = (U8bit)(val); \
		(p_byte)[1] = (U8bit)((val) >> 8); \
		(p_byte)[2] = (U8bit)((val) >> 16); \
		(p_byte)[3] = (U8bit)((val) >> 24); \
	} while (0)

#define PUT_3_BYTE_LE(p_byte, val) \
        do \
        { \
                (p_byte)[0] = (U8bit)(val); \
                (p_byte)[1] = (U8bit)((val) >> 8); \
                (p_byte)[2] = (U8bit)((val) >> 16); \
        } while (0)

#define PUT_2_BYTE_LE(p_byte, val) \
	do \
	{ \
		(p_byte)[0] = (U8bit)(val); \
		(p_byte)[1] = (U8bit)((val) >> 8); \
	} while (0)
/* spr # 9341 started */
#if 0

#ifdef SCCP_CHINESE

#define GET_PC(p_byte) ((p_byte[0])|((p_byte[1]) << 8)|((p_byte[2]) << 16)) 

#else

#ifdef SCCP_JAPANESE
#define GET_PC(p_byte) (((sc_opt.standard == STACK_JAPANESE) ) ?\
					((p_byte[0])|((p_byte[1]) << 8)) : 0 )
#else
#define GET_PC(p_byte)  (((sc_opt.standard == STACK_ANSI) || \
			  (sc_opt.standard == STACK_BCGR)) ? \
						((p_byte[0])|((p_byte[1]) << 8)|((p_byte[2]) << 16)) : \
						((p_byte[0])|(((p_byte[1]) & 0x3f) << 8))) 
#endif
#endif

#endif /* endif 0 */

/*start spr 9634 */
#if 0
#ifdef SCCP_JAPANESE
#define GET_PC(p_byte) (((sc_opt.standard == STACK_JAPANESE) ) ?\
					((p_byte[0])|((p_byte[1]) << 8)) : 0 )
#else
#define GET_PC(p_byte)  (((sc_opt.standard == STACK_ANSI) || \
			  (sc_opt.standard == STACK_BCGR) || (sc_opt.standard == STACK_CHINESE)) ? \
						((p_byte[0])|((p_byte[1]) << 8)|((p_byte[2]) << 16)) : \
						((p_byte[0])|(((p_byte[1]) & 0x3f) << 8))) 
#endif
/* end spr # 9341 */

#endif  /* #if 0 */

/* end spr 9634 */
/* start spr 9634 */
#define GET_PC(p_byte)  (((sc_opt.standard == STACK_ANSI) || \
                          (sc_opt.standard == STACK_BCGR) || (sc_opt.standard == \
 STACK_CHINESE)) ? \
                                                ((p_byte[0])|((p_byte[1]) << 8)| \
((p_byte[2]) << 16)) :((sc_opt.standard == STACK_JAPANESE)?\
                                        ((p_byte[0])|((p_byte[1]) << 8)) : \
                                        ((p_byte[0])|(((p_byte[1]) & 0x3f) \
 << 8))))

/* ends spr 9634 */    
/* start spr # 9341 */
#if 0    

#ifdef SCCP_CHINESE
#define PUT_PC(p_byte, pc) \
	do \
	{ \
               p_byte[0] = (U8bit)pc; \
               p_byte[1] = (U8bit)(pc >> 8); \
               p_byte[2] = (U8bit)(pc >> 16); \
	}while(0)
#else

#ifdef SCCP_JAPANESE
#define PUT_PC(p_byte, pc) \
        do \
        { \
                if (sc_opt.standard == STACK_JAPANESE)  \
                { \
                        p_byte[0] = (U8bit)pc; \
                        p_byte[1] = (U8bit)(pc >> 8); \
                } \
        } while (0)
#else
#define PUT_PC(p_byte, pc) \
        do \
        { \
                if ((sc_opt.standard == STACK_ANSI) || \
		    (sc_opt.standard == STACK_BCGR))  \
                { \
                        p_byte[0] = (U8bit)pc; \
                        p_byte[1] = (U8bit)(pc >> 8); \
                        p_byte[2] = (U8bit)(pc >> 16); \
                } \
                else \
                { \
                        p_byte[0] = (U8bit)pc; \
                        p_byte[1] = (U8bit)((pc >> 8) & 0x3f); \
                } \
        } while (0)
#endif                              
#endif

#endif /* end of if 0 */

#define PUT_PC(p_byte, pc) \
        if ((sc_opt.standard == STACK_ANSI) || \
	    (sc_opt.standard == STACK_BCGR) || (sc_opt.standard == STACK_CHINESE))  \
        { \
                p_byte[0] = (U8bit)pc; \
                p_byte[1] = (U8bit)(pc >> 8); \
                p_byte[2] = (U8bit)(pc >> 16); \
        } \
        else if (sc_opt.standard == STACK_JAPANESE)  \
        { \
                p_byte[0] = (U8bit)pc; \
                p_byte[1] = (U8bit)(pc >> 8); \
        } \
        else \
        { \
                p_byte[0] = (U8bit)pc; \
                p_byte[1] = (U8bit)((pc >> 8) & 0x3f); \
        }
    
/* end spr 9341 */    

/* start spr  # 9341 */
#if 0        

#ifdef SCCP_CHINESE
#define PC_SIZE 3

#else

#define PC_SIZE (((sc_opt.standard == STACK_ANSI) || \
		  (sc_opt.standard == STACK_BCGR)) ? 3 : 2)    
#endif

#endif /* end of if 0 */

#define PC_SIZE (((sc_opt.standard == STACK_ANSI) || \
		  (sc_opt.standard == STACK_BCGR) || (sc_opt.standard == STACK_CHINESE)) ? 3 : 2)    
/* end of spr # 9341 */
    
#define API_ID_OFFSET        0
#define API_VER_OFFSET       1
#define API_NELEM_OFFSET     2
#define API_LEN_LSB          3
#define API_LEN_MSB          4
#define API_HEADER_LEN       SS7_API_HEADER_LEN 

#define API_EXTENDED_ID_OFFSET        5

#define GET_EXTENDED_API_ID(p_api)     (p_api[API_EXTENDED_ID_OFFSET])
#define GET_API_ID(p_api)     (p_api[API_ID_OFFSET])
#define GET_API_VER(p_api)    (p_api[API_VER_OFFSET])
#define GET_API_NELEM(p_api)  (p_api[API_NELEM_OFFSET])
#define GET_API_LEN(p_api)    (p_api[API_LEN_LSB] | (p_api[API_LEN_MSB] << 8))

#define SCCP_VERSION_ID       1
/* SPR # 7470 Fix Start */
#ifdef DISTRIBUTED_SCCP
#define DSCCP_VERSION_ID	2
#endif
/* SPR # 7470 Fix End */

#define SM_CATEGORY_LEN 1
#define SM_COMMAND_LEN  1
#define SM_TRANS_ID_LEN  1

/* SPR 7350: Start Fix */
#define SCCP_SM_CATEGORY_OFFSET    (API_HEADER_LEN)
/* SPR 7350: End Fix */
#define SM_COMMAND_OFFSET     (API_HEADER_LEN + SM_CATEGORY_LEN)
#define SM_TRANS_ID_OFFSET    (API_HEADER_LEN + SM_CATEGORY_LEN + SM_COMMAND_LEN)
#define SM_ERR_FLAG_OFFSET    (SS7_SM_API_MIN_LEN)
#define SM_ERR_LEVEL_OFFSET   (SM_ERR_FLAG_OFFSET + 4)
#define SM_TRC_FLAG_OFFSET    (SS7_SM_API_MIN_LEN)
#define SM_TRC_LEVEL_OFFSET   (SM_TRC_FLAG_OFFSET + 4)
#define SM_STAT_TYPE_OFFSET   (SS7_SM_API_MIN_LEN)
#define SM_RESET_FLAG_OFFSET  (SS7_SM_API_MIN_LEN + 1)
#define SCCP_SM_OBJECT_ID_OFFSET        (SS7_SM_API_MIN_LEN)
#define SCCP_SM_OBJECT_LEVEL_OFFSET     (SCCP_SM_OBJECT_ID_OFFSET + 2)
 


/* SPR 1596: SCCP_SM_STD_RESP_LEN should be equal to 9 */
#define SCCP_SM_STD_RESP_LEN         (SS7_SM_API_MIN_LEN + 1)
#define SCCP_SM_STD_RESP_MIN_NELEM   (SS7_SM_API_MIN_NO_ELEM + 1)

/* SPR 7350: Start Fix */
#define GET_SM_CAT(p_api)       (p_api[SCCP_SM_CATEGORY_OFFSET])
/* SPR 7350: End Fix */
#define GET_SM_CMD(p_api)       (p_api[SM_COMMAND_OFFSET])
#define GET_SM_ERR_FLAG(p_api)  (GET_4_BYTE_LE(p_api + SM_ERR_FLAG_OFFSET))
#define GET_SM_ERR_LEVEL(p_api) (p_api[SM_ERR_LEVEL_OFFSET])
#define GET_SM_TRC_FLAG(p_api)  (GET_4_BYTE_LE(p_api + SM_TRC_FLAG_OFFSET))
#define GET_SM_TRC_LEVEL(p_api) (p_api[SM_TRC_LEVEL_OFFSET])
#define GET_SM_STAT_TYPE(p_api) (p_api[SM_STAT_TYPE_OFFSET])
#define GET_SM_RESET_FLAG(p_api)        (p_api[SM_RESET_FLAG_OFFSET])
#define GET_SCCP_SM_OBJECT_ID(p_api)    (GET_2_BYTE_LE(p_api + SCCP_SM_OBJECT_ID_OFFSET))
#define GET_SCCP_SM_OBJECT_LEVEL(p_api) (p_api[SCCP_SM_OBJECT_LEVEL_OFFSET])


 
#define GET_TIMER_ID(p_api)     (p_api[API_HEADER_LEN])

#define SCCP_ELEM_NW_ID_LEN       1
#define LEN_SSN 1

#define SCCP_ELEM_NUM_ENTRIES_LEN	1
#define SCCP_ELEM_ENTRY_SIZE_LEN 	1
#define SCCP_SM_TIMER_CONF_INFO_LEN 5
#define SCCP_SM_SP_CONF_INFO_LEN 	11
#define SCCP_SM_SS_CONF_INFO_LEN 	9
#define SCCP_SM_CSS_CONF_INFO_LEN 	4
#define SCCP_SM_CSP_CONF_INFO_LEN 	4

#define MTP3_MIN_API_TO_UP      MTP3_UP_TRANSFER_INDICATION

#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
#define MTP3_MAX_API_TO_UP      MTP3_ANSI_UP_CLUSTER_RESUME_INDICATION
#else
#define MTP3_MAX_API_TO_UP      MTP3_UP_STATUS_INDICATION
#endif
/* starts spr # 9341 */
#if 0
#ifdef SCCP_CHINESE
#define LEN_BYTE_CODED_ITU_T_PC  3
#else
#define LEN_BYTE_CODED_ITU_T_PC  2
#endif
#endif /* end of if 0 */

#define LEN_BYTE_CODED_ITU_T_PC (((sc_opt.standard == STACK_ANSI) || \
		  (sc_opt.standard == STACK_BCGR) || (sc_opt.standard == STACK_CHINESE)) ? 3 : 2) 
    
/* end spr # 9341 */
    
#define PUT_SCCP_ELEM_LEN(p_byte, len) \
	do \
	{ \
		p_byte[0] = (U8bit)len; \
		p_byte[1] = (U8bit)(len >> 8); \
	} while (0)

/* Lengths of the MTP3 APIs */
#define MTP3_LEN_UP_PAUSE_INDICATION   (API_HEADER_LEN + \
                                        LEN_BYTE_CODED_ITU_T_PC)

#define MTP3_LEN_UP_RESUME_INDICATION  (API_HEADER_LEN + \
                                        LEN_BYTE_CODED_ITU_T_PC)

#define MTP3_LEN_UP_STATUS_INDICATION  (API_HEADER_LEN + \
                                        MTP3_LENGTH_CAUSE + \
                                        LEN_BYTE_CODED_ITU_T_PC + \
                                        MTP3_LENGTH_CONGESTION_STATUS_LEVEL)
/* Length of APIs added for GR */

#define CLUSTER_LEN     3

#define MTP3_LEN_UP_PAUSE_CLUSTER_INDICATION   (API_HEADER_LEN +\
                                                CLUSTER_LEN)

#define MTP3_LEN_UP_RESUME_CLUSTER_INDICATION   (API_HEADER_LEN +\
                                                CLUSTER_LEN)


/* Masks to access mtp3 api elements */
#define MTP3_CAUSE_MASK		0x3
/* SPR 8985 - Fix Start */
/* Variable name is being changed to avoid warnings */
/*#define MTP3_CONG_LEVEL_MASK	0x3 */
#define SCCP_MTP3_CONG_LEVEL_MASK	0x3
/* SPR 8985 - Fix End  */

#define GET_CLUSTER(p_byte)  ((p_byte[0])|((p_byte[1]) << 8))

#define ONE_BYTE_OPT_ELEM_SIZE  (SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN + 1)


/** Sizes for Redn APIs **/
#define SCCP_SM_REDN_MAX_API_LEN		SS7_MAX_BUFFER_SIZE
#define SCCP_SM_REDN_MAX_UPDATES_PER_MSG	0xff /* this number must fit in one 
												 ** octet */
#define SCCP_SM_INIT_REDN_DATA_LEN      (SS7_SM_API_MIN_LEN + 1)
#define SCCP_SM_INIT_REDN_DATA_NELEM    (SS7_SM_API_MIN_NO_ELEM + 1)

#define SCCP_SM_REDN_REQ_ACT_LEN        (SS7_SM_API_MIN_LEN \
											+ 1 /* type of data */ \
											+ 7 /* redn info flag + info */)   
#define SCCP_SM_REDN_REQ_ACT_NELEM      (SS7_SM_API_MIN_NO_ELEM + 2)   

#define SCCP_SM_REDN_RECV_UPDATE_MIN_LEN	(SS7_SM_API_MIN_LEN \
												+ 1 /* status (reserved) */ \
												+ 1 /* more data flag */ \
												+ 1 /* update seq num */ \
												+ 1 /* type of data */ \
												+ 7 /* redn info flag + info */)
#define SCCP_SM_REDN_RECV_UPDATE_NELEM  (SS7_SM_API_MIN_NO_ELEM + 5 + 1)  
												/* 6th elem = redn data */

#define SCCP_SM_REDN_REQ_ACT_RESP_MIN_LEN	SCCP_SM_REDN_RECV_UPDATE_MIN_LEN
#define SCCP_SM_REDN_REQ_ACT_RESP_NELEM		SCCP_SM_REDN_RECV_UPDATE_NELEM

#define SCCP_SM_ACTIVATE_LEN      		(SS7_SM_API_MIN_LEN)
#define SCCP_SM_ACTIVATE_NELEM    		(SS7_SM_API_MIN_NO_ELEM)



#define SS7_EVENT_RPT		1
#define SS7_NO_EVENT_RPT	0


#endif /* _SC_API_H_ */
