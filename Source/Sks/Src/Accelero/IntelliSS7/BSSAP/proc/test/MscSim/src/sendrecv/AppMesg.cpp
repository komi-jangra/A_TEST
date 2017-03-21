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
 *  ID: $Id: AppMesg.cpp,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:42  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:58  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/30 12:23:28  adutta
 * LOG: Modified for UDT (SS)
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/28 05:57:02  adutta
 * LOG: Remodeled for MSC
 * LOG:
 * LOG: Revision 1.2  2005/02/23 10:15:39  csireesh
 * LOG: IOSCDMA Codec Implementation.
 * LOG:
 * LOG: Revision 1.1  2005/02/11 10:23:13  csireesh
 * LOG: New file for Reading/Printing Messages & Parameters
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#include <its++.h>
#include <engine++.h>
#include <sccp++.h>
#include <sccp_cmn.h>
#include <its_types.h>
#include <its_route.h>

#include <App.h>
#include <AppTrace.h>
#include <AppDbc.h>
#include <AppDsm.h>
#include <AppCodec.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/*****************************************************************************
 *  Purpose:
 *      This function converts the Message type to String.
 *
 *  Input Parameters:
 *      MessageType.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      Message Tpye String.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
const char *
convertMsgTyptoStr(int msgTyp)
{

    switch(msgTyp)
    {
    case SCCP_MSG_CR:
        return "CR";

    case SCCP_MSG_CC:
        return "CC";

    case SCCP_MSG_CREF:
        return "CREF";

    case SCCP_MSG_RLSD:
        return "RLSD";

    case SCCP_MSG_RLC:
        return "RLC";

    case SCCP_MSG_DT1:
        return "DT1";

    case SCCP_MSG_DT2:
        return "DT2";

    case SCCP_MSG_AK:
        return "AK";

    case SCCP_MSG_ED:
        return "ED";

    case SCCP_MSG_EA:
        return "EA";

    case SCCP_MSG_RSR:
        return "RSR";

    case SCCP_MSG_RSC:
        return "RSC";

    case SCCP_MSG_ERR:
        return "ERR";

    case SCCP_MSG_IT:
        return "IT";

    case SCCP_MSG_UDT:
        return "UDT";

    }
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received SCCP Message Header.
 *
 *  Input Parameters:
 *      Event - pointer to an IntelliSS7 event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      offset.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
PrintMsg(Event& evt)
{
    int          offset = 0;
    ITS_CTXT     Conref = 0;
    MTP3_HEADER  mtp3;
    MTP3_ROUTING_LABEL label;
    const ITS_OCTET* event_data;
    char name[20];

    memset((void*) &mtp3, 0, sizeof(MTP3_HEADER));
    memset((void*) &label, 0, sizeof(MTP3_ROUTING_LABEL));

    event_data = evt.GetData();

    offset = 0;

    printf("App: Msg Type = %s\n", convertMsgTyptoStr(event_data[offset++]));

    Conref = ITS_GET_CTXT(&event_data[offset]);
    offset += sizeof(ITS_CTXT);

    printf("App: ConnectionRef = %d\n", Conref);

    memcpy((void*)&mtp3, &event_data[offset], sizeof(MTP3_HEADER));

    printf("App: Sio = %d\n", MTP3_HDR_GET_SIO(mtp3));

    memcpy(&label, &mtp3.label, sizeof(MTP3_ROUTING_LABEL));

    printf("App: Opc  = %d\n", MTP3_RL_GET_OPC_VALUE(label));
    printf("App: Dpc  = %d\n", MTP3_RL_GET_DPC_VALUE(label));
    printf("App: Sls  = 0x%01x\n", MTP3_RL_GET_SLS(label));

    printf("\n");
    return offset;
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received CR Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass. 
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
PrintCR(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of CR Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_SRC_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_PROTOCOL_CLASS);
    PrintMsgParam(sccp_msg, CGP_PC);
    PrintMsgParam(sccp_msg, CGP_SSN);
    PrintMsgParam(sccp_msg, CGP_NI);
    PrintMsgParam(sccp_msg, CGP_ROUT_TYPE);

    PrintMsgParam(sccp_msg, CGP_GTT_TYPE);
    PrintMsgParam(sccp_msg, CGP_GTT_DIG);

    PrintMsgParam(sccp_msg, CDP_PC);
    PrintMsgParam(sccp_msg, CDP_SSN);
    PrintMsgParam(sccp_msg, CDP_NI);
    PrintMsgParam(sccp_msg, CDP_ROUT_TYPE);

    //PrintMsgParam(sccp_msg, CDP_GTT_TYPE);
    //PrintMsgParam(sccp_msg, CDP_GTT_DIG);

    PrintMsgParam(sccp_msg, SCCP_PRM_CREDIT);
    PrintMsgParam(sccp_msg, SCCP_PRM_HOP_COUNTER);

    printf("\n");

}

void
PrintUDT(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of UDT Message\n");
    PrintMsgParam(sccp_msg, SCCP_PRM_DATA);
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received CC Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintCC(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of CC Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_SRC_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_PROTOCOL_CLASS);
    PrintMsgParam(sccp_msg, SCCP_PRM_CREDIT);
    PrintMsgParam(sccp_msg, CDP_PC);
    PrintMsgParam(sccp_msg, CDP_SSN);
    PrintMsgParam(sccp_msg, CDP_NI);
    PrintMsgParam(sccp_msg, CDP_ROUT_TYPE);
    PrintMsgParam(sccp_msg, CDP_GTT_TYPE);
    PrintMsgParam(sccp_msg, CDP_GTT_DIG);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received CREF Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintCREF(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of CREF Message\n");
    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, CDP_PC);
    PrintMsgParam(sccp_msg, CGP_SSN);
    PrintMsgParam(sccp_msg, CDP_NI);
    PrintMsgParam(sccp_msg, CDP_ROUT_TYPE);
    PrintMsgParam(sccp_msg, SCCP_PRM_REFUSAL_CAUSE);
    PrintMsgParam(sccp_msg, CDP_GTT_TYPE);
    PrintMsgParam(sccp_msg, CDP_GTT_DIG);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received RLSD Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintRLSD(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of RLSD Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_SRC_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_RELEASE_CAUSE);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received RLC Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintRLC(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of RLC Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_SRC_LOCAL_REF);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received DT1 Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintDT1(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of DT1 Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_DATA);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received DT2 Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintDT2(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of DT2 Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_DATA);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received AK Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintAK(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of AK Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_CREDIT);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received RSR Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintRSR(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of RSR Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_SRC_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_RESET_CAUSE);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received RSC Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintRSC(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of RSC Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_ERROR_CAUSE);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received ERR Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintERR(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of ERR Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_ERROR_CAUSE);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received IT Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintIT(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of IT Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_SRC_LOCAL_REF);
    PrintMsgParam(sccp_msg, SCCP_PRM_PROTOCOL_CLASS);
    PrintMsgParam(sccp_msg, SCCP_PRM_CREDIT);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received ED Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintED(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of ED Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received EA Message.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
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
PrintEA(SCCP_MessageClass *sccp_msg)
{
    printf("Dump of EA Message\n");

    PrintMsgParam(sccp_msg, SCCP_PRM_DEST_LOCAL_REF);

    printf("\n");
}

/*****************************************************************************
 *  Purpose:
 *      This function display the received Parameter.
 *
 *  Input Parameters:
 *      SCCP_MessageClass.
 *      Parameter Id.
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
PrintMsgParam(SCCP_MessageClass *sccpmsg, int param_id)
{
    ITS_UINT slr_get = 0;
    ITS_UINT dlr_get = 0;
    ITS_UINT prot_class = 0;
    ITS_UINT cre = 0;
    ITS_OCTET   hcount = 0;
    ITS_OCTET   refusal_cause = 0;
    ITS_OCTET   seg_reassmb = 0;
    ITS_OCTET   err_cause = 0;
    ITS_OCTET   reset_cause = 0;
    ITS_OCTET   release_cause = 0;

    ITS_OCTET cgp_pc = 0;
    ITS_OCTET cgp_ssn = 0;
    ITS_OCTET cgp_gtt_dig[SCCP_MAX_ADDR_LEN];
    ITS_USHORT cgp_gtt_len = 0;
    ITS_OCTET cgp_gtt_type = 0;
    ITS_OCTET cgp_ni = 0;
    ITS_BOOLEAN cgp_route_type = ITS_FALSE;

    ITS_OCTET cdp_pc = 0;
    ITS_OCTET cdp_ssn = 0;
    ITS_OCTET cdp_gtt_dig[SCCP_MAX_ADDR_LEN];
    ITS_USHORT cdp_gtt_len = 0;
    ITS_OCTET cdp_gtt_type = 0;
    ITS_OCTET cdp_ni = 0;
    ITS_BOOLEAN cdp_route_type = ITS_FALSE;

    switch(param_id)
    {
        case SCCP_PRM_SRC_LOCAL_REF:
            {
                 SCCP_SourceLocalRef *slr =
                 (SCCP_SourceLocalRef *)sccpmsg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            
                 if (slr != NULL)
                 {
                     slr_get = slr->GetRefNum();
                     printf(" Parameter:: SLR value:: \t%d\n", slr_get);
                 }
                 break;
            }

        case SCCP_PRM_DEST_LOCAL_REF:
            {
                SCCP_DestinationLocalRef *dlr =
                (SCCP_DestinationLocalRef *)sccpmsg->FindIE(SCCP_PRM_DEST_LOCAL_REF);

                if (dlr != NULL)
                {
                    dlr_get = dlr->GetRefNum();
                    printf(" Parameter:: DLR value:: \t%d\n", dlr_get);
                }
                break;
            }

        case SCCP_PRM_PROTOCOL_CLASS:
            {
                SCCP_ProtocolClass *proto_class =
                (SCCP_ProtocolClass *)sccpmsg->FindIE(SCCP_PRM_PROTOCOL_CLASS);

                if (proto_class != NULL)
                {
                    prot_class = proto_class->GetProtocolClass();
                    printf(" Parameter:: ProtoClass value::\t%d\n", prot_class);
                }
                break;
            }

        case SCCP_PRM_CREDIT:
            {
                SCCP_Credit *credit =
                (SCCP_Credit *)sccpmsg->FindIE(SCCP_PRM_CREDIT);

                if (credit != NULL)
                {
                    cre = credit->GetCredit();
                    printf(" Parameter:: CREDIT value:: \t%d\n", cre);
                }
                break;
            }

        case CGP_PC:
            {
                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);

                if ((calling_pa != NULL) && (calling_pa->HasPointCode()))
                {
                    cgp_pc = calling_pa->GetPointCode();
                    printf(" Parameter:: CGP_PC value:: \t%d\n", cgp_pc);
                }
                break;
            }

        case CGP_SSN:
            {
                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);

                if ((calling_pa != NULL) && (calling_pa->HasSSN()))
                {
                    cgp_ssn = calling_pa->GetSSN();
                    printf(" Parameter:: CGP_SSN value:: \t%d\n", cgp_ssn);
                }
                break;
            }

        case CGP_ROUT_TYPE:
            {
                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);

                if (calling_pa != NULL)
                {
                    cgp_route_type = calling_pa->IsRoutedByPCSSN();

                    if (cgp_route_type)
                    {
                        printf(" Parameter:: CGP_ROUT_TYPE value:: RouteBySSN \n");
                    } 
                    else 
                    {
                        printf(" Parameter:: CGP_ROUT_TYPE value:: RouteByGT \n");
                    } 
                }
                break;
            }

        case CGP_NI:
            {
                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);

                if (calling_pa != NULL)
                {
                    cgp_ni = calling_pa->IsInternationalRouting();
                    
                    if (cgp_ni)
                    {
                        printf(" Parameter:: CGP_NI value:: International \n");
                    } 
                    else 
                    {
                        printf(" Parameter:: CGP_NI value:: National \n");
                    } 
                }
                break;
            }

        case CGP_GTT_TYPE:
            {
                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
   
                if ((calling_pa != NULL) && (calling_pa->HasGlobalTitle()))
                {
                    printf(" Parameter:: CGP_GTT_TYPE value::");

                    calling_pa->GetGlobalTitle(cgp_gtt_type, cgp_gtt_dig, cgp_gtt_len);

                    switch (cgp_gtt_type)
                    { 
#if defined(ANSI)
                        case SCCP_CPA_GTTI_TNE_ANSI:
                        {
                            printf(" SCCP_CPA_GTTI_TNE_ANSI \n");
                            break;
                        }
                        case SCCP_CPA_GTTI_TRANS_ANSI:
                        {
                            printf(" SCCP_CPA_GTTI_TRANS_ANSI \n");
                            break;
                        }
#endif

#if defined(CCITT)
                        case SCCP_CPA_GTTI_NATURE:
                        {
                            printf("SCCP_CPA_GTTI_TNE_ANSI \n");
                            break;
                        }

                        case SCCP_CPA_GTTI_TRANS_CCITT:
                        {
                            printf(" SCCP_CPA_GTTI_TRANS_CCITT \n");
                            break;
                        }

                        case SCCP_CPA_GTTI_TNE_CCITT:
                        {
                            printf(" SCCP_CPA_GTTI_TNE_CCITT \n");
                            break;
                        }

                        case SCCP_CPA_GTTI_ALL:
                        {
                            printf(" SCCP_CPA_GTTI_ALL \n");
                            break;
                        }
#endif
                    }  
                }
                break;
            }

        case CGP_GTT_DIG:
            {
                SCCP_CallingPartyAddr *calling_pa =
                (SCCP_CallingPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
   
                if (calling_pa != NULL)
                {
                    calling_pa->GetGlobalTitle(cgp_gtt_type, cgp_gtt_dig, cgp_gtt_len);
                    printf(" Parameter:: CGP_GTT_DIG: ");
                    for (int i = 0; i < cgp_gtt_len; i++)
                    printf("%02x ", cgp_gtt_dig[i]);
                    printf("\n");
                }
                break;
            }

        case CDP_PC:
            {
                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);

                if ((called_pa != NULL) && (called_pa->HasPointCode()))
                {
                    cdp_pc = called_pa->GetPointCode();
                    printf(" Parameter:: CDP_PC value:: \t%d\n", cdp_pc);
                }
                break;
            }

        case CDP_SSN:
            {
                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);

                if ((called_pa != NULL) && (called_pa->HasSSN()))
                {
                    cdp_ssn = called_pa->GetSSN();
                    printf(" Parameter:: CDP_SSN value:: \t%d\n", cdp_ssn);
                }
                break;
            }

        case CDP_ROUT_TYPE:
            {
                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);

                if (called_pa != NULL)
                {
                    cdp_route_type = called_pa->IsRoutedByPCSSN();

                    if (cdp_route_type)
                    {
                        printf(" Parameter:: CDP_ROUT_TYPE value:: RouteBySSN \n");
                    }
                    else
                    {
                        printf(" Parameter:: CDP_ROUT_TYPE value:: RouteByGT \n");
                    }

                }
                break;
            }

        case CDP_NI:
            {
                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);

                if (called_pa != NULL)
                {
                    cdp_ni = called_pa->IsInternationalRouting();

                    if (cgp_ni)
                    {
                        printf(" Parameter:: CDP_NI value:: International \n");
                    }
                    else
                    {
                        printf(" Parameter:: CDP_NI value:: National \n");
                    }
                }
                break;
            }

        case CDP_GTT_TYPE:
            {
                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);

                if ((called_pa != NULL) && (called_pa->HasGlobalTitle()))
                {
                    called_pa->GetGlobalTitle(cdp_gtt_type, cdp_gtt_dig, cdp_gtt_len);

                    printf(" Parameter:: CDP_GTT_TYPE value::");

                    switch (cdp_gtt_type)
                    {
#if defined(ANSI)
                        case SCCP_CPA_GTTI_TNE_ANSI:
                        {
                            printf(" SCCP_CPA_GTTI_TNE_ANSI \n");
                            break;
                        }
                        case SCCP_CPA_GTTI_TRANS_ANSI:
                        {
                            printf(" SCCP_CPA_GTTI_TRANS_ANSI \n");
                            break;
                        }
#endif

#if defined(CCITT)
                        case SCCP_CPA_GTTI_NATURE:
                        {
                            printf("SCCP_CPA_GTTI_TNE_ANSI \n");
                            break;
                        }

                        case SCCP_CPA_GTTI_TRANS_CCITT:
                        {
                            printf(" SCCP_CPA_GTTI_TRANS_CCITT \n");
                            break;
                        }

                        case SCCP_CPA_GTTI_TNE_CCITT:
                        {
                            printf(" SCCP_CPA_GTTI_TNE_CCITT \n");
                            break;
                        }
                        case SCCP_CPA_GTTI_ALL:
                        {
                            printf(" SCCP_CPA_GTTI_ALL \n");
                            break;
                        }
#endif
                    }
                }
                break;
            }

        case CDP_GTT_DIG:
            {
                SCCP_CalledPartyAddr *called_pa =
                (SCCP_CalledPartyAddr *)sccpmsg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);

                if (called_pa != NULL)
                {
                    called_pa->GetGlobalTitle(cdp_gtt_type, cdp_gtt_dig, cdp_gtt_len);
                    printf(" Parameter:: CDP_GTT_DIG: ");
                    for (int i = 0; i < cdp_gtt_len; i++)
                    printf("%02x ", cdp_gtt_dig[i]);
                    printf("\n");
                }
                break;
            }

        case SCCP_PRM_HOP_COUNTER:
            {
                SCCP_HopCount *hc =
                (SCCP_HopCount *)sccpmsg->FindIE(SCCP_PRM_HOP_COUNTER);

                if (hc != NULL)
                {
                    hcount = hc->GetHopCount();
                    printf(" Parameter:: HOP_COUNTER value:: \t%d\n", hcount);
                }
                break;
            }

        case SCCP_PRM_DATA:
            {
                ITS_OCTET  data[1024];
                int len;

                SCCP_UserData *ud = (SCCP_UserData *)sccpmsg->FindIE(SCCP_PRM_DATA);

                if (ud != NULL)
                {
                    ud->GetUserData(data, len);
                    InterpretMsg(data, len);
                }
                break;
            }

        case SCCP_PRM_REFUSAL_CAUSE:
            {
                SCCP_RefusalCause *rc =
                (SCCP_RefusalCause *)sccpmsg->FindIE(SCCP_PRM_REFUSAL_CAUSE);
   
                if (rc != NULL)
                {
                    refusal_cause = rc->GetCause();
                    printf(" Parameter:: REFUSAL_CAUSE value:: "
                                  "\t%d\n", refusal_cause);
                }
                break;
            }

        case SCCP_PRM_SEGMENT_REASSEM:
            {
                SCCP_SegmentReassem *sr =
                (SCCP_SegmentReassem *)sccpmsg->FindIE(SCCP_PRM_SEGMENT_REASSEM);

                 if (sr != NULL)
                 {
                     seg_reassmb = sr->GetSegmentReassem();
                     printf(" Parameter:: SEGMENT_REASSEM value:: "
                                  "\t%d\n", seg_reassmb);
                 }
                break;
            }

        case SCCP_PRM_RELEASE_CAUSE:
            {
                SCCP_ReleaseCause *rlsd_cause =
                (SCCP_ReleaseCause *)sccpmsg->FindIE(SCCP_PRM_RELEASE_CAUSE);

                 if (rlsd_cause != NULL)
                 {
                     release_cause = rlsd_cause->GetCause();
                     printf(" Parameter:: RELEASE_CAUSE value:: "
                                  "\t%d\n", release_cause);
                 }
                break;
            }

        case SCCP_PRM_RESET_CAUSE:
            {
                SCCP_ResetCause *rs =
                (SCCP_ResetCause *)sccpmsg->FindIE(SCCP_PRM_RESET_CAUSE);

                 if (rs != NULL)
                 {
                     reset_cause = rs->GetCause();
                     printf(" Parameter:: RESET_CAUSE value:: "
                                  "\t%d\n", reset_cause);
                 }
                break;
            }

        case SCCP_PRM_ERROR_CAUSE:
            {
                SCCP_ErrorCause *ec =
                (SCCP_ErrorCause *)sccpmsg->FindIE(SCCP_PRM_ERROR_CAUSE);

                 if (ec != NULL)
                 {
                     err_cause = ec->GetCause();
                     printf(" Parameter:: ERROR_CAUSE value::"
                                  " \t%d\n", err_cause);
                 }
                break;
           }

        case SCCP_PRM_SEQUENCE_SEGMENT:
            {
                SCCP_SequenceSegment *ss =
                (SCCP_SequenceSegment *)sccpmsg->FindIE(SCCP_PRM_SEQUENCE_SEGMENT);

                 if (ss != NULL)
                 {
                    printf(" Parameter:: SEQUENCE_SEGMENT ::\n");
                 }
                break;
            }

        case SCCP_PRM_RCV_SEQ_NUM:
            {
                SCCP_ReceiveSequenceNum *rsn =
                (SCCP_ReceiveSequenceNum *)sccpmsg->FindIE(SCCP_PRM_RCV_SEQ_NUM);

                if (rsn != NULL)
                {
                    printf(" Parameter:: RCV_SEQ_NUM   :: \n");
                }
                break;
            }
        default:
            //APP_TRACE_ERROR(("ProcessSCCPMsg::Received UNKNOWN Message"));
            break;

    }
}
