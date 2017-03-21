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
 *  ID: $Id: itu-tcap_cvt.c,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:56  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:30  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:37  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.10.1  2004/10/19 10:30:20  sswami
 * LOG: Modified TIDToData for tid >=0xFFXXXXXX
 * LOG:
 * LOG: Revision 7.3  2003/01/07 15:26:07  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/09/26 22:18:20  yranade
 * LOG: 64 bit issues.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/07/03 17:40:49  mmiers
 * LOG: More china changes
 * LOG:
 * LOG: Revision 6.4  2002/06/07 19:48:12  mmiers
 * LOG: Add QOSI_PROT_VER
 * LOG:
 * LOG: Revision 6.3  2002/05/17 17:52:02  mmiers
 * LOG: Add a define for returning fixed size TIDs
 * LOG:
 * LOG: Revision 6.2  2002/03/20 20:07:48  mmiers
 * LOG: Move the ASNC library to the VFrame (as on UNIX).
 * LOG:
 * LOG: Revision 6.1  2002/03/20 17:56:24  mmiers
 * LOG: Move the codecs back.  It's consistent, so I'll just deal
 * LOG: with the VFrame pain (ASN).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/19 18:03:02  mmiers
 * LOG: Adax testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 5.1  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.5  2001/11/21 00:21:20  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.3  2001/10/31 22:14:03  mmiers
 * LOG: Add bitfield test
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.3  2000/11/29 17:50:44  mmiers
 * LOG: Weird Cisco TCAP fix.
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:05:49  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/11/06 17:29:09  fhasle
 * LOG:
 * LOG: fixed bug when parsing AARE dialogue portion "AC name not suuported"
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:45  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/06/26 21:28:48  mmiers
 * LOG:
 * LOG:
 * LOG: Mem leak plugging.
 * LOG:
 * LOG: Revision 2.4  2000/04/13 20:45:43  mmiers
 * LOG:
 * LOG:
 * LOG: Fix bit pattern bug.
 * LOG:
 * LOG: Revision 2.3  2000/03/23 20:21:30  mmiers
 * LOG:
 * LOG:
 * LOG: Final IntelliSS7 changes from Plano.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:29  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:40:30  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is very unforgiving.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:09  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.29  1999/10/08 21:51:49  rsonak * LOG:
 * LOG: Fixed more memory leaks. 'ac' wasnt getting freed in BuildDialogue.
 * LOG: In fact 'ui' also doesnt seem to be getting freed in BuildDialogue.
 * LOG:
 * LOG: Revision 1.28  1999/10/08 19:14:26  rsonak
 * LOG:
 * LOG: Fixed memory leaks. Some PEs (ac and ui) were not egtting freed.
 * LOG:
 * LOG: Revision 1.27  1999/10/06 15:36:20  cbascon
 * LOG:
 * LOG: fhasle: fix bug when sending Error Component (if Error Code was local,
 * LOG:         Error Code in PDU was not set).
 * LOG:
 * LOG: Revision 1.26  1999/09/30 20:34:05  mmiers
 * LOG:
 * LOG:
 * LOG: Don't include a reason if the user didn't give us one.
 * LOG:
 * LOG: Revision 1.25  1999/09/30 14:51:12  mmiers
 * LOG:
 * LOG:
 * LOG: Hack to get L_REJECT working with our stack.
 * LOG:
 * LOG: Revision 1.24  1999/09/24 22:18:20  mmiers
 * LOG:
 * LOG:
 * LOG: Commit the fix for AARE in U-ABORT situations.
 * LOG:
 * LOG: Revision 1.23  1999/09/23 22:21:17  ite
 * LOG:
 * LOG: passing correct msg type in BuildDialoguePortion function call
 * LOG:
 * LOG: Revision 1.22  1999/09/23 20:07:00  ite
 * LOG:
 * LOG: fixed Dialogue-As-ID value bug (encoded value was used instead of decoded one).
 * LOG:
 * LOG: Revision 1.21  1999/09/17 16:01:06  labuser
 * LOG:
 * LOG:
 * LOG: Move the variant variable into tcap.c
 * LOG:
 * LOG: Revision 1.20  1999/09/17 15:51:44  labuser
 * LOG:
 * LOG:
 * LOG: Oops, missed one.
 * LOG:
 * LOG: Revision 1.19  1999/09/17 15:50:48  labuser
 * LOG:
 * LOG:
 * LOG: Remove cast warnings.
 * LOG:
 * LOG: Revision 1.18  1999/09/10 23:11:07  mmiers
 * LOG:
 * LOG:
 * LOG: Split out blue book and white book variants.
 * LOG:
 * LOG: Revision 1.17  1999/09/09 17:01:07  ite
 * LOG:
 * LOG: fhasle: fixed setting type of reject (remote or User) for
 * LOG:         return error problem, when receiving Reject cpt.
 * LOG:
 * LOG: Revision 1.16  1999/09/08 23:04:46  mmiers
 * LOG:
 * LOG:
 * LOG: Remove extra brace.
 * LOG:
 * LOG: Revision 1.15  1999/09/08 23:04:16  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the sign for invoke ids.
 * LOG:
 * LOG: Revision 1.14  1999/09/08 20:04:58  mmiers
 * LOG:
 * LOG:
 * LOG: Include global error and operation codes.
 * LOG:
 * LOG: Revision 1.13  1999/09/01 15:34:26  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Fred's testing.
 * LOG:
 * LOG: Revision 1.12  1999/08/30 21:28:58  mmiers
 * LOG:
 * LOG:
 * LOG: Fold in Fred's finding of U_REJECT codes.
 * LOG:
 * LOG: Revision 1.11  1999/08/27 15:58:52  ssharma
 * LOG:
 * LOG:
 * LOG: Abort logic in encode was wrong.  Initialize the hdr type for TCAP.
 * LOG:
 * LOG: Revision 1.10  1999/08/25 21:22:41  mmiers
 * LOG:
 * LOG:
 * LOG: Add error checking for components and dialogue (sanity checks).
 * LOG:
 * LOG: Revision 1.9  1999/08/25 17:41:36  ite
 * LOG:
 * LOG:
 * LOG: Fix the sign extend.
 * LOG:
 * LOG: Revision 1.8  1999/08/25 17:20:33  ite
 * LOG:
 * LOG:
 * LOG: Sign extend TIDs when retrieving from PDU.
 * LOG:
 * LOG: Revision 1.7  1999/08/20 17:10:42  ite
 * LOG:
 * LOG:
 * LOG: Build the TID correctly for CCITT.
 * LOG:
 * LOG: Revision 1.6  1999/08/19 22:33:12  mmiers
 * LOG:
 * LOG:
 * LOG: Remove dead parameter.
 * LOG:
 * LOG: Revision 1.5  1999/07/30 15:26:46  hdivoux
 * LOG:
 * LOG:
 * LOG: Compute the size of operation code (don't hardcode it).
 * LOG:
 * LOG: Revision 1.4  1999/06/18 23:13:26  mmiers
 * LOG:
 * LOG:
 * LOG: ITU TIDs are zero to four bytes, not fixed size as in ANSI
 * LOG:
 * LOG: Revision 1.3  1999/06/15 22:41:42  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build for function signatures, predefines.
 * LOG:
 * LOG: Revision 1.2  1999/06/04 21:56:39  mmiers
 * LOG:
 * LOG:
 * LOG: Update to reflect that the op code can be an OID.
 * LOG:
 * LOG: Revision 1.1  1999/05/24 20:25:45  mmiers
 * LOG:
 * LOG:
 * LOG: Move the codec into the library for sharing.
 * LOG:
 * LOG: Revision 1.10  1999/05/18 17:00:17  mmiers
 * LOG:
 * LOG:
 * LOG: Initial coding of ITU TCAP complete.  Much testing and FIXME
 * LOG: removal to do.
 * LOG:
 * LOG: Revision 1.9  1999/05/17 23:05:38  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.8  1999/05/11 00:54:34  mmiers
 * LOG:
 * LOG:
 * LOG: Slight bug fixes.
 * LOG:
 * LOG: Revision 1.7  1999/03/17 21:37:52  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.6  1999/03/17 18:39:50  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.5  1999/03/01 20:29:10  mmiers
 * LOG:
 * LOG:
 * LOG: Update this with latest TCAP changes.
 * LOG:
 * LOG: Revision 1.4  1999/02/20 00:00:04  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.3  1999/02/19 00:40:52  mmiers
 * LOG:
 * LOG:
 * LOG: Work on ITU.
 * LOG:
 * LOG: Revision 1.2  1999/02/17 20:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Get ITU conversion to compile.
 * LOG:
 * LOG: Revision 1.1  1999/02/17 02:30:58  mmiers
 * LOG:
 * LOG:
 * LOG: Add this file.  Won't compile yet.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#ident "$Id: itu-tcap_cvt.c,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $"

#if defined(CCITT)

#include <itu/tcap.h>

#elif defined(PRC)

#include <china/tcap.h>

#endif

#include <stdlib.h>

static unsigned int UnidialogueAsIDValue[] =
{
    0x00U,  /* CCITT */
    0x00U,  /* Recommendation */
    0x11U,  /* Q */
    0x0305U,/* 773 */
    0x01U,  /* as(1) */
    0x02U,  /* unidialoguePDU(2) */
    0x01U   /* version1(1) */
};
static unsigned int DialogueAsIDValue[] =
{
    0x00U,  /* CCITT */
    0x00U,  /* Recommendation */
    0x11U,  /* Q */
    0x0305U,/* 773 */
    0x01U,  /* as(1) */
    0x01U,  /* dialoguePDU(1) */
    0x01U   /* version1(1) */
};
static OIDentifier UnidialogueAsID =
{
    sizeof(UnidialogueAsIDValue) / sizeof(unsigned int),
    UnidialogueAsIDValue
};
static OIDentifier DialogueAsID =
{
    sizeof(DialogueAsIDValue) / sizeof(unsigned int),
    DialogueAsIDValue
};

static int
TIDToData(ITS_OCTET *d, ITS_UINT t, ITS_UINT len)
{
#if FIXED_SIZE_TIDS

    d[0] = (t >> 24) & 0xFFU;
    d[1] = (t >> 16) & 0xFFU;
    d[2] = (t >> 8) & 0xFFU;
    d[3] = (t & 0xFFU;

    return (sizeof(ITS_UINT));

#else

    int opSize = sizeof(ITS_UINT);
    ITS_UINT code = t;
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
#if 0
        if (opSize != sizeof(ITS_UINT) &&
            ((code >> ((opSize -1) * ITS_BITS_PER_BYTE) & 0x80) == 0x80))
        {
            opSize++;
        }
#endif

    }
    else
    {
        opSize = 1;
    }

    for (i = opSize; i > 0; i--)
    {
        d[opSize - i] = (ITS_OCTET)((code >> ((i - 1) * ITS_BITS_PER_BYTE)) &
                                     0x0FF);
    }

    /* weird Cisco bug */
    if (len > (ITS_UINT)opSize)
    {
        memmove(&d[len - opSize], d, opSize);
        memset(d, 0, len - opSize);

        opSize = (int)len;
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

/*
 * From NMS:
 *
 * MTP3 type:    0x01
 * SIO:          0x03
 * RoutingLabel: 0x02 0x40 0x00 0x60
 * SCCP MsgType: 0x09
 *  PClass:      0x81
 *  Ptr to CDP:  0x03
 *  Ptr to CLP:  0x07
 *  Ptr to data: 0x0b
 *  CDP:         0x04 0x43 0x02 0x00 0x04
 *  CLP:         0x04 0x43 0x01 0x00 0x03
 *  Data len:    0x29
 * TCAP MsgType: 0x62 [APPLICATION 2]
 *          len: 0x27
 * OTID:         0x48 [APPLICATION 8]
 *          len: 0x01
 *          val: 0x1d
 * DialoguePTag: 0x6b [APPLICATION 11]
 *          len: 0x22
 * EXTERNAL Tag: 0x28 [UNIVERSAL 8] (EXTERNAL)
 *          len: 0x20
 * directrefTag: 0x06 [UNIVERSAL 6] (OID)
 *          len: 0x07
 * Value: ccitt: 0x00
 *          'q': 0x11
 *          773: 0x86 0x05
 *        as(1): 0x01
 * dialogPDU(1): 0x01
 *  version1(1): 0x01
 *   singleASN1: 0xa0 [CONTEXT-SPECIFIC 0]
 *          len: 0x15
 * dialogReqTag: 0x60
 *          len: 0x13
 * protocolVTag: 0x80
 *          len: 0x02
 *         bits: 0x07 0x80
 *  AC name tag: 0xa1
 *          len: 0x0d
 *      AC name: 0x06 [UNIVERSAL 6] (OID)
 *          len: 0x0b
 *    bogus tag: 0xa1
 *          len: 0x09
 * bogus OIDTag: 0x06
 *          len: 0x07
 *       AC OID: 0x04 0x00 0x00 0x01 0x00 0x0f 0x02
 *          EOC: 0x00 0x00
 *      Garbage: 0x70 0xf6 0x7d 0x01 0x00 0x00 0x00 0x00 0x2c 0x6a 0x00
 */
static PE
BuildDialoguePortion(ITS_USHORT ptype,
                     ITS_OCTET *applicationContext, ITS_USHORT acLen,
                     ITS_OCTET *userInformation, ITS_USHORT uiLen,
                     ITS_BOOLEAN accept, ITS_BOOLEAN fromUser,
                     ITS_BOOLEAN causeACName, ITS_BOOLEAN includePV)
{
    struct type_UNIV_EXTERNAL* dp;
    int err;
    PE pv;
    PE ac;
    PE ui;
    PE ret = NULL;
    char buf[8];

    if (acLen == 0 && uiLen == 0)
    {
        return (NULL);
    }

    dp = (struct type_UNIV_EXTERNAL *)
        calloc(1, sizeof(struct type_UNIV_EXTERNAL));
    if (dp == NULL)
    {
        return (NULL);
    }

    if (ptype == TCPPT_TC_UNI)
    {
        dp->direct__reference = oid_cpy(&UnidialogueAsID);
    }
    else
    {
        dp->direct__reference = oid_cpy(&DialogueAsID);
    }

    dp->encoding = (struct choice_UNIV_0 *)
        calloc(1, sizeof(struct choice_UNIV_0));
    if (dp->encoding == NULL)
    {
        free(dp);

        return (NULL);
    }

    dp->encoding->offset = choice_UNIV_0_single__ASN1__type;

    switch (ptype)
    {
    case TCPPT_TC_UNI:
        {
            struct type_ITU__TCAP__APDU_AUDT__apdu* audt;

            audt = (struct type_ITU__TCAP__APDU_AUDT__apdu *)
                calloc(1, sizeof(struct type_ITU__TCAP__APDU_AUDT__apdu));

            if (audt == NULL)
            {
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            /* protocol version */
            if (includePV)
            {
                int2strb(1 << bit_ITU__TCAP__APDU_protocol__version_version1,
                         1, buf, 8);
                pv = strb2bitstr(buf, 1,
                                 PE_CLASS_UNIV, PE_FORM_PRIM);
                audt->protocol__version = bit2prim(pv);
            }

            /* application context */
            if (acLen)
            {
                ac = ssdu2pe((char *)applicationContext, acLen, NULL, &err);

                if (err != PS_ERR_NONE)
                {
                    free(audt);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }

                audt->application__context__name = prim2oid(ac);
                pe_free(ac);
            }

            /* user information */
            if (uiLen)
            {
                ui = ssdu2pe((char *)userInformation, uiLen, NULL, &err);

                if (err != PS_ERR_NONE)
                {
                    free(audt);
                    oid_free(audt->application__context__name);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }

                if (decode_ITU__TCAP__APDU_UserInformation(ui, 1, NULL, NULL,
                                                     (char **)&audt->
                                                        user__information) ==
                    NOTOK)
                {
                    free(audt);
                    oid_free(audt->application__context__name);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }
            }

            if (encode_ITU__TCAP__APDU_AUDT__apdu(&dp->encoding->
                                                      un.single__ASN1__type,
                                                  1, 0, NULL,
                                                  (char *)audt) == NOTOK)
            {
                free(audt);
                oid_free(audt->application__context__name);
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            free_ITU__TCAP__APDU_AUDT__apdu(audt);
        }

        if (encode_UNIV_EXTERNAL(&ret, 1, 0, NULL, (char *)dp) == NOTOK)
        {
            free(dp->encoding);
            free(dp);

            return (NULL);
        }

        free_UNIV_EXTERNAL(dp);

        break;

    case TCPPT_TC_BEGIN:
        {
            struct type_ITU__TCAP__APDU_AARQ__apdu* aarq;

            aarq = (struct type_ITU__TCAP__APDU_AARQ__apdu *)
                calloc(1, sizeof(struct type_ITU__TCAP__APDU_AARQ__apdu));

            if (aarq == NULL)
            {
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            /* protocol version */
            if (includePV)
            {
                int2strb(1 << bit_ITU__TCAP__APDU_protocol__version_version1,
                         1, buf, 8);
                pv = strb2bitstr(buf, 1,
                                 PE_CLASS_UNIV, PE_FORM_PRIM);
                aarq->protocol__version = bit2prim(pv);
            }

            /* application context */
            if (acLen)
            {
                ac = ssdu2pe((char *)applicationContext, acLen, NULL, &err);

                if (err != PS_ERR_NONE)
                {
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }

                aarq->application__context__name = prim2oid(ac);
                pe_free(ac);
            }

            /* user information */
            if (uiLen)
            {
                ui = ssdu2pe((char *)userInformation, uiLen, NULL, &err);

                if (err != PS_ERR_NONE)
                {
                    oid_free(aarq->application__context__name);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }

                if (decode_ITU__TCAP__APDU_UserInformation(ui, 1, NULL, NULL,
                                                     (char **)&aarq->
                                                        user__information) ==
                    NOTOK)
                {
                    oid_free(aarq->application__context__name);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }
            }

            if (encode_ITU__TCAP__APDU_AARQ__apdu(&dp->encoding->
                                                      un.single__ASN1__type,
                                                  1, 0, NULL,
                                                  (char *)aarq) == NOTOK)
            {
                free(aarq);
                oid_free(aarq->application__context__name);
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            free_ITU__TCAP__APDU_AARQ__apdu(aarq);
        }

        if (encode_UNIV_EXTERNAL(&ret, 1, 0, NULL, (char *)dp) == NOTOK)
        {
            free(dp->encoding);
            free(dp);

            return (NULL);
        }

        free_UNIV_EXTERNAL(dp);

        break;

    case TCPPT_TC_CONTINUE:
    case TCPPT_TC_END:
        {
            struct type_ITU__TCAP__APDU_AARE__apdu* aare;

            aare = (struct type_ITU__TCAP__APDU_AARE__apdu *)
                calloc(1, sizeof(struct type_ITU__TCAP__APDU_AARE__apdu));

            if (aare == NULL)
            {
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            /* protocol version */
            if (includePV)
            {
                int2strb(1 << bit_ITU__TCAP__APDU_protocol__version_version1,
                         1, buf, 8);
                pv = strb2bitstr(buf, 1,
                                 PE_CLASS_UNIV, PE_FORM_PRIM);
                aare->protocol__version = bit2prim(pv);
            }

            /* application context */
            if (acLen)
            {
                ac = ssdu2pe((char *)applicationContext, acLen, NULL, &err);

                if (err != PS_ERR_NONE)
                {
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }

                aare->application__context__name = prim2oid(ac);
                pe_free(ac);
            }

            /* result */
            aare->result = (struct type_ITU__TCAP__APDU_Associate__result *)
                calloc(1,
                       sizeof(struct type_ITU__TCAP__APDU_Associate__result));
            if (aare->result == NULL)
            {
                oid_free(aare->application__context__name);
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            if (accept)
            {
                aare->result->parm =
                    int_ITU__TCAP__APDU_Associate__result_accepted;
            }
            else
            {
                aare->result->parm =
                    int_ITU__TCAP__APDU_Associate__result_reject__permanent;
            }

            /* result source diagnostic */
            aare->result__source__diagnostic =
                (struct type_ITU__TCAP__APDU_Associate__source__diagnostic *)
                    calloc(1, sizeof(struct type_ITU__TCAP__APDU_Associate__source__diagnostic));
            if (aare->result__source__diagnostic == NULL)
            {
                oid_free(aare->application__context__name);
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            if (fromUser)
            {
                aare->result__source__diagnostic->offset =
                    type_ITU__TCAP__APDU_Associate__source__diagnostic_dialogue__service__user;

                if (!causeACName)
                {
                    aare->result__source__diagnostic->un.dialogue__service__user =
                        int_ITU__TCAP__APDU_dialogue__service__user_null;
                }
                else
                {
                    aare->result__source__diagnostic->
                        un.dialogue__service__user =
                            int_ITU__TCAP__APDU_dialogue__service__user_application__context__name__not__supported;
                }
            }
            else
            {
                aare->result__source__diagnostic->offset =
                    type_ITU__TCAP__APDU_Associate__source__diagnostic_dialogue__service__provider;

                if (accept)
                {
                    aare->result__source__diagnostic->
                        un.dialogue__service__provider =
                            int_ITU__TCAP__APDU_dialogue__service__provider_null;
                }
                else
                {
                    aare->result__source__diagnostic->
                        un.dialogue__service__provider =
                            int_ITU__TCAP__APDU_dialogue__service__provider_no__common__dialogue__portion;
                }
            }


            /* user information */
            if (uiLen)
            {
                ui = ssdu2pe((char *)userInformation, uiLen, NULL, &err);

                if (err != PS_ERR_NONE)
                {
                    oid_free(aare->application__context__name);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }

                if (decode_ITU__TCAP__APDU_UserInformation(ui, 1, NULL, NULL,
                                                     (char **)&aare->
                                                        user__information) ==
                    NOTOK)
                {
                    oid_free(aare->application__context__name);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }
            }

            if (encode_ITU__TCAP__APDU_AARE__apdu(&dp->encoding->
                                                      un.single__ASN1__type,
                                                  1, 0, NULL,
                                                  (char *)aare) == NOTOK)
            {
                free(aare);
                oid_free(aare->application__context__name);
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            free_ITU__TCAP__APDU_AARE__apdu(aare);
        }

        if (encode_UNIV_EXTERNAL(&ret, 1, 0, NULL, (char *)dp) == NOTOK)
        {
            free(dp->encoding);
            free(dp);

            return (NULL);
        }

        free_UNIV_EXTERNAL(dp);

        break;

    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:
        {
            struct type_ITU__TCAP__APDU_ABRT__apdu* abrt;

            abrt = (struct type_ITU__TCAP__APDU_ABRT__apdu *)
                calloc(1, sizeof(struct type_ITU__TCAP__APDU_ABRT__apdu));

            if (abrt == NULL)
            {
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            /* abort source */
            abrt->abort__source = (struct type_ITU__TCAP__APDU_ABRT__source *)
                calloc(1, sizeof(struct type_ITU__TCAP__APDU_ABRT__source));
            if (abrt->abort__source == NULL)
            {
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            if (fromUser)
            {
                abrt->abort__source->parm =
                    int_ITU__TCAP__APDU_ABRT__source_dialogue__service__user;
            }
            else
            {
                abrt->abort__source->parm =
                    int_ITU__TCAP__APDU_ABRT__source_dialogue__service__provider;
            }

            /* user information */
            if (uiLen)
            {
                ui = ssdu2pe((char *)userInformation, uiLen, NULL, &err);

                if (err != PS_ERR_NONE)
                {
                    free(abrt->abort__source);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }

                if (decode_ITU__TCAP__APDU_UserInformation(ui, 1, NULL, NULL,
                                                     (char **)&abrt->
                                                        user__information) ==
                    NOTOK)
                {
                    free(abrt->abort__source);
                    free(dp->encoding);
                    free(dp);

                    return (NULL);
                }
            }

            if (encode_ITU__TCAP__APDU_ABRT__apdu(&dp->encoding->
                                                      un.single__ASN1__type,
                                                  1, 0, NULL,
                                                  (char *)abrt) == NOTOK)
            {
                free(abrt);
                free(dp->encoding);
                free(dp);

                return (NULL);
            }

            free_ITU__TCAP__APDU_ABRT__apdu(abrt);
        }

        if (encode_UNIV_EXTERNAL(&ret, 1, 0, NULL, (char *)dp) == NOTOK)
        {
            free(dp->encoding);
            free(dp);

            return (NULL);
        }

        free_UNIV_EXTERNAL(dp);

        break;
    }

    return (ret);
}

static ITS_BOOLEAN
ParseDialoguePortion(ITS_USHORT ptype,
                     PE pe,
                     ITS_OCTET *applicationContext, ITS_USHORT *acLen,
                     ITS_OCTET *userInformation, ITS_USHORT *uiLen,
                     ITS_BOOLEAN *fromUser, ITS_BOOLEAN *accept,
                     ITS_BOOLEAN *causeACName, ITS_BOOLEAN *hasPV)
{
    int tval;
    PE ac;
    PE ui;
    char *tmp;
    struct type_UNIV_EXTERNAL *dp;

    *acLen = 0;
    *uiLen = 0;
    *fromUser = ITS_FALSE;
    *accept = ITS_FALSE;
    *hasPV = ITS_FALSE;

    if (pe == NULL)
    {
        return (ITS_TRUE);
    }

    if (decode_UNIV_EXTERNAL(pe, 1, 0, NULL, (char **)&dp) == NOTOK)
    {
        return (ITS_FALSE);
    }

    if (ptype == TCPPT_TC_UNI)
    {
        if (oid_cmp(dp->direct__reference, &UnidialogueAsID) != 0)
        {
            free_UNIV_EXTERNAL(dp);

            return (ITS_FALSE);
        }
    }
    else
    {
        if (oid_cmp(dp->direct__reference, &DialogueAsID) != 0)
        {
            free_UNIV_EXTERNAL(dp);

            return (ITS_FALSE);
        }
    }

    if (dp->encoding == NULL)
    {
        free_UNIV_EXTERNAL(dp);

        return (ITS_FALSE);
    }

    if (dp->encoding->offset != choice_UNIV_0_single__ASN1__type)
    {
        free_UNIV_EXTERNAL(dp);

        return (ITS_FALSE);
    }

    if (dp->encoding->un.single__ASN1__type == NULL)
    {
        free_UNIV_EXTERNAL(dp);

        return (ITS_TRUE); /* FIXME: is this right */
    }

    switch (ptype)
    {
    case TCPPT_TC_UNI:
        {
            struct type_ITU__TCAP__APDU_AUDT__apdu* audt;

            if (decode_ITU__TCAP__APDU_AUDT__apdu(dp->encoding->
                                                      un.single__ASN1__type,
                                                      1, 0, NULL,
                                                      (char **)&audt) == NOTOK)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_FALSE);
            }

            if (audt == NULL)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_TRUE);
            }

            /* protocol version */
            if (audt->protocol__version != NULL)
            {
                *hasPV = ITS_TRUE;
            }

            /* application context */
            if (audt->application__context__name)
            {
                ac = oid2prim(audt->application__context__name);
                if (pe2ssdu(ac, &tmp, &tval) != OK)
                {
                    free_ITU__TCAP__APDU_AUDT__apdu(audt);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                *acLen = (ITS_USHORT)tval;
                memcpy(applicationContext, tmp, tval);

                if (tval)
                {
                    free(tmp);
                }

                pe_free(ac);
            }

            /* user information */
            if (audt->user__information)
            {
                if (encode_ITU__TCAP__APDU_UserInformation(&ui, 1, 0, NULL,
                                                     (char *)audt->user__information)
                    == NOTOK)
                {
                    free_ITU__TCAP__APDU_AUDT__apdu(audt);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                if (pe2ssdu(ui, &tmp, &tval) != OK)
                {
                    free_ITU__TCAP__APDU_AUDT__apdu(audt);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                *uiLen = (ITS_USHORT)tval;

                memcpy(userInformation, tmp, tval);

                pe_free(ui);

                if (tval)
                {
                    free(tmp);
                }
            }

            free_ITU__TCAP__APDU_AUDT__apdu(audt);

            free_UNIV_EXTERNAL(dp);

            return (ITS_TRUE);
        }

        break;

    case TCPPT_TC_BEGIN:
        {
            struct type_ITU__TCAP__APDU_AARQ__apdu* aarq;

            if (decode_ITU__TCAP__APDU_AARQ__apdu(dp->encoding->
                                                      un.single__ASN1__type,
                                                  1, 0, NULL,
                                                  (char **)&aarq) == NOTOK)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_FALSE);
            }

            if (aarq == NULL)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_TRUE);
            }

            /* protocol version */
            if (aarq->protocol__version != NULL)
            {
                *hasPV = ITS_TRUE;
            }

            /* application context */
            if (aarq->application__context__name)
            {
                ac = oid2prim(aarq->application__context__name);
                if (pe2ssdu(ac, &tmp, &tval) != OK)
                {
                    free_ITU__TCAP__APDU_AARQ__apdu(aarq);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                *acLen = (ITS_USHORT)tval;
                memcpy(applicationContext, tmp, tval);

                if (tval)
                {
                    free(tmp);
                }

                pe_free(ac);
            }

            /* user information */
            if (aarq->user__information)
            {
                if (encode_ITU__TCAP__APDU_UserInformation(&ui, 1, 0, NULL,
                                                           (char *)aarq->
                                                               user__information)
                    == NOTOK)
                {
                    free_ITU__TCAP__APDU_AARQ__apdu(aarq);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                if (pe2ssdu(ui, &tmp, &tval) != OK)
                {
                    free_ITU__TCAP__APDU_AARQ__apdu(aarq);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                *uiLen = (ITS_USHORT)tval;

                memcpy(userInformation, tmp, tval);

                if (tval)
                {
                    free(tmp);
                }

                pe_free(ui);
            }

            free_ITU__TCAP__APDU_AARQ__apdu(aarq);

            free_UNIV_EXTERNAL(dp);

            return (ITS_TRUE);
        }

        break;

    case TCPPT_TC_CONTINUE:
    case TCPPT_TC_END:
        {
            struct type_ITU__TCAP__APDU_AARE__apdu* aare;

            if (decode_ITU__TCAP__APDU_AARE__apdu(dp->encoding->
                                                      un.single__ASN1__type,
                                                  1, 0, NULL,
                                                  (char **)&aare) == NOTOK)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_FALSE);
            }

            if (aare == NULL)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_TRUE);
            }

            /* protocol version */
            if (aare->protocol__version != NULL)
            {
                *hasPV = ITS_TRUE;
            }

            /* application context */
            if (aare->application__context__name)
            {
                ac = oid2prim(aare->application__context__name);
                if (pe2ssdu(ac, &tmp, &tval) != OK)
                {
                    free_ITU__TCAP__APDU_AARE__apdu(aare);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                *acLen = (ITS_USHORT)tval;
                memcpy(applicationContext, tmp, tval);

                if (tval)
                {
                    free(tmp);
                }

                pe_free(ac);
            }


            /* result */
            if (aare->result->parm ==
                int_ITU__TCAP__APDU_Associate__result_accepted)
            {
                *accept = ITS_TRUE;
            }
            else
            {
                *accept = ITS_FALSE;
            }

            /* result source diagnostic */
            if (aare->result__source__diagnostic == NULL)
            {
                free_ITU__TCAP__APDU_AARE__apdu(aare);

                free_UNIV_EXTERNAL(dp);

                return (ITS_FALSE);
            }

            if (aare->result__source__diagnostic->offset ==
                type_ITU__TCAP__APDU_Associate__source__diagnostic_dialogue__service__user)
            {
                *fromUser = ITS_TRUE;

                *causeACName = ITS_FALSE;

                if (aare->result__source__diagnostic->
                        un.dialogue__service__user ==
                    int_ITU__TCAP__APDU_dialogue__service__user_null)
                {
                    *accept = ITS_TRUE;
                }
                else if (aare->result__source__diagnostic->
                             un.dialogue__service__user ==
                         int_ITU__TCAP__APDU_dialogue__service__user_application__context__name__not__supported)
                {
                    *causeACName = ITS_TRUE;
                }
                else
                {
                    *accept = ITS_FALSE;
                }
            }
            else
            {
                *fromUser = ITS_FALSE;
                if (aare->result__source__diagnostic->
                        un.dialogue__service__provider ==
                    int_ITU__TCAP__APDU_dialogue__service__provider_null)
                {
                    *accept = ITS_TRUE;
                }
                else
                {
                    *accept = ITS_FALSE;
                }
            }


            /* user information */
            if (aare->user__information)
            {
                if (encode_ITU__TCAP__APDU_UserInformation(&ui, 1, 0, NULL,
                                                           (char *)aare->
                                                               user__information)
                    == NOTOK)
                {
                    free_ITU__TCAP__APDU_AARE__apdu(aare);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                if (pe2ssdu(ui, &tmp, &tval) != OK)
                {
                    free_ITU__TCAP__APDU_AARE__apdu(aare);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                *uiLen = (ITS_USHORT)tval;
                memcpy(userInformation, tmp, tval);

                pe_free(ui);

                if (tval)
                {
                    free(tmp);
                }
            }

            free_ITU__TCAP__APDU_AARE__apdu(aare);

            free_UNIV_EXTERNAL(dp);

            return (ITS_TRUE);
        }

        break;

    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:
        {
            struct type_ITU__TCAP__APDU_ABRT__apdu* abrt;

            if (decode_ITU__TCAP__APDU_ABRT__apdu(dp->encoding->
                                                      un.single__ASN1__type,
                                                  1, 0, NULL,
                                                  (char **)&abrt) == NOTOK)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_FALSE);
            }

            if (abrt == NULL)
            {
                free_UNIV_EXTERNAL(dp);

                return (ITS_TRUE);
            }

            /* abort source */
            if (abrt->abort__source == NULL)
            {
                free_ITU__TCAP__APDU_ABRT__apdu(abrt);

                free_UNIV_EXTERNAL(dp);

                return (ITS_FALSE);
            }

            if (abrt->abort__source->parm ==
                int_ITU__TCAP__APDU_ABRT__source_dialogue__service__user)
            {
                *fromUser = ITS_TRUE;
            }
            else
            {
                *fromUser = ITS_FALSE;
            }

            /* user information */
            if (abrt->user__information)
            {
                if (encode_ITU__TCAP__APDU_UserInformation(&ui, 1, 0, NULL,
                                                     (char *)abrt->user__information)
                    == NOTOK)
                {
                    free_ITU__TCAP__APDU_ABRT__apdu(abrt);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                if (pe2ssdu(ui, &tmp, &tval) != OK)
                {
                    free_ITU__TCAP__APDU_ABRT__apdu(abrt);

                    free_UNIV_EXTERNAL(dp);

                    return (ITS_FALSE);
                }

                *uiLen = (ITS_USHORT)tval;
                memcpy(userInformation, tmp, tval);

                if (tval)
                {
                    free(tmp);
                }

                pe_free(ui);
            }

            free_ITU__TCAP__APDU_ABRT__apdu(abrt);

            free_UNIV_EXTERNAL(dp);

            return (ITS_TRUE);
        }

        break;
    }

    return (ITS_FALSE);
}

/*.implementation:extern (or static)
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
 ****************************************************************************/
SS7DLLAPI struct type_ITU__TCAP_ComponentPDU *
TCAP_CvtCPTToComponentPDU_CCITT(TCAP_CPT *cpt)
{
    struct type_ITU__TCAP_ComponentPDU *ret;
    int i;

    /* allocate the component */
    ret = (struct type_ITU__TCAP_ComponentPDU *)
         calloc(1, sizeof(struct type_ITU__TCAP_ComponentPDU));
    if (ret == NULL)
    {
        return ret;
    }

    switch (cpt->ptype)
    {
    case TCPPT_TC_INVOKE:
        ret->offset = type_ITU__TCAP_ComponentPDU_invoke;

        /* allocate the invoke */
        ret->un.invoke = (struct type_ITU__TCAP_Invoke *)
            calloc(1, sizeof(struct type_ITU__TCAP_Invoke));
        if (ret == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the invokeID */
        ret->un.invoke->invokeID = (struct type_ITU__TCAP_InvokeIdType *)
            calloc(1, sizeof(struct type_ITU__TCAP_InvokeIdType));
        if (ret == NULL)
        {
            free(ret->un.invoke);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        ret->un.invoke->invokeID->parm = 0;
        ret->un.invoke->invokeID->parm =
            (signed char)cpt->u.invoke.invoke_id.data[2];

        if (cpt->u.invoke.linked_id.len != 0)
        {
            /* allocate the linkedID */
            ret->un.invoke->linkedID = (struct type_ITU__TCAP_InvokeIdType *)
                calloc(1, sizeof(struct type_ITU__TCAP_InvokeIdType));
            if (ret == NULL)
            {
                free(ret->un.invoke->invokeID);
                free(ret->un.invoke);
                free(ret);

                return (NULL);
            }

            ret->un.invoke->linkedID->parm = 0;
            for (i = 0;
                 i < cpt->u.invoke.linked_id.data[1] && i < sizeof(ITS_LONG);
                 i++)
            {
                ret->un.invoke->linkedID->parm <<= 8;
                ret->un.invoke->linkedID->parm |=
                    cpt->u.invoke.linked_id.data[2+i];
            }
        }

        /* allocate the operationCode */
        ret->un.invoke->operationCode =
            (struct type_ITU__TCAP_Operation *)
            calloc(1, sizeof(struct type_ITU__TCAP_Operation));
        if (ret == NULL)
        {
            free(ret->un.invoke->invokeID);
            free(ret->un.invoke->linkedID);
            free(ret->un.invoke);
            free(ret);

            return (NULL);
        }

        /* pay attention to local vs global code */
        if (cpt->u.invoke.operation.data[0] ==
            TCPPN_LOCAL_OP_TAG)
        {
            ret->un.invoke->operationCode->offset =
                type_ITU__TCAP_Operation_localCode;
            ret->un.invoke->operationCode->un.localCode = 0;
            for (i = 0;
                 i < cpt->u.invoke.operation.data[1] && i < sizeof(ITS_LONG);
                 i++)
            {
                ret->un.invoke->operationCode->un.localCode <<= 8;
                ret->un.invoke->operationCode->un.localCode |=
                    cpt->u.invoke.operation.data[2+i];
            }
        }
        else if (cpt->u.invoke.operation.data[0] ==
                 TCPPN_GLOBAL_OP_TAG)
        {
            PE tmp;
            int err;

            ret->un.invoke->operationCode->offset =
                type_ITU__TCAP_Operation_globalCode;

            tmp = ssdu2pe((char *)&cpt->u.invoke.operation.data[2],
                          cpt->u.invoke.operation.data[1],
                          NULL,
                          &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.invoke->operationCode);

                free(ret->un.invoke->invokeID);
                if (ret->un.invoke->linkedID)
                {
                    free(ret->un.invoke->linkedID);
                }
                free(ret->un.invoke);
                free(ret);

                return (NULL);
            }

            ret->un.invoke->operationCode->un.globalCode = prim2oid(tmp);
        }

        /* set up the PE for the param */
        if (cpt->u.invoke.param.len == 0)
        {
            ret->un.invoke->parameter = NULL;
        }
        else
        {
            int err;

            ret->un.invoke->parameter =
                ssdu2pe((char *)cpt->u.invoke.param.data,
                        cpt->u.invoke.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.invoke->operationCode);

                free(ret->un.invoke->invokeID);
                if (ret->un.invoke->linkedID)
                {
                    free(ret->un.invoke->linkedID);
                }
                free(ret->un.invoke);
                free(ret);

                return (NULL);
            }
        }

        break;

    case TCPPT_TC_RESULT_L:
        ret->offset = type_ITU__TCAP_ComponentPDU_returnResultLast;
        goto skipit;

    case TCPPT_TC_RESULT_NL:
        ret->offset = type_ITU__TCAP_ComponentPDU_returnResultNotLast;

skipit:
        ret->un.returnResultLast = (struct type_ITU__TCAP_ReturnResult *)
            calloc(1, sizeof(struct type_ITU__TCAP_ReturnResult));
        if (ret->un.returnResultLast == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the invokeID */
        ret->un.returnResultLast->invokeID = (struct type_ITU__TCAP_InvokeIdType *)
            calloc(1, sizeof(struct type_ITU__TCAP_InvokeIdType));
        if (ret == NULL)
        {
            free(ret->un.returnResultLast);
            free(ret);

            return (NULL);
        }
        /* copy in the invoke info */
        ret->un.returnResultLast->invokeID->parm = 0;
        ret->un.returnResultLast->invokeID->parm =
            (signed char)cpt->u.result.invoke_id.data[2];

        /* set up the PE for the param */
        if (cpt->u.result.operation.len != 0 ||
            cpt->u.result.param.len != 0)
        {
            ret->un.returnResultLast->result = (struct element_ITU__TCAP_0 *)
                calloc(1, sizeof(struct element_ITU__TCAP_0));

            if (ret->un.returnResultLast->result == NULL)
            {

                free(ret->un.returnResultLast->invokeID);
                free(ret->un.returnResultLast);
                free(ret);

                return (NULL);
            }

            /* allocate the operationCode */
            ret->un.returnResultLast->result->operationCode =
                (struct type_ITU__TCAP_Operation *)
                calloc(1, sizeof(struct type_ITU__TCAP_Operation));
            if (ret == NULL)
            {
                free(ret->un.returnResultLast->result);
                free(ret->un.returnResultLast->invokeID);
                free(ret->un.returnResultLast);
                free(ret);

                return (NULL);
            }

            /* Pay attention to local vs global code */
            if (cpt->u.result.operation.data[0] ==
                TCPPN_LOCAL_OP_TAG)
            {
                ret->un.returnResultLast->result->operationCode->offset =
                    type_ITU__TCAP_Operation_localCode;
                ret->un.returnResultLast->result->operationCode->un.localCode = 0;
                for (i = 0;
                     i < cpt->u.result.operation.data[1] && i < sizeof(ITS_LONG);
                     i++)
                {
                    ret->un.returnResultLast->result->operationCode->un.localCode <<= 8;
                    ret->un.returnResultLast->result->operationCode->un.localCode |=
                        cpt->u.result.operation.data[2+i];
                }
            }
            else if (cpt->u.result.operation.data[0] ==
                     TCPPN_GLOBAL_OP_TAG)
            {
                PE tmp;
                int err;

                ret->un.returnResultLast->result->operationCode->offset =
                    type_ITU__TCAP_Operation_globalCode;

                tmp = ssdu2pe((char *)&cpt->u.result.operation.data[2],
                              cpt->u.result.operation.data[1],
                              NULL,
                              &err);

                if (err != PS_ERR_NONE)
                {
                    free(ret->un.returnResultLast->result);
                    free(ret->un.returnResultLast->invokeID);
                    free(ret->un.returnResultLast);
                    free(ret);

                    return (NULL);
                }

                ret->un.returnResultLast->result->operationCode->un.globalCode =
                    prim2oid(tmp);
            }


            if (cpt->u.result.param.len == 0)
            {
                ret->un.returnResultLast->result->parameter = NULL;
            }
            else
            {
                int err;

                ret->un.returnResultLast->result->parameter =
                    ssdu2pe((char *)cpt->u.result.param.data,
                            cpt->u.result.param.len,
                            NULL,
                            &err);

                if (err != PS_ERR_NONE)
                {
                    free(ret->un.returnResultLast->result->operationCode);
                    free(ret->un.returnResultLast->result);
                    free(ret->un.returnResultLast->invokeID);
                    free(ret->un.returnResultLast);
                    free(ret);

                    return (NULL);
                }
            }
        }

        break;

    case TCPPT_TC_U_ERROR:
        ret->offset = type_ITU__TCAP_ComponentPDU_returnError;

        ret->un.returnError = (struct type_ITU__TCAP_ReturnError *)
            calloc(1, sizeof(struct type_ITU__TCAP_ReturnError));

        if (ret->un.returnError == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* allocate the invokeID */
        ret->un.returnError->invokeID =
            (struct type_ITU__TCAP_InvokeIdType *)
                calloc(1, sizeof(struct type_ITU__TCAP_InvokeIdType));

        if (ret == NULL)
        {
            free(ret->un.returnError);
            free(ret);

            return (NULL);
        }

        /* copy in the invoke info */
        ret->un.returnError->invokeID->parm = 0;
        ret->un.returnError->invokeID->parm =
            (signed char)cpt->u.error.invoke_id.data[2];

        /* allocate the errorCode */
        ret->un.returnError->errorCode =
            (struct type_ITU__TCAP_Error *)
                calloc(1, sizeof(struct type_ITU__TCAP_Error));
        if (ret == NULL)
        {
            free(ret->un.returnError->invokeID);
            free(ret->un.returnError);
            free(ret);

            return (NULL);
        }

        /* Pay attention to local vs global */
        /* copy in the error info */
        if (cpt->u.error.error.data[0] ==
                 TCPPN_LOCAL_ERR_TAG)
        {
            ret->un.returnError->errorCode->offset =
                type_ITU__TCAP_Error_localCode;
            for (i = 0;
                 i < cpt->u.error.error.data[1] && i < sizeof(ITS_LONG);
                 i++)
            {
                ret->un.returnError->errorCode->un.localCode <<= 8;
                ret->un.returnError->errorCode->un.localCode |=
                    cpt->u.error.error.data[2+i];
            }
        }
        else if (cpt->u.error.error.data[0] ==
                 TCPPN_GLOBAL_OP_TAG)
        {
            PE tmp;
            int err;

            ret->un.returnError->errorCode->offset =
                type_ITU__TCAP_Error_globalCode;

            tmp = ssdu2pe((char *)&cpt->u.error.error.data[2],
                          cpt->u.error.error.data[1],
                          NULL,
                          &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnError->invokeID);
                free(ret->un.returnError);
                free(ret);

                return (NULL);
            }

            ret->un.returnError->errorCode->un.globalCode = prim2oid(tmp);
        }

        /* set up the PE for the param */
        if (cpt->u.error.param.len == 0)
        {
            ret->un.returnError->parameter = NULL;
        }
        else
        {
            int err;

            ret->un.returnError->parameter =
                ssdu2pe((char *)cpt->u.error.param.data,
                        cpt->u.error.param.len,
                        NULL,
                        &err);

            if (err != PS_ERR_NONE)
            {
                free(ret->un.returnError->invokeID);
                free(ret->un.returnError);
                free(ret);

                return (NULL);
            }
        }

        break;

    case TCPPT_TC_L_REJECT:
    case TCPPT_TC_R_REJECT:
    case TCPPT_TC_U_REJECT:
        ret->offset = type_ITU__TCAP_ComponentPDU_reject;

        ret->un.reject = (struct type_ITU__TCAP_Reject *)
            calloc(1, sizeof(struct type_ITU__TCAP_Reject));
        if (ret->un.reject == NULL)
        {
            free(ret);

            return (NULL);
        }

        ret->un.reject->invokeID = (struct choice_ITU__TCAP_0 *)
            calloc(1, sizeof(struct choice_ITU__TCAP_0));
        if (ret->un.reject->invokeID == NULL)
        {
            free(ret->un.reject);
            free(ret);

            return (NULL);
        }

        /* we have an invokeID? */
        if (cpt->u.reject.invoke_id.len != 0)
        {
            ret->un.reject->invokeID->offset = choice_ITU__TCAP_0_derivable;

            /* allocate the invokeID */
            ret->un.reject->invokeID->un.derivable =
                (struct type_ITU__TCAP_InvokeIdType *)
                    calloc(1, sizeof(struct type_ITU__TCAP_InvokeIdType));
            if (ret == NULL)
            {
                free(ret->un.reject->invokeID);
                free(ret->un.reject);
                free(ret);

                return (NULL);
            }

            /* copy in the invoke info */
            ret->un.reject->invokeID->un.derivable->parm = 0;
            ret->un.reject->invokeID->un.derivable->parm =
                (signed char)cpt->u.reject.invoke_id.data[2];
        }
        else
        {
            ret->un.reject->invokeID->offset =
                choice_ITU__TCAP_0_not__derivable;
        }

        /* allocate the problem */
        ret->un.reject->problem =
            (struct choice_ITU__TCAP_1 *)
                calloc(1, sizeof(struct choice_ITU__TCAP_1));
        if (ret == NULL)
        {
            free(ret->un.reject->invokeID);
            free(ret->un.reject);
            free(ret);

            return (NULL);
        }

        /* build the problem */
        switch (cpt->u.reject.problem.data[0] & ~LOCAL_REJECT_MARKER)
        {
        default:
        case TCPPROB_GENERAL:
            ret->un.reject->problem->un.generalProblem =
                (struct type_ITU__TCAP_GeneralProblem *)
                    calloc(1, sizeof(struct type_ITU__TCAP_GeneralProblem));
            if (ret->un.reject->problem->un.generalProblem == NULL)
            {
                free(ret->un.reject->problem);
                free(ret->un.reject->invokeID);
                free(ret->un.reject);
                free(ret);

                return (NULL);
            }

            ret->un.reject->problem->offset = choice_ITU__TCAP_1_generalProblem;
            /*
             * hack to indicate source is local.  Note that this must not be
             * set if this component is to be encoded by the ASN runtime
             * (valid only for our stack).
             */
            if (cpt->u.reject.problem.data[0] & LOCAL_REJECT_MARKER)
            {
                ret->un.reject->problem->offset |= LOCAL_REJECT_MARKER;
            }

            ret->un.reject->problem->un.generalProblem->parm =
                        cpt->u.reject.problem.data[2];

            break;

        case TCPPROB_INVOKE:
            ret->un.reject->problem->un.invokeProblem =
                (struct type_ITU__TCAP_InvokeProblem *)
                    calloc(1, sizeof(struct type_ITU__TCAP_InvokeProblem));
            if (ret->un.reject->problem->un.invokeProblem == NULL)
            {
                free(ret->un.reject->problem);
                free(ret->un.reject->invokeID);
                free(ret->un.reject);
                free(ret);

                return (NULL);
            }

            ret->un.reject->problem->offset = choice_ITU__TCAP_1_invokeProblem;
            /*
             * hack to indicate source is local.  Note that this must not be
             * set if this component is to be encoded by the ASN runtime
             * (valid only for our stack).
             */
            if (cpt->u.reject.problem.data[0] & LOCAL_REJECT_MARKER)
            {
                ret->un.reject->problem->offset |= LOCAL_REJECT_MARKER;
            }
            ret->un.reject->problem->un.invokeProblem->parm =
                        cpt->u.reject.problem.data[2];

            break;

        case TCPPROB_RETURN_RES:
            ret->un.reject->problem->un.returnResultProblem =
                (struct type_ITU__TCAP_ReturnResultProblem *)
                    calloc(1, sizeof(struct type_ITU__TCAP_ReturnResultProblem));
            if (ret->un.reject->problem->un.returnResultProblem == NULL)
            {
                free(ret->un.reject->problem);
                free(ret->un.reject->invokeID);
                free(ret->un.reject);
                free(ret);

                return (NULL);
            }

            ret->un.reject->problem->offset = choice_ITU__TCAP_1_returnResultProblem;
            /*
             * hack to indicate source is local.  Note that this must not be
             * set if this component is to be encoded by the ASN runtime
             * (valid only for our stack).
             */
            if (cpt->u.reject.problem.data[0] & LOCAL_REJECT_MARKER)
            {
                ret->un.reject->problem->offset |= LOCAL_REJECT_MARKER;
            }
            ret->un.reject->problem->un.returnResultProblem->parm =
                        cpt->u.reject.problem.data[2];

            break;

        case TCPPROB_RETURN_ERR:
            ret->un.reject->problem->un.returnErrorProblem =
                (struct type_ITU__TCAP_ReturnErrorProblem *)
                    calloc(1, sizeof(struct type_ITU__TCAP_ReturnErrorProblem));
            if (ret->un.reject->problem->un.returnErrorProblem == NULL)
            {
                free(ret->un.reject->problem);
                free(ret->un.reject->invokeID);
                free(ret->un.reject);
                free(ret);

                return (NULL);
            }

            ret->un.reject->problem->offset = choice_ITU__TCAP_1_returnErrorProblem;
            /*
             * hack to indicate source is local.  Note that this must not be
             * set if this component is to be encoded by the ASN runtime
             * (valid only for our stack).
             */
            if (cpt->u.reject.problem.data[0] & LOCAL_REJECT_MARKER)
            {
                ret->un.reject->problem->offset |= LOCAL_REJECT_MARKER;
            }
            ret->un.reject->problem->un.returnErrorProblem->parm =
                        cpt->u.reject.problem.data[2];

            break;
        }

        break;

    }

    return (ret);
}

/*.implementation:extern (or static)
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
 ****************************************************************************/
SS7DLLAPI struct type_ITU__TCAP_MessageType *
TCAP_CvtDLGToMessage_CCITT(TCAP_DLG *dlg,
                           ITS_INT ltid, ITS_INT rtid, ITS_UINT rtidLen,
                           int variant)
{
    struct type_ITU__TCAP_MessageType *ret = NULL;

    /* allocate the component */
    ret = (struct type_ITU__TCAP_MessageType *)
         calloc(1, sizeof(struct type_ITU__TCAP_MessageType));
    if (ret == NULL)
    {
        return ret;
    }

    switch (dlg->ptype)
    {
    case TCPPT_TC_UNI:
        ret->offset = type_ITU__TCAP_MessageType_unidirectional;

        ret->un.unidirectional = (struct type_ITU__TCAP_Unidirectional *)
            calloc(1, sizeof(struct type_ITU__TCAP_Unidirectional));
        if (ret->un.unidirectional == NULL)
        {
            free(ret);

            return (NULL);
        }

        if (variant >= ITS_SECOND_GEN)
        {
            ret->un.unidirectional->dialoguePortion =
                BuildDialoguePortion(TCPPT_TC_UNI,
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

        break;

    case TCPPT_TC_BEGIN:
        ret->offset = type_ITU__TCAP_MessageType_begin;

        ret->un.begin = (struct type_ITU__TCAP_Begin *)
            calloc(1, sizeof(struct type_ITU__TCAP_Begin));
        if (ret->un.begin == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.begin->otid =
            (struct type_ITU__TCAP_OrigTransactionID *)
                calloc(1, sizeof(struct type_ITU__TCAP_OrigTransactionID) + 8);
        if (ret->un.begin->otid == NULL)
        {
            free(ret->un.begin);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.begin->otid->qb_data =
            ret->un.begin->otid->qb_base;
        /* link up the qbufs */
    	ret->un.begin->otid->qb_forw =
            ret->un.begin->otid;
	    ret->un.begin->otid->qb_back =
            ret->un.begin->otid;
        /* allocate a new local tid */
        ret->un.begin->otid->qb_len =
            TIDToData((ITS_OCTET *)ret->un.begin->otid->qb_data, ltid, 0);

        if (variant >= ITS_SECOND_GEN)
        {
            /* add the dialogue portion */
            ret->un.begin->dialoguePortion =
                BuildDialoguePortion(TCPPT_TC_BEGIN,
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

        break;

    case TCPPT_TC_CONTINUE:
        ret->offset = type_ITU__TCAP_MessageType_contin;

        ret->un.contin = (struct type_ITU__TCAP_Continue *)
            calloc(1, sizeof(struct type_ITU__TCAP_Continue));
        if (ret->un.contin == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.contin->otid =
            (struct type_ITU__TCAP_OrigTransactionID *)
                calloc(1, sizeof(struct type_ITU__TCAP_OrigTransactionID) + 8);
        if (ret->un.contin->otid == NULL)
        {
            free(ret->un.contin);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.contin->otid->qb_data =
            ret->un.contin->otid->qb_base;
        /* link up the qbufs */
    	ret->un.contin->otid->qb_forw =
            ret->un.contin->otid;
	    ret->un.contin->otid->qb_back =
            ret->un.contin->otid;
        ret->un.contin->otid->qb_len =
            TIDToData((ITS_OCTET *)ret->un.contin->otid->qb_data,
                      ltid, 0);


        /* build the transactionID */
        ret->un.contin->dtid =
            (struct type_ITU__TCAP_DestTransactionID *)
                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + 8);
        if (ret->un.contin->dtid == NULL)
        {
            free(ret->un.contin->otid);
            free(ret->un.contin);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.contin->dtid->qb_data =
            ret->un.contin->dtid->qb_base;
        /* link up the qbufs */
    	ret->un.contin->dtid->qb_forw =
            ret->un.contin->dtid;
	    ret->un.contin->dtid->qb_back =
            ret->un.contin->dtid;
        /* set the tid's */
        ret->un.contin->dtid->qb_len =
            TIDToData((ITS_OCTET *)ret->un.contin->dtid->qb_data,
                      rtid, rtidLen);

        if (variant >= ITS_SECOND_GEN)
        {
            ret->un.contin->dialoguePortion =
                BuildDialoguePortion(TCPPT_TC_CONTINUE,
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

        break;

    case TCPPT_TC_END:
        ret->offset = type_ITU__TCAP_MessageType_end;

        ret->un.end = (struct type_ITU__TCAP_End *)
            calloc(1, sizeof(struct type_ITU__TCAP_End));
        if (ret->un.end == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.end->dtid =
            (struct type_ITU__TCAP_DestTransactionID *)
                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + 8);
        if (ret->un.end->dtid == NULL)
        {
            free(ret->un.end);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.end->dtid->qb_data =
            ret->un.end->dtid->qb_base;
        /* link up the qbufs */
    	ret->un.end->dtid->qb_forw =
            ret->un.end->dtid;
	    ret->un.end->dtid->qb_back =
            ret->un.end->dtid;
        /* set the tid */
        ret->un.end->dtid->qb_len =
            TIDToData((ITS_OCTET *)ret->un.end->dtid->qb_data,
                      rtid, rtidLen);

        if (variant >= ITS_SECOND_GEN)
        {
            ret->un.end->dialoguePortion =
                BuildDialoguePortion(TCPPT_TC_END,
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

        break;

    case TCPPT_TC_U_ABORT:
    case TCPPT_TC_P_ABORT:
        ret->offset = type_ITU__TCAP_MessageType_abort;

        ret->un.abort = (struct type_ITU__TCAP_Abort *)
            calloc(1, sizeof(struct type_ITU__TCAP_Abort));
        if (ret->un.abort == NULL)
        {
            free(ret);

            return (NULL);
        }

        /* build the transactionID */
        ret->un.abort->dtid =
            (struct type_ITU__TCAP_DestTransactionID *)
                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + 8);
        if (ret->un.abort->dtid == NULL)
        {
            free(ret->un.abort);
            free(ret);

            return (NULL);
        }
        /* get space for the tids */
        ret->un.abort->dtid->qb_data =
            ret->un.abort->dtid->qb_base;
        /* link up the qbufs */
    	ret->un.abort->dtid->qb_forw =
            ret->un.abort->dtid;
	    ret->un.abort->dtid->qb_back =
            ret->un.abort->dtid;
        /* set the tid */
        ret->un.abort->dtid->qb_len =
            TIDToData((ITS_OCTET *)ret->un.abort->dtid->qb_data,
                      rtid, rtidLen);

        if (dlg->ptype == TCPPT_TC_P_ABORT)
        {
            /* fill in the abort cause */
            ret->un.abort->reason =
                (struct choice_ITU__TCAP_2 *)
                    calloc(1, sizeof(struct choice_ITU__TCAP_2));
            if (ret->un.abort->reason == NULL)
            {
                free(ret->un.abort->dtid);
                free(ret->un.abort);
                free(ret);

                return (NULL);
            }

            ret->un.abort->reason->offset = choice_ITU__TCAP_2_p__abort__cause;

            ret->un.abort->reason->un.p__abort__cause =
                (struct type_ITU__TCAP_P__AbortCause *)
                    calloc(1, sizeof(struct type_ITU__TCAP_P__AbortCause));
            if (ret->un.abort->reason->un.p__abort__cause == NULL)
            {
                free(ret->un.abort->reason);
                free(ret->un.abort->dtid);
                free(ret->un.abort);
                free(ret);

                return (NULL);
            }
            ret->un.abort->reason->un.p__abort__cause->parm =
                dlg->u.abort.abort_reason;
        }
        else /* U-ABORT */
        {
            /* fill in the abort cause */
            ret->un.abort->reason =
                (struct choice_ITU__TCAP_2 *)
                    calloc(1, sizeof(struct choice_ITU__TCAP_2));
            if (ret->un.abort->reason == NULL)
            {
                free(ret->un.abort->dtid);
                free(ret->un.abort);
                free(ret);

                return (NULL);
            }

            ret->un.abort->reason->offset = choice_ITU__TCAP_2_dialoguePortion;

            if (variant >= ITS_SECOND_GEN)
            {
                if (dlg->u.abort.ac_name.len != 0 ||
                    dlg->u.abort.user_info.len != 0)
                {
                    if (dlg->u.abort.abort_reason == TCPUABT_AC_NOT_SUP)
                    {
                        ret->un.abort->reason->un.dialoguePortion =
                            BuildDialoguePortion(TCPPT_TC_END,
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
                        ret->un.abort->reason->un.dialoguePortion =
                            BuildDialoguePortion(TCPPT_TC_END,
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
                        ret->un.abort->reason->un.dialoguePortion =
                            BuildDialoguePortion(TCPPT_TC_U_ABORT,
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
                    free(ret->un.abort->reason);
                    ret->un.abort->reason = NULL;
                }
            }
            else /* Assume Blue Book */
            {
                ret->un.abort->reason->un.dialoguePortion = int2prim(dlg->u.abort.abort_reason);
            }
        }

        break;
    }

    return (ret);
}

/*.implementation:extern (or static)
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
 ****************************************************************************/
SS7DLLAPI int
TCAP_CvtComponentPDUToCPT_CCITT(TCAP_CPT *cpt,
                                struct type_ITU__TCAP_ComponentPDU *comp)
{
    struct type_ITU__TCAP_InvokeIdType *cid;
    char *tmp;
    int len;
    PE param;
    ITS_BOOLEAN isLocal = ITS_FALSE;

    memset(cpt, 0, sizeof(TCAP_CPT));

    if (comp == NULL)
    {
        return (ITS_EPROTERR);
    }

    switch (comp->offset)
    {
    case type_ITU__TCAP_ComponentPDU_invoke:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_INVOKE;

        if (comp->un.invoke == NULL ||
            comp->un.invoke->invokeID == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.invoke->invokeID;

        cpt->u.invoke.invoke_id.len = 3;
        cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt->u.invoke.invoke_id.data[1] = 1;
        cpt->u.invoke.invoke_id.data[2] = (ITS_OCTET)cid->parm;

        cid = comp->un.invoke->linkedID;
        if (cid)
        {
            cpt->u.invoke.linked_id.len = 3;
            cpt->u.invoke.linked_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.invoke.linked_id.data[1] = 1;
            cpt->u.invoke.linked_id.data[2] = (ITS_OCTET)cid->parm;
        }

        /* get the op code */
        if (comp->un.invoke->operationCode)
        {
            if (comp->un.invoke->operationCode->offset ==
                type_ITU__TCAP_Operation_localCode)
            {
                ITS_LONG code = comp->un.invoke->operationCode->un.localCode;
                int opSize = sizeof(ITS_LONG);
                int i;

                if (code < 0)
                {
                    while (opSize > 1 &&
                           ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FF) == 0x0FF))
                    {
                        opSize--;
                    }
                }
                else if (code > 0)
                {
                    while (opSize > 1 &&
                           ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FFU) == 0x00))
                    {
                        opSize--;
                    }
                }
                else
                {
                    opSize = 1;
                }

                cpt->u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
                cpt->u.invoke.operation.data[1] = (ITS_OCTET)opSize;
                for (i = opSize; i > 0; i--)
                {
                    cpt->u.invoke.operation.data[2 + opSize - i] =
                        (ITS_OCTET)(
                            (code >> ((i - 1) * ITS_BITS_PER_BYTE)) & 0x0FF);
                }

                cpt->u.invoke.operation.len = (ITS_USHORT)(2 + opSize);
            }
            else if (comp->un.invoke->operationCode->offset ==
                     type_ITU__TCAP_Operation_globalCode)
            {
                PE global;

                cpt->u.invoke.operation.data[0] = TCPPN_GLOBAL_OP_TAG;

                global = oid2prim(comp->un.invoke->operationCode->un.globalCode);

                if (pe2ssdu(global, &tmp, &len) != OK)
                {
                    return (ITS_EPROTERR);
                }

                cpt->u.invoke.operation.data[1] = (ITS_OCTET)len;
                memcpy(&cpt->u.invoke.operation.data[2], tmp, len);

                if (len)
                {
                    free(tmp);
                }

                pe_free(global);
            }
        }

        /* get the parameter */
        param = comp->un.invoke->parameter;
        len = 0;
        if (param)
        {
            if (pe2ssdu(param, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }
        }
        cpt->u.invoke.param.len = (ITS_USHORT)len;
        if (len)
        {
            memcpy(cpt->u.invoke.param.data, tmp, len);

            free(tmp);
        }

        break;

    case type_ITU__TCAP_ComponentPDU_returnResultLast:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_RESULT_L;
        goto skipit;

    case type_ITU__TCAP_ComponentPDU_returnResultNotLast:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_RESULT_NL;

skipit:
        if (comp->un.returnResultLast == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.returnResultLast->invokeID;

        cpt->u.result.invoke_id.len = 3;
        cpt->u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt->u.result.invoke_id.data[1] = 1;
        cpt->u.result.invoke_id.data[2] = (ITS_OCTET)cid->parm;

        /* get the parameter */
        if (comp->un.returnResultLast->result)
        {
            /* get the op code */
            if (comp->un.returnResultLast->result->operationCode)
            {
                if (comp->un.returnResultLast->result->operationCode->offset ==
                     type_ITU__TCAP_Operation_localCode)
                {
                    ITS_LONG code = comp->un.returnResultLast->result->operationCode->un.localCode;
                    int opSize = sizeof(ITS_LONG);
                    int i;

                    if (code < 0)
                    {
                        while (opSize > 1 &&
                               ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FF) == 0x0FF))
                        {
                            opSize--;
                        }
                    }
                    else if (code > 0)
                    {
                        while (opSize > 1 &&
                               ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FFU) == 0x00))
                        {
                            opSize--;
                        }
                    }
                    else
                    {
                        opSize = 1;
                    }

                    cpt->u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
                    cpt->u.result.operation.data[1] = (ITS_OCTET)opSize;
                    for (i = opSize; i > 0; i--)
                    {
                        cpt->u.result.operation.data[2 + opSize - i] =
                            (ITS_OCTET)(
                                (code >> ((i - 1) * ITS_BITS_PER_BYTE)) & 0x0FF);
                    }

                    cpt->u.result.operation.len = (ITS_USHORT)(2 + opSize);
                }
                else if (comp->un.returnResultLast->result->operationCode->offset ==
                         type_ITU__TCAP_Operation_globalCode)
                {
                    PE global;

                    cpt->u.result.operation.data[0] = TCPPN_GLOBAL_OP_TAG;

                    global = oid2prim(comp->un.returnResultLast->result->operationCode->un.globalCode);

                    if (pe2ssdu(global, &tmp, &len) != OK)
                    {
                        return (ITS_EPROTERR);
                    }

                    cpt->u.result.operation.data[1] = (ITS_OCTET)len;
                    memcpy(&cpt->u.result.operation.data[2], tmp, len);

                    if (len)
                    {
                        free(tmp);
                    }
                }
            }

            param = comp->un.returnResultLast->result->parameter;
            len = 0;
            if (param)
            {
                if (pe2ssdu(param, &tmp, &len) != OK)
                {
                    return (ITS_EPROTERR);
                }
            }
            cpt->u.result.param.len = (ITS_USHORT)len;
            if (len)
            {
                memcpy(cpt->u.result.param.data, tmp, len);

                free(tmp);
            }
        }

        break;

    case type_ITU__TCAP_ComponentPDU_returnError:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_U_ERROR;

        if (comp->un.returnError == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        cid = comp->un.returnError->invokeID;

        cpt->u.result.invoke_id.len = 3;
        cpt->u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt->u.result.invoke_id.data[1] = 1;
        cpt->u.result.invoke_id.data[2] = (ITS_OCTET)cid->parm;

        /* get the problem code */
        /* Pay attention to local vs. global code */
        if (comp->un.returnError->errorCode)
        {
            if (comp->un.returnError->errorCode->offset ==
                type_ITU__TCAP_Error_localCode)
            {
                ITS_LONG code = comp->un.returnError->errorCode->un.localCode;
                int opSize = sizeof(ITS_LONG);
                int i;

                if (code < 0)
                {
                    while (opSize > 1 &&
                           ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FF) == 0x0FF))
                    {
                        opSize--;
                    }
                }
                else if (code > 0)
                {
                    while (opSize > 1 &&
                           ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FFU) == 0x00))
                    {
                        opSize--;
                    }
                }
                else
                {
                    opSize = 1;
                }

                cpt->u.error.error.data[0] = TCPPN_LOCAL_ERR_TAG;
                cpt->u.error.error.data[1] = (ITS_OCTET)opSize;
                for (i = opSize; i > 0; i--)
                {
                    cpt->u.error.error.data[2 + opSize - i] =
                        (ITS_OCTET)(
                            (code >> ((i - 1) * ITS_BITS_PER_BYTE)) & 0x0FF);
                }

                cpt->u.error.error.len = (ITS_USHORT)(2 + opSize);
            }
            else if (comp->un.returnError->errorCode->offset ==
                     type_ITU__TCAP_Error_globalCode)
            {
                PE global;

                cpt->u.error.error.data[0] = TCPPN_GLOBAL_OP_TAG;

                global = oid2prim(comp->un.returnError->errorCode->un.globalCode);

                if (pe2ssdu(global, &tmp, &len) != OK)
                {
                    return (ITS_EPROTERR);
                }

                cpt->u.result.operation.data[1] = (ITS_OCTET)len;
                memcpy(&cpt->u.result.operation.data[2], tmp, len);

                if (len)
                {
                    free(tmp);
                }
            }
        }

        /* get the parameter */
        param = comp->un.returnError->parameter;
        len = 0;
        if (param)
        {
            if (pe2ssdu(param, &tmp, &len) != OK)
            {
                return (ITS_EPROTERR);
            }
        }
        cpt->u.error.param.len = (ITS_USHORT)len;
        if (len)
        {
            memcpy(cpt->u.error.param.data, tmp, len);

            free(tmp);
        }

        break;

    case type_ITU__TCAP_ComponentPDU_reject:
        /* set the ptype */
        cpt->ptype = TCPPT_TC_R_REJECT;

        if (comp->un.reject == NULL)
        {
            return (ITS_EPROTERR);
        }

        /* get the invoke ids */
        if (comp->un.reject->invokeID->offset ==
            choice_ITU__TCAP_0_derivable)
        {
            cid = comp->un.reject->invokeID->un.derivable;

            cpt->u.reject.invoke_id.len = 3;
            cpt->u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.reject.invoke_id.data[1] = 1;
            cpt->u.reject.invoke_id.data[2] = (ITS_OCTET)cid->parm;
        }

        /* get the problem */
        if (comp->un.reject->problem != NULL)
        {
            cpt->u.reject.problem.len = 3;

            cpt->u.reject.problem.data[1] = 1;

            isLocal = comp->un.reject->problem->offset & LOCAL_REJECT_MARKER;
            comp->un.reject->problem->offset &= ~LOCAL_REJECT_MARKER;

            switch (comp->un.reject->problem->offset)
            {
            default:
            case choice_ITU__TCAP_1_generalProblem:
                cpt->u.reject.problem.data[0] = TCPPROB_GENERAL;
                cpt->u.reject.problem.data[2] =
                    (ITS_OCTET)comp->un.reject->
                        problem->un.generalProblem->parm;
                break;

            case choice_ITU__TCAP_1_invokeProblem:
                cpt->u.reject.problem.data[0] = TCPPROB_INVOKE;
                cpt->u.reject.problem.data[2] =
                    (ITS_OCTET)comp->un.reject->
                        problem->un.invokeProblem->parm;

                if (cpt->u.reject.problem.data[2] !=
                    TCPPROB_SPEC_INV_UNREC_LINKED_ID)
                {
                    cpt->ptype = TCPPT_TC_U_REJECT;
                }
                break;

            case choice_ITU__TCAP_1_returnResultProblem:
                cpt->u.reject.problem.data[0] = TCPPROB_RETURN_RES;
                cpt->u.reject.problem.data[2] =
                    (ITS_OCTET)comp->un.reject->
                        problem->un.returnResultProblem->parm;

                if (cpt->u.reject.problem.data[2] ==
                    TCPPROB_SPEC_RES_MISTYPED_PARAM)
                {
                    cpt->ptype = TCPPT_TC_U_REJECT;
                }
                break;

            case choice_ITU__TCAP_1_returnErrorProblem:
                cpt->u.reject.problem.data[0] = TCPPROB_RETURN_ERR;
                cpt->u.reject.problem.data[2] =
                    (ITS_OCTET)comp->un.reject->
                        problem->un.returnErrorProblem->parm;

                if ((cpt->u.reject.problem.data[2] !=
                    TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR) &&
                    (cpt->u.reject.problem.data[2] !=
                    TCPPROB_SPEC_ERR_UNREC_INVOKE_ID))
                {
                    cpt->ptype = TCPPT_TC_U_REJECT;
                }
                break;
            }
        }

        break;

    default:
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern (or static)
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
 ****************************************************************************/
SS7DLLAPI int
TCAP_CvtMessageToDLG_CCITT(TCAP_DLG *dlg,
                           struct type_ITU__TCAP_MessageType *dialog,
                           int variant)
{
    ITS_BOOLEAN fromUser, accept, causeACName, hasPV;

    memset(dlg, 0, sizeof(TCAP_DLG));

    if (dialog == NULL)
    {
        return (ITS_EPROTERR);
    }

    switch (dialog->offset)
    {
    case type_ITU__TCAP_MessageType_unidirectional:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_UNI;

        /* check for components */
        if (dialog->un.unidirectional->components != NULL)
        {
            dlg->u.uni.cpt_present = 1;
        }

        if (variant >= ITS_SECOND_GEN)
        {
            /* get the dialogue portion, if any */
            if (!ParseDialoguePortion(TCPPT_TC_UNI,
                                      dialog->un.unidirectional->
                                          dialoguePortion,
                                      dlg->u.uni.ac_name.data,
                                      &dlg->u.uni.ac_name.len,
                                      dlg->u.uni.user_info.data,
                                      &dlg->u.uni.user_info.len,
                                      &fromUser, &accept,
                                      &causeACName, &hasPV))
            {
                return (ITS_EPROTERR);
            }

            if (hasPV)
            {
                dlg->u.uni.qos.indicator |= QOSI_PROT_VER;
            }
        }

        break;

    case type_ITU__TCAP_MessageType_begin:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_BEGIN;

        /* check for components */
        if (dialog->un.begin->components != NULL)
        {
            dlg->u.begin.cpt_present = 1;
        }

        /* get the dialogue portion, if any */
        if (variant >= ITS_SECOND_GEN)
        {
            if (!ParseDialoguePortion(TCPPT_TC_BEGIN,
                                      dialog->un.begin->dialoguePortion,
                                      dlg->u.begin.ac_name.data,
                                      &dlg->u.begin.ac_name.len,
                                      dlg->u.begin.user_info.data,
                                      &dlg->u.begin.user_info.len,
                                      &fromUser, &accept,
                                      &causeACName, &hasPV))
            {
                return (ITS_EPROTERR);
            }

            if (hasPV)
            {
                dlg->u.begin.qos.indicator |= QOSI_PROT_VER;
            }
        }

        break;

    case type_ITU__TCAP_MessageType_end:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_END;

        /* check for components */
        if (dialog->un.end->components != NULL)
        {
            dlg->u.end.cpt_present = 1;
        }

        if (variant >= ITS_SECOND_GEN)
        {
            /* get the dialogue portion, if any */
            if (!ParseDialoguePortion(TCPPT_TC_END,
                                      dialog->un.end->dialoguePortion,
                                      dlg->u.end.ac_name.data,
                                      &dlg->u.end.ac_name.len,
                                      dlg->u.end.user_info.data,
                                      &dlg->u.end.user_info.len,
                                      &fromUser, &accept,
                                      &causeACName, &hasPV))
            {
                return (ITS_EPROTERR);
            }

            if (hasPV)
            {
                dlg->u.end.qos.indicator |= QOSI_PROT_VER;
            }
        }

        break;

    case type_ITU__TCAP_MessageType_contin:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_CONTINUE;

        /* check for components */
        if (dialog->un.contin->components != NULL)
        {
            dlg->u.cont.cpt_present = 1;
        }

        if (variant >= ITS_SECOND_GEN)
        {
            /* get the dialogue portion, if any */
            if (!ParseDialoguePortion(TCPPT_TC_CONTINUE,
                                      dialog->un.contin->dialoguePortion,
                                      dlg->u.cont.ac_name.data,
                                      &dlg->u.cont.ac_name.len,
                                      dlg->u.cont.user_info.data,
                                      &dlg->u.cont.user_info.len,
                                      &fromUser, &accept,
                                      &causeACName, &hasPV))
            {
                return (ITS_EPROTERR);
            }

            if (hasPV)
            {
                dlg->u.cont.qos.indicator |= QOSI_PROT_VER;
            }
        }

        break;

    case type_ITU__TCAP_MessageType_abort:
        /* set the ptype */
        dlg->ptype = TCPPT_TC_P_ABORT;

        if (dialog->un.abort->reason != NULL)
        {
            if (dialog->un.abort->reason->offset ==
                choice_ITU__TCAP_2_p__abort__cause)
            {
                dlg->u.abort.abort_reason =
                    (ITS_OCTET)dialog->un.abort->
                                reason->un.p__abort__cause->parm;
            }
            else
            {
                dlg->ptype = TCPPT_TC_U_ABORT;

                if (variant >= ITS_SECOND_GEN)
                {
                    /* get the dialogue portion, if any */
                    if (ParseDialoguePortion(TCPPT_TC_U_ABORT,
                                              dialog->un.abort->reason->
                                                  un.dialoguePortion,
                                              dlg->u.abort.ac_name.data,
                                              &dlg->u.abort.ac_name.len,
                                              dlg->u.abort.user_info.data,
                                              &dlg->u.abort.user_info.len,
                                              &fromUser, &accept,
                                              &causeACName, &hasPV))
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
                    else if (ParseDialoguePortion(TCPPT_TC_END,
                                                  dialog->un.abort->reason->
                                                      un.dialoguePortion,
                                                  dlg->u.abort.ac_name.data,
                                                  &dlg->u.abort.ac_name.len,
                                                  dlg->u.abort.user_info.data,
                                                  &dlg->u.abort.user_info.len,
                                                  &fromUser, &accept,
                                                  &causeACName, &hasPV))
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
                else /* Assume Blue Book */
                {
                    dlg->u.abort.abort_reason =
                        (ITS_USHORT)
                            prim2num(dialog->un.abort->reason->un.dialoguePortion);
                }
            }
        }
        else
        {
            dlg->ptype = TCPPT_TC_U_ABORT;
        }


        break;

    default:
        break;
    }

    return (ITS_SUCCESS);
}
