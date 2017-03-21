/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2005 IntelliNet Technologies, Inc. All Rights Reserved.    *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                  
 * CONTRACT: INTERNAL
 *      
 * ID: $Id: mtp2_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:21:59  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.4  2006/07/19 16:52:30  sjaddu
 * LOG: Removed Traces for mcc driver
 * LOG:
 * LOG: Revision 1.1.2.3  2006/06/14 17:27:37  sjaddu
 * LOG: Commiting after mtp2 testing.
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/14 17:17:52  gdevanand
 * LOG: Commiting after mtp2 testing.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:18:40  lbana
 * LOG: Vframe structure and mtp2 specifics.
 * LOG:
 ****************************************************************************/

#if !defined(_MTP2_INTERN_H_)
#define _MTP2_INTERN_H_

/*
 * The only purpose of this file is to trick any IntelliSS7 included headers
 * into thinking they're still in IntellISS7.  We need to do this, because
 * we don't clearly separate parts of IntelliSS7 into user/kernel.
 */
#include <linux/kernel.h>
#include <linux/errno.h>
#include <asm/string.h>

/*
 * Note that this is LOCAL TO THIS PROJECT, NOT THE USUAL ONE
 */
#include <its.h>

#include "mtp2_cmn.h"
#include "mtp2_sn.h"
#include <itu/mtp2.h>
#include "arrayq.h"

/*
 * To/from user.  Also used to control size of TB/RTB.  Do NOT make
 * less than 4.
 */
#define MTP2_SIGNAL_QUEUE_EXP   6

/*
 * Needed for timer implementation
 * This is a bit of a cheat.  I "know" that these aren't valid L3->L2
 * signals, so they are safe to pass in on the queue as unique signals.
 */
#define MTP2_T1          1
#define MTP2_T2          2
#define MTP2_T3          3
#define MTP2_T4          4
#define MTP2_T5          5
#define MTP2_T6          6
#define MTP2_T7          7
#define MTP2_QUEUED_TRIG 8

/*
 * Some of the arithmetic in this puppy use 7 bits only.  We need
 * something to normalize the arithmetic so we don't get false
 * results.
 */
#define SNVAL(x)         ((x) & 0x7FU)

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * MTP2 Triggers.  Divided into initiating subsystems, then 
 * target subsystem.
 */
