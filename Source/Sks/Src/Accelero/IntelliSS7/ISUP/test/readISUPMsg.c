/****************************************************************************
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: readISUPMsg.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:07  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:02  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:59  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.2.6.1  2004/01/05 09:55:46  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.1.4.2.2.4  2003/11/03 14:14:35  sjaddu
 * LOG: Removed c++ style comments.
 * LOG:
 * LOG: Revision 7.1.4.2.2.3  2003/09/15 11:17:57  akumar
 * LOG: Bug Fix.
 * LOG:
 * LOG: Revision 7.1.4.2.2.2  2003/09/11 09:04:18  akumar
 * LOG: ServiceActivation param issue solved.
 * LOG:
 * LOG: Revision 7.1.4.2.2.1  2003/09/11 06:03:19  akumar
 * LOG: Some modifications to RUN the variants.
 * LOG:
 * LOG: Revision 7.1.4.2  2003/06/26 04:17:00  sjaddu
 * LOG: Service activation is changed for 92 and 95.
 * LOG:
 * LOG: Revision 7.1.4.1  2003/06/18 09:10:26  tsanthosh
 * LOG: Added latest files.
 * LOG:
 * LOG: Revision 7.3  2002/10/25 16:11:58  ssingh
 * LOG: Put some comments as fixing BUG 148.
 * LOG:
 * LOG: Revision 7.2  2002/10/10 10:23:01  sjaddu
 * LOG: Changed ISUP_PRM_USER_SERVICE_INFORM_PRIME to ISUP_PRM_USER_SERVICE_INFO_PRIME.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.5  2002/08/01 16:01:46  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.4.2.4  2002/07/31 19:13:48  ssingh
 * LOG: Changes done to support ANSI95 related new params.
 * LOG:
 * LOG: Revision 1.4.2.3  2002/07/06 06:16:21  hbalimid
 * LOG: Took care of all the warnings.
 * LOG:
 * LOG: Revision 1.4.2.2  2002/07/03 20:13:31  ssharma
 * LOG: Bug fix for unrecognized param.
 * LOG:
 * LOG: Revision 1.4  2002/06/23 23:27:27  hbalimid
 * LOG: ITU97 specific parameters in Place.
 * LOG:
 * LOG: Revision 1.3  2002/06/18 20:23:08  sjaddu
 * LOG: Added mtp3 label case for ANSI.
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:49  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/04/06 22:43:30  ssharma
 * LOG: reorganized and added files for xml based ISUP Functional test
 * LOG:
 * LOG: Revision 1.2  2002/02/05 20:19:53  ssharma
 * LOG: IntelliNet ISUP stack test directory.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/29 20:32:12  ssharma
 * LOG: Functional test for IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/23 18:14:44  ssharma
 * LOG: Interactive functional test for IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:08  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 1.3  2001/02/05 23:10:58  hxing
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 1.2  2001/02/05 16:06:16  hxing
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 1.1  2000/12/11 23:14:38  hxing
 * LOG: Add testing files
 * LOG:
 * LOG: Revision 3.2  2000/10/12 14:29:17  labuser
 * LOG: Core dump problem fixed
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:11:13  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.7  2000/08/01 19:52:11  hxing
 * LOG: Continue testing
 * LOG:
 * LOG: Revision 1.6  2000/07/31 21:39:16  hxing
 * LOG: Testing more ies and more messages
 * LOG:
 * LOG: Revision 1.5  2000/07/28 15:04:42  hxing
 * LOG: Testing
 * LOG:
 * LOG: Revision 1.4  2000/07/27 23:00:19  hxing
 * LOG: Testing with more optional IEs
 * LOG:
 * LOG: Revision 1.3  2000/07/24 21:24:07  hxing
 * LOG: Fix bug with ie translation
 * LOG:
 * LOG: Revision 1.2  2000/07/21 19:16:08  hxing
 * LOG: Type of transaction_id is changed to ITS_OCTET[4] from ITS_UINT
 * LOG:
 * LOG: Revision 1.1  2000/07/12 16:13:35  hxing
 * LOG: Reuse part of what cbascon did for Newnet to test the NMS(ISUP) vendor
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include <its.h>
#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#include "readISUPMsg.h"

int GetSPNumber();
int SetSPNumber(int num);

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function calculates the number of octets required to store
 *      a number of digits.
 *      
 *  Input Parameters:
 *      nDigits - number of digits
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Number of octets needed for number of digits.
 *      -1 if an error occured.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
NumOfOctets4Digits(ITS_OCTET nDigits)
{
    if ((int)nDigits % 2 == 0)
    {
        return (int)nDigits / 2;
    }
    else
    {
        return (int)nDigits / 2 + 1;
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will get a string of octets from strtok and save the
 *      octets in an ITS_OCTET array.
 *      
 *  Input Parameters:
 *      nOctets - number of octets to get from strtok
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      array - pointer to an ITS_OCTET array to store octets read from strtok
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if 
 *      Any other return code indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
GetOctetsFromStr(ITS_OCTET *array, int nOctets)
{
    int i;

    /* TODO: error check rtrieval of tokens */
    for (i = 0; i < nOctets; ++i)
    {
        array[i] = (ITS_OCTET) strtol(strtok(NULL, " \t"), NULL, BASE_16);
    }
    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will get a token from strtok and convert it to an
 *      ITS_UINT.
 *
 *  Input Parameters:
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The ITS_UINT value of the token taken from strtok.
 *      Error code from failure of strtol or strtok.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_UINT
