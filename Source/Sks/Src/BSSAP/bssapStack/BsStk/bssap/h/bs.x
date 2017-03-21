/*******************************************************************************
**      FILE NAME:
**          bs.x
**
**      DESCRIPTION:
**              Defines required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef __BSX__
#define __BSX__

#include "s7_typ.h"
#include "lbs.x"
#include "bs_hashFunc.h"

#ifdef SCM_CHG
#include "sysxxx_typedef.h"
#include "scm_msgdef.h"
#include "nwstkscm_hashdefs.h"
#include "nwstkscm_msgdef.h"
#endif

#define BSSAP_DATA_LEN           (0xFFU)

struct timer_info {
  U8bit    timer_status ;
  timer_id_t  timer_id ;
} ;

typedef struct timer_info  timer_info_t ;

typedef struct spConId           /* connection id */
{
    S16bit suId;                   /* service user id */
    S16bit spId;                   /* service provider id */
    U32bit suInstId;             /* service user instance id */
    U32bit spInstId;             /* service provider instance id */
} SpConId;

typedef struct bsCallCb            /* Bssap Call structure  */
{
  struct bsIntfCb *intfCb;
  U32bit suInstId;
  U32bit spInstId;
  U16bit cic;
  U32bit appId;
  U8bit msgType;
  U8bit callType;
  U32bit callId;
  U8bit timerId;
  U8bit handoverFlagSet;
  U8bit hofaicause;
  Boolean channelAlloc;
  /*timer_info_t timers[MAXSIMTIMER];*/
  CmTimer timers[MAXSIMTIMER];     /* timer structure                    */
  timer_id_t timer_key[MAXSIMTIMER]; /* Amaresh added new key store for timer */
}BsCallCb;

/* Circuit */
typedef struct bsCirCb
{
   struct bsIntfCb *intfCb;
   U16bit cic;
   U8bit flaglistSet;
   U8bit blockReqRetryCount;
   U8bit unBlockReqRetryCount;
   U8bit resetCktRetryCount;
   U8bit cktGrpblockReqRetryCount;
   U8bit cktGrpUnblockReqRetryCount;
   U8bit timerId;
   U8bit msgtype;
   Data* databuf;
   S16bit   datalen;
/*   timer_info_t timers[MAXSIMTIMER];*/
   CmTimer timers[MAXSIMTIMER];     /* timer structure                    */
   timer_id_t timer_key[MAXSIMTIMER]; /* Amaresh added new key store for timer */
}BsCirCb;


typedef struct bsIntfCb       /* Interface control block configuration   */
{
   struct bsLcfRef   **lcfRef;    
   U32bit           nmbLr;                 /* number of local references */
   U32bit           nextLr;                /* next lclRef to be selected */
   BsCirCb       *cicDataList;
#ifdef BSSAP_HA
   CmHashListCp *callIdList;
   CmHashListCp *callRefList;
#endif
   U32bit		 intfId;        /* Interface id                             */
   U8bit            bscId;          /* bsc Id                   */
   U8bit            ni;          /* Sub service field             */
   U16bit           opc;           /* physical originating point code          */
   U16bit           phyDpc;        /* physical destination point code          */
   S16bit	         swtch;         /* Protocol Switch                          */
   U32bit           startCic;
   U32bit           endCic;
   U8bit            PcSsnStatusInd;
   U8bit resetRetryCount;
   U8bit resetIPRetryCount;
   U8bit rstRcvtimerId;
   U8bit rstSndtimerId;
   U8bit overloadT17;
   U8bit overloadT18;
   U8bit Fistoverld;
   U8bit TrbsctimerId;
   TmrCfg t1;
   TmrCfg t4;
   TmrCfg t7;
   TmrCfg t8;
   TmrCfg t10;
   TmrCfg t11;
   TmrCfg t13;
   TmrCfg t17;
   TmrCfg t18;
   TmrCfg t19;
   TmrCfg t20;
   TmrCfg t25;
   TmrCfg trbsc;
   Data* databuf;
   S16bit   datalen;
   /*timer_info_t timers[MAXSIMTIMER];*/
   CmTimer timers[MAXSIMTIMER];     /* timer structure                    */
   BsSts   sts;  /* Commented by Amaresh */          /* layerwide error stats (not cir specific) */
} BsIntfCb;

