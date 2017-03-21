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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/04/12 15:36:30  hdivoux
 * LOG: ITSDLLAPI specifier for class and class record.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.16  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.15  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.14  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.13  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.12  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.11  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.10  2001/01/15 17:36:33  mmiers
 * LOG: Bug fixes from Olivier
 * LOG:
 * LOG: Revision 3.9  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.8  2000/12/20 17:49:49  mmiers
 * LOG: Solaris debugging.
 * LOG:
 * LOG: Revision 3.7  2000/11/30 19:37:45  mmiers
 * LOG: Ready to debug.
 * LOG:
 * LOG: Revision 3.6  2000/11/17 23:16:56  mmiers
 * LOG: Missed precedence values.
 * LOG:
 * LOG: Revision 3.5  2000/10/05 00:11:02  mmiers
 * LOG: Merge in the rev13 changes.
 * LOG:
 * LOG: Revision 3.4  2000/10/02 22:15:50  mmiers
 * LOG: More work.
 * LOG:
 * LOG: Revision 3.3  2000/09/28 21:49:47  mmiers
 * LOG:
 * LOG: Checkpoint for solaris build.
 * LOG:
 * LOG: Revision 3.2  2000/09/27 18:56:44  mmiers
 * LOG: Working on SCTP again.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:22  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.16  2000/08/03 22:47:31  mmiers
 * LOG: SCTP update.
 * LOG:
 * LOG: Revision 2.15  2000/06/02 15:51:32  mmiers
 * LOG:
 * LOG:
 * LOG: More sockets testing.
 * LOG:
 * LOG: Revision 2.14  2000/05/24 22:01:10  mmiers
 * LOG:
 * LOG:
 * LOG: More fixes for raw sockets.  Now 3 platforms down.
 * LOG:
 * LOG: Revision 2.13  2000/05/24 19:59:38  mmiers
 * LOG:
 * LOG:
 * LOG: Back this change out.  Special case only the windows code, its
 * LOG: the oddball here.
 * LOG:
 * LOG: Revision 2.12  2000/05/24 19:44:29  mmiers
 * LOG:
 * LOG:
 * LOG: Work around an NT limitation.
 * LOG:
 * LOG: Revision 2.11  2000/05/23 22:58:38  mmiers
 * LOG:
 * LOG:
 * LOG: Missing struct from IPv4 ICMP union.
 * LOG:
 * LOG: Revision 2.10  2000/05/23 22:18:50  mmiers
 * LOG:
 * LOG:
 * LOG: Add ICMP for v4, v6.
 * LOG:
 * LOG: Revision 2.9  2000/05/23 18:47:31  mmiers
 * LOG:
 * LOG:
 * LOG: Socket API update.
 * LOG:
 * LOG: Revision 2.8  2000/05/23 14:39:23  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a few typo bugs.
 * LOG:
 * LOG: Revision 2.7  2000/05/22 23:49:24  mmiers
 * LOG:
 * LOG:
 * LOG: Change signature for EndPointOpen
 * LOG:
 * LOG: Revision 2.6  2000/05/22 15:52:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add RAW socket type.
 * LOG:
 * LOG: Revision 2.5  2000/05/16 00:17:19  mmiers
 * LOG:
 * LOG:
 * LOG: Add C++ API for SOCK_GetPeerName().  Clean up GDI a bit.
 * LOG:
 * LOG: Revision 2.4  2000/05/03 21:07:14  mmiers
 * LOG:
 * LOG:
 * LOG: Start adding support for reader/writer locks.
 * LOG: Add SOCK_GetPeerName().
 * LOG:
 * LOG: Revision 2.3  2000/02/10 14:48:08  mmiers
 * LOG:
 * LOG: Add functions for network/host conversion so they're always in our
 * LOG: namespace.
 * LOG:
 * LOG: Revision 2.2  2000/01/05 00:24:58  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks for RUDP.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:58  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:44  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.22  1999/09/01 01:00:32  mmiers
 * LOG:
 * LOG:
 * LOG: Fix build errors.
 * LOG:
 * LOG: Revision 1.21  1999/06/28 23:45:23  skarmakar
 * LOG:
 * LOG:
 * LOG: More work on portability.
 * LOG:
 * LOG: Revision 1.20  1998/11/13 17:50:50  mmiers
 * LOG: Add UDP sockets to the collection.
 * LOG:
 * LOG: Revision 1.19  1998/09/22 15:17:59  mmiers
 * LOG: Fix brain damage.
 * LOG:
 * LOG: Revision 1.18  1998/09/21 19:09:03  jrao
 * LOG: Added HPUX support
 * LOG:
 * LOG: Revision 1.17  1998/09/03 17:13:24  hdivoux
 * LOG: Correction: Socket base class destructor is now virtual.
 * LOG:
 * LOG: Revision 1.16  1998/06/01 16:35:19  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.15  1998/05/31 23:59:10  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.14  1998/05/29 15:08:57  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.13  1998/05/29 03:31:32  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.12  1998/05/19 17:11:48  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.11  1998/05/14 01:22:43  mmiers
 * LOG: General cleanup.  Remove dead files.  Adjust include comments.
 * LOG:
 * LOG: Revision 1.10  1998/05/01 00:24:33  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.9  1998/04/16 04:32:01  mmiers
 * LOG: Cleanup for the gated versions.
 * LOG:
 * LOG: Revision 1.8  1998/04/09 23:43:42  mmiers
 * LOG: Debugging threads and sockets.
 * LOG:
 * LOG: Revision 1.7  1998/04/09 14:33:20  mmiers
 * LOG: Visual complains about operator= not having a return value even when hidden
 * LOG: in the private section of the class record and given a stub implementation.
 * LOG:
 * LOG: Revision 1.6  1998/04/09 01:47:19  mmiers
 * LOG: Some of these are false positives, but most have had modifications.  More
 * LOG: work on the infrastructure.
 * LOG:
 * LOG: Revision 1.5  1998/04/08 20:23:15  mmiers
 * LOG: Finish sockets API.
 * LOG:
 * LOG: Revision 1.4  1998/04/08 20:12:56  mmiers
 * LOG: update socket library and classes.
 * LOG:
 * LOG: Revision 1.3  1998/04/08 18:43:25  mmiers
 * LOG: Get sockets to build on Solaris.
 * LOG:
 * LOG: Revision 1.2  1998/04/08 17:25:27  mmiers
 * LOG: Work on sockets abstraction.
 * LOG:
 * LOG: Revision 1.1  1998/04/08 03:22:53  mmiers
 * LOG: New ITS APIs for trace, sockets.
 * LOG:
 * LOG: Revision 1.2  1998/03/05 21:38:04  ssharma
 * LOG: Changes to conform to coding standards.
 * LOG:
 *
 *****************************************************************************/

