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
 *  ID: $Id: ansi-smh.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:06  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/05/06 10:04:15  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1731) Fix.
 * LOG:
 * LOG: Revision 9.2  2005/05/06 06:05:27  adutta
 * LOG: MTP Route peg declaration
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:53:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.9.2.1.2.5.6.4  2005/02/24 11:33:37  mmanikandan
 * LOG: CTF Trace added.
 * LOG:
 * LOG: Revision 7.9.2.1.2.5.6.3  2005/01/25 11:34:26  snagesh
 * LOG: OAM Bug fixes for bugs 1419,1420
 * LOG:
 * LOG: Revision 7.9.2.1.2.5.6.2  2005/01/05 10:35:55  craghavendra
 * LOG: Critical Trace before abort().
 * LOG:
 * LOG: Revision 7.9.2.1.2.5.6.1  2004/12/31 06:53:26  sbabu
 * LOG: MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.9.2.1.2.5  2004/10/20 05:57:27  sswami
 * LOG: Hex dump trace added
 * LOG:
 * LOG: Revision 7.9.2.1.2.4  2004/09/07 06:39:27  sswami
 * LOG: Fix for displaying wrong dpc for alarm 2104
 * LOG:
 * LOG: Revision 7.9.2.1.2.3  2004/09/03 09:23:34  sswami
 * LOG:  Fix given for  text changes made for 2104 & 2103
 * LOG:
 * LOG: Revision 7.9.2.1.2.2  2004/08/10 12:14:45  kannanp
 * LOG: Changes for MTP3 pegs, alarms & MMLs - propagated from TCS.
 * LOG:
 * LOG: Revision 7.9.2.1.2.1  2004/01/27 14:08:37  sjaddu
 * LOG: Changes for active-back up configuration.
 * LOG:
 * LOG: Revision 7.9.2.1  2003/11/28 07:50:11  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.9  2003/02/13 10:24:45  ttipatre
 * LOG: New Alarms added.
 * LOG:
 * LOG: Revision 7.8  2003/01/15 09:19:32  ttipatre
 * LOG: Send TFP for invalid destination fixed.
 * LOG:
 * LOG: Revision 7.7  2002/12/24 19:22:34  randresol
 * LOG: Move LINK_FindLink to improve performance
 * LOG:
 * LOG: Revision 7.6  2002/12/24 07:40:48  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.5  2002/11/20 05:10:56  ttipatre
 * LOG: Pegs and Alarms code submission.
 * LOG:
 * LOG: Revision 7.4  2002/11/14 21:53:44  randresol
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 7.3  2002/11/09 22:09:55  randresol
 * LOG: Replace LINK_FindLinkLock LINK_FindLinkNoLock for faster processing
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.10  2002/07/30 14:13:47  mmiers
 * LOG: Wrong function called.
 * LOG:
 * LOG: Revision 6.9  2002/07/25 14:21:51  randresol
 * LOG: Fix bugs found during functional testing.
 * LOG:
 * LOG: Revision 6.8  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.7  2002/05/03 22:35:29  mmiers
 * LOG: Bug fixes.
 * LOG:
 * LOG: Revision 6.6  2002/04/29 21:23:21  randresol
 * LOG: Add InterNode processing and shared booleans
 * LOG:
 * LOG: Revision 6.5  2002/04/08 19:10:35  mmiers
 * LOG: Bug fix for user parts.
 * LOG:
 * LOG: Revision 6.4  2002/03/27 18:38:34  randresol
 * LOG: Remove Visual C++ warnings
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:28:23  randresol
 * LOG: crBuf, cocbBuf, rtrvBuf and route list are now in DSM
 * LOG:
 * LOG: Revision 6.2  2002/03/12 22:41:55  mmiers
 * LOG: Magic number removal.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.46  2002/02/28 15:31:09  mmiers
 * LOG: On failure to send certain messages send synthetic events
 * LOG: back.
 * LOG:
 * LOG: Revision 5.45  2002/01/09 21:24:15  mmiers
 * LOG: Correct the build settings, add XCO/XCA (SAAL changeover).
 * LOG:
 * LOG: Revision 5.44  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.43  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.42  2001/12/11 23:49:52  mmiers
 * LOG: Get rid of FIXMEs.
 * LOG:
 * LOG: Revision 5.41  2001/12/06 22:39:04  mmiers
 * LOG: First cut of ITU MTP3.
 * LOG:
 * LOG: Revision 5.40  2001/11/30 23:43:14  mmiers
 * LOG: Start testing config-d (route management).
 * LOG:
 * LOG: Revision 5.39  2001/11/29 23:43:24  mmiers
 * LOG: All config A tests passed (by kicking the INET).
 * LOG:
 * LOG: Revision 5.38  2001/11/22 00:05:27  mmiers
 * LOG: Todays fixes.
 * LOG:
 * LOG: Revision 5.37  2001/11/16 23:37:40  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.36  2001/11/14 23:17:13  mmiers
 * LOG: Many changes from conformance testing.
 * LOG:
 * LOG: Revision 5.35  2001/11/09 20:19:54  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.34  2001/11/07 18:05:52  mmiers
 * LOG: Fixes for changeback.  Finally working.
 * LOG:
 * LOG: Revision 5.33  2001/11/07 01:14:40  mmiers
 * LOG: Fix CBD logic.
 * LOG:
 * LOG: Revision 5.32  2001/11/02 23:03:31  mmiers
 * LOG: Convert to new event queuing.
 * LOG:
 * LOG: Revision 5.31  2001/10/30 00:16:10  mmiers
 * LOG: Today's debugging session.  Looks close.
 * LOG:
 * LOG: Revision 5.30  2001/10/25 16:51:32  mmiers
 * LOG: SLT timer context bug.  T28 timer context bug.  Fix bugs in
 * LOG: SMH I added yesterday.
 * LOG:
 * LOG: Revision 5.29  2001/10/24 22:16:38  mmiers
 * LOG: Add current route logic.
 * LOG:
 * LOG: Revision 5.28  2001/10/22 21:18:21  rsonak
 * LOG: Get cvs logs in the file
 * LOG:
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_callback.h>
#include <its_mutex.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_assertion.h>
#include <its_thread_pool.h>
#include <its_redundancy.h>
#include <its_ctf.h>
#include <engine.h>

#ident "$Id: ansi-smh.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/snmm.h>
#include <ansi/sltm.h>
#include <ansi/mtp3.h>
#include <itu/mtp3.h>

#include "mtp3_intern.h"

/* local data */
static ITS_BOOLEAN      TRIGGER_FOR_ROUTING = ITS_FALSE;