typedef struct bsLcfRef
{
  BsIntfCb   *intfCb;
  BsCallCb   *callCb;
  U8bit         allocateFfg;
}BsLcfRef;


typedef struct bsCb            /* BSSAP Control                             */
{
   BsInit       init;
   BsGenCfg     genCfg;         /* General configuration                    */
   BsIntfCb     **intfLst;      /* Pointer to Interface control block list   */
   U8bit           nmIntf;
   CmTqCp       callTqCp;        /* call timing queue control point    */
   CmTqCp       cirTqCp;        /* circuit timing queue control point    */
   CmTqCp       nsapTmrTqCp;        /* NSAP timing queue control point    */
   CmTqType     cirTq[TQNUMENT];/* circuit timing queue                */
   CmTqType     callTq[TQNUMENT];/*  connection timing queue             */
   CmTqType     nsapTmrTq[TQNUMENT];/* NSAP connection timing queue             */
  /* BsUstaDgn    ustaDgn;*//* Commented by Amaresh */        /* diagnostics value structure for alarms   */
}BsCb;


EXTERN BsCb bsCb;
#if 0

EXTERN BsCb bsCb;
EXTERN S16bit bsActvInit ARGS((Ent entity, Inst inst, Region region,
                            Reason reason));
EXTERN S16bit bsDropMsg ARGS((Buffer *mBuf));
EXTERN Void bsBldReplyPst ARGS((Pst *rPst, Header *hdr, Pst *iPst));
EXTERN S16bit bsActvTmr ARGS((void));
EXTERN S16bit bsCfgGen ARGS((Pst *pst, BsMngmt *cfg));
EXTERN S16bit bsCfgSAP ARGS(( Pst *pst, BsMngmt *cfg));
EXTERN Void bsHandleTmrEv ARGS((PTR cb, S16bit event));
EXTERN Void bsGenAlarmNew ARGS((Pst *smPst, U16bit category, U16bit event, U16bit cause,
                               Boolean dgnInitialized));
EXTERN S16bit bsInitExt ARGS((void));
EXTERN S16bit bsCfgNSAP ARGS(( Pst *pst, BsMngmt *cfg));
EXTERN S16bit bsCfgCirCb ARGS(( Pst *pst, BsMngmt *cfg));
EXTERN S16bit bsCfgIntfCb ARGS(( Pst *pst, BsMngmt *cfg));
EXTERN S16bit bsCntrlElmnt ARGS(( Pst *pst, BsMngmt *cntrl));
EXTERN S16bit bsInitUstaDgn ARGS((U8bit  type1, PTR val1, U8bit  type2, PTR val2,
                               U8bit  type3, PTR val3, U8bit  type4, PTR val4));
EXTERN S16bit bsStartNSAPTmr ARGS((S16bit timer, BsNSAPCb *cb));
EXTERN S16bit bsRmvNSAPTq ARGS((BsNSAPCb *cb,U8bit tmrNum));
EXTERN S16bit bsStopNSAPTmr ARGS((BsNSAPCb *cb, S16bit timer));
EXTERN S16bit bsCntrlDbg ARGS((Pst *pst,BsMngmt *cntrl));
EXTERN S16bit bsCntrlUstaInd ARGS((Pst *pst,BsMngmt *cntrl));
EXTERN BsCallCb* bsFindCall ARGS((BsIntfCb *intfCb,U32bit id));
EXTERN S16bit bsBldUData ARGS((SpUDatEvnt *uData, BsNSAPCb *sCb));
EXTERN S16bit bsBldData ARGS((SpDatEvnt *dataReq,SuId suId,SpId spId,InstId suInstId,InstId spInstId));
EXTERN S16bit bsBldConEvt ARGS((SpConEvnt *conEvnt,U8bit type,SpConId *conId,BsNSAPCb *sCb));
EXTERN S16bit bsBldDisEvt ARGS((SpDisEvnt *disEvnt,SpConId *conId,U8bit sccpMsgType,BsNSAPCb *sCb));
EXTERN S16bit bsStsCir ARGS(( Pst *pst, Action action, BsMngmt *sta));
EXTERN S16bit bsStsGen ARGS(( Pst *pst, Action action, BsMngmt *sta));
EXTERN Void bsStartConTmr ARGS((S16bit timer, BsCallCb *con, BsIntfCb *cb));
EXTERN Void bsStopConTmr ARGS((BsCallCb *con,S16bit timer));
EXTERN Void bsStartIntfTmr ARGS((S16bit timer,BsIntfCb *cb));
EXTERN Void bsStartCirTmr ARGS((S16bit timer,BsCirCb *cir,BsIntfCb *cb));
EXTERN Void bsStopCirTmr ARGS((BsCirCb *cir,S16bit timer));
EXTERN Void bsStopIntfTmr ARGS((BsIntfCb *intf,S16bit timer));

