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
 * ID:$Id: ISUP_Test.c,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:19  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 1.1  2003/02/19 15:35:50  vnitin
 * LOG:Add functional tester for Tandem
 * LOG:
 * LOG:Revision 1.3  2003/01/30 13:11:07  ssingh
 * LOG:VCIC related changes and CIC initialization as LBLOCKED.
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:47:42  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 * LOG:
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>
#include <sys/types.h>

#include <its.h>
#include <its_app.h>
#include <its_assertion.h>
#include <its_iniparse.h>
#include <its_dsm_stub.h>
#include <ss7_mgmt.h>

#include <isup_intern.h>
#include "ISUP_Test.h"
#include "ISUP_SendMsg.h"
#include "ISUP_PrintMsg.h"
#include "ISUP_ProcessMsg.h"

#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#else
#error "Protocol family not defined."
#endif

#if defined (CCITT)
static const char* section = "ITU-ISUP";
#elif defined (ANSI)
static const char* section = "ANSI-ISUP";
#else
#error "Protocol Not Defined"
#endif


extern ITS_HANDLE Tandem_handle;

#define ISS7_Stack Tandem_handle


#define NEWCODE 0
#define OLDCODE 1

#define USER_COMMAND (0x0002U) /* accept command from CLI app */

#if NEWCODE
static TRANSPORT_Control* tc = NULL;
static ITS_SHORT instance = 0;
static ITS_HDR hdr;
#endif

ITS_MUTEX configLock;

static void InitCircuitInfo(const char* dmpFile);
void WorkerDispatchFunction(ITS_HANDLE handle);
static void DumpITSEvent(ITS_EVENT* ev);
int    RouteApp(ITS_HDR *hdr,ITS_EVENT *event);
void   ExecuteCommand(const char *cmdLine);
int    GetOpcDpcInfo(OpcDpcInfo*);
extern int ValidateCicRange(const char* cmdLine, ITS_USHORT* startcic,
                            ITS_USHORT* endcic);
extern int PrintCICRecInfo(ITS_UINT opc, ITS_UINT dpc, ITS_UINT sio, ITS_USHORT cic);
extern int PrintCicRangeInfo(ITS_UINT opc, ITS_UINT dpc, ITS_USHORT sio,
                             ITS_USHORT startcic, ITS_USHORT endcic);

void   ISUP_HandleLocalCongestion (ITS_POINTER object, ITS_POINTER userData,
                                   ITS_POINTER callData);
void   ISUP_HandleMTP3Mgmt (ITS_POINTER object, ITS_POINTER userData,
                            ITS_POINTER callData);

/*------------------------------------------------------------------------------
 * Function for Locally unblocking first 24 circuits.
 *----------------------------------------------------------------------------*/
static void Send24UBLRequests()
{
    int i =0 ;
    ITS_HDR hdr;
    hdr.type = ITS_ISUP;
    for( i = 1; i < 2 ; ++i)
    {
        hdr.context.cic = (ITS_UINT) i;
        TestSendUBLRequest(ISS7_Stack, &hdr);
    }
}

/*------------------------------------------------------------------------------
 * Function for App specific initialization
 *----------------------------------------------------------------------------*/
void ftestPreFunc(void)
{
    static char dmpFile[256];

    printf("Ftest: Entered PreFunc\n");

    strcpy(dmpFile,APPL_GetConfigFileName());

    printf("App Dmp Name = %s\n", dmpFile);

    /* initialize the circuit Info */
    InitCircuitInfo(dmpFile);

    /* unblock Local circuits */
    Send24UBLRequests();

    printf("Ftest: Ready to accept Commands!\n");

    return;
}

/*------------------------------------------------------------------------------
 * Function for App specific Termination
 *----------------------------------------------------------------------------*/
void ftestPostFunc(void)
{
    printf("Ftest: Entered PostFunc\n");

    return;
}


/*------------------------------------------------------------------------------
 * Function for main application Loop
 *----------------------------------------------------------------------------*/
void
WorkerDispatchFunction(ITS_HANDLE handle)
{

    ITS_EVENT event;
    ITS_INT ret;

    /* Application specific initialization */
    ftestPreFunc();

    memset(&event,0,sizeof(event));

    while(1)
    {
        ret = ITS_GetNextEvent(handle, &event);
        if (ret != ITS_SUCCESS)
        {
                printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }

        printf("Application:: Event Src = %x\n", event.src);
        DumpITSEvent(&event);

        if ( event.src == ITS_ISUP_SRC )
        {

            printf("Application:: Decoding the Received Event from ISUP:\n");
            if (ISUP_ReceiveMsg(ISS7_Stack, &event) == ITS_SUCCESS)
            {
                printf("Application:: Worker: ISUP msg receive success\n");
                printf("------------------------------------------------------\n");
            }
        }
        else if ( event.src < ITS_LAST_USER_SRC)
        {
            /* User Message */
            if ( event.src == USER_COMMAND )
            {
               ExecuteCommand ((const char *)event.data);
            }
        }
    }
}

