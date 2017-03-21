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
 *  ID: $Id: test2.cpp,v 1.1.1.1 2007-10-08 11:11:28 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:57  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:32  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
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
 * LOG: Revision 3.7  2000/09/02 01:39:31  mmiers
 * LOG: Use default value for MAKE, update tests.
 * LOG:
 * LOG: Revision 3.6  2000/09/01 23:31:38  lbana
 * LOG:
 * LOG:
 * LOG: Tracking down bugs.
 * LOG:
 * LOG: Revision 3.5  2000/09/01 20:56:30  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.4  2000/08/31 19:18:39  lbana
 * LOG: Something foul here.
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:06:34  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 18:53:28  mmiers
 * LOG: Track down the KDD problem.  The MEMPOOL is really finding some tricky
 * LOG: bugs.
 * LOG:
 * LOG: Revision 1.20  1999/12/01 00:11:18  mmiers
 * LOG:
 * LOG:
 * LOG: Get GDI working.
 * LOG:
 * LOG: Revision 1.19  1999/11/29 16:19:45  mmiers
 * LOG:
 * LOG:
 * LOG: Don't block on transport create.
 * LOG:
 * LOG: Revision 1.18  1999/11/10 21:21:42  mmiers
 * LOG:
 * LOG:
 * LOG: Correct tests.
 * LOG:
 * LOG: Revision 1.17  1999/08/06 14:50:57  mmiers
 * LOG:
 * LOG:
 * LOG: Remove SetComponentPresent().  This member is always populated
 * LOG: by the stack, and should be read-only to the user.
 * LOG:
 * LOG: Revision 1.16  1999/08/05 17:04:31  mmiers
 * LOG:
 * LOG:
 * LOG: Include a parameter in the test message.
 * LOG:
 * LOG: Revision 1.15  1999/07/30 16:13:06  mmiers
 * LOG:
 * LOG:
 * LOG: Add old signature back in, make new one explicit.  Compilation couldn't
 * LOG: tell the difference between the two.
 * LOG:
 * LOG: Revision 1.14  1999/06/21 16:18:07  mmiers
 * LOG:
 * LOG:
 * LOG: Get the ITU test running.
 * LOG:
 * LOG: Revision 1.13  1999/06/18 22:50:56  mmiers
 * LOG:
 * LOG:
 * LOG: Update ITU definitions for sanity.
 * LOG:
 * LOG: Revision 1.12  1999/06/18 21:31:05  mmiers
 * LOG:
 * LOG:
 * LOG: Update the tests for correct function.
 * LOG:
 * LOG: Revision 1.11  1999/03/25 00:16:32  mmiers
 * LOG:
 * LOG:
 * LOG: Update for new TCAP.
 * LOG:
 * LOG: Revision 1.10  1999/03/24 23:50:03  mmiers
 * LOG:
 * LOG:
 * LOG: Update build configurations.
 * LOG:
 * LOG: Revision 1.9  1999/03/24 17:40:56  mmiers
 * LOG:
 * LOG:
 * LOG: Start updating the tests.
 * LOG:
 * LOG: Revision 1.8  1998/07/08 20:01:53  mmiers
 * LOG: Fix some buggy comments Hongling identified.
 * LOG:
 * LOG: Revision 1.7  1998/07/07 21:12:32  mmiers
 * LOG: Fixes for timers and TCAP cancels.
 * LOG:
 * LOG: Revision 1.6  1998/07/07 15:22:04  mmiers
 * LOG: Change the TCAP tests to reflect current status.
 * LOG:
 * LOG: Revision 1.5  1998/06/26 16:31:24  mmiers
 * LOG: Complete the transport conversion.
 * LOG:
 * LOG: Revision 1.4  1998/06/24 16:12:29  mmiers
 * LOG: Straighten out the tranport vs. worker issues.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:00  mmiers
 * LOG: Reaching the end of TCAP.  Initial SCCP implementation.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 23:39:31  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.1  1998/06/16 21:52:12  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.4  1998/06/16 00:00:22  mmiers
 * LOG: Beaucoup bug fix day.  Start unit testing TCAP, which caught most
 * LOG: of these.
 * LOG:
 * LOG: Revision 1.3  1998/06/15 16:43:55  mmiers
 * LOG: How to exit gracefully.
 * LOG:
 * LOG: Revision 1.2  1998/06/15 16:29:06  mmiers
 * LOG: Testing TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/06/15 15:53:01  mmiers
 * LOG: Add a TCAP unit test.
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <its++.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <exception>
#include <iostream>

