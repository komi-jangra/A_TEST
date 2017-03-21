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
 *  ID: $Id: ptest.cpp,v 1.1.1.1 2007-10-08 11:11:30 bsccs2 Exp $
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
 * LOG: Revision 1.3  2005/03/21 13:50:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.2.2.1  2004/09/21 14:18:05  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 1.2  2003/11/13 22:19:40  mmiers
 * LOG: Testing
 * LOG:
 * LOG: Revision 1.1  2003/11/13 16:39:16  mmiers
 * LOG: Add lib test
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <its.h>
#include <its_pprint.h>

#ident "$Id: ptest.cpp,v 1.1.1.1 2007-10-08 11:11:30 bsccs2 Exp $"

/*
 * shorthand
 */
#define CHECK_RETURN(r, cnt)    \
    if ((r) < 0)                \
    {                           \
        return (cnt);           \
    }                           \
    else                        \
    {                           \
        (cnt) += (r);           \
    }

extern "C"
int
ParamPrint(RINGBUF_Manager *rb, ITS_UINT *bCount,
           ITS_OCTET cType,
           ITS_OCTET opFamily, ITS_OCTET opCode,
           ITS_OCTET *pdu, ITS_USHORT clen)
{
    int tmp, ret = 0;

    tmp = PPrint(rb, " --- Component type %x family %02x code %02x ---\n",
                 cType, opFamily, opCode);
    do
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "SHLIB: Param Data = %d\n",
                     *bCount, *pdu,
                     *pdu, *pdu);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        clen--;
        pdu++;
    }
    while (clen > 0);

    return (ret);
}