typedef enum
{
    /* Management */
    MGMT_LSC_TRIGGER_PowerOn,                 /* MGMT->LSC     */
    MGMT_LSC_TRIGGER_L3_Failure,              /* MGMT->LSC     */
    MGMT_LSC_TRIGGER_LocalProcessorOutage,    /* MGMT->LSC     */
    MGMT_LSC_TRIGGER_LocalProcessorRecovered, /* MGMT->LSC     */

    MGMT_RC_TRIGGER_CongestionAccept,         /* MGMT->RC      */
    MGMT_RC_TRIGGER_CongestionDiscard,        /* MGMT->RC      */
    MGMT_RC_TRIGGER_NoCongestion,             /* MGMT->RC      */

    MGMT_TRIGGER_MIN = MGMT_LSC_TRIGGER_PowerOn,
    MGMT_TRIGGER_MAX = MGMT_RC_TRIGGER_NoCongestion,


    /* Layer 1 */
    L1_DAEDR_TRIGGER_BadCheckSum,             /* L1->DAEDR     */
    L1_DAEDR_TRIGGER_OctetCountingMode,       /* L1->DAEDR     */
    L1_DAEDR_TRIGGER_16_Octets,               /* L1->DAEDR     */
    L1_DAEDR_TRIGGER_SignalUnit,              /* L1->DAEDR     */

    L1_TRIGGER_MIN = L1_DAEDR_TRIGGER_BadCheckSum,
    L1_TRIGGER_MAX = L1_DAEDR_TRIGGER_SignalUnit,


    /* Layer 3 */
    L3_LSC_TRIGGER_Start,                     /* L3->LSC       */
    L3_LSC_TRIGGER_Stop,                      /* L3->LSC       */
    L3_LSC_TRIGGER_Continue,                  /* L3->LSC       */
    L3_LSC_TRIGGER_RetrieveBSNT,              /* L3->LSC       */
    L3_LSC_TRIGGER_RetrievalFSNC,             /* L3->LSC       */
    L3_LSC_TRIGGER_Emergency,                 /* L3->LSC       */
    L3_LSC_TRIGGER_EmergencyEnd,              /* L3->LSC       */
    L3_LSC_TRIGGER_LocalProcessorRecovered,   /* L3->LSC       */
    L3_LSC_TRIGGER_FlushBuffers,              /* L3->LSC       */

    L3_TXC_TRIGGER_MessageForTransmission,    /* L3->LSC       */

    L3_TRIGGER_MIN = L3_LSC_TRIGGER_Start,
    L3_TRIGGER_MAX = L3_TXC_TRIGGER_MessageForTransmission,


    /* Link State Control */
    LSC_L3_TRIGGER_InService,                 /* LSC->L3       */
    LSC_L3_TRIGGER_OutOfService,              /* LSC->L3       */
    LSC_L3_TRIGGER_Stop,                      /* LSC->L3       */
    LSC_L3_TRIGGER_RemoteProcessorOutage,     /* LSC->L3       */
    LSC_L3_TRIGGER_RemoteProcessorRecovered,  /* LSC->L3       */

    LSC_IAC_TRIGGER_Start,                    /* LSC->IAC      */
    LSC_IAC_TRIGGER_Stop,                     /* LSC->IAC      */
    LSC_IAC_TRIGGER_Emergency,                /* LSC->IAC      */

    LSC_POC_TRIGGER_Stop,                     /* LSC->POC      */
    LSC_POC_TRIGGER_LocalProcessorOutage,     /* LSC->POC      */
    LSC_POC_TRIGGER_LocalProcessorRecovered,  /* LSC->POC      */
    LSC_POC_TRIGGER_RemoteProcessorOutage,    /* LSC->POC      */
    LSC_POC_TRIGGER_RemoteProcessorRecovered, /* LSC->POC      */
    LSC_POC_TRIGGER_NoProcessorOutage,        /* LSC->POC      */

    LSC_TXC_TRIGGER_Start,                    /* LSC->TXC      */
    LSC_TXC_TRIGGER_Stop,                     /* LSC->TXC      */
    LSC_TXC_TRIGGER_RetrievalFSNC,            /* LSC->TXC      */
    LSC_TXC_TRIGGER_SendSIOS,                 /* LSC->TXC      */
    LSC_TXC_TRIGGER_SendFISU,                 /* LSC->TXC      */
    LSC_TXC_TRIGGER_SendSIPO,                 /* LSC->TXC      */
    LSC_TXC_TRIGGER_SendMSU,                  /* LSC->TXC      */
    LSC_TXC_TRIGGER_FlushBuffers,             /* LSC->TXC      */

    LSC_RC_TRIGGER_Start,                     /* LSC->RC       */
    LSC_RC_TRIGGER_Stop,                      /* LSC->RC       */
    LSC_RC_TRIGGER_RetrieveBSNT,              /* LSC->RC       */
    LSC_RC_TRIGGER_RetrieveFSNX,              /* LSC->RC       */
    LSC_RC_TRIGGER_AcceptMSUOrFISU,           /* LSC->RC       */
    LSC_RC_TRIGGER_RejectMSUOrFISU,           /* LSC->RC       */

    LSC_AERM_TRIGGER_SetTiToTin,              /* LSC->AERM     */

    LSC_SUERM_TRIGGER_Start,                  /* LSC->SUERM    */
    LSC_SUERM_TRIGGER_Stop,                   /* LSC->SUERM    */

    LSC_TRIGGER_MIN = LSC_L3_TRIGGER_InService,
    LSC_TRIGGER_MAX = LSC_SUERM_TRIGGER_Stop,


    /* Initial Aligment Control */
    IAC_LSC_TRIGGER_AlignmentComplete,        /* IAC->LSC      */
    IAC_LSC_TRIGGER_AlignmentNotPossible,     /* IAC->LSC      */

    IAC_TXC_TRIGGER_SendSIO,                  /* IAC->TXC      */
    IAC_TXC_TRIGGER_SendSIN,                  /* IAC->TXC      */
    IAC_TXC_TRIGGER_SendSIE,                  /* IAC->TXC      */

    IAC_AERM_TRIGGER_Start,                   /* IAC->AERM     */
    IAC_AERM_TRIGGER_Stop,                    /* IAC->AERM     */
    IAC_AERM_TRIGGER_SetTiToTin,              /* IAC->AERM     */
    IAC_AERM_TRIGGER_SetTiToTie,              /* IAC->AERM     */

    IAC_TRIGGER_MIN = IAC_LSC_TRIGGER_AlignmentComplete,
    IAC_TRIGGER_MAX = IAC_AERM_TRIGGER_SetTiToTie,


    /* Processor Outage Control */
    POC_LSC_TRIGGER_NoProcessorOutage,        /* POC-LSC       */

    POC_TRIGGER_MIN = POC_LSC_TRIGGER_NoProcessorOutage,
    POC_TRIGGER_MAX = POC_LSC_TRIGGER_NoProcessorOutage,


    /* Delimitation, Alignment, and Error Detection (Receive)  */
    DAEDR_IAC_TRIGGER_CorrectSU,              /* DAEDR->IAC    */

    DAEDR_RC_TRIGGER_SignalUnit,              /* DAEDR->RC     */

    DAEDR_SUERM_TRIGGER_SUInError,            /* DAEDR->SUERM  */
    DAEDR_SUERM_TRIGGER_CorrectSU,            /* DAEDR->SUERM  */

    DAEDR_AERM_TRIGGER_SUInError,             /* DAEDR->AERM   */

    DAEDR_L1_TRIGGER_Start,                   /* DAEDR->L1     */

    DAEDR_TRIGGER_MIN = DAEDR_IAC_TRIGGER_CorrectSU,
    DAEDR_TRIGGER_MAX = DAEDR_L1_TRIGGER_Start,


    /* Delimitation, Alignment, and Error Detection (Transmit) */
    DAEDT_TXC_TRIGGER_TransmissionRequest,    /* DAEDT->TXC    */
    DAEDT_L1_TRIGGER_BitsForTransmission,     /* DAEDT->TXC    */

    DAEDT_TRIGGER_MIN = DAEDT_TXC_TRIGGER_TransmissionRequest,
    DAEDT_TRIGGER_MAX = DAEDT_L1_TRIGGER_BitsForTransmission,

    /* Basic Transmission Control */
    TXC_L3_TRIGGER_RetrievedMessage,          /* TXC->L3       */
    TXC_L3_TRIGGER_RetrievalNotPossible,      /* TXC->L3       */
    TXC_L3_TRIGGER_RetrievalComplete,         /* TXC->L3       */
    TXC_L3_TRIGGER_RTBCleared,                /* TXC->L3       */

    TXC_LSC_TRIGGER_LinkFailure,              /* TXC->LSC      */

    TXC_DAEDT_TRIGGER_Start,                  /* TXC->DAEDT    */
    TXC_DAEDT_TRIGGER_SignalUnit,             /* TXC->DAEDT    */

    TXC_RC_TRIGGER_FSNTValue,                 /* TXC->RC       */

    TXC_TRIGGER_MIN = TXC_L3_TRIGGER_RetrievedMessage,
    TXC_TRIGGER_MAX = TXC_RC_TRIGGER_FSNTValue,


    /* Basic Reception Control */
    RC_L3_TRIGGER_ReceivedMessage,            /* RC->L3        */
    RC_L3_TRIGGER_BSNT,                       /* RC->L3        */
    RC_L3_TRIGGER_BSNTNotRetrievable,         /* RC->L3        */
    RC_L3_TRIGGER_RBCleared,                  /* RC->L3        */

    RC_LSC_TRIGGER_LinkFailure,               /* RC->LSC       */
    RC_LSC_TRIGGER_ReceiveSIO,                /* RC->LSC       */
    RC_LSC_TRIGGER_ReceiveSIN,                /* RC->LSC       */
    RC_LSC_TRIGGER_ReceiveSIE,                /* RC->LSC       */
    RC_LSC_TRIGGER_ReceiveSIOS,               /* RC->LSC       */
    RC_LSC_TRIGGER_ReceiveSIPO,               /* RC->LSC       */
    RC_LSC_TRIGGER_ReceiveMSUOrFISU,          /* RC->LSC       */

    RC_IAC_TRIGGER_ReceiveSIO,                /* RC->IAC       */
    RC_IAC_TRIGGER_ReceiveSIN,                /* RC->IAC       */
    RC_IAC_TRIGGER_ReceiveSIE,                /* RC->IAC       */
    RC_IAC_TRIGGER_ReceiveSIOS,               /* RC->IAC       */

    RC_DAEDR_TRIGGER_Start,                   /* RC->DAEDR     */

    RC_TXC_TRIGGER_NACKToBeSent,              /* RC->TXC       */
    RC_TXC_TRIGGER_SIBReceived,               /* RC->TXC       */
    RC_TXC_TRIGGER_BSNRAndBIBR,               /* RC->TXC       */
    RC_TXC_TRIGGER_FSNXValue,                 /* RC->TXC       */

    RC_CC_TRIGGER_Normal,                     /* RC->CC        */
    RC_CC_TRIGGER_Busy,                       /* RC->CC        */

    RC_TRIGGER_MIN = RC_L3_TRIGGER_ReceivedMessage,
    RC_TRIGGER_MAX = RC_CC_TRIGGER_Busy,


    /* Alignment Error Rate Monitor */
    AERM_IAC_TRIGGER_AbortProving,            /* AERM->IAC     */

    AERM_TRIGGER_MIN = AERM_IAC_TRIGGER_AbortProving,
    AERM_TRIGGER_MAX = AERM_IAC_TRIGGER_AbortProving,

    /* Signal Unit Error Rate Monitor */
    SUERM_LSC_TRIGGER_LinkFailure,            /* SUERM->LSC    */

    SUERM_TRIGGER_MIN = SUERM_LSC_TRIGGER_LinkFailure,
    SUERM_TRIGGER_MAX = SUERM_LSC_TRIGGER_LinkFailure,

    /* Congestion Control */
    CC_TXC_TRIGGER_SendSIB,                   /* CC->TXC       */

    CC_TRIGGER_MIN = CC_TXC_TRIGGER_SendSIB,
    CC_TRIGGER_MAX = CC_TXC_TRIGGER_SendSIB,

    /* Timers */
    TIMER_TRIGGER_StartT1,
    TIMER_TRIGGER_StopT1,
    TIMER_TRIGGER_T1Expired,

    TIMER_TRIGGER_StartT2,
    TIMER_TRIGGER_StopT2,
    TIMER_TRIGGER_T2Expired,

    TIMER_TRIGGER_StartT3,
    TIMER_TRIGGER_StopT3,
    TIMER_TRIGGER_T3Expired,

    TIMER_TRIGGER_StartT4,
    TIMER_TRIGGER_StopT4,
    TIMER_TRIGGER_T4Expired,

    TIMER_TRIGGER_StartT5,
    TIMER_TRIGGER_StopT5,
    TIMER_TRIGGER_T5Expired,

    TIMER_TRIGGER_StartT6,
    TIMER_TRIGGER_StopT6,
    TIMER_TRIGGER_T6Expired,

    TIMER_TRIGGER_StartT7,
    TIMER_TRIGGER_StopT7,
    TIMER_TRIGGER_T7Expired,

    TIMER_TRIGGER_MIN = TIMER_TRIGGER_StartT1,
    TIMER_TRIGGER_MAX = TIMER_TRIGGER_T7Expired
}
MTP2_Trigger;        