GetUIntFromStrToken()
{
    return (ITS_UINT) strtol(strtok(NULL, " \t"), NULL, BASE_16);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will get a token from strtok and convert it to an
 *      ITS_USHORT.
 *      
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The ITS_USHORT value of the token taken from strtok.
 *      Error code from failure of strtol or strtok.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_USHORT
GetUShortFromStrToken()
{
    return (ITS_USHORT) strtol(strtok(NULL, " \t"), NULL, BASE_16);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function retrieves AccessTransport parameter data from strtok.
 *      The data is then stored in an ITS_ISUP_IE structure.
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadMessageInPAMPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    ie->param_id = ISUP_PRM_MSG_IN_PAM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if (ie->param_length != plen)
    {
        printf("ReadISUPMsg: msgTypeInPAM plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.msgTypeInPAM), plen);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function retrieves AccessTransport parameter data from strtok.
 *      The data is then stored in an ITS_ISUP_IE structure.
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int ReadAccessDeliveryInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    /* Set IE information */
    ie->param_id = ISUP_PRM_ACCESS_DELIVERY_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if (ie->param_length != plen)
    {
        printf("ReadISUPMsg: AccessDeliveryInformation plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.accessDeliveryInfo.info), plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function retrieves AccessTransport parameter data from strtok.
 *      The data is then stored in an ITS_ISUP_IE structure.
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadAccessTransportPar(char *buf, ITS_ISUP_IE *ie)
{
    ie->param_id = ISUP_PRM_ACCESS_TRANSPORT;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);
    GetOctetsFromStr(&(ie->param_data.accessTransport.acc_transport[0]),
                     (int)ie->param_length);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function retrieves AutomaticCongestionLevel parameter data from
 *      strtok. The data is then stored in an ITS_ISUP_IE structure.
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadAutoCongestionLvlPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;            /* ANSI & CCITT param len = 1 octet */

    ie->param_id = ISUP_PRM_AUTO_CONGEST_LEVEL;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: AutomaticCongestionLevel, plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.autoCongestionLevel.level), plen);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadBackwardCallIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;              /* ANSI & CCITT param len = 2 */

    ie->param_id = ISUP_PRM_BKWD_CALL_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* Check for valid number of octets */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: BackwardCallIndicator plen != %d \n", plen);
        ret = !ITS_SUCCESS; 
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.backwardCallIndicators.bkwd_ci[0]),
                         (int)ie->param_length);
    }

    return ret; 
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This parameter is present in ANSI only.
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadBusinessGrpPar(char *buf, ITS_ISUP_IE *ie)
{
    int        fieldOctLenBusGrpId = 3;
    int        fieldOctLenSubGrpId = 2;
    ITS_OCTET  nOctBusGrpId = 0x00;
    ITS_OCTET  nOctSubGrpId = 0x00;
    
    ie->param_id = ISUP_PRM_BUSINESS_GROUP;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.businessGroup.party_selector), 1);
    GetOctetsFromStr(&nOctBusGrpId, 1);

    if ((int)nOctBusGrpId != fieldOctLenBusGrpId)
    {
        printf("ReadISUPMsg: BusinessGroup, GroupId field len != %d \n",
               fieldOctLenBusGrpId);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.businessGroup.business_group_ident[0]), 
                     (int)nOctBusGrpId);

    /* sub-group identifier */
    GetOctetsFromStr(&nOctSubGrpId, 1);      /* sub group ident, no. octets */

    /* check for correct data length */
    if ((int)nOctSubGrpId != fieldOctLenSubGrpId)
    {
        printf("ReadISUPMsg: BusinessGroup, SubGroupId field len != %d \n",
               fieldOctLenSubGrpId);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.businessGroup.sub_group_ident[0]), 
                     (int)nOctSubGrpId);

    /* line privileges */
    GetOctetsFromStr(&(ie->param_data.businessGroup.line_privileges), 1);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadCallDiversionInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;                   /* param len = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_CALL_DIVERSION_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: CallDiversionInformation plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.callDiversionInfo.div_info), plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadCalledPartyNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int        nOctets = 0;
    ITS_OCTET  nDigits = 0x00;

    /* Set IE information */
    ie->param_id = ISUP_PRM_CALLED_PARTY_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.calledPartyNum.addr_ind), 1);
    GetOctetsFromStr(&(ie->param_data.calledPartyNum.num_plan), 1);

    /* read in no. of digits */
    GetOctetsFromStr(&nDigits, 1);          
    nOctets = NumOfOctets4Digits(nDigits);

    GetOctetsFromStr(&(ie->param_data.calledPartyNum.dgts[0]), nOctets);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadCallHistoryInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;

    /* Set IE information */
    ie->param_id = ISUP_PRM_CALL_HISTORY_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: CallHistoryInformation maxplen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.callHistoryInfo.prop_delay[0]),
                         plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadCallReferencePar(char *buf, ITS_ISUP_IE *ie)
{
    int        ciLen = 3;
    int        pcLen = 0;
    ITS_OCTET  ci_nOctet = 0x00;
    ITS_OCTET  pc_nOctet = 0x00;

    /* Set IE information */
    ie->param_id = ISUP_PRM_CALL_REF;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* call identity */
    GetOctetsFromStr(&ci_nOctet, 1);

    /* Check if valid no. of octets for call identity field */
    if (ci_nOctet != ciLen)
    {
        printf("ReadISUPMsg: CallReference: CallIdentity field != %d octets",
               ciLen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.callRef.call_ident[0]), (int)ci_nOctet);

#if defined(CCITT)
    pcLen = 2;
#endif
#if defined(ANSI)
    pcLen = 3;
#endif

    /* point code */
    GetOctetsFromStr(&pc_nOctet, 1);
    if (pc_nOctet != pcLen)
    {
        printf("ReadISUPMsg: Point code octet length != %d", pcLen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.callRef.point_code.data[0]), (int)pc_nOctet);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadCallingPartyCategoryPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;             /* ANSI & CCITT param len = 1 octet */

    ie->param_id = ISUP_PRM_CALLING_PARTY_CATEGORY;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* Check for valid number of octets */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: CallingPartyCategory plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.callingPartyCategory.cat),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadCallingPartyNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        nOctets = 0;
    ITS_OCTET  nDigits = 0x00;

    ie->param_id = ISUP_PRM_CALLING_PARTY_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.callingPartyNum.addr_ind), 1);
    GetOctetsFromStr(&(ie->param_data.callingPartyNum.subfields4), 1);

    /* read in no. of digits */
    GetOctetsFromStr(&nDigits, 1);
    nOctets = NumOfOctets4Digits(nDigits);

    /* Check for valid number of octets */
    if (nOctets > MAX_NB_OCTETS_DIGITS)
    {
        printf("ReadISUPMsg: CallingPartyNumber: no. of digits octets > %d \n",
               MAX_NB_OCTETS_DIGITS);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.callingPartyNum.dgts[0]), nOctets);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This parameter is present in ANSI only.
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadCarrierIdPar(char *buf, ITS_ISUP_IE *ie)
{
    int maxplen = 3;       /* length of parameter in octets */
    
    /* Set IE information */
    ie->param_id = ISUP_PRM_CARRIER_ID;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct data length */
    if ((int)ie->param_length != maxplen)
    {
        printf("ReadISUPMsg: CarrierId plen > %d \n", maxplen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.carrierIdentification.network), 1);
    GetOctetsFromStr(&(ie->param_data.carrierIdentification.digit2and1), 1);
    GetOctetsFromStr(&(ie->param_data.carrierIdentification.digit4and3), 1);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This parameter is valid in ANSI only.
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadCarrierSelectionInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int maxplen = 1;       /* parameter length = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_CARRIER_SELECTION_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct parameter length */
    if ((int)ie->param_length != maxplen)
    {
        printf("ReadISUPMsg: CarrierSelectionInfo plen > %d \n", maxplen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.carrierSelectionInfo.information),
                     (int)ie->param_length);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadCauseIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        cvlen = 1;
    int        s4len = 1;
    ITS_OCTET  nDiagnostics = 0x00;

    /* Set IE information */
    ie->param_id = ISUP_PRM_CAUSE_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.causeIndicator.subfields4), s4len);
    GetOctetsFromStr(&(ie->param_data.causeIndicator.cause_val), cvlen);

    if ((int)ie->param_length > (cvlen + s4len))
    {
        GetOctetsFromStr(&nDiagnostics, 1);
        GetOctetsFromStr(&(ie->param_data.causeIndicator.diagnostics[0]), 
                         (int)nDiagnostics);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadChargeNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int        nOctDigits = 0;             /* no. octets for digits */
    ITS_OCTET  nDigits = 0;          /* number of digits */

    /* Set IE information */
    ie->param_id = ISUP_PRM_CHARGE_NUMBER;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.chargeNumber.addr_ind), 1);
    GetOctetsFromStr(&(ie->param_data.chargeNumber.num_plan), 1);

    /* Calculate number of octets used for digits */
    GetOctetsFromStr(&nDigits, 1);  /* get no. of digits */
    nOctDigits = NumOfOctets4Digits(nDigits);
    GetOctetsFromStr(&(ie->param_data.chargeNumber.dgts[0]), nOctDigits);

    return ITS_SUCCESS;
}
#endif /* ANSI */

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadCircuitGrpCharIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int maxplen = 1;

    /* Set IE information */
    ie->param_id = ISUP_PRM_CKT_GRP_CHARACTERISTIC;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != maxplen)
    {
        printf("ReadISUPMsg: CircuitGroupCharacteristicIndicator plen != %d \n",
               maxplen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.circuitGrpCharacteristic.indicator),
                     maxplen);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadCircuitGrpSupervisionMsgTypIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;             /* param len = 1 octet */

    ie->param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: CircuitGroupSupervisionMsgTypeInd plen != %d \n",
               plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.supervisionMsgType.sup_mt),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadCircuitIdNamePar(char *buf, ITS_ISUP_IE *ie)
{
    int        maxTrunkNumLen = 4;
    int        maxCLLILen = 11;
    ITS_OCTET  tnLen = 0x00;
    ITS_OCTET  clliLen = 0x00;

    /* Set IE information */
    ie->param_id = ISUP_PRM_CKT_IDENTIFICATION_NAME;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&tnLen, 1);
    if ((int)tnLen != maxTrunkNumLen)
    {
        printf("ReadISUPMsg: CircuitIdentificationName trunkNumDigits != %d \n",
               maxTrunkNumLen);
        return !ITS_SUCCESS;
    }
 
    GetOctetsFromStr(&(ie->param_data.circuitIdName.trunkNum[0]),
                     maxTrunkNumLen);

    /* office A */
    GetOctetsFromStr(&clliLen, 1);
    if ((int)clliLen != maxCLLILen)
    {
        printf("ReadISUPMsg: CircuitIdentificationName officeA len != %d \n",
               maxTrunkNumLen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.circuitIdName.clliCode_officeA[0]),
                     maxCLLILen);
 
    /* office Z */
    GetOctetsFromStr(&(ie->param_data.circuitIdName.clliCode_officeZ[0]),
                     maxCLLILen);
 
    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadCircuitStateIndPar(char *buf, ITS_ISUP_IE *ie)
{
    /* Set IE information */
    ie->param_id = ISUP_PRM_CKT_STATE_INDICATOR;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.circuitStateIndicators.states[0]),
                     (int)ie->param_length);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadCircuitValRespIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int maxplen = 1;       /* parameter length = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_CKT_VALIDATION_RESP;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct parameter length */
    if ((int)ie->param_length != 1)
    {
        printf("ReadISUPMsg: CircuitValidationResponseIndicator plen != %d \n",
               maxplen); 
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.circuitValidationResponse.indicator), 
                     maxplen);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadCLLICodePar(char *buf, ITS_ISUP_IE *ie)
{
    int maxTownOctets = 4;
    int maxStateOctets = 2;
    int maxBuildingOctets = 2;
    int maxBuildingSubdivOctets = 3;

    /* Set IE information */
    ie->param_id = ISUP_PRM_CLLI_CODE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.clliCode.town[0]), maxTownOctets);
    GetOctetsFromStr(&(ie->param_data.clliCode.state[0]), maxStateOctets);
    GetOctetsFromStr(&(ie->param_data.clliCode.building[0]), maxBuildingOctets);
    GetOctetsFromStr(&(ie->param_data.clliCode.buildingSubdiv[0]),
                     maxBuildingSubdivOctets);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadClosedUserGroupInterlockCodePar(char *buf, ITS_ISUP_IE *ie)
{
    int        dLen = 2;           /* digits len = 2 octet */
    int        cLen = 2;           /* code len   = 2 octet */
    ITS_OCTET  d_nOctets = 0x00;
    ITS_OCTET  c_nOctets = 0x00;

    ie->param_id = ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* digits */
    GetOctetsFromStr(&d_nOctets, 1);
    if ((int)d_nOctets != dLen)
    {
        printf("ReadISUPMsg: ClosedUserGroupInterlockCode digits len != %d \n",
               dLen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.interlockCode.digits[0]), dLen);

    /* code */
    GetOctetsFromStr(&c_nOctets, 1);
    if ((int)c_nOctets != cLen)
    {
        printf("ReadISUPMsg: ClosedUserGroupInterlockCode code length != %d \n",
               cLen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.interlockCode.code[0]), cLen);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadConnectedNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        nDigitsOctets = 0;
    int        ailen = 1;
    int        s4len = 1;
    ITS_OCTET  nDigits = 0x00;
    
    /* Set IE information */
    ie->param_id = ISUP_PRM_CONNECTED_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.connectedNum.addr_ind), ailen);
    GetOctetsFromStr(&(ie->param_data.connectedNum.subfields4), s4len);

    /* digits */
    GetOctetsFromStr(&nDigits, 1);  
    nDigitsOctets = NumOfOctets4Digits(nDigits);

    if (nDigitsOctets > MAX_NB_OCTETS_DIGITS)
    {
        printf("ReadISUPMsg: ConnectedNumber: no. of digits octets > %d \n",
               MAX_NB_OCTETS_DIGITS);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.connectedNum.dgts[0]), nDigitsOctets);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadConnectRequestPar(char *buf, ITS_ISUP_IE *ie)
{
    int        maxplen = 0;    /* total parameter data len */
    int        ciLen = 3;      /* call identity len */
    int        pcLen = 0;      /* point code len */
    ITS_OCTET  lenPointCode;   /* length of point code in octets */
    ITS_OCTET  lenLocalRef;    /* length of local reference in octets */
    
    /* Set IE information */
    ie->param_id = ISUP_PRM_CONNECTION_REQ;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

#ifdef CCITT
    maxplen = 7;
#endif
#ifdef ANSI
    maxplen = 8;
#endif

    if ((int)ie->param_length > maxplen || 
        (int)ie->param_length < (maxplen - 1))
    {
        printf("ReadISUPMsg: ConnectionRequest plen > %d \n", maxplen);
        return !ITS_SUCCESS;
    }

    /* local reference */
    GetOctetsFromStr(&lenLocalRef, 1);
    if ((int)lenLocalRef != ciLen)
    {
        printf("ReadISUPMsg: ConnectionRequest call identity len != %d \n",
               ciLen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.connectionRequest.call_ident[0]),
                     (int)lenLocalRef);

    /* point code */
    GetOctetsFromStr(&lenPointCode, 1);

#ifdef CCITT
    pcLen = 2;
#endif
#ifdef ANSI
    pcLen = 3;
#endif

    if ((int)lenPointCode != pcLen)
    {
        printf("ReadISUPMsg: ConnectionRequest pt code len != %d \n", pcLen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.connectionRequest.point_code.data[0]),
                     (int)lenPointCode);
    GetOctetsFromStr(&(ie->param_data.connectionRequest.protocol_class), 1);

    if((int)ie->param_length == maxplen )
    {
      if(ie->param_data.connectionRequest.protocol_class > 2)
      {
         GetOctetsFromStr(&(ie->param_data.connectionRequest.credit), 1);
      }
      else
      {
         printf("ReadISUPMsg: ConnectionRequest plen !=  %d\n", maxplen - 1);
         return !ITS_SUCCESS;
      }
   } 

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadContinuityIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;                     /* param len = 1 octet */

    ie->param_id = ISUP_PRM_CONTINUITY_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: ContinuityIndicator, plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.continuityIndicators.indicators),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadEchoControlInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;             /* param len = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_ECHO_CTRL_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: EchoControlInformation plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.echoControlInfo.info), plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadEgressServicePar(char *buf, ITS_ISUP_IE *ie)
{
    /* Set IE information */
    ie->param_id = ISUP_PRM_EGRESS_SERVICE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);
    GetOctetsFromStr(&(ie->param_data.egressService.data[0]), 
                     (int)ie->param_length);

    return ITS_SUCCESS;
}
#endif


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadEOPPar(char *buf, ITS_ISUP_IE *ie)
{
    /* Set IE information: parameter tag only */
    ie->param_id = ISUP_PRM_EOP;
    ie->param_length = 0;

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadEventInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;            /* ANSI & CCITT param len = 1 octet */

    ie->param_id = ISUP_PRM_EVENT_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: EventInformation plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.eventInfo.evt_info),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadFacilityIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;

    int plen = 1;            /* param len = 1 octet */

    ie->param_id = ISUP_PRM_FACILITY_INDICATOR;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: FacilityIndicator plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.facilityIndicator.fac_ind),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadForwardCallIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;             /* ANSI & CCITT param len = 2 octets */

    ie->param_id = ISUP_PRM_FWD_CALL_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct data length */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: ForwardCallIndicators plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.forwardCallIndicators.fwd_ci[0]),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Reserved parameter format not defined in Q.763 (03/93).
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadFreephoneIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadGenericAddrPar(char *buf, ITS_ISUP_IE *ie)
{
    int        nOctets = 0;        /* no. of octets needed to store digits */
    ITS_OCTET  nDigits = 0;  /* no. of digits */

    /* Set IE information */
    ie->param_id = ISUP_PRM_GENERIC_ADDR;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);
    
    GetOctetsFromStr(&(ie->param_data.genericAddress.type_of_addr), 1);
    GetOctetsFromStr(&(ie->param_data.genericAddress.addr_ind), 1);
    GetOctetsFromStr(&(ie->param_data.genericAddress.subfields4), 1);

    /* digits */
    GetOctetsFromStr(&nDigits, 1);
    nOctets = NumOfOctets4Digits(nDigits);
    GetOctetsFromStr(&(ie->param_data.genericAddress.dgts[0]),
                     nOctets);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadGenericDigitsPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        nOctets = 0;
    int        tslen = 1;
    int        maxNoOctets = 128;
    ITS_OCTET  nDigits;

    ie->param_id = ISUP_PRM_GENERIC_DIGITS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.genericDigits.type_scheme), tslen);

    /* digits */
    GetOctetsFromStr(&nDigits, 1);
    nOctets = NumOfOctets4Digits(nDigits);

    if ((int)nOctets > maxNoOctets)
    {
        printf("ReadISUPMsg: GenericDigits max num of octets > %d \n",
               maxNoOctets);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.genericDigits.digits[0]), nOctets);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadGenericNotificationPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    ie->param_id = ISUP_PRM_GENERIC_NOTIFICATION;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if (ie->param_length != plen)
    {
        printf("ReadISUPMsg: GenericNotification plen != %d", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.genericNotificationIndicator. \
                         indicators[0]), (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadGenericNumberPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        nOctets = 0;
    int        qlen = 1;
    int        nlen = 1;
    int        s4len = 1;
    ITS_OCTET  nDigits = 0x00;

    /* Set IE information */
    ie->param_id = ISUP_PRM_GENERIC_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.genericNumber.qualifier), qlen);
    GetOctetsFromStr(&(ie->param_data.genericNumber.nature), nlen);
    GetOctetsFromStr(&(ie->param_data.genericNumber.subfields4), s4len);
    
    /* digits */
    GetOctetsFromStr(&nDigits, 1);          /* read no. of digits */

    if ((int)nDigits > MAX_NB_OCTETS_DIGITS)
    {
        ret = !ITS_SUCCESS;
    }
    else
    {
        nOctets = NumOfOctets4Digits(nDigits);
        GetOctetsFromStr(&(ie->param_data.genericNumber.dgts[0]), nOctets);

        /*printf("\n\n----------------------------------------\n");
        printf("nDigits %d \n", nDigits);
        for(i = 0; i < nOctets; ++i)
        {
            printf("0x%02x ", ie->param_data.genericNumber.dgts[i]);
        }
        printf("\n\n----------------------------------------\n");*/
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      In Q.763 (03/93) page 29 this parameter is reserved.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadGenericReferencePar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        nOctetsToRead = 0;  /* No. of octets to be read from file */
    int        nQualOctets = 1;    /* Qualifier len = 1 octet */
    int        nLROctets = 1;      /* Length of Reference = 1 octet */
    int        maxRefOctets = 4;   /* max Reference octets */
    int        entryIndex = 0;     /* GenericReference entry index */
    ITS_OCTET  nRefOctets = 0;     /* Reference Octets */ 

    /* Set IE information */
    ie->param_id = ISUP_PRM_GENERIC_REF;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* starting count of octets to read from file */
    nOctetsToRead = (int)ie->param_length;

#if 0
    while (nOctetsToRead > 0)
    {
        nRefOctets = 0;

        /* qualifier */
        GetOctetsFromStr(&ie->param_data.genericReference. \
                         entries[entryIndex].qualifier, nQualOctets);

        /* length of reference [1, 4] inclusive */
        GetOctetsFromStr(&ie->param_data.genericReference. \
                         entries[entryIndex].refCount, nLROctets);

        /* references */
        GetOctetsFromStr(&nRefOctets, 1);

        if ((int)nRefOctets > maxRefOctets)
        {
            printf("ReadISUPMsg: GenericReference, reference len > %d \n",
                   maxRefOctets);
            return !ITS_SUCCESS;
        }

        GetOctetsFromStr(&(ie->param_data.genericReference. \
                         entries[entryIndex].refs[0]), (int)nRefOctets);

        /* Read N octets from file */
        nOctetsToRead -= nQualOctets - nLROctets - (int)nRefOctets;

        ++entryIndex;

        /* Check if all octets are present in file */
        if (nOctetsToRead < 0)
        {
            printf("ReadISUPMsg: GenericReference, missing data in file \n");
            ret = !ITS_SUCCESS;
        }
    }
#endif

        nRefOctets = 0;

        /* qualifier */
        GetOctetsFromStr(&ie->param_data.genericReference.entries[entryIndex].qualifier,
            nQualOctets);

        /* length of reference [1, 4] inclusive */
        GetOctetsFromStr(&ie->param_data.genericReference.entries[entryIndex].refCount,
            nLROctets);

        /* references */
        GetOctetsFromStr(&(ie->param_data.genericReference.entries[entryIndex].refs[0]),
            (int)ie->param_data.genericReference.entries[entryIndex].refCount);

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      In Q.763 (03/93) this parameter is reserved.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadHopCounterPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;

    printf("\n");
    printf("ReadISUPMsg: HopCounter reserved param not read. \n");

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadInfoIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;                  /* ANSI & CCITT param len = 2 octets */

    ie->param_id = ISUP_PRM_INFO_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: InformationIndicator plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.informationIndicators.indics[0]),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadInfoReqIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;           /* ANSI & CCITT param len = 2 octets */

    ie->param_id = ISUP_PRM_INFO_REQ_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: InformationRequestIndicator plen != %d \n",
               plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.informationRequestIndicators. \
                         indics[0]), (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadJurisdictionInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int maxplen = 3;       /* parameter length = 3 octets */

    /* Set IE information */
    ie->param_id = ISUP_PRM_JURISDICTION;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct data size */
    if ((int)ie->param_length != maxplen)
    {
        printf("ReadISUPMsg: Jurisdiction plen > %d \n", maxplen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.jurisdiction.digits[0]),
                     (int)ie->param_length);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadLocationNumberPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        nOctets = 0;
    int        nAddrIndOctets = 1;
    int        nSubfielsOctets = 1;
    ITS_OCTET  nDigits = 0x00;

    ie->param_id = ISUP_PRM_LOCATION_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.locationNumber.addr_ind),
                     nAddrIndOctets);
    GetOctetsFromStr(&(ie->param_data.locationNumber.subfields4),
                     nSubfielsOctets);

    /* digits */
    GetOctetsFromStr(&nDigits, 1);
    nOctets = NumOfOctets4Digits(nDigits);

    if ((int)nOctets > MAX_NB_OCTETS_DIGITS)
    {
        printf("ReadISUPMsg: LocationNumber no. of octets for digits > %d \n",
               MAX_NB_OCTETS_DIGITS);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.locationNumber.dgts[0]), nOctets);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int ReadMCIDRequestIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;                   /* param len = 1 octets */

    ie->param_id = ISUP_PRM_MCID_REQ_INDICATOR;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: MCIDRequestIndicator plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.mcidRequestIndicators.indics),
                         (int)ie->param_length);
    }

    return ret;

}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int ReadMCIDResponseIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;                   /* param len = 1 octets */

    ie->param_id = ISUP_PRM_MCID_RESP_INDICATOR;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: MCIDResponseIndicator plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.mcidResponseIndicators.indics),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadMessageCompInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 128;                   /* max param len = 128 octets */

    ie->param_id = ISUP_PRM_MSG_COMPAT_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length > plen)
    {
        printf("ReadISUPMsg: plen > %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.msgCompatibilityInfo.data[0]),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadMLPPPrecedencePar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int maxplen = 6;        /* max param len */
    int nLFBOctets = 1;
    int nNIOctets = 2;
    int nDomainOctets = 3;

    ie->param_id = ISUP_PRM_MLPP_PRECEDENCE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != maxplen)
    {
        printf("ReadISUPMsg: MLPPPrecedence plen != %d \n", maxplen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.mlppPrecedence.lfbLevel), nLFBOctets);
        GetOctetsFromStr(&(ie->param_data.mlppPrecedence.ni[0]), nNIOctets);
        GetOctetsFromStr(&(ie->param_data.mlppPrecedence.domain[0]),
                         nDomainOctets);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadNatureOfConnectionIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;       /* ANSI & CCITT parameter length = 1 octet */

    ie->param_id = ISUP_PRM_NATURE_CONN_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: NatureOfConnection plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.connectionIndicator.subfields4),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadNetworkSpecificFacilityPar(char *buf, ITS_ISUP_IE *ie)
{
    int        lenNetwId = 0;
    int        maxNoNetwId = 12;
    int        maxNoNetwFacility = 128;
    ITS_OCTET  nNetwFacility = 0x00;

    ie->param_id = ISUP_PRM_NTWK_SPECIFIC_FACILITIES;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if (ie->param_length == 0)
    {
        return ITS_SUCCESS;
    }

    /* Length of Network Id */
    GetOctetsFromStr(&(ie->param_data.networkSpecificFacility. \
                       length_ofNtwrkId), 1);

    lenNetwId = (int)ie->param_data.networkSpecificFacility.length_ofNtwrkId;

    if (lenNetwId >= 1)
    {
    /* 1a) network type plan */
        GetOctetsFromStr(&(ie->param_data.networkSpecificFacility. \
                           ntwrk_type_plan), 1);

        /* 1b - 1m) network id */
    if ((int)lenNetwId > maxNoNetwId)
        {
            printf("ReadISUPMsg: No. of network ids > %d \n", maxNoNetwId);
            return !ITS_SUCCESS;
        }

    GetOctetsFromStr(&(ie->param_data.networkSpecificFacility. \
                           ntwrk_id[0]), (int)lenNetwId);
    }

    /* network facility */
    GetOctetsFromStr(&nNetwFacility, 1);

    if ((int)nNetwFacility > maxNoNetwFacility)
    {
        printf("ReadISUPMsg: NetworkSpecificFacility no. of facility > %d \n",
                maxNoNetwFacility);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.networkSpecificFacility. \
                       ntwrk_facility[0]), (int)nNetwFacility);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadNetworkTransportPar(char *buf, ITS_ISUP_IE *ie)
{
    int octMultiple = 3;
    int maxplen = 10;

    /* Set IE information */
    ie->param_id = ISUP_PRM_NTWK_TRANSPORT;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /*
     * Check if no. of octets is a multiple of 3
     * Each parameter has 3 octets
     * octet 1: Name of ISDN User Part
     *       2: Length indicator of parameter N
     *       3: Contents of parameter N
     */
    if (((int)ie->param_length % octMultiple) != 0)
    {
        printf("ReadISUPMsg: NetworkTransport plen > %d \n", maxplen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.networkTransport.data[0]),
                     (int)ie->param_length);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadNotificationIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int maxplen = 1;       /* parameter length = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_NOTIFICATION;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct data size */
    if ((int)ie->param_length != maxplen)
    {
        printf("ReadISUPMsg: NotificationIndicator plen > %d \n", maxplen);
        return !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.notification.indicator),
                     (int)ie->param_length);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadOptBackwardCallIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;             /* param len = 1 octet */

    ie->param_id = ISUP_PRM_OPT_BKWD_CALL_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: OptionalBackwardCallIndicator plen != %d \n",
               plen);
        ret = !ITS_SUCCESS;
    }
    else 
    {
        GetOctetsFromStr(&(ie->param_data.optBkwdCallIndicators.obkwd_ind),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadOptionalForwardCallIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;           /* param len = 1 octet */

    ie->param_id = ISUP_PRM_OPT_FWD_CALL_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: OptionalForwardCallIndicator plen != %d \n",
               plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.optFwdCallIndicators.indics),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadOrigCalledNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int        nOctets = 0;    /* no. of octets needed for no. of digits */
    int        ailen = 1;
    int        s4len = 1;
    ITS_OCTET  nDigits = 0x00;
    
    ie->param_id = ISUP_PRM_ORIG_CALLED_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.origCalledNum.addr_ind), ailen);
    GetOctetsFromStr(&(ie->param_data.origCalledNum.subfields4), s4len);

    /* digits */
    GetOctetsFromStr(&nDigits, 1);
    nOctets = NumOfOctets4Digits(nDigits);
    GetOctetsFromStr(&(ie->param_data.origCalledNum.dgts[0]), nOctets);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadOrigISCPointCodePar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    ITS_OCTET  nOctets = 0x00;

    ie->param_id = ISUP_PRM_ORIG_ISC_PC;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&nOctets, 1);
    GetOctetsFromStr(&(ie->param_data.origIscPointCode.data[0]), nOctets);

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadOrigLineInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int maxplen = 1;       /* parameter length = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_ORIG_LINE_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct data size */
    if ((int)ie->param_length != maxplen)
    {
        printf("ReadISUPMsg: OriginatingLineInfo plen > %d \n", maxplen);
        return !ITS_SUCCESS;
    }
    GetOctetsFromStr(&(ie->param_data.origLineInfo.data),
                     (int)ie->param_length);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadOutgoingTrunkGrpNumPar(char *buf, ITS_ISUP_IE *ie)
{
    /* Set IE information */
    ie->param_id = ISUP_PRM_OUTGOING_TRUNK_GRP_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);
    GetOctetsFromStr(&(ie->param_data.outgoingTrunkNum.digits[0]), 
                     ie->param_length);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadParamCompInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int  i = 0;
    ITS_OCTET numInsOctets = 0;
    ITS_OCTET insIndicator = 0x00;

    ie->param_id = ISUP_PRM_PARAM_COMPAT_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&numInsOctets,1);
    ie->param_length = numInsOctets;

    i = 0;
    while( (int) numInsOctets )
    {
    
        GetOctetsFromStr(&ie->param_data.paramCompatInfo.param_info[i].paramName,1);
        numInsOctets--;

        GetOctetsFromStr(&insIndicator,1);
        numInsOctets--;

        if( insIndicator & 0x80 )
        {
            /*last octet*/
            ie->param_data.paramCompatInfo.param_info[i].instructions[0] = insIndicator;
            ie->param_data.paramCompatInfo.param_info[i].instructions[1] = 0x00;
        }
        else
        {
            /*next octet exists*/
            ie->param_data.paramCompatInfo.param_info[i].instructions[0] = insIndicator;
            GetOctetsFromStr(&ie->param_data.paramCompatInfo.param_info[i].instructions[1],1);
            numInsOctets--;
        }

        i++;

    }

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadPropagationDelayCounterPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        plen = 2;

    ie->param_id = ISUP_PRM_PROP_DELAY_COUNTER;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: PropagationDelayCounter plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.propDelayCounter.delay[0]),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadRangeAndStatusPar(char *buf, ITS_ISUP_IE *ie)
{
    int  nRangeOctets = 1;
    int  nStatusOctets = 0;

    ie->param_id = ISUP_PRM_RANGE_STATUS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.rangeAndStatus.range),
                     nRangeOctets);

    nStatusOctets = ie->param_length - nRangeOctets;
    GetOctetsFromStr(&(ie->param_data.rangeAndStatus.status[0]),
                     nStatusOctets);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadRedirectingNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int        aiLen = 1;
    int        s4Len = 1;
    int        nOctDigits = 0;
    ITS_OCTET  nDigits = 0x00;
    
    /* Set IE information */
    ie->param_id = ISUP_PRM_REDIRECTING_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.redirectingNum.addr_ind), aiLen);
    GetOctetsFromStr(&(ie->param_data.redirectingNum.subfields4), s4Len);

    /* digits */
    GetOctetsFromStr(&nDigits, 1);
    nOctDigits = NumOfOctets4Digits(nDigits);   /* no. of octets needed */
    GetOctetsFromStr(&(ie->param_data.redirectingNum.dgts[0]), nOctDigits);

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadRedirectionInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;          /* ANSI & CCITT param len = 2 octets */

    ie->param_id = ISUP_PRM_REDIRECTION_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: RedirectionInformation plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.redirectionInfo.red_info[0]),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadRedirectionNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int        aiLen = 1;
    int        npLen = 1;
    int        nOctDigits = 0;
    ITS_OCTET  nDigits = 0x00;

    ie->param_id = ISUP_PRM_REDIRECTION_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.redirectionNum.addr_ind), aiLen);
    GetOctetsFromStr(&(ie->param_data.redirectionNum.num_plan), npLen);

    GetOctetsFromStr(&nDigits, 1);
    nOctDigits = NumOfOctets4Digits(nDigits);
    GetOctetsFromStr(&(ie->param_data.redirectionNum.dgts[0]), nOctDigits);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int ReadRedirectionNumRestrictPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    ie->param_id = ISUP_PRM_REDIRECTION_NUM_RESTRICT;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: RedirectionNumberRestriction plen != %d \n",
               plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.redirectionRestriction.bits), plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadRemoteOperationsPar(char *buf, ITS_ISUP_IE *ie)
{
    int        pplen = 1;
    int        maxCompLen = 128;
    ITS_OCTET  compLen = 0x00;

    /* Set IE information */
    ie->param_id = ISUP_PRM_REMOTE_OPS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* protocol profile */
    GetOctetsFromStr(&(ie->param_data.remoteOperation.protocol_profile),
                     pplen);

    if ((int)ie->param_length > 1)
    {
        /* components */
        GetOctetsFromStr(&compLen, 1);

        if ((int)compLen > maxCompLen)
        {
            printf("ReadISUPMsg: RemoteOperations components length > %d \n",
                   maxCompLen);
            return !ITS_SUCCESS;
        }

        GetOctetsFromStr(&(ie->param_data.remoteOperation.components[0]),
                         (int)compLen);
    }

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadServiceActivationPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int maxplen = 0;

    ie->param_id = ISUP_PRM_SERVICE_ACTIVATION;
#if defined(ANSI) && !defined(ANSI_ISUP_95)
    ie->param_id = ISUP_PRM_SERVICE_ACTIVATION_ANSI92;
#endif
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

#ifdef ANSI
    maxplen = 64;
#endif
#ifdef CCITT
    maxplen = 128;
#endif

    if ((int)ie->param_length > maxplen)
    {
        printf("ReadISUPMsg: ServiceActivation plen > %d \n", maxplen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.servactivation.data[0]),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadServiceCodePar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    ie->param_id = ISUP_PRM_SERVICE_CODE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: ServiceCode plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.serviceCode.code),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadSignallingPointCodePar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;

    /* Set IE information */
    ie->param_id = ISUP_PRM_SIGNALLING_POINT_CODE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: SignallingPointCode plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.signallingPointCode.data[0]),
                         plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadSpecialProcessReqPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;           /* param len = 1 octet */

    ie->param_id = ISUP_PRM_SPECIAL_PROCESS_REQUEST;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: SpecialProcessingRequest plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.specialProcessing.data),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadSubsequentNumPar(char *buf, ITS_ISUP_IE *ie)
{
    int aiLen = 1;
    int nDigitsOctets = 0;

    ie->param_id = ISUP_PRM_SUBSEQUENT_NUM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.subsequentNum.addr_ind), aiLen);

    nDigitsOctets = (int)ie->param_length - aiLen;
    GetOctetsFromStr(&(ie->param_data.subsequentNum.dgts[0]), nDigitsOctets);

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadSuspendResumeIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;       /* param len = 1 octet */

    ie->param_id = ISUP_PRM_SUSP_RESUM_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: SuspendResumeIndicator plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.suspendResumeInd.sus_res),
                         (int)ie->param_length);
    }

    return ret;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef ANSI
