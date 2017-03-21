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
 *  ID: $Id: App.h,v 1.1.1.1 2007-10-08 11:11:15 bsccs2 Exp $
 * 
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:57  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/30 12:24:07  adutta
 * LOG: Modified from UDT (SS)
 * LOG:
 * LOG: Revision 1.1.2.2  2005/09/28 10:54:34  adutta
 * LOG: Remodeled for MSC Sim
 * LOG:
 * LOG: Revision 1.2  2005/02/11 10:25:37  csireesh
 * LOG: Committing after sanitizing Sample App (send-recv) for SCCP-CO: yet to take care of Codec
 * LOG:
 * LOG: Revision 1.1  2004/02/12 13:46:55  aganguly
 * LOG: Initial version of CDMA test application on SCCP-CO.
 * LOG:
 ****************************************************************************/

#ifndef _TEST_APP_H
#define _TEST_APP_H

#include <its++.h>
#include <sccp++.h>
#include <engine++.h>
#include <its_trace.h>
#include <its_types.h>
#include <its_route.h>
#include <its_sctp.h>
#include <its_service.h>
#include <its_iniparse.h>
#include <its_sctp_trans.h>
#include <its_gen_disp.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

/* used to get IE parameter len in Hex */
#define BASE_16            16

/* #defines for reading parameters from file */
#define CDP_PC             (0x20U)
#define CGP_PC             (0x21U)
#define CDP_SSN            (0x22U)
#define CGP_SSN            (0x23U)
#define CDP_NI             (0x24U)
#define CDP_ROUT_TYPE      (0x25U)
#define CDP_GTT_TYPE       (0x26U)
#define CDP_GTT_DIG        (0x27U)
#define RL_OPC             (0x28U)
#define RL_DPC             (0x29U)
#define RL_SLS             (0x2AU)
#define CGP_NI             (0x2BU)
#define CGP_ROUT_TYPE      (0x2CU)
#define CGP_GTT_TYPE       (0x2DU)
#define CGP_GTT_DIG        (0x2EU)

int ParseArguments(int, const char**);

/* Prototypes for AppSendReceive related functions */
void InitiateSCCPMessage(its::ThreadPoolThread *thr, void * arg);
int ProcessSCCPMsg(its::ThreadPoolThread *thr, its::Event& evt);

int GetOctetsFromStr(ITS_OCTET *array, int nOctets);
int PrintMsg(its::Event& evt);

/* Methods for printing Messages */
void PrintCR(SCCP_MessageClass *sccpmsg);
void PrintUDT(SCCP_MessageClass *sccpmsg);
void PrintCC(SCCP_MessageClass *sccpmsg);
void PrintDT1(SCCP_MessageClass *sccpmsg);
void PrintDT2(SCCP_MessageClass *sccpmsg);
void PrintRLSD(SCCP_MessageClass *sccpmsg);
void PrintRLC(SCCP_MessageClass *sccpmsg);
void PrintCREF(SCCP_MessageClass *sccpmsg);
void PrintRSR(SCCP_MessageClass *sccpmsg);
void PrintRSC(SCCP_MessageClass *sccpmsg);
void PrintERR(SCCP_MessageClass *sccpmsg);
void PrintIT(SCCP_MessageClass *sccpmsg);
void PrintED(SCCP_MessageClass *sccpmsg);
void PrintEA(SCCP_MessageClass *sccpmsg);
void PrintAK(SCCP_MessageClass *sccpmsg);

/* Method for printing Message parameter */
void
PrintMsgParam(SCCP_MessageClass *sccp_msg, int param_id);

/* Methods for sending Messages */
void SendCR(ITS_HDR hdr);
void SendUDT(ITS_HDR hdr);
void SendCC(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendDT1(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendDT2(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendRLSD(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendRLC(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendCREF(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendRSR(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendRSC(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendERR(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendIT(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendED(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendEA(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);
void SendAK(ITS_CTXT conref, ITS_HDR hdr, ITS_HDR rhdr);

#endif
