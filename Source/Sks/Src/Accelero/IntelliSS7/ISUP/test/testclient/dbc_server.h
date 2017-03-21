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
#ifndef DBC_SERVER_H
#define DBC_SERVER_H

#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>

#include <its_ss7_trans.h>
#include <dbc_serv.h>
#include <itu/mtp3.h>
#include <ss7_mgmt.h>

#include "readISUPMsg.h"
#include "sendISUPMsg.h"
#include "printISUPMsg.h"


#if defined (CCITT)
typedef struct _opcdpcinfo
{
    ITS_USHORT opc;
    ITS_USHORT dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#elif defined (ANSI)
typedef struct _opcdpcinfo
{
    ITS_UINT   opc;
    ITS_UINT   dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#else "Protocol Not Defined"
#endif

static OpcDpcInfo info;

static char dmpFile[256];

#if defined (CCITT)
static const char* section = "ITU-ISUP";
#elif defined (ANSI)
static const char* section = "ANSI-ISUP";
#else
#error "Protocol Not Defined"
#endif

void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);
void ISUPMgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData);
int GetOpcDpcInfo(OpcDpcInfo*);
extern int ValidateCicRange(const char* cmdLine, ITS_USHORT* startcic, ITS_USHORT* endcic);
extern int PrintCicRangeInfo(ITS_USHORT opc, ITS_USHORT dpc, ITS_USHORT sio,
                             ITS_USHORT startcic, ITS_USHORT endcic);

#endif
