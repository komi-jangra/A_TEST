/****************************************************************************
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
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/07 15:27:42  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:07  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/27 22:57:42  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.4  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2000/11/29 23:42:35  mmiers
 * LOG: HPUX has a problem with C common variables in C++.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:35  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:08  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/02/03 15:07:44  mmiers
 * LOG:
 * LOG:
 * LOG: Add pragma for Hubert.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.31  1999/10/26 14:27:06  mmiers
 * LOG:
 * LOG:
 * LOG: The truth about STL.
 * LOG:
 * LOG: Revision 1.30  1999/08/30 17:53:40  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitization of the support library.
 * LOG:
 * LOG: Revision 1.29  1999/07/29 16:27:03  mmiers
 * LOG:
 * LOG:
 * LOG: Add basic type ByteArray (template vector<ITS_OCTET>).
 * LOG:
 * LOG: Revision 1.28  1999/07/29 00:08:37  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating some of Hubert's review comments.
 * LOG:
 * LOG: Revision 1.27  1999/06/28 19:57:01  mmiers
 * LOG:
 * LOG:
 * LOG: Try this one more time.
 * LOG:
 * LOG: Revision 1.26  1999/06/28 19:43:37  mmiers
 * LOG:
 * LOG:
 * LOG: Add a #define so we can see std behavior.
 * LOG:
 * LOG: Revision 1.25  1999/06/28 19:13:26  skarmakar
 * LOG:
 * LOG:
 * LOG: Update with awareness of throw specifiers.
 * LOG:
 * LOG: Revision 1.24  1999/06/28 18:58:38  skarmakar
 * LOG:
 * LOG:
 * LOG: Add support for throw lists.  Add #defines for STD namespace,
 * LOG: namespaces in general, and throw specifiers.
 * LOG:
 * LOG: Revision 1.23  1998/09/26 21:01:45  mmiers
 * LOG: Adapt DBC to UNIX.
 * LOG:
 * LOG: Revision 1.22  1998/08/21 20:38:10  whu
 * LOG: When we set the data, we might as well set the length too.
 * LOG:
 * LOG: Revision 1.21  1998/07/08 20:01:54  mmiers
 * LOG: Fix some buggy comments Hongling identified.
 * LOG:
 * LOG: Revision 1.20  1998/06/30 20:59:09  mmiers
 * LOG: Update a few comments.
 * LOG:
 * LOG: Revision 1.19  1998/06/26 14:30:36  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.18  1998/06/24 16:12:29  mmiers
 * LOG: Straighten out the tranport vs. worker issues.
 * LOG:
 * LOG: Revision 1.17  1998/06/15 16:29:06  mmiers
 * LOG: Testing TCAP.
 * LOG:
 * LOG: Revision 1.16  1998/06/01 16:35:12  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.15  1998/05/28 02:59:12  mmiers
 * LOG: More documentation, make application route selection single threaded,
 * LOG: and remove nasty tab characters from StandardHeaders.
 * LOG:
 * LOG: Revision 1.14  1998/05/22 17:24:12  mmiers
 * LOG: Handle C++ style comments.
 * LOG:
 * LOG: Revision 1.13  1998/05/22 16:23:10  mmiers
 * LOG: Sample work for documentation purposes.
 * LOG:
 * LOG: Revision 1.12  1998/05/19 17:11:43  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.11  1998/05/08 00:23:54  hdivoux
 * LOG: Added #define ITS_NAMESPACE if WIN32 is defined.
 * LOG:
 * LOG: Revision 1.10  1998/05/06 21:26:52  mmiers
 * LOG: Continue working on IS634 and SCCP.  Add C++ bindings for IS634
 * LOG: SCCP, and TCAP.
 * LOG:
 * LOG: Revision 1.9  1998/04/27 20:00:25  mmiers
 * LOG: Get trace working (portably).  More work on TCAP.
 * LOG:
 * LOG: Revision 1.8  1998/04/22 22:20:03  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 * LOG: Revision 1.7  1998/04/20 22:04:43  mmiers
 * LOG: Integrate in the worker code.  Trying to maintain backwards
 * LOG: compatibility with existing vendor code.
 * LOG:
 * LOG: Revision 1.6  1998/04/19 02:42:46  mmiers
 * LOG: Pretty close to having the basic worker architecture for the HLR
 * LOG: done.
 * LOG:
 * LOG: Revision 1.5  1998/04/17 17:43:20  mmiers
 * LOG: Working thread pool.  Still have to do something about termination.
 * LOG:
 * LOG: Revision 1.4  1998/04/17 02:11:44  mmiers
 * LOG: Fix transports on Solaris.  Add dependency computation to Makefile.
 * LOG:
 * LOG: Revision 1.3  1998/04/16 17:23:32  mmiers
 * LOG: Ok, not the final baseline.  More work on the transports, first.
 * LOG:
 * LOG: Revision 1.2  1998/04/16 16:59:51  mmiers
 * LOG: Final commit before baseline.
 * LOG:
 * LOG: Revision 1.1  1998/04/16 04:36:21  mmiers
 * LOG: New versions for C++.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_PLUS_PLUS_H
#define ITS_PLUS_PLUS_H

#if !defined(USE_CPLUSPLUS)
#define USE_CPLUSPLUS
#endif

#if defined(WIN32) || defined(HAVE_STD_NAMESPACE)
#define ITS_STD_NAMESPACE
#else
#define std
#endif

#if defined(WIN32) || defined(HAVE_NAMESPACES)
#define ITS_NAMESPACE
#endif

#if defined(WIN32) || defined(HAVE_STL)
#define ITS_STL_PRESENT
#endif

#if defined(HAVE_THROW_SPECS)
#define ITS_THROW_SPEC_NULL    throw()
#define ITS_THROW_SPEC(x)      throw(x)
#else
#define ITS_THROW_SPEC_NULL
#define ITS_THROW_SPEC(x)
#endif

#if defined(WIN32)
/* shut up, compiler */
#pragma warning(disable:4786) 
#endif

