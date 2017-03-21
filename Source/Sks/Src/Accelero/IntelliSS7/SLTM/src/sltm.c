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
 *  ID: $Id: sltm.c,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:24  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:50:31  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1.6.1  2004/12/16 02:28:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 14:04:24  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:31  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 15:59:00  mmiers
 * LOG: Changes for china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
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
 * LOG: Revision 3.1  2000/08/16 00:02:32  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:53  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/10/06 22:19:46  mmiers
 * LOG:
 * LOG:
 * LOG: Update new user part, integrate into licensing scheme.
 * LOG:
 * LOG: Revision 1.1  1999/10/06 20:35:46  mmiers
 * LOG:
 * LOG:
 * LOG: New user part.
 * LOG:
 *
 *****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_license.h>

#ident "$Id: sltm.c,v 1.1.1.1 2007-10-08 11:11:26 bsccs2 Exp $"

#if defined(ANSI)
#include <ansi/sltm.h>
#endif

#if defined(CCITT)
#include <itu/sltm.h>
#endif

#if defined(PRC)
#include <china/sltm.h>
#endif
#if defined(TTC)
#include <japan/sltm.h>
#endif

/*
 * header
 */
#define SLTM_PHDR   "-------------- SLTM ----------------\n"
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Encode_CCITT(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    ITS_USHORT size;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SLTM))
    {
        return (ITS_ENOLICENSE);
    }

    size = sizeof(ITS_OCTET);
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Decode_CCITT(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SLTM))
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
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  SLTM_MESSAGE *msg)
{
    int tmp, ret;
    ITS_OCTET len, i;

    /* header */
    ret = PPrint(rb, SLTM_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* HC0/HC1 */
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  "
                     "HC1 = %d | HC0 = %d",
                 *bCount, msg->headingCode,
                 SLTM_HC1_GET(*msg), SLTM_HC0_GET(*msg),
                 SLTM_HC1_GET(*msg), SLTM_HC0_GET(*msg));
    CHECK_RETURN(tmp, ret);

    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        /* Test message */
        tmp = PPrint(rb, "(HC0: TST, ");
        CHECK_RETURN(tmp, ret);

        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
            tmp = PPrint(rb, "HC1: SLTM)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* length */
            len = SLTM_LINK_TEST_GET_LENGTH_CCITT(msg->data.linkTest);
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  LI | spare  LI = %d\n",
                         *bCount, msg->data.linkTest.slc_li,
                         SLTM_LINK_TEST_GET_LENGTH_CCITT(msg->data.linkTest),
                         msg->data.linkTest.slc_li & 0x0FU,
                         SLTM_LINK_TEST_GET_LENGTH_CCITT(msg->data.linkTest));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* test data */
            for (i = 0; i < len; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  data = %3u '%c'\n",
                             *bCount, msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
            break;

        case SLTM_HC1_SLTA:
            tmp = PPrint(rb, "HC1: SLTA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* length */
            len = SLTM_LINK_TEST_GET_LENGTH_CCITT(msg->data.linkTest);
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  LI | spare  LI = %d\n",
                         *bCount, msg->data.linkTest.slc_li,
                         SLTM_LINK_TEST_GET_LENGTH_CCITT(msg->data.linkTest),
                         msg->data.linkTest.slc_li & 0x0FU,
                         SLTM_LINK_TEST_GET_LENGTH_CCITT(msg->data.linkTest));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* test data */
            for (i = 0; i < len; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  data = %3u '%c'\n",
                             *bCount, msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    default:
        /* Test message */
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Encode_ANSI(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    ITS_USHORT size;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SLTM))
    {
        return (ITS_ENOLICENSE);
    }

    size = sizeof(ITS_OCTET);
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Decode_ANSI(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SLTM))
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
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                 SLTM_MESSAGE *msg)
{
    int tmp, ret;
    ITS_OCTET len, i;

    /* header */
    ret = PPrint(rb, SLTM_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* HC0/HC1 */
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  "
                     "HC1 = %d | HC0 = %d",
                 *bCount, msg->headingCode,
                 SLTM_HC1_GET(*msg), SLTM_HC0_GET(*msg),
                 SLTM_HC1_GET(*msg), SLTM_HC0_GET(*msg));
    CHECK_RETURN(tmp, ret);

    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        /* Test message */
        tmp = PPrint(rb, "(HC0: TST, ");
        CHECK_RETURN(tmp, ret);

        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
            tmp = PPrint(rb, "HC1: SLTM)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* length */
            len = SLTM_LINK_TEST_GET_LENGTH_ANSI(msg->data.linkTest);
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  LI | SLC  LI = %d SLC = %d\n",
                         *bCount, msg->data.linkTest.slc_li,
                         SLTM_LINK_TEST_GET_LENGTH_ANSI(msg->data.linkTest),
                         SLTM_LINK_TEST_GET_SLC_ANSI(msg->data.linkTest),
                         SLTM_LINK_TEST_GET_LENGTH_ANSI(msg->data.linkTest),
                         SLTM_LINK_TEST_GET_SLC_ANSI(msg->data.linkTest));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* test data */
            for (i = 0; i < len; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  data = %3u '%c'\n",
                             *bCount,
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
            break;

        case SLTM_HC1_SLTA:
            tmp = PPrint(rb, "HC1: SLTA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* length */
            len = SLTM_LINK_TEST_GET_LENGTH_ANSI(msg->data.linkTest);
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  LI | SLC  LI = %d SLC = %d\n",
                         *bCount, msg->data.linkTest.slc_li,
                         SLTM_LINK_TEST_GET_LENGTH_ANSI(msg->data.linkTest),
                         SLTM_LINK_TEST_GET_SLC_ANSI(msg->data.linkTest),
                         SLTM_LINK_TEST_GET_LENGTH_ANSI(msg->data.linkTest),
                         SLTM_LINK_TEST_GET_SLC_ANSI(msg->data.linkTest));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* test data */
            for (i = 0; i < len; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  data = %3u '%c'\n",
                             *bCount, msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    default:
        /* Test message */
        tmp = PPrint(rb, "(HC0: UNKNOWN, HC1: ?) Decode Error!\n");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        return (ret);
    }

    return (ret);
}

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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Encode_PRC(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    ITS_USHORT size;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SLTM))
    {
        return (ITS_ENOLICENSE);
    }

    size = sizeof(ITS_OCTET);
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Decode_PRC(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SLTM))
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
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                SLTM_MESSAGE *msg)
{
    int tmp, ret;
    ITS_OCTET len, i;

    /* header */
    ret = PPrint(rb, SLTM_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* HC0/HC1 */
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  "
                     "HC1 = %d | HC0 = %d",
                 *bCount, msg->headingCode,
                 SLTM_HC1_GET(*msg), SLTM_HC0_GET(*msg),
                 SLTM_HC1_GET(*msg), SLTM_HC0_GET(*msg));
    CHECK_RETURN(tmp, ret);

    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        /* Test message */
        tmp = PPrint(rb, "(HC0: TST, ");
        CHECK_RETURN(tmp, ret);

        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
            tmp = PPrint(rb, "HC1: SLTM)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* length */
            len = SLTM_LINK_TEST_GET_LENGTH_PRC(msg->data.linkTest);
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  LI | spare  LI = %d\n",
                         *bCount, msg->data.linkTest.slc_li,
                         SLTM_LINK_TEST_GET_LENGTH_PRC(msg->data.linkTest),
                         msg->data.linkTest.slc_li & 0x0FU,
                         SLTM_LINK_TEST_GET_LENGTH_PRC(msg->data.linkTest));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* test data */
            for (i = 0; i < len; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  data = %3u '%c'\n",
                             *bCount, msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
            break;

        case SLTM_HC1_SLTA:
            tmp = PPrint(rb, "HC1: SLTA)\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* length */
            len = SLTM_LINK_TEST_GET_LENGTH_PRC(msg->data.linkTest);
            tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  LI | spare  LI = %d\n",
                         *bCount, msg->data.linkTest.slc_li,
                         SLTM_LINK_TEST_GET_LENGTH_PRC(msg->data.linkTest),
                         msg->data.linkTest.slc_li & 0x0FU,
                         SLTM_LINK_TEST_GET_LENGTH_PRC(msg->data.linkTest));
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            /* test data */
            for (i = 0; i < len; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  data = %3u '%c'\n",
                             *bCount, msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i],
                             msg->data.linkTest.pattern[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
            break;

        default:
            tmp = PPrint(rb, "HC1: UNKNOWN) Decode Error!\n");
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            return (ret);
        }
        break;

    default:
        /* Test message */
        tmp = PPrint(rb, "(HC0: UNKNOWN, HC1: ?) Decode Error!\n");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        return (ret);
    }

    return (ret);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Encode_TTC(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    ITS_USHORT size;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SLTM))
    {
        return (ITS_ENOLICENSE);
    }

    size = sizeof(ITS_OCTET);
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
    case SLTM_HC0_SRA_TTC:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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
 ****************************************************************************/
SS7DLLAPI int
SLTM_Decode_TTC(ITS_EVENT *ev, MTP3_HEADER *label, SLTM_MESSAGE *msg)
{
    int ret;
    ITS_USHORT size, rsize;
    ITS_OCTET mType;

    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SLTM))
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
    switch (SLTM_HC0_GET(*msg))
    {
    case SLTM_HC0_TST:
        switch (SLTM_HC1_GET(*msg))
        {
        case SLTM_HC1_SLTM:
        case SLTM_HC1_SLTA:
            size += sizeof(SLTM_LINK_TEST) - sizeof(ITS_OCTET) +
                        SLTM_LINK_TEST_GET_LENGTH(msg->data.linkTest);
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

#endif

