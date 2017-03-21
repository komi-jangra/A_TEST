/*************************************************************** File Header ***
   File Name      : sysxxx_msgopcode.h                                         *
   Purpose        : Contains message opcodes for BSS                           *
   Project        : BSC                                                        *
   Subsystem      : BSS                                                        *
   Author         : Aricent/VNL BSC TEAM                                       *
   Created        : 05/29/2007 11:26:47 AM IST                                 *
   CSCI id        :                                                            *
   Version        : 1.9                                                        *
************************************************************************ End **/

#ifndef __SYSXXX_MSGOPCODE_H 
#define __SYSXXX_MSGOPCODE_H 

/*
 * General guidelines:
 * All messages for one interface starts with base of that interface
 * If a new message is required, it should be added at the end of the interface
 * IMPORTANT NOTE: 
 * Message Opcodes for New Messages/Interface should be added
 * at the end and NOT IN THE BEGINNING OR MIDDLE
 */

/* BSC BASE opcode number: arbitrary number, should be after MSC opcodes */
#define BASE_INTERFACE            500
#define BASE_OPCODE               (BASE_INTERFACE + 0)
                                  
/* IPC framework */               
#define BASE_OPCODE_IPC           (BASE_INTERFACE + 0)
                                  
/** IPC framewok start **/        
#define IPC_BASE_MSG_NUM          (BASE_OPCODE + 0) 
                                  
#define IPC_TIMER                 (IPC_BASE_MSG_NUM + 1)
#define IPC_CALL_CNTXT            (IPC_BASE_MSG_NUM + 2)
#define IPC_CALL_CER              (IPC_BASE_MSG_NUM + 3)
#define IPC_IF_BSSAP_UP           (IPC_BASE_MSG_NUM + 4)
#define IPC_IF_BSSAP_DN           (IPC_BASE_MSG_NUM + 5)
#define IPC_IF_LAPD_UP            (IPC_BASE_MSG_NUM + 6)
#define IPC_IF_LAPD_DN            (IPC_BASE_MSG_NUM + 7)
#define IPC_IF_PM_UP              (IPC_BASE_MSG_NUM + 8)
#define IPC_IF_PM_DN              (IPC_BASE_MSG_NUM + 9)
#define IPC_IF_CSSCM_UP           (IPC_BASE_MSG_NUM + 10)
#define IPC_IF_CSSCM_DN           (IPC_BASE_MSG_NUM + 11)
#define IPC_IF_MGS_UP             (IPC_BASE_MSG_NUM + 12)
#define IPC_IF_MGS_DN             (IPC_BASE_MSG_NUM + 13)
#define IPC_IF_OMC_UP             (IPC_BASE_MSG_NUM + 14)
#define IPC_IF_OMC_DN             (IPC_BASE_MSG_NUM + 15)

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (IPC_BASE_MSG_NUM + 16) to (IPC_BASE_MSG_NUM + 25).
 */
#define IPC_LAST_MSG_NUM          (IPC_BASE_MSG_NUM + 25) 
/** IPC framewok end **/

/* External messages */
/** BSSAP i/f start **/
#define EXT_BSSAP_BASE_MSG_NUM    (IPC_LAST_MSG_NUM + 0)
#define EXT_BSSAP_MSG             (EXT_BSSAP_BASE_MSG_NUM + 1) 
#define EXT_BSSAP_PROP_MSG        (EXT_BSSAP_BASE_MSG_NUM + 2) 
#define EXT_BSSAP_LAST_MSG_NUM    (EXT_BSSAP_BASE_MSG_NUM + 10) 
/** BSSAP i/f end **/

/** LAPD i/f start **/
#define EXT_LAPD_BASE_MSG_NUM     (EXT_BSSAP_LAST_MSG_NUM + 0) 
#define EXT_LAPD_MSG              (EXT_LAPD_BASE_MSG_NUM + 1)  
#define EXT_LAPD_LAST_MSG_NUM     (EXT_LAPD_BASE_MSG_NUM + 10)
/** LAPD i/f end **/

/** TSM i/f start **
 *  Note: Same as MGS
 */
#define EXT_TSM_BASE_MSG_NUM      (EXT_LAPD_LAST_MSG_NUM + 0)
#define EXT_TSM_MSG               (EXT_TSM_BASE_MSG_NUM + 1) 
#define EXT_TSM_LAST_MSG_NUM      (EXT_TSM_BASE_MSG_NUM + 10)
/** TSM i/f end **/

/** OMC i/f start **/
#define EXT_OMC_BASE_MSG_NUM      (EXT_TSM_LAST_MSG_NUM + 0)
#define EXT_OMC_MSG               (EXT_OMC_BASE_MSG_NUM + 1) 
#define EXT_OMC_LAST_MSG_NUM      (EXT_OMC_BASE_MSG_NUM + 10)
/** OMC i/f end **/

/** PM i/f start **/
#define EXT_PM_BASE_MSG_NUM       (EXT_OMC_LAST_MSG_NUM + 0)
#define EXT_PM_MSG                (EXT_PM_BASE_MSG_NUM + 1) 
#define EXT_PM_LAST_MSG_NUM       (EXT_PM_BASE_MSG_NUM + 10)

/** CS SCM i/f start **/
#define EXT_SCM_BASE_MSG_NUM      (EXT_PM_LAST_MSG_NUM + 0)
#define EXT_SCM_MSG               (EXT_SCM_BASE_MSG_NUM + 1) 
#define EXT_SCM_LAST_MSG_NUM      (EXT_SCM_BASE_MSG_NUM + 10) 
/** CS SCM i/f end **/

/* CSAPP subsystem */
/** CPHM i/f **/
/*** Opcodes at Interface between CPHM and ABIHM start ***/
#define CPHM_ABIHM_BASE_MSG_NUM                (EXT_SCM_LAST_MSG_NUM + 0) 

#define CSAPP_ABIHM_CPHM_DATA_IND              (CPHM_ABIHM_BASE_MSG_NUM + 1)  /*CsappAbihmCphmDataInd       */
#define CSAPP_ABIHM_CPHM_ERROR_IND             (CPHM_ABIHM_BASE_MSG_NUM + 2)  /*CsappAbihmCphmErrorInd      */
#define CSAPP_ABIHM_CPHM_ESTABLISH_CNF         (CPHM_ABIHM_BASE_MSG_NUM + 3)  /*CsappAbihmCphmEstCnf        */
#define CSAPP_ABIHM_CPHM_ESTABLISH_IND         (CPHM_ABIHM_BASE_MSG_NUM + 4)  /*CsappAbihmCphmEstInd        */
#define CSAPP_ABIHM_CPHM_RELEASE_CNF           (CPHM_ABIHM_BASE_MSG_NUM + 5)  /*CsappAbihmCphmReleaseCnf    */
#define CSAPP_ABIHM_CPHM_RELEASE_IND           (CPHM_ABIHM_BASE_MSG_NUM + 6)  /*CsappAbihmCphmReleaseInd    */
#define CSAPP_ABIHM_CPHM_UNIT_DATA_IND         (CPHM_ABIHM_BASE_MSG_NUM + 7)  /*CsappAbihmCphmUnitDataInd   */
#define CSAPP_ABIHM_CPHM_CHAN_ACTIVATION_ACK   (CPHM_ABIHM_BASE_MSG_NUM + 8)  /*CsappAbihmCphmChanActAck    */
#define CSAPP_ABIHM_CPHM_CHAN_ACTIVATION_NACK  (CPHM_ABIHM_BASE_MSG_NUM + 9)  /*CsappAbihmCphmChanActNack   */
#define CSAPP_ABIHM_CPHM_CONN_FAILURE_IND      (CPHM_ABIHM_BASE_MSG_NUM + 10) /*CsappAbihmCphmConFailureInd */
#define CSAPP_ABIHM_CPHM_PHY_CTX_CNF           (CPHM_ABIHM_BASE_MSG_NUM + 11) /*CsappAbihmCphmPhyContextCnf */
#define CSAPP_ABIHM_CPHM_RF_CHAN_REL_ACK       (CPHM_ABIHM_BASE_MSG_NUM + 12) /*CsappAbihmCphmRfChanRelAck  */
#define CSAPP_ABIHM_CPHM_CHAN_REQUIRED         (CPHM_ABIHM_BASE_MSG_NUM + 13) /*CsappAbihmCphmChanReq       */
#define CSAPP_ABIHM_CPHM_DELETE_IND            (CPHM_ABIHM_BASE_MSG_NUM + 14) /*CsappAbihmCphmDeleteInd     */
#define CSAPP_ABIHM_CPHM_ERROR_REPORT          (CPHM_ABIHM_BASE_MSG_NUM + 15) /*CsappAbihmCphmErrorReport   */
#define CSAPP_CPHM_ABIHM_DATA_REQ              (CPHM_ABIHM_BASE_MSG_NUM + 16) /*CsappCphmAbihmDataReq       */
#define CSAPP_CPHM_ABIHM_ESTABLISH_REQ         (CPHM_ABIHM_BASE_MSG_NUM + 17) /*CsappCphmAbihmEstReq        */
#define CSAPP_CPHM_ABIHM_RELEASE_REQ           (CPHM_ABIHM_BASE_MSG_NUM + 18) /*CsappCphmAbihmRelReq        */
#define CSAPP_CPHM_ABIHM_UNIT_DATA_REQ         (CPHM_ABIHM_BASE_MSG_NUM + 19) /*CsappCphmAbihmUnitDataReq   */
#define CSAPP_CPHM_ABIHM_CHAN_ACT_REQ          (CPHM_ABIHM_BASE_MSG_NUM + 20) /*CsappCphmAbihmChanActReq    */
#define CSAPP_CPHM_ABIHM_DEACTIVATE_SACCH      (CPHM_ABIHM_BASE_MSG_NUM + 21) /*CsappCphmAbihmDeactivateSacc*/
#define CSAPP_CPHM_ABIHM_ENCRYPTION_CMD        (CPHM_ABIHM_BASE_MSG_NUM + 22) /*CsappCphmAbihmEncryptCmd    */
#define CSAPP_CPHM_ABIHM_RF_CHAN_REL           (CPHM_ABIHM_BASE_MSG_NUM + 23) /*CsappCphmAbihmRfChanRel     */
#define CSAPP_CPHM_ABIHM_IMM_ASSIGN_CMD        (CPHM_ABIHM_BASE_MSG_NUM + 24) /*CsappCphmAbihmImmAssCmd     */
#define CSAPP_ABIHM_CPHM_LINK_UP_IND           (CPHM_ABIHM_BASE_MSG_NUM + 25) /*CsappAbihmCphmLinkUpInd     */
#define CSAPP_ABIHM_CPHM_LINK_DOWN_IND         (CPHM_ABIHM_BASE_MSG_NUM + 26) /*CsappAbihmCphmLinkDownInd   */
#define CSAPP_CPHM_ABIHM_SM_CONF_REQ           (CPHM_ABIHM_BASE_MSG_NUM + 27) /*CsappCphmAbihmSmConfReq     */
#define CSAPP_ABIHM_CPHM_SM_CONF_ACK           (CPHM_ABIHM_BASE_MSG_NUM + 28) /*CsappAbihmCphmSmConfAck     */
#define CSAPP_ABIHM_CPHM_SM_CONF_NACK          (CPHM_ABIHM_BASE_MSG_NUM + 29) /*CsappAbihmCphmSmConfNack    */
#define CSAPP_CPHM_ABIHM_TM_STATUS_INQ         (CPHM_ABIHM_BASE_MSG_NUM + 30) /*CsappCphmAbihmTmStatInq     */
#define CSAPP_ABIHM_CPHM_TM_STATUS_REP         (CPHM_ABIHM_BASE_MSG_NUM + 31) /*CsappAbihmCphmTmStatRep     */
/*Added For CS3.0*/
#define CSAPP_ABIHM_CPHM_HO_DET                (CPHM_ABIHM_BASE_MSG_NUM + 32) /*CsappAbihmCphmHoDet         */
/*Added For R3 : HO Power Boost */
#define CSAPP_CPHM_ABIHM_BS_PWR_CTRL           (CPHM_ABIHM_BASE_MSG_NUM + 33) /*CsappAbihmCphmHoDet         */
#define	CSAPP_CPHM_ABIHM_MODE_MODIFY_REQ	     (CPHM_ABIHM_BASE_MSG_NUM + 34)
#define CSAPP_ABIHM_CPHM_MODE_MODIFY_ACK	     (CPHM_ABIHM_BASE_MSG_NUM + 35)
#define CSAPP_ABIHM_CPHM_MODE_MODIFY_NACK   	 (CPHM_ABIHM_BASE_MSG_NUM + 36)

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (CPHM_ABIHM_BASE_MSG_NUM + 28) to (CPHM_ABIHM_BASE_MSG_NUM + 36).
 */
#define CPHM_ABIHM_LAST_MSG_NUM                (CPHM_ABIHM_BASE_MSG_NUM + 37) 
/*** Opcodes at Interface between CPHM and ABIHM end ***/

/*** Opcodes at Interface between CPHM and RRAL start ***/
#define RRAL_CPHM_BASE_MSG_NUM                 (CPHM_ABIHM_LAST_MSG_NUM + 0)

#define CSAPP_CPHM_RRAL_CHAN_ALLOC_REQ         (RRAL_CPHM_BASE_MSG_NUM + 1) /*CsappCphmGrhmChanAllocReq*/
#define CSAPP_CPHM_RRAL_CHAN_DEALLOC_REQ       (RRAL_CPHM_BASE_MSG_NUM + 2) /*CsappCphmGrhmChanDeallocReq*/
#define CSAPP_CPHM_RRAL_RESOURCE_DEALLOC_REQ   (RRAL_CPHM_BASE_MSG_NUM + 3) /*CsappCphmGrhmResourceDeallocReq*/
#define CSAPP_RRAL_CPHM_CHAN_ALLOC_NACK        (RRAL_CPHM_BASE_MSG_NUM + 4) /*CsappGrhmCphmChanAllocNack*/
#define CSAPP_RRAL_CPHM_CHAN_ALLOC_ACK         (RRAL_CPHM_BASE_MSG_NUM + 5) /*CsappGrhmCphmChanAllocAck*/
#define CSAPP_RRAL_CPHM_BPC_RELEASE            (RRAL_CPHM_BASE_MSG_NUM + 6) /*CsappGrhmCphmBpcRelease*/
/*Added For CS3.0*/
#define CSAPP_CPHM_RRAL_TCH_ALLOC_REQ          (RRAL_CPHM_BASE_MSG_NUM + 7) /*CsappCphmGrhmTchAllocReq*/
#define CSAPP_RRAL_CPHM_TCH_ALLOC_NACK         (RRAL_CPHM_BASE_MSG_NUM + 8) /*CsappGrhmCphmTchAllocNack*/
#define CSAPP_RRAL_CPHM_TCH_ALLOC_ACK          (RRAL_CPHM_BASE_MSG_NUM + 9) /*CsappGrhmCphmTchAllocAck*/
#define CSAPP_CPHM_RRAL_RESOURCE_CONNECT_REQ   (RRAL_CPHM_BASE_MSG_NUM + 10) /*CsappCphmGrhmResourceConnectReq*/
#define CSAPP_RRAL_CPHM_RESOURCE_CONNECT_NACK  (RRAL_CPHM_BASE_MSG_NUM + 11) /*CsappGrhmCphmResourceConnectNack*/
#define CSAPP_RRAL_CPHM_RESOURCE_CONNECT_ACK   (RRAL_CPHM_BASE_MSG_NUM + 12) /*CsappGrhmCphmResourceConnectAck*/
/*  NCELL_CIC PROBLEM CHANGES STARTS*/
#define CSAPP_CPHM_RRAL_CKT_SWAP_REQ           (RRAL_CPHM_BASE_MSG_NUM + 13) /*CsappCphmGrhmCktSwapReq*/
#define CSAPP_RRAL_CPHM_CKT_SWAP_RESP          (RRAL_CPHM_BASE_MSG_NUM + 14) /*CsappCphmGrhmCktSwapAck*/
#define CSAPP_RRAL_CPHM_INTRA_CELL_HANDOVER_REQ  (RRAL_CPHM_BASE_MSG_NUM + 15) //CsappGrhmCphmIntraCellHandoverReq
#define CSAPP_CPHM_RRAL_INTRA_CELL_HANDOVER_FAIL (RRAL_CPHM_BASE_MSG_NUM + 16) //CsappCphmGrhmIntraCellHandoverFail
/*  NCELL_CIC PROBLEM CHANGES ENDS*/
#define CSAPP_CPHM_RRAL_HA_CNTXT_DATA           (RRAL_CPHM_BASE_MSG_NUM + 17) /*CsappCphmRralHaCntxtData*/

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (RRAL_CPHM_BASE_MSG_NUM + 17) to (RRAL_CPHM_BASE_MSG_NUM + 20).
 */
#define RRAL_CPHM_LAST_MSG_NUM                 (RRAL_CPHM_BASE_MSG_NUM + 21)
/*** Opcodes at Interface between CPHM and RRAL end ***/
#define	RRAL_MRHM_BASE_MSG_NUM								(RRAL_CPHM_LAST_MSG_NUM)
#define	CSAPP_RRAL_MRHM_START_TBHO_IND				(RRAL_MRHM_BASE_MSG_NUM + 1)
#define	RRAL_MRHM_LAST_MSG_NUM								(RRAL_MRHM_BASE_MSG_NUM + 5)

/*** Opcodes at Interface between CPHM and MRHM start ***/
#define CPHM_MRHM_BASE_MSG_NUM                 (RRAL_MRHM_LAST_MSG_NUM + 0) 

#define CSAPP_CPHM_MRHM_START_MEAS             (CPHM_MRHM_BASE_MSG_NUM + 1) /*CsappCphmMrhmStartMeas*/
#define CSAPP_CPHM_MRHM_STOP_MEAS              (CPHM_MRHM_BASE_MSG_NUM + 2) /*CsappCphmMrhmStopMeas*/
#define CSAPP_CPHM_MRHM_PWR_PARAMS_REQ         (CPHM_MRHM_BASE_MSG_NUM + 3) /*CsappCphmMrhmPwrParamsReq*/
#define CSAPP_MRHM_CPHM_PWR_PARAMS_RESP        (CPHM_MRHM_BASE_MSG_NUM + 4) /*CsappMrhmCphmPwrParamsResp*/
/*! To be removed as RLTO macro is no more needed
		this is the reason these two macros are having same value.
*/
#define CSAPP_MRHM_CPHM_RLTO_IND               (CPHM_MRHM_BASE_MSG_NUM + 5) /*CsappMrhmCphmRltoInd*/
#define CSAPP_MRHM_CPHM_REL_IND                (CPHM_MRHM_BASE_MSG_NUM + 5) /*CsappMrhmCphmRelInd*/
/*Added for CS3.0*/
#define CSAPP_MRHM_CPHM_HO_RQD                 (CPHM_MRHM_BASE_MSG_NUM + 6) /*CsappMrhmCphmHoRqd*/
#define CSAPP_CPHM_MRHM_RESUME                 (CPHM_MRHM_BASE_MSG_NUM + 7) /*CsappCphmMrhmResume*/

/*End- Added for CS3.0*/
/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (CPHM_MRHM_BASE_MSG_NUM + 8) to (CPHM_MRHM_BASE_MSG_NUM + 15).
 */
#define CPHM_MRHM_LAST_MSG_NUM                 (CPHM_MRHM_BASE_MSG_NUM + 15) 
/*** Opcodes at Interface between CPHM and MRHM end ***/

/*** Opcodes at Interface between ABIHM and CFG start ***/
#define ABIHM_CFG_BASE_MSG_NUM                 (CPHM_MRHM_LAST_MSG_NUM + 0)
/*Change Start: R3-BSC
  Dated: 03-Aug-2011
*/

/* Between ABIHM to CFG */

#define CSAPP_ABIHM_CFG_IP_LINK_UP_IND         (ABIHM_CFG_BASE_MSG_NUM + 1)
#define CSAPP_ABIHM_CFG_IP_LINK_DOWN_IND       (ABIHM_CFG_BASE_MSG_NUM + 2)
#define CSAPP_ABIHM_CFG_PROC_UP_IND            (ABIHM_CFG_BASE_MSG_NUM + 3)
                                               
#define CSAPP_ABIHM_CFG_LAST_MSG_NUM           (ABIHM_CFG_BASE_MSG_NUM + 20)

/* Between CFG to ABIHM */

#define OAMS_CFG_ABIHM_BASE_MSG_NUM            (CSAPP_ABIHM_CFG_LAST_MSG_NUM + 0)
#define OAMS_CFG_ABIHM_DEL_BTS_IND             (OAMS_CFG_ABIHM_BASE_MSG_NUM + 1)
#define OAMS_CFG_ABIHM_DEL_TRX_IND             (OAMS_CFG_ABIHM_BASE_MSG_NUM + 2)
#define OAMS_CFG_ABIHM_ADD_BTS_IND             (OAMS_CFG_ABIHM_BASE_MSG_NUM + 3)
#define OAMS_CFG_ABIHM_ADD_TRX_IND             (OAMS_CFG_ABIHM_BASE_MSG_NUM + 4)
#define OAMS_CFG_ABIHM_ASSOC_DISC_REQ          (OAMS_CFG_ABIHM_BASE_MSG_NUM + 5)


/*Change End : R3-BSC
  Dated: 03-Aug-2011
*/
#define ABIHM_CFG_LAST_MSG_NUM                 (OAMS_CFG_ABIHM_BASE_MSG_NUM + 20)

/*** Opcodes at Interface between ABIHM and CFG end ***/
/*** Opcodes at Interface between CPHM and AIFDHM start ***/
#define AIFDHM_CPHM_BASE_MSG_NUM                       (ABIHM_CFG_LAST_MSG_NUM + 0)
                                                       
#define CSAPP_CPHM_AIFDHM_COMP_L3_MSG                  (AIFDHM_CPHM_BASE_MSG_NUM + 1) /*CsappCphmAifdhmCompL3Msg*/ 
#define CSAPP_AIFDHM_CPHM_SCCP_CON_STATUS              (AIFDHM_CPHM_BASE_MSG_NUM + 2) /*CsappAifdhmCphmSccpConStatus*/ 
#define CSAPP_CPHM_AIFDHM_SCCP_CON_REL                 (AIFDHM_CPHM_BASE_MSG_NUM + 3) /*CsappCphmAifdhmSccpConRel*/    
#define CSAPP_AIFDHM_CPHM_CIPHER_MODE_CMD              (AIFDHM_CPHM_BASE_MSG_NUM + 4) /*CsappAifdhmCphmCipherModeCmd*/  
#define CSAPP_CPHM_AIFDHM_CIPHER_MODE_CMP              (AIFDHM_CPHM_BASE_MSG_NUM + 5) /*CsappCphmAifdhmCipherModeCmp*/ 
#define CSAPP_CPHM_AIFDHM_CIPHER_MODE_REJ              (AIFDHM_CPHM_BASE_MSG_NUM + 6) /*CsappCphmAifdhmCipherModeRej*/  
#define CSAPP_AIFDHM_CPHM_ASSIGN_REQ                   (AIFDHM_CPHM_BASE_MSG_NUM + 7) /*CsappAifdhmCphmAssignReq*/  
#define CSAPP_CPHM_AIFDHM_CLEAR_REQ                    (AIFDHM_CPHM_BASE_MSG_NUM + 8) /*CsappCphmAifdhmClearReq*/
#define CSAPP_CPHM_AIFDHM_ASSIGN_CMP                   (AIFDHM_CPHM_BASE_MSG_NUM + 9) /*CsappCphmAifdhmAssignCmp*/   
#define CSAPP_CPHM_AIFDHM_ASSIGN_FAILURE               (AIFDHM_CPHM_BASE_MSG_NUM + 10) /*CsappCphmAifdhmAssignFailure*/
#define CSAPP_CPHM_AIFDHM_CLEAR_CMP                    (AIFDHM_CPHM_BASE_MSG_NUM + 11) /*CsappCphmAifdhmClearCmp*/  
#define CSAPP_CPHM_AIFDHM_DTAP_DATA_REQ                (AIFDHM_CPHM_BASE_MSG_NUM + 12) /*CsappCphmAifdhmDtapDataReq*/ 
#define CSAPP_AIFDHM_CPHM_DTAP_DATA_IND                (AIFDHM_CPHM_BASE_MSG_NUM + 13) /*CsappAifdhmCphmDtapDataInd*/
#define CSAPP_AIFDHM_CPHM_CLEAR_CMD                    (AIFDHM_CPHM_BASE_MSG_NUM + 14) /*CsappAifdhmCphmClearCmd*/ 
#define CSAPP_CPHM_AIFDHM_SAPI_N_REJ                   (AIFDHM_CPHM_BASE_MSG_NUM + 15) /*CsappCphmAifdhmSapiNRej*/
#define CSAPP_CPHM_AIFDHM_CLASSMARK_UPDATE             (AIFDHM_CPHM_BASE_MSG_NUM + 16) /*CsappCphmAifdhmClassmarkUpdate*/
/*Added for CS3.0*/                                    
#define CSAPP_AIFDHM_CPHM_HANDOVER_REQUEST             (AIFDHM_CPHM_BASE_MSG_NUM + 17) /*CsappAifdhmCphmHandoverRequest*/
#define CSAPP_CPHM_AIFDHM_HANDOVER_REQUIRED            (AIFDHM_CPHM_BASE_MSG_NUM + 18) /*CsappCphmAifdhmHandoverRequired*/
#define CSAPP_CPHM_AIFDHM_HANDOVER_REQUEST_ACK         (AIFDHM_CPHM_BASE_MSG_NUM + 19) /*CsappCphmAifdhmHandoverRequestAck*/
#define CSAPP_AIFDHM_CPHM_HANDOVER_COMMAND             (AIFDHM_CPHM_BASE_MSG_NUM + 20) /*CsappAifdhmCphmHandoverCommand*/
#define CSAPP_CPHM_AIFDHM_HANDOVER_COMPLETE            (AIFDHM_CPHM_BASE_MSG_NUM + 21) /*CsappCphmAifdhmHandoverComplete*/
#define CSAPP_CPHM_AIFDHM_HANDOVER_FAILURE             (AIFDHM_CPHM_BASE_MSG_NUM + 22) /*CsappCphmAifdhmHandoverFailure*/
#define CSAPP_AIFDHM_CPHM_HANDOVER_REQUIRED_REJECT     (AIFDHM_CPHM_BASE_MSG_NUM + 23) /*CsappAifdhmCphmHandoverRequiredReject*/
#define CSAPP_CPHM_AIFDHM_HANDOVER_DETECT              (AIFDHM_CPHM_BASE_MSG_NUM + 24) /*CsappCphmAifdhmHandoverDetect*/
#define CSAPP_CPHM_AIFDHM_HANDOVER_PERFORMED           (AIFDHM_CPHM_BASE_MSG_NUM + 25) /*CsappCphmAifdhmHandoverPerformed*/
#define CSAPP_AIFDHM_CPHM_HANDOVER_SUCCEEDED           (AIFDHM_CPHM_BASE_MSG_NUM + 26) /*CsappAifdhmCphmHandoverSucceeded*/
#define CSAPP_AIFDHM_CPHM_HANDOVER_CANDIDATE_ENQUIRE   (AIFDHM_CPHM_BASE_MSG_NUM + 27) /*CsappAifdhmCphmHandoverCandidateEnquire*/
#define CSAPP_CPHM_AIFDHM_HANDOVER_CANDIDATE_RESPONSE  (AIFDHM_CPHM_BASE_MSG_NUM + 28) /*CsappCphmAifdhmHandoverCandidateResp*/
#define CSAPP_AIFDHM_CPHM_HANDOVER_FAILURE_IND         (AIFDHM_CPHM_BASE_MSG_NUM + 29) /*CsappAifdhmCphmHandoverFailureInd*/
#define CSAPP_AIFDHM_CPHM_BSSAP_PROTOCOL_ERROR_IND     (AIFDHM_CPHM_BASE_MSG_NUM + 30) /*CsappAifdhmCphmBssapProtocolErrorInd*/
/* Change Start: R3-BSC
   Dated: 3-Aug-2011
*/