int
ReadTransactionReqPar(char *buf, ITS_ISUP_IE *ie)
{
    int result = ITS_SUCCESS;

    /* Set IE information */
    ie->param_id = 0xE3;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr( &ie->param_data.transactionRequest.transaction_id[0],
                     sizeof(ie->param_data.transactionRequest.transaction_id) );
    ie->param_data.transactionRequest.SCCP_addr.len = GetUShortFromStrToken();

    if (ie->param_data.transactionRequest.SCCP_addr.len > SCCP_MAX_ADDR_LEN)
    {
        printf("ReadISUPMsg: TransactionRequest SCCP addr len > %d \n",
               SCCP_MAX_ADDR_LEN);
        result = !ITS_SUCCESS;
    }

    GetOctetsFromStr(&(ie->param_data.transactionRequest.SCCP_addr.data[0]),
                     ie->param_data.transactionRequest.SCCP_addr.len); 

    return result;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadTransitNetworkSelectionPar(char *buf, ITS_ISUP_IE *ie)
{
    int       networklen = 1;
#ifdef CCITT
    ITS_OCTET nOctNetworkId = 0x00;
#endif

/*FIXME*/
    ITS_OCTET nDigits = 0x00;

    ie->param_id = ISUP_PRM_TRANSIT_NTWK_SELECT;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    GetOctetsFromStr(&(ie->param_data.transitNetworkSelection.network),
                     networklen);

#ifdef CCITT
    GetOctetsFromStr(&nOctNetworkId, 1);
    GetOctetsFromStr(&(ie->param_data.transitNetworkSelection.network_id[0]),
                     (int)nOctNetworkId);
#endif

#ifdef ANSI
    GetOctetsFromStr(&nDigits, 1);
    GetOctetsFromStr(&(ie->param_data.transitNetworkSelection.digit2and1), 1);

    if ( (int)nDigits < 3 || (int)nDigits > 4 )
    {
        return !ITS_SUCCESS;
    }

    /* conditionally set field for digits 4 & 3 */
    if ( (int)nDigits == 4 )
    {
        GetOctetsFromStr(&(ie->param_data.transitNetworkSelection.digit4and3),
                         1);
    }

    GetOctetsFromStr(&(ie->param_data.transitNetworkSelection.code), 1);
#endif

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadTransmissionMediumRequirementPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;                /* param len = 1 octet */

    ie->param_id = ISUP_PRM_TX_MEDIUM_REQMNT;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: TransmissionMediumRequirement plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.txMediumRequirement.tmr),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadTransmissionMediumRequirementPrimePar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;                /* param len = 1 octet */

    ie->param_id = ISUP_PRM_TX_MEDIUM_REQMNT_PRIME;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: TransmissionMediumRequirementPrime plen != %d \n",
               plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.txMediumRequirementPrime.tmr),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadTransmissionMediumUsedPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    ie->param_id = ISUP_PRM_TX_MEDIUM_USED;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: TransmissionMediumUsed plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.txMediumUsed.tmr),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadUserServiceInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int        varplen = 1;

    ie->param_id = ISUP_PRM_USER_SERVICE_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ( ie->param_length >= varplen )
    {
        /* coding */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.coding), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* transfer mode */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.trans_mode), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* configuration */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.config), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* symmetry */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.symmetry), 1);
    }
    ++varplen;

