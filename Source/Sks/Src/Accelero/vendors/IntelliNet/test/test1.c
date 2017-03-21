/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: test1.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:56  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:14  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:05  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:15  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/07/10 19:41:14  mmiers
 * LOG: Fix ANSI traffic gen
 * LOG:
 * LOG: Revision 6.3  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.2  2002/06/13 20:42:54  ttipatre
 * LOG: Adding gp command
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:40  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.30  2002/02/27 23:07:44  mmiers
 * LOG: Post throughput testing.
 * LOG:
 * LOG: Revision 1.29  2002/02/14 22:13:09  mmiers
 * LOG: Commit tests as is.
 * LOG:
 * LOG: Revision 1.28  2002/02/04 23:04:06  mmiers
 * LOG: Check in test.
 * LOG:
 * LOG: Revision 1.27  2002/02/01 22:50:48  mmiers
 * LOG: Testing.
 * LOG:
 * LOG: Revision 1.26  2002/02/01 22:12:26  mmiers
 * LOG: ISUP integration
 * LOG:
 * LOG: Revision 1.25  2002/02/01 19:47:06  mmiers
 * LOG: More work on traffic generation.
 * LOG:
 * LOG: Revision 1.24  2002/02/01 18:02:26  mmiers
 * LOG: Init event.
 * LOG:
 * LOG: Revision 1.23  2002/02/01 18:01:47  mmiers
 * LOG: Print stats
 * LOG:
 * LOG: Revision 1.22  2002/02/01 18:00:58  mmiers
 * LOG: More traffic work
 * LOG:
 * LOG: Revision 1.21  2002/02/01 17:48:37  mmiers
 * LOG: Set up for traffic testing.
 * LOG:
 * LOG: Revision 1.20  2002/01/30 21:26:40  mmiers
 * LOG: Convert back to ANSI
 * LOG:
 * LOG: Revision 1.19  2001/12/28 18:43:40  mmiers
 * LOG: A few mistakes to fix.
 * LOG:
 * LOG: Revision 1.18  2001/12/19 18:03:02  mmiers
 * LOG: Adax testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 1.17  2001/12/11 15:21:53  mmiers
 * LOG: Bug remnants
 * LOG:
 * LOG: Revision 1.16  2001/12/07 23:11:47  mmiers
 * LOG: Fix up ITU MTP3 (start testing it).
 * LOG:
 * LOG: Revision 1.15  2001/11/30 23:43:14  mmiers
 * LOG: Start testing config-d (route management).
 * LOG:
 * LOG: Revision 1.14  2001/11/20 21:46:00  mmiers
 * LOG: Debug the debug console.  Working now.
 * LOG:
 * LOG: Revision 1.13  2001/11/20 20:15:52  mmiers
 * LOG: Tab removal
 * LOG:
 * LOG: Revision 1.12  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 1.11  2001/11/15 23:52:27  mmiers
 * LOG: Today's testing.
 * LOG:
 * LOG: Revision 1.10  2001/11/14 23:17:13  mmiers
 * LOG: Many changes from conformance testing.
 * LOG:
 * LOG: Revision 1.9  2001/11/13 16:14:48  vnitin
 * LOG: new test case
 * LOG:
 * LOG: Revision 1.8  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 1.7  2001/10/24 22:42:00  rsonak
 * LOG: Modified test
 * LOG:
 * LOG: Revision 1.6  2001/10/24 14:46:02  rsonak
 * LOG: MOdified test file
 * LOG:
 * LOG: Revision 1.5  2001/10/19 20:49:00  mmiers
 * LOG: Get things working with the engine.
 * LOG:
 * LOG: Revision 1.4  2001/10/19 16:47:34  mmiers
 * LOG: Convert to engine for testing.
 * LOG:
 * LOG: Revision 1.3  2001/10/12 23:14:52  mmiers
 * LOG: Fun with NMS.  The MTP2 API now works.
 * LOG:
 * LOG: Revision 1.2  2001/10/04 21:31:34  mmiers
 * LOG: Today's installment.  Really need hardware at this point.
 * LOG:
 * LOG: Revision 1.1  2001/09/28 21:34:36  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>

