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
 *  ID: $Id: abis_traffic_management.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
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
 *  Revision 1.1.2.6  2006/10/07 12:31:52  sjaddu
 *  Receving 3 octet Uplink Measurement Info buffer. Done respective validation.
 *
 *  Revision 1.1.2.5  2006/01/20 14:52:38  yranade
 *  Files after code review - 2nd phase. (badri)
 *
 *  Revision 1.1.2.4  2005/12/20 13:59:08  yranade
 *  Immediate Assignment Release related changes: Badrinarayanan
 *
 *  Revision 1.1.2.3  2005/09/27 11:59:46  mkrishna
 *  Added changes to OS related problems
 *
 *  Revision 1.1.2.2  2005/09/23 06:41:32  mkrishna
 *  Bug fixes done
 *
 *  Revision 1.1.2.1  2005/08/16 09:29:16  mkrishna
 *  added initial version after unit testing.
 *
 *
 ****************************************************************************/


#include <abis_traffic_management.h>

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the common elements in traffic management message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This internal API is used by all the messages in Traffic Management
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0130, ID :: D0090,
*                        ID :: D0120
*/
static ITS_INT
TM_encodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                        ITS_OCTET *buffer)
{
    TM_MSG_DESCRIMINATOR *desc = &msg->genElemnts.msgDesc;

    /* Check and Set Message Descriminator T bit*/
    if (desc->trasparent > 1)
    {
        return TM_RLLM_GEN_MSG_T_BIT_ERROR;
    } 
    buffer[*size] = desc->trasparent & 0x01;

    /* Check and Set Message Descriminator group*/
    if (desc->msgGruop > 127)
    {
        return TM_RLLM_GEN_MSG_GROUP_ERROR;
    } 
    buffer[(*size)++] |= ((desc->msgGruop & 0x7f) << 1); 

    buffer[(*size)++] = msg->genElemnts.msgType;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the common elements in Radio Link Layer Management msg's.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This internal API is used by all the messages in RLLM 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0090, 
*                        ID :: D0120
*/
static ITS_INT
TM_RLLM_encodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                             ITS_OCTET *buffer)
{
    ITS_UINT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.rllmMsg.rllmGenElements.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.rllmMsg.rllmGenElements.linkId;
    
    ret = TM_encodeCommonElements(msg, size, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Channel Number */ 
    buffer[(*size)++] = TM_IEI_CHANNEL_NUMBER;

    if (chanlNum->timeSlotNum > 7)
    {
        return TM_RLLM_CN_TIME_SLOT_ERROR;
    } 
    buffer[*size] = chanlNum->timeSlotNum & 0x07;

    if (chanlNum->chanlBits > 31)
    {
        return TM_RLLM_CN_CHANNEL_BITS_ERROR;
    }
    buffer[(*size)++] |= ((chanlNum->chanlBits & 0x1f) << 3);

    /* Set Link Identifier */
    buffer[(*size)++] = TM_IEI_LINK_IDENTIFIER;

    if (linkId->SAPI > 7)
    {
        return TM_RLLM_LI_SAPI_ERROR;
    }
    buffer[*size] = linkId->SAPI & 0x07;

    if (linkId->priority > 3)
    {
        return TM_RLLM_LI_PRIORITY_ERROR; 
    }
    buffer[*size] |= ((linkId->priority & 0x03) << 3);
    
    if (linkId->NA > 1)
    {
        return TM_RLLM_LI_NA_ERROR;
    }
    buffer[*size] |= ((linkId->NA & 0x01) << 5);

    if (linkId->chanlBits > 3)
    {
        return TM_RLLM_LI_CHANNEL_BITS_ERROR;
    }
    buffer[(*size)++] |= ((linkId->chanlBits & 0x03) << 6);

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Data Request Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*      This same API is used for Data Indication, Unit Data Request and 
*      Unit Data indication messages in RLLM. 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0100,   
*                        ID :: D0120   
*/
static ITS_INT
TM_RLLM_encodeDataReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size, 
                      ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_L3_INFORMATION *l3Info = &msg->u.rllmMsg.u.dataReq.l3Info; 
  
    ret = TM_RLLM_encodeCommonElements(msg, &index, buffer); 
    if (ret != ITS_SUCCESS)
    {
        return ret;
    } 

    /* Set L3 Information  */
    buffer[index++] = TM_IEI_L3_INFORMATION;

    buffer[index++] = l3Info->lengthInd >> 8;
    buffer[index++] = l3Info->lengthInd & 0xff;   

    /* Check Unit Data Request L3 Info length */
    if ((msg->genElemnts.msgType == TM_RLLM_UNIT_DATA_REQUEST) &&
        (l3Info->lengthInd > 22))
    {
        return CONTENT_LENGTH_ERROR;
    }
 
    /* Check Unit Data Indication L3 Info length */
    if ((msg->genElemnts.msgType == TM_RLLM_UNIT_DATA_INDICATION) &&
        (l3Info->lengthInd > 20))
    {
        return CONTENT_LENGTH_ERROR;
    }
 
    if (l3Info->lengthInd > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }    
    memcpy(&buffer[index], &l3Info->LLSDU[0], l3Info->lengthInd);
    index += l3Info->lengthInd;
    
    /* Assign index to size */
    *size = index; 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Error Indication Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None       
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
TM_RLLM_encodeErrorInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_RLLM_ERROR_IND *errorInd = &msg->u.rllmMsg.u.errorInd;

    ret = TM_RLLM_encodeCommonElements(msg, &index, buffer); 
    if (ret != ITS_SUCCESS)
    {
        return ret;
    } 

    /* Set RLM Cause */ 
    buffer[index++] = TM_IEI_RLM_CAUSE;

    if (errorInd->rlmLen != 0x00)
    {
        buffer[index++] = 0x00;
   
        if (((errorInd->causeVal & 0x80) >> 7) == 0)
        {
            buffer[index - 1] = 0x01;
            buffer[index++] = errorInd->causeVal;
        }
        else
        {
            buffer[index - 1] = 0x02;
            buffer[index++] = errorInd->causeVal & 0xff;
            buffer[index++] = errorInd->causeVal >> 8;   
        }
    }                                                                                                                                   
    else
    {
        buffer[index++] = 0x00;
    }
    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Establish Request Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Establish Request, Establish Confirm,
*       Release Confirm, Release Indication messages in RLLM. 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120, 
*/
static ITS_INT
TM_RLLM_encodeEstaReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                      ITS_OCTET *buffer)
{
    ITS_UINT ret = 0, index = 0;

    ret = TM_RLLM_encodeCommonElements(msg, &index, buffer); 
    if (ret != ITS_SUCCESS)
    {
        return ret;
    } 

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}
/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Establish Indicator Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None       
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0100,
*                        ID :: D0120
*/

static ITS_INT
TM_RLLM_encodeEstaInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                      ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_L3_INFORMATION *l3Info = &msg->u.rllmMsg.u.estInd.l3Info; 
    TM_RLLM_EST_IND *estInd = &msg->u.rllmMsg.u.estInd;
                                                                                                                                              
    ret = TM_RLLM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set L3 Information */
    if (IS_PRESENT_TM_RLLM_EI_L3_INFO(msg))
    {
        buffer[index++] = TM_IEI_L3_INFORMATION;

        buffer[index++] = l3Info->lengthInd >> 8;
        buffer[index++] = l3Info->lengthInd & 0xff;   

        if (l3Info->lengthInd > 20)
        {
            return CONTENT_LENGTH_ERROR;
        }    
        memcpy(&buffer[index], &l3Info->LLSDU[0], l3Info->lengthInd);
        index += l3Info->lengthInd;
    }
    
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Release Request Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None       
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0090,
*                        ID :: D0120
*/
static ITS_INT
TM_RLLM_encodeRelReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                     ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_RLLM_REL_REQ *relReq = &msg->u.rllmMsg.u.relReq;

    ret = TM_RLLM_encodeCommonElements(msg, &index, buffer); 
    if (ret != ITS_SUCCESS)
    {
        return ret;
    } 

    /* Set Release Mode */
    buffer[index++] = TM_IEI_RELEASE_MODE;       

    if (relReq->modeBit > 1)
    {
        return TM_RLLM_RM_MODE_BIT_ERROR;
    }
    buffer[index++] = relReq->modeBit;

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the common elements in CCM and DCM Messages.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This internal API is used by all the messages in CCM and DCM 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0090,
*                        ID :: D0120
*/
static ITS_INT
TM_CCM_encodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                            ITS_OCTET *buffer)
{
    ITS_UINT ret = 0;
    TM_MSG_DESCRIMINATOR *desc = &msg->genElemnts.msgDesc;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum;

    ret = TM_encodeCommonElements(msg, size, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Channel Number */
    buffer[(*size)++] = TM_IEI_CHANNEL_NUMBER;
                                                                                                                                              
    if (chanlNum->timeSlotNum > 7)
    {
        return TM_RLLM_CN_TIME_SLOT_ERROR;
    }
    buffer[*size] = chanlNum->timeSlotNum & 0x07;
                                                                                                                                              
    if (chanlNum->chanlBits > 31)
    {
        return TM_RLLM_CN_CHANNEL_BITS_ERROR;
    }
    buffer[(*size)++] |= ((chanlNum->chanlBits & 0x1f) << 3);
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the BCCH Information Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_encodeBcchInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                      ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_BCCH_INFO *bcchInfo = &msg->u.ccmMsg.u.bcchInfo;
    TM_FULL_BCCH_INFO *fullBcch = &msg->u.ccmMsg.u.bcchInfo.fullBcch;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set System Info Type */
    buffer[index++] = TM_IEI_SYSTEM_INFO_TYPE;

    buffer[index++] = bcchInfo->sysInfoType;

    /* Set BCCH Information if present */
    if (IS_PRESENT_TM_CCM_BI_FULL_BCCH_INFO(msg))
    {
        buffer[index++] = TM_IEI_FULL_BCCH_INFORMATION;

        if (fullBcch->length != 23)
        {
            return TM_DCM_BI_BCCH_INFO_LEN_ERROR;
        }
        buffer[index++] = fullBcch->length;

        memcpy(&buffer[index], &fullBcch->msg, fullBcch->length);

        index += fullBcch->length;
    }

    /* Set Start Time if present */
    if (IS_PRESENT_TM_CCM_BI_STARTING_TIME(msg))
    {
        buffer[index++] = TM_IEI_STARTING_TIME;
 
        buffer[index++] = bcchInfo->startingTime >> 8;
        buffer[index++] = bcchInfo->startingTime & 0xff;
    }
    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the CCCH Load Indication Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0090,
*                        ID :: D0120
*/
static ITS_INT
TM_CCM_encodeCcchLoadInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                        ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_RACH_LOAD *rach = &msg->u.ccmMsg.u.ccchLoadInd.rach;
    TM_CCM_CCCH_LOAD_IND *loadInd = &msg->u.ccmMsg.u.ccchLoadInd;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set RACH */
    if (chanlNum->chanlBits == TM_CN_UPLINK_CCCH)
    {
        buffer[index++] = TM_IEI_RACH_LOAD;

        if (rach->length < 6)
        {
            return TM_CCM_RL_LEN_ERROR;     
        }
        buffer[index++] = rach->length;

        buffer[index++] = rach->slotCount >> 8;
        buffer[index++] = rach->slotCount & 0xff;   

        buffer[index++] = rach->busyCount >> 8;
        buffer[index++] = rach->busyCount & 0xff;   

        buffer[index++] = rach->accessCount >> 8;
        buffer[index++] = rach->accessCount & 0xff;   

        memcpy(&buffer[index], &rach->info[0], (rach->length - 6));
        index += (rach->length - 6);
    }

    /* Set Paging Load */ 
    if (chanlNum->chanlBits == TM_CN_DOWNLINK_CCCH)
    {
        buffer[index++] = TM_IEI_PAGING_LOAD;

        buffer[index++] = loadInd->pagBufSpace >> 8;
        buffer[index++] = loadInd->pagBufSpace & 0xff;   
    }     
    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Channel Required Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_encodeChanRqd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                     ITS_OCTET *buffer) 
{
    ITS_UINT index = 0, ret = 0;
    TM_PHYSICAL_CONTEXT *phyCnxt = &msg->u.ccmMsg.u.chanRqd.phyContext;
    TM_CCM_CHAN_RQD *chanRqd = &msg->u.ccmMsg.u.chanRqd;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
  
    /* Set Required Reference */
    buffer[index++] = TM_IEI_REQUEST_REFERENCE;

    buffer[index++] = chanRqd->RA; 

    memcpy(&buffer[index], &chanRqd->reqRefNum, 2);
    index += 2;
     
    /* Set Access Delay */
    buffer[index++] = TM_IEI_ACCESS_DELAY;

    buffer[index++] = chanRqd->accessDelay;

    /* Set Physical Context if present */
    if (IS_PRESENT_TM_CCM_CR_PHYSICAL_CONTEXT(msg))
    {
        buffer[index++] = TM_IEI_PHYSICAL_CONTEXT;

        buffer[index++] = phyCnxt->length;

        memcpy(&buffer[index], &phyCnxt->content[0], phyCnxt->length);
        index += phyCnxt->length;
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Delete Indication Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Immediate Assign Command msg in CCM.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_encodeDeleteInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_DELETE_IND *deleteInd = &msg->u.ccmMsg.u.deleteInd;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Assignment Information */
    buffer[index++] = TM_IEI_FULL_IMMEDIATE_ASSIGN_INFO;

    if (deleteInd->length > 23)
    {
        return TM_CCM_DI_FULL_IMMD_LEN_ERROR;
    }
    buffer[index++] = deleteInd->length;

    memcpy(&buffer[index], &deleteInd->assignInfo[0], deleteInd->length);
    index += deleteInd->length;
 
    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Paging Command Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0090,
*                        ID :: D0120              
*/
static ITS_INT
TM_CCM_encodePagingCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, bitPos, i;
    TM_MS_IDENTITY *msIdentity = &msg->u.ccmMsg.u.pagingCmd.msIdentity;
    TM_CCM_PAGING_CMD *pagCmd = &msg->u.ccmMsg.u.pagingCmd;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Paging Group */
    buffer[index++] = TM_IEI_PAGING_GROUP;

    buffer[index++] = msg->u.ccmMsg.u.pagingCmd.pagingGroup;

    /* Set MS Identity */
    buffer[index++] = TM_IEI_MS_IDENTITY;

    if (msIdentity->length > 8)
    {
        return TM_CCM_PC_MSID_LEN_ERROR;
    }
    buffer[index++] = msIdentity->length;

    memcpy(&buffer[index], &msIdentity->identity[0], msIdentity->length);
    index += msIdentity->length;

    /* Set Channal Needed if present */
    if (IS_PRESENT_TM_CCM_PC_CHANNEL_NEEDED(msg))
    {
        buffer[index++] = TM_IEI_CHANNEL_NEEDED;

        if (pagCmd->chanlNeed > 3)
        {
            return TM_CCM_PC_CHANNEL_ERROR;  
        }
        buffer[index++] = pagCmd->chanlNeed & 0x03;
    }

    /* Set Priority if present */
    if (IS_PRESENT_TM_CCM_PC_EMLPP_PRIORITY(msg))
    {
        buffer[index++] = TM_IEI_EMLPP_PRIORITY;

        if (pagCmd->callPriority> 7)
        {
            return TM_CCM_PC_CALL_PRIORITY_ERROR;
        } 
        buffer[index++] = pagCmd->callPriority & 0x07;
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the SMS Broadcast Request Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0090,
*                        ID :: D0120 
*/
static ITS_INT
TM_CCM_encodeSmsBcReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                      ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    TM_CCM_SMS_BC_REQ *smsReq = &msg->u.ccmMsg.u.smsBcReq;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set SMSCB Info */
    buffer[index++] = TM_IEI_SMSCB_INFORMATION;

    if (smsReq->smscbInfoLen != 23)
    {
        return TM_CCM_SBR_SMSCB_LEN_ERROR;  
    }

    for (i=0; i<smsReq->smscbInfoLen; i++)
    {
        buffer[index++] = smsReq->smscbInfo[i];
    }

    /* Set Channel Indicator if present */
    if (IS_PRESENT_TM_CCM_SBR_SMSCB_CHANNEL_IND(msg))
    {
        buffer[index++] = TM_IEI_SMSCB_CHANNEL_INDICATOR;

        if (smsReq->chanlInd > 15)
        {
            return TM_CCM_SBR_CHANNEL_IND_ERROR;
        }
        buffer[index++] = smsReq->chanlInd & 0x0f;
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the RF Resource Indication Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120,
*                        ID :: D0090              
*/
static ITS_INT
TM_TRXM_encodeRfResInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                      ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, loc, len;
    TM_TRAX_RF_RES_IND *rfResInd = &msg->u.trxmMsg.u.rfResInd;

    ret = TM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Resource info */
    buffer[index++] = TM_IEI_RESOURCE_INFORMATION;
 
    /* make sure length is always even value */
    if ((rfResInd->length % 2) != 0)
    {
        return TM_TRXM_RRI_LENGTH_ERROR; 
    }

    /* Remember the location to fill lengnth later */ 
    loc = len = index++;

    for (i = 0; i < (rfResInd->length/2); i++)
    {
         if (rfResInd->info[i].chanlNum.timeSlotNum > 7)
         {
             return TM_TRXM_RRI_TIME_SLOT_ERROR;
         }
         buffer[index] = rfResInd->info[i].chanlNum.timeSlotNum & 0x07;
         if (rfResInd->info[i].chanlNum.chanlBits > 31)
         {
             return TM_TRXM_RRI_CHANNEL_BITS_ERROR;
         }
         buffer[index++] |= ((rfResInd->info[i].chanlNum.chanlBits & 0x1f) << 3);
         buffer[index] = (0 & 0x00);
         if (rfResInd->info[i].interfBand > 7)
         {
             return TM_TRXM_RRI_INTER_LEVEL_ERROR;
         }
         buffer[index++] |= ((rfResInd->info[i].interfBand & 0x07) << 5);  
    } 

    /* Fill up the len now */
    buffer[loc] = (index - len - 1);

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the SACCH Filling Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
TM_TRXM_encodeSacchFill(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_L3_INFORMATION *l3Info = &msg->u.trxmMsg.u.sacchFill.l3Info;
    TM_TRAX_SACCH_FILL *sacchFill = &msg->u.trxmMsg.u.sacchFill;

    ret = TM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set System Information Type */
    buffer[index++] = TM_IEI_SYSTEM_INFO_TYPE;

    buffer[index++] = sacchFill->sysInfoType;

    /* Set L3 Inforamtion if present */
    if (IS_PRESENT_TM_TRXM_SF_L3_INFO(msg))
    {
        buffer[index++] = TM_IEI_L3_INFORMATION;
                                                                                                                                              
        buffer[index++] = l3Info->lengthInd >> 8;
        buffer[index++] = l3Info->lengthInd & 0xff;   

        if (l3Info->lengthInd != 19)
        {
            return CONTENT_LENGTH_ERROR;
        }
        memcpy(&buffer[index], &l3Info->LLSDU[0], l3Info->lengthInd);
        index += l3Info->lengthInd;     
    }

    /* Set Starting Time if present */
    if (IS_PRESENT_TM_TRXM_SF_STARTING_TIME(msg))
    {
        buffer[index++] = TM_IEI_STARTING_TIME;

        buffer[index++] = sacchFill->startingTime >> 8;
        buffer[index++] = sacchFill->startingTime & 0xff;
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Overload Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120
*/
static ITS_INT
TM_TRXM_encodeOverload(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                      ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, loc, len;
    TM_TRAX_OVERLOAD *overload = &msg->u.trxmMsg.u.overload;

    ret = TM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Cause */
    buffer[index++] = TM_IEI_CAUSE;

    /* Remember the length location */
    loc = len = index++;

    if (overload->length > 0x00)
    { 
        /* Set Cause value and Diagnostics if any */
        if (((overload->causeVal & 0x80) >> 7) == 0)
        {
            buffer[index++] = overload->causeVal;
            if ((overload->length - 1) > 0)
            {
                memcpy(&buffer[index], &overload->diagnostics[0], 
                       (overload->length - 1));
                index += (overload->length - 1);
            }
        } 
        else
        {
            buffer[index++] = overload->causeVal & 0xff;
            buffer[index++] = overload->causeVal >> 8;   
            if ((overload->length - 2) > 0)
            {
                memcpy(&buffer[index], &overload->diagnostics[0], 
                       (overload->length - 2));
                index += (overload->length - 2);
            }
        } 
    }

    /* Fill up the length filed */ 
    buffer[loc] = (index - len - 1);

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Error Report Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120,
*                        ID :: D0090
*/
static ITS_INT
TM_TRXM_encodeErrorReport(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                         ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, len, loc;
    TM_CAUSE *cause = &msg->u.trxmMsg.u.errorReport.cause;
    TM_TRAX_ERROR_REPORT *errorReport = &msg->u.trxmMsg.u.errorReport;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.trxmMsg.u.errorReport.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.trxmMsg.u.errorReport.linkId;
    TM_ERRONEOUS_MSG *errMsg = &msg->u.trxmMsg.u.errorReport.errMsg;

    ret = TM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Cause */
    buffer[index++] = TM_IEI_CAUSE;

    /* Remember the length location */
    loc = len = index++;

    if (cause->length > 0x00)
    {
        /* Set Cause value and Diagnostics if any */
        if (((cause->causeVal & 0x80) >> 7) == 0)
        {
            buffer[index++] = cause->causeVal;
            if ((cause->length - 1) > 0)
            {
                memcpy(&buffer[index], &cause->diagnostics[0], 
                       (cause->length - 1));
                index += (cause->length - 1);
            }
        } 
        else
        {
            buffer[index++] = cause->causeVal & 0xff;
            buffer[index++] = cause->causeVal >> 8;   
            if ((cause->length - 2) > 0)
            {
                memcpy(&buffer[index], &cause->diagnostics[0], 
                       (cause->length - 2));
                index += (cause->length - 2);
            }
        } 
    }
 
    /* Fill up the length filed */ 
    buffer[loc] = (index - len - 1);

    /* Set Message Identifier if present */
    if (IS_PRESENT_TM_TRXM_ER_MESSAGE_IDENTIFIER(msg))
    {
        buffer[index++] = TM_IEI_MESSAGE_IDENTIFIER;
 
        buffer[index++] = errorReport->msgId;
    }

    /* Set Channel Number if present */ 
    if (IS_PRESENT_TM_TRXM_ER_CHANNEL_NUMBER(msg))
    {
        buffer[index++] = TM_IEI_CHANNEL_NUMBER;

        if (chanlNum->timeSlotNum > 7)
        {
            return TM_TRXM_CN_TIME_SLOT_ERROR;
        } 
        buffer[index] = chanlNum->timeSlotNum & 0x07;

        if (chanlNum->chanlBits > 31)
        {
            return TM_TRXM_CN_CHANNEL_BITS_ERROR;
        }
        buffer[index++] |= ((chanlNum->chanlBits & 0x1f) << 3);
    }

    /* Set Link Identifier if present */
    if (IS_PRESENT_TM_TRXM_ER_LINK_IDENTIFIER(msg))
    {
        buffer[index++] = TM_IEI_LINK_IDENTIFIER;

        if (linkId->SAPI > 7)
        {
            return TM_TRXM_LI_SAPI_ERROR;
        }
        buffer[index] = linkId->SAPI & 0x07;

        if (linkId->priority > 3)
        {
            return TM_TRXM_LI_PRIORITY_ERROR; 
        }
        buffer[index] |= ((linkId->priority & 0x03) << 3);
    
        if (linkId->NA > 1)
        {
            return TM_TRXM_LI_NA_ERROR;
        }
        buffer[index] |= ((linkId->NA & 0x01) << 5);

        if (linkId->chanlBits > 3)
        {
            return TM_TRXM_LI_CHANNEL_BITS_ERROR;
        }
        buffer[index++] |= ((linkId->chanlBits & 0x03) << 6);
    }
   
    /* Set Erroneous Message */
    if (IS_PRESENT_TM_TRXM_ER_ERRONEOUS_MSG(msg))
    {
        buffer[index++] = TM_IEI_ERRONEOUS_MESSAGE;
        
        if (errMsg->length < 1)
        {
            return TM_TRXM_ER_ERRONS_LEN_ERROR;
        }
        buffer[index++] = errMsg->length;

        memcpy(&buffer[index], &errMsg->recvdMsg[0], errMsg->length);
        index += errMsg->length;
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the SMS Broadcast Command Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0090,
*                        ID :: D0120 
*/
static ITS_INT
TM_CCM_encodeSmsBcCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                      ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CB_CMD_TYPE *cmdType = &msg->u.ccmMsg.u.smsBcCmd.cmdType;
    TM_SMSCB_MSG *smscbMsg = &msg->u.ccmMsg.u.smsBcCmd.smscbMsg;
    TM_CCM_SMS_BC_CMD *smsCmd = &msg->u.ccmMsg.u.smsBcCmd;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Command Type */
    buffer[index++] = TM_IEI_CB_COMMAND_TYPE;

    if (cmdType->lastlock > 3)
    {
        return TM_CCM_SMS_BC_LAST_BLOCK_ERROR;
    }
    buffer[index] = cmdType->lastlock & 0x03;

    if (cmdType->broadcast > 1)
    {
        return TM_CCM_SMS_BC_BROADCAST_ERROR; 
    } 
    buffer[index] |= ((cmdType->broadcast & 0x01) << 3);

    if (cmdType->command > 15)
    {
        return TM_CCM_SMS_BC_COMMOND_ERROR;
    }
    buffer[index++] |= ((cmdType->command & 0x0f) << 4);

    
    /* Set SMSCB Message */
    buffer[index++] = TM_IEI_SMSCB_MESSAGE;

    if (smscbMsg->length > 88)
    {
        return TM_CCM_SBC_SMSCB_MSG_LEN_ERROR;
    }
    buffer[index++] = smscbMsg->length;

    memcpy(&buffer[index], &smscbMsg->msg, smscbMsg->length);
    index += smscbMsg->length; 

    /* Set SMSBC Channel if present */ 
    if (IS_PRESENT_TM_CCM_SBC_SMSCB_CHANNEL_IND(msg))
    {
        buffer[index++] = TM_IEI_SMSCB_CHANNEL_INDICATOR;

        if (smsCmd->chanlInd > 15)
        {
            return TM_CCM_SBC_CHANNEL_IND_ERROR;
        }
        buffer[index++] = smsCmd->chanlInd & 0x0f;
    }
   
    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the CBCH Load Indication Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0090,
*                        ID :: D0120 
*/
static ITS_INT
TM_CCM_encodeCbchLoadInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                         ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_CBCH_LOAD_IND *loadInd = &msg->u.ccmMsg.u.cbchLoadInd;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set CBCH Load Info */
    buffer[index++] =  TM_IEI_CBCH_LOAD_INFORMATION;

    if (loadInd->slotCount > 15)
    {
        return TM_CCM_CBCH_SLOT_COUNT_ERROR;
    }
    buffer[index] =  loadInd->slotCount & 0x0f;

    if (loadInd->type > 1)
    {
        return TM_CCM_CBCH_LOAD_TYPE_ERROR;
    }
    buffer[index++] |= ((loadInd->type & 0x01) << 7);

    /* Set CBCH Channel Indicator if present */ 
    if (IS_PRESENT_TM_CCM_CLI_SMSCB_CHANNEL_IND(msg))
    {
        buffer[index++] = TM_IEI_SMSCB_CHANNEL_INDICATOR;

        if (loadInd->chanlInd > 15)
        {
            return TM_CCM_CBCH_CHANNEL_ERROR;
        }
        buffer[index++] = loadInd->chanlInd & 0x0f;
    } 

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Notification Command Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0090,
*                        ID :: D0120 
*/
static ITS_INT
TM_CCM_encodeNotCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                    ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_COMMAND_IND *cmdInd = &msg->u.ccmMsg.u.notCmd.cmdInd;
    TM_GROUP_CALL_REF *callRef = &msg->u.ccmMsg.u.notCmd.callRef;
    TM_GROUP_CHANNEL_DESC *chanlDesc = &msg->u.ccmMsg.u.notCmd.chanlDesc;
    TM_NCH_DRX_INFO *nchDrx = &msg->u.ccmMsg.u.notCmd.nchDrx; 

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Command Indicator */
    buffer[index++] = TM_IEI_COMMAND_INDICATOR;

    if (((cmdInd->cmdVal & 0x80) >> 7) == 0)
    {
        buffer[index++] = 0x01;
        buffer[index++] = cmdInd->cmdVal;
    }
    else 
    {
        buffer[index++] = 0x02;
        buffer[index++] = cmdInd->cmdVal & 0xff;
        buffer[index++] = cmdInd->cmdVal >> 8;   
    }

    /* Set Group Call Reference if present */
    if (IS_PRESENT_TM_CCM_NC_GROUP_CALL_REFERENCE(msg))
    {
        buffer[index++] = TM_IEI_GROUP_CALL_REFERENCE;

        if ((callRef->length < 1) || (callRef->length > 6))
        {
            return TM_CCM_NC_CALL_REF_LEN_ERROR;
        }
        buffer[index++] = callRef->length;

        memcpy(&buffer[index], &callRef->descGroup[0], callRef->length);
        index += callRef->length;
    }

    /* Set Channel Description if present */
    if (IS_PRESENT_TM_CCM_NC_CHANNEL_DESCRIPTION(msg))
    {
        buffer[index++] = TM_IEI_CHANNEL_DESCRIPTION;

        buffer[index++] = chanlDesc->length;

        memcpy(&buffer[index], &chanlDesc->chanlDesc[0], chanlDesc->length);
        index += chanlDesc->length;
    }

    /* Set NCH DRX Information if present */
    if (IS_PRESENT_TM_CCM_NC_NCH_DRX_INFO(msg))
    {
        buffer[index++] = TM_IEI_NCH_DRX_INFORMATION;

        if (nchDrx->length < 1)
        {
            return TM_CCM_NC_LEN_ERROR;
        } 
        buffer[index++] = nchDrx->length;

        if (nchDrx->NLN > 3)
        {
            return TM_CCM_NC_RADIO_INTERFACE_ERROR;
        }
        buffer[index] = nchDrx->NLN & 0x03;

        if (nchDrx->emlpp > 7)
        {
            return TM_CCM_NC_EMLPP_ERROR;
        }
        buffer[index] |= ((nchDrx->emlpp & 0x07) << 2);

        if (nchDrx->status > 1)
        {
            return TM_CCM_NC_NLN_ERROR;
        }
        buffer[index++] |= ((nchDrx->status & 0x01) << 5);
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Channel Activation Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodeChanActiv(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, len = 0, i, j, loc = 0; 
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

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
 
    /* Set Activation Type */
    buffer[index++] = TM_IEI_ACTIVATION_TYPE;

    if (chanActiv->actType > 7)
    {
        return TM_DCM_CA_ACTIVE_TYPE_ERROR;
    }
    buffer[index] = (chanActiv->actType & 0x07); 
    
    buffer[index] |= ((0 & 0x00) << 3);

    if (chanActiv->procedure > 1)
    {
        return TM_DCM_CA_PROCEDURE_ERROR;
    }
    buffer[index++] |= ((chanActiv->procedure & 0x01) << 7);

    /* Set Channel Mode */
    buffer[index++] = TM_IEI_CHANNEL_MODE;
   
    /* Remember the length location */
    loc = len = index++;

    if (chnlMode->dtxu > 1)
    {
        return TM_DCM_CM_DTXD_ERROR;
    }
    buffer[index] = (chnlMode->dtxu & 0x01);
    
    if (chnlMode->dtxd > 1)
    {
        return TM_DCM_CM_DTXU_ERROR;
    }
    buffer[index++] |= ((chnlMode->dtxd & 0x01) << 1);

    buffer[index++] = chnlMode->indicator;

    buffer[index++] = chnlMode->rateAndType;

    /* Check and Set Speech coding algrithm + trasp ind */
    if (chnlMode->indicator == TM_CM_SIGNALLING)
    {
        buffer[index++] = 0x00;
    }
    else if (chnlMode->indicator == TM_CM_DATA)
    {
        if (chnlMode->rate > 63)
        {
            return TM_DCM_CM_RATE_ERROR;
        }
        buffer[index] = (chnlMode->rate & 0x3f); 

        if (chnlMode->service > 1)
        {
            return TM_DCM_CM_SERVICE_BIT_ERROR;
        }
        buffer[index++] |= ((chnlMode->service & 0x01) << 6); 
    }
    else if (chnlMode->indicator == TM_CM_SPEECH)
    {
        buffer[index++] = chnlMode->codingAlg;
    }
    else
    {
        buffer[index++] = 0x00;
    }

    /* Fill up the length filed */ 
    buffer[loc] = (index - len - 1);

    /* Set Channel Identification if present */
    if (IS_PRESENT_TM_DCM_CA_CHANNEL_IDENTIFIER(msg)) 
    {
        buffer[index++] = TM_IEI_CHANNEL_IDENTIFICATION;
        /* The Channel Identification buffer should be 4 or more bytes.
         * it is shown in section 10.5.2.21 from 04.18 spec 
         */
        if ((chnlId->descLen + chnlId->allocLen) != 6)
        {
            return TM_DCM_CA_CHANL_ID_LEN_ERROR;
        }
        buffer[index++] = chnlId->descLen + chnlId->allocLen;
      
        memcpy(&buffer[index], &chnlId->chanlDesc[0], chnlId->descLen);
        index += chnlId->descLen;

        memcpy(&buffer[index], &chnlId->mobAlloc[0], chnlId->allocLen);
        index += chnlId->allocLen;
    }
 
    /* Set Encryption Information if present */
    if (IS_PRESENT_TM_DCM_CA_ENCRYPT_INFO(msg))
    {
        buffer[index++] = TM_IEI_ENCRYPTION_INFORMATION;
        if (encrption->length < 1)
        {
            return TM_DCM_EI_LENGTH_ERROR;
        }
        buffer[index++] = encrption->length;
                                                                                                                                              
        buffer[index++] = encrption->algorithmId;
                                                                                                                                              
        memcpy(&buffer[index], &encrption->key[0], (encrption->length - 1));
        index += (encrption->length -1);
    }

    /* Set Handover Reference if present */
    if ((chanActiv->actType == TM_AT_ASYNCRONOUS_HANDOVER) ||
        (chanActiv->actType == TM_AT_SYNCRONOUS_HANDOVER))
    {
        buffer[index++] = TM_IEI_HANDOVER_REFERENCE;
        buffer[index++] = chanActiv->handRef;
    }

    /* Set BS Power if present */
    if (IS_PRESENT_TM_DCM_CA_BS_POWER(msg))
    {
        buffer[index++] = TM_IEI_BS_POWER;

        if (bsPower->powerLevel > 15)
        {
            return TM_DCM_BP_POWER_LEVEL_ERROR;
        }
        buffer[index] = bsPower->powerLevel & 0x0f;
                                                                                                                                              
        if (bsPower->FPC > 1)
        {
            return TM_DCM_BP_FPC_ERROR;
        }
        buffer[index++] |= ((bsPower->FPC & 0x01) << 4);
    }

    /* Set MS Power if present */
    if (IS_PRESENT_TM_DCM_CA_MS_POWER(msg))
    {
        buffer[index++] = TM_IEI_MS_POWER;

        if (msPower->powerLevel > 31)
        {
            return TM_DCM_MP_POWER_LEVEL_ERROR;
        }
        buffer[index] = msPower->powerLevel & 0x1f;
                                                                                                                                              
        if (msPower->FPC > 1)
        {
            return TM_DCM_MP_FPC_ERROR;
        }
        buffer[index++] |= ((msPower->FPC & 0x01) << 5);
    }

    /* Set Timing Advance */
    if ((chanActiv->actType == TM_AT_IMMEDIATE_ASSIGNMENT) ||
        (chanActiv->actType == TM_AT_NORMAL_ASSIGNMENT))
    {
        buffer[index++] = TM_IEI_TIMING_ADVANCE;
        buffer[index++] = chanActiv->timingAdv; 
    }

    /* Set BS Power Parameters if present */
    if (IS_PRESENT_TM_DCM_CA_BS_POWER_PARAMS(msg))
    {
        buffer[index++] = TM_IEI_BS_POWER_PARAMETERS;

        buffer[index++] = bsParams->length;
                                                                                                                                              
        memcpy(&buffer[index], &bsParams->powerControl[0], bsParams->length);
        index += bsParams->length;
    }


    /* Set MS Power Parameters if present */
    if (IS_PRESENT_TM_DCM_CA_MS_POWER_PARAMS(msg))
    {
        buffer[index++] = TM_IEI_MS_POWER_PARAMETERS;

        buffer[index++] = msParams->length;
                                                                                                                                              
        memcpy(&buffer[index], &msParams->powerControl[0], msParams->length);
        index += msParams->length;
    }

    /* Set Physical Context if present */
    if (IS_PRESENT_TM_DCM_CA_PHYSICAL_CONTEXT(msg))
    {
        buffer[index++] = TM_IEI_PHYSICAL_CONTEXT;

        buffer[index++] = phyCnxt->length;
                                                                                                                                              
        memcpy(&buffer[index], &phyCnxt->content[0], phyCnxt->length);
        index += phyCnxt->length;
    }

    /* Set SAACH Inforamtion if present */
    if (IS_PRESENT_TM_DCM_CA_SAACH_INFO(msg))
    {
        buffer[index++] = TM_IEI_SACCH_INFORMATION;
        /* Remember location later we fill the length */
        loc = len = index++;

        buffer[index++] = sacchInfo->numOfMsgs;

        for (i = 0; i < sacchInfo->numOfMsgs; i++)
        {
            buffer[index++] = sacchInfo->msgInfo[i].typeOfMsg;
            buffer[index++] = sacchInfo->msgInfo[i].length;
            memcpy(&buffer[index], &sacchInfo->msgInfo[i].msg, 
                    sacchInfo->msgInfo[i].length);
            index += sacchInfo->msgInfo[i].length;
        }
        buffer[loc] = (index - len - 1);
    }

    /* Set UIC if present */
    if (IS_PRESENT_TM_DCM_CA_UIC(msg))
    {
        buffer[index++] = TM_IEI_UIC;
        buffer[index++] = chanActiv->uicLen;
        buffer[index++] = chanActiv->uicInfo; 
    }

    /* Set Main Channel Reference if present */
    if (IS_PRESENT_TM_DCM_CA_MAIN_CHANNEL_REF(msg))
    {
        buffer[index++] = TM_IEI_MAIN_CHANNEL_REFERENCE;
        if (chanActiv->mainChnlRefTn > 7)
        {
            return TM_DCM_CA_MAIN_CHANL_TN_ERROR;
        }
        buffer[index++] = chanActiv->mainChnlRefTn;
    }

    /* Set MultiRate Configuration if present */
    if (IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONFIG(msg))
    {
        buffer[index++] = TM_IEI_MULTIRATE_CONFIGURATION;

        if (mrConfig->length < 0x2)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = mrConfig->length;
                                                                                                                                              
        memcpy(&buffer[index], &mrConfig->content[0], mrConfig->length);
        index += mrConfig->length;
    }

    /* Set MultiRate Control if present */
    if (IS_PRESENT_TM_DCM_CA_MULTI_RATE_CONTROL(msg))
    {
        buffer[index++] = TM_IEI_MULTIRATE_CONTROL;

        if (mrControl->TFO > 1)
        {
            return TM_DCM_MC_TFO_ERROR;
        }
        buffer[index] = mrControl->TFO & 0x01;
                                                                                                                                              
        if (mrControl->RAE > 3)
        {
            return TM_DCM_MC_RAE_ERROR;
        }
        buffer[index] |= ((mrControl->RAE & 0x03) << 1);
                                                                                                                                              
        if (mrControl->PRE > 1)
        {
            return TM_DCM_MC_PRE_ERROR;
        }
        buffer[index++] |= ((mrControl->PRE & 0x01) << 3);
    }

    /* Set Supported Codec types if present */
    if (IS_PRESENT_TM_DCM_CA_SUPPORTED_CODEC_TYPES(msg))
    {
        buffer[index++] = TM_IEI_SUPPORTED_CODEC_TYPES;

        /* Remember the location to fill lengnth later */ 
        loc = len = index++;

        buffer[index++] = codecTypes->sysId;
                                                                                                                                              
        if (codecTypes->codecList > 127)
        {
            return TM_DCM_SCT_CODEC_LIST_ERROR;
        }
        buffer[index++] = codecTypes->codecList & 0x3f;
                                                                                                                                              
        /* Set Codec List info. if bit 4, 5 both having 1 then the
         * same info will send twice. if any one of 4, 5 bit is 1
         * then info sent once */
        if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            for (i = 0, j = 0; i < 2; i++, j++)
            {
                if (codecTypes->MACS[j] > 3)
                {
                    return TM_DCM_SCT_MACS_ERROR;
                }
                buffer[index] = codecTypes->MACS[j] & 0x03;
                                                                                                                                              
                if (codecTypes->TFO_VER[j] > 3)
                {
                    return TM_DCM_SCT_TFO_VER_ERROR;
                }
                buffer[index++] |= ((codecTypes->TFO_VER[j] & 0x03) << 2);
                buffer[index++] = codecTypes->SCS[j];
            }
        }
        else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
                ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            if (codecTypes->MACS[0] > 3)
            {
                return TM_DCM_SCT_MACS_ERROR;
            }
            buffer[index] = codecTypes->MACS[0] & 0x03;
                                                                                                                                              
            if (codecTypes->TFO_VER[0] > 3)
            {
                return TM_DCM_SCT_TFO_VER_ERROR;
            }
            buffer[index++] |= ((codecTypes->TFO_VER[0] & 0x03) << 2);
            buffer[index++] = codecTypes->SCS[0];
        }
                                                                                                                                              
        buffer[index++] = codecTypes->prefCodecType;
        /* Fill up the len now */
        buffer[loc] = (index - len - 1);
    }
    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Channel Activation Ack Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_encodeChanActivAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                          ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_CHAN_ACTIV_ACK *chanActivAck = &msg->u.dcmMsg.u.chanActivAck;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Frame number */
    buffer[index++] = TM_IEI_FRAME_NUMBER;

    buffer[index++] = chanActivAck->frameNum >> 8;
    buffer[index++] = chanActivAck->frameNum & 0xff;   

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}


/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Channel Activation NAck Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Connection Failure indication,
*       Mode Modify NAck, Multirate Codec Modifcation NAck msg's in DCM. 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_encodeChanActivNack(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, loc, len;
    TM_DCM_CHAN_ACTIV_NACK *chanActivNack = &msg->u.dcmMsg.u.chanActivNack; 
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Cause */
    buffer[index++] = TM_IEI_CAUSE;

    /* Remember the length location */
    loc = len = index++;

    if (chanActivNack->length > 0x00)
    {
        /* Set Cause value and Diagnostics if any */
        if (((chanActivNack->causeVal & 0x80) >> 7) == 0)
        {
            buffer[index++] = chanActivNack->causeVal;
            if ((chanActivNack->length - 1) > 0)
            {
                memcpy(&buffer[index], &chanActivNack->diagnostics[0],
                       (chanActivNack->length - 1));
                index += (chanActivNack->length - 1);
            }
        }
        else
        {
            buffer[index++] = chanActivNack->causeVal & 0xff;
            buffer[index++] = chanActivNack->causeVal >> 8;   
            if ((chanActivNack->length - 2) > 0)
            {
                memcpy(&buffer[index], &chanActivNack->diagnostics[0],
                       (chanActivNack->length - 2));
                index += (chanActivNack->length - 2);
            }
        }
    }

    /* Fill up the length filed */ 
    buffer[loc] = (index - len - 1);

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Deactivate SACCH Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Mode Modify Acknowledge, 
*       Physical Context Request, RF Channel Release, RF Channel Release Ack
*       messages in DCM.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_encodeDeactivateSaach(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                             ITS_OCTET *buffer)
{
    ITS_UINT ret = 0, index = 0;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Encryption Command Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090, ID :: D0100 
*/
static ITS_INT
TM_DCM_encodeEncrCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                     ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_ENCRYPTION_INFO *encrption = &msg->u.dcmMsg.u.encrCmd.encryption;
    TM_LINK_IDENTIFIER *linkId = &msg->u.dcmMsg.u.encrCmd.linkId;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.encrCmd.l3Info;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Encryption Information */
    buffer[index++] = TM_IEI_ENCRYPTION_INFORMATION;

    if (encrption->length < 1)
    {
        return TM_DCM_EI_LENGTH_ERROR;
    }  
    buffer[index++] = encrption->length;
 
    buffer[index++] = encrption->algorithmId;

    memcpy(&buffer[index], &encrption->key[0], (encrption->length - 1));
    index += (encrption->length -1);

    /* Set Link Identifier */
    buffer[index++] = TM_IEI_LINK_IDENTIFIER;
                                                                                                                                              
    if (linkId->SAPI > 7)
    {
        return TM_DCM_LI_SAPI_ERROR;
    }
    buffer[index] = linkId->SAPI & 0x07;
                                                                                                                                              
    if (linkId->priority > 3)
    {
        return TM_DCM_LI_PRIORITY_ERROR;
    }
    buffer[index] |= ((linkId->priority & 0x03) << 3);
                                                                                                                                          
    if (linkId->NA > 1)
    {
        return TM_DCM_LI_NA_ERROR;
    }
    buffer[index] |= ((linkId->NA & 0x01) << 5);
                                                                                                                                          
    if (linkId->chanlBits > 3)
    {
        return TM_DCM_LI_CHANNEL_BITS_ERROR;
    }
    buffer[index++] |= ((linkId->chanlBits & 0x03) << 6);

    /* Set L3 Information */
    buffer[index++] = TM_IEI_L3_INFORMATION;
                                                                                                                                              
    buffer[index++] = l3Info->lengthInd >> 8;
    buffer[index++] = l3Info->lengthInd & 0xff;   

    if (l3Info->lengthInd > 0x03)
    {
        return CONTENT_LENGTH_ERROR;
    }
    memcpy(&buffer[index], &l3Info->LLSDU[0], l3Info->lengthInd);
    index += l3Info->lengthInd;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Handover Detection Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Talker Detection, Listener Detection
*       messages in DCM 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_encodeHandoDet(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret;
    TM_DCM_HANDO_DET *handoDet = &msg->u.dcmMsg.u.handoDet; 

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    /* Set Access Delay element Id */
    if (IS_PRESENT_TM_DCM_HD_ACCESS_DELAY(msg))
    {
        buffer[index++] = TM_IEI_ACCESS_DELAY;
        buffer[index++] = handoDet->accessDelay;
    }

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Measurement Result Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090, ID :: D0100 
*/
static ITS_INT
TM_DCM_encodeMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
        ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_UPLINK_MEAS *uplinkMeas = &msg->u.dcmMsg.u.measRes.uplinkMeas; 
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.measRes.bsPower;
    TM_L1_INFORMATION *l1Info = &msg->u.dcmMsg.u.measRes.l1Info;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.measRes.l3Info;
    TM_DCM_MEAS_RES *measRes = &msg->u.dcmMsg.u.measRes;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Measurement Result Number */
    buffer[index++] = TM_IEI_MEASUREMENT_RESULT_NUMBER;
 
    buffer[index++] = measRes->measResultNum;

    /* Set Uplink Measurement */
    buffer[index++] = TM_IEI_UPLINK_MEASUREMENTS;

    if (uplinkMeas->length < 3)
    {
        return TM_DCM_UM_LENGTH_ERROR; 
    }
    buffer[index++] = uplinkMeas->length;
  
    if (uplinkMeas->rxlevFullUp > 63)
    {
        return TM_DCM_UM_RELEV_FULL_UP_ERROR;
    }
    buffer[index] = uplinkMeas->rxlevFullUp & 0x1f;

    if (uplinkMeas->dtxd > 1)
    {
        return TM_DCM_UM_DTXD_ERROR;
    }
    buffer[index] |= ((uplinkMeas->dtxd & 0x01) << 6);

    if (uplinkMeas->rfu > 1)
    {
        return TM_DCM_UM_RFU_ERROR;
    }
    buffer[index++] |= ((uplinkMeas->rfu & 0x01) << 7);

    if (uplinkMeas->rxlevSubUp > 63)
    {
        return TM_DCM_UM_RELEV_SUB_UP_ERROR;
    }  
    buffer[index++] = uplinkMeas->rxlevSubUp & 0x1f;

    if (uplinkMeas->rxqualSubUp > 7)
    {
        return TM_DCM_UM_RXQUAL_SUB_UP;
    }
    buffer[index] = uplinkMeas->rxqualSubUp & 0x07;

    if (uplinkMeas->rxqualFullUp > 7)
    {
        return TM_DCM_UM_RXQUAL_FULL_UP;
    } 
    buffer[index++] |= ((uplinkMeas->rxqualFullUp & 0x07) << 3);

    memcpy(&buffer[index], &uplinkMeas->SMI[0], (uplinkMeas->length - 3));
    index += (uplinkMeas->length - 3);

    /* Set BS Power */
    buffer[index++] = TM_IEI_BS_POWER;

    if (bsPower->powerLevel > 15)
    {
        return TM_DCM_BP_POWER_LEVEL_ERROR;
    }
    buffer[index] = bsPower->powerLevel & 0x0f;
   
    if (bsPower->FPC > 1)
    {
        return TM_DCM_BP_FPC_ERROR;
    }
    buffer[index++] |= ((bsPower->FPC & 0x01) << 4); 

    /* Set L1 Information if present */
    if (IS_PRESENT_TM_DCM_MR_L1_INFO(msg))
    {
        buffer[index++]  = TM_IEI_L1_INFORMATION;

        if (l1Info->FPC > 1)
        {
            return TM_DCM_L1_FPC_ERROR;
        }
        buffer[index] = ((l1Info->FPC & 0x01) << 2);
       
        if (l1Info->powerLevel > 31)
        {
            return TM_DCM_L1_POWER_LEVEL_ERROR;
        } 
        buffer[index++] |= ((l1Info->powerLevel & 0x1f) << 3);

        buffer[index++] = l1Info->timingAdvns;
    } 

    /* Set L3 Information if present */
    if (IS_PRESENT_TM_DCM_MR_L3_INFO(msg))
    {
        buffer[index++] = TM_IEI_L3_INFORMATION;
                                                                                                                                              
        buffer[index++] = l3Info->lengthInd >> 8;
        buffer[index++] = l3Info->lengthInd & 0xff;   

        if (l3Info->lengthInd != 18)
        {
            return CONTENT_LENGTH_ERROR;
        }
        memcpy(&buffer[index], &l3Info->LLSDU[0], l3Info->lengthInd);
        index += l3Info->lengthInd;
    }

    /* Set MS Timing Offset if present */
    if (IS_PRESENT_TM_DCM_MR_MS_TIMING_OFFSET(msg))
    {
        buffer[index++] = TM_IEI_MS_TIMING_OFFSET;
        buffer[index++] = measRes->timingOffset;
    }

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Mode Modify Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodeModeModifyReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, j, loc, len;
    TM_CHANNEL_MODE *chnlMode = &msg->u.dcmMsg.u.modeModifyReq.chnlMode;
    TM_ENCRYPTION_INFO *encrption = &msg->u.dcmMsg.u.modeModifyReq.encryption;
    TM_DCM_MODE_MODIFY_REQ *modeModifyReq = &msg->u.dcmMsg.u.modeModifyReq;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.modeModifyReq.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.modeModifyReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.modeModifyReq.codecTypes;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Channel Mode */
    buffer[index++] = TM_IEI_CHANNEL_MODE;
                                                                                                                                              
    /* Remember the length location */
    loc = len = index++;

    if (chnlMode->dtxu > 1)
    {
        return TM_DCM_CM_DTXD_ERROR;
    }
    buffer[index] = (chnlMode->dtxu & 0x01);
                                                                                                                                              
    if (chnlMode->dtxd > 1)
    {
        return TM_DCM_CM_DTXU_ERROR;
    }
    buffer[index++] |= ((chnlMode->dtxd & 0x01) << 1);
                                                                                                                                              
    buffer[index++] = chnlMode->indicator;
                                                                                                                                              
    buffer[index++] = chnlMode->rateAndType;

    /* Check and Set Speech coding algrithm + trasp ind */
    if (chnlMode->indicator == TM_CM_SIGNALLING)
    {
        buffer[index++] = 0x00;
    }
    else if (chnlMode->indicator == TM_CM_DATA)
    {
        if (chnlMode->rate > 63)
        {
            return TM_DCM_CM_RATE_ERROR;
        }
        buffer[index] = (chnlMode->rate & 0x3f);
                                                                                                                                              
        if (chnlMode->service > 1)
        {
            return TM_DCM_CM_SERVICE_BIT_ERROR;
        }
        buffer[index++] |= ((chnlMode->service & 0x01) << 6);
    }
    else if (chnlMode->indicator == TM_CM_SPEECH)
    {
        buffer[index++] = chnlMode->codingAlg;
    }
    else
    {
        buffer[index++] = 0x00;
    }

    /* Fill up the length filed */ 
    buffer[loc] = (index - len - 1);

    /* Set Encryption Information if present */
    if (IS_PRESENT_TM_DCM_MM_ENCRYPT_CHANNEL(msg))
    {
        buffer[index++] = TM_IEI_ENCRYPTION_INFORMATION;
        if (encrption->length < 1)
        {
            return TM_DCM_EI_LENGTH_ERROR;
        }
        buffer[index++] = encrption->length;
                                                                                                                                              
        buffer[index++] = encrption->algorithmId;
                                                                                                                                              
        memcpy(&buffer[index], &encrption->key[0], (encrption->length - 1));
        index += (encrption->length -1);
    }

    /* Set Main Channel Reference if present */
    if (IS_PRESENT_TM_DCM_MM_MAIN_CHANNEL_REF(msg))
    {
        buffer[index++] = TM_IEI_MAIN_CHANNEL_REFERENCE;
        if (modeModifyReq->mainChnlRefTn > 7)
        {
            return TM_DCM_CA_MAIN_CHANL_TN_ERROR;
        }
        buffer[index++] = modeModifyReq->mainChnlRefTn;
    }

    /* Set MultiRate Configuration if present */
    if (IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONFIG(msg))
    {
        buffer[index++] = TM_IEI_MULTIRATE_CONFIGURATION;

        if (mrConfig->length < 0x2)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = mrConfig->length;
                                                                                                                                              
        memcpy(&buffer[index], &mrConfig->content[0], mrConfig->length);
        index += mrConfig->length;
    }

    /* Set MultiRate Control if present */
    if (IS_PRESENT_TM_DCM_MM_MULTI_RATE_CONTROL(msg))
    {
        buffer[index++] = TM_IEI_MULTIRATE_CONTROL;
        if (mrControl->TFO > 1)
        {
            return TM_DCM_MC_TFO_ERROR;
        }
        buffer[index] = mrControl->TFO & 0x01;
                                                                                                                                              
        if (mrControl->RAE > 3)
        {
            return TM_DCM_MC_RAE_ERROR;
        }
        buffer[index] |= ((mrControl->RAE & 0x03) << 1);
                                                                                                                                              
        if (mrControl->PRE > 1)
        {
            return TM_DCM_MC_PRE_ERROR;
        }
        buffer[index++] |= ((mrControl->PRE & 0x01) << 3);
    }

    /* Set Supported Codec Types if present */
    if (IS_PRESENT_TM_DCM_MM_SUPPORTED_CODEC_TYPES(msg))
    {
        buffer[index++] = TM_IEI_SUPPORTED_CODEC_TYPES;

        /* Remember the location to fill lengnth later */ 
        loc = len = index++;

        buffer[index++] = codecTypes->sysId;
                                                                                                                                              
        if (codecTypes->codecList > 127)
        {
            return TM_DCM_SCT_CODEC_LIST_ERROR;
        }
        buffer[index++] = codecTypes->codecList & 0x3f;
                                                                                                                                              
        /* Set Codec List info. if bit 4, 5 both having 1 then the
         * same info will send twice. if any one of 4, 5 bit is 1
         * then info sent once */
        if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            for (i = 0, j = 0; i < 2; i++, j++)
            {
                if (codecTypes->MACS[j] > 3)
                {
                    return TM_DCM_SCT_MACS_ERROR;
                }
                buffer[index] = codecTypes->MACS[j] & 0x03;
                                                                                                                                              
                if (codecTypes->TFO_VER[j] > 3)
                {
                    return TM_DCM_SCT_TFO_VER_ERROR;
                }
                buffer[index++] |= ((codecTypes->TFO_VER[j] & 0x03) << 2);
                buffer[index++] = codecTypes->SCS[j];
            }
        }
        else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
                ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            if (codecTypes->MACS[0] > 3)
            {
                return TM_DCM_SCT_MACS_ERROR;
            }
            buffer[index] = codecTypes->MACS[0] & 0x03;
                                                                                                                                              
            if (codecTypes->TFO_VER[0] > 3)
            {
                return TM_DCM_SCT_TFO_VER_ERROR;
            }
            buffer[index++] |= ((codecTypes->TFO_VER[0] & 0x03) << 2);
            buffer[index++] = codecTypes->SCS[0];
        }
        buffer[index++] = codecTypes->prefCodecType;
        /* Fill up the len now */
        buffer[loc] = (index - len - 1);
    }

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Physical Context Confirm Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodePhyContextConf(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                            ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.phyContextConf.bsPower;
    TM_MS_POWER *msPower = &msg->u.dcmMsg.u.phyContextConf.msPower;
    TM_PHYSICAL_CONTEXT *phyCnxt = &msg->u.dcmMsg.u.phyContextConf.phyContext;

    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
   /* Set BS Power */                                                                    
    buffer[index++] = TM_IEI_BS_POWER;
   
    if (bsPower->powerLevel > 15)
    {
        return TM_DCM_BP_POWER_LEVEL_ERROR;
    }
    buffer[index] = bsPower->powerLevel & 0x0f;
                                                                                                                                              
    if (bsPower->FPC > 1)
    {
        return TM_DCM_BP_FPC_ERROR;
    }
    buffer[index++] |= ((bsPower->FPC & 0x01) << 4);

    /* Set MS Power */
    buffer[index++] = TM_IEI_MS_POWER;
                                                                                                                                              
    if (msPower->powerLevel > 31)
    {
        return TM_DCM_MP_POWER_LEVEL_ERROR;
    }
    buffer[index] = msPower->powerLevel & 0x1f;
                                                                                                                                              
    if (msPower->FPC > 1)
    {
        return TM_DCM_MP_FPC_ERROR;
    }
    buffer[index++] |= ((msPower->FPC & 0x01) << 5);

    /* Set Timing Advance */
    buffer[index++] = TM_IEI_TIMING_ADVANCE;
 
    buffer[index++] = msg->u.dcmMsg.u.phyContextConf.timingAdv;
      
    /* Set Physical Context if present */
    if (IS_PRESENT_TM_DCM_PCC_PHYSICAL_CONTEXT(msg))
    {
        buffer[index++] = TM_IEI_PHYSICAL_CONTEXT;
                                                                                                                                              
        buffer[index++] = phyCnxt->length;
                                                                                                                                              
        memcpy(&buffer[index], &phyCnxt->content[0], phyCnxt->length);
        index += phyCnxt->length;
    }
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the MS Power Control Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodeMsPowerControl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                            ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_MS_POWER *msPower = &msg->u.dcmMsg.u.mspowerControl.msPower;
    TM_MS_POWER_PARAMS *msParams = &msg->u.dcmMsg.u.mspowerControl.msParams; 
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set MS Power */
    buffer[index++] = TM_IEI_MS_POWER;
                                                                                                                                              
    if (msPower->powerLevel > 31)
    {
        return TM_DCM_MP_POWER_LEVEL_ERROR;
    }
    buffer[index] = msPower->powerLevel & 0x1f;
                                                                                                                                              
    if (msPower->FPC > 1)
    {
        return TM_DCM_MP_FPC_ERROR;
    }
    buffer[index++] |= ((msPower->FPC & 0x01) << 5);

    /* Set MS Power Parameters if present */
    if (IS_PRESENT_TM_DCM_MPC_MS_POWER_PARAMS(msg))
    { 
        buffer[index++] = TM_IEI_MS_POWER_PARAMETERS;

        buffer[index++] = msParams->length; 
 
        memcpy(&buffer[index], &msParams->powerControl[0], msParams->length);
        index += msParams->length; 
    }

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the BS Power Control Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodeBsPowerControl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                            ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.bspowerControl.bsPower;
    TM_BS_POWER_PARAMS *bsParams = &msg->u.dcmMsg.u.bspowerControl.bsParams; 
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set BS Power */
    buffer[index++] = TM_IEI_BS_POWER;
                                                                                                                                              
    if (bsPower->powerLevel > 15)
    {
        return TM_DCM_BP_POWER_LEVEL_ERROR;
    }
    buffer[index] = bsPower->powerLevel & 0x0f;
                                                                                                                                              
    if (bsPower->FPC > 1)
    {
        return TM_DCM_BP_FPC_ERROR;
    }
    buffer[index++] |= ((bsPower->FPC & 0x01) << 4);
                                                                                                                                              
    /* Set BS Power Parameters if present */
    if (IS_PRESENT_TM_DCM_BPC_BS_POWER_PARAMS(msg))
    {
        buffer[index++] = TM_IEI_BS_POWER_PARAMETERS;
        buffer[index++] = bsParams->length;
                                                                                                                                              
        memcpy(&buffer[index], &bsParams->powerControl[0], bsParams->length);
        index += bsParams->length;
    }

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Preprocess Configure Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodePreprocConfig(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_PREPROC_CONFIG *preprocConfig = &msg->u.dcmMsg.u.preprocConfig;
 
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
 
    /* Set Preprocessing Parameters */
    buffer[index++] = TM_IEI_PRE_PROCESSING_PARAMETERS;

    buffer[index++] = preprocConfig->length;

    if (preprocConfig->procedure > 1)
    {
        return TM_DCM_PP_PROCEDURE_ERROR;
    }
    buffer[index++] = preprocConfig->procedure & 0x01;

    memcpy(&buffer[index], &preprocConfig->processParam[0], 
            preprocConfig->length - 1); 
    index += (preprocConfig->length - 1); 

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Preprocessed Measurement Result Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_encodePreprocMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_PREPOC_MEAS_RES *prepocMeasRes = &msg->u.dcmMsg.u.prepocMeasRes;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Preprocessing Measurement */
    buffer[index++] = TM_IEI_PRE_PROCESSED_MEASUREMENTS;
                                                                                                                                              
    buffer[index++] = prepocMeasRes->length;
                                                                                                                                              
    memcpy(&buffer[index], &prepocMeasRes->processMeas[0],
            prepocMeasRes->length);
    index += prepocMeasRes->length; 

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the SACCH Info Modify Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0100 
*/
static ITS_INT
TM_DCM_encodeSacchInfoModify(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                             ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_SACCH_INFO_MOD *sacchInfoMod = &msg->u.dcmMsg.u.sacchInfoMod; 
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.sacchInfoMod.l3Info;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set System Info Type */
    buffer[index++] = TM_IEI_SYSTEM_INFO_TYPE;

    buffer[index++] = sacchInfoMod->sysInfoType;

    /* Set L3 Inforamtion if present */
    if (IS_PRESENT_TM_DCM_SIM_L3_INFO(msg))
    {
        buffer[index++] = TM_IEI_L3_INFORMATION;
                                                                                                                                              
        buffer[index++] = l3Info->lengthInd >> 8;
        buffer[index++] = l3Info->lengthInd & 0xff;   

        if (l3Info->lengthInd > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        memcpy(&buffer[index], &l3Info->LLSDU[0], l3Info->lengthInd);
        index += l3Info->lengthInd;
    }

    /* Set Start Time if present */
    if (IS_PRESENT_TM_DCM_SIM_STARTING_TIME(msg))
    {
        buffer[index++] = TM_IEI_STARTING_TIME;
                                                                                                                                              
        buffer[index++] = sacchInfoMod->startingTime >> 8;
        buffer[index++] = sacchInfoMod->startingTime & 0xff;
    }

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Remote Codec Configureation Report Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodeRemoteCodeConfRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                               ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, j, len, loc;
    TM_CODEC_CONFIG *config = &msg->u.dcmMsg.u.remoteCodecConfRep.config;    
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes;
                                                                                                                                          
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Codec Configuration */
    buffer[index++] = TM_IEI_CODEC_CONFIGURATION;

    if (config->length < 1)
    {
        return TM_DCM_CC_LENGTH_ERROR;
    } 
    /* Remember the location to fill length later */ 
    loc = len = index++;

    buffer[index++] = config->codecType;
  
    /* Set additional two octets if codec type is AMR(FR or HR) */
    if ((config->codecType == TM_CC_FR_MULTI_RATE_IN_USE) ||
        (config->codecType == TM_CC_HR_MULTI_RATE_IN_USE))
    {
        if (config->ICM > 3)
        {
            return TM_DCM_CC_ICM_ERROR;
        }
        buffer[index++] = config->ICM & 0x03; 

        buffer[index++] = config->codecSet;
    } 
    /* Fill up the length now */
    buffer[loc] = (index - len - 1);

    /* Set Supported Codec Type */
    buffer[index++] = TM_IEI_SUPPORTED_CODEC_TYPES;

    /* Remember the location to fill lengnth later */ 
    loc = len = index++;

    buffer[index++] = codecTypes->sysId;

    if (codecTypes->codecList > 127)
    {
        return TM_DCM_SCT_CODEC_LIST_ERROR;
    }  
    buffer[index++] = codecTypes->codecList & 0x3f;

    /* Set Codec List info. if bit 4, 5 both having 1 then the
     * same info will send twice. if any one of 4, 5 bit is 1
     * then info sent once */ 
    if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
        ((codecTypes->codecList & 0x10) >> 4 == 1) )
    {
        for (i = 0, j = 0; i < 2; i++, j++)
        {
            if (codecTypes->MACS[j] > 3)
            {
                return TM_DCM_SCT_MACS_ERROR;
            }
            buffer[index] = codecTypes->MACS[j] & 0x03;
                                                                                                                                              
            if (codecTypes->TFO_VER[j] > 3)
            {
                return TM_DCM_SCT_TFO_VER_ERROR;
            }
            buffer[index++] |= ((codecTypes->TFO_VER[j] & 0x03) << 2);
            buffer[index++] = codecTypes->SCS[j];
        }
    }
    else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
    {
        if (codecTypes->MACS[0] > 3)
        {
            return TM_DCM_SCT_MACS_ERROR;
        }
        buffer[index] = codecTypes->MACS[0] & 0x03;
       
        if (codecTypes->TFO_VER[0] > 3)
        {
            return TM_DCM_SCT_TFO_VER_ERROR;
        }
        buffer[index++] |= ((codecTypes->TFO_VER[0] & 0x03) << 2);
        buffer[index++] = codecTypes->SCS[0];
    }
      
    buffer[index++] = codecTypes->prefCodecType;

    /* Fill up the len now */
    buffer[loc] = (index - len - 1);

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Round Trip Delay Report Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodeRtdRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                    ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_RTD_REP *rtdRep = &msg->u.dcmMsg.u.rtdRep;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Round Trip Delay */
    buffer[index++] = TM_IEI_ROUND_TRIP_DELAY;

    if (rtdRep->delay > 1)
    {
        return TM_DCM_RTD_DELAY_IND_ERROR;
    }
    buffer[index] = rtdRep->delay & 0x01;

    if (rtdRep->RTD > 127)
    {
        return TM_DCM_RTD_ERROR;
    } 
    buffer[index++] |= ((rtdRep->RTD & 0x7f) << 1);
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Pre-Handover Notification Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodePreHandoNotif(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, loc, len;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.preHandoNotif.mrControl;
    TM_CODEC_CONFIG *config = &msg->u.dcmMsg.u.preHandoNotif.config;    
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Multi Rate Control */
    buffer[index++] = TM_IEI_MULTIRATE_CONTROL; 

    if (mrControl->TFO > 1)
    {
        return TM_DCM_MC_TFO_ERROR;
    }
    buffer[index] = mrControl->TFO & 0x01;
 
    if (mrControl->RAE > 3)
    {
        return TM_DCM_MC_RAE_ERROR; 
    }
    buffer[index] |= ((mrControl->RAE & 0x03) << 1);
  
    if (mrControl->PRE > 1)
    {
        return TM_DCM_MC_PRE_ERROR;
    }
    buffer[index++] |= ((mrControl->PRE & 0x01) << 3);
 
    /* Set Codec Configuration */
    buffer[index++] = TM_IEI_CODEC_CONFIGURATION;
                                                                                                                                              
    if (config->length < 1)
    {
        return TM_DCM_CC_LENGTH_ERROR;
    }

    /* Remember the location to fill length later */ 
    loc = len = index++;

    buffer[index++] = config->codecType;

    /* Set additional two octets if codec type is AMR(FR or HR) */
    if ((config->codecType == TM_CC_FR_MULTI_RATE_IN_USE) ||
        (config->codecType == TM_CC_HR_MULTI_RATE_IN_USE))
    {
        if (config->ICM > 3)
        {
            return TM_DCM_CC_ICM_ERROR;
        }
        buffer[index++] = config->ICM & 0x03;
                                                                                                                                              
        buffer[index++] = config->codecSet;
    }
 
    /* Fill up the length now */
    buffer[loc] = (index - len - 1);

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Multirate Codec Modification Request Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for MultiRate Codec Modification Ack message 
*       in DCM 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_encodeMrCodecModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.mrCodecModReq.mrConfig; 
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Multi Configuration if present */
    if (IS_PRESENT_TM_DCM_MCMR_MULTI_RATE_CONFIG(msg))
    {
        buffer[index++] =  TM_IEI_MULTIRATE_CONFIGURATION;  

        if (mrConfig->length < 0x2)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = mrConfig->length;

        memcpy(&buffer[index], &mrConfig->content[0], mrConfig->length);
        index += mrConfig->length;
    } 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Multirate Codec Modification Performed Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_encodeMrCodecModPer(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.mrCodecModPer.mrConfig; 
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Multi Configuration */
    buffer[index++] = TM_IEI_MULTIRATE_CONFIGURATION;
                                                                                                                                              
    if (mrConfig->length < 0x2)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = mrConfig->length;
                                                                                                                                              
    memcpy(&buffer[index], &mrConfig->content[0], mrConfig->length);
    index += mrConfig->length;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the TFO Request Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT
TM_DCM_encodeTfoRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                    ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_TFO_REP *tfoRep = &msg->u.dcmMsg.u.tfoRep;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set TFO Status */
    buffer[index++] = TM_IEI_TFO_STATUS;
 
    if (tfoRep->tfoStatus > 1)
    {
        return TM_DCM_TR_TFO_STATUS_ERROR;
    }  
    buffer[index++] = tfoRep->tfoStatus & 0x01;  

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the TFO Modification Request Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090 
*/
static ITS_INT                                                                                                               
TM_DCM_encodeTfoModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, j, len, loc;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.tfoModReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.tfoModReq.codecTypes;
                                                                                                                                              
    ret = TM_CCM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Multi Rate Control */
    buffer[index++] = TM_IEI_MULTIRATE_CONTROL;
                                                                                                                                              
    if (mrControl->TFO > 1)
    {
        return TM_DCM_MC_TFO_ERROR;
    }
    buffer[index] = mrControl->TFO & 0x01;
                                                                                                                                              
    if (mrControl->RAE > 3)
    {
        return TM_DCM_MC_RAE_ERROR;
    }
    buffer[index] |= ((mrControl->RAE & 0x03) << 1);
                                                                                                                                              
    if (mrControl->PRE > 1)
    {
        return TM_DCM_MC_PRE_ERROR;
    }
    buffer[index++] |= ((mrControl->PRE & 0x01) << 3);
 
    /* Set Supported Codec Type if present */
    if (IS_PRESENT_TM_DCM_TMR_SUPPORTED_CODEC_TYPE(msg))
    {
        buffer[index++] = TM_IEI_SUPPORTED_CODEC_TYPES;

        /* Remember the location to fill lengnth later */ 
        loc = len = index++;
                                                                                                                                              
        buffer[index++] = codecTypes->sysId;
                                                                                                                                              
        if (codecTypes->codecList > 127)
        {
            return TM_DCM_SCT_CODEC_LIST_ERROR;
        }
        buffer[index++] = codecTypes->codecList & 0x3f;
                                                                                                                                              
        /* Set Codec List info. if bit 4, 5 both having 1 then the
         * same info will send twice. if any one of 4, 5 bit is 1
         * then info sent once */
        if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            for (i = 0, j = 0; i < 2; i++, j++)
            {
                if (codecTypes->MACS[j] > 3)
                {
                    return TM_DCM_SCT_MACS_ERROR;
                }
                buffer[index] = codecTypes->MACS[j] & 0x03;
                                                                                                                                              
                if (codecTypes->TFO_VER[j] > 3)
                {
                    return TM_DCM_SCT_TFO_VER_ERROR;
                }
                buffer[index++] |= ((codecTypes->TFO_VER[j] & 0x03) << 2);
                buffer[index++] = codecTypes->SCS[j];
            }
        }
        else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
                ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            if (codecTypes->MACS[0] > 3)
            {
                return TM_DCM_SCT_MACS_ERROR;
            }
            buffer[index] = codecTypes->MACS[0] & 0x03;
                                                                                                                                              
            if (codecTypes->TFO_VER[0] > 3)
            {
                return TM_DCM_SCT_TFO_VER_ERROR;
            }
            buffer[index++] |= ((codecTypes->TFO_VER[0] & 0x03) << 2);
            buffer[index++] = codecTypes->SCS[0];
        }
                                                                                                                                              
        buffer[index++] = codecTypes->prefCodecType;

        /* Fill up the len now */
        buffer[loc] = (index - len - 1);
    }
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Location Information Message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0180, ID :: D0120
*/
static ITS_INT
TM_LCS_encodeLocationInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
                          ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_LCS_LOC_INFO *lcsLocInfo = &msg->u.lcsMsg.u.lcsLocInfo;
                                                                                                                                              
    ret = TM_encodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set LLP APDU */
    buffer[index++] = TM_IEI_LLP_APDU;

    buffer[index++] = lcsLocInfo->length;

    memcpy(&buffer[index], &lcsLocInfo->facIEI[0], lcsLocInfo->length);
    index += lcsLocInfo->length;
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}
                                                                                                                                              
/*implementation:internal 
* 
* PURPOSE:  
*       Display Reserved/Invalid Message Type.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       buffer - encoded value to be placed
*       size - size of filled buffer
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0120
*/
static ITS_INT
reserved(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size,
         ITS_OCTET *buffer)
{
    printf("Reserved/Invalid  Message Type \n");
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the common elements in Traffic Management msg's.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
*       index - starting pointer of the buffer 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This internal API is used by all the messages in Traffic Management
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0130, ID :: D0120
*/
static ITS_INT
TM_decodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *index,
                        ITS_OCTET *buffer)
{
    ITS_UINT value;
    TM_MSG_DESCRIMINATOR *msgDesc = &msg->genElemnts.msgDesc;

    /* Get Message Descriminator */ 
    value = buffer[*index] & 0x01;
    msgDesc->trasparent = value;

    value = (buffer[(*index)++] & 0xfe) >> 1;
    msgDesc->msgGruop = value;

    /* Get Message Type */
    msg->genElemnts.msgType = buffer[(*index)++];

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the common elements in Radio Link Layer Management.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
*       index - starting pointer of the buffer 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This internal API is used by all the messages in Traffic Management 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120
*/
static ITS_INT
TM_RLLM_decodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *index,
                             ITS_OCTET *buffer)
{
    ITS_UINT ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.rllmMsg.rllmGenElements.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.rllmMsg.rllmGenElements.linkId;

    ret = TM_decodeCommonElements(msg, index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get Channel Number */
    if (buffer[(*index)++] != TM_IEI_CHANNEL_NUMBER)
    {  
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    chanlNum->timeSlotNum = buffer[*index] & 0x07;
    chanlNum->chanlBits = ((buffer[(*index)++] & 0xf8) >> 3);

    /* Get Link Identifier */
    if (buffer[(*index)++] != TM_IEI_LINK_IDENTIFIER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    linkId->SAPI = buffer[*index] & 0x07;
    linkId->priority = ((buffer[*index] & 0x18) >> 3);
    linkId->NA = ((buffer[*index] & 0x20) >> 5);
    linkId->chanlBits = ((buffer[(*index)++] & 0xc0) >> 6);

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Data Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*      This same API is used for Data Indication, Unit Data Request and 
*      Unit Data indication messages in RLLM. 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120,
*                        ID :: D0100              
*/
static ITS_INT
TM_RLLM_decodeDataReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_L3_INFORMATION *l3Info = &msg->u.rllmMsg.u.dataReq.l3Info;

    ret = TM_RLLM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get L3 Information */
    if (buffer[index++] != TM_IEI_L3_INFORMATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    l3Info->lengthInd = buffer[index++];
    l3Info->lengthInd = (l3Info->lengthInd << 8) | buffer[index++];
    
    if (l3Info->lengthInd > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&l3Info->LLSDU[0], &buffer[index], l3Info->lengthInd);  
    index += l3Info->lengthInd;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Error Indication Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120
*/
static ITS_INT
TM_RLLM_decodeErrorInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_RLLM_ERROR_IND *errorInd = &msg->u.rllmMsg.u.errorInd;   

    ret = TM_RLLM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get RLM Cause */
    if (buffer[index++] != TM_IEI_RLM_CAUSE)
    {
       return TM_INFO_ELEMENT_ID_ERROR;
    }
 
    errorInd->rlmLen = buffer[index++];

    if ((buffer[index] >> 7) == 0)
    {
        errorInd->causeVal = buffer[index];
    }
    else
    {
        errorInd->causeVal = buffer[index + 1];
        errorInd->causeVal = (errorInd->causeVal << 8) | buffer[index++];
        index++;
    } 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Establish Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Establish Request, Establish Confirm,
*       Release Confirm, Release Indication messages in RLLM. 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120
*/
static ITS_INT
TM_RLLM_decodeEstaReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = TM_RLLM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Establish Indication Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120,
*                        ID :: D0100              
*/
static ITS_INT
TM_RLLM_decodeEstaInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_L3_INFORMATION *l3Info = &msg->u.rllmMsg.u.estInd.l3Info;
                                                                                                                                              
    ret = TM_RLLM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Intialise optional bit map to ZERO */    
    CLEAR_TM_RLLM_EI_OPTIONAL_BIT_MAP(msg);

    /* Get L3 Information if present */
    if (buffer[index] == TM_IEI_L3_INFORMATION)
    {
        index++;
        SET_TM_RLLM_EI_L3_INFO(msg);

        l3Info->lengthInd = buffer[index++];
        l3Info->lengthInd = (l3Info->lengthInd << 8) | buffer[index++];
     
        if (l3Info->lengthInd > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&l3Info->LLSDU[0], &buffer[index], l3Info->lengthInd);
        index += l3Info->lengthInd;                                                                                                               }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Release Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0140, ID :: D0120
*/
static ITS_INT
TM_RLLM_decodeRelReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_RLLM_REL_REQ *relReq = &msg->u.rllmMsg.u.relReq;
                                                                                                                                              
    ret = TM_RLLM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    /* Get Release Mode if present */
    if (buffer[index++] != TM_IEI_RELEASE_MODE)                                                            
    {
       return TM_INFO_ELEMENT_ID_ERROR;
    }
    
    relReq->modeBit = buffer[index] & 0x01;                            

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the common elements in CCM and DCM messages.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This internal API is used by all the messages in CCM and DCM
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeCommonElements(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *index,
                             ITS_OCTET *buffer)
{
    ITS_UINT value, ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum;

    ret = TM_decodeCommonElements(msg, index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get Channel Number */
    if (buffer[(*index)++] != TM_IEI_CHANNEL_NUMBER)
    {  
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    chanlNum->timeSlotNum = buffer[*index] & 0x07;
    chanlNum->chanlBits = ((buffer[(*index)++] & 0xf8) >> 3);

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the BCCH Information Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeBcchInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_BCCH_INFO *bcchInfo = &msg->u.ccmMsg.u.bcchInfo;
    TM_FULL_BCCH_INFO *fullBcch = &msg->u.ccmMsg.u.bcchInfo.fullBcch;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    if (buffer[index++] != TM_IEI_SYSTEM_INFO_TYPE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;  
    }

    /* Get System Info Type */
    bcchInfo->sysInfoType = buffer[index++];
                                                                                                                                              
    /* Intialise optional bit map to ZERO */ 
    CLEAR_TM_CCM_BI_OPTIONAL_BIT_MAP(msg);

    /* Get Full BCCH Inforamtion if present */
    if (buffer[index] == TM_IEI_FULL_BCCH_INFORMATION)
    {
        index++; 
        SET_TM_CCM_BI_FULL_BCCH_INFO(msg);

        fullBcch->length = buffer[index++];
        if (fullBcch->length != 23)
        {
            return TM_DCM_BI_BCCH_INFO_LEN_ERROR;
        }
        memcpy(&fullBcch->msg[0], &buffer[index], fullBcch->length);
    }

    /* Get Starting Time if present */
    if (buffer[index] == TM_IEI_STARTING_TIME)
    {
        index++; 
        SET_TM_CCM_BI_STARTING_TIME(msg);

        bcchInfo->startingTime = buffer[index++];
        bcchInfo->startingTime = (bcchInfo->startingTime << 8) | buffer[index++];
    }
    
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the CCCH Load Indication Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeCcchLoadInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.ccmMsg.ccmGenElements.chanlNum;
    TM_RACH_LOAD *rach = &msg->u.ccmMsg.u.ccchLoadInd.rach;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get RACH Info if present */
    if (chanlNum->chanlBits == TM_CN_UPLINK_CCCH)
    {
        if (buffer[index++] != TM_IEI_RACH_LOAD)
        {
            return TM_INFO_ELEMENT_ID_ERROR;
        }
        
        rach->length = buffer[index++];

        rach->slotCount = buffer[index++];
        rach->slotCount = (rach->slotCount << 8) | buffer[index++];

        rach->busyCount = buffer[index++];
        rach->busyCount = (rach->busyCount << 8) | buffer[index++];

        rach->accessCount = buffer[index++];
        rach->accessCount = (rach->accessCount << 8) | buffer[index++];

        memcpy(&rach->info[0], &buffer[index], (rach->length - 6));
        index += (rach->length - 6);
    }

    /* Get paging buffer space if present */
    if (chanlNum->chanlBits == TM_CN_DOWNLINK_CCCH)
    {
        if (buffer[index++] != TM_IEI_PAGING_LOAD)
        {
            return TM_INFO_ELEMENT_ID_ERROR;
        }  
        
        msg->u.ccmMsg.u.ccchLoadInd.pagBufSpace = buffer[index++];
        msg->u.ccmMsg.u.ccchLoadInd.pagBufSpace = 
             (msg->u.ccmMsg.u.ccchLoadInd.pagBufSpace << 8) | buffer[index++];
    }
                                                    
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Change Required Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeChanRqd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_CHAN_RQD *chanRqd = &msg->u.ccmMsg.u.chanRqd;
    TM_PHYSICAL_CONTEXT *phyContext = &msg->u.ccmMsg.u.chanRqd.phyContext; 
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
   
    if (buffer[index++] != TM_IEI_REQUEST_REFERENCE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }                                                            
     
    /* Get Random Access Info */
    chanRqd->RA = buffer[index++];

    memcpy(&chanRqd->reqRefNum, &buffer[index], 2);
    index += 2;

    if (buffer[index++] != TM_IEI_ACCESS_DELAY)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }                                                   

    /* Get access delay */
    chanRqd->accessDelay = buffer[index++];

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_CCM_CR_OPTIONAL_BIT_MAP(msg);

    /* Get the physical context if present */
    if (buffer[index] == TM_IEI_PHYSICAL_CONTEXT)
    {
        index++;
        SET_TM_CCM_CR_PHYSICAL_CONTEXT(msg);

        phyContext->length = buffer[index++];

        memcpy(&phyContext->content[0], &buffer[index], phyContext->length);
        index += phyContext->length;  
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Delete Indication Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Immediate Assign Command msg in CCM.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeDeleteInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_DELETE_IND *deleteInd = &msg->u.ccmMsg.u.deleteInd;      
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                      
   /* Get Immediate Assignment Info */ 
    if (buffer[index++] != TM_IEI_FULL_IMMEDIATE_ASSIGN_INFO)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }                                                             

    deleteInd->length = buffer[index++];
    if (deleteInd->length > 23)
    {
        return TM_CCM_DI_FULL_IMMD_LEN_ERROR;
    }

    memcpy(&deleteInd->assignInfo[0], &buffer[index], deleteInd->length);
    index += deleteInd->length;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Paging Command Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodePagingCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_PAGING_CMD *pagingCmd = &msg->u.ccmMsg.u.pagingCmd;
    TM_MS_IDENTITY *msIdentity = &msg->u.ccmMsg.u.pagingCmd.msIdentity;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    if (buffer[index++] != TM_IEI_PAGING_GROUP)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }                                        

    /* Get paging Group info */
    pagingCmd->pagingGroup = buffer[index++];

    /* Get MS Identity */
    if (buffer[index++] != TM_IEI_MS_IDENTITY)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    msIdentity->length = buffer[index++];

    memcpy(&msIdentity->identity[0], &buffer[index], msIdentity->length);
    index += msIdentity->length;

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_CCM_PC_OPTIONAL_BIT_MAP(msg);

    /* Get Channel indicator if present */
    if (buffer[index] == TM_IEI_CHANNEL_NEEDED)
    {
        index++;
        SET_TM_CCM_PC_CHANNEL_NEEDED(msg);

        pagingCmd->chanlNeed = buffer[index++] & 0x03;
    }

    /* Get call priority info if present */ 
    if (buffer[index] == TM_IEI_EMLPP_PRIORITY)
    {
        index++;
        SET_TM_CCM_PC_EMLPP_PRIORITY(msg);

        pagingCmd->callPriority = buffer[index++] & 0x07;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the SMS Broadcast Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeSmsBcReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_SMS_BC_REQ *smsBcReq = &msg->u.ccmMsg.u.smsBcReq; 
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    if (buffer[index++] != TM_IEI_SMSCB_INFORMATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }                                                                   
 
    /* Needs to be re-checked. Specification says buffer is 23 bytes value
     * But looks like length field is missing. since we are maintaining len
     * field, assign 23 to it  
     */
    smsBcReq->smscbInfoLen = 23;

    memcpy(&smsBcReq->smscbInfo, &buffer[index], smsBcReq->smscbInfoLen);
    index += smsBcReq->smscbInfoLen;

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_CCM_SBR_OPTIONAL_BIT_MAP(msg);
  
    /* Get Channel Indicator if present*/
    if (buffer[index] == TM_IEI_SMSCB_CHANNEL_INDICATOR)
    {
        index++;
        SET_TM_CCM_SBR_SMSCB_CHANNEL_IND(msg);

        smsBcReq->chanlInd = buffer[index++] & 0x0f;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the RF Resource Indication Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120
*/
static ITS_INT
TM_TRXM_decodeRfResInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, len;
    TM_TRAX_RF_RES_IND *rfResInd = &msg->u.trxmMsg.u.rfResInd;
                                                                                                                                              
    ret = TM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    if (buffer[index++] != TM_IEI_RESOURCE_INFORMATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Check the length in even number */
    if ((buffer[index] % 2) != 0)
    {
        return TM_TRXM_RRI_LENGTH_ERROR;
    }
    rfResInd->length = buffer[index++];

    len = index - 1;

    /* Get the resource information */
    for (i = 0; i < (rfResInd->length/2); i++)
    {
         rfResInd->info[i].chanlNum.timeSlotNum = buffer[index] & 0x07;

         rfResInd->info[i].chanlNum.chanlBits = (buffer[index++] & 0xf8) >> 3;

         rfResInd->info[i].interfBand = (buffer[index++] & 0xe0) >> 5;
    }
 
    if (rfResInd->length != (index - len - 1))
    {
        return TM_TRXM_RI_LENGTH_ERROR;
    }
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the SACCH Filling Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120
*/
static ITS_INT
TM_TRXM_decodeSacchFill(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_TRAX_SACCH_FILL *sacchFill = &msg->u.trxmMsg.u.sacchFill;
    TM_L3_INFORMATION *l3Info = &msg->u.trxmMsg.u.sacchFill.l3Info;
                                          
    ret = TM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    if (buffer[index++] != TM_IEI_SYSTEM_INFO_TYPE)
    {
        return TM_INFO_ELEMENT_ID_ERROR; 
    }
  
    /* Get System Info Type */ 
    sacchFill->sysInfoType = buffer[index++];

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_TRXM_SF_OPTIONAL_BIT_MAP(msg);

    /* Get L3 Information if present */
    if (buffer[index] == TM_IEI_L3_INFORMATION)
    {
        index++;
        SET_TM_TRXM_SF_L3_INFO(msg);

        l3Info->lengthInd = buffer[index++];
        l3Info->lengthInd = (l3Info->lengthInd << 8) | buffer[index++];
    
        if (l3Info->lengthInd > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&l3Info->LLSDU[0], &buffer[index], l3Info->lengthInd);
        index += l3Info->lengthInd;     
    }
 
    /* Get Starting time if present */
    if (buffer[index] == TM_IEI_STARTING_TIME)
    {
        index++;
        SET_TM_TRXM_SF_STARTING_TIME(msg);

        sacchFill->startingTime = buffer[index++];
        sacchFill->startingTime = (sacchFill->startingTime << 8) | buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Overload Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120
*/
static ITS_INT
TM_TRXM_decodeOverload(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_TRAX_OVERLOAD *overload = &msg->u.trxmMsg.u.overload;                                                                                                                                              
    ret = TM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    if (buffer[index++] != TM_IEI_CAUSE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get Cause length */
    overload->length = buffer[index++];

    /* Get cause value and diagnostics if any */ 
    if ((buffer[index] & 0x80) >> 7)
    {
        overload->causeVal = buffer[index + 1];
        overload->causeVal = (overload->causeVal << 8) | buffer[index++];
        index++; 
        if ((overload->length - 2) > 0)
        {
            memcpy(&overload->diagnostics[0], &buffer[index], 
                    overload->length - 2);
            index += (overload->length - 2);
        }
    }
    else
    {
        overload->causeVal = buffer[index++];
        if ((overload->length - 1) > 0)
        {
            memcpy(&overload->diagnostics[0], &buffer[index], 
                    overload->length - 1);
            index += (overload->length - 1);
        }
    } 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Error Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0170, ID :: D0120
*/
static ITS_INT
TM_TRXM_decodeErrorReport(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CAUSE *cause = &msg->u.trxmMsg.u.errorReport.cause;
    TM_TRAX_ERROR_REPORT *errorReport = &msg->u.trxmMsg.u.errorReport;
    TM_CHANNEL_NUMBER *chanlNum = &msg->u.trxmMsg.u.errorReport.chanlNum;
    TM_LINK_IDENTIFIER *linkId = &msg->u.trxmMsg.u.errorReport.linkId;
    TM_ERRONEOUS_MSG *errMsg = &msg->u.trxmMsg.u.errorReport.errMsg;
                                                                                                                                              
    ret = TM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_CAUSE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
                                                                                                                                              
    /* Get Cause length */
    cause->length = buffer[index++];
                                                                                                                                              
    /* Get cause value and diagnostics if any */
    if ((buffer[index] & 0x80) >> 7)
    {
        cause->causeVal = buffer[index + 1];
        cause->causeVal = (cause->causeVal << 8) | buffer[index++];
        index++; 
        if ((cause->length - 2) > 0)
        {
            memcpy(&cause->diagnostics[0], &buffer[index], cause->length - 2);
            index += (cause->length - 2);
        }
    }
    else
    {
        cause->causeVal = buffer[index++];
        if ((cause->length - 1) > 0)
        {
            memcpy(&cause->diagnostics[0], &buffer[index], cause->length - 1);
            index += (cause->length - 1);
        }
    }

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_TRXM_ER_OPTIONAL_BIT_MAP(msg);

    /* Get Message Identifier if present */
    if (buffer[index] == TM_IEI_MESSAGE_IDENTIFIER)
    {
        index++;
        SET_TM_TRXM_ER_MESSAGE_IDENTIFIER(msg);

        errorReport->msgId = buffer[index++]; 
    }
 
    /* Get Channel number info if present */
    if (buffer[index] == TM_IEI_CHANNEL_NUMBER)
    {
        index++;
        SET_TM_TRXM_ER_CHANNEL_NUMBER(msg);

        chanlNum->timeSlotNum = buffer[index] & 0x07;
                                                                                                                                              
        chanlNum->chanlBits = (buffer[index++] & 0xf8) >> 3;
    }

    /* Get Link Identifier Info If present */
    if (buffer[index] == TM_IEI_LINK_IDENTIFIER)
    {
        index++;
        SET_TM_TRXM_ER_LINK_IDENTIFIER(msg);

        linkId->SAPI = buffer[index] & 0x07;
                                                                                                                                              
        linkId->priority = (buffer[index] & 0x18) >> 3;
                                                                                                                                              
        linkId->NA = (buffer[index] & 0x20) >> 5;
                                                                                                                                              
        linkId->chanlBits = (buffer[index++] & 0xc0) >> 6;
    }

    if (buffer[index] == TM_IEI_ERRONEOUS_MESSAGE)
    {
        index++;
        SET_TM_TRXM_ER_ERRONEOUS_MSG(msg);

        errMsg->length = buffer[index++];
        if (errMsg->length < 1)
        {
            return TM_TRXM_ER_ERRONS_LEN_ERROR;
        }

        memcpy(&errMsg->recvdMsg[0], &buffer[index], errMsg->length);
        index += errMsg->length;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the SMS Broadcast Command Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeSmsBcCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CB_CMD_TYPE *cmdType = &msg->u.ccmMsg.u.smsBcCmd.cmdType; 
    TM_SMSCB_MSG *smscbMsg = &msg->u.ccmMsg.u.smsBcCmd.smscbMsg;
    TM_CCM_SMS_BC_CMD *smsBcCmd = &msg->u.ccmMsg.u.smsBcCmd;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    if (buffer[index++] != TM_IEI_CB_COMMAND_TYPE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get Command Type details */
    cmdType->lastlock = buffer[index] & 0x03;

    cmdType->broadcast = ((buffer[index] & 0x08) >> 3); 
 
    cmdType->command = (buffer[index++] & 0xf0) >> 4;
 
    /* Get SMSCB msg */
    if (buffer[index++] != TM_IEI_SMSCB_MESSAGE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    smscbMsg->length = buffer[index++];

    memcpy(&smscbMsg->msg, &buffer[index], smscbMsg->length);
    index += smscbMsg->length;

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_CCM_SBC_OPTIONAL_BIT_MAP(msg);

    /* Get Channel indicator if present*/ 
    if (buffer[index] == TM_IEI_SMSCB_CHANNEL_INDICATOR)
    {
        index++;
        SET_TM_CCM_SBC_SMSCB_CHANNEL_IND(msg);

        smsBcCmd->chanlInd = buffer[index++] & 0x0f;
    }
 
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the CBCH Load Indication Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeCbchLoadInd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_CCM_CBCH_LOAD_IND *cbchLoadInd = &msg->u.ccmMsg.u.cbchLoadInd;
    
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_CBCH_LOAD_INFORMATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR; 
    }

    cbchLoadInd->slotCount = buffer[index] & 0x0f;

    cbchLoadInd->type = (buffer[index++] & 0x80) >> 7;

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_CCM_CLI_OPTIONAL_BIT_MAP(msg);

    /* Get Channel indicator if present*/
    if (buffer[index] == TM_IEI_SMSCB_CHANNEL_INDICATOR)
    {
        index++;
        SET_TM_CCM_CLI_SMSCB_CHANNEL_IND(msg);
        cbchLoadInd->chanlInd = buffer[index++] & 0x0f;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Notification Command Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0160, ID :: D0120
*/
static ITS_INT
TM_CCM_decodeNotCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_COMMAND_IND *cmdInd = &msg->u.ccmMsg.u.notCmd.cmdInd;
    TM_GROUP_CALL_REF *callRef = &msg->u.ccmMsg.u.notCmd.callRef;
    TM_GROUP_CHANNEL_DESC *chanlDesc = &msg->u.ccmMsg.u.notCmd.chanlDesc;
    TM_NCH_DRX_INFO *nchDrx = &msg->u.ccmMsg.u.notCmd.nchDrx;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get Command Indicator */
    if (buffer[index++] != TM_IEI_COMMAND_INDICATOR)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    cmdInd->length = buffer[index++];

    /* Get command Value based on 8 bit */
    if (buffer[index] >> 7)
    {
        cmdInd->cmdVal = buffer[index + 1];
        cmdInd->cmdVal = (cmdInd->cmdVal << 8) | buffer[index++];
        index++;
    }
    else
    {
        cmdInd->cmdVal = buffer[index++];
    } 

    /* Intilase optional bit map to ZERO */
    CLEAR_TM_CCM_NC_OPTIONAL_BIT_MAP(msg);
 
    /* Get callref details if present */
    if (buffer[index] == TM_IEI_GROUP_CALL_REFERENCE)
    {
        index++;
        SET_TM_CCM_NC_GROUP_CALL_REFERENCE(msg);

        callRef->length = buffer[index++];
        if ((callRef->length < 1) || (callRef->length > 6))
        {
            return TM_CCM_NC_CALL_REF_LEN_ERROR;
        }

        memcpy(&callRef->descGroup[0], &buffer[index], callRef->length);
        index += callRef->length;
    }

    /* Get channel description info if present */
    if (buffer[index] == TM_IEI_CHANNEL_DESCRIPTION)
    {
        index++;
        SET_TM_CCM_NC_CHANNEL_DESCRIPTION(msg);
    
        chanlDesc->length = buffer[index++];     

        memcpy(&chanlDesc->chanlDesc[0], &buffer[index], chanlDesc->length);
        index += chanlDesc->length;
    }

    /* Get NCH DRX info if present */
    if (buffer[index] == TM_IEI_NCH_DRX_INFORMATION)
    {
        index++;
        SET_TM_CCM_NC_NCH_DRX_INFO(msg);

        nchDrx->length = buffer[index++]; 

        nchDrx->NLN = buffer[index] & 0x03;
 
        nchDrx->emlpp = (buffer[index] & 0x1c) >> 2;

        nchDrx->status = (buffer[index++] & 0x20) >> 5;
    }  

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Channel Activation Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*                        ID :: D0090              
*/
static ITS_INT
TM_DCM_decodeChanActiv(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, j, len; 
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

    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
 
    /* Get Activation Type */
    if (buffer[index++] != TM_IEI_ACTIVATION_TYPE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    chanActiv->actType = buffer[index] & 0x07; 
    chanActiv->procedure = ((buffer[index++] & 0x80) >> 7);

    /* Get Channel Mode */
    if (buffer[index++] != TM_IEI_CHANNEL_MODE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    chnlMode->length = buffer[index++];

    len = index - 1;

    chnlMode->dtxu = (buffer[index] & 0x01);
    chnlMode->dtxd = ((buffer[index++] & 0x02) >> 1);
    chnlMode->indicator = buffer[index++];
    chnlMode->rateAndType = buffer[index++];

    /* Check and Get Speech coding algrithm + trasp ind */
    if (chnlMode->indicator == TM_CM_SIGNALLING)
    {
        chnlMode->codingAlg = 0x00;
        index++;
    }
    else if (chnlMode->indicator == TM_CM_DATA)
    {
        chnlMode->rate = (buffer[index] & 0x3f); 
        chnlMode->service = ((buffer[index++] & 0x40) >> 6); 
    }
    else if (chnlMode->indicator == TM_CM_SPEECH)
    {
        chnlMode->codingAlg = buffer[index++];
    }
    else
    {
        index++;
    }

    if (chnlMode->length != (index - len - 1))
    {
        return TM_DCM_CA_CHANL_ID_LEN_ERROR;
    }

    /* Intialise optional bit map to ZERO */ 
    CLEAR_TM_DCM_CA_OPTIONAL_BIT_MAP(msg);

    /* Get Channel Identification if present */
    if (buffer[index] == TM_IEI_CHANNEL_IDENTIFICATION) 
    {
        index++;
        SET_TM_DCM_CA_CHANNEL_ID(msg); 

        chnlId->length = buffer[index++];

        /* The Channel Identification buffer should be 4 or more bytes.
         * it is shown in section 10.5.2.21 from 04.18 spec 
         */
        if (chnlId->length < 4)
        {
            return TM_DCM_CA_CHANL_ID_LEN_ERROR;
        }
        memcpy(&chnlId->chanlDesc[0], &buffer[index], 4);
        index += 4;

        memcpy(&chnlId->mobAlloc[0], &buffer[index], (chnlId->length - 4));
        index += (chnlId->length - 4);
    }
 
    /* Get Encryption Information if present */
    if (buffer[index] == TM_IEI_ENCRYPTION_INFORMATION)
    {
        index++;
        SET_TM_DCM_CA_ENCRYPT_INFO(msg);
        encrption->length = buffer[index++];
        if (encrption->length < 1)
        {
            return TM_DCM_EI_LENGTH_ERROR;
        }
                                                                                                                                              
        encrption->algorithmId = buffer[index++];
                                                                                                                                              
        memcpy(&encrption->key[0], &buffer[index], (encrption->length - 1));
        index += (encrption->length -1);
    }

    /* Get Handover Reference if present */
    if ((chanActiv->actType == TM_AT_ASYNCRONOUS_HANDOVER) ||
        (chanActiv->actType == TM_AT_SYNCRONOUS_HANDOVER))
    {
        if (buffer[index++] != TM_IEI_HANDOVER_REFERENCE)
        {
            return TM_INFO_ELEMENT_ID_ERROR;
        }
        chanActiv->handRef = buffer[index++];
    }

    /* Get BS Power if present */
    if (buffer[index] == TM_IEI_BS_POWER)
    {
        index++;
        SET_TM_DCM_CA_BS_POWER(msg);

        bsPower->powerLevel = buffer[index] & 0x0f;
        bsPower->FPC = ((buffer[index++] & 0x10) >> 4);
    }

    /* Get MS Power if present */
    if (buffer[index] == TM_IEI_MS_POWER)
    {
        index++;
        SET_TM_DCM_CA_MS_POWER(msg);

        msPower->powerLevel = buffer[index] & 0x1f;
        msPower->FPC = ((buffer[index++] & 0x20) >> 5);
    }

    /* Get Timing Advance */
    if ((chanActiv->actType == TM_AT_IMMEDIATE_ASSIGNMENT) ||
        (chanActiv->actType == TM_AT_NORMAL_ASSIGNMENT))
    {
        if (buffer[index++] != TM_IEI_TIMING_ADVANCE)
        {
            return TM_INFO_ELEMENT_ID_ERROR;
        }
        chanActiv->timingAdv = buffer[index++]; 
    }

    /* Get BS Power Parameters if present */
    if (buffer[index] == TM_IEI_BS_POWER_PARAMETERS)
    {
        index++;
        SET_TM_DCM_CA_BS_POWER_PARAM(msg);

        bsParams->length = buffer[index++];
                                                                                                                                              
        memcpy(&bsParams->powerControl[0], &buffer[index], bsParams->length);
        index += bsParams->length;
    }


    /* Get MS Power Parameters if present */
    if (buffer[index] == TM_IEI_MS_POWER_PARAMETERS)
    {
        index++;
        SET_TM_DCM_CA_MS_POWER_PARAM(msg);

        msParams->length = buffer[index++];
                                                                                                                                              
        memcpy(&msParams->powerControl[0], &buffer[index], msParams->length);
        index += msParams->length;
    }

    /* Get Physical Context if present */
    if (buffer[index] == TM_IEI_PHYSICAL_CONTEXT)
    {
        index++; 
        SET_TM_DCM_CA_PHYSICAL_CONTEXT(msg);

        phyCnxt->length = buffer[index++];
                                                                                                                                              
        memcpy(&phyCnxt->content[0], &buffer[index], phyCnxt->length);
        index += phyCnxt->length;
    }

    /* Get SAACH Inforamtion if present */
    if (buffer[index] == TM_IEI_SACCH_INFORMATION)
    {
        index++;
        SET_TM_DCM_CA_SAACH_INFO(msg);

        sacchInfo->length = buffer[index++];
        
        len = index - 1;
        /* User has to free the allocated memory. This allocation is done
         * by keeping in mind of that static allocation is consuming more
         * memory for every message in traffic management.
         */
        sacchInfo->msgInfo = (TM_SACCH_MSG_INFO *)malloc(sacchInfo->length);

        sacchInfo->numOfMsgs = buffer[index++];

        for (i = 0; i < sacchInfo->numOfMsgs; i++)
        {
            sacchInfo->msgInfo[i].typeOfMsg = buffer[index++];
            sacchInfo->msgInfo[i].length = buffer[index++];
            memcpy(&sacchInfo->msgInfo[i].msg, &buffer[index], 
                    sacchInfo->msgInfo[i].length);
            index += sacchInfo->msgInfo[i].length;
        }

        if (sacchInfo->length != (index - len - 1))
        {
            return TM_DCM_CA_SACCH_LEN_ERROR;
        }  
    }

    /* Get UIC if present */
    if (buffer[index] == TM_IEI_UIC)
    {
        index++;
        SET_TM_DCM_CA_UIC(msg);

        chanActiv->uicLen = buffer[index++];
        chanActiv->uicInfo = buffer[index++]; 
    }

    /* Get Main Channel Reference if present */
    if (buffer[index] == TM_IEI_MAIN_CHANNEL_REFERENCE)
    {
        index++;
        SET_TM_DCM_CA_MAIN_CHANNEL_REF(msg);
        chanActiv->mainChnlRefTn = buffer[index++] & 0x07;
    }

    /* Get MultiRate Configuration if present */
    if (buffer[index] == TM_IEI_MULTIRATE_CONFIGURATION)
    {
        index++;
        SET_TM_DCM_CA_MULTI_RATE_CONFIG(msg);

        mrConfig->length = buffer[index++];
        if (mrConfig->length < 0x2)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&mrConfig->content[0], &buffer[index], mrConfig->length);
        index += mrConfig->length;
    }

    /* Get MultiRate Control if present */
    if (buffer[index] == TM_IEI_MULTIRATE_CONTROL)
    {
        index++;
        SET_TM_DCM_CA_MULTI_RATE_CONTROL(msg);

        mrControl->TFO = buffer[index] & 0x01;
        mrControl->RAE = ((buffer[index] & 0x06) >> 1);
        mrControl->PRE = ((buffer[index++] & 0x08) >> 3);
    }

    /* Get Supported Codec types if present */
    if (buffer[index] == TM_IEI_SUPPORTED_CODEC_TYPES)
    {
        index++;
        SET_TM_DCM_CA_SUPPORTED_CODEC_TYPES(msg); 

        codecTypes->length = buffer[index++];

        len = index -1;

        codecTypes->sysId = buffer[index++];
        codecTypes->codecList = buffer[index++];
                                                                                                                                              
        /* Get Codec List info. if bit 4, 5 both having 1 then the
         * same info will be coming twice. if any one of the 4, 5 bit is 1
         * then info will come once */
        if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            for (i = 0, j = 0; i < 2; i++, j++)
            {
                codecTypes->MACS[j] = buffer[index] & 0x03;
                codecTypes->TFO_VER[j] = (buffer[index++] & 0x0c) >> 2;
                codecTypes->SCS[j] = buffer[index++];
            }
        }
        else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
                ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            codecTypes->MACS[0] = buffer[index] & 0x03;
            codecTypes->TFO_VER[0] = (buffer[index++] & 0x0c) >> 2;
            codecTypes->SCS[0] = buffer[index++];
        }
                                                                                                                                              
        /* Get preffered Codec Type */
        codecTypes->prefCodecType = buffer[index++];

        if (codecTypes->length != (index - len -1))
        {
            return TM_DCM_CA_SUP_CODEC_LEN_ERROR;
        }
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Channel Activation Ack Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeChanActivAck(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_CHAN_ACTIV_ACK *chanActivAck = &msg->u.dcmMsg.u.chanActivAck;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get Frame Number */
    if (buffer[index++] != TM_IEI_FRAME_NUMBER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    chanActivAck->frameNum = buffer[index++];
    chanActivAck->frameNum = (chanActivAck->frameNum << 8) | buffer[index++]; 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Channel Activation Nack Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Connection Failure indication,
*       Mode Modify NAck, Multirate Codec Modifcation NAck msg's in DCM. 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeChanActivNack(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_CHAN_ACTIV_NACK *chanActivNack = &msg->u.dcmMsg.u.chanActivNack;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    if (buffer[index++] != TM_IEI_CAUSE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
                                                                                                                                              
    /* Get Cause length */
    chanActivNack->length = buffer[index++];
                                                                                                                                              
    /* Get cause value and diagnostics if any */
    if ((buffer[index] & 0x80) >> 7)
    {
        chanActivNack->causeVal = buffer[index + 1];
        chanActivNack->causeVal = (chanActivNack->causeVal << 8) | buffer[index++];
        index++; 
        if ((chanActivNack->length - 2) > 0)
        {
            memcpy(&chanActivNack->diagnostics[0], &buffer[index], 
                    chanActivNack->length - 2);
            index += (chanActivNack->length - 2);
        }
    }
    else
    {
        chanActivNack->causeVal = buffer[index++];
        if ((chanActivNack->length - 1) > 0)
        {
            memcpy(&chanActivNack->diagnostics[0], &buffer[index], 
                    chanActivNack->length - 1);
            index += (chanActivNack->length - 1);
        }
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Deactivate SACCH Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Mode Modify Acknowledge, 
*       Physical Context Request, RF Channel Release, RF Channel Release Ack
*       messages in DCM.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeDeactivateSaach(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;

    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Encryption Command Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0100              
*/
static ITS_INT
TM_DCM_decodeEncrCmd(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_ENCRYPTION_INFO *encryption = &msg->u.dcmMsg.u.encrCmd.encryption;
    TM_LINK_IDENTIFIER *linkId = &msg->u.dcmMsg.u.encrCmd.linkId;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.encrCmd.l3Info;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_ENCRYPTION_INFORMATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get the Encryption Information */ 
    encryption->length = buffer[index++];
    if (encryption->length < 1)
    {
        return TM_DCM_EI_LENGTH_ERROR;
    }  
                                                                                                                                              
    encryption->algorithmId = buffer[index++];
                                                                                                                                              
    memcpy(&encryption->key[0], &buffer[index], encryption->length - 1);
    index += (encryption->length - 1);
                                                                                                                                              
    /* Get Link Identifier */
    if (buffer[index++] != TM_IEI_LINK_IDENTIFIER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    linkId->SAPI = buffer[index] & 0x07;
                                                                                                                                              
    linkId->priority = (buffer[index] & 0x18) >> 3;
                                                                                                                                              
    linkId->NA = (buffer[index] & 0x20) >> 5;
                                                                                                                                              
    linkId->chanlBits = (buffer[index++] & 0xc0) >> 6;

     /* Get L3 Information */
    if (buffer[index++] != TM_IEI_L3_INFORMATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
                                                                                                                                              
    l3Info->lengthInd = buffer[index++];
    l3Info->lengthInd = (l3Info->lengthInd << 8) | buffer[index++];
    
    if (l3Info->lengthInd > 0x03)
    {
        return CONTENT_LENGTH_ERROR;
    }
                                                                                                                                          
    memcpy(&l3Info->LLSDU[0], &buffer[index], l3Info->lengthInd);
    index += l3Info->lengthInd;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Handover Detection Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for Talker Detection, Listener Detection
*       messages in DCM 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeHandoDet(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_HANDO_DET *handoDet = &msg->u.dcmMsg.u.handoDet;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_DCM_HD_OPTIONAL_BIT_MAP(msg);
 
    /* Get Access Delay if present */
    if (buffer[index] == TM_IEI_ACCESS_DELAY)
    {
        index++;
        SET_TM_DCM_HD_ACCESS_DELAY(msg);

        handoDet->accessDelay = buffer[index++];
    } 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Measurement Result Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0100              
*/
static ITS_INT
TM_DCM_decodeMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_MEAS_RES *measRes = &msg->u.dcmMsg.u.measRes;
    TM_UPLINK_MEAS *uplinkMeas = &msg->u.dcmMsg.u.measRes.uplinkMeas;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.measRes.bsPower;
    TM_L1_INFORMATION *l1Info = &msg->u.dcmMsg.u.measRes.l1Info;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.measRes.l3Info;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_MEASUREMENT_RESULT_NUMBER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    measRes->measResultNum = buffer[index++];

    if (buffer[index++] != TM_IEI_UPLINK_MEASUREMENTS)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get Uplink Measurement Info */
    if ( buffer[index] < 3)
    {
        return TM_DCM_UM_LENGTH_ERROR;
    } 
    uplinkMeas->length = buffer[index++];
    uplinkMeas->rxlevFullUp = buffer[index] & 0x3f;
    uplinkMeas->dtxd = (buffer[index] & 0x40) >> 6;
    uplinkMeas->rfu = (buffer[index++] & 0x80) >> 7; 
    uplinkMeas->rxlevSubUp = buffer[index++] & 0x3f;
    uplinkMeas->rxqualSubUp = buffer[index] & 0x07;
    uplinkMeas->rxqualFullUp = (buffer[index++] & 0x38) >> 3;

    if ((uplinkMeas->length - 3) > 0)
    {
        memcpy(&uplinkMeas->SMI[0], &buffer[index], uplinkMeas->length - 3); 
        index += (uplinkMeas->length - 3);
    } 

    /* Get BS Power msg Info */
    if (buffer[index++] != TM_IEI_BS_POWER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }    

    bsPower->powerLevel = buffer[index] & 0x0f;

    bsPower->FPC = (buffer[index++] & 0x10) >> 4;

    /* Initialse optional bit map to ZERO */
    CLEAR_TM_DCM_MR_OPTIONAL_BIT_MAP(msg);
 
    /* Get L1 Info if present */
    if (buffer[index] == TM_IEI_L1_INFORMATION)
    {
        index++;
        SET_TM_DCM_MR_L1_INFO(msg);

        l1Info->FPC = (buffer[index] & 0x04) >> 2;

        l1Info->powerLevel = (buffer[index++] & 0xf8) >> 3;

        l1Info->timingAdvns = buffer[index++];
    } 

    /* Get L3 Information if present */
    if (buffer[index] == TM_IEI_L3_INFORMATION)
    {
        index++;
        SET_TM_DCM_MR_L3_INFO(msg); 

        l3Info->lengthInd = buffer[index++];
        l3Info->lengthInd = (l3Info->lengthInd << 8) | buffer[index++];
    
        if (l3Info->lengthInd != 18)
        {
            return CONTENT_LENGTH_ERROR;
        }
        memcpy(&l3Info->LLSDU[0], &buffer[index], l3Info->lengthInd);
        index += l3Info->lengthInd;    
    }

    /* Get MS Timing Offset if present */
    if (buffer[index] == TM_IEI_MS_TIMING_OFFSET)
    {
        index++;
        SET_TM_DCM_MR_MS_TIMING_OFFSET(msg);

        measRes->timingOffset = buffer[index++];
    }
  
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Mode Modify Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090              
*/
static ITS_INT
TM_DCM_decodeModeModifyReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, j, len;
    TM_CHANNEL_MODE *chnlMode = &msg->u.dcmMsg.u.modeModifyReq.chnlMode;
    TM_ENCRYPTION_INFO *encrption = &msg->u.dcmMsg.u.modeModifyReq.encryption;
    TM_DCM_MODE_MODIFY_REQ *modeModifyReq = &msg->u.dcmMsg.u.modeModifyReq;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.modeModifyReq.mrConfig;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.modeModifyReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.modeModifyReq.codecTypes;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Channel Mode */
    if (buffer[index++] != TM_IEI_CHANNEL_MODE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }  
    chnlMode->length = buffer[index++];

    len = index - 1;

    chnlMode->dtxu = (buffer[index] & 0x01);
    chnlMode->dtxd = ((buffer[index++] & 0x02) >> 1);
    chnlMode->indicator = buffer[index++];
    chnlMode->rateAndType = buffer[index++];

    /* Check and Get Speech coding algrithm + trasp ind */
    if (chnlMode->indicator == TM_CM_SIGNALLING)
    {
        chnlMode->codingAlg = 0x00;
        index++;
    }
    else if (chnlMode->indicator == TM_CM_DATA)
    {
        chnlMode->rate = (buffer[index] & 0x3f);
        chnlMode->service = ((buffer[index++] & 0x40) >> 6);
    }
    else if (chnlMode->indicator == TM_CM_SPEECH)
    {
        chnlMode->codingAlg = buffer[index++];
    }
    else
    {
        index++;
    }
 
    if (chnlMode->length != (index - len - 1))
    {
        return TM_DCM_CA_CHANL_ID_LEN_ERROR;
    }

    /* Intialise optional bit map field to ZERO */
    CLEAR_TM_DCM_MM_OPTIONAL_BIT_MAP(msg);

    /* Get Encryption Information if present */
    if (buffer[index] == TM_IEI_ENCRYPTION_INFORMATION)
    {
        index++;
        SET_TM_DCM_MM_ENCRYPT_INFO(msg);

        encrption->length = buffer[index++];
        if (encrption->length < 1)
        {
            return TM_DCM_EI_LENGTH_ERROR;
        }
                                                                                                                                              
        encrption->algorithmId = buffer[index++];
                                                                                                                                              
        memcpy(&encrption->key[0], &buffer[index], (encrption->length - 1));
        index += (encrption->length -1);
    }

    /* Get Main Channel Reference if present */
    if (buffer[index] == TM_IEI_MAIN_CHANNEL_REFERENCE)
    {
        index++;
        SET_TM_DCM_MM_MAIN_CHANNEL_REF(msg);
        modeModifyReq->mainChnlRefTn = buffer[index++] & 0x07;
    }

    /* Get MultiRate Configuration if present */
    if (buffer[index] == TM_IEI_MULTIRATE_CONFIGURATION)
    {
        index++;
        SET_TM_DCM_MM_MULTI_RATE_CONFIG(msg);

        mrConfig->length = buffer[index++];
        if (mrConfig->length < 0x2)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&mrConfig->content[0], &buffer[index], mrConfig->length);
        index += mrConfig->length;
    }

    /* Get MultiRate Control if present */
    if (buffer[index] == TM_IEI_MULTIRATE_CONTROL)
    {
        index++;
        SET_TM_DCM_MM_MULTI_RATE_CONTROL(msg);

        mrControl->TFO = buffer[index] & 0x01;
        mrControl->RAE = ((buffer[index] & 0x06) >> 1);
        mrControl->PRE = ((buffer[index++] & 0x08) >> 3);
    }

    /* Get Supported Codec Types if present */
    if (buffer[index] == TM_IEI_SUPPORTED_CODEC_TYPES)
    {
        index++;
        SET_TM_DCM_MM_SUPPORTED_CODEC_TYPES(msg);

        codecTypes->length = buffer[index++];

        len = index - 1;

        codecTypes->sysId = buffer[index++];
        codecTypes->codecList = buffer[index++];
                                                                                                                                              
        /* Get Codec List info. if bit 4, 5 both having 1 then the
         * same info will be coming twice. if any one of the 4, 5 bit is 1
         * then info will come once */
        if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            for (i = 0, j = 0; i < 2; i++, j++)
            {
                codecTypes->MACS[j] = buffer[index] & 0x03;
                codecTypes->TFO_VER[j] = (buffer[index++] & 0x0c) >> 2;
                codecTypes->SCS[j] = buffer[index++];
            }
        }
        else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
                ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            codecTypes->MACS[0] = buffer[index] & 0x03;
            codecTypes->TFO_VER[0] = (buffer[index++] & 0x0c) >> 2;
            codecTypes->SCS[0] = buffer[index++];
        }
                                                                                                                                              
        /* Get preffered Codec Type */
        codecTypes->prefCodecType = buffer[index++];
  
        if (codecTypes->length != (index - len -1))
        {
            return TM_DCM_CA_SUP_CODEC_LEN_ERROR;
        }
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Physical Context Confirm Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodePhyContextConf(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.phyContextConf.bsPower;
    TM_MS_POWER *msPower = &msg->u.dcmMsg.u.phyContextConf.msPower;
    TM_PHYSICAL_CONTEXT *phyContext = &msg->u.dcmMsg.u.phyContextConf.phyContext;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get BS Power msg Info */
    if (buffer[index++] != TM_IEI_BS_POWER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
                                                                                                                                              
    bsPower->powerLevel = buffer[index] & 0x0f;
                                                                                                                                              
    bsPower->FPC = (buffer[index++] & 0x10) >> 4;
 
    /* Get MS Power Info */
    if (buffer[index++] != TM_IEI_MS_POWER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    msPower->powerLevel = buffer[index] & 0x1f;
                                                                                                                                              
    msPower->FPC = (buffer[index++] & 0x20) >> 5;

    if (buffer[index++] != TM_IEI_TIMING_ADVANCE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    msg->u.dcmMsg.u.phyContextConf.timingAdv = buffer[index++];

    /* Initialise optional bit map to ZERO */
    CLEAR_TM_DCM_PCC_OPTIONAL_BIT_MAP(msg);

    /* Get Physical Context info if present */
    if (buffer[index] == TM_IEI_PHYSICAL_CONTEXT)
    {
        index++;
        SET_TM_DCM_PCC_PHYSICAL_CONTEXT(msg);

        phyContext->length = buffer[index++];

        memcpy(&phyContext->content[0], &buffer[index], phyContext->length);
        index += phyContext->length;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the MS Power Control Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeMsPowerControl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_MS_POWER *msPower = &msg->u.dcmMsg.u.mspowerControl.msPower;
    TM_MS_POWER_PARAMS *msParams = &msg->u.dcmMsg.u.mspowerControl.msParams; 
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get MS Power Info */
    if (buffer[index++] != TM_IEI_MS_POWER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    msPower->powerLevel = buffer[index] & 0x1f;
                                                                                                                                              
    msPower->FPC = (buffer[index++] & 0x20) >> 5;

    /* Initialise optional bit map to ZERO */
    CLEAR_TM_DCM_MPC_OPTIONAL_BIT_MAP(msg);

    /* Get MS Power Parameters if present */
    if (buffer[index] == TM_IEI_MS_POWER_PARAMETERS)
    {
        index++;
        SET_TM_DCM_MPC_MS_POWER_PARAMS(msg);

        msParams->length = buffer[index++]; 

        memcpy(&msParams->powerControl[0], &buffer[index], msParams->length);
        index += msParams->length;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the BS Power Control Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeBsPowerControl(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_BS_POWER *bsPower = &msg->u.dcmMsg.u.bspowerControl.bsPower;
    TM_BS_POWER_PARAMS *bsParams = &msg->u.dcmMsg.u.bspowerControl.bsParams; 
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
   
    /* Get MS Power Info */
    if (buffer[index++] != TM_IEI_BS_POWER)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
    bsPower->powerLevel = buffer[index] & 0x0f;
                                                                                                                                              
    bsPower->FPC = (buffer[index++] & 0x10) >> 4;
                                                                                                                                              
    /* Initialse optional bit map to ZERO */
    CLEAR_TM_DCM_BPC_OPTIONAL_BIT_MAP(msg);

    /* Get MS Power Parameters if present */
    if (buffer[index] == TM_IEI_BS_POWER_PARAMETERS)
    {
        index++;
        SET_TM_DCM_BPC_BS_POWER_PARAMS(msg);

        bsParams->length = buffer[index++];
                                                                                                                                              
        memcpy(&bsParams->powerControl[0], &buffer[index], bsParams->length);
        index += bsParams->length;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Preprocess Configure Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodePreprocConfig(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_PREPROC_CONFIG *preprocConfig = &msg->u.dcmMsg.u.preprocConfig;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_PRE_PROCESSING_PARAMETERS)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
   
    /* Get Pre-processor Configure details */
    preprocConfig->length = buffer[index++];

    preprocConfig->procedure = buffer[index++] & 0x01;

    memcpy(&preprocConfig->processParam[0], &buffer[index], preprocConfig->length - 1);
    index += (preprocConfig->length - 1); 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Preprocessed Measurement Result Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodePreprocMeasRes(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_PREPOC_MEAS_RES *prepocMeasRes = &msg->u.dcmMsg.u.prepocMeasRes;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
 
    if (buffer[index++] != TM_IEI_PRE_PROCESSED_MEASUREMENTS)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get Pre-process Measurements info */  
    prepocMeasRes->length = buffer[index++];

    memcpy(&prepocMeasRes->processMeas[0], &buffer[index], prepocMeasRes->length);
    index += prepocMeasRes->length;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the SACCH Info Modify Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0100              
*/
static ITS_INT
TM_DCM_decodeSacchInfoModify(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_SACCH_INFO_MOD *sacchInfoMod = &msg->u.dcmMsg.u.sacchInfoMod;
    TM_L3_INFORMATION *l3Info = &msg->u.dcmMsg.u.sacchInfoMod.l3Info;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_SYSTEM_INFO_TYPE)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    sacchInfoMod->sysInfoType = buffer[index++];

    /* Initialise optional bit map to ZERO */
    CLEAR_TM_DCM_SIM_OPTIONAL_BIT_MAP(msg);

    /* Get L3 Information if present */
    if (buffer[index] == TM_IEI_L3_INFORMATION)
    {
        index++;
        SET_TM_DCM_SIM_L3_INFO(msg);

        l3Info->lengthInd = buffer[index++];
        l3Info->lengthInd = (l3Info->lengthInd << 8) | buffer[index++];
    
        if (l3Info->lengthInd > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        /* Get L3 Information LLSDU info */
        memcpy(&l3Info->LLSDU[0], &buffer[index], l3Info->lengthInd);
        index += l3Info->lengthInd;    
    }

    /* Get Starting Time if present */
    if (buffer[index] == TM_IEI_STARTING_TIME)
    {
        index++;
        SET_TM_DCM_SIM_STARTING_TIME(msg);

        sacchInfoMod->startingTime = buffer[index++];
        sacchInfoMod->startingTime = (sacchInfoMod->startingTime << 8) | buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Remote Codec Configuration Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090              
*/
static ITS_INT
TM_DCM_decodeRemoteCodeConfRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, j, len;
    TM_CODEC_CONFIG *config = &msg->u.dcmMsg.u.remoteCodecConfRep.config;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.remoteCodecConfRep.codecTypes;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_CODEC_CONFIGURATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    } 

    config->length = buffer[index++];

    len = index - 1; 

    config->codecType = buffer[index++];

    /* Get additional two octets if codec type is AMR(FR or HR) */
    if ((config->codecType == TM_CC_FR_MULTI_RATE_IN_USE) ||
        (config->codecType == TM_CC_HR_MULTI_RATE_IN_USE))
    {
        config->ICM = buffer[index++] & 0x03;
                                                                                                                                              
        config->codecSet = buffer[index++];
    }
    if (config->length != (index - len -1))
    {
        return TM_DCM_CA_CODEC_CONFIG_LEN_ERROR;
    }

    if (buffer[index++] != TM_IEI_SUPPORTED_CODEC_TYPES)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    codecTypes->length = buffer[index++];

    len = index -1;

    codecTypes->sysId = buffer[index++];
 
    codecTypes->codecList = buffer[index++];

    /* Get Codec List info. if bit 4, 5 both having 1 then the
     * same info will be coming twice. if any one of the 4, 5 bit is 1
     * then info will come once */
    if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
        ((codecTypes->codecList & 0x10) >> 4 == 1) )
    {
        for (i = 0, j = 0; i < 2; i++, j++)
        {
            codecTypes->MACS[j] = buffer[index] & 0x03;
                                                                                                                                              
            codecTypes->TFO_VER[j] = (buffer[index++] & 0x0c) >> 2;

            codecTypes->SCS[j] = buffer[index++];
        }
    }
    else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
    {
        codecTypes->MACS[0] = buffer[index] & 0x03;
                                                                                                                                              
        codecTypes->TFO_VER[0] = (buffer[index++] & 0x0c) >> 2;

        codecTypes->SCS[0] = buffer[index++];
    }
                                                                                                                                              
    /* Set preffered Codec Type */
    codecTypes->prefCodecType = buffer[index++];
 
    if (codecTypes->length != (index - len -1))
    { 
        return TM_DCM_CA_SUP_CODEC_LEN_ERROR;
    } 
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Round Trip Delay Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeRtdRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_RTD_REP *rtdRep = &msg->u.dcmMsg.u.rtdRep;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_ROUND_TRIP_DELAY)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get Round Trip Delay */ 
    rtdRep->delay = buffer[index] & 0x01;

    rtdRep->RTD = (buffer[index++] & 0xfe) >> 1;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Pre-handover Notification Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090              
*/
static ITS_INT
TM_DCM_decodePreHandoNotif(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, len;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.preHandoNotif.mrControl;                                                               
    TM_CODEC_CONFIG *config = &msg->u.dcmMsg.u.preHandoNotif.config;

    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_MULTIRATE_CONTROL)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get Multi-Rate control Info */
    mrControl->TFO = buffer[index] & 0x01;
    mrControl->RAE = ((buffer[index] & 0x06) >> 1);
    mrControl->PRE = ((buffer[index++] & 0x08) >> 3);

    if (buffer[index++] != TM_IEI_CODEC_CONFIGURATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
                                                                                                                                              
    config->length = buffer[index++];

    len = index - 1; 

    config->codecType = buffer[index++];
                                                                                                                                              
    /* Get additional two octets if codec type is AMR(FR or HR) */
    if ((config->codecType == TM_CC_FR_MULTI_RATE_IN_USE) ||
        (config->codecType == TM_CC_HR_MULTI_RATE_IN_USE))
    {
        config->ICM = buffer[index++] & 0x03;
                                                                                                                                              
        config->codecSet = buffer[index++];
    }
                                                                                                                                              
    if (config->length != (index - len -1))
    {
        return TM_DCM_CA_CODEC_CONFIG_LEN_ERROR;
    }
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the MultiRate Codec Modification Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       This same API is used for MultiRate Codec Modification Ack message 
*       in DCM 
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeMrCodecModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.mrCodecModReq.mrConfig;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Initialise optional bit map to ZERO */
    CLEAR_TM_DCM_MCMR_OPTIONAL_BIT_MAP(msg);

    /* Get Multi-rate configuration if present */
    if (buffer[index] == TM_IEI_MULTIRATE_CONFIGURATION)
    {
        index++;
        SET_TM_DCM_MCMR_MULTI_RATE_CONFIG(msg);

        mrConfig->length = buffer[index++];
        if (mrConfig->length < 0x2)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&mrConfig->content[0], &buffer[index], mrConfig->length); 
        index += mrConfig->length;
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the MultiRate Codec Modification Performed Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeMrCodecModPer(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_MULTIRATE_CONFIG *mrConfig = &msg->u.dcmMsg.u.mrCodecModPer.mrConfig;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_MULTIRATE_CONFIGURATION)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get Multi-rate configuration */
    mrConfig->length = buffer[index++];
    if (mrConfig->length < 0x2)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&mrConfig->content[0], &buffer[index], mrConfig->length);
    index += mrConfig->length;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the TFO Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120
*/
static ITS_INT
TM_DCM_decodeTfoRep(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_DCM_TFO_REP *tfoRep = &msg->u.dcmMsg.u.tfoRep; 
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_TFO_STATUS)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    tfoRep->tfoStatus = buffer[index++] & 0x01;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the TFO Modification Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0150, ID :: D0120,
*                        ID :: D0090              
*/
static ITS_INT
TM_DCM_decodeTfoModReq(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i, j, len;
    TM_MULTIRATE_CONTROL *mrControl = &msg->u.dcmMsg.u.tfoModReq.mrControl;
    TM_SUPP_CODEC_TYPES *codecTypes = &msg->u.dcmMsg.u.tfoModReq.codecTypes;
                                                                                                                                              
    ret = TM_CCM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_MULTIRATE_CONTROL)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }
                                                                                                                                              
    /* Get Multi-Rate control Info */
    mrControl->TFO = buffer[index] & 0x01;
    mrControl->RAE = ((buffer[index] & 0x06) >> 1);
    mrControl->PRE = ((buffer[index++] & 0x08) >> 3);

    /* Intialise optional bit map to ZERO */
    CLEAR_TM_DCM_TMR_OPTIONAL_BIT_MAP(msg);
 
    /* Get Supported Codec Types if present */
    if (buffer[index] == TM_IEI_SUPPORTED_CODEC_TYPES)
    {
        index++;
        SET_TM_DCM_TMR_SUPPORTED_CODEC_TYPE(msg);

        codecTypes->length = buffer[index++];

        len = index -1;

        codecTypes->sysId = buffer[index++];
        codecTypes->codecList = buffer[index++];
                                                                                                                                              
        /* Get Codec List info. if bit 4, 5 both having 1 then the
         * same info will be coming twice. if any one of the 4, 5 bit is 1
         * then info will come once */
        if (((codecTypes->codecList & 0x08) >> 3 == 1) &&
            ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            for (i = 0, j = 0; i < 2; i++, j++)
            {
                codecTypes->MACS[j] = buffer[index] & 0x03;
                                                                                                                                              
                codecTypes->TFO_VER[j] = (buffer[index++] & 0x0c) >> 2;
                                                                                                                                              
                codecTypes->SCS[j] = buffer[index++];
            }
        }
        else if (((codecTypes->codecList & 0x08) >> 3 == 1) ||
                ((codecTypes->codecList & 0x10) >> 4 == 1) )
        {
            codecTypes->MACS[0] = buffer[index] & 0x03;
                                                                                                                                              
            codecTypes->TFO_VER[0] = (buffer[index++] & 0x0c) >> 2;
                                                                                                                                              
            codecTypes->SCS[0] = buffer[index++];
        }
                                                                                                                                              
        /* Set preffered Codec Type */
        codecTypes->prefCodecType = buffer[index++];

        if (codecTypes->length != (index - len -1))
        {
            return TM_DCM_CA_SUP_CODEC_LEN_ERROR;
        }
    } 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Location Information Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0180, ID :: D0120
*/
static ITS_INT
TM_LCS_decodeLocationInfo(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    TM_LCS_LOC_INFO *lcsLocInfo = &msg->u.lcsMsg.u.lcsLocInfo;
                                                                                                                                              
    ret = TM_decodeCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (buffer[index++] != TM_IEI_LLP_APDU)
    {
        return TM_INFO_ELEMENT_ID_ERROR;
    }

    /* Get LLP APDU info */
    lcsLocInfo->length = buffer[index++];

    memcpy(&lcsLocInfo->facIEI[0], &buffer[index], lcsLocInfo->length);
    index += lcsLocInfo->length;
 
    return ITS_SUCCESS;
}

ITS_INT (*trafficManagementEncoding[MAX_TRAFFIC_FUNS_SIZE])() = {
                            reserved,                       /* 0x00 */
                            TM_RLLM_encodeDataReq,          /* 0x01 */
                            TM_RLLM_encodeDataReq,          /* 0x02 */
                            TM_RLLM_encodeErrorInd,         /* 0x03 */
                            TM_RLLM_encodeEstaReq,          /* 0x04 */ 
                            TM_RLLM_encodeEstaReq,          /* 0x05 */
                            TM_RLLM_encodeEstaInd,          /* 0x06 */
                            TM_RLLM_encodeRelReq,           /* 0x07 */  
                            TM_RLLM_encodeEstaReq,          /* 0x08 */
                            TM_RLLM_encodeEstaReq,          /* 0x09 */
                            TM_RLLM_encodeDataReq,          /* 0x0A */
                            TM_RLLM_encodeDataReq,          /* 0x0B */
                            reserved,                       /* Reserved */
                            reserved,
                            reserved,
                            reserved,
                            reserved,
                            TM_CCM_encodeBcchInfo,           /* 0x11 */
                            TM_CCM_encodeCcchLoadInd,        /* 0x12 */
                            TM_CCM_encodeChanRqd,            /* 0x13 */
                            TM_CCM_encodeDeleteInd,          /* 0x14 */
                            TM_CCM_encodePagingCmd,          /* 0x15 */
                            TM_CCM_encodeDeleteInd,          /* 0x16 */
                            TM_CCM_encodeSmsBcReq,           /* 0x17 */
                            reserved,                        /* 0x18 */
                            TM_TRXM_encodeRfResInd,          /* 0x19 */
                            TM_TRXM_encodeSacchFill,         /* 0x1A */
                            TM_TRXM_encodeOverload,          /* 0x1B */  
                            TM_TRXM_encodeErrorReport,       /* 0x1C */
                            TM_CCM_encodeSmsBcCmd,           /* 0x1D */ 
                            TM_CCM_encodeCbchLoadInd,        /* 0x1E */
                            TM_CCM_encodeNotCmd,             /* 0x1F */
                            reserved,                        /* Reserved */
                            TM_DCM_encodeChanActiv,          /* 0x21 */
                            TM_DCM_encodeChanActivAck,       /* 0x22 */ 
                            TM_DCM_encodeChanActivNack,      /* 0x23 */
                            TM_DCM_encodeChanActivNack,      /* 0x24 */  
                            TM_DCM_encodeDeactivateSaach,    /* 0x25 */
                            TM_DCM_encodeEncrCmd,            /* 0x26 */
                            TM_DCM_encodeHandoDet,           /* 0x27 */ 
                            TM_DCM_encodeMeasRes,            /* 0x28 */
                            TM_DCM_encodeModeModifyReq,      /* 0x29 */
                            TM_DCM_encodeDeactivateSaach,    /* 0x2A */
                            TM_DCM_encodeChanActivNack,      /* 0x2B */
                            TM_DCM_encodeDeactivateSaach,    /* 0x2C */
                            TM_DCM_encodePhyContextConf,     /* 0x2D */
                            TM_DCM_encodeDeactivateSaach,    /* 0x2E */
                            TM_DCM_encodeMsPowerControl,     /* 0x2F */
                            TM_DCM_encodeBsPowerControl,     /* 0x30 */
                            TM_DCM_encodePreprocConfig,      /* 0x31 */
                            TM_DCM_encodePreprocMeasRes,     /* 0x32 */
                            TM_DCM_encodeDeactivateSaach,    /* 0x33 */
                            TM_DCM_encodeSacchInfoModify,    /* 0x34 */
                            TM_DCM_encodeHandoDet,           /* 0x35 */
                            TM_DCM_encodeHandoDet,           /* 0x36 */
                            TM_DCM_encodeRemoteCodeConfRep,  /* 0x37 */
                            TM_DCM_encodeRtdRep,             /* 0x38 */
                            TM_DCM_encodePreHandoNotif,      /* 0x39 */
                            TM_DCM_encodeMrCodecModReq,      /* 0x3A */ 
                            TM_DCM_encodeMrCodecModReq,      /* 0x3B */
                            TM_DCM_encodeChanActivNack,      /* 0x3C */ 
                            TM_DCM_encodeMrCodecModPer,      /* 0x3D */
                            TM_DCM_encodeTfoRep,             /* 0x3E */
                            TM_DCM_encodeTfoModReq,          /* 0x3F */
                            reserved,                        /* Reserved */
                            TM_LCS_encodeLocationInfo        /* 0x41 */
                         };

ITS_INT (*trafficManagementDecoding[MAX_TRAFFIC_FUNS_SIZE])() = {
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
                            reserved,
                            reserved,
                            reserved,
                            reserved,
                            TM_CCM_decodeBcchInfo,           /* 0x11 */
                            TM_CCM_decodeCcchLoadInd,        /* 0x12 */
                            TM_CCM_decodeChanRqd,            /* 0x13 */
                            TM_CCM_decodeDeleteInd,          /* 0x14 */
                            TM_CCM_decodePagingCmd,          /* 0x15 */
                            TM_CCM_decodeDeleteInd,          /* 0x16 */
                            TM_CCM_decodeSmsBcReq,           /* 0x17 */
                            reserved,                        /* 0x18 */
                            TM_TRXM_decodeRfResInd,          /* 0x19 */
                            TM_TRXM_decodeSacchFill,         /* 0x1A */
                            TM_TRXM_decodeOverload,          /* 0x1B */  
                            TM_TRXM_decodeErrorReport,       /* 0x1C */
                            TM_CCM_decodeSmsBcCmd,           /* 0x1D */ 
                            TM_CCM_decodeCbchLoadInd,        /* 0x1E */
                            TM_CCM_decodeNotCmd,             /* 0x1F */
                            reserved,                        /* Reserved */
                            TM_DCM_decodeChanActiv,          /* 0x21 */
                            TM_DCM_decodeChanActivAck,       /* 0x22 */ 
                            TM_DCM_decodeChanActivNack,      /* 0x23 */
                            TM_DCM_decodeChanActivNack,      /* 0x24 */  
                            TM_DCM_decodeDeactivateSaach,    /* 0x25 */
                            TM_DCM_decodeEncrCmd,            /* 0x26 */
                            TM_DCM_decodeHandoDet,           /* 0x27 */ 
                            TM_DCM_decodeMeasRes,            /* 0x28 */
                            TM_DCM_decodeModeModifyReq,      /* 0x29 */
                            TM_DCM_decodeDeactivateSaach,    /* 0x2A */
                            TM_DCM_decodeChanActivNack,      /* 0x2B */
                            TM_DCM_decodeDeactivateSaach,    /* 0x2C */
                            TM_DCM_decodePhyContextConf,     /* 0x2D */
                            TM_DCM_decodeDeactivateSaach,    /* 0x2E */
                            TM_DCM_decodeMsPowerControl,     /* 0x2F */
                            TM_DCM_decodeBsPowerControl,     /* 0x30 */
                            TM_DCM_decodePreprocConfig,      /* 0x31 */
                            TM_DCM_decodePreprocMeasRes,     /* 0x32 */
                            TM_DCM_decodeDeactivateSaach,    /* 0x33 */
                            TM_DCM_decodeSacchInfoModify,    /* 0x34 */
                            TM_DCM_decodeHandoDet,           /* 0x35 */
                            TM_DCM_decodeHandoDet,           /* 0x36 */
                            TM_DCM_decodeRemoteCodeConfRep,  /* 0x37 */
                            TM_DCM_decodeRtdRep,             /* 0x38 */
                            TM_DCM_decodePreHandoNotif,      /* 0x39 */
                            TM_DCM_decodeMrCodecModReq,      /* 0x3A */ 
                            TM_DCM_decodeMrCodecModReq,      /* 0x3B */
                            TM_DCM_decodeChanActivNack,      /* 0x3C */ 
                            TM_DCM_decodeMrCodecModPer,      /* 0x3D */
                            TM_DCM_decodeTfoRep,             /* 0x3E */
                            TM_DCM_decodeTfoModReq,          /* 0x3F */
                            reserved,                        /* Reserved */
                            TM_LCS_decodeLocationInfo        /* 0x41 */
                          };

/*implementation:external 
* 
* PURPOSE:  
*       Encoding the message.
* INPUT: 
*       msg - input message to be encoded 
* INPUT/OUTPUT: 
*       size - size of allocated/filled buffer
* OUTPUT: 
*       buffer - encoded value to be placed
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None      
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0010, ID :: D0120,
*                        ID :: D0070, ID :: D0080               
*/

ITS_INT
ABIS_TMM_Encode(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT *size, ITS_OCTET *buffer)
{
    ITS_INT  ret = 0;

    if ((buffer == NULL) || (msg == NULL))
    {
        return ABIS_NOMEM; 
    }

    /* All these four messages are Transparent. Others are Non-Transparent */
    if ((msg->genElemnts.msgType == TM_RLLM_DATA_REQUEST) ||
        (msg->genElemnts.msgType == TM_RLLM_DATA_INDICATION) ||
        (msg->genElemnts.msgType == TM_RLLM_UNIT_DATA_REQUEST) ||
        (msg->genElemnts.msgType == TM_RLLM_UNIT_DATA_INDICATION)) 
    {
        if (msg->genElemnts.msgDesc.trasparent != TM_TRANSPARENT_MSG)
        {
            return TM_TRANSPARENT_BIT_ERROR;    
        } 
    } 
    else
    {
        if (msg->genElemnts.msgDesc.trasparent != TM_NON_TRANSPARENT_MSG)
        {
            return TM_NON_TRANSPARENT_BIT_ERROR;    
        } 
    } 

    
    /* At the moment, it is assumed that the user allocates enough buffer
     * memory to hold the encoded buffer 
     */
#if 0
    /* make sure buffer size is sufficient */ 
    if (sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG) > *size)
    {
       return ABIS_INVALID_LEN;
    }
#endif

    ret = (trafficManagementEncoding[msg->genElemnts.msgType])(msg, size, buffer);

    if (ret != ITS_SUCCESS)
    {
        return ret; 
    }

    return ret;
}

/*implementation:external 
* 
* PURPOSE:  
*       Decoding the Traffic Management message.
* INPUT: 
*       buffer - encoded value to be parsed
*       length - size of buffer 
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS, if no error occured
*       error, if error occured 
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0020, ID :: D0120,
*                        ID :: D0070, ID :: D0080               
*/

ITS_INT
ABIS_TMM_Decode(ABIS_TRAFFIC_MANAGEMENT_MSG *msg, ITS_UINT length, ITS_OCTET *buffer)
{
    ITS_INT  ret = 0;

    if ((buffer == NULL) || (msg == NULL))
    {
        return ABIS_NOMEM;
    } 

#if 0
    /* buffer length shouldn't cross max limit */
    if (sizeof(ABIS_TRAFFIC_MANAGEMENT_MSG) <= length)
    {
        ret = ABIS_INVALID_LEN;
    }
#endif

    ret = (trafficManagementDecoding[buffer[1]])(msg, buffer);
                                                                                                                                              
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ret;   
}

