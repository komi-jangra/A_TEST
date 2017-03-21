/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
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
 *  ID: $Id: snmm.c,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:55  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:52  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:25  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:50:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1.6.2  2004/12/17 03:35:28  randresol
 * LOG: Comment out Pprint function due to compilation errors
 * LOG:
 * LOG: Revision 7.1.14.1.6.1  2004/12/16 02:44:09  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 14:14:10  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 16:14:33  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.6  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.5  2001/12/28 20:48:23  mmiers
 * LOG: CCITT uses the SLS field for SLC
 * LOG:
 * LOG: Revision 5.4  2001/12/06 23:50:43  mmiers
 * LOG: Dunno how I missed this.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/04/24 23:13:38  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:59  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/10/06 22:19:46  mmiers
 * LOG:
 * LOG:
 * LOG: Update new user part, integrate into licensing scheme.
 * LOG:
 * LOG: Revision 1.2  1999/10/06 22:08:58  mmiers
 * LOG:
 * LOG:
 * LOG: Correct codec.
 * LOG:
 * LOG: Revision 1.1  1999/10/06 20:23:01  mmiers
 * LOG:
 * LOG:
 * LOG: New user part.
 * LOG:
 * LOG: Revision 1.1  1999/10/06 15:59:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add new user part for signalling network management messages.
 * LOG:
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>

#ident "$Id: snmm.c,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $"

#include <its.h>
#include <its_license.h>

#if defined(ANSI)
#include <ansi/snmm.h>
#endif

#if defined(CCITT)
#include <itu/snmm.h>
#endif

#if defined(PRC)
#include <china/snmm.h>
#endif

#if defined(TTC)
#include <japan/snmm.h>
#endif


/*
 * header
 */
#define SNMM_PHDR   "-------------- SNMM ----------------\n"

#define CHECK_RETURN(r, cnt)    \
    if ((r) < 0)                \
    {                           \
        return (cnt);           \
    }                           \
    else                        \
    {                           \
        (cnt) += (r);           \
    }

