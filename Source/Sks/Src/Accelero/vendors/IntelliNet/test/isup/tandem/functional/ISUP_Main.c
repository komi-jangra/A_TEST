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
 * ID:$Id: ISUP_Main.c,v 1.1.1.1 2007-10-08 11:12:23 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:19  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:17  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 1.1  2003/02/19 15:35:50  vnitin
 * LOG:Add functional tester for Tandem
 * LOG:
 * LOG:Revision 1.3  2003/01/28 14:40:39  ssingh
 * LOG:Log cleanup.
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:37:59  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 ****************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>

#include <its_iniparse.h>
#include <ansi/mtp3.h>
#include <ss7_mgmt.h>

#include <its_dsm_stub.h>
#include <its_app.h>
#include <isup_intern.h>

/* Forward declarations */
void WorkerDispatchFunction(ITS_HANDLE handle);

/* Global */
ITS_HANDLE Tandem_handle = 0;

#define ISS7_Stack Tandem_handle


int main(int argc, const char** argv)
{
    ITS_USHORT instance;
    ITS_UINT initMask;
    ITS_HANDLE handle;
    printf("\nBegin INTELLINET ISUP Test...\n");

    /* Application Instance number*/
    instance = 1;

    /*-------------------------------------------------------------------
     * Setting the name of the application. The application name is the
     * name of the ini file read by IntelliSS7.
     */
    printf("**** MAIN MAIN MAIN MAIN  *****");
    APPL_SetName("$NODEA.VNITIN.NSKINI");
    APPL_SetConfigFileExtension("");
    APPL_SetTraceDir("");
    printf("**** GOT Passed APP STUFF *****");

    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 subsystems initialization (including licensing).
     */

    ITS_AddFeature(itsDSM_StubImplClass);

#if defined(CCITT)
    ITS_AddFeature(itsSS7STACK_ClassCCITT);

    ITS_AddFeature(isupITU93_Class);

    ITS_AddFeature(itsTANDEM_ClassCCITT);
#elif defined(ANSI)
    ITS_AddFeature(itsSS7STACK_ClassANSI);

    ITS_AddFeature(isupANSI95_Class);

    ITS_AddFeature(itsTANDEM_ClassANSI);
#endif



    /*--------------------------------------------------------------------------
     *
     *  Create transport.
     */

    initMask = (ITS_ISUP_ANSI | ITS_TRANSPORT_SS7 |
                         ITS_TRANSPORT_SINGLE_USER);

    handle = (ITS_HANDLE)ITS_Initialize(initMask, instance);

    if (handle == NULL)
    {
        printf("\nIntelliSS7 Error <%s>.\n",
               ITS_GetErrorText(ITS_ENOTRANSPORT));

        ITS_GlobalStop();

        return 0;
    }
    /* Make It Global*/
     Tandem_handle = handle;

    /*--------------------------------------------------------------------------
     * Main Application Loop
     *
     */

    WorkerDispatchFunction(Tandem_handle);

    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 termination.
     */
    ITS_Terminate(handle);

    ITS_GlobalStop();

    return ITS_SUCCESS;
}

