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
 *  ID: $Id: ss7_behaviors.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:00  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:53:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/05/15 15:05:54  randresol
 * LOG: Integrate shared behaviors and timers with management interface
 * LOG:
 * LOG: Revision 6.3  2002/03/14 23:08:26  mmiers
 * LOG: TCAP behaviors.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 22:52:31  mmiers
 * LOG: Convert TCAP and SCCP to OAM
 * LOG:
 * LOG: Revision 6.1  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 *
 ****************************************************************************/

#if !defined(_SS7_BEHAVIORS_H_)
#define _SS7_BEHAVIORS_H_

#include <its_behaviors.h>

/*
 * TCAP
 */
#define TCAP_B_use_reserved_NI  0

#define TCAP_NUM_BEHAVIORS      1

extern BEHAVIOR_Manager CCITT_TCAP_Behaviors;
extern BEHAVIOR_Manager ANSI_TCAP_Behaviors;

/*
 * SCCP
 */
#define SCCP_B_propagate_IT     0
#define SCCP_B_propagate_ERR    1
#define SCCP_B_propagate_SCMG   2
#define SCCP_B_use_SCMG         3

#define SCCP_NUM_BEHAVIORS      4

extern BEHAVIOR_Manager CCITT_SCCP_Behaviors;
extern BEHAVIOR_Manager ANSI_SCCP_Behaviors;

/*
 * ISUP
 */

/*
 * MTP3
 */
#define MTP3_B_stpFunction         0
#define MTP3_B_fullRestartNeeded   1
#define MTP3_B_spRestarting        2
#define MTP3_B_sendingStatus       3

#define MTP3_NUM_BEHAVIORS         4

extern BEHAVIOR_Manager CCITT_MTP3_Behaviors;
extern BEHAVIOR_Manager ANSI_MTP3_Behaviors;


#endif /* _SS7_BEHAVIORS_H_ */
