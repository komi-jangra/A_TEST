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
 *  ID: $Id: test12.c,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:32  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:14  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:24  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:24  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:06  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/18 22:11:57  mmiers
 * LOG: Try to reproduce bug noticed by customer
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
 * LOG: Revision 3.1  2000/08/16 00:06:14  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/04/25 16:46:41  mmiers
 * LOG:
 * LOG:
 * LOG: Update to current code base.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:28:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/08/27 02:25:44  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for DEC build
 * LOG:
 * LOG: Revision 1.3  1999/08/20 20:40:41  mmiers
 * LOG:
 * LOG:
 * LOG: Make sure I got this right.
 * LOG:
 * LOG: Revision 1.2  1999/08/20 20:09:59  mmiers
 * LOG:
 * LOG:
 * LOG: Resfile test.
 * LOG:
 * LOG: Revision 1.1  1999/08/20 00:10:39  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a free twice bug in the resource manager.
 * LOG:
 *
 ****************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if defined(unix)
#include <unistd.h>
#include <signal.h>
#endif

#include <its.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <its_dsm.h>

int
main(int argc, char **argv)
{
    char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];
    const char *section;

    RESFILE_Manager *res;

    APPL_SetConfigFileName("apu.cfg");

    RESFILE_SetAltCommentChar('!');

    ITS_AddFeature(itsDSM_StubImplClass);

    if (ITS_GlobalStart(0) != ITS_SUCCESS)
    {
        exit(0);
    }

    if ((res = RESFILE_CreateResourceManager((char *)APPL_GetConfigFileName())) == NULL)
    {
        exit(0);
    }

    RESFILE_Lock(res);

    RESFILE_Rewind(res, NULL);

    printf("GLOBALS SECTION:\n");
    while (RESFILE_GetKeyName(res, NULL, key, ITS_PATH_MAX) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, NULL, val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        printf("  KEY: '%s' VALUE: '%s'\n", key, val);
    }

    section = NULL;
    while ((section = RESFILE_GetNextSectionName(res, section)) != NULL)
    {
        RESFILE_Rewind(res, section);

        printf("SECTION '%s':\n", section);

        while (RESFILE_GetKeyName(res, section, key, ITS_PATH_MAX) == ITS_SUCCESS &&
               RESFILE_GetKeyValue(res, section, val, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            printf("  KEY: '%s' VALUE: '%s'\n", key, val);
        }
    }

    RESFILE_Unlock(res);

    RESFILE_AddSection(res, "Section 1");
    RESFILE_AddSection(res, "Section 2");
    RESFILE_RemSection(res, "Section 2");
    RESFILE_RemSection(res, "Section 1");
    RESFILE_AddSection(res, "Section 1");

    ITS_GlobalStop();

    return (0);
}
