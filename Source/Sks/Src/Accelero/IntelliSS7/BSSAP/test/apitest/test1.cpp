/***************************************************************************
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
 *  ID: $Id: test1.cpp,v 1.1.1.1 2007-10-08 11:11:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:43  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:59  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.2.1  2006/03/29 15:27:55  yranade
 * LOG: Fix for Issue ID 3327 (sgavalkar)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:09  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:14  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1  2003/08/21 18:03:53  hcho
 * LOG: Added IE position changes testing.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.1  2002/06/10 17:04:40  ngoel
 * LOG: test program
 * LOG:
 * LOG: Revision 1.1.2.21  2002/05/30 14:33:35  ngoel
 * LOG: dd status messages
 * LOG:
 * LOG: Revision 1.1.2.20  2002/05/29 21:05:57  ngoel
 * LOG: add stop dtmf messages
 * LOG:
 * LOG: Revision 1.1.2.19  2002/05/29 20:46:14  ngoel
 * LOG: add dtmf messges
 * LOG:
 * LOG: Revision 1.1.2.18  2002/05/29 20:10:04  ngoel
 * LOG: add start dtmf
 * LOG:
 * LOG: Revision 1.1.2.17  2002/05/29 19:07:43  ngoel
 * LOG: add notify message
 * LOG:
 * LOG: Revision 1.1.2.16  2002/05/29 18:29:16  ngoel
 * LOG: add congestion control
 * LOG:
 * LOG: Revision 1.1.2.15  2002/05/29 17:18:44  ngoel
 * LOG: add disconnect release messages
 * LOG:
 * LOG: Revision 1.1.2.14  2002/05/29 16:30:57  ngoel
 * LOG: add retrieve messages
 * LOG:
 * LOG: Revision 1.1.2.13  2002/05/29 16:17:09  ngoel
 * LOG: add hold reject
 * LOG:
 * LOG: Revision 1.1.2.12  2002/05/29 15:51:14  ngoel
 * LOG: add hold and hold ack
 * LOG:
 * LOG: Revision 1.1.2.11  2002/05/29 15:21:39  ngoel
 * LOG: add user info message
 * LOG:
 * LOG: Revision 1.1.2.10  2002/05/16 14:31:30  ngoel
 * LOG: add layer 3 header
 * LOG:
 * LOG: Revision 1.1.2.9  2002/05/13 13:22:41  ngoel
 * LOG: add modify reject
 * LOG:
 * LOG: Revision 1.1.2.8  2002/05/10 20:40:13  ngoel
 * LOG: add modify
 * LOG:
 * LOG: Revision 1.1.2.7  2002/05/10 16:12:38  ngoel
 * LOG: add progress message
 * LOG:
 * LOG: Revision 1.1.2.6  2002/05/10 13:22:20  ngoel
 * LOG: add connect message
 * LOG:
 * LOG: Revision 1.1.2.5  2002/05/09 18:49:23  ngoel
 * LOG: add messages
 * LOG:
 * LOG: Revision 1.1.2.4  2002/05/09 17:22:26  ngoel
 * LOG: call proceeding
 * LOG:
 * LOG: Revision 1.1.2.3  2002/05/09 16:51:43  ngoel
 * LOG: add call confirm
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/09 15:54:23  ngoel
 * LOG: add code
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/09 14:49:55  ngoel
 * LOG: add code
 * LOG:
 * LOG: Revision 6.1.4.1  2002/04/24 22:19:58  hxing
 * LOG: Back port to PR5.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.3  2001/11/26 15:18:16  dzhang
 * LOG: Move Output for Old BSS to New BSS IE to DumpIEBSS()
 * LOG:
 * LOG: Revision 1.2  2001/11/19 17:11:29  dzhang
 * LOG: Monor modification
 * LOG:
 * LOG: Revision 1.1  2001/11/12 14:47:42  dzhang
 * LOG: update to latest spec version 8.9.0
 * LOG:
 *
 ****************************************************************************/

#include <iomanip>
#include <UnitTest.h>
#include <its_license.h>

#include <BSSAPPrint.h>
//#include <its_ss7_stubs.h>
#include <its_app.h>

#include <its_statics.cpp>

using namespace std;

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

class BSSAP_UnitTest : public UnitTest
{
public:
    BSSAP_UnitTest() : UnitTest("BSSAP_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};


//Print UserData
void
DumpData(ITS_OCTET* data, int len)
{
    cout << endl;
    cout << "The length of UserData is : " << len <<endl;

    for (int i = 0; i < len; i++)
    {
        if (i && !(i%20))
        {
            cout << endl;
        }
        printf("%02x ", data[i]);        
    }
    cout << endl<<endl;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
void
BSSAP_UnitTest::DoCommand(istream& cmdLine)
{
    //variables
    ITS_OCTET               octet = 0x12U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = { 1, 0, 0, 1, 1, 0, 0, 1, 1 };
    ITS_OCTET               prio[1] = { 1 };
    ITS_OCTET               key[] = { 1, 2, 3, 4, 5 };
    ITS_OCTET               key1[20] = { 2, 7, 3, 4, 5, 6, 7, 8, 9 };
    ITS_OCTET               key2[] = { 3, 5, 3, 4, 5, 6, 7 };
    ITS_OCTET               key3[] = { 0x1U, 0x2U, 0x3U, 0x4U, 0x5U, 0x6U, 0x7U, 0x8U, 0x9U, 0x10U, 0x11U, 0x12U };
    ITS_OCTET               mindig[] = { 0x69, 0x64, 0x63, 0x60 };
    ITS_USHORT              ushort  = 0x678U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    //char*                   dgts1  = "186213217260686";
    char*                   dgts1  = "123456789123456";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    

 
    ////////////////////////////////////////////////////////////////////
    //            3.1.2  Message Formats               
    ////////////////////////////////////////////////////////////////////

    /* ---------- 3.2.1.1 Assignment Request ---------- */
    if (Cmd("ENCASSREQ", "Encode AssignmentRequest"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
	BSSAP_InterBandToBeUsed         itBand;
        //BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        //BSSAP_ServHandover              servHand;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_AssignmentRequest assReq;

        // populate Channel Type, add it to the message   
        chanType.SetSpeechDataID(CT_DATA);                           //0x02
        chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);  //0x08
        
                // populate Channel Type, add it to the message      
        chanType.SetSpeechDataID(CT_DATA);                             //0x02
        chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);    //0x08
/*        
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 0);      //0x01
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 1);      //0x11
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 2);      //0x21
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 3);      //0x01
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 4);      //0x11
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 5);      //0x21
*/
        chanType.SetDataTransp(1, CT_DATA_MAX_ALLOWED_CHANNEL1, 1);    //0x20
        chanType.SetIFDateRate(1, 0x53);                               //0x53
        chanType.SetAsymInd(0, 0x02);                                  //0x02

        assReq.AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);


        // populate Layer 3 Header Information, add it to the message
        l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        l3hInfo.SetTIVal(TI_VALUE_3);                      //0x03
        l3hInfo.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        assReq.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);


        // populate Priority, add it to the message
        prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
        prio.SetQA(P_QUEUING_ALLOWED);                      //0x01
        prio.SetPCI(P_PREEMPTION_ALLOWED);                  //0x01 
        prio.SetPVI(P_CONN_BE_REQ);                         //0x01
        

        assReq.AddIE(BSSAP_IEI_PRIORITY, &prio);               


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x11

        assReq.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        
        // populate Downlink DTX Flag, add it to the message
        dlFlag.SetDTXFlag(DLDTX_ACTIVATE_ALLOWED);          //0x00
        
        assReq.AddIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, &dlFlag);

	// Populate Interference Band To Be Used
	itBand.SetBandToBeUsed(0x1F);
	assReq.AddIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED, &itBand);

        // populate Classmark Info Type2, add it to the message
        cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
        cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
        cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
        cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
        cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
        cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
        cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
        cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
        cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
        cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
        cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
        cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
        cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
        cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
        cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
        cmInfo2.SetCM3(CIT2_CM3_OPTIONS_SUPPORTED);         //0x01

        assReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);


        // populate Group Call Reference, add it to the message
        gcRef.SetCallRef(uint);                             //0x4321000
        gcRef.SetClPrio(GCR_CALL_PRIORITY_LEVEL_B);         //0x06
        gcRef.SetAF(GCR_AF_ACK_REQUIRED);                   //0x01
        gcRef.SetSF(GCR_SF_VBS);                            //0x00
        gcRef.SetCiphInfo(GCR_CIPHERING_KEY_9);             //0x09;

        assReq.AddIE(BSSAP_IEI_GROUP_CALL_REFERENCE, &gcRef);


        // populate Talker Flag, add it to the message
        assReq.AddIE(BSSAP_IEI_TALKER_FLAG, &tkFlag);
#if 0
        // populate LSA Access Control Suppression, add it to the message
        lacs.SetEmergency(0x01); 

        assReq.AddIE(BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR, &lacs);
#endif
        
        // populate Configuration Evolution Indication, add it to the message
        ceInd.SetSMI(CE_MODIFICATION_ALLOWED_TCH_F_2);        //0x02
        assReq.AddIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, &ceInd);

#if 0
        // populate Service Handover, add it to the message
        servHand.SetServHandoverInfo(SH_HANDPVER_TO_NEITHER_SHOULD_NOT_PERFORM);//0x01

        assReq.AddIE(BSSAP_IEI_SERVICE_HANDOVER, &servHand);
#endif
 
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &assReq) != ITS_SUCCESS)
        {
            cout << "Error encoding Assignment Request." << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);
/*
	// Message injected for testing
        ITS_OCTET inject[] = {0x00, 0x1a, 0x01, 0x0b, 0x04, 0x01, 0x08, 0x01,
		              0x80, 0x00, 0x02, 0x06, 0x00, 0x06, 0x01, 0x3c,
			      0x01, 0x00, 0x01, 0x19, 0x00, 0x14, 0x1f, 0x12,
			      0x03, 0x00, 0x00, 0x00};
        len = sizeof(inject);
        DumpData(inject, len);
*/
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Assignment Request." << endl;
            return;
        }     

        PrintBSSMAPMsgAssignReq(dec);
    }

    if (Cmd("ALERTING", "Encode Alerting"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Alerting alert;

        // populate Layer 3 Header Information, add it to the message
        alert.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        alert.SetTIVal(TI_VALUE_3);                      //0x03

        //l3hInfo.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        alert.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

        facility.SetFacilityData(buff, 0);
        alert.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        alert.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        BSSAP_UserToUser    userTouser;
        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        alert.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &alert) != ITS_SUCCESS)
        {
            cout << "Error encoding Alerting " << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

/*        ITS_OCTET inject[] = { 0x01, 0x00, 0x95, 0x33, 0x01, 0x1c, 0x00, 0x1e,
                               0x02, 0xa1, 0x81, 0x7e, 0x8b, 0x00, 0x00, 0x00, 
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
                                                                                                                            
        DumpData(inject, sizeof(inject));
*/
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Alerting" << endl;
            return;
        }     

        PrintBSSMAPMsgAlerting(dec);
    }

    if (Cmd("CALLCONFIRM", "Call Confirmed"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CallConfirmed ccon;

        // populate Layer 3 Header Information, add it to the message
        ccon.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        ccon.SetTIVal(TI_VALUE_3);                      //0x03
        ccon.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        ccon.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        cause.SetCodingLocationCause(1, 1, 1);
        ccon.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        cc.SetDTMF();
        cc.SetPCP();
        ccon.AddIE(BSSAP_IEI_CC_CAPABILITIES, &cc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &ccon) != ITS_SUCCESS)
        {
            cout << "Error encoding Call Confirmed " << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Call confirmed" << endl;
            return;
        }     

        PrintBSSMAPMsgCallConfirm(dec);
    }

    if (Cmd("CALLPROCEEDING", "Call Proceeding"))
    {
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_PriorityLevel             pl;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CallProceeding cp;

        // populate Layer 3 Header Information, add it to the message
        cp.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        cp.SetTIVal(TI_VALUE_3);                      //0x03
        cp.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        cp.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        facility.SetFacilityData(buff, 5);
        cp.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        cp.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        pl.SetPriority(PRIORITY_LEVEL_2);
        cp.AddIE(BSSAP_IEI_CC_PRIORITY_LEVEL, &pl);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cp) != ITS_SUCCESS)
        {
            cout << "Error encoding Call Proceeding" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);
/*
        ITS_OCTET inject[] = { 0x01, 0x00, 0x11, 0xb3, 0x02, 0x04, 0x01, 0x79,
                               0x1c, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e,
                               0x02, 0xa1, 0x81, 0x83 };

        DumpData(inject, sizeof(inject));
*/
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Call Proceeding" << endl;
            return;
        }     

        PrintBSSMAPMsgCallProceeding(dec);
    }


    if (Cmd("CONNECT", "Encode Connect"))
    {
        BSSAP_Facility             facility;
        BSSAP_ProgressIndicator    progress;
        BSSAP_ConnectedNumber      cn;
        BSSAP_ConnectedSubAddress  cs;
        BSSAP_UserToUser           userTouser;
        BSSAP_SSVersion            ss;
        BSSAP_StreamIdentifier     strmIdent;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Connect co;

        //co.SetProtDiscr(0x05);       
        co.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        co.SetTIVal(TI_VALUE_3);                      //0x03
        co.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        facility.SetFacilityData(buff, 5);
        co.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        co.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        cn.SetTypeAndNumPlan( 1, 1);
        cn.SetDigits(buff, 5);
        co.AddIE(BSSAP_IEI_CC_CONNECTED_NUMBER, &cn);

        cs.SetSubAddressType( 1, ITS_TRUE);
        cs.SetSubAddressInfo(buff, 5);
        co.AddIE(BSSAP_IEI_CC_CONNECTED_SUB_ADDRESS, &cs);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        co.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        ss.SetSSVersion(buff, 1);
        co.AddIE(BSSAP_IEI_CC_SS_VERSION_IND, &ss);

        strmIdent.SetStrmIdentVal(0x99);
        co.AddIE(BSSAP_IEI_CC_STREAM_IDENTIFIER, &strmIdent);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &co) != ITS_SUCCESS)
        {
            cout << "Error encoding CONNECT " << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);
