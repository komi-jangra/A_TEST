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
 *  ID: $Id: abis_network_management_printIE.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
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
 *  Revision 1.1.2.3  2006/04/07 09:31:53  yranade
 *  RF Max Power Reduction IE Added (sgavalkar)
 *
 *  Revision 1.1.2.2  2006/03/28 09:17:10  yranade
 *  TRX Hello message added. (sgavalkar)
 *
 *  Revision 1.1.2.1  2005/08/16 11:41:53  mkrishna
 *  Added Initial version after unit testing.
 *
 *
 ****************************************************************************/

#include <abis_network_management.h>

ITS_INT (*Print_Network_Msg[MAX_NETWORK_FUNS_SIZE])
               (ABIS_NETWORK_MANAGEMENT_MSG *msg);

void
Print_Abis_Network_Management_Msg(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_OCTET msgType = msg->u.formMsg.formGenElemnts.msgType;
                                                                                
    (Print_Network_Msg[msgType])(msg);
}

static ITS_INT
NM_PrintCommonElements(ABIS_NETWORK_MANAGEMENT_MSG *msg)
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
NM_SWDM_PrintLoadDataInit(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{ 
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr;
    NM_SWDM_LOAD_DATA_INIT *loadInit = &msg->u.formMsg.u.swdmMsg.u.loadInit;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg); 
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

    if (msg->u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_INTIATE_NACK)
    {
        printf(" nackCause  : %02x\n", loadInit->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_PrintLoadDataSeg(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_SWDM_LOAD_DATA_SEG *loadSeg = &msg->u.formMsg.u.swdmMsg.u.loadSeg;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
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
NM_SWDM_PrintLoadDataAbort(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_UINT ret = 0;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_PrintLoadDataEnd(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.loadEnd.swDescr;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
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

    if (msg->u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_END_NACK) 
    {                                                                                                              
        printf(" nackCause  : %02x\n",
                msg->u.formMsg.u.swdmMsg.u.loadEnd.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SWDM_PrintSwActiveReq(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_UINT ret = 0, i, j;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf(" sw len     : %02x\n",
                         msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length);

    for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.length; j++)
    {
        printf(" swId len   : %02x\n",
            msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileIdLen); 
        for (i = 0;
             i < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileIdLen;
             i++)
        {
            printf(" file Id[%d] : %02x\n",
            i, msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileId[i]);
        }

        printf(" Ver Len    : %02x\n",
             msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVerLen);
        for (i = 0;
            i < msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVerLen;
            i++)
        {
            printf(" Version[%d] : %02x\n", i,
              msg->u.formMsg.u.swdmMsg.u.actReq.swConfig.swDesc[j].fileVer[i]);
        }
    }

    printf(" hwLen      : %02x\n",
                          msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length);

    for (j = 0; j < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.length; j++)
    {
        printf(" hwId Len   : %02x\n",
              msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipIdLen);
        for (i = 0;
            i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipIdLen;
            i++)
        {
            printf(" Id[%d]      : %02x\n", i,
              msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipId[i]);
        }

        printf(" Type Len   : %02x\n",
            msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipTypeLen);
        for (i = 0;
          i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipTypeLen;
          i++)
        {
            printf(" Type[%d]    : %02x\n", i,
             msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipType[i]);
        }

        printf(" ver Len    : %02x\n",
             msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVerLen);
        for (i = 0;
           i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVerLen;
           i++)
        {
            printf(" version[%d] : %02x\n", i,
              msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].equipVer[i]);
        }

        printf(" locLen     : %02x\n",
                  msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].locLen);
        for (i = 0;
          i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].locLen; i++)
        {
            printf(" loc[%d]     : %02x\n", i,
              msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].location[i]);
        }

        printf(" infoLen    : %02x\n",
                 msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].infoLen);
        for (i = 0;
             i < msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].infoLen;
             i++)
        {
            printf(" hwInfo[%d]  : %02x\n", i,
                 msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig.hwDesc[j].info[i]);
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
NM_SWDM_PrintActivateSw(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.actSw.swDescr;
    NM_SWDM_ACTIVE_SW *actSw = &msg->u.formMsg.u.swdmMsg.u.actSw;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_SWDM_AS_SW_DESCRIPTION(msg))
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

    if (msg->u.formMsg.formGenElemnts.msgType == NM_ACTIVATE_SW_NACK)
    {
        printf(" %02x\n", actSw->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_PrintEstablishTei(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_INT ret = 0;
    NM_ABIM_ESTABLISH_TEI *estaTei = &msg->u.formMsg.u.abisMsg.u.estaTei;
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("teiVal      : %02x\n", estaTei->teiVal);
    if (msg->u.formMsg.formGenElemnts.msgType == NM_ESTABLISH_TEI_NACK)
    { 
        printf("nackCause   : %02x\n", estaTei->nackCuase);
    }

    printf("btsPortNum  : %02x\n", abisChanl->btsPortNum);
    printf("timeSlotNum : %02x\n", abisChanl->timeSlotNum);
    printf("subSlotNum  : %02x\n", abisChanl->subSlotNum);
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_PrintConnTerrSign(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
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
        printf("nackCause   : %02x\n",
                msg->u.formMsg.u.abisMsg.u.connTerr.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_ABIM_PrintConnTerrTraffic(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
    NM_ABIM_CONN_TERR_TRAFFIC *connTraf = &msg->u.formMsg.u.abisMsg.u.connTraf;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("btsPortNum  : %02x\n", abisChanl->btsPortNum);
    printf("timeSlotNum : %02x\n", abisChanl->timeSlotNum);
    printf("subSlotNum  : %02x\n", abisChanl->subSlotNum);

    if (IS_PRESENT_NM_AM_CTT_RADIO_SUB_CHANNEL(msg))
    {
        printf("radioSubChanl : %02x\n", connTraf->radioSubChanl);
    }
   
    if ((msg->u.formMsg.formGenElemnts.msgType ==
                                       NM_CONNECT_TERRESTRIAL_TRAFFIC_NACK) ||
        (msg->u.formMsg.formGenElemnts.msgType ==
                                       NM_DISCONNECT_TERRESTRIAL_TRAFFIC_NACK))
    {
        printf("nackCause : %02x\n", connTraf->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_TRM_PrintConnMultiDropLink(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    MD_BSC_LINK *bscLink = &msg->u.formMsg.u.transMsg.u.conLink.bscLink;
    MD_NEXT_BTS_LINK *btsLink = &msg->u.formMsg.u.transMsg.u.conLink.btsLink;
    NM_TRM_CON_MULTI_DROP_LINK *conLink = &msg->u.formMsg.u.transMsg.u.conLink;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("btsPortNum  : %02x\n", bscLink->btsPortNum);
    printf("timeSlotNum : %02x\n", bscLink->timeSlotNum);

    printf("btsPortNum  : %02x\n", btsLink->btsPortNum);
    printf("timeSlotNum : %02x\n", btsLink->timeSlotNum);

    if ((msg->u.formMsg.formGenElemnts.msgType ==
                                       NM_CONNECT_MULTI_DROP_LINK_NACK) ||
        (msg->u.formMsg.formGenElemnts.msgType ==
                                        NM_DISCONNECT_MULTI_DROP_LINK_NACK))
    {
        printf("nackCause   : %02x\n", conLink->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_PrintSetBtsAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_AIM_SET_BTS_ATTR *btsAttr = &msg->u.formMsg.u.airMsg.u.btsAttr;
    INTER_LEVEL_BOUND *interLevel =
                        &msg->u.formMsg.u.airMsg.u.btsAttr.interLevel;
    CON_FAIL_CRITERION *conFail = &msg->u.formMsg.u.airMsg.u.btsAttr.conFail;
    T200 *t200 = &msg->u.formMsg.u.airMsg.u.btsAttr.t200;
    OVERLOAD_PERIOD *overldPeriod =
                        &msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES(msg))
    {
        printf("interfBound0 : %02x\n", interLevel->interfBound0);
        printf("interfBound1 : %02x\n", interLevel->interfBound1);
        printf("interfBound2 : %02x\n", interLevel->interfBound2);
        printf("interfBound3 : %02x\n", interLevel->interfBound3);
        printf("interfBound4 : %02x\n", interLevel->interfBound4);
        printf("interfBound5 : %02x\n", interLevel->interfBound5);     
    }

    if (IS_PRESENT_NM_AIM_SBA_INTAVE_PARAMETER(msg))
    {
        printf("intaveParam : %02x\n", btsAttr->intaveParam);
    }

    if (IS_PRESENT_NM_AIM_SBA_CONN_FAILURE_CRITERION(msg))
    {
        printf("length : %02x\n", conFail->length);
        printf("failCrit : %02x\n", conFail->failCrit);
        for (i = 0; i < conFail->length; i++)
        {
            printf("critVal[%d] : %02x\n", i, conFail->critVal[i]);
        }  
    }

    if (IS_PRESENT_NM_AIM_SBA_T200(msg))
    {
        printf("sdcch      : %02x\n", t200->sdcch);
        printf("facchFull  : %02x\n", t200->facchFull);
        printf("facchHalf  : %02x\n", t200->facchHalf);
        printf("sacchSap10 : %02x\n", t200->sacchSap10);
        printf("sacchSdcch : %02x\n", t200->sacchSdcch);
        printf("sdcchSap13 : %02x\n", t200->sdcchSap13);
        printf("sacchSap13 : %02x\n", t200->sacchSap13);
    }

    if (IS_PRESENT_NM_AIM_SBA_MAX_TIMING_ADVANCE(msg))
    {
        printf("maxTimeAdv : %02x\n", btsAttr->maxTimeAdv);
    }

    if (IS_PRESENT_NM_AIM_SBA_OVERLOAD_PERIOD(msg))
    {
        printf("overldPeriod length : %02x\n", overldPeriod->length);
        for (i = 0; i < overldPeriod->length; i++)
        {
            printf("period[%d] : %02x\n", i, overldPeriod->period[i]);
        } 
    }

    if (IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_THRESHOLD(msg))
    {
        printf("threshold : %02x\n", btsAttr->threshold);
    }

    if (IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD(msg))
    {
        printf("initPeriod : %02x\n", btsAttr->initPeriod);
    }

    if (IS_PRESENT_NM_AIM_SBA_RACH_BUSY_THRESHOLD(msg))
    {
        printf("busyThreshold : %02x\n", btsAttr->busyThreshold);
    }

    if (IS_PRESENT_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS(msg))
    {
        printf("avgSlots : %02x\n", btsAttr->avgSlots);
    }

    if (IS_PRESENT_NM_AIM_SBA_BTS_AIR_TIMER(msg))
    {
        printf("airT3105.tch : %02x\n", btsAttr->airT3105.tch);
        printf("airT3105.sdcch : %02x\n", btsAttr->airT3105.sdcch);
    }

    if (IS_PRESENT_NM_AIM_SBA_NY1(msg))
    {
        printf("ny1.tch : %02x\n", btsAttr->ny1.tch);
        printf("ny1.sdcch : %02x\n", btsAttr->ny1.sdcch);
    }

    if (IS_PRESENT_NM_AIM_SBA_BCCH_ARFCN(msg))
    {
        printf("arfcn : %02x\n", btsAttr->arfcn);
    }

    if (IS_PRESENT_NM_AIM_SBA_BSIC(msg))
    {
        printf("bsic : %02x\n", btsAttr->bsic);
    }

    if (IS_PRESENT_NM_AIM_SBA_RF_MAX_POWER_REDUCTION(msg))
    {
        printf("RF Max Power reduction : %02x\n", btsAttr->powerRedn);
    }

    if (IS_PRESENT_NM_AIM_SBA_STARTING_TIME(msg))
    {
        printf("startCurFrameNo : %02x\n", btsAttr->startCurFrameNo);
    }

    if (msg->u.formMsg.formGenElemnts.msgType == NM_SET_BTS_ATTRIBUTES_NACK)
    {
        printf("nackCause : %02x\n", btsAttr->nackCuase); 
    }

    if (IS_PRESENT_NM_AIM_SBA_PAGING_AG_PARAMS((msg)))
    {
        printf("bsPaMfrms : %02x\n", btsAttr->pageAgParams.bsPaMfrms);
        printf("bsCcchChans : %02x\n", btsAttr->pageAgParams.bsCcchChans);
        printf("bsAgRes : %02x\n", btsAttr->pageAgParams.bsAgRes);
        printf("pageAlg : %02x\n", btsAttr->pageAgParams.pageAlg);
    }
                                                                                
    if (IS_PRESENT_NM_AIM_SBA_SYST_INFO_LIST((msg)))
    {
        printf("length : %02x\n", btsAttr->systInfoList.len);
        for (i = 0; i < btsAttr->systInfoList.len; i++)
        {
            printf("SI-x[%d] : %02x\n", i, btsAttr->systInfoList.six[i]);
        }
    }
                                                                                
    if (IS_PRESENT_NM_AIM_SBA_FN_OFFSET((msg)))
    {
        printf("fnOffset : %02x\n", btsAttr->fnOffset);
    }


    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_PrintSetRadioCarrierAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_AIM_SET_RADIO_ATTR *radioAttr = &msg->u.formMsg.u.airMsg.u.radioAttr;
    ARFCN_LIST  *arfcnList = &msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION(msg))
    {
        printf(" powerRedu  : %02x\n", radioAttr->powerRedu);
    }

    if (IS_PRESENT_NM_AIM_SRCA_ARFCN_LIST(msg))
    { 
        printf(" length     : %02x\n", arfcnList->length);
        for (i = 0; i < arfcnList->length; i++)
        {
            printf("arfcn[%d] : %02x\n", i, arfcnList->arfcn[i]);
        }
    }
  
    if (msg->u.formMsg.formGenElemnts.msgType ==
                                        NM_SET_RADIO_CARRIER_ATTRIBUTES_NACK)
    {
        printf("NackCause : %02x", radioAttr->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_AIM_PrintSetChanlAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_AIM_SET_CHANNEL_ATTR *chanlAttr = &msg->u.formMsg.u.airMsg.u.chanlAttr;
    ARFCN_LIST *arfcnList = &msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_AIM_SCA_CHANNEL_COMBINATION(msg))
    {
        printf("chanlComb : %02x\n", chanlAttr->chanlComb);
    }

    if (IS_PRESENT_NM_AIM_SCA_HSN(msg))
    {
        printf("hsn : %02x\n", chanlAttr->hsn);
    } 

    if (IS_PRESENT_NM_AIM_SCA_MAIO(msg))
    {
        for (i = 0; i < chanlAttr->maioList.len; i++)
        {
            printf("maio[%d] : %02x\n", i, chanlAttr->maioList.maio[i]);
        }
    }

    if (IS_PRESENT_NM_AIM_SCA_ARFCN_LIST(msg))
    {
        printf("length : %02x\n", arfcnList->length);
        for (i = 0; i < arfcnList->length; i++)
        {
            printf("arfcn[%d] : %02x\n", i, arfcnList->arfcn[i]);
        } 
    }

    if (IS_PRESENT_NM_AIM_SCA_STARTING_TIME(msg))
    {
        printf("startCurFrameNo : %02x\n", chanlAttr->startCurFrameNo);
    }

    if (IS_PRESENT_NM_AIM_SCA_TSC(msg))
    {
        printf("tscSeqCode : %02x\n", chanlAttr->tscSeqCode);
    }

    if (IS_PRESENT_NM_AIM_SCA_RF_MAX_POWER_REDUCTION(msg))
    {
        printf("RF Max Power Reduction : %02x\n", chanlAttr->powerRedn);
    }
    
    if (msg->u.formMsg.formGenElemnts.msgType == NM_SET_CHANNEL_ATTRIBUTES_NACK)
    {
        printf("nackCause : %02x\n", chanlAttr->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_PrintPerformTest(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_TM_PERFORM_TEST *perfTest = &msg->u.formMsg.u.testMsg.u.perfTest;
    PHYSICAL_CONFIG *phyContext =
                              &msg->u.formMsg.u.testMsg.u.perfTest.phyContext; 
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("testNum : %02x\n", msg->u.formMsg.u.testMsg.testNum);
    printf("autoRep : %02x\n", perfTest->autoRep);

    if (IS_PRESENT_NM_TM_PT_TEST_DURATION(msg))
    {
        printf("testDura : %02x\n", perfTest->testDura);
    }

    if (IS_PRESENT_NM_TM_PT_PHYSICAL_CONFIGURATION(msg))
    {
        printf("length : %02x\n", phyContext->length);
        for (i = 0; i < phyContext->length; i++)
        {
            printf("testConfig[%d] : %02x\n", i,  phyContext->testConfig[i]);
        } 
    }

    if (msg->u.formMsg.formGenElemnts.msgType == NM_PERFORM_TEST_NACK)
    {
        printf("nackCause : %02x", perfTest->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_PrintTestReport(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_TM_TEST_REP *testRep = &msg->u.formMsg.u.testMsg.u.testRep;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("testNum : %02x\n", msg->u.formMsg.u.testMsg.testNum);

    printf("length : %02x\n", testRep->length);
    for (i = 0; i < testRep->length; i++)
    {
        printf("resultInfo[%d] : %02x\n", i, testRep->resultInfo[i]);
    } 

    return ITS_SUCCESS;
}

static ITS_INT
NM_TM_PrintSendTestReport(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("testNum : %02x\n",msg->u.formMsg.u.testMsg.testNum);

    if ((msg->u.formMsg.formGenElemnts.msgType == NM_SEND_TEST_REPORT_NACK) ||
        (msg->u.formMsg.formGenElemnts.msgType == NM_STOP_TEST_NACK))
    {
        printf("nackCause : %02x",
                                msg->u.formMsg.u.testMsg.u.sendRep.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_PrintStateChangdEventRep(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_UINT ret = 0, i;
    NM_SM_STATE_CHNG_EVENT_REP *changeEv =
                                         &msg->u.formMsg.u.stateMsg.u.changeEv;
    AVAILABILITY_STATUS *availStat =
                               &msg->u.formMsg.u.stateMsg.u.changeEv.availStat;
    SITE_INPUTS *siteInputs = &msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_SM_SCER_OPERATIONAL_STATE(msg))
    {
        printf("operanStat : %02x\n", changeEv->operanStat);
    }

    if (IS_PRESENT_NM_SM_SCER_AVAILABILITY_STATE(msg))
    {
        printf("length : %02x\n", availStat->length);
        for (i = 0; i < availStat->length; i++)
        {
            printf("status[%d] : %02x\n", i, availStat->status[i]);
        }
    }

    if (IS_PRESENT_NM_SM_SCER_MAN_DEP_STATE(msg))
    { 
        printf("mfdDepen : %02x\n", changeEv->mfdDepen);
    }

    if (IS_PRESENT_NM_SM_SCER_SITE_INPUTS(msg))
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
NM_SM_PrintFailureEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_SM_FAIL_EVENT_REP *failEv = &msg->u.formMsg.u.stateMsg.u.failEv;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.stateMsg.u.failEv.probCause;
    ADDITIONAL_TEXT *addText = &msg->u.formMsg.u.stateMsg.u.failEv.addText;
    ADDITIONAL_INFO *addInfo = &msg->u.formMsg.u.stateMsg.u.failEv.addInfo;
    HW_DESCRIPTION *hwDescr = &msg->u.formMsg.u.stateMsg.u.failEv.hwDescr;
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.stateMsg.u.failEv.swDescr;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("evtType     : %02x\n", failEv->evtType);
    printf("percvdSever : %02x\n", failEv->percvdSever);
    printf("type        : %02x\n", failEv->probCause.type);
    printf("value       : %02x\n", failEv->probCause.value);

    if (IS_PRESENT_NM_SM_FER_SPECIFIC_PROBLEMS(msg))
    {
        printf("specProbs : %02x\n", failEv->specProbs);
    }

    if (IS_PRESENT_NM_SM_FER_HW_DESCRIPTION(msg))
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
    
    if (IS_PRESENT_NM_SM_FER_SW_DESCRIPTION(msg))
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

    if (IS_PRESENT_NM_SM_FER_ADDITIONAL_TEXT(msg))
    {
        printf("addText length : %02x\n", addText->length);
        for (i = 0; i < addText->length; i++)
        {
            printf("addText value[%d] : %02x\n", i, addText->value[i]);
        }
    }

    if (IS_PRESENT_NM_SM_FER_ADDITIONAL_INFO(msg))
    {
        printf("addInfo length : %02x\n", addInfo->length);
        for (i = 0; i < addInfo->length; i++)
        {
            printf("addInfo value[%d] : %02x\n", i, addInfo->value[i]);
        }
    }

    if (IS_PRESENT_NM_SM_FER_OUTSTANDING_ALARM_SEQ(msg))
    {
        printf("alarmSeq : %02x\n", failEv->alarmSeq);
    } 
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_PrintStopSendEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_SM_STOP_SEND_EVENT_REP *stopEv = &msg->u.formMsg.u.stateMsg.u.stopEv;
    AVAILABILITY_STATUS *availStat =
                              &msg->u.formMsg.u.stateMsg.u.stopEv.availStat;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.stateMsg.u.stopEv.probCause;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_SM_SSER_OPERATIONAL_STATE(msg))
    {  
        printf("operanStat : %02x\n", stopEv->operanStat);
    }

    if (IS_PRESENT_NM_SM_SSER_AVAILABILTY_STATE(msg))
    {
        printf("length : %02x\n", availStat->length);
        for (i = 0; i < availStat->length; i++)
        {
            printf("status[%d] : %02x\n", i, availStat->status[i]);
        }
    }

    if (IS_PRESENT_NM_SM_SSER_MFD_DEP_STATE(msg))
    {
        printf("mfdDepen : %02x\n", stopEv->mfdDepen);
    }

    if (IS_PRESENT_NM_SM_SSER_PROBABLE_CAUSE(msg))
    {
        printf("type : %02x\n", probCause->type);
        printf("value : %02x\n", probCause->value);
    }

    if (IS_PRESENT_NM_SM_SSER_SPECIFIC_PROBLEMS(msg))
    {
        printf("specProbs : %02x\n", stopEv->specProbs);
    }
   
    if ((msg->u.formMsg.formGenElemnts.msgType ==
                                        NM_STOP_SENDING_EVENT_REPORTS_NACK) ||
        (msg->u.formMsg.formGenElemnts.msgType ==
                                        NM_RESTART_SENDING_EVENT_REPORTS_NACK))
    {
        printf("nackCause : %02x\n", stopEv->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_PrintChangeAdminState(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_SM_CHNG_ADMIN_STATE *state = &msg->u.formMsg.u.stateMsg.u.state;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    printf("adminStat : %02x\n", state->adminStat);
    
    if ((msg->u.formMsg.formGenElemnts.msgType ==
                                   NM_CHANGE_ADMINISTRATIVE_STATE_NACK) ||
        (msg->u.formMsg.formGenElemnts.msgType ==
                                   NM_CHANGE_ADMINISTRATIVE_STATE_REQUEST_NACK))
    {
        printf("nackCause : %02x\n", state->nackCuase);
    }
    
    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_PrintChangeover(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    SOURCE *src = &msg->u.formMsg.u.equipMsg.u.changeOver.src;
    DESTINATION *dest = &msg->u.formMsg.u.equipMsg.u.changeOver.dest;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
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

    if (msg->u.formMsg.formGenElemnts.msgType == NM_CHANGEOVER_NACK)
    {
        printf("nackCause : %02x\n",
                         msg->u.formMsg.u.equipMsg.u.changeOver.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_PrintOpstart(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                    
    if (msg->u.formMsg.formGenElemnts.msgType == NM_OPSTART_NACK)
    {
        printf("nackCause : %02x",
                               msg->u.formMsg.u.equipMsg.u.opStart.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_PrintSetSiteOutputs(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_EM_SET_SITE_OUTPUTS *siteOutput =
                                      &msg->u.formMsg.u.equipMsg.u.siteOutput;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("length : %02x\n", siteOutput->length);
    for (i = 0; i < siteOutput->length; i++)
    {
        printf("output[%d] : %02x\n", i, siteOutput->output[i]);
    } 
 
    if ((msg->u.formMsg.formGenElemnts.msgType == NM_SET_SITE_OUTPUTS_NACK) ||
        (msg->u.formMsg.formGenElemnts.msgType ==
                                             NM_CHANGE_HW_CONFIGURATION_NACK))
    {
        printf("nackCause : %02x\n", siteOutput->nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_PrintGetAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_MS_GET_ATTR *getAttr = &msg->u.formMsg.u.miscMsg.u.getAttr;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("length : %02x\n", getAttr->length);
    for (i = 0; i < getAttr->length; i++)
    {
        printf("atrrId[%d] : %02x\n", i, getAttr->atrrId[i]);
    }
    
    if (msg->u.formMsg.formGenElemnts.msgType == NM_GET_ATTRIBUTES_NACK)   
    {
        printf("nackCause : %02x\n", getAttr->nackCuase);
    }
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_PrintGetAttrResp(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_MS_GET_ATTR_RESP *getAttrResp = &msg->u.formMsg.u.miscMsg.u.getAttrResp;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
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
NM_MM_PrintSetAlarmThreshold(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    POWER_OUTPUT_THRESHOLD *powerOutput =
                     &msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput;
    PROBABLE_CAUSE *probCause =
                     &msg->u.formMsg.u.miscMsg.u.alarmThresh.probCause;
    VSWR_THRESHOLD *vswr = &msg->u.formMsg.u.miscMsg.u.alarmThresh.vswr;
    MFD_THRESHOLDS *mfdThresh =
                     &msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("type  : %02x\n", probCause->type);
    printf("value : %02x\n", probCause->value);

    if (IS_PRESENT_NM_MM_SAT_POWER_OUTPUT_THRESHOLD(msg))
    {
        printf("fault     : %02x\n", powerOutput->fault);
        printf("reduced   : %02x\n", powerOutput->reduced);
        printf("excessive : %02x\n", powerOutput->excessive);
    }

    if (IS_PRESENT_NM_MM_SAT_VSWR_THRESHOLDS(msg))
    {
        printf("faulty      : %02x\n", vswr->faulty);
        printf("notAdjusted : %02x\n", vswr->notAdjusted);
    } 

    if (IS_PRESENT_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS(msg))
    {
        printf("length : %02x\n", mfdThresh->length);
        for (i = 0; i < mfdThresh->length; i++)
        {
            printf("mfdDependnt[%d] : %02x\n", i, mfdThresh->mfdDependnt[i]);
        }
    }

    if (msg->u.formMsg.formGenElemnts.msgType == NM_SET_ALARM_THRESHOLD_NACK)
    {
        printf("nackCause : %02x\n",
                msg->u.formMsg.u.miscMsg.u.alarmThresh.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_EM_PrintReinitialise(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    HW_DESCRIPTION *hwDesc = &msg->u.formMsg.u.equipMsg.u.reInit.hwDesc; 
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
 
    if (IS_PRESENT_NM_EM_REIN_HW_DESCRIPTION(msg))
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
   
    if (msg->u.formMsg.formGenElemnts.msgType == NM_REINITIALIZE_NACK)
    {
        printf("nackCause : %02x\n",
                             msg->u.formMsg.u.equipMsg.u.reInit.nackCuase);
    }
 
    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_PrintMeasResultReq(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }                                                                                                                                         
    printf(" measId : %02x\n", msg->u.formMsg.u.measMsg.measId);

    return ITS_SUCCESS;
}

static ITS_INT
NM_MM_PrintMeasResultResp(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_MM__MEAS_RES_RESP *measResp = &msg->u.formMsg.u.measMsg.u.measResp;
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    printf("measId : %02x\n", msg->u.formMsg.u.measMsg.measId);

    printf("length : %02x\n", measResp->length);
    for (i = 0; i < measResp->length; i++)
    {
        printf("measResult[%d] : %02x\n", i, measResp->measResult[i]);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_PrintReportOutstandAlarms(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    ITS_UINT ret = 0, i;

    ret = NM_PrintCommonElements(msg);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
   
    if (msg->u.formMsg.formGenElemnts.msgType ==
                                            NM_REPORT_OUTSTANDING_ALARMS_NACK)
    {
        printf("nackCause : %02x\n",
                               msg->u.formMsg.u.stateMsg.u.repAlarm.nackCuase);
    }

    return ITS_SUCCESS;
}

static ITS_INT
NM_SM_PrintTrxHello(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    NM_SM_TRX_HELLO *trxHello = &msg->u.formMsg.u.stateMsg.u.trxHello;
    ITS_UINT ret = 0, i;
                                                                                
    ret = NM_PrintCommonElements(msg);
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

    if (IS_PRESENT_NM_SM_TRX_HELLO_SW_DESC(msg))
    {
        printf("swDesc.fileIdLen : %02x\n", trxHello->swDesc.fileIdLen);
        for (i = 0; i < trxHello->swDesc.fileIdLen; i++)
        {
            printf("swDesc.fileId[%d] : %02x\n", i, trxHello->swDesc.fileId[i]);
        }
        printf("swDesc.fileVerLen : %02x\n", i,  trxHello->swDesc.fileVerLen);
        for (i = 0; i < trxHello->swDesc.fileVerLen; i++)
        {
            printf("swDesc.fileVer[%d] : %02x\n", i,
                                        trxHello->swDesc.fileVer[i]);
        }
    }

    if (IS_PRESENT_NM_SM_TRX_HELLO_HW_DESC(msg))
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
reserved(ABIS_NETWORK_MANAGEMENT_MSG *msg)
{
    printf("Reserved/Invalid  Message Type \n");

    return ITS_SUCCESS;
}

ITS_INT (*Print_Network_Msg[MAX_NETWORK_FUNS_SIZE])
                 (ABIS_NETWORK_MANAGEMENT_MSG *msg) =
{
    reserved,                         /* 0x00 */
    NM_SWDM_PrintLoadDataInit,        /* 0x01 */
    NM_SWDM_PrintLoadDataInit,        /* 0x02 */
    NM_SWDM_PrintLoadDataInit,        /* 0x03 */
    NM_SWDM_PrintLoadDataSeg,         /* 0x04 */
    NM_SWDM_PrintLoadDataSeg,         /* 0x05 */
    NM_SWDM_PrintLoadDataAbort,       /* 0x06 */
    NM_SWDM_PrintLoadDataEnd,         /* 0x07 */
    NM_SWDM_PrintLoadDataEnd,         /* 0x08 */
    NM_SWDM_PrintLoadDataEnd,         /* 0x09 */
    NM_SWDM_PrintSwActiveReq,         /* 0x0A */
    NM_SWDM_PrintSwActiveReq,         /* 0x0B */
    NM_SWDM_PrintSwActiveReq,         /* 0x0C */
    NM_SWDM_PrintActivateSw,          /* 0x0D */
    NM_SWDM_PrintActivateSw,          /* 0x0E */
    NM_SWDM_PrintActivateSw,          /* 0x0F */
    NM_SWDM_PrintLoadDataAbort,       /* 0x10 */
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
    NM_ABIM_PrintEstablishTei,        /* 0x21 */
    NM_ABIM_PrintEstablishTei,        /* 0x22 */
    NM_ABIM_PrintEstablishTei,        /* 0x23 */
    NM_ABIM_PrintConnTerrSign,        /* 0x24 */
    NM_ABIM_PrintConnTerrSign,        /* 0x25 */
    NM_ABIM_PrintConnTerrSign,        /* 0x26 */
    NM_ABIM_PrintConnTerrSign,        /* 0x27 */
    NM_ABIM_PrintConnTerrSign,        /* 0x28 */
    NM_ABIM_PrintConnTerrSign,        /* 0x29 */
    NM_ABIM_PrintConnTerrTraffic,     /* 0x2A */
    NM_ABIM_PrintConnTerrTraffic,     /* 0x2B */
    NM_ABIM_PrintConnTerrTraffic,     /* 0x2C */
    NM_ABIM_PrintConnTerrTraffic,     /* 0x2D */
    NM_ABIM_PrintConnTerrTraffic,     /* 0x2E */
    NM_ABIM_PrintConnTerrTraffic,     /* 0x2F */
    reserved,                         /* 0x30 */
    NM_TRM_PrintConnMultiDropLink,    /* 0x31 */
    NM_TRM_PrintConnMultiDropLink,    /* 0x32 */
    NM_TRM_PrintConnMultiDropLink,    /* 0x33 */
    NM_TRM_PrintConnMultiDropLink,    /* 0x34 */
    NM_TRM_PrintConnMultiDropLink,    /* 0x35 */
    NM_TRM_PrintConnMultiDropLink,    /* 0x36 */
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
    NM_AIM_PrintSetBtsAttr,           /* 0x41 */
    NM_AIM_PrintSetBtsAttr,           /* 0x42 */
    NM_AIM_PrintSetBtsAttr,           /* 0x43 */
    NM_AIM_PrintSetRadioCarrierAttr,  /* 0x44 */
    NM_AIM_PrintSetRadioCarrierAttr,  /* 0x45 */
    NM_AIM_PrintSetRadioCarrierAttr,  /* 0x46 */
    NM_AIM_PrintSetChanlAttr,         /* 0x47 */
    NM_AIM_PrintSetChanlAttr,         /* 0x48 */
    NM_AIM_PrintSetChanlAttr,         /* 0x49 */
    reserved,                         /* 0x4A */
    reserved,                         /* 0x4B */
    reserved,                         /* 0x4C */
    reserved,                         /* 0x4D */
    reserved,                         /* 0x4E */
    reserved,                         /* 0x4F */
    reserved,                         /* 0x50 */
    NM_TM_PrintPerformTest,           /* 0x51 */
    NM_TM_PrintPerformTest,           /* 0x52 */
    NM_TM_PrintPerformTest,           /* 0x53 */
    NM_TM_PrintTestReport,            /* 0x54 */
    NM_TM_PrintSendTestReport,        /* 0x55 */
    NM_TM_PrintSendTestReport,        /* 0x56 */
    NM_TM_PrintSendTestReport,        /* 0x57 */
    NM_TM_PrintSendTestReport,        /* 0x58 */
    NM_TM_PrintSendTestReport,        /* 0x59 */
    NM_TM_PrintSendTestReport,        /* 0x5A */
    reserved,                         /* 0x5B */
    reserved,                         /* 0x5C */
    reserved,                         /* 0x5D */
    reserved,                         /* 0x5E */
    reserved,                         /* 0x5F */
    reserved,                         /* 0x60 */
    NM_SM_PrintStateChangdEventRep,   /* 0x61 */
    NM_SM_PrintFailureEventReport,    /* 0x62 */
    NM_SM_PrintStopSendEventReport,   /* 0x63 */
    NM_SM_PrintStopSendEventReport,   /* 0x64 */
    NM_SM_PrintStopSendEventReport,   /* 0x65 */
    NM_SM_PrintStopSendEventReport,   /* 0x66 */
    NM_SM_PrintStopSendEventReport,   /* 0x67 */
    NM_SM_PrintStopSendEventReport,   /* 0x68 */
    NM_SM_PrintChangeAdminState,      /* 0x69 */
    NM_SM_PrintChangeAdminState,      /* 0x6A */
    NM_SM_PrintChangeAdminState,      /* 0x6B */
    NM_SM_PrintChangeAdminState,      /* 0x6C */
    NM_SM_PrintChangeAdminState,      /* 0x6D */
    NM_SM_PrintChangeAdminState,      /* 0x6E */
    reserved,                         /* 0x6F */
    reserved,                         /* 0x70 */
    NM_EM_PrintChangeover,            /* 0x71 */
    NM_EM_PrintChangeover,            /* 0x72 */
    NM_EM_PrintChangeover,            /* 0x73 */
    NM_EM_PrintOpstart,               /* 0x74 */
    NM_EM_PrintOpstart,               /* 0x75 */
    NM_EM_PrintOpstart,               /* 0x76 */
    NM_EM_PrintSetSiteOutputs,        /* 0x77 */
    NM_EM_PrintSetSiteOutputs,        /* 0x78 */
    NM_EM_PrintSetSiteOutputs,        /* 0x79 */
    reserved,                         /* 0x7A */
    reserved,                         /* 0x7B */
    reserved,                         /* 0x7C */
    reserved,                         /* 0x7D */
    reserved,                         /* 0x7E */
    reserved,                         /* 0x7F */
    reserved,                         /* 0x80 */
    NM_MM_PrintGetAttr,               /* 0x81 */
    NM_MM_PrintGetAttrResp,           /* 0x82 */
    NM_MM_PrintGetAttr,               /* 0x83 */
    NM_MM_PrintSetAlarmThreshold,     /* 0x84 */
    NM_MM_PrintSetAlarmThreshold,     /* 0x85 */
    NM_MM_PrintSetAlarmThreshold,     /* 0x86 */
    NM_EM_PrintReinitialise,          /* 0x87 */
    NM_EM_PrintReinitialise,          /* 0x88 */
    NM_EM_PrintReinitialise,          /* 0x89 */
    NM_MM_PrintMeasResultReq,         /* 0x8A */
    NM_MM_PrintMeasResultResp,        /* 0x8B */
    NM_MM_PrintMeasResultReq,         /* 0x8C */
    NM_MM_PrintMeasResultReq,         /* 0x8D */
    reserved,                         /* 0x8E */
    reserved,                         /* 0x8F */
    NM_EM_PrintSetSiteOutputs,        /* 0x90 */
    NM_EM_PrintSetSiteOutputs,        /* 0x91 */
    NM_EM_PrintSetSiteOutputs,        /* 0x92 */
    NM_SM_PrintReportOutstandAlarms,  /* 0x93 */
    NM_SM_PrintReportOutstandAlarms,  /* 0x94 */
    NM_SM_PrintReportOutstandAlarms,  /* 0x95 */
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
    NM_SM_PrintTrxHello               /* 0xA0 */
};
