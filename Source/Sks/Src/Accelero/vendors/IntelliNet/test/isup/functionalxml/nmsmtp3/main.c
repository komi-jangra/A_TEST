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
 * $Id: main.c,v 1.1.1.1 2007-10-08 11:12:22 bsccs2 Exp $
 *
 * $Log: not supported by cvs2svn $
 * Revision 1.1.1.1  2007/10/04 13:24:59  bsccs2
 * init tree
 *
 * Revision 1.1.1.1  2007/08/03 06:49:28  cvsadmin
 * BscCs2
 *
 * Revision 1.1.1.1  2007/03/08 15:15:18  cvsadmin
 * BSC project
 *
 * Revision 9.1  2005/03/23 12:55:13  cvsadmin
 * Begin PR6.5
 *
 * Revision 8.2  2005/03/21 13:54:26  cvsadmin
 * PR6.4.2 Source Propagated to Current
 *
 * Revision 7.1  2002/08/26 22:10:39  mmiers
 * Begin PR6.2
 *
 * Revision 1.6  2002/08/01 16:01:46  ssharma
 * Merge from ISUP_PR7 branch.
 *
 * Revision 1.5.2.5  2002/07/06 06:16:52  hbalimid
 * Took care of all the warnings.
 *
 * Revision 1.5.2.4  2002/07/05 21:41:58  hbalimid
 * updated with GetErrorText.
 *
 * Revision 1.5.2.3  2002/07/04 23:39:36  hbalimid
 * More comments and prints added.
 *
 * Revision 1.5.2.2  2002/07/04 01:24:20  hbalimid
 * FAC added to ANSI95.
 *
 * Revision 1.5.2.1  2002/06/29 22:20:28  ssharma
 * dumpr and dumpl added.
 *
 * Revision 1.5  2002/06/27 17:44:46  hbalimid
 * Modified to take care of ANSI ISUP testing
 *
 * Revision 1.4  2002/06/25 19:06:30  ssingh
 * lower case for commands
 *
 * Revision 1.3  2002/06/23 23:29:57  hbalimid
 * all commands changed to lower case.
 *
 * Revision 1.2  2002/05/20 15:58:49  sjaddu
 * Merge from PR6, remove unwanted directories.
 *
 * Revision 1.1.2.2  2002/04/13 06:09:04  hbalimid
 * ISUP Functional test with NMS MTP3 and multiple vendor support at layer 2
 *
 *
 ****************************************************************************/

/*
 * system includes
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

/*
 * IntelliSS7 includes
 */
#include <its.h>
#include <engine.h>

/*
 * Local Include
 */
#include <sendISUPMsg.h>


#if defined(CCITT)
#define ISS7_Stack ISS7_CCITT_Stack
#elif defined(ANSI)
#define ISS7_Stack ISS7_ANSI_Stack
#endif

#if defined (CCITT)
static const char* section = "ITU-ISUP";
#elif defined (ANSI)
static const char* section = "ANSI-ISUP";
#else
#error "Protocol Not Defined"
#endif

#if defined (CCITT)
typedef struct _opcdpcinfo
{
    ITS_USHORT opc;
    ITS_USHORT dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#elif defined (ANSI)
typedef struct _opcdpcinfo
{
    ITS_UINT   opc;
    ITS_UINT   dpc;
    ITS_USHORT sio;
} OpcDpcInfo;
#else "Protocol Not Defined"
#endif

static char dmpFile[256];


int GetOpcDpcInfo(OpcDpcInfo*);
void ExecuteCommand(DBC_Server *dbc, const char *cmdLine);
void ISUPMgmt(ITS_POINTER object, ITS_POINTER userData,
              ITS_POINTER callData);

extern int PrintCICRecInfo(int opc, int dpc, int sio, int cic);
extern int PrintCicRangeInfo(ITS_USHORT opc, ITS_USHORT dpc,
                             ITS_USHORT sio, ITS_USHORT startcic,
                             ITS_USHORT endcic);
extern int ValidateCicRange(const char* cmdLine, ITS_USHORT* startcic,
                            ITS_USHORT* endcic);


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
main(int argc, const char** argv)
{
    const ushort MAXPATH = 256;
    char path[MAXPATH];

    memset( path, 0, MAXPATH );
    assert( getcwd(path, MAXPATH) != NULL );
    strcat( path, "/" );

    printf("Path = %s\n", path);

    APPL_SetConfigDir(path);
    APPL_SetName("ftest");
    APPL_SetConfigFileExtension("xml");

    /* 
     * DBC_SetDoCommand(ExecuteCommand);
     * This is not a correct usage
     * This is moved to Prefunc in ftest.c
     */

    ENGINE_Initialize(argc, argv, NULL, 0);

    ENGINE_Run(argc, argv);

    return (0);

}

int GetOpcDpcInfo(OpcDpcInfo* info)
{
    char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];
    RESFILE_Manager* res = NULL;

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    printf("GetOpcDpcInfo(): App Dmp Name = %s\n", dmpFile);

    ITS_C_ASSERT( info != NULL );

    res = RESFILE_CreateResourceManager(dmpFile);

    ITS_C_ASSERT( res != NULL );

    RESFILE_Lock(res);
    RESFILE_Rewind(res, section);

    while (RESFILE_GetKeyName(res, section, key, ITS_PATH_MAX)
                                                   == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section, val, ITS_PATH_MAX)
                                                   == ITS_SUCCESS)
    {
        if(strcmp(DEST_POINT_CODE_STRING, key) == 0)
        {
            info->dpc = RESFILE_ParseNum(val);
        }
        else if (strcmp(LOCAL_POINT_CODE_STRING, key) == 0)
        {
            info->opc = RESFILE_ParseNum(val);
        }
        else if (strcmp(SIO_STRING, key) == 0)
        {
            info->sio = RESFILE_ParseNum(val);
        }

    }
    RESFILE_Unlock(res);

    printf("DPC = %d\n", info->dpc);
    printf("OPC = %d\n", info->opc);
    printf("SIO = %d\n", info->sio);

    return ITS_SUCCESS;
}