static void
DumpITSEvent(ITS_EVENT* ev)
{
    int i;

    switch(ev->src)
    {
        case ITS_ISUP_CCITT_SRC:
             printf("Event Source is ITS_ISUP_CCITT_SRC\n");
             break;
        case ITS_ISUP_ANSI_SRC:
             printf("Event Source is ITS_ISUP_ANSI_SRC\n");
             break;
        case ITS_MTP3_CCITT_SRC:
             printf("Event Source is ITS_MTP3_CCITT_SRC\n");
             break;
        case ITS_MTP3_ANSI_SRC:
             printf("Event Source is ITS_MTP3_ANSI_SRC\n");
             break;
        case ITS_TIMER_SRC:
             printf("Event Source is ITS_TIMER_SRC\n");
             break;
        default:
             printf("Event Source is * UNKNOWN * (%d)\n", ev->src);
             break;
    }

    printf("Event Length: %d\n", ev->len);
    printf("Event Dump follows:\n");

    for (i = 0; i < ev->len; i++)
    {
        printf("%02x ", ev->data[i]);
        if (!((i+1) % 20))
        {
            printf("\n");
        }
    }
    if ((i+1) % 20)
    {
        printf("\n");
    }

    printf("------------------------------------------------------\n");
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      InitCircuitInfo
 *
 *  Input Parameters:
 *      const char* dmpFile
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
 *      This function is to modified with RESFILE Manager
 *
 *  See Also:
 ****************************************************************************/
static void
InitCircuitInfo(const char* dmpFile)
{
    FILE* fp = NULL;
    char buf[128];
    char* tmp = NULL;
    char* section = "[ANSI-ISUP]";

    short startCic = -1;
    short numCics = 0;
    short cicCount = 0;
    short i = 0;

    assert(dmpFile != NULL);

    MUTEX_AcquireMutex(&configLock);

    cicStatus[cicCount].cic_num = (ITS_USHORT)(-1);

    fp  = fopen(dmpFile, "r");
    assert(fp != NULL);

    while( !feof(fp) )
    {
        fgets(buf, 128, fp);

        buf[strlen(buf)-1] = 0;

        if( strcmp(section,buf) == 0 )
        {
            printf("Entered ISUP : %s\n", buf);
            break;
        }
    }

    while( !feof(fp) )
    {
        fgets(buf, 128, fp);
        buf[strlen(buf)-1] = 0;

        tmp = strchr((const char*)buf,'=');
        if( !tmp ) continue;
        *tmp = 0;
        tmp++;

        if((strcmp("startCic",buf) == 0))
        {
            cicStatus[cicCount].cic_num = (ITS_USHORT)RESFILE_ParseNum(tmp);
            startCic = (ITS_SHORT)RESFILE_ParseNum(tmp);
        }
        else if((strcmp("numberCics",buf) == 0))
        {
            numCics = (ITS_SHORT)RESFILE_ParseNum(tmp);

            for( i = 0; i < numCics; i++)
            {
                cicStatus[cicCount].cic_num = (ITS_USHORT)(startCic + i);
                cicCount+=1;
            }
        }

        if( feof(fp) ) break;
    }

    for(i=0; i< cicCount; i++)
    {
        cicStatus[i].cic_state = CKTS_IDLE_LBLOCKED;
        cicStatus[i].fsm_state = CPC_IDLE;
        printf("CIC index = %3d | CIC number = %3d | CIC State : %d  and FSM State : %d\n",
                              i, cicStatus[i].cic_num, cicStatus[i].cic_state,
                                                       cicStatus[i].fsm_state);
    }

    numOfCICs = cicCount;

    printf("InitCircuitInfo(): Total Number of Cics = %d\n", numOfCICs);

    sleep(2);

    MUTEX_ReleaseMutex(&configLock);

    fclose(fp);

    return;
}

#if OLDCODE
#define VALIDATE_CMDLINE(x){\
        char *tmp, *dup; \
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
           while( isdigit(*dup) ) dup++; \
           *dup = 0; \
           if( strlen(tmp) == 0 ) \
           { \
               printf("Usage: %s <cic>\n",x); \
               return; \
           } \
           hdr.context.cic = atoi(tmp); \
        } \
        }