#ifndef ITS_SOCKETS_H
#define ITS_SOCKETS_H

#if !defined(ITS_SOCKETS_ONE_SHOT)
#define ITS_SOCKETS_ONE_SHOT

#include <its_object.h>

#ident "$Id: its_sockets.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

/*
 * IANA defined, but most platforms don't have it yet.
 */
#if !defined(IPPROTO_SCTP)
#define IPPROTO_SCTP    132
#endif

/*
 * determine the type of socket you want
 */
typedef enum 
{
    UNIX_DOMAIN,
    INET_DOMAIN
} 
ITS_SOCK_DOMAIN;

/*
 * determine the IP type, if INET_DOMAIN, else local
 */
typedef enum
{
    SPROT_TYPE_LOCAL_CLIENT,
    SPROT_TYPE_LOCAL_SERVER,
    SPROT_TYPE_TCP_CLIENT,
    SPROT_TYPE_TCP_SERVER,
    SPROT_TYPE_UDP,
    SPROT_TYPE_LOCAL_DATAGRAM,
    SPROT_TYPE_RAW
}
ITS_SPROTO_TYPE;

/*
 * socket management structure
 */
typedef struct
{
    ITS_SOCKET      socket;
    ITS_SPROTO_TYPE type;
    void*           addr;
    int             asize;
    int             af;
}
ITS_SocketInfo;

/*
 * polling struct
 */
typedef struct
{
    ITS_SocketInfo  *sinfo;
    int             lookFor;
    int             wasSet;
}
ITS_SockPollInfo;

#define SOCK_POLL_READ      0x01
#define SOCK_POLL_READ_OOB  0x02
#define SOCK_POLL_WRITE     0x04
#define SOCK_POLL_WRITE_OOB 0x08

#define SOCK_POLL_WAIT_FOREVER  (-1)

/*
 * normally I wouldn't define this crap, as it can be found in ip.h.
 * Windows, in it's unfortunate state, doesn't have a way to get these
 */
#define LOCAL_INTERFACE_STRING  "localInterface"
#define LOCAL_MASK_STRING       "localMask"
#define LOCAL_BCAST_STRING      "localBroadcast"

/*
 * normally I wouldn't define this crap, as it can be found in ip.h.
 * Windows, in it's unfortunate state, doesn't define these however.
 */

/******************************* IPv4 *********************************/
/******************************* IPv4 *********************************/
/******************************* IPv4 *********************************/

#define SOCK_V4_VERSION     4
#define SOCK_V6_VERSION     6

typedef ITS_UINT    SOCK_IPv4Addr;

/*
 * v4 timestamp
 */
typedef struct
{
    ITS_OCTET   len;
    ITS_OCTET   ptr;
#if (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
    (defined(BYTE_ORDER) && BYTE_ORDER == LITTLE_ENDIAN)
    ITS_OCTET   flags : 4,
                overflow : 4;
#elif (defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN) || \
      (defined(BYTE_ORDER) && BYTE_ORDER == BIG_ENDIAN)
    ITS_OCTET   overflow : 4,
                flags : 4;
#else
# error "Bytesex not defined"
#endif
    ITS_UINT    data[9];
}
SOCK_IPv4TimeStamp;

/*
 * v4 options
 */
typedef struct
{
    SOCK_IPv4Addr   faddr;
    ITS_OCTET       optlen;
    ITS_OCTET       srr;
    ITS_OCTET       rr;
    ITS_OCTET       ts;
    ITS_OCTET       isSetByUser : 1,
                    isData : 1,
                    isStrictRoute : 1,
                    srrIsHit : 1,
                    isChanged : 1,
                    rrNeedAddr : 1,
                    tsNeedTime : 1,
                    tsNeedAddr : 1;
    ITS_OCTET       routerAlert;
    ITS_OCTET       pad1;
    ITS_OCTET       pad2;
    /* data follows */
}
SOCK_IPv4Options;

/*
 * option defs
 */
#define SOCK_IPv4_OPT_COPY          0x80U
#define SOCK_IPv4_OPT_CLASS_MASK    0x60U
#define SOCK_IPv4_OPT_NUMBER_MASK   0x1FU

#define SOCK_IPv4_OPT_CONTROL       0x00U
#define SOCK_IPv4_RESERVED1         0x20U
#define SOCK_IPv4_MEASUREMENT       0x40U
#define SOCK_IPv4_RESERVED2         0x60U

#define SOCK_IPv4_OPT_END           0
#define SOCK_IPv4_OPT_NOOP          1
#define SOCK_IPv4_OPT_RECORD_ROUTE  7
#define SOCK_IPv4_OPT_TIMESTAMP     68
#define SOCK_IPv4_OPT_SECURITY      130
#define SOCK_IPv4_OPT_LOOSE_SRC_RT  131
#define SOCK_IPv4_OPT_SATNET_ID     136
#define SOCK_IPv4_OPT_STRICT_SRC_RT 137
#define SOCK_IPv4_OPT_ROUTER_ALERT  148

/*
 * v4 header
 */
typedef struct
{
#if (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
    (defined(BYTE_ORDER) && BYTE_ORDER == LITTLE_ENDIAN)
    ITS_OCTET       hdrLen : 4,
                    version : 4;
#elif (defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN) || \
      (defined(BYTE_ORDER) && BYTE_ORDER == BIG_ENDIAN)
    ITS_OCTET       version : 4,
                    hdrLen : 4;
#else
# error "Bytesex not defined"
#endif
    ITS_OCTET       typeOfService;
    ITS_USHORT      totalLen;
    ITS_USHORT      id;
    ITS_USHORT      fragOffset;
    ITS_OCTET       timeToLive;
    ITS_OCTET       protocol;
    ITS_USHORT      cksum;
    SOCK_IPv4Addr   saddr;
    SOCK_IPv4Addr   daddr;
    /* options start here */
}
SOCK_IPv4Header;

/*
 * types of service
 */
