/*******************************************************************************
**      FILE NAME:
**          bssapmf.x
**
**      DESCRIPTION:
**              Defines Structures and Parameters required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/


#ifndef __BSSAPMFX__
#define __BSSAPMFX__

/* Common Sttructue used to strote msg Param information*/
typedef struct bsMsgArgsList
{
    U8bit*  mArgs;
    S16bit  nmArgs;
    U8bit*  oArgs;
    S16bit  noArgs;
}BsMsgArgsList;

/*****************************************************
           Assignement Request
*****************************************************/
static U8bit AssignReqMArgs[] =
{
        BSSAP_IEI_CHANNEL_TYPE
};

static U8bit AssignReqOArgs[] =
    {
        BSSAP_IEI_LAYER3_HEADER_INFORMATION,
        BSSAP_IEI_PRIORITY,
        BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
        BSSAP_IEI_DOWNLINK_DTX_FLAG,
        BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED,
        BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2,
        BSSAP_IEI_GROUP_CALL_REFERENCE,
        BSSAP_IEI_TALKER_FLAG,
        BSSAP_IEI_CONFIGURATION_EVOLUTION_IND,
        BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR,
        BSSAP_IEI_SERVICE_HANDOVER,
        BSSAP_IEI_ENCRYPTION_INFORMATION ,
        BSSAP_IEI_TALKER_PRIORITY,
        BSSAP_IEI_AOIP,
        BSSAP_IEI_CODEC_LIST,
        BSSAP_IEI_CALL_ID,
        BSSAP_IEI_PROFILE_ID
#ifdef LCLS_PARAM_DECODE
        ,
        BSSAP_IEI_KC128,                         
        BSSAP_IEI_GLB_CALL_REF,                  
        BSSAP_IEI_LCLS_CONFIG,                   
        BSSAP_IEI_LCLS_CONN_STATUS_CNTRL,        
        BSSAP_IEI_LCLS_CORR_NOT_NED 
#endif
    };
BsMsgArgsList BSSAP_AssignReq =
{
    AssignReqMArgs, sizeof(AssignReqMArgs),
    AssignReqOArgs, sizeof(AssignReqOArgs)
};

/*****************************************************
           Assignement Complete
*****************************************************/
static U8bit  AssignComOArgs[] =
    {
       BSSAP_IEI_RR_CAUSE,
       BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
       BSSAP_IEI_CELL_IDENTIFIER,
       BSSAP_IEI_CHOSEN_CHANNEL,
       BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM,
       BSSAP_IEI_CIRCUIT_POOL,
       BSSAP_IEI_SPEECH_VERSION,
       BSSAP_IEI_LSA_IDENTIFIER,
       BSSAP_IEI_TALKER_PRIORITY,
       BSSAP_IEI_AOIP,
       BSSAP_IEI_CODEC_LIST,
       BSSAP_IEI_SPEECH_CODEC
#ifdef LCLS_PARAM_DECODE
        ,
       BSSAP_IEI_LCLS_BSS_STATUS
#endif

    };

BsMsgArgsList BSSAP_AssignCom=
{
    NULL,0,
    AssignComOArgs, sizeof(AssignComOArgs)

}
;
/*****************************************************
           Assignement Failure
*****************************************************/
static U8bit  AssignFailmArgs[] =
   {
       BSSAP_IEI_CAUSE
   };
static U8bit  AssignFailOArgs[] =
    {
       BSSAP_IEI_RR_CAUSE,
       BSSAP_IEI_CIRCUIT_POOL,
       BSSAP_IEI_CIRCUIT_POOL_LIST,
       BSSAP_IEI_TALKER_PRIORITY,
       BSSAP_IEI_CODEC_LIST
    };

BsMsgArgsList BSSAP_AssignFail=
{
    AssignFailmArgs,sizeof(AssignFailmArgs),
    AssignFailOArgs, sizeof(AssignFailOArgs)

}
;


static U8bit  HandoverReqstmArgs[] =
   {
        BSSAP_IEI_CHANNEL_TYPE,
        BSSAP_IEI_ENCRYPTION_INFORMATION,
        BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1,  
        BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2,  
        BSSAP_IEI_CELL_IDENTIFIER,
        BSSAP_IEI_CELL_IDENTIFIER
   };