/*.implementation: macro
 ****************************************************************************
 *  Purpose:
 *     Validate the command line 
 *
 *  Input Parameters:
 *      command string.
 *
 *  Input/Output Parameters:
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

#define VALIDATE_CMDLINE(x){\
        char *tmp, *dup; \
        int len = 0; \
        printf("Command entered = %s\n", cmdLine); \
        tmp = strchr(cmdLine,' '); \
        if( !tmp) tmp = strchr(cmdLine, '\t'); \
        if(!tmp) \
        { \
           printf("Usage: %s <cic>\n",x); \
           return; \
        } \
        else \
        { \
          *tmp = 0; tmp++; \
           while(*tmp == ' ' || *tmp == '\t') tmp++; \
           dup = tmp; \
           while( isdigit((int)*dup) ) dup++; \
           *dup = 0; \
           if( (len = strlen(tmp)) == 0 ) \
           { \
               printf("Usage: %s <cic>\n",x); \
               return; \
           } \
           hdr.context.cic = atoi(tmp); \
        } \
        }


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Execute Command for Debug  Console 
 *
 *  Input Parameters:
 *      command string.
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
ExecuteCommand(DBC_Server *dbc, const char *cmdLine)
{
    ITS_INT result = 0;
    ITS_HDR hdr;

    ITS_USHORT startcic = 0;
    ITS_USHORT endcic = 0;

    static ITS_BOOLEAN firstCall = ITS_TRUE;
    static OpcDpcInfo info;

    if( firstCall )
    {
        firstCall = ITS_FALSE;
        GetOpcDpcInfo(&info);
        printf("%d;%d;%d\n", info.dpc, info.opc, info.sio);
    }

    ITS_C_ASSERT(dbc != NULL);

    printf("------------------------------------------------------\n");

    if (DBC_Cmd(dbc, "acm", "SendACM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("acm");
        result = TestSendACMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) ACM return result = %d\n", result);
    }   
    else if (DBC_Cmd(dbc, "anm", "SendANM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("anm");
        result = TestSendANMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) ANM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "bla", "SendBLA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("bla");
        result = TestSendBLARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) BLA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "blo", "SendBLO", "<cic>", ""))
    {
        VALIDATE_CMDLINE("blo");
        result = TestSendBLORequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) BLO return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ccr", "SendCCR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ccr");
        result = TestSendCCRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CCR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cfn", "SendCFN", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cfn");
        result = TestSendCFNRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CFN return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgb", "SendCGB", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgb");
        result = TestSendCGBRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CGB return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgba", "SendCGBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgba");
        result = TestSendCGBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CGBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgu", "SendCGU", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgu");
        result = TestSendCGURequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CGU return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cgua", "SendCGUA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cgua");
        result = TestSendCGUARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CGUA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cot", "SendCOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cot");
        result = TestSendCOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) COT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cpg", "SendCPG", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cpg");
        result = TestSendCPGRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CPG return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cqm", "SendCQM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cqm");
        result = TestSendCQMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CQM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fot", "SendFOT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fot");
        result = TestSendFOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FOT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "grs", "SendGRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("grs");
        result = TestSendGRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) GRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "gra", "SendGRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("gra");
        result = TestSendGRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) GRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "iam", "SendIAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("iam");
        result = TestSendIAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) IAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inf", "SendINF", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inf");
        result = TestSendINFRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) INF return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "inr", "SendINR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("inr");
        result = TestSendINRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) INR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "lpa", "SendLPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lpa");
        result = TestSendLPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) LPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "pam", "SendPAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("pam");
        result = TestSendPAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) PAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rel", "SendREL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rel");
        result = TestSendRELRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) REL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "res", "SendRES", "<cic>", ""))
    {
        VALIDATE_CMDLINE("res");
        result = TestSendRESRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) RES return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rlc", "SendRLC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rlc");
        result = TestSendRLCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) RLC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "rsc", "SendRSC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("rsc");
        result = TestSendRSCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) RSC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sus", "SendSUS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sus");
        result = TestSendSUSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) SUS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "uba", "SendUBA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("uba");
        result = TestSendUBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) UBA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ubl", "SendUBL", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ubl");
        result = TestSendUBLRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) UBL return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "ucic", "SendUCIC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("ucic");
        result = TestSendUCICRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) UCIC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cic", "PrintCicInfo", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cic");
        PrintCICRecInfo(info.opc, info.dpc, info.sio, hdr.context.cic);
        printf("\n");
    }
    else if (DBC_Cmd(dbc, "cicrange", "CicInfo for a range", "<startcic> <endcic>", ""))
    {
        if(ValidateCicRange(cmdLine, &startcic, &endcic) != ITS_SUCCESS)
        {
            return;
        }
        /*printf("startcic = %d\n",startcic);
        printf("endcic = %d\n",endcic);*/

        PrintCicRangeInfo(info.opc, info.dpc, info.sio, startcic, endcic);
        printf("\n");

    }
    else if (DBC_Cmd(dbc, "dumpr", "Dump routing table", "", ""))
    {
        char *dump = NULL;

        ROUTE_DumpSS7ToIdHashtable(&dump);

        printf("%s\n", dump);
    }
    else if (DBC_Cmd(dbc, "dumpl", "Dump linkset table", "", ""))
    {
        char *dump = NULL;

        LINKSET_DumpLinkSetHashtable(&dump);

        printf("%s\n", dump);
    }

