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
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/04/25 23:03:57  mmiers
 * LOG: Add user data.
 * LOG:
 * LOG: Revision 3.6  2001/04/02 19:50:14  mmiers
 * LOG: Solaris build.
 * LOG:
 * LOG: Revision 3.5  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 3.4  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.3  2001/03/06 23:54:44  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.2  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 * LOG: Revision 3.1  2001/03/02 18:27:17  mmiers
 * LOG: Add work item.  Need to add WorkItemPool.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_WORK_ITEM_H)
#define ITS_WORK_ITEM_H

#include <its.h>

#ident "$Id: its_work_item.h,v 1.1.1.1 2007-10-08 11:11:33 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:WORKITEM_*
 *****************************************************************************
 *  Interface:
 *      WORKITEM_*
 *
 *  Purpose:
 *      The WORKITEM_ interface is defined for thread pools that share a
 *      transport.  In this case, "events" placed on the transport are
 *      actually WORKITEMs.
 *
 *  Usage:
 *      Note that a *copy* of the work item is actually placed on the
 *      transport.  For successful processing, the user MUST create
 *      WORKITEMs on the heap, and initialize the object pointer to
 *      self.
 *
 *      NOTE: For simplicity's sake, this is NOT an ITS_Object.  It is felt
 *      that making it so would make using WORKITEMs a pain as a new
 *      ITS_Class would be required for any specialization.  Simply extending
 *      the struct gives the same effect while preserving the interface.
 *
 *      Note the allocator expects the total size of the WORKITEM.
 *      Specializations should take the form
 *
 *      struct specialization
 *      {
 *          WORKITEM_Instance    base;
 *          int foo, bar;
 *      };
 *
 *      WORKITEM_Instance *tmp = WORKITEM_Create(sizeof(struct specialization),
 *                                               ITS_TRUE, ItemFunc);
 *
 *      ...
 *
 *      WORKITEM_PutWorkItem(42, tmp);
 *
 *      Finally, note that the destruction of the object is left to the
 *      application upon determining that the work item is not (any longer)
 *      persistent.
 *
 *****************************************************************************/
typedef struct _workItem    WORKITEM_Instance;

typedef void (*WORKITEM_ItemFunc)(void *instance);

/*
 * this structure MUST be placed at the beginning of any
 * specializations.
 */
struct _workItem
{
    ITS_BOOLEAN         persist;    /* should this work item repeat */
    WORKITEM_ItemFunc   func;       /* work item function */
    void                *object;    /* pointer to real object */
};

ITSDLLAPI WORKITEM_Instance   *WORKITEM_Create(ITS_UINT size,
                                               ITS_BOOLEAN persist,
                                               WORKITEM_ItemFunc func);
ITSDLLAPI void                WORKITEM_Destroy(WORKITEM_Instance *item);

ITSDLLAPI int                 WORKITEM_PutWorkItem(ITS_USHORT instance,
                                                   WORKITEM_Instance *item);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:WorkItem
 *****************************************************************************
 *  Interface:
 *      WorkItem
 *
 *  Purpose:
 *      The WorkItem interface is defined for thread pools that share a
 *      transport.  In this case, "events" placed on the transport are
 *      actually the WORKITEM_Instance member variable.
 *
 *  Usage:
 *
 *****************************************************************************/
class WorkItem
{
public:
    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      Create a work item
     *
     *  Input Parameters:
     *      persist - should the work item persist on the queue
     *
     ************************************************************************/
    WorkItem(bool persist = false)
    {
        if (persist)
        {
            workItem.persist = ITS_TRUE;
        }
        else
        {
            workItem.persist = ITS_FALSE;
        }

        workItem.object = (void *)this;
        workItem.func = (WORKITEM_ItemFunc)CallVirtualExecute;
    }

    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      Destroy a work item
     *
     ************************************************************************/
    virtual ~WorkItem()
    {
    }

    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      Execute a work item
     *
     *  Notes:
     *      Specializations of this base class need to implement
     *      this method.  Specializations should include any data
     *      (or context) they need for this method in the instance
     *      data.
     *
     ************************************************************************/
    virtual void Execute() = 0;

    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      Put a work item on the queue.
     *
     *  Input Parameters:
     *      instance - the transport queue to put to.
     *
     *  Return Value:
     *      ITS_SUCCESS - item was placed on queue
     *
     ************************************************************************/
    int
    PutWorkItem(ITS_USHORT instance)
    {
        return WORKITEM_PutWorkItem(instance, &workItem);
    }

    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      Test a work item for persistence.
     *
     *  Return Value:
     *      true - work item is persistent.  false otherwise
     *
     ************************************************************************/
    bool
    IsPersistent() const
    {
        return (workItem.persist ? true : false);
    }

    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      Make a work item persistent.
     *
     ************************************************************************/
    void
    SetPersistent()
    {
        workItem.persist = ITS_TRUE;
    }

    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      Make a work item non-persistent.
     *
     ************************************************************************/
    void
    SetNonPersistent()
    {
        workItem.persist = ITS_FALSE;
    }

    void
    SetUserData(void *data)
    {
        userData = data;
    }

protected:
    /*.implementation:public,inline,WorkItem
     ************************************************************************
     *  Purpose:
     *      C binding for calling the virtual execute.
     *
     ************************************************************************/
    static void
    CallVirtualExecute(void *object)
    {
        WorkItem *inst = (WorkItem *)object;

        inst->Execute();
    }

private:
    WORKITEM_Instance   workItem;
    void                *userData;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_WORK_ITEM_H */