extern ITS_Class ITS_RedundancyClass;
extern ITS_UINT PEER_MTP3_NODE_STATUS;
/*
 * signalling message handling: message discrimination
 */
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
SMH_Main_ANSI(MTP3_SubSystems src, MTP3_SubSystems dest,
              SMH_Triggers trigger,
              ITS_OCTET *sif, ITS_USHORT len,
              ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_ANSI(MTP3_SMH, src, trigger, sif, len,
                          linkSet, linkCode);

    switch (trigger)
    {
    /* HMDC */
    /* HMDT */
    case SMH_TRIGGER_L2_L3_MSG:
        /*
         * we have to be a little more creative than the SDLs.  They
         * magically deliver MTP2 indications to the right place without
         * saying how that happens.
         */
        switch (sif[0])
        {
        case L2_L3_IN_SERVICE:
            return LSAC_Main_ANSI(MTP3_L2,
                                  SLM_TRIGGER_L2_IN_SERVICE,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_REMOTE_PROCESSOR_OUT:
            return LSAC_Main_ANSI(MTP3_L2,
                                  SLM_TRIGGER_L2_RPO,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_OUT_OF_SERVICE:
            MTP3_ERROR(("OUT_OF_SERVICE  Received at MTP3\n"));
            return LSAC_Main_ANSI(MTP3_L2,
                                  SLM_TRIGGER_L2_OUT_OF_SERVICE,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_REMOTE_PROCESSOR_REC:
            return LSAC_Main_ANSI(MTP3_L2,
                                  SLM_TRIGGER_L2_RPR,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_BSNT:
            MTP3_ERROR(("L2_L3_BSNT Received at MTP3\n"));
            return TCOC_Main_ANSI(MTP3_L2,
                                  STM_TRIGGER_BSNT,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_BSNT_NOT_RETRIEVABLE:
            MTP3_ERROR(("L2_L3_BSNT_NOT_RETRIEVABLE at MTP3\n"));
            return TCOC_Main_ANSI(MTP3_L2,
                                  STM_TRIGGER_BSNT_NOT_RETRIEVABLE,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_RETRIEVED_MSG:
            MTP3_ERROR(("L2_L3_RETRIEVED_MSG at MTP3\n"));
            return TCOC_Main_ANSI(MTP3_L2,
                                  STM_TRIGGER_RETRIEVED_MSGS,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_RETRIEVAL_COMPLETE:
            MTP3_ERROR(("L2_L3_RETRIEVAL_COMPLETE  at MTP3\n"));
            return TCOC_Main_ANSI(MTP3_L2,
                                  STM_TRIGGER_RETRIEVAL_COMPLETE,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_RETRIEVAL_NOT_POSSIBLE:
            MTP3_ERROR(("L2_L3_RETRIEVAL_NOT_POSSIBLE at MTP3\n"));
            return TCOC_Main_ANSI(MTP3_L2,
                                  STM_TRIGGER_RETRIEVAL_NOT_POSSIBLE,
                                  sif, len,
                                  linkSet, linkCode);
            
        case L2_L3_DATA:
            return HMDC_Main_ANSI(MTP3_L2, trigger,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_RB_CLEARED:
            return LSAC_Main_ANSI(MTP3_L2,
                                  SLM_TRIGGER_RB_CLEARED,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_RTB_CLEARED:
            return LSAC_Main_ANSI(MTP3_L2,
                                  SLM_TRIGGER_RTB_CLEARED,
                                  sif, len,
                                  linkSet, linkCode);

        case L2_L3_CONGESTION_ONSET:
        case L2_L3_CONGESTION_ABATES:
            return TSRC_Main_ANSI(MTP3_L2,
                                  STM_TRIGGER_LINK_CONGESTION_STATUS,
                                  sif, len,
                                  linkSet, linkCode);

        default:
            MTP3_ERROR(("Unknown msg type: %d\n", sif[0]));
            MTP3_Alarm_ANSI(2406, __FILE__, __LINE__, "%d from L2", 
                             sif[0]);
            PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
            break;
        }
        break;

    case SMH_TRIGGER_L4_L3_MSG:
        return HMRT_Main_ANSI(MTP3_L4, trigger,
                              sif, len,
                              linkSet, linkCode);

    default:
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        MTP3_CRITICAL(("SMH_Main_ANSI: SMH_Triggers Unknown Type\n"));  
        abort();
    }

    /* NOTREACHED */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
HMDC_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3a;
    MTP3_HEADER_CCITT *mtp3i;
    ITS_UINT dpc;
    ITS_BOOLEAN isNational = ITS_TRUE;
    ITS_BOOLEAN isLocal = ITS_FALSE;
    int ret;
    ITS_OCTET up, ni;
    
    MTP3_TRACE_ENTRY_ANSI(MTP3_SMH_HMDC, src, trigger, sif, len,
                          linkSet, linkCode);

    /*
     * determine label structure.  Should only handle national networks
     * here.
     *
     * byte 1 of the buffer is the SIO.  Use the NI to determine which
     * MTP3 decode to use (ANSI or ITU).
     */
    mtp3a = (MTP3_HEADER_ANSI *)&sif[1];
    mtp3i = (MTP3_HEADER_CCITT *)&sif[1];
    if ((MTP3_HDR_GET_SIO_ANSI(*mtp3a) & MTP3_NIC_MASK) == MTP3_NIC_INTERNATIONAL ||
        (MTP3_HDR_GET_SIO_ANSI(*mtp3a) & MTP3_NIC_MASK) == MTP3_NIC_SPARE)
    {
        isNational = ITS_FALSE;
        dpc = MTP3_RL_GET_DPC_VALUE_CCITT(mtp3i->label);
    }
    else if ((MTP3_HDR_GET_SIO_ANSI(*mtp3a) & MTP3_NIC_MASK) == MTP3_NIC_NATIONAL)
    {
        dpc = MTP3_RL_GET_DPC_VALUE_ANSI(mtp3a->label);
    }
    else if ((MTP3_HDR_GET_SIO_ANSI(*mtp3a) & MTP3_NIC_MASK) == MTP3_NIC_RESERVED)
    {
        if (MTP3_ANSI_HandleSpareNIC)
        {
            dpc = MTP3_RL_GET_DPC_VALUE_ANSI(mtp3a->label);
        }
        else
        {
            /* discard, what else can we do? */
            MTP3_DEBUG(("MTP3_HMDC: Failed to handle L2 message\n"));

            MTP3_Alarm_ANSI(2407, __FILE__, __LINE__, NULL);
            
            return (ITS_EINVALIDARGS);
        }
    }
    else
    {
        /* discard, what else can we do? */
        MTP3_DEBUG(("MTP3_HMDC: Failed to handle L2 message\n"));

        MTP3_Alarm_ANSI(2407, __FILE__, __LINE__, NULL);
            
        return (ITS_EINVALIDARGS);
    }
    
    up = MTP3_HDR_GET_SIO_ANSI(*mtp3a) & MTP3_SIO_UP_MASK;
    ni = MTP3_HDR_GET_SIO_ANSI(*mtp3a) & MTP3_NIC_MASK;
    if ((ret = ROUTE_GetRouteContextLocal(dpc, &isLocal,
                                          /* ROUTE_DPC_NI, */ ROUTE_DPC_SIO,
                                          FAMILY_ANSI,
                                          ni | up,
                                          ITS_SS7_DEFAULT_LINK_SET,
                                          ITS_SS7_DEFAULT_LINK_CODE,
                                          ITS_SS7_DEFAULT_PRI,
                                          ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
    {
        MTP3_DEBUG(("MTP3_HMDC: Route failure\n"));
 
        MTP3_Alarm_ANSI(2408, __FILE__, __LINE__, "user part %d",up);

        isLocal = ITS_FALSE;
    }
    
    /*
     * if local, send to distribution.  Else send to routing.
     */
    if (isNational)
    {
        if (isLocal)
        {
            return HMDT_Main_ANSI(MTP3_SMH_HMDC,
                                  SMH_TRIGGER_L2_L3_MSG,
                                  sif, len,
                                  linkSet, linkCode);
        }
        else
        {
            return HMRT_Main_ANSI(MTP3_SMH_HMDC,
                                  SMH_TRIGGER_MSG_FOR_ROUTING,
                                  sif, len,
                                  linkSet, linkCode);
        }
    }
    else
    {
#if 0
       /*Fix bug 585 for ANSI International Links doesnt come active*/
        ITS_EVENT ev;
        int ret;

        /*
         * build event, send it to ITU-MTP3.
         */
        ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, len + 3 * sizeof(ITS_OCTET));
        ev.data[0] = L2_L3_DATA;
        ev.data[1] = linkSet;
        ev.data[2] = linkCode;
        if (len)
        {
            memcpy(L2_LINK_DATA(&ev), sif, len);
        }

        ret = TRANSPORT_PutEvent(ITS_MTP3_CCITT_SRC, &ev);

        ITS_EVENT_TERM(&ev);

        return (ret);
#endif
        /*
         * this is the old way we did it.
         */
        if (isLocal)
        {
            return HMDT_Main_ANSI(MTP3_SMH_HMDC,
                                 SMH_TRIGGER_L2_L3_MSG,
                                 sif, len,
                                 linkSet, linkCode);
        }
        else
        {
            return HMRT_Main_ANSI(MTP3_SMH_HMDC,
                                 SMH_TRIGGER_MSG_FOR_ROUTING,
                                 sif, len,
                                 linkSet, linkCode);
        }
    }
}

/*
 * HMDT
 */
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
HMDT_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SNMM_MESSAGE *snmm;
    MTP3_HEADER *mtp3;
    MTP3_HEADER_ANSI omtp3;
    SNMM_MESSAGE osnmm;
    ITS_UINT pc1, pc2;
    ITS_USHORT dest;
    ITS_EVENT ev;
    ITS_OCTET sio, ni;
    int ret;
    
    MTP3_TRACE_ENTRY_ANSI(MTP3_SMH_HMDT, src, trigger, sif, len,
                          linkSet, linkCode);

    mtp3 = (MTP3_HEADER_ANSI *)&sif[1];

    sio = MTP3_HDR_GET_SIO(*mtp3);

    switch (sio & MTP3_SIO_UP_MASK)
    {
    case MTP3_SIO_SNMM: /* signalling network management */
        snmm = (SNMM_MESSAGE *)&sif[sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_OCTET)];
        switch (SNMM_HC0_GET_ANSI(*snmm))
        {
        case SNMM_HC0_CHM_ANSI: /* changeover */
        case SNMM_HC0_ECM_ANSI: /* emergency changeover */
        case SNMM_HC0_MIM_ANSI: /* management inhibit */
        case SNMM_HC0_TRM_ANSI: /* traffic restart */
        case SNMM_HC0_UFC_ANSI: /* user flow control */
            return STM_Main_ANSI(MTP3_SMH_HMDT, MTP3_STM,
                                 STM_TRIGGER_L2_MSG,
                                 sif, len,
                                 linkSet, linkCode);
            
        case SNMM_HC0_FCM_ANSI: /* transfer controlled/congestion */
        case SNMM_HC0_TFM_ANSI: /* transfer prohibit/allow/restrict */
        case SNMM_HC0_RSM_ANSI: /* route set test */
            return SRM_Main_ANSI(MTP3_SMH_HMDT, MTP3_SRM,
                                 SRM_TRIGGER_L2_MSG,
                                 sif, len, linkSet, linkCode);
            
        case SNMM_HC0_DLM_ANSI: /* data link connection */
            return SLM_Main_ANSI(MTP3_SMH_HMDT, MTP3_SLM,
                                 SLM_TRIGGER_L2_MSG,
                                 sif, len,
                                 linkSet, linkCode);
            
        default:
            MTP3_DEBUG(("HMDT_Main_ANSI: Invalid HCO\n"));
            return (ITS_EINVALIDARGS);
        }
        break;
        
    case MTP3_SIO_SLTM_REG: /* signalling network testing and maintenance */
    case MTP3_SIO_SLTM_SPEC:
        return SLT_Main_ANSI(MTP3_SMH_HMDT, MTP3_SLT,
                             SLT_TRIGGER_L2_MSG,
                             sif, len,
                             linkSet, linkCode);

    default:
        dest = MTP3_UserPartOwner_ANSI((ITS_OCTET)(sio & MTP3_SIO_UP_MASK));

        if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
        {
            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            if ((ret = MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA,
                                        mtp3,
                                        sif + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_OCTET),
                                        (ITS_USHORT)
                                            (len - sizeof(MTP3_HEADER_ANSI) -
                                             sizeof(ITS_OCTET)))) != ITS_SUCCESS)
            {
                MTP3_DEBUG(("HMDT_Main_ANSI: MTP3 encode failed.\n"));

                MTP3_Alarm_ANSI(2501, __FILE__, __LINE__, "Destination %d", dest);
            
                return (ret);
            }

            if (ITS_RedundancyClass != NULL)
            {
                /* Now we have to check the user part state*/
                if (REDUNDANCY_GET_NODE_STATE(ITS_RedundancyClass)
                                    == ITS_STATE_BACKUP)
                {
                    TRANSPORT_Control *trCtl = NULL;
                    /* Put the event on the inter node
                     * hopefully we find some nicer way to do it
                     * TBD
                     */
                    trCtl = TRANSPORT_FindTransportByName(
                                                MTP3_INTER_NODE_STRING);
                    if (trCtl == NULL) 
                    {
                        return ret;
                    }

                    ev.src = sio & MTP3_SIO_UP_MASK;

                    ret = TRANSPORT_PutEvent(TRANSPORT_INSTANCE(trCtl), &ev);
                    if (ret != ITS_SUCCESS)
                    {
                        MTP3_DEBUG(("HMDT_Main_CCITT: No Inter node connection %d\n"));
                        return ret;
                    }

                    TRANSPORT_UnfindTransport(trCtl);
                    return ret;
                }
            }

            /* We are here becuz active or stub */
             
            PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_MSU_RX);
        
            return TRANSPORT_PutEvent(dest, &ev);
        }
        else
        {
            SS7_LinkPtr ln;

            /* build UPU, send */
            pc1 = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            pc2 = MTP3_RL_GET_OPC_VALUE(mtp3->label);
            ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
            MTP3_HDR_SET_SIO(omtp3, MTP3_SIO_SNMM | ni | MTP3_MPC_PRI_3);
            MTP3_RL_SET_DPC_VALUE(omtp3.label, pc2);
            MTP3_RL_SET_OPC_VALUE(omtp3.label, pc1);

            SNMM_HC0_SET_ANSI(osnmm, SNMM_HC0_UFC_ANSI);
            SNMM_HC1_SET_ANSI(osnmm, SNMM_HC1_UPU_ANSI);
            SNMM_USER_PART_UNAVAIL_SET_DEST_ANSI(osnmm.data.userPartUnavailable,
                                                 pc1);
            SNMM_USER_PART_UNAVAIL_SET_USER_ANSI(osnmm.data.userPartUnavailable,
                                                 MTP3_HDR_GET_SIO(*mtp3) &
                                                    MTP3_SIO_UP_MASK);
            SNMM_USER_PART_UNAVAIL_SET_CAUSE_ANSI(osnmm.data.userPartUnavailable,
                                                  SNMM_UPU_CAUSE_UNEQUIPPED);

            ITS_EVENT_INIT(&ev, ITS_MTP3_ANSI_SRC, 0);
            SNMM_Encode_ANSI(&ev, &omtp3, &osnmm);

            if ( (ln = LINK_FindLinkNoLock(linkSet, linkCode)) != NULL)
            {
                /* Increament Link Peg for UPU Transmitted */
                PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_MTP3_LINK_UPU_TX);
            }

            ret = HMRT_Main_ANSI(MTP3_SMH_HMDT,
                                 SMH_TRIGGER_MSG_FOR_ROUTING,
                                 ev.data, ev.len,
                                 linkSet, linkCode);
            ITS_EVENT_TERM(&ev);

            return (ret);
        }
        break;
    }
}

/*
 * HMRT
 */
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static int
MessageForRouting(ITS_OCTET *sif, ITS_USHORT len,
                  ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    int ret;
    ITS_USHORT dest;
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    ITS_UINT dpc, opc;
    ITS_BOOLEAN isLocal = ITS_FALSE;
    ITS_OCTET ni, up, sls;
    SS7_Destination *rc;
    MTP3_POINT_CODE pc;
    ROUTE_MatchInfo rinfo;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    up = MTP3_HDR_GET_SIO(*mtp3) & MTP3_SIO_UP_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);
    MTP3_ERROR(("MessageForRouting sls = %d\n",sls));
    rinfo.rkey = 0;

    /*
     * Any routing data for that DPC?
     */
    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_ANSI,
                                      ni,
                                      ITS_SS7_DEFAULT_LINK_SET,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {
        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }
    //MTP3_DEBUG(("MessageForRouting:After  ROUTE_ParseRouteMatchInfoArgs Route message to ls:%d lc:%d rinfo.sls %d\n", rinfo.linkSet, rinfo.linkCode,rinfo.sls));  


    dest = ROUTE_SelectRouteContextInfo(&rinfo);
    //MTP3_DEBUG(("MessageForRouting: After ROUTE_SelectRouteContextInfo Route message to ls:%d lc:%d rinfo.sls %d\n", rinfo.linkSet, rinfo.linkCode,rinfo.sls));  
    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     */

    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

        if ((ret = ROUTE_GetRouteContextLocal(opc, &isLocal,
                                              ROUTE_DPC_SIO,
                                              FAMILY_ANSI,
                                              ni | up,
                                              ITS_SS7_DEFAULT_LINK_SET,
                                              ITS_SS7_DEFAULT_LINK_CODE,
                                              ITS_SS7_DEFAULT_PRI,
                                              ITS_SS7_DEFAULT_SLS)) != ITS_SUCCESS)
        {
            MTP3_DEBUG(("MessageForRouting: RouteContextLocal\n"));

            /* fix for Bug 162 */
            if ((dest == ITS_INVALID_SRC) && TRIGGER_FOR_ROUTING)
            {
                MTP3_DEBUG(("let RTPC know\n"));
            }
            else 
            {
                return (ITS_EINVALIDARGS);
            }
        }

        /* trigger managment */
        MGMT_Main_ANSI(MTP3_SMH_HMRT,
                       MGMT_TRIGGER_MSG_FOR_INVALID_DEST,
                       sif, len,
                       linkSet, linkCode);

        /* let RTPC know */
        if (isLocal)
        {
            return (ITS_EINVALIDARGS);
        }
        else
        {
            if ((rc = ROUTE_FindDestination(dpc, ni, FAMILY_ANSI)) == NULL)
            {
                MTP3_DEBUG(("FindDestination failed.\n"));

                MTP3_Alarm_ANSI(2411, __FILE__, __LINE__, 
                                 "dpc %x ni %x",dpc, ni);

                MTP3_PC_SET_VALUE(pc, dpc);

                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    return RTPC_Main_ANSI(MTP3_SMH_HMRT,
                                          SRM_TRIGGER_MSG_FOR_INACCESS_CLUST,
                                          sif, len,
                                          linkSet, linkCode);
                }
                else
                {
                    return RTPC_Main_ANSI(MTP3_SMH_HMRT,
                                          SRM_TRIGGER_MSG_FOR_INACCESS_SP,
                                          sif, len,
                                          linkSet, linkCode);
                }
            }

            /* if (!cluster inaccessible) */
            if (rc->status == DESTINATION_UNAVAILABLE)
            {
                MTP3_DEBUG(("Destination unavailable: %02x %08x.\n", ni, dpc));
                MTP3_Alarm_ANSI(2412, __FILE__, __LINE__,
                                "dpc %x ni %x",dpc, ni);

                MTP3_PC_SET_VALUE(pc, dpc);

                if (MTP3_PC_IS_CLUSTER_ANSI(pc))
                {
                    return RTPC_Main_ANSI(MTP3_SMH_HMRT,
                                          SRM_TRIGGER_MSG_FOR_INACCESS_CLUST,
                                          sif, len,
                                          linkSet, linkCode);
                }
                else
                {
                    return RTPC_Main_ANSI(MTP3_SMH_HMRT,
                                          SRM_TRIGGER_MSG_FOR_INACCESS_SP,
                                          sif, len,
                                          linkSet, linkCode);
                }
            }
        }

        return (ITS_SUCCESS);
    }
    else
    {
        if ((rc = ROUTE_FindDestination(dpc, ni, FAMILY_ANSI)) == NULL)
        {
            MTP3_DEBUG(("FindDestination failed, return.\n"));

            return (ITS_SS7_DEFAULT_LINK_SET);
        }

        /* if destination restricted */
        if (rc->status == DESTINATION_RESTRICTED)
        {
            MTP3_PC_SET_VALUE(pc, dpc);

            MTP3_Alarm_ANSI(2413, __FILE__, __LINE__, "dpc %x ni %x",dpc, ni);

            /* if cluster */
            if (MTP3_PC_IS_CLUSTER_ANSI(pc))
            {
                RTRC_Main_ANSI(MTP3_SMH_HMRT,
                               SRM_TRIGGER_MSG_FOR_RESTRICTED_CLUST,
                               sif, len,
                               linkSet, linkCode);
            }
            else
            {
                RTRC_Main_ANSI(MTP3_SMH_HMRT,
                               SRM_TRIGGER_MSG_FOR_RESTRICTED_DEST,
                               sif, len,
                               linkSet, linkCode);
            }
        }

        /*
         * DPC is acccessible.
         *
         * select linkset, link on the basis of the SLS.
         * User messages are handled here, so linkSet, linkCode are
         * unspecified here.  However,  the destination link has already
         * been selected and the SLS bits rotated.
         */
        MTP3_RL_SET_SLS(mtp3->label, sls);/* sandeep  jeevan as no information is available in rinfo*/
        //MTP3_RL_SET_SLS(mtp3->label, linkCode);
        
        //MTP3_DEBUG(("MessageForRouting: Route message to ls:%d lc:%d SLS %d\n", rinfo.linkSet, rinfo.linkCode,rinfo.sls));  

        PEG_IncrPeg(ANSI_MTP3_Pegs, PEG_MTP3_MSU_TX);
        /*PEG_IncrPeg(&ln->MTP3_LINK_PEGS, PEG_LINK_MSU_TX);*/

        rc = ROUTE_FindDestination(dpc, ni, FAMILY_ANSI);
        PEG_IncrPeg(&rc->MTP3_DPC_PEGS,PEG_MTP3_DPC_SIF_TX);
        

        return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                              SMH_TRIGGER_L3_L2_MSG,
                              sif, len,
                              rinfo.linkSet,
                              rinfo.linkCode,
                              rinfo.rkey);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static int
LinkManagementMessage(ITS_OCTET *sif, ITS_USHORT len,
                      ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_USHORT dest;
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    ITS_UINT dpc;
    ITS_OCTET ni, sls;
    ROUTE_MatchInfo rinfo;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);
    rinfo.rkey = 0;

    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_ANSI,
                                      ni,
                                      linkSet, linkCode,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {
        MTP3_Alarm_ANSI(2502, __FILE__, __LINE__,
                        "destination %x,linkset:linkcode %x:%x",
                        dpc,linkSet,linkCode);
        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }

    /* find route */
    dest = ROUTE_SelectRouteContextInfo(&rinfo);
    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     */

    /* is the destination accessible */
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        MTP3_Alarm_ANSI(2414, __FILE__, __LINE__,"dpc %x ni %x",dpc,ni);
        /* discard if it isn't */
        MTP3_Alarm_ANSI(2502, __FILE__, __LINE__,
                        "destination %x,linkset:linkcode %x:%x",
                        dpc,linkSet,linkCode);
        return (ITS_SUCCESS);
    }

    /*
     * SDL says "select an available link SLC".  To me, that means
     * "any way you can get there".  We don't really care about SLS
     * in this case.  SelectRouteContextInfo may return a link that
     * is down, but I guess that's ok, because traffic will be at
     * some point be transferred.
     */
    MTP3_RL_SET_SLS(mtp3->label, rinfo.sls);

    return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                          SMH_TRIGGER_L3_L2_MSG,
                          sif, len,
                          rinfo.linkSet,
                          rinfo.linkCode,
                          rinfo.rkey);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static int
TrafficManagementMessage(ITS_OCTET *sif, ITS_USHORT len,
                         ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    ITS_USHORT dest;
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    ITS_UINT dpc;
    SNMM_MESSAGE *snmm = (SNMM_MESSAGE *)(sif + sizeof(MTP3_HEADER_ANSI) +
                                          sizeof(ITS_OCTET));
    ITS_OCTET ni, sls;
    ROUTE_MatchInfo rinfo;
    SS7_Destination *d;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);
    rinfo.rkey = 0;

    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_ANSI,
                                      ni,
                                      ITS_SS7_DEFAULT_LINK_SET,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {
        MTP3_Alarm_ANSI(2503, __FILE__, __LINE__,
                         "destination %d", dpc);

        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }

    d = ROUTE_FindDestination(dpc, ni, FAMILY_ANSI);
    dest = ROUTE_SelectRouteContextInfo(&rinfo);

    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     */

    /*MTP3_RL_SET_SLS(mtp3->label, rinfo.sls);As rinfo is not havin the correct value need to pass same lincode */
    MTP3_RL_SET_SLS(mtp3->label, linkCode);

    /* management inhibit message? */
    if (SNMM_HC0_GET_ANSI(*snmm) == SNMM_HC0_MIM_ANSI)
    {
        /* force uninhibit? */
        if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_LFU_ANSI)
        {
            /* select link coded in SLC */
            return HMCG_Main_ANSI(MTP3_SMH_HMRT, SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
        }
        /* uninhibit or uninhibit ack? */
        else if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_LUN_ANSI ||
                 SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_LUA_ANSI)
        {
            /* DPC accessible? */
            /*
             * Houston, we have a problem.  Some tests like the first
             * form, some prefer the second.  It would be nice to know
             * why.  I suspect it's when the first form sees the allowed
             * flag.
             */

            /*if (d->status != DESTINATION_UNAVAILABLE)*/
            if  (dest != ITS_NO_SRC && dest != ITS_INVALID_SRC) 
            {

                /* yes, select an available link */
                return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                      SMH_TRIGGER_L3_L2_MSG,
                                      sif, len,
                                      rinfo.linkSet,
                                      rinfo.linkCode,
                                      rinfo.rkey);
            }

            /* select link coded in SLC */

            return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                  SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
 
        }

        /* select an available link */
        return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                              SMH_TRIGGER_L3_L2_MSG,
                              sif, len,
                              rinfo.linkSet,
                              rinfo.linkCode,
                              rinfo.rkey);
    }
    /* destination accessible? */
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        MTP3_Alarm_ANSI(2415, __FILE__, __LINE__, "dpc %x ni %x",dpc,ni);

        MTP3_Alarm_ANSI(2503, __FILE__, __LINE__,
                         "destination %d", dpc);

        return (ITS_EINVALIDARGS);
    }

    /* changeback message? */
    if (SNMM_HC0_GET_ANSI(*snmm) == SNMM_HC0_CHM_ANSI)
    {
        /* changeback declaration */
        if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_CBD_ANSI)
        {
            /*
             * Select an alternative link based on the SLC and the
             * changeback code.  Interpretation, anyone?  Yes.  Use
             * what the caller gave you.
             */
            return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                  SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
        }
        /* changeback ack */
        else if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_CBA_ANSI)
        {
            /* select linkSet, link based on loadsharing and SLS */
            return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                  SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
        }
        /* changeover */
        else if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_COO_ANSI ||
                 SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_XCO_ANSI)
        {
            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                  SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
        }
        /* changeover ack */
        else if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_COA_ANSI ||
                 SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_XCA_ANSI)
        {
            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                  SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
        }
    }
    /* changeback message? */
    else if (SNMM_HC0_GET_ANSI(*snmm) == SNMM_HC0_ECM_ANSI)
    {
        /* changeover */
        if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_ECO_ANSI)
        {
            MTP3_Alarm_ANSI(2515, __FILE__, __LINE__, "ECO Trasmitted on %d:%d",
                            linkSet,linkCode);
            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                  SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
        }
        /* changeover ack */
        else if (SNMM_HC1_GET_ANSI(*snmm) == SNMM_HC1_ECA_ANSI)
        {
            /* select linkSet, link based on what TLAC or TCOC tells us */
            return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                                  SMH_TRIGGER_L3_L2_MSG,
                                  sif, len,
                                  linkSet,
                                  linkCode,
                                  rinfo.rkey);
        }
    }

    if  (dest != ITS_NO_SRC && dest != ITS_INVALID_SRC)
    {
        /* select an available link */
        return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                              SMH_TRIGGER_L3_L2_MSG,
                              sif, len,
                              rinfo.linkSet,
                              rinfo.linkCode,
                              rinfo.rkey);
    }

    return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                          SMH_TRIGGER_L3_L2_MSG,
                          sif, len,
                          linkSet,
                          linkCode,
                          rinfo.rkey);

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static int
TestControlMessage(ITS_OCTET *sif, ITS_USHORT len,
                   ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    ITS_UINT dpc;
    ITS_OCTET ni, sls;
    ROUTE_MatchInfo rinfo;
    ITS_USHORT dest;

    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    sls = MTP3_RL_GET_SLS(mtp3->label);
    //MTP3_ERROR(("\n TestControlMessage SLS =%d",sls));

    /* use linkSet, linkCode here */
    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, dpc,
                                      DONT_CARE, ROUTE_DPC_NI,
                                      FAMILY_ANSI,
                                      ni,
                                      linkSet,
                                      linkCode,
                                      ITS_SS7_DEFAULT_PRI,
                                      sls) != ITS_SUCCESS)
    {

        MTP3_Alarm_ANSI(2504, __FILE__, __LINE__,
                        "destination %x linkset:linkcode %x:%x",
                         dpc,linkSet,linkCode);

        /* can't recover, can't continue */
        return (ITS_EPROTERR);
    }

    dest = ROUTE_SelectRouteContextInfo(&rinfo);
    /*
     * NOTE: at this point, rinfo.sls has the rotated SLS bits.
     * Also, rinfo.rkey has the index of the routing entry used.
     */
    //MTP3_ERROR(("\n TestControlMessage Rinfo SLS =%d",rinfo.sls));
    //MTP3_RL_SET_SLS(mtp3->label, rinfo.sls);/* sandeep jeevan as we dont store sls in rinfo*/
      MTP3_RL_SET_SLS(mtp3->label, linkCode);

    /* DPC accessible? SDL doesn't have this, but it makes sense. */
    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        MTP3_Alarm_ANSI(2416, __FILE__, __LINE__, "dpc %x ni %x",dpc,ni);

        MTP3_Alarm_ANSI(2504, __FILE__, __LINE__,
                        "destination %x linkset:linkcode %x:%x",
                         dpc,linkSet,linkCode);

        return (ITS_SUCCESS);
    }

    /*
     * select a link == SLC.  As long as the initiator gives the right
     * link code, this is ok.
     */
    return HMCG_Main_ANSI(MTP3_SMH_HMRT,
                          SMH_TRIGGER_L3_L2_MSG,
                          sif, len,
                          linkSet, linkCode,
                          rinfo.rkey);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static void
