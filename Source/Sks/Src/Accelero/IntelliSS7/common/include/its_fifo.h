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
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
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
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
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
 * LOG: Revision 3.1  2000/08/16 00:03:12  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:57  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:34  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.19  1998/11/19 00:36:17  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.18  1998/11/12 16:43:36  mmiers
 * LOG: Try to make WIN fifos a little smarter.
 * LOG:
 * LOG: Revision 1.17  1998/09/22 15:17:59  mmiers
 * LOG: Fix brain damage.
 * LOG:
 * LOG: Revision 1.16  1998/09/21 19:01:23  jrao
 * LOG: Added HPUX support
 * LOG:
 * LOG: Revision 1.15  1998/07/16 22:49:07  mmiers
 * LOG: Add fifo peek method for the SRM.
 * LOG:
 * LOG: Revision 1.14  1998/06/01 16:35:14  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.13  1998/05/29 03:31:28  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.12  1998/05/27 02:46:25  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.11  1998/05/27 02:18:11  mmiers
 * LOG: Reimplement fifos for NT and Solaris.  Nobody should be affected by this
 * LOG: change (from a user perspective), but ITS_Worker has a new transport type,
 * LOG: depending on whether or not the FIFO transport is reentrant.
 * LOG:
 * LOG: Revision 1.10  1998/05/19 17:11:44  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.9  1998/05/01 00:24:29  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.8  1998/04/16 04:32:01  mmiers
 * LOG: Cleanup for the gated versions.
 * LOG:
 * LOG: Revision 1.7  1998/04/15 00:07:15  mmiers
 * LOG: Tests and bug fixes for infrastructure.
 * LOG:
 * LOG: Revision 1.6  1998/04/13 22:24:37  mmiers
 * LOG: Add direction checking for fifos.
 * LOG:
 * LOG: Revision 1.5  1998/04/13 22:19:21  mmiers
 * LOG: Fifo (named pipe) implementation.  For portability, fifos can be
 * LOG: RDONLY or WRONLY, but not both (i.e., not bidirectional).  For
 * LOG: bidirectional communication, use two fifos.
 * LOG:
 * LOG: Revision 1.4  1998/04/09 01:47:17  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.3  1998/04/07 15:03:55  mmiers
 * LOG: More work on fifos, which required some new error numbers.
 * LOG:
 * LOG: Revision 1.2  1998/04/07 14:33:22  mmiers
 * LOG: Add fifo implementation.
 * LOG:
 * LOG: Revision 1.1  1998/04/07 01:04:23  mmiers
 * LOG: New file.  One method for IPC.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_FIFO_H
#define ITS_FIFO_H

#ident "$Id: its_fifo.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if !defined(ITS_FIFO_ONESHOT)
#define ITS_FIFO_ONESHOT

typedef enum
{
    ITS_FIFO_READER,
    ITS_FIFO_WRITER
}
ITS_FIFO_MODE;

#endif /* ITS_FIFO_ONESHOT */

#ifdef __cplusplus
extern "C" {
#endif

/*.interface:FIFO
 *****************************************************************************
 *  Interface:
 *      FIFO_*
 *
 *  Purpose:
 *      This interface provides exactly half of the interface needed by
 *      the Fifo class.  In other words, the fifo that a task reads from
 *      is NOT the fifo that other tasks write to.  For IPC, you need two
 *      fifos for bidirectional communication.
 *
 *  Usage:
 *      Depending on the creation mode, a fifo can either be read from,
 *      or written to, but never both.  This follows the general logic for
 *      transports that any task consumes messages from one point, but
 *      can send messages to many points.
 *
 *      Note that the read/write routines do NOT check for whether or not
 *      the fifo created is in read or write mode; it is assumed that the
 *      caller is smart enough to know which is which.  This is another reason
 *      that these interfaces are not intended for general use.
 *
 *      Usage of fifos is as follows:
 *      ----------------------------------------------------------------------
 *      * for readers *
 *      ITS_FIFO rfifo;
 *
 *      * creation *
 *      if (ITS_CreateFifo(&rfifo, ITS_FIFO_READER) != ITS_SUCCESS)
 *      {
 *          * error condition *
 *      }
 *
 *      ...
 *
 *      * for writers *
 *      ITS_FIFO wfifo;
 *
 *      * creation *
 *      if (ITS_CreateFifo(&wfifo, ITS_FIFO_WRITER) != ITS_SUCCESS)
 *      {
 *          * error condition *
 *      }
 *
 *      ...
 *
 *      * which one you use from here on out depends on which side of the
 *      * endpoint you're on.  Senders Write() to ITS_FIFO_WRITER fifos.
 *      * Readers Read() from ITS_FIFO_READER fifos.
 *      if (ITS_WriteFifo(&wfifo, buf, size) != ITS_SUCCESS)
 *      {
 *          * error condition *
 *      }
 *
 *      if (ITS_ReadFifo(&rfifo, buf, size) != ITS_SUCCESS)
 *      {
 *          * error condition *
 *      }
 *
 *      ...
 *
 *      * regardless of the type, the user should destroy any fifos created.
 *      ITS_DeleteFifo(&wfifo);
 *      ITS_DeleteFifo(&rfifo);
 *      -----------------------------------------------------------------------
 *
 *      Again, the reentrancy restrictions of this transport are operating
 *      system dependent.
 *
 *****************************************************************************/
ITSDLLAPI int FIFO_CreateFifo(ITS_FIFO *m, char *name, ITS_FIFO_MODE mode);
ITSDLLAPI void FIFO_DeleteFifo(ITS_FIFO *m, char *name);
ITSDLLAPI int FIFO_ReadFifo(ITS_FIFO *m, char *buf, int size);
ITSDLLAPI int FIFO_PeekFifo(ITS_FIFO *m, char *buf, int size);
ITSDLLAPI int FIFO_WriteFifo(ITS_FIFO *m, char *buf, int size);
ITSDLLAPI int FIFO_ResyncFifo(ITS_FIFO *m, char *pat, int psize);

#ifdef __cplusplus
}
#endif

