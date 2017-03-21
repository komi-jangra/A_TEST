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
 *  ID: $Id: test27.c,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:33  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:14  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:25  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:29  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2002/02/27 23:01:31  vnitin
 * LOG: Adding sctp test code for retrieve buffer and SSN
 * LOG:
 * LOG: Revision 3.3  2000/12/20 22:12:35  mmiers
 * LOG: Still condvar problems on Solaris
 * LOG:
 * LOG: Revision 3.2  2000/12/20 17:49:49  mmiers
 * LOG: Solaris debugging.
 * LOG:
 * LOG: Revision 3.1  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 1.20  2000/10/30 16:18:24  mmiers
 * LOG: Post bakeoff.  Now to clean up.
 * LOG:
 * LOG: Revision 1.19  2000/10/22 20:27:45  mmiers
 * LOG: Add static cookie life extension.
 * LOG:
 * LOG: Revision 1.18  2000/10/21 23:49:26  mmiers
 * LOG: Final version for bakeoff.
 * LOG:
 * LOG: Revision 1.17  2000/10/21 22:45:07  mmiers
 * LOG: Surprising results running with efence.
 * LOG:
 * LOG: Revision 1.16  2000/10/19 23:19:28  mmiers
 * LOG: More testing bug fixes.
 * LOG:
 * LOG: Revision 1.15  2000/10/17 18:25:52  mmiers
 * LOG: Retransmit working.
 * LOG:
 * LOG: Revision 1.14  2000/10/17 16:00:51  mmiers
 * LOG: Final version (I think).
 * LOG:
 * LOG: Revision 1.13  2000/10/16 22:41:58  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.12  2000/10/16 20:29:32  mmiers
 * LOG: Clean up.  Debugging almost done.
 * LOG:
 * LOG: Revision 1.11  2000/10/16 19:32:33  mmiers
 * LOG: Debugging round 1.
 * LOG:
 * LOG: Revision 1.10  2000/10/15 18:50:40  mmiers
 * LOG: Test program done.  Now debugging is all that's left.
 * LOG:
 *
 ****************************************************************************/

/*
 * adapted from Stewart's user input module, which appears under the GNU
 * copyleft.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <its.h>
#include <its_sctp.h>
#include <its_timers.h>
#include <its_transports.h>
#include <its_thread.h>

#if !defined(WIN32)
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#if defined(solaris)
#include <sys/socket.h>
#endif
#endif

int payload = 0;
int pingPongCount = 0;
char pingBuffer[8192];
int pingBufSize = 0;
int pingStream = 0;
int defStream = 0;

int bulkCount = 0;
int bulkBufSize = 0;
int bulkStream = 0;
int bulkSeen = 0;

int continualINIT = 0;
int mainnotDone = 1;
int destinationSet = 0;
int sendOptions = 0;
int bulkInProgress = 0;
int bulkPingMode = 0;

struct sockaddr_in to_ip;

ITS_USHORT myPort;
ITS_THREAD recvThread;

/* wire test structures */
typedef struct
{
    ITS_OCTET  type;
    ITS_OCTET  padding;
    ITS_USHORT dgramLen;
    ITS_UINT   dgramID;
}
testDgram_t;

#define SCTP_TEST_LOOPREQ   1
#define SCTP_TEST_LOOPRESP  2
#define SCTP_TEST_SIMPLE    3

/*
 * make an address
 */
SOCK_IPv4Addr
translateIPAddress(char *host)
{
    struct sockaddr_in sa;
    struct hostent *hp;

    sa.sin_addr.s_addr = htonl(inet_network(host));

    if(sa.sin_addr.s_addr == 0xffffffff)
    {
        hp = gethostbyname(host);

        if(hp == NULL)
        {
            return(htonl(strtoul(host,NULL,0)));
        }

        memcpy(&sa.sin_addr,hp->h_addr_list[0],sizeof(sa.sin_addr));
    }

    return(sa.sin_addr.s_addr);
}

/*
 * send one SCTP message
 */
int
sendOne(ITS_USHORT sd, struct sockaddr_in *to, int stream, int ptype,
        void *data, int sz)
{
    SCTP_API_IOVEC iovec;
    SCTP_API_MSG_HDR msg;
    SCTP_API_CMSG cmsg;

/*  printf("sendOne: %08x %d str: %d ptype %d len %d\n",
       to->sin_addr.s_addr, to->sin_port, stream, ptype, sz);
*/

    msg.name = (ITS_POINTER)to;
    msg.nameLen = sizeof(struct sockaddr_in);
    msg.ioVecs = &iovec;
    msg.numIOVecs = 1;
    iovec.vector = data;
    iovec.len = sz;
    msg.control = (ITS_POINTER)&cmsg;
    msg.controlLen = sizeof(cmsg);
    cmsg.hdr.len = sizeof(SCTP_API_SND_RCV);
    cmsg.hdr.type = SCTP_CM_DATA_IO;
    cmsg.hdr.level = 0;
    cmsg.data.sndRcv.stream = stream;
    cmsg.data.sndRcv.flags = sendOptions;
    cmsg.data.sndRcv.context = ptype;

    return SCTP_SendMsg(sd, &msg, SCTP_API_SYNC);
}

/*
 * send bulk transfer
 */
int
sendBulkTransfer(ITS_USHORT sd,int sz)
{
    char buffer[10000];
    testDgram_t *tt;
    static ITS_UINT dgramCount = 0;
    int sndsz;

    if((sz+sizeof(testDgram_t)) > (sizeof(buffer)))
    {
        sndsz = sizeof(buffer) -  sizeof(sizeof(testDgram_t));
    }
    else
    {
        sndsz = sz +  sizeof(sizeof(testDgram_t));
    }

    memset(buffer, 0, sndsz);

    tt = (testDgram_t *)buffer;

    tt->type = SCTP_TEST_SIMPLE;
    tt->dgramLen = sndsz - sizeof(testDgram_t);
    tt->dgramID = dgramCount++;

    return sendOne(sd, &to_ip, defStream, payload, buffer, sndsz);
}

/*
 * send additional bulk transfer
 */
void
checkBulkTranfer(ITS_USHORT sd)
{	
    int ret = 0,cnt;
    cnt = 0;

    while (bulkCount > 0)
    {
        if (bulkPingMode == 0)
        {
#if 0
            ret = sendOne(sd, &to_ip, bulkStream, 0, pingBuffer, bulkBufSize);
#else
            sprintf(&pingBuffer[4], "Send on stream %d\n", bulkCount % 3);

printf("%d:%s\n", bulkCount % 3, &pingBuffer[4]);
            ret = sendOne(sd, &to_ip, bulkCount % 3, 0, pingBuffer, bulkBufSize);
#endif
        }
        else
        {
            ret = sendBulkTransfer(sd, bulkBufSize);
        }

        if(ret < 0)
        {
          return;
        }

        cnt++;
        bulkCount--;
    }

    /* ask for the time again */
    if (bulkPingMode == 0)
    {
        strcpy(pingBuffer, "time");

        ret = sendOne(sd, &to_ip, bulkStream, 0, pingBuffer, 5);

        if (ret < 0)
        {
            printf("Could not get time in, will wait ret:%d\n",ret);

            return;
        }
    }

    bulkInProgress = 0;

    printf("bulk message are now queued: ret:%d\n", ret);
}

/*
 * dump an array
 */
void
printArry(ITS_OCTET *data, int sz)
{
    /* if debug is on hex dump a array */
    int i, j, linesOut;
    char buff1[64];
    char buff2[64];
    char *ptr1, *ptr2, *dptrlast, *dptr;
    char *hexes = "0123456789ABCDEF";

    ptr1 = buff1;
    ptr2 = buff2;
    dptrlast = dptr = (char *)data;

    for (i = 0, linesOut = 0; i < sz; i++)
    {
        *ptr1++ = hexes[0x0f&((*dptr)>>4)];
        *ptr1++ = hexes[0x0f&(*dptr)];
        *ptr1++ = ' ';

        if ((*dptr >= 040) && (*dptr <= 0176))
        {
            *ptr2++ = *dptr;
        }
        else
        {
            *ptr2++ = '.';
        }

        dptr++;

        if (((i+1) % 16) == 0)
        {
            *ptr1 = 0;
            *ptr2 = 0;

            printf("%s %s\n", buff1, buff2);

            linesOut++;

            ptr1 = buff1;
            ptr2 = buff2;

            dptrlast = dptr;
        }
    }

    if ((linesOut*16) < sz)
    {
        char spaces[64];
        int dist,sp;

        j=(linesOut*16);

        dist = ((16 - (i - j)) * 3) + 2;

        *ptr1 = 0;
        *ptr2 = 0;

        for ( sp = 0; sp < dist; sp++)
        {
            spaces[sp] = ' ';
        }

        spaces[sp] = 0;

        printf("%s %s%s\n", buff1, spaces, buff2);
    }

    fflush(stdout);
}