/*
        ITS_OCTET inject[] = { 0x01, 0x00, 0x1f, 0xb3, 0x07, 0x1c, 0x05, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x1e, 0x02, 0xa1, 0x81,
                               0x4c, 0x10, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00 };

        DumpData(inject, sizeof(inject));
*/
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CONNECT" << endl;
            return;
        }     

        PrintBSSMAPMsgConnect(dec);
    }

    if (Cmd("CONNECTACK", "Encode ConnectAck"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ConnectAck cok;

        cok.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        cok.SetTIVal(TI_VALUE_3);                      //0x03
        cok.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cok) != ITS_SUCCESS)
        {
            cout << "Error encoding connect " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Assignment Request." << endl;
            return;
        }     

        PrintBSSMAPMsgConnectAck(dec);
    }


    if (Cmd("EMRGSETUP", "Encode Emergency Setup"))
    {
        BSSAP_BearerData           bd;
        BSSAP_StreamIdentifier     strmIdent;
        BSSAP_SupportedCodecs      suppCodecs;
        BSSAP_EmergencyCategory    emergCat;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_EmergencySetup es;
       
        es.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        es.SetTIVal(TI_VALUE_3);                      //0x03
        es.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        es.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        strmIdent.SetStrmIdentVal(0x99);
        es.AddIE(BSSAP_IEI_CC_STREAM_IDENTIFIER, &strmIdent);

        ITS_OCTET value[] = { SYS_ID_GSM, 0x02, 0x01, 0x00 };
        suppCodecs.SetSystemID(value, sizeof(value));
        es.AddIE(BSSAP_IEI_CC_SUPPORTED_CODECS, &suppCodecs);

        emergCat.SetEmergencyVal(0x13);
        es.AddIE(BSSAP_IEI_CC_EMERGENCY_CATEGORY, &emergCat);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &es) != ITS_SUCCESS)
        {
            cout << "Error encoding Emergency Setup " << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Emergency Setup ." << endl;
            return;
        }     

        PrintBSSMAPMsgEmergencySetup(dec);
    }


    if (Cmd("PROGRESS", "Progress"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_UserToUser                userTouser;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Progress pr;

        pr.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        pr.SetTIVal(TI_VALUE_3);                      //0x03
        pr.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
       
        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        pr.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        pr.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &pr) != ITS_SUCCESS)
        {
            cout << "Error encoding Progress " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Progress Request." << endl;
            return;
        }     

        PrintBSSMAPMsgProgress(dec);
    }


    if (Cmd("CCESTABLISH", "CC Establishment"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_UserToUser                userTouser;
        BSSAP_SetupContainer            sc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CCEstablishment cce;

        cce.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        cce.SetTIVal(TI_VALUE_3);                      //0x03
        cce.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
       
        ITS_OCTET value = 1;
        sc.SetSetupData(buff, 5);
        cce.AddIE(BSSAP_IEI_CC_SETUP_CONTAINER_INTERNAL, &sc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cce) != ITS_SUCCESS)
        {
            cout << "Error encoding CC Establishment " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CC Establishment" << endl;
            return;
        }     

        PrintBSSMAPMsgCCEstablishment(dec);
    }

    if (Cmd("SETUP", "Encode Setup"))
    {
        BSSAP_Facility                facility;
        BSSAP_ProgressIndicator       progress;
        BSSAP_BearerData              bd;
        BSSAP_CCCause                 cause;
        BSSAP_CCCapabilities          cc;
        BSSAP_ConnectedNumber         cn;
        BSSAP_ConnectedSubAddress     cs;
        BSSAP_CallingPartyBCDNumber   cg;
        BSSAP_CallingPartySubAddress  cgs;
        BSSAP_CalledPartyBCDNumber    cd;
        BSSAP_CalledPartySubAddress   cds;
        BSSAP_UserToUser              userTouser;
        BSSAP_Signal                  signal;
        BSSAP_LowLevelCompInfo        lc;
        BSSAP_HighLevelCompInfo       hc;
        BSSAP_RepeatIndicator         ri;
        BSSAP_PriorityLevel           priolev;
        BSSAP_AlertingPattern         alertPat;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Setup setup;

        setup.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        setup.SetTIVal(TI_VALUE_3);                      //0x03
        setup.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        ri.SetRepeatType(1);
        setup.AddIE(BSSAP_IEI_CC_REPEAT_INDICATOR, &ri);

        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        setup.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        bd.SetInfoTransferCapabAndRadioChannelType(2, 2);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        setup.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        facility.SetFacilityData(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        setup.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        signal.SetSignal(1);
        setup.AddIE(BSSAP_IEI_CC_SIGNAL, &signal);

        cg.SetTypeAndNumPlan( 1, 1);
        cg.SetDigits(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLING_PARTY_BCD_NUMBER, &cg);

        cgs.SetSubAddressType( 1, ITS_TRUE);
        cgs.SetSubAddressInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLING_PARTY_SUB_ADDRESS, &cgs);

        cd.SetTypeAndNumPlan( 1, 1);
        cd.SetDigits(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLED_PARTY_BCD_NUMBER, &cd);

        cds.SetSubAddressType( 1, ITS_TRUE);
        cds.SetSubAddressInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLED_PARTY_SUB_ADDRESS, &cds);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        lc.SetLowLevelCompInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(value, value);
        setup.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        priolev.SetPriority(PRIORITY_LEVEL_2);
        setup.AddIE(BSSAP_IEI_CC_PRIORITY_LEVEL, &priolev);

        alertPat.SetPattern(ALERTING_PATTERN_7);
        setup.AddIE(BSSAP_IEI_CC_ALERTING_PATTERN, &alertPat);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &setup) != ITS_SUCCESS)
        {
            cout << "Error encoding setup " << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding setup." << endl;
            return;
        }     

        PrintBSSMAPMsgSetup(dec);
    }

    if (Cmd("MODIFY", "Encode Modify"))
    {
        BSSAP_BearerData                 bd;
        BSSAP_LowLevelCompInfo           lc;
        BSSAP_HighLevelCompInfo          hc;
        BSSAP_ReverseCallSetupDirection  revCall;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Modify modify;

        modify.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        modify.SetTIVal(TI_VALUE_3);                      //0x03
        modify.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        modify.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        lc.SetLowLevelCompInfo(buff, 5);
        modify.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(1, 1);
        modify.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        modify.AddIE(BSSAP_IEI_CC_REVERSE_CALL_SETUP_DIRECTION, &revCall);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &modify) != ITS_SUCCESS)
        {
            cout << "Error encoding modify " << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        ITS_OCTET inject[] = { 0x01, 0x00, 0x10, 0xb3, 0x17, 0x01, 0xa1, 0x7c,
                               0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7d, 0x02,
                               0x81, 0x81, 0xa3 };
        DumpData(inject, sizeof(inject));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(inject, sizeof(inject), &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify." << endl;
            return;
        }     
    
        PrintBSSMAPMsgModify(dec);
    }

    if (Cmd("MODIFYCOMP", "Encode ModifyComplete"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ModifyComplete mc;

        mc.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        mc.SetTIVal(TI_VALUE_3);                      //0x03
        mc.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
       
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        mc.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        lc.SetLowLevelCompInfo(buff, 5);
        mc.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(1, 1);
        mc.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &mc) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgModifyComplete(dec);
    }

    if (Cmd("MODIFYREJECT", "Encode ModifyReject"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ModifyReject mr;
       
        mr.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        mr.SetTIVal(TI_VALUE_3);                      //0x03
        mr.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        mr.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);


        cause.SetCodingLocationCause(1, 1, 1);
        mr.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        lc.SetLowLevelCompInfo(buff, 5);
        mr.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(1, 1);
        mr.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &mr) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgModifyReject(dec);
    }

    if (Cmd("ENCUSERINFO", "Encode UserInformation"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UserInformation ui;
       
        ui.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        ui.SetTIVal(TI_VALUE_3);                      //0x03
        ui.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        ui.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        ui.AddIE(BSSAP_IEI_CC_MORE_DATA, &md);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &ui) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgUserInformation(dec);
    }


    if (Cmd("ENCHOLD", "Encode Hold"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Hold ho;
       
        ho.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        ho.SetTIVal(TI_VALUE_3);                      //0x03
        ho.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &ho) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgHold(dec);
    }

    if (Cmd("ENCHOLDACK", "Encode Hold Ack"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HoldAck hack;
       
        hack.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        hack.SetTIVal(TI_VALUE_3);                      //0x03
        hack.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &hack) != ITS_SUCCESS)
        {
            cout << "Error encoding hold ack " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgHoldAck(dec);
    }

    if (Cmd("ENCHOLDREJECT", "Encode Hold Reject"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HoldReject hrej;
       
        hrej.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        hrej.SetTIVal(TI_VALUE_3);                      //0x03
        hrej.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        hrej.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &hrej) != ITS_SUCCESS)
        {
            cout << "Error encoding hold reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgHoldReject(dec);
    }

    if (Cmd("ENCRTRV", "Encode Retrieve"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Retrieve rtrv;
       
        rtrv.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rtrv.SetTIVal(TI_VALUE_3);                      //0x03
        rtrv.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rtrv) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgRetrieve(dec);
    }

    if (Cmd("ENCRTRVACK", "Encode Retrieve Ack"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_RetrieveAck rack;
       
        rack.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rack.SetTIVal(TI_VALUE_3);                      //0x03
        rack.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rack) != ITS_SUCCESS)
        {
            cout << "Error encoding hold ack " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgRetrieveAck(dec);
    }

    if (Cmd("ENCRTRVREJECT", "Encode Retrieve Reject"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_RetrieveReject rrej;
       
        rrej.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rrej.SetTIVal(TI_VALUE_3);                      //0x03
        rrej.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        rrej.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rrej) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgRetrieveReject(dec);
    }

    if (Cmd("ENCDISCONNECT", "Encode Disconnect"))
    {
        BSSAP_Facility           facility;
        BSSAP_ProgressIndicator  progress;
        BSSAP_CCCause            cause;
        BSSAP_UserToUser         userTouser;
        BSSAP_AllowedAction     allwdact;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Disconnect disc;
       
        disc.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        disc.SetTIVal(TI_VALUE_3);                      //0x03
        disc.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        cause.SetCodingLocationCause(1, 1, 1);
        disc.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        facility.SetFacilityData(buff, 0);
        disc.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        disc.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        disc.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        //allwdact.SetCCBS(ACTIVATION_OF_CCBS_NOT_POS);  // 0
        allwdact.SetCCBS(ACTIVATION_OF_CCBS_POS);    // 1
        disc.AddIE(BSSAP_IEI_CC_ALLOWED_ACTIONS, &allwdact);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &disc) != ITS_SUCCESS)
        {
            cout << "Error encoding Disconnect " << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Disconnect" << endl;
            return;
        }     

        PrintBSSMAPMsgDisconnect(dec);
    }

    if (Cmd("ENCRELEASE", "Encode Release"))
    {
        BSSAP_ChanType                chanType;
        BSSAP_L3HeaderInfo            l3hInfo;
        BSSAP_Facility                facility;
        BSSAP_BearerData              bd;
        BSSAP_CCCause                 cause;
        BSSAP_UserToUser              userTouser;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Release rel;
       
        rel.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rel.SetTIVal(TI_VALUE_3);                      //0x03
        rel.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        cause.SetCodingLocationCause(1, 1, 1);
        rel.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        facility.SetFacilityData(buff, 0);
        rel.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        rel.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        cause.SetCodingLocationCause(2, 2, 2);
        rel.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rel) != ITS_SUCCESS)
        {
            cout << "Error encoding Release" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Release " << endl;
            return;
        }     

        PrintBSSMAPMsgRelease(dec);
    }

    if (Cmd("ENCRELEASECMP", "Encode ReleaseComplete"))
    {
        BSSAP_ChanType                chanType;
        BSSAP_L3HeaderInfo            l3hInfo;
        BSSAP_Prio                    prio;
        BSSAP_CktIDCode               cktId;
        BSSAP_DLDTXFlag               dlFlag;
        BSSAP_ClassmarkInfo2          cmInfo2;
        BSSAP_GrpClRef                gcRef;
        BSSAP_TalkerFlag              tkFlag;
        BSSAP_LsaAccCtrlSuppr         lacs;
        BSSAP_ConfigEvlInd            ceInd;
        BSSAP_ServHandover            servHand;
        BSSAP_Facility                facility;
        BSSAP_ProgressIndicator       progress;
        BSSAP_BearerData              bd;
        BSSAP_CCCause                 cause;
        BSSAP_CCCapabilities          cc;
        BSSAP_ConnectedNumber         cn;
        BSSAP_ConnectedSubAddress     cs;
        BSSAP_CallingPartyBCDNumber   cg;
        BSSAP_CallingPartySubAddress  cgs;
        BSSAP_CalledPartyBCDNumber    cd;
        BSSAP_CalledPartySubAddress   cds;
        BSSAP_UserToUser              userTouser;
        BSSAP_SSVersion               ss;
        BSSAP_Signal                  signal;
        BSSAP_LowLevelCompInfo        lc;
        BSSAP_HighLevelCompInfo       hc;
        BSSAP_MoreData                md;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ReleaseComplete relcmp;
       
        relcmp.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        relcmp.SetTIVal(TI_VALUE_3);                      //0x03
        relcmp.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        cause.SetCodingLocationCause(1, 1, 1);
        relcmp.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        facility.SetFacilityData(buff, 0);
        relcmp.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        relcmp.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &relcmp) != ITS_SUCCESS)
        {
            cout << "Error encoding ReleaseComplete" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding ReleaseComplete" << endl;
            return;
        }     

        PrintBSSMAPMsgReleaseComplete(dec);
    }

    if (Cmd("ENCCONGCRTL", "Encode Congestion Contol"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_CongestionLevel   cl;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CongestionControl cong;
       
        cong.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        cong.SetTIVal(TI_VALUE_3);                      //0x03
        cong.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        cl.SetCongestionLevel(1);
        cong.AddIE(BSSAP_IEI_CC_CONGESTION_LEVEL_INTERNAL, &cl);

        cause.SetCodingLocationCause(1, 1, 1);
        cong.AddIE(BSSAP_IEI_CC_CAUSE, &cause);


        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cong) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgCongestionControl(dec);
    }

    if (Cmd("ENCNOTIFY", "Encode Notify"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_Notify   nfy;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_NotificationIndicator ni;
       
        nfy.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        nfy.SetTIVal(TI_VALUE_3);                      //0x03
        nfy.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        ni.SetNotifyIndicator(1);
        nfy.AddIE(BSSAP_IEI_CC_NOTIFICATION_INDICATOR_INTERNAL, &ni);


        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &nfy) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgNotify(dec);
    }

    if (Cmd("ENCSTARTDTMF", "Encode Start DTMF"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_StartDTMF sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        kpf.SetKeyValue(1);
        sdtmf.AddIE(BSSAP_IEI_CC_KEYPAD_FACILITY, &kpf);


        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgStartDTMF(dec);
    }

    if (Cmd("ENCSTARTDTMFACK", "Encode Start DTMF Ack"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_StartDTMFAck sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        kpf.SetKeyValue(1);
        sdtmf.AddIE(BSSAP_IEI_CC_KEYPAD_FACILITY, &kpf);


        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgStartDTMFAck(dec);
    }

    if (Cmd("ENCSTARTDTMFREJECT", "Encode Start DTMF Reject"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_StartDTMFReject sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        sdtmf.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgStartDTMFReject(dec);
    }


    if (Cmd("ENCSTOPDTMF", "Encode Stop DTMF"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_StopDTMF sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgStopDTMF(dec);
    }

    if (Cmd("ENCSTOPDTMFACK", "Encode Stop DTMF Ack"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_StopDTMFAck sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgStopDTMFAck(dec);
    }

    if (Cmd("ENCSTATUS", "Encode Status"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;
        BSSAP_CallState        cs;
        BSSAP_AuxState         as;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Status status;
       
        status.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        status.SetTIVal(TI_VALUE_3);                      //0x03
        status.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        status.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        cs.SetCodingAndState(1, 1);
        status.AddIE(BSSAP_IEI_CC_CALL_STATE_INTERNAL, &cs);

        as.SetAuxState(1);
        status.AddIE(BSSAP_IEI_CC_AUXILLARY_STATES, &as);

        int len;

        // build the message
        if (BSSAP_Message::Encode(buff, len, &status) != ITS_SUCCESS)
        {
            cout << "Error encoding STATUS " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
       // ITS_OCTET buf[] ={ 0x01, 0x00, 0x08, 0xb3, 0x3d, 0x02, 0xa1, 0x81,
       //                    0x24, 0x01, 0x00};
        ITS_OCTET buf[] ={ 0x01, 0x00, 0x09, 0xb3, 0x05, 0x02, 0xa1, 0x81, 0x01,
                           0x24, 0x01, 0x00};
        len = sizeof(buf);
        DumpData(buf, len);

        if (BSSAP_Message::Decode(buf, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding STATUS" << endl;
            return;
        }     

        PrintBSSMAPMsgStatus(dec);
    }

    if (Cmd("ENCSTATUSENQ", "Encode Status Enquiry"))
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_StatusEnquiry se;
       
        se.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        se.SetTIVal(TI_VALUE_3);                      //0x03
        se.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &se) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }


        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding hold reject" << endl;
            return;
        }     

        PrintBSSMAPMsgStatusEnquiry(dec);
    }
    /*--------------------------------------------------------------*/

     /* ---------- 3.2.1.2 Assignment Complete ---------- */
    if (Cmd("ENCASSCMP", "Encode AssignmentComplete"))
    {        
        BSSAP_RRcause                   rrCs;
        BSSAP_CktIDCode                 cktId;
        BSSAP_CellID                    cellId;
        BSSAP_ChsChan                   chsChan;    
        BSSAP_ChsEncAlg                 ceAlg;
        BSSAP_CktPool                   cktPl;
        BSSAP_SpchVer                   spchVer;
        BSSAP_LsaId                     lsaid;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_AssignmentComplete assCmp;

        // populate RR Cause, add it to the message
        rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

        assCmp.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        assCmp.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi  
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);
        cellId.SetCellID(cid);
        
        assCmp.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

        // populate Chosen Channel, add it to the message
        chsChan.SetChan(CC_CH_SPEECH);                      //0x09
        chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01 
        
        assCmp.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);

        // populate Chosen Encryption Algorithm, add it to the message
        ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                 //0x03
        assCmp.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

        // populate Circuit Pool, add it to the message
        cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

        assCmp.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);        
        
        // populate Speech Version, add it to the message
        spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER3);         //0x21

        assCmp.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);

        // populate LSA Identifier, add it to the message
        lsaid.SetLSAIDBit1(0x01); 
        lsaid.SetLSAID(0x432111); 

        assCmp.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &assCmp) != ITS_SUCCESS)
        {
            cout << "Error encoding Assignment Complete." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Assignment Complete." << endl;
            return;
        }

        PrintBSSMAPMsgAssignComplete(dec); 
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.3 Assignment Failure ---------- */
    if (Cmd("ENCASSFAIL", "Encode AssignmentFailure"))
    {
        BSSAP_Cse                       cs;
        BSSAP_RRcause                   rrCs;
        BSSAP_CktPool                   cktPl;
        BSSAP_CktPoolList               cpList;

      
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_AssignmentFailure assFail;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        assFail.AddIE(BSSAP_IEI_CAUSE, &cs);    


        // populate RR Cause, add it to the message
        rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

        assFail.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);


        // populate Circuit Pool, add it to the message
        cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

        assFail.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);  

    
        // populate Circuit Pool List, add it to the message
        CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
