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
 *  ID: $Id: network_codec_test_app.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
 *  $Log: not supported by cvs2svn $
 *  Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
 *  init tree
 *
 *  Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 *  BscCs2
 *
 *  Revision 1.1.1.1  2007/03/08 15:12:53  cvsadmin
 *  BSC project
 *
 *  Revision 1.1.2.3  2006/04/07 09:33:00  yranade
 *  RF Max Power Reduction IE Added (sgavalkar)
 *
 *  Revision 1.1.2.2  2006/03/28 09:18:05  yranade
 *  TRX Hello message added. (sgavalkar)
 *
 *  Revision 1.1.2.1  2005/08/16 11:41:53  mkrishna
 *  Added Initial version after unit testing.
 *
 *
 ****************************************************************************/

#include <abis_network_management.h>

static ITS_INT
NM_encodeFomCommonElements(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_INT choice)
{
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    OBJECT_INSTANCE *objInst = &msg->u.formMsg.formGenElemnts.objInst;

    formGenElemnts->msgDesc =  0x00;
    formGenElemnts->placeInd = 0x00;
    formGenElemnts->seqNum =   0x00;

    formGenElemnts->msgType = choice;
    formGenElemnts->objClass = 0x00;

    objInst->btsNum      = 0x00; 
    objInst->baseBandNum = 0x00;
    objInst->timeSlotNum = 0x00;
    
    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_encodeLoadDataInit(ITS_INT choice)
{ 
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr;
    NM_SWDM_LOAD_DATA_INIT *loadInit = &msg.u.formMsg.u.swdmMsg.u.loadInit;
    ITS_OCTET buffer[100]; 
    ITS_UINT ret = 0, i, len;
    
    ret = NM_encodeFomCommonElements(&msg, choice); 
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    swDescr->fileIdLen = 0x02;
    for (i = 0; i < swDescr->fileIdLen; i++)
    {
        swDescr->fileId[i] = 0x01;  
    }

    swDescr->fileVerLen = 0x02;
    for (i = 0; i < swDescr->fileVerLen; i++)
    {
        swDescr->fileVer[i] = 0x01;
    }

    loadInit->winSize = 0x01;
    loadInit->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Load Data Initiate Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Load Data Initiate Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    
    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_encodeLoadDataSeg(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SWDM_LOAD_DATA_SEG *loadSeg = &msg.u.formMsg.u.swdmMsg.u.loadSeg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                             
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    loadSeg->length = 0x02;
    for (i = 0; i < loadSeg->length; i++)
    {
        loadSeg->data[i] = 0x02;
    }

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Load Data Segment Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Load Data Segment Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                      
    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_encodeLoadDataAbort(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                         
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                       
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Load Data Abort Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Load Data Abort Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                        
    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_encodeLoadDataEnd(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.swdmMsg.u.loadEnd.swDescr; 
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                                              
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    swDescr->fileIdLen = 0x02;
    for (i = 0; i < swDescr->fileIdLen; i++)
    {
        swDescr->fileId[i] = 0x01;
    }                                                                                                                                         
    swDescr->fileVerLen = 0x00;
    for (i = 0; i < swDescr->fileVerLen; i++)
    {
        swDescr->fileVer[i] = 0x01;
    }                                                                                                                                         
    msg.u.formMsg.u.swdmMsg.u.loadEnd.nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Data Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Data Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_encodeSwActiveReq(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG *msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, j, len;                                                                                                                                         
    msg = (ABIS_NETWORK_MANAGEMENT_MSG *)malloc(sizeof(ABIS_NETWORK_MANAGEMENT_MSG));

    ret = NM_encodeFomCommonElements(msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                     
    msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length = 0x01;
    /* allocate memory for SW Description */
    msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc = 
    (SW_DESCRIPTION *)calloc(msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length, sizeof(SW_DESCRIPTION));   
 
    for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length; j++)
    {
        msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileIdLen = 0x02; 
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileIdLen; i++)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileId[i] = 0x01;
        }

        msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVerLen = 0x02;
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVerLen; i++)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVer[i] = 0x01;
        }
    }

    msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length = 0x01;
    /* allocate memory for SW Description */
    msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc =
    (HW_DESCRIPTION *)calloc(msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length, sizeof(HW_DESCRIPTION));
                                                                                                                                              
    for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length; j++)
    {
        msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipIdLen= 0x02;
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipIdLen; i++)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipId[i] = 0x01;
        }
                                                                                                                                              
        msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipTypeLen= 0x02;
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipTypeLen; i++)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipType[i] = 0x01;
        }

        msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVerLen = 0x02;
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVerLen; i++)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVer[i] = 0x01;
        }

        msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].locLen = 0x02;
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].locLen; i++)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].location[i] = 0x01;
        }

        msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].infoLen = 0x02;
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].infoLen; i++)
        {
            msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].info[i] = 0x01;
        }
    }
    
    msg->u.formMsg.u.swdmMsg.u.actReq.nackCuase = 0xcd;
    
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding SW Activated Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding SW Activated Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                             
    free(msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc);
    free(msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc);
    free(msg);

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_encodeActivateSw(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.swdmMsg.u.actSw.swDescr;
    NM_SWDM_ACTIVE_SW *actSw = &msg.u.formMsg.u.swdmMsg.u.actSw; 
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                              
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                 
    /* Initialise optional bit map */
    CLEAR_NM_SWDM_AS_OPTIONAL_BIT_MAP((&msg));

    SET_NM_SWDM_AS_SW_DESCRIPTION((&msg));
    swDescr->fileIdLen = 0x02;
    for (i = 0; i < swDescr->fileIdLen; i++)
    {
        swDescr->fileId[i] = 0x01;
    }                                                                                                                                              
    swDescr->fileVerLen = 0x00;
    for (i = 0; i < swDescr->fileVerLen; i++)
    {
        swDescr->fileVer[i] = 0x01;
    }                                                                                                                                         
    actSw->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Activate SW Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Activate SW Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                           
    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_encodeEstablishTei(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_ABIM_ESTABLISH_TEI *estaTei = &msg.u.formMsg.u.abisMsg.u.estaTei;
    ABIS_CHANNEL *abisChanl = &msg.u.formMsg.u.abisMsg.abisChanl;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                         
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                      
    estaTei->teiVal = 0x6F;
    estaTei->nackCuase = 0xcd;

    abisChanl->btsPortNum = 0x02;
    abisChanl->timeSlotNum = 0x1F;
    abisChanl->subSlotNum = 0x2F;
 
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Establish TEI Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Establish TEI Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                         
    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_encodeConnTerrSign(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ABIS_CHANNEL *abisChanl = &msg.u.formMsg.u.abisMsg.abisChanl;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg.u.formMsg.formGenElemnts;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                                              
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    abisChanl->btsPortNum = 0x02;
    abisChanl->timeSlotNum = 0x1F;
    abisChanl->subSlotNum = 0x02;
 
    msg.u.formMsg.u.abisMsg.u.connTerr.nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Connection Terristrial Signalling Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Connection Terristrial Signalling Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                         
    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_encodeConnTerrTraffic(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ABIS_CHANNEL *abisChanl = &msg.u.formMsg.u.abisMsg.abisChanl;
    NM_ABIM_CONN_TERR_TRAFFIC *connTraf = &msg.u.formMsg.u.abisMsg.u.connTraf;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                                              
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    abisChanl->btsPortNum = 0x02;
    abisChanl->timeSlotNum = 0x1F;
    abisChanl->subSlotNum = 0x02;
 
    /* Intialise optional bit map field */
    CLEAR_NM_AM_CTT_OPTIONAL_BIT_MAP((&msg));

    SET_NM_AM_CTT_RADIO_SUB_CHANNEL((&msg));

    connTraf->radioSubChanl = 0x02;

    connTraf->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Connection Terristrial Traffic Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Connection Terristrial Traffic Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_TRM_encodeConnMultiDropLink(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    MD_BSC_LINK *bscLink = &msg.u.formMsg.u.transMsg.u.conLink.bscLink;
    MD_NEXT_BTS_LINK *btsLink = &msg.u.formMsg.u.transMsg.u.conLink.btsLink;
    NM_TRM_CON_MULTI_DROP_LINK *conLink = &msg.u.formMsg.u.transMsg.u.conLink;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                      
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                        
    bscLink->btsPortNum = 0x01;
    bscLink->timeSlotNum = 0x1F;

    btsLink->btsPortNum = 0x02;
    btsLink->timeSlotNum = 0x1F;

    conLink->nackCuase = 0xcd;
 
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Connection Multi-drop Link Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Connection Multi-drop Link Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                       
    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_encodeSetBtsAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_AIM_SET_BTS_ATTR *btsAttr = &msg.u.formMsg.u.airMsg.u.btsAttr;
    INTER_LEVEL_BOUND *interLevel = &msg.u.formMsg.u.airMsg.u.btsAttr.interLevel;
    CON_FAIL_CRITERION *conFail = &msg.u.formMsg.u.airMsg.u.btsAttr.conFail;
    T200 *t200 = &msg.u.formMsg.u.airMsg.u.btsAttr.t200;
    OVERLOAD_PERIOD *overldPeriod = &msg.u.formMsg.u.airMsg.u.btsAttr.overldPeriod;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;

    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    /* initialise optional bit map */
    CLEAR_NM_AIM_SBA_OPTIONAL_BIT_MAP((&msg));

    SET_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES((&msg));
    interLevel->interfBound0 = 0x01;
    interLevel->interfBound1 = 0x01;
    interLevel->interfBound2 = 0x01;
    interLevel->interfBound3 = 0x01;
    interLevel->interfBound4 = 0x01;
    interLevel->interfBound5 = 0x01;     

    SET_NM_AIM_SBA_INTAVE_PARAMETER((&msg));
    btsAttr->intaveParam = 0x02;
    
    SET_NM_AIM_SBA_CONN_FAILURE_CRITERION((&msg));
    conFail->length = 0x03;
    conFail->failCrit = 0x03;
    for (i = 0; i < conFail->length; i++)
    {
        conFail->critVal[i] = 0x03;
    }  

    SET_NM_AIM_SBA_T200((&msg));
    t200->sdcch = 0x04;
    t200->facchFull = 0x04;
    t200->facchHalf = 0x04;
    t200->sacchSap10 = 0x04;
    t200->sacchSdcch = 0x04;
    t200->sdcchSap13 = 0x04;
    t200->sacchSap13 = 0x04;

    SET_NM_AIM_SBA_MAX_TIMING_ADVANCE((&msg));
    btsAttr->maxTimeAdv = 0x05;

    SET_NM_AIM_SBA_OVERLOAD_PERIOD((&msg));
    overldPeriod->length = 0x02;
    for (i = 0; i < overldPeriod->length; i++)
    {
        overldPeriod->period[i] = 0x06;
    } 

    SET_NM_AIM_SBA_CCCH_LOAD_THRESHOLD((&msg));
    btsAttr->threshold = 0x07;

    SET_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD((&msg));
    btsAttr->initPeriod = 0x08;

    SET_NM_AIM_SBA_RACH_BUSY_THRESHOLD((&msg));
    btsAttr->busyThreshold = 0x09;

    SET_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS((&msg));
    btsAttr->avgSlots = 0x0A;

    SET_NM_AIM_SBA_BTS_AIR_TIMER((&msg));
    btsAttr->airT3105.tch = 0x11;
    btsAttr->airT3105.sdcch = 0x22;

    SET_NM_AIM_SBA_NY1((&msg));
    btsAttr->ny1.tch = 0x33;
    btsAttr->ny1.sdcch = 0x44;

    SET_NM_AIM_SBA_BCCH_ARFCN((&msg));
    btsAttr->arfcn = 0x0D;

    SET_NM_AIM_SBA_BSIC((&msg));
    btsAttr->bsic = 0x0E;

    SET_NM_AIM_SBA_RF_MAX_POWER_REDUCTION((&msg));
    btsAttr->powerRedn = 0x88;

    SET_NM_AIM_SBA_STARTING_TIME((&msg));
    btsAttr->startCurFrameNo = 0x0F;
 
    btsAttr->nackCuase = 0xcd;

    SET_NM_AIM_SBA_PAGING_AG_PARAMS((&msg));
    btsAttr->pageAgParams.bsPaMfrms = 0xF1;
    btsAttr->pageAgParams.bsCcchChans = 0xF2;
    btsAttr->pageAgParams.bsAgRes = 0xF3;
    btsAttr->pageAgParams.pageAlg = 0xF4;
                                                                                
    SET_NM_AIM_SBA_SYST_INFO_LIST((&msg));
    btsAttr->systInfoList.len = 0x05;
    for (i = 0; i < btsAttr->systInfoList.len; i++)
    {
        btsAttr->systInfoList.six[i] = 0x03;
    }
                                                                                
    SET_NM_AIM_SBA_FN_OFFSET((&msg));
    btsAttr->fnOffset = 0xFF; 

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Set BTS Attributes Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Set BTS Attributes Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_encodeSetRadioCarrierAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_AIM_SET_RADIO_ATTR *radioAttr = &msg.u.formMsg.u.airMsg.u.radioAttr;
    ARFCN_LIST  *arfcnList = &msg.u.formMsg.u.airMsg.u.radioAttr.arfcnList;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                         
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map */
    CLEAR_NM_AIM_SRCA_OPTIONAL_BIT_MAP((&msg));

    SET_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION((&msg));
    radioAttr->powerRedu = 0x01;

    SET_NM_AIM_SRCA_ARFCN_LIST((&msg));
    arfcnList->length = 0x03;
   
    for (i = 0; i < arfcnList->length; i++)
    {
        arfcnList->arfcn[i] = 0x3FF;
    }
    radioAttr->nackCuase = 0xcd;    

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Set Radio Carrier Attributes Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Set Radio Carrier Attributes Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_encodeSetChanlAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_AIM_SET_CHANNEL_ATTR *chanlAttr = &msg.u.formMsg.u.airMsg.u.chanlAttr;
    ARFCN_LIST *arfcnList = &msg.u.formMsg.u.airMsg.u.chanlAttr.arfcnList;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                          
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map */
    CLEAR_NM_AIM_SCA_OPTIONAL_BIT_MAP((&msg));

    SET_NM_AIM_SCA_CHANNEL_COMBINATION((&msg));
    chanlAttr->chanlComb = 0x01;

    SET_NM_AIM_SCA_HSN((&msg));
    chanlAttr->hsn = 0x02;

    SET_NM_AIM_SCA_MAIO((&msg));
    chanlAttr->maioList.len = 0x05;
    for (i = 0; i < chanlAttr->maioList.len; i++)
    {
        chanlAttr->maioList.maio[i] = 0x88;
    }

    SET_NM_AIM_SCA_ARFCN_LIST((&msg));
    arfcnList->length = 0x03;
    for (i = 0; i < arfcnList->length; i++)
    {
        arfcnList->arfcn[i] = 0x04;
    } 

    SET_NM_AIM_SCA_STARTING_TIME((&msg));
    chanlAttr->startCurFrameNo = 0x05;

    SET_NM_AIM_SCA_TSC((&msg));
    chanlAttr->tscSeqCode = 0x06;
 
    SET_NM_AIM_SCA_RF_MAX_POWER_REDUCTION((&msg));
    chanlAttr->powerRedn = 0x88;

    chanlAttr->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Set Channel Attributes Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Set Channel Attributes Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_encodePerformTest(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_TM_PERFORM_TEST *perfTest = &msg.u.formMsg.u.testMsg.u.perfTest;
    PHYSICAL_CONFIG *phyContext = &msg.u.formMsg.u.testMsg.u.perfTest.phyContext; 
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;

    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    msg.u.formMsg.u.testMsg.testNum = 0x01;

    perfTest->autoRep = 0x02;

    /* Initialise optiona bit map */
    CLEAR_NM_TM_PT_OPTIONAL_BIT_MAP((&msg));

    SET_NM_TM_PT_TEST_DURATION((&msg));
    perfTest->testDura = 0x03;

    SET_NM_TM_PT_PHYSICAL_CONFIGURATION((&msg));
    phyContext->length = 0x02;
    for (i = 0; i < phyContext->length; i++)
    {
        phyContext->testConfig[i] = 0x03;
    } 
    
    perfTest->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Perform Test Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Perform Test Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_encodeTestReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_TM_TEST_REP *testRep = &msg.u.formMsg.u.testMsg.u.testRep;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                                              
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    msg.u.formMsg.u.testMsg.testNum = 0x01;

    testRep->length = 0x03;
    for (i = 0; i < testRep->length; i++)
    {
        testRep->resultInfo[i] = 0x02;
    } 

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Test Report Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Test Report Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                       
    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_encodeSendTestReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                      
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                       
    msg.u.formMsg.u.testMsg.testNum = 0x01;

    msg.u.formMsg.u.testMsg.u.sendRep.nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Send Test Report Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Send Test Report Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                   
    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_encodeStateChangdEventRep(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_STATE_CHNG_EVENT_REP *changeEv = &msg.u.formMsg.u.stateMsg.u.changeEv;
    AVAILABILITY_STATUS *availStat = &msg.u.formMsg.u.stateMsg.u.changeEv.availStat;
    SITE_INPUTS *siteInputs = &msg.u.formMsg.u.stateMsg.u.changeEv.siteInputs;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                       
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map */
    CLEAR_NM_SM_SCER_OPTIONAL_BIT_MAP((&msg));

    SET_NM_SM_SCER_OPERATIONAL_STATE((&msg));
    changeEv->operanStat = 0x01;

    SET_NM_SM_SCER_AVAILABILITY_STATE((&msg));
    availStat->length = 0x03;
    for (i = 0; i < availStat->length; i++)
    {
        availStat->status[i] = 0x02;
    }

    SET_NM_SM_SCER_MAN_DEP_STATE((&msg));
    changeEv->mfdDepen = 0x03;

    SET_NM_SM_SCER_SITE_INPUTS((&msg));
    siteInputs->length = 0x03;
    for (i = 0; i < siteInputs->length; i++)
    {
        siteInputs->attr[i].state = 0x01;
        siteInputs->attr[i].input = 0x7F;
    }

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding State Changed Event Report Failed ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding State Changed Event Report Success ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_encodeFailureEventReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_FAIL_EVENT_REP *failEv = &msg.u.formMsg.u.stateMsg.u.failEv;
    PROBABLE_CAUSE *probCause = &msg.u.formMsg.u.stateMsg.u.failEv.probCause;
    ADDITIONAL_TEXT *addText = &msg.u.formMsg.u.stateMsg.u.failEv.addText;
    ADDITIONAL_INFO *addInfo = &msg.u.formMsg.u.stateMsg.u.failEv.addInfo;
    HW_DESCRIPTION *hwDescr = &msg.u.formMsg.u.stateMsg.u.failEv.hwDescr;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.stateMsg.u.failEv.swDescr;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                          
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                      
    failEv->evtType         = 0x01;
    failEv->percvdSever     = 0x02;
    failEv->probCause.type  = 0x03;
    failEv->probCause.value = 0x03;

    /* Initialise optiona bit map */
    CLEAR_NM_SM_FER_OPTIONAL_BIT_MAP((&msg));

    SET_NM_SM_FER_SPECIFIC_PROBLEMS((&msg));
    failEv->specProbs = 0x04;

    SET_NM_SM_FER_HW_DESCRIPTION((&msg));
    hwDescr->equipIdLen = 0x02;
    for (i = 0; i < hwDescr->equipIdLen; i++)
    {
        hwDescr->equipId[i] = 0x05;
    }

    hwDescr->equipTypeLen = 0x02;
    for (i = 0; i < hwDescr->equipTypeLen; i++)
    {
        hwDescr->equipType[i] = 0x05;
    }
    
    hwDescr->equipVerLen = 0x02;
    for (i = 0; i < hwDescr->equipVerLen; i++)
    {
        hwDescr->equipVer[i] = 0x05;
    }
    
    hwDescr->locLen = 0x02;
    for (i = 0; i < hwDescr->locLen; i++)
    {
        hwDescr->location[i] = 0x05;
    }
    
    hwDescr->infoLen = 0x02;
    for (i = 0; i < hwDescr->infoLen; i++)
    {
        hwDescr->info[i] = 0x05;
    }
    
    SET_NM_SM_FER_SW_DESCRIPTION((&msg));
    swDescr->fileIdLen = 0x02;
    for (i = 0; i < swDescr->fileIdLen; i++)
    {
        swDescr->fileId[i] = 0x06;
    }

    swDescr->fileVerLen = 0x02;
    for (i = 0; i < swDescr->fileVerLen; i++)
    {
        swDescr->fileVer[i] = 0x06;
    }

    SET_NM_SM_FER_ADDITIONAL_TEXT((&msg));
    addText->length = 0x02;
    for (i = 0; i < addText->length; i++)
    {
        addText->value[i] = 0x07;
    }

    SET_NM_SM_FER_ADDITIONAL_INFO((&msg));
    addInfo->length = 0x02;
    for (i = 0; i < addInfo->length; i++)
    {
        addInfo->value[i] = 0x07;
    }

    SET_NM_SM_FER_OUTSTANDING_ALARM_SEQ((&msg));
    failEv->alarmSeq = 0x08; 
 
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Failure Event Report Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Failure Event Report Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_encodeStopSendEventReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_STOP_SEND_EVENT_REP *stopEv = &msg.u.formMsg.u.stateMsg.u.stopEv;
    AVAILABILITY_STATUS *availStat = &msg.u.formMsg.u.stateMsg.u.stopEv.availStat;
    PROBABLE_CAUSE *probCause = &msg.u.formMsg.u.stateMsg.u.stopEv.probCause;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                                              
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map */
    CLEAR_NM_SM_SSER_OPTIONAL_BIT_MAP((&msg));

    SET_NM_SM_SSER_OPERATIONAL_STATE((&msg));
    stopEv->operanStat = 0x01;

    SET_NM_SM_SSER_AVAILABILTY_STATE((&msg));
    availStat->length = 0x03;
    for (i = 0; i < availStat->length; i++)
    {
        availStat->status[i] = 0x02;
    }

    SET_NM_SM_SSER_MFD_DEP_STATE((&msg));
    stopEv->mfdDepen = 0x03;

    SET_NM_SM_SSER_PROBABLE_CAUSE((&msg));
    probCause->type = 0x04;
    probCause->value = 0x04;

    SET_NM_SM_SSER_SPECIFIC_PROBLEMS((&msg));
    stopEv->specProbs = 0x05;

    stopEv->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Stop Sending Event Rep Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Stop Sending Event Rep Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_encodeChangeAdminState(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_CHNG_ADMIN_STATE *state = &msg.u.formMsg.u.stateMsg.u.state;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                      
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                          
    state->adminStat = 0x01;
    state->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Change Admin State Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Change Admin State Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                       
    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_encodeChangeover(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SOURCE *src = &msg.u.formMsg.u.equipMsg.u.changeOver.src;
    DESTINATION *dest = &msg.u.formMsg.u.equipMsg.u.changeOver.dest;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                          
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                      
    src->length = 0x02;
    for (i = 0; i < src->length; i++)
    {
        src->value[i] = 0x01;
    }

    dest->length = 0x02;
    for (i = 0; i < dest->length; i++)
    {
        dest->value[i] = 0x01;
    }

    msg.u.formMsg.u.equipMsg.u.changeOver.nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Changeover Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Changeover Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                          
    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_encodeOpstart(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
    msg.u.formMsg.u.equipMsg.u.opStart.nackCuase = 0xcd;     
                                                                                                                    
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                             
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Opstart Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Opstart Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                      
    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_encodeSetSiteOutputs(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_EM_SET_SITE_OUTPUTS *siteOutput = &msg.u.formMsg.u.equipMsg.u.siteOutput;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    siteOutput->length = 0x02;
    for (i = 0; i < siteOutput->length; i++)
    {
        siteOutput->output[i] = 0x01;
    } 

    siteOutput->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Set Site Outputs Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Set Site Outputs Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                       
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_encodeGetAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_MS_GET_ATTR *getAttr = &msg.u.formMsg.u.miscMsg.u.getAttr;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                          
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                        
    getAttr->length = 0x02;
    for (i = 0; i < getAttr->length; i++)
    {
        getAttr->atrrId[i] = 0x01;
    }

    getAttr->nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Get Attributes Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Get Attributes Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                       
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_encodeGetAttrResp(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_MS_GET_ATTR_RESP *getAttrResp = &msg.u.formMsg.u.miscMsg.u.getAttrResp;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                        
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                     
    getAttrResp->length = 0x05;
    getAttrResp->notRepCount = 0x02;

    for (i = 0; i < getAttrResp->length; i++)
    {
        getAttrResp->notRep[i] = 0x01;
        getAttrResp->reported[i] = 0x02;
    }

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Get Attributes Resp Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Get Attributes Resp Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                          
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_encodeSetAlarmThreshold(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    POWER_OUTPUT_THRESHOLD *powerOutput =
                   &msg.u.formMsg.u.miscMsg.u.alarmThresh.powerOutput;
    PROBABLE_CAUSE *probCause = &msg.u.formMsg.u.miscMsg.u.alarmThresh.probCause;
    VSWR_THRESHOLD *vswr = &msg.u.formMsg.u.miscMsg.u.alarmThresh.vswr;
    MFD_THRESHOLDS *mfdThresh = &msg.u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;

    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    probCause->type = 0x01;
    probCause->value = 0x01;

    /* Initialise optional bit map */
    CLEAR_NM_MM_SAT_OPTIONAL_BIT_MAP((&msg));

    SET_NM_MM_SAT_POWER_OUTPUT_THRESHOLD((&msg));
    powerOutput->fault = 0x02;
    powerOutput->reduced = 0x02;
    powerOutput->excessive = 0x02;

    SET_NM_MM_SAT_VSWR_THRESHOLDS((&msg));
    vswr->faulty = 0x03;
    vswr->notAdjusted = 0x03;

    SET_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS((&msg));
    mfdThresh->length = 0x03;
    for (i = 0; i < mfdThresh->length; i++)
    {
        mfdThresh->mfdDependnt[i] = 0x04;
    }

    msg.u.formMsg.u.miscMsg.u.alarmThresh.nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Get Attribute Resp Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Get Attribute Resp Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                         
    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_encodeReinitialise(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    HW_DESCRIPTION *hwDesc = &msg.u.formMsg.u.equipMsg.u.reInit.hwDesc; 
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                                                 
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    /* Initialise optional bit map */
    CLEAR_NM_EM_REIN_OPTIONAL_BIT_MAP((&msg));
 
    SET_NM_EM_REIN_HW_DESCRIPTION((&msg));
    hwDesc->equipIdLen = 0x02;
    for (i = 0; i < hwDesc->equipIdLen; i++)
    {
        hwDesc->equipId[i] = 0x01;
    }
                                                                                                                       
    hwDesc->equipTypeLen = 0x02;
    for (i = 0; i < hwDesc->equipTypeLen; i++)
    {
        hwDesc->equipType[i] = 0x01;
    }                                                                                                                                        
    hwDesc->equipVerLen = 0x02;
    for (i = 0; i < hwDesc->equipVerLen; i++)
    {
        hwDesc->equipVer[i] = 0x01;
    }                                                                                                                                         
    hwDesc->locLen = 0x02;
    for (i = 0; i < hwDesc->locLen; i++)
    {
        hwDesc->location[i] = 0x01;
    }                                                                                                                                         
    hwDesc->infoLen = 0x02;
    for (i = 0; i < hwDesc->infoLen; i++)
    {
        hwDesc->info[i] = 0x01;
    }

    msg.u.formMsg.u.equipMsg.u.reInit.nackCuase = 0xcd;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding  Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding  Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                         
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_encodeMeasResultReq(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                        
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                       
    msg.u.formMsg.u.measMsg.measId = 0x01;

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Measurement Result Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Measurement Result Request Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                      
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_encodeMeasResultResp(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_MM__MEAS_RES_RESP *measResp = &msg.u.formMsg.u.measMsg.u.measResp;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                         
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    msg.u.formMsg.u.measMsg.measId = 0x01;

    measResp->length = 0x03;
    for (i = 0; i < measResp->length; i++)
    {
        measResp->measResult[i] = 0x02;
    }

    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Measurement Result Resp Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Measurement Result Resp Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }
                                                                                                                      
    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_encodeReportOutstandAlarms(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;                                                                                                                                         
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    msg.u.formMsg.u.stateMsg.u.repAlarm.nackCuase = 0xcd;    
                                                                                                                   
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding Report Outstanding Alarm Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding Report Outstanding Alarm Success  ret :: %d\n\n", ret);
        /* display buffer */
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                                                                        
    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_encodeTrxHello(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;     NM_SM_TRX_HELLO *trxHello = &msg.u.formMsg.u.stateMsg.u.trxHello;     ITS_OCTET buffer[100];
    ITS_UINT ret = 0, i, len;
                                                                                
    ret = NM_encodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                
    trxHello->onmProtoVer.versionX = 0xAA;
    trxHello->onmProtoVer.versionY = 0xAA;
                                                                                
    trxHello->hwCapab.freqHop = 0xBB;
    trxHello->hwCapab.diversity = 0xBB;
    trxHello->hwCapab.powClassSup = 0xBB;
    trxHello->hwCapab.freqBand = 0xBB;
    trxHello->hwCapab.lsclAvail = 0xBB;
    trxHello->hwCapab.memoryCapb = 0xBB;
                                                                                
    SET_NM_SM_TRX_HELLO_SW_DESC((&msg));
    trxHello->swDesc.fileIdLen = 0x0004;
    for (i = 0; i < trxHello->swDesc.fileIdLen; i++)
    {
        trxHello->swDesc.fileId[i] = 0xCC;
    }
                                                                                     trxHello->swDesc.fileVerLen = 0x0004;
    for (i = 0; i < trxHello->swDesc.fileVerLen; i++)
    {
        trxHello->swDesc.fileVer[i] = 0xDD;
    }

    SET_NM_SM_TRX_HELLO_HW_DESC((&msg));
    trxHello->hwDesc.equipIdLen = 0x0003;
    for (i = 0; i < trxHello->hwDesc.equipIdLen; i++)
    {
        trxHello->hwDesc.equipId[i] = 0x11;
    }
                                                                                
    trxHello->hwDesc.equipTypeLen = 0x0003;
    for (i = 0; i < trxHello->hwDesc.equipTypeLen; i++)
    {
        trxHello->hwDesc.equipType[i] = 0x22;
    }
                                                                                
    trxHello->hwDesc.equipVerLen = 0x0003;
    for (i = 0; i < trxHello->hwDesc.equipVerLen; i++)
    {
        trxHello->hwDesc.equipVer[i] = 0x33;
    }
                                                                                
    trxHello->hwDesc.locLen = 0x0003;
    for (i = 0; i < trxHello->hwDesc.locLen; i++)
    {
        trxHello->hwDesc.location[i] = 0x44;
    }
                                                                                
    trxHello->hwDesc.infoLen = 0x0003;
    for (i = 0; i < trxHello->hwDesc.infoLen; i++)
    {
        trxHello->hwDesc.info[i] = 0x55;
    }
                                                                                
    len = sizeof(ABIS_NETWORK_MANAGEMENT_MSG);
    ret = ABIS_NMM_Encode(&msg, &len, buffer);
                                                                                
    if (ret != ITS_SUCCESS)
    {
        printf("Encoding TRX Hello Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Encoding TRX Hello Success  ret :: %d\n\n", ret);
                                                                                
        for(i=0;i<len;i++)
        {
           printf("%02x ", buffer[i]);
        }
        printf("\n\n");
    }                                                                                 
    return ITS_SUCCESS;
}

static ITS_INT
NM_decodeFomCommonElements(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_INT choice)
{
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    OBJECT_INSTANCE *objInst = &msg->u.formMsg.formGenElemnts.objInst;

    printf(" msg Desc   : %02x\n", formGenElemnts->msgDesc);
    printf(" Place Ind  : %02x\n", formGenElemnts->placeInd);
    printf(" Seq Num    : %02x\n", formGenElemnts->seqNum);
    printf(" Length     : %02x\n", formGenElemnts->lenInd);

    printf(" Msg Type   : %02x\n", formGenElemnts->msgType);
    printf(" Obj Class  : %02x\n", formGenElemnts->objClass);

    printf(" Bts Num    : %02x\n", objInst->btsNum); 
    printf(" Band Num   : %02x\n", objInst->baseBandNum);
    printf(" Slot Num   : %02x\n", objInst->timeSlotNum);
    
    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_decodeLoadDataInit(ITS_INT choice)
{ 
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.swdmMsg.u.loadInit.swDescr;
    NM_SWDM_LOAD_DATA_INIT *loadInit = &msg.u.formMsg.u.swdmMsg.u.loadInit;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x10, choice, 0x00, 0xff, 0xff, 0xff, 0x42,
                              0x12, 0x00, 0x02, 0x01, 0x01, 0x13, 0x00, 0x02, 0x01, 0x01, 
                              0x39, 0x01, 0x22, 0x02
                            }; 
    
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Load Data Initiate Failed  ret :: %d\n", ret);
        return ret; 
    }
    else
    {
        printf("Decoding Load Data Initiate Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice); 
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf(" FileId Len : %02x\n", swDescr->fileIdLen);
    for (i = 0; i < swDescr->fileIdLen; i++)
    {
        printf(" FileId[%d]  : %02x\n", i, swDescr->fileId[i]);  
    }

    printf(" File Ver   : %02x\n", swDescr->fileVerLen);
    for (i = 0; i < swDescr->fileVerLen; i++)
    {
        printf(" Version[%d] : %02x\n", i, swDescr->fileVer[i]);
    }

    printf(" Winsize    : %02x\n", loadInit->winSize);

    if (msg.u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_INTIATE_NACK)
    {
        printf(" nackCause  : %02x\n", loadInit->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_decodeLoadDataSeg(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SWDM_LOAD_DATA_SEG *loadSeg = &msg.u.formMsg.u.swdmMsg.u.loadSeg;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = {0x80, 0x00, 0x00, 0x08, choice, 0x00, 0xff, 0xff, 0xff, 0x47, 
                             0x00, 0x02, 0x01, 0x01, 0x22, 0x02};
                                                                                                                      
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Load Data Segment Failed  ret :: %d\n", ret);
        return ret; 
    }
    else
    {
        printf("Decoding Load Data Segment Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf(" Seg Len    : %02x\n", loadSeg->length);
    for (i = 0; i < loadSeg->length; i++)
    {
        printf("Seg Data[%d] : %02x\n", i, loadSeg->data[i]);
    }                                                                                                                               
    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_decodeLoadDataAbort(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = {0x80, 0x00, 0x00, 0x05, choice, 0x00, 0xff, 0xff, 0xff};
                                                                                                                                              
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Load Data Abort Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Load Data Abort Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_decodeLoadDataEnd(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.swdmMsg.u.loadEnd.swDescr;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = {0x80, 0x00, 0x00, 0x0e, choice, 0x00, 0xff, 0xff, 0xff, 0x42,
                             0x12, 0x00, 0x02, 0x01, 0x01, 0x13, 0x00, 0x00};                                                                                                                                         
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Data Request Failed  ret :: %d\n", ret);
    }
    else
    {
        printf("Decoding Data Request Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                       
    printf(" Id Len     : %02x\n", swDescr->fileIdLen);
    for (i = 0; i < swDescr->fileIdLen; i++)
    {
        printf(" FileId[%d]  : %02x\n", i, swDescr->fileId[i]);
    }                                                                                                                                        
    printf(" Ver  Len   : %02x\n", swDescr->fileVerLen);
    for (i = 0; i < swDescr->fileVerLen; i++)
    {
        printf(" Version[%d]  : %02x\n", swDescr->fileVer[i]);
    }

    if (msg.u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_END_NACK) 
    {                                                                                                              
        printf(" nackCause  : %02x\n", msg.u.formMsg.u.swdmMsg.u.loadEnd.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_decodeSwActiveReq(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG *msg;
    ITS_UINT ret = 0, i, j;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x3d, choice, 0x00, 0xff, 0xff, 0xff, 0x16,
                              0x00, 0x01, 0x17, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x01, 
                              0x01, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x01, 0x01, 0x00, 
                              0x02, 0x01, 0x01, 0x41, 0x00, 0x01, 0x42, 0x12, 0x00,
                              0x02, 0x01, 0x01, 0x13, 0x00, 0x02, 0x01, 0x01, 0x42, 0x12,
                              0x00, 0x00, 0x13, 0x00, 0x00};
                                                                                               
    msg = (ABIS_NETWORK_MANAGEMENT_MSG *)malloc(sizeof(ABIS_NETWORK_MANAGEMENT_MSG));
    ret = ABIS_NMM_Decode(msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding SW Activated Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding SW Activated Request Success  ret :: %d\n\n", ret);
    }
    ret = NM_decodeFomCommonElements(msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf(" sw len     : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length);

    for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length; j++)
    {
        printf(" swId len   : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileIdLen); 
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileIdLen; i++)
        {
            printf(" file Id[%d] : %02x\n", i, msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileId[i]);
        }

        printf(" Ver Len    : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVerLen);
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVerLen; i++)
        {
            printf(" Version[%d] : %02x\n", i, msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVer[i]);
        }
    }

    printf(" hwLen      : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length);

    for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length; j++)
    {
        printf(" hwId Len   : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipIdLen);
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipIdLen; i++)
        {
            printf(" Id[%d]      : %02x\n", i, msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipId[i]);
        }
                                                                                                                                              
        printf(" Type Len   : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipTypeLen);
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipTypeLen; i++)
        {
            printf(" Type[%d]    : %02x\n", i, msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipType[i]);
        }

        printf(" ver Len    : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVerLen);
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVerLen; i++)
        {
            printf(" version[%d] : %02x\n", i, msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVer[i]);
        }

        printf(" locLen     : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].locLen);
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].locLen; i++)
        {
            printf(" loc[%d]     : %02x\n", i, msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].location[i]);
        }

        printf(" infoLen    : %02x\n", msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].infoLen);
        for (i = 0; i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].infoLen; i++)
        {
            printf(" hwInfo[%d]  : %02x\n", i, msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].info[i]);
        }
    }

    if(msg->u.formMsg.formGenElemnts.msgType == NM_SW_ACTIVATE_REQUEST_NACK)
    {
        printf("nackCause :%02x", msg->u.formMsg.u.swdmMsg.u.actReq.nackCuase);   
    }

    free(msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc);
    free(msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc);
    free(msg);

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_decodeActivateSw(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.swdmMsg.u.actSw.swDescr;
    NM_SWDM_ACTIVE_SW *actSw = &msg.u.formMsg.u.swdmMsg.u.actSw;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = {0x80, 0x00, 0x00, 0x11, choice, 0x00, 0xff,
                             0xff, 0xff, 0x42, 0x12, 0x00, 0x02, 0x01,
                             0x01, 0x13, 0x00, 0x01, 0x02, 0x22, 0xcd
                            };                                                                                                                                        
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Activate SW Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Activate SW Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_SWDM_AS_SW_DESCRIPTION((&msg)))
    {
        printf(" %02x\n", swDescr->fileIdLen);
        for (i = 0; i < swDescr->fileIdLen; i++)
        {
            printf(" %02x\n", swDescr->fileId[i]);
        }
                                                                                                                                              
        printf(" %02x\n", swDescr->fileVerLen);
        for (i = 0; i < swDescr->fileVerLen; i++)
        {
           printf(" %02x\n",  swDescr->fileVer[i]);
        }
    }                                                                                                                   
    
    if (msg.u.formMsg.formGenElemnts.msgType == NM_ACTIVATE_SW_NACK)
    {
        printf(" %02x\n", actSw->nackCuase);
    }
   
    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_decodeEstablishTei(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_ABIM_ESTABLISH_TEI *estaTei = &msg.u.formMsg.u.abisMsg.u.estaTei;
    ABIS_CHANNEL *abisChanl = &msg.u.formMsg.u.abisMsg.abisChanl;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0b, choice, 0x00, 0xff, 0xff, 0xff, 0x34,
                              0x01, 0x01, 0x02, 0x02, 0x02};
    ITS_UINT ret = 0, i;                                                                                                                                  
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Establish TEI Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Establish TEI Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                       
    printf("teiVal      : %02x\n", estaTei->teiVal);
    if (msg.u.formMsg.formGenElemnts.msgType == NM_ESTABLISH_TEI_NACK)
    { 
        printf("nackCuase   : %02x\n", estaTei->nackCuase);
    }

    printf("btsPortNum  : %02x\n", abisChanl->btsPortNum);
    printf("timeSlotNum : %02x\n", abisChanl->timeSlotNum);
    printf("subSlotNum  : %02x\n", abisChanl->subSlotNum);
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_decodeConnTerrSign(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ABIS_CHANNEL *abisChanl = &msg.u.formMsg.u.abisMsg.abisChanl;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg.u.formMsg.formGenElemnts;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x09, choice, 0x00, 0xff, 0xff, 0xff, 0x01,
                              0x02, 0x02, 0x02, 0x22, 0x02};
    ITS_UINT ret = 0, i;                                                                                                                                  
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Connection Terristrial Signalling Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Connection Terristrial Signalling Success  ret :: %d\n\n", ret);
    }
                                                                                                                      
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                              
    printf("btsPortNum  : %02x\n", abisChanl->btsPortNum);
    printf("timeSlotNum : %02x\n", abisChanl->timeSlotNum);
    printf("subSlotNum  : %02x\n", abisChanl->subSlotNum);
    if ((formGenElemnts->msgType == NM_CONNECT_TERRESTRIAL_SIGNALLING_NACK) ||
        (formGenElemnts->msgType == NM_DISCONNECT_TERRESTRIAL_SIGNALLING_NACK))
    {
        printf("nackCuase   : %02x\n", msg.u.formMsg.u.abisMsg.u.connTerr.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_decodeConnTerrTraffic(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ABIS_CHANNEL *abisChanl = &msg.u.formMsg.u.abisMsg.abisChanl;
    NM_ABIM_CONN_TERR_TRAFFIC *connTraf = &msg.u.formMsg.u.abisMsg.u.connTraf;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0b, choice, 0x00, 0xff, 0xff, 0xff, 0x01,
                              0x00, 0x00, 0x00, 0x2c, 0x00};
    ITS_UINT ret = 0, i;                                                                                                                                      
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Connection Terristrial Traffic Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Connection Terristrial Traffic Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                       
    printf("btsPortNum  : %02x\n", abisChanl->btsPortNum);
    printf("timeSlotNum : %02x\n", abisChanl->timeSlotNum);
    printf("subSlotNum  : %02x\n", abisChanl->subSlotNum);
 
    if (IS_PRESENT_NM_AM_CTT_RADIO_SUB_CHANNEL((&msg)))
    {
        printf("radioSubChanl : %02x\n", connTraf->radioSubChanl);
    }
   
    if ((msg.u.formMsg.formGenElemnts.msgType == NM_CONNECT_TERRESTRIAL_TRAFFIC_NACK) ||
        (msg.u.formMsg.formGenElemnts.msgType == NM_DISCONNECT_TERRESTRIAL_TRAFFIC_NACK))
    {
        printf("nackCuase : %02x\n", connTraf->nackCuase);
    }
   
    return ITS_SUCCESS;
}

static ITS_INT
NM_TRM_decodeConnMultiDropLink(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    MD_BSC_LINK *bscLink = &msg.u.formMsg.u.transMsg.u.conLink.bscLink;
    MD_NEXT_BTS_LINK *btsLink = &msg.u.formMsg.u.transMsg.u.conLink.btsLink;
    NM_TRM_CON_MULTI_DROP_LINK *conLink = &msg.u.formMsg.u.transMsg.u.conLink;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0d, choice, 0x00, 0xff, 0xff, 0xff, 0x20,
                              0x01, 0x01, 0x21, 0x02, 0x02, 0x22, 0x02};
                                                                                       
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Connection Multi-drop Link Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Connection Multi-drop Link Success  ret :: %d\n\n", ret);
    }
                                                                                                                           
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                            
    printf("btsPortNum  : %02x\n", bscLink->btsPortNum);
    printf("timeSlotNum : %02x\n", bscLink->timeSlotNum);

    printf("btsPortNum  : %02x\n", btsLink->btsPortNum);
    printf("timeSlotNum : %02x\n", btsLink->timeSlotNum);
    
    if ((msg.u.formMsg.formGenElemnts.msgType == NM_CONNECT_MULTI_DROP_LINK_NACK) ||
        (msg.u.formMsg.formGenElemnts.msgType == NM_DISCONNECT_MULTI_DROP_LINK_NACK))
    {
        printf("nackCuase   : %02x\n", conLink->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_decodeSetBtsAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;

    NM_AIM_SET_BTS_ATTR *btsAttr = &msg.u.formMsg.u.airMsg.u.btsAttr;
    INTER_LEVEL_BOUND *interLevel = &msg.u.formMsg.u.airMsg.u.btsAttr.interLevel;
    CON_FAIL_CRITERION *conFail = &msg.u.formMsg.u.airMsg.u.btsAttr.conFail;
    T200 *t200 = &msg.u.formMsg.u.airMsg.u.btsAttr.t200;
    OVERLOAD_PERIOD *overldPeriod = &msg.u.formMsg.u.airMsg.u.btsAttr.overldPeriod;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x4a, choice, 0x00, 0xff, 0xff,
                              0xff, 0x19, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                              0x18, 0x02, 0x0e, 0x00, 0x03, 0x03, 0x03, 0x03,
                              0x33, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
                              0x1f, 0x05, 0x25, 0x00, 0x02, 0x06, 0x06, 0x0c,
                              0x07, 0x0b, 0x08, 0x2a, 0x09, 0x2b, 0x00, 0x0a,
                              0x0a, 0x11, 0x22, 0x23, 0x33, 0x44, 0x08, 0x00,
                              0x0d, 0x09, 0x0e, 0x2d, 0x88, 0x32, 0x00, 0x0f,
                              0x3A, 0xf1, 0xf2, 0xf3, 0xf4, 0x3B, 0x05, 0x03,
                              0x03, 0x03, 0x03, 0x03, 0x3C, 0xff
                            };
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Set BTS Attributes Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Set BTS Attributes Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                          
    if (IS_PRESENT_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES((&msg)))
    {
        printf("interfBound0 : %02x\n", interLevel->interfBound0);
        printf("interfBound1 : %02x\n", interLevel->interfBound1);
        printf("interfBound2 : %02x\n", interLevel->interfBound2);
        printf("interfBound3 : %02x\n", interLevel->interfBound3);
        printf("interfBound4 : %02x\n", interLevel->interfBound4);
        printf("interfBound5 : %02x\n", interLevel->interfBound5);     
    }

    if (IS_PRESENT_NM_AIM_SBA_INTAVE_PARAMETER((&msg)))
    {
        printf("intaveParam : %02x\n", btsAttr->intaveParam);
    }

    if (IS_PRESENT_NM_AIM_SBA_CONN_FAILURE_CRITERION((&msg)))
    {
        printf("length : %02x\n", conFail->length);
        printf("failCrit : %02x\n", conFail->failCrit);
        for (i = 0; i < conFail->length; i++)
        {
            printf("critVal[%d] : %02x\n", i, conFail->critVal[i]);
        }  
    }

    if (IS_PRESENT_NM_AIM_SBA_T200((&msg)))
    {
        printf("sdcch      : %02x\n", t200->sdcch);
        printf("facchFull  : %02x\n", t200->facchFull);
        printf("facchHalf  : %02x\n", t200->facchHalf);
        printf("sacchSap10 : %02x\n", t200->sacchSap10);
        printf("sacchSdcch : %02x\n", t200->sacchSdcch);
        printf("sdcchSap13 : %02x\n", t200->sdcchSap13);
        printf("sacchSap13 : %02x\n", t200->sacchSap13);
    }

    if (IS_PRESENT_NM_AIM_SBA_MAX_TIMING_ADVANCE((&msg)))
    {
        printf("maxTimeAdv : %02x\n", btsAttr->maxTimeAdv);
    }

    if (IS_PRESENT_NM_AIM_SBA_OVERLOAD_PERIOD((&msg)))
    {
        printf("overldPeriod length : %02x\n", overldPeriod->length);
        for (i = 0; i < overldPeriod->length; i++)
        {
            printf("period[%d] : %02x\n", i, overldPeriod->period[i]);
        } 
    }

    if (IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_THRESHOLD((&msg)))
    {
        printf("threshold : %02x\n", btsAttr->threshold);
    }

    if (IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD((&msg)))
    {
        printf("initPeriod : %02x\n", btsAttr->initPeriod);
    }

    if (IS_PRESENT_NM_AIM_SBA_RACH_BUSY_THRESHOLD((&msg)))
    {
        printf("busyThreshold : %02x\n", btsAttr->busyThreshold);
    }

    if (IS_PRESENT_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS((&msg)))
    {
        printf("avgSlots : %02x\n", btsAttr->avgSlots);
    }

    if (IS_PRESENT_NM_AIM_SBA_BTS_AIR_TIMER((&msg)))
    {
        printf("airT3105 : %02x\n", btsAttr->airT3105.tch);
        printf("airT3105 : %02x\n", btsAttr->airT3105.sdcch);
    }

    if (IS_PRESENT_NM_AIM_SBA_NY1((&msg)))
    {
        printf("ny1 : %02x\n", btsAttr->ny1.tch);
        printf("ny1 : %02x\n", btsAttr->ny1.sdcch);
    }

    if (IS_PRESENT_NM_AIM_SBA_BCCH_ARFCN((&msg)))
    {
        printf("arfcn : %02x\n", btsAttr->arfcn);
    }

    if (IS_PRESENT_NM_AIM_SBA_BSIC((&msg)))
    {
        printf("bsic : %02x\n", btsAttr->bsic);
    }

    if (IS_PRESENT_NM_AIM_SBA_RF_MAX_POWER_REDUCTION((&msg)))
    {
        printf("RF Max Power reduction : %02x\n", btsAttr->powerRedn);
    }

    if (IS_PRESENT_NM_AIM_SBA_STARTING_TIME((&msg)))
    {
        printf("startCurFrameNo : %02x\n", btsAttr->startCurFrameNo);
    }

    if (msg.u.formMsg.formGenElemnts.msgType == NM_SET_BTS_ATTRIBUTES_NACK)
    {
        printf("nackCuase : %02x\n", btsAttr->nackCuase); 
    }

    if (IS_PRESENT_NM_AIM_SBA_PAGING_AG_PARAMS((&msg)))
    {
        printf("bsPaMfrms : %02x\n", btsAttr->pageAgParams.bsPaMfrms);
        printf("bsCcchChans : %02x\n", btsAttr->pageAgParams.bsCcchChans);
        printf("bsAgRes : %02x\n", btsAttr->pageAgParams.bsAgRes);
        printf("pageAlg : %02x\n", btsAttr->pageAgParams.pageAlg);
    }
                                                                                
    if (IS_PRESENT_NM_AIM_SBA_SYST_INFO_LIST((&msg)))
    {
        printf("length : %02x\n", btsAttr->systInfoList.len);
        for (i = 0; i < btsAttr->systInfoList.len; i++)
        {
            printf("SI-x[%d] : %02x\n", i, btsAttr->systInfoList.six[i]);
        }
    }
                                                                                
    if (IS_PRESENT_NM_AIM_SBA_FN_OFFSET((&msg)))
    {
        printf("fnOffset : %02x\n", btsAttr->fnOffset);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_decodeSetRadioCarrierAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_AIM_SET_RADIO_ATTR *radioAttr = &msg.u.formMsg.u.airMsg.u.radioAttr;
    ARFCN_LIST  *arfcnList = &msg.u.formMsg.u.airMsg.u.radioAttr.arfcnList;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0a, choice, 0x00, 0xff, 0xff, 0xff, 0x2d,
                              0x00, 0x05, 0x00, 0x00};
                                                                                                                                              
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Set Radio Carrier Attributes Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Set Radio Carrier Attributes Success  ret :: %d\n\n", ret);
    }
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION((&msg)))
    {
        printf(" powerRedu  : %02x\n", radioAttr->powerRedu);
    }

    if (IS_PRESENT_NM_AIM_SRCA_ARFCN_LIST((&msg)))
    { 
        printf(" length     : %02x\n", arfcnList->length);
        for (i = 0; i < arfcnList->length; i++)
        {
            printf("arfcn[%d] : %02x\n", i, arfcnList->arfcn[i]);
        }
    }
  
    if (msg.u.formMsg.formGenElemnts.msgType == NM_SET_RADIO_CARRIER_ATTRIBUTES_NACK)
    {
        printf("NackCause : %02x", radioAttr->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_decodeSetChanlAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_AIM_SET_CHANNEL_ATTR *chanlAttr = &msg.u.formMsg.u.airMsg.u.chanlAttr;
    ARFCN_LIST *arfcnList = &msg.u.formMsg.u.airMsg.u.chanlAttr.arfcnList;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x20, choice, 0x00, 0xff, 0xff,
                              0xff, 0x0d, 0x00, 0x15, 0x00, 0x1b, 0x05, 0x88,
                              0x88, 0x88, 0x88, 0x88, 0x05, 0x00, 0x03, 0x00,
                              0x04, 0x00, 0x04, 0x00, 0x04, 0x32, 0x00, 0x05,
                              0x40, 0x06, 0x2d, 0x88
                            };
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Set Channel Attributes Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Set Channel Attributes Success  ret :: %d\n\n", ret);
    }
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_AIM_SCA_CHANNEL_COMBINATION((&msg)))
    {
        printf("chanlComb : %02x\n", chanlAttr->chanlComb);
    }

    if (IS_PRESENT_NM_AIM_SCA_HSN((&msg)))
    {
        printf("hsn : %02x\n", chanlAttr->hsn);
    } 

    if (IS_PRESENT_NM_AIM_SCA_MAIO((&msg)))
    {
        for (i = 0; i < chanlAttr->maioList.len; i++)
        {
            printf("maio[%d] : %02x\n", i, chanlAttr->maioList.maio[i]);
        }
    }

    if (IS_PRESENT_NM_AIM_SCA_ARFCN_LIST((&msg)))
    {
        printf("length : %02x\n", arfcnList->length);
        for (i = 0; i < arfcnList->length; i++)
        {
            printf("arfcn[%d] : %02x\n", i, arfcnList->arfcn[i]);
        } 
    }

    if (IS_PRESENT_NM_AIM_SCA_STARTING_TIME((&msg)))
    {
        printf("startCurFrameNo : %02x\n", chanlAttr->startCurFrameNo);
    }

    if (IS_PRESENT_NM_AIM_SCA_TSC((&msg)))
    {
        printf("tscSeqCode : %02x\n", chanlAttr->tscSeqCode);
    }

    if (IS_PRESENT_NM_AIM_SCA_RF_MAX_POWER_REDUCTION((&msg)))
    {
        printf("RF Max Power Reduction : %02x\n", chanlAttr->powerRedn);
    }

    if (msg.u.formMsg.formGenElemnts.msgType == NM_SET_CHANNEL_ATTRIBUTES_NACK)
    {
        printf("nackCuase : %02x\n", chanlAttr->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_decodePerformTest(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_TM_PERFORM_TEST *perfTest = &msg.u.formMsg.u.testMsg.u.perfTest;
    PHYSICAL_CONFIG *phyContext = &msg.u.formMsg.u.testMsg.u.perfTest.phyContext; 
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0f, choice, 0x00, 0xff, 0xff, 0xff, 0x36,
                              0x01, 0x06, 0x00, 0x35, 0x00, 0x00, 0x26, 0x00, 0x00};

    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Perform Test Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Perform Test Success  ret :: %d\n\n", ret);
    }
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("testNum : %02x\n", msg.u.formMsg.u.testMsg.testNum);
    printf("autoRep : %02x\n", perfTest->autoRep);

    if (IS_PRESENT_NM_TM_PT_TEST_DURATION((&msg)))
    {
        printf("testDura : %02x\n", perfTest->testDura);
    }

    if (IS_PRESENT_NM_TM_PT_PHYSICAL_CONFIGURATION((&msg)))
    {
        printf("length : %02x\n", phyContext->length);
        for (i = 0; i < phyContext->length; i++)
        {
            printf("testConfig[%d] : %02x\n", i,  phyContext->testConfig[i]);
        } 
    }

    if (msg.u.formMsg.formGenElemnts.msgType == NM_PERFORM_TEST_NACK)
    {
        printf("nackCause : %02x", perfTest->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_decodeTestReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_TM_TEST_REP *testRep = &msg.u.formMsg.u.testMsg.u.testRep;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0d, choice, 0x00, 0xff, 0xff, 0xff, 0x36,
                              0x01, 0x37, 0x00, 0x03, 0x02, 0x02, 0x02};                                                                                                                                         
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Test Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Test Report Success  ret :: %d\n\n", ret);
    }
                                                                                                                                              
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("testNum : %02x\n", msg.u.formMsg.u.testMsg.testNum);

    printf("length : %02x\n", testRep->length);
    for (i = 0; i < testRep->length; i++)
    {
        printf("resultInfo[%d] : %02x\n", i, testRep->resultInfo[i]);
    } 

    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_decodeSendTestReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x07, choice, 0x00, 0xff, 0xff, 0xff, 0x36, 0x01};                                                                                                                                              
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Send Test Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Send Test Report Success  ret :: %d\n\n", ret);
    }
                                                                                                                
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                 
    printf("testNum : %02x\n",msg.u.formMsg.u.testMsg.testNum);

    if ((msg.u.formMsg.formGenElemnts.msgType == NM_SEND_TEST_REPORT_NACK) ||
        (msg.u.formMsg.formGenElemnts.msgType == NM_STOP_TEST_NACK))
    {
        printf("nackCause : %02x", msg.u.formMsg.u.testMsg.u.sendRep.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_decodeStateChangdEventRep(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_STATE_CHNG_EVENT_REP *changeEv = &msg.u.formMsg.u.stateMsg.u.changeEv;
    AVAILABILITY_STATUS *availStat = &msg.u.formMsg.u.stateMsg.u.changeEv.availStat;
    SITE_INPUTS *siteInputs = &msg.u.formMsg.u.stateMsg.u.changeEv.siteInputs;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0f, choice, 0x00, 0xff, 0xff, 0xff, 0x46,
                              0x00, 0x07, 0x00, 0x00, 0x1c, 0x00, 0x2e, 0x00, 0x00};
                                                                                                             
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding State Changed Event Report Failed ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding State Changed Event Report Success ret :: %d\n\n", ret);
    }
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_SM_SCER_OPERATIONAL_STATE((&msg)))
    {
        printf("operanStat : %02x\n", changeEv->operanStat);
    }

    if (IS_PRESENT_NM_SM_SCER_AVAILABILITY_STATE((&msg)))
    {
        printf("length : %02x\n", availStat->length);
        for (i = 0; i < availStat->length; i++)
        {
            printf("status[%d] : %02x\n", i, availStat->status[i]);
        }
    }

    if (IS_PRESENT_NM_SM_SCER_MAN_DEP_STATE((&msg)))
    { 
        printf("mfdDepen : %02x\n", changeEv->mfdDepen);
    }

    if (IS_PRESENT_NM_SM_SCER_SITE_INPUTS((&msg)))
    {
        printf(" length : %02x\n", siteInputs->length);
        for (i = 0; i < siteInputs->length; i++)
        {
            printf("attr[%d].state : %02x\n", i, siteInputs->attr[i].state);
            printf("attr[%d].input : %02x\n", i, siteInputs->attr[i].input);
        }
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_decodeFailureEventReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_FAIL_EVENT_REP *failEv = &msg.u.formMsg.u.stateMsg.u.failEv;
    PROBABLE_CAUSE *probCause = &msg.u.formMsg.u.stateMsg.u.failEv.probCause;
    ADDITIONAL_TEXT *addText = &msg.u.formMsg.u.stateMsg.u.failEv.addText;
    ADDITIONAL_INFO *addInfo = &msg.u.formMsg.u.stateMsg.u.failEv.addInfo;
    HW_DESCRIPTION *hwDescr = &msg.u.formMsg.u.stateMsg.u.failEv.hwDescr;
    SW_DESCRIPTION *swDescr = &msg.u.formMsg.u.stateMsg.u.failEv.swDescr;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x29, choice, 0x00, 0xff, 0xff, 0xff, 0x11,
                              0x00, 0x43, 0x00, 0x29, 0x00, 0x00, 0x00, 0x31, 0x00, 0x17, 
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                              0x42, 0x12, 0x00, 0x00, 0x13, 0x00, 0x00, 0x03, 0x00, 0x00, 
                              0x02, 0x00, 0x00, 0x24, 0x00};
                                                                                                                
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Failure Event Report Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Failure Event Report Success  ret :: %d\n\n", ret);
    }
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                           
    printf("evtType     : %02x\n", failEv->evtType);
    printf("percvdSever : %02x\n", failEv->percvdSever);
    printf("type        : %02x\n", failEv->probCause.type);
    printf("value       : %02x\n", failEv->probCause.value);

    if (IS_PRESENT_NM_SM_FER_SPECIFIC_PROBLEMS((&msg)))
    {
        printf("specProbs : %02x\n", failEv->specProbs);
    }

    if (IS_PRESENT_NM_SM_FER_HW_DESCRIPTION((&msg)))
    { 
        printf("equipIdLen : %02x\n", hwDescr->equipIdLen);
        for (i = 0; i < hwDescr->equipIdLen; i++)
        {
            printf("equipId[%d] : %02x\n", i, hwDescr->equipId[i]);
        }

        printf("equipTypeLen : %02x\n", hwDescr->equipTypeLen);
        for (i = 0; i < hwDescr->equipTypeLen; i++)
        {
            printf("equipType[%d] : %02x\n", i, hwDescr->equipType[i]);
        }
    
        printf("equipVerLen : %02x\n", hwDescr->equipVerLen);
        for (i = 0; i < hwDescr->equipVerLen; i++)
        {
            printf("equipVer[%d] : %02x\n", i, hwDescr->equipVer[i]);
        }
    
        printf("locLen : %02x\n", hwDescr->locLen);
        for (i = 0; i < hwDescr->locLen; i++)
        {
            printf("location[%d] : %02x\n", i, hwDescr->location[i]);
        }
    
        printf("infoLen : %02x\n", hwDescr->infoLen);
        for (i = 0; i < hwDescr->infoLen; i++)
        {
            printf("info[%d] : %02x\n", i, hwDescr->info[i]);
        }
    } 
    
    if (IS_PRESENT_NM_SM_FER_SW_DESCRIPTION((&msg)))
    {
        printf("fileIdLen : %02x\n", swDescr->fileIdLen);
        for (i = 0; i < swDescr->fileIdLen; i++)
        {
            printf("fileId[%d] : %02x\n", i, swDescr->fileId[i]);
        }

        printf("fileVerLen : %02x\n", swDescr->fileVerLen);
        for (i = 0; i < swDescr->fileVerLen; i++)
        {
            printf("fileVer[%d] : %02x\n", swDescr->fileVer[i]);
        }
    }

    if (IS_PRESENT_NM_SM_FER_ADDITIONAL_TEXT((&msg)))
    {
        printf("addText length : %02x\n", addText->length);
        for (i = 0; i < addText->length; i++)
        {
            printf("addText value[%d] : %02x\n", i, addText->value[i]);
        }
    }

    if (IS_PRESENT_NM_SM_FER_ADDITIONAL_INFO((&msg)))
    {
        printf("addInfo length : %02x\n", addInfo->length);
        for (i = 0; i < addInfo->length; i++)
        {
            printf("addInfo value[%d] : %02x\n", i, addInfo->value[i]);
        }
    }

    if (IS_PRESENT_NM_SM_FER_OUTSTANDING_ALARM_SEQ((&msg)))
    {
        printf("alarmSeq : %02x\n", failEv->alarmSeq);
    } 
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_decodeStopSendEventReport(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_STOP_SEND_EVENT_REP *stopEv = &msg.u.formMsg.u.stateMsg.u.stopEv;
    AVAILABILITY_STATUS *availStat = &msg.u.formMsg.u.stateMsg.u.stopEv.availStat;
    PROBABLE_CAUSE *probCause = &msg.u.formMsg.u.stateMsg.u.stopEv.probCause;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x12, choice, 0x00, 0xff, 0xff, 0xff, 0x46,
                              0x00, 0x07, 0x00, 0x00, 0x1c, 0x00, 0x29, 0x00, 0x00, 0x00,
                              0x31, 0x00};                                                                                                                                             
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Stop Sending Event Rep Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Stop Sending Event Rep Success  ret :: %d\n\n", ret);
    }
                                                                                                                                              
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_SM_SSER_OPERATIONAL_STATE((&msg)))
    {  
        printf("operanStat : %02x\n", stopEv->operanStat);
    }

    if (IS_PRESENT_NM_SM_SSER_AVAILABILTY_STATE((&msg))) 
    {
        printf("length : %02x\n", availStat->length);
        for (i = 0; i < availStat->length; i++)
        {
            printf("status[%d] : %02x\n", i, availStat->status[i]);
        }
    }

    if (IS_PRESENT_NM_SM_SSER_MFD_DEP_STATE((&msg)))
    {
        printf("mfdDepen : %02x\n", stopEv->mfdDepen);
    }

    if (IS_PRESENT_NM_SM_SSER_PROBABLE_CAUSE((&msg)))
    {
        printf("type : %02x\n", probCause->type);
        printf("value : %02x\n", probCause->value);
    }

    if (IS_PRESENT_NM_SM_SSER_SPECIFIC_PROBLEMS((&msg)))
    {
        printf("specProbs : %02x\n", stopEv->specProbs);
    }
   
    if ((msg.u.formMsg.formGenElemnts.msgType == NM_STOP_SENDING_EVENT_REPORTS_NACK) ||
        (msg.u.formMsg.formGenElemnts.msgType == NM_RESTART_SENDING_EVENT_REPORTS_NACK))
    {
        printf("nackCuase : %02x\n", stopEv->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_decodeChangeAdminState(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_CHNG_ADMIN_STATE *state = &msg.u.formMsg.u.stateMsg.u.state;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x07, choice, 0x00, 0xff, 0xff, 0xff, 0x69,
                              0x01};
                                                                                                                      
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Change Admin State Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Change Admin State Success  ret :: %d\n\n", ret);
    }                                                                                                                                   
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    printf("adminStat : %02x\n", state->adminStat);
    
    if ((msg.u.formMsg.formGenElemnts.msgType == NM_CHANGE_ADMINISTRATIVE_STATE_NACK) ||
        (msg.u.formMsg.formGenElemnts.msgType == NM_CHANGE_ADMINISTRATIVE_STATE_REQUEST_NACK))
    {
        printf("nackCuase : %02x\n", state->nackCuase);
    }
    
    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_decodeChangeover(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    SOURCE *src = &msg.u.formMsg.u.equipMsg.u.changeOver.src;
    DESTINATION *dest = &msg.u.formMsg.u.equipMsg.u.changeOver.dest;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0f, choice, 0x00, 0xff, 0xff, 0xff, 0x30,
                              0x00, 0x02, 0x01, 0x01, 0x0f, 0x00, 0x02, 0x01, 0x01};
                                                                                                              
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Changeover Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Changeover Success  ret :: %d\n\n", ret);
    }
                                                                                                                   
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                       
    printf("src length : %02x\n", src->length);
    for (i = 0; i < src->length; i++)
    {
        printf("value[%d] : %02x\n", i, src->value[i]);
    }

    printf("dest length : %02x\n", dest->length);
    for (i = 0; i < dest->length; i++)
    {
        printf("value[%d] : %02x\n", i, dest->value[i]);
    }

    if (msg.u.formMsg.formGenElemnts.msgType == NM_CHANGEOVER_NACK)
    {
        printf("nackCuase : %02x\n", msg.u.formMsg.u.equipMsg.u.changeOver.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_decodeOpstart(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x05, choice, 0x00, 0xff, 0xff, 0xff};                                                                                                                                              
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Opstart Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Opstart Success  ret :: %d\n\n", ret);
    }
                                                                                                              
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                    
    if (msg.u.formMsg.formGenElemnts.msgType == NM_OPSTART_NACK)
    {
        printf("nackCause : %02x", msg.u.formMsg.u.equipMsg.u.opStart.nackCuase);
    }
                                                                                          
    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_decodeSetSiteOutputs(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_EM_SET_SITE_OUTPUTS *siteOutput = &msg.u.formMsg.u.equipMsg.u.siteOutput;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0a, choice, 0x00, 0xff, 0xff, 0xff, 0x2f,
                              0x00, 0x02, 0x01, 0x01};
                                                                                                                
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Set Site Outputs Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Set Site Outputs Success  ret :: %d\n\n", ret);
    }
                                                                                                                   
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("length : %02x\n", siteOutput->length);
    for (i = 0; i < siteOutput->length; i++)
    {
        printf("output[%d] : %02x\n", i, siteOutput->output[i]);
    } 
 
    if ((msg.u.formMsg.formGenElemnts.msgType == NM_SET_SITE_OUTPUTS_NACK) ||
        (msg.u.formMsg.formGenElemnts.msgType == NM_CHANGE_HW_CONFIGURATION_NACK))
    {
        printf("nackCuase : %02x\n", siteOutput->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_decodeGetAttr(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_MS_GET_ATTR *getAttr = &msg.u.formMsg.u.miscMsg.u.getAttr;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0a, choice, 0x00, 0xff, 0xff, 0xff, 0x1a,
                              0x00, 0x02, 0x01, 0x01};
                                                                                                                 
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Get Attributes Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Get Attributes Success  ret :: %d\n\n", ret);
    }
                                                                                                                                              
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                          
    printf("length : %02x\n", getAttr->length);
    for (i = 0; i < getAttr->length; i++)
    {
        printf("atrrId[%d] : %02x\n", i, getAttr->atrrId[i]);
    }
    
    if (msg.u.formMsg.formGenElemnts.msgType == NM_GET_ATTRIBUTES_NACK)   
    {
        printf("nackCuase : %02x\n", getAttr->nackCuase);
    }
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_decodeGetAttrResp(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_MS_GET_ATTR_RESP *getAttrResp = &msg.u.formMsg.u.miscMsg.u.getAttrResp;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0e, choice, 0x00, 0xff, 0xff, 0xff, 0x44,
                              0x00, 0x05, 0x02, 0x01, 0x01, 0x02, 0x02, 0x02};                                                                                                                                  
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Get Attributes Resp Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Get Attributes Resp Success  ret :: %d\n\n", ret);
    }
                                                                                                                                              
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                             
    printf("length      : %02x\n", getAttrResp->length);
    printf("notRepCount : %02x\n", getAttrResp->notRepCount);

    for (i = 0; i < getAttrResp->length; i++)
    {
        printf("notRep[%d]   : %02x\n", i, getAttrResp->notRep[i]);
        printf("reported[%d] : %02x\n", i, getAttrResp->reported[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_decodeSetAlarmThreshold(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    POWER_OUTPUT_THRESHOLD *powerOutput =
                   &msg.u.formMsg.u.miscMsg.u.alarmThresh.powerOutput;
    PROBABLE_CAUSE *probCause = &msg.u.formMsg.u.miscMsg.u.alarmThresh.probCause;
    VSWR_THRESHOLD *vswr = &msg.u.formMsg.u.miscMsg.u.alarmThresh.vswr;
    MFD_THRESHOLDS *mfdThresh = &msg.u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x15, choice, 0x00, 0xff, 0xff, 0xff, 0x29,
                              0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 
                              0x1d, 0x00, 0x00, 0x22, 0xcd };

    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Get Attribute Resp Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Get Attribute Resp Success  ret :: %d\n\n", ret);
    }
                                                                                                                                              
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("type  : %02x\n", probCause->type);
    printf("value : %02x\n", probCause->value);

    if (IS_PRESENT_NM_MM_SAT_POWER_OUTPUT_THRESHOLD((&msg)))
    {
        printf("fault     : %02x\n", powerOutput->fault);
        printf("reduced   : %02x\n", powerOutput->reduced);
        printf("excessive : %02x\n", powerOutput->excessive);
    }

    if (IS_PRESENT_NM_MM_SAT_VSWR_THRESHOLDS((&msg)))
    {
        printf("faulty      : %02x\n", vswr->faulty);
        printf("notAdjusted : %02x\n", vswr->notAdjusted);
    } 

    if (IS_PRESENT_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS((&msg)))
    {
        printf("length : %02x\n", mfdThresh->length);
        for (i = 0; i < mfdThresh->length; i++)
        {
            printf("mfdDependnt[%d] : %02x\n", i, mfdThresh->mfdDependnt[i]);
        }
    }

    if (msg.u.formMsg.formGenElemnts.msgType == NM_SET_ALARM_THRESHOLD_NACK)
    {
        printf("nackCuase : %02x\n", msg.u.formMsg.u.miscMsg.u.alarmThresh.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_decodeReinitialise(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    HW_DESCRIPTION *hwDesc = &msg.u.formMsg.u.equipMsg.u.reInit.hwDesc; 
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x10, choice, 0x00, 0xff, 0xff, 0xff, 0x17,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};                                                                                                                                      
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding  Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding  Success  ret :: %d\n\n", ret);
    }
                                                                                      
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
 
    if (IS_PRESENT_NM_EM_REIN_HW_DESCRIPTION((&msg)))
    {
        printf("equipIdLen : %02x\n", hwDesc->equipIdLen);
        for (i = 0; i < hwDesc->equipIdLen; i++)
        {
            printf("equipId[%d] : %02x\n", i, hwDesc->equipId[i]);
        }
                                                                                                                                              
        printf("equipTypeLen : %02x\n", hwDesc->equipTypeLen);
        for (i = 0; i < hwDesc->equipTypeLen; i++)
        {
            printf("equipType[%d] : %02x\n", i, hwDesc->equipType[i]);
        }                                                                                                                                   
        printf("equipVerLen : %02x\n", hwDesc->equipVerLen);
        for (i = 0; i < hwDesc->equipVerLen; i++)
        {
            printf("equipVer[%d] : %02x\n", i, hwDesc->equipVer[i]);
        }                                                                                                                                     
        printf("locLen : %02x\n", hwDesc->locLen);
        for (i = 0; i < hwDesc->locLen; i++)
        {
            printf("location[%d] : %02x\n", i, hwDesc->location[i]);
        }                                                                                                                                     
        printf("infoLen : %02x\n", hwDesc->infoLen);
        for (i = 0; i < hwDesc->infoLen; i++)
        {
            printf("info[%d] : %02x\n", i, hwDesc->info[i]);
        }
    }
   
    if (msg.u.formMsg.formGenElemnts.msgType == NM_REINITIALIZE_NACK)
    {
        printf("nackCause : %02x\n", msg.u.formMsg.u.equipMsg.u.reInit.nackCuase);
    }
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_decodeMeasResultReq(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x07, choice, 0x00, 0xff, 0xff, 0xff, 0x49,
                              0x01};
                                                                                                                 
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Measurement Result Request Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Measurement Result Request Success  ret :: %d\n\n", ret);
    }                                                                                                                                           
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    printf(" measId : %02x\n", msg.u.formMsg.u.measMsg.measId);

    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_decodeMeasResultResp(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_MM__MEAS_RES_RESP *measResp = &msg.u.formMsg.u.measMsg.u.measResp;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x0d, choice, 0x00, 0xff, 0xff, 0xff, 0x49,
                              0x01, 0x48, 0x00, 0x03, 0x02, 0x02, 0x02};                                                                                                                                          
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Measurement Result Resp Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Measurement Result Resp Success  ret :: %d\n\n", ret);
    }

    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("measId : %02x\n", msg.u.formMsg.u.measMsg.measId);

    printf("length : %02x\n", measResp->length);
    for (i = 0; i < measResp->length; i++)
    {
        printf("measResult[%d] : %02x\n", i, measResp->measResult[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_decodeReportOutstandAlarms(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x05, choice, 0x00, 0xff, 0xff, 0xff};
                                                                                                               
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding Report Outstanding Alarm Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding Report Outstanding Alarm Success  ret :: %d\n\n", ret);
    }
                                                                                                                     
    ret = NM_decodeFomCommonElements(&msg, choice);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
   
    if (msg.u.formMsg.formGenElemnts.msgType ==
        NM_REPORT_OUTSTANDING_ALARMS_NACK)
    {
        printf("nackCause : %02x\n", msg.u.formMsg.u.stateMsg.u.repAlarm.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_decodeTrxHello(ITS_INT choice)
{
    ABIS_NETWORK_MANAGEMENT_MSG msg;
    NM_SM_TRX_HELLO *trxHello = &msg.u.formMsg.u.stateMsg.u.trxHello;
    ITS_UINT ret = 0, i;
    ITS_OCTET buffer[100] = { 0x80, 0x00, 0x00, 0x33, choice, 0x00, 0xff, 0xff,
                              0xff, 0xaa, 0xaa, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,
                              0xbb, 0x42, 0x00, 0x04, 0xcc, 0xcc, 0xcc, 0xcc,
                              0x00, 0x04, 0xdd, 0xdd, 0xdd, 0xdd, 0x00, 0x03,
                              0x11, 0x11, 0x11, 0x00, 0x03,
                              0x22, 0x22, 0x22, 0x00, 0x03, 0x33, 0x33, 0x33,
                              0x00, 0x03, 0x44, 0x44, 0x44, 0x00, 0x03, 0x55,
                              0x55, 0x55
                            };
                                                                                
    ret = ABIS_NMM_Decode(&msg, 100, buffer);
                                                                                
    if (ret != ITS_SUCCESS)
    {
        printf("Decoding TRX Hello Failed  ret :: %d\n", ret);
        return ret;
    }
    else
    {
        printf("Decoding TRX Hello Success  ret :: %d\n\n", ret);
    }
                                                                                
    ret = NM_decodeFomCommonElements(&msg, choice);
                                                                                
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                
    printf("OnM Protocol version X : %02x\n", trxHello->onmProtoVer.versionX);
    printf("OnM Protocol version Y : %02x\n", trxHello->onmProtoVer.versionY);
                                                                                
    printf("hwCapab.freqHop: %02x\n", trxHello->hwCapab.freqHop);
    printf("hwCapab.diversity: %02x\n", trxHello->hwCapab.diversity);
    printf("hwCapab.powClassSu: %02x\n", trxHello->hwCapab.powClassSup);
    printf("hwCapab.freqBan: %02x\n", trxHello->hwCapab.freqBand);
    printf("hwCapab.lsclAvail: %02x\n", trxHello->hwCapab.lsclAvail);
    printf("hwCapab.memoryCap: %02x\n", trxHello->hwCapab.memoryCapb);
                                                                                
    if (IS_PRESENT_NM_SM_TRX_HELLO_SW_DESC((&msg)))
    {
        printf("swDesc.fileIdLen : %02x\n", trxHello->swDesc.fileIdLen);
        for (i = 0; i < trxHello->swDesc.fileIdLen; i++)
        {
            printf("swDesc.fileId[%d] : %02x\n", i, trxHello->swDesc.fileId[i]);        }
        printf("swDesc.fileVerLen : %02x\n", i,  trxHello->swDesc.fileVerLen);
        for (i = 0; i < trxHello->swDesc.fileVerLen; i++)
        {
            printf("swDesc.fileVer[%d] : %02x\n", i,
                                  trxHello->swDesc.fileVer[i]);
        }
    }
                                                                                
    if (IS_PRESENT_NM_SM_TRX_HELLO_HW_DESC((&msg)))
    {
        printf("equipIdLen : %02x\n", trxHello->hwDesc.equipIdLen);
        for (i = 0; i < trxHello->hwDesc.equipIdLen; i++)
        {
            printf("equipId[%d] : %02x\n", i, trxHello->hwDesc.equipId[i]);
        }
                                                                                
        printf("equipTypeLen : %02x\n", trxHello->hwDesc.equipTypeLen);
        for (i = 0; i < trxHello->hwDesc.equipTypeLen; i++)
        {
            printf("equipType[%d] : %02x\n", i, trxHello->hwDesc.equipType[i]);
        }
                                                                                
        printf("equipVerLen : %02x\n", trxHello->hwDesc.equipVerLen);
        for (i = 0; i < trxHello->hwDesc.equipVerLen; i++)
        {
            printf("equipVer[%d] : %02x\n", i, trxHello->hwDesc.equipType[i]);
        }
                                                                                
        printf("locLen : %02x\n", trxHello->hwDesc.locLen);
        for (i = 0; i < trxHello->hwDesc.locLen; i++)
        {
            printf("location[%d] : %02x\n", i, trxHello->hwDesc.location[i]);
        }
                                                                                
        printf("infoLen : %02x\n", trxHello->hwDesc.infoLen);
        for (i = 0; i < trxHello->hwDesc.infoLen; i++)
        {
            printf("info[%d] : %02x\n", i, trxHello->hwDesc.info[i]);
        }
    }
                                                                                
    return ITS_SUCCESS;
}

static ITS_INT
reserved(ITS_INT choice)
{
    printf("Reserved/Invalid  Message Type \n");                                                                                                                              
    return ITS_SUCCESS;
}

ITS_INT (*testNetworkEncodeMsg[MAX_NETWORK_FUNS_SIZE])(ITS_INT) = {
                            reserved,                         /* 0x00 */
                            NM_SWDM_encodeLoadDataInit,       /* 0x01 */
                            NM_SWDM_encodeLoadDataInit,       /* 0x02 */
                            NM_SWDM_encodeLoadDataInit,       /* 0x03 */
                            NM_SWDM_encodeLoadDataSeg,        /* 0x04 */
                            NM_SWDM_encodeLoadDataSeg,        /* 0x05 */
                            NM_SWDM_encodeLoadDataAbort,      /* 0x06 */
                            NM_SWDM_encodeLoadDataEnd,        /* 0x07 */
                            NM_SWDM_encodeLoadDataEnd,        /* 0x08 */
                            NM_SWDM_encodeLoadDataEnd,        /* 0x09 */
                            NM_SWDM_encodeSwActiveReq,        /* 0x0A */
                            NM_SWDM_encodeSwActiveReq,        /* 0x0B */
                            NM_SWDM_encodeSwActiveReq,        /* 0x0C */
                            NM_SWDM_encodeActivateSw,         /* 0x0D */
                            NM_SWDM_encodeActivateSw,         /* 0x0E */
                            NM_SWDM_encodeActivateSw,         /* 0x0F */
                            NM_SWDM_encodeLoadDataAbort,       /* 0x10 */
                            reserved,                         /* 0x11 */
                            reserved,                         /* 0x12 */
                            reserved,                         /* 0x13 */
                            reserved,                         /* 0x14 */
                            reserved,                         /* 0x15 */
                            reserved,                         /* 0x16 */
                            reserved,                         /* 0x17 */
                            reserved,                         /* 0x18 */
                            reserved,                         /* 0x19 */
                            reserved,                         /* 0x1A */
                            reserved,                         /* 0x1B */
                            reserved,                         /* 0x1C */
                            reserved,                         /* 0x1D */
                            reserved,                         /* 0x1E */
                            reserved,                         /* 0x1F */
                            reserved,                         /* 0x20 */
                            NM_ABIM_encodeEstablishTei,       /* 0x21 */
                            NM_ABIM_encodeEstablishTei,       /* 0x22 */
                            NM_ABIM_encodeEstablishTei,       /* 0x23 */
                            NM_ABIM_encodeConnTerrSign,       /* 0x24 */
                            NM_ABIM_encodeConnTerrSign,       /* 0x25 */
                            NM_ABIM_encodeConnTerrSign,       /* 0x26 */
                            NM_ABIM_encodeConnTerrSign,       /* 0x27 */
                            NM_ABIM_encodeConnTerrSign,       /* 0x28 */
                            NM_ABIM_encodeConnTerrSign,       /* 0x29 */
                            NM_ABIM_encodeConnTerrTraffic,    /* 0x2A */
                            NM_ABIM_encodeConnTerrTraffic,    /* 0x2B */
                            NM_ABIM_encodeConnTerrTraffic,    /* 0x2C */
                            NM_ABIM_encodeConnTerrTraffic,    /* 0x2D */
                            NM_ABIM_encodeConnTerrTraffic,    /* 0x2E */
                            NM_ABIM_encodeConnTerrTraffic,    /* 0x2F */
                            reserved,                         /* 0x30 */
                            NM_TRM_encodeConnMultiDropLink,   /* 0x31 */
                            NM_TRM_encodeConnMultiDropLink,   /* 0x32 */
                            NM_TRM_encodeConnMultiDropLink,   /* 0x33 */
                            NM_TRM_encodeConnMultiDropLink,   /* 0x34 */
                            NM_TRM_encodeConnMultiDropLink,   /* 0x35 */
                            NM_TRM_encodeConnMultiDropLink,   /* 0x36 */
                            reserved,                         /* 0x37 */
                            reserved,                         /* 0x38 */
                            reserved,                         /* 0x39 */
                            reserved,                         /* 0x3A */
                            reserved,                         /* 0x3B */
                            reserved,                         /* 0x3C */
                            reserved,                         /* 0x3D */
                            reserved,                         /* 0x3E */
                            reserved,                         /* 0x3F */
                            reserved,                         /* 0x40 */
                            NM_AIM_encodeSetBtsAttr,          /* 0x41 */
                            NM_AIM_encodeSetBtsAttr,          /* 0x42 */
                            NM_AIM_encodeSetBtsAttr,          /* 0x43 */
                            NM_AIM_encodeSetRadioCarrierAttr, /* 0x44 */
                            NM_AIM_encodeSetRadioCarrierAttr, /* 0x45 */
                            NM_AIM_encodeSetRadioCarrierAttr, /* 0x46 */
                            NM_AIM_encodeSetChanlAttr,        /* 0x47 */
                            NM_AIM_encodeSetChanlAttr,        /* 0x48 */
                            NM_AIM_encodeSetChanlAttr,        /* 0x49 */
                            reserved,                         /* 0x4A */
                            reserved,                         /* 0x4B */
                            reserved,                         /* 0x4C */
                            reserved,                         /* 0x4D */
                            reserved,                         /* 0x4E */
                            reserved,                         /* 0x4F */
                            reserved,                         /* 0x50 */
                            NM_TM_encodePerformTest,          /* 0x51 */
                            NM_TM_encodePerformTest,          /* 0x52 */
                            NM_TM_encodePerformTest,          /* 0x53 */
                            NM_TM_encodeTestReport,           /* 0x54 */
                            NM_TM_encodeSendTestReport,       /* 0x55 */
                            NM_TM_encodeSendTestReport,       /* 0x56 */
                            NM_TM_encodeSendTestReport,       /* 0x57 */
                            NM_TM_encodeSendTestReport,       /* 0x58 */
                            NM_TM_encodeSendTestReport,       /* 0x59 */
                            NM_TM_encodeSendTestReport,       /* 0x5A */
                            reserved,                         /* 0x5B */
                            reserved,                         /* 0x5C */
                            reserved,                         /* 0x5D */
                            reserved,                         /* 0x5E */
                            reserved,                         /* 0x5F */
                            reserved,                         /* 0x60 */
                            NM_SM_encodeStateChangdEventRep,  /* 0x61 */
                            NM_SM_encodeFailureEventReport,   /* 0x62 */
                            NM_SM_encodeStopSendEventReport,  /* 0x63 */
                            NM_SM_encodeStopSendEventReport,  /* 0x64 */
                            NM_SM_encodeStopSendEventReport,  /* 0x65 */
                            NM_SM_encodeStopSendEventReport,  /* 0x66 */
                            NM_SM_encodeStopSendEventReport,  /* 0x67 */
                            NM_SM_encodeStopSendEventReport,  /* 0x68 */
                            NM_SM_encodeChangeAdminState,     /* 0x69 */
                            NM_SM_encodeChangeAdminState,     /* 0x6A */
                            NM_SM_encodeChangeAdminState,     /* 0x6B */
                            NM_SM_encodeChangeAdminState,     /* 0x6C */
                            NM_SM_encodeChangeAdminState,     /* 0x6D */
                            NM_SM_encodeChangeAdminState,     /* 0x6E */
                            reserved,                         /* 0x6F */
                            reserved,                         /* 0x70 */
                            NM_EM_encodeChangeover,           /* 0x71 */
                            NM_EM_encodeChangeover,           /* 0x72 */
                            NM_EM_encodeChangeover,           /* 0x73 */
                            NM_EM_encodeOpstart,              /* 0x74 */
                            NM_EM_encodeOpstart,              /* 0x75 */
                            NM_EM_encodeOpstart,              /* 0x76 */
                            NM_EM_encodeSetSiteOutputs,       /* 0x77 */
                            NM_EM_encodeSetSiteOutputs,       /* 0x78 */
                            NM_EM_encodeSetSiteOutputs,       /* 0x79 */
                            reserved,                         /* 0x7A */
                            reserved,                         /* 0x7B */
                            reserved,                         /* 0x7C */
                            reserved,                         /* 0x7D */
                            reserved,                         /* 0x7E */
                            reserved,                         /* 0x7F */
                            reserved,                         /* 0x80 */
                            NM_MM_encodeGetAttr,              /* 0x81 */
                            NM_MM_encodeGetAttrResp,          /* 0x82 */
                            NM_MM_encodeGetAttr,              /* 0x83 */
                            NM_MM_encodeSetAlarmThreshold,    /* 0x84 */
                            NM_MM_encodeSetAlarmThreshold,    /* 0x85 */
                            NM_MM_encodeSetAlarmThreshold,    /* 0x86 */
                            NM_EM_encodeReinitialise,         /* 0x87 */
                            NM_EM_encodeReinitialise,         /* 0x88 */
                            NM_EM_encodeReinitialise,         /* 0x89 */
                            NM_MM_encodeMeasResultReq,        /* 0x8A */
                            NM_MM_encodeMeasResultResp,       /* 0x8B */
                            NM_MM_encodeMeasResultReq,        /* 0x8C */
                            NM_MM_encodeMeasResultReq,        /* 0x8D */
                            reserved,                         /* 0x8E */
                            reserved,                         /* 0x8F */
                            NM_EM_encodeSetSiteOutputs,       /* 0x90 */
                            NM_EM_encodeSetSiteOutputs,       /* 0x91 */
                            NM_EM_encodeSetSiteOutputs,       /* 0x92 */
                            NM_SM_encodeReportOutstandAlarms, /* 0x93 */
                            NM_SM_encodeReportOutstandAlarms, /* 0x94 */
                            NM_SM_encodeReportOutstandAlarms, /* 0x95 */
                            reserved,                         /* 0x96 */
                            reserved,                         /* 0x97 */
                            reserved,                         /* 0x98 */
                            reserved,                         /* 0x99 */
                            reserved,                         /* 0x9A */
                            reserved,                         /* 0x9B */
                            reserved,                         /* 0x9C */
                            reserved,                         /* 0x9D */
                            reserved,                         /* 0x9E */
                            reserved,                         /* 0x9F */
                            NM_SM_encodeTrxHello              /* 0xA0 */
                            };

ITS_INT (*testNetworkDecodeMsg[MAX_NETWORK_FUNS_SIZE])(ITS_INT) = {
                            reserved,                         /* 0x00 */
                            NM_SWDM_decodeLoadDataInit,       /* 0x01 */
                            NM_SWDM_decodeLoadDataInit,       /* 0x02 */
                            NM_SWDM_decodeLoadDataInit,       /* 0x03 */
                            NM_SWDM_decodeLoadDataSeg,        /* 0x04 */
                            NM_SWDM_decodeLoadDataSeg,        /* 0x05 */
                            NM_SWDM_decodeLoadDataAbort,      /* 0x06 */
                            NM_SWDM_decodeLoadDataEnd,        /* 0x07 */
                            NM_SWDM_decodeLoadDataEnd,        /* 0x08 */
                            NM_SWDM_decodeLoadDataEnd,        /* 0x09 */
                            NM_SWDM_decodeSwActiveReq,        /* 0x0A */
                            NM_SWDM_decodeSwActiveReq,        /* 0x0B */
                            NM_SWDM_decodeSwActiveReq,        /* 0x0C */
                            NM_SWDM_decodeActivateSw,         /* 0x0D */
                            NM_SWDM_decodeActivateSw,         /* 0x0E */
                            NM_SWDM_decodeActivateSw,         /* 0x0F */
                            NM_SWDM_decodeLoadDataAbort,       /* 0x10 */
                            reserved,                         /* 0x11 */
                            reserved,                         /* 0x12 */
                            reserved,                         /* 0x13 */
                            reserved,                         /* 0x14 */
                            reserved,                         /* 0x15 */
                            reserved,                         /* 0x16 */
                            reserved,                         /* 0x17 */
                            reserved,                         /* 0x18 */
                            reserved,                         /* 0x19 */
                            reserved,                         /* 0x1A */
                            reserved,                         /* 0x1B */
                            reserved,                         /* 0x1C */
                            reserved,                         /* 0x1D */
                            reserved,                         /* 0x1E */
                            reserved,                         /* 0x1F */
                            reserved,                         /* 0x20 */
                            NM_ABIM_decodeEstablishTei,       /* 0x21 */
                            NM_ABIM_decodeEstablishTei,       /* 0x22 */
                            NM_ABIM_decodeEstablishTei,       /* 0x23 */
                            NM_ABIM_decodeConnTerrSign,       /* 0x24 */
                            NM_ABIM_decodeConnTerrSign,       /* 0x25 */
                            NM_ABIM_decodeConnTerrSign,       /* 0x26 */
                            NM_ABIM_decodeConnTerrSign,       /* 0x27 */
                            NM_ABIM_decodeConnTerrSign,       /* 0x28 */
                            NM_ABIM_decodeConnTerrSign,       /* 0x29 */
                            NM_ABIM_decodeConnTerrTraffic,    /* 0x2A */
                            NM_ABIM_decodeConnTerrTraffic,    /* 0x2B */
                            NM_ABIM_decodeConnTerrTraffic,    /* 0x2C */
                            NM_ABIM_decodeConnTerrTraffic,    /* 0x2D */
                            NM_ABIM_decodeConnTerrTraffic,    /* 0x2E */
                            NM_ABIM_decodeConnTerrTraffic,    /* 0x2F */
                            reserved,                         /* 0x30 */
                            NM_TRM_decodeConnMultiDropLink,   /* 0x31 */
                            NM_TRM_decodeConnMultiDropLink,   /* 0x32 */
                            NM_TRM_decodeConnMultiDropLink,   /* 0x33 */
                            NM_TRM_decodeConnMultiDropLink,   /* 0x34 */
                            NM_TRM_decodeConnMultiDropLink,   /* 0x35 */
                            NM_TRM_decodeConnMultiDropLink,   /* 0x36 */
                            reserved,                         /* 0x37 */
                            reserved,                         /* 0x38 */
                            reserved,                         /* 0x39 */
                            reserved,                         /* 0x3A */
                            reserved,                         /* 0x3B */
                            reserved,                         /* 0x3C */
                            reserved,                         /* 0x3D */
                            reserved,                         /* 0x3E */
                            reserved,                         /* 0x3F */
                            reserved,                         /* 0x40 */
                            NM_AIM_decodeSetBtsAttr,          /* 0x41 */
                            NM_AIM_decodeSetBtsAttr,          /* 0x42 */
                            NM_AIM_decodeSetBtsAttr,          /* 0x43 */
                            NM_AIM_decodeSetRadioCarrierAttr, /* 0x44 */
                            NM_AIM_decodeSetRadioCarrierAttr, /* 0x45 */
                            NM_AIM_decodeSetRadioCarrierAttr, /* 0x46 */
                            NM_AIM_decodeSetChanlAttr,        /* 0x47 */
                            NM_AIM_decodeSetChanlAttr,        /* 0x48 */
                            NM_AIM_decodeSetChanlAttr,        /* 0x49 */
                            reserved,                         /* 0x4A */
                            reserved,                         /* 0x4B */
                            reserved,                         /* 0x4C */
                            reserved,                         /* 0x4D */
                            reserved,                         /* 0x4E */
                            reserved,                         /* 0x4F */
                            reserved,                         /* 0x50 */
                            NM_TM_decodePerformTest,          /* 0x51 */
                            NM_TM_decodePerformTest,          /* 0x52 */
                            NM_TM_decodePerformTest,          /* 0x53 */
                            NM_TM_decodeTestReport,           /* 0x54 */
                            NM_TM_decodeSendTestReport,       /* 0x55 */
                            NM_TM_decodeSendTestReport,       /* 0x56 */
                            NM_TM_decodeSendTestReport,       /* 0x57 */
                            NM_TM_decodeSendTestReport,       /* 0x58 */
                            NM_TM_decodeSendTestReport,       /* 0x59 */
                            NM_TM_decodeSendTestReport,       /* 0x5A */
                            reserved,                         /* 0x5B */
                            reserved,                         /* 0x5C */
                            reserved,                         /* 0x5D */
                            reserved,                         /* 0x5E */
                            reserved,                         /* 0x5F */
                            reserved,                         /* 0x60 */
                            NM_SM_decodeStateChangdEventRep,  /* 0x61 */
                            NM_SM_decodeFailureEventReport,   /* 0x62 */
                            NM_SM_decodeStopSendEventReport,  /* 0x63 */
                            NM_SM_decodeStopSendEventReport,  /* 0x64 */
                            NM_SM_decodeStopSendEventReport,  /* 0x65 */
                            NM_SM_decodeStopSendEventReport,  /* 0x66 */
                            NM_SM_decodeStopSendEventReport,  /* 0x67 */
                            NM_SM_decodeStopSendEventReport,  /* 0x68 */
                            NM_SM_decodeChangeAdminState,     /* 0x69 */
                            NM_SM_decodeChangeAdminState,     /* 0x6A */
                            NM_SM_decodeChangeAdminState,     /* 0x6B */
                            NM_SM_decodeChangeAdminState,     /* 0x6C */
                            NM_SM_decodeChangeAdminState,     /* 0x6D */
                            NM_SM_decodeChangeAdminState,     /* 0x6E */
                            reserved,                         /* 0x6F */
                            reserved,                         /* 0x70 */
                            NM_EM_decodeChangeover,           /* 0x71 */
                            NM_EM_decodeChangeover,           /* 0x72 */
                            NM_EM_decodeChangeover,           /* 0x73 */
                            NM_EM_decodeOpstart,              /* 0x74 */
                            NM_EM_decodeOpstart,              /* 0x75 */
                            NM_EM_decodeOpstart,              /* 0x76 */
                            NM_EM_decodeSetSiteOutputs,       /* 0x77 */
                            NM_EM_decodeSetSiteOutputs,       /* 0x78 */
                            NM_EM_decodeSetSiteOutputs,       /* 0x79 */
                            reserved,                         /* 0x7A */
                            reserved,                         /* 0x7B */
                            reserved,                         /* 0x7C */
                            reserved,                         /* 0x7D */
                            reserved,                         /* 0x7E */
                            reserved,                         /* 0x7F */
                            reserved,                         /* 0x80 */
                            NM_MM_decodeGetAttr,              /* 0x81 */
                            NM_MM_decodeGetAttrResp,          /* 0x82 */
                            NM_MM_decodeGetAttr,              /* 0x83 */
                            NM_MM_decodeSetAlarmThreshold,    /* 0x84 */
                            NM_MM_decodeSetAlarmThreshold,    /* 0x85 */
                            NM_MM_decodeSetAlarmThreshold,    /* 0x86 */
                            NM_EM_decodeReinitialise,         /* 0x87 */
                            NM_EM_decodeReinitialise,         /* 0x88 */
                            NM_EM_decodeReinitialise,         /* 0x89 */
                            NM_MM_decodeMeasResultReq,        /* 0x8A */
                            NM_MM_decodeMeasResultResp,       /* 0x8B */
                            NM_MM_decodeMeasResultReq,        /* 0x8C */
                            NM_MM_decodeMeasResultReq,        /* 0x8D */
                            reserved,                         /* 0x8E */
                            reserved,                         /* 0x8F */
                            NM_EM_decodeSetSiteOutputs,       /* 0x90 */
                            NM_EM_decodeSetSiteOutputs,       /* 0x91 */
                            NM_EM_decodeSetSiteOutputs,       /* 0x92 */
                            NM_SM_decodeReportOutstandAlarms, /* 0x93 */
                            NM_SM_decodeReportOutstandAlarms, /* 0x94 */
                            NM_SM_decodeReportOutstandAlarms, /* 0x95 */
                            reserved,                         /* 0x96 */
                            reserved,                         /* 0x97 */
                            reserved,                         /* 0x98 */
                            reserved,                         /* 0x99 */
                            reserved,                         /* 0x9A */
                            reserved,                         /* 0x9B */
                            reserved,                         /* 0x9C */
                            reserved,                         /* 0x9D */
                            reserved,                         /* 0x9E */
                            reserved,                         /* 0x9F */
                            NM_SM_decodeTrxHello              /* 0xA0 */
                            };
