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
 * CONTRACT: TCAP                                                           *
 *                                                                          *
 *     FILE: Test.c (Receive Test)                                          *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: Test.c,v 1.1.1.1 2007-10-08 11:11:28 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:58  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:55  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:33  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:34  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:53  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2000/12/19 23:37:50  mmiers
 * LOG: Tweaks
 * LOG:
 * LOG: Revision 3.5  2000/12/19 22:13:03  mmiers
 * LOG: False positive?
 * LOG:
 * LOG: Revision 3.4  2000/12/19 20:00:25  mmiers
 * LOG: Add Makefiles
 * LOG:
 * LOG: Revision 3.3  2000/12/19 17:52:19  mmiers
 * LOG: Correct the includes
 * LOG:
 * LOG: Revision 3.2  2000/12/19 17:43:15  mmiers
 * LOG: Start testing.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:55  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/03/23 20:21:31  mmiers
 * LOG:
 * LOG:
 * LOG: Final IntelliSS7 changes from Plano.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:30  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:20  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1998/02/26 16:23:07  mmiers
 * LOG: Update the TCAP tests to use the single ITS_Initialize() signature.  The
 * LOG: parameters are now read from a file for NMS.  The signature in its.h has
 * LOG: been consolidated to one platform-independent signature.
 * LOG:
 * LOG: Revision 1.4  1998/02/11 23:29:32  ite
 * LOG: Update to IntelliSS7 improvement.
 * LOG:
 * LOG: Revision 1.3  1998/02/06 15:29:21  ite
 * LOG: Update for changes to sccp.h include location.
 * LOG:
 * LOG: Revision 1.2  1998/02/04 18:52:12  ite
 * LOG: Correct usage for NMS testing.
 * LOG:
 * LOG: Revision 1.1  1998/02/03 02:12:58  ite
 * LOG: Test files for IntelliSS7 at the TCAP level.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <its.h>

#if defined(USE_INTELLINET_STACK)

#include <its_app.h>
#include <its_thread.h>
#include <its_semaphore.h>
#include <its_object.h>
#include <its_sctp_trans.h>
#include <its_ss7_trans.h>
#include <its_ual.h>

#endif

#if defined(CCITT)
#include <itu/sccp.h>
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/sccp.h>
#include <ansi/tcap.h>
#endif

#include <sua.h>

#if defined(WIN32)
#include <windows.h>
#else
#include <signal.h>
#endif

static void dumpHexa(unsigned char* ptrDumpArea, int length);
static int debug_dump = 1;

ITS_HANDLE handle = NULL;

#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
{
    if (handle)
    {
        ITS_Terminate(handle);
    }

    exit(0);

    return 1;
}
#elif defined(unix)
static void exitHandler(int sig)
{
    if (handle)
    {
        ITS_Terminate(handle);
    }

    exit(0);
}
#endif


ITS_THREAD      receiveThread;
ITS_SEMAPHORE   syncObj;


THREAD_RET_TYPE
BorderDispatch(void *arg)
{
    ITS_HANDLE h;
    ITS_EVENT ev;

    h = ITS_Initialize(ITS_TCAP |
                       ITS_TRANSPORT_SCTP_SOCKET |
                       ITS_TRANSPORT_DATAGRAM |
                       ITS_TRANSPORT_SINGLE_USER,
                       2);

    if (h == NULL)
    {
        THREAD_NORMAL_EXIT;
    }

    SEMA_PostSemaphore(&syncObj);

    while (ITS_GetNextEvent(h, &ev) == ITS_SUCCESS)
    {
        ev.src = ITS_MTP3_SRC;

        TRANSPORT_PutEvent(ITS_SCCP_SRC, &ev);
    }

    THREAD_NORMAL_EXIT;
}


int
CreateBorderTransport()
{
    int result;

    if (SEMA_CreateSemaphore(&syncObj, 0) != ITS_SUCCESS)
    {
        return (ITS_EBADSEMAPHORE);
    }

    /* starting the Receiving Thread first */
    result = THREAD_CreateThread(&receiveThread, 0,
                                 BorderDispatch,
                                 NULL, ITS_TRUE);

    if (result != ITS_SUCCESS)
    {
        return (result);
    }

    if (SEMA_WaitSemaphore(&syncObj) != ITS_SUCCESS)
    {
        THREAD_KillThread(&receiveThread);

        return (ITS_EBADSEMAPHORE);
    }

    SEMA_DeleteSemaphore(&syncObj);

    return (ITS_SUCCESS);
}



