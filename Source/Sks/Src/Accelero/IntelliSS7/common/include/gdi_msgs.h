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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:07  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/12 22:55:12  mmiers
 * LOG: Add the GDI ASN libraries.  We finally have a customer that
 * LOG: wants them.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:08  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.2  2000/05/24 18:55:48  mmiers
 * LOG:
 * LOG:
 * LOG: Warning removal ("incomplete last line")
 * LOG:
 * LOG: Revision 1.1  2000/05/16 00:17:41  mmiers
 * LOG:
 * LOG:
 * LOG: Clean up GDI a bit.
 * LOG:
 *
 ****************************************************************************/

#if !defined(GDI_MSGS_H)
#define GDI_MSGS_H

#ident "$Id: gdi_msgs.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

/*
 * Maximum size of a GDI message
 */
#define GDI_MAX_MSG_SIZE    (4096 - (2 * sizeof(ITS_USHORT) + \
                                     2 * sizeof(ITS_OCTET)))

/*
 * GDI header structure
 */
typedef struct
{
    ITS_USHORT  messageType;
    ITS_USHORT  messageLength;
    ITS_OCTET   versionNumber;
    ITS_OCTET   applicationID;
}
ITS_GDI_HDR;

typedef struct
{
    ITS_GDI_HDR     header;
    union
    {
        ITS_USHORT  errorCode;
        ITS_USHORT  operationCode;
        ITS_OCTET   payload[GDI_MAX_MSG_SIZE];
    }
    contents;
}
ITS_GDI_MSG;

/*
 * message types
 */
#define GDI_MSG_KEEP_ALIVE_REQ      0x0000U
#define GDI_MSG_KEEP_ALIVE_RESP     0x0001U
#define GDI_MSG_ERROR               0x0002U
#define GDI_MSG_DATA                0x0003U

/*
 * version numbers
 */
#define GDI_VERSION_4           0x01U
#define GDI_VERSION_5           0x02U

/*
 * application ID
 */
#define GDI_DEFAULT_APPLICATION 0x00U

/*
 * error codes
 */
#define GDI_ERR_GEN_FAILURE     0x0001U
#define GDI_ERR_TASK_REFUSED    0x0007U
#define GDI_ERR_QUEUE_FULL      0x0008U
#define GDI_ERR_TIMER_EXP       0x000AU
#define GDI_ERR_SYS_NOT_RESP    0x000FU
#define GDI_ERR_UNAUTH_REQ      0x0014U
#define GDI_ERR_INCOMPAT_VERS   0x003CU
#define GDI_ERR_RESULT_TOO_LONG 0x003DU

/*
 * operation family.  Note that for ITU TCAP (SR-5202)
 * the operation family _is_ included, but as two extra
 * octets in the operation code - octet[0] = 0, octet[1]
 * = GDI_OP_FAMILY, octet[2] = GDI_OP_XXXX.
 */
#define GDI_OP_FAMILY       0xE7

/*
 * operation codes.  Operation family
 * is always "miscellaneous".
 */
#define GDI_OP_GET_DATA     0x01U
#define GDI_OP_SEND_DATA    0x02U
#define GDI_OP_INVOKE_APP   0x04U

#endif /* GDI_MSGS_H */
