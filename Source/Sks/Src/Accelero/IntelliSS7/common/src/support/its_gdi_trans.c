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
 * LOG: Revision 1.2  2007/03/30 04:58:58  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:58  cvsadmin
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
 * LOG: Revision 3.7  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.5  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.3  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.3  2000/11/09 23:04:25  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.2  2000/11/09 01:32:34  mmiers
 * LOG: Some cross platform issues, more comments about the new routing mech.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.22  2000/06/22 23:10:44  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG: Fix route bugs with multilink routes.
 * LOG:
 * LOG: Revision 1.21  2000/06/02 17:18:12  mmiers
 * LOG:
 * LOG:
 * LOG: Socket modifications.
 * LOG:
 * LOG: Revision 1.20  2000/05/15 22:34:00  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 1.19  2000/05/10 23:39:50  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 * LOG: Revision 1.18  2000/03/02 16:24:15  ssharma
 * LOG:
 * LOG: Watch for type promotion in varargs (short becomes int).
 * LOG:
 * LOG: Revision 1.17  2000/02/15 20:34:46  mmiers
 * LOG:
 * LOG: Register subclasses so that we can destruct them.  This keeps the
 * LOG: class reference counting mechanism kosher.  See its_object.h for
 * LOG: details.
 * LOG:
 * LOG: Revision 1.16  2000/02/14 19:17:42  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 1.15  2000/02/10 14:48:10  mmiers
 * LOG:
 * LOG: Add functions for network/host conversion so they're always in our
 * LOG: namespace.
 * LOG:
 * LOG: Revision 1.14  2000/01/31 23:17:02  mmiers
 * LOG:
 * LOG:
 * LOG: Some GDI tweaks, some RUDP work.
 * LOG:
 * LOG: Revision 1.13  1999/12/22 02:09:01  mmiers
 * LOG:
 * LOG:
 * LOG: Finish conversion to OO methods.
 * LOG:
 * LOG: Revision 1.12  1999/12/16 21:19:56  mmiers
 * LOG:
 * LOG:
 * LOG: Complete the split.
 * LOG:
 * LOG: Revision 1.11  1999/12/16 21:15:14  mmiers
 * LOG:
 * LOG: Try to get the split right.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 00:53:00  mmiers
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:25:23  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI
 * LOG:
 * LOG: Revision 1.1.2.1  1999/12/06 21:22:45  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP GDI.
 * LOG:
 * LOG: Revision 1.1  1999/12/03 00:40:24  mmiers
 * LOG:
 * LOG:
 * LOG: Break GDI out into a different library.
 * LOG:
 * LOG: Revision 1.9  1999/12/01 19:45:40  mmiers
 * LOG:
 * LOG:
 * LOG: Make application ID more intuitive.
 * LOG:
 * LOG: Revision 1.8  1999/12/01 03:08:14  mmiers
 * LOG:
 * LOG:
 * LOG: This is more reasonable, but still questionable.
 * LOG:
 * LOG: Revision 1.7  1999/12/01 00:11:19  mmiers
 * LOG:
 * LOG:
 * LOG: Get GDI working.
 * LOG:
 * LOG: Revision 1.6  1999/11/22 19:23:31  mmiers
 * LOG:
 * LOG:
 * LOG: Cleanup from Linux build.  Removed nested comment in iniparse,
 * LOG: cleaned up decls in gdi_trans.
 * LOG:
 * LOG: Revision 1.5  1999/11/11 19:59:26  mmiers
 * LOG:
 * LOG:
 * LOG: Need netinet/in.h on HPUX (htons/ntohs)
 * LOG:
 * LOG: Revision 1.4  1999/11/10 18:27:18  mmiers
 * LOG:
 * LOG:
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.3  1999/11/10 00:09:40  mmiers
 * LOG:
 * LOG:
 * LOG: Transport extensions
 * LOG:
 * LOG: Revision 1.2  1999/11/05 20:30:07  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up first cut of GDI, remove volatile qualifier from
 * LOG: FindTransport.
 * LOG:
 * LOG: Revision 1.1  1999/10/29 20:46:08  mmiers
 * LOG:
 * LOG:
 * LOG: Initial GDI implementation.  Needs work still.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_sockets.h>
#include <its_transports.h>
#include <its_gdi_trans.h>

#ident "$Id: its_gdi_trans.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

