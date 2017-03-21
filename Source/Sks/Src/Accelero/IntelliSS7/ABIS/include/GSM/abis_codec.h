/***************************************************************************
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: abis_codec.h,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:52  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.6  2006/04/07 09:28:39  yranade
 *  RF Max Power reduction IE added (sgavalkar)
 *
 *  Revision 1.1.2.5  2006/03/28 09:16:32  yranade
 *  TRX Hello message added. (sgavalkar)
 *
 *  Revision 1.1.2.4  2005/09/27 12:01:17  mkrishna
 *  Error case added
 *
 *  Revision 1.1.2.3  2005/09/23 06:42:59  mkrishna
 *  Bug fixes added
 *
 *  Revision 1.1.2.2  2005/08/29 09:02:35  mkrishna
 *  Added header file for simulator
 *
 *  Revision 1.1.2.1  2005/08/16 11:44:14  mkrishna
 *  Added Initial version after unit testing.
 *
 *
 ****************************************************************************/
                                                                                                                                              
#if !defined(ABIS_CODEC_H)
#define ABIS_CODEC_H

#include <its.h>
#include <stdio.h>

#define MAX_OCTET_LENGTH        256
#define MAX_CONTENT_LENGTH      280  
#define MAX_TRAFFIC_FUNS_SIZE   66      
#define MAX_NETWORK_FUNS_SIZE   200      
#define MAX_PARAM_LENGTH        2      


/*  SET MACROS
 *  ---------
 *  macro's used to set optionalBitMaps in Messages.
 *  The usage of macro can be done in two ways
 *  1. if msg is pointer, then it can be passed directly.
 *  2. if msg is static variable, then it can be passed as ((&msg))
 */

/* TRAFFIC MANAGEMENT MESSAGES */

/* Establish Indication in Radio Link Layer Management */
#define CLEAR_TM_RLLM_EI_OPTIONAL_BIT_MAP(msg) \
        (msg->u.rllmMsg.u.estInd.optionalBitMap = 0x00)                   

#define SET_TM_RLLM_EI_L3_INFO(msg) \
        (msg->u.rllmMsg.u.estInd.optionalBitMap |= 0x01)

/* Dedicated Channel Management */

/*  Channel Activation message */ 
#define CLEAR_TM_DCM_CA_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap = 0x00)                   

#define SET_TM_DCM_CA_CHANNEL_ID(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x01) 

#define SET_TM_DCM_CA_ENCRYPT_INFO(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x02)

#define SET_TM_DCM_CA_BS_POWER(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x04) 

#define SET_TM_DCM_CA_MS_POWER(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x08)

#define SET_TM_DCM_CA_BS_POWER_PARAM(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x10)

#define SET_TM_DCM_CA_MS_POWER_PARAM(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x20)
        
#define SET_TM_DCM_CA_PHYSICAL_CONTEXT(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x40)

#define SET_TM_DCM_CA_SAACH_INFO(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x80)

#define SET_TM_DCM_CA_UIC(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x0100)

#define SET_TM_DCM_CA_MAIN_CHANNEL_REF(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x0200)

#define SET_TM_DCM_CA_MULTI_RATE_CONFIG(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x0400)

#define SET_TM_DCM_CA_MULTI_RATE_CONTROL(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x0800)
 
#define SET_TM_DCM_CA_SUPPORTED_CODEC_TYPES(msg) \
        (msg->u.dcmMsg.u.chanActiv.optionalBitMap |= 0x1000)

/* Handover Detection */
#define CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.handoDet.optionalBitMap = 0x00)                   

#define SET_TM_DCM_HD_ACCESS_DELAY(msg) \
        (msg->u.dcmMsg.u.handoDet.optionalBitMap |= 0x01)

/* Measurement Result */
#define CLEAR_TM_DCM_MR_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.measRes.optionalBitMap = 0x00)

#define SET_TM_DCM_MR_L1_INFO(msg) \
        (msg->u.dcmMsg.u.measRes.optionalBitMap |= 0x01)  

#define SET_TM_DCM_MR_L3_INFO(msg) \
        (msg->u.dcmMsg.u.measRes.optionalBitMap |= 0x02)

#define SET_TM_DCM_MR_MS_TIMING_OFFSET(msg) \
        (msg->u.dcmMsg.u.measRes.optionalBitMap |= 0x04)

/* Mode Modify */ 
#define CLEAR_TM_DCM_MM_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.modeModifyReq.optionalBitMap = 0x00)                  

#define SET_TM_DCM_MM_ENCRYPT_INFO(msg) \
        (msg->u.dcmMsg.u.modeModifyReq.optionalBitMap |= 0x01)

#define SET_TM_DCM_MM_MAIN_CHANNEL_REF(msg) \
        (msg->u.dcmMsg.u.modeModifyReq.optionalBitMap |= 0x02)

#define SET_TM_DCM_MM_MULTI_RATE_CONFIG(msg) \
        (msg->u.dcmMsg.u.modeModifyReq.optionalBitMap |= 0x04)

#define SET_TM_DCM_MM_MULTI_RATE_CONTROL(msg) \
        (msg->u.dcmMsg.u.modeModifyReq.optionalBitMap |= 0x08)

#define SET_TM_DCM_MM_SUPPORTED_CODEC_TYPES(msg) \
        (msg->u.dcmMsg.u.modeModifyReq.optionalBitMap |= 0x10)

/* Physical Context Confirm */
#define CLEAR_TM_DCM_PCC_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.phyContextConf.optionalBitMap = 0x00)

#define SET_TM_DCM_PCC_PHYSICAL_CONTEXT(msg) \
        (msg->u.dcmMsg.u.phyContextConf.optionalBitMap |= 0x01)

/* MS Power Control */
#define CLEAR_TM_DCM_MPC_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.mspowerControl.optionalBitMap = 0x00)

#define SET_TM_DCM_MPC_MS_POWER_PARAMS(msg) \
        (msg->u.dcmMsg.u.mspowerControl.optionalBitMap |= 0x01)

/* BS Power Control */
#define CLEAR_TM_DCM_BPC_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.bspowerControl.optionalBitMap = 0x00)
                                                                                                                                              
#define SET_TM_DCM_BPC_BS_POWER_PARAMS(msg) \
        (msg->u.dcmMsg.u.bspowerControl.optionalBitMap |= 0x01)

/* SAACH Info Modify */
#define CLEAR_TM_DCM_SIM_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.sacchInfoMod.optionalBitMap = 0x00)

#define SET_TM_DCM_SIM_L3_INFO(msg) \
        (msg->u.dcmMsg.u.sacchInfoMod.optionalBitMap  |= 0x01)

#define SET_TM_DCM_SIM_STARTING_TIME(msg) \
        (msg->u.dcmMsg.u.sacchInfoMod.optionalBitMap  |= 0x02) 

/* Talker Detection */
#define CLEAR_TM_DCM_TD_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.talkerDet.optionalBitMap = 0x00)

