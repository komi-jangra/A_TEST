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
 *                  
 * CONTRACT: INTERNAL
 *      
 * ID: $Id: mtp2.c,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:50:16  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1.6.1  2004/12/16 01:57:33  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.10.1  2004/09/21 06:53:06  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 22:11:31  mmiers
 * LOG: Tandem port
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/03 15:12:58  mmiers
 * LOG: Changes for PRC family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:10  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/04/24 23:13:38  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.4  2001/03/28 23:26:28  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.3  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:31  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:01:51  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:22  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/10/06 17:14:47  mmiers
 * LOG:
 * LOG:
 * LOG: Build fix for mtp2.
 * LOG:
 * LOG: Revision 1.3  1999/08/16 20:57:52  mmiers
 * LOG:
 * LOG:
 * LOG: More tweaks.
 * LOG:
 * LOG: Revision 1.2  1999/08/16 20:48:02  mmiers
 * LOG:
 * LOG:
 * LOG: Find and fix a few infrastructure bugs.
 * LOG:
 * LOG: Revision 1.1  1999/08/12 19:59:51  mmiers
 * LOG:
 * LOG:
 * LOG: New project for encode/decode of MTP2 messages.
 * LOG:
 *                 
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#ident "$Id: mtp2.c,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $"

#if defined(CCITT)
#include <itu/mtp2.h>
#elif defined(ANSI)
#include <ansi/mtp2.h>
#elif defined(PRC)
#include <china/mtp2.h>
#elif defined(TTC)
#include <japan/mtp2.h>
#else
#error "Protocol family not defined"
#endif

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Encode an ITS_EVENT with an MTP2 message
 *
 *  Input Parameters:
 *      hdr - the MTP2 header
 *      sif - the SIF
 *      len - byte count of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ev - an ITS_EVENT containing the MTP2 message
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 *      MTP2_Decode
 ************************************************************************/