#define SOCK_IPv4_TOS_MASK      0x1EU
#define SOCK_IPv4_LOW_DELAY     0x10U
#define SOCK_IPv4_THROUGHPUT    0x08U
#define SOCK_IPv4_RELIABILITY   0x04U
#define SOCK_IPv4_LOWCOST       0x02U

#define SOCK_IPv4_MAX_LEN       65535U

#define SOCK_IPv4_PREC_NETCONTROL       0xE0U
#define SOCK_IPv4_PREC_INTERNETCONTROL  0xC0U
#define SOCK_IPv4_PREC_CRITIC_ECP       0xA0U
#define SOCK_IPv4_PREC_FLASH_OVERRIDE   0x80U
#define SOCK_IPv4_PREC_FLASH            0x60U
#define SOCK_IPv4_PREC_IMMEDIATE        0x40U
#define SOCK_IPv4_PREC_PRIORITY         0x20U
#define SOCK_IPv4_PREC_ROUTINE          0x00U

/*
 * fragOffset macros
 */
#define SOCK_IPv4_FRAG_RESERVED_FLAG 0x8000U
#define SOCK_IPv4_FRAG_DONT_FLAG     0x4000U
#define SOCK_IPv4_FRAG_MORE_FRAGS    0x2000U
#define SOCK_IPv4_FRAG_OFFSET_MASK   0x1FFFU

/*
 * timestamp flags
 */
#define SOCK_IPv4_TS_ONLY       0x00U
#define SOCK_IPv4_TS_AND_ADDR   0x01U
#define SOCK_IPv4_TS_PRESPEC    0x03U

/*
 * bits for security (not byte swapped)
 */
#define SOCK_IPv4_OPT_SECUR_UNCLASS     0x0000U
#define SOCK_IPv4_OPT_SECUR_CONFID      0xF135U
#define SOCK_IPv4_OPT_SECUR_EFTO        0x789AU
#define SOCK_IPv4_OPT_SECUR_MMMM        0xBC4DU
#define SOCK_IPv4_OPT_SECUR_RESTR       0xAF13U
#define SOCK_IPv4_OPT_SECUR_SECRET      0xD788U
#define SOCK_IPv4_OPT_SECUR_TOP_SECRET  0x6BC5U

#define SOCK_IPv4_MAX_TTL       255
#define SOCK_IPv4_DEFAULT_TTL   64
#define SOCK_IPv4_FRAG_TTL      60
#define SOCK_IPv4_TTL_DEC       1

#define SOCK_IPv4_IP_MSS        576

typedef struct
{
    ITS_OCTET  type;                    /* message type */
    ITS_OCTET  code;                    /* type sub-code */
    ITS_USHORT checksum;
    union
    {
        struct
        {
            ITS_USHORT  id;
            ITS_USHORT  sequence;
        }
        echo;                           /* echo datagram */
        SOCK_IPv4Addr	gateway;        /* gateway address */
        struct
        {
            ITS_USHORT  __unused;
            ITS_USHORT  mtu;
        }
        frag;			/* path mtu discovery */
        struct
        {
            ITS_OCTET   num_addrs;
            ITS_OCTET   wpa;
            ITS_USHORT  lifetime;
        }
        route_advert;
    }
    data;
}
SOCK_IPv4ICMPHeader;

#define SOCK_IPv4_ICMP_ECHOREPLY	0    /* Echo Reply		*/
#define SOCK_IPv4_ICMP_DEST_UNREACH	3    /* Destination Unreachable	*/
#define SOCK_IPv4_ICMP_SOURCE_QUENCH	4    /* Source Quench		*/
#define SOCK_IPv4_ICMP_REDIRECT		5    /* Redirect (change route)	*/
#define SOCK_IPv4_ICMP_ECHO		8    /* Echo Request		*/
#define SOCK_IPv4_ICMP_TIME_EXCEEDED	11   /* Time Exceeded		*/
#define SOCK_IPv4_ICMP_PARAMETERPROB	12   /* Parameter Problem	*/
#define SOCK_IPv4_ICMP_TIMESTAMP	13   /* Timestamp Request		*/
#define SOCK_IPv4_ICMP_TIMESTAMPREPLY	14   /* Timestamp Reply		*/
#define SOCK_IPv4_ICMP_INFO_REQUEST	15   /* Information Request	*/
#define SOCK_IPv4_ICMP_INFO_REPLY	16   /* Information Reply	*/
#define SOCK_IPv4_ICMP_ADDRESS		17   /* Address Mask Request	*/
#define SOCK_IPv4_ICMP_ADDRESSREPLY	18   /* Address Mask Reply	*/
#define SOCK_IPv4_NR_ICMP_TYPES		18


/*
 * Codes for UNREACH.
 */
#define SOCK_IPv4_ICMP_NET_UNREACH	0    /* Network Unreachable	*/
#define SOCK_IPv4_ICMP_HOST_UNREACH	1    /* Host Unreachable	*/
#define SOCK_IPv4_ICMP_PROT_UNREACH	2    /* Protocol Unreachable	*/
#define SOCK_IPv4_ICMP_PORT_UNREACH	3    /* Port Unreachable	*/
#define SOCK_IPv4_ICMP_FRAG_NEEDED	4    /* Fragmentation Needed/DF set*/
#define SOCK_IPv4_ICMP_SR_FAILED	5    /* Source Route failed	*/
#define SOCK_IPv4_ICMP_NET_UNKNOWN	6
#define SOCK_IPv4_ICMP_HOST_UNKNOWN	7
#define SOCK_IPv4_ICMP_HOST_ISOLATED	8
#define SOCK_IPv4_ICMP_NET_ANO		9
#define SOCK_IPv4_ICMP_HOST_ANO		10
#define SOCK_IPv4_ICMP_NET_UNR_TOS	11
#define SOCK_IPv4_ICMP_HOST_UNR_TOS	12
#define SOCK_IPv4_ICMP_PKT_FILTERED	13    /* Packet filtered */
#define SOCK_IPv4_ICMP_PREC_VIOLATION	14    /* Precedence violation */
#define SOCK_IPv4_ICMP_PREC_CUTOFF	15    /* Precedence cut off */
#define SOCK_IPv4_NR_ICMP_UNREACH	15    /* instead of hardcoding immediate value */

/*
 * Codes for REDIRECT.
 */
