/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID: $Id: sua_sccp_conv.c,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:53  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:25  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:23  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/05/28 19:04:47  ngoel
 * LOG: port sua to current
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:02  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/01/10 21:46:20  mmiers
 * LOG: Get things building again.
 * LOG:
 * LOG: Revision 5.4  2002/01/10 14:38:04  ngoel
 * LOG: work in progress
 * LOG:
 * LOG: Revision 5.3  2002/01/04 18:14:30  ngoel
 * LOG: upgrading to draft 9 work in progress
 * LOG:
 * LOG: Revision 5.2  2001/10/08 20:08:03  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:48  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/26 14:48:52  labuser
 * LOG: commit SUA v5 to current.
 * LOG:
 * LOG: Revision 1.15.2.1  2001/06/22 20:23:25  labuser
 * LOG: SUA draft v5 codec.
 * LOG:
 *                   
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <its.h>
#include <its_trace.h>

#include <sua.h>

#if defined (CCITT)
#include <itu/sccp.h>
#elif defined (ANSI)
#include <ansi/sccp.h>
#endif
#include <its_sockets.h>


extern int _sua_itw_mode;

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is a helper function used find a given ITS_SCCP_IE
 *      in an array.
 *     
 *  Input Parameters:
 *      ies - pointer to the first element of IES array (common msg header)
 *      ieCount - number of IES in the array
 *      param - parameter name of the IE we want to find.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SCCP_IE* - pointer to ITS_SCCP_IE
 *      NULL if the element is not found within the array.
 *
 *  Notes:
 *
 *  See Also:
 *
 *****************************************************************************/
static ITS_SCCP_IE*
SUA_FindSCCPIE(ITS_OCTET param, ITS_SCCP_IE *ies, int ieCount)
{
    int i;

    for (i=0; i < ieCount; i++)
    {
        if (ies[i].param_id == param)
        {
            return &ies[i];
        }
    }

    return NULL;
}


