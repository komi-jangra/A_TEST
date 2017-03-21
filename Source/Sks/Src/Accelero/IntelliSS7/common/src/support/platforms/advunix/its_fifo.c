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
 * LOG: Revision 8.2  2005/03/21 13:52:08  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:13  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:56  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:58  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:54  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.1  1999/12/16 16:16:22  mmiers
 * LOG: Sanitize the build environment a bit.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:34  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1998/06/01 16:35:31  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.1  1998/05/29 03:31:35  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.7  1998/05/27 22:08:06  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.6  1998/05/27 02:18:14  mmiers
 * LOG: Reimplement fifos for NT and Solaris.  Nobody should be affected by this
 * LOG: change (from a user perspective), but ITS_Worker has a new transport type,
 * LOG: depending on whether or not the FIFO transport is reentrant.
 * LOG:
 * LOG: Revision 1.5  1998/05/20 04:44:08  mmiers
 * LOG: Cleanup.
 * LOG: Hubert, some iterators need to be constant while others don't.  Please
 * LOG: see me about this.
 * LOG:
 * LOG: Revision 1.4  1998/04/13 22:19:21  mmiers
 * LOG: Fifo (named pipe) implementation.  For portability, fifos can be
 * LOG: RDONLY or WRONLY, but not both (i.e., not bidirectional).  For
 * LOG: bidirectional communication, use two fifos.
 * LOG:
 * LOG: Revision 1.3  1998/04/13 21:16:29  mmiers
 * LOG: Resolving some cross-platform issues.
 * LOG:
 * LOG: Revision 1.2  1998/04/07 15:03:55  mmiers
 * LOG: More work on fifos, which required some new error numbers.
 * LOG:
 * LOG: Revision 1.1  1998/04/07 14:33:23  mmiers
 * LOG: Add fifo implementation.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <errno.h>
#include <sys/fcntl.h>

#include <its.h>
#include <its_types.h>
#include <its_fifo.h>

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
FIFO_CreateFifo(ITS_FIFO *f, char *name, ITS_FIFO_MODE mode)
{
    int oflag = 0;
    struct mq_attr attr = {
        0, /* flags */
        512, /* max num msgs */
        1024, /* max msg size */
        0 /* num msgs queued */
    };
    char buf[ITS_PATH_MAX];

    if (mode == ITS_FIFO_READER)
    {
        oflag = O_RDONLY;
    }
    else if (mode == ITS_FIFO_WRITER)
    {
        oflag = O_WRONLY;
    }
    else
    {
        return (ITS_EINVALIDARGS);
    }

    if ((*f = mq_open(name, oflag|O_CREAT|O_EXCL,
                      S_IRWXU|S_IRWXG, &attr)) < 0 && errno != EEXIST)
    {
        return (ITS_ENOFIFO);
    }
    else if ((*f = mq_open(name, oflag)) < 0)
    {
        return (ITS_ENOFIFO);
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
FIFO_DeleteFifo(ITS_FIFO *f, char *name)
{
    mq_close(*f);

    mq_unlink(name);
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
FIFO_WriteFifo(ITS_FIFO *f, char *buf, int size)
{
    if (mq_send(*f, buf, size, 1) == 0)
    {
        return (ITS_SUCCESS);
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
FIFO_ReadFifo(ITS_FIFO *f, char *buf, int size)
{
    if (mq_receive(*f, buf, size, NULL) == size)
    {
        return (ITS_EBADFIFO);
    }

    return (ITS_EBADFIFO);
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
FIFO_ResyncFifo(ITS_FIFO *f, char *buf, int size)
{
    return (ITS_SUCCESS);
}
