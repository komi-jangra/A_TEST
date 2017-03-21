/*******************************************************************************
**      FILE NAME:
**          bssapcom.x
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



#ifndef __BSSAPCOMX__
#define __BSSAPCOMX__

typedef enum
{
   MO_CALL = 1,
   MT_CALL,
   LU_CALL,
   HO_CALL,
   IMSI_DETACH
}
CALL_TYPE;

#define ITS_MAX_SCCP_IES   32
/*********************************
BSSAP_IEI_RESOURCE_AVAILABLE
*********************************/
typedef struct
{
    U8bit    full[2];
    U8bit    half[2];
}BSSAP_Full_Half;

/********************************
BSSAP_IEI_CELL_IDENTIFIER

*******************************/

typedef struct
{
     U8bit    MCC[2];    /* Mobile COuntry Code*/
     U8bit    MNC;       /* Mobile Network Code*/
     U8bit    LAC[2];    /* Location Area Code*/
     U8bit    CI[2];     /* Cell Identity */
}
BSSAP_Cgi;
typedef struct
{
     U8bit    LAC[2];
     U8bit    CI[2];
}
BSSAP_Lai_Ci;

typedef struct
{
     U8bit    CI[2];
}
BSSAP_Ci;

typedef struct
{
     U8bit    MCC[2];
     U8bit    MNC;
     U8bit    LAC[2];
     U8bit    RNCID[2];
}
BSSAP_Plmn_Lac_Rnc;

typedef struct
{
     U8bit    RNCID[2];
}
BSSAP_Rnc;

typedef struct
{
     U8bit    LAC[2];
     U8bit    RNCID[2];
}
BSSAP_Lac_Rnc;
typedef struct
{
     U8bit    MCC[2];
     U8bit    MNC;
     U8bit    LAC[2];
     U8bit    SAC[2];
}
BSSAP_Sai;

typedef struct
{
    U8bit    MCC[2];    /* Mobile Country Code*/
    U8bit    MNC;       /* Mobile Network Code */
    U8bit    LAC[2];    /* Location Area Code */
}
BSSAP_Lai;
typedef struct
{
   U8bit    LAC[2];    /* Location Area Code */
}
BSSAP_Lac;
typedef struct
{
    U8bit    LAC[2];
    U8bit    CI[2];
}
BSSAP_Lac_Ci;

typedef union
{
    BSSAP_Cgi           cgi;
    BSSAP_Lac_Ci        Lac_ci;
    BSSAP_Ci            ci;
    BSSAP_Plmn_Lac_Rnc  plmn_lac_rnc;
    BSSAP_Rnc           rnc;
    BSSAP_Lac_Rnc       lac_rnc;
    BSSAP_Sai           sai;
    BSSAP_Lai           lai;
    BSSAP_Lac           lac;
}
BSSAP_CellId_Type;
typedef struct
{
     U8bit    resource_type;
     U8bit    num_of_channels[2];
}
BSSAP_ResSitnElmnt;

typedef struct
{
U8bit data[100];

}
BSSMAP_Data;
/******************************

BSSMAP ELEMENTS

*******************************/
typedef struct
{
  U8bit  cic[2];
}
BSSAP_CircuitIdentityCode;

typedef struct
{
 BSSAP_Full_Half    data_field[5];
}
BSSAP_ResourceAvailable;
typedef struct
{
 U8bit  cause_val[1];
 U8bit  national_use;/*not using now*/
}
BSSAP_Cause;
typedef struct
{
  U8bit     cell_id_discriminator;
  BSSAP_CellId_Type  cell_id;
}
BSSAP_CellIdentifier;

