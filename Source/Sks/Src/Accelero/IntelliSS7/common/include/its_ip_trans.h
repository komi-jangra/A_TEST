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
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:47  cvsadmin
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
 * LOG: Revision 3.10  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.7  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.6  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.5  2001/02/02 21:32:00  hxing
 * LOG: add functions
 * LOG:
 * LOG: Revision 3.4  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2001/01/15 17:36:33  mmiers
 * LOG: Bug fixes from Olivier
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:17  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.9  2000/06/23 22:30:57  rsonak
 * LOG:
 * LOG: Swapped the mask and instance
 * LOG:
 * LOG: Revision 2.8  2000/06/02 17:18:10  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 2.7  2000/02/08 18:23:22  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up RUDP.  Now to test this mess.
 * LOG:
 * LOG: Revision 2.6  2000/02/02 02:29:22  mmiers
 * LOG:
 * LOG:
 * LOG: Add a find method (mostly for RUDP).
 * LOG:
 * LOG: Revision 2.5  2000/02/01 21:29:23  mmiers
 * LOG:
 * LOG:
 * LOG: Some updates for specific features.
 * LOG:
 * LOG: Revision 2.4  2000/01/25 03:05:30  mmiers
 * LOG:
 * LOG:
 * LOG: Let the user add virtual transports.
 * LOG:
 * LOG: Revision 2.3  2000/01/24 23:13:49  mmiers
 * LOG:
 * LOG:
 * LOG: Start integrating.
 * LOG:
 * LOG: Revision 2.2  2000/01/24 22:19:20  mmiers
 * LOG:
 * LOG:
 * LOG: Add UDP style transports.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:52:35  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:39  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.30  1999/11/10 18:27:18  mmiers
 * LOG:
 * LOG:
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.29  1999/11/10 00:09:26  mmiers
 * LOG:
 * LOG:
 * LOG: In goes the mods.
 * LOG:
 * LOG: Revision 1.28  1999/10/25 18:28:09  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.27  1999/10/14 15:38:35  mmiers
 * LOG:
 * LOG:
 * LOG: Remove memory leaks from socket creation.  Publish
 * LOG: ReConnect/ReAccept APIs.
 * LOG:
 * LOG: Revision 1.26  1999/09/09 23:00:38  mmiers
 * LOG:
 * LOG:
 * LOG: Add retry count and retry delay as configuration items.
 * LOG:
 * LOG: Revision 1.25  1999/09/01 00:53:29  mmiers
 * LOG:
 * LOG:
 * LOG: This work makes the transport system a little more sane.  What I
 * LOG: did was make the ITS_Transport class implement the default behavior
 * LOG: for transports, which should make things like:
 * LOG:     ITS_Transport tc = transport->GetTC();
 * LOG: work when you say
 * LOG:     tc.GetNextEvent(ev);
 * LOG:
 * LOG: Revision 1.24  1999/07/29 02:11:41  mmiers
 * LOG:
 * LOG:
 * LOG: Correct build errors after addressing Hubert's comments.
 * LOG:
 * LOG: Revision 1.23  1999/07/29 01:58:18  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the first round of addressing Hubert's review comments.
 * LOG:
 * LOG: Revision 1.22  1999/06/29 01:28:53  mmiers
 * LOG:
 * LOG:
 * LOG: Portability changes.
 * LOG:
 * LOG: Revision 1.21  1999/06/25 16:06:43  mmiers
 * LOG:
 * LOG:
 * LOG: Rework the berkeley sockets transport classes a little.  Required
 * LOG: modification to the Accept() method to create a transport correctly.
 * LOG:
 * LOG: Revision 1.20  1999/06/23 21:21:18  rsonak
 * LOG:
 * LOG:
 * LOG: Rework the iterative/dynamic socket server (more tightly coupled
 * LOG: with infrastructure).
 * LOG:
 * LOG: Revision 1.19  1999/06/23 16:22:14  rsonak
 * LOG:
 * LOG: C++ support for Iterative transport
 * LOG:
 * LOG: Revision 1.18  1999/06/15 16:15:16  rsonak
 * LOG:
 * LOG: DynamicServerTransport modified
 * LOG:
 * LOG: Revision 1.17  1999/06/15 15:09:48  rsonak
 * LOG:
 * LOG: Added Iterative and Dyanmic transports
 * LOG:
 * LOG: Revision 1.16  1998/11/19 00:36:18  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.15  1998/11/05 16:52:13  mmiers
 * LOG: Add in transport pause/resume.
 * LOG: Add reconnect to sockets.
 * LOG:
 * LOG: Revision 1.14  1998/09/22 16:01:24  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.13  1998/06/26 14:30:38  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.12  1998/06/18 03:29:14  mmiers
 * LOG: Create the task queue transport type.
 * LOG:
 * LOG: Revision 1.11  1998/06/18 03:10:07  mmiers
 * LOG: Build on Solaris.  Right now, the NT build is not OK.
 * LOG:
 * LOG: Revision 1.10  1998/06/18 01:02:41  mmiers
 * LOG: More "C" style transports.
 * LOG:
 * LOG: Revision 1.9  1998/06/02 19:43:14  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.8  1998/06/01 16:35:16  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.7  1998/05/31 02:59:39  mmiers
 * LOG: More documenation, stabilizing the interfaces.
 * LOG:
 * LOG: Revision 1.6  1998/05/29 22:35:36  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.5  1998/05/29 15:08:57  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.4  1998/05/29 03:31:30  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.3  1998/05/19 17:11:46  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.2  1998/05/01 00:24:32  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 22:20:04  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_IP_TRANS_H
