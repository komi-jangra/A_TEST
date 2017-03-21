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
 *  ID: $Id: traffic_codec_test_app.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:53  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.2  2006/03/28 09:18:05  yranade
 *  TRX Hello message added. (sgavalkar)
 *
 *  Revision 1.1.2.1  2005/08/16 09:34:13  mkrishna
 *  added initail version after unit testing.
 *
 *
 ****************************************************************************/

#include <abis_traffic_management.h>

static ITS_INT
encodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_INT choice)
{  
    TM_MSG_DESCRIMINATOR *desc = &msg->genElemnts.msgDesc;

    desc->trasparent = 0x00;
    desc->msgGruop   = 0x78;
    msg->genElemnts.msgType = choice;

    return ITS_SUCCESS;
}

static ITS_INT
encodeCommonRllmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_INT choice)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.rllmMsg.rllmGenElements.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.rllmMsg.rllmGenElements.linkId;

    ret = encodeCommonElements(msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    chanlNum->timeSlotNum = 0x07;
    chanlNum->chanlBits   = 0x1f;
    linkId->SAPI          = 0x07;
    linkId->priority      = 0x03;
    linkId->chanlBits     = 0x03;
    linkId->NA            = 0x01;

    return ITS_SUCCESS;
}

static ITS_INT
encodeCommonDcmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_INT choice)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.dcmMsg.dcmGenElements.chanlNum;

    ret = encodeCommonElements(msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    chanlNum->timeSlotNum = 0x07;
    chanlNum->chanlBits   = 0x1f;

    return ITS_SUCCESS;
}

static ITS_INT
encodeCommonCcmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_INT choice)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum; 

    ret = encodeCommonElements(msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    chanlNum->timeSlotNum = 0x07;
    chanlNum->chanlBits   = 0x11;

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_encodeDataReq(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_L3_INFORMATION *l3Info = &msg.u.rllmMsg.u.dataReq.l3Info;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];


    /* fill up Data Request msg */
    ret = encodeCommonRllmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    l3Info->lengthInd = 0x0001;
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        l3Info->LLSDU[i] = 0xff;
    } 

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer); 
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Data Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS; 
}

static ITS_INT
TM_RLLM_encodeErrorInd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_RLLM_ERROR_IND *errorInd = &msg.u.rllmMsg.u.errorInd;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];


    /* fill up Error Indication msg */
    ret = encodeCommonRllmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    errorInd->rlmLen    = 0xff;
    errorInd->causeVal  = 0x8f;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Error Indication Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Error Indication Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_encodeEstaReq(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up establish request msg */
    ret = encodeCommonRllmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Establish Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Establish Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}
                                                                                                                     
static ITS_INT
TM_RLLM_encodeEstaInd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_L3_INFORMATION *l3Info = &msg.u.rllmMsg.u.estInd.l3Info;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Establish Indication msg */
    ret = encodeCommonRllmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map field to ZERO */
    CLEAR_TM_RLLM_EI_OPTIONAL_BIT_MAP(((&msg)));

    SET_TM_RLLM_EI_L3_INFO(((&msg)));
    l3Info->lengthInd = 0x0001;
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        l3Info->LLSDU[i]  = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer); 
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Establish Indication Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Establish Indication Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]); 
        }
        printf("\n\n"); 
    }

    return ITS_SUCCESS; 
}
                                                                                                          
