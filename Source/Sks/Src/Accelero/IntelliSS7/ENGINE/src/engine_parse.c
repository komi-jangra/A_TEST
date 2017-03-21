/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:44  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:41  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:00  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.1  2005/08/29 09:21:53  adutta
 * LOG: BSSAP configuration
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:19  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2004/04/16 05:07:54  akumar
 * LOG: Modified to allow SIP configurable thru XML.
 * LOG:
 * LOG: Revision 8.2  2003/06/16 13:27:24  mmanikandan
 * LOG: Xml Persistency is added.
 * LOG:
 * LOG: Revision 8.1  2003/02/27 15:46:56  mmiers
 * LOG: Implementation was getting too large.  Split into
 * LOG: manageable chunks.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#ident "$Id: engine_parse.c,v 1.1.1.1 2007-10-08 11:11:17 bsccs2 Exp $"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <engine.h>
#include <expat.h>
#include "engine_intern.h"

/*
 * forward
 */
static ITS_Object   curLayer = NULL;

extern ITS_BOOLEAN  ENGINE_inParser;

#undef ITS_C_ASSERT
#define ITS_C_ASSERT(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_ASSERT_PRINT(assertion);                                        \
        if (ENGINE_inParser)                                                  \
        {                                                                     \
            ENGINE_LinePrint();                                               \
        }                                                                     \
        abort();                                                              \
    }

static char *ANSI_Variants[] =
{
    NULL,
    "ANSI_88",
    "ANSI_92",
    "ANSI_96",
    NULL
};

