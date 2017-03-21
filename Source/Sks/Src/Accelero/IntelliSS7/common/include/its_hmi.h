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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:48  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:47  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.5  2001/05/09 22:21:31  mmiers
 * LOG: Updates after ADP brainstorming.
 * LOG:
 * LOG: Revision 4.4  2001/05/02 19:06:01  mmiers
 * LOG: OK, HMI timer updating is in on all transports but FIFO
 * LOG: (which I'm going to skip).
 * LOG:
 * LOG: Revision 4.3  2001/05/02 00:01:50  mmiers
 * LOG: Finish alarm implementation.  HMI just needs the monitor
 * LOG: algorithm.
 * LOG:
 * LOG: Revision 4.2  2001/05/01 23:09:03  mmiers
 * LOG: Add functionality for HMI and alarm.  The rest is pretty easy.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2001/05/01 00:40:03  mmiers
 * LOG: Prep for PR5.
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_HMI_H)
#define ITS_HMI_H

#include <its.h>
#include <its_transports.h>

#ident "$Id: its_hmi.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*.interface:HMI_
 *****************************************************************************
 *  Interface:
 *      HMI_*
 *
 *  Purpose:
 *      Monitor the health of threads in the system.
 *
 *  Usage:
 *      This subsystem doesn't really have a public interface (it's for
 *      internal use) but does allow user override as desired.
 *
 *****************************************************************************/

#define HMI_CLASS_NAME "Health Monitor Class"

ITSDLLAPI extern ITS_ClassRec itsHMI_ClassRec;
ITSDLLAPI extern ITS_Class    itsHMI_Class;

/*
 * default check interval
 */
#define HMI_CHECK_INTERVAL      15      /* seconds */
#define HMI_TIMEOUT_INTERVAL    5000    /* msecs */

/*
 * override
 */
#define HMI_INTERVAL_STRING "hmiCheckInterval"
#define HMI_TIMEOUT_STRING  "hmiTimeOutInterval"

/*
 * user interface
 */
ITSDLLAPI extern CALLBACK_Manager   *HMI_Callbacks;

/*
 * default handler (if no callback set)
 */
ITSDLLAPI void HMI_Reset(TRANSPORT_Control *);

/*
 * other transports need to know how often to wake up.
 */
ITSDLLAPI ITS_UINT HMI_GetTimeOutInterval();
enum VNL_HEALTH { HEALTH_NOT_OK=0,HEALTH_OK};
#if defined(__cplusplus)
}
#endif

#endif /* ITS_HMI_H */
