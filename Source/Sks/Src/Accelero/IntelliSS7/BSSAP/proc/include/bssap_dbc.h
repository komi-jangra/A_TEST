/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: bssap_dbc.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/06 08:26:15  adutta
 * LOG: DBC declaratio
 * LOG:
 ****************************************************************************/
                                                                                                                             
#ifndef  _BSSAP_DBC_H_
#define  _BSSAP_DBC_H_

#include <dbc_serv.h>

void BSSAP_ConsoleCommand(DBC_Server* dbc, const ITS_CHAR* cmdLine);

/*****************************************************************************
 *
 * The BSSAP General Configuration.
 *
 *****************************************************************************/
typedef struct
{
    ITS_OCTET       alarmLevel;
    ITS_BOOLEAN     traceOn;     /* on(1), off(0) */
    ITS_CHAR        traceType[ITS_PATH_MAX];
    ITS_CHAR        traceOutput[ITS_PATH_MAX];
}
BSSAPGeneralCfg;
                                                                                                                                              
 /*
  * prototypes
  */
BSSAPGeneralCfg* BSSAP_GetGeneralCfg();
int              BSSAP_SetGeneralCfg(BSSAPGeneralCfg *data);


#endif
