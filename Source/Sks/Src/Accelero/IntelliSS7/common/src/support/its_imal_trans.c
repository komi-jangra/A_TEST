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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:01  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:59  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 03:30:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:39:59  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/07/05 19:58:21  mmiers
 * LOG: Add PRC IP transports
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.2  2001/10/17 00:39:15  mmiers
 * LOG: Allow simultaneous family presence for TALI, IMAL, GDI
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.9  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.8  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.7  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.6  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.4  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.6  2000/11/09 23:04:25  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.5  2000/11/09 01:32:34  mmiers
 * LOG: Some cross platform issues, more comments about the new routing mech.
 * LOG:
 * LOG: Revision 3.4  2000/11/09 00:48:42  mmiers
 * LOG: Today's installment.  Also an IMAL fix.
 * LOG:
 * LOG: Revision 3.3  2000/08/31 22:57:24  mmiers
 * LOG: Fix a typo, condition variable locking for Solaris.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:39  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:31  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.10  2000/08/09 01:13:44  mmiers
 * LOG: Platform corrections.
 * LOG:
 * LOG: Revision 2.9  2000/08/05 00:20:34  mmiers
 * LOG: IMAL: Add per link SLTM data.
 * LOG: SCTP: Update implementation.
 * LOG:
 * LOG: Revision 2.8  2000/07/13 19:29:00  mmiers
 * LOG:
 * LOG: Per transport timer.
 * LOG:
 * LOG: Revision 2.7  2000/06/22 23:10:45  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG: Fix route bugs with multilink routes.
 * LOG:
 * LOG: Revision 2.6  2000/06/15 17:29:08  mmiers
 * LOG: Watch recursion problem
 * LOG:
 * LOG: Revision 2.5  2000/06/02 17:19:11  mmiers
 * LOG:
 * LOG:
 * LOG: Socket changes.
 * LOG:
 * LOG: Revision 2.4  2000/05/15 22:34:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.3  2000/05/11 21:23:08  mmiers
 * LOG:
 * LOG:
 * LOG: OOps, get the names right.
 * LOG:
 * LOG: Revision 2.2  2000/05/11 02:06:13  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.1  2000/05/10 23:43:45  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based transports with heartbeats.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_sockets.h>
#include <its_transports.h>
#include <its_ip_trans.h>
#include <its_tq_trans.h>
#include <its_trace.h>
#include <its_thread.h>
#include <its_timers.h>
#include <its_imal_trans.h>
#include <its_assertion.h>

#ident "$Id: its_imal_trans.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*
 * trace control
 */
#define IMAL_DEBUG

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method does the necessary part of shutting down a bad socket.
 *
 *  Input Parameters:
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
 ****************************************************************************/
