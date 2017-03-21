/*******************************************************************************
**      FILE NAME:
**          bs_msgst.h
**
**      DESCRIPTION:
**              This files defines the macros common definitions to be used by
**              by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/



/***************************************************************************
**  FILE NAME:
**      sc_msgst.h
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
**  13Nov2002 Ashish Sawalkar		  Fixed SPR IMP_SPR
**  20Jun2001 Suyash Tripathi         fixed SPR #8985  
**  03Apr2002 Salil Agrawal           fixed SPR #8530  
**  31Oct2001 Pawanish Modi           Chanages for Distributed SCCP  phase 2
**  29Aug2001 pawanish Modi           Chanages for Distributed SCCP  phase 1
**  28May2001 Rajesh Mehta            Increase corr_id to U16 and conn_id to
**                                    to U32 if SCCP_CONNECTION_ID_CHANGES is defined
**  12Oct2000 Ramu Kandula            Modified for broadband - added #def
**                                    for LONG_V_PARAM_LEN_LEN
**  09Jun2000 Ramu Kandula            Fixed SPR # 2579
**  05Jun2000 Ramu Kandula            Fixed SPR # 3643
**  24Feb2000 Ramu Kandula            Fixed SPR # 2731
**  23Feb2000 Ramu Kandula            Fixed SPR # 2663
**  17Feb2000 Ramu Kandula            Fixed SPR # 2618
**  17Feb2000 Ramu Kadula             Fixed SPR # 2617
**  12May'98 Sriganesh. Kini   -----  Original
**  06Aug'98 Anil K.				  ANSI Connectionless Added
**  18Aug'98 Anil K.		   -----  Connection oriented srevices added.
**  29Apr'99 Sudipta Pattar    -----  Fixed SPR 1502
**
**  Copyright 1997, Hughes Software Systems
***************************************************************************/

#ifndef _BS_MSGST_H_
#define _BS_MSGST_H_

#include "bs_stgl.h"


#define SCCP_SI    0x3

#define MAX_ISNI_LEN 16


#define ISNI_MASK                  ((0x1) << 2)
#define HOP_COUNTER_IE_MASK        ((0x1) << 6)
#define SEQUENCING_PARAM_IE_MASK   ((0x1) << 7)
#define TRANSLATION_DONE_MASK      ((0x1) << 8)
#define SCCP_IMPORTANCE_MASK	           ((0x1) << 9)
#define SEGMENTATION_MASK          ((0x1) << 10)
#define CREDIT_MASK                ((0x1) << 11)
#define CG_MASK                    ((0x1) << 12)
#define DATA_MASK                  ((0x1) << 13)
#define CD_MASK                    ((0x1) << 14)
#define ED_SLECTION_MASK           ((0x1) << 15)
#define RG_MASK                    ((0x1) << 16)
#define RPLY_REQ_INDICATOR_MASK    ((0x1) << 17)
#define REFUSAL_INDICATOR_MASK     ((0x1) << 18)
#define CORR_ID_MASK               ((0x1) << 19)
#define L_MASK                     ((0x1) << 20)
#define PROTO_CLASS_MASK           ((0x1) << 21)
#define ED_MASK                    ((0x1) << 22)
#define RELAY_MSG_FLAG             ((0x1) << 23)
#define L_O_MASK                   ((0x1) << 24)

#define IE_FLAG(p)      ((p)->flag)