typedef struct
{
 U8bit priorty;
}BSSAP_Priority;
typedef struct
{
 U8bit layer3_info[1];
}
BSSAP_Layer3HeaderInfo;
typedef struct
{
 U8bit digits[1];
}
BSSAP_Imsi;
typedef struct
{
 U8bit digits[1];
}
BSSAP_Tmsi;
typedef struct
{
    U8bit    permittedAlgorithms;
    U8bit    key[1];
}
BSSAP_EncryptionInfo;
typedef struct
{
  U8bit   speech_or_data;
  U8bit   chan_rate_type;
  U8bit   permit_ind_rate[9];
}
BSSAP_ChannelType;
typedef struct
{
 U8bit    data;
}
BSSAP_Periodicity;
typedef struct
{
 U8bit    data_field[1];
}
BSSAP_ExtendedResourceIndicator;
typedef struct
{
  U8bit    numOfMSs;
}
BSSAP_NumberOfMs;
typedef struct
{
  U8bit  data_4field;   /*Has Revision level, ES, A5/1, RF cap.*/
  U8bit  data_6field_1; /*Has PS cap., SS ind., SM cap.,VBS, VGCS, FC*/
  U8bit  data_6field_2; /*Has CM3, LCSVA cap., SoLSA, CMSP, A5/3, A5/2*/
}
BSSAP_ClassmarkInfoType2;
typedef struct
{
    U8bit  data_field1_2[2];
    U8bit  data_field2_2[1];
    U8bit  data_field3_4[2];
}
BSSAP_ClassmarkInfoType3;
typedef struct
{
  U8bit    band_to_be_used;
}
BSSAP_InterferenceBandToBeUsed;
typedef struct
{
 U8bit    rr_cause;
}
BSSAP_RRCause;
typedef struct
{
 U8bit    layer3_info[1];
}
BSSAP_Layer3Information;
typedef struct
{
 U8bit    downLink_DTX;
}
BSSAP_DownLinkDTX;
typedef struct
{
    U8bit    MCC[2];    /* Mobile COuntry Code*/
    U8bit    MNC;       /* Mobile Network Code*/
    U8bit    LAC[2];    /* Location Area Code*/
    U8bit    CI[2];     /* Cell Identity*/
}
BSSAP_CellGlobalId;

typedef union
{
    BSSAP_CellGlobalId  cgi;
    BSSAP_Lac_Ci        lac_ci;
    BSSAP_Ci            ci;
    BSSAP_Lai           lai;
    BSSAP_Lac           lac;
    BSSAP_Plmn_Lac_Rnc  plmn_lac_rnc;
    BSSAP_Rnc           rnc;
    BSSAP_Lac_Rnc       lac_rnc;
}
BSSAP_CellIDT;

typedef struct
{
 U8bit         cell_id_discriminator;
 BSSAP_CellIDT      cell_id[1];
}
BSSAP_CellIdentifierList;
typedef struct
{
  U8bit dummy;
}
BSSAP_ResponseRequest;
typedef struct
{
 U8bit    resource_ind_method;
}
BSSAP_ResourceIndicationMethod;
typedef struct
{
  U8bit data_4field;  /* Has Revision level, ES, A5/1, RF cap. */
}
BSSAP_ClassmarkInfoType1;
typedef struct
{
    U8bit    range;
    U8bit    status[1];
}
BSSAP_CircuitIdentityCodeList;
typedef struct
{
   U8bit    error_pointer[2];
   U8bit    message_received[1];
}
BSSAP_Diagnostic;
typedef struct
{
 U8bit   l3MsgCnt[1];
}
BSSAP_Layer3MsgContent;
typedef struct
{
  U8bit    data_2field;
}
BSSAP_ChosenChannel;
typedef struct
{
  U8bit dummy;

}
BSSAP_TotalResourceAccessible;
typedef struct
{
  U8bit    cipher_resp_mode;
}
BSSAP_CipherResponseMode;
typedef struct
{
  U8bit    channel;
}
BSSAP_ChannelNeeded;
typedef struct
{
 U8bit   traceType;
}
BSSAP_TraceType;
typedef struct
{
 U8bit    entityId[1];
}
BSSAP_TriggerId;
typedef struct
{
 U8bit    traceRef[2];
}
BSSAP_TraceRefernce;
typedef struct
{
  U8bit    transId[2];
}
BSSAP_TransactionId;
typedef struct
{
  U8bit    data_3field;
  U8bit    digit[1];
}
BSSAP_MobileIdentity;
typedef struct
{
 U8bit    omcId[1];
}
BSSAP_OmcId;
typedef struct
{
 U8bit    forwardInd;
}
BSSAP_ForwardIndicator;
typedef struct
{
 U8bit    algorithmId;
}
BSSAP_ChosenEncryptAlgorithm;
typedef struct
{
 U8bit    circuitPoolNum;
}
BSSAP_CircuitPool;
typedef struct
{
  BSSAP_CircuitPool    cktPlList[1];
}
BSSAP_CircuitPoolList;
typedef struct
{
  U8bit    time;
}
BSSAP_TimeIndication;
typedef struct
{
 BSSAP_ResSitnElmnt    res_sitn[1];
}
BSSAP_ResourceSituation;
typedef struct
{
  U8bit    data_2field;
}
BSSAP_CurrentChannelType1;
typedef struct
{
   U8bit    data_1field;
}
BSSAP_QueuingIndicator;
typedef struct
{
    U8bit    data_1field;
}
BSSAP_SpeechVersion;
typedef struct
{
 U8bit    data_1field;
}
BSSAP_AssignementRequirement;
typedef struct
{
  U8bit dummy;
}
BSSAP_TalkerFlag;
typedef struct
{
 U8bit    data_5field[5];
}
BSSAP_GroupCallReference;
typedef struct
{
 U8bit    call_pri;
}
BSSAP_emlppPriorty;
typedef struct
{
 U8bit    smi;
}
BSSAP_ConfigEvolutionInd;
typedef struct
{
  U8bit dummy;

}
BSSAP_OldBssToNewBssInfo;
typedef struct
{
  U8bit dummy;

}
BSSAP_IEI_LSA_INFORMATION_LIST;
typedef struct
{

    U8bit   vert;
     U8bit   ha_horacc;
     U8bit   va_vertacc;
     U8bit   rt;
}
BSSAP_LcsQos;
typedef struct
{
  U8bit   emergency;
}
BSSAP_LsaAccessCtrlSuppr;
typedef struct
{
  U8bit   priority[1];
}
BSSAP_LcsPriorty;
typedef struct
{
  U8bit   loc_info;
     U8bit   pos_mthd;
}
BSSAP_LocationType;
typedef struct
{
  U8bit   loc_est[1];
}
BSSAP_LocationEstimate;
typedef struct
{
   U8bit   pos_data_discr;
     U8bit   pos_mthd[1];
}
BSSAP_PositioningData;
typedef struct
{
 U8bit   cause_value;
     U8bit   diag_value;
}
BSSAP_LcsCause;
typedef struct
{
 U8bit   client_cat_subtype;
}
BSSAP_LcsClientType;
typedef struct
{
  U8bit   prot_id;
  U8bit   embed_msg[1];
}
BSSAP_Apdu;
typedef struct
{
    U8bit    MCC[2];    /* Mobile Country Code*/
    U8bit    MNC;       /* Mobile Network Code*/
    U8bit    LAC[2];    /* Location Area Code*/
}
BSSAP_LAI;

