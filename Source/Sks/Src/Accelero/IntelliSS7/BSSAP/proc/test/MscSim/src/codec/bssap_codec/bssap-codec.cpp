/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: bssap-codec.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:42  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.8  2005/11/30 12:11:00  adutta
 * LOG: Codec modified by SS
 * LOG:
 * LOG: Revision 1.1.2.6  2005/11/08 07:30:04  adutta
 * LOG: Added ciruit/location update messages
 * LOG:
 * LOG: Revision 1.1.2.5  2005/10/14 10:08:59  adutta
 * LOG: Modified for DTAP messages
 * LOG:
 * LOG: Revision 1.1.2.4  2005/10/11 13:46:38  adutta
 * LOG: buffer size increased
 * LOG:
 * LOG: Revision 1.1.2.3  2005/10/11 11:03:01  adutta
 * LOG: Added new messages for MSc
 * LOG:
 *
 * LOG:
 ****************************************************************************/

#include <iostream>
#include <its++.h>
#include <AppCodec.h>
#include <BSSAPPrint.h>

#if defined(ITS_STD_NAMESPACE)

using namespace std;
using namespace its;

#endif

#define BSSAP_MSG_ASSIGN_REQ       0xF1U
#define BSSAP_MSG_CLEAR_CMP        0xF2U
#define BSSAP_MSG_ASSIGN_CMP       0xF3U
#define BSSAP_MSG_HANDOVER_CMP     0xF4U
#define BSSAP_MSG_HANDOVER_DET     0xF5U
#define BSSAP_MSG_HANDOVER_REQ_ACK 0xF6U
#define BSSAP_MSG_HANDOVER_FAIL    0xF7U
#define BSSAP_MSG_ASSIGN_FAIL      0xF8U
#define BSSAP_MSG_LOCATION_UPDATION_REQ 0xF9U
#define BSSAP_MSG_LOCATION_UPDATING_ACCEPT 0xFAU

static void DecodeParams(ITS_OCTET* buf, int len);
static void SetParams(int val, BSSAP_Message* msg);
static void GetParams(int val, BSSAP_Message* msg);
static void EncodeParams(BSSAP_Message* msg, ITS_OCTET* buf, int *len);

