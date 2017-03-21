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
 *  ID: $Id: bssap_dbc.cpp,v 1.4 2008-02-25 01:42:37 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.3  2008/01/14 05:39:15  bsccs2
 * LOG: Block the Bssap  timer response
 * LOG:
 * LOG: Revision 1.2  2007/12/27 13:40:40  bsccs2
 * LOG: Modify the  cic  addition command  , Add the start Ts  and  End  Ts
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.4  2006/10/07 12:35:00  sjaddu
 * LOG: Added IMSI_Detach procedure.
 * LOG:
 * LOG: Revision 1.1.2.3  2005/12/05 09:17:05  mkrishna
 * LOG: Added pegs implementation
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/06 08:24:14  adutta
 * LOG: Added basic mmls
 * LOG:
 ****************************************************************************/

#include <bssap_cicdb.h>
#include <bssap_call.h>
#include <bssap_cfgdb.h>
#include <bssap_timer.h>
#include <bssap_dbc.h>
#include <bssap_pegs.h>

#define ALPHABET  "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
#define SPECIAL_CHAR  "#\\`~!@$%^&*()-_+=|^?{}[]:;'<>,.?/"

ITS_UINT BSSAP_AlarmLevel = ALARM_LVL_OFF;

extern ITS_OCTET TIMER_Tries[];

/*implementation:internal
*
* PURPOSE:
*       Set general config info for stack
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0030, ID :: D0180
*/
void
BSSAP_ShowAllPegs(DBC_Server* dbc)
{
    ITS_CHAR buf[ITS_PATH_MAX];
    ITS_UINT count = 0;
                                                                                                                                              
    DBC_AppendText(dbc, "\n");
                                                                                                                                              
    for (ITS_INT i = 0; i < PEG_BSSAP_LAST_COUNT; i++)
    {
        memset(buf, 0, ITS_PATH_MAX);
                                                                                                                                              
        count = PEG_GetPeg(BSSAP_Pegs, i);
        sprintf(buf, "%s   %d\n", PEG_STR(i), count);
                                                                                                                                              
        DBC_AppendText(dbc, buf);
    }
                                                                                                                                              
}

/*implementation:internal
*
* PURPOSE:
*       Set general config info for stack
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0030, ID :: D0180
*/
void
BSSAP_ClearAllPegs(DBC_Server* dbc)
{
    ITS_CHAR buf[ITS_PATH_MAX];
                                                                                                                                              
    memset(buf, 0, ITS_PATH_MAX);
                                                                                                                                              
    PEG_ClearBlock(BSSAP_Pegs);
                                                                                                                                              
    sprintf(buf, "Clearing all BSSAP pegs\n");
    DBC_AppendText(dbc, buf);
}

/*implementation:internal
*
* PURPOSE:
*       Set general config info for stack  
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0030, ID :: D0180
*/
int
BSSAP_SetGeneralCfg(BSSAPGeneralCfg *data)
{
    BSSAP_AlarmLevel = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    { 
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                      BSSAP_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                      BSSAP_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                      BSSAP_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                      BSSAP_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       BSSAP_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
        }
    }

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       Get general config info  
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0030, ID :: D0180
*/
BSSAPGeneralCfg*
BSSAP_GetGeneralCfg()
{
    BSSAPGeneralCfg *ret;

    ret = (BSSAPGeneralCfg *)calloc(1, sizeof(BSSAPGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(BSSAP_TraceData,
                                    BSSAP_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(BSSAP_TraceData,
                                    BSSAP_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(BSSAP_TraceData,
                                    BSSAP_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_ERROR,
                                      2))) ||
                   (TRACE_IsLevelOn(BSSAP_TraceData,
                                    BSSAP_TRACE_CRITICAL) &&
                    (TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_CRITICAL,
                                      0) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_CRITICAL,
                                      1) ||
                     TRACE_IsOutputOn(BSSAP_TraceData,
                                      BSSAP_TRACE_CRITICAL,
                                      2))); 
    ret->alarmLevel = BSSAP_AlarmLevel;

    return (ret);
}