#ifdef ANSI
    if ( ie->param_length >= varplen )
    {
        /* rate multiplier */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.rate_multiplier), 1);
    }
    ++varplen;
#endif

    if ( ie->param_length >= varplen )
    {
        /* layer 1 */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.layer1), 1);
    }
    ++varplen;

#ifdef ANSI
    if ( ie->param_length >= varplen )
    {
        GetOctetsFromStr(&(ie->param_data.userServiceInfo. \
                           layer1_ext_user_rate), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        GetOctetsFromStr(&(ie->param_data.userServiceInfo. \
                         layer1_ext_rate_adaption_3b), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.layer1_ext_parity),
                         1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        GetOctetsFromStr(&(ie->param_data.userServiceInfo. \
                           layer1_ext_modem_type), 1);
    }
    ++varplen;
#endif

    if ( ie->param_length >= varplen )
    {
        /* layer 2 */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.layer2), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* layer 3 */
        GetOctetsFromStr(&(ie->param_data.userServiceInfo.layer3), 1);
    }

    return ITS_SUCCESS;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadUserServiceInfoPrimePar(char *buf, ITS_ISUP_IE *ie)
{
    int varplen = 1;

    ie->param_id = ISUP_PRM_USER_SERVICE_INFO_PRIME;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ( ie->param_length >= varplen )
    {
        /* coding */
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.coding), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* transfer mode */
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.trans_mode), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* configuration */
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.config), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* symmetry */
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.symmetry), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* layer 1 */
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer1), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* layer 2 */
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer2), 1);
    }
    ++varplen;

    if ( ie->param_length >= varplen )
    {
        /* layer 3 */
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer3), 1);
    }

    return ITS_SUCCESS;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadUserTeleserviceInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;

    ie->param_id = ISUP_PRM_USER_TELESERVICE_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

