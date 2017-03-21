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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:30  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
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
 * LOG: Revision 3.6  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:51  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:18  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:37  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.13  1998/11/12 16:43:36  mmiers
 * LOG: Try to make WIN fifos a little smarter.
 * LOG:
 * LOG: Revision 1.12  1998/11/12 00:09:13  mmiers
 * LOG: Debugging SSP/SSA.  Note that this has a major change for FIFOs.
 * LOG: Revert to the previous version of fifo-win and fifo_trans if this
 * LOG: doesn't work everywhere.
 * LOG:
 * LOG: Revision 1.11  1998/11/05 16:52:13  mmiers
 * LOG: Add in transport pause/resume.
 * LOG: Add reconnect to sockets.
 * LOG:
 * LOG: Revision 1.10  1998/09/23 22:54:19  mmiers
 * LOG: Add tracing to the windows implementation.
 * LOG:
 * LOG: Revision 1.9  1998/08/17 14:56:57  mmiers
 * LOG: Check for data available, not just if Peek succeeds.
 * LOG:
 * LOG: Revision 1.8  1998/07/16 19:16:48  mmiers
 * LOG: Add a peek for fifo objects.
 * LOG:
 * LOG: Revision 1.7  1998/07/16 16:03:03  mmiers
 * LOG: Modify the return value so that SUCCESS is returned on successful write.
 * LOG:
 * LOG: Revision 1.6  1998/06/08 18:44:21  whu
 * LOG: Fixed return value error in ITS_ReadFifo.
 * LOG:
 * LOG: Revision 1.5  1998/06/08 18:11:09  mmiers
 * LOG: Modify for NT.
 * LOG:
 * LOG: Revision 1.4  1998/06/01 16:35:32  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.3  1998/05/27 22:08:06  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.2  1998/04/15 00:07:15  mmiers
 * LOG: Tests and bug fixes for infrastructure.
 * LOG:
 * LOG: Revision 1.1  1998/04/13 21:43:08  mmiers
 * LOG: Fifos for windows.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_fifo.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_fifo.c,v 1.1.1.1 2007-10-08 11:11:58 bsccs2 Exp $"

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function creates one FIFO for either reading or writing.
 *      A read-only FIFO is considered the "local" end of a two FIFO
 *      connection (i.e., the local process will "read" messages from the
 *      read-only FIFO).  A write-only FIFO is considered a shared path
 *      the the "remote" end of a two FIFO connection.  That is, local
 *      processes will "write" messages to the remote.
 *
 *  Input Parameters:
 *      name - a constant string, built within the rules of the current
 *          operating system, definining the name of the FIFO.
 *      mode - an enum value describing the open mode.  Can be either
 *          ITS_FIFO_READER or ITS_FIFO_WRITER.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      f - the address of the FIFO to create
 *
 *  Return Value:
 *      On successful creation of the FIFO, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 *      FIFO_DeleteFifo()
 ****************************************************************************/