#define SET_TM_DCM_TD_ACCESS_DELAY(msg) \
        (msg->u.dcmMsg.u.talkerDet.optionalBitMap |= 0x01)

/* Listener Detection */
#define CLEAR_TM_DCM_LD_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.listenerDet.optionalBitMap = 0x00)

#define SET_TM_DCM_LD_ACCESS_DELAY(msg) \
        (msg->u.dcmMsg.u.listenerDet.optionalBitMap |= 0x01)

/* MultiRate Codec Modification Request */
#define CLEAR_TM_DCM_MCMR_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.mrCodecModReq.optionalBitMap = 0x00) 

#define SET_TM_DCM_MCMR_MULTI_RATE_CONFIG(msg) \
        (msg->u.dcmMsg.u.mrCodecModReq.optionalBitMap |= 0x01)

/* MultiRate Codec Modification Acknowledge */
#define CLEAR_TM_DCM_MCMA_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.mrCodecModAck.optionalBitMap = 0x00)

#define SET_TM_DCM_MCMA_MULTI_RATE_CONFIG(msg) \
        (msg->u.dcmMsg.u.mrCodecModAck.optionalBitMap |= 0x01)

/* TFO Modification Request */
#define CLEAR_TM_DCM_TMR_OPTIONAL_BIT_MAP(msg) \
        (msg->u.dcmMsg.u.tfoModReq.optionalBitMap = 0x00)

#define SET_TM_DCM_TMR_SUPPORTED_CODEC_TYPE(msg) \
        (msg->u.dcmMsg.u.tfoModReq.optionalBitMap |= 0x01)

/* Common Channel Management */

/* BCCH Information */
#define CLEAR_TM_CCM_BI_OPTIONAL_BIT_MAP(msg) \
        (msg->u.ccmMsg.u.bcchInfo.optionalBitMap = 0x00)

#define SET_TM_CCM_BI_FULL_BCCH_INFO(msg) \
        (msg->u.ccmMsg.u.bcchInfo.optionalBitMap |= 0x01)

#define SET_TM_CCM_BI_STARTING_TIME(msg) \
        (msg->u.ccmMsg.u.bcchInfo.optionalBitMap |= 0x02)

/* Channel Required */
#define CLEAR_TM_CCM_CR_OPTIONAL_BIT_MAP(msg) \
        (msg->u.ccmMsg.u.chanRqd.optionalBitMap = 0x00)

#define SET_TM_CCM_CR_PHYSICAL_CONTEXT(msg) \
        (msg->u.ccmMsg.u.chanRqd.optionalBitMap |= 0x01)

/* Paging Command */
#define CLEAR_TM_CCM_PC_OPTIONAL_BIT_MAP(msg) \
        (msg->u.ccmMsg.u.pagingCmd.optionalBitMap = 0x00)

#define SET_TM_CCM_PC_CHANNEL_NEEDED(msg) \
        (msg->u.ccmMsg.u.pagingCmd.optionalBitMap |= 0x01)

#define SET_TM_CCM_PC_EMLPP_PRIORITY(msg) \
        (msg->u.ccmMsg.u.pagingCmd.optionalBitMap |= 0x02)

/* SMS Broadcast Request */
#define CLEAR_TM_CCM_SBR_OPTIONAL_BIT_MAP(msg) \
        (msg->u.ccmMsg.u.smsBcReq.optionalBitMap = 0x00)

#define SET_TM_CCM_SBR_SMSCB_CHANNEL_IND(msg) \
        (msg->u.ccmMsg.u.smsBcReq.optionalBitMap |= 0x01)

/* SMS Broadcast Command */
#define CLEAR_TM_CCM_SBC_OPTIONAL_BIT_MAP(msg) \
        (msg->u.ccmMsg.u.smsBcCmd.optionalBitMap = 0x00)

#define SET_TM_CCM_SBC_SMSCB_CHANNEL_IND(msg) \
        (msg->u.ccmMsg.u.smsBcCmd.optionalBitMap |= 0x01)

/* CBCH Load Indication */
#define CLEAR_TM_CCM_CLI_OPTIONAL_BIT_MAP(msg) \
        (msg->u.ccmMsg.u.cbchLoadInd.optionalBitMap = 0x00)

#define SET_TM_CCM_CLI_SMSCB_CHANNEL_IND(msg) \
        (msg->u.ccmMsg.u.cbchLoadInd.optionalBitMap |= 0x01)

/* Notification Command */
#define CLEAR_TM_CCM_NC_OPTIONAL_BIT_MAP(msg) \
        (msg->u.ccmMsg.u.notCmd.optionalBitMap = 0x00)

#define SET_TM_CCM_NC_GROUP_CALL_REFERENCE(msg) \
        (msg->u.ccmMsg.u.notCmd.optionalBitMap |= 0x01)

#define SET_TM_CCM_NC_CHANNEL_DESCRIPTION(msg) \
        (msg->u.ccmMsg.u.notCmd.optionalBitMap |= 0x02)

#define SET_TM_CCM_NC_NCH_DRX_INFO(msg) \
        (msg->u.ccmMsg.u.notCmd.optionalBitMap |= 0x04)

/* TRX Management */

/* SACCH Filling */
#define CLEAR_TM_TRXM_SF_OPTIONAL_BIT_MAP(msg) \
        (msg->u.trxmMsg.u.sacchFill.optionalBitMap = 0x00)

#define SET_TM_TRXM_SF_L3_INFO(msg) \
        (msg->u.trxmMsg.u.sacchFill.optionalBitMap |= 0x01)

#define SET_TM_TRXM_SF_STARTING_TIME(msg) \
        (msg->u.trxmMsg.u.sacchFill.optionalBitMap |= 0x02)

/* Error Report */
#define CLEAR_TM_TRXM_ER_OPTIONAL_BIT_MAP(msg) \
        (msg->u.trxmMsg.u.errorReport.optionalBitMap = 0x00)

#define SET_TM_TRXM_ER_MESSAGE_IDENTIFIER(msg) \
        (msg->u.trxmMsg.u.errorReport.optionalBitMap |= 0x01)

#define SET_TM_TRXM_ER_CHANNEL_NUMBER(msg) \
        (msg->u.trxmMsg.u.errorReport.optionalBitMap |= 0x02)

#define SET_TM_TRXM_ER_LINK_IDENTIFIER(msg) \
        (msg->u.trxmMsg.u.errorReport.optionalBitMap |= 0x04)

#define SET_TM_TRXM_ER_ERRONEOUS_MSG(msg) \
        (msg->u.trxmMsg.u.errorReport.optionalBitMap |= 0x08)

/* NETWORK MANAGEMENT MESSAGES */

/* Activate SW */
#define CLEAR_NM_SWDM_AS_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.swdmMsg.u.actSw.optionalBitMap = 0x00)

#define SET_NM_SWDM_AS_SW_DESCRIPTION(msg) \
        (msg->u.formMsg.u.swdmMsg.u.actSw.optionalBitMap |= 0x01)