static char *CCITT_Variants[] =
{
    NULL,
    "BlueBook",
    "WhiteBook",
    "WhiteBook_97",
    NULL
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Figure out variant by name
 *
 *  Input Parameters:
 *      string - variant string
 *
 *  Notes:
 ****************************************************************************/
static int
GetANSIVariant(const char *name)
{
    int i;

    for (i = 1; ANSI_Variants[i] != NULL; i++)
    {
        if (strcmp(name, ANSI_Variants[i]) == 0)
        {
            return (i);
        }
    }

    return (ITS_LATEST_GEN);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Figure out variant by name
 *
 *  Input Parameters:
 *      string - variant string
 *
 *  Notes:
 ****************************************************************************/
static int
GetCCITTVariant(const char *name)
{
    int i;

    for (i = 1; CCITT_Variants[i] != NULL; i++)
    {
        if (strcmp(name, CCITT_Variants[i]) == 0)
        {
            return (i);
        }
    }

    return (ITS_LATEST_GEN);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse application level attributes
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ApplicationClass, isService,
 *                          usesCPP, globalStartMask, "libCISCO.so",
 *                          "ss7Selector", "appSelector", "appDeselector",
 *                          "hmi", "alarm", "preFunc", "postFunc");
 ****************************************************************************/
static void
HandleApplication(const char **attr)
{
    ITS_BOOLEAN cppBinding = ITS_TRUE;
    ITS_BOOLEAN isService = ITS_FALSE;
    ITS_UINT mask = 0;
    const char *lib = NULL, *ss7 = NULL, *app = NULL, *appD = NULL;
    const char *hmi = NULL, *alarm = NULL;
    const char *preFunc = NULL, *postFunc = NULL;

    /* parse the attributes */
    while (*attr)
    {
        const char *tattr = *attr;

        attr++;
        if (strcmp(tattr, NAME_STRING) == 0)
        {
            APPL_SetName(*attr);
        }
        else if (strcmp(tattr, TYPE_STRING) == 0)
        {
            if (strcmp(*attr, SERVICE_STRING) == 0)
            {
                isService = ITS_TRUE;
            }
        }
        else if (strcmp(tattr, BINDING_STRING) == 0)
        {
            if (strcmp(*attr, "C") == 0)
            {
                cppBinding = ITS_FALSE;
            }
        }
        else if (strcmp(tattr, LIBRARY_STRING) == 0)
        {
            lib = *attr;
        }
        else if (strcmp(tattr, SS7_SELECT_STRING) == 0)
        {
            ss7 = *attr;
        }
        else if (strcmp(tattr, APP_SELECT_STRING) == 0)
        {
            app = *attr;
        }
        else if (strcmp(tattr, APP_DESELECT_STRING) == 0)
        {
            appD = *attr;
        }
        else if (strcmp(tattr, HMI_CB_STRING) == 0)
        {
            hmi = *attr;
        }
        else if (strcmp(tattr, ALARM_CB_STRING) == 0)
        {
            alarm = *attr;
        }
        else if (strcmp(tattr, PRE_FUNC_STRING) == 0)
        {
            preFunc = *attr;
        }
        else if (strcmp(tattr, POST_FUNC_STRING) == 0)
        {
            postFunc = *attr;
        }
        else if (strcmp(tattr, GS_STRING) == 0)
        {
            /* filter it out here */
            /* hardcode the strings.  These will never change. */
            if (strstr(*attr, "ANSI-MTP3") != NULL)
            {
                mask |= ITS_MTP3_ANSI;
            }
            if (strstr(*attr, "ANSI-ISUP") != NULL)
            {
                mask |= ITS_ISUP_ANSI;
            }
            if (strstr(*attr, "ANSI-SCCP") != NULL)
            {
                mask |= ITS_SCCP_ANSI;
            }
            if (strstr(*attr, "ANSI-TCAP") != NULL)
            {
                mask |= ITS_TCAP_ANSI;
            }
            if (strstr(*attr, "ITU-MTP3") != NULL)
            {
                mask |= ITS_MTP3_CCITT;
            }
            if (strstr(*attr, "ITU-ISUP") != NULL)
            {
                mask |= ITS_ISUP_CCITT;
            }
            if (strstr(*attr, "ITU-SCCP") != NULL)
            {
                mask |= ITS_SCCP_CCITT;
            }
            if (strstr(*attr, "ITU-TCAP") != NULL)
            {
                mask |= ITS_TCAP_CCITT;
            }
            if (strstr(*attr, "PRC-MTP3") != NULL)
            {
                mask |= ITS_MTP3_PRC;
            }
            if (strstr(*attr, "PRC-ISUP") != NULL)
            {
                mask |= ITS_ISUP_PRC;
            }
            if (strstr(*attr, "PRC-SCCP") != NULL)
            {
                mask |= ITS_SCCP_PRC;
            }
            if (strstr(*attr, "PRC-TCAP") != NULL)
            {
                mask |= ITS_TCAP_PRC;
            } 
        }

        attr++;
    }

    /* build the config object */
    application = (ENGINE_Application)
                    ITS_ConstructObject(itsENGINE_ApplicationClass,
                                        isService, cppBinding,
                                        mask, lib, ss7, app, appD,
                                        hmi, alarm,
                                        preFunc, postFunc);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse application level options
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleOption(const char **attr)
{
    char buf[ITS_PATH_MAX];
    char **opts = NULL;
    int numOpts = 0;
    const char *name = NULL, *value = NULL;

    ITS_C_ASSERT(application != NULL);

    opts = ENGINE_APP_OPTIONS(application);
    numOpts = ENGINE_APP_NUM_OPTIONS(application);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            name = *attr;

            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            value = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(name && value);

    sprintf(buf, "%s=%s", name, value);

    numOpts++;

    opts = (char **)realloc(opts, numOpts * sizeof(char *));
    ITS_C_ASSERT(opts != NULL);

    opts[numOpts - 1] = malloc(strlen(buf) + 1);
    ITS_C_ASSERT(opts[numOpts - 1] != NULL);

    strcpy(opts[numOpts - 1], buf);

    ENGINE_APP_NUM_OPTIONS(application) = numOpts;
    ENGINE_APP_OPTIONS(application) = opts;
}

static ITS_BOOLEAN inFaultTolerance = ITS_FALSE;
static ENGINE_FaultTolerance faultTolerance = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start Fault Tolerance.
 *
 *  Input Parameters:
 *      attr - Fault Tolerance element attributes.
 *
 ****************************************************************************/
static void
StartFaultTolerance(const char** attr)
{
    ITS_USHORT maxNumFtGroups           = 0;
    ITS_USHORT maxNumProcesses          = 0;
    ITS_USHORT maxNumNodes              = 0;
    ITS_USHORT nodeId                   = (ITS_USHORT)(-1);
    ITS_USHORT processId                = (ITS_USHORT)(-1);
    ITS_USHORT tcapFtGroupId            = 0;
    ITS_USHORT sccpFtGroupId            = 0;
    ITS_USHORT mtp3FtGroupId            = 0;
    ITS_USHORT isupFtGroupId            = 0;
    ITS_USHORT routingFtGroupId         = 0;
    ITS_USHORT timersFtGroupId          = 0;
    ITS_USHORT mgmtDataFtGroupId        = 0;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, MAX_NUM_FT_GRPS_STRING) == 0)
        {
            attr++;
            maxNumFtGroups = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MAX_NUM_PROCS_STRING) == 0)
        {
            attr++;
            maxNumProcesses = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MAX_NUM_NODES_STRING) == 0)
        {
            attr++;
            maxNumNodes = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, NODE_ID_STRING) == 0)
        {
            attr++;
            nodeId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, PROC_ID_STRING) == 0)
        {
            attr++;
            processId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, TCAP_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            tcapFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, SCCP_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            sccpFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MTP3_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            mtp3FtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, ISUP_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            isupFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, ROUTING_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            routingFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, TIMERS_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            timersFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MGMT_DATA_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            mgmtDataFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    object = ITS_ConstructObject(
                    itsENGINE_FaultToleranceClass,
                    application,
                    (int)maxNumFtGroups,
                    (int)maxNumProcesses,
                    (int)maxNumNodes,
                    (int)nodeId,
                    (int)processId,
                    (int)tcapFtGroupId,
                    (int)sccpFtGroupId,
                    (int)mtp3FtGroupId,
                    (int)isupFtGroupId,
                    (int)routingFtGroupId,
                    (int)timersFtGroupId,
                    (int)mgmtDataFtGroupId,
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL  /* To be overwritten. */);

    ITS_C_ASSERT(object != NULL);

    faultTolerance = (ENGINE_FaultTolerance)object;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      End Fault Tolerance.
 *
 ****************************************************************************/
static void
EndFaultTolerance()
{
    faultTolerance = NULL;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtmPreExecuteLogicProcedure.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtmPreExecuteLogicProcedure(const char** attr)
{
    const char* ftmPreExecLogicProcName = NULL;
    const char* ftmPreExecLogicProcLibName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            ftmPreExecLogicProcLibName = *attr;
            attr++;
        }
        else if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            ftmPreExecLogicProcName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    /* 
     * Overwrites. 
     */

    if (ftmPreExecLogicProcName && 
        strlen(ftmPreExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPreExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPreExecLogicProcLibName && 
        strlen(ftmPreExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPreExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtmLoopExecuteLogicProcedure.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtmLoopExecuteLogicProcedure(const char** attr)
{
    const char* ftmLoopExecLogicProcName = NULL;
    const char* ftmLoopExecLogicProcLibName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            ftmLoopExecLogicProcLibName = *attr;
            attr++;
        }
        else if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            ftmLoopExecLogicProcName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    /* 
     * Overwrites. 
     */

    if (ftmLoopExecLogicProcName && 
        strlen(ftmLoopExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmLoopExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmLoopExecLogicProcLibName && 
        strlen(ftmLoopExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmLoopExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtmPostExecuteLogicProcedure.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtmPostExecuteLogicProcedure(const char** attr)
{
    const char* ftmPostExecLogicProcName = NULL;
    const char* ftmPostExecLogicProcLibName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            ftmPostExecLogicProcLibName = *attr;
            attr++;
        }
        else if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            ftmPostExecLogicProcName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    /* 
     * Overwrites. 
     */

    if (ftmPostExecLogicProcName && 
        strlen(ftmPostExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPostExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPostExecLogicProcLibName && 
        strlen(ftmPostExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPostExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MembershipChangeAllFtGroupsCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleMembershipChangeAllFtGroupsCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_CALLBACKS(ft),
                    (int)FT_CALLBACK_MEMBERSHIP_CHANGE_ALL_FT_GROUPS,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle EventFromAllFtGroupMembersCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleEventFromAllFtGroupMembersCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_CALLBACKS(ft),
                    (int)FT_CALLBACK_EVENT_FROM_ALL_FT_GROUP_MEMBERS,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}

static ITS_BOOLEAN inFtGroup = ITS_FALSE;
static ENGINE_FtGroup currentFtGroup = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start FtGroup.
 *
 *  Input Parameters:
 *      attr - FtGroup element attributes.
 *
 ****************************************************************************/
static void
StartFtGroup(const char** attr)
{
    ITS_USHORT ftGroupId    = (ITS_USHORT)(-1);
    const char* ftGroupName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FT_GRP_ID_STRING) == 0)
        {
            attr++;
            ftGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, FT_GRP_NAME_STRING) == 0)
        {
            attr++;
            ftGroupName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtGroupClass,
                    &ENGINE_FT_FT_GROUPS(ft),
                    (int)ftGroupId,
                    ftGroupName,
                    0,    /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    0,    /* To be overwritten. */
                    NULL  /* To be overwritten. */);

    ITS_C_ASSERT(object != NULL);

    currentFtGroup = (ENGINE_FtGroup)object;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      End Fault Tolerance.
 *
 ****************************************************************************/
static void
EndFtGroup()
{
    currentFtGroup = NULL;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle DsmConfig.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleDsmConfig(const char** attr)
{
    ITS_UINT dsmSize = 0;
    const char* dsmBaseAddress = NULL;
    ITS_UINT dsmMaxNumTables = 0;
    const char* dsmType = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;

    while (*attr)
    {
        if (strcmp(*attr, DSM_SIZE_STRING) == 0)
        {
            attr++;
            dsmSize = (ITS_UINT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, DSM_BASE_ADDR_STRING) == 0)
        {
            attr++;
            dsmBaseAddress = *attr;
            attr++;
        }
        else if (strcmp(*attr, DSM_MAX_NUM_TBLS_STRING) == 0)
        {
            attr++;
            dsmMaxNumTables = (ITS_UINT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, DSM_TYPE_STRING) == 0)
        {
            attr++;
            dsmType = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    /* 
     * Overwrites. 
     */

    ENGINE_FT_GROUP_DSM_SIZE(ftGroup) = dsmSize;

    if (dsmBaseAddress && strlen(dsmBaseAddress) != 0)
    {
        ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) = strdup(dsmBaseAddress);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) != NULL);
    }

    ENGINE_FT_GROUP_DSM_MAX_NUM_TABLES(ftGroup) = dsmMaxNumTables;

    if (dsmType && strlen(dsmType) != 0)
    {
        ENGINE_FT_GROUP_DSM_TYPE(ftGroup) = strdup(dsmType);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_TYPE(ftGroup) != NULL);
    }       
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtGroupMember.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtGroupMember(const char** attr)
{
    ITS_USHORT nodeId = (ITS_USHORT)(-1);
    const char* nodeName = NULL;
    ITS_USHORT processId = (ITS_USHORT)(-1);
    const char* processName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, NODE_ID_STRING) == 0)
        {
            attr++;
            nodeId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, NODE_NAME_STRING) == 0)
        {
            attr++;
            nodeName = *attr;
            attr++;
        }
        else if (strcmp(*attr, PROC_ID_STRING) == 0)
        {
            attr++;
            processId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, PROC_NAME_STRING) == 0)
        {
            attr++;
            processName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtGroupMemberClass,
                    &ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftGroup),
                    (int)FT_GROUP_MEMBER_NORMAL,
                    (int)nodeId,
                    nodeName,
                    (int)processId,
                    processName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MasterFtGroupMember.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleMasterFtGroupMember(const char** attr)
{
    ITS_USHORT nodeId = (ITS_USHORT)(-1);
    const char* nodeName = NULL;
    ITS_USHORT processId = (ITS_USHORT)(-1);
    const char* processName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, NODE_ID_STRING) == 0)
        {
            attr++;
            nodeId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, NODE_NAME_STRING) == 0)
        {
            attr++;
            nodeName = *attr;
            attr++;
        }
        else if (strcmp(*attr, PROC_ID_STRING) == 0)
        {
            attr++;
            processId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, PROC_NAME_STRING) == 0)
        {
            attr++;
            processName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtGroupMemberClass,
                    &ENGINE_FT_GROUP_MASTER_FT_GROUP_MEMBERS(ftGroup),
                    (int)FT_GROUP_MEMBER_MASTER,
                    (int)nodeId,
                    nodeName,
                    (int)processId,
                    processName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MembershipChangeCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleMembershipChangeCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_GROUP_FT_CALLBACKS(ftGroup),
                    (int)FT_CALLBACK_MEMBERSHIP_CHANGE,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle EventFromFtGroupMemberCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleEventFromFtGroupMemberCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_GROUP_FT_CALLBACKS(ftGroup),
                    (int)FT_CALLBACK_EVENT_FROM_FT_GROUP_MEMBER,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}


static ITS_BOOLEAN inWindows = ITS_FALSE;
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse windows crap.
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleWindows(const char **attr)
{
    char buf[ITS_PATH_MAX];
    const char *ifc = NULL, *mask = NULL, *bcast = NULL;
    char **opts = NULL;
    int numOpts = 0;

    ITS_C_ASSERT(application != NULL);

    opts = ENGINE_APP_OPTIONS(application);
    numOpts = ENGINE_APP_NUM_OPTIONS(application);

    while (*attr)
    {
        if (strcmp(*attr, LOCAL_INTERFACE_STRING) == 0)
        {
            attr++;
            ifc = *attr;
            attr++;
        }
        else if (strcmp(*attr, LOCAL_MASK_STRING) == 0)
        {
            attr++;
            mask = *attr;
            attr++;
        }
        else if (strcmp(*attr, LOCAL_BCAST_STRING) == 0)
        {
            attr++;
            bcast = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }

        if (ifc && mask && bcast)
        {
            numOpts += 3;

            opts = (char **)realloc(opts, numOpts * sizeof(char *));
            ITS_C_ASSERT(opts != NULL);

            /* interface */
            sprintf(buf, "%s=%s", LOCAL_INTERFACE_STRING, ifc);
            opts[numOpts - 3] = (char *)malloc(strlen(buf) + 1);
            ITS_C_ASSERT(opts[numOpts - 3] != NULL);
            strcpy(opts[numOpts - 3], buf);

            /* mask */
            sprintf(buf, "%s=%s", LOCAL_MASK_STRING, mask);
            opts[numOpts - 2] = (char *)malloc(strlen(buf) + 1);
            ITS_C_ASSERT(opts[numOpts - 2] != NULL);
            strcpy(opts[numOpts - 2], buf);

            /* broadcast */
            sprintf(buf, "%s=%s", LOCAL_BCAST_STRING, bcast);
            opts[numOpts - 1] = (char *)malloc(strlen(buf) + 1);
            ITS_C_ASSERT(opts[numOpts - 1] != NULL);
            strcpy(opts[numOpts - 1], buf);
        }
    }

    ENGINE_APP_OPTIONS(application) = opts;
    ENGINE_APP_NUM_OPTIONS(application) = numOpts;
}

static ITS_BOOLEAN inFeature = ITS_FALSE;
static struct
{
    char *name;
    char *library;
    char *classRec;
    char **opts;
    int  numOpts;
}
curFeature;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse features
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartFeature(const char **attr)
{
    memset(&curFeature, 0, sizeof(curFeature));

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;
            curFeature.name = strdup(*attr);
            ITS_C_ASSERT(curFeature.name != NULL);
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            curFeature.library = strdup(*attr);
            ITS_C_ASSERT(curFeature.library != NULL);
            attr++;
        }
        else if (strcmp(*attr, CLASS_REC_STRING) == 0)
        {
            attr++;
            curFeature.classRec = strdup(*attr);
            ITS_C_ASSERT(curFeature.classRec != NULL);
            attr++;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse feature options
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleFeatureOption(const char **attr)
{
    char buf[ITS_PATH_MAX];
    const char *name = NULL, *value = NULL;

    ITS_C_REQUIRE(inFeature);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;
            name = *attr;
            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;
            value = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(name != NULL && value != NULL);

    sprintf(buf, "%s=%s", name, value);

    curFeature.numOpts++;

    curFeature.opts = (char **)realloc(curFeature.opts,
                            curFeature.numOpts * sizeof(char *));
    ITS_C_ASSERT(curFeature.opts != NULL);

    curFeature.opts[curFeature.numOpts - 1] = (char *)malloc(strlen(buf) + 1);
    ITS_C_ASSERT(curFeature.opts[curFeature.numOpts - 1] != NULL);
    strcpy(curFeature.opts[curFeature.numOpts - 1], buf);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse feature options
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndFeature()
{
    ITS_Object obj;

    obj = ITS_ConstructObject(itsENGINE_FeatureClass, application,
                              curFeature.name, curFeature.library,
                              curFeature.classRec,
                              curFeature.opts, curFeature.numOpts);
    ITS_C_ASSERT(obj != NULL);
}

/*
 * trace data
 */
static ITS_BOOLEAN tkTrace = ITS_FALSE;
static ITS_BOOLEAN appTrace = ITS_FALSE;
static ITS_BOOLEAN stackTrace = ITS_FALSE;

static int critMask;
static int errMask;
static int warnMask;
static int dbgMask;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording trace info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartTrace(const char **attr)
{
    critMask = TRACE_TO_NONE;
    errMask = TRACE_TO_NONE;
    warnMask = TRACE_TO_NONE;
    dbgMask = TRACE_TO_NONE;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse trace info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleTrace(const char *el, const char **attr)
{
    int *mask = NULL;

    if (strcmp(el, CRIT_STRING) == 0)
    {
        mask = &critMask;
    }
    else if (strcmp(el, ERR_STRING) == 0)
    {
        mask = &errMask;
    }
    else if (strcmp(el, WARN_STRING) == 0)
    {
        mask = &warnMask;
    }
    else if (strcmp(el, DBG_STRING) == 0)
    {
        mask = &dbgMask;
    }
    else
    {
        return;
    }

    while (*attr)
    {
        if (strcmp(*attr, OUTPUT_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ITS_STDOUT_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_DISPLAY;
            }
            else if (strcmp(*attr, ITS_FILE_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_FILE;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording trace info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndTrace()
{
    ITS_Object *tmp = NULL, level;

    if (tkTrace)
    {
        tmp = &ENGINE_APP_SUPPORT_LEVELS(application);
    }
    else if (stackTrace)
    {
        ITS_C_ASSERT(curLayer != NULL);

        tmp = &ENGINE_ISS7_TRACE(curLayer);
    }
    else
    {
        tmp = &ENGINE_APP_TRACE_LEVELS(application);
    }

    /* create the levels */
    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_CRITICAL_STRING, critMask);
    ITS_C_ASSERT(level != NULL);

    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_ERROR_STRING, errMask);
    ITS_C_ASSERT(level != NULL);

    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_WARNING_STRING, warnMask);
    ITS_C_ASSERT(level != NULL);

    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_DEBUG_STRING, dbgMask);
    ITS_C_ASSERT(level != NULL);
}

static ITS_BOOLEAN  inWorkPool = ITS_FALSE;
static ITS_BOOLEAN  inItemPool = ITS_FALSE;
static ITS_BOOLEAN  inBorderPool = ITS_FALSE;
static ITS_Object   curPool = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording pool info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartPool(const char *el, const char **attr)
{
    ENGINE_ThreadPoolType type;
    int stackSize = 0;

    ITS_C_ASSERT(curPool == NULL);

    if (strcmp(el, WORK_POOL_STRING) == 0)
    {
        type = TP_WORKERS;
    }
    else if (strcmp(el, ITEM_POOL_STRING) == 0)
    {
        type = TP_WORK_ITEMS;
    }
    else if (strcmp(el, BORDER_POOL_STRING) == 0)
    {
        type = TP_BORDERS;
    }
    else
    {
        return;
    }

    while (*attr)
    {
        if (strcmp(*attr, STACK_SIZE_STRING) == 0)
        {
            attr++;

            stackSize = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    curPool = ITS_ConstructObject(itsENGINE_ThreadPoolClass, application,
                                  stackSize, type);
    ITS_C_ASSERT(curPool != NULL);

    if (type == TP_WORK_ITEMS)
    {
        ENGINE_TransportPart thisTrans;
        ITS_Object ret;

        memset(&thisTrans, 0, sizeof(ENGINE_TransportPart));

        /* go ahead and create this transport */
        thisTrans.callbacks =
                  ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                      application, NULL, ITS_FALSE,
                                      DISP_PROT_WORK_ITEM, DISP_BLOCKING,
                                      NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL,
                                      NULL, NULL, DISP_PROT_WORK_ITEM);
        ITS_C_ASSERT(thisTrans.callbacks != NULL);

        thisTrans.mask = ITS_TRANSPORT_TQUEUE;

        ret = ITS_ConstructObject(itsENGINE_TransportClass, curPool,
                                  thisTrans.name, thisTrans.mask, thisTrans.inst,
                                  ITS_FALSE,
                                  thisTrans.specialization, thisTrans.callbacks,
                                  thisTrans.links, thisTrans.workItems);
        ITS_C_ASSERT(ret != NULL);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording pool info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndPool(const char *el)
{
    curPool = NULL;
}

static ITS_BOOLEAN  inTransport = ITS_FALSE;
static ITS_BOOLEAN  isITU = ITS_FALSE;
static ITS_BOOLEAN  isANSI = ITS_FALSE;
static ITS_BOOLEAN  isCHINA = ITS_FALSE;
static int trCount = 0;
static ENGINE_TransportPart thisTrans;
static ENGINE_TransportSpecificsPart thisSpecs;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording transport info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartTransport(const char **attr)
{
    ITS_C_ASSERT(inTransport);
    ITS_C_ASSERT(application != NULL);

    memset(&thisTrans, 0, sizeof(ENGINE_TransportPart));
    memset(&thisSpecs, 0, sizeof(ENGINE_TransportSpecificsPart));
    isITU = ITS_FALSE;
    isANSI = ITS_FALSE;
    isCHINA = ITS_FALSE;
    trCount = 0;

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, T_SS7_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_SS7 |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_FIFO_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_FIFO |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_GFIFO_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_GFIFO |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_CSOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_CSOCKET |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_SSOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_SSOCKET |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_ISOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_SSOCKET |
                                    ITS_TRANSPORT_SSOCKET_ITER |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_DSOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_DATAGRAM |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_VIRT_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_DATAGRAM |
                                    ITS_TRANSPORT_DGRAM_VIRT;
            }
            else if (strcmp(*attr, T_TQ_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_TQUEUE;
            }
            else
            {
                ITS_C_ASSERT(ITS_FALSE);
            }

            attr++;
        }
        else if (strcmp(*attr, INSTANCE_STRING) == 0)
        {
            attr++;

            thisTrans.inst = atoi(*attr);

            attr++;
        }
        else if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            thisTrans.name = strdup(*attr);
            ITS_C_ASSERT(thisTrans.name != NULL);

            attr++;
        }
        else if (strcmp(*attr, INTERNODE_STRING) == 0)
        {
            attr++;
 
            thisTrans.isInterNode = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ITU_STRING) == 0)
            {
                isITU = ITS_TRUE;
            }
            else if (strcmp(*attr, ANSI_STRING) == 0)
            {
                isANSI = ITS_TRUE;
            }
            else if (strcmp(*attr, CHINA_STRING) == 0)
            {
                isCHINA = ITS_TRUE;
            }

            attr++;
        }
        else if (strcmp(*attr, COUNT_STRING) == 0)
        {
            attr++;

            trCount = atoi(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record transport specifics info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleTransport(const char *el, const char **attr)
{
    switch (ITS_GET_TRANSPORT_TYPE(thisTrans.mask))
    {
    case ITS_TRANSPORT_SS7:
        if (strcmp(el, VENDOR_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, LIBRARY_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.ss7Specs.vendorLib = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.ss7Specs.vendorLib != NULL);

                    attr++;
                }
                else if (strcmp(*attr, NAME_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.ss7Specs.vendorName = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.ss7Specs.vendorName != NULL);

                    attr++;
                }
                else if (strcmp(*attr, VENDOR_REC_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.ss7Specs.vendorClass = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.ss7Specs.vendorClass != NULL);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        if (strcmp(el, FIFO_DATA_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, FIFO_CLIENT_PATH_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.fifoSpecs.clientPath = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.fifoSpecs.clientPath != NULL);

                    attr++;
                }
                else if (strcmp(*attr, FIFO_SERVER_PATH_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.fifoSpecs.serverPath = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.fifoSpecs.serverPath != NULL);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        if (strcmp(el, STREAM_DATA_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, SOCKET_DOMAIN_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.socketDomain = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.socketDomain != NULL);

                    attr++;
                }
                else if (strcmp(*attr, SERVER_PATH_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.serverPath = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.serverPath != NULL);

                    attr++;
                }
                else if (strcmp(*attr, SERVER_PORT_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.serverPort = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.serverPort != NULL);

                    attr++;
                }
                else if (strcmp(*attr, RETRY_DELAY_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.retryDelay = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.retryDelay != NULL);

                    attr++;
                }
                else if (strcmp(*attr, RETRY_COUNT_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.retryCount = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.retryCount != NULL);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }

        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            if (strcmp(el, MOD_GDI_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, GDI_LOCAL_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.gdiSpecs.localPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.gdiSpecs.localPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, GDI_REMOTE_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.gdiSpecs.remotePC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.gdiSpecs.remotePC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, GDI_REMOTE_SSN_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.gdiSpecs.remoteSSN = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.gdiSpecs.remoteSSN != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            if (strcmp(el, MOD_TALI_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, TALI_LOCAL_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.localPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.localPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, TALI_ADJ_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.adjacentPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.adjacentPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, TALI_LOCALLY_ALLOWED_ON_OPEN_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.localAllowedOnOpen = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.localAllowedOnOpen != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, TALI_USE_UPPER_LAYER_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.useUpperLayer = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.useUpperLayer != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            if (strcmp(el, MOD_IMAL_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, IMAL_LOCAL_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.imalSpecs.localPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.imalSpecs.localPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, IMAL_ADJ_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.imalSpecs.adjacentPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.imalSpecs.adjacentPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, IMAL_KEEPALIVE_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.imalSpecs.keepAliveTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.imalSpecs.keepAliveTimeOut != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        break;

    case ITS_TRANSPORT_DATAGRAM:
        if (strcmp(el, DGRAM_DATA_STRING) == 0)
        {
            while (*attr)
            {
                if (thisTrans.mask & ITS_TRANSPORT_DGRAM_VIRT)
                {
                    if (strcmp(*attr, SERVER_PATH_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localHost = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localHost != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, SERVER_PORT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localPort = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localPort != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
                else
                {
                    if (strcmp(*attr, LOCAL_HOST_NAME_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localHost = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localHost != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, LOCAL_PORT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localPort = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localPort != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
        }
        else if (strcmp(el, ASSOCIATE_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, VALUE_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.udpSpecs.numAssociates++;

                    thisSpecs.data.udpSpecs.associates = (char **)
                                            realloc(thisSpecs.data.udpSpecs.associates,
                                                    thisSpecs.data.udpSpecs.numAssociates *
                                                        sizeof(char *));
                    ITS_C_ASSERT(thisSpecs.data.udpSpecs.associates != NULL);

                    thisSpecs.data.udpSpecs.associates[thisSpecs.data.udpSpecs.numAssociates - 1] =
                        malloc(strlen(*attr) + 1);
                    ITS_C_ASSERT(thisSpecs.data.udpSpecs.associates
                                    [thisSpecs.data.udpSpecs.numAssociates - 1] != NULL);

                    strcpy(thisSpecs.data.udpSpecs.associates
                            [thisSpecs.data.udpSpecs.numAssociates - 1],
                           *attr);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }

        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            if (strcmp(el, OTHER_HOME_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, LOCAL_HOST_NAME_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.numExtraHomes++;

                        thisSpecs.data.sctpSpecs.extraHomes = (char **)
                                                realloc(thisSpecs.data.sctpSpecs.extraHomes,
                                                        thisSpecs.data.sctpSpecs.numExtraHomes *
                                                            sizeof(char *));
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.extraHomes != NULL);

                        thisSpecs.data.sctpSpecs.extraHomes
                            [thisSpecs.data.sctpSpecs.numExtraHomes - 1] = malloc(strlen(*attr) + 1);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.extraHomes
                                        [thisSpecs.data.sctpSpecs.numExtraHomes - 1] != NULL);

                        strcpy(thisSpecs.data.sctpSpecs.extraHomes
                                [thisSpecs.data.sctpSpecs.numExtraHomes - 1],
                               *attr);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            else if (strcmp(el, MOD_SCTP_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, MAX_IN_STREAMS_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.maxInStreams = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.maxInStreams != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, NUM_OUT_STREAMS_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.numOutStreams = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.numOutStreams != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, MAX_ATTEMPTS_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.maxAttempts = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.maxAttempts != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, INIT_COOKIE_LIFE_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.cookieLife = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.cookieLife != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, INIT_HB_ON_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.hbOn = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.hbOn != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, INIT_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.initTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.initTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, SEND_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.sendTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.sendTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, RECV_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.recvTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.recvTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, HB_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.hbTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.hbTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, SHUT_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.shutdownTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.shutdownTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, PMTU_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.pmtuTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.pmtuTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, IS_CLIENT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.isClient = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.isClient != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, PAYLOAD_TYPE_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.payloadType = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.payloadType != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording transport info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndTransport()
{
    ITS_Object ret;

    /* deal with undefined callbacks */
    if (thisTrans.callbacks == NULL)
    {
        DISP_HandlerType htype, atype = DISP_PROT_USER;
        ITS_BOOLEAN realSS7 = ITS_FALSE;

        if (thisTrans.mask & ITS_TRANSPORT_SS7)
        {
            realSS7 = ITS_TRUE;
        }

        if (thisTrans.mask & ITS_TRANSPORT_SSOCKET_ITER)
        {
            htype = DISP_PROT_ITERATIVE;

            if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
            {
                atype = DISP_PROT_ANSI;
            }
            else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
            {
                atype = DISP_PROT_CCITT;
            }
            else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
            {
                atype = DISP_PROT_PRC;
            }
            else
            {
                atype = DISP_PROT_USER;
            }
        }
        else if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            htype = DISP_PROT_ANSI;
        }
        else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            htype = DISP_PROT_CCITT;
        }
        else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            htype = DISP_PROT_PRC;
        }
        else
        {
            htype = DISP_PROT_USER;
        }

        thisTrans.callbacks =
                  ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                      application, NULL, realSS7,
                                      htype, DISP_BLOCKING,
                                      NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL,
                                      NULL, NULL, atype);
        ITS_C_ASSERT(thisTrans.callbacks != NULL);
    }

    /* create the specifics */
    switch (ITS_GET_TRANSPORT_TYPE(thisTrans.mask))
    {
    case ITS_TRANSPORT_SS7:
        thisTrans.specialization =
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                thisTrans.mask,
                                thisSpecs.data.ss7Specs.vendorName,
                                thisSpecs.data.ss7Specs.vendorLib,
                                thisSpecs.data.ss7Specs.vendorClass);
        ITS_C_ASSERT(thisTrans.specialization != NULL);

        if (thisSpecs.data.ss7Specs.vendorName)
        {
            free(thisSpecs.data.ss7Specs.vendorName);
        }

        if (thisSpecs.data.ss7Specs.vendorLib)
        {
            free(thisSpecs.data.ss7Specs.vendorLib);
        }

        if (thisSpecs.data.ss7Specs.vendorClass)
        {
            free(thisSpecs.data.ss7Specs.vendorClass);
        }

        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        thisTrans.specialization =
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                thisTrans.mask,
                                thisSpecs.data.fifoSpecs.clientPath,
                                thisSpecs.data.fifoSpecs.serverPath);

        if (thisSpecs.data.fifoSpecs.clientPath)
        {
            free(thisSpecs.data.fifoSpecs.clientPath);
        }
        if (thisSpecs.data.fifoSpecs.serverPath)
        {
            free(thisSpecs.data.fifoSpecs.serverPath);
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount,
                                    thisSpecs.data.gdiSpecs.localPC,
                                    thisSpecs.data.gdiSpecs.remotePC,
                                    thisSpecs.data.gdiSpecs.remoteSSN);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            if (thisSpecs.data.gdiSpecs.localPC)
            {
                free(thisSpecs.data.gdiSpecs.localPC);
            }
            if (thisSpecs.data.gdiSpecs.remotePC)
            {
                free(thisSpecs.data.gdiSpecs.remotePC);
            }
            if (thisSpecs.data.gdiSpecs.remoteSSN)
            {
                free(thisSpecs.data.gdiSpecs.remoteSSN);
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount,
                                    thisSpecs.data.taliSpecs.localPC,
                                    thisSpecs.data.taliSpecs.adjacentPC,
                                    thisSpecs.data.taliSpecs.localAllowedOnOpen,
                                    thisSpecs.data.taliSpecs.useUpperLayer);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            if (thisSpecs.data.taliSpecs.localPC)
            {
                free(thisSpecs.data.taliSpecs.localPC);
            }
            if (thisSpecs.data.taliSpecs.adjacentPC)
            {
                free(thisSpecs.data.taliSpecs.adjacentPC);
            }
            if (thisSpecs.data.taliSpecs.localAllowedOnOpen)
            {
                free(thisSpecs.data.taliSpecs.localAllowedOnOpen);
            }
            if (thisSpecs.data.taliSpecs.useUpperLayer)
            {
                free(thisSpecs.data.taliSpecs.useUpperLayer);
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount,
                                    thisSpecs.data.imalSpecs.localPC,
                                    thisSpecs.data.imalSpecs.adjacentPC,
                                    thisSpecs.data.imalSpecs.keepAliveTimeOut);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            if (thisSpecs.data.imalSpecs.localPC)
            {
                free(thisSpecs.data.imalSpecs.localPC);
            }
            if (thisSpecs.data.imalSpecs.adjacentPC)
            {
                free(thisSpecs.data.imalSpecs.adjacentPC);
            }
            if (thisSpecs.data.imalSpecs.keepAliveTimeOut)
            {
                free(thisSpecs.data.imalSpecs.keepAliveTimeOut);
            }
            break;

        default:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        break;

    case ITS_TRANSPORT_DATAGRAM:

        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_SCTP_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.udpSpecs.localHost,
                                    thisSpecs.data.udpSpecs.localPort,
                                    thisSpecs.data.udpSpecs.associates,
                                    thisSpecs.data.udpSpecs.numAssociates,
                                    thisSpecs.data.sctpSpecs.extraHomes,
                                    thisSpecs.data.sctpSpecs.numExtraHomes,
                                    thisSpecs.data.sctpSpecs.maxInStreams,
                                    thisSpecs.data.sctpSpecs.numOutStreams,
                                    thisSpecs.data.sctpSpecs.maxAttempts,
                                    thisSpecs.data.sctpSpecs.cookieLife,
                                    thisSpecs.data.sctpSpecs.hbOn,
                                    thisSpecs.data.sctpSpecs.initTimeOut,
                                    thisSpecs.data.sctpSpecs.sendTimeOut,
                                    thisSpecs.data.sctpSpecs.recvTimeOut,
                                    thisSpecs.data.sctpSpecs.hbTimeOut,
                                    thisSpecs.data.sctpSpecs.shutdownTimeOut,
                                    thisSpecs.data.sctpSpecs.pmtuTimeOut,
                                    thisSpecs.data.sctpSpecs.isClient,
                                    thisSpecs.data.sctpSpecs.payloadType);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.udpSpecs.localHost)
            {
                free(thisSpecs.data.udpSpecs.localHost);
            }
            if (thisSpecs.data.udpSpecs.localPort)
            {
                free(thisSpecs.data.udpSpecs.localPort);
            }
            if (thisSpecs.data.sctpSpecs.maxInStreams)
            {
                free(thisSpecs.data.sctpSpecs.maxInStreams);
            }
            if (thisSpecs.data.sctpSpecs.numOutStreams)
            {
                free(thisSpecs.data.sctpSpecs.numOutStreams);
            }
            if (thisSpecs.data.sctpSpecs.maxAttempts)
            {
                free(thisSpecs.data.sctpSpecs.maxAttempts);
            }
            if (thisSpecs.data.sctpSpecs.cookieLife)
            {
                free(thisSpecs.data.sctpSpecs.cookieLife);
            }
            if (thisSpecs.data.sctpSpecs.hbOn)
            {
                free(thisSpecs.data.sctpSpecs.hbOn);
            }
            if (thisSpecs.data.sctpSpecs.initTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.initTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.sendTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.sendTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.recvTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.recvTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.hbTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.hbTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.shutdownTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.shutdownTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.pmtuTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.pmtuTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.isClient)
            {
                free(thisSpecs.data.sctpSpecs.isClient);
            }
            if (thisSpecs.data.sctpSpecs.payloadType)
            {
                free(thisSpecs.data.sctpSpecs.payloadType);
            }
            break;

        case ITS_TRANSPORT_DATA_SOCKET:
        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing yet */

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */

        default:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.udpSpecs.localHost,
                                    thisSpecs.data.udpSpecs.localPort,
                                    thisSpecs.data.udpSpecs.associates,
                                    thisSpecs.data.udpSpecs.numAssociates);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.udpSpecs.localHost)
            {
                free(thisSpecs.data.udpSpecs.localHost);
            }
            if (thisSpecs.data.udpSpecs.localPort)
            {
                free(thisSpecs.data.udpSpecs.localPort);
            }
            break;
        }
        break;
    }

    /* create the transport */
    ret = ITS_ConstructObject(itsENGINE_TransportClass, curPool,
                              thisTrans.name, thisTrans.mask, thisTrans.inst,
                              thisTrans.isInterNode,
                              thisTrans.specialization, thisTrans.callbacks,
                              thisTrans.links, thisTrans.workItems);
    ITS_C_ASSERT(ret != NULL);

    ENGINE_TR_NUM_ASSOCIATES(ret) = trCount;

    if (thisTrans.name)
    {
        free(thisTrans.name);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle a modifier
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleModifier(const char **attr)
{
    ITS_C_ASSERT(inTransport);

    while (*attr)
    {
        if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, MOD_DATA_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET));
                thisTrans.mask |= ITS_TRANSPORT_DATA_SOCKET;
            }
            else if (strcmp(*attr, MOD_GDI_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET));
                thisTrans.mask |= ITS_TRANSPORT_GDI_SOCKET;
            }
            else if (strcmp(*attr, MOD_RUDP_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & ITS_TRANSPORT_DATAGRAM);
                thisTrans.mask |= ITS_TRANSPORT_RUDP_SOCKET;
            }
            else if (strcmp(*attr, MOD_TALI_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET));
                thisTrans.mask |= ITS_TRANSPORT_TALI_SOCKET;
            }
            else if (strcmp(*attr, MOD_IMAL_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET |
                                               ITS_TRANSPORT_DATAGRAM));
                thisTrans.mask |= ITS_TRANSPORT_IMAL_SOCKET;
            }
            else if (strcmp(*attr, MOD_SCTP_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & ITS_TRANSPORT_DATAGRAM);
                thisTrans.mask |= ITS_TRANSPORT_SCTP_SOCKET;
            }
            else if (strcmp(*attr, MOD_MTP2_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_MTP2_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_MTP2_ANSI;
                }
                if (isCHINA)
                {
                    thisTrans.mask |= ITS_MTP2_PRC;
                }
            }
            else if (strcmp(*attr, MOD_MTP3_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_MTP3_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_MTP3_ANSI;
                }
                if (isCHINA)
                {
                    thisTrans.mask |= ITS_MTP3_PRC;
                }
            }
            else if (strcmp(*attr, MOD_ISUP_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_ISUP_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_ISUP_ANSI;
                }
            }
            else if (strcmp(*attr, MOD_SCCP_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_SCCP_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_SCCP_ANSI;
                }
            }
            else if (strcmp(*attr, MOD_TCAP_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_TCAP_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_TCAP_ANSI;
                }
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle callbacks
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCustomDispatch(const char **attr)
{
    const char *library = NULL, *cdisp = NULL;

    ITS_C_ASSERT(thisTrans.callbacks == NULL);

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            library = strdup(*attr);
            ITS_C_ASSERT(library != NULL);

            attr++;
        }
        else if (strcmp(*attr, CDISP_STRING) == 0)
        {
            attr++;

            cdisp = strdup(*attr);
            ITS_C_ASSERT(cdisp != NULL);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    thisTrans.callbacks =
              ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                  application, library, ITS_FALSE,
                                  DISP_PROT_CUSTOM, DISP_BLOCKING,
                                  cdisp, NULL,
                                  NULL, NULL, NULL,
                                  NULL, NULL, NULL,
                                  NULL, NULL,
                                  NULL, NULL, DISP_PROT_USER);
    ITS_C_ASSERT(thisTrans.callbacks != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle callbacks
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCallbacks(const char **attr)
{
    ITS_BOOLEAN realSS7 = ITS_FALSE;
    ITS_BOOLEAN blocking = ITS_TRUE;
    DISP_HandlerType htype, atype = DISP_PROT_USER;
    const char *libName = NULL, *preInit = NULL, *postInit = NULL;
    const char *preNext = NULL, *nextFailed = NULL, *postNext = NULL;
    const char *dispUser = NULL, *dispISUP = NULL, *dispSCCP = NULL;
    const char *preAccept = NULL, *onAccept = NULL;
    const char *preTerm = NULL, *postTerm = NULL;

    ITS_C_ASSERT(inTransport);
    ITS_C_ASSERT(thisTrans.callbacks == NULL);

    if (thisTrans.mask & ITS_TRANSPORT_SS7)
    {
        realSS7 = ITS_TRUE;
    }

    if (thisTrans.mask & ITS_TRANSPORT_SSOCKET_ITER)
    {
        htype = DISP_PROT_ITERATIVE;

        if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            atype = DISP_PROT_ANSI;
        }
        else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            atype = DISP_PROT_CCITT;
        }
        else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            atype = DISP_PROT_PRC;
        }
        else
        {
            atype = DISP_PROT_USER;
        }
    }
    else if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
    {
        htype = DISP_PROT_ANSI;
    }
    else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
    {
        htype = DISP_PROT_CCITT;
    }
    else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
    {
        htype = DISP_PROT_PRC;
    }
    else
    {
        htype = DISP_PROT_USER;
    }

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, NBLOCK_STRING) == 0)
            {
                blocking = ITS_FALSE;
            }
            else if (strcmp(*attr, TYPE_DBC_STRING) == 0)
            {
                if (thisTrans.mask & ITS_TRANSPORT_SSOCKET_ITER)
                {
                    atype = DISP_PROT_DBC;
                }
                else
                {
                    htype = DISP_PROT_DBC;
                }
            }

            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_INIT_STRING) == 0)
        {
            attr++;

            preInit = *attr;

            attr++;
        }
        else if (strcmp(*attr, POST_INIT_STRING) == 0)
        {
            attr++;

            postInit = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_NEXT_STRING) == 0)
        {
            attr++;

            preNext = *attr;

            attr++;
        }
        else if (strcmp(*attr, NEXT_FAIL_STRING) == 0)
        {
            attr++;

            nextFailed = *attr;

            attr++;
        }
        else if (strcmp(*attr, POST_NEXT_STRING) == 0)
        {
            attr++;

            postNext = *attr;

            attr++;
        }
        else if (strcmp(*attr, UDISP_STRING) == 0)
        {
            attr++;

            dispUser = *attr;

            attr++;
        }
        else if (strcmp(*attr, IDISP_STRING) == 0)
        {
            attr++;

            dispISUP = *attr;

            attr++;
        }
        else if (strcmp(*attr, SDISP_STRING) == 0)
        {
            attr++;

            dispSCCP = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_ACCEPT_STRING) == 0)
        {
            attr++;

            preAccept = *attr;

            attr++;
        }
        else if (strcmp(*attr, ON_ACCEPT_STRING) == 0)
        {
            attr++;

            onAccept = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_TERM_STRING) == 0)
        {
            attr++;

            preTerm = *attr;

            attr++;
        }
        else if (strcmp(*attr, POST_TERM_STRING) == 0)
        {
            attr++;

            postTerm = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    thisTrans.callbacks =
              ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                  application, libName, realSS7,
                                  htype, (blocking ? DISP_BLOCKING
                                                   : DISP_NON_BLOCKING),
                                  preInit, postInit,
                                  preNext, nextFailed, postNext,
                                  dispUser, dispISUP, dispSCCP,
                                  preAccept, onAccept,
                                  preTerm, postTerm, atype);
    ITS_C_ASSERT(thisTrans.callbacks != NULL);
}

static ITS_BOOLEAN      inRoute = ITS_FALSE;
static ROUTE_MatchInfo  rinfo;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartRoute(const char **attr)
{
    memset(&rinfo, 0, sizeof(ROUTE_MatchInfo));
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ROUTE_TYPE_LOCAL_STRING) == 0)
            {
                rinfo.basic.type = LOCAL_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_REMOTE_STRING) == 0)
            {
                rinfo.basic.type = REMOTE_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_CONCERNED_STRING) == 0)
            {
                rinfo.basic.type = CONCERNED_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_DUPLICATE_STRING) == 0)
            {
                rinfo.basic.type = DUPLICATED_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_ROUTING_KEY_STRING) == 0)
            {
                rinfo.basic.type = ROUTING_KEY_ROUTE;
            }

            attr++;
        }
        else if (strcmp(*attr, STYLE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ROUTE_STYLE_DPC_NI_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_NI;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_NI;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_SSN;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_CIC;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;
            }

            attr++;
        }
        else if (strcmp(*attr, PRIORITY_STRING) == 0)
        {
            attr++;

            rinfo.priority = (ITS_OCTET)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINKSET_SET_STRING) == 0)
        {
            attr++;

            rinfo.linkSet = (ITS_OCTET)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_JAPAN;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleRoute(const char *el, const char **attr)
{
    ITS_C_ASSERT(inRoute);

    if (strcmp(el, ROUTING_KEY_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.rkey = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, DEST_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.dpc = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, ORIG_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.opc = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, LOCAL_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.opc = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, SIO_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.sio = (ITS_OCTET)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, ROUTE_MASK_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.mask = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, SSN_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.ssn = (ITS_OCTET)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, LOCAL_SSN_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.cic = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, CIC_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.cic = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, RANGE_BEGIN_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.range.begin = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, RANGE_END_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.range.end = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndRoute()
{
    ITS_Object ret;

    /* NOTE: rinfo.sls is irrelevent (always zero) */
    switch (rinfo.basic.style)
    {
    case ROUTE_DPC_NI:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_NI:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_SSN_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_CIC_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_SSN:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.ssn,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_CIC:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.cic,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO_SSN:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.ssn,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        /* for concerned routes */
        ENGINE_RT_INFO(ret).basic.criteria.cic = rinfo.basic.criteria.cic;
        break;

    case ROUTE_DPC_OPC_SIO_CIC:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.cic,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
    }
}

/*
 * for link set
 */
static ENGINE_LinkSetPart linkSet;
static ITS_BOOLEAN haveAPC, haveLPC, haveNI;
static ITS_BOOLEAN inLinkSet = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record linkset info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartLinkSet(const char *el, const char **attr)
{
    ITS_BOOLEAN haveID = ITS_FALSE;

    haveAPC = ITS_FALSE;
    haveLPC = ITS_FALSE;
    haveNI = ITS_FALSE;

    memset(&linkSet, 0, sizeof(ENGINE_LinkSetPart));

    while (*attr)
    {
        if (strcmp(*attr, ID_STRING) == 0)
        {
            attr++;

            linkSet.linkSet = (ITS_OCTET)RESFILE_ParseNum(*attr);
            haveID = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, LINKSET_NUM_TO_START_STRING) == 0)
        {
            attr++;

            linkSet.numToStart = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINKSET_ADJ_STP_STRING) == 0)
        {
            attr++;

            linkSet.adjacentSTP = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINKSET_IS_CLINK_STRING) == 0)
        {
            attr++;

            linkSet.isC = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINKSET_IS_5BIT_STRING) == 0)
        {
            attr++;

            linkSet.is5Bit = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                linkSet.family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                linkSet.family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                linkSet.family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                linkSet.family = FAMILY_JAPAN;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(haveID);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record linkset info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleLinkSet(const char *el, const char **attr)
{
    if (strcmp(el, ADJ_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                linkSet.adjacent = RESFILE_ParseNum(*attr);
                haveAPC = ITS_TRUE;

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, NI_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                linkSet.ni = (ITS_OCTET)RESFILE_ParseNum(*attr);
                haveNI = ITS_TRUE;

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, LOCAL_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                linkSet.lpc = RESFILE_ParseNum(*attr);
                haveLPC = ITS_TRUE;

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record linkset info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndLinkSet()
{
    ITS_Object ret;

    ITS_C_ASSERT(haveAPC && haveLPC && haveNI);

    ret = ITS_ConstructObject(itsENGINE_LinkSetClass, application,
                              linkSet.adjacent, linkSet.lpc,
                              linkSet.linkSet,
                              linkSet.ni, linkSet.numToStart,
                              linkSet.adjacentSTP, linkSet.isC,
                              linkSet.is5Bit, linkSet.family);

    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleLink(const char *el, const char **attr)
{
    ENGINE_LinkPart link;
    ITS_BOOLEAN haveSet = ITS_FALSE, haveCode = ITS_FALSE,
                havePri = ITS_FALSE;
    ITS_Object ret;
    ITS_Object *list;

    ITS_C_ASSERT(inTransport || curLayer != NULL);
    if (curLayer == NULL)
    {
        list = &thisTrans.links;
    }
    else
    {
        list = &ENGINE_ISS7_LINKS(curLayer);
    }

    memset(&link, 0, sizeof(ENGINE_LinkPart));

    link.initActive = ITS_TRUE;
    link.termFixed = ITS_TRUE;
    link.linkFixed = ITS_TRUE;

    while (*attr)
    {
        if (strcmp(*attr, LINKSET_SET_STRING) == 0)
        {
            attr++;

            link.linkSet = (ITS_OCTET)RESFILE_ParseNum(*attr);
            haveSet = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, ID_STRING) == 0)
        {
            attr++;

            link.linkCode = (ITS_OCTET)RESFILE_ParseNum(*attr);
            haveCode = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, PRIORITY_STRING) == 0)
        {
            attr++;

            link.linkPri = (ITS_OCTET)RESFILE_ParseNum(*attr);
            havePri = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, LINK_INIT_ACTIVE_STRING) == 0)
        {
            attr++;

            link.initActive = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_TERMINAL_FIXED_STRING) == 0)
        {
            attr++;

            link.termFixed = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_FIXED_STRING) == 0)
        {
            attr++;

            link.linkFixed = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_TERMINAL_STRING) == 0)
        {
            attr++;

            link.terminal = (ITS_USHORT)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINK_DATA_LINK_STRING) == 0)
        {
            attr++;

            link.circuit = (ITS_USHORT)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINK_SAAL_LINK_STRING) == 0)
        {
            attr++;

            link.isSAAL = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_LOCAL_STRING) == 0)
        {
            attr++;

            link.isLocal = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                link.family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                link.family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                link.family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                link.family = FAMILY_JAPAN;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(haveSet && haveCode && havePri);

    ret = ITS_ConstructObject(itsENGINE_LinkClass, list,
                              link.linkSet, link.linkCode, link.linkPri,
                              link.initActive, link.termFixed, link.linkFixed,
                              link.terminal, link.circuit,
                              link.isSAAL, link.isLocal, link.family);
    ITS_C_ASSERT(ret != NULL);
}