ITSDLLAPI int
FIFO_CreateFifo(ITS_FIFO *m, char *name, ITS_FIFO_MODE mode)
{
    ITS_TRACE_DEBUG(("FIFO_CreateFifo:\n"));

    ITS_C_REQUIRE(m != NULL);
    ITS_C_REQUIRE(name != NULL);

    m->handle = INVALID_HANDLE_VALUE;
    m->mode = mode;
    m->isPipe = ITS_FALSE;
    m->isConnected = ITS_FALSE;

    if (mode == ITS_FIFO_WRITER)
    {
        if ((m->handle = CreateFile(name, GENERIC_WRITE,
                                    0, NULL, OPEN_EXISTING,
                                    0, 0)) == INVALID_HANDLE_VALUE)
        {
            if ((m->handle = CreateNamedPipe(name, PIPE_ACCESS_OUTBOUND,
                                             PIPE_TYPE_MESSAGE|
                                                PIPE_READMODE_MESSAGE|
                                                PIPE_WAIT,
                                             1, 4096, 4096,
                                             NMPWAIT_USE_DEFAULT_WAIT,
                                             NULL)) == INVALID_HANDLE_VALUE)
            {
                ITS_TRACE_ERROR(("FIFO_CreateFifo: Couldn't create WRITER "
                                 "fifo\n"));

                return (ITS_ENOFIFO);
            }
            else
            {
                m->isPipe = ITS_TRUE;
            }
        }
    }
    else if (mode == ITS_FIFO_READER)
    {
        if ((m->handle = CreateNamedPipe(name, PIPE_ACCESS_INBOUND,
                                         PIPE_TYPE_MESSAGE|
                                            PIPE_READMODE_MESSAGE|
                                            PIPE_WAIT,
                                         1, 4096, 4096,
                                         NMPWAIT_USE_DEFAULT_WAIT,
                                         NULL)) == INVALID_HANDLE_VALUE)
        {
            if ((m->handle = CreateFile(name, GENERIC_READ,
                                        0, NULL, OPEN_EXISTING,
                                        0, 0)) == INVALID_HANDLE_VALUE)
            {
                ITS_TRACE_ERROR(("FIFO_CreateFifo: Couldn't create READER "
                                 "fifo\n"));

                return (ITS_ENOFIFO);
            }
        }
        else
        {
            m->isPipe = ITS_TRUE;
        }
    }
    else
    {
        ITS_TRACE_ERROR(("FIFO_CreateFifo: invalid args\n"));

        return (ITS_EINVALIDARGS);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function closes and unlinks the file-system resources
 *      associated with this fifo.  Note that the resources will not be
 *      completely released until *both* ends of the connection are
 *      destroyed.
 *
 *  Input Parameters:
 *      m - the address of the FIFO to destroy
 *      name - the name of the file-system object associated with this fifo.
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
 *      FIFO_CreateFifo()
 ****************************************************************************/
ITSDLLAPI void
FIFO_DeleteFifo(ITS_FIFO *m, char *name)
{
    ITS_TRACE_DEBUG(("FIFO_DeleteFifo:\n"));

    ITS_C_REQUIRE(m != NULL);
    ITS_C_REQUIRE(name != NULL);

    if (m->isPipe && m->isConnected)
    {
        DisconnectNamedPipe(m->handle);
    }
    CloseHandle(m->handle);

    m->handle = INVALID_HANDLE_VALUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function writes "size" bytes to a fifo.  The operation is
 *      guaranteed to be atomic.
 *
 *  Input Parameters:
 *      f - the address of the fifo to write to
 *      buf - a character buffer to write from
 *      size - the number of bytes to write.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the correct number of bytes was written, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      FIFO_ReadFifo()
 ****************************************************************************/
ITSDLLAPI int
FIFO_WriteFifo(ITS_FIFO *m, char *buf, int size)
{
    DWORD ret;

    ITS_TRACE_DEBUG(("FIFO_WriteFifo:\n"));

    ITS_C_REQUIRE(m != NULL);
    ITS_C_REQUIRE(buf != NULL || size == 0);

    if (m->isPipe && !m->isConnected)
    {
        if (ConnectNamedPipe(m->handle, NULL) ||
            GetLastError() == ERROR_PIPE_CONNECTED)
        {
            m->isConnected = ITS_TRUE;
        }
        else
        {
            return (ITS_EBADFIFO);
        }
    }

    if (WriteFile(m->handle, buf, size, &ret, NULL) != 0)
    {
        if ((signed)ret == size)
        {
            ITS_TRACE_DEBUG(("FIFO_WriteFifo: write ok\n"));

            return (ITS_SUCCESS);
        }
        else
        {
            ITS_TRACE_ERROR(("FIFO_WriteFifo: bad size\n"));

            return (ITS_ERCVFAIL);
        }
    }

    return (ITS_EBADFIFO);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function reads "size" bytes from a fifo.  The operation is
 *      guaranteed to be atomic.
 *
 *  Input Parameters:
 *      f - the address of the fifo to read from.
 *      size = how many bytes to read.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      buf - a character buffer to read into
 *
 *  Return Value:
 *      If the expected number of bytes are read, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      FIFO_WriteFifo()
 ****************************************************************************/
ITSDLLAPI int
FIFO_ReadFifo(ITS_FIFO *m, char *buf, int size)
{
    DWORD ret;

    ITS_TRACE_DEBUG(("FIFO_ReadFifo:\n"));

    ITS_C_REQUIRE(m != NULL);
    ITS_C_REQUIRE(buf != NULL || size == 0);

    if (m->isPipe && !m->isConnected)
    {
        if (ConnectNamedPipe(m->handle, NULL) ||
            GetLastError() == ERROR_PIPE_CONNECTED)
        {
            m->isConnected = ITS_TRUE;
        }
        else
        {
            return (ITS_EBADFIFO);
        }
    }

    if (ReadFile(m->handle, buf, size, &ret, NULL) != 0)
    {
        if ((signed)ret == size)
        {
            ITS_TRACE_DEBUG(("FIFO_WriteFifo: read ok\n"));

            return (ITS_SUCCESS);
        }
        else
        {
            ITS_TRACE_ERROR(("FIFO_ReadFifo: bad size\n"));

            return (ITS_ERCVFAIL);
        }
    }

    return (ITS_EBADFIFO);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function reads "size" bytes from a fifo.  The operation is
 *      guaranteed to be atomic.
 *
 *  Input Parameters:
 *      f - the address of the fifo to read from.
 *      size = how many bytes to read.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      buf - a character buffer to read into
 *
 *  Return Value:
 *      If the expected number of bytes are read, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      FIFO_WriteFifo()
 ****************************************************************************/
ITSDLLAPI int
FIFO_PeekFifo(ITS_FIFO *m, char *buf, int size)
{
    DWORD ret, avail = 0;

    ITS_TRACE_DEBUG(("FIFO_PeekFifo:\n"));

    ITS_C_REQUIRE(m != NULL);
    ITS_C_REQUIRE(buf != NULL || size == 0);

    if (m->isPipe && !m->isConnected)
    {
        if (ConnectNamedPipe(m->handle, NULL) ||
            GetLastError() == ERROR_PIPE_CONNECTED)
        {
            m->isConnected = ITS_TRUE;
        }
        else
        {
            return (ITS_EBADFIFO);
        }
    }

    if (PeekNamedPipe(m->handle, NULL, 0, NULL, &avail, NULL) && avail > 0)
    {
        if (ReadFile(m->handle, buf, size, &ret, NULL) != 0)
        {
            if ((signed)ret == size)
            {
                ITS_TRACE_DEBUG(("FIFO_PeekFifo: message present\n"));

                return (ITS_SUCCESS);
            }
            else
            {
                ITS_TRACE_ERROR(("FIFO_PeekFifo: bad size\n"));

                return (ITS_ERCVFAIL);
            }
        }

        ITS_TRACE_DEBUG(("FIFO_PeekFifo: no message present\n"));
    }

    return (ITS_ENOMSG);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *      This function is unnecessary on this platform.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
FIFO_ResyncFifo(ITS_FIFO *m, char *buf, int size)
{
    ITS_TRACE_DEBUG(("FIFO_ResyncFifo:\n"));

    return (ITS_SUCCESS);
}