SS7DLLAPI int
MTP2_Encode(ITS_EVENT *ev, MTP2_HEADER* hdr,
            ITS_OCTET* sif, ITS_USHORT len)
{
    if (len > MTP2_MAX_MSG_SIZE)
    {
        return (ITS_EOVERFLOW);
    }

    if (len == 0)
    {
        MTP2_SET_LI(*hdr, 0);

        ev->len = sizeof(MTP2_HEADER) - sizeof(ITS_OCTET); /* no SIO */
        ev->data = (ITS_OCTET *)ITS_Malloc(ev->len);
        if (ev->data == NULL)
        {
            return (ITS_ENOMEM);
        }

        memcpy(ev->data, hdr, ev->len);
    }
    else if (len == 1 || len == 2)
    {
        MTP2_SET_LI(*hdr, len);

        ev->len = (ITS_USHORT)(sizeof(MTP2_HEADER) - sizeof(ITS_OCTET) + len);
        ev->data = (ITS_OCTET *)ITS_Malloc(ev->len);
        if (ev->data == NULL)
        {
            return (ITS_ENOMEM);
        }

        memcpy(ev->data, hdr, sizeof(MTP2_HEADER) - sizeof(ITS_OCTET));
        memcpy(&ev->data[sizeof(MTP2_HEADER) - sizeof(ITS_OCTET)],
               sif, len);
    }
    else
    {
        MTP2_SET_MSU_LEN(*hdr, len);

        ev->len = (ITS_USHORT)(sizeof(MTP2_HEADER) - sizeof(ITS_OCTET) + len);
        ev->data = (ITS_OCTET *)ITS_Malloc(ev->len);
        if (ev->data == NULL)
        {
            return (ITS_ENOMEM);
        }

        /* NULL out the trailer bytes */
        memset(ev->data, 0, sizeof(MTP2_HEADER) + len + 7);
        memcpy(ev->data, hdr, sizeof(MTP2_HEADER) - sizeof(ITS_OCTET));
        memcpy(&ev->data[sizeof(MTP2_HEADER) - sizeof(ITS_OCTET)],
               sif, len);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Encode an ITS_EVENT with an MTP2 message
 *
 *  Input Parameters:
 *      hdr - the MTP2 header
 *      data - the SIF, if any
 *      len - byte count of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 *      MTP2_Decode
 ************************************************************************/
SS7DLLAPI int
MTP2_Decode(ITS_EVENT *ev, MTP2_HEADER* hdr,
            ITS_OCTET* sif, ITS_USHORT* len)
{
    if (ev->len < sizeof(MTP2_HEADER) - sizeof(ITS_OCTET))
    {
        return (ITS_EOVERFLOW);
    }

    memcpy(hdr, ev->data, sizeof(MTP2_HEADER) - sizeof(ITS_OCTET));

    if (MTP2_GET_LI(*hdr) == 0)
    {
        MTP2_SET_SIO(*hdr, 0);
    }
    else if (MTP2_GET_LI(*hdr) == 1 || MTP2_GET_LI(*hdr) == 2)
    {
        MTP2_SET_SIO(*hdr, 0);

        *len = (ITS_USHORT)MTP2_GET_LI(*hdr);

        memcpy(sif,
               &ev->data[sizeof(MTP2_HEADER) - sizeof(ITS_OCTET)],
               MTP2_GET_LI(*hdr));
    }
    else
    {
        MTP2_SET_SIO(*hdr, ev->data[sizeof(MTP2_HEADER) - sizeof(ITS_OCTET)]);

        *len = (ITS_USHORT)MTP2_GET_MSU_LEN(*hdr);

        memcpy(sif,
               &ev->data[sizeof(MTP2_HEADER) - sizeof(ITS_OCTET)],
               *len);
    }

    return (ITS_SUCCESS);
}

/*
 * header
 */
#define MTP2_PHDR   "-------------- MTP2 ----------------\n"
#define CHECK_RETURN(r, cnt)    \
    if ((r) < 0)                \
    {                           \
        return (cnt);           \
    }                           \
    else                        \
    {                           \
        (cnt) += (r);           \
    }

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Print an MTP2 header
 *
 *  Input Parameters:
 *      hdr - the MTP2 header
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The number of characters allowed in the ubuf (at max),
 *      the number put in ubuf (no overflow), or -1 (not enough
 *      room to even start).
 *
 *  Notes:
 *      For example:
 * ----------MTP 2----------
 *  1. a3     1|0100011 BIB | Backward Sequence Number = 35
 *  2. a9     1|0101001 FIB | Forward  Sequence Number = 41
 *  3. 3f     00|111111 spare | Length Indicator = 63 - MSU
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP2_PPrint(RINGBUF_Manager *rb, ITS_UINT *bCount, MTP2_HEADER *hdr)
{
    int tmp, ret, type = 0;

    /* header */
    ret = PPrint(rb, MTP2_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* BIB/BSN */
    tmp = PPrint(rb, " %3d.  %02x   %1b|%07b  "
                     "BIB | Backward Sequence Number = %d\n",
                 *bCount, hdr->bsn,
                 MTP2_GET_BIB(*hdr) ? 1 : 0,
                 MTP2_GET_BSN(*hdr), MTP2_GET_BSN(*hdr));
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* FIB/FSN */
    tmp = PPrint(rb, " %3d.  %02x   %1b|%07b  "
                     "FIB | Forward Sequence Number = %d\n",
                 *bCount, hdr->fsn,
                 MTP2_GET_FIB(*hdr) ? 1 : 0,
                 MTP2_GET_FSN(*hdr), MTP2_GET_FSN(*hdr));
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* LI */
    type = MTP2_MSG_TYPE(*hdr);
    tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  "
                     "spare | Length Indicator = %d (%s)\n",
                 *bCount, hdr->len,
                 MTP2_GET_SPARE(*hdr),
                 MTP2_GET_LI(*hdr), MTP2_GET_LI(*hdr),
                 (type == MTP2_MSG_FISU
                    ? "FISU"
                    : (type == MTP2_MSG_LSSU
                            ? "LSSU"
                            : "MSU")));
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    return (ret);
}