/*
 * Inter-subsystem messages
 */
typedef struct
{
    ITS_OCTET FSNC;
}
RetrievalFSNC;

typedef struct
{
    ITS_OCTET BIBR;
    ITS_OCTET BSNR;
}
BSNRAndBIBR;

typedef struct
{
    ITS_OCTET BSNR;
}
BSNRAlone;

typedef struct
{
    ITS_OCTET FSNX;
}
FSNXValue;

typedef struct
{
    ITS_OCTET FSNT;
}
FSNTValue;

typedef struct
{
    ITS_OCTET BSNT;
}
RetrieveBSNT;

/*
 * LSC states
 */
typedef enum
{
    LSC_STATE_POWER_OFF,
    LSC_STATE_OUT_OF_SERVICE,
    LSC_STATE_INITIAL_ALIGNMENT,
    LSC_STATE_ALIGNED_NOT_READY,
    LSC_STATE_ALIGNED_READY,
    LSC_STATE_PROCESSOR_OUTAGE,
    LSC_STATE_IN_SERVICE,
    LSC_STATE_MAX_STATE
}
LSC_States;

/*
 * LSC data
 */
struct LSC_Info
{
    LSC_States  curState;
    ITS_BOOLEAN localProcessorOutage;
    ITS_BOOLEAN processorOutage;
    ITS_BOOLEAN emergency;
    ITS_BOOLEAN l3Received;
};

