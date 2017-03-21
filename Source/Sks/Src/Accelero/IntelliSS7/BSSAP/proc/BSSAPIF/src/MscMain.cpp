/*********************************-*-CPP-*-**********************************
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: MscMain.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: MscMain.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $"

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>


#include <engine++.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif


static void Usage(const char** args)
{
    cout << " Usage: " << args[0] << endl;
    cout << " ConfigFileName <configFile> " << endl;
    cout << endl;
    exit (0);
}


int
ParseArguments(int argc, const char** args)
{
    int i = 1;
    int flag = 1;
    int ret = 0;

    if (argc == 1)
    {
        Usage (args);
        return -1; 
    }

    for(; i < argc && flag; i++)
    {
        if(strcmp(args[i], "-configFile") == 0)
        {
           flag = 0;
        }
        else
        {
           Usage(args);
        }
    }

    /* from here onwards are engine arguments. */
    return (i - 2);
}


int
main(int argc, const char **args)
{
    int ret;

    ret = ParseArguments(argc, args);

    ENGINE_Initialize((argc - ret), &args[ret], NULL, 0);

    ret = ENGINE_Run(argc, args);

    return ret;
}
