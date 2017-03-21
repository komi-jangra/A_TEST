/* syntax test of BSSAP.h */

#include <iostream.h>

#include <its.h>
#include <BSSAP.h>

main()
{
    ITS_BSSAP_IE            test;
    int                     y=200;
    BSSAP_CellIdentifier    cid;
    ITS_OCTET               x;
    
    /* ------------ Circuit Identity Code 3.2.2.2 ------------*/
    CIC_SET_PCM_ID(test.param_data.circuitIdentityCode, 2);
    CIC_GET_PCM_ID(test.param_data.circuitIdentityCode);

    CIC_SET_TIMESLOT(test.param_data.circuitIdentityCode, 3);
    CIC_GET_TIMESLOT(test.param_data.circuitIdentityCode);


    /* ----------- Connection Release Requested 3.2.2.3 ----------*/
    // No data.

  
    /* ------------ Resource Available 3.2.2.4 -------------*/
    RA_SET_FULL_HALF_RATE_CHANNELS_AVAILABLE_FOR_BAND
                  (test.param_data.resourceAvailable, 0, 20, 30);
    RA_GET_FULL_RATE_CHANNELS_AVAILABLE_FOR_BAND
                         (test.param_data.resourceAvailable, 0);
    RA_GET_HALF_RATE_CHANNELS_AVAILABLE_FOR_BAND
                         (test.param_data.resourceAvailable, 0);
  

    /* ------------ Cause 3.2.2.5 -------------*/
    C_SET_EXTENSION(test.param_data.cause,C_IS_EXTENDED);
    C_GET_EXTENSION(test.param_data.cause);
    
    C_SET_BASIC_CAUSE(test.param_data.cause, 100);
    C_GET_BASIC_CAUSE(test.param_data.cause);
    
    C_SET_EXT_CAUSE_CLASS(test.param_data.cause,200);
    C_GET_EXT_CAUSE_CLASS(test.param_data.cause);

    C_SET_EXT_CAUSE(test.param_data.cause,C_UPLINK_QUALITY);
    C_GET_EXT_CAUSE(test.param_data.cause);

    
    /* ------------ IMSI 3.2.2.6 -------------*/
    // Fix me.


    /* ------------ TMSI 3.2.2.8 -------------*/
    // Fix me.

    
    /* ------------ Number Of MSs 3.2.2.7 -------------*/
    // No macro.

    
    /* --------- Layer 3 Header Information 3.2.2.9 -------------*/
    PD_SET_PROT_DISCR(x,y);
    PD_GET_PROT_DISCR(x);
    
    TI_SET_TI_VALUE(x,y);
    TI_GET_TI_VALUE(x);
   
    TI_SET_TI_FLAG(x,y);
    TI_GET_TI_FLAG(x);

    L3HI_SET_PROT_DISCR(test.param_data.layer3HeaderInfo,y);
    L3HI_GET_PROT_DISCR(test.param_data.layer3HeaderInfo);
    
    L3HI_SET_TRAN_ID_VALUE(test.param_data.layer3HeaderInfo,y);
    L3HI_GET_TRAN_ID_VALUE(test.param_data.layer3HeaderInfo);
   
    L3HI_SET_TRAN_ID_FLAG(test.param_data.layer3HeaderInfo,y);
    L3HI_GET_TRAN_ID_FLAG(test.param_data.layer3HeaderInfo);


    /* ------------ Encryption Information 3.2.2.10 -------------*/
    EI_SET_ALGORITHM_ID(test.param_data.encryptionInfo,EI_GSM_A5_1);
    EI_GET_ALGORITHM_ID(test.param_data.encryptionInfo);


    // Fix me.
     /* --------- Channel Type 3.2.2.11-------------*/
    


     /* ------------ Periodicity 3.2.2.12-------------*/
    P_SET_PERIODICITY(test.param_data.periodicity,y);
    P_GET_PERIODICITY(test.param_data.periodicity);


    /* --------- Extended Resource Indicator 3.2.2.13-------------*/
    ERI_SET_TARR(test.param_data.extendedResInd,y);
    ERI_GET_TARR(test.param_data.extendedResInd);

    ERI_SET_SM(test.param_data.extendedResInd,y);
    ERI_GET_SM(test.param_data.extendedResInd);
  		    

    
    /* --------- Total Resource Accessible 3.2.2.14-------------*/
    TRA_SET_FULL_RATE_CHANNELS(test.param_data.totalResAccessible,y);
//    TRA_GET_FULL_RATE_CHANNELS(test.param_data.totalResAccessible);
// Fix me later.  	
    TRA_SET_HALF_RATE_CHANNELS(test.param_data.totalResAccessible,y);
//    TRA_GET_HALF_RATE_CHANNELS(test.param_data.totalResAccessible);


    // Temp keep all. Fix me later.
    /* --------- Cell Identifier 3.2.2.15-------------*/
/*    CID_CGI_SET_MCC(test.param_data.cid.cell_id,y);
    CID_CGI_GET_MCC(test.param_data.cid.cell_id);
	
    CID_CGI_SET_MNC(test.param_data.cid.cell_id,y);
    CID_CGI_GET_MNC(test.param_data.cid.cell_id);

    CID_CGI_SET_LAC(test.param_data.cid.cell_id,y);
    CID_CGI_GET_LAC(test.param_data.cid.cell_id);

    CID_CGI_SET_CI(test.param_data.cid.cell_id,y);
    CID_CGI_GET_CI(test.param_data.cid.cell_id);

    CID_LACCI_SET_LAC(test.param_data.cid.cell_id,y);
    CID_LACCI_GET_LAC(test.param_data.cid.cell_id);

    CID_LACCI_SET_CI(test.param_data.cid.cell_id,y);
    CID_LACCI_GET_CI(test.param_data.cid.cell_id);

    CID_CI_SET_CI(test.param_data.cid.cell_id,y);
    CID_CI_GET_CI(test.param_data.cid.cell_id);

    CID_LAI_SET_MCC(test.param_data.cid.cell_id,y);
    CID_LAI_GET_MCC(test.param_data.cid.cell_id);

    CID_LAI_SET_MNC(test.param_data.cid.cell_id,y);
    CID_LAI_GET_MNC(test.param_data.cid.cell_id);

    CID_LAI_SET_LAC(test.param_data.cid.cell_id,y);
    CID_LAI_GET_LAC(test.param_data.cid.cell_id);

    CID_LAC_SET_LAC(test.param_data.cid.cell_id,y);
    CID_LAC_GET_LAC(test.param_data.cid.cell_id);

    CID_SET_CELL_ID_DISCRIMINATOR(test.param_data.cid,CID_LAI);
    CID_GET_CELL_ID_DISCRIMINATOR(test.param_data.cid);
*/

     /* --------- Priority 3.2.2.18-------------*/
    
    P_SET_PRIORITY(test.param_data.priority,P_PRI_LEVEL_1);
    P_GET_PRIORITY(test.param_data.priority);

    P_SET_QUEUING(test.param_data.priority,P_QUEUING_ALLOWED);
    P_GET_QUEUING(test.param_data.priority);

    P_SET_PREEMPTION_CAPABILITY(test.param_data.priority,P_NO_PREEMPTION);
    P_GET_PREEMPTION_CAPABILITY(test.param_data.priority);

//    P_SET_PREEMPTION_VULNERABILITY(test.param_data.priority, **//Fix me);
    P_GET_PREEMPTION_VULNERABILITY(test.param_data.priority);


    /* --------- Classmark Information Type 2 3.2.2.19 -------------*/
    CIT2_SET_REV_LEVEL(test.param_data.classmarkInfo2,CIT2_REV_LEVEL_PHASE_1);
    CIT2_GET_REV_LEVEL(test.param_data.classmarkInfo2);
	
    CIT2_SET_ES_IND(test.param_data.classmarkInfo2,CIT2_ES_IND_IS_IMPLEMENTED);
    CIT2_GET_ES_IND(test.param_data.classmarkInfo2);
	
    CIT2_SET_A5_1_IND(test.param_data.classmarkInfo2,CIT2_A5_1_IS_AVAILABLE);
    CIT2_GET_A5_1_IND(test.param_data.classmarkInfo2);
	
    CIT2_SET_RF_POWER_CAP(test.param_data.classmarkInfo2,
                                        CIT2_RF_POWER_CAP_CLASS1);
    CIT2_GET_RF_POWER_CAP(test.param_data.classmarkInfo2);
	
    CIT2_SET_PS_CAP(test.param_data.classmarkInfo2,CIT2_PS_CAP_PRESENT);
    CIT2_GET_PS_CAP(test.param_data.classmarkInfo2);
	
    CIT2_SET_SS_SCREEN_IND(test.param_data.classmarkInfo2,
                                                CIT2_SS_SCREEN_IND_1);
    CIT2_GET_SS_SCREEN_IND(test.param_data.classmarkInfo2);
	
    CIT2_SET_SM_CAP(test.param_data.classmarkInfo2,CIT2_SM_CAP_SUPPORTED);
    CIT2_GET_SM_CAP(test.param_data.classmarkInfo2);
	
    CIT2_SET_VBS_CAP(test.param_data.classmarkInfo2,CIT2_VBS_CAP_NEEDED);
    CIT2_GET_VBS_CAP(test.param_data.classmarkInfo2);
	
    CIT2_SET_VGCS_CAP(test.param_data.classmarkInfo2,CIT2_VGCS_CAP_NEEDED);
    CIT2_GET_VGCS_CAP(test.param_data.classmarkInfo2);
	
    CIT2_SET_FC(test.param_data.classmarkInfo2,CIT2_FC_SUPPORTED);
    CIT2_GET_FC(test.param_data.classmarkInfo2);
	
    CIT2_SET_CM3(test.param_data.classmarkInfo2,CIT2_CM3_OPTIONS_SUPPORTED);
    CIT2_GET_CM3(test.param_data.classmarkInfo2);

    CIT2_SET_LCS_VA_CAP(test.param_data.classmarkInfo2,
                                          CIT2_LCS_VA_CAP_SUPPORTED);
    CIT2_GET_LCS_VA_CAP(test.param_data.classmarkInfo2);

    CIT2_SET_SOLSA(test.param_data.classmarkInfo2,CIT2_SOLSA_SUPPORTED);
    CIT2_GET_SOLSA(test.param_data.classmarkInfo2);

    CIT2_SET_CMSP(test.param_data.classmarkInfo2,CIT2_CMSP_SUPPORTED);
    CIT2_GET_CMSP(test.param_data.classmarkInfo2);

    CIT2_SET_A5_3(test.param_data.classmarkInfo2,CIT2_A5_3_SUPPORTED);
    CIT2_GET_A5_3(test.param_data.classmarkInfo2);

    CIT2_SET_A5_2(test.param_data.classmarkInfo2,CIT2_A5_2_SUPPORTED);
    CIT2_GET_A5_2(test.param_data.classmarkInfo2);

    /* --------- Classmark Information Type 3 3.2.2.20-------------*/
    // Fix me later.


    /* --------- Interference Band to be used 3.2.2.21-------------*/
    P_SET_BAND_TO_BE_USED(test.param_data.bandToBeUsed,y);
    P_GET_BAND_TO_BE_USED(test.param_data.bandToBeUsed);


     /* --------- Source Radio Environment 3.2.2.22 -------------*/
    P_SET_RR_CAUSE(test.param_data.rrCause,RRC_PREEMPTIVE_RELEASE);
    P_GET_RR_CAUSE(test.param_data.rrCause);
  

    /* ------------ Layer 3 Information 3.2.2.24 -------------*/
    // Fix me later.


    /* ------------- DLCI 3.2.2.25 --------------*/
    DLCI_SET_CONTROL_CHANNEL(test.param_data.dlci,DLCI_SACCH);
    DLCI_GET_CONTROL_CHANNEL(test.param_data.dlci);   

    DLCI_SET_SAPI(test.param_data.dlci,y);
    DLCI_GET_SAPI(test.param_data.dlci); 


    /* ----------- Downlink DTX Flag 3.2.2.26 -------------*/
    DLDTX_SET_DOWNLINK(test.param_data.downLinkDTX,DLDTX_ACTIVATE_ALLOWED);
    DLDTX_GET_DOWNLINK(test.param_data.downLinkDTX);


    // Temp keep all. Fix me later.
     /* ----------- Cell Identifier List 3.2.2.27 -------------*/
/*    CIL_SET_CELL_ID_DISCRIMINATOR(test.param_data.cidList,y);
    CIL_GET_CELL_ID_DISCRIMINATOR(test.param_data.cidList);
*/   

    /* ------------ Resource Indication Method 3.2.2.29 -------------*/    
    RIM_SET_RES_IND_METHOD(test.param_data.resourceIndMethod,RIM_SUBCLAUSE_1);    
    RIM_GET_RES_IND_METHOD(test.param_data.resourceIndMethod);


    /* --------- Classmark Information Type 1 3.2.2.30-------------*/
    CIT1_SET_REV_LEVEL(test.param_data.classmarkInfo1,CIT1_REV_LEVEL_PHASE_1);
    CIT1_GET_REV_LEVEL(test.param_data.classmarkInfo1);

    CIT1_SET_ES_IND(test.param_data.classmarkInfo1,CIT1_ES_IND_IS_IMPLEMENTED);
    CIT1_GET_ES_IND(test.param_data.classmarkInfo1);

    CIT1_SET_A5_1_IND(test.param_data.classmarkInfo1,CIT1_A5_1_IS_AVAILABLE);
    CIT1_GET_A5_1_IND(test.param_data.classmarkInfo1);

    CIT1_SET_RF_POWER_CAP(test.param_data.classmarkInfo1,CIT1_RF_POWER_CAP_CLASS1);
    CIT1_GET_RF_POWER_CAP(test.param_data.classmarkInfo1);

    // Fix me later
    /* ----------- Circuit Identity Code List 3.2.2.31 -------------*/    
/*    CCL_SET_RANGE(test.param_data.circuitIdCodeList,16);    
    CCL_GET_RANGE(test.param_data.circuitIdCodeList);

    CCL_SET_STATUS(test.param_data.circuitIdCodeList,2);    
    CCL_GET_STATUS(test.param_data.circuitIdCodeList);
*/    

    /* ------------- Diagnostics 3.2.2.32 -------------*/    
    // Fix me later


    /* ----------- Chosen Channel 3.2.2.33 -------------*/    
    CC_SET_CHANNEL(test.param_data.chosenChannel,CC_CH_SPEECH);    
    CC_GET_CHANNEL(test.param_data.chosenChannel);

    CC_SET_CHANNEL_MODE(test.param_data.chosenChannel,CC_CM_NONE );    
    CC_GET_CHANNEL_MODE(test.param_data.chosenChannel);


    /* ----------- Cipher Response Mode 3.2.2.34 -------------*/
    CRM_SET_INDICATOR(test.param_data.cipherResponseMode,CRM_IMEISV_INLCUDED);
    CRM_GET_INDICATOR(test.param_data.cipherResponseMode);


    /* ------------ Channel Needed 3.2.2.36 -------------*/
    CN_CHANNEL_SET_CHANNEL_NEEDED(test.param_data.channelNeeded,
                                                      CN_CHANNEL_TCH_F);
    CN_CHANNEL_GET_CHANNEL_NEEDED(test.param_data.channelNeeded);


    /* ------------ Trace Type 3.2.2.37 -------------*/
    // Fix me later.


    /* ------------ Trigger ID 3.2.2.38 -------------*/
    // Fix me later.


    /* ------------ Trace Reference 3.2.2.39 -------------*/
    TR_SET_TRACE_REFERENCE(test.param_data.traceRef,y);
    TR_GET_TRACE_REFERENCE(test.param_data.traceRef);


     /* ------------ Transaction Identifier 3.2.2.40 -------------*/
    TI_SET_TRANSACTION_ID(test.param_data.transactionId,y);
    TI_GET_TRANSACTION_ID(test.param_data.transactionId);
   

    // Fix me later.
    /* ------------ Mobile Identity 6.2.2.41 -------------*/
/*    MI_SET_ODD_EVEN_IND(test.param_data.mid,EVEN_DIGITS);
    MI_GET_ODD_EVEN_IND(test.param_data.mid);

    MI_SET_TYPE_IDENTITY(test.param_data.mid,y);
    MI_GET_TYPE_IDENTITY(test.param_data.mid);
*/

    // Fix me later.
    /* ------------- OMCID 6.2.2.42 -------------*/

    
    /* ------------ Forward Indicator 3.2.2.43 -------------*/
    FI_FORWARD_SET_INDICATOR(test.param_data.forwardInd,FI_FORWARD_TRACE);
    FI_FORWARD_GET_INDICATOR(test.param_data.forwardInd);


     /* ----------- Chosen Encryption Algorithm 3.2.2.44 -------------*/
    CEA_SET_ENCRYPTION_ID(test.param_data.chosenEncryptAlgorithm,CEA_GSM_A_5_1);
    CEA_GET_ENCRYPTION_ID(test.param_data.chosenEncryptAlgorithm);   


     /* ------------- Circuit Pool 3.2.2.45 -------------*/
    CP_SET_CIRCUIT_POOL_NUM(test.param_data.circuitPool,CP_NUMBER_1);
    CP_GET_CIRCUIT_POOL_NUM(test.param_data.circuitPool);


    /* ------------- Circuit Pool List 3.2.2.46 -------------*/
    // Fix me.


    /* ------------- Time Indication 3.2.2.47 -------------*/
    TI_SET_TIME_VAL(test.param_data.timeInd,y);
    TI_GET_TIME_VAL(test.param_data.timeInd);
    

    /* ------------ Resource Situation 3.2.2.48 -------------*/
    // Fix me later. 


    /* ------------ Current Channel 3.2.2.49 -------------*/
    CC_CHANNEL_SET_CHANNEL_MODE(test.param_data.currentChannel,
                                                   CC_CHANNEL_MODE_SPEECH);
    CC_CHANNEL_GET_CHANNEL_MODE(test.param_data.currentChannel);

    CC_CHANNEL_SET_CHANNEL(test.param_data.currentChannel,CC_CHANNEL_SDCCH);
    CC_CHANNEL_GET_CHANNEL(test.param_data.currentChannel);


    /* ------------ Queuing Indicator 6.2.2.50 -------------*/
    QI_SET_QUEUING_IND(test.param_data.queuingInd,QI_QUEUING_ALLOWED);
    QI_GET_QUEUING_IND(test.param_data.queuingInd);


    /* ------------ Speech Version 3.2.2.51 -------------*/
    SV_SET_SPEECH_VERSION(test.param_data.speechVer,SV_GSM_FULL_RATE_VER1);
    SV_GET_SPEECH_VERSION(test.param_data.speechVer); 


    /* ------------ Assignment Requirement 3.2.2.52 -------------*/
    AR_SET_ASSIGNMENT_REQUIREMENT(test.param_data.assignmentRequirement,
                                                               AR_DELAYED);
    AR_GET_ASSIGNMENT_REQUIREMENT(test.param_data.assignmentRequirement);


    /* ------------- Talker Flag 3.2.2.54 -------------*/
    // No macro.


    /* ------------- Group Call Reference 3.2.2.55 -------------*/
    GCR_SET_CALL_REFERENCE(test.param_data.groupCallRef,y);
    GCR_GET_CALL_REFERENCE(test.param_data.groupCallRef);

    GCR_SET_SF(test.param_data.groupCallRef,GCR_SF_VBS);
    GCR_GET_SF(test.param_data.groupCallRef);

    GCR_SET_AF(test.param_data.groupCallRef,GCR_AF_ACK_REQUIRED);
    GCR_GET_AF(test.param_data.groupCallRef);

    GCR_SET_CALL_PRIORITY(test.param_data.groupCallRef,
                                      GCR_CALL_PRIORITY_LEVEL_A);
    GCR_GET_CALL_PRIORITY(test.param_data.groupCallRef);

    GCR_SET_CIPHERING_KEY(test.param_data.groupCallRef,
                                           GCR_CIPHERING_KEY_9);
//    GCR_GET_CIPHERING_KEY(test.param_data.groupCallRef); Fix me later.

   
     /* ------------ eMLPP Priority 3.2.2.56 -------------*/
    EP_SET_CALL_PRIORITY(test.param_data.eMLPP_pri,y);
    EP_GET_CALL_PRIORITY(test.param_data.eMLPP_pri);


    /* ---------- Configuration Evolution Indication 3.2.2.57 ---------*/
    CE_SET_MODIFICATION_IND(test.param_data.configEvolutionInd,
                                                 CE_NO_MODIFICATION_ALLOWED);
    CE_GET_MODIFICATION_IND(test.param_data.configEvolutionInd);

    return 0;
}