//        cpList.AddCircuitPoolNo(cpool);
        for (i = 0; i < 2; i++)
        {
            cpList.SetCircuitPoolNo(cpool, i);
        }

        assFail.AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &assFail) != ITS_SUCCESS)
        {
            cout << "Error encoding Assignment Failure." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Assignment Failure." << endl;
            return;
        }

        PrintBSSMAPMsgAssignFailure(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.4 Block ---------- */
    if (Cmd("ENCBLOCK", "Encode Block"))
    {
        BSSAP_CktIDCode  cktId;
        BSSAP_Cse        cs;
        BSSAP_ConRlsReq  crReq;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Block blk;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        blk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        blk.AddIE(BSSAP_IEI_CAUSE, &cs); 

        // populate Connection Release Requested, add it to the message
        blk.AddIE(BSSAP_IEI_CONNECTION_RELEASE_REQUESTED, &crReq);
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &blk) != ITS_SUCCESS)
        {
            cout << "Error encoding Block." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        //ITS_OCTET inject[] = { 0x00, 0x09, 0x40, 0x01, 0x45, 0x11, 0x04, 0x02,
        //                       0xb0, 0x11, 0x36 };
        //ITS_OCTET inject[] = { 0x00, 0x08, 0x40, 0x01, 0x45, 0x11, 0x04, 0x02,
        //                       0xb0, 0x11 };
        ITS_OCTET inject[] = { 0x00, 0x08, 0x40, 0x01, 0x45, 0x11, 0x04, 
                               0xb0, 0x11, 0x36 };
        
        //DumpData(inject, sizeof(inject));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Block." << endl;
            return;
        }

        PrintBSSMAPMsgBlock(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.5 BlockingAcknowledge ------------ */
    if (Cmd("ENCBLKACK", "Encode BlockingAcknowledge"))
    {
        BSSAP_CktIDCode  cktId;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_BlockAcknowledge   blkAck;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x11

        blkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &blkAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Blocking Acknowledge." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        //ITS_OCTET inject[] = { 0x00, 0x04, 0x41, 0x01, 0x45, 0x11 };
        //ITS_OCTET inject[] = { 0x00, 0x09, 0x41, 0x01, 0x45, 0x11 };
        //ITS_OCTET inject[] = { 0x00, 0x02, 0x41, 0x01, 0x45, 0x11 };

        //DumpData(inject, sizeof(inject));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Blocking Acknowledge." << endl;
            return;
        }
       
        PrintBSSMAPMsgBlockAck(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.6 Unblock ---------- */
    if (Cmd("ENCUNBLK", "Encode Unblock"))
    {        
        BSSAP_CktIDCode                 cktId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Unblock unblk;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        unblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &unblk) != ITS_SUCCESS)
        {
            cout << "Error encoding Unblock." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        ITS_OCTET inject[] = { 0x00, 0x04, 0x41, 0x01, 0x45, 0x11 };
                                                                                                                            
        DumpData(inject, sizeof(inject));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(inject, sizeof(inject), &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Unblock." << endl;
            return;
        }   

        PrintBSSMAPMsgUnblock(dec);
    }
    /*--------------------------------------------------------------*/

    /* --------- 3.2.1.7 Unblock Acknowledge ---------- */
    if (Cmd("ENCUNBLKACK", "Encode UnblockAcknowledge"))
    {
        BSSAP_CktIDCode                 cktId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UnblockAcknowledge unblkAck;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        unblkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &unblkAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Unblock Acknowledge." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Unblock Acknowledge." << endl;
            return;
        }

        PrintBSSMAPMsgUnblockAck(dec);
    }
    

    /* ---------- 3.2.1.8 Handover Request ---------- */
    if (Cmd("ENCHANDREQ", "Encode HandoverRequest"))
    {        
        BSSAP_ChanType                  chanType; 
        BSSAP_EncryptionInformation     encInfo;
        BSSAP_ClassmarkInfo1            cmInfo1;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_CellID                    cellId;
        BSSAP_CellID                    target_cellId;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_InterBandToBeUsed         ibbu;
        BSSAP_Cse                       cs;
        BSSAP_ClassmarkInfo3            cmInfo3;
        BSSAP_CrtChan                   crtChan;
        BSSAP_SpchVer                   spchVer;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ChsEncAlg                 ceAlg;
        BSSAP_SrcRNCtoTgtRNCInfoUMTS    umts;
        BSSAP_SrcRNCtoTgtRNCInfoCDMA    cdma;
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverRequest handReq;

        // populate Channel Type, add it to the message      
        chanType.SetSpeechDataID(CT_DATA);                           //0x02
        chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);  //0x08
/*Repeated        
        // populate Channel Type, add it to the message      
        chanType.SetSpeechDataID(CT_DATA);                             //0x02
        chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);    //0x08
*/        
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 0);      //0x01
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 1);      //0x11
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 2);      //0x21
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 3);      //0x01
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 4);      //0x11
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 5);      //0x21

        chanType.SetDataTransp(1, CT_DATA_MAX_ALLOWED_CHANNEL1, 1);    //0x20
        chanType.SetIFDateRate(1, 0x53);                               //0x53
        chanType.SetAsymInd(0, 0x02);                                  //0x02

        handReq.AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);


        // populate Encryption Information, add it to the message
        encInfo.SetNoEncryption(0); 
        encInfo.SetA5_1(1);
        encInfo.SetA5_2(0);
        encInfo.SetA5_3(1);
        encInfo.SetA5_4(0);
        encInfo.SetA5_5(1);
        encInfo.SetA5_6(0);
        encInfo.SetA5_7(1);
        encInfo.SetKey(key, sizeof(key));                     

        handReq.AddIE(BSSAP_IEI_ENCRYPTION_INFORMATION, &encInfo);

        // Classmark Information 1 and 2 can not be set up at the sametime
        // populate Classmark Information 1, add it to the message
/*        cmInfo1.SetRFPowerCap(CIT1_RF_POWER_CAP_CLASS2);    //0x01
        cmInfo1.SetA51(CIT1_A5_1_IS_AVAILABLE);             //0x00
        cmInfo1.SetESIND(CIT1_ES_IND_IS_IMPLEMENTED);       //0x00
        cmInfo1.SetRevLevel(CIT1_REV_LEVEL_PHASE_2);        //0x01

        handReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1, &cmInfo1);

*/
        // populate Classmark Information 2, add it to the message
        cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
        cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
        cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
        cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
        cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
        cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
        cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
        cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
        cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
        cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
        cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
        cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
        cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
        cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
        cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
        cmInfo2.SetCM3(CIT2_CM3_OPTIONS_NOT_SUPPORTED);     //0x01

        handReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2); 

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        handReq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

        // populate Cell Identifier (target_cellId), add it to the message
        target_cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        target_cellId.SetCellID(cid);

        handReq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &target_cellId); 


        // populate Priority, add it to the message
        prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
        prio.SetQA(P_QUEUING_ALLOWED);                      //1
        prio.SetPVI(1);                 
        prio.SetPCI(P_NO_PREEMPTION );                      //0 

        handReq.AddIE(BSSAP_IEI_PRIORITY, &prio);   


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        handReq.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Downlink DTX Flag, add it to the message
        dlFlag.SetDTXFlag(DLDTX_ACTIVATE_ALLOWED);          //0x00
        //dlFlag.SetDTXFlag(DLDTX_ACTIVATE_FORBIDDEN);          //0x01
        
        handReq.AddIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, &dlFlag);


        // populate Interference Band To Be Used, add it to the message
        ibbu.SetBandToBeUsed(octet);                        //0x04
        
        handReq.AddIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED, &ibbu);


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        handReq.AddIE(BSSAP_IEI_CAUSE, &cs); 


        // populate Classmark Information3, add it to the message
        cmInfo3.SetMultiBand(0x05);                      //0x01
        cmInfo3.SetA54(1);                               //0x01
        cmInfo3.SetA55(0);                               //0x01
        cmInfo3.SetA56(0);                               //0x01
        cmInfo3.SetA57(1);                               //0x01
        cmInfo3.SetRadioCap1(0x04);   
        cmInfo3.SetRadioCap2(0x08);
        cmInfo3.SetMultiSlotClass(0x07);
        cmInfo3.SetRGSMCap(0x06);
        cmInfo3.SetSMValue(0x09); 
        cmInfo3.SetSMSValue(0x02);
        cmInfo3.SetUCS2Treat(1);
        cmInfo3.SetExtMeasCap(0);
        cmInfo3.SetMSConGPS(1);
        cmInfo3.SetMSBasedGPS(0); 
        cmInfo3.SetMSAssistedGPS(1);
        cmInfo3.SetMSBasedEOTD(0);
        cmInfo3.SetMSAssistedEOTD(1);
        
        handReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, &cmInfo3);


        // populate Current Channel, add it to the message
        crtChan.SetChan(CC_CHANNEL_MODE_SPEECH);               //0x01
        crtChan.SetChanMode(CC_CHANNEL_SDCCH);                 //0x01

        handReq.AddIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1, &crtChan);


        // populate Speech Version, add it to the message
        spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01

        handReq.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);

        // populate Group Call Reference, add it to the message
        gcRef.SetCallRef(uint);
        gcRef.SetClPrio(GCR_CALL_PRIORITY_LEVEL_B);         //0x06
        gcRef.SetAF(GCR_AF_ACK_REQUIRED);                   //0x01
        gcRef.SetSF(GCR_SF_VBS);                            //0x00
        gcRef.SetCiphInfo(GCR_CIPHERING_KEY_9);             //0x09;

        handReq.AddIE(BSSAP_IEI_GROUP_CALL_REFERENCE, &gcRef);

        // populate Talker Flag, add it to the message
        handReq.AddIE(BSSAP_IEI_TALKER_FLAG, &tkFlag);


        // populate Configuration Evolution Indication, add it to the message
        ceInd.SetSMI(CE_NO_MODIFICATION_ALLOWED);           //0x00
        handReq.AddIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, &ceInd);


        // populate Chosen Encryption Algorithm, add it to the message
        ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03
        handReq.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

        // populate Soruce RNC to Target RNC Transparent Information (UMTS), 
        // add it to the message
        umts.SetSrcRNCtoTgtRNCInfoUMTS(key, sizeof(key));                     

        handReq.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS, &umts);

        // populate Soruce RNC to Target RNC Transparent Information (CDMA), 
        // add it to the message
        cdma.SetSrcRNCtoTgtRNCInfoCDMA(key, sizeof(key));                     

        handReq.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA, &cdma);



        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handReq) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Request." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);
/*
	ITS_OCTET injectBuf[] = {0x00, 0x57, 0x10, 0x0b, 0x05, 0x02, 0x08, 0xe0,
                                 0xd3, 0x40, 0x0a, 0x06, 0xaa, 0x01, 0x03, 0x03,
                                 0x04, 0x05, 0x12, 0x03, 0x21, 0x7f, 0x2f, 
                                 0x05, 0x08, 0x00, 0x22, 0x08, 0x11, 0x02, 0x28,
                                 0x02, 0x28, 0x06, 0x01, 0x17, 0x01, 0x45, 0x11,
                                 0x19, 0x01, 0x05, 0x08, 0x00, 0x22, 0x08, 0x11,
                                 0x02, 0x28, 0x02, 0x28, 0x14, 0x11, 0x04, 0x02,
                                 0xb0, 0x11, 0x13, 0x05, 0x59, 0x84, 0xc7, 0x8a,
                                 0x6a,
                                 0x31, 0x01, 0x40, 0x01, 0x37, 0x05, 0x00, 0x86,
                                 0x42, 0x0e, 0x90, 0x35, 0x39, 0x00, 0x2c, 0x03,
                                 0x51, 0x05, 0x01, 0x03, 0x03, 0x04, 0x05, 0x52,
                                 0x05, 0x01, 0x03, 0x03, 0x04, 0x05 };

        ITS_OCTET injectBuf[] = {0x00, 0x57, 0x10, 0x0b, 0x05, 0x02, 0x08, 0xe0,
                                 0xd3, 0x40, 0x0a, 0x06, 0xaa, 0x01, 0x02, 0x03,
                                 0x04, 0x05, 0x05, 0x08, 0x00, 0x22, 0x08, 0x11,
                                 0x02, 0x28, 0x02, 0x28, 0x05, 0x08, 0x00, 0x22,
                                 0x08, 0x11, 0x02, 0x28, 0x02, 0x28,                 
                                 //0x1d, 0x41,              // Classmark Info 1
                                 //0x12, 0x02, 0x11, 0x22,  // Classmark Info 2 
                                 0x06, 0x01, 0x17, 0x01, 0x45, 0x11, 0x19, 0x00,
                                 0x14, 0x11, 0x04, 0x02, 0xb0, 0x11, 0x13, 0x05,
                                 0x59, 0x84, 0xc7, 0x8a, 0x6a, 0x31, 0x11, 0x40,
                                 0x01, 0x37, 0x05, 0x00, 0x86, 0x42, 0x0e, 0x90,
                                 0x35, 0x39, 0x00, 0x2c, 0x03, 0x51, 0x05, 0x01,
                                 0x02, 0x03,
                                 0x04, 0x05, 0x52, 0x05, 0x01, 0x02, 0x03, 0x04,
                                 0x05 }; 

        DumpData(injectBuf, sizeof(injectBuf));
*/  
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Request." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverReq(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.9 Handover Required ----------- */    
    if (Cmd("ENCHANDRQD", "Encode HandoverRequired"))
    {           
        BSSAP_Cse                       cs;
        BSSAP_CellIDList                ciList;
        BSSAP_RspReq                    rspReq;
        BSSAP_CktPoolList               cpList;
        BSSAP_CrtChan                   crtChan;
        BSSAP_SpchVer                   spchVer;
        BSSAP_QueuingInd                qInd;
        BSSAP_OldBSStoNewBSSInfo        bssInfo;
        BSSAP_SrcRNCtoTgtRNCInfoUMTS    umts;
        BSSAP_SrcRNCtoTgtRNCInfoCDMA    cdma;
        // IEs included in Old BSS to New BSS
        BSSAP_ExtraInfo                 exInfo;
        BSSAP_CrtChan2                  crtChan2;
        BSSAP_TargetCellRadioInfo       tcri;
        BSSAP_GPRSSuspendInfo           gsi;
        BSSAP_MultirateConfigInfo       mci;
        BSSAP_DualTransferModeInfo      dtmi;
        BSSAP_UECapInfo                 uci;
        BSSAP_cdma2000CapInfo           cci;
        BSSAP_UTRANIndicationSet        upis;
        BSSAP_UESecurityInfo            usi;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverRequired handRqd;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        handRqd.AddIE(BSSAP_IEI_CAUSE, &cs); 


        // populate Cell Identifier List, add it to the message
        ciList.SetCellIDListDisc(CI_CID_CGI);
        //cgi
        CIL_CGI_SET_MCC_PCS(cid1,ushort);
        CIL_CGI_SET_MNC_PCS(cid1,octet);
        CIL_CGI_SET_LAC(cid1,ushort);
        CIL_CGI_SET_CI(cid1,ushort);
//        ciList.AddCellID(cid1);
        for (i = 0; i < 10; i++)
        {
            ciList.SetCellID(cid1, i);
        }

        handRqd.AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);

        // populate Response Request, add it to the message
        handRqd.AddIE(BSSAP_IEI_RESPONSE_REQUEST, &rspReq);
