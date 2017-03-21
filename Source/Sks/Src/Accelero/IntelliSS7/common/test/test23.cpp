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
 *  ID: $Id: test23.cpp,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:52:28  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:07  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/06 22:24:37  mmiers
 * LOG: Convert to SUPPORT only
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:06:21  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.10  2000/06/02 15:51:36  mmiers
 * LOG:
 * LOG:
 * LOG: More sockets testing.
 * LOG:
 * LOG: Revision 1.9  2000/05/25 14:10:55  mmiers
 * LOG:
 * LOG:
 * LOG: Add port numbers
 * LOG:
 * LOG: Revision 1.8  2000/05/24 22:56:58  mmiers
 * LOG:
 * LOG:
 * LOG: Added in checksum
 * LOG:
 * LOG: Revision 1.7  2000/05/24 22:01:13  mmiers
 * LOG:
 * LOG:
 * LOG: More fixes for raw sockets.  Now 3 platforms down.
 * LOG:
 * LOG: Revision 1.6  2000/05/24 19:46:45  mmiers
 * LOG:
 * LOG:
 * LOG: Work around an NT limitation.
 * LOG:
 * LOG: Revision 1.5  2000/05/24 14:43:16  mmiers
 * LOG:
 * LOG:
 * LOG: Figuring out path MTU.
 * LOG:
 * LOG: Revision 1.4  2000/05/24 00:29:56  mmiers
 * LOG:
 * LOG:
 * LOG: Cross platform working.
 * LOG:
 * LOG: Revision 1.3  2000/05/24 00:25:00  mmiers
 * LOG:
 * LOG: Get this working on UNIX.  NT apparently automatically prepends
 * LOG: an IP header.  Unices apparently don't.
 * LOG:
 * LOG: Revision 1.2  2000/05/23 23:05:34  mmiers
 * LOG:
 * LOG:
 * LOG: Try to generate ICMP message.
 * LOG:
 * LOG: Revision 1.1  2000/05/23 18:48:04  mmiers
 * LOG:
 * LOG:
 * LOG: Raw tests.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:32  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1998/11/18 18:07:11  mmiers
 * LOG: Update project information.
 * LOG:
 * LOG: Revision 1.3  1998/09/23 22:04:31  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.2  1998/05/29 03:31:39  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.1  1998/04/09 23:43:46  mmiers
 * LOG: Debugging threads and sockets.
 * LOG:
 * LOG: Revision 1.1  1998/04/09 15:25:58  mmiers
 * LOG: Some cleanup for testing purposes.
 * LOG:
 *
 ****************************************************************************/

