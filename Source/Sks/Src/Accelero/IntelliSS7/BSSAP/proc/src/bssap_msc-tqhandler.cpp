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
 * ID: $Id: bssap_msc-tqhandler.cpp,v 1.1.1.1 2007-10-08 11:11:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.4  2005/12/19 05:05:33  adutta
 * LOG: Changes to follow only 3GPP8.08
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/18 06:38:59  mkrishna
 * LOG: Added MTP/SCCP status checks
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/17 06:34:51  mkrishna
 * LOG: Fix issue id#3024/3019
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:02:45  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/
                                                                                                                             

#include <bssap_msc-tqhandler.h>
#include <bssap_msc-sccphandler.h>
#include <bssap_msc-discriminator.h>
#include <bssap_msc-timer.h>

extern ITS_BOOLEAN pauseFlag;
extern ITS_BOOLEAN sspFlag;

/*implementation:internal
*
* PURPOSE:
*      Thread function to receive application and SCCP stack data.
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  10-10-2005   IMR-MSC-SDS-BSAP-V1.0.01
*                        ID :: D0640, ID :: D0320
*                        ID :: D0310, ID :: D0920
*/
THREAD_RET_TYPE
BSSAP_MssgHandler(void* arg)
{
    ITS_INT ret = 0;
    TQUEUETRAN_Manager* recvQ = (TQUEUETRAN_Manager*)arg;
    ITS_EVENT bssapEvent;
    BSSAP_SCCPHandler sccpHndl;
    BSSAP_Interface bssIf;
    BSSAP_Discriminator dis; 
    BSSAP_Timer timer;


    ret = SCCP_EnableUserPart(SCCP_SSN_BSSAP, ITS_BSSAP_SRC);
    if (ret != ITS_SUCCESS)
    {
        BSSAP_CRITICAL(("BSSAP_MssgHandler: SCCP registration failed %d\n", 
                                                                  ret));
        exit(0);
    }
    else
    {
        BSSAP_DEBUG(("BSSAP_MssgHandler: User Part enabled. ssn 0x%02X \n",
                                                         SCCP_SSN_BSSAP));
    }

    for (;;)
    {
        memset(&bssapEvent, 0, sizeof(ITS_EVENT));

        ret = TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(recvQ))
                                                        (recvQ,
                                                         &bssapEvent);
        if (ret != ITS_SUCCESS)
        {
            continue;
        }

        ITS_Event evt(&bssapEvent);

        switch(evt.GetSource())
        {
            case ITS_BSSAP_SRC:
                break;

            case ITS_SCCP_SRC:
                BSSAP_DEBUG(("BSSAP_MssgHandler: Received SCCP event\n"));
                sccpHndl.BSSAP_ProcessSCCPdata(evt);
                break;

            case ITS_TIMER_SRC:
                BSSAP_DEBUG(("BSSAP_MssgHandler: Received Timeout event\n"));
                timer.ProcessTimeout(evt); 
                break;

            case BSSAP_HND_SRC:
                BSSAP_DEBUG(("BSSAP_MssgHandler: Received Layer3 event\n"));
                if (!pauseFlag)
                {
                    if (!sspFlag)
                    {
                        ret = dis.ProcessHandoverMessages(evt);
                    }
                    else
                    {
                        BSSAP_CRITICAL(("BSSAP_MssgHandler: "
                                           "Remote sub-system down\n"));
                                                                                                                                              
                        ret = (!ITS_SUCCESS);
                    }
                }
                else
                {
                    BSSAP_CRITICAL(("BSSAP_MssgHandler: Network down\n"));
                                                                                                                                              
                    ret = (!ITS_SUCCESS);
                }
                break;

            default:
                BSSAP_DEBUG(("BSSAP_MssgHandler: Received app. event\n"));

                if (!pauseFlag)
                {
                    if (!sspFlag)
                    {
                        ret = dis.ProcessOutBSSAPMessage(evt); 
                    }
                    else
                    {
                        BSSAP_CRITICAL(("BSSAP_MssgHandler: " 
                                           "Remote sub-system down\n"));

                        ret = (!ITS_SUCCESS);
                    }
                }
                else
                {
                    BSSAP_CRITICAL(("BSSAP_MssgHandler: Network down\n"));

                    ret = (!ITS_SUCCESS);
                }
                break; 
        }

        if (ret != ITS_SUCCESS)
        {
            BSSAP_ERROR(("BSSAP_MssgHandler: Message sent failed\n"));
            bssIf.DispatchErrorToApp(BSSAP_MD_PROTOCOL, BSSAP_EMSGSENTFAIL);
        }

        ITS_EVENT_TERM(&bssapEvent);
    }
}