#endif

#if NEWCODE
#define VALIDATE_CMDLINE(x){\
        char *tmp, *dup; \
        char buf[ITS_PATH_MAX]; \
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
           while( isdigit(*dup) ) dup++; \
           *dup = 0; \
           if( strlen(tmp) == 0 ) \
           { \
               printf("Usage: %s <cic>\n",x); \
               return; \
           } \
           hdr.context.cic = atoi(tmp); \
        } \
        }
#endif


void
ExecuteCommand(const char *cmdLine)
{
    ITS_INT result = 0;
    ITS_INT ret = 0;
    ITS_HDR hdr;
    char buf[ITS_PATH_MAX];

    ITS_USHORT startcic = 0;
    ITS_USHORT endcic = 0;

    static ITS_BOOLEAN firstCall = ITS_TRUE;
    static OpcDpcInfo info;
    ITS_UINT i;
    ISUP_CIC_INFO *cic_rec = NULL;

#if OLDCODE /* retianed */
    if( firstCall )
    {
        firstCall = ITS_FALSE;
        GetOpcDpcInfo(&info);
    }
#endif

#if NEWCODE
    if( firstCall )
    {
        firstCall = ITS_FALSE;
        GetOpcDpcInfo(&info);
    }
#endif

    printf("------------------------------------------------------\n");

    if ( strncmp(cmdLine, "acm", 3) == 0)
    {
        VALIDATE_CMDLINE("acm");
        result = TestSendACMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send ACM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "anm", 3) == 0)
    {
        VALIDATE_CMDLINE("anm");
        result = TestSendANMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send ANM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "bla", 3) == 0)
    {
        VALIDATE_CMDLINE("bla");
        result = TestSendBLARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send BLA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "blo", 3) == 0)
    {
        VALIDATE_CMDLINE("blo");
        result = TestSendBLORequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send BLO return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "ccr", 3) == 0)
    {
        VALIDATE_CMDLINE("ccr");
        result = TestSendCCRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CCR return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cfn", 3) == 0)
    {
        VALIDATE_CMDLINE("cfn");
        result = TestSendCFNRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CFN return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cgb", 3) == 0)
    {
        VALIDATE_CMDLINE("cgb");
        result = TestSendCGBRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGB return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cgba", 4) == 0)
    {
        VALIDATE_CMDLINE("cgba");
        result = TestSendCGBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGBA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cgu", 3) == 0)
    {
        VALIDATE_CMDLINE("cgu");
        result = TestSendCGURequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGU return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cgua", 4) == 0)
    {
        VALIDATE_CMDLINE("cgua");
        result = TestSendCGUARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CGUA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cot", 3) == 0)
    {
        VALIDATE_CMDLINE("cot");
        result = TestSendCOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send COT return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cpg", 3) == 0)
    {
        VALIDATE_CMDLINE("cpg");
        result = TestSendCPGRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CPG return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cqm", 3) == 0)
    {
        VALIDATE_CMDLINE("cqm");
        result = TestSendCQMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CQM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "fot", 3) == 0)
    {
        VALIDATE_CMDLINE("fot");
        result = TestSendFOTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FOT return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "grs", 3) == 0)
    {
        VALIDATE_CMDLINE("grs");
        result = TestSendGRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send GRS return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "gra", 3) == 0)
    {
        VALIDATE_CMDLINE("gra");
        result = TestSendGRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send GRA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "iam", 3) == 0)
    {
        VALIDATE_CMDLINE("iam");
        result = TestSendIAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IAM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "inf", 3) == 0)
    {
        VALIDATE_CMDLINE("inf");
        result = TestSendINFRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send INF return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "inr", 3) == 0)
    {
        VALIDATE_CMDLINE("inr");
        result = TestSendINRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send INR return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "lpa", 3) == 0)
    {
        VALIDATE_CMDLINE("lpa");
        result = TestSendLPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send LPA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "pam", 3) == 0)
    {
        VALIDATE_CMDLINE("pam");
        result = TestSendPAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send PAM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "rel", 3) == 0)
    {
        VALIDATE_CMDLINE("rel");
        result = TestSendRELRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send REL return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "res", 3) == 0)
    {
        VALIDATE_CMDLINE("res");
        result = TestSendRESRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RES return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "rlc", 3) == 0)
    {
        VALIDATE_CMDLINE("rlc");
        result = TestSendRLCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RLC return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "rsc", 3) == 0)
    {
        VALIDATE_CMDLINE("rsc");
        result = TestSendRSCRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send RSC return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "sus", 3) == 0)
    {
        VALIDATE_CMDLINE("sus");
        result = TestSendSUSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SUS return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "uba", 3) == 0)
    {
        VALIDATE_CMDLINE("uba");
        result = TestSendUBARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UBA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "ubl", 3) == 0)
    {
        VALIDATE_CMDLINE("ubl");
        result = TestSendUBLRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UBL return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "ucic", 4) == 0)
    {
        VALIDATE_CMDLINE("ucic");
        result = TestSendUCICRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UCIC return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cic", 3) == 0)
    {
        VALIDATE_CMDLINE("cic");
        PrintCICRecInfo(info.opc, info.dpc, info.sio, (ITS_USHORT)hdr.context.cic);
        printf("\n");
    }
    else if (strncmp(cmdLine, "cicrange", 8) == 0)
    {
        /* printf("ExecuteCommand:cmdLine = *%s*\n",cmdLine); */
        if(ValidateCicRange(cmdLine, &startcic, &endcic) != ITS_SUCCESS)
        {
            return;
        }
        /* printf("startcic = %d\n",startcic); */
        /* printf("endcic = %d\n",endcic); */

        PrintCicRangeInfo(info.opc, info.dpc, info.sio, startcic, endcic);
        printf("\n");
    }

#if defined (ANSI)
    else if (strncmp(cmdLine, "cra", 3) == 0)
    {
        VALIDATE_CMDLINE("cra");
        result = TestSendCRARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CRA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "crm", 3) == 0)
    {
        VALIDATE_CMDLINE("crm");
        result = TestSendCRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CRM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cvr", 3) == 0)
    {
        VALIDATE_CMDLINE("cvr");
        result = TestSendCVRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CVR return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "cvt", 3) == 0)
    {
        VALIDATE_CMDLINE("cvt");
        result = TestSendCVTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CVT return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "exm", 3) == 0)
    {
        VALIDATE_CMDLINE("exm");
        result = TestSendACMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send EXM return result = %d\n", result);
    }

    /* To test the ANSI/ITU pegs - Arun */

    else if (strncmp(cmdLine, "ia_get_peg", 10) == 0)
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value;
        ITS_UINT pg = PEG_ISUP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
            printf("**** Invalid Command Arguments *******\n");
            return;
        }

        for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
        {
            if ( strstr(pgName, ISUP_Peg_Desc[i]))
            {
                pg = i;
            }
        }

        if (pg == PEG_ISUP_NUM_PEGS)
        {
            printf("**** Invalid Peg Type *******\n");
            return;
        }

        printf("Getting the Peg for %s Now\n", pgName);

        value = PEG_GetPeg(ANSI_ISUP_Pegs, pg);

        printf("value is %d\n", value);
    }

    else if (strncmp(cmdLine, "ia_get_cic_peg", 14) == 0)
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT value, cic;
        ISUP_PCIC pcic;
        OpcDpcInfo info;
        ITS_UINT pg = PEG_ISUP_CIC_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s %d", buf, pgName, &cic);
        if (ret != 3)
        {
            printf("**** Invalid Command Arguments *******\n");
            return;
        }

        for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
        {
            if ( strstr(pgName, ISUP_CIC_Peg_Desc[i]))
            {
                pg = i;
            }
        }

        if (pg == PEG_ISUP_CIC_NUM_PEGS)
        {
            printf("**** Invalid Peg Type *******\n");
            return;
        }

        GetOpcDpcInfo(&info);

        /* Convert cic, opc, dpc to pcic */
        ISUP_PCICFromParts(&pcic, info.opc, info.dpc, (ITS_OCTET)info.sio, (ITS_USHORT)cic);

        /* Get cic_rec using the pcic as key */
        cic_rec = ISUP_FindPcic( pcic);
        if (cic_rec == NULL)
        {
            printf("No CIC rec found \n");
            return;
        }

        printf(buf, "Getting the Peg for %s Now\n", pgName);

        value = PEG_GetPeg(&cic_rec->ISUP_CIC_PEGS, pg);

        printf("value is %d\n", value);
    }

    else if (strncmp(cmdLine, "ia_clr_peg", 10) == 0)
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT pg = PEG_ISUP_NUM_PEGS;

        ret = sscanf(cmdLine, "%s %s", buf, pgName);
        if (ret != 2)
        {
             printf("**** Invalid Command Arguments *******\n");
             return;
        }

        for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
        {
            if ( strstr(pgName, ISUP_Peg_Desc[i]))
            {
                pg = i;
            }
        }

        if (pg == PEG_ISUP_NUM_PEGS)
        {
            printf("**** Invalid Peg Type *******\n");
            return;
        }

        printf("Clearing the Pegs for %s Now\n", pgName);

        PEG_ClearPeg(ANSI_ISUP_Pegs, pg);

    }

    else if (strncmp(cmdLine, "ia_clr_cic_peg", 14) == 0)
    {
        char pgName[ITS_PATH_MAX];
        ITS_UINT pg = PEG_ISUP_NUM_PEGS;
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %d", buf, pgName, &cic);
        if (ret != 3)
        {
             printf("**** Invalid Command Arguments *******\n");
             return;
        }

        for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
        {
            if ( strstr(pgName, ISUP_CIC_Peg_Desc[i]))
            {
                pg = i;
            }
        }

        if (pg == PEG_ISUP_CIC_NUM_PEGS)
        {
            printf("**** Invalid Peg Type *******\n");
             return;
        }

        GetOpcDpcInfo(&info);

        /* Convert cic, opc, dpc to pcic */
        ISUP_PCICFromParts(&pcic, info.opc, info.dpc, (ITS_OCTET)info.sio, (ITS_USHORT)cic);

        /* Get cic_rec using the pcic as key */
        cic_rec = ISUP_FindPcic( pcic);
        if (cic_rec == NULL)
        {
            printf("No CIC rec found \n");
            return;
        }

        printf("Clearing the Pegs for %s Now\n", pgName);

        PEG_ClearPeg(&cic_rec->ISUP_CIC_PEGS, pg);

    }

    else if (strncmp(cmdLine, "ia_clr_all_peg", 14) == 0)
    {
        PEG_ClearBlock(ANSI_ISUP_Pegs);

        printf("Clearing All ANSI ISUP Pegs \n");
    }

