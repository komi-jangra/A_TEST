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
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
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
 * LOG: Revision 3.1  2000/08/16 00:03:14  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:37  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1998/11/19 00:36:18  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.7  1998/06/12 16:42:53  mmiers
 * LOG: Add dual mutexes for sockets and fifos.
 * LOG:
 * LOG: Revision 1.6  1998/06/01 16:35:14  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.5  1998/05/29 03:31:29  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.4  1998/05/27 02:18:12  mmiers
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
 * LOG: Revision 1.1  1998/04/16 04:31:06  mmiers
 * LOG: Add C++ declarations for gated fifos and sockets.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_GFIFO_H
#define ITS_GFIFO_H

#if defined (USE_CPLUSPLUS)

#include <its_fifo.h>
#include <its_mutex.h>
#include <its_exception.h>

#ident "$Id: its_gfifo.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:GatedFifo
 *****************************************************************************
 *  Interface:
 *      GatedFifo
 *
 *  Purpose:
 *      This class is intended for those platforms that do not support
 *      thread-safe fifos (i.e., where fifos are implemented as byte
 *      streams).
 *
 *  Usage:
 *      Usage is exactly as Fifo.  See
 *      <A HREF=its_fifo.html>Fifo</A>
 *      for details.
 *
 *****************************************************************************/
class GatedFifo : public Fifo
{
public:
    /*.implementation:public,inline,GatedFifo
     ************************************************************************
     *  Purpose:
     *      This method creates (at least) one end of a FIFO transport, and
     *      connects to the other end of said transport.  In this way a
     *      bidirectional data path is created, where one FIFO is read only,
     *      and the other FIFO is write only.  The read only fifo is local;
     *      the write only FIFO is the pipe to the other end.
     *
     *      In addition, this method creates a mutex to serialize access to this
     *      fifo.  This is necessary on those platforms that only support
     *      byte-stream fifos and not message based fifos.
     *
     *  Input Parameters:
     *      _name - the path name of the basic transport involved.
     *
     *  Notes:
     *      If for whatever reason one end of the FIFO cannot be created, this
     *      method may issue an exception.
     *
     *  See Also:
     *      ~GatedFifo()
     ************************************************************************/
    GatedFifo(char *client, char *server)
        : Fifo(client, server), rmutex(NULL), wmutex(NULL)
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
    /*.implementation:public,inline,GatedFifo
     ************************************************************************
     *  Purpose:
     *      This method destroys a FIFO transport.  Note that the release of the
     *      individual components of the transport may be delayed until both
     *      ends of the FIFO transport have released their resources.
     *
     *      In addition, this method destroys the mutex guard associated with
     *      this gated fifo.
     *
     *  See Also:
     *      GatedFifo()
     ************************************************************************/
    virtual ~GatedFifo()
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

    /*.implementation:public,inline,GatedFifo
     ************************************************************************
     *  Purpose:
     *      This method reads one message from the READER side of a FIFO transport.
     *      Serialization for the read is ensured by the mutex guard.
     *
     *  Input Parameters:
     *      buf - the data buffer to copy incoming information into.
     *      size - the maximum size of the message to be read.
     *
     *  Return Value:
     *      On success, ITS_SUCCESS is returned.
     *      Any other return code indicates that an IntelliSS7 error occurred.
     *
     *  See Also:
     *      Write()
     ************************************************************************/
    virtual int
    Read(char *buf, int size)
    {
        int ret;

        if ((ret = rmutex->Acquire()) != ITS_SUCCESS)
        {
            return (ret);
        }

        ret = Fifo::Read(buf, size);

        rmutex->Release();

        return ret;
    }
    /*.implementation:public,inline,GatedFifo
     ************************************************************************
     *  Purpose:
     *      This method writes a message onto the WRITER side of the FIFO
     *      transport.
     *
     *  Input Parameters:
     *      buf - the data buffer to copy outgoing information from.
     *      size - the maximum size of the message to be written.
     *
     *  Return Value:
     *      On success, ITS_SUCCESS is returned.
     *      Any other return code indicates that an IntelliSS7 error occurred.
     *
     *  See Also:
     *      Read()
     ************************************************************************/
    virtual int
    Write(char *buf, int size)
    {
        int ret;

        if ((ret = wmutex->Acquire()) != ITS_SUCCESS)
        {
            return (ret);
        }

        ret = Fifo::Write(buf, size);

        wmutex->Release();

        return ret;
    }

private:
    /* sorry folks, no copying these */
    GatedFifo& operator=(GatedFifo&) { return *this; }

    Mutex *rmutex;
    Mutex *wmutex;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_GFIFO_H */