/*****************************************************************************
 *  Purpose:
 *      This function is used for building the Assignment Request
 *
 *  Input Parameters:
 *     None
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      msg -  Filled in BSSAP message.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
static void
BuildAssignmentRequest(BSSAP_Message* msg)
{
    ITS_OCTET                octet = 0x11U;
    ITS_USHORT               ushort  = 0x228U;
    ITS_UINT                 uint = 0x4321000;
    BSSAP_ChanType           chanType;
    BSSAP_L3HeaderInfo       l3hInfo;
    BSSAP_Prio               prio;
    BSSAP_CktIDCode          cktId;
    BSSAP_DLDTXFlag          dlFlag;
    BSSAP_ClassmarkInfo2     cmInfo2;
    BSSAP_GrpClRef           gcRef;
    BSSAP_TalkerFlag         tkFlag;
    BSSAP_InterBandToBeUsed  itBand;
    BSSAP_ConfigEvlInd       ceInd;

    // message
    BSSAP_AssignmentRequest *assReq = (BSSAP_AssignmentRequest*)msg;

    // populate Channel Type, add it to the message
    chanType.SetSpeechDataID(CT_DATA);                             //0x02
    chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);    //0x08
    chanType.SetDataTransp(1, CT_DATA_MAX_ALLOWED_CHANNEL1, 1);    //0x20
    chanType.SetIFDateRate(1, 0x53);                               //0x53
    chanType.SetAsymInd(0, 0x02);                                  //0x02
    assReq->AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);

    // populate Layer 3 Header Information, add it to the message
    l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    l3hInfo.SetTIVal(TI_VALUE_3);                      //0x03
    l3hInfo.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
    assReq->AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

    // populate Priority, add it to the message
    prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
    prio.SetQA(P_QUEUING_ALLOWED);                      //0x01
    prio.SetPCI(P_PREEMPTION_ALLOWED);                  //0x01
    prio.SetPVI(P_CONN_BE_REQ);                         //0x01
    assReq->AddIE(BSSAP_IEI_PRIORITY, &prio);

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x11
    assReq->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    // populate Downlink DTX Flag, add it to the message
    dlFlag.SetDTXFlag(DLDTX_ACTIVATE_ALLOWED);          //0x00
    assReq->AddIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, &dlFlag);

    // Populate Interference Band To Be Used
    itBand.SetBandToBeUsed(0x1F);
    assReq->AddIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED, &itBand);

    // populate Classmark Info Type2, add it to the message
    cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
    cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
    cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
    cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
    cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
    cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
    cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
    cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
    cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
    cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
    cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
    cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
    cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
    cmInfo2.SetCM3(CIT2_CM3_OPTIONS_SUPPORTED);         //0x01
    assReq->AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);

    // populate Group Call Reference, add it to the message
    gcRef.SetCallRef(uint);                             //0x4321000
    gcRef.SetClPrio(GCR_CALL_PRIORITY_LEVEL_B);         //0x06
    gcRef.SetAF(GCR_AF_ACK_REQUIRED);                   //0x01
    gcRef.SetSF(GCR_SF_VBS);                            //0x00
    gcRef.SetCiphInfo(GCR_CIPHERING_KEY_9);             //0x09;
    assReq->AddIE(BSSAP_IEI_GROUP_CALL_REFERENCE, &gcRef);

    // populate Talker Flag, add it to the message
    assReq->AddIE(BSSAP_IEI_TALKER_FLAG, &tkFlag);

    // populate Configuration Evolution Indication, add it to the message
    ceInd.SetSMI(CE_MODIFICATION_ALLOWED_TCH_F_2);        //0x02
    assReq->AddIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, &ceInd);
}

static void
BuildCallProceeding(BSSAP_Message* msg)
{
    BSSAP_ChanType           chanType;
    BSSAP_L3HeaderInfo       l3hInfo;
    BSSAP_Prio               prio;
    BSSAP_CktIDCode          cktId;
    BSSAP_DLDTXFlag          dlFlag;
    BSSAP_ClassmarkInfo2     cmInfo2;
    BSSAP_GrpClRef           gcRef;
    BSSAP_TalkerFlag         tkFlag;
    BSSAP_LsaAccCtrlSuppr    lacs;
    BSSAP_ConfigEvlInd       ceInd;
    BSSAP_ServHandover       servHand;
    BSSAP_Facility           facility;
    BSSAP_ProgressIndicator  progress;
    BSSAP_BearerData         bd;
    BSSAP_CCCause            cause;
    BSSAP_CCCapabilities     cc;
    BSSAP_PriorityLevel      pl;
    ITS_OCTET                octets[] = { 0x1, 0x2, 0x3, 0x4, 0x5 };

    // message
    BSSAP_CallProceeding *cp = (BSSAP_CallProceeding*)msg;

    // populate Layer 3 Header Information, add it to the message
    cp->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    cp->SetTIVal(TI_VALUE_3);                      //0x03
    cp->SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

    bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
    bd.SetCodingGsm();
    bd.SetTransferModeCkt();
    cp->AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

    facility.SetFacilityData(octets, 5);
    cp->AddIE(BSSAP_IEI_CC_FACILITY, &facility);

    ITS_OCTET value = 1;
    progress.SetCodingLocationDesc(value, value, value);
    cp->AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

    pl.SetPriority(PRIORITY_LEVEL_2);
    cp->AddIE(BSSAP_IEI_PRIORITY, &pl);
}

static void
BuildConnect(BSSAP_Message* msg)
{
    BSSAP_Facility             facility;
    BSSAP_ProgressIndicator    progress;
    BSSAP_ConnectedNumber      cn;
    BSSAP_ConnectedSubAddress  cs;
    BSSAP_UserToUser           userTouser;
    BSSAP_SSVersion            ss;
    ITS_OCTET                  octets[100];
    ITS_OCTET                  value = 1;

    // message
    BSSAP_Connect *co = (BSSAP_Connect*)msg;

    co->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    co->SetTIVal(TI_VALUE_3);                      //0x03
    co->SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

    facility.SetFacilityData(octets, 5);
    co->AddIE(BSSAP_IEI_CC_FACILITY, &facility);

    progress.SetCodingLocationDesc(value, value, value);
    co->AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

    cn.SetTypeAndNumPlan( 1, 1);
    cn.SetDigits(octets, 5);
    co->AddIE(BSSAP_IEI_CC_CONNECTED_NUMBER, &cn);

    cs.SetSubAddressType( 1, ITS_TRUE);
    cs.SetSubAddressInfo(octets, 5);
    co->AddIE(BSSAP_IEI_CC_CONNECTED_SUB_ADDRESS, &cs);

    userTouser.SetProtocolDiscriminator(1);
    userTouser.SetUserInfo(octets, 5);
    co->AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

    ss.SetSSVersion(octets, 2);
    co->AddIE(BSSAP_IEI_CC_SS_VERSION_IND, &ss);
}

static void
BuildSetup(BSSAP_Message* msg)
{
    BSSAP_Facility                facility;
    BSSAP_ProgressIndicator       progress;
    BSSAP_BearerData              bd;
    BSSAP_CCCause                 cause;
    BSSAP_CCCapabilities          cc;
    BSSAP_ConnectedNumber         cn;
    BSSAP_ConnectedSubAddress     cs;
    BSSAP_CallingPartyBCDNumber   cg;
    BSSAP_CallingPartySubAddress  cgs;
    BSSAP_CalledPartyBCDNumber    cd;
    BSSAP_CalledPartySubAddress   cds;
    BSSAP_UserToUser              userTouser;
    BSSAP_SSVersion               ss;
    BSSAP_Signal                  signal;
    BSSAP_LowLevelCompInfo        lc;
    BSSAP_HighLevelCompInfo       hc;
    BSSAP_RepeatIndicator         ri;
    BSSAP_PriorityLevel           pl;
    ITS_OCTET                     octets[100];
    ITS_OCTET                     value = 1;
              
    // message
    BSSAP_Setup *setup = (BSSAP_Setup*)msg;
      
    setup->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    setup->SetTIVal(TI_VALUE_3);                      //0x03
    setup->SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

    ri.SetRepeatType(1);
    setup->AddIE(BSSAP_IEI_CC_REPEAT_INDICATOR, &ri);
            
    bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
    bd.SetCodingGsm();
    bd.SetTransferModeCkt();
    setup->AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);
             
    bd.SetInfoTransferCapabAndRadioChannelType(2, 2);
    bd.SetCodingGsm();
    bd.SetTransferModeCkt();
    setup->AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);
              
    facility.SetFacilityData(octets, 5);
    setup->AddIE(BSSAP_IEI_CC_FACILITY, &facility);
              
    progress.SetCodingLocationDesc(value, value, value);
    setup->AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);
              
    signal.SetSignal(1);
    setup->AddIE(BSSAP_IEI_CC_SIGNAL, &signal);
              
    cg.SetTypeAndNumPlan( 1, 1);
    cg.SetDigits(octets, 5);
    setup->AddIE(BSSAP_IEI_CC_CALLING_PARTY_BCD_NUMBER, &cg);
             
    cgs.SetSubAddressType( 1, ITS_TRUE);
    cgs.SetSubAddressInfo(octets, 5);
    setup->AddIE(BSSAP_IEI_CC_CALLING_PARTY_SUB_ADDRESS, &cgs);
              
    cd.SetTypeAndNumPlan( 1, 1);
    cd.SetDigits(octets, 5);
    setup->AddIE(BSSAP_IEI_CC_CALLED_PARTY_BCD_NUMBER, &cd);
             
    cds.SetSubAddressType( 1, ITS_TRUE);
    cds.SetSubAddressInfo(octets, 5);
    setup->AddIE(BSSAP_IEI_CC_CALLED_PARTY_SUB_ADDRESS, &cds);

    userTouser.SetProtocolDiscriminator(1);
    userTouser.SetUserInfo(octets, 5);
    setup->AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);
              
    lc.SetLowLevelCompInfo(octets, 5);
    setup->AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);
              
    hc.SetCodingPrsInterpretAndCharacterstics(value, value);
    setup->AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);
             
    pl.SetPriority(1);     //For Priority info 81H
    setup->AddIE(BSSAP_IEI_PRIORITY, &pl);
}

static void
BuildDisconnect(BSSAP_Message* msg)
{
    BSSAP_Facility           facility;
    BSSAP_ProgressIndicator  progress;
    BSSAP_CCCause            cause;
    BSSAP_UserToUser         userTouser;
    ITS_OCTET                octets[100];
    ITS_OCTET                value = 1;
                 
    // message
    BSSAP_Disconnect *disc = (BSSAP_Disconnect*)msg;
 
    disc->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    disc->SetTIVal(TI_VALUE_3);                      //0x03
    disc->SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

    cause.SetCodingLocationCause(1, 1, 1);
    disc->AddIE(BSSAP_IEI_CC_CAUSE, &cause);
                
    facility.SetFacilityData(octets, 0);
    disc->AddIE(BSSAP_IEI_CC_FACILITY, &facility);
                
    progress.SetCodingLocationDesc(value, value, value);
    disc->AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);
              
    userTouser.SetProtocolDiscriminator(1);
    userTouser.SetUserInfo(octets, 5);
    disc->AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);
}

static void
BuildRelease(BSSAP_Message* msg)
{
    BSSAP_Facility    facility;
    BSSAP_CCCause     cause;
    BSSAP_UserToUser  userTouser;
    ITS_OCTET         octets[100];
                 
    // message
    BSSAP_Release *rel = (BSSAP_Release*)msg;
                
    rel->SetProtDiscr(PD_CALL_CONTROL_MSGS);  //0x03
    rel->SetTIVal(TI_VALUE_3);                //0x03
    rel->SetTIFlag(TI_FLAG_TO_SIDE);          //0x01

    cause.SetCodingLocationCause(1, 1, 1);
    rel->AddIE(BSSAP_IEI_CC_CAUSE, &cause);
                 
    facility.SetFacilityData(octets, 0);
    rel->AddIE(BSSAP_IEI_CC_FACILITY, &facility);
                 
    userTouser.SetProtocolDiscriminator(1);
    userTouser.SetUserInfo(octets, 5);
    rel->AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);
}

static void
BuildCallConfirmed(BSSAP_Message* msg)
{
    BSSAP_BearerData      bd;
    BSSAP_CCCause         cause;
    BSSAP_CCCapabilities  cc;
    ITS_OCTET             octets[100];
              
    // message
    BSSAP_CallConfirmed* ccon = (BSSAP_CallConfirmed*)msg;
    // populate Layer 3 Header Information, add it to the message
    ccon->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    ccon->SetTIVal(TI_VALUE_3);                      //0x03
    ccon->SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
    bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
    bd.SetCodingGsm();
    bd.SetTransferModeCkt();
    ccon->AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);
              
    cause.SetCodingLocationCause(1, 1, 1);
    ccon->AddIE(BSSAP_IEI_CC_CAUSE, &cause);
            
    cc.SetDTMF();
    cc.SetPCP();
    ccon->AddIE(BSSAP_IEI_CC_CAPABILITIES, &cc);
}

static void
BuildConnectAcknowledge(BSSAP_Message* msg)
{
    ITS_OCTET  octets[100];
              
    // message
    BSSAP_ConnectAck *cok = (BSSAP_ConnectAck *)msg;
              
    cok->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    cok->SetTIVal(TI_VALUE_3);                      //0x03
    cok->SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
}

static void
BuildReleaseComplete(BSSAP_Message* msg)
{
    BSSAP_Facility    facility;
    BSSAP_CCCause     cause;
    BSSAP_UserToUser  userTouser;
    ITS_OCTET         octets[100];
                 
    // message
    BSSAP_ReleaseComplete *relcmp = (BSSAP_ReleaseComplete *)msg;
                 
    relcmp->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    relcmp->SetTIVal(TI_VALUE_3);                      //0x03
    relcmp->SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
                 
    cause.SetCodingLocationCause(1, 1, 1);
    relcmp->AddIE(BSSAP_IEI_CC_CAUSE, &cause);
                
    facility.SetFacilityData(octets, 0);
    relcmp->AddIE(BSSAP_IEI_CC_FACILITY, &facility);
                 
    userTouser.SetProtocolDiscriminator(1);
    userTouser.SetUserInfo(octets, 5);
    relcmp->AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);
}

static void
BuildAlerting(BSSAP_Message* msg)
{
    BSSAP_ChanType           chanType;
    BSSAP_L3HeaderInfo       l3hInfo;
    BSSAP_Prio               prio;
    BSSAP_CktIDCode          cktId;
    BSSAP_DLDTXFlag          dlFlag;
    BSSAP_ClassmarkInfo2     cmInfo2;
    BSSAP_GrpClRef           gcRef;
    BSSAP_TalkerFlag         tkFlag;
    BSSAP_LsaAccCtrlSuppr    lacs;
    BSSAP_ConfigEvlInd       ceInd;
    BSSAP_ServHandover       servHand;
    BSSAP_Facility           facility;
    BSSAP_ProgressIndicator  progress;
    BSSAP_UserToUser         userTouser;
    ITS_OCTET                value = 1;
    ITS_OCTET                octets[100];

    // message
    BSSAP_Alerting *alert = (BSSAP_Alerting *)msg;

    // populate Layer 3 Header Information, add it to the message
    alert->SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    alert->SetTIVal(TI_VALUE_3);                      //0x03
    //l3hInfo.SetTIFlag(TI_FLAG_TO_SIDE);             //0x01

    alert->AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

    facility.SetFacilityData(octets, 0);
    alert->AddIE(BSSAP_IEI_CC_FACILITY, &facility);

    progress.SetCodingLocationDesc(value, value, value);
    alert->AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

    userTouser.SetProtocolDiscriminator(1);
    userTouser.SetUserInfo(octets, 5);
    alert->AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);
}

static void
BuildAuthReq(BSSAP_Message* msg)
{
    BSSAP_CypheringKeySequence  ckey;
    BSSAP_ParameterRand         rand;
    BSSAP_ParameterSres         psr;
    ITS_OCTET                   octet[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x1, 0x2, 0x3, 0x4, 0x5, 0x1, 0x2, 0x3, 0x4, 0x5, 0x1};

    BSSAP_AuthenticationRequest *authReq = (BSSAP_AuthenticationRequest *)msg;

    authReq->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
    authReq->SetTIVal(TI_VALUE_3);                                //0x03
    authReq->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

    ckey.SetCypheringKeySequence(0x01);
    authReq->AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &ckey);

    rand.SetParameterRand(octet);
    authReq->AddIE(BSSAP_IEI_PARAMETER_RAND, &rand);
}

static void
BuildPaging(BSSAP_Message* msg)
{
    BSSAP_IMSI        imsi;
    BSSAP_CellIDList  ciList;
    BSSAP_TMSI        tmsi;
    BSSAP_ChanNeeded  chanNd;
    BSSAP_eMMLPrio    emmlp;
    BSSAP_CellIDT     cid1;
    ITS_OCTET         mindig[] = {0x69,0x64,0x63,0x60};
    ITS_UINT          uint = 0x4321000;
    ITS_OCTET         octet = 0x11U;
    ITS_USHORT        ushort  = 0x228U;
    ITS_INT           i;

    // message
    BSSAP_Paging *pag = (BSSAP_Paging *)msg;

    // populate IMSI, add it to the message
    // imsi.SetDigits(digits, strlen(digits));              //7260686
    imsi.SetDigitsB(mindig, 7);
    pag->AddIE(BSSAP_IEI_IMSI, &imsi);

    // populate TMSI, add it to the message
    tmsi.SetTMSI(uint);                                    //0x4321000
    pag->AddIE(BSSAP_IEI_TMSI, &tmsi);
                            
    // populate Cell Identifier List, add it to the message
    ciList.SetCellIDListDisc(CI_CID_CGI);
    //cgi
    CIL_CGI_SET_MCC_PCS(cid1, ushort);
    CIL_CGI_SET_MNC_PCS(cid1, octet);
    CIL_CGI_SET_LAC(cid1, ushort);
    CIL_CGI_SET_CI(cid1, ushort);
    // ciList.AddCellID(cid1);
    for(i = 0; i < 10; i++)
    {
        ciList.SetCellID(cid1, i);
    }
    pag->AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);
                            
    // populate Channel Needed, add it to the message
    chanNd.SetChan(CN_CHANNEL_TCH_F);                      //0x02
    pag->AddIE(BSSAP_IEI_CHANNEL_NEEDED, &chanNd);
                            
    // populate eMMLPriority, add it to the message
    emmlp.SetClPrio(octet);
    pag->AddIE(BSSAP_IEI_eMLPP_PRIORITY, &emmlp);
}

static void
BuildCipherModeCmd(BSSAP_Message* msg)
{
    BSSAP_EncryptionInformation  encInfo;
    BSSAP_L3HeaderInfo           l3hInfo;
    BSSAP_CipherRspMode          crMd;
    ITS_OCTET                    key[] = {1,3,3,4,5};

    // message
    BSSAP_CipherModeCommand *cmCmd = (BSSAP_CipherModeCommand *)msg;

    // populate Encryption Information, add it to the message
    encInfo.SetNoEncryption(0);
    encInfo.SetA5_1(1);
    encInfo.SetA5_2(0);
    encInfo.SetA5_3(1);
    encInfo.SetA5_4(0);
    encInfo.SetA5_5(1);
    encInfo.SetA5_6(0);
    encInfo.SetA5_7(1);
    encInfo.SetKey(key, sizeof(key));
    cmCmd->AddIE(BSSAP_IEI_ENCRYPTION_INFORMATION, &encInfo);

    // populate Layer 3 Header Information, add it to the message
    l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    l3hInfo.SetTIVal(7);
    l3hInfo.SetTIFlag(1);
    cmCmd->AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

    // populate Cipher Response Mode, add it to the message
    crMd.SetCipherRspMode(CRM_IMEISV_INLCUDED);        //0x01
    cmCmd->AddIE(BSSAP_IEI_CIPHER_RESPONSE_MODE, &crMd);
}

static void
BuildCipherModeComplete(BSSAP_Message* msg)
{
    BSSAP_L3MsgCnt   l3mc;
    BSSAP_ChsEncAlg  ceAlg;
    ITS_OCTET        key[] = {1,3,3,4,5};

    // message
    BSSAP_CipherModeComplete *cmCplt = (BSSAP_CipherModeComplete *) msg;

    // populate Layer 3 Messge Contents, add it to the message
    l3mc.SetL3MsgCnt(key, sizeof(key));
    cmCplt->AddIE(BSSAP_IEI_LAYER3_MESSAGE_CONTENT, &l3mc);

    // populate Chosen Encryption Algorithm, add it to the message
    ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03
    cmCplt->AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);
}

static void
BuildClearCommand(BSSAP_Message* msg)
{
    BSSAP_Cse           cs;
    BSSAP_L3HeaderInfo  l3hInfo;
    ITS_OCTET           octet = 0x11U;
    bool                isExt = 1;

    // message
    BSSAP_ClearCommand *clrCmd = (BSSAP_ClearCommand *)msg;

    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
    clrCmd->AddIE(BSSAP_IEI_CAUSE, &cs);

    // populate Layer 3 Header Information, add it to the message
    l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    l3hInfo.SetTIVal(8);
    l3hInfo.SetTIFlag(9);
    clrCmd->AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);
}

static void
BuildClearComplete(BSSAP_Message* msg)
{

}

static void
BuildClearRequest(BSSAP_Message* msg)
{
    BSSAP_Cse  cs;
    ITS_OCTET  octet = 0x11U;
    bool       isExt = 1;

    //message
    BSSAP_ClearRequest *clrReq = (BSSAP_ClearRequest *)msg;

    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
    clrReq->AddIE(BSSAP_IEI_CAUSE, &cs);
}

static void
BuildBlock(BSSAP_Message* msg)
{
    BSSAP_CktIDCode  cktId;
    BSSAP_Cse        cs;
    BSSAP_ConRlsReq  crReq;
    ITS_OCTET        octet = 0x11U;
    ITS_USHORT       ushort  = 0x228U; 
    bool             isExt = 1;

    // message
    BSSAP_Block *blk = (BSSAP_Block *)msg;

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    blk->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
        
    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
    blk->AddIE(BSSAP_IEI_CAUSE, &cs);
        
    // populate Connection Release Requested, add it to the message
    blk->AddIE(BSSAP_IEI_CONNECTION_RELEASE_REQUESTED, &crReq);
}

static void
BuildBlockAck(BSSAP_Message* msg)
{
    BSSAP_CktIDCode  cktId;
    ITS_OCTET        octet = 0x11U;
    ITS_USHORT       ushort  = 0x228U;

    // message
    BSSAP_BlockAcknowledge  *blkAck = (BSSAP_BlockAcknowledge *)msg;

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x11
    blkAck->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId); 
}

static void
BuildUnblock(BSSAP_Message* msg)
{
    BSSAP_CktIDCode  cktId;
    ITS_OCTET        octet = 0x11U;
    ITS_USHORT       ushort  = 0x228U;

    // message
    BSSAP_Unblock *unblk = (BSSAP_Unblock *)msg;

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    unblk->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId); 
}

static void
BuildUnblockAck(BSSAP_Message* msg)
{
    BSSAP_CktIDCode  cktId;
    ITS_OCTET        octet = 0x11U;
    ITS_USHORT       ushort  = 0x228U;
 
    // message
    BSSAP_UnblockAcknowledge *unblkAck = (BSSAP_UnblockAcknowledge *)msg;

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    unblkAck->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
}

static void
BuildReset(BSSAP_Message* msg)
{
    BSSAP_Cse  cs;
    ITS_OCTET  octet = 0x11U;  
    bool       isExt = 1;

    // message
    BSSAP_Reset *set = (BSSAP_Reset *)msg;

    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
    set->AddIE(BSSAP_IEI_CAUSE, &cs);
}

static void
BuildResetAck(BSSAP_Message* msg)
{

}

static void
BuildOverload(BSSAP_Message* msg)
{
    BSSAP_Cse         cs;
    BSSAP_CellID      cellId;
    BSSAP_CellIDType  cid;
    ITS_OCTET         octet = 0x11U;
    ITS_USHORT        ushort  = 0x228U;
    bool              isExt = 1;

    // message
    BSSAP_Overload *ovld = (BSSAP_Overload *)msg;

    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
    ovld->AddIE(BSSAP_IEI_CAUSE, &cs);

    // populate Cell Identifier, add it to the message
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);
    ovld->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);
}

static void
BuildResetCircuit(BSSAP_Message* msg)
{
    BSSAP_CktIDCode  cktId;
    BSSAP_Cse        cs;
    ITS_OCTET        octet = 0x11U;
    ITS_USHORT       ushort  = 0x228U;
    bool             isExt = 1;    

    // message
    BSSAP_ResetCircuit *rCkt = (BSSAP_ResetCircuit *)msg;
 
    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    rCkt->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    // populate Cause, add it to the message
    cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
    // cs.SetNationalCause(C_CLASS_INTERWORKING, octet);
    rCkt->AddIE(BSSAP_IEI_CAUSE, &cs);
}

static void
BuildResetCircuitAck(BSSAP_Message* msg)
{
    BSSAP_CktIDCode  cktId;
    ITS_OCTET        octet = 0x11U;
    ITS_USHORT       ushort  = 0x228U;

    // message
    BSSAP_ResetCircuitAcknowledge *rcAck = (BSSAP_ResetCircuitAcknowledge *)msg;

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    rcAck->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId); 
}

static void
BuildAssignComplete(BSSAP_Message* msg)
{
    BSSAP_RRcause     rrCs;
    BSSAP_CktIDCode   cktId;
    BSSAP_CellID      cellId;
    BSSAP_ChsChan     chsChan;
    BSSAP_ChsEncAlg   ceAlg;
    BSSAP_CktPool     cktPl;
    BSSAP_SpchVer     spchVer;
    BSSAP_LsaId       lsaid;
    BSSAP_CellIDType  cid;
    ITS_OCTET         octet = 0x11U;
    ITS_OCTET         key[] = {1,3,3,4,5}; 
    ITS_USHORT        ushort  = 0x228U;

    // message
    BSSAP_AssignmentComplete *assCmp = (BSSAP_AssignmentComplete *)msg;

    // populate RR Cause, add it to the message
    rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05
    assCmp->AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    assCmp->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    // populate Cell Identifier, add it to the message
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid, ushort);
    CI_CGI_SET_MNC_PCS(cid, octet);
    CI_CGI_SET_LAC(cid, ushort);
    CI_CGI_SET_CI(cid, ushort);
    cellId.SetCellID(cid);
    assCmp->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);

    // populate Chosen Channel, add it to the message
    chsChan.SetChan(CC_CH_SPEECH);                      //0x09
    chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01
    assCmp->AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);

    // populate Chosen Encryption Algorithm, add it to the message
    ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                 //0x03
    assCmp->AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01
    assCmp->AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);

    // populate Speech Version, add it to the message
    spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER3);         //0x21
    assCmp->AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);

    // populate LSA Identifier, add it to the message
    lsaid.SetLSAIDBit1(0x01);
    lsaid.SetLSAID(0x432111);
    assCmp->AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);
}

static void
BuildIdenReq(BSSAP_Message* msg)
{
    BSSAP_IdentityType idType;
    BSSAP_ParameterSres psr;

    // message
    BSSAP_IdentityRequest *idReq = (BSSAP_IdentityRequest *)msg;
 
    idReq->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
    idReq->SetTIVal(TI_VALUE_3);                                //0x03
    idReq->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

    idType.SetIdentityType(0x04);
    idReq->AddIE(BSSAP_IEI_IDENTITY_TYPE, &idType);
}

static void
BuildIdenResp(BSSAP_Message* msg)
{
    BSSAP_MobileID  mobId;
    BSSAP_ParameterSres psr;
    char       digits[] = {0x01, 0x02, 0x03, 0x04, 0x05}; 

    // message
    BSSAP_IdentityResponse *idResp = (BSSAP_IdentityResponse *)msg;

    idResp->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
    idResp->SetTIVal(TI_VALUE_3);                                //0x03
    idResp->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

    mobId.SetOddEvenInd(MI_ODD_DIGITS);
    mobId.SetTypeIdentity(MI_IMSI);
    mobId.SetIdenCDig(digits, 5);
    idResp->AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mobId);   
}

static void
BuildCmServAcc(BSSAP_Message* msg)
{
    BSSAP_CMServiceAccept *cmServAcc=(BSSAP_CMServiceAccept *)msg;
    BSSAP_ParameterSres    psr;
                                                                                                                                          
    cmServAcc->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
    cmServAcc->SetTIVal(TI_VALUE_3);                                //0x03
    cmServAcc->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr); 
}

static void
BuildTmsiRealCmd(BSSAP_Message* msg)
{
    BSSAP_LocationAreaID  locAreaId;
    BSSAP_ParameterSres   psr;
    ITS_OCTET             octet1[] = { 0x11U, 0x22U};
    ITS_OCTET             octet2[] = { 0x11U, 0x22U};
    BSSAP_MobileID        mobId;
    ITS_CHAR              digits[] = {0x01, 0x03, 0x03, 0x04, 0x05};

    // message
    BSSAP_TMSIReallocCommand *tRealCmd = (BSSAP_TMSIReallocCommand *)msg;

    tRealCmd->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
    tRealCmd->SetTIVal(TI_VALUE_3);                                //0x03
    tRealCmd->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

    locAreaId.SetLocationAreaIDMCC(octet2);
    locAreaId.SetLocationAreaIDMNC(octet1);
    locAreaId.SetLocationAreaIDLAC(octet2);
    tRealCmd->AddIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, &locAreaId); 

    mobId.SetOddEvenInd(MI_ODD_DIGITS);
    mobId.SetTypeIdentity(MI_IMSI);
    mobId.SetIdenCDig(digits, 5);
    tRealCmd->AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mobId);
}

static void
BuildTmsiRealCmp(BSSAP_Message* msg)
{
    BSSAP_ParameterSres psr;
                                                                                                                                              
    // message
    BSSAP_TMSIReallocComplete *tmsiRelCom=(BSSAP_TMSIReallocComplete *)msg;
                                                                                                                                              
    tmsiRelCom->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
    tmsiRelCom->SetTIVal(TI_VALUE_3);                                //0x03
    tmsiRelCom->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);    
}

static void
BuildAuthenResp(BSSAP_Message* msg)
{
    BSSAP_ParameterSres  psr;
    ITS_OCTET            parasres[4]={88,77,66,44};

    //message
    BSSAP_AuthenticationResponse *AuthResp = (BSSAP_AuthenticationResponse *)msg;

    psr.SetParameterSres(parasres);
    
    AuthResp->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
    AuthResp->SetTIVal(TI_VALUE_3);                                //0x03
    AuthResp->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);
}

static void
BuildPagingResp(BSSAP_Message* msg)
{
    BSSAP_MobileID              mobId;
    BSSAP_CypheringKeySequence  cKeySeq;
    BSSAP_ClassmarkInfo2        cmInfo2;
    ITS_CHAR                    digits[] = {0x01, 0x03, 0x03, 0x04, 0x05}; 

    // message
    BSSAP_PagingResponse *pagResp = (BSSAP_PagingResponse *)msg;

    cKeySeq.SetCypheringKeySequence(0x01);
    pagResp->AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &cKeySeq);

    // populate Classmark Info Type2, add it to the message
    cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
    cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
    cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
    cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
    cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
    cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
    cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
    cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
    cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
    cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
    cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
    cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
    cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
    cmInfo2.SetCM3(CIT2_CM3_OPTIONS_SUPPORTED);         //0x01
    pagResp->AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);

    mobId.SetOddEvenInd(MI_ODD_DIGITS);
    mobId.SetTypeIdentity(MI_IMSI);
    mobId.SetIdenCDig(digits, 4);
    pagResp->AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mobId);
}

static void
BuildHandoverReq(BSSAP_Message* msg)
{
    BSSAP_ChanType                chanType;
    BSSAP_EncryptionInformation   encInfo;
    BSSAP_ClassmarkInfo1          cmInfo1;
    BSSAP_ClassmarkInfo2          cmInfo2;
    BSSAP_CellID                  cellId;
    BSSAP_CellID                  target_cellId;
    BSSAP_Prio                    prio;
    BSSAP_CktIDCode               cktId;
    BSSAP_DLDTXFlag               dlFlag;
    BSSAP_InterBandToBeUsed       ibbu;
    BSSAP_Cse                     cs;
    BSSAP_ClassmarkInfo3          cmInfo3;
    BSSAP_CrtChan                 crtChan;
    BSSAP_SpchVer                 spchVer;
    BSSAP_GrpClRef                gcRef;
    BSSAP_TalkerFlag              tkFlag;
    BSSAP_ConfigEvlInd            ceInd;
    BSSAP_ChsEncAlg               ceAlg;
    BSSAP_SrcRNCtoTgtRNCInfoUMTS  umts;
    BSSAP_SrcRNCtoTgtRNCInfoCDMA  cdma;
    BSSAP_CellIDType              cid;
    ITS_OCTET                     key[] = {1,3,3,4,5};
    bool                          isExt = 1;
    ITS_OCTET                     octet = 0x11U;
    ITS_USHORT                    ushort  = 0x228U;
    ITS_UINT                      uint = 0x4321000;

    // message
    BSSAP_HandoverRequest *handReq = (BSSAP_HandoverRequest *)msg;

    // populate Channel Type, add it to the message
    chanType.SetSpeechDataID(CT_DATA);                             //0x02
    chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);    //0x08
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 0);      //0x01
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 1);      //0x11
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 2);      //0x21
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 3);      //0x01
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 4);      //0x11
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 5);      //0x21
    chanType.SetDataTransp(1, CT_DATA_MAX_ALLOWED_CHANNEL1, 1);    //0x20
    chanType.SetIFDateRate(1, 0x53);                               //0x53
    chanType.SetAsymInd(0, 0x02);                                  //0x02
    handReq->AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);

    // populate Encryption Information, add it to the message
    encInfo.SetNoEncryption(0);
    encInfo.SetA5_1(1);
    encInfo.SetA5_2(0);
    encInfo.SetA5_3(1);
    encInfo.SetA5_4(0);
    encInfo.SetA5_5(1);
    encInfo.SetA5_6(0);
    encInfo.SetA5_7(1);
    encInfo.SetKey(key, sizeof(key));
    handReq->AddIE(BSSAP_IEI_ENCRYPTION_INFORMATION, &encInfo);

/*    // Classmark Information 1 and 2 can not be set up at the sametime
    // populate Classmark Information 1, add it to the message
    cmInfo1.SetRFPowerCap(CIT1_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo1.SetA51(CIT1_A5_1_IS_AVAILABLE);             //0x00
    cmInfo1.SetESIND(CIT1_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo1.SetRevLevel(CIT1_REV_LEVEL_PHASE_2);        //0x01
    handReq->AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1, &cmInfo1);
*/

    // populate Classmark Information 2, add it to the message
    cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
    cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
    cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
    cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
    cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
    cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
    cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
    cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
    cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
    cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
    cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
    cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
    cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
    cmInfo2.SetCM3(CIT2_CM3_OPTIONS_NOT_SUPPORTED);     //0x01
    handReq->AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);

    // populate Cell Identifier, add it to the message
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid, ushort);
    CI_CGI_SET_MNC_PCS(cid, octet);
    CI_CGI_SET_LAC(cid, ushort);
    CI_CGI_SET_CI(cid, ushort);
    cellId.SetCellID(cid);
    handReq->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);

    // populate Cell Identifier (target_cellId), add it to the message
    target_cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    target_cellId.SetCellID(cid);
    handReq->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &target_cellId);

    // populate Priority, add it to the message
    prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
    prio.SetQA(P_QUEUING_ALLOWED);                      //1
    prio.SetPVI(1);
    prio.SetPCI(P_NO_PREEMPTION );                      //0
    handReq->AddIE(BSSAP_IEI_PRIORITY, &prio);

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    handReq->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    // populate Downlink DTX Flag, add it to the message
    dlFlag.SetDTXFlag(DLDTX_ACTIVATE_ALLOWED);          //0x00
    handReq->AddIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, &dlFlag);

    // populate Interference Band To Be Used, add it to the message
    ibbu.SetBandToBeUsed(octet);                        //0x04
    handReq->AddIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED, &ibbu);

    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
    handReq->AddIE(BSSAP_IEI_CAUSE, &cs);

    // populate Classmark Information3, add it to the message
    cmInfo3.SetMultiBand(0x05);                      //0x01
    cmInfo3.SetA54(1);                               //0x01
    cmInfo3.SetA55(0);                               //0x01
    cmInfo3.SetA56(0);                               //0x01
    cmInfo3.SetA57(1);                               //0x01
    cmInfo3.SetRadioCap1(0x04);
    cmInfo3.SetRadioCap2(0x08);
    cmInfo3.SetMultiSlotClass(0x07);
    cmInfo3.SetRGSMCap(0x06);
    cmInfo3.SetSMValue(0x09);
    cmInfo3.SetSMSValue(0x02);
    cmInfo3.SetUCS2Treat(1);
    cmInfo3.SetExtMeasCap(0);
    cmInfo3.SetMSConGPS(1);
    cmInfo3.SetMSBasedGPS(0);
    cmInfo3.SetMSAssistedGPS(1);
    cmInfo3.SetMSBasedEOTD(0);
    handReq->AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, &cmInfo3);

    // populate Current Channel, add it to the message
    crtChan.SetChan(CC_CHANNEL_MODE_SPEECH);               //0x01
    crtChan.SetChanMode(CC_CHANNEL_SDCCH);                 //0x01
    handReq->AddIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1, &crtChan);

    // populate Speech Version, add it to the message
    spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01
    handReq->AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);

    // populate Group Call Reference, add it to the message
    gcRef.SetCallRef(uint);
    gcRef.SetClPrio(GCR_CALL_PRIORITY_LEVEL_B);         //0x06
    gcRef.SetAF(GCR_AF_ACK_REQUIRED);                   //0x01
    gcRef.SetSF(GCR_SF_VBS);                            //0x00
    gcRef.SetCiphInfo(GCR_CIPHERING_KEY_9);             //0x09;
    handReq->AddIE(BSSAP_IEI_GROUP_CALL_REFERENCE, &gcRef);

    // populate Talker Flag, add it to the message
    handReq->AddIE(BSSAP_IEI_TALKER_FLAG, &tkFlag);

    // populate Configuration Evolution Indication, add it to the message
    ceInd.SetSMI(CE_NO_MODIFICATION_ALLOWED);           //0x00
    handReq->AddIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, &ceInd);

    // populate Chosen Encryption Algorithm, add it to the message
    ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03
    handReq->AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

    // populate Soruce RNC to Target RNC Transparent Information (UMTS),
    // add it to the message
    umts.SetSrcRNCtoTgtRNCInfoUMTS(key, sizeof(key));
    handReq->AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS, &umts);

    // populate Soruce RNC to Target RNC Transparent Information (CDMA),
    // add it to the message
    cdma.SetSrcRNCtoTgtRNCInfoCDMA(key, sizeof(key));
    handReq->AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA, &cdma);
}