static U8bit  HandoverReqstOArgs[] =
   {
        BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
        BSSAP_IEI_PRIORITY,
        BSSAP_IEI_DOWNLINK_DTX_FLAG,
        BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED,
        BSSAP_IEI_CAUSE,
        BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3,
        BSSAP_IEI_CURRENT_CHANNEL_TYPE_1,
        BSSAP_IEI_SPEECH_VERSION,
        BSSAP_IEI_GROUP_CALL_REFERENCE,
        BSSAP_IEI_TALKER_FLAG,
        BSSAP_IEI_CONFIGURATION_EVOLUTION_IND,
        BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM,
        BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO,
        BSSAP_IEI_LSA_INFORMATION,
        BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR,
        BSSAP_IEI_SERVICE_HANDOVER,
        BSSAP_IEI_IMSI,BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS,
        BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA,
        BSSAP_IEI_TALKER_PRIORITY,
        BSSAP_IEI_AOIP,
        BSSAP_IEI_CODEC_LIST,
        BSSAP_IEI_CALL_ID,
        BSSAP_IEI_PROFILE_ID
#ifdef LCLS_PARAM_DECODE
        ,
        BSSAP_IEI_KC128,
        BSSAP_IEI_GLB_CALL_REF,
        BSSAP_IEI_LCLS_CONFIG,
        BSSAP_IEI_LCLS_CONN_STATUS_CNTRL
#endif

   };
BsMsgArgsList BSSAP_HandoverReqst=
{
    HandoverReqstmArgs,sizeof(HandoverReqstmArgs),
   HandoverReqstOArgs,sizeof(HandoverReqstOArgs)

}
;
static U8bit  HandoverRequiredmArgs[] =
{
    BSSAP_IEI_CAUSE,
    BSSAP_IEI_CELL_IDENTIFIER_LIST
};
static U8bit  HandoverRequiredOArgs[] =
{
        BSSAP_IEI_RESPONSE_REQUEST,
        BSSAP_IEI_CIRCUIT_POOL_LIST,
        BSSAP_IEI_CURRENT_CHANNEL_TYPE_1,
        BSSAP_IEI_SPEECH_VERSION,
        BSSAP_IEI_QUEUING_INDICATOR,
        BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO,
        BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS,
        BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA,
        BSSAP_IEI_TALKER_PRIORITY,
        BSSAP_IEI_SPEECH_CODEC
};
BsMsgArgsList BSSAP_HandoverRequired=
{
    HandoverRequiredmArgs,sizeof(HandoverRequiredmArgs),
   HandoverRequiredOArgs,sizeof(HandoverRequiredOArgs)
}
;
static U8bit  HandoverReqstAckmArgs[] =
{
       BSSAP_IEI_LAYER3_INFORMATION
};
static U8bit  HandoverReqstAckOArgs[] =
{
        BSSAP_IEI_CHOSEN_CHANNEL,
        BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM,
        BSSAP_IEI_CIRCUIT_POOL,
        BSSAP_IEI_SPEECH_VERSION,
        BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
        BSSAP_IEI_LSA_IDENTIFIER,
        BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO,
        BSSAP_IEI_INTER_SYSTEM_INFO,
        BSSAP_IEI_TALKER_PRIORITY,
        BSSAP_IEI_AOIP,
        BSSAP_IEI_SPEECH_CODEC
#ifdef LCLS_PARAM_DECODE
        ,
       BSSAP_IEI_LCLS_BSS_STATUS
#endif
};
BsMsgArgsList BSSAP_HandoverReqstAck=
{
   HandoverReqstAckmArgs,sizeof(HandoverReqstAckmArgs),
   HandoverReqstAckOArgs,sizeof(HandoverReqstAckOArgs)
};
static U8bit  HandoverCompOArgs[] =
{
    BSSAP_IEI_RR_CAUSE,
    BSSAP_IEI_TALKER_PRIORITY,
    BSSAP_IEI_SPEECH_CODEC,
    BSSAP_IEI_CODEC_LIST,
    BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM,
    BSSAP_IEI_CHOSEN_CHANNEL
#ifdef LCLS_PARAM_DECODE
    ,
    BSSAP_IEI_LCLS_BSS_STATUS
#endif

};
BsMsgArgsList BSSAP_HandoverComp=
{
   NULL,0,
   HandoverCompOArgs , sizeof(HandoverCompOArgs)

};
static U8bit  HandoverFailmArgs[] =
{
    BSSAP_IEI_CAUSE
};
static U8bit  HandoverFailOArgs[] =
{
        BSSAP_IEI_RR_CAUSE,
        BSSAP_IEI_CIRCUIT_POOL,
        BSSAP_IEI_CIRCUIT_POOL_LIST,
        BSSAP_IEI_GERAN_CLASSMARK,
        BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO,
        BSSAP_IEI_INTER_SYSTEM_INFO,
        BSSAP_IEI_TALKER_PRIORITY,
        BSSAP_IEI_CODEC_LIST
};
BsMsgArgsList BSSAP_HandoverFail=
{
   HandoverFailmArgs,sizeof(HandoverFailmArgs),
   HandoverFailOArgs,sizeof(HandoverFailOArgs)

};
static U8bit  HandoverRequiredRejmArgs[] =
{
     BSSAP_IEI_CAUSE
};
static U8bit  HandoverRequiredRejOArgs[] =
{
    BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO,
    BSSAP_IEI_TALKER_PRIORITY
    
};
BsMsgArgsList BSSAP_HandoverRequiredRej=
{
    HandoverRequiredRejmArgs,sizeof(HandoverRequiredRejmArgs),
    HandoverRequiredRejOArgs, sizeof(HandoverRequiredRejOArgs)

};

