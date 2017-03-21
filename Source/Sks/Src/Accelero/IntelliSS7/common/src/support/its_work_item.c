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
 * LOG: Revision 1.2  2007/03/30 04:59:25  cvsadmin
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
 * LOG: Revision 3.4  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.3  2001/03/02 23:04:04  mmiers
 * LOG: Cross platform cleanup.
 * LOG:
 * LOG: Revision 3.2  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
 * LOG:
 * LOG: Revision 3.1  2001/03/02 18:27:17  mmiers
 * LOG: Add work item.  Need to add WorkItemPool.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#include <its.h>
#include <its_assertion.h>
#include <its_transports.h>
#include <its_work_item.h>

#ident "$Id: its_work_item.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a work item.
 *
 *  Input Parameters:
 *      size - the size of the work item
 *      persist - should the work item be returned to the queue after
 *          processing
 *      func - the function to be invoked.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the allocated work item or NULL if not allocated.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI WORKITEM_Instance *
WORKITEM_Create(ITS_UINT size, ITS_BOOLEAN persist, WORKITEM_ItemFunc func)
{
    WORKITEM_Instance *tmp;

    ITS_C_REQUIRE(size >= sizeof(WORKITEM_Instance));

    if ((tmp = calloc(1, size)) == NULL)
    {
        return (NULL);
    }

    tmp->persist = persist;
    tmp->func = func;
    tmp->object = tmp;

    return (tmp);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Free a work item.
 *
 *  Input Parameters:
 *      item - the item to free.
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
 ****************************************************************************/
ITSDLLAPI void
WORKITEM_Destroy(WORKITEM_Instance *item)
{
    free(item);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Free a work item.
 *
 *  Input Parameters:
 *      item - the item to free.
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
 *      Note the event source.  That is used as a sanity check in the work
 *      item dispatcher to ensure that *this* function was used to put the
 *      work item on the queue (in other words, to force error conditions
 *      if a true event should be put on the queue).
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
WORKITEM_PutWorkItem(ITS_USHORT instance, WORKITEM_Instance *item)
{
    ITS_EVENT event;

    ITS_EVENT_INIT(&event, ITS_NO_SRC, sizeof(WORKITEM_Instance));

    memcpy(event.data, item, sizeof(WORKITEM_Instance));

    return TRANSPORT_PutEvent(instance, &event);
}