static void
Shutdown(SOCKTRAN_Manager *ft)
{
    IMALTRAN_KA_REQ_PENDING(ft) = ITS_FALSE;

    SOCKTRAN_CLASS_SHUTDOWN(ITS_CLASS_SUPERCLASS(ITS_OBJ_CLASS(ft)))(ft);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method does the necessary part of restarting a bad socket.
 *
 *  Input Parameters:
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
 ****************************************************************************/
static void
Restart(SOCKTRAN_Manager *ft)
{
    IMALTRAN_KA_REQ_PENDING(ft) = ITS_FALSE;

    SOCKTRAN_CLASS_RESTART(ITS_CLASS_SUPERCLASS(ITS_OBJ_CLASS(ft)))(ft);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function performs the network read.
 *
 *  Input Parameters:
 *      msg - the message to convert
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
static int
LowRead(KASOCKTRAN_Manager *kt, void *buf)
{
    ITS_C_REQUIRE(kt != NULL);
    ITS_C_REQUIRE(buf != NULL);

    /* We just inherit from IntelliSS7 */
    return SOCKTRAN_CLASS_EXT_READ_EVENT(itsSOCKTRAN_ClientClass)(kt,
                                                                  buf);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function performs the network write.
 *
 *  Input Parameters:
 *      msg - the message to convert
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
static int
LowWrite(KASOCKTRAN_Manager *kt, void *buf)
{
    ITS_C_REQUIRE(kt != NULL);
    ITS_C_REQUIRE(buf != NULL);

    return SOCKTRAN_CLASS_EXT_WRITE_EVENT(itsSOCKTRAN_ClientClass)(kt,
                                                                   buf);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function creates a IMAL transport
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
static int
Create(ITS_Object h, va_list args)
{
    IMALTRAN_Manager *tc = (IMALTRAN_Manager *)h;
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    RESFILE_Manager *res;
    char value[ITS_PATH_MAX], *rname;

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    if (TRANSPORT_MASK(tc) & ITS_TRANSPORT_SSOCKET_ITER)
    {
        return (ITS_SUCCESS);
    }

    KASOCKTRAN_LOW_READ_BUF(tc) = malloc(sizeof(ITS_EVENT) +
                                         ITS_MAX_EVENT_SIZE);
    if (KASOCKTRAN_LOW_READ_BUF(tc) == NULL)
    {
        return (ITS_ENOMEM);
    }

    KASOCKTRAN_LOW_WRITE_BUF(tc) = malloc(sizeof(ITS_EVENT) +
                                          ITS_MAX_EVENT_SIZE);
    if (KASOCKTRAN_LOW_WRITE_BUF(tc) == NULL)
    {
        free(KASOCKTRAN_LOW_READ_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;

        return (ITS_ENOMEM);
    }

    /* get the remoteSSN value */
    res = TRANSPORT_RES(tc);
    rname = TRANSPORT_NAME(tc);
    if (RESFILE_GetKeyValueOf(res, rname, IMAL_LOCAL_PC_STRING,
                              value, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("IMAL Create: Missing localPC\n"));

        free(KASOCKTRAN_LOW_READ_BUF(tc));
        free(KASOCKTRAN_LOW_WRITE_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
        KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;

        return (ITS_EINVALIDARGS);
    }
    else
    {
        IMALTRAN_KA_LOCAL_PC(tc) = RESFILE_ParseNum(value);
    }

    if (RESFILE_GetKeyValueOf(res, rname, IMAL_ADJ_PC_STRING,
                              value, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("IMAL Create: Missing adjacentPC\n"));

        free(KASOCKTRAN_LOW_READ_BUF(tc));
        free(KASOCKTRAN_LOW_WRITE_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
        KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;

        return (ITS_EINVALIDARGS);
    }
    else
    {
        IMALTRAN_KA_ADJACENT_PC(tc) = RESFILE_ParseNum(value);
    }

    if (RESFILE_GetKeyValueOf(res, rname,
                              IMAL_KEEPALIVE_TIMEOUT_STRING,
                              value, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        IMALTRAN_KA_TIMEOUT(tc) = atoi(value);
    }
    else
    {
        IMALTRAN_KA_TIMEOUT(tc) = IMAL_KEEP_ALIVE_TIMEOUT_DEFAULT;
    }

    /* initial values for the keepalives */
    IMALTRAN_KA_START_TIME(tc) =
        IMALTRAN_KA_TRANSMIT_TIME(tc) =
            TIMERS_Time();

    if (MUTEX_CreateMutex(&IMALTRAN_KA_PATTERN_LOCK(tc), 0) != ITS_SUCCESS)
    {
        free(KASOCKTRAN_LOW_READ_BUF(tc));
        free(KASOCKTRAN_LOW_WRITE_BUF(tc));

        KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
        KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;

        return (ITS_EBADMUTEX);
    }

    strcpy((char *)IMALTRAN_KA_SEND_PATTERN(tc), "IMAL");
    IMALTRAN_KA_SEND_PATTERN_LEN(tc) = 4;

    IMALTRAN_KA_REQ_PENDING(tc) = ITS_FALSE;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      This function destroys a IMAL transport
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
static void
Destroy(ITS_Object h)
{
    IMALTRAN_Manager *tc = (IMALTRAN_Manager *)h;

    MUTEX_DeleteMutex(&IMALTRAN_KA_PATTERN_LOCK(tc));

    free(KASOCKTRAN_LOW_READ_BUF(tc));
    free(KASOCKTRAN_LOW_WRITE_BUF(tc));

    KASOCKTRAN_LOW_READ_BUF(tc) = NULL;
    KASOCKTRAN_LOW_WRITE_BUF(tc) = NULL;
}

/*
 * the class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ClientClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_CLIENT_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ClientClass_ANSI =
    (TRANSPORT_Class)&itsIMALTRAN_ClientClassRec_ANSI;

ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ServerClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_SERVER_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ServerClass_ANSI =
    (TRANSPORT_Class)&itsIMALTRAN_ServerClassRec_ANSI;

/*
 * the dynamic server class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_DynamicServerClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_DYNAMIC_CLASS_NAME,                    /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_DynamicServerClass_ANSI =
    (TRANSPORT_Class)&itsIMALTRAN_DynamicServerClassRec_ANSI;

/*
 * the local end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_LocalEndPointClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_LocalEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_LOCAL_EP_CLASS_NAME,                   /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_LocalEndPointClass_ANSI =
    (TRANSPORT_Class)&itsIMALTRAN_LocalEndPointClassRec_ANSI;

/*
 * the remote end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_RemoteEndPointClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_RemoteEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_REMOTE_EP_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_RemoteEndPointClass_ANSI =
    (TRANSPORT_Class)&itsIMALTRAN_RemoteEndPointClassRec_ANSI;

/*
 * the class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ClientClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_CLIENT_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ClientClass_CCITT =
    (TRANSPORT_Class)&itsIMALTRAN_ClientClassRec_CCITT;

ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ServerClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_SERVER_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ServerClass_CCITT =
    (TRANSPORT_Class)&itsIMALTRAN_ServerClassRec_CCITT;

/*
 * the dynamic server class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_DynamicServerClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_DYNAMIC_CLASS_NAME,                    /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_DynamicServerClass_CCITT =
    (TRANSPORT_Class)&itsIMALTRAN_DynamicServerClassRec_CCITT;

/*
 * the local end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_LocalEndPointClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_LocalEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_LOCAL_EP_CLASS_NAME,                   /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_LocalEndPointClass_CCITT =
    (TRANSPORT_Class)&itsIMALTRAN_LocalEndPointClassRec_CCITT;

/*
 * the remote end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_RemoteEndPointClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_RemoteEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_REMOTE_EP_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_RemoteEndPointClass_CCITT =
    (TRANSPORT_Class)&itsIMALTRAN_RemoteEndPointClassRec_CCITT;

/*
 * the class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ClientClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_CLIENT_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ClientClass_PRC =
    (TRANSPORT_Class)&itsIMALTRAN_ClientClassRec_PRC;

ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ServerClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_SERVER_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ServerClass_PRC =
    (TRANSPORT_Class)&itsIMALTRAN_ServerClassRec_PRC;

/*
 * the dynamic server class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_DynamicServerClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_DYNAMIC_CLASS_NAME,                    /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_DynamicServerClass_PRC =
    (TRANSPORT_Class)&itsIMALTRAN_DynamicServerClassRec_PRC;

/*
 * the local end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_LocalEndPointClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_LocalEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_LOCAL_EP_CLASS_NAME,                   /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_LocalEndPointClass_PRC =
    (TRANSPORT_Class)&itsIMALTRAN_LocalEndPointClassRec_PRC;

/*
 * the remote end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_RemoteEndPointClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_RemoteEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_REMOTE_EP_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_RemoteEndPointClass_PRC =
    (TRANSPORT_Class)&itsIMALTRAN_RemoteEndPointClassRec_PRC;

/*
 * TTC class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ClientClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_CLIENT_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ClientClass_TTC =
    (TRANSPORT_Class)&itsIMALTRAN_ClientClassRec_TTC;

ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_ServerClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(IMALTRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        IMALTRAN_SERVER_CLASS_NAME,                 /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        Create,                                     /* create routine */
        Destroy,                                    /* destructor */
        ITS_INST_CLONE_INHERIT,                     /* inherit clone */
        ITS_INST_PRINT_INHERIT,                     /* inherit print */
        ITS_INST_SERIAL_INHERIT,                    /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                    /* inherit equals */
        ITS_INST_HASH_INHERIT,                      /* inherit equals */
        NULL                                        /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_ServerClass_TTC =
    (TRANSPORT_Class)&itsIMALTRAN_ServerClassRec_TTC;

/*
 * the dynamic server class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_DynamicServerClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_DYNAMIC_CLASS_NAME,                    /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_DynamicServerClass_TTC =
    (TRANSPORT_Class)&itsIMALTRAN_DynamicServerClassRec_TTC;

/*
 * the local end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_LocalEndPointClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_LocalEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_LOCAL_EP_CLASS_NAME,                   /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_LocalEndPointClass_TTC =
    (TRANSPORT_Class)&itsIMALTRAN_LocalEndPointClassRec_TTC;

/*
 * the remote end point class record
 */
ITSDLLAPI IMALTRAN_ClassRec itsIMALTRAN_RemoteEndPointClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_RemoteEndPointClassRec,/* the root object */
        sizeof(IMALTRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        IMALTRAN_REMOTE_EP_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        Create,                                         /* instantiate */
        Destroy,                                        /* destructor */
        ITS_INST_CLONE_INHERIT,                         /* inherit clone */
        ITS_INST_PRINT_INHERIT,                         /* inherit print */
        ITS_INST_SERIAL_INHERIT,                        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                        /* inherit equals */
        ITS_INST_HASH_INHERIT,                          /* inherit equals */
        NULL                                            /* extension */
    },
    /* transport */
    {
        TRANSPORT_INHERIT_EVENT_PROC,       /* get */
        TRANSPORT_INHERIT_EVENT_PROC,       /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,       /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,      /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        LowRead,                                    /* low read */
        LowWrite,                                   /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsIMALTRAN_RemoteEndPointClass_TTC =
    (TRANSPORT_Class)&itsIMALTRAN_RemoteEndPointClassRec_TTC;
