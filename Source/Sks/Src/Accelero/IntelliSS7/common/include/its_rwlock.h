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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:21  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/06/02 02:05:15  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some nasty hangaround bugs, convert transports and route to
 * LOG: RWLOCK.
 * LOG:
 * LOG: Revision 2.1  2000/05/03 21:07:14  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding support for reader/writer locks.
 * LOG: Add SOCK_GetPeerName().
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_RWLOCK_H
#define ITS_RWLOCK_H

#include <its_types.h>
#include <its_mutex.h>

#ident "$Id: its_rwlock.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#ifdef __cplusplus
extern "C"
{
#endif


#if !defined(ITS_RWLOCK_ONESHOT)
#define ITS_RWLOCK_ONESHOT

/*
 * Reader/writer lock
 */
typedef struct
{
    ITS_MUTEX         guard;
    ITS_INT           numActive;
    ITS_UINT          readerWaitCount;
    ITS_UINT          writerWaitCount;
    ITS_CONDVAR       readerQueue;
    ITS_CONDVAR       writerQueue;
}
ITS_RWLOCK;

#endif /* ITS_RWLOCK_ONESHOT */

/*.interface:RWLOCK_
 *****************************************************************************
 *  Interface:
 *      RWLOCK_*
 *
 *  Purpose:
 *      This interface provides an API for architecture independent reader
 *      writer lock objects from "C".
 *
 *  Usage:
 *      Allow many readers or a single writer to hold a lock.  NOTE: these
 *      are not panacea objects.  If you think that upgrading a reader
 *      lock to a writer lock will fix all of your issues, think again.
 *      Upgrading a reader lock to a writer lock *can*imply* that another,
 *      disjoint (meaning not current thread) writer may acquire the lock
 *      before you do.  This implies that you should repeat your reader
 *      operations (i.e., all operations from the RWLOCK_LockShared() to
 *      RWLOCK_UpgradeToExclusive() calls) because it is possible that a
 *      writer intervened between your shared lock and your upgrade to
 *      exclusive lock and changed your reader data.  Think about it.
 *      
 *****************************************************************************/

ITSDLLAPI int RWLOCK_CreateLock(ITS_RWLOCK *rw);
ITSDLLAPI void RWLOCK_DeleteLock(ITS_RWLOCK *rw);

ITSDLLAPI int RWLOCK_LockShared(ITS_RWLOCK* rw);
ITSDLLAPI int RWLOCK_UnlockShared(ITS_RWLOCK* rw);
ITSDLLAPI int RWLOCK_LockExclusive(ITS_RWLOCK* rw);
ITSDLLAPI int RWLOCK_UnlockExclusive(ITS_RWLOCK* rw);

ITSDLLAPI int RWLOCK_UpgradeToExclusive(ITS_RWLOCK* rw);
ITSDLLAPI int RWLOCK_DowngradeToShared(ITS_RWLOCK* rw);

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:RWLock
 *****************************************************************************
 *  Interface:
 *      RWLock
 *
 *  Purpose:
 *
 *  Usage:
 *
 *****************************************************************************/
class RWLock
{
public:
    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function creates a reader/writer lock.
     *
     *  See Also:
     *      ~RWLock()
     ************************************************************************/
    RWLock()
    {
        int ret;

        ret = RWLOCK_CreateLock(&rwlock);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }
    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function destroys the reader/writer lock
     *
     *  See Also:
     *      RWLock()
     ************************************************************************/
    virtual ~RWLock()
    {
        RWLOCK_DeleteLock(&rwlock);
    }

    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function waits for a non-exclusive lock to be granted.
     *
     *  Return Value:
     *      Once the lock is granted, ITS_SUCCESS is returned.
     *      Any other value indicates an IntelliSS7 error.
     *
     *  See Also:
     *      UnlockShared()
     ************************************************************************/
    int
    LockShared()
    {
        return RWLOCK_LockShared(&rwlock);
    }
    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function releases a non-exclusive lock.
     *
     *  Return Value:
     *      On success, ITS_SUCCESS is returned.
     *      Any other value indicates that an IntelliSS7 error has occurred.
     *
     *  See Also:
     *      LockShared()
     ************************************************************************/
    int
    UnlockShared()
    {
        return RWLOCK_UnlockShared(&rwlock);
    }
    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function waits for an exclusive lock to be granted.
     *
     *  Return Value:
     *      Once the lock is granted, ITS_SUCCESS is returned.
     *      Any other value indicates an IntelliSS7 error.
     *
     *  See Also:
     *      UnlockExclusive()
     ************************************************************************/
    int
    LockExclusive()
    {
        return RWLOCK_LockExclusive(&rwlock);
    }
    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function releases an exclusive lock.
     *
     *  Return Value:
     *      On success, ITS_SUCCESS is returned.
     *      Any other value indicates that an IntelliSS7 error has occurred.
     *
     *  See Also:
     *      LockExclusive()
     ************************************************************************/
    int
    UnlockExclusive()
    {
        return RWLOCK_UnlockExclusive(&rwlock);
    }
    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function upgrades a non-exclusive lock to exclusive.
     *
     *  Return Value:
     *      On success, ITS_SUCCESS is returned.
     *      Any other value indicates that an IntelliSS7 error has occurred.
     *
     *  See Also:
     *      DowngradeToShared()
     ************************************************************************/
    int
    UpgradeToExclusive()
    {
        return RWLOCK_UpgradeToExclusive(&rwlock);
    }
    /*.implementation:public,inline,RWLock
     ************************************************************************
     *  Purpose:
     *      This function downgrades an exclusive lock to non-exclusive.
     *
     *  Return Value:
     *      On success, ITS_SUCCESS is returned.
     *      Any other value indicates that an IntelliSS7 error has occurred.
     *
     *  See Also:
     *      UpgradeExclusive()
     ************************************************************************/
    int
    DowngradeToShared()
    {
        return RWLOCK_DowngradeToShared(&rwlock);
    }

private:
    ITS_RWLOCK rwlock;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_RWLOCK_H */