#endif /* ANSI */

#if defined (CCITT)
    else if (strncmp(cmdLine, "con", 3) == 0)
    {
        VALIDATE_CMDLINE("con");
        result = TestSendCONRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send CON return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "faa", 3) == 0)
    {
        VALIDATE_CMDLINE("faa");
        result = TestSendFAARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "fac", 3) == 0)
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) FAC return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "far", 3) == 0)
    {
        VALIDATE_CMDLINE("far");
        result = TestSendFARRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAR return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "frj", 3) == 0)
    {
        VALIDATE_CMDLINE("frj");
        result = TestSendFRJRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FRJ return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "idr", 3) == 0)
    {
        VALIDATE_CMDLINE("idr");
        result = TestSendIDRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IDR return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "irs", 3) == 0)
    {
        VALIDATE_CMDLINE("irs");
        result = TestSendIRSRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send IRS return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "nrm", "3) == 0)
    {
        VALIDATE_CMDLINE("nrm");
        result = TestSendNRMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send NRM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "olm", 3) == 0)
    {
        VALIDATE_CMDLINE("olm");
        result = TestSendOLMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send OLM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "sam", 3) == 0)
    {
        VALIDATE_CMDLINE("sam");
        result = TestSendSAMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SAM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "sgm", 3) == 0)
    {
        VALIDATE_CMDLINE("sgm");
        result = TestSendSGMRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send SGM return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "upa", 3) == 0)
    {
        VALIDATE_CMDLINE("upa");
        result = TestSendUPARequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UPA return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "upt", 3) == 0)
    {
        VALIDATE_CMDLINE("upt");
        result = TestSendUPTRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send UPT return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "usr", 3) == 0)
    {
        VALIDATE_CMDLINE("usr");
        result = TestSendUSRRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send USR return result = %d\n", result);
    }
    else if (strncmp(cmdLine, "deststat", 8) == 0)
    {
        ISUP_PrintAllOpcDpcStat();
    }
    else if (strncmp(cmdLine, "cicpegs", 7) == 0)
    {
        VALIDATE_CMDLINE("cicpegs");
        PrintCICPegsInfo(info.opc, info.dpc, info.sio, hdr.context.cic);
        printf("\n");
    }
    else if (strncmp(cmdLine, "pegs", 4) == 0)
    {
        PrintPegsInfo();
    }
    else if (strncmp(cmdLine, "destpegs", 8) == 0)
    {
        PrintDestPegsInfo(info.opc, info.dpc, info.sio);
    }