#if defined (USE_CPLUSPLUS)

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Fifo
 *****************************************************************************
 *  Interface:
 *      Fifo
 *
 *  Purpose:
 *      The Fifo interface provides the means for high-speed communication
 *      between processes on a single platform.  It falls mid-way along the
 *      cost/complexity line -- it is heavier than a task queue, but lighter
 *      than sockets.
 *
 *      Fifo(s) aren't intended for use by consumers of IntelliSS7,
 *      although they are available as a convenience.  The methods are not
 *      guaranteed to retain the same signatures in this case.
 *
 *  Usage:
 *      How fifos are implemented is operating system dependent, but the
 *      public interface is the same across platforms.  On those platforms
 *      that do not implement an interprocess message passing mechanism
 *      (e.g., something like mqd_t for Solaris, or CreateNamedPipe() on NT),
 *      the fifo is not guaranteed to be of the minimum possible weight.
 *
 *      Note that while ITS_FIFO represents a bidirectional communications
 *      path, BOTH *endpoints* in a connection need a their own fifo.
 *      This explains why any given Fifo endpoint has two ITS_FIFO objects;
 *      one for sending messages, one for receiving messages.
 *
 *      The usage for fifos is as follows:
 *      --------------------------------------------------------------------
 *      char pathName = "./local_fifo"; // Note that the rules for fifo names
 *                                      // varies from platform to platform.
 *
 *      ...
 *
 *      // you must specify the pathname for the fifo as well as the open mode
 *      Fifo *f = new Fifo(pathName);
 *
 *      ...
 *
 *      // the read and write routines are used for passing data
 *      // the return values from these routines are ITS_SUCCESS or error
 *      char buf[ITS_PATH_MAX];
 *      if (f->Read(buf, ITS_PATH_MAX) == ITS_SUCCESS)
 *      {
 *          if (f->Write(buf, nbytes) != ITS_SUCCESS)
 *          {
 *              // an error has occurred
 *          }
 *      }
 *      else
 *      {
 *          // an error has occurred.
 *      }
 *
 *      ...
 *
 *      // when finished with a fifo, it should be deleted
 *      delete f;
 *      --------------------------------------------------------------------
 *
 *      For those operating systems whose fifos are implemented as byte
 *      streams, users should use the ITS_GatedFifo to guarantee proper
 *      data serialization.
 *
 *      This code cannot be considered reentrant on all platforms.  Check
 *      its_fifo.h to see if your platform supports reentrant fifos, or
 *      if you need to use gated fifos.
 *
 *****************************************************************************/
class Fifo
{
public:
    /*.implementation:public,inline,Fifo
     ************************************************************************
     *  Purpose:
     *      This method creates (at least) one end of a FIFO transport, and
     *      connects to the other end of said transport.  In this way a
     *      bidirectional data path is created, where one FIFO is read only,
     *      and the other FIFO is write only.  The read only fifo is local;
     *      the write only FIFO is the pipe to the other end.
     *
     *  Input Parameters:
     *      _name - the path name of the basic transport involved.
     *
     *  Notes:
     *      If for whatever reason one end of the FIFO cannot be created, this
     *      method may issue an exception.
     *
     *  See Also:
     *      ~Fifo()
     ************************************************************************/
    Fifo(char *client, char *server)
    {
        if (FIFO_CreateFifo(&rfifo, server, ITS_FIFO_READER) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADFIFO, __FILE__, __LINE__);
        }
        rname = strdup(server);

        if (FIFO_CreateFifo(&wfifo, client, ITS_FIFO_WRITER) != ITS_SUCCESS)
        {
            FIFO_DeleteFifo(&rfifo, rname);

            free(rname);

            throw Error(ITS_EBADFIFO, __FILE__, __LINE__);
        }
        wname = strdup(client);

    }
    /*.implementation:public,inline,Fifo
     ************************************************************************
     *  Purpose:
     *      This method destroys a FIFO transport.  Note that the release of the
     *      individual components of the transport may be delayed until both
     *      ends of the FIFO transport have released their resources.
     *
     *  See Also:
     *      Fifo()
     ************************************************************************/
    virtual ~Fifo()
    {
        FIFO_DeleteFifo(&wfifo, wname);
        FIFO_DeleteFifo(&rfifo, rname);

        free(wname);
        free(rname);
    }

    /*.implementation:public,inline,Fifo
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
        return FIFO_WriteFifo(&wfifo, buf, size);
    }
    /*.implementation:public,inline,Fifo
     ************************************************************************
     *  Purpose:
     *      This method reads one message from the READER side of a FIFO transport.
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
        return FIFO_ReadFifo(&rfifo, buf, size);
    }

private:
    /* sorry folks, no copying these */
    Fifo() {}
    Fifo(Fifo&) {}
    Fifo& operator=(Fifo&) { return *this; }

    ITS_FIFO rfifo;
    ITS_FIFO wfifo;
    char *rname;
    char *wname;
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_FIFO_H */
