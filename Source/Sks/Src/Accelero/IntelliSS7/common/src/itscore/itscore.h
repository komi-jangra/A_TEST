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
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:11  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:17  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2002/12/17 20:45:11  mmiers
 * LOG: Add license version.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/13 16:59:39  mmiers
 * LOG: Fix warning, add key generation tools
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:07  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.2  2001/01/04 16:11:35  hdivoux
 * LOG: Warning removal, proper flags.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:07  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/07/27 19:59:17  mmiers
 * LOG:
 * LOG: Move things around so we can publish the license API.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITSCORE_H
#define ITSCORE_H

#ident "$Id: itscore.h,v 1.1.1.1 2007-10-08 11:11:55 bsccs2 Exp $"

#include <its_license.h>

/*
 * licensing stuff
 */
#define ITS_LICENSE_MAGIC   0xdeadbeef

#define ITS_LIC_STRING_LEN  32

#define ITS_LIC_REVISION    0x0700

typedef struct license_t
{
    ITS_UINT    cookie;
    ITS_TIME    expiry;
    ITS_TIME    duration;
    ITS_INT     max_voice_ports;
    ITS_USHORT  max_links;
    ITS_USHORT  revision;
#if defined(unix)
    ITS_UINT    serial_number;
#elif defined(WIN32)
    ITS_OCTET   serial_number[ITS_LIC_STRING_LEN];
#endif
    ITS_OCTET   capabilities[32];
}
ITS_License;

#define LICENSE_FILE    "its.lic"

#define DEFAULT_EXPIRE_TIME     (-1)
#define DEFAULT_DURATION        (-1)
#define DEFAULT_PORT_COUNT      (-1)
#define DEFAULT_LINK_COUNT      (0xFFFFU)

/*
 * licensing capabilities
 */
#define LICENSE_CAP_BYTE(x)     ((x)/ITS_BITS_PER_BYTE)
#define LICENSE_CAP_BIT(x)      ((x)%ITS_BITS_PER_BYTE)

#define LICENSE_HAS_CAPABILITY(x,y) \
    ((y).capabilities[LICENSE_CAP_BYTE(x)] & (1 << LICENSE_CAP_BIT(x)))
#define LICENSE_SET_CAPABILITY(x,y) \
    ((y).capabilities[LICENSE_CAP_BYTE(x)] |= (1 << LICENSE_CAP_BIT(x)))

#endif /* ITSCORE_H */