#define CSAPP_CPHM_AIFDHM_CHG_APPID_CALL_REFID_REQ     (AIFDHM_CPHM_BASE_MSG_NUM + 32)
#define CSAPP_AIFDHM_CPHM_CHG_APPID_CALL_REFID_RSP     (AIFDHM_CPHM_BASE_MSG_NUM + 33)

/* Added on 14 Sep 2012: For LCLS Feature */
#define CSAPP_CPHM_AIFDHM_LCLS_CONNECT_CONTROL_ACK		 (AIFDHM_CPHM_BASE_MSG_NUM + 34)
#define CSAPP_CPHM_AIFDHM_LCLS_NOTIFICATION						 (AIFDHM_CPHM_BASE_MSG_NUM + 35)
#define CSAPP_AIFDHM_CPHM_LCLS_CONNECT_CONTROL				 (AIFDHM_CPHM_BASE_MSG_NUM + 36)

/* Change End: R3-BSC
   Dated: 3-Aug-2011
*/



/* New Message Opcodes for this interface to be inserted here.
 dfimst-* Available Opcodes: 
 * from (AIFDHM_CPHM_BASE_MSG_NUM + 30) to (AIFDHM_CPHM_BASE_MSG_NUM + 38).
 */
#define AIFDHM_CPHM_LAST_MSG_NUM               (AIFDHM_CPHM_BASE_MSG_NUM + 38)
/*** Opcodes at Interface between CPHM and AIFDHM end ***/

/*** Opcodes at Interface between CPHM and OAM ***/
/**** CPHM and PTDC start ***/
#define CPHM_PTDC_BASE_MSG_NUM                 (AIFDHM_CPHM_LAST_MSG_NUM + 0)
#define CSAPP_CPHM_PTDC_CER_IND                (CPHM_PTDC_BASE_MSG_NUM + 1) /*CsappCphmPtdcCerInd*/

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (CPHM_PTDC_BASE_MSG_NUM + 2) to (CPHM_PTDC_BASE_MSG_NUM + 11).
 */
#define CPHM_PTDC_LAST_MSG_NUM                 (CPHM_PTDC_BASE_MSG_NUM + 11)
/**** CPHM and PTDC end ***/

/** MRHM i/f **/
/*** Opcodes at Interface between ABIHM and MRHM start ***/
#define MRHM_ABIHM_BASE_MSG_NUM                (CPHM_PTDC_LAST_MSG_NUM + 0) 

#define CSAPP_ABIHM_MRHM_LINK_UP_IND           (MRHM_ABIHM_BASE_MSG_NUM + 1)
#define CSAPP_ABIHM_MRHM_LINK_DOWN_IND         (MRHM_ABIHM_BASE_MSG_NUM + 2)
#define CSAPP_ABIHM_MRHM_MEAS_RESULT           (MRHM_ABIHM_BASE_MSG_NUM + 3) /*CsappAbihmMrhmMeasResult*/
#define CSAPP_MRHM_ABIHM_BS_PWR_CTRL           (MRHM_ABIHM_BASE_MSG_NUM + 4) /*CsappMrhmAbihmBsPwrCtrl*/
#define CSAPP_MRHM_ABIHM_MS_PWR_CTRL           (MRHM_ABIHM_BASE_MSG_NUM + 5) /*CsappMrhmAbihmMsPwrCtrl*/
/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (MRHM_ABIHM_BASE_MSG_NUM + 6) to (MRHM_ABIHM_BASE_MSG_NUM + 15).
 */
#define MRHM_ABIHM_LAST_MSG_NUM                (MRHM_ABIHM_BASE_MSG_NUM + 15) 
/*** Opcodes at Interface between ABIHM and MRHM end ***/

/** RRAL i/f **/
/*** Opcodes at Interface between IFML  and AIFDHM ***/
#define IFML_AIFDHM_BASE_MSG_NUM                  (MRHM_ABIHM_LAST_MSG_NUM + 0)

#define CSAPP_AIFDHM_IFML_BLOCK                    (IFML_AIFDHM_BASE_MSG_NUM + 1) /*CsappAifdhmGrhmBlock*/
#define CSAPP_AIFDHM_IFML_UNBLOCK                  (IFML_AIFDHM_BASE_MSG_NUM + 2) /*CsappAifdhmGrhmUnblock*/
#define CSAPP_AIFDHM_IFML_CKT_GROUP_BLOCK          (IFML_AIFDHM_BASE_MSG_NUM + 3) /*CsappAifdhmGrhmCktGroupBlock*/
#define CSAPP_AIFDHM_IFML_CKT_GROUP_UNBLOCK        (IFML_AIFDHM_BASE_MSG_NUM + 4) /*CsappAifdhmGrhmCktGroupUnblock*/
#define CSAPP_AIFDHM_IFML_RESET_CKT                (IFML_AIFDHM_BASE_MSG_NUM + 5) /*CsappAifdhmGrhmResetCkt*/
#define CSAPP_AIFDHM_IFML_RESET                    (IFML_AIFDHM_BASE_MSG_NUM + 6) /*CsappAifdhmGrhmReset*/
#define CSAPP_AIFDHM_IFML_BLOCK_ACK                (IFML_AIFDHM_BASE_MSG_NUM + 7) /*CsappAifdhmGrhmBlockAck*/
#define CSAPP_AIFDHM_IFML_UNBLOCK_ACK              (IFML_AIFDHM_BASE_MSG_NUM + 8) /*CsappAifdhmGrhmUnblockAck*/
#define CSAPP_AIFDHM_IFML_CKT_GROUP_BLOCK_ACK      (IFML_AIFDHM_BASE_MSG_NUM + 9) /*CsappAifdhmGrhmCktGroupBlockAck*/
#define CSAPP_AIFDHM_IFML_CKT_GROUP_UNBLOCK_ACK    (IFML_AIFDHM_BASE_MSG_NUM + 10) /*CsappAifdhmGrhmCktGroupUnblockAck*/
#define CSAPP_AIFDHM_IFML_RESET_CKT_ACK            (IFML_AIFDHM_BASE_MSG_NUM + 11) /*CsappAifdhmGrhmResetCktAck*/
#define CSAPP_AIFDHM_IFML_RESET_ACK                (IFML_AIFDHM_BASE_MSG_NUM + 12) /*CsappAifdhmGrhmResetAck*/
#define CSAPP_AIFDHM_IFML_UNEQUIPPED_CKT           (IFML_AIFDHM_BASE_MSG_NUM + 13) /*CsappAifdhmGrhmUnequippedCkt*/
#define CSAPP_AIFDHM_IFML_BSSAP_PROTOCOL_ERROR_IND (IFML_AIFDHM_BASE_MSG_NUM + 14) /*CsappAifdhmGrhmBssapProtocolErrorInd*/
#define CSAPP_AIFDHM_IFML_BSSAP_NETWORK_STATUS     (IFML_AIFDHM_BASE_MSG_NUM + 15) /*CsappAifdhmGrhmBssapNetworkStatus*/
#define OAMS_IFML_AIFDHM_BLOCK                     (IFML_AIFDHM_BASE_MSG_NUM + 16) /*CsappGrhmAifdhmBlock*/
#define OAMS_IFML_AIFDHM_UNBLOCK                   (IFML_AIFDHM_BASE_MSG_NUM + 17) /*CsappGrhmAifdhmUnblock*/
#define OAMS_IFML_AIFDHM_CKT_GROUP_BLOCK           (IFML_AIFDHM_BASE_MSG_NUM + 18) /*CsappGrhmAifdhmCktGroupBlock*/
#define OAMS_IFML_AIFDHM_CKT_GROUP_UNBLOCK         (IFML_AIFDHM_BASE_MSG_NUM + 19) /*CsappGrhmAifdhmCktGroupUnblock*/
#define OAMS_IFML_AIFDHM_RESET_CKT                 (IFML_AIFDHM_BASE_MSG_NUM + 20) /*CsappGrhmAifdhmResetCkt*/
#define OAMS_IFML_AIFDHM_RESET                     (IFML_AIFDHM_BASE_MSG_NUM + 21) /*CsappGrhmAifdhmReset*/
#define OAMS_IFML_AIFDHM_BLOCK_ACK                 (IFML_AIFDHM_BASE_MSG_NUM + 22) /*CsappGrhmAifdhmBlockAck*/
#define OAMS_IFML_AIFDHM_UNBLOCK_ACK               (IFML_AIFDHM_BASE_MSG_NUM + 23) /*CsappGrhmAifdhmUnblockAck*/
#define OAMS_IFML_AIFDHM_CKT_GROUP_BLOCK_ACK       (IFML_AIFDHM_BASE_MSG_NUM + 24) /*CsappGrhmAifdhmCktGroupBlockAck*/
#define OAMS_IFML_AIFDHM_CKT_GROUP_UNBLOCK_ACK     (IFML_AIFDHM_BASE_MSG_NUM + 25) /*CsappGrhmAifdhmCktGroupUnblockAck*/
#define OAMS_IFML_AIFDHM_RESET_CKT_ACK             (IFML_AIFDHM_BASE_MSG_NUM + 26) /*CsappGrhmAifdhmResetCktAck*/
#define OAMS_IFML_AIFDHM_RESET_ACK                 (IFML_AIFDHM_BASE_MSG_NUM + 27) /*CsappGrhmAifdhmResetAck*/
#define OAMS_IFML_AIFDHM_UNEQUIPPED_CKT            (IFML_AIFDHM_BASE_MSG_NUM + 28) /*CsappGrhmAifdhmUnequippedCkt*/
#define CSAPP_AIFDHM_IFML_TIMEOUT_IND              (IFML_AIFDHM_BASE_MSG_NUM + 29) /*CsappAifdhmGrhmTimeoutInd*/
#define CSAPP_AIFDHM_IFML_RESET_IP_RESOURCE        (IFML_AIFDHM_BASE_MSG_NUM + 30) /*CsappAifdhmIfmlResetIpResource*/
#define OAMS_IFML_AIFDHM_RESET_IP_RESOURCE_ACK     (IFML_AIFDHM_BASE_MSG_NUM + 31) /*CsappAifdhmIfmlResetIpResourceAck*/
#define OAMS_IFML_AIFDHM_RESET_IP_RESOURCE         (IFML_AIFDHM_BASE_MSG_NUM + 32) /*OamsIfmlAifdhmResetIpResource*/
#define CSAPP_AIFDHM_IFML_RESET_IP_RESOURCE_ACK    (IFML_AIFDHM_BASE_MSG_NUM + 33) /*CsappAifdhmIfmlResetIpResourceAck*/

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (IFML_AIFDHM_BASE_MSG_NUM + 30) to (IFML_AIFDHM_BASE_MSG_NUM + 38).
 */
#define IFML_AIFDHM_LAST_MSG_NUM                  (IFML_AIFDHM_BASE_MSG_NUM + 38)
/*** Opcodes at Interface between IFML and AIFDHM  end ***/

/*** Opcodes at Interface between RRAL and TRXH start ***/
#define RRAL_TRXH_BASE_MSG_NUM                 (IFML_AIFDHM_LAST_MSG_NUM + 0)

#define OAMS_TRXH_RRAL_CRE_CHN_REQ             (RRAL_TRXH_BASE_MSG_NUM + 1) /*OamsTrxhGrhmCreChanReq*/
#define CSAPP_RRAL_TRXH_CRE_CHN_ACK            (RRAL_TRXH_BASE_MSG_NUM + 2) /*CsappGrhmTrxhCreChanAck*/
#define CSAPP_RRAL_TRXH_CRE_CHN_NACK           (RRAL_TRXH_BASE_MSG_NUM + 3) /*CsappGrhmTrxhCreChanNack*/
#define OAMS_TRXH_RRAL_DEL_CHN_REQ             (RRAL_TRXH_BASE_MSG_NUM + 4) /*OamsTrxhGrhmDelChanReq*/
#define CSAPP_RRAL_TRXH_DEL_CHN_ACK            (RRAL_TRXH_BASE_MSG_NUM + 5) /*CsappGrhmTrxhDelChanAck*/
/*Changes PCU R2.5 -- START*/
#define OAMS_TRXH_RRAL_TRS_IND                 (RRAL_TRXH_BASE_MSG_NUM + 6) /*OamsTrxhGrhmTrsInd*/
/*Changes PCU R2.5 -- END*/
/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (RRAL_TRXH_BASE_MSG_NUM + 8) to (RRAL_TRXH_BASE_MSG_NUM + 15).
 */
/* R2.5.5 - ABIS HA Changes : Start */
#define OAMS_TRXH_RRAL_TRX_OPER_STATE_IND      (RRAL_TRXH_BASE_MSG_NUM + 7) /*OamsTrxhGrhmTrxOperStateInd*/
/* #define OAMS_TRXH_RRAL_RRAL_INIT_IND        (RRAL_TRXH_BASE_MSG_NUM + 8)*/ /*OamsTrxhGrhmRrAlInitInd*/
/* R2.5.5 - ABIS HA Changes : End */

#define RRAL_TRXH_LAST_MSG_NUM                 (RRAL_TRXH_BASE_MSG_NUM + 15)
/*** Opcodes at Interface between RRAL and TRXH end ***/

/*** Opcodes at Interface between RRAL and CFG start ***/
#define RRAL_CFG_BASE_MSG_NUM                  (RRAL_TRXH_LAST_MSG_NUM)

#define OAMS_CFG_IFML_LOCK_REQ                 (RRAL_CFG_BASE_MSG_NUM + 1) /*OamsCfgIfmlLockReq*/
#define OAMS_IFML_CFG_LOCK_RESP                (RRAL_CFG_BASE_MSG_NUM + 2) /*OamsIfmlCfgLockResp*/
#define OAMS_CFG_IFML_UNLOCK_REQ               (RRAL_CFG_BASE_MSG_NUM + 3) /*OamsCfgIfmlUnlockReq*/
#define OAMS_IFML_CFG_ALARM_IND                (RRAL_CFG_BASE_MSG_NUM + 4) /*OamsIfmlCfgAlarmInd*/
#define OAMS_IFML_CFG_UNLOCK_RESP              (RRAL_CFG_BASE_MSG_NUM + 5) /*OomsIfmlCfgUnlockResp*/
#define OAMS_IFML_CFG_UNLOCK_FAIL              (RRAL_CFG_BASE_MSG_NUM + 6) /*OamsIfmlCfgUnlockFail*/
#define OAMS_CFG_RRAL_BSS_INFO_UPD_IND         (RRAL_CFG_BASE_MSG_NUM + 7) 
#define OAMS_CFG_RRAL_CELL_INFO_UPD_IND        (RRAL_CFG_BASE_MSG_NUM + 8) 

#define RRAL_CFG_LAST_MSG_NUM                  (RRAL_CFG_BASE_MSG_NUM + 18)
/*** Opcodes at Interface between RRAL and CFG end ***/

/*** Opcodes at Interface between RRAL and TSM ***/
/**** 
 **** There will be single opcode for communication with TSM. 
 **** The further messages are part of payload. Values should be taken from MGS
 **** header file: mgs_common_hashdef.h
 ****/

#define RRAL_TSM_BASE_MSG_NUM                  (RRAL_CFG_LAST_MSG_NUM + 0)                     

/*#define MGS_TSM_RRAL_DATA_IND                   EXT_TSM_MSG */ 
/*#define CSAPP_RRAL_TSM_DATA_REQ                 EXT_TSM_MSG */

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (RRAL_TSM_BASE_MSG_NUM + 2) to (RRAL_TSM_BASE_MSG_NUM + 11).
 */
#define RRAL_TSM_LAST_MSG_NUM                  (RRAL_TSM_BASE_MSG_NUM + 11)            

/** PHM i/f **/
/*** Opcodes at Interface between PHM and AIFDHM start ***/
#define AIFDHM_PHM_BASE_MSG_NUM                (RRAL_TSM_LAST_MSG_NUM + 0)
#define CSAPP_AIFDHM_PHM_PAGING                (AIFDHM_PHM_BASE_MSG_NUM + 1) /*CsappAifdhmPhmPaging*/   

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (AIFDHM_PHM_BASE_MSG_NUM + 2) to (AIFDHM_PHM_BASE_MSG_NUM + 11).
 */
#define AIFDHM_PHM_LAST_MSG_NUM                (AIFDHM_PHM_BASE_MSG_NUM + 11)
/*** Opcodes at Interface between PHM and AIFDHM end ***/

/*** Opcodes at Interface between PHM and ABIHM start ***/
#define ABIHM_PHM_BASE_MSG_NUM                 (AIFDHM_PHM_LAST_MSG_NUM +0)
#define CSAPP_PHM_ABIHM_PAGING_CMD             (ABIHM_PHM_BASE_MSG_NUM + 1) /*CsappPhmAbihmPagingCmd*/    

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (ABIHM_PHM_BASE_MSG_NUM + 2) to (ABIHM_PHM_BASE_MSG_NUM + 11).
 */
#define ABIHM_PHM_LAST_MSG_NUM                 (ABIHM_PHM_BASE_MSG_NUM + 11)
/*** Opcodes at Interface between PHM and ABIHM end ***/

/** ABIHM i/f **/
/*** Opcodes at Interface between ABIHM and TRXH start ***/
#define ABIHM_TRXH_BASE_MSG_NUM                    (ABIHM_PHM_LAST_MSG_NUM + 0)

#define OAMS_TRXH_ABIHM_SET_BTS_ATTR_REQ           (ABIHM_TRXH_BASE_MSG_NUM + 1) /*OamsTrxhAbihmSetBtsAttrReq*/
#define CSAPP_ABIHM_TRXH_SET_BTS_ATTR_ACK          (ABIHM_TRXH_BASE_MSG_NUM + 2) /*CsappAbihmTrxhSetBtsAttrAck*/
#define CSAPP_ABIHM_TRXH_SET_BTS_ATTR_NACK         (ABIHM_TRXH_BASE_MSG_NUM + 3) /*CsappAbihmTrxhSetBtsAttrNack*/
#define OAMS_TRXH_ABIHM_SET_CHAN_ATTR_REQ          (ABIHM_TRXH_BASE_MSG_NUM + 4) /*OamsTrxhAbihmSetChanAttrReq*/
#define CSAPP_ABIHM_TRXH_SET_CHAN_ATTR_ACK         (ABIHM_TRXH_BASE_MSG_NUM + 5) /*CsappAbihmTrxhSetChanAttrAck*/
#define CSAPP_ABIHM_TRXH_SET_CHAN_ATTR_NACK        (ABIHM_TRXH_BASE_MSG_NUM + 6) /*CsappAbihmTrxhSetChanAttrNack*/
#define CSAPP_ABIHM_TRXH_STATE_CHANGE_EVENT_REPORT (ABIHM_TRXH_BASE_MSG_NUM + 7) /*CsappAbihmTrxhStateChangeEventReport*/
#define CSAPP_ABIHM_TRXH_FAILURE_EVENT_REPORT      (ABIHM_TRXH_BASE_MSG_NUM + 8) /*CsappAbihmTrxhFailureEventReport*/
#define OAMS_TRXH_ABIHM_OP_START_REQ               (ABIHM_TRXH_BASE_MSG_NUM + 9) /*OamsTrxhAbihmOpStartReq*/
#define CSAPP_ABIHM_TRXH_OP_START_ACK              (ABIHM_TRXH_BASE_MSG_NUM + 10) /*CsappAbihmTrxhOpStartAck*/
#define CSAPP_ABIHM_TRXH_OP_START_NACK             (ABIHM_TRXH_BASE_MSG_NUM + 11) /*CsappAbihmTrxhOpStartNack*/
#define OAMS_TRXH_ABIHM_OP_STOP_REQ                (ABIHM_TRXH_BASE_MSG_NUM + 12) /*OamsTrxhAbihmOpStopReq*/
#define CSAPP_ABIHM_TRXH_OP_STOP_ACK               (ABIHM_TRXH_BASE_MSG_NUM + 13) /*CsappAbihmTrxhOpStopAck*/
#define CSAPP_ABIHM_TRXH_OP_STOP_NACK              (ABIHM_TRXH_BASE_MSG_NUM + 14) /*CsappAbihmTrxhOpStopNack*/
#define OAMS_TRXH_ABIHM_DATA_REQ                   (ABIHM_TRXH_BASE_MSG_NUM + 16)
/* R2.2 Changes :Starts */
#define OAMS_TRXH_ABIHM_TM_RESTART                 (ABIHM_TRXH_BASE_MSG_NUM + 22) /*OamsTrxhAbihmTmRestart*/
#define CSAPP_ABIHM_TRXH_TM_RESTART_ACK            (ABIHM_TRXH_BASE_MSG_NUM + 23) /*CsappAbihmTrxhTmRestartAck*/
/*Mantis #: 0007309(If RSL Link is lost with a TRX then OML link should also be released).*/
#define OAMS_TRXH_ABIHM_BIC_PWR_ORDER_REQ          (ABIHM_TRXH_BASE_MSG_NUM + 25) /*OamsTrxhAbihmBicPwrOrderReq*/
/* R2.2 Changes :Ends */

/*Changes PCU R2.5 -- START*/
#define OAMS_TRXH_ABIHM_SET_TRX_PS_ATTR        (ABIHM_TRXH_BASE_MSG_NUM + 26) /*OamsTrxhAbihmSetPsAttrReq*/
#define CSAPP_ABIHM_TRXH_SET_TRX_PS_ATTR_ACK   (ABIHM_TRXH_BASE_MSG_NUM + 27) /*CsappAbihmTrxhSetPsAttrAck*/
#define CSAPP_ABIHM_TRXH_SET_TRX_PS_ATTR_NACK  (ABIHM_TRXH_BASE_MSG_NUM + 28) /*CsappAbihmTrxhSetPsAttrNack*/
/*Changes PCU R2.5 -- END*/
/* R2.5.5 (ABIS HA No ABIS Down) : Start
   Dated: 18-Aug-2010
*/
#define OAMS_TRXH_ABIHM_LINK_STATUS_REQ        (ABIHM_TRXH_BASE_MSG_NUM + 29) /*OamsTrxhAbihmLinkStatusReq*/
#define CSAPP_ABIHM_TRXH_LINK_STATUS_RESP      (ABIHM_TRXH_BASE_MSG_NUM + 30) /*CsappAbihmTrxhLinkStatusResp*/
#define OAMS_TRXH_ABIHM_TRX_OPR_STATUS_REQ     (ABIHM_TRXH_BASE_MSG_NUM + 31) /*OamsTrxhAbihmTrxOprStatusReq*/
#define CSAPP_ABIHM_TRXH_TRX_OPR_STATUS_RESP   (ABIHM_TRXH_BASE_MSG_NUM + 32) /*CsappAbihmTrxhTrxOprStatusResp*/
#define OAMS_TRXH_ABIHM_TM_CAP_INQ             (ABIHM_TRXH_BASE_MSG_NUM + 33) /*OamsTrxhAbihmTmCapInq*/
#define CSAPP_ABIHM_TRXH_TM_CAP_REPORT         (ABIHM_TRXH_BASE_MSG_NUM + 34) /*OamsTrxhAbihmTmCapReport*/
#define OAMS_TRXH_ABIHM_ASSOC_DISC_REQ				 (ABIHM_TRXH_BASE_MSG_NUM + 35) /*OamsTrxhAbihmAssocDiscReq*/
/* R2.5.5 (ABIS HA No ABIS Down) : End 
   Dated: 18-Aug-2010
*/
/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (ABIHM_TRXH_BASE_MSG_NUM + 29) to (ABIHM_TRXH_BASE_MSG_NUM + 60).
 */
#define ABIHM_TRXH_LAST_MSG_NUM                (ABIHM_TRXH_BASE_MSG_NUM + 60)
/*** Opcodes at Interface between ABIHM and TRXH end ***/


/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (ABIHM_LAPD_BASE_MSG_NUM + 1) to (ABIHM_LAPD_BASE_MSG_NUM + 12).
 */

/**** 
 **** There will be single opcode for communication with BSSAP. 
 **** The further messages are part of payload. 
 ****/
#define AIFDHM_BSSAP_BASE_MSG_NUM              (ABIHM_TRXH_LAST_MSG_NUM + 0) /* NOT USED*/
/*#define CSAPP_AIFDHM_BSSAP_MSG    EXT_BSSAP_MSG*/
/*#define CSSTK_BSSAP_AIFDHM_MSG    EXT_BSSAP_MSG*/ 

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (AIFDHM_BSSAP_BASE_MSG_NUM + 3) to (AIFDHM_BSSAP_BASE_MSG_NUM + 12).
 */
#define AIFDHM_BSSAP_LAST_MSG_NUM              (AIFDHM_BSSAP_BASE_MSG_NUM + 12) /* NOT USED*/

/* OAM */
/** CFG i/f **/

/*** Opcodes at Interface between CFG and CELLH ***/
#define CFG_CELLH_BASE_MSG_NUM                 (AIFDHM_BSSAP_LAST_MSG_NUM + 0)