static ITS_Object curDest = NULL;
static ITS_Object curISUPAttr = NULL;
static ITS_Object curGroup = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record destination info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleDestination(const char *el, const char **attr)
{
    ITS_UINT pc;
    ITS_OCTET ni;
    ITS_INT mtp3, sccp, tcap, tup, dup;
    SS7_Family family;
    const char *isup = NULL;
    ITS_Object ret;

    pc = 0;
    ni = 0;
    family = FAMILY_ANSI;
    mtp3 = ITS_THIRD_GEN;
    isup = NULL;
    sccp = ITS_THIRD_GEN;
    tcap = ITS_THIRD_GEN;
    tup = ITS_THIRD_GEN;
    dup = ITS_THIRD_GEN;

    while (*attr)
    {
        if (strcmp(*attr, PC_STRING) == 0)
        {
            attr++;

            pc = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                family = FAMILY_JAPAN;
            }

            attr++;
        }
        else if (strcmp(*attr, ENI_STRING) == 0)
        {
            attr++;

            ni = (ITS_OCTET)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, DI_MTP3_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                mtp3 = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                mtp3 = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_ISUP_VAR_STRING) == 0)
        {
            attr++;

            isup = *attr;

            attr++;
        }
        else if (strcmp(*attr, DI_SCCP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                sccp = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                sccp = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_TCAP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                tcap = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                tcap = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_TUP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                tup = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                tup = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_DUP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                dup = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                dup = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_DestClass, application,
                              pc, ni, family,
                              mtp3, isup, sccp, tcap, tup, dup);
    ITS_C_ASSERT(ret != NULL);

    curDest = ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleISUPTimer(const char *el, const char **attr)
{
    const char *id = NULL, *value = NULL, *handler = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curISUPAttr != NULL);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            id = *attr;

            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            value = *attr;

            attr++;
        }
        else if (strcmp(*attr, HANDLED_BY_STRING) == 0)
        {
            attr++;

            handler = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_ISUPTimerClass,
                              curISUPAttr,
                              id, value, handler);
    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record circuit group info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCircuitGroup(const char *el, const char **attr)
{
    const char *huntRule = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curDest != NULL);
    ITS_C_ASSERT(curISUPAttr != NULL);

    while (*attr)
    {
        if (strcmp(*attr, HUNT_RULE_STRING) == 0)
        {
            attr++;

            huntRule = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_CircuitGroupClass,
                              curISUPAttr,
                              huntRule);
    ITS_C_ASSERT(ret != NULL);

    curGroup = ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record CIC info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCICs(const char *el, const char **attr)
{
    ITS_Object ret;
    ITS_UINT start = 0, count = 1;

    ITS_C_ASSERT(curDest != NULL);
    ITS_C_ASSERT(curISUPAttr != NULL);
    ITS_C_ASSERT(curGroup != NULL);

    while (*attr)
    {
        if (strcmp(*attr, START_STRING) == 0)
        {
            attr++;

            start = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, COUNT_STRING) == 0)
        {
            attr++;

            count = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_CICsClass,
                              curGroup,
                              start, count);
    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record ISUP attributes info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleISUPAttr(const char *el, const char **attr)
{
    ITS_UINT lpc = 0;
    ITS_UINT sio = 0;
    const char *xchangeType = NULL;
    const char *segmentationSupported = NULL;
    const char *classRec = NULL;
    const char *libName = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curDest != NULL);

    while (*attr)
    {
        if (strcmp(*attr, LPC_STRING) == 0)
        {
            attr++;

            lpc = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, CLASS_REC_STRING) == 0)
        {
            attr++;

            classRec = *attr;

            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, SIO_STRING) == 0)
        {
            attr++;

            sio = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, ISUP_XCHANGE_TYPE_STR) == 0)
        {
            attr++;

            xchangeType = *attr;

            attr++;
        }
        else if (strcmp(*attr, ISUP_SEG_SUPPORT_STR) == 0)
        {
            attr++;

            segmentationSupported = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_ISUPAttrClass,
                              application, curDest,
                              lpc, classRec, libName, sio,
                              xchangeType, segmentationSupported);
    curISUPAttr = ret;
    ITS_C_ASSERT(ret != NULL);
}

