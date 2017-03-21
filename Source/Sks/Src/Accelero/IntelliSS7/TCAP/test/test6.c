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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:58  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:32  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/25 19:58:44  mmiers
 * LOG: Update test.
 * LOG:
 * LOG: Revision 6.1  2002/06/24 18:50:20  mmiers
 * LOG: Test ANSI encode/decode.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:53  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2001/04/03 17:42:17  mmiers
 * LOG: A test for Ericsson.  Their UserInfo is wrong.
 * LOG:
 *
 ****************************************************************************/

#define ANSI   1
#define ITS_IMPLEMENTATION
#define INCLUDE_CODEC

#include <its.h>
#include <its_app.h>
#include <its_dsm.h>

#include <ansi/tcap.h>

static ITS_OCTET msg[] =
{
#if 0
    0x09, 0x00, 0x03, 0x08, 0x0d, 0x05, 0xc3, 0xfe, 0x01, 0x01, 0x01, 0x05,
    0xc3, 0xfe, 0x02, 0x02, 0x02, 0x25, 0xe2, 0x23, 0xc7, 0x04, 0xd2, 0x04,
    0x00, 0x00, 0xf9, 0x03, 0xda, 0x01, 0x01, 0xe8, 0x16, 0xe9, 0x14, 0xcf,
    0x01, 0x05, 0xd0, 0x02, 0x01, 0x01, 0xf2, 0x0b, 0x84, 0x09, 0x01, 0x00,
    0x11, 0x0a, 0x08, 0x50, 0x55, 0x21, 0x21
#else
#if 0
    0x09, 0x00, 0x03, 0x08, 0x0d, 0x05, 0xc3, 0xfe, 0x01, 0x01, 0x01, 0x05,
    0xc3, 0xfe, 0x02, 0x02, 0x02, 0x2b, 0xe2, 0x29, 0xc7, 0x04, 0xd2, 0x04,
    0x00, 0x00, 0xf9, 0x09, 0xdc, 0x07, 0x04, 0x00, 0x00, 0x01, 0x00, 0x03,
    0x02, 0xe8, 0x16, 0xe9, 0x14, 0xcf, 0x01, 0x05, 0xd0, 0x02, 0x01, 0x01,
    0xf2, 0x0b, 0x84, 0x09, 0x01, 0x00, 0x11, 0x00, 0x00, 0x50, 0x55, 0x21,
    0x21
#else
    0x09, 0x00, 0x03, 0x08, 0x0d, 0x05, 0xc3, 0xfe, 0x01, 0x01, 0x01, 0x05,
    0xc3, 0xfe, 0x02, 0x02, 0x02, 0x2e, 0xe2, 0x2c, 0xc7, 0x04, 0xd2, 0x04,
    0x00, 0x00, 0xf9, 0x1b, 0xfd, 0x19, 0x28, 0x17, 0x06, 0x07, 0x04, 0x00,
    0x00, 0x01, 0x01, 0x01, 0x01, 0xa0, 0x0c, 0xa0, 0x0a, 0x80, 0x03, 0x12,
    0x34, 0x56, 0x81, 0x03, 0x78, 0x90, 0x55, 0xe8, 0x07, 0xe9, 0x05, 0xcf,
    0x03, 0x00, 0x01, 0x00
#endif
#endif
};

int
main(int argc, char **argv)
{
    ITS_SCCP_IE ies[8], *ud = NULL;
    int ieCount = 0, ret, i;
    struct type_ANSI__TCAP_PackageType *tcap;
    ITS_OCTET mType;
    TCAP_DLG dlg;
    int err;
    PE pe;

    APPL_SetName("test6");

    ITS_AddFeature(itsDSM_StubImplClass);

    ITS_GlobalStart(0);

    /* parse SCCP */
    ret = SCCP_DecodeMTP3(msg, sizeof(msg), &mType,
                          ies, &ieCount, &SCCP_UDT_Desc);

    /* find UD */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DATA)
        {
            ud = &ies[i];

            break;
        }
    }

    if (!ud)
    {
        ITS_GlobalStop();

        return (0);
    }

    /* parse TCAP */
    pe = ssdu2pe((char *)ud->param_data.userData.data,
                 ud->param_length, NULL, &err);
    if (err != PS_ERR_NONE)
    {
        return (ITS_EPROTERR);
    }
    if (decode_ANSI__TCAP_PackageType(pe, 1, NULL, NULL, (char **)&tcap) == OK)
    {
        printf("decode successful\n");
    }

    if (!tcap)
    {
        ITS_GlobalStop();

        return (0);
    }

    /* now parse parts */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    if (TCAP_CvtPackageToDLG_ANSI(&dlg, tcap) != ITS_SUCCESS)
    {
        ITS_GlobalStop();

        return (0);
    }

    tcap = TCAP_CvtDLGToPackage_ANSI(&dlg, 1, 2);
    if (tcap == NULL)
    {
        ITS_GlobalStop();

        return (0);
    }

    ITS_GlobalStop();

    return (0);
}