/*
 * IAC states
 */
typedef enum
{
    IAC_STATE_IDLE,
    IAC_STATE_NOT_ALIGNED,
    IAC_STATE_ALIGNED,
    IAC_STATE_PROVING,
    IAC_STATE_MAX_STATE
}
IAC_States;

/*
 * IAC data
 */
struct IAC_Info
{
    IAC_States  curState;
    ITS_BOOLEAN emergency;
    ITS_BOOLEAN furtherProving;
    ITS_UINT    Pn;
    ITS_UINT    Pe;
    ITS_UINT    Cp;
};

/*
 * POC states
 */
typedef enum
{
    POC_STATE_IDLE,
    POC_STATE_LOCAL_PROCESSOR_OUTAGE,
    POC_STATE_REMOTE_PROCESSOR_OUTAGE,
    POC_STATE_BOTH_PROCESSORS_OUT,
    POC_STATE_MAX_STATE
}
POC_States;

/*
 * POC data
 */
struct POC_Info
{
    POC_States  curState;
};

/*
 * DAEDR states
 */
typedef enum
{
    DAEDR_STATE_IDLE,
    DAEDR_STATE_IN_SERVICE,
    DAEDR_STATE_MAX_STATE
}
DAEDR_States;

/*
 * DAEDR data
 */
