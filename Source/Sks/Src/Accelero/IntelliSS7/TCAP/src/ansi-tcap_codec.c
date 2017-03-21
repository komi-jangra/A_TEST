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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *  ID: $Id: ansi-tcap_codec.c,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
 *
 *  LOG: $Log: not supported by cvs2svn $
 *  LOG: Revision 1.1.1.1  2007/10/04 13:23:56  bsccs2
 *  LOG: init tree
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 *  LOG: BscCs2
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/03/08 15:13:30  cvsadmin
 *  LOG: BSC project
 *  LOG:
 *  LOG: Revision 9.2  2005/04/08 07:39:55  adutta
 *  LOG: Fix for BCGI bug
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:52:37  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.17  2005/03/21 13:50:36  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 1.7.2.24  2003/11/25 06:09:58  ssingh
 *  LOG: Bug #649, Message received from Network with no dialogue no component
 *  LOG: should be acked with Abort.
 *  LOG:
 *  LOG: Revision 1.7.2.23  2003/09/22 05:27:46  yranade
 *  LOG: Fixes issues seen while testing with ANSI ATP.
 *  LOG:
 *  LOG: Revision 1.7.2.22  2003/06/10 11:35:00  yranade
 *  LOG: Warning removal.
 *  LOG:
 *  LOG: Revision 1.7.2.21  2003/04/16 09:16:52  vjatti
 *  LOG: Corrected National TCAP error code length check & problem code length.
 *  LOG:
 *  LOG: Revision 1.7.2.20  2003/03/30 09:11:34  vjatti
 *  LOG: Coding standerds.
 *  LOG:
 *  LOG: Revision 1.7.2.19  2003/03/28 13:03:19  vjatti
 *  LOG: Put the length checks for component portion.
 *  LOG: Fix 243-case 1
 *  LOG:
 *  LOG: Revision 1.7.2.18  2003/03/26 11:36:16  vjatti
 *  LOG: Corrected skipping of Problem code len to 1 octet.
 *  LOG:
 *  LOG: Revision 1.7.2.17  2003/03/25 14:31:46  vjatti
 *  LOG: Correct logical operation check in FindParts function.
 *  LOG:
 *  LOG: Revision 1.7.2.16  2003/03/24 09:12:10  vjatti
 *  LOG: Changes for Abort and Rejct causes.
 *  LOG:
 *  LOG: Revision 1.7.2.15  2003/03/15 10:34:33  vjatti
 *  LOG: Fix for Application Context in ParseDP.
 *  LOG: Check for Null Parameter Seq/Set.
 *  LOG:
 *  LOG: Revision 1.7.2.14  2003/03/13 12:16:38  vjatti
 *  LOG: Fix for setting the transaction portion len in extended format.
 *  LOG: Put Variant Checks for Return error when both DialogPortion and
 *  LOG: Component portion are missing.
 *  LOG:
 *  LOG: Revision 1.7.2.13  2003/03/11 13:52:06  vjatti
 *  LOG: Code enhancements
 *  LOG:
 *  LOG: Revision 1.7.2.12  2003/03/11 13:16:04  vjatti
 *  LOG: Get the null dialog portion check right
 *  LOG:
 *  LOG: Revision 1.7.2.11  2003/03/11 07:17:07  vjatti
 *  LOG: Fix for Invoke Not Last Tag
 *  LOG:
 *  LOG: Revision 1.7.2.10  2003/03/10 06:31:31  vjatti
 *  LOG: Fix for bug 238
 *  LOG:
 *  LOG: Revision 1.7.2.9  2003/03/09 12:03:13  vjatti
 *  LOG: Fix for 233/235
 *  LOG:
 *  LOG: Revision 1.7.2.8  2003/03/09 11:03:35  vjatti
 *  LOG: Fix for Bug 234
 *  LOG:
 *  LOG: Revision 1.7.2.7  2003/03/05 09:37:02  vjatti
 *  LOG: Indentation. Coding standards
 *  LOG:
 *  LOG: Revision 1.7.2.6  2003/03/05 08:53:05  vjatti
 *  LOG: Fix for Component length in conversation
 *  LOG:
 *  LOG: Revision 1.7.2.5  2003/02/28 03:40:48  vjatti
 *  LOG: Fix for Bug no 227, 228, and windows warning.
 *  LOG:
 *  LOG: Revision 1.7.2.4  2003/02/24 11:08:46  vjatti
 *  LOG: Fix for Bug 225.
 *  LOG:
 *  LOG: Revision 1.7.2.3  2003/02/19 03:26:06  vjatti
 *  LOG: Removed Extended length check for Application Context in Dialog Portion
 *  LOG:
 *  LOG: Revision 1.7.2.2  2003/02/18 05:50:57  vjatti
 *  LOG: Fix for Extended Dialogue portion length
 *  LOG:
 *  LOG: Revision 1.7.2.1  2003/02/17 15:26:46  vjatti
 *  LOG: Fix for Uni Message Encoding.
 *  LOG:
 *  LOG: Revision 1.7  2003/02/12 04:42:54  yranade
 *  LOG: Check for missing dialog and component after call to ParseDP.
 *  LOG:
 *  LOG: Revision 1.6  2003/02/07 15:04:25  yranade
 *  LOG: Removed warnings shown by gcc -Wall.
 *  LOG:
 *  LOG: Revision 1.5  2003/02/07 08:39:16  vjatti
 *  LOG: Prapagated fixes from PR 6.2
 *  LOG:
 *  LOG: Revision 1.4  2003/02/05 14:02:59  yranade
 *  LOG: Rename FindParts to TCAP_FindParts, since it's in Global Scope.
 *  LOG:
 *  LOG: Revision 1.3  2003/02/05 12:57:09  yranade
 *  LOG: Changes for Windows build.
 *  LOG:
 *  LOG: Revision 1.2  2003/02/04 10:06:30  vjatti
 *  LOG: Code cleanup and Coding standards.
 *  LOG:
 *  LOG: Revision 1.1  2003/02/04 07:19:40  yranade
 *  LOG: Manual Tcap Codec.
 *  LOG:
 *
 ****************************************************************************/
#if !defined(TANDEM)

#if defined(ANSI)
#include <ansi/tcap.h>
#endif

#else /* TANDEM */

#if defined(ANSI)
#include <ansitcap>
#endif

#endif /* TANDEM */

#if defined(ANSI)
#define PROTOCOL_VERSION_TAG                  (0xDAU)
#define AC_NAME_TAG                           (0xDCU) 
#define USER_INFO_TAG                         (0xFDU) 
#define PABT_CAUSE_TAG                        (0xD7U) 
#define TCPPN_SEQUENCE_TAG                    (0x30U)
#define TCPPN_SET_TAG                         (0xF2U)
#define U_ABORT_INFO_TAG                      (0xD8U)

static ITS_OCTET ProtocolVersion[] =
{
   0x01U   /* T1.114-1996 */
};
#endif

/*****************************************************************************
 *  Purpose:
 *      This function converts TID to Octets.
 *
 *  Input Parameters:
 *      TID t.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Data d.
 *
 *  Return Value:
 *      Returns the size of the Transaction Id.
 ****************************************************************************/
