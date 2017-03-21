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
 *  ID: $Id: test25.c,v 1.1.1.1 2007-10-08 11:12:00 bsccs2 Exp $
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
 * LOG: Revision 5.1  2001/08/16 20:46:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.2  2000/10/15 18:50:39  mmiers
 * LOG: Test program done.  Now debugging is all that's left.
 * LOG:
 *
 ****************************************************************************/

#include <its_app.h>
#include <its_ss7_stubs.h>
#include <its_ip_trans.h>
#include <its_kasock_trans.h>
#include <its_imal_trans.h>
#include <its_timers.h>

int
main(int argc, char **argv)
{
    SOCKTRAN_Manager *endPoint;
    ITS_EVENT event;

    APPL_SetName("Test25");

    ITS_AddFeature(itsKEEPALIVE_Class);

    ITS_AddFeature(itsIMAL_Class);

    ITS_GlobalStart(0);

    for (;;)
    {
        while((endPoint = ITS_Initialize(ITS_TRANSPORT_IMAL_SOCKET|
                                             ITS_TRANSPORT_CSOCKET|
                                             ITS_TRANSPORT_SINGLE_USER,
                                         1)) == NULL)
        {
            TIMERS_Sleep(1);
        }

        printf("Init done\n");

        while (ITS_GetNextEvent(endPoint, &event) == ITS_SUCCESS)
        {
            printf("Event fetched\n");
        }

        ITS_Terminate(endPoint);
    }

    ITS_GlobalStop();

    ITS_RemFeature(itsIMAL_Class);

    ITS_RemFeature(itsKEEPALIVE_Class);

    return (0);
}