#define ITS_IP_TRANS_H

#include <its.h>
#include <its_mutex.h>
#include <its_transports.h>
#include <its_sockets.h>
#include <its_worker.h>

#ident "$Id: its_ip_trans.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if !defined(ITS_SOCK_TRANS_ONESHOT)
#define ITS_SOCK_TRANS_ONESHOT

/*
 * resource strings
 */
#define SOCKET_DOMAIN_STRING    "socketDomain"          /* "INET" or "UNIX" */
# define DOMAIN_INET_STRING     "INET"
# define DOMAIN_UNIX_STRING     "UNIX"
#define SERVER_PATH_STRING      "serverHostName"        /* any valid host name */
#define SERVER_PORT_STRING      "serverPort"            /* any valid port number */
#define RETRY_COUNT_STRING      "retryCount"
#define RETRY_DELAY_STRING      "retryDelay"

#define DEFAULT_RETRY_DELAY     10U
#define DEFAULT_RETRY_COUNT     5

/*
 * used by UDP transports
 */
#define LOCAL_HOST_NAME_STRING  "localHostName"
#define LOCAL_PORT_STRING       "localPort"
#define ASSOC_TRID_NAME_STRING  "associateName"
#define ASSOC_TRID_INST_STRING  "associateInstance"
#define ASSOC_TRID_MASK_STRING  "associateMask"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * a socket transport in "C"
 */
typedef struct
{
    ITS_SocketInfo      *source;
    ITS_SocketInfo      *connect;
    TRANSPORT_Control   **remotes;
    ITS_USHORT          remoteCount;
    ITS_USHORT          remoteMax;
    ITS_SOCK_DOMAIN     domain;
    char                *host_or_path;
    int                 port;
    ITS_MUTEX           rmutex;
    ITS_MUTEX           wmutex;
    volatile ITS_TIME   retryDelay;
    volatile int        retryCount;
    ITS_BOOLEAN         isValid;
    ITS_UINT            rwTimeout;
    TRANSPORT_EventProc ReadEvent;
    TRANSPORT_EventProc WriteEvent;
}
SOCKTRAN_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SOCKTRAN_ObjectPart     socket;
}
SOCKTRAN_Manager;

#define SOCKTRAN_SOURCE(x) \
    (((SOCKTRAN_Manager *)(x))->socket.source)

#define SOCKTRAN_CONNECT(x) \
    (((SOCKTRAN_Manager *)(x))->socket.connect)