/* Connect Terrestrial Traffic */
#define CLEAR_NM_AM_CTT_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.abisMsg.u.connTraf.optionalBitMap = 0x00)

#define SET_NM_AM_CTT_RADIO_SUB_CHANNEL(msg) \
        (msg->u.formMsg.u.abisMsg.u.connTraf.optionalBitMap |= 0x01)

/* Disconnect Terrestrial Traffic */
#define CLEAR_NM_AM_DTT_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.abisMsg.u.disconTraf.optionalBitMap = 0x00)
                                                                                                                                              
#define SET_NM_AM_DTT_RADIO_SUB_CHANNEL(msg) \
        (msg->u.formMsg.u.abisMsg.u.disconTraf.optionalBitMap |= 0x01)

/* Set BTS Attributes in Air Interface Management */
#define CLEAR_NM_AIM_SBA_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap = 0x00)

#define SET_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x01)

#define SET_NM_AIM_SBA_INTAVE_PARAMETER(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x02)

#define SET_NM_AIM_SBA_CONN_FAILURE_CRITERION(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x04)

#define SET_NM_AIM_SBA_T200(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x08)

#define SET_NM_AIM_SBA_MAX_TIMING_ADVANCE(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x10)

#define SET_NM_AIM_SBA_OVERLOAD_PERIOD(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x20)

#define SET_NM_AIM_SBA_CCCH_LOAD_THRESHOLD(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x40)

#define SET_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x80)

#define SET_NM_AIM_SBA_RACH_BUSY_THRESHOLD(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x0100)

#define SET_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x0200)

#define SET_NM_AIM_SBA_BTS_AIR_TIMER(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x0400)

#define SET_NM_AIM_SBA_NY1(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x0800)

#define SET_NM_AIM_SBA_BCCH_ARFCN(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x1000)

#define SET_NM_AIM_SBA_BSIC(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x2000)

#define SET_NM_AIM_SBA_STARTING_TIME(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x4000)

#define SET_NM_AIM_SBA_PAGING_AG_PARAMS(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap |= 0x8000)
                                                                                
#define SET_NM_AIM_SBA_SYST_INFO_LIST(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optBitMap |= 0x01)
                                                                                
#define SET_NM_AIM_SBA_FN_OFFSET(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optBitMap |= 0x02) 

#define SET_NM_AIM_SBA_RF_MAX_POWER_REDUCTION(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optBitMap |= 0x04)
 
/* Set Radio Carrier Attributes */
#define CLEAR_NM_AIM_SRCA_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.airMsg.u.radioAttr.optionalBitMap = 0x00)
                                                                                                                                              
#define SET_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION(msg) \
        (msg->u.formMsg.u.airMsg.u.radioAttr.optionalBitMap |= 0x01)

#define SET_NM_AIM_SRCA_ARFCN_LIST(msg) \
        (msg->u.formMsg.u.airMsg.u.radioAttr.optionalBitMap |= 0x02)

/* Set Channel Attributes */
#define CLEAR_NM_AIM_SCA_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap = 0x00)

#define SET_NM_AIM_SCA_CHANNEL_COMBINATION(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap |= 0x01)

#define SET_NM_AIM_SCA_HSN(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap |= 0x02)

#define SET_NM_AIM_SCA_MAIO(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap |= 0x04)

#define SET_NM_AIM_SCA_ARFCN_LIST(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap |= 0x08)

#define SET_NM_AIM_SCA_STARTING_TIME(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap |= 0x10)

#define SET_NM_AIM_SCA_TSC(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap |= 0x20)

#define SET_NM_AIM_SCA_RF_MAX_POWER_REDUCTION(msg) \
        (msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap |= 0x40)

/* Perform Test */
#define CLEAR_NM_TM_PT_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.testMsg.u.perfTest.optionalBitMap = 0x00) 

#define SET_NM_TM_PT_TEST_DURATION(msg) \
        (msg->u.formMsg.u.testMsg.u.perfTest.optionalBitMap |= 0x01) 

#define SET_NM_TM_PT_PHYSICAL_CONFIGURATION(msg) \
        (msg->u.formMsg.u.testMsg.u.perfTest.optionalBitMap |= 0x02)

/* State Changed Event Report */
#define CLEAR_NM_SM_SCER_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap = 0x00)

#define SET_NM_SM_SCER_OPERATIONAL_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap |= 0x01)

#define SET_NM_SM_SCER_AVAILABILITY_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap |= 0x02)

#define SET_NM_SM_SCER_MAN_DEP_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap |= 0x04)

#define SET_NM_SM_SCER_SITE_INPUTS(msg) \
        (msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap |= 0x08)


/* Failure Event Report */
#define CLEAR_NM_SM_FER_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap = 0x00)

#define SET_NM_SM_FER_SPECIFIC_PROBLEMS(msg) \
        (msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap |= 0x01)

#define SET_NM_SM_FER_HW_DESCRIPTION(msg) \
        (msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap |= 0x02)

#define SET_NM_SM_FER_SW_DESCRIPTION(msg) \
        (msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap |= 0x04)

#define SET_NM_SM_FER_ADDITIONAL_TEXT(msg) \
        (msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap |= 0x08)

#define SET_NM_SM_FER_ADDITIONAL_INFO(msg) \
        (msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap |= 0x10)

#define SET_NM_SM_FER_OUTSTANDING_ALARM_SEQ(msg) \
        (msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap |= 0x20)

/* Stop Sending Event Reports */
#define CLEAR_NM_SM_SSER_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap = 0x00)

#define SET_NM_SM_SSER_OPERATIONAL_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap |= 0x01)

#define SET_NM_SM_SSER_AVAILABILTY_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap |= 0x02)

#define SET_NM_SM_SSER_MFD_DEP_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap |= 0x04)

#define SET_NM_SM_SSER_PROBABLE_CAUSE(msg) \
        (msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap |= 0x08)

#define SET_NM_SM_SSER_SPECIFIC_PROBLEMS(msg) \
        (msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap |= 0x10)

/* Restart Sending Event Reports */
#define CLEAR_NM_SM_RSER_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap = 0x00)
                                                                                                                                              
#define SET_NM_SM_RSER_OPERATIONAL_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap |= 0x01)
                                                                                                                                              
#define SET_NM_SM_RSER_AVAILABILTY_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap |= 0x02)
                                                                                                                                              
#define SET_NM_SM_RSER_MFD_DEP_STATE(msg) \
        (msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap |= 0x04)
                                                                                                                                              
#define SET_NM_SM_RSER_PROBABLE_CAUSE(msg) \
        (msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap |= 0x08)
                                                                                                                                              
#define SET_NM_SM_RSER_SPECIFIC_PROBLEMS(msg) \
        (msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap |= 0x10)

