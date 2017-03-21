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
 ****************************************************************************/

#include <clientapi.h>
#include <engine.h>
#include "dbc_server.h"
#include <signal.h>

/* Default registration with server */
#define DEF_LOCAL_POINT_CODE     0x10
#define DEF_REMOTE_POINT_CODE    0x15
#define DEF_SIO                  0x85 

/* Misc defines */
#define FOREVER                  1
#define OPC_DPC_SIO_COUNT        1

/* public variable */
static char* hostIpAddress1;
static char* hostIpAddress2;
static int serverPort1;
static int serverPort2;


/* signal handling function */
static void
SignalHandler(int sig)
{
    CL_Terminate();
    exit(0);
}
    
/* Forward declarations */
static void* Receive(void* args);

static void HandleAppEvent(ITS_EVENT *evt);
static int InitClient(int conServattempts);
static int globalargcnt = 0;


int main(int argc, const char** argv)
{
    ITS_THREAD info;
    MTP3_HEADER hdr;
    int ret =0;
    int conServattempts = 0;

    signal(SIGINT, SignalHandler);

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

    /* Bind the client app with server and register 
     * the list of opc,dpc,ni 
     */
    ret = InitClient(conServattempts);
    if (ret == ITS_SUCCESS)
    {   
        printf("Client Initialization success\n");
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
            printf("CL_Register: Successfully Registered the client \n");
        }
    } 
    else
    {
        return ret;
    }

    /* Dispatch a new thread to receive event from server */
    THREAD_CreateThread(&info, 0, Receive, NULL, ITS_TRUE);

    /* Set the application name */
    APPL_SetName("Client");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    /* Set the call back function for DBC */
    DBC_SetDoCommand(ExecuteCommand);
 
    ENGINE_Initialize(argc, argv, NULL, 0);

    return(ENGINE_Run(argc, argv));
}


/* Method binds the app with server on specified ipaddress and port
 * and also registers the list of OPC,DPC,Ni supported by app
 */
int InitClient(int conServattempts)
{
    int ret1 = !ITS_SUCCESS;
    int ret2 = !ITS_SUCCESS;

    /* Method binds client app with server on specified
     * ipaddress and port
     */

    ret1 = CL_Initialize(hostIpAddress1,
                              serverPort1,
                              CL_PRIMARY_CONNECTION, conServattempts);
    if (ret1 != ITS_SUCCESS)
    {
        printf("Client Connect to Primary Server failed\n");
        sleep(5);
    }
    else
    {
        fflush(stdout);
    }

    if (globalargcnt > 4)
    {
        ret2 = CL_Initialize(hostIpAddress2,
                                  serverPort2,
                                  CL_BACKUP_CONNECTION, conServattempts);
        if (ret2 != ITS_SUCCESS)
        {
            printf("Client Connect to Secondary Server failed\n");
            sleep(5);
        }
        else
        {
            fflush(stdout);
        }
    }

    if((ret1 != ITS_SUCCESS) && (ret2 != ITS_SUCCESS))
    {
       return !ITS_SUCCESS;
    }
    else
    {
       return ITS_SUCCESS;
    }
}

/* 
 * This Function runs as a separate thread to 
 * receive event from the Server and waits for 
 * establishing connection with server
 */
void* Receive(void* args)
{
    ITS_EVENT evt;
    ITS_INT ret=0;
    signal(SIGINT, SignalHandler);

    while(FOREVER)
    {
        /* Receive event from the server */
        ret = CL_GetNextEvent(__ISUP_Handle, &evt);
        if(ret != ITS_SUCCESS)
        {
            printf("Failed to get event from Que\n");
        }

        HandleAppEvent(&evt);

        /* Free the Event we no longer require it */
        ITS_EVENT_TERM(&evt);
        fflush(stdout);
    }
}

/* 
 * This function will Handle the application events
 * It decodes the events and prints the contents
 */
void HandleAppEvent(ITS_EVENT *evt)
{
    CL_ISUP_RESERVE_CIC_ENTRY reserveCic;
    CL_ISUP_UNRESERVE_CIC_ENTRY unreserveCic;
    CL_ISUP_REG_ENTRY  regInfo;
    int ret =0;

    switch (evt->data[0])
    {
    case CL_ISUP_RESERVE_CIC_RESP:
        ret = ISUP_ReceiveReserveCICIndication(__ISUP_Handle, evt, &reserveCic);

        printf("HandleAppEvent: Received ReserveCIC responsen\n");
        printf("VCIC = %d : CIC = %d cic_state = %d : ret = %d\n",
               reserveCic.vcic, reserveCic.cic,
               reserveCic.cic_state,reserveCic.ret);
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(reserveCic.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(reserveCic.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(reserveCic.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));


        break;

    case CL_ISUP_UNRESERVE_CIC_RESP:
        ret = ISUP_ReceiveUnReserveCICIndication(__ISUP_Handle, evt,
                                                     &unreserveCic);

        printf("HandleAppEvent: Received Un ReserveCIC response: \n");
        printf("CIC = %d : ret = %d\n",
                unreserveCic.cic, unreserveCic.ret);
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        break;

    case CL_ISUP_REGISTER_RESP:
        printf("HandleAppEvent: Received Register Response\n");

        ret = ISUP_ReceiveRegisterIndication(__ISUP_Handle, evt, &regInfo);
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        break;

    case CL_ISUP_DEREGISTER_RESP:
        printf("HandleAppEvent: Received DeRegister Response\n");

        ret = ISUP_ReceiveDeRegisterIndication(__ISUP_Handle, evt, &regInfo);
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC %d SIO %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.mtp3.label),
                MTP3_RL_GET_DPC_VALUE(regInfo.mtp3.label),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.mtp3) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));
        break;

    default:
        /* This will handle all other message including
         * ISUP msgs,
         * Information indications,
         * time out indiactions,
         * error indications .
         * See the defintion in printISUPMsg.c
         */
        printf("\n\n--- Received ISUP Event From Server --");
        ISUP_ReceiveMsg(__ISUP_Handle, evt);
        break;
    }
}

