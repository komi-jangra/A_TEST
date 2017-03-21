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
 *  ID: $Id: test20.cpp,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:33  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:14  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:25  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:27  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/04/25 16:49:26  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:58  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 1.6  1998/11/18 18:07:10  mmiers
 * LOG: Update project information.
 * LOG:
 * LOG: Revision 1.5  1998/06/30 01:50:27  mmiers
 * LOG: IS634: Clean up some warnings from a GCC build (ANSI "for" scope rule).
 * LOG: The rest is cleanup.  We can add Linux as a platform, but it is not
 * LOG: safe multithreaded (yet).
 * LOG:
 * LOG: Revision 1.4  1998/05/29 03:31:38  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.3  1998/04/16 15:59:02  mmiers
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  1998/04/13 20:41:11  mmiers
 * LOG: Finish tracking down the bugs for Windows sockets.  NOTE:
 * LOG: You MUST call WSAStartup for ALL sockets created --
 * LOG: INCLUDING the socket that is the result of accept().
 * LOG:
 * LOG: Revision 1.1  1998/04/09 15:25:58  mmiers
 * LOG: Some cleanup for testing purposes.
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <its++.h>
#include <its_sockets.h>
#include <its_mutex.h>
#include <its_semaphore.h>
#include <its_list.h>
#include <its_mlist.h>
#include <its_emlist.h>
#include <its_thread.h>
#include <its_statics.cpp>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

THREAD_RET_TYPE
thread_func(void *arg)
{
    THREAD_NORMAL_EXIT;
}

ITS_MList avail;
ITS_MList busy;

class TEST_Entry : public ITS_ListEntry
{
public:
    TEST_Entry(int _copy) { copy = _copy; }
    virtual ~TEST_Entry() {}

    virtual ITS_ListEntry *Clone() const
    {
        TEST_Entry *newTest = new TEST_Entry(copy);

        return (ITS_ListEntry *)newTest;
    }

    virtual void Release()
    {
        delete this;
    }

    virtual ITS_ListEntry& operator=(const ITS_ListEntry& copy)
    {
        prev = copy.prev;
        next = copy.next;

        static_cast<TEST_Entry *>(this)->copy =
            static_cast<const TEST_Entry *>(&copy)->copy;

        return *this;
    }

    virtual bool operator==(const ITS_ListEntry& rhs) const
    {
        return (copy == static_cast<const TEST_Entry *>(&rhs)->copy);
    }

private:
    int copy;
};

int
main(int argc, char **argv)
{
    int i;
    TEST_Entry entry(-1);

    for (i = 0; i < 32; i++)
    {
        TEST_Entry entry(i);

        avail.AddHead(entry);
    }

    for (i = 0; i < 0x7FFFF; i++)
    {
        avail.RemHead(entry);

        busy.AddTail(entry);

        busy.Unlink(entry);

        avail.AddTail(entry);
    }

    return (0);
}