ITS_Object curSIPAttr = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handle SIP timer info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleSIPTimer(const char *el, const char **attr)
{
    const char *id = NULL, *value = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curSIPAttr != NULL);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            id = *attr;

            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            value = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_SIPTimerClass,
                              curSIPAttr,
                              id, value);
    ITS_C_ASSERT(ret != NULL);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record SIP attributes info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleSIPAttr(const char *el, const char **attr)
{
    ITS_USHORT UDPPortNo = 0, TCPPortNo = 0;
    const char *ipAddr = NULL;
    ITS_Object ret;

    while (*attr)
    {
        if (strcmp(*attr, SIP_UDPPORTNO_STRING) == 0)
        {
            attr++;

            UDPPortNo = RESFILE_ParseNum(*attr);

            attr++;
        }
        if (strcmp(*attr, SIP_TCPPORTNO_STRING) == 0)
        {
            attr++;

            TCPPortNo = RESFILE_ParseNum(*attr);
    
            attr++;
        } 
        else if (strcmp(*attr, SIP_IPADDR_STRING) == 0)
        {
            attr++;

            ipAddr = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
    ret = ITS_ConstructObject(itsENGINE_SIPAttrClass, application,
                              UDPPortNo, TCPPortNo, ipAddr);
    curSIPAttr = ret;
    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record work item info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleWorkItem(const char *el, const char **attr)
{
    const char *libName = NULL, *userDisp = NULL;
    ITS_BOOLEAN persist = ITS_TRUE;
    ITS_Object tmp;
    ITS_UINT count = 1;

    ITS_C_ASSERT(inItemPool);
    ITS_C_ASSERT(ENGINE_TP_TRANSPORTS(curPool) != NULL);

    tmp = ENGINE_TP_TRANSPORTS(curPool);

    if (strcmp(el, NUM_WORKERS_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                ENGINE_TR_NUM_ASSOCIATES(tmp) = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        return;
    }

    /* has to be a work item record or we're hosed. */
    if (strcmp(el, WORK_ITEM_STRING) != 0)
    {
        return;
    }

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, NREPEAT_STRING) == 0)
            {
                persist = ITS_FALSE;
            }

            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, WDISP_STRING) == 0)
        {
            attr++;

            userDisp = *attr;

            attr++;
        }
        else if (strcmp(*attr, COUNT_STRING) == 0)
        {
            attr++;

            count = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    tmp = ITS_ConstructObject(itsENGINE_WorkItemClass, tmp,
                              persist, count, libName, userDisp);
    ITS_C_ASSERT(tmp != NULL);
}

static ITS_BOOLEAN  inManagement = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record stack management info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleManagement(const char **attr)
{
    const char *libName = NULL;
    const char *mtp3A = NULL, *isupA = NULL, *sccpA = NULL, *gttA = NULL;
    const char *mtp3I = NULL, *isupI = NULL, *sccpI = NULL, *gttI = NULL;
    const char *rcA = NULL, *rcI = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(application != NULL);
    ITS_C_ASSERT(inManagement);

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_MTP3_STRING) == 0)
        {
            attr++;

            mtp3A = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_ISUP_STRING) == 0)
        {
            attr++;

            isupA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_SCCP_STRING) == 0)
        {
            attr++;

            sccpA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_GTT_STRING) == 0)
        {
            attr++;

            gttA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_RC_STRING) == 0)
        {
            attr++;

            rcA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_MTP3_STRING) == 0)
        {
            attr++;

            mtp3I = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_ISUP_STRING) == 0)
        {
            attr++;

            isupI = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_SCCP_STRING) == 0)
        {
            attr++;

            sccpI = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_GTT_STRING) == 0)
        {
            attr++;

            gttI = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_RC_STRING) == 0)
        {
            attr++;

            rcI = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_SS7StackMgmtClass,
                              application, libName,
                              mtp3A, mtp3I, isupA, isupI,
                              sccpA, sccpI, gttA, gttI,
                              rcA, rcI);

    ITS_C_ASSERT(ret != NULL);
}