static void
BuildHandoverCmd(BSSAP_Message* msg)
{
    BSSAP_L3Info      l3Info;
    BSSAP_CellID      cellId;
    BSSAP_CellIDType  cid;
    ITS_OCTET         key[] = {1,3,3,4,5};
    ITS_USHORT        ushort  = 0x228U;

    // message
    BSSAP_HandoverCommand  *handCmd = (BSSAP_HandoverCommand *)msg;

    // populate Layer 3 Information, add it to the message
    l3Info.SetL3Info(key, sizeof(key));
    handCmd->AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);

    // populate Cell Identifier, add it to the message
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,0x22);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);
    handCmd->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);
}

static void
BuildCompL3(BSSAP_Message* msg)
{
    BSSAP_CellID  cellId;
    BSSAP_L3Info  l3Info;
    ITS_USHORT  ushort  = 0x228U;
    BSSAP_CellIDType cid;
    ITS_OCTET octet = 0x11U;
                                                                                                                                              
    BSSAP_CompleteLayer3Information* cl3 =
                                   (BSSAP_CompleteLayer3Information*)msg;
                                                                                                                                              
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);
                                                                                                                                              
                                                                                                                                              
    cl3->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);
                                                                                                                                              
    //CM_SERV_REQ
    ITS_OCTET servReq[] = {0x01, 0x00, 0x10, 0x35, 0x24, 0x11, 0x12, 0x13};
                                                                                                                                              
    l3Info.SetL3Info(servReq, sizeof(servReq));
                                                                                                                                              
    cl3->AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);
                                                                                                                                              
    printf("\t++++ CM_SERV build complete\n");
}