ResetLinkMap(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;

    ls = LINKSET_FindLinkSet(linkSet);
    if (ls == NULL)
    {
        MTP3_WARNING(("Can't find linkSet to adjust\n"));

        return;
    }

    /* move SLS codes away */
    LINKSET_RemoveActiveLink(ls, linkCode);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static void
SetCurrentRoute(ITS_OCTET *sif, ITS_USHORT len, ITS_OCTET linkSet)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    ROUTE_MatchInfo rinfo;
    ITS_UINT pc;
    ITS_OCTET ni;

    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    /* get the match info */
    if (ROUTE_ParseRouteMatchInfoArgs(&rinfo, pc,
                                      REMOTE_ROUTE, ROUTE_DPC_NI,
                                      FAMILY_ANSI,
                                      ni,
                                      linkSet,
                                      ITS_SS7_DEFAULT_LINK_CODE,
                                      ITS_SS7_DEFAULT_LINK_PRI,
                                      ITS_SS7_DEFAULT_SLS) != ITS_SUCCESS)
    {
        /* give up. */
        return;
    }

    ROUTE_SetCurrentRoute(&rinfo);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
HMRT_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    MTP3_TRACE_ENTRY_ANSI(MTP3_SMH_HMRT, src, trigger, sif, len,
                          linkSet, linkCode);

    /* 
     * set this Bool to false;
     * should be set to true only if Message is for Routing.
     */ 
     TRIGGER_FOR_ROUTING = ITS_FALSE;

    /* HMRT */
    switch (trigger)
    {
    case SMH_TRIGGER_UPDATE_ROUTING_TABLES:
        ITS_C_ASSERT(src == MTP3_STM_TCOC ||
                     src == MTP3_STM_TCBC ||
                     src == MTP3_STM_TFRC ||
                     src == MTP3_STM_TCRC);
        if (src == MTP3_STM_TCOC)
        {
            /*
             * if src is TCOC, recalculate SLS/SLC map, removing
             * the indicated link.
             */
            ResetLinkMap(linkSet, linkCode);
        }
        else if (src == MTP3_STM_TCBC)
        {
            /*
             * if src is TCBC, recalculate SLS/SLC map, adding
             * the indicated link.
             *
             * This is a NOOP now.  The changeback code has to
             * be smarter than this.
             */
        }
        else if (src == MTP3_STM_TFRC)
        {
            /*
             * if src is TFRC, change the current route to the
             * newly indicated one.
             */
            SetCurrentRoute(sif, len, linkSet);
        }
        else if (src == MTP3_STM_TCRC)
        {
            /*
             * if src is TCRC, change the current route back to
             * the indicated one.
             */
            SetCurrentRoute(sif, len, linkSet);
        }
        break;

    case SMH_TRIGGER_MSG_FOR_ROUTING:
        ITS_C_ASSERT(src == MTP3_SMH_HMDC ||
                     src == MTP3_SMH_HMDT);
        /* fix for bug 162 */
        TRIGGER_FOR_ROUTING = ITS_TRUE;
        return MessageForRouting(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_L4_L3_MSG:
        ITS_C_ASSERT(src == MTP3_L4);
        return MessageForRouting(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_ROUTE_MGMT_MSG:
        ITS_C_ASSERT(src >= MTP3_SRM_RTPC &&
                     src <= MTP3_SRM_RTRC);
        return MessageForRouting(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_LINK_MGMT_MSG:
        ITS_C_ASSERT(src >= MTP3_SLM_LLSC &&
                     src <= MTP3_SLM_LSDA);
        return LinkManagementMessage(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_TRAFFIC_MGMT_MSG:
        ITS_C_ASSERT(src >= MTP3_STM_TLAC &&
                     src <= MTP3_STM_TPRC);
        return TrafficManagementMessage(sif, len, linkSet, linkCode);

    case SMH_TRIGGER_TEST_CONTROL_MSG:
        return TestControlMessage(sif, len, linkSet, linkCode);

    default:
        MTP3_DEBUG(("Unknown trigger: src %d trigger %d\n", src, trigger));
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        break;
    }

    /* NOTREACHED */
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static ITS_BOOLEAN
ShouldDiscard(ITS_OCTET congLevel, ITS_OCTET pri)
{
    /*
     * discard if message is at priority lower that one less than the
     * the current congestion level.  IMPLEMENTATION CHOICE.
     */
    if ((congLevel - pri) > 1)
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static ITS_BOOLEAN
DangerOfCongestion(MTP3_HEADER_ANSI *mtp3, ITS_OCTET pri)
{
    /*
     * implementation dependent
     */
    return (ITS_FALSE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
static ITS_BOOLEAN
TransmitBufferFull()
{
    /*
     * implementation choice.  We never say this.
     */
    return (ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference           Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005    Bug ID:1731        CTF Issue.
 *
 ****************************************************************************/
int
HMCG_Main_ANSI(MTP3_SubSystems src, SMH_Triggers trigger,
               ITS_OCTET *sif, ITS_USHORT len,
               ITS_OCTET linkSet, ITS_OCTET linkCode,
               ITS_UINT whichEntry)
{
    MTP3_HEADER_ANSI *mtp3 = (MTP3_HEADER_ANSI *)&sif[1];
    SS7_Destination *rc;
    ITS_UINT dpc;
    ITS_OCTET pri, ni;
    int ret;

    MTP3_TRACE_ENTRY_ANSI(MTP3_SMH_HMCG, src, trigger, sif, len,
                          linkSet, linkCode);

    pri = MTP3_HDR_GET_SIO(*mtp3) & MTP3_MPC_MASK;
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;

    if ((rc = ROUTE_FindDestination(dpc, ni, FAMILY_ANSI)) == NULL)
    {
        MTP3_DEBUG(("FindDestination failed, return.\n"));

        MTP3_Alarm_ANSI(2419, __FILE__, __LINE__, "dpc %x ni %x",dpc,ni);

        return (ITS_SS7_DEFAULT_LINK_SET);
    }

    /*
     * we found the destination so we can see if we should queue or
     * go ahead and send.
     */
    if (rc->entries[whichEntry]->qPut)
    {
        ITS_EVENT ev;

        /*
         * we have to queue.  SLS rotation has already been performed,
         * so put it in L2 format to help us remember that.
         */
        ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, len + 3 * sizeof(ITS_OCTET));

        L2_MSG_TYPE(&ev) = L3_L2_DATA;
        L2_LINK_SET(&ev) = linkSet;
        L2_LINK_CODE(&ev) = linkCode;

        if (len)
        {
            memcpy(L2_LINK_DATA(&ev), sif, len);
        }

        return DSMQUEUE_Enqueue(rc->entries[whichEntry]->crBuf, ev);
    }

    /* is pri < congestion status */
    if (pri < rc->entries[whichEntry]->congLevel)
    {
        RTCC_Main_ANSI(MTP3_SMH_HMCG,
                       SRM_TRIGGER_SEND_TRANSFER_CONTROL,
                       sif, len,
                       linkSet, linkCode);

        /* is pri < discard status */
        if (ShouldDiscard(rc->entries[whichEntry]->congLevel, pri))
        {
            return (ITS_ENOMSG);
        }

        /* transmit buffer full */
        if (TransmitBufferFull(linkSet, linkCode))
        {
            return (ITS_ENOMSG);
        }

        ret = MTP2_SendData_ANSI(linkSet, linkCode,
                                 L3_L2_DATA, sif, len);

        return (ret);
    }
    else if (DangerOfCongestion(mtp3, pri))
    {
        TSRC_Main_ANSI(MTP3_SMH_HMDC,
                       STM_TRIGGER_DANGER_OF_CONGESTION,
                       sif, len,
                       linkSet, linkCode);
    }

    ret = MTP2_SendData_ANSI(linkSet, linkCode,
                             L3_L2_DATA, sif, len);

    return (ret);
}

/*
 * debugging.
 */
static char *toL2[] =
{
    "START",
    "STOP",
    "RESUME",
    "CLEAR_BUFFERS",
    "CLEAR_RTB",
    "EMERGENCY",
    "EMERGENCY_CEASE",
    "DATA",
    "RETRIEVE_BSNT",
    "RETRIEVE_MSGS",
    "FLOW_CONTROL_START",
    "FLOW_CONTROL_STOP",
    "LPO",
    "LPR"
};

static char *toL1[] =
{
    "CONNECT",
    "DISCONNECT"
};

#define MUST_PASS(x) \
    (((x)[1] & MTP3_SIO_UP_MASK) <= MTP3_SIO_SLTM_SPEC)

/*
 * These bits indicate the level messages are being directed
 * to.
 */
#define L2_BITS 0x80
#define L1_BITS 0x90

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference              Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005    Bug ID:1731            CTF Issue.
 *
 ****************************************************************************/
int
MTP2_SendData_ANSI(ITS_OCTET linkSet, ITS_OCTET linkCode,
                   ITS_OCTET command,
                   ITS_OCTET *data, ITS_USHORT len)
{
    SS7_LinkPtr ln;
    ITS_EVENT ev;
    ITS_USHORT idx;
    char *cmd;
    ITS_UINT count;
    ITS_CHAR* buff;
    ITS_CHAR TempBuffer[10];


    if ((command & L1_BITS) == L1_BITS)
    {
        cmd = toL1[command - L1_BITS];
    }
    else if (command & L2_BITS)
    {
        cmd = toL2[command - L2_BITS];
    }
    else
    {
        cmd = "UNKNOWN";
    }

    if (command != L3_L2_DATA)
    {
        MTP3_DEBUG(("MTP2Send: command %s linkSet/Code: %d:%d\n",
                    cmd, linkSet, linkCode));

        if (data && len > 0)
        {
            for (idx = 0; idx < len; idx++)
            {
                TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
                          ("%02x ", data[idx]));

                if (!((idx+1) % 25))
                {
                    TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG,
                              ("\n"));
                }
            }
            if ((idx+1) % 25)
            {
                TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG, ("\n"));
            }
        }
        else
        {
            TRACE_RAW(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG, ("  NO DATA\n"));
        }
    }

    if ((ln = LINK_FindLinkNoLock(linkSet, linkCode)) == NULL)
    {
        MTP3_ERROR(("Can't find link to send to\n"));

        MTP3_Alarm_ANSI(2420, __FILE__, __LINE__, "The Link is %x:%x",
                         linkSet, linkCode);

        return (ITS_EINVALIDARGS);
    }

    /*
     * break into L2 format here
     */
    ITS_EVENT_INIT(&ev, ITS_MTP3_SRC, len + 3 * sizeof(ITS_OCTET));

    L2_MSG_TYPE(&ev) = command;
    L2_LINK_SET(&ev) = linkSet;
    L2_LINK_CODE(&ev) = linkCode;
    if (len)
    {
        memcpy(L2_LINK_DATA(&ev), data, len);
    }

    if (TRACE_IsLevelOn(MTP3_ANSI_TraceData, MTP3_TRACE_EVENT))
    {
        ITS_UINT gmask = 0;
        ITS_USHORT src = ITS_SCCP_ANSI_SRC;
        ITS_INT output = 0;
        
        if(TRACE_IsOutputOn(MTP3_ANSI_TraceData,
            MTP3_TRACE_EVENT,
            0))
        {
            output += 1;
        }
        if(TRACE_IsOutputOn(MTP3_ANSI_TraceData,
            MTP3_TRACE_EVENT,
            1))
        {
            output += 2;
        }
        
        gmask = ENGINE_APP_GS_MASK(application);
        
        if ((gmask & ITS_TCAP_ANSI) == ITS_TCAP_ANSI)
        {
            src = ITS_SCCP_ANSI_SRC;
        }
        else if ((gmask & ITS_TCAP_CCITT) == ITS_TCAP_CCITT)
        {
            src = ITS_SCCP_CCITT_SRC;
        }
        
        CTF_TraceEvent(src, ITS_MTP3_CCITT_SRC,
            output, &ev);
    }

    if (command == L3_L2_DATA)
    {
        if (TRACE_IsLevelOn(MTP3_ANSI_TraceData, MTP3_TRACE_DEBUG))
        {
             buff = (ITS_OCTET*)calloc(ev.len * 5 + 1 + ev.len/15,
                                       sizeof(ITS_OCTET));

             strcpy(buff, "");

             for (count = 1; count <= ev.len; count++)
             {
                 sprintf(TempBuffer, "0x%02x ", ev.data[count - 1]);
                 strcat(buff,TempBuffer);

                 if ((count % 15) == 0)
                 {
                     strcat(buff,"\n");
                 }
              }
              printf("\n\nData sent to MTP2:  \n\n%s\n\n",buff);
              free(buff);
        }

        if (!MUST_PASS(data) && ln->qPut)
        {
            int ret;
            MTP3_EventRec evRec;

            evRec.seqNo = ln->linkSet->seqNum++;
            evRec.event = ev;

            ret = DSMQUEUE_Enqueue(ln->cocbBuf, 
                                    MTP3EventRecToItsEvent_ANSI(evRec));

            ITS_EVENT_TERM(&evRec.event);           

            return ret;
        }

        return TRANSPORT_PutEvent(ln->id, &ev);
    }
    else
    {
        int ret;
/*****ANSI REDUNDANCY CHANGES STARTS HERE ********/
         MTP3_ERROR(("ln->id =%d.ln->isUp =%d \n",ln->id,ln->isUp));
         if(ln->id == 20002)
         {
           if(ln->isUp ==-1 || ln->isUp == 0)
           {
             MTP3_DEBUG(("Internode ln->id DOWN \n"));
             ITS_EVENT fail;
            if (command == L3_L2_RETRIEVE_BSNT)
            {
             MTP3_DEBUG(("Artifical L2_L3_BSNT_NOT_RETRIEVABLE -> In Response to _L3_L2_RETRIEVE_BSNT MSG \n"));
                /* generate artificial event back to MTP3 saying we can't get
                 * it. */
                ITS_EVENT_INIT(&fail,ITS_MTP2_SRC, 3 * sizeof(ITS_OCTET));

                fail.data[0] = L2_L3_BSNT_NOT_RETRIEVABLE;
                fail.data[1] = linkSet;
                fail.data[2] = linkCode;
               if(PEER_MTP3_NODE_STATUS == 0)
                 {
                   ret = TRANSPORT_PutEvent(ln->id, &ev);
                   return ITS_SUCCESS; 
                 }
               else if(PEER_MTP3_NODE_STATUS == 1)
                 {
                   ret = TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &fail);
                   return ITS_SUCCESS; 
                 }
  
            }
            else if (command == L3_L2_RETRIEVE_MSGS)
            {
             MTP3_DEBUG(("Artifical L2_L3_RETRIEVAL_NOT_POSSIBLE -> In Response to L3_L2_RETRIEVE_MSG \n"));
                /* generate artificial event back to MTP3 */
                ITS_EVENT_INIT(&fail, ITS_MTP2_SRC, 3 * sizeof(ITS_OCTET));

                fail.data[0] = L2_L3_RETRIEVAL_NOT_POSSIBLE;
                fail.data[1] = linkSet;
                fail.data[2] = linkCode;
               if(PEER_MTP3_NODE_STATUS == 0)
                 {
                   ret = TRANSPORT_PutEvent(ln->id, &ev);
                   return ITS_SUCCESS; 
                 }
               else if(PEER_MTP3_NODE_STATUS == 1)
                 {
                   ret = TRANSPORT_PutEvent(ITS_MTP3_ANSI_SRC, &fail);
                   return ITS_SUCCESS; 
                 }

            }
           } 
         }
          
          ret = TRANSPORT_PutEvent(ln->id, &ev);
/*****ANSI REDUNDANCY CHANGES ENDS HERE ********/

        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT fail;

            if (command == L3_L2_RETRIEVE_BSNT)
            {
                /* generate artificial event back to MTP3 saying we can't get
                 * it. */
                ITS_EVENT_INIT(&fail, ln->id, 3 * sizeof(ITS_OCTET));

                fail.data[0] = L2_L3_BSNT_NOT_RETRIEVABLE;
                fail.data[1] = linkSet;
                fail.data[2] = linkCode;

                TRANSPORT_PutEvent(ITS_MTP3_SRC, &fail);
            }
            else if (command == L3_L2_RETRIEVE_MSGS)
            {
                /* generate artificial event back to MTP3 */
                ITS_EVENT_INIT(&fail, ln->id, 3 * sizeof(ITS_OCTET));

                fail.data[0] = L2_L3_RETRIEVAL_NOT_POSSIBLE;
                fail.data[1] = linkSet;
                fail.data[2] = linkCode;

                TRANSPORT_PutEvent(ITS_MTP3_SRC, &fail);
            }
        }

        return (ret);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005    Bug ID:1731               CTF Issue.
 *
 ****************************************************************************/
int
MTP2_ReceiveData_ANSI(ITS_EVENT *ev,
                      ITS_OCTET *linkSet, ITS_OCTET *linkCode,
                      ITS_OCTET *data, ITS_USHORT *len)
{
    ITS_C_ASSERT(ev->len >= (3 * sizeof(ITS_OCTET)));

    *len = ev->len - (2 * sizeof(ITS_OCTET));

    *linkSet = L2_LINK_SET(ev);
    *linkCode = L2_LINK_CODE(ev);
    *data = L2_MSG_TYPE(ev);

    if (len)
    {
        memcpy(&data[1], L2_LINK_DATA(ev), *len);
    }

    if (TRACE_IsLevelOn(MTP3_ANSI_TraceData, MTP3_TRACE_EVENT))
    {
        ITS_INT output = 0;
        if(TRACE_IsOutputOn(MTP3_ANSI_TraceData,
            MTP3_TRACE_EVENT,
            0))
        {
            output += 1;
        }
        if(TRACE_IsOutputOn(MTP3_ANSI_TraceData,
            MTP3_TRACE_EVENT,
            1))
        {
            output += 2;
        }
        CTF_TraceEvent(ev->src, ITS_MTP3_ANSI_SRC,
            output, ev);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
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
MTP3_INodeEvent_ANSI(TPOOL_THREAD *thr, ITS_EVENT *ev)
{

    switch (L2_MSG_TYPE(ev))
    {
    case L3_L2_START:
    case L3_L2_STOP:
    case L3_L2_RESUME:
    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
    case L3_L2_EMERGENCY:
    case L3_L2_EMERGENCY_CEASE:
    case L3_L2_DATA:
    case L3_L2_RETRIEVE_BSNT:
    case L3_L2_RETRIEVE_MSGS:
    case L3_L2_FLOW_CONTROL_START:
    case L3_L2_FLOW_CONTROL_STOP:
    case L3_L2_LOCAL_PROCESSOR_OUT:
    case L3_L2_LOCAL_PROCESSOR_REC:
    {
        char *cmd;
        ITS_OCTET command = L2_MSG_TYPE(ev);

        if ((command & L1_BITS) == L1_BITS)
        {
            cmd = toL1[command - L1_BITS];
        }
        else if (command & L2_BITS)
        {
            cmd = toL2[command - L2_BITS];
        }
        else
        {
            cmd = "UNKNOWN";
        }

        MTP3_DEBUG(("MTP3_INodeEvent: Receive Inter-Node Event for local MTP2:"
                    "\ncommand= %s linkSet= %d linkCode= %d\n", cmd,
                     L2_LINK_SET(ev),  L2_LINK_CODE(ev) ));

        MTP2_SendData_ANSI(L2_LINK_SET(ev),
                           L2_LINK_CODE(ev),
                           L2_MSG_TYPE(ev),
                           L2_LINK_DATA(ev),
                           (ITS_USHORT)(ev->len -
                           3 * sizeof(ITS_OCTET)));
        break;
    }
    case MTP3_MSG_USER_DATA:
    {
        /*This event is comming from backup node*/
        ITS_USHORT dest =0;

        dest = MTP3_UserPartOwner_ANSI((ITS_OCTET)(ev->src & MTP3_SIO_UP_MASK));
        if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
        {
            ev->src = ITS_MTP3_SRC;
            TRANSPORT_PutEvent(dest, ev);
        }
        return !ITS_SUCCESS;
    }        
    default:
        PEG_IncrPeg(ANSI_MTP3_Pegs,PEG_MTP3_MSG_RECEIVED_INERROR);
        /* unknown command to L2 */
        break;
    }

    return ITS_SUCCESS;
}

