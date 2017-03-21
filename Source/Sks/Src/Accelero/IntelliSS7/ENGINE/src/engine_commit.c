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
 *  ID: $Id: engine_commit.c,v 1.1.1.1 2007-10-08 11:11:16 bsccs2 Exp $
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
 * LOG: Revision 9.4  2005/05/10 14:17:58  mmanikandan
 * LOG: Validation Bug Fix (Bug 1793, 1823).
 * LOG:
 * LOG: Revision 9.3  2005/05/06 09:07:52  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:37:22  mmanikandan
 * LOG: Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:19  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.8  2005/03/21 13:49:21  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.7.2.1.6.3  2005/02/25 13:05:49  mmanikandan
 * LOG: Validation bugs are resolved.
 * LOG:
 * LOG: Revision 1.7.2.1.6.2  2005/01/18 13:03:44  mmanikandan
 * LOG: printf statements are removed.
 * LOG:
 * LOG: Revision 1.7.2.1.6.1  2005/01/05 07:21:23  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 1.7.2.1  2004/09/15 05:24:51  mmanikandan
 * LOG: Initial commit in 6.4.1 branch.
 * LOG:
 *
 ****************************************************************************/ 

#include <its.h>
#include <engine.h>
#include <vframe.h>
#include <engine_intern.h>
#include <its_trace.h>

FILE* tempfp;
int tab = 0;
VENDOR_Class ven = NULL;
VENDOR_Class mtp2ven = NULL;

Sig_Callback  sctpCallback = NULL;
Sig_Callback  ualCallback = NULL;
Sig_Callback  m2uaCallback = NULL;
Sig_Callback  m3uaCallback = NULL;

static ITS_CHAR *Route_Types[] =
{
    "",
    ROUTE_TYPE_LOCAL_STRING,
    ROUTE_TYPE_REMOTE_STRING,
    ROUTE_TYPE_CONCERNED_STRING,
    ROUTE_TYPE_DUPLICATE_STRING,
    ROUTE_TYPE_ROUTING_KEY_STRING,
    NULL 
};

static ITS_CHAR* Route_Styles[] =
{
    ROUTE_STYLE_DPC_NI_STRING,
    ROUTE_STYLE_DPC_OPC_NI_STRING,
    ROUTE_STYLE_DPC_SIO_STRING,
    ROUTE_STYLE_DPC_OPC_SIO_STRING,
    ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING,
    ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING,
    ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING,
    ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING,
    ROUTE_STYLE_DPC_SIO_SSN_STRING,
    ROUTE_STYLE_DPC_SIO_CIC_STRING,
    ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING,
    ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING,
    ROUTE_STYLE_DPC_UDEF_STRING,
    NULL
};

static ITS_CHAR* SS7_FamilyStr[] =
{
    FAMILY_ANSI_STRING,
    FAMILY_CCITT_STRING,
    FAMILY_CHINA_STRING,
    FAMILY_JAPAN_STRING,
    NULL
};

static ITS_CHAR* itu_variant[] =
{
    "",
    "BlueBook",
    "WhiteBook",
    "WhiteBook_97",
    NULL
};

static ITS_CHAR* ansi_variant[] =
{
    "",
    "ANSI-88",
    "ANSI-92",
    "ANSI-96",
    NULL
};

const ITS_CHAR* GetFTCallback(int i)
{
    if (i == FT_CALLBACK_MEMBERSHIP_CHANGE_ALL_FT_GROUPS)
    {
        return MB_CHANGE_ALL_FT_GRPS_CB_STRING;
    }
    else if (i == FT_CALLBACK_EVENT_FROM_ALL_FT_GROUP_MEMBERS)
    {
        return EVT_FR_ALL_FT_GRP_MBS_CB_STRING;
    }
    else if (i == FT_CALLBACK_MEMBERSHIP_CHANGE)
    {
        return MB_CHANGE_CB_STRING;
    }
    else if (i == FT_CALLBACK_EVENT_FROM_FT_GROUP_MEMBER)
    {
        return EVT_FR_FT_GRP_MB_CB_STRING;
    }
    else
    {
        return "";
    }
}
 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Using mask this will identify the global start and 
 *      copy into str as string.
 *
 *  Input Parameters:
 *      int mask, char** str.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005  Bug ID:1783, 1791
 *
 ****************************************************************************/