#include <its_app.h>
#include <its_timers.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_worker.h>
#include <its_exception.h>
#include <its_timers.h>
#include <its_gdi_trans.h>
#include <its_imal_trans.h>
#include <its_ss7_trans.h>
#include <its_tq_trans.h>

#include <sccp++.h>
#include <tcap++.h>

#include <UnitTest.h>

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

using namespace std;

TCAP_End end;
//
// comm
//
ITS_Worker*     trin;
ITS_Worker*     trout;

//
// local subsystem for testing
#define LOCAL_PC    0x01
#define REMOTE_PC   0x0
#define LOCAL_SSN   2
#define REMOTE_SSN  2

//
// address indicator
//
#define ADDR_IND    (SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|\
                     SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN)

//
// termination handler
//
#if defined(WIN32)
static BOOL WINAPI breakHandler(DWORD ctrlType)
#else
static void exitHandler(int sig)
#endif
{
    ITS_GlobalStop();

    exit(0);

#if defined(WIN32)
    return 1;
#endif
}

//
// unit tester derived class
//
class TCAPUnitTest : public UnitTest
{
public:
    TCAPUnitTest() : UnitTest("TCAPUnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};



void
TCAPUnitTest::DoCommand(istream& cmdLine)
{
    static ITS_USHORT idid;

    if (Cmd("GetMTP3Event", "GetMTP3Event", ""))
    {
        ITS_Event ev;
        int ret;

        if ((ret = trout->GetNextEvent(ev)) != ITS_SUCCESS)
        {
            cout << "GetNextMTP3Event() failed. " << ret << endl;

            return;
        }

        cout << "Event came from: " << ev.GetSource() << endl;
        cout << "The length was:  " << ev.GetLength() << endl;

#if defined(PRINT_DATA)
        int i;
        for (i = 0; i < ev.GetLength(); i++)
        {
            printf("%02x ", ev.GetData()[i]);
            if (!((i+1) % 25))
            {
                printf("\n");
            }
        }
        if ((i+1) % 25)
        {
            printf("\n");
        }
#endif

        cout << "Sending to SCCP..." << endl;
        ev.SetSource(ITS_MTP3_SRC);
        ITS_Transport::PutEvent(ITS_SCCP_SRC, ev);
    }
    else if (Cmd("GetTCAPEvent", "GetTCAPEvent", ""))
    {
        ITS_Event ev;
        static TCAP_Dialogue *dlg = NULL;
        static TCAP_Component *cpt = NULL;
        int ret;

repeat:
        if ((ret = trin->GetNextEvent(ev)) != ITS_SUCCESS)
        {
            cout << "GetNextTCAPEvent failed. " << ret << endl;

            return;
        }

        cout << "Event came from: " << ev.GetSource() << endl;
        cout << "The length was:  " << ev.GetLength() << endl;

#if defined(PRINT_DATA)
        int i;
        for (i = 0; i < ev.GetLength(); i++)
        {
            printf("%02x ", ev.GetData()[i]);
            if (!((i+1) % 25))
            {
                printf("\n");
            }
        }
        if ((i+1) % 25)
        {
            printf("\n");
        }
#endif

        if (TCAP_MSG_TYPE(&ev.GetEvent()) == ITS_TCAP_CPT)
        {
            TCAP_Component::Receive((ITS_HANDLE)trin->GetTransport()->GetTC(), ev, &end, &cpt);

            if (cpt->GetComponentType() == TCPPT_TC_L_CANCEL)
            {
                delete cpt;

                goto repeat;
            }

            delete cpt;
        }
        else if (TCAP_MSG_TYPE(&ev.GetEvent()) == ITS_TCAP_DLG)
        {
            TCAP_Dialogue::Receive((ITS_HANDLE)trin->GetTransport()->GetTC(), ev, &dlg);

            printf("Got dialogue: DID is %04x\n", dlg->GetDialogueID());
            idid = dlg->GetDialogueID();

            delete dlg;
        }
    }
    else if (Cmd("SendInvoke", "SendInvoke", ""))
    {
        TCAP_Invoke inv;
        TCAP_Begin beg;
        ITS_USHORT did;

        if (TCAP_AllocateDialogueId(&did) != ITS_SUCCESS)
        {
            abort();
        }

        printf("Send DID %04x\n", did);

        beg.SetDialogueID(did);
        beg.SetOrigAddr(ADDR_IND, LOCAL_PC, LOCAL_SSN, NULL, 0);
        beg.SetDestAddr(ADDR_IND, REMOTE_PC, REMOTE_SSN, NULL, 0);

        inv.SetInvokeID(1);
#if defined(CCITT)
        inv.SetOperation(0);
        inv.SetClass(1);
#elif defined(ANSI)
        inv.SetOperation(false, 0, 0);
#else
#error "Protocol family not defined."
#endif
        ITS_OCTET param[3] = { 0x02, 0x01, 0x00 };

        inv.SetParameter(param, sizeof(param));

        inv.SetTimeOut(10);

        TCAP_Component::Send((ITS_HANDLE)trin->GetTransport()->GetTC(), &beg, &inv);
        TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport()->GetTC(), &beg);
    }
    else if (Cmd("SendResult", "SendResult", ""))
    {
        TCAP_Result res;
        TCAP_End resp;

        resp.SetDialogueID(idid);

        res.SetInvokeID(1);
#if defined(CCITT)
        res.SetOperation(0);
#endif
        ITS_OCTET param[3] = { 0x02, 0x01, 0xFF };

        res.SetParameter(param, sizeof(param));


        TCAP_Component::Send((ITS_HANDLE)trin->GetTransport()->GetTC(), &resp, &res);
        TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport()->GetTC(), &resp);
    }
    else if (Cmd("SendBegin", "SendBegin", ""))
    {
        TCAP_Begin beg;
        ITS_USHORT did;

        if (TCAP_AllocateDialogueId(&did) != ITS_SUCCESS)
        {
            abort();
        }

        printf("Send DID %04x\n", did);

        beg.SetDialogueID(did);
        beg.SetOrigAddr(ADDR_IND, LOCAL_PC, LOCAL_SSN, NULL, 0);
        beg.SetDestAddr(ADDR_IND, REMOTE_PC, REMOTE_SSN, NULL, 0);

        TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport()->GetTC(), &beg);
    }
    else if (Cmd("SendEnd", "SendEnd", ""))
    {
        TCAP_End end;
        TCAP_Invoke inv;

        inv.SetInvokeID(2);
#if defined(CCITT)
        inv.SetOperation(0);
        inv.SetClass(4);
#elif defined(ANSI)
        inv.SetOperation(true, 1, 1);
#else
#error "Protocol family not defined."
#endif
        ITS_OCTET param[5] = { 0x30, 0x03, 0x02, 0x01, 0x01 };

        inv.SetParameter(param, sizeof(param));

        //inv.SetTimeOut(30);

        end.SetDialogueID(idid);

        TCAP_Component::Send((ITS_HANDLE)trin->GetTransport()->GetTC(), &end, &inv);
        TCAP_Dialogue::Send((ITS_HANDLE)trin->GetTransport()->GetTC(), &end);
    }
}