int
main(int argc, char** argv)
{
    TCAP_CPT cpt;
    TCAP_DLG dlg;
    ITS_HDR hdrDlg, hdrCpt;
    ITS_EVENT ev;

    printf("initializing\n");

    APPL_SetName("SCTP");

    if (ITS_AddFeature(itsINTELLISS7_Class) != ITS_SUCCESS)
    {
        printf("Failed to add stack feature.\n");
        exit(0);
    }

    if (ITS_AddFeature(itsSCTP_Class) != ITS_SUCCESS)
    {
        printf("Failed to add SCTP feature.\n");
        exit(0);
    }

    if (ITS_AddFeature(itsSUA_Class) != ITS_SUCCESS)
    {
        printf("Failed to add UAL feature.\n");
        exit(0);
    }

    if (ITS_AddFeature(itsUAL_Class) != ITS_SUCCESS)
    {
        printf("Failed to add UAL feature.\n");
        exit(0);
    }

    if (ITS_GlobalStart(ITS_TCAP_CCITT | ITS_SCCP_ANSI | ITS_MTP3_ANSI) != ITS_SUCCESS)
    {
        printf("Global start failed.\n");
        exit(0);
    }

    if (CreateBorderTransport() != ITS_SUCCESS)
    {
        printf("Border transport create failed.\n");

        ITS_GlobalStop();

        exit(0);
    }


    if ((handle = ITS_Initialize(ITS_TCAP|
                                 ITS_TRANSPORT_SINGLE_USER |
                                 ITS_TRANSPORT_TQUEUE,
                                 1)) == NULL)
    {
        perror("Failed to initilalize: ");

        exit(0);
    }

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#elif defined(unix)
    signal(SIGINT, exitHandler);
#endif

    memset(&dlg, 0, sizeof(TCAP_DLG));
    memset(&cpt, 0, sizeof(TCAP_CPT));
    memset(&hdrDlg, 0, sizeof(ITS_HDR));
    memset(&hdrCpt, 0, sizeof(ITS_HDR));

    memset(&ev, 0, sizeof(ITS_EVENT));

    while (1)
    {
        ITS_GetNextEvent(handle, &ev);

        printf("Got event. Src: <%d>.\n", ev.src);

        switch (ev.src)
        {
        case ITS_TCAP:

            switch (TCAP_MSG_TYPE(&ev))
            {
            case ITS_TCAP_CPT:
                TCAP_ReceiveComponent(handle, &ev, &hdrCpt, &cpt);
                printf("Got component. Type: <%d>.\n", cpt.ptype);
                switch (cpt.ptype)
                {
                case TCPPT_TC_INVOKE:
                    if (cpt.u.invoke.param.len > 0)
                    {
                        int i;

                        for (i = 0; i < cpt.u.invoke.param.len; i++)
                        {
                            ITS_OCTET tmp1 = cpt.u.invoke.param.data[i] & 0x0FU;
                            ITS_OCTET tmp2 = (cpt.u.invoke.param.data[i] >> 4) & 0x0FU;

                            putchar((tmp2 >= 10) ? ('A' + tmp2 - 10) : ('0' + tmp2));
                            putchar((tmp1 >= 10) ? ('A' + tmp1 - 10) : ('0' + tmp1));
                        }
                    }
                    else
                    {
                        /* NO DATA */
                    }
                }
                break;

            case ITS_TCAP_DLG:
                TCAP_ReceiveDialogue(handle, &ev, &hdrDlg, &dlg);
                printf("Got dialogue. Type: <%d>.\n", dlg.ptype);
                printf("DialogueId: <%d>.\n", hdrDlg.context.dialogue_id);
                hdrCpt.context.dialogue_id = hdrDlg.context.dialogue_id;
                break;
            default:
                break;
            }
            break;

        default: /* UNKNOWN SOURCE */
            break;
        }
    }

    return EXIT_SUCCESS;
}

/*
 * Debug utility.
 */

void dumpHexa(unsigned char* ptrDumpArea, int length)
{
    unsigned char* ptr = NULL;
    int i, j;

    ptr = ptrDumpArea;

    printf("\n");

    for (i = 0; i < length / 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            printf("%02X ", *(ptr++));
        }

        printf("\n");
    }

    for (j = 0; j < length % 10; j++)
    {
        printf("%02X ", *(ptr++));
    }

    printf("\n");
}