/*
        // populate Circuit Pool List, add it to the message
        CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
//        cpList.AddCircuitPoolNo(cpool);
        for (i = 0; i < 2; i++)
        {
            cpList.SetCircuitPoolNo(cpool, i);
        }

        handRqd.AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);

        // populate Response Request, add it to the message
        handRqd.AddIE(BSSAP_IEI_RESPONSE_REQUEST, &rspReq);

        // populate Current Channel, add it to the message
        crtChan.SetChan(CC_CHANNEL_MODE_SPEECH);               //0x01
        crtChan.SetChanMode(CC_CHANNEL_SDCCH);                 //0x01

        handRqd.AddIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1, &crtChan);


        // populate Speech Version, add it to the message
        spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);           //0x01

        handRqd.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);


        // populate Queuing Indicator, add it to the message
        qInd.SetQRI(QI_QUEUING_ALLOWED);                       //0x01

        handRqd.AddIE(BSSAP_IEI_QUEUING_INDICATOR, &qInd);

*/
        // populate Old BSS to New BSS Information, add it to the message

            // Estra Information
            exInfo.SetPREC(0x01);
            exInfo.SetLCS(0x01);

            bssInfo.AddIE(BSSAP_IEI_EXTRA_INFORMATION, &exInfo);

            // Current Channel Type 2
            crtChan2.SetChan(CCT2_CF_1_FULL_RATE);          //0x04
            crtChan2.SetChanMode(CCT2_CM_DATA_6);           //0x08

            bssInfo.AddIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_2, &crtChan2);

            // Target Cell Radio Information
            tcri.SetRXLEV_NCELL(0x11);
            bssInfo.AddIE(BSSAP_IEI_TARGET_CELL_RADIO_INFO, &tcri);


            // GPRS Suspend Information
            
            gsi.SetTLLI(key, sizeof(key));
            
            gsi.SetRAI(key2, sizeof(key2));
            
            gsi.SetSRN(key, sizeof(key));

            bssInfo.AddIE(BSSAP_IEI_GPRS_SUSPEND_INFO, &gsi);

            // Multirate Configuration Information
            mci.SetStartMode(MCI_CODEC_MODE_4);            // 0x03
            mci.SetICMI(0x01);
            mci.SetMRVersion(MCI_ADAPTIVE_MR_SPCH_VER_1);  // 0x01
            mci.SetARMCodecMode1(0x01);
            mci.SetARMCodecMode2(0x00);
            mci.SetARMCodecMode3(0x01);
            mci.SetARMCodecMode4(0x00);
            mci.SetARMCodecMode5(0x01);
            mci.SetARMCodecMode6(0x00);
            mci.SetARMCodecMode7(0x01);
            mci.SetARMCodecMode8(0x00);
            mci.SetThreshold1(0x06);
            mci.SetThreshold2(0x12);
            mci.SetThreshold3(0x19);
            mci.SetHysteresis1(0x05);
            mci.SetHysteresis2(0x04);
            mci.SetHysteresis3(0x01);

            bssInfo.AddIE(BSSAP_IEI_MULTIRATE_CONFIG_INFO, &mci);

            // Dual Transfer Mode Information
            dtmi.SetDTMInd(0x01);
            dtmi.SetSTOInd(0x00);
            dtmi.SetEGPRSInd(0x01);
    
            bssInfo.AddIE(BSSAP_IEI_DUAL_TRANSFER_MODE_INFO, &dtmi);

            // UE Capability Information
            uci.SetUECapInfo(key, sizeof(key));

            bssInfo.AddIE(BSSAP_IEI_UE_CAP_INFO, &uci);

            // cdma2000 Capability Information
            cci.SetcdmaCapInfo(key, sizeof(key));

            bssInfo.AddIE(BSSAP_IEI_CDMA_2000_CAP_INFO, &cci);

            // UTRAN Pre-configuration Indication Set
            upis.SetPre_Config_Id_Tag(0x04, 0x05, 0);
            upis.SetPre_Config_Id_Tag(0x06, 0x07, 1);
            upis.SetPre_Config_Id_Tag(0x01, 0x02, 2);
           
            bssInfo.AddIE(BSSAP_IEI_UTRAN_PRECONFIG_IND_SET_INFO, &upis);

            // UE Security Information
            usi.SetUESecurityInfo(key, sizeof(key));
            bssInfo.AddIE(BSSAP_IEI_UE_SECURITY_INFO, &usi);

        handRqd.AddIE(BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO, &bssInfo);


        // populate Soruce RNC to Target RNC Transparent Information (UMTS), 
        // add it to the message
        umts.SetSrcRNCtoTgtRNCInfoUMTS(key, sizeof(key));                     

        handRqd.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS, &umts);

        // populate Soruce RNC to Target RNC Transparent Information (CDMA), 
        // add it to the message
        cdma.SetSrcRNCtoTgtRNCInfoCDMA(key, sizeof(key));                     

        handRqd.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA, &cdma);
              
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handRqd) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Required." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

	ITS_OCTET injectBuf[] = { 0x00, 0xa1, 0x11, 0x04, 0x02, 0xb0, 0x11, 0x1b, 0x1a, 0x47, 0x00, 0x22, 0x08, 0x11, 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
	0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11, 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11, 0x02, 0x28, 0x02, 0x28, 0x22, 0x08,
	0x11, 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11, 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11, 0x02, 0x28, 0x02, 0x28, 0x22,
	0x08, 0x11, 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11, 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11, 0x02, 0x28, 0x02, 0x28,
	0x3a, 0x42, 0x01, 0x01, 0x03, 0x02, 0x02, 0x04, 0x08, 0x03, 0x01, 0x11, 0x04, 0x11, 0x01, 0x03, 0x03, 0x04, 0x05,
	0x03, 0x05, 0x03, 0x04, 0x05, 0x06, 0x07, 0x01, 0x03, 0x03, 0x04, 0x05, 0x05, 0x06, 0x27, 0x55, 0x06, 0x54, 0x91, 0x91,
	0x06, 0x01, 0x05, 0x07, 0x05, 0x01, 0x03, 0x03, 0x04, 0x05, 0x08, 0x05, 0x01, 0x03, 0x03, 0x04, 0x05, 0x09, 0x03, 0x54,
	0x76, 0x21, 0x0a, 0x05, 0x01, 0x03, 0x03, 0x04, 0x05, 0x51, 0x05, 0x01, 0x03, 0x03, 0x04, 0x05, 0x52, 0x05, 0x01, 0x03,
	0x03, 0x04, 0x05};
        DumpData(injectBuf, sizeof(injectBuf));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(injectBuf, sizeof(injectBuf), &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Required." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverRequired(dec);

    }


    /* ---------- 3.2.1.10 Handover Request Acknowledge----------- */
    if (Cmd("ENCHRACK", "Encode HandoverRequestAck"))
    {  
        BSSAP_L3Info                    l3Info;
        BSSAP_ChsChan                   chsChan;
        BSSAP_ChsEncAlg                 ceAlg;
        BSSAP_CktPool                   cktPl;
        BSSAP_SpchVer                   spchVer;
        BSSAP_CktIDCode                 cktId;
        BSSAP_LsaId                     lsaid;
        BSSAP_InterSystemInformation    iSysInfo;
        BSSAP_NewBSStoOldBSSInfo        bssInfo;
        //IEs for NewBSStoOldBSSInfo
        BSSAP_dlCellLoadInfo            downlink;
        BSSAP_ulCellLoadInfo            uplink;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverRequestAcknowledge hrAck;


        // populate Layer 3 Information, add it to the message
        l3Info.SetL3Info(key3, sizeof(key3));                      
        
        hrAck.AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);

      
        // populate Chosen Channel, add it to the message
        chsChan.SetChan(CC_CH_SPEECH);                      //0x09
        chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01 
        
        hrAck.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);


        // populate Chosen Encryption Algorithm, add it to the message
        ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03

        hrAck.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

        // populate Circuit Pool, add it to the message
        cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

        hrAck.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);        
        
  
        // populate Speech Version, add it to the message
        spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01

        hrAck.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        hrAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        // populate LSA Identifier, add it to the message
        lsaid.SetLSAIDBit1(0x01); 
        lsaid.SetLSAID(0x432111); 

        hrAck.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);

        //Downlink Cell Load Information
        downlink.SetCellCapClassValue(0x01);
        downlink.SetLoadValue(0x02);
        downlink.SetRTLoadValue(0x03);
        downlink.SetNRTLoadInfo(0x04);
        bssInfo.AddIE(BSSAP_IEI_DOWNLINK_CELL_LOAD_INFO, &downlink);
                                                                                
        uplink.SetCellCapClassValue(0x01);
        uplink.SetLoadValue(0x02);
        uplink.SetRTLoadValue(0x03);
        uplink.SetNRTLoadInfo(0x04);
        bssInfo.AddIE(BSSAP_IEI_UPLINK_CELL_LOAD_INFO, &uplink);
                                                                                
        hrAck.AddIE(BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO, &bssInfo);

        iSysInfo.SetTransparentContainer(key, sizeof(key));

        hrAck.AddIE(BSSAP_IEI_INTER_SYSTEM_INFO, &iSysInfo);        

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &hrAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Request Acknowledge." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Request Acknowledge." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverReqAck(dec);
    }


    /* ---------- 3.2.1.11 Handover Command ---------- */
    if (Cmd("ENCHANDCMD", "Encode HandoverCommand"))
    {        
        BSSAP_L3Info                    l3Info;
        BSSAP_CellID                    cellId;
        BSSAP_NewBSStoOldBSSInfo        bssInfo;
        //IEs for NewBSStoOldBSSInfo
        BSSAP_dlCellLoadInfo            downlink;
        BSSAP_ulCellLoadInfo            uplink;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverCommand  handCmd;


        // populate Layer 3 Information, add it to the message
        l3Info.SetL3Info(key3, sizeof(key3));                      
//        l3Info.SetL3Info(key3, 0);                      
        
        handCmd.AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);


        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi  
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,0x22);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);
        cellId.SetCellID(cid);

        handCmd.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

        //Downlink Cell Load Information       
        downlink.SetCellCapClassValue(0x01);
        downlink.SetLoadValue(0x02);
        downlink.SetRTLoadValue(0x03);
        downlink.SetNRTLoadInfo(0x04);
        bssInfo.AddIE(BSSAP_IEI_DOWNLINK_CELL_LOAD_INFO, &downlink);
        
        uplink.SetCellCapClassValue(0x01);
        uplink.SetLoadValue(0x02);
        uplink.SetRTLoadValue(0x03);
        uplink.SetNRTLoadInfo(0x04);
        bssInfo.AddIE(BSSAP_IEI_UPLINK_CELL_LOAD_INFO, &uplink);

        handCmd.AddIE(BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO, &bssInfo);


        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Command." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

