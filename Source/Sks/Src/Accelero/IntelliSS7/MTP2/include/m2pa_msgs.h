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
 *                  
 * CONTRACT: INTERNAL
 *      
 * ID: $Id: m2pa_msgs.h,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:45  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:16  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:15  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.2  2002/01/03 23:24:55  mmiers
 * LOG: More work on M2PA
 * LOG:
 * LOG: Revision 1.1  2002/01/02 23:22:32  mmiers
 * LOG: Start M2PA
 * LOG:
 *                 
 ****************************************************************************/

#include <its.h>

#if !defined(_ITS_M2PA_MSGS_H_)
#define _ITS_M2PA_MSGS_H_

/*
 * common header
 */
typedef struct
{
    ITS_OCTET   version;
    ITS_OCTET   spare;
    ITS_OCTET   msgClass;
    ITS_OCTET   msgType;
    ITS_UINT    msgLength;
}
UA_HDR;

/*
 * version info
 */
#define M2PA_VERSION_1  1

/*
 * class info
 */
#define M2PA_MSG_CLASS  11

/*
 * message types.
 */
#define M2PA_MSG_USER_DATA      1
#define M2PA_MSG_LINK_STATUS    2
#define M2PA_MSG_PROVING_DATA   3

/*
 * messages for M2PA
 */
/*
 * user data
 */
typedef struct
{
    ITS_OCTET       li;         /* only used when national variant uses
                                 * 2 extra bits. */
    ITS_OCTET       data[1];    /* from SIO onwards */
}
M2PA_DATA_MSG;

/*
 * link status
 */
typedef struct
{
    ITS_UINT        status;
}
M2PA_LINK_STATUS_MSG;

/*
 * status types
 */
#define M2PA_LS_ALIGNMENT       1
#define M2PA_LS_PROVING_NORMAL  2
#define M2PA_LS_PROVING_EMERG   3
#define M2PA_LS_READY           4
#define M2PA_LS_PROCESSOR_OUT   5
#define M2PA_LS_PROCESSOR_REC   6
#define M2PA_LS_BUSY            7
#define M2PA_LS_BUSY_END        8

/*
 * proving data
 */
typedef struct
{
    ITS_OCTET   data[1];
}
M2PA_PROVING_MSG;

/*
 * max size of M2PA data
 */
#define M2PA_MAX_MSG_SIZE   300

/*
 * an M2PA message
 */
typedef struct
{
    UA_HDR                      hdr;
    union
    {
        M2PA_DATA_MSG           userData;
        M2PA_LINK_STATUS_MSG    linkStatus;
        M2PA_PROVING_MSG        provingData;
        ITS_OCTET               dummy[M2PA_MAX_MSG_SIZE];
    }
    body;
}
M2PA_MSG;

#endif /* _ITS_M2PA_MSGS_H_ */