/*
 * send a loopback request
 */
int
sendLoopRequest(ITS_USHORT sd, int sz)
{
    char buffer[15000];
    testDgram_t *tt;
    static ITS_UINT dgramCount = 0;
    int sndsz;

    printf("sendLoopReq\n");
    if ((sz + sizeof(testDgram_t)) > (sizeof(buffer)))
    {
        sndsz = sizeof(buffer) -  sizeof(sizeof(testDgram_t));
    }
    else
    {
        sndsz = sz +  sizeof(sizeof(testDgram_t));
    }

    memset(buffer, 0, sizeof(buffer));

    tt = (testDgram_t *)buffer;

    tt->type = SCTP_TEST_LOOPREQ;
    tt->dgramLen = sndsz - sizeof(testDgram_t);
    tt->dgramID = dgramCount++;

    return sendOne(sd, &to_ip, defStream, payload, buffer, sndsz);      
}

/*
 * do pong to a ping
 */
void
handlePong(ITS_USHORT sd, struct sockaddr_in *from, int mode)
{
    pingPongCount--;

    if (pingPongCount <= 0)
    {
        /* done */
        time_t x;
        struct tm *timeptr;

        x = time(0);
        timeptr = localtime(&x);

        printf("handlePong: %s", asctime(timeptr));
        printf("--Ping pong completes\n");

        fflush(stdout);

        return;
    }

    if (mode == 0)
    {
        sendOne(sd, from, pingStream, 0, pingBuffer, pingBufSize);  
    }
    else
    {
        sendLoopRequest(sd, pingBufSize);
    }
}

/*
 * send ping
 */
void
doPingPong(ITS_USHORT sd)
{
    time_t x;
    int i;
    struct tm *timeptr;

    if (bulkPingMode == 0)
    {
        /* use ascii bulk ping mode.*/
        strncpy(pingBuffer,"ping",4);

        for(i = 4; i < pingBufSize;i++)
        {
            pingBuffer[i] = 'A' + (i%26);
        }

        sendOne(sd, &to_ip, pingStream, payload, pingBuffer, pingBufSize);      
    }
    else
    {
         /* use binary bulk ping mode */
        sendLoopRequest(sd, pingBufSize);
    }

    x = time(0);
    timeptr = localtime(&x);

    printf("doPingPong: %s", asctime(timeptr));
}

/*
 * receive SCTP messages
 */
void
sctpInput(ITS_USHORT sd)
{
    /* receive some number of datagrams and
     * act on them.
     */
    int sz, str, seq, i, disped, payloadtype, doProcess;
    struct sockaddr_in from, to, *who;
    testDgram_t *testptr;
    char readBuffer[8192];
    SCTP_API_MSG_HDR msg;
    SCTP_API_IOVEC iovec;
    SCTP_API_CMSG cmsg;
    SOCK_AddrStore addr;
    SCTP_API_IOCTL_ARG arg;

    disped = i = 0;
    sz = 0;

    testptr = (testDgram_t *)readBuffer;

    msg.name = (ITS_POINTER)&addr;
    msg.nameLen = sizeof(SOCK_AddrStore);
    msg.ioVecs = &iovec;
    msg.numIOVecs = 1;
    iovec.vector = readBuffer;
    iovec.len = 8192;
    msg.control = (ITS_POINTER)&cmsg;
    msg.controlLen = sizeof(cmsg);
    cmsg.hdr.type = 0;

    while (mainnotDone && (sz = SCTP_RecvMsg(sd, &msg, SCTP_API_SYNC)) >= 0)
    {
        switch (cmsg.hdr.type)
        {
        case SCTP_CM_DATA_IO:
            doProcess = 1;
            break;

        case SCTP_CM_ASSOC_CHG:
            doProcess = 0;

            printf("assoc changed: ");
            switch (cmsg.data.assocChg.state)
            {
            case SCTP_AC_COMM_UP:
                printf("ASSOCIATION UP\n");
                break;
            case SCTP_AC_COMM_LOST:
                printf("ASSOCIATION DOWN\n");
                break;
            case SCTP_AC_COMM_RESTART:
                printf("ASSOCIATION RESTART\n");
                break;
            case SCTP_AC_COMM_ABORTED:
                printf("ASSOCIATION ABORTED\n");
                break;
            case SCTP_AC_SHUTDOWN_DONE:
                printf("ASSOCIATION SHUTDOWN DONE\n");
                break;
            case SCTP_AC_CANT_START:
                printf("ASSOCIATION CAN'T START\n");
                break;
            default:
                printf("unknown state\n");
                break;
            }
            fflush(stdout);
            break;

        case SCTP_CM_INTF_CHG:
            doProcess = 0;

            printf("interface changed: ");
            who = (struct sockaddr_in *)&cmsg.data.intfChg.affectedAddr;
            switch (cmsg.data.intfChg.state)
            {
            case SCTP_IC_ADDR_REACHABLE:
                printf("INTF REACHEABLE: %08x %d\n",
                       who->sin_addr.s_addr, who->sin_port);
                break;

            case SCTP_IC_ADDR_UNREACHABLE:
                printf("INTF UNREACHEABLE: %08x %d\n",
                       who->sin_addr.s_addr, who->sin_port);
                break;

            default:
                printf("unknown state\n");
                break;
            }
            break;

        case SCTP_CM_SEND_FAIL:
            doProcess = 0;

            printf("send fail\n");
            break;

        case SCTP_CM_REMOTE_ERR:
            doProcess = 0;
            printf("remote error: ");
            printf("cause: %d len: %d\n",
                   cmsg.data.remErr.causeCode, cmsg.data.remErr.causeLen);
            break;

        case SCTP_CM_HB_RESP:
            doProcess = 0;
            printf("hb response\n");
            break;

        case SCTP_CM_SSN_CONFM:
            doProcess = 0;
            printf("SSN Confirm : %d\n", cmsg.data.sndRcv.seqNum);
            break;
  
        case SCTP_CM_BUFF_RTRV:
            doProcess = 0;
            printf("Buffer Retrival SSN : %d\n", cmsg.data.sndRcv.seqNum);
            break;

        case SCTP_CM_BUFF_RTRV_COMP:
            doProcess = 0;
            printf("Buffer Retrival COMPLETE\n");
            break;

        case SCTP_CM_SSN_NOT_RTRV:
            doProcess = 0;
            printf("Unable to Retrieve SSN \n");
            break;

        default:
            doProcess = 0;
            printf("unknown notification\n");
            break;

        }

        fflush(stdout);

        if (!doProcess)
        {
            continue;
        }

        str = cmsg.data.sndRcv.stream;
        seq = cmsg.data.sndRcv.seqNum;
        memcpy(&from, &addr, sizeof(struct sockaddr_in));
        payloadtype = cmsg.data.sndRcv.context;
        to.sin_addr.s_addr = cmsg.data.sndRcv.primary;
        to.sin_port = myPort;

        i++;

        if (testptr->type == SCTP_TEST_LOOPREQ)
        {
            /* another ping/pong type */
            printf("Loop request Stream:%d Sequence:%d\n",str,seq);

            testptr->type = SCTP_TEST_LOOPRESP;
            memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));

            if (SCTP_Ioctl(sd, IOCTL_GET_NUM_OUT_STREAMS, &arg) < 0)
            {
                printf("IOCTL failed.\n");
                continue;
            }

            if (str >= arg.value)
            {
                printf("stream in was %d but my max is %d\n",
                       str, arg.value);
                str = 0;
                printf("responding on 0\n");
            }

            sendOne(sd, &from, str, payloadtype, readBuffer, sz);
        }
        else if (testptr->type == SCTP_TEST_LOOPRESP)
        {
            printf("loop resp\n");
            handlePong(sd, &from, 1);
        }
        else if (testptr->type == SCTP_TEST_SIMPLE)
        {
            printf("Got simple dg len:%d dgID:%x\n",
                   SOCK_NToHS(testptr->dgramLen),
                   (ITS_UINT)testptr->dgramID);
        }
        else if (strncmp(readBuffer,"ping",4) == 0)
        {
            /* it is a ping-pong message, send it back after changing
             * the first 4 bytes to pong 
             */
            printf("send pong\n"); 
            strncpy(readBuffer, "pong", 4);
            sendOne(sd, &from, str, payloadtype, readBuffer, sz);
        }
        else if (strcmp(readBuffer,"time") == 0)
        {
            time_t x;
            struct tm *timeptr;
            x = time(0);

            timeptr = localtime(&x);
            printf("sctpInput: %s", asctime(timeptr));
        }
        else if(strncmp(readBuffer,"pong",4) == 0)
        {
            handlePong(sd, &from, 0);
        }
        else if(strncmp(readBuffer,"bulk",4) == 0)
        {
            bulkSeen++;
        }
        else
        {
            /* display a text message */
            ITS_UINT frm,too;

            frm = ntohl(from.sin_addr.s_addr);
            too = ntohl(to.sin_addr.s_addr);

            if (isascii(readBuffer[0]))
            {
                printf("From:%d.%d.%d.%d:%d To:%d.%d.%d.%d:%d "
                       "strm:%d seq:%d %d:'%s'\n",
                       (int)((frm >> 24) & 0x000000ff),
                       (int)((frm >> 16) & 0x000000ff),
                       (int)((frm >> 8) & 0x000000ff),
                       (int)(frm  & 0x000000ff),
                       from.sin_port,
                       (int)((too >> 24) & 0x000000ff),
                       (int)((too >> 16) & 0x000000ff),
                       (int)((too >> 8) & 0x000000ff),
                       (int)(too  & 0x000000ff),
                       to.sin_port,
                       str,
                       seq,
                       sz,
                       readBuffer);

                readBuffer[0] = 0;
                disped = 1;
            }
            else
            {
                printf("From:%d.%d.%d.%d:%d To:%d.%d.%d.%d:%d "
                       "strm:%d seq:%d %d\n",
                       (int)((frm >> 24) & 0x000000ff),
                       (int)((frm >> 16) & 0x000000ff),
                       (int)((frm >> 8) & 0x000000ff),
                       (int)(frm  & 0x000000ff),
                       from.sin_port,
                       (int)((too >> 24) & 0x000000ff),
                       (int)((too >> 16) & 0x000000ff),
                       (int)((too >> 8) & 0x000000ff),
                       (int)(too  & 0x000000ff),
                       to.sin_port,
                       str,
                       seq,
                       sz);

                printArry(readBuffer,sz);
                readBuffer[0] = 0;
                disped = 1;
            }
        }
    }

    printf("sz: %d mainnotDone %d\n", sz, mainnotDone);
}