static int
TIDToData(ITS_OCTET *d, ITS_UINT t)
{
    d[0] = (t >> 24) & 0xFFU;
    d[1] = (t >> 16) & 0xFFU;
    d[2] = (t >> 8) & 0xFFU;
    d[3] = (t & 0xFFU);

    return (sizeof(ITS_UINT));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
#if defined(LOCAL_DEBUG)
static void
PrintOctets(ITS_OCTET *data, int dlen)
{
    int i = 0;
    
    printf("-----------------------\n");
    getchar();
    for (i = 0; i < dlen; i ++)
    {
        printf("%02x ", data[i]);
        if ( i % 15 == 0 && i != 0)
        {
             printf("\n");
        }
    }
    printf("\n----------------------\n");
}
#endif

/*****************************************************************************
 *  Purpose:
 *      This function encodes the ComponentPortion Octets and sets the len from
 *      a list of components.
 *
 *  Input Parameters:
 *      List of components, cpList and the total len of cptsLen.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      The ComponentPortion Octets cp and the len of the cp.
 *
 *  Return Value:
 *      Success or failure.
 ****************************************************************************/
static int
BuildCP(ITS_OCTET *cp, ITS_UINT *cpLen, ITS_OCTET *cpList, ITS_UINT cptsLen)
{
    int offset = 0;
    *cpLen = 0;

    if (cptsLen == 0)
    {
        return (ITS_SUCCESS);
    }

    /* Set the Component Portion Tag */
     cp[offset++] = CSEQ_IDENT;

     /* Set the component portion len */
     offset += TCAP_SetLength(&cp[offset], cptsLen, ITS_TRUE);
     memcpy(&cp[offset], cpList, cptsLen);

#if defined (LOCAL_DEBUG)
     printf("\nBuildCP: Components-----------------------\n");
     PrintOctets(cp, cptsLen + 2);
     printf("\nBuildCP: Components----------------------\n");
#endif

     *cpLen = cptsLen + offset;

     return (ITS_SUCCESS);
}

/*****************************************************************************
 *  Purpose:
 *      This function sets the TransactionPortion part tp, DialogPortion part dp
 *      and the ComponentPortion part cp from the data and len provided.
 *
 *  Input Parameters:
 *      Data pdup and length wlen.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      TransactionPortion tp, DialogPortion dp, ComponentPortion cp.
 *
 *  Return Value:
 *      Either PC_PARSE_OK or error value
 ****************************************************************************/
SS7DLLAPI int
TCAP_FindParts_ANSI(ITS_OCTET *pdup, int wlen,
                    ITS_OCTET **tp, ITS_OCTET **dp, ITS_OCTET **cp)
{
    ITS_UINT tag, clen;
    ITS_OCTET *pdu = pdup;

    *tp = pdup;
    *dp = NULL;
    *cp = NULL;

    /* skip tag */
    pdu += TCAP_GetTag(pdu, &tag, pdup + wlen);

    /* get total len */
    pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);

    /*
     * skip tids
     */
    if (*pdu == TID_IDENT)
    {
        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }
    else
    {
        return TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI;
    }

    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        if (*pdup == TCAP_PT_TC_UNI_ANSI)
        {
            return TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI;
        }
        else
        {
            return ITS_SUCCESS;
        }
    }
    /*
     * Dialogue portion present?
     */
    if (*pdu == DIALOG_IDENT)
    {
        *dp = pdu;

        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }
    else if (*pdu == PABT_IDENT )
    {
        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }
    else if(*pdu != U_ABORT_INFO_TAG && *pdu != CSEQ_IDENT)
    {
        return TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI;
    }
 
    if (*pdu == U_ABORT_INFO_TAG)
    {
        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }

    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        if (*pdup == TCAP_PT_TC_UNI_ANSI)
        {
            return TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI;
        }
        else
        {
            return ITS_SUCCESS;
        }
    }

    /*
     * component portion ?
     */
    if (*pdu == CSEQ_IDENT)
    {
        *cp = pdu;

        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }
    
    if ((pdu - pdup) >= wlen)
    {
        return ITS_SUCCESS;
    }
    else
    {
        return TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI;
    }
}

/*****************************************************************************
 *  Purpose:
 *      This function encodes the DialogPortion dp octets and sets the len dpLen
 *
 *  Input Parameters:
 *      ptype, applicationContext, acLen, userInformation, uiLen, accept,
 *      fromUser, causeACName, includePV.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      dp and dpLen.
 *
 *  Return Value:
 *      Success or Failure.
 *  
 *  Date : 12/12/02
 ****************************************************************************/

static ITS_BOOLEAN
BuildDP(ITS_OCTET *dp, ITS_UINT *dpLen,
        ITS_OCTET *applicationContext, ITS_USHORT acLen,
        ITS_OCTET *userInformation, ITS_USHORT uiLen,
        ITS_OCTET *security, ITS_USHORT securityLen,
        ITS_OCTET *confidentiality, ITS_USHORT confidentialityLen,
        ITS_BOOLEAN includePV)
{
     ITS_INT offset = 0;
     ITS_INT pvLen = 0;
     ITS_INT dialogLen = 0;
     *dpLen = 0;

     if (acLen == 0 && uiLen == 0 && (!includePV))
     {
         return (ITS_SUCCESS);
     }

     /* Set Dialog Portion Tag */
     dp[offset++] = DIALOG_IDENT;

     /* Skip Dialog Portion Len here */
     if (includePV) 
     {
         /* Skip PV here tag+len+PV*/
         dialogLen += 2 + (sizeof(ProtocolVersion) / sizeof(ITS_OCTET));
     }

     if(acLen)
     { 
         /* Skip AC here tag+len+acLen*/
        dialogLen += acLen; 
     }

     if (uiLen)
     {
         /* Skip UI here tag+Ext+uiLen*/
         dialogLen += uiLen;
     }
 
     offset += TCAP_SetLength(&dp[offset], dialogLen, ITS_TRUE);

     if (includePV)   /* ======Protocol Verion - Optional */
     {
         /* Set Protocol Version Tag */
         dp[offset++] = PROTOCOL_VERSION_TAG;
         /* Set Protocol Version Len */
         pvLen = sizeof(ProtocolVersion) / sizeof(ITS_OCTET);
         dp[offset++] = pvLen;
         /* Set Protocol Version */
         memcpy(&dp[offset], ProtocolVersion, pvLen);
         offset += pvLen;
     }

     if(acLen)      /* ========Application Context - Optional */
     {
         /* Copy in the Application Context applicationContext contains tag + len */
         memcpy(&dp[offset], applicationContext, acLen);
         offset += acLen;
     }

     if (uiLen)    /* ========User Info - Optional */
     {
         /* Copy in the User Info */
         memcpy(&dp[offset], userInformation, uiLen);
         offset += uiLen;
     }

     /* Set the lengths */
     dialogLen = offset - 2;
     *dpLen = offset;

     return (ITS_SUCCESS);
} 


