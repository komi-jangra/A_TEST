/*********************************-*-C++-*-**********************************
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
 * Revision 1.1.1.1  2007/03/08 15:15:19  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:55:16  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:54:28  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:10:39  mmiers
 * Begin PR6.2
 *
 * Revision 1.2  2002/05/20 15:58:50  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.1  2002/04/13 04:43:13  hbalimid
 * ISUP load test with NMS MTP3 baseline
 *
 *
 ****************************************************************************/

/* System Includes */

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>


/* IntelliSS7 includes */

#include <its.h>
#include <its_app.h>
#include <engine.h>


void
MTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    /* Do nothing */
}


int main(int argc, const char** argv)
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

    ENGINE_Run(argc, argv);

    return (0);

}