char *namelist[]=
{
    "SCTP_PEG_SACKS_RCVD",
    "SCTP_PEG_SACKS_SENT",
    "SCTP_PEG_TSNS_RCVD",
    "SCTP_PEG_TSNS_SENT",
    "SCTP_PEG_DGRAMS_RCVD",
    "SCTP_PEG_DGRAMS_SENT",
    "SCTP_PEG_NUM_RETRANS",
    "SCTP_PEG_NUM_DUPS",
    "SCTP_PEG_HBEATS_RCVD",
    "SCTP_PEG_HBEATS_SENT",
    "SCTP_PEG_HABEATS_RCVD",
    "SCTP_PEG_HABEATS_SENT",
    "SCTP_PEG_DATA_RCVD",
    "SCTP_PEG_DATA_SENT",
    "SCTP_PEG_XMIT_TIMER",
    "SCTP_PEG_RECV_TIMER",
    "SCTP_PEG_HB_TIMER",  
    "SCTP_PEG_FAST_RETRAN",
    "SCTP_PEG_TSNS_SEEN",
    "SCTP_PEG_RWND_FULL",
    "SCTP_PEG_NONE_TO_SEND",
    "SCTP_PEG_CWND_FULL",
    "UNKNOWN"
};

char *assocstate[] =
{
    "SCTP_CLOSED",
    "SCTP_COOKIE_WAIT",
    "SCTP_COOKIE_SENT",    /* This is COOKIE_ECHOED */
    "SCTP_ESTABLISHED",
	"SCTP_SHUTDOWN_PENDING",
    "SCTP_SHUTDOWN_SENT",
    "SCTP_SHUTDOWN_RECEIVED",
    "SCTP_SHUTDOWN_ACK_SENT"
};

char *mibnames[] = 
{
    "SCTP_MIB_RTO_ALGORITHM",
    "SCTP_MIB_RTO_MIN",
    "SCTP_MIB_RTO_MAX",
    "SCTP_MIB_RTO_INITIAL",
    "SCTP_MIB_COOKIE_LIFE",
    "SCTP_MIB_MAX_INIT_RETR",
    "SCTP_MIB_GEN_VARIABLE",
    "SCTP_MIB_CURR_ESTAB",
    "SCTP_MIB_ACTIVE_ESTAB",
    "SCTP_MIB_PASSIVE_ESTAB",
    "SCTP_MIB_ABORTED",
    "SCTP_SHUTDOWNS",
    "SCTP_MIB_GEN_STATES",
    "SCTP_MIB_OOB",
    "SCTP_MIB_SENT_CHUNKS",
    "SCTP_MIB_REC_CHUNKS",
    "SCTP_MIB_OO_SENT_CHUNKS",
    "SCTP_MIB_OO_REC_CHUNKS",
    "SCTP_MIB_FRAG_DG",
    "SCTP_MIB_REASMB_DG",
    "SCTP_MIB_GEN_STATISTICS",
    "SCTP_MIB_ASSOC_ID",
    "SCTP_MIB_REM_NAME",
    "SCTP_MIB_LOCAL_PORT",
    "SCTP_MIB_REM_PORT",          
    "SCTP_MIB_REM_PRIM_ADDR_TYP",
    "SCTP_MIB_REM_PRIM_ADDR",
    "SCTP_MIB_HBEAT_FLAG",
    "SCTP_MIB_HBEAT_TIMER",
    "SCTP_MIB_ASSOC_STATE",
    "SCTP_MIB_IN_STREAM",
    "SCTP_MIB_OUT_STREAM",
    "SCTP_MIB_MAX_SEND_RET",
    "SCTP_ASSOC_GEN_VARIABLE", 
    "SCTP_MIB_T1_EXPIRED",
    "SCTP_MIB_T2_EXPIRED ",
    "SCTP_MIB_RETR_CHUNKS ",
    "SCTP_MIB_CKSUM_ERROR ",
    "SCTP_MIB_ASSOC_START_TIME ",
    "SCTP_MIB_ASSOC_STATISTICS ",
    "SCTP_MIB_LCL_ADDR_TYPE",
    "SCTP_MIB_LCL_IP_ADDR",
    "SCTP_MIB_LCL_IP_START_TIME",
    "SCTP_MIB_LOCAL_IP_TABLE",
    "SCTP_MIB_REM_ADDR_TYPE ",
    "SCTP_MIB_REM_IP_ADDR ",
    "SCTP_MIB_REM_ADDR_STATE ",
    "SCTP_MIB_REM_ADDR_RTO ",
    "SCTP_MIB_REM_MAX_PATH_RETR ",
    "SCTP_MIB_REM_RETR_COUNT ",
    "SCTP_MIB_REM_IP_START_TIME ",
    "SCTP_MIB_REM_IP_TABLE "
};

/*
 * Printing MIB info retrived 
 */