#define OAMS_CFG_CELLH_UNLOCK_REQ              (CFG_CELLH_BASE_MSG_NUM + 1) /*OamsCfgCellhUnlockReq*/
#define OAMS_CELLH_CFG_UNLOCK_RESP             (CFG_CELLH_BASE_MSG_NUM + 2) /*OamsCellhCfgUnlockResp*/
#define OAMS_CFG_CELLH_LOCK_REQ                (CFG_CELLH_BASE_MSG_NUM + 3) /*OamsCfgCellhLockReq*/
#define OAMS_CELLH_CFG_LOCK_RESP               (CFG_CELLH_BASE_MSG_NUM + 4) /*OamsCellhCfgLockResp*/
#define OAMS_CFG_CELLH_CELL_BAR_ACCESS         (CFG_CELLH_BASE_MSG_NUM + 5) /*OamsCfgCellhCellBarAccess*/
#define OAMS_CFG_CELLH_BLOCK_IND               (CFG_CELLH_BASE_MSG_NUM + 6) /*OamsCfgCellhBlockInd*/
#define OAMS_CELLH_CFG_ALARM_IND               (CFG_CELLH_BASE_MSG_NUM + 7) /*OamsCellhCfgAlarmInd*/
#define OAMS_CFG_CELLH_CSNEIGHCELLS_CHANGE     (CFG_CELLH_BASE_MSG_NUM + 8) /*OamsCfgCellhCsNeighCellsChange*/
#define OAMS_CFG_CELLH_RESERVED10              (CFG_CELLH_BASE_MSG_NUM + 13)


/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (CFG_CELLH_BASE_MSG_NUM + 14) to (CFG_CELLH_BASE_MSG_NUM + 17).
 */
#define CFG_CELLH_LAST_MSG_NUM                 (CFG_CELLH_BASE_MSG_NUM + 17)
/*** Opcodes at Interface between CFG and CELLH end ***/

/*** Opcodes at Interface between CFG and TRXH start ***/
#define CFG_TRXH_BASE_MSG_NUM                  (CFG_CELLH_LAST_MSG_NUM + 0) /*OamsCfgTrxhUnlockReq*/
#define OAMS_CFG_TRXH_UNLOCK_REQ               (CFG_TRXH_BASE_MSG_NUM + 1) /*OamsTrxhCfgUnlockResp*/
#define OAMS_TRXH_CFG_UNLOCK_RESP              (CFG_TRXH_BASE_MSG_NUM + 2) /*OamsTrxhCfgAlarmInd*/
#define OAMS_TRXH_CFG_ALARM_IND                (CFG_TRXH_BASE_MSG_NUM + 3) /*OamsTrxhCfgAlarmInd*/
#define OAMS_CFG_TRXH_LOCK_REQ                 (CFG_TRXH_BASE_MSG_NUM + 4) /*OamsCfgTrxhLockReq*/
#define OAMS_TRXH_CFG_LOCK_RESP                (CFG_TRXH_BASE_MSG_NUM + 5) /*OamsTrxhCfgLockResp*/
#define OAMS_CFG_TRXH_ADD_TRX_REQ              (CFG_TRXH_BASE_MSG_NUM + 6) /*OamsCfgTrxhAddTrxReq*/
#define OAMS_TRXH_CFG_ADD_TRX_RESP             (CFG_TRXH_BASE_MSG_NUM + 7) /*OamsTrxhCfgAddTrxResp*/
#define OAMS_CFG_TRXH_DEL_TRX_REQ              (CFG_TRXH_BASE_MSG_NUM + 8) /*OamsCfgTrxhDelTrxReq*/
#define OAMS_TRXH_CFG_DEL_TRX_RESP             (CFG_TRXH_BASE_MSG_NUM + 9) /*OamsTrxhCfgDelTrxResp*/
/* R2.2 Changes : Starts */
#define OAMS_CFG_TRXH_TRX_RESET                (CFG_TRXH_BASE_MSG_NUM + 10) /*OamsCfgTrxhTrxReset*/
#define OAMS_TRXH_CFG_TRX_RESET_ACK            (CFG_TRXH_BASE_MSG_NUM + 11) /*OamsTrxhCfgTrxResetAck*/
#define OAMS_TRXH_CFG_TRX_RESET_NACK           (CFG_TRXH_BASE_MSG_NUM + 12) /*OamsTrxhCfgTrxResetNack*/
/* R2.2 Changes : Ends */
/*Changes PCU R2.5.1 -- START*/
#define OAMS_CFG_TRXH_BLOCK_REQ                (CFG_TRXH_BASE_MSG_NUM + 13) /*OamsCfgTrxhBlockReq*/
#define OAMS_TRXH_CFG_BLOCK_RESP               (CFG_TRXH_BASE_MSG_NUM + 14) /*OamsCfgTrxhBlockReq*/
/*Changes PCU R2.5.1 -- END*/

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * (CFG_TRXH_BASE_MSG_NUM + 15).
 */
#define CFG_TRXH_LAST_MSG_NUM                  (CFG_TRXH_BASE_MSG_NUM + 16)
/*** Opcodes at Interface between CFG and TRXH end ***/


/*** Opcodes at Interface between TRXH and CELLH start ***/
#define CELLH_TRXH_BASE_MSG_NUM                        (CFG_TRXH_LAST_MSG_NUM + 0)

#define OAMS_TRXH_CELLH_BCCH_AVAIL                     (CELLH_TRXH_BASE_MSG_NUM + 1) /*OamsTrxhCellhBcchAvail*/
#define OAMS_TRXH_CELLH_BCCH_UNAVAIL                   (CELLH_TRXH_BASE_MSG_NUM + 2) /*OamsTrxhCellhBcchUnAvail*/
#define OAMS_TRXH_CELLH_SEND_SACCH_INFO                (CELLH_TRXH_BASE_MSG_NUM + 3) /*OamsTrxhCellhSendSacchInfo*/
#define OAMS_CELLH_TRXH_UPDATE_PS_CELL_ATTR            (CELLH_TRXH_BASE_MSG_NUM + 4) /*OamsCellhTrxhUpdatePsCellAttr*/
#define OAMS_TRXH_CELLH_INITIATE_MAP                   (CELLH_TRXH_BASE_MSG_NUM + 5) /*OamsTrxhMapentInitiateMap*/
#define OAMS_CELLH_TRXH_CRE_LTRX_PTRX_MAPPING_REQ      (CELLH_TRXH_BASE_MSG_NUM + 6) /*OamsMapentTrxhCreLtrxPtrxMappingReq*/
#define OAMS_TRXH_CELLH_CRE_LTRX_PTRX_MAPPING_RESP     (CELLH_TRXH_BASE_MSG_NUM + 7) /*OamsTrxhMapentCreLtrxPtrxMappingResp*/
#define OAMS_TRXH_CELLH_CRE_LTRX_PTRX_MAPPING_FAILED   (CELLH_TRXH_BASE_MSG_NUM + 8) /*OamsTrxhMapentCreLtrxPtrxMappingFailed*/
#define OAMS_CELLH_TRXH_DEL_LTRX_PTRX_MAPPING_REQ      (CELLH_TRXH_BASE_MSG_NUM + 9) /*OamsMapentTrxhDelLtrxPtrxMappingReq*/
#define OAMS_TRXH_CELLH_DEL_LTRX_PTRX_MAPPING_RESP     (CELLH_TRXH_BASE_MSG_NUM + 10) /*OamsTrxhMapentDelLtrxPtrxMappingResp*/
#define OAMS_TRXH_CELLH_OPR_STATE_IND                  (CELLH_TRXH_BASE_MSG_NUM + 11) 
#define OAMS_CELLH_TRXH_SEND_TRX_INFO                  (CELLH_TRXH_BASE_MSG_NUM + 12) 

#define CELLH_TRXH_LAST_MSG_NUM                        (CELLH_TRXH_BASE_MSG_NUM + 13)
/*** Opcodes at Interface between TRXH and CELLH end ***/


/*** Opcodes at Interface between CELLH and ABIHM start ***/
#define CELLH_ABIHM_BASE_MSG_NUM               (CELLH_TRXH_LAST_MSG_NUM + 0)

#define OAMS_CELLH_ABIHM_BCCH_INFO             (CELLH_ABIHM_BASE_MSG_NUM + 1) /*OamsCellhAbihmBcchInfo*/
#define OAMS_CELLH_ABIHM_SACCH_FILL            (CELLH_ABIHM_BASE_MSG_NUM + 2) /*OamsCellhAbihmSacchFill*/

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (CELLH_ABIHM_BASE_MSG_NUM + 3) to (CELLH_ABIHM_BASE_MSG_NUM + 12).
 */
#define CELLH_ABIHM_LAST_MSG_NUM               (CELLH_ABIHM_BASE_MSG_NUM + 12)
/*** Opcodes at Interface between CELLH and ABIHM end ***/

/* PCU opcodes */

/*** Opcodes at Interface between GSAL and PS applications start ***/

#define GSAL_PSMSH_BASE_MSG_NUM                (CELLH_ABIHM_LAST_MSG_NUM + 0)
/*Changes PCU R2.5 -- START*/

/**** From PSMSH to GSAL ****/
#define PSAPP_PSMSH_BSSGP_FLUSH_LL_ACK         (GSAL_PSMSH_BASE_MSG_NUM + 1) /*BssgpMsgFlushLlAck*/
#define PSAPP_PSMSH_BSSGP_LLC_DISCARD          (GSAL_PSMSH_BASE_MSG_NUM + 2) /*BssgpMsgLlcDiscarded*/
#define PSAPP_PSMSH_BSSGP_RADIO_STATUS         (GSAL_PSMSH_BASE_MSG_NUM + 3) /*BssgpMsgRadioStatus*/
#define PSAPP_PSMSH_BSSGP_MS_FLOW_CTRL         (GSAL_PSMSH_BASE_MSG_NUM + 4) /*BssgpMsgFlowControlMs*/
#define PSAPP_PSMSH_BSSGP_SUSPEND_REQ          (GSAL_PSMSH_BASE_MSG_NUM + 5) /*BssgpMsgSuspend*/
#define PSAPP_PSMSH_BSSGP_UL_UNIT_DATA         (GSAL_PSMSH_BASE_MSG_NUM + 6) /*PsappPsmshBssgpUlUnitdata*/
#define PSAPP_PSMSH_BSSGP_REMOVE_TLLI_IND      (GSAL_PSMSH_BASE_MSG_NUM + 7) /*PsappPsmshBssgpRemoveTlliInd*/
#define PSAPP_PSMSH_BSSGP_UPD_MSID             (GSAL_PSMSH_BASE_MSG_NUM + 8) /*PsappPsmshBssgpUpdMsid*/

/**** From GSAL to PS APPS ****/
#define PSSKS_BSSGP_PSMSH_RA_CAPABILITY        (GSAL_PSMSH_BASE_MSG_NUM + 9) /*BssgpMsgRaCapability*/
#define PSSKS_BSSGP_PSMSH_FLUSH_LL             (GSAL_PSMSH_BASE_MSG_NUM + 10) /*BssgpMsgFlushLl*/
#define PSSKS_BSSGP_PSMSH_MS_FLOW_CTRL_ACK     (GSAL_PSMSH_BASE_MSG_NUM + 11) /*BssgpMsgFlowControlMsAck*/
#define PSSKS_BSSGP_PSMSH_CS_PAGING_REQ        (GSAL_PSMSH_BASE_MSG_NUM + 12) /*BssgpMsgPagingCs*/
#define PSSKS_BSSGP_PSMSH_SUSPEND_ACK          (GSAL_PSMSH_BASE_MSG_NUM + 13) /*BssgpMsgSuspendAck*/
#define PSSKS_BSSGP_PSMSH_SUSPEND_NACK         (GSAL_PSMSH_BASE_MSG_NUM + 14) /*BssgpMsgSuspendNack*/
#define PSSKS_BSSGP_PSMSH_DL_UNIT_DATA         (GSAL_PSMSH_BASE_MSG_NUM + 15) /*PssksBssgpPsmshDlUnitdata*/
#define PSSKS_BSSGP_PSMSH_UPD_TLLIINDEX        (GSAL_PSMSH_BASE_MSG_NUM + 16) /*PssksBssgpPsmshUpdTlliIndex*/

#define GSAL_PSMSH_LAST_MSG_NUM                (GSAL_PSMSH_BASE_MSG_NUM + 20)

#define GSAL_GBH_BASE_MSG_NUM                  (GSAL_PSMSH_LAST_MSG_NUM + 0)
/**** From GBH to GSAL ****/
#define OAMS_GBH_BSSGP_SIG_BVC_RESET           (GSAL_GBH_BASE_MSG_NUM + 1) /*BssgpMsgBvcReset*/
#define OAMS_GBH_BSSGP_SIG_BVC_RESET_ACK       (GSAL_GBH_BASE_MSG_NUM + 2) /*BssgpMsgBvcResetAck*/

/**** From GSAL to GBH ****/
#define PSSKS_BSSGP_GBH_SIG_BVC_RESET          (GSAL_GBH_BASE_MSG_NUM + 5) /*BssgpMsgBvcReset*/
#define PSSKS_BSSGP_GBH_SIG_BVC_RESET_ACK      (GSAL_GBH_BASE_MSG_NUM + 6) /*BssgpMsgBvcResetAck*/

#define GSAL_GBH_LAST_MSG_NUM                  (GSAL_GBH_BASE_MSG_NUM + 10)


/**** From PSCH to GSAL ****/
#define GSAL_PSCH_BASE_MSG_NUM                 (GSAL_GBH_LAST_MSG_NUM + 0)
#define OAMS_PSCH_BSSGP_PTP_BVC_RESET          (GSAL_PSCH_BASE_MSG_NUM + 1) /*BssgpMsgBvcReset*/
#define OAMS_PSCH_BSSGP_PTP_BVC_BLOCK          (GSAL_PSCH_BASE_MSG_NUM + 2) /*BssgpMsgBvcBlock*/
#define OAMS_PSCH_BSSGP_PTP_BVC_UNBLOCK        (GSAL_PSCH_BASE_MSG_NUM + 3) /*BssgpMsgBvcUnblock*/
#define OAMS_PSCH_BSSGP_PTP_BVC_FLOW_CTRL_REQ  (GSAL_PSCH_BASE_MSG_NUM + 4) /*BssgpMsgFlowControlBvc*/
#define OAMS_PSCH_BSSGP_PTP_BVC_RESET_ACK      (GSAL_PSCH_BASE_MSG_NUM + 5) /*BssgpMsgBvcResetAck*/

/**** From PSCH to GSAL ****/
#define PSSKS_BSSGP_PSCH_PTP_BVC_RESET         (GSAL_PSCH_BASE_MSG_NUM + 8) /*BssgpMsgBvcReset*/
#define PSSKS_BSSGP_PSCH_PTP_BVC_BLOCK_ACK     (GSAL_PSCH_BASE_MSG_NUM + 9) /*BssgpMsgBvcBlockAck*/
#define PSSKS_BSSGP_PSCH_PTP_BVC_RESET_ACK     (GSAL_PSCH_BASE_MSG_NUM + 10) /*BssgpMsgBvcResetAck*/
#define PSSKS_BSSGP_PSCH_PTP_BVC_UNBLOCK_ACK   (GSAL_PSCH_BASE_MSG_NUM + 11) /*BssgpMsgBvcUnblockAck*/
#define PSSKS_BSSGP_PSCH_PTP_BVC_FLOW_CTRL_ACK (GSAL_PSCH_BASE_MSG_NUM + 12) /*BssgpMsgFlowControlBvcAck*/

#define GSAL_PSCH_LAST_MSG_NUM                 (GSAL_PSCH_BASE_MSG_NUM + 15)

#define GSAL_PHM_BASE_MSG_NUM                  (GSAL_PSCH_LAST_MSG_NUM + 0)
/**** From PHM to GSAL ****/
#define PSSKS_BSSGP_PHM_PS_PAGING_REQ          (GSAL_PHM_BASE_MSG_NUM + 1) /*BssgpMsgPagingPs*/
#define PSSKS_BSSGP_PHM_CS_PAGING_REQ          (GSAL_PHM_BASE_MSG_NUM + 2) /*BssgpMsgPagingCs*/

#define GSAL_PHM_LAST_MSG_NUM                  (GSAL_PHM_BASE_MSG_NUM + 5)


/*** Opcodes at Interface between GSAL and PS applications end ***/

/**********************************/
/*** Opcodes at Interface between GSAL and PSSCM ***/
#define GSAL_PSSCM_BASE_MSG_NUM                (GSAL_PHM_LAST_MSG_NUM + 0)

/**** From GSAL To PSSCM ****/

#define PSSKS_NS_PSSCM_PROV_NSEI_CNF           (GSAL_PSSCM_BASE_MSG_NUM + 1) /*PssksNsPsscmProvNseiCnf*/
#define PSSKS_NS_PSSCM_UNPROV_NSEI_CNF         (GSAL_PSSCM_BASE_MSG_NUM + 2) /*PssksNsPsscmUnprovNseiCnf*/
#define PSSKS_NS_PSSCM_PROV_SIG_BVC_CNF        (GSAL_PSSCM_BASE_MSG_NUM + 3) /*PssksNsPsscmProvSigBvcCnf*/
#define PSSKS_NS_PSSCM_UNPROV_SIG_BVC_CNF      (GSAL_PSSCM_BASE_MSG_NUM + 4) /*PssksNsPsscmUnprovSigBvcCnf*/
#define PSSKS_NS_PSSCM_PROV_LEP_CNF            (GSAL_PSSCM_BASE_MSG_NUM + 5) /*PssksNsPsscmProvLepCnf*/
#define PSSKS_NS_PSSCM_UNPROV_LEP_CNF          (GSAL_PSSCM_BASE_MSG_NUM + 6) /*PssksNsPsscmUnprovLepCnf*/
#define PSSKS_NS_PSSCM_PROV_REP_CNF            (GSAL_PSSCM_BASE_MSG_NUM + 7) /*PssksNsPsscmProvRepCnf*/
#define PSSKS_NS_PSSCM_UNPROV_REP_CNF          (GSAL_PSSCM_BASE_MSG_NUM + 8) /*PssksNsPsscmUnprovRepCnf*/
#define PSSKS_NS_PSSCM_AUTO_CONFIG_CNF         (GSAL_PSSCM_BASE_MSG_NUM + 9) /*PssksNsPsscmAutoConfigCnf*/
#define PSSKS_NS_PSSCM_TEST_ENABLE_CNF         (GSAL_PSSCM_BASE_MSG_NUM + 10) /*PssksNsPsscmTestEnableCnf*/
#define PSSKS_NS_PSSCM_ALARM_IND               (GSAL_PSSCM_BASE_MSG_NUM + 11) /*PssksNsPsscmAlarmInd*/
#define PSSKS_BSSGP_PSSCM_PROV_SIG_BVC_CNF     (GSAL_PSSCM_BASE_MSG_NUM + 12) /*PssksBssgpPsscmProvSigBvcCnf*/
#define PSSKS_BSSGP_PSSCM_UNPROV_SIG_BVC_CNF   (GSAL_PSSCM_BASE_MSG_NUM + 13) /*PssksBssgpPsscmUnprovSigBvcCnf*/
#define PSSKS_BSSGP_PSSCM_PROV_PTP_BVC_CNF     (GSAL_PSSCM_BASE_MSG_NUM + 14) /*PssksBssgpPsscmProvPtpBvcCnf*/
#define PSSKS_BSSGP_PSSCM_UNPROV_PTP_BVC_CNF   (GSAL_PSSCM_BASE_MSG_NUM + 15) /*PssksBssgpPsscmUnprovPtpBvcCnf*/
#define PSSKS_NS_PSSCM_PROV_PTP_BVC_CNF        (GSAL_PSSCM_BASE_MSG_NUM + 16) /*PssksNsPsscmProvPtpBvcCnf*/
#define PSSKS_BSSGP_PSSCM_ALARM_IND            (GSAL_PSSCM_BASE_MSG_NUM + 17) /*PssksBssgpPsscmAlarmInd*/
#define PSSKS_NS_PSSCM_UNPROV_PTP_BVC_CNF      (GSAL_PSSCM_BASE_MSG_NUM + 18) /*PssksNsPsscmUnprovPtpBvcCnf*/
/* (GSAL_PSSCM_BASE_MSG_NUM + 19) to (GSAL_PSSCM_BASE_MSG_NUM + 20) reserved for future use */

/**** From PSSCM To GSAL ****/
#define OAMS_PSSCM_NS_PROV_NSEI                (GSAL_PSSCM_BASE_MSG_NUM + 21) /*OamsPsscmNsProvNsei*/
#define OAMS_PSSCM_NS_UNPROV_NSEI              (GSAL_PSSCM_BASE_MSG_NUM + 22) /*OamsPsscmNsUnprovNsei*/
#define OAMS_PSSCM_NS_PROV_SIG_BVC             (GSAL_PSSCM_BASE_MSG_NUM + 23) /*OamsPsscmNsProvSigBvc*/
#define OAMS_PSSCM_NS_UNPROV_SIG_BVC           (GSAL_PSSCM_BASE_MSG_NUM + 24) /*OamsPsscmNsUnprovSigBvc*/
#define OAMS_PSSCM_NS_PROV_LEP                 (GSAL_PSSCM_BASE_MSG_NUM + 25) /*OamsPsscmNsProvLep*/
#define OAMS_PSSCM_NS_UNPROV_LEP               (GSAL_PSSCM_BASE_MSG_NUM + 26) /*OamsPsscmNsUnprovLep*/
#define OAMS_PSSCM_NS_PROV_REP                 (GSAL_PSSCM_BASE_MSG_NUM + 27) /*OamsPsscmNsProvRep*/
#define OAMS_PSSCM_NS_UNPROV_REP               (GSAL_PSSCM_BASE_MSG_NUM + 28) /*OamsPsscmNsUnprovRep*/
#define OAMS_PSSCM_NS_AUTO_CONFIG              (GSAL_PSSCM_BASE_MSG_NUM + 29) /*OamsPsscmNsAutoConfig*/
#define OAMS_PSSCM_NS_TEST_ENABLE              (GSAL_PSSCM_BASE_MSG_NUM + 30) /*OamsPsscmNsTestEnable*/
#define OAMS_PSSCM_BSSGP_PROV_SIG_BVC          (GSAL_PSSCM_BASE_MSG_NUM + 31) /*OamsPsscmBssgpProvSigBvc*/
#define OAMS_PSSCM_BSSGP_UNPROV_SIG_BVC        (GSAL_PSSCM_BASE_MSG_NUM + 32) /*OamsPsscmBssgpUnprovSigBvc*/
#define OAMS_PSSCM_BSSGP_PROV_PTP_BVC          (GSAL_PSSCM_BASE_MSG_NUM + 33) /*OamsPsscmBssgpProvPtpBvc*/
#define OAMS_PSSCM_BSSGP_UNPROV_PTP_BVC        (GSAL_PSSCM_BASE_MSG_NUM + 34) /*OamsPsscmBssgpUnprovPtpBvc*/
#define OAMS_PSSCM_NS_PROV_PTP_BVC             (GSAL_PSSCM_BASE_MSG_NUM + 35) /*OamsPsscmNsProvPtpBvc*/
#define OAMS_PSSCM_NS_UNPROV_PTP_BVC           (GSAL_PSSCM_BASE_MSG_NUM + 36) /*OamsPsscmNsUnprovPtpBvc*/

/* (GSAL_PSSCM_BASE_MSG_NUM + 37) to (GSAL_PSSCM_BASE_MSG_NUM + 40) reserved for future use */

#define GSAL_PSSCM_LAST_MSG_NUM                (GSAL_PSSCM_BASE_MSG_NUM + 40)

#define GSAL_NSVCH_BASE_MSG_NUM                (GSAL_PSSCM_LAST_MSG_NUM + 0)
/* From NSVCH to GSAL */
#define OAMS_NSVCH_NS_PROV_FR_LINK             (GSAL_NSVCH_BASE_MSG_NUM + 1) /*OamsNsvchNsProvFrLink*/ 
#define OAMS_NSVCH_NS_UNPROV_FR_LINK           (GSAL_NSVCH_BASE_MSG_NUM + 2) /*OamsNsvchNsUnprovFrLink*/
#define OAMS_NSVCH_NS_PROV_NSVC                (GSAL_NSVCH_BASE_MSG_NUM + 3) /*OamsNsvchNsProvNsvc*/
#define OAMS_NSVCH_NS_UNPROV_NSVC              (GSAL_NSVCH_BASE_MSG_NUM + 4) /*OamsNsvchNsUnprovNsvc*/
#define OAMS_NSVCH_NS_REM_NSVC_NSEI_GRP        (GSAL_NSVCH_BASE_MSG_NUM + 5) /*OamsNsvchNsRemNsvcNseiGrp*/
#define OAMS_NSVCH_NS_NSVC_RESET               (GSAL_NSVCH_BASE_MSG_NUM + 6) /*OamsNsvchNsNsvcReset*/
#define OAMS_NSVCH_NS_NSVC_BLOCK               (GSAL_NSVCH_BASE_MSG_NUM + 7) /*OamsNsvchNsNsvcBlock*/
#define OAMS_NSVCH_NS_NSVC_UNBLOCK             (GSAL_NSVCH_BASE_MSG_NUM + 8) /*OamsNsvchNsNsvcUnblock*/
#define OAMS_NSVCH_NS_NSVC_DOWN                (GSAL_NSVCH_BASE_MSG_NUM + 9) /*OamsNsvchNsNsvcDown*/
#define OAMS_NSVCH_NS_N_CONN_IND               (GSAL_NSVCH_BASE_MSG_NUM + 10) /*OamsNsvchNsNConnInd*/
#define OAMS_NSVCH_NS_N_DISC_IND               (GSAL_NSVCH_BASE_MSG_NUM + 11) /*OamsNsvchNsNDiscInd*/
#define OAMS_NSVCH_NS_ADD_NSVC_TO_NSEI_GRP     (GSAL_NSVCH_BASE_MSG_NUM + 12) /*OamsNsvchNsAddNsvcToNseiGrp*/

/* (GSAL_NSVCH_BASE_MSG_NUM + 13) to (GSAL_NSVCH_BASE_MSG_NUM + 14) reserved for future use */

