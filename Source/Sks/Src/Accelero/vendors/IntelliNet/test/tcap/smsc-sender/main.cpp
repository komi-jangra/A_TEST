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
 * CONTRACT: SCCP Load Test Program                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: main.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:23  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/12/17 04:16:26  randresol
 * LOG: Add TCAP test program for TTC
 * LOG:
 * LOG: Revision 1.1.2.1  2004/02/06 19:27:05  randresol
 * LOG: SCCP-CO test program addition
 * LOG:
 * LOG: Revision 1.1.2.1  2003/12/02 01:30:02  randresol
 * LOG: Add Test sender for the API dynamic configuration
 * LOG:
 * LOG: Revision 1.1.2.1  2003/10/21 21:44:56  randresol
 * LOG: Add test file for redundant SCCP
 * LOG:
 * LOG: 
 *
 *****************************************************************************/
#include <stdio.h>
#include <iostream.h>
#include <its++.h>
#include <engine.h>
#include <its_dsm_gcs.h>
#include <its_dsm_stub.h>
#include <sccp++.h>
#include "dbc.h"

void
NPREQ_DbcServer::DoCommand(istream& commandLine)
{
    if (Cmd("addB", "Add Border", ""))
    {
        cout<<"Adding border "<< endl;

    }

}


int
main(int argc, const char **argv)
{
    int ret;
    int count = 0;

    ITS_AddFeature(itsDBC_ServerClass); 

    NPREQ_DbcServer sccpDbcServer("TEST MML Console");

    APPL_SetName("ansi-smsc");
/*
    ITS_AddFeature(itsDSM_GcsImplClass);

    ITS_AddFeature(itsDSM_StubImplClass);
*/
    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    printf("Application is terminating...\n");

    return ITS_SUCCESS;;
}