void printMIBInfo(int val, SCTP_API_MIB_DATA *data)
{
    int i;

    switch(val)
    {
    case SCTP_MIB_RTO_ALGORITHM:

        printf("SCTP_MIB: get rto alogorithm %d \n", data->msg.genVar.rto_algo);
        
        break;

    case SCTP_MIB_RTO_MIN:

        printf("SCTP_MIB: get gen rto min %ld\n",data->msg.genVar.rto_min);
         
        break;

    case SCTP_MIB_RTO_MAX:

        printf("SCTP_MIB: get gen rto max %ld\n",data->msg.genVar.rto_max);
         
        break;

    case SCTP_MIB_RTO_INITIAL:

        printf("SCTP_MIB: get gen rto initial %ld\n",data->msg.genVar.rto_init);
        
        break;

    case SCTP_MIB_COOKIE_LIFE:

        printf("SCTP_MIB: get gen ValCookieLife %ld\n",data->msg.genVar.cookieLife);
        
        break;

    case SCTP_MIB_MAX_INIT_RETR:

        printf("SCTP_MIB: get gen maxInitAttempts %d\n"
            ,data->msg.genVar.maxInitAttempts);
         
        break;

    case SCTP_MIB_GEN_VARIABLE:

        printf("SCTP_MIB: get all protocol general Variables\n");

        printf ("SCTP_RTO_ALGORITHM:%d\n", data->msg.genVar.rto_algo);
        printf ("rto_min :%ld\n", data->msg.genVar.rto_min);
        printf ("rto_max :%ld\n",data->msg.genVar.rto_max);
        printf ("rto_initial: %ld\n",data->msg.genVar.rto_init );
        printf ("Cookile Life: %ld\n",data->msg.genVar.cookieLife );
        printf ("Max Init Attempts: %d\n",data->msg.genVar.maxInitAttempts );
        break;

    case SCTP_MIB_CURR_ESTAB:

        printf("SCTP_MIB: gen state currEstab %d\n",data->msg.genState.currEstab);
        break;

    case SCTP_MIB_ACTIVE_ESTAB:

        printf("SCTP_MIB: gen state activeEstab %d\n",
            data->msg.genState.activeEstab);
        
        break;

    case SCTP_MIB_PASSIVE_ESTAB:

        printf("SCTP_MIB: gen state passiveEstab %d\n",
            data->msg.genState.passiveEstab);
        break;

    case SCTP_MIB_ABORTED:

        printf("SCTP_MIB: gen state aborted %d\n",data->msg.genState.aborted);
        break;

    case SCTP_SHUTDOWNS:

        printf("SCTP_MIB:  gen state numShutdowns %d\n",
            data->msg.genState.numShutdowns);
        break;

    case SCTP_MIB_GEN_STATES:  

        printf("SCTP_MIB: all protocol general states\n");        
        printf("[currEstab]: %d\n",data->msg.genState.currEstab);
        printf("[activeEstab] : %d\n",data->msg.genState.activeEstab);
        printf("[passiveEstab] : %d\n",data->msg.genState.passiveEstab);
        printf("[aborted]: %d\n",data->msg.genState.aborted);
        printf("[numShutdowns] : %d\n",data->msg.genState.numShutdowns);
        break;

    case SCTP_MIB_OOB:
        /* Out of blue user datagrams */

        printf("SCTP_MIB: gen statictics %ld\n",
            data->msg.genCounter.numOutOfBlue);
       
        break;

    case SCTP_MIB_SENT_CHUNKS:

        printf("SCTP_MIB: gen numSentChunks statictics %ld\n",
            data->msg.genCounter.numSentChunks);
         break;

    case SCTP_MIB_REC_CHUNKS:

        printf("SCTP_MIB: gen numRecChunks statictics %ld\n",
            data->msg.genCounter.numRecChunks);
        break;

    case SCTP_MIB_OO_SENT_CHUNKS:
        /* Out of order with u bit set to 1 */

        printf("SCTP_MIB: gen numOutOfOrderSent statictics %ld\n",
            data->msg.genCounter.numOutOfOrderSent);
        break;

    case SCTP_MIB_OO_REC_CHUNKS:
        /* Out of order with u bit set to 1 */

        printf("SCTP_MIB: gen numOutOfOrderRec statictics %ld\n",
           data->msg.genCounter.numOutOfOrderRec );
        break;

    case SCTP_MIB_FRAG_DG:

        printf("SCTP_MIB: gen numFragUsrMsgs statictics %ld\n",
            data->msg.genCounter.numFragUsrMsgs);
        break;

    case SCTP_MIB_REASMB_DG:

        printf("SCTP_MIB: gen numReassmbUsrMsgs statictics %ld\n",
            data->msg.genCounter.numReassmbUsrMsgs);
        break;

    case SCTP_MIB_GEN_STATISTICS:

        printf("SCTP_MIB: all protocol general statictics\n");
        printf("[numOutOfBlue] : %ld",data->msg.genCounter.numOutOfBlue);             
        printf("[numSentChunks] : %ld",data->msg.genCounter.numSentChunks);            
        printf("[numRecChunks] : %ld",data->msg.genCounter.numRecChunks);             
        printf("[numOutOfOrderSent] : %ld",data->msg.genCounter.numOutOfOrderSent);             
        printf("[numOutOfOrderRec] : %ld",data->msg.genCounter.numOutOfOrderRec);            
        printf("[numFragUsrMsgs] : %ld",data->msg.genCounter.numFragUsrMsgs);            
        printf("[numReassmbUsrMsgs] : %ld",data->msg.genCounter.numReassmbUsrMsgs);
            
        break;

    case SCTP_MIB_ASSOC_ID:

        printf("SCTP_MIB: association ID %ld\n",data->msg.assocVar.assocId );
        
        break;

    case SCTP_MIB_REM_NAME:

        printf("SCTP_MIB:assoc remote Name %s\n",data->msg.assocVar.remoteName);
        break;

    case SCTP_MIB_LOCAL_PORT:

        printf("SCTP_MIB: assoc local port %d\n",data->msg.assocVar.srcPort);
        
        break;

    case SCTP_MIB_REM_PORT:

        printf("SCTP_MIB: assoc Destination port %d\n",data->msg.assocVar.destPort);
 
        break;

    case SCTP_MIB_REM_PRIM_ADDR_TYP:

        printf("SCTP_MIB: assoc primary remote address type %d\n",
            data->msg.assocVar.remPrimAddrType);

        break;

    case SCTP_MIB_REM_PRIM_ADDR:

        printf("SCTP_MIB: association primary remote address %d\n",
            data->msg.assocVar.remPrimAddr);

         break;

    case SCTP_MIB_HBEAT_FLAG:

        printf("SCTP_MIB: association Heartbeat Flag %s\n",
            data->msg.assocVar.hbState? "Inactive" : "Active" );

        break;

    case SCTP_MIB_HBEAT_TIMER:

        printf("SCTP_MIB: association Heartbeat Timer %ld\n",
            data->msg.assocVar.hbTimer);
        break;

    case SCTP_MIB_ASSOC_STATE:

        printf("SCTP_MIB: association state %s\n", 
            assocstate[data->msg.assocVar.state]);

        break;

    case SCTP_MIB_IN_STREAM:

        printf("SCTP_MIB: association no of inbound streams %ld\n",
            data->msg.assocVar.numInStreams);

        break;

    case SCTP_MIB_OUT_STREAM:

        printf("SCTP_MIB: get assoc no of outbound streams %ld\n"
            ,data->msg.assocVar.numOutStreams);

        break;

    case SCTP_MIB_MAX_SEND_RETR:

        printf("SCTP_MIB: association Max Retransmission %d\n",
            data->msg.assocVar.maxRetrans);

        break;

    case SCTP_MIB_ASSOC_START_TIME:

        printf("SCTP_MIB: get association start time %ld\n",
            data->msg.assocVar.startTime);

        break;

    case SCTP_ASSOC_GEN_VARIABLE:

        printf("SCTP_MIB:all association gen variables");
        printf("SCTP_MIB:assoc remote Name %s\n",data->msg.assocVar.remoteName);
        printf("SCTP_MIB: assoc local port %d\n",data->msg.assocVar.srcPort);
        printf("SCTP_MIB: assoc Destination port %d\n",data->msg.assocVar.destPort);
        printf("SCTP_MIB: assoc primary remote address type %d\n",
            data->msg.assocVar.remPrimAddrType);
        printf("SCTP_MIB: association primary remote address %d\n",
            data->msg.assocVar.remPrimAddr);
        printf("SCTP_MIB: association Heartbeat Flag %s\n",
            data->msg.assocVar.hbState? "Inactive" : "Active" );
        printf("SCTP_MIB: association Heartbeat Timer %ld\n",
            data->msg.assocVar.hbTimer);
        printf("SCTP_MIB: association state %s\n", 
            assocstate[data->msg.assocVar.state]);
        printf("SCTP_MIB: association no of inbound streams %ld\n",
            data->msg.assocVar.numInStreams);
        printf("SCTP_MIB: get assoc no of outbound streams %ld\n"
            ,data->msg.assocVar.numOutStreams);
        printf("SCTP_MIB: association Max Retransmission %d\n",
            data->msg.assocVar.maxRetrans);
        printf("SCTP_MIB: get association start time %ld\n",
            data->msg.assocVar.startTime);
        
        break;

    case SCTP_MIB_T1_EXPIRED:

        printf("SCTP_MIB:association T1 expired count %ld\n",
            data->msg.assocCounter.t1Expired);


        break;

    case SCTP_MIB_T2_EXPIRED:

        printf("SCTP_MIB: association T2 expired count %ld\n",
            data->msg.assocCounter.t2Expired);

        break;

    case SCTP_MIB_RETR_CHUNKS:

        printf("SCTP_MIB: assoc no of chunks retransmitted %ld\n",
           data->msg.assocCounter.retransChunks );


        break;

    case SCTP_MIB_CKSUM_ERROR:

        printf("SCTP_MIB: assoc no of checksum errors %ld\n",
            data->msg.assocCounter.chksumError);

        break;

    case SCTP_MIB_ASSOC_STATISTICS:

        printf(("SCTP_MIB: all association statistics \n"));

        printf("SCTP_MIB:association T1 expired count %ld\n",
            data->msg.assocCounter.t1Expired);
        printf("SCTP_MIB: association T2 expired count %ld\n",
            data->msg.assocCounter.t2Expired);
        printf("SCTP_MIB: assoc no of chunks retransmitted %ld\n",
           data->msg.assocCounter.retransChunks );
        printf("SCTP_MIB: assoc no of checksum errors %ld\n",
            data->msg.assocCounter.chksumError);

        break;

    case SCTP_MIB_LCL_ADDR_TYPE:

        printf ("SCTP_MIB: Local Address Table:\n");
        printf (" Total Local interfaces are: %d\n",data->numNets);
        
 
        for (i = 0; i < data->numNets; i++)
        {
            /* For now we support only IPv4 address */
            printf(" address type %d, for intf: %d\n"
                ,data->msg.lclIpTable[i].addrType,i);
        }

        break;

    case SCTP_MIB_LCL_IP_ADDR:
        
        printf ("SCTP_MIB: Local Address Table:\n");
        printf (" Total Local interfaces are: %d\n",data->numNets);

        for (i = 0; i < data->numNets; i++)
        {
           printf(" address %d, for intf: %d\n"
                ,data->msg.lclIpTable[i].addr,i);          
        }

        break;
    case SCTP_MIB_LCL_IP_START_TIME:

        printf("SCTP_MIB: Local address table: start time %ld\n",
            data->msg.lclIpTable[0].startTime);

         break;

    case SCTP_MIB_LOCAL_IP_TABLE:

        printf ("SCTP_MIB: Local Address Table:\n");
        printf (" Total Local interfaces are: %d\n",data->numNets);

        printf("SCTP_MIB: Local address table: start time %ld\n",
            data->msg.lclIpTable[0].startTime);
 

        for (i = 0; i < data->numNets; i++)
        {
            printf("address type %d, for intf: %d\n"
                ,data->msg.lclIpTable[i].addrType,i);
            printf("address %d, for intf: %d\n"
                ,data->msg.lclIpTable[i].addr,i);
        }

        break;

    case SCTP_MIB_REM_ADDR_TYPE:

        printf("Remote Addr Table: Total interface %d\n",
            data->numRemote);
 
        for (i = 0; i < data->numRemote; i++)
        {
            printf("SCTP_MIB: Remote address table: addr Type :%d for intf %d\n",
                data->msg.remIpTable[i].addrType, i);
        }

        break;

#if 0

    case SCTP_MIB_REM_IP_ADDR:   

        printf(("SCTP_MIB: get Remote address table: address\n"));

        assoc = FindTCBv4(&manager, to->sin_addr.s_addr, to->sin_port,
                          manager.usocks[idx].port, NULL);
        if (assoc == NULL)
        {
            MUTEX_ReleaseMutex(&manager.gate);

            return (ITS_ENOTFOUND);
        }
        if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 10 )
        {
            data->numRemote = 10;
        }
        else if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 0 )
        {
            data->numRemote = SCTP_TCB_NUM_REMOTE_EPS(assoc);
        }
        else
        {
            data->numRemote = 0;
        }

        for (i = 0; i < SCTP_TCB_NUM_REMOTE_EPS(assoc); i++)
        {
            SCTPTRAN_REMOTE_EP *remt = &SCTP_TCB_REMOTE_EPS(assoc)[i];
            /* supporting IPv4 address only */
            data->msg.remIpTable[i].addr = SCTPTRAN_RE_REM_ADDR(remt);
        }

        break;

    case SCTP_MIB_REM_ADDR_STATE:

        printf(("SCTP_MIB: get Remote address table: Rem state\n"));

        assoc = FindTCBv4(&manager, to->sin_addr.s_addr, to->sin_port,
                          manager.usocks[idx].port, NULL);
        if (assoc == NULL)
        {
            MUTEX_ReleaseMutex(&manager.gate);

            return (ITS_ENOTFOUND);
        }
        if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 10 )
        {
            data->numRemote = 10;
        }
        else if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 0 )
        {
            data->numRemote = SCTP_TCB_NUM_REMOTE_EPS(assoc);
        }
        else
        {
            data->numRemote = 0;
        }

        for (i = 0; i < SCTP_TCB_NUM_REMOTE_EPS(assoc); i++)
        {
            SCTPTRAN_REMOTE_EP *remt = &SCTP_TCB_REMOTE_EPS(assoc)[i];
            if (SCTPTRAN_RE_TSTATE(remt) == SCTP_TRANS_DOWN)
            {
                /* MIB needs 1- inactive (down), 0 for active */
                data->msg.remIpTable[i].status = 1;
            }
            else
            {
                data->msg.remIpTable[i].status = 0;
            }
        }

        break;

    case SCTP_MIB_REM_ADDR_RTO:

        printf(("SCTP_MIB: get Remote address table: Rto\n"));

        assoc = FindTCBv4(&manager, to->sin_addr.s_addr, to->sin_port,
                          manager.usocks[idx].port, NULL);
        if (assoc == NULL)
        {
            MUTEX_ReleaseMutex(&manager.gate);

            return (ITS_ENOTFOUND);
        }
        if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 10 )
        {
            data->numRemote = 10;
        }
        else if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 0 )
        {
            data->numRemote = SCTP_TCB_NUM_REMOTE_EPS(assoc);
        }
        else
        {
            data->numRemote = 0;
        }

        for (i = 0; i < SCTP_TCB_NUM_REMOTE_EPS(assoc); i++)
        {
            SCTPTRAN_REMOTE_EP *remt = &SCTP_TCB_REMOTE_EPS(assoc)[i];
            
            data->msg.remIpTable[i].rto = SCTPTRAN_RE_RTO(remt);
        }

        break;
    case SCTP_MIB_REM_MAX_PATH_RETR:

        printf(("SCTP_MIB: get Rem address table: maxPathRetran\n"));

        assoc = FindTCBv4(&manager, to->sin_addr.s_addr, to->sin_port,
                          manager.usocks[idx].port, NULL);
        if (assoc == NULL)
        {
            MUTEX_ReleaseMutex(&manager.gate);

            return (ITS_ENOTFOUND);
        }
        if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 10 )
        {
            data->numRemote = 10;
        }
        else if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 0 )
        {
            data->numRemote = SCTP_TCB_NUM_REMOTE_EPS(assoc);
        }
        else
        {
            data->numRemote = 0;
        }

        for (i = 0; i < SCTP_TCB_NUM_REMOTE_EPS(assoc); i++)
        {
            SCTPTRAN_REMOTE_EP *remt = &SCTP_TCB_REMOTE_EPS(assoc)[i];
          
            data->msg.remIpTable[i].maxPathRetrans = 
                SCTPTRAN_RE_ERROR_THRESHOLD(remt);
        }

        break;
    case SCTP_MIB_REM_RETR_COUNT:

        printf(("SCTP_MIB: get Remote address table: Retrans\n"));

        assoc = FindTCBv4(&manager, to->sin_addr.s_addr, to->sin_port,
                          manager.usocks[idx].port, NULL);
        if (assoc == NULL)
        {
            MUTEX_ReleaseMutex(&manager.gate);

            return (ITS_ENOTFOUND);
        }
        if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 10 )
        {
            data->numRemote = 10;
        }
        else if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 0 )
        {
            data->numRemote = SCTP_TCB_NUM_REMOTE_EPS(assoc);
        }
        else
        {
            data->numRemote = 0;
        }

        for (i = 0; i < SCTP_TCB_NUM_REMOTE_EPS(assoc); i++)
        {
            SCTPTRAN_REMOTE_EP *remt = &SCTP_TCB_REMOTE_EPS(assoc)[i];
           
            data->msg.remIpTable[i].retransCount = SCTPTRAN_RE_ERROR_COUNT(remt);
        }

        break;

    case SCTP_MIB_REM_IP_START_TIME:

        printf(("SCTP_MIB: get Rem address start time\n"));

        assoc = FindTCBv4(&manager, to->sin_addr.s_addr, to->sin_port,
                          manager.usocks[idx].port, NULL);
        if (assoc == NULL)
        {
            MUTEX_ReleaseMutex(&manager.gate);

            return (ITS_ENOTFOUND);
        }
        if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 10 )
        {
            data->numRemote = 10;
        }
        else if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 0 )
        {
            data->numRemote = SCTP_TCB_NUM_REMOTE_EPS(assoc);
        }
        else
        {
            data->numRemote = 0;
        }

        for (i = 0; i < SCTP_TCB_NUM_REMOTE_EPS(assoc); i++)
        {
            SCTPTRAN_REMOTE_EP *remt = &SCTP_TCB_REMOTE_EPS(assoc)[i];
            /* supporting IPv4 address only */
            data->msg.remIpTable[i].startTime = SCTPTRAN_RE_START_TIME(remt);
        }

        break;
    case SCTP_MIB_REM_IP_TABLE:

        printf(("SCTP_MIB: get Remote address table\n"));

        assoc = FindTCBv4(&manager, to->sin_addr.s_addr, to->sin_port,
                          manager.usocks[idx].port, NULL);
        if (assoc == NULL)
        {
            MUTEX_ReleaseMutex(&manager.gate);

            return (ITS_ENOTFOUND);
        }
        if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 10 )
        {
            data->numRemote = 10;
        }
        else if (SCTP_TCB_NUM_REMOTE_EPS(assoc) > 0 )
        {
            data->numRemote = SCTP_TCB_NUM_REMOTE_EPS(assoc);
        }
        else
        {
            data->numRemote = 0;
        }

        for (i = 0; i < SCTP_TCB_NUM_REMOTE_EPS(assoc); i++)
        {
            SCTPTRAN_REMOTE_EP *remt = &SCTP_TCB_REMOTE_EPS(assoc)[i];

            data->msg.remIpTable[i].addrType = SCTPTRAN_RE_ADDR_TYPE(remt);
            data->msg.remIpTable[i].addr = SCTPTRAN_RE_REM_ADDR(remt);

            if (SCTPTRAN_RE_TSTATE(remt) == SCTP_TRANS_DOWN)
            {
                /* MIB needs 1- inactive (down), 0 for active */
                data->msg.remIpTable[i].status = 1;
            }
            else
            {
                data->msg.remIpTable[i].status = 0;
            }
        
            data->msg.remIpTable[i].rto = SCTPTRAN_RE_RTO(remt);
            data->msg.remIpTable[i].maxPathRetrans = 
                SCTPTRAN_RE_ERROR_THRESHOLD(remt);
            data->msg.remIpTable[i].retransCount = SCTPTRAN_RE_ERROR_COUNT(remt);
            data->msg.remIpTable[i].startTime = SCTPTRAN_RE_START_TIME(remt);
        }

        break;