int
SUA_SuaAddrToSccpAddr(ITS_SCCP_IE *ie, ITS_OCTET *data, ITS_USHORT len, 
            MTP3_HEADER *mhdr)
{
    ITS_OCTET suaRoutIndic, suaAddrIndic;
    ITS_OCTET sccpAddrIndic = 0x00;
    ITS_UINT pc;
    ITS_OCTET ssn;
    SUA_GT gt;
    int gtLen = 0, ret = ITS_SUCCESS;
    ITS_OCTET sccpGT[255];
    SCCP_ADDR sccpAddr;
    
    /* initialize to 0 */ 
    memset(sccpGT, 0, 255);

    ret = SUA_DecodeAddress(data, len, &suaRoutIndic, &suaAddrIndic,  
                            &pc, &ssn, &gt, &gtLen);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (suaAddrIndic & SUA_CPA_HAS_SSN_MASK)
    {
        sccpAddrIndic |= SCCP_CPA_HAS_SSN;
    }

    if (suaAddrIndic & SUA_CPA_HAS_PC_MASK)
    {
        sccpAddrIndic |= SCCP_CPA_HAS_PC;

        if (ie->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {

            MTP3_RL_SET_OPC_VALUE(mhdr->label, pc); 
        }
        else
        {
            MTP3_RL_SET_DPC_VALUE(mhdr->label, pc);
        }
    }

    /* routing indicator */
    if (suaRoutIndic == SUA_CPA_ROUTE_ON_GT)
    {
        sccpAddrIndic |= SCCP_CPA_ROUTE_GTTI;   
    }
    else if (suaRoutIndic == SUA_CPA_ROUTE_ON_SSN)
    {
        sccpAddrIndic |= SCCP_CPA_ROUTE_SSN;
    }

    if (suaAddrIndic & SUA_CPA_HAS_GT_MASK)
    {
        /* now the rest of the information is hidden in the GT parameter */
        if ((gt.numPlan & SUA_GT_NUM_PLAN_MASK) &&
            (gt.transType) && (gt.natOfAddr))
        {
            sccpAddrIndic |= SCCP_CPA_GTTI_ALL;
    
            /* now encode the GT in SCCP format */
            sccpGT[0] = gt.transType;
            sccpGT[1] = (gt.numPlan & SUA_GT_NUM_PLAN_MASK) << 4;
    
            if (!(gt.numOfDgts % 2))   /* even */
            {
                sccpGT[1] |= (SCCP_GTT_ENC_BCD_ODD); /* BCD odd */
            }
            else
            {
                sccpGT[1] |= (SCCP_GTT_ENC_BCD_EVEN); /* BCD even */
            }

            sccpGT[2] = gt.natOfAddr;

            memcpy(&sccpGT[3], gt.data, gtLen - 4); 
            gtLen = gtLen - 1;

        }
        else if ((gt.numPlan & SUA_GT_NUM_PLAN_MASK) &&
                 (gt.transType) && (!gt.natOfAddr))
        {
            sccpAddrIndic |= SCCP_CPA_GTTI_TNE_CCITT;

            /* now encode the GT in SCCP format */
            sccpGT[0] = gt.transType;
            sccpGT[1] = (gt.numPlan & SUA_GT_NUM_PLAN_MASK) << 4;
    
            if (!(gt.numOfDgts % 2)) /* even */
            {
                sccpGT[1] |= (SCCP_GTT_ENC_BCD_ODD); 
            }
            else
            {
                sccpGT[1] |= (SCCP_GTT_ENC_BCD_EVEN); 
            }

            memcpy(&sccpGT[2], gt.data, gtLen - 4);
            gtLen = gtLen - 2;

        }
        else if (!(gt.numPlan & SUA_GT_NUM_PLAN_MASK) &&
                 (gt.transType) && (!gt.natOfAddr))
        {
            sccpAddrIndic |= SCCP_CPA_GTTI_TRANS_CCITT;

            /* now encode the GT in SCCP format */
            sccpGT[0] = gt.transType;

            memcpy(&sccpGT[1], gt.data, gtLen - 4);
            gtLen = gtLen - 3;
            

        }
        else if (!(gt.numPlan & SUA_GT_NUM_PLAN_MASK) &&
                 (!gt.transType) && (gt.natOfAddr))
        {
            sccpAddrIndic |= SCCP_CPA_GTTI_NATURE;

            sccpGT[0] = gt.natOfAddr;

            if (gt.numOfDgts % 2) /* ODD */
            {
                sccpGT[0] |= (0x80U); /* TODO define a macro */
            }

            memcpy(&sccpGT[1], gt.data, gtLen - 4);
            gtLen = gtLen - 3;
            

        }
    }

    /* build the SCCP address now */

    ret = SCCP_EncodeAddr(&sccpAddr, sccpAddrIndic, pc, ssn,
                          sccpGT, gtLen);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* now build the IE and return */
 
    memcpy(&ie->param_data.calledPartyAddr, &sccpAddr, sizeof(SCCP_ADDR));

    return (ret);

}

int
SUA_SccpAddrToSuaAddr(ITS_SUA_IE *ie, ITS_OCTET *data, ITS_USHORT len, 
                      ITS_UINT *routCtxt)
{
    int ret = ITS_SUCCESS;
    SCCP_ADDR sccpAddr;
    ITS_OCTET sccpAddrIndic = 0x00, ssn = 0x00;
    ITS_OCTET suaAddrIndic = 0x00, suaRoutIndic = 0x00;
    ITS_UINT realPC;
    ITS_OCTET gttInfo[255];
    ITS_USHORT gttLen = 0, suaGTLen = 0;
    SUA_GT suaGT;
    ROUTE_Info rInfo;

    sccpAddr.len = len;
    memcpy(sccpAddr.data, data, len);

    ret = SCCP_DecodeAddr(&sccpAddr, &sccpAddrIndic, &realPC, &ssn,
                          gttInfo, &gttLen);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (routCtxt != NULL)
    {
        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if ( ((sccpAddrIndic & SCCP_CPA_HAS_SSN) == SCCP_CPA_HAS_SSN) &&
             ((sccpAddrIndic & SCCP_CPA_HAS_PC) == SCCP_CPA_HAS_PC) )
        {
            rInfo.pc = realPC;
            rInfo.routeCriteria.ssn = ssn;
            rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
            rInfo.style = ROUTE_DPC_SIO_SSN;
        }
        else if (sccpAddrIndic & SCCP_CPA_HAS_SSN)
        {
            rInfo.routeCriteria.ssn = ssn;
            /* TO DO  might have to send error message*/
        }
        else if (sccpAddrIndic & SCCP_CPA_HAS_PC)
        {
            rInfo.routeCriteria.opc = realPC;
            rInfo.style = ROUTE_DPC_SIO;
            rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
         }
         else
         {
            ITS_TRACE_ERROR(("Addr does not have PC or SSN"
                             " Cannot fint route context\n"));
         }

         ret = ROUTE_FindRoutingKeyByInfo(routCtxt, &rInfo);
         if (ret != ITS_SUCCESS)
         {
         }

    }

    /* take care of the routing indicator */
    if (sccpAddrIndic & SCCP_CPA_ROUTE_SSN)
    {
        suaRoutIndic = SUA_CPA_ROUTE_ON_SSN;
    }
    else
    {
        suaRoutIndic = SUA_CPA_ROUTE_ON_GT;
    }

    /* now the sua address indicator */
    if (sccpAddrIndic & SCCP_CPA_HAS_SSN)
    {
        suaAddrIndic |= SUA_CPA_HAS_SSN_MASK;
    }

    if (sccpAddrIndic & SCCP_CPA_HAS_PC)
    {
        suaAddrIndic |= SUA_CPA_HAS_PC_MASK;
    }

    if (sccpAddrIndic & SCCP_CPA_GTTI_MASK)
    {
        suaAddrIndic |= SUA_CPA_HAS_GT_MASK;
    }

    /* next we need to build the SUA GT if present */
    if (gttLen != 0)
    {
        if (sccpAddrIndic & SCCP_CPA_GTTI_NATURE)
        {
            suaGT.natOfAddr = gttInfo[0] & 0x7F;
            suaGT.numPlan = 0x00;
            suaGT.transType = 0x00;

            if (gttInfo[0] & 0x80)
            {
                suaGT.numPlan |= 0x80;
            }

            memcpy(suaGT.data, &gttInfo[1], (gttLen-1));

            suaGTLen = gttLen - 1;

        }
        else if (sccpAddrIndic & SCCP_CPA_GTTI_TRANS_CCITT)
        {
            suaGT.transType = gttInfo[0];
            suaGT.natOfAddr = 0x00;
            suaGT.numPlan = 0x00;
            suaGT.numOfDgts = (gttLen - 1) * 2;

            memcpy(suaGT.data, &gttInfo[1], (gttLen-1));

            suaGTLen = gttLen - 1;            

        }
        else if (sccpAddrIndic & SCCP_CPA_GTTI_TNE_CCITT)
        {
            suaGT.transType = gttInfo[0];
            suaGT.natOfAddr = 0x00;
            suaGT.numPlan = gttInfo[1] >> 4;
            suaGT.numOfDgts = (gttLen - 2) * 2;

            if ((gttInfo[1] & 0x0F) == SCCP_GTT_ENC_BCD_ODD)
            {
                suaGT.numPlan |= SUA_GT_ODD_EVEN_MASK;
                suaGT.numOfDgts = suaGT.numOfDgts - 1;
            }

            memcpy(suaGT.data, &gttInfo[2], (gttLen - 2));

            suaGTLen = gttLen - 2;
        }
        else if (sccpAddrIndic & SCCP_CPA_GTTI_ALL)
        {
            suaGT.transType = gttInfo[0];
            suaGT.natOfAddr = gttInfo[2];
            suaGT.numPlan = gttInfo[1] >> 4;
            suaGT.numOfDgts = (gttLen - 3) * 2;
        
            if ((gttInfo[1] & 0x0F) == SCCP_GTT_ENC_BCD_ODD)
            {
                suaGT.numPlan |= SUA_GT_ODD_EVEN_MASK;
                suaGT.numOfDgts = suaGT.numOfDgts - 1;
            }

            memcpy(suaGT.data, &gttInfo[3], (gttLen - 3));

            suaGTLen = gttLen - 3;

        }   
    }

    /* now encode the SUA address */

    ret = SUA_EncodeAddress(&ie->param_data.dstAddrs, suaRoutIndic, 
                             suaAddrIndic, realPC, ssn, &suaGT, suaGTLen);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* set the length in th IE */

    ie->param_length = ie->param_data.dstAddrs.len + 4;

    return ret;
    
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used internally to convert a SUA parameter to its
 *      SCCP equivalent. This function is used by SUA_SUADecodeToSCCP(). the
 *      SCCP parameter is returned as a ITS_SCCP_IE.
 *     
 *  Input Parameters:
 *      paramId - SUA parameter to be converted.
 *      paramLen - Length of SUA parameter.
 *      msgType - type of the SUA message the parameter to be converted 
 *                belongs to
 *      data - pointer to the SUA parameter data. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ies - pointer to ITS_SCCP_IE.
 *
 *  Return Value:
 *      ITS_SUCCESS, any other return value would indicate a conversion 
 *      failure
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
static int
SUA_SUAParamToSCCPParam(ITS_SCCP_IE **ies, int *ieCount, ITS_USHORT paramId,
                        ITS_USHORT paramLen, ITS_OCTET *data, MTP3_HEADER *mhdr)
{
    int ret = ITS_SUCCESS;

    switch(paramId)
    {
    case SUA_PRM_DATA:

        (*ies)->param_id = SCCP_PRM_DATA;
        (*ies)->param_length = (ITS_OCTET)paramLen;
        memcpy((*ies)->param_data.userData.data, data, paramLen);

        (*ies)++;
        (*ieCount)++;

        break;

    case SUA_PRM_SRC_ADDR:
    {
        (*ies)->param_id = SCCP_PRM_CALLING_PARTY_ADDR;

        ret = SUA_SuaAddrToSccpAddr(*ies, data, paramLen, mhdr);
        if (ret != ITS_SUCCESS)
        {   
            return ret;
        }

        (*ies)++;
        (*ieCount)++;

        break;
    }
    case SUA_PRM_DST_ADDR:
    {
        (*ies)->param_id = SCCP_PRM_CALLED_PARTY_ADDR;

        ret = SUA_SuaAddrToSccpAddr(*ies, data, paramLen, mhdr);
        if (ret != ITS_SUCCESS)
        {   
            return ret;
        }

        (*ies)++;
        (*ieCount)++;

        break;
    }
    case SUA_PRM_SRC_REF_NUM:

        (*ies)->param_id = SCCP_PRM_SRC_LOCAL_REF;
        (*ies)->param_length = sizeof(SCCP_REF_NUM);
        memcpy((*ies)->param_data.sourceLocalReference.refno,
               data + 1, sizeof(SCCP_REF_NUM));

        (*ies)++;
        (*ieCount)++;

        break;

    case SUA_PRM_DST_REF_NUM:

        (*ies)->param_id = SCCP_PRM_DEST_LOCAL_REF;
        (*ies)->param_length = sizeof(SCCP_REF_NUM);
        memcpy((*ies)->param_data.destinationLocalReference.refno,
               data + 1, sizeof(SCCP_REF_NUM));

        (*ies)++;
        (*ieCount)++;

        break;

    case SUA_PRM_CREDIT:

        (*ies)->param_id = SCCP_PRM_CREDIT;
        (*ies)->param_length = sizeof(SCCP_CREDIT);
        memcpy(&(*ies)->param_data.credit.win_size, data, 
                sizeof(SCCP_CREDIT));

        (*ies)++;
        (*ieCount)++;
 
        break;

    case SUA_PRM_SEQ_NUM:
    {
        SUA_SEQ_NUM seqNum;
   
        memcpy(&seqNum, data, sizeof(SUA_SEQ_NUM));

        if (seqNum.sentSenqNum == 0 && (seqNum.recSeqNum >> 1) == 0)
        {
            (*ies)->param_id = SCCP_PRM_SEGMENT_REASSEM;
            (*ies)->param_length = sizeof(SCCP_SEG_RES);
            (*ies)->param_data.segmentingReassembly.seg_res = 
                          seqNum.recSeqNum & SUA_SNUM_MORE_DATA_MASK;
        }
        else
        {
            (*ies)->param_id = SCCP_PRM_SEQUENCE_SEGMENT;
            (*ies)->param_length = sizeof(SCCP_SEQ_SEG);
            (*ies)->param_data.sequenceSegment.tsn = seqNum.sentSenqNum;
            (*ies)->param_data.sequenceSegment.tsn = seqNum.recSeqNum;
        }

        (*ies)++;
        (*ieCount)++;

        break;

    }
    case SUA_PRM_REC_SEQ_NUM:
    {
        SUA_REC_SEQ_NUM rsn;
 
        memcpy(&rsn, data, sizeof(SUA_REC_SEQ_NUM));

        (*ies)->param_id = SCCP_PRM_RCV_SEQ_NUM;
        (*ies)->param_length = sizeof(SCCP_RSN);
        (*ies)->param_data.receivedSequenceNumber.rsn = rsn.recSeqNum;
        
    }
    case SUA_PRM_SCCP_CAUSE:
    {
        SUA_SCCP_CAUSE  sccpCause;

        memcpy(&sccpCause, data, sizeof(SUA_SCCP_CAUSE));
        
        switch (sccpCause.causeType)
        {
        case SUA_CAUSE_TYPE_RETURN:

            (*ies)->param_id = SCCP_PRM_RETURN_CAUSE;
            (*ies)->param_length = sizeof(SCCP_RET_CAUSE);
            (*ies)->param_data.returnCause.cause = sccpCause.causeValue;

            break;

        case SUA_CAUSE_TYPE_RELEASE:

            (*ies)->param_id = SCCP_PRM_RELEASE_CAUSE;
            (*ies)->param_length = sizeof(SCCP_REL_CAUSE);
            (*ies)->param_data.releaseCause.cause = sccpCause.causeValue;

            break;

        case SUA_CAUSE_TYPE_RESET:

            (*ies)->param_id = SCCP_PRM_RESET_CAUSE;
            (*ies)->param_length = sizeof(SCCP_RES_CAUSE);
            (*ies)->param_data.resetCause.cause = sccpCause.causeValue;

            break;

        case SUA_CAUSE_TYPE_ERROR:

            (*ies)->param_id = SCCP_PRM_ERROR_CAUSE;
            (*ies)->param_length = sizeof(SCCP_ERR_CAUSE);
            (*ies)->param_data.errorCause.cause = sccpCause.causeValue;

            break;

        case SUA_CAUSE_TPYE_REFUSAL:

            (*ies)->param_id = SCCP_PRM_REFUSAL_CAUSE;
            (*ies)->param_length = sizeof(SCCP_REF_CAUSE);
            (*ies)->param_data.refusalCause.cause = sccpCause.causeValue;

            break;
        default:
            /* this message does not have the Cause parameter */
            return SUA_EBADMSG;

        }

        (*ies)++;
        (*ieCount)++;

        break;
    }


    case  SUA_PRM_PROT_CLASS :
    {
        SUA_PROT_CLASS pClass;
 
        memcpy(&pClass, data, sizeof(SUA_PROT_CLASS));

        pClass.value = SOCK_NToHL(pClass.value);

        (*ies)->param_id = SCCP_PRM_PROTOCOL_CLASS;
        (*ies)->param_length = sizeof(SCCP_PROT_CLASS);
        (*ies)->param_data.protocolClass.pclass = pClass.value;

        (*ies)++;
        (*ieCount)++;

        
        break;
    }

    case SUA_PRM_SEQ_CTL :
        break;

    case SUA_PRM_IMPORTANCE :
    {
        SUA_IMPORTANCE importance;
 
        memcpy(&importance, data, sizeof(SUA_IMPORTANCE));

        importance.value = SOCK_NToHL(importance.value);

        (*ies)->param_id = SCCP_PRM_IMPORTANCE;
        (*ies)->param_length = sizeof(SCCP_IMPORTANCE);
        (*ies)->param_data.importance.importance = importance.value;

        (*ies)++;
        (*ieCount)++;

        
        break;
    }

    case SUA_PRM_HOP_CNT :
    {
        SUA_HOP_COUNT hopCount;
 
        memcpy(&hopCount, data, sizeof(SUA_HOP_COUNT));

        hopCount.value = SOCK_NToHL(hopCount.value);

        (*ies)->param_id = SCCP_PRM_HOP_COUNTER ;
        (*ies)->param_length = sizeof(SCCP_HOP_COUNT);
        (*ies)->param_data.hopCount.count = hopCount.value;

        (*ies)++;
        (*ieCount)++;

        
        break;
    }
    
   case SUA_PRM_SEGMENTATION :
    {
        SUA_SEGMENTATION segmentation;
 
        memcpy(&segmentation, data, sizeof(SUA_SEGMENTATION));

        (*ies)->param_id = SCCP_PRM_SEGMENTATION;
        (*ies)->param_length = sizeof(SCCP_SEGMENTATION);
        memcpy(&((*ies)->param_data.segmentation),  data, 
                  sizeof(SUA_SEGMENTATION));

        (*ies)++;
        (*ieCount)++;

        
        break;
    }

    case SUA_PRM_ROUT_CTX :
        break;


    default:

        return SUA_EWRG_SUA_PARAM;

    }

    return ret;

}


SUADLLAPI int
SUA_SUADecodeSCMGToSCCP(ITS_SCCP_IE *ies, int *ieCount, ITS_EVENT *ev, 
                        SUA_MSG_DESC *desc)
{
    ITS_OCTET *ptr = ev->data;
    int evOffset = 0;
    ITS_USHORT paramId, paramLen;
    int ret = ITS_SUCCESS;
    SUA_MSG_HDR hdr;
    ITS_OCTET addrInd = 0;
    SCCP_ADDR sccpAddr;
    SCCP_SCMG scmg;


    *ieCount = 0;    

    /* get the SUA message type */
    memcpy(&hdr, ptr, sizeof(SUA_MSG_HDR));

    /* skip the common message header */
    evOffset += sizeof(SUA_MSG_HDR);

    if (hdr.msgClass != SUA_CL_SSNM_MSG)
    {
        return SUA_EBADMSG;
    }

    ies->param_id = SCCP_PRM_PROTOCOL_CLASS;
    ies->param_length = sizeof(SCCP_PROT_CLASS);
    ies->param_data.protocolClass.pclass = SCCP_PCLASS_0; /* must be set to 0 */

    ies++;
    (*ieCount)++;

    addrInd |= SCCP_CPA_HAS_SSN;
    addrInd |= SCCP_CPA_ROUTE_SSN;

    ret = SCCP_EncodeAddr(&sccpAddr, addrInd, 0, 1, NULL, 0);

    ies->param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies->param_length = (ITS_OCTET)sccpAddr.len;
    ies->param_data.calledPartyAddr.len = sccpAddr.len;
    memcpy(ies->param_data.calledPartyAddr.data, sccpAddr.data, sccpAddr.len);

    ies++;
    (*ieCount)++;

    ies->param_id = SCCP_PRM_CALLING_PARTY_ADDR;
    ies->param_length = (ITS_OCTET)sccpAddr.len;
    ies->param_data.callingPartyAddr.len = sccpAddr.len; 
    memcpy(ies->param_data.callingPartyAddr.data, sccpAddr.data, sccpAddr.len);

    ies++;
    (*ieCount)++;

    ies->param_id = SCCP_PRM_DATA;
    ies->param_length = sizeof(SCCP_SCMG);

    (*ieCount)++;


    if (hdr.msgType == SUA_MSG_DAVA)
    {
        scmg.type = SCCP_SCMG_SS_ALLOWED;
    }

    if (hdr.msgType == SUA_MSG_DUNA)
    {
        scmg.type = SCCP_SCMG_SS_PROHIBIT;
    }

    if (hdr.msgType == SUA_MSG_DAUD)
    {
        scmg.type = SCCP_SCMG_SS_STATUS_TEST;
    }

    /* mandatory parameters */
    if (desc->nmParam != 0)   /* It can be possible */
    {
        int i;
       
        for (i = 0; i < desc->nmParam; i++)
        {
            paramId = ev->data[evOffset] << 8 |
                      ev->data[evOffset + 1];
            evOffset += 2;

            paramLen = ev->data[evOffset] << 8 | 
                       ev->data[evOffset + 1] - 4;
            evOffset += 2;
            
            switch (paramId)
            {
            case SUA_PRM_SMI:
            {
                SUA_SMI smi;
                memcpy(&smi, &ev->data[evOffset], sizeof(SUA_SMI));

                scmg.multiplicity = (ITS_OCTET)smi.smi;

                break;
            }
            case SUA_SPRM_SSN:
            {
                SUA_SSN ssn;
                memcpy(&ssn, &ev->data[evOffset], sizeof(SUA_SSN));

                scmg.ssn = ssn.ssn;

                break;
            }
            case SUA_PRM_AFFECTED_PC:
            {
                SUA_AFFECTED_DEST pc;
                ITS_UINT realPC;

                memcpy(&pc, &ev->data[evOffset], sizeof(SUA_AFFECTED_DEST));

                realPC = SUA_PC_GET_VALUE(pc);
                
                MTP3_PC_SET_VALUE(scmg.pointCode, realPC);

                break;
            }

            }
                     
            evOffset += paramLen + SUA_GetPadding(paramLen);
    
            if (*ieCount > ITS_MAX_SUA_IES)
            {
                return (ITS_EOVERFLOW);
            }
        }  
    }
    else
    {
        return SUA_EBADMSG;
    }

    /* optional parameters */
    if (desc->noParam != 0)   /* It can be possible */
    {
        int i;
       
        while (evOffset < ev->len)
        {
            paramId = ev->data[evOffset] << 8 |
                      ev->data[evOffset + 1];
            evOffset += 2;

            paramLen = ev->data[evOffset] << 8 | 
                       ev->data[evOffset + 1] - 4;
            evOffset += 2;
            
            switch (paramId)
            {
            case SUA_PRM_SMI:
            {
                SUA_SMI smi;
                memcpy(&smi, &ev->data[evOffset], sizeof(SUA_SMI));

                scmg.multiplicity = (ITS_OCTET)smi.smi;

                break;
            }
            case SUA_SPRM_SSN:
            {
                SUA_SSN ssn;
                memcpy(&ssn, &ev->data[evOffset], sizeof(SUA_SSN));

                scmg.ssn = ssn.ssn;

                break;
            }
            case SUA_PRM_AFFECTED_PC:
            {
                SUA_AFFECTED_DEST pc;
                ITS_UINT realPC;

                memcpy(&pc, &ev->data[evOffset], sizeof(SUA_AFFECTED_DEST));

                realPC = SUA_PC_GET_VALUE(pc);
                
                MTP3_PC_SET_VALUE(scmg.pointCode, realPC);

                break;
            }

            }
                     
            evOffset += paramLen + SUA_GetPadding(paramLen);
    
            if (*ieCount > ITS_MAX_SUA_IES)
            {
                return (ITS_EOVERFLOW);
            }
        }  
    }

    /*TODO Get the cogestion level parameter from message
      this is not implemented yet in the SCCP SCMG structure */


    memcpy(&ies->param_data.userData, &scmg, sizeof(SCCP_SCMG));

    ies++;

    return (ITS_SUCCESS);

}




/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to obtain an array of ITS_SCCP_IES from a
 *      ITS_EVENT carrying a SUA message. The SCCP message type is also
 *      returned.
 *     
 *  Input Parameters:
 *      ev - pointer to the ITS_EVENT containing the SUA message.
 *      ieCount - number of SCCP ies elements in the array.
 *      desc - pointer to the SUA message descriptor.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ies - pointer to array of SCCP ies obtained from the SUA message.
 *      sccpMsgType - type of the sccp message converted.
 *      sccpDesc - address of the pointer to the SCCP message descriptor
 *
 *  Return Value:
 *      ITS_SUCCESS, any other return value would indicate a conversion 
 *      failure
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
SUADLLAPI int
SUA_SUADecodeToSCCP(ITS_SCCP_IE *ies, int *ieCount, ITS_EVENT *ev,
                    SUA_MSG_DESC *desc, MTP3_HEADER *mhdr)
{
    ITS_USHORT msgLen = ev->len;
    int evOffset = 0;
    ITS_USHORT paramId, paramLen;
    int ret = ITS_SUCCESS;

    *ieCount = 0;

    /* skip the common message hdr */
    evOffset += sizeof(SUA_MSG_HDR);
    
    
    /* mandatory parameters */
    if (desc->nmParam != 0)   /* It can be possible */
    {
        int i;

        for (i = 0; i < desc->nmParam; i++)
        {
            paramId = ev->data[evOffset] << 8 | 
                      ev->data[evOffset + 1];
  
            /* check if param is legal */
            if (paramId != desc->mParam[i])
            {
                return (ITS_EMISSMAND);
            }

            evOffset += 2;
            paramLen = (ev->data[evOffset] << 8 | 
                       ev->data[evOffset + 1]) - 4;
            evOffset += 2;

            ret = SUA_SUAParamToSCCPParam(&ies, ieCount, paramId,
                                          paramLen, &ev->data[evOffset], mhdr);
            

            evOffset += paramLen + SUA_GetPadding(paramLen);
            
            (*ieCount)++;
    
            if (*ieCount > ITS_MAX_SUA_IES)
            {
                return (ITS_EOVERFLOW);
            }

            ies++;
        }  
    }


    /* if we have optional parameters take care of them too */
    if (desc->noParam != 0)
    {
        while (evOffset < msgLen)
        {
            paramId = ev->data[evOffset] << 8 | 
                      ev->data[evOffset + 1];

            /* 
             * TODO: implement a check mechanism to
             * see is the opt parameter is legal
             */

            evOffset += 2;

            paramLen = (ev->data[evOffset] << 8 | 
                        ev->data[evOffset + 1]) - 4;

            evOffset += 2;

            ret = SUA_SUAParamToSCCPParam(&ies, ieCount, paramId,
                                          paramLen, &ev->data[evOffset], mhdr);            
          
            evOffset += paramLen + SUA_GetPadding(paramLen); 

            (*ieCount)++;

            if (*ieCount > ITS_MAX_SUA_IES)
            {
                return (ITS_EOVERFLOW);
            }

            ies++;
        }
    }

    return (ret);
}






/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used internally to convert a SCCP parameter to its
 *      SUA equivalent. This function is used by SUA_SCCPDecodeToSUA(). the
 *      SUA parameter is returned as a ITS_SUA_IE.
 *     
 *  Input Parameters:
 *      paramId - SCCP parameter to be converted.
 *      paramLen - Length of SCCP parameter.
 *      data - pointer to the SCCP parameter data. 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ies - pointer to ITS_SUA_IE containing the elements of SUA message.
 *
 *  Return Value:
 *      ITS_SUCCESS, any other return value would indicate a conversion 
 *      failure
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
static int
SUA_SCCPParamToSUAParam(ITS_SUA_IE *ies, ITS_OCTET paramId, ITS_OCTET paramLen, 
                        ITS_OCTET *data, ITS_UINT *routCtxt)
{
    int ret = ITS_SUCCESS;

    switch (paramId)
    {
    case SCCP_PRM_DEST_LOCAL_REF:
    {
        SCCP_REF_NUM num;
        ITS_UINT suaRefNum;

        /* convert DEST_LOCAL_REF to DEST_REF_NUM */
        memcpy(&num, data, sizeof(SCCP_REF_NUM));
       
        suaRefNum = RN_GET_REF_NUM(num);
        
        ies->param_id = SUA_PRM_DST_REF_NUM;
        ies->param_length =  sizeof(SUA_REF_NUM);
        ies->param_data.dstRefNum.refNum = suaRefNum;

        break;
    }    
    case SCCP_PRM_SRC_LOCAL_REF:
    {
        SCCP_REF_NUM num;
        ITS_UINT suaRefNum;

        /* convert DEST_LOCAL_REF to DEST_REF_NUM */
        memcpy(&num, data, sizeof(SCCP_REF_NUM));
       
        suaRefNum = RN_GET_REF_NUM(num);
        
        ies->param_id = SUA_PRM_SRC_REF_NUM;
        ies->param_length =  sizeof(SUA_REF_NUM);
        ies->param_data.srcRefNum.refNum = suaRefNum;

        break;
    }
    case SCCP_PRM_CALLED_PARTY_ADDR:
        
        /* convert to the SUA address format */

        if (_sua_itw_mode == SUA_ITW_SG)
        {
            ret = SUA_SccpAddrToSuaAddr(ies, data, (ITS_USHORT)paramLen, routCtxt);
        }
        else if (_sua_itw_mode == SUA_ITW_ASP)
        {
            ret = SUA_SccpAddrToSuaAddr(ies, data, (ITS_USHORT)paramLen, NULL);
        }
        else
        {
            ITS_TRACE_ERROR(("Interworking Mode neither ASP or SGP\n"));
        }

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        ies->param_id = SUA_PRM_DST_ADDR;


        break;
    
    case SCCP_PRM_CALLING_PARTY_ADDR:
    
        /* convert to the SUA address format */

        if (_sua_itw_mode == SUA_ITW_SG)
        {
            ret = SUA_SccpAddrToSuaAddr(ies, data, (ITS_USHORT)paramLen, NULL);
        }
        else if (_sua_itw_mode == SUA_ITW_ASP)
        {
            ret = SUA_SccpAddrToSuaAddr(ies, data, (ITS_USHORT)paramLen, 
                                        routCtxt);
        }
        else
        {
            ITS_TRACE_ERROR(("Interworking Mode neither ASP or SGP\n"));
        }

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        ies->param_id = SUA_PRM_SRC_ADDR;

        break;
    
    case SCCP_PRM_RELEASE_CAUSE:

        ies->param_id = SUA_PRM_SCCP_CAUSE;
        ies->param_length = sizeof(SUA_PRM_SCCP_CAUSE);
        ies->param_data.cause.causeType = SUA_CAUSE_TYPE_RELEASE;
        ies->param_data.cause.causeValue = *data;

        break;

    case SCCP_PRM_RETURN_CAUSE:

        ies->param_id = SUA_PRM_SCCP_CAUSE;
        ies->param_length = sizeof(SUA_SCCP_CAUSE);
        ies->param_data.cause.causeType = SUA_CAUSE_TYPE_RETURN;
        ies->param_data.cause.causeValue = *data;

        break;

    case SCCP_PRM_RESET_CAUSE:

        ies->param_id = SUA_PRM_SCCP_CAUSE;
        ies->param_length = sizeof(SUA_PRM_SCCP_CAUSE);
        ies->param_data.cause.causeType = SUA_CAUSE_TYPE_RESET;
        ies->param_data.cause.causeValue = *data;

        break;

    case SCCP_PRM_ERROR_CAUSE:

        ies->param_id = SUA_PRM_SCCP_CAUSE;
        ies->param_length = sizeof(SUA_PRM_SCCP_CAUSE);
        ies->param_data.cause.causeType = SUA_CAUSE_TYPE_ERROR;
        ies->param_data.cause.causeValue = *data;

        break;

    case SCCP_PRM_REFUSAL_CAUSE:

        ies->param_id = SUA_PRM_SCCP_CAUSE;
        ies->param_length = sizeof(SUA_PRM_SCCP_CAUSE);
        ies->param_data.cause.causeType = SUA_CAUSE_TPYE_REFUSAL;
        ies->param_data.cause.causeValue = *data;

        break;

    case SCCP_PRM_DATA:

        ies->param_id = SUA_PRM_DATA;
        ies->param_length = (ITS_USHORT)paramLen;
        memcpy(ies->param_data.data.data, data, ies->param_length);

        break;

    case SCCP_PRM_CREDIT:

        ies->param_id = SUA_PRM_CREDIT;
        ies->param_length = sizeof(SUA_CREDIT);
        ies->param_data.cr.credit = *data;

        break;

    case SCCP_PRM_SEQUENCE_SEGMENT:
    {
        SCCP_SEQ_SEG seqSeg;

        memcpy(&seqSeg, data, sizeof(SCCP_SEQ_SEG));

        ies->param_id = SUA_PRM_SEQ_NUM;
        ies->param_length = sizeof(SUA_SEQ_NUM);
        ies->param_data.seqNum.recSeqNum = seqSeg.rsn;
        ies->param_data.seqNum.sentSenqNum = seqSeg.tsn;

        break;
    }
    case SCCP_PRM_RCV_SEQ_NUM:

        ies->param_id = SUA_PRM_REC_SEQ_NUM;
        ies->param_length = sizeof(SUA_REC_SEQ_NUM);
        ies->param_data.rSeqNum.recSeqNum = (*data) >> 1;

        break;

    case SCCP_PRM_SEGMENT_REASSEM:

        ies->param_id = SUA_PRM_SEQ_NUM;
        ies->param_length = sizeof(SUA_SEQ_NUM);
        ies->param_data.seqNum.recSeqNum = *data;
        ies->param_data.seqNum.sentSenqNum = 0x00;

        break;
    case SCCP_PRM_HOP_COUNTER :
        ies->param_id = SUA_PRM_HOP_CNT;
        ies->param_length = sizeof(SUA_HOP_COUNT);
        ies->param_data.hopCount.value = *data;
        break;
    case SCCP_PRM_IMPORTANCE :
        ies->param_id = SUA_PRM_IMPORTANCE;
        ies->param_length = sizeof(SUA_IMPORTANCE);
        ies->param_data.importance.value = *data;
        break;
    case SCCP_PRM_PROTOCOL_CLASS :
        ies->param_id = SUA_PRM_PROT_CLASS;
        ies->param_length = sizeof(SUA_PROT_CLASS);
        ies->param_data.pClass.value = *data;
        break;
    case SCCP_PRM_SEGMENTATION :
        ies->param_id = SUA_PRM_SEGMENTATION;
        ies->param_length = sizeof(SUA_SEGMENTATION);
        memcpy(&(ies->param_data.segmentation), data, ies->param_length);
        break;

    default:

        return SUA_EBADMSG;

    }

    return ret;

}


SUADLLAPI int
SUA_AllocIEforSUAFlags(ITS_SUA_IE **flagPtr)
{
    *flagPtr = (ITS_SUA_IE*)calloc(1, sizeof(ITS_SUA_IE));
    if (*flagPtr == NULL)
    {
        return ITS_ENOMEM;
    }
    /*(*flagPtr)->param_id = SUA_PRM_FLAGS;
    (*flagPtr)->param_length = sizeof(SUA_FLAGS); */

    return ITS_SUCCESS;
}

/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function is used to obtain an array of ITS_SUA_IES from a
 *      ITS_EVENT carrying a SCCP message. The SUA message type is also
 *      returned.
 *     
 *  Input Parameters:
 *      ev - pointer to the ITS_EVENT containing the SCCP message.
 *      ieCount - number of SUA ies elements in the array.
 *      desc - pointer to the SCCP message descriptor.
 *      toUser - ITS_TRUE if the SCCP message is from the SCCP stack to
 *               the SCCP/SUA user. The reason for that is that if the
 *               message is for the user we also get the context info.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ies - pointer to array of SUA ies obtained from the SCCP message.
 *      suaDesc - retun a pointer to the SUA message descriptor.
 *
 *  Return Value:
 *      ITS_SUCCESS, any other return value would indicate a conversion 
 *      failure
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
SUADLLAPI int
SUA_SCCPDecodeToSUA(ITS_SUA_IE *ies, int *ieCount, ITS_EVENT *ev,
                    SCCP_MSG_DESC* desc, ITS_HDR *hdr,
                    ITS_BOOLEAN toUser, ITS_OCTET *sls, ITS_UINT *routCtxt)
{
    int evoffset = 0;
    ITS_OCTET *ptr;
    int i;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
#if 0 /* this is a placholder */
    ITS_OCTET *oargs = desc->oArgs;
#endif
    int noargs = desc->noArgs;
    ITS_OCTET paramId, paramLen, msgType;
    ITS_SUA_IE *ieHdr = ies;
    int ret = ITS_SUCCESS;
    ITS_SUA_IE *flagPtr = NULL;  /* used for the flag param */

    if (toUser)
    {
        if (ev->data[0] == MTP3_MSG_USER_DATA)
        {

            evoffset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER); 

            msgType = ev->data[evoffset];

            evoffset++;
        
        }
        else
        {
            msgType = ev->data[0];

           evoffset = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) +
                       sizeof(MTP3_HEADER);
          }
        
    }
    else
    {
        /* 
         * in that case the message format is:
         * MTP3 msg type: 1 byte
         * MTP3_HEADER: sizeof(MTP3_HEADER)
         * The SCCP message data
         */

        evoffset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER); /* TODO verify !! */

        msgType = ev->data[evoffset];

        evoffset++;
        
    }

    

    *ieCount = 0;

    /*
     * we need to create a SUA_IE for the common message header with the 
     * hop counter and the protocol class parameter if present
     */

    memset((char*)&ieHdr->param_data.msgHeader, 0, sizeof(SUA_MSG_HDR));
    ieHdr->param_id = SUA_PRM_MSG_HDR;
    ieHdr->param_length = sizeof(SUA_MSG_HDR);
    ieHdr->param_data.msgHeader.version = SUA_PROT_VER1;

    ies++;
    (*ieCount)++;


    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        paramId = margs[i];
        paramLen = SCCP_ComputeMSize(margs[i]);

        ret = SUA_SCCPParamToSUAParam(ies, paramId, paramLen,
                                      &ev->data[evoffset], routCtxt);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        ies++;
        (*ieCount)++;

        evoffset += paramLen;
    }

    /* get the variable mandatories */
    ptr = &ev->data[evoffset];

    for (i = 0; i < nvargs; i++)
    {
        ITS_OCTET *tmp;

        paramId = vargs[i];

        /* compute the pointer */
        tmp = ptr + *ptr;
        paramLen = *tmp;
        tmp++;

        ret = SUA_SCCPParamToSUAParam(ies, paramId, paramLen, 
                                      tmp, routCtxt);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        ies++;
        (*ieCount)++;

        ptr++;
    }

    /* get the optionals, if any */
    
    if (noargs && *ptr)
    {
        ptr += *ptr;

        assert((ptr - ev->data) <= ev->len);

        while (*ptr != SCCP_PRM_EOP)
        {
            paramId = *ptr;
            ptr++;
            paramLen = *ptr;
            ptr++;

            ret = SUA_SCCPParamToSUAParam(ies, paramId, paramLen, 
                                              ptr, routCtxt);
            if(ret != ITS_SUCCESS)
            {
                return ret;
            }

            ies++;
            (*ieCount)++;

            ptr += paramLen;
           
            assert((ptr - ev->data) <= ev->len);
        }
    }

    if(flagPtr != NULL)
    {
        memcpy(ies, flagPtr, sizeof(ITS_SUA_IE));
        (*ieCount)++;
        free(flagPtr);
    }
    return (ret);
}