static ITS_BOOLEAN  inStacks = ITS_FALSE;
static ITS_BOOLEAN  inIntelliNet = ITS_FALSE;
static ITS_BOOLEAN  inCodec = ITS_FALSE;
static ITS_BOOLEAN  inLayer = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record stack info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleStack(const char *el, const char **attr)
{
    const char *name = NULL;
    int variant = ITS_LATEST_GEN;
    int numThreads = 0;

    ITS_C_ASSERT(application != NULL);

    if (strcmp(el, ITU_MTP3_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ITU_ISUP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ITU_SCCP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ITU_TCAP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_MTP3_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_ISUP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_SCCP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_TCAP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, TIMERS_STRING) == 0)
    {
        ITS_C_ASSERT(inLayer);
        ITS_C_ASSERT(curLayer != NULL);

        while (*attr)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%s=%s", attr[0], attr[1]);

            ENGINE_ISS7_NUM_TIMERS(curLayer)++;

            ENGINE_ISS7_TIMERS(curLayer) = (char **)
                                    realloc(ENGINE_ISS7_TIMERS(curLayer),
                                            ENGINE_ISS7_NUM_TIMERS(curLayer) *
                                                sizeof(char *));
            ITS_C_ASSERT(ENGINE_ISS7_TIMERS(curLayer) != NULL);

            ENGINE_ISS7_TIMERS(curLayer)
                [ENGINE_ISS7_NUM_TIMERS(curLayer) - 1] =
                    malloc(strlen(buf) + 1);
            ITS_C_ASSERT(ENGINE_ISS7_TIMERS(curLayer)
                            [ENGINE_ISS7_NUM_TIMERS(curLayer) - 1] != NULL);

            strcpy(ENGINE_ISS7_TIMERS(curLayer)
                    [ENGINE_ISS7_NUM_TIMERS(curLayer) - 1],
                   buf);

            attr += 2;
        }
    }
    else if (strcmp(el, BEHAVIOR_STRING) == 0)
    {
        ITS_C_ASSERT(inLayer);
        ITS_C_ASSERT(curLayer != NULL);

        while (*attr)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%s=%s", attr[0], attr[1]);

            ENGINE_ISS7_NUM_MODIFIERS(curLayer)++;

            ENGINE_ISS7_MODIFIERS(curLayer) = (char **)
                                    realloc(ENGINE_ISS7_MODIFIERS(curLayer),
                                            ENGINE_ISS7_NUM_MODIFIERS(curLayer) *
                                                sizeof(char *));
            ITS_C_ASSERT(ENGINE_ISS7_MODIFIERS(curLayer) != NULL);

            ENGINE_ISS7_MODIFIERS(curLayer)
                [ENGINE_ISS7_NUM_MODIFIERS(curLayer) - 1] =
                    malloc(strlen(buf) + 1);
            ITS_C_ASSERT(ENGINE_ISS7_MODIFIERS(curLayer)
                            [ENGINE_ISS7_NUM_MODIFIERS(curLayer) - 1] != NULL);

            strcpy(ENGINE_ISS7_MODIFIERS(curLayer)
                    [ENGINE_ISS7_NUM_MODIFIERS(curLayer) - 1],
                   buf);

            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Build a parser extension record.
 *
 *  Input Parameters:
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleParserExtension(const char **attr)
{
    const char *libName = NULL, *elemName = NULL;
    const char *start = NULL, *stop = NULL, *xlate = NULL, *diff = NULL;
    ITS_Object ret;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, ELEM_NAME_STRING) == 0)
        {
            attr++;

            elemName = *attr;

            attr++;
        }
        else if (strcmp(*attr, START_FUNC_STRING) == 0)
        {
            attr++;

            start = *attr;

            attr++;
        }
        else if (strcmp(*attr, STOP_FUNC_STRING) == 0)
        {
            attr++;

            stop = *attr;

            attr++;
        }
        else if (strcmp(*attr, XLATE_FUNC_STRING) == 0)
        {
            attr++;

            xlate = *attr;

            attr++;
        }
        else if (strcmp(*attr, DIFF_FUNC_STRING) == 0)
        {
            attr++;

            diff = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_ParserExtensionClass,
                              application, libName, elemName,
                              start, stop, xlate, diff);

    ITS_C_ASSERT(ret != NULL);
}