struct DAEDR_Info
{
    DAEDR_States  curState;
    ITS_BOOLEAN   octetCountingMode;
};

/*
 * DAEDT states
 */
typedef enum
{
    DAEDT_STATE_IDLE,
    DAEDT_STATE_IN_SERVICE,
    DAEDT_STATE_MAX_STATE
}
DAEDT_States;

/*
 * DAEDT data
 */
struct DAEDT_Info
{
    DAEDT_States  curState;
};

/*
 * TXC states
 */
typedef enum
{
    TXC_STATE_IDLE,
    TXC_STATE_IN_SERVICE,
    TXC_STATE_MAX_STATE
}
TXC_States;

/*
 * TXC data
 */
struct TXC_Info
{
    TXC_States  curState;
    ITS_BOOLEAN LSSUAvailable;
    ITS_BOOLEAN SIBReceived;
    ITS_BOOLEAN RTBFull;
    ITS_OCTET   statusInd;
    ITS_BOOLEAN forcedRetransmission;
    ITS_BOOLEAN MSUInhibited;
    ITS_UINT Cm;           /* Explicitly initialized in SDL */
    ITS_UINT Z;            /* Explicitly initialized in SDL */
    ITS_UINT octetCount;
    ITS_UINT N1;
    ITS_UINT N2;
    unsigned int  FIB : 1, /* Explicitly initialized in SDL */
                  BIB : 1, /* Explicitly initialized in SDL */
                  FSNT : 7, /* Explicitly initialized in SDL */
                  FSNL : 7, /* Explicitly initialized in SDL */
                  FSNX : 7, /* Explicitly initialized in SDL */
                  FSNF : 7; /* Explicitly initialized in SDL */
};