/*.implementation:extern
 ******************************************************************************
 *  Purpose:
 *      This function converts a SUA message to an SCCP message.
 *     
 *  Input Parameters:
 *      toSCCP - is set to ITS_TRUE if the SCCP message is from user to
 *               SCCP/SUA stack. That is not from "SCTP" into SCCP/SUA stack
 *      hdr - must not be NULL if toSCCP is TRUE.
 *
 *  Input/Output Parameters:
 *      evt - pointer to the ITS_EVENT containing the SUA message.
 *            the SCCP message is returned to the same ITS_EVENT
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS, any other return value would indicate a conversion 
 *      failure
 *
 *  Notes:
 *
 *  See Also:
 *
 ******************************************************************************/
SUADLLAPI int
SUA_SUAEvtToSCCPEvt(ITS_EVENT *evt, ITS_BOOLEAN toSCCP, ITS_HDR *hdr,
                    ITS_BOOLEAN *isMgmt)
{
    int ret = ITS_SUCCESS;
    ITS_SCCP_IE sccpIes[ITS_MAX_SCCP_IES];
    int ieCount = 0;
    ITS_USHORT sccpMsgLen = 0;
    ITS_OCTET sccpMsgType;
    SCCP_MSG_DESC *sccpDesc;
    SUA_MSG_HDR suaMsgHdr;
    MTP3_HEADER mhdr;

    if (toSCCP)
    {
        if (hdr == NULL)
        {
            ITS_TRACE_DEBUG(("Header is NULL\n"));

            return ITS_ENOTFOUND;
        }
    }
    else
    {
        memset(&mhdr, 0, sizeof(MTP3_HEADER));
        MTP3_HDR_SET_SIO(mhdr, MTP3_SIO_SCCP);
    }

    *isMgmt = ITS_FALSE;

    /* get the SUA common message header */
    memcpy(&suaMsgHdr, evt->data, sizeof(SUA_MSG_HDR));

    SUA_NComHdrToH(&suaMsgHdr);

    switch (suaMsgHdr.msgClass)
    {
    case SUA_CL_ASP_STATE_MAINT_MSG:
    case SUA_CL_ASP_TRAF_MAINT_MSG:
    case SUA_CL_MGMT_MSG:
    {
        *isMgmt = ITS_TRUE;

        return ITS_SUCCESS;
    }
    case SUA_CL_CL_MSG:

        switch (suaMsgHdr.msgType)
        {
        case SUA_MSG_CLDT:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_CLDT_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            /* if we have the hop couter then we translate to XUDT */
            if(SUA_FindSCCPIE(SCCP_PRM_HOP_COUNTER, sccpIes, ieCount) != NULL)
            {
                sccpMsgType = SCCP_MSG_XUDT;
                sccpDesc = &SCCP_XUDT_Desc;
            }
            else
            {
                sccpMsgType = SCCP_MSG_UDT;
                sccpDesc = &SCCP_UDT_Desc;
            }
   
            break;

        case SUA_MSG_CLDR:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_CLDR_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            /* if we have the hop couter then we translate to XUDT */
            if(SUA_FindSCCPIE(SCCP_PRM_HOP_COUNTER, sccpIes, ieCount) != NULL)
            {
                sccpMsgType = SCCP_MSG_XUDTS;
                sccpDesc = &SCCP_XUDTS_Desc;
            }
            else
            {
                sccpMsgType = SCCP_MSG_UDTS;
                sccpDesc = &SCCP_UDTS_Desc;
            }

            break;

        default:
            return SUA_EBADMSG;        
        }

        break;

    case SUA_CL_CO_MSG:

        switch (suaMsgHdr.msgType)
        {

        case SUA_MSG_CODT:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_CODT_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            if (SUA_FindSCCPIE(SCCP_PRM_SEQUENCE_SEGMENT, sccpIes, ieCount) 
                                                                     != NULL)
            {
                sccpMsgType = SCCP_MSG_DT2;
                sccpDesc = &SCCP_DT2_Desc;
            }
            else if (SUA_FindSCCPIE(SCCP_PRM_SEGMENT_REASSEM, sccpIes, 
                                    ieCount) != NULL)
            {
                sccpMsgType = SCCP_MSG_DT1;
                sccpDesc = &SCCP_DT1_Desc;
            }
            else
            {
                sccpMsgType = SCCP_MSG_ED;
                sccpDesc = &SCCP_ED_Desc;
            }

            break;

        case SUA_MSG_CODA:

        /* this message should map to EA or AK. For the EA there is no
         * problem. For the AK we miss the mandatory Rec Seq Number parameter
         * for now we can only convert to EA. (this concerns PC3 messages
         */
            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_CODA_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }
   
            sccpMsgType = SCCP_MSG_EA;
            sccpDesc = &SCCP_EA_Desc;

            break;

        case SUA_MSG_CORE:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_CORE_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            sccpMsgType = SCCP_MSG_CR;
            sccpDesc = &SCCP_CR_Desc;

            break;

        case SUA_MSG_COAK:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_COAK_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            sccpMsgType = SCCP_MSG_CC;
            sccpDesc = &SCCP_CC_Desc;

            break;

        case SUA_MSG_COREF:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_COREF_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            sccpMsgType = SCCP_MSG_CREF;
            sccpDesc = &SCCP_CREF_Desc;
            
            break;

        case SUA_MSG_RELRE:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_RELRE_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            sccpMsgType = SCCP_MSG_RLSD;
            sccpDesc = &SCCP_RLSD_Desc;

            break;

        case SUA_MSG_RELCO:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_RELCO_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            sccpMsgType = SCCP_MSG_RLC;
            sccpDesc = &SCCP_RLC_Desc;

            break;

        case SUA_MSG_RESRE:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_RESRE_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            sccpMsgType = SCCP_MSG_RSR;
            sccpDesc = &SCCP_RSR_Desc;

            break;

        case SUA_MSG_RESCO:

            ret = SUA_SUADecodeToSCCP(sccpIes, &ieCount, evt,
                                      &SUA_RESCO_Desc, &mhdr);
            if (ret != ITS_SUCCESS)
            {
                return ret;
            }

            sccpMsgType = SCCP_MSG_RSC;
            sccpDesc = &SCCP_RSC_Desc;

            break;

        default:
            return SUA_EBADMSG;
        
        }

        break;

    case SUA_CL_SSNM_MSG:
    
        switch (suaMsgHdr.msgType)
        {
        case SUA_MSG_DAVA :

            ret = SUA_SUADecodeSCMGToSCCP(sccpIes, &ieCount, evt, 
                                          &SUA_DAVA_Desc);
            if (ret != ITS_SUCCESS)
            {
                return ret;   
            }

            sccpMsgType = SCCP_MSG_UDT;
            sccpDesc = &SCCP_UDT_Desc;

            break;
        case SUA_MSG_DUNA :

            ret = SUA_SUADecodeSCMGToSCCP(sccpIes, &ieCount, evt, 
                                          &SUA_DUNA_Desc);
            if (ret != ITS_SUCCESS)
            {
                return ret;   
            }

            sccpMsgType = SCCP_MSG_UDT;
            sccpDesc = &SCCP_UDT_Desc;

            break;
        case SUA_MSG_DAUD :

            ret = SUA_SUADecodeSCMGToSCCP(sccpIes, &ieCount, evt, 
                                           &SUA_DAUD_Desc);
            if (ret != ITS_SUCCESS)
            {
                return ret;   
            }

            sccpMsgType = SCCP_MSG_UDT;
            sccpDesc = &SCCP_UDT_Desc;

            break;
        case SUA_MSG_SCON :

            ret = SUA_SUADecodeSCMGToSCCP(sccpIes, &ieCount, evt, 
                                          &SUA_SCON_Desc);
            if (ret != ITS_SUCCESS)
            {
                return ret;   
            }

            sccpMsgType = SCCP_MSG_UDT;
            sccpDesc = &SCCP_UDT_Desc;

            break;
        case SUA_MSG_DUPU :

            ret = SUA_SUADecodeSCMGToSCCP(sccpIes, &ieCount, evt, 
                                          &SUA_DUPU_Desc);
            if (ret != ITS_SUCCESS)
            {
                return ret;   
            }

            sccpMsgType = SCCP_MSG_UDT;
            sccpDesc = &SCCP_UDT_Desc;

            break;
        default:
            return SUA_EBADMSG;
        }
        break;

    default:
        return SUA_EBADMSG;

    }

    if (toSCCP)
    {
        ITS_EVENT_TERM(evt);
        ret = SCCP_Encode(sccpIes, ieCount, sccpMsgType,
                          evt, hdr, sccpDesc);
    }
    else
    {
        ITS_OCTET buff[SUA_MAX_DATA_SIZE];

        ITS_EVENT_TERM(evt);
        ret = SCCP_EncodeMTP3(buff, &sccpMsgLen, sccpMsgType,
                              sccpIes, ieCount, sccpDesc);

        evt->src = ITS_MTP3_SRC;

        ret = MTP3_Encode(evt, MTP3_MSG_USER_DATA, &mhdr, buff, 
                          sccpMsgLen);

    }
    
    return ret;
}

