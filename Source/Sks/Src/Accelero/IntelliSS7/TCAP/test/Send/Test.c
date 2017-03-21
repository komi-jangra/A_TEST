/***************************************************************************
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
 *     FILE: Test.c (Send Test)                                             *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: Test.c,v 1.1.1.1 2007-10-08 11:11:29 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:50:39  cvsadmin
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
 * LOG: Revision 3.8  2000/12/22 00:38:03  mmiers
 * LOG: Tweaks
 * LOG:
 * LOG: Revision 3.7  2000/12/19 23:39:43  mmiers
 * LOG: Tweaks
 * LOG:
 * LOG: Revision 3.6  2000/12/19 23:37:50  mmiers
 * LOG: Tweaks
 * LOG:
 * LOG: Revision 3.5  2000/12/19 22:11:43  mmiers
 * LOG: Testing starting
 * LOG:
 * LOG: Revision 3.4  2000/12/19 21:08:45  mmiers
 * LOG: Cleanup
 * LOG:
 * LOG: Revision 3.3  2000/12/19 17:52:19  mmiers
 * LOG: Correct the includes
 * LOG:
 * LOG: Revision 3.2  2000/12/19 17:43:15  mmiers
 * LOG: Start testing.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:57  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/03/23 21:09:02  mmiers
 * LOG:
 * LOG:
 * LOG: Show the way.
 * LOG:
 * LOG: Revision 2.2  2000/03/10 15:25:12  mmiers
 * LOG: GDI stubs is no longer needed.  Add functions similar to what we did
 * LOG: for DECSS7 to our vendor lib.  Update test to remove mem leak.
 * LOG:
 * LOG: Revision 2.1  2000/02/23 18:51:43  mmiers
 * LOG:
 * LOG: Update this to current support levels.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:24  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.6  1998/02/26 16:23:08  mmiers
 * LOG: Update the TCAP tests to use the single ITS_Initialize() signature.  The
 * LOG: parameters are now read from a file for NMS.  The signature in its.h has
 * LOG: been consolidated to one platform-independent signature.
 * LOG:
 * LOG: Revision 1.5  1998/02/11 23:29:33  ite
 * LOG: Update to IntelliSS7 improvement.
 * LOG:
 * LOG: Revision 1.4  1998/02/06 15:41:52  ite
 * LOG: Update for header file modifications.
 * LOG:
 * LOG: Revision 1.3  1998/02/06 15:29:55  ite
 * LOG: update for changes to nms header location.
 * LOG:
 * LOG: Revision 1.2  1998/02/04 18:52:12  ite
 * LOG: Correct usage for NMS testing.
 * LOG:
 * LOG: Revision 1.1  1998/02/03 02:12:59  ite
 * LOG: Test files for IntelliSS7 at the TCAP level.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <its.h>


#include <its_app.h>
#include <its_thread.h>
#include <its_semaphore.h>
#include <its_object.h>
#include <its_sctp_trans.h>
#include <its_ss7_trans.h>
#include <its_ual.h>

#if defined(CCITT)
#include <itu/tcap.h>
#include <itu/sccp.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#include <ansi/sccp.h>
#endif

#include <sua.h>

#if defined(WIN32)
#include <windows.h>
#else
#include <signal.h>
#endif

int its_errno;
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
#else
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
        printf("thread create failed\n");

        return (result);
    }

    if (SEMA_WaitSemaphore(&syncObj) != ITS_SUCCESS)
    {
        printf("SEMA wait failed\n");

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
    ITS_USHORT dialogue_id;
    ITS_HDR hdrDlg, hdrCpt;
    ITS_EVENT ev;

    printf("initializing\n");

    APPL_SetName("SCTP");

    /*
     * using our stack, so add that feature
     */
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

    if (ITS_AddFeature(itsSCTPTRAN_Class) != ITS_SUCCESS)
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


    /*
     * start border transport
     */
    if (CreateBorderTransport() != ITS_SUCCESS)
    {
        printf("Border transport create failed.\n");

        ITS_GlobalStop();

        exit(0);
    }

#if defined(RECEIVE)
    /* don't need this to send, just to receive */

    /*
     * build the application queue.
     */
    if ((handle = ITS_Initialize(ITS_TCAP |
                                 ITS_TRANSPORT_SINGLE_USER |
                                 ITS_TRANSPORT_TQUEUE,
                                 1)) == NULL)
    {
	fprintf(stderr, "%s: %s\n", argv[0], ITS_GetErrorText(its_errno));
	perror("because: ");
	exit(0);
    }
#endif

    TCAP_AllocateDialogueId(&dialogue_id);

    memset(&hdrDlg, 0, sizeof(ITS_HDR));
    memset(&hdrCpt, 0, sizeof(ITS_HDR));

    memset(&dlg, 0, sizeof(TCAP_DLG));
    memset(&cpt, 0, sizeof(TCAP_CPT));

    hdrDlg.context.dialogue_id = dialogue_id;
    hdrCpt.context.dialogue_id = dialogue_id;


    dlg.ptype = TCAP_PT_TC_BEGIN_CCITT;

    /*
     * new style
     */
    SCCP_EncodeAddr(&dlg.u.begin.orig_addr,
                    SCCP_CPA_ROUTE_NAT | SCCP_CPA_ROUTE_SSN |
                    SCCP_CPA_HAS_PC | SCCP_CPA_HAS_SSN, /* addrInd */
                    1, /* pointCode */
                    2, /* ssn */
                    NULL, 0); /* gtt */

    SCCP_EncodeAddr(&dlg.u.begin.dest_addr,
                    SCCP_CPA_ROUTE_NAT | SCCP_CPA_ROUTE_SSN |
                    SCCP_CPA_HAS_PC | SCCP_CPA_HAS_SSN, /* addrInd */
                    2, /* pointCode */
                    2, /* ssn */
                    NULL, 0); /* gtt */

    cpt.ptype = TCPPT_TC_INVOKE;
#if defined(CCITT)
    cpt.u.invoke.opClass = 1;             /* ie. Class 1 operation */
#endif
    cpt.u.invoke.timeout = 30;            /* ie. 30 seconds */

    cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG; /* tag */
    cpt.u.invoke.invoke_id.data[1] = 1;  /* length */
    cpt.u.invoke.invoke_id.data[2] = 1;  /* value */
    cpt.u.invoke.invoke_id.len = 3;

    cpt.u.invoke.linked_id.len = 0;       /* no linked_id */

    cpt.u.invoke.operation.len = 4;
    cpt.u.invoke.operation.data[0] = TCAP_PN_LOCAL_OP_TAG_CCITT;
    /*cpt.u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP; */
    cpt.u.invoke.operation.data[1] = 2;
    cpt.u.invoke.operation.data[3] = 0x45U;
    /*cpt.u.invoke.operation.data[3] = TCPPN_OF_IS41;*/
    cpt.u.invoke.operation.data[4] = 1;

    cpt.u.invoke.param.len = 3;
    memcpy(cpt.u.invoke.param.data, "\002\001\001", 3);

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    TIMERS_Sleep(10);

    TCAP_SendComponent(handle, &hdrCpt, &cpt);

    TCAP_SendDialogue(handle, &hdrDlg, &dlg);

    memset(&ev, 0, sizeof(ITS_EVENT));

#if defined(RECEIVE)
    while (ITS_GetNextEvent(handle, &ev) == ITS_SUCCESS)
    {
    }

    ITS_Terminate(handle);
#endif

    TIMERS_Sleep(10);

    ITS_GlobalStop();

    ITS_RemFeature(itsINTELLISS7_Class);

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