EXTERN BsNSAPCb *bsGetSCbPtr ARGS((U8bit bscId,Swtch  swtch));
EXTERN BsIntfCb *bsGetIntfPtr ARGS((U8bit bscId,Swtch swtch));
EXTERN S16bit bsInitBsCb ARGS((Ent entity, Inst inst, Region region,
                            Reason reason));
EXTERN BsCallCb *bsCreate_InsertConRef ARGS((BsIntfCb *intfCb));
EXTERN S16bit bsDeallocateConRef ARGS((BsCallCb *cb));
EXTERN BsCallCb* bsFindCallForAbnormalRLSD ARGS((BsIntfCb *intfCb,U32bit appid));
EXTERN S16bit BsMiShtCntrlReq ARGS((Pst *pst, ShtCntrlReqEvnt *reqInfo));
EXTERN S16bit BsMiShtCntrlCfm ARGS((Pst *pst, ShtCntrlCfmEvnt *cfmInfo));
EXTERN S16bit bsEnableLowerSap ARGS((BsNSAPCb *nSapCb,U16bit *reason)); 
EXTERN S16bit bsDisableLowerSap ARGS((BsNSAPCb *nSap));
EXTERN BsIntfCb* bsFindIntf ARGS((Dpc dpcval));

#ifdef ZS
EXTERN S16bit zsActvInit ARGS((Ent entity,Inst inst,Region region,Reason reason));
EXTERN S16bit zsActvTsk ARGS((Pst *pst,Buffer *mBuf));
EXTERN S16bit zsInsertRestId ARGS((BsCallCb *cb,U8bit queueId));
#endif
#ifdef ZS_DFTHA 
EXTERN S16bit ZsUpdatePeer(U8bit msgType,BsCallCb *callcb,BsCirCb  *ciccb,SiInstId InfId,U8bit tags,BsIntfCb *IntfCb,BsNSAPCb *nsap);
EXTERN  S16bit ZsCreateCallCkptSection(U32bit CallRef ,BsCallCb *Calldb);
EXTERN PUBLIC S16bit ZsDeleteCallCkptSection(U32bit CallRef);
EXTERN S16bit ZsCreateCicCkptSection(U16bit Cic,BsCirCb *Cicdb);
EXTERN S16bit ZsCreateSapCkptSection(SiInstId      intfId);
EXTERN S16bit ZsCkptInit(Void);
EXTERN S16bit ZsInitCallCkpt( char *ckptName);
EXTERN S16bit ZsReadCallCkptSection(Void);
EXTERN void getCallRefCkptName(char *suName, char *sgName, char *ckptName);
EXTERN S16bit bsEventInit(Void);
EXTERN S16bit bsEventPublish(char *queue_name);

#endif

#endif /* Commented by Amaresh */
BsCallCb *bsCreate_InsertConRef(BsIntfCb  *intfCb);
BsCallCb* bsFindCall(BsIntfCb *intfCb,U32bit id);
S16bit bsDeallocateConRef(BsCallCb  *cb);

void bsStopConTmr(BsCallCb *con, S16bit timer);
void bsStopIntfTmr(BsIntfCb *intf,U8bit timer);

#ifdef BSSAP_HA
void SocketOption (int fd);
void SetKeepAliveOption(int fd);
int SendInterfaceAddUpdateToPeer(BsIntfCb *bsIntfCb);
int SendInterfaceDelUpdateToPeer(int intfId);
#endif
#ifdef SCM_CHG
int bsCfgIntfCb(ScmBsInterfaceConfig *cfg);
int bsDelIntfCb(ScmBsInterfaceConfig *cfg);
#endif


#endif /* ___BSX__ */