#define IS_HOP_COUNTER_IE_PRESENT(p)	 (IE_FLAG(p) & HOP_COUNTER_IE_MASK)
#define IS_SEQUENCING_PARAM_PRESENT(p)	 (IE_FLAG(p) & SEQUENCING_PARAM_IE_MASK)
#define IS_TRANSLATION_DONE(p)		     (IE_FLAG(p) & TRANSLATION_DONE_MASK)
#define IS_IMPORTANCE_PRESENT(p)	     (IE_FLAG(p) & SCCP_IMPORTANCE_MASK)
#define IS_IMPORTANCE_IE_PRESENT(p)	     (IE_FLAG(p) & SCCP_IMPORTANCE_MASK)
#define IS_SEGMENTATION_IE_PRESENT(p)    (IE_FLAG(p) & SEGMENTATION_MASK)
#define IS_ISNI_PRESENT(p)               (IE_FLAG(p) & ISNI_MASK)
#define IS_CREDIT_IE_PRESENT(p)          (IE_FLAG(p) & CREDIT_MASK)
#define IS_CG_IE_PRESENT(p)              (IE_FLAG(p) & CG_MASK)
#define IS_DATA_IE_PRESENT(p)            (IE_FLAG(p) & DATA_MASK)
#define IS_CD_IE_PRESENT(p)              (IE_FLAG(p) & CD_MASK)
#define IS_RG_IE_PRESENT(p)              (IE_FLAG(p) & RG_MASK)
#define IS_ED_SELECTION_PRESENT(p)       (IE_FLAG(p) & ED_MASK)
#define IS_REF_IND_PRESENT(p)            (IE_FLAG(p) & REFUSAL_INDICATOR_MASK)
#define IS_REPLY_REQ_IND_PRESENT(p)      (IE_FLAG(p) & RPLY_REQ_INDICATOR_MASK)
#define IS_CORR_ID_IE_PRESENT(p)         (IE_FLAG(p) & CORR_ID_MASK)
#define IS_LOGUID_IE_PRESENT(p)          (IE_FLAG(p) & L_MASK)
#define IS_LOGUID_O_IE_PRESENT(p)        (IE_FLAG(p) & L_O_MASK)
#define IS_RELAY_MSG(p)                  (IE_FLAG(p) & RELAY_MSG_FLAG)


#define SET_IMPORTANCE_PRESENT(p)        (IE_FLAG(p) |= SCCP_IMPORTANCE_MASK)
#define SET_SEGMENTATION_PRESENT(p)      (IE_FLAG(p) |= SEGMENTATION_MASK)
#define SET_HOP_COUNTER_IE_PRESENT(p)    (IE_FLAG(p) |= HOP_COUNTER_IE_MASK)
#define SET_TRANSLATION_DONE(p)          (IE_FLAG(p) |= TRANSLATION_DONE_MASK)
#define SET_ISNI_PRESENT(p)              (IE_FLAG(p) |= ISNI_MASK)
#define SET_CREDIT_PRESENT(p)          (IE_FLAG(p) |= CREDIT_MASK)
#define SET_CG_PRESENT(p)              (IE_FLAG(p) |= CG_MASK)
#define SET_DATA_PRESENT(p)            (IE_FLAG(p) |= DATA_MASK)
#define SET_CD_PRESENT(p)              (IE_FLAG(p) |= CD_MASK)
#define SET_HOP_COUNTER_PRESENT(p)     (IE_FLAG(p) |= HOP_COUNTER_IE_MASK)
#define SET_EXPEDIATE_DATA_SELECTION_PRESENT(p) \
									   (IE_FLAG(p) |= ED_SLECTION_MASK)
#define SET_RG_PRESENT(p)              (IE_FLAG(p) |= RG_MASK)
#define SET_RPLY_REQ_INDICATOR_PRESENT(p) (IE_FLAG(p)|= RPLY_REQ_INDICATOR_MASK)
#define SET_REFUSAL_INDICATOR_PRESENT(p)  (IE_FLAG(p) |= REFUSAL_INDICATOR_MASK)
#define SET_CORR_ID_PRESENT(p)         (IE_FLAG(p) |= CORR_ID_MASK)
#define SET_L_ID_PRESENT(p)            (IE_FLAG(p) |= L_MASK)
#define SET_PROTOCOL_CLASS_PRESENT(p)  (IE_FLAG(p) |= PROTO_CLASS_MASK)
#define SET_RELAY_MSG(p)               (IE_FLAG(p) |= RELAY_MSG_FLAG)
#define SET_L_ID_O_PRESENT(p)          (IE_FLAG(p) |= L_O_MASK)

#define CLR_RG_IE_PRESENT(p)           (IE_FLAG (p) &= ~RG_MASK)

#define CLR_IMPORTANCE_PRESENT(p)      (IE_FLAG(p) &= ~SCCP_IMPORTANCE_MASK)
#define CLR_CD_PRESENT(p)	       (IE_FLAG (p) &= ~CD_MASK)


#define SS7_NARROWBAND_NETWORK     1
#ifdef SCCP_BROADBAND
#define SS7_BROADBAND_NETWORK      2
#endif

#define ROUTE_ON_GT   0
#define ROUTE_ON_SSN  1


#define PROTOCOL_CLASS_0      0
#define PROTOCOL_CLASS_1      1
#define PROTOCOL_CLASS_2      2
#define PROTOCOL_CLASS_3      3

#define RET_OPTN_MASK         0x80

#define IDX_MSG_TYPE_IN_MSG   0

#define UDT_MSG_TYPE         0x09
#define UDTS_MSG_TYPE        0x0a
#define XUDT_MSG_TYPE        0x11
#define XUDTS_MSG_TYPE       0x12