typedef struct
{
    U8bit    LAC[2];    /* Location Area Code*/
}
BSSAP_LAC;

typedef union
{
    BSSAP_CellGlobalId  cgi;
    BSSAP_Lac_Ci        lac_ci;
    BSSAP_LAI           lai;
    BSSAP_LAC           lac;
}
BSSAP_NetID;
typedef struct
{
 U8bit         id_discriminator;
    BSSAP_NetID       net_elmnt_id;
}
BSSAP_NetworkElementIdentity;
  typedef struct
  {
     U8bit    keyFlag;
     U8bit    crrtKeyValue[7];
     U8bit    nextKeyValue[7];
  }
BSSAP_DecphieringKeys;
typedef struct
{
 U8bit    errorType;
}
BSSAP_RetrunErrorRequest;
typedef struct
{
 U8bit    causeValue;
}
BSSAP_RetrunErrorCause;
typedef struct
{
 U8bit  seg_msg_info[3];
}
BSSAP_Segmentation;
typedef struct
{
 U8bit    shi;
}
BSSAP_ServiceHandover;
typedef struct
{
 U8bit    rnc_umts_info[1];
}
BSSAP_SrcRncToTgtRncInfoUmts;
typedef struct
{
 U8bit    rnc_cdma_info[1];
}
BSSAP_SrcRncToTgtRncInfoCdma;
typedef struct
{
  U8bit dummy;

}
BSSAP_GeranClassmark;
typedef struct
{
  U8bit dummy;

}
BSSAP_GeranBscContainer;
typedef struct
{
  U8bit dummy;

}
BSSAP_NewBssToOldBssInfo;
typedef struct
{
 U8bit    transp_cont[1];
}
BSSAP_InterSystemInfo;
typedef struct
{
    U8bit    lsa_id[3];
}
BSSAP_LSAIdentifier;