#define SOCK_IPv4_ICMP_REDIR_NET	0    /* Redirect Net		*/
#define SOCK_IPv4_ICMP_REDIR_HOST	1    /* Redirect Host		*/
#define SOCK_IPv4_ICMP_REDIR_NETTOS	2    /* Redirect Net for TOS	*/
#define SOCK_IPv4_ICMP_REDIR_HOSTTOS	3    /* Redirect Host for TOS	*/

/*
 * Codes for TIME_EXCEEDED.
 */
#define SOCK_IPv4_ICMP_EXC_TTL		0    /* TTL count exceeded	*/
#define SOCK_IPv4_ICMP_EXC_FRAGTIME	1    /* Fragment Reass time exceeded*/


/******************************* IPv6 *********************************/
/******************************* IPv6 *********************************/
/******************************* IPv6 *********************************/
/*
 * v6 header
 */
typedef struct
{
    union
    {
        ITS_OCTET   addrInfo8[16];
        ITS_USHORT  addrInfo16[8];
        ITS_UINT    addrInfo32[4];
    }
    _S6_un;
}
SOCK_IPv6Addr;

/*
 * v6 header
 */
typedef struct
{
    union 
    {
	struct
        {
            ITS_UINT    flow;       /* 24 bits of flow-ID */
            ITS_USHORT  payloadLen; /* payload length */
            ITS_OCTET   next;       /* next header */
            ITS_OCTET   hopLim;     /* hop limit */
        }
        stream;
        ITS_OCTET vfc;        /* 4 bits version, 4 bits priority */
    }
    control;
    SOCK_IPv6Addr saddr;      /* source address */
    SOCK_IPv6Addr daddr;      /* destination address */
}
SOCK_IPv6Header;

/*
 * Hop-by-Hop options header.
 */
typedef struct
{
    ITS_OCTET  next;       /* next hesder.  */
    ITS_OCTET  len;        /* length in units of 8 octets.  */
    /* followed by options */
}
SOCK_IPv6HopByHopOptsHdr;

/*
 * Destination options header
 */
typedef struct
{
    ITS_OCTET  next;       /* next header */
    ITS_OCTET  len;        /* length in units of 8 octets */
    /* followed by options */
}
SOCK_IPv6DestOptsHdr;

/*
 * Routing header
 */
typedef struct
{
    ITS_OCTET  next;       /* next header */
    ITS_OCTET  len;        /* length in units of 8 octets */
    ITS_OCTET  type;       /* routing type */
    ITS_OCTET  segleft;    /* segments left */
    /* followed by routing type specific data */
}
SOCK_IPv6RouteHdr;

/*
 * Type 0 Routing header
 */
typedef struct
{
    ITS_OCTET       next;      /* next header */
    ITS_OCTET       len;       /* length in units of 8 octets */
    ITS_OCTET       type;      /* always zero */
    ITS_OCTET       segleft;   /* segments left */
    ITS_OCTET       reserved;  /* reserved field */
    ITS_OCTET       slmap[3];  /* strict/loose bit map */
    SOCK_IPv6Addr   addr[1];   /* up to 23 addresses */
}
SOCK_IPv6Type0RouteHdr;

/*
 * Fragment header
 */
typedef struct
{
    ITS_OCTET   next;      /* next header */
    ITS_OCTET   reserved;  /* reserved field */
    ITS_USHORT  offlg;     /* offset, reserved, and flag */
    ITS_UINT    ident;     /* identification */
}
SOCK_IPv6FragHdr;


#define SOCK_IPv6_ICMP6_FILTER 1

#define SOCK_IPv6_ICMP6_FILTER_BLOCK		1
#define SOCK_IPv6_ICMP6_FILTER_PASS		2
#define SOCK_IPv6_ICMP6_FILTER_BLOCKOTHERS	3
#define SOCK_IPv6_ICMP6_FILTER_PASSONLY		4

typedef struct
{
    ITS_UINT data[8];
}
SOCK_IPv6ICMPFilter;

typedef struct
{
    ITS_OCTET     type;   /* type field */
    ITS_OCTET     code;   /* code field */
    ITS_USHORT    cksum;  /* checksum field */
    union 
    {
        ITS_UINT    un_data32[1]; /* type-specific field */
        ITS_USHORT  un_data16[2]; /* type-specific field */
        ITS_OCTET   un_data8[4];  /* type-specific field */
        ITS_UINT    pptr;         /* parameter prob */
        ITS_UINT    mtu;          /* packet to big */
        struct
        {
            ITS_USHORT  id;       /* echo request/reply */
            ITS_USHORT  seq;      /* echo request/reply */
        }
        echo;
        ITS_USHORT  maxdelay;     /* mcast group membership */
        ITS_UINT    rsreserved;   /* router solicitation */
        struct
        {
            ITS_OCTET  curhoplimit;
            ITS_OCTET  flags;
            ITS_USHORT lifetime;
            ITS_UINT   reachable;   /* reachable time */
            ITS_UINT   retransmit;  /* retransmit timer */
        }
        routerAdvert;               /* router advertisement */
        ITS_UINT    nsreserved;   /* neighbor solicit */
        ITS_UINT    naflags;      /* neighbor advertisement */
        ITS_UINT    redirect;     /* redirect */
    }
    data;
}
SOCK_IPv6ICMPHeader; 

#define SOCK_IPv6_ICMP6_DST_UNREACH             1
#define SOCK_IPv6_ICMP6_PACKET_TOO_BIG          2
#define SOCK_IPv6_ICMP6_TIME_EXCEEDED           3
#define SOCK_IPv6_ICMP6_PARAM_PROB              4

#define SOCK_IPv6_ICMP6_INFOMSG_MASK  0x80    /* all informational messages */

#define SOCK_IPv6_ICMP6_ECHO_REQUEST          128
#define SOCK_IPv6_ICMP6_ECHO_REPLY            129
#define SOCK_IPv6_ICMP6_MEMBERSHIP_QUERY      130
#define SOCK_IPv6_ICMP6_MEMBERSHIP_REPORT     131
#define SOCK_IPv6_ICMP6_MEMBERSHIP_REDUCTION  132

#define SOCK_IPv6_ICMP6_DST_UNREACH_NOROUTE     0 /* no route to destination */
#define SOCK_IPv6_ICMP6_DST_UNREACH_ADMIN       1 /* communication with
                                                   * destination
                                                   * administratively
                                                   * prohibited */