#define SOCKTRAN_DOMAIN(x) \
    (((SOCKTRAN_Manager *)(x))->socket.domain)

#define SOCKTRAN_HOST_PATH(x) \
    (((SOCKTRAN_Manager *)(x))->socket.host_or_path)

#define SOCKTRAN_PORT(x) \
    (((SOCKTRAN_Manager *)(x))->socket.port)

#define SOCKTRAN_RMUTEX(x) \
    (((SOCKTRAN_Manager *)(x))->socket.rmutex)

#define SOCKTRAN_WMUTEX(x) \
    (((SOCKTRAN_Manager *)(x))->socket.wmutex)

#define SOCKTRAN_RETRY_DELAY(x) \
    (((SOCKTRAN_Manager *)(x))->socket.retryDelay)

#define SOCKTRAN_RETRY_COUNT(x) \
    (((SOCKTRAN_Manager *)(x))->socket.retryCount)

#define SOCKTRAN_IS_VALID(x) \
    (((SOCKTRAN_Manager *)(x))->socket.isValid)

#define SOCKTRAN_REMOTES(x) \
    (((SOCKTRAN_Manager *)(x))->socket.remotes)

#define SOCKTRAN_REMOTE_COUNT(x) \
    (((SOCKTRAN_Manager *)(x))->socket.remoteCount)

#define SOCKTRAN_REMOTE_MAX(x) \
    (((SOCKTRAN_Manager *)(x))->socket.remoteMax)

#define SOCKTRAN_RW_TIMEOUT(x) \
    (((SOCKTRAN_Manager *)(x))->socket.rwTimeout)

#define SOCKTRAN_READ_EVENT(x) \
    (((SOCKTRAN_Manager *)(x))->socket.ReadEvent)

#define SOCKTRAN_WRITE_EVENT(x) \
    (((SOCKTRAN_Manager *)(x))->socket.WriteEvent)

/*
 * this is easier to handle if subs can use the supers,
 * especially at times the super doesn't know about (timer
 * expiry is a good example).
 */
typedef void    (*SOCKTRAN_StartStopProc)(SOCKTRAN_Manager *);

#define SOCKTRAN_CLASS_RESTART_INHERIT  (SOCKTRAN_StartStopProc)NULL
#define SOCKTRAN_CLASS_SHUTDOWN_INHERIT (SOCKTRAN_StartStopProc)NULL

typedef struct
{
    SOCKTRAN_StartStopProc  shutdown;
    SOCKTRAN_StartStopProc  restart;
}
SOCKTRAN_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    TRANSPORT_ClassPart transportClass;
    SOCKTRAN_ClassPart  socktranClass;
}
SOCKTRAN_ClassRec, *SOCKTRAN_Class;

#define SOCKTRAN_CLASS_SHUTDOWN(x) \
    (((SOCKTRAN_Class)(x))->socktranClass.shutdown)

#define SOCKTRAN_CLASS_RESTART(x) \
    (((SOCKTRAN_Class)(x))->socktranClass.restart)

/*
 * we need to use the extension field so that
 * subclasses can overwrite the send/receive
 * methods
 */
typedef struct
{
    TRANSPORT_EventProc ReadEvent;
    TRANSPORT_EventProc WriteEvent;
    SOCKTRAN_Class      AssociatedClass;
}
SOCKTRAN_ClassExtPart;

typedef struct
{
    ITS_CoreClassExtPart    coreClass;
    SOCKTRAN_ClassExtPart   socktranClass;
}
SOCKTRAN_ClassExtRec, *SOCKTRAN_ClassExtension;

#define SOCKTRAN_CLASS_EXT_READ_EVENT(c) \
    (((SOCKTRAN_ClassExtension)ITS_CLASS_EXTENSION(c))->socktranClass.ReadEvent)

#define SOCKTRAN_CLASS_EXT_WRITE_EVENT(c) \
    (((SOCKTRAN_ClassExtension)ITS_CLASS_EXTENSION(c))->socktranClass.WriteEvent)

