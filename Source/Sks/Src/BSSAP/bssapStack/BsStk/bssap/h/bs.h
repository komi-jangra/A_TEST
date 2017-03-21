/*******************************************************************************
**      FILE NAME:
**          bs.h
**
**      DESCRIPTION:
**							Defines required by Bssap Stack.
**
**
**      DATE            NAME             							REFERENCE        REASON
**      ----            ----             							---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef __BSH__
#define __BSH__ 

/******************* Define dependency checks (DO NOT CHANGE !!) **********/
#ifdef TDS_ROLL_UPGRADE_SUPPORT
#ifndef TDS_CORE2
#error "Rolling upgrade feature available in CORE II only"
#endif 
#endif


/* global defines */
#if (ERRCLASS & ERRCLS_INT_PAR)
#define BSUPSAP(spId) \
   (((spId >= (SpId)bsCb.genCfg.nmbMaxSaps) || (spId < 0)) ? \
      (BsUpSAPCb *)NULLP : *(bsCb.upSAPLst + spId))


#define BSSCCPSAP(suId) \
   (((suId >= (SuId)bsCb.genCfg.nmbMaxNSaps) || (suId < 0)) ? \
      (BsNSAPCb *)NULLP : *(bsCb.sccpSAPLst + suId))

#define BSFINDINTF(intfId) \
   (((intfId >= (SiInstId)bsCb.genCfg.nmbMaxIntf) || (intfId < 0)) ? \
      (BsIntfCb *)NULLP : *(bsCb.intfLst + intfId))

#else
#define BSUPSAP(spId)   *(bsCb.upSAPLst   + spId)
#define BSSCCPSAP(suId) *(bsCb.sccpSAPLst + suId)
#define BSFINDINTF(intfId) *(bsCb.intfLst + intfId)
#endif /* ERRCLASS & ERRCLS_INT_PAR */

#define BSSNDLBSCFGCFM(pst, cfgPtr, statusval, reasonval, oldId, oldCause) \
       { \
          cfgPtr->cfm.status = statusval; \
          cfgPtr->cfm.reason = reasonval; \
          BsMiLbsCfgCfm(pst, cfgPtr); \
       } 

#define BSSNDLBSCNTRLCFM(pst, cntrlPtr, statusval, reasonval, oldId, oldCause) \
       { \
          cntrlPtr->cfm.status = statusval; \
          cntrlPtr->cfm.reason = reasonval; \
          BsMiLbsCntrlCfm(pst, cntrlPtr); \
       } 

#define BSSNDLBSSTSCFM(pst, stsPtr, statusval, reasonval, action, \
                       oldId, oldCause) \
       { \
          stsPtr->cfm.status = statusval; \
          stsPtr->cfm.reason = reasonval; \
          BsMiLbsStsCfm(pst, action, stsPtr); \
       }
#define BSSNDLBSSTAIND(smPstPtr, category, event, cause, ustaDgn, \
                       oldId, oldCause) \
        bsGenAlarmNew(smPstPtr, category, event, cause, ustaDgn)

#define BSLAYERNAME "BSSAP"
#define BS_STR      "\n\n------------------------------------------------------------------\n\n"

#define BSDBGP(class,arg)   {DBGP(&bsCb.init, BSLAYERNAME, class, arg)}



/* This macro takes the two subsystem service information fields and
   compares the Network type ids in them */
#define BSCMPNT(first,second) (first == second)


/* defines for cb state */
#define BS_UNBND          0      /* SAP/NSAP - not bound */
#define BS_BND            1      /* SAP/NSAP - bound */
#define BS_WT_BNDCFM      2      /* NSAP - waiting for bind confirm */

#define BS_MAX_INTRETRY   2      /* maximum number of bind retries */


/* priority */

#define PRIORUTY_0        0      /* priority 0 */
#define PRIORUTY_1        1      /* priority 1 */ 
#define PRIORUTY_2        2      /* priority 2 */ 


#define BSSAP_NUM_TIMERS                          (0x05U)
#define BSSMAP_REQ_TRIES  4
 
/* timer events */
#define   BSSAP_INVALID_TMRID                     (0xFFU)
#define   BSSAP_T_1                               (0x00U)
#define   BSSAP_T_4                               (0x01U)
#define   BSSAP_T_7                               (0x02U)
#define   BSSAP_T_8                               (0x03U)
#define   BSSAP_T_10                              (0x04U)
#define   BSSAP_T_11                              (0x05U)
#define   BSSAP_T_13                              (0x06U)
#define   BSSAP_T_17                              (0x07U)
#define   BSSAP_T_18                              (0x08U)
#define   BSSAP_T_19                              (0x09U)
#define   BSSAP_T_20                              (0x0AU)
#define   BSSAP_T_25                              (0x0CU)
#define   BSSAP_T_RBSC                            (0x0DU)

#define   BSSAP_T1_INFO_STRING                    "T1"
#define   BSSAP_T4_INFO_STRING                    "T4"
#define   BSSAP_T7_INFO_STRING                    "T7"
#define   BSSAP_T8_INFO_STRING                    "T8"
#define   BSSAP_T10_INFO_STRING                   "T10"
#define   BSSAP_T11_INFO_STRING                   "T11"
#define   BSSAP_T13_INFO_STRING                   "T13"
#define   BSSAP_T17_INFO_STRING                   "T17"
#define   BSSAP_T18_INFO_STRING                   "T18"
#define   BSSAP_T19_INFO_STRING                   "T19"
#define   BSSAP_T20_INFO_STRING                   "T20"

#define TMR_TINT          0x29   /* Interface timer for BINDCFM */
#define TMR_ALL           0xff   /* all timers */

#define NOTUSED           0      /* not used */

#define MAXSIMTIMER       4      /* maximum number of simultaneous timers */
#define MAXCONTIMER       20      /* maximum number of simultaneous timers */

#define MAX_MSG_LEN       272    /* maximum length of the message */

#define TQNUMENT          512    /* timing queue number of entries */


#define MAXSILISNT        4      /* maximum number of lower interfaces with
                                    mtp level 3 */
#define MAXSILISPT        3      /* maximum number of lower interfaces with
                                    sccp */
#define MAXSIMI           3      /* maximum number of interfaces with the sm */


#endif /*End of _BSH_ */
