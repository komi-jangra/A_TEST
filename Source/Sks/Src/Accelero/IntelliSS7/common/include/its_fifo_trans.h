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
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:46  cvsadmin
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
 * LOG: Revision 4.2  2001/06/27 22:57:42  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
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
 * LOG: Revision 3.1  2000/08/16 00:03:13  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:52:34  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:34  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.18  1999/10/25 18:28:08  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.17  1999/09/01 00:53:28  mmiers
 * LOG:
 * LOG:
 * LOG: This work makes the transport system a little more sane.  What I
 * LOG: did was make the Transport class implement the default behavior
 * LOG: for transports, which should make things like:
 * LOG:     Transport tc = transport->GetTC();
 * LOG: work when you say
 * LOG:     tc.GetNextEvent(ev);
 * LOG:
 * LOG: Revision 1.16  1999/07/29 01:58:17  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the first round of addressing Hubert's review comments.
 * LOG:
 * LOG: Revision 1.15  1998/11/19 00:36:17  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.14  1998/09/22 16:01:23  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.13  1998/06/26 14:30:37  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.12  1998/06/18 17:16:28  mmiers
 * LOG: Finish up the C transports and the SS7 transports.
 * LOG:
 * LOG: Revision 1.11  1998/06/18 00:24:56  mmiers
 * LOG: Documentation update, C versions of some transports, C version of
 * LOG: resource file manager.
 * LOG:
 * LOG: Revision 1.10  1998/06/02 19:43:13  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.9  1998/06/01 16:35:14  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.8  1998/05/31 02:59:38  mmiers
 * LOG: More documenation, stabilizing the interfaces.
 * LOG:
 * LOG: Revision 1.7  1998/05/29 22:35:35  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.6  1998/05/29 13:42:27  mmiers
 * LOG: Somebody keeps dropping GatedFifo.
 * LOG:
 * LOG: Revision 1.5  1998/05/29 03:31:29  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.4  1998/05/27 02:18:11  mmiers
 * LOG: Reimplement fifos for NT and Solaris.  Nobody should be affected by this
 * LOG: change (from a user perspective), but ITS_Worker has a new transport type,
 * LOG: depending on whether or not the FIFO transport is reentrant.
 * LOG:
 * LOG: Revision 1.3  1998/05/19 17:11:44  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.2  1998/05/01 00:24:30  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 22:20:03  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_FIFO_TRANS_H
#define ITS_FIFO_TRANS_H

#include <its.h>
#include <its_fifo.h>
#include <its_transports.h>

#ident "$Id: its_fifo_trans.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if !defined(ITS_FIFO_TRANS_ONESHOT)
#define ITS_FIFO_TRANS_ONESHOT

/*
 * resource strings
 */
#define FIFO_CLIENT_PATH_STRING    "clientPath"
#define FIFO_SERVER_PATH_STRING    "serverPath"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * a fifo transport in "C"
 */
typedef struct
{
    char *              sourceName;
    char *              sinkName;
    ITS_FIFO            source;
    ITS_FIFO            sink;
}
FIFOTRAN_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    FIFOTRAN_ObjectPart     fifo;
}
FIFOTRAN_Manager;

#define FIFOTRAN_SOURCE_NAME(x) \
    (((FIFOTRAN_Manager *)(x))->fifo.sourceName)

#define FIFOTRAN_SINK_NAME(x) \
    (((FIFOTRAN_Manager *)(x))->fifo.sinkName)

#define FIFOTRAN_SOURCE(x) \
    (((FIFOTRAN_Manager *)(x))->fifo.source)

#define FIFOTRAN_SINK(x) \
    (((FIFOTRAN_Manager *)(x))->fifo.sink)

ITSDLLAPI extern TRANSPORT_ClassRec   itsFIFOTRAN_ClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsFIFOTRAN_Class;

#define FIFOTRAN_CLASS_NAME "FIFOTRAN"

ITSDLLAPI FIFOTRAN_Manager* FIFOTRAN_CreateTransport(const char *name,
                                                     ITS_USHORT instance,
                                                     ITS_UINT mask);
ITSDLLAPI void FIFOTRAN_DeleteTransport(FIFOTRAN_Manager *ft);

#if defined(__cplusplus)
}
#endif

#endif

#if defined (USE_CPLUSPLUS)

#include <string>

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*
 * fifo
 */
/*.interface:FifoTransport
 *****************************************************************************
 *  Interface:
 *      FifoTransport
 *
 *  Purpose:
 *      The FifoTransport is simply a transport implemented via
 *      a FIFO queue.  It implements no additional functionality beyond
 *      that of the Transport class.  See:
 *      <A HREF=its_transport.html>Transport</A>
 *      for additional information.
 *
 *  Usage:
 *      See Transport for usage.
 *
 *      The resource file is expected to contain the variables
 *      FIFO_CLIENT_PATH
 *      and
 *      FIFO_SERVER_PATH
 *
 *      The FIFO_SERVER_PATH is the fifo name that this transport will read
 *      from.  The FIFO_CLIENT_PATH is the fifo name that this transport will
 *      send messages to.
 *
 *****************************************************************************/
class FifoTransport : public Transport
{
public:
    /*.implementation:public,inline,FifoTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a FIFO based transport.  Two fifos are
     *      created (one for reading, one for writing); this routine should
     *      succeed even if the other endpoint process is not present when
     *      the fifos are created.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for path information for the
     *      fifo.
     *
     *  See Also:
     *      ~FifoTransport
     ************************************************************************/
    FifoTransport(const char *name,
                      ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (FIFOTRAN_CreateTransport(const_cast<char *>(name),
                                       instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_EBADFIFO, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,FifoTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a FIFO based transport.  Two fifos are
     *      created (one for reading, one for writing); this routine should
     *      succeed even if the other endpoint process is not present when
     *      the fifos are created.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for path information for the
     *      fifo.
     *
     *  See Also:
     *      ~FifoTransport
     ************************************************************************/
    FifoTransport(const std::string& name,
                      ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (FIFOTRAN_CreateTransport(const_cast<char *>(name.c_str()),
                                       instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_EBADFIFO, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,FifoTransport
     ************************************************************************
     *  Purpose:
     *      This method destroys a fifo transport.
     *
     *  See Also:
     *      FifoTransport()
     ************************************************************************/
    virtual ~FifoTransport()
    {
        if (tc)
        {
            FIFOTRAN_DeleteTransport(
                reinterpret_cast<FIFOTRAN_Manager *>(tc));
        }
    }

    /*.implementation:public,inline,FifoTransport
     ************************************************************************
     *  Purpose:
     *      This method peeks at the server end of the fifo to see if data is
     *      present.  If data is present, it attempts to read the data into
     *      an event.
     *
     *  Output Parameters:
     *      event - a reference to an Event to place the incoming event
     *          into
     *
     *  Return Value:
     *      If the event is successfully read, ITS_SUCCESS is returned.
     *      If no data is available, ITS_ENOMSG is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    PeekNextEvent(Event& event)
    {
        return (ITS_ENOMSG);
    }

private:
    /* sorry, no copying */
    FifoTransport& operator=(Transport&) { return *this; }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_FIFO_TRANS_H */