#define SOCKTRAN_CLASS_EXT_ASSOCIATE(c) \
    (((SOCKTRAN_ClassExtension)ITS_CLASS_EXTENSION(c))->socktranClass.AssociatedClass)

#define SOCKTRAN_CLIENT_CLASS_NAME          "SOCKTRAN_CLIENT"
#define SOCKTRAN_SERVER_CLASS_NAME          "SOCKTRAN_SERVER"
#define SOCKTRAN_ITERATIVE_CLASS_NAME       "SOCKTRAN_ITERATIVE"
#define SOCKTRAN_DYNAMIC_CLASS_NAME         "SOCKTRAN_DYNAMIC"
#define SOCKTRAN_LOCAL_ENDPOINT_CLASS_NAME  "SOCKTRAN_LOCAL_ENDPOINT"
#define SOCKTRAN_REMOTE_ENDPOINT_CLASS_NAME "SOCKTRAN_REMOTE_ENDPOINT"

ITSDLLAPI extern SOCKTRAN_ClassRec    itsSOCKTRAN_ClientClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSOCKTRAN_ClientClass;
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSOCKTRAN_ServerClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSOCKTRAN_ServerClass;
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSOCKTRAN_IterativeServerClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSOCKTRAN_IterativeServerClass;
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSOCKTRAN_DynamicServerClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSOCKTRAN_DynamicServerClass;
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSOCKTRAN_LocalEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSOCKTRAN_LocalEndPointClass;
ITSDLLAPI extern SOCKTRAN_ClassRec    itsSOCKTRAN_RemoteEndPointClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSOCKTRAN_RemoteEndPointClass;

ITSDLLAPI SOCKTRAN_Manager* SOCKTRAN_CreateClientTransport(const char *name,
                                                           ITS_USHORT instance,
                                                           ITS_UINT mask);
ITSDLLAPI void SOCKTRAN_DeleteClientTransport(SOCKTRAN_Manager *ft);
ITSDLLAPI int SOCKTRAN_ClientReConnect(SOCKTRAN_Manager *ft);

ITSDLLAPI SOCKTRAN_Manager* SOCKTRAN_CreateServerTransport(const char *name,
                                                           ITS_USHORT instance,
                                                           ITS_UINT mask);
ITSDLLAPI void SOCKTRAN_DeleteServerTransport(SOCKTRAN_Manager *ft);

ITSDLLAPI SOCKTRAN_Manager* SOCKTRAN_IterativeAccept(SOCKTRAN_Manager *sm,
                                                     const char *name,
                                                     ITS_USHORT newInstance,
                                                     ITS_UINT newMask);
ITSDLLAPI int SOCKTRAN_ServerReAccept(SOCKTRAN_Manager *ft);

ITSDLLAPI SOCKTRAN_Manager* SOCKTRAN_CreateEndPointTransport(const char *name,
                                                             ITS_USHORT instance,
                                                             ITS_UINT mask);
ITSDLLAPI void SOCKTRAN_DeleteEndPointTransport(SOCKTRAN_Manager *st);

ITSDLLAPI int SOCKTRAN_EndPointAddVirtualTransport(SOCKTRAN_Manager *st, const char *name,
                                                   ITS_USHORT instance, ITS_UINT mask);
ITSDLLAPI int SOCKTRAN_EndPointRemVirtualTransport(SOCKTRAN_Manager *st,
                                                   ITS_USHORT instance);
ITSDLLAPI TRANSPORT_Control * SOCKTRAN_EndPointFindVirtualTransport(SOCKTRAN_Manager *st,
                                                                    ITS_USHORT index);

#if defined(__cplusplus)
}
#endif

#endif /* ITS_SOCK_TRANS_ONESHOT */

#if defined (USE_CPLUSPLUS)

#include <string>

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*
 * socket connections
 */