#define SOCK_IPv6_ICMP6_DST_UNREACH_NOTNEIGHBOR 2 /* not a neighbor */
#define SOCK_IPv6_ICMP6_DST_UNREACH_ADDR        3 /* address unreachable */
#define SOCK_IPv6_ICMP6_DST_UNREACH_NOPORT      4 /* bad port */

#define SOCK_IPv6_ICMP6_TIME_EXCEED_TRANSIT     0 /* Hop Limit == 0 in
                                                   * transit */
#define SOCK_IPv6_ICMP6_TIME_EXCEED_REASSEMBLY  1 /* Reassembly time out */

#define SOCK_IPv6_ICMP6_PARAMPROB_HEADER        0 /* erroneous header field */
#define SOCK_IPv6_ICMP6_PARAMPROB_NEXTHEADER    1 /* unrecognized Next Header */
#define SOCK_IPv6_ICMP6_PARAMPROB_OPTION        2 /* unrecognized IPv6 option */

#define SOCK_IPv6_ICMP6_FILTER_WILLPASS(type, filterp) \
	((((filterp)->data[(type) >> 5]) & (1 << ((type) & 31))) == 0)

#define SOCK_IPv6_ICMP6_FILTER_WILLBLOCK(type, filterp) \
	((((filterp)->data[(type) >> 5]) & (1 << ((type) & 31))) != 0)

#define SOCK_IPv6_ICMP6_FILTER_SETPASS(type, filterp) \
	((((filterp)->data[(type) >> 5]) &= ~(1 << ((type) & 31))))

#define SOCK_IPv6_ICMP6_FILTER_SETBLOCK(type, filterp) \
	((((filterp)->data[(type) >> 5]) |=  (1 << ((type) & 31))))

#define SOCK_IPv6_ICMP6_FILTER_SETPASSALL(filterp) \
	memset (filterp, 0, sizeof (SOCK_IPv6ICMPFilter))

#define SOCK_IPv6_ICMP6_FILTER_SETBLOCKALL(filterp) \
	memset (filterp, 0xFF, sizeof (SOCK_IPv6ICMPFilter))

#define SOCK_IPv6_ND_ROUTER_SOLICIT           133
#define SOCK_IPv6_ND_ROUTER_ADVERT            134
#define SOCK_IPv6_ND_NEIGHBOR_SOLICIT         135
#define SOCK_IPv6_ND_NEIGHBOR_ADVERT          136
#define SOCK_IPv6_ND_REDIRECT                 137

#define SOCK_IPv6_ND_RA_FLAG_MANAGED       0x80U
#define SOCK_IPv6_ND_RA_FLAG_OTHER         0x40U

#if (defined(__BYTE_ORDER) && __BYTE_ORDER == __BIG_ENDIAN) || \
    (defined(BYTE_ORDER) && BYTE_ORDER == BIG_ENDIAN)
#define SOCK_IPv6_ND_NA_FLAG_ROUTER        0x80000000
#define SOCK_IPv6_ND_NA_FLAG_SOLICITED     0x40000000
#define SOCK_IPv6_ND_NA_FLAG_OVERRIDE      0x20000000
#elif (defined(__BYTE_ORDER) && __BYTE_ORDER == __LITTLE_ENDIAN) || \
      (defined(BYTE_ORDER) && BYTE_ORDER == LITTLE_ENDIAN)
#define SOCK_IPv6_ND_NA_FLAG_ROUTER        0x00000080
#define SOCK_IPv6_ND_NA_FLAG_SOLICITED     0x00000040
#define SOCK_IPv6_ND_NA_FLAG_OVERRIDE      0x00000020
#else
# error "Bad bytesex"
#endif

/*
 * Neighbor discovery option header
 */
typedef struct nd_opt_hdr
{
    ITS_OCTET  opt_type;
    ITS_OCTET  opt_len;        /* in units of 8 octets */
    /* followed by option specific data */
}
SOCK_IPv6_ICMPNDOptionHdr;

#define  SOCK_IPv6_ND_OPT_SOURCE_LINKADDR       1
#define  SOCK_IPv6_ND_OPT_TARGET_LINKADDR       2
#define  SOCK_IPv6_ND_OPT_PREFIX_INFORMATION    3
#define  SOCK_IPv6_ND_OPT_REDIRECTED_HEADER     4
#define  SOCK_IPv6_ND_OPT_MTU                   5

/*
 * prefix information
 */
typedef struct nd_opt_prefix_info
{
    ITS_OCTET      pi_type;
    ITS_OCTET      pi_len;
    ITS_OCTET      pi_prefix_len;
    ITS_OCTET      pi_flags_reserved;
    ITS_UINT       pi_valid_time;
    ITS_UINT       pi_preferred_time;
    ITS_UINT       pi_reserved2;
    SOCK_IPv6Addr  pi_prefix;
}
SOCK_IPv6_ICMPNDOptionPrefix;

#define SOCK_IPv6_ND_OPT_PI_FLAG_ONLINK        0x80U
#define SOCK_IPv6_ND_OPT_PI_FLAG_AUTO          0x40U

/*
 * redirected header
 */
typedef struct
{
    ITS_OCTET   rh_type;
    ITS_OCTET   rh_len;
    ITS_USHORT  rh_reserved1;
    ITS_UINT    rh_reserved2;
    /* followed by IP header and data */
}
SOCK_IPv6_ICMPRedirectHdr;

/*
 * MTU option
 */
typedef struct
{
    ITS_OCTET   mtu_type;
    ITS_OCTET   mtu_len;
    ITS_USHORT  mtu_reserved;
    ITS_UINT    mtu_mtu;
}
SOCK_IPv6_ICMPMTUOption;

/*
 * RFC-2553 storage
 */

/*
 * Desired design of maximum size and alignment
 */
#define SOCK_SS_MAXSIZE    128
#define SOCK_SS_ALIGNSIZE  (sizeof(ITS_ULONG))

#if !defined(BSD_44_ADDRS)
/*
 * Definitions used for sockaddr_storage structure paddings design.
 */
#define SOCK_SS_PAD1SIZE   (SOCK_SS_ALIGNSIZE - sizeof(ITS_USHORT))

#define SOCK_SS_PAD2SIZE   (SOCK_SS_MAXSIZE - (sizeof(ITS_USHORT) + \
                                               SOCK_SS_PAD1SIZE +   \
                                               SOCK_SS_ALIGNSIZE))