/* From GSAL to NSVCH */
#define PSSKS_NS_NSVCH_PROV_FR_LINK_CNF            (GSAL_NSVCH_BASE_MSG_NUM + 15) /*PssksNsNsvchProvFrLinkCnf*/
#define PSSKS_NS_NSVCH_UNPROV_FR_LINK_CNF          (GSAL_NSVCH_BASE_MSG_NUM + 16) /*PssksNsNsvchUnprovFrLinkCnf*/
#define PSSKS_NS_NSVCH_PROV_NSVC_CNF               (GSAL_NSVCH_BASE_MSG_NUM + 17) /*PssksNsNsvchProvNsvcCnf*/
#define PSSKS_NS_NSVCH_UNPROV_NSVC_CNF             (GSAL_NSVCH_BASE_MSG_NUM + 18) /*PssksNsNsvchUnprovNsvcCnf*/
#define PSSKS_NS_NSVCH_ADD_NSVC_TO_NSEI_GRP_CNF    (GSAL_NSVCH_BASE_MSG_NUM + 19) /*PssksNsNsvchAddNsvcToNseiGrpCnf*/
#define PSSKS_NS_NSVCH_REM_NSVC_NSEI_GRP_CNF       (GSAL_NSVCH_BASE_MSG_NUM + 20) /*PssksNsNsvchRemNsvcToNseiGrpCnf*/
#define PSSKS_NS_NSVCH_NSVC_BLOCK_IND              (GSAL_NSVCH_BASE_MSG_NUM + 21) /*PssksNsNsvchNsvcBlockInd*/
#define PSSKS_NS_NSVCH_NSVC_DOWN_CNF               (GSAL_NSVCH_BASE_MSG_NUM + 22) /*PssksNsNsvchNsvcDownCnf*/
#define PSSKS_NS_NSVCH_NSVC_UNBLOCK_IND            (GSAL_NSVCH_BASE_MSG_NUM + 23) /*PssksNsNsvchNsvcUnblockInd*/
#define PSSKS_NS_NSVCH_NSVC_BLOCK_CNF              (GSAL_NSVCH_BASE_MSG_NUM + 24) /*PssksNsNsvchNsvcBlockCnf*/
#define PSSKS_NS_NSVCH_NSVC_UNBLOCK_CNF            (GSAL_NSVCH_BASE_MSG_NUM + 25) /*PssksNsNsvchNsvcUnblockCnf*/
#define PSSKS_NS_NSVCH_NSVC_RESET_CNF              (GSAL_NSVCH_BASE_MSG_NUM + 26) /*PssksNsNsvchNsvcResetCnf*/
#define PSSKS_NS_NSVCH_NSVC_RESET_IND              (GSAL_NSVCH_BASE_MSG_NUM + 27) /*PssksNsNsvchNsvcResetInd*/
#define PSSKS_NS_NSVCH_ALARM_IND                   (GSAL_NSVCH_BASE_MSG_NUM + 28) /*PssksNsNsvchAlarmInd*/
/* (GSAL_NSVCH_BASE_MSG_NUM + 29) to (GSAL_NSVCH_BASE_MSG_NUM + 35) reserved for future use */

#define GSAL_NSVCH_LAST_MSG_NUM                    (GSAL_NSVCH_BASE_MSG_NUM + 35)

#define GSAL_PDC_BASE_MSG_NUM                      (GSAL_NSVCH_LAST_MSG_NUM + 0)

/* From PDC to GSAL */
#define OAM_PDC_NS_GET_STATS_REQ                   (GSAL_PDC_BASE_MSG_NUM + 1) /*OamPdcNsGetStatsReq*/
#define OAM_PDC_BSSGP_GET_STATS_REQ                (GSAL_PDC_BASE_MSG_NUM + 2) /*OamPdcBssgpGetStatsReq*/
#define OAM_PDC_BSSGP_GET_BVCI_STATS_REQ           (GSAL_PDC_BASE_MSG_NUM + 3) /*OamPdcBssgpGetBvciStatsReq*/

/* From GSAL to PDC  */
#define PSSKS_NS_PDC_GET_STATS_CNF_FAIL            (GSAL_PDC_BASE_MSG_NUM + 6) /*PssksNsPdcGetStatsFail*/
#define PSSKS_NS_PDC_GET_STATS_CNF                 (GSAL_PDC_BASE_MSG_NUM + 7) /*PssksNsPdcGetStatsCnfFr*/
#define PSSKS_BSSGP_PDC_GET_STATS_CNF              (GSAL_PDC_BASE_MSG_NUM + 8) /*PssksBssgpPdcGetStatsCnf*/
#define PSSKS_BSSGP_PDC_GET_STATS_CNF_FAIL         (GSAL_PDC_BASE_MSG_NUM + 9) /*PssksBssgpPdcGetStatsFail*/
#define PSSKS_BSSGP_PDC_GET_BVCI_STATS_CNF         (GSAL_PDC_BASE_MSG_NUM + 10) /*PssksBssgpPdcGetBvciGetStatsCnf*/
#define PSSKS_BSSGP_PDC_GET_BVCI_STATS_CNF_FAIL    (GSAL_PDC_BASE_MSG_NUM + 11) /*PssksBssgpPdcGetBvciStatsFail*/

#define GSAL_PDC_LAST_MSG_NUM                      (GSAL_PDC_BASE_MSG_NUM + 15)

/*Currently these messages are not used*/
#define GSAL_PSSCM_NOT_USED_BASE_MSG_NUM           (GSAL_PDC_LAST_MSG_NUM + 0)
#define GSAL_PSSCM_BSSGP_REDUN_STATUS_CNF          (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 1) 
#define GSAL_PSSCM_BSSGP_REDUN_START_CNF           (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 2)
#define GSAL_PSSCM_BSSGP_REDUN_STOP_CNF            (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 3)
#define GSAL_PSSCM_BSSGP_ADD_TLLI_CNF              (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 4)
#define GSAL_PSSCM_BSSGP_REMOVE_TLLI_CNF           (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 5)
#define GSAL_PSSCM_BSSGP_RESET_STATS_CNF           (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 6)
#define GSAL_PSSCM_BSSGP_GET_TRACE_LEVEL_CNF       (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 7)
#define GSAL_PSSCM_BSSGP_SET_TRACE_LEVEL_CNF       (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 8)
#define GSAL_PSSCM_BSSGP_SET_TIMER_CNF             (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 9)
#define GSAL_PSSCM_BSSGP_GET_TIMER_CNF             (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 10)
#define GSAL_PSSCM_NS_REDUN_STATUS_CNF             (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 11)
#define GSAL_PSSCM_NS_REDUN_START_CNF              (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 12)
#define GSAL_PSSCM_NS_REDUN_STOP_CNF               (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 13)
#define GSAL_PSSCM_OAM_NS_TEST_DISABLE_CNF         (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 14)
#define GSAL_PSSCM_NS_OAM_ADD_CNF                  (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 15)
#define GSAL_PSSCM_NS_OAM_CHG_WEIGHT_CNF           (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 16)
#define GSAL_PSSCM_NS_OAM_DELETE_CNF               (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 17)
#define GSAL_PSSCM_OAM_NS_PROV_NSEI_GROUP_CNF      (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 18)
#define GSAL_PSSCM_OAM_NS_UNPROV_NSEI_GROUP_CNF    (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 19)
#define GSAL_PSSCM_NS_RESET_STATS_CNF              (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 20)
#define GSAL_PSSCM_NS_GET_TRACE_LEVEL_CNF          (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 21)
#define GSAL_PSSCM_NS_SET_TRACE_LEVEL_CNF          (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 22)
#define GSAL_PSSCM_NS_GET_TIMER_CNF                (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 23)
#define GSAL_PSSCM_NS_SET_TIMER_CNF                (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 24)
#define GSAL_PSSCM_OAM_NS_SET_RETRIES_CNF          (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 25)
#define GSAL_PSSCM_OAM_NS_GET_RETRIES_CNF          (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 26) 
#define GSAL_PSSCM_SEND_TO_SCM                     (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 27)

#define GSAL_PSSCM_NOT_USED_LAST_MSG_NUM           (GSAL_PSSCM_NOT_USED_BASE_MSG_NUM + 30)
/** FR i/f **/
/*** Opcodes at Interface between NS and FR ***/
#define NS_FR_BASE_MSG_NUM                         (GSAL_PSSCM_NOT_USED_LAST_MSG_NUM  + 0)

/**** From FR To NS ****/

#define PSSKS_FR_NS_N_DATA_IN                      (NS_FR_BASE_MSG_NUM + 1)


#define PSSKS_NS_FR_N_DATA_REQ                     (NS_FR_BASE_MSG_NUM + 2)

#define NS_FR_LAST_MSG_NUM                         (NS_FR_BASE_MSG_NUM + 5)

/*Changes PCU R2.5 Aricent -- END*/

/*** Opcodes at Interface between FR and PSSCM start ***/
#define FR_PSSCM_BASE_MSG_NUM                      (NS_FR_LAST_MSG_NUM + 0)
/**********************************/

#define FR_PSSCM_N_CONN_IND                        (FR_PSSCM_BASE_MSG_NUM + 1)
#define FR_PSSCM_N_DISC_IND                        (FR_PSSCM_BASE_MSG_NUM + 2)
#define FR_PSSCM_N_STAT_REQ                        (FR_PSSCM_BASE_MSG_NUM + 3)
#define FR_PSSCM_N_START_REQ                       (FR_PSSCM_BASE_MSG_NUM + 4)
#define FR_PSSCM_N_STATUS_IND                      (FR_PSSCM_BASE_MSG_NUM + 5)
#define FR_PSSCM_N_STOP_REQ                        (FR_PSSCM_BASE_MSG_NUM + 6)

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (FR_PSSCM_BASE_MSG_NUM + 7) to (FR_PSSCM_BASE_MSG_NUM + 16).
 */
#define FR_PSSCM_LAST_MSG_NUM                      (FR_PSSCM_BASE_MSG_NUM + 10)
/*** Opcodes at Interface between FR and PSSCM end ***/


/*** Opcodes at Interface between PSSCM and CFG start ***/
#define PSSCM_CFG_BASE_MSG_NUM                     (FR_PSSCM_LAST_MSG_NUM + 0)

/* CS_PS_MERGING : 07-Mar-2012 START */
#define OAMS_CFG_PSSCM_NSE_LOCK_REQ                    (PSSCM_CFG_BASE_MSG_NUM + 1) /*OamsCfgPsscmLockReq*/
#define OAMS_PSSCM_CFG_NSE_LOCK_RESP                   (PSSCM_CFG_BASE_MSG_NUM + 2) /*OamsPsscmCfgLockResp*/
#define OAMS_CFG_PSSCM_NSE_UNLOCK_REQ                  (PSSCM_CFG_BASE_MSG_NUM + 3) /*OamsCfgPsscmUnlockReq*/
#define OAMS_PSSCM_CFG_NSE_UNLOCK_RESP                 (PSSCM_CFG_BASE_MSG_NUM + 4) /*OamsPsscmCfgUnlockResp*/
/* CS_PS_MERGING : 07-Mar-2012 END */

#define OAMS_PSSCM_CFG_ALARM_IND                   (PSSCM_CFG_BASE_MSG_NUM + 5) 

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (PSSCM_CFG_BASE_MSG_NUM + 6) to (PSSCM_CFG_BASE_MSG_NUM + 10).
 */
#define PSSCM_CFG_LAST_MSG_NUM                     (PSSCM_CFG_BASE_MSG_NUM + 10)
/*** Opcodes at Interface between PSSCM and CFG end ***/

/*** Opcodes at Interface between FR and CFG start ***/
#define FR_CFG_BASE_MSG_NUM                        (PSSCM_CFG_LAST_MSG_NUM + 0)
#define PSSKS_FR_CFG_ALARM_IND                     (FR_CFG_BASE_MSG_NUM + 1) /*SysAlarm*/
#define FR_CFG_LAST_MSG_NUM                        (FR_CFG_BASE_MSG_NUM + 5)


#define OAM_BASE_MSG_NUM                           (FR_CFG_LAST_MSG_NUM + 0)



/****************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES BETWEEN CM AND OMC
* *************************************************************************/
/*  Commented in CS3.0 as per CS2.2  - commented messages removed 14-10-2008*/


/***************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES BETWEEN CM AND PDC
 * ************************************************************************/
#define OAM_CM_PDC_ERROR                       (OAM_BASE_MSG_NUM + 41) 
#define OAM_CM_PDC_INST_CER_REQ                (OAM_BASE_MSG_NUM + 42)
#define OAM_CM_PDC_INST_PERF_REQ               (OAM_BASE_MSG_NUM + 43)
#define OAM_PDC_CM_INST_CER_RESP               (OAM_BASE_MSG_NUM + 44)
#define OAM_PDC_CM_INST_PERF_RESP              (OAM_BASE_MSG_NUM + 45) 
#define OAM_PDC_CM_PERIODIC_TRACE_RESP         (OAM_BASE_MSG_NUM + 46)
#define OAM_PDC_CM_PERIODIC_ALARM_RESP         (OAM_BASE_MSG_NUM + 47)  
#define OAM_PDC_CM_PERIODIC_DIAG_RESP          (OAM_BASE_MSG_NUM + 48)
#define OAM_PDC_CM_PERIODIC_PERF_RESP          (OAM_BASE_MSG_NUM + 49)
#define OAM_PDC_CM_PERIODIC_CER_RESP           (OAM_BASE_MSG_NUM + 50)
#define OAM_CM_PDC_ERROR_RESP                  (OAM_BASE_MSG_NUM + 51)
#define OAM_CM_PDC_INST_TRACE_REQ              (OAM_BASE_MSG_NUM + 52)
#define OAM_CM_PDC_INST_ALARM_REQ              (OAM_BASE_MSG_NUM + 53)
#define OAM_PDC_AFH_FILEOP_REQ                 (OAM_BASE_MSG_NUM + 54)
#define OAM_AFH_PDC_FILEOP_RESP                (OAM_BASE_MSG_NUM + 55)
#define OAM_CM_PDC_INST_DATA_REQ               (OAM_BASE_MSG_NUM + 56)
#define OAM_PDC_CM_INST_DATA_RESP              (OAM_BASE_MSG_NUM + 57)

/************************************************************************
OPCODES ASSOCIATED FOR MESSAGES BETWEEN CM AND PDD
**************************************************************************/
/*Added for R3-BSC  25th Jan.2012 ** Start ***/
#define OAM_CM_PDD_FILE_RESEND_REQ             (OAM_BASE_MSG_NUM + 60)
/*Added for R3-BSC  25th Jan.2012 ** Ends  ***/

#define OAM_CM_PDD_ERROR                       (OAM_BASE_MSG_NUM + 61)
#define OAM_CM_PDD_FTP_INFO_REQ                (OAM_BASE_MSG_NUM + 62)
#define OAM_PDD_CM_FTP_INFO_RESP               (OAM_BASE_MSG_NUM + 63) 
#define OAM_PDD_CM_DIAG_RESP                   (OAM_BASE_MSG_NUM + 64)
#define OAM_PDD_CM_TRACE_REQ                   (OAM_BASE_MSG_NUM + 65)
#define OAM_PDD_CM_TRACE_RESP                  (OAM_BASE_MSG_NUM + 66) 
#define OAM_PDD_CM_ALARM_REQ                   (OAM_BASE_MSG_NUM + 67)
#define OAM_PDD_CM_ALARM_RESP                  (OAM_BASE_MSG_NUM + 68) 
#define OAM_CM_PDD_ERROR_RESP                  (OAM_BASE_MSG_NUM + 69) 
#define OAM_CM_PDD_SPEC_REQ                    (OAM_BASE_MSG_NUM + 70)  
#define OAM_PDD_CM_SPEC_RESP                   (OAM_BASE_MSG_NUM + 71)   
#define OAM_PDD_CM_SVR_DWN_REQ                 (OAM_BASE_MSG_NUM + 72) 
/* Added by Aricent on 19-Oct07 */
#define OAM_CM_PDD_DIAG_REQ                    (OAM_BASE_MSG_NUM + 73)
/* Added by Aricent on 19-Oct07 */
#define OAM_PDD_CM_PERIODIC_PERF_RESP          (OAM_BASE_MSG_NUM + 74)
#define OAM_CM_PDD_FILE_INTGRTY_MSG            (OAM_BASE_MSG_NUM + 75)
#define OAM_CM_PDD_FTP_START                   (OAM_BASE_MSG_NUM + 76)
#define OAM_CM_PDD_RESET_MSG                   (OAM_BASE_MSG_NUM + 77)
#define OAM_PDD_CM_CER_RESP                    (OAM_BASE_MSG_NUM + 78)
/*  Commented as per in CS2.2  */

/*Added for R3-BSC  25th Jan.2012 ** Start ***/
#define OAM_PDD_CM_FILE_RESEND_RESP            (OAM_BASE_MSG_NUM + 79)
/*Added for R3-BSC  25th Jan.2012 ** Ends  ***/



/*************************************************************************
OPCODES ASSOCIATED FOR MESSAGES BETWEEN CM AND SNMP  
**************************************************************************/
#define OAM_CM_SNMP_CONFIG_REQ                 (OAM_BASE_MSG_NUM + 80)   
#define OAM_SNMP_CM_CONFIG_RESP                (OAM_BASE_MSG_NUM + 81)
#define OAM_CM_SNMP_RESET_MSG                  (OAM_BASE_MSG_NUM + 82)
#define OAM_SNMP_CM_INST_DATA_REQ              (OAM_BASE_MSG_NUM + 83)
#define OAM_CM_SNMP_INST_DATA_RESP             (OAM_BASE_MSG_NUM + 84)

/* Added by Aricent on 19-Oct07 */
/*  Commented as per in CS2.2   */


/*************************************************************************
OPCODES ASSOCIATED FOR MESSAGES BETWEEN PDC AND PDD  
**************************************************************************/
#define OAM_PDC_PDD_INST_PERF_REQ              (OAM_BASE_MSG_NUM + 85)
#define OAM_PDC_PDD_INST_CER_REQ               (OAM_BASE_MSG_NUM + 86) 
#define OAM_PDD_PDC_INST_CER_RESP              (OAM_BASE_MSG_NUM + 87)    
#define OAM_PDD_PDC_INST_PERF_RESP             (OAM_BASE_MSG_NUM + 88)  
#define OAM_PDC_PDD_CER_TIMER_EXPIRY           (OAM_BASE_MSG_NUM + 89) 
#define OAM_PDC_PDD_INST_TRACE_REQ             (OAM_BASE_MSG_NUM + 90)  
#define OAM_PDC_PDD_INST_DIAG_REQ              (OAM_BASE_MSG_NUM + 91)
#define OAM_PDC_PDD_INST_ALARM_REQ             (OAM_BASE_MSG_NUM + 92) 
#define OAM_PDD_PDC_INST_TRACE_RESP            (OAM_BASE_MSG_NUM + 93) 
#define OAM_PDD_PDC_INST_DIAG_RESP             (OAM_BASE_MSG_NUM + 94)
#define OAM_PDD_PDC_INST_ALARM_RESP            (OAM_BASE_MSG_NUM + 95) 
#define OAM_PDD_PDC_ERROR                      (OAM_BASE_MSG_NUM + 96)

/**************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES FROM PDC AND MGS 
 * ************************************************************************/
#define OAM_PDC_MGS_PERF_DATA_REQ              (OAM_BASE_MSG_NUM + 97) /*OamPdcMgsPerfReq*/
#define OAM_MGS_PDC_PERF_DATA_RESP             (OAM_BASE_MSG_NUM + 98) /*OamMgsPdcPerfResp*/
#define OAM_RESERVED21                         (OAM_BASE_MSG_NUM + 99)

/**************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES FROM PDC AND OIL(For SCM messages)
 * ************************************************************************/
#define OAM_PDC_SCM_PERF_DATA_REQ              (OAM_BASE_MSG_NUM + 102)
#define OAM_SCM_PDC_PERF_DATA_RESP             (OAM_BASE_MSG_NUM + 103) 

/**************************************************************************/
/**************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES FROM PDC AND OIL(For PSSCM messages)
 * ************************************************************************/
#define OAM_PDC_PSSCM_PERF_DATA_REQ            (OAM_BASE_MSG_NUM + 104) /*OamPdcPsscmPerfReq*/
#define OAM_PSSCM_PDC_PERF_DATA_RESP           (OAM_BASE_MSG_NUM + 105) /*OamPsscmPdcPerfResp*/

/****************************************************************************/
/**************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES FROM PDC AND OIL(For Platform messages)
 * ************************************************************************/
#define OAM_PDC_PM_PERF_DATA_REQ               (OAM_BASE_MSG_NUM + 106)
#define OAM_PM_PDC_PERF_DATA_RESP              (OAM_BASE_MSG_NUM + 107) 

/**************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES FROM AFH TO SNMP
 * ************************************************************************/
#define OAM_AFH_SNMP_TRAP_MSG                  (OAM_BASE_MSG_NUM + 108) 

/* CS3.0 changes */
/**************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES BETWEEN MRHM AND PDC
 * ************************************************************************/
#define OAM_PDC_MRHM_PERF_DATA_REQ             (OAM_BASE_MSG_NUM + 109) /*OamPdcMrhmPerfReq*/
#define CSAPP_MRHM_PDC_PERF_DATA_RESP          (OAM_BASE_MSG_NUM + 110) /*CsappMrhmPdcPerfResp*/
/* CS3.0 changes end*/

/***************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES BETWEEN PDC AND SNMP
 * *************************************************************************/
#define OAM_SNMP_PDC_INST_DATA_REQ             (OAM_BASE_MSG_NUM + 111)
#define OAM_PDC_SNMP_INST_DATA_RESP            (OAM_BASE_MSG_NUM + 112)

 /***************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES BETWEEN CM, PDC AND SNMP
 * *************************************************************************/
#define OAM_SNMP_CM_DATA_REQ                   (OAM_BASE_MSG_NUM + 113)
#define OAM_CM_SNMP_DATA_RESP                  (OAM_BASE_MSG_NUM + 114) 
#define OAM_CM_PDC_DATA_REQ                    (OAM_BASE_MSG_NUM + 115)
#define OAM_PDC_CM_DATA_RESP                   (OAM_BASE_MSG_NUM + 116) 
/*SNMP CRASH PATCH : Nitin: 18-Feb-2010 */
#define OAM_SNMP_CM_GET_CONFIG_INFO_REQ        (OAM_BASE_MSG_NUM + 117)

/***************************************************************************
 * OPCODES ASSOCIATED FOR MESSAGES BETWEEN CLI AND CM
 * *************************************************************************/
#define OAM_CLI_CM_INST_DATA_REQ               (OAM_BASE_MSG_NUM + 118)
#define OAM_CM_CLI_INST_DATA_RESP              (OAM_BASE_MSG_NUM + 119)

/*CLI MSG: Nitin:21-Dec-2009*/
#define OAM_CLI_CM_DATA_REQ                    (OAM_BASE_MSG_NUM + 120)
#define OAM_CM_CLI_DATA_RESP                   (OAM_BASE_MSG_NUM + 121)

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (OAM_BASE_MSG_NUM + 111) to (OAM_BASE_MSG_NUM + 118).
 */
/* Added for 2 slot chassis. Start */
#define OAM_PDC_PDD_PERF_DATA_LOGGING_REQ      (OAM_BASE_MSG_NUM + 122)
#define OAM_PDC_PDD_FILE_CLOSE_AND_MOVE_REQ    (OAM_BASE_MSG_NUM + 123)

#define OAM_PDD_CM_SEND_CONFIG_DATA_REQ        (OAM_BASE_MSG_NUM + 124)
#define OAM_AFH_CM_SEND_CONFIG_DATA_REQ        (OAM_BASE_MSG_NUM + 125)
/* Added for 2 slot chassis. End */

 #define OAM_LAST_MSG_NUM                      (OAM_BASE_MSG_NUM + 126)     



/* OPCODES for CFG SCM interface start */
#define CFG_SCM_BASE_MSG_NUM                   (OAM_LAST_MSG_NUM + 0)
#define OAMS_SCM_CFG_UNLOCK_RESP               (CFG_SCM_BASE_MSG_NUM + 1) /*OamsScmCfgUnlockResp*/
#define OAMS_SCM_CFG_LOCK_RESP                 (CFG_SCM_BASE_MSG_NUM + 2) /*OamsScmCfgLockResp*/
#define OAMS_SCM_CFG_ALARM_IND                 (CFG_SCM_BASE_MSG_NUM + 3) /*OamsCfgScmCfgAlarmInd*/
#define OAMS_CFG_SCM_UNLOCK_REQ                (CFG_SCM_BASE_MSG_NUM + 4) /*OamsCfgScmUnlockReq*/
#define OAMS_CFG_SCM_LOCK_REQ                  (CFG_SCM_BASE_MSG_NUM + 5) /*OamsCfgScmLockReq*/
#define OAMS_BPM_CFG_ALARM_IND                 (CFG_SCM_BASE_MSG_NUM + 6)

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (CFG_SCM_BASE_MSG_NUM + 6) to (CFG_SCM_BASE_MSG_NUM + 15).
 */
#define CFG_SCM_LAST_MSG_NUM                   (CFG_SCM_BASE_MSG_NUM + 15)
/* OPCODES for CFG SCM interface end */
 
/* OPCODES for CFG AFH interface start */
#define CFG_AFH_BASE_MSG_NUM                   (CFG_SCM_LAST_MSG_NUM + 0)
#define OAMS_CFG_AFH_ALARM_IND                 (CFG_AFH_BASE_MSG_NUM + 1) /*OamsCfgAfhSysAlarm*/
#define OAMS_CFG_AFH_CON_MODE_INDICATION       (CFG_AFH_BASE_MSG_NUM + 2)

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (CFG_AFH_BASE_MSG_NUM + 2) to (CFG_AFH_BASE_MSG_NUM + 11).
 */
#define CFG_AFH_LAST_MSG_NUM                   (CFG_AFH_BASE_MSG_NUM + 11)
/* OPCODES for CFG AFH interface end */
 
/* OPCODES for XXX PDC Interface start */
#define XXX_PTDC_BASE_MSG_NUM                  (CFG_AFH_LAST_MSG_NUM + 0)
#define PSAPP_XXX_PTDC_CER_IND                 (XXX_PTDC_BASE_MSG_NUM + 1)

/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (XXX_PTDC_BASE_MSG_NUM + 2) to (XXX_PTDC_BASE_MSG_NUM + 11).
 */
#define XXX_PTDC_LAST_MSG_NUM                  (XXX_PTDC_BASE_MSG_NUM + 11)
/* OPCODES for XXX PDC Interface end */


/*** Opcodes at  Interface between UL and DL start ***/

#define UL_DL_BASE_MSG_NUM                     (XXX_PTDC_LAST_MSG_NUM+0)

#define PSAPP_UL_DL_RE_ESTABLISH_TBF           (UL_DL_BASE_MSG_NUM + 1)
/* New Message Opcodes for this interface to be inserted here.
 */
#define UL_DL_LAST_MSG_NUM                     (UL_DL_BASE_MSG_NUM + 5)

 /*** Opcodes at  Interface between ULand RADL start ***/

#define UL_RADL_BASE_MSG_NUM                   (UL_DL_LAST_MSG_NUM+0)

/* New Message Opcodes for this interface to be inserted here.
 */
#define PSAPP_RADL_UL_TLLI_UPDATE_IND          (UL_RADL_BASE_MSG_NUM + 1)
 
#define UL_RADL_LAST_MSG_NUM                   (UL_RADL_BASE_MSG_NUM + 5)

/*Start CS2.2 -  New Message Opcodes for CFG - BTSH Interface 
 * from (OAMS_CFG_BTSH_BASE_MSG_NUM ) to ( OAMS_CFG_BTSH_BASE_MSG_NUM + 10).
 */
