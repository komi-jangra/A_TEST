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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:31  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:16  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:14  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.3  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 1.2  2001/02/12 21:42:33  lbana
 * LOG: ident macro is defined
 * LOG:
 * LOG: Revision 1.1  2001/02/12 21:07:48  lbana
 * LOG: fifo stub implementation for vxWorks
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <its.h>
#include <its_types.h>
#include <its_fifo.h>
#include <its_trace.h>

#ident "$Id: its_fifo.c,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $"

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
   return ITS_SUCCESS;
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
   return ITS_SUCCESS;
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
   return ITS_SUCCESS;
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
    return (ITS_SUCCESS);
}
