/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *
 * CONTRACT: INTERNAL
 *
 *  LOG: $Log: not supported by cvs2svn $
 *  LOG: Revision 1.1.1.1  2007/10/04 13:23:51  bsccs2
 *  LOG: init tree
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/08/03 06:48:47  cvsadmin
 *  LOG: BscCs2
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/03/08 15:13:13  cvsadmin
 *  LOG: BSC project
 *  LOG:
 *  LOG: Revision 1.2  2005/05/06 09:36:38  mmanikandan
 *  LOG: PR6.5.1 Validation Bug(1773) Fix.
 *  LOG:
 *  LOG: Revision 1.1  2005/04/06 06:02:40  adutta
 *  LOG: MML feature add as part of Bug#1557
 *  LOG:
 *  LOG:
 *
 ***************************************************************************/
#include <its.h>
#include <its_types.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <dbc_serv.h>
#include <m3ua.h>

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Helper function to set M3UA configuration.
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
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     Addition of debug console feature.
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI ITS_INT
M3UA_SetGeneralCfg(M3UAGeneralCfg* data)
{
    M3UA_AlarmLevel = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      M3UA_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       M3UA_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(M3UA_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(M3UA_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Helper function to get M3UA configuration details.
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
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     Addition of debug console feature.
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI M3UAGeneralCfg*
M3UA_GetGeneralCfg()
{
    M3UAGeneralCfg *ret;

    ret = calloc(1, sizeof(M3UAGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_DEBUG,
                                      2))) ||
                     (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_WARNING) &&
                     (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_WARNING,
                                      2))) ||
                     (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_ERROR) &&
                     (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_ERROR,
                                      2))) ||
                     (TRACE_IsLevelOn(M3UA_TraceData,
                                    M3UA_TRACE_CRITICAL) &&
                     (TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_CRITICAL,
                                      0) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_CRITICAL,
                                      1) ||
                     TRACE_IsOutputOn(M3UA_TraceData,
                                      M3UA_TRACE_CRITICAL,
                                      2)));
    ret->alarmLevel = M3UA_AlarmLevel;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      It gives the M3UA configuration details
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
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     Addition of debug console feature.
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI
void GetCfg(DBC_Server *dbc, ITS_CHAR *buf)
{
    M3UAGeneralCfg *cfg;
    ITS_UINT i;

    cfg =  M3UA_GetGeneralCfg();

    i = cfg->alarmLevel;

    /* Alarm Info */
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

    strcpy(buf, "    M3UA Trace -\n");
    DBC_AppendText(dbc, buf);

    /* Trace Info */
    if ( cfg->traceOn)
    {
        /* Debug */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                               M3UA_TRACE_DEBUG))
        {
            strcpy(buf, "        Debug     = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_DEBUG,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_DEBUG,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_DEBUG,
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

        /* Critical */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL))
        {
            strcpy(buf, "        Critical  = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_CRITICAL,
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

        /* Warning */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING))
        {
            strcpy(buf, "        Warning   = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_WARNING,
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

        /* Error */
        if (TRACE_IsLevelOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR))
        {
            strcpy(buf, "        Error     = ");
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR,
                                0))
            {
                strcat(buf, " stdout");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR,
                                1))
            {
                strcat(buf, " file");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                                M3UA_TRACE_ERROR,
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

    sprintf(buf, "*********** End of M3UA General Config *************\n");
    DBC_AppendText(dbc, buf);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      MML handler
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
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name       Date        Reference      Description
 * -----------------------------------------------------------------------------
 *
 * gdevanand  04-06-2005  BugId:1557     This function handles mml commands .
 *
 *  See Also:
 ****************************************************************************/
M3UADLLAPI void
M3UA_Console(DBC_Server *dbc, const char *cmdLine)
{
    ITS_CHAR buf[ITS_PATH_MAX];
    ITS_INT ret;

    ITS_C_ASSERT(dbc != NULL);

    if (DBC_Cmd(dbc, "m3_get_gen_cfg", "M3UA Get General Config", "", ""))
    {
        GetCfg(dbc,buf);
    }
    else if (DBC_Cmd(dbc, "m3_set_gen_cfg", "M3UA Set General Config", "<al>",
                     "<alarm level>"))
    {
        M3UAGeneralCfg cfg;
        ITS_CHAR alarmLevel[ITS_PATH_MAX];
        ITS_CHAR traceOn[ITS_PATH_MAX];
        ITS_CHAR traceType[ITS_PATH_MAX];
        ITS_CHAR traceOutput[ITS_PATH_MAX];

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
        else if (strstr(alarmLevel, "MAJOR") || strstr(alarmLevel, "major"))
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") || strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") || strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") || strstr(alarmLevel, "off") )
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
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, M3UA_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, M3UA_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, M3UA_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, M3UA_ERROR_STRING);
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
            strcpy(cfg.traceOutput, M3UA_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, M3UA_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, M3UA_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  M3UA_SetGeneralCfg(&cfg);
        if (ret != ITS_SUCCESS)
        {
            return;
        }

        sprintf(buf, "*********** M3UA General Config Set*************\n");
        DBC_AppendText(dbc, buf);

        M3UA_DEBUG(("M3UA DEBUG IS ACTIVE \n")); 
        M3UA_CRITICAL(("M3UA CRITICAL IS ACTIVE \n")); 
        M3UA_WARNING(("M3UA WARNING IS ACTIVE \n")); 
        M3UA_ERROR(("M3UA ERROR IS ACTIVE \n")); 
    }
    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Commiting the configuration in the XML file.
 *
 *  Input Parameters:
 *      FILE* fp - File Pointer to commit.
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
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name        Date        Reference      Description
 * -----------------------------------------------------------------------------
 * Mani        05-05-2005  BugId:1773
 *
 *  See Also:
 ****************************************************************************/

int
M3UA_Commit(FILE* fp)
{
    fprintf(fp, "\t\t<M3UA>\n");

    if (M3UA_TraceData != NULL)
    {
        fprintf(fp, "\t\t\t<SigtranTrace>\n");
        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_CRITICAL))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_CRITICAL, 0))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_CRITICAL, 1))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_CRITICAL, 2))
            {
                fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_ERROR))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_ERROR, 0))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_ERROR, 1))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_ERROR, 2))
            {
                fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_WARNING))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_WARNING, 0))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_WARNING, 1))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_WARNING, 2))
            {
                fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
            }
        }

        if (TRACE_IsLevelOn(M3UA_TraceData,
            M3UA_TRACE_DEBUG))
        {
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_DEBUG, 0))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_DEBUG, 1))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
            }
            if (TRACE_IsOutputOn(M3UA_TraceData,
                M3UA_TRACE_DEBUG, 2))
            {
                fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
            }
        }
        fprintf(fp, "\t\t\t</SigtranTrace>\n");
    }

    fprintf(fp, "\t\t</M3UA>\n\n");

    return ITS_SUCCESS;
}

