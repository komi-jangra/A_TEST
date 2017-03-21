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
 *
 *  ID: $Id: tcap.c,v 1.1.1.1 2007-10-08 11:11:28 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:57  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:31  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.3  2005/04/08 09:10:02  adutta
 * LOG: Fix for BCGI Bug ( for invk. id. length null)
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:38:43  mmanikandan
 * LOG: Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.16  2005/03/21 13:50:37  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.3.6.2.6.3  2005/02/24 12:37:05  mmanikandan
 * LOG: PPrint is modified for TID display.
 * LOG:
 * LOG: Revision 7.3.2.3.6.2.6.2  2005/02/21 11:25:48  mmanikandan
 * LOG: Printing the dialog data in PPrint is modified.
 * LOG:
 * LOG: Revision 7.3.2.3.6.2.6.1  2004/12/16 03:03:03  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.3.2.3.6.2  2004/09/21 14:31:43  mmanikandan
 * LOG: Propagating pprint from current (linker error is resolved).
 * LOG:
 * LOG: Revision 7.3.2.3.6.1  2004/09/21 09:36:09  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.3.2.3  2003/06/10 11:26:33  yranade
 * LOG: Added abnormal dlg and no common dlg in sanity check for P-Abort Cause
 * LOG: in Abort for CCITT.
 * LOG:
 * LOG: Revision 7.3.2.2  2003/05/30 12:06:45  yranade
 * LOG: Sanity Check added for P-Abort Cause in Abort for CCITT.
 * LOG:
 * LOG: Revision 7.3.2.1  2003/04/23 06:20:49  vjatti
 * LOG: Added Sanity Check for R_Reject component for CCITT.
 * LOG:
 * LOG: Revision 7.3  2003/01/07 15:26:07  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/09/16 18:37:49  mmiers
 * LOG: Add U-ABORT for ANSI
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/07/16 16:17:27  labuser
 * LOG: ANSI-96 changes tested in PR5 ported to current. Tested. (clin)
 * LOG:
 * LOG: Revision 6.3  2002/07/03 16:37:28  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.2  2002/06/17 16:14:15  mmiers
 * LOG: Correct variant number
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.3  2001/10/18 21:55:32  mmiers
 * LOG: Change max variant
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:53  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.2  2001/01/03 17:50:11  mmiers
 * LOG: Correct semantics for result
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:49  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/07/14 17:24:51  fhasle
 * LOG:
 * LOG: updated TCAP to support ITU 97 and Timer Reset.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:29  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:14  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.26  1999/11/10 18:40:01  mmiers
 * LOG:
 * LOG:
 * LOG: Correct ANSI variant.
 * LOG:
 * LOG: Revision 1.25  1999/11/10 18:06:43  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.24  1999/09/17 16:01:07  labuser
 * LOG:
 * LOG:
 * LOG: Move the variant variable into tcap.c
 * LOG:
 * LOG: Revision 1.23  1999/09/16 22:09:19  lbana
 * LOG:
 * LOG:
 * LOG: Allow stacks to send artificial ANSI CANCEL components.
 * LOG:
 * LOG: Revision 1.22  1999/09/10 23:11:09  mmiers
 * LOG:
 * LOG:
 * LOG: Split out blue book and white book variants.
 * LOG:
 * LOG: Revision 1.21  1999/09/09 21:19:28  mmiers
 * LOG:
 * LOG:
 * LOG: Remove recursive call.
 * LOG:
 * LOG: Revision 1.20  1999/08/26 16:30:20  rsonak
 * LOG:
 * LOG:
 * LOG: Op class doesn't get transmitted, it is a local value only.  Make
 * LOG: sure the vendor sanity check doesn't require opclass.
 * LOG:
 * LOG: Revision 1.19  1999/08/25 21:57:53  mmiers
 * LOG:
 * LOG:
 * LOG: Add a check for vendor sanity.
 * LOG:
 * LOG: Revision 1.18  1999/08/25 21:27:38  mmiers
 * LOG:
 * LOG:
 * LOG: Make sure this works with split stack configurations.
 * LOG:
 * LOG: Revision 1.17  1999/08/25 21:22:41  mmiers
 * LOG:
 * LOG:
 * LOG: Add error checking for components and dialogue (sanity checks).
 * LOG:
 *
 ****************************************************************************/

#ident "$Id: tcap.c,v 1.1.1.1 2007-10-08 11:11:28 bsccs2 Exp $"

#if defined(CCITT)
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#elif defined(PRC)
#include <china/tcap.h>
#elif defined(TTC)
#include <japan/tcap.h>
#endif

/*
 * print header
 */
#define TCAP_PHDR   "-------------- TCAP ----------------\n"
#define CHECK_RETURN(r, cnt)    \
    if ((r) < 0)                \
    {                           \
        return (cnt);           \
    }                           \
    else                        \
    {                           \
        (cnt) += (r);           \
    }

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define EXTERNAL_TAG                           (0x28U)
#define OID_TAG                                (0x06U)
#define SINGLE_ASN1_TAG                        (0xA0U)
#define INTEGER_TAG                            (0x02U)

#define DIALOG_REQUEST_TAG                     (0x60U)
#define UNIDIRECTIONAL_TAG                     (0x60U)
#define DIALOG_RESPONSE_TAG                    (0x61U)
#define DIALOG_ABORT_TAG                       (0x64U)
#define RESULT_TAG                             (0xA2U)
#define RESULT_SOURCE_DIAGNOSTIC_TAG           (0xA3U)
#define DIALOG_SERVICE_USER_TAG                (0xA1U)
#define ABORT_SOURCE_TAG                       (0x80U)

#define PROTOCOL_VERSION_TAG                   (0x80U)
#define AC_NAME_TAG                            (0xA1U)
#define USER_INFO_TAG                          (0xBEU)

#endif

#if defined(ANSI)

#define PROTOCOL_VERSION_TAG                  (0xDAU)
#define AC_NAME_TAG                           (0xDCU) 
#define USER_INFO_TAG                         (0xFDU) 
#define PABT_CAUSE_TAG                        (0xD7U) 
#define TCPPN_SEQUENCE_TAG                    (0x30U)
#define TCPPN_SET_TAG                         (0xF2U)
#define U_ABORT_INFO_TAG                      (0xD8U)

#endif

#if defined(CCITT) || defined(PRC)

