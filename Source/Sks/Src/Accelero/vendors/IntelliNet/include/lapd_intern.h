/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2005 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: 
 * LOG:
 ****************************************************************************/

#ident "$Id: lapd_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $"

#if !defined(_LAPD_INTERN_H_)
#define _LAPD_INTERN_H_

#if defined __KERNEL__ && linux
/*
 * The only purpose of this file is to trick any IntelliSS7 included headers
 * into thinking they're still in IntellISS7.  We need to do this, because
 * we don't clearly separate parts of IntelliSS7 into user/kernel.
 */
#include <linux/kernel.h>
#include <linux/errno.h>
#include <asm/string.h>

#include <tsi_elin.h>
#include <cputune.h>
#include <cpu.h>
#include <tslink3.h>
                                                                                            
#include <protofun.h>

/*
 * Note that this is LOCAL TO THIS PROJECT, NOT THE USUAL ONE
 */
#include <its.h>

#include "arrayq.h"

/*
 * To/from user.  Also used to control size of TB/RTB.  Do NOT make
 * less than 4.
 */
#define LAPD_SIGNAL_QUEUE_EXP   6

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 *  struct to store the commands and requests received from user space.
 */
struct put_rqst
{
   int    pid_t;
   char   msg_data[LBUFLEN];
   int    datalen;
   char   command[sizeof(struct l4_ce_l3_msg)];
};

/*
 * Queue entry format
 */
typedef struct
{
    arrayq_elem_t        elem;
    union
    {
        struct req_data_xfer l4_ce; /* for write ???? */
        struct put_rqst      ce_l4; /* used for read  */
    }
    data;
}
LAPD_QEntry;

typedef struct
{
    /*
     * Interface to user (well, really the OS).
     */
    arrayq_t     rq;
    LAPD_QEntry  rqData[1 << LAPD_SIGNAL_QUEUE_EXP];
}
LAPD_TRx;


#if defined(__cplusplus)
}
#endif

#endif

#endif /* _MTP2_INTERN_H_ */