typedef struct
{
    ITS_USHORT     __ss_family;
    ITS_CHAR       __ss_pad1[SOCK_SS_PAD1SIZE];
    ITS_ULONG      __ss_align;
    ITS_CHAR       __ss_pad2[SOCK_SS_PAD2SIZE];
}
SOCK_AddrStore;

#else /* BSD_44_ADDRS */

/*
 * Definitions used for sockaddr_storage structure paddings design.
 */
#define SOCK_SS_PAD1SIZE (SOCK_SS_ALIGNSIZE -   \
                          (sizeof(ITS_OCTET) +  \
                           sizeof(ITS_OCTET)))

#define SOCK_SS_PAD2SIZE (SOCK_SS_MAXSIZE - (sizeof(ITS_OCTET) +    \
                                             SOCK_SS_PAD1SIZE +     \
                                             SOCK_SS_ALIGNSIZE))

typedef struct
{
    ITS_OCTET    __ss_len;
    ITS_OCTET    __ss_family;
    ITS_CHAR     __ss_pad1[_SS_PAD1SIZE];
    ITS_ULONG    __ss_align;
    ITS_CHAR     __ss_pad2[_SS_PAD2SIZE];
}
SOCK_AddrStore;

#endif /* BSD_44_ADDRS */

#endif /* ITS_SOCKETS_ONE_SHOT */

/*
 * Forward Decls for procedures
 */
#ifdef __cplusplus
extern "C" {
#endif

/*.interface:SOCK
 *****************************************************************************
 *  Interface:
 *      SOCK_*
 *
 *  Purpose:
 *      The SOCK_* routines implement socket connections in C, Berkeley style.
 *
 *      Sockets are a generic inter-process inter-platform transport using
 *      (normally) the Internet Protocol (v4) and the Transmission Control
 *      Protocol; aka TCP/IP.  Socket connections have two sides; the server
 *      side and the client side.  The server side must exist, and be
 *      "listening" for connections before a client can connect.
 *
 *      Sockets are used in IntelliSS7 as an interplatform/interprocess
 *      communications mechanism by the TRANSPORT_ layer.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/* 
 * Return amount of bytes ready to read  
 */ 
ITSDLLAPI extern int SOCK_Pending(ITS_SocketInfo* sock); 

/* 
 * Return ITS_TRUE if socket is ready to read  
 */ 
ITSDLLAPI extern ITS_BOOLEAN SOCK_ReadyToRead(ITS_SocketInfo* sock); 
 

/*
 * open and initialize a server socket
 */
ITSDLLAPI extern int SOCK_ServerOpen(ITS_SocketInfo **info,
                                     ITS_SOCK_DOMAIN domain,
                                     const char *host_or_path,
                                     int port);

/* 
 * open and initialize a client socket
 */
ITSDLLAPI extern int SOCK_ClientOpen(ITS_SocketInfo **info,
                                     ITS_SOCK_DOMAIN domain,
                                     const char *host_or_path,
                                     int port);

/* 
 * open and initialize a client socket
 */
ITSDLLAPI extern int SOCK_EndPointOpen(ITS_SocketInfo **info,
                                       ITS_SOCK_DOMAIN domain,
                                       const char *host_or_path,
                                       int port);

/* 
 * open and initialize a raw socket
 */
ITSDLLAPI extern int SOCK_RawOpen(ITS_SocketInfo **info,
                                  ITS_SOCK_DOMAIN domain,
                                  const char *host_or_path,
                                  int port, int pf,
                                  ITS_BOOLEAN autoHeaders);
/*
 * close either a server or a client socket
 */
ITSDLLAPI extern void SOCK_Close(ITS_SocketInfo* sock);

/*
 * accept a connection on a server socket
 */
ITSDLLAPI extern int SOCK_ServerAccept(ITS_SocketInfo* sock,
                                       ITS_SocketInfo** newInfo);

/*
 * connect to a server from a client
 */
ITSDLLAPI extern int SOCK_ClientConnect(ITS_SocketInfo* sock);

/*
 * poll sockets
 */
ITSDLLAPI extern int SOCK_Poll(ITS_SockPollInfo* socks, int nsocks,
                               int usecs);

/*
 * read data from a socket
 */
ITSDLLAPI extern int SOCK_Read(ITS_SocketInfo* sock,
                               char *buf, int nbytes);

/*
 * write data to a socket
 */
ITSDLLAPI extern int SOCK_Write(ITS_SocketInfo* sock,
                                char *buf, int nbytes);

/*
 * recv data from a socket
 */
ITSDLLAPI extern int SOCK_Recv(ITS_SocketInfo* sock,
                               char *buf, int nbytes,
                               void* from, int* len);

/*
 * send data to a socket
 */
ITSDLLAPI extern int SOCK_Send(ITS_SocketInfo* sock,
                               char *buf, int nbytes,
                               void* to, int len);

/*
 * non-blocking versions of the above
 */
ITSDLLAPI extern int SOCK_NonBlockingRead(ITS_SocketInfo* sock,
                                          char *buf, int len, int);

ITSDLLAPI extern int SOCK_NonBlockingWrite(ITS_SocketInfo* sock,
                                           char *buf, int len, int);

/*
 * print some debugging information from a socket
 */
ITSDLLAPI extern void SOCK_DebugDump(ITS_SocketInfo* sock);

ITSDLLAPI extern ITS_BOOLEAN  SOCK_AddrsAreEqual(ITS_SocketInfo* a1,
                                                 ITS_SocketInfo* a2);
ITSDLLAPI extern int  SOCK_CreateAddr(ITS_SOCK_DOMAIN domain,
                                      const char *host_or_path,
                                      int port, void **addr, int *len);

ITSDLLAPI extern int  SOCK_GetPeerName(ITS_SocketInfo *in,
                                       ITS_SocketInfo *out);

ITSDLLAPI extern int  SOCK_GetLocalAddrs(SOCK_AddrStore **addrs,
                                         SOCK_AddrStore **masks,
                                         SOCK_AddrStore **bcasts);

ITSDLLAPI extern int  SOCK_GetIPv4AddrAndPort(SOCK_AddrStore *addrStruct,
                                              SOCK_IPv4Addr *addr,
                                              ITS_USHORT *port);
ITSDLLAPI extern int  SOCK_IPv4NameToAddr(const char *name, SOCK_IPv4Addr *addr);
ITSDLLAPI extern int  SOCK_IPv4AddrToName(char *name, SOCK_IPv4Addr addr);

/*
 * expose these in our namespace.  Not so efficient, but
 * we don't use them that much, and nobody puts the protos
 * in the same location.
 */
ITSDLLAPI ITS_ULONG   SOCK_NToHL(ITS_ULONG val);
ITSDLLAPI ITS_USHORT  SOCK_NToHS(ITS_USHORT val);
ITSDLLAPI ITS_ULONG   SOCK_HToNL(ITS_ULONG val);
ITSDLLAPI ITS_USHORT  SOCK_HToNS(ITS_USHORT val);

#define SOCKET_CLASS_NAME   "Sockets"

ITSDLLAPI extern ITS_ClassRec itsSOCKET_ClassRec;
ITSDLLAPI extern ITS_Class    itsSOCKET_Class;

#ifdef __cplusplus
}
#endif

