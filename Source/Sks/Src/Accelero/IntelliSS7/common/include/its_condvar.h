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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:12  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/08 16:16:11  mmiers
 * LOG: Make sure things compile without its_bc.h.  Fix MutexGuard.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
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
 * LOG: Revision 3.3  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:10  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/08/09 00:08:19  mmiers
 * LOG:
 * LOG: Semaphore is now platform neutral.
 * LOG: Add new error code.
 * LOG: Work on SCTP
 * LOG: Make CONDVAR take a timeout on wait.
 * LOG: Add new entry point to TIMERS.
 * LOG:
 * LOG: Revision 2.1  2000/04/24 22:20:03  mmiers
 * LOG:
 * LOG:
 * LOG: Add condition variable type.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_CONDVAR_H
#define ITS_CONDVAR_H

#include <its_types.h>
#include <its_mutex.h>

#ident "$Id: its_condvar.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#ifdef __cplusplus
extern "C"
{
#endif

/*.interface:CONDVAR
 *****************************************************************************
 *  Interface:
 *      CONDVAR_*
 *
 *  Purpose:
 *      This interface provides an API for architecture independent condition
 *      variable objects from "C".
 *
 *  Usage:
 *****************************************************************************/

ITSDLLAPI int CONDVAR_Create(ITS_CONDVAR *cv);
ITSDLLAPI void CONDVAR_Delete(ITS_CONDVAR *cv);

ITSDLLAPI int CONDVAR_Wait(ITS_CONDVAR *cv, ITS_MUTEX *m);
ITSDLLAPI int CONDVAR_WaitWithTimeOut(ITS_CONDVAR *cv, ITS_MUTEX *m,
                                      ITS_UINT millisecs);
ITSDLLAPI int CONDVAR_Signal(ITS_CONDVAR *cv);
ITSDLLAPI int CONDVAR_Broadcast(ITS_CONDVAR *cv);

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:CondVar
 *****************************************************************************
 *  Interface:
 *      CondVar
 *
 *  Purpose:
 *
 *  Usage:
 *
 *****************************************************************************/
class CondVar
{
public:
    /*.implementation:public,inline,CondVar
     ************************************************************************
     *  Purpose:
     *      Create a condition variable
     *
     ************************************************************************/
    CondVar()
    {
        int ret = CONDVAR_Create(&cv);

        ITS_THROW_ASSERT(ret == ITS_SUCCESS);
    }
    /*.implementation:public,inline,CondVar
     ************************************************************************
     *  Purpose:
     *      Destroy a condition variable
     *
     ************************************************************************/
    virtual ~CondVar()
    {
        CONDVAR_Delete(&cv);
    }

    /*.implementation:public,inline,CondVar
     ************************************************************************
     *  Purpose:
     *      Wait on a condition variable
     *
     *  Input Parameters:
     *      m - the mutex guarding this condition
     *
     *  Return Value:
     *      ITS_SUCCESS - condition waited for
     *
     ************************************************************************/
    int
    Wait(Mutex& m)
    {
        if (CONDVAR_Wait(&cv, &m.mutex) != ITS_SUCCESS)
        {
            return (ITS_EBADCONDVAR);
        }
    
        return (ITS_SUCCESS);
    }
    /*.implementation:public,inline,CondVar
     ************************************************************************
     *  Purpose:
     *      Wait on a condition variable
     *
     *  Input Parameters:
     *      m - the mutex guarding this condition
     *      millisecs - how long to wait
     *
     *  Return Value:
     *      ITS_SUCCESS - condition waited for
     *
     ************************************************************************/
    int
    WaitWithTimeOut(Mutex& m, ITS_UINT millisecs)
    {
        int ret;

        if ((ret = CONDVAR_WaitWithTimeOut(&cv, &m.mutex,
                                           millisecs)) != ITS_SUCCESS)
        {
            return (ret);
        }
    
        return (ITS_SUCCESS);
    }
    /*.implementation:public,inline,CondVar
     ************************************************************************
     *  Purpose:
     *      Signal the next waiter on this condition
     *
     *  Return Value:
     *      ITS_SUCCESS - condition signalled
     *
     ************************************************************************/
    int
    Signal()
    {
        return CONDVAR_Signal(&cv);
    }
    /*.implementation:public,inline,CondVar
     ************************************************************************
     *  Purpose:
     *      Broadcast to all waiters on this condition
     *
     *  Return Value:
     *      ITS_SUCCESS - condition broadcasted
     *
     ************************************************************************/
    int
    Broadcast()
    {
        return CONDVAR_Broadcast(&cv);
    }

private:
    ITS_CONDVAR cv;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_CONDVAR_H */
