/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 * LOG: Revision 8.2  2005/03/21 13:50:47  cvsadmin
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
 * LOG: Revision 3.1  2000/08/16 00:03:15  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:37  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.10  1998/09/03 18:40:52  hdivoux
 * LOG: Correction: base class destructor now virtual.
 * LOG:
 * LOG: Revision 1.9  1998/06/12 16:42:53  mmiers
 * LOG: Add dual mutexes for sockets and fifos.
 * LOG:
 * LOG: Revision 1.8  1998/06/02 19:43:13  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.7  1998/06/01 16:35:15  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.6  1998/05/31 23:59:10  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.5  1998/05/29 03:31:30  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 17:11:45  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.3  1998/05/14 01:22:42  mmiers
 * LOG: General cleanup.  Remove dead files.  Adjust include comments.
 * LOG:
 * LOG: Revision 1.2  1998/05/01 00:24:30  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/16 04:31:06  mmiers
 * LOG: Add C++ declarations for gated fifos and sockets.
 * LOG:
 *
 *****************************************************************************/

#ifndef ITS_GSOCKETS_H
#define ITS_GSOCKETS_H

#if defined(USE_CPLUSPLUS)

#include <its_sockets.h>
#include <its_mutex.h>
#include <its_exception.h>

#ident "$Id: its_gsockets.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:GatedSocket
 *****************************************************************************
 *  Interface:
 *      GatedSocket
 *
 *  Purpose:
 *      GatedSocket implements a threadsafe socket.  Multiple threads
 *      can communicate via a single socket without worrying about
 *      message corruption.  See:
 *      <A HREF=its_socket.html>Socket</A>
 *      for additional information.
 *
 *  Usage:
 *      Same as Socket
 *
 *****************************************************************************/
class GatedSocket : public Socket
{
public:
    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a new gated socket.  The only addition from
     *      Socket is the creation of a guard mutex.
     *
     *  Notes:
     *      This method can throw exceptions if the mutex cannot be created.
     *
     ************************************************************************/
    GatedSocket()
        : rmutex(NULL), wmutex(NULL)
    {
        try
        {
            rmutex = new Mutex(0);
            wmutex = new Mutex(0);
        }
        catch (ITS_GenericException& iex)
        {
            iex.Log();

            throw iex;
        }
        catch (exception& exc)
        {
            ITS_StandardException standardExc(exc.what(), __FILE__, __LINE__);

            standardExc.Log();

            throw standardExc;
        }
    #if defined(NDEBUG)
        catch (...)
        {
            ITS_UnknownException unknownExc(__FILE__, __LINE__);

            unknownExc.Log();

            throw unknownExc;
        }
    #endif
    }
    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      Destroy a gated socket.
     *
     ************************************************************************/
    virtual ~GatedSocket()
    {
        if (rmutex)
        {
            delete rmutex;
        }
        if (wmutex)
        {
            delete wmutex;
        }
    }
   
    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      Determine if there is data pending on a socket connection.
     *
     *  Return Value:
     *      If the return value is less than zero, an error occured.
     *      If the return value is zero, no data is pending.
     *      A positive return value indicates the number of bytes waiting to be
     *          read.
     *
     ************************************************************************/
    virtual int
    Pending()
    {
        int ret;

        if ((ret = rmutex->Acquire()) != ITS_SUCCESS)
        {
            return ret;
        }

        ret = Socket::Pending();

        rmutex->Release();

        return ret;
    }

    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      This method checks to see if a socket is ready for reading.
     *
     *  Return Value:
     *      If the socket is ready, ITS_TRUE is returned.
     *      ITS_FALSE is returned for errors or not-ready for read.
     *
     ************************************************************************/
    virtual ITS_BOOLEAN
    ReadyToRead()
    {
        int ret;

        if ((ret = rmutex->Acquire()) != ITS_SUCCESS)
        {
            return ret;
        }

        ret = Socket::ReadyToRead();

        rmutex->Release();

        return ret;
    }
 
    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      This method reads data from a gated socket.
     *
     *  Input Parameters:
     *      nbytes - the maximum number of bytes to read
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to fill
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes read.
     *
     ************************************************************************/
    virtual int
    Read(char *buf, int nbytes)
    {
        int ret;

        if ((ret = rmutex->Acquire()) != ITS_SUCCESS)
        {
            return ret;
        }

        ret = Socket::Read(buf, nbytes);

        rmutex->Release();

        return ret;
    }

    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      This method writes data to a gated socket.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to send
     *      nbytes - the maximum number of bytes to write
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes written.
     *
     ************************************************************************/
    virtual int
    Write(char *buf, int nbytes)
    {
        int ret;

        if ((ret = wmutex->Acquire()) != ITS_SUCCESS)
        {
            return ret;
        }

        ret = Socket::Write(buf, nbytes);

        wmutex->Release();

        return ret;
    }

    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      This method attempts to read data from a gated socket without
     *      blocking on the socket.
     *
     *  Input Parameters:
     *      nbytes - the maximum number of bytes to read
     *      timeout - the number of seconds to wait for data before returning on
     *          error
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to fill
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes read.
     *
     ************************************************************************/
    virtual int
    NonBlockingRead(char *buf, int size, int timeout)
    {
        int ret;

        if ((ret = rmutex->Acquire()) != ITS_SUCCESS)
        {
            return ret;
        }

        ret = Socket::NonBlockingRead(buf, size, timeout);

        rmutex->Release();

        return ret;
    }
    /*.implementation:public,inline,GatedSocket
     ************************************************************************
     *  Purpose:
     *      This method writes data to a gated socket.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to send
     *      nbytes - the maximum number of bytes to write
     *      timeout - the number of seconds to wait for writing before returning
     *          on error.
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes written.
     *
     ************************************************************************/
    virtual int
    NonBlockingWrite(char *buf, int size, int timeout)
    {
        int ret;

        if ((ret = wmutex->Acquire()) != ITS_SUCCESS)
        {
            return ret;
        }

        ret = Socket::NonBlockingWrite(buf, size, timeout);

        wmutex->Release();

        return ret;
    }

private:
    /* sorry folks, no copying these */
    GatedSocket(GatedSocket&) {}
    GatedSocket& operator=(GatedSocket&) { return *this; }