/* TBD: Fix me */
#if 0
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: UserTeleserviceInformation plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.userTeleServiceInfo.subfields3),
                         s3len); 
        GetOctetsFromStr(&(ie->param_data.userTeleServiceInfo.hlayer_char_id),
                         hlcilen); 
        GetOctetsFromStr(&(ie->param_data.userTeleServiceInfo. \
                         ext_hlayer_char_id), ehlcilen); 
    }
#endif 

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadUserToUserIndPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    ie->param_id = ISUP_PRM_USER_TO_USER_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: UserToUserIndicator plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.userToUserIndicators.utu_ind),
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
int
ReadUserToUserInfoPar(char *buf, ITS_ISUP_IE *ie)
{
    int        ret = ITS_SUCCESS;
    int        maxplen = 131;         /* max param length = 131 octets */
    ITS_OCTET  nInfo = 0x00;

    ie->param_id = ISUP_PRM_USER_TO_USER_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length > maxplen)
    {
        printf("ReadISUPMsg: UserToUserInfo: param len > %d \n", maxplen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        /* protocol discriminator */
        GetOctetsFromStr(&(ie->param_data.userToUserInfo.prot_disc), 1);

        /* user-to-user info */
        GetOctetsFromStr(&nInfo, 1);
        if ((int)nInfo > maxplen - 1)
        {
            printf("ReadISUPMsg: UserToUserInfo: info len > %d \n", maxplen - 1);
            ret = !ITS_SUCCESS;
        }
        else
        {
            GetOctetsFromStr(&(ie->param_data.userToUserInfo.utu_info[0]),
                             (int)nInfo);
        }
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the CCITT routing label
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadRoutingLabelPar(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
#ifdef CCITT
    int plen = 5;
#else
    int plen = 8;
#endif

    ie->param_id = ISUP_PRM_ROUTING_LABEL;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: MTP3 Header plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr((ITS_OCTET *) (&(ie->param_data.routingLabel)),
                         (int)ie->param_length);
    }

    return ret;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Call Transfer Reference Parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT) && defined(ITU_ISUP_97)

int
ReadCallTransferReference(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;             /* param len = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_CALL_TRANSFER_REFERENCE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: CallTransferReference plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.callTransferReference.call_trans_identity), plen);
    }

    return ret;
}

#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the CCSS Parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT) && defined(ITU_ISUP_97)

int
ReadCCSS(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;             /* param len = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_CCSS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: CCSS plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.ccss.ccssInd), plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Loop Prevention Ind Parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(CCITT) && defined(ITU_ISUP_97)

int
ReadLoopPreventionInd(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;             /* param len = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_LOOP_PREVENTION_INDICATORS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: Loop Pren Ind plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.loopPreventionIndicators.loop_prev_ind), plen);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Circuit Assignment Map Parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadCircuitAssignMap(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 4;             /* param len = 1 octet */

    /* Set IE information */
    ie->param_id = ISUP_PRM_CIRCUIT_ASSIGN_MAP;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: Circuit Assignment Map plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.circuitAssignmentMap.map_type), 1);
        GetOctetsFromStr(ie->param_data.circuitAssignmentMap.map_format, plen - 1);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Generic Name parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadGenericName(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;

    /* Set IE information */
    ie->param_id = ISUP_PRM_GENERIC_NAME;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length < 1)
    {
        printf("ReadISUPMsg: Generic Name param lenght is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.genericName.pres_avail_name), 1);
        GetOctetsFromStr(ie->param_data.genericName.character,
                         (int)ie->param_length - 1);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Hop Counter parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadHopCouner(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;   

    /* Set IE information */
    ie->param_id = ISUP_PRM_HOP_CTR;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: Hope Counter param length is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.hopCounter.hop_counter), 1);
    }
    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Operator Service Info parameter
 *
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadOperatorServInfo(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;   

    /* Set IE information */
    ie->param_id = ISUP_PRM_OPERATOR_SERVICES_INFO;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: Operator service Info param length is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.operServicesInfo.type_value), 1);
    }
    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Precedence parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadPrecedence(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 6;   

    /* Set IE information */
    ie->param_id = ISUP_PRM_PRECEDENCE;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: Precedence plen != %d \n", plen);
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.precedence.lfb_level), 1);
        GetOctetsFromStr(&(ie->param_data.precedence.first_second_ni_digits), 1);
        GetOctetsFromStr(&(ie->param_data.precedence.third_fourth_ni_digits), 1);
        GetOctetsFromStr(ie->param_data.precedence.mlpp_service, plen - 3);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Remote Operations parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadRemoteOperations(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;

    /* Set IE information */
    ie->param_id = ISUP_PRM_REMOTE_OPERATIONS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length < 1)
    {
        printf("ReadISUPMsg: Precedence Param length is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.remoteOperations.protocol_profile), 1);
        GetOctetsFromStr(ie->param_data.remoteOperations.components,
                         (int)ie->param_length - 1);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the Transmission medium Used parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadTransMediumUsed(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    /* Set IE information */
    ie->param_id = ISUP_PRM_TRANSMISSION_MEDIUM_USED;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: Trans medium used  param length is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.transMediumUsed.trans_med_used), 1);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the User Service Information Prime parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadUserServInfoPrime(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 2;

    /* Set IE information */
    ie->param_id = ISUP_PRM_USER_SERVICE_INFORM_PRIME;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length < plen)
    {
        printf("ReadISUPMsg: User Serv Info Prime param lenght is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.trans_cap), 1);
        GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.trans_mode), 1);

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.config), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.symmetry), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.rate_multiplier), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.userinfo_layer1), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer1_ext_user_rate), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer1_ext_intermediate_3b), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer1_ext_header_frame_3b), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer1_ext_parity), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.layer1_ext_modem_type), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.userinfo_layer2), 1);
        }
        ++plen;

        if (ie->param_length > plen)
        {
            GetOctetsFromStr(&(ie->param_data.userServiceInfoPrime.userinfo_layer3), 1);
        }
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the User to user indicators parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadUserToUserIndicators(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;
    int plen = 1;

    /* Set IE information */
    ie->param_id = ISUP_PRM_USER_TO_USER_INDS;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length != plen)
    {
        printf("ReadISUPMsg: User To User Indicators length is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(&(ie->param_data.userToUserInd.indicator), 1);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads the User to user information parameter
 *      
 *  Input Parameters:
 *      buf - string read from a file containing parameter data
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if the parameter is stored in the IE successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI) && defined(ANSI_ISUP_95)

int
ReadUserToUserInfo(char *buf, ITS_ISUP_IE *ie)
{
    int ret = ITS_SUCCESS;

    /* Set IE information */
    ie->param_id = ISUP_PRM_USER_TO_USER_INFORM;
    ie->param_length = (ITS_OCTET)strtol(strtok(buf, " \t"), NULL, BASE_16);

    /* check for correct length of parameter */
    if ((int)ie->param_length < 1)
    {
        printf("ReadISUPMsg: User to User Info param length is not correct \n");
        ret = !ITS_SUCCESS;
    }
    else
    {
        GetOctetsFromStr(ie->param_data.userToUserInfo.userinfo,
                         (int)ie->param_length);
    }

    return ret;
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function reads an ISUP message from a file and stores the
 *      information in an array of ITS_ISUP_IE.
 *      
 *  Input Parameters:
 *      isupMsgType - ISUP message code
 *      filename - pointer to name of file to search for the ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ie - pointer to the first member an information element structure
 *      ieCount - number of parameters in current message being read
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is read successfully.
 *      Any other return code indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ReadISUPMsg(ITS_OCTET isupMsgType, char *filename, ITS_ISUP_IE *ie,
            int *no_of_ies)
{
    int        ieIndex = -1;
    int        parCode = 0;
    int        nFields = 0;
    char       *p = NULL, typeOfInfo;
    FILE       *fp = NULL;
    ITS_OCTET  mType = 0;
    char       buf[1024];
    char       unrecognizedParam = 0;

    memset(buf, 1024, 0);

    printf("ReadISUPMsg: start ReadISUPMsg(). \n");

    *no_of_ies = 0;           /* no. of IEs */

    fp = fopen( filename, "r" );

    if ( fp )
    {
        printf("ReadISUPMsg: %s opened. \n", filename);
    }
    else
    {
        printf("ReadISUPMsg: Failed to open %s. \n", filename);
        return !ITS_SUCCESS;
    }

    do
    {
        fgets(buf, 110, fp);

        if (feof(fp))
        {
            printf("ReadISUPMsg: eof reached.\n");
            fclose(fp);
            return !ITS_SUCCESS;
        }

        if (buf[0] == 'M')
        {
            p = (char *)strtok( buf, " \t" );
            mType = (ITS_OCTET) strtol(strtok(NULL, " \t"), (char **)0, 16);
            /*printf("Msg Type = %d\n", mType);*/
        }
    } while (mType != isupMsgType);

    printf("ReadISUPMsg: Found message data.\n"); 
    while ( !feof(fp) )
    {
        /* Read info type and parameter code */
        nFields = fscanf(fp, "%c\t%x\t", &typeOfInfo, &parCode);

        if (nFields != 2)
            break;
        if ( (typeOfInfo == 'P') || (typeOfInfo == 'p') )
        {
            /* do nothing .... fall through */
        }
        else
        {
            break;
        }

            /* do nothing .... fall through */
        /* Read in 100 characters */
        fgets(buf, 100, fp);

        if (!unrecognizedParam)
            ++ieIndex;
        else
            unrecognizedParam = 0;

        /*printf("ReadISUPMsg: parCode = 0x%02x\t%s\n", parCode,paramArray[parCode]);*/
        switch ( parCode )
        {
        case ISUP_PRM_ROUTING_LABEL:
            /* includes SIO and MTP3 Routing Label */
            ReadRoutingLabelPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_MSG_IN_PAM:
            ReadMessageInPAMPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_ACCESS_TRANSPORT:
            ReadAccessTransportPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_AUTO_CONGEST_LEVEL:
            ReadAutoCongestionLvlPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_BKWD_CALL_INDICATORS:
            ReadBackwardCallIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CALLED_PARTY_NUM:
            ReadCalledPartyNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CALLING_PARTY_CATEGORY:
            ReadCallingPartyCategoryPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CALLING_PARTY_NUM:
            ReadCallingPartyNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CALL_REF:
            ReadCallReferencePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CAUSE_INDICATORS:
            ReadCauseIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CKT_STATE_INDICATOR:
            ReadCircuitStateIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CKT_GRP_SUPRVN_MT_IND:
            ReadCircuitGrpSupervisionMsgTypIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CONNECTION_REQ:
            ReadConnectRequestPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CONTINUITY_INDICATORS:
            ReadContinuityIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_EOP:
            ReadEOPPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_EVENT_INFO:
            ReadEventInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_FWD_CALL_INDICATORS:
            ReadForwardCallIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_INFO_INDICATORS:
            ReadInfoIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_INFO_REQ_INDICATORS:
            ReadInfoReqIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_GENERIC_DIGITS:
            ReadGenericDigitsPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_NATURE_CONN_INDICATORS:
            ReadNatureOfConnectionIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_OPT_BKWD_CALL_INDICATORS:
            ReadOptBackwardCallIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_ORIG_CALLED_NUM:
            ReadOrigCalledNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_RANGE_STATUS:
            ReadRangeAndStatusPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_REDIRECTING_NUM:
            ReadRedirectingNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_REDIRECTION_INFO:
            ReadRedirectionInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_SERVICE_ACTIVATION:
#if defined(ANSI) && !defined(ANSI_ISUP_95)
        case ISUP_PRM_SERVICE_ACTIVATION_ANSI92:
#endif
            ReadServiceActivationPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_SUSP_RESUM_INDICATORS:
            ReadSuspendResumeIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_TRANSIT_NTWK_SELECT:
            ReadTransitNetworkSelectionPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_SERVICE_INFO:
            ReadUserServiceInfoPar(buf, &(ie[ieIndex]));
            break;

#ifdef ANSI
        case ISUP_PRM_BUSINESS_GROUP:
            ReadBusinessGrpPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CARRIER_ID:
            ReadCarrierIdPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CARRIER_SELECTION_INFO: 
            ReadCarrierSelectionInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CHARGE_NUMBER:
            ReadChargeNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CKT_GRP_CHARACTERISTIC:
            ReadCircuitGrpCharIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CKT_VALIDATION_RESP:
            ReadCircuitValRespIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CKT_IDENTIFICATION_NAME:
            ReadCircuitIdNamePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CLLI_CODE:
            ReadCLLICodePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_EGRESS_SERVICE:
            ReadEgressServicePar(buf, &(ie[ieIndex])); 
            break;

        case ISUP_PRM_GENERIC_ADDR:
            ReadGenericAddrPar(buf, &(ie[ieIndex]));
            break; 

        case ISUP_PRM_JURISDICTION: 
            ReadJurisdictionInfoPar(buf, &(ie[ieIndex]));
            break; 

        case ISUP_PRM_NOTIFICATION:
            ReadNotificationIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_NTWK_TRANSPORT:
            ReadNetworkTransportPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_ORIG_LINE_INFO:
            ReadOrigLineInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_OUTGOING_TRUNK_GRP_NUM:
            ReadOutgoingTrunkGrpNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_SERVICE_CODE:
            ReadServiceCodePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_SPECIAL_PROCESS_REQUEST:
            ReadSpecialProcessReqPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_TRANSACTION_REQUEST:
            ReadTransactionReqPar(buf, &(ie[ieIndex]));
            break;

#endif /* ANSI Prameters */

#ifdef CCITT
        case ISUP_PRM_ACCESS_DELIVERY_INFO:
            ReadAccessDeliveryInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CALL_DIVERSION_INFO:
            ReadCallDiversionInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CALL_HISTORY_INFO:
            ReadCallHistoryInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE:
            ReadClosedUserGroupInterlockCodePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CONNECTED_NUM:
            ReadConnectedNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_ECHO_CTRL_INFO:
            ReadEchoControlInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_FACILITY_INDICATOR:
            ReadFacilityIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_FREEPHONE_INDICATORS:
            ReadFreephoneIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_GENERIC_NOTIFICATION:
            ReadGenericNotificationPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_GENERIC_NUM:
            ReadGenericNumberPar(buf, &(ie[ieIndex]));

            /*printf("\n\n----------------------------------------\n");
            printf("genericNumber.digits[]: ");
            for(i = 0; i < ie[ieIndex].param_length - 3; ++i)
            {
                printf("0x%02x ", ie->param_data.genericNumber.dgts[i]);
            }
            printf("\n\n----------------------------------------\n");*/
            break;

        case ISUP_PRM_GENERIC_REF:
            ReadGenericReferencePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_HOP_COUNTER:
            ReadHopCounterPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_LOCATION_NUM:
            ReadLocationNumberPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_MCID_REQ_INDICATOR:
            ReadMCIDRequestIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_MCID_RESP_INDICATOR:
            ReadMCIDResponseIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_MSG_COMPAT_INFO:
            ReadMessageCompInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_MLPP_PRECEDENCE:
            ReadMLPPPrecedencePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_NTWK_SPECIFIC_FACILITIES:
            ReadNetworkSpecificFacilityPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_OPT_FWD_CALL_INDICATORS:
            ReadOptionalForwardCallIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_ORIG_ISC_PC:
            ReadOrigISCPointCodePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_PARAM_COMPAT_INFO:
            ReadParamCompInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_PROP_DELAY_COUNTER:
            ReadPropagationDelayCounterPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_REDIRECTION_NUM:
            ReadRedirectionNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_REDIRECTION_NUM_RESTRICT:
            ReadRedirectionNumRestrictPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_REMOTE_OPS:
            ReadRemoteOperationsPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_SIGNALLING_POINT_CODE:
            ReadSignallingPointCodePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_SUBSEQUENT_NUM:
            ReadSubsequentNumPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_TX_MEDIUM_REQMNT:
            ReadTransmissionMediumRequirementPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_TX_MEDIUM_REQMNT_PRIME:
            ReadTransmissionMediumRequirementPrimePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_TX_MEDIUM_USED:
            ReadTransmissionMediumUsedPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_SERVICE_INFO_PRIME:
            ReadUserServiceInfoPrimePar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_TELESERVICE_INFO:
            ReadUserTeleserviceInfoPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_TO_USER_INDICATORS:
            ReadUserToUserIndPar(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_TO_USER_INFO:
            ReadUserToUserInfoPar(buf, &(ie[ieIndex]));
            break;

/*
        case ISUP_PRM_PASS_THRU:
            (buf, &(ie[ieIndex]));
            break;
*/

#endif /* CCITT parameters */

#if defined(CCITT) && defined(ITU_ISUP_97)

        case ISUP_PRM_CALL_TRANSFER_REFERENCE:
            ReadCallTransferReference(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_LOOP_PREVENTION_INDICATORS:
            ReadLoopPreventionInd(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_CCSS:
            ReadCCSS(buf, &(ie[ieIndex]));
            break;

#endif /* ITU_ISUP_97 */

#if defined(ANSI) && defined(ANSI_ISUP_95)

        case ISUP_PRM_CIRCUIT_ASSIGN_MAP:
            ReadCircuitAssignMap(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_GENERIC_NAME:
            ReadGenericName(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_HOP_CTR:
            ReadHopCouner(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_OPERATOR_SERVICES_INFO:
            ReadOperatorServInfo(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_PRECEDENCE:
            ReadPrecedence(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_REMOTE_OPERATIONS:
            ReadRemoteOperations(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_TRANSMISSION_MEDIUM_USED:
            ReadTransMediumUsed(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_SERVICE_INFORM_PRIME:
            ReadUserServInfoPrime(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_TO_USER_INDS:
            ReadUserToUserIndicators(buf, &(ie[ieIndex]));
            break;

        case ISUP_PRM_USER_TO_USER_INFORM:
            ReadUserToUserInfo(buf, &(ie[ieIndex]));
            break;

#endif /* ANSI_ISUP_95 */

        default:
            printf("ReadISUPMsg: Unrecognized parameter. \n");
            unrecognizedParam = 1;
            break;
        }
    }

    /* Final IE count */
    *no_of_ies = ieIndex + 1;

    printf("ReadISUPMsg: Closing %s \n", filename);
    fclose( fp );
    return ITS_SUCCESS;
}