typedef struct
{
    U8bit              ep;
    BSSAP_LSAIdentifier    lsa_id[1];
}
BSSAP_LSAIdentifierList;
typedef struct
{
 U8bit SpeechCodeElem[1];
}
BSSAP_SpeechCodecElem;
typedef struct
{
BSSAP_SpeechCodecElem  SpeechCodec[1];
}
BSSAP_SpeechCodec;
typedef struct
{
U8bit addr[4];
U8bit port[2];
}
BSSAP_Aoip_Ip;
typedef struct
{
U8bit priorty;

}
BSSAP_TalkerPriority;
typedef struct
{
 BSSAP_SpeechCodec speechcodeclist[1];

}
BSSAP_SpeechCodecList;
typedef struct
{
U32bit callId;
}
BSSAP_CallIdentifier;

typedef struct
{

 BSSAP_CallIdentifier calllist[1];
}
BSSAP_CallIdentifierList;
typedef struct
{
 U8bit profileId;

}
BSSAP_ProfileId;
typedef struct
{
 U8bit indicator;

}
BSSAP_Aif_Selector;
typedef struct
{
 U8bit x;
}
BSSAP_SnaAccessInfo;
#ifdef LCLS_PARAM_DECODE
typedef struct
{
 U8bit kc128[16];
}BSSAP_KC128;

typedef struct
{
 U8bit gcr[1];
  
}BSSAP_GlbCallRef;

typedef struct
{
U8bit lcls_config;
}BSSAP_LcLsConfig;

typedef struct
{
 U8bit lcls_conn_status_cntrl;
}BSSAP_LcLsConnStatCntrl;

typedef struct
{
 U8bit  lcls_correlation_flg;
}BSSAP_LcLsCorrelNotNeed;
typedef struct
{
 U8bit  lcls_break_req;
}BSSAP_LcLsBrkReq;
typedef struct
{
 U8bit lcls_bss_status;
}BSSAP_LcLsBssStatus;

#endif



typedef struct
{
  U8bit  mDisc;
  U8bit dlci;
  U8bit l3h;
  U8bit msgType;
}
BSSAP_Hdr;