/*
 * RC states
 */
typedef enum
{
    RC_STATE_IDLE,
    RC_STATE_IN_SERVICE,
    RC_STATE_MAX_STATE
}
RC_States;

/*
 * RC data
 */
struct RC_Info
{
    RC_States   curState;
    ITS_BOOLEAN FISUOrMSUAccepted;
    ITS_BOOLEAN abnormalBSNR;
    ITS_BOOLEAN abnormalFIBR;
    ITS_BOOLEAN congestionDiscard;
    ITS_BOOLEAN congestionAccept;
    unsigned int RTR : 1,
                 UNF : 1,
                 UNB : 1,
                 FIBX : 1, /* Explicitly initialized in SDL */
                 FSNX : 7, /* Explicitly initialized in SDL */
                 FSNF : 7, /* Explicitly initialized in SDL */
                 FSNT : 7; /* Explicitly initialized in SDL */
};

/*
 * AERM states
 */
typedef enum
{
    AERM_STATE_IDLE,
    AERM_STATE_MONITORING,
    AERM_STATE_MAX_STATE
}
AERM_States;

/*
 * AERM data
 */
struct AERM_Info
{
    AERM_States  curState;
    ITS_UINT     Ti;
    ITS_UINT     Tin;
    ITS_UINT     Tie;
    ITS_UINT     Ca;
};

/*
 * SUERM states
 */
typedef enum
{
    SUERM_STATE_IDLE,
    SUERM_STATE_IN_SERVICE,
    SUERM_STATE_MAX_STATE
}
SUERM_States;

/*
 * SUERM data
 */
struct SUERM_Info
{
    SUERM_States  curState;
    ITS_UINT      Cs;
    ITS_UINT      Nsu;
    ITS_UINT      T;
};

/*
 * CC states
 */
typedef enum
{
    CC_STATE_IDLE,
    CC_STATE_L2_CONGESTION,
    CC_STATE_MAX_STATE
}
CC_States;

/*
 * CC data
 */
struct CC_Info
{
    CC_States  curState;
};

/*
 * MTP2 signal transfer
 */ 

/*
 * Queue entry format
 */
typedef struct
{
    arrayq_elem_t elem;
    MTP2_Signal   signal;
}
MTP2_QEntry;

/*
 * Link Performance Statistics Data Structure 
 */
typedef struct
{
    unsigned int SLFail_abnormBSNR;  /* link failures due to abn BSNR */
    unsigned int SLFail_abnormFIBR;  /* link failures due to abn FIBR */
    unsigned int SLFail_T7;      /* link failures due to T7 Expiry */
    unsigned int SLFail_suerm;   /* link failures due to SUERM */
    unsigned int SLFail_cong;    /* link failures due to T6 Expiry */
    unsigned int ALFail_T2T3;    /* alignment failures due to T2 or T3 */
    unsigned int ALFail_aerm;    /* alignment failures due to aerm */
    unsigned int numNegAck;      /* Number of Negative Acks */
    unsigned int numErrSu;       /* Number of SUs in error */
    unsigned int SIBtx;          /* SIBs Tx'd */
    unsigned int SIBrx;          /* SIBs Rx'd */
    unsigned int N1rtx;          /* Number of Retransmissions due to N1 */
    unsigned int N2rtx;          /* Number of Retransmissions due to N2 */
    unsigned int MSUrtx;         /* Number of MSUs Retransmitted */
    unsigned int MSUrtx_octets;  /* Number of MSU Octets Retransmitted */
    unsigned int MSUhsrx;        /* Number of MSUs Rx'd from MTP3 */
    unsigned int MSUhstx;        /* Number of MSUs Tx'd to MTP3 */
    unsigned int MSUrx;          /* Number of MSUs Rx'd from MCC */
    unsigned int MSUtx;          /* Number of MSUs Tx'd to MCC */
    unsigned int MSUtx_octets;   /* Number of MSU octets Tx'd to MCC */
    unsigned int MSUrx_octets;   /* Number of MSU octets Rx'd from MCC */
    unsigned int RQThresCross;   /* Number of times RQ crossed threshold */
    unsigned int TQThresCross;   /* Number of times TQ crossed threshold */
    unsigned int TBThresCross;   /* Number of times TB crossed threshold */
    unsigned int RTBThresCross;  /* Number of times RTB crossed threshold */
}
MTP2_PerfData;
/*
 * Link State structure
 */