//        ITS_OCTET injectBuf[]={0x00, 0x0d, 0x13, 0x17, 0x00, 0x05, 0x08, 0x00, 0x22, 0x08, 0x22, 0x02, 0x28, 0x02, 0x28 };
        ITS_OCTET injectBuf[]={0x00,0x0d,0x13,0x17,0x02,0x11,0x22,0x05,0x08,0x00,0x22,0x08,0x22, 0x02, 0x28, 0x02, 0x28 };

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Command." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverCmd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.12 Handover Complete ---------- */
    if (Cmd("ENCHANDCMP", "Encode HandoverComplete"))
    {        
        BSSAP_RRcause                   rrCs;
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverComplete handCmp;

        // populate RR Cause, add it to the message
        rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

        handCmp.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handCmp) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Complete." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Complete." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverComplete(dec);         
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.13 Handover Succeeded ---------- */
    if (Cmd("ENCHANDSUC", "Encode HandoverSucceeded"))
    {        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverSucceeded handSuc;

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handSuc) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Succeeded." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Succeeded." << endl;
            return;
        }       

        PrintBSSMAPMsgHandoverSucceeded(dec);         
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.14 Handover Candidate Enquire ---------- */
    if (Cmd("ENCHCENQ", "Encode HandoverCandidateEnquire"))
    { 
        BSSAP_NumMSs                    nMs;
        BSSAP_CellIDList                ciList;
        BSSAP_CellID                    cellId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverCandidateEnquire hcEnq;


        // populate Cell Identifier List, add it to the message
        nMs.SetNumHand(octet);                         //0x11

        hcEnq.AddIE(BSSAP_IEI_NUMBER_OF_MS, &nMs);


        // populate Cell Identifier List, add it to the message
        ciList.SetCellIDListDisc(CI_CID_CGI);
        //cgi
        CIL_CGI_SET_MCC_PCS(cid1,ushort);
        CIL_CGI_SET_MNC_PCS(cid1,ushort);
        CIL_CGI_SET_LAC(cid1,ushort);
        CIL_CGI_SET_CI(cid1,ushort);
//        ciList.AddCellID(cid1);
        for (i = 0; i < 10; i++)
        {
            ciList.SetCellID(cid1, i);
        }

        hcEnq.AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);



        // populate Cell Identifier, add it to the message
        int disc = -1;

        cout << "Select Discriminator." <<endl;
        cout << "[0] CGI" << endl;
        cout << "[1] LAC" << endl;
        cout << "[2] CI" << endl;
        cout << "[3] PLMN_LAC_RNC" << endl;
        cout << "[4] RNC" << endl;
        cout << "[5] LAC_RNC" << endl;
        cout << "[6] SAI" << endl;
        cout << "-->" << endl;
        cin >> disc;


        if (disc == 0)
        {
            cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
            CI_CGI_SET_MCC_PCS(cid,ushort);
            CI_CGI_SET_MNC_PCS(cid,ushort);
            CI_CGI_SET_LAC(cid,ushort);
            CI_CGI_SET_CI(cid,ushort); 
        }
        else if (disc == 1)
        {
            cellId.SetCellIDDisc(CI_CID_LAC);  //lac
            CI_LACCI_SET_LAC(cid,ushort);
            CI_LACCI_SET_CI(cid,ushort);
        }
        else if (disc == 2)
        {
            cellId.SetCellIDDisc(CI_CID_CI);  //ci
            CI_CI_SET_CI(cid,ushort);
        }
        else if (disc == 3)
        {
            cellId.SetCellIDDisc(CI_CID_PLMN_LAC_RNC);  //plmn_lac_rnc
            CI_PLR_SET_MCC(cid,ushort);
            CI_PLR_SET_MNC(cid,octet);
            CI_PLR_SET_LAC(cid,ushort);
            CI_PLR_SET_RNC_ID(cid,ushort); 
        }
        else if (disc == 4)
        {
            cellId.SetCellIDDisc(CI_CID_RNC);  // rnc
         
            CI_RNC_SET_RNC_ID(cid,ushort); 
        }
        else if (disc == 5)
        {
            cellId.SetCellIDDisc(CI_CID_LAC_RNC);  // lac_rnc
            
            CI_LR_SET_LAC(cid,ushort);
            CI_LR_SET_RNC_ID(cid,ushort); 
        }
        else if (disc == 6)
        {
            cellId.SetCellIDDisc(CI_CID_SAI);  // sai
            CI_SAI_SET_MCC(cid,ushort);
            CI_SAI_SET_MNC(cid,ushort);
            CI_SAI_SET_LAC(cid,ushort);
            CI_SAI_SET_SAC(cid,ushort); 
        }

        cellId.SetCellID(cid);

        hcEnq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &hcEnq) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Candidate Enquire." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Candidate Enquire." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverCandidateEnq(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.15 Handover Candidate Response ---------- */
    if (Cmd("ENCHCRSP", "Encode HandoverCandidateResponse"))
    { 
        BSSAP_NumMSs                    nMs;
        BSSAP_CellID                    cellId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverCandidateResponse hcRsp;

        // populate Cell Identifier List, add it to the message
        nMs.SetNumHand(octet);

        hcRsp.AddIE(BSSAP_IEI_NUMBER_OF_MS, &nMs);


        // populate Cell Identifier, add it to the message

        int disc = -1;

        cout << "Select Discriminator." <<endl;
        cout << "[0] CGI" << endl;
        cout << "[1] LAC" << endl;
        cout << "[2] CI" << endl;
        cout << "-->" << endl;
        cin >> disc;


        if (disc == 0)
        {
            cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
            CI_CGI_SET_MCC_PCS(cid,ushort);
            CI_CGI_SET_MNC_PCS(cid,octet);
            CI_CGI_SET_LAC(cid,ushort);
            CI_CGI_SET_CI(cid,ushort); 
        }
        else if (disc == 1)
        {
            cellId.SetCellIDDisc(CI_CID_LAC);  //lac
            CI_LACCI_SET_LAC(cid,ushort);
            CI_LACCI_SET_CI(cid,ushort);
        }
        else if (disc == 2)
        {
            cellId.SetCellIDDisc(CI_CID_CI);  //ci
            CI_CI_SET_CI(cid,ushort);
        }


        cellId.SetCellID(cid);

        hcRsp.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 
 
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &hcRsp) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Candidate Response." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Candidate Response." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverCandidateRsp(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.16 Handover Failure ---------- */
    if (Cmd("ENCHANDFAIL", "Encode HandoverFailure"))
    {     
        BSSAP_Cse                       cs;
        BSSAP_RRcause                   rrCs;
        BSSAP_CktPool                   cktPl;
        BSSAP_CktPoolList               cpList;

      
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverFailure handFail;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        handFail.AddIE(BSSAP_IEI_CAUSE, &cs);    


        // populate RR Cause, add it to the message
        rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

        handFail.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);


        // populate Circuit Pool, add it to the message
        cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

        handFail.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);  

     
        // populate Circuit Pool List, add it to the message
        CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
//        cpList.AddCircuitPoolNo(cpool);
        for (i = 0; i < 2; i++)
        {
            cpList.SetCircuitPoolNo(cpool, i);
        }

        handFail.AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);  
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handFail) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Failure." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Failure." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverFailure(dec);           
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.17 Resource Request ---------- */
    if (Cmd("ENCRESREQ", "Encode ResourceRequest"))
    {         
        BSSAP_Period                    prd;
        BSSAP_CellID                    cellId;
        BSSAP_ResIndMethod              riMthd;
        BSSAP_ExtResInd                 erInd;
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ResourceRequest resReq;

        // populate Periodicity, add it to the message
        prd.SetPeriod(octet);                          //0x11

        resReq.AddIE(BSSAP_IEI_PERIODICITY, &prd);


        // populate Resource Indication Method, add it to the message
        riMthd.SetResIndMethod(RIM_SUBCLAUSE_3);          //0x03

        resReq.AddIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD, &riMthd);
        

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_GSM_DCS(cid,ushort);
        CI_CGI_SET_MNC_GSM_DCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        resReq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Extended Resource Indicator, add it to the message
        erInd.SetTARR(1);     
        erInd.SetSM(0);

        resReq.AddIE(BSSAP_IEI_EXTENDED_RESOURCE_INDICATOR, &erInd);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &resReq) != ITS_SUCCESS)
        {
            cout << "Error encoding Resource Request." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Resource Request." << endl;
            return;
        }

        PrintBSSMAPMsgResourceReq(dec);     
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.18 Resource Indication ---------- */
    if (Cmd("ENCRESIND", "Encode ResourceIndication"))
    {             
        BSSAP_ResIndMethod              riMthd;
        BSSAP_CellID                    cellId;
        BSSAP_ResAvail                  resAvail;
        BSSAP_TotResAcc                 tra;        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ResourceIndication resInd;

        // populate Resource Indication Method, add it to the message
        riMthd.SetResIndMethod(RIM_SUBCLAUSE_1);          //0x00

        resInd.AddIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD, &riMthd);
        

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        resInd.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Resource Available, add it to the message
        resAvail.SetNumFullHalf(ushort, ushort1, 0); 
        resAvail.SetNumFullHalf(ushort3, ushort4, 1); 
        resAvail.SetNumFullHalf(ushort, ushort1, 2);
        resAvail.SetNumFullHalf(ushort3, ushort4, 3);
        resAvail.SetNumFullHalf(ushort3, ushort4, 4);

        resInd.AddIE(BSSAP_IEI_RESOURCE_AVAILABLE, &resAvail);


        // populate Total Resource Accessible, add it to the message
        tra.SetFullRate(ushort);     
        tra.SetHalfRate(ushort1);

        resInd.AddIE(BSSAP_IEI_TOTAL_RESOURCE_ACCESSIBLE, &tra);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &resInd) != ITS_SUCCESS)
        {
            cout << "Error encoding Resource Indication." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Resource Indication." << endl;
            return;
        }

        PrintBSSMAPMsgResourceInd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.19 Paging ---------- */
    if (Cmd("ENCPAGING", "Encode Paging"))
    {     
        BSSAP_IMSI                      imsi;
        BSSAP_CellIDList                ciList;
        BSSAP_TMSI                      tmsi;
        BSSAP_ChanNeeded                chanNd;
        BSSAP_eMMLPrio                  emmlp;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Paging pag;
        
        // populate IMSI, add it to the message
        //imsi.SetDigits(digits, strlen(digits));              //7260686
        imsi.SetDigitsB(mindig, 7);

        pag.AddIE(BSSAP_IEI_IMSI, &imsi);

        // populate Cell Identifier List, add it to the message
        //ciList.SetCellIDListDisc(CI_CID_CGI);
        ciList.SetCellIDListDisc(CIL_CID_ALL_CELLS);
        //cgi
        //   CIL_CGI_SET_MCC_PCS(cid1, ushort);
        //   CIL_CGI_SET_MNC_PCS(cid1, octet);
        //   CIL_CGI_SET_LAC(cid1, ushort);
        //   CIL_CGI_SET_CI(cid1, ushort);
        CIL_CGI_SET_MCC_GSM_DCS(cid1, ushort);
        CIL_CGI_SET_MNC_GSM_DCS(cid1, octet);
        CIL_CGI_SET_LAC(cid1, ushort);
        CIL_CGI_SET_CI(cid1, ushort);

        //ciList.AddCellID(cid1);
        for (i = 0; i < 4; i++)
        {
            ciList.SetCellID(cid1, i);
        }

        pag.AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);

        // populate TMSI, add it to the message
        tmsi.SetTMSI(uint);                                    //0x4321000

        pag.AddIE(BSSAP_IEI_TMSI, &tmsi);

        // populate Channel Needed, add it to the message
        chanNd.SetChan(CN_CHANNEL_TCH_F);                      //0x02

        pag.AddIE(BSSAP_IEI_CHANNEL_NEEDED, &chanNd);

        // populate eMMLPriority, add it to the message
        emmlp.SetClPrio(octet);

        pag.AddIE(BSSAP_IEI_eMLPP_PRIORITY, &emmlp);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &pag) != ITS_SUCCESS)
        {
            cout << "Error encoding Paging." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

/*	ITS_OCTET injectBuf[] = {0x00, 0x5a, 0x52, 0x08, 0x04, 0x69, 0x64,
		                 0x63, 0x60, 0x09, 0x04, 0x04, 0x32, 0x10,
				 0x00, 0x1a, 0x47, 0x00, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x22, 0x08, 0x11,
				 0x02, 0x28, 0x02, 0x28, 0x24, 0x02, 0x38,
				 0x01};
*/
	ITS_OCTET injectBuf[] = {0x00, 0x14, 0x52, 0x08, 0x04, 0x69, 0x64,
		                 0x63, 0x60, 0x09, 0x04, 0x04, 0x32, 0x10,
				 0x00, 0x1a, 0x01, 0x06, 0x24, 0x02, 0x38,
				 0x01};

/*
        ITS_OCTET injectBuf[] = {0x00, 0x0e, 0x52, 0x08, 0x08, 0x09, 0x10,
                                 0x20, 0x89, 0x54, 0x42, 0x92, 0x21, 0x1a,
                                 0x01, 0x06 };
*/
        DumpData(injectBuf, sizeof(injectBuf));

        // do the decode
        BSSAP_Message* dec;

        if (BSSAP_Message::Decode(injectBuf, sizeof(injectBuf), &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Paging." << endl;
            return;
        }

        PrintBSSMAPMsgPaging(dec);  
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.20 Clear Request ---------- */
    if (Cmd("ENCLRREQ", "Encode ClearRequest"))
    { 
        BSSAP_Cse                     cs;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ClearRequest clrReq;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        clrReq.AddIE(BSSAP_IEI_CAUSE, &cs);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &clrReq) != ITS_SUCCESS)
        {
            cout << "Error encoding ClearRequest." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Clear Request." << endl;
            return;
        }

        PrintBSSMAPMsgClrReq(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.21 Clear Command ---------- */
    if (Cmd("ENCLRCOM", "Encode ClearCommand"))
    {     
        BSSAP_Cse           cs;
        BSSAP_L3HeaderInfo  l3hInfo;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ClearCommand clrCmd;
        
        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        clrCmd.AddIE(BSSAP_IEI_CAUSE, &cs);

        // populate Layer 3 Header Information, add it to the message
        l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        l3hInfo.SetTIVal(8);
        l3hInfo.SetTIFlag(9);
        
        clrCmd.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &clrCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding Clear Command." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // Reverse Cause with L3IF
        ITS_OCTET tmp[20];

        memcpy(tmp, &buff[3], 4);
        memmove(&buff[3], &buff[7], 4);
        memcpy(&buff[7], tmp, 4);

        // print the user data
        DumpData(buff, len);

	ITS_OCTET injectBuf[] = { 0x00, 0x09, 0x20, 0x04, 
                                  0x02, 0xb0, 0x11, 0x02, 0x00, 0x09 };

        DumpData(injectBuf, sizeof(injectBuf));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(injectBuf, sizeof(injectBuf), &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Clear Command." << endl;
            return;
        }

        PrintBSSMAPMsgClrCmd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.22 Clear Complete ---------- */
    if (Cmd("ENCLRCPLT", "Encode ClearComplete"))
    {     
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ClearComplete clrCplt;

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &clrCplt) != ITS_SUCCESS)
        {
            cout << "Error encoding Clear Complete." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Clear Complete." << endl;
            return;
        }

        PrintBSSMAPMsgClrComplete(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.23 Reset ---------- */
    if (Cmd("ENCRESET", "Encode Reset"))
    {            
        BSSAP_Cse                     cs;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Reset set;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
//        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);   //0x03U

        set.AddIE(BSSAP_IEI_CAUSE, &cs);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &set) != ITS_SUCCESS)
        {
            cout << "Error encoding Reset." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Reset." << endl;
            return;
        }

        PrintBSSMAPMsgReset(dec);
    }
    /*--------------------------------------------------------------*/

    /* ------------ 3.2.1.24 Reset Acknowledge -----------*/
    if (Cmd("ENCRESETACK", "Encode ResetAcknowledge"))
    {  
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ResetAcknowledge rstAck;
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rstAck) != ITS_SUCCESS)
        {
            cout << "Error encoding ResetAcknowledge." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding ResetAcknowledge." << endl;
            return;
        }

        PrintBSSMAPMsgResetAck(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.25 Handover Performed ---------- */
    if (Cmd("ENCHANDPFM", "HandoverPerformed"))
    {                  
        BSSAP_Cse                       cs;
        BSSAP_CellID                    cellId;
        BSSAP_ChsChan                   chsChan; 
        BSSAP_ChsEncAlg                 ceAlg;
        BSSAP_SpchVer                   spchVer;
        BSSAP_LsaId                     lsaid;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverPerformed handPfm;


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        handPfm.AddIE(BSSAP_IEI_CAUSE, &cs); 

        // populate Cell Identifier, add it to the message
        //cellId.SetCellIDDisc(CI_CID_CGI);         //cgi 0x00
        cellId.SetCellIDDisc(CI_CID_PLMN_LAC_RNC);  //cgi 0x08
        //cellId.SetCellIDDisc(CI_CID_LAC_RNC);       //cgi 0x10
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        handPfm.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

              
        // populate Chosen Channel, add it to the message
        chsChan.SetChan(CC_CH_SPEECH);                      //0x09
        chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01 
        
        handPfm.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);


        // populate Chosen Encryption Algorithm, add it to the message
        ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03

        handPfm.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

  
        // populate Speech Version, add it to the message
        spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01

        handPfm.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);

        // populate LSA Identifier, add it to the message
        lsaid.SetLSAIDBit1(0x01); 
        lsaid.SetLSAID(0x432111); 

        handPfm.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);
 
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handPfm) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Performed." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Handover Performed." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverPerformed(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.26 Overload ---------- */
    if (Cmd("ENCOVLD", "Encode Overload"))
    {          
        BSSAP_Cse                       cs;
        BSSAP_CellID                    cellId;

        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Overload ovld;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        ovld.AddIE(BSSAP_IEI_CAUSE, &cs); 

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        ovld.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &ovld) != ITS_SUCCESS)
        {
            cout << "Error encoding Overload." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Overload." << endl;
            return;
        }

        PrintBSSMAPMsgOverload(dec);
    }
    /*--------------------------------------------------------------*/

    /* ----------- 3.2.1.27 MSC Invoke Trace ------------------*/
    if (Cmd("ENCMSCIT", "Encode MSCInvokeTrace"))
    {  
        BSSAP_TraceTyp                   tType;
        BSSAP_TraceRef                   tRef;
        BSSAP_TrigID                     trigId;
        BSSAP_TransactionID              transID;
        BSSAP_MobileID                   mId;
        BSSAP_OMCID                      omcid;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_MSCInvokeTrace mscit;

         // populate Trace Type, add it to the message
        tType.SetInvEvnt(TT_IE_SEVEN_EVENTS);                    //0x01
        tType.SetMSCRecType(TT_MRT_DETAILED);                    //0x01
        tType.SetBSSRecType(TT_BRT_RADIO);                       //0x02
        tType.SetPrioInd(TT_PI_PRI);                             //0x01

        mscit.AddIE(BSSAP_IEI_TRACE_TYPE, &tType); 


        // populate Trace Reference, add it to the message
        tRef.SetTraceRef(ushort);                                //0x228

        mscit.AddIE(BSSAP_IEI_TRACE_REFERENCE, &tRef); 

        // populate Trigger ID, add it to the message
        trigId.SetEntityID(key1, 9);                             

        mscit.AddIE(BSSAP_IEI_TRIGGER_ID, &trigId); 

        // populate TransactioID, add it to the message
        transID.SetTransNo(ushort);                              //0x228

        mscit.AddIE(BSSAP_IEI_TRANSACTION_ID, &transID); 

        // populate Mobile Identity, add it to the message
        //populate the IEs, add to the message

        int iei;
        cout << "Input iei for testing" << endl;
        cout << "[1] IMSI. " <<endl;
        cout << "[2] IMEI. " <<endl;
        cout << "[3] IMEISV. " <<endl;
        cout << "--> ";
        cin >> iei;

        if (iei == 1)
        {
            mId.SetTypeIdentity(MI_IMSI);                 //0x01U
            mId.SetOddEvenInd(MI_ODD_DIGITS);             //1
            mId.SetIdenCDig(digits, strlen(digits));      //7260686 
        }
        else if (iei == 2)
        {
            mId.SetTypeIdentity(MI_IMEI);                 //0x02U
            mId.SetOddEvenInd(MI_ODD_DIGITS);             //1
            mId.SetIdenCDig(dgts1, strlen(dgts1));       // 15 digits 
        }
        else if (iei == 3)
        {
            mId.SetTypeIdentity(MI_IMEISV);                //0x02U
            mId.SetOddEvenInd(MI_EVEN_DIGITS);             //0
            mId.SetIdenCDig(dgts1, strlen(dgts2));       // 16 digits 
        }

        mscit.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mId); 

        // populate OMCID, add it to the message
        omcid.SetOMCID(key1, 9);                             

        mscit.AddIE(BSSAP_IEI_OMC_ID, &omcid); 

        int len;        
        // build the message
        if (BSSAP_Message::Encode(buff, len, &mscit) != ITS_SUCCESS)
        {
            cout << "Error encoding MSCInvokeTrace." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding MSCInvokeTrace." << endl;
            return;
        }

        PrintBSSMAPMsgMSCInvokeTrace(dec);
    }
    /*--------------------------------------------------------------------*/


    /* ----------- 3.2.1.28 BSSInvokeTrace ------------------*/
    if (Cmd("ENCBSSIT", "Encode BSSInvokeTrace"))
    {  
        BSSAP_TraceTyp                   tType;
        BSSAP_TraceRef                   tRef;
        BSSAP_FwdInd                     fwdInd;
        BSSAP_TrigID                     trigId;
        BSSAP_TransactionID              transID;
        BSSAP_MobileID                   mId;
        BSSAP_OMCID                      omcid;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_BSSInvokeTrace bssit;


        // populate Trace Type, add it to the message
        tType.SetInvEvnt(TT_IE_SEVEN_EVENTS);                    //0x01
        tType.SetMSCRecType(TT_MRT_DETAILED);                    //0x01
        tType.SetBSSRecType(TT_BRT_RADIO);                       //0x02
        tType.SetPrioInd(TT_PI_PRI);                             //0x01

        bssit.AddIE(BSSAP_IEI_TRACE_TYPE, &tType); 


        // populate Trace Reference, add it to the message
        tRef.SetTraceRef(ushort);                                //0x228

        bssit.AddIE(BSSAP_IEI_TRACE_REFERENCE, &tRef); 

         // populate Trigger ID, add it to the message
        trigId.SetEntityID(key1, 9);                             

        bssit.AddIE(BSSAP_IEI_TRIGGER_ID, &trigId); 

          // populate Forward Indicator, add it to the message
        fwdInd.SetFwdInd(FI_FORWARD_TRACE);                    //0x02

        bssit.AddIE(BSSAP_IEI_FORWARD_INDICATOR, &fwdInd); 

        // populate TransactioID, add it to the message
        transID.SetTransNo(ushort);                              //0x228

        bssit.AddIE(BSSAP_IEI_TRANSACTION_ID, &transID); 

        // populate Mobile Identity, add it to the message
        //populate the IEs, add to the message

        int iei;
        cout << "Input iei for testing" << endl;
        cout << "[1] IMSI. " <<endl;
        cout << "[2] IMEI. " <<endl;
        cout << "[3] IMEISV. " <<endl;
        cout << "--> ";
        cin >> iei;

        if (iei == 1)
        {
            mId.SetTypeIdentity(MI_IMSI);                 //0x01U
            mId.SetOddEvenInd(MI_ODD_DIGITS);             //1
            mId.SetIdenCDig(digits, strlen(digits));      //7260686 
        }
        else if (iei == 2)
        {
            mId.SetTypeIdentity(MI_IMEI);                 //0x02U
            mId.SetOddEvenInd(MI_ODD_DIGITS);             //1
            mId.SetIdenCDig(dgts1, strlen(dgts1));       // 15 digits 
        }
        else if (iei == 3)
        {
            mId.SetTypeIdentity(MI_IMEISV);                //0x02U
            mId.SetOddEvenInd(MI_EVEN_DIGITS);             //0
            mId.SetIdenCDig(dgts1, strlen(dgts2));       // 16 digits 
        }

        bssit.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mId); 

        // populate OMCID, add it to the message
        omcid.SetOMCID(key1, 9);                             

        bssit.AddIE(BSSAP_IEI_OMC_ID, &omcid); 
       
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &bssit) != ITS_SUCCESS)
        {
            cout << "Error encoding BSSInvokeTrace." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding BSSInvokeTrace." << endl;
            return;
        }

        PrintBSSMAPMsgBSSInvokeTrace(dec);
    }
    /*--------------------------------------------------------------------*/


    /* ----------- 3.2.1.29 Classmark Update ---------- */
    if (Cmd("ENCCMUPDATE", "Encode ClassmarkUpdate"))
    {        
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_ClassmarkInfo3            cmInfo3;    

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ClassmarkUpdate cmUpdt;

        
        // populate Classmark Information2, add it to the message
        cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
        cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
        cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
        cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
        cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
        cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
        cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
        cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
        cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
        cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
        cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
        cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
        cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
        cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
        cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
        cmInfo2.SetCM3(CIT2_CM3_OPTIONS_NOT_SUPPORTED);     //0x01

        cmUpdt.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2); 
        
        // populate Classmark Information3, add it to the message
        cmInfo3.SetMultiBand(0x05);                      //0x01
        cmInfo3.SetA54(1);                               //0x01
        cmInfo3.SetA55(0);                               //0x01
        cmInfo3.SetA56(0);                               //0x01
        cmInfo3.SetA57(1);                               //0x01
        cmInfo3.SetRadioCap1(0x04);   
        cmInfo3.SetRadioCap2(0x08);
        cmInfo3.SetMultiSlotClass(0x07);
        cmInfo3.SetRGSMCap(0x06);
        cmInfo3.SetSMValue(0x09); 
        cmInfo3.SetSMSValue(0x02);
        cmInfo3.SetUCS2Treat(1);
        cmInfo3.SetExtMeasCap(0);
        cmInfo3.SetMSConGPS(1);
        cmInfo3.SetMSBasedGPS(0); 
        cmInfo3.SetMSAssistedGPS(1);
        cmInfo3.SetMSBasedEOTD(0);
        cmInfo3.SetMSAssistedEOTD(1);
        
        cmUpdt.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, &cmInfo3); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cmUpdt) != ITS_SUCCESS)
        {
            cout << "Error encoding Classmark Update." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Classmark Update." << endl;
            return;
        }

       PrintBSSMAPMsgClassmarkUpdate(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.30 Cipher Mode Command ---------- */
    if (Cmd("ENCCMCMD", "Encode CipherModeCommand"))
    {
        BSSAP_EncryptionInformation     encInfo;  
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_CipherRspMode             crMd;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CipherModeCommand cmCmd;

        
        // populate Encryption Information, add it to the message
        encInfo.SetNoEncryption(0); 
        encInfo.SetA5_1(1);
        encInfo.SetA5_2(0);
        encInfo.SetA5_3(1);
        encInfo.SetA5_4(0);
        encInfo.SetA5_5(1);
        encInfo.SetA5_6(0);
        encInfo.SetA5_7(1);
        encInfo.SetKey(key, sizeof(key));                     

        cmCmd.AddIE(BSSAP_IEI_ENCRYPTION_INFORMATION, &encInfo);


        // populate Layer 3 Header Information, add it to the message
        l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        l3hInfo.SetTIVal(7);
        l3hInfo.SetTIFlag(1);
        
        cmCmd.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);
        

        // populate Cipher Response Mode, add it to the message
        crMd.SetCipherRspMode(CRM_IMEISV_INLCUDED);        //0x01
        
        cmCmd.AddIE(BSSAP_IEI_CIPHER_RESPONSE_MODE, &crMd);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cmCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding CipherModeCommand." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

	// Message injected for testing
//        ITS_OCTET inject[] = {0x00, 0x0f, 0x53, 0x0a, 0x06, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
//                              0x07, 0x02, 0x03, 0x0f, 0x23, 0x01};
  
//        DumpData(inject, sizeof(inject));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CipherModeCommand." << endl;
            return;
        }

        PrintBSSMAPMsgCipherModeCmd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.31 Cipher Mode Complete ---------- */
    if (Cmd("ENCCMCPLT", "Encode CipherModeComplete"))
    {
        BSSAP_L3MsgCnt                  l3mc;
        BSSAP_ChsEncAlg                 ceAlg;
     
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CipherModeComplete cmCplt;

        // populate Layer 3 Messge Contents, add it to the message
        l3mc.SetL3MsgCnt(key, sizeof(key));       

        cmCplt.AddIE(BSSAP_IEI_LAYER3_MESSAGE_CONTENT, &l3mc);

        
        // populate Chosen Encryption Algorithm, add it to the message
        ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03

        cmCplt.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cmCplt) != ITS_SUCCESS)
        {
            cout << "Error encoding CipherModeComplete." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CipherModeComplete." << endl;
            return;
        }

        PrintBSSMAPMsgCipherModeComplete(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.32 Complete Layer3 Information ---------- */
    if (Cmd("ENCCL3I", "Encode CompleteLayer3Information"))
    {
        BSSAP_CellID                    cellId;
        BSSAP_L3Info                    l3Info;
        BSSAP_LsaIdList                 lidList;

        BSSAP_LSAIdentifier lid = {0};

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CompleteLayer3Information cl3i;

        
        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        cl3i.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Layer 3 Information, add it to the message
        l3Info.SetL3Info(key, sizeof(key));                      
        
        cl3i.AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);

        // populate LSA Identifier List, add it to the message
        lidList.SetEscapePLMN(0x01); 
        
        LSAID_SET_LSA_ID_BIT_1(lid,0x01);
        LSAID_SET_LSA_ID(lid,0x432110);

        lidList.SetLSAID(lid, 0);
        lidList.SetLSAID(lid, 1);
        
        cl3i.AddIE(BSSAP_IEI_LSA_IDENTIFIER_LIST, &lidList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cl3i) != ITS_SUCCESS)
        {
            cout << "Error encoding Complete Layer3 Information." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Complete Layer3 Information." << endl;
            return;
        }

        PrintBSSMAPMsgCompleteLayer3Info(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.33 Queueing Indication ---------- */
    if (Cmd("ENCQIND", "Encode QueueingIndication"))
    {
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_QueueingIndication qInd;

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &qInd) != ITS_SUCCESS)
        {
            cout << "Error encoding QueueingIndication." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Queueing Indication." << endl;
            return;
        }

        PrintBSSMAPMsgQueuingInd(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.34 SAPI n REJECT ---------- */
    if (Cmd("ENCSNREJ", "Encode SAPInREJECT"))
    {
        BSSAP_dlci                      dlci;
        BSSAP_Cse                       cs;     
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_SAPInReject snRej;


        // populate DLCI, add it to the message
        dlci.SetCtrlChan(DLCI_FACCH_OR_SDCCH);            //0x02U
        dlci.SetSAPI(DLCI_SAPI_SHORT_MSG_SVS);            //0x03U

        snRej.AddIE(BSSAP_IEI_DLCI, &dlci); 
        
        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        snRej.AddIE(BSSAP_IEI_CAUSE, &cs); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &snRej) != ITS_SUCCESS)
        {
            cout << "Error encoding SAPInREJECT." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding SAPInREJECT." << endl;
            return;
        }

        PrintBSSMAPMsgSAPInRej(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.37 Handover Required Reject ---------- */
    if (Cmd("ENCHRREJ", "Encode HandoverRequiredReject"))
    {
        BSSAP_Cse                       cs; 
             
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverRequiredReject hrRej;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        hrRej.AddIE(BSSAP_IEI_CAUSE, &cs); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &hrRej) != ITS_SUCCESS)
        {
            cout << "Error encoding HandoverRequiredReject." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding HandoverRequiredReject." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverRequiredRej(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.38 Reset Circuit ---------- */
    if (Cmd("ENCRCKT", "Encode ResetCircuit"))
    {
        BSSAP_CktIDCode                 cktId;
        BSSAP_Cse                       cs;
     
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ResetCircuit rCkt;


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        rCkt.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        rCkt.AddIE(BSSAP_IEI_CAUSE, &cs); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rCkt) != ITS_SUCCESS)
        {
            cout << "Error encoding ResetCircuit." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);


        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding ResetCircuit." << endl;
            return;
        }

        PrintBSSMAPMsgResetCircuit(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.39 Reset Circuit Acknowledge ---------- */
    if (Cmd("ENCRCACK", "Encode ResetCircuitAcknowledget"))
    {
        BSSAP_CktIDCode                 cktId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ResetCircuitAcknowledge rcAck;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        rcAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rcAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Reset Circuit Acknowledge." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Reset Circuit Acknowledge." << endl;
            return;
        }

        PrintBSSMAPMsgResetCircuitAck(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.40 Handover Detect ---------- */
    if (Cmd("ENCHANDDET", "Encode HandoverDetect"))
    {
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverDetect handDet;

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &handDet) != ITS_SUCCESS)
        {
            cout << "Error encoding HandoverDetect." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding HandoverDetect." << endl;
            return;
        }

        PrintBSSMAPMsgHandoverDetect(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.41 Circuit Group Block ---------- */
    if (Cmd("ENCCGBLK", "Encode CircuitGroupBlock"))
    {
        BSSAP_Cse                      cs;
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList; 
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupBlock cgBlk;


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        cgBlk.AddIE(BSSAP_IEI_CAUSE, &cs); 


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        cgBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Circuit Identity Code List, add it to the message
        cicList.SetRange(20); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data

        cgBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cgBlk) != ITS_SUCCESS)
        {
            cout << "Error encoding Circuit Group Block." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Circuit Group Block." << endl;
            return;
        }

       PrintBSSMAPMsgCktGroupBlock(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.42 Circuit Group Blocking Acknowledge ---------- */
    if (Cmd("ENCCGBA", "Encode CircuitGroupBlockAcknowledge"))
    {  
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList; 

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupBlockAcknowledge cgba;


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x11

        cgba.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        // populate Circuit Identity Code, add it to the message

        cicList.SetRange(255); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data

        cgba.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cgba) != ITS_SUCCESS)
        {
            cout << "Error encoding Parameter CircuitGroupBlockAck." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Circuit Group Blocking Ack." << endl;
            return;
        }

        PrintBSSMAPMsgCktGroupBlockAck(dec);
    }
    /*----------------------------------------------------------------------*/


    /* ---------- 3.2.1.43 Circuit Group Unblock ---------- */
    if (Cmd("ENCCGUNBLK", "Encode CircuitGroupUnblock"))
    {  
        BSSAP_Cse            cs;
        BSSAP_CktIDCode      cktId;
        BSSAP_CktIDCodeList  cicList; 
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupUnblock cgUnblk;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
        //cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        cgUnblk.AddIE(BSSAP_IEI_CAUSE, &cs); 

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        cgUnblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        // populate Circuit Identity Code List, add it to the message
        cicList.SetRange(8); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

        //cicList.SetStatus(status, sizeof(status));    // 9 data

        cgUnblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cgUnblk) != ITS_SUCCESS)
        {
            cout << "Error encoding Circuit Group Unblock." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        //ITS_OCTET inject[] = { 0x00, 0x07, 0x46, 0x01, 0x45, 0x11, 0x1e, 0x01,
        //                         0x08 };
/*        ITS_OCTET inject[] = { 0x00, 0x2e, 0x46, 0x01, 0x45, 0x11, 0x1e, 0x28,
                               0x0a, 0x55, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

        DumpData(inject, sizeof(inject));
*/
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CircuitGroupUnblock." << endl;
            return;
        }

        PrintBSSMAPMsgCktGroupUnblock(dec);
    }

    /*-----------------------------------------------------------------*/

    /* ---------- 3.2.1.44 Circuit Group Unblock Ack ---------- */
    if (Cmd("ENCCGUA", "Encode CircuitGroupUnblockAck"))
    { 
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupUnblockAck cgua;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        cgua.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Circuit Identity Code List, add it to the message
        cicList.SetRange(2); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data

        cgua.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cgua) != ITS_SUCCESS)
        {
            cout << "Error encoding Circuit Group Unblock Ack." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Circuit Group Unblock Ack." << endl;
            return;
        }

       PrintBSSMAPMsgCktGroupUnblockAck(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.45 Confusion ---------- */
    if (Cmd("ENCCNF", "Encode Confusion"))
    { 
        BSSAP_Cse                      cs;
        BSSAP_Diagn                    diag;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Confusion cnf;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        cnf.AddIE(BSSAP_IEI_CAUSE, &cs); 


        // populate Diagnostics, add it to the message
        diag.SetErrPtr(DIAG_ERRONEOUS_OCTET_1);         //0x01
        diag.SetBitPtr(DIAG_ERROR_BIT_POSITION_2);
        diag.SetMsgRcvd(key1, 9);
     
        cnf.AddIE(BSSAP_IEI_DIAGNOSTICS, &diag); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cnf) != ITS_SUCCESS)
        {
            cout << "Error encoding Confusion." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Confusion." << endl;
            return;
        }

        PrintBSSMAPMsgConfusion(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.46 Classmark Request ---------- */
    if (Cmd("ENCCMREQ", "Encode ClassmarkRequest"))
    { 
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ClassmarkRequest cmReq;

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cmReq) != ITS_SUCCESS)
        {
            cout << "Error encoding Classmark Request." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Classmark Request." << endl;
            return;
        }

        PrintBSSMAPMsgClassmarkReq(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.47 Unequipped Circuit ---------- */
    if (Cmd("ENCUNCKT", "Encode UnequippedCircuit"))
    { 
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UnequippedCircuit unCkt;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        unCkt.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Circuit Identity Code List, add it to the message 
        cicList.SetRange(2); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data
        
        unCkt.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &unCkt) != ITS_SUCCESS)
        {
            cout << "Error encoding Unequipped Circuit." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Unequipped Circuit." << endl;
            return;
        }

        PrintBSSMAPMsgUnequippedCkt(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.48 Cipher Mode Reject ---------- */
    if (Cmd("ENCCMREJ", "Encode CipherModeReject"))
    { 
        BSSAP_Cse                     cs;
 
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CipherModeReject cmRej;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        cmRej.AddIE(BSSAP_IEI_CAUSE, &cs);   
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cmRej) != ITS_SUCCESS)
        {
            cout << "Error encoding Cipher Mode Reject." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Cipher Mode Reject." << endl;
            return;
        }

        PrintBSSMAPMsgCipherModeRej(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.49 Load Indication ---------- */
    if (Cmd("ENCLDIND", "Encode LoadIndication"))
    { 
        BSSAP_TimeInd                   tmInd;
        BSSAP_CellID                    cellId;
        BSSAP_CellIDList                ciList;
        BSSAP_ResSituation              resStn;
        BSSAP_Cse                       cs;
         
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_LoadIndication ldInd;

        // populate Time Indication, add it to the message
        tmInd.SetTime(octet);                               //0x04 

        ldInd.AddIE(BSSAP_IEI_TIME_INDICATION, &tmInd);  


        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi  
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);
        cellId.SetCellID(cid);

        ldInd.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Cell Identifier List, add it to the message
        ciList.SetCellIDListDisc(CI_CID_CGI);
        //cgi
        CIL_CGI_SET_MCC_PCS(cid1,ushort);
        CIL_CGI_SET_MNC_PCS(cid1,octet);
        CIL_CGI_SET_LAC(cid1,ushort);
        CIL_CGI_SET_CI(cid1,ushort);
//        ciList.AddCellID(cid1);
        for (i = 0; i < 1; i++)
        {
            ciList.SetCellID(cid1, i);
        }

        ldInd.AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        ldInd.AddIE(BSSAP_IEI_CAUSE, &cs);   
        

        // populate Resource Situation, add it to the message
        RS_SET_CHANNEL_TYPE(rse, RS_CHANNEL_TYPE_SDCCH);
        RS_SET_RADIO_INT_BAND_IND(rse, RS_RIBI_INTERFERENCE_BAND_2);
        RS_SET_EXTENSION_BIT(rse, isExt);

        RS_SET_NUMBER_OF_CHANNEL_BASE_VALUE(rse, 0x03);

        if (RS_GET_EXTENSION_BIT(rse)) //two Octets
        {
            RS_SET_NUMBER_OF_CHANNEL_EXT_VALUE(rse, 0x05);
        }
        for (int i = 0; i < 5; i++)
        {
            resStn.SetResSitnElmnt(rse, i);
        }

        ldInd.AddIE(BSSAP_IEI_RESOURCE_SITUATION, &resStn);  

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &ldInd) != ITS_SUCCESS)
        {
            cout << "Error encoding Load Indication." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Load Indication." << endl;
            return;
        }

        PrintBSSMAPMsgLoadInd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.50 VGCS/VBS Setup ---------- */
    if (Cmd("ENCVVSETUP", "Encode VGCSVBSSetup"))
    { 
        BSSAP_GrpClRef                  gcRef;
        BSSAP_Prio                      prio;
                

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_VGCSVBSSetup vvs;

        // populate Priority, add it to the message
        prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
        prio.SetQA(P_QUEUING_ALLOWED);                      //1
        prio.SetPVI(0x01);                                      
        prio.SetPCI(P_NO_PREEMPTION );                      //0 

        vvs.AddIE(BSSAP_IEI_PRIORITY, &prio);               


        // populate Group Call Reference, add it to the message
        gcRef.SetCallRef(uint);
        gcRef.SetClPrio(GCR_CALL_PRIORITY_LEVEL_B);         //0x06
        gcRef.SetAF(GCR_AF_ACK_REQUIRED);                   //0x01
        gcRef.SetSF(GCR_SF_VBS);                            //0x00
        gcRef.SetCiphInfo(GCR_CIPHERING_KEY_9);             //0x09;

        vvs.AddIE(BSSAP_IEI_GROUP_CALL_REFERENCE, &gcRef);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &vvs) != ITS_SUCCESS)
        {
            cout << "Error encoding VGCS/VBS Setup." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding VGCS/VBS Setup." << endl;
            return;
        }

        PrintBSSMAPMsgVGCSVBSSetup(dec);    
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.51 VGCS/VBS Setup Ack ---------- */
    if (Cmd("ENCVVSA", "Encode VGCSVBSSetupAck"))
    {
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_VGCSVBSSetupAck vvsa;

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &vvsa) != ITS_SUCCESS)
        {
            cout << "Error encoding VGCS/VBS Setup Ack." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding VGCS/VBS Setup Ack." << endl;
            return;
        }

        PrintBSSMAPMsgVGCSVBSSetupAck(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.52 VGCS/VBS Setup Refuse ---------- */
    if (Cmd("ENCVVSR", "Encode VGCSVBSSetupRefuse"))
    { 
        BSSAP_Cse                     cs;        
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_VGCSVBSSetupRefuse vvsr;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        vvsr.AddIE(BSSAP_IEI_CAUSE, &cs);          

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &vvsr) != ITS_SUCCESS)
        {
            cout << "Error encoding VGCS/VBS Setup Refuse." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding VGCS/VBS Setup Refuse." << endl;
            return;
        }

        PrintBSSMAPMsgVGCSVBSSetupRefuse(dec);                   
    }
    /*--------------------------------------------------------------*/

    /* ------------ 3.2.1.53 VGCS/VBS Assignment Request ------------------ */
    if (Cmd("ENCVVAR", "Encode VGCSVBSAssignmentRequest"))
    {  
        BSSAP_ChanType                  chanType;
        BSSAP_AssReq                    assReq;
        BSSAP_CellID                    cellId;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_EncryptionInformation     encInfo;
                                

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_VGCSVBSAssignmentRequest vvar;


        // populate Channel Type, add it to the message     
        chanType.SetSpeechDataID(CT_DATA);                           //0x02
        chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);  //0x08
        // Add more here...

        vvar.AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);


        // populate Assignment Requirement, add it to the message     
        assReq.SetAssReq(AR_IMMEDIATE);                      //0x01

        vvar.AddIE(BSSAP_IEI_ASSIGNMENT_REQUIREMENT, &assReq);

        
        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi  
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);
        cellId.SetCellID(cid);

        vvar.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Group Call Reference, add it to the message.
        gcRef.SetCallRef(uint);
        gcRef.SetClPrio(GCR_CALL_PRIORITY_LEVEL_B);         //0x06
        gcRef.SetAF(GCR_AF_ACK_REQUIRED);                   //0x01
        gcRef.SetSF(GCR_SF_VBS);                            //0x00
        gcRef.SetCiphInfo(GCR_CIPHERING_KEY_9);             //0x09;

        vvar.AddIE(BSSAP_IEI_GROUP_CALL_REFERENCE, &gcRef);


        // populate Priority, add it to the message
        prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
        prio.SetQA(P_QUEUING_ALLOWED);                      //1
        prio.SetPVI(1);                 
        prio.SetPCI(P_NO_PREEMPTION );                      //0 

        vvar.AddIE(BSSAP_IEI_PRIORITY, &prio);   
        

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        vvar.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        
        // populate Downlink DTX Flag, add it to the message
        dlFlag.SetDTXFlag(DLDTX_ACTIVATE_ALLOWED);          //0x00
        
        vvar.AddIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, &dlFlag);   
        

        // populate Encryption Information, add it to the message
