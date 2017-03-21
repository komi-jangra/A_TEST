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
 * LOG: Revision 1.2  2007/03/30 04:59:09  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/06/02 06:56:06  yranade
 * LOG: Changes for Linux Kernel SCTP Integration as per ACC652-SDS-LKSC-V1.0.02.
 * LOG:
 * LOG: Revision 9.2  2005/04/01 12:01:25  ssingh
 * LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:39  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.5.2.2.6.1  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.4.2.5.2.2  2004/09/29 09:56:14  asingh
 * LOG: Changes for linux ES 30 operating system; compilation issue.
 * LOG:
 * LOG: Revision 7.4.2.5.2.1  2004/05/03 12:36:13  ssingh
 * LOG: Bug#805/776;
 * LOG: Stack dumping core while trying to send DATA to INACTIVE
 * LOG: Non Transfer messages received on stream other than zero.
 * LOG:
 * LOG: Revision 7.4.2.5  2003/10/16 13:47:39  lbana
 * LOG: incorrect patch applied on this branch.
 * LOG:
 * LOG: Revision 7.4.2.4  2003/10/15 21:02:32  lbana
 * LOG: remove transport after association lost indication.
 * LOG:
 * LOG: Revision 7.4.2.3  2003/09/12 22:53:00  lbana
 * LOG: Set isActive flag for remote transports to true|false
 * LOG:
 * LOG: Revision 7.4.2.2  2003/08/27 19:32:33  hcho
 * LOG: Set state is done in UAL.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/08/04 23:11:38  hcho
 * LOG: propagate CANT_SATRT indication to ual.
 * LOG:
 * LOG: Revision 7.4  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.3  2002/12/30 17:29:45  lbana
 * LOG: propagating bug fixes in PR6.1 to current
 * LOG:
 * LOG: Revision 7.2  2002/12/16 15:31:40  ngoel
 * LOG: set correct mask while creating remote transport
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:03  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/05/28 21:36:41  lbana
 * LOG: Initialize stack variables.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 16:15:27  omayor
 * LOG: Add reconnection code on client side of the association. Also don't
 * LOG: remove the remote if association is lost (client side only).
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.11  2002/01/10 17:37:38  mmiers
 * LOG: Finish off the refcounting code.
 * LOG:
 * LOG: Revision 5.10  2002/01/09 23:28:35  mmiers
 * LOG: Switch FindTransport to a reference counting mechanism to
 * LOG: avoid race problems.
 * LOG:
 * LOG: Revision 5.9  2002/01/09 21:21:59  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 5.8  2002/01/04 22:50:05  mmiers
 * LOG: Update SCTP code sig
 * LOG:
 * LOG: Revision 5.7  2002/01/02 23:30:55  mmiers
 * LOG: Mark the callbacks as exported.
 * LOG:
 * LOG: Revision 5.6  2001/11/15 18:07:36  mmiers
 * LOG: Add exit proc for SCTP transports.
 * LOG:
 * LOG: Revision 5.5  2001/11/15 02:02:57  mmiers
 * LOG: Note some things to do.
 * LOG:
 * LOG: Revision 5.4  2001/11/01 19:21:21  mmiers
 * LOG: Reader/writer lock problem
 * LOG:
 * LOG: Revision 5.3  2001/09/19 00:53:36  mmiers
 * LOG: Bugs found in cross platform build.
 * LOG:
 * LOG: Revision 5.2  2001/09/18 22:18:58  mmiers
 * LOG: Add internal transports API
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.38  2001/04/27 21:23:28  labuser
 * LOG: typo in AddRemoteTrans.
 * LOG:
 * LOG: Revision 3.37  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.36  2001/04/04 01:15:23  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.35  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.34  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.33  2001/02/06 00:26:00  mmiers
 * LOG: Continue adding assertions.
 * LOG:
 * LOG: Revision 3.32  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.31  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.30  2001/01/16 21:39:25  mmiers
 * LOG: Reorganize so that support is completely standalone
 * LOG:
 * LOG: Revision 3.29  2000/12/29 17:56:56  mmiers
 * LOG: Return SUCCESS, not num bytes read
 * LOG:
 * LOG: Revision 3.28  2000/12/21 21:29:10  mmiers
 * LOG: Can't pass in the addr.
 * LOG:
 * LOG: Revision 3.27  2000/12/21 20:53:00  mmiers
 * LOG: Missing payload ident.
 * LOG:
 * LOG: Revision 3.26  2000/12/21 20:37:00  mmiers
 * LOG: Old bug parsing.
 * LOG:
 * LOG: Revision 3.25  2000/12/21 18:41:40  mmiers
 * LOG: Pass management indication to codec
 * LOG:
 * LOG: Revision 3.24  2000/12/21 18:36:12  mmiers
 * LOG: Set codec and ptype on preconfigured transports
 * LOG:
 * LOG: Revision 3.23  2000/12/21 18:24:07  mmiers
 * LOG: Finish fixing address conversion
 * LOG:
 * LOG: Revision 3.22  2000/12/21 01:47:39  mmiers
 * LOG: Temp version.
 * LOG:
 * LOG: Revision 3.21  2000/12/21 00:30:28  mmiers
 * LOG: Make Get/Put return ITS error codes.
 * LOG:
 * LOG: Revision 3.20  2000/12/21 00:06:52  mmiers
 * LOG: Build remotes correctly.
 * LOG:
 * LOG: Revision 3.19  2000/12/20 23:38:43  mmiers
 * LOG: It helps if you create the transport.
 * LOG:
 * LOG: Revision 3.18  2000/12/19 23:19:39  mmiers
 * LOG: Debug section rewind
 * LOG:
 * LOG: Revision 3.17  2000/12/19 22:01:23  mmiers
 * LOG: Missing break
 * LOG:
 * LOG: Revision 3.16  2000/12/19 21:34:41  mmiers
 * LOG: Missing allocation
 * LOG:
 * LOG: Revision 3.15  2000/12/18 23:46:54  mmiers
 * LOG: Add SLS key to signature.
 * LOG:
 * LOG: Revision 3.14  2000/12/05 16:56:00  mmiers
 * LOG: Final route installment.
 * LOG:
 * LOG: Revision 3.13  2000/11/30 19:37:45  mmiers
 * LOG: Ready to debug.
 * LOG:
 * LOG: Revision 3.12  2000/11/30 17:55:55  mmiers
 * LOG: Straighten out the defines (we had overlaps)
 * LOG:
 * LOG: Revision 3.11  2000/11/29 23:38:26  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 3.10  2000/11/29 20:38:17  mmiers
 * LOG: Build on solaris.
 * LOG:
 * LOG: Revision 3.9  2000/11/29 20:35:28  mmiers
 * LOG: Use the pointers.
 * LOG:
 * LOG: Revision 3.8  2000/11/29 20:27:20  mmiers
 * LOG: Fix UNIX build warnings
 * LOG:
 * LOG: Revision 3.7  2000/11/29 18:24:42  mmiers
 * LOG: Write ok.  Think about SLS->stream.
 * LOG:
 * LOG: Revision 3.6  2000/11/29 00:59:30  mmiers
 * LOG: Got read done.  Write should be simple.
 * LOG:
 * LOG: Revision 3.5  2000/11/28 23:44:29  mmiers
 * LOG: Today's SCTPTRAN installment.  About finished, just need to create
 * LOG: remote transports when clients connect/destroy when they leave.
 * LOG:
 * LOG: Revision 3.4  2000/11/17 23:09:52  mmiers
 * LOG: clean up on SCTP some.
 * LOG:
 * LOG: Revision 3.3  2000/11/16 23:01:55  mmiers
 * LOG: Add the SCTP transport.  Getting close on this...
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: its_sctp_trans.c,v 1.1.1.1 2007-10-08 11:11:57 bsccs2 Exp $"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(WIN32)
#if defined(solaris)
#include <sys/socket.h>
#endif
#include <netinet/in.h>
#endif

