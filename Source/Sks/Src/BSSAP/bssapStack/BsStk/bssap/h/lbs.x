/*******************************************************************************
**      FILE NAME:
**          lbs.x
**
**      DESCRIPTION:
**  	          		  Defines Structures, variables and typedefs required by the
**	  							  Configuration Management service user.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
#ifndef __LBSX__
#define __LBSX__

/* public variable declarations */

#include "s7_typ.h"


typedef S32bit Cntr;
typedef struct tmrCfg           /* timer configuration structure */
{
   Boolean             enb;                    /* enable */
   U16bit              val;                     /* value */
   timer_id_t  timer_id_key;            /* Start timer key */
} TmrCfg;

typedef struct cmTimer         /* timer structure */
{
   S16bit tmrEvnt;                /* Timer Event */
   U32bit tqExpire;               /* Timing Queue Expiry */
   U16bit cb;                     /* Pointer to start of control block list */
   struct cmTimer *next;       /* Next item in the timing queue */
   struct cmTimer *prev;       /* Previous item in the timing queue */
   U8bit     ent2bUpd;            /* TRUE, if the timer block is not in the
                                  proper bin */
   U16bit   entIdx;                /* Current entry index */
} CmTimer;

typedef struct cmTqCp          /*  timing queue control point */
{
   U32bit nxtEnt;                 /* next Entry */
   U32bit tmrLen;                 /* length of timer (MODULO is -1) */
   CmTimer *tmp;               /* Temporary  variable used in cmPrcTmr */
} CmTqCp;

typedef struct cmTqType
{
   CmTimer *first;             /* First Entry */
   CmTimer *tail;              /* Last Entry */
} CmTqType;

typedef struct cmTmrArg
{
   CmTqCp     *tqCp;           /* timing queue control point */
   CmTqType   *tq;             /* timing queue point */
   CmTimer    *timers;         /* timers array */
   U16bit        cb;              /* control block pointer */
   S16bit        evnt;            /* event */
   U32bit        wait;            /* wait */
   U8bit         tNum;            /* timer number */
   U8bit         max;             /* max timers */
} CmTmrArg;

typedef struct bsInit            /* task initialization */
{
   U8bit  region;                 /* static region */
   U8bit  pool;                     /* static pool */
   S16bit reason;                 /* reason */
   U8bit  cfgDone;                  /* configuration done */
} BsInit;

typedef struct bsGenCfg         /* BSSAP general configuration               */
{
   U32bit    nmbMaxCRef;            /* Maximum allowed call reference*/               
   U32bit    nmbMaxCir;            /* Maximum allowed call reference*/               
   U16bit    nmbMaxIntf;              /* Number of interfaces                     */
   S16bit    timeRes;              /* time resolution                          */
} BsGenCfg;


        
typedef struct bsCirCfg         /* Circuit Configuration                    */
{
   U8bit    bscId;
   U32bit   startCic;
   U32bit   endCic;
   S16bit   swtch;         /* Protocol Switch                          */
} BsCirCfg;

typedef struct bsIntfCfg       /* Interface control block configuration   */
{
   U32bit      intfId;        /* Interface id                             */
   U8bit            bscId;          /* bsc Id                   */
   U8bit            ni;          
   U16bit           opc;           /* physical originating point code          */
   U16bit           phyDpc;        /* physical destination point code          */
   S16bit         swtch;         /* Protocol Switch                          */
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
} BsIntfCfg;

typedef struct bsCfg            /* BSSAP configuration                       */
{
   union
   {
      BsGenCfg   bsGen;         /* BSSAP General Config                      */
      BsIntfCfg bsIntfCb;     /* BSSAP Interface control block             */
      BsCirCfg   bsCir;         /* BSSAP Circuit Config                      */
   } s;
} BsCfg;

typedef struct bsDbgCntrl       /* debugging control structure              */
{
   U32bit dbgMask;                 /* debug mask                               */
} BsDbgCntrl;

typedef struct bsIntfCntrl
{
   U32bit      intfId;        /* Interface id                             */
}BsIntfCntrl;

