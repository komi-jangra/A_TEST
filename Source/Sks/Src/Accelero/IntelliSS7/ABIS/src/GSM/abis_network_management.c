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
 *  ID: $Id: abis_network_management.c,v 1.1.1.1 2007-10-08 11:11:11 bsccs2 Exp $
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
 *  Revision 1.1.2.9  2006/12/29 05:31:04  sjaddu
 *  Done changes to Support TRX HELLO.
 *
 *  Revision 1.1.2.8  2006/08/11 09:42:02  sjaddu
 *  Modified during Integration Testing.
 *
 *  Revision 1.1.2.7  2006/06/27 10:04:26  gdevanand
 *  Fix for BUG ID: 3918 and 3919
 *
 *  Revision 1.1.2.6  2006/05/15 11:03:21  gdevanand
 *  Added code for FILLER_TRX as object class as per IMR requirement (badri).
 *
 *  Revision 1.1.2.5  2006/04/07 09:30:56  yranade
 *  RF Max Power Reduction IE Added (sgavalkar)
 *
 *  Revision 1.1.2.4  2006/03/28 09:17:10  yranade
 *  TRX Hello message added. (sgavalkar)
 *
 *  Revision 1.1.2.3  2005/09/27 11:59:46  mkrishna
 *  Added changes to OS related problems
 *
 *  Revision 1.1.2.2  2005/09/23 06:41:32  mkrishna
 *  Bug fixes done
 *
 *  Revision 1.1.2.1  2005/08/16 11:38:34  mkrishna
 *  Added Initial version after unit testing.
 *
 *
 ****************************************************************************/
                                                                                                                                              
