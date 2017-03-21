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
 *
 *  ID: $Id: AppUtils.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:42  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:58  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/28 05:57:02  adutta
 * LOG: Remodeled for MSC
 * LOG:
 * LOG: Revision 1.2  2005/02/11 10:21:10  csireesh
 * LOG: Committing after sanitizing Sample App (send-recv) for SCCP-CO: yet to take care of Codec
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#include <iostream>
#include <stdlib.h>

#include <its++.h>
#include <engine++.h>

#include <App.h>
#include <AppTrace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#define NO_CMDLINE_ARGS  0
#define CONFIG_APP       1

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Displays the usage. 
 *
 *  Input Parameters:
 *      const char** args 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

static void Usage(const char** args)
{
    cout << " Usage: " << args[0] << endl;
    cout << " ConfigFileName <configFile> " << endl;
    cout << endl;
    exit (0);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will get a string of octets from strtok and save the
 *      octets in an ITS_OCTET array.
 *
 *  Input Parameters:
 *      nOctets - number of octets to get from strtok
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      array - pointer to an ITS_OCTET array to store octets read from strtok
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if
 *      Any other return code indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
GetOctetsFromStr(ITS_OCTET *array, int nOctets)
{
    int i;

    /* TODO: error check rtrieval of tokens */
    for (i = 0; i < nOctets; ++i)
    {
        array[i] = (ITS_OCTET) strtol(strtok(NULL, " \t"), NULL, BASE_16);
    }
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Parse the given arguments. 
 *
 *  Input Parameters:
 *      int argc, const char** args 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
ParseArguments(int argc, const char** args)
{
    int i = 1;
    int flag = 1;
    int ret = 0;

    if (argc == 1)
    {
        Usage (args);
        return NO_CMDLINE_ARGS;
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

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Prints the SCCP data passed as an argument.
 *
 *  Input Parameters:
 *    SCCP data and the length of the data 
 *
 *  Input/Output Parameters:
 *      .
 *
 *  Output Parameters:
 *      Prints the data.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

void
PrintData(ITS_OCTET *data, int len)
{
    if (data != NULL)
    {
        int i;

        cout << "UserData:" << endl;

        if(len > 0)
        {
            for (i = 0; i < len; i++)
            {
                printf("%02x ", *(data+i));
                if (!((i+1) % 20))
                {
 	            printf("\n");
                }
            }
            if ((i+1) % 20)
            {
 	        printf("\n");
            }
        }
        else
        {
            printf("Length = 0 \n");
        }
    }
    else
    {
        printf("No UserData \n");
    }
}