/* Reinitialise */
#define CLEAR_NM_EM_REIN_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.equipMsg.u.reInit.optionalBitMap = 0x00)

#define SET_NM_EM_REIN_HW_DESCRIPTION(msg) \
        (msg->u.formMsg.u.equipMsg.u.reInit.optionalBitMap |= 0x01)

/* Set Alarm Threshold */
#define CLEAR_NM_MM_SAT_OPTIONAL_BIT_MAP(msg) \
        (msg->u.formMsg.u.miscMsg.u.alarmThresh.optionalBitMap = 0x00)

#define SET_NM_MM_SAT_POWER_OUTPUT_THRESHOLD(msg) \
        (msg->u.formMsg.u.miscMsg.u.alarmThresh.optionalBitMap |= 0x01)

#define SET_NM_MM_SAT_VSWR_THRESHOLDS(msg) \
        (msg->u.formMsg.u.miscMsg.u.alarmThresh.optionalBitMap |= 0x02)

#define SET_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS(msg) \
        (msg->u.formMsg.u.miscMsg.u.alarmThresh.optionalBitMap |= 0x04)

/* TRX Hello   */
#define SET_NM_SM_TRX_HELLO_SW_DESC(msg) \
        (msg->u.formMsg.u.stateMsg.u.trxHello.optBitMap |= 0x01)
                                                                                
#define SET_NM_SM_TRX_HELLO_HW_DESC(msg) \
        (msg->u.formMsg.u.stateMsg.u.trxHello.optBitMap |= 0x02)

/*  GET MACROS
 *  ---------
 *  macro's used to get optionalBitMaps from Messages
 *  The usage of macro can be done in two ways
 *  1. if msg is pointer, then it can be passed directly.
 *  2. if msg is static variable, then it can be passed as ((&msg))
 */
                                                                                                                                              
/* TRAFFIC MANAGEMENT MESSAGES */

/* Establish Indication in Radio Link Layer Management */
#define IS_PRESENT_TM_RLLM_EI_L3_INFO(msg) \
        (msg->u.rllmMsg.u.estInd.optionalBitMap & 0x01)
                                                                                                                                              
/* Dedicated Channel Management */

/*  Channel Activation Message */ 
#define IS_PRESENT_TM_DCM_CA_CHANNEL_IDENTIFIER(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x01) >> 0)

#define IS_PRESENT_TM_DCM_CA_ENCRYPT_INFO(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x02) >> 1)

#define IS_PRESENT_TM_DCM_CA_BS_POWER(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x04) >> 2)

#define IS_PRESENT_TM_DCM_CA_MS_POWER(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x08) >> 3)

#define IS_PRESENT_TM_DCM_CA_BS_POWER_PARAMS(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x10) >> 4)

#define IS_PRESENT_TM_DCM_CA_MS_POWER_PARAMS(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x20) >> 5)

#define IS_PRESENT_TM_DCM_CA_PHYSICAL_CONTEXT(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x40) >> 6)

#define IS_PRESENT_TM_DCM_CA_SAACH_INFO(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x80) >> 7)

#define IS_PRESENT_TM_DCM_CA_UIC(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x0100) >> 8)

#define IS_PRESENT_TM_DCM_CA_MAIN_CHANNEL_REF(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x0200) >> 9)

#define IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONFIG(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x0400) >> 10)

#define IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONTROL(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x0800) >> 11)

#define IS_PRESENT_TM_DCM_CA_SUPPORTED_CODEC_TYPES(msg) \
         ((msg->u.dcmMsg.u.chanActiv.optionalBitMap & 0x1000) >> 12)

/* Handover Detection */
#define IS_PRESENT_TM_DCM_HD_ACCESS_DELAY(msg) \
        (msg->u.dcmMsg.u.handoDet.optionalBitMap & 0x01)
                                                                                                                                              
