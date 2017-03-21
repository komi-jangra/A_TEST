/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: main.c,v 1.1.1.1 2007-10-08 11:12:23 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:24:59  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:15:18  cvsadmin
 * BSC project
 *
 * Revision 9.2  2005/04/05 11:58:35  sjaddu
 * Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * Code changes for ISSUE ID 289.
 *
 * Revision 9.1  2005/03/23 12:55:16  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:54:28  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1.4.1  2003/05/09 04:59:48  ssingh
 * AddFeature is now would be through xml.
 *
 * Revision 7.1  2002/08/26 22:10:39  mmiers
 * Begin PR6.2
 *
 * Revision 1.3  2002/08/07 21:51:49  hbalimid
 * updated to work with new infrastructure.
 *
 * Revision 1.2  2002/05/20 15:58:50  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.3  2002/05/09 18:40:21  labuser
 * Merge from ISUP_APR_19_2002 to PR6.
 *
 * Revision 1.1.2.2.2.1  2002/05/09 14:52:50  labuser
 * Change return from main (use return value from ENGINE_Run()).
 *
 * Revision 1.1.2.2  2002/04/15 00:54:50  hbalimid
 * ISUP Load test - Base Version Done.
 *
 *
 ****************************************************************************/

/*
 * System Includes
 */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>

#include <engine.h>
#include <its_iniparse.h>
#include <dbc_serv.h>
#include <itu/mtp3.h>
#include <ss7_mgmt.h>

#include <isup_intern.h>
#include <mtp3_intern.h>

#if defined(CCITT)
#define ISS7_Stack ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack ISS7_ANSI_Stack
#endif


/*
 * IntelliSS7 Includes
 */

#include <its.h>
#include <its_app.h>
#include <engine.h>



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      MTP3 Management CallBacks
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
MTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    /* Do nothing */
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      main program
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
main(int argc, const char** argv)
{
    const ushort MAXPATH = 256;
    char path[MAXPATH];

    memset( path, 0, MAXPATH );
    assert( getcwd(path, MAXPATH) != NULL );
    strcat( path, "/" );

    printf("Path = %s\n", path);

    APPL_SetConfigDir(path);
    APPL_SetName("load");
    APPL_SetConfigFileExtension("xml");

    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}
