/***************************************************************************
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
 * CONTRACT: INTERNAL
 *                                                                          *
 * ID: $Id: TRACE_Main.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:56  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:14  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:05  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/08/10 07:52:04  ssingh
 * LOG: Initial commits for CTF Event Trace Client (base-code).
 * LOG:
 ****************************************************************************/
#include <engine.h>

extern ITS_USHORT thrInstance;

/* Debug console function */
void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);

int main(int argc, const char **argv)
{
    /* Set the application name */
    APPL_SetName("trace-event-client");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    DBC_SetDoCommand(ExecuteCommand);

    ENGINE_Initialize(argc, argv, NULL, 0);

    return(ENGINE_Run(argc, argv));
}

void ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    ITS_C_ASSERT(dbc != NULL);
}