typedef struct
{
    U8bit   param_id;
    U8bit   param_length;
    union
   {
     /*BSSMAP_Data                         ie_data;*/
     BSSAP_CircuitIdentityCode            cic ;
     BSSAP_ResourceAvailable              res_avail;
     BSSAP_Cause                          cause;
     BSSAP_CellIdentifier                 cell_id;
     BSSAP_Priority                        priority;
     BSSAP_Layer3HeaderInfo               l3h;
     BSSAP_Imsi                           imsi;
     BSSAP_Tmsi                           tmsi;
     BSSAP_EncryptionInfo                 encry_info;
     BSSAP_ChannelType                    chanl_type;
     BSSAP_Periodicity                    periodicity;
     BSSAP_ExtendedResourceIndicator      exd_res_ind;
     BSSAP_NumberOfMs                     no_ms;
     BSSAP_ClassmarkInfoType2             clsmrk_info_2;
     BSSAP_ClassmarkInfoType3             clsmrk_info_3;
     BSSAP_InterferenceBandToBeUsed       intf_band_used;
     BSSAP_RRCause                        rr_cause;
     BSSAP_Layer3Information              l3_info;
     BSSAP_DownLinkDTX                    dtx_flag;
     BSSAP_CellIdentifierList             cellid_list;
     BSSAP_ResponseRequest                resp_req  ;
     BSSAP_ResourceIndicationMethod       resid_method;
     BSSAP_ClassmarkInfoType1             clsmrk_info_type1 ;
     BSSAP_CircuitIdentityCodeList        cic_list;
     BSSAP_Diagnostic                       diagno;
     BSSAP_Layer3MsgContent               layer3_msgcnt;
     BSSAP_ChosenChannel                   chosn_channl;
     BSSAP_TotalResourceAccessible        tot_res_access;
     BSSAP_CipherResponseMode             ciphr_respmode;
     BSSAP_ChannelNeeded                   channel_needed;
     BSSAP_TraceType                       trace_type;
     BSSAP_TriggerId                       trgg_id;
     BSSAP_TraceRefernce                  trace_ref;
     BSSAP_TransactionId                   trans_id;
     BSSAP_MobileIdentity                  mob_id;
     BSSAP_OmcId                           omc_id;
     BSSAP_ForwardIndicator                forwd_ind;
     BSSAP_ChosenEncryptAlgorithm      chosen_encry_algo;
     BSSAP_CircuitPool                     cirt_pool;
     BSSAP_CircuitPoolList                cirt_pool_list;
     BSSAP_TimeIndication                  time_ind;
     BSSAP_ResourceSituation               res_situt;
     BSSAP_CurrentChannelType1           cur_chnl_1;
     BSSAP_QueuingIndicator                qung_ind;
     BSSAP_SpeechVersion                   spch_ver;
     BSSAP_AssignementRequirement           assgn_req;
     BSSAP_TalkerFlag                      tlkr_flag;
     BSSAP_GroupCallReference             grp_call_ref;
     BSSAP_emlppPriorty                   eMlpp_priorty;
     BSSAP_ConfigEvolutionInd      confg_evlt_ind;
     BSSAP_OldBssToNewBssInfo          oldtonew_bss;
     BSSAP_LSAIdentifier                   lsa_id;
     BSSAP_LSAIdentifierList              lsa_id_list;
     BSSAP_LcsQos                          lcs_qos;
     BSSAP_LsaAccessCtrlSuppr            lsa_accs_ctrl;
     BSSAP_LcsPriorty                      lcs_priorty;
     BSSAP_LocationType                    loctn_type;
     BSSAP_LocationEstimate                loctn_est;
     BSSAP_PositioningData                 post_data;
     BSSAP_LcsCause                        lcs_cause;
     BSSAP_LcsClientType                  lcs_clntype;
     BSSAP_Apdu                             apdu;
     BSSAP_NetworkElementIdentity         new_elm_id;
     BSSAP_DecphieringKeys                 decph_keys;
     BSSAP_RetrunErrorRequest             ret_err_req;
     BSSAP_RetrunErrorCause               ret_err_cause;
     BSSAP_Segmentation                     seg;
     BSSAP_ServiceHandover                 serv_hand;
     BSSAP_SrcRncToTgtRncInfoUmts     srctotgt_rnc_umts;
     BSSAP_SrcRncToTgtRncInfoCdma     srctotgt_rnc_cdma;
     BSSAP_GeranClassmark                  geran_clssmrk;
     BSSAP_GeranBscContainer              geran_bsc_cont;
     BSSAP_NewBssToOldBssInfo          newtoold_bss;
     BSSAP_InterSystemInfo                int_sys_info;
     BSSAP_SnaAccessInfo                  sna_accs_info;
     BSSAP_TalkerPriority                 talker_pririty;
     BSSAP_Aoip_Ip                        aoip_addr;
     BSSAP_SpeechCodec                    speech_codec;
     BSSAP_SpeechCodecList                speech_codec_list;
     BSSAP_CallIdentifier                 call_id;
     BSSAP_CallIdentifierList             call_id_list;
     BSSAP_ProfileId                      profileId;
     BSSAP_Aif_Selector                   aif_selector;
#ifdef LCLS_PARAM_DECODE
     BSSAP_KC128                          kc128;
     BSSAP_GlbCallRef                     glbcallref;
     BSSAP_LcLsConfig                     lclsconfig;
     BSSAP_LcLsConnStatCntrl              connstatcntrl;
     BSSAP_LcLsCorrelNotNeed              correlnotneed;    
#endif
   }
   param_data;
}BSSAP_IE;

typedef struct addIeParam
{
   U8bit cause;
   BSSAP_CircuitIdentityCode cic;
   BSSAP_CircuitIdentityCodeList  cic_list;
   BSSAP_Diagnostic diagno;
   U8bit diagbuflen;
   U8bit cicListlen;
}AddIeParam;

#if 0
/*Function Prototype */
EXTERN S16 BsDecode ARGS((Data *buf,U8bit len,BSSAP_IE *ies,S16 *iecount,BSSAP_Hdr *hdr));
EXTERN S16 BsEncode ARGS((U8bit msgtype,AddIeParam *ieparamlist,Data *databuf,MsgLen *datalen));