static ITS_BOOLEAN inExtension = ITS_FALSE;
static ENGINE_ParserExtension curExt = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element start function for parser unknown symbols
 *
 *  Input Parameters:
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleExtensionStart(const char *el, const char **attr)
{
    
    if (inExtension)
    {
        ITS_C_ASSERT(curExt != NULL);
    }
    else
    {
        ITS_Object tmp;

        for (tmp = ENGINE_APP_PARSER_EXTENSIONS(application);
             tmp != NULL;
             tmp = ENGINE_PE_NEXT(tmp))
        {
            if (strcmp(ENGINE_PE_ELEMENT_NAME(tmp), el) == 0)
            {
                curExt = (ENGINE_ParserExtension)tmp;
                inExtension = ITS_TRUE;

                break;
            }
        }

        if (tmp == NULL)
        {
            return;
        }
    }
    if (ENGINE_PE_START_FUNC(curExt))
    {
        const char** temp = attr;
        int count = 0;
        ENGINE_PE_ELEMENT_DATA_COUNT(curExt) = 0;

        while (*temp)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%s=\"%s\"", temp[0], temp[1]);
            count++;
            ENGINE_PE_ELEMENT_DATA(curExt) = (char **)
                                    realloc(ENGINE_PE_ELEMENT_DATA(curExt),
                                            count * sizeof(char *));
            ITS_C_ASSERT(ENGINE_PE_ELEMENT_DATA(curExt) != NULL);

            ENGINE_PE_ELEMENT_DATA(curExt) [count-1] = malloc(strlen(buf) + 1);
            ITS_C_ASSERT(ENGINE_PE_ELEMENT_DATA(curExt)[count-1] != NULL);

            strcpy(ENGINE_PE_ELEMENT_DATA(curExt)[count-1], buf);

            temp += 2;
        }

        ENGINE_PE_ELEMENT_DATA_COUNT(curExt) = count;
        ENGINE_PE_START_FUNC(curExt)(curExt, el, attr);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element stop function for parser unknown symbols
 *
 *  Input Parameters:
 *      el - the element
 *
 ****************************************************************************/