#if defined(USE_CPLUSPLUS)

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:Socket
 *****************************************************************************
 *  Interface:
 *      Socket
 *
 *  Purpose:
 *      The Socket class implements socket connections, Berkeley style.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
class Socket
{
public:
    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method creates a new  socket.  The only addition from
     *      Socket is the creation of a guard mutex.
     *
     *  Notes:
     *      This method can throw exceptions if the mutex cannot be created.
     *
     ************************************************************************/
    Socket()
    {
        info = NULL;
    }
    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Destroy a  socket.
     *
     ************************************************************************/
    virtual ~Socket()
    {
        if (info != NULL)
        {
            SOCK_Close(info);
        }
    }
    
    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Determine if there is data pending on a socket connection.
     *
     *  Return Value:
     *      If the return value is less than zero, an error occured.
     *      If the return value is zero, no data is pending.
     *      A positive return value indicates the number of bytes waiting to be
     *          read.
     *
     ************************************************************************/
    virtual int
    Pending()
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_Pending(info);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method checks to see if a socket is ready for reading.
     *
     *  Return Value:
     *      If the socket is ready, ITS_TRUE is returned.
     *      ITS_FALSE is returned for errors or not-ready for read.
     *
     ************************************************************************/
    virtual ITS_BOOLEAN
    ReadyToRead()
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_ReadyToRead(info);
    }
    
    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method reads data from a  socket.
     *
     *  Input Parameters:
     *      nbytes - the maximum number of bytes to read
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes read.
     *
     ************************************************************************/
    virtual int
    Read(char *buf, int nbytes)
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_Read(info, buf, nbytes);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method writes data to a  socket.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to send
     *      nbytes - the maximum number of bytes to write
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes written.
     *
     ************************************************************************/
    virtual int
    Write(char *buf, int nbytes)
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_Write(info, buf, nbytes);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method attempts to read data from a  socket without
     *      blocking on the socket.
     *
     *  Input Parameters:
     *      nbytes - the maximum number of bytes to read
     *      timeout - the number of seconds to wait for data before returning on
     *          error
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to fill
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes read.
     *
     ************************************************************************/
    virtual int
    NonBlockingRead(char *buf, int size, int timeout)
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_NonBlockingRead(info, buf, size, timeout);
    }
    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method writes data to a  socket.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to send
     *      nbytes - the maximum number of bytes to write
     *      timeout - the number of seconds to wait for writing before returning
     *          on error.
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes written.
     *
     ************************************************************************/
    virtual int
    NonBlockingWrite(char *buf, int size, int timeout)
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_NonBlockingWrite(info, buf, size, timeout);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method attempts to read a datagram from a socket
     *
     *  Input Parameters:
     *      nbytes - the maximum number of bytes to read
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to fill
     *      addr - buffer containing the datagram source address
     *      len - length of the source address
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes read.
     *
     ************************************************************************/
    virtual int
    Recv(char *buf, int nbytes, void *addr, int *len)
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_Recv(info, buf, nbytes, addr, len);
    }
    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      This method writes a datagram to a socket.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to send
     *      nbytes - the maximum number of bytes to write
     *      addr - the address to send to
     *      len - the length of the address
     *
     *  Return Value:
     *      If the return value is less than zero, an error occurred.
     *      Any other return value indicates the number of bytes written.
     *
     ************************************************************************/
    virtual int
    Send(char *buf, int nbytes, void *addr, int len)
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_Send(info, buf, nbytes, addr, len);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Dump socket info
     *
     ************************************************************************/
    void
    DebugDump()
    {
        ITS_THROW_ASSERT(info != NULL);

        SOCK_DebugDump(info);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Explicitly set the socket data
     *
     *  Input Parameters:
     *      tmp - socket info to set
     *
     ************************************************************************/
    void
    SetSocketInfo(ITS_SocketInfo *tmp)
    {
        info = tmp;
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Get the peername information of a socket
     *
     *  Output Parameters:
     *      peer - the peer information
     *
     ************************************************************************/
    int
    GetPeerName(ITS_SocketInfo *peer)
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_GetPeerName(info, peer);
    }

    /*.implementation:public,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Create an address based on the supplied parameters.
     *
     *  Input Parameters:
     *      domain - UNIX or INET
     *      host_or_path - hostname or unix filesystem name
     *      port - port number
     *
     *  Output Parameters:
     *      addr - address is stored in this pointer
     *      len - size of the address info
     *
     ************************************************************************/
    static int
    CreateAddr(ITS_SOCK_DOMAIN domain,
               const char *host_or_path, int port,
               void **addr, int *len)
    {
        return SOCK_CreateAddr(domain, host_or_path, port, addr, len);
    }

    /*
     * network and host ordering
     */
    /*.implementation:static,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Network to host long
     *
     ************************************************************************/
    static ITS_ULONG
    NToHL(ITS_ULONG val)
    {
        return SOCK_NToHL(val);
    }
    /*.implementation:static,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Network to host short
     *
     ************************************************************************/
    static ITS_USHORT
    NToHS(ITS_USHORT val)
    {
        return SOCK_NToHS(val);
    }
    /*.implementation:static,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Host to network long
     *
     ************************************************************************/
    static ITS_ULONG
    HToNL(ITS_ULONG val)
    {
        return SOCK_HToNL(val);
    }
    /*.implementation:static,inline,Socket
     ************************************************************************
     *  Purpose:
     *      Host to network short
     *
     ************************************************************************/
    static ITS_USHORT
    HToNS(ITS_USHORT val)
    {
        return SOCK_HToNS(val);
    }

protected:
    ITS_SocketInfo* info;

private:
    /* sorry folks, no copying these */
    Socket(Socket&) {}
    Socket& operator=(Socket&) { return *this; }
};