static void
BuildCompL3Pag(BSSAP_Message* msg)
{
    BSSAP_CellID  cellId;
    BSSAP_L3Info  l3Info;
    BSSAP_CellIDType cid;
    ITS_USHORT  ushort  = 0x228U;
    ITS_OCTET octet = 0x11U;
                                                                                                                                              
    BSSAP_CompleteLayer3Information *cl3 =
                             (BSSAP_CompleteLayer3Information *)msg;
                                                                                                                                              
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);
                                                                                                                                              
    cl3->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);
                                                                                                                                              
    //Paging response
    ITS_OCTET servReq[] = {0x01, 0x00, 0x10, 0x36, 0x27, 0x11, 0x12, 0x13};
                                                                                                                                              
    l3Info.SetL3Info(servReq, sizeof(servReq));
                                                                                                                                              
    cl3->AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);
                                                                                                                                              
    printf("\t++++ PAGING RESP build complete\n");
}

static void
BuildHandoverReqAck(BSSAP_Message* msg)
{
    BSSAP_L3Info       l3Info;
    BSSAP_ChsChan      chsChan;
    BSSAP_ChsEncAlg    ceAlg;
    BSSAP_CktPool      cktPl;
    BSSAP_SpchVer      spchVer;
    BSSAP_CktIDCode    cktId;
    BSSAP_LsaId        lsaid;
    ITS_OCTET          key[] = {1,2,3,4,5,6,7,8,9,10,11};
    ITS_OCTET          octet = 0x11U;
    ITS_USHORT         ushort  = 0x228U;
                                                                                                                                              
    // encode/decode buffer
    ITS_OCTET buff[100];
                                                                                                                                              
    // message
    BSSAP_HandoverRequestAcknowledge *hrAck = (BSSAP_HandoverRequestAcknowledge *)msg;
                                                                                                                                              
    // populate Layer 3 Information, add it to the message
    l3Info.SetL3Info(key, sizeof(key));
    hrAck->AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);
                                                                                                                                              
    // populate Chosen Channel, add it to the message
    chsChan.SetChan(CC_CH_SPEECH);                      //0x09
    chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01
    hrAck->AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);
                                                                                                                                              
    // populate Chosen Encryption Algorithm, add it to the message
    ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03
    hrAck->AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);
                                                                                                                                              
    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01
    hrAck->AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);
                                                                                                                                              
    // populate Speech Version, add it to the message
    spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01
    hrAck->AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
    hrAck->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
                                                                                                                                              
    // populate LSA Identifier, add it to the message
    lsaid.SetLSAIDBit1(0x01);
    lsaid.SetLSAID(0x432111);
    hrAck->AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);
}