static void 
GetGlobalStart(int mask, char* str)
{
    if ((mask & ITS_MTP3_ANSI) == ITS_MTP3_ANSI)
    {
        strcat(str,ANSI_MTP3_STRING);
        strcat(str," +");
    }

    if ((mask & ITS_TCAP_PRC) == ITS_TCAP_PRC)
    {
        strcat(str,"PRC-TCAP +");
    }

    if ((mask & ITS_SCCP_PRC) == ITS_SCCP_PRC)
    {
        strcat(str,"PRC-SCCP +");
    }

    if ((mask & ITS_ISUP_PRC) == ITS_ISUP_PRC)
    {
        strcat(str,"PRC-ISUP +");
    }

    if ((mask & ITS_MTP3_PRC) == ITS_MTP3_PRC)
    {
        strcat(str,"PRC-MTP3 +");
    }

    if ((mask & ITS_TCAP_CCITT) == ITS_TCAP_CCITT)
    {
        strcat(str,ITU_TCAP_STRING);
        strcat(str," +");
    }

    if ((mask & ITS_SCCP_CCITT) == ITS_SCCP_CCITT)
    {
        strcat(str,ITU_SCCP_STRING);
        strcat(str," +");
    }

    if ((mask & ITS_ISUP_CCITT) == ITS_ISUP_CCITT)
    {
        strcat(str,ITU_ISUP_STRING);
        strcat(str," +");
    }

    if ((mask & ITS_MTP3_CCITT) == ITS_MTP3_CCITT)
    {
        strcat(str,ITU_MTP3_STRING);
        strcat(str," +");
    }

    if ((mask & ITS_TCAP_ANSI) == ITS_TCAP_ANSI)
    {
        strcat(str,ANSI_TCAP_STRING);
        strcat(str," +");
    }

    if ((mask & ITS_SCCP_ANSI) == ITS_SCCP_ANSI)
    {
        strcat(str,ANSI_SCCP_STRING);
        strcat(str," +");
    }

    if ((mask & ITS_ISUP_ANSI) == ITS_ISUP_ANSI)
    {
        strcat(str,ANSI_ISUP_STRING);
        strcat(str," +");
    }

    if (strlen(str) > 2)
    {
        str[strlen(str)-2] = '\0'; 
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the call back function names in the file.
 *
 *  Input Parameters:
 *      ENGINE_TransportCallbacksRec* cb.
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
SaveCallBacks(ENGINE_TransportCallbacksRec* cb)
{
    if ((cb == NULL) || (tempfp == NULL)) 
    {
        return;
    }

    fprintf(tempfp, "%*c<%s \n", tab*8, ' ', CALLBACK_STRING); 

    if (ENGINE_TC_LIB_NAME(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s         = \"%s\"\n",
                tab*8, ' ', LIBRARY_STRING, ENGINE_TC_LIB_NAME(cb));
    }

    if (ENGINE_TC_HANDLER_TYPE(cb) == DISP_PROT_DBC) 
    {
        fprintf(tempfp, 
                "%*c           %s            = \"debug-console\"\n",
                tab*8, ' ', TYPE_STRING);
    }
    else
    {
        fprintf(tempfp, 
                "%*c           %s            = \"%s\"\n",
                tab*8, ' ', TYPE_STRING,
                (ENGINE_TC_TYPE(cb) == DISP_NON_BLOCKING)? 
                "non-blocking" : "blocking");
    }

    if (ENGINE_TC_PRE_INIT(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s   = \"%s\"\n",
                tab*8, ' ', PRE_INIT_STRING, ENGINE_TC_PRE_INIT(cb));
    }

    if (ENGINE_TC_POST_INIT(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s  = \"%s\"\n",
                tab*8, ' ', POST_INIT_STRING, ENGINE_TC_POST_INIT(cb));
    }

    if (ENGINE_TC_PRE_NEXT_EVENT(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s    = \"%s\"\n",
                tab*8, ' ', PRE_NEXT_STRING, ENGINE_TC_PRE_NEXT_EVENT(cb));
    }

    if (ENGINE_TC_NEXT_EVENT_FAIL(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s = \"%s\"\n",
                tab*8, ' ', NEXT_FAIL_STRING, ENGINE_TC_NEXT_EVENT_FAIL(cb));
    }

    if (ENGINE_TC_POST_NEXT_EVENT(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s   = \"%s\"\n",
                tab*8, ' ', POST_NEXT_STRING, ENGINE_TC_POST_NEXT_EVENT(cb));
    }

    if (ENGINE_TC_DISP_USER(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s  = \"%s\"\n",
                tab*8, ' ', UDISP_STRING, ENGINE_TC_DISP_USER(cb));
    }

    if (ENGINE_TC_DISP_SCCP(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s  = \"%s\"\n",
                tab*8, ' ', SDISP_STRING, ENGINE_TC_DISP_SCCP(cb));
    }

    if (ENGINE_TC_DISP_ISUP(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s  = \"%s\"\n",
                tab*8, ' ', IDISP_STRING, ENGINE_TC_DISP_ISUP(cb));
    }

    if (ENGINE_TC_PRE_ACCEPT(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s       = \"%s\"\n",
                tab*8, ' ', PRE_ACCEPT_STRING, ENGINE_TC_PRE_ACCEPT(cb));
    }

    if (ENGINE_TC_ON_ACCEPT(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s        = \"%s\"\n",
                tab*8, ' ', ON_ACCEPT_STRING, ENGINE_TC_ON_ACCEPT(cb));
    }

    if (ENGINE_TC_PRE_TERM(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s    = \"%s\"\n",
                tab*8, ' ', PRE_TERM_STRING, ENGINE_TC_PRE_TERM(cb));
    }

    if (ENGINE_TC_POST_TERM(cb) != NULL)
    {
        fprintf(tempfp, 
                "%*c           %s   = \"%s\"\n",
                tab*8,' ',POST_TERM_STRING, ENGINE_TC_POST_TERM(cb));
    }

    fprintf(tempfp, "%*c/>\n", tab*8, ' ');
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the app options in the file.
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
SaveAppOptions()
{
    int options = 0, i;
    char appOptions[ITS_PATH_MAX];
    char* value;
    options = ENGINE_APP_NUM_OPTIONS(application);

    for(i = 0; i < options; i++)
    {
        strcpy(appOptions, ENGINE_APP_OPTIONS(application)[i]);
        value = strstr(appOptions,"=");
        *value = '\0';

        if (strcmp(appOptions,LOCAL_INTERFACE_STRING) == 0)
        {
            fprintf(tempfp, "\t<%s>\n", WINDOWS_STRING);
            fprintf(tempfp, "\t\t<%s\n", NET_HOME_STRING);
            fprintf(tempfp, "\t\t\t%s = ", appOptions);
            *value = '=';
            value++;  
            fprintf(tempfp, "\"%s\"\n", value); 
        }
        else if (strcmp(appOptions,LOCAL_MASK_STRING) == 0)
        {
            fprintf(tempfp, "\t\t\t%s = ", appOptions);
            *value = '=';
            value++;
            fprintf(tempfp, "\"%s\"\n", value);
        } 
        else if (strcmp(appOptions,LOCAL_BCAST_STRING) == 0)
        {
            fprintf(tempfp, "\t\t\t%s = ", appOptions);
            *value = '=';
            value++;
            fprintf(tempfp, "\"%s\" />\n", value);
            fprintf(tempfp, "\t</%s>\n", WINDOWS_STRING);
        }
        else
        {
            fprintf(tempfp, 
                    "\t<%s name = \"%s\"\n",
                    OPTIONS_STRING, appOptions);
            *value = '=';
            value++;
            fprintf(tempfp, "\t            value = \"%s\"/>\n", value);
        } 
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the features in the file.
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
SaveFeature()
{
    int options,i;
    char featOptions[ITS_PATH_MAX];
    char* value;
    ENGINE_FeatureRec* fpr = 
        (ENGINE_FeatureRec *)ENGINE_APP_FEATURES(application);

    while (fpr != NULL)
    {
        fprintf(tempfp, 
                "\t<%s %s     = \"%s\"\n",
                FEATURE_STRING, NAME_STRING, ENGINE_FEAT_NAME(fpr));

        if (ENGINE_FEAT_LIB_CACHE_ENTRY(fpr)->libCache.libName != NULL)
        {
            fprintf(tempfp, 
                    "\t         %s  = \"%s\"\n",
                    LIBRARY_STRING, 
                    ENGINE_FEAT_LIB_CACHE_ENTRY(fpr)->libCache.libName);
        }

        fprintf(tempfp, 
                "\t         %s = \"%s\">\n",
                CLASS_REC_STRING,ENGINE_FEAT_CLASS_NAME(fpr));

        if ((strcmp(ENGINE_FEAT_CLASS_NAME(fpr),
                    "itsINTELLISS7_ClassCCITT") == 0) ||
            (strcmp(ENGINE_FEAT_CLASS_NAME(fpr),
                    "itsINTELLISS7_ClassANSI") == 0))
        {
            ven = (VENDOR_Class)ENGINE_FEAT_CLASS_REC(fpr);
        }
        else if ((strcmp(ENGINE_FEAT_CLASS_NAME(fpr),
                    "itsNMS_ClassCCITT") == 0) ||
            (strcmp(ENGINE_FEAT_CLASS_NAME(fpr),
                    "itsNMS_ClassANSI") == 0))
        {
            mtp2ven = (VENDOR_Class)ENGINE_FEAT_CLASS_REC(fpr);
        }

        options = ENGINE_FEAT_NUM_OPTIONS(fpr);

        for(i = 0;i < options; i++)
        {
            strcpy(featOptions, ENGINE_FEAT_OPTIONS(fpr)[i]);
            value = strstr(featOptions,"=");
            *value = '\0';
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%s\" ",
                    FEAT_OPTION_STRING,NAME_STRING,featOptions);
            *value = '=';
            value++;
            fprintf(tempfp, " %s = \"%s\"/>\n", VALUE_STRING, value);
        }

        fprintf(tempfp, "\t</%s>\n", FEATURE_STRING);
        fpr = (ENGINE_FeatureRec*)ENGINE_FEAT_NEXT(fpr);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the fault tolerance in the file.
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
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1633   Printing DsmGcs configuration for STUB
 *                                                    is removed.
 *  Mani   05-05-2005    Bug ID:1789,1796  Printing of Parser Extension Data is
 *                                                   Modified.
 *
 ****************************************************************************/

static void 
SaveFT()
{
    ENGINE_TransportCallbacksRec* cb = NULL;
    ENGINE_FtGroupRec* ftg = NULL;
    ENGINE_FtGroupMemberRec* ftgm = NULL;
    ENGINE_FaultTolerance* ft =
        (ENGINE_FaultTolerance*)ENGINE_APP_FAULT_TOLERANCE(application);
    ENGINE_ParserExtensionRec* pe = NULL;
    int elemCount = 0;
    char** temp = NULL;
    ENGINE_FtCallback ftcb = NULL;

    if ((ft == NULL) || (tempfp == NULL))
    {
        return;
    }

    fprintf(tempfp, 
            "\t<%s %s    = \"%d\"\n",
            FAULT_TOLERANCE_STRING, MAX_NUM_FT_GRPS_STRING,
            ENGINE_FT_MAX_NUM_FT_GROUPS(ft));
    fprintf(tempfp, 
            "\t                %s   = \"%d\"\n",
            MAX_NUM_PROCS_STRING, ENGINE_FT_MAX_NUM_PROCESSES(ft));
    fprintf(tempfp, 
            "\t                %s       = \"%d\"\n",
            MAX_NUM_NODES_STRING, ENGINE_FT_MAX_NUM_NODES(ft));
    fprintf(tempfp, 
            "\t                %s            = \"%d\"\n",
            NODE_ID_STRING, ENGINE_FT_NODE_ID(ft));
    fprintf(tempfp, 
            "\t                %s         = \"%d\"\n",
            PROC_ID_STRING, ENGINE_FT_PROCESS_ID(ft));
    fprintf(tempfp, 
            "\t                %s     = \"%d\"\n",
            TCAP_FT_GRP_ID_STRING, ENGINE_FT_TCAP_FT_GROUP_ID(ft));
    fprintf(tempfp, 
            "\t                %s     = \"%d\"\n",
            SCCP_FT_GRP_ID_STRING, ENGINE_FT_SCCP_FT_GROUP_ID(ft));
    fprintf(tempfp, 
            "\t                %s     = \"%d\"\n",
            MTP3_FT_GRP_ID_STRING, ENGINE_FT_MTP3_FT_GROUP_ID(ft));
    fprintf(tempfp, 
            "\t                %s     = \"%d\"\n",
            ISUP_FT_GRP_ID_STRING, ENGINE_FT_ISUP_FT_GROUP_ID(ft));
    fprintf(tempfp, 
            "\t                %s  = \"%d\"\n",
            ROUTING_FT_GRP_ID_STRING, ENGINE_FT_ROUTING_FT_GROUP_ID(ft));
    fprintf(tempfp, 
            "\t                %s   = \"%d\"\n",
            TIMERS_FT_GRP_ID_STRING, ENGINE_FT_TIMERS_FT_GROUP_ID(ft));
    fprintf(tempfp, 
            "\t                %s = \"%d\">\n",
            MGMT_DATA_FT_GRP_ID_STRING, ENGINE_FT_MGMT_DATA_FT_GROUP_ID(ft));
    fprintf(tempfp, "\t\t<%s>\n",PROCS_STRING);

    if (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        fprintf(tempfp, 
                "\t\t\t<%s %s = \"%s\" %s = \"%s\" />\n",
                FTM_PRE_EXEC_LOGIC_PROC_STRING, 
                LIBRARY_STRING, FUNCTION_STRING,
                ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft),
                (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) == NULL)? 
                    "" : ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    if (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        fprintf(tempfp, 
                "\t\t\t<%s %s = \"%s\" %s = \"%s\" />\n",
                FTM_LOOP_EXEC_LOGIC_PROC_STRING, 
                LIBRARY_STRING, FUNCTION_STRING,
                ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft),
                (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) == NULL)? 
                    "" : ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    if (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        fprintf(tempfp, 
                "\t\t\t<%s %s = \"%s\" %s = \"%s\" />\n",
                FTM_POST_EXEC_LOGIC_PROC_STRING, 
                LIBRARY_STRING, FUNCTION_STRING,
                ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft),
                (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) == NULL)? 
                    "" : ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    fprintf(tempfp, "\t\t</%s>\n", PROCS_STRING);
    cb = (ENGINE_TransportCallbacksRec*)ENGINE_FT_CALLBACKS(ft);
    tab = 2;
    SaveCallBacks(cb);
    tab = 0;
    fprintf(tempfp, "\t\t<%s>\n", FT_GRPS_STRING);
    ftg = (ENGINE_FtGroupRec*)ENGINE_FT_FT_GROUPS(ft);

    while (ftg != NULL)
    {
        fprintf(tempfp, 
                "\t\t\t<%s %s = \"%d\" %s = \"%s\">\n",
                FT_GRP_STRING, FT_GRP_ID_STRING,
                ENGINE_FT_GROUP_FT_GROUP_ID(ftg), FT_GRP_NAME_STRING, 
                (ENGINE_FT_GROUP_FT_GROUP_NAME(ftg) == NULL)? 
                    "" : ENGINE_FT_GROUP_FT_GROUP_NAME(ftg));
        fprintf(tempfp, 
                "\t\t\t\t<%s %s         = \"%d\"\n",
                DSM_CFG_STRING, DSM_SIZE_STRING, 
                ENGINE_FT_GROUP_DSM_SIZE(ftg));
        fprintf(tempfp, 
                "\t\t\t\t           %s  = \"%s\"\n",
                DSM_BASE_ADDR_STRING,
                (ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftg) == NULL)? 
                    "" : ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftg));
        fprintf(tempfp, 
                "\t\t\t\t           %s = \"%d\"\n",
                DSM_MAX_NUM_TBLS_STRING, 
                ENGINE_FT_GROUP_DSM_MAX_NUM_TABLES(ftg));
        fprintf(tempfp, 
                "\t\t\t\t           %s         = \"%s\" />\n",
                DSM_TYPE_STRING,
                (ENGINE_FT_GROUP_DSM_TYPE(ftg) == NULL)? 
                    "" : ENGINE_FT_GROUP_DSM_TYPE(ftg));

        pe = (ENGINE_ParserExtensionRec*)
                 ENGINE_APP_PARSER_EXTENSIONS(application);

        while (pe)
        {
            if ((strcmp(ENGINE_FT_GROUP_DSM_TYPE(ftg), "GCS") == 0) &&
                (strcmp(ENGINE_PE_ELEMENT_NAME(pe),"DsmGcsConfig") == 0))
            {
                elemCount = ENGINE_PE_ELEMENT_DATA_COUNT(pe);

                if (elemCount > 0)
                {
                    int iCnt = 0;

                    fprintf(tempfp, "\t\t\t\t<%s\n",ENGINE_PE_ELEMENT_NAME(pe));
                    temp = ENGINE_PE_ELEMENT_DATA(pe);

                    for (;iCnt < elemCount;iCnt++)
                    {
                        fprintf(tempfp, "\t\t\t\t\t%s\n", *temp);
                        temp++;
                    }

                    fprintf(tempfp, "\t\t\t\t/>\n");
                }
            }

            pe = (ENGINE_ParserExtensionRec*)ENGINE_PE_NEXT(pe);
        }

        fprintf(tempfp, "\t\t\t\t<%s>\n", FT_GRP_MBS_STRING);
        ftgm = (ENGINE_FtGroupMemberRec*)ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftg);

        while (ftgm != NULL)
        {
            fprintf(tempfp, 
                    "\t\t\t\t\t<%s %s      = \"%d\"\n",
                    FT_GRP_MB_STRING, NODE_ID_STRING,
                    ENGINE_FT_GROUP_MEMBER_NODE_ID(ftgm));

            if (ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftgm) != NULL)
            {
                fprintf(tempfp, 
                        "\t\t\t\t\t               %s    = \"%s\"\n",
                        NODE_NAME_STRING, 
                        ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftgm));
            }

            fprintf(tempfp, 
                    "\t\t\t\t\t               %s   = \"%d\"\n",
                    PROC_ID_STRING, 
                    ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftgm));

            if (ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftgm) != NULL)
            {
                fprintf(tempfp, 
                        "\t\t\t\t\t               %s = \"%s\" />\n",
                        PROC_NAME_STRING, 
                        ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftgm));
            }

            ftgm = (ENGINE_FtGroupMemberRec*)ENGINE_FT_GROUP_MEMBER_NEXT(ftgm);
        }

        fprintf(tempfp, "\t\t\t\t</%s>\n", FT_GRP_MBS_STRING);
        fprintf(tempfp, "\t\t\t\t<%s>\n", MASTER_FT_GRP_MBS_STRING);
        ftgm = (ENGINE_FtGroupMemberRec*)ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftg);

        if (ftgm)
        {
            ftgm = (ENGINE_FtGroupMemberRec*)ENGINE_FT_GROUP_MEMBER_NEXT(ftgm);
        }

        while (ftgm != NULL)
        {
            if ((ENGINE_FT_GROUP_MEMBER_NODE_ID(ftgm) > 0) && 
                (ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftgm) > 0))
            {
                fprintf(tempfp, 
                        "\t\t\t\t\t<%s %s      = \"%d\"\n",
                        MASTER_FT_GRP_MB_STRING, NODE_ID_STRING,
                        ENGINE_FT_GROUP_MEMBER_NODE_ID(ftgm));
                fprintf(tempfp,
                        "\t\t\t\t\t                     %s   = \"%d\" />\n",
                        PROC_ID_STRING, 
                        ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftgm));
            }

            ftgm = (ENGINE_FtGroupMemberRec*)ENGINE_FT_GROUP_MEMBER_NEXT(ftgm);
        }

        fprintf(tempfp, "\t\t\t\t</%s>\n", MASTER_FT_GRP_MBS_STRING);

        ftcb = (ENGINE_FtCallback)ENGINE_FT_GROUP_FT_CALLBACKS(ftg);

        if (ftcb != NULL)
        {
            fprintf(tempfp,"\t\t\t\t<%s>\n",CALLBACK_STRING);

            while (ftcb)
            {
                fprintf(tempfp,"\t\t\t\t\t<%s\n",
                            GetFTCallback(ENGINE_FT_CALLBACK_TYPE(ftcb)));
                fprintf(tempfp,"\t\t\t\t\t\t%s = \"%s\"\n",LIBRARY_STRING,
                         (ENGINE_FT_CALLBACK_LIBRARY_NAME(ftcb) == NULL)?"":
                             ENGINE_FT_CALLBACK_LIBRARY_NAME(ftcb)); 
                fprintf(tempfp,"\t\t\t\t\t\t%s = \"%s\"\n",FUNCTION_STRING,
                         (ENGINE_FT_CALLBACK_FUNCTION_NAME(ftcb) == NULL)?"":
                             ENGINE_FT_CALLBACK_FUNCTION_NAME(ftcb)); 
                fprintf(tempfp,"\t\t\t\t\t/>\n");
                ftcb = (ENGINE_FtCallback)ENGINE_FT_CALLBACK_NEXT(ftcb);
            }

            fprintf(tempfp,"\t\t\t\t</%s>\n",CALLBACK_STRING);
        }

        fprintf(tempfp, "\t\t\t</%s>\n", FT_GRP_STRING);
        ftg = (ENGINE_FtGroupRec*)ENGINE_FT_GROUP_NEXT(ftg);
    }

    fprintf(tempfp, "\t\t</%s>\n", FT_GRPS_STRING);
    fprintf(tempfp, "\t</%s>\n", FAULT_TOLERANCE_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the parser extensions in the file.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005  Bug ID:1763
 *
 ****************************************************************************/

static void 
SaveParserExtension()
{
    int elemCount = 0;
    char** temp;
    int i = 0;
    ENGINE_ParserExtensionRec* pe = 
        (ENGINE_ParserExtensionRec*)ENGINE_APP_PARSER_EXTENSIONS(application);
    while (pe)
    {
        fprintf(tempfp, 
                "\t<%s %s = \"%s\"",
                PEXT_STRING, ELEM_NAME_STRING, 
                ENGINE_PE_ELEMENT_NAME(pe));

        if (ENGINE_PE_LIB_CACHE_ENTRY(pe)->libCache.libName != NULL)
        {
            fprintf(tempfp, 
                    "\n\t                 %s     = \"%s\"",
                    LIBRARY_STRING, 
                    ENGINE_PE_LIB_CACHE_ENTRY(pe)->libCache.libName);
        }

        if (ENGINE_PE_START_FUNC_NAME(pe) != NULL)
        {  
            fprintf(tempfp, 
                    "\n\t                 %s   = \"%s\"",
                    START_FUNC_STRING, ENGINE_PE_START_FUNC_NAME(pe));
        }

        if (ENGINE_PE_STOP_FUNC_NAME(pe) != NULL)
        {
            fprintf(tempfp, 
                    "\n\t                 %s    = \"%s\"",
                    STOP_FUNC_STRING, ENGINE_PE_STOP_FUNC_NAME(pe)); 
        } 

        if (ENGINE_PE_XLATE_FUNC_NAME(pe) != NULL)
        {
            fprintf(tempfp, 
                    "\n\t                 %s   = \"%s\"",
                    XLATE_FUNC_STRING, ENGINE_PE_XLATE_FUNC_NAME(pe));
        }

        if (ENGINE_PE_DIFF_FUNC_NAME(pe) != NULL)
        {
            fprintf(tempfp, 
                    "\n\t                 %s    = \"%s\"",
                    DIFF_FUNC_STRING, ENGINE_PE_DIFF_FUNC_NAME(pe)); 
        }

        if (ENGINE_PE_COMMIT_FUNC_NAME(pe) != NULL)
        {
            fprintf(tempfp, 
                    "\n\t                 %s    = \"%s\"",
                    COMMIT_FUNC_STRING, ENGINE_PE_COMMIT_FUNC_NAME(pe)); 
        }

        fprintf(tempfp, "/>\n");

        if (strcmp(ENGINE_PE_ELEMENT_NAME(pe),"DsmGcsConfig") != 0)
        {
            elemCount = ENGINE_PE_ELEMENT_DATA_COUNT(pe);
            i = 0;

            if (elemCount > 0)
            {
                
                temp = ENGINE_PE_ELEMENT_DATA(pe);

                if (strcmp(ENGINE_PE_ELEMENT_NAME(pe),"ISUP_Data") == 0)
                {
                    fprintf(tempfp, "\t\t<%s\n",ENGINE_PE_ELEMENT_NAME(pe));
                    if (*temp)
                    {
                        fprintf(tempfp, "\t\t\t%s\n", *temp);
                        if (ven)
                        {
                            VCLASS_REC(ven).isup.commit(tempfp, 
                                                 ISUP_PARSER_EXTENSION,0,0,0);
                        }
                    }
                    fprintf(tempfp, "\t\t/>\n");
                }
                else if (strcmp(ENGINE_PE_ELEMENT_NAME(pe),"UAL_Manager") == 0)
                {
                    if (ENGINE_PE_COMMIT_FUNC(pe))
                    {
                        ENGINE_PE_COMMIT_FUNC(pe)(tempfp);
                    }
                }
                else
                {
                    fprintf(tempfp, "\t\t<%s\n",ENGINE_PE_ELEMENT_NAME(pe));
                    for (i = 0; i < elemCount; i++)
                    {
                        fprintf(tempfp, "\t\t\t%s\n", temp[i]);
                    }
                    fprintf(tempfp, "\t\t/>\n");
                }

                
            }
        }

        pe = (ENGINE_ParserExtensionRec*)ENGINE_PE_NEXT(pe);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the linkset in the file.
 *
 *  Input Parameters:
 *      ITS_POINTER data.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      char** pStrDump.
 *
 *  Return Value:
 *      After writing the linkset this will return ITS_SUCCESS.
 ****************************************************************************/

static int 
DumpLS(ITS_POINTER data, char** pStrDump)
{
    SS7_LinkSetPtr ss7Context = (SS7_LinkSetPtr)data;
    *pStrDump = (char*)calloc(1,sizeof(ITS_CHAR)*2);
    
    if (ss7Context != NULL)
    {
        fprintf(tempfp,
                "\t<%s %s = \"%d\"\n",
                LINK_SET_STRING, ID_STRING, ss7Context->linkSet);
        fprintf(tempfp,
                "\t         %s = \"%s\"\n",
                FAMILY_STRING, SS7_FamilyStr[ss7Context->family]);
        fprintf(tempfp,
                "\t         %s = \"%s\"\n",
                LINKSET_ADJ_STP_STRING, ss7Context->adjSTP? "yes" : "no");
        if (LINKSET_IS_CLINK_STRING, ss7Context->isC)
        {
            fprintf(tempfp,
                "\t         %s = \"yes\"\n", LINKSET_IS_CLINK_STRING);
        }
        if (ss7Context->is5Bit)
        {
            fprintf(tempfp,
                "\t         %s      = \"yes\"\n", LINKSET_IS_5BIT_STRING);
        }
        fprintf(tempfp,
                "\t         %s  = \"%d\">\n", LINKSET_NUM_TO_START_STRING,
                ss7Context->numToStart);
        fprintf(tempfp,
                "\t\t<%s %s = \"%d\" />\n",
                NI_STRING, VALUE_STRING, ss7Context->ni);
        fprintf(tempfp,
                "\t\t<%s %s = \"%d\" />\n",
                ADJ_POINT_CODE_STRING, VALUE_STRING, ss7Context->adjacent);
        fprintf(tempfp,
                "\t\t<%s %s = \"%d\" />\n",
                LOCAL_POINT_CODE_STRING, VALUE_STRING, ss7Context->lpc);
        fprintf(tempfp, "\t</%s>\n",LINK_SET_STRING);
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It gets the linkset from the dsm.
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
SaveLS()
{
    char* strDumpEntries = NULL;

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS) != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableDump(DSM_Mtp3FtGroupId, 
                  DSM_TABLE_LINK_SETS, 
                  &strDumpEntries, 
                  DumpLS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the route info in the file.
 *
 *  Input Parameters:
 *      ROUTE_Info* rinfo.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005    Bug ID:1787
 *  Manikandan  10-05-2005    Bug ID:1823        Saving RoutingKey Route
 *
 ****************************************************************************/

static void 
DumpRouteInfo(ROUTE_Info* rinfo)
{
    fprintf(tempfp, 
            "\t<%s %s     = \"%s\"\n",
            ROUTE_STRING, TYPE_STRING, Route_Types[rinfo->basic.type]);
    fprintf(tempfp, 
            "\t       %s   = \"%s\"\n",
            FAMILY_STRING, SS7_FamilyStr[rinfo->basic.family]);

    if (strcmp(Route_Types[rinfo->basic.type],
               ROUTE_TYPE_CONCERNED_STRING) == 0)
    {
        fprintf(tempfp,
            "\t       %s    = \"%s\"\n",
            STYLE_STRING, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING);
        rinfo->basic.style = ROUTE_DPC_OPC_SIO_SSN;
    }
    else if (strcmp(Route_Types[rinfo->basic.type],
               ROUTE_TYPE_ROUTING_KEY_STRING) == 0)
    {
        fprintf(tempfp,
            "\t       %s    = \"%s\">\n",
            STYLE_STRING, Route_Styles[rinfo->basic.style]);
    }
    else
    {
        fprintf(tempfp,
            "\t       %s    = \"%s\"\n",
            STYLE_STRING, Route_Styles[rinfo->basic.style]);
    }

    if (rinfo->basic.type == ROUTING_KEY_ROUTE)
    {
        fprintf(tempfp, 
            "\t\t<%s %s = \"%d\"/>\n",
            ROUTING_KEY_STRING, VALUE_STRING, rinfo->rkey);
        fprintf(tempfp, 
            "\t\t<%s %s = \"%d\"/>\n",
            DEST_POINT_CODE_STRING, VALUE_STRING, rinfo->basic.dpc);
        fprintf(tempfp, 
            "\t\t<%s %s = \"%d\"/>\n",
            SIO_STRING, VALUE_STRING, rinfo->basic.criteria.sio);
        fprintf(tempfp, 
            "\t\t<%s %s = \"%d\"/>\n",
            SSN_STRING, VALUE_STRING, rinfo->basic.criteria.ssn);
    }
    else
    {
        fprintf(tempfp, 
                "\t       %s  = \"%d\"\n",
                LINKSET_SET_STRING, rinfo->linkSet->linkSet);

        fprintf(tempfp, "\t       priority = \"%d\">\n",rinfo->priority);
        fprintf(tempfp, 
                "\t\t<%s %s = \"%d\"/>\n",
                DEST_POINT_CODE_STRING, VALUE_STRING, rinfo->basic.dpc);
        fprintf(tempfp, 
                "\t\t<%s %s = \"%d\"/>\n",
                SIO_STRING, VALUE_STRING, rinfo->basic.criteria.sio);

        if ((rinfo->basic.style == ROUTE_DPC_OPC_NI) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_CIC_RANGE) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_CIC))
        {
            if (strcmp(Route_Types[rinfo->basic.type],
                   ROUTE_TYPE_CONCERNED_STRING) != 0)
            {
                fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n",
                    ORIG_POINT_CODE_STRING, VALUE_STRING, 
                    rinfo->basic.criteria.opc);
            }
            else
            {
                fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n", 
                    LOCAL_POINT_CODE_STRING,VALUE_STRING, 
                    rinfo->basic.criteria.opc);
            }
        }

        if ((rinfo->basic.style == ROUTE_DPC_SIO_SSN) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN))
        {
            if (strcmp(Route_Types[rinfo->basic.type],
                   ROUTE_TYPE_CONCERNED_STRING) == 0)
            {
                fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n",
                    LOCAL_SSN_STRING, VALUE_STRING, rinfo->basic.criteria.cic);
            }

            fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n",
                    SSN_STRING, VALUE_STRING, rinfo->basic.criteria.ssn);
        }

        if ((rinfo->basic.style == ROUTE_DPC_SIO_CIC) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_CIC))
        {
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n",
                    CIC_STRING, VALUE_STRING, rinfo->basic.criteria.cic);
        }

        if ((rinfo->basic.style == ROUTE_DPC_SIO_SSN_RANGE) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_SSN_RANGE) ||
            (rinfo->basic.style == ROUTE_DPC_SIO_CIC_RANGE) ||
            (rinfo->basic.style == ROUTE_DPC_OPC_SIO_CIC_RANGE))
        {
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n",
                    RANGE_BEGIN_STRING, VALUE_STRING, 
                    rinfo->basic.criteria.range.begin);
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n",
                    RANGE_END_STRING, VALUE_STRING, 
                    rinfo->basic.criteria.range.end);
        }
    }

    fprintf(tempfp, "\t</%s>\n", ROUTE_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the sccp route info in the file.
 *
 *  Input Parameters:
 *      ITS_POINTER data, void *in, void *out.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      After writing the sccp route it returns ITS_SUCCESS.
 ****************************************************************************/

static int 
DumpSCCPRoute(ITS_POINTER data, void *in, void *out)
{
    ROUTE_Info *rinfo = (ROUTE_Info *)data;

    while (rinfo != NULL)
    {
        DumpRouteInfo(rinfo);
        rinfo = rinfo->next;
    }
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the route in the file.
 *
 *  Input Parameters:
 *      ITS_POINTER data, void *in, void *out.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      After writing the route it returns ITS_SUCCESS.
 ****************************************************************************/

static int 
DumpRoute(ITS_POINTER data, void *in, void *out)
{
    int i;
    SS7_Destination* ss7Context = (SS7_Destination*)data;
    ROUTE_Info* rinfo = NULL;

    for(i = 0; i < (int)ss7Context->numEntries; i++)
    {
        rinfo = (ROUTE_Info*)ss7Context->entries[i];
        DumpRouteInfo(rinfo);
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It gets the route from dsm.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  10-05-2005    Bug ID:1823        Saving RoutingKey Route
 *
 ****************************************************************************/

static void 
SaveRoute()
{
    if (DSM_LockTable( DSM_RoutingFtGroupId, 
                       DSM_TABLE_DESTINATIONS) != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableIterate(DSM_RoutingFtGroupId, 
                     DSM_TABLE_DESTINATIONS, 
                     NULL, 
                     NULL, 
                     DumpRoute);
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_DESTINATIONS);

    if (DSM_LockTable( DSM_RoutingFtGroupId, 
                       DSM_TABLE_RCONTEXTS) != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableIterate(DSM_RoutingFtGroupId, 
                     DSM_TABLE_RCONTEXTS, 
                     NULL, 
                     NULL, 
                     DumpRoute);
    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_RCONTEXTS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It gets the sccp route from dsm.
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
SaveSCCPRoute()
{
    if (ROUTE_LockTable() != ITS_SUCCESS)
    {
        return;
    }

    DSM_TableIterate(DSM_SccpFtGroupId, 
                     DSM_TABLE_ITU_SCCP_LPC, 
                     NULL, 
                     NULL, 
                     DumpSCCPRoute);

    DSM_TableIterate(DSM_SccpFtGroupId,
                     DSM_TABLE_ANSI_SCCP_LPC,
                     NULL,
                     NULL,
                     DumpSCCPRoute);

    ROUTE_UnlockTable();
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the engine trace in the file.
 *
 *  Input Parameters:
 *      ENGINE_Trace trace.
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
SaveTrace(ENGINE_Trace trace)
{
    while (trace != NULL)
    {
        if ((ENGINE_TL_LEVEL_MASK(trace) & TRACE_TO_DISPLAY) != 0)
        {
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%s\"/>\n",
                    ENGINE_TL_LEVEL_NAME(trace), 
                    OUTPUT_STRING, ITS_STDOUT_STRING);
        }

        if ((ENGINE_TL_LEVEL_MASK(trace) & TRACE_TO_FILE) != 0)
        {
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%s\"/>\n",
                    ENGINE_TL_LEVEL_NAME(trace), 
                    OUTPUT_STRING, ITS_FILE_STRING);
        }

        if ((ENGINE_TL_LEVEL_MASK(trace) & TRACE_TO_SYSLOG) != 0)
        {
            fprintf(tempfp,
                    "\t\t<%s %s = \"%s\"/>\n",
                    ENGINE_TL_LEVEL_NAME(trace),
                    OUTPUT_STRING, ITS_SYSLOG_STRING);
        }

        trace = (ENGINE_Trace)ENGINE_TL_NEXT(trace);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the toolkit trace in the file.
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
SaveToolKitTrace()
{
    ENGINE_Trace trace = (ENGINE_Trace)ENGINE_APP_SUPPORT_LEVELS(application);

    fprintf(tempfp, "\t<%s>\n", TK_TRACE_STRING);
    SaveTrace(trace);
    fprintf(tempfp, "\t</%s>\n", TK_TRACE_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the application trace in the file.
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
SaveApplicationTrace()
{
    ENGINE_Trace trace = (ENGINE_Trace)ENGINE_APP_TRACE_LEVELS(application);

    fprintf(tempfp, "\t<%s>\n", APP_TRACE_STRING);
    SaveTrace(trace);
    fprintf(tempfp, "\t</%s>\n", APP_TRACE_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the destination in the file.
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
SaveDestination()
{
    ENGINE_ISUPAttr isup = NULL;
    int fam, temp;

    ENGINE_Dest dest = (ENGINE_Dest)ENGINE_APP_DESTS(application);

    while (dest != NULL)
    {
        fam = ENGINE_DE_FAMILY(dest);
        fprintf(tempfp, 
                "\t<%s %s = \"%s\"\n",
                DEST_STRING, FAMILY_STRING, SS7_FamilyStr[fam]);
        fprintf(tempfp, 
                "\t             %s = \"%d\"\n",
                PC_STRING, ENGINE_DE_PC(dest));
        fprintf(tempfp, 
                "\t             %s = \"%d\"\n",
                ENI_STRING, ENGINE_DE_NI(dest));
        temp = ENGINE_DE_MTP3(dest);
        fprintf(tempfp, 
                "\t             %s = \"%s\"\n",
                DI_MTP3_VAR_STRING,
                (fam == FAMILY_ANSI)? ansi_variant[temp] : itu_variant[temp]);
        fprintf(tempfp, 
                "\t             %s = \"%s\"\n",
                DI_ISUP_VAR_STRING, ENGINE_DE_ISUP(dest));
        temp = ENGINE_DE_SCCP(dest); 
        fprintf(tempfp, 
                "\t             %s = \"%s\"\n",
                DI_SCCP_VAR_STRING,
                (fam == FAMILY_ANSI)? ansi_variant[temp] : itu_variant[temp]);
        temp = ENGINE_DE_TCAP(dest); 
        fprintf(tempfp, 
                "\t             %s = \"%s\"\n",
                DI_TCAP_VAR_STRING,
                (fam == FAMILY_ANSI)? ansi_variant[temp] : itu_variant[temp]);
        temp = ENGINE_DE_TUP(dest); 
        fprintf(tempfp, 
                "\t             %s = \"%s\"\n",
                DI_TUP_VAR_STRING,
                (fam == FAMILY_ANSI)? ansi_variant[temp] : itu_variant[temp]);
        temp = ENGINE_DE_DUP(dest); 
        fprintf(tempfp, 
                "\t             %s = \"%s\">\n",
                DI_DUP_VAR_STRING,
                (fam == FAMILY_ANSI)? ansi_variant[temp] : itu_variant[temp]);
        isup = (ENGINE_ISUPAttr)ENGINE_DE_ISUP_ATTR(dest);
        fprintf(tempfp, 
                "\t\t<%s %s = \"%d\"\n",
                ISUP_ATTR_STRING, LPC_STRING,ENGINE_IA_LPC(isup));

        if (ENGINE_IA_LIB(isup)->libCache.libName != NULL)
        { 
            fprintf(tempfp, 
                    "\t\t                %s        = \"%s\"\n",
                    LIBRARY_STRING, 
                    ENGINE_IA_LIB(isup)->libCache.libName);
        }

        fprintf(tempfp, 
                "\t\t                %s       = \"%s\"\n",
                CLASS_REC_STRING, ENGINE_IA_CLASS_REC(isup));
        if (ven)
        {
            VCLASS_REC(ven).isup.commit(tempfp,
                                        ISUP_CONFIG,
                                        ENGINE_IA_LPC(isup),
                                        ENGINE_DE_PC(dest),
                                        ENGINE_IA_SIO(isup));
        }

        fprintf(tempfp, 
                "\t\t                %s            = \"%d\">\n",
                SIO_STRING, ENGINE_IA_SIO(isup));

        if (ven)
        {
            VCLASS_REC(ven).isup.commit(tempfp, 
                                        ISUP_DESTINATION,
                                        ENGINE_IA_LPC(isup),
                                        ENGINE_DE_PC(dest),
                                        ENGINE_IA_SIO(isup));
        }

        fprintf(tempfp, "\t\t</%s>\n", ISUP_ATTR_STRING);
        fprintf(tempfp, "\t</%s>\n", DEST_STRING);
        dest = (ENGINE_Dest)ENGINE_DE_NEXT(dest);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the link in the file.
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
SaveLink(ENGINE_Link ln)
{
    while (ln != NULL)
    {
        fprintf(tempfp, 
                "%*c<%s %s = \"%d\"\n",tab*8,' ',
                LINK_STRING, ID_STRING, ENGINE_LN_CODE(ln));
        fprintf(tempfp, 
                "%*c      %s = \"%s\"\n",
                tab*8, ' ', FAMILY_STRING, 
                SS7_FamilyStr[ENGINE_LN_FAMILY(ln)]);
        fprintf(tempfp, 
                "%*c      %s = \"%d\"\n",
                tab*8, ' ', LINKSET_SET_STRING, ENGINE_LN_SET(ln));
        fprintf(tempfp, 
                "%*c      %s = \"%s\"\n",
                tab*8, ' ', LINK_INIT_ACTIVE_STRING,
                ENGINE_LN_INIT_ACTIVE(ln)? "yes" : "no");
        fprintf(tempfp, 
                "%*c      %s = \"%s\"\n",
                tab*8, ' ', LINK_TERMINAL_FIXED_STRING,
                ENGINE_LN_TERM_FIXED(ln)? "yes" : "no");
        fprintf(tempfp, 
                "%*c      %s = \"%s\"\n",
                tab*8, ' ', LINK_FIXED_STRING, 
                ENGINE_LN_LINK_FIXED(ln)? "yes" : "no");
        fprintf(tempfp, 
                "%*c      %s = \"%s\"\n",
                tab*8, ' ', LINK_SAAL_LINK_STRING,
                ENGINE_LN_IS_SAAL(ln)? "yes" : "no");
        fprintf(tempfp, 
                "%*c      %s = \"%s\"\n",
                tab*8, ' ', LINK_LOCAL_STRING,
                ENGINE_LN_IS_LOCAL(ln)? "yes" : "no");
        fprintf(tempfp, 
                "%*c      %s = \"%d\"\n",
                tab*8, ' ', PRIORITY_STRING, ENGINE_LN_PRI(ln));
        fprintf(tempfp, 
                "%*c      %s = \"%d\"\n",
                tab*8, ' ', LINK_TERMINAL_STRING, ENGINE_LN_TERMINAL(ln));
        fprintf(tempfp, 
                "%*c      %s = \"%d\"/>\n",
                tab*8, ' ', LINK_DATA_LINK_STRING, ENGINE_LN_CIRCUIT(ln));
        ln = (ENGINE_Link)ENGINE_LN_NEXT(ln);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It returns the family and modifier for the given mask.
 *
 *  Input Parameters:
 *      int mask.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      char** family, char** modifier.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/

static void 
GetFamilyModifier(int mask,char* family, char* modifier)
{
    if ((mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
    {
        strcpy(family,ANSI_STRING);
    }
    else if ((mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
    {
        strcpy(family,ITU_STRING);
    }
    else if ((mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
    {
        strcpy(family,"PRC");
    }

    if ((mask & ITS_FLAG_MTP2) == ITS_FLAG_MTP2)
    {
        strcpy(modifier,MOD_MTP2_STRING);
    }
    else if ((mask & ITS_FLAG_MTP3) == ITS_FLAG_MTP3)
    {
        strcpy(modifier,MOD_MTP3_STRING);
    }
    else if ((mask & ITS_FLAG_ISUP) == ITS_FLAG_ISUP)
    {
        strcpy(modifier,MOD_ISUP_STRING);
    }
    else if ((mask & ITS_FLAG_SCCP) == ITS_FLAG_SCCP)
    {
        strcpy(modifier,MOD_SCCP_STRING);
    }
    else if ((mask & ITS_FLAG_TCAP) == ITS_FLAG_TCAP)
    {
        strcpy(modifier,MOD_TCAP_STRING);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the transport in the file.
 *
 *  Input Parameters:
 *      ENGINE_Transport tp.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  10-05-2005    Bug ID:1823        Changes in SCTP Transport 
 *
 ****************************************************************************/

static void 
SaveTransport(ENGINE_Transport tp)
{
    ENGINE_TransportSpecifics ts = NULL;
    ENGINE_Link ln = NULL;
    ENGINE_TransportCallbacks cb = NULL;
    char family[10];
    char modifier[10];
    int count;

    while (tp != NULL)
    {
        fprintf(tempfp, "\t\t<%s ",TRANSPORT_STRING);

        if (ENGINE_TR_NAME(tp) != NULL)
        {
            fprintf(tempfp, 
                    "%s = \"%s\"\n\t\t           ",
                    NAME_STRING, ENGINE_TR_NAME(tp));
        }        

        memset(family, 0, 10);
        memset(modifier, 0, 10);

        GetFamilyModifier(ENGINE_TR_MASK(tp),family,modifier);

        if (strcmp(family,"") != 0)
        {
            fprintf(tempfp, 
                    "%s = \"%s\"\n\t\t           ",
                    FAMILY_STRING, family);
        } 

        if (ENGINE_TR_NUM_ASSOCIATES(tp) != 0)
        {
            fprintf(tempfp, 
                    "%s = \"%d\"\n\t\t           ",
                    COUNT_STRING, ENGINE_TR_NUM_ASSOCIATES(tp));
        } 

        if (ENGINE_TR_IS_INTERNODE(tp))
        {
            fprintf(tempfp, "%s = \"yes\"\n\t\t           ", INTERNODE_STRING);
        }

        ts = (ENGINE_TransportSpecifics)ENGINE_TR_SPECIFICS(tp);

        switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TR_MASK(tp)))
        {
            case ITS_TRANSPORT_TQUEUE:
            {
                fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_TQ_STRING);
                break;
            }

            case ITS_TRANSPORT_CSOCKET:
            {
                fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_CSOCK_STRING);
                break;
            }

            case ITS_TRANSPORT_SSOCKET:
            case ITS_TRANSPORT_DATA_SOCKET:
            { 
                fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_SSOCK_STRING);
                break;
            }

            case ITS_TRANSPORT_SSOCKET_ITER:
            {
                fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_ISOCK_STRING);
                break;
            }

            case ITS_TRANSPORT_DATAGRAM:
            {
                if ((ENGINE_TS_MASK(ts) & ITS_TRANSPORT_DGRAM_VIRT) == 
                             ITS_TRANSPORT_DGRAM_VIRT)
                {
                    fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_VIRT_STRING);
                }
                else
                {
                    fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_DSOCK_STRING);
                }
                break;
            }

            case ITS_TRANSPORT_FIFO:
            case ITS_TRANSPORT_GFIFO:
            {
                fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_GFIFO_STRING);
                break;
            }

            case ITS_TRANSPORT_SS7:
            {
                fprintf(tempfp, "%s = \"%s\">\n", TYPE_STRING, T_SS7_STRING);
                break;
            }
        }

        switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TR_MASK(tp)))
        {
            case ITS_TRANSPORT_CSOCKET:
            case ITS_TRANSPORT_SSOCKET:
            case ITS_TRANSPORT_SSOCKET_ITER:
            {
                if (ts == NULL)
                { 
                    break;
                }
                fprintf(tempfp, 
                        "\t\t\t<%s %s = \"%s\"\n",
                        STREAM_DATA_STRING, SOCKET_DOMAIN_STRING,
                        ENGINE_TS_DATA(ts).tcpSpecs.socketDomain);
                fprintf(tempfp, 
                        "\t\t\t            %s = \"%s\"\n",
                        SERVER_PATH_STRING, 
                        ENGINE_TS_DATA(ts).tcpSpecs.serverPath);
                fprintf(tempfp, 
                        "\t\t\t            %s = \"%s\"/>\n",
                        SERVER_PORT_STRING, 
                        ENGINE_TS_DATA(ts).tcpSpecs.serverPort);
                switch(ENGINE_TR_MASK(tp) & ITS_TRANSPORT_SOCKP_MASK)
                {
                    case ITS_TRANSPORT_GDI_SOCKET:
                    {
                        fprintf(tempfp, 
                                "\t\t\t<%s %s = \"%s\"/>\n",
                                MODIFIER_STRING, VALUE_STRING, MOD_GDI_STRING);
                        fprintf(tempfp, 
                                "\t\t\t<%s %s = \"%s\"\n",
                                MOD_GDI_STRING,GDI_LOCAL_PC_STRING,
                                ENGINE_TS_DATA(ts).gdiSpecs.localPC);
                        fprintf(tempfp, 
                                "\t\t\t     %s = \"%s\"\n",
                                GDI_REMOTE_PC_STRING,
                                ENGINE_TS_DATA(ts).gdiSpecs.remotePC);
                        fprintf(tempfp, 
                                "\t\t\t     %s = \"%s\"/>\n",
                                GDI_REMOTE_SSN_STRING,
                                ENGINE_TS_DATA(ts).gdiSpecs.remoteSSN);
                        break;
                    }
                    case ITS_TRANSPORT_TALI_SOCKET:
                    {
                        fprintf(tempfp, 
                                "\t\t\t<%s %s = \"%s\"/>\n",
                                MODIFIER_STRING, VALUE_STRING, MOD_TALI_STRING);
                        fprintf(tempfp, 
                                "\t\t\t<%s %s = \"%s\"\n",
                                MOD_TALI_STRING,TALI_LOCAL_PC_STRING,
                        ENGINE_TS_DATA(ts).taliSpecs.localPC);
                        fprintf(tempfp, 
                                "\t\t\t      %s = \"%s\"\n",
                                TALI_ADJ_PC_STRING, 
                                ENGINE_TS_DATA(ts).taliSpecs.adjacentPC);
                        fprintf(tempfp, 
                                "\t\t\t      %s = \"%s\"\n",
                                TALI_USE_UPPER_LAYER_STRING,
                                ENGINE_TS_DATA(ts).taliSpecs.useUpperLayer);
                        fprintf(tempfp, 
                                "\t\t\t      %s = \"%s\"/>\n",
                                TALI_LOCALLY_ALLOWED_ON_OPEN_STRING,
                                ENGINE_TS_DATA(ts).taliSpecs.
                                                 localAllowedOnOpen);
                        break;
                    }
                    case ITS_TRANSPORT_IMAL_SOCKET:
                    {
                        fprintf(tempfp, 
                                "\t\t\t<%s %s = \"%s\"/>\n",
                                MODIFIER_STRING, VALUE_STRING, MOD_IMAL_STRING);
                        if (strcmp(modifier,"") != 0)
                        {
                            fprintf(tempfp,
                                    "\t\t\t<%s %s = \"%s\"/>\n",
                                    MODIFIER_STRING, VALUE_STRING, modifier);
                        }

                        fprintf(tempfp, 
                                "\t\t\t<%s %s = \"%s\"\n",
                                MOD_IMAL_STRING,IMAL_LOCAL_PC_STRING,
                                ENGINE_TS_DATA(ts).imalSpecs.localPC);
                        fprintf(tempfp, 
                                "\t\t\t      %s = \"%s\"\n",
                                IMAL_ADJ_PC_STRING,
                                ENGINE_TS_DATA(ts).imalSpecs.adjacentPC);
                        fprintf(tempfp, 
                                "\t\t\t      %s = \"%s\"/>\n",
                                IMAL_KEEPALIVE_TIMEOUT_STRING,
                                (ENGINE_TS_DATA(ts).imalSpecs.keepAliveTimeOut 
                                    == NULL)? "" :
                                ENGINE_TS_DATA(ts).imalSpecs.keepAliveTimeOut);
                        break;
                    }
                }

                break;
            }
            case ITS_TRANSPORT_DATAGRAM:
            {
                int numA = 0;

                if ((ENGINE_TS_MASK(ts) & ITS_TRANSPORT_DGRAM_VIRT) == 
                             ITS_TRANSPORT_DGRAM_VIRT) 
                {
                    fprintf(tempfp, 
                        "\t\t\t<%s %s = \"INET\"\n",
                        DGRAM_DATA_STRING, SOCKET_DOMAIN_STRING);
                    fprintf(tempfp, 
                        "\t\t\t            %s = \"%s\"\n",
                        SERVER_PATH_STRING, 
                        ENGINE_TS_DATA(ts).sctpSpecs.udpPart.localHost);
                    fprintf(tempfp, 
                        "\t\t\t            %s = \"%s\" />\n",
                        SERVER_PORT_STRING, 
                        ENGINE_TS_DATA(ts).sctpSpecs.udpPart.localPort);

                    fprintf(tempfp,
                            "\t\t\t<%s %s = \"%s\"/>\n",
                            MODIFIER_STRING, VALUE_STRING, MOD_SCTP_STRING);
                    break;
                }

                fprintf(tempfp, 
                            "\t\t\t<%s %s = \"%s\"\n",
                            DGRAM_DATA_STRING, LOCAL_HOST_NAME_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.udpPart.localHost);
                fprintf(tempfp, 
                            "\t\t\t              %s = \"%s\">\n",
                            LOCAL_PORT_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.udpPart.localPort);

                for (numA = 0; 
                     numA < ENGINE_TS_DATA(ts).udpSpecs.numAssociates;
                     numA++)
                {
                    fprintf(tempfp, 
                            "\t\t\t\t <%s  %s = \"%s\" />\n",
                            ASSOCIATE_STRING, VALUE_STRING,
                            ENGINE_TS_DATA(ts).udpSpecs.associates[numA]);
                }

                fprintf(tempfp, "\t\t\t</%s>\n", DGRAM_DATA_STRING);

                if ((ENGINE_TR_MASK(tp) & ITS_TRANSPORT_SOCKP_MASK) == 
                     ITS_TRANSPORT_SCTP_SOCKET)
                {
                    fprintf(tempfp, 
                            "\t\t\t<%s %s = \"%s\"/>\n",
                            MODIFIER_STRING, VALUE_STRING, MOD_SCTP_STRING);
                    fprintf(tempfp, 
                            "\t\t\t<%s %s = \"%s\"\n",
                            MOD_SCTP_STRING,MAX_IN_STREAMS_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.maxInStreams);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            NUM_OUT_STREAMS_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.numOutStreams);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            MAX_ATTEMPTS_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.maxAttempts);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            INIT_COOKIE_LIFE_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.cookieLife);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            INIT_HB_ON_STRING, 
                            ENGINE_TS_DATA(ts).sctpSpecs.hbOn);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            INIT_TIMEOUT_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.initTimeOut);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            SEND_TIMEOUT_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.sendTimeOut);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            RECV_TIMEOUT_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.recvTimeOut);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            HB_TIMEOUT_STRING, 
                            ENGINE_TS_DATA(ts).sctpSpecs.hbTimeOut);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            SHUT_TIMEOUT_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.shutdownTimeOut);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            PMTU_TIMEOUT_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.pmtuTimeOut);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"\n",
                            IS_CLIENT_STRING, 
                            ENGINE_TS_DATA(ts).sctpSpecs.isClient);
                    fprintf(tempfp, 
                            "\t\t\t      %s = \"%s\"/>\n",
                            PAYLOAD_TYPE_STRING,
                            ENGINE_TS_DATA(ts).sctpSpecs.payloadType);

                    for(count = 0; 
                        count < ENGINE_TS_DATA(ts).sctpSpecs.numExtraHomes;
                        count++)
                    {
                        fprintf(tempfp, 
                                "\t\t\t\t<%s %s = \"%s\"/>\n",
                                OTHER_HOME_STRING, LOCAL_HOST_NAME_STRING,
                                ENGINE_TS_DATA(ts).sctpSpecs.extraHomes[count]);
                    }
                }
                else
                {
                   fprintf(tempfp, 
                           "\t\t\t<%s %s = \"%s\"\n",
                           DGRAM_DATA_STRING, LOCAL_HOST_NAME_STRING, 
                           ENGINE_TS_DATA(ts).udpSpecs.localHost);
                   fprintf(tempfp, 
                           "\t\t\t              %s = \"%s\"/>\n",
                           LOCAL_PORT_STRING, 
                           ENGINE_TS_DATA(ts).udpSpecs.localPort);
                }

                break;
            }
            case ITS_TRANSPORT_FIFO:
            case ITS_TRANSPORT_GFIFO:
            { 
                if (ts != NULL)
                {
                    fprintf(tempfp, 
                            "\t\t\t<%s %s = \"%s\"\n",
                            FIFO_DATA_STRING, FIFO_CLIENT_PATH_STRING, 
                            ENGINE_TS_DATA(ts).fifoSpecs.clientPath);
                    fprintf(tempfp, 
                            "\t\t\t          %s = \"%s\"/>\n",
                            FIFO_SERVER_PATH_STRING, 
                            ENGINE_TS_DATA(ts).fifoSpecs.serverPath);
                }

                break;
            }
            case ITS_TRANSPORT_SS7:
            { 
                if (strcmp(modifier,"") != 0)
                {
                    fprintf(tempfp,
                        "\t\t\t<%s %s = \"%s\"/>\n",
                    MODIFIER_STRING, VALUE_STRING, modifier);
                }

                if (ts != NULL)
                {
                    fprintf(tempfp, 
                            "\t\t\t<%s %s = \"%s\"\n",
                            VENDOR_STRING, NAME_STRING,
                            (ENGINE_TS_DATA(ts).ss7Specs.vendorName == NULL)? 
                                "" : ENGINE_TS_DATA(ts).ss7Specs.vendorName);
                    fprintf(tempfp, 
                            "\t\t\t        %s = \"%s\"\n",
                            LIBRARY_STRING, 
                            ENGINE_TS_DATA(ts).ss7Specs.vendorLib);
                    fprintf(tempfp, 
                            "\t\t\t        %s = \"%s\"/>\n",
                            VENDOR_REC_STRING,
                            ENGINE_TS_DATA(ts).ss7Specs.vendorClass);
                }
                break;
            }
        }

        tab = 3;
        cb = (ENGINE_TransportCallbacks)ENGINE_TR_CALLBACKS(tp);
        SaveCallBacks(cb);

        if (ENGINE_TC_HANDLER_TYPE(tp) == DISP_PROT_CUSTOM)
        {
            fprintf(tempfp, 
                    "\t\t\t<%s %s = \"%s\"\n",
                    CUSTOM_DISP_STRING, LIBRARY_STRING,
                    (ENGINE_TC_LIB_NAME(tp) == NULL)? 
                        "" : ENGINE_TC_LIB_NAME(tp));
            fprintf(tempfp, 
                    "\t\t\t                %s = \"%s\"/>\n",
                    CDISP_STRING, ENGINE_TC_MAIN(tp));
        }

        ln = (ENGINE_Link)ENGINE_TR_LINKS(tp);
        SaveLink(ln);
        tab = 0;
        fprintf(tempfp, "\t\t</%s>\n", TRANSPORT_STRING);
        tp = (ENGINE_Transport)ENGINE_TR_NEXT(tp);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the border pool in the file.
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
SaveBorderPool()
{
    ENGINE_ThreadPool wp = (ENGINE_ThreadPool)ENGINE_APP_POOLS(application);
    ENGINE_Transport tp = NULL;

    while (wp != NULL)
    {
        if (ENGINE_TP_TYPE(wp) == TP_BORDERS)
        {
            fprintf(tempfp, 
                    "\t<%s %s = \"%d\">\n",
                    BORDER_POOL_STRING, STACK_SIZE_STRING, 
                    ENGINE_TP_STACK_SIZE(wp));
            tp = (ENGINE_Transport)ENGINE_TP_TRANSPORTS(wp);
            SaveTransport(tp);
            fprintf(tempfp, "\t</%s>\n", BORDER_POOL_STRING);
        }

        wp = (ENGINE_ThreadPool)ENGINE_TP_NEXT(wp);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the worker pool in the file.
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
SaveWorkerPool()
{
    ENGINE_ThreadPool wp = (ENGINE_ThreadPool)ENGINE_APP_POOLS(application);
    ENGINE_Transport tp = NULL;

    while (wp != NULL)
    {
        if (ENGINE_TP_TYPE(wp) == TP_WORKERS)
        {
            fprintf(tempfp, 
                    "\t<%s %s = \"%d\">\n",
                    WORK_POOL_STRING, STACK_SIZE_STRING, 
                    ENGINE_TP_STACK_SIZE(wp));
            tp = (ENGINE_Transport)ENGINE_TP_TRANSPORTS(wp);
            SaveTransport(tp);
            fprintf(tempfp, "\t</%s>\n", WORK_POOL_STRING);
        }

        wp = (ENGINE_ThreadPool)ENGINE_TP_NEXT(wp);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the workitem pool in the file.
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
SaveWorkItemPool()
{
    ENGINE_ThreadPool wi = (ENGINE_ThreadPool)ENGINE_APP_POOLS(application);
    ENGINE_WorkItem ewi = NULL;

    while (wi != NULL)
    {
        if (ENGINE_TP_TYPE(wi) == TP_WORK_ITEMS)
        {
            fprintf(tempfp, 
                    "\t<%s %s = \"%d\">\n",
                    ITEM_POOL_STRING, STACK_SIZE_STRING, 
                    ENGINE_TP_STACK_SIZE(wi));
            ewi = (ENGINE_WorkItem)
                ENGINE_TR_WORK_ITEMS(ENGINE_TP_TRANSPORTS(wi));
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%d\"/>\n",
                    NUM_WORKERS_STRING, VALUE_STRING,
                    ENGINE_TR_NUM_ASSOCIATES(ENGINE_TP_TRANSPORTS(wi)));
            fprintf(tempfp, 
                    "\t\t<%s %s = \"%s\"\n",
                    WORK_ITEM_STRING, TYPE_STRING,
                    (ENGINE_WI_PERSIST(ewi) == ITS_TRUE)? 
                        REPEAT_STRING : NREPEAT_STRING);
            fprintf(tempfp, 
                    "\t\t          %s = \"%s\"\n",
                    LIBRARY_STRING,
                    (ENGINE_WI_LIB_NAME(ewi) == NULL)? "" : 
                        ENGINE_WI_LIB_NAME(ewi));
            fprintf(tempfp, 
                    "\t\t          %s = \"%s\"\n",
                    WDISP_STRING,
                    (ENGINE_WI_DELEGATE(ewi) == NULL)? "" : 
                        ENGINE_WI_DELEGATE(ewi));
            fprintf(tempfp, 
                    "\t\t          %s        = \"%d\"/>\n",
                    COUNT_STRING, ENGINE_WI_REPEAT(ewi));
            fprintf(tempfp, "\t</%s>\n", ITEM_POOL_STRING);
        }

        wi = (ENGINE_ThreadPool)ENGINE_TP_NEXT(wi);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the itu isup stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788
 *
 ****************************************************************************/

static void 
SaveITU_ISUP(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\">\n",
            ITU_ISUP_STRING, VARIANT_STRING, 
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ven)
    {
        VCLASS_REC(ven).isup.commit(tempfp, ISUP_STACK, 0, 0, 0 );
    }

    fprintf(tempfp, "\t\t\t</%s>\n", ITU_ISUP_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the ansi isup stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788
 *
 ****************************************************************************/

static void 
SaveANSI_ISUP(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\">\n",
            ANSI_ISUP_STRING, VARIANT_STRING, 
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ven)
    {
        VCLASS_REC(ven).isup.commit(tempfp, ISUP_STACK, 0, 0, 0);
    }

    fprintf(tempfp, "\t\t\t</%s>\n", ANSI_ISUP_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the itu mtp3 stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788
 *
 ****************************************************************************/

static void 
SaveITU_MTP3(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\">\n",
            ITU_MTP3_STRING, VARIANT_STRING, 
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ven)
    {
        VCLASS_REC(ven).mtp3.commit(tempfp);
    }

    fprintf(tempfp, "\t\t\t</%s>\n", ITU_MTP3_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the ansi mtp3 stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788
 *
 ****************************************************************************/

static void 
SaveANSI_MTP3(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\">\n",
            ANSI_MTP3_STRING, VARIANT_STRING, 
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ven)
    {
        VCLASS_REC(ven).mtp3.commit(tempfp);
    }

    fprintf(tempfp, "\t\t\t</%s>\n", ANSI_MTP3_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the itu tcap stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788
 *
 ****************************************************************************/

static void 
SaveITU_TCAP(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\"",
            ITU_TCAP_STRING, VARIANT_STRING, 
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ENGINE_ISS7_NUM_THREADS(stk) > 1)
    {
        fprintf(tempfp, 
                "\n\t\t\t           %s = \"%d\"",
                NUM_THREADS_STRING, ENGINE_ISS7_NUM_THREADS(stk));
    }

    fprintf(tempfp, ">\n");

    if (ven)
    {
        VCLASS_REC(ven).tcap.commit(tempfp);
    }

    tab = 3;
    SaveLink((ENGINE_Link)ENGINE_ISS7_LINKS(stk));
    tab = 0;
    fprintf(tempfp, "\t\t\t</%s>\n", ITU_TCAP_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the ansi tcap stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788, 1783
 *
 ****************************************************************************/

static void 
SaveANSI_TCAP(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\"",
            ANSI_TCAP_STRING, VARIANT_STRING, 
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ENGINE_ISS7_NUM_THREADS(stk) > 1)
    {
        fprintf(tempfp, 
                "\n\t\t\t           %s = \"%d\"",
                NUM_THREADS_STRING, ENGINE_ISS7_NUM_THREADS(stk));
    }

    fprintf(tempfp, ">\n");

    if (ven)
    {
        VCLASS_REC(ven).tcap.commit(tempfp);
    }

    tab = 3;
    SaveLink((ENGINE_Link)ENGINE_ISS7_LINKS(stk));
    tab = 0;

    fprintf(tempfp, "\t\t\t</%s>\n", ANSI_TCAP_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the itu sccp stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788, 1783
 *
 ****************************************************************************/

static void 
SaveITU_SCCP(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\"",
            ITU_SCCP_STRING, VARIANT_STRING, 
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ENGINE_ISS7_NUM_THREADS(stk) > 1)
    {
        fprintf(tempfp, 
                "\n\t\t\t           %s = \"%d\"",
                NUM_THREADS_STRING, ENGINE_ISS7_NUM_THREADS(stk));
    }

    fprintf(tempfp, ">\n");

    if (ven)
    { 
        VCLASS_REC(ven).sccp.commit(tempfp);
    }

    tab = 3;
    SaveLink((ENGINE_Link)ENGINE_ISS7_LINKS(stk));
    tab = 0;

    fprintf(tempfp, "\t\t\t</%s>\n", ITU_SCCP_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the ansi sccp stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005   Bug ID:1788, 1783
 *
 ****************************************************************************/

static void 
SaveANSI_SCCP(ENGINE_ISS7Stack stk)
{
    fprintf(tempfp, 
            "\t\t\t<%s %s = \"%s\"",
            ANSI_SCCP_STRING, VARIANT_STRING,
            (ENGINE_ISS7_VARIANT_NAME(stk))?
                 ENGINE_ISS7_VARIANT_NAME(stk):"");

    if (ENGINE_ISS7_NUM_THREADS(stk) > 1)
    {
        fprintf(tempfp, 
                "\n\t\t\t           %s = \"%d\"",
                NUM_THREADS_STRING, ENGINE_ISS7_NUM_THREADS(stk));
    }

    fprintf(tempfp, ">\n");

    if (ven)
    {
        VCLASS_REC(ven).sccp.commit(tempfp);
    }

    tab = 3;
    SaveLink((ENGINE_Link)ENGINE_ISS7_LINKS(stk));
    tab = 0;

    fprintf(tempfp, "\t\t\t</%s>\n", ANSI_SCCP_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the ss7 stack informations in the file.
 *
 *  Input Parameters:
 *      ENGINE_ISS7Stack stk.
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
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1636   Configuration Persistance for MTP2 
 *                                                  is added.
 *  Mani   05-05-2005    Bug ID : 1793
 *  Mani   05-05-2005    Bug ID : 1793   Modified the VFrame object to commit 
 *                                        MTP2
 * 
 ****************************************************************************/

static void 
SaveSS7Stacks()
{
    ENGINE_SS7StackMgmt mgmt = 
        (ENGINE_SS7StackMgmt)ENGINE_APP_SS7_STACK_MGMT(application);
    ENGINE_ISS7Stack stk = 
        (ENGINE_ISS7Stack)ENGINE_APP_ISS7_STACK_CTRL(application);

    fprintf(tempfp, "\t<%s>\n", STACKS_STRING);

    if (mgmt != NULL)
    {
        fprintf(tempfp, 
                "\t\t<%s %s = \"%s\"\n",
                MGMT_CBS_STRING, LIBRARY_STRING,
                (ENGINE_S7_LIB_NAME(mgmt) == NULL)? 
                    "" : ENGINE_S7_LIB_NAME(mgmt));
        if (ENGINE_S7_MTP3_MGMT_CCITT(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_I_MTP3_STRING, ENGINE_S7_MTP3_MGMT_CCITT(mgmt));
        }
        if (ENGINE_S7_MTP3_MGMT_ANSI(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_A_MTP3_STRING, ENGINE_S7_MTP3_MGMT_ANSI(mgmt));
        }
        if (ENGINE_S7_ISUP_MGMT_CCITT(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_I_ISUP_STRING, ENGINE_S7_ISUP_MGMT_CCITT(mgmt));
        }
        if (ENGINE_S7_ISUP_MGMT_ANSI(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_A_ISUP_STRING, ENGINE_S7_ISUP_MGMT_ANSI(mgmt));
        }
        if (ENGINE_S7_SCCP_MGMT_CCITT(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_I_SCCP_STRING, ENGINE_S7_SCCP_MGMT_CCITT(mgmt));
        }
        if (ENGINE_S7_SCCP_MGMT_ANSI(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_A_SCCP_STRING, ENGINE_S7_SCCP_MGMT_ANSI(mgmt));
        }
        if (ENGINE_S7_SCCP_GTT_CCITT(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_I_GTT_STRING, ENGINE_S7_SCCP_GTT_CCITT(mgmt));
        }
        if (ENGINE_S7_SCCP_GTT_ANSI(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_A_GTT_STRING, ENGINE_S7_SCCP_GTT_ANSI(mgmt));
        }
        if (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_I_RC_STRING, ENGINE_S7_SCCP_SSN_ROUTE_CCITT(mgmt));
        }
        if (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(mgmt) != NULL)
        {
            fprintf(tempfp, 
                "\t\t                     %s = \"%s\"\n",
                MGMT_A_RC_STRING, ENGINE_S7_SCCP_SSN_ROUTE_ANSI(mgmt));
        }
        fprintf(tempfp, "\t\t/>\n");
    }

    if ((stk == NULL) || (ven == NULL))  
    {
        return;
    }
    
    fprintf(tempfp, "\t\t<%s>\n", INTELLINET_STRING);

    while (stk != NULL)
    {
        if(strcmp(ENGINE_ISS7_NAME(stk),ITU_MTP3_STRING) == 0)
        {
            SaveITU_MTP3(stk);
        }
        else if (strcmp(ENGINE_ISS7_NAME(stk),ANSI_MTP3_STRING) == 0)
        {
            SaveANSI_MTP3(stk);
        }
        else if (strcmp(ENGINE_ISS7_NAME(stk),ITU_ISUP_STRING) == 0)
        {
            SaveITU_ISUP(stk);
        }
        else if (strcmp(ENGINE_ISS7_NAME(stk),ANSI_ISUP_STRING) == 0)
        {
            SaveANSI_ISUP(stk);
        }
        else if (strcmp(ENGINE_ISS7_NAME(stk),ITU_TCAP_STRING) == 0)
        {
            SaveITU_TCAP(stk);
        }
        else if (strcmp(ENGINE_ISS7_NAME(stk),ANSI_TCAP_STRING) == 0)
        {
            SaveANSI_TCAP(stk);
        }
        else if (strcmp(ENGINE_ISS7_NAME(stk),ITU_SCCP_STRING) == 0)
        {
            SaveITU_SCCP(stk);
        }
        else if (strcmp(ENGINE_ISS7_NAME(stk),ANSI_SCCP_STRING) == 0)
        {
            SaveANSI_SCCP(stk);
        }
        stk = (ENGINE_ISS7Stack)ENGINE_ISS7_NEXT(stk);
    }

    fprintf(tempfp, "\t\t</%s>\n\n", INTELLINET_STRING);

    if ((ENGINE_APP_VENDOR_ONE_LEVELS(application) != NULL) ||
        (ENGINE_APP_VENDOR_TWO_LEVELS(application) != NULL))
    {
        fprintf(tempfp, "\t\t<%s>\n\n", VENDORS_STRING); 

        if (ENGINE_APP_VENDOR_ONE_LEVELS(application) != NULL)
        {
            if (mtp2ven)
            {
                VCLASS_REC(mtp2ven).mtp2.commit(tempfp);
            }
        }

        if (ENGINE_APP_VENDOR_TWO_LEVELS(application) != NULL)
        {
            if (mtp2ven)
            {
                VCLASS_REC(mtp2ven).mtp2.commit(tempfp);
            }
        }

        fprintf(tempfp, "\t\t</%s>\n\n", VENDORS_STRING); 
    }

    fprintf(tempfp, "\t</%s>\n\n", STACKS_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It saves the sigtran stack informations in the file.
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
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1639   Configuration Persistance for SCTP
 *                                                  is added.
 *  Mani   05-05-2005    Bug ID : 1764, 1765, 
 *                                1773, 1777
 *
 ****************************************************************************/

static void
SaveSigtranStacks()
{
    ENGINE_SIGTRANStack sigstack = 
              (ENGINE_SIGTRANStack)ENGINE_APP_SIGTRAN_STACK_CTRL(application);

    if (sigstack == NULL)
        return;

    fprintf(tempfp, "\t<%s>\n",SIGTRAN_STACK_STRING);
  
    while (sigstack != NULL)
    {
        if (strcmp(ENGINE_SIGTRAN_NAME(sigstack), SCTP_STACK_STRING) == 0)
        {
            if (sctpCallback)
            {
                sctpCallback(tempfp);
            }
        }
        else if (strcmp(ENGINE_SIGTRAN_NAME(sigstack), UAL_STACK_STRING) == 0)
        {
            if (ualCallback)
            {
                ualCallback(tempfp);
            }
        }
        else if (strcmp(ENGINE_SIGTRAN_NAME(sigstack), M3UA_STACK_STRING) == 0)
        {
            if (m3uaCallback)
            {
                m3uaCallback(tempfp);
            }
        }
        else if (strcmp(ENGINE_SIGTRAN_NAME(sigstack), M2UA_STACK_STRING) == 0)
        {
            if (m2uaCallback)
            {
                m2uaCallback(tempfp);
            }
        } 

        sigstack = (ENGINE_SIGTRANStack)ENGINE_SIGTRAN_NEXT(sigstack);
    }

    fprintf(tempfp, "\t</%s>\n",SIGTRAN_STACK_STRING);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      It will commit the changes which was made by the mml commands.
 *      All the changes will be written back into the file. 
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
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   06-04-2005    Bug ID : 1639   Configuration Persistance for SCTP
 *                                                  is added.
 *  Mani   05-05-2005    Bug ID : 1787
 *
 ****************************************************************************/

ITSDLLAPI int 
ENGINE_Commit(char* filename, char** bakfile)
{
    time_t t = time(0);
    struct tm* time_now = localtime(&t);
    char str[ITS_PATH_MAX];
    char filename1[ITS_PATH_MAX];
    char filename2[ITS_PATH_MAX];
    ITS_BOOLEAN fileAvl = ITS_FALSE;

    if ((filename == NULL) || (strcmp(filename,"") == 0))
    {
        return ITS_ENULLPTR;
    }

    tempfp = fopen(filename,"r"); 

    if (tempfp != NULL)
    {
        fileAvl = ITS_TRUE;
        fclose(tempfp);
    }

    tempfp = NULL;

    sprintf(filename1,
            "%s_%02d_%02d_%04d_%02d_%02d_%02d.tmp",filename,
            time_now->tm_mday, time_now->tm_mon+1, time_now->tm_year+1900,
            time_now->tm_hour, time_now->tm_min, time_now->tm_sec);

    if (fileAvl == ITS_TRUE)
    {
        sprintf(filename2,
                "%s_%02d_%02d_%04d_%02d_%02d_%02d.bak",filename,
                time_now->tm_mday, time_now->tm_mon+1, time_now->tm_year+1900,
                time_now->tm_hour, time_now->tm_min, time_now->tm_sec);
    }

    tempfp = fopen(filename1,"w+");

    if (tempfp == NULL) 
    {
        return ITS_ENULLPTR;
    }

    fprintf(tempfp, 
            "<%s %s          = \"%s\"\n",
            APPL_STRING, NAME_STRING, APPL_GetName());
    fprintf(tempfp, 
            "             %s          = \"%s\"\n",
            TYPE_STRING, 
            (!ENGINE_APP_IS_SERVICE(application))? 
                "console-application":"service");

    memset(str,0,ITS_PATH_MAX);
    GetGlobalStart(ENGINE_APP_GS_MASK(application),str);

    fprintf(tempfp, "             %s   = \"%s\"\n", GS_STRING, str);
    fprintf(tempfp, 
            "             %s       = \"%s\"",
            BINDING_STRING, 
            (ENGINE_APP_CPP_BINDING(application))? "CPP" : "C");

    if (ENGINE_APP_LIB_NAME(application) != NULL)
    {
        fprintf(tempfp, 
                "\n             %s       = \"%s\"",
                LIBRARY_STRING, ENGINE_APP_LIB_NAME(application));
    }

    if (ENGINE_APP_PRE_FUNC(application) != NULL)
    {
        fprintf(tempfp, 
                "\n             %s       = \"%s\"",
                PRE_FUNC_STRING, ENGINE_APP_PRE_FUNC(application));
    }

    if (ENGINE_APP_POST_FUNC(application) != NULL)
    {
        fprintf(tempfp, 
                "\n             %s      = \"%s\"",
                POST_FUNC_STRING, ENGINE_APP_POST_FUNC(application));
    }

    if (ENGINE_APP_SS7_SELECTOR(application) != NULL)
    {
        fprintf(tempfp, 
                "\n             %s   = \"%s\"",
                SS7_SELECT_STRING, ENGINE_APP_SS7_SELECTOR(application));
    }

    if (ENGINE_APP_APP_SELECTOR(application) != NULL)
    {
        fprintf(tempfp, 
                "\n             %s   = \"%s\"",
                APP_SELECT_STRING, ENGINE_APP_APP_SELECTOR(application));
    }

    if (ENGINE_APP_APP_DESELECTOR(application) != NULL)
    { 
        fprintf(tempfp, 
                "\n             %s = \"%s\"",
                APP_DESELECT_STRING, ENGINE_APP_APP_DESELECTOR(application));
    }

    if (ENGINE_APP_HMI_CB(application) != NULL)
    {
        fprintf(tempfp, 
                "\n             %s   = \"%s\"",
                HMI_CB_STRING, ENGINE_APP_HMI_CB(application));
    }

    if (ENGINE_APP_ALARM_CB(application) != NULL)
    {
        fprintf(tempfp, 
                "\n             %s = \"%s\"",
                ALARM_CB_STRING, ENGINE_APP_ALARM_CB(application));
    }

    fprintf(tempfp, ">\n");

    SaveAppOptions();
    SaveFeature();
    SaveParserExtension();
    SaveFT();
    SaveLS();
    SaveRoute();
//    SaveSCCPRoute();
    SaveDestination();
    SaveToolKitTrace();
    SaveApplicationTrace();
    SaveWorkItemPool();
    SaveWorkerPool();
    SaveBorderPool();
    SaveSS7Stacks();
    SaveSigtranStacks();

    fprintf(tempfp, "</%s>\n", APPL_STRING);

    fclose(tempfp);

    if (fileAvl == ITS_TRUE) 
    {
        int len = strlen(filename2) + 1;

        if(APPL_GetConfigDir())
        {
            len += strlen(APPL_GetConfigDir()) + 1;
        }
        
        if (rename(filename,filename2))
        {
            return -1;
        }
 
        *bakfile = (char*)calloc(1,len*sizeof(char));

        if (bakfile == NULL)
        {
            return ITS_ENULLPTR;
        }

        if (APPL_GetConfigDir())
        {
            strcpy(*bakfile, APPL_GetConfigDir());
            strcat(*bakfile,"/");
            strcat(*bakfile,filename2);
        }
        else
        {
            strcpy(*bakfile,filename2);
        }
    }

    if (rename(filename1,filename))
    {
        return -1;
    }

    return 0;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This will register the sigtran callbacks for commit. 
 *
 *  Input Parameters:
 *      char* prot - The protocol which is registering
 *      Sig_Callback sigC - Callback function for the protocol
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
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  Mani   05-05-2005    Bug ID : 1764, 1765
 *                                1773, 1777
 *
 ****************************************************************************/

DRVDLLAPI void
AddCommitCallback (char* prot, Sig_Callback sigC)
{
    if (strcmp(prot,"SCTP") == 0)
    {
        sctpCallback = sigC;
    }
    else if (strcmp(prot,"UAL") == 0)
    {
        ualCallback = sigC;
    }
    else if (strcmp(prot,"M2UA") == 0)
    {
        m2uaCallback = sigC;
    }
    else if (strcmp(prot,"M3UA") == 0)
    {
        m3uaCallback = sigC;
    }
}

