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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:26  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:02  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.7  2001/04/04 01:20:54  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.6  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.5  2001/03/16 20:56:07  mmiers
 * LOG:
 * LOG: Ok, only resdb and parsing left.
 * LOG:
 * LOG: Revision 3.4  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 3.3  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.2  2001/03/06 22:19:30  mmiers
 * LOG: Cross-platform cleanup.
 * LOG:
 * LOG: Revision 3.1  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#include <its.h>
#include <its_assertion.h>
#include <its_transports.h>
#include <its_work_item.h>
#include <its_work_item_pool.h>
#include <its_tq_trans.h>

#ident "$Id: its_work_item_pool.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a thread into this pool
 *
 *  Input Parameters:
 *      pool - the pool to create into
 *      stackSize - the stacksize of this thread
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      a pointer to the created thread.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static TPOOL_THREAD *
ThreadCreate(TPOOL *pool, int stackSize)
{
    return (TPOOL_THREAD *)calloc(1, sizeof(TPOOL_THREAD));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a work item pool.
 *
 *  Input Parameters:
 *      obj - the pool being created.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the pool was created successfully
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ConstructPool(ITS_Object obj, va_list args)
{
    void *data;
    ITS_USHORT instance;
    int numThreads, stackSize, ret, i;
    TPOOL_FUNC dispatch;
    char name[ITS_PATH_MAX];

    data = va_arg(args, void *);
    instance = (ITS_USHORT)va_arg(args, ITS_UINT);
    numThreads = va_arg(args, int);
    stackSize = va_arg(args, int);
    dispatch = va_arg(args, TPOOL_FUNC);

    ITS_C_REQUIRE(dispatch != NULL);

    /*
     * ok, the superclass constructor has built the object.  Now we need
     * to finish constructing the pool.
     */
    sprintf(name, ITS_UNNAMED_TRANSPORT_FORMAT_STRING, instance);

    if ((WORKITEMPOOL_QUEUE(obj) = (TRANSPORT_Control *)
                                    TQUEUETRAN_CreateTransport(name,
                                                               instance,
                                                               0)) == NULL)
    {
        return (ITS_ENOTRANSPORT);
    }

    WORKITEMPOOL_NUM_THREADS(obj) = numThreads;

    /*
     * create the pool
     */
    if ((ret = TPOOL_CreatePool((TPOOL *)obj, numThreads, stackSize,
                                ThreadCreate)) != ITS_SUCCESS)
    {
        return (ret);
    }

    for (i = 0; i < numThreads; i++)
    {
        TPOOL_Dispatch((TPOOL *)obj, dispatch, obj);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a work item pool.
 *
 *  Input Parameters:
 *      obj - the pool being destroyed.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the pool was created successfully
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
DestroyPool(ITS_Object obj)
{
    int i;
    ITS_EVENT ev;

    ITS_EVENT_INIT(&ev, TRANSPORT_INSTANCE(WORKITEMPOOL_QUEUE(obj)), 0);

    /* put dummy events to clean the queue */
    for (i = 0; i < WORKITEMPOOL_NUM_THREADS(obj); i++)
    {
        TRANSPORT_PutEvent(TRANSPORT_INSTANCE(WORKITEMPOOL_QUEUE(obj)),
                           &ev);
    }
}

/*
 * the class record
 */
ITSDLLAPI TPOOL_ClassRec itsWORKITEMPOOL_ClassRec =
{
    /* core */
    {
        (ITS_Class)&itsTPOOL_ClassRec,/* core superclass */
        sizeof(WORKITEMPOOL),      /* instance size */
        ITS_FALSE,                 /* not initialized */
        0,                         /* initial ref count */
        WORKITEMPOOL_CLASS_NAME,   /* class name */
        ITS_CLASS_NO_INIT,         /* class initializer */
        ITS_CLASS_NO_DEST,         /* class destructor */
        ITS_CLASS_PART_NO_INIT,    /* class part constructor */
        ITS_CLASS_PART_NO_DEST,    /* class part destructor */
        ConstructPool,             /* instance constructor */
        DestroyPool,               /* instance destructor */
        ITS_INST_CLONE_INHERIT,    /* inherit clone */
        ITS_INST_PRINT_INHERIT,    /* inherit print */
        ITS_INST_SERIAL_INHERIT,   /* inherit serial */
        ITS_INST_EQUALS_INHERIT,   /* inherit equals */
        ITS_INST_HASH_INHERIT,     /* inherit hash */
        NULL                       /* no meaningful extension */
    },
    /* tpool */
    /* nothing to say */
};

ITSDLLAPI TPOOL_Class itsWORKITEMPOOL_Class = &itsWORKITEMPOOL_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Create a work item pool.
 *
 *  Input Parameters:
 *      data - back pointer (C++)
 *      instance - work item queue instance
 *      numThreads - number of threads associated with this queue
 *      stackSize - default stackSize for each thread
 *      dispatch - the function to execute
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the pool was created successfully
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI WORKITEMPOOL *
WORKITEMPOOL_InitPool(void *data, ITS_USHORT instance,
                      int numThreads, int stackSize,
                      TPOOL_FUNC dispatch)
{
    return (WORKITEMPOOL *)ITS_ConstructObject((ITS_Class)
                                                  itsWORKITEMPOOL_Class,
                                               data, instance,
                                               numThreads, stackSize,
                                               dispatch);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Destroy a work item pool.
 *
 *  Input Parameters:
 *      pool - the pool being destroyed.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the pool was created successfully
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
WORKITEMPOOL_DestroyPool(WORKITEMPOOL *pool)
{
    ITS_DestructObject((ITS_Object)pool);
}


/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Dispatch a work item
 *
 *  Input Parameters:
 *      thr - this border thread
 *      arg - the work item queue
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
ITSDLLAPI void
WORKITEMPOOL_Dispatch(TPOOL_THREAD *thr, void *arg)
{
    ITS_EVENT event;
    TRANSPORT_Control *tc = WORKITEMPOOL_QUEUE(arg);
    WORKITEM_Instance *item;

    memset(&event, 0, sizeof(ITS_EVENT));

    while (TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(tc))(tc, &event) ==
           ITS_SUCCESS)
    {
        /* termination event? */
        if (event.src == TRANSPORT_INSTANCE(tc))
        {
            break;
        }

        ITS_C_ASSERT(event.src == ITS_NO_SRC);

        /* process the work item */
        item = (WORKITEM_Instance *)event.data;

        if (item->func)
        {
            (item->func)(item->object);
        }

        if (item->persist)
        {
            TRANSPORT_CLASS_PUT_EVENT(ITS_OBJ_CLASS(tc))(tc, &event);
            event.data = NULL;
        }
        else
        {
            ITS_EVENT_TERM(&event);
        }
    }
}
