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
 * $Id: main.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
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


ITS_HANDLE hand;

#if defined(CCITT)
#define ISS7_Stack hand
#elif defined(ANSI)
#define ISS7_Stack hand
#endif
/*
 * IntelliSS7 Includes
 */

#include <its.h>
#include <its_app.h>
#include <engine.h>
#include <clientapi.h>

/* Default registration with server */
#define DEF_LOCAL_POINT_CODE     0x10
#define DEF_REMOTE_POINT_CODE    0x15
#define DEF_SIO                  0x85

/* Misc defines */
#define FOREVER                  1
#define OPC_DPC_SIO_COUNT        1
#define MAXPATH                256 


/* public variable */
static char* hostIpAddress1;
static char* hostIpAddress2;
static int serverPort1;
static int serverPort2;

static int globalargcnt = 0;



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

/* Method binds the app with server on specified ipaddress and port
 * and also registers the list of OPC,DPC,Ni supported by app
 */
int InitClient(conServattempts)
{

    MTP3_HEADER hdr;

    int ret = ITS_SUCCESS;

    /* Method binds client app with server on specified
     *  ipaddress and port as a primary, its a blocking call.
     */
    ret  = CL_Initialize(hostIpAddress1, serverPort1, CL_PRIMARY_CONNECTION,
                         conServattempts);
    if (ret != ITS_SUCCESS)
    {
        printf("Client Connect to Server failed\n");
        return ret;
    }

    if (globalargcnt > 3)
    {
        /* Method binds client app with server on specified
         *  ipaddress and port as a backup, its a blocking call.
         */
        ret = CL_Initialize(hostIpAddress2,
                            serverPort2,
                            CL_BACKUP_CONNECTION, conServattempts);
        if (ret != ITS_SUCCESS)
        {
            printf("Client Connect to Server failed\n");
            return ret;
        }
    }


   /* Compose MTP3 headers for def list of OPC,DPC,SIO
     * client will register with def MTP3 header.
     */
    memset(&hdr, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(hdr.label, DEF_LOCAL_POINT_CODE);
    MTP3_RL_SET_DPC_VALUE(hdr.label, DEF_REMOTE_POINT_CODE);
    hdr.sio = DEF_SIO;

    /* Register with the server */
    ret = CL_Register(__ISUP_Handle, &hdr, OPC_DPC_SIO_COUNT);
    if (ret  == ITS_SUCCESS)
    {
        printf("CL_Register: Successfully Regitered the client \n");
    }

    return ret;

}/*End of InitClient */


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
    char path[MAXPATH];
    int ret =0;
    int conServattempts = 0;

    if(argc == 6 || argc == 4)
    {
        globalargcnt = argc;
    }
    else
    {
        printf("Usage : ./test <primaryIP> <primaryport> <conServattempts> [<backupIP> <backupport>] \n");
        return(-1);
    }

    CL_PreInitialize();

    printf("\n\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****  IntelliSS7 ISUP Client Test     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n\n\n");

    hostIpAddress1 = (char*)argv[1];
    serverPort1    = atoi(argv[2]);
    conServattempts = atoi(argv[3]);
    hostIpAddress2 = (char*)argv[4];
    serverPort2    = atoi(argv[5]);

    memset( path, 0, MAXPATH );
    assert( getcwd(path, MAXPATH) != NULL );
    strcat( path, "/" );

    printf("Path = %s\n", path);

    APPL_SetConfigDir(path);
    APPL_SetName("load");
    APPL_SetConfigFileExtension("xml");

    ret = InitClient(conServattempts);
    if (ret != ITS_SUCCESS) return ret;

    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}