SUADLLAPI int 
SUA_To_SCCP_Codec(SCTPTRAN_Manager *m, ITS_EVENT *evt,
                  ITS_BOOLEAN *isMgmt, ITS_OCTET *sls)
{
    int ret = ITS_SUCCESS;
    SUA_MSG_HDR *commonHdr = NULL;

    ITS_TRACE_DEBUG(("SUA_To_SCCP\n"));

    commonHdr = (SUA_MSG_HDR*)evt->data;

    if (commonHdr->msgClass == SUA_CL_ASP_STATE_MAINT_MSG ||
        commonHdr->msgClass == SUA_CL_ASP_TRAF_MAINT_MSG ||
        commonHdr->msgClass == SUA_RKEY_MGMT_MSG ||
        commonHdr->msgClass == SUA_CL_MGMT_MSG )
    {
        *isMgmt = ITS_TRUE;
        return ITS_SUCCESS;
    }
    else if (commonHdr->msgClass == SUA_CL_SSNM_MSG &&
             _sua_itw_mode == SUA_ITW_SG)
    {
        *isMgmt = ITS_TRUE;
        return ITS_SUCCESS;
    }


    return SUA_SUAEvtToSCCPEvt(evt, ITS_FALSE, NULL, isMgmt);
}



SUADLLAPI ITS_BOOLEAN
SUA_HandleSccpScmgParam(ITS_SUA_IE *ie, int *ieCount, ITS_OCTET *msgType, 
                        SUA_MSG_DESC **desc)
{
    SUA_SSN ssn;
    SCCP_SCMG scmgParam;


    ITS_SUA_IE *destAddr = SUA_FindSUAIE(ie, *ieCount, SUA_PRM_DST_ADDR);
    if (destAddr == NULL)
    {
        return SUA_EBADMSG;
    }
    
    if (destAddr->param_data.dstAddrs.routIndic[1] == SUA_CPA_ROUTE_ON_SSN)
    {
        ITS_USHORT paramId, paramLen;
        int offset = 0;

        /* need to check if the SSN is 1 */

        while (offset < destAddr->param_data.dstAddrs.len)
        {
            paramId = destAddr->param_data.dstAddrs.addrData[offset] << 8 | 
                      destAddr->param_data.dstAddrs.addrData[offset + 1];
            offset += 2;

            paramLen = destAddr->param_data.dstAddrs.addrData[offset] << 8 | 
                       destAddr->param_data.dstAddrs.addrData[offset + 1];
            offset += 2;

            if (paramId == SUA_SPRM_SSN)
            {
                memcpy(&ssn.ssn, &destAddr->param_data.dstAddrs.addrData[offset], 
                       sizeof(SUA_SSN));

                break;
            }
        }

        if (ssn.ssn == SCCP_SSN_SCCPMGMT)
        {
            ITS_SUA_IE *data = SUA_FindSUAIE(ie, *ieCount, SUA_PRM_DATA);
            ITS_UINT realPC;

            memcpy(&scmgParam, &data->param_data.data, sizeof(SCCP_SCMG));

            /*ie[*ieCount].param_id = SUA_PRM_FORMAT_ID;
            ie[*ieCount].param_length = sizeof(SUA_SCMG_FORM);
            ie[*ieCount].param_data.scmg.formatId = scmgParam.type; 

            (*ieCount)++; */
            switch(scmgParam.type)
            {
             case SCCP_SCMG_SS_ALLOWED :
                *msgType = SUA_MSG_DAVA;
                *desc = &SUA_DAVA_Desc;
                break;
             case SCCP_SCMG_SS_PROHIBIT :
                *msgType = SUA_MSG_DUNA;
                *desc = &SUA_DUNA_Desc;
                 break;
             case SCCP_SCMG_SS_STATUS_TEST :
                *msgType = SUA_MSG_DAUD;
                *desc = &SUA_DAUD_Desc;
                break;
             default :
                return SUA_EBADMSG;
                 break;
            }

            ie[*ieCount].param_id = SUA_PRM_SMI;
            ie[*ieCount].param_length = sizeof(SUA_SMI);
            ie[*ieCount].param_data.smi.smi = scmgParam.multiplicity;

            (*ieCount)++;

            ie[*ieCount].param_id = SUA_SPRM_SSN;
            ie[*ieCount].param_length = sizeof(SUA_SSN);
            ie[*ieCount].param_data.ssn.ssn = scmgParam.ssn;

            (*ieCount)++;

            ie[*ieCount].param_id = SUA_PRM_AFFECTED_PC;
            ie[*ieCount].param_length = sizeof(SUA_PC);

            realPC = MTP3_PC_GET_VALUE(scmgParam.pointCode);

            SUA_PC_SET_VALUE(ie[*ieCount].param_data.pc, realPC);

            (*ieCount)++;

            return ITS_TRUE;
        }     
    }

    return ITS_FALSE;

}