#define OAMS_CFG_BTSH_BASE_MSG_NUM             (UL_RADL_LAST_MSG_NUM + 1)
#define OAMS_CFG_BTSH_ADD_BTS_REQ              (OAMS_CFG_BTSH_BASE_MSG_NUM + 0) /*OamsCfgBichAddBicReq*/
#define OAMS_BTSH_CFG_ADD_BTS_RESP             (OAMS_CFG_BTSH_BASE_MSG_NUM + 1) /*OamsBichCfgAddBicResp*/
#define OAMS_CFG_BTSH_DEL_BTS_REQ              (OAMS_CFG_BTSH_BASE_MSG_NUM + 2) /*OamsCfgBichDelBicReq*/
#define OAMS_BTSH_CFG_DEL_BTS_RESP             (OAMS_CFG_BTSH_BASE_MSG_NUM + 3) /*OamsBichCfgDelBicResp*/
#define OAMS_BTSH_CFG_ALARM_IND                (OAMS_CFG_BTSH_BASE_MSG_NUM + 4) /*OamsBichCfgAlarmInd*/

/* Change for R2.2 : Start */
#define OAMS_CFG_BTSH_LOCK_REQ                 (OAMS_CFG_BTSH_BASE_MSG_NUM + 9) /*OamsCfgBichLockReq*/
#define OAMS_BTSH_CFG_LOCK_RESP                (OAMS_CFG_BTSH_BASE_MSG_NUM + 10) /*OamsBichCfgLockResp*/
#define OAMS_CFG_BTSH_UNLOCK_REQ               (OAMS_CFG_BTSH_BASE_MSG_NUM + 11) /*OamsCfgBichUnlockReq*/
#define OAMS_BTSH_CFG_UNLOCK_RESP              (OAMS_CFG_BTSH_BASE_MSG_NUM + 12) /*OamsBichCfgUnlockResp*/
#define OAMS_CFG_BTSH_BTS_RESET                (OAMS_CFG_BTSH_BASE_MSG_NUM + 13) /*OamsCfgBichBtsReset*/
#define OAMS_CFG_BTSH_ADD_TRX_INDICATION       (OAMS_CFG_BTSH_BASE_MSG_NUM + 14) /*OamsCfgBichAddTrxInd*/
#define OAMS_CFG_BTSH_DEL_TRX_INDICATION       (OAMS_CFG_BTSH_BASE_MSG_NUM + 15) /*OamsCfgBichDelTrxInd*/
#define OAMS_CFG_BTSH_IP_LINK_UP               (OAMS_CFG_BTSH_BASE_MSG_NUM + 16) 
#define OAMS_CFG_BTSH_IP_LINK_DOWN             (OAMS_CFG_BTSH_BASE_MSG_NUM + 17) 
#define OAMS_CFG_BTSH_LAST_MSG_NUM             (OAMS_CFG_BTSH_BASE_MSG_NUM + 20) 
/* Change for R2.2 : End */
/* End - CS2.2 CFG-BTSH interface */

/*Start CS2.2 -  New Message Opcodes for ABIHM - BTSH Interface 
 */
#define CSAPP_ABIHM_BTSH_BASE_MSG_NUM          (OAMS_CFG_BTSH_LAST_MSG_NUM + 1)
#define OAMS_BTSH_ABIHM_BM_RESTART             (CSAPP_ABIHM_BTSH_BASE_MSG_NUM + 2) 
#define CSAPP_ABIHM_BTSH_FAILURE_EVENT_REPORT  (CSAPP_ABIHM_BTSH_BASE_MSG_NUM + 3) 
#define OAMS_BTSH_ABIHM_BM_EVENT_INQ           (CSAPP_ABIHM_BTSH_BASE_MSG_NUM + 4) 
#define OAMS_BTSH_ABIHM_BM_CAP_INQ             (CSAPP_ABIHM_BTSH_BASE_MSG_NUM + 5) /*OamsBtshAbihmBmCapInq*/
#define CSAPP_ABIHM_BTSH_BM_CAP_REPORT         (CSAPP_ABIHM_BTSH_BASE_MSG_NUM + 6) /*OamsBtshAbihmBmCapReport*/
#define OAMS_BTSH_ABIHM_ASSOC_DISC_REQ         (CSAPP_ABIHM_BTSH_BASE_MSG_NUM + 7) /*OamsBtshAbihmDiscReq*/

#define CSAPP_ABIHM_BTSH_LAST_MSG_NUM          (CSAPP_ABIHM_BTSH_BASE_MSG_NUM + 10)

/*CS2.2 - The last base shall be changed to CSAPP_ABIHM_BTSH_LAST_MSG_NUM + 100, but since it will impact SCM and we have enough room between CSAPP_ABIHM_BTSH_LAST_MSG_NUM and UL_RADL_LAST_MSG_NUM+100. It is kept like this */

/* Opcodes at interface between CPM and RM    */

#define CPM_RM_BASE_MSG_NUM                    (CSAPP_ABIHM_BTSH_LAST_MSG_NUM + 0)



#define CSAPP_CPM_RM_CHAN_SETUP_REQ            (CPM_RM_BASE_MSG_NUM + 1) /*CsappCpmRmChanSetupReq*/
#define CSAPP_RM_CPM_SETUP_SUCC                (CPM_RM_BASE_MSG_NUM + 2) /*CsappRmCpmSetupSucc*/
#define CSAPP_RM_CPM_CHAN_SETUP_FAIL           (CPM_RM_BASE_MSG_NUM + 3) /*CsappRmCpmChanSetupFail*/
#define CSAPP_CPM_RM_CHAN_REL_REQ              (CPM_RM_BASE_MSG_NUM + 4) /*CsappCpmRmChanRelReq*/
#define CSAPP_RM_CPM_CHAN_REL_CMP              (CPM_RM_BASE_MSG_NUM + 5) /*CsappRmCpmChanRelCmp*/ 
#define CSAPP_RM_CPM_ASS_CMD_IND               (CPM_RM_BASE_MSG_NUM + 6) /*CsappRmCpmAssCmdInd*/
#define CSAPP_RM_CPM_HO_CMD                    (CPM_RM_BASE_MSG_NUM + 7) /*CsappRmCpmHoCmdv*/
#define CSAPP_RM_CPM_REV_TO_OLD_CHAN_IND       (CPM_RM_BASE_MSG_NUM + 8) /*CsappRmCpmReversionToOldChanInd*/
#define CSAPP_CPM_RM_ASSIGN_HO_CMD_SENT        (CPM_RM_BASE_MSG_NUM + 9) /*CsappCpmRmAssignHoCmdSent*/
#define CSAPP_CPM_RM_ASSIGN_CMP_IND            (CPM_RM_BASE_MSG_NUM + 10) /*CsappCpmRmAssignCmpInd*/
#define CSAPP_CPM_RM_HO_CMP_IND                (CPM_RM_BASE_MSG_NUM + 11) /*CsappCpmRmHoCmpInd*/
#define CSAPP_CPM_RM_STOP_T3109_REQ            (CPM_RM_BASE_MSG_NUM + 12) /*CsappCpmRmStopt3109Req*/
/* Change Start: R3-BSC
   Dated: 3-Aug-2011
*/

#define CSAPP_CPHM_SYSCPHM_KPI_REQ             (CPM_RM_BASE_MSG_NUM + 13) /*CsappCpmRmStopt3109Req*/
#define CSAPP_CPHM_SYSCPHM_PERF_REQ            (CPM_RM_BASE_MSG_NUM + 14) /*CsappCpmRmStopt3109Req*/

#define CSAPP_CPHM_CPHM_INTER_CARD_HO_REQ      (CPM_RM_BASE_MSG_NUM + 15)
#define CSAPP_CPHM_CPHM_INTER_CARD_HO_FAIL     (CPM_RM_BASE_MSG_NUM + 16)
#define CSAPP_CPHM_CPHM_INTER_CARD_HO_COMP     (CPM_RM_BASE_MSG_NUM + 17)
#define CSAPP_CPHM_CPHM_INTER_CARD_HO_DET      (CPM_RM_BASE_MSG_NUM + 18)
#define CSAPP_CPHM_CPHM_INTER_CARD_HO_CMD      (CPM_RM_BASE_MSG_NUM + 19)
#define CSAPP_CPHM_CPHM_INTER_CARD_DTAP_IND    (CPM_RM_BASE_MSG_NUM + 20)


/* Change End: R3-BSC
   Dated: 3-Aug-2011
*/



#define CPM_RM_LAST_MSG_NUM                    (CPM_RM_BASE_MSG_NUM + 20)

/* CS 3.0 (On The Fly changes)*/
/* Opcodes at interface between CELLH and MRHM starts */
#define OAMS_CELLH_MRHM_BASE_MSG_NUM           (CPM_RM_LAST_MSG_NUM + 0)   

#define OAMS_CELLH_MRHM_CSNEIGHCELLS_CHANGE    (OAMS_CELLH_MRHM_BASE_MSG_NUM + 1) /*OamsCellhMrhmCsNeighCellsChange*/
#define OAMS_CELLH_MRHM_BA_IND                 (OAMS_CELLH_MRHM_BASE_MSG_NUM + 2)

#define OAMS_CELLH_MRHM_LAST_MSG_NUM           (OAMS_CELLH_MRHM_BASE_MSG_NUM + 5)

/* Opcodes at interface between CELLH and MRHM ends */

/* CS 3.0 (On The Fly changes)*/
/* Opcodes at interface between CFG and MRHM starts */
#define OAMS_CFG_MRHM_BASE_MSG_NUM             (OAMS_CELLH_MRHM_LAST_MSG_NUM + 0)

#define CSAPP_MRHM_CFG_ALARM_IND               (OAMS_CFG_MRHM_BASE_MSG_NUM + 1) /*CsappMrhmCfgAlarmInd*/
#define OAMS_CFG_MRHM_CELL_DELETE              (OAMS_CFG_MRHM_BASE_MSG_NUM + 2) /*OamsCfgMrhmCellDelete*/

#define OAMS_CFG_MRHM_LAST_MSG_NUM             (OAMS_CFG_MRHM_BASE_MSG_NUM + 5)

/* Opcodes at interface between CELLH and MRHM ends */

/* Opcode at interface between CFG and PDC starts */

#define OAMS_CFG_PDC_BASE_MSG_NUM              (OAMS_CFG_MRHM_LAST_MSG_NUM + 0)

#define OAMS_CFG_PDC_TRAU_UL_FRAMESTATUS       (OAMS_CFG_PDC_BASE_MSG_NUM + 1) /*CfgPdcTrauUlFrameStatus*/
/*Changes PCU R2.5  -- START*/
#define OAMS_CFG_PDC_BSS_LOCK_IND              (OAMS_CFG_PDC_BASE_MSG_NUM + 2) /*OamsCfgPdcBssLockInd*/
#define OAMS_CFG_PDC_BSS_UNLOCK_IND            (OAMS_CFG_PDC_BASE_MSG_NUM + 3) /*OamsCfgPdcBssUnlockInd*/
/*Changes PCU R2.5  -- END*/

#define OAMS_CFG_PDC_LAST_MSG_NUM              (OAMS_CFG_PDC_BASE_MSG_NUM + 5)

/* Opcode at interface between CFG and RM ends */

/*BSC CS4.0 HA Changes Starts*/
#define OAMS_CFG_RM_BASE_MSG_NUM               (OAMS_CFG_PDC_LAST_MSG_NUM)
#define OAMS_CFG_RM_LAST_MSG_NUM               (OAMS_CFG_RM_BASE_MSG_NUM + 7)

/* Opcode at interface between RM and RRAL ends */


/*  Added for new Object model  */
/***********************************************************************/

/*****************************************************************
SCM <---> OAM     (22-09-2011)  BASE_OPCODE_SCM
*****************************************************************/
/*** Opcodes at Interface between OAM and SCM start ***/

#define  BASE_OPCODE_SCM                       OAMS_CFG_RM_LAST_MSG_NUM 


/*   OAM  ---> SCM  */
/* Genernal Configuration */
#define OAM_SCM_BSSAPINTF_CONFIG                     (BASE_OPCODE_SCM + 1)
#define OAM_SCM_BSSAPCIC_CONFIG                      (BASE_OPCODE_SCM + 2)
#define OAM_SCM_SCCPROUTE_CONFIG                     (BASE_OPCODE_SCM + 3)/*OamScmSccpRouteConfig*/
#define OAM_SCM_SCCPSSN_CONFIG                       (BASE_OPCODE_SCM + 4)
#define OAM_SCM_MTP3GEN_CONFIG                       (BASE_OPCODE_SCM + 5)
#define OAM_SCM_MTP3_COMBINEDLINKSET_CONFIG          (BASE_OPCODE_SCM + 6)
#define OAM_SCM_MTP3ROUTE_CONFIG                     (BASE_OPCODE_SCM + 7)
#define OAM_SCM_LINKSET_CONFIG                       (BASE_OPCODE_SCM + 8)
#define OAM_SCM_LINKSET_ADMIN_CONFIG                 (BASE_OPCODE_SCM + 9)
#define OAM_SCM_LINK_CONFIG                          (BASE_OPCODE_SCM + 10)
#define OAM_SCM_LINK_ADMIN_CONFIG                    (BASE_OPCODE_SCM + 11)
#define OAM_SCM_SIGTRAN_LOCALIP_CONFIG               (BASE_OPCODE_SCM + 12)
#define OAM_SCM_SIGTRAN_REMOTEIP_CONFIG              (BASE_OPCODE_SCM + 13)
#define OAM_SCM_SIGTRAN_NW_CONFIG                    (BASE_OPCODE_SCM + 14)
#define OAM_SCM_SIGTRAN_PS_CONFIG                    (BASE_OPCODE_SCM + 15)
#define OAM_SCM_SIGTRAN_PSP_CONFIG                   (BASE_OPCODE_SCM + 16)
#define OAM_SCM_SIGTRAN_PSP_ADMIN_CONFIG             (BASE_OPCODE_SCM + 17)
#define OAM_SCM_SIGTRAN_ROUTE_CONFIG                 (BASE_OPCODE_SCM + 18)
/*#define OAM_SCM_NEOMCIPADDRESS                       (BASE_OPCODE_SCM + 19)*/
#define OAM_SCM_MLPPPTS_CONFIG                       (BASE_OPCODE_SCM + 20)
/* Timers */
#define OAM_SCM_BSSAP_TIMER_CONFIG                   (BASE_OPCODE_SCM + 21)
#define OAM_SCM_SCCP_TIMER_CONFIG                    (BASE_OPCODE_SCM + 22)
#define OAM_SCM_MTP3_TIMER_CONFIG                    (BASE_OPCODE_SCM + 23)
#define OAM_SCM_MTP2_TIMER_CONFIG                    (BASE_OPCODE_SCM + 24)
#define OAM_SCM_M3UA_TIMER_CONFIG                    (BASE_OPCODE_SCM + 25)
#define OAM_SCM_SCTP_TIMER_CONFIG                    (BASE_OPCODE_SCM + 26)
/* Pegs */
#define OAM_SCM_BSSAP_CKT_SPRVSN_PEG_GET             (BASE_OPCODE_SCM + 27)
#define OAM_SCM_BSSAP_CNTRL_MSG_PEG_GET              (BASE_OPCODE_SCM + 28)
#define OAM_SCM_SCCP_GENPEG_GET                      (BASE_OPCODE_SCM + 29)
#define OAM_SCM_SCCP_ROUTE_PEG_GET                   (BASE_OPCODE_SCM + 30)
#define OAM_SCM_MTP3_LINK_PEG_GET                    (BASE_OPCODE_SCM + 31)
#define OAM_SCM_MTP3_ROUTE_PEG_GET                   (BASE_OPCODE_SCM + 32)
#define OAM_SCM_MTP3_LINKSET_PEG_GET                 (BASE_OPCODE_SCM + 33)
#define OAM_SCM_MTP2_LINK_PEG_GET                    (BASE_OPCODE_SCM + 34)
#define OAM_SCM_M3UA_PEG_GET                         (BASE_OPCODE_SCM + 35)
#define OAM_SCM_SCTP_PEG_GET                         (BASE_OPCODE_SCM + 36)

/* Status Query */
#define OAM_SCM_LINK_STATUS_GET                      (BASE_OPCODE_SCM + 37)
#define OAM_SCM_LINKSET_STATUS_GET                   (BASE_OPCODE_SCM + 38)
#define OAM_SCM_M3UA_PSP_STATUS_GET                  (BASE_OPCODE_SCM + 39)

/* end here */
/* MSG OPCODE SCM --> OAM*/
#define OAM_SCM_BSSAPINTF_CONFIG_RESP                     (BASE_OPCODE_SCM + 51)
#define OAM_SCM_BSSAPCIC_CONFIG_RESP                      (BASE_OPCODE_SCM + 52)
#define OAM_SCM_SCCPROUTE_CONFIG_RESP                     (BASE_OPCODE_SCM + 53)/*OamScmSccpRouteConfig*/
#define OAM_SCM_SCCPSSN_CONFIG_RESP                       (BASE_OPCODE_SCM + 54)
#define OAM_SCM_MTP3GEN_CONFIG_RESP                       (BASE_OPCODE_SCM + 55)
#define OAM_SCM_MTP3_COMBINEDLINKSET_CONFIG_RESP          (BASE_OPCODE_SCM + 56)
#define OAM_SCM_MTP3ROUTE_CONFIG_RESP                     (BASE_OPCODE_SCM + 57)
#define OAM_SCM_LINKSET_CONFIG_RESP                       (BASE_OPCODE_SCM + 58)
#define OAM_SCM_LINKSET_ADMIN_CONFIG_RESP                 (BASE_OPCODE_SCM + 59)
#define OAM_SCM_LINK_CONFIG_RESP                          (BASE_OPCODE_SCM + 60)
#define OAM_SCM_LINK_ADMIN_CONFIG_RESP                    (BASE_OPCODE_SCM + 61)
#define OAM_SCM_SIGTRAN_LOCALIP_CONFIG_RESP               (BASE_OPCODE_SCM + 62)
#define OAM_SCM_SIGTRAN_REMOTEIP_CONFIG_RESP              (BASE_OPCODE_SCM + 63)
#define OAM_SCM_SIGTRAN_NW_CONFIG_RESP                    (BASE_OPCODE_SCM + 64)
#define OAM_SCM_SIGTRAN_PS_CONFIG_RESP                    (BASE_OPCODE_SCM + 65)
#define OAM_SCM_SIGTRAN_PSP_CONFIG_RESP                   (BASE_OPCODE_SCM + 66)
#define OAM_SCM_SIGTRAN_PSP_ADMIN_CONFIG_RESP             (BASE_OPCODE_SCM + 67)
#define OAM_SCM_SIGTRAN_ROUTE_CONFIG_RESP                 (BASE_OPCODE_SCM + 68)
#define OAM_SCM_NEOMCIPADDRESG_RESP                       (BASE_OPCODE_SCM + 69)
#define OAM_SCM_MLPPPTS_CONFIG_RESP                       (BASE_OPCODE_SCM + 70)
/* Timers */
#define OAM_SCM_BSSAP_TIMER_CONFIG_RESP                   (BASE_OPCODE_SCM + 71)
#define OAM_SCM_SCCP_TIMER_CONFIG_RESP                    (BASE_OPCODE_SCM + 72)
#define OAM_SCM_MTP3_TIMER_CONFIG_RESP                    (BASE_OPCODE_SCM + 73)
#define OAM_SCM_MTP2_TIMER_CONFIG_RESP                    (BASE_OPCODE_SCM + 74)
#define OAM_SCM_M3UA_TIMER_CONFIG_RESP                    (BASE_OPCODE_SCM + 75)
#define OAM_SCM_SCTP_TIMER_CONFIG_RESP                    (BASE_OPCODE_SCM + 76)
/* Pegs */
#define OAM_SCM_BSSAP_CKT_SPRVSN_PEG_RESP                 (BASE_OPCODE_SCM + 77)
#define OAM_SCM_BSSAP_CNTRL_MSG_PEG_RESP                  (BASE_OPCODE_SCM + 78)
#define OAM_SCM_SCCP_GENPEG_RESP                          (BASE_OPCODE_SCM + 79)
#define OAM_SCM_SCCP_ROUTE_PEG_RESP                       (BASE_OPCODE_SCM + 80)
#define OAM_SCM_MTP3_LINK_PEG_RESP                        (BASE_OPCODE_SCM + 81)
#define OAM_SCM_MTP3_ROUTE_PEG_RESP                       (BASE_OPCODE_SCM + 82)
#define OAM_SCM_MTP3_LINKSET_PEG_RESP                     (BASE_OPCODE_SCM + 83)
#define OAM_SCM_MTP2_LINK_PEG_RESP                        (BASE_OPCODE_SCM + 84)
#define OAM_SCM_M3UA_PEG_RESP                             (BASE_OPCODE_SCM + 85)
#define OAM_SCM_SCTP_PEG_RESP                             (BASE_OPCODE_SCM + 86)

/* Status Query Response*/
#define OAM_SCM_LINK_STATUS_RESP                          (BASE_OPCODE_SCM + 86)
#define OAM_SCM_LINKSET_STATUS_RESP                       (BASE_OPCODE_SCM + 87)
#define OAM_SCM_M3UA_PSP_STATUS_RESP                      (BASE_OPCODE_SCM + 88)

/***Added on 2nd Feb 2012 Start ***/
#define SCM_OAM_INPROGRESS_IND                            (BASE_OPCODE_SCM + 89)
#define SCM_OAM_INITDONE_IND                              (BASE_OPCODE_SCM + 90)
/***Added on 2nd Feb 2012 Ends ****/

#define SCM_OAM_ALARM_IND                                 (BASE_OPCODE_SCM + 99)

#define  LAST_OPCODE_SCM                                  (BASE_OPCODE_SCM + 99)

/* Opcodes at interface between OAM and SCM ends */

/* end here */

/*****************************************************************
BSSAP <---> CSAPP     (22-09-2011)  BASE_OPCODE_BSSAP
*****************************************************************/

#define BASE_OPCODE_BSSAP      LAST_OPCODE_SCM

/* Message Opcode  Application -> BSSAP */
#define CSAPP_BSSAP_UNIT_DATA_REQ            (BASE_OPCODE_BSSAP + 1)

/* Message Opcode  BSSAP --> Application*/
#define BSSAP_CSAPP_UNIT_DATA_IND            (BASE_OPCODE_BSSAP + 2)

#define  LAST_OPCODE_BSSAP                   (BASE_OPCODE_BSSAP + 3)
/* Opcodes at interface between BSSAP and CSAPP ends */

/*****************************************************************
SCTP  <---> ABISD       (22-09-2011)  BASE_OPCODE_SCTP
*****************************************************************/


#define BASE_OPCODE_SCTP                    LAST_OPCODE_BSSAP


#define SCTP_ABIS_API_DATA_REQ              (BASE_OPCODE_SCTP + 1)
#define SCTP_ABIS_API_DATA_IND              (BASE_OPCODE_SCTP + 2) 
#define SCTP_ABIS_API_ASSOC_UP_IND          (BASE_OPCODE_SCTP + 3)
#define SCTP_ABIS_API_ASSOC_DOWN_IND        (BASE_OPCODE_SCTP + 4)
#define SCTP_ABIS_API_ASSOC_DISC_REQ        (BASE_OPCODE_SCTP + 5)
#define SCTP_ABIS_API_ASSOC_DISC_IND        (BASE_OPCODE_SCTP + 6)
#define SCTP_ABIS_API_ASSOC_DISC_CFM        (BASE_OPCODE_SCTP + 8)
#define SCTP_ABIS_API_ASSOC_STA_REQ         (BASE_OPCODE_SCTP + 9)
#define SCTP_ABIS_API_ASSOC_STA_CFM         (BASE_OPCODE_SCTP + 10)
#define SCTP_ABIS_API_ASSOC_ADDR_INFO_REQ   (BASE_OPCODE_SCTP + 11)
#define SCTP_ABIS_API_ASSOC_ADDR_INFO_CFM   (BASE_OPCODE_SCTP + 12) 

#define LAST_OPCODE_SCTP                    (BASE_OPCODE_SCTP + 15)

/* Opcodes at interface between ABISD and SCTP ends */


/* Changes for CCU cs4.0 start*/
/* (19-05-2009) Opcodes at interface between CFG & OMCINTF and OMCINTF & CM*/
#define BASE_OPCODE_OMCINTF                    LAST_OPCODE_SCTP 
#define OAM_CFG_OMCINTF_CONFIG_MSG             (BASE_OPCODE_OMCINTF + 1) 
#define OAM_OMCINTF_CFG_CONFIG_ACK             (BASE_OPCODE_OMCINTF + 2)
#define OAM_OMCINTF_CM_UP                      (BASE_OPCODE_OMCINTF + 3)
#define OAM_OMCINTF_CM_DOWN                    (BASE_OPCODE_OMCINTF + 4)
#define OAM_OMCINTF_CM_OMC_MSG                 (BASE_OPCODE_OMCINTF + 5)
/* Change for R2.3.3 - CBCH */                 
#define OAM_CM_CFG_ADD_NODE_SUCCESS_IND        (BASE_OPCODE_OMCINTF + 6)
                                               
#define LAST_OPCODE_OMCINTF                    (BASE_OPCODE_OMCINTF + 10)

/* Opcodes at interface between CFG and OMCINTF Ends*/

/*Op Codes between CFG and CM */
#define BASE_OPCODE_CMCFG                      LAST_OPCODE_OMCINTF
#define OAMS_CFG_CM_SET_IP_ADDRESS_REQ         (BASE_OPCODE_CMCFG + 1) /*OamsCfgCmSetIpAddress*/
#define OAM_CM_CFG_SET_IP_ADDRESS_RESP         (BASE_OPCODE_CMCFG + 2) /*OamCmCfgSetIpAddressResp*/
#define OAM_CM_CFG_SNMP_GET_REQ                (BASE_OPCODE_CMCFG + 3) /**/
#define OAMS_CFG_CM_SNMP_GET_RESP              (BASE_OPCODE_CMCFG + 4) /**/
#define LAST_OPCODE_CMCFG                      (BASE_OPCODE_CMCFG + 10)

/*Op Codes between CM and AFH */
#define BASE_OPCODE_CMAFH                      LAST_OPCODE_CMCFG
#define OAM_CM_AFH_ADDNODE_START               (BASE_OPCODE_CMAFH + 1)
#define OAM_CM_AFH_ADDNODE_STATUS              (BASE_OPCODE_CMAFH + 2)

/*Added for R3-BSC  25th Jan.2012 ** Start ***/
#define OAM_CM_AFH_SNMP_GET_REQ                (BASE_OPCODE_CMAFH + 3)
#define OAM_AFH_CM_SNMP_GET_RESP               (BASE_OPCODE_CMAFH + 4)
/*Added for R3-BSC  25th Jan.2012 ** Ends  ***/

#define LAST_OPCODE_CMAFH                      (BASE_OPCODE_CMAFH + 10)