typedef struct bsGenStat
{
  Cntr unxExpEvt;
  Cntr msgDecodeFail;
  Cntr msgEncodeFail;
  Cntr totalMapMsgRx;
  Cntr totalDtapMsgRx;
  Cntr totalMapMsgTx;
  Cntr totalDtapMsgTx;
  Cntr AssRegRx;
  Cntr handoverReqRx;
  Cntr clearCmdRx;
  Cntr handoverCandEnqRx;
  Cntr handoverRequiredRejRx;
  Cntr handoverCmdRx;
  Cntr handoverSuccRx;
  Cntr resourceReqRx;
  Cntr pagingRx;
  Cntr ClassmarkReqRx;
  Cntr cipherModeCmdRx;
  Cntr changeCktRx;
  Cntr commonIdRx;
  Cntr lsaInfoRx;
  Cntr intHandoverReqRejRx;
  Cntr intHandoverCmdRx;
  Cntr intHandoverEnqRx;
  Cntr AssCmpTx;
  Cntr AssFailTx;
  Cntr chanModReqTx;
  Cntr clearCompTx;
  Cntr clearReqTx;
  Cntr handoverCandRspTx;
  Cntr handoverReqTx;
  Cntr handoverReqAckTx;
  Cntr handoverCmpTx;
  Cntr handoverFailTx;
  Cntr handoverPerfTx;
  Cntr handoverDetTx;
  Cntr resourceIndTx;
  Cntr cipherModeCompTx;
  Cntr cipherModeRejTx;
  Cntr cl3ITx;
  Cntr changeCktAckTx;
  Cntr indHandoverReqTx;

}BsGenStat;


typedef struct bsCktStat
{
   Cntr blockRx;
   Cntr blockAckRx;
   Cntr unblockRx;
   Cntr unblockAckRx;
   Cntr resCirRx;
   Cntr resCirAckRx;
   Cntr cirGrBlockRx;
   Cntr cirGrBlockAckRx;
   Cntr cirGrUnBlockRx;
   Cntr cirGrUnBlockAckRx;
   Cntr overloadRx;
   Cntr confusionRx;
   Cntr loadIndRx;
   Cntr unequippedRx;
   Cntr resetIpResourceRx;
   Cntr resetIpResourceAckRx;
   Cntr blockTx;
   Cntr blockAckTx;
   Cntr unblockTx;
   Cntr unblockAckTx;
   Cntr resCirTx;
   Cntr resCirAckTx;
   Cntr cirGrBlockTx;
   Cntr cirGrBlockAckTx;
   Cntr cirGrUnBlockTx;
   Cntr cirGrUnBlockAckTx;
   Cntr overloadTx;
   Cntr confusionTx;
   Cntr loadIndTx;
   Cntr unequippedTx;
   Cntr resetIpResourceTx;
   Cntr resetIpResourceAckTx;
}BsCktStat;


typedef struct bsSts
{
 /*  DateTime dt;           */ /*date and time */
   U32bit      dpc;
   BsGenStat genStat;
   BsCktStat cktStat;
} BsSts;                    /* statistics */



#if 0
typedef struct bsUstaDgnVal
{
   U8bit type;
   
   union
   {
      Event    event;        /* event identifier */
      SpId     spId;         /* service provider id */
      SuId     suId;         /* service user id     */
      SiInstId spInstId;     /* service provider instance id */
      SiInstId suInstId;     /* service user instance id */
      Cic      cic;          /* circuit identification code */
      Dpc      dpc;          /* dpc */
      U8bit       bscId;       /* interface id */
      S16bit    swtch;        /* protocol switch */
      U8bit       msgType;      /* Message type */
      U8bit       state;        /* Connection state */
      SiInstId intfId;        /* Interface id                             */
      Ssn      ssn;
   } t;
} BsUstaDgnVal;

typedef struct bsUstaDgn
{
   BsUstaDgnVal dgnVal[LBS_USTA_MAX_DGNVAL];
} BsUstaDgn;

typedef struct bsUsta
{
   CmAlarm        alarm;        /* alarm structure */
   BsUstaDgn      dgn;          /* alarm diagnostic values */
} BsUsta;


typedef struct bsMngmt
{
   Header hdr;                  /* header */
   CmStatus cfm;
   union 
   {
      BsCfg   cfg;   /* configuration */
      BsSts   sts;   /* statistics */
      BsUsta  usta;  /* unsolicited status */
      BsCntrl cntrl; /* control */
   }t;
} BsMngmt;
#endif /* Commented by Amaresh for later Use */
#endif
  