SUADLLAPI int
SUA_SetMsgType(ITS_SUA_IE *ie, ITS_OCTET msgClass, ITS_OCTET msgType)
{
    int ret = ITS_SUCCESS;

    if (ie->param_id == SUA_PRM_MSG_HDR)
    {
        ie->param_data.msgHeader.msgClass = msgClass;
        ie->param_data.msgHeader.msgType = msgType;
    }
    else
    {
        ret = SUA_EWRG_SUA_PARAM;
    }

    return ret;
}


SUADLLAPI int
SUA_SCCPEvtToSUAEvt(SCTPTRAN_Manager *m, ITS_EVENT *evt, ITS_BOOLEAN toUser, 
                    ITS_HDR *hdr,
                    ITS_OCTET *sls)
{
    int ret = ITS_SUCCESS;
    ITS_SUA_IE suaIes[ITS_MAX_SUA_IES];
    int ieCount = 0;
    ITS_OCTET sccpMsgType;
    SUA_MSG_DESC *suaDesc;
    ITS_OCTET scmgType;
    ITS_UINT  routCtxt = 0;
    MTP3_HEADER mhdr;
    int opc, dpc;
    ITS_OCTET ssn = 0;
    ROUTE_Info rInfo;
    ROUTE_Info *rinfo;


    ITS_TRACE_DEBUG(("SCCPToSUA\n"));

    if (toUser)
    {
        if (evt->data[0] == MTP3_MSG_USER_DATA)
        {
            memcpy(&mhdr, &evt->data[1], sizeof(MTP3_HEADER));

            opc = MTP3_RL_GET_OPC_VALUE(mhdr.label);
            dpc = MTP3_RL_GET_DPC_VALUE(mhdr.label);
            *sls = MTP3_RL_GET_SLS(mhdr.label);

            sccpMsgType = evt->data[sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)];
        }
        else
        {
            sccpMsgType = evt->data[0];
            memcpy(&mhdr, &evt->data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)], 
               sizeof(MTP3_HEADER));

            opc = MTP3_RL_GET_OPC_VALUE(mhdr.label);
            dpc = MTP3_RL_GET_DPC_VALUE(mhdr.label);
            *sls = MTP3_RL_GET_SLS(mhdr.label);
        }
    }
    else
    {
        /* get the SLS from the MTP3 Header */

        memcpy(&mhdr, &evt->data[1], sizeof(MTP3_HEADER));

        opc = MTP3_RL_GET_OPC_VALUE(mhdr.label);
        dpc = MTP3_RL_GET_DPC_VALUE(mhdr.label);
        *sls = MTP3_RL_GET_SLS(mhdr.label);

        sccpMsgType = evt->data[sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)];
    }
    
    for (rinfo = TRANSPORT_SS7_INFO((TRANSPORT_Control *)m).routeInfo;
         rinfo != NULL;
         rinfo = rinfo->next)
    {
        if (rinfo->pc == dpc && _sua_itw_mode == SUA_ITW_ASP) 
        {
            ssn = rinfo->routeCriteria.ssn;
        }
        else if (rinfo->pc == dpc && _sua_itw_mode == SUA_ITW_SG) 
        {
            ssn = rinfo->routeCriteria.ssn;
        }
    }

    
    switch (sccpMsgType)
    {
    case SCCP_MSG_UDT:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_UDT_Desc, 
                                  hdr, toUser, sls, &routCtxt);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        if(SUA_HandleSccpScmgParam(suaIes, &ieCount, &scmgType, &suaDesc))
        {
            ret = SUA_SetMsgType(suaIes, SUA_CL_SSNM_MSG, scmgType);
            if(ret != ITS_SUCCESS)
            {
                return ret;
            }
        }
        else
        {
            suaDesc = &SUA_CLDT_Desc;
            ret = SUA_SetMsgType(suaIes, SUA_CL_CL_MSG, SUA_MSG_CLDT);
            if(ret != ITS_SUCCESS)
            {
                return ret;
            }


             suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
             suaIes[ieCount].param_length = 4;

             if (routCtxt != 0)
             {
                 routCtxt = SOCK_NToHL(routCtxt);
                 memcpy(&(suaIes[ieCount].param_data), &routCtxt, 
                              sizeof(ITS_UINT));
             }
             else
             {
                 ITS_TRACE_ERROR((" Cannot fint route context\n"));
                 return ret;
             }

             ieCount++;
        
            suaIes[ieCount].param_id = SUA_PRM_SEQ_CTL;
            suaIes[ieCount].param_length = 4;
            suaIes[ieCount].param_data.seqCtl.value = *sls;
            ieCount++;
        
        
        }

        break;

    case SCCP_MSG_UDTS:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_UDTS_Desc, 
                                  hdr, toUser, sls, &routCtxt);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        if (routCtxt != 0)
        {
             routCtxt = SOCK_NToHL(routCtxt);
             memcpy(&(suaIes[ieCount].param_data), &routCtxt, 
                          sizeof(ITS_UINT));
         }
         else
         {
             ITS_TRACE_ERROR((" Cannot fint route context\n"));
             return ret;
         }

        ieCount++;
        

        /* add the flag IE to make SUA Happy... although it is
           empty of any signalling content... ??? */

        ieCount++;

        suaDesc = &SUA_CLDR_Desc;

        ret = SUA_SetMsgType(suaIes, SUA_CL_CL_MSG, SUA_MSG_CLDR);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_XUDT:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_XUDT_Desc, 
                                  hdr, toUser, sls, &routCtxt);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        if (routCtxt != 0)
        {
             routCtxt = SOCK_NToHL(routCtxt);
             memcpy(&(suaIes[ieCount].param_data), &routCtxt, 
                          sizeof(ITS_UINT));
         }
         else
         {
             ITS_TRACE_ERROR((" Cannot fint route context\n"));
             return ret;
         }

        ieCount++;
        
        suaIes[ieCount].param_id = SUA_PRM_SEQ_CTL;
        suaIes[ieCount].param_length = 4;
        suaIes[ieCount].param_data.seqCtl.value = *sls;
        ieCount++;
        

        if(SUA_HandleSccpScmgParam(suaIes, &ieCount, &scmgType, &suaDesc))
        {
            /*suaDesc = &SUA_SCMG_Desc;*/
            ret = SUA_SetMsgType(suaIes, SUA_CL_SSNM_MSG, scmgType);
            if(ret != ITS_SUCCESS)
            {
                return ret;
            } 
        }
        else
        {
            suaDesc = &SUA_CLDT_Desc;
            ret = SUA_SetMsgType(suaIes, SUA_CL_CL_MSG, SUA_MSG_CLDT);
            if(ret != ITS_SUCCESS)
            {
                return ret;
            }
        }

        break;

    case SCCP_MSG_XUDTS:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_XUDTS_Desc, 
                                  hdr, toUser, sls, &routCtxt);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        if (routCtxt != 0)
        {
             routCtxt = SOCK_NToHL(routCtxt);
             memcpy(&(suaIes[ieCount].param_data), &routCtxt, 
                          sizeof(ITS_UINT));
         }
         else
         {
             ITS_TRACE_ERROR((" Cannot fint route context\n"));
             return ret;
         }

        ieCount++;
        
        suaDesc = &SUA_CLDR_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CL_MSG, SUA_MSG_CLDR);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_LUDT:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_LUDT_Desc, 
                                  hdr, toUser, sls, &routCtxt);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        if (routCtxt != 0)
        {
             routCtxt = SOCK_NToHL(routCtxt);
             memcpy(&(suaIes[ieCount].param_data), &routCtxt, 
                          sizeof(ITS_UINT));
        }
        else
        {
             ITS_TRACE_ERROR((" Cannot fint route context\n"));
             return ret;
        }

        ieCount++;
        
        suaDesc = &SUA_CLDT_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CL_MSG, SUA_MSG_CLDT);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_LUDTS:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_LUDTS_Desc, 
                                  hdr, toUser, sls, &routCtxt);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;
        ieCount++;
        
        suaDesc = &SUA_CLDR_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CL_MSG, SUA_MSG_CLDR);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_DT1:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_DT1_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_CODT_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_CODT);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_DT2:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_DT2_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_CODT_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_CODT);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_ED:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_ED_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_CODT_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_CODT);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_AK:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_AK_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_CODA_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_CODA);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_EA:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_EA_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_CODA_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_CODA);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_CR:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_CR_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaIes[ieCount].param_id = SUA_PRM_SEQ_CTL;
        suaIes[ieCount].param_length = 4;
        suaIes[ieCount].param_data.seqCtl.value = *sls;
        ieCount++;
        
        suaDesc = &SUA_CORE_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_CORE);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_CC:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_CC_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;

        suaIes[ieCount].param_id = SUA_PRM_SEQ_CTL;
        suaIes[ieCount].param_length = 4;
        suaIes[ieCount].param_data.seqCtl.value = *sls;
        ieCount++;
        
        
        suaDesc = &SUA_COAK_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_COAK);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_CREF:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_CREF_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaIes[ieCount].param_id = SUA_PRM_SEQ_CTL;
        suaIes[ieCount].param_length = 4;
        suaIes[ieCount].param_data.seqCtl.value = *sls;
        ieCount++;
        
        suaDesc = &SUA_COREF_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_COREF);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_RLSD:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_RLSD_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_RELRE_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_RELRE);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_RLC:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_RLC_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_RELCO_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_RELCO);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_RSR:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_RSR_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }

        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_RESRE_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_RESRE);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_RSC:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_RSC_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_RESCO_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_CO_MSG, SUA_MSG_RESCO);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    case SCCP_MSG_ERR:

        ret = SUA_SCCPDecodeToSUA(suaIes, &ieCount, evt, &SCCP_ERR_Desc, 
                                  hdr, toUser, sls, NULL);
        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        /* Adding sequence ctl and routing context ies ngoel temp*/
        suaIes[ieCount].param_id = SUA_PRM_ROUT_CTX;
        suaIes[ieCount].param_length = 4;

        memset(&rInfo, 0, sizeof(ROUTE_Info));
        rInfo.type = ROUTING_KEY_ROUTE;
        if (_sua_itw_mode == SUA_ITW_ASP)
        {
            rInfo.pc = opc;
            rInfo.routeCriteria.ssn = ssn;
        }
        else
        {
            rInfo.pc = dpc;
            rInfo.routeCriteria.ssn = ssn;
        }
        rInfo.routeCriteria.sio = MTP3_SIO_SCCP;
        rInfo.style = ROUTE_DPC_SIO_SSN;

        ret = ROUTE_FindRoutingKeyByInfo(&routCtxt, &rInfo);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((" Cannot fint route context\n"));
            return ret;
        }

        routCtxt = SOCK_NToHL(routCtxt);
        memcpy(&(suaIes[ieCount].param_data), &routCtxt, sizeof(ITS_UINT));

        ieCount++;
        
        suaDesc = &SUA_ERR_Desc;
        ret = SUA_SetMsgType(suaIes, SUA_CL_MGMT_MSG, SUA_MSG_ERR);
        if(ret != ITS_SUCCESS)
        {
            return ret;
        }

        break;

    default:

        return ret;

    }

    return SUA_EncodeMsg(suaIes, ieCount, evt, suaDesc);

}


SUADLLAPI int 
SCCP_To_SUA_Codec(SCTPTRAN_Manager *m, ITS_EVENT *evt,
                  ITS_BOOLEAN *isMgmt, ITS_OCTET *sls)
{
    ITS_TRACE_DEBUG(("SCCPToSUA Codec\n"));

    if (*isMgmt)
    {
        return (ITS_SUCCESS);
    }

    if (_sua_itw_mode == SUA_ITW_SG)
    {
        return SUA_SCCPEvtToSUAEvt(m, evt, ITS_TRUE, NULL, sls);
    }
    else
    {
        return SUA_SCCPEvtToSUAEvt(m, evt, ITS_FALSE, NULL, sls);
    }
}