#include <its_trace.h>
#include <its_sctp.h>

#include <its_sctp_trans.h>
#include <its_assertion.h>

#define LK_SCTP_CLASS_NAME  "LKSCTP"

/**
 * These two IOCTLs are used for setting socket-level
 * recv and send timeouts.
 */
#define IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT 0x0021
#define IOCTL_SET_SND_NON_BLOCKING_TIMEOUT 0x0022


/*
 * UA usage
 */
ITSDLLAPI CALLBACK_Manager    *SCTPTRAN_ManagementCallbacks = NULL;

/*
 * SCTP hooks
 */
ITS_USHORT  (*SCTP_SocketPtr)(int af, int t);
int         (*SCTP_BindPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
int         (*SCTP_ListenPtr)(ITS_USHORT sd, int backlog);
ITS_USHORT  (*SCTP_AcceptPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int *wlen);
int         (*SCTP_ConnectPtr)(ITS_USHORT sd, SOCK_AddrStore *who, int wlen);
int         (*SCTP_SendMsgPtr)(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
int         (*SCTP_RecvMsgPtr)(ITS_USHORT sd, SCTP_API_MSG_HDR *msg, int flags);
int         (*SCTP_ClosePtr)(ITS_USHORT sd);
int         (*SCTP_PendingPtr)(ITS_USHORT sd);
int         (*SCTP_IoctlPtr)(ITS_USHORT sd, int req, ...);

/*
 * codec record
 */
static SCTPTRAN_CodecRec    codecs[SCTP_PAYLOAD_MAX];

static ITS_Class lkClass = NULL;

/*
 * transport names
 */
#define SCTP_TRANSPORT_NAME "SCTP-Transport-%u"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method creates an SCTP socket
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_Open(SOCKTRAN_Manager *m)
{
    char var[1024], val[1024];
    char *tmp;
    SCTP_API_IOCTL_ARG arg;

    ITS_C_REQUIRE(m != NULL);

    /*
     * we have (already) the local port number.  So what we need is to
     * get the local bind addresses.  Further, we then need the remote
     * address(es) and port.
     */
    ITS_TRACE_DEBUG(("SCTPTRAN_Open\n"));

    lkClass = ITS_FindFeature(LK_SCTP_CLASS_NAME);

    if (lkClass != NULL)
    {
        ITS_TRACE_WARNING(("Linux Kernel SCTP Configured. \n"));
    }

    /* is SCTP around ?*/
    if (SCTP_SocketPtr == NULL || SCTP_BindPtr == NULL ||
        SCTP_ConnectPtr == NULL || SCTP_ClosePtr == NULL)
    {
        ITS_TRACE_ERROR(("SCTP missing.\n"));

        return (ITS_EINVALIDARGS);
    }

    if ((SOCKTRAN_SOURCE(m) =
            (ITS_SocketInfo *)calloc(1,
                                     sizeof(ITS_SocketInfo))) == NULL)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_Open: out of memory.\n"));

        return (ITS_ENOMEM);
    }

    /* get the socket */
    SOCKTRAN_SOURCE(m)->socket =
        (ITS_SOCKET)(*SCTP_SocketPtr)(AF_INET, SCTP_DATAGRAM_SOCK);

    if (SOCKTRAN_SOURCE(m)->socket == (ITS_SOCKET)ITS_INVALID_SRC ||
        SOCKTRAN_SOURCE(m)->socket == (ITS_SOCKET)ITS_NO_SRC)
    {
        ITS_TRACE_ERROR(("Couldn't open SCTP socket.\n"));

        return (ITS_EBADSOCKET);
    }


    /* lock the DB */
    if (RESFILE_Lock(TRANSPORT_RES(m)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't lock resource file\n"));

        (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

        return (ITS_EBADMUTEX);
    }

    if (RESFILE_Rewind(TRANSPORT_RES(m), TRANSPORT_NAME(m)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't rewind resource file\n"));

        (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

        return (ITS_EBADMUTEX);
    }

    /* get the bindings */
    while (RESFILE_GetKeyName(TRANSPORT_RES(m), TRANSPORT_NAME(m),
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(TRANSPORT_RES(m), TRANSPORT_NAME(m),
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        /* local addr? */
        if (strcmp(var, LOCAL_HOST_NAME_STRING) == 0)
        {
            /* turn it into something useful */
            if (SOCK_CreateAddr(INET_DOMAIN, val, SOCKTRAN_PORT(m),
                                &SOCKTRAN_SOURCE(m)->addr,
                                &SOCKTRAN_SOURCE(m)->asize) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't create bind addr\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }

            /* bind it */
            if ((*SCTP_BindPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                SOCKTRAN_SOURCE(m)->addr,
                                SOCKTRAN_SOURCE(m)->asize) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't bind addr\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }

            if (lkClass != NULL)
            {
                if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                     IOCTL_SET_RCV_NON_BLOCKING_TIMEOUT,
                                     &arg) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("Couldn't set recv timeout IOCTL\n"));

                    (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                    RESFILE_Unlock(TRANSPORT_RES(m));

                    return (ITS_EINVALIDARGS);
                }
                if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                     IOCTL_SET_SND_NON_BLOCKING_TIMEOUT, 
                                     &arg) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("Couldn't set send timeout IOCTL\n"));

                    (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                    RESFILE_Unlock(TRANSPORT_RES(m));

                    return (ITS_EINVALIDARGS);
                }

            }
        }
        /*
         * the next three MUST appear IN ORDER to have any effect
         */
        else if (strcmp(var, MAX_IN_STREAMS_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, NUM_OUT_STREAMS_STRING) == 0)
        {
            arg.value2 = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, MAX_ATTEMPTS_STRING) == 0)
        {
            arg.value3 = RESFILE_ParseNum(val);

            if (lkClass != NULL)
            {
                /* -1 indicates keep sending init, but in Kernel how to implement it? */
                if (arg.value3 <= -1)
                {
                    /* So set to default value, normally it is Max.Init.Retransmit */
                    arg.value3 = 0;
                }
            }
            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_INIT_DATA,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, INIT_COOKIE_LIFE_STRING) == 0)
        {
            arg.value = RESFILE_ParseNum(val);

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_INIT_COOK_LIFE,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init cookie IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, INIT_HB_ON_STRING) == 0)
        {
            arg.value = strcmp(val, "YES") == 0 ||
                        strcmp(val, "yes") == 0;

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_INIT_HB_ON,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init HB IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, INIT_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_INIT_TIMEOUT,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set init timeout IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, SEND_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_SEND_TIMEOUT,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set send timeout IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, RECV_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_RECV_TIMEOUT,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set recv timeout IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, HB_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_HB_TIMEOUT,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set hb timeout IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, SHUT_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_SHUT_TIMEOUT,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set shutdown timeout IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
        else if (strcmp(var, PMTU_TIMEOUT_STRING) == 0)
        {
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("Value must be two numbers comma separated\n"));

                continue;
            }

            *tmp = 0;
            tmp++;

            arg.value = RESFILE_ParseNum(val);
            arg.value2 = RESFILE_ParseNum(tmp);

            if ((*SCTP_IoctlPtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket,
                                 IOCTL_SET_PMTU_TIMEOUT,
                                 &arg) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't set pmtu timeout IOCTL\n"));

                (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);

                RESFILE_Unlock(TRANSPORT_RES(m));

                return (ITS_EINVALIDARGS);
            }
        }
    }

    RESFILE_Unlock(TRANSPORT_RES(m));

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method connects an SCTP socket
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_Connect(SOCKTRAN_Manager *m)
{
    ITS_C_REQUIRE(m != NULL);

    if (SCTP_ConnectPtr == NULL)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_Connect: SCTP not present\n"));

        return (ITS_ENOTRANSPORT);
    }

    if (SOCKTRAN_REMOTE_COUNT(m) != 1)
    {
        ITS_TRACE_ERROR(("SCTPTRAN_Connect: Data inconsistency\n"));

        return (ITS_EINVALIDARGS);
    }

    return (*SCTP_ConnectPtr)
               ((ITS_USHORT)SOCKTRAN_SOURCE(SOCKTRAN_REMOTES(m)[0])->socket,
                                            SOCKTRAN_CONNECT(m)->addr,
                                            SOCKTRAN_CONNECT(m)->asize);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reconnects an SCTP socket. This is used only by LK-SCTP
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History: 
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_ReConnect(SOCKTRAN_Manager *local, SOCKTRAN_Manager *remote)
{
    int i;

    ITS_TRACE_DEBUG(("SCTPTRAN_ReConnect:\n"));

    if (SOCKTRAN_RETRY_COUNT(local) == 0)
    {
        /* For SCTP Transport, No retryCount*/
        ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: Retry count = 0\n"));

        /* Let us set it for infinite */
        SOCKTRAN_RETRY_COUNT(local) = -1;
    }

    /* create the client socket */
    i = 0;
    while (SOCKTRAN_RETRY_COUNT(local) < 0 || i < SOCKTRAN_RETRY_COUNT(local))
    {
        if (TRANSPORT_EXIT_NOW(local))
        {
            ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: TRANSPORT_EXIT_NOW failed\n"));

            return (ITS_EBADSOCKET);
        }

        SCTPTRAN_Close(local);
        free(SOCKTRAN_SOURCE(local));

        if (SCTPTRAN_Open(local) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: failed to "
                             "open client socket\n"));

            i++;
            continue;
        }

        /* connect to the server */
        if (SCTPTRAN_Connect((SOCKTRAN_Manager *)remote) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("SCTPTRAN_ReConnect: connect to "
                             "server failed\n"));

            TIMERS_Sleep(5);

            i++;
            continue;
        }

        return (ITS_SUCCESS);
    }

    return (ITS_EBADSOCKET);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method closes an SCTP socket
 *
 *  Input Parameters:
 *      m - the socktran manager to use
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
SCTPTRAN_Close(SOCKTRAN_Manager *m)
{
    if (SCTP_ClosePtr == NULL)
    {
        return;
    }

    (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(m)->socket);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds a local end point.
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
 *      ITS_SUCCESS - transport built.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
static int
LocalCreate(ITS_Object h, va_list args)
{
    char buf[ITS_PATH_MAX];
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    int i;

    ITS_TRACE_DEBUG(("CreateLocal:\n"));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);

    /* Get the codec */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(h), TRANSPORT_NAME(h),
                              PAYLOAD_TYPE_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("LocalCreate: INI is missing "
                         "payload type.\n"));

        return (ITS_ENOTRANSPORT);
    }

    for (i = 0; i < SCTP_PAYLOAD_MAX; i++)
    {
        if (codecs[i].name && strcmp(codecs[i].name, buf) == 0)
        {
            SCTPTRAN_PAYLOAD(h) = codecs[i].type;
            SCTPTRAN_ENCODE(h) = codecs[i].encode;
            SCTPTRAN_DECODE(h) = codecs[i].decode;

            break;
        }
    }

    ITS_C_ASSERT(i != SCTP_PAYLOAD_MAX);

    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(h); i++)
    {
        SCTPTRAN_PAYLOAD(SOCKTRAN_REMOTES(h)[i]) = SCTPTRAN_PAYLOAD(h);
        SCTPTRAN_ENCODE(SOCKTRAN_REMOTES(h)[i]) = SCTPTRAN_ENCODE(h);
        SCTPTRAN_DECODE(SOCKTRAN_REMOTES(h)[i]) = SCTPTRAN_DECODE(h);
    }

    /* bail on no codec */
    if (i == SCTP_PAYLOAD_MAX)
    {
        ITS_TRACE_ERROR(("Codec not found\n"));

        return (ITS_ENOTRANSPORT);
    }

    /* allocate the read buffer */
    SCTPTRAN_BUFFER(h) = ITS_Malloc(65535);
    if (SCTPTRAN_BUFFER(h) == NULL)
    {
        ITS_TRACE_ERROR(("LocalCreate: out of memory\n"));

        return (ITS_ENOMEM);
    }

    if (lkClass == NULL)
    {
        return (ITS_SUCCESS);
    }

    /* Get the server state */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(h), TRANSPORT_NAME(h),
                              IS_CLIENT_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        SCTPTRAN_IS_CLIENT(h) = ITS_FALSE;
    }
    else
    {
        SCTPTRAN_IS_CLIENT(h) = strcmp(buf, "YES") == 0 ||
                                  strcmp(buf, "yes") == 0;
    }

    /* may need to listen if server */
    if (SCTPTRAN_IS_CLIENT(h))
    {
        /* IS CLIENT */
    }
    else
    {
        /* We need to Listen */
        if (SCTP_ListenPtr != NULL)
        {
            if ((*SCTP_ListenPtr)((ITS_USHORT)((SCTPTRAN_Manager *)h)->socket.source->socket,
                  SOMAXCONN) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Couldn't bind addr\n"));

                (*SCTP_ClosePtr)
                  ((ITS_USHORT)((SCTPTRAN_Manager *)h)->socket.source->socket);

                return (ITS_EINVALIDARGS);
            }
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method builds a remote end point.
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
 *      ITS_SUCCESS - transport built.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name             Date        Reference                Description
 * -------------------------------------------------------------------------
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
static int
RemoteCreate(ITS_Object obj, va_list args)
{
    char buf[ITS_PATH_MAX];
    const char *name;
    ITS_USHORT instance;
    ITS_UINT mask;
    SCTPTRAN_Manager *local;

    ITS_TRACE_DEBUG(("CreateRemote: %08x\n", obj));

    name = va_arg(args, const char *);
    instance = va_arg(args, unsigned);
    mask = va_arg(args, ITS_UINT);
    local = va_arg(args, SCTPTRAN_Manager *);

    SCTPTRAN_PAYLOAD(obj) = SCTPTRAN_PAYLOAD(local);
    SCTPTRAN_ENCODE(obj) = SCTPTRAN_ENCODE(local);
    SCTPTRAN_DECODE(obj) = SCTPTRAN_DECODE(local);

    /* Get the client state */
    if (RESFILE_GetKeyValueOf(TRANSPORT_RES(obj), TRANSPORT_NAME(obj),
                              IS_CLIENT_STRING,
                              buf, ITS_PATH_MAX) != ITS_SUCCESS)
    {
        SCTPTRAN_IS_CLIENT(obj) = ITS_FALSE;
    }
    else
    {
        SCTPTRAN_IS_CLIENT(obj) = strcmp(buf, "YES") == 0 ||
                                  strcmp(buf, "yes") == 0;
    }

    /* may need to connect */
    if (SCTPTRAN_IS_CLIENT(obj))
    {
        int retVal;

        retVal = SCTPTRAN_Connect((SOCKTRAN_Manager *)obj);

        if (lkClass != NULL)
        { 
            if (retVal != ITS_SUCCESS)
            {
                /* Reconnect */
                return(SCTPTRAN_ReConnect((SOCKTRAN_Manager *)local,
                                          (SOCKTRAN_Manager *)obj));
            }
            else
            {
                return(ITS_SUCCESS);
            }
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method adds a (possibly) new remote to the local transport.
 *
 *  Input Parameters:
 *      local - the transport to add to
 *      msg - info about the new association
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The remote added.  NULL indicates processing failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SCTPTRAN_Manager *
AddRemoteTransport(SCTPTRAN_Manager *local,
                   SCTP_API_MSG_HDR *msg)
{
    int i;
    ITS_SocketInfo a, b;
    ITS_USHORT trid;
    char buf[ITS_PATH_MAX];
    char value[ITS_PATH_MAX];
    SOCK_IPv4Addr addr;
    ITS_USHORT port;
    SCTPTRAN_Manager *ret = NULL;
    ITS_INT mask = TRANSPORT_MASK(local);

    a.type = 0;
    a.af = 0;
    a.addr = (void *)msg->name;
    a.asize = msg->nameLen;

    memset(buf,   0, sizeof(char) * ITS_PATH_MAX);
    memset(value, 0, sizeof(char) * ITS_PATH_MAX);

    ITS_TRACE_DEBUG(("AddRemote\n"));

    /* already there? */
    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(local); i++)
    {
        b.type = 0;
        b.af = 0;
        b.addr = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->addr;
        b.asize = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->asize;

        if (SOCK_AddrsAreEqual(&a, &b))
        {
            ITS_TRACE_DEBUG(("Remote already present: %d trid %08x %d\n", i,
                             SOCKTRAN_REMOTES(local)[i],
                             TRANSPORT_INSTANCE(SOCKTRAN_REMOTES(local)[i])));

            return (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
        }
    }

    /* find a slot.  Not very efficient, but we don't check that many */
    if (TRANSPORT_LockManager() != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't lock transport manager\n"));

        return (NULL);
    }

    for (trid = SCTPTRAN_FIRST_SRC; trid <= SCTPTRAN_LAST_SRC; trid++)
    {
        TRANSPORT_Control *tc;

        if ((tc = TRANSPORT_FindTransportNoLock(trid)) == NULL)
        {
            break;
        }
    }

    /* overflow */
    if (trid == SCTPTRAN_LAST_SRC + 1)
    {
        ITS_TRACE_ERROR(("Too many associations\n"));

        TRANSPORT_UnlockManager();

        return (NULL);
    }

    /* reserve this slot */
    TRANSPORT_ReserveSlot(trid);

    /* release the lock */
    TRANSPORT_UnlockManager();

    /* add the section and vars */
    sprintf(buf, SCTP_TRANSPORT_NAME, trid);

    if (RESFILE_Lock(TRANSPORT_RES(local)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't get DB lock\n"));

        return (NULL);
    }

    /* section */
    if (RESFILE_AddSection(TRANSPORT_RES(local), buf) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't add section.\n"));

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    /* variables */
    if (SOCK_GetIPv4AddrAndPort((SOCK_AddrStore *)msg->name,
                                &addr, &port) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't get addr.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    if (SOCK_IPv4AddrToName(value, addr) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't decode addr.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    /* host addr */
    if (RESFILE_AddKeyValue(TRANSPORT_RES(local), buf,
                            SERVER_PATH_STRING, value) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't add variable.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    /* port */
    sprintf(value, "%u", port);
    if (RESFILE_AddKeyValue(TRANSPORT_RES(local), buf,
                            SERVER_PORT_STRING, value) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't add variable.\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    if (SOCKTRAN_EndPointAddVirtualTransport((SOCKTRAN_Manager *)local,
                                             buf, trid,
                                             ITS_TRANSPORT_SINGLE_USER|
                                             mask) !=
        ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Failed to create remote transport\n"));

        RESFILE_RemSection(TRANSPORT_RES(local), buf);

        RESFILE_Unlock(TRANSPORT_RES(local));

        return (NULL);
    }

    RESFILE_Unlock(TRANSPORT_RES(local));

    /* we use the nolock method to avoid adding a reference */
    if (TRANSPORT_LockManager() != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Couldn't lock transport manager\n"));

        return (NULL);
    }

    ret = (SCTPTRAN_Manager *)TRANSPORT_FindTransportNoLock(trid);

    TRANSPORT_UnlockManager();

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method finds a remote from the local transport.
 *
 *  Input Parameters:
 *      local - the transport to add to
 *      msg - info about the association
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The remote found.  NULL indicates processing failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SCTPTRAN_Manager *
FindRemoteTransport(SCTPTRAN_Manager *local,
                    SCTP_API_MSG_HDR *msg)
{
    int i;
    ITS_SocketInfo a, b;

    a.type = 0;
    a.af = 0;
    a.addr = (void *)msg->name;
    a.asize = msg->nameLen;

    ITS_TRACE_DEBUG(("FindRemote\n"));

    /* Check list */
    for (i = 0; i < SOCKTRAN_REMOTE_COUNT(local); i++)
    {
        b.type = 0;
        b.af = 0;
        b.addr = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->addr;
        b.asize = SOCKTRAN_CONNECT(SOCKTRAN_REMOTES(local)[i])->asize;

        ITS_TRACE_DEBUG(("FindRemote: a %d b %d\n",
                         a.asize, b.asize));

        if (SOCK_AddrsAreEqual(&a, &b))
        {
            ITS_TRACE_DEBUG(("FindRemote: found %08x\n",
                             SOCKTRAN_REMOTES(local)[i]));

            return (SCTPTRAN_Manager *)SOCKTRAN_REMOTES(local)[i];
        }
    }

    ITS_TRACE_DEBUG(("FindRemote: no transport found\n"));

    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an ITS_EVENT from a SCTP socket.
 *
 *  Input Parameters:
 *      h - the handle to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name             Date        Reference               Description
 * -----------------------------------------------------------------------------
 * ssingh          04-01-2005  BugId: 924/770/818   Added changes along with code 
 *                             826/861/867        propagated for PAUSE/RESUME @ ASP.
 *
 * Raghavendra CE  01-06-2005  ACC652-SDS-LKSC-V1.0.02 LK-SCTP Integration
 *
 ****************************************************************************/
static int
SCTPReadEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int sz, ret;
    ITS_USHORT sd = SOCKTRAN_SOURCE(h)->socket;
    SCTP_API_MSG_HDR msg;
    SCTP_API_IOVEC iovec;
    SCTP_API_CMSG cmsg;
    SOCK_AddrStore addr;
    ITS_BOOLEAN doReturn, isManagement;
    SCTPTRAN_Manager *rem;
    ITS_OCTET sls = 0;
    SCTP_API_IOCTL_ARG arg;
    struct sockaddr_in  to;
    int flag = SCTP_API_SYNC;

    msg.name = (ITS_POINTER)&addr;
    msg.nameLen = sizeof(SOCK_AddrStore);
    msg.ioVecs = &iovec;
    msg.numIOVecs = 1;
    iovec.vector = SCTPTRAN_BUFFER(h);
    iovec.len = 65535;
    msg.control = (ITS_POINTER)&cmsg;
    msg.controlLen = sizeof(cmsg);
    cmsg.hdr.type = 0;

    sz = 0;

    ITS_TRACE_DEBUG(("SCTPReceive\n"));

    if (SCTPTRAN_DECODE(h) == NULL)
    {
        ITS_TRACE_ERROR(("SCTPReceive: no decode\n"));

        return (ITS_ERCVFAIL);
    }

    if (SCTP_RecvMsgPtr == NULL)
    {
        ITS_TRACE_WARNING(("SCTPReceive: SCTP missing\n"));

        return (ITS_ERCVFAIL);
    }

    if (lkClass != NULL)
    {
        flag = SCTP_API_ASYNC;
    }
    else
    {
        flag = SCTP_API_SYNC;
    }
    
    while ((sz = (*SCTP_RecvMsgPtr)(sd, &msg, flag)) >= 0)
    {
        doReturn = ITS_FALSE;

        switch (cmsg.hdr.type)
        {
        case SCTP_CM_DATA_IO:
            /* got data */
            ITS_TRACE_DEBUG(("Got DATA\n"));

            rem = FindRemoteTransport((SCTPTRAN_Manager *)h,
                                      &msg);

            if (rem)
            {
                ITS_TRACE_DEBUG(("Have data, send to user or MGMT\n"));

                ITS_EVENT_INIT(ev, TRANSPORT_INSTANCE(rem), sz);

                memcpy(ev->data, iovec.vector, sz);

                sls = (ITS_OCTET) cmsg.data.sndRcv.stream;

                isManagement = ITS_FALSE;

                if ((ret = SCTPTRAN_DECODE(h)(rem, ev,
                                              &isManagement, &sls)) == ITS_SUCCESS)
                {
                    if (isManagement)
                    {
                        ITS_TRACE_DEBUG(("Send to MGMT\n"));

                        TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, ev);
                    }
                    else
                    {
                        ITS_TRACE_DEBUG(("Send to user\n"));

                        doReturn = ITS_TRUE;
                    }
                }
                else
                {
                    /* only complain if the codec didn't filter */
                    if (ret != ITS_ENOMSG)
                    {
                        ITS_TRACE_DEBUG(("Decode failed\n"));
                    }
                }
            }
            break;

        case SCTP_CM_ASSOC_CHG:
            ITS_TRACE_DEBUG(("assoc changed: "));

            switch (cmsg.data.assocChg.state)
            {
            case SCTP_AC_COMM_UP:
                ITS_TRACE_DEBUG(("ASSOCIATION UP\n"));

                /* if remote not present, create/add it */
                rem = AddRemoteTransport((SCTPTRAN_Manager *)h,
                                         &msg);

                /* send open msg to UAL */
                if (rem)
                {
                    if (SCTP_IoctlPtr)
                    {
                        to.sin_addr.s_addr =
                           ((struct sockaddr_in*)(rem->socket.connect->addr))->sin_addr.s_addr;
                        to.sin_port = rem->socket.port;

                        to.sin_port = SOCK_NToHS(to.sin_port);

                        memcpy(&arg.addr, &to, sizeof(struct sockaddr_in));

                        /* get the number of available streams */
                        if (SCTP_IoctlPtr(sd, IOCTL_GET_NUM_OUT_STREAMS, &arg)
                                                                       != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("IOCTL failed to get num out streams.\n"));
                        }
                        else
                        {
                            SCTPTRAN_OUTSTREAMS(rem) = arg.value;
                        }
                    }
                    else
                    {
                        ITS_TRACE_WARNING(("IOCTL Pointer is NULL.\n"));
                    }

                    /* send open msg to UAL */
                    ITS_TRACE_DEBUG(("New remote TRANSPORT added: \n"));

                    TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_TRUE);

                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                              (ITS_POINTER)rem,
                                              (ITS_POINTER)&msg);
                }
                else
                {
                    ITS_TRACE_WARNING(("Unable to create SCTP remote\n"));
                }
                break;

            case SCTP_AC_COMM_LOST:
                ITS_TRACE_DEBUG(("ASSOCIATION DOWN\n"));

                rem = FindRemoteTransport((SCTPTRAN_Manager *)h,
                                          &msg);

                /* send close msg to UAL */
                if (rem)
                {
                    TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);

                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                              (ITS_POINTER)rem,
                                              (ITS_POINTER)&msg);
                    if (lkClass != NULL)
                    {
                        if (SCTPTRAN_IS_CLIENT(rem))
                        {
                            /* if client try to reconnect */
                            if (SCTPTRAN_Connect((SOCKTRAN_Manager *)rem) != ITS_SUCCESS)
                            {
                                /* Reconnect */
                                SCTPTRAN_ReConnect((SOCKTRAN_Manager *)h,
                                                   (SOCKTRAN_Manager *)rem);
                            }
                        }
                        else
                        {

                            /* delete the section */
                            if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                            {
                                RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                RESFILE_Unlock(TRANSPORT_RES(rem));
                            }

                            /* if remote present, remove/delete it */
                            SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)h,
                                                                 TRANSPORT_INSTANCE(rem));

                            ITS_DestructObject(rem);
                        }
                    }
                    else
                    {
                        /* delete the section */
                        if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                        {

                            RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                            RESFILE_Unlock(TRANSPORT_RES(rem));
                        }

                        if (SCTPTRAN_IS_CLIENT(rem))
                        {
                            /* if client try to reconnect */
                            (*SCTP_ConnectPtr)(sd, (SOCK_AddrStore *)msg.name, msg.nameLen);
                        }
                        else
                        {
                            /* delete the section */
                            if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                            {
                                RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                RESFILE_Unlock(TRANSPORT_RES(rem));
                            }

                            /* if remote present, remove/delete it */
                            SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)h,
                                                                 TRANSPORT_INSTANCE(rem));

                            ITS_DestructObject(rem);
                        }
                    }
                }
                break;

            case SCTP_AC_COMM_RESTART:
                ITS_TRACE_DEBUG(("ASSOCIATION RESTART\n"));

                /* if remote not present, create/add it */
                rem = AddRemoteTransport((SCTPTRAN_Manager *)h,
                                         &msg);

                /* send open msg to UAL */
                if (rem)
                {
                    if (SCTP_IoctlPtr)
                    {
                        to.sin_addr.s_addr =
                           ((struct sockaddr_in*)(rem->socket.connect->addr))->sin_addr.s_addr;
                        to.sin_port = rem->socket.port;

                        to.sin_port = SOCK_NToHS(to.sin_port);

                        memcpy(&arg.addr, &to, sizeof(struct sockaddr_in));

                        /* get the number of available streams */
                        if (SCTP_IoctlPtr(sd, IOCTL_GET_NUM_OUT_STREAMS, &arg)
                                                                       != ITS_SUCCESS)
                        {
                            ITS_TRACE_ERROR(("IOCTL failed to get num out streams.\n"));
                        }
                        else
                        {
                            SCTPTRAN_OUTSTREAMS(rem) = arg.value;
                        }
                    }
                    else
                    {
                        ITS_TRACE_WARNING(("IOCTL Pointer is NULL.\n"));
                    }

                    TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);

                    TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_TRUE);

                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                              (ITS_POINTER)rem,
                                              (ITS_POINTER)&msg);
                }
                break;

            case SCTP_AC_COMM_ABORTED:
                ITS_TRACE_DEBUG(("ASSOCIATION ABORTED\n"));

                rem = FindRemoteTransport((SCTPTRAN_Manager *)h,
                                          &msg);

                /* send close msg to UAL */
                if (rem)
                {
                    TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);

                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                              (ITS_POINTER)rem,
                                              (ITS_POINTER)&msg);
                    if (lkClass != NULL)
                    {
                        if (SCTPTRAN_IS_CLIENT(rem))
                        {
                            /* if client try to reconnect */
                            if (SCTPTRAN_Connect((SOCKTRAN_Manager *)rem) != ITS_SUCCESS)
                            {
                                /* Reconnect */
                                SCTPTRAN_ReConnect((SOCKTRAN_Manager *)h,
                                                   (SOCKTRAN_Manager *)rem);
                            }
                        }
                        else
                        {
                            /* delete the section */
                            if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                            {
                                RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                RESFILE_Unlock(TRANSPORT_RES(rem));
                             }

                            /* if remote present, remove/delete it */
                            SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)h,
                                                                 TRANSPORT_INSTANCE(rem));
                            ITS_DestructObject(rem);
                        }
                    }
                    else
                    {
                        /* delete the section */
                        if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                        {
                            RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                            RESFILE_Unlock(TRANSPORT_RES(rem));
                        }

                        if (SCTPTRAN_IS_CLIENT(rem))
                        {
                            /* if client try to reconnect */
                            (*SCTP_ConnectPtr)(sd, (SOCK_AddrStore *)msg.name, msg.nameLen);
                        }
                        else
                        {
                            /* delete the section */
                            if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                            {
                                RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                                RESFILE_Unlock(TRANSPORT_RES(rem));
                            }

                            /* if remote present, remove/delete it */
                            SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)h,
                                                                 TRANSPORT_INSTANCE(rem));
                            ITS_DestructObject(rem);
                        }
                    }
                }
                break;

            case SCTP_AC_SHUTDOWN_DONE:
                ITS_TRACE_DEBUG(("ASSOCIATION SHUTDOWN DONE\n"));

                rem = FindRemoteTransport((SCTPTRAN_Manager *)h,
                                          &msg);

                /* send close msg to UAL */
                if (rem)
                {
                    TRANSPORT_SetState((TRANSPORT_Control *)rem, ITS_FALSE);

                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                              (ITS_POINTER)rem,
                                              (ITS_POINTER)&msg);

                    /* delete the section */
                    if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                    {
                        RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                        RESFILE_Unlock(TRANSPORT_RES(rem));
                    }

                    /* if remote present, remove/delete it */
                    SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)h,
                                                         TRANSPORT_INSTANCE(rem));
                    ITS_DestructObject((ITS_Object)rem);
                }
                break;

            case SCTP_AC_CANT_START:
                ITS_TRACE_DEBUG(("ASSOCIATION CAN'T START\n"));

                /* think about this.  This maybe should be a shutdown indication */
                rem = FindRemoteTransport((SCTPTRAN_Manager *)h,
                                          &msg);

                /* send close msg to UAL */
                if (rem)
                {
                    /* delete the section */
                    if (RESFILE_Lock(TRANSPORT_RES(rem)) == ITS_SUCCESS)
                    {
                        RESFILE_RemSection(TRANSPORT_RES(rem), TRANSPORT_NAME(rem));

                        RESFILE_Unlock(TRANSPORT_RES(rem));
                    }

                    CALLBACK_CallCallbackList(SCTPTRAN_ManagementCallbacks,
                                              (ITS_POINTER)rem,
                                              (ITS_POINTER)&msg);

                    /* if remote present, remove/delete it */
                    SOCKTRAN_EndPointRemVirtualTransport((SOCKTRAN_Manager *)h,
                                                         TRANSPORT_INSTANCE(rem));
                    ITS_DestructObject(rem);
                }
                break;

            default:
                ITS_TRACE_DEBUG(("unknown state\n"));
                break;
            }
            break;

        case SCTP_CM_INTF_CHG:
            ITS_TRACE_DEBUG(("interface changed: "));

            switch (cmsg.data.intfChg.state)
            {
            case SCTP_IC_ADDR_REACHABLE:
                ITS_TRACE_DEBUG(("INTF REACHEABLE\n"));
                break;

            case SCTP_IC_ADDR_UNREACHABLE:
                ITS_TRACE_DEBUG(("INTF UNREACHEABLE\n"));
                break;

            default:
                ITS_TRACE_DEBUG(("unknown state\n"));
                break;
            }
            break;

        case SCTP_CM_SEND_FAIL:
            ITS_TRACE_DEBUG(("send fail\n"));

            break;

        case SCTP_CM_REMOTE_ERR:
            ITS_TRACE_DEBUG(("remote error: cause: %d len: %d\n",
                             cmsg.data.remErr.causeCode,
                             cmsg.data.remErr.causeLen));

            break;

        case SCTP_CM_HB_RESP:
            ITS_TRACE_DEBUG(("hb response\n"));

            break;

        default:
            ITS_TRACE_DEBUG(("unknown notification\n"));

            break;

        }

        if (doReturn)
        {
            break;
        }
    }

    if (sz <= 0)
    {
        ITS_TRACE_WARNING(("SCTP Recv failed\n"));

        return (ITS_ERCVFAIL);
    }

    return (sz);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an ITS_EVENT to a UDP socket.
 *
 *  Input Parameters:
 *      h - the handle to write into
 *      ev - the buffer to send
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - message read.
 *
 *  Notes:
 *      RemoteEndPoints are write only.  LocalEndPoints are read only.
 *      The SOURCE field in a remote is a pointer to the associated
 *      local's SOURCE.  The CONNECT field in local is a scratch buffer.
 *      The CONNECT field in a remote is the remote port addr.
 *
 *  See Also:
 ****************************************************************************/
