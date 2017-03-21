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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:36  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:16  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:30  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:58  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:08  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/04/16 21:48:16  hdivoux
 * LOG: Update for FT/HA integration.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:18  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.2  2001/04/03 01:11:57  mmiers
 * LOG:
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.1  2001/03/30 23:38:00  mmiers
 * LOG: More engine debugging.
 * LOG:
 * LOG: Revision 1.2  2001/03/29 03:07:34  mmiers
 * LOG: Start debugging.
 * LOG:
 * LOG: Revision 1.1  2001/03/26 23:02:15  mmiers
 * LOG: Today's installment.  Now that I'm caught up on email, I should
 * LOG: be able to finish the parser tomorrow.
 * LOG:
 *
 ****************************************************************************/

#include <its++.h>

#ident "$Id: test.cpp,v 1.1.1.1 2007-10-08 11:12:03 bsccs2 Exp $"

#include <stdio.h>
#include <stdlib.h>

#include <engine.h>

#include <iostream>

#include <its_dsm_stub.h>
#include <its_dsm_gcs.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

class foo
{
public:
    foo() {}

    virtual void Execute() = 0;
};

/*
 * test the driver.
 */
int
main(int argc, const char **argv)
{
    cout << "Starting" << endl;

    ITS_AddFeature(itsDSM_StubImplClass);

    ITS_AddFeature(itsDSM_GcsImplClass);

    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    return (0);
}