/* Op codes between RRAL and TRXH interface*/
#define BASE_OPCODE_RRALTRXH                   LAST_OPCODE_CMAFH 
#define OAMS_TRXHENV_TRXH_DSP_AVAILABILITY_IND (BASE_OPCODE_RRALTRXH + 1)
#define LAST_OPCODE_RRALTRXH                   (BASE_OPCODE_RRALTRXH + 10)

/* Changes For ChannelActAck Retry Implementation Starts  */
/* Opcodes at interface between CPHM and TRXH */

#define BASE_OPCODE_CPHMTRXH                   LAST_OPCODE_RRALTRXH 

#define CSAPP_CPHM_TRXH_RETRY_EXHAUST_INDN     (BASE_OPCODE_CPHMTRXH+1)
#define LAST_OPCODE_CPHMTRXH                   (BASE_OPCODE_CPHMTRXH+2)
/* Changes For ChannelActAck Retry Implementation Ends  */



/* R2.2 Changes : Starts */
/* Opcodes at interface between BTSH and TRXH */
#define BASE_OPCODE_BTSHTRXH                   LAST_OPCODE_CPHMTRXH 
#define OAMS_BTSH_TRXH_LOCK_IND                (BASE_OPCODE_BTSHTRXH + 1) /*OamsBichTrxhLockInd*/
#define OAMS_BTSH_TRXH_UNLOCK_IND              (BASE_OPCODE_BTSHTRXH + 2) /*OamsBichTrxhUnlockInd*/
#define OAMS_TRXH_BTSH_OPER_STATE_CHANGE_IND   (BASE_OPCODE_BTSHTRXH + 4)
#define OAMS_BTSH_TRXH_IP_LINK_UP              (BASE_OPCODE_BTSHTRXH + 5) 
#define OAMS_BTSH_TRXH_IP_LINK_DOWN            (BASE_OPCODE_BTSHTRXH + 6) 
#define OAMS_TRXH_BTSH_SCTP_CONN_STATUS_ENQ    (BASE_OPCODE_BTSHTRXH + 7) 
#define OAMS_BTSH_TRXH_SCTP_CONN_STATUS_RESP   (BASE_OPCODE_BTSHTRXH + 8) 
#define OAMS_BTSH_ABIHM_SCTP_CONN_STATUS_ENQ   (BASE_OPCODE_BTSHTRXH + 9) 
#define OAMS_ABIHM_BTSH_SCTP_CONN_STATUS_RESP  (BASE_OPCODE_BTSHTRXH + 10) 
/* Added on 18-Jun-2010 - For Mantis 12900 */
#define OAMS_CELLH_TRXH_LOCK_IND               (BASE_OPCODE_BTSHTRXH + 11)
#define LAST_OPCODE_BTSHTRXH                   (BASE_OPCODE_BTSHTRXH + 15)

/* R2.2 Changes : Ends */
/* START - Change for R2.3.3 - CBCH */
/* Opcodes at interface between CFG and CBSIF */
#define BASE_OPCODE_CFGCBSIF                   LAST_OPCODE_BTSHTRXH 
#define OAMS_CFG_CBSIF_CONFIG_CBS              (BASE_OPCODE_CFGCBSIF + 1) /*OamsCfgCbsifConfigCbs*/
#define OAMS_CFG_CBSIF_DELETE_CONFIG_CBS       (BASE_OPCODE_CFGCBSIF + 2) /*OamsCfgCbsifDelConfigCbs*/
#define OAMS_CFG_CBSIF_DATA_REQ                (BASE_OPCODE_CFGCBSIF + 3) /*OamsCfgCbsifDataReq*/
#define OAMS_CFG_CBSIF_BREAK_IP                (BASE_OPCODE_CFGCBSIF + 4) /*OamsCfgCbsifBreakIpAddress*/
#define CSAPP_CBSIF_CFG_CONNECTION_DOWN        (BASE_OPCODE_CFGCBSIF + 5) /*CsappCbsifCfgConnectionDown*/
#define CSAPP_CBSIF_CFG_DELETE_CONFIG_CBS_RESP (BASE_OPCODE_CFGCBSIF + 6) /*CsappCbsifCfgDelConfigResp*/
#define CSAPP_CBSIF_CFG_CONNECTION_UP          (BASE_OPCODE_CFGCBSIF + 7) /*CsappCbsifCfgConnectionUp*/
#define CSAPP_CBSIF_CFG_DATA_IND               (BASE_OPCODE_CFGCBSIF + 8) /*CsappCbsifCfgDataInd*/
#define LAST_OPCODE_CFGCBSIF                   (BASE_OPCODE_CFGCBSIF + 20)


/* Opcodes at interface between CBSH and CFG */

#define BASE_OPCODE_CBSHCFG                     LAST_OPCODE_CFGCBSIF
#define OAMS_CFG_SCBSH_ADD_CB_SERVER            (BASE_OPCODE_CBSHCFG + 1) /*OamsCfgCbshAddCbServer*/
#define OAMS_CFG_SCBSH_DEL_CB_SERVER            (BASE_OPCODE_CBSHCFG + 2) /*OamsCfgCbshDelCbServer*/
#define OAMS_CFG_SCBSH_INTF_UP                  (BASE_OPCODE_CBSHCFG + 3) /*OamsCfgCbshIntfUp*/
#define OAMS_CFG_SCBSH_INTF_DOWN                (BASE_OPCODE_CBSHCFG + 4) /*OamsCfgCbshIntfDown*/
#define OAMS_CFG_SCBSH_MODIFY_CBS_IP            (BASE_OPCODE_CBSHCFG + 5) /*OamsCfgCbshModifyCbsIp*/
#define OAMS_CFG_ACBSH_ADD_CB_CELL              (BASE_OPCODE_CBSHCFG + 6) /*OamsCfgCbshAddCbCell*/
#define OAMS_CFG_ACBSH_DEL_CB_CELL              (BASE_OPCODE_CBSHCFG + 7) /*OamsCfgCbshDelCbCell*/
#define OAMS_CFG_ACBSH_CB_CELL_STATUS_CHANGE    (BASE_OPCODE_CBSHCFG + 8) /*OamsCfgCbshCbCellStatusChange*/
/*#define OAMS_CFG_CBSH_CELL_ENABLED           (BASE_OPCODE_CBSHCFG+8) */
/*#define OAMS_CFG_CBSH_CELL_DISABLED          (BASE_OPCODE_CBSHCFG+9) */
#define CSAPP_ACBSH_CFG_ALARM_IND               (BASE_OPCODE_CBSHCFG + 9) /*CsappCbshCfgAlarmInd*/
#define LAST_OPCODE_CBSHCFG                     (BASE_OPCODE_CBSHCFG + 15)

/* Opcodes at interface between CBSH and CBSIF */

/* OPCODES CFG-PDD INTERFACE 07-09-10::12:11 */
#define BASE_OPCODE_CFG_PDD_IF                 LAST_OPCODE_CBSHCFG
#define OAMS_CFG_PDD_START_FTP                 (BASE_OPCODE_CFG_PDD_IF + 1)
#define OAM_PDD_CFG_FTP_COMPLETE               (BASE_OPCODE_CFG_PDD_IF + 2)
#define LAST_OPCODE_CFG_PDD_IF                 (BASE_OPCODE_CFG_PDD_IF + 3)

/* OPCODES CFG-PDD INTERFACE 07-09-10::12:11 */

#define BASE_OPCODE_CBSHCBSIF                  LAST_OPCODE_CFG_PDD_IF
#define CSAPP_CBSIF_SCBSH_DATA_IND             (BASE_OPCODE_CBSHCBSIF + 1) /*CsappCbsifCbshDataInd*/
#define CSAPP_SCBSH_CBSIF_DATA_REQ             (BASE_OPCODE_CBSHCBSIF + 2) /*CsappCbshCbsifDataReq*/
#define LAST_OPCODE_CBSHCBSIF                  (BASE_OPCODE_CBSHCBSIF + 4)

/* Opcodes at interface between CBSH and CELLH */


#define BASE_OPCODE_CBSHCELLH                  LAST_OPCODE_CBSHCBSIF
#define CSAPP_ACBSH_CELLH_CBCH_SI_MODIFY_REQ   (BASE_OPCODE_CBSHCELLH + 1) /*CsappCbshCellhSIMOdifyReq*/
#define LAST_OPCODE_CBSHCELLH                  (BASE_OPCODE_CBSHCELLH + 4)

/* Opcodes at interface between CBSH and ABIHM */

#define BASE_OPCODE_CBSHABIHM                   LAST_OPCODE_CBSHCELLH
#define CSAPP_ACBSH_ABIHM_SMSCB_CMD_MSG         (BASE_OPCODE_CBSHABIHM + 1)
#define CSAPP_ABIHM_ACBSH_CBCH_LOAD_INDICATION  (BASE_OPCODE_CBSHABIHM + 2)
#define CSAPP_ACBSH_ABIHM_CHAN_ACT_REQ          (BASE_OPCODE_CBSHABIHM + 3)
#define CSAPP_ABIHM_ACBSH_CHAN_ACTIVATION_ACK   (BASE_OPCODE_CBSHABIHM + 4)
#define CSAPP_ABIHM_ACBSH_CHAN_ACTIVATION_NACK  (BASE_OPCODE_CBSHABIHM + 5)
#define CSAPP_ACBSH_ABIHM_RF_CHAN_REL           (BASE_OPCODE_CBSHABIHM + 6)
#define CSAPP_ABIHM_ACBSH_RF_CHAN_REL_ACK       (BASE_OPCODE_CBSHABIHM + 7)
#define CSAPP_ABIHM_ACBSH_ERROR_REPORT          (BASE_OPCODE_CBSHABIHM + 8)
#define LAST_OPCODE_CBSHABIHM                   (BASE_OPCODE_CBSHABIHM + 15)


/* Opcodes at interface between CBSH and RRAL */
#define BASE_OPCODE_CBSHRRAL                   LAST_OPCODE_CBSHABIHM
#define CSAPP_ACBSH_RRAL_CHAN_ALLOC_REQ        (BASE_OPCODE_CBSHRRAL + 1)
#define CSAPP_ACBSH_RRAL_CHAN_DEALLOC_REQ      (BASE_OPCODE_CBSHRRAL + 2)
#define CSAPP_RRAL_ACBSH_BPC_RELEASE           (BASE_OPCODE_CBSHRRAL + 3)
#define CSAPP_RRAL_ACBSH_CHAN_ALLOC_ACK        (BASE_OPCODE_CBSHRRAL + 4)
#define CSAPP_RRAL_ACBSH_CHAN_ALLOC_NACK       (BASE_OPCODE_CBSHRRAL + 5)
#define LAST_OPCODE_CBSHRRAL                   (BASE_OPCODE_CBSHRRAL + 8)

/* Opcodes at interface between CBSH and CM   */

#define BASE_OPCODE_CBSHCM                     LAST_OPCODE_CBSHRRAL
#define OAM_CM_SCBSH_DATA_IND                  (BASE_OPCODE_CBSHCM + 1) /*OamCmCbshDataInd*/
#define CSAPP_SCBSH_CM_DATA_REQ                (BASE_OPCODE_CBSHCM + 2) /*CsappCbshCmDataReq*/
#define LAST_OPCODE_CBSHCM                     (BASE_OPCODE_CBSHCM + 4)


/* Opcodes at interface between SCBSH and ACBSH    */
#define BASE_OPCODE_SCBSHACBSH                                 LAST_OPCODE_CBSHCM
#define CSAPP_SCBSH_ACBSH_WRITE_REPLACE_REQ                    (BASE_OPCODE_SCBSHACBSH + 1)
#define CSAPP_SCBSH_ACBSH_KILL_REQ                             (BASE_OPCODE_SCBSHACBSH + 2)
#define CSAPP_SCBSH_ACBSH_STATUS_LOAD_QUERY_REQ                (BASE_OPCODE_SCBSHACBSH + 3)
#define CSAPP_SCBSH_ACBSH_STATUS_MESSAGE_QUERY_REQ             (BASE_OPCODE_SCBSHACBSH + 4)
#define CSAPP_SCBSH_ACBSH_RESET_REQ                            (BASE_OPCODE_SCBSHACBSH + 5)
#define CSAPP_SCBSH_ACBSH_STOP_SMSCB                           (BASE_OPCODE_SCBSHACBSH + 6)
#define CSAPP_SCBSH_ACBSH_SMSCB_TMR_EXPIRY                     (BASE_OPCODE_SCBSHACBSH + 7)
#define CSAPP_SCBSH_ACBSH_WRITE_REQ                            (BASE_OPCODE_SCBSHACBSH + 8)
#define CSAPP_SCBSH_ACBSH_WRITE_REPLACE_RESP_GUARD_TMR_EXPIRY  (BASE_OPCODE_SCBSHACBSH + 9)
#define CSAPP_SCBSH_ACBSH_GET_ACTIVE_TMR_RESP									 (BASE_OPCODE_SCBSHACBSH + 10)
#define CSAPP_SCBSH_ACBSH_CELL_INFO_DISPLAY_REQ								 (BASE_OPCODE_SCBSHACBSH + 11)	/*DRV 22Aug*/
#define CSAPP_SCBSH_ACBSH_STOP_CELL_INFO_DISPLAY_REQ					 (BASE_OPCODE_SCBSHACBSH + 12)	/*AMIT 9May*/
#define CSAPP_ACBSH_SCBSH_STOP_CELL_INFO_DISPLAY_RESP	 				 (BASE_OPCODE_SCBSHACBSH + 13)	/*AMIT 9May*/
#define LAST_OPCODE_SCBSHACBSH                                 (BASE_OPCODE_SCBSHACBSH + 15)


/* Opcodes at interface between ACBSH and SCBSH    */

#define BASE_OPCODE_ACBSHSCBSH                         LAST_OPCODE_SCBSHACBSH
#define CSAPP_ACBSH_SCBSH_REPORT_KILL_ACK_RESP         (BASE_OPCODE_ACBSHSCBSH + 1)
#define CSAPP_ACBSH_SCBSH_REPORT_ACK_RESP              (BASE_OPCODE_ACBSHSCBSH + 2)
#define CSAPP_ACBSH_SCBSH_REPORT_KILL_NACK_RESP        (BASE_OPCODE_ACBSHSCBSH + 3)
#define CSAPP_ACBSH_SCBSH_REPORT_NACK_RESP             (BASE_OPCODE_ACBSHSCBSH + 4)
#define CSAPP_ACBSH_SCBSH_STATUS_LOAD_QUERY_RESP       (BASE_OPCODE_ACBSHSCBSH + 5)
#define CSAPP_ACBSH_SCBSH_STATUS_MESSAGE_QUERY_RESP    (BASE_OPCODE_ACBSHSCBSH + 6)
#define CSAPP_ACBSH_SCBSH_RESTART_INDICATION           (BASE_OPCODE_ACBSHSCBSH + 7)
#define CSAPP_ACBSH_SCBSH_FAILURE_INDICATION           (BASE_OPCODE_ACBSHSCBSH + 8)
#define CSAPP_ACBSH_SCBSH_STOP_SMSCB_ACK               (BASE_OPCODE_ACBSHSCBSH + 9)
#define CSAPP_ACBSH_SCBSH_RESET_ACK                    (BASE_OPCODE_ACBSHSCBSH + 10)
#define CSAPP_ACBSH_SCBSH_RESET_NACK                   (BASE_OPCODE_ACBSHSCBSH + 11)
#define CSAPP_ACBSH_SCBSH_DEL_CB_CELL_IND              (BASE_OPCODE_ACBSHSCBSH + 12)
#define CSAPP_ACBSH_SCBSH_GET_ACTIVE_TMR_REQ					 (BASE_OPCODE_ACBSHSCBSH + 13)
#define CSAPP_ACBSH_SCBSH_CELL_INFO_DISPLAY_RESP			 (BASE_OPCODE_ACBSHSCBSH + 14)	/*DRV 22Aug*/
#define LAST_OPCODE_ACBSHSCBSH                         (BASE_OPCODE_ACBSHSCBSH + 15)

/* END - Change for R2.3.3 - CBCH */

/*Changes PCU R2.5 --Start*/
#define BSC_PSAPP_MSG_OPCODE_BASE              (LAST_OPCODE_ACBSHSCBSH + 0)

/************************************************************************
OPCODES ASSOCIATED FOR MESSAGES BETWEEN CFG AND GBH
**************************************************************************/
#define GBH_CFG_BASE_MSG_NUM                   (BSC_PSAPP_MSG_OPCODE_BASE + 0)

#define OAMS_CFG_GBH_FIRST_NSVC_ENABLED        (GBH_CFG_BASE_MSG_NUM + 1) /*OamsCfgGbhFirstNsvcEnabled*/
#define OAMS_CFG_GBH_LAST_NSVC_DISABLED        (GBH_CFG_BASE_MSG_NUM + 2) /*OamsCfgGbhLastNsvcDisabled*/
#define OAMS_GBH_CFG_ALARM_IND                 (GBH_CFG_BASE_MSG_NUM + 3) /*OamsGbhCfgAlarmInd*/
#define OAMS_CFG_GBH_SIG_BVC_RESET_FAILED      (GBH_CFG_BASE_MSG_NUM + 4) /*OamsCfgGbhSigBvcResetFailed*/
/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (GBH_CFG_BASE_MSG_NUM + 4) to (GBH_CFG_BASE_MSG_NUM + 10).
 */
#define GBH_CFG_LAST_MSG_NUM                   (GBH_CFG_BASE_MSG_NUM + 10)

/************************************************************************
OPCODES ASSOCIATED FOR MESSAGES BETWEEN CFG AND NSVCH
**************************************************************************/
#define NSVCH_CFG_BASE_MSG_NUM                 (GBH_CFG_LAST_MSG_NUM + 0)

#define OAMS_CFG_NSVCH_LOCK_REQ                (NSVCH_CFG_BASE_MSG_NUM + 1) /*OamsCfgNsvchUnlockReq*/
#define OAMS_CFG_NSVCH_UNLOCK_REQ              (NSVCH_CFG_BASE_MSG_NUM + 2) /*OamsCfgNsvchLockReq*/
#define OAMS_NSVCH_CFG_UNLOCK_RESP             (NSVCH_CFG_BASE_MSG_NUM + 3) /*OamsNsvchCfgUnlockResp*/
#define OAMS_NSVCH_CFG_LOCK_RESP               (NSVCH_CFG_BASE_MSG_NUM + 4) /*OamsNsvchCfgLockResp*/
#define OAMS_NSVCH_CFG_ALARM_IND               (NSVCH_CFG_BASE_MSG_NUM + 5) /*OamsNsvchCfgAlarmInd*/
/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (NSVCH_CFG_BASE_MSG_NUM + 6) to (NSVCH_CFG_BASE_MSG_NUM + 15).
 */
#define NSVCH_CFG_LAST_MSG_NUM                 (NSVCH_CFG_BASE_MSG_NUM + 10)

/************************************************************************
OPCODES ASSOCIATED FOR MESSAGES BETWEEN CFG AND PSCH
**************************************************************************/
#define PSCH_CFG_BASE_MSG_NUM                  (NSVCH_CFG_LAST_MSG_NUM + 0)

#define OAMS_CFG_PSCH_UNLOCK_REQ               (PSCH_CFG_BASE_MSG_NUM + 1) /*OamsCfgPschLockReq*/
#define OAMS_CFG_PSCH_LOCK_REQ                 (PSCH_CFG_BASE_MSG_NUM + 2) /*OamsCfgPschUnlockReq*/
#define OAMS_PSCH_CFG_UNLOCK_RESP              (PSCH_CFG_BASE_MSG_NUM + 3) /*OamsPschCfgUnlockResp*/
#define OAMS_PSCH_CFG_LOCK_RESP                (PSCH_CFG_BASE_MSG_NUM + 4) /*OamsPschCfgLockResp*/
#define OAMS_PSCH_CFG_ALARM_IND                (PSCH_CFG_BASE_MSG_NUM + 5) /*OamsPschCfgAlarmInd*/
#define OAMS_CFG_PSCH_SHUTDOWN_IND             (PSCH_CFG_BASE_MSG_NUM + 6) /*OamsCfgPschShutdownInd*/
#define OAMS_CFG_PSCH_CELL_BAR_ACCESS          (PSCH_CFG_BASE_MSG_NUM + 7) /*OamsCfgPschCellBarAccess*/
#define OAMS_CFG_PSCH_BVC_OP_FAILED            (PSCH_CFG_BASE_MSG_NUM + 8) /*OamsCfgPschBvcOpFailed*/
#define OAMS_CFG_PSCH_PTP_BVC_RESET            (PSCH_CFG_BASE_MSG_NUM + 9) /*OamsCfgPschPtpBvcReset*/

/*CFG-TB*/ 
#define OAMS_CFG_TBBSC_ADD_MLPPP_CONFIG        (PSCH_CFG_BASE_MSG_NUM + 10) /*OamsCfgPschPtpBvcReset*/
/* New Message Opcodes for this interface to be inserted here.
 * Available Opcodes: 
 * from (PSCH_CFG_BASE_MSG_NUM + 10) to (PSCH_CFG_BASE_MSG_NUM + 20).
 */
/* CS_PS_MERGING : 07-Mar-2012 START */
#define OAMS_CFG_PSCH_NSE_LOCK_REQ           (PSCH_CFG_BASE_MSG_NUM + 11) /*OamsCfgPschNseLockReq*///REQUIRED FOR R3-RAJU
#define OAMS_PSCH_CFG_NSE_LOCK_RESP           (PSCH_CFG_BASE_MSG_NUM + 12) /*OamsPschCfgNseLockResp*///REQUIRED FOR R3-RAJU
#define OAMS_CFG_PSCH_NSE_UPDATE_REQ           (PSCH_CFG_BASE_MSG_NUM + 13) /*OamsCfgPschNseUpdateReq*///REQUIRED FOR R3-RAJU
/* CS_PS_MERGING : 07-Mar-2012 END */
#define PSCH_CFG_LAST_MSG_NUM                  (PSCH_CFG_BASE_MSG_NUM + 20)

/*RRAL-TB*/ 
#define BASE_OPCODE_RRALTB                     (PSCH_CFG_LAST_MSG_NUM + 0)

#define PSAPP_TB_RRAL_DATA_IND                 (BASE_OPCODE_RRALTB + 1) /*PsappTbGrhmDataInd*/
#define CSAPP_RRAL_TB_DATA_REQ                 (BASE_OPCODE_RRALTB + 2) /*CsappGrhmTbDataReq*/

#define LAST_OPCODE_RRALTB                     (BASE_OPCODE_RRALTB + 10)

/*PSMSH-TB*/
#define BASE_OPCODE_PSMSHTB                    (LAST_OPCODE_RRALTB + 0)

#define PSAPP_PSMSH_TB_RTT_REQ                 (BASE_OPCODE_PSMSHTB + 1) /*PsappPsmshTbRttReq*/
#define PSAPP_TB_PSMSH_RTT_ACK                 (BASE_OPCODE_PSMSHTB + 2) /*PsappTbPsmshRttAck*/
#define PSAPP_TB_PSMSH_RTT_NACK                (BASE_OPCODE_PSMSHTB + 3) /*PsappTbPsmshRttNack*/
#define PSAPP_PSMSH_TB_DATA_REQ                (BASE_OPCODE_PSMSHTB + 4) /*PsappPsmshTbDataReq*/
#define PSAPP_TB_PSMSH_DATA_IND                (BASE_OPCODE_PSMSHTB + 5) /*PsappTbPsmshDataInd*/

#define LAST_OPCODE_PSMSHTB                    (BASE_OPCODE_PSMSHTB + 10)

/*TRXH-TB*/
#define BASE_OPCODE_TRXHTB                     (LAST_OPCODE_PSMSHTB + 0)

#define OAMS_TRXH_TB_ADD_BTS_TEI_MAPPING       (BASE_OPCODE_TRXHTB + 1) /*OamsTrxhTbAddBtsTeiMapping*/
#define OAMS_TRXH_TB_DEL_BTS_TEI_MAPPING       (BASE_OPCODE_TRXHTB + 2) /*OamsTrxhTbDelBtsTeiMapping*/

#define LAST_OPCODE_TRXHTB                     (BASE_OPCODE_TRXHTB + 10)

/*BTSH-TB*/
#define BASE_OPCODE_BTSHTB                     (LAST_OPCODE_TRXHTB + 0)

#define OAMS_BTSH_TB_ADD_BTS_IP                (BASE_OPCODE_BTSHTB + 1) /*OamsBichTbAddBtsIp*/
#define OAMS_BTSH_TB_DEL_BTS_IP                (BASE_OPCODE_BTSHTB + 2) /*OamsBichTbDelBtsIp*/
#define OAMS_BTSH_TB_IP_LINK_DOWN              (BASE_OPCODE_BTSHTB + 3) /*OamsBichTbIpLinkDown*/
#define PSAPP_TB_BTSH_IP_LINK_DOWN             (BASE_OPCODE_BTSHTB + 4) /*PsappTbBichIpLinkDown*/
#define PSAPP_TB_BTSH_IP_LINK_UP               (BASE_OPCODE_BTSHTB + 5) /*PsappTbBichIpLinkUp*/

#define LAST_OPCODE_BTSHTB                     (BASE_OPCODE_BTSHTB + 10)

/*NSVCH-FR*/
#define BASE_OPCODE_NSVCHFR                    (LAST_OPCODE_BTSHTB + 0)

#define OAMS_NSVCH_FR_N_START_REQ              (BASE_OPCODE_NSVCHFR +1) /*OamsNsvchFrNStartReq*/
#define OAMS_NSVCH_FR_N_STOP_REQ               (BASE_OPCODE_NSVCHFR +2) /*OamsNsvchFrNStopReq*/
#define PSSKS_FR_NSVCH_N_CONN_IND              (BASE_OPCODE_NSVCHFR +3) /*PssksFrNsvchNConnInd*/
#define PSSKS_FR_NSVCH_N_DISC_IND              (BASE_OPCODE_NSVCHFR +4) /*PssksFrNsvchNDiscInd*/
#define PSSKS_FR_NSVCH_N_STATUS_IND            (BASE_OPCODE_NSVCHFR +5) /*PssksFrNsvchNStatusIndv*/
#define PSSKS_FR_NSVCH_N_STOP_CNF              (BASE_OPCODE_NSVCHFR +6) /*PssksFrNsvchNStopCnf*/
#define LAST_OPCODE_NSVCHFR                    (BASE_OPCODE_NSVCHFR +10)

/*NSVCH-PSSCM*/
#define BASE_OPCODE_NSVCHPSSCM                 (LAST_OPCODE_NSVCHFR + 0)

#define OAMS_NSVCH_PSSCM_NSVC_DISABLED_IND     (BASE_OPCODE_NSVCHPSSCM + 1) /*OamsNsvchPsscmNsvcDisabledInd*/
#define OAMS_NSVCH_PSSCM_NSVC_ENABLED_IND      (BASE_OPCODE_NSVCHPSSCM + 2) /*OamsNsvchPsscmNsvcEnabledInd*/