/* Measurement Result */
#define IS_PRESENT_TM_DCM_MR_L1_INFO(msg) \
        ((msg->u.dcmMsg.u.measRes.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_TM_DCM_MR_L3_INFO(msg) \
        ((msg->u.dcmMsg.u.measRes.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_TM_DCM_MR_MS_TIMING_OFFSET(msg) \
        ((msg->u.dcmMsg.u.measRes.optionalBitMap & 0x04) >> 2)

/* Mode Modify message in Dedicated Channel management */ 
#define IS_PRESENT_TM_DCM_MM_ENCRYPT_CHANNEL(msg)  \
        ((msg->u.dcmMsg.u.modeModifyReq.optionalBitMap & 0x01) >> 0)

#define IS_PRESENT_TM_DCM_MM_MAIN_CHANNEL_REF(msg) \
        ((msg->u.dcmMsg.u.modeModifyReq.optionalBitMap & 0x02) >> 1)

#define IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONFIG(msg) \
        ((msg->u.dcmMsg.u.modeModifyReq.optionalBitMap & 0x04) >> 2)

#define IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONTROL(msg) \
        ((msg->u.dcmMsg.u.modeModifyReq.optionalBitMap & 0x08) >> 3)

#define IS_PRESENT_TM_DCM_MM_SUPPORTED_CODEC_TYPES(msg) \
        ((msg->u.dcmMsg.u.modeModifyReq.optionalBitMap & 0x10) >> 4)

/* Physical Context Confirm */
#define IS_PRESENT_TM_DCM_PCC_PHYSICAL_CONTEXT(msg) \
        (msg->u.dcmMsg.u.phyContextConf.optionalBitMap & 0x01)
                                                                                                                                              
/* MS Power Control */
#define IS_PRESENT_TM_DCM_MPC_MS_POWER_PARAMS(msg) \
        (msg->u.dcmMsg.u.mspowerControl.optionalBitMap & 0x01)
                                                                                                                                              
/* BS Power Control */
#define IS_PRESENT_TM_DCM_BPC_BS_POWER_PARAMS(msg) \
        (msg->u.dcmMsg.u.bspowerControl.optionalBitMap & 0x01)
                                                                                                                                              
/* SAACH Info Modify */
#define IS_PRESENT_TM_DCM_SIM_L3_INFO(msg) \
        ((msg->u.dcmMsg.u.sacchInfoMod.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_TM_DCM_SIM_STARTING_TIME(msg) \
        ((msg->u.dcmMsg.u.sacchInfoMod.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
/* Talker Detection */
#define IS_PRESENT_TM_DCM_TD_ACCESS_DELAY(msg) \
        (msg->u.dcmMsg.u.talkerDet.optionalBitMap & 0x01)

/* Listener Detection */
#define IS_PRESENT_TM_DCM_LD_ACCESS_DELAY(msg) \
        (msg->u.dcmMsg.u.listenerDet.optionalBitMap & 0x01)
                                                                                                                                              
/* MultiRate Codec Modification Request */
#define IS_PRESENT_TM_DCM_MCMR_MULTI_RATE_CONFIG(msg) \
        (msg->u.dcmMsg.u.mrCodecModReq.optionalBitMap & 0x01)
                                                                                                                                              
/* MultiRate Codec Modification Acknowledge */
#define IS_PRESENT_TM_DCM_MCMA_MULTI_RATE_CONFIG(msg) \
        (msg->u.dcmMsg.u.mrCodecModAck.optionalBitMap & 0x01)
                                                                                                                                              
/* TFO Modification Request */
#define IS_PRESENT_TM_DCM_TMR_SUPPORTED_CODEC_TYPE(msg) \
        (msg->u.dcmMsg.u.tfoModReq.optionalBitMap & 0x01)
                                                                                                                                              
/* Common Channel Management */
                                                                                                                                              
/* BCCH Information */
#define IS_PRESENT_TM_CCM_BI_FULL_BCCH_INFO(msg) \
        ((msg->u.ccmMsg.u.bcchInfo.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_TM_CCM_BI_STARTING_TIME(msg) \
        ((msg->u.ccmMsg.u.bcchInfo.optionalBitMap & 0x02) >> 1)

/* Channel Required */
#define IS_PRESENT_TM_CCM_CR_PHYSICAL_CONTEXT(msg) \
        (msg->u.ccmMsg.u.chanRqd.optionalBitMap & 0x01)
                                                                                                                                              
/* Paging Command */
#define IS_PRESENT_TM_CCM_PC_CHANNEL_NEEDED(msg) \
        ((msg->u.ccmMsg.u.pagingCmd.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_TM_CCM_PC_EMLPP_PRIORITY(msg) \
        ((msg->u.ccmMsg.u.pagingCmd.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
/* SMS Broadcast Request */
#define IS_PRESENT_TM_CCM_SBR_SMSCB_CHANNEL_IND(msg) \
        (msg->u.ccmMsg.u.smsBcReq.optionalBitMap & 0x01)
                                                                                                                                              
/* SMS Broadcast Command */
#define IS_PRESENT_TM_CCM_SBC_SMSCB_CHANNEL_IND(msg) \
        (msg->u.ccmMsg.u.smsBcCmd.optionalBitMap & 0x01)
                                                                                                                                              
/* CBCH Load Indication */
#define IS_PRESENT_TM_CCM_CLI_SMSCB_CHANNEL_IND(msg) \
        (msg->u.ccmMsg.u.cbchLoadInd.optionalBitMap & 0x01)

/* Notification Command */
#define IS_PRESENT_TM_CCM_NC_GROUP_CALL_REFERENCE(msg) \
        ((msg->u.ccmMsg.u.notCmd.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_TM_CCM_NC_CHANNEL_DESCRIPTION(msg) \
        ((msg->u.ccmMsg.u.notCmd.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_TM_CCM_NC_NCH_DRX_INFO(msg) \
        ((msg->u.ccmMsg.u.notCmd.optionalBitMap & 0x04) >> 2)
                                                                                                                                              
/* TRX Management */
                                                                                                                                              
/* SACCH Filling */
#define IS_PRESENT_TM_TRXM_SF_L3_INFO(msg) \
        ((msg->u.trxmMsg.u.sacchFill.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_TM_TRXM_SF_STARTING_TIME(msg) \
        ((msg->u.trxmMsg.u.sacchFill.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
/* Error Report */
#define IS_PRESENT_TM_TRXM_ER_MESSAGE_IDENTIFIER(msg) \
        ((msg->u.trxmMsg.u.errorReport.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_TM_TRXM_ER_CHANNEL_NUMBER(msg) \
        ((msg->u.trxmMsg.u.errorReport.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_TM_TRXM_ER_LINK_IDENTIFIER(msg) \
        ((msg->u.trxmMsg.u.errorReport.optionalBitMap & 0x04) >> 2)
                                                                                                                                              
#define IS_PRESENT_TM_TRXM_ER_ERRONEOUS_MSG(msg) \
        ((msg->u.trxmMsg.u.errorReport.optionalBitMap & 0x08) >> 3)

/* NETWORK MANAGEMENT MESSAGES */

/* Activate SW */
#define IS_PRESENT_NM_SWDM_AS_SW_DESCRIPTION(msg) \
        (msg->u.formMsg.u.swdmMsg.u.actSw.optionalBitMap & 0x01)

/* Connect Terrestrial Traffic */
#define IS_PRESENT_NM_AM_CTT_RADIO_SUB_CHANNEL(msg) \
        (msg->u.formMsg.u.abisMsg.u.connTraf.optionalBitMap & 0x01)
                                                                                                                                              
/* Disconnect Terrestrial Traffic */
#define IS_PRESENT_NM_AM_DTT_RADIO_SUB_CHANNEL(msg) \
        (msg->u.formMsg.u.abisMsg.u.disconTraf.optionalBitMap & 0x01)

/* Set BTS Attributes in Air Interface Management */
#define IS_PRESENT_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x01)  >> 0)

#define IS_PRESENT_NM_AIM_SBA_INTAVE_PARAMETER(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x02)  >> 1)

#define IS_PRESENT_NM_AIM_SBA_CONN_FAILURE_CRITERION(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x04)  >> 2)

#define IS_PRESENT_NM_AIM_SBA_T200(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x08)  >> 3)

#define IS_PRESENT_NM_AIM_SBA_MAX_TIMING_ADVANCE(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x10)  >> 4)

#define IS_PRESENT_NM_AIM_SBA_OVERLOAD_PERIOD(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x20)  >> 5)

#define IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_THRESHOLD(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x40)  >> 6)

#define IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x80)  >> 7)

#define IS_PRESENT_NM_AIM_SBA_RACH_BUSY_THRESHOLD(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x0100) >> 8)

#define IS_PRESENT_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x0200) >> 9)

#define IS_PRESENT_NM_AIM_SBA_BTS_AIR_TIMER(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x0400) >> 10)

#define IS_PRESENT_NM_AIM_SBA_NY1(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x0800) >> 11)

#define IS_PRESENT_NM_AIM_SBA_BCCH_ARFCN(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x1000) >> 12)

#define IS_PRESENT_NM_AIM_SBA_BSIC(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x2000) >> 13)

#define IS_PRESENT_NM_AIM_SBA_STARTING_TIME(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x4000) >> 14)

#define IS_PRESENT_NM_AIM_SBA_PAGING_AG_PARAMS(msg) \
        ((msg->u.formMsg.u.airMsg.u.btsAttr.optionalBitMap & 0x8000) >> 15)
                                                                                
#define IS_PRESENT_NM_AIM_SBA_SYST_INFO_LIST(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optBitMap & 0x01)
                                                                                
#define IS_PRESENT_NM_AIM_SBA_FN_OFFSET(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optBitMap & 0x02)

#define IS_PRESENT_NM_AIM_SBA_RF_MAX_POWER_REDUCTION(msg) \
        (msg->u.formMsg.u.airMsg.u.btsAttr.optBitMap & 0x04)

/* Set Radio Carrier Attributes */
#define IS_PRESENT_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION(msg) \
        (msg->u.formMsg.u.airMsg.u.radioAttr.optionalBitMap & 0x01)
                                                                                                                                              
#define IS_PRESENT_NM_AIM_SRCA_ARFCN_LIST(msg) \
        ((msg->u.formMsg.u.airMsg.u.radioAttr.optionalBitMap & 0x02) >> 1)

/* Set Channel Attributes */
#define IS_PRESENT_NM_AIM_SCA_CHANNEL_COMBINATION(msg) \
        ((msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_NM_AIM_SCA_HSN(msg) \
        ((msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_NM_AIM_SCA_MAIO(msg) \
        ((msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap & 0x04) >> 2)
                                                                                                                                              
#define IS_PRESENT_NM_AIM_SCA_ARFCN_LIST(msg) \
        ((msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap & 0x08) >> 3)
                                                                                                                                              
#define IS_PRESENT_NM_AIM_SCA_STARTING_TIME(msg) \
        ((msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap & 0x10) >> 4)
                                                                                                                                              
#define IS_PRESENT_NM_AIM_SCA_TSC(msg) \
        ((msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap & 0x20) >> 5)

#define IS_PRESENT_NM_AIM_SCA_RF_MAX_POWER_REDUCTION(msg) \
        ((msg->u.formMsg.u.airMsg.u.chanlAttr.optionalBitMap & 0x40) >> 6)

/* Perform Test */
#define IS_PRESENT_NM_TM_PT_TEST_DURATION(msg) \
        (msg->u.formMsg.u.testMsg.u.perfTest.optionalBitMap & 0x01) 
                                                                                                                                              
#define IS_PRESENT_NM_TM_PT_PHYSICAL_CONFIGURATION(msg) \
        ((msg->u.formMsg.u.testMsg.u.perfTest.optionalBitMap & 0x02) >> 1)

/* State Changed Event Report */
#define IS_PRESENT_NM_SM_SCER_OPERATIONAL_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_NM_SM_SCER_AVAILABILITY_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_NM_SM_SCER_MAN_DEP_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap & 0x04) >> 2)
                                                                                                                                              
#define IS_PRESENT_NM_SM_SCER_SITE_INPUTS(msg) \
        ((msg->u.formMsg.u.stateMsg.u.changeEv.optionalBitMap & 0x08) >> 3)

/* Failure Event Report */
#define IS_PRESENT_NM_SM_FER_SPECIFIC_PROBLEMS(msg) \
        ((msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_NM_SM_FER_HW_DESCRIPTION(msg) \
        ((msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_NM_SM_FER_SW_DESCRIPTION(msg) \
        ((msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap & 0x04) >> 2)
                                                                                                                                              
#define IS_PRESENT_NM_SM_FER_ADDITIONAL_TEXT(msg) \
        ((msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap & 0x08) >> 3)
                                                                                                                                              
#define IS_PRESENT_NM_SM_FER_ADDITIONAL_INFO(msg) \
        ((msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap & 0x10) >> 4)
                                                                                                                                              
#define IS_PRESENT_NM_SM_FER_OUTSTANDING_ALARM_SEQ(msg) \
        ((msg->u.formMsg.u.stateMsg.u.failEv.optionalBitMap & 0x20) >> 5)

/* Stop Sending Event Reports */
#define IS_PRESENT_NM_SM_SSER_OPERATIONAL_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_NM_SM_SSER_AVAILABILTY_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_NM_SM_SSER_MFD_DEP_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap & 0x04) >> 2)
                                                                                                                                              
#define IS_PRESENT_NM_SM_SSER_PROBABLE_CAUSE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap & 0x08) >> 3)
                                                                                                                                              
#define IS_PRESENT_NM_SM_SSER_SPECIFIC_PROBLEMS(msg) \
        ((msg->u.formMsg.u.stateMsg.u.stopEv.optionalBitMap & 0x10) >> 4)
                                                                                                                                              
/* Restart Sending Event Reports */
#define IS_PRESENT_NM_SM_RSER_OPERATIONAL_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_NM_SM_RSER_AVAILABILTY_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_NM_SM_RSER_MFD_DEP_STATE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap & 0x04) >> 2)
                                                                                                                                              
#define IS_PRESENT_NM_SM_RSER_PROBABLE_CAUSE(msg) \
        ((msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap & 0x08) >> 3)
                                                                                                                                              
#define IS_PRESENT_NM_SM_RSER_SPECIFIC_PROBLEMS(msg) \
        ((msg->u.formMsg.u.stateMsg.u.restartEv.optionalBitMap & 0x10) >> 4)

/* Reinitialise */
#define IS_PRESENT_NM_EM_REIN_HW_DESCRIPTION(msg) \
        (msg->u.formMsg.u.equipMsg.u.reInit.optionalBitMap & 0x01)
                                                                                                                                              
/* Set Alarm Threshold */
#define IS_PRESENT_NM_MM_SAT_POWER_OUTPUT_THRESHOLD(msg) \
        ((msg->u.formMsg.u.miscMsg.u.alarmThresh.optionalBitMap & 0x01) >> 0)
                                                                                                                                              
#define IS_PRESENT_NM_MM_SAT_VSWR_THRESHOLDS(msg) \
        ((msg->u.formMsg.u.miscMsg.u.alarmThresh.optionalBitMap & 0x02) >> 1)
                                                                                                                                              
#define IS_PRESENT_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS(msg) \
        ((msg->u.formMsg.u.miscMsg.u.alarmThresh.optionalBitMap & 0x04) >> 2)

/* TRX Hello   */
#define IS_PRESENT_NM_SM_TRX_HELLO_SW_DESC(msg) \
        ((msg->u.formMsg.u.stateMsg.u.trxHello.optBitMap & 0x01) >> 0)
                                                                                
#define IS_PRESENT_NM_SM_TRX_HELLO_HW_DESC(msg) \
        ((msg->u.formMsg.u.stateMsg.u.trxHello.optBitMap & 0x02) >> 1)


/* Common Macro for all below mentioned errors.
 * change starting error code in this macro only if required
 */
#define ABIS_START_ERROR_CODE   -1

/* Memory Errors 
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0130, ID :: D0190,
 *                        ID :: D0070
 */
#define ABIS_NOMEM              ABIS_START_ERROR_CODE

/* Length Error 
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0130, ID :: D0190,
 *                        ID :: D0080
 */
#define ABIS_INVALID_LEN        (ABIS_START_ERROR_CODE - 5)
#define CONTENT_LENGTH_ERROR    (ABIS_START_ERROR_CODE - 6)

/*
 * 
 * Traffic Management Error Codes for indivisual parameters 
 *
 */

/* Boundary Check Error on Data Field Size 
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0130, ID :: D0090
 */
#define TM_RLLM_GEN_MSG_T_BIT_ERROR       (ABIS_START_ERROR_CODE - 10)
#define TM_RLLM_GEN_MSG_GROUP_ERROR       (ABIS_START_ERROR_CODE - 11)
#define TM_RLLM_CN_TIME_SLOT_ERROR        (ABIS_START_ERROR_CODE - 12)
#define TM_RLLM_CN_CHANNEL_BITS_ERROR     (ABIS_START_ERROR_CODE - 13)
#define TM_RLLM_LI_SAPI_ERROR             (ABIS_START_ERROR_CODE - 14)
#define TM_RLLM_LI_PRIORITY_ERROR         (ABIS_START_ERROR_CODE - 15)
#define TM_RLLM_LI_NA_ERROR               (ABIS_START_ERROR_CODE - 16)
#define TM_RLLM_LI_CHANNEL_BITS_ERROR     (ABIS_START_ERROR_CODE - 17)
#define TM_RLLM_RM_MODE_BIT_ERROR         (ABIS_START_ERROR_CODE - 18)

#define TM_CCM_PC_CHANNEL_ERROR           (ABIS_START_ERROR_CODE - 30)
#define TM_CCM_PC_CALL_PRIORITY_ERROR     (ABIS_START_ERROR_CODE - 31)
#define TM_CCM_SBR_CHANNEL_IND_ERROR      (ABIS_START_ERROR_CODE - 32)
#define TM_CCM_SMS_BC_LAST_BLOCK_ERROR    (ABIS_START_ERROR_CODE - 33)
#define TM_CCM_SMS_BC_BROADCAST_ERROR     (ABIS_START_ERROR_CODE - 34)
#define TM_CCM_SMS_BC_COMMOND_ERROR       (ABIS_START_ERROR_CODE - 35)
#define TM_CCM_SBC_CHANNEL_IND_ERROR      (ABIS_START_ERROR_CODE - 36)
#define TM_CCM_CBCH_SLOT_COUNT_ERROR      (ABIS_START_ERROR_CODE - 37)
#define TM_CCM_CBCH_LOAD_TYPE_ERROR       (ABIS_START_ERROR_CODE - 38)
#define TM_CCM_CBCH_CHANNEL_ERROR         (ABIS_START_ERROR_CODE - 39)
#define TM_CCM_NC_RADIO_INTERFACE_ERROR   (ABIS_START_ERROR_CODE - 40)
#define TM_CCM_NC_EMLPP_ERROR             (ABIS_START_ERROR_CODE - 41)
#define TM_CCM_NC_NLN_ERROR               (ABIS_START_ERROR_CODE - 42) 
#define TM_CCM_SBR_SMSCB_LEN_ERROR        (ABIS_START_ERROR_CODE - 43) 
#define TM_CCM_SBC_SMSCB_MSG_LEN_ERROR    (ABIS_START_ERROR_CODE - 44) 
#define TM_CCM_PC_MSID_LEN_ERROR          (ABIS_START_ERROR_CODE - 45) 
#define TM_CCM_NC_CALL_REF_LEN_ERROR      (ABIS_START_ERROR_CODE - 46) 

#define TM_TRXM_RRI_INTER_LEVEL_ERROR     (ABIS_START_ERROR_CODE - 60)
#define TM_TRXM_RRI_TIME_SLOT_ERROR       (ABIS_START_ERROR_CODE - 61)
#define TM_TRXM_RRI_CHANNEL_BITS_ERROR    (ABIS_START_ERROR_CODE - 62)
#define TM_TRXM_CN_TIME_SLOT_ERROR        (ABIS_START_ERROR_CODE - 63)
#define TM_TRXM_CN_CHANNEL_BITS_ERROR     (ABIS_START_ERROR_CODE - 64)
#define TM_TRXM_LI_SAPI_ERROR             (ABIS_START_ERROR_CODE - 65)
#define TM_TRXM_LI_PRIORITY_ERROR         (ABIS_START_ERROR_CODE - 66)
#define TM_TRXM_LI_NA_ERROR               (ABIS_START_ERROR_CODE - 67)
#define TM_TRXM_LI_CHANNEL_BITS_ERROR     (ABIS_START_ERROR_CODE - 68)
#define TM_TRXM_ER_ERRONS_LEN_ERROR       (ABIS_START_ERROR_CODE - 69)

#define TM_DCM_CA_ACTIVE_TYPE_ERROR       (ABIS_START_ERROR_CODE - 80)
#define TM_DCM_CA_PROCEDURE_ERROR         (ABIS_START_ERROR_CODE - 81)
#define TM_DCM_CM_DTXD_ERROR              (ABIS_START_ERROR_CODE - 82)
#define TM_DCM_CM_DTXU_ERROR              (ABIS_START_ERROR_CODE - 83)
#define TM_DCM_CM_INDICATOR_ERROR         (ABIS_START_ERROR_CODE - 84)
#define TM_DCM_CM_RATE_ERROR              (ABIS_START_ERROR_CODE - 85)
#define TM_DCM_CM_SERVICE_BIT_ERROR       (ABIS_START_ERROR_CODE - 86)
#define TM_DCM_LI_SAPI_ERROR              (ABIS_START_ERROR_CODE - 87)
#define TM_DCM_LI_PRIORITY_ERROR          (ABIS_START_ERROR_CODE - 88)
#define TM_DCM_LI_NA_ERROR                (ABIS_START_ERROR_CODE - 89)
#define TM_DCM_LI_CHANNEL_BITS_ERROR      (ABIS_START_ERROR_CODE - 90) 
#define TM_DCM_UM_RELEV_FULL_UP_ERROR     (ABIS_START_ERROR_CODE - 91)
#define TM_DCM_UM_DTXD_ERROR              (ABIS_START_ERROR_CODE - 92)
#define TM_DCM_UM_RFU_ERROR               (ABIS_START_ERROR_CODE - 93)
#define TM_DCM_UM_RELEV_SUB_UP_ERROR      (ABIS_START_ERROR_CODE - 94)
#define TM_DCM_UM_RXQUAL_SUB_UP           (ABIS_START_ERROR_CODE - 95)
#define TM_DCM_UM_RXQUAL_FULL_UP          (ABIS_START_ERROR_CODE - 96)
#define TM_DCM_BP_POWER_LEVEL_ERROR       (ABIS_START_ERROR_CODE - 97)
#define TM_DCM_BP_FPC_ERROR               (ABIS_START_ERROR_CODE - 98)
#define TM_DCM_L1_FPC_ERROR               (ABIS_START_ERROR_CODE - 99)
#define TM_DCM_L1_POWER_LEVEL_ERROR       (ABIS_START_ERROR_CODE - 100)
#define TM_DCM_MP_POWER_LEVEL_ERROR       (ABIS_START_ERROR_CODE - 101)
#define TM_DCM_MP_FPC_ERROR               (ABIS_START_ERROR_CODE - 102)
#define TM_DCM_PP_PROCEDURE_ERROR         (ABIS_START_ERROR_CODE - 103)
#define TM_DCM_SCT_CODEC_LIST_ERROR       (ABIS_START_ERROR_CODE - 104)
#define TM_DCM_SCT_MACS_ERROR             (ABIS_START_ERROR_CODE - 105)
#define TM_DCM_SCT_TFO_VER_ERROR          (ABIS_START_ERROR_CODE - 106)
#define TM_DCM_RTD_DELAY_IND_ERROR        (ABIS_START_ERROR_CODE - 107)
#define TM_DCM_RTD_ERROR                  (ABIS_START_ERROR_CODE - 108)
#define TM_DCM_MC_TFO_ERROR               (ABIS_START_ERROR_CODE - 109)
#define TM_DCM_MC_RAE_ERROR               (ABIS_START_ERROR_CODE - 110)
#define TM_DCM_MC_PRE_ERROR               (ABIS_START_ERROR_CODE - 111)
#define TM_DCM_TR_TFO_STATUS_ERROR        (ABIS_START_ERROR_CODE - 112)
#define TM_DCM_CC_ICM_ERROR               (ABIS_START_ERROR_CODE - 113)
#define TM_DCM_CA_MAIN_CHANL_TN_ERROR     (ABIS_START_ERROR_CODE - 114)
#define TM_CCM_DI_FULL_IMMD_LEN_ERROR     (ABIS_START_ERROR_CODE - 115)

/* Boundary Check Error on Data Value
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0130, ID :: D0100
 */
#define TM_CCM_NC_LEN_ERROR               (ABIS_START_ERROR_CODE - 130)
#define TM_CCM_RL_LEN_ERROR               (ABIS_START_ERROR_CODE - 131)

#define TM_TRXM_RRI_LENGTH_ERROR          (ABIS_START_ERROR_CODE - 140)
#define TM_TRXM_RI_LENGTH_ERROR           (ABIS_START_ERROR_CODE - 141)

#define TM_DCM_UM_LENGTH_ERROR            (ABIS_START_ERROR_CODE - 160)
#define TM_DCM_CC_LENGTH_ERROR            (ABIS_START_ERROR_CODE - 161)
#define TM_DCM_EI_LENGTH_ERROR            (ABIS_START_ERROR_CODE - 162)
#define TM_DCM_CA_CHANL_ID_LEN_ERROR      (ABIS_START_ERROR_CODE - 163)
#define TM_DCM_CA_SACCH_LEN_ERROR         (ABIS_START_ERROR_CODE - 164)
#define TM_DCM_CA_SUP_CODEC_LEN_ERROR     (ABIS_START_ERROR_CODE - 165)
#define TM_DCM_CA_CODEC_CONFIG_LEN_ERROR  (ABIS_START_ERROR_CODE - 166)
#define TM_DCM_BI_BCCH_INFO_LEN_ERROR     (ABIS_START_ERROR_CODE - 167)

/* Conditional Parameter Errors
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0130, ID :: D0110
 */

/* General Errors 
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0130, ID :: D0120
 */
#define TM_INFO_ELEMENT_ID_ERROR          (ABIS_START_ERROR_CODE - 180)
#define TM_TRANSPARENT_BIT_ERROR          (ABIS_START_ERROR_CODE - 181)
#define TM_NON_TRANSPARENT_BIT_ERROR      (ABIS_START_ERROR_CODE - 182)

/*
 * 
 * Network Management Error Codes for indivisual parameters 
 *
 */

/* Boundary Check Errors on Data Field Size 
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0190, ID :: D0090
 */
#define NM_FOM_SM_INPUT_ERROR              (ABIS_START_ERROR_CODE - 200)
#define NM_FOM_SM_STATE_ERROR              (ABIS_START_ERROR_CODE - 201)

/* Boundary Check Errors on Data Value
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0190, ID :: D0100
 */
#define NM_FOM_AC_INVALID_TIME_SLOT_ERROR  (ABIS_START_ERROR_CODE - 210)
#define NM_FOM_TEI_INVALID_ERROR           (ABIS_START_ERROR_CODE - 211)
#define NM_FOM_MBL_TIME_SLOT_ERROR         (ABIS_START_ERROR_CODE - 212)
#define NM_FOM_POT_FAULT_ERROR             (ABIS_START_ERROR_CODE - 213)
#define NM_FOM_POT_REDUCED_ERROR           (ABIS_START_ERROR_CODE - 214)
#define NM_FOM_POT_EXCESSIVE_ERROR         (ABIS_START_ERROR_CODE - 215)
#define NM_FOM_VT_FAULTY_ERROR             (ABIS_START_ERROR_CODE - 216)
#define NM_FOM_VT_NOT_ADJUSTED_ERROR       (ABIS_START_ERROR_CODE - 217)
#define NM_FOM_IP_INTAVE_PARAM_ERROR       (ABIS_START_ERROR_CODE - 218)
#define NM_FOM_CFC_LENGTH_ERROR            (ABIS_START_ERROR_CODE - 219)
#define NM_FOM_MTA_TIMING_ADV_ERROR        (ABIS_START_ERROR_CODE - 220)
#define NM_FOM_CLT_THRESHOLD_ERROR         (ABIS_START_ERROR_CODE - 221)
#define NM_FOM_BA_ARFCN_ERROR              (ABIS_START_ERROR_CODE - 222)
#define NM_FOM_BSIC_ERROR                  (ABIS_START_ERROR_CODE - 223)
#define NM_FOM_HSN_ERROR                   (ABIS_START_ERROR_CODE - 224)
#define NM_FOM_MAIO_ERROR                  (ABIS_START_ERROR_CODE - 225)
#define NM_FOM_TSC_ERROR                   (ABIS_START_ERROR_CODE - 226)
#define NM_FOM_AIM_ARFCN_ERROR             (ABIS_START_ERROR_CODE - 227)
#define NM_FOM_TM_DURATION_ERROR           (ABIS_START_ERROR_CODE - 228)

/* Conditional Parameter Errors 
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0190, ID :: D0110
 */
                                                                                                                                              
/* General Errors 
 * HISTORY:
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                  Description
 * -------------------------------------------------------------------------
 * mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2
 *                        ID :: D0190, ID :: D0120
 */
#define NM_INVLID_ATTRIBUTE_ID             (ABIS_START_ERROR_CODE - 250) 
#define NM_INVALID_MSG_TYPE                (ABIS_START_ERROR_CODE - 251)         
#define NM_FOM_OI_BTS_NUMBER_ERROR         (ABIS_START_ERROR_CODE - 252)
#define NM_FOM_OI_BASE_OR_RADIO_ERROR      (ABIS_START_ERROR_CODE - 253)
#define NM_FOM_OI_RADIO_TN_NUM_ERROR       (ABIS_START_ERROR_CODE - 254)
#define NM_FOM_WS_INVALID_SIZE             (ABIS_START_ERROR_CODE - 255)
#define NM_FOM_OS_INVALID_STATE_ERROR      (ABIS_START_ERROR_CODE - 256)

#endif