#endif
    default:
        printf(("SCTP_MIB: get unknown\n"));
        break;
    }

    return;
       
}


/*
 * receive user input and act upon it. 
 */
void
handleStdin(ITS_USHORT sd)
{
    int ret, lenread;
    char readBuffer[256];
    SCTP_API_IOCTL_ARG arg;
    SCTP_API_MIB_DATA mibarg;

    fgets(readBuffer,256,stdin);
    lenread = strlen(readBuffer);

    if (readBuffer[(lenread-1)] == '\n')
    {
        readBuffer[(lenread-1)] = 0;
    }

    payload = 0;
    if (lenread == 0)
    {
        printf(">");
        fflush(stdout);
        return;
    }

    memset(&arg, 0, sizeof(arg));

    if (strcmp(readBuffer, "help") == 0)
    {
        printf("Available commands are:\n");
        printf(" quit - exit the program\n");
        printf(" sethost:host/X.Y.Z.A - set the destination host IP address\n");
        printf(" setport:port   - set the destination SCTP port number\n");
        printf(" setopts:val    - set options to specified value\n");
        printf(" setpay:payloadt - set the payload type\n");
        printf(" setdefstrm:num - set the default stream to\n");
        printf(" getcookielife  - display current assoc cookieLife\n");
        printf(" chgcookielife:val  - change the current assoc cookieLife\n");
        printf(" ping:size:stream:times - play ping pong\n");
        printf(" outqueue - report outqueue empty\n");
        printf(" bulk:size:stream:number - send a bulk of messages\n");
        printf(" setstrms:numpreopenstrms - set the number of strms "
               "I request\n");
        printf(" assoc - associate with the set destination\n");
        printf(" setprimary:host/X.Y.Z.A - set host\n");
        printf(" term - terminate the set destination association "
               "(graceful shutdown )\n");
        printf(" getpegs - retrieve the peg counts\n");
        printf(" getMIBinfo:n - retrieve the MIB info for parameter n\n");
        printf(" clearpegs - clear the peg counts\n");
        printf(" netstats - return all network stats\n");
        printf(" heart:on/off - Turn HB on or off  to the destination\n");
        printf(" heartdelay:time - Add number of seconds + RTO to hb "
               "interval\n");
        printf(" continual:flagval - set continuous init to n times\n");
        printf(" gethbdelay - get the hb delay\n");
        printf(" defrwnd:num - set the default rwnd of the SCTP\n");
        printf(" whereto - tell where the default sends\n");
        printf(" defretrys:num - set a new association failure threshold for "                 "sending\n");
        printf(" defretryi:num - set a new association failure threshold for "                 "initing\n");
        printf(" seterr:num - set the association send error thresh\n");
        printf(" setneterr:net:num - set the association network error "
               "thresh\n");
        printf(" doheartbeat - preform a on demand HB\n");
        printf(" SSN:stream - Find last In Seq Stream Seq number fror stream\n");
        printf(" rb:SSN:stream - Retrive buffers from SCTP, SSN onwards\n");
        printf(" rwnd - get rwnds\n");
        printf(" sendloop:N - send test script loopback request of N size\n");
        printf(" sendloopend:N - send test script loopback request of N size "
               "and terminate\n");
        printf(" setbpmode:ascii - set bulk transfer mode to ascii\n");
        printf(" setbpmode:binary - set bulk transfer mode to binary\n");
        printf(" some-other-string - send this to a peer if a peer is set\n");
    }
    else if (strncmp(readBuffer, "setprimary:", 11) == 0)
    {
        ITS_UINT x;
        ITS_USHORT port;

        port = to_ip.sin_port;
        to_ip.sin_addr.s_addr = translateIPAddress(&readBuffer[11]);
        x = ntohl(to_ip.sin_addr.s_addr);

        printf("set primary to %d.%d.%d.%d:%d\n",
               (int)((x>>24) & 0x000000ff),
               (int)((x>>16) & 0x000000ff),
               (int)((x>>8) & 0x000000ff),
               (int)(x & 0x000000ff),
               to_ip.sin_port
               );

        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_SET_PRIMARY, &arg);
    }
    else if (strncmp(readBuffer, "sendloopend:", 12) == 0)
    {
        int x;

        x = (int)strtol(&readBuffer[12],NULL,0);

        if (x == 0)
        {
            printf("N was 0? defaulting to 64\n");
            x = 64;
        }

        printf("Send loop request returns:%d\n", sendLoopRequest(sd, x));

        sendOptions |= SCTP_SR_SHUTDOWN;
        sendOne(sd, &to_ip, 0, 0, NULL, 0);
        sendOptions &= ~SCTP_SR_SHUTDOWN;

        printf("Sent loop and termintate queued\n");
    }
    else if (strncmp(readBuffer, "sendloop:", 9) == 0)
    {
        int x, ret;

        x = (int)strtol(&readBuffer[9],NULL,0);

        if (x == 0)
        {
            printf("N was 0? defaulting to 64\n");
            x = 64;
        }

        ret = sendLoopRequest(sd, x);

        printf("Sent loop returned %d\n", ret);
    }
    else if (strcmp(readBuffer, "getcookielife") == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));

        SCTP_Ioctl(sd, IOCTL_GET_COOKIE_LIFE, &arg);

        printf("Current cookie life is %d seconds\n", arg.value);
    }
    else if (strncmp(readBuffer, "setpay:", 7) == 0)
    {
        payload = strtol(&readBuffer[10], NULL, 0);
        printf("payloadtype set to %d\n", payload);
    }
    else if (strncmp(readBuffer, "continual:", 10) == 0)
    {
        continualINIT = strtol(&readBuffer[10], NULL, 0);
        printf("continual INIT set to %d\n", continualINIT);
    }
    else if (strncmp(readBuffer, "chgcookielife:", 14) == 0)
    {
        arg.value = strtol(&readBuffer[14],NULL,0);

        if (arg.value == 0)
        {
            printf("sorry can't set cookie life to 0\n");
        }
        else
        {
            memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));

            if (SCTP_Ioctl(sd, IOCTL_SET_COOKIE_LIFE, &arg) >= 0)
            {
                printf("I set cookie life to %d\n", arg.value);
            }
            else
            {
                printf("Set cookie life to %d\n", arg.value);

                SCTP_Ioctl(sd, IOCTL_SET_INIT_COOK_LIFE, &arg);
            }
        }
    }
    else if (strcmp(readBuffer, "whereto") == 0)
    {
        ITS_UINT x;

        to_ip.sin_addr.s_addr = translateIPAddress(&readBuffer[11]);

        x = ntohl(to_ip.sin_addr.s_addr);
        printf("sends go to %d.%d.%d.%d:%d\n",
               (int)((x>>24) & 0x000000ff),
               (int)((x>>16) & 0x000000ff),
               (int)((x>>8) & 0x000000ff),
               (int)(x & 0x000000ff),
               to_ip.sin_port
               );
    }
    else if (strcmp(readBuffer, "quit") == 0)
    {
        mainnotDone = 0;
        /* print no prompt, we are out of here once all
         * datagrams de-queue
         */
        return;
    }
    else if (strncmp(readBuffer,"rwnd", 4) == 0)
    {
        int rwnd, myrwnd;

        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_LOCAL_RWND, &arg);
        myrwnd = arg.value;
        SCTP_Ioctl(sd, IOCTL_GET_PEER_RWND, &arg);
        rwnd = arg.value;

        printf("My rwnd:%d peers rwnd:%d\n", myrwnd,rwnd);
    }
    else if(strncmp(readBuffer,"heart:", 6) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));

        if (strncmp(&readBuffer[6],"off", 3) == 0)
        {
            arg.value = 0;
            if (SCTP_Ioctl(sd, IOCTL_SET_HEARTBEAT, &arg) < 0)
            {
                SCTP_Ioctl(sd, IOCTL_SET_INIT_HB_ON, &arg);
            }
        }
        else
        {
            arg.value = 1;
            if (SCTP_Ioctl(sd, IOCTL_SET_HEARTBEAT, &arg) < 0)
            {
                SCTP_Ioctl(sd, IOCTL_SET_INIT_HB_ON, &arg);
            }
        }
    }
    else if (strcmp(readBuffer,"getrtt") == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_RTO_REPORT, &arg);

        printf("RTT of TO is %d\n", arg.value);
    }
    else if(strncmp(readBuffer,"defrwnd:", 8) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        arg.value = strtol(&readBuffer[8], NULL, 0);

        SCTP_Ioctl(sd, IOCTL_SET_LOCAL_RWND, &arg);
    }
    else if (strncmp(readBuffer, "defretrys:", 10) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        arg.value = strtol(&readBuffer[10], NULL, 0);

        SCTP_Ioctl(sd, IOCTL_SET_SEND_ATTEMPTS , &arg);
    }
    else if (strncmp(readBuffer, "defretryi:", 10) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_INIT_DATA, &arg);
        arg.value3 = strtol(&readBuffer[10], NULL, 0);
        SCTP_Ioctl(sd, IOCTL_SET_INIT_DATA , &arg);
    }
    else if(strcmp(readBuffer,"doheartbeat") == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        printf("Request returns %d\n",
               SCTP_Ioctl(sd, IOCTL_REQUEST_HEARTBEAT, &arg));
    }
    else if (strncmp(readBuffer, "heartdelay:", 11) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        arg.value = strtol(&readBuffer[11], NULL, 0);
        SCTP_Ioctl(sd, IOCTL_SET_HEARTBEAT_DELAY, &arg);
    }
    else if (strcmp(readBuffer,"gethbdelay") == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_HEARTBEAT_DELAY, &arg);

        printf("HB delay is %d plus RTT\n", arg.value);
    }
    else if (strcmp("outqueue",readBuffer) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_OUTBOUND_FLUSHED, &arg);
        printf("Outbound queue flushed = %d\n", arg.value);
    }
    else if (strcmp("term", readBuffer) == 0)
    {
        sendOptions |= SCTP_SR_SHUTDOWN;
        sendOne(sd, &to_ip, 0, 0, NULL, 0);
        sendOptions &= ~SCTP_SR_SHUTDOWN;
    }
    else if (strcmp("abort", readBuffer) == 0)
    {
        sendOptions |= SCTP_SR_ABORT;
        sendOne(sd, &to_ip, 0, 0, NULL, 0);
        sendOptions &= ~SCTP_SR_ABORT;
    }
    else if (strncmp("setstrms:", readBuffer, 9) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_INIT_DATA, &arg);

        arg.value = strtol(&readBuffer[9], NULL, 0);
        SCTP_Ioctl(sd, IOCTL_SET_INIT_DATA, &arg);
    }
    else if (strcmp("assoc", readBuffer) == 0)
    {
        if (destinationSet >= 2)
        {
            SCTP_Connect(sd,
                         (SOCK_AddrStore *)&to_ip,
                         sizeof(struct sockaddr_in));
        }
        else
        {
            printf("You must set a destination first.\n");
        }
    }
    else if (strncmp("ping:", readBuffer, 5) == 0)
    {
        char *end,*nxt;
        int skip;

        skip = 0;

        if (pingPongCount)
        {
            printf("Sorry ping-pong already in progress\n");
            printf(">");
            fflush(stdout);

            return;
        }

        pingBufSize = strtol(&readBuffer[5], &end, 0);
        if (end != NULL)
        {
            if(*end != ':')
            {
                skip = 1;
            }
        }
        else
        {
            skip = 1;
        }

        if(skip)
        {
            printf("mal-formed request at size\n");
            printf(">");
            fflush(stdout);

            return;
        }

        nxt = end;
        nxt++;

        pingStream = strtol(nxt, &end, 0);
        if (end != NULL)
        {
            if(*end != ':')
            {
                skip = 1;
            }
        }
        else
        {
            skip = 1;
        }

        if (skip)
        {
            printf("mal-formed request stream\n");
            printf(">");
            fflush(stdout);

            return;
        }    

        nxt = end;
        nxt++;

        pingPongCount = strtol(nxt, NULL, 0);
        if (pingPongCount == 0)
        {
            printf("mal-formed request at times\n");
            printf(">");
            fflush(stdout);

            return;
        }

        /* prepare ping buffer */
        doPingPong(sd);
    }
    else if (strncmp("setbpmode:a", readBuffer, 11) == 0)
    {
        bulkPingMode = 0;
        printf("bulk/ping transfer set to ascii mode\n");
    }
    else if (strncmp("setbpmode:b", readBuffer, 11) == 0)
    {
        bulkPingMode = 1;
        printf("bulk/ping transfer set to binary mode\n");
    }
    else if (strncmp("bulk:", readBuffer, 5) == 0)
    {
        int ret;
        char *end,*nxt;
        int skip,i;

        skip = 0;

        if (bulkInProgress)
        {
            printf("sorry bulk already in progress\n");
            printf(">");
            fflush(stdout);

            return;
        }

        bulkBufSize = strtol(&readBuffer[5], &end, 0);
        if (end != NULL)
        {
            if (*end != ':')
            {
                skip = 1;
            }
        }
        else
        {
            skip = 1;
        }

        if (skip)
        {
            printf("mal-formed request at size\n");
            printf(">");
            fflush(stdout);

            return;
        }

        nxt = end;
        nxt++;

        bulkStream = strtol(nxt, &end, 0);
        if (end != NULL)
        {
            if (*end != ':')
            {
                skip = 1;
            }
        }
        else
        {
            skip = 1;
        }

        if (skip)
        {
            printf("mal-formed request stream\n");
            printf(">");
            fflush(stdout);

            return;
        }    

        nxt = end;
        nxt++;

        bulkCount = strtol(nxt, NULL, 0);
        if (bulkCount == 0)
        {
            printf("mal-formed request at times\n");
            printf(">");
            fflush(stdout);

            return;
        }

        /* prepare ping buffer */
    
        /* ask for the time */
        if (bulkPingMode == 0)
        {
            strcpy(pingBuffer,"time");
            ret = sendOne(sd, &to_ip, bulkStream, payload, pingBuffer, 5);

            strncpy(pingBuffer,"bulk",4);

            for(i=4;i<bulkBufSize;i++)
            {
                pingBuffer[i] = 'A' + (i%26);
            }
        }

        bulkInProgress = 1;
        checkBulkTranfer(sd);

        if (bulkCount == 0)
        {
            printf("bulk message are now queued\n");
        }
        else
        {
            printf("bulk transfer now in progress\n");
        }
    }
    else if (strcmp("netstats", readBuffer) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_NUM_NETS, &arg);

        printf("There are %d networks for the destination\n",
                arg.value);

        SCTP_Ioctl(sd, IOCTL_GET_PEER_RWND, &arg);
        printf("peersRwnd: %d\n", arg.value);

        SCTP_Ioctl(sd, IOCTL_GET_RTO_REPORT, &arg);
        printf("RTO: %d\n", arg.value);

        SCTP_Ioctl(sd, IOCTL_GET_CWND_REPORT, &arg);
        printf("CWND: %d\n", arg.value);

        SCTP_Ioctl(sd, IOCTL_GET_SRTT_REPORT, &arg);
        printf("SRTT: %d\n", arg.value);

        SCTP_Ioctl(sd, IOCTL_GET_STATE_REPORT, &arg);
        printf("STATE: %d\n", arg.value);
    }
    else if (strncmp("setdefstrm:", readBuffer, 11) == 0)
    {
        defStream = strtol(&readBuffer[11],NULL,0);
    }
    else if (strncmp("SSN:",readBuffer,4) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        arg.value = strtol(&readBuffer[4],NULL,0);
        SCTP_Ioctl(sd, IOCTL_FIND_LAST_SSN, &arg);
        if (arg.value2 == SCTP_SSN_NOT_RETRIEVABLE)
        {
            printf("SCTP Assoc not available: SSN not Retrievable");
        }
    }
    else if (strncmp("rb:",readBuffer,3) == 0)
    {
        char *end,*nxt;
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        arg.value = strtol(&readBuffer[3],&end,0);
        nxt = end;
        nxt++;
        arg.value2 = strtol(nxt,NULL,0);
        SCTP_Ioctl(sd, IOCTL_RETRIEVE_BUFFER, &arg);
        if (arg.value3 == SCTP_RETRIVE_BUFFER_COMP)
        {
            printf("Association Not available: Retrive Buff Complete");
        }
    }
    else if (strncmp("seterr:",readBuffer,7) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        arg.value = strtol(&readBuffer[7],NULL,0);
        SCTP_Ioctl(sd, IOCTL_SET_ASSOC_ERR_THRESH, &arg);
    }
    else if (strncmp("setneterr:", readBuffer, 10) == 0)
    {
        char *nxt;
        int newrtry,net;

        net = strtol(&readBuffer[10], &nxt, 0);
        if (nxt == NULL)
        {
            printf("syntax error 'setneterr:net-num:val' please\n");
            printf(">");
            fflush(stdout);

            return;
        }

        nxt++;
        newrtry = strtol(nxt,NULL,0);

        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_GET_NUM_NETS, &arg);

        if (newrtry < 1 || net >= arg.value)
        {
            printf("syntax error 'setneterr:net-num:val' please\n");
            printf(">");
            fflush(stdout);

            return;
        }

        printf("Setting net:%d failure threshold to %d\n",
               net,newrtry);

        arg.value = newrtry;

        SCTP_Ioctl(sd, IOCTL_SET_NET_ERR_THRESH, &arg);
    }
    else if (strncmp("sethost:", readBuffer, 8) == 0)
    {
        ITS_UINT x;

        to_ip.sin_addr.s_addr = translateIPAddress(&readBuffer[8]);

        destinationSet++;

        x = ntohl(to_ip.sin_addr.s_addr);
        printf("host set to  %d.%d.%d.%d:%d\n",
               (int)((x>>24) & 0x000000ff),
               (int)((x>>16) & 0x000000ff),
               (int)((x>>8) & 0x000000ff),
               (int)(x & 0x000000ff),
               to_ip.sin_port
               );
    }
    else if (strncmp("setport:", readBuffer, 8) == 0)
    {
        ITS_USHORT pt;

        pt = (ITS_USHORT)strtol(&readBuffer[8],NULL,0);

        to_ip.sin_port = SOCK_HToNS(pt);

        printf("Port set to %d\n", pt);
        destinationSet++;
    }
    else if(strncmp("setopts:",readBuffer,8) == 0)
    {
        sendOptions = strtol(&readBuffer[8],NULL,0);
    }
    else if (strcmp("getpegs",readBuffer) == 0)
    {
        int i;
        ITS_UINT x;

        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        x = SCTP_Ioctl(sd, IOCTL_GET_PEGS, &arg);
        if (x >= 0)
        {
            for (i = 0; i < SCTP_PEG_MAX_PEGS; i++)
            {
                printf("Peg[%s] = %d\n", namelist[i], arg.pegs[i]);
            }
        }
    }
    else if (strncmp("getMIBinfo:",readBuffer, 11) == 0)
    {
        int val = strtol(&readBuffer[11],NULL,0);
        memcpy (&mibarg.addr, &to_ip, sizeof(struct sockaddr_in));
        ret = SCTP_GetMIBInfo(sd, val, &mibarg); 
        if (ret == ITS_SUCCESS)
        {
            printf(" get MIB Info resulted in \n");
            /* Print MIB Info */
            printMIBInfo(val, &mibarg);
        }
        else
        {
            printf("getMIBinfo failed error: %d", ret);
        }
    }
    else if(strcmp("clearpegs",readBuffer) == 0)
    {
        memcpy(&arg.addr, &to_ip, sizeof(struct sockaddr_in));
        SCTP_Ioctl(sd, IOCTL_CLEAR_PEGS, &arg);
    }
    else if(destinationSet >= 2)
    {
        /* default send the string to our peer */
        if ((pingPongCount>0) || bulkInProgress)
        {
            printf("Sorry bulk or ping in progress, you must "
                   "wait for completion before sending\n");
        }
        else
        {
            int xsxx;

            xsxx = sendOne(sd, &to_ip, defStream, payload, readBuffer, lenread);
            printf("Returned %d from the send\n",xsxx);
        }
    }
    else
    {
        printf("sorry first set a destination before sending\n");
    }

    printf(">");
    fflush(stdout);
}