//        encInfo.SetPermitAlg(EI_GSM_A5_1);                  //0x02
        encInfo.SetKey(key, sizeof(key));                     

        vvar.AddIE(BSSAP_IEI_ENCRYPTION_INFORMATION, &encInfo);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &vvar) != ITS_SUCCESS)
        {
            cout << "Error encoding VGCS/VBS Assignment Request." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding VGCS/VBS Assignment Request." << endl;
            return;
        }

        PrintBSSMAPMsgVGCSVBSAssignReq(dec);
    }
    /*----------------------------------------------------------------------*/

    /* ---------- 3.2.1.54 VGCS/VBS Assignment Result ---------- */
    if (Cmd("ENCVVASR", "Encode VGCSVBSAssignmentResult"))
    { 
        BSSAP_ChanType                  chanType;
        BSSAP_CellID                    cellId;
        BSSAP_ChsChan                   chsChan;
        BSSAP_CktIDCode                 cktId;
        BSSAP_CktPool                   cktPl;

        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_VGCSVBSAssignmentResult vvasr;

        
        // populate Channel Type, add it to the message      
        chanType.SetSpeechDataID(CT_DATA);                             //0x02
        chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);    //0x08
/*        
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 0);      //0x01
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 1);      //0x11
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 2);      //0x21
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 3);      //0x01
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 4);      //0x11
        chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 5);      //0x21
*/
        chanType.SetDataTransp(1, CT_DATA_MAX_ALLOWED_CHANNEL1, 1);    //0x20
        chanType.SetIFDateRate(1, 0x53);                               //0x53
        chanType.SetAsymInd(0, 0x02);                                  //0x02
        
        vvasr.AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);

       
        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi  
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);
        cellId.SetCellID(cid);

        vvasr.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);  
  

        // populate Chosen Channel, add it to the message
        chsChan.SetChan(CC_CH_SPEECH);                      //0x09
        chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01 
        
        vvasr.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        vvasr.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Circuit Pool, add it to the message
        cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

        vvasr.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);
               
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &vvasr) != ITS_SUCCESS)
        {
            cout << "Error encoding VGCS/VBS Assignment Result." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding VGCS/VBS Assignment Result." << endl;
            return;
        }

        PrintBSSMAPMsgVGCSVBSAssignRsult(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.55 VGCS/VBS Assignment Failure ---------- */
    if (Cmd("ENCVVAF", "Encode VGCSVBSAssignmentFailure"))
    { 
        BSSAP_Cse                       cs;
        BSSAP_CktPool                   cktPl;
        BSSAP_CktPoolList               cpList;
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_VGCSVBSAssignmentFailure vvaf;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        vvaf.AddIE(BSSAP_IEI_CAUSE, &cs);   

        // populate Circuit Pool, add it to the message
        cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

        vvaf.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);  

     
        // populate Circuit Pool List, add it to the message
        CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
//        cpList.AddCircuitPoolNo(cpool);
        for (i = 0; i < 2; i++)
        {
            cpList.SetCircuitPoolNo(cpool, i);
        }

        vvaf.AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &vvaf) != ITS_SUCCESS)
        {
            cout << "Error encoding VGCS/VBS Assignment Failure." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding VGCS/VBS Assignment Failure." << endl;
            return;
        }

        PrintBSSMAPMsgVGCSVBSAssignFailure(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.56 Soft VGCS/VBS Queuing Indication ---------- */
    if (Cmd("ENCVVQI", "Encode VGCSVBSQueuingIndication"))
    { 
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_VGCSVBSQueuingIndication vvqi;

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &vvqi) != ITS_SUCCESS)
        {
            cout << "Error encoding  VGCS/VBS Queuing Indication." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding  VGCS/VBS Queuing Indication." << endl;
            return;
        }

        PrintBSSMAPMsgVGCSVBSQueuingInd(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.57 Uplink Request ---------- */
    if (Cmd("ENCUPLKREQ", "Encode UplinkRequest"))
    { 
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UplinkRequest uplkReq;
       
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &uplkReq) != ITS_SUCCESS)
        {
            cout << "Error encoding Uplink Request." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Uplink Request." << endl;
            return;
        }

        PrintBSSMAPMsgUplinkReq(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.58 Uplink Request Acknowledge ---------- */
    if (Cmd("ENCURACK", "Encode UplinkRequestAcknowledge"))
    { 
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UplinkRequestAcknowledge urAck;
       
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &urAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Uplink Request Acknowledge." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Uplink Request Acknowledge." << endl;
            return;
        }

        PrintBSSMAPMsgUplinkReqAck(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.59 Uplink Request Confirmation ---------- */
    if (Cmd("ENCURCFM", "Encode UplinkRequestConfirmation"))
    { 
        BSSAP_CellID                    cellId;
        BSSAP_L3Info                    l3Info;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UplinkRequestConfirmation urCfm;


        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        urCfm.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Layer 3 Information, add it to the message
        l3Info.SetL3Info(key1, 9);                      
        
        urCfm.AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &urCfm) != ITS_SUCCESS)
        {
            cout << "Error encoding Uplink Request Confirmation." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Uplink Request Confirmation." << endl;
            return;
        }

        PrintBSSMAPMsgUplinkReqConfirm(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.60 Uplink Release Indication ---------- */
    if (Cmd("ENCURIND", "Encode UplinkReleaseIndication"))
    { 
        BSSAP_Cse                   cs;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UplinkReleaseIndication urInd;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        urInd.AddIE(BSSAP_IEI_CAUSE, &cs);    

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &urInd) != ITS_SUCCESS)
        {
            cout << "Error encoding Uplink Release Indication." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Uplink Release Indication." << endl;
            return;
        }

        PrintBSSMAPMsgUplinkReleaseInd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.61 Uplink Reject Command ---------- */
    if (Cmd("ENCURCMD", "Encode UplinkRejectCommand"))
    { 
        BSSAP_Cse                 cs;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UplinkRejectCommand  urCmd;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        urCmd.AddIE(BSSAP_IEI_CAUSE, &cs);    
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &urCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding Uplink Reject Command." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding UplinkRejectCommand." << endl;
            return;
        }

        PrintBSSMAPMsgUplinkRejCmd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.62 Uplink Release Command ---------- */
    if (Cmd("ENCURLCMD", "Encode UplinkReleaseCommand"))
    { 
        BSSAP_Cse                 cs;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UplinkReleaseCommand  urlCmd;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        urlCmd.AddIE(BSSAP_IEI_CAUSE, &cs);    
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &urlCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding Uplink Release Command." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding UplinkReleaseCommand." << endl;
            return;
        }

        PrintBSSMAPMsgUplinkReleaseCmd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.63 Uplink Seized Command ---------- */
    if (Cmd("ENCUSCMD", "Encode UplinkSeizedCommand"))
    { 
        BSSAP_Cse                 cs;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_UplinkSeizedCommand  usCmd;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        usCmd.AddIE(BSSAP_IEI_CAUSE, &cs);    
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &usCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding Uplink Seized Command." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding UplinkSeizedCommand." << endl;
            return;
        }

        PrintBSSMAPMsgUplinkSeizedCmd(dec);
    }
    /*--------------------------------------------------------------*/

    /* ------------- 3.2.1.64 Suspend ------------------ */
    if (Cmd("ENCSSPND", "Encode Suspend"))
    {  
        BSSAP_dlci                      dlci;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Suspend suspend;

        // populate DLCI, add it to the message
        dlci.SetCtrlChan(DLCI_FACCH_OR_SDCCH);            //0x02U
        dlci.SetSAPI(DLCI_SAPI_SHORT_MSG_SVS);            //0x03U

        suspend.AddIE(BSSAP_IEI_DLCI, &dlci); 
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &suspend) != ITS_SUCCESS)
        {
            cout << "Error encoding Suspend." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Suspend." << endl;
            return;
        }

        PrintBSSMAPMsgSuspend(dec);
    }
    /*--------------------------------------------------------------*/

    /* ------------- 3.2.1.65 Resume ------------------ */
    if (Cmd("ENCRSM", "Encode Resume"))
    {  
        BSSAP_dlci                       dlci;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Resume rsm;
        
        // populate DLCI, add it to the message
        dlci.SetCtrlChan(DLCI_FACCH_OR_SDCCH);            //0x02U
        dlci.SetSAPI(DLCI_SAPI_SHORT_MSG_SVS);            //0x03U

        rsm.AddIE(BSSAP_IEI_DLCI, &dlci); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &rsm) != ITS_SUCCESS)
        {
            cout << "Error encoding Resume." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Resume." << endl;
            return;
        }

        PrintBSSMAPMsgResume(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.66 Change Circuit ---------- */
    if (Cmd("ENCCHGCKT", "Encode ChangeCircuit"))
    { 
        BSSAP_Cse                 cs; 

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ChangeCircuit chgCkt;

        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        chgCkt.AddIE(BSSAP_IEI_CAUSE, &cs); 

        
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &chgCkt) != ITS_SUCCESS)
        {
            cout << "Error encoding Change Circuit." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Change Circuit." << endl;
            return;
        }

        PrintBSSMAPMsgChangeCkt(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.67 Change Circuit Acknowledge ---------- */
    if (Cmd("ENCCCACK", "Encode ChangeCircuitAcknowledge"))
    { 
        BSSAP_CktIDCode           cktId;
      
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ChangeCircuitAcknowledge ccAck;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(0x229);                             //0x229
        cktId.SetTimeslot(octet);                          //0x11

        ccAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &ccAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Change Circuit Acknowledge." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Change Circuit." << endl;
            return;
        }

        PrintBSSMAPMsgChangeCktAck(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.68 CommonID ---------- */
    if (Cmd("ENCCOMID", "Encode Common ID"))
    { 
        BSSAP_IMSI                      imsi;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CommonID comid;

        // populate IMSI, add it to the message
        //imsi.SetDigits(digits, strlen(digits));              //7260686
        imsi.SetDigitsB(mindig, 4);

        comid.AddIE(BSSAP_IEI_IMSI, &imsi);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &comid) != ITS_SUCCESS)
        {
            cout << "Error encoding CommonID." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);
/*
        ITS_OCTET inject[] = { 0x00, 0x17, 0x2f, 0x08, 0x14, 0x12, 0x34, 0x56,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
        DumpData(inject, sizeof(inject));
*/
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CommonID." << endl;
            return;
        }

        PrintBSSMAPMsgCommonID(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.69 LSA Information ---------- */
    if (Cmd("ENCLSAINFO", "Encode LSA Information"))
    { 
        BSSAP_LsaInfo                      lsai;
        
        BSSAP_LSA  lsa = {0};

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_LSAInformation lsaInfo;

        // populate LSA Information, add it to the message
        lsai.SetLSAIndicator(0x01);                             // 0x01

        LSAI_SET_LSA_ID_PRIORITY(lsa,0x04);
        LSAI_SET_LSA_ID_PREF(lsa,0x01);
        LSAI_SET_LSA_ID_ACT(lsa,0x01);

        LSAI_SET_LSA_ID_BIT_1(lsa,0x01);
        LSAI_SET_LSA_ID(lsa,0x432100);              //0x432100

        lsai.SetLSAID(lsa, 0);
        lsai.SetLSAID(lsa, 1);
        lsai.SetLSAID(lsa, 2);


        lsaInfo.AddIE(BSSAP_IEI_LSA_INFORMATION, &lsai);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &lsaInfo) != ITS_SUCCESS)
        {
            cout << "Error encoding LSA Information." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding LSA Information." << endl;
            return;
        }

        PrintBSSMAPMsgLSAInfo(dec);

    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.70 Connection Oriented Information ---------- */
    if (Cmd("ENCCOINFO", "Encode Conn Oriented Info"))
    { 
        BSSAP_Apdu                apdu;   // Mandatory
        BSSAP_Segment             seg;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ConnectionOrientedInformation coi;

        // populate APDU, add it to the message
        apdu.SetProtocolID(APDU_PROT_LLP);             //0x02
        apdu.SetEmbededMsg(key, sizeof(key));

        coi.AddIE(BSSAP_IEI_APDU, &apdu);

        // populate Segmentation, add it to the message

        seg.SetSegmentNum(0x03);
        seg.SetSegmentBit(0x01);

        seg.SetMessageID(0x228);
        
        coi.AddIE(BSSAP_IEI_SEGMENTATION, &seg);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &coi) != ITS_SUCCESS)
        {
            cout << "Error encoding Connection Oriented Information." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Connection Oriented Information." << endl;
            return;
        }

        PrintBSSMAPMsgConnOrientInfo(dec);
    }
    /*--------------------------------------------------------------*/


    /* ---------- 3.2.1.71 Perform Location Request ---------- */
    if (Cmd("ENCPLREQ", "Encode Perform Location Request"))
    { 
        BSSAP_LocType                   locType; //mandatory
        BSSAP_CellID                    cellId;
        BSSAP_ClassmarkInfo3            cmInfo3;
        BSSAP_ClientType                lcType;
        BSSAP_ChsChan                   chsChan; 
        BSSAP_LcsQoS                    lcsq;
        BSSAP_GPSAssistData             gadata;
        BSSAP_Apdu                      apdu;
        BSSAP_LCSPrio                   lcsp;

        BSSAP_SATID_IODE id = {0};

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_PerformLocationRequest plr;

        // populate Location Type, add it to the message
//        locType.SetLocInfo(LT_LI_LOC_IFNO_FOR_MS);             //0x01
        locType.SetLocInfo(LT_LI_CRRT_GEO_LOC);   //0x00, set this value, locType 
                                                  //will not be included, even it 
                                                  // is set up                                                      
        locType.SetPosMethod(LT_PM_ASSISTED_GPS);              //0x03

        plr.AddIE(BSSAP_IEI_LOCATION_TYPE, &locType);

        // populate Cell Identifier, add it to the message
        
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi  
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);
        cellId.SetCellID(cid);
        
        plr.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

        // populate Classmark Information3, add it to the message
        cmInfo3.SetMultiBand(0x05);                      //0x01
        cmInfo3.SetA54(1);                               //0x01
        cmInfo3.SetA55(0);                               //0x01
        cmInfo3.SetA56(0);                               //0x01
        cmInfo3.SetA57(1);                               //0x01
        cmInfo3.SetRadioCap1(0x04);   
        cmInfo3.SetRadioCap2(0x08);
        cmInfo3.SetMultiSlotClass(0x07);
        cmInfo3.SetRGSMCap(0x06);
        cmInfo3.SetSMValue(0x09); 
        cmInfo3.SetSMSValue(0x02);
        cmInfo3.SetUCS2Treat(1);
        cmInfo3.SetExtMeasCap(0);
        cmInfo3.SetMSConGPS(1);
        cmInfo3.SetMSBasedGPS(0); 
        cmInfo3.SetMSAssistedGPS(1);
        cmInfo3.SetMSBasedEOTD(0);
        cmInfo3.SetMSAssistedEOTD(1);
        
        plr.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, &cmInfo3);

        // populate LCS Client Type, add it to the message
        lcType.SetClientSubtype(0x01);                //0x01
        lcType.SetClientCategory(0x03);               //0x03

        plr.AddIE(BSSAP_IEI_LCS_CLIENT_TYPE, &lcType);
      
        // populate Chosen Channel, add it to the message
        chsChan.SetChan(CC_CH_SPEECH);                      //0x09
        chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01 
        
        plr.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);

        // populate LCS Priority, add it to the message
        lcsp.SetPriority(prio);             
     
        plr.AddIE(BSSAP_IEI_LCS_PRIORITY, &lcsp);

        // populate LCS QoS, add it to the message

        lcsq.SetVERT(0x01);
        lcsq.SetHA(0x01);
        lcsq.SetHorizAccuracy(0x04);
        lcsq.SetVA(0x01);
        lcsq.SetVertAccuracy(0x04);
        lcsq.SetRspTime(LQ_RT_DELAY_TOLERANT);        //0x02
        
        plr.AddIE(BSSAP_IEI_LCS_QOS, &lcsq);

        // populate GPS Assistance Data, add it to the message
        gadata.SetAlmanc(0x01);             
        gadata.SetUTCModel(0x00);
        gadata.SetIonosphericModel(0x01);             
        gadata.SetNavigationModel(0x00);
        gadata.SetDGPSCorrections(0x01);             
        gadata.SetRefLocation(0x00);
        gadata.SetRefTime(0x01);             
        gadata.SetAcquitionAssistance(0x00);
        gadata.SetRealTimeIntegrity(0x01);
        gadata.SetGPSWeek(0x228);

        gadata.SetGPSToe(0x09);
        gadata.SetToeLimit(0x04);
        gadata.SetNSAT(0x05);

        GAD_SET_SAT_ID(id,0x01);
        GAD_SET_IODE(id,0x01);
        
        gadata.SetSatid_Iode(id, 0);
        gadata.SetSatid_Iode(id, 1);

        plr.AddIE(BSSAP_IEI_GPS_ASSISTANCE_DATA, &gadata);

        // populate APDU, add it to the message