static void
BuildHandoverDet(BSSAP_Message* msg)
{
                                                                                                                                              
}

static void
BuildHandoverCmp(BSSAP_Message* msg)
{
    BSSAP_RRcause   rrCs;
                                                                                                                                              
    // encode/decode buffer
    ITS_OCTET buff[100];
                                                                                                                                              
    // message
    BSSAP_HandoverComplete *handCmp = (BSSAP_HandoverComplete *)msg;
                                                                                                                                              
    // populate RR Cause, add it to the message
    rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05
    handCmp->AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);
}

static void
BuildHandoverFail(BSSAP_Message* msg)
{
    BSSAP_Cse          cs;
    BSSAP_RRcause      rrCs;
    BSSAP_CktPool      cktPl;
    BSSAP_CktPoolList  cpList;
    BSSAP_CircuitPool  cpool;
    ITS_OCTET          octet = 0x11U;
    bool               isExt = 1;
    int                i;
                                                                                                                                              
    // message
    BSSAP_HandoverFailure *handFail = (BSSAP_HandoverFailure *)msg;
                                                                                                                                              
    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
                                                                                                                                              
    handFail->AddIE(BSSAP_IEI_CAUSE, &cs);
                                                                                                                                              
    // populate RR Cause, add it to the message
    rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05
                                                                                                                                              
    handFail->AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);
                                                                                                                                              
    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01
                                                                                                                                              
    handFail->AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);
                                                                                                                                              
    // populate Circuit Pool List, add it to the message
    CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
//    cpList.AddCircuitPoolNo(cpool);
    for(i = 0; i < 2; i++)
    {
        cpList.SetCircuitPoolNo(cpool, i);
    }
                                                                                                                                              
    handFail->AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);
}

static void
BuildUnequippeCkt(BSSAP_Message* msg)
{
    BSSAP_CktIDCode     cktId;
    BSSAP_CktIDCodeList cicList;
                                                                                                                                              
    // message
    BSSAP_UnequippedCircuit *unCkt = (BSSAP_UnequippedCircuit *)msg;
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
                                                                                                                                              
    unCkt->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
/*
    
    // populate Circuit Identity Code List, add it to the message
    cicList.SetRange(9);
                                                                                                                                              
    int range = cicList.GetRange() + 1;
                                                                                                                                              
    for (int i = 0; i < range; i++)
    {
        if (i & 1)
        {
            cicList.SetStatusBit(1, i);
        }
        else
        {
            cicList.SetStatusBit(1, i);
        }
    }
                                                                                                                                              
    unCkt->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
*/
}

static void
BuildAssignFail(BSSAP_Message* msg)
{
    BSSAP_Cse          cs;
    BSSAP_RRcause      rrCs;
    BSSAP_CktPool      cktPl;
    BSSAP_CktPoolList  cpList;
    BSSAP_CircuitPool  cpool;
    ITS_OCTET          octet = 0x11U;
    bool               isExt = 1;
    int                i;
                                                                                                                                              
    // message
    BSSAP_AssignmentFailure *assFail = (BSSAP_AssignmentFailure *)msg;
                                                                                                                                              
    // populate Cause, add it to the message
    cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);
                                                                                                                                              
    assFail->AddIE(BSSAP_IEI_CAUSE, &cs);
                                                                                                                                              
    // populate RR Cause, add it to the message
    rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05
                                                                                                                                              
    assFail->AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);
                                                                                                                                              
    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01
                                                                                                                                              
    assFail->AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);
                                                                                                                                              
    // populate Circuit Pool List, add it to the message
    CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
//    cpList.AddCircuitPoolNo(cpool);
    for(i = 0; i < 2; i++)
    {
        cpList.SetCircuitPoolNo(cpool, i);
    }
                                                                                                                                              
    assFail->AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);
}

static void
BuildCktGrpBlk(BSSAP_Message* msg)
{
    BSSAP_Cse                      cs;
    BSSAP_CktIDCode                cktId;
    BSSAP_CktIDCodeList            cicList;
                                                                                                                                              
    // message
    BSSAP_CircuitGroupBlock *cgBlk = (BSSAP_CircuitGroupBlock *)msg;
                                                                                                                                              
    // populate Cause, add it to the message
    cs.SetCause(ITS_TRUE, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, 12);
                                                                                                                                              
    cgBlk->AddIE(BSSAP_IEI_CAUSE, &cs);
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
                                                                                                                                              
    cgBlk->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
                                                                                                                                              
    // populate Circuit Identity Code List, add it to the message
    cicList.SetRange(7);
                                                                                                                                              
    int range = cicList.GetRange() + 1;
                                                                                                                                              
    for (int i = 0; i < range; i++)
    {
        if (i & 1)
        {
            cicList.SetStatusBit(1, i);
        }
        else
        {
            cicList.SetStatusBit(1, i);
        }
    }
                                                                                                                                              
    cgBlk->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
}

static void
BuildCktGrpBlkAck(BSSAP_Message* msg)
{
    BSSAP_CktIDCode                cktId;
    BSSAP_CktIDCodeList            cicList;
                                                                                                                                              
    // message
    BSSAP_CircuitGroupBlockAcknowledge *cgba =
                             (BSSAP_CircuitGroupBlockAcknowledge *)msg;
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x11
                                                                                                                                              
    cgba->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
    cicList.SetRange(7);
                                                                                                                                              
    int range = cicList.GetRange() + 1;
                                                                                                                                              
    for (int i = 0; i < range; i++)
    {
        if (i & 1)
        {
            cicList.SetStatusBit(1, i);
        }
        else
        {
            cicList.SetStatusBit(1, i);
        }
    }
                                                                                                                                              
    cgba->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
}

static void
BuildCktGrpUnblk(BSSAP_Message* msg)
{
    BSSAP_Cse                      cs;
    BSSAP_CktIDCode                cktId;
    BSSAP_CktIDCodeList            cicList;
                                                                                                                                              
    // message
    BSSAP_CircuitGroupUnblock *cgUnblk = (BSSAP_CircuitGroupUnblock *)msg;
                                                                                                                                              
    // populate Cause, add it to the message
    cs.SetCause(ITS_TRUE, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, 12);
                                                                                                                                              
    cgUnblk->AddIE(BSSAP_IEI_CAUSE, &cs);
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
                                                                                                                                              
    cgUnblk->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
                                                                                                                                              
    cicList.SetRange(7);
                                                                                                                                              
    int range = cicList.GetRange() + 1;
                                                                                                                                              
    for (int i = 0; i < range; i++)
    {
        if (i & 1)
        {
            cicList.SetStatusBit(1, i);
        }
        else
        {
            cicList.SetStatusBit(1, i);
        }
    }
                                                                                                                                              
    cgUnblk->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
}

static void
BuildCktGrpUnblkAck(BSSAP_Message* msg)
{
    BSSAP_CktIDCode                cktId;
    BSSAP_CktIDCodeList            cicList;
                                                                                                                                              
    // message
    BSSAP_CircuitGroupUnblockAck *cgua = (BSSAP_CircuitGroupUnblockAck *)msg;
                                                                                                                                              
    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(1);                             //0x228
    cktId.SetTimeslot(1);                           //0x04
                                                                                                                                              
    cgua->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
                                                                                                                                              
    // populate Circuit Identity Code List, add it to the message
    cicList.SetRange(7);
                                                                                                                                              
    int range = cicList.GetRange() + 1;
                                                                                                                                              
    for (int i = 0; i < range; i++)
    {
        if (i & 1)
        {
            cicList.SetStatusBit(1, i);
        }
        else
        {
            cicList.SetStatusBit(1, i);
        }
    }
                                                                                                                                              
    cgua->AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
}
                                                                                                                                              
static void
BuildLocationUpdationReq(BSSAP_Message* msg)
{
    BSSAP_CellID  cellId;
    BSSAP_L3Info  l3Info;
    ITS_USHORT  ushort  = 0x228U;
    BSSAP_CellIDType cid;
    ITS_OCTET octet = 0x11U;
                                                                                                                                              
    BSSAP_CompleteLayer3Information* cl3 =
                                   (BSSAP_CompleteLayer3Information*)msg;
                                                                                                                                              
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);
                                                                                                                                              
                                                                                                                                              
    cl3->AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);
                                                                                                                                              
    //Location Updating Request
    ITS_OCTET servReq[] = {0x01, 0x00, 0x10, 0x35, 0x08, 0x11, 0x12, 0x13};
                                                                                                                                              
    l3Info.SetL3Info(servReq, sizeof(servReq));
                                                                                                                                              
    cl3->AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);
                                                                                                                                              
    printf("\t++++ LOCATION UPDATE build complete\n");
}

static void
BuildLocationUpdatingAccept(BSSAP_Message* msg)
{


        //Message
        BSSAP_LocationUpdatingAccept *lUA=(BSSAP_LocationUpdatingAccept *)msg;


         //populate level 3 header
        BSSAP_ParameterSres psr;
        lUA->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        lUA->SetTIVal(TI_VALUE_3);                                //0x03
        lUA->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

        //populate Location Area Identifier
            BSSAP_LocationAreaID lID;
            ITS_OCTET lai = {0x01};
            ITS_OCTET mcc = {0x02};
            ITS_OCTET mnc = {0x02};
            ITS_OCTET lac = {0x03};
            lID.SetLocationAreaID(&lai);
            lID.SetLocationAreaIDMCC(&mcc);
            lID.SetLocationAreaIDMNC(&mnc);
            lID.SetLocationAreaIDLAC(&lac);
           lUA->AddIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER,&lID);

        //populate Mobile Staion Class Mark1
            BSSAP_ClassmarkInfo1 cIF;
            cIF.SetRFPowerCap(0x01);
            cIF.SetA51(1);
            cIF.SetESIND(1);
            cIF.SetRevLevel(0x02);          lUA->AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1,&cIF);


         //populate mobile identity
            BSSAP_MobileID mobId;            char       digits[] = {0x01, 0x02, 0x03, 0x04, 0x05};
            mobId.SetOddEvenInd(MI_ODD_DIGITS);
            mobId.SetTypeIdentity(MI_IMSI);
            mobId.SetIdenCDig(digits, 5);
            lUA->AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mobId);
}

static void
BuildResouceIndicationMessage(BSSAP_Message* msg)
{


    BSSAP_ResIndMethod  rM;
    BSSAP_CellID bCID;
    BSSAP_CellIDType cellType;
    BSSAP_ResourceIndication *resInd=
                 (BSSAP_ResourceIndication *)msg;


    //populate Resouce Indication Mothod
      rM.SetResIndMethod(0x03);
     resInd->AddIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD,&rM);


   ////Populate Cell Identifier
     bCID.SetCellIDDisc(CIL_CID_CI);
     BSSAP_Ci cid={0x01,0x02};

     cellType.ci=cid;
     bCID.SetCellID(cellType);
     resInd->AddIE(BSSAP_IEI_CELL_IDENTIFIER,&bCID);
}