static U8bit BSSAP_ResetCircuitmArgs[] =
{
     BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
     BSSAP_IEI_CAUSE
};
BsMsgArgsList BSSAP_ResetCircuit=
{
   BSSAP_ResetCircuitmArgs ,sizeof(BSSAP_ResetCircuitmArgs),
   NULL , 0

};
static U8bit  BSSAP_ResetCircuitAcknowledgemArgs[] =
{
       BSSAP_IEI_CIRCUIT_IDENTITY_CODE
};
BsMsgArgsList BSSAP_ResetCircuitAcknowledge=
{
   BSSAP_ResetCircuitAcknowledgemArgs ,sizeof(BSSAP_ResetCircuitAcknowledgemArgs),
   NULL,0
};
static U8bit  BSSAP_ResetmArgs[] =
{
    BSSAP_IEI_CAUSE
};
BsMsgArgsList BSSAP_Reset=
{
    BSSAP_ResetmArgs,sizeof(BSSAP_ResetmArgs),
   NULL,0
};
BsMsgArgsList BSSAP_ResetAcknowledge=
{
   NULL,0,
   NULL,0

};

static U8bit  BSSAP_ResetIPmArgs[] =
{
    BSSAP_IEI_CAUSE,
    BSSAP_IEI_CALLID_LIST
};
BsMsgArgsList BSSAP_ResetIP=
{
    BSSAP_ResetIPmArgs,sizeof(BSSAP_ResetIPmArgs),
   NULL,0
};
static U8bit  BSSAP_ResetIPAckmArgs[] =
{
    BSSAP_IEI_CALLID_LIST
};
BsMsgArgsList BSSAP_ResetIP_Ack=
{
    BSSAP_ResetIPAckmArgs,sizeof(BSSAP_ResetIPAckmArgs),
   NULL,0

};