/*implementation:internal
*
* PURPOSE:
*       Display all CIC records from CIC CTXT table 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0050
*/
static ITS_INT 
GetAllCIC(ITS_POINTER entry, void *in, void *out)
{
    CICData* crec = (CICData*)entry;
    DBC_Server* dbc = (DBC_Server*)in;
    ITS_CHAR buf[ITS_PATH_MAX];

    sprintf(buf, "\npcm          : %d", crec->pcm);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\ntime slot    : %d", crec->ts);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\nNetwork Id   : %d\n", crec->nwId);
    DBC_AppendText(dbc, buf);

    if (crec->localState == CIC_ST_BLOCK)
    {
        sprintf(buf, "Local State  : BLOCK\n");
    }
    else
    {
        sprintf(buf, "Local State  : UN-BLOCK\n");
    }
    DBC_AppendText(dbc, buf);

    if (crec->remoteState == CIC_ST_BLOCK)
    {
        sprintf(buf, "Remote State : BLOCK\n");
    }
    else
    {
        sprintf(buf, "Remote State : UN-BLOCK\n");
    }
    DBC_AppendText(dbc, buf);

    if (crec->callState == CALL_ST_IDLE)
    {
        sprintf(buf, "Call State   : IDLE\n");
    }
    else
    {
        sprintf(buf, "Call State   : BUSY\n");
    }
    DBC_AppendText(dbc, buf);

    sprintf(buf, "Timer ID     : %d\n", crec->timerId);

    DBC_AppendText(dbc, buf);

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       Display all config info from table 
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0050
*/
static ITS_INT
GetAllCFG(ITS_POINTER entry, void *in, void *out)
{
    CFGData* crec = (CFGData*)entry;
    DBC_Server* dbc = (DBC_Server*)in;
    ITS_CHAR buf[ITS_PATH_MAX];

    sprintf(buf, "\nNetwork Id   : %d\n", crec->Id);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "Local point code : %d\n", crec->lpc);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "Remote point code : %d\n", crec->rpc);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "Local ssn : %d\n", crec->lssn);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "Remote ssn : %d\n", crec->rssn);
    DBC_AppendText(dbc, buf);

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       Display all call info from table
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0050
*/
ITS_INT
GetAllCDR(ITS_POINTER entry, void *in, void *out)
{
    BSSAP_Call* call = (BSSAP_Call*)entry;
    DBC_Server* dbc = (DBC_Server*)in;
    ITS_CHAR buf[ITS_PATH_MAX];
    ITS_OCTET callType;

    callType = call->GetCallType();

    if (callType == MO_CALL)
    {
        sprintf(buf, "\nCall Type   : MO CALL\n");
    }
    else if (callType == MT_CALL)
    {
        sprintf(buf, "\nCall Type   : MT CALL\n");
    }
    else if (callType == LU_CALL)
    {
        sprintf(buf, "\nCall Type   : LU CALL\n");
    }
    else if (callType == IMSI_DETACH)
    {
        sprintf(buf, "\nCall Type   : IMSI DETACH\n");
    }

    else
    {
        sprintf(buf, "\nCall Type   : HO CALL\n");
    }

    DBC_AppendText(dbc, buf);
    sprintf(buf, "\nSLR         : %d\n", call->GetSLR());
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\nDLR         : %d\n", call->GetDLR());
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\nCIC         : %d\n", call->GetCIC());
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\nNetworkId   : %d\n", call->GetBssId());
    DBC_AppendText(dbc, buf);
    if (call->GetChannelAlloc())
    {
        sprintf(buf, "\nChannel Allocated\n\n");
    }
    else
    {
        sprintf(buf, "\nNo Channel Allocated\n\n");
    }
    DBC_AppendText(dbc, buf);

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       this function is used for MML's  
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
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0030, ID :: D0040,
*                        ID :: D0050
*/
void
BSSAP_ConsoleCommand(DBC_Server* dbc, const ITS_CHAR* cmdLine)
{
    ITS_UINT cic = 0;
    ITS_INT pcm = 0;
    ITS_INT Sts = 0,Fts=0;    
    ITS_INT ts = 0;
    ITS_INT nwId = 0;
    ITS_INT ret = 0;
    ITS_CHAR buf[ITS_PATH_MAX];
    BSSAP_CfgDB cfgdb;
    CFGData* cfg = NULL;
    BSSAP_CicDB cicdb;
    CICData* crec = NULL;

    // CIC MML
    if (DBC_Cmd(dbc, "bs_get_cic_record", "Get single CIC record", "", ""))
    {

        ret = sscanf(cmdLine, "%s %d %d %d", buf, &pcm, &ts, &nwId);
        if (ret != 4)
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "Usage: bs_get_cic_record <pcm> <timeslot> "
                                                           "<network Id>\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        if (pcm < 0 || ts < 0)
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        if (pcm > (0x7FFU) || ts > (0x1FU) || nwId > (0xFFU))
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        cic = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));

        crec = cicdb.FetchCICRecord(cic,0,nwId);
        if (crec)
        {
	           	sprintf(buf, "\npcm   : %d\n", crec->pcm);
           		DBC_AppendText(dbc, buf);
          		sprintf(buf, "\ntimeslot   : %d\n", crec->ts); 
          		DBC_AppendText(dbc, buf); 
              sprintf(buf, "\nNetwork Id   : %d\n", crec->nwId);
              DBC_AppendText(dbc, buf);

            if (crec->localState == CIC_ST_BLOCK)
            {
                sprintf(buf, "Local State : BLOCK\n");
            }
            else
            {
                sprintf(buf, "Local State : UN-BLOCK\n");
            }

            DBC_AppendText(dbc, buf);
            if (crec->remoteState == CIC_ST_BLOCK)
            {
                sprintf(buf, "Remote State : BLOCK\n");
            }
            else
            {
                sprintf(buf, "Remote State : UN-BLOCK\n");
            }
            DBC_AppendText(dbc, buf);
            if (crec->callState == CALL_ST_IDLE)
            {
                sprintf(buf, "Call State   : IDLE\n");
            }
            else
            {
                sprintf(buf, "Call State   : BUSY\n");
            }
            DBC_AppendText(dbc, buf);

            sprintf(buf, "Timer ID     : %d\n", crec->timerId);

            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "\nError: CIC record not found" 
                                     " for pcm <%d>  timeslot <%d>\n", pcm, ts);
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "bs_get_all_cic_record", "Get all CIC record", "", ""))
    {
        DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CIC_CTXT,
                     dbc, NULL, GetAllCIC);

    }
    else if (DBC_Cmd(dbc, "bs_rem_cic_record", "Remove CIC record", "", ""))
    {
         //    ret = sscanf(cmdLine, "%s %d %d %d", buf, &pcm, &ts, &nwId);
        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pcm, &Sts,&Fts, &nwId);
         //if (ret != 4)
        if (ret != 5)
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "Usage: bs_rem_cic_record <pcm> <timeslot> <nwId>\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        // if (pcm < 0 || ts < 0)
        if (pcm < 0 || Sts < 0)
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        if (pcm > (0x7FFU) || Fts > (0x1FU) || nwId > (0xFFU))
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        for(ts = Sts ; ts <= Fts ;ts++)
	      {
             cic = (nwId << 16) | ((pcm << 5) | (0x1FU & ts));
             ret = cicdb.RemoveCICRecord(cic,nwId);
             if (ret !=  ITS_SUCCESS)
             {
                sprintf(buf, "\nFail to remove CIC record pcm <%d>"
                                                  " timeslot <%d>\n", pcm, ts);
	              DBC_AppendText(dbc, buf);  // Addition
                return;                    // Addition
            }
           else
            {
	             sprintf(buf, "\nCIC record removed pcm \n ");
            }
	       }

        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "bs_add_cic_record", "Add CIC record", "", ""))
    {
       //  ret = sscanf(cmdLine, "%s %d %d %d", buf, &pcm, &ts, &nwId);
       ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &pcm, &Sts,&Fts, &nwId);  
       if (ret != 5)
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "\nUsage: bs_add_cic_record <pcm> <timeslot>"
                                                            " <network Id>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (pcm < 0 || Sts < 0)
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (pcm > (0x7FFU) || Fts > (0x1FU) || nwId > (0xFFU))
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = cicdb.AddCIC(nwId, pcm, Sts, Fts);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\nFail to add CIC record pcm <%d>"
                                                   " timeslot<%d>\n", pcm, ts);
        }
        else
        {
            sprintf(buf, "\nCIC rec. added pcm <%d> timeslot <%d>\n", pcm, ts);
        }

        DBC_AppendText(dbc, buf);
    }
    // CFG Record MML
    else if (DBC_Cmd(dbc, "bs_get_cfg_record", "Get single CFG record", "", ""))
    {
        ret = sscanf(cmdLine, "%s %d ", buf, &nwId);
        if (ret != 2)
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "Usage: bs_get_cfg_record <network Id>\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        if (nwId > (0xFFU))
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        cfg = cfgdb.FetchRPCEntry(nwId);
        if (cfg)
        {
            sprintf(buf, "\nNetwork Id   : %d\n", cfg->Id);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "Local point code : %d\n", cfg->lpc);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "Remote point code : %d\n", cfg->rpc);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "Local ssn : %d\n", cfg->lssn);
            DBC_AppendText(dbc, buf);

            sprintf(buf, "Remote ssn : %d\n", cfg->rssn);
            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "\nError: CFG record not found" 
                                     " for networkId <%d>\n", nwId);
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "bs_get_all_cfg_record", "Get all CFG record", "", ""))
    {
        DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_RPC_LIST,
                     dbc, NULL, GetAllCFG);

    }
    else if (DBC_Cmd(dbc, "bs_rem_cfg_record", "Remove CIC record", "", ""))
    {
        ITS_INT rpc = 0;

        ret = sscanf(cmdLine, "%s %d %d", buf, &nwId, &rpc);
        if (ret != 3) 
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "Usage: bs_rem_cfg_record <network Id> <remote pc>\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        if (nwId > (0xFFU))
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);
        
            return;
        }   

        ret = cfgdb.RemoveRPCEntry(nwId);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\nFail to remove CFG record remote pc <%d>\n", rpc);
        }
        else
        {
            sprintf(buf, "\nCFG record removed remote pc <%d>\n", rpc);
        }

        ret = cfgdb.RemoveNWIDEntry(rpc);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\nFail to remove CFG record network Id <%d>\n", nwId);
        }
        else
        {
            sprintf(buf, "\nCFG record removed network Id <%d>\n", nwId);
        }

        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "bs_add_cfg_record", "Add CFG record", "", ""))
    {
        ITS_INT lpc = 0;
        ITS_INT rpc = 0;
        ITS_INT lssn = 0;
        ITS_INT rssn = 0;

        ret = sscanf(cmdLine, "%s %d %d %d %d %d", buf, &nwId, &lpc,
                                                      &rpc, &lssn, &rssn);
        if (ret != 6)
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "\nUsage: bs_add_cfg_record <network Id> "
                            "<local point code> <remote point code> "
                                           "<local ssn> <remote ssn> \n");

            DBC_AppendText(dbc, buf);

            return;
        }

        if (nwId > (0xFFU))
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);
        
            return;
        }   

        if (lpc < 0 || rpc < 0 || lssn < 0 || rssn < 0)
        {
            sprintf(buf, "\nError: Incorrect values\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        if (lssn > 0xFF || rssn > 0xFF)
        {
            sprintf(buf, "\nError: Incorrect values (ssn)\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        ret = cfgdb.AddCfg(nwId, lpc, rpc, lssn, rssn);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "\nFail to add CFG record network Id <%d>\n", nwId);
        }
        else
        {
            sprintf(buf, "\nCFG record added network Id <%d>\n", nwId);
        }

        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "bs_get_call_detail", "Get all CFG record", "", ""))
    {
        DSM_TableIterate(DSM_SccpFtGroupId, DSM_TABLE_BSSAP_CALL_CTXT,
                     dbc, NULL, GetAllCDR);

    }
    else if (DBC_Cmd(dbc, "bs_set_timer", "Set BSSAP stack timers", "", ""))
    {
        ITS_INT tr = 0;
        ITS_INT timerType = 0;
        BSSAP_Timer t;

        ret = sscanf(cmdLine, "%s %d %d", buf, &timerType, &tr);

        if (ret != 3)
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "Usage: bs_set_timer <Timer Id> <Timer valure>");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (tr < 0)
        {
            sprintf(buf, "\nError: Incorrect value\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        switch (timerType)
        {
            case BSSAP_T_1:
            case BSSAP_T_4:
            case BSSAP_T_7:
            case BSSAP_T_8:
            case BSSAP_T_10:
            case BSSAP_T_11:
            case BSSAP_T_13:
            case BSSAP_T_17:
            case BSSAP_T_18:
            case BSSAP_T_19:
            case BSSAP_T_20:
             /* sprintf(buf, "\n%s timer set to %d secs.\n",
                                           t.GetTimerString(timerType), tr);*/
            break;
            default:
                sprintf(buf, "\nError: Wrong timer type\n");
                DBC_AppendText(dbc, buf);
                return;
        } 

        TIMERS_SetTimerValue(&BSSAP_Timers, timerType, tr);
      	buf[0]='\0';
        /*change for SCM requirement */
    	  DBC_AppendText(dbc, buf);
      	return ;
    }
    else if (DBC_Cmd(dbc, "bs_set_timer_tries", "Set BSSAP stack timer tries",
                       "", ""))
    {
        ITS_INT tries = 0;
        ITS_INT timerType = 0;
        BSSAP_Timer t;

        ret = sscanf(cmdLine, "%s %d %d", buf, &timerType, &tries);

        if (ret != 3)
        {
            sprintf(buf, "\nError: Invalid arguments\n");
            sprintf(buf, "Usage: bs_set_timer_tries <Timer Id> <Timer value>");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (tries < 0)
        {
            sprintf(buf, "\nError: Incorrect value\n");
            DBC_AppendText(dbc, buf);

            return;
        }

        switch (timerType)
        {
            case BSSAP_T_1:
            case BSSAP_T_4:
            case BSSAP_T_7:
            case BSSAP_T_8:
            case BSSAP_T_10:
            case BSSAP_T_11:
            case BSSAP_T_13:
            case BSSAP_T_17:
            case BSSAP_T_18:
            case BSSAP_T_19:
            case BSSAP_T_20:
                sprintf(buf, "\n%s timer set to %d tries.\n",
                                           t.GetTimerString(timerType), tries);
            break;
            default:
                sprintf(buf, "\nError: Wrong timer type\n");
                DBC_AppendText(dbc, buf);
                return;
        } 

        TIMER_Tries[timerType] = tries;
        DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "bs_get_all_timer_tries", 
                         "Get all BSSAP stack timer tries", "", ""))
    {
        BSSAP_Timer t; 
        int i;
        for (i = 0; i < 11; i++)
        {
            sprintf(buf, "\n%s timer value set to %d  tries\n",
                               t.GetTimerString(i), TIMER_Tries[i]);
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "bs_get_all_timers", "Get all BSSAP stack timers", "", ""))
    {
        ITS_TIME value;
        BSSAP_Timer t;
        int i;

        for (i = 0; i < 11; i++)
        {
            value = TIMERS_GetTimerValue(&BSSAP_Timers, i); 
            sprintf(buf, "\n%s timer value set to %d  secs\n", 
                               t.GetTimerString(i), value); 
            DBC_AppendText(dbc, buf);
        } 
    }
    else if (DBC_Cmd(dbc, "bs_set_gen_cfg", "BSSAP Set General Config", 
                      "<al> <trType> <trOutput> <on/off>",
                     "<Alarm Level> <Trace Type> <Trace Output> <On / Off>"))

    {
        BSSAPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType, 
                     traceOutput, traceOn);

        if (ret != 5)
        {
            sprintf(buf, "**** Invalid Command Arguments *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL || 
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") || 
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") || 
                 strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") || 
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "Invalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        
        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, BSSAP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, BSSAP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, BSSAP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, BSSAP_ERROR_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, BSSAP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, BSSAP_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, BSSAP_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  BSSAP_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

       sprintf(buf, "*********** BSSAP General Config Set*************\n");
       DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "bs_get_gen_cfg", "BSSAP Get General Config", "", ""))
    {
        ITS_UINT i;
        BSSAPGeneralCfg *cfg;
        cfg =  BSSAP_GetGeneralCfg();

        sprintf(buf, "*********** BSSAP General Config *************\n");
        DBC_AppendText(dbc, buf);

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "    Alarm Level = CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "    Alarm Level = MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "    Alarm Level = MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "    Alarm Level = INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "    Alarm Level = OFF\n");
            break;

            default :
                sprintf(buf, "    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);

        strcpy(buf, "    BSSAP Trace -\n");
        DBC_AppendText(dbc, buf);
        if (cfg->traceOn)
        {
            if (TRACE_IsLevelOn(BSSAP_TraceData,
                                     BSSAP_TRACE_DEBUG))
            {
                strcpy(buf, "        Debug     = ");
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_DEBUG,
                                       0))
                {
                     strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_DEBUG,
                                       1))
                {
                     strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_DEBUG,
                                       2))
                {
                     strcat(buf, " syslog");
                }

            }
            else
            {
                strcpy(buf, "        Debug     = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(BSSAP_TraceData,
                                     BSSAP_TRACE_CRITICAL))
            {
                strcpy(buf, "        Critical  = ");
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_CRITICAL,
                                       0))
                {
                     strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_CRITICAL,
                                       1))
                {
                     strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_CRITICAL,
                                       2))
                {
                     strcat(buf, " syslog");
                }
 
            }
            else
            {
                strcpy(buf, "        Critical  = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);

            if (TRACE_IsLevelOn(BSSAP_TraceData,
                                     BSSAP_TRACE_WARNING))
            {
                strcpy(buf, "        Warning   = ");
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_WARNING,
                                       0))
                {
                     strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_WARNING,
                                       1))
                {
                     strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_WARNING,
                                       2))
                {
                     strcat(buf, " syslog");
                }
            }
            else
            {
                strcpy(buf, "        Warning   = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);
 
            if (TRACE_IsLevelOn(BSSAP_TraceData,
                                     BSSAP_TRACE_ERROR))
            {
                strcpy(buf, "        Error     = ");
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_ERROR,
                                       0))
                {
                     strcat(buf, " stdout");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_ERROR,
                                       1))
                {
                     strcat(buf, " file");
                }
                if (TRACE_IsOutputOn(BSSAP_TraceData,
                                       BSSAP_TRACE_ERROR,
                                       2))
                {
                    strcat(buf, " syslog");
                }
 
            }
            else
            {
                strcpy(buf, "        Error     = null");
            }
            strcat(buf, "\n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            strcpy(buf, "        Debug     = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Critical  = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Warning   = null\n");
            DBC_AppendText(dbc, buf);
            strcpy(buf, "        Error    = null\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "bs_show_all_pegs", "", "", ""))
    {
        BSSAP_ShowAllPegs(dbc);
    }
    else if (DBC_Cmd(dbc, "bs_clear_all_pegs", "", "", ""))
    {
        BSSAP_ClearAllPegs(dbc);
    }
    else if (DBC_Cmd(dbc, "bs_clear_pegs", "", "", ""))
    {
        ITS_INT pgNum = 0;
                                                                                                                                              
        ret = sscanf(cmdLine, "%s %d", buf, &pgNum);
        if (ret != 2)
        {
             sprintf(buf, "\nInvalid Command Arguments\n");
             DBC_AppendText(dbc, buf);
                                                                                                                                              
             return;
        }
                                                                                                                                              
        if (pgNum >= PEG_BSSAP_LAST_COUNT)
        {
            sprintf(buf, "\nInvalid Peg Type\n");
            DBC_AppendText(dbc, buf);
                                                                                                                                              
            return;
        }
                                                                                                                                              
        PEG_ClearPeg(BSSAP_Pegs, pgNum);
                                                                                                                                              
        sprintf(buf, "%s   %d\n", PEG_STR(pgNum),
                                          PEG_GetPeg(BSSAP_Pegs, pgNum));
    }
}