static void
BuildClassMarkUpdate(BSSAP_Message* msg)
{
        BSSAP_ClassmarkInfo2 CI2;

            //Message

        BSSAP_ClassmarkUpdate *cmU = (BSSAP_ClassmarkUpdate *)msg;

         //Populate ClassMark Information Type 2
        CI2.SetRFPowerCap(0x01);
        CI2.SetA51(0);
        CI2.SetESIND(1);
        CI2.SetRevLevel(0x01);
        CI2.SetFC(0);
        CI2.SetVGCS(1);
        CI2.SetVBS(1);
        CI2.SetSMCap(1);
        CI2.SetSSSInd(0x20);
        CI2.SetPSCap(1);
        CI2.SetA52(1);
        CI2.SetA53(1);
        CI2.SetCMSP(1);
        CI2.SetSoLSA(1);
        CI2.SetLCSVACap(0);
        CI2.SetCM3(1);

        cmU->AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2,&CI2);
}

static void
BuildCipherModeReject(BSSAP_Message* msg)
{

        BSSAP_Cse ca;
        bool isExt = 0;
        //Message
        BSSAP_CipherModeReject *cMR = (BSSAP_CipherModeReject *)msg;

       //Populate Cause
       ca.SetCause(isExt,C_REQUESTED_SPEECH_VER_UNAVAIALBLE,C_REQUESTED_SPEECH_VER_UNAVAIALBLE);

       cMR->AddIE(BSSAP_IEI_CAUSE,&ca);
}


static void
BuildUplinkReleaseIndication(BSSAP_Message* msg)
{

        BSSAP_Cse ca;
        bool isExt = 0;

        //Message
        BSSAP_UplinkReleaseIndication *upRelInd = (BSSAP_UplinkReleaseIndication *)msg;

        //Populate Cause        ca.SetCause(isExt,C_BSS_NOT_EQUIPPED,C_BSS_NOT_EQUIPPED);
        upRelInd->AddIE(BSSAP_IEI_CAUSE,&ca);
}

static void
BuildUplinkReleaseCommand(BSSAP_Message* msg)
{

        BSSAP_Cse ca;
        bool isExt = 0;

         BSSAP_UplinkReleaseCommand *upRelCMD = (BSSAP_UplinkReleaseCommand *)msg;

        //Populate Cause
        ca.SetCause(isExt,C_BSS_NOT_EQUIPPED,C_BSS_NOT_EQUIPPED);
        upRelCMD->AddIE(BSSAP_IEI_CAUSE,&ca);
}

static void
BuildAuthenticationFailure(BSSAP_Message* msg)
{

	 ITS_OCTET            parasres[4]={88,77,66,44};

        //Message
        BSSAP_AuthenticationFailure *aFil = (BSSAP_AuthenticationFailure *)msg;

        //populate level3 header
        BSSAP_ParameterSres psr;
	psr.SetParameterSres(parasres);
        aFil->SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x03
        aFil->SetTIVal(TI_VALUE_3);                      //0x03
        aFil->AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

        //populate Reject cause
        BSSAP_Cse cU;
        cU.SetCause(0,C_ICORRECT_VALUE,C_ICORRECT_VALUE); //ILLEGAL MS
        aFil->AddIE(BSSAP_IEI_CC_CAUSE,&cU);
}





/*****************************************************************************
 *  Purpose:
 *      This function is used for getting the operation which user 
 *      wants to perform.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Choice - The operation to be encode
 *
 *  Return Value:
 *     User choice
 ****************************************************************************/
int
GetChoice()
{
    int choice = 0;
    int op = 0;

    printf("Enter your choice to send a message \n\n");
    printf("DTAP Messages \n");
    printf("============= \n");
    printf("\t Call Control Messages \n");  
    printf("\t --------------------- \n");
    printf("\t\t 1. Alerting(DT1) \n");
    printf("\t\t 2. Call Confirmed(DT1) \n");
    printf("\t\t 3. Call Proceeding(DT1) \n");
    printf("\t\t 4. Connect(DT1) \n");
    printf("\t\t 5. Connect Acknowledge(DT1) \n");
    printf("\t\t 6. Setup(DT1) \n");
    printf("\t\t 7. Disconnect(DT1) \n");
    printf("\t\t 8. Release(DT1) \n");
    printf("\t\t 9. Release Complete(DT1) \n\n");
    printf("\t Mobility Management Messages \n");
    printf("\t ---------------------------- \n");
    printf("\t\t11. Authentication Request(DT1) \n");
    printf("\t\t12. Authentication Response(DT1) \n");
    printf("\t\t13. Identity Request(DT1) \n");
    printf("\t\t14. Identity Response(DT1) \n");
    printf("\t\t15. TMSI Reallocation Command(DT1) \n");
    printf("\t\t16. TMSI Reallocation Complete(DT1) \n");
    printf("\t\t17. CM Service Accept(DT1) \n\n");
    printf("\t\t18. CM Service Request(DT1) \n\n");
    printf("\t\t19. Authentication Failure \n\n");
    printf("BSSMAP Messages \n");
    printf("=============== \n");
    printf("\t Radio Resources Management Messages \n");
    printf("\t ----------------------------------- \n");
    printf("\t\t30. Assignment Request(DT1) \n");
    printf("\t\t31. Assignment Complete(DT1) \n");
    printf("\t\t32. Block(UDT) \n");
    printf("\t\t33. Blocking Acknowledge(UDT) \n");
    printf("\t\t34. Clear Command(DT1) \n");
    printf("\t\t35. Clear Complete(DT1) \n");
    printf("\t\t36. Clear Request(DT1) \n");
    printf("\t\t37. Unblock(UDT) \n");
    printf("\t\t38. Unblocking Acknowledge(UDT) \n");
    printf("\t\t39. Handover Request(DT1) \n");
    printf("\t\t40. Handover Command(DT1) \n");
    printf("\t\t41. Reset(UDT) \n");
    printf("\t\t42. Reset Acknowledge(UDT) \n");
    printf("\t\t43. Paging(UDT) \n");
    printf("\t\t44. Overload(UDT) \n");
    printf("\t\t45. Cipher Mode Command(DT1) \n");
    printf("\t\t46. Cipher Mode Complete(DT1) \n");
    printf("\t\t47. Reset Circuit(UDT) \n");
    printf("\t\t48. Reset Circuit Acknowledge(UDT) \n");
    printf("\t\t49. Paging Response(CR) \n");
    printf("\t\t50. Handover Request Ack \n");
    printf("\t\t51. Handover Detection \n");
    printf("\t\t52. Handover Complete \n");
    printf("\t\t53. Handover Fail \n");
    printf("\t\t54. Unequipped Circuit \n");
    printf("\t\t55. Assignement Failure\n");
    printf("\t\t56. Circuit Gruop Block\n");
    printf("\t\t57. Circuit Gruop Block Ack\n");
    printf("\t\t58. Circuit Gruop Unblock\n");
    printf("\t\t59. Circuit Gruop Unblock Ack\n");
    printf("\t\t60. Location Updating\n");
    printf("\t\t61. Resource Indication \n");
    printf("\t\t62. Class Mark Update \n"); 
    printf("\t\t63. Cipher Mode Reject \n");
    printf("\t\t64. Location Updation Accept \n");
     printf("\t VGCS/VBS Messages \n");
    printf("\t ---------------------------- \n");
    printf("\t\t75.UplinkRelease Indication \n");
    printf("\t\t76.UplinkRelease Command \n");
 
    printf("\t\t99. EXIT \n\n");

    printf("Choice : ");
    scanf("%d",&choice);

    switch (choice)
    {
        case 1:
        {
            op = BSSAP_CC_MSG_ALERTING;
            break;
        }

        case 2:
        {
            op = BSSAP_CC_MSG_CALL_CONFIRMED;
            break;
        }

        case 3:
        {
            op = BSSAP_CC_MSG_CALL_PROCEEDING;
            break;
        }

        case 4:
        {
            op = BSSAP_CC_MSG_CONNECT;
            break;
        }

        case 5:
        {
            op = BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE;
            break;
        }

        case 6:
        {
            op = BSSAP_CC_MSG_SETUP;
            break;
        }

        case 7:
        {
            op = BSSAP_CC_MSG_DISCONNECT;
            break;
        }

        case 8:
        {
            op = BSSAP_CC_MSG_RELEASE;
            break;
        }

        case 9:
        {
            op = BSSAP_CC_MSG_RELEASE_COMPLETE;
            break;
        }

        case 11:
        {
            op = BSSAP_MSG_AUTHENTICATION_REQUEST;
            break;
        }

        case 12:
        {
            op = BSSAP_MSG_AUTHENTICATION_RESPONSE;
            break;
        }

        case 13:
        {
            op = BSSAP_MSG_IDENTITY_REQUEST;
            break;
        }

        case 14:
        {
            op = BSSAP_MSG_IDENTITY_RESPONSE;
            break;
        }

        case 15:
        {
            op = BSSAP_MSG_TMSI_REALLOC_COMMAND;
            break;
        }

        case 16:
        {
            op = BSSAP_MSG_TMSI_REALLOC_COMPLETE;
            break;
        }

        case 17:
        {
            op = BSSAP_MSG_CM_SERVICE_ACCEPT;
            break;
        }

        case 18:
        {
            op = BSSAP_MSG_CM_SERVICE_REQUEST;
            break;
        }

	case 19:
	{
	    op = BSSAP_MSG_AUTHENTICATION_FAILURE;
            break;
        }


        case 30:
        {
            op = BSSAP_MSG_ASSIGN_REQ;
            break;
        }

        case 31:
        {
            op = BSSAP_MSG_ASSIGN_CMP;
            break;
        }

        case 32:
        {
            op = BSSAP_MSG_BLOCK;
            break;
        }

        case 33:
        {
            op = BSSAP_MSG_BLOCK_ACK;
            break;
        }      

        case 34:
        {
            op = BSSAP_MSG_CLEAR_COMMAND;
            break;
        }

        case 35:
        {
            op = BSSAP_MSG_CLEAR_CMP;
            break;
        }

        case 36:
        {
            op = BSSAP_MSG_CLEAR_REQUEST;
            break;
        }

        case 37:
        {
            op = BSSAP_MSG_UNBLOCK;
            break;
        }

        case 38:
        {
            op = BSSAP_MSG_UNBLOCK_ACK;
            break;
        }

        case 39:
        {
            op = BSSAP_MSG_HANDOVER_REQUEST;
            break;
        }

        case 40:
        {
            op = BSSAP_MSG_HANDOVER_COMMAND;
            break;
        }

        case 41:
        {
            op = BSSAP_MSG_RESET;
            break;
        }
 
        case 42:
        {
            op = BSSAP_MSG_RESET_ACK;
            break;
        }
        
        case 43:
        {
            op = BSSAP_MSG_PAGING;
            break;
        }
        
        case 44:
        {
            op = BSSAP_MSG_OVERLOAD;
            break;
        }
                                                                                                           
        case 45:
        {
            op = BSSAP_MSG_CIPHER_MODE_CMD;
            break;
        }

        case 46:
        {
            op = BSSAP_MSG_CIPHER_MODE_COMPLETE;
            break;
        }
       
        case 47:
        {
            op = BSSAP_MSG_RESET_CIRCUIT;
            break;
        }

        case 48:
        {
            op = BSSAP_MSG_RESET_CIRCUIT_ACK;
            break;
        }
                                                                                                  
        case 49:
        {
            op = BSSAP_MSG_PAGING_RESPONSE;
            break;
        }
                                                                                                                    
        case 50:
        {
            op = BSSAP_MSG_HANDOVER_REQ_ACK;
            break;
        }
                                                                                                                    
        case 51:
        {
            op = BSSAP_MSG_HANDOVER_DET;
            break;
        }
                                                                                                                    
        case 52:
        {
            op = BSSAP_MSG_HANDOVER_CMP;
            break;
        }
                                                                                                                    
        case 53:
        {
            op = BSSAP_MSG_HANDOVER_FAIL;
            break;
        }
                                                                                                                    
        case 54:
        {
            op = BSSAP_MSG_UNEQUIPPED_CKT;
            break;
        }
                                                                                                                    
        case 55:
        {
            op = BSSAP_MSG_ASSIGN_FAIL;
            break;
        }

        case 56:
        {
            op = BSSAP_MSG_CKT_GROUP_BLOCK;
            break;
        }
                                                                                                                                              
        case 57:
        {
            op = BSSAP_MSG_CKT_GRP_BLK_ACK;
            break;
        }
                                                                                                                                              
        case 58:
        {
            op = BSSAP_MSG_CKT_GRP_UNBLOCK;
            break;
        }
                                                                                                                                              
        case 59:
        {
            op = BSSAP_MSG_CKT_GRP_UNBLKING_ACK;
            break;
        }
                                                                                                                    
        case 60:
        {
            op = BSSAP_MSG_LOCATION_UPDATION_REQ;
            break;
        }

	case 61:
	{
		op = BSSAP_MSG_RESOURCE_INDICATION;
		break;
	}

	case 62:
	{
		op =  BSSAP_MSG_CLASSMARK_UPDATE;
                break;
        }

	case 63 :
	{
		op = BSSAP_MSG_CIPHER_MODE_REJECT;
            break;
        }

	case 64 :
	{
		op = BSSAP_MSG_LOCATION_UPDATING_ACCEPT;
		break;
        }

        case 99:
        {
            exit(0);
        }

	case 75:
        {
           op = BSSAP_MSG_UPLINK_RELEASE_INDICATION;
           break;
        }

        case 76:
        {
           op = BSSAP_MSG_UPLINK_RELEASE_COMMAND;
           break;
        }
	
        default:
            printf("Invalid Choice \n");
    }
    return op;
}

