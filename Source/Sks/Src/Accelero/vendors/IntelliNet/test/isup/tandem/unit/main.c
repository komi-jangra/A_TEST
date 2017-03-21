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
 * $Id: main.c,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:55:19  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:54:29  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 1.1  2003/02/07 23:21:47  vnitin
 * Add first tandem test
 *
 * Revision 7.1  2002/08/26 22:10:39  mmiers
 * Begin PR6.2
 *
 * Revision 1.3  2002/08/07 21:51:49  hbalimid
 * updated to work with new infrastructure.
 *
 * Revision 1.2  2002/05/20 15:58:50  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.3  2002/05/09 18:40:21  labuser
 * Merge from ISUP_APR_19_2002 to PR6.
 *
 * Revision 1.1.2.2.2.1  2002/05/09 14:52:50  labuser
 * Change return from main (use return value from ENGINE_Run()).
 *
 * Revision 1.1.2.2  2002/04/15 00:54:50  hbalimid
 * ISUP Load test - Base Version Done.
 *
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

#include <its_iniparse.h>
#include <ansi/mtp3.h>
#include <ss7_mgmt.h>

#include <its_dsm_stub.h>

#include <isup_intern.h>

#if defined(CCITT)
#define ISS7_Stack ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack itsTANDEM_ClassANSI
#endif


/*
 * IntelliSS7 Includes
 */
#include <its.h>
#include <its_app.h>

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
main(int argc, char **argv)
{
    int res = 0;
    ITS_HDR hdr;
    ITS_OCTET cic_state;
    ITS_USHORT boardNum, cic;
    ITS_CTXT vcic;
    ITS_OCTET sio = 0x85;
    int ret;
    ITS_EVENT ev;
    ITS_UINT opc, dpc;
    ITS_UINT initMask;
    ITS_HANDLE handle;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ITS_INT ieIndex = 0;

    printf("\nBegin INTELLINET ISUP Test...\n");

    /* FIXME: hardcode */
    boardNum = 1;
    cic = 12;
    hdr.context.cic = cic;
    opc = 0x0208CB;
    dpc = 0x0208D0;
    /* --- */

    /*-------------------------------------------------------------------
     * Setting the name of the application. The application name is the
     * name of the ini file read by IntelliSS7.
     */
    printf("**** MAIN MAIN MAIN MAIN  *****");
    APPL_SetName("$NODEA.VNITIN.NSKINI");
    APPL_SetConfigFileExtension("");
    APPL_SetTraceDir("");
    printf("**** GOT Passed APP STUFF *****");

    ITS_AddFeature(itsDSM_StubImplClass);

#if defined(CCITT)
    ITS_AddFeature(itsSS7STACK_ClassCCITT);
    printf("**** GOT Passed itsSS7STACK_ClassCCITT *****");
    ITS_AddFeature(itsINTELLISS7_ClassCCITT);
    printf("**** GOT Passed itsINTELLISS7_ClassCCITT *****");
    ITS_AddFeature(isupITU93_Class);

    ITS_AddFeature(itsTANDEM_ClassCCITT);
#elif defined(ANSI)
    ITS_AddFeature(itsSS7STACK_ClassANSI);
    printf("@@@@@ GOT Passed itsSS7STACK_ClassANSI @@@@@");
/*  ITS_AddFeature(itsINTELLISS7_ClassANSI); */
    ITS_AddFeature(isupANSI95_Class);
    printf("~~~~ GOT Passed  isupANSI95_Class ~~~~~");
    ITS_AddFeature(itsTANDEM_ClassANSI);
    printf("### GOT Passed  itsTANDEM_ClassANSI ####");
#endif

    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 subsystems initialization (including licensing).
     */
#if 0
    res = ITS_GlobalStart(ITS_ISUP | ITS_SS7_MASK);
#endif

    if (res != ITS_SUCCESS)
    {
        printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(res));

        return 0;
    }

    /*--------------------------------------------------------------------------
     *
     *  Create transport.
     */

    /* Create a Border Transport */

    initMask = (ITS_ISUP_ANSI | ITS_TRANSPORT_SS7 |
                         ITS_TRANSPORT_SINGLE_USER);

    handle = (ITS_HANDLE)ITS_Initialize(initMask, boardNum);

    if (handle == NULL)
    {
        printf("\nIntelliSS7 Error <%s>.\n",
               ITS_GetErrorText(ITS_ENOTRANSPORT));

        ITS_GlobalStop();

        return 0;
    }

    /*------ Send UBL to Network -----*/
    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;
    hdr.context.cic = cic;

    ieIndex = 0;

    ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieIndex].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                             sio, opc, dpc, (cic & 0x000F) );
    ieIndex++;

    ieCount = ieIndex;

    res  = ISUP_SendUBLRequest(handle, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
        printf("Error in sending UBL for cic %d \n", cic);
        return (res);
    }
    
    /* --- Try Reserving Cic --
    ret = ISUP_ReserveCIC_ANSI(handle, sio, opc, dpc,
                           cic, &cic_state, &vcic);
    if (ret != ITS_SUCCESS)
    {
        printf("ReserveCIC failed (%d)\n", ret);
    }
     */
    while (1)
    {
        ret = ITS_GetNextEvent(handle, &ev);

        if (ret == ITS_SUCCESS)
        printf (" Hello Tandem World");
    }
    /*--------------------------------------------------------------------------
     *
     *  IntelliSS7 termination.
     */
    ITS_Terminate(handle);

    ITS_GlobalStop();

    return ITS_SUCCESS;
}


