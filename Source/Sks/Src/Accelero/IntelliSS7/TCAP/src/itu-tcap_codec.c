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
 *  ID: $Id: itu-tcap_codec.c,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
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
 *  LOG: Revision 9.5  2005/05/26 10:34:09  adutta
 *  LOG: To satisfy gnu comp.
 *  LOG:
 *  LOG: Revision 9.4  2005/05/11 14:54:16  yranade
 *  LOG: Finish up Indeterminate Length decode fixes.
 *  LOG:
 *  LOG: Revision 9.3  2005/05/11 13:46:41  yranade
 *  LOG: Indeterminate Length Fixes. Help Desk ID 742.
 *  LOG:
 *  LOG: Revision 9.2  2005/04/08 07:40:42  adutta
 *  LOG: Fix for WSC Bug# 1170
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:52:37  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.19  2005/03/21 13:50:36  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 1.5.2.21  2003/09/22 05:27:46  yranade
 *  LOG: Fixes issues seen while testing with ANSI ATP.
 *  LOG:
 *  LOG: Revision 1.5.2.20  2003/07/25 09:35:57  yranade
 *  LOG: Return reject causes, in DataToCPT.
 *  LOG:
 *  LOG: Revision 1.5.2.19  2003/06/28 12:33:49  yranade
 *  LOG: Updates.
 *  LOG:
 *  LOG: Revision 1.5.2.18  2003/06/10 11:18:40  yranade
 *  LOG: Updates to send Abort with ABRT pdu for specific cases.
 *  LOG:
 *  LOG: Revision 1.5.2.17  2003/06/06 14:48:08  yranade
 *  LOG: Length check validation, in DataToCPT.
 *  LOG: Dont check for ASN.1 Tag in ParseDP.
 *  LOG: Some formatting.
 *  LOG:
 *  LOG: Revision 1.5.2.16  2003/06/05 04:59:39  yranade
 *  LOG: Don't check for ParameterTag since it can be any valid ASN.1 tag.
 *  LOG:
 *  LOG: Revision 1.5.2.15  2003/05/27 14:54:27  yranade
 *  LOG: Revert back the rev 1.2.5.13 change. The Abort Tag was being set correctly, before
 *  LOG: this change.
 *  LOG:
 *  LOG: Revision 1.5.2.14  2003/05/27 08:42:25  yranade
 *  LOG: Finish up DialogPDU validation. Set the Reject Tag correctly.
 *  LOG:
 *  LOG: Revision 1.5.2.13  2003/05/25 11:53:08  vjatti
 *  LOG: Set the correct ABORT tag while encoding the ABORT Msg in TCAP_CvtDLGToData().
 *  LOG:
 *  LOG: Revision 1.5.2.12  2003/05/16 10:34:39  vjatti
 *  LOG: Removal of extra check for Dialog portion in FindParts().
 *  LOG:
 *  LOG: Revision 1.5.2.11  2003/05/13 14:01:18  yranade
 *  LOG: Set the return vals correctly.
 *  LOG:
 *  LOG: Revision 1.5.2.10  2003/05/13 07:05:32  vjatti
 *  LOG: Fix Bug 335: Dialog PDU type validation.
 *  LOG:
 *  LOG: Revision 1.5.2.8  2003/05/09 13:45:49  vjatti
 *  LOG: Codec hardening.
 *  LOG:
 *  LOG: Revision 1.5.2.7  2003/05/08 11:51:46  vjatti
 *  LOG: Fix for Bug 294: To make Reject Problem code tags compatible with
 *  LOG: the ones defined in header for ASN.
 *  LOG:
 *  LOG: Revision 1.5.2.6  2003/05/08 09:38:52  vjatti
 *  LOG: Fix for Bug 297.Put P-Abort cause length validation check.
 *  LOG:
 *  LOG: Revision 1.5.2.5  2003/04/23 06:17:49  vjatti
 *  LOG: Handling for U_Reject was missing in TCAP_CvtDataToCPT().
 *  LOG:
 *  LOG: Revision 1.5.2.4  2003/03/27 11:37:05  yranade
 *  LOG: Linked Id Tag and Sequence Length corrections.
 *  LOG:
 *  LOG: Revision 1.5.2.3  2003/03/15 11:13:18  vjatti
 *  LOG: Code Enhancement for Extended Parameter Length.
 *  LOG:
 *  LOG: Revision 1.5.2.2  2003/03/13 12:17:19  vjatti
 *  LOG: Fix for setting the transaction portion len in extended format.
 *  LOG:
 *  LOG: Revision 1.5.2.1  2003/03/11 13:56:17  vjatti
 *  LOG: Code enhancement in BuildCP
 *  LOG:
 *  LOG: Revision 1.5  2003/02/10 14:32:57  yranade
 *  LOG: Oops..increment the offset after setting the Abort Cause.
 *  LOG:
 *  LOG: Revision 1.4  2003/02/07 15:04:25  yranade
 *  LOG: Removed warnings shown by gcc -Wall.
 *  LOG:
 *  LOG: Revision 1.3  2003/02/05 14:02:59  yranade
 *  LOG: Rename FindParts to TCAP_FindParts, since it's in Global Scope.
 *  LOG:
 *  LOG: Revision 1.2  2003/02/05 12:57:09  yranade
 *  LOG: Changes for Windows build.
 *  LOG:
 *  LOG: Revision 1.1  2003/02/04 07:19:40  yranade
 *  LOG: Manual Tcap Codec.
 *  LOG:
 *
 ****************************************************************************/
#if defined(CCITT)
#include <itu/tcap.h>
#elif defined(PRC)
#include <china/tcap.h>
#endif



#define DIALOG_REQUEST_TAG                     (0x60U)
#define UNIDIRECTIONAL_TAG                     (0x60U)
#define DIALOG_RESPONSE_TAG                    (0x61U)
#define DIALOG_ABORT_TAG                       (0x64U)
#define PROTOCOL_VERSION_TAG                   (0x80U)
#define AC_NAME_TAG                            (0xA1U)
#define USER_INFO_TAG                          (0xBEU)
#define RESULT_TAG                             (0xA2U)
#define RESULT_ACCEPTED_TAG                    (0x00U)
#define RESULT_REJECTED_TAG                    (0x01U)
#define RESULT_SOURCE_DIAGNOSTIC_TAG           (0xA3U)
#define DIALOG_SERVICE_USER_TAG                (0xA1U)
#define DIALOG_SERVICE_PROVIDER_TAG            (0xA2U)
#define NULL_TAG                               (0x00U)
#define SERVICE_USER_CONTEXT_NAME_NOT_SUPPLIED (0x02U)
#define SERVICE_PROVIDER_NO_COMM_DIALOG_PORT   (0x02U)
#define ABORT_SOURCE_TAG                       (0x80U)
#define ABORT_SOURCE_USER                      (0x00U)
#define ABORT_SOURCE_PROVIDER                  (0x01U)
#define PABT_CAUSE_TAG                         (0x4AU)

#define EXTERNAL_TAG                           (0x28U)
#define OID_TAG                                (0x06U)
#define SINGLE_ASN1_TAG                        (0xA0U)
#define INTEGER_TAG                            (0x02U)
#define LINKED_ID_TAG                          (0x80U)
#define SEQUENCE_TAG                           (0x30U)
#define SET_TAG                                (0x31U)

#define REJ_PROB_DECODE_MASK                   (0x0FU)
#define REJ_PROB_ENCODE_MASK                   (0x80U)

static ITS_OCTET UnidialogueAsIDValue[] =
{
    0x00U,  /* CCITT */
    0x11U,  /* Recommendation */
    0x86U,  /* Q */
    0x05U,  /* 773 */
    0x01U,  /* as(1) */
    0x02U,  /* unidialoguePDU(2) */
    0x01U   /* version1(1) */
};
static ITS_OCTET DialogueAsIDValue[] =
{
    0x00U,  /* CCITT */
    0x11U,  /* Recommendation */
    0x86U,  /* Q */
    0x05U,  /* 773 */
    0x01U,  /* as(1) */
    0x01U,  /* dialoguePDU(1) */
    0x01U   /* version1(1) */
};

static ITS_OCTET ProtocolVersion[] =
{
   0x07U,  /* Unused Bits */
   0x80U   /* Version 1 */
};

/*****************************************************************************
 *  Purpose:
 *      This function converts TID to Octets.
 *
 *  Input Parameters:
 *      TID t and len.
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
TIDToData(ITS_OCTET *d, ITS_UINT t, ITS_UINT len)
{
#if FIXED_SIZE_TIDS

    d[0] = (t >> 24) & 0xFFU;
    d[1] = (t >> 16) & 0xFFU;
    d[2] = (t >> 8) & 0xFFU;
    d[3] = (t & 0xFFU);

    return (sizeof(ITS_UINT));

#else

    int opSize = sizeof(ITS_UINT);
    int code = (int)t;
    int i;

    /* pretty, ain't it?  It boils down to shearing off the sign
     * extension bits, except the last ITS_OCTET (if 127 > code > -128) */
    if (code < 0)
    {
        while (opSize > 1 &&
               ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FF) == 0x0FF))
        {
            opSize--;
        }

        if (opSize != sizeof(ITS_UINT) &&
            ((code >> ((opSize -1) * ITS_BITS_PER_BYTE) & 0x80) != 0x80))
        {
            opSize++;
        }
    }
    else if (code > 0)
    {
        while (opSize > 1 &&
               ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FFU) == 0x00))
        {
            opSize--;
        }

        if (opSize != sizeof(ITS_UINT) &&
            ((code >> ((opSize -1) * ITS_BITS_PER_BYTE) & 0x80) == 0x80))
        {
            opSize++;
        }
    }
    else
    {
        opSize = 1;
    }

    for (i = opSize; i > 0; i--)
    {
        d[opSize - i] = (code >> ((i - 1) * ITS_BITS_PER_BYTE)) & 0x0FF;
    }

    /* weird Cisco bug */
    if (len > (ITS_UINT)opSize)
    {
        memmove(&d[len - opSize], d, opSize);
        memset(d, 0, len - opSize);

        opSize = len;
    }

    return opSize;