#if defined (ANSI)
    else if (DBC_Cmd(dbc, "cra", "SendCRA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cra");
        result = TestSendCRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CRA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "crm", "SendCRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("crm");
        result = TestSendCRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvr", "SendCVR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvr");
        result = TestSendCVRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CVR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "cvt", "SendCVT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("cvt");
        result = TestSendCVTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CVT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "exm", "SendEXM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("exm");
        result = TestSendACMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) EXM return result = %d\n", result);
    }

#endif /* ANSI */

#if defined (CCITT)
    else if (DBC_Cmd(dbc, "con", "SendCON", "<cic>", ""))
    {
        VALIDATE_CMDLINE("con");
        result = TestSendCONRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) CON return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "faa", "SendFAA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("faa");
        result = TestSendFAARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FAA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FAC return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "far", "SendFAR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("far");
        result = TestSendFARRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FAR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "frj", "SendFRJ", "<cic>", ""))
    {
        VALIDATE_CMDLINE("frj");
        result = TestSendFRJRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FRJ return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "idr", "SendIDR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("idr");
        result = TestSendIDRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) IDR return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "irs", "SendIRS", "<cic>", ""))
    {
        VALIDATE_CMDLINE("irs");
        result = TestSendIRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) IRS return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "nrm", "SendNRM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("nrm");
        result = TestSendNRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) NRM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "olm", "SendOLM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("olm");
        result = TestSendOLMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) OLM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sam", "SendSAM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sam");
        result = TestSendSAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) SAM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "sgm", "SendSGM", "<cic>", ""))
    {
        VALIDATE_CMDLINE("sgm");
        result = TestSendSGMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) SGM return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upa", "SendUPA", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upa");
        result = TestSendUPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) UPA return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "upt", "SendUPT", "<cic>", ""))
    {
        VALIDATE_CMDLINE("upt");
        result = TestSendUPTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) UPT return result = %d\n", result);
    }
    else if (DBC_Cmd(dbc, "usr", "SendUSR", "<cic>", ""))
    {
        VALIDATE_CMDLINE("usr");
        result = TestSendUSRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) USR return result = %d\n", result);
    }
#endif /* CCITT */

#if defined (CCITT) && defined (ITU_ISUP_97)
    else if (DBC_Cmd(dbc, "lop", "SendLOP", "<cic>", ""))
    {
        VALIDATE_CMDLINE("lop");
        result = TestSendLOPRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send LOP return result = %d\n", result);
    }
#endif /* ITU_ISUP_97 */

#if defined (ANSI) && defined (ANSI_ISUP_95)
    else if (DBC_Cmd(dbc, "fac", "SendFAC", "<cic>", ""))
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAC return result = %d\n", result);
    }
#endif /* ANSI_ISUP_95 */

    printf("Return Result from ISUP to APP = \"%s\"\n", ITS_GetErrorText(result));
    if( result != 0 )
    {
        printf("Please check \"IntelliSS7/common/include/its.h\"" \
                " for the error codes\n");
    }
    printf("\n------------------------------------------------------\n");

    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      ISUP Management callback
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
ISUPMgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{

    printf("Entered IsupMgmt\n");

    while(1)
    {
        sleep(300);
        printf("Entered IsupMgmt\n");
    }
    return;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      MTP3 Management callback
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
