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
 *     FILE: Test.c (ReceiveSend Test)                                      *
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
 * LOG: Revision 3.1  2000/08/16 00:02:56  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:23  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/05/27 16:18:29  mmiers
 * LOG:
 * LOG:
 * LOG: Update tests to latest code.
 * LOG:
 * LOG: Revision 1.4  1999/05/27 15:53:27  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 1.3  1998/02/27 16:38:19  ite
 * LOG: Fix merge error.
 * LOG:
 * LOG: Revision 1.2  1998/02/26 16:23:08  mmiers
 * LOG: Update the TCAP tests to use the single ITS_Initialize() signature.  The
 * LOG: parameters are now read from a file for NMS.  The signature in its.h has
 * LOG: been consolidated to one platform-independent signature.
 * LOG:
 * LOG: Revision 1.1  1998/02/24 17:35:25  ite
 * LOG: More TCAP tests.  Useful for vendor lib debugging.
 * LOG:
 *
 ****************************************************************************/

/*

A simple test to receive and send back. To be used in association with send
receive test.

*/

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <its.h>

#if defined(CCITT)
#include <itu/sccp.h>
#include <itu/tcap.h>
#else
#include <ansi/sccp.h>
#include <ansi/tcap.h>
#endif

#include <its_ss7_stubs.h>

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

int main(int argc, char** argv)
{
    TCAP_CPT cpt;
    TCAP_DLG dlg;
    int dialogue_id = 4;
    ITS_HDR hdrDlg, hdrCpt;
    ITS_EVENT ev;

    /* SB = Send Back. */

    TCAP_CPT cptSB;
    TCAP_DLG dlgSB;
    ITS_HDR hdrDlgSB, hdrCptSB;
    ITS_OCTET ssn = 3;
    int pc = 0;
    int bStop = 0, i = 0;

#if defined(WIN32)
    SetConsoleCtrlHandler(breakHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    printf("initializing\n");

    if ((handle = ITS_Initialize(ITS_TCAP, 1)) == NULL)
    {
        fprintf(stderr, "%s: error initializing stack\n", argv[0]);
        perror("because: ");

        exit(0);
    }

    SCCP_SendUserOutOfService(handle, pc, ssn);
    SCCP_SendUserInService(handle, pc, ssn);

    memset(&dlg, 0, sizeof(TCAP_DLG));
    memset(&cpt, 0, sizeof(TCAP_CPT));
    memset(&hdrDlg, 0, sizeof(ITS_HDR));
    memset(&hdrCpt, 0, sizeof(ITS_HDR));

    while (!bStop)
    {
        ITS_GetNextEvent(handle, &ev);
        
        printf("Got event. Src: <%d>.\n", ev.src);
        
        switch (ev.src)
        {
        case ITS_TCAP:
            
            switch (ev.data[0])
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
                    
                    printf("Receive done. Stop the receive loop and send back...\n");
                    
                    bStop = 1;
                    
                }
                break;
                
                case ITS_TCAP_DLG:
                    TCAP_ReceiveDialogue(handle, &ev, &hdrDlg, &dlg);
                    printf("Got dialogue. Type: <%d>.\n", dlg.ptype);
                    printf("DialogueId: <%d>.\n", hdrDlg.context.dialogue_id);
                    
                    /* The following initialization could be useful:
                    * hdrCpt.context.dialogue_id = hdrDlg.context.dialogue_id;
                    */
                    
                    break;
                default:
                    break;
            }
            break;
            
            default: /* UNKNOWN SOURCE */
                break;
        }
    }


    memset(&hdrDlgSB, 0, sizeof(ITS_HDR));
    memset(&hdrCptSB, 0, sizeof(ITS_HDR));

    memset(&dlgSB, 0, sizeof(TCAP_DLG));
    memset(&cptSB, 0, sizeof(TCAP_CPT));

    hdrDlgSB.context.dialogue_id = hdrDlg.context.dialogue_id;
    hdrCptSB.context.dialogue_id = hdrDlg.context.dialogue_id;

    dlgSB.ptype = TCPPT_TC_RESP;
    cptSB.ptype = TCPPT_TC_ERROR;

    cptSB.u.error.invoke_id.data[0] = cpt.u.invoke.invoke_id.data[0];
    cptSB.u.error.invoke_id.data[1] = cpt.u.invoke.invoke_id.data[1];
    cptSB.u.error.invoke_id.data[2] = cpt.u.invoke.invoke_id.data[2];
    cptSB.u.error.invoke_id.len = 3;


    cptSB.u.error.param.len = 0;

    cptSB.u.error.error.data[0] = TCPPN_ECI_NATIONAL_TCAP;
    cptSB.u.error.error.data[1] = 1;
    cptSB.u.error.error.data[2] = TCPERR_DATA_UNAV;
    cptSB.u.error.error.len = 3;

    TCAP_SendComponent(handle, &hdrCptSB, &cptSB);

    TCAP_SendDialogue(handle, &hdrDlgSB, &dlgSB);

    for (i = 0; i < 5; i++)
    {
        if (ITS_PeekNextEvent(handle, &ev) == ITS_SUCCESS)
        {
            printf("GOT RETURN EVENT\n");
        }
        Sleep(2500);
    }

    ITS_Terminate(handle);

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