#endif /* CCITT */

#if defined (CCITT) && defined (ITU_ISUP_97)
    else if (strncmp(cmdLine, "lop", 3) == 0)
    {
        VALIDATE_CMDLINE("lop");
        result = TestSendLOPRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send LOP return result = %d\n", result);
    }
#endif /* ITU_ISUP_97 */

#if defined (ANSI) && defined (ANSI_ISUP_95)
    else if (strncmp(cmdLine, "fac", 3) == 0)
    {
        VALIDATE_CMDLINE("fac");
        result = TestSendFACRequest( ISS7_Stack, &hdr );
        printf("\n(Application to ISUP Stack) Send FAC return result = %d\n", result);
    }
#endif /* ANSI_ISUP_95 */
    else if (strncmp(cmdLine, "stat", 4) == 0)
    {
        result = ISUP_PrintAllOpcDpcStat();
        printf("\n Route Stats result = %d\n", result);
    }

    printf("------------------------------------------------------\n");

    return;
}


int GetOpcDpcInfo(OpcDpcInfo* info)
{
    static char dmpFile[24];

    char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];
    RESFILE_Manager* res = NULL;

    strcpy(dmpFile,APPL_GetConfigFileName());
    strcat(dmpFile,".dmp");

    ITS_C_ASSERT( info != NULL );

    res = RESFILE_CreateResourceManager("$NODEA.VNITIN.NSKINI");

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
            info->sio = (ITS_USHORT)RESFILE_ParseNum(val);
        }

    }
    RESFILE_Unlock(res);

    printf("\nDPC = %d |", info->dpc);
    printf("OPC = %d |", info->opc);
    printf("SIO = %d\n", info->sio);

    return ITS_SUCCESS;
}