#ifdef SCCP_BROADBAND
#define LUDT_MSG_TYPE        0x13
#define LUDTS_MSG_TYPE       0x14
#endif


/* SCCP message types for SCCP Connection oriented services */
#define CR_MSG_TYPE          0x01  /* Connection Request (Class 2/3)*/
#define CC_MSG_TYPE          0x02  /* Connection Confirm (Class 2/3)*/
#define CREF_MSG_TYPE        0x03  /* Connection Refused (Class 2/3)*/
#define RLSD_MSG_TYPE        0x04  /* Connection ReleaSed (Class 2/3)*/
#define RLC_MSG_TYPE         0x05  /* ReLease Complete (Class 2/3)*/
#define DT1_MSG_TYPE         0x06  /* DaTa form 1 (Class 2)*/
#define DT2_MSG_TYPE         0x07  /* DaTa form 2 (Class 3)*/
#define AK_MSG_TYPE          0x08  /* data Acknowledgement (Class 3)*/
#define ED_MSG_TYPE          0x0B  /* Expediate Data (Class 3)*/
#define EA_MSG_TYPE          0x0C  /* Expediate data Acknowledgement (Class 3)*/
#define RSR_MSG_TYPE         0x0D  /* ReSet Request (Class 3)*/
#define RSC_MSG_TYPE         0x0E  /* ReSet Confirm (Class 3)*/
#define ERR_MSG_TYPE         0x0F  /* protocol data unit Error (Class 2/3)*/
#define IT_MSG_TYPE          0x10  /* Inactivity Test (Class 2/3)*/

/* Note : MIN_MSG_LEN below include length of fix parameters and number
   of pointers included in the messgaes. e.g. for XUDT message
   MIN_XUDT_MSG_LEN is calculated as follows :
   lentgh of message type : 1
   length of proto_class  : 1
   length of hop_counter  : 1
   Number of mandatory vairable elements : 3
   Pointer to optional part : 1

   Total : 7 bytes
*/
#define MIN_UDT_MSG_LEN            5
#define NUM_MAND_VAR_IES_IN_UDT    3
#define IDX_PROTO_CLASS_IN_UDT     1
#define IDX_CD_ADDR_PTR_IN_UDT     2
#define IDX_CG_ADDR_PTR_IN_UDT     3
#define IDX_DATA_PTR_IN_UDT        4
#define MIN_UDTS_MSG_LEN           5
#define NUM_MAND_VAR_IES_IN_UDTS   3
#define IDX_RET_CAUSE_IN_UDTS      1
#define IDX_CD_ADDR_PTR_IN_UDTS    2
#define IDX_CG_ADDR_PTR_IN_UDTS    3
#define IDX_DATA_PTR_IN_UDTS       4

#define MIN_XUDT_MSG_LEN           7
#define NUM_MAND_VAR_IES_IN_XUDT   4
#define IDX_PROTO_CLASS_IN_XUDT    1
#define IDX_HOP_CNTR_IN_XUDT       2
#define IDX_CD_ADDR_PTR_IN_XUDT    3
#define IDX_CG_ADDR_PTR_IN_XUDT    4
#define IDX_DATA_PTR_IN_XUDT       5
#define IDX_OPT_PARAM_PTR_IN_XUDT  6

#define MIN_XUDTS_MSG_LEN           7
#define NUM_MAND_VAR_IES_IN_XUDTS   4
#define IDX_RET_CAUSE_IN_XUDTS      1
#define IDX_HOP_CNTR_IN_XUDTS       2
#define IDX_CD_ADDR_PTR_IN_XUDTS    3
#define IDX_CG_ADDR_PTR_IN_XUDTS    4
#define IDX_DATA_PTR_IN_XUDTS       5
#define IDX_OPT_PARAM_PTR_IN_XUDTS  6

#ifdef SCCP_BROADBAND
#define MIN_LUDT_MSG_LEN            (3+3*2+1*2)
#define NUM_MAND_VAR_IES_IN_LUDT    4
#define IDX_PROTO_CLASS_IN_LUDT     1
#define IDX_HOP_CNTR_IN_LUDT        2
#define IDX_CD_ADDR_PTR_IN_LUDT     3
#define IDX_CG_ADDR_PTR_IN_LUDT     5
#define IDX_DATA_PTR_IN_LUDT        7
#define IDX_OPT_PARAM_PTR_IN_LUDT   9
 