#include <engine.h>

/*
 * tuneables
 */
#define NUM_PAYLOAD_BYTES   50
#define MSGS_PER_TICK       20

#if 0
#undef ANSI
#undef CCITT
#define CCITT
#else
#undef CCITT
#undef ANSI
#define ANSI
#endif

#if defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(CCITT)
#include <itu/mtp3.h>
#endif

#ident "$Id: test1.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $"

#if defined(WIN32)

#if defined(TEST_IMPLEMENTATION)
#define TESTDLLAPI __declspec(dllexport)
#else
#define TESTDLLAPI __declspec(dllimport)
#endif

#else  /* WIN32 */

#define TESTDLLAPI

#endif /* WIN32 */

ITS_THREAD thr;

static ITS_BOOLEAN sendTraffic = ITS_FALSE;

TESTDLLAPI void
MTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT *ev = (ITS_EVENT *)callData;
    ITS_OCTET mType;
    ITS_OCTET buf[255];
    ITS_USHORT len;

#if defined(ANSI)
    MTP3_HEADER_ANSI mtp3;

printf("\n\n\n\n\n\n\n\n\n\n\n\nMTP3 MANAGEMENT\n\n\n\n\n\n\n"); 
    MTP3_Decode_ANSI(ev, &mType, &mtp3, buf, &len);

    switch (mType)
    {
    case MTP3_MSG_USER_DATA:
        printf("################### GOT USER DATA\n");
        break;

    case MTP3_MSG_PAUSE:
        printf("################### GOT PAUSE: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)buf)->affected));
        sendTraffic = ITS_FALSE;
        break;

    case MTP3_MSG_RESUME:
        printf("################### GOT RESUME: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)buf)->affected));
        sendTraffic = ITS_TRUE;
        break;


    case MTP3_MSG_STATUS:
        printf("################### GOT STATUS: pc %06x cause %d cong %d\n",
               MTP3_PC_GET_VALUE(((MTP3_STATUS_ANSI *)buf)->affected),
               ((MTP3_STATUS_ANSI *)buf)->cause,
               ((MTP3_STATUS_ANSI *)buf)->congLevel);
        break;

    default:
        printf("################### DON'T KNOW WHAT I GOT\n");
        break;
    }
#elif defined(CCITT)
    MTP3_HEADER_CCITT mtp3;

printf("\n\n\n\n\n\n\n\n\n\n\n\nMTP3 MANAGEMENT\n\n\n\n\n\n\n"); 
    MTP3_Decode_CCITT(ev, &mType, &mtp3, buf, &len);

    switch (mType)
    {
    case MTP3_MSG_USER_DATA:
        printf("################### GOT USER DATA\n");
        break;

    case MTP3_MSG_PAUSE:
        printf("################### GOT PAUSE: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_CCITT *)buf)->affected));
        sendTraffic = ITS_FALSE;
        break;

    case MTP3_MSG_RESUME:
        printf("################### GOT RESUME: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_CCITT *)buf)->affected));
        sendTraffic = ITS_TRUE;
        break;

    case MTP3_MSG_STATUS:
        printf("################### GOT STATUS: pc %06x cause %d cong %d\n",
               MTP3_PC_GET_VALUE(((MTP3_STATUS_CCITT *)buf)->affected),
               ((MTP3_STATUS_CCITT *)buf)->cause,
               ((MTP3_STATUS_CCITT *)buf)->congLevel);
        break;

    default:
        printf("################### DON'T KNOW WHAT I GOT\n");
        break;
    }
#endif
}

TESTDLLAPI int
TrafficGenerator(TPOOL_THREAD *thr)
{
    ITS_UINT i, sndCnt, rcvCnt;
    WORKER_Control *work = (WORKER_Control *)thr;
    TRANSPORT_Control *tr = WORKER_TRANSPORT(work);
    ITS_EVENT ev;
    int delay = 100;
    int j, repeat = MSGS_PER_TICK;

    memset(&ev, 0, sizeof(ITS_EVENT));

    TIMERS_Sleep(40);

    rcvCnt = sndCnt = 0;

#if defined(ANSI)
    MTP3_EnableUserPart_ANSI(MTP3_SIO_SCCP, TRANSPORT_INSTANCE(tr));
#elif defined(CCITT)
    MTP3_EnableUserPart_CCITT(MTP3_SIO_SCCP, TRANSPORT_INSTANCE(tr));
#endif

    for (i = 0; ; i++)
    {
        if (WORKER_GetExit((WORKER_Control *)thr))
        {
            break;
        }

#if defined(ANSI)
        if (sendTraffic)
        {
            for (j = 0; j < repeat; j++)
            {
                MTP3_HEADER_ANSI mtp3;
                ITS_EVENT ev;
	        ITS_OCTET buf[NUM_PAYLOAD_BYTES];

                memset(buf, 0, NUM_PAYLOAD_BYTES);
                MTP3_HDR_SET_SIO(mtp3, MTP3_NIC_NATIONAL | MTP3_SIO_SCCP);
                MTP3_RL_SET_OPC_VALUE(mtp3.label, 0x000100);
                MTP3_RL_SET_DPC_VALUE(mtp3.label, 0x000101);
                MTP3_RL_SET_SLS(mtp3.label, sndCnt);

                ITS_EVENT_INIT(&ev, ITS_SCCP_ANSI_SRC, 0);
                MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                                 &mtp3, NULL, 0);

                ev.src = ITS_SCCP_ANSI_SRC;
                TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &ev);

                sndCnt++;
            }

            while (TRANSPORT_PeekNextEvent(tr, &ev) == ITS_SUCCESS)
            {
                rcvCnt++;
            }
  
            if (!(sndCnt % 1000))
            {
                printf("sndCnt %d rcvCnt %d\n", sndCnt, rcvCnt);
            }
        }
#elif defined(CCITT)
        if (sendTraffic)
        {
            for (j = 0; j < repeat; j++)
            {
                MTP3_HEADER_CCITT mtp3;
                ITS_EVENT ev;
	        ITS_OCTET buf[NUM_PAYLOAD_BYTES];

                memset(buf, 0, NUM_PAYLOAD_BYTES);
                MTP3_HDR_SET_SIO(mtp3, MTP3_NIC_NATIONAL | MTP3_SIO_SCCP);
                MTP3_RL_SET_OPC_VALUE(mtp3.label, 0x0008);
                MTP3_RL_SET_DPC_VALUE(mtp3.label, 0x0009);
                MTP3_RL_SET_SLS(mtp3.label, sndCnt);

                ITS_EVENT_INIT(&ev, ITS_SCCP_CCITT_SRC, 0);
                MTP3_Encode_CCITT(&ev, MTP3_MSG_USER_DATA,
                                  &mtp3, buf, NUM_PAYLOAD_BYTES);

                ev.src = ITS_SCCP_CCITT_SRC;
                TRANSPORT_PutEvent(ITS_MTP3_CCITT_SRC, &ev);

                sndCnt++;
            }

            while (TRANSPORT_PeekNextEvent(tr, &ev) == ITS_SUCCESS)
            {
                rcvCnt++;
            }
      
            if (!(sndCnt % 1000))
            {
                printf("sndCnt %d rcvCnt %d time %d\n", sndCnt, rcvCnt,
                       TIMERS_Time());
            }
        }
#endif

        TIMERS_USleep(USEC_PER_MILLISEC + delay);

        if (delay > 0) delay -= 10;
    }

    return (ITS_SUCCESS);
}

int
main(int argc, const char **argv)
{
#if 0
    char *buf;
    int ret;

    buf = malloc(16384);
    ITS_C_ASSERT(buf != NULL);

    ret = setvbuf(stdout, buf, _IOFBF, 16384);
    ITS_C_ASSERT(ret == 0);
#endif

    APPL_SetName("test");

    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}