static U8bit BSSAP_BlockmArgs[] =
{
    BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
    BSSAP_IEI_CAUSE
};
static U8bit  BSSAP_BlockOArgs[] =
{
    BSSAP_IEI_CONNECTION_RELEASE_REQUESTED
};
BsMsgArgsList BSSAP_Block=
{
    BSSAP_BlockmArgs,sizeof(BSSAP_BlockmArgs),
    BSSAP_BlockOArgs, sizeof(BSSAP_BlockOArgs)
};
static U8bit BSSAP_BlockAcknowledgemArgs[] =
{
         BSSAP_IEI_CIRCUIT_IDENTITY_CODE
};
BsMsgArgsList BSSAP_BlockAcknowledge=
{
   BSSAP_BlockAcknowledgemArgs ,sizeof(BSSAP_BlockAcknowledgemArgs),
   NULL,0
};
static U8bit BSSAP_UnblockmArgs[] =
{
    BSSAP_IEI_CIRCUIT_IDENTITY_CODE
};
BsMsgArgsList BSSAP_Unblock=
{
    BSSAP_UnblockmArgs,sizeof(BSSAP_UnblockmArgs),
   NULL,0
};
static U8bit BSSAP_UnblockAcknowledgemArgs[] =
{
    BSSAP_IEI_CIRCUIT_IDENTITY_CODE

};
BsMsgArgsList BSSAP_UnblockAcknowledge=
{
    BSSAP_UnblockAcknowledgemArgs,sizeof(BSSAP_UnblockAcknowledgemArgs),
   NULL,0

};
static U8bit BSSAP_CircuitGroupBlockmArgs[] =
{
        BSSAP_IEI_CAUSE,
        BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
        BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST
};
BsMsgArgsList BSSAP_CircuitGroupBlock=
{
   BSSAP_CircuitGroupBlockmArgs,sizeof(BSSAP_CircuitGroupBlockmArgs),
   NULL,0

};
static U8bit BSSAP_CircuitGroupUnblockmArgs[] =
{
   BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
   BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST
};
BsMsgArgsList BSSAP_CircuitGroupUnblock=
{
   BSSAP_CircuitGroupUnblockmArgs,sizeof(BSSAP_CircuitGroupUnblockmArgs),
   NULL,0
};
static U8bit BSSAP_CircuitGroupBlockAcknowledgemArgs[] =
{
   BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
   BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST
};
BsMsgArgsList BSSAP_CircuitGroupBlockAcknowledge=
{
    BSSAP_CircuitGroupBlockAcknowledgemArgs,sizeof(BSSAP_CircuitGroupBlockAcknowledgemArgs),
   NULL,0
};
static U8bit BSSAP_CircuitGroupUnblockAckmArgs[] =
{
         BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
        BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST
};
BsMsgArgsList BSSAP_CircuitGroupUnblockAck=
{
   BSSAP_CircuitGroupUnblockAckmArgs ,sizeof(BSSAP_CircuitGroupUnblockAckmArgs),
   NULL,0
};
static U8bit BSSAP_UnequippedCircuitmArgs[] =
{
     BSSAP_IEI_CIRCUIT_IDENTITY_CODE
};
static U8bit  BSSAP_UnequippedCircuitOArgs[] =
{
      BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST
};
BsMsgArgsList BSSAP_UnequippedCircuit=
{
    BSSAP_UnequippedCircuitmArgs,sizeof(BSSAP_UnequippedCircuitmArgs),
    BSSAP_UnequippedCircuitOArgs, sizeof(BSSAP_UnequippedCircuitOArgs)
};
static U8bit BSSAP_ClearRequestmArgs[] =
{
    BSSAP_IEI_CAUSE
};
BsMsgArgsList BSSAP_ClearRequest=
{
    BSSAP_ClearRequestmArgs,sizeof(BSSAP_ClearRequestmArgs),
    NULL,0
};
static U8bit BSSAP_ClearCommandmArgs[] =
{
      BSSAP_IEI_CAUSE
};
static U8bit BSSAP_ClearCommandOArgs[] =
{
      BSSAP_IEI_LAYER3_HEADER_INFORMATION
};
BsMsgArgsList BSSAP_ClearCommand=
{
   BSSAP_ClearCommandmArgs ,sizeof(BSSAP_ClearCommandmArgs),
   BSSAP_ClearCommandOArgs , sizeof(BSSAP_ClearCommandOArgs)
};
static U8bit BSSAP_PagingmArgs[] =
{
      BSSAP_IEI_IMSI,
      BSSAP_IEI_CELL_IDENTIFIER_LIST
};
static U8bit BSSAP_PagingOArgs[] =
{
     BSSAP_IEI_TMSI,
     BSSAP_IEI_CHANNEL_NEEDED,
     BSSAP_IEI_eMLPP_PRIORITY
};

