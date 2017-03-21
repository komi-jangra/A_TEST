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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:14  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:03  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:06  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:08  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.2.1  2005/01/04 13:10:25  mmanikandan
 * LOG: CTF Initial commit.
 * LOG:
 *
 ****************************************************************************/

#include <its_ctf.h>
#include <its_thread_pool.h>
#include <its_transports.h>

static ITS_HANDLE CFTTransportHand_ = NULL;

CTFDLLAPI ITS_INT 
CTF_PostInitialize(TPOOL_THREAD* thr, ITS_HANDLE hnd)
{
    CFTTransportHand_ = hnd;

    return ITS_SUCCESS;
}

CTFDLLAPI ITS_INT 
CTF_TraceEvent (ITS_USHORT src, ITS_USHORT dest, 
                ITS_UINT output, ITS_EVENT* event)
{
    ITS_INT ret = ITS_SUCCESS;

    if (CFTTransportHand_)
    {
        ITS_EVENT evt;
        ITS_USHORT offset = 0;
        ITS_USHORT len = 0;
        
        len = 2*sizeof(ITS_USHORT) + sizeof(ITS_INT) + event->len;
        
        ITS_EVENT_INIT(&evt, 0, len);
        
        evt.data[offset]     = (src & 0xff00) >> 8;
        evt.data[offset + 1] = (src & 0x00ff);
        offset += sizeof(ITS_USHORT);
        
        evt.data[offset]     = (dest & 0xff00) >> 8;
        evt.data[offset + 1] = (dest & 0x00ff);
        offset += sizeof(ITS_USHORT);
        
        evt.data[offset]     = (output & 0xff000000) >> 24;
        evt.data[offset + 1] = (output & 0x00ff0000) >> 16;
        evt.data[offset + 2] = (output & 0x0000ff00) >> 8;
        evt.data[offset + 3] = (output & 0x000000ff);
        offset += sizeof(ITS_INT);
        
        /* Put actual event data */
        memcpy(&evt.data[offset], event->data, event->len);
        
        ret = TRANSPORT_PutEvent (TRANSPORT_INSTANCE(CFTTransportHand_), &evt);
    }

    return ret;
}