typedef struct
{
    struct LSC_Info   lscInfo;
    struct IAC_Info   iacInfo;
    struct POC_Info   pocInfo;
    struct DAEDR_Info daedrInfo;
    struct DAEDT_Info daedtInfo;
    struct TXC_Info   txcInfo;
    struct RC_Info    rcInfo;
    struct AERM_Info  aermInfo;
    struct SUERM_Info suermInfo;
    struct CC_Info    ccInfo;

    MTP2_TraceData    traceData;
    MTP2_ConfigData   configData;
    MTP2_PerfData    perfData;

    /*
     * Interface to user (well, really the OS).
     */
    unsigned     linkNum;
    arrayq_t     rq;
    MTP2_QEntry  rqData[1 << MTP2_SIGNAL_QUEUE_EXP];
    arrayq_t     tq;
    MTP2_QEntry  tqData[1 << MTP2_SIGNAL_QUEUE_EXP];
    arrayq_t     rtb;
    MTP2_QEntry  rtbData[1 << (MTP2_SIGNAL_QUEUE_EXP - 2)];
    arrayq_t     tb;
    MTP2_QEntry  tbData[1 << (MTP2_SIGNAL_QUEUE_EXP - 1)];
}
MTP2_LinkState;

/*
 * Function signatures
 */
void L1_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
             ITS_OCTET *data, ITS_USHORT size);
void L3_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
             ITS_OCTET *data, ITS_USHORT size);
void LSC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size);
void IAC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size);
void POC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size);
void DAEDR_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size);
void DAEDT_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size);
void TXC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size);
void RC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
             ITS_OCTET *data, ITS_USHORT size);
void AERM_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size);
void SUERM_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size);
void CC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
             ITS_OCTET *data, ITS_USHORT size);
void TIMER_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size);

/*
 * Interface functions
 */
int  L3_Buffer(MTP2_LinkState *link, MTP2_QEntry *data);
void L3_Dispatch(MTP2_LinkState *link, MTP2_QEntry *data);
int QueueIncoming(MTP2_LinkState *link, MTP2_QEntry *sig);
void QueueOutgoing(MTP2_LinkState *link, MTP2_QEntry *signal);
const char *MTP2_TriggerToString(MTP2_Trigger trigger);
void MTP2_ToggleAERM(MTP2_LinkState *link, int onOff);
void MTP2_ToggleSUERM(MTP2_LinkState *link, int onOff);
void MTP2_ToggleOCM(MTP2_LinkState *link, int onOff);
void MTP2_ResetFISUFilter(MTP2_LinkState *link);

/*
 * For trace.
 */
extern void MTP2_Trace(MTP2_LinkState *link, int level,
                       const char *format, ...);

/*
 * for now
 */
/*
#define DEBUG_TRIGGERS 
*/
/*
  This needs tweaking.
 */
#define MTP2_CRITICAL(l,f,...) \
    MTP2_Trace(l,ITS_TRACE_LEVEL_CRITICAL,f,__VA_ARGS__)
#define MTP2_ERROR(l,f,...)    \
    MTP2_Trace(l,ITS_TRACE_LEVEL_ERROR,f,__VA_ARGS__)
#define MTP2_WARNING(l,f,...)  \
    MTP2_Trace(l,ITS_TRACE_LEVEL_WARNING,f,__VA_ARGS__)
#define MTP2_DEBUG(l,f,...)    \
    MTP2_Trace(l,ITS_TRACE_LEVEL_DEBUG,f,__VA_ARGS__)

#if defined(__cplusplus)
}
#endif

#endif /* _MTP2_INTERN_H_ */