#define LAST_OPCODE_NSVCHPSSCM                 (BASE_OPCODE_NSVCHPSSCM + 5)

#define PSSCM_PSCH_BASE_MSG_NUM                (LAST_OPCODE_NSVCHPSSCM + 0)

#define OAMS_PSCH_PSSCM_PROV_PTP_BVC           (PSSCM_PSCH_BASE_MSG_NUM + 1) /*OamsPschPsscmProvPtpBvc*/
#define OAMS_PSCH_PSSCM_UNPROV_PTP_BVC         (PSSCM_PSCH_BASE_MSG_NUM + 2) /*OamsPschPsscmUnprovPtpBvc*/
#define OAMS_PSSCM_PSCH_PROV_PTP_BVC_CNF       (PSSCM_PSCH_BASE_MSG_NUM + 3) /*OamsPsscmPschProvPtpBvcCnf*/
#define OAMS_PSSCM_PSCH_UNPROV_PTP_BVC_CNF     (PSSCM_PSCH_BASE_MSG_NUM + 4) /*OamsPsscmPschUnprovPtpBvcCnf*/

#define LAST_OPCODE_PSSCMPSCH                  (PSSCM_PSCH_BASE_MSG_NUM + 5)

/*GBH-PSSCM*/

#define GBH_PSCH_BASE_MSG_NUM                  (LAST_OPCODE_PSSCMPSCH + 0)

#define OAMS_GBH_PSCH_SIG_BVC_RESET_IND        (GBH_PSCH_BASE_MSG_NUM + 1) /*OamsGbhPschSigBvcResetInd*/
/* CS_PS_MERGING : 07-Mar-2012 START */
#define OAMS_GBH_PSCH_NSE_DOWN_IND              (GBH_PSCH_BASE_MSG_NUM + 2) /*OamsGbhPschNseDownInd*/
/*#define OAMS_GBH_PSCH_GB_DOWN_IND              (GBH_PSCH_BASE_MSG_NUM + 2)*/ /*OamsGbhPschGbDownInd*/
/* CS_PS_MERGING : 07-Mar-2012 END */

#define GBH_PSCH_LAST_MSG_NUM                  (GBH_PSCH_BASE_MSG_NUM + 5)

/*TRXH-PSCH*/
#define  TRXH_PSCH_BASE_MSG_NUM                (GBH_PSCH_LAST_MSG_NUM + 0)

#define  OAMS_TRXH_PSCH_PS_ALLOWED             (TRXH_PSCH_BASE_MSG_NUM + 1) /*OamsTrxhPschPsAllowed*/
#define  OAMS_TRXH_PSCH_PS_NOT_ALLOWED         (TRXH_PSCH_BASE_MSG_NUM + 2) /*OamsTrxhPschPsNotAllowed*/
#define  OAMS_PSCH_TRXH_PS_ATTR_CHANGE_IND     (TRXH_PSCH_BASE_MSG_NUM + 3) /*OamsPschTrxhPsAttrChangeInd*/

#define  TRXH_PSCH_LAST_MSG_NUM                (TRXH_PSCH_BASE_MSG_NUM + 5)

/*CELLH-PSCH*/
#define  CELLH_PSCH_BASE_MSG_NUM               (TRXH_PSCH_LAST_MSG_NUM + 0)

#define  OAMS_PSCH_CELLH_PS_CELL_ENABLED       (CELLH_PSCH_BASE_MSG_NUM + 1) /*OamsPschCellhPsCellEnabled*/
#define  OAMS_PSCH_CELLH_PS_CELL_DISABLED      (CELLH_PSCH_BASE_MSG_NUM + 2) /*OamsPschCellhPsCellDisabled*/

#define  CELLH_PSCH_LAST_MSG_NUM               (CELLH_PSCH_BASE_MSG_NUM + 5)


/*PSMSH-PSCH*/
#define  PSMSH_PSCH_BASE_MSG_NUM               (CELLH_PSCH_LAST_MSG_NUM + 0)

#define  OAMS_PSCH_PSMSH_DEL_CELL_BVC_MAP      (PSMSH_PSCH_BASE_MSG_NUM + 1) /*OamsPschPsmshDelCellBvcMap*/
#define  OAMS_PSCH_PSMSH_CRE_CELL_BVC_MAP      (PSMSH_PSCH_BASE_MSG_NUM + 2) /*OamsPschPsmshCreCellBvcMap*/

#define  PSMSH_PSCH_LAST_MSG_NUM               (PSMSH_PSCH_BASE_MSG_NUM + 5)

/*RRAL-PSCH*/
#define  RRAL_PSCH_BASE_MSG_NUM                (PSMSH_PSCH_LAST_MSG_NUM + 0)

#define  CSAPP_RRAL_PSCH_ACT_PDCH_IND          (RRAL_PSCH_BASE_MSG_NUM + 1) /*CsappGrhmPschActPdchInd*/
#define  OAMS_PSCH_RRAL_CRS_IND                (RRAL_PSCH_BASE_MSG_NUM + 2) /*OamsPschGrhmCrsInd*/

#define  RRAL_PSCH_LAST_MSG_NUM                (RRAL_PSCH_BASE_MSG_NUM + 5)


/* PSMSH-RRAL*/
#define PSMSH_RRAL_BASE_MSG_NUM                (RRAL_PSCH_LAST_MSG_NUM + 1)
#define PSAPP_PSMSH_RRAL_MS_RES_ALLOC_REQ      (PSMSH_RRAL_BASE_MSG_NUM + 1) /*PsappPsmshGrhmMsResAllocReq*/
#define CSAPP_RRAL_PSMSH_MS_RES_ALLOC_ACK      (PSMSH_RRAL_BASE_MSG_NUM + 2) /*CsappGrhmPsmshMsResAllocAck*/
#define CSAPP_RRAL_PSMSH_MS_RES_ALLOC_NACK     (PSMSH_RRAL_BASE_MSG_NUM + 3) /*CsappGrhmPsmshMsResAllocNack*/
#define PSAPP_PSMSH_RRAL_MS_EST_IND            (PSMSH_RRAL_BASE_MSG_NUM + 4) /*PsappPsmshGrhmMsEstInd*/
#define PSAPP_PSMSH_RRAL_MS_RESUME_REQ         (PSMSH_RRAL_BASE_MSG_NUM + 5) /*PsappPsmshGrhmMsResumeReq*/
#define CSAPP_RRAL_PSMSH_MS_RESUME_ACK         (PSMSH_RRAL_BASE_MSG_NUM + 6) /*CsappGrhmPsmshMsResumeAck*/
#define CSAPP_RRAL_PSMSH_MS_RESUME_NACK        (PSMSH_RRAL_BASE_MSG_NUM + 7) /*CsappGrhmPsmshMsResumeNack*/
#define PSAPP_PSMSH_RRAL_MS_REL_IND            (PSMSH_RRAL_BASE_MSG_NUM + 8) /*PsappPsmshGrhmMsRelInd*/
#define PSAPP_PSMSH_RRAL_MS_REL_ACK            (PSMSH_RRAL_BASE_MSG_NUM + 9) /*PsappPsmshGrhmMsRelAck*/
#define PSAPP_PSMSH_RRAL_MS_ABN_REL_IND        (PSMSH_RRAL_BASE_MSG_NUM + 10) /*PsappPsmshGrhmMsAbnRelInd*/
#define PSAPP_PSMSH_RRAL_MS_TBF_CLASS_IND      (PSMSH_RRAL_BASE_MSG_NUM + 11) /*PsappPsmshGrhmMsTbfClassInd*/
#define CSAPP_RRAL_PSMSH_MS_REORG_REQ          (PSMSH_RRAL_BASE_MSG_NUM + 12) /*CsappGrhmPsmshMsReorgReq*/
#define PSAPP_PSMSH_RRAL_MS_REORG_ACK          (PSMSH_RRAL_BASE_MSG_NUM + 13) /*PsappPsmshGrhmMsReorgAck*/
#define CSAPP_RRAL_PSMSH_MS_REL_REQ            (PSMSH_RRAL_BASE_MSG_NUM + 14) /*CsappGrhmPsmshMsRelReq*/
#define PSMSH_RRAL_LAST_MSG_NUM                (PSMSH_RRAL_BASE_MSG_NUM + 20)

/*PSMSH-ABIHM*/
#define PSMSH_ABIHM_BASE_MSG_NUM               (PSMSH_RRAL_LAST_MSG_NUM + 1)
#define CSAPP_ABIHM_PSMSH_CHANNEL_REQUIRED     (PSMSH_ABIHM_BASE_MSG_NUM + 1) /*CsappAbihmPsmshChanReq*/
#define CSAPP_ABIHM_PSMSH_DATA_IND             (PSMSH_ABIHM_BASE_MSG_NUM + 2) /*CsappAbihmPsmshDataInd*/
#define PSAPP_PSMSH_ABIHM_IMM_ASS_CMD          (PSMSH_ABIHM_BASE_MSG_NUM + 3) /*PsappPsmshAbihmImmAssCmd*/
#define PSMSH_ABIHM_LAST_MSG_NUM               (PSMSH_ABIHM_BASE_MSG_NUM + 5)

/*PSMSH-PHM*/
#define PSMSH_PHM_BASE_MSG_NUM                 (PSMSH_ABIHM_LAST_MSG_NUM + 1)
#define PSAPP_PSMSH_PHM_CS_PAGING_REQ          (PSMSH_PHM_BASE_MSG_NUM + 1) /*PsappPsmshPhmCsPagingReq*/
#define PSMSH_PHM_LAST_MSG_NUM                 (PSMSH_PHM_BASE_MSG_NUM + 5)

/*PSMSH-CELLH*/
#define PSMSH_CELLH_BASE_MSG_NUM               (PSMSH_PHM_LAST_MSG_NUM + 1)
#define OAMS_CELLH_PSMSH_ADD_BCCH_TRX_INFO     (PSMSH_CELLH_BASE_MSG_NUM + 1) /*OamsCellhPsmshAddBcchTrxInfo*/
#define OAMS_CELLH_PSMSH_DEL_BCCH_TRX_INFO     (PSMSH_CELLH_BASE_MSG_NUM + 2) /*OamsCellhPsmshDelBcchTrxInfo*/
#define PSMSH_CELLH_LAST_MSG_NUM               (PSMSH_CELLH_BASE_MSG_NUM + 5)

/*PSMSH-PDC*/
#define PSMSH_PDC_BASE_MSG_NUM                 (PSMSH_CELLH_LAST_MSG_NUM + 1)
#define OAM_PDC_PSMSH_PERF_DATA_REQ            (PSMSH_PDC_BASE_MSG_NUM + 1) /*OamPdcPsmshPerfDataReq*/
#define PSAPP_PSMSH_PDC_PERF_DATA_RESP         (PSMSH_PDC_BASE_MSG_NUM + 2) /*PsappPsmshPdcPerfDataResp*/
/* CS_PS_MERGING : 07-Mar-2012 START */
#define OAM_PDC_PSMSH_EGPRS_PERF_DATA_REQ       (PSMSH_PDC_BASE_MSG_NUM + 3) //OamPdcPsmshPerfDataReq
#define PSAPP_PSMSH_PDC_EGPRS_PERF_DATA_RESP    (PSMSH_PDC_BASE_MSG_NUM + 4) //PsappPsmshPdcPerfDataResp
/* CS_PS_MERGING : 07-Mar-2012 END */
#define PSMSH_PDC_LAST_MSG_NUM                 (PSMSH_PDC_BASE_MSG_NUM + 5)

/*PSMSH-CFG*/
#define PSMSH_CFG_BASE_MSG_NUM                 (PSMSH_PDC_LAST_MSG_NUM + 1)
#define OAMS_CFG_PSMSH_BSS_INFO_UPD_IND        (PSMSH_CFG_BASE_MSG_NUM + 1) /*OamsCfgPsmshBssInfoUpdInd*/
#define PSMSH_CFG_LAST_MSG_NUM                 (PSMSH_CFG_BASE_MSG_NUM + 5)

/*CELLH-RRAL*/
#define CELLH_RRAL_BASE_MSG_NUM                (PSMSH_CFG_LAST_MSG_NUM + 1)
#define OAMS_CELLH_RRAL_CRE_CELL_MAP_IND       (CELLH_RRAL_BASE_MSG_NUM + 1) /*OamsCellhGrhmCreCellMapInd*/
#define OAMS_CELLH_RRAL_DEL_CELL_MAP_IND       (CELLH_RRAL_BASE_MSG_NUM + 2) /*OamsCellhGrhmDelCellMapInd*/
#define OAMS_CELLH_RRAL_CRS_IND                (CELLH_RRAL_BASE_MSG_NUM + 4) /*OamsCellhGrhmCrsInd*/
#define OAMS_CELLH_RRAL_CSNEIGHCELLS_CHANGE    (CELLH_RRAL_BASE_MSG_NUM + 5) /*OamsCellhGrhmCrsInd*/
#define CELLH_RRAL_LAST_MSG_NUM                (CELLH_RRAL_BASE_MSG_NUM + 10)

/*ABIHM-PDC*/
#define ABIHM_PDC_BASE_MSG_NUM                 (CELLH_RRAL_LAST_MSG_NUM + 1)
#define OAM_PDC_ABIHM_PERF_DATA_REQ            (ABIHM_PDC_BASE_MSG_NUM + 1) /*OamPdcAbihmPerfDataReq*/
#define CSAPP_ABIHM_PDC_PERF_DATA_RESP         (ABIHM_PDC_BASE_MSG_NUM + 2) /*CsappAbihmPdcPerfDataResp*/
#define OAM_PDC_ABIHM_EGPRS_PERF_DATA_REQ            (ABIHM_PDC_BASE_MSG_NUM + 3) /*OamPdcAbihmEgrpsPerfDataReq*/
#define CSAPP_ABIHM_PDC_EGPRS_PERF_DATA_RESP         (ABIHM_PDC_BASE_MSG_NUM + 4) /*CsappAbihmPdcEgprsPerfDataResp*/
#define ABIHM_PDC_LAST_MSG_NUM                 (ABIHM_PDC_BASE_MSG_NUM + 5)

/*RRAL-RRALSTUB*/
#define RRAL_RRALSTUB_BASE_MSG_NUM             (ABIHM_PDC_LAST_MSG_NUM + 1)
#define EXEC_RRAL_UDC_IND                      (RRAL_RRALSTUB_BASE_MSG_NUM + 1) /*RralUdcInd*/
#define EXEC_RRALLIB_UDC_IND                   (RRAL_RRALSTUB_BASE_MSG_NUM + 2) /*RralUdcInd*/
#define RRAL_STUBRRAL_LAST_MSG_NUM             (RRAL_RRALSTUB_BASE_MSG_NUM + 5)

/*Changes PCU R2.5.1 --Start*/
/*RRAL-PDC*/
#define RRAL_PDC_BASE_MSG_NUM                  (RRAL_STUBRRAL_LAST_MSG_NUM + 1)
#define OAM_PDC_RRAL_PERF_DATA_REQ             (RRAL_PDC_BASE_MSG_NUM + 1) /*OamPdcGrhmPerfDataReq*/
#define CSAPP_RRAL_PDC_PERF_DATA_RESP          (RRAL_PDC_BASE_MSG_NUM + 2) /*PsappGrhmPdcPerfDataResp*/
#define RRAL_PDC_LAST_MSG_NUM                  (RRAL_PDC_BASE_MSG_NUM + 5)
  

#define BSC_RM_APPL_BASE                       (RRAL_PDC_LAST_MSG_NUM + 10)
#define OAMS_CELLH_RM_READY                    (BSC_RM_APPL_BASE + 1)
#define OAMS_TRXH_RM_READY                     (BSC_RM_APPL_BASE + 2)
#define CSAPP_RRAL_RM_READY                    (BSC_RM_APPL_BASE + 3)
#define CSAPP_MRHM_RM_READY                    (BSC_RM_APPL_BASE + 4)
#define CSAPP_PHM_RM_READY                     (BSC_RM_APPL_BASE + 5)
#define CSAPP_CPHM_RM_READY                    (BSC_RM_APPL_BASE + 6)
#define CSAPP_ABIHM_RM_READY                   (BSC_RM_APPL_BASE + 7)
#define CSAPP_AIFDHM_RM_READY                  (BSC_RM_APPL_BASE + 8)

#define OAMS_RM_CELLH_ACTIVE_IND               (BSC_RM_APPL_BASE + 9)
#define OAMS_RM_TRXH_ACTIVE_IND                (BSC_RM_APPL_BASE + 10)
#define OAMS_RM_RRAL_ACTIVE_IND                (BSC_RM_APPL_BASE + 11)
#define OAMS_RM_MRHM_ACTIVE_IND                (BSC_RM_APPL_BASE + 12)
#define OAMS_RM_PHM_ACTIVE_IND                 (BSC_RM_APPL_BASE + 13)
#define OAMS_RM_CPHM_ACTIVE_IND                (BSC_RM_APPL_BASE + 14)
#define OAMS_RM_ABIHM_ACTIVE_IND               (BSC_RM_APPL_BASE + 15)
#define OAMS_RM_AIFDHM_ACTIVE_IND              (BSC_RM_APPL_BASE + 16)
#define OAMS_RM_TRXH_START_OAM_HA_REQ          (BSC_RM_APPL_BASE + 17)
#define OAMS_RM_CPHM_START_CALL_HA_REQ         (BSC_RM_APPL_BASE + 18)
#define OAMS_TRXH_RM_START_OAM_HA_RESP         (BSC_RM_APPL_BASE + 19)
#define CSAPP_CPHM_RM_START_CALL_HA_RESP       (BSC_RM_APPL_BASE + 20)
#define BSC_RM_APPL_LAST_MSG_NUM               (BSC_RM_APPL_BASE + 25)

/*RRAL - MPHM Interface */
#define CSAPP_RRAL_MPHM_BASE_MSG_NUM               (BSC_RM_APPL_LAST_MSG_NUM + 10)
#define CSAPP_RRAL_MPHM_CRE_CALL_CONTEXT_REQ       (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 0)
#define CSAPP_RRAL_MPHM_MOD_CALL_CONTEXT_REQ       (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 1)
#define CSAPP_RRAL_MPHM_MOD_CALL_CONTEXT_COMP_REQ  (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 2)
#define CSAPP_RRAL_MPHM_REL_CALL_CONTEXT_REQ       (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 3)
#define CSAPP_MPHM_RRAL_RESET_CALL_CONTEXT_IND     (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 4)
#define CSAPP_RRAL_MPHM_CKT_SWAP_REQ               (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 5)
#define CSAPP_MPHM_RRAL_CRE_CALL_CONTEXT_RESP      (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 6)
#define CSAPP_MPHM_RRAL_MOD_CALL_CONTEXT_RESP      (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 7)
#define CSAPP_MPHM_RRAL_MOD_CALL_CONTEXT_CMP_RESP  (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 8)
#define CSAPP_MPHM_RRAL_CKT_SWAP_RESP              (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 9)
#define CSAPP_MPHM_RRAL_REL_CALL_CONTEXT_RESP      (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 10)
#define CSAPP_MPHM_RRAL_MEDIA_PLANE_DOWN_IND       (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 11)
#define CSAPP_MPHM_RRAL_MEDIA_RESOURCE_STATUS_REQ  (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 12)
#define CSAPP_RRAL_MEDIA_RESOURCE_STATUS_RESP      (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 13)
#define CSAPP_RRAL_MPHM_RESET_CALL_CONTEXT_IND     (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 14)


#define MPHM_MEDIA_PLANE_CONNECT_REQ               (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 15)
#define MPHM_MEDIA_PLANE_AUDIT_REQ                 (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 16)
#define MPHM_MEDIA_PLANE_AUDIT_RESP                (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 17)
#define MPHM_MEDIA_PLANE_AUDIT_FAILURE             (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 18)
#define MPHM_MEDIA_PLANE_CONNECT_RESP              (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 19)

#define OAM_RRAL_MPHM_LAST_MSG_NUM                 (CSAPP_RRAL_MPHM_BASE_MSG_NUM + 30)

/*IFML - MPHM  */


#define CSAPP_IFML_MPHM_BASE_MSG_NUM               (OAM_RRAL_MPHM_LAST_MSG_NUM + 0)
#define CSAPP_MPHM_IFML_MEDIA_RESOURCE_STATUS_REQ  (CSAPP_IFML_MPHM_BASE_MSG_NUM+1)
#define OAMS_IFML_MPHM_MEDIA_RESOURCE_STATUS_RESP  (CSAPP_IFML_MPHM_BASE_MSG_NUM+2)
#define CSAPP_MPHM_IFML_CIC_BLOCK_REQ              (CSAPP_IFML_MPHM_BASE_MSG_NUM+3)
#define OAMS_IFML_MPHM_CIC_BLOCK_RESP              (CSAPP_IFML_MPHM_BASE_MSG_NUM+4)
#define CSAPP_MPHM_IFML_CIC_UNBLOCK_REQ            (CSAPP_IFML_MPHM_BASE_MSG_NUM+5)
#define OAMS_IFML_MPHM_CIC_UNBLOCK_RESP            (CSAPP_IFML_MPHM_BASE_MSG_NUM+6)
#define CSAPP_MPHM_IFML_CIC_CONFIG_REQ             (CSAPP_IFML_MPHM_BASE_MSG_NUM+7)
#define OAMS_IFML_MPHM_CIC_CONFIG_RESP             (CSAPP_IFML_MPHM_BASE_MSG_NUM+8)
#define OAMS_IFML_MPHM_CIC_STATUS_ENQUIRY_REQ      (CSAPP_IFML_MPHM_BASE_MSG_NUM+9)
#define CSAPP_MPHM_IFML_CIC_STATUS_ENQUIRY_RESP    (CSAPP_IFML_MPHM_BASE_MSG_NUM+10)
#define OAMS_IFML_MPHM_INITIATE_RESET_IND          (CSAPP_IFML_MPHM_BASE_MSG_NUM+11)

#define OAMS_IFML_RRAL_INITIATE_BPC_RELEASE        (CSAPP_IFML_MPHM_BASE_MSG_NUM+12)            
#define CSAPP_RRAL_IFML_UPD_RESOURCE_STATUS_IND    (CSAPP_IFML_MPHM_BASE_MSG_NUM+13)
#define CSAPP_CPHM_IFML_CKT_RESET                  (CSAPP_IFML_MPHM_BASE_MSG_NUM+14) /*CsappCphmIfmlCktReset*/

#define OAM_IFML_MPHM_LAST_MSG_NUM                 (CSAPP_IFML_MPHM_BASE_MSG_NUM + 30)

#define OAM_PDD_CFG_BASE_MSG_NUM                   (OAM_IFML_MPHM_LAST_MSG_NUM + 10)
/* Start Changes for Diagnostics*/

#define OAM_PDD_CFG_FTP_START                      (OAM_PDD_CFG_BASE_MSG_NUM + 0) 
#define OAM_PDD_CFG_LAST_MSG_NUM                   (OAM_PDD_CFG_FTP_START + 10) 

/*Added to trigger ind for CFG after Switchover */
/* End Changes for Diagnostics*/

/* Change Start: R3-BSC
   Dated: 3-Aug-2011
*/

/* 
  ABIHM - ABISD 
*/

#define CSAPP_ABIHM_ABISD_BASE_MSG_NUM         (OAM_PDD_CFG_LAST_MSG_NUM + 0)
#define CSAPP_ABIHM_ABISD_DATA_REQ             (CSAPP_ABIHM_ABISD_BASE_MSG_NUM + 1)
#define CSAPP_ABIHM_ABISD_ASSOC_DISC_REQ       (CSAPP_ABIHM_ABISD_BASE_MSG_NUM + 2)
#define CSAPP_ABIHM_ABISD_TRX_DEL_IND          (CSAPP_ABIHM_ABISD_BASE_MSG_NUM + 3) 
#define CSAPP_ABIHM_ABISD_BTS_DEL_IND          (CSAPP_ABIHM_ABISD_BASE_MSG_NUM + 4)
#define CSAPP_ABIHM_ABISD_TRX_ADD_IND          (CSAPP_ABIHM_ABISD_BASE_MSG_NUM + 5) 
#define CSAPP_ABIHM_ABISD_BTS_ADD_IND          (CSAPP_ABIHM_ABISD_BASE_MSG_NUM + 6)

#define CSAPP_ABIHM_ABISD_LAST_MSG_NUM         (CSAPP_ABIHM_ABISD_BASE_MSG_NUM + 20)
/*
  ABISD - ABIHM
*/

#define CSAPP_ABISD_ABIHM_BASE_MSG_NUM         (CSAPP_ABIHM_ABISD_LAST_MSG_NUM + 0)
#define CSAPP_ABISD_ABIHM_DATA_IND             (CSAPP_ABISD_ABIHM_BASE_MSG_NUM + 1)
#define CSAPP_ABISD_ABIHM_IP_LINK_UP_IND       (CSAPP_ABISD_ABIHM_BASE_MSG_NUM + 2) 
#define CSAPP_ABISD_ABIHM_IP_LINK_DOWN_IND     (CSAPP_ABISD_ABIHM_BASE_MSG_NUM + 3)
#define CSAPP_ABISD_ABIHM_PROC_UP_IND          (CSAPP_ABISD_ABIHM_BASE_MSG_NUM + 4)
 
#define CSAPP_ABISD_ABIHM_LAST_MSG_NUM         (CSAPP_ABISD_ABIHM_BASE_MSG_NUM + 20)