THREAD_RET_TYPE
receiver(void *arg)
{
    ITS_USHORT sock = *(ITS_USHORT *)arg;

    sctpInput(sock);

    printf("**** Receiver exiting\n");

    THREAD_NORMAL_EXIT;
}

int
main(int argc, char **argv)
{
    struct sockaddr_in from;
    SOCK_IPv4Addr laddrs[2];
    int addrSet = 0, portSet = 0, i;
    ITS_USHORT sock;

    for (i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-i") == 0)
        {
            if (addrSet > 2)
            {
                continue;
            }

            if (i == argc - 1)
            {
                printf("missing arg\n");

                exit(EXIT_FAILURE);
            }

            laddrs[addrSet] = inet_addr(argv[i+1]);
            addrSet++;
            i++;
        }
        else if (strcmp(argv[i], "-p") == 0)
        {
            if (portSet)
            {
                continue;
            }

            if (i == argc - 1)
            {
                printf("missing arg\n");

                exit(EXIT_FAILURE);
            }

            myPort = SOCK_HToNS(atoi(argv[i+1]));

            portSet = 1;
        }
    }
        
    if (!addrSet || !portSet)
    {
        printf("missing args\n");

        exit(EXIT_FAILURE);
    }

    ITS_AddFeature(itsSCTP_Class);

    if (ITS_GlobalStart(0) != ITS_SUCCESS)
    {
        printf("Can't start\n");

        exit(EXIT_FAILURE);
    }

    printf("getting socket...\n");

    sock = SCTP_Socket(AF_INET, SCTP_DATAGRAM_SOCK);

    if (sock == ITS_INVALID_SRC)
    {
        printf("can't open socket\n");

        ITS_GlobalStop(0);

        ITS_RemFeature(itsSCTP_Class);

        exit(EXIT_FAILURE);
    }

    printf("binding...\n");

    for (i = 0; i < addrSet; i++)
    {
        from.sin_family = AF_INET;
        from.sin_addr.s_addr = laddrs[i];
        from.sin_port = myPort;
        if (SCTP_Bind(sock,
                      (SOCK_AddrStore *)&from,
                      sizeof(struct sockaddr_in)) < 0)
        {
            printf("error binding\n");

            SCTP_Close(sock);

            ITS_GlobalStop(0);

            ITS_RemFeature(itsSCTP_Class);

            exit(EXIT_FAILURE);
        }
    }

    if (THREAD_CreateThread(&recvThread, 0,
                            receiver, &sock, ITS_TRUE) != ITS_SUCCESS)
    {
        printf("error creating receiver\n");

        SCTP_Close(sock);

        ITS_GlobalStop(0);

        ITS_RemFeature(itsSCTP_Class);

        exit(EXIT_FAILURE);
    }

    while (mainnotDone)
    {
        handleStdin(sock);
    }

    SCTP_Close(sock);

    ITS_GlobalStop();

    ITS_RemFeature(itsSCTP_Class);

    exit(EXIT_SUCCESS);
}