#define MIN_LUDTS_MSG_LEN           (3+3*2+1*2)
#define NUM_MAND_VAR_IES_IN_LUDTS   4
#define IDX_RET_CAUSE_IN_LUDTS      1
#define IDX_HOP_CNTR_IN_LUDTS       2
#define IDX_CD_ADDR_PTR_IN_LUDTS    3
#define IDX_CG_ADDR_PTR_IN_LUDTS    5
#define IDX_DATA_PTR_IN_LUDTS       7
#define IDX_OPT_PARAM_PTR_IN_LUDTS  9
#endif


/* CR Message related information */
#define MIN_CR_MSG_LEN              7
#define NUM_MAND_VAR_IES_IN_CR      1
#define IDX_CD_ADDR_PTR_IN_CR       5
#define IDX_OPT_PARAM_PTR_IN_CR     6

#define MIN_CC_MSG_LEN              9
#define NUM_MAND_VAR_IES_IN_CC      0
#define IDX_OPT_PARAM_PTR_IN_CC     8

#define MIN_CREF_MSG_LEN            6
#define NUM_MAND_VAR_IES_IN_CREF    0
#define IDX_OPT_PARAM_PTR_IN_CREF   5

#define MIN_RLSD_MSG_LEN            9
#define NUM_MAND_VAR_IES_IN_RLSD    0
#define IDX_OPT_PARAM_PTR_IN_RLSD   8

#define MIN_RLC_MSG_LEN             7
#define NUM_MAND_VAR_IES_IN_RLC     0
#define MIN_DT1_MSG_LEN             6
#define NUM_MAND_VAR_IES_IN_DT1     1
#define IDX_DATA_PTR_IN_DT1         5

#define MIN_DT2_MSG_LEN             7
#define NUM_MAND_VAR_IES_IN_DT2     1
#define IDX_DATA_PTR_IN_DT2         6
#define MIN_AK_MSG_LEN              6
#define NUM_MAND_VAR_IES_IN_AK      0

#define MIN_ED_MSG_LEN              5
#define NUM_MAND_VAR_IES_IN_ED      1
#define IDX_DATA_PTR_IN_ED          4
#define MIN_EA_MSG_LEN              4
#define NUM_MAND_VAR_IES_IN_EA      0
#define MIN_RSR_MSG_LEN             8
#define NUM_MAND_VAR_IES_IN_RSR     1
#define IDX_OPT_PARAM_PTR_IN_RSR    8

#define MIN_RSC_MSG_LEN             7
#define NUM_MAND_VAR_IES_IN_RSC     0
#define MIN_ERR_MSG_LEN             5 
# define NUM_MAND_VAR_IES_IN_ERR    1
# define IDX_OPT_PARAM_PTR_IN_ERR   5 

#define MIN_IT_MSG_LEN              11
# define NUM_MAND_VAR_IES_IN_IT      0

/* Possible Return causes 3.12 in Q.713 */
#define SCCP_NO_TRANSLATION_ADDR_OF_SUCH_NATURE 0x0
#define SCCP_NO_TRANSLATION_FOR_SPECIFIC_ADDR   0X1
#define SCCP_SUBSYSTEM_CONGESTION               0X2
#define SCCP_SUBSYSTEM_FAILURE                  0X3
#define SCCP_UNEQUIPPED_USER                    0X4
#define SCCP_MTP_FAILURE                        0X5
#define SCCP_NETWORK_CONGESTION                 0X6
#define SCCP_UNQUALIFIED                        0X7
#define SCCP_ERR_IN_MESSAGE_TRANSPORT           0X8
#define SCCP_ERR_IN_LOCAL_PROCESSING            0X9
#define SCCP_DESTN_CANNOT_PERFORM_REASSEMBLY    0XA
#define SCCP_FAILURE                            0XB
#define SCCP_HOP_COUNTER_VIOLATION              0XC
#define SCCP_SEGMENTATION_NOT_SUPPORTED         0XD
#if ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined (SCCP_ETSI) || defined (SCCP_CHINESE)
#define SCCP_SEGMENTATION_FAILURE               0XE 
#endif

