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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.2  2005/09/14 16:31:02  lbana
 * LOG: use its_linux.h for Montavista distro.
 * LOG:
 * LOG: Revision 9.1.8.1  2005/09/14 16:27:54  lbana
 * LOG: Modified for building mtp2 kernel module on Linux flavors.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:51  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5  2003/01/16 16:18:33  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.4  2003/01/07 15:59:18  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.3  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.2  2002/10/25 21:53:45  mmiers
 * LOG: Add 64 bit solaris platform
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 14:49:36  mmiers
 * LOG: Add bits.  Rename CIC cic.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:58  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/08/16 19:56:32  lbana
 * LOG: vxworks platform header is included
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/04/05 16:52:16  mmiers
 * LOG: Proper class hierarchy for thread.
 * LOG:
 * LOG: Revision 3.7  2001/02/12 22:44:15  mmiers
 * LOG: Add pragma to its_types.h
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/02/05 22:05:02  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.4  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:06:36  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.2  2000/08/18 02:20:13  mmiers
 * LOG: First implementation of stack MEMPOOL.  Smarten realloc needs to be
 * LOG: done.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:26  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:03:34  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  2000/01/24 22:19:20  mmiers
 * LOG:
 * LOG:
 * LOG: Add UDP style transports.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:59  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:50  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.17  1999/11/03 00:09:26  labuser
 * LOG:
 * LOG: fhasle: updated ITS_HDR for ISUP (CIC instead of Call Ref).
 * LOG:
 * LOG: Revision 1.16  1999/07/22 00:34:34  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.15  1999/03/17 14:27:38  mmiers
 * LOG:
 * LOG:
 * LOG: More work on simultaneous ANSI and CCITT protocols.  Change the size
 * LOG: of the "type" field of ITS_HDR to be 16 bits.
 * LOG:
 * LOG: Revision 1.14  1999/03/12 18:20:08  mmiers
 * LOG:
 * LOG:
 * LOG: Break the core functions out of the support library.  This
 * LOG: allows just the core and vendor library to be sold to a customer.
 * LOG:
 * LOG: Revision 1.13  1999/02/26 15:41:07  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Solaris C++ build.
 * LOG:
 * LOG: Revision 1.12  1998/04/29 00:23:56  mmiers
 * LOG: False positive?
 * LOG:
 * LOG: Revision 1.11  1998/04/22 19:00:11  mmiers
 * LOG: Continuing on with the infrastructure.  Completed the removal of all
 * LOG: vendor aware code.
 * LOG:
 * LOG: Revision 1.10  1998/04/20 22:04:45  mmiers
 * LOG: Integrate in the worker code.  Trying to maintain backwards
 * LOG: compatibility with existing vendor code.
 * LOG:
 * LOG: Revision 1.9  1998/04/16 04:36:20  mmiers
 * LOG: New versions for C++.
 * LOG:
 * LOG: Revision 1.8  1998/04/06 15:27:14  mmiers
 * LOG: Infrastructure cleanup.
 * LOG:
 * LOG: Revision 1.7  1998/03/13 04:12:32  mmiers
 * LOG: Update files with latest data for TCAP implementation.  emlist represents
 * LOG: portable message queues.
 * LOG:
 * LOG: Revision 1.6  1998/03/12 03:50:55  mmiers
 * LOG: More corrections for the TCAP impl.  Make sure the LIST_Entry is appropriate
 * LOG: for the list type.
 * LOG:
 * LOG: Revision 1.5  1998/03/11 23:10:58  mmiers
 * LOG: Oops, missed one.
 * LOG:
 * LOG: Revision 1.4  1998/03/11 23:07:11  mmiers
 * LOG: Add some new files for lists, mutex protected lists, and semaphore gated
 * LOG: mutex protected lists.
 * LOG:
 * LOG: Revision 1.3  1998/02/26 18:48:08  mmiers
 * LOG: sccp.h: A few changes to param ids.
 * LOG:
 * LOG: its_types.h: #define the max length of an event.
 * LOG:
 * LOG: Revision 1.2  1998/02/25 22:12:23  mmiers
 * LOG: sccp.h: Some corrections, a plan for moving the address structure from
 * LOG: tcap.h to sccp.h.  Add SCCP as a possible event source to its.h.  Add
 * LOG: a type for point codes to its_types.h.
 * LOG:
 * LOG: Revision 1.1  1998/02/10 22:32:38  mmiers
 * LOG: New file for types in IntelliSS7
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_TYPES_H
#define ITS_TYPES_H

/* DevStudio 7 can't do this */
#if defined(WIN32)
#pragma warning(disable:4274)
#endif

#ident "$Id: its_types.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"


/*
 * NOTE NOTE NOTE NOTE NOTE NOTE
 *
 * TYPES ONLY IN THIS FILE, PLEASE.  IT IS NOT PROTECTED WITH
 * #ifdef __cplusplus, SO NO FUNCTION SIGNATURES ARE ALLOWED.
 */

/*
 * basic types
 */