#include <abis_network_management.h>

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the common elements in network management message.
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
*       This API is used by all the messages in Network Management
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0200, ID :: D0120
*/
static ITS_INT
encodeFomCommonElements(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                        ITS_OCTET *buffer)
{
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts; 
    OBJECT_INSTANCE *objInst = &msg->u.formMsg.formGenElemnts.objInst;

    buffer[(*size)++] = 0x80;

#if 0
    buffer[(*size)++] = formGenElemnts->placeInd;
#endif

//Added for Integration Testing with Real TRX
    buffer[(*size)++] = 0x80;

    buffer[(*size)++] = formGenElemnts->seqNum;

    /* We fill this octet once we get complete length */
    buffer[(*size)++] = 0x00;  
     
    buffer[(*size)++] = formGenElemnts->msgType;
   
    buffer[(*size)++] = formGenElemnts->objClass;

    if (formGenElemnts->objClass == NM_OC_SITE_MANAGER)
    {
        buffer[(*size)++] = 0xff;

        buffer[(*size)++] = 0xff;

        buffer[(*size)++] = 0xff; 
    }
    else if (formGenElemnts->objClass == NM_OC_BTS)
    {
#if 0
        buffer[(*size)++] = objInst->btsNum;

        buffer[(*size)++] = 0xff;

        buffer[(*size)++] = 0xff; 
#endif
//Added for Integration Testing with Real TRX
        buffer[(*size)++] = 0x00;

        buffer[(*size)++] = 0x00;

        buffer[(*size)++] = 0x00; 
      
    }
    else if ((formGenElemnts->objClass == NM_OC_RADIO_CARRIER) || 
             (formGenElemnts->objClass == NM_OC_BASEBAND_TRANSCEIVER))
    {
        buffer[(*size)++] = objInst->btsNum;

        buffer[(*size)++] = objInst->baseBandNum;

        buffer[(*size)++] = 0xff;
    }
    else if (formGenElemnts->objClass == NM_OC_CHANNEL)
    {
#if 0
        buffer[(*size)++] = objInst->btsNum;

        buffer[(*size)++] = objInst->baseBandNum;

        buffer[(*size)++] = objInst->timeSlotNum;
#endif
//Added for Integration Testing with Real TRX
        buffer[(*size)++] = 0x00;

        buffer[(*size)++] = 0x00;

        buffer[(*size)++] = objInst->timeSlotNum;

    }
	/*
	 * This is not in spec 3GPP TS 12.21 v 8.0.0 release 1999
	 * This object class is added as per proprietary IMR requirement. 
	 */
	else if (formGenElemnts->objClass == NM_OC_FILLER)
	{
#if 0
		buffer[(*size)++] = 0xff;

        buffer[(*size)++] = 0xff;

        buffer[(*size)++] = 0xff;
#endif
//Added for Integration Testing with Real TRX
		buffer[(*size)++] = 0x00;

        buffer[(*size)++] = 0x00;

        buffer[(*size)++] = 0x00;
	}

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Load Data Initiate Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_encodeLoadDataInit(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr;
    NM_SWDM_LOAD_DATA_INIT *loadInit = &msg->u.formMsg.u.swdmMsg.u.loadInit;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set SW Description */
    buffer[index++] = NM_SW_DESCRIPTION;

    buffer[index++] = NM_FILE_ID;
 
    if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    } 

    buffer[index++] = swDescr->fileIdLen >> 8;
    buffer[index++] = swDescr->fileIdLen & 0xff;

    memcpy(&buffer[index], &swDescr->fileId[0], swDescr->fileIdLen); 
    index += swDescr->fileIdLen; 

    buffer[index++] = NM_FILE_VERSION;

    if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    buffer[index++] = swDescr->fileVerLen >> 8;
    buffer[index++] = swDescr->fileVerLen & 0xff;

    memcpy(&buffer[index], &swDescr->fileVer[0], swDescr->fileVerLen);
    index += swDescr->fileVerLen;

    /* Set Window Size */
    buffer[index++] = NM_WINDOW_SIZE;

    if (loadInit->winSize == 0x00)
    {
        return NM_FOM_WS_INVALID_SIZE;
    } 
    buffer[index++] = loadInit->winSize;
  
    /* Set Nack Cause if msg is Load Data Intiate Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_INTIATE_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = loadInit->nackCuase; 
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Load Data Segment Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_encodeLoadDataSeg(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                          ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SWDM_LOAD_DATA_SEG *loadSeg = &msg->u.formMsg.u.swdmMsg.u.loadSeg;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    buffer[index++] = NM_FILE_DATA;

    if (loadSeg->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = loadSeg->length >> 8;
    buffer[index++] = loadSeg->length & 0xff;

    memcpy(&buffer[index], &loadSeg->data[0], loadSeg->length);
    index += loadSeg->length;

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Load Data Abort Message.
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
*       This same API is used for SW Activated Report Message.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_encodeLoadDataAbort(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                            ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Load Data End Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_encodeLoadDataEnd(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                          ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.loadEnd.swDescr;
                                                    
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set SW Description */
    buffer[index++] = NM_SW_DESCRIPTION;
                                                                                                                                              
    buffer[index++] = NM_FILE_ID;
                                                                                                                                              
    if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = swDescr->fileIdLen >> 8;
    buffer[index++] = swDescr->fileIdLen & 0xff;

    memcpy(&buffer[index], &swDescr->fileId[0], swDescr->fileIdLen);
    index += swDescr->fileIdLen;
                                                                                                                                              
    buffer[index++] = NM_FILE_VERSION;
                                                                                                                                              
    if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = swDescr->fileVerLen >> 8;
    buffer[index++] = swDescr->fileVerLen & 0xff;

    memcpy(&buffer[index], &swDescr->fileVer[0], swDescr->fileVerLen);
    index += swDescr->fileVerLen;
                                                                                                                                              
    /* Set Nack Cause if msg is Load Data End Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_END_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.swdmMsg.u.loadEnd.nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the SW Activate Request Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_encodeSwActiveReq(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    HW_CONFIG *hwConfig = &msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig; 
    SW_CONFIG *swConfig = &msg->u.formMsg.u.swdmMsg.u.actReq.swConfig;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set HW Configuration */
    buffer[index++] = NM_HW_CONFIGURATION;

    if (hwConfig->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = hwConfig->length >> 8;
    buffer[index++] = hwConfig->length & 0xff;

    for (i = 0; i < hwConfig->length; i++)
    {
        buffer[index++] = NM_HW_DESCRIPTION;

        /* Equipment Id */ 
        if (hwConfig->hwDesc[i].equipIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwConfig->hwDesc[i].equipIdLen >> 8;
        buffer[index++] = hwConfig->hwDesc[i].equipIdLen & 0xff;

        memcpy(&buffer[index], &hwConfig->hwDesc[i].equipId[0], 
               hwConfig->hwDesc[i].equipIdLen);
        index += hwConfig->hwDesc[i].equipIdLen;

        /* Equipment Type */
        if (hwConfig->hwDesc[i].equipTypeLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwConfig->hwDesc[i].equipTypeLen >> 8;
        buffer[index++] = hwConfig->hwDesc[i].equipTypeLen & 0xff;

        memcpy(&buffer[index], &hwConfig->hwDesc[i].equipType[0],
               hwConfig->hwDesc[i].equipTypeLen);
        index += hwConfig->hwDesc[i].equipTypeLen;

        /* Equipment Version */
        if (hwConfig->hwDesc[i].equipVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwConfig->hwDesc[i].equipVerLen >> 8;
        buffer[index++] = hwConfig->hwDesc[i].equipVerLen & 0xff;

        memcpy(&buffer[index], &hwConfig->hwDesc[i].equipVer[0],
               hwConfig->hwDesc[i].equipVerLen);
        index += hwConfig->hwDesc[i].equipVerLen;

        /* Location */
        if (hwConfig->hwDesc[i].locLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwConfig->hwDesc[i].locLen >> 8;
        buffer[index++] = hwConfig->hwDesc[i].locLen & 0xff;

        memcpy(&buffer[index], &hwConfig->hwDesc[i].location[0],
               hwConfig->hwDesc[i].locLen);
        index += hwConfig->hwDesc[i].locLen;
   
        /* Man Dep Info */
        if (hwConfig->hwDesc[i].infoLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwConfig->hwDesc[i].infoLen >> 8;
        buffer[index++] = hwConfig->hwDesc[i].infoLen & 0xff;

        memcpy(&buffer[index], &hwConfig->hwDesc[i].info[0],
               hwConfig->hwDesc[i].infoLen);
        index += hwConfig->hwDesc[i].infoLen;
    }

    /* Set SW Configuration */
    buffer[index++] = NM_SW_CONFIGURATION;

    if (swConfig->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = swConfig->length >> 8;
    buffer[index++] = swConfig->length & 0xff;

    for (i = 0; i < swConfig->length; i++)
    {
        buffer[index++] = NM_SW_DESCRIPTION;
        
        /* Set File Id */
        buffer[index++] = NM_FILE_ID;

        if (swConfig->swDesc[i].fileIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = swConfig->swDesc[i].fileIdLen >> 8;
        buffer[index++] = swConfig->swDesc[i].fileIdLen & 0xff;

        memcpy(&buffer[index], &swConfig->swDesc[i].fileId[0], 
                swConfig->swDesc[i].fileIdLen);
        index += swConfig->swDesc[i].fileIdLen; 

        /* Set File Version */
        buffer[index++] = NM_FILE_VERSION;

        if (swConfig->swDesc[i].fileVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = swConfig->swDesc[i].fileVerLen >> 8;
        buffer[index++] = swConfig->swDesc[i].fileVerLen & 0xff;

        memcpy(&buffer[index], &swConfig->swDesc[i].fileVer[0],
                swConfig->swDesc[i].fileVerLen);
        index += swConfig->swDesc[i].fileVerLen;       
    }

    /* Set Nack Cause if msg is Activeate Request Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_SW_ACTIVATE_REQUEST_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.swdmMsg.u.actReq.nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Activate SW Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_encodeActivateSw(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                         ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.actSw.swDescr;
    NM_SWDM_ACTIVE_SW *actSw = &msg->u.formMsg.u.swdmMsg.u.actSw;                                                                                                                                          
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set SW Description if present */
    if (IS_PRESENT_NM_SWDM_AS_SW_DESCRIPTION(msg))
    {
        buffer[index++] = NM_SW_DESCRIPTION;
                                                                                                                                              
        buffer[index++] = NM_FILE_ID;
                                                                                                                                              
        if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = swDescr->fileIdLen >> 8;
        buffer[index++] = swDescr->fileIdLen & 0xff;

        memcpy(&buffer[index], &swDescr->fileId[0], swDescr->fileIdLen);
        index += swDescr->fileIdLen;
                                                                                                                                              
        buffer[index++] = NM_FILE_VERSION;
                                                                                                                                              
        if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = swDescr->fileVerLen >> 8;
        buffer[index++] = swDescr->fileVerLen & 0xff;

        memcpy(&buffer[index], &swDescr->fileVer[0], swDescr->fileVerLen);
        index += swDescr->fileVerLen;
    }

    /* Set Nack Cause if msg is Active SW Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_ACTIVATE_SW_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.swdmMsg.u.actSw.nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Establish TEI Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0220, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_ABIM_encodeEstablishTei(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_ABIM_ESTABLISH_TEI *estaTei = &msg->u.formMsg.u.abisMsg.u.estaTei;
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set TEI */
    buffer[index++] = NM_TEI;

    if (estaTei->teiVal >= NM_TEI_NOT_USED)
    {
        return NM_FOM_TEI_INVALID_ERROR;
    } 
    buffer[index++] = estaTei->teiVal;

    /* Set Abis Channel */
    buffer[index++] = NM_ABIS_CHANNEL;

    buffer[index++] = abisChanl->btsPortNum;

    if (abisChanl->timeSlotNum > NM_AC_END_TIME_SLOT_NUM)
    {
        return NM_FOM_AC_INVALID_TIME_SLOT_ERROR;
    }
    buffer[index++] = abisChanl->timeSlotNum;    

    buffer[index++] = abisChanl->subSlotNum;

    /* Set Nack Cause if msg is Establish TEI Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_ESTABLISH_TEI_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = estaTei->nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Connect Terrestrial Signalling Message.
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
*       The same API is used for Disconnect Terrestrial Signalling msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0220, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_ABIM_encodeConnTerrSign(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Abis Channel */
    buffer[index++] = NM_ABIS_CHANNEL;
                                                                                                                                              
    buffer[index++] = abisChanl->btsPortNum;
                                                                                                                                              
    if (abisChanl->timeSlotNum > NM_AC_END_TIME_SLOT_NUM)
    {
        return NM_FOM_AC_INVALID_TIME_SLOT_ERROR;
    }
    buffer[index++] = abisChanl->timeSlotNum;
                                                                                                                                              
    buffer[index++] = abisChanl->subSlotNum;
                                                                                                                                              
    /* Set Nack Cause if msg is Connect Terrestrial Signalling Nack or 
     * Disconnect Terrestrial Signalling Nack */
    if ((formGenElemnts->msgType == NM_CONNECT_TERRESTRIAL_SIGNALLING_NACK) ||
        (formGenElemnts->msgType == NM_DISCONNECT_TERRESTRIAL_SIGNALLING_NACK))
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.abisMsg.u.connTerr.nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Connect Terrestrial Traffic Message.
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
*       The same API is used for Disconnect Terrestrial Traffic msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0220, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_ABIM_encodeConnTerrTraffic(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                              ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
    NM_ABIM_CONN_TERR_TRAFFIC *connTraf = &msg->u.formMsg.u.abisMsg.u.connTraf;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
    
    /* Set Abis Channel */
    buffer[index++] = NM_ABIS_CHANNEL;
                                                                                                                                              
    buffer[index++] = abisChanl->btsPortNum;
                                                                                                                                              
    if (abisChanl->timeSlotNum > NM_AC_END_TIME_SLOT_NUM)
    {
        return NM_FOM_AC_INVALID_TIME_SLOT_ERROR;
    }
    buffer[index++] = abisChanl->timeSlotNum;
                                                                                                                                              
    buffer[index++] = abisChanl->subSlotNum;
                                                                                                                                          
    /* Set Radio Sub Channel if present*/
    if (IS_PRESENT_NM_AM_CTT_RADIO_SUB_CHANNEL(msg))
    {
        buffer[index++] = NM_RADIO_SUB_CHANNEL;
        buffer[index++] = connTraf->radioSubChanl; 
    }

    /* Set Nack Cause if msg is Connect Terrestrial Traffic Nack or 
     * Disconnect Terrestrial Traffic Nack */
    if ((formGenElemnts->msgType == NM_CONNECT_TERRESTRIAL_TRAFFIC_NACK) ||
        (formGenElemnts->msgType == NM_DISCONNECT_TERRESTRIAL_TRAFFIC_NACK))
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = connTraf->nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Connect Multi-drop Link Message.
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
*       This same API is used for Disconnect multi-drop Link msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0230, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TRM_encodeConnMultiDropLink(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                               ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    MD_BSC_LINK *bscLink = &msg->u.formMsg.u.transMsg.u.conLink.bscLink;
    MD_NEXT_BTS_LINK *btsLink = &msg->u.formMsg.u.transMsg.u.conLink.btsLink;
    NM_TRM_CON_MULTI_DROP_LINK *conLink = &msg->u.formMsg.u.transMsg.u.conLink;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Multi-drop BSC Link */
    buffer[index++] = NM_MULTI_DROP_BSC_LINK;

    buffer[index++] = bscLink->btsPortNum; 

    if (bscLink->timeSlotNum > NM_MBL_END_TIME_SLOT_2MBPS_LINK)
    {
        return NM_FOM_MBL_TIME_SLOT_ERROR;
    }
    buffer[index++] = bscLink->timeSlotNum;

    /* Multi-drop next BTS Link */
    buffer[index++] = NM_MULTI_DROP_NEXT_BTS_LINK;

    buffer[index++] = btsLink->btsPortNum;
 
    if (btsLink->timeSlotNum > NM_MBL_END_TIME_SLOT_2MBPS_LINK)
    {
        return NM_FOM_MBL_TIME_SLOT_ERROR;
    } 
    buffer[index++] = btsLink->timeSlotNum;

    /* Set Nack Cause if msg is Connect Multi-drop link Nack or 
     * Disconnect Multi-drop link Nack */
    if ((formGenElemnts->msgType == NM_CONNECT_MULTI_DROP_LINK_NACK) || 
        (formGenElemnts->msgType == NM_DISCONNECT_MULTI_DROP_LINK_NACK))
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = conLink->nackCuase;
    } 

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Set BTS Attributes Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0240, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_AIM_encodeSetBtsAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                        ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    NM_AIM_SET_BTS_ATTR *btsAttr = &msg->u.formMsg.u.airMsg.u.btsAttr;
    INTER_LEVEL_BOUND *interLevel = &msg->u.formMsg.u.airMsg.u.btsAttr.interLevel;
    CON_FAIL_CRITERION *conFail = &msg->u.formMsg.u.airMsg.u.btsAttr.conFail;
    T200 *t200 = &msg->u.formMsg.u.airMsg.u.btsAttr.t200;
    OVERLOAD_PERIOD *overldPeriod = &msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Interference Level Boundaries if present */
    if (IS_PRESENT_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES(msg))
    {
        buffer[index++] = NM_INTERFERENCE_LEVEL_BOUNDARIES;
        buffer[index++] = interLevel->interfBound0; 
        buffer[index++] = interLevel->interfBound1;
        buffer[index++] = interLevel->interfBound2;
        buffer[index++] = interLevel->interfBound3;
        buffer[index++] = interLevel->interfBound4;
        buffer[index++] = interLevel->interfBound5;   
    } 

    /* Set Intave parameter if present */
    if (IS_PRESENT_NM_AIM_SBA_INTAVE_PARAMETER(msg))
    {
        buffer[index++] = NM_INTAVE_PARAMETER;

        if (btsAttr->intaveParam > NM_IP_END_INTAVE_PARAM)
        {
            return NM_FOM_IP_INTAVE_PARAM_ERROR;
        }
        buffer[index++] = btsAttr->intaveParam;
    }

    /* Set Connection Failure Criterion if present*/
    if (IS_PRESENT_NM_AIM_SBA_CONN_FAILURE_CRITERION(msg))
    {
        buffer[index++] = NM_CONNECTION_FAILURE_CRITERION;

        if ((conFail->length < 0x01) || (conFail->length > MAX_CONTENT_LENGTH))
        {
            return NM_FOM_CFC_LENGTH_ERROR;
        }
        buffer[index++] = conFail->length >> 8;
        buffer[index++] = conFail->length & 0xff;

        buffer[index++] = conFail->failCrit;

        if (conFail->failCrit == NM_CFC_UPLINK_SACCH_ERROR_RATE)
        {
            buffer[index++] = conFail->critVal[0];
        } 
        else
        {
            memcpy(&buffer[index], &conFail->critVal[0], conFail->length - 1);
            index += (conFail->length - 1);
        } 
    }

    /* Set T200 if present */
    if (IS_PRESENT_NM_AIM_SBA_T200(msg))
    {
        buffer[index++] = NM_T200;
        buffer[index++] = t200->sdcch; 
        buffer[index++] = t200->facchFull; 
        buffer[index++] = t200->facchHalf; 
        buffer[index++] = t200->sacchSap10; 
        buffer[index++] = t200->sacchSdcch; 
        buffer[index++] = t200->sdcchSap13; 
        buffer[index++] = t200->sacchSap13; 
    }

    /* Set Max Timing Advance if present */
    if (IS_PRESENT_NM_AIM_SBA_MAX_TIMING_ADVANCE(msg))
    {
        buffer[index++] = NM_MAX_TIMING_ADVANCE;
    
        if (btsAttr->maxTimeAdv > NM_MTA_END_MAX_TIMING_ADVANCE)
        {
            return NM_FOM_MTA_TIMING_ADV_ERROR;
        }
        buffer[index++] = btsAttr->maxTimeAdv; 
    }

    /* Set Overload Period if present */
    if (IS_PRESENT_NM_AIM_SBA_OVERLOAD_PERIOD(msg))
    {
        buffer[index++] = NM_OVERLOAD_PERIOD;

        if (overldPeriod->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = overldPeriod->length >> 8;
        buffer[index++] = overldPeriod->length & 0xff;

        memcpy(&buffer[index], &overldPeriod->period[0], overldPeriod->length);
        index += overldPeriod->length;
    }  

    /* Set CCCH Load Threshold if present */
    if (IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_THRESHOLD(msg))
    {
        buffer[index++] = NM_CCCH_LOAD_THRESOLD;

        if (btsAttr->threshold > NM_CLT_END_LOAD_THRESHOLD)
        {
            return NM_FOM_CLT_THRESHOLD_ERROR;
        }
        buffer[index++] = btsAttr->threshold;
    }  

    /* Set CCCH Load Indication Period if present */
    if (IS_PRESENT_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD(msg))
    {
        buffer[index++] = NM_CCCH_LOAD_INDICATION_PERIOD;
        buffer[index++] = btsAttr->initPeriod;
    }

    /* Set RACH Busy Threshold if present */
    if (IS_PRESENT_NM_AIM_SBA_RACH_BUSY_THRESHOLD(msg))
    {
        buffer[index++] = NM_RACH_BUSY_THRESOLD;
        buffer[index++] = btsAttr->busyThreshold;
    }

    /* Set RACH Load Averaging Slots if present */
    if (IS_PRESENT_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS(msg))
    {
        buffer[index++] = NM_RACH_LOAD_AVERAGING_SLOTS;
        
        buffer[index++] = btsAttr->avgSlots >> 8;
        buffer[index++] = btsAttr->avgSlots & 0xff;
    }

    /* Set BTS Air Timer if present */
    if (IS_PRESENT_NM_AIM_SBA_BTS_AIR_TIMER(msg))
    {
        buffer[index++] = NM_BTS_AIR_TIMER;
        buffer[index++] = btsAttr->airT3105.tch;
        buffer[index++] = btsAttr->airT3105.sdcch;
    }

    /* Set NY1 if present */
    if (IS_PRESENT_NM_AIM_SBA_NY1(msg))
    {
        buffer[index++] = NM_NY1;
        buffer[index++] = btsAttr->ny1.tch;
        buffer[index++] = btsAttr->ny1.sdcch;
    }

    /* Set BCCH ARFCN if present */
    if (IS_PRESENT_NM_AIM_SBA_BCCH_ARFCN(msg))
    {
        buffer[index++] = NM_BCCH_ARFCN;
       
        if (btsAttr->arfcn > NM_BA_BCCH_END_ARFCN)
        {
            return NM_FOM_BA_ARFCN_ERROR;
        }
        buffer[index++] = btsAttr->arfcn >> 8;
        buffer[index++] = btsAttr->arfcn & 0xff;
    }
 
    /* Set BSIC if present */
    if (IS_PRESENT_NM_AIM_SBA_BSIC(msg))
    {
        buffer[index++] = NM_BSIC;

        if (btsAttr->bsic > NM_BSIC_END)
        {
            return NM_FOM_BSIC_ERROR;
        }
        buffer[index++] = btsAttr->bsic;
    }

    /* Set RF Max Power Reduction  */
    if (IS_PRESENT_NM_AIM_SBA_RF_MAX_POWER_REDUCTION(msg))
    {
        buffer[index++] = NM_RF_MAX_POWER_REDUCTION;
        buffer[index++] = btsAttr->powerRedn;
    }

    /* Set Starting Time if present */
    if (IS_PRESENT_NM_AIM_SBA_STARTING_TIME(msg))
    {
        buffer[index++] = NM_STARTING_TIME;
        
        buffer[index++] = btsAttr->startCurFrameNo >> 8;
        buffer[index++] = btsAttr->startCurFrameNo & 0xff;
    }

    /* Set Nack Cause if msg is Set BTS Attributes Nack */
    if (formGenElemnts->msgType == NM_SET_BTS_ATTRIBUTES_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = btsAttr->nackCuase;
    }

    if (IS_PRESENT_NM_AIM_SBA_PAGING_AG_PARAMS(msg))
    {
        buffer[index++] = NM_PAGING_AG_PARAMS;
        buffer[index++] = btsAttr->pageAgParams.bsPaMfrms;
        buffer[index++] = btsAttr->pageAgParams.bsCcchChans;
        buffer[index++] = btsAttr->pageAgParams.bsAgRes;
        buffer[index++] = btsAttr->pageAgParams.pageAlg;
    }

    if (IS_PRESENT_NM_AIM_SBA_SYST_INFO_LIST(msg))
    {
        buffer[index++] = NM_SYST_INFO_LIST;
        buffer[index++] = btsAttr->systInfoList.len;
        memcpy(&buffer[index], &btsAttr->systInfoList.six[0],
                                     btsAttr->systInfoList.len);
        index += btsAttr->systInfoList.len;
    }

    if (IS_PRESENT_NM_AIM_SBA_FN_OFFSET(msg))
    {
        buffer[index++] = NM_FN_OFFSET;
        buffer[index++] = btsAttr->fnOffset;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Set Radio Carrier Attributes Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0240, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_AIM_encodeSetRadioCarrierAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                                 ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    NM_AIM_SET_RADIO_ATTR *radioAttr = &msg->u.formMsg.u.airMsg.u.radioAttr;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    ARFCN_LIST  *arfcnList = &msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set RF Max Power Reduction if present */
    if (IS_PRESENT_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION(msg))
    {
        buffer[index++] = NM_RF_MAX_POWER_REDUCTION;
        buffer[index++] = radioAttr->powerRedu;
    }
     
    /* Set ARFCN List if present */
    if (IS_PRESENT_NM_AIM_SRCA_ARFCN_LIST(msg))
    {
        buffer[index++] = NM_ARFCN_LIST;
        
        if (arfcnList->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = arfcnList->length >> 8;
        buffer[index++] = arfcnList->length & 0xff;

        for (i = 0; i < arfcnList->length; i++)
        {
            if (arfcnList->arfcn[i] > NM_AL_END_ARFCN_LIST)
            {
                return NM_FOM_AIM_ARFCN_ERROR;
            }
            buffer[index++] = arfcnList->arfcn[i] >> 8;
            buffer[index++] = arfcnList->arfcn[i] & 0xff;
        }
    }

    /* Set Nack Cause if msg is Set Radio Carrier Attribute Nack */
    if (formGenElemnts->msgType == NM_SET_RADIO_CARRIER_ATTRIBUTES_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = radioAttr->nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Set Channel Attributes Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0240, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_AIM_encodeSetChanlAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                          ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    NM_AIM_SET_CHANNEL_ATTR *chanlAttr = &msg->u.formMsg.u.airMsg.u.chanlAttr; 
    ARFCN_LIST *arfcnList = &msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Channel Combination if present */
    if (IS_PRESENT_NM_AIM_SCA_CHANNEL_COMBINATION(msg))
    {
        buffer[index++] = NM_CHANNEL_COMBINATION;
        buffer[index++] = chanlAttr->chanlComb;
    }

    /* Set HSN if present */
    if (IS_PRESENT_NM_AIM_SCA_HSN(msg))
    {
        buffer[index++] = NM_HSN;
 
        if (chanlAttr->hsn > NM_HSN_END)
        {
            return NM_FOM_HSN_ERROR;
        }
        buffer[index++] = chanlAttr->hsn;
    } 

    /* Set MAIO if present */
    if (IS_PRESENT_NM_AIM_SCA_MAIO(msg))
    {
        buffer[index++] = NM_MAIO;
        buffer[index++] = chanlAttr->maioList.len;
        memcpy(&buffer[index], &chanlAttr->maioList.maio[0],
                                  chanlAttr->maioList.len);
        index += chanlAttr->maioList.len;

/*
        if (chanlAttr->maio > NM_MAIO_END)
        {
            return NM_FOM_MAIO_ERROR;
        }
        buffer[index++] = chanlAttr->maio;
*/
    }

    /* Set ARFCN List if present */
    if (IS_PRESENT_NM_AIM_SCA_ARFCN_LIST(msg))
    {
        buffer[index++] = NM_ARFCN_LIST;

        if (arfcnList->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = arfcnList->length >> 8;
        buffer[index++] = arfcnList->length & 0xff;

        for (i = 0; i < arfcnList->length; i++)
        {
            buffer[index++] = arfcnList->arfcn[i] >> 8;
            buffer[index++] = arfcnList->arfcn[i] & 0xff;
        }     
    }

    /* Set Starting Time if present */
    if (IS_PRESENT_NM_AIM_SCA_STARTING_TIME(msg))
    {
        buffer[index++] = NM_STARTING_TIME;

        buffer[index++] = chanlAttr->startCurFrameNo >> 8;
        buffer[index++] = chanlAttr->startCurFrameNo & 0xff;
    }

    /* Set TSC if present */
    if (IS_PRESENT_NM_AIM_SCA_TSC(msg))
    {
        buffer[index++] = NM_TSC;

        if (chanlAttr->tscSeqCode > NM_TSC_END_VALUE)
        {
            return NM_FOM_TSC_ERROR;
        }  
        buffer[index++] = chanlAttr->tscSeqCode;
    }

    /* Set RF Max Power reduction */
    if (IS_PRESENT_NM_AIM_SCA_RF_MAX_POWER_REDUCTION(msg))
    {
        buffer[index++] = NM_RF_MAX_POWER_REDUCTION;
        buffer[index++] = chanlAttr->powerRedn;
    }

    /* Set Nack Cause if msg is Set Channel Attributes Nack */
    if (formGenElemnts->msgType == NM_SET_CHANNEL_ATTRIBUTES_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = chanlAttr->nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Perform Test Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0250, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TM_encodePerformTest(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                        ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    NM_TM_PERFORM_TEST *perfTest = &msg->u.formMsg.u.testMsg.u.perfTest;
    PHYSICAL_CONFIG *phyContext = &msg->u.formMsg.u.testMsg.u.perfTest.phyContext;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Test No */
    buffer[index++] = NM_TEST_NO;
                                                                                                                                              
    buffer[index++] = msg->u.formMsg.u.testMsg.testNum;

    /* Set Autonomously Report */
    buffer[index++] = NM_AUTONOMOUSLY_REPORT;

    buffer[index++] = perfTest->autoRep;

    /* Set Test Duration if present */
    if (IS_PRESENT_NM_TM_PT_TEST_DURATION(msg))
    {
        buffer[index++] = NM_TEST_DURATION;

        if (perfTest->testDura < NM_TD_START_DURATION)
        {
            return NM_FOM_TM_DURATION_ERROR;
        } 
        buffer[index++] = perfTest->testDura >> 8;
        buffer[index++] = perfTest->testDura & 0xff;
    }

    /* Set Physical Configuration if present */
    if (IS_PRESENT_NM_TM_PT_PHYSICAL_CONFIGURATION(msg))
    {
        buffer[index++] = NM_PHYSICAL_CONFIG;
        
        if (phyContext->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = phyContext->length >> 8;
        buffer[index++] = phyContext->length & 0xff;

        memcpy(&buffer[index], &phyContext->testConfig[0], phyContext->length);
        index += phyContext->length; 
    }

    /* Set Nack Cause if msg is Perform Test Nack */
    if (formGenElemnts->msgType == NM_PERFORM_TEST_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = perfTest->nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Test Report Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0250, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TM_encodeTestReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_TM_TEST_REP *testRep = &msg->u.formMsg.u.testMsg.u.testRep;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Test No */
    buffer[index++] = NM_TEST_NO;

    buffer[index++] = msg->u.formMsg.u.testMsg.testNum;
 
    /* Set Test Report Info */
    buffer[index++] = NM_TEST_REPORT_INFO;
 
    if (testRep->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = testRep->length >> 8;
    buffer[index++] = testRep->length & 0xff;

    memcpy(&buffer[index], &testRep->resultInfo[0], testRep->length);
    index += testRep->length;

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Send Test Report Message.
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
*       This same API is used for Stop Test Message.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0250, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TM_encodeSendTestReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Test No */
    buffer[index++] = NM_TEST_NO;

    buffer[index++] = msg->u.formMsg.u.testMsg.testNum;
 
    /* Set Nack Cause if msg is Send Test Report Nack or Stop Test Nack*/
    if ((msg->u.formMsg.formGenElemnts.msgType == NM_SEND_TEST_REPORT_NACK) || 
        (msg->u.formMsg.formGenElemnts.msgType == NM_STOP_TEST_NACK))
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.testMsg.u.sendRep.nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the State Changed Event Report Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_encodeStateChangdEventRep(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                                ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    NM_SM_STATE_CHNG_EVENT_REP *changeEv = &msg->u.formMsg.u.stateMsg.u.changeEv; 
    AVAILABILITY_STATUS *availStat = &msg->u.formMsg.u.stateMsg.u.changeEv.availStat;
    SITE_INPUTS *siteInputs = &msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Operational State if present */ 
    if (IS_PRESENT_NM_SM_SCER_OPERATIONAL_STATE(msg))
    {
        buffer[index++] = NM_OPERATIONAL_STATE;
        
        if (changeEv->operanStat == NM_OS_NULL)
        {
            return NM_FOM_OS_INVALID_STATE_ERROR;
        }
        buffer[index++] = changeEv->operanStat;
    } 

    /* Set Availability State if present */ 
    if (IS_PRESENT_NM_SM_SCER_AVAILABILITY_STATE(msg))
    {
        buffer[index++] = NM_AVAILABLITY_STATUS;
        
        if (availStat->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = availStat->length >> 8;
        buffer[index++] = availStat->length & 0xff;

        memcpy(&buffer[index], &availStat->status[0], availStat->length);
        index += availStat->length;
    }

    /* Set Manufacturer Dependent State if present */ 
    if (IS_PRESENT_NM_SM_SCER_MAN_DEP_STATE(msg))
    {
        buffer[index++] = NM_MANUFACTURE_DEPENDENT_STATE;
        buffer[index++] = changeEv->mfdDepen;
    }

    /* Set Site Inputs if present */ 
    if (IS_PRESENT_NM_SM_SCER_SITE_INPUTS(msg))
    {
        buffer[index++] = NM_SITE_INPUTS;
        
        if (siteInputs->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = siteInputs->length >> 8;
        buffer[index++] = siteInputs->length & 0xff;

        for (i = 0; i < siteInputs->length; i++)
        {
            if (siteInputs->attr[i].input > 127)
            {
                return NM_FOM_SM_INPUT_ERROR;
            } 
            buffer[index] = siteInputs->attr[i].input & 0x7F;

            if (siteInputs->attr[i].state > 1)
            {
                return NM_FOM_SM_STATE_ERROR;
            }
            buffer[index++] |= ((siteInputs->attr[i].state & 0x01) << 7); 
        }
    } 

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Failure Event Report Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_encodeFailureEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                               ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SM_FAIL_EVENT_REP *failEv = &msg->u.formMsg.u.stateMsg.u.failEv;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.stateMsg.u.failEv.probCause; 
    ADDITIONAL_TEXT *addText = &msg->u.formMsg.u.stateMsg.u.failEv.addText;
    ADDITIONAL_INFO *addInfo = &msg->u.formMsg.u.stateMsg.u.failEv.addInfo;
    HW_DESCRIPTION *hwDesc = &msg->u.formMsg.u.stateMsg.u.failEv.hwDescr; 
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.stateMsg.u.failEv.swDescr;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Event Type */ 
    buffer[index++] = NM_EVENT_TYPE;
    buffer[index++] = failEv->evtType; 
     
    /* Set Perceived Severity */
    buffer[index++] = NM_PERCEIVED_SEVERITY; 
    buffer[index++] = failEv->percvdSever;

    /* Set Probable Cause */
    buffer[index++] = NM_PROBABLE_CAUSE;
    buffer[index++] = probCause->type;
    
    buffer[index++] = probCause->value >> 8;
    buffer[index++] = probCause->value & 0xff;

    /* Set Specific Problems if present */
    if (IS_PRESENT_NM_SM_FER_SPECIFIC_PROBLEMS(msg))
    {
        buffer[index++] = NM_SPECIFIC_PROBLEMS;
        buffer[index++] = failEv->specProbs;
    }
 
    /* Set HW Description if present */
    if (IS_PRESENT_NM_SM_FER_HW_DESCRIPTION(msg))
    {
        buffer[index++] = NM_HW_DESCRIPTION;

        /* Equipment Id */
        if (hwDesc->equipIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->equipIdLen >> 8;
        buffer[index++] = hwDesc->equipIdLen & 0xff;

        memcpy(&buffer[index], &hwDesc->equipId[0], hwDesc->equipIdLen);
        index += hwDesc->equipIdLen;
                                                                                                                                              
        /* Equipment Type */
        if (hwDesc->equipTypeLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->equipTypeLen >> 8;
        buffer[index++] = hwDesc->equipTypeLen & 0xff;

        memcpy(&buffer[index], &hwDesc->equipType[0], hwDesc->equipTypeLen);
        index += hwDesc->equipTypeLen;
                                                                                                                                              
        /* Equipment Version */
        if (hwDesc->equipVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->equipVerLen >> 8;
        buffer[index++] = hwDesc->equipVerLen & 0xff;

        memcpy(&buffer[index], &hwDesc->equipVer[0], hwDesc->equipVerLen);
        index += hwDesc->equipVerLen;
                                                                                                                                              
        /* Location */
        if (hwDesc->locLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->locLen >> 8;
        buffer[index++] = hwDesc->locLen & 0xff;

        memcpy(&buffer[index], &hwDesc->location[0], hwDesc->locLen);
        index += hwDesc->locLen;
                                                                                                                                              
        /* Man Dep Info */
        if (hwDesc->infoLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->infoLen >> 8;
        buffer[index++] = hwDesc->infoLen & 0xff;

        memcpy(&buffer[index], &hwDesc->info[0], hwDesc->infoLen);
        index += hwDesc->infoLen;
    }
 
    /* Set SW Description if present */
    if (IS_PRESENT_NM_SM_FER_SW_DESCRIPTION(msg))
    {
        buffer[index++] = NM_SW_DESCRIPTION;

        buffer[index++] = NM_FILE_ID;
                                                                                                                                              
        if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = swDescr->fileIdLen >> 8;
        buffer[index++] = swDescr->fileIdLen & 0xff;

        memcpy(&buffer[index], &swDescr->fileId[0], swDescr->fileIdLen);
        index += swDescr->fileIdLen;
                                                                                                                                              
        buffer[index++] = NM_FILE_VERSION;
                                                                                                                                              
        if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = swDescr->fileVerLen >> 8;
        buffer[index++] = swDescr->fileVerLen & 0xff;

        memcpy(&buffer[index], &swDescr->fileVer[0], swDescr->fileVerLen);
        index += swDescr->fileVerLen;
    }
 
    /* Set Additional Text if present */
    if (IS_PRESENT_NM_SM_FER_ADDITIONAL_TEXT(msg))
    {
        buffer[index++] = NM_ADDITIONAL_TEXT;

        if (addText->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = addText->length >> 8;
        buffer[index++] = addText->length & 0xff;

        memcpy(&buffer[index], &addText->value, addText->length);
        index += addText->length;
    }
 
    /* Set Additional Info if present */
    if (IS_PRESENT_NM_SM_FER_ADDITIONAL_INFO(msg))
    {
        buffer[index++] = NM_ADDITIONAL_INFO;

        if (addInfo->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = addInfo->length >> 8;
        buffer[index++] = addInfo->length & 0xff;

        memcpy(&buffer[index], &addInfo->value, addInfo->length);
        index += addInfo->length;
    }
 
    /* Set Outstanding Alarm Sequence if present */
    if (IS_PRESENT_NM_SM_FER_OUTSTANDING_ALARM_SEQ(msg))
    {
        buffer[index++] = NM_OUTSTANDING_ALARM_SEQUENCE;
        buffer[index++] = failEv->alarmSeq;
    }
 
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Stop Sending Event Reports Message.
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
*       This same API is used for Restart Sending Event Reports msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_encodeStopSendEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                                ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    NM_SM_STOP_SEND_EVENT_REP *stopEv = &msg->u.formMsg.u.stateMsg.u.stopEv; 
    AVAILABILITY_STATUS *availStat = &msg->u.formMsg.u.stateMsg.u.stopEv.availStat;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.stateMsg.u.stopEv.probCause; 
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Operational State if present */
    if (IS_PRESENT_NM_SM_SSER_OPERATIONAL_STATE(msg))
    {
        buffer[index++] = NM_OPERATIONAL_STATE;
                                                                                                                                              
        if (stopEv->operanStat == NM_OS_NULL)
        {
            return NM_FOM_OS_INVALID_STATE_ERROR;
        }
        buffer[index++] = stopEv->operanStat;
    }
                                                                                                                                              
    /* Set Availability State if present */
    if (IS_PRESENT_NM_SM_SSER_AVAILABILTY_STATE(msg))
    {
        buffer[index++] = NM_AVAILABLITY_STATUS;
                                                                                                                                              
        if (availStat->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = availStat->length >> 8;
        buffer[index++] = availStat->length & 0xff;

        memcpy(&buffer[index], &availStat->status[0], availStat->length);
        index += availStat->length;
    }
                                                                                                                                              
    /* Set Manufacturer Dependent State if present */
    if (IS_PRESENT_NM_SM_SSER_MFD_DEP_STATE(msg))
    {
        buffer[index++] = NM_MANUFACTURE_DEPENDENT_STATE;
        buffer[index++] = stopEv->mfdDepen;
    }

    /* Set Probable Cause if present */
    if (IS_PRESENT_NM_SM_SSER_PROBABLE_CAUSE(msg))
    {
        buffer[index++] = NM_PROBABLE_CAUSE;
        buffer[index++] = probCause->type;
                                                                                                                                              
        buffer[index++] = probCause->value >> 8;
        buffer[index++] = probCause->value & 0xff;
    }                                                                                       
    /* Set Specific Problems if present */
    if (IS_PRESENT_NM_SM_SSER_SPECIFIC_PROBLEMS(msg))
    {
        buffer[index++] = NM_SPECIFIC_PROBLEMS;
        buffer[index++] = stopEv->specProbs;
    }

    /* Set Nack Cause if msg is Stop Sending Event Reports Nack or
     * Restart Sending Event Reports Nack */
    if ((formGenElemnts->msgType == NM_STOP_SENDING_EVENT_REPORTS_NACK) ||
        (formGenElemnts->msgType == NM_RESTART_SENDING_EVENT_REPORTS_NACK))
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = stopEv->nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Change Administrative State Message.
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
*       This same API is used for Change Administrative State Request msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_encodeChangeAdminState(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                             ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SM_CHNG_ADMIN_STATE *state = &msg->u.formMsg.u.stateMsg.u.state;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    buffer[index++] = NM_ADMINISTRATIVE_STATE;
 
    buffer[index++] = state->adminStat;

    /* Set Nack Cause if msg is Change Administrative State Nack or 
     * Change Administrative State Request Nack */
    if ((formGenElemnts->msgType == NM_CHANGE_ADMINISTRATIVE_STATE_NACK) ||
        (formGenElemnts->msgType == NM_CHANGE_ADMINISTRATIVE_STATE_REQUEST_NACK))
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = state->nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Encoding the TRX Hello Message.
* INPUT:
*       msg - input message to be encoded
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       buffer - encoded value to be placed
*       size - size of filled buffer * RETURNS:
*       ITS_SUCCESS, if no error occured
*       error, if error occured
* COMMENTS:
*       This same API is used for TRX Hello Message.
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
*/
static ITS_INT
NM_SM_encodeTrxHello(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                             ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SM_TRX_HELLO *trxHello = &msg->u.formMsg.u.stateMsg.u.trxHello;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    buffer[index++] = trxHello->onmProtoVer.versionX;
    buffer[index++] = trxHello->onmProtoVer.versionY;

    buffer[index++] = trxHello->hwCapab.freqHop;
    buffer[index++] = trxHello->hwCapab.diversity;
    buffer[index++] = trxHello->hwCapab.powClassSup;
    buffer[index++] = trxHello->hwCapab.freqBand;
    buffer[index++] = trxHello->hwCapab.lsclAvail;
    buffer[index++] = trxHello->hwCapab.memoryCapb;

    //Set the flag for Optional IE here
    if (IS_PRESENT_NM_SM_TRX_HELLO_SW_DESC(msg))
    {
        buffer[index++] = NM_SW_DESCRIPTION;
        buffer[index++] = trxHello->swDesc.fileIdLen >> 8;
        buffer[index++] = trxHello->swDesc.fileIdLen & 0xff;
        memcpy(&buffer[index], &trxHello->swDesc.fileId[0],
                                         trxHello->swDesc.fileIdLen);
        index += trxHello->swDesc.fileIdLen;

        buffer[index++] = trxHello->swDesc.fileVerLen >> 8;
        buffer[index++] = trxHello->swDesc.fileVerLen  & 0xff;
        memcpy(&buffer[index], &trxHello->swDesc.fileVer,
                                         trxHello->swDesc.fileVerLen);
        index += trxHello->swDesc.fileVerLen;
    }

    if (IS_PRESENT_NM_SM_TRX_HELLO_HW_DESC(msg))
    {
        buffer[index++] = trxHello->hwDesc.equipIdLen >> 8;
        buffer[index++] = trxHello->hwDesc.equipIdLen & 0xff;
        memcpy(&buffer[index], &trxHello->hwDesc.equipId[0],
                                         trxHello->hwDesc.equipIdLen);
        index += trxHello->hwDesc.equipIdLen;

        buffer[index++] = trxHello->hwDesc.equipTypeLen >> 8;
        buffer[index++] = trxHello->hwDesc.equipTypeLen & 0xff;
        memcpy(&buffer[index], &trxHello->hwDesc.equipType[0],
                                       trxHello->hwDesc.equipTypeLen);
        index += trxHello->hwDesc.equipTypeLen;

        buffer[index++] = trxHello->hwDesc.equipVerLen >> 8;
        buffer[index++] = trxHello->hwDesc.equipVerLen & 0xff;
        memcpy(&buffer[index], &trxHello->hwDesc.equipVer[0],
                                       trxHello->hwDesc.equipVerLen );
        index += trxHello->hwDesc.equipVerLen;

        buffer[index++] = trxHello->hwDesc.locLen >> 8;
        buffer[index++] = trxHello->hwDesc.locLen & 0xff;
        memcpy(&buffer[index], &trxHello->hwDesc.location[0],
                                         trxHello->hwDesc.locLen);
        index += trxHello->hwDesc.locLen;

        buffer[index++] = trxHello->hwDesc.infoLen >> 8;
        buffer[index++] = trxHello->hwDesc.infoLen & 0xff;
        memcpy(&buffer[index], &trxHello->hwDesc.info[0],
                                         trxHello->hwDesc.infoLen);
        index += trxHello->hwDesc.infoLen;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Changeover Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_encodeChangeover(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                       ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    SOURCE *src = &msg->u.formMsg.u.equipMsg.u.changeOver.src;
    DESTINATION *dest = &msg->u.formMsg.u.equipMsg.u.changeOver.dest;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Source */
    buffer[index++] = NM_SOURCE;

    if (src->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = src->length >> 8;
    buffer[index++] = src->length & 0xff;

    memcpy(&buffer[index], &src->value[0], src->length);
    index += src->length;

    /* Set Destination */
    buffer[index++] = NM_DESTINATION;

    if (dest->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = dest->length >> 8;
    buffer[index++] = dest->length & 0xff;

    memcpy(&buffer[index], &dest->value[0], dest->length);
    index += dest->length;

    /* Set Nack Cause if msg is Changeover Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_CHANGEOVER_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.equipMsg.u.changeOver.nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Opstart Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_encodeOpstart(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                    ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Nack Cause if msg is Opstart Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_OPSTART_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.equipMsg.u.opStart.nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Set Site Outputs Message.
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
*       This same API is used for Change HW Configuration message.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_encodeSetSiteOutputs(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_EM_SET_SITE_OUTPUTS *siteOutput = &msg->u.formMsg.u.equipMsg.u.siteOutput;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Site Outputs */
    buffer[index++] = NM_SITE_OUTPUTS;

    if (siteOutput->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = siteOutput->length >> 8;
    buffer[index++] = siteOutput->length & 0xff;

    memcpy(&buffer[index], &siteOutput->output[0], siteOutput->length);
    index += siteOutput->length;
     
    /* Set Nack Cause if msg is Set Site Outputs Nack or 
     * Change HW Configuration Nack */
    if ((formGenElemnts->msgType == NM_SET_SITE_OUTPUTS_NACK) || 
        (formGenElemnts->msgType == NM_CHANGE_HW_CONFIGURATION_NACK))
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = siteOutput->nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Get Attributes Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0290, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_encodeGetAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                    ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_MS_GET_ATTR *getAttr = &msg->u.formMsg.u.miscMsg.u.getAttr;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
   
    buffer[index++] = NM_LIST_OF_REQUIRED_ATTRIBUTES;

    if (getAttr->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = getAttr->length >> 8;
    buffer[index++] = getAttr->length & 0xff;

    memcpy(&buffer[index], &getAttr->atrrId[0], getAttr->length);
    index += getAttr->length;

    /* Set Nack Cause if msg is Get Attributes Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_GET_ATTRIBUTES_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = getAttr->nackCuase;
    }

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Get Attributes Response Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0290, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_encodeGetAttrResp(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                        ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_MS_GET_ATTR_RESP *getAttrResp = &msg->u.formMsg.u.miscMsg.u.getAttrResp;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Get Attribute Response Info */
    buffer[index++] = NM_GET_ATTRIBUTE_RESPONSE_INFO;

    if ((getAttrResp->length < 1) || (getAttrResp->length > MAX_CONTENT_LENGTH))
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = getAttrResp->length >> 8;
    buffer[index++] = getAttrResp->length & 0xff;

    if ((getAttrResp->notRepCount > MAX_CONTENT_LENGTH) || 
        (getAttrResp->notRepCount > getAttrResp->length))
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = getAttrResp->notRepCount; 

    memcpy(&buffer[index], &getAttrResp->notRep[0], getAttrResp->notRepCount); 
    index += getAttrResp->notRepCount;

    memcpy(&buffer[index], &getAttrResp->reported[0], 
            (getAttrResp->length - getAttrResp->notRepCount - 1));
    index += (getAttrResp->length - getAttrResp->notRepCount - 1);
 
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Set Alarm Threshold Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0290, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_encodeSetAlarmThreshold(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                              ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    POWER_OUTPUT_THRESHOLD *powerOutput = 
                   &msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.miscMsg.u.alarmThresh.probCause;
    VSWR_THRESHOLD *vswr = &msg->u.formMsg.u.miscMsg.u.alarmThresh.vswr;
    MFD_THRESHOLDS *mfdThresh = &msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh;

    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Set Probable Cause */
    buffer[index++] = NM_PROBABLE_CAUSE;

    buffer[index++] = probCause->type;

    buffer[index++] = probCause->value >> 8;
    buffer[index++] = probCause->value & 0xff;
 
    /* Set Power Output Thresholds if present */
    if (IS_PRESENT_NM_MM_SAT_POWER_OUTPUT_THRESHOLD(msg))
    {
        buffer[index++] = NM_POWER_OUTPUT_THRESHOLDS;

        if (powerOutput->fault > NM_POT_END_OPT)
        {
            return NM_FOM_POT_FAULT_ERROR;
        }    
        buffer[index++] = powerOutput->fault;

        if (powerOutput->reduced > NM_POT_END_ROPT)
        {
            return NM_FOM_POT_REDUCED_ERROR;
        }
        buffer[index++] = powerOutput->reduced;

        if (powerOutput->excessive > NM_POT_END_EOPT)
        {
            return NM_FOM_POT_EXCESSIVE_ERROR;
        }
        buffer[index++] = powerOutput->excessive;
    }

    /* Set VSWR Thresholds if present */
    if (IS_PRESENT_NM_MM_SAT_VSWR_THRESHOLDS(msg))
    {
        buffer[index++] = NM_VSWR_THRESOLDS;
        if (vswr->faulty > NM_VSWR_END_FAULTY_ANTENNA)
        {
            return NM_FOM_VT_FAULTY_ERROR;
        }
        buffer[index++] = vswr->faulty;

        if (vswr->notAdjusted > NM_VSWR_END_ANTENNA_NOT_ADJUSTED)
        {
            return NM_FOM_VT_NOT_ADJUSTED_ERROR;
        }
        buffer[index++] = vswr->notAdjusted;    
    }
 
    /* Manufacturer Dependent Thresholds */
    if (IS_PRESENT_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS(msg))
    {
        buffer[index++] = NM_MANUFACTURE_DEPENDENT_THRESHOLDS;

        if (mfdThresh->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = mfdThresh->length >> 8;
        buffer[index++] = mfdThresh->length & 0xff;

        memcpy(&buffer[index], &mfdThresh->mfdDependnt[0], mfdThresh->length);
        index += mfdThresh->length;
    }        

    /* Set Nack Cause if msg is Set Alarm Threshold Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_SET_ALARM_THRESHOLD_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.miscMsg.u.alarmThresh.nackCuase;
    }
 
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;
 
    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Reinitialize Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_encodeReinitialise(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                         ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    HW_DESCRIPTION *hwDesc = &msg->u.formMsg.u.equipMsg.u.reInit.hwDesc; 
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if (IS_PRESENT_NM_EM_REIN_HW_DESCRIPTION(msg))
    {
        /* Set HW Description */
        buffer[index++] = NM_HW_DESCRIPTION;

        /* Equipment Id */ 
        if (hwDesc->equipIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->equipIdLen >> 8;
        buffer[index++] = hwDesc->equipIdLen & 0xff;

        memcpy(&buffer[index], &hwDesc->equipId[0], hwDesc->equipIdLen);
        index += hwDesc->equipIdLen;

        /* Equipment Type */
        if (hwDesc->equipTypeLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->equipTypeLen >> 8;
        buffer[index++] = hwDesc->equipTypeLen & 0xff;

        memcpy(&buffer[index], &hwDesc->equipType[0], hwDesc->equipTypeLen);
        index += hwDesc->equipTypeLen;

        /* Equipment Version */
        if (hwDesc->equipVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->equipVerLen >> 8;
        buffer[index++] = hwDesc->equipVerLen & 0xff;

        memcpy(&buffer[index], &hwDesc->equipVer[0], hwDesc->equipVerLen);
        index += hwDesc->equipVerLen;

        /* Location */
        if (hwDesc->locLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->locLen >> 8;
        buffer[index++] = hwDesc->locLen & 0xff;

        memcpy(&buffer[index], &hwDesc->location[0], hwDesc->locLen);
        index += hwDesc->locLen;
   
        /* Man Dep Info */
        if (hwDesc->infoLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        buffer[index++] = hwDesc->infoLen >> 8;
        buffer[index++] = hwDesc->infoLen & 0xff;

        memcpy(&buffer[index], &hwDesc->info[0], hwDesc->infoLen);
        index += hwDesc->infoLen;
    }

    /* Set Nack Cause if msg is Reinitialize Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_REINITIALIZE_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.equipMsg.u.reInit.nackCuase;
    }
 
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Measurement Result Request Message.
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
*       This same API is used for Start Measurement, Stop Measurement msg's
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0280, ID :: D0120,
*                        ID :: D0100 
*/
static ITS_INT
NM_MM_encodeMeasResultReq(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                          ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Measurement Identifier */
    buffer[index++] = NM_MEASUREMENT_TYPE;

    buffer[index++] = msg->u.formMsg.u.measMsg.measId;  

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Measurement Result Response Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0280, ID :: D0120,
*                        ID :: D0100 
*/
static ITS_INT
NM_MM_encodeMeasResultResp(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                           ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_MM__MEAS_RES_RESP *measResp = &msg->u.formMsg.u.measMsg.u.measResp;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Measurement Identifier */
    buffer[index++] = NM_MEASUREMENT_TYPE;
                                                                                                                                              
    buffer[index++] = msg->u.formMsg.u.measMsg.measId;

    /* Set Measurement Result */
    buffer[index++] = NM_MEASUREMENT_RESULT;
  
    if (measResp->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    buffer[index++] = measResp->length >> 8;
    buffer[index++] = measResp->length & 0xff;

    memcpy(&buffer[index], &measResp->measResult[0], measResp->length);
    index += measResp->length;

    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Encoding the Report Outstanding Alarms Message.
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
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100 
*/
static ITS_INT
NM_SM_encodeReportOutstandAlarms(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                                 ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = encodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Set Nack Cause if msg is Report Outstanding Alarms Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == 
        NM_REPORT_OUTSTANDING_ALARMS_NACK)
    {
        buffer[index++] = NM_NACK_CAUSES;
        buffer[index++] = msg->u.formMsg.u.stateMsg.u.repAlarm.nackCuase;
    }
                                                                                                                                              
    /* Finally fill up the length of complete buffer */
    buffer[3] = index - 4;

    /* Assign index to size */
    *size = index;
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the common elements in Network Management msg's.
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
*       This API is used by all the messages in Network Management msg's
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0200, ID :: D0120,
*                        ID :: D0100 
*/
static ITS_INT
decodeFomCommonElements(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *index, 
                        ITS_OCTET *buffer)
{
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts; 
    OBJECT_INSTANCE *objInst = &msg->u.formMsg.formGenElemnts.objInst;

    if (buffer[*index]  != NM_FORMATTED_OM_MSG)
    {
        return NM_INVALID_MSG_TYPE;
    }
    formGenElemnts->msgDesc = buffer[(*index)++];

    formGenElemnts->placeInd = buffer[(*index)++];

    formGenElemnts->seqNum = buffer[(*index)++];

    /* We fill this octet once we get complete length */
    formGenElemnts->lenInd = buffer[(*index)++];  
     
    formGenElemnts->msgType = buffer[(*index)++];
   
    formGenElemnts->objClass = buffer[(*index)++];

    objInst->btsNum = buffer[(*index)++];

    objInst->baseBandNum = buffer[(*index)++];

    objInst->timeSlotNum = buffer[(*index)++]; 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Load Data Initiate Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_decodeLoadDataInit(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.loadInit.swDescr;
    NM_SWDM_LOAD_DATA_INIT *loadInit = &msg->u.formMsg.u.swdmMsg.u.loadInit;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }


    /* Get SW Description */
    if (buffer[index++] != NM_SW_DESCRIPTION)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    if (buffer[index++] != NM_FILE_ID)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
    
    swDescr->fileIdLen = buffer[index++];
    swDescr->fileIdLen = (swDescr->fileIdLen << 8) | buffer[index++];

    if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&swDescr->fileId[0], &buffer[index], swDescr->fileIdLen); 
    index += swDescr->fileIdLen; 

    if (buffer[index++] != NM_FILE_VERSION)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    } 

    swDescr->fileVerLen = buffer[index++];
    swDescr->fileVerLen = (swDescr->fileVerLen << 8) | buffer[index++];

    if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
 
    memcpy(&swDescr->fileVer[0], &buffer[index], swDescr->fileVerLen);
    index += swDescr->fileVerLen;

    /* Get Window Size */
    if (buffer[index++] != NM_WINDOW_SIZE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    loadInit->winSize = buffer[index++];
    if (loadInit->winSize == 0x00)
    {
        return NM_FOM_WS_INVALID_SIZE;
    } 
  
    /* Get Nack Cause if msg is Load Data Intiate Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_INTIATE_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        loadInit->nackCuase = buffer[index++]; 
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Load Data Segment Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_decodeLoadDataSeg(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SWDM_LOAD_DATA_SEG *loadSeg = &msg->u.formMsg.u.swdmMsg.u.loadSeg;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get File Data */
    if (buffer[index++] != NM_FILE_DATA)
    {
        return NM_INVLID_ATTRIBUTE_ID; 
    }

    loadSeg->length = buffer[index++];
    loadSeg->length = (loadSeg->length << 8) | buffer[index++];

    if (loadSeg->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&loadSeg->data[0], &buffer[index], loadSeg->length);
    index += loadSeg->length;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Load Data Abort Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This same API is used for SW Activated Report Message.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_decodeLoadDataAbort(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Load Data End Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_decodeLoadDataEnd(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.loadEnd.swDescr;
                                                    
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get SW Description */
    if (buffer[index++] != NM_SW_DESCRIPTION)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    if (buffer[index++] != NM_FILE_ID)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    swDescr->fileIdLen = buffer[index++];
    swDescr->fileIdLen = (swDescr->fileIdLen << 8) | buffer[index++];

    if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
                                                                                                                                              
    memcpy(&swDescr->fileId[0], &buffer[index], swDescr->fileIdLen);
    index += swDescr->fileIdLen;
   
    if (buffer[index++] != NM_FILE_VERSION)
    {
        return NM_INVLID_ATTRIBUTE_ID; 
    }

    swDescr->fileVerLen = buffer[index++];
    swDescr->fileVerLen = (swDescr->fileVerLen << 8) | buffer[index++];

    if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
                                                                                                                                              
    memcpy(&swDescr->fileVer[0], &buffer[index], swDescr->fileVerLen);
    index += swDescr->fileVerLen;

    /* Get Nack Cause if msg is Load Data End Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_LOAD_DATA_END_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.swdmMsg.u.loadEnd.nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the SW Activate Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_decodeSwActiveReq(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    HW_CONFIG *hwConfig = &msg->u.formMsg.u.swdmMsg.u.actReq.hwConfig; 
    SW_CONFIG *swConfig = &msg->u.formMsg.u.swdmMsg.u.actReq.swConfig;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get HW Configuration */
    if (buffer[index++] != NM_HW_CONFIGURATION)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    } 

    hwConfig->length = buffer[index++];
    hwConfig->length = (hwConfig->length << 8) | buffer[index++];

    if (hwConfig->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    /* User has to free the allocated memory. This allocation is done
     * by keeping in mind of that static allocation is consuming more
     * memory for every message in network management.
     */ 
    hwConfig->hwDesc = (HW_DESCRIPTION *)malloc(hwConfig->length * sizeof(HW_DESCRIPTION)); 

    for (i = 0; i < hwConfig->length; i++)
    {
        if (buffer[index++] != NM_HW_DESCRIPTION)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }

        /* Equipment Id */ 
        hwConfig->hwDesc[i].equipIdLen = buffer[index++];
        hwConfig->hwDesc[i].equipIdLen = 
            (hwConfig->hwDesc[i].equipIdLen << 8) | buffer[index++];

        if (hwConfig->hwDesc[i].equipIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
      
        memcpy(&hwConfig->hwDesc[i].equipId[0], &buffer[index], 
               hwConfig->hwDesc[i].equipIdLen);
        index += hwConfig->hwDesc[i].equipIdLen;

        /* Equipment Type */
        hwConfig->hwDesc[i].equipTypeLen = buffer[index++];
        hwConfig->hwDesc[i].equipTypeLen = 
           (hwConfig->hwDesc[i].equipTypeLen << 8) | buffer[index++];

        if (hwConfig->hwDesc[i].equipTypeLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&hwConfig->hwDesc[i].equipType[0], &buffer[index],
               hwConfig->hwDesc[i].equipTypeLen);
        index += hwConfig->hwDesc[i].equipTypeLen;

        /* Equipment Version */
        hwConfig->hwDesc[i].equipVerLen = buffer[index++];
        hwConfig->hwDesc[i].equipVerLen = 
              (hwConfig->hwDesc[i].equipVerLen << 8) | buffer[index++];

        if (hwConfig->hwDesc[i].equipVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwConfig->hwDesc[i].equipVer[0], &buffer[index],
               hwConfig->hwDesc[i].equipVerLen);
        index += hwConfig->hwDesc[i].equipVerLen;

        /* Location */
        hwConfig->hwDesc[i].locLen = buffer[index++];
        hwConfig->hwDesc[i].locLen = (hwConfig->hwDesc[i].locLen << 8) | 
                                      buffer[index++];

        if (hwConfig->hwDesc[i].locLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwConfig->hwDesc[i].location[0], &buffer[index],
               hwConfig->hwDesc[i].locLen);
        index += hwConfig->hwDesc[i].locLen;
   
        /* Man Dep Info */
        hwConfig->hwDesc[i].infoLen = buffer[index++];
        hwConfig->hwDesc[i].infoLen = (hwConfig->hwDesc[i].infoLen << 8) |
                                       buffer[index++];

        if (hwConfig->hwDesc[i].infoLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwConfig->hwDesc[i].info[0], &buffer[index],
               hwConfig->hwDesc[i].infoLen);
        index += hwConfig->hwDesc[i].infoLen;
    }

    /* Get SW Configuration */
    if (buffer[index++] != NM_SW_CONFIGURATION)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    swConfig->length = buffer[index++];
    swConfig->length = (swConfig->length << 8) | buffer[index++];

    if (swConfig->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
    
    /* User has to free the allocated memory. This allocation is done
     * by keeping in mind of that static allocation is consuming more
     * memory for every message in network management.
     */ 
    swConfig->swDesc = (SW_DESCRIPTION *)malloc(swConfig->length * sizeof(SW_DESCRIPTION)); 

    for (i = 0; i < swConfig->length; i++)
    {
        if (buffer[index++] != NM_SW_DESCRIPTION)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }

        /* Get File Id */
        if (buffer[index++] != NM_FILE_ID)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }

        swConfig->swDesc[i].fileIdLen = buffer[index++];
        swConfig->swDesc[i].fileIdLen = (swConfig->swDesc[i].fileIdLen << 8) | buffer[index++];

        if (swConfig->swDesc[i].fileIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&swConfig->swDesc[i].fileId[0], &buffer[index],
                swConfig->swDesc[i].fileIdLen);
        index += swConfig->swDesc[i].fileIdLen; 

        /* Get File Version */
        if (buffer[index++] != NM_FILE_VERSION)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }

        swConfig->swDesc[i].fileVerLen = buffer[index++];
        swConfig->swDesc[i].fileVerLen = (swConfig->swDesc[i].fileVerLen << 8) | buffer[index++];

        if (swConfig->swDesc[i].fileVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&swConfig->swDesc[i].fileVer[0], &buffer[index],
                swConfig->swDesc[i].fileVerLen);
        index += swConfig->swDesc[i].fileVerLen;       
    }

    /* Get Nack Cause if msg is Activeate Request Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_SW_ACTIVATE_REQUEST_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.swdmMsg.u.actReq.nackCuase = buffer[index++];
    }
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Activate SW Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0210, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SWDM_decodeActivateSw(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{

    ITS_UINT index = 0, ret = 0;
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.swdmMsg.u.actSw.swDescr;
    NM_SWDM_ACTIVE_SW *actSw = &msg->u.formMsg.u.swdmMsg.u.actSw; 

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Initialise optional bit map to ZERO */
    CLEAR_NM_SWDM_AS_OPTIONAL_BIT_MAP(msg);

    /* Get SW Description if present */
    if (buffer[index] == NM_SW_DESCRIPTION)
    {
        index++;
        SET_NM_SWDM_AS_SW_DESCRIPTION(msg);

        if (buffer[index++] != NM_FILE_ID)
        {
            return NM_INVLID_ATTRIBUTE_ID; 
        }                                                                                                                   

        swDescr->fileIdLen = buffer[index++];
        swDescr->fileIdLen = (swDescr->fileIdLen << 8) | buffer[index++];

        if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&swDescr->fileId[0], &buffer[index], swDescr->fileIdLen);
        index += swDescr->fileIdLen;
                                                                                                                                              
        if (buffer[index++] != NM_FILE_VERSION)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }

        swDescr->fileVerLen = buffer[index++];
        swDescr->fileVerLen = (swDescr->fileVerLen << 8) | buffer[index++];

        if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&swDescr->fileVer[0], &buffer[index], swDescr->fileVerLen);
        index += swDescr->fileVerLen;
    }

    /* Get Nack Cause if msg is Active SW Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_ACTIVATE_SW_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;  
        }
        msg->u.formMsg.u.swdmMsg.u.actSw.nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Establish TEI Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0220, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_ABIM_decodeEstablishTei(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_ABIM_ESTABLISH_TEI *estaTei = &msg->u.formMsg.u.abisMsg.u.estaTei;
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get TEI */
    if (buffer[index++] != NM_TEI)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    estaTei->teiVal = buffer[index++];

    /* Get Abis Channel */
    if (buffer[index++] != NM_ABIS_CHANNEL)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    abisChanl->btsPortNum = buffer[index++];

    abisChanl->timeSlotNum = buffer[index++];    
    if (abisChanl->timeSlotNum > NM_AC_END_TIME_SLOT_NUM)
    {
        return NM_FOM_AC_INVALID_TIME_SLOT_ERROR;
    }

    abisChanl->subSlotNum = buffer[index++];

    /* Get Nack Cause if msg is Establish TEI Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_ESTABLISH_TEI_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        } 
        estaTei->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Connect Terrestrial Signalling Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       The same API is used for Disconnect Terrestrial Signalling msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0220, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_ABIM_decodeConnTerrSign(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Abis Channel */
    if (buffer[index++] != NM_ABIS_CHANNEL)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    abisChanl->btsPortNum = buffer[index++];
                                                                                                                                              
    abisChanl->timeSlotNum = buffer[index++];
    if (abisChanl->timeSlotNum > NM_AC_END_TIME_SLOT_NUM)
    {
        return NM_FOM_AC_INVALID_TIME_SLOT_ERROR;
    }
                                                                                                                                              
    abisChanl->subSlotNum = buffer[index++];
                                                                                                                                              
    /* Get Nack Cause if msg is Connect Terrestrial Signalling Nack or 
     * Disconnect Terrestrial Signalling Nack */
    if ((formGenElemnts->msgType == NM_CONNECT_TERRESTRIAL_SIGNALLING_NACK) ||
        (formGenElemnts->msgType == NM_DISCONNECT_TERRESTRIAL_SIGNALLING_NACK))
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.abisMsg.u.connTerr.nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Disconnect Terrestrial Signalling Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       The same API is used for Disconnect Terrestrial Traffic msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0220, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_ABIM_decodeConnTerrTraffic(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    ABIS_CHANNEL *abisChanl = &msg->u.formMsg.u.abisMsg.abisChanl;
    NM_ABIM_CONN_TERR_TRAFFIC *connTraf = &msg->u.formMsg.u.abisMsg.u.connTraf;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Abis Channel */
    if (buffer[index++] != NM_ABIS_CHANNEL)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    abisChanl->btsPortNum = buffer[index++];
                                                                                                                                              
    abisChanl->timeSlotNum = buffer[index++];
    if (abisChanl->timeSlotNum > NM_AC_END_TIME_SLOT_NUM)
    {
        return NM_FOM_AC_INVALID_TIME_SLOT_ERROR;
    }
                                                                                                                                              
    abisChanl->subSlotNum = buffer[index++];
                                                                                                                                              
    /* Initialise optional bit map to ZERO */
    CLEAR_NM_AM_CTT_OPTIONAL_BIT_MAP(msg);

    /* Get Radio Sub Channel if present*/
    if (buffer[index] == NM_RADIO_SUB_CHANNEL)
    {
        index++;
        SET_NM_AM_CTT_RADIO_SUB_CHANNEL(msg);

        connTraf->radioSubChanl = buffer[index++];
    }

    /* Get Nack Cause if msg is Connect Terrestrial Traffic Nack or
     * Disconnect Terrestrial Traffic Nack */
    if ((formGenElemnts->msgType == NM_CONNECT_TERRESTRIAL_TRAFFIC_NACK) ||
        (formGenElemnts->msgType == NM_DISCONNECT_TERRESTRIAL_TRAFFIC_NACK))
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        connTraf->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Connect Multi-drop Link Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This same API is used for Disconnect multi-drop Link msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0230, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TRM_decodeConnMultiDropLink(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    MD_BSC_LINK *bscLink = &msg->u.formMsg.u.transMsg.u.conLink.bscLink;
    MD_NEXT_BTS_LINK *btsLink = &msg->u.formMsg.u.transMsg.u.conLink.btsLink;
    NM_TRM_CON_MULTI_DROP_LINK *conLink = &msg->u.formMsg.u.transMsg.u.conLink;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Multi-drop BSC Link */
    if (buffer[index++] != NM_MULTI_DROP_BSC_LINK)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
    bscLink->btsPortNum = buffer[index++]; 

    bscLink->timeSlotNum = buffer[index++];
    if (bscLink->timeSlotNum > NM_MBL_END_TIME_SLOT_2MBPS_LINK)
    {
        return NM_FOM_MBL_TIME_SLOT_ERROR;
    }

    /* Multi-drop next BTS Link */
    if (buffer[index++] != NM_MULTI_DROP_NEXT_BTS_LINK)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
    btsLink->btsPortNum = buffer[index++];
 
    btsLink->timeSlotNum = buffer[index++];
    if (btsLink->timeSlotNum > NM_MBL_END_TIME_SLOT_2MBPS_LINK)
    {
        return NM_FOM_MBL_TIME_SLOT_ERROR;
    } 

    /* Get Nack Cause if msg is Connect Multi-drop link Nack or 
     * Disconnect Multi-drop link Nack */
    if ((formGenElemnts->msgType == NM_CONNECT_MULTI_DROP_LINK_NACK) || 
        (formGenElemnts->msgType == NM_DISCONNECT_MULTI_DROP_LINK_NACK))
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        conLink->nackCuase = buffer[index++];
    } 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Set BTS Attributes Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0240, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_AIM_decodeSetBtsAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    NM_AIM_SET_BTS_ATTR *btsAttr = &msg->u.formMsg.u.airMsg.u.btsAttr;
    INTER_LEVEL_BOUND *interLevel = &msg->u.formMsg.u.airMsg.u.btsAttr.interLevel;
    CON_FAIL_CRITERION *conFail = &msg->u.formMsg.u.airMsg.u.btsAttr.conFail;
    T200 *t200 = &msg->u.formMsg.u.airMsg.u.btsAttr.t200;
    OVERLOAD_PERIOD *overldPeriod = &msg->u.formMsg.u.airMsg.u.btsAttr.overldPeriod;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* intialise optional bit map field to ZERO*/ 
    CLEAR_NM_AIM_SBA_OPTIONAL_BIT_MAP(msg);
 
    /* Get Interference Level Boundaries if present */
    if (buffer[index] == NM_INTERFERENCE_LEVEL_BOUNDARIES)
    {
        index++;
        SET_NM_AIM_SBA_INTER_LEVEL_BOUNDARIES(msg);

        interLevel->interfBound0 = buffer[index++]; 
        interLevel->interfBound1 = buffer[index++];
        interLevel->interfBound2 = buffer[index++];
        interLevel->interfBound3 = buffer[index++];
        interLevel->interfBound4 = buffer[index++];
        interLevel->interfBound5 = buffer[index++];   
    } 

    /* Get Intave parameter if present */
    if (buffer[index] == NM_INTAVE_PARAMETER)
    {
        index++;
        SET_NM_AIM_SBA_INTAVE_PARAMETER(msg);

        btsAttr->intaveParam = buffer[index++];
        if (btsAttr->intaveParam > NM_IP_END_INTAVE_PARAM)
        {
            return NM_FOM_IP_INTAVE_PARAM_ERROR;
        }
    }

    /* Get Connection Failure Criterion if present*/
    if (buffer[index] == NM_CONNECTION_FAILURE_CRITERION)
    {
        index++;
        SET_NM_AIM_SBA_CONN_FAILURE_CRITERION(msg);

        conFail->length = buffer[index++];
        conFail->length = (conFail->length << 8) | buffer[index++];

        if (conFail->length < 0x01)
        {
            return NM_FOM_CFC_LENGTH_ERROR;
        }
        if (conFail->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        conFail->failCrit = buffer[index++];

        if (conFail->failCrit == NM_CFC_UPLINK_SACCH_ERROR_RATE)
        {
            conFail->critVal[0] = buffer[index++];
        } 
        else
        {
            memcpy(&conFail->critVal[0], &buffer[index], conFail->length - 1);
            index += (conFail->length - 1);
        } 
    }

    /* Get T200 if present */
    if (buffer[index] == NM_T200)
    {
        index++;
        SET_NM_AIM_SBA_T200(msg);

        t200->sdcch = buffer[index++]; 
        t200->facchFull = buffer[index++]; 
        t200->facchHalf = buffer[index++]; 
        t200->sacchSap10 = buffer[index++]; 
        t200->sacchSdcch = buffer[index++]; 
        t200->sdcchSap13 = buffer[index++]; 
        t200->sacchSap13 = buffer[index++]; 
    }

    /* Get Max Timing Advance if present */
    if (buffer[index] == NM_MAX_TIMING_ADVANCE)
    {
        index++;
        SET_NM_AIM_SBA_MAX_TIMING_ADVANCE(msg);

        btsAttr->maxTimeAdv = buffer[index++]; 
        if (btsAttr->maxTimeAdv > NM_MTA_END_MAX_TIMING_ADVANCE)
        {
            return NM_FOM_MTA_TIMING_ADV_ERROR;
        }
    }

    /* Get Overload Period if present */
    if (buffer[index] == NM_OVERLOAD_PERIOD)
    {
        index++;
        SET_NM_AIM_SBA_OVERLOAD_PERIOD(msg);

        overldPeriod->length = buffer[index++];
        overldPeriod->length = (overldPeriod->length << 8) | buffer[index++];

        if (overldPeriod->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&overldPeriod->period[0], &buffer[index], overldPeriod->length);
        index += overldPeriod->length;
    }  

    /* Get CCCH Load Threshold if present */
    if (buffer[index] == NM_CCCH_LOAD_THRESOLD)
    {
        index++;
        SET_NM_AIM_SBA_CCCH_LOAD_THRESHOLD(msg); 

        btsAttr->threshold = buffer[index++];
        if (btsAttr->threshold > NM_CLT_END_LOAD_THRESHOLD)
        {
            return NM_FOM_CLT_THRESHOLD_ERROR;
        }
    }  

    /* Get CCCH Load Indication Period if present */
    if (buffer[index] == NM_CCCH_LOAD_INDICATION_PERIOD)
    {
        index++;
        SET_NM_AIM_SBA_CCCH_LOAD_IND_PERIOD(msg);

        btsAttr->initPeriod = buffer[index++];
    }

    /* Get RACH Busy Threshold if present */
    if (buffer[index] == NM_RACH_BUSY_THRESOLD)
    {
        index++;
        SET_NM_AIM_SBA_RACH_BUSY_THRESHOLD(msg);

        btsAttr->busyThreshold = buffer[index++];
    }

    /* Get RACH Load Averaging Slots if present */
    if (buffer[index] == NM_RACH_LOAD_AVERAGING_SLOTS)
    {
        index++;
        SET_NM_AIM_SBA_RACH_LOAD_AVG_SLOTS(msg);        

        btsAttr->avgSlots = buffer[index++];
        btsAttr->avgSlots = (btsAttr->avgSlots << 8) | buffer[index++];
    }

    /* Get BTS Air Timer if present */
    if (buffer[index] == NM_BTS_AIR_TIMER)
    {
        index++;
        SET_NM_AIM_SBA_BTS_AIR_TIMER(msg);

        btsAttr->airT3105.tch = buffer[index++];
        btsAttr->airT3105.sdcch= buffer[index++];
    }

    /* Get NY1 if present */
    if (buffer[index] == NM_NY1)
    {
        index++;
        SET_NM_AIM_SBA_NY1(msg);

        btsAttr->ny1.tch = buffer[index++];
        btsAttr->ny1.sdcch = buffer[index++];
    }

    /* Get BCCH ARFCN if present */
    if (buffer[index] == NM_BCCH_ARFCN)
    {
        index++;
        SET_NM_AIM_SBA_BCCH_ARFCN(msg);
       
        btsAttr->arfcn = buffer[index++];
        btsAttr->arfcn = (btsAttr->arfcn << 8) | buffer[index++]; 
        if (btsAttr->arfcn > NM_BA_BCCH_END_ARFCN)
        {
            return NM_FOM_BA_ARFCN_ERROR;
        }
    }
 
    /* Get BSIC if present */
    if (buffer[index] == NM_BSIC)
    {
        index++;
        SET_NM_AIM_SBA_BSIC(msg);

        btsAttr->bsic = buffer[index++];
        if (btsAttr->bsic > NM_BSIC_END)
        {
            return NM_FOM_BSIC_ERROR;
        }
    }

    /* Get RF Power Reduction */
    if (buffer[index] == NM_RF_MAX_POWER_REDUCTION)
    {
	    index++;
        SET_NM_AIM_SBA_RF_MAX_POWER_REDUCTION(msg);

        btsAttr->powerRedn = buffer[index++];
    }

    /* Get Starting Time if present */
    if (buffer[index] == NM_STARTING_TIME)
    {
        index++;
        SET_NM_AIM_SBA_STARTING_TIME(msg);
       
        btsAttr->startCurFrameNo = buffer[index++];
        btsAttr->startCurFrameNo = (btsAttr->startCurFrameNo << 8) |
                                    buffer[index++];
    }

    if (buffer[index] == NM_PAGING_AG_PARAMS)
    {
        index++;
        SET_NM_AIM_SBA_PAGING_AG_PARAMS(msg);
                                                                                
        btsAttr->pageAgParams.bsPaMfrms = buffer[index++];
        btsAttr->pageAgParams.bsCcchChans = buffer[index++];
        btsAttr->pageAgParams.bsAgRes = buffer[index++];
        btsAttr->pageAgParams.pageAlg = buffer[index++];
   }
                                                                                
    if (buffer[index] == NM_SYST_INFO_LIST)
    {
        index++;
        SET_NM_AIM_SBA_SYST_INFO_LIST(msg);
                                                                                
        btsAttr->systInfoList.len = buffer[index++];
        memcpy(&btsAttr->systInfoList.six[0], &buffer[index],
                                 btsAttr->systInfoList.len);
        index += btsAttr->systInfoList.len;
    }
                                                                                
    if (buffer[index] == NM_FN_OFFSET)
    {
        index++;
        SET_NM_AIM_SBA_FN_OFFSET(msg);
                                                                                
        btsAttr->fnOffset = buffer[index++];
    }
    /* Get Nack Cause if msg is Set BTS Attributes Nack */
    if (formGenElemnts->msgType == NM_SET_BTS_ATTRIBUTES_NACK)
    {   
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        btsAttr->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Set Radio Carrier Attributes Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0240, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_AIM_decodeSetRadioCarrierAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    NM_AIM_SET_RADIO_ATTR *radioAttr = &msg->u.formMsg.u.airMsg.u.radioAttr;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    ARFCN_LIST  *arfcnList = &msg->u.formMsg.u.airMsg.u.radioAttr.arfcnList;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Initialise optional bit map to ZERO */
    CLEAR_NM_AIM_SRCA_OPTIONAL_BIT_MAP(msg);

    /* Get RF Max Power Reduction if present */
    if (buffer[index] == NM_RF_MAX_POWER_REDUCTION)
    {
        index++;
        SET_NM_AIM_SRCA_RF_MAX_POWER_REDUCTION(msg);

        radioAttr->powerRedu = buffer[index++];
    }

    /* Get ARFCN List if present */
    if (buffer[index] == NM_ARFCN_LIST)
    {
        index++;
        SET_NM_AIM_SRCA_ARFCN_LIST(msg);

        arfcnList->length = buffer[index++];
        arfcnList->length = (arfcnList->length << 8) | buffer[index++];

        if (arfcnList->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        for (i = 0; i < arfcnList->length; i++)
        {
            arfcnList->arfcn[i] = buffer[index++];
            arfcnList->arfcn[i] = (arfcnList->arfcn[i] << 8) | buffer[index++]; 
            if (arfcnList->arfcn[i] > NM_AL_END_ARFCN_LIST)
            {
                return NM_FOM_AIM_ARFCN_ERROR;
            }
        }
    }
    else
    {
        arfcnList->length = 0x00;
    }                                                                                                    

    /* Get Nack Cause if msg is Set Radio Carrier Attribute Nack */
    if (formGenElemnts->msgType == NM_SET_RADIO_CARRIER_ATTRIBUTES_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        radioAttr->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Set Channel Attributes Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0240, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_AIM_decodeSetChanlAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    NM_AIM_SET_CHANNEL_ATTR *chanlAttr = &msg->u.formMsg.u.airMsg.u.chanlAttr; 
    ARFCN_LIST *arfcnList = &msg->u.formMsg.u.airMsg.u.chanlAttr.arfcnList;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Intialise optional bit map field to ZERO */
    CLEAR_NM_AIM_SCA_OPTIONAL_BIT_MAP(msg);

    /* Get Channel Combination if present */
    if (buffer[index] == NM_CHANNEL_COMBINATION)
    {
        index++;
        SET_NM_AIM_SCA_CHANNEL_COMBINATION(msg);

        chanlAttr->chanlComb = buffer[index++];
    }

    /* Get HSN if present */
    if (buffer[index] == NM_HSN)
    {
        index++;
        SET_NM_AIM_SCA_HSN(msg);

        chanlAttr->hsn = buffer[index++];
        if (chanlAttr->hsn > NM_HSN_END)
        {
            return NM_FOM_HSN_ERROR;
        }
    } 

    /* Get MAIO if present */
    if (buffer[index] == NM_MAIO)
    {
        index++;
        SET_NM_AIM_SCA_MAIO(msg);

        chanlAttr->maioList.len = buffer[index++];
        memcpy(&chanlAttr->maioList.maio[0], &buffer[index],
                                     chanlAttr->maioList.len);
        index += chanlAttr->maioList.len;

/*
        chanlAttr->maio = buffer[index++];
        if (chanlAttr->maio > NM_MAIO_END)
        {
            return NM_FOM_MAIO_ERROR;
        }
*/
    }

    /* Get ARFCN List if present */
    if (buffer[index] == NM_ARFCN_LIST)
    {
        index++;
        SET_NM_AIM_SCA_ARFCN_LIST(msg);

        arfcnList->length = buffer[index++];
        arfcnList->length = (arfcnList->length << 8) | buffer[index++];

        if (arfcnList->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        for (i = 0; i < arfcnList->length; i++)
        {
            arfcnList->arfcn[i] = buffer[index++];
            arfcnList->arfcn[i] = (arfcnList->arfcn[i] << 8) | buffer[index++]; 
        }     
    }

    /* Get Starting Time if present */
    if (buffer[index] == NM_STARTING_TIME)
    {
        index++;
        SET_NM_AIM_SCA_STARTING_TIME(msg);

        chanlAttr->startCurFrameNo = buffer[index++];
        chanlAttr->startCurFrameNo = (chanlAttr->startCurFrameNo << 8) |
                                    buffer[index++];
    }

    /* Get TSC if present */
    if (buffer[index] == NM_TSC)
    {
        index++;
        SET_NM_AIM_SCA_TSC(msg);
 
        chanlAttr->tscSeqCode = buffer[index++];
        if (chanlAttr->tscSeqCode > NM_TSC_END_VALUE)
        {
            return NM_FOM_TSC_ERROR;
        }  
    }

    /* Get RX Max Power Reduction */
    if (buffer[index] == NM_RF_MAX_POWER_REDUCTION)
    {
	    index++;
        SET_NM_AIM_SCA_RF_MAX_POWER_REDUCTION(msg);
        chanlAttr->powerRedn = buffer[index++];
    }

    /* Get Nack Cause if msg is Set Channel Attributes Nack */
    if (formGenElemnts->msgType == NM_SET_CHANNEL_ATTRIBUTES_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        chanlAttr->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Perform Test Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0250, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TM_decodePerformTest(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    NM_TM_PERFORM_TEST *perfTest = &msg->u.formMsg.u.testMsg.u.perfTest;
    PHYSICAL_CONFIG *phyContext = &msg->u.formMsg.u.testMsg.u.perfTest.phyContext;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Test No */
    if (buffer[index++] != NM_TEST_NO)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    msg->u.formMsg.u.testMsg.testNum = buffer[index++];

    /* Get Autonomously Report */
    if (buffer[index++] != NM_AUTONOMOUSLY_REPORT)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    } 

    perfTest->autoRep = buffer[index++];
                                                                                                                                              
    /* Initialse optional bit map to ZERO */
    CLEAR_NM_TM_PT_OPTIONAL_BIT_MAP(msg);

    /* Get Test Duration if present */
    if (buffer[index] == NM_TEST_DURATION)
    {
        index++;
        SET_NM_TM_PT_TEST_DURATION(msg);

        perfTest->testDura = buffer[index++];
        perfTest->testDura = (perfTest->testDura << 8) | buffer[index++];
 
        if (perfTest->testDura < NM_TD_START_DURATION)
        {
            return NM_FOM_TM_DURATION_ERROR;
        } 
    }

    /* Get Physical Configuration if present */
    if (buffer[index] == NM_PHYSICAL_CONFIG)
    {
        index++;
        SET_NM_TM_PT_PHYSICAL_CONFIGURATION(msg);

        phyContext->length = buffer[index++];
        phyContext->length = (phyContext->length << 8) | buffer[index++];

        if (phyContext->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&phyContext->testConfig[0], &buffer[index], phyContext->length);
        index += phyContext->length;
    }

    /* Get Nack Cause if msg is Perform Test Nack */
    if (formGenElemnts->msgType == NM_PERFORM_TEST_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        perfTest->nackCuase = buffer[index++];
    }
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Test Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0250, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TM_decodeTestReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_TM_TEST_REP *testRep = &msg->u.formMsg.u.testMsg.u.testRep;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Test No */
    if (buffer[index++] != NM_TEST_NO)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    } 

    msg->u.formMsg.u.testMsg.testNum = buffer[index++];
 
    /* Set Test Report Info */
    if (buffer[index++] != NM_TEST_REPORT_INFO)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
 
    testRep->length = buffer[index++];
    testRep->length = (testRep->length << 8) | buffer[index++];

    if (testRep->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&testRep->resultInfo[0], &buffer[index], testRep->length);
    index += testRep->length;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Send Test Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This same API is used for Stop Test Message.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0250, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_TM_decodeSendTestReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Test No */
    if (buffer[index++] != NM_TEST_NO)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    msg->u.formMsg.u.testMsg.testNum = buffer[index++];
 
    /* Get Nack Cause if msg is Send Test Report Nack or Stop Test Nack*/
    if ((msg->u.formMsg.formGenElemnts.msgType == NM_SEND_TEST_REPORT_NACK) || 
        (msg->u.formMsg.formGenElemnts.msgType == NM_STOP_TEST_NACK))
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.testMsg.u.sendRep.nackCuase = buffer[index++];
    }
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the State Changed Event Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_decodeStateChangdEventRep(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0, i;
    NM_SM_STATE_CHNG_EVENT_REP *changeEv = &msg->u.formMsg.u.stateMsg.u.changeEv; 
    AVAILABILITY_STATUS *availStat = &msg->u.formMsg.u.stateMsg.u.changeEv.availStat;
    SITE_INPUTS *siteInputs = &msg->u.formMsg.u.stateMsg.u.changeEv.siteInputs;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Intialise optional bit map to ZERO */
    CLEAR_NM_SM_SCER_OPTIONAL_BIT_MAP(msg);

    /* Get Operational State if present */ 
    if (buffer[index] == NM_OPERATIONAL_STATE)
    {
        index++; 
        SET_NM_SM_SCER_OPERATIONAL_STATE(msg);
 
        changeEv->operanStat = buffer[index++];
        if (changeEv->operanStat == NM_OS_NULL)
        {
            return NM_FOM_OS_INVALID_STATE_ERROR;
        }
    } 

    /* Get Availability State if present */ 
    if (buffer[index] == NM_AVAILABLITY_STATUS)
    {
        index++;
        SET_NM_SM_SCER_AVAILABILITY_STATE(msg);

        availStat->length = buffer[index++];
        availStat->length = (availStat->length << 8) | buffer[index++];

        if (availStat->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&availStat->status[0], &buffer[index], availStat->length);
        index += availStat->length;
    }

    /* Get Manufacturer Dependent State if present */ 
    if (buffer[index] == NM_MANUFACTURE_DEPENDENT_STATE)
    {
        index++;
        SET_NM_SM_SCER_MAN_DEP_STATE(msg);

        changeEv->mfdDepen = buffer[index++];
    }

    /* Get Site Inputs if present */ 
    if (buffer[index] == NM_SITE_INPUTS)
    {
        index++;
        SET_NM_SM_SCER_SITE_INPUTS(msg);
        
        siteInputs->length = buffer[index++];
        siteInputs->length = (siteInputs->length << 8) | buffer[index++];

        if (siteInputs->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        for (i = 0; i < siteInputs->length; i++)
        {
            siteInputs->attr[i].input = buffer[index] & 0x7F;
            siteInputs->attr[i].state = (buffer[index++] & 0x80) >> 7;; 
        }
    } 

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Failure Event Report Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_decodeFailureEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SM_FAIL_EVENT_REP *failEv = &msg->u.formMsg.u.stateMsg.u.failEv;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.stateMsg.u.failEv.probCause; 
    ADDITIONAL_TEXT *addText = &msg->u.formMsg.u.stateMsg.u.failEv.addText;
    ADDITIONAL_INFO *addInfo = &msg->u.formMsg.u.stateMsg.u.failEv.addInfo;
    HW_DESCRIPTION *hwDesc = &msg->u.formMsg.u.stateMsg.u.failEv.hwDescr; 
    SW_DESCRIPTION *swDescr = &msg->u.formMsg.u.stateMsg.u.failEv.swDescr;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Event Type */ 
    if (buffer[index++] != NM_EVENT_TYPE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
    failEv->evtType = buffer[index++]; 
     
    /* Get Perceived Severity */
    if (buffer[index++] != NM_PERCEIVED_SEVERITY)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
    failEv->percvdSever = buffer[index++];

    /* Get Probable Cause */
    if (buffer[index++] != NM_PROBABLE_CAUSE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
    probCause->type = buffer[index++];
    
    probCause->value = buffer[index++];
    probCause->value = (probCause->value << 8) | buffer[index++];

    /* Intialise optional bit map to ZERO */ 
    CLEAR_NM_SM_FER_OPTIONAL_BIT_MAP(msg);

    /* Get Specific Problems if present */
    if (buffer[index] == NM_SPECIFIC_PROBLEMS)
    {
        index++;
        SET_NM_SM_FER_SPECIFIC_PROBLEMS(msg);  
        failEv->specProbs = buffer[index++];
    }
 
    /* Get HW Description if present */
    if (buffer[index] == NM_HW_DESCRIPTION)
    {
        index++;
        SET_NM_SM_FER_HW_DESCRIPTION(msg);

        /* Equipment Id */
        hwDesc->equipIdLen = buffer[index++];
        hwDesc->equipIdLen = (hwDesc->equipIdLen << 8) | buffer[index++];

        if (hwDesc->equipIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwDesc->equipId[0], &buffer[index], hwDesc->equipIdLen);
        index += hwDesc->equipIdLen;
                                                                                                                                              
        /* Equipment Type */
        hwDesc->equipTypeLen = buffer[index++];
        hwDesc->equipTypeLen = (hwDesc->equipTypeLen << 8) | buffer[index++];

        if (hwDesc->equipTypeLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&hwDesc->equipType[0], &buffer[index], hwDesc->equipTypeLen);
        index += hwDesc->equipTypeLen;
                                                                                                                                              
        /* Equipment Version */
        hwDesc->equipVerLen = buffer[index++];
        hwDesc->equipVerLen = (hwDesc->equipVerLen << 8) | buffer[index++];

        if (hwDesc->equipVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&hwDesc->equipVer[0], &buffer[index], hwDesc->equipVerLen);
        index += hwDesc->equipVerLen;
                                                                                                                                              
        /* Location */
        hwDesc->locLen = buffer[index++];
        hwDesc->locLen = (hwDesc->locLen << 8) | buffer[index++];

        if (hwDesc->locLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwDesc->location[0], &buffer[index], hwDesc->locLen);
        index += hwDesc->locLen;
                                                                                                                                              
        /* Man Dep Info */
        hwDesc->infoLen = buffer[index++];
        hwDesc->infoLen = (hwDesc->infoLen << 8) | buffer[index++];

        if (hwDesc->infoLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&hwDesc->info[0], &buffer[index], hwDesc->infoLen);
        index += hwDesc->infoLen;
    }
 
    /* Get SW Description if present */
    if (buffer[index] == NM_SW_DESCRIPTION)
    {
        index++;
        SET_NM_SM_FER_SW_DESCRIPTION(msg);
 
        if (buffer[index++] != NM_FILE_ID)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }

        swDescr->fileIdLen = buffer[index++];
        swDescr->fileIdLen = (swDescr->fileIdLen << 8) | buffer[index++];

        if (swDescr->fileIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&swDescr->fileId[0], &buffer[index], swDescr->fileIdLen);
        index += swDescr->fileIdLen;

        if (buffer[index++] != NM_FILE_VERSION)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }

        swDescr->fileVerLen = buffer[index++];
        swDescr->fileVerLen = (swDescr->fileVerLen << 8) | buffer[index++];

        if (swDescr->fileVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&swDescr->fileVer[0], &buffer[index], swDescr->fileVerLen);
        index += swDescr->fileVerLen;
    }
 
    /* Get Additional Text if present */
    if (buffer[index] == NM_ADDITIONAL_TEXT)
    {
        index++;
        SET_NM_SM_FER_ADDITIONAL_TEXT(msg);

        addText->length = buffer[index++];
        addText->length = (addText->length << 8) | buffer[index++];

        if (addText->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&addText->value, &buffer[index], addText->length);
        index += addText->length;
    }
 
    /* Get Additional Info if present */
    if (buffer[index] == NM_ADDITIONAL_INFO)
    {
        index++;
        SET_NM_SM_FER_ADDITIONAL_INFO(msg);

        addInfo->length = buffer[index++];
        addInfo->length = (addInfo->length << 8) | buffer[index++];

        if (addInfo->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&addInfo->value, &buffer[index], addInfo->length);
        index += addInfo->length;
    }
 
    /* Get Outstanding Alarm Sequence if present */
    if (buffer[index] == NM_OUTSTANDING_ALARM_SEQUENCE)
    {
        index++;
        SET_NM_SM_FER_OUTSTANDING_ALARM_SEQ(msg);

        failEv->alarmSeq = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Stop Sending Event Reports Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This same API is used for Restart Sending Event Reports msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_decodeStopSendEventReport(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;
    NM_SM_STOP_SEND_EVENT_REP *stopEv = &msg->u.formMsg.u.stateMsg.u.stopEv; 
    AVAILABILITY_STATUS *availStat = &msg->u.formMsg.u.stateMsg.u.stopEv.availStat;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.stateMsg.u.stopEv.probCause; 
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Intialise optional bit map field to ZERO */
    CLEAR_NM_SM_SSER_OPTIONAL_BIT_MAP(msg);
  
    /* Get Operational State if present */
    if (buffer[index] == NM_OPERATIONAL_STATE)
    {
        index++;
        SET_NM_SM_SSER_OPERATIONAL_STATE(msg);

        stopEv->operanStat = buffer[index++];
        if (stopEv->operanStat == NM_OS_NULL)
        {
            return NM_FOM_OS_INVALID_STATE_ERROR;
        }
    }
                                                                                                                                              
    /* Get Availability State if present */
    if (buffer[index] == NM_AVAILABLITY_STATUS)
    {
        index++;
        SET_NM_SM_SSER_AVAILABILTY_STATE(msg);
                                                                                                                                              
        availStat->length = buffer[index++];
        availStat->length = (availStat->length << 8) | buffer[index++];

        if (availStat->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&availStat->status[0], &buffer[index], availStat->length);
        index += availStat->length;
    }
                                                                                                                                              
    /* Get Manufacturer Dependent State if present */
    if (buffer[index] == NM_MANUFACTURE_DEPENDENT_STATE)
    {
        index++;
        SET_NM_SM_SSER_MFD_DEP_STATE(msg);

        stopEv->mfdDepen = buffer[index++];
    }

    /* Get Probable Cause if present */
    if (buffer[index] == NM_PROBABLE_CAUSE)
    {
        index++;
        SET_NM_SM_SSER_PROBABLE_CAUSE(msg);

        probCause->type = buffer[index++];
                                                                                                                                              
        probCause->value = buffer[index++];
        probCause->value = (probCause->value << 8) | buffer[index++];
    }                                                                                       

    /* Get Specific Problems if present */
    if (buffer[index] == NM_SPECIFIC_PROBLEMS)
    {
        index++;
        SET_NM_SM_SSER_SPECIFIC_PROBLEMS(msg);

        stopEv->specProbs = buffer[index++];
    }

    /* Get Nack Cause if msg is Stop Sending Event Reports Nack or
     * Restart Sending Event Reports Nack */
    if ((formGenElemnts->msgType == NM_STOP_SENDING_EVENT_REPORTS_NACK) ||
        (formGenElemnts->msgType == NM_RESTART_SENDING_EVENT_REPORTS_NACK))
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        stopEv->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Change Administrative State Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This same API is used for Change Administrative State Request msg.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_decodeChangeAdminState(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SM_CHNG_ADMIN_STATE *state = &msg->u.formMsg.u.stateMsg.u.state;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
 
    if (buffer[index++] != NM_ADMINISTRATIVE_STATE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
 
    state->adminStat = buffer[index++];

    /* Get Nack Cause if msg is Change Administrative State Nack or 
     * Change Administrative State Request Nack */
    if ((formGenElemnts->msgType == NM_CHANGE_ADMINISTRATIVE_STATE_NACK) ||
        (formGenElemnts->msgType == NM_CHANGE_ADMINISTRATIVE_STATE_REQUEST_NACK))
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        state->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal
*
* PURPOSE:
*       Decoding the TRX Hello Message.
* INPUT:
*       buffer - encoded value to be parsed
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       msg - values to be filled in the msg after parsing
* RETURNS:
*       ITS_SUCCESS
* COMMENTS:
*       This same API is used for TRX Hello Message.
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
*/
static ITS_INT
NM_SM_decodeTrxHello(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_SM_TRX_HELLO *trxHello = &msg->u.formMsg.u.stateMsg.u.trxHello;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    if(buffer[index++] != NM_ONM_PROT_VERSION)
    {
        return !ITS_SUCCESS;
    }

    trxHello->onmProtoVer.versionX = buffer[index++];
    trxHello->onmProtoVer.versionY = buffer[index++];

    if(buffer[index++] != NM_HW_CAPAB)
    {
        return !ITS_SUCCESS;
    }

    trxHello->hwCapab.freqHop = buffer[index++];
    trxHello->hwCapab.diversity = buffer[index++];
    trxHello->hwCapab.powClassSup = buffer[index++];
    trxHello->hwCapab.freqBand = buffer[index++];
    trxHello->hwCapab.lsclAvail = buffer[index++];
    trxHello->hwCapab.memoryCapb = buffer[index++];

#if 0
    /*optional parameters start from here*/
    if (buffer[index] == NM_SW_DESCRIPTION)
    {
	index++;
        SET_NM_SM_TRX_HELLO_SW_DESC(msg);
        trxHello->swDesc.fileIdLen = buffer[index++];
        trxHello->swDesc.fileIdLen = (trxHello->swDesc.fileIdLen  << 8) |
                                                          buffer[index++];
        if (trxHello->swDesc.fileIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        memcpy(&trxHello->swDesc.fileId[0], &buffer[index],
                                 trxHello->swDesc.fileIdLen);
        index += trxHello->swDesc.fileIdLen;

        trxHello->swDesc.fileVerLen = buffer[index++];
        trxHello->swDesc.fileVerLen = (trxHello->swDesc.fileVerLen << 8) |
                                                          buffer[index++];
        if (trxHello->swDesc.fileVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
        memcpy(&trxHello->swDesc.fileVer[0], &buffer[index],
                                 trxHello->swDesc.fileVerLen);
        index += trxHello->swDesc.fileVerLen;
    }

    if(buffer[index] == NM_HW_DESCRIPTION)
    {
        index++;
        SET_NM_SM_TRX_HELLO_HW_DESC(msg);
        trxHello->hwDesc.equipIdLen = buffer[index++];
        trxHello->hwDesc.equipIdLen  = (trxHello->hwDesc.equipIdLen << 8) |
                                                          buffer[index++];
        if (trxHello->hwDesc.equipIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&trxHello->hwDesc.equipId[0], &buffer[index],
                             trxHello->hwDesc.equipIdLen);
        index += trxHello->hwDesc.equipIdLen ;

        trxHello->hwDesc.equipTypeLen = buffer[index++];
        trxHello->hwDesc.equipTypeLen = (trxHello->hwDesc.equipTypeLen << 8) |                                                      buffer[index++];

        if (trxHello->hwDesc.equipTypeLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&trxHello->hwDesc.equipType[0], &buffer[index],
                             trxHello->hwDesc.equipTypeLen);
        index += trxHello->hwDesc.equipTypeLen;

        trxHello->hwDesc.equipVerLen = buffer[index++];
        trxHello->hwDesc.equipVerLen = (trxHello->hwDesc.equipVerLen << 8) |
                                                           buffer[index++];

        if (trxHello->hwDesc.equipVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&trxHello->hwDesc.equipVer[0], &buffer[index],
                                trxHello->hwDesc.equipVerLen);
        index += trxHello->hwDesc.equipVerLen;

        trxHello->hwDesc.locLen = buffer[index++];
        trxHello->hwDesc.locLen = (trxHello->hwDesc.locLen << 8) |
                                                           buffer[index++];

        if (trxHello->hwDesc.locLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&trxHello->hwDesc.location[0], &buffer[index],
                                       trxHello->hwDesc.locLen);
        index += trxHello->hwDesc.locLen;

        trxHello->hwDesc.infoLen = buffer[index++];
        trxHello->hwDesc.infoLen = (trxHello->hwDesc.infoLen << 8) |
                                                           buffer[index++];

        if (trxHello->hwDesc.infoLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&trxHello->hwDesc.info[0], &buffer[index],
                                 trxHello->hwDesc.infoLen);
        index += trxHello->hwDesc.infoLen;
    }
#endif

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Changeover Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_decodeChangeover(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    SOURCE *src = &msg->u.formMsg.u.equipMsg.u.changeOver.src;
    DESTINATION *dest = &msg->u.formMsg.u.equipMsg.u.changeOver.dest;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get Source */
    if (buffer[index++] != NM_SOURCE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    src->length = buffer[index++];
    src->length = (src->length << 8) | buffer[index++];

    if (src->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&src->value[0], &buffer[index], src->length);
    index += src->length;

    /* Get Destination */
    if (buffer[index++] != NM_DESTINATION)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    } 

    dest->length = buffer[index++];
    dest->length = (dest->length << 8) | buffer[index++];

    if (dest->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
  
    memcpy(&dest->value[0], &buffer[index], dest->length);
    index += dest->length;

    /* Get Nack Cause if msg is Changeover Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_CHANGEOVER_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.equipMsg.u.changeOver.nackCuase = buffer[index++];
    }
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Opstart Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_decodeOpstart(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get Nack Cause if msg is Opstart Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_OPSTART_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.equipMsg.u.opStart.nackCuase = buffer[index++];
    }
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Set Site Outputs Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This same API is used for Change HW Configuration message.
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_decodeSetSiteOutputs(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_EM_SET_SITE_OUTPUTS *siteOutput = &msg->u.formMsg.u.equipMsg.u.siteOutput;
    FORM_GEN_ELEMENTS *formGenElemnts = &msg->u.formMsg.formGenElemnts;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Site Outputs */
    if (buffer[index++] != NM_SITE_OUTPUTS)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    siteOutput->length = buffer[index++];
    siteOutput->length = (siteOutput->length << 8) | buffer[index++];

    if (siteOutput->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&siteOutput->output[0], &buffer[index], siteOutput->length);
    index += siteOutput->length;
     
    /* Get Nack Cause if msg is Set Site Outputs Nack or 
     * Change HW Configuration Nack */
    if ((formGenElemnts->msgType == NM_SET_SITE_OUTPUTS_NACK) || 
        (formGenElemnts->msgType == NM_CHANGE_HW_CONFIGURATION_NACK))
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        siteOutput->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Get Attributes Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0290, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_decodeGetAttr(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_MS_GET_ATTR *getAttr = &msg->u.formMsg.u.miscMsg.u.getAttr;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
   
    if (buffer[index++] != NM_LIST_OF_REQUIRED_ATTRIBUTES)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    getAttr->length = buffer[index++];
    getAttr->length = (getAttr->length << 8) | buffer[index++];

    if (getAttr->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy(&getAttr->atrrId[0], &buffer[index], getAttr->length);
    index += getAttr->length;

    /* Set Nack Cause if msg is Get Attributes Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_GET_ATTRIBUTES_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        getAttr->nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Get Attributes Response Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0290, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_decodeGetAttrResp(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_MS_GET_ATTR_RESP *getAttrResp = &msg->u.formMsg.u.miscMsg.u.getAttrResp;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    if (buffer[index++] != NM_GET_ATTRIBUTE_RESPONSE_INFO)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }  

    getAttrResp->length = buffer[index++];
    getAttrResp->length = (getAttrResp->length << 8) | buffer[index++];

    if ((getAttrResp->length < 1) || (getAttrResp->length > MAX_CONTENT_LENGTH))
    {
        return CONTENT_LENGTH_ERROR;
    }

    getAttrResp->notRepCount = buffer[index++]; 
    if (getAttrResp->notRepCount > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }

    memcpy( &getAttrResp->notRep[0], &buffer[index], getAttrResp->notRepCount); 
    index += getAttrResp->notRepCount;

    memcpy(&getAttrResp->reported[0], &buffer[index], 
            (getAttrResp->length - getAttrResp->notRepCount - 1));
    index += (getAttrResp->length - getAttrResp->notRepCount - 1);
 
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Set Alarm Threshold Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0290, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_decodeSetAlarmThreshold(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    POWER_OUTPUT_THRESHOLD *powerOutput = 
                   &msg->u.formMsg.u.miscMsg.u.alarmThresh.powerOutput;
    PROBABLE_CAUSE *probCause = &msg->u.formMsg.u.miscMsg.u.alarmThresh.probCause;
    VSWR_THRESHOLD *vswr = &msg->u.formMsg.u.miscMsg.u.alarmThresh.vswr;
    MFD_THRESHOLDS *mfdThresh = &msg->u.formMsg.u.miscMsg.u.alarmThresh.mfdThresh;

    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Get Probable Cause */
    if (buffer[index++] != NM_PROBABLE_CAUSE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
    probCause->type = buffer[index++];

    probCause->value = buffer[index++];
    probCause->value = (probCause->value << 8) | buffer[index++];

    /* Initialise optional bit map to ZERO */
    CLEAR_NM_MM_SAT_OPTIONAL_BIT_MAP(msg);

    /* Get Power Output Thresholds if present */
    if (buffer[index] == NM_POWER_OUTPUT_THRESHOLDS)
    {
        index++;
        SET_NM_MM_SAT_POWER_OUTPUT_THRESHOLD(msg);

        powerOutput->fault = buffer[index++];
        if (powerOutput->fault > NM_POT_END_OPT)
        {
            return NM_FOM_POT_FAULT_ERROR;
        }    

        powerOutput->reduced = buffer[index++];
        if (powerOutput->reduced > NM_POT_END_ROPT)
        {
            return NM_FOM_POT_REDUCED_ERROR;
        }

        powerOutput->excessive = buffer[index++];
        if (powerOutput->excessive > NM_POT_END_EOPT)
        {
            return NM_FOM_POT_EXCESSIVE_ERROR;
        }
    }

    /* Get VSWR Thresholds if present if present */
    if (buffer[index] == NM_VSWR_THRESOLDS)
    {
        index++;
        SET_NM_MM_SAT_VSWR_THRESHOLDS(msg);

        vswr->faulty = buffer[index++];
        if (vswr->faulty > NM_VSWR_END_FAULTY_ANTENNA)
        {
            return NM_FOM_VT_FAULTY_ERROR;
        }

        vswr->notAdjusted = buffer[index++];    
        if (vswr->notAdjusted > NM_VSWR_END_ANTENNA_NOT_ADJUSTED)
        {
            return NM_FOM_VT_NOT_ADJUSTED_ERROR;
        }
    }

    /* Get Manufacturer Dependent Thresholds if present */
    if (buffer[index] == NM_MANUFACTURE_DEPENDENT_THRESHOLDS)
    {
        index++;
        SET_NM_MM_SAT_MFD_DEPENDENT_THRESHOLDS(msg);

        mfdThresh->length = buffer[index++];
        mfdThresh->length = (mfdThresh->length << 8) | buffer[index++];

        if (mfdThresh->length > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&mfdThresh->mfdDependnt[0], &buffer[index], mfdThresh->length);
        index += mfdThresh->length;
    }        

    /* Get Nack Cause if msg is Set Alarm Threshold Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_SET_ALARM_THRESHOLD_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.miscMsg.u.alarmThresh.nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Reinitialse Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0270, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_EM_decodeReinitialise(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    HW_DESCRIPTION *hwDesc = &msg->u.formMsg.u.equipMsg.u.reInit.hwDesc; 
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Initialise optional bit map to ZERO */
    CLEAR_NM_EM_REIN_OPTIONAL_BIT_MAP(msg);

    /* Get HW Description if present */
    if (buffer[index] == NM_HW_DESCRIPTION)
    {
        index++;
        SET_NM_EM_REIN_HW_DESCRIPTION(msg);

        /* Equipment Id */ 
        hwDesc->equipIdLen = buffer[index++];
        hwDesc->equipIdLen = (hwDesc->equipIdLen << 8) | buffer[index++];

        if (hwDesc->equipIdLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
      
        memcpy(&hwDesc->equipId[0], &buffer[index], hwDesc->equipIdLen);
        index += hwDesc->equipIdLen;

        /* Equipment Type */
        hwDesc->equipTypeLen = buffer[index++];
        hwDesc->equipTypeLen = (hwDesc->equipTypeLen << 8) | buffer[index++];

        if (hwDesc->equipTypeLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }

        memcpy(&hwDesc->equipType[0], &buffer[index], hwDesc->equipTypeLen);
        index += hwDesc->equipTypeLen;

        /* Equipment Version */
        hwDesc->equipVerLen = buffer[index++];
        hwDesc->equipVerLen = (hwDesc->equipVerLen << 8) | buffer[index++];

        if (hwDesc->equipVerLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwDesc->equipVer[0], &buffer[index], hwDesc->equipVerLen);
        index += hwDesc->equipVerLen;

        /* Location */
        hwDesc->locLen = buffer[index++];
        hwDesc->locLen = (hwDesc->locLen << 8) | buffer[index++];

        if (hwDesc->locLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwDesc->location[0], &buffer[index], hwDesc->locLen);
        index += hwDesc->locLen;
   
        /* Man Dep Info */
        hwDesc->infoLen = buffer[index++];
        hwDesc->infoLen = (hwDesc->infoLen << 8) | buffer[index++];

        if (hwDesc->infoLen > MAX_CONTENT_LENGTH)
        {
            return CONTENT_LENGTH_ERROR;
        }
                                                                                                                                              
        memcpy(&hwDesc->info[0], &buffer[index], hwDesc->infoLen);
        index += hwDesc->infoLen;
    }
    
    /* Get Nack Cause if msg is Reinitialize Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == NM_REINITIALIZE_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.equipMsg.u.reInit.nackCuase = buffer[index++];
    }

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Measurement Result Request Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       This same API is used for Start Measurement, Stop Measurement msg's
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0280, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_decodeMeasResultReq(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Measurement Identifier */
    if (buffer[index++] != NM_MEASUREMENT_TYPE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }

    msg->u.formMsg.u.measMsg.measId = buffer[index++];  

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Measurement Result Response Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0280, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_MM_decodeMeasResultResp(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
    NM_MM__MEAS_RES_RESP *measResp = &msg->u.formMsg.u.measMsg.u.measResp;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Measurement Identifier */
    if (buffer[index++] != NM_MEASUREMENT_TYPE)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    } 

    msg->u.formMsg.u.measMsg.measId = buffer[index++];

    /* Get Measurement Result */
    if (buffer[index++] != NM_MEASUREMENT_RESULT)
    {
        return NM_INVLID_ATTRIBUTE_ID;
    }
  
    measResp->length = buffer[index++];
    measResp->length = (measResp->length << 8) | buffer[index++];

    if (measResp->length > MAX_CONTENT_LENGTH)
    {
        return CONTENT_LENGTH_ERROR;
    }
 
    memcpy(&measResp->measResult[0], &buffer[index], measResp->length);
    index += measResp->length;

    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Decoding the Report Outstanding Alarms Message.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
* COMMENTS: 
*       None
* HISTORY: 
* -------------------------------------------------------------------------
*  Name     Date         Reference                Description
* -------------------------------------------------------------------------
* mkrishna  08-08-2005   IMR-SDS-ABIS-V1.0.2 
*                        ID :: D0260, ID :: D0120,
*                        ID :: D0100
*/
static ITS_INT
NM_SM_decodeReportOutstandAlarms(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_OCTET *buffer)
{
    ITS_UINT index = 0, ret = 0;
                                                                                                                                              
    ret = decodeFomCommonElements(msg, &index, buffer);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    /* Get Nack Cause if msg is Report Outstanding Alarms Nack */
    if (msg->u.formMsg.formGenElemnts.msgType == 
        NM_REPORT_OUTSTANDING_ALARMS_NACK)
    {
        if (buffer[index++] != NM_NACK_CAUSES)
        {
            return NM_INVLID_ATTRIBUTE_ID;
        }
        msg->u.formMsg.u.stateMsg.u.repAlarm.nackCuase = buffer[index++];
    }
                                                                                                                                              
    return ITS_SUCCESS;
}

/*implementation:internal 
* 
* PURPOSE:  
*       Display Reserved/Invalid message Type.
* INPUT: 
*       buffer - encoded value to be parsed
* INPUT/OUTPUT: 
*       None
* OUTPUT: 
*       msg - values to be filled in the msg after parsing 
* RETURNS: 
*       ITS_SUCCESS
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
reserved(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
         ITS_OCTET *buffer)
{
    printf("Reserved/Invalid  Message Type \n");

    return ITS_SUCCESS;
}

ITS_INT (*networkManagementEncoding[MAX_NETWORK_FUNS_SIZE])() = {
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
                            NM_SWDM_encodeLoadDataAbort,      /* 0x10 */  
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

ITS_INT (*networkManagementDecoding[MAX_NETWORK_FUNS_SIZE])() = {
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
                            NM_SWDM_decodeLoadDataAbort,      /* 0x10 */  
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
/*implementation:external
*
* PURPOSE:
*       Encoding the Network Management Message.
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
*                        ID :: D0030, ID :: D0120,
*                        ID :: D0070, ID :: D0080
*/
ITS_INT
ABIS_NMM_Encode(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT *size,
                ITS_OCTET *buffer)
{
    ITS_INT  ret = 0;
                                                                                                                                              
    if ((buffer == NULL) || (msg == NULL))
    {
        return ABIS_NOMEM;
    }

    /* At the moment, it is assumed that the user allocates enough buffer
     * memory to hold the encoded buffer 
     */
#if 0
    /* make sure buffer size is sufficient */
    if (sizeof(ABIS_NETWORK_MANAGEMENT_MSG) > *size)
    {
       return ABIS_INVALID_LEN;
    }
#endif
                                                                                                                                              
    ret = (networkManagementEncoding[msg->u.formMsg.formGenElemnts.msgType])
           (msg, size, buffer);
                                                                                                                                              
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    return ret;
}

/*implementation:external
*
* PURPOSE:
*       Decoding the Network Management Message.
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
*                        ID :: D0040, ID :: D0120,
*                        ID :: D0070, ID :: D0080
*/
ITS_INT
ABIS_NMM_Decode(ABIS_NETWORK_MANAGEMENT_MSG *msg, ITS_UINT length,
                ITS_OCTET *buffer)
{
    ITS_INT  ret = 0;
                                                                                                                                              
    if ((buffer == NULL) || (msg == NULL))
    {
        return ABIS_NOMEM;
    } 

#if 0
    /* buffer length shouldn't cross max limit */
    if (sizeof(ABIS_NETWORK_MANAGEMENT_MSG) <= length)
    {
        ret = ABIS_INVALID_LEN;
    }
#endif                                                                                                                                              
    ret = (networkManagementDecoding[buffer[4]])(msg, buffer);
                                                                                                                                              
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }
                                                                                                                                              
    return ret;
}