static void
HandleExtensionStop(const char *el)
{
    if (!inExtension)
    {
        return;
    }

    ITS_C_ASSERT(curExt != NULL);

    if (ENGINE_PE_STOP_FUNC(curExt))
    {
        ENGINE_PE_STOP_FUNC(curExt)(curExt, el);
    }

    if (strcmp(ENGINE_PE_ELEMENT_NAME(curExt), el) == 0)
    {
        curExt = NULL;
        inExtension = ITS_FALSE;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element start function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
void
ENGINE_ElementStart(void *data, const char *el, const char **attr)
{
    if (strcmp(el, APPL_STRING) == 0)
    {
        HandleApplication(attr);
    }
    else if (strcmp(el, OPTIONS_STRING) == 0)
    {
        HandleOption(attr);
    }
    else if (strcmp(el, FAULT_TOLERANCE_STRING) == 0)
    {
        inFaultTolerance = ITS_TRUE;
        StartFaultTolerance(attr);
    }
    else if (strcmp(el, FTM_PRE_EXEC_LOGIC_PROC_STRING) == 0)
    {
        HandleFtmPreExecuteLogicProcedure(attr);
    }
    else if (strcmp(el, FTM_LOOP_EXEC_LOGIC_PROC_STRING) == 0)
    {
        HandleFtmLoopExecuteLogicProcedure(attr);
    }
    else if (strcmp(el, FTM_POST_EXEC_LOGIC_PROC_STRING) == 0)
    {
        HandleFtmPostExecuteLogicProcedure(attr);
    }
    else if (strcmp(el, MB_CHANGE_ALL_FT_GRPS_CB_STRING) == 0)
    {
        HandleMembershipChangeAllFtGroupsCallback(attr);
    }
    else if (strcmp(el, EVT_FR_ALL_FT_GRP_MBS_CB_STRING) == 0)
    {
        HandleEventFromAllFtGroupMembersCallback(attr);
    }
    else if (strcmp(el, FT_GRP_STRING) == 0)
    {
        inFtGroup = ITS_TRUE;
        StartFtGroup(attr);
    }
    else if (strcmp(el, DSM_CFG_STRING) == 0)
    {
        HandleDsmConfig(attr);
    }
    else if (strcmp(el, FT_GRP_MB_STRING) == 0)
    {
        HandleFtGroupMember(attr);
    }
    else if (strcmp(el, MASTER_FT_GRP_MB_STRING) == 0)
    {
        HandleMasterFtGroupMember(attr);
    }
    else if (strcmp(el, MB_CHANGE_CB_STRING) == 0)
    {
        HandleMembershipChangeCallback(attr);
    }
    else if (strcmp(el, EVT_FR_FT_GRP_MB_CB_STRING) == 0)
    {
        HandleEventFromFtGroupMemberCallback(attr);
    }
    /**/
    else if (strcmp(el, WINDOWS_STRING) == 0)
    {
        inWindows = ITS_TRUE;
    }
    else if (strcmp(el, NET_HOME_STRING) == 0)
    {
        if (inWindows)
        {
            HandleWindows(attr);
        }
    }
    else if (strcmp(el, FEATURE_STRING) == 0)
    {
        inFeature = ITS_TRUE;
        StartFeature(attr);
    }
    else if (strcmp(el, FEAT_OPTION_STRING) == 0)
    {
        HandleFeatureOption(attr);
    }
    else if (strcmp(el, TK_TRACE_STRING) == 0)
    {
        tkTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, APP_TRACE_STRING) == 0)
    {
        appTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, STACK_TRACE_STRING) == 0)
    {
        stackTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, CRIT_STRING) == 0)
    {
        if (tkTrace || appTrace || stackTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, ERR_STRING) == 0)
    {
        if (tkTrace || appTrace || stackTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, WARN_STRING) == 0)
    {
        if (tkTrace || appTrace || stackTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, DBG_STRING) == 0)
    {
        if (tkTrace || appTrace || stackTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, WORK_POOL_STRING) == 0)
    {
        inWorkPool = ITS_TRUE;
        StartPool(el, attr);
    }
    else if (strcmp(el, ITEM_POOL_STRING) == 0)
    {
        inItemPool = ITS_TRUE;
        StartPool(el, attr);
    }
    else if (strcmp(el, BORDER_POOL_STRING) == 0)
    {
        inBorderPool = ITS_TRUE;
        StartPool(el, attr);
    }
    else if (strcmp(el, TRANSPORT_STRING) == 0)
    {
        inTransport = ITS_TRUE;
        StartTransport(attr);
    }
    else if (strcmp(el, CUSTOM_DISP_STRING) == 0)
    {
        HandleCustomDispatch(attr);
    }
    else if (strcmp(el, CALLBACK_STRING) == 0)
    {
        if (inTransport)
        {
            HandleCallbacks(attr);
        }
    }
    else if (strcmp(el, MODIFIER_STRING) == 0)
    {
        HandleModifier(attr);
    }
    else if (strcmp(el, ROUTE_STRING) == 0)
    {
        inRoute = ITS_TRUE;
        StartRoute(attr);
    }
    else if (strcmp(el, WORK_ITEM_STRING) == 0)
    {
        HandleWorkItem(el, attr);
    }
    else if (strcmp(el, NUM_WORKERS_STRING) == 0)
    {
        HandleWorkItem(el, attr);
    }
    else if (strcmp(el, STACKS_STRING) == 0)
    {
        inStacks = ITS_TRUE;
    }
    else if (strcmp(el, MGMT_CBS_STRING) == 0)
    {
        inManagement = ITS_TRUE;
        HandleManagement(attr);
    }
    else if (strcmp(el, INTELLINET_STRING) == 0)
    {
        inIntelliNet = ITS_TRUE;
    }
    else if (strcmp(el, CODEC_STRING) == 0)
    {
        inCodec = ITS_TRUE;
    }
    else if (strcmp(el, PEXT_STRING) == 0)
    {
        HandleParserExtension(attr);
    }
    else if (strcmp(el, LINK_SET_STRING) == 0)
    {
        inLinkSet = ITS_TRUE;
        StartLinkSet(el, attr);
    }
    else if (strcmp(el, LINK_STRING) == 0)
    {
        HandleLink(el, attr);
    }
    else if (strcmp(el, DEST_STRING) == 0)
    {
        HandleDestination(el, attr);
    }
    else if (strcmp(el, ISUP_ATTR_STRING) == 0)
    {
        HandleISUPAttr(el, attr);
    }
    else if (strcmp(el, CIRC_GRP_STRING) == 0)
    {
        HandleCircuitGroup(el, attr);
    }
    else if (strcmp(el, CIRC_CODE_STRING) == 0)
    {
        HandleCICs(el, attr);
    }
    else if (strcmp(el, TIMER_STRING) == 0)
    {
        HandleISUPTimer(el, attr);
    }
    else if (inRoute)
    {
        HandleRoute(el, attr);
    }
    else if (inTransport)
    {
        HandleTransport(el, attr);
    }
    else if (inStacks && inIntelliNet)
    {
        HandleStack(el, attr);
    }
    else if (inLinkSet)
    {
        HandleLinkSet(el, attr);
    }
    else if (strcmp(el, SIP_ATTR_STRING) == 0)
    {
        HandleSIPAttr(el, attr);
    }
    else if (strcmp(el, SIP_TIMERS_STRING) == 0)
    {
        HandleSIPTimer(el, attr);
    }
    else
    {
        HandleExtensionStart(el, attr);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element end function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
void
ENGINE_ElementEnd(void *data, const char *el)
{
    if (strcmp(el, FAULT_TOLERANCE_STRING) == 0)
    {
        EndFaultTolerance();
        inFaultTolerance = ITS_FALSE;
    }
    else if (strcmp(el, FT_GRP_ID_STRING) == 0)
    {
        EndFtGroup();
        inFtGroup = ITS_FALSE;
    }
    else if (strcmp(el, WINDOWS_STRING) == 0)
    {
        inWindows = ITS_FALSE;
    }
    else if (strcmp(el, FEATURE_STRING) == 0)
    {
        EndFeature();
        inFeature = ITS_FALSE;
    }
    else if (strcmp(el, TK_TRACE_STRING) == 0)
    {
        EndTrace();
        tkTrace = ITS_FALSE;
    }
    else if (strcmp(el, APP_TRACE_STRING) == 0)
    {
        EndTrace();
        appTrace = ITS_FALSE;
    }
    else if (strcmp(el, STACK_TRACE_STRING) == 0)
    {
        EndTrace();
        stackTrace = ITS_FALSE;
    }
    else if (strcmp(el, WORK_POOL_STRING) == 0)
    {
        EndPool(el);
        inWorkPool = ITS_FALSE;
    }
    else if (strcmp(el, ITEM_POOL_STRING) == 0)
    {
        EndPool(el);
        inItemPool = ITS_FALSE;
    }
    else if (strcmp(el, BORDER_POOL_STRING) == 0)
    {
        EndPool(el);
        inBorderPool = ITS_FALSE;
    }
    else if (strcmp(el, TRANSPORT_STRING) == 0)
    {
        EndTransport();
        inTransport = ITS_FALSE;
    }
    else if (strcmp(el, ROUTE_STRING) == 0)
    {
        EndRoute();
        inRoute = ITS_FALSE;
    }
    else if (strcmp(el, DEST_STRING) == 0)
    {
        curDest = NULL;
    }
    else if (strcmp(el, CIRC_GRP_STRING) == 0)
    {
        curGroup = NULL;
    }
    else if (strcmp(el, ISUP_ATTR_STRING) == 0)
    {
        curISUPAttr = NULL;
    }
    else if (strcmp(el, STACKS_STRING) == 0)
    {
        inStacks = ITS_FALSE;
    }
    else if (strcmp(el, MGMT_CBS_STRING) == 0)
    {
        ITS_C_ASSERT(inStacks);
        inManagement = ITS_FALSE;
    }
    else if (strcmp(el, LINK_SET_STRING) == 0)
    {
        inLinkSet = ITS_FALSE;
        EndLinkSet();
    }
    else if (strcmp(el, INTELLINET_STRING) == 0)
    {
        inIntelliNet = ITS_FALSE;
    }
    else if (strcmp(el, CODEC_STRING) == 0)
    {
        inCodec = ITS_FALSE;
    }
    else if (strcmp(el, ITU_MTP3_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ITU_ISUP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ITU_SCCP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ITU_TCAP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_MTP3_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_ISUP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_SCCP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_TCAP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, SIP_ATTR_STRING) == 0)
    {
        /* curSIPAttr = NULL; */
    }
    else
    {
        HandleExtensionStop(el);
    }
}