/*
 * the class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ClientClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_CLIENT_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ClientClass_ANSI =
    (TRANSPORT_Class)&itsGDITRAN_ClientClassRec_ANSI;

ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ServerClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_SERVER_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ServerClass_ANSI =
    (TRANSPORT_Class)&itsGDITRAN_ServerClassRec_ANSI;

/*
 * the dynamic server class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_DynamicServerClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(GDITRAN_Manager),                        /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        GDITRAN_DYNAMIC_CLASS_NAME,                     /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        NULL,                                           /* instantiate */
        NULL,                                           /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_DynamicServerClass_ANSI =
    (TRANSPORT_Class)&itsGDITRAN_DynamicServerClassRec_ANSI;

/*
 * the class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ClientClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_CLIENT_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ClientClass_CCITT =
    (TRANSPORT_Class)&itsGDITRAN_ClientClassRec_CCITT;

ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ServerClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_SERVER_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ServerClass_CCITT =
    (TRANSPORT_Class)&itsGDITRAN_ServerClassRec_CCITT;

/*
 * the dynamic server class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_DynamicServerClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(GDITRAN_Manager),                        /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        GDITRAN_DYNAMIC_CLASS_NAME,                     /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        NULL,                                           /* instantiate */
        NULL,                                           /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_DynamicServerClass_CCITT =
    (TRANSPORT_Class)&itsGDITRAN_DynamicServerClassRec_CCITT;

/*
 * the class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ClientClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_CLIENT_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ClientClass_PRC =
    (TRANSPORT_Class)&itsGDITRAN_ClientClassRec_PRC;

ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ServerClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_SERVER_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ServerClass_PRC =
    (TRANSPORT_Class)&itsGDITRAN_ServerClassRec_PRC;

/*
 * the dynamic server class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_DynamicServerClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(GDITRAN_Manager),                        /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        GDITRAN_DYNAMIC_CLASS_NAME,                     /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        NULL,                                           /* instantiate */
        NULL,                                           /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_DynamicServerClass_PRC =
    (TRANSPORT_Class)&itsGDITRAN_DynamicServerClassRec_PRC;

/*
 * TTC class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ClientClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_CLIENT_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ClientClass_TTC =
    (TRANSPORT_Class)&itsGDITRAN_ClientClassRec_TTC;

ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_ServerClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(GDITRAN_Manager),                    /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        GDITRAN_SERVER_CLASS_NAME,                  /* class name */
        ITS_AddFeature,                             /* class initialize */
        ITS_RemFeature,                             /* class destroy */
        ITS_CLASS_PART_NO_INIT,                     /* class part init */
        ITS_CLASS_PART_NO_DEST,                     /* class part destroy */
        NULL,                                       /* create routine */
        NULL,                                       /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_ServerClass_TTC =
    (TRANSPORT_Class)&itsGDITRAN_ServerClassRec_TTC;

/*
 * the dynamic server class record
 */
ITSDLLAPI GDITRAN_ClassRec itsGDITRAN_DynamicServerClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(GDITRAN_Manager),                        /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        GDITRAN_DYNAMIC_CLASS_NAME,                     /* class name */
        ITS_AddFeature,                                 /* class initialize */
        ITS_RemFeature,                                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,                         /* class part init */
        ITS_CLASS_PART_NO_DEST,                         /* class part destroy */
        NULL,                                           /* instantiate */
        NULL,                                           /* destructor */
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
        SOCKTRAN_CLASS_SHUTDOWN_INHERIT,
        SOCKTRAN_CLASS_RESTART_INHERIT
    },
    /* keepalive */
    {
        KASOCKTRAN_CLASS_REGISTER_INHERIT,          /* register */
        KASOCKTRAN_CLASS_DEREGISTER_INHERIT,        /* deregister */
        NULL,                                       /* low read */
        NULL,                                       /* low write */
        KASOCKTRAN_CLASS_ENCODE_INHERIT,            /* encode/inject */
        KASOCKTRAN_CLASS_DECODE_INHERIT,            /* decode/convert */
        KASOCKTRAN_CLASS_CHECK_TIME_INHERIT,        /* keepalive time */
        KASOCKTRAN_CLASS_CHECK_EVENT_INHERIT        /* keepalive event */
    }
};

ITSDLLAPI TRANSPORT_Class itsGDITRAN_DynamicServerClass_TTC =
    (TRANSPORT_Class)&itsGDITRAN_DynamicServerClassRec_TTC;
