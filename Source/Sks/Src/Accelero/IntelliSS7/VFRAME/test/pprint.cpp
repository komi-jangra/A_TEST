/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997-2003 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: pprint.cpp,v 1.1.1.1 2007-10-08 11:11:30 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.6  2005/03/21 13:50:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.5.2.1  2004/09/21 13:31:52  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 1.5  2004/09/21 09:46:57  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 1.4  2003/11/21 16:47:04  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 1.3  2003/11/17 15:53:57  mmiers
 * LOG: Debug build errors.
 * LOG:
 * LOG: Revision 1.2  2003/11/14 14:49:31  mmiers
 * LOG: Tweaking.
 * LOG:
 * LOG: Revision 1.1  2003/11/13 15:12:53  mmiers
 * LOG: Change to C++ build for linkage purposes.
 * LOG:
 * LOG: Revision 1.8  2003/11/12 19:09:50  mmiers
 * LOG: Add hook for dynamic linking.
 * LOG:
 * LOG: Revision 1.7  2003/10/31 10:19:31  yranade
 * LOG: Fix typo.
 * LOG:
 * LOG: Revision 1.6  2003/10/29 16:04:04  mmiers
 * LOG: Get the pretty printer working on Linux
 * LOG:
 * LOG: Revision 1.5  2003/10/29 15:20:05  mmiers
 * LOG: Linux build
 * LOG:
 * LOG: Revision 1.4  2003/10/23 20:38:26  mmiers
 * LOG: Add parameter printer indirection.
 * LOG:
 * LOG: Revision 1.3  2003/10/22 21:06:08  mmiers
 * LOG: Finish first pass at pretty printer.
 * LOG:
 * LOG: Revision 1.2  2003/10/21 20:32:54  mmiers
 * LOG: Flesh out a bit more.  Need switches and attention to the SIO.
 * LOG:
 * LOG: Revision 1.1  2003/10/17 21:47:59  mmiers
 * LOG: Debug the pretty printers.  Need to finish TCAP.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <its.h>
#include <its_dsm.h>
#include <its_pprint.h>
#include <its_dlsym.h>

#ident "$Id: pprint.cpp,v 1.1.1.1 2007-10-08 11:11:30 bsccs2 Exp $"

#include <vframe.h>

#if defined UNIT_TEST
/*
 * test pattern
 */
static ITS_OCTET testBytes[] =
{
    0xa3, 0xa9, 0x3f, 0x93, 0x01, 0x02, 0x02, 0x00, 0xf2, 0xf6, 0x0d, 0x09,
    0x80, 0x03, 0x0b, 0x10, 0x08, 0xc9, 0xf7, 0xd2, 0x03, 0x31, 0x27, 0x54,
    0x51, 0x05, 0xc3, 0xf7, 0x01, 0xfd, 0xf6, 0x52, 0xe2, 0x50, 0xc7, 0x04,
    0x01, 0xa7, 0x01, 0xaf, 0xe8, 0x48, 0xe9, 0x46, 0xcf, 0x01, 0x00, 0xd1,
    0x02, 0x64, 0x02, 0x30, 0x3d, 0xbf, 0x35, 0x07, 0x81, 0x05, 0x03, 0x31,
    0x27, 0x54, 0x51, 0x8d, 0x01, 0x01, 0x93, 0x07, 0x03, 0x10, 0x03, 0x31,
    0x27, 0x54, 0x51, 0x9f, 0x23, 0x04, 0x80, 0x03, 0x32, 0x06, 0x9f, 0x29,
    0x04, 0x04, 0x04, 0x30, 0x33, 0x9f, 0x34, 0x01, 0x11, 0x92, 0x07, 0x03,
    0x13, 0x03, 0x31, 0x27, 0x54, 0x51, 0x94, 0x01, 0x00, 0x96, 0x07, 0x72,
    0x10, 0x03, 0x31, 0x00, 0x06, 0x00
};
#endif

/*
 * family control
 */
static ITS_BOOLEAN doANSI = ITS_FALSE;
static ITS_BOOLEAN doCCITT = ITS_FALSE;
static ITS_BOOLEAN doPRC = ITS_FALSE;

/*
 * print control
 */