typedef unsigned int     ITS_BOOLEAN;
typedef unsigned char    ITS_OCTET;
typedef unsigned short   ITS_USHORT;
typedef unsigned int     ITS_UINT;
typedef unsigned long    ITS_ULONG;
typedef char             ITS_CHAR;
typedef short            ITS_SHORT;
typedef int              ITS_INT;
typedef long             ITS_LONG;
typedef float            ITS_FLOAT;
typedef double           ITS_DOUBLE;
typedef void *           ITS_HANDLE;
typedef void *           ITS_SS7_HANDLE;
typedef char *           ITS_POINTER;

/*
 * serial for events.
 */
typedef ITS_UINT    ITS_SERIAL;


/*
 * yes/no, true/false
 */
#define ITS_NO        (0U)
#define ITS_YES       (~ITS_NO)
#define ITS_FALSE     ITS_NO
#define ITS_TRUE      ITS_YES

/*
 * the context type can change, depending on the platform.
 */
#if defined(NEED_LARGE_CONTEXT)

typedef ITS_UINT    ITS_CTXT;

#define ITS_SET_CTXT(b, v)                      \
    ((b)[0] = (ITS_OCTET)(((v) >> 24) & 0xFF),  \
     (b)[1] = (ITS_OCTET)(((v) >> 16) & 0xFF),  \
     (b)[2] = (ITS_OCTET)(((v) >> 8) & 0xFF),   \
     (b)[3] = (ITS_OCTET)((v) & 0xFF))
#define ITS_GET_CTXT(b)                         \
    (((b)[0] << 24) | ((b)[1] << 16) |          \
     ((b)[2] << 8) | (b)[3])

#else

typedef ITS_USHORT  ITS_CTXT;

#define ITS_SET_CTXT(b, v)                      \
    ((b)[0] = (ITS_OCTET)(((v) >> 8) & 0xFF),   \
     (b)[1] = (ITS_OCTET)((v) & 0xFF))
#define ITS_GET_CTXT(b)                         \
     (((b)[0] << 8) | (b)[1])

#endif

/*
 * the ITS_HDR provides some context for individual messages
 */
typedef struct
{
    ITS_USHORT type;
    union
    {
        ITS_CTXT    cic;          /* ISUP */
        ITS_CTXT    dialogue_id;  /* TCAP */
        ITS_CTXT    ssn;          /* connectionless SCCP */
        ITS_CTXT    conref;       /* connection oriented SCCP */
    }
    context;
}
ITS_HDR;

/*
 * event notification structure
 *
 * Zero copy strategy:
 *  o border transports do an ITS_Malloc() on GetNextEvent for
 *    the data portion of the event.
 *  o TRANSPORT_PutEvent() will do an ITS_Free() on the data
 *    portion of the event, if the transport being put to is *not*
 *    task queue based.  If the transport *is* task queue based,
 *    the caller's event has its data pointer set to NULL.
 *  o For task queues, if the data portion is non-null in the
 *    event that is passed to GetNextEvent(), that data portion
 *    is ITS_Free()'d as it is assumed that the event was consumed
 *    by the caller's thread.
 * This should effectively cope with all scenarios.  Bottom line,
 *  o events MUST always be auto variables, not heap or
 *    bss
 * Follow that rule and you'll be ok.
 */
#define ITS_MAX_EVENT_SIZE  65000 /* allow room for IP header and such */

typedef struct
{
    ITS_USHORT len;
    ITS_USHORT src;
    ITS_OCTET* data;
}
ITS_EVENT;

#ifndef __KERNEL__

#include <time.h>

/*
 * get the object types
 */
#include <its_object.h>

/*
 * may need to change this for other platforms
 */
typedef time_t      ITS_TIME;

/*
 * Please TRY at least to localize this here, 'kay?
 */
#if defined(WIN32)
#include <platforms/its_win.h>
#elif defined(DECUNIX)
#include <platforms/its_decunix.h>
#elif defined(linux) || defined (montavista)
#include <platforms/its_linux.h>
#elif defined(solaris) || defined(solaris64)
#include <platforms/its_solaris.h>
#elif defined(HPUX)
#include <platforms/its_hpux.h>
#elif defined(TANDEM)
#include <platforms/its_tandem.h>
#elif defined(vxworks)
#include <platforms/its_vxworks.h>
#else
#error "Platform not defined!"
#endif

#else /* nostd for kernel modules */
/*
 * debugging
 */
#define ITS_ASSERT(cond)                                  \
    do                                                    \
    {                                                     \
        if (!(cond))                                      \
        {                                                 \
            printk("assertion " #cond "failed at %s %d\n",\
                   __FILE__, __LINE__);                   \
            for (;;) {}                                   \
        }                                                 \
    }                                                     \
    while (0)

                                                                                   
#define ITS_TRACE_LEVEL_CRITICAL      0
#define ITS_TRACE_LEVEL_ERROR         1
#define ITS_TRACE_LEVEL_WARNING       2
#define ITS_TRACE_LEVEL_DEBUG         3
#define ITS_TRACE_LEVEL_EVENT         4

#endif /* __KERNEL__ */

#endif /* ITS_TYPES_H */