/*.interface:ClientSocket
 *****************************************************************************
 *  Interface:
 *      ClientSocket
 *
 *  Purpose:
 *      Client sockets represent the connecting side of a TCP/IP transport
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/*
 * client side
 */
class ClientSocket : public Socket
{
public:
    /*.implementation:public,inline,ClientSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a  client socket
     *
     *  Input Parameters:
     *      domain - either INET or UNIX address families.
     *      host_or_path - the hostname of the server, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the server
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    ClientSocket(ITS_SOCK_DOMAIN domain,
                 const char *host_or_path, int port)
        : Socket()
    {
        if (SOCK_ClientOpen(&info, domain, host_or_path, port) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,ClientSocket
     ************************************************************************
     *  Purpose:
     *      This method destroyes  client sockets.
     *
     ************************************************************************/
    virtual ~ClientSocket()
    {
    }

    /*.implementation:public,inline,ClientSocket
     ************************************************************************
     *  Purpose:
     *      This method attempts to connect the  client socket to the
     *      server.
     *
     *  Return Value:
     *      If the return value is less than zero, an error is returned.
     *      Otherwise, zero indicates success.
     *
     ************************************************************************/
    int
    Connect()
    {
        ITS_THROW_ASSERT(info != NULL);

        return SOCK_ClientConnect(info);
    }

private:
    /* sorry folks, no copying these */
    ClientSocket() {}
    ClientSocket(ClientSocket&) {}
    ClientSocket& operator=(ClientSocket&) { return *this; }
};

/*.interface:ServerSocket
 *****************************************************************************
 *  Interface:
 *      ServerSocket
 *
 *  Purpose:
 *      Server sockets represent the accepting side of a TCP/IP transport.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/*
 * server side
 */
class ServerSocket : public Socket
{
public:
    /*.implementation:public,inline,ServerSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a  server socket.
     *
     *  Input Parameters:
     *      domain - either INET or UNIX address families.
     *      host_or_path - the hostname of the server, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the server
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    ServerSocket(ITS_SOCK_DOMAIN domain,
                 const char *host_or_path, int port)
        : Socket()
    {
        if (SOCK_ServerOpen(&info, domain, host_or_path, port) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,ServerSocket
     ************************************************************************
     *  Purpose:
     *      This method destroys a  server socket.
     *
     ************************************************************************/
    virtual ~ServerSocket()
    {
    }

    /*.implementation:public,inline,ServerSocket
     ************************************************************************
     *  Purpose:
     *      This method accepts a connection on a  server socket.
     *
     *  Output Parameters:
     *      clone - an ITS_GatedSocket containing the new connection
     *
     *  Return Value:
     *      If a new client is successfully accepted, ITS_SUCCESS is returned.
     *      Any other value indicates an IntelliSS7 processing error.
     *
     ************************************************************************/
    int
    Accept(Socket** clone)
    {
        int ret;
        ITS_SocketInfo *tmp = NULL;

        ret = SOCK_ServerAccept(info, &tmp);

        *clone = NULL;

        if (ret == ITS_SUCCESS)
        {
            *clone = new Socket;

            (*clone)->SetSocketInfo(tmp);
        }

        return ret;
    }

private:
    /* sorry folks, no copying these */
    ServerSocket() {}
    ServerSocket(ServerSocket&) {}
    ServerSocket& operator=(ServerSocket&) { return *this; }
};

/*.interface:EndPointSocket
 *****************************************************************************
 *  Interface:
 *      EndPointSocket
 *
 *  Purpose:
 *      EndPoint sockets represent either side of a UDP/IP transport.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/*
 * server side
 */
class EndPointSocket : public Socket
{
public:
    /*.implementation:public,inline,EndPointSocket
     ************************************************************************
     *  Purpose:
     *      This method creates an endpoint socket.
     *
     *  Input Parameters:
     *      host_or_path - the hostname of the endpoint, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the endpoint
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    EndPointSocket(ITS_SOCK_DOMAIN domain,
                   const char *host_or_path, int port)
    {
        if (SOCK_EndPointOpen(&info, domain,
                              host_or_path, port) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,EndPointSocket
     ************************************************************************
     *  Purpose:
     *      This method destroys an endpoint socket.
     *
     ************************************************************************/
    virtual ~EndPointSocket()
    {
    }

private:
    /* sorry folks, no copying these */
    EndPointSocket() {}
    EndPointSocket(EndPointSocket&) {}
    EndPointSocket& operator=(EndPointSocket&) { return *this; }
};

/*.interface:RawSocket
 *****************************************************************************
 *  Interface:
 *      RawSocket
 *
 *  Purpose:
 *      Raw sockets represent a raw IP socket.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
/*
 * server side
 */
class RawSocket : public Socket
{
public:
    /*.implementation:public,inline,RawSocket
     ************************************************************************
     *  Purpose:
     *      This method creates a raw socket.
     *
     *  Input Parameters:
     *      host_or_path - the hostname of the endpoint, or the pathname to the
     *          UNIX domain socket
     *      port - the port number to connect to on the endpoint
     *
     *  Notes:
     *      This method can throw exceptions if the socket cannot be opened.
     *
     ************************************************************************/
    RawSocket(ITS_SOCK_DOMAIN domain,
              const char *host_or_path, int port, int pf,
              bool autoHeaders)
    {
        if (SOCK_RawOpen(&info, domain, host_or_path, port, pf,
                         autoHeaders ? ITS_TRUE : ITS_FALSE) != ITS_SUCCESS)
        {
            throw Error(ITS_EBADSOCKET, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,RawSocket
     ************************************************************************
     *  Purpose:
     *      This method destroys a raw socket.
     *
     ************************************************************************/
    virtual ~RawSocket()
    {
    }

private:
    /* sorry folks, no copying these */
    RawSocket() {}
    RawSocket(RawSocket&) {}
    RawSocket& operator=(RawSocket&) { return *this; }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_SOCKETS_H */
