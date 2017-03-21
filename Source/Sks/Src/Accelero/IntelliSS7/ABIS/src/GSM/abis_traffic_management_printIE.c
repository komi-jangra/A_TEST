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
 ****************************************************************************
 *  $Id: abis_traffic_management_printIE.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
 *
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
 *  Revision 1.1.2.1  2006/02/06 05:27:29  yranade
 *  After unit test for 2nd validation release (badri).
 *
 *****************************************************************************/

#include <abis_traffic_management.h>

ITS_INT (*Print_Traffic_Msg[MAX_TRAFFIC_FUNS_SIZE])
               (ABIS_TRAFFIC_MANAGEMENT_MSG *msg);

//extern "C"
void
Print_Abis_Traffic_Management_Msg(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_OCTET msgType = msg->genElemnts.msgType;

    (Print_Traffic_Msg[msgType])(msg);
}

static ITS_INT
Print_CommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    TM_MSG_DESCRIMINATOR *msgDesc = &msg->genElemnts.msgDesc;

    printf("msgTransp : %02x\n", msgDesc->trasparent) ;
    printf("msgGroup  : %02x\n", msgDesc->msgGruop) ;
    printf("msgType   : %02x\n", msg->genElemnts.msgType);

    return ITS_SUCCESS;
}

static ITS_INT
Print_CommonRllmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.rllmMsg.rllmGenElements.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.rllmMsg.rllmGenElements.linkId;

    ret = Print_CommonElements(msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("timeSlotNum : %02x\n", chanlNum->timeSlotNum);
    printf("chanlBits   : %02x\n", chanlNum->chanlBits);
    printf("SAPI        : %02x\n", linkId->SAPI);
    printf("priority    : %02x\n", linkId->priority);
    printf("chanlBits   : %02x\n", linkId->chanlBits);
    printf("NA          : %02x\n", linkId->NA);
 
    return ITS_SUCCESS;
}

static ITS_INT
Print_CommonDcmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.dcmMsg.dcmGenElements.chanlNum;

    ret = Print_CommonElements(msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("timeSlotNum : %02x\n", chanlNum->timeSlotNum);
    printf("chanlBits   : %02x\n", chanlNum->chanlBits);
    
    return ITS_SUCCESS;
}