#define LINKED_ID_TAG   0x80U
#define SEQUENCE_TAG    0x30U

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Invoke_ITU(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  ITS_OCTET *bytes, ITS_USHORT len,
                  ITS_OCTET cType,
                  ITS_OCTET **ppdu, ITS_UINT *cslen,
                  TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Invoke Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is invoke, operation, param */
    /* invoke id? */
#if defined(CCITT)
    if (*pdu == TCAP_PN_INVOKE_TAG_CCITT)
#elif defined(PRC)
    if (*pdu == TCAP_PN_INVOKE_TAG_PRC)
#endif
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* linked id? */
    if (*pdu == LINKED_ID_TAG)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Linked ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Linked ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Linked ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Linked ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* operation code */
#if defined(CCITT)
    if (*pdu == TCAP_PN_LOCAL_OP_TAG_CCITT ||
        *pdu == TCAP_PN_GLOBAL_OP_TAG_CCITT)
#elif defined(PRC)
    if (*pdu == TCAP_PN_LOCAL_OP_TAG_PRC ||
        *pdu == TCAP_PN_GLOBAL_OP_TAG_PRC)
#endif
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Operation tag (%s)\n",
                     *bCount, *pdu,
                     *pdu,
#if defined(CCITT)
                     *pdu == TCAP_PN_GLOBAL_OP_TAG_CCITT
#elif defined(PRC)
                     *pdu == TCAP_PN_GLOBAL_OP_TAG_PRC
#endif
                        ? "Global"
                        : "Local");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* operation length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Operation Code Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* operation code */
        if (ilen)
        {
            here = pdu;
            pdu += ilen;
            if (here < pdu)
            {
                opCode = *here;
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Operation Code Data = %d\n",
                             *bCount, *here,
                             *here, *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* param */
    if (clen)
    {
        if (paramPrint)
        {
            tmp = (*paramPrint)(rb, bCount,
                                cType, 0, opCode,
                                pdu, (ITS_USHORT)clen);
            CHECK_RETURN(tmp, ret);

            pdu += clen;
            *cslen -= clen;
            clen = 0;
        }
        else
        {
            do
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Param Data = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                clen--;
                (*cslen)--;
                pdu++;
            }
            while (clen > 0);
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Result_ITU(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  ITS_OCTET *bytes, ITS_USHORT len,
                  ITS_OCTET cType,
                  ITS_OCTET **ppdu, ITS_UINT *cslen,
                  TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Result Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is the invoke data (op, id, param) */
    /* invoke id? */
#if defined(CCITT)
    if (*pdu == TCAP_PN_INVOKE_TAG_CCITT)
#elif defined(PRC)
    if (*pdu == TCAP_PN_INVOKE_TAG_PRC)
#endif
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* param */
    if (clen)
    {
        /* param present? */
        if (*pdu == SEQUENCE_TAG)
        {
            /* print sequence tag */
            tmp = PPrint(rb, " %3d.  %02x    %08b  Sequence Tag\n",
                         *bCount, *pdu,
                         *pdu);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            pdu++;
            (*cslen)--;
            clen--;

            /* sequence length */
            here = pdu;
            pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
            if (here < pdu)
            {
                if ((ITS_UINT)(pdu - here) > *cslen)
                {
                    *cslen = 0;
                    clen = 0;
                }
                else
                {
                    *cslen -= pdu - here;
                    clen -= pdu - here;
                }
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Sequence Length = %d\n",
                             *bCount, *here,
                             *here, ilen);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }

            /* get operation code */
#if defined(CCITT)
            if (*pdu == TCAP_PN_LOCAL_OP_TAG_CCITT ||
                *pdu == TCAP_PN_GLOBAL_OP_TAG_CCITT)
#elif defined(PRC)
            if (*pdu == TCAP_PN_LOCAL_OP_TAG_PRC ||
                *pdu == TCAP_PN_GLOBAL_OP_TAG_PRC)
#endif
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  Operation tag (%s)\n",
                             *bCount, *pdu,
                             *pdu,
#if defined(CCITT)
                             *pdu == TCAP_PN_GLOBAL_OP_TAG_CCITT
#elif defined(PRC)
                             *pdu == TCAP_PN_GLOBAL_OP_TAG_PRC
#endif
                                ? "Global"
                                : "Local");
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                pdu++;
                (*cslen)--;
                clen--;

                /* operation length */
                here = pdu;
                pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
                if (here < pdu)
                {
                    if ((ITS_UINT)(pdu - here) > *cslen)
                    {
                        *cslen = 0;
                        clen = 0;
                    }
                    else
                    {
                        *cslen -= pdu - here;
                        clen -= pdu - here;
                    }
                    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                     "Operation Code Length = %d\n",
                                 *bCount, *here,
                                 *here, ilen);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    here++;
                }
                while (here < pdu)
                {
                    tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                 *bCount, *here,
                                 *here);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    here++;
                }

                /* operation code */
                if (ilen)
                {
                    here = pdu;
                    pdu += ilen;
                    if (here < pdu)
                    {
                        opCode = *here;
                        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                         "Operation Code Data = %d\n",
                                     *bCount, *here,
                                     *here, *here);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }
                    while (here < pdu)
                    {
                        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                     *bCount, *here,
                                     *here);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }
                }

                /* local housekeeping */
                clen -= ilen;
                *cslen -= ilen;
            }

            /* print param */
            if (paramPrint)
            {
                tmp = (*paramPrint)(rb, bCount,
                                    cType, 0, opCode,
                                    pdu, (ITS_USHORT)clen);
                CHECK_RETURN(tmp, ret);

                pdu += clen;
                *cslen -= clen;
                clen = 0;
            }
            else
            {
                do
                {
                    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                     "Param Data = %d\n",
                                 *bCount, *pdu,
                                 *pdu, *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    clen--;
                    (*cslen)--;
                    pdu++;
                }
                while (clen > 0);
            }
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Error_ITU(RINGBUF_Manager *rb, ITS_UINT *bCount,
                 ITS_OCTET *bytes, ITS_USHORT len,
                 ITS_OCTET cType,
                 ITS_OCTET **ppdu, ITS_UINT *cslen,
                 TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Error Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is the invoke data (op, id, param) */
    /* invoke id? */
#if defined(CCITT)
    if (*pdu == TCAP_PN_INVOKE_TAG_CCITT)
#elif defined(PRC)
    if (*pdu == TCAP_PN_INVOKE_TAG_PRC)
#endif
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* error code */
#if defined(CCITT)
    if (*pdu == TCAP_PN_LOCAL_ERR_TAG_CCITT ||
        *pdu == TCAP_PN_GLOBAL_ERR_TAG_CCITT)
#elif defined(PRC)
    if (*pdu == TCAP_PN_LOCAL_ERR_TAG_PRC ||
        *pdu == TCAP_PN_GLOBAL_ERR_TAG_PRC)
#endif
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Error tag (%s)\n",
                     *bCount, *pdu,
                     *pdu,
#if defined(CCITT)
                     *pdu == TCAP_PN_GLOBAL_ERR_TAG_CCITT
#elif defined(PRC)
                     *pdu == TCAP_PN_GLOBAL_ERR_TAG_PRC
#endif
                        ? "Global"
                        : "Local");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* error length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Error Code Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* error code */
        if (ilen)
        {
            here = pdu;
            pdu += ilen;
            if (here < pdu)
            {
                opCode = *here;
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Error Code Data = %d\n",
                             *bCount, *here,
                             *here, *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* param */
    if (clen)
    {
        if (paramPrint)
        {
            tmp = (*paramPrint)(rb, bCount,
                                cType, 0, opCode,
                                pdu, (ITS_USHORT)clen);
            CHECK_RETURN(tmp, ret);

            pdu += clen;
            *cslen -= clen;
            clen = 0;
        }
        else
        {
            do
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Param Data = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                clen--;
                (*cslen)--;
                pdu++;
            }
            while (clen > 0);
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Reject_ITU(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  ITS_OCTET *bytes, ITS_USHORT len,
                  ITS_OCTET cType,
                  ITS_OCTET **ppdu, ITS_UINT *cslen,
                  TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Reject Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is the invoke data (op, id, param) */
    /* invoke id? */
#if defined(CCITT)
    if (*pdu == TCAP_PN_INVOKE_TAG_CCITT)
#elif defined(PRC)
    if (*pdu == TCAP_PN_INVOKE_TAG_PRC)
#endif
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* reject type code */
    switch (*pdu)
    {
#if defined(CCITT)
    case TCAP_PROB_GENERAL_CCITT:
#elif defined(PRC)
    case TCAP_PROB_GENERAL_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  General problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

#if defined(CCITT)
    case TCAP_PROB_INVOKE_CCITT:
#elif defined(PRC)
    case TCAP_PROB_INVOKE_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

#if defined(CCITT)
    case TCAP_PROB_RETURN_RES_CCITT:
#elif defined(PRC)
    case TCAP_PROB_RETURN_RES_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  Result problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

#if defined(CCITT)
    case TCAP_PROB_RETURN_ERR_CCITT:
#elif defined(PRC)
    case TCAP_PROB_RETURN_ERR_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  Error problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

    default:
        tmp = PPrint(rb, " %3d.  %02x    %08b  Unknown problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;
    }

    /* problem length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
            clen = 0;
        }
        else
        {
            *cslen -= pdu - here;
            clen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Problem Length = %d\n",
                     *bCount, *here,
                     *here, ilen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* problem code */
    if (ilen)
    {
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Problem Code Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
    }

    /* local housekeeping */
    clen -= ilen;
    *cslen -= ilen;

    /* param (shouldn't be present) */
    if (clen)
    {
        if (paramPrint)
        {
            tmp = (*paramPrint)(rb, bCount,
                                cType, 0, opCode,
                                pdu, (ITS_USHORT)clen);
            CHECK_RETURN(tmp, ret);

            pdu += clen;
            *cslen -= clen;
            clen = 0;
        }
        else
        {
            do
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Param Data = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                clen--;
                (*cslen)--;
                pdu++;
            }
            while (clen > 0);
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Common print routine for ITU and PRC transactions
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1672   Printing the dialog portion clearly.
 *                        
 ****************************************************************************/
static int
CommonPrint(RINGBUF_Manager *rb, ITS_UINT *bCount,
            ITS_OCTET *bytes, ITS_USHORT len,
            TCAP_PPrintProc paramPrint)
{
    ITS_OCTET *tp, *dp, *cp, *pdu, *here, cType;
    enum ParseCode code;
    ITS_UINT tid, tidLen;
    ITS_UINT tag, clen, cslen;
    int ret, tmp;

    /* split up the transaction */
    code = TCAP_FindParts_CCITT(bytes, (int)len, &tp, &dp, &cp);
    if (code != PC_PARSE_OK)
    {
        return (-1);
    }

    if (tp == NULL)
    {
        return (-1);
    }

    /* header */
    ret = PPrint(rb, TCAP_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* package tag */
    pdu = bytes;
    pdu += TCAP_GetTag(pdu, &tag, bytes + len);

    switch (tag)
    {
#if defined(CCITT)
    case TCAP_PT_TC_UNI_CCITT:
#elif defined(PRC)
    case TCAP_PT_TC_UNI_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-UNI)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

#if defined(CCITT)
    case TCAP_PT_TC_BEGIN_CCITT:
#elif defined(PRC)
    case TCAP_PT_TC_BEGIN_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-BEGIN)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

#if defined(CCITT)
    case TCAP_PT_TC_END_CCITT:
#elif defined(PRC)
    case TCAP_PT_TC_END_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-END)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

#if defined(CCITT)
    case TCAP_PT_TC_CONTINUE_CCITT:
#elif defined(PRC)
    case TCAP_PT_TC_CONTINUE_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-CONTINUE)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

#if defined(CCITT)
    case TCAP_PT_TC_P_ABORT_CCITT:
#elif defined(PRC)
    case TCAP_PT_TC_P_ABORT_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-P-ABORT)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

#if defined(CCITT)
    case TCAP_PT_TC_U_ABORT_CCITT:
#elif defined(PRC)
    case TCAP_PT_TC_U_ABORT_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-U-ABORT)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

#if defined(CCITT)
    case TCAP_PT_TC_NOTICE_CCITT:
#elif defined(PRC)
    case TCAP_PT_TC_NOTICE_PRC:
#endif
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-NOTICE)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    default:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (UNKNOWN)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;
    }

    /* PDU length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* tids */
    if (*pdu == OTID_IDENT)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  OTID identifier = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        pdu++;
        here = pdu;

        TCAP_GetTID(&pdu, &tid, &tidLen);

        if (here < pdu)
        {
            ITS_UINT tid_mod = 0;
            ITS_INT i = 0;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "OTID length = %d\n",
                         *bCount, *here,
                         *here, tidLen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;

            for (i = 0; i < tidLen; i++)
                tid_mod = (tid & (0xff << (i * 8))) | tid_mod;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "OTID = 0x%08x\n",
                         *bCount, *here,
                         *here, tid_mod);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
    }
    else if (*pdu == DTID_IDENT)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  DTID identifier = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        pdu++;
        here = pdu;

        TCAP_GetTID(&pdu, &tid, &tidLen);
        if (here < pdu)
        {
            ITS_UINT tid_mod = 0;
            ITS_INT i = 0;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "OTID length = %d\n",
                         *bCount, *here,
                         *here, tidLen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;

            for (i = 0; i < tidLen; i++)
                tid_mod = (tid & (0xff << (i * 8))) | tid_mod;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "DTID = 0x%08x\n",
                         *bCount, *here,
                         *here, tid_mod);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
    }
    else
    {
#if defined(CCITT)
        if (tag != TCAP_PT_TC_UNI_CCITT)
#elif defined(PRC)
        if (tag != TCAP_PT_TC_UNI_PRC)
#endif
        {
            tmp = PPrint(rb, " Decode error (missing TIDs)\n");
            CHECK_RETURN(tmp, ret);
            return (ret);
        }
    }

    /* have we run out of data */
    if ((pdu - bytes) >= len)
    {
        return (ret);
    }

    if (*pdu == OTID_IDENT)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  OTID identifier = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        pdu++;
        here = pdu;

        TCAP_GetTID(&pdu, &tid, &tidLen);
        if (here < pdu)
        {
            ITS_UINT tid_mod = 0;
            ITS_INT i = 0;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "OTID length = %d\n",
                         *bCount, *here,
                         *here, tidLen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;

            for (i = 0; i < tidLen; i++)
                tid_mod = (tid & (0xff << (i * 8))) | tid_mod;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "OTID = 0x%08x\n",
                         *bCount, *here,
                         *here, tid_mod);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
    }
    else if (*pdu == DTID_IDENT)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  DTID identifier = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        pdu++;
        here = pdu;

        TCAP_GetTID(&pdu, &tid, &tidLen);
        if (here < pdu)
        {
            ITS_UINT tid_mod = 0;
            ITS_INT i = 0;
 
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "OTID length = %d\n",
                         *bCount, *here,
                         *here, tidLen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;

            for (i = 0; i < tidLen; i++)
                tid_mod = (tid & (0xff << (i * 8))) | tid_mod;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "DTID = 0x%08x\n",
                         *bCount, *here,
                         *here, tid_mod);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
    }

    /* dialog portion, if present */
    if (dp)
    {
        if ((pdu - bytes) >= len)
        {
#if defined(CCITT)
            if (tag != TCAP_PT_TC_UNI_CCITT)
#elif defined(PRC)
            if (tag != TCAP_PT_TC_UNI_PRC)
#endif
            {
                tmp = PPrint(rb, " Decode error (missing components)\n");
                CHECK_RETURN(tmp, ret);
                return (ret);
            }
            else
            {
                return (ret);
            }
        }

        if (*dp == DIALOG_IDENT)
        {
            ITS_UINT dTag = 0;
            ITS_OCTET dType = 0;
            ITS_INT tmplen = 0;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "TCAP Dialogue ID = %d\n",
                         *bCount, *dp,
                         *dp, *dp);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            pdu = dp;
            pdu++;
            here = pdu;
            pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
            if (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "TCAP Dialogue Length = %d\n",
                             *bCount, *here,
                             *here, clen);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }

            if (*pdu != EXTERNAL_TAG)
                return ITS_FALSE; 

            PPrint(rb, " %3d.  %02x    %08b  External Tag = %d\n",
                *bCount, *pdu, *pdu, *pdu);     
            pdu++;
            (*bCount)++;

            PPrint(rb, " %3d.  %02x    %08b  External Length = %d\n",
                *bCount, *pdu, *pdu, *pdu);
            pdu++;
            (*bCount)++;

            if (*pdu != OID_TAG)
                return ITS_FALSE;

            PPrint(rb, " %3d.  %02x    %08b  Object Identifier Tag = %d\n",
                *bCount, *pdu, *pdu, *pdu);
            pdu++;
            (*bCount)++;

            here = pdu;
            pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);

            if (here < pdu)
            {
                PPrint(rb, " %3d.  %02x    %08b  Object Identifier Length = %d\n",
                    *bCount, *here, *here, clen);
                here++;
                (*bCount)++;
            }

            if ((pdu - here) > 5)
            {
                dType = here[4];
            }

            while (clen) 
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  Object Identifier Value = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                pdu++;
                clen--;
            }

            PPrint(rb, " %3d.  %02x    %08b  Single ASN.1 Tag = %d\n",
                *bCount, *pdu, *pdu, *pdu);
            pdu++;
            (*bCount)++;  

            PPrint(rb, " %3d.  %02x    %08b  Single ASN.1 Length = %d\n",
                *bCount, *pdu, *pdu, *pdu);
            pdu++;
            (*bCount)++;

            here = pdu;
            pdu += TCAP_GetTag(pdu, &dTag, bytes + len);
            here = pdu;
            pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);

            if (here >= pdu)
                return ITS_FALSE;
          
            here++; 
           
            switch (dTag)
            {
                case DIALOG_REQUEST_TAG:
                    if (dType == 0)
                    {
                        PPrint(rb, " %3d.  %02x    %08b  Dialog Request Tag = %d\n",
                        *bCount, dTag, dTag, dTag);
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  Dialog Request Length = %d\n",
                                   *bCount, clen, clen, clen);
                        (*bCount)++;
                    } 
                    else if (dType == 1)
                    {
                        PPrint(rb, " %3d.  %02x    %08b  UniDialog Tag = %d\n",
                        *bCount, dTag, dTag, dTag);
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  UniDialog Length = %d\n",
                                   *bCount, clen, clen, clen);
                        (*bCount)++;
                    }

                    break;

                case DIALOG_RESPONSE_TAG:
                    PPrint(rb, " %3d.  %02x    %08b  Dialog Response Tag = %d\n",
                    *bCount, dTag, dTag, dTag);
                    (*bCount)++;

                    PPrint(rb, " %3d.  %02x    %08b  Dialog Response Length = %d\n",
                               *bCount, clen, clen, clen);
                    (*bCount)++;

                    break;

                case DIALOG_ABORT_TAG:
                    PPrint(rb, " %3d.  %02x    %08b  Dialog Abort Tag = %d\n",
                    *bCount, dTag, dTag, dTag);
                    (*bCount)++;

                    PPrint(rb, " %3d.  %02x    %08b  Dialog Abort Length = %d\n",
                               *bCount, clen, clen, clen);
                    (*bCount)++;

                    break;

                default:
                    PPrint(rb, " %3d.  %02x    %08b  Dialog Unknown Tag = %d\n",
                    *bCount, dTag, dTag, dTag);
                    (*bCount)++;

                    PPrint(rb, " %3d.  %02x    %08b  Dialog Unknown Tag Length = %d\n",
                               *bCount, clen, clen, clen);
                    (*bCount)++;

                    break;
            }

            here = pdu;
            pdu = pdu + clen;

            while (here < pdu)
            {
                if (*here == PROTOCOL_VERSION_TAG)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Protocol Version Tag = %d\n",
                    *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;

                    here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                    PPrint(rb, " %3d.  %02x    %08b  Protocol Version Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                    (*bCount)++;

                    while (tmplen)
                    {
                        PPrint(rb, " %3d.  %02x    %08b  Protocol Version Value = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;
                        tmplen--;
                    } 
                }
                else if (*here == AC_NAME_TAG)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Application Context Tag = %d\n",
                    *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;

                    here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                    PPrint(rb, " %3d.  %02x    %08b  Application Context Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                    (*bCount)++;

                    while (tmplen)
                    {
                        PPrint(rb, " %3d.  %02x    %08b  Application Context Value = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;
                        tmplen--;
                    }
                }
                else if (*here == USER_INFO_TAG)
                {
                    PPrint(rb, " %3d.  %02x    %08b  User Info Tag = %d\n",
                    *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;

                    here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                    PPrint(rb, " %3d.  %02x    %08b  User Info Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                    (*bCount)++;

                    while (tmplen)
                    {
                        PPrint(rb, " %3d.  %02x    %08b  User Info Value = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;
                        tmplen--;
                    }
                }
                else if (*here == RESULT_TAG)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Result Tag = %d\n",
                    *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;

                    here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                    PPrint(rb, " %3d.  %02x    %08b  Result Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                    (*bCount)++;

                    PPrint(rb, " %3d.  %02x    %08b  Result Value Tag = %d\n",
                    *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;

                    here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                    PPrint(rb, " %3d.  %02x    %08b  Result Value Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                    (*bCount)++;

                    PPrint(rb, " %3d.  %02x    %08b  Result Value  = %d\n",
                               *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;
                }
                else if (*here == RESULT_SOURCE_DIAGNOSTIC_TAG)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Result Source Diagnostic Tag = %d\n",
                    *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;

                    here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                    PPrint(rb, " %3d.  %02x    %08b  Result Source Diagnostic Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                    (*bCount)++;

                    if (*here == DIALOG_SERVICE_USER_TAG)
                    {
                        PPrint(rb, " %3d.  %02x    %08b  Service User Tag = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;

                        here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                        PPrint(rb, " %3d.  %02x    %08b  Service User Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  Integer Tag = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  Integer Length = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  Service User Diagnostic Value = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;
                    }
                    else
                    {
                        PPrint(rb, " %3d.  %02x    %08b  Service Provider Tag = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  Service Provider Length = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  Integer Tag = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;

                        PPrint(rb, " %3d.  %02x    %08b  Integer Length = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;

                        PPrint(rb, 
                               " %3d.  %02x    %08b  Service Provider Diagnostic Value = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;
                    }
                }
                else if (*here == ABORT_SOURCE_TAG)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Abort Source Tag = %d\n",
                    *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;

                    here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                    PPrint(rb, " %3d.  %02x    %08b  Abort Source Length = %d\n",
                               *bCount, tmplen, tmplen, tmplen);
                    (*bCount)++;

                    while (tmplen)
                    {
                        PPrint(rb, " %3d.  %02x    %08b  Abort Source Value = %d\n",
                               *bCount, *here, *here, *here);
                        here++;
                        (*bCount)++;
                        tmplen--;
                    }
                }
                else
                {
                    here = pdu;
                    break;
                }
            } 
        }
        else if (*dp == PABT_IDENT)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "TCAP P-ABORT ID = %d\n",
                         *bCount, *dp,
                         *dp, *dp);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            pdu = dp;
            pdu++;
            here = pdu;
            pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
            if (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "TCAP P-ABORT Length = %d\n",
                             *bCount, *here,
                             *here, clen);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }

            /* FIXME: dump abort bytes more clearly */
            if (clen)
            {
                do
                {
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Abort data = %d\n",
                                 *bCount, *pdu,
                                 *pdu, *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    clen--;
                }
                while (clen > 0);
            }
       
            /* have we run out of data */
            if ((pdu - bytes) != len)
            {
                /* print */
                tmp = PPrint(rb, " Decode error (bad P-ABORT data)\n");
                CHECK_RETURN(tmp, ret);
                return (ret);
            }
            else
            {
                return (ret);
            }
        } 
    }

    /*
     * component portion ?
     */
    if (cp && *cp == CSEQ_IDENT)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Component sequence ID = %d\n",
                     *bCount, *cp,
                     *cp, *cp);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        pdu = cp;
        here = pdu;
        pdu++;
        pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "TCAP Component Sequence Length = %d\n",
                         *bCount, clen,
                         clen, clen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here+=2;
        }

        /* dump components */
        cslen = clen;
        if (cslen > 0)
        {
            do
            {
                cType = *pdu;
                switch (*pdu)
                {
#if defined(CCITT)
                case TCAP_PT_TC_INVOKE_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_INVOKE_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-INVOKE)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the invoke contents */
                    tmp = PPrint_Invoke_ITU(rb, bCount, bytes, len,
                                            cType,
                                            &pdu, &cslen,
                                            paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_RESULT_L_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_RESULT_L_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-RESULT-L)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the result contents */
                    tmp = PPrint_Result_ITU(rb, bCount, bytes, len,
                                            cType,
                                            &pdu, &cslen,
                                            paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_U_ERROR_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_U_ERROR_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-U-ERROR)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the error contents */
                    tmp = PPrint_Error_ITU(rb, bCount, bytes, len,
                                           cType,
                                           &pdu, &cslen,
                                           paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_R_REJECT_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_R_REJECT_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-R-REJECT)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the reject contents */
                    tmp = PPrint_Reject_ITU(rb, bCount, bytes, len,
                                            cType,
                                            &pdu, &cslen,
                                            paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_RESULT_NL_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_RESULT_NL_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-RESULT-NL)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the result contents */
                    tmp = PPrint_Result_ITU(rb, bCount, bytes, len,
                                            cType,
                                            &pdu, &cslen,
                                            paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_L_CANCEL_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_L_CANCEL_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-L-CANCEL)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* do the component length */
                    here = pdu;
                    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
                    if (here < pdu)
                    {
                        if ((ITS_UINT)(pdu - here) > cslen)
                        {
                            cslen = 0;
                        }
                        else
                        {
                            cslen -= pdu - here;
                        }
                        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                         "TCAP Cancel Length = %d\n",
                                     *bCount, *here,
                                     *here, clen);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }
                    while (here < pdu)
                    {
                        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                     *bCount, *here,
                                     *here);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }

                    /* the rest is the invoke data (op, id, param) */
                    cslen -= clen;
                    pdu += clen;
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_U_CANCEL_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_U_CANCEL_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-U-CANCEL)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* do the component length */
                    here = pdu;
                    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
                    if (here < pdu)
                    {
                        if ((ITS_UINT)(pdu - here) > cslen)
                        {
                            cslen = 0;
                        }
                        else
                        {
                            cslen -= pdu - here;
                        }
                        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                         "TCAP Cancel Length = %d\n",
                                     *bCount, *here,
                                     *here, clen);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }
                    while (here < pdu)
                    {
                        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                     *bCount, *here,
                                     *here);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }

                    /* the rest is the invoke data (op, id, param) */
                    cslen -= clen;
                    pdu += clen;
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_L_REJECT_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_L_REJECT_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-L-REJECT)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the reject contents */
                    tmp = PPrint_Reject_ITU(rb, bCount, bytes, len,
                                            cType,
                                            &pdu, &cslen,
                                            paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

#if defined(CCITT)
                case TCAP_PT_TC_U_REJECT_CCITT:
#elif defined(PRC)
                case TCAP_PT_TC_U_REJECT_PRC:
#endif
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-U-REJECT)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the reject contents */
                    tmp = PPrint_Reject_ITU(rb, bCount, bytes, len,
                                            cType,
                                            &pdu, &cslen,
                                            paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

                default:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (UNKNOWN)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    cslen = 0;
                    break;
                }
            }
            while (cslen > 0);
        }
    }

    if ((pdu - bytes) > len)
    {
        /* print */
        tmp = PPrint(rb, " Decode error (bad component data)\n");
        CHECK_RETURN(tmp, ret);
        return (ret);
    }

    return (ret);
}
#endif

