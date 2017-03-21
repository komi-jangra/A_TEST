/*********************************-*-CPP-*-**********************************
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 * LOG:
 *
 * ID: $Id: bssapif_transport.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_transport.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $"


#include <bssapif_transport.h>

extern "C" ITS_INT
TCPReadEvent(ITS_HANDLE h,
             ITS_EVENT *ev)
{
    ITS_INT ret = ITS_SUCCESS;
    static ITS_CHAR buf[DATA_MAX_SIZE];

    ret = read(SOCKTRAN_SOURCE((SOCKTRAN_Manager *)h)->socket,
               buf, DATA_MAX_SIZE);

    if (ret > 0)
    {
        ev->data = (ITS_OCTET*)malloc(sizeof(char) * ret);
        ev->len = ret;
        memcpy ((char*)ev->data, buf, ret);
        return (ITS_SUCCESS);
    }
    else
    {
        ret = ITS_EBADTRANSPORT;
    }

    return ret;
}

ITS_INT
TCPWriteEvent(ITS_HANDLE h,
              ITS_EVENT *ev)
{
    ITS_INT ret = ITS_SUCCESS;

    if (ev->len)
    {
        ret = SOCK_Write(SOCKTRAN_SOURCE((SOCKTRAN_Manager *)h),
                         (char *)ev->data, ev->len);

        if (ret ==  ev->len)
        {
            return (ITS_SUCCESS);
        }
    }

    return ret;
}

SOCKTRAN_ClassExtRec MyBasicReadWrite =
{
    {
        ITS_EXT_VERSION
    },
    {
        TCPReadEvent,
        TCPWriteEvent
    }
};