//
// and the entry point.
//
int
main(int argc, char **argv)
{
#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    ITS_Application::SetName("Test2");

    ITS_AddFeature(itsINTELLISS7_Class);
    ITS_AddFeature(itsKEEPALIVE_Class);
    ITS_AddFeature(itsIMAL_Class);

    ITS_GlobalStart(ITS_TCAP|ITS_SCCP);

#if 0
    try
#endif
    {
        trin = new ITS_Worker(0, "User", ITS_DEFAULT_USER_SRC,
                              ITS_TRANSPORT_TQUEUE);
        trout = new ITS_Worker(0, "User 2", ITS_DEFAULT_USER_SRC+1,
                              ITS_TCAP|ITS_TRANSPORT_SSOCKET|
                                  ITS_TRANSPORT_IMAL_SOCKET);
    }
#if 0
    catch (...)
    {
        cout << "Couldn't create transport." << endl;

        return (0);
    }
#endif

    ITS_HDR hdr;
    hdr.type = 0;
    hdr.context.dialogue_id = 1;
    ITS_ASSERT(ROUTE_AddApplication(ITS_DEFAULT_USER_SRC, &hdr) == ITS_SUCCESS);

    TCAPUnitTest test;

    test.ExecuteCommandsFromStream();

    ROUTE_DeleteApplication(ITS_DEFAULT_USER_SRC, &hdr);

    delete trin;
    delete trout;

    ITS_GlobalStop();

    ITS_RemFeature(itsIMAL_Class);
    ITS_RemFeature(itsKEEPALIVE_Class);
    ITS_RemFeature(itsINTELLISS7_Class);

    return (0);
}