static ITS_BOOLEAN doMTP2 = ITS_FALSE;
static ITS_BOOLEAN doMTP3 = ITS_FALSE;
static ITS_BOOLEAN doSLTM = ITS_FALSE;
static ITS_BOOLEAN doSNMM = ITS_FALSE;
static ITS_BOOLEAN doISUP = ITS_FALSE;
static ITS_BOOLEAN doSCCP = ITS_FALSE;
static ITS_BOOLEAN doTCAP = ITS_FALSE;

/*
 * buffers
 */
static ITS_OCTET mtp2Bytes[MTP2_MAX_MSG_SIZE_ANSI];
static ITS_USHORT mtp2Len;
static ITS_OCTET mtp3Bytes[MTP2_MAX_MSG_SIZE_ANSI];
static ITS_USHORT mtp3Len;
static ITS_SCCP_IE ies[32];
static int ieCount;
static ITS_OCTET data[4096];
static ITS_USHORT len = 0;

/*
 * ring buffer
 */
static RINGBUF_Manager *buffer = NULL;

/*
 * dynamic linking
 */
static DLSYM_Manager *dlsym = NULL;
static ITS_DLSYM ppr = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dump ring bytes to stdout
 *
 *  Input Parameters:
 *      rb - ring buffer
 *      string - characters to dump
 *      len - length of string
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of bytes written
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
WriteStdout(RINGBUF_Manager *rb, char *string, ITS_UINT len)
{
    return printf("%*.*s", len, len, string);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print data as ANSI SS7 data.
 *
 *  Input Parameters:
 *      bytes = octet vector
 *      len = length of vector
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ANSI_SCCP))
static void
PrintANSI(ITS_OCTET *bytes, ITS_USHORT len)
{
    ITS_EVENT ev;
    MTP2_HEADER_ANSI mtp2;
    MTP3_HEADER_ANSI mtp3;
    ITS_OCTET mType;
    int ret, i;
    ITS_UINT byteCount = 1;
    ITS_OCTET sio = 0xFFU;

    /* is L2 present? */
    if (doMTP2)
    {
        ev.src = 0;
        ev.len = len;
        ev.data = bytes;

        ret = MTP2_Decode_ANSI(&ev, &mtp2,
                               &mtp2Bytes[1], &mtp2Len);

        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%AD", &byteCount, &mtp2);

            sio = mtp2.sio;
        }
    }

    /* is L3 present? */
    if (doMTP3)
    {
        /* if L2 was present, get the data we parsed above */
        if (doMTP2)
        {
            ev.len = mtp2Len;
            ev.data= mtp2Bytes;
            mtp2Bytes[0] = MTP3_MSG_USER_DATA;
        }
        /* otherwise the user bytes are L3 data */
        else
        {
            memcpy(&mtp3Bytes[1], bytes, len);
            mtp3Bytes[0] = MTP3_MSG_USER_DATA;
            ev.len = len + 1;
            ev.data = mtp3Bytes;
        }

        ret = MTP3_Decode_ANSI(&ev, &mType, &mtp3, mtp3Bytes, &mtp3Len);

        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%AN", &byteCount, &mtp3);

            sio = mtp3.sio;
        }
    }

    /* filter a bit based on what we have */
    switch (sio & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
        doSNMM = ITS_TRUE;
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
        doSLTM = ITS_TRUE;
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_SCCP:
        doSCCP = ITS_TRUE;
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_ISUP:
    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        doISUP = ITS_TRUE;
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_TUP:
    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_MTP_TEST:
    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
    case MTP3_SIO_SPARE5:
    default:
        break;
    }

    /* PDU is ISUP? */
    if (doISUP)
    {
        /* L3 data included?  Use the data we parsed above */
        if (doMTP3)
        {
            ev.len = mtp3Len;
            ev.data = mtp3Bytes;
        }
        /* otherwise the user passed ISUP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

        /* FIXME: Add ISUP printer */
        ret = -1;
        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%AI");
        }
    }

    /* PDU is SCCP? */
    if (doSCCP)
    {
        /* L3 data included?  Use the data we parsed above */
        if (doMTP3)
        {
            ev.len = mtp3Len;
            ev.data = mtp3Bytes;
        }
        /* otherwise the user passed SCCP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

        /*
         * This is ugly, but it's nice to have the
         * IE array here for TCAP printing.
         */
        switch (ev.data[0])
        {
        case SCCP_MSG_CR:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_CR_Desc_ANSI);
            break;

        case SCCP_MSG_CC:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_CC_Desc_ANSI);
            break;

        case SCCP_MSG_CREF:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_CREF_Desc_ANSI);
            break;

        case SCCP_MSG_RLSD:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_RLSD_Desc_ANSI);
            break;

        case SCCP_MSG_RLC:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_RLC_Desc_ANSI);
            break;

        case SCCP_MSG_DT1:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_DT1_Desc_ANSI);
            break;

        case SCCP_MSG_DT2:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_DT2_Desc_ANSI);
            break;

        case SCCP_MSG_AK:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_AK_Desc_ANSI);
            break;

        case SCCP_MSG_UDT:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_UDT_Desc_ANSI);
            break;

        case SCCP_MSG_XUDT:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_XUDT_Desc_ANSI);
            break;

        case SCCP_MSG_UDTS:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_UDTS_Desc_ANSI);
            break;

        case SCCP_MSG_XUDTS:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_XUDTS_Desc_ANSI);
            break;

        case SCCP_MSG_ED:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_ED_Desc_ANSI);
            break;

        case SCCP_MSG_EA:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_EA_Desc_ANSI);
            break;

        case SCCP_MSG_RSR:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_RSR_Desc_ANSI);
            break;

        case SCCP_MSG_RSC:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_RSC_Desc_ANSI);
            break;

        case SCCP_MSG_ERR:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_ERR_Desc_ANSI);
            break;

        case SCCP_MSG_IT:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_IT_Desc_ANSI);
            break;

        case SCCP_MSG_LUDT:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_LUDT_Desc_ANSI);
            break;

        case SCCP_MSG_LUDTS:
            ret = SCCP_DecodeMTP3_ANSI(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_LUDTS_Desc_ANSI);
            break;

        case SCCP_MSG_NOTICE:
        default:
            ret = ITS_ENOTFOUND;
            break;
        }

        if (ret == ITS_SUCCESS)
        {
            if (!doTCAP && ppr)
            {
                PPrint(buffer, "%AS", &byteCount, mType, ies, ieCount, ITS_FALSE);

                for (i = 0; i < ieCount; i++)
                {
                    if (ies[i].param_id == SCCP_PRM_DATA ||
                        ies[i].param_id == SCCP_PRM_LONG_DATA)
                    {
                        ev.len = ies[i].param_length;
                        ev.data = ies[i].param_data.userData.data;

                        if (ppr)
                        {
                            SCCP_PPrintProc p = (SCCP_PPrintProc)ppr;

                            (p)(buffer, &byteCount,
                                ies[i].param_data.userData.data,
                                ies[i].param_length);
                        }
                    }
                }
            }
            else if (!doTCAP)
            {
                PPrint(buffer, "%AS", &byteCount, mType, ies, ieCount, ITS_TRUE);
            }
            else
            {
                PPrint(buffer, "%AS", &byteCount, mType, ies, ieCount, ITS_FALSE);
            }
        }
    }

    /* print TCAP? */
    if (doTCAP)
    {
        /* SCCP included?  Use the USER_DATA we found above */
        if (doSCCP)
        {
            ev.data = NULL;
            ev.len = 0;
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_DATA ||
                    ies[i].param_id == SCCP_PRM_LONG_DATA)
                {
                    ev.len = ies[i].param_length;
                    ev.data = ies[i].param_data.userData.data;
                    break;
                }
            }
        }
        /* otherwise the user passed raw TCAP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

#if !defined(SPLIT_STACK)
        PPrint(buffer, "%AT", &byteCount, ev.data, ev.len, ppr);
#else
        PPrint(buffer, "%CT", &byteCount, ev.data, ev.len, ppr);
#endif
    }
}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print data as ANSI SS7 data.
 *
 *  Input Parameters:
 *      bytes = octet vector
 *      len = length of vector
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ITU_SCCP))
static void
PrintCCITT(ITS_OCTET *bytes, ITS_USHORT len)
{
    ITS_EVENT ev;
    MTP2_HEADER_CCITT mtp2;
    MTP3_HEADER_CCITT mtp3;
    ITS_OCTET mType;
    int ret, i;
    ITS_UINT byteCount = 1;
    ITS_OCTET sio = 0xFFU;

    /* L2 data included? */
    if (doMTP2)
    {
        ev.src = 0;
        ev.len = len;
        ev.data = bytes;

        ret = MTP2_Decode_CCITT(&ev, &mtp2,
                                &mtp2Bytes[1], &mtp2Len);

        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%CD", &byteCount, &mtp2);

            sio = mtp2.sio;
        }
    }

    /* L3 data included? */
    if (doMTP3)
    {
        /* L2 data included?  Use the data we parsed above */
        if (doMTP2)
        {
            ev.len = mtp2Len;
            ev.data= mtp2Bytes;
            mtp2Bytes[0] = MTP3_MSG_USER_DATA;
        }
        /* otherwise the user passed L3 data */
        else
        {
            memcpy(&mtp3Bytes[1], bytes, len);
            mtp3Bytes[0] = MTP3_MSG_USER_DATA;
            ev.len = len + 1;
            ev.data = mtp3Bytes;
        }

        ret = MTP3_Decode_CCITT(&ev, &mType, &mtp3, mtp3Bytes, &mtp3Len);

        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%CN", &byteCount, &mtp3);
            RINGBUF_Flush(buffer);

            sio = mtp3.sio;
        }
    }

    /* filter a bit based on what we have */
    switch (sio & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
        doSNMM = ITS_TRUE;
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
        doSLTM = ITS_TRUE;
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_SCCP:
        doSCCP = ITS_TRUE;
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_ISUP:
    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        doISUP = ITS_TRUE;
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_TUP:
    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_MTP_TEST:
    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
    case MTP3_SIO_SPARE5:
    default:
        break;
    }

    /* PDU is ISUP? */
    if (doISUP)
    {
        /* L3 data included?  Use the data we parsed above */
        if (doMTP3)
        {
            ev.len = mtp3Len;
            ev.data = mtp3Bytes;
        }
        /* otherwise the user passed ISUP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

        /* FIXME: Add ISUP printer */
        ret = -1;
        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%CI");
        }
    }

    /* SCCP data included? */
    if (doSCCP)
    {
        /* L3 data included?  Use the data we parsed above */
        if (doMTP3)
        {
            ev.len = mtp3Len;
            ev.data = mtp3Bytes;
        }
        /* otherwise the user passed SCCP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

        /*
         * This is ugly, but it's nice to have the
         * IE array here for TCAP printing.
         */
        switch (ev.data[0])
        {
        case SCCP_MSG_CR:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_CR_Desc_CCITT);
            break;

        case SCCP_MSG_CC:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_CC_Desc_CCITT);
            break;

        case SCCP_MSG_CREF:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_CREF_Desc_CCITT);
            break;

        case SCCP_MSG_RLSD:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_RLSD_Desc_CCITT);
            break;

        case SCCP_MSG_RLC:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_RLC_Desc_CCITT);
            break;

        case SCCP_MSG_DT1:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_DT1_Desc_CCITT);
            break;

        case SCCP_MSG_DT2:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_DT2_Desc_CCITT);
            break;

        case SCCP_MSG_AK:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_AK_Desc_CCITT);
            break;

        case SCCP_MSG_UDT:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_UDT_Desc_CCITT);
            break;

        case SCCP_MSG_XUDT:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_XUDT_Desc_CCITT);
            break;

        case SCCP_MSG_UDTS:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_UDTS_Desc_CCITT);
            break;

        case SCCP_MSG_XUDTS:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_XUDTS_Desc_CCITT);
            break;

        case SCCP_MSG_ED:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_ED_Desc_CCITT);
            break;

        case SCCP_MSG_EA:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_EA_Desc_CCITT);
            break;

        case SCCP_MSG_RSR:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_RSR_Desc_CCITT);
            break;

        case SCCP_MSG_RSC:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_RSC_Desc_CCITT);
            break;

        case SCCP_MSG_ERR:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_ERR_Desc_CCITT);
            break;

        case SCCP_MSG_IT:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_IT_Desc_CCITT);
            break;

        case SCCP_MSG_LUDT:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_LUDT_Desc_CCITT);
            break;

        case SCCP_MSG_LUDTS:
            ret = SCCP_DecodeMTP3_CCITT(ev.data, ev.len,
                                        &mType, ies, &ieCount,
                                        &SCCP_LUDTS_Desc_CCITT);
            break;

        case SCCP_MSG_NOTICE:
        default:
            ret = ITS_ENOTFOUND;
            break;
        }

        if (ret == ITS_SUCCESS)
        {
            if (!doTCAP && ppr)
            {
                PPrint(buffer, "%CS", &byteCount, mType, ies, ieCount, ITS_FALSE);

                for (i = 0; i < ieCount; i++)
                {
                    if (ies[i].param_id == SCCP_PRM_DATA ||
                        ies[i].param_id == SCCP_PRM_LONG_DATA)
                    {
                        ev.len = ies[i].param_length;
                        ev.data = ies[i].param_data.userData.data;

                        if (ppr)
                        {
                            SCCP_PPrintProc p = (SCCP_PPrintProc)ppr;

                            (p)(buffer, &byteCount,
                                ies[i].param_data.userData.data,
                                ies[i].param_length);
                        }
                    }
                }
            }
            else if (!doTCAP)
            {
                PPrint(buffer, "%CS", &byteCount, mType, ies, ieCount, ITS_TRUE);
            }
            else
            {
                PPrint(buffer, "%CS", &byteCount, mType, ies, ieCount, ITS_FALSE);
            }
        }
    }

    /* TCAP data included? */
    if (doTCAP)
    {
        /* SCCP data included?  Use the USER_DATA we found above */
        if (doSCCP)
        {
            ev.data = NULL;
            ev.len = 0;
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_DATA ||
                    ies[i].param_id == SCCP_PRM_LONG_DATA)
                {
                    ev.len = ies[i].param_length;
                    ev.data = ies[i].param_data.userData.data;
                    break;
                }
            }
        }
        /* otherwise the user passed raw TCAP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

#if !defined(SPLIT_STACK)
        PPrint(buffer, "%CT", &byteCount, ev.data, ev.len, ppr);
#else
        PPrint(buffer, "%AT", &byteCount, ev.data, ev.len, ppr);
#endif
    }
}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print data as ANSI SS7 data.
 *
 *  Input Parameters:
 *      bytes = octet vector
 *      len = length of vector
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if !defined(SPLIT_STACK)
static void
PrintPRC(ITS_OCTET *bytes, ITS_USHORT len)
{
    ITS_EVENT ev;
    MTP2_HEADER_PRC mtp2;
    MTP3_HEADER_PRC mtp3;
    ITS_OCTET mType;
    int ret, i;
    ITS_UINT byteCount = 1;
    ITS_OCTET sio = 0xFFU;

    /* L2 data included? */
    if (doMTP2)
    {
        ev.src = 0;
        ev.len = len;
        ev.data = bytes;

        ret = MTP2_Decode_PRC(&ev, &mtp2,
                              &mtp2Bytes[1], &mtp2Len);

        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%PD", &byteCount, &mtp2);

            sio = mtp2.sio;
        }
    }

    /* L3 data included? */
    if (doMTP3)
    {
        /* L2 included?  Use bytes parsed above */
        if (doMTP2)
        {
            ev.len = mtp2Len;
            ev.data= mtp2Bytes;
            mtp2Bytes[0] = MTP3_MSG_USER_DATA;
        }
        /* otherwise the user passed L3 data */
        else
        {
            memcpy(&mtp3Bytes[1], bytes, len);
            mtp3Bytes[0] = MTP3_MSG_USER_DATA;
            ev.len = len + 1;
            ev.data = mtp3Bytes;
        }

        ret = MTP3_Decode_PRC(&ev, &mType, &mtp3, mtp3Bytes, &mtp3Len);

        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%PN", &byteCount, &mtp3);

            sio = mtp3.sio;
        }
    }

    /* filter a bit based on what we have */
    switch (sio & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM:
        doSNMM = ITS_TRUE;
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_SLTM_REG:
    case MTP3_SIO_SLTM_SPEC:
        doSLTM = ITS_TRUE;
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_SCCP:
        doSCCP = ITS_TRUE;
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doISUP)
        {
            doISUP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_ISUP:
    case MTP3_SIO_BROAD_ISUP:
    case MTP3_SIO_SAT_ISUP:
        doISUP = ITS_TRUE;
        if (doSNMM)
        {
            doSNMM = ITS_FALSE;
        }
        if (doSLTM)
        {
            doSLTM = ITS_FALSE;
        }
        if (doSCCP)
        {
            doSCCP = ITS_FALSE;
        }
        if (doTCAP)
        {
            doTCAP = ITS_FALSE;
        }
        break;

    case MTP3_SIO_TUP:
    case MTP3_SIO_DUP_CIRC:
    case MTP3_SIO_DUP_FAC:
    case MTP3_SIO_MTP_TEST:
    case MTP3_SIO_SPARE3:
    case MTP3_SIO_SPARE4:
    case MTP3_SIO_ECIS6:
    case MTP3_SIO_PRIVATE:
    case MTP3_SIO_SPARE5:
    default:
        break;
    }

    /* PDU is ISUP? */
    if (doISUP)
    {
        /* L3 data included?  Use the data we parsed above */
        if (doMTP3)
        {
            ev.len = mtp3Len;
            ev.data = mtp3Bytes;
        }
        /* otherwise the user passed ISUP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

        /* FIXME: Add ISUP printer */
        ret = -1;
        if (ret == ITS_SUCCESS)
        {
            PPrint(buffer, "%PI");
        }
    }

    /* SCCP data included? */
    if (doSCCP)
    {
        /* L3 data included?  Use bytes parsed above */
        if (doMTP3)
        {
            ev.len = mtp3Len;
            ev.data = mtp3Bytes;
        }
        /* otherwise user passed SCCP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

        /*
         * This is ugly, but it's nice to have the
         * IE array here for TCAP printing.
         */
        switch (ev.data[0])
        {
        case SCCP_MSG_CR:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_CR_Desc_PRC);
            break;

        case SCCP_MSG_CC:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_CC_Desc_PRC);
            break;

        case SCCP_MSG_CREF:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_CREF_Desc_PRC);
            break;

        case SCCP_MSG_RLSD:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_RLSD_Desc_PRC);
            break;

        case SCCP_MSG_RLC:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                       &mType, ies, &ieCount,
                                       &SCCP_RLC_Desc_PRC);
            break;

        case SCCP_MSG_DT1:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_DT1_Desc_PRC);
            break;

        case SCCP_MSG_DT2:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_DT2_Desc_PRC);
            break;

        case SCCP_MSG_AK:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_AK_Desc_PRC);
            break;

        case SCCP_MSG_UDT:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_UDT_Desc_PRC);
            break;

        case SCCP_MSG_XUDT:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_XUDT_Desc_PRC);
            break;

        case SCCP_MSG_UDTS:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_UDTS_Desc_PRC);
            break;

        case SCCP_MSG_XUDTS:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_XUDTS_Desc_PRC);
            break;

        case SCCP_MSG_ED:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_ED_Desc_PRC);
            break;

        case SCCP_MSG_EA:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_EA_Desc_PRC);
            break;

        case SCCP_MSG_RSR:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_RSR_Desc_PRC);
            break;

        case SCCP_MSG_RSC:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_RSC_Desc_PRC);
            break;

        case SCCP_MSG_ERR:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_ERR_Desc_PRC);
            break;

        case SCCP_MSG_IT:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_IT_Desc_PRC);
            break;

        case SCCP_MSG_LUDT:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_LUDT_Desc_PRC);
            break;

        case SCCP_MSG_LUDTS:
            ret = SCCP_DecodeMTP3_PRC(ev.data, ev.len,
                                      &mType, ies, &ieCount,
                                      &SCCP_LUDTS_Desc_PRC);
            break;

        case SCCP_MSG_NOTICE:
        default:
            ret = ITS_ENOTFOUND;
            break;
        }

        if (ret == ITS_SUCCESS)
        {
            if (!doTCAP && ppr)
            {
                PPrint(buffer, "%PS", &byteCount, mType, ies, ieCount, ITS_FALSE);

                for (i = 0; i < ieCount; i++)
                {
                    if (ies[i].param_id == SCCP_PRM_DATA ||
                        ies[i].param_id == SCCP_PRM_LONG_DATA)
                    {
                        ev.len = ies[i].param_length;
                        ev.data = ies[i].param_data.userData.data;

                        if (ppr)
                        {
                            SCCP_PPrintProc p = (SCCP_PPrintProc)ppr;

                            (p)(buffer, &byteCount,
                                ies[i].param_data.userData.data,
                                ies[i].param_length);
                        }
                    }
                }
            }
            else if (!doTCAP)
            {
                PPrint(buffer, "%PS", &byteCount, mType, ies, ieCount, ITS_TRUE);
            }
            else
            {
                PPrint(buffer, "%PS", &byteCount, mType, ies, ieCount, ITS_FALSE);
            }
        }
    }

    /* TCAP included? */
    if (doTCAP)
    {
        /* SCCP included?  Use USER_DATA found above */
        if (doSCCP)
        {
            ev.data = NULL;
            ev.len = 0;
            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_DATA ||
                    ies[i].param_id == SCCP_PRM_LONG_DATA)
                {
                    ev.len = ies[i].param_length;
                    ev.data = ies[i].param_data.userData.data;
                    break;
                }
            }
        }
        /* otherwise the user passed raw TCAP data */
        else
        {
            ev.len = len;
            ev.data = bytes;
        }

        PPrint(buffer, "%PT", &byteCount, ev.data, ev.len, ppr);
    }
}
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print program usage
 *
 *  Input Parameters:
 *      name - program invocation
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
Usage(const char *name)
{
    printf("Usage: %s: -[23mlistACP] -d <libname> -p <printer>\n", name);
    printf("\n");
    printf("  where arguments are:\n");
    printf("    2 - data contains a level 2 PDU (MTP2)\n");
    printf("    3 - data contains a level 3 PDU (MTP3)\n");
    printf("    m - data contains a management message (SNMM)\n");
    printf("    l - data contains a link test message (SLTM)\n");
    printf("    i - data contains an ISUP message\n");
    printf("    s - data contains an SCCP message\n");
    printf("    t - data contains a TCAP message\n");
    printf("    A - the data is in ANSI format\n");
    printf("    C - the data is in CCITT/ITU format\n");
    printf("    P - the data is in PRC format (ITU with large point codes)\n");
    printf("    d - specify a shared object to find a print procedure in\n");
    printf("    p - specify a print procedure name\n");
    printf("\n");
    printf("Notes:\n");
    printf("  Certain combinations of flags aren't possible (e.g., turning\n");
    printf("SNMM and ISUP on at the same time).  If the SIO is present, by\n");
    printf("including L2/L3 data, the flags will be silently corrected in\n");
    printf("favor of what user part is indicated by the SIO.\n");
    printf("\n");
    printf("  The data is read from stdin after the program starts running.\n");
    printf("The input is assumed to be one two byte hex value per line.\n");
    printf("The data is parsed until an EOF condition appears on stdin, at\n");
    printf("which time the data is pretty printed to stdout.\n");
    printf("\n");
    printf("  When using dynamic print procedures, the shared object must\n");
    printf("be given as the following argument.  This is true for the print\n");
    printf("procedure as well.  Note that the shared object argument must\n");
    printf("be given BEFORE the print procedure.\n");
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Load the pretty print buffer
 *
 *  Input Parameters:
 *      name - program invocation
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      The assumption is that input is hexadecimal.
 *
 *  See Also:
 ****************************************************************************/
static void
LoadBuffer()
{
    char ch;
    ITS_OCTET val = 0;
    ITS_BOOLEAN haveVal = ITS_FALSE;

    while ((ch = getc(stdin)) != EOF)
    {
        switch (ch)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            val <<= 4;
            val += ch - '0';
            haveVal = ITS_TRUE;
            break;

        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            val <<= 4;
            val += 10 + ch - 'A';
            haveVal = ITS_TRUE;
            break;

        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            val <<= 4;
            val += 10 + ch - 'a';
            haveVal = ITS_TRUE;
            break;

        default:
            if (haveVal)
            {
                data[len] = val;
                len++;
                haveVal = ITS_FALSE;
                val = 0;
            }
            break;
        }
    }

    if (haveVal)
    {
        data[len] = val;
        len++;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Entry point
 *
 *  Input Parameters:
 *      argc - argument count
 *      argv - argument vector
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Standard main return values.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
main(int argc, char **argv)
{
    int ret, i;

    /* stub in */
    ret = ITS_AddFeature(itsDSM_StubImplClass);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to add DSM stub class: %d\n", ret);

        exit(EXIT_FAILURE);
    }

    /* ANSI class */
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ANSI_SCCP))
    ret = ITS_AddFeature(itsSS7STACK_ClassANSI);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to add ANSI stack class: %d\n", ret);

        exit(EXIT_FAILURE);
    }
