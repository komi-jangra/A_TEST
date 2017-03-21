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
 * ID:$Id: ISUP_Main.c,v 1.1.1.1 2007-10-08 11:12:20 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:24:56  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:27  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:14  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:05  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 8.4  2005/03/21 13:54:16  cvsadmin
 * LOG:PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG:Revision 1.3.2.2  2003/03/28 09:45:57  ssingh
 * LOG:Changes done to avoid STACK functionality usage.
 * LOG:
 * LOG:Revision 1.3.2.1  2003/02/25 09:04:45  ssingh
 * LOG:Add STUB/GCS feature is removed from Application.
 * LOG:One of these will be added in xml depending on need.
 * LOG:
 * LOG:Revision 1.3  2003/01/28 14:40:39  ssingh
 * LOG:Log cleanup.
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:37:59  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 ****************************************************************************/
#include <engine.h>
#include <assert.h>

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      The Application MAIN function
 *
 *  Input Parameters:
 *      argc - Argument Count to the Main func.
 *      argv - Argument String Name/Value.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int main(int argc, const char** argv)
{
    const ushort MAXPATH = 256;
    char path[MAXPATH];

    memset( path, 0, MAXPATH );
    assert( getcwd(path, MAXPATH) != NULL );
    strcat( path, "/" );

    printf("Path = %s\n", path);

    APPL_SetConfigDir(path);
    APPL_SetName("ftest");
    APPL_SetConfigFileExtension("xml");

    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}