static int
SCTPWriteEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    SCTP_API_MSG_HDR msg;
    SCTP_API_IOVEC iovec;
    SCTP_API_CMSG cmsg;
    SOCK_AddrStore addr;
    ITS_USHORT sd = SOCKTRAN_SOURCE(h)->socket;
    ITS_BOOLEAN isManagement;
    ITS_OCTET sls;
    int ret;

    ITS_TRACE_DEBUG(("WriteEvent:\n"));

    if (SCTPTRAN_ENCODE(h) == NULL)
    {
        return (ITS_ESENDFAIL);
    }

    if (ev->src == UAL_MANAGER_INSTANCE)
    {
        isManagement = ITS_TRUE;
    }
    else
    {
        isManagement = ITS_FALSE;
    }

    if ((ret = SCTPTRAN_ENCODE(h)(h, ev,
                                  &isManagement, &sls)) != ITS_SUCCESS)
    {
        if (ret == ITS_ENOMSG || ret == ITS_EBADSTATE)
        {
            /* This is ok, the codec is filtering */
            /* return event lengh for ITS_SUCCESS */
            return (ev->len);
        }

        return (ITS_EINVALIDARGS);
    }

    memcpy(&addr, SOCKTRAN_CONNECT(h)->addr, SOCKTRAN_CONNECT(h)->asize);

    msg.name = (ITS_POINTER)&addr;
    msg.nameLen = sizeof(SOCK_AddrStore);
    msg.ioVecs = &iovec;
    msg.numIOVecs = 1;
    iovec.vector = (ITS_POINTER)ev->data;
    iovec.len = ev->len;
    msg.control = (ITS_POINTER)&cmsg;
    msg.controlLen = sizeof(cmsg);
    cmsg.hdr.len = sizeof(SCTP_API_SND_RCV);
    cmsg.hdr.type = SCTP_CM_DATA_IO;
    cmsg.hdr.level = 0;
    cmsg.data.sndRcv.stream = sls;
    cmsg.data.sndRcv.flags = 0;
    cmsg.data.sndRcv.payload = SCTPTRAN_PAYLOAD(h);

    return (*SCTP_SendMsgPtr)(sd, &msg, SCTP_API_SYNC);
}

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
    if (MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(ft)) != ITS_SUCCESS)
    {
        ITS_TRACE_CRITICAL(("Shutdown: mutex corrupted\n"));
        abort();
    }

    if (!SOCKTRAN_IS_VALID(ft))
    {
        MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ft));

        return;
    }

    if (TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft)))
    {
        TRANSPORT_CLASS_ON_DISCONNECT(ITS_OBJ_CLASS(ft))(ft);
    }

    SOCKTRAN_IS_VALID(ft) = ITS_FALSE;

    TRANSPORT_IS_ACTIVE(TRANSPORT(ft)) = ITS_FALSE;

    TRANSPORT_SetState(TRANSPORT(ft), ITS_FALSE);

    if (ITS_IsInstanceOf((ITS_Class)itsSOCKTRAN_ServerClass,
                         (ITS_Object)ft) ||
        ITS_IsInstanceOf((ITS_Class)itsSOCKTRAN_DynamicServerClass,
                         (ITS_Object)ft))
    {
        SOCKTRAN_SOURCE(ft)->addr = NULL;
    }

    if (SCTP_ClosePtr != NULL)
    {
        (*SCTP_ClosePtr)((ITS_USHORT)SOCKTRAN_SOURCE(ft)->asize);
    }

    SOCKTRAN_SOURCE(ft) = NULL;

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(ft));
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
    if (SOCKTRAN_IS_VALID(ft))
    {
        return;
    }

    SOCKTRAN_IS_VALID(ft) = ITS_TRUE;

    if (TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft)))
    {
        TRANSPORT_CLASS_ON_CONNECT(ITS_OBJ_CLASS(ft))(ft);
    }

    TRANSPORT_IS_ACTIVE(TRANSPORT(ft)) = ITS_TRUE;

    /* TRANSPORT_SetState(TRANSPORT(ft), ITS_TRUE); */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalGetNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = SOCKTRAN_READ_EVENT(h)(h, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    if (ret < 0)
    {
        return (ITS_ERCVFAIL);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method reads an event from a local end point, if a message
 *      is pending
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
LocalPeekNextEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if (!SCTP_PendingPtr)
    {
        return (ITS_EINVALIDARGS);
    }

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_RMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    if ((*SCTP_PendingPtr)((ITS_USHORT)SOCKTRAN_SOURCE(h)->socket))
    {
        ret = SOCKTRAN_READ_EVENT(h)(h, ev);

        if (ret < 0)
        {
            MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

            return (ITS_ERCVFAIL);
        }
    }
    else
    {
        ret = ITS_ENOMSG;
    }

    MUTEX_ReleaseMutex(&SOCKTRAN_RMUTEX(h));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Set the exit flag on a transport.
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      doExit - ITS_TRUE to mark the transport to exit
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
SetExit(ITS_HANDLE tr, ITS_BOOLEAN doExit)
{
    TRANSPORT_Control *tc;

    TRANSPORT_EXIT_NOW(tr) = doExit;

    /*
     * this is tricky.  The SCTP transport is dual layer; the socket
     * layer hides the underlying task queue.  This code sets the exit
     * flag on the task queue.
     */
    ITS_C_ASSERT(SOCKTRAN_SOURCE(tr) != NULL);

    tc = TRANSPORT_FindTransport((ITS_USHORT)SOCKTRAN_SOURCE(tr)->socket);

    TRANSPORT_UnfindTransport(tc);

    TRANSPORT_SetExit(tc, doExit);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method writes an event to a remote end point
 *
 *  Input Parameters:
 *      h - the SOCKTRAN to read from
 *      ev - the buffer to read into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - operation successful
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RemotePutEvent(ITS_HANDLE h, ITS_EVENT *ev)
{
    int ret;

    if ((ret = MUTEX_AcquireMutex(&SOCKTRAN_WMUTEX(h))) != ITS_SUCCESS)
    {
        return (ret);
    }

    ret = SOCKTRAN_WRITE_EVENT(h)(h, ev);

    MUTEX_ReleaseMutex(&SOCKTRAN_WMUTEX(h));

    if (ret != ev->len)
    {
        return (ITS_ESENDFAIL);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method return an error. Used for mapping GetNextEvent, 
 *      PeeknextEvent and PutEvent in the Iterative Server.
 *
 *  Input Parameters:
 *      event - a reference to an ITS_Event to send to the remote end
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the data is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ReturnErrorFunction(ITS_HANDLE h, ITS_EVENT* event)
{
    return !ITS_SUCCESS;
}

/*
 * forward
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSCTPTRAN_RemoteEndPointClassRec;

static SOCKTRAN_ClassExtRec SCTPReadWrite =
{
    /* core class */
    {
        ITS_EXT_VERSION
    },
    /* socket class */
    {
        SCTPReadEvent,                      /* Read one */
        SCTPWriteEvent,                     /* Write one */
        &itsSCTPTRAN_RemoteEndPointClassRec /* associate */
    }
};

/*
 * the SCTP class record(s)
 */
ITSDLLAPI SOCKTRAN_ClassRec itsSCTPTRAN_LocalEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_LocalEndPointClassRec,  /* the root object */
        sizeof(SCTPTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SCTPTRAN_LOCAL_ENDPOINT_CLASS_NAME,     /* class name */
        ITS_AddFeature,                         /* no class initialize */
        ITS_RemFeature,                         /* no class destructor */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        LocalCreate,                            /* instantiate */
        ITS_INST_NO_DEST,                       /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&SCTPReadWrite            /* extension */
    },
    /* transport */
    {
        LocalGetNextEvent,              /* get next */
        LocalPeekNextEvent,             /* peek next */
        ReturnErrorFunction,            /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        SetExit                         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSCTPTRAN_LocalEndPointClass =
    (TRANSPORT_Class)&itsSCTPTRAN_LocalEndPointClassRec;

ITSDLLAPI SOCKTRAN_ClassRec itsSCTPTRAN_RemoteEndPointClassRec =
{
    /* core */
    {
        (ITS_Class)&itsSOCKTRAN_RemoteEndPointClassRec,  /* the root object */
        sizeof(SCTPTRAN_Manager),               /* instance size */
        ITS_FALSE,                              /* not initted */
        0,                                      /* initial ref count */
        SCTPTRAN_REMOTE_ENDPOINT_CLASS_NAME,    /* class name */
        ITS_AddFeature,                         /* no class initialize */
        ITS_RemFeature,                         /* no class destructor */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        RemoteCreate,                           /* instantiate */
        ITS_INST_NO_DEST,                       /* destructor */
        ITS_INST_CLONE_INHERIT,                 /* inherit clone */
        ITS_INST_PRINT_INHERIT,                 /* inherit print */
        ITS_INST_SERIAL_INHERIT,                /* inherit serial */
        ITS_INST_EQUALS_INHERIT,                /* inherit equals */
        ITS_INST_HASH_INHERIT,                  /* inherit equals */
        (ITS_ClassExt)&SCTPReadWrite            /* extension */
    },
    /* transport */
    {
        ReturnErrorFunction,            /* getNext */
        ReturnErrorFunction,            /* peekNext */
        RemotePutEvent,                 /* put */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onConnect */
        TRANSPORT_INHERIT_HANDLE_PROC,  /* onDisconnect */
        TRANSPORT_INHERIT_EXIT_PROC         /* setExit */
    },
    /* socktran */
    {
        Shutdown,
        Restart
    }
};

ITSDLLAPI TRANSPORT_Class itsSCTPTRAN_RemoteEndPointClass =
    (TRANSPORT_Class)&itsSCTPTRAN_RemoteEndPointClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Register a codec here.
 *
 *  Input Parameters:
 *      ptype - the codec type
 *      encode - the encode function
 *      decode - the decode function
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the codec is added, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_RegisterCodec(char *name, SCTP_PAYLOAD ptype,
                       SCTP_CodecPtr encode, SCTP_CodecPtr decode)
{
    if (ptype > SCTP_PAYLOAD_MAX || encode == NULL || decode == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    if (codecs[ptype].name != NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    codecs[ptype].name = strdup(name);
    codecs[ptype].type = ptype;
    codecs[ptype].encode = encode;
    codecs[ptype].decode = decode;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method return an error. Used for mapping GetNextEvent, 
 *      PeeknextEvent and PutEvent in the Iterative Server.
 *
 *  Input Parameters:
 *      event - a reference to an ITS_Event to send to the remote end
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the data is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SCTPTRAN_DeregisterCodec(char *name)
{
    int i;

    if (name == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    for (i = 0; i < SCTP_PAYLOAD_MAX; i++)
    {
        if (codecs[i].name && strcmp(codecs[i].name, name) == 0)
        {
            free(codecs[i].name);

            codecs[i].name = NULL;
            codecs[i].type = 0;
            codecs[i].encode = NULL;
            codecs[i].decode = NULL;
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the SCTP transport subsytem.
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
 *      If the routing subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("Initialize\n"));

    SCTPTRAN_ManagementCallbacks = CALLBACK_InitManager();

    if (SCTPTRAN_ManagementCallbacks == NULL)
    {
        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the SCTP transport subsystem.
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
 *      ROUTE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("Terminate:\n"));

    CALLBACK_DestroyManager(SCTPTRAN_ManagementCallbacks);
}

ITSDLLAPI ITS_ClassRec itsSCTPTRAN_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        SCTPTRAN_CLASS_NAME,            /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsSCTPTRAN_Class = &itsSCTPTRAN_ClassRec;
