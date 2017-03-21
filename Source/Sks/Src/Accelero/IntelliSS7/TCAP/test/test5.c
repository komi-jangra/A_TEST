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

#define CCITT   1
#define ITS_IMPLEMENTATION
#define INCLUDE_CODEC

#include <its.h>
#include <itu/tcap.h>

static ITS_OCTET msg[] =
{
    0x09, 0x01, 0x03, 0x07, 0x0b, 0x04, 0x43, 0x0d, 0x27, 0x07, 0x04, 0x43, 0xac,
    0x17, 0xfc, 0x6a, 0x62, 0x68, 0x48, 0x03, 0xc2, 0x00, 0xf0, 0x6b, 0x35,
    0x28, 0x33, 0x06, 0x07, 0x00, 0x11, 0x86, 0x05, 0x01, 0x01, 0x01, 0xa0, 0x28,
    0x60, 0x26, 0x80, 0x02, 0x07, 0x80, 0xa1, 0x0e, 0x06, 0x0c, 0x2a, 0x86,
    0x3a, 0x00, 0x89, 0x61, 0x33, 0x01, 0x00, 0x01, 0x00, 0x01, 0xbe, 0x10, 0x28,
    0x0e, 0xfe, 0x0c, 0x30, 0x0a, 0x80, 0x01, 0x05, 0x81, 0x01, 0x08, 0x82,
    0x02, 0x04, 0xf1, 0x6c, 0x80, 0xa1, 0x26, 0x02, 0x01, 0x01, 0x02, 0x01, 0x00,
    0x30, 0x1e, 0x80, 0x01, 0x01, 0x82, 0x08, 0x83, 0x10, 0x60, 0x29, 0x75,
    0x91, 0x07, 0x00, 0x83, 0x08, 0x04, 0x11, 0x94, 0x98, 0x98, 0x24, 0x79, 0x60,
    0x85, 0x01, 0x0a, 0x9a, 0x02, 0x29, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04
};

extern struct type_ITU__TCAP_MessageType *
CCITT_DecodeTCAPData(ITS_OCTET *data, ITS_USHORT len);

int
main(int argc, char **argv)
{
    ITS_SCCP_IE ies[8], *ud = NULL;
    int ieCount = 0, ret, i;
    struct type_ITU__TCAP_MessageType *tcap;
    ITS_OCTET mType;
    TCAP_DLG dlg;

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
    tcap = CCITT_DecodeTCAPData(ud->param_data.userData.data,
                                ud->param_length);

    if (!tcap)
    {
        ITS_GlobalStop();

        return (0);
    }

    /* now parse parts */
    memset(&dlg, 0, sizeof(TCAP_DLG));
    if (TCAP_CvtMessageToDLG_CCITT(&dlg, tcap) != ITS_SUCCESS)
    {
        ITS_GlobalStop();

        return (0);
    }

    ITS_GlobalStop();

    return (0);
}
