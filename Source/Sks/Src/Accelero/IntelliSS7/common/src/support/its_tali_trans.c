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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:29  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:59:18  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:46  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 03:30:36  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:39:59  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:04  mmiers
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
 * LOG: Revision 5.1  2001/08/16 20:46:12  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/02/07 22:12:56  mmiers
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
 * LOG: Revision 3.3  2000/11/09 23:04:27  mmiers
 * LOG: Routing changes are finished.
 * LOG:
 * LOG: Revision 3.2  2000/11/09 01:32:36  mmiers
 * LOG: Some cross platform issues, more comments about the new routing mech.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.9  2000/06/22 23:10:47  rsonak
 * LOG: Iterative servers cannot run protocols.
 * LOG: Fix route bugs with multilink routes.
 * LOG:
 * LOG: Revision 2.8  2000/06/02 17:19:12  mmiers
 * LOG:
 * LOG:
 * LOG: Socket changes.
 * LOG:
 * LOG: Revision 2.7  2000/05/15 22:34:02  mmiers
 * LOG:
 * LOG:
 * LOG: Add ON_CONNECT/ON_DISCONNECT functions.  Really only used by sockets
 * LOG: and fifos.
 * LOG:
 * LOG: Revision 2.6  2000/05/15 21:21:04  mmiers
 * LOG:
 * LOG:
 * LOG: Snapshot for TALI.  Almost everything but ISUP is there now.
 * LOG:
 * LOG: Revision 2.5  2000/05/13 00:56:04  mmiers
 * LOG:
 * LOG:
 * LOG: More thinking.
 * LOG:
 * LOG: Revision 2.4  2000/05/13 00:36:32  mmiers
 * LOG:
 * LOG:
 * LOG: Ok, we can read and write TALI messages, now to build the state
 * LOG: machine...
 * LOG:
 * LOG: Revision 2.3  2000/05/11 21:03:05  mmiers
 * LOG:
 * LOG:
 * LOG: Update TODO, add some comments to show how to finish TALI.
 * LOG:
 * LOG: Revision 2.2  2000/05/11 02:06:14  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 2.1  2000/05/10 23:39:51  mmiers
 * LOG:
 * LOG:
 * LOG: Common framework for TCP based protocols with heartbeats.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_sockets.h>
#include <its_transports.h>
#include <its_tali_trans.h>

#ident "$Id: its_tali_trans.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

/*
 * the class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ClientClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_CLIENT_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ClientClass_ANSI =
    (TRANSPORT_Class)&itsTALITRAN_ClientClassRec_ANSI;

ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ServerClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_SERVER_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ServerClass_ANSI =
    (TRANSPORT_Class)&itsTALITRAN_ServerClassRec_ANSI;

/*
 * the dynamic server class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_DynamicServerClassRec_ANSI =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(TALITRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        TALITRAN_DYNAMIC_CLASS_NAME,                    /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_DynamicServerClass_ANSI =
    (TRANSPORT_Class)&itsTALITRAN_DynamicServerClassRec_ANSI;

/*
 * the class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ClientClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_CLIENT_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ClientClass_CCITT =
    (TRANSPORT_Class)&itsTALITRAN_ClientClassRec_CCITT;

ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ServerClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_SERVER_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ServerClass_CCITT =
    (TRANSPORT_Class)&itsTALITRAN_ServerClassRec_CCITT;

/*
 * the dynamic server class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_DynamicServerClassRec_CCITT =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(TALITRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        TALITRAN_DYNAMIC_CLASS_NAME,                    /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_DynamicServerClass_CCITT =
    (TRANSPORT_Class)&itsTALITRAN_DynamicServerClassRec_CCITT;

/*
 * the class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ClientClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_CLIENT_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ClientClass_PRC =
    (TRANSPORT_Class)&itsTALITRAN_ClientClassRec_PRC;

ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ServerClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_SERVER_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ServerClass_PRC =
    (TRANSPORT_Class)&itsTALITRAN_ServerClassRec_PRC;

/*
 * the dynamic server class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_DynamicServerClassRec_PRC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(TALITRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        TALITRAN_DYNAMIC_CLASS_NAME,                    /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_DynamicServerClass_PRC =
    (TRANSPORT_Class)&itsTALITRAN_DynamicServerClassRec_PRC;

/*
 * TTC class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ClientClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ClientClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_CLIENT_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ClientClass_TTC =
    (TRANSPORT_Class)&itsTALITRAN_ClientClassRec_TTC;

ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_ServerClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_ServerClassRec,   /* super class */
        sizeof(TALITRAN_Manager),                   /* instance size */
        ITS_FALSE,                                  /* not initted */
        0,                                          /* initial ref count */
        TALITRAN_SERVER_CLASS_NAME,                 /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_ServerClass_TTC =
    (TRANSPORT_Class)&itsTALITRAN_ServerClassRec_TTC;

/*
 * the dynamic server class record
 */
ITSDLLAPI TALITRAN_ClassRec itsTALITRAN_DynamicServerClassRec_TTC =
{
    /* core */
    {
        (ITS_Class)&itsKASOCKTRAN_DynamicServerClassRec,/* the root object */
        sizeof(TALITRAN_Manager),                       /* instance size */
        ITS_FALSE,                                      /* not initted */
        0,                                              /* initial ref count */
        TALITRAN_DYNAMIC_CLASS_NAME,                    /* class name */
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
        TRANSPORT_INHERIT_EVENT_PROC,   /* get */
        TRANSPORT_INHERIT_EVENT_PROC,   /* peek */
        TRANSPORT_INHERIT_EVENT_PROC,   /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC     /* setExit */
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

ITSDLLAPI TRANSPORT_Class itsTALITRAN_DynamicServerClass_TTC =
    (TRANSPORT_Class)&itsTALITRAN_DynamicServerClassRec_TTC;