/*.interface:ClientTransport
 *****************************************************************************
 *  Interface:
 *      ClientTransport
 *
 *  Purpose:
 *      The ClientTransport is simply a transport implemented via
 *      a gated client socket.  It implements no additional functionality
 *      beyond that of the Transport class.  See:
 *      <A HREF=its_transport.html>Transport</A>
 *      for additional information.
 *
 *  Usage:
 *      See Transport for usage.
 *
 *      The resource file is expected to contain the variables
 *      SOCKET_DOMAIN
 *      SERVER_HOST_NAME
 *      and
 *      SERVER_PORT
 *
 *      The SOCKET_DOMAIN is either UNIX or INET.  Note that only INET
 *      is portable.  SERVER_HOST_NAME and SERVER_PORT together identify
 *      the socket to connect to.
 *
 *****************************************************************************/
class ClientTransport : public Transport
{
public:
    explicit ClientTransport(TRANSPORT_Control *tc)
        : Transport(tc)
    {
    }
    /*.implementation:public,inline,ClientTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a socket based transport.  Note that this
     *      routine will block until the server side is available.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for host and port information for
     *      the socket
     *
     *  See Also:
     *      ~ClientTransport
     ************************************************************************/
    ClientTransport(const char *name,
                    ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
                   (SOCKTRAN_CreateClientTransport(const_cast<char *>(name),
                                                   instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,ClientTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a socket based transport.  Note that this
     *      routine will block until the server side is available.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for host and port information for
     *      the socket
     *
     *  See Also:
     *      ~ClientTransport
     ************************************************************************/
    ClientTransport(const std::string& name,
                    ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (SOCKTRAN_CreateClientTransport(const_cast<char *>(name.c_str()),
                                             instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,ClientTransport
     ************************************************************************
     *  Purpose:
     *      This method destroys a socket transport.
     *
     *  See Also:
     *      ClientTransport()
     ************************************************************************/
    virtual ~ClientTransport()
    {
        if (tc)
        {
            SOCKTRAN_DeleteClientTransport(
                reinterpret_cast<SOCKTRAN_Manager *>(tc));
        }
    }

    /*.implementation:public,inline,ClientTransport
     ************************************************************************
     *  Purpose:
     *      This method reconnects to the server.
     *
     *  Return Value:
     *      ITS_SUCCESS - reconnect successful
     *
     ************************************************************************/
    int ReConnect()
    {
        return SOCKTRAN_ClientReConnect(reinterpret_cast<SOCKTRAN_Manager*>(tc));
    }


private:
    /* sorry, no copying */
    ClientTransport& operator=(Transport&) { return *this; }
};

/*.interface:ServerTransport
 *****************************************************************************
 *  Interface:
 *      ServerTransport
 *
 *  Purpose:
 *      The ServerTransport is simply a transport implemented via
 *      a gated server socket.  It implements no additional functionality
 *      beyond that of the Transport class.  See:
 *      <A HREF=its_transport.html>Transport</A>
 *      for additional information.
 *
 *  Usage:
 *      See Transport for usage.
 *
 *      The resource file is expected to contain the variables
 *      SOCKET_DOMAIN
 *      SERVER_HOST_NAME
 *      and
 *      SERVER_PORT
 *
 *      The SOCKET_DOMAIN is either UNIX or INET.  Note that only INET
 *      is portable.  SERVER_HOST_NAME and SERVER_PORT together identify
 *      the socket to listen and accept on.
 *
 *****************************************************************************/
class ServerTransport : public Transport
{
public:
    explicit ServerTransport(TRANSPORT_Control *tc)
        : Transport(tc)
    {
    }
    /*.implementation:public,inline,ServerTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a socket based transport.  Note that this
     *      routine will block until the client side connects.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for host and port information for
     *      the socket
     *
     *  See Also:
     *      ~ServerTransport
     ************************************************************************/
    ServerTransport(const char *name,
                    ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        if (ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SSOCKET_DYN)
        {
            tc = (TRANSPORT_Control *)TRANSPORT_FindTransport(instance);

            if (tc == NULL)
            {
                throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
            }
        }
        else
        {
            tc = reinterpret_cast<TRANSPORT_Control *>
                 (SOCKTRAN_CreateServerTransport(const_cast<char *>(name),
                                                 instance, mask));

            if (tc == NULL)
            {
                throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
            }
        }
    }
    /*.implementation:public,inline,ServerTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a socket based transport.  Note that this
     *      routine will block until the client side connects.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for host and port information for
     *      the socket
     *
     *  See Also:
     *      ~ServerTransport
     ************************************************************************/
    ServerTransport(const std::string& name,
                    ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        if (ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SSOCKET_DYN)
        {
            tc = (TRANSPORT_Control *)TRANSPORT_FindTransport(instance);

            if (tc == NULL)
            {
                throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
            }
        }
        else
        {
            tc = reinterpret_cast<TRANSPORT_Control *>
                 (SOCKTRAN_CreateServerTransport(const_cast<char *>(name.c_str()),
                                                 instance, mask));

            if (tc == NULL)
            {
                throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
            }
        }
    }
    /*.implementation:public,inline,ServerTransport
     ************************************************************************
     *  Purpose:
     *      This method destroys a socket transport.
     *
     *  See Also:
     *      ServerTransport()
     ************************************************************************/
    virtual ~ServerTransport()
    {
        if (tc)
        {
            SOCKTRAN_DeleteServerTransport(
                reinterpret_cast<SOCKTRAN_Manager *>(tc));
        }
    }

    /*.implementation:public,inline,ServerTransport
     ************************************************************************
     *  Purpose:
     *      This method is an accept call for the Iterative Transport. 
     *      After it accepts a connection, it creates a
     *      DynamicServerTransport which now deals with this particular
     *      session. 
     *
     *  Input Parameters:
     *      name - accepted's name
     *      newInstance - accepted's instance
     *      newMask - accepted's mask
     *
     *  Return Value:
     *      handle of the accepted's transport or NULL on error.
     *      
     ************************************************************************/
    virtual ITS_HANDLE
    IterativeAccept(const char *name,
                    ITS_USHORT newInstance,
                    ITS_UINT newMask)
    {
        return SOCKTRAN_IterativeAccept(reinterpret_cast<SOCKTRAN_Manager*>(tc),
                                        const_cast<char *>(name),
                                        newInstance, newMask);
    }
    /*.implementation:public,inline,ServerTransport
     ************************************************************************
     *  Purpose:
     *      This method is an accept call for the Iterative Transport. 
     *      After it accepts a connection, it creates a
     *      DynamicServerTransport which now deals with this particular
     *      session. 
     *
     *  Input Parameters:
     *      name - accepted's name
     *      newInstance - accepted's instance
     *      newMask - accepted's mask
     *
     *  Return Value:
     *      handle of the accepted's transport or NULL on error.
     *      
     ************************************************************************/
    virtual ITS_HANDLE
    IterativeAccept(const std::string& name,
                    ITS_USHORT newInstance,
                    ITS_UINT newMask)
    {
        return IterativeAccept(name.c_str(), newInstance, newMask);
    }

    /*.implementation:public,inline,ServerTransport
     ************************************************************************
     *  Purpose:
     *      This method allows for a server to re-accept a client's
     *      connection.
     *
     ************************************************************************/
    int ReAccept()
    {
        return SOCKTRAN_ServerReAccept(reinterpret_cast<SOCKTRAN_Manager*>(tc));
    }

private:
    /* sorry, no copying */
    ServerTransport& operator=(Transport&) { return *this; }
};

/*.interface:EndPointTransport
 *****************************************************************************
 *  Interface:
 *      EndPointTransport
 *
 *  Purpose:
 *      The EndPointTransport is simply a transport implemented via
 *      a gated UDP socket.  It implements no additional functionality
 *      beyond that of the Transport class.  See:
 *      <A HREF=its_transport.html>Transport</A>
 *      for additional information.
 *
 *  Usage:
 *      See Transport for usage.
 *
 *      The resource file is expected to contain the variables
 *      LOCAL_HOST_NAME
 *      and
 *      LOCAL_PORT
 *
 *      LOCAL_HOST_NAME and LOCAL_PORT together identify the local end
 *      point address.  Additional "virtual" transports should be specified
 *      in the INI file as well, via 
 *      ASSOCIATED_TRID_NAME,
 *      ASSOCIATED_TRID_MASK,
 *      and
 *      ASSOCIATED_TRID_INSTANCE.
 *
 *      These fields describe a virtual transport that will be created for
 *      routing purposes.  The EndPoint created will be used for reading;
 *      the virtual transports are used for writing.
 *
 *****************************************************************************/
class EndPointTransport : public Transport
{
public:
    explicit EndPointTransport(TRANSPORT_Control *tc)
        : Transport(tc)
    {
    }
    /*.implementation:public,inline,EndPointTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a socket based transport.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for host and port information for
     *      the socket
     *
     *  See Also:
     *      ~EndPointTransport
     ************************************************************************/
    EndPointTransport(const char *name,
                      ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (SOCKTRAN_CreateEndPointTransport(const_cast<char *>(name),
                                               instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,EndPointTransport
     ************************************************************************
     *  Purpose:
     *      This method creates a socket based transport.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for host and port information for
     *      the socket
     *
     *  See Also:
     *      ~EndPointTransport
     ************************************************************************/
    EndPointTransport(const std::string& name,
                      ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (SOCKTRAN_CreateEndPointTransport(const_cast<char *>(name.c_str()),
                                               instance, mask));

        if (tc == NULL)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,EndPointTransport
     ************************************************************************
     *  Purpose:
     *      This method destroys a socket transport.
     *
     *  See Also:
     *      EndPointTransport()
     ************************************************************************/
    virtual ~EndPointTransport()
    {
        if (tc)
        {
            SOCKTRAN_DeleteEndPointTransport(reinterpret_cast<SOCKTRAN_Manager *>(tc));
        }
    }

    /*.implementation:public,inline,EndPointTransport
     ************************************************************************
     *  Purpose:
     *      This method adds a virtual transport to an EndPoint transport
     *
     *  Input Parameters:
     *      name - the transport name
     *      instance - the transport instance
     *      mask - the transport mask
     *
     *  See Also:
     *      EndPointTransport()
     ************************************************************************/
    int
    AddVirtualTransport(const char *name,
                        ITS_USHORT instance, ITS_UINT mask)
    {
        return SOCKTRAN_EndPointAddVirtualTransport((SOCKTRAN_Manager *)this->tc,
                                                    name, instance, mask);
    }
    /*.implementation:public,inline,EndPointTransport
     ************************************************************************
     *  Purpose:
     *      This method adds a virtual transport to an EndPoint transport
     *
     *  Input Parameters:
     *      name - the transport name
     *      instance - the transport instance
     *      mask - the transport mask
     *
     ************************************************************************/
    int
    AddVirtualTransport(const std::string& name,
                        ITS_USHORT instance, ITS_UINT mask)
    {
        return AddVirtualTransport(name.c_str(), instance, mask);
    }

    /*.implementation:public,inline,EndPointTransport
     ************************************************************************
     *  Purpose:
     *      This method removes a virtual transport from an EndPoint transport
     *
     *  Input Parameters:
     *      name - the transport name
     *      instance - the transport instance
     *
     ************************************************************************/
    int
    RemVirtualTransport(ITS_USHORT instance)
    {
        return SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)this->tc,
                                                    instance);
    }
    /*.implementation:public,inline,EndPointTransport
     ************************************************************************
     *  Purpose:
     *      This method finds a virtual transport in an EndPoint transport
     *
     *  Input Parameters:
     *      name - the transport name
     *      index - the transport index
     *
     *  Return Value:
     *      HANDLE of the virtual transport.
     *
     ************************************************************************/
    ITS_HANDLE
    FindVirtualTransport(ITS_USHORT instance)
    {
        return (ITS_HANDLE)
                 SOCKTRAN_EndPointFindVirtualTransport((SOCKTRAN_Manager *)this->tc,
                                                       instance);
    }

private:
    /* sorry, no copying */
    EndPointTransport& operator=(Transport&) { return *this; }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_IP_TRANS_H */