EXTERN S16 BsProcessInBSSAPMessage ARGS((BsCallCb *call,Buffer *mBuf,BsIntfCb *intfCb,U8bit rcause,U8bit sccpMsgType));
EXTERN Void BsHandleDecodeFailure ARGS((BsCallCb *call,BSSAP_Hdr *hdr,Data *databuff,MsgLen dataLen,BsIntfCb *intfCb,S16 retcause));
EXTERN S16 BsProcessInBSSMAPMessage ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsIntfCb *intfCb,Data *databuff,MsgLen dataLen,U8bit mType));
EXTERN S16 BsProcessInBSSMAPUDTMessage ARGS((BSSAP_IE *ie,S16 iecount,BsIntfCb *intfCb,Data *databuff,MsgLen dataLen,U8bit mType));
EXTERN Void BsSendFailureMsg ARGS((BsCallCb *call,U8bit msgtype,S16  errcause,Data *buffer,MsgLen bufLen,BsNSAPCb *sCb));
EXTERN Void BsIncrPegsCounter ARGS((U8bit isDtapMsgFlag,U8bit msgtype,U8bit directionFlag,BsIntfCb *intfCb));
EXTERN Void BsSendCktMsg ARGS((U8bit msgType,U16 cic,BSSAP_IE *ieCicList,BsNSAPCb *sCb));
EXTERN S16 BsSendUDataReq ARGS((BsNSAPCb *sCb,Data *sndBuf,MsgLen sndbufLen));
EXTERN S16 BsProcessOutBSSAPMessage ARGS((BSSAPData *bdata,BsNSAPCb *sCb));
EXTERN S16 BsSendConResp ARGS((SpConId *conId,BsNSAPCb   *sCb));
EXTERN S16 BsSendDisReq ARGS((SpConId *conId,U8bit sccpMsgType,BsNSAPCb   *sCb));
EXTERN S16 BsSendConReq ARGS((BsNSAPCb *sCb,Data *sndBuf,MsgLen sndbufLen,U32 callref));


EXTERN S16 BsProcessAssignmentRequest ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessAssignmentComplete ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessHandoverRequest ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,Data *databuff,
                                          MsgLen dataLen,BsNSAPCb *sCb));

EXTERN S16 BsProcessHandoverRequired ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessHandoverReqAck ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessHandoverFailure ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessHandoverPerformed ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessAssignmentFailure ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessClearCommand ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessClearRequest ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessCompleteLayer3Info ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb,Data *databuf,MsgLen  buflen));
EXTERN S16 BsProcessChangeCircuitAck ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessOverloadInd ARGS((BsNSAPCb *sCb));
EXTERN U8bit  BsGetStatusBit ARGS((U16 startcic,U16 Endcic,BSSAP_IE *ielist));
EXTERN Void BsSetStatusBit ARGS((BSSAP_IE *ieCiclist,U8bit type,U32 bitn));
EXTERN S16 BsProcessBlockRequest ARGS((BSSAP_IE *ie,S16 iecount,Data *databuff,MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessBlockAckInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessUnBlockRequest ARGS((BSSAP_IE *ie,S16 iecount,Data *databuff,MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessUnBlockAckInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessBlockInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessBlockAckReq ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessUnBlockInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessUnBlockAckReq ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetCktReq ARGS((BSSAP_IE *ie,S16 iecount,Data *databuff,MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetCktAckInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetCktInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetCktAckReq ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetReq ARGS((BSSAP_IE *ie,S16 iecount,Data *databuff,MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetAckInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetAckReq ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessUnequippedCktReq ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetIPReq ARGS((BSSAP_IE *ie,S16 iecount,Data *databuff,MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessResetIPAckInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessInternalHandoverRequired ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,Data *databuff,
                                          MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessInternalHandoverRequiredReject ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,Data *databuff,
                                          MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessInternalHandoverCmd ARGS((BsCallCb *call,BSSAP_IE *ie,S16 iecount,Data *databuff,
                                          MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessUnequippedCktInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN BSSAP_IE* BsFindIE ARGS((BSSAP_IE *ie,S16  iecount,U8bit  ieParamId));
EXTERN S16 BsProcessCktGroupBlockReq ARGS((BSSAP_IE *ie,S16 iecount,Data *databuff,MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessCktGroupUnblockReq ARGS((BSSAP_IE *ie,S16 iecount,Data *databuff,MsgLen dataLen,BsNSAPCb *sCb));
EXTERN S16 BsProcessCktGroupBlockInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessCktGroupBlockAckInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessCktGroupUnBlockInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));
EXTERN S16 BsProcessCktGroupUnBlockAckInd ARGS((BSSAP_IE *ie,S16 iecount,BsNSAPCb *sCb));

#ifdef ZS_DFTHA
EXTERN S16 zsActvTsk ARGS((Pst *pst,Buffer *mBuf));
#endif

#endif /* Commented by Amaresh */
#endif /*End of __BSSAPCOMX__*/