#if defined(CCITT)

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Encode_CCITT(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    ITS_USHORT size = sizeof(ITS_OCTET);

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TFA:
#if defined(ANSI)
        case SNMM_HC1_TCP:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TCA:
#endif
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
#if defined(ANSI)
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
#endif
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    return MTP3_Encode_CCITT(ev, MTP3_MSG_USER_DATA, label,
                             (ITS_OCTET *)msg, size);
}

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Decode_CCITT(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    if ((ret = MTP3_Decode_CCITT(ev, &mType, label,
                                 (ITS_OCTET *)msg, &rsize)) != ITS_SUCCESS)
    {
        return (ret);
    }

    if (mType != MTP3_MSG_USER_DATA || rsize < sizeof(ITS_OCTET))
    {
        return (ITS_EPROTERR);
    }

    size = sizeof(ITS_OCTET);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TFA:
#if defined(ANSI)
        case SNMM_HC1_TCP:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TCA:
#endif
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
#if defined(ANSI)
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
#endif
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    if (size != rsize)
    {
        return (ITS_EPROTERR);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  SNMM_MESSAGE *msg)
{
    int tmp, ret;
    MTP3_POINT_CODE_CCITT pc;
    ITS_UINT pcVal;

    /* header */
    ret = PPrint(rb, SNMM_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* HC0/HC1 */
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  "
                     "HC1 = %d | HC0 = %d",
                 *bCount, msg->headingCode,
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg),
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg));
    CHECK_RETURN(tmp, ret);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        /* Changeover message */
        tmp = PPrint(rb, "(HC0: CHM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
            tmp = PPrint(rb, "HC1: COO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x   %b|%07b  spare | FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0] >> 7,
                         SNMM_CHANGEOVER_GET_FSN_CCITT(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_COA:
            tmp = PPrint(rb, "HC1: COA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x   %b|%07b  spare | FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0] >> 7,
                         SNMM_CHANGEOVER_GET_FSN_CCITT(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCO:
            tmp = PPrint(rb, "HC1: XCO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN lo. FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_CCITT(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 1 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.fsn[1],
                         msg->data.changeOver.fsn[1]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 2 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi\n",
                         *bCount, msg->data.changeOver.fsn[2],
                         msg->data.changeOver.fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCA:
            tmp = PPrint(rb, "HC1: XCA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN lo.  FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_CCITT(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 1 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.fsn[1],
                         msg->data.changeOver.fsn[1]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 3 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi\n",
                         *bCount, msg->data.changeOver.fsn[2],
                         msg->data.changeOver.fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBD:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE = %d\n",
                         *bCount, msg->data.changeBack.cbcode,
                         SNMM_CHANGEBACK_GET_CODE_CCITT(msg->data.changeBack),
                         SNMM_CHANGEBACK_GET_CODE_CCITT(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBA:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE = %d\n",
                         *bCount, msg->data.changeBack.cbcode,
                         SNMM_CHANGEBACK_GET_CODE_CCITT(msg->data.changeBack),
                         SNMM_CHANGEBACK_GET_CODE_CCITT(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_ECM:
        /* Emergency Changeover message */
        tmp = PPrint(rb, "(HC0: ECM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
            tmp = PPrint(rb, "HC1: ECO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_ECA:
            tmp = PPrint(rb, "HC1: ECA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_FCM:
        /* flow control */
        tmp = PPrint(rb, "(HC0: FCM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            tmp = PPrint(rb, "HC1: RCT)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFC:
            tmp = PPrint(rb, "HC1: TFC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferControl.dest;
            pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferControl.dest.data[0],
                         MTP3_PC_GET_NETWORK_CCITT(pc),
                         MTP3_PC_GET_CLUSTER_CCITT(pc),
                         MTP3_PC_GET_MEMBER_CCITT(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare | PC hi.  PC = 0x%04x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferControl.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* status */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Status = %d\n",
                         *bCount, msg->data.transferControl.status,
                         msg->data.transferControl.status);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TFM:
        /* transfer state */
        tmp = PPrint(rb, "(HC0: TFM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
            tmp = PPrint(rb, "HC1: TFP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_CCITT(pc),
                         MTP3_PC_GET_CLUSTER_CCITT(pc),
                         MTP3_PC_GET_MEMBER_CCITT(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare | PC hi.  PC = 0x%04x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFR:
            tmp = PPrint(rb, "HC1: TFR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_CCITT(pc),
                         MTP3_PC_GET_CLUSTER_CCITT(pc),
                         MTP3_PC_GET_MEMBER_CCITT(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare | PC hi.  PC = 0x%04x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFA:
            tmp = PPrint(rb, "HC1: TFA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_CCITT(pc),
                         MTP3_PC_GET_CLUSTER_CCITT(pc),
                         MTP3_PC_GET_MEMBER_CCITT(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare | PC hi.  PC = 0x%04x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_RSM:
        /* route state */
        tmp = PPrint(rb, "(HC0: RSM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
            tmp = PPrint(rb, "HC1: RSP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_CCITT(pc),
                         MTP3_PC_GET_CLUSTER_CCITT(pc),
                         MTP3_PC_GET_MEMBER_CCITT(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare | PC hi.  PC = 0x%04x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_RSR:
            tmp = PPrint(rb, "HC1: RSR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_CCITT(pc),
                         MTP3_PC_GET_CLUSTER_CCITT(pc),
                         MTP3_PC_GET_MEMBER_CCITT(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare | PC hi.  PC = 0x%04x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_MIM:
        /* link management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
            tmp = PPrint(rb, "HC1: LIN)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUN:
            tmp = PPrint(rb, "HC1: LUN)\n");
            CHECK_RETURN(tmp, ret);
           (*bCount)++;
            break;

        case SNMM_HC1_LIA:
            tmp = PPrint(rb, "HC1: LIA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUA:
            tmp = PPrint(rb, "HC1: LUA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LID:
            tmp = PPrint(rb, "HC1: LID)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LFU:
            tmp = PPrint(rb, "HC1: LFU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LLI:
            tmp = PPrint(rb, "HC1: LLI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LRI:
            tmp = PPrint(rb, "HC1: LRI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TRM:
        /* traffic management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
            tmp = PPrint(rb, "HC1: TRA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TRW:
            tmp = PPrint(rb, "HC1: TRW)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_DLM:
        /* data link management */
        tmp = PPrint(rb, "(HC0: DLM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            tmp = PPrint(rb, "HC1: DLC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* link */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Link lo.  Link = %d\n",
                         *bCount, msg->data.datalinkConnect.link[0],
                         msg->data.datalinkConnect.link[0],
                         SNMM_DATALINK_CONNECT_GET_LINK_CCITT(msg->data.datalinkConnect));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare | Link hi\n",
                         *bCount, msg->data.datalinkConnect.link[1],
                         msg->data.datalinkConnect.link[1] >> 4,
                         msg->data.datalinkConnect.link[1] & 0x0FU);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CSS:
            tmp = PPrint(rb, "HC1: CSS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNS:
            tmp = PPrint(rb, "HC1: CNS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNP:
            tmp = PPrint(rb, "HC1: CNP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_UFC:
        /* user flow */
        tmp = PPrint(rb, "(HC0: UFC, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            tmp = PPrint(rb, "HC1: UPU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.userPartUnavailable.dest;
            pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[0],
                         msg->data.userPartUnavailable.dest.data[0],
                         MTP3_PC_GET_NETWORK_CCITT(pc),
                         MTP3_PC_GET_CLUSTER_CCITT(pc),
                         MTP3_PC_GET_MEMBER_CCITT(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare | PC hi.  PC = 0x%04x\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[1],
                         msg->data.userPartUnavailable.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* user */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Cause = %d\n",
                         *bCount, msg->data.userPartUnavailable.user,
                         msg->data.userPartUnavailable.user);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    default:
        tmp = PPrint(rb, "(HC0: UNKNOWN, HC1: ?) Decode Error!\n");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        return (ret);
    }

    return (ret);
}

#endif

#if defined(ANSI)

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Encode_ANSI(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    ITS_USHORT size = sizeof(ITS_OCTET);

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            size += sizeof(SNMM_EMERG_CHANGEOVER);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TCP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TFA:
        case SNMM_HC1_TCA:
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            size += sizeof(SNMM_INHIBIT);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            size += sizeof(SNMM_DATALINK_CONN_ACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    return MTP3_Encode_ANSI(ev, MTP3_MSG_USER_DATA, label,
                            (ITS_OCTET *)msg, size);
}

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Decode_ANSI(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    if ((ret = MTP3_Decode_ANSI(ev, &mType, label,
                                (ITS_OCTET *)msg, &rsize)) != ITS_SUCCESS)
    {
        return (ret);
    }

    if (mType != MTP3_MSG_USER_DATA || rsize < sizeof(ITS_OCTET))
    {
        return (ITS_EPROTERR);
    }

    size = sizeof(ITS_OCTET);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            size += sizeof(SNMM_EMERG_CHANGEOVER);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TCP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TFA:
        case SNMM_HC1_TCA:
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            size += sizeof(SNMM_INHIBIT);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            size += sizeof(SNMM_DATALINK_CONN_ACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    if (size != rsize)
    {
        return (ITS_EPROTERR);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                 SNMM_MESSAGE *msg)
{
#if 0
    int tmp, ret;
    MTP3_POINT_CODE_ANSI pc;
    ITS_UINT pcVal;

    /* header */
    ret = PPrint(rb, SNMM_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* HC0/HC1 */
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  "
                     "HC1 = %d | HC0 = %d",
                 *bCount, msg->headingCode,
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg),
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg));
    CHECK_RETURN(tmp, ret);
    if (mType != MTP3_MSG_USER_DATA || rsize < sizeof(ITS_OCTET))
    {
        return (ITS_EPROTERR);
    }

    size = sizeof(ITS_OCTET);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TFA:
#if defined(ANSI)
        case SNMM_HC1_TCP:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TCA:
#endif
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
#if defined(ANSI)
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
#endif
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    if (size != rsize)
    {
        return (ITS_EPROTERR);
    }
#endif
    return (ITS_SUCCESS);
}

#endif

#if defined(TTC)

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Encode_TTC(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    ITS_USHORT size = sizeof(ITS_OCTET);

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TFA:
#if defined(ANSI)
        case SNMM_HC1_TCP:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TCA:
#endif
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
#if defined(ANSI)
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
#endif
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    return MTP3_Encode_TTC(ev, MTP3_MSG_USER_DATA, label,
                           (ITS_OCTET *)msg, size);
}

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Decode_TTC(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    if ((ret = MTP3_Decode_TTC(ev, &mType, label,
                               (ITS_OCTET *)msg, &rsize)) != ITS_SUCCESS)
    {
        return (ret);
    }

    if (mType != MTP3_MSG_USER_DATA || rsize < sizeof(ITS_OCTET))
    {
        return (ITS_EPROTERR);
    }

    size = sizeof(ITS_OCTET);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TFA:
#if defined(ANSI)
        case SNMM_HC1_TCP:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TCA:
#endif
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
#if defined(ANSI)
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
#endif
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    if (size != rsize)
    {
        return (ITS_EPROTERR);
    }

    return (ITS_SUCCESS);
}

#if 0
/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_PPrint_TTC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                SNMM_MESSAGE *msg)
{
    int tmp, ret;
    MTP3_POINT_CODE_TTC pc;
    ITS_UINT pcVal;

    /* header */
    ret = PPrint(rb, SNMM_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* HC0/HC1 */
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  "
                     "HC1 = %d | HC0 = %d",
                 *bCount, msg->headingCode,
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg),
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg));
    CHECK_RETURN(tmp, ret);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        /* Changeover message */
        tmp = PPrint(rb, "(HC0: CHM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
            tmp = PPrint(rb, "HC1: COO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x   %b|%07b  spare | FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0] >> 7,
                         SNMM_CHANGEOVER_GET_FSN_TTC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_COA:
            tmp = PPrint(rb, "HC1: COA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x   %b|%07b  spare | FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0] >> 7,
                         SNMM_CHANGEOVER_GET_FSN_TTC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCO:
            tmp = PPrint(rb, "HC1: XCO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN lo. FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_TTC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 1 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.fsn[1],
                         msg->data.changeOver.fsn[1]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 2 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi\n",
                         *bCount, msg->data.changeOver.fsn[2],
                         msg->data.changeOver.fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCA:
            tmp = PPrint(rb, "HC1: XCA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN lo.  FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_TTC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 1 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.fsn[1],
                         msg->data.changeOver.fsn[1]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 3 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi\n",
                         *bCount, msg->data.changeOver.fsn[2],
                         msg->data.changeOver.fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBD:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE = %d\n",
                         *bCount, msg->data.changeBack.cbcode,
                         SNMM_CHANGEBACK_GET_CODE_TTC(msg->data.changeBack),
                         SNMM_CHANGEBACK_GET_CODE_TTC(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBA:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE = %d\n",
                         *bCount, msg->data.changeBack.cbcode,
                         SNMM_CHANGEBACK_GET_CODE_TTC(msg->data.changeBack),
                         SNMM_CHANGEBACK_GET_CODE_TTC(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_ECM:
        /* Emergency Changeover message */
        tmp = PPrint(rb, "(HC0: ECM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
            tmp = PPrint(rb, "HC1: ECO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_ECA:
            tmp = PPrint(rb, "HC1: ECA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_FCM:
        /* flow control */
        tmp = PPrint(rb, "(HC0: FCM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            tmp = PPrint(rb, "HC1: RCT)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFC:
            tmp = PPrint(rb, "HC1: TFC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferControl.dest;
            pcVal = MTP3_PC_GET_VALUE_TTC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferControl.dest.data[0],
                         MTP3_PC_GET_NETWORK_TTC(pc),
                         MTP3_PC_GET_CLUSTER_TTC(pc),
                         MTP3_PC_GET_MEMBER_TTC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferControl.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferControl.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* status */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Status = %d\n",
                         *bCount, msg->data.transferControl.status,
                         msg->data.transferControl.status);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TFM:
        /* transfer state */
        tmp = PPrint(rb, "(HC0: TFM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
            tmp = PPrint(rb, "HC1: TFP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_TTC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_TTC(pc),
                         MTP3_PC_GET_CLUSTER_TTC(pc),
                         MTP3_PC_GET_MEMBER_TTC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFR:
            tmp = PPrint(rb, "HC1: TFR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_TTC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_TTC(pc),
                         MTP3_PC_GET_CLUSTER_TTC(pc),
                         MTP3_PC_GET_MEMBER_TTC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferState.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFA:
            tmp = PPrint(rb, "HC1: TFA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_TTC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_TTC(pc),
                         MTP3_PC_GET_CLUSTER_TTC(pc),
                         MTP3_PC_GET_MEMBER_TTC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferState.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_RSM:
        /* route state */
        tmp = PPrint(rb, "(HC0: RSM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
            tmp = PPrint(rb, "HC1: RSP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_TTC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_TTC(pc),
                         MTP3_PC_GET_CLUSTER_TTC(pc),
                         MTP3_PC_GET_MEMBER_TTC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_RSR:
            tmp = PPrint(rb, "HC1: RSR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_TTC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_TTC(pc),
                         MTP3_PC_GET_CLUSTER_TTC(pc),
                         MTP3_PC_GET_MEMBER_TTC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_MIM:
        /* link management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
            tmp = PPrint(rb, "HC1: LIN)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUN:
            tmp = PPrint(rb, "HC1: LUN)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LIA:
            tmp = PPrint(rb, "HC1: LIA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUA:
            tmp = PPrint(rb, "HC1: LUA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LID:
            tmp = PPrint(rb, "HC1: LID)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LFU:
            tmp = PPrint(rb, "HC1: LFU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LLI:
            tmp = PPrint(rb, "HC1: LLI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LRI:
            tmp = PPrint(rb, "HC1: LRI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TRM:
        /* traffic management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
            tmp = PPrint(rb, "HC1: TRA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TRW:
            tmp = PPrint(rb, "HC1: TRW)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_DLM:
        /* data link management */
        tmp = PPrint(rb, "(HC0: DLM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            tmp = PPrint(rb, "HC1: DLC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* link */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Link lo.  Link = %d\n",
                         *bCount, msg->data.datalinkConnect.link[0],
                         msg->data.datalinkConnect.link[0],
                         SNMM_DATALINK_CONNECT_GET_LINK_TTC(msg->data.datalinkConnect));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare | Link hi\n",
                         *bCount, msg->data.datalinkConnect.link[1],
                         msg->data.datalinkConnect.link[1] >> 4,
                         msg->data.datalinkConnect.link[1] & 0x0FU);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CSS:
            tmp = PPrint(rb, "HC1: CSS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNS:
            tmp = PPrint(rb, "HC1: CNS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNP:
            tmp = PPrint(rb, "HC1: CNP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_UFC:
        /* user flow */
        tmp = PPrint(rb, "(HC0: UFC, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            tmp = PPrint(rb, "HC1: UPU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.userPartUnavailable.dest;
            pcVal = MTP3_PC_GET_VALUE_TTC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[0],
                         msg->data.userPartUnavailable.dest.data[0],
                         MTP3_PC_GET_NETWORK_TTC(pc),
                         MTP3_PC_GET_CLUSTER_TTC(pc),
                         MTP3_PC_GET_MEMBER_TTC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[1],
                         msg->data.userPartUnavailable.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[2],
                         msg->data.userPartUnavailable.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* user */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Cause = %d\n",
                         *bCount, msg->data.userPartUnavailable.user,
                         msg->data.userPartUnavailable.user);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    default:
        tmp = PPrint(rb, "(HC0: UNKNOWN, HC1: ?) Decode Error!\n");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        return (ret);
    }

    return (ret);
}

#endif

#if 0
SS7DLLAPI int
SNMM_Decode_TTC(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{  
    int tmp, ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    if ((ret = MTP3_Decode_TTC(ev, &mType, label,
                               (ITS_OCTET *)msg, &rsize)) != ITS_SUCCESS)
    {
        return (ret);
    }

    if (mType != MTP3_MSG_USER_DATA || rsize < sizeof(ITS_OCTET))
    {
        return (ITS_EPROTERR);
    }

    size = sizeof(ITS_OCTET);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        /* Changeover message */
        tmp = PPrint(rb, "(HC0: CHM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
            tmp = PPrint(rb, "HC1: COO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  FSN lo / SLC = %d\n",
                         *bCount, msg->data.changeOver.slc_fsn[0],
                         msg->data.changeOver.slc_fsn[0] >> 4,
                         msg->data.changeOver.slc_fsn[0] & 0x0FU,
                         SNMM_CHANGEOVER_GET_SLC_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi. FSN = %d\n",
                         *bCount,  msg->data.changeOver.slc_fsn[1],
                         msg->data.changeOver.slc_fsn[1],
                         SNMM_CHANGEOVER_GET_FSN_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_COA:
            tmp = PPrint(rb, "HC1: COA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  FSN lo / SLC = %d\n",
                         *bCount, msg->data.changeOver.slc_fsn[0],
                         msg->data.changeOver.slc_fsn[0] >> 4,
                         msg->data.changeOver.slc_fsn[0] & 0x0FU,
                         SNMM_CHANGEOVER_GET_SLC_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi. FSN = %d\n",
                         *bCount,  msg->data.changeOver.slc_fsn[1],
                         msg->data.changeOver.slc_fsn[1],
                         SNMM_CHANGEOVER_GET_FSN_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCO:
            tmp = PPrint(rb, "HC1: XCO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  FSN lo / SLC = %d\n",
                         *bCount, msg->data.changeOver.slc_fsn[0],
                         msg->data.changeOver.slc_fsn[0] >> 4,
                         msg->data.changeOver.slc_fsn[0] & 0x0FU,
                         SNMM_CHANGEOVER_GET_SLC_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid. FSN = %d\n",
                         *bCount, msg->data.changeOver.slc_fsn[1],
                         msg->data.changeOver.slc_fsn[1],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 2 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.slc_fsn[2],
                         msg->data.changeOver.slc_fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 3 */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / FSN hi\n",
                         *bCount, msg->data.changeOver.slc_fsn[3],
                         msg->data.changeOver.slc_fsn[3] >> 4,
                         msg->data.changeOver.slc_fsn[3] & 0x0FU);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCA:
            tmp = PPrint(rb, "HC1: XCA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  FSN lo / SLC = %d\n",
                         *bCount, msg->data.changeOver.slc_fsn[0],
                         msg->data.changeOver.slc_fsn[0] >> 4,
                         msg->data.changeOver.slc_fsn[0] & 0x0FU,
                         SNMM_CHANGEOVER_GET_SLC_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid. FSN = %d\n",
                         *bCount, msg->data.changeOver.slc_fsn[1],
                         msg->data.changeOver.slc_fsn[1],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_ANSI(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 2 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.slc_fsn[2],
                         msg->data.changeOver.slc_fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 3 */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / FSN hi\n",
                         *bCount, msg->data.changeOver.slc_fsn[3],
                         msg->data.changeOver.slc_fsn[3] >> 4,
                         msg->data.changeOver.slc_fsn[3] & 0x0FU);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBD:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  CB CODE lo / SLC = %d\n",
                         *bCount, msg->data.changeBack.slc_cbcode[0],
                         msg->data.changeBack.slc_cbcode[0] >> 4,
                         msg->data.changeBack.slc_cbcode[0] & 0x0FU,
                         SNMM_CHANGEBACK_GET_SLC_ANSI(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE hi, CB CODE = %d\n",
                         *bCount, msg->data.changeBack.slc_cbcode[0],
                         msg->data.changeBack.slc_cbcode[1],
                         SNMM_CHANGEBACK_GET_CODE_ANSI(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBA:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  CB CODE lo / SLC = %d\n",
                         *bCount, msg->data.changeBack.slc_cbcode[0],
                         msg->data.changeBack.slc_cbcode[0] >> 4,
                         msg->data.changeBack.slc_cbcode[0] & 0x0FU,
                         SNMM_CHANGEBACK_GET_SLC_ANSI(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE hi, CB CODE = %d\n",
                         *bCount,  msg->data.changeBack.slc_cbcode[1],
                         msg->data.changeBack.slc_cbcode[1],
                         SNMM_CHANGEBACK_GET_CODE_ANSI(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        /* Changeover message */
        tmp = PPrint(rb, "(HC0: ECM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
            tmp = PPrint(rb, "HC1: ECO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.emergencyChangeOver.slc,
                         msg->data.emergencyChangeOver.slc >> 4,
                         SNMM_EMERG_CHANGEOVER_GET_SLC_ANSI(msg->data.emergencyChangeOver),
                         SNMM_EMERG_CHANGEOVER_GET_SLC_ANSI(msg->data.emergencyChangeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_ECA:
            tmp = PPrint(rb, "HC1: ECA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.emergencyChangeOver.slc,
                         msg->data.emergencyChangeOver.slc >> 4,
                         SNMM_EMERG_CHANGEOVER_GET_SLC_ANSI(msg->data.emergencyChangeOver),
                         SNMM_EMERG_CHANGEOVER_GET_SLC_ANSI(msg->data.emergencyChangeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        /* flow control */
        tmp = PPrint(rb, "(HC0: FCM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            tmp = PPrint(rb, "HC1: RCT)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFC:
            tmp = PPrint(rb, "HC1: TFC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferControl.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferControl.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferControl.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferControl.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* status */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Status = %d\n",
                         *bCount, msg->data.transferControl.status,
                         msg->data.transferControl.status);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TFM:
        /* transfer state */
        tmp = PPrint(rb, "(HC0: TFM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
            tmp = PPrint(rb, "HC1: TFP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFR:
            tmp = PPrint(rb, "HC1: TFR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFA:
            tmp = PPrint(rb, "HC1: TFA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TCP:
            tmp = PPrint(rb, "HC1: TCP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferState.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TCR:
            tmp = PPrint(rb, "HC1: TCR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferState.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TCA:
            tmp = PPrint(rb, "HC1: TCA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferState.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_RSM:
        /* route state */
        tmp = PPrint(rb, "(HC0: RSM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
            tmp = PPrint(rb, "HC1: RSP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_RSR:
            tmp = PPrint(rb, "HC1: RSR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_RCP:
            tmp = PPrint(rb, "HC1: RCP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_RCR:
            tmp = PPrint(rb, "HC1: RCR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_MIM:
        /* link management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
            tmp = PPrint(rb, "HC1: LIN)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUN:
            tmp = PPrint(rb, "HC1: LUN)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LIA:
            tmp = PPrint(rb, "HC1: LIA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUA:
            tmp = PPrint(rb, "HC1: LUA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LID:
            tmp = PPrint(rb, "HC1: LID)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LFU:
            tmp = PPrint(rb, "HC1: LFU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LLI:
            tmp = PPrint(rb, "HC1: LLI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LRI:
            tmp = PPrint(rb, "HC1: LRI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* SLC */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare / SLC = %d\n",
                         *bCount, msg->data.managementInhibit.slc,
                         msg->data.managementInhibit.slc >> 4,
                         msg->data.managementInhibit.slc & 0x0FU,
                         SNMM_INHIBIT_GET_SLC_ANSI(msg->data.managementInhibit));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;


        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TRM:
        /* traffic management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
            tmp = PPrint(rb, "HC1: TRA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TRW:
            tmp = PPrint(rb, "HC1: TRW)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_DLM:
        /* data link management */
        tmp = PPrint(rb, "(HC0: DLM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            tmp = PPrint(rb, "HC1: DLC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* link */
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  Link lo | SLC.  Link = %d SLC = %d\n",
                         *bCount, msg->data.datalinkConnect.slc_link[0],
                         msg->data.datalinkConnect.slc_link[0] >> 4,
                         msg->data.datalinkConnect.slc_link[0] & 0x0FU,
                         SNMM_DATALINK_CONNECT_GET_LINK_ANSI(msg->data.datalinkConnect));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  Link mid\n",
                         *bCount, msg->data.datalinkConnect.slc_link[1],
                         msg->data.datalinkConnect.slc_link[1]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %06b|%02b  spare | Link hi\n",
                         *bCount, msg->data.datalinkConnect.slc_link[2],
                         msg->data.datalinkConnect.slc_link[2] >> 2,
                         msg->data.datalinkConnect.slc_link[2] & 0x03U);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CSS:
            tmp = PPrint(rb, "HC1: CSS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNS:
            tmp = PPrint(rb, "HC1: CNS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNP:
            tmp = PPrint(rb, "HC1: CNP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_UFC:
        /* user flow */
        tmp = PPrint(rb, "(HC0: UFC, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            tmp = PPrint(rb, "HC1: UPU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.userPartUnavailable.dest;
            pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[0],
                         msg->data.userPartUnavailable.dest.data[0],
                         MTP3_PC_GET_NETWORK_ANSI(pc),
                         MTP3_PC_GET_CLUSTER_ANSI(pc),
                         MTP3_PC_GET_MEMBER_ANSI(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[1],
                         msg->data.userPartUnavailable.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[2],
                         msg->data.userPartUnavailable.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* user */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Cause = %d\n",
                         *bCount, msg->data.userPartUnavailable.user,
                         msg->data.userPartUnavailable.user);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    default:
        tmp = PPrint(rb, "(HC0: UNKNOWN, HC1: ?) Decode Error!\n");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        return (ret);
    }

    return (ret);
}

#endif

#endif

#if defined(PRC)

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Encode_PRC(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    ITS_USHORT size = sizeof(ITS_OCTET);

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TFA:
#if defined(ANSI)
        case SNMM_HC1_TCP:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TCA:
#endif
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
#if defined(ANSI)
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
#endif
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    return MTP3_Encode_PRC(ev, MTP3_MSG_USER_DATA, label,
                           (ITS_OCTET *)msg, size);
}

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_Decode_PRC(ITS_EVENT *ev, MTP3_HEADER *label, SNMM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SNMM))
    {
        return (ITS_ENOLICENSE);
    }

    if ((ret = MTP3_Decode_PRC(ev, &mType, label,
                               (ITS_OCTET *)msg, &rsize)) != ITS_SUCCESS)
    {
        return (ret);
    }

    if (mType != MTP3_MSG_USER_DATA || rsize < sizeof(ITS_OCTET))
    {
        return (ITS_EPROTERR);
    }

    size = sizeof(ITS_OCTET);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
        case SNMM_HC1_COA:
            size += sizeof(SNMM_CHANGEOVER) - 2 * sizeof(ITS_OCTET);
            break;

        case SNMM_HC1_XCO:
        case SNMM_HC1_XCA:
            size += sizeof(SNMM_CHANGEOVER);
            break;

        case SNMM_HC1_CBD:
        case SNMM_HC1_CBA:
            size += sizeof(SNMM_CHANGEBACK);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_ECM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
        case SNMM_HC1_ECA:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_FCM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            break;

        case SNMM_HC1_TFC:
            size += sizeof(SNMM_TRANSFER_CONTROL);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TFM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
        case SNMM_HC1_TFR:
        case SNMM_HC1_TFA:
#if defined(ANSI)
        case SNMM_HC1_TCP:
        case SNMM_HC1_TCR:
        case SNMM_HC1_TCA:
#endif
            size += sizeof(SNMM_TRANSFER_STATE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_RSM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
        case SNMM_HC1_RSR:
#if defined(ANSI)
        case SNMM_HC1_RCP:
        case SNMM_HC1_RCR:
#endif
            size += sizeof(SNMM_ROUTE_SET_TEST);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_MIM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
        case SNMM_HC1_LUN:
        case SNMM_HC1_LIA:
        case SNMM_HC1_LUA:
        case SNMM_HC1_LID:
        case SNMM_HC1_LFU:
        case SNMM_HC1_LLI:
        case SNMM_HC1_LRI:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_TRM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
        case SNMM_HC1_TRW:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_DLM:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            size += sizeof(SNMM_DATALINK_CONNECT);
            break;

        case SNMM_HC1_CSS:
        case SNMM_HC1_CNS:
        case SNMM_HC1_CNP:
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    case SNMM_HC0_UFC:
        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            size += sizeof(SNMM_USER_PART_UNAVAILABLE);
            break;

        default:
            return (ITS_EINVALIDARGS);
        }
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    if (size != rsize)
    {
        return (ITS_EPROTERR);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SNMM_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                SNMM_MESSAGE *msg)
{
    int tmp, ret;
    MTP3_POINT_CODE_PRC pc;
    ITS_UINT pcVal;

    /* header */
    ret = PPrint(rb, SNMM_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* HC0/HC1 */
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  "
                     "HC1 = %d | HC0 = %d",
                 *bCount, msg->headingCode,
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg),
                 SNMM_HC1_GET(*msg), SNMM_HC0_GET(*msg));
    CHECK_RETURN(tmp, ret);

    switch (SNMM_HC0_GET(*msg))
    {
    case SNMM_HC0_CHM:
        /* Changeover message */
        tmp = PPrint(rb, "(HC0: CHM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_COO:
            tmp = PPrint(rb, "HC1: COO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x   %b|%07b  spare | FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0] >> 7,
                         SNMM_CHANGEOVER_GET_FSN_PRC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_COA:
            tmp = PPrint(rb, "HC1: COA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x   %b|%07b  spare | FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0] >> 7,
                         SNMM_CHANGEOVER_GET_FSN_PRC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCO:
            tmp = PPrint(rb, "HC1: XCO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN lo. FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_PRC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 1 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.fsn[1],
                         msg->data.changeOver.fsn[1]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 2 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi\n",
                         *bCount, msg->data.changeOver.fsn[2],
                         msg->data.changeOver.fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_XCA:
            tmp = PPrint(rb, "HC1: XCA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* FSN */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN lo.  FSN = %d\n",
                         *bCount, msg->data.changeOver.fsn[0],
                         msg->data.changeOver.fsn[0],
                         SNMM_CHANGEOVER_GET_FSN_SAAL_PRC(msg->data.changeOver));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 1 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN mid\n",
                         *bCount, msg->data.changeOver.fsn[1],
                         msg->data.changeOver.fsn[1]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* byte 3 */
            tmp = PPrint(rb, " %3d.  %02x    %08b  FSN hi\n",
                         *bCount, msg->data.changeOver.fsn[2],
                         msg->data.changeOver.fsn[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBD:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE = %d\n",
                         *bCount, msg->data.changeBack.cbcode,
                         SNMM_CHANGEBACK_GET_CODE_PRC(msg->data.changeBack),
                         SNMM_CHANGEBACK_GET_CODE_PRC(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CBA:
            tmp = PPrint(rb, "HC1: CBD)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* CB CODE */
            tmp = PPrint(rb, " %3d.  %02x    %08b  CB CODE = %d\n",
                         *bCount, msg->data.changeBack.cbcode,
                         SNMM_CHANGEBACK_GET_CODE_PRC(msg->data.changeBack),
                         SNMM_CHANGEBACK_GET_CODE_PRC(msg->data.changeBack));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_ECM:
        /* Emergency Changeover message */
        tmp = PPrint(rb, "(HC0: ECM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_ECO:
            tmp = PPrint(rb, "HC1: ECO)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_ECA:
            tmp = PPrint(rb, "HC1: ECA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_FCM:
        /* flow control */
        tmp = PPrint(rb, "(HC0: FCM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RCT:
            tmp = PPrint(rb, "HC1: RCT)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFC:
            tmp = PPrint(rb, "HC1: TFC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferControl.dest;
            pcVal = MTP3_PC_GET_VALUE_PRC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferControl.dest.data[0],
                         MTP3_PC_GET_NETWORK_PRC(pc),
                         MTP3_PC_GET_CLUSTER_PRC(pc),
                         MTP3_PC_GET_MEMBER_PRC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferControl.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferControl.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* status */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Status = %d\n",
                         *bCount, msg->data.transferControl.status,
                         msg->data.transferControl.status);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TFM:
        /* transfer state */
        tmp = PPrint(rb, "(HC0: TFM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TFP:
            tmp = PPrint(rb, "HC1: TFP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_PRC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferControl.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_PRC(pc),
                         MTP3_PC_GET_CLUSTER_PRC(pc),
                         MTP3_PC_GET_MEMBER_PRC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferControl.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferControl.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFR:
            tmp = PPrint(rb, "HC1: TFR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_PRC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_PRC(pc),
                         MTP3_PC_GET_CLUSTER_PRC(pc),
                         MTP3_PC_GET_MEMBER_PRC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferState.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TFA:
            tmp = PPrint(rb, "HC1: TFA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.transferState.dest;
            pcVal = MTP3_PC_GET_VALUE_PRC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.transferState.dest.data[0],
                         msg->data.transferState.dest.data[0],
                         MTP3_PC_GET_NETWORK_PRC(pc),
                         MTP3_PC_GET_CLUSTER_PRC(pc),
                         MTP3_PC_GET_MEMBER_PRC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.transferState.dest.data[1],
                         msg->data.transferState.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.transferState.dest.data[2],
                         msg->data.transferState.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_RSM:
        /* route state */
        tmp = PPrint(rb, "(HC0: RSM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_RSP:
            tmp = PPrint(rb, "HC1: RSP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_PRC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_PRC(pc),
                         MTP3_PC_GET_CLUSTER_PRC(pc),
                         MTP3_PC_GET_MEMBER_PRC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_RSR:
            tmp = PPrint(rb, "HC1: RSR)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.routeSetTest.dest;
            pcVal = MTP3_PC_GET_VALUE_PRC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.routeSetTest.dest.data[0],
                         msg->data.routeSetTest.dest.data[0],
                         MTP3_PC_GET_NETWORK_PRC(pc),
                         MTP3_PC_GET_CLUSTER_PRC(pc),
                         MTP3_PC_GET_MEMBER_PRC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.routeSetTest.dest.data[1],
                         msg->data.routeSetTest.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.routeSetTest.dest.data[2],
                         msg->data.routeSetTest.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_MIM:
        /* link management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_LIN:
            tmp = PPrint(rb, "HC1: LIN)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUN:
            tmp = PPrint(rb, "HC1: LUN)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LIA:
            tmp = PPrint(rb, "HC1: LIA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LUA:
            tmp = PPrint(rb, "HC1: LUA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LID:
            tmp = PPrint(rb, "HC1: LID)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LFU:
            tmp = PPrint(rb, "HC1: LFU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LLI:
            tmp = PPrint(rb, "HC1: LLI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_LRI:
            tmp = PPrint(rb, "HC1: LRI)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_TRM:
        /* traffic management */
        tmp = PPrint(rb, "(HC0: MIM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_TRA:
            tmp = PPrint(rb, "HC1: TRA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_TRW:
            tmp = PPrint(rb, "HC1: TRW)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_DLM:
        /* data link management */
        tmp = PPrint(rb, "(HC0: DLM, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_DLC:
            tmp = PPrint(rb, "HC1: DLC)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* link */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Link lo.  Link = %d\n",
                         *bCount, msg->data.datalinkConnect.link[0],
                         msg->data.datalinkConnect.link[0],
                         SNMM_DATALINK_CONNECT_GET_LINK_PRC(msg->data.datalinkConnect));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  spare | Link hi\n",
                         *bCount, msg->data.datalinkConnect.link[1],
                         msg->data.datalinkConnect.link[1] >> 4,
                         msg->data.datalinkConnect.link[1] & 0x0FU);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CSS:
            tmp = PPrint(rb, "HC1: CSS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNS:
            tmp = PPrint(rb, "HC1: CNS)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        case SNMM_HC1_CNP:
            tmp = PPrint(rb, "HC1: CNP)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    case SNMM_HC0_UFC:
        /* user flow */
        tmp = PPrint(rb, "(HC0: UFC, ");
        CHECK_RETURN(tmp, ret);

        switch (SNMM_HC1_GET(*msg))
        {
        case SNMM_HC1_UPU:
            tmp = PPrint(rb, "HC1: UPU)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* point code */
            pc = msg->data.userPartUnavailable.dest;
            pcVal = MTP3_PC_GET_VALUE_PRC(pc);
            tmp = PPrint(rb, " %3d.  %02x    %08b  PC lo.  PC = %d-%d-%d\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[0],
                         msg->data.userPartUnavailable.dest.data[0],
                         MTP3_PC_GET_NETWORK_PRC(pc),
                         MTP3_PC_GET_CLUSTER_PRC(pc),
                         MTP3_PC_GET_MEMBER_PRC(pc));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC mid.  PC = 0x%06x\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[1],
                         msg->data.userPartUnavailable.dest.data[1],
                         pcVal);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            tmp = PPrint(rb, " %3d.  %02x    %08b  PC hi.\n",
                         *bCount, msg->data.userPartUnavailable.dest.data[2],
                         msg->data.userPartUnavailable.dest.data[2]);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* user */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Cause = %d\n",
                         *bCount, msg->data.userPartUnavailable.user,
                         msg->data.userPartUnavailable.user);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    default:
        tmp = PPrint(rb, "(HC0: UNKNOWN, HC1: ?) Decode Error!\n");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        return (ret);
    }

    return (ret);
}
#endif

