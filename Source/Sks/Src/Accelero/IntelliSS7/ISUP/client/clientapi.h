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
 * $Id: clientapi.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:23:46  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:13:05  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * Begin PR6.5
 *
 * Revision 1.2  2005/03/23 07:26:06  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 1.1.2.5.6.1.10.1  2004/12/15 06:01:40  mmanikandan
 * Windows Build Support.
 *
 * Revision 1.1.2.5.6.1  2004/01/05 09:48:02  sjaddu
 * Merged code from tcs isup branch.
 *
 * Revision 1.1.2.5.2.5  2003/12/19 04:45:11  akumar
 * Added flexibility to modifiy the client connection attempts with the server.
 *
 * Revision 1.1.2.5.2.4  2003/10/31 05:57:45  sjaddu
 * Final commit.
 *
 * Revision 1.1.2.5.2.3  2003/10/29 12:32:06  akumar
 * CL_CloseConnection API added.
 *
 * Revision 1.1.2.5.2.2  2003/09/15 11:14:40  akumar
 * Misc Changes.
 *
 * Revision 1.1.2.5.2.1  2003/08/26 12:47:48  sjaddu
 * Redundancy changes done.
 *
 * Revision 1.1.2.5  2003/07/04 09:36:16  tsanthosh
 * Added SS7DDLAPI to all funtion signatures.
 *
 * Revision 1.1.2.4  2003/06/25 09:04:37  sjaddu
 *
 * Changed the opcode values for res events.
 *
 * Revision 1.1.2.3  2003/06/20 11:23:07  sjaddu
 * more #defines are added.
 *
 * Revision 1.1.2.2  2003/06/18 08:28:58  tsanthosh
 * Added Request & Response functinality.
 *
 * Revision 1.1.2.1  2003/06/05 05:21:45  sjaddu
 * Added first revision of files for ISUP client.
 *
 *
 ****************************************************************************/

#ifndef CLIENTAPI_H
#define CLIENTAPI_H

#include <its.h>
#include <its_types.h>
#include <its_sockets.h>

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#if defined(WIN32)
#if defined(CL_IMPLEMENTATION)
#define CLDLLAPI __declspec(dllexport)
#else
#define CLDLLAPI __declspec(dllimport)
#endif
#else
#define CLDLLAPI
#endif

extern CLDLLAPI ITS_HANDLE  __ISUP_Handle;

/*
 * clientapi.h
 * This file contains the application APIs 
 */

#define CL_ISUP_RESERVE_CIC_RESP    0xF1 
#define CL_ISUP_REGISTER_RESP       0xF2 
#define CL_ISUP_DEREGISTER_RESP     0xF3 
#define CL_ISUP_UNRESERVE_CIC_RESP  0xF4 

/*
 * Structure will hold the info of reserve cic api
 */
typedef struct _cl_isup_reserveCic_info
{
    MTP3_HEADER mtp3;
    ITS_USHORT  cic;
    ITS_OCTET   cic_state;
    ITS_CTXT    vcic;
    ITS_UINT    ret;
}
CL_ISUP_RESERVE_CIC_ENTRY;

/*
 * Structure will hold the info of unreserve cic api
 */
typedef struct _cl_isup_unreserveCic_info
{
    MTP3_HEADER mtp3;
    ITS_USHORT  cic;
    ITS_UINT     ret;
}
CL_ISUP_UNRESERVE_CIC_ENTRY;

/*
 * Structure will hold the reg - dereg info of client
 */
typedef struct _cl_isup_register_info
{
    MTP3_HEADER mtp3;
    ITS_UINT     ret;
}
CL_ISUP_REG_ENTRY;

typedef enum
{
    CL_PRIMARY_CONNECTION =0,
    CL_BACKUP_CONNECTION
}
CL_CONNECTION_TYPE;

/*
 * Pre initialization function
 */
CLDLLAPI int
CL_PreInitialize();

/*
 * initialization function
 */
CLDLLAPI int
CL_Initialize(const char *host, int port, CL_CONNECTION_TYPE type,
                                             int conServattempts);

/*
 * Do the clean up during Terminate 
 */
CLDLLAPI void
CL_Terminate();



/*
 * Close the connection, for the user
 */
CLDLLAPI int
CL_CloseConnection(CL_CONNECTION_TYPE type);

/*
 * Registration function
 */
CLDLLAPI int
CL_Register(ITS_HANDLE handle, MTP3_HEADER *hdr, int count);


/*
 * Deregister function
 */
CLDLLAPI int
CL_Deregister(ITS_HANDLE handle, MTP3_HEADER *hdr, int count);


/*
 * GetNextEvent function
 */
CLDLLAPI int
CL_GetNextEvent(ITS_HANDLE handle, ITS_EVENT *evt);


/*
 * This function is used to receive reserve cic indication
 */
CLDLLAPI int
ISUP_ReceiveReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                 CL_ISUP_RESERVE_CIC_ENTRY *reserveCic);

/*
 * This function is used to receive registration response indication
 */
CLDLLAPI int
ISUP_ReceiveRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                               CL_ISUP_REG_ENTRY *regInfo);

/*
 * This function is used to receive deregistration response indication
 */
CLDLLAPI int
ISUP_ReceiveDeRegisterIndication(ITS_HANDLE handle, ITS_EVENT *ev, 
                                 CL_ISUP_REG_ENTRY *regInfo);
/*
 * This function is used to receive Unreserver CIC response indication
 */
CLDLLAPI int
ISUP_ReceiveUnReserveCICIndication(ITS_HANDLE handle, ITS_EVENT *ev,
                                   CL_ISUP_UNRESERVE_CIC_ENTRY *entry); 
#endif
