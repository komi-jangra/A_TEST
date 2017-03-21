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
 *
 *  ID: $Id: AppDbc.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:42  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/28 10:53:51  adutta
 * LOG: Remodeled for MSC Sim
 * LOG:
 * LOG: Revision 1.3  2005/02/23 10:15:39  csireesh
 * LOG: IOSCDMA Codec Implementation.
 * LOG:
 * LOG: Revision 1.2  2005/02/11 09:14:53  csireesh
 * LOG: Sanitized Sample App for SCCP-CO
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:43:20  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#include <iostream>
#include <stdlib.h>

#include <its++.h>
#include <engine++.h>
#include <AppDbc.h>
#include <its_trace.h>
#include <App.h>
#include <AppTrace.h>
#include <AppDsm.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#define ALPHABET  "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
#define SPECIAL_CHAR  "#\\`~!@$%&*()-_+=|^?{}[]:;'<>,.?/"

/*****************************************************************************
 *  Purpose:
 *      This function process the commands given from debug console.
 *          Below is an example for turning Debug Trace on similarly 
 *          other commands could be implemented - for load start-traffic,
 *          for statistics - stats, for perfomance - stats etc.
 *
 *  Input Parameters:
 *      istream commandLine.
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
void
AppDbcServer::DoCommand(istream& commandLine)
{
    ITS_CTXT slr = 0;
    ITS_CTXT dlr = 0;
    ITS_CTXT conref = 0;
    ITS_HDR hdr;
    ITS_HDR rhdr;
    DsmInfo *dInfo = NULL;
    int ret;
    char buf[ITS_PATH_MAX];

    if (Cmd("AppDbgTrace", "Application Debug Trace", "<on, off>"))
    {
        string onOff;
        string dummy;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnDebugTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnDebugTraceOnOff(ITS_FALSE);
        }
    }
    else if (Cmd("AppWarTrace", "Application Warning Trace", "<on, off>"))
    {
        string onOff;
        string dummy;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnWarningTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnWarningTraceOnOff(ITS_FALSE);
        }
    }
    else if (Cmd("AppErrTrace", "Application Error Trace", "<on, off>"))
    {
        string onOff;
        string dummy;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnErrorTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnErrorTraceOnOff(ITS_FALSE);
        }
    }
    else if (Cmd("AppCriTrace", "Application Critical Trace", "<on, off>"))
    {
        string onOff;
        string dummy;

        commandLine >> dummy >> onOff;

        if (onOff == "on")
        {
            TRACE_TurnCriticalTraceOnOff(ITS_TRUE);
        }
        else if (onOff == "off")
        {
            TRACE_TurnCriticalTraceOnOff(ITS_FALSE);
        }
    }
    else if (Cmd("AppDumpCtxt", "AppDumpCtxt", "<conref>"))
    {
        std::string temp = "";
        string dummy;
        char tem[7];

        ITS_OCTET cgp_gtt_dig[SCCP_MAX_ADDR_LEN];
        ITS_USHORT cgp_gtt_len = 0;
        ITS_OCTET cgp_gtt_type = 0;

        ITS_OCTET cdp_gtt_dig[SCCP_MAX_ADDR_LEN];
        ITS_USHORT cdp_gtt_len = 0;
        ITS_OCTET cdp_gtt_type = 0;

        commandLine >> dummy >> temp;

        if (temp == "")
        {
            oss << "Error : Conref value is not given"
                   "/Invalid Arguments\n"
                << "Usage: AppDumpCtxt <conref>\n" << endl;
            return;
        }

        if (strpbrk(temp.c_str(),ALPHABET) ||
           (strpbrk(temp.c_str(),SPECIAL_CHAR)))
        {
            oss << "Error : Incorrect Conref value given"
                   "/Invalid Arguments\n"
                << "Usage: AppDumpCtxt <conref>\n" << endl;
            return;
        }
      
        conref = (atoi(temp.c_str()));

        if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                            != ITS_SUCCESS)
        {
            oss << "AppDumpCtxt::Retrieve Ctxt failed "
                               "for Conref: " << conref << endl;
        }
        else
        {
            oss << "AppDumpCtxt::Retrieve Ctxt successful"
                               " for Conref: " << conref << endl;

            oss << "AppDumpCtxt:: SLR: " << dInfo->sccpinfo.slr << endl;
            oss << "AppDumpCtxt:: DLR: " << dInfo->sccpinfo.dlr << endl;
            oss << "AppDumpCtxt:: OPC: " << dInfo->opc << endl;
            oss << "AppDumpCtxt:: DPC: " << dInfo->dpc << endl;

            oss << "AppDumpCtxt:: State: ";
            switch (dInfo->sccpinfo.state)
            {
                case SCCP_CONN_IDLE:
                {
                    oss << "SCCP_CONN_IDLE";
                    break;
                }
                case SCCP_CONN_IN_PEND:
                {
                    oss << "SCCP_CONN_IN_PEND";
                    break;
                }
                case SCCP_CONN_OUT_PEND:
                {
                    oss << "SCCP_CONN_OUT_PEND";
                    break;
                }
                case SCCP_DATA_TRANSFER:
                {
                    oss << "SCCP_DATA_TRANSFER";
                    break;
                }
                case SCCP_IN_RESET_PEND:
                {
                    oss << "SCCP_IN_RESET_PEND";
                    break;
                }
                case SCCP_OUT_RESET_PEND:
                {
                    oss << "SCCP_OUT_RESET_PEND";
                    break;
                }
                case SCCP_IN_RELEASE_PEND:
                {
                    oss << "SCCP_IN_RELEASE_PEND";
                    break;
                }
                case SCCP_OUT_RELEASE_PEND:
                {
                    oss << "SCCP_OUT_RELEASE_PEND";
                    break;
                }
            }
            oss << endl << endl;

            if(dInfo->src) 
            {
                oss << "AppDumpCtxt:: Session Initiator Self "<< endl << endl; 
            }
            else
            {
                oss << "AppDumpCtxt:: Session Initiator Remote "<< endl << endl;
            }  

            oss << "AppDumpCtxt::CallingPartyAddr PC: "
                << dInfo->cgpa->GetPointCode() << endl;
            oss << "AppDumpCtxt::CallingPartyAddr SSN: "
                <<  (int)dInfo->cgpa->GetSSN() << endl;

            if (dInfo->cgpa->IsRoutedByPCSSN())
            {
                oss << "AppDumpCtxt::CallingPartyAddr ROUT_TYPE: "
                                        "RouteBySSN " << endl;
            }
            else
            {
                oss << "AppDumpCtxt::CallingPartyAddr ROUT_TYPE: "
                                        "RouteByGT " << endl;
            }

            if (dInfo->cgpa->IsInternationalRouting())
            {
                oss << "AppDumpCtxt::CallingPartyAddr NI: "
                                        "International " << endl;
            }
            else
            {
                oss << "AppDumpCtxt::CallingPartyAddr NI: "
                                        "National " << endl;
            }

            if (dInfo->cgpa->HasGlobalTitle())
            {
                dInfo->cgpa->GetGlobalTitle(cgp_gtt_type, 
                                    cgp_gtt_dig, cgp_gtt_len);

                    switch (cgp_gtt_type)
                    {
#if defined(ANSI)
                        case SCCP_CPA_GTTI_TNE_ANSI:
                        {
                            oss << "AppDumpCtxt::CallingPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TNE_ANSI" << endl;
                            break;
                        }
                        case SCCP_CPA_GTTI_TRANS_ANSI:
                        {
                            oss << "AppDumpCtxt::CallingPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TRANS_ANSI" << endl;
                            break;
                        }
#endif

#if defined(CCITT)
                        case SCCP_CPA_GTTI_NATURE:
                        {
                            oss << "AppDumpCtxt::CallingPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TNE_ANSI" << endl;
                            break;
                        }

                        case SCCP_CPA_GTTI_TRANS_CCITT:
                        {
                            oss << "AppDumpCtxt::CallingPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TRANS_CCITT" << endl;
                            break;
                        }

                        case SCCP_CPA_GTTI_TNE_CCITT:
                        {
                            oss << "AppDumpCtxt::CallingPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TNE_CCITT" << endl;
                            break;
                        }

                        case SCCP_CPA_GTTI_ALL:
                        {
                            oss << "AppDumpCtxt::CallingPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_ALL" << endl;
                            break;
                        }
#endif
                    }
                oss << "AppDumpCtxt::CalledPartyAddr GTT_DIG: " << endl;

                for (int i = 0; i < cgp_gtt_len; i++)
                {
                    sprintf(tem,"0x%02x ",cgp_gtt_dig[i]);
                    oss << tem;
                }
                oss << endl; 
            }
            oss << endl; 

            oss << "AppDumpCtxt::CalledPartyAddr PC: "
                << dInfo->cdpa->GetPointCode() << endl;
            oss << "AppDumpCtxt::CalledPartyAddr SSN: "
                <<  (int)dInfo->cdpa->GetSSN() << endl;

            if (dInfo->cdpa->IsRoutedByPCSSN())
            {
                oss << "AppDumpCtxt::CalledPartyAddr ROUT_TYPE: "
                                        "RouteBySSN " << endl;
            }
            else
            {
                oss << "AppDumpCtxt::CalledPartyAddr ROUT_TYPE: "
                                        "RouteByGT " << endl;
            }

            if (dInfo->cdpa->IsInternationalRouting())
            {
                oss << "AppDumpCtxt::CalledPartyAddr NI: "
                                        "International " << endl;
            }
            else
            {
                oss << "AppDumpCtxt::CalledPartyAddr NI: "
                                        "National " << endl;
            }

            if (dInfo->cdpa->HasGlobalTitle())
            {
                dInfo->cdpa->GetGlobalTitle(cdp_gtt_type,
                                    cdp_gtt_dig, cdp_gtt_len);

                    switch (cdp_gtt_type)
                    {
#if defined(ANSI)
                        case SCCP_CPA_GTTI_TNE_ANSI:
                        {
                            oss << "AppDumpCtxt::CallingPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TNE_ANSI" << endl;
                            break;
                        }
                        case SCCP_CPA_GTTI_TRANS_ANSI:
                        {
                            oss << "AppDumpCtxt::CalledPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TRANS_ANSI" << endl;
                            break;
                        }
#endif

#if defined(CCITT)
                        case SCCP_CPA_GTTI_NATURE:
                        {
                            oss << "AppDumpCtxt::CalledPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TNE_ANSI" << endl;
                            break;
                        }

                        case SCCP_CPA_GTTI_TRANS_CCITT:
                        {
                            oss << "AppDumpCtxt::CalledPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TRANS_CCITT" << endl;
                            break;
                        }

                        case SCCP_CPA_GTTI_TNE_CCITT:
                        {
                            oss << "AppDumpCtxt::CalledPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_TNE_CCITT" << endl;
                            break;
                        }

                        case SCCP_CPA_GTTI_ALL:
                        {
                            oss << "AppDumpCtxt::CalledPartyAddr GTT_TYPE: "
                                           "SCCP_CPA_GTTI_ALL" << endl;
                            break;
                        }
#endif
                    }

                oss << "AppDumpCtxt::CalledPartyAddr GTT_DIG: " << endl;
                for (int i = 0; i < cdp_gtt_len; i++)
                {
                    sprintf(tem,"0x%02x ",cdp_gtt_dig[i]);
                    oss << tem;
                }
                oss << endl;
            }

            oss << endl; 
            oss << "Dump Context SUCCESS" << endl;
        }
    }
    else if (Cmd("SendCR", "SendCR", "<slr>"))
    {
        std::string temp = "";
        string dummy;

        commandLine >> dummy >> temp;

        if (temp == "")
        {
            oss << "Error : Conref value is not given"
                   "/Invalid arguments\n"
                << "Usage: SendCR <slr>\n" << endl;
            return;
        }

        if (strpbrk(temp.c_str(),ALPHABET) ||
           (strpbrk(temp.c_str(),SPECIAL_CHAR)))
        {
            oss << "Error : Incorrect Conref value given"
                   "/Invalid Arguments\n"
                << "Usage: SendCR <slr>\n" << endl;
            return;
        }

        slr = (atoi(temp.c_str()));

        hdr.context.conref = slr;

        SendCR(hdr);
    }
    else if (Cmd("SendUDT", "SendUDT", "<slr>"))
    {
        std::string temp = "";
        string dummy;
                                                                                                                                              
        commandLine >> dummy >> temp;
                                                                                                                                              
        if (temp == "")
        {
            oss << "Error : Conref value is not given"
                   "/Invalid arguments\n"
                << "Usage: SendUDT <slr>\n" << endl;
            return;
        }
                                                                                                                                              
        if (strpbrk(temp.c_str(),ALPHABET) ||
           (strpbrk(temp.c_str(),SPECIAL_CHAR)))
        {
            oss << "Error : Incorrect Conref value given"
                   "/Invalid Arguments\n"
                << "Usage: SendUDT <slr>\n" << endl;
            return;
        }
                                                                                                                                              
        slr = (atoi(temp.c_str()));
                                                                                                                                              
        hdr.context.conref = slr;
                                                                                                                                              
        SendUDT(hdr);
    }
    else if (Cmd("SendCC", "SendCC", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendCC <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                               != ITS_SUCCESS) 
            {
                APP_TRACE_DEBUG(("DBC_SendCC::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendCC::Retrieve Context successful"
                               " for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */

                hdr.context.conref = dInfo->sccpinfo.slr;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */

                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendCC(conref, hdr, rhdr);
            }
        }
        else
        {
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendCC(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendDT1", "SendDT1", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendDT1 <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                                != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendDT1::Retrieve Context failed " 
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendDT1::Retrieve Context successful "
                               "for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */

                hdr.context.conref = dInfo->sccpinfo.slr;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */

                rhdr.context.conref = dInfo->sccpinfo.dlr;

                SendDT1(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populae slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;
            SendDT1(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendDT2", "SendDT2", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendDT2 <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                                 != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendDT2::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendDT2::Retrieve Context successful "
                               "for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendDT2(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendDT2(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendRLSD", "SendRLSD", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendRLSD <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                                 != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendRLSD::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendRLSD::Retrieve Context successful "
                               "for Conref:%d \n",conref));
                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendRLSD(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendRLSD(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendRLC", "SendRLC", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendRLC <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                                 != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendRLC::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendRLC::Retrieve Context successful "
                               "for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendRLC(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendRLC(conref, hdr, rhdr);
        }

    }
    else if (Cmd("SendCREF", "SendCREF", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendCREF <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                               != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendCREF::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendCREF::Retrieve Context successful"
                               " for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendCREF(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendCREF(conref, hdr, rhdr);
        }

    }
    else if (Cmd("SendRSC", "SendRSC", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendRSC <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                                 != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendRSC::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendRSC::Retrieve Context successful "
                               "for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendRSC(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendRSC(conref, hdr, rhdr);
        }

    }
    else if (Cmd("SendRSR", "SendRSR", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendRSR <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                                 != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendRSR::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendRSR::Retrieve Context successful "
                               "for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendRSR(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendRSR(conref, hdr, rhdr);
        }

    }
    else if (Cmd("SendIT", "SendIT", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendIT <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                                 != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendRSR::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendRSR::Retrieve Context successful "
                               "for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendIT(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendIT(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendERR", "SendERR", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendERR <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                               != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendERR::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendERR::Retrieve Context successful"
                               " for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendERR(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendERR(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendAK", "SendAK", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendAK <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                               != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendAK::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendAK::Retrieve Context successful"
                               " for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendAK(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendAK(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendED", "SendED", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendED <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                               != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendED::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendED::Retrieve Context successful"
                               " for Conref:%d \n",conref));

                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendED(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendED(conref, hdr, rhdr);
        }
    }
    else if (Cmd("SendEA", "SendEA", "<conref><slr><dlr>"))
    {
        std::string temp = "";
        std::string temp1 = "";
        std::string temp2 = "";
        string dummy;

        commandLine >> dummy >> temp >> temp1 >> temp2;

        if (temp == "" || temp1 == "" || temp2 == "")
        {
            oss << "Invalid number of arguments in command\n"
                << "Usage: SendEA <conref> <slr> <dlr>\n" << endl;

            return;
        }

        conref = (atoi(temp.c_str()));
        slr = (atoi(temp1.c_str()));
        dlr = (atoi(temp2.c_str()));

        if (conref)
        {
            if (RetrieveContext(&dInfo, (ITS_OCTET*)&conref, sizeof(ITS_USHORT))
                               != ITS_SUCCESS)
            {
                APP_TRACE_DEBUG(("DBC_SendEA::Retrieve Context failed "
                               "for Conref:%d \n",conref));
            }
            else
            {
                APP_TRACE_DEBUG(("DBC_SendEA::Retrieve Context successful"
                               " for Conref:%d \n",conref));
                /* slr to be sent should be the conref allotted by the stack:
                   hdr.context.conref will be used as slr */
                hdr.context.conref = conref;

                /* dlr to be sent should be the dlr stored in DSM :
                   rhdr.conref will be used as dlr */
                rhdr.context.conref = dInfo->sccpinfo.slr;

                SendEA(conref, hdr, rhdr);
            }
        }
        else
        {
            /* Populate slr & dlr input by user */
            hdr.context.conref = slr;
            rhdr.context.conref = dlr;

            /* The conref should be the slr */
            conref = slr;

            SendEA(conref,  hdr, rhdr);
        }

    }
}