static ITS_INT
TM_RLLM_encodeRelReq(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Release Request msg */
    ret = encodeCommonRllmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    msg.u.rllmMsg.u.relReq.modeBit = 0x01;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Release Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Release Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeBcchInfo(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_BCCH_INFO *bcchInfo = &msg.u.ccmMsg.u.bcchInfo;
    TM_FULL_BCCH_INFO *fullBcch = &msg.u.ccmMsg.u.bcchInfo.fullBcch;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up BCCH Information  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    bcchInfo->sysInfoType  = 0xff;

    CLEAR_TM_CCM_BI_OPTIONAL_BIT_MAP((&msg));
    /* Full BCCH Info */
    SET_TM_CCM_BI_FULL_BCCH_INFO((&msg));
    fullBcch->length   = 0x01;
    for(i = 0; i < fullBcch->length; i++)
    {
        fullBcch->msg[i] = 0xff;
    }

    /* Starting Time */
    SET_TM_CCM_BI_STARTING_TIME((&msg));
    bcchInfo->startingTime  = 0xabcd;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding BCCH Information Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding BCCH Information Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeCcchLoadInd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_RACH_LOAD *rach = &msg.u.ccmMsg.u.ccchLoadInd.rach;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up CCCH Load Indication  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* RACH Load */
    rach->length       = 0x09;
    rach->slotCount    = 0x1234;
    rach->busyCount    = 0x5678;
    rach->accessCount  = 0xabcd;
    for(i = 0; i < (rach->length - 6); i++) 
    {
        rach->info[i]  = 0xff;
    }

    /* Paging Load */
    msg.u.ccmMsg.u.ccchLoadInd.pagBufSpace  = 0xcdef;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding CCCH Load Indication Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding CCCH Load Indication Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeChanRqd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_PHYSICAL_CONTEXT *phyCnxt = &msg.u.ccmMsg.u.chanRqd.phyContext;
    TM_CCM_CHAN_RQD *chanRqd = &msg.u.ccmMsg.u.chanRqd;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up Chaneel  Required  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    chanRqd->RA          = 0xff;
    chanRqd->reqRefNum   = 0x1234;
    chanRqd->accessDelay = 0xff;
 
    /* Initialise optional bit map */
    CLEAR_TM_CCM_CR_OPTIONAL_BIT_MAP((&msg));

    /* Physical Context */
    SET_TM_CCM_CR_PHYSICAL_CONTEXT((&msg));
    phyCnxt->length  = 0x01;
    for(i = 0; i < phyCnxt->length; i++)
    {
        phyCnxt->content[i] = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Channel Required Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Channel Required success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeDeleteInd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_DELETE_IND *deleteInd = &msg.u.ccmMsg.u.deleteInd;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up Delete Indication msg */ 
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    deleteInd->length  = 0x05;
    for(i = 0; i < deleteInd->length; i++)
    {
        deleteInd->assignInfo[i]  = 0xff;
    }
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Delete Indication Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Delete Indication  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodePagingCmd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MS_IDENTITY *msIdentity = &msg.u.ccmMsg.u.pagingCmd.msIdentity;
    TM_CCM_PAGING_CMD *pagCmd = &msg.u.ccmMsg.u.pagingCmd; 
    ITS_INT len = 0, ret = 0, i, j;
    ITS_OCTET buffer[100];

    /* fill up Paging Command  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    pagCmd->pagingGroup = 0xff;
    msIdentity->length  = 0x02;
    for(i = 0; i < msIdentity->length; i++)
    {
        msIdentity->identity[i] = 0xff;
    }
    
    /* Initialise optional bit map */
    CLEAR_TM_CCM_PC_OPTIONAL_BIT_MAP((&msg));

    /* Channel Needed */
    SET_TM_CCM_PC_CHANNEL_NEEDED((&msg));
    pagCmd->chanlNeed = 0x03;
   
    /* eMLPP Priority */
    SET_TM_CCM_PC_EMLPP_PRIORITY((&msg));
    pagCmd->callPriority = 0x07;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Paging Command Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Paging Command  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeSmsBCReq(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_SMS_BC_REQ *smsReq = &msg.u.ccmMsg.u.smsBcReq;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up SMS Broadcast Request  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    smsReq->smscbInfoLen  = 0x03; 
    for(i = 0; i < smsReq->smscbInfoLen; i++)
    {
        smsReq->smscbInfo[i] = 0xff;
    }
    
    /* Initialise optional bit map */
    CLEAR_TM_CCM_SBR_OPTIONAL_BIT_MAP((&msg));

    /* SMSCB Channel Indicator */
    SET_TM_CCM_SBR_SMSCB_CHANNEL_IND((&msg));
    smsReq->chanlInd = 0x0f;      
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding  SMS Broadcast Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  SMS Broadcast Request  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_encodeRfReInd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_TRAX_RF_RES_IND *rfResInd = &msg.u.trxmMsg.u.rfResInd;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up RF Resource Indication  msg */
    ret = encodeCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    rfResInd->length = 0x04;
    for(i = 0; i < (rfResInd->length/2); i++)
    {
        rfResInd->info[i].chanlNum.timeSlotNum = 0x07;
        rfResInd->info[i].chanlNum.chanlBits   = 0x1f;
        rfResInd->info[i].interfBand           = 0x07;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding RF Resource Indication  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  RF Resource Indication  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_encodeSacchFill(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_L3_INFORMATION *l3Info = &msg.u.trxmMsg.u.sacchFill.l3Info;
    TM_TRAX_SACCH_FILL *sacchFill = &msg.u.trxmMsg.u.sacchFill;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up SACCH Filling  msg */
    ret = encodeCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    sacchFill->sysInfoType = 0x01;
    
    /* Initialise optional bit map */
    CLEAR_TM_TRXM_SF_OPTIONAL_BIT_MAP((&msg));

    /* L3 Info */
    SET_TM_TRXM_SF_L3_INFO((&msg));    
    l3Info->lengthInd = 0x0002;
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        l3Info->LLSDU[i] = 0xff;
    }

    /* Starting Time */
    SET_TM_TRXM_SF_STARTING_TIME((&msg));
    sacchFill->startingTime  = 0xcdef;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SACCH Filling  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  SACCH Filling  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}
                                                                                                                             
static ITS_INT
TM_TRXM_encodeOverload(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_TRAX_OVERLOAD *overload = &msg.u.trxmMsg.u.overload;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up Overload  msg */
    ret = encodeCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
          return ret;
    }
    overload->length   = 0x00;   
    overload->causeVal = 0x80;
    for(i = 0; i < overload->length; i++)
    {
        overload->diagnostics[i]  = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Overload  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Overload  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_encodeErrorReport(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CAUSE *cause = &msg.u.trxmMsg.u.errorReport.cause;
    TM_TRAX_ERROR_REPORT *errorReport = &msg.u.trxmMsg.u.errorReport;
    TM_CHANNEL_NUMBER *chanlNum = &msg.u.trxmMsg.u.errorReport.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg.u.trxmMsg.u.errorReport.linkId;
    TM_ERRONEOUS_MSG *errMsg = &msg.u.trxmMsg.u.errorReport.errMsg;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up Error Report  msg */
    ret = encodeCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    cause->length   = 0x03;
    cause->causeVal = 0x7f;
    for(i = 0; i < cause->length; i++)
    {
        cause->diagnostics[i] = 0xff;
    }
    
    /* Initialise optional bit map */
    CLEAR_TM_TRXM_ER_OPTIONAL_BIT_MAP((&msg));

    /* Message Identifier */
    SET_TM_TRXM_ER_MESSAGE_IDENTIFIER((&msg));
    errorReport->msgId  = 0xff;
    
    /* Channel Number */
    SET_TM_TRXM_ER_CHANNEL_NUMBER((&msg));
    chanlNum->timeSlotNum = 0x07;
    chanlNum->chanlBits   = 0x1f;
    
    /* Link Identifier */
    SET_TM_TRXM_ER_LINK_IDENTIFIER((&msg));
    linkId->SAPI      = 0x07;
    linkId->priority  = 0x03;
    linkId->chanlBits = 0x03;
    linkId->NA        = 0x01;
    
    /* Erroneous Message */
    SET_TM_TRXM_ER_ERRONEOUS_MSG((&msg));
    errMsg->length = 0x02;
    for(i = 0; i < errMsg->length; i++)
    {
        errMsg->recvdMsg[i] = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Error Report Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Error Report  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeSmsBcCmd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CB_CMD_TYPE *cmdType = &msg.u.ccmMsg.u.smsBcCmd.cmdType;
    TM_SMSCB_MSG *smscbMsg = &msg.u.ccmMsg.u.smsBcCmd.smscbMsg;
    TM_CCM_SMS_BC_CMD *smsCmd = &msg.u.ccmMsg.u.smsBcCmd;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up SMS Broadcast command  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    cmdType->lastlock  = 0x03;
    cmdType->command   = 0x0f;
    cmdType->broadcast = 0x01; 

    smscbMsg->length = 0x03;
    for(i = 0; i < smscbMsg->length; i++)
    {
        smscbMsg->msg[i] = 0xff;    
    } 

    /* Initialise optional bit map */
    CLEAR_TM_CCM_SBC_OPTIONAL_BIT_MAP((&msg));

    /* SMSCB Channel Indicator */
    SET_TM_CCM_SBC_SMSCB_CHANNEL_IND((&msg));
    smsCmd->chanlInd = 0x0f;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding  SMS Broadcast Command Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  SMS Broadcast Command  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeCbchLoadInd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_CBCH_LOAD_IND *loadInd = &msg.u.ccmMsg.u.cbchLoadInd;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up CBCH Load Indication  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    loadInd->slotCount = 0x0f;
    loadInd->type      = 0x01;
    
    /* Initialise optional bit map */
    CLEAR_TM_CCM_CLI_OPTIONAL_BIT_MAP((&msg));

    /* SMSCB Channel Indicator */
    SET_TM_CCM_CLI_SMSCB_CHANNEL_IND((&msg));
    loadInd->chanlInd = 0x0f;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding CBCH Load Indication Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding CBCH Load Indication  success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_encodeNotiCmd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_COMMAND_IND *cmdInd = &msg.u.ccmMsg.u.notCmd.cmdInd;
    TM_GROUP_CALL_REF *callRef = &msg.u.ccmMsg.u.notCmd.callRef;
    TM_GROUP_CHANNEL_DESC *chanlDesc = &msg.u.ccmMsg.u.notCmd.chanlDesc;
    TM_NCH_DRX_INFO *nchDrx = &msg.u.ccmMsg.u.notCmd.nchDrx; 
    ITS_INT len = 0, ret = 0, i, j;
    ITS_OCTET buffer[100];

    /* fill up Notification Command  msg */
    ret = encodeCommonCcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    cmdInd->length = 0x02;
    cmdInd->cmdVal = 0xff;
 
    /* Initialise optional bit map */
    CLEAR_TM_CCM_NC_OPTIONAL_BIT_MAP((&msg));

    /* Group call reference */
    SET_TM_CCM_NC_GROUP_CALL_REFERENCE((&msg));
    callRef->length  = 0x01;
    for (i = 0; i < callRef->length; i++)
    {
        callRef->descGroup[i]  = 0xff;
    }
 
    /* NCH DRX Information */
    SET_TM_CCM_NC_NCH_DRX_INFO((&msg));
    nchDrx->length = 0x01;
    nchDrx->NLN    = 0x03;
    nchDrx->emlpp  = 0x07;
    nchDrx->status = 0x01;

    /* Chanel Description */
    SET_TM_CCM_NC_CHANNEL_DESCRIPTION((&msg));
    chanlDesc->length  = 0x03;
    for(i = 0; i < chanlDesc->length; i++)
    {   
        chanlDesc->chanlDesc[i] = 0xff;    
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Notification Command Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Notification Command success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeChanActiv(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_CHAN_ACTIV *chanActiv = &msg.u.dcmMsg.u.chanActiv;
    TM_CHANNEL_MODE *chnlMode = &msg.u.dcmMsg.u.chanActiv.chnlMode;
    TM_CHANNEL_ID *chnlId = &msg.u.dcmMsg.u.chanActiv.chnlId;
    TM_ENCRYPTION_INFO *encrption = &msg.u.dcmMsg.u.chanActiv.encryption;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.chanActiv.bsPower;
    TM_MS_POWER *msPower = &msg.u.dcmMsg.u.chanActiv.msPower;
    TM_BS_POWER_PARAMS *bsParams = &msg.u.dcmMsg.u.chanActiv.bsParams;
    TM_MS_POWER_PARAMS *msParams = &msg.u.dcmMsg.u.chanActiv.msParams;
    TM_PHYSICAL_CONTEXT *phyCnxt = &msg.u.dcmMsg.u.chanActiv.phyContext;
    TM_SACCH_INFO *sacchInfo = &msg.u.dcmMsg.u.chanActiv.sacchInfo;
    TM_MULTIRATE_CONFIG *mrConfig = &msg.u.dcmMsg.u.chanActiv.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.chanActiv.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.chanActiv.codecTypes; 
    ITS_INT len = 0, ret = 0, i, j;
    ITS_OCTET buffer[200];

    /* fill up Channel Activation  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Activation Type */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Activation Type */
    chanActiv->actType   = 0x05;
    chanActiv->procedure = 0x00;
    
    /* Channel Mode */
    chnlMode->length      = 0xff;
    chnlMode->dtxd        = 0x01;
    chnlMode->dtxu        = 0x01;
    chnlMode->indicator   = 0x03;
    chnlMode->rateAndType = 0xff;
    chnlMode->codingAlg   = 0xab;

    if (chnlMode->indicator == TM_CM_DATA)
    {
        printf("rate          : %02x\n", chnlMode->rate);
        printf("service       : %02x\n", chnlMode->service);
    }
    
    /* Initialise optional bit map */
    CLEAR_TM_DCM_CA_OPTIONAL_BIT_MAP((&msg));

    /* Channel Identification */
    SET_TM_DCM_CA_CHANNEL_ID((&msg));
    chnlId->length  = 0x0a;
    chnlId->descLen = 0x05;
    for(i = 0; i < chnlId->descLen; i++)
    {
        chnlId->chanlDesc[i] = 0x00;
    }

    chnlId->allocLen = 0x01;
    for(i = 0; i < chnlId->allocLen; i++)
    {
        chnlId->mobAlloc[i] = 0xff;
    }

    /* Encryption Information */
    SET_TM_DCM_CA_ENCRYPT_INFO((&msg));
    encrption->length      = 0x02;
    encrption->algorithmId = 0xff;

    for(i = 0; i< encrption->length; i++)
    {
        encrption->key[i] = 0xff;
    }
    
    /* Handover Reference */
    chanActiv->handRef = 0xff;
    
    /* BS Power */
    SET_TM_DCM_CA_BS_POWER((&msg));
    bsPower->powerLevel = 0x0f;
    bsPower->FPC        = 0x01;
    
    /* MS Power */
    SET_TM_DCM_CA_MS_POWER((&msg));
    msPower->powerLevel = 0x0f;
    msPower->FPC        = 0x00;
    
    /* Timing Advance */
    chanActiv->timingAdv = 0xff;
    
    /* BS Power Parameters */
    SET_TM_DCM_CA_BS_POWER_PARAM((&msg));
    bsParams->length = 0x01;
    for(i = 0; i < bsParams->length ; i++)
    {
        bsParams->powerControl[i]  = 0x00;
    }

    /* MS Power Parameters */
    SET_TM_DCM_CA_MS_POWER_PARAM((&msg));
    msParams->length = 0x01;
    for(i = 0; i < msParams->length ; i++)
    {
        msParams->powerControl[i]  = 0x00;
    }

    /* Physical Context */
    SET_TM_DCM_CA_PHYSICAL_CONTEXT((&msg));
    phyCnxt->length = 0x01;
    for(i = 0; i < phyCnxt->length; i++)
    {
        phyCnxt->content[i] = 0x00;
    }

    /* SACCH Information */
    SET_TM_DCM_CA_SAACH_INFO((&msg));
    sacchInfo->length    = 0xff;
    sacchInfo->numOfMsgs = 0x02;

    /* Allocate memory for msgInfo */
    sacchInfo->msgInfo = 
    (TM_SACCH_MSG_INFO  *)calloc(sacchInfo->length, sizeof(TM_SACCH_MSG_INFO));

    for(i = 0; i < sacchInfo->numOfMsgs ; i++)
    {
        sacchInfo->msgInfo[i].typeOfMsg  = 0xab;
        sacchInfo->msgInfo[i].length     = 0x01;

        for(j = 0; j< sacchInfo->msgInfo[i].length; j++)
        {
            sacchInfo->msgInfo[i].msg[j]  = 0xcd;
        }
    }

    /* UIC */
    SET_TM_DCM_CA_UIC((&msg));
    chanActiv->uicLen  = 0x0f;
    chanActiv->uicInfo = 0x0f;

    /* Main Channel Reference */
    SET_TM_DCM_CA_MAIN_CHANNEL_REF((&msg));
    chanActiv->mainChnlRefTn = 0x07;
    
    /* Multirate Configuration */
    SET_TM_DCM_CA_MULTI_RATE_CONFIG((&msg));
    mrConfig->length = 0x01;
    for(i = 0; i < mrConfig->length; i++)
    {
        mrConfig->content[i] = 0x00;
    }

    /* Multirate Control */
    SET_TM_DCM_CA_MULTI_RATE_CONTROL((&msg));
    mrControl->TFO  = 0x01;
    mrControl->PRE  = 0x01;
    mrControl->RAE  = 0x03;

    /* Supported Codec Types */
    SET_TM_DCM_CA_SUPPORTED_CODEC_TYPES((&msg));
    codecTypes->length        = 0x0a;
    codecTypes->sysId         = 0x00;
    codecTypes->codecList     = 0x08;
    
    codecTypes->MACS[0]       = 0x03;
    codecTypes->TFO_VER[0]    = 0x03;
    codecTypes->MACS[1]       = 0x02;
    codecTypes->TFO_VER[1]    = 0x02;

    codecTypes->SCS[0]        = 0xff;
    codecTypes->SCS[1]        = 0xff;
    codecTypes->prefCodecType = 0xff;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Chanel Activation Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Chanel Activation Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
   }
   free(msg.u.dcmMsg.u.chanActiv.sacchInfo.msgInfo);

   return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeChanActivAck(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    int len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up Channel Activation Acknowledge msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    msg.u.dcmMsg.u.chanActivAck.frameNum = 0xabcd;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Chanel Activation Acknowledge Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Chanel Activation Acknowledge Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    } 
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeChanActivNAck(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_CHAN_ACTIV_NACK *chanActivNack = &msg.u.dcmMsg.u.chanActivNack;
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up Channel Activation Negative Acknowledge msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
     
    chanActivNack->length   = 0x05;
    chanActivNack->causeVal = 0xff;
    for(i = 0; i < chanActivNack->length; i++)
    {
        chanActivNack->diagnostics[i] = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Chanel Activation Negative Acknowledge Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Chanel Activation Negative Acknowledge Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeDeactivSaach(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Deactivate SACCH  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Deactivate SACCH Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Deactivate SACCH Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        } 
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeEncrCmd(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_ENCRYPTION_INFO *encrption = &msg.u.dcmMsg.u.encrCmd.encryption;
    TM_LINK_IDENTIFIER *linkId = &msg.u.dcmMsg.u.encrCmd.linkId;
    TM_L3_INFORMATION *l3Info = &msg.u.dcmMsg.u.encrCmd.l3Info;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Encryption Command  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    linkId->SAPI      = 0x07;
    linkId->priority  = 0x03;
    linkId->chanlBits = 0x03;
    linkId->NA        = 0x01;

    encrption->length      = 0x03;
    encrption->algorithmId = 0xff;
    for(i = 0 ; i < encrption->length ; i++)
    {
        encrption->key[i] = 0xff;    
    }

    l3Info->lengthInd  = 0x0002;
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        l3Info->LLSDU[i]  = 0xff;  
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Encryption Command Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Encryption Command Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeHandODet(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up HandOver Detection  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map */ 
    CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP((&msg));

    /* Access Delay */
    SET_TM_DCM_HD_ACCESS_DELAY((&msg));
    msg.u.dcmMsg.u.handoDet.accessDelay  = 0xff;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding HandOver Detection  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding HandOver Detection Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeMeasRes(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_UPLINK_MEAS *uplinkMeas = &msg.u.dcmMsg.u.measRes.uplinkMeas;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.measRes.bsPower;
    TM_L1_INFORMATION *l1Info = &msg.u.dcmMsg.u.measRes.l1Info;
    TM_L3_INFORMATION *l3Info = &msg.u.dcmMsg.u.measRes.l3Info;
    TM_DCM_MEAS_RES *measRes = &msg.u.dcmMsg.u.measRes;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Measurement Result  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    measRes->measResultNum = 0xff;

    uplinkMeas->length       = 0x04;
    uplinkMeas->rxlevFullUp  = 0x3f;
    uplinkMeas->rxlevSubUp   = 0x2f;
    uplinkMeas->rxqualFullUp = 0x01;
    uplinkMeas->rxqualSubUp  = 0x07;
    uplinkMeas->rfu          = 0x01;
    uplinkMeas->dtxd         = 0x01;
    for(i = 0; i < uplinkMeas->length; i++)
    {
        uplinkMeas->SMI[i]  = 0xff;
    }

    bsPower->powerLevel = 0x0f;
    bsPower->FPC        = 0x01;

    /* Initialise optional bit map */
    CLEAR_TM_DCM_MR_OPTIONAL_BIT_MAP((&msg));

    /* L1 Information */
    SET_TM_DCM_MR_L1_INFO((&msg));
//    l1Info->len         = 0x06;
    l1Info->powerLevel  = 0x1f;
    l1Info->timingAdvns = 0xff;
    l1Info->FPC         = 0x01;
    
    /* L3 Information */
    SET_TM_DCM_MR_L3_INFO((&msg));
    l3Info->lengthInd = 0x01;
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        l3Info->LLSDU[i] = 0xff;
    }

    /* MS Timing Offset */
    SET_TM_DCM_MR_MS_TIMING_OFFSET((&msg));
    measRes->timingOffset  = 0x3f;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Measurement Result Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Measurement Result Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeModeModifyReq(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CHANNEL_MODE *chnlMode = &msg.u.dcmMsg.u.modeModifyReq.chnlMode;
    TM_ENCRYPTION_INFO *encrption = &msg.u.dcmMsg.u.modeModifyReq.encryption;
    TM_DCM_MODE_MODIFY_REQ *modeModifyReq = &msg.u.dcmMsg.u.modeModifyReq;
    TM_MULTIRATE_CONFIG *mrConfig = &msg.u.dcmMsg.u.modeModifyReq.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.modeModifyReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.modeModifyReq.codecTypes;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Mode Modify  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    chnlMode->length      = 0x04;
    chnlMode->dtxd        = 0x01;    
    chnlMode->dtxu        = 0x01;
    chnlMode->indicator   = 0x04;
    chnlMode->rateAndType = 0xff;
    chnlMode->codingAlg   = 0xff;

    if (chnlMode->indicator == TM_CM_DATA)
    {
        printf("rate          : %02x\n", chnlMode->rate);
        printf("service       : %02x\n", chnlMode->service);
    }

    /* Initialise optional bit map */
    CLEAR_TM_DCM_MM_OPTIONAL_BIT_MAP((&msg));

    /* Encryption Information */
    SET_TM_DCM_MM_ENCRYPT_INFO((&msg));
    encrption->length      = 0x02;
    encrption->algorithmId = 0xab;
    for(i = 0; i < encrption->length; i++)
    {
        encrption->key[i] = 0xcd;
    }

    /* Main Channel Reference */
    SET_TM_DCM_MM_MAIN_CHANNEL_REF((&msg));
    modeModifyReq->mainChnlRefTn = 0x07;
    
    /* Multirate Configuration */
    SET_TM_DCM_MM_MULTI_RATE_CONFIG((&msg));
    mrConfig->length  = 0x04;
    for(i = 0; i < mrConfig->length; i++)
    {
        mrConfig->content[i] = 0xff;
    }

    /* Multirate Control */
    SET_TM_DCM_MM_MULTI_RATE_CONTROL((&msg));
    mrControl->TFO = 0x01;
    mrControl->PRE = 0x01;
    mrControl->RAE = 0x03;

    /* Supported Codec types */
    SET_TM_DCM_MM_SUPPORTED_CODEC_TYPES((&msg));
    codecTypes->length        = 0xab;
    codecTypes->sysId         = 0xcd;
    codecTypes->codecList     = 0x08;
    codecTypes->MACS[0]       = 0x03;
    codecTypes->TFO_VER[0]    = 0x03;
    codecTypes->MACS[1]       = 0x03;
    codecTypes->TFO_VER[1]    = 0x03;
    codecTypes->SCS[0]        = 0xab;
    codecTypes->SCS[1]        = 0xcd;
    codecTypes->prefCodecType = 0xef;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Mode Modify  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Mode Modify Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodePhyContextConf(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.phyContextConf.bsPower;
    TM_MS_POWER *msPower = &msg.u.dcmMsg.u.phyContextConf.msPower;
    TM_PHYSICAL_CONTEXT *phyCnxt = &msg.u.dcmMsg.u.phyContextConf.phyContext;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Physical Context Confirm  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* BS Power */
    bsPower->powerLevel = 0x0f;
    bsPower->FPC        = 0x00;
    
    /* MS Power */
    msPower->powerLevel = 0x0f;
    msPower->FPC        = 0x00;
    
    /* Timing Advance */
    msg.u.dcmMsg.u.phyContextConf.timingAdv = 0xff;
    
    /* Initialise optional bit map */
    CLEAR_TM_DCM_PCC_OPTIONAL_BIT_MAP((&msg));

    /* Physical Context */
    SET_TM_DCM_PCC_PHYSICAL_CONTEXT((&msg));    
    phyCnxt->length = 0x01;
    for(i = 0; i < phyCnxt->length; i++)
    {   
        phyCnxt->content[i] = 0xff;
    }
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Physical Context Confirm  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Physical Context Confirm Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeMsPowerControl(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MS_POWER *msPower = &msg.u.dcmMsg.u.mspowerControl.msPower;
    TM_MS_POWER_PARAMS *msParams = &msg.u.dcmMsg.u.mspowerControl.msParams;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up MS Power Control  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    /* MS Power */
    msPower->powerLevel = 0x1f;
    msPower->FPC        = 0x01;

    /* Initialise optional bit map */
    CLEAR_TM_DCM_MPC_OPTIONAL_BIT_MAP((&msg));

    /* MS Power parameters */
    SET_TM_DCM_MPC_MS_POWER_PARAMS((&msg));
    msParams->length  = 0x03;
    for(i = 0; i < msParams->length; i++)
    {
        msParams->powerControl[i] = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding MS Power Control Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding MS Power Control Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
             printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeBsPowerControl(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.bspowerControl.bsPower;
    TM_BS_POWER_PARAMS *bsParams = &msg.u.dcmMsg.u.bspowerControl.bsParams;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up BS Power Control  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    bsPower->powerLevel = 0x0f;
    bsPower->FPC        = 0x01;

    /* Initialise optional bit map */
    CLEAR_TM_DCM_BPC_OPTIONAL_BIT_MAP((&msg));

    /* BS Parameters */
    SET_TM_DCM_BPC_BS_POWER_PARAMS((&msg));
    bsParams->length = 0x02;
    for(i = 0; i < bsParams->length; i++)
    {
        bsParams->powerControl[i] = 0xee;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding BS Power Control Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding BS Power Control Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodePreprocConfig(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_PREPROC_CONFIG *preprocConfig = &msg.u.dcmMsg.u.preprocConfig;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Preprocess Configure msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    preprocConfig->length = 0x05;
    for(i = 0; i < preprocConfig->length; i++)
    {
        preprocConfig->processParam[i] = 0xff;
    } 
    preprocConfig->procedure = 0x01;       

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Preprocess Configure Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Preprocess Configure Success  ret :: %d\n\n", ret);
        /* display buffer */
        for (i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodePreproceMeasRes(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_PREPOC_MEAS_RES *prepocMeasRes = &msg.u.dcmMsg.u.prepocMeasRes;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Preprocessed Measurement Result msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    prepocMeasRes->length = 0x00;
    for(i = 0; i < prepocMeasRes->length; i++)
    {
        prepocMeasRes->processMeas[i] = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Preprocessed Measurement Result  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Preprocessed Measurement Result  Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
             printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeSacchInfoModify(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_SACCH_INFO_MOD *sacchInfoMod = &msg.u.dcmMsg.u.sacchInfoMod;
    TM_L3_INFORMATION *l3Info = &msg.u.dcmMsg.u.sacchInfoMod.l3Info;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up SACCH Info Modify msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    sacchInfoMod->sysInfoType = 0xff;
 
    /* Initialise optional bit map */
    CLEAR_TM_DCM_SIM_OPTIONAL_BIT_MAP((&msg));
    
    /* L3 Info */
    SET_TM_DCM_SIM_L3_INFO((&msg));
    l3Info->lengthInd = 0x0002;
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        l3Info->LLSDU[i] = 0xff;
    }

    /* Starting Time */
    SET_TM_DCM_SIM_STARTING_TIME((&msg));
    sacchInfoMod->startingTime = 0xabcd;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SACCH Info Modify  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding SACCH Info Modify  Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeRemotCodecConfRep(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CODEC_CONFIG *config = &msg.u.dcmMsg.u.remoteCodecConfRep.config;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes; 
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Remote Codec Configuration Report msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    } 
 
    /* Codec Configuration */
    config->length    = 0x01;
    config->codecType = 0x04;
    config->ICM       = 0x03;   
    config->codecSet  = 0xff;
    
    /* Supported Codec Types */
    codecTypes->length        = 0x05;
    codecTypes->sysId         = 0xff;
    codecTypes->codecList     = 0x18;
    codecTypes->MACS[0]       = 0x03;
    codecTypes->TFO_VER[0]    = 0x03;
    codecTypes->MACS[1]       = 0x03;
    codecTypes->TFO_VER[1]    = 0x03;
    codecTypes->SCS[0]        = 0xff;
    codecTypes->SCS[1]        = 0xff;
    codecTypes->prefCodecType = 0xff;
    
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
         printf("Encoding  Remote Codec Configuration Report  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  Remote Codec Configuration Report Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
             printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeRTDRep(int choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_RTD_REP *rtdRep = &msg.u.dcmMsg.u.rtdRep;
    int len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Round Trip Delay Report msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    rtdRep->RTD   = 0x7f;
    rtdRep->delay = 0x01;
 
    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
         printf("Encoding Round Trip Delay Report  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  Round Trip Delay Report Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodePreHandONotif(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.preHandoNotif.mrControl;
    TM_CODEC_CONFIG *config = &msg.u.dcmMsg.u.preHandoNotif.config;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Pre_HandOver Notification  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    config->length    = 0x01;
    config->codecType = 0x03;
    config->ICM       = 0x03;
    config->codecSet  = 0xff;
 
    mrControl->TFO = 0x01;
    mrControl->PRE = 0x01;
    mrControl->RAE = 0x03; 

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
         printf("Encoding  Pre_HandOver Notification  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Pre_HandOver Notification  Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeMCodecModReq(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MULTIRATE_CONFIG *mrConfig = &msg.u.dcmMsg.u.mrCodecModReq.mrConfig;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up Multirate Codec Modification Request  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map */
    CLEAR_TM_DCM_MCMR_OPTIONAL_BIT_MAP((&msg));

    /* Multirate Configuration */
    SET_TM_DCM_MCMR_MULTI_RATE_CONFIG((&msg));
    mrConfig->length = 0x02;
    for(i = 0; i < mrConfig->length; i++)
    {
        mrConfig->content[i] = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding  Multirate Codec Modification Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  Multirate Codec Modification Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeTfoRep(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up TFO Report  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    msg.u.dcmMsg.u.tfoRep.tfoStatus  = 0x01;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
         printf("Encoding  TFO Report  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding TFO Report  Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_encodeTfoModReq(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.tfoModReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.tfoModReq.codecTypes; 
    ITS_INT len = 0, ret = 0, i;
    ITS_OCTET buffer[100];

    /* fill up TFO Modification Request  msg */
    ret = encodeCommonDcmElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }    

    mrControl->TFO = 0x01;
    mrControl->PRE = 0x01;
    mrControl->RAE = 0x03;

    /* Initialise optional bit map */
    CLEAR_TM_DCM_TMR_OPTIONAL_BIT_MAP((&msg));

    /* Supported Codec Types*/
    SET_TM_DCM_TMR_SUPPORTED_CODEC_TYPE((&msg));
    codecTypes->length        = 0x06;
    codecTypes->sysId         = 0xff;
    codecTypes->codecList     = 0x00;
    codecTypes->MACS[0]       = 0x03;
    codecTypes->TFO_VER[0]    = 0x03;
    codecTypes->MACS[1]       = 0x03;
    codecTypes->TFO_VER[1]    = 0x03;
    codecTypes->SCS[0]        = 0xff;
    codecTypes->SCS[1]        = 0xff;
    codecTypes->prefCodecType = 0xff;

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
         printf("Encoding  TFO Modification Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding TFO Modification Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_LCS_encodeLocInfo(ITS_INT choice)
{
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_LCS_LOC_INFO *lcsLocInfo = &msg.u.lcsMsg.u.lcsLocInfo; 
    ITS_INT len = 0, ret = 0, i,j;
    ITS_OCTET buffer[100];

    /* fill up Location Information  msg */
    ret = encodeCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    lcsLocInfo->length = 0x01;
    for(i = 0; i < lcsLocInfo->length; i++)
    {
        lcsLocInfo->facIEI[i] = 0xff;
    }

    len = sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG);
    ret = ABIS_TMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Location Information Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Location Information success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i = 0; i < len; i++)
        {
            printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
decodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    TM_MSG_DESCRIMINATOR *msgDesc = &msg->genElemnts.msgDesc;

    printf("msgTransp : %02x\n", msgDesc->trasparent) ;
    printf("msgGroup  : %02x\n", msgDesc->msgGruop) ;
    printf("msgType   : %02x\n", msg->genElemnts.msgType);

    return ITS_SUCCESS;
}

static ITS_INT
decodeCommonRllmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.rllmMsg.rllmGenElements.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.rllmMsg.rllmGenElements.linkId;

    ret = decodeCommonElements(msg);
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
decodeCommonDcmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.dcmMsg.dcmGenElements.chanlNum;

    ret = decodeCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("timeSlotNum : %02x\n", chanlNum->timeSlotNum);
    printf("chanlBits   : %02x\n", chanlNum->chanlBits);
    
    return ITS_SUCCESS;
}

static ITS_INT
decodeCommonCcmElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg)
{
    ITS_INT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum;

    ret = decodeCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("timeSlotNum : %02x\n", chanlNum->timeSlotNum);
    printf("chanlBits   : %02x\n", chanlNum->chanlBits);
                                                                                                                             
    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_decodeDataReq(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_L3_INFORMATION *l3Info = &msg.u.rllmMsg.u.dataReq.l3Info;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x02, 0xff, 0x0b, 0x00,
                             0x01, 0xcd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                             0xff, 0xff, 0xff, 0xff 
                            };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Data Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    { 
        printf("Decoding Data Request Success  ret :: %d\n", ret);
    }

    /* display Data Request message*/
    ret = decodeCommonRllmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                           
    printf("lengthInd   : %04x\n", l3Info->lengthInd);
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_decodeErrorInd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_RLLM_ERROR_IND *errorInd = &msg.u.rllmMsg.u.errorInd;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x02, 0xff, 0x16, 0xff,
                             0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                             0xff, 0xff, 0xff
                            };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Error Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Error Indication Success  ret :: %d\n", ret);
    }

    /* display Error Indication message*/
    ret = decodeCommonRllmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("RLM length   : %02x\n", errorInd->rlmLen);
    printf("RLM Clause   : %02x\n", errorInd->causeVal);

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_decodeEstaReq(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x02, 0xff, 0x0b, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                            };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Establish Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Establish Request Success  ret :: %d\n", ret);
    }

    /* display Establish Request message*/
    ret = decodeCommonRllmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_decodeEstaInd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_L3_INFORMATION *l3Info = &msg.u.rllmMsg.u.estInd.l3Info;  
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x02, 0xff, 0x0b, 0x00,
                             0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Establish Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Establish Indication Success  ret :: %d\n", ret);
    }

    /* display Establish Indication message*/
    ret = decodeCommonRllmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    if (IS_PRESENT_TM_RLLM_EI_L3_INFO((&msg)))
    {
        printf("lengthInd   : %04x\n", l3Info->lengthInd);
        for(i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_RLLM_decodeRelReq(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x02, 0xff, 0x14, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };
    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Release Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Release Request Success  ret :: %d\n", ret);
    }

    /* display Release Request message*/
    ret = decodeCommonRllmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Mode bit   : %02x\n", msg.u.rllmMsg.u.relReq.modeBit);
                                                                                                                             
    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeBcchInfo(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_BCCH_INFO *bcchInfo = &msg.u.ccmMsg.u.bcchInfo;
    TM_FULL_BCCH_INFO *fullBcch = &msg.u.ccmMsg.u.bcchInfo.fullBcch;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x1e, 0xff, 0x27, 0x01,
                             0xff, 0x17, 0xab, 0xab, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding BCCH Information Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding BCCH Information Success  ret :: %d\n", ret);
    }

    /* display BCCH Information message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Sys Info type   : %02x\n", bcchInfo->sysInfoType);
    
    if (IS_PRESENT_TM_CCM_BI_FULL_BCCH_INFO((&msg)))
    {
        printf("FB Length Ind   : %02x\n", fullBcch->length);
        for(i = 0; i < fullBcch->length; i++)
        {
            printf("FB msg[%d]  : %02x\n", i, fullBcch->msg[i]);
        }
    }

    if (IS_PRESENT_TM_CCM_BI_STARTING_TIME((&msg)))
    {
        printf("Starting time : %04x\n", bcchInfo->startingTime);        
    }                                                                                                                

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeCcchLoadInd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_RACH_LOAD *rach = &msg.u.ccmMsg.u.ccchLoadInd.rach;
    TM_CHANNEL_NUMBER *chanlNum = &msg.u.ccmMsg.ccmGenElements.chanlNum;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0x8f, 0x12, 0x07, 0x12, 0x34,
                             0x56, 0x78, 0xab, 0xcd, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding CCCH Load Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding CCCH Load Indication Success  ret :: %d\n", ret);
    }

    /* display CCCH Load Indication message*/
    ret = decodeCommonCcmElements(&msg);
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
        for(i = 0; i < (rach->length-6); i++)
        {
            printf("RACH Info[%d] : %02x\n", i, rach->info[i]);
        }
    }

    if (chanlNum->chanlBits == TM_CN_DOWNLINK_CCCH)
    {
        printf("PageBufSpace : %02x\n", msg.u.ccmMsg.u.ccchLoadInd.pagBufSpace);
    } 

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeChanRqd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_CHAN_RQD *chanRqd = &msg.u.ccmMsg.u.chanRqd;
    TM_PHYSICAL_CONTEXT *phyContext = &msg.u.ccmMsg.u.chanRqd.phyContext;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x13, 0xff, 0x12, 0x34,
                             0x11, 0xff, 0x10, 0x01, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Chaneel Required Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Chaneel Required Success  ret :: %d\n", ret);
    }

    /* display Chaneel Required message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("chanRqdRA   : %02x\n", chanRqd->RA);
    printf("reqRefNum   : %02x\n", chanRqd->reqRefNum);
    printf("accessDelay : %02x\n", chanRqd->accessDelay);

    if (IS_PRESENT_TM_CCM_CR_PHYSICAL_CONTEXT((&msg)))
    {
        printf("PC Length   : %02x\n", phyContext->length);
        for(i = 0; i < phyContext->length; i++)
        {
            printf("PC Content[%d] : %02x\n", i, phyContext->content[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeDeleteInd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_DELETE_IND *deleteInd = &msg.u.ccmMsg.u.deleteInd; 
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x2b, 0x05, 0xff, 0xff,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Delete Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Delete Indication Success  ret :: %d\n", ret);
    }

    /* display Delete Indication message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("DelInd Length   : %02x\n", deleteInd->length);
    for(i = 0; i < deleteInd->length; i++)
    {
        printf("AssignInfo[%d] : %02x\n", i, deleteInd->assignInfo[i]);
    }

    return ITS_SUCCESS;
}
                                                                                                                            
static ITS_INT
TM_CCM_decodePagingCmd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_PAGING_CMD *pagingCmd = &msg.u.ccmMsg.u.pagingCmd;
    TM_MS_IDENTITY *msIdentity = &msg.u.ccmMsg.u.pagingCmd.msIdentity;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x0e, 0xff, 0x0c, 0x02,
                             0xff, 0xff, 0x28, 0x03, 0x33, 0x07
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Paging Command Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Paging Command Success  ret :: %d\n", ret);
    }

    /* display Paging Command message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Paging Group : %02x\n", pagingCmd->pagingGroup);
    printf("MSI length   : %02x\n", msIdentity->length);
    for(i = 0; i < msIdentity->length; i++)
    {
        printf("Identity[%d] : %02x\n", i, msIdentity->identity[i]);
    }

    if (IS_PRESENT_TM_CCM_PC_CHANNEL_NEEDED((&msg)))
    {
        printf("Chanl Need   : %02x\n", pagingCmd->chanlNeed);
    }

    if (IS_PRESENT_TM_CCM_PC_EMLPP_PRIORITY((&msg)))
    {
        printf("CallPriority : %02x\n", pagingCmd->callPriority);                                              
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeSmsBCReq(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_SMS_BC_REQ *smsBcReq = &msg.u.ccmMsg.u.smsBcReq;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0x8f, 0x24, 0xff, 0xff, 0xff,
                             0x2e, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SMS Broadcast Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding SMS Broadcast Request Success  ret :: %d\n", ret);
    }

    /* display SMS Broadcast Request message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("SmscbInfoLen : %02x\n", smsBcReq->smscbInfoLen);
    for(i = 0; i < smsBcReq->smscbInfoLen; i++)
    {
        printf("SmscbIfo[%d] : %02x\n", i, smsBcReq->smscbInfo[i]);
    }

    if (IS_PRESENT_TM_CCM_SBR_SMSCB_CHANNEL_IND((&msg)))
    {
        printf("ChanlInd : %02x\n", smsBcReq->chanlInd);
    }
                                                                                                                             
    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_decodeRfReInd(ITS_INT choice)
{
    ITS_INT ret, i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_TRAX_RF_RES_IND *rfResInd = &msg.u.trxmMsg.u.rfResInd;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x15, 0x04, 0xff, 0xc0, 0xff, 0xe0,
                             0x0b, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding RF Resource Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding RF Resource Indication Success  ret :: %d\n", ret);
    }

    /* display RF Resource Indication message*/
    ret = decodeCommonElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Length   : %02x\n", rfResInd->length);
    for(i = 0; i < (rfResInd->length/2); i++)
    {
        printf("CNTimeSlotNum[%d]: %02x\n", i, rfResInd->info[i].chanlNum.timeSlotNum);
        printf("CNChanlBits[%d]  : %02x\n", i, rfResInd->info[i].chanlNum.chanlBits);  
        printf("InterfBand[%d]   : %02x\n", i, rfResInd->info[i].interfBand);          
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_decodeSacchFill(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_TRAX_SACCH_FILL *sacchFill = &msg.u.trxmMsg.u.sacchFill;
    TM_L3_INFORMATION *l3Info = &msg.u.trxmMsg.u.sacchFill.l3Info;
    ITS_OCTET buffer[50] = {0xf0, choice, 0x1e, 0xff, 0x0b, 0x00, 0x02, 0xff, 0xff,
                            0x17, 0xab, 0xcd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SACCH Filling Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding SACCH Filling Success  ret :: %d\n", ret);
    }

    /* display SACCH Filling message*/
    ret = decodeCommonElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }   
    printf("SysInfoType   : %02x\n", sacchFill->sysInfoType);

    if (IS_PRESENT_TM_TRXM_SF_L3_INFO((&msg)))
    { 
        printf("L3InfoLenInd  : %02x\n", l3Info->lengthInd);
        for(i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDu[%d]  : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    if (IS_PRESENT_TM_TRXM_SF_STARTING_TIME((&msg)))
    {
        printf("StartingTime  : %02x\n", sacchFill->startingTime);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_decodeOverload(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_TRAX_OVERLOAD *overload = &msg.u.trxmMsg.u.overload;
    ITS_OCTET buffer[20] = {0xf0, choice, 0x1a, 0x03, 0x0f, 0xff, 0xff, 0xff,
                            0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Overload Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Overload Success  ret :: %d\n", ret);
    }   

    /* display Overload  message*/
    ret = decodeCommonElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
           
    printf("Overload Length : %02x\n", overload->length);
    printf("Cause Value     : %02x\n", overload->causeVal);
    for(i = 0; i < overload->length; i++)
    {
        printf("diagnostics[%d] : %02x\n", i, overload->diagnostics[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_TRXM_decodeErrorReport(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CAUSE *cause = &msg.u.trxmMsg.u.errorReport.cause;
    TM_CHANNEL_NUMBER *chanlNum = &msg.u.trxmMsg.u.errorReport.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg.u.trxmMsg.u.errorReport.linkId;
    TM_ERRONEOUS_MSG *errMsg = &msg.u.trxmMsg.u.errorReport.errMsg;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x1a, 0x03, 0x7f, 0xff, 0xff, 0x1c,
                             0xff, 0x01, 0xff, 0x02, 0xff, 0x26, 0x03, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Error Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding  Error Report Success  ret :: %d\n", ret);
    }
    /* display  Error Report message*/
    ret = decodeCommonElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                             
    printf("Cause Length : %02x\n", cause->length);
    printf("Cause Value  : %02x\n", cause->causeVal);
    for(i = 0; i < cause->length; i++)
    {
        printf("Diagnostics[%d]  : %02x\n", i, cause->diagnostics[i]);
    }

    if (IS_PRESENT_TM_TRXM_ER_MESSAGE_IDENTIFIER((&msg)))
    {
        printf("MsgId       : %02x\n", msg.u.trxmMsg.u.errorReport.msgId);
    }

    if (IS_PRESENT_TM_TRXM_ER_CHANNEL_NUMBER((&msg)))
    {
        printf("timeSlotNum : %02x\n", chanlNum->timeSlotNum);
        printf("Chanl Bits  : %02x\n", chanlNum->chanlBits);
    }

    if (IS_PRESENT_TM_TRXM_ER_LINK_IDENTIFIER((&msg)))
    {
        printf("SAPI        : %02x\n", linkId->SAPI);
        printf("Priority    : %02x\n", linkId->priority);
        printf("Chanl Bits  : %02x\n", linkId->chanlBits);
        printf("LinkId NA   : %02x\n", linkId->NA);
    }
   
    if (IS_PRESENT_TM_TRXM_ER_ERRONEOUS_MSG((&msg)))
    {
        printf("ErrMsgLength: %02x\n", errMsg->length);
        for(i = 0; i < errMsg->length; i++)
        {
            printf("recvdMsg[%d]  : %02x\n", i, errMsg->recvdMsg[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeSmsBcCmd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CB_CMD_TYPE *cmdType = &msg.u.ccmMsg.u.smsBcCmd.cmdType;
    TM_SMSCB_MSG *smscbMsg = &msg.u.ccmMsg.u.smsBcCmd.smscbMsg;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x29, 0xf0, 0x2a, 0x03,
                             0xff, 0xff, 0xff, 0x2e, 0x00, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SMS Broadcast Command Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding SMS Broadcast Command Success  ret :: %d\n", ret);
    }

    /* display SMS Broadcast Command message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    printf("Last Block   : %02x\n", cmdType->lastlock);
    printf("Command      : %02x\n", cmdType->command);
    printf("Broadcast    : %02x\n", cmdType->broadcast);
    printf("SMSCB length : %02x\n", smscbMsg->length);
    for(i = 0; i < smscbMsg->length; i++)
    {
        printf("msg[%d] : %02x\n", i,smscbMsg->msg[i]);
    }                                                                                                             

    if (IS_PRESENT_TM_CCM_SBC_SMSCB_CHANNEL_IND((&msg)))
    {
        printf("ChanlInd  : %02x\n", msg.u.ccmMsg.u.smsBcCmd.chanlInd);
    }
                                                                                                                             
    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeCbchLoadInd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CCM_CBCH_LOAD_IND *cbchLoadInd = &msg.u.ccmMsg.u.cbchLoadInd;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x2d, 0x8f, 0x2e, 0x0f,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding CBCH Load Indication Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding CBCH Load Indication Success  ret :: %d\n", ret);
    }

    /* display CBCH Load Indication  message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Slot Count    : %02x\n", cbchLoadInd->slotCount);
    printf("CBCH LoadType : %02x\n", cbchLoadInd->type);

    if (IS_PRESENT_TM_CCM_CLI_SMSCB_CHANNEL_IND((&msg)))
    {
        printf("Chanl Indi    : %02x\n", cbchLoadInd->chanlInd); 
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_CCM_decodeNotiCmd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_COMMAND_IND *cmdInd = &msg.u.ccmMsg.u.notCmd.cmdInd;
    TM_GROUP_CALL_REF *callRef = &msg.u.ccmMsg.u.notCmd.callRef;
    TM_GROUP_CHANNEL_DESC *chanlDesc = &msg.u.ccmMsg.u.notCmd.chanlDesc;
    TM_NCH_DRX_INFO *nchDrx = &msg.u.ccmMsg.u.notCmd.nchDrx;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x32, 0x03, 0x7f, 0x2f,
                             0x01, 0xff, 0x30, 0x02, 0xff, 0xff, 0x31, 0x03,
                             0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Notification Command Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Notification Command Success  ret :: %d\n", ret);
    }

    /* display Notification Command  message*/
    ret = decodeCommonCcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("CmdInd Len    : %02x\n", cmdInd->length);
    printf("CmdVal        : %02x\n", cmdInd->cmdVal);

    if (IS_PRESENT_TM_CCM_NC_GROUP_CALL_REFERENCE((&msg)))
    {
        printf("CallRef len   : %02x\n", callRef->length);
        for (i = 0; i < callRef->length; i++)
        {
            printf("DescGroup[%d] : %02x\n", i, callRef->descGroup[i]);
        }
    }

    if (IS_PRESENT_TM_CCM_NC_CHANNEL_DESCRIPTION((&msg)))
    {
        printf("ChanlDesc len : %02x\n", chanlDesc->length);
        for(i = 0; i < chanlDesc->length; i++)
        {
            printf("ChanlDesc[%d] : %02x\n", i, chanlDesc->chanlDesc[i]);
        }
    }

    if (IS_PRESENT_TM_CCM_NC_NCH_DRX_INFO((&msg)))
    {
        printf("NCHDRX len    : %02x\n", nchDrx->length);
        printf("NCHDRX emlpp  : %02x\n", nchDrx->emlpp); 
        printf("NLN           : %02x\n", nchDrx->NLN);
        printf("Status        : %02x\n", nchDrx->status);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeChanActiv(ITS_INT choice)
{
    ITS_INT ret,i,j;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_CHAN_ACTIV *chanActiv = &msg.u.dcmMsg.u.chanActiv;
    TM_CHANNEL_MODE *chnlMode = &msg.u.dcmMsg.u.chanActiv.chnlMode;
    TM_CHANNEL_ID *chnlId = &msg.u.dcmMsg.u.chanActiv.chnlId;
    TM_ENCRYPTION_INFO *encrption = &msg.u.dcmMsg.u.chanActiv.encryption;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.chanActiv.bsPower;
    TM_MS_POWER *msPower = &msg.u.dcmMsg.u.chanActiv.msPower;
    TM_BS_POWER_PARAMS *bsParams = &msg.u.dcmMsg.u.chanActiv.bsParams;
    TM_MS_POWER_PARAMS *msParams = &msg.u.dcmMsg.u.chanActiv.msParams;
    TM_PHYSICAL_CONTEXT *phyCnxt = &msg.u.dcmMsg.u.chanActiv.phyContext;
    TM_SACCH_INFO *sacchInfo = &msg.u.dcmMsg.u.chanActiv.sacchInfo;
    TM_MULTIRATE_CONFIG *mrConfig = &msg.u.dcmMsg.u.chanActiv.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.chanActiv.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.chanActiv.codecTypes; 
    ITS_OCTET buffer[90] = { 0xf0, choice, 0x01, 0xff, 0x03, 0x05, 0x06, 0x04,
                             0x03, 0x01, 0xff, 0xab, 0x05, 0x06, 0x00, 0x00,
                             0x00, 0x00, 0x00, 0xff, 0x07, 0x02, 0xff, 0xff,
                             0x04, 0x1f, 0x0d, 0x0f, 0x20, 0x01, 0x00, 0x1f,
                             0x01, 0x00, 0x10, 0x01, 0x00, 0x2c, 0x04, 0x01,
                             0xab, 0x01, 0xcd, 0x34, 0x0f, 0x0f, 0x35, 0xff,
                             0x36, 0x01, 0x00, 0x37, 0x0f, 0x38, 0x05, 0x00,
                             0x08, 0x0f, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Chanel Activation Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("\nDecoding Chanel Activation Success  ret :: %d\n", ret);
    }

    /* display Chanel Activation message*/
    ret = decodeCommonDcmElements(&msg);
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
    if (IS_PRESENT_TM_DCM_CA_CHANNEL_IDENTIFIER((&msg)))
    {
        printf("CI Length     : %02x\n", chnlId->length);
    }
        
    /* Encryption Information */
    if (IS_PRESENT_TM_DCM_CA_ENCRYPT_INFO((&msg)))
    {
        printf("EI length     : %02x\n", encrption->length);
        printf("algorithmId   : %02x\n", encrption->algorithmId);
        for(i = 0; i < encrption->length; i++)
        {
            printf("key[%d]        : %02x\n", i, encrption->key[i]);
        }
    } 

    /* Handover Reference */
    printf("HandRef       : %02x\n", chanActiv->handRef);
       
    /* BS Power */
    if (IS_PRESENT_TM_DCM_CA_BS_POWER((&msg)))
    { 
        printf("BsPowLevel    : %02x\n", bsPower->powerLevel);
        printf("FPC           : %02x\n", bsPower->FPC);
    } 

    /* MS Power */
    if (IS_PRESENT_TM_DCM_CA_MS_POWER((&msg)))
    { 
        printf("MsPowLevel    : %02x\n", msPower->powerLevel);
        printf("FPC           : %02x\n", msPower->FPC);
    }
    
    /* Timing Advance */
    printf("timingAdv     : %02x\n", chanActiv->timingAdv);
        
    /* BS Power Parameters */   
    if (IS_PRESENT_TM_DCM_CA_BS_POWER_PARAMS((&msg)))
    { 
        printf("BsParamsLen   : %02x\n", bsParams->length);
        for(i = 0; i < bsParams->length ; i++)
        {
            printf("powerControl[%d]: %02x\n", i, bsParams->powerControl[i]);
        }
    }

    /* MS Power Parameters */
    if (IS_PRESENT_TM_DCM_CA_MS_POWER_PARAMS((&msg)))
    { 
        printf("MsParamsLen   : %02x\n", msParams->length);
        for(i = 0; i < msParams->length ; i++)
        {
            printf("powerControl[%d]: %02x\n", i, msParams->powerControl[i]);
        }
    }

    /* Physical Context */
    if (IS_PRESENT_TM_DCM_CA_PHYSICAL_CONTEXT((&msg)))
    { 
        printf("PhyCnxtLen    : %02x\n", phyCnxt->length);
        for(i = 0; i < phyCnxt->length; i++)
        {
            printf("content[%d]    : %02x\n", i, phyCnxt->content[i]);
        }
    }

    /* SACCH Information */
    if (IS_PRESENT_TM_DCM_CA_SAACH_INFO((&msg)))
    { 
        printf("SacchInflen   : %02x\n", sacchInfo->length);
        printf("NoOfMsgs      : %02x\n", sacchInfo->numOfMsgs);
        for(i = 0; i < sacchInfo->numOfMsgs ; i++)
        {
            printf("msg[%d]Type    : %02x\n", i, sacchInfo->msgInfo[i].typeOfMsg);
            printf("msg[%d]Length  : %02x\n", i, sacchInfo->msgInfo[i].length);
            for(j = 0; j< sacchInfo->msgInfo[i].length; j++)
            {
                printf("msg[%d].mesg[%d]: %02x\n", i, j, sacchInfo->msgInfo[i].msg[j]);
            }
        }
    }

    /* UIC */
    if (IS_PRESENT_TM_DCM_CA_UIC((&msg)))
    { 
        printf("uicLen        : %02x\n", chanActiv->uicLen);
        printf("uicInfo       : %02x\n", chanActiv->uicInfo);
    }
    
    /* Main Channel Referenc */
    if (IS_PRESENT_TM_DCM_CA_MAIN_CHANNEL_REF((&msg)))
    { 
        printf("mainChnlRefTn : %02x\n", chanActiv->mainChnlRefTn);
    }
    
    /* Multirate Configuration */
    if (IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONFIG((&msg)))
    { 
        printf("MrConfLen     : %02x\n", mrConfig->length);
        for(i = 0; i < mrConfig->length ; i++)
        { 
            printf("content[%d]    : %02x\n", i, mrConfig->content[i]);
        }
    }

    /* Multirate Control */
    if (IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONTROL((&msg)))
    { 
        printf("mrControl.TFO : %02x\n", mrControl->TFO);
        printf("mrControl.PRE : %02x\n", mrControl->PRE);
        printf("mrControl.RAE : %02x\n", mrControl->RAE);
    }
    
    /* Supported Codec Types */
    if (IS_PRESENT_TM_DCM_CA_SUPPORTED_CODEC_TYPES((&msg)))
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
TM_DCM_decodeChanActivAck(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x08, 0xcd, 0xab, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Chanel Activation Acknowledge Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Chanel Activation Acknowledge Success  ret :: %d\n", ret);
    }  

    /* display  Chanel Activation Acknowledge  message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Frame Number  : %02x\n", msg.u.dcmMsg.u.chanActivAck.frameNum);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeChanActivNAck(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_CHAN_ACTIV_NACK *chanActivNack = &msg.u.dcmMsg.u.chanActivNack; 
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x1a, 0x05, 0x8f, 0x00,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };
    
    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Chanel Activation Negative Acknowledge Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding  Chanel Activation Negative Acknowledge Success  ret :: %d\n", ret);
    }                                                                                                                       

    /* display  Chanel Activation Negative Acknowledge  message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                  

    printf("Length      : %02x\n", chanActivNack->length);
    printf("Cause Value : %02x\n", chanActivNack->causeVal);
    for(i = 0; i < chanActivNack->length; i++)
    {
        printf("Diagnostics[%d] : %02x\n", i, chanActivNack->diagnostics[i]);
    }      

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeDeactivSaach(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x02, 0xff, 0x0b, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Deactivate SACCH  Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Deactivate SACCH Success  ret :: %d\n", ret);
    }

    /* display  Deactivate SACCH message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                           

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeEncrCmd(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_ENCRYPTION_INFO *encryption = &msg.u.dcmMsg.u.encrCmd.encryption;
    TM_LINK_IDENTIFIER *linkId = &msg.u.dcmMsg.u.encrCmd.linkId;
    TM_L3_INFORMATION *l3Info = &msg.u.dcmMsg.u.encrCmd.l3Info;
    ITS_OCTET buffer[50] = { 0xf0, 0x26, 0x01, 0xff, 0x07, 0x03, 0xff, 0xff,
                             0xff, 0x02, 0xff, 0x0b, 0x00, 0x02, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Encryption Command  Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Encryption Command Success  ret :: %d\n", ret);
    }

    /* display Encryption Command message*/
    ret = decodeCommonDcmElements(&msg);
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
    for(i = 0; i < (encryption->length - 1); i++)
    {
        printf("key[%d] : %02x\n", i, encryption->key[i]);
    }
    printf("LengthInd : %02x\n", l3Info->lengthInd);
    for(i = 0; i < l3Info->lengthInd; i++)
    {
        printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeHandODet(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x11, 0xff, 0x0b, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding HandOver Detection Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding HandOver Detection Success  ret :: %d\n", ret);
    }

    /* display  HandOver Detection message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }      

    if (IS_PRESENT_TM_DCM_HD_ACCESS_DELAY((&msg)))
    {
        printf("Access Dealay : %02x\n", msg.u.dcmMsg.u.handoDet.accessDelay);
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeMeasRes(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_MEAS_RES *measRes = &msg.u.dcmMsg.u.measRes;
    TM_UPLINK_MEAS *uplinkMeas = &msg.u.dcmMsg.u.measRes.uplinkMeas;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.measRes.bsPower;
    TM_L1_INFORMATION *l1Info = &msg.u.dcmMsg.u.measRes.l1Info;
    TM_L3_INFORMATION *l3Info = &msg.u.dcmMsg.u.measRes.l3Info;
    ITS_OCTET buffer[50] = {0xf0, choice, 0x01, 0xff, 0x1b, 0xff, 0x19, 0x05, 0xdf,
                            0x0f, 0x0f, 0xff, 0xff, 0x04, 0x1f, 0x0a, 0xfc, 0xff, 
                            0x0b, 0x00, 0x01, 0xff, 0x25, 0x3f
                           };
    
    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Measurement Result Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Measurement Result Success  ret :: %d\n", ret);
    }

    /* display  Measurement Result message*/
    ret = decodeCommonDcmElements(&msg);
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
    for(i = 0; i < uplinkMeas->length; i++)
    {
        printf("SMI[%d]      : %02x\n", i, uplinkMeas->SMI[i]);
    }

    printf("powerLevel    : %02x\n", bsPower->powerLevel);
    printf("FPC           : %02x\n", bsPower->FPC);

    if (IS_PRESENT_TM_DCM_MR_L1_INFO((&msg)))
    {
//        printf("Length        : %02x\n", l1Info->len);
        printf("powerLevel    : %02x\n", l1Info->powerLevel);
        printf("timingAdvns   : %02x\n", l1Info->timingAdvns);
        printf("FPC           : %02x\n", l1Info->FPC);
    }
 
    if (IS_PRESENT_TM_DCM_MR_L3_INFO((&msg)))
    {
        printf("lengthInd     : %02x\n", l3Info->lengthInd);
        for(i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDU[%d] : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    if (IS_PRESENT_TM_DCM_MR_MS_TIMING_OFFSET((&msg)))
    {
        printf("timingOffset  : %02x\n", measRes->timingOffset);
    }

    return ITS_SUCCESS;
}
  
static ITS_INT
TM_DCM_decodeModeModifyReq(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CHANNEL_MODE *chnlMode = &msg.u.dcmMsg.u.modeModifyReq.chnlMode;
    TM_ENCRYPTION_INFO *encrption = &msg.u.dcmMsg.u.modeModifyReq.encryption;
    TM_DCM_MODE_MODIFY_REQ *modeModifyReq = &msg.u.dcmMsg.u.modeModifyReq;
    TM_MULTIRATE_CONFIG *mrConfig = &msg.u.dcmMsg.u.modeModifyReq.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.modeModifyReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.modeModifyReq.codecTypes;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x06, 0x04, 0x03, 0x04,
                             0xff, 0x00, 0x07, 0x02, 0xab, 0xcd, 0x35, 0x07, 0x36,
                             0x04, 0xff, 0xff, 0xff, 0xff, 0x37, 0x0f, 0x38,
                             0x05, 0xcd, 0x08, 0x0f, 0xab, 0xef
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Mode Modify Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Mode Modify Success  ret :: %d\n", ret);
    }
    /* display Mode Modify message*/
    ret = decodeCommonDcmElements(&msg);
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
    if (IS_PRESENT_TM_DCM_MM_ENCRYPT_CHANNEL((&msg)))
    {
        printf("length        : %02x\n", encrption->length);
        printf("algorithmId   : %02x\n", encrption->algorithmId);
        for(i = 0; i < encrption->length; i++)
        {
            printf("key[%d]     : %02x\n", i, encrption->key[i]);
        }
    }

    /* Main Channel Reference */
    if (IS_PRESENT_TM_DCM_MM_MAIN_CHANNEL_REF((&msg)))
    {
        printf("mainChnlRefTn : %02x\n", modeModifyReq->mainChnlRefTn);
    }
        
    /* Multirate Configuration */
    if (IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONFIG((&msg)))
    {
        printf("length        : %02x\n", mrConfig->length);
        for(i = 0; i < mrConfig->length; i++)
        {
            printf("content[%d]   : %02x\n", i, mrConfig->content[i]);
        }
    }

    /* Multirate Control */
    if (IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONTROL((&msg)))
    {
        printf("TFO           : %02x\n", mrControl->TFO);
        printf("PRE           : %02x\n", mrControl->PRE);
        printf("RAE           : %02x\n", mrControl->RAE);
    }
        
    /* Supported Codec types */
    if (IS_PRESENT_TM_DCM_MM_SUPPORTED_CODEC_TYPES((&msg)))
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
TM_DCM_decodePhyContextConf(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.phyContextConf.bsPower;
    TM_MS_POWER *msPower = &msg.u.dcmMsg.u.phyContextConf.msPower;
    TM_PHYSICAL_CONTEXT *phyContext = &msg.u.dcmMsg.u.phyContextConf.phyContext; 
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x04, 0x0f, 0x0d, 0x0f,
                             0x18, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                          };
        
    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Physical Context Confirm Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Physical Context Confirm Success  ret :: %d\n", ret);
    }

    /* display Physical Context Confirm message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("BS Power Level : %02x\n", bsPower->powerLevel);
    printf("FPC            : %02x\n", bsPower->FPC);
    printf("MS Power Level : %02x\n", msPower->powerLevel);
    printf("FPC            : %02x\n", msPower->FPC);

    printf("TimingAdv      : %02x\n", msg.u.dcmMsg.u.phyContextConf.timingAdv);

    if (IS_PRESENT_TM_DCM_PCC_PHYSICAL_CONTEXT((&msg)))
    {
        printf("Length         : %02x\n", phyContext->length);
        for(i = 0; i < phyContext->length; i++)
        {
            printf("Content[%d]  : %02x\n", i, phyContext->content[i]);
        }
    }

    return ITS_SUCCESS;
}
  
static ITS_INT
TM_DCM_decodeMsPowerControl(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MS_POWER *msPower = &msg.u.dcmMsg.u.mspowerControl.msPower;
    TM_MS_POWER_PARAMS *msParams = &msg.u.dcmMsg.u.mspowerControl.msParams;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x0d, 0xff, 0x1f, 0x03,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
                           };
    
    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding MS Power Control Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding MS Power Control Success  ret :: %d\n", ret);
    }

    /* display MS Power Control message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Power Level : %02x\n", msPower->powerLevel);
    printf("FPC         : %02x\n", msPower->FPC);       

    if (IS_PRESENT_TM_DCM_MPC_MS_POWER_PARAMS((&msg)))
    {
        printf("Length      : %02x\n", msParams->length);
        for(i = 0; i < msParams->length; i++)
        {
            printf("powerControl[%d] : %02x\n", i, msParams->powerControl[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeBsPowerControl(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_BS_POWER *bsPower = &msg.u.dcmMsg.u.bspowerControl.bsPower;
    TM_BS_POWER_PARAMS *bsParams = &msg.u.dcmMsg.u.bspowerControl.bsParams;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x04, 0xff, 0x20, 0x03,
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding BS Power Control Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding BS Power Control Success  ret :: %d\n", ret);
    }

    /* display BS Power Control message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Power Level  : %02x\n", bsPower->powerLevel);
    printf("FPC          : %02x\n", bsPower->FPC);

    if (IS_PRESENT_TM_DCM_BPC_BS_POWER_PARAMS((&msg)))
    {
        printf("Length       : %02x\n", bsParams->length);
        for(i = 0; i < bsParams->length; i++)
        {
           printf("powerControl[%d] : %02x\n", i, bsParams->powerControl[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodePreprocConfig(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_PREPROC_CONFIG *preprocConfig = &msg.u.dcmMsg.u.preprocConfig;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x21, 0x08, 0x01, 
                             0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Preprocess Configure Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Preprocess Configure Success  ret :: %d\n", ret);
    }

    /* display Preprocess Configure message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("Length  : %02x\n", preprocConfig->length);
    for(i = 0; i < preprocConfig->length; i++)
    {
        printf("processParam[%d]  : %02x\n", i, preprocConfig->processParam[i]);
    }
    printf("Procedure  : %02x\n", preprocConfig->procedure);

    return ITS_SUCCESS;
}
 
static ITS_INT
TM_DCM_decodePreproceMeasRes(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_PREPOC_MEAS_RES *prepocMeasRes = &msg.u.dcmMsg.u.prepocMeasRes;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x22, 0x04, 0xab, 0xcd,
                             0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Preprocessed Measurement Result Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Preprocessed Measurement Result Success  ret :: %d\n", ret);
    }

    /* display Preprocessed Measurement Result message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Length  : %02x\n", prepocMeasRes->length);
    for(i = 0; i < prepocMeasRes->length; i++)
    {
        printf("processMeas[%d]  : %02x\n", i, prepocMeasRes->processMeas[i]);
    }

    return ITS_SUCCESS;
}  

static ITS_INT
TM_DCM_decodeSacchInfoModify(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_SACCH_INFO_MOD *sacchInfoMod = &msg.u.dcmMsg.u.sacchInfoMod;
    TM_L3_INFORMATION *l3Info = &msg.u.dcmMsg.u.sacchInfoMod.l3Info; 
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x1e, 0xff, 0x0b, 0x00,
                             0x02, 0xff, 0xff, 0x17, 0xcd, 0xab
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SACCH Info Modify Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding SACCH Info Modify Success  ret :: %d\n", ret);
    }

    /* display SACCH Info Modify message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("SysInfoType  : %02x\n", sacchInfoMod->sysInfoType);

    if (IS_PRESENT_TM_DCM_SIM_L3_INFO((&msg)))
    {
        printf("LengthInd    : %04x\n", l3Info->lengthInd);
        for(i = 0; i < l3Info->lengthInd; i++)
        {
            printf("LLSDU[%d]   : %02x\n", i, l3Info->LLSDU[i]);
        }
    }

    if (IS_PRESENT_TM_DCM_SIM_STARTING_TIME((&msg)))
    {
        printf("StartingTime : %04x\n", sacchInfoMod->startingTime);
    }

    return ITS_SUCCESS;
}
                                                                                                                             
static ITS_INT
TM_DCM_decodeRemotCodecConfRep(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_CODEC_CONFIG *config = &msg.u.dcmMsg.u.remoteCodecConfRep.config;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.remoteCodecConfRep.codecTypes;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x39, 0xff, 0x04, 0x03,
                             0xff, 0x38, 0x05, 0xff, 0x18, 0x0f, 0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Remote Codec Configuration Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Remote Codec Configuration Report Success  ret :: %d\n", ret);
    }

    /* display Remote Codec Configuration Report message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("ConfigLength : %02x\n", config->length);
    printf("CodecType    : %02x\n", config->codecType);
    printf("ICM          : %02x\n", config->ICM);
    printf("CodecSet     : %02x\n", config->codecSet);
    
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
TM_DCM_decodeRTDRep(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_DCM_RTD_REP *rtdRep = &msg.u.dcmMsg.u.rtdRep;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x3a, 0xff, 0x0b, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Round Trip Delay Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Round Trip Delay Report Success  ret :: %d\n", ret);
    }

    /* display  Round Trip Delay Report message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("RTD      : %02x\n", rtdRep->RTD);
    printf("Delay    : %02x\n", rtdRep->delay);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodePreHandONotif(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.preHandoNotif.mrControl;
    TM_CODEC_CONFIG *config = &msg.u.dcmMsg.u.preHandoNotif.config;
    ITS_OCTET buffer[20] = { 0xf0, choice, 0x01, 0xff, 0x37, 0x00, 0x39, 0x01,
                             0x04, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Pre_HandOver Notification Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Pre_HandOver Notification success  ret :: %d\n", ret);
    }

    /* display  Pre_HandOver Notification message*/
    ret = decodeCommonDcmElements(&msg);
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
TM_DCM_decodeMCodecModReq(ITS_INT  choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MULTIRATE_CONFIG *mrConfig = &msg.u.dcmMsg.u.mrCodecModReq.mrConfig;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x36, 0x00, 0x00, 0x00,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Multirate Codec Modification Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Multirate Codec Modification Request success  ret :: %d\n", ret);
    }

    /* display  Multirate Codec Modification Request message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }        
 
    if (IS_PRESENT_TM_DCM_MCMR_MULTI_RATE_CONFIG((&msg)))
    { 
        printf("Length  : %02x\n", mrConfig->length);
        for(i = 0; i < mrConfig->length; i++)
        {
            printf("content[%d]  : %02x\n", i, mrConfig->content[i]);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeTfoRep(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[50] = { 0xff, choice, 0x01, 0xff, 0x3b, 0x0f, 0x0b, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding TFO Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding TFO Report success  ret :: %d\n", ret);
    }

    /* display TFO Report message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("TFO Status  : %02x\n",msg.u.dcmMsg.u.tfoRep.tfoStatus);

    return ITS_SUCCESS;
}

static ITS_INT
TM_DCM_decodeTfoModReq(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_MULTIRATE_CONTROL *mrControl = &msg.u.dcmMsg.u.tfoModReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg.u.dcmMsg.u.tfoModReq.codecTypes;
    ITS_OCTET buffer[50] = { 0xf0, choice, 0x01, 0xff, 0x37, 0x0f, 0x38, 0xff,
                             0xff, 0x08, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding TFO Modification Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding TFO Modification Request success  ret :: %d\n", ret);
    }

    /* display TFO Modification Request message*/
    ret = decodeCommonDcmElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("TFO           : %02x\n", mrControl->TFO);
    printf("PRE           : %02x\n", mrControl->PRE);
    printf("RAE           : %02x\n", mrControl->RAE);

    if (IS_PRESENT_TM_DCM_TMR_SUPPORTED_CODEC_TYPE((&msg)))
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
TM_LCS_decodeLocInfo(ITS_INT choice)
{
    ITS_INT ret,i;
    ABIS_TRAFFIC_MANAGEMENT_MSG msg;
    TM_LCS_LOC_INFO *lcsLocInfo = &msg.u.lcsMsg.u.lcsLocInfo;
    ITS_OCTET buffer[20] = { 0xff, choice, 0x3c, 0x02, 0xff, 0xff, 0x0b, 0x01,
                             0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                             0xff, 0xff
                           };

    ret = ABIS_TMM_Decode(&msg, sizeof(buffer), buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Location Information Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Location Information success  ret :: %d\n", ret);
    }

    /* display Location Information message*/
    ret = decodeCommonElements(&msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    printf("Length     : %02x\n", lcsLocInfo->length);
    for(i = 0; i < lcsLocInfo->length; i++)
    {
       printf("FAC IEI[%d]   : %02x\n", i, lcsLocInfo->facIEI[i]);
    }

    return ITS_SUCCESS;
}
           
static ITS_INT
reserved(ITS_INT choice)
{
    printf("Invalid/Reserved message Type\n");
    return ITS_SUCCESS;
}

/* Add all the functions here */
ITS_INT (*testTrafficEncodeMsg[MAX_TRAFFIC_FUNS_SIZE])(ITS_INT) = {
                          reserved,                       /* 0x00 */
                          TM_RLLM_encodeDataReq,          /* 0x01 */
                          TM_RLLM_encodeDataReq,          /* 0x02 */
                          TM_RLLM_encodeErrorInd,         /* 0x03 */
                          TM_RLLM_encodeEstaReq,          /* 0X04 */
                          TM_RLLM_encodeEstaReq,          /* 0x05 */
                          TM_RLLM_encodeEstaInd,          /* 0x06 */
                          TM_RLLM_encodeRelReq,           /* 0x07 */
                          TM_RLLM_encodeEstaReq,          /* 0x08 */
                          TM_RLLM_encodeEstaReq,          /* 0x09 */
                          TM_RLLM_encodeDataReq,          /* 0x0A */
                          TM_RLLM_encodeDataReq,          /* 0x0B */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          TM_CCM_encodeBcchInfo,          /* 0x11 */
                          TM_CCM_encodeCcchLoadInd,       /* 0x12 */
                          TM_CCM_encodeChanRqd,           /* 0x13 */
                          TM_CCM_encodeDeleteInd,         /* 0x14 */
                          TM_CCM_encodePagingCmd,         /* 0x15 */
                          TM_CCM_encodeDeleteInd,         /* 0x16 */
                          TM_CCM_encodeSmsBCReq,          /* 0x17 */
                          reserved,                       /* Reserved */
                          TM_TRXM_encodeRfReInd,          /* 0x19 */
                          TM_TRXM_encodeSacchFill,        /* 0x1A */
                          TM_TRXM_encodeOverload,         /* 0x1B */
                          TM_TRXM_encodeErrorReport,      /* 0x1C */
                          TM_CCM_encodeSmsBcCmd,          /* 0x1D */
                          TM_CCM_encodeCbchLoadInd,       /* 0x1E */
                          TM_CCM_encodeNotiCmd,           /* 0x1F */
                          reserved,                       /* 0x20 */
                          TM_DCM_encodeChanActiv,         /* 0x21 */
                          TM_DCM_encodeChanActivAck,      /* 0x22 */
                          TM_DCM_encodeChanActivNAck,     /* 0x23 */
                          TM_DCM_encodeChanActivNAck,     /* 0x24 */
                          TM_DCM_encodeDeactivSaach,      /* 0x25 */
                          TM_DCM_encodeEncrCmd,           /* 0x26 */                    
                          TM_DCM_encodeHandODet,          /* 0x27 */
                          TM_DCM_encodeMeasRes,           /* 0x28 */
                          TM_DCM_encodeModeModifyReq,     /* 0x29 */
                          TM_DCM_encodeDeactivSaach,      /* 0x2A */
                          TM_DCM_encodeChanActivNAck,     /* 0x2B */
                          TM_DCM_encodeDeactivSaach,      /* 0x2C */
                          TM_DCM_encodePhyContextConf,    /* 0x2D */
                          TM_DCM_encodeDeactivSaach,      /* 0x2E */
                          TM_DCM_encodeMsPowerControl,    /* 0x2F */
                          TM_DCM_encodeBsPowerControl,    /* 0x30 */
                          TM_DCM_encodePreprocConfig,     /* 0x31 */
                          TM_DCM_encodePreproceMeasRes,   /* 0x32 */
                          TM_DCM_encodeDeactivSaach,      /* 0x33 */
                          TM_DCM_encodeSacchInfoModify,   /* 0x34 */
                          TM_DCM_encodeHandODet,          /* 0x35 */
                          TM_DCM_encodeHandODet,          /* 0x36 */
                          TM_DCM_encodeRemotCodecConfRep, /* 0x37 */
                          TM_DCM_encodeRTDRep,            /* 0x38 */
                          TM_DCM_encodePreHandONotif,     /* 0x39 */
                          TM_DCM_encodeMCodecModReq,      /* 0x3A */
                          TM_DCM_encodeMCodecModReq,      /* 0x3B */
                          TM_DCM_encodeChanActivNAck,     /* 0x3C */
                          TM_DCM_encodeMCodecModReq,      /* 0x3D */
                          TM_DCM_encodeTfoRep,            /* 0x3E */
                          TM_DCM_encodeTfoModReq,         /* 0x3F */
                          reserved,                       /* Reserved */
                          TM_LCS_encodeLocInfo            /* 0x41 */
                      };



ITS_INT (*testTrafficDecodeMsg[MAX_TRAFFIC_FUNS_SIZE])(ITS_INT) = {
                          reserved,                       /* 0x00 */   
                          TM_RLLM_decodeDataReq,          /* 0x01 */
                          TM_RLLM_decodeDataReq,          /* 0x02 */
                          TM_RLLM_decodeErrorInd,         /* 0x03 */
                          TM_RLLM_decodeEstaReq,          /* 0x04 */
                          TM_RLLM_decodeEstaReq,          /* 0x05 */
                          TM_RLLM_decodeEstaInd,          /* 0x06 */
                          TM_RLLM_decodeRelReq,           /* 0x07 */
                          TM_RLLM_decodeEstaReq,          /* 0x08 */
                          TM_RLLM_decodeEstaReq,          /* 0x09 */
                          TM_RLLM_decodeDataReq,          /* 0x0A */
                          TM_RLLM_decodeDataReq,          /* 0x0B */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          reserved,                       /* Reserved */
                          TM_CCM_decodeBcchInfo,          /* 0x11 */
                          TM_CCM_decodeCcchLoadInd,       /* 0x12 */
                          TM_CCM_decodeChanRqd,           /* 0x13 */
                          TM_CCM_decodeDeleteInd,         /* 0x14 */
                          TM_CCM_decodePagingCmd,         /* 0x15 */
                          TM_CCM_decodeDeleteInd,         /* 0x16 */
                          TM_CCM_decodeSmsBCReq,          /* 0x17 */
                          reserved,                       /* Reserved */
                          TM_TRXM_decodeRfReInd,          /* 0x19 */
                          TM_TRXM_decodeSacchFill,        /* 0x1A */
                          TM_TRXM_decodeOverload,         /* 0x1B */
                          TM_TRXM_decodeErrorReport,      /* 0x1C */
                          TM_CCM_decodeSmsBcCmd,          /* 0x1D */
                          TM_CCM_decodeCbchLoadInd,       /* 0x1E */
                          TM_CCM_decodeNotiCmd,           /* 0x1F */
                          reserved,                       /* 0x20 */
                          TM_DCM_decodeChanActiv,         /* 0x21 */
                          TM_DCM_decodeChanActivAck,      /* 0x22 */
                          TM_DCM_decodeChanActivNAck,     /* 0x23 */
                          TM_DCM_decodeChanActivNAck,     /* 0x24 */
                          TM_DCM_decodeDeactivSaach,      /* 0x25 */
                          TM_DCM_decodeEncrCmd,           /* 0x26 */
                          TM_DCM_decodeHandODet,          /* 0x27 */
                          TM_DCM_decodeMeasRes,           /* 0x28 */
                          TM_DCM_decodeModeModifyReq,     /* 0x29 */
                          TM_DCM_decodeDeactivSaach,      /* 0x2A */
                          TM_DCM_decodeChanActivNAck,     /* 0x2B */
                          TM_DCM_decodeDeactivSaach,      /* 0x2C */
                          TM_DCM_decodePhyContextConf,    /* 0x2D */
                          TM_DCM_decodeDeactivSaach,      /* 0x2E */
                          TM_DCM_decodeMsPowerControl,    /* 0x2F */
                          TM_DCM_decodeBsPowerControl,    /* 0x30 */
                          TM_DCM_decodePreprocConfig,     /* 0x31 */
                          TM_DCM_decodePreproceMeasRes,   /* 0x32 */
                          TM_DCM_decodeDeactivSaach,      /* 0x33 */
                          TM_DCM_decodeSacchInfoModify,   /* 0x34 */
                          TM_DCM_decodeHandODet,          /* 0x35 */
                          TM_DCM_decodeHandODet,          /* 0x36 */
                          TM_DCM_decodeRemotCodecConfRep, /* 0x37 */
                          TM_DCM_decodeRTDRep,            /* 0x38 */
                          TM_DCM_decodePreHandONotif,     /* 0x39 */
                          TM_DCM_decodeMCodecModReq,      /* 0x3A */
                          TM_DCM_decodeMCodecModReq,      /* 0x3B */
                          TM_DCM_decodeChanActivNAck,     /* 0x3C */
                          TM_DCM_decodeMCodecModReq,      /* 0x3D */
                          TM_DCM_decodeTfoRep,            /* 0x3E */
                          TM_DCM_decodeTfoModReq,         /* 0x3F */
                          reserved,                       /* Reserved */
                          TM_LCS_decodeLocInfo            /* 0x41 */
                     };

