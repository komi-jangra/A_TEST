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
 *  ID: $Id: test.c,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:10  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:10  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:01:52  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:23  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/09/30 00:24:03  mmiers
 * LOG:
 * LOG:
 * LOG: Testing
 * LOG:
 *
 ****************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <its.h>

#include <ansi/mtp2.h>
#include <ansi/mtp3.h>

int
main(int argc, char **argv)
{
    ITS_EVENT ev;
    char buf[512];
    char *ptr;
    int count;

    while (gets(buf) != NULL)
    {
        MTP2_HEADER *mtp2;
        MTP3_HEADER *mtp3;
        int i;

        if (buf[0] == '>')
        {
            continue;
        }

        for (count = 0, ptr = buf; ptr < buf + strlen(buf); ptr += 3, count++)
        {
            int val;

            sscanf(ptr, "%02x", &val);
            ev.data[count] = val;
        }

        ev.len = count;

#if 0
        mtp2 = (MTP2_HEADER *)ev.data;
        mtp3 = (MTP3_HEADER *)(ev.data + sizeof(MTP2_HEADER) - 1);
        printf("BSN: %02x\n", MTP2_GET_BSN(*mtp2));
        printf("BIB: %02x\n", MTP2_GET_BIB(*mtp2));
        printf("FSN: %02x\n", MTP2_GET_FSN(*mtp2));
        printf("FIB: %02x\n", MTP2_GET_FIB(*mtp2));
        printf("LI : %02x\n", MTP2_GET_LI(*mtp2));
        printf("SIO: %02x\n", MTP2_GET_SIO(*mtp2));
        printf("DPC: %06x\n", MTP3_RL_GET_DPC_VALUE(mtp3->label));
        printf("OPC: %06x\n", MTP3_RL_GET_OPC_VALUE(mtp3->label));
        printf("SLS: %02x\n", MTP3_RL_GET_SLS(mtp3->label));

        printf("DATA: ");
        for (i = sizeof(MTP2_HEADER) + sizeof(MTP3_HEADER) - 1;
             i < ev.len;
             i++)
        {
            printf("%02x ", ev.data[i]);
        }
        printf("\n");
#else
        mtp3 = (MTP3_HEADER *)ev.data;
        mtp2 = NULL;

        printf("SIO: %02x\n", mtp3->sio);
        printf("DPC: %06x\n", MTP3_RL_GET_DPC_VALUE(mtp3->label));
        printf("OPC: %06x\n", MTP3_RL_GET_OPC_VALUE(mtp3->label));
        printf("SLS: %02x\n", MTP3_RL_GET_SLS(mtp3->label));

        printf("DATA: ");
        for (i = sizeof(MTP3_HEADER); i < ev.len; i++)
        {
            printf("%02x ", ev.data[i]);
        }
        printf("\n");
#endif
    }

    return (0);
}