#include <its.h>

#include <string.h>

#include <vector>

#ident "$Id: its++.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*
 * this will see common use
 */
typedef std::vector<ITS_OCTET>  ByteArray;

#if !defined(DONT_INCLUDE_ITS_EVENT)

/*.interface:Event
 *****************************************************************************
 *  Interface:
 *      Event
 *
 *  Purpose:
 *      The Event is the heart of the C++ interface to IntelliSS7.  All
 *      intertask and interprocess indications are passed between entities
 *      in the Event structure.  The class wrappers the C structure
 *      ITS_EVENT, which defines the basic structure of an indication.
 *
 *  Usage:
 *      User code should use objects of this class when receiving events
 *      (normally via ITS_Transport::GetEvent()).
 *      Users should not (in general) create Events for transmitting
 *      information; all IntelliSS7 APIs provide routines for building
 *      and sending Events, as the internal structure of the ITS_EVENT
 *      is not documented.
 *
 *****************************************************************************/
class Event
{
public:
    /* constructors */
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      The default constructor for Events should be used by most
     *      user code.  This constructor builds an Event with all
     *      members set to a predefined state.
     *
     *  Input Parameters:
     *      None.
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
    Event()
    {
        event.src = 0;
        event.len = 0;
        event.data = NULL;
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This constructor for Events is used by most internal
     *      IntelliSS7 code to build an Event for transmission.
     *      While it can be invoked by user code, it's use is not
     *      recommended.
     *
     *  Input Parameters:
     *      src - a transport identifier.  Indicates the *originating*
     *          transport of an event.
     *      len - the length of the data portion of this event.
     *      data - the data payload to be carried by this event.
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
    Event(const ITS_USHORT src, const ITS_USHORT len,
          const ITS_OCTET *data)
    {
        event.src = src;
        event.len = len;
        event.data = (ITS_OCTET *)ITS_Malloc(len);
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        memcpy(event.data, data, len);
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This constructor for Events is used by most internal
     *      IntelliSS7 code to build an Event for transmission.
     *      While it can be invoked by user code, it's use is not
     *      recommended.
     *
     *  Input Parameters:
     *      src - a transport identifier.  Indicates the *originating*
     *          transport of an event.
     *      len - the length of the data portion of this event.
     *      data - the data payload to be carried by this event.
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
    Event(const ITS_USHORT src, const ByteArray& data)
    {
        event.src = src;
        event.len = (ITS_USHORT)data.size();
        event.data = (ITS_OCTET *)ITS_Malloc(event.len);
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        memcpy(event.data, &data[0], data.size());
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This constructor is used as a copy constructor of the C
     *      ITS_EVENT data type.  It is used most frequently by
     *      IntelliSS7 APIs, but can be invoked by user code.
     *
     *  Input Parameters:
     *      ev - a const pointer to a const ITS_EVENT structure.
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
    Event(const ITS_EVENT* const ev)
    {
        event.src = ev->src;
        event.len = ev->len;
        event.data = (ITS_OCTET *)ITS_Malloc(ev->len);
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        memcpy(event.data, ev->data, ev->len);
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This copy constructor is made available for copying Events.
     *      It is provided for convenience purposes only.
     *
     *  Input Parameters:
     *      None.
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
    Event(const Event& copy)
    {
        event.len = copy.event.len;
        event.src = copy.event.src;
        event.data = (ITS_OCTET *)ITS_Malloc(copy.event.len);
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        memcpy(event.data, copy.event.data, event.len);
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      Default destructor.
     *
     *  Input Parameters:
     *      None.
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
    virtual ~Event()
    {
        if (event.data)
        {
            ITS_Free(event.data);
            event.data = NULL;
        }
    }

    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method provides the user a mechanism for retrieving the
     *      ITS_EVENT data that the Event object wrappers.  It is
     *      used most frequently by user code when the user is interested
     *      in calling C functions or macros that take an ITS_EVENT or
     *      ITS_EVENT pointer.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      A reference to the contained ITS_EVENT.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_EVENT&
    GetEvent()
    {
        return event;
    }

    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method is used to access the source transport identifier
     *      of an event.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      An ITS_USHORT quantity that identifies the transport or
     *      worker that originated this event.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_USHORT
    GetSource() const
    {
        return event.src;
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method provides the means to set the transport/worker
     *      identifier of an event.
     *
     *  Input Parameters:
     *      src - an ITS_USHORT identifying the source of an event.
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
    void
    SetSource(const ITS_USHORT src)
    {
        event.src = src;
    }

    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method returns the length of the data portion of this
     *      event.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      The length of the data as an ITS_USHORT.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_USHORT
    GetLength() const
    {
        return event.len;
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method allows the user to set the length of the data
     *      portion of an event.
     *
     *  Input Parameters:
     *      None.
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
    void
    SetLength(const ITS_USHORT len)
    {
        event.len = len;
    }

    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method returns a pointer to the start of data in this
     *      event.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      A pointer to the data portion of the event.
     *
     *  Notes:
     *      Because the return value is a pointer into this event, it can
     *      be used by code that wishes to modify the contents of the data.
     *
     *  See Also:
     ************************************************************************/
    const ITS_OCTET*
    GetData() const
    {
        return event.data;
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method provides an interface to set the data portion
     *      of an event.
     *
     *  Input Parameters:
     *      None.
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
    void
    SetData(const ITS_OCTET* data, int len)
    {
        if (event.data)
        {
            ITS_Free(event.data);
        }
        event.data = (ITS_OCTET *)ITS_Malloc(len);
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        event.len = (ITS_USHORT)len;
        memcpy(event.data, data, len);
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method returns a vector containing the data in this event.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      data - a vector containing the event contents.
     *
     *  Return Value:
     *      A pointer to the data portion of the event.
     *
     *  Notes:
     *      Because the return value is a pointer into this event, it can
     *      be used by code that wishes to modify the contents of the data.
     *
     *  See Also:
     ************************************************************************/
    void
    GetData(ByteArray& data) const
    {
        data.erase(data.begin(), data.end());

        data.assign(&event.data[0], &event.data[event.len]);
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method provides an interface to set the data portion
     *      of an event.
     *
     *  Input Parameters:
     *      None.
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
    void
    SetData(const ByteArray& data)
    {
        if (event.data)
        {
            ITS_Free(event.data);
        }
        event.data = (ITS_OCTET *)ITS_Malloc(data.size());
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        event.len = (ITS_USHORT)data.size();
        memcpy(event.data, &data[0], data.size());
    }

    /* operators */
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method implements the assignment operator for Events.
     *
     *  Input Parameters:
     *      copy - a reference to the event to copy.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      A reference to the event that was the LHS of the assignment
     *      operator.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    Event&
    operator=(const Event& copy)
    {
        if (event.data)
        {
            ITS_Free(event.data);
        }
        event.data = (ITS_OCTET *)ITS_Malloc(copy.event.len);
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        event.len = copy.event.len;
        event.src = copy.event.src;
        memcpy(event.data, copy.event.data, event.len);

        return (*this);
    }
    /*.implementation:public,inline,Event
     ************************************************************************
     *  Purpose:
     *      This method provides the user with the ability to assign
     *      the ITS_EVENT C strscture to an instance of the Event class.
     *
     *  Input Parameters:
     *      copy - a reference to an ITS_EVENT structure.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      A reference to the Event that was the LHS of this assignment
     *      operation.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    Event&
    operator=(const ITS_EVENT& copy)
    {
        if (event.data)
        {
            ITS_Free(event.data);
        }
        event.data = (ITS_OCTET *)ITS_Malloc(copy.len);
        if (event.data == NULL)
        {
            throw std::bad_alloc();
        }

        event.len = copy.len;
        event.src = copy.src;
        memcpy(event.data, copy.data, event.len);

        return (*this);
    }

protected:
    ITS_EVENT event;
};

#endif /* DONT_INCLUDE_ITS_EVENT */

#if defined(ITS_NAMESPACE)
}
#endif

/*
 * Get the backward compatibility typedefs (for now)
 */
#include <its_bc.h>

#endif /* ITS_PLUSPLUS_H */
