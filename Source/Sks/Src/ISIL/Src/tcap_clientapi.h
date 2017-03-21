/****************************************************************************
 *                                                                          *
 *     Copyright 2003 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * $Id: tcap_clientapi.h
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:25:04  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * Initialising sources in CVS
 *
 * Revision 1.4  2003/11/11 06:00:42  ssingh
 * Signature of TCAP_AllocateLocalDID changed.
 *
 * Revision 1.3  2003/10/17 09:11:30  ssingh
 * compilation warning removal.
 *
 * Revision 1.2  2003/10/10 04:50:27  sswami
 * New function to allocate Local DID at test client side
 *
 * Revision 1.1  2003/10/07 12:24:09  sswami
 * Client API
 *
 *
 ****************************************************************************/

#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <its.h>
#include <its_types.h>
#include <its_sockets.h>

#if defined(CCITT)
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#endif


/*
 * clientapi.h
 * This file contains the application APIs 
 */


#define CL_TCAP_REGISTER_RESP          0xF1 
#define CL_TCAP_DEREGISTER_RESP        0xF2 

// Maximum number of dialogues for application initiated messages.
#define MAX_NUM_LID                    0x8000 

#define ROUTE_DPC_STRING "dpc"
#define ROUTE_SSN_STRING "ssn"
#define ROUTE_OPC_DPC_STRING "opc-dpc"
#define ROUTE_DPC_SIO_STRING "dpc-sio"
#define ROUTE_DPC_SSN_STRING "dpc-ssn"
#define ROUTE_OPC_DPC_SIO_STRING "opc-dpc-sio"
#define ROUTE_OPC_DPC_SSN_STRING "opc-dpc-ssn"
#define ROUTE_OPC_DPC_SIO_SSN_STRING "opc-dpc-sio-ssn"

typedef enum
{
    DPC,
    SSN,
    OPC_DPC,
    DPC_SIO,
    DPC_SSN,
    OPC_DPC_SIO,
    OPC_DPC_SSN,
    OPC_DPC_SIO_SSN
}ROUTE_STYLE;

typedef struct
{
    ITS_OCTET   route_style;
    MTP3_POINT_CODE     opc;
    MTP3_POINT_CODE     dpc;
    ITS_OCTET           sio;
    ITS_OCTET           ssn; 
}
CL_REG_INFO;

/* Structure will hold the reg - dereg info of client */
typedef struct _cl_tcap_register_info
{
    CL_REG_INFO reg_info;
    ITS_UINT      ret;

}
CL_TCAP_REG_ENTRY;

/* Initialization function */
SS7DLLAPI ITS_HANDLE
CL_Initialize(const char *host, int port);

/* Closes the connection */

SS7DLLAPI int
CL_CloseConnection(ITS_HANDLE handle);

/* Registration function */

SS7DLLAPI int
CL_Register(ITS_HANDLE handle, CL_REG_INFO *reg_info, int count);

/* Get the Routing Style */
int GetRouteStyle(char*);

/* This function allocates the local DID for Test Client application */
int TCAP_AllocateLocalDID(ITS_CTXT *did);

/* Deregister function */

SS7DLLAPI int
CL_Deregister(ITS_HANDLE handle, CL_REG_INFO *reg_info, int count);

/* GetNextEvent function */

SS7DLLAPI int
CL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt);



SS7DLLAPI int
CL_GetNextEvent_FromMtp3(ITS_HANDLE handle, ITS_EVENT *evt);

SS7DLLAPI int
CL_GetNextEvent_FromIsup(ITS_HANDLE handle, ITS_EVENT *evt);


SS7DLLAPI int
CL_GetNextEvent_FromSccp(ITS_HANDLE handle, ITS_EVENT *evt);

SS7DLLAPI int
CL_GetNextEvent_FromTcap(ITS_HANDLE handle, ITS_EVENT *evt);

/* This function is used to receive registration response indication */

SS7DLLAPI int
TCAP_ReceiveRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev,
                                  CL_TCAP_REG_ENTRY *regInfo);

/* This function is used to receive deregistration response indication */

SS7DLLAPI int
TCAP_ReceiveDeRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev,
                                 CL_TCAP_REG_ENTRY *regInfo);

//static int TCAP_AllocateLocalDID(ITS_HANDLE, int);

#endif