/* Possible Release causes 3.11 in ITU-T Q.713, 3.11 in ANSI T1-112.3*/
#define SCCP_RLSDC_END_USER_ORIGINATED                0X00
#define SCCP_RLSDC_END_USER_CONGESTED                 0X01
#define SCCP_RLSDC_END_USER_FAILURE                   0X02
#define SCCP_RLSDC_SCCP_USER_ORIGINATED               0X03
#define SCCP_RLSDC_REMOTE_PROCEDURE_ERROR             0X04
#define SCCP_RLSDC_INCONSISTENT_CONNECTION_DATA       0X05
#define SCCP_RLSDC_ACCESS_FAILURE                     0X06
#define SCCP_RLSDC_ACCESS_CONGESTION                  0X07
#define SCCP_RLSDC_SUBSYSTEM_FAILURE                  0X08
#define SCCP_RLSDC_SUBSYSTEM_CONGESTION               0X09 /* ANSI:For further s
tudy*/
#define SCCP_RLSDC_MTP_FAILURE                        0X0A
#define SCCP_RLSDC_NETWORK_CONGESTION                 0X0B
#define SCCP_RLSDC_RESET_TIMER_EXPIRED                0X0C
#define SCCP_RLSDC_IT_TIMER_EXPIRED                   0X0D
#define SCCP_RLSDC_UNQUALIFIED                        0X0F
#define SCCP_RLSDC_SCCP_FAILURE                       0X10 /* ANSI:Not supported
 */

/* Possible Reset causes 3.13 in ITU-T Q.713, 3.13 in ANSI T1-112.3 */
#define SCCP_RSC_END_USER_ORIGINATED                  0X00
#define SCCP_RSC_SCCP_USER_ORIGINATED                 0X01
#define SCCP_RSC_INCORRECT_PS                         0X02
#define SCCP_RSC_INCORRECT_PR                         0X03
#define SCCP_RSC_RPE_MSG_OUT_OF_WINDOW                0X04
#define SCCP_RSC_RPE_INCORRECT_PS                     0X05
#define SCCP_RSC_RPE_GENERAL                          0X06
#define SCCP_RSC_REMOTE_END_UESR_OPERATIONAL          0X07
#define SCCP_RSC_NETWORK_OPERATIONAL                  0X08
#define SCCP_RSC_ACCESS_OPERATIONAL                   0X09
#define SCCP_RSC_NETWORK_CONGESTION                   0X0A
#define SCCP_RSC_UNQUALIFIED                          0X0C

/* Possible Error causes 3.14 in ITU-T Q.713, 3.14 in ANSI T1-112.3 */
#define SCCP_ERRC_LRN_MISMATCH_UNASSIGNED_DLRN        0X00
#define SCCP_ERRC_LRN_MISMATCH_INCONSISTENT_SLRN      0x01
#define SCCP_ERRC_POINT_CODE_MISMATCH                 0X02
#define SCCP_ERRC_SERVICE_CLASS_MISMATCH              0X03
#define SCCP_ERRC_UNQUALIFIED                         0X04

/* Possible Refusal causes 3.15 in ITU-T Q.713, 3.15 in ANSI T1-112.3 */
#define SCCP_RFC_END_USER_ORIGINATED                  0X00
#define SCCP_RFC_END_USER_CONGESTION                  0X01
#define SCCP_RFC_END_USER_FAILURE                     0X02
#define SCCP_RFC_SCCP_USER_ORIGINATED                 0X03
#define SCCP_RFC_DESTINATION_ADDRESS_UNKNOWN          0X04
#define SCCP_RFC_DESTINATION_INACCESSIBLE             0X05
#define SCCP_RFC_NR_QOS_NOT_AVAILABLE_NON_TRANSIENT   0X06
#define SCCP_RFC_NR_QOS_NOT_AVAILABLE_TRANSIENT       0X07
#define SCCP_RFC_ACCESS_FAILURE                       0X08
#define SCCP_RFC_ACCESS_CONGESTION                    0X09
#define SCCP_RFC_SUBSYSTEM_FAILURE                    0X0A
#define SCCP_RFC_SUBSYSTEM_CONGESTION                 0X0B /* ANSI:Further study
 */
#define SCCP_RFC_CONNECTION_ESTABLISHMENT_TIMER_EXPIERD 0X0C
#define SCCP_RFC_INCOMPATIBLE_USER_DATA               0X0D
#define SCCP_RFC_UNQUALIFIED                          0X0F
#define SCCP_RFC_HOP_COUNTER_VIOLATION                0X10
#define SCCP_RFC_SCCP_FAILURE                         0X11 /* ANSI:Not supported
 */
#define SCCP_RFC_NO_TRANSLATION_ADDR_OF_SUCH_NATURE   0X12
#define SCCP_RFC_UNEQUIPPED_USER                      0X13

#define SCCP_INF_REASON_CONGESTION 1