/*****************************************************************************
 *  Purpose:
 *      Decodes the dialogPortion array of octets and fills the appContext,
 *      acLen, userInfo, uiLen, causeACName, hasPV
 *
 *  Input Parameters:
 *      dialogPortion dp and stop.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      applicationContext, acLen, userInformation, uiLen, fromUser, accept,
 *      causeACName, hasPV, isResponse.
 *
 *  Return Value:
 *      Sucess or Failure
 ****************************************************************************/
static ITS_BOOLEAN
ParseDP(ITS_OCTET* dp, ITS_OCTET *stop,
        ITS_OCTET *applicationContext, ITS_USHORT *acLen,
        ITS_OCTET *userInformation, ITS_USHORT *uiLen,
        ITS_OCTET *securityInfo, ITS_USHORT *secLen,
        ITS_OCTET *confInfo, ITS_USHORT *confLen,
        ITS_BOOLEAN *hasPV)
{
    ITS_OCTET *data, *dlgData; 
    ITS_OCTET *tmp;
    ITS_UINT len, dtag, dlen, dpLenSize;
    ITS_UINT extAcOctets;

    *acLen = 0;
    *uiLen = 0;
    *hasPV = ITS_FALSE;

    if (!dp)
    {
        /* Check it out */
        return (ITS_TRUE);
    }
    
    /* data points toDialogue portion */
    data = dp;

    /* Skip Dialogue Portion ID  */ 
    dlgData = data;

    data++;

    /* Get Dialog Len */
    dpLenSize = TCAP_GetLength(data, &dlen, stop, ITS_TRUE);
    data += dpLenSize;

    dtag = *data;
 
    /* protocol version */
    if (dtag == PROTOCOL_VERSION_TAG)
    {
        *hasPV = ITS_TRUE;
        data ++;
        data += TCAP_GetLength(data, &len, stop, ITS_TRUE);
        data += len;
    }

    if (*data == AC_NAME_TAG)
    {
        extAcOctets = 0;
        tmp = data;
        tmp ++;
        extAcOctets = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
        *acLen = len + extAcOctets + 1;
        memcpy(applicationContext, data, *acLen);
        data += *acLen;
    }

    if (*data == USER_INFO_TAG)
    {
        data ++;
        data += TCAP_GetLength(data, &len, stop, ITS_TRUE);
        *uiLen = len;
        memcpy(userInformation, data, len);
        data += len;
    }

    if ((ITS_UINT)(data - dlgData) != ( 1 + dpLenSize + dlen))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

/*****************************************************************************
 *  Purpose:
 *      Encodes TCAP_CPT to octets.
 *
 *  Input Parameters:
 *      Pointer to TCAP_CPT cpt.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Octets cp and their len cpLen.
 *
 *  Return Value:
 *      Success or Failure.
 ****************************************************************************/
SS7DLLAPI int
TCAP_CvtCPTToData_ANSI(TCAP_CPT *cpt, ITS_OCTET *cp, ITS_UINT *cpLen)
{
    ITS_UINT cptLen;
    ITS_INT offset = 0;
    ITS_INT compIdOffset = 0;
    ITS_INT tmp = 0, extOctets = 0, paramLen = 0;
    ITS_UINT paramSeqLen = 0;
    ITS_OCTET *stop;

    *cpLen = 0;

    if (!cp)
    {
       return (!ITS_SUCCESS);
    }    

    switch (cpt->ptype)
    {
    case TCPPT_TC_INVOKE:
    case TCPPT_TC_INVOKE_NL:
        cptLen = (cpt->u.invoke.invoke_id.len +
                  cpt->u.invoke.operation.len +
                  cpt->u.invoke.param.len);

        if(!cpt->u.invoke.param.len)
        {
            cptLen += 2;
        }

        if (cpt->u.invoke.correlation_id.len)
        {
            cptLen++;
        }
 
        /* Set the Component type Tag */
        cp[offset++] = (ITS_OCTET)cpt->ptype;

        /* Skip Component Type Len here */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke Ids */
        if ( cpt->u.invoke.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            cp[offset++] = TCPPN_INVOKE_TAG; 
            compIdOffset = offset;
            cp[offset++] = 1;
            cp[offset++] = cpt->u.invoke.invoke_id.data[2];
        }
        else
        {
            return (!ITS_SUCCESS);
        }
 
        /* Correlation ids if any */
        if (cpt->u.invoke.correlation_id.len != 0)
        {
            cp[compIdOffset] += 1;
            cp[offset++] = cpt->u.invoke.correlation_id.data[2];
        }

        /* Op Code Tag */
        if (cpt->u.invoke.operation.data[0] == TCPPN_OCI_NATIONAL_TCAP ||
            cpt->u.invoke.operation.data[0] == TCPPN_OCI_PRIVATE_TCAP)
        {
            /* Set OpCode Tag, Len and Value */
            memcpy(&cp[offset], cpt->u.invoke.operation.data, 4);
            offset += 4;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Parameters */
        if (cpt->u.invoke.param.len)
        {
            /* Param Tag */
            cp[offset++] = cpt->u.invoke.param.data[0];

            /* Param Len */
            tmp = cpt->u.invoke.param.len - 1;
            stop = &cpt->u.invoke.param.data[tmp];
            extOctets = TCAP_GetLength(&cpt->u.invoke.param.data[1], &paramSeqLen,
                                       stop, ITS_TRUE);
            offset += TCAP_SetLength(&cp[offset], paramSeqLen, ITS_TRUE);

            /* Parameters */
            paramLen = cpt->u.invoke.param.len - (extOctets + 1);
            memcpy(&cp[offset], &cpt->u.invoke.param.data[extOctets +1], paramLen);
            offset += paramLen;
        }
        else
        {
            cp[offset++] = TCPPN_SET_TAG;
            cp[offset++] = 0;
        }

        /* Set the Lengths */
        *cpLen = offset;
        break;

    case TCPPT_TC_RESULT_L:
    case TCPPT_TC_RESULT_NL:
        cptLen = (cpt->u.result.invoke_id.len +
                  cpt->u.result.param.len);

        if(!cpt->u.result.param.len)
        {
            cptLen += 2;
        }

        /* Set Component Type Tag */
        cp[offset++] = (ITS_OCTET)cpt->ptype;

        /* Skip Component Type Len here */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke ID TAG */
        if ( cpt->u.result.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Set Invoke Id Tag, Len and ID */
            memcpy(&cp[offset], cpt->u.result.invoke_id.data, 3);
            offset += 3;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Parameters */
        if (cpt->u.result.param.len)
        {
            /* Param Tag */
            cp[offset++] = cpt->u.result.param.data[0];

            /* Param Len */
            tmp = cpt->u.result.param.len - 1;
            stop = &cpt->u.result.param.data[tmp];
            extOctets = TCAP_GetLength(&cpt->u.result.param.data[1], &paramSeqLen,
                                       stop, ITS_TRUE);
            offset += TCAP_SetLength(&cp[offset], paramSeqLen, ITS_TRUE);

            /* Parameters */
            paramLen = cpt->u.result.param.len - (extOctets + 1);
            memcpy(&cp[offset], &cpt->u.result.param.data[extOctets +1], paramLen);
            offset += paramLen;
        }
        else
        {
            cp[offset++] = TCPPN_SET_TAG;
            cp[offset++] = 0;
        }

        /* Set the Lengths */
        *cpLen = offset;
        break;

    case TCPPT_TC_ERROR:
        cptLen = (cpt->u.error.invoke_id.len +
                  cpt->u.error.error.len +
                  cpt->u.error.param.len);

        if(!cpt->u.error.param.len)
        {
            cptLen += 2;
        }

        /* Set Component Type Tag */
        cp[offset++] = TCPPT_TC_ERROR;

        /* Skip Component Type Len here */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke ID TAG */
        if ( cpt->u.error.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Set Invoke Id Tag, Len and ID */
            memcpy(&cp[offset], cpt->u.error.invoke_id.data, 3);
            offset += 3;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Error Code Tag */
        if ( cpt->u.error.error.data[0] == TCPPN_ECI_NATIONAL_TCAP ||
             cpt->u.error.error.data[0] == TCPPN_ECI_PRIVATE_TCAP)
        {
            /* Set Error Code Tag, Length and Value */
            memcpy(&cp[offset], cpt->u.error.error.data, 3);
            offset += 3;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Parameters */
        if (cpt->u.error.param.len)
        {
            /* Param Tag */
            cp[offset++] = cpt->u.error.param.data[0];

            /* Param Len */
            tmp = cpt->u.error.param.len - 1;
            stop = &cpt->u.error.param.data[tmp];
            extOctets = TCAP_GetLength(&cpt->u.error.param.data[1], &paramSeqLen,
                                       stop, ITS_TRUE);
            offset += TCAP_SetLength(&cp[offset], paramSeqLen, ITS_TRUE);

            /* Parameters */
            paramLen = cpt->u.error.param.len - (extOctets + 1);
            memcpy(&cp[offset], &cpt->u.error.param.data[extOctets +1], paramLen);
            offset += paramLen;
        }
        else
        {
            cp[offset++] = TCPPN_SET_TAG;
            cp[offset++] = 0;
        }

        /* Set the Lengths */
        *cpLen = offset;
        break;

    case TCPPT_TC_REJECT:
        cptLen = (cpt->u.reject.invoke_id.len +
                  cpt->u.reject.problem.len +
                  cpt->u.reject.param.len);

        if(!cpt->u.reject.param.len)
        {
            cptLen += 2;
        }
         
        /* Set Component Type Tag */
        cp[offset++] = (ITS_OCTET)cpt->ptype;

        /* Skip Component Type Len here */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke ID TAG */
        if ( cpt->u.reject.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Set Invoke Id Tag, Len and ID */
            memcpy(&cp[offset], cpt->u.reject.invoke_id.data, 3);
            offset += 3;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Problem Code */
        if ( cpt->u.reject.problem.len && cpt->u.reject.problem.data[1] == 2)
        {
            /* Set the problem code tag, len and value */
            memcpy(&cp[offset], cpt->u.reject.problem.data, 4);
            offset += 4;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Parameters */
        if (cpt->u.reject.param.len)
        {
            /* Param Tag */
            cp[offset++] = cpt->u.reject.param.data[0];

            /* Param Len */
            tmp = cpt->u.reject.param.len - 1;
            stop = &cpt->u.reject.param.data[tmp];
            extOctets = TCAP_GetLength(&cpt->u.reject.param.data[1], &paramSeqLen,
                                       stop, ITS_TRUE);
            offset += TCAP_SetLength(&cp[offset], paramSeqLen, ITS_TRUE);

            /* Parameters */
            paramLen = cpt->u.reject.param.len - (extOctets + 1);
            memcpy(&cp[offset], &cpt->u.reject.param.data[extOctets +1], paramLen);
            offset += paramLen;
        }
        else
        {
            cp[offset++] = TCPPN_SET_TAG;
            cp[offset++] = 0;
        }

        /* Set the Lengths */
        *cpLen = offset;
        break;

        default:
        break;
    }
    return (ITS_SUCCESS);
}
/*****************************************************************************
 *  Purpose:
 *      Encode the message in Octets. Also see BuildDP and BuildCP
 *
 *  Input Parameters:
 *      Pointer to TCAP_DLG dlg structure, List of Components cpList, ComponentsLen
 *      cptsLen, local TID ltid, remoteTID rtid,
 *      remoteTID len rtidLen 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      TransactionPortion tp, TransactionPortionLen tpLen.
 *
 *  Return Value:
 *      Success or Failure.
 ****************************************************************************/

SS7DLLAPI int
TCAP_CvtDLGToData_ANSI(TCAP_DLG *dlg, ITS_OCTET *tp, ITS_UINT *tpLen,
                      ITS_OCTET *cpList, ITS_UINT cptsLen,
                      ITS_INT ltid, ITS_INT rtid)
{
    ITS_INT offset = 0, mlenoffset = 0, otidoffset = 0;
    ITS_INT otidlen = 0, dtidlen = 0;
    ITS_OCTET tidArr [4];
    ITS_UINT dpLen = 0;
    ITS_UINT cpLen = 0;
    int lsize=0;

    if (!dlg)
    {
        return (!ITS_SUCCESS);
    }

    if (ANSI_TCAP_Variant > ANSI_TCAP_1992)
    { 
        if ((!cptsLen) && (dlg->ptype != TCPPT_TC_ABORT))
        {
            if (dlg->u.uni.ac_name.len == 0 &&
                dlg->u.uni.user_info.len == 0 &&
                !(dlg->u.uni.qos.indicator & QOSI_PROT_VER))
            {
                /* Missing dialog Portion as well as Component Portion
                 * ANSI-Specs Figure 3/T1.114.3 Note 2
                 */
                return (ITS_EPROTERR);
            }
        }
    }

    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        /* Set Message Type Tag */
        tp[offset++] = TCPPT_TC_UNI;

        /* Mark & Skip Message Len here */
        mlenoffset = offset;
        offset++;

        /* Set TID Tag */
        tp[offset++] = TID_IDENT;
        /* Set TIDlen to zero since UNI doesn't have TIDs*/
        tp[offset++] = 0;

        /* Build Dialog Portion if any */
        BuildDP(&tp[offset], &dpLen,
                dlg->u.uni.ac_name.data,
                dlg->u.uni.ac_name.len,
                dlg->u.uni.user_info.data,
                dlg->u.uni.user_info.len,
                NULL, 0, NULL, 0,
                dlg->u.uni.qos.indicator & QOSI_PROT_VER
                     ? ITS_TRUE
                     : ITS_FALSE);
        offset += dpLen;

        /* Build Components
           mandatory in case of UNI */
        if (!cptsLen)
        {
            return (ITS_EPROTERR);
        }
        BuildCP(&tp[offset], &cpLen, cpList, cptsLen);
        if (!cpLen)
        {
            return (ITS_EPROTERR);
        }
        offset += cpLen;

        /* Set transaction portion len */
        lsize = TCAP_SetLength(NULL, (offset - mlenoffset - 1), ITS_FALSE);
        if (lsize > 1)
        {
            offset--;
            memmove(&tp[lsize + mlenoffset], &tp[mlenoffset + 1], offset - 1);
            TCAP_SetLength(&tp[mlenoffset], (offset - mlenoffset), ITS_TRUE);
            offset += lsize;
        }
        else
        {
           TCAP_SetLength(&tp[mlenoffset], (offset - 2), ITS_TRUE);
        }
        *tpLen = offset;

        break;

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        /* Set Message Type Tag */
        tp[offset++] = (ITS_OCTET)dlg->ptype ;

        /* Mark & Skip Message Len Offset */
        mlenoffset = offset;
        offset++;

        /* build the Originating transaction id */
        /* TID Tag */
        tp[offset++] = TID_IDENT;
        /* OTID Len */
        otidlen = TIDToData(tidArr, ltid);
        tp[offset++] = otidlen;
        /* OTID */
        memcpy(&tp[offset], tidArr, otidlen);
        offset += otidlen;

        /* Build Dialog Portion if any */
        BuildDP(&tp[offset], &dpLen,
                dlg->u.begin.ac_name.data,
                dlg->u.begin.ac_name.len,
                dlg->u.begin.user_info.data,
                dlg->u.begin.user_info.len,
                NULL, 0, NULL, 0,
                dlg->u.begin.qos.indicator & QOSI_PROT_VER
                     ? ITS_TRUE
                     : ITS_FALSE);
#if defined (LOCAL_DEBUG)
    printf("\n: DP-----------------------------\n");
    PrintOctets(&tp[offset], dpLen);
    printf("\n: DP-----------------------------\n");
#endif
        offset += dpLen;

        /* Build Components */
        BuildCP(&tp[offset], &cpLen, cpList, cptsLen);
        offset += cpLen;

        /* Set transaction portion len */
        lsize = TCAP_SetLength(NULL, (offset - mlenoffset - 1), ITS_FALSE);
        if (lsize > 1)
        {
            offset--;
            memmove(&tp[lsize + mlenoffset], &tp[mlenoffset + 1], offset - 1);
            TCAP_SetLength(&tp[mlenoffset], (offset - mlenoffset), ITS_TRUE);
            offset += lsize;
        }
        else
        {
            TCAP_SetLength(&tp[mlenoffset], (offset - 2), ITS_TRUE);
        }
        *tpLen = offset;

#if defined (LOCAL_DEBUG)
     printf("\n : Transaction-----------------------\n");
     PrintOctets(tp, *tpLen);
     printf("\n: Transaction----------------------\n");
#endif

        break;

    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        /* Set Message Type Tag */
        tp[offset++] = (ITS_OCTET)dlg->ptype ;

        /* Mark & Skip Message Len here */
        mlenoffset = offset;
        offset++;

        /* build the Originating transaction id */
        /* OTID Tag */
        tp[offset++] = TID_IDENT;
        /* OTID Len */
        otidlen = TIDToData(tidArr, ltid);
        otidoffset = offset;
        offset++;
        /* OTID */
        memcpy(&tp[offset], tidArr, otidlen);
        offset += otidlen;

        /* build the Destination transaction id */
        /* OTID Tag */
        /* OTID Len */
        dtidlen = TIDToData(tidArr, rtid);
        /* OTID */
        memcpy(&tp[offset], tidArr, dtidlen);
        offset += dtidlen;
        tp[otidoffset] = otidlen + dtidlen;

        /* Build Dialog Portion if any */
        BuildDP(&tp[offset], &dpLen,
                dlg->u.cont.ac_name.data,
                dlg->u.cont.ac_name.len,
                dlg->u.cont.user_info.data,
                dlg->u.cont.user_info.len,
                NULL, 0, NULL, 0,
                dlg->u.cont.qos.indicator & QOSI_PROT_VER
                     ? ITS_TRUE
                     : ITS_FALSE);
#if defined (LOCAL_DEBUG)
    printf("\n: DP-----------------------------\n");
    PrintOctets(&tp[offset], dpLen);
    printf("\n: DP-----------------------------\n");
#endif
        offset += dpLen;

        /* Build Components */
        BuildCP(&tp[offset], &cpLen, cpList, cptsLen);
        offset += cpLen;

        /* Set transaction portion len */
        lsize = TCAP_SetLength(NULL, (offset - mlenoffset - 1), ITS_FALSE);
        if (lsize > 1)
        {
            offset--;
            memmove(&tp[lsize + mlenoffset], &tp[mlenoffset + 1], offset - 1);
            TCAP_SetLength(&tp[mlenoffset], (offset - mlenoffset), ITS_TRUE);
            offset += lsize;
        }
        else
        {
            TCAP_SetLength(&tp[mlenoffset], (offset - 2), ITS_TRUE);
        }
        *tpLen = offset;

#if defined (LOCAL_DEBUG)
     printf("\n : Transaction-----------------------\n");
     PrintOctets(tp, *tpLen);
     printf("\n: Transaction----------------------\n");
#endif

        break;

    case TCPPT_TC_RESP:
        /* Set Message Type Tag */
        tp[offset++] =  TCPPT_TC_RESP;

        /* Mark & Skip Message Len here */
        mlenoffset = offset;
        offset++;

        /* build the Destination transaction id */
        /* OTID Tag */
        tp[offset++] = TID_IDENT;
        /* OTID Len */
        dtidlen = TIDToData(tidArr, rtid);
        tp[offset++] = dtidlen;
        /* DTID */
        memcpy(&tp[offset], tidArr, dtidlen);
        offset += dtidlen;

        /* Build Dialog Portion if any */
        BuildDP(&tp[offset], &dpLen,
                dlg->u.end.ac_name.data,
                dlg->u.end.ac_name.len,
                dlg->u.end.user_info.data,
                dlg->u.end.user_info.len,
                NULL, 0, NULL, 0,
                dlg->u.end.qos.indicator & QOSI_PROT_VER
                     ? ITS_TRUE
                     : ITS_FALSE);

#if defined (LOCAL_DEBUG)
    printf("\n: DP-----------------------------\n");
    PrintOctets(&tp[offset], dpLen);
    printf("\n: DP-----------------------------\n");
#endif
        offset += dpLen;

        /* Build Components */
        BuildCP(&tp[offset], &cpLen, cpList, cptsLen);
        offset += cpLen;

        /* Set transaction portion len */
        lsize = TCAP_SetLength(NULL, (offset - mlenoffset - 1), ITS_FALSE);
        if (lsize > 1)
        {
            offset--;
            memmove(&tp[lsize + mlenoffset], &tp[mlenoffset + 1], offset - 1);
            TCAP_SetLength(&tp[mlenoffset], (offset - mlenoffset), ITS_TRUE);
            offset += lsize;
        }
        else
        {
           TCAP_SetLength(&tp[mlenoffset], (offset - 2), ITS_TRUE);
        }
        *tpLen = offset;

#if defined (LOCAL_DEBUG)
     printf("\n : Transaction-----------------------\n");
     PrintOctets(tp, *tpLen);
     printf("\n: Transaction----------------------\n");
#endif
        break;

    case TCPPT_TC_ABORT:
        /* Set Message Type Tag */
        tp[offset++] =  TCPPT_TC_ABORT;

        /*Mark & Skip Messg Len here */
        mlenoffset = offset;
        offset++;

        /* build the Destination transaction id */
        /* DTID Tag */
        tp[offset++] = TID_IDENT;
        /* DTID Len */
        dtidlen = TIDToData(tidArr, rtid);
        tp[offset++] = dtidlen;
        /* DTID */
        memcpy(&tp[offset], tidArr, dtidlen);
        offset += dtidlen;

        /* Build Dialog Portion */ 
        if (dlg->u.abort.abort_reason != 0) /* P-ABORT? */
        {
            /* Set the P-Abort Cause Tag, Length and Cause */
            tp[offset++] = PABT_CAUSE_TAG;

            /* Set the P-Abort Cause Len */
            tp[offset++] = 1;

            /* Copy in the P-Abort Cause */
            tp[offset++] = (ITS_OCTET)dlg->u.abort.abort_reason;

            /* No Dialog Portion */
        }
        else /* U-ABORT */
        {
             /* dialogue portion (only in U-ABORT) */
            BuildDP(&tp[offset], &dpLen,
                    dlg->u.abort.ac_name.data,
                    dlg->u.abort.ac_name.len,
                    dlg->u.abort.user_info.data,
                    dlg->u.abort.user_info.len,
                    NULL, 0, NULL, 0,
                    dlg->u.abort.qos.indicator & QOSI_PROT_VER
                               ? ITS_TRUE
                               : ITS_FALSE);
           
            /* Skip Dialog Portion Length */
            offset += dpLen;
       
            /* Set U Abort info */
            memcpy(&tp[offset], dlg->u.abort.abort_info.data, dlg->u.abort.abort_info.len);
            offset += dlg->u.abort.abort_info.len;

        }

        /* Set transaction portion len */
        lsize = TCAP_SetLength(NULL, (offset - mlenoffset - 1), ITS_FALSE);
        if (lsize > 1)
        {
            offset--;
            memmove(&tp[lsize + mlenoffset], &tp[mlenoffset + 1], offset - 1);
            TCAP_SetLength(&tp[mlenoffset], (offset - mlenoffset), ITS_TRUE);
            offset += lsize;
        }
        else
        {
           TCAP_SetLength(&tp[mlenoffset], (offset - 2), ITS_TRUE);
        }
        *tpLen = offset;

        break;
    }
    return (ITS_SUCCESS);
}
/****************************************************************************
 *  Purpose:
 *      To build the component portion.
 *
 *  Input Parameters:
 *      ITS_OCTET*  cp
 *      ITS_UINT    cTag
 *      ITS_USHORT  cLen.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      TCAP_CPT*   cpt
 *
 *  Return Value:
 *      int
 *
 *  Revision History:
 * --------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * --------------------------------------------------------------------------
 * sbabu     04-06-2005  BCGI bug                Fix for stack not able to
 *                                               decode a TCAP UNI if the length
 *                                               of the INVOKE ID in the component
 *                                               portion is null.
 *
 ****************************************************************************/

SS7DLLAPI int
TCAP_CvtDataToCPT_ANSI(TCAP_CPT *cpt, ITS_OCTET *cp, ITS_UINT cTag, ITS_USHORT cLen)
{
    ITS_OCTET *tmp, *data, *stop;
    ITS_UINT len, opLen;
    ITS_UINT cptIdLen; 
    ITS_INT tLen = 0;

    memset(cpt, 0, sizeof(TCAP_CPT));

    if (!cp || !cLen)
    {
        return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
    }
    data = cp;
    stop = cp + cLen;

    switch (cTag)
    {
    case TCPPT_TC_INVOKE:
    case TCPPT_TC_INVOKE_NL:
        /* set the ptype */
        cpt->ptype = cTag ;

        /* get the invoke id if any */    
        if (*data == TCPPN_INVOKE_TAG && 
           (*(data + 1) == 1 || *(data + 1) == 2|| *(data + 1) == 0)) /* yes 0 is valid */
        {

            if (*(data + 1) == 0)
            {
                cpt->u.invoke.invoke_id.len = 3;
                cpt->u.invoke.invoke_id.data[0] = TCPPN_COMPONENT_ID;
                cpt->u.invoke.invoke_id.data[1] = 0;
                cpt->u.invoke.invoke_id.data[2] = 0;
                data += 2; /* skip to the opCode Id */
            }
            else  
            {
             
                cpt->u.invoke.invoke_id.len = 3;
                cpt->u.invoke.invoke_id.data[0] = TCPPN_COMPONENT_ID;
                cpt->u.invoke.invoke_id.data[1] = 1;

                /* Skip Invoke ID Tag & Len here */
                data ++;
                cptIdLen = *data;
                data++;
  
                /* get Invoke Id here */
                cpt->u.invoke.invoke_id.data[2] = *data;
                data++;
       
                if(cptIdLen == 2)
                {
                    /* get Correlation Id if any */
                    cpt->u.invoke.correlation_id.len = 3;
                    cpt->u.invoke.correlation_id.data[0] = TCPPN_COMPONENT_ID;
                    cpt->u.invoke.correlation_id.data[1] = 1;
                    cpt->u.invoke.correlation_id.data[2] = *data;
                    data ++;
                }
            }
        }         
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }

        /* get the op code */  
        if ((*data == TCPPN_OCI_NATIONAL_TCAP &&
             *(data + 1) == 2) || 
             *data == TCPPN_OCI_PRIVATE_TCAP)  
        {
            cpt->u.invoke.operation.data[0] = *data;
            data ++;
            cpt->u.invoke.operation.data[1] = *data;
            opLen = *data;
            data ++;
            memcpy(&cpt->u.invoke.operation.data[2], data, opLen);
            cpt->u.invoke.operation.len = (2 + opLen);
            data += opLen;
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }

        /* get the parameter */
        if (*data == TCPPN_SEQUENCE_TAG || *data == TCPPN_SET_TAG)
        {
            tmp = data;
            tmp ++;
            tLen = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
            tmp += tLen;
            memcpy(&cpt->u.invoke.param.data, data, tLen + len + 1);
            cpt->u.invoke.param.len = len + tLen + 1;
            data += (tLen + len + 1);
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }
        break;

    case TCPPT_TC_RESULT_NL:
    case TCPPT_TC_RESULT_L:
        /* set the ptype */
        cpt->ptype = cTag ;
        
        /* get the invoke ids if any */
        if (*data == TCPPN_INVOKE_TAG && *(data + 1) == 1)
        {
            cpt->u.result.invoke_id.len = 3;
            cpt->u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.result.invoke_id.data[1] = 1;

            /* skip Invoke ID Tag and Invoke ID Len */
            data += 2;
            cpt->u.result.invoke_id.data[2] = *data;
            data ++;
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }

        /* get the parameter */
        if (*data == TCPPN_SEQUENCE_TAG || *data == TCPPN_SET_TAG)
        {
            tmp = data;
            tmp ++;
            tLen = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
            tmp += tLen;
            memcpy(&cpt->u.result.param.data, data, tLen + len + 1);
            cpt->u.result.param.len = len + tLen + 1;
            data += (tLen + len + 1);
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }
        break;

    case TCPPT_TC_ERROR:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_ERROR;
       
        /* get the invoke ids */
        if (*data == TCPPN_INVOKE_TAG && 
            *(data + 1) == 1)
        {
            cpt->u.error.invoke_id.len = 3;
            cpt->u.error.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.error.invoke_id.data[1] = 1;
            /* skip Invoke ID Tag and Invoke ID Len */
            data += 2;
            cpt->u.error.invoke_id.data[2] = *data;
            data ++;
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }

        /* get the Error code */ 
        if ((*data == TCPPN_ECI_NATIONAL_TCAP &&
             *(data + 1) == 1) ||
             *data == TCPPN_ECI_PRIVATE_TCAP) 
        {
            cpt->u.error.error.data[0] = *data;
            data ++;
            cpt->u.error.error.data[1] = *data;
            opLen = *data;
            data ++;
            memcpy(&cpt->u.error.error.data[2], data, opLen);
            cpt->u.error.error.len = (2 + opLen);
            data += opLen;
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }

        /* get the parameter */
        if (*data == TCPPN_SEQUENCE_TAG || *data == TCPPN_SET_TAG)
        {
            tmp = data;
            tmp ++;
            tLen = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
            tmp += tLen;
            memcpy(&cpt->u.error.param.data, data, tLen + len + 1);
            cpt->u.error.param.len = len + tLen + 1;
            data += (tLen + len + 1);
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }
        break;

    case TCPPT_TC_REJECT:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_REJECT;

        /* get the invoke ids */
        if (*data == TCPPN_INVOKE_TAG)
        {
            cpt->u.reject.invoke_id.len = 3;
            cpt->u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.reject.invoke_id.data[1] = 1;
            /* skip Invoke ID Tag and Invoke ID Len */
            data += 2;
            /* Check me: memcpy ? */
            cpt->u.reject.invoke_id.data[2] = *data;
            data ++;
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }

        /* get the problem */
        if(*data == TCPPROB_IDENT && 
           *(data + 1) == 2) 
        {
            cpt->u.reject.problem.len = 4;
            cpt->u.reject.problem.data[0] = TCPPROB_IDENT;

            /* Skip problem code Identifier */
            data ++;
            cpt->u.reject.problem.data[1] = 2;

            /*Skip Problem code len here */
            data++;
            cpt->u.reject.problem.data[2] = *data; 
            data ++;
            cpt->u.reject.problem.data[3] = *data;
            data++; 
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }

        /* add in parameter */ 
        if (*data == TCPPN_SEQUENCE_TAG || *data == TCPPN_SET_TAG)
        {
            tmp = data;
            tmp ++;
            tLen = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
            tmp += tLen;
            memcpy(&cpt->u.reject.param.data, data, tLen + len + 1);
            cpt->u.reject.param.len = len + tLen + 1;
            data += (tLen + len + 1);
        }
        else
        {
            return (TCAP_PROB_SPEC_GEN_INCORRECT_COMP_ANSI);
        }
        break;

    default:

        return (TCAP_PROB_SPEC_GEN_UNREC_COMP_ANSI);
    }

    if ((data - cp) != cLen)
    {
        /* Validate the Component portion Len here */
        return (TCAP_PROB_SPEC_GEN_BADLY_STRUCT_COMP_ANSI); 
    }

    return (ITS_SUCCESS);
} 

SS7DLLAPI int
TCAP_CvtDataToDLG_ANSI(TCAP_DLG *dlg,ITS_OCTET *pType,
                       ITS_OCTET *tp, ITS_OCTET *dp, ITS_BOOLEAN cpPresent,
                       ITS_USHORT len)
{
    ITS_BOOLEAN hasPV;
    ITS_UINT tidLen, causeLen, tcapMesgLen;
    ITS_OCTET *tmp = NULL;
    ITS_UINT abortInfoLen;
    ITS_UINT tpLenSize;
    ITS_UINT tpLen;
    ITS_UINT dplen;

    memset(dlg, 0, sizeof(TCAP_DLG));

    if (tp == NULL)
    {
        return (TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI);
    }
   
    tmp = tp;

    /* Transaction Portion length validation */
    tpLenSize = TCAP_GetLength(tp + 1, &tpLen, tp + len, ITS_TRUE);

    if ((1 + tpLenSize + tpLen) != len)
    {
        return (TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI);
    }
     
    switch (*pType)
    {
    case TCPPT_TC_UNI:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_UNI;
    
        /* check for components */
        if (cpPresent)
        {
            dlg->u.uni.cpt_present = 1;
        }
 
        /* parse dialogue portion */
        if (!ParseDP(dp,
                     tp + len,
                     dlg->u.uni.ac_name.data, 
             	     &dlg->u.uni.ac_name.len,
                     dlg->u.uni.user_info.data,
                     &dlg->u.uni.user_info.len,
                     NULL, NULL, NULL, NULL,
                     &hasPV))
        {
            return (TCAP_ABT_REASON_BADLY_STRUCT_DLG_PORT_ANSI);
        }

       	if (hasPV)
        {
            dlg->u.uni.qos.indicator |= QOSI_PROT_VER;
        }

        if (!cpPresent)/* Fix for 174, 175, 188 */
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1992)
            {
                if (dlg->u.uni.ac_name.len == 0 &&
                    dlg->u.uni.user_info.len == 0 &&
                    !hasPV)
                {
                    /* Missing dialog Portion as well as Component Portion
                     * ANSI-Specs Figure 3/T1.114.3 Note 2
                     */

                    return (TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI);
                }
            }
        }
        break;

    case TCPPT_TC_QUERY_W_PERM:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_QUERY_W_PERM;
 
        /* check for components */
        if (cpPresent)
        {
            dlg->u.begin.cpt_present = 1;
        }

        /* parse dialogue portion */
        if (!ParseDP(dp,
                     tp + len,
                     dlg->u.begin.ac_name.data,
                     &dlg->u.begin.ac_name.len,
                     dlg->u.begin.user_info.data,
                     &dlg->u.begin.user_info.len,
                     NULL, NULL, NULL, NULL,
                     &hasPV))
        {
            return (TCAP_ABT_REASON_BADLY_STRUCT_DLG_PORT_ANSI);
        }

        if (hasPV)
        {
            dlg->u.begin.qos.indicator |= QOSI_PROT_VER;
        }

        if (!cpPresent) /* Fix for 174, 175, 188 */
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1992)
            {
                if (dlg->u.begin.ac_name.len == 0 &&
                    dlg->u.begin.user_info.len == 0 &&
                    !hasPV)
                {
                    /* Missing dialog Portion as well as Component Portion
                     * ANSI-Specs Figure 3/T1.114.3 Note 2
                     */

                    return (TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI);
                }
            }
        }
        break;

    case TCPPT_TC_QUERY_WO_PERM:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_QUERY_WO_PERM;

        /* check for components */
        if (cpPresent)
        {
            dlg->u.begin.cpt_present = 1;
        }

        /* parse dialogue portion */
        if (!ParseDP(dp,
                     tp + len,
                     dlg->u.begin.ac_name.data,
                     &dlg->u.begin.ac_name.len,
                     dlg->u.begin.user_info.data,
                     &dlg->u.begin.user_info.len,
                     NULL, NULL, NULL, NULL,
                     &hasPV))
        {
            return (TCAP_ABT_REASON_BADLY_STRUCT_DLG_PORT_ANSI);
        }

        if (hasPV)
        {
            dlg->u.begin.qos.indicator |= QOSI_PROT_VER;
        }

        if (!cpPresent)
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1992)
            {
                if (dlg->u.begin.ac_name.len == 0 &&
                    dlg->u.begin.user_info.len == 0 &&
                    !hasPV)
                {
                    /* Missing dialog Portion as well as Component Portion
                     * ANSI-Specs Figure 3/T1.114.3 Note 2
                     */

                    return (TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI);
                }
            }
        }
        break;

    case TCPPT_TC_RESP:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_RESP;

        /* check for components */
        if (cpPresent)
        {
            dlg->u.end.cpt_present = 1;
        }

        /* parse dialogue portion */
        if (!ParseDP(dp,
                     tp + len,
                     dlg->u.end.ac_name.data,
                     &dlg->u.end.ac_name.len,
                     dlg->u.end.user_info.data,
                     &dlg->u.end.user_info.len,
                     NULL, NULL, NULL, NULL,
                     &hasPV))
        {
        	return (TCAP_ABT_REASON_BADLY_STRUCT_DLG_PORT_ANSI);
        }

        if (hasPV)
        {
            dlg->u.end.qos.indicator |= QOSI_PROT_VER;
        }

        if (!cpPresent)
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1992)
            {
                if (dlg->u.end.ac_name.len == 0 &&
                    dlg->u.end.user_info.len == 0 &&
                    !hasPV)
                {
                    /* Missing dialog Portion as well as Component Portion
                     * ANSI-Specs Figure 3/T1.114.3 Note 2
                     */

                    return (TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI);
                }
            }
        }
        break;

    case TCPPT_TC_CONV_W_PERM:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_CONV_W_PERM;
 
        /* check for components */
        if (cpPresent)
        {
            dlg->u.cont.cpt_present = 1;
        }

        /* parse dialogue portion */
        if (!ParseDP(dp,
                     tp + len,
                     dlg->u.cont.ac_name.data,
                     &dlg->u.cont.ac_name.len,
                     dlg->u.cont.user_info.data,
                     &dlg->u.cont.user_info.len,
                     NULL, NULL, NULL, NULL,
                     &hasPV))
        {
            return (TCAP_ABT_REASON_BADLY_STRUCT_DLG_PORT_ANSI);
        }

        if (hasPV)
        {
            dlg->u.cont.qos.indicator |= QOSI_PROT_VER;
        }

        if (!cpPresent)
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1992)
            {
                if (dlg->u.cont.ac_name.len == 0 &&
                    dlg->u.cont.user_info.len == 0 &&
                    !hasPV)
                {
                    /* Missing dialog Portion as well as Component Portion
                     * ANSI-Specs Figure 3/T1.114.3 Note 2
                     */

                    return (TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI);
                }
            }
        }
        break;

    case TCPPT_TC_CONV_WO_PERM:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_CONV_WO_PERM;

        /* check for components */
        if (cpPresent)
        {
            dlg->u.cont.cpt_present = 1;
        }

        /* parse dialogue portion */
        if (!ParseDP(dp,
                     tp + len,
                     dlg->u.cont.ac_name.data,
                     &dlg->u.cont.ac_name.len,
                     dlg->u.cont.user_info.data,
                     &dlg->u.cont.user_info.len,
                     NULL, NULL, NULL, NULL,
                     &hasPV))
        {
            return (TCAP_ABT_REASON_BADLY_STRUCT_DLG_PORT_ANSI);
        }

        if (hasPV)
        {
            dlg->u.cont.qos.indicator |= QOSI_PROT_VER;
        }

        if (!cpPresent) /* fix for 174, 175, 188 */
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1992)
            {
                if (dlg->u.cont.ac_name.len == 0 &&
                    dlg->u.cont.user_info.len == 0 &&
                    !hasPV)
                {
                    /* Missing dialog Portion as well as Component Portion
                     * ANSI-Specs Figure 3/T1.114.3 Note 2
                     */

                    return (TCAP_ABT_REASON_UNREC_DLG_PORT_ANSI);
                }
            }
        }
        break;

    case TCPPT_TC_ABORT:
        /* tmp points to tp  
        * skip Package Type Id and Total TCAP Mesg Len */
        tmp++;
        tmp += TCAP_GetLength(tmp, &tcapMesgLen, tp + len, ITS_TRUE);

        /* check TID */
        if (*tmp != TID_IDENT)
        {
            return (TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI);
        }

        /* skip tag */
        tmp ++;

        /* skip Transaction ID */
        tmp += TCAP_GetLength(tmp, &tidLen, tp + len, ITS_TRUE);
        tmp += tidLen; /* Incr by 4 octets */

        if (*tmp == PABT_CAUSE_TAG)
        {
            /* set the ptype */
            dlg->ptype = TCPPT_TC_ABORT;
            tmp ++;
            tmp += TCAP_GetLength(tmp, &causeLen, tp + len, ITS_TRUE);
            /* Set the Abort Reason to P-Abort Cause */
            dlg->u.abort.abort_reason = *tmp;
            /* There is no dialog portion for P_ABORT */
        }
        else
        {
            /* set the ptype */
            dlg->ptype = TCPPT_TC_ABORT;

            /* get the dialogue portion, if any */
            if (dp != NULL)
            {
                /* function to parse dp */
                if (!ParseDP(dp,
                             tp + len,
                             dlg->u.abort.ac_name.data,
                             &dlg->u.abort.ac_name.len,
                             dlg->u.abort.user_info.data,
                             &dlg->u.abort.user_info.len,
                             NULL, NULL, NULL, NULL,
                             &hasPV))
                {
                    return (TCAP_ABT_REASON_BADLY_STRUCT_DLG_PORT_ANSI);
                }

                /* Skip Dialog Portion Id here */
                tmp++;

                /* Skip Dialog Portion len here */
                tmp += TCAP_GetLength(tmp, &dplen, tp + len, ITS_TRUE);
                tmp += dplen;
            }
            if (*tmp == U_ABORT_INFO_TAG)
            {
                /* Skip U_ABORT tag here */
                tmp++;

                /* Get U_abort info len here */
                tmp += TCAP_GetLength(tmp, &abortInfoLen, tp + len, ITS_TRUE);
                dlg->u.abort.abort_info.len = abortInfoLen;
               
                /* Get U_ABORT info */
                memcpy(dlg->u.abort.abort_info.data, tmp, abortInfoLen);
                tmp += abortInfoLen;
            }
            else
            {
                return (TCAP_ABT_REASON_INCORRECT_TRANS_PORT_ANSI);
            }
        }
        break;

    default:
        return (TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_ANSI);
    }

    return (ITS_SUCCESS);
}
