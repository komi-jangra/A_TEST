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
 * LOG: Revision 8.2  2005/03/21 13:50:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/03/06 23:54:44  mmiers
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
 * LOG: Revision 3.1  2000/08/16 00:03:25  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:52:36  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:48  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.17  1999/10/25 18:28:09  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.16  1999/09/01 00:53:29  mmiers
 * LOG:
 * LOG:
 * LOG: This work makes the transport system a little more sane.  What I
 * LOG: did was make the Transport class implement the default behavior
 * LOG: for transports, which should make things like:
 * LOG:     Transport tc = transport->GetTC();
 * LOG: work when you say
 * LOG:     tc.GetNextEvent(ev);
 * LOG:
 * LOG: Revision 1.15  1999/07/29 01:58:19  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the first round of addressing Hubert's review comments.
 * LOG:
 * LOG: Revision 1.14  1998/11/19 00:36:21  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.13  1998/09/22 16:01:26  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.12  1998/07/21 18:37:13  mmiers
 * LOG: Add mutex initialization to ip transports.
 * LOG:
 * LOG: Remove vestigial connection variable from tq transports.
 * LOG:
 * LOG: Add localPC, localSSN processing to the transport base class.
 * LOG:
 * LOG: Revision 1.11  1998/06/26 14:30:40  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.10  1998/06/18 03:29:14  mmiers
 * LOG: Create the task queue transport type.
 * LOG:
 * LOG: Revision 1.9  1998/06/02 19:43:16  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.8  1998/06/01 16:35:21  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.7  1998/05/31 02:59:40  mmiers
 * LOG: More documenation, stabilizing the interfaces.
 * LOG:
 * LOG: Revision 1.6  1998/05/29 22:35:36  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.5  1998/05/29 15:08:58  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.4  1998/05/29 03:31:33  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.3  1998/05/19 17:11:49  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.2  1998/05/01 00:24:35  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 22:20:05  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_TQ_TRANS_H
#define ITS_TQ_TRANS_H

#include <its.h>
#include <its_transports.h>
#include <its_emlist.h>

#ident "$Id: its_tq_trans.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if !defined(ITS_TQ_TRANS_ONESHOT)
#define ITS_TQ_TRANS_ONESHOT

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * a task queue transport in "C"
 */
typedef struct
{
    EMLIST_Manager*     emlist;
}
TQUEUETRAN_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    TQUEUETRAN_ObjectPart   tqueue;
}
TQUEUETRAN_Manager;

#define TQUEUETRAN_EMLIST(x) \
    (((TQUEUETRAN_Manager *)(x))->tqueue.emlist)

ITSDLLAPI extern TRANSPORT_ClassRec       itsTQUEUETRAN_ClassRec;
ITSDLLAPI extern TRANSPORT_Class          itsTQUEUETRAN_Class;

#define TQUEUETRAN_CLASS_NAME   "TQUEUETRAN"

ITSDLLAPI TQUEUETRAN_Manager* TQUEUETRAN_CreateTransport(const char *name,
                                                         ITS_USHORT instance,
                                                         ITS_UINT mask);
ITSDLLAPI void TQUEUETRAN_DeleteTransport(TQUEUETRAN_Manager *ft);

#if defined(__cplusplus)
}
#endif

#endif /* ITS_TQ_TRANS_ONESHOT */

#if defined (USE_CPLUSPLUS)

#include <string>

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:TaskQueueTransport
 *****************************************************************************
 *  Interface:
 *      TaskQueueTransport
 *
 *  Purpose:
 *      The ITS_FifoTransport is simply a transport implemented via
 *      an ITS_EMList message queue.  It implements no additional
 *      functionality beyond that of the Transport class.  See:
 *      <A HREF=its_transport.html>Transport</A>
 *      for additional information.
 *
 *  Usage:
 *      See Transport for usage.  Note that this transport is intraprocess
 *      ONLY.
 *
 *****************************************************************************/
class TaskQueueTransport : public Transport
{
public:
    /*.implementation:public,inline,TaskQueueTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a task queue based transport.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  See Also:
     *      ~TaskQueueTransport
     ************************************************************************/
    TaskQueueTransport(const char *name,
                       ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (TQUEUETRAN_CreateTransport(const_cast<char *>(name),
                                         instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_ENOLIST, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,TaskQueueTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a task queue based transport.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  See Also:
     *      ~TaskQueueTransport
     ************************************************************************/
    TaskQueueTransport(const std::string& name,
                       ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (TQUEUETRAN_CreateTransport(const_cast<char *>(name.c_str()),
                                         instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_ENOLIST, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,TaskQueueTransport
     ************************************************************************
     *  Purpose:
     *      This method destroys a task queue transport.
     *
     *  See Also:
     *      TaskQueueTransport()
     ************************************************************************/
    virtual ~TaskQueueTransport()
    {
        if (tc)
        {
            TQUEUETRAN_DeleteTransport(
                reinterpret_cast<TQUEUETRAN_Manager *>(tc));
        }
    }

private:
    /* sorry, no copying */
    TaskQueueTransport& operator=(Transport&) { return *this; }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_TQ_TRANS_H */