#define INITIAL_HOP_COUNTER_VALUE   15

#if 0
typedef struct
{
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
	isni_t isni;
#endif

	U8bit gti;
	U8bit gt_len;
	U8bit gt[MAX_GT_LEN];

	Boolean ssn_ind;
	U8bit ssn;
} gtt_ip_t;

typedef struct
{
#if defined (SCCP_ANSI) || defined (SCCP_BCGR)
	isni_t isni;
#endif

	U8bit err_reason;

	U8bit rout_ind;

	pc_t pc;
	Boolean ssn_ind;
	U8bit ssn;

	U8bit gti;
	U8bit gt_len;
	U8bit gt[MAX_GT_LEN];
} gtt_op_t;

#endif /* Amaresh */

#define V_PARAM_LEN_LEN    1
#define O_PARAM_TYPE_LEN   1
#define O_PARAM_LEN_LEN    1
#ifdef SCCP_BROADBAND
#define LONG_V_PARAM_LEN_LEN 2
#endif

/* SCCP parameters name codes in Table 2 ITU-T Q.713, ANSI T1-112.3 */
#define END_OF_OPT_PARAM_TYPE       0x00
#define DLR_PARAM_TYPE              0x01
#define SLR_PARAM_TYPE              0x02
#define CD_PARAM_TYPE               0x03
#define CG_PARAM_TYPE               0x04
#define PROTO_CLASS_PARAM_TYPE      0x05
#define SEG_REASS_PARAM_TYPE        0x06
#define RECV_SEQ_NUM_PARAM_TYPE     0x07
#define SEQ_SEG_PARAM_TYPE          0x08
#define CREDIT_PARAM_TYPE           0x09
#define RLEASE_CAUSE_PARAM_TYPE     0x0A
#define RETURN_CAUSE_PARAM_TYPE     0x0B
#define RESET_CAUSE_PARAM_TYPE      0x0C
#define ERROR_CAUSE_PARAM_TYPE      0X0D
#define REFUSAL_CAUSE_PARAM_TYPE    0x0E
#define DATA_PARAMETER_TYPE         0x0F
#define SEGMENTATION_PARAM_TYPE     0x10
#define HOP_COUNTER_PARAM_TYPE      0x11
#define IMPORTANCE_PARAM_TYPE       0x12
#define ISNI_PARAM_TYPE             0xfa

#define NW_SEGMENTATION_PARAM_LEN      0x4
#define NW_IMPORTANCE_PARAM_LEN        0x1
#define NW_END_OP_OPT_PARAM_LEN        0x1

#define ADDR_IND_LEN       1
#define ADDR_IND_PC_MASK (((sc_opt.standard == STACK_ANSI) || \
				(sc_opt.standard == STACK_BCGR)) ? 0x2 : 0x1) 
#define ADDR_IND_SSN_MASK (((sc_opt.standard == STACK_ANSI) || \
				(sc_opt.standard == STACK_BCGR))? 0x1 : 0x2)  
#define ADDR_IND_GTI_MASK  0x3c
#define ADDR_IND_RI_MASK   0x40

#define CREDIT_PARAM_LEN    	1
#define SEGMENTATION_PARAM_LEN  1
#define IMPORTANCE_PARAM_LEN    1
#define HOP_COUNTER_PARAM_LEN   1

#define SLR_LEN 3

#if defined (SCCP_ANSI) || defined (SCCP_BCGR) || defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)

typedef struct 
{
  U8bit message_type;
  U8bit min_priority;
  U8bit max_priority;
} sccp_message_priority_t;


#if defined (SCCP_ANSI) || defined (SCCP_BCGR) 

#ifdef SCCP_BROADBAND
extern sccp_message_priority_t sccp_message_priority [LUDTS_MSG_TYPE] ;
#else
extern sccp_message_priority_t sccp_message_priority [XUDTS_MSG_TYPE] ;
#endif 
extern sccp_message_priority_t sccp_scmg_message_priority [] ;
#endif

#if defined(SCCP_ETSI) || ( defined(SCCP_ITU) || defined(SCCP_JAPANESE) ) || defined(SCCP_CHINESE)

#ifdef SCCP_BROADBAND
extern sccp_message_priority_t sccp_message_priority_itu [LUDTS_MSG_TYPE] ;
#else
extern sccp_message_priority_t sccp_message_priority_itu [XUDTS_MSG_TYPE] ;
#endif 

#endif 

#endif 


#define MAX_ED_DATA_LEN   32

#endif /* _BS_MSGST_H_ */