/*        apdu.SetProtocolID(APDU_PROT_LLP);             //0x02
        apdu.SetEmbededMsg(key, sizeof(key));

        plr.AddIE(BSSAP_IEI_APDU, &apdu);
*/
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &plr) != ITS_SUCCESS)
        {
            cout << "Error encoding Perform Location Request." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Perform Location Request." << endl;
            return;
        }

        PrintBSSMAPMsgPerformLocReq(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.72 Perform Location Response ---------- */
    if (Cmd("ENCPLRSP", "Encode Perform Location Response"))
    { 
        BSSAP_LocEstimate         locEst;
        BSSAP_DecipherKeys        dKey;
        BSSAP_LCSCse              lCse;
        BSSAP_PositionData        posData;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_PerformLocationResponse plRsp;

        // populate Location Estimate, add it to the message
        locEst.SetLocEstimate(key, sizeof(key));

        plRsp.AddIE(BSSAP_IEI_LOCATION_ESTIMATE, &locEst);

        // populate Positioning Data, add it to the message
        posData.SetPosDataDiscr(0x00);            
        posData.SetPosMthd_Usage(PD_PM_TOA, PD_USAGE_SUCCESS_RESULT_NOT_USED_TO_LOC, 0); //0x01, 0x01
        posData.SetPosMthd_Usage(PD_PM_AOA, PD_USAGE_SUPPORT_METHOD_CASE, 1);         //0x02/ 0x04
      
        plRsp.AddIE(BSSAP_IEI_POSITIONING_DATA, &posData);

        // populate Deciphering Keys, add it to the message

        dKey.SetKeyFlag(0x01);
        dKey.SetCurrentValue(key2);
        dKey.SetNextValue(key2);
        
        plRsp.AddIE(BSSAP_IEI_DECIPHERING_KEYS, &dKey);

        // populate LCS Cause, add it to the message
        lCse.SetCauseValue(LC_CV_CONGESTION);             //0x11
        lCse.SetDiagValue(0x02);

        plRsp.AddIE(BSSAP_IEI_LCS_CAUSE, &lCse);


        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &plRsp) != ITS_SUCCESS)
        {
            cout << "Error encoding Perform Location Response." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Perform Location Response." << endl;
            return;
        }

        PrintBSSMAPMsgPerformLocRsp(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- 3.2.1.73 Perform Location Abort ---------- */
    if (Cmd("ENCPLA", "Encode Perform Location Abort"))
    { 
        BSSAP_LCSCse              lCse;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_PerformLocationAbort pla;

        // populate LCS Cause, add it to the message
//        lCse.SetCauseValue(LC_CV_CONGESTION);             //0x11
        lCse.SetCauseValue(LC_CV_POS_MTHD_FAILURE); // 0x05
        lCse.SetDiagValue(0x02); //will be included when Cause value is 0x05

        pla.AddIE(BSSAP_IEI_LCS_CAUSE, &lCse);
       
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &pla) != ITS_SUCCESS)
        {
            cout << "Error encoding Perform Location Abort." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Perform Location Abort." << endl;
            return;
        }

        PrintBSSMAPMsgPerformLocAbort(dec);
    }
    /*--------------------------------------------------------------*/

    /* ---------- Location Updating Reject             ---------- */
    if (Cmd("LOCUPDATEREJ", "Encode Location Updating Reject"))
    {
        BSSAP_RejectCause  rejCause;
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_LocationUpdatingReject  locUpdateRej;

        locUpdateRej.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        locUpdateRej.SetSkipVal(SKIP_VALUE_0);
                                                                                
        rejCause.SetRejectCause(0x03);
        locUpdateRej.AddIE(BSSAP_IEI_REJECT_CAUSE, &rejCause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &locUpdateRej) != ITS_SUCCESS)
        {
            cout << "Error encoding Location Updating Reject" << endl;
            return;
        }
                                                                                
        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Location Updating Reject" << endl;
            return;
        }
                                                                                
        //PrintBSSMAPMsg......(dec);
    }

    /* ---------- 3.2.1.74 Connectionless Information ---------- */
    if (Cmd("ENCCLINFO", "Encode Connectionless Information"))
    { 
        BSSAP_NetElementID        netId1;  // Mandatory
        BSSAP_NetElementID        netId2;  // Mandatory
        BSSAP_Apdu                apdu;    // Mandatory 
        BSSAP_Segment             seg;     // Conditional  
        BSSAP_ReturnErrCse        rec;     // Conditional
        BSSAP_ReturnErrReq        req;     // Conditional

        BSSAP_NetID  netid = {0};

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ConnectionlessInformation clInfo;

        // populate Network Element Identity, add it to the message
        int disc = -1;

        cout << "Select Discriminator." <<endl;
        cout << "[0] CGI" << endl;
        cout << "[1] LAC_CI" << endl;
        cout << "[2] LAI" << endl;
        cout << "[3] LAC" << endl;
        cout << "-->" << endl;
        cin >> disc;

        if (disc == 0)
        {
            netId1.SetIDDisc(NEI_ID_CGI);  //cgi
            NEI_CGI_SET_MCC(netid,ushort);
            NEI_CGI_SET_MNC(netid,octet);
            NEI_CGI_SET_LAC(netid,ushort);
            NEI_CGI_SET_CI(netid,ushort); 
        }
        else if (disc == 1)
        {
            netId1.SetIDDisc(NEI_ID_LAC_CI);             //0x01

            // LAC+CI
            NEI_LACCI_SET_LAC(netid,ushort);    
            NEI_LACCI_SET_CI(netid,ushort);            
        }
        else if (disc == 2)
        {
            netId1.SetIDDisc(NEI_ID_LAI);             //0x04

            // LAI -- MCC + MNC + LAC
            NEI_LAI_SET_MCC(netid,ushort);
            NEI_LAI_SET_MNC(netid,octet);
            NEI_LAI_SET_LAC(netid,ushort);
        }
        else if (disc == 3)
        {
            netId1.SetIDDisc(NEI_ID_LAC);             //0x05

            // LAC 
            NEI_LAC_SET_LAC(netid,ushort);
        }

        netId1.SetNetElementID(netid);
        clInfo.AddIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, &netId1);

        netId2.SetIDDisc(NEI_ID_LAI);             //0x04

        // LAI -- MCC + MNC + LAC
        NEI_LAI_SET_MCC(netid,ushort);
        NEI_LAI_SET_MNC(netid,octet);
        NEI_LAI_SET_LAC(netid,ushort);
       
        netId2.SetNetElementID(netid);

        clInfo.AddIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, &netId2);

        // populate APDU, add it to the message
        apdu.SetProtocolID(APDU_PROT_LLP);             //0x02
        apdu.SetEmbededMsg(key, sizeof(key));

        clInfo.AddIE(BSSAP_IEI_APDU, &apdu);

        // populate Segmentation, add it to the message
        seg.SetSegmentNum(0x03);
        seg.SetSegmentBit(0x01);
        seg.SetMessageID(0x228);
        
        clInfo.AddIE(BSSAP_IEI_SEGMENTATION, &seg);

        // populate Return Error Request, add it to the message
        req.SetErrorType(RER_UNSEG_APDU_OR_FIRST_SEG_APDU);          //0x00

        clInfo.AddIE(BSSAP_IEI_RETURN_ERROR_REQUEST, &req);

        // populate Return Error Cause, add it to the message
        rec.SetCauseValue(REC_SYSTEM_FAILURE);          //0x01

        clInfo.AddIE(BSSAP_IEI_RETURN_ERROR_CAUSE, &rec);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &clInfo) != ITS_SUCCESS)
        {
            cout << "Error encoding Connectionless Information." << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        ITS_OCTET inject[] = { 0x00, 0x20, 0x3a, 0x4a, 0x08, 0x00, 0x02, 0xf8,
                               0x07, 0x02, 0x28, 0x02, 0x28, 0x4a, 0x06, 0x04,
                               0x02, 0xf8, 0x07, 0x02, 0x28, 0x49, 0x00, 0x00, 
                               0x4f, 0x03, 
                               0x13, 0x02, 0x28, 0x4d, 0x01, 0x00, 0x4e, 0x01,
                               0x01 };

        DumpData(inject, sizeof(inject));

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Connectionless Information." << endl;
            return;
        }

        PrintBSSMAPMsgConnlessInfo(dec);
    }
    /*--------------------------------------------------------------*/

    if (Cmd("TMSIREALCMP", "Encode TMSI Reallocation Complete"))
    {
        BSSAP_NetElementID        netId1;  // Mandatory
        BSSAP_NetElementID        netId2;  // Mandatory
        BSSAP_Apdu                apdu;    // Mandatory
        BSSAP_ParameterSres psr;        
                                                                                                                    
        // encode/decode buffer
        ITS_OCTET buff[maxSize];
                                                                                                                            
        // message
        BSSAP_TMSIReallocComplete tmsiRelCom;

        tmsiRelCom.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        tmsiRelCom.SetTIVal(TI_VALUE_3);                                //0x03
        tmsiRelCom.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &tmsiRelCom) != ITS_SUCCESS)
        {
            cout << "Error encoding TMSI Reallocation Complete" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding  TMSI Reallocation Complete" << endl;
            return;
        }

        PrintBSSMAPMsgTMSIReallocComplete(dec);
    }      

    if (Cmd("AUTHRESP", "Encode AuthenticationResponse"))
    {
        ITS_OCTET                     parasres[4]={0x88, 0x77, 0x66, 0x44};
        ITS_OCTET                     buff[maxSize];
        BSSAP_ParameterSres           psr;
        BSSAP_AuthenticationResponse  authResp;

        psr.SetParameterSres(parasres);

        authResp.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        authResp.SetSkipVal(SKIP_VALUE_0);
        authResp.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &authResp) != ITS_SUCCESS)
        {
            cout << "Error encoding AuthenticationResponse" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding AuthenticationResponse " << endl;
            return;
        }

        PrintBSSMAPMsgAuthenticationResponse(dec);
    }

    if (Cmd("AUTHREQ", "Encode Authentication Request"))
    {
        ITS_OCTET buff[maxSize] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8,
                                   0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf, 0x10};
        BSSAP_CypheringKeySequence  ckey;
        BSSAP_ParameterRand         rand;

        BSSAP_ParameterSres psr;
        BSSAP_AuthenticationRequest authReq;

        authReq.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        authReq.SetSkipVal(SKIP_VALUE_0);
        authReq.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);
        
        ckey.SetCypheringKeySequence(0x01);
        authReq.AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &ckey);

        rand.SetParameterRand(buff);
        authReq.AddIE(BSSAP_IEI_PARAMETER_RAND, &rand);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &authReq) != ITS_SUCCESS)
        {
            cout << "Error encoding AuthenticationRequest" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding AuthenticationRequest " << endl;
            return;
        }

        PrintBSSMAPMsgAuthenticationRequest(dec);
    }

    if (Cmd("AUTHFAIL", "Encode AuthenticationFailure"))
    {
        ITS_OCTET                     buff[maxSize];
        BSSAP_RejectCause             rejCause;
        BSSAP_AuthFailParameter       authFailPara;
        BSSAP_AuthenticationFailure   authFail;

        authFail.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);       //0x05
        authFail.SetSkipVal(SKIP_VALUE_0);                           
    
        rejCause.SetRejectCause(0x03);
        authFail.AddIE(BSSAP_IEI_REJECT_CAUSE, &rejCause);

        ITS_OCTET data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                             0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e };
        authFailPara.SetAuthFailParameter(data, sizeof(data));
        authFail.AddIE(BSSAP_IEI_AUTH_FAILURE_PARAMETER, &authFailPara);
                                                                            
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &authFail) != ITS_SUCCESS)
        {
            cout << "Error encoding AuthenticationFailure " << endl;
            return;
        }
                                                                                
        // print the user data
        DumpData(buff, len);
                                                                                
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding AuthenticationFailure " << endl;
            return;
        }

        PrintBSSMAPMsgAuthenticationFailure(dec);
    }

    if (Cmd("TMSIREALCMD", "Encode TMSI Reallocation Command"))
    {
        ITS_OCTET             buff[maxSize];
        ITS_OCTET             mcc[] = { 0x12U, 0x34U };
        ITS_OCTET             mnc = 0x56U;
        ITS_OCTET             lac[] = { 0x77U, 0x88U };
        BSSAP_LocationAreaID  locAreaId;
        BSSAP_MobileID        mobId;
        BSSAP_ParameterSres   psr;
        ITS_CHAR              digits[] = {0x01, 0x02, 0x03, 0x04, 0x05};

        // message
        BSSAP_TMSIReallocCommand tRealCmd;
             
        tRealCmd.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        tRealCmd.SetTIVal(TI_VALUE_3);                                //0x03
        tRealCmd.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

        locAreaId.SetLocationAreaIDMCC(mcc);
        locAreaId.SetLocationAreaIDMNC(&mnc);
        locAreaId.SetLocationAreaIDLAC(lac);

        tRealCmd.AddIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, &locAreaId);

        mobId.SetOddEvenInd(MI_ODD_DIGITS);
        mobId.SetTypeIdentity(MI_IMSI);
        //mobId.SetIdenCDig(digits, 5);
        mobId.SetIdenCDig(dgts1, strlen(dgts1));
        tRealCmd.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mobId);                                                                                                                            

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &tRealCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding TMSI Reallocation Command" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);
                                                                                                                            
        // do the decode
        BSSAP_Message *dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding TMSI Reallocation Command " << endl;
            return;
        }
        PrintBSSMAPMsgTMSIReallocCommand(dec);
    }

    if (Cmd("IDENTREQ", "Encode Identity Request"))
    {
        ITS_OCTET buff[maxSize];
        BSSAP_IdentityType idType;
        BSSAP_ParameterSres psr;                                                                                                                            
        // message
        BSSAP_IdentityRequest idReq;
            
        idReq.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        idReq.SetTIVal(TI_VALUE_3);                                //0x03
        idReq.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);
                                                                                                                
        idType.SetIdentityType(0x04);
        idReq.AddIE(BSSAP_IEI_IDENTITY_TYPE, &idType);                                                                                                                            
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &idReq) != ITS_SUCCESS)
        {
            cout << "Error encoding Identity Request" << endl;
            return;
        }
                                                                                                                            
        // print the user data
        DumpData(buff, len);
                                                                                                                            
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Identity Request" << endl;
            return;
        }
                                                                                                                            
        PrintBSSMAPMsgIdentityRequest(dec);
                                                                                                                            
    }

    if (Cmd("IDENTRESP", "Encode Identity Response"))
    {
        ITS_OCTET       buff[maxSize];
        BSSAP_MobileID  mobId;
        char            digits[] = {0x01, 0x02, 0x03, 0x04, 0x05};
        BSSAP_ParameterSres psr;                               

        // message
        BSSAP_IdentityResponse idResp;

        idResp.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        idResp.SetTIVal(TI_VALUE_3);                                //0x03
        idResp.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);
                                         
        mobId.SetOddEvenInd(MI_ODD_DIGITS);
        mobId.SetTypeIdentity(MI_IMSI);
        //mobId.SetIdenCDig(digits, 5);
        mobId.SetIdenCDig(dgts1, strlen(dgts1));
        idResp.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mobId);                                                                                                                           
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &idResp) != ITS_SUCCESS)
        {
            cout << "Error encoding Identity Response" << endl;
            return;
        }
                                                                                                                            
        // print the user data
        DumpData(buff, len);
                                                                                                                            
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Identity Response" << endl;
            return;
        }
                                                                                                                            
        PrintBSSMAPMsgIdentityResponse(dec);
    }

    if (Cmd("CMSERVREQ", "Encode CM Service Request"))
    {
        ITS_OCTET                   buff[maxSize];
        BSSAP_ParameterSres         psr;
        BSSAP_CMServiceType         cmServType;
        BSSAP_CypheringKeySequence  cypKeySeq;
        BSSAP_ClassmarkInfo2        cmInfo2;
        BSSAP_MobileID              mobID;
        BSSAP_PriorityLevel         prio;

        // Message
        BSSAP_CMServiceRequest      cmServReq;

        cmServReq.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);    //0x05
        cmServReq.SetTIVal(TI_VALUE_3);                            //0x03
        cmServReq.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);

        cmServType.SetCMServiceType(0x08);
        cmServReq.AddIE(BSSAP_IEI_CM_SERVICE_TYPE, &cmServType);

        cypKeySeq.SetCypheringKeySequence(0x4);
        cmServReq.AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &cypKeySeq); 

        // populate Classmark Info Type2, add it to the message
        cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
        cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
        cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
        cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
        cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
        cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
        cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
        cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
        cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
        cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
        cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
        cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
        cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
        cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
        cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
        cmInfo2.SetCM3(CIT2_CM3_OPTIONS_SUPPORTED);         //0x01
                                                                                
        cmServReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);

        mobID.SetOddEvenInd(MI_ODD_DIGITS);
        mobID.SetTypeIdentity(MI_IMSI);
        //mobID.SetIdenCDig(digits, 5);
        mobID.SetIdenCDig(dgts1, strlen(dgts1));
        cmServReq.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mobID);

        prio.SetPriority(PRIORITY_LEVEL_2);
        cmServReq.AddIE(BSSAP_IEI_CC_PRIORITY_LEVEL, &prio);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cmServReq) != ITS_SUCCESS)
        {
            cout << "Error encoding CM Service Request" << endl;
            return;
        }

        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CM Service Request" << endl;
            return;
        }

        PrintBSSMAPMsgCMServiceRequest(dec);
    }


    if (Cmd("CMSERVACC", "Encode CM Service Accept"))
    {
        ITS_OCTET              buff[maxSize];
        BSSAP_CMServiceAccept  cmServAcc;                           
        BSSAP_ParameterSres    psr;        

        cmServAcc.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        cmServAcc.SetTIVal(TI_VALUE_3);                                //0x03
        cmServAcc.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);                                                                                                                    
        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cmServAcc) != ITS_SUCCESS)
        {
            cout << "Error encoding CM Service Accept" << endl;
            return;
        }
                                                                                                                            
        // print the user data
        DumpData(buff, len);
                                                                                                                            
        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding CM Service Accept" << endl;
            return;
        }
                                                                                                                            
        PrintBSSMAPMsgCMServiceAccept(dec);
    }
}


int
main(int argc, char **argv)
{
    BSSAP_UnitTest test;

     LICENSE_Load();

//    ITS_Application::SetName("Test2");

//    ITS_GlobalStart(0);

    test.ExecuteCommandsFromStream();

//    ITS_GlobalStop();

    return 0;
}