    Mutex *rmutex;
    Mutex *wmutex;
};

/*.interface:GatedClientSocket
 *****************************************************************************
 *  Interface:
 *      GatedClientSocket
 *
 *  Purpose:
 *      This class implements client sockets that are immune to message
 *      corruption caused by multithreading.  See:
 *      <A HREF=its_sockets.html>Socket</A>
 *      for additional information.
 *
 *  Usage:
 *      See Socket
 *
 *****************************************************************************/
class GatedClientSocket : public GatedSocket
{
public:
    /*.implementation:public,inline,GatedClientSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a gated client socket
     *
     *  Input Parameters:
     *      domain - either INET or UNIX address families.
     *      host_or_path - the hostname of the server, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the server
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    GatedClientSocket(ITS_SOCK_DOMAIN domain,
                      char *host_or_path, int port)
        : GatedSocket()
    {
        if (SOCK_ClientOpen(&info, domain, host_or_path, port) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,GatedClientSocket
     ************************************************************************
     *  Purpose:
     *      This method destroyes gated client sockets.
     *
     ************************************************************************/
    virtual ~GatedClientSocket()
    {
    }

    /*.implementation:public,inline,GatedClientSocket
     ************************************************************************
     *  Purpose:
     *      This method attempts to connect the gated client socket to the
     *      server.
     *
     *  Return Value:
     *      If the return value is less than zero, an error is returned.
     *      Otherwise, zero indicates success.
     *
     ************************************************************************/
    virtual int
    Connect()
    {
        return SOCK_ClientConnect(info);
    }

private:
    /* sorry folks, no copying these */
    GatedClientSocket() {}
    GatedClientSocket(GatedClientSocket&) {}
    GatedClientSocket& operator=(GatedClientSocket&) { return *this; }
};

/*.interface:GatedServerSocket
 *****************************************************************************
 *  Interface:
 *      GatedServerSocket
 *
 *  Purpose:
 *      This class implements server sockets that are immune to message
 *      corruption caused by multithreading.  See:
 *      <A HREF=its_sockets.html>Socket</A>
 *      for additional information.
 *
 *  Usage:
 *      See Socket
 *
 *****************************************************************************/
class GatedServerSocket : public GatedSocket
{
public:
    /*.implementation:public,inline,GatedServerSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a gated server socket.
     *
     *  Input Parameters:
     *      domain - either INET or UNIX address families.
     *      host_or_path - the hostname of the server, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the server
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    GatedServerSocket(ITS_SOCK_DOMAIN domain,
                      char *host_or_path, int port)
        : GatedSocket()
    {
        if (SOCK_ServerOpen(&info, domain, host_or_path, port) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,GatedServerSocket
     ************************************************************************
     *  Purpose:
     *      This method destroys a gated server socket.
     *
     ************************************************************************/
    virtual ~GatedServerSocket()
    {
    }

    /*.implementation:public,inline,GatedServerSocket
     ************************************************************************
     *  Purpose:
     *      This method accepts a connection on a gated server socket.
     *
     *  Output Parameters:
     *      clone - an GatedSocket containing the new connection
     *
     *  Return Value:
     *      If a new client is successfully accepted, ITS_SUCCESS is returned.
     *      Any other value indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    virtual int
    Accept(GatedSocket** info)
    {
        int ret;
        SocketInfo *tmp = NULL;

        ret = SOCK_ServerAccept(info, &tmp);

        *clone = NULL;

        if (ret == ITS_SUCCESS)
        {
            *clone = new GatedSocket;

            (*clone)->SetSocketInfo(tmp);
        }

        return ret;
    }

private:
    /* sorry folks, no copying these */
    GatedServerSocket() {}
    GatedServerSocket(GatedServerSocket&) {}
    GatedServerSocket& operator=(GatedServerSocket&) { return *this; }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_GSOCKETS_H */