/*
 * list handling routines
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <exception>

#include <its++.h>
#include <its_thread.h>
#include <its_sockets.h>
#include <its_statics.cpp>
#include <its_adler.h>

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace std;
#endif

#define IPV4_HDR_SIZE	20
#define BIG_WRITE_SIZE	9000
#define BIG_WRITE_UNIT	10000
#define REQUIRE_IP_HDR	1
#define LOCALHOST       1

void
PrintHeader(SOCK_IPv4Header *hdr)
{
    printf(" IHL:      %01x\n", hdr->hdrLen);
    printf(" Version:  %01x\n", hdr->version);
    printf(" TOS:      %02x\n", hdr->typeOfService);
    printf(" TotalLen: %04x\n", ITS_Socket::NToHS(hdr->totalLen));
    printf(" ID:       %04x\n", ITS_Socket::NToHS(hdr->id));
    printf(" FragOff:  %04x\n", ITS_Socket::NToHS(hdr->fragOffset));
    printf(" TTL:      %02x\n", hdr->timeToLive);
    printf(" Protocol: %02x\n", hdr->protocol);
    printf(" Chksum:   %04x\n", ITS_Socket::NToHS(hdr->cksum));
    printf(" SrcAddr:  %08x\n", ITS_Socket::NToHL(hdr->saddr));
    printf(" DstAddr:  %08x\n", ITS_Socket::NToHL(hdr->daddr));
}

int
in_chksum(ITS_OCTET *p, int nbytes)
{
    long sum;
    ITS_USHORT oddbyte;
    ITS_USHORT answer;
    ITS_USHORT *ptr = (ITS_USHORT *)p;

    sum = 0;
    while (nbytes > 1)
    {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1)
    {
        oddbyte = 0;
        *((ITS_OCTET *)&oddbyte) = *(ITS_OCTET *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    answer = ~sum;

    return (answer);
}

int
main(int argc, char **argv)
{
    ITS_Socket *sock;
    void *addr;
    int len;

    if (ITS_Socket::CreateAddr(INET_DOMAIN, "192.168.1.13", 25000,
                               &addr, &len) != ITS_SUCCESS)
    {
        return (EXIT_FAILURE);
    }
    
    try
    {
        sock = new ITS_RawSocket(INET_DOMAIN, "192.168.1.57", 25001,
                                 IPPROTO_SCTP, false);
    }
    catch (exception& ex)
    {
        printf("Couldn't create client\n");

        return (EXIT_FAILURE);
    }

    printf("Connected to server.  Enter text to send.\n> ");
    fflush(stdout);

    ITS_UINT align;
    char buf[256];
memset(buf, 0, 256);

#if REQUIRE_IP_HDR
    SOCK_IPv4Header *hdr = (SOCK_IPv4Header *)buf;
    hdr->hdrLen = 5;
    hdr->version = 4;
    hdr->typeOfService = 0;
    hdr->totalLen = 0;
    hdr->id = ITS_Socket::HToNS(getpid());
    hdr->fragOffset = ITS_Socket::HToNS(SOCK_IPv4_FRAG_DONT_FLAG);
    hdr->timeToLive = 32;
    hdr->protocol = 255;
#if LOCALHOST
    hdr->saddr = ITS_Socket::HToNL(0x7f000001);
    hdr->daddr = ITS_Socket::HToNL(0x7f000001);
#else
    hdr->saddr = ITS_Socket::HToNL(0xc0a80139);
    hdr->daddr = ITS_Socket::HToNL(0xc0a8010d);
#endif

    while (gets(buf + IPV4_HDR_SIZE) != NULL)
    {
	ITS_USHORT *tmp = (ITS_USHORT *)buf + IPV4_HDR_SIZE;

        if (strlen(buf+IPV4_HDR_SIZE) == 0)
        {
            break;
        }

        strcat(buf+IPV4_HDR_SIZE, "\n");

        hdr->totalLen = ITS_Socket::HToNS(IPV4_HDR_SIZE + 4 +
                                            strlen(buf + IPV4_HDR_SIZE + 4));
        hdr->cksum = 0;
        hdr->cksum = in_chksum((ITS_OCTET *)buf, IPV4_HDR_SIZE);
printf("local form: %04x\n", hdr->cksum);
        hdr->cksum = ITS_Socket::HToNS(hdr->cksum);

        tmp[0] = ITS_Socket::HToNS(25001);
        tmp[1] = ITS_Socket::HToNS(25000);

printf("network form: %04x\n", hdr->cksum);
        PrintHeader(hdr);

        printf("Sending text: '%s' len %d returns %d\n",
               buf + IPV4_HDR_SIZE + 4,
               strlen(buf + IPV4_HDR_SIZE + 4) + IPV4_HDR_SIZE + 4,
               sock->Send(buf,
                          strlen(buf + IPV4_HDR_SIZE + 4) + IPV4_HDR_SIZE + 4,
                          addr, len));

        printf("> ");
        fflush(stdout);
    }
#else
    while (gets(buf) != NULL)
    {
        if (strlen(buf) == 0)
        {
            break;
        }

        strcat(buf, "\n");

        printf("Sending text: '%s' len %d returns %d\n",
               buf, strlen(buf),
               sock->Send(buf, strlen(buf), addr, len));

        printf("> ");
        fflush(stdout);
    }
#endif

    unsigned char *tmp = new unsigned char[BIG_WRITE_UNIT];
    memset(tmp, 0, BIG_WRITE_UNIT);

#if REQUIRE_IP_HDR
    hdr = (SOCK_IPv4Header *)tmp;
    hdr->hdrLen = 5;
    hdr->version = 4;
    hdr->typeOfService = 0;
    hdr->totalLen = ITS_Socket::HToNS(BIG_WRITE_SIZE + IPV4_HDR_SIZE);
    hdr->id = 0;
    hdr->fragOffset = 0;
    hdr->timeToLive = 32;
    hdr->protocol = 255;
    hdr->cksum = ITS_Socket::HToNS(in_chksum((ITS_OCTET *)tmp,
                                             IPV4_HDR_SIZE));
#if LOCALHOST
    hdr->saddr = ITS_Socket::HToNL(0x7f000001);
    hdr->daddr = ITS_Socket::HToNL(0x7f000001);
#else
    hdr->saddr = ITS_Socket::HToNL(0xc0a80139);
    hdr->daddr = ITS_Socket::HToNL(0xc0a8010d);
#endif

    PrintHeader(hdr);
#endif

    printf("Big write: %d\n", sock->Send((char *)tmp, BIG_WRITE_SIZE,
                                         addr, len));

#if 0
    if (sock->ReadyToRead())
#else
    while (1)
#endif
    {
        int len2;
        printf("Pending: recv: %d\n",
               (len2 = sock->Recv((char *)tmp, BIG_WRITE_UNIT, addr, &len)));

        if (len2 > 0)
        {
            PrintHeader((SOCK_IPv4Header *)tmp);

            printf("Data:\n");
            for (int i = 0; i < len2 - sizeof(SOCK_IPv4Header) && i < 20; i++)
            {
                printf("%02x ", (tmp + sizeof(SOCK_IPv4Header))[i]);
            }
            printf("\n");
        }
    }

    delete tmp;
    delete sock;

    free(addr);

    return (0);
}