static ITS_INT
Print_CommonCcmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum;

    ret = Print_CommonElements(msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("timeSlotNum : %02x\n", chanlNum->timeSlotNum);
    printf("chanlBits   : %02x\n", chanlNum->chanlBits);

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_PrintDataReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_L3_INFORMATION *l3Info = &msg->u.rllmMsg.u.dataReq.l3Info;

    /* display Data Request message */
    ret = Print_CommonRllmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                           

    printf("lengthInd   : %04x\n", l3Info->lengthInd);

    for (i = 0; i < l3Info->lengthInd; i++)
    {
        printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_PrintErrorInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;
    TM_RLLM_ERROR_IND *errorInd = &msg->u.rllmMsg.u.errorInd;

    /* display Error Indication message */
    ret = Print_CommonRllmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("RLM length   : %02x\n", errorInd->rlmLen);
    printf("RLM Clause   : %02x\n", errorInd->causeVal);

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_PrintEstaReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;

    /* display Establish Request message */
    ret = Print_CommonRllmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_PrintEstaInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_L3_INFORMATION *l3Info = &msg->u.rllmMsg.u.estInd.l3Info;  

    /* display Establish Indication message */
    ret = Print_CommonRllmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_TM_RLLM_EI_L3_INFO(msg))
    {
        printf("lengthInd   : %04x\n", l3Info->lengthInd);

        for (i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_PrintRelReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;

    /* display Release Request message */
    ret = Print_CommonRllmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Mode bit   : %02x\n", msg->u.rllmMsg.u.relReq.modeBit);

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintBcchInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CCM_BCCH_INFO *bcchInfo = &msg->u.ccmMsg.u.bcchInfo;
    TM_FULL_BCCH_INFO *fullBcch = &msg->u.ccmMsg.u.bcchInfo.fullBcch;

    /* display BCCH Information message */
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Sys Info type   : %02x\n", bcchInfo->sysInfoType);
    
    if (IS_PRESENT_TM_CCM_BI_FULL_BCCH_INFO(msg))
    {
        printf("FB Length Ind   : %02x\n", fullBcch->length);

        for (i = 0; i < fullBcch->length; i++)
        {
            printf("FB msg[%d]  : %02x\n", i, fullBcch->msg[i]);
        }
    }

    if (IS_PRESENT_TM_CCM_BI_STARTING_TIME(msg))
    {
        printf("Starting time : %04x\n", bcchInfo->startingTime);        
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintCcchLoadInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_RACH_LOAD *rach = &msg->u.ccmMsg.u.ccchLoadInd.rach;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum;

    /* display CCCH Load Indication message */
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (chanlNum->chanlBits == TM_CN_UPLINK_CCCH)
    {
        printf("RACH Length  : %02x\n", rach->length);
        printf("Slot Count   : %02x\n", rach->slotCount);
        printf("Busy Count   : %02x\n", rach->busyCount);
        printf("Access Count : %02x\n", rach->accessCount);

        for (i = 0; i < (rach->length-6); i++)
        {
            printf("RACH Info[%d] : %02x\n", i, rach->info[i]);
        }
    }

    if (chanlNum->chanlBits == TM_CN_DOWNLINK_CCCH)
    {
        printf("PageBufSpace : %02x\n",
                      msg->u.ccmMsg.u.ccchLoadInd.pagBufSpace);
    } 

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintChanRqd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CCM_CHAN_RQD *chanRqd = &msg->u.ccmMsg.u.chanRqd;
    TM_PHYSICAL_CONTEXT *phyContext = &msg->u.ccmMsg.u.chanRqd.phyContext;

    /* display Chaneel Required message */
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("chanRqdRA   : %02x\n", chanRqd->RA);
    printf("reqRefNum   : %02x\n", chanRqd->reqRefNum);
    printf("accessDelay : %02x\n", chanRqd->accessDelay);

    if (IS_PRESENT_TM_CCM_CR_PHYSICAL_CONTEXT(msg))
    {
        printf("PC Length   : %02x\n", phyContext->length);

        for (i = 0; i < phyContext->length; i++)
        {
            printf("PC Content[%d] : %02x\n", i, phyContext->content[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintDeleteInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CCM_DELETE_IND *deleteInd = &msg->u.ccmMsg.u.deleteInd; 

    /* display Delete Indication message */
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("DelInd Length   : %02x\n", deleteInd->length);

    for (i = 0; i < deleteInd->length; i++)
    {
        printf("AssignInfo[%d] : %02x\n", i, deleteInd->assignInfo[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintPagingCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CCM_PAGING_CMD *pagingCmd = &msg->u.ccmMsg.u.pagingCmd;
    TM_MS_IDENTITY *msIdentity = &msg->u.ccmMsg.u.pagingCmd.msIdentity;

    /* display Paging Command message */
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Paging Group : %02x\n", pagingCmd->pagingGroup);
    printf("MSI length   : %02x\n", msIdentity->length);

    for (i = 0; i < msIdentity->length; i++)
    {
        printf("Identity[%d] : %02x\n", i, msIdentity->identity[i]);
    }

    if (IS_PRESENT_TM_CCM_PC_CHANNEL_NEEDED(msg))
    {
        printf("Chanl Need   : %02x\n", pagingCmd->chanlNeed);
    }

    if (IS_PRESENT_TM_CCM_PC_EMLPP_PRIORITY(msg))
    {
        printf("CallPriority : %02x\n", pagingCmd->callPriority);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintSmsBCReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CCM_SMS_BC_REQ *smsBcReq = &msg->u.ccmMsg.u.smsBcReq;

    /* display SMS Broadcast Request message */
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("SmscbInfoLen : %02x\n", smsBcReq->smscbInfoLen);

    for (i = 0; i < smsBcReq->smscbInfoLen; i++)
    {
        printf("SmscbIfo[%d] : %02x\n", i, smsBcReq->smscbInfo[i]);
    }

    if (IS_PRESENT_TM_CCM_SBR_SMSCB_CHANNEL_IND(msg))
    {
        printf("ChanlInd : %02x\n", smsBcReq->chanlInd);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_PrintRfReInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_TRAX_RF_RES_IND *rfResInd = &msg->u.trxmMsg.u.rfResInd;

    /* display RF Resource Indication message */
    ret = Print_CommonElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Length   : %02x\n", rfResInd->length);

    for (i = 0; i < (rfResInd->length/2); i++)
    {
        printf("CNTimeSlotNum[%d]: %02x\n",
                                  i, rfResInd->info[i].chanlNum.timeSlotNum);
        printf("CNChanlBits[%d]  : %02x\n",
                                    i, rfResInd->info[i].chanlNum.chanlBits);  
        printf("InterfBand[%d]   : %02x\n", i, rfResInd->info[i].interfBand);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_PrintSacchFill(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_TRAX_SACCH_FILL *sacchFill = &msg->u.trxmMsg.u.sacchFill;
    TM_L3_INFORMATION *l3Info = &msg->u.trxmMsg.u.sacchFill.l3Info;

    /* display SACCH Filling message*/
    ret = Print_CommonElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }   

    printf("SysInfoType   : %02x\n", sacchFill->sysInfoType);

    if (IS_PRESENT_TM_TRXM_SF_L3_INFO(msg))
    { 
        printf("L3InfoLenInd  : %02x\n", l3Info->lengthInd);

        for (i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDu[%d]  : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    if (IS_PRESENT_TM_TRXM_SF_STARTING_TIME(msg))
    {
        printf("StartingTime  : %02x\n", sacchFill->startingTime);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_PrintOverload(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_TRAX_OVERLOAD *overload = &msg->u.trxmMsg.u.overload;

    /* display Overload  message*/
    ret = Print_CommonElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Overload Length : %02x\n", overload->length);
    printf("Cause Value     : %02x\n", overload->causeVal);

    for (i = 0; i < overload->length; i++)
    {
        printf("diagnostics[%d] : %02x\n", i, overload->diagnostics[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_PrintErrorReport(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CAUSE *cause = &msg->u.trxmMsg.u.errorReport.cause;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.trxmMsg.u.errorReport.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.trxmMsg.u.errorReport.linkId;
    TM_ERRONEOUS_MSG *errMsg = &msg->u.trxmMsg.u.errorReport.errMsg;

    /* display  Error Report message*/
    ret = Print_CommonElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Cause Length : %02x\n", cause->length);
    printf("Cause Value  : %02x\n", cause->causeVal);

    for (i = 0; i < cause->length; i++)
    {
        printf("Diagnostics[%d]  : %02x\n", i, cause->diagnostics[i]);
    }

    if (IS_PRESENT_TM_TRXM_ER_MESSAGE_IDENTIFIER(msg))
    {
        printf("MsgId       : %02x\n", msg->u.trxmMsg.u.errorReport.msgId);
    }

    if (IS_PRESENT_TM_TRXM_ER_CHANNEL_NUMBER(msg))
    {
        printf("timeSlotNum : %02x\n", chanlNum->timeSlotNum);
        printf("Chanl Bits  : %02x\n", chanlNum->chanlBits);
    }

    if (IS_PRESENT_TM_TRXM_ER_LINK_IDENTIFIER(msg))
    {
        printf("SAPI        : %02x\n", linkId->SAPI);
        printf("Priority    : %02x\n", linkId->priority);
        printf("Chanl Bits  : %02x\n", linkId->chanlBits);
        printf("LinkId NA   : %02x\n", linkId->NA);
    }

    if (IS_PRESENT_TM_TRXM_ER_ERRONEOUS_MSG(msg))
    {
        printf("ErrMsgLength: %02x\n", errMsg->length);

        for (i = 0; i < errMsg->length; i++)
        {
            printf("recvdMsg[%d]  : %02x\n", i, errMsg->recvdMsg[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintSmsBcCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CB_CMD_TYPE *cmdType = &msg->u.ccmMsg.u.smsBcCmd.cmdType;
    TM_SMSCB_MSG *smscbMsg = &msg->u.ccmMsg.u.smsBcCmd.smscbMsg;

    /* display SMS Broadcast Command message*/
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Last Block   : %02x\n", cmdType->lastlock);
    printf("Command      : %02x\n", cmdType->command);
    printf("Broadcast    : %02x\n", cmdType->broadcast);
    printf("SMSCB length : %02x\n", smscbMsg->length);

    for (i = 0; i < smscbMsg->length; i++)
    {
        printf("msg[%d] : %02x\n", i,smscbMsg->msg[i]);
    }

    if (IS_PRESENT_TM_CCM_SBC_SMSCB_CHANNEL_IND(msg))
    {
        printf("ChanlInd  : %02x\n", msg->u.ccmMsg.u.smsBcCmd.chanlInd);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintCbchLoadInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;
    TM_CCM_CBCH_LOAD_IND *cbchLoadInd = &msg->u.ccmMsg.u.cbchLoadInd;

    /* display CBCH Load Indication  message*/
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Slot Count    : %02x\n", cbchLoadInd->slotCount);
    printf("CBCH LoadType : %02x\n", cbchLoadInd->type);

    if (IS_PRESENT_TM_CCM_CLI_SMSCB_CHANNEL_IND(msg))
    {
        printf("Chanl Indi    : %02x\n", cbchLoadInd->chanlInd); 
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_PrintNotiCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_COMMAND_IND *cmdInd = &msg->u.ccmMsg.u.notCmd.cmdInd;
    TM_GROUP_CALL_REF *callRef = &msg->u.ccmMsg.u.notCmd.callRef;
    TM_GROUP_CHANNEL_DESC *chanlDesc = &msg->u.ccmMsg.u.notCmd.chanlDesc;
    TM_NCH_DRX_INFO *nchDrx = &msg->u.ccmMsg.u.notCmd.nchDrx;

    /* display Notification Command  message*/
    ret = Print_CommonCcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("CmdInd Len    : %02x\n", cmdInd->length);
    printf("CmdVal        : %02x\n", cmdInd->cmdVal);

    if (IS_PRESENT_TM_CCM_NC_GROUP_CALL_REFERENCE(msg))
    {
        printf("CallRef len   : %02x\n", callRef->length);

        for (i = 0; i < callRef->length; i++)
        {
            printf("DescGroup[%d] : %02x\n", i, callRef->descGroup[i]);
        }
    }

    if (IS_PRESENT_TM_CCM_NC_CHANNEL_DESCRIPTION(msg))
    {
        printf("ChanlDesc len : %02x\n", chanlDesc->length);

        for (i = 0; i < chanlDesc->length; i++)
        {
            printf("ChanlDesc[%d] : %02x\n", i, chanlDesc->chanlDesc[i]);
        }
    }

    if (IS_PRESENT_TM_CCM_NC_NCH_DRX_INFO(msg))
    {
        printf("NCHDRX len    : %02x\n", nchDrx->length);
        printf("NCHDRX emlpp  : %02x\n", nchDrx->emlpp); 
        printf("NLN           : %02x\n", nchDrx->NLN);
        printf("Status        : %02x\n", nchDrx->status);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintChanActiv(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i, j;
    TM_DCM_CHAN_ACTIV *chanActiv = &msg->u.dcmMsg.u.chanActiv;
    TM_CHANNEL_MODE *chnlMode = &msg->u.dcmMsg.u.chanActiv.chnlMode;
    TM_CHANNEL_ID *chnlId = &msg->u.dcmMsg.u.chanActiv.chnlId;
    TM_ENCRYPTION_INFO *encrption = &msg->u.dcmMsg.u.chanActiv.encryption;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.chanActiv.bsPower;
    TM_MS_POWER *msPower = &msg->u.dcmMsg.u.chanActiv.msPower;
    TM_BS_POWER_PARAMS *bsParams = &msg->u.dcmMsg.u.chanActiv.bsParams;
    TM_MS_POWER_PARAMS *msParams = &msg->u.dcmMsg.u.chanActiv.msParams;
    TM_PHYSICAL_CONTEXT *phyCnxt = &msg->u.dcmMsg.u.chanActiv.phyContext;
    TM_SACCH_INFO *sacchInfo = &msg->u.dcmMsg.u.chanActiv.sacchInfo;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.chanActiv.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.chanActiv.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.chanActiv.codecTypes; 

    /* display Chanel Activation message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Activation Type */
    printf("Active Type   : %02x\n", chanActiv->actType);
    printf("Procedure     : %02x\n", chanActiv->procedure);

    /* Channel Mode */
    printf("CM Length     : %02x\n", chnlMode->length);
    printf("DTXD          : %02x\n", chnlMode->dtxd);
    printf("DTXU          : %02x\n", chnlMode->dtxu);
    printf("Indicatior    : %02x\n", chnlMode->indicator);
    printf("RateAnd Type  : %02x\n", chnlMode->rateAndType);
    printf("codingAlg     : %02x\n", chnlMode->codingAlg);

    if (chnlMode->indicator == TM_CM_DATA)
    {
        printf("rate          : %02x\n", chnlMode->rate);
        printf("service       : %02x\n", chnlMode->service);
    }
    
    /* Channel Identification */
    if (IS_PRESENT_TM_DCM_CA_CHANNEL_IDENTIFIER(msg))
    {
        printf("CI Length     : %02x\n", chnlId->length);
    }
        
    /* Encryption Information */
    if (IS_PRESENT_TM_DCM_CA_ENCRYPT_INFO(msg))
    {
        printf("EI length     : %02x\n", encrption->length);
        printf("algorithmId   : %02x\n", encrption->algorithmId);

        for (i = 0; i < encrption->length; i++)
        {
            printf("key[%d]        : %02x\n", i, encrption->key[i]);
        }
    } 

    /* Handover Reference */
    printf("HandRef       : %02x\n", chanActiv->handRef);
       
    /* BS Power */
    if (IS_PRESENT_TM_DCM_CA_BS_POWER(msg))
    { 
        printf("BsPowLevel    : %02x\n", bsPower->powerLevel);
        printf("FPC           : %02x\n", bsPower->FPC);
    } 

    /* MS Power */
    if (IS_PRESENT_TM_DCM_CA_MS_POWER(msg))
    { 
        printf("MsPowLevel    : %02x\n", msPower->powerLevel);
        printf("FPC           : %02x\n", msPower->FPC);
    }
    
    /* Timing Advance */
    printf("timingAdv     : %02x\n", chanActiv->timingAdv);
        
    /* BS Power Parameters */   
    if (IS_PRESENT_TM_DCM_CA_BS_POWER_PARAMS(msg))
    { 
        printf("BsParamsLen   : %02x\n", bsParams->length);

        for (i = 0; i < bsParams->length ; i++)
        {
            printf("powerControl[%d]: %02x\n", i, bsParams->powerControl[i]);
        }
    }

    /* MS Power Parameters */
    if (IS_PRESENT_TM_DCM_CA_MS_POWER_PARAMS(msg))
    { 
        printf("MsParamsLen   : %02x\n", msParams->length);

        for (i = 0; i < msParams->length ; i++)
        {
            printf("powerControl[%d]: %02x\n", i, msParams->powerControl[i]);
        }
    }

    /* Physical Context */
    if (IS_PRESENT_TM_DCM_CA_PHYSICAL_CONTEXT(msg))
    { 
        printf("PhyCnxtLen    : %02x\n", phyCnxt->length);

        for (i = 0; i < phyCnxt->length; i++)
        {
            printf("content[%d]    : %02x\n", i, phyCnxt->content[i]);
        }
    }

    /* SACCH Information */
    if (IS_PRESENT_TM_DCM_CA_SAACH_INFO(msg))
    { 
        printf("SacchInflen   : %02x\n", sacchInfo->length);
        printf("NoOfMsgs      : %02x\n", sacchInfo->numOfMsgs);

        for (i = 0; i < sacchInfo->numOfMsgs ; i++)
        {
            printf("msg[%d]Type    : %02x\n",
                                           i, sacchInfo->msgInfo[i].typeOfMsg);
            printf("msg[%d]Length  : %02x\n", i, sacchInfo->msgInfo[i].length);

            for (j = 0; j< sacchInfo->msgInfo[i].length; j++)
            {
                printf("msg[%d].mesg[%d]: %02x\n",
                                           i, j, sacchInfo->msgInfo[i].msg[j]);
            }
        }
    }

    /* UIC */
    if (IS_PRESENT_TM_DCM_CA_UIC(msg))
    { 
        printf("uicLen        : %02x\n", chanActiv->uicLen);
        printf("uicInfo       : %02x\n", chanActiv->uicInfo);
    }
    
    /* Main Channel Referenc */
    if (IS_PRESENT_TM_DCM_CA_MAIN_CHANNEL_REF(msg))
    { 
        printf("mainChnlRefTn : %02x\n", chanActiv->mainChnlRefTn);
    }
    
    /* Multirate Configuration */
    if (IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONFIG(msg))
    { 
        printf("MrConfLen     : %02x\n", mrConfig->length);

        for (i = 0; i < mrConfig->length ; i++)
        { 
            printf("content[%d]    : %02x\n", i, mrConfig->content[i]);
        }
    }

    /* Multirate Control */
    if (IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONTROL(msg))
    { 
        printf("mrControl.TFO : %02x\n", mrControl->TFO);
        printf("mrControl.PRE : %02x\n", mrControl->PRE);
        printf("mrControl.RAE : %02x\n", mrControl->RAE);
    }
    
    /* Supported Codec Types */
    if (IS_PRESENT_TM_DCM_CA_SUPPORTED_CODEC_TYPES(msg))
    { 
        printf("CTLen         : %02x\n", codecTypes->length);
        printf("sysId         : %02x\n", codecTypes->sysId);
        printf("codecList     : %02x\n", codecTypes->codecList);
        printf("MACS[0]       : %02x\n", codecTypes->MACS[0]);
        printf("TFO_VER[0]    : %02x\n", codecTypes->TFO_VER[0]);
        printf("MACS[1]       : %02x\n", codecTypes->MACS[1]);
        printf("TFO_VER[1]    : %02x\n", codecTypes->TFO_VER[1]);
        printf("SCS[0]        : %02x\n", codecTypes->SCS[0]);
        printf("SCS[1]        : %02x\n", codecTypes->SCS[1]);
        printf("prefCodecType : %02x\n", codecTypes->prefCodecType);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintChanActivAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;

    /* display  Chanel Activation Acknowledge  message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Frame Number  : %02x\n", msg->u.dcmMsg.u.chanActivAck.frameNum);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintChanActivNAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_DCM_CHAN_ACTIV_NACK *chanActivNack = &msg->u.dcmMsg.u.chanActivNack; 

    /* display  Chanel Activation Negative Acknowledge  message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                  

    printf("Length      : %02x\n", chanActivNack->length);
    printf("Cause Value : %02x\n", chanActivNack->causeVal);

    for (i = 0; i < chanActivNack->length; i++)
    {
        printf("Diagnostics[%d] : %02x\n", i, chanActivNack->diagnostics[i]);
    }      

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintDeactivSaach(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;

    /* display  Deactivate SACCH message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintEncrCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_ENCRYPTION_INFO *encryption = &msg->u.dcmMsg.u.encrCmd.encryption;
    TM_LINK_IDENTIFIER *linkId = &msg->u.dcmMsg.u.encrCmd.linkId;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.encrCmd.l3Info;

    /* display Encryption Command message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("SAPI        : %02x\n", linkId->SAPI);
    printf("Priority    : %02x\n", linkId->priority);
    printf("Chanl Bits  : %02x\n", linkId->chanlBits);
    printf("NA          : %02x\n", linkId->NA);
    printf("Length      : %02x\n", encryption->length);
    printf("AlgId       : %02x\n", encryption->algorithmId);

    for (i = 0; i < (encryption->length - 1); i++)
    {
        printf("key[%d] : %02x\n", i, encryption->key[i]);
    }

    printf("LengthInd : %02x\n", l3Info->lengthInd);

    for (i = 0; i < l3Info->lengthInd; i++)
    {
        printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintHandODet(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;

    /* display  HandOver Detection message*/
    ret = Print_CommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }      

    if (IS_PRESENT_TM_DCM_HD_ACCESS_DELAY(msg))
    {
        printf("Access Dealay : %02x\n", msg->u.dcmMsg.u.handoDet.accessDelay);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_DCM_MEAS_RES *measRes = &msg->u.dcmMsg.u.measRes;
    TM_UPLINK_MEAS *uplinkMeas = &msg->u.dcmMsg.u.measRes.uplinkMeas;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.measRes.bsPower;
    TM_L1_INFORMATION *l1Info = &msg->u.dcmMsg.u.measRes.l1Info;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.measRes.l3Info;

    /* display  Measurement Result message*/
    ret = Print_CommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("MeasResultNum : %02x\n", measRes->measResultNum);

    printf("Length        : %02x\n", uplinkMeas->length);
    printf("RXLevFullup   : %02x\n", uplinkMeas->rxlevFullUp);
    printf("RXLevSubUp    : %02x\n", uplinkMeas->rxlevSubUp);
    printf("RXQualFullUp  : %02x\n", uplinkMeas->rxqualFullUp);
    printf("RXQualSubUp   : %02x\n", uplinkMeas->rxqualSubUp);
    printf("RFU           : %02x\n", uplinkMeas->rfu);
    printf("DTXD          : %02x\n", uplinkMeas->dtxd);

    for (i = 0; i < uplinkMeas->length; i++)
    {
        printf("SMI[%d]      : %02x\n", i, uplinkMeas->SMI[i]);
    }

    printf("powerLevel    : %02x\n", bsPower->powerLevel);
    printf("FPC           : %02x\n", bsPower->FPC);

    if (IS_PRESENT_TM_DCM_MR_L1_INFO(msg))
    {
        printf("powerLevel    : %02x\n", l1Info->powerLevel);
        printf("timingAdvns   : %02x\n", l1Info->timingAdvns);
        printf("FPC           : %02x\n", l1Info->FPC);
    }
 
    if (IS_PRESENT_TM_DCM_MR_L3_INFO(msg))
    {
        printf("lengthInd     : %02x\n", l3Info->lengthInd);
        for (i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    if (IS_PRESENT_TM_DCM_MR_MS_TIMING_OFFSET(msg))
    {
        printf("timingOffset  : %02x\n", measRes->timingOffset);
    }

    return ITS_SUCCESS;
}
  
static ITS_INT
TM_DCM_PrintModeModifyReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_CHANNEL_MODE *chnlMode = &msg->u.dcmMsg.u.modeModifyReq.chnlMode;
    TM_ENCRYPTION_INFO *encrption = &msg->u.dcmMsg.u.modeModifyReq.encryption;
    TM_DCM_MODE_MODIFY_REQ *modeModifyReq = &msg->u.dcmMsg.u.modeModifyReq;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.modeModifyReq.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.modeModifyReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.modeModifyReq.codecTypes;

    /* display Mode Modify message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Channel Mode */
    printf("ChnlModeLength: %02x\n", chnlMode->length);
    printf("dtxd          : %02x\n", chnlMode->dtxd);
    printf("dtxu          : %02x\n", chnlMode->dtxu);
    printf("indicator     : %02x\n", chnlMode->indicator);
    printf("rateAndType   : %02x\n", chnlMode->rateAndType);
    printf("codingAlg     : %02x\n", chnlMode->codingAlg);

    if (chnlMode->indicator == TM_CM_DATA)
    {
        printf("rate          : %02x\n", chnlMode->rate);
        printf("service       : %02x\n", chnlMode->service);
    }
    
    /* Encryption Information  */
    if (IS_PRESENT_TM_DCM_MM_ENCRYPT_CHANNEL(msg))
    {
        printf("length        : %02x\n", encrption->length);
        printf("algorithmId   : %02x\n", encrption->algorithmId);

        for (i = 0; i < encrption->length; i++)
        {
            printf("key[%d]     : %02x\n", i, encrption->key[i]);
        }
    }

    /* Main Channel Reference */
    if (IS_PRESENT_TM_DCM_MM_MAIN_CHANNEL_REF(msg))
    {
        printf("mainChnlRefTn : %02x\n", modeModifyReq->mainChnlRefTn);
    }
        
    /* Multirate Configuration */
    if (IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONFIG(msg))
    {
        printf("length        : %02x\n", mrConfig->length);

        for (i = 0; i < mrConfig->length; i++)
        {
            printf("content[%d]   : %02x\n", i, mrConfig->content[i]);
        }
    }

    /* Multirate Control */
    if (IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONTROL(msg))
    {
        printf("TFO           : %02x\n", mrControl->TFO);
        printf("PRE           : %02x\n", mrControl->PRE);
        printf("RAE           : %02x\n", mrControl->RAE);
    }
        
    /* Supported Codec types */
    if (IS_PRESENT_TM_DCM_MM_SUPPORTED_CODEC_TYPES(msg))
    {
        printf("length        : %02x\n", codecTypes->length);
        printf("sysId         : %02x\n", codecTypes->sysId);
        printf("codecList     : %02x\n", codecTypes->codecList);
        
        printf("MACS[0]       : %02x\n", codecTypes->MACS[0]);
        printf("TFO_VER[0]    : %02x\n", codecTypes->TFO_VER[0]);
        printf("SCS[0]        : %02x\n", codecTypes->SCS[0]);
        printf("MACS[1]       : %02x\n", codecTypes->MACS[1]);
        printf("TFO_VER[1]    : %02x\n", codecTypes->TFO_VER[1]);
        printf("SCS[1]        : %02x\n", codecTypes->SCS[1]);

        printf("prefCodecType : %02x\n", codecTypes->prefCodecType);
    }

    return ITS_SUCCESS;
}
  
static ITS_INT
TM_DCM_PrintPhyContextConf(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.phyContextConf.bsPower;
    TM_MS_POWER *msPower = &msg->u.dcmMsg.u.phyContextConf.msPower;
    TM_PHYSICAL_CONTEXT *phyContext = 
                                &msg->u.dcmMsg.u.phyContextConf.phyContext;

    /* display Physical Context Confirm message*/
    ret = Print_CommonDcmElements(&msg);
    
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("BS Power Level : %02x\n", bsPower->powerLevel);
    printf("FPC            : %02x\n", bsPower->FPC);
    printf("MS Power Level : %02x\n", msPower->powerLevel);
    printf("FPC            : %02x\n", msPower->FPC);

    printf("TimingAdv      : %02x\n", msg->u.dcmMsg.u.phyContextConf.timingAdv);

    if (IS_PRESENT_TM_DCM_PCC_PHYSICAL_CONTEXT(msg))
    {
        printf("Length         : %02x\n", phyContext->length);

        for (i = 0; i < phyContext->length; i++)
        {
            printf("Content[%d]  : %02x\n", i, phyContext->content[i]);
        }
    }

    return ITS_SUCCESS;
}
  
static ITS_INT
TM_DCM_PrintMsPowerControl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_MS_POWER *msPower = &msg->u.dcmMsg.u.mspowerControl.msPower;
    TM_MS_POWER_PARAMS *msParams = &msg->u.dcmMsg.u.mspowerControl.msParams;
    
    /* display MS Power Control message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Power Level : %02x\n", msPower->powerLevel);
    printf("FPC         : %02x\n", msPower->FPC);       

    if (IS_PRESENT_TM_DCM_MPC_MS_POWER_PARAMS(msg))
    {
        printf("Length      : %02x\n", msParams->length);

        for (i = 0; i < msParams->length; i++)
        {
            printf("powerControl[%d] : %02x\n", i, msParams->powerControl[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintBsPowerControl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.bspowerControl.bsPower;
    TM_BS_POWER_PARAMS *bsParams = &msg->u.dcmMsg.u.bspowerControl.bsParams;

    /* display BS Power Control message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Power Level  : %02x\n", bsPower->powerLevel);
    printf("FPC          : %02x\n", bsPower->FPC);

    if (IS_PRESENT_TM_DCM_BPC_BS_POWER_PARAMS(msg))
    {
        printf("Length       : %02x\n", bsParams->length);

        for (i = 0; i < bsParams->length; i++)
        {
           printf("powerControl[%d] : %02x\n", i, bsParams->powerControl[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintPreprocConfig(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_DCM_PREPROC_CONFIG *preprocConfig = &msg->u.dcmMsg.u.preprocConfig;

    /* display Preprocess Configure message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Length  : %02x\n", preprocConfig->length);

    for (i = 0; i < preprocConfig->length; i++)
    {
        printf("processParam[%d]  : %02x\n", i, preprocConfig->processParam[i]);
    }

    printf("Procedure  : %02x\n", preprocConfig->procedure);

    return ITS_SUCCESS;
}
 
static ITS_INT
TM_DCM_PrintPreproceMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_DCM_PREPOC_MEAS_RES *prepocMeasRes = &msg->u.dcmMsg.u.prepocMeasRes;

    /* display Preprocessed Measurement Result message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Length  : %02x\n", prepocMeasRes->length);

    for (i = 0; i < prepocMeasRes->length; i++)
    {
        printf("processMeas[%d]  : %02x\n", i, prepocMeasRes->processMeas[i]);
    }

    return ITS_SUCCESS;
}  

static ITS_INT
TM_DCM_PrintSacchInfoModify(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_DCM_SACCH_INFO_MOD *sacchInfoMod = &msg->u.dcmMsg.u.sacchInfoMod;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.sacchInfoMod.l3Info; 

    /* display SACCH Info Modify message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("SysInfoType  : %02x\n", sacchInfoMod->sysInfoType);

    if (IS_PRESENT_TM_DCM_SIM_L3_INFO(msg))
    {
        printf("LengthInd    : %04x\n", l3Info->lengthInd);

        for (i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDU[%d]   : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    if (IS_PRESENT_TM_DCM_SIM_STARTING_TIME(msg))
    {
        printf("StartingTime : %04x\n", sacchInfoMod->startingTime);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintRemotCodecConfRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;
    TM_CODEC_CONFIG *config = &msg->u.dcmMsg.u.remoteCodecConfRep.config;
    TM_SUPP_CODEC_TYPES *codecTypes =
                             &msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes;

    /* display Remote Codec Configuration Report message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("ConfigLength    : %02x\n", config->length);
    printf("CodecType       : %02x\n", config->codecType);
    printf("ICM             : %02x\n", config->ICM);
    printf("CodecSet        : %02x\n", config->codecSet);
    
    printf("CodecTypeLength : %02x\n", codecTypes->length);
    printf("SysId           : %02x\n", codecTypes->sysId);
    printf("CodecList       : %02x\n", codecTypes->codecList);
    printf("MACS[0]         : %02x\n", codecTypes->MACS[0]);
    printf("TFO_VER[0]      : %02x\n", codecTypes->TFO_VER[0]);
    printf("MACS[1]         : %02x\n", codecTypes->MACS[1]);
    printf("TFO_VER[1]      : %02x\n", codecTypes->TFO_VER[1]);
    printf("SCS[0]          : %02x\n", codecTypes->SCS[0]);
    printf("SCS[1]          : %02x\n", codecTypes->SCS[1]);
    printf("prefCodecType   : %02x\n", codecTypes->prefCodecType);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintRTDRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;
    TM_DCM_RTD_REP *rtdRep = &msg->u.dcmMsg.u.rtdRep;

    /* display  Round Trip Delay Report message*/
    ret = Print_CommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("RTD      : %02x\n", rtdRep->RTD);
    printf("Delay    : %02x\n", rtdRep->delay);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintPreHandONotif(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.preHandoNotif.mrControl;
    TM_CODEC_CONFIG *config = &msg->u.dcmMsg.u.preHandoNotif.config;

    /* display  Pre_HandOver Notification message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Length    : %02x\n", config->length);
    printf("codecType : %02x\n", config->codecType);
    printf("ICM       : %02x\n", config->ICM);
    printf("CodecSet  : %02x\n", config->codecSet);

    printf("TFO       : %02x\n", mrControl->TFO);
    printf("PRE       : %02x\n", mrControl->PRE);
    printf("RAE       : %02x\n", mrControl->RAE);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintMCodecModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.mrCodecModReq.mrConfig;

    /* display  Multirate Codec Modification Request message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }        
 
    if (IS_PRESENT_TM_DCM_MCMR_MULTI_RATE_CONFIG(msg))
    { 
        printf("Length  : %02x\n", mrConfig->length);

        for (i = 0; i < mrConfig->length; i++)
        {
            printf("content[%d]  : %02x\n", i, mrConfig->content[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintTfoRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;

    /* display TFO Report message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("TFO Status  : %02x\n", msg->u.dcmMsg.u.tfoRep.tfoStatus);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_PrintTfoModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.tfoModReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.tfoModReq.codecTypes;

    /* display TFO Modification Request message*/
    ret = Print_CommonDcmElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("TFO           : %02x\n", mrControl->TFO);
    printf("PRE           : %02x\n", mrControl->PRE);
    printf("RAE           : %02x\n", mrControl->RAE);

    if (IS_PRESENT_TM_DCM_TMR_SUPPORTED_CODEC_TYPE(msg))
    {
        printf("length        : %02x\n", codecTypes->length);
        printf("SysId         : %02x\n", codecTypes->sysId);
        printf("CodecList     : %02x\n", codecTypes->codecList);
        printf("MACS[0]       : %02x\n", codecTypes->MACS[0]);
        printf("TFO_VER[0]    : %02x\n", codecTypes->TFO_VER[0]);
        printf("MACS[1]       : %02x\n", codecTypes->MACS[1]);
        printf("TFO_VER[1]    : %02x\n", codecTypes->TFO_VER[1]);
        printf("SCS[0]        : %02x\n", codecTypes->SCS[0]);
        printf("SCS[1]        : %02x\n", codecTypes->SCS[1]);
        printf("prefCodecType : %02x\n", codecTypes->prefCodecType);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_LCS_PrintLocInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret, i;
    TM_LCS_LOC_INFO *lcsLocInfo = &msg->u.lcsMsg.u.lcsLocInfo;

    /* display Location Information message*/
    ret = Print_CommonElements(&msg);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Length     : %02x\n", lcsLocInfo->length);

    for (i = 0; i < lcsLocInfo->length; i++)
    {
       printf("FAC IEI[%d]   : %02x\n", i, lcsLocInfo->facIEI[i]);
    }

    return ITS_SUCCESS;
}
           
static ITS_INT
reserved(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    printf("Invalid/Reserved message Type\n");

    return ITS_SUCCESS;
}

/* Add all the function pointers here */
ITS_INT (*Print_Traffic_Msg[MAX_TRAFFIC_FUNS_SIZE])
                    (ABIS_TRAFFIC_MANAGEMENT_MSG *msg) =
{
    reserved,                      /* 0x00 */   
    TM_RLLM_PrintDataReq,          /* 0x01 */
    TM_RLLM_PrintDataReq,          /* 0x02 */
    TM_RLLM_PrintErrorInd,         /* 0x03 */
    TM_RLLM_PrintEstaReq,          /* 0x04 */
    TM_RLLM_PrintEstaReq,          /* 0x05 */
    TM_RLLM_PrintEstaInd,          /* 0x06 */
    TM_RLLM_PrintRelReq,           /* 0x07 */
    TM_RLLM_PrintEstaReq,          /* 0x08 */
    TM_RLLM_PrintEstaReq,          /* 0x09 */
    TM_RLLM_PrintDataReq,          /* 0x0A */
    TM_RLLM_PrintDataReq,          /* 0x0B */
    reserved,                      /* Reserved */
    reserved,                      /* Reserved */
    reserved,                      /* Reserved */
    reserved,                      /* Reserved */
    reserved,                      /* Reserved */
    TM_CCM_PrintBcchInfo,          /* 0x11 */
    TM_CCM_PrintCcchLoadInd,       /* 0x12 */
    TM_CCM_PrintChanRqd,           /* 0x13 */
    TM_CCM_PrintDeleteInd,         /* 0x14 */
    TM_CCM_PrintPagingCmd,         /* 0x15 */
    TM_CCM_PrintDeleteInd,         /* 0x16 */
    TM_CCM_PrintSmsBCReq,          /* 0x17 */
    reserved,                      /* Reserved */
    TM_TRXM_PrintRfReInd,          /* 0x19 */
    TM_TRXM_PrintSacchFill,        /* 0x1A */
    TM_TRXM_PrintOverload,         /* 0x1B */
    TM_TRXM_PrintErrorReport,      /* 0x1C */
    TM_CCM_PrintSmsBcCmd,          /* 0x1D */
    TM_CCM_PrintCbchLoadInd,       /* 0x1E */
    TM_CCM_PrintNotiCmd,           /* 0x1F */
    reserved,                      /* 0x20 */
    TM_DCM_PrintChanActiv,         /* 0x21 */
    TM_DCM_PrintChanActivAck,      /* 0x22 */
    TM_DCM_PrintChanActivNAck,     /* 0x23 */
    TM_DCM_PrintChanActivNAck,     /* 0x24 */
    TM_DCM_PrintDeactivSaach,      /* 0x25 */
    TM_DCM_PrintEncrCmd,           /* 0x26 */
    TM_DCM_PrintHandODet,          /* 0x27 */
    TM_DCM_PrintMeasRes,           /* 0x28 */
    TM_DCM_PrintModeModifyReq,     /* 0x29 */
    TM_DCM_PrintDeactivSaach,      /* 0x2A */
    TM_DCM_PrintChanActivNAck,     /* 0x2B */
    TM_DCM_PrintDeactivSaach,      /* 0x2C */
    TM_DCM_PrintPhyContextConf,    /* 0x2D */
    TM_DCM_PrintDeactivSaach,      /* 0x2E */
    TM_DCM_PrintMsPowerControl,    /* 0x2F */
    TM_DCM_PrintBsPowerControl,    /* 0x30 */
    TM_DCM_PrintPreprocConfig,     /* 0x31 */
    TM_DCM_PrintPreproceMeasRes,   /* 0x32 */
    TM_DCM_PrintDeactivSaach,      /* 0x33 */
    TM_DCM_PrintSacchInfoModify,   /* 0x34 */
    TM_DCM_PrintHandODet,          /* 0x35 */
    TM_DCM_PrintHandODet,          /* 0x36 */
    TM_DCM_PrintRemotCodecConfRep, /* 0x37 */
    TM_DCM_PrintRTDRep,            /* 0x38 */
    TM_DCM_PrintPreHandONotif,     /* 0x39 */
    TM_DCM_PrintMCodecModReq,      /* 0x3A */
    TM_DCM_PrintMCodecModReq,      /* 0x3B */
    TM_DCM_PrintChanActivNAck,     /* 0x3C */
    TM_DCM_PrintMCodecModReq,      /* 0x3D */
    TM_DCM_PrintTfoRep,            /* 0x3E */
    TM_DCM_PrintTfoModReq,         /* 0x3F */
    reserved,                      /* Reserved */
    TM_LCS_PrintLocInfo            /* 0x41 */
};