#if defined(CCITT)

/*
 * This guy needs to be well known, but defined here for linkage reasons.
 */
SS7DLLAPI int CCITT_TCAP_Variant = CCITT_TCAP_WHITE_BOOK;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the current TCAP variant.
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
SS7DLLAPI int
TCAP_SetVariant_CCITT(int variant)
{
    int ret = CCITT_TCAP_Variant;

    if (variant < CCITT_TCAP_BLUE_BOOK || variant > CCITT_TCAP_WHITE_BOOK_97)
    {
        return (ITS_EINVALIDARGS);
    }

    CCITT_TCAP_Variant = variant;

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the current ITU variant in effect.
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
SS7DLLAPI int
TCAP_GetVariant_CCITT()
{
    return (CCITT_TCAP_Variant);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_ComponentSanityCheck_CCITT(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_CCITT:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.invoke.invoke_id.len != 3 ||
            cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
            cpt->u.invoke.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct */
        if (cpt->u.invoke.operation.len <= 2 ||
            (cpt->u.invoke.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_CCITT &&
             cpt->u.invoke.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_CCITT) ||
            cpt->u.invoke.operation.data[1] == 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* class of operation is mandatory and must be correct */
        if (cpt->u.invoke.opClass < 1 || cpt->u.invoke.opClass > 4)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* if linked id is present it must be correct */
        if (cpt->u.invoke.linked_id.len != 0 &&
            (cpt->u.invoke.linked_id.len != 3 ||
             cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
             cpt->u.invoke.invoke_id.data[1] != 1))
        {
            return (ITS_BADTCAPMESSAGE);
        }

        break;

    case TCAP_PT_TC_RESULT_L_CCITT:
    case TCAP_PT_TC_RESULT_NL_CCITT:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.result.invoke_id.len != 3 ||
            cpt->u.result.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
            cpt->u.result.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct, iff param is present. */
        if (cpt->u.result.param.len != 0 &&
            (cpt->u.result.operation.len <= 2 ||
             (cpt->u.result.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_CCITT &&
              cpt->u.result.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_CCITT) ||
             cpt->u.result.operation.data[1] == 0))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        else if (cpt->u.result.param.len == 0 &&
                 cpt->u.result.operation.len != 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_ERROR_CCITT:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.error.invoke_id.len != 3 ||
            cpt->u.error.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
            cpt->u.error.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (cpt->u.error.error.len <= 2 ||
            (cpt->u.error.error.data[0] != TCAP_PN_LOCAL_ERR_TAG_CCITT &&
             cpt->u.error.error.data[0] != TCAP_PN_GLOBAL_ERR_TAG_CCITT))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_CANCEL_CCITT:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_REJECT_CCITT:
    case TCAP_PT_TC_R_REJECT_CCITT:
        if (cpt->u.reject.problem.len == 0 ||
            (cpt->u.reject.problem.data[0] != TCAP_PROB_GENERAL_CCITT &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_INVOKE_CCITT &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_RES_CCITT &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_ERR_CCITT) ||
            cpt->u.reject.problem.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_TIMER_RESET_CCITT:
        /* The variant must be ITU White Book 97. */
        if(CCITT_TCAP_Variant < CCITT_TCAP_WHITE_BOOK_97)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for the end user.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorComponentSanityCheck_CCITT(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_CCITT:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.invoke.invoke_id.len != 3 ||
            cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
            cpt->u.invoke.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct */
        if (cpt->u.invoke.operation.len <= 2 ||
            (cpt->u.invoke.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_CCITT &&
             cpt->u.invoke.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_CCITT) ||
            cpt->u.invoke.operation.data[1] == 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* if linked id is present it must be correct */
        if (cpt->u.invoke.linked_id.len != 0 &&
            (cpt->u.invoke.linked_id.len != 3 ||
             cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
             cpt->u.invoke.invoke_id.data[1] != 1))
        {
            return (ITS_BADTCAPMESSAGE);
        }

        break;

    case TCAP_PT_TC_RESULT_L_CCITT:
    case TCAP_PT_TC_RESULT_NL_CCITT:
    case TCAP_PT_TC_U_ERROR_CCITT:
    case TCAP_PT_TC_U_CANCEL_CCITT:
    case TCAP_PT_TC_U_REJECT_CCITT:
        return TCAP_ComponentSanityCheck_CCITT(cpt);

    /* stack only messages */
    case TCAP_PT_TC_R_REJECT_CCITT:
    case TCAP_PT_TC_L_REJECT_CCITT:
        if (cpt->u.reject.problem.len == 0 ||
            (cpt->u.reject.problem.data[0] != TCAP_PROB_GENERAL_CCITT &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_INVOKE_CCITT &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_RES_CCITT &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_ERR_CCITT) ||
            cpt->u.reject.problem.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_L_CANCEL_CCITT:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_CCITT ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_DialogueSanityCheck_CCITT(TCAP_DLG *dlg)
{
    ITS_OCTET ai, ssn, gttInfo[SCCP_MAX_ADDR_LEN];
    ITS_UINT pc;
    ITS_USHORT gttLen;

    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_CCITT:
        if (dlg->u.uni.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.uni.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (CCITT_TCAP_Variant < CCITT_TCAP_WHITE_BOOK)
        {
            if (dlg->u.uni.ac_name.len != 0 ||
                dlg->u.uni.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_BEGIN_CCITT:
        if (dlg->u.begin.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.begin.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (CCITT_TCAP_Variant < CCITT_TCAP_WHITE_BOOK)
        {
            if (dlg->u.begin.ac_name.len != 0 ||
                dlg->u.begin.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_CONTINUE_CCITT:
        if (dlg->u.cont.orig_addr.len != 0 &&
            SCCP_DecodeAddr(&dlg->u.cont.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (CCITT_TCAP_Variant < CCITT_TCAP_WHITE_BOOK)
        {
            if (dlg->u.cont.ac_name.len != 0 ||
                dlg->u.cont.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_END_CCITT:
        if (dlg->u.end.termination != TCAP_END_BASIC &&
            dlg->u.end.termination != TCAP_END_PREARRANGED)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (CCITT_TCAP_Variant < CCITT_TCAP_WHITE_BOOK)
        {
            if (dlg->u.end.ac_name.len != 0 ||
                dlg->u.end.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_U_ABORT_CCITT:
        if (CCITT_TCAP_Variant < CCITT_TCAP_WHITE_BOOK)
        {
            if (dlg->u.abort.ac_name.len != 0 ||
                dlg->u.abort.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for end users.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorDialogueSanityCheck_CCITT(TCAP_DLG *dlg)
{
    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_CCITT:
    case TCAP_PT_TC_BEGIN_CCITT:
    case TCAP_PT_TC_CONTINUE_CCITT:
    case TCAP_PT_TC_END_CCITT:
    case TCAP_PT_TC_U_ABORT_CCITT:
        return TCAP_DialogueSanityCheck(dlg);

    case TCAP_PT_TC_P_ABORT_CCITT:
        if ((dlg->u.abort.ac_name.len == 0 && dlg->u.abort.user_info.len == 0) &&
            (dlg->u.abort.abort_reason != TCAP_PABT_ABNORMAL_DLG_CCITT &&
             dlg->u.abort.abort_reason != TCAP_PABT_NO_COMMON_DLG_CCITT &&
             dlg->u.abort.abort_reason != TCAP_ABT_REASON_UNREC_MSG_TYPE_CCITT &&
             dlg->u.abort.abort_reason != TCAP_ABT_REASON_UNREC_TRANS_ID_CCITT &&
             dlg->u.abort.abort_reason != TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_CCITT &&
             dlg->u.abort.abort_reason != TCAP_ABT_REASON_INCORRECT_TRANS_PORT_CCITT &&
             dlg->u.abort.abort_reason != TCAP_ABT_REASON_RES_UNAVAIL_CCITT))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_NOTICE_CCITT:
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method prints a CCITT variant TCAP PDU
 *
 *  Input Parameters:
 *      rb - the ring buffer
 *      bCount - the byte counter
 *      data - the byte stream
 *      len - number of bytes in the stream
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of characters printed
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  ITS_OCTET *bytes, ITS_USHORT len,
                  TCAP_PPrintProc paramPrint)
{
    return CommonPrint(rb, bCount, bytes, len, paramPrint);
}

#endif

#if defined(ANSI)

/*
 * This guy needs to be well known, but defined here for linkage reasons.
 */
SS7DLLAPI int ANSI_TCAP_Variant = ANSI_TCAP_1996;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the current TCAP variant.
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
SS7DLLAPI int
TCAP_SetVariant_ANSI(int variant)
{
    int ret = ANSI_TCAP_Variant;

    if (variant < ANSI_TCAP_1988 || variant > ANSI_TCAP_1996)
    {
        return (ITS_EINVALIDARGS);
    }

    ANSI_TCAP_Variant = variant;

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the current ITU variant in effect.
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
SS7DLLAPI int
TCAP_GetVariant_ANSI()
{
    return (ANSI_TCAP_Variant);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * sbabu     04-07-2005  BCGI bug                Fix for stack not able to
 *                                               decode a TCAP UNI because the
 *                                               length of the INVOKE ID in the
 *                                               component portion is null.
 *
 ****************************************************************************/
SS7DLLAPI int
TCAP_ComponentSanityCheck_ANSI(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_ANSI:
    case TCAP_PT_TC_INVOKE_NL_ANSI:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.invoke.invoke_id.len != 3 ||
            cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_ANSI) 
            
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct */
        if (cpt->u.invoke.operation.len <= 3 ||
            (cpt->u.invoke.operation.data[0] != TCAP_PN_OCI_NATIONAL_TCAP_ANSI &&
             cpt->u.invoke.operation.data[0] != TCAP_PN_OCI_PRIVATE_TCAP_ANSI) ||
            cpt->u.invoke.operation.data[1] != 2)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* if linked id is present it must be correct */
        if (cpt->u.invoke.linked_id.len != 0 &&
            (cpt->u.invoke.linked_id.len != 3 ||
             cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_ANSI ||
             cpt->u.invoke.invoke_id.data[1] != 1))
        {
            return (ITS_BADTCAPMESSAGE);
        }

        break;

    case TCAP_PT_TC_RESULT_L_ANSI:
    case TCAP_PT_TC_RESULT_NL_ANSI:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.result.invoke_id.len != 3 ||
            cpt->u.result.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_ANSI ||
            cpt->u.result.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_ERROR_ANSI:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.error.invoke_id.len != 3 ||
            cpt->u.error.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_ANSI ||
            cpt->u.error.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (cpt->u.error.error.len <= 2 ||
            (cpt->u.error.error.data[0] != TCAP_PN_ECI_NATIONAL_TCAP_ANSI &&
             cpt->u.error.error.data[0] != TCAP_PN_ECI_PRIVATE_TCAP_ANSI))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_REJECT_ANSI:
        if (cpt->u.reject.problem.len != 4 ||
            cpt->u.reject.problem.data[0] != TCAP_PN_PROB_IDENT_ANSI ||
            cpt->u.reject.problem.data[1] != 2)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for the end user.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorComponentSanityCheck_ANSI(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_ANSI:
    case TCAP_PT_TC_INVOKE_NL_ANSI:
    case TCAP_PT_TC_RESULT_L_ANSI:
    case TCAP_PT_TC_RESULT_NL_ANSI:
    case TCAP_PT_TC_ERROR_ANSI:
    case TCAP_PT_TC_REJECT_ANSI:
        return TCAP_ComponentSanityCheck(cpt);

	case TCAP_PT_TC_CANCEL_ANSI:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_ANSI ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
		break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_DialogueSanityCheck_ANSI(TCAP_DLG *dlg)
{
    ITS_OCTET ai, ssn, gttInfo[SCCP_MAX_ADDR_LEN];
    ITS_UINT pc;
    ITS_USHORT gttLen;

    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_ANSI:
        if (dlg->u.uni.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.uni.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_QUERY_W_PERM_ANSI:
    case TCAP_PT_TC_QUERY_WO_PERM_ANSI:
        if (dlg->u.begin.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.begin.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_CONV_W_PERM_ANSI:
    case TCAP_PT_TC_CONV_WO_PERM_ANSI:
        if (dlg->u.cont.orig_addr.len != 0 &&
            SCCP_DecodeAddr(&dlg->u.cont.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_RESP_ANSI:
        if (dlg->u.end.termination != TCAP_END_BASIC &&
            dlg->u.end.termination != TCAP_END_PREARRANGED)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_ABORT_ANSI:
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for end users.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorDialogueSanityCheck_ANSI(TCAP_DLG *dlg)
{
    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_ANSI:
    case TCAP_PT_TC_QUERY_W_PERM_ANSI:
    case TCAP_PT_TC_QUERY_WO_PERM_ANSI:
    case TCAP_PT_TC_CONV_W_PERM_ANSI:
    case TCAP_PT_TC_CONV_WO_PERM_ANSI:
    case TCAP_PT_TC_RESP_ANSI:
        return TCAP_DialogueSanityCheck(dlg);

    case TCAP_PT_TC_ABORT_ANSI:
        break;

    case TCAP_PT_TC_NOTICE_ANSI:
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

#define U_ABORT_INFO_TAG                      (0xD8U)

static char *ofNames[] =
{
    "NOT_USED",
    "PARAMETER",
    "CHARGING",
    "PROV_INST",
    "CONN_CTRL",
    "CALLER_INT",
    "SEND_NOT",
    "NET_MAN",
    "PROCEDURAL",
    "IS41"
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Invoke_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                   ITS_OCTET *bytes, ITS_USHORT len,
                   ITS_OCTET cType,
                   ITS_OCTET **ppdu, ITS_UINT *cslen,
                   TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0, opFamily = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Invoke Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is the invoke data (op, id, param) */
    /* invoke id? */
    if (*pdu == TCAP_PN_INVOKE_TAG_ANSI)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* operation code */
    if (*pdu == TCAP_PN_OCI_NATIONAL_TCAP_ANSI ||
        *pdu == TCAP_PN_OCI_PRIVATE_TCAP_ANSI)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Operation tag (%s)\n",
                     *bCount, *pdu,
                     *pdu,
                     *pdu == TCAP_PN_OCI_NATIONAL_TCAP_ANSI
                        ? "National"
                        : "Private");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* operation length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Operation Code Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* family */
        opFamily = *pdu;
        tmp = PPrint(rb, " %3d.  %02x   %b|%07b  "
                         "(%s) | Family = %s\n",
                     *bCount, *pdu,
                     *pdu >> 7, *pdu & 0x7FU,
                     (*pdu >> 7)
                        ? "Reply required"
                        : "Reply not required",
                     (*pdu & 0x7FU) <= TCAP_OF_IS41_ANSI
                        ? ofNames[(*pdu & 0x7FU)]
                        : "Not generic");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        ilen--;
        (*cslen)--;
        clen--;
        pdu++;

        if (ilen)
        {
            here = pdu;
            pdu += ilen;
            if (here < pdu)
            {
                opCode = *here;
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Operation Code Data = %d\n",
                             *bCount, *here,
                             *here, *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* param */
    if (clen)
    {
        if (paramPrint)
        {
            tmp = (*paramPrint)(rb, bCount,
                                cType, opFamily, opCode,
                                pdu, (ITS_USHORT)clen);
            CHECK_RETURN(tmp, ret);

            pdu += clen;
            *cslen -= clen;
            clen = 0;
        }
        else
        {
            do
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Param Data = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                clen--;
                (*cslen)--;
                pdu++;
            }
            while (clen > 0);
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Result_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                   ITS_OCTET *bytes, ITS_USHORT len,
                   ITS_OCTET cType,
                   ITS_OCTET **ppdu, ITS_UINT *cslen,
                   TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Invoke Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is the invoke data (op, id, param) */
    /* invoke id? */
    if (*pdu == TCAP_PN_INVOKE_TAG_ANSI)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* param */
    if (clen)
    {
        if (paramPrint)
        {
            tmp = (*paramPrint)(rb, bCount,
                                cType, 0, opCode,
                                pdu, (ITS_USHORT)clen);
            CHECK_RETURN(tmp, ret);

            pdu += clen;
            *cslen -= clen;
            clen = 0;
        }
        else
        {
            do
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Param Data = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                clen--;
                (*cslen)--;
                pdu++;
            }
            while (clen > 0);
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Error_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  ITS_OCTET *bytes, ITS_USHORT len,
                  ITS_OCTET cType,
                  ITS_OCTET **ppdu, ITS_UINT *cslen,
                  TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Invoke Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is the invoke data (op, id, param) */
    /* invoke id? */
    if (*pdu == TCAP_PN_INVOKE_TAG_ANSI)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* error code */
    if (*pdu == TCAP_PN_ECI_NATIONAL_TCAP_ANSI ||
        *pdu == TCAP_PN_ECI_PRIVATE_TCAP_ANSI)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Error tag (%s)\n",
                     *bCount, *pdu,
                     *pdu,
                     *pdu == TCAP_PN_ECI_NATIONAL_TCAP_ANSI
                        ? "National"
                        : "Private");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* error length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Error Code Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* error code */
        if (ilen)
        {
            here = pdu;
            pdu += ilen;
            if (here < pdu)
            {
                opCode = *here;
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Error Code Data = %d\n",
                             *bCount, *here,
                             *here, *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* param */
    if (clen)
    {
        if (paramPrint)
        {
            tmp = (*paramPrint)(rb, bCount,
                                cType, 0, opCode,
                                pdu, (ITS_USHORT)clen);
            CHECK_RETURN(tmp, ret);

            pdu += clen;
            *cslen -= clen;
            clen = 0;
        }
        else
        {
            do
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Param Data = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                clen--;
                (*cslen)--;
                pdu++;
            }
            while (clen > 0);
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Print a TC-INVOKE
 *
 *  Input Parameters:
 *      various
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_Reject_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                   ITS_OCTET *bytes, ITS_USHORT len,
                   ITS_OCTET cType,
                   ITS_OCTET **ppdu, ITS_UINT *cslen,
                   TCAP_PPrintProc paramPrint)
{
    int tmp, ret;
    ITS_UINT clen, ilen;
    ITS_OCTET *here, *pdu, opCode = 0;

    pdu = *ppdu;
    ret = 0;

    /* print the pdu length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
        }
        else
        {
            *cslen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Invoke Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* the rest is the invoke data (op, id, param) */
    /* invoke id? */
    if (*pdu == TCAP_PN_INVOKE_TAG_ANSI)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke ID Tag\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;

        /* invoke length */
        here = pdu;
        pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            if ((ITS_UINT)(pdu - here) > *cslen)
            {
                *cslen = 0;
                clen = 0;
            }
            else
            {
                *cslen -= pdu - here;
                clen -= pdu - here;
            }
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Length = %d\n",
                         *bCount, *here,
                         *here, ilen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* invoke id data */
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Invoke ID Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* local housekeeping */
        clen -= ilen;
        *cslen -= ilen;
    }

    /* reject type code */
    switch (*pdu)
    {
    case TCAP_PROB_GENERAL_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  General problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

    case TCAP_PROB_INVOKE_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  Invoke problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

    case TCAP_PROB_RETURN_RES_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  Result problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

    case TCAP_PROB_RETURN_ERR_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  Error problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

    case TCAP_PROB_TRANS_PORTION_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  Transaction problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;

    default:
        tmp = PPrint(rb, " %3d.  %02x    %08b  Unknown problem\n",
                     *bCount, *pdu,
                     *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        pdu++;
        (*cslen)--;
        clen--;
        break;
    }

    /* problem length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &ilen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        if ((ITS_UINT)(pdu - here) > *cslen)
        {
            *cslen = 0;
            clen = 0;
        }
        else
        {
            *cslen -= pdu - here;
            clen -= pdu - here;
        }
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Problem Length = %d\n",
                     *bCount, *here,
                     *here, ilen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* problem code */
    if (ilen)
    {
        here = pdu;
        pdu += ilen;
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "Problem Code Data = %d\n",
                         *bCount, *here,
                         *here, *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
    }

    /* local housekeeping */
    clen -= ilen;
    *cslen -= ilen;

    /* param */
    if (clen)
    {
        if (paramPrint)
        {
            tmp = (*paramPrint)(rb, bCount,
                                cType, 0, opCode,
                                pdu, (ITS_USHORT)clen);
            CHECK_RETURN(tmp, ret);

            pdu += clen;
            *cslen -= clen;
            clen = 0;
        }
        else
        {
            do
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Param Data = %d\n",
                             *bCount, *pdu,
                             *pdu, *pdu);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                clen--;
                (*cslen)--;
                pdu++;
            }
            while (clen > 0);
        }
    }

    /* global housekeeping */
    *ppdu = pdu;

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method prints a ANSI variant TCAP PDU
 *
 *  Input Parameters:
 *      rb - the ring buffer
 *      bCount - the byte counter
 *      data - the byte stream
 *      len - number of bytes in the stream
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of characters printed
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                 ITS_OCTET *bytes, ITS_USHORT len,
                 TCAP_PPrintProc paramPrint)
{
    ITS_OCTET *tp, *dp, *cp, *pdu, *here, cType;
    ITS_UINT tid, tidLen;
    ITS_UINT tag, clen, cslen;
    int ret, tmp;

    /* split up the transaction */
    ret = TCAP_FindParts_ANSI(bytes, (int)len, &tp, &dp, &cp);
    if (ret != ITS_SUCCESS)
    {
        return (-1);
    }

    if (tp == NULL)
    {
        return (-1);
    }

    /* header */
    ret = PPrint(rb, TCAP_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* package tag */
    pdu = bytes;
    pdu += TCAP_GetTag(pdu, &tag, bytes + len);

    switch (tag)
    {
    case TCAP_PT_TC_UNI_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-UNI)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case TCAP_PT_TC_QUERY_W_PERM_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-QUERY-W-PERM)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case TCAP_PT_TC_QUERY_WO_PERM_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-QUERY-WO-PERM)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case TCAP_PT_TC_RESP_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-RESP)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case TCAP_PT_TC_CONV_W_PERM_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-CONV-W-PERM)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case TCAP_PT_TC_CONV_WO_PERM_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-CONV-WO-PERM)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case TCAP_PT_TC_ABORT_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-ABORT)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case TCAP_PT_TC_NOTICE_ANSI:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (TC-NOTICE)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    default:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Type = %d (UNKOWN)\n",
                     *bCount, tag,
                     tag, tag);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;
    }

    /* PDU length */
    here = pdu;
    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
    if (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "TCAP Package Length = %d\n",
                     *bCount, *here,
                     *here, clen);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }
    while (here < pdu)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, *here,
                     *here);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        here++;
    }

    /* tids */
    if (*pdu == TID_IDENT)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  TID identifier = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        pdu++;
        here = pdu;

        TCAP_GetTID(&pdu, &tid, &tidLen);
        if (here < pdu)
        {
            ITS_UINT tid_mod = 0;
            ITS_INT i = 0;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "TID length = %d\n",
                         *bCount, *here,
                         *here, tidLen);
            (*bCount)++;
            here++;

            for (i = 0; i < tidLen; i++)
                tid_mod = (tid & (0xff << (i * 8))) | tid_mod;

            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "TID = 0x%08x\n",
                         *bCount, *here,
                         *here, tid_mod);

            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
    }

    /* have we run out of data */
    if ((pdu - bytes) >= len)
    {
        if (tag != TCAP_PT_TC_UNI_ANSI)
        {
            tmp = PPrint(rb, " Decode error!\n");
            CHECK_RETURN(tmp, ret);
            return (ret);
        }
        else
        {
            return ITS_SUCCESS;
        }
    }

    /* Dialogue portion present? */
    if (dp)
    {
        int tmplen = 0;
        pdu = dp;
        if (*pdu == DIALOG_IDENT)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  Dialogue identifier = %d\n",
                         *bCount, *pdu,
                         *pdu, *pdu);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            pdu++;
            here = pdu;
            pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
            if (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "TCAP Dialogue Length = %d\n",
                             *bCount, *here,
                             *here, clen);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }

            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }

            pdu += clen;

            if (*here == PROTOCOL_VERSION_TAG)
            {
                PPrint(rb, " %3d.  %02x    %08b  Protocol Version Tag = %d\n",
                    *bCount, *here, *here, *here);
                here++;
                (*bCount)++;
                
                here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                PPrint(rb, " %3d.  %02x    %08b  Protocol Version Length = %d\n",
                    *bCount, tmplen, tmplen, tmplen);
                (*bCount)++;
                
                while (tmplen)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Protocol Version Value = %d\n",
                        *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;
                    tmplen--;
                } 
            }

            if (*here == AC_NAME_TAG)
            {
                PPrint(rb, " %3d.  %02x    %08b  Application Context Tag = %d\n",
                    *bCount, *here, *here, *here);
                here++;
                (*bCount)++;
                
                here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                PPrint(rb, " %3d.  %02x    %08b  Application Context Length = %d\n",
                    *bCount, tmplen, tmplen, tmplen);
                (*bCount)++;
                
                while (tmplen)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Application Context Value = %d\n",
                        *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;
                    tmplen--;
                }
            }

            if (*here == USER_INFO_TAG)
            {
                PPrint(rb, " %3d.  %02x    %08b  User Info Tag = %d\n",
                    *bCount, *here, *here, *here);
                here++;
                (*bCount)++;
                
                here += TCAP_GetLength(here, &tmplen, bytes + len, ITS_TRUE);
                PPrint(rb, " %3d.  %02x    %08b  User Info Length = %d\n",
                    *bCount, tmplen, tmplen, tmplen);
                (*bCount)++;
                
                while (tmplen)
                {
                    PPrint(rb, " %3d.  %02x    %08b  User Info Value = %d\n",
                        *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;
                    tmplen--;
                }
            }

            if (here < pdu)
            {
                while (here < pdu)
                {
                    PPrint(rb, " %3d.  %02x    %08b  Dialog Data = %d\n",
                        *bCount, *here, *here, *here);
                    here++;
                    (*bCount)++;
                }
            }
        }
        else if (*pdu == PABT_IDENT)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  P-ABORT identifier = %d\n",
                         *bCount, *pdu,
                         *pdu, *pdu);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            pdu++;
            here = pdu;
            pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
            if (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "TCAP P-Abort Length = %d\n",
                             *bCount, *here,
                             *here, clen);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }

            /* FIXME: print data more clearly */
            if (clen)
            {
                do
                {
                    tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    clen--;
                }
                while (clen > 0);
            }
        }
        else if(*pdu != U_ABORT_INFO_TAG && *pdu != CSEQ_IDENT)
        {
            tmp = PPrint(rb, " Decode error!\n");
            CHECK_RETURN(tmp, ret);
            return (ret);
        }

        if (*pdu == U_ABORT_INFO_TAG)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  U-ABORT identifier = %d\n",
                         *bCount, *pdu,
                         *pdu, *pdu);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;

            pdu++;
            here = pdu;
            pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
            if (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "TCAP U-Abort Length = %d\n",
                             *bCount, *here,
                             *here, clen);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }
            while (here < pdu)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                             *bCount, *here,
                             *here);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
                here++;
            }

            /* FIXME: print data more clearly */
            if (clen)
            {
                do
                {
                    tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    clen--;
                }
                while (clen > 0);
            }
        }

        /* have we run out of data */
        if ((pdu - bytes) >= len)
        {
            if (tag != TCAP_PT_TC_UNI_ANSI)
            {
                return (ret);
            }
            else
            {
                return (ret);
            }
        }
    }

    /*
     * component portion ?
     */
    if (cp && *cp == CSEQ_IDENT)
    {
        pdu = cp;
        tmp = PPrint(rb, " %3d.  %02x    %08b  Component sequence identifier = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        pdu++;
        here = pdu;
        pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
        if (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b  "
                             "TCAP Component Sequence Length = %d\n",
                         *bCount, *here,
                         *here, clen);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }
        while (here < pdu)
        {
            tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                         *bCount, *here,
                         *here);
            CHECK_RETURN(tmp, ret);
            (*bCount)++;
            here++;
        }

        /* FIXME: print components */
        cslen = clen;
        if (cslen > 0)
        {
            do
            {
                cType = *pdu;
                switch (*pdu)
                {
                case TCAP_PT_TC_INVOKE_ANSI:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-INVOKE-L)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the invoke contents */
                    tmp = PPrint_Invoke_ANSI(rb, bCount, bytes, len,
                                             cType,
                                             &pdu, &cslen,
                                             paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

                case TCAP_PT_TC_RESULT_L_ANSI:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-RESULT-L)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the result contents */
                    tmp = PPrint_Result_ANSI(rb, bCount, bytes, len,
                                             cType,
                                             &pdu, &cslen,
                                             paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

                case TCAP_PT_TC_ERROR_ANSI:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-ERROR)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the error contents */
                    tmp = PPrint_Error_ANSI(rb, bCount, bytes, len,
                                            cType,
                                            &pdu, &cslen,
                                            paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

                case TCAP_PT_TC_REJECT_ANSI:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-REJECT)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the reject contents */
                    tmp = PPrint_Reject_ANSI(rb, bCount, bytes, len,
                                             cType,
                                             &pdu, &cslen,
                                             paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

                case TCAP_PT_TC_INVOKE_NL_ANSI:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-INVOKE-NL)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the invoke contents */
                    tmp = PPrint_Invoke_ANSI(rb, bCount, bytes, len,
                                             cType,
                                             &pdu, &cslen,
                                             paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

                case TCAP_PT_TC_RESULT_NL_ANSI:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-RESULT-NL)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* print the result contents */
                    tmp = PPrint_Result_ANSI(rb, bCount, bytes, len,
                                             cType,
                                             &pdu, &cslen,
                                             paramPrint);
                    CHECK_RETURN(tmp, ret);
                    break;

                case TCAP_PT_TC_CANCEL_ANSI:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (TC-CANCEL)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    pdu++;
                    cslen--;

                    /* do the component length */
                    here = pdu;
                    pdu += TCAP_GetLength(pdu, &clen, bytes + len, ITS_TRUE);
                    if (here < pdu)
                    {
                        if ((ITS_UINT)(pdu - here) > cslen)
                        {
                            cslen = 0;
                        }
                        else
                        {
                            cslen -= pdu - here;
                        }
                        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                         "TCAP Cancel Length = %d\n",
                                     *bCount, *here,
                                     *here, clen);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }
                    while (here < pdu)
                    {
                        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                     *bCount, *here,
                                     *here);
                        CHECK_RETURN(tmp, ret);
                        (*bCount)++;
                        here++;
                    }

                    /* the rest is the invoke data (op, id, param) */
                    cslen -= clen;
                    pdu += clen;
                    break;

                default:
                    tmp = PPrint(rb, " %3d.  %02x    %08b  Component (UNKNOWN)\n",
                                 *bCount, *pdu,
                                 *pdu);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                    cslen = 0;
                    break;
                }
            }
            while (cslen > 0);
        }
    }

    if ((pdu - bytes) > len)
    {
        tmp = PPrint(rb, " Decode error (bad component data)\n");
        CHECK_RETURN(tmp, ret);

        return (ret);
    }

    return (ret);
}

#endif

#if defined(PRC)

/*
 * This guy needs to be well known, but defined here for linkage reasons.
 */
SS7DLLAPI int PRC_TCAP_Variant = PRC_TCAP_WHITE_BOOK;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the current TCAP variant.
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
SS7DLLAPI int
TCAP_SetVariant_PRC(int variant)
{
    int ret = PRC_TCAP_Variant;

    if (variant < PRC_TCAP_BLUE_BOOK || variant > PRC_TCAP_WHITE_BOOK_97)
    {
        return (ITS_EINVALIDARGS);
    }

    PRC_TCAP_Variant = variant;

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the current ITU variant in effect.
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
SS7DLLAPI int
TCAP_GetVariant_PRC()
{
    return (PRC_TCAP_Variant);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_ComponentSanityCheck_PRC(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_PRC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.invoke.invoke_id.len != 3 ||
            cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
            cpt->u.invoke.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct */
        if (cpt->u.invoke.operation.len <= 2 ||
            (cpt->u.invoke.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_PRC &&
             cpt->u.invoke.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_PRC) ||
            cpt->u.invoke.operation.data[1] == 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* class of operation is mandatory and must be correct */
        if (cpt->u.invoke.opClass < 1 || cpt->u.invoke.opClass > 4)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* if linked id is present it must be correct */
        if (cpt->u.invoke.linked_id.len != 0 &&
            (cpt->u.invoke.linked_id.len != 3 ||
             cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
             cpt->u.invoke.invoke_id.data[1] != 1))
        {
            return (ITS_BADTCAPMESSAGE);
        }

        break;

    case TCAP_PT_TC_RESULT_L_PRC:
    case TCAP_PT_TC_RESULT_NL_PRC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.result.invoke_id.len != 3 ||
            cpt->u.result.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
            cpt->u.result.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct, iff param is present. */
        if (cpt->u.result.param.len != 0 &&
            (cpt->u.result.operation.len <= 2 ||
             (cpt->u.result.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_PRC &&
              cpt->u.result.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_PRC) ||
             cpt->u.result.operation.data[1] == 0))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        else if (cpt->u.result.param.len == 0 &&
                 cpt->u.result.operation.len != 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_ERROR_PRC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.error.invoke_id.len != 3 ||
            cpt->u.error.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
            cpt->u.error.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (cpt->u.error.error.len <= 2 ||
            (cpt->u.error.error.data[0] != TCAP_PN_LOCAL_ERR_TAG_PRC &&
             cpt->u.error.error.data[0] != TCAP_PN_GLOBAL_ERR_TAG_PRC))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_CANCEL_PRC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_REJECT_PRC:
        if (cpt->u.reject.problem.len == 0 ||
            (cpt->u.reject.problem.data[0] != TCAP_PROB_GENERAL_PRC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_INVOKE_PRC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_RES_PRC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_ERR_PRC) ||
            cpt->u.reject.problem.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_TIMER_RESET_PRC:
        /* The variant must be ITU White Book 97. */
        if(PRC_TCAP_Variant < PRC_TCAP_WHITE_BOOK_97)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for the end user.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorComponentSanityCheck_PRC(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_PRC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.invoke.invoke_id.len != 3 ||
            cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
            cpt->u.invoke.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct */
        if (cpt->u.invoke.operation.len <= 2 ||
            (cpt->u.invoke.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_PRC &&
             cpt->u.invoke.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_PRC) ||
            cpt->u.invoke.operation.data[1] == 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* if linked id is present it must be correct */
        if (cpt->u.invoke.linked_id.len != 0 &&
            (cpt->u.invoke.linked_id.len != 3 ||
             cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
             cpt->u.invoke.invoke_id.data[1] != 1))
        {
            return (ITS_BADTCAPMESSAGE);
        }

        break;

    case TCAP_PT_TC_RESULT_L_PRC:
    case TCAP_PT_TC_RESULT_NL_PRC:
    case TCAP_PT_TC_U_ERROR_PRC:
    case TCAP_PT_TC_U_CANCEL_PRC:
    case TCAP_PT_TC_U_REJECT_PRC:
        return TCAP_ComponentSanityCheck_PRC(cpt);

    /* stack only messages */
    case TCAP_PT_TC_R_REJECT_PRC:
    case TCAP_PT_TC_L_REJECT_PRC:
        if (cpt->u.reject.problem.len == 0 ||
            (cpt->u.reject.problem.data[0] != TCAP_PROB_GENERAL_PRC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_INVOKE_PRC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_RES_PRC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_ERR_PRC) ||
            cpt->u.reject.problem.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_L_CANCEL_PRC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_PRC ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_DialogueSanityCheck_PRC(TCAP_DLG *dlg)
{
    ITS_OCTET ai, ssn, gttInfo[SCCP_MAX_ADDR_LEN];
    ITS_UINT pc;
    ITS_USHORT gttLen;

    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_PRC:
        if (dlg->u.uni.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.uni.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (PRC_TCAP_Variant < PRC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.uni.ac_name.len != 0 ||
                dlg->u.uni.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_BEGIN_PRC:
        if (dlg->u.begin.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.begin.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (PRC_TCAP_Variant < PRC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.begin.ac_name.len != 0 ||
                dlg->u.begin.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_CONTINUE_PRC:
        if (dlg->u.cont.orig_addr.len != 0 &&
            SCCP_DecodeAddr(&dlg->u.cont.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (PRC_TCAP_Variant < PRC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.cont.ac_name.len != 0 ||
                dlg->u.cont.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_END_PRC:
        if (dlg->u.end.termination != TCAP_END_BASIC &&
            dlg->u.end.termination != TCAP_END_PREARRANGED)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (PRC_TCAP_Variant < PRC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.end.ac_name.len != 0 ||
                dlg->u.end.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_U_ABORT_PRC:
        if (PRC_TCAP_Variant < PRC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.abort.ac_name.len != 0 ||
                dlg->u.abort.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for end users.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorDialogueSanityCheck_PRC(TCAP_DLG *dlg)
{
    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_PRC:
    case TCAP_PT_TC_BEGIN_PRC:
    case TCAP_PT_TC_CONTINUE_PRC:
    case TCAP_PT_TC_END_PRC:
    case TCAP_PT_TC_U_ABORT_PRC:
        return TCAP_DialogueSanityCheck(dlg);

    case TCAP_PT_TC_P_ABORT_PRC:
        break;

    case TCAP_PT_TC_NOTICE_PRC:
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method prints a PRC (CCITT) variant TCAP PDU
 *
 *  Input Parameters:
 *      rb - the ring buffer
 *      bCount - the byte counter
 *      data - the byte stream
 *      len - number of bytes in the stream
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of characters printed
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                ITS_OCTET *bytes, ITS_USHORT len,
                TCAP_PPrintProc paramPrint)
{
    return CommonPrint(rb, bCount, bytes, len, paramPrint);
}

#endif

#if defined(TTC)

/*
 * This guy needs to be well known, but defined here for linkage reasons.
 */
SS7DLLAPI int TTC_TCAP_Variant = TTC_TCAP_WHITE_BOOK;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set the current TCAP variant.
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
SS7DLLAPI int
TCAP_SetVariant_TTC(int variant)
{
    int ret = TTC_TCAP_Variant;

    if (variant < TTC_TCAP_BLUE_BOOK || variant > TTC_TCAP_WHITE_BOOK_97)
    {
        return (ITS_EINVALIDARGS);
    }

    TTC_TCAP_Variant = variant;

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the current ITU variant in effect.
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
SS7DLLAPI int
TCAP_GetVariant_TTC()
{
    return (TTC_TCAP_Variant);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_ComponentSanityCheck_TTC(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_TTC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.invoke.invoke_id.len != 3 ||
            cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
            cpt->u.invoke.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct */
        if (cpt->u.invoke.operation.len <= 2 ||
            (cpt->u.invoke.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_TTC &&
             cpt->u.invoke.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_TTC) ||
            cpt->u.invoke.operation.data[1] == 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* class of operation is mandatory and must be correct */
        if (cpt->u.invoke.opClass < 1 || cpt->u.invoke.opClass > 4)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* if linked id is present it must be correct */
        if (cpt->u.invoke.linked_id.len != 0 &&
            (cpt->u.invoke.linked_id.len != 3 ||
             cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
             cpt->u.invoke.invoke_id.data[1] != 1))
        {
            return (ITS_BADTCAPMESSAGE);
        }

        break;

    case TCAP_PT_TC_RESULT_L_TTC:
    case TCAP_PT_TC_RESULT_NL_TTC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.result.invoke_id.len != 3 ||
            cpt->u.result.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
            cpt->u.result.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct, iff param is present. */
        if (cpt->u.result.param.len != 0 &&
            (cpt->u.result.operation.len <= 2 ||
             (cpt->u.result.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_TTC &&
              cpt->u.result.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_TTC) ||
             cpt->u.result.operation.data[1] == 0))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        else if (cpt->u.result.param.len == 0 &&
                 cpt->u.result.operation.len != 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_ERROR_TTC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.error.invoke_id.len != 3 ||
            cpt->u.error.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
            cpt->u.error.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (cpt->u.error.error.len <= 2 ||
            (cpt->u.error.error.data[0] != TCAP_PN_LOCAL_ERR_TAG_TTC &&
             cpt->u.error.error.data[0] != TCAP_PN_GLOBAL_ERR_TAG_TTC))
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_CANCEL_TTC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_U_REJECT_TTC:
        if (cpt->u.reject.problem.len == 0 ||
            (cpt->u.reject.problem.data[0] != TCAP_PROB_GENERAL_TTC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_INVOKE_TTC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_RES_TTC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_ERR_TTC) ||
            cpt->u.reject.problem.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_TIMER_RESET_TTC:
        /* The variant must be ITU White Book 97. */
        if(TTC_TCAP_Variant < TTC_TCAP_WHITE_BOOK_97)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP component
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for the end user.
 *
 *  Input Parameters:
 *      cpt - the TCAP component to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADTCAPMESSAGE - the component is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorComponentSanityCheck_TTC(TCAP_CPT *cpt)
{
    /* sanity check the component */
    switch (cpt->ptype)
    {
    case TCAP_PT_TC_INVOKE_TTC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.invoke.invoke_id.len != 3 ||
            cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
            cpt->u.invoke.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* operation is mandatory and must be correct */
        if (cpt->u.invoke.operation.len <= 2 ||
            (cpt->u.invoke.operation.data[0] != TCAP_PN_LOCAL_OP_TAG_TTC &&
             cpt->u.invoke.operation.data[0] != TCAP_PN_GLOBAL_OP_TAG_TTC) ||
            cpt->u.invoke.operation.data[1] == 0)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        /* if linked id is present it must be correct */
        if (cpt->u.invoke.linked_id.len != 0 &&
            (cpt->u.invoke.linked_id.len != 3 ||
             cpt->u.invoke.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
             cpt->u.invoke.invoke_id.data[1] != 1))
        {
            return (ITS_BADTCAPMESSAGE);
        }

        break;

    case TCAP_PT_TC_RESULT_L_TTC:
    case TCAP_PT_TC_RESULT_NL_TTC:
    case TCAP_PT_TC_U_ERROR_TTC:
    case TCAP_PT_TC_U_CANCEL_TTC:
    case TCAP_PT_TC_U_REJECT_TTC:
        return TCAP_ComponentSanityCheck_TTC(cpt);

    /* stack only messages */
    case TCAP_PT_TC_R_REJECT_TTC:
    case TCAP_PT_TC_L_REJECT_TTC:
        if (cpt->u.reject.problem.len == 0 ||
            (cpt->u.reject.problem.data[0] != TCAP_PROB_GENERAL_TTC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_INVOKE_TTC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_RES_TTC &&
             cpt->u.reject.problem.data[0] != TCAP_PROB_RETURN_ERR_TTC) ||
            cpt->u.reject.problem.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    case TCAP_PT_TC_L_CANCEL_TTC:
        /* invoke id is mandatory and must be correct */
        if (cpt->u.cancel.invoke_id.len != 3 ||
            cpt->u.cancel.invoke_id.data[0] != TCAP_PN_INVOKE_TAG_TTC ||
            cpt->u.cancel.invoke_id.data[1] != 1)
        {
            return (ITS_BADTCAPMESSAGE);
        }
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_DialogueSanityCheck_TTC(TCAP_DLG *dlg)
{
    ITS_OCTET ai, ssn, gttInfo[SCCP_MAX_ADDR_LEN];
    ITS_UINT pc;
    ITS_USHORT gttLen;

    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_TTC:
        if (dlg->u.uni.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.uni.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.uni.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (TTC_TCAP_Variant < TTC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.uni.ac_name.len != 0 ||
                dlg->u.uni.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_BEGIN_TTC:
        if (dlg->u.begin.orig_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS ||
            dlg->u.begin.dest_addr.len == 0 ||
            SCCP_DecodeAddr(&dlg->u.begin.dest_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (TTC_TCAP_Variant < TTC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.begin.ac_name.len != 0 ||
                dlg->u.begin.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_CONTINUE_TTC:
        if (dlg->u.cont.orig_addr.len != 0 &&
            SCCP_DecodeAddr(&dlg->u.cont.orig_addr,
                            &ai, &pc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (TTC_TCAP_Variant < TTC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.cont.ac_name.len != 0 ||
                dlg->u.cont.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_END_TTC:
        if (dlg->u.end.termination != TCAP_END_BASIC &&
            dlg->u.end.termination != TCAP_END_PREARRANGED)
        {
            return (ITS_BADTCAPMESSAGE);
        }

        if (TTC_TCAP_Variant < TTC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.end.ac_name.len != 0 ||
                dlg->u.end.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    case TCAP_PT_TC_U_ABORT_TTC:
        if (TTC_TCAP_Variant < TTC_TCAP_WHITE_BOOK)
        {
            if (dlg->u.abort.ac_name.len != 0 ||
                dlg->u.abort.user_info.len != 0)
            {
                return (ITS_BADTCAPMESSAGE);
            }
        }

        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the values specified in a TCAP dialogue
 *      are valid for the protocol family.  This particular function is
 *      intended for vendor implementations, not for end users.
 *
 *  Input Parameters:
 *      dlg - the TCAP dialogue to check sanity for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the dialogue is coherent
 *      ITS_BADTCAPMESSAGE - the dialogue is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
TCAP_VendorDialogueSanityCheck_TTC(TCAP_DLG *dlg)
{
    switch (dlg->ptype)
    {
    case TCAP_PT_TC_UNI_TTC:
    case TCAP_PT_TC_BEGIN_TTC:
    case TCAP_PT_TC_CONTINUE_TTC:
    case TCAP_PT_TC_END_TTC:
    case TCAP_PT_TC_U_ABORT_TTC:
        return TCAP_DialogueSanityCheck(dlg);

    case TCAP_PT_TC_P_ABORT_TTC:
        break;

    case TCAP_PT_TC_NOTICE_TTC:
        break;

    default:
        return (ITS_BADTCAPMESSAGE);
    }

    return (ITS_SUCCESS);
}

#endif