void
ISUP_HandleLocalCongestion (ITS_POINTER object, ITS_POINTER userData,
                            ITS_POINTER callData)
{
     ISUP_CONGESTION_ENTRY *cong = (ISUP_CONGESTION_ENTRY *)callData;

     printf("------------------------------------------------------\n");
     switch (cong->congId)
     {
     case  ITS_ISUP_LOC_CONGLEVEL1_IND:
           printf("Application: ISUP Local Congestion Level 1 Detected\n");
           printf("====  Cut down Traffic by 1/3 ====\n");
	   break;

     case  ITS_ISUP_LOC_CONGLEVEL2_IND:
           printf("Application: ISUP Local Congestion Level 2 Detected\n");
           printf("====  Cut down Traffic by 2/3 ====\n");
           break;

     case  ITS_ISUP_LOC_CONGLEVEL3_IND:
           printf("Application: ISUP Local Congestion Level 3 Detected\n");
           printf("====  Cut down complete Traffic ====\n");
	   break;

     case  ITS_ISUP_LOC_NOCONG_IND:
           printf("Application: ISUP Local Congestion ceased\n");
           printf("====  Resume Traffic Procedures ====\n");
           break;
     }
     printf("------------------------------------------------------\n");
     return;
}

void
ISUP_HandleMTP3Mgmt (ITS_POINTER object, ITS_POINTER userData,
                     ITS_POINTER callData)
{
     ITS_EVENT *ev = (ITS_EVENT *)callData;

     printf("------------------------------------------------------\n");

     switch (ev->data[0])
     {
     case MTP3_MSG_PAUSE:
           printf ("Application: Rcvd MTP3 PAUSE from OPC|DPC|NI %06x\n",
           MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)&ev->data[1])->affected));
           printf("====  Stop Traffic Procedures ====\n");
           break;

     case MTP3_MSG_RESUME:
           printf ("Application: Rcvd MTP3 RESUME from OPC|DPC|NI %06x\n",
           MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)&ev->data[1])->affected));
           printf("====  Resume Traffic Procedures ====\n");
           break;

     case MTP3_MSG_STATUS:
           printf ("Application: Rcvd MTP3 STATUS from opc|dpc|ni %06x cause %d cong %d\n",
           MTP3_PC_GET_VALUE(((MTP3_STATUS_ANSI *)&ev->data[1])->affected),
           ((MTP3_STATUS_ANSI *)&ev->data[1])->cause,
           ((MTP3_STATUS_ANSI *)&ev->data[1])->congLevel);
           printf("====  MTP3 Status Indication Received  ====\n");

     default:
           printf ("Application: Received MTP3 USER DATA \n");
           break;
     }
     printf("------------------------------------------------------\n");
     return;
}
