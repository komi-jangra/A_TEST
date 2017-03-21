/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 2001,2002 IntelliNet Technologies, Inc.            *
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
 *  ID: $Id: ansi-timers.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:52  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:53:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1.6.1.12.1  2004/12/06 13:34:50  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.2.2.1.6.1  2004/01/05 10:10:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.2.2.1.2.1  2003/11/24 06:36:29  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 10:38:00  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.2  2003/04/03 15:24:34  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/10 19:32:12  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/06 06:09:59  hbalimid
 * LOG: Tookcare of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/05 22:01:24  hbalimid
 * LOG: ANSI CVT states and timers implemented.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/01 20:17:50  hbalimid
 * LOG: Baseline for ISUP ANSI GENERIC 92.
 * LOG:
 * LOG: Revision 1.1  2002/06/10 14:55:36  sjaddu
 * LOG: Added first draft of file for ANSI ISUP.
 * LOG:
 *
 *****************************************************************************/

#undef CCITT
#undef ANSI
#define ANSI

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <isup_intern.h>
#include <ansi/isup_92.h>

/*
 * Functions for handling ISUP timers
 */

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start BLO timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartBLOTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Start Timer T13 only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T13))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T13, 
                    config_info->tmr_hndl_info[ITS_ISUP_TIMER_T13].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("BLO Timers: Failed to start T13. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT13++;
    }
    
    /* Figure out if T12 needs to be restarted */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T12))
    {
        max_restarts = 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T13].tmr_value /
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T12].tmr_value;

        if (cic_rec->cntT12 < (ITS_OCTET)max_restarts)
        {
            /* Start Timer T12 */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T12, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T12].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("BLO Timers: Failed to start T12. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                return ret;
            }
            cic_rec->cntT12++;
        }
    }

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Stop BLO timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StopBLOTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Stop timers T13, T12. */
    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T13);
    cic_rec->cntT13 = 0;

    if (ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T12))
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T12);
        cic_rec->cntT12 = 0;
    }
    else
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("BLO short timer not running, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
    }

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Check and start BLO repeat timer
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartBLORepeatTimer(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Figure out if T12 needs to be restarted */
    max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T13].tmr_value /
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T12].tmr_value;

    if (cic_rec->cntT12 < (ITS_OCTET)max_restarts)
    {
        /* Start Timer T12 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T12, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T12].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("BLO Repeat Timer: Failed to start T12. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT12++;
    }
    else
    {
        return ITS_ISUP_TIMER_DONE;
    }
    
    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start REL timers
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartRELTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Figure out if T1 needs to be restarted */
    max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T5].tmr_value /
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T1].tmr_value;

    if (cic_rec->cntT1 < (ITS_OCTET)max_restarts)
    {
        /* Start Timer T1 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T1, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T1].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("REL Timers: Failed to start T1. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT1++;
    }
    /* Start Timer T5 only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T5))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T5, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T5].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("REL Timers: Failed to start T5. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
    }
    
    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Stop REL timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StopRELTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    
    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T1);
    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T5);
    cic_rec->cntT1 = 0;

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start UBL timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartUBLTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Start Timer T15 only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T15))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T15,
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T15].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("UBL Timers: Failed to start T15. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT15++;
    }  
    
    /* Figure out if T14 needs to be restarted */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T14))
    {
        max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T15].tmr_value /
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T14].tmr_value;

        if (cic_rec->cntT14 < (ITS_OCTET)max_restarts)
        {
            /* Start Timer T14 */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T14, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T14].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("UBL Timers: Failed to start T14. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                return ret;
            }
            cic_rec->cntT14++;
        }
    }

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Stop UBL timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StopUBLTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Stop timers T15, T14. */
    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T15);
    cic_rec->cntT15 = 0;

    if (ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T14))
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T14);
        cic_rec->cntT14 = 0;
    }
    else
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("UBL short timer not running, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
    }

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Check and start UBL repeat timer
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartUBLRepeatTimer(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Figure out if T14 needs to be restarted */
    max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T15].tmr_value /
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T14].tmr_value;

    if (cic_rec->cntT14 < (ITS_OCTET)max_restarts)
    {
        /* Start Timer T14 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T14, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T14].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("UBL Repeat Timer: Failed to start T14. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT14++;
    }
    else
    {
        return ITS_ISUP_TIMER_DONE;
    }
    
    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start RSC timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartRSCTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;
    
    /* Figure out if T16 needs to be restarted */
    if ((cic_rec->reset_flag != RESET_AFTER_T5) &&
            !ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T16))
    {
        max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T17].tmr_value /
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T16].tmr_value;

        if (cic_rec->cntT16 < (ITS_OCTET)max_restarts)
        {
            /* Start Timer T16 */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T16, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T16].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("RSC Timers: Failed to start T16. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                return ret;
            }
            cic_rec->cntT16++;
           
            /* Start Repeat RSC timer Also, TCS req */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T98,
                                    config_info->repeat_rsc_timerval);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("RSC Timers: Failed to start T98. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                return ret;
            }
        }
    }

    /* Start Timer T17 only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T17))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T17, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T17].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("RSC Timers: Failed to start T17. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT17++;
    }
    
    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Stop RSC timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StopRSCTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Stop timers T16, T17. */
    if (ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T16))
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T16);
        cic_rec->cntT16 = 0;
    }
    else
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("RSC short timer not running, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
    }

    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T17);
    cic_rec->cntT17 = 0;

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Check and start BLO repeat timer
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartRSCRepeatTimer(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Figure out if T16 needs to be restarted */
    max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T17].tmr_value /
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T16].tmr_value;

    if (cic_rec->cntT16 < (ITS_OCTET)max_restarts)
    {
        /* Start Timer T16 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T16, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T16].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("RSC Repeat Timer: Failed to start T16. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT16++;
    }
    else
    {
        return ITS_ISUP_TIMER_DONE;
    }
    
    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start CGB timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartCGBTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;
    
    /* Figure out if T18 needs to be restarted */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T18))
    {
        max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T19].tmr_value /
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T18].tmr_value;

        if (cic_rec->cntT18 < (ITS_OCTET)max_restarts)
        {
            /* Start Timer T18 */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T18, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T18].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("CGB Timers: Failed to start T18. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                return ret;
            }
            cic_rec->cntT18++;
        }
    }
    
    /* Start Timer T19 only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T19))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T19, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T19].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("CGB Timers: Failed to start T19. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT19++;
    }    

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Stop CGB timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StopCGBTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Stop timers T18, T19. */
    if (ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T18))
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T18);
        cic_rec->cntT18 = 0;
    }
    else
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("CGB short timer not running, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
    }

    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T19);
    cic_rec->cntT19 = 0;

    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Check and start CGB repeat timer
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartCGBRepeatTimer(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Figure out if T18 needs to be restarted */
    max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T19].tmr_value /
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T18].tmr_value;

    if (cic_rec->cntT18 < (ITS_OCTET)max_restarts)
    {
        /* Start Timer T18 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T18, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T18].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("CGB Repeat Timer: Failed to start T18. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT18++;
    }
    else
    {
        return ITS_ISUP_TIMER_DONE;
    }
    
    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start CGU timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartCGUTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;
    
    /* Figure out if T20 needs to be restarted */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T20))
    {
        max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T21].tmr_value /
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T20].tmr_value;

        if (cic_rec->cntT20 < (ITS_OCTET)max_restarts)
        {
            /* Start Timer T20 */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T20, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T20].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("CGU Timers: Failed to start T20. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                return ret;
            }
            cic_rec->cntT20++;
        }    
    }
    
    /* Start Timer T21 only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T21))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T21, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T21].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("CGU Timers: Failed to start T21. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT21++;
    }
    
    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Stop CGU timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StopCGUTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Stop timers T20, T21. */
    if (ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T20))
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T20);
        cic_rec->cntT20 = 0;
    }
    else
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("CGU short timer not running, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
    }

    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T21);
    cic_rec->cntT21 = 0;

    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Check and start CGU repeat timer
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartCGURepeatTimer(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Figure out if T20 needs to be restarted */
    max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T21].tmr_value /
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T20].tmr_value;

    if (cic_rec->cntT20 < (ITS_OCTET)max_restarts)
    {
        /* Start Timer T20 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T20, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T20].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("CGU Repeat Timer: Failed to start T20. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT20++;
    }
    else
    {
        return ITS_ISUP_TIMER_DONE;
    }
    
    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start GRS timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartGRSTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Start Timer T23 only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T23))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T23,
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T23].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("GRS Timers: Failed to start T23. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT23++;
    }

    /* Figure out if T22 needs to be restarted */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T22))
    {
        max_restarts = 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_T23].tmr_value /
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T22].tmr_value;

        if (cic_rec->cntT22 < (ITS_OCTET)max_restarts)
        {
            /* Start Timer T22 */
            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T22, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T22].tmr_value);
            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("GRS Timers: Failed to start T22. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
                return ret;
            }
            cic_rec->cntT22++;
        }
    }

    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Stop GRS timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StopGRSTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Stop timers T22, T23. */
    if (ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_T22))
    {
        __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T22);
        cic_rec->cntT22 = 0;
    }
    else
    {
        /* Maintenance system ind */
        ISUP_CRITICAL(("GRS short timer not running, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic)); 
    }

    __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T23);
    cic_rec->cntT23 = 0;

    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Check and start GRS repeat timer
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartGRSRepeatTimer(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT max_restarts;
    int ret = ITS_SUCCESS;

    /* Figure out if T22 needs to be restarted */
    max_restarts = config_info->tmr_hndl_info[ITS_ISUP_TIMER_T23].tmr_value /
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T22].tmr_value;

    if (cic_rec->cntT22 < (ITS_OCTET)max_restarts)
    {
        /* Start Timer T22 */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T22, 
                config_info->tmr_hndl_info[ITS_ISUP_TIMER_T22].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("GRS Repeat Timer: Failed to start T22. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntT22++;
    }
    else
    {
        return ITS_ISUP_TIMER_DONE;
    }
    
    return ret;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Start CVT timers
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartCVTTimers(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Start Timer TCVT only if not already started */
    if (!ISUP_PndgTmrExists(cic_rec, ITS_ISUP_TIMER_TCVT))
    {
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCVT, 
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_TCVT].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("CVT Timers: Failed to start TCVT. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntTCVT++;
    }

    return ret;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      Check and start CVT repeat timer
 *
 *  Input Parameters:
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartCVTRepeatTimer(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;

    /* Figure out if TCVT needs to be restarted */

    if (cic_rec->cntTCVT < (ITS_OCTET)CVT_TIMER_MAX_RESTARTS)
    {
        /* Start Timer CVT */
        ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TCVT,
            config_info->tmr_hndl_info[ITS_ISUP_TIMER_TCVT].tmr_value);
        if (ret != ITS_SUCCESS)
        {
            ISUP_ERROR(("CVT Repeat Timer: Failed to start TCVT. pcic 0x%08x,"
                        " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            return ret;
        }
        cic_rec->cntTCVT++;
    }
    else
    {
        return ITS_ISUP_TIMER_DONE;
    }
    
    return ret;
}
