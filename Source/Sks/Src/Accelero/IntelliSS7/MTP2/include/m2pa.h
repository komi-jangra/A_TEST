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
 * ID: $Id: m2pa.h,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:50:15  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.4  2002/01/09 21:21:58  mmiers
 * LOG: Update for M2PA.  It (and SAAL) require larger BSNT fields
 * LOG: (16 and 24 bits, respectively).  Update SNMM to reflect this,
 * LOG: additional updates to SUPPORT for M2PA.
 * LOG:
 * LOG: Revision 1.3  2002/01/03 23:24:55  mmiers
 * LOG: More work on M2PA
 * LOG:
 * LOG: Revision 1.2  2002/01/02 23:46:08  mmiers
 * LOG: Add SM triggers
 * LOG:
 * LOG: Revision 1.1  2002/01/02 23:22:32  mmiers
 * LOG: Start M2PA
 * LOG:
 *                 
 ****************************************************************************/

#include <its.h>
#include <its_sctp_trans.h>

#if !defined(_ITS_M2PA_H_)
#define _ITS_M2PA_H_

/*
 * states
 */
typedef enum
{
    M2PA_STATE_IDLE,
    M2PA_STATE_OOS,
    M2PA_STATE_AIP,
    M2PA_STATE_PROVING,
    M2PA_STATE_ALIGNED_READY,
    M2PA_STATE_INS,
    M2PA_STATE_RETRIEVAL
}
M2PA_State;

/*
 * triggers
 */
typedef enum
{
    M2PA_TRIGGER_LINK_START,
    M2PA_TRIGGER_LINK_STOP,
    M2PA_TRIGGER_COMM_UP,
    M2PA_TRIGGER_COMM_DOWN,
    M2PA_TRIGGER_COMM_RESTART,
    M2PA_TRIGGER_COMM_ERROR,
    M2PA_TRIGGER_ALIGNMENT,
    M2PA_TRIGGER_PROVING,
    M2PA_TRIGGER_PROVING_COMPLETE,
    M2PA_TRIGGER_USER_DATA,
    M2PA_TRIGGER_RETRIEVAL_COMPLETE,
    M2PA_TRIGGER_T1_EXPIRY,
    M2PA_TRIGGER_T2_EXPIRY,
    M2PA_TRIGGER_T3_EXPIRY,
    M2PA_TRIGGER_T6_EXPIRY,
    /* internal triggers */
    M2PA_TRIGGER_PROVING_DATA_NEEDED,
    M2PA_TRIGGER_SEND_STATUS
}
M2PA_Trigger;

/*
 * timer context
 */
typedef struct
{
    M2PA_Trigger    trigger;
    ITS_USHORT      transport;
}
M2PA_TimerContext;

#define M2PA_CLASS_NAME     "M2PA Class"

VSS7DLLAPI extern ITS_Class itsM2PA_Class;

#endif /* _ITS_M2PA_H_ */
