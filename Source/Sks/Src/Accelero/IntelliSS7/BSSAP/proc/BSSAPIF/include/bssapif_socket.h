/*********************************-*-H-*-************************************
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
 * LOG: Revision 1.1.2.1  2005/12/20 12:10:13  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: bssapif_socket.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_socket.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $"

#ifndef _BSSAP_SOCKET_H
#define _BSSAP_SOCKET_H

#include <its++.h>
#include <its_ip_trans.h>

class SocketCom
{
public:

    int SendToSocket(its::ITS_Event& evt);

    void SetSocketTransHandle(ITS_HANDLE hd)
    {
       bsTransHandle = hd;
    }

    void SetSocketTransInst(ITS_USHORT inst)
    {
       bsTransInst = inst;
    }

    const ITS_USHORT GetSocketTransInst() const
    {
       return bsTransInst;
    }


    const bool IsClientTransValid(ITS_HANDLE clHandle)
    {
        SOCKTRAN_Manager *ft = (SOCKTRAN_Manager *)clHandle;

        if (ft && SOCKTRAN_IS_VALID(ft))
        {
           return (true);
        }

        return false;
    }

    static SocketCom* GetInstance();

private:
    ITS_USHORT bsTransInst;
    ITS_HANDLE bsTransHandle;

    static its::ITS_Mutex guard;
    static its::ITS_Mutex lock;

private:
    SocketCom();                        /* Prevent Constructor */
    SocketCom(const SocketCom&);            /* Prevent Copy Constructor */
    SocketCom& operator=(const SocketCom&); /* Prevent assignment */

};

#endif