#endif
}

#if 0
/*
 * This isn't used right now but is included for symmetry.  Commented
 * to avoid warnings.
 */
static ITS_UINT
DataToTID(ITS_OCTET *d, int c)
{
    ITS_UINT tid = 0;
    int i;

    for (i = 0; i < c; i++)
    {
        tid <<= 8;
        /*
         * for the first octet, make sure we sign-extend into
         * the upper bits.  Subsequent octets can just be OR'd
         * into the lower bytes after the shift.
         */
        if (i == 0)
        {
            tid |= (signed char)d[i];
        }
        else
        {
            tid |= d[i];
        }
    }

    return tid;
}
#endif

/*****************************************************************************
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
 *      None.
 ****************************************************************************/
#if defined (LOCAL_DEBUG)
static void
PrintOctets(ITS_OCTET *data, int dlen)
{
    int i = 0;

    printf("-----------------------\n");
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
BuildCP(ITS_OCTET *cp, ITS_UINT *cpLen, 
        ITS_OCTET *cpList, ITS_UINT cptsLen)
{
    ITS_INT offset = 0;
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
    PrintOctets(cp, cptsLen + offset);
    printf("\nBuildCP: Components----------------------\n");
#endif

    *cpLen = cptsLen + offset;

    return (ITS_SUCCESS);
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
 ****************************************************************************/
static ITS_BOOLEAN 
BuildDP(ITS_USHORT ptype, ITS_OCTET *dp, ITS_UINT *dpLen,
        ITS_OCTET *applicationContext, ITS_USHORT acLen,
        ITS_OCTET *userInformation, ITS_USHORT uiLen,
        ITS_BOOLEAN accept, ITS_BOOLEAN fromUser,
        ITS_BOOLEAN causeACName, ITS_BOOLEAN includePV)
{
    ITS_INT offset = 0;
    ITS_INT oidLen = 0, pvLen = 0;
    ITS_INT dialogLen = 0, len = 0, asnLen = 0, extLen = 0, dialogPLen = 0;

    *dpLen = 0;

    if ((ptype != TCPPT_TC_U_ABORT) && (acLen == 0 && uiLen == 0))
    {
        return (ITS_SUCCESS);
    }

    /* Step 1: Calculate the lengths */
    switch (ptype)
    {
    case TCPPT_TC_UNI:
    case TCPPT_TC_BEGIN:

        if (includePV)
        {
            /* PV Tag, PV Length, Protocol Version */
            pvLen = sizeof(ProtocolVersion) / sizeof(ITS_OCTET);
            len += (2 + pvLen);
        }

        if (acLen)
        {
            /* AC Name Tag */
            len ++;
            /* AC Name Len Size */
            len += TCAP_SetLength(NULL, acLen, ITS_FALSE);
            /* AC Name */
            len += acLen;
        }

        if (uiLen)
        {
            /* User Info Tag */
            len ++;
            /* User Info len Size */
            len += TCAP_SetLength(NULL, uiLen, ITS_FALSE);
            /* User Info */
            len += uiLen;
        }

        break;

    case TCPPT_TC_END:
    case TCPPT_TC_CONTINUE:

        if (includePV)
        {
            /* PV Tag, PV Length, Protocol Version Len */
            pvLen = sizeof(ProtocolVersion) / sizeof(ITS_OCTET);
            len += (2 + pvLen);
        }

        if(acLen)
        {
            /* AC Name Tag */
            len ++;
            /* AC Name Len Size */
            len += TCAP_SetLength(NULL, acLen, ITS_FALSE);
            /* AC Name */
            len += acLen;
        }

        /* Result Tag, Result Len, Result Value */
        len += 5;

        /* Result Source Diagnostic Tag, Result Source Diagnostic Len 
        Dialog Service Diagnostic */
        len += 7;

        if (uiLen)
        {
            /* User Info Tag */
            len ++;
            /* User Info len Size */
            len += TCAP_SetLength(NULL, uiLen, ITS_FALSE);
            /* User Info */
            len += uiLen;
        }

        break;

    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:

        /* Abort Source Tag, Len, Abort Source */
        len += 3;

        if (uiLen)
        {
            /* User Info Tag */
            len ++;
            /* User Info len */
            len += TCAP_SetLength(NULL, uiLen, ITS_FALSE);
            /* User Info */
            len += uiLen;
        }

        break;

    default:
        break;
    }

    /* Dialog len */
    dialogLen = len;
    len += TCAP_SetLength(NULL, dialogLen, ITS_FALSE);
    /* dialog Tag */
    len ++;

    /* Asn Len */
    asnLen = len;
    len += TCAP_SetLength(NULL, asnLen, ITS_FALSE);
    /* ASN Tag */
    len ++;

    /* OID */
    if (ptype == TCPPT_TC_UNI)
    {
        oidLen = sizeof(UnidialogueAsIDValue) / sizeof(ITS_OCTET);
    }
    else
    {
        oidLen = sizeof(DialogueAsIDValue) / sizeof(ITS_OCTET);
    }

    len += oidLen;
    /* OID Length & Tag */
    len += 2;

    /* Ext Length */
    extLen = len;
    len += TCAP_SetLength(NULL, extLen, ITS_FALSE);
    /* Ext Length Tag */
    len ++;

    /* DialogPortion Length */
    dialogPLen = len;
    len += TCAP_SetLength(NULL, dialogPLen, ITS_FALSE);
    /* DialogPortion Tag */
    len ++;

    /* Step 2: Start Encoding using the lengths we have */

    /* Set Dialog Portion Tag */
    dp[offset++] = DIALOG_IDENT;
    /* Dialog Portion Len */
    offset += TCAP_SetLength(&dp[offset], dialogPLen, ITS_TRUE);

    /* Set External Tag */
    dp[offset++] = EXTERNAL_TAG;
    /* External Len here */
    offset += TCAP_SetLength(&dp[offset], extLen, ITS_TRUE);

    /* Set the OID Tag */
    dp[offset++] = OID_TAG;

    if (ptype == TCPPT_TC_UNI)
    {
        /* Set OID Length */
        oidLen = sizeof(UnidialogueAsIDValue) / sizeof(ITS_OCTET);
        dp[offset++] = oidLen; 
        /* Set UniDialogueAsID Value */
        memcpy(&dp[offset], UnidialogueAsIDValue, oidLen); 
        offset += oidLen;
    } 
    else
    { 
        /* Set OID Length */
        oidLen = sizeof(DialogueAsIDValue) / sizeof(ITS_OCTET);
        dp[offset++] = oidLen;
        memcpy(&dp[offset], DialogueAsIDValue, oidLen);
        offset += oidLen;
    }

    /* Single-ASN.1-type Tag */
    dp[offset++] = SINGLE_ASN1_TAG;
    /* Single-ASN.1-type len */ 
    offset += TCAP_SetLength(&dp[offset], asnLen, ITS_TRUE);
 
    switch (ptype)
    {
    case TCPPT_TC_UNI:
    case TCPPT_TC_BEGIN:

        if (ptype == TCPPT_TC_UNI)
        {
            /* Set Unidirectional Dialog Tag */
            dp[offset++] = UNIDIRECTIONAL_TAG;
            /* Unidirectional Dialog Len */
            offset += TCAP_SetLength(&dp[offset], dialogLen, ITS_TRUE); 
        }
        else
        {
            /* Set Dialogue Request Tag */
            dp[offset++] = DIALOG_REQUEST_TAG;
            /* Dialog  Request Len */
            offset += TCAP_SetLength(&dp[offset], dialogLen, ITS_TRUE); 
        }
        if (includePV)
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

        if (acLen)
        {
            /* Set AC Name Tag */
            dp[offset++] = AC_NAME_TAG;
            /* Set AC Name Len */
            offset += TCAP_SetLength(&dp[offset], acLen, ITS_TRUE);
            /* Copy in the Application Context */
            memcpy(&dp[offset], applicationContext, acLen);
            offset += acLen;
        }

        if (uiLen)
        {
            /* Set User Info Tag */
            dp[offset++] = USER_INFO_TAG;
            /* Set User Info len */
            offset += TCAP_SetLength(&dp[offset], uiLen, ITS_TRUE);
            /* Copy in the User Info */
            memcpy(&dp[offset], userInformation, uiLen);
            offset += uiLen; 
        }

        /* Set the lengths */
        *dpLen = offset;

        break;
   
    case TCPPT_TC_END:
    case TCPPT_TC_CONTINUE:
    
        /* Set Dialogue Response Tag */
        dp[offset++] = DIALOG_RESPONSE_TAG;
        /* Dialog  Response Len */
        offset += TCAP_SetLength(&dp[offset], dialogLen, ITS_TRUE);

        if (includePV)
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

        if(acLen)
        {
            /* Set AC Name Tag */
            dp[offset++] = AC_NAME_TAG;
            /* Set AC Name Len */
            offset += TCAP_SetLength(&dp[offset], acLen, ITS_TRUE);
            /* Copy in the Application Context */
            memcpy(&dp[offset], applicationContext, acLen);
            offset += acLen;
        }

        /* Set Result Tag */
        dp[offset++] = RESULT_TAG;
        /* Set Result Len */
        dp[offset++] = 3; 
        /* Set Result Value Tag */
        dp[offset++] = INTEGER_TAG;
        /* Set Result Value Len */
        dp[offset++] = 1; 
        /* Set Result Value */
        if (accept)
        {
            dp[offset++] = RESULT_ACCEPTED_TAG;
        }
        else
        {
            dp[offset++] = RESULT_REJECTED_TAG;
        } 

        /* Result Source Diagnostic Tag */
        dp[offset++] = RESULT_SOURCE_DIAGNOSTIC_TAG;
        /* Result Source Diagnostic Len */
        dp[offset++] = 5;
        /* Dialog Service Diagnostic */ 
        if (fromUser)
        {
            /* Set Dialog Service User Tag */
            dp[offset++] = DIALOG_SERVICE_USER_TAG;
            /* Set Dialog Service User Len */
            dp[offset++] = 3;
            /* Set INTEGER TAG */
            dp[offset++] = INTEGER_TAG;
            /* Set Integer Len */
            dp[offset++] = 1;

            if (!causeACName)
            {
                /* Set Dialog Service User Diagnostic Value */
                dp[offset++] = NULL_TAG;
            }
            else
            {
                /* Set Dialog Service User Diagnostic Value */
                dp[offset++] = SERVICE_USER_CONTEXT_NAME_NOT_SUPPLIED;
            }
        }
        else
        {
            /* Set Dialog Service Provider Tag */
            dp[offset++] = DIALOG_SERVICE_PROVIDER_TAG;
            /* Set Dialog Service Provider Len */
            dp[offset++] = 3;
            /* Set INTEGER TAG */
            dp[offset++] = INTEGER_TAG;
            /* Set Integer Len */
            dp[offset++] = 1;

            if (accept)
            {
                /* Set Dialog Service Provider Diagnostic Value */
                dp[offset++] = NULL_TAG;
            }
            else
            {
                /* Set Dialog Service Provider Diagnostic Value */
                dp[offset++] = SERVICE_PROVIDER_NO_COMM_DIALOG_PORT;
            }
        } 

        if (uiLen)
        {
            /* Set User Info Tag */
            dp[offset++] = USER_INFO_TAG;
            /* Set User Info len */
            offset += TCAP_SetLength(&dp[offset], uiLen, ITS_TRUE);
            /* Copy in the User Info */
            memcpy(&dp[offset], userInformation, uiLen);
            offset += uiLen;
        }

        /* Set the lengths */
        *dpLen = offset;

        break;
    
    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:
   
        /* Set Dialogue Abort Tag */
        dp[offset++] = DIALOG_ABORT_TAG;
        /* Skip Dialog Abort Len */
        offset += TCAP_SetLength(&dp[offset], dialogLen, ITS_TRUE);

        /* Abort Source Tag */
        dp[offset++] = ABORT_SOURCE_TAG;
        /* Abort Source Len */
        dp[offset++] = 1;
        /* Abort Source */
        if (fromUser)
        {
            /* Set Abort Source */ 
            dp[offset++] = ABORT_SOURCE_USER;
        }
        else
        {
            /* Set Abort Source */ 
            dp[offset++] = ABORT_SOURCE_PROVIDER;
        }

        if (uiLen)
        {
            /* Set User Info Tag */
            dp[offset++] = USER_INFO_TAG;
            /* Set User Info len */
            offset += TCAP_SetLength(&dp[offset], uiLen, ITS_TRUE);
            /* Copy in the User Info */
            memcpy(&dp[offset], userInformation, uiLen);
            offset += uiLen;
        } 

        /* Set the lengths */
        *dpLen = offset;

        break;
   
    default:
        break;
    }

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
 *
 *
 *  Revision History:
 * ---------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * ---------------------------------------------------------------------------
 * sbabu     04-07-2005  WSC Bug ID#1170         TCAP decoding fails if the total
 *                                               TCAP length is 128
 *
 * sbabu     04-11-2005  HelpDesk ID#742         Indeterminate Length Decode 
 *
 ****************************************************************************/
SS7DLLAPI enum ParseCode
TCAP_FindParts_CCITT(ITS_OCTET *pdup, int wlen,
                     ITS_OCTET **tp, ITS_OCTET **dp, ITS_OCTET **cp)
{
    ITS_UINT tid, tidLen;
    ITS_UINT tag, clen;
    ITS_OCTET *pdu = pdup;
    ITS_UINT eocBytes;

    *tp = pdup;
    *dp = NULL;
    *cp = NULL;

    /* skip tag */
    pdu += TCAP_GetTag(pdu, &tag, pdup + wlen);

    /* get total len */
    pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);

    /*
     * skip 1st tids
     */
    if (*pdu == OTID_IDENT)
    {
        pdu++;

        TCAP_GetTID(&pdu, &tid, &tidLen);
    }
    else if (*pdu == DTID_IDENT)
    {
        pdu++;

        TCAP_GetTID(&pdu, &tid, &tidLen);
    }
    else
    {
        if (*pdup != TCAP_PT_TC_UNI_CCITT)
        {
            return PC_NO_TIDS;
        }
    }

    /*
     * skip second tid, if present
     */
    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        if (*pdup == TCAP_PT_TC_UNI_CCITT)
        {
            return PC_OOD_1;
        }
        else
        {
            return PC_PARSE_OK;
        }
    }

    if (*pdu == OTID_IDENT)
    {
        pdu++;

        TCAP_GetTID(&pdu, &tid, &tidLen);
    }
    else if (*pdu == DTID_IDENT)
    {
        pdu++;

        TCAP_GetTID(&pdu, &tid, &tidLen);
    }

    /*
     * Dialogue portion present?
     */
    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        if (*pdup == TCAP_PT_TC_UNI_CCITT)
        {
            return PC_OOD_2;
        }
        else
        {
            return PC_PARSE_OK;
        }
    }

    if (*pdu == DIALOG_IDENT)
    {
        *dp = pdu;

        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }
    else if (*pdu == PABT_IDENT)
    {
        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
       
        /* have we run out of data */
        if ((pdu - pdup) != wlen)
        {
            return PC_OOD_3;
        }
        else
        {
            return PC_PARSE_OK;
        }
    }

    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        if (*pdup == TCAP_PT_TC_UNI_CCITT)
        {
            return PC_OOD_3;
        }
        else
        {
            return PC_PARSE_OK;
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

    eocBytes = pdu - pdup;

    while (eocBytes < wlen && pdu[0] == 0 && pdu[1] == 0)
    {
        pdu += 2;
        eocBytes += 2;
    }
    
    if ((pdu - pdup) >= wlen)
    {
        return PC_PARSE_OK;
    }
    else
    {
        return PC_OVERFLOW;
    }
}

/*****************************************************************************
 *  Purpose:
 *      Encode the message in Octets. Also see BuildDP and BuildCP
 *
 *  Input Parameters:
 *      Pointer to TCAP_DLG dlg structure, List of Components cpList, ComponentsLen
 *      cptsLen, local TID ltid, remoteTID rtid,
 *      remoteTID len rtidLen and the variant
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
TCAP_CvtDLGToData_CCITT(TCAP_DLG *dlg, ITS_OCTET *tp, ITS_UINT *tpLen,
                        ITS_OCTET *cpList, ITS_UINT cptsLen,
                        ITS_INT ltid, ITS_INT rtid, ITS_UINT rtidLen,
                        int variant)
{
    ITS_INT offset = 0, mlenoffset = 0;
    ITS_INT otidlen = 0, dtidlen = 0;
    ITS_OCTET tidArr [4]; 
    ITS_UINT dpLen = 0;
    ITS_UINT cpLen = 0;
    int lsize = 0;

    if (!dlg)
    {
        return (!ITS_SUCCESS);
    }

    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
   
        /* Set Message Type Tag */
        tp[offset++] = TCPPT_TC_UNI; 

        /* Mark & Skip Message Len here */
        mlenoffset = offset;
        offset++;

        /* Build Dialog Portion if any */
        if (variant >= ITS_SECOND_GEN)
        {
            BuildDP(TCPPT_TC_UNI,
                    &tp[offset], &dpLen,
                    dlg->u.uni.ac_name.data,
                    dlg->u.uni.ac_name.len,
                    dlg->u.uni.user_info.data,
                    dlg->u.uni.user_info.len,
                    ITS_TRUE,
                    ITS_TRUE,
                    ITS_FALSE,
                    dlg->u.uni.qos.indicator & QOSI_PROT_VER
                       ? ITS_TRUE
                       : ITS_FALSE);
        } 

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
        /* Move the data only when in extended format */
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

    case TCPPT_TC_BEGIN:
       
        /* Set Message Type Tag */
        tp[offset++] =  TCPPT_TC_BEGIN;
        /* Mark & Skip Message Len */
        mlenoffset = offset;
        offset++;

        /* build the Originating transaction id */
        /* OTID Tag */
        tp[offset++] = OTID_IDENT;
        /* OTID Len */
        otidlen = TIDToData(tidArr, ltid, 0);
        tp[offset++] = otidlen;
        /* OTID */
        memcpy(&tp[offset], tidArr, otidlen);
        offset += otidlen;

        /* Build Dialog Portion if any */
        if (variant >= ITS_SECOND_GEN)
        {
            BuildDP(TCPPT_TC_BEGIN,
                    &tp[offset], &dpLen,
                    dlg->u.begin.ac_name.data,
                    dlg->u.begin.ac_name.len,
                    dlg->u.begin.user_info.data,
                    dlg->u.begin.user_info.len,
                    ITS_TRUE,
                    ITS_TRUE,
                    ITS_FALSE,
                    dlg->u.begin.qos.indicator & QOSI_PROT_VER
                       ? ITS_TRUE
                       : ITS_FALSE);
        }

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
        /* Move the data only when in extended format */
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
     
    case TCPPT_TC_CONTINUE:
  
        /* Set Message Type Tag */
        tp[offset++] =  TCPPT_TC_CONTINUE;

        /* Mark & Skip Message Len here */
        mlenoffset = offset;
        offset++;

        /* build the Originating transaction id */
        /* OTID Tag */
        tp[offset++] = OTID_IDENT;
        /* OTID Len */
        otidlen = TIDToData(tidArr, ltid, 0);
        tp[offset++] = otidlen;
        /* OTID */
        memcpy(&tp[offset], tidArr, otidlen);
        offset += otidlen;

        /* build the Destination transaction id */
        /* OTID Tag */
        tp[offset++] = DTID_IDENT;
        /* OTID Len */
        dtidlen = TIDToData(tidArr, rtid, rtidLen);
        tp[offset++] = dtidlen;
        /* OTID */
        memcpy(&tp[offset], tidArr, dtidlen);
        offset += dtidlen;

        /* Build Dialog Portion if any */
        if (variant >= ITS_SECOND_GEN)
        {
            BuildDP(TCPPT_TC_CONTINUE,
                    &tp[offset], &dpLen,
                    dlg->u.cont.ac_name.data,
                    dlg->u.cont.ac_name.len,
                    dlg->u.cont.user_info.data,
                    dlg->u.cont.user_info.len,
                    ITS_TRUE,
                    ITS_TRUE,
                    ITS_FALSE,
                    dlg->u.cont.qos.indicator & QOSI_PROT_VER
                       ? ITS_TRUE
                       : ITS_FALSE);
        }

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
        /* Move the data only when in extended format */
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
       
    case TCPPT_TC_END:
    
        /* Set Message Type Tag */
        tp[offset++] =  TCPPT_TC_END;

        /* Mark Message Len here */
        mlenoffset = offset;
        offset++;

        /* build the Destination transaction id */
        /* OTID Tag */
        tp[offset++] = DTID_IDENT;
        /* OTID Len */
        dtidlen = TIDToData(tidArr, rtid, rtidLen);
        tp[offset++] = dtidlen;
        /* DTID */
        memcpy(&tp[offset], tidArr, dtidlen);
        offset += dtidlen;

        /* Build Dialog Portion if any */
        if (variant >= ITS_SECOND_GEN)
        {
            BuildDP(TCPPT_TC_END,
                    &tp[offset], &dpLen,
                    dlg->u.end.ac_name.data,
                    dlg->u.end.ac_name.len,
                    dlg->u.end.user_info.data,
                    dlg->u.end.user_info.len,
                    ITS_TRUE,
                    ITS_TRUE,
                    ITS_FALSE,
                    dlg->u.end.qos.indicator & QOSI_PROT_VER
                       ? ITS_TRUE
                       : ITS_FALSE);
        }

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
        /* Move the data only when in extended format */
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
      
    case TCPPT_TC_U_ABORT:
    case TCPPT_TC_P_ABORT:
         
        /* Set Message Type Tag */
        tp[offset++] = TCPPT_TC_P_ABORT;

        /* Skip Message Len here */
        mlenoffset = offset;
        offset++;

        /* build the Destination transaction id */
        /* DTID Tag */
        tp[offset++] = DTID_IDENT;
        /* DTID Len */
        dtidlen = TIDToData(tidArr, rtid, rtidLen);
        tp[offset++] = dtidlen;
        /* DTID */
        memcpy(&tp[offset], tidArr, dtidlen);
        offset += dtidlen;

        /* Build Dialog Portion */
        if (dlg->ptype == TCPPT_TC_P_ABORT)
        {
            if ((variant >= ITS_SECOND_GEN) && 
                (dlg->u.abort.abort_reason == TCPPABT_ABNORMAL_DLG))
            {
                 BuildDP(TCPPT_TC_U_ABORT,
                         &tp[offset], &dpLen,
                         dlg->u.abort.ac_name.data,
                         dlg->u.abort.ac_name.len,
                         dlg->u.abort.user_info.data,
                         dlg->u.abort.user_info.len,
                         ITS_FALSE,
                         ITS_FALSE,
                         ITS_FALSE,
                         dlg->u.abort.qos.indicator & QOSI_PROT_VER
                              ? ITS_TRUE
                              : ITS_FALSE);
            } 
            else
            {
                 /* Set the P-Abort Cause Tag, Length and Cause */
                 tp[offset++] = PABT_CAUSE_TAG;
                 /* Set the P-Abort Cause Len */
                 tp[offset++] = 1;
                 /* Copy in the P-Abort Cause */
                 tp[offset++] = (ITS_OCTET)dlg->u.abort.abort_reason;

                 /* No Dialog Portion */
            }
        }
        else
        {
            if (variant >= ITS_SECOND_GEN)
            {
                if (dlg->u.abort.ac_name.len != 0 ||
                    dlg->u.abort.user_info.len != 0)
                {
                    if (dlg->u.abort.abort_reason == TCPUABT_AC_NOT_SUP)
                    {
                        BuildDP(TCPPT_TC_END,
                                &tp[offset], &dpLen,
                                dlg->u.abort.ac_name.data,
                                dlg->u.abort.ac_name.len,
                                dlg->u.abort.user_info.data,
                                dlg->u.abort.user_info.len,
                                ITS_FALSE,
                                ITS_TRUE,
                                ITS_TRUE,
                                dlg->u.abort.qos.indicator & QOSI_PROT_VER
                                  ? ITS_TRUE
                                  : ITS_FALSE);
                    }
                    else if (dlg->u.abort.abort_reason == TCPUABT_DLG_REFUSED)
                    {
                        BuildDP(TCPPT_TC_END,
                                &tp[offset], &dpLen,
                                dlg->u.abort.ac_name.data,
                                dlg->u.abort.ac_name.len,
                                dlg->u.abort.user_info.data,
                                dlg->u.abort.user_info.len,
                                ITS_FALSE,
                                ITS_TRUE,
                                ITS_FALSE,
                                dlg->u.abort.qos.indicator & QOSI_PROT_VER
                                  ? ITS_TRUE
                                  : ITS_FALSE);
                    }
                    else
                    {
                        BuildDP(TCPPT_TC_U_ABORT,
                                &tp[offset], &dpLen,
                                dlg->u.abort.ac_name.data,
                                dlg->u.abort.ac_name.len,
                                dlg->u.abort.user_info.data,
                                dlg->u.abort.user_info.len,
                                ITS_FALSE,
                                ITS_TRUE,
                                ITS_FALSE,
                                dlg->u.abort.qos.indicator & QOSI_PROT_VER
                                  ? ITS_TRUE
                                  : ITS_FALSE);
                    }     
                }
                else
                {
                    dpLen = 0;
                }
            }
            else
            {
                /* TODO: Assume Blue Book */
            }
        }

#if defined (LOCAL_DEBUG)
printf("\n: DP-----------------------------\n");
PrintOctets(&tp[offset], dpLen);
printf("\n: DP-----------------------------\n");
#endif

        offset += dpLen;

        /* No component portion */

        /* Set transaction portion len */
        /* Move the data only when in extended format */
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
       
    }

    return (ITS_SUCCESS); 
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
TCAP_CvtCPTToData_CCITT(TCAP_CPT *cpt, ITS_OCTET *cp, ITS_UINT *cpLen)
{
    ITS_UINT cptLen, seqLen = 0;
    ITS_INT offset = 0;

    *cpLen = 0;

    if (!cpt)
    {
        return (!ITS_SUCCESS);
    }
     
    switch (cpt->ptype)
    {
    case TCPPT_TC_INVOKE:
        
        cptLen = (cpt->u.invoke.invoke_id.len + 
                  cpt->u.invoke.linked_id.len +
                  cpt->u.invoke.operation.len +
                  cpt->u.invoke.param.len);

        /* Set Component Type Tag */
        cp[offset++] = TCPPT_TC_INVOKE;

        /* Component Type Len */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke ID TAG */
        if (cpt->u.invoke.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Set Invoke Id Tag, Len and ID */
            memcpy(&cp[offset], cpt->u.invoke.invoke_id.data, 
                                cpt->u.invoke.invoke_id.len);
            offset += cpt->u.invoke.invoke_id.len;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Linked ID Tag */
        if (cpt->u.invoke.linked_id.len == 3 && 
            cpt->u.invoke.linked_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Refer SetLinkedId function in tcap++.h
               It sets INVOKE_TAG and length and copies in the
               data. Works fine for Pepsy Codec. But we need to
               really set the Linked Id Tag
            */

            /* Set Linked Id Tag */
            cp[offset++] = LINKED_ID_TAG;
            /* Set Len */
            cp[offset++] = 1;
            /* Set the Linked ID */
            cp[offset++] = cpt->u.invoke.linked_id.data[2];
        }

        /* Op Code Tag */
        /* Check me -- Works for Local Op */
        if (cpt->u.invoke.operation.len)
        {
            memcpy(&cp[offset], cpt->u.invoke.operation.data, 
                                cpt->u.invoke.operation.len);
            offset += cpt->u.invoke.operation.len;
        }
        else
        {
            return (!ITS_SUCCESS);
        } 

        /* Parameters */
        if (cpt->u.invoke.param.len)
        {
            memcpy(&cp[offset], cpt->u.invoke.param.data, 
                                cpt->u.invoke.param.len);
            offset += cpt->u.invoke.param.len;
        } 

        *cpLen = offset;

        break;
      
    case TCPPT_TC_RESULT_L:
    case TCPPT_TC_RESULT_NL:
        
        if (cpt->u.result.param.len)
        {
            cptLen = (2 + cpt->u.result.invoke_id.len + 
                      cpt->u.result.operation.len +
                      cpt->u.result.param.len);
        }
        else
        {
            cptLen = (cpt->u.result.invoke_id.len +
                      cpt->u.result.operation.len);
        }

        /* Set Component Type Tag */
        cp[offset++] = (ITS_OCTET)cpt->ptype;

        /* Component Type Len */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke ID TAG */
        if (cpt->u.result.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Set Invoke Id Tag, Len and ID */
            memcpy(&cp[offset], cpt->u.result.invoke_id.data, 
                                cpt->u.result.invoke_id.len);
            offset += cpt->u.result.invoke_id.len;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Sequence Tag */
        if (cpt->u.result.param.len)
        {
            /* Set Sequence Tag Ref: Table 16:Q.773 */ 
            cp[offset++] = SEQUENCE_TAG;
            /* Set Sequence Len */
            if (cpt->u.result.operation.len)
            {
                seqLen = cpt->u.result.operation.len;
            }
            seqLen += cpt->u.result.param.len;
            cp[offset++] = seqLen; 
        }

        /* OpCode */
        /* Check me -- Works for Local Op */
        if (cpt->u.result.operation.len)
        {
            /* Set OpCode Tag, Length and Value */
            memcpy(&cp[offset], cpt->u.result.operation.data, 
                                cpt->u.result.operation.len);
            offset += cpt->u.result.operation.len;
        } 

        /* Parameters */
        if (cpt->u.result.param.len)
        {
            memcpy(&cp[offset], cpt->u.invoke.param.data, 
                                cpt->u.invoke.param.len);
            offset += cpt->u.invoke.param.len;
        }

        /* Return the total Length */
        *cpLen = offset;

        break;
        
    case TCPPT_TC_U_ERROR:
        
        cptLen = (cpt->u.error.invoke_id.len +
                 cpt->u.error.error.len +
                 cpt->u.error.param.len);

        /* Set Component Type Tag */
        cp[offset++] = TCPPT_TC_U_ERROR;

        /* Component Type Len */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke ID TAG */
        if (cpt->u.error.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Set Invoke Id Tag, Len and ID */
            memcpy(&cp[offset], cpt->u.error.invoke_id.data, 
                                cpt->u.error.invoke_id.len);
            offset += cpt->u.error.invoke_id.len;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Error Code Tag */
        if (cpt->u.error.error.len)
        {
            memcpy(&cp[offset], cpt->u.error.error.data, 
                                cpt->u.error.error.len);
            offset += cpt->u.error.error.len;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Parameters */
        if (cpt->u.error.param.len)
        {
            memcpy(&cp[offset], cpt->u.invoke.param.data, 
                                cpt->u.invoke.param.len);
            offset += cpt->u.invoke.param.len;
        }

        /* Return the total Length */
        *cpLen = offset;

        break;
       
    case TCPPT_TC_L_REJECT:
    case TCPPT_TC_R_REJECT:
    case TCPPT_TC_U_REJECT:
      
        cptLen = (cpt->u.reject.invoke_id.len + 
                  cpt->u.reject.problem.len);
     
        /* Set Component Type Tag */
        cp[offset] = (ITS_OCTET)cpt->ptype;

        if (cpt->ptype != TCPPT_TC_L_REJECT)
        {
            cp[offset] = TCPPT_TC_R_REJECT;
        } 
        offset ++;

        /* Component Type Len */
        offset += TCAP_SetLength(&cp[offset], cptLen, ITS_TRUE);

        /* Invoke ID TAG */
        if (cpt->u.reject.invoke_id.data[0] == TCPPN_INVOKE_TAG)
        {
            /* Set Invoke Id Tag, Len and ID */
            memcpy(&cp[offset], cpt->u.reject.invoke_id.data, 
                                cpt->u.reject.invoke_id.len);
            offset += cpt->u.reject.invoke_id.len;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Problem Code */
        if (cpt->u.reject.problem.len && cpt->u.reject.problem.data[1] == 1)
        {
            /* Fix for Problem code to make it compatible with ASN code vals*/
            cpt->u.reject.problem.data[0] |= REJ_PROB_ENCODE_MASK;
            /* Set the problem code tag, len and value */
            memcpy(&cp[offset], cpt->u.reject.problem.data, 
                                cpt->u.reject.problem.len);
            offset += cpt->u.reject.problem.len;
        }
        else
        {
            return (!ITS_SUCCESS);
        }

        /* Return the total Length */
        *cpLen = offset;

        break;
        
    default:
        /* Check me */
        break;
    }

    return (ITS_SUCCESS);
}


/*****************************************************************************
 *  Purpose:
 *      Decodes the Octets and builds the TCAP_CPT structure.
 *
 *  Input Parameters:
 *      ITS_OCTET array cp, ComponentType Tag and Componentslen cLen.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Pointer to TCAP_CPT strucure.
 *
 *  Return Value:
 *      Success or Failure. Failure is returned with Exact Reject Cause.
 *
 *  NOTE: For UNREC_COMP a Reject Cause of 0x80 is returned instead of
 *            0x0, since ITS_SUCCESS is also 0x0
 *
 *
 *  Revision History:
 * ---------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * ---------------------------------------------------------------------------
 * sbabu     04-07-2005  WSC Bug Id#1170         Decoding fails if the total 
 *                                               TCAP length is 128 
 * sbabu     04-11-2005  HelpDesk ID#742         Indeterminate Length Decode 
 *                                          
 ****************************************************************************/
SS7DLLAPI int
TCAP_CvtDataToCPT_CCITT(TCAP_CPT *cpt, ITS_OCTET *cp,
                        ITS_UINT cTag, ITS_USHORT cLen)
{
    ITS_OCTET *tmp, *data, *stop;
    ITS_UINT tag, pTag, len;
    ITS_INT tagLen = 0, tLen = 0;
    ITS_UINT eocBytes;

    memset(cpt, 0, sizeof(TCAP_CPT));

    if (!cp || !cLen)
    {
        return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
    } 

    data = cp;

    stop = cp + cLen;

    switch (cTag)
    {
    case TCPPT_TC_INVOKE:
        
        /* set the pType */
        cpt->ptype = TCPPT_TC_INVOKE;

        /* get the invoke ids */
        if (*data == TCPPN_INVOKE_TAG &&
            *(data + 1) == 1)
        {
            cpt->u.invoke.invoke_id.len = 3;
            cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.invoke.invoke_id.data[1] = 1;
            /* skip Invoke ID Tag and Invoke ID Len */
            data += 2;
            cpt->u.invoke.invoke_id.data[2] = *data;
            data ++;
        }
        else
        {
            return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
        }

        /* Have we run out of data
         * If Yes, return Error, since OP Code
         * presence is mandatory
         */
        if ((data - cp) >= cLen)
        {
            return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        }

        if (*data == LINKED_ID_TAG &&
            *(data + 1) == 1)
        {
            cpt->u.invoke.linked_id.len = 3;
            cpt->u.invoke.linked_id.data[0] = LINKED_ID_TAG;
            cpt->u.invoke.linked_id.data[1] = 1;
            /* skip Linked ID Tag and Linked ID Len */
            data += 2;
            cpt->u.invoke.linked_id.data[2] = *data;
            data ++;
        }

        /* get the opCode */
        if ((data - cp) < cLen)
        {
            tmp = data;
            tagLen = TCAP_GetTag(tmp, &tag, stop);

            if (tag == TCPPN_LOCAL_OP_TAG || 
                tag == TCPPN_GLOBAL_OP_TAG)
            {
                tmp += tagLen;
                tLen = TCAP_GetLength(tmp, &len, stop,ITS_FALSE);
                tmp += tLen;
                memcpy(cpt->u.invoke.operation.data, data, tagLen + tLen + len);
                cpt->u.invoke.operation.len = (tagLen + tLen + len);
                data += (tagLen + tLen + len);
            }
            else
            {
                /* Invalid Tag: OpCode expected */
                return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
            }

        }
        else
        {
            /* Missing Mandatory OpCode */
            return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        }

        /* get the parameters if any */
        if ((data - cp) < cLen)
        {
            tmp = data;
            tagLen = TCAP_GetTag(tmp, &tag, stop);
            tmp += tagLen;

            tLen = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
            tmp += tLen;

            memcpy(cpt->u.invoke.param.data, data, tagLen + tLen + len);
            cpt->u.invoke.param.len = (tagLen + tLen + len);
            data += (tagLen + tLen + len);
        }

        break;
      
    case TCPPT_TC_RESULT_L:
    case TCPPT_TC_RESULT_NL:
       
        /* set the pType */
        cpt->ptype = cTag;

        /* get the invoke ids */
        if (*data == TCPPN_INVOKE_TAG &&
            *(data + 1) == 1)
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
            return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
        }

        /* Have we run out of data.
         * If Yes, it means, no Optionals are present
         * So just return.
         */
        if ((data - cp) == cLen)
        {
            return (ITS_SUCCESS);
        }

        /* skip the Sequence Tag and Len */
        if (*data == SEQUENCE_TAG)
        {
            data += TCAP_GetTag(data, &tag, stop);
            data += TCAP_GetLength(data, &len, stop, ITS_TRUE);
        }
        else
        {
            if ((data - cp) < cLen)
            {
                return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
            }
        }

        /* get the opCode */
        if ((data - cp) < cLen)
        {
            tmp = data;
            tagLen = TCAP_GetTag(tmp, &tag, stop);

            if (tag == TCPPN_LOCAL_OP_TAG || 
                tag == TCPPN_GLOBAL_OP_TAG)
            {
                tmp += tagLen;
                tLen = TCAP_GetLength(tmp, &len, stop,ITS_FALSE);
                tmp += tLen;
                memcpy(cpt->u.result.operation.data, data, tagLen + tLen + len);
                cpt->u.result.operation.len = (tagLen + tLen + len);
                data += (tagLen + tLen + len);
            }
            else
            {
                /* Invalid Tag: OpCode expected */
                return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
            }
        }
        else
        {
            /*
             * We have run out of data. It means, seq is present, 
             * but no opCode and no Parameter
             * return error
             */
            return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        }

        /* get the parameters if any */
        if ((data - cp) < cLen)
        {
            tmp = data;
            tagLen = TCAP_GetTag(tmp, &tag, stop);
            tmp += tagLen;
            tLen = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
            tmp += tLen;
            memcpy(cpt->u.result.param.data, data, tagLen + tLen + len);
            cpt->u.result.param.len = tagLen + tLen + len;
            data += (tagLen + tLen + len);
        }
        else
        {
            /* No Parameters 
             * But Sequence and OpCode was present
             * return Error, since it must be
             * present only when parameters are present.
             */
            return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        }

        break;
        
    case TCPPT_TC_U_ERROR:
       
        /* set the pType */
        cpt->ptype = TCPPT_TC_U_ERROR;

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
            return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
        }

        /* get the ErrorCode */
        if ((data - cp) < cLen)
        {
            tmp = data;
            tagLen = TCAP_GetTag(tmp, &tag, stop);

            if (tag == TCPPN_LOCAL_ERR_TAG || 
                tag == TCPPN_GLOBAL_OP_TAG)
            {
                tmp += tagLen;
                tLen = TCAP_GetLength(tmp, &len, stop,ITS_FALSE);
                tmp += tLen;
                memcpy(cpt->u.error.error.data, data, tagLen + tLen + len);
                cpt->u.error.error.len = (tagLen + tLen + len);
                data += (tagLen + tLen + len);
            }
            else
            {
                return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
            }
        }
        else
        {
            /*
             * We have run out of data. 
             * Missing Mandatory Error Code 
             * return error
             */
            return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        }

        /* get the parameter */
        if ((data - cp) < cLen)
        {
            tmp = data;
            tagLen = TCAP_GetTag(tmp, &tag, stop);
            tmp += tagLen;
            tLen = TCAP_GetLength(tmp, &len, stop, ITS_TRUE);
            tmp += tLen;
            memcpy(cpt->u.error.param.data, data, tagLen + tLen + len);
            cpt->u.error.param.len = tagLen + tLen + len;
            data += (tagLen + tLen + len);
        }

        break;

    case TCPPT_TC_R_REJECT:
    case TCPPT_TC_U_REJECT:
      
        /* set the pType */
        cpt->ptype = cTag;

        /* get the invoke ids */
        if (*data == TCPPN_INVOKE_TAG &&
            *(data + 1) == 1)
        {
            cpt->u.reject.invoke_id.len = 3;
            cpt->u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.reject.invoke_id.data[1] = 1;
            /* skip Invoke ID Tag and Invoke ID Len */
            data += 2;
            cpt->u.reject.invoke_id.data[2] = *data;
            data ++;
        }
        else if (*data == NULL_TAG &&
                 *(data + 1) == 0)
        {
            cpt->u.reject.invoke_id.len = 2;
            cpt->u.reject.invoke_id.data[0] = NULL_TAG;
            cpt->u.reject.invoke_id.data[1] = 0;
            data += 2;
        }
        else
        {
            return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
        }

        /* Have we run out of data
         * If Yes, return Error, missing Problem Code
         */
        if ((data - cp) >= cLen)
        {
            return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
        }

        /* get the problem */
        pTag = *data;
        cpt->u.reject.problem.len = 3;
        cpt->u.reject.problem.data[1] = 1;

        /* Skip problem code Tag and Problem Code Len */
        data += 2;

        /* Fix for Problem code to make it compatible with ASN code vals*/
        pTag = pTag & REJ_PROB_DECODE_MASK;

        switch (pTag)
        {
        case TCPPROB_GENERAL:
            cpt->u.reject.problem.data[0] = TCPPROB_GENERAL;
            cpt->u.reject.problem.data[2] = *data;
            break;

        case TCPPROB_INVOKE:
            cpt->u.reject.problem.data[0] = TCPPROB_INVOKE;
            cpt->u.reject.problem.data[2] = *data;
            if (cpt->u.reject.problem.data[2] !=
                TCPPROB_SPEC_INV_UNREC_LINKED_ID)
            {
                cpt->ptype = TCPPT_TC_U_REJECT;
            }
            break;

        case TCPPROB_RETURN_RES:
            cpt->u.reject.problem.data[0] = TCPPROB_RETURN_RES;
            cpt->u.reject.problem.data[2] = *data;
            if (cpt->u.reject.problem.data[2] ==
                TCPPROB_SPEC_RES_MISTYPED_PARAM)
            {
                cpt->ptype = TCPPT_TC_U_REJECT;
            }
            break;

        case TCPPROB_RETURN_ERR:
            cpt->u.reject.problem.data[0] = TCPPROB_RETURN_ERR;
            cpt->u.reject.problem.data[2] = *data;
            if ((cpt->u.reject.problem.data[2] !=
                TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR) &&
                (cpt->u.reject.problem.data[2] !=
                TCPPROB_SPEC_ERR_UNREC_INVOKE_ID))
            {
                cpt->ptype = TCPPT_TC_U_REJECT;
            }
            break;

        default:
            return (TCPPROB_SPEC_GEN_MISTYPED_COMP);
        }
        data ++;
        break;
        
    default:
        /* Unrecognized Comp: Returning 0x80 instead of UNREC_COMP
         * Since UNREC_COMP is 0x0 which is same as ITS_SUCCESS
         */
        return (TCPPROB_SPEC_GEN_UNREC_COMP | REJ_PROB_ENCODE_MASK);
    }

    eocBytes = data - cp;
    while (eocBytes < cLen && data[0] == 0 && data[1] == 0)
    {
        data += 2;
        eocBytes += 2;
    }

    if ((data - cp) != cLen)
    {
        /* Validate the Component portion Len here */
        return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
    }

    if (TCAP_VendorComponentSanityCheck(cpt) != ITS_SUCCESS)
    {
        return (TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
    }

    return (ITS_SUCCESS);
}

/*****************************************************************************
 *  Purpose:
 *      Decodes the dialogPortion array of octets and fills the appContext, 
 *      acLen, userInfo, uiLen, fromUser, accept, causeACName, hasPV, isResponse.
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
 *
 *
 *  Revision History:
 * ---------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * ---------------------------------------------------------------------------
 * sbabu     04-07-2005  WSC Bug ID#1170         TCAP decoding fails if the total 
 *                                               TCAP length is 128  
 * sbabu     04-11-2005  HelpDesk ID#742         Indeterminate Length Decode 
 *                                              
 ****************************************************************************/
static ITS_BOOLEAN 
ParseDP(ITS_USHORT ptype, ITS_OCTET *dp,
        ITS_OCTET *stop,
        ITS_OCTET *applicationContext, ITS_USHORT *acLen,
        ITS_OCTET *userInformation, ITS_USHORT *uiLen,
        ITS_BOOLEAN *fromUser, ITS_BOOLEAN *accept,
        ITS_BOOLEAN *causeACName, ITS_BOOLEAN *hasPV,
        ITS_BOOLEAN *isResponse)
{
    ITS_OCTET *data, *dlgData;
    ITS_UINT len, dtag, dlen, dlgLen, dlgLenSize, dpLenSize;
    ITS_UINT atag, etag, alen, elen;
    ITS_UINT totalLen, eocBytes;
    ITS_BOOLEAN isExtended = ITS_FALSE;

    *acLen = 0;
    *uiLen = 0;
    *fromUser = ITS_FALSE;
    *accept = ITS_FALSE;
    *hasPV = ITS_FALSE;
    *isResponse = ITS_FALSE;

    if (!dp)
    {
        /* Check me */
        return (ITS_TRUE);
    }

    data = dp;

    /* Check Dialog Portion Tag */
    if (*data != DIALOG_IDENT)
    {
        return (ITS_FALSE);
    }
    
    /* Skip Dialog Portion Tag */
    data ++;

    /* Get Dialog Portion Len */
    dlgLenSize = TCAP_GetLength(data, &dlen, stop, ITS_TRUE);
    data += dlgLenSize;
    dlgLen = dlen;

    totalLen = 1 + dlgLenSize + dlgLen;

    /* Mandatory params 

        -- External Tag
        -- External Len
        -- OIDTag
        -- OID Len
        -- Dialog-As-ID value or UniDialog-As-ID Value
        -- SingleASN.1 tag
        -- SingleASN.1 len
    */

    data += TCAP_GetTag(data, &etag, stop);

    if (etag == EXTERNAL_TAG)
    {
        data += TCAP_GetLength(data, &elen, stop, ITS_TRUE);
    }
    else
    {
        return (ITS_FALSE);
    }
    
    /* This is OK, since it's a Primitive */
    if (*data == OID_TAG)
    {
        data += 2;
    }
    else
    {
        return (ITS_FALSE);
    }

    if (ptype == TCPPT_TC_UNI)
    {
        if (memcmp(data, UnidialogueAsIDValue, 
                   sizeof(UnidialogueAsIDValue) / sizeof(ITS_OCTET)) == 0)
        {
            data += sizeof(UnidialogueAsIDValue) / sizeof(ITS_OCTET);
        }
        else
        {
            return (ITS_FALSE);
        }
    }
    else
    {
        if (memcmp(data, DialogueAsIDValue,
                   sizeof(DialogueAsIDValue) / sizeof(ITS_OCTET)) == 0)
        {
            data += sizeof(DialogueAsIDValue) / sizeof(ITS_OCTET);
        }
        else
        {
            return (ITS_FALSE);
        }
    }

    /* Single ASN.1 Tag */
    data += TCAP_GetTag(data, &atag, stop);
   
    /* Single ASN.1 Len */
    data += TCAP_GetLength(data, &alen, stop, ITS_TRUE);

    /* Start of the DLG PDU */
    dlgData = data;

    /* Get Dialog Tag */
    data += TCAP_GetTag(data, &dtag, stop);

    /* Get Dialog Len */
    dpLenSize = TCAP_GetLength(data, &dlen, stop, ITS_TRUE);
    data += dpLenSize;

    switch (dtag)
    {
    case DIALOG_REQUEST_TAG:
       
        if (ptype != TCPPT_TC_BEGIN && 
            ptype != TCPPT_TC_UNI)
        {
            return (ITS_FALSE);
        }

        /* check for Protocol Version Tag */
        if (*data == PROTOCOL_VERSION_TAG)
        {
            *hasPV = ITS_TRUE;
            data ++;
            data += TCAP_GetLength(data, &len, stop, ITS_FALSE);
            data += len;
        }

        if (*data == AC_NAME_TAG)
        {
            data ++;

            if (*data == EXT_LEN_FLAG)
            {
                isExtended = ITS_TRUE;
            }

            data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

            if (isExtended)
            {
                /* Strip of the EOC TAG && EOC Len in case of Indefinite
                 * Form
                 */
                if (data[len - 1] == 0 && data[len - 2] == 0)
                {
                    *acLen = len - 2;
                    memcpy(applicationContext, data, len - 2);
                }
            }
            else
            {
                *acLen = len;
                memcpy(applicationContext, data, len);
            }
            
            data += len;
        }
        else
        {
            return (ITS_FALSE);
        }

        if ((data - dp) < totalLen)
        {
            isExtended = ITS_FALSE;

            if (*data == USER_INFO_TAG)
            {
                data ++;

                if (*data == EXT_LEN_FLAG)
                {
                    isExtended = ITS_TRUE;
                }

                data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

                /* Strip of the EOC TAG && EOC Len in case of Indefinite
                 * Form
                 */
                if (isExtended)
                {
                    if (data[len - 1] == 0 && data[len - 2] == 0)
                    {
                        *uiLen = len - 2;
                        memcpy(userInformation, data, len - 2);
                    }
                }
                else
                {
                    *uiLen = len;
                    memcpy(userInformation, data, len);
                }
                data += len;
            }
        } 
        break;

    case DIALOG_RESPONSE_TAG:
       
        if (ptype == TCPPT_TC_BEGIN ||
            ptype == TCPPT_TC_UNI)
        {
            return (ITS_FALSE);
        }

        *isResponse = ITS_TRUE;

        /* check for Protocol Version Tag */

        if (*data == PROTOCOL_VERSION_TAG)
        {
           *hasPV = ITS_TRUE;
           data ++;
           data += TCAP_GetLength(data, &len, stop, ITS_FALSE);
           data += len;
        }

        /* Application Context */
        if (*data == AC_NAME_TAG)
        {
            data ++;

            if (*data == EXT_LEN_FLAG)
            {
                isExtended = ITS_TRUE;
            }

            data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

            /* Strip of the EOC TAG && EOC Len in case of Indefinite
             * Form
             */
            if (isExtended)
            {
                if (data[len - 1] == 0 && data[len - 2] == 0)
                {
                    *acLen = len - 2;
                    memcpy(applicationContext, data, len - 2);
                }
            }
            else
            {
                *acLen = len;
                memcpy(applicationContext, data, len);
            }

            data += len;
        }
        else
        {
            return (ITS_FALSE);
        }

        /* Result Tag */
        if (*data == RESULT_TAG)
        {
            data ++;
            /* Result len */
            data += TCAP_GetLength(data, &len, stop, ITS_TRUE);
            /* Result Value Tag & Len */
            data += 2;
            /* Result Value */
            if (*data == RESULT_ACCEPTED_TAG)
            {
                *accept = ITS_TRUE;
            }
            data ++;
        }
        else
        {
            return (ITS_FALSE);
        }

        /* Result Source Diagnostic Tag */
        if (*data == RESULT_SOURCE_DIAGNOSTIC_TAG)
        {
            data ++;
            /* Result Source Diagnostic Len */
            data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

            /*Dialog Service Diagnostic Tag */
            if (*data == DIALOG_SERVICE_USER_TAG)
            {
                *fromUser = ITS_TRUE;
                *causeACName = ITS_FALSE;
                data ++;
                data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

                /* Skip Integer Tag & Len */
                data += 2;

                /* Dialog Service User Diagnostic Value */
                if (*data == NULL_TAG)
                {
                    *accept = ITS_TRUE;
                }
                else if (*data == SERVICE_USER_CONTEXT_NAME_NOT_SUPPLIED)
                {
                    *causeACName = ITS_TRUE;
                }
                else
                {
                    *accept = ITS_FALSE;
                }
                data ++;
            }
            else
            {
                *fromUser = ITS_FALSE;
                data ++;
                data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

                /* Skip Integer Tag & Len */
                data += 2;

                /*Dialog Service User Diagnostic Value */
                if (*data == NULL_TAG)
                {
                    *accept = ITS_TRUE;
                }
                else
                {
                    *accept = ITS_FALSE;
                }
                data ++;
            }
        }
        else
        {
            return (ITS_FALSE);
        }
        if ((data - dp) < totalLen)        
        {
            isExtended = ITS_FALSE;
            /* User Info */
            if (*data == USER_INFO_TAG)
            {
                data ++;

                if (*data == EXT_LEN_FLAG)
                {
                    isExtended = ITS_TRUE;
                }

                data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

                /* Strip of the EOC TAG && EOC Len in case of Indefinite
                 * Form
                 */
                if (isExtended)
                {
                    if (data[len - 1] == 0 && data[len - 2] == 0)
                    {
                        *uiLen = len - 2;
                        memcpy(userInformation, data, len - 2);
                    }
                }
                else
                {
                    *uiLen = len;
                    memcpy(userInformation, data, len);
                }
                data += len;
            }
        }
        break;

    case DIALOG_ABORT_TAG:
       
        if (ptype != TCPPT_TC_U_ABORT &&
            ptype != TCPPT_TC_P_ABORT)
        {
            return (ITS_FALSE);
        }

        /* Abort Source Tag */
        if (*data == ABORT_SOURCE_TAG)
        {
            data ++;
            data += TCAP_GetLength(data, &len, stop, ITS_FALSE);
            /* Abort Source */
            if (*data == ABORT_SOURCE_PROVIDER)
            {
                *fromUser = ITS_FALSE;
            }
            else
            {
                *fromUser = ITS_TRUE;
            }
            data += len;
        }
        if ((data - dp) < totalLen)
        {
            isExtended = ITS_FALSE;
            /* User Info */
            if (*data == USER_INFO_TAG)
            {
                data ++;

                if (*data == EXT_LEN_FLAG)
                {
                    isExtended = ITS_TRUE;
                }

                data += TCAP_GetLength(data, &len, stop, ITS_TRUE);

                /* Strip of the EOC TAG && EOC Len in case of Indefinite
                 * Form
                 */
                if (isExtended)
                {
                    if (data[len - 1] == 0 && data[len - 2] == 0)
                    {
                        *uiLen = len - 2;
                        memcpy(userInformation, data, len - 2);
                    }
                }
                else
                {
                    *uiLen = len;
                    memcpy(userInformation, data, len);
                }
                data += len;
            }
        } 
        break;

    default:
        return (ITS_FALSE);
    }

    eocBytes = data - dp;

    while (eocBytes < totalLen && data[0] == 0 && data[1] == 0)
    {
        data += 2;
        eocBytes += 2;
    }

    if ((ITS_UINT)(data - dp) != totalLen)
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

/*****************************************************************************
 *  Purpose:
 *      Decodes the octet array into a TCAP_DLG structure. 
 *
 *  Input Parameters:
 *      pType, tp, dp, cpPresent, len, variant.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Pointer to TCAP_DLG structure.
 *
 *  Return Value:
 *      Success or Failure 
 *
 *
 *  Revision History:
 * ---------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * ---------------------------------------------------------------------------
 * sbabu     04-07-2005  WSC Bug Id#1170         TCAP encoding fails if the  
 *                                               total TCAP length is 128 
 *                                               
 ****************************************************************************/
SS7DLLAPI int
TCAP_CvtDataToDLG_CCITT(TCAP_DLG *dlg, ITS_OCTET *pType,
                        ITS_OCTET *tp, ITS_OCTET *dp, ITS_BOOLEAN cpPresent,
                        ITS_USHORT len, int variant)
{
    ITS_OCTET *tmp = NULL;
    ITS_BOOLEAN fromUser, accept, causeACName, hasPV, isResponse;
    ITS_UINT mLen, tidLen, causeLen;
    ITS_UINT tpLenSize;
    ITS_UINT tpLen;

    memset(dlg, 0, sizeof(TCAP_DLG));

    if (tp == NULL)
    {
        return (ITS_EPROTERR);
    }

    tmp = tp;

    /* Transaction Portion length validation */
    tpLenSize = TCAP_GetLength(tp + 1, &tpLen, tp + len, ITS_TRUE);

    if ((1 + tpLenSize + tpLen) != len) 
    {
        return (ITS_EPROTERR);
    }

    switch (*pType)
    {
    case TCPPT_TC_UNI:

        /* set the ptype */
        dlg->ptype = TCPPT_TC_UNI;
        /* Check for components */
        if (cpPresent)
        {
            dlg->u.uni.cpt_present = 1;
        }

        if (variant >= ITS_SECOND_GEN)
        {
            /* get the dialogue portion, if any */
            if (dp != NULL)
            {
                /* function to parse dp */
                if (!ParseDP(TCPPT_TC_UNI,
                             dp,
                             tp + len,
                             dlg->u.uni.ac_name.data,
                             &dlg->u.uni.ac_name.len,
                             dlg->u.uni.user_info.data,
                             &dlg->u.uni.user_info.len,
                             &fromUser, &accept,
                             &causeACName, &hasPV,
                             &isResponse))
                {
                    return (ITS_EPROTERR);
                }

                if (hasPV)
                {
                    dlg->u.uni.qos.indicator |= QOSI_PROT_VER;
                }
            }
        }

        break;

    case TCPPT_TC_BEGIN:

        /* set the ptype */
        dlg->ptype = TCPPT_TC_BEGIN;
        /* Check for components */
        if (cpPresent)
        {
            dlg->u.begin.cpt_present = 1;
        }

        if (variant >= ITS_SECOND_GEN)
        {
            /* get the dialogue portion, if any */
            if (dp != NULL)
            {
                /* function to parse dp */
                if (!ParseDP(TCPPT_TC_BEGIN,
                             dp,
                             tp + len,
                             dlg->u.begin.ac_name.data,
                             &dlg->u.begin.ac_name.len,
                             dlg->u.begin.user_info.data,
                             &dlg->u.begin.user_info.len,
                             &fromUser, &accept,
                             &causeACName, &hasPV,
                             &isResponse)) 
                {
                    return (ITS_EPROTERR);
                }

                if (hasPV)
                {
                    dlg->u.begin.qos.indicator |= QOSI_PROT_VER;
                }
            }
        }

        break;

    case TCPPT_TC_END:

        /* set the ptype */
        dlg->ptype = TCPPT_TC_END;
        if (cpPresent)
        {
            dlg->u.end.cpt_present = 1;
        }

        if (variant >= ITS_SECOND_GEN)
        {
            /* get the dialogue portion, if any */
            if (dp != NULL)
            {
                /* function to parse dp */
                if (!ParseDP(TCPPT_TC_END,
                             dp,
                             tp + len,
                             dlg->u.end.ac_name.data,
                             &dlg->u.end.ac_name.len,
                             dlg->u.end.user_info.data,
                             &dlg->u.end.user_info.len,
                             &fromUser, &accept,
                             &causeACName, &hasPV,
                             &isResponse))
                {
                    return (ITS_EPROTERR);
                }

                if (hasPV)
                {
                    dlg->u.end.qos.indicator |= QOSI_PROT_VER;
                }
            }
        }

        break;

    case TCPPT_TC_CONTINUE:

        /* set the ptype */
        dlg->ptype = TCPPT_TC_CONTINUE;
        if (cpPresent)
        {
            dlg->u.cont.cpt_present = 1;
        }

        if (variant >= ITS_SECOND_GEN)
        {
            /* get the dialogue portion, if any */
            if (dp != NULL)
            {
                /* function to parse dp */
                if (!ParseDP(TCPPT_TC_CONTINUE,
                             dp,
                             tp + len,
                             dlg->u.cont.ac_name.data,
                             &dlg->u.cont.ac_name.len,
                             dlg->u.cont.user_info.data,
                             &dlg->u.cont.user_info.len,
                             &fromUser, &accept,
                             &causeACName, &hasPV,
                             &isResponse))
                {
                    return (ITS_EPROTERR);
                }

                if (hasPV)
                {
                    dlg->u.cont.qos.indicator |= QOSI_PROT_VER;
                }
            }
        }

        break;

    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:

        /* tmp points to transactionPortion tp */
        /*
           0 -- MessageTypeTag
           1 -- TotalMessageLength
        */
        tmp ++;
        tmp += TCAP_GetLength(tmp, &mLen, tp + len, ITS_TRUE);

        /* check TID */
        if (*tmp != DTID_IDENT)
        {
            return (ITS_EPROTERR);
        }

        /* skip tag */
        tmp ++;
        /* skip Transaction ID */
        tmp += TCAP_GetLength(tmp, &tidLen, tp + len,ITS_FALSE);
        tmp += tidLen;

        if (*tmp == PABT_CAUSE_TAG)
        {
            /* set the ptype */
            dlg->ptype = TCPPT_TC_P_ABORT;
            tmp ++;
            tmp += TCAP_GetLength(tmp, &causeLen, tp + len,ITS_FALSE);
            /* Set the Abort Reason to P-Abort Cause */
            dlg->u.abort.abort_reason = *tmp;
            /* There is no dialog portion for P_ABORT */
        }
        else
        {
            /* set the ptype */
            dlg->ptype = TCPPT_TC_U_ABORT;
            if (variant >= ITS_SECOND_GEN)
            {
                /* get the dialogue portion, if any */
                if (dp != NULL)
                {
                    /* function to parse dp */
                    if (ParseDP(TCPPT_TC_U_ABORT,
                                 dp,
                                 tp + len,
                                 dlg->u.abort.ac_name.data,
                                 &dlg->u.abort.ac_name.len,
                                 dlg->u.abort.user_info.data,
                                 &dlg->u.abort.user_info.len,
                                 &fromUser, &accept,
                                 &causeACName, &hasPV, &isResponse))
                    {
                        if (!isResponse)
                        {
                            if (!fromUser)
                            {
                                dlg->ptype = TCPPT_TC_P_ABORT;
                            }
                            else
                            {
                                dlg->u.abort.abort_reason =
                                        TCPUABT_USER_DEFINED;
                            }

                            if (hasPV)
                            {
                                dlg->u.abort.qos.indicator |= QOSI_PROT_VER;
                            }

                        }
                        else
                        {
                            if (fromUser)
                            {
                                if (causeACName)
                                {
                                    dlg->u.abort.abort_reason =
                                        TCPUABT_AC_NOT_SUP;
                                }
                                else
                                {
                                    dlg->u.abort.abort_reason =
                                        TCPUABT_DLG_REFUSED;
                                }

                                if (hasPV)
                                {
                                    dlg->u.abort.qos.indicator |= QOSI_PROT_VER;
                                }
                            }
                            else
                            {
                                return (ITS_EPROTERR);
                            }
                        }
                   }
                   else
                   {
                        return (ITS_EPROTERR);
                   }
                }
            }

            else
            {
                /* Assume Blue Book */
            }
        }

        break;

    default:
        return (ITS_EPROTERR);
    }

    return (ITS_SUCCESS);
}