#endif

    /* ITU class */
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ITU_SCCP))
    ret = ITS_AddFeature(itsSS7STACK_ClassCCITT);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to add ITU stack class: %d\n", ret);

        exit(EXIT_FAILURE);
    }
#endif

    /* PRC class */
#if !defined(SPLIT_STACK)
    ret = ITS_AddFeature(itsSS7STACK_ClassPRC);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Failed to add PRC stack class: %d\n", ret);

        exit(EXIT_FAILURE);
    }
#endif

    /* global start */
    ret = ITS_GlobalStart(0);
    if (ret != ITS_SUCCESS)
    {
        fprintf(stderr, "Can't initialize IntelliSS7: %d\n", ret);

        exit(EXIT_FAILURE);
    }

    /* create the ring buffer */
    if ((buffer = RINGBUF_InitManager(4096, 90, WriteStdout, NULL)) == NULL)
    {
        fprintf(stderr, "Can't create ring buffer\n");

        return (EXIT_FAILURE);
    }

    /* consume arguments */
    if (argc == 1)
    {
        Usage(argv[0]);

        exit(EXIT_FAILURE);
    }

    for (i = 1; i < argc; i++)
    {
        /* consume flags */
        if (argv[i][0] == '-')
        {
            switch (argv[i][1])
            {
            /* layers */
            case '2':
                doMTP2 = ITS_TRUE;
                break;

            case '3':
                doMTP3 = ITS_TRUE;
                break;

            case 'm':
                doSNMM = ITS_TRUE;
                break;

            case 'l':
                doSLTM = ITS_TRUE;
                break;

            case 's':
                doSCCP = ITS_TRUE;
                break;

            case 'i':
                doISUP = ITS_TRUE;
                break;

            case 't':
                doTCAP = ITS_TRUE;
                break;

            /* shared object */
            case 'd':
                i++;
                if (argv[i])
                {
                    dlsym = DLSYM_Create(argv[i]);
                    if (dlsym == NULL)
                    {
                        fprintf(stderr, "Can't open shared object '%s': %s.\n",
                                argv[i], DLSYM_Error());
                    }
                }
                break;

            /* print procedure */
            case 'p':
                i++;
                if (dlsym == NULL)
                {
                    fprintf(stderr, "No shared object specified.\n");
                }
                else
                {
                    if (argv[i])
                    {
                        ppr = DLSYM_Resolve(dlsym, argv[i]);
                        if (ppr == NULL)
                        {
                            fprintf(stderr, "Unable to resolve symbol '%s'\n",
                                    argv[i]);
                        }
                    }
                }
                break;

            /* family */
            case 'A':
                doANSI = ITS_TRUE;
                break;

            case 'C':
                doCCITT = ITS_TRUE;
                break;

            case 'P':
                doPRC = ITS_TRUE;
                break;

            default:
                Usage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
    }

    if (!doANSI && !doCCITT && !doPRC)
    {
        fprintf(stderr, "One of -A, -C, or -P must be specified.\n");

        exit(EXIT_FAILURE);
    }

    /* load the buffer */
    LoadBuffer();

    /* do the printing */
#if defined(UNIT_TEST)
    PrintANSI(testBytes, sizeof(testBytes));
#endif

#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ANSI_SCCP))
    if (doANSI)
    {
        PrintANSI(data, len);
    }
#endif
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ITU_SCCP))
    if (doCCITT)
    {
        PrintCCITT(data, len);
    }
#endif
#if !defined(SPLIT_STACK)
    if (doPRC)
    {
        PrintPRC(data, len);
    }
#endif

    /* cleanup */
    RINGBUF_FreeManager(buffer);

    ITS_GlobalStop();

#if !defined(SPLIT_STACK)
    ITS_RemFeature(itsSS7STACK_ClassPRC);
#endif
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ITU_SCCP))
    ITS_RemFeature(itsSS7STACK_ClassCCITT);
#endif
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(USE_ANSI_SCCP))
    ITS_RemFeature(itsSS7STACK_ClassANSI);
#endif

    return (EXIT_SUCCESS);
}
