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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:58  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/05/01 23:09:03  mmiers
 * LOG: Add functionality for HMI and alarm.  The rest is pretty easy.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.4  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 3.3  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.2  2001/03/06 23:54:44  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.1  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_WORK_ITEM_POOL_H
#define ITS_WORK_ITEM_POOL_H

#include <its_thread_pool.h>
#include <its_transports.h>
#include <its_work_item.h>

#ident "$Id: its_work_item_pool.h,v 1.1.1.1 2007-10-08 11:11:33 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:WORKITEMPOOL_*
 *****************************************************************************
 *  Interface:
 *      WORKITEMPOOL_*
 *
 *  Purpose:
 *      The WORKITEMPOOL is a specialization of TPOOL designed to share
 *      a single transport.
 *
 *  Usage:
 e****************************************************************************/
typedef struct
{
    TRANSPORT_Control   *queue;
    int                 numThreads;
}
WORKITEMPOOL_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TPOOL_ObjectPart        tpool;
    WORKITEMPOOL_ObjectPart workItemPool;
}
WORKITEMPOOL;

#define WORKITEMPOOL_QUEUE(x) \
    (((WORKITEMPOOL *)(x))->workItemPool.queue)

#define WORKITEMPOOL_NUM_THREADS(x) \
    (((WORKITEMPOOL *)(x))->workItemPool.numThreads)

#define WORKITEMPOOL_CLASS_NAME "WORKITEM_POOL class"

ITSDLLAPI extern TPOOL_ClassRec   itsWORKITEMPOOL_ClassRec;
ITSDLLAPI extern TPOOL_Class      itsWORKITEMPOOL_Class;

/*
 * API
 */
ITSDLLAPI WORKITEMPOOL *  WORKITEMPOOL_InitPool(void *data,
                                                ITS_USHORT instance,
                                                int numThreads,
                                                int stackSize,
                                                TPOOL_FUNC dispatch);
ITSDLLAPI void            WORKITEMPOOL_DestroyPool(WORKITEMPOOL *pool);
ITSDLLAPI void            WORKITEMPOOL_Dispatch(TPOOL_THREAD *thr,
                                                void *arg);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_NAMESPACE)
namespace its
{
#endif
/*.interface:WorkItemPool
 *****************************************************************************
 *  Interface:
 *      WorkItemPool
 *
 *  Purpose:
 *      The WorkItemPool is a specialization of ThreadPool designed to share
 *      a single transport.
 *
 *  Usage:
 *****************************************************************************/
class WorkItemPool
{
public:
    /*.implementation:public,inline,WorkItemPool
     ************************************************************************
     *  Purpose:
     *      Create a work item pool
     *
     *  Input Parameters:
     *      instance - the transport instance to use
     *      numThreads - number of threads in the pool
     *      stackSize - stack size for each thread
     *
     ************************************************************************/
    WorkItemPool(ITS_USHORT instance, int numThreads, int stackSize)
    {
        pool = WORKITEMPOOL_InitPool(this, instance,
                                     numThreads, stackSize,
                                     WORKITEMPOOL_Dispatch);

        ITS_THROW_ASSERT(pool != NULL);
    }

    /*.implementation:public,inline,WorkItemPool
     ************************************************************************
     *  Purpose:
     *      Destroy a work item pool
     *
     ************************************************************************/
    virtual
    ~WorkItemPool()
    {
        WORKITEMPOOL_DestroyPool(pool);
    }

    /*.implementation:public,inline,WorkItemPool
     ************************************************************************
     *  Purpose:
     *      Add a work item to a pool
     *
     *  Input Parameters:
     *      item - the work item to add
     *
     *  Return Value:
     *      ITS_SUCCESS - item added ok.
     *
     ************************************************************************/
    int
    AddWorkItem(WorkItem *item)
    {
        return item->PutWorkItem(TRANSPORT_INSTANCE(WORKITEMPOOL_QUEUE(pool)));
    }

private:
    WORKITEMPOOL    *pool;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_WORK_ITEM_POOL_H */