/*
  START : CFG - MPHM
*/
#define CFG_MPHM_BASE_MSG_NUM         				  (CSAPP_ABISD_ABIHM_LAST_MSG_NUM + 0)
#define CSAPP_MPHM_CFG_MEDIA_CIC_CONFIG_REQ     (CFG_MPHM_BASE_MSG_NUM + 1)
#define OAMS_CFG_MPHM_MEDIA_CIC_CONFIG_RESP     (CFG_MPHM_BASE_MSG_NUM + 2) 
#define OAMS_CFG_MPHM_ADMIN_STATE_CHANGE_REQ    (CFG_MPHM_BASE_MSG_NUM + 3) 
#define CSAPP_MPHM_CFG_ADMIN_STATE_CHANGE_RESP  (CFG_MPHM_BASE_MSG_NUM + 4)
#define OAMS_CFG_MPHM_MTP2_ALLOC_HDLC_REQ       (CFG_MPHM_BASE_MSG_NUM + 5)
#define OAMS_CFG_MPHM_MLPPP_ALLOC_HDLC_REQ      (CFG_MPHM_BASE_MSG_NUM + 6)
#define OAMS_CFG_MPHM_FR_ALLOC_HDLC_REQ         (CFG_MPHM_BASE_MSG_NUM + 7)
#define CSAPP_MPHM_CFG_MTP2_ALLOC_HDLC_RESP     (CFG_MPHM_BASE_MSG_NUM + 8)
#define CSAPP_MPHM_CFG_MLPPP_ALLOC_HDLC_RESP    (CFG_MPHM_BASE_MSG_NUM + 9)
#define CSAPP_MPHM_CFG_FR_ALLOC_HDLC_RESP       (CFG_MPHM_BASE_MSG_NUM + 10)
#define OAMS_CFG_MPHM_MTP2_DEALLOC_HDLC_REQ     (CFG_MPHM_BASE_MSG_NUM + 11)
#define OAMS_CFG_MPHM_MLPPP_DEALLOC_HDLC_REQ    (CFG_MPHM_BASE_MSG_NUM + 12)
#define OAMS_CFG_MPHM_FR_DEALLOC_HDLC_REQ       (CFG_MPHM_BASE_MSG_NUM + 13)
#define CSAPP_MPHM_CFG_MTP2_DEALLOC_HDLC_RESP   (CFG_MPHM_BASE_MSG_NUM + 14)
#define CSAPP_MPHM_CFG_MLPPP_DEALLOC_HDLC_RESP  (CFG_MPHM_BASE_MSG_NUM + 15)
#define CSAPP_MPHM_CFG_FR_DEALLOC_HDLC_RESP     (CFG_MPHM_BASE_MSG_NUM + 16)
#define CSAPP_MPHM_CFG_MEDIA_PLANE_INIT_IND     (CFG_MPHM_BASE_MSG_NUM + 17)
 
#define CFG_MPHM_LAST_MSG_NUM                   (CFG_MPHM_BASE_MSG_NUM + 20)
/*
  END : CFG - MPHM
*/
/*Change End: R3-BSC
  Dated: 3-Aug-2011
*/

/*#define BSC_TABLE_API_BASE                     (CFG_MPHM_LAST_MSG_NUM + 0) commented on 28dec2011 by BSC-CS team*/

/* Change Start: R3-BSC
   Dated: 20-Sep-2011
*/

#define CSAPP_ABISD_INTF_BASE_MSG_NUM         (CFG_MPHM_LAST_MSG_NUM + 0)
#define CSAPP_ABISD_INTF_IP_LINK_UP_IND       (CSAPP_ABISD_INTF_BASE_MSG_NUM + 1)
#define CSAPP_ABISD_INTF_IP_LINK_DOWN_IND     (CSAPP_ABISD_INTF_BASE_MSG_NUM + 2)


#define CSAPP_ABISD_INTF_LAST_MSG_NUM         (CSAPP_ABISD_INTF_BASE_MSG_NUM + 10)


/* Change End: R3-BSC
   Dated: 20-Sep-2011
*/

/*  Added for new Object model  */
/***********************************************************************/

/*****************************************************************
PM <---> CFGM     (26-09-2011)  BASE_OPCODE_PM
*****************************************************************/
/*** Opcodes at Interface between OAM and Platform start ***/


#define OAM_MWD_QUERY_TYPE_BASE                           (CSAPP_ABISD_INTF_LAST_MSG_NUM)

/*Queries*/

#define QUERY_GET_CHASSIS_DISK_INFO_OAM_PM                (OAM_MWD_QUERY_TYPE_BASE + 0)
#define QUERY_GET_DISK_STATUS_OAM_PM                      (OAM_MWD_QUERY_TYPE_BASE + 1)
#define QUERY_SET_DISK_THRESHOLD_OAM_PM                   (OAM_MWD_QUERY_TYPE_BASE + 2)
#define QUERY_SET_SYS_INTERFACE_IP_OAM_PM                 (OAM_MWD_QUERY_TYPE_BASE + 3)
#define QUERY_GET_SYS_INTERFACE_IP_OAM_PM                 (OAM_MWD_QUERY_TYPE_BASE + 4)
#define QUERY_SET_CLK_OAM_PM                              (OAM_MWD_QUERY_TYPE_BASE + 5)
#define QUERY_SYS_CLOCK_DETAILS_OAM_PM                    (OAM_MWD_QUERY_TYPE_BASE + 6)
#define QUERY_START_UPGRADE_OFFER_OAM_PM                  (OAM_MWD_QUERY_TYPE_BASE + 7)
#define QUERY_ACTIVATE_OAM_PM                             (OAM_MWD_QUERY_TYPE_BASE + 8)
#define QUERY_GET_CARD_RELEASE_INFO_OAM_PM                (OAM_MWD_QUERY_TYPE_BASE + 9)
#define QUERY_GET_SYSTEM_RELEASE_INFO_OAM_PM              (OAM_MWD_QUERY_TYPE_BASE + 10)
#define QUERY_SET_TRUNK_PORT_VARS_OAM_PM                  (OAM_MWD_QUERY_TYPE_BASE + 11)
#define QUERY_GET_SYSTEM_DETAILS_OAM_PM                   (OAM_MWD_QUERY_TYPE_BASE + 12)
#define QUERY_GET_TRUNK_PORT_STATUS_OAM_PM                (OAM_MWD_QUERY_TYPE_BASE + 13)
#define QUERY_GET_CHASSIS_TRUNK_PORT_STATUS_OAM_PM        (OAM_MWD_QUERY_TYPE_BASE + 14)
#define QUERY_LOCK_BLADE_OAM_PM                           (OAM_MWD_QUERY_TYPE_BASE + 15)
#define QUERY_RESET_OAM_PM                                (OAM_MWD_QUERY_TYPE_BASE + 16)
#define QUERY_GET_FRU_INFO_OAM_PM                         (OAM_MWD_QUERY_TYPE_BASE + 17)
#define QUERY_UNLOCK_BLADE_OAM_PM                         (OAM_MWD_QUERY_TYPE_BASE + 18)
#define QUERY_SET_SYS_TIME_OAM_PM                         (OAM_MWD_QUERY_TYPE_BASE + 19)
#define QUERY_SET_MEDIA_INTERFACE_IP_OAM_PM               (OAM_MWD_QUERY_TYPE_BASE + 20)
#define QUERY_GET_MEDIA_INTERFACE_IP_OAM_PM               (OAM_MWD_QUERY_TYPE_BASE + 21)
#define QUERY_SET_NEIP_VARS_OAM_PM                        (OAM_MWD_QUERY_TYPE_BASE + 22)
#define QUERY_GET_NEIP_DETAILS_OAM_PM                     (OAM_MWD_QUERY_TYPE_BASE + 23)
/* Added on 19-03-2013 */
#define QUERY_GET_PERFORMANCE_COUNTER_OAM_PM							(OAM_MWD_QUERY_TYPE_BASE + 24)



#define OAM_MWD_QUERY_ACK_TYPE_BASE                       (OAM_MWD_QUERY_TYPE_BASE + 30)


/*Query Ack*/
#define QUERY_ACK_GET_CHASSIS_DISK_INFO_PM_OAM                  (OAM_MWD_QUERY_ACK_TYPE_BASE + 0)
#define QUERY_ACK_GET_DISK_STATUS_PM_OAM                        (OAM_MWD_QUERY_ACK_TYPE_BASE + 1)
#define QUERY_ACK_SET_DISK_THRESHOLD_PM_OAM                     (OAM_MWD_QUERY_ACK_TYPE_BASE + 2)
#define QUERY_ACK_SET_SYS_INTERFACE_IP_PM_OAM                   (OAM_MWD_QUERY_ACK_TYPE_BASE + 3)
#define QUERY_ACK_GET_SYS_INTERFACE_IP_PM_OAM                   (OAM_MWD_QUERY_ACK_TYPE_BASE + 4)
#define QUERY_ACK_SET_CLK_PM_OAM                                (OAM_MWD_QUERY_ACK_TYPE_BASE + 5)
#define QUERY_ACK_SYS_CLOCK_DETAILS_PM_OAM                      (OAM_MWD_QUERY_ACK_TYPE_BASE + 6)
#define QUERY_ACK_START_UPGRADE_OFFER_PM_OAM                    (OAM_MWD_QUERY_ACK_TYPE_BASE + 7)
#define QUERY_ACK_ACTIVATE_PM_OAM                               (OAM_MWD_QUERY_ACK_TYPE_BASE + 8)
#define QUERY_ACK_GET_CARD_RELEASE_INFO_PM_OAM                  (OAM_MWD_QUERY_ACK_TYPE_BASE + 9)
#define QUERY_ACK_GET_SYSTEM_RELEASE_INFO_PM_OAM                (OAM_MWD_QUERY_ACK_TYPE_BASE + 10)
#define QUERY_ACK_SET_TRUNK_PORT_VARS_PM_OAM                    (OAM_MWD_QUERY_ACK_TYPE_BASE + 11)
#define QUERY_ACK_GET_SYSTEM_DETAILS_PM_OAM                     (OAM_MWD_QUERY_ACK_TYPE_BASE + 12)
#define QUERY_ACK_GET_TRUNK_PORT_STATUS_PM_OAM                  (OAM_MWD_QUERY_ACK_TYPE_BASE + 13)
#define QUERY_ACK_GET_CHASSIS_TRUNK_PORT_STATUS_PM_OAM          (OAM_MWD_QUERY_ACK_TYPE_BASE + 14)
#define QUERY_ACK_LOCK_BLADE_PM_OAM                             (OAM_MWD_QUERY_ACK_TYPE_BASE + 15)
#define QUERY_ACK_RESET_PM_OAM                                  (OAM_MWD_QUERY_ACK_TYPE_BASE + 16)
#define QUERY_ACK_GET_FRU_INFO_PM_OAM                           (OAM_MWD_QUERY_ACK_TYPE_BASE + 17)
#define QUERY_ACK_UNLOCK_BLADE_PM_OAM                           (OAM_MWD_QUERY_ACK_TYPE_BASE + 18)
#define QUERY_ACK_SET_SYS_TIME_PM_OAM                           (OAM_MWD_QUERY_ACK_TYPE_BASE + 19)
#define QUERY_ACK_SET_MEDIA_INTERFACE_IP_PM_OAM                 (OAM_MWD_QUERY_ACK_TYPE_BASE + 20)
#define QUERY_ACK_GET_MEDIA_INTERFACE_IP_PM_OAM                 (OAM_MWD_QUERY_ACK_TYPE_BASE + 21)
#define QUERY_ACK_SET_NEIP_VARS_PM_OAM                          (OAM_MWD_QUERY_ACK_TYPE_BASE + 22)
#define QUERY_ACK_GET_NEIP_DETAILS_PM_OAM                       (OAM_MWD_QUERY_ACK_TYPE_BASE + 23)
#define QUERY_ACK_GET_PERFORMANCE_COUNTER_PM_OAM								(OAM_MWD_QUERY_ACK_TYPE_BASE + 24)

#define OAM_MWD_QUERY_ACK_TYPE_LAST_MSG_NUM                     (OAM_MWD_QUERY_ACK_TYPE_BASE + 30)


/* Opcodes at interface between CFGM and Platform ends */

/* BSC CONTROL - MEDIA Message  Exception*/
#define CSAPP_MPHM_MEDIA_BASE_MSG_NUM                           0x4000 
#define CONTROL_MEDIA_MSG_CALL_MGMT                             (CSAPP_MPHM_MEDIA_BASE_MSG_NUM + 1)
#define CONTROL_MEDIA_MSG_OAM                                   (CSAPP_MPHM_MEDIA_BASE_MSG_NUM + 2)
#define CONTROL_MEDIA_MSG_SIGNALLING                            (CSAPP_MPHM_MEDIA_BASE_MSG_NUM + 3)
#define CONTROL_MEDIA_MSG                                       (CSAPP_MPHM_MEDIA_BASE_MSG_NUM + 4)
#define CSAPP_MPHM_MEDIA_LAST_MSG_NUM                           (CSAPP_MPHM_MEDIA_BASE_MSG_NUM + 10)

/* end here */
#define OAMS_CFG_CFG_BASE_MSG_NUM                               (CSAPP_MPHM_MEDIA_LAST_MSG_NUM + 1)
#define OAMS_CFG_CFG_SRVC_INST_UP_IND                           (OAMS_CFG_CFG_BASE_MSG_NUM     + 2)
#define OAMS_CFG_CFG_SRVC_INST_DOWN_IND                         (OAMS_CFG_CFG_BASE_MSG_NUM     + 3)
/*Added on 10-05-2012 Start */
#define OAMS_CFG_CFG_MED_SRVC_INST_UP_IND                       (OAMS_CFG_CFG_BASE_MSG_NUM     + 4)
#define OAMS_CFG_CFG_MED_SRVC_INST_DOWN_IND                     (OAMS_CFG_CFG_BASE_MSG_NUM     + 5)
/*Added on 10-05-2012 Ends  */
#define OAMS_CFG_CFG_LAST_MSG_NUM                               (OAMS_CFG_CFG_BASE_MSG_NUM     + 6)

/**********************ADDED on 17th Jan. for ABISD and PS Interface****** Start********************/
/*ABISD -> RELAY/PSMSH Interface Added on 17th Jan. 2012*/
#define CSAPP_ABISD_PSINTF_BASE_MSG_NUM                         (OAMS_CFG_CFG_LAST_MSG_NUM + 0)
#define CSAPP_ABISD_RELAY_IP_LINK_UP_IND                        (CSAPP_ABISD_PSINTF_BASE_MSG_NUM + 1)
#define CSAPP_ABISD_RELAY_IP_LINK_DOWN_IND                      (CSAPP_ABISD_PSINTF_BASE_MSG_NUM + 2)
#define CSAPP_ABISD_RELAY_DATA_IND                              (CSAPP_ABISD_PSINTF_BASE_MSG_NUM + 3)
#define CSAPP_ABISD_PSMSH_DATA_IND                              (CSAPP_ABISD_PSINTF_BASE_MSG_NUM + 4)
#define CSAPP_ABISD_PSMSH_RTT_ACK                               (CSAPP_ABISD_PSINTF_BASE_MSG_NUM + 5)
#define CSAPP_ABISD_PSMSH_RTT_NACK                              (CSAPP_ABISD_PSINTF_BASE_MSG_NUM + 6)
#define CSAPP_ABISD_RELAY_LAST_MSG_NUM                          (CSAPP_ABISD_PSINTF_BASE_MSG_NUM + 30)

/*RELAY/PSMSH -> ABISD Interface Added on 17th Jan. 2012*/
#define PSAPP_PSINTF_ABISD_BASE_MSG_NUM                         (CSAPP_ABISD_RELAY_LAST_MSG_NUM  + 0)
#define PSAPP_RELAY_ABISD_DATA_REQ                              (PSAPP_PSINTF_ABISD_BASE_MSG_NUM + 1)
#define PSAPP_PSMSH_ABISD_DATA_REQ                              (PSAPP_PSINTF_ABISD_BASE_MSG_NUM + 2)
#define PSAPP_PSMSH_ABISD_RTT_REQ                               (PSAPP_PSINTF_ABISD_BASE_MSG_NUM + 3)

#define PSAPP_PSINTF_ABISD_LAST_MSG_NUM                         (PSAPP_PSINTF_ABISD_BASE_MSG_NUM + 30)
/**********************ADDED on 17th Jan. for ABISD and PS Interface****** Ends*********************/

/**********************ADDED on 18th Jan. for ABIHM and RRAL Interface****** Start******************/
/*ABIHM -> RRAL Interface Added on 18th Jan. 2012*/
#define CSAPP_ABIHM_RRAL_BASE_MSG_NUM                           (PSAPP_PSINTF_ABISD_LAST_MSG_NUM + 0)
#define CSAPP_ABIHM_RRAL_PDCH_ACT_ACK                           (CSAPP_ABIHM_RRAL_BASE_MSG_NUM   + 1)
#define CSAPP_ABIHM_RRAL_PDCH_ACT_NACK                          (CSAPP_ABIHM_RRAL_BASE_MSG_NUM   + 2)
#define CSAPP_ABIHM_RRAL_PDCH_DEACT_ACK                         (CSAPP_ABIHM_RRAL_BASE_MSG_NUM   + 3)
#define CSAPP_ABIHM_RRAL_PDCH_DEACT_NACK                        (CSAPP_ABIHM_RRAL_BASE_MSG_NUM   + 4)
#define CSAPP_ABIHM_RRAL_RF_RESOURCE_IND                        (CSAPP_ABIHM_RRAL_BASE_MSG_NUM   + 5)
#define CSAPP_ABIHM_RRAL_LAST_MSG_NUM                           (CSAPP_ABIHM_RRAL_BASE_MSG_NUM   + 15)
/*RRAL -> ABIHM Interface Added on 18th Jan. 2012*/
#define CSAPP_RRAL_ABIHM_BASE_MSG_NUM                           (CSAPP_ABIHM_RRAL_LAST_MSG_NUM   + 0)
#define CSAPP_RRAL_ABIHM_PDCH_ACT_REQ                           (CSAPP_RRAL_ABIHM_BASE_MSG_NUM   + 1)
#define CSAPP_RRAL_ABIHM_PDCH_DEACT_REQ                         (CSAPP_RRAL_ABIHM_BASE_MSG_NUM   + 2) 
#define CSAPP_RRAL_ABIHM_LAST_MSG_NUM                           (CSAPP_RRAL_ABIHM_BASE_MSG_NUM   + 15)
/**********************ADDED on 18th Jan. for ABIHM and RRAL Interface****** Ends*******************/

/* CS_PS_MERGING : 07-Mar-2012 START */
/************************************ADDED on 25th Jan. for PSMSH and RELAY Interface********Starts*****/
/* PSMSH ->RELAY Interface Added on 25th Jan. 2012 */
#define PSAPP_PSMSH_RELAY_BASE_MSG_NUM               (CSAPP_RRAL_ABIHM_LAST_MSG_NUM + 0)

#define PSAPP_PSMSH_RELAY_CRE_MS_CTXT                (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 1)
#define PSAPP_PSMSH_RELAY_DEL_MS_CTXT                (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 2)
#define PSAPP_PSMSH_RELAY_MS_EST_TRIG_ACK            (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 3)
#define PSAPP_PSMSH_RELAY_MS_RE_EST_ACK              (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 4)
#define PSAPP_PSMSH_RELAY_MERGE_MS_CTXT              (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 5)
#define PSAPP_PSMSH_RELAY_MS_RESUME_FAILED           (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 6)
#define PSAPP_PSMSH_RELAY_MS_RESUME_ACK              (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 7)
#define PSAPP_PSMSH_RELAY_LAST_MSG_NUM               (PSAPP_PSMSH_RELAY_BASE_MSG_NUM + 15)
 
/*RELAY -> PSMSH Interface Added on 25th Jan. 2012*/
#define PSAPP_RELAY_PSMSH_BASE_MSG_NUM               (PSAPP_PSMSH_RELAY_LAST_MSG_NUM + 0)
#define PSAPP_RELAY_PSMSH_UPD_TLLI_INDEX             (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 1)
#define PSAPP_RELAY_PSMSH_MS_EST_TRIG                (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 2)
#define PSAPP_RELAY_PSMSH_MS_RE_EST_REQ              (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 3)
#define PSAPP_RELAY_PSMSH_MS_REL_IND                 (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 4)
#define PSAPP_RELAY_PSMSH_MS_ABN_REL_IND             (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 5)
#define PSAPP_RELAY_PSMSH_MS_REL_REQ                 (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 6)
#define PSAPP_RELAY_PSMSH_FLUSH_LL                   (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 7)
#define PSAPP_RELAY_PSMSH_GPRS_SUSPEND_REQ           (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 8)
#define PSAPP_RELAY_PSMSH_TLLI_REASS_IND             (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 9)
#define PSAPP_RELAY_PSMSH_MS_RESUME_IND              (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 10)
#define PSAPP_RELAY_PSMSH_MS_RESUME_FAILED_ACK       (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 11)
#define PSAPP_RELAY_PSMSH_MS_REL_TLLI_REASS          (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 12)
#define PSAPP_RELAY_PSMSH_DEL_MS_CTXT_RESP           (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 13)
#define PSAPP_RELAY_PSMSH_LAST_MSG_NUM               (PSAPP_RELAY_PSMSH_BASE_MSG_NUM + 20)
/************************************ADDED on 25th Jan. for PSMSH and RELAY Interface********Ends******/

/************************************ADDED on 25th Jan. for RRAL and RELAY Interface********Starts*****/
/* RRAL -> RELAY Interface Added on 25th Jan. 2012 */
#define CSAPP_RRAL_RELAY_BASE_MSG_NUM               (PSAPP_RELAY_PSMSH_LAST_MSG_NUM + 0)

#define CSAPP_RRAL_RELAY_MS_REL_REQ                 (CSAPP_RRAL_RELAY_BASE_MSG_NUM + 1)
#define CSAPP_RRAL_RELAY_LAST_MSG_NUM               (CSAPP_RRAL_RELAY_BASE_MSG_NUM + 5)

/* ABIHM - RELAY */
#define RELAY_ABIHM_BASE_MSG_NUM                 (CSAPP_RRAL_RELAY_LAST_MSG_NUM + 10)

#define CSAPP_ABIHM_RELAY_DATA_IND               (RELAY_ABIHM_BASE_MSG_NUM + 0) //CsappAbihmRelayDataInd

#define RELAY_ABIHM_LAST_MSG_NUM                 (RELAY_ABIHM_BASE_MSG_NUM + 5)

/* PSCH - RELAY */
#define  RELAY_PSCH_BASE_MSG_NUM                 (RELAY_ABIHM_LAST_MSG_NUM + 10)

#define  OAMS_PSCH_RELAY_DEL_CELL_BVC_MAP        (RELAY_PSCH_BASE_MSG_NUM + 0) //OamsPschRelayDelCellBvcMap
#define  OAMS_PSCH_RELAY_CRE_CELL_BVC_MAP        (RELAY_PSCH_BASE_MSG_NUM + 1) //OamsPschRelayCreCellBvcMap
#define  OAMS_PSCH_RELAY_DEL_BTS_TEI_MAPPING     (RELAY_PSCH_BASE_MSG_NUM + 2) //OamsPschRelayDelBtsTeiMapping
#define  OAMS_PSCH_RELAY_ADD_BTS_TEI_MAPPING     (RELAY_PSCH_BASE_MSG_NUM + 3) //OamsPschRelayAddBtsTeiMapping

#define  RELAY_PSCH_LAST_MSG_NUM                 (RELAY_PSCH_BASE_MSG_NUM + 5)

/* GSAL - RELAY */
#define GSAL_RELAY_BASE_MSG_NUM                  (RELAY_PSCH_LAST_MSG_NUM + 10)

#define PSAPP_RELAY_BSSGP_LLC_DISCARD            (GSAL_RELAY_BASE_MSG_NUM + 0) //BssgpMsgLlcDiscarded
#define PSAPP_RELAY_BSSGP_MS_FLOW_CTRL           (GSAL_RELAY_BASE_MSG_NUM + 1) //BssgpMsgFlowControlMs
#define PSAPP_RELAY_BSSGP_UL_UNIT_DATA           (GSAL_RELAY_BASE_MSG_NUM + 2) //PsappRELAYBssgpUlUnitdata
#define PSAPP_RELAY_BSSGP_REMOVE_TLLI_IND        (GSAL_RELAY_BASE_MSG_NUM + 3) //PsappRELAYBssgpRemoveTlliInd
#define PSAPP_RELAY_BSSGP_UPD_MSID               (GSAL_RELAY_BASE_MSG_NUM + 4) //PsappRELAYBssgpUpdMsid

#define PSSKS_BSSGP_RELAY_FLUSH_LL               (GSAL_RELAY_BASE_MSG_NUM + 5) //BssgpMsgFlushLl
#define PSSKS_BSSGP_RELAY_MS_FLOW_CTRL_ACK       (GSAL_RELAY_BASE_MSG_NUM + 6) //BssgpMsgFlowControlMsAck
#define PSSKS_BSSGP_RELAY_DL_UNIT_DATA           (GSAL_RELAY_BASE_MSG_NUM + 7) //PssksBssgpRELAYDlUnitdata
#define PSSKS_BSSGP_RELAY_UPD_TLLIINDEX          (GSAL_RELAY_BASE_MSG_NUM + 8) //PssksBssgpRELAYUpdTlliIndex

#define GSAL_RELAY_LAST_MSG_NUM                  (GSAL_RELAY_BASE_MSG_NUM  + 10)

/************************************ADDED on 25th Jan. for RRAL and RELAY Interface********Ends******/
/* CS_PS_MERGING : 07-Mar-2012 END */


#define BSC_TABLE_API_BASE                                      0x5000

/* New Offset added 
 * For all Control Application interfaces.
 * Date: 12-Oct-2012
 */
#define BSC_CONTROL_APPL_BASE                                   0x6000

/* New Messages for CPHM to CPHM interface of LCLS: Date: 12-Oct-2012 */
#define CSAPP_CPHM_CPHM_SEND_LCLS_NOTIFY_IND    			(BSC_CONTROL_APPL_BASE + 1)
#define CSAPP_CPHM_CPHM_LCLS_START_SWITCH_REQ   			(BSC_CONTROL_APPL_BASE + 2)
#define CSAPP_CPHM_CPHM_LCLS_START_SWITCH_ACK   			(BSC_CONTROL_APPL_BASE + 3)
#define CSAPP_CPHM_CPHM_LCLS_CONNECT_CONTROL_LOC			(BSC_CONTROL_APPL_BASE + 4)

/*!Start:Added for MC_BTS_TYPE
	Dated:Nov 22,2012
	Modified By:Pardeep Kumar
*/
#define OAMS_BTSH_ABIHM_SET_BM_CONFIG						(BSC_CONTROL_APPL_BASE + 5)
#define CSAPP_ABIHM_BTSH_SET_BM_CONFIG_ACK			(BSC_CONTROL_APPL_BASE + 6)
#define	CSAPP_ABIHM_BTSH_SET_BM_CONFIG_NACK			(BSC_CONTROL_APPL_BASE + 7)	

/* Added for Prop. LCLS Implementaion at AIFDHM for Inter Vertical Data Exchange */
#define	CSAPP_AIFDHM_AIFDHM_DEL_CONNID					(BSC_CONTROL_APPL_BASE + 8)

/*!Start:-OpCodes Defined For New Messages Added b/w LSM and AIFDHM
	Modified By:Pardeep Kumar
	Dated :Jan 30,2013
*/
#define CSAPP_AIFDHM_LSM_UPDATE_MS_DATA_REQ			(BSC_CONTROL_APPL_BASE + 9)

/*!Start:-OpCodes Defined For New Messages Added b/w CPHM and AIFDHM
	Modified By:Raj Kumar
	Dated :May 9,2013
*/
#define CSAPP_AIFDHM_CPHM_PAGING_INFO						(BSC_CONTROL_APPL_BASE + 10)

#define OAMS_CFG_CPHM_AFLEX_AIF_STATUS					(BSC_CONTROL_APPL_BASE + 11)

/*!End*/

#endif /* __SYSXXX_MSGOPCODE_H */