BsMsgArgsList  BSSAP_Paging = 
{
   BSSAP_PagingmArgs ,sizeof(BSSAP_PagingmArgs),
   BSSAP_PagingOArgs , sizeof(BSSAP_PagingOArgs)

};
BsMsgArgsList BSSAP_ClearComplete=
{
   NULL ,0,
   NULL, 0
};
static U8bit BSSAP_CompleteLayer3InformationmArgs[] =
{
     BSSAP_IEI_CELL_IDENTIFIER,
     BSSAP_IEI_LAYER3_INFORMATION
};
static U8bit BSSAP_CompleteLayer3InformationOArgs[] =
{
     BSSAP_IEI_CHOSEN_CHANNEL,
     BSSAP_IEI_LSA_IDENTIFIER_LIST,
     BSSAP_IEI_APDU
};
BsMsgArgsList BSSAP_CompleteLayer3Information =
{
  BSSAP_CompleteLayer3InformationmArgs,sizeof(BSSAP_CompleteLayer3InformationmArgs),
  BSSAP_CompleteLayer3InformationOArgs,sizeof(BSSAP_CompleteLayer3InformationOArgs)
};

static U8bit BSSAP_OverloadmArgs[] =
{
     BSSAP_IEI_CAUSE
};
static U8bit BSSAP_OverloadOArgs[] =
{
      BSSAP_IEI_CELL_IDENTIFIER
};
BsMsgArgsList BSSAP_Overload =
{
   BSSAP_OverloadmArgs,sizeof(BSSAP_OverloadmArgs),
   BSSAP_OverloadOArgs,sizeof(BSSAP_OverloadOArgs)
};
static U8bit BSSAP_ChangeCktmArgs[] =
{
    BSSAP_IEI_CAUSE
};
BsMsgArgsList BSSAP_ChangeCkt =
{
   BSSAP_ChangeCktmArgs,sizeof(BSSAP_ChangeCktmArgs),
   NULL,0
};
static U8bit BSSAP_ChangeCktAckmArgs[] =
{
      BSSAP_IEI_CIRCUIT_IDENTITY_CODE
};
BsMsgArgsList BSSAP_ChangeCktAck =
{
     BSSAP_ChangeCktAckmArgs,sizeof(BSSAP_ChangeCktAckmArgs),
     NULL,0
};
static U8bit BSSAP_ConfusionmArgs[] =
{
      BSSAP_IEI_CAUSE,
      BSSAP_IEI_DIAGNOSTICS
};
BsMsgArgsList BSSAP_Confusion =
{
     BSSAP_ConfusionmArgs,sizeof(BSSAP_ConfusionmArgs),
     NULL,0
};
static U8bit BSSAP_InternalhandoverCmdmArgs[] =
{
    BSSAP_IEI_SPEECH_CODEC
};
static U8bit BSSAP_InternalhandoverCmdOArgs[] =
{
    BSSAP_IEI_CIRCUIT_IDENTITY_CODE,
    BSSAP_IEI_AOIP,
    BSSAP_IEI_CALL_ID, 
    BSSAP_IEI_DOWNLINK_DTX_FLAG,
};
BsMsgArgsList BSSAP_InternalhandoverCmd =
{
   BSSAP_InternalhandoverCmdmArgs,sizeof(BSSAP_InternalhandoverCmdmArgs),
   BSSAP_InternalhandoverCmdOArgs,sizeof(BSSAP_InternalhandoverCmdOArgs)
};
static U8bit BSSAP_InternalhandoverReqmArgs[] =
{
  BSSAP_IEI_CAUSE,
  BSSAP_IEI_CELL_IDENTIFIER,
  BSSAP_IEI_CODEC_LIST
};
static U8bit BSSAP_InternalhandoverReqOArgs[] =
{
    BSSAP_IEI_AOIP
};
BsMsgArgsList BSSAP_InternalhandoverReq =
{
   BSSAP_InternalhandoverReqmArgs,sizeof(BSSAP_InternalhandoverReqmArgs),
   BSSAP_InternalhandoverReqOArgs,sizeof(BSSAP_InternalhandoverReqOArgs)
};
static U8bit BSSAP_InternalhandoverReqRejectmArgs[] =
{
  BSSAP_IEI_CAUSE,
};
static U8bit BSSAP_InternalhandoverReqRejectOArgs[] =
{
  BSSAP_IEI_CODEC_LIST
};
BsMsgArgsList BSSAP_InternalhandoverReqReject =
{
   BSSAP_InternalhandoverReqRejectmArgs,sizeof(BSSAP_InternalhandoverReqRejectmArgs),
   BSSAP_InternalhandoverReqRejectOArgs,sizeof(BSSAP_InternalhandoverReqRejectOArgs)
};

#endif