/*****************************************************************************
 *  Purpose:

 *      This function is used for creating an Instance of the Message.
 *
 *  Input Parameters:
 *      msgid - Message ID 
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *      BSSAP_Message object.
 *
 *  Return Value:
 *     intstace of the Object.
 ****************************************************************************/
static BSSAP_Message*
CreateInstance(int msgid)
{
    BSSAP_Message* ret = NULL;

    switch(msgid)
    {
        case BSSAP_MSG_LOCATION_UPDATION_REQ:
        {
            ret = new BSSAP_CompleteLayer3Information;
            break;
        }

	case BSSAP_MSG_AUTHENTICATION_FAILURE:
	{
	     ret = new BSSAP_AuthenticationFailure;
                break;
        }

	case BSSAP_MSG_LOCATION_UPDATING_ACCEPT:
	{
		ret = new BSSAP_LocationUpdatingAccept;
                break;
        }

	case BSSAP_MSG_RESOURCE_INDICATION:
         {
               ret = new BSSAP_ResourceIndication;
               break;
         }

	case BSSAP_MSG_CIPHER_MODE_REJECT:
        {
                ret = new BSSAP_CipherModeReject;
                break;
        }


        case BSSAP_MSG_CLASSMARK_UPDATE:
         {
                ret = new BSSAP_ClassmarkUpdate;
                break;
         }
	
        case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
        {
            ret = new BSSAP_CircuitGroupUnblockAck;
            break;
        }
        
	case BSSAP_MSG_CKT_GRP_UNBLOCK:
        {
            ret = new BSSAP_CircuitGroupUnblock;
            break;
        }
                                                                                                                                              
        case BSSAP_MSG_CKT_GRP_BLK_ACK:
        {
            ret = new BSSAP_CircuitGroupBlockAcknowledge;
            break;
        }
                                                                                                                                              
        case BSSAP_MSG_CKT_GROUP_BLOCK:
        {
            ret = new BSSAP_CircuitGroupBlock;
            break;
        }

        case BSSAP_MSG_ASSIGN_FAIL:
        {
            ret = new BSSAP_AssignmentFailure;
            break;
        }

        case BSSAP_MSG_UNEQUIPPED_CKT:
        {
            ret = new BSSAP_UnequippedCircuit;
            break;
        }

        case BSSAP_MSG_HANDOVER_FAIL:
        {
            ret = new BSSAP_HandoverFailure;
            break;
        }

        case BSSAP_MSG_HANDOVER_CMP:
        {
            ret = new BSSAP_HandoverComplete;
            break;
        }

        case BSSAP_MSG_HANDOVER_DET:
        {
            ret = new BSSAP_HandoverDetect;
            break;
        }

        case BSSAP_MSG_HANDOVER_REQ_ACK:
        {
            ret = new BSSAP_HandoverRequestAcknowledge;
            break;
        }

        case BSSAP_MSG_PAGING_RESPONSE:
        case BSSAP_MSG_CM_SERVICE_REQUEST:
        {
            ret = new BSSAP_CompleteLayer3Information;
            break;
        }

        case BSSAP_MSG_ASSIGN_REQ:
        {
            ret = new BSSAP_AssignmentRequest;
            break;
        }

        case BSSAP_CC_MSG_CALL_PROCEEDING:
        {
            ret = new BSSAP_CallProceeding;
            break;
        } 

        case BSSAP_CC_MSG_CONNECT:
        {
            ret = new BSSAP_Connect;
            break; 
        }

        case BSSAP_CC_MSG_SETUP:
        {
            ret = new BSSAP_Setup;
            break;
        }

        case BSSAP_CC_MSG_DISCONNECT:
        {
            ret = new BSSAP_Disconnect;
            break;
        }

	case BSSAP_MSG_UPLINK_RELEASE_INDICATION:
        {
                ret = new BSSAP_UplinkReleaseIndication;
                break;
        }

       case BSSAP_MSG_UPLINK_RELEASE_COMMAND:
       {
                ret = new BSSAP_UplinkReleaseCommand;
                break;
       }
	

        case BSSAP_CC_MSG_RELEASE:
        {
            ret = new BSSAP_Release;
            break;
        }

        case BSSAP_CC_MSG_CALL_CONFIRMED:
        {
            ret = new BSSAP_CallConfirmed;
            break;
        }

        case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
        {
            ret = new BSSAP_ConnectAck;
            break;
        }

        case BSSAP_CC_MSG_RELEASE_COMPLETE:
        {
            ret = new BSSAP_ReleaseComplete;
            break;
        }

        case BSSAP_CC_MSG_ALERTING:
        {
            ret = new BSSAP_Alerting;
            break;
        }

        case BSSAP_MSG_AUTHENTICATION_REQUEST:
        {
            ret = new BSSAP_AuthenticationRequest;
            break;
        }

        case BSSAP_MSG_PAGING:
        {
            ret = new BSSAP_Paging;
            break;
        }

        case BSSAP_MSG_CIPHER_MODE_CMD:
        {
            ret = new BSSAP_CipherModeCommand;
            break;
        }

        case BSSAP_MSG_CIPHER_MODE_COMPLETE:
        {
            ret = new BSSAP_CipherModeComplete;
            break;
        }

        case BSSAP_MSG_CLEAR_COMMAND:
        {
            ret = new BSSAP_ClearCommand;
            break;
        }

        case BSSAP_MSG_CLEAR_CMP:
        {
            ret = new BSSAP_ClearComplete;
            break;
        }

        case BSSAP_MSG_CLEAR_REQUEST:
        {
            ret = new BSSAP_ClearRequest;
            break;
        }

        case BSSAP_MSG_BLOCK:
        {
            ret = new BSSAP_Block;
            break;
        }

        case BSSAP_MSG_BLOCK_ACK:
        {
            ret = new BSSAP_BlockAcknowledge;
            break;
        }

        case BSSAP_MSG_UNBLOCK:
        {
            ret = new BSSAP_Unblock;
            break;
        }

        case BSSAP_MSG_UNBLOCK_ACK:
        {
            ret = new BSSAP_UnblockAcknowledge;
            break;
        }

        case BSSAP_MSG_RESET:
        {
            ret = new BSSAP_Reset;
            break;
        }

        case BSSAP_MSG_RESET_ACK:
        {
            ret = new BSSAP_ResetAcknowledge;
            break;
        }                                 
                                     
        case BSSAP_MSG_OVERLOAD:
        {
            ret = new BSSAP_Overload;
            break;
        }

        case BSSAP_MSG_RESET_CIRCUIT:
        {
            ret = new BSSAP_ResetCircuit;
            break;
        }

        case BSSAP_MSG_RESET_CIRCUIT_ACK:
        {
            ret = new BSSAP_ResetCircuitAcknowledge;
            break;
        }
                                                      
        case BSSAP_MSG_ASSIGN_CMP:
        {
            ret = new BSSAP_AssignmentComplete;
            break;
        }

        case BSSAP_MSG_IDENTITY_REQUEST:
        {
            ret = new BSSAP_IdentityRequest;
            break;
        }

        case BSSAP_MSG_IDENTITY_RESPONSE:
        {
            ret = new BSSAP_IdentityResponse;
            break;
        }

        case BSSAP_MSG_CM_SERVICE_ACCEPT:
        {
            ret = new BSSAP_CMServiceAccept;
            break;
        }

        case BSSAP_MSG_TMSI_REALLOC_COMMAND:
        {
            ret = new BSSAP_TMSIReallocCommand;
            break;
        }

        case BSSAP_MSG_TMSI_REALLOC_COMPLETE:
        {
            ret = new BSSAP_TMSIReallocComplete;
            break;
        }

        case BSSAP_MSG_AUTHENTICATION_RESPONSE:
        {
            ret = new BSSAP_AuthenticationResponse;
            break;
        }


        case BSSAP_MSG_HANDOVER_REQUEST:
        {
            ret = new BSSAP_HandoverRequest;
            break;
        }

        case BSSAP_MSG_HANDOVER_COMMAND:
        {
            ret = new BSSAP_HandoverCommand;
            break;
        }

        default:
            printf("Invalid msgid \n");
    }

    return ret;
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Decoding the meassage parameters.
 *
 *  Input Parameters:
 *     encOctets - Data to be decoded.
 *     len       - lenght of the Data.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
static void DecodeParams(ITS_OCTET* buf, int len)
{
    BSSAP_Message* msg;
    int ret;
  
    ret = BSSAP_Message::Decode(buf, len, &msg);

    if (ret != ITS_SUCCESS)
    {
        cout << "Error decoding message; error code: " << ret << endl;
        return;
    }

    printf("\nDecoding\n");
    printf("--------\n");
    printf("\nRaw bytes before Decoding......\n\n");

    for (int i = 0; i < len; i++)
    {
        printf("%02x ",buf[i]);

        if (((i+1) %16) == 0)
            printf("\n");
    }

    printf("\n------------------------------------------------------");
    printf("\nMessage after Decoding......\n\n");

    GetParams(msg->GetMsgType(), msg);

    printf("\n");
    printf("\n------------------------------------------------------\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for setting the meassage parameters.
 *
 *  Input Parameters:
 *      val - Message ID
 *      msg - instance of BSSAP message object.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
static
void SetParams(int val, BSSAP_Message* msg)
{
    switch(val)
    {
        case BSSAP_MSG_LOCATION_UPDATION_REQ:
              BuildLocationUpdationReq(msg);
              break;

	case BSSAP_MSG_LOCATION_UPDATING_ACCEPT:
	     BuildLocationUpdatingAccept(msg);
	     break;

         case BSSAP_MSG_RESOURCE_INDICATION:
             BuildResouceIndicationMessage(msg);
             break;

	case BSSAP_MSG_AUTHENTICATION_FAILURE:
             BuildAuthenticationFailure(msg);
             break;

	case BSSAP_MSG_ASSIGN_FAIL:
            BuildAssignFail(msg);
            break;


	case BSSAP_MSG_CLASSMARK_UPDATE:
             BuildClassMarkUpdate(msg);
             break;

	 case BSSAP_MSG_CIPHER_MODE_REJECT:
             BuildCipherModeReject(msg);
             break;


	case BSSAP_MSG_UPLINK_RELEASE_INDICATION:
             BuildUplinkReleaseIndication(msg);
             break;

         case BSSAP_MSG_UPLINK_RELEASE_COMMAND:
             BuildUplinkReleaseCommand(msg);
             break;
	     

        case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
            BuildCktGrpUnblkAck(msg);
            break;
                                                                                                                                              
        case BSSAP_MSG_CKT_GRP_UNBLOCK:
            BuildCktGrpUnblk(msg);
            break;
                                                                                                                                              
        case BSSAP_MSG_CKT_GRP_BLK_ACK:
            BuildCktGrpBlkAck(msg);
            break;
                                                                                                                                              
        case BSSAP_MSG_CKT_GROUP_BLOCK:
            BuildCktGrpBlk(msg);
            break;

        case BSSAP_MSG_UNEQUIPPED_CKT:
            BuildUnequippeCkt(msg);
            break;

        case BSSAP_MSG_HANDOVER_FAIL:
            BuildHandoverFail(msg);
            break;

        case BSSAP_MSG_HANDOVER_CMP:
            BuildHandoverCmp(msg);
            break;

        case BSSAP_MSG_HANDOVER_DET:
            BuildHandoverDet(msg);
            break;

        case BSSAP_MSG_HANDOVER_REQ_ACK:
            BuildHandoverReqAck(msg);
            break;

        case BSSAP_MSG_CM_SERVICE_REQUEST:
            BuildCompL3(msg);
            break;
                                                                                                                                              
        case BSSAP_MSG_ASSIGN_REQ:
            BuildAssignmentRequest(msg) ;
            break;

        case BSSAP_CC_MSG_CALL_PROCEEDING:
            BuildCallProceeding(msg);
            break;

        case BSSAP_CC_MSG_CONNECT:
            BuildConnect(msg);
            break;  

        case BSSAP_CC_MSG_SETUP:
            BuildSetup(msg);
            break;

        case BSSAP_CC_MSG_DISCONNECT:
            BuildDisconnect(msg);
            break;

        case BSSAP_CC_MSG_RELEASE:
            BuildRelease(msg);
            break;

        case BSSAP_CC_MSG_CALL_CONFIRMED:
            BuildCallConfirmed(msg);
            break;

        case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
            BuildConnectAcknowledge(msg);
            break;

        case BSSAP_CC_MSG_RELEASE_COMPLETE:
            BuildReleaseComplete(msg);
            break;

        case BSSAP_CC_MSG_ALERTING:
            BuildAlerting(msg);
            break;

        case BSSAP_MSG_AUTHENTICATION_REQUEST:
            BuildAuthReq(msg);
            break;

        case BSSAP_MSG_PAGING:
            BuildPaging(msg);
            break;

        case BSSAP_MSG_CIPHER_MODE_CMD:
            BuildCipherModeCmd(msg);
            break;

        case BSSAP_MSG_CIPHER_MODE_COMPLETE:
            BuildCipherModeComplete(msg);
            break;

        case BSSAP_MSG_CLEAR_COMMAND:
            BuildClearCommand(msg);
            break;

        case BSSAP_MSG_CLEAR_CMP:
            BuildClearComplete(msg);
            break;

        case BSSAP_MSG_CLEAR_REQUEST:
            BuildClearRequest(msg);
            break;

        case BSSAP_MSG_BLOCK:
            BuildBlock(msg);
            break;

        case BSSAP_MSG_BLOCK_ACK:
            BuildBlockAck(msg);
            break;

        case BSSAP_MSG_UNBLOCK:
            BuildUnblock(msg);
            break;

        case BSSAP_MSG_UNBLOCK_ACK:
            BuildUnblockAck(msg);
            break;

        case BSSAP_MSG_RESET:
            BuildReset(msg);
            break;

        case BSSAP_MSG_RESET_ACK:
            BuildResetAck(msg);
            break;

        case BSSAP_MSG_OVERLOAD:
            BuildOverload(msg);
            break;

        case BSSAP_MSG_RESET_CIRCUIT:
            BuildResetCircuit(msg);
            break;

        case BSSAP_MSG_RESET_CIRCUIT_ACK:
            BuildResetCircuitAck(msg);
            break;

        case BSSAP_MSG_ASSIGN_CMP:
            BuildAssignComplete(msg);
            break;

        case BSSAP_MSG_IDENTITY_REQUEST:
            BuildIdenReq(msg);
            break;
        
        case BSSAP_MSG_IDENTITY_RESPONSE:
            BuildIdenResp(msg);
            break;
        
        case BSSAP_MSG_CM_SERVICE_ACCEPT:
            BuildCmServAcc(msg);
            break;

        case BSSAP_MSG_TMSI_REALLOC_COMMAND:
            BuildTmsiRealCmd(msg);
            break;
        
        case BSSAP_MSG_TMSI_REALLOC_COMPLETE:
            BuildTmsiRealCmp(msg);
            break;
        
        case BSSAP_MSG_AUTHENTICATION_RESPONSE:
            BuildAuthenResp(msg);
            break;
        
        case BSSAP_MSG_PAGING_RESPONSE:
            BuildCompL3Pag(msg);
            break;
        
        case BSSAP_MSG_HANDOVER_REQUEST:
            BuildHandoverReq(msg);
            break;
        
        case BSSAP_MSG_HANDOVER_COMMAND:
            BuildHandoverCmd(msg);
            break;
        
        default:
            printf("Message not implemented in this application\n");
    }
}

static
void GetParams(int val, BSSAP_Message* msg)
{
    switch(val)
    {

        case BSSAP_MSG_ASSIGN_REQ:
            PrintBSSMAPMsgAssignReq(msg) ;
            break;

        case BSSAP_CC_MSG_CALL_PROCEEDING:
            PrintBSSMAPMsgCallProceeding(msg);
            break;
        
        case BSSAP_CC_MSG_CONNECT:
            PrintBSSMAPMsgConnect(msg);
            break;

	case BSSAP_CC_MSG_PROGRESS:
	    printf("\t\t PROGRESS \n\n");
	    PrintBSSMAPMsgProgress(msg);
	    break;

        case BSSAP_CC_MSG_SETUP:
            PrintBSSMAPMsgSetup(msg);
            break;

        case BSSAP_CC_MSG_DISCONNECT:
            PrintBSSMAPMsgDisconnect(msg);
            break;
        
        case BSSAP_CC_MSG_RELEASE:
            PrintBSSMAPMsgRelease(msg);
            break;

        case BSSAP_CC_MSG_CALL_CONFIRMED:
            PrintBSSMAPMsgCallConfirm(msg);
            break;

        case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
            PrintBSSMAPMsgConnectAck(msg);
            break;

        case BSSAP_CC_MSG_RELEASE_COMPLETE:
            PrintBSSMAPMsgReleaseComplete(msg);
            break;

        case BSSAP_CC_MSG_ALERTING:
            PrintBSSMAPMsgAlerting(msg);
            break;

        case BSSAP_MSG_CIPHER_MODE_CMD:
            PrintBSSMAPMsgCipherModeCmd(msg);
            break;

        case BSSAP_MSG_CIPHER_MODE_COMPLETE:
            PrintBSSMAPMsgCipherModeComplete(msg);
            break;

        case BSSAP_MSG_CLEAR_COMMAND:
            PrintBSSMAPMsgClrCmd(msg);
            break;

        case BSSAP_MSG_CLEAR_CMP:
            PrintBSSMAPMsgClrComplete(msg);
            break;

        case BSSAP_MSG_CLEAR_REQUEST:
            PrintBSSMAPMsgClrReq(msg);
            break;

        case BSSAP_MSG_BLOCK:
            PrintBSSMAPMsgBlock(msg);
            break;

        case BSSAP_MSG_BLOCK_ACK:
            PrintBSSMAPMsgBlockAck(msg);
            break;

        case BSSAP_MSG_UNBLOCK:
            PrintBSSMAPMsgUnblock(msg);
            break;

        case BSSAP_MSG_UNBLOCK_ACK:
            PrintBSSMAPMsgUnblockAck(msg);
            break;

        case BSSAP_MSG_RESET:
            PrintBSSMAPMsgReset(msg);
            break;

        case BSSAP_MSG_RESET_ACK:
            PrintBSSMAPMsgResetAck(msg);
            break;

        case BSSAP_MSG_OVERLOAD:
            PrintBSSMAPMsgOverload(msg);
            break;

        case BSSAP_MSG_RESET_CIRCUIT:
            PrintBSSMAPMsgResetCircuit(msg);
            break;

        case BSSAP_MSG_RESET_CIRCUIT_ACK:
            PrintBSSMAPMsgResetCircuitAck(msg);
            break;

        case BSSAP_MSG_ASSIGN_CMP:
            PrintBSSMAPMsgAssignComplete(msg);
            break;

	case BSSAP_MSG_CONFUSION:
	     printf("\t\t CONFUSION \n\n");
             PrintBSSMAPMsgConfusion;
	     break;

        default:
            printf("Message not implemented in this application\n");
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for encoding the meassage.
 *
 *  Input Parameters:
 *      msg - instance of BSSAP message object.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     buf - Data to be encoded.
 *     len - lenght of the Data.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
static
void EncodeParams(BSSAP_Message* msg, ITS_OCTET* buf, int *len)
{
    int ret;

    printf("\nEncoding\n");
    printf("--------\n");

    ret = BSSAP_Message::Encode(&buf[0], *len, msg);
    if (ret != ITS_SUCCESS)
    {
        cout << "Error encoding message; error code: " << ret << endl;
        return;
    }

    printf("\nEncoded raw bytes......\n\n");
    for (int i = 0; i < *len; i++)
    {
        printf("%02x ",buf[i]);

        if (((i+1) %16) == 0)
            printf("\n");
    }

    printf("\n------------------------------------------------------");
    printf("\nMessage after Encoding......\n\n");
    
    //PrintBSSAPMessage(buf, *len); 
    
    printf("\n");
    printf("\n------------------------------------------------------\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Interpreting received data.
 *
 *  Input Parameters:
 *     encOctets - Data to be decoded.
 *     len       - lenght of the Data.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
void
InterpretMsg(ITS_OCTET* encOctets, int len)
{
    DecodeParams(encOctets, len);
    cout << "Decode Completed" << endl << endl;
}

/*****************************************************************************
 *  Purpose:
 *      This function is used for Buildig the Message .
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *     octets - Data to be encoded.
 *     len    - lenght of the Data.
 *
 *  Return Value:
 *     None
 ****************************************************************************/
void
BuildMsg(ITS_OCTET* octets, int* len)
{
    BSSAP_Message* msg = NULL;
    ITS_INT op ;

    op = GetChoice();

    msg = CreateInstance(op);
    if (!msg)
    {
        cout << "Message creation failed" << endl;
        return;
    }

    SetParams(op, msg);

    EncodeParams(msg, octets, len);

    delete msg;
    msg = NULL;
    cout << "Encode Completed" << endl;
    return;
}

