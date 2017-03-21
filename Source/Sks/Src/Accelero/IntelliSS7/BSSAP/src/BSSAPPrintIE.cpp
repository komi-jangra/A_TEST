/****************************************************************************
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
 *  ID: $Id: BSSAPPrintIE.cpp,v 1.1.1.1 2007-10-08 11:11:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:43  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:40  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:58  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.2.5  2006/03/29 15:26:22  adutta
 * LOG: Fix fo Issue Id 3327 (sgavalkar)
 * LOG:
 * LOG: Revision 9.1.2.4  2005/11/30 07:30:59  adutta
 * LOG: Added Authentication Failure message
 * LOG:
 * LOG: Revision 9.1.2.3  2005/11/18 05:02:38  adutta
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 9.1.2.2  2005/10/14 10:21:56  adutta
 * LOG: modified print for DTAP messages
 * LOG:
 * LOG: Revision 9.1.2.1  2005/09/29 07:13:10  adutta
 * LOG: Implemented paging response
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:09  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:13  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/10 16:55:53  ngoel
 * LOG: DTAP merge
 * LOG:
 * LOG: Revision 1.1.2.23  2002/06/06 20:44:30  ngoel
 * LOG: after MM changes
 * LOG:
 * LOG: Revision 1.1.2.22  2002/05/29 22:09:04  ngoel
 * LOG: add call state
 * LOG:
 * LOG: Revision 1.1.2.21  2002/05/29 20:10:30  ngoel
 * LOG: test start dtmf
 * LOG:
 * LOG: Revision 1.1.2.20  2002/05/29 19:08:09  ngoel
 * LOG: test notify message
 * LOG:
 * LOG: Revision 1.1.2.19  2002/05/29 18:29:49  ngoel
 * LOG: test congestion control message
 * LOG:
 * LOG: Revision 1.1.2.18  2002/05/24 20:35:01  ngoel
 * LOG: after MM fixes
 * LOG:
 * LOG: Revision 1.1.2.17  2002/05/24 15:58:32  ngoel
 * LOG: remove duplocate
 * LOG:
 * LOG: Revision 1.1.2.16  2002/05/24 13:41:35  ngoel
 * LOG: mm specific changes
 * LOG:
 * LOG: Revision 1.1.2.15  2002/05/22 17:04:14  ngoel
 * LOG: merge print functions with mm
 * LOG:
 * LOG: Revision 1.1.2.14  2002/05/10 13:52:09  ngoel
 * LOG: format print
 * LOG:
 * LOG: Revision 1.1.2.13  2002/05/09 20:40:38  ngoel
 * LOG: add auxillary state ie
 * LOG:
 * LOG: Revision 1.1.2.12  2002/05/09 20:13:35  ngoel
 * LOG: add clir ie print
 * LOG:
 * LOG: Revision 1.1.2.11  2002/05/09 17:21:27  ngoel
 * LOG: add fixes
 * LOG:
 * LOG: Revision 1.1.2.10  2002/05/09 16:10:35  ngoel
 * LOG: bug fixes
 * LOG:
 * LOG: Revision 1.1.2.9  2002/05/09 13:24:36  ngoel
 * LOG: add print functions
 * LOG:
 * LOG: Revision 1.1.2.8  2002/05/09 03:25:35  ngoel
 * LOG: dd messages
 * LOG:
 * LOG: Revision 1.1.2.7  2002/05/09 03:04:28  ngoel
 * LOG: dd print functions
 * LOG:
 * LOG: Revision 1.1.2.6  2002/05/09 02:47:00  ngoel
 * LOG: add print for ies
 * LOG:
 * LOG: Revision 1.1.2.5  2002/05/09 01:06:19  ngoel
 * LOG: add print functions
 * LOG:
 * LOG: Revision 1.1.2.4  2002/05/08 22:56:36  ngoel
 * LOG: dd function
 * LOG:
 * LOG: Revision 1.1.2.3  2002/05/08 19:45:15  ngoel
 * LOG: add code
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/08 18:52:51  ngoel
 * LOG: bug fixes
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 17:19:26  ngoel
 * LOG: start adding cc messages
 * LOG:
 * LOG: Revision 6.1.4.2  2002/04/26 20:44:36  hxing
 * LOG: Build on Solaris.
 * LOG:
 * LOG: Revision 6.1.4.1  2002/04/24 22:20:35  hxing
 * LOG: Back port to PR5.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.4  2001/11/26 15:27:28  dzhang
 * LOG: Add DumpIEBSS()
 * LOG:
 * LOG: Revision 1.3  2001/11/12 14:44:55  dzhang
 * LOG: update to latest spec version8.9.0
 * LOG:
 * LOG: Revision 1.2  2001/10/05 19:47:58  dzhang
 * LOG: Mionr modification on CircuitIdCodeList IE
 * LOG:
 * LOG: Revision 1.1  2001/10/02 21:54:26  dzhang
 * LOG: Initially check in after unit test
 * LOG:
 *
 ****************************************************************************/
#ifdef _WIN32
#pragma warning (disable : 4786)
#endif

#ifndef HPUX
#include <iostream>
#include <iomanip>
#else
#include <iostream/iostream.h>
#include <iostream/iomanip.h>
#endif

#include <stdio.h>

#include <BSSAPPrintIE.h>
//#include <its_exception.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

#if defined(ITS_NAMESPACE)
namespace its
{
#endif


void
DumpIE(ITS_OCTET id, const BSSAP_Element* ie)
{  
    //var2
    int                     i; 
    ITS_OCTET               key[32];
    ITS_OCTET               status[32];
    int                     len = 5;
    int                     len1;
    bool                    isExt;
    bool                    isNat;
    ITS_OCTET               classORcause1;
    ITS_OCTET               cause2, octet;
    BSSAP_CellIDType        cid;
    BSSAP_CellIDT           cid1[10];
    BSSAP_CircuitPool       cpn[10];
    char                    chardig[64];
    ITS_OCTET               octetdig[64];
    BSSAP_ResSitnElmnt      rse[5];

    BSSAP_LSAIdentifier     lid;
    BSSAP_LSA               lsa;
    BSSAP_SATID_IODE        sid;
    BSSAP_NetID             nid;
    ITS_OCTET               buf[50];
    ITS_OCTET               dlen = 0;

    if (ie == NULL)
    {
        return;
    }
    
    cout << setw(30) << "BSSAP IE --> ";
    cout << setiosflags(ios::left);

    switch (id)
    { 
    case BSSAP_IEI_CIRCUIT_IDENTITY_CODE:
        cout << "Circuit Identity Code: " << endl << setw(17) << " "
             << "PCMID: [ "
             << UshortToHex(((BSSAP_CktIDCode *)ie)->GetPCMID()) << "]"
             << endl << setw(17) << " " << "Timeslot: [ "
             << OctetToHex(((BSSAP_CktIDCode *)ie)->GetTimeslot()) << "]";
        break; 


    case BSSAP_IEI_RESOURCE_AVAILABLE:
        cout << "Resource Available: " << endl << setw(17) << " "
             << "Number of Full Rate at 0: [ "
             << UshortToHex(((BSSAP_ResAvail *)ie)->GetNumFull(0)) << "]"
             << endl << setw(17) << " "<< "Number of Full Rate at 1: [ " 
             << UshortToHex(((BSSAP_ResAvail *)ie)->GetNumFull(1)) << "]"
             << endl << setw(17) << " " << "Number of Half Rate at 0: [ "
             << UshortToHex(((BSSAP_ResAvail *)ie)->GetNumHalf(0)) << "]"
             << endl << setw(17) << " " << "Number of Half Rate at 1: [ "
             << UshortToHex(((BSSAP_ResAvail *)ie)->GetNumHalf(1)) << "]";
        break; 

    case BSSAP_IEI_CAUSE:
        cout << "Cause: " << endl << setw(17) << " ";
        ((BSSAP_Cse *)ie)->GetCause(isExt, isNat, classORcause1, cause2);
        cout << endl << setw(17) << " " <<"isExt: [ "<<OctetToHex(isExt)<<"]"
             << endl << setw(17) << " " <<"isNat: [ "<<OctetToHex(isNat)<<"]"
             << endl << setw(17) << " "
             << "classORcause1: [ " << OctetToHex(classORcause1) << "]"
             << endl << setw(17) << " "; 
        if(isExt)         
            cout << "cause2: [ " << OctetToHex(cause2) << "]";             
        break;    
 
    case BSSAP_IEI_CELL_IDENTIFIER:
        cout << "Cell Identifier: " << endl;
        octet = ((BSSAP_CellID *)ie)->GetCellIDDisc();        
        ((BSSAP_CellID *)ie)->GetCellID(cid);
        cout << setw(17) << " " << "cidDisc:[ " << OctetToHex(octet) << "]" 
             << endl;
        DumpCellID(octet, cid);        
        break;  
      
    case BSSAP_IEI_PRIORITY:
        cout << "Priority: " << endl << setw(17) << " "
             << "priority: [ "
             << OctetToHex(((BSSAP_Prio *)ie)->GetPriority()) << "]"
             << endl << setw(17) << " " << "QueuingAllowed: [ "
             << OctetToHex(((BSSAP_Prio *)ie)->GetQA()) << "]"
             << endl << setw(17) << " " << "Preemption Capability Ind: [ "
             << OctetToHex(((BSSAP_Prio *)ie)->GetPCI()) << "]"
             << endl << setw(17) << " " << "Preemption Vulnerability Ind: [ "
             << OctetToHex(((BSSAP_Prio *)ie)->GetPVI()) << "]";
        break;
    
    case BSSAP_IEI_LAYER3_HEADER_INFORMATION:
        cout << "Layer 3 Header Information: " << endl << setw(17)
             << " " << "Protocol Discrimination: ["
             << OctetToHex(((BSSAP_L3HeaderInfo *)ie)->GetProtDiscr()) << " ]"
             << endl << setw(17) << " " << "TI Value: ["
             << OctetToHex(((BSSAP_L3HeaderInfo *)ie)->GetTIVal()) << " ]"
             << endl << setw(17) << " "<< "TI Flag: ["
             << OctetToHex(((BSSAP_L3HeaderInfo *)ie)->GetTIFlag()) << " ]";
        break;

    case BSSAP_IEI_IMSI:
        cout << "IMSI: " << endl
             << setw(17) << " "
             << "Digits: ";             
             ((BSSAP_IMSI *)ie)->GetDigits(chardig, len);        
        cout << endl << setw(17) << " " << "digits: [ " << chardig << "]"
             << "    length: [ " << len << " ]"; 
                
        ((BSSAP_IMSI *)ie)->GetDigitsB(octetdig, len1);
        cout << endl << setw(17) << " " <<"Binary digits: [";
        for (i = 0; i < (len1 + 1) / 2; i++)
        {
            cout << OctetToHex(octetdig[i]);
        }
        cout << "]" << endl 
             << setw(17) << " " << "number of digits: [" << len1 << "]";
        break;


    case BSSAP_IEI_TMSI:
        cout << "TMSI: " << endl << setw(17) << " " << "[ "
             << UintToHex(((BSSAP_TMSI *)ie)->GetTMSI()) << " ]";
        break;

    case BSSAP_IEI_ENCRYPTION_INFORMATION:
        cout << "Encryption Information: " << endl
             << setw(17) << " " << "PermitAlg:" << endl
             << setw(17) << " " << "No Encryption: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetNoEncryption())
             << "]" << endl
             << setw(17) << " " << "A5_1: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetA5_1())
             << "]" << endl
             << setw(17) << " " << "A5_2: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetA5_2())
             << "]" << endl
             << setw(17) << " " << "A5_3: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetA5_3())
             << "]" << endl
             << setw(17) << " " << "A5_4: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetA5_4())
             << "]" << endl
             << setw(17) << " " << "A5_5: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetA5_5())
             << "]" << endl
             << setw(17) << " " << "A5_6: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetA5_6())
             << "]" << endl
             << setw(17) << " " << "A5_7: [ "
             << OctetToHex(((BSSAP_EncryptionInformation *)ie)->GetA5_7())
             << "]" << endl << setw(17) << " " << "key: [ "; 
        ((BSSAP_EncryptionInformation *)ie)->GetKey(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]," << "  Key's length: " << len;
        break; 

    case BSSAP_IEI_CHANNEL_TYPE:
        cout <<"Channel Type: " << endl
             <<setw(17) << " " << "Speech or Data Indicator: [ "
             <<OctetToHex(((BSSAP_ChanType *)ie)->GetSpeechDataID())<<"]"<<endl
             <<setw(17) << " " << "Channel Rate and Type: [ "
             <<OctetToHex(((BSSAP_ChanType *)ie)->GetChanRateType())<<"]"<<endl
             <<setw(17)<<" "<<"Permitted Speech Version ID/Rate and isExt: "<< endl;
                          
             ITS_BOOLEAN isExt;
             ITS_BOOLEAN transp;
             ITS_OCTET id;
             ITS_OCTET rate;
             if (((BSSAP_ChanType *)ie)->GetSpeechDataID() == CT_SPEECH)
             {
                 for (i = 0; i < 6; i++)
                 {                  
                     ((BSSAP_ChanType *)ie)->GetPermitSpch(isExt, id, i);

                     cout << "[" << OctetToHex(id) << "]-";
                     cout << "[" << OctetToHex(isExt) << "]; ";
                 }
             }
             else if (((BSSAP_ChanType *)ie)->GetSpeechDataID() == CT_DATA)
             {
                 ((BSSAP_ChanType *)ie)->GetDataTransp(isExt, rate, transp);
                 cout << setw(17) << " " << "[" << OctetToHex(rate) << "]-";
                 cout << "[" << OctetToHex(isExt) << "]; ";
                 cout << "Transparent: [" << OctetToHex(transp) << "]" <<endl;

                 ((BSSAP_ChanType *)ie)->GetIFDateRate(isExt, rate);
                 cout << setw(17) << " " << "Allowed r i/f rate: [" 
                      << OctetToHex(rate) << "]-";
                 cout << "[" << OctetToHex(isExt) << "]"<<endl;

                 ((BSSAP_ChanType *)ie)->GetAsymInd(isExt, rate);
                 cout << setw(17) << " " << "Assymmetry Indication:[" 
                      << OctetToHex(rate) << "]-";
                 cout << "[" << OctetToHex(isExt) << "]"<<endl;
             }
        break;

    case BSSAP_IEI_PERIODICITY:
        cout << "Periodicity: " << endl
             << setw(17) << " " << "periodicity: [ "
             << OctetToHex(((BSSAP_Period *)ie)->GetPeriod()) <<" ]";
        break;

    case BSSAP_IEI_EXTENDED_RESOURCE_INDICATOR:
        cout << "Extended Resource Indicator: " << endl
             << setw(17) << " " << "Total Accessible Resource Requested: [ "
             << OctetToHex(((BSSAP_ExtResInd *)ie)->GetTARR()) << " ]" << endl
             << setw(17) << " " << "Subsequent Mode: [ "
             << OctetToHex(((BSSAP_ExtResInd *)ie)->GetSM()) << " ]";
        break;

    case BSSAP_IEI_NUMBER_OF_MS:
        cout << "Number of MSs: " << endl
             << setw(17) << " " << "Number of Handover Candidate: [ "
             << OctetToHex(((BSSAP_NumMSs *)ie)->GetNumHand()) << " ]";
        break;

    case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2:
        cout << "Classmark Info Type 2: " << endl
             << setw(17) << " " << "RF Power Capability: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetRFPowerCap()) << "]"
             << endl << setw(17) << " " << "Short Message Capability: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetSMCap()) << "]"
             << endl << setw(17) << " " << "Frequency Capability: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetFC()) << "]"
             << endl << setw(17) << " " << "A5/1: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetA51()) << "]"
             << endl << setw(17) << " " << "ES Ind: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetESIND()) << "]"
             << endl << setw(17) << " " << "Revision level: [ " 
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetRevLevel()) << "]"
             << endl << setw(17) << " " << "VGCS notificatio reception: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetVGCS()) << "]"
             << endl << setw(17) << " " << "VBS notificatio reception: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetVBS()) << "]"
             << endl << setw(17) << " " << "SS screen indicator: [ "             
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetSSSInd()) << "]"
             << endl << setw(17) << " " << "PS Capability: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetPSCap()) << "]"
             << endl << setw(17) << " " << "A5/2: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetA52()) << "]"
             << endl << setw(17) << " " << "A5/3: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetA53()) << "]"
             << endl << setw(17) << " " << "CMSP: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetCMSP()) << "]"
             << endl << setw(17) << " " << "SoLSA: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetSoLSA()) << "]"
             << endl << setw(17) << " " << "LCSVACap: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetLCSVACap()) << "]"
             << endl << setw(17) << " " << "CM3: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo2 *)ie)->GetCM3()) << "]";
        break;


    case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3:
        cout << "Classmark Information Type 3: " << endl << setw(17) << " "
             << "Multiband Supported: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMultiBand()) << "]"
             << endl << setw(17) << " " << "Band 1: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMultiBand1())<<"]"
             << endl << setw(17) << " " << "Band 2: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMultiBand2())<<"]"
             << endl << setw(17) << " " << "Band 3: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMultiBand3())<<"]"
             << endl << setw(17) << " " << "A5/4: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetA54())<<"]"
             << endl << setw(17) << " " << "A5/5: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetA55())<<"]"
             << endl << setw(17) << " " << "A5/6: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetA56())<<"]"
             << endl << setw(17) << " " << "A5/7: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetA57())<<"]"
             << endl << setw(17) << " " << "Assoc. Radio Cap1: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetRadioCap1())<<"]"
             << endl << setw(17) << " " << "Assoc. Radio Cap2: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetRadioCap2())<<"]"
             << endl << setw(17) << " " << "R Suport: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetRGSMCap())<<"]"
             << endl << setw(17) << " " << "Multi Slot Cap: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMultiSlotClass())<<"]"
             << endl << setw(17) << " " << "UCS2 Treatment: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetUCS2Treat())<<"]"
             << endl << setw(17) << " " << "Ext Measurement Cap: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetExtMeasCap())<<"]"
             << endl << setw(17) << " " << "SM Value: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetSMValue())<<"]"
             << endl << setw(17) << " " << "SMS Value: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetSMSValue())<<"]"
             << endl << setw(17) << " " << "MS Conventional GPS: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMSConGPS())<<"]"
             << endl << setw(17) << " " << "MS Based GPS: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMSBasedGPS())<<"]"
             << endl << setw(17) << " " << "MS Assisted GPS: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMSAssistedGPS())<<"]"
             << endl << setw(17) << " " << "MS Based EOTD: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMSBasedEOTD())<<"]"
             << endl << setw(17) << " " << "MS Assisted EOTD: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo3 *)ie)->GetMSAssistedEOTD())<<"]";
        break;
 
    case BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED:
        cout << "Interference Band To Be Used: " << endl
             << setw(17) << " " << "Band To Be Used: [ "
             << OctetToHex(((BSSAP_InterBandToBeUsed *)ie)->GetBandToBeUsed()) 
             << "]";
        break; 

    case BSSAP_IEI_RR_CAUSE:
        cout << "RR Cause: " << endl << setw(17) << " "
             << "RR cause: [ " 
             << OctetToHex(((BSSAP_RRcause *)ie)->GetRRCause()) << "]";
        break;      

    case BSSAP_IEI_LAYER3_INFORMATION:
        cout << "Layer 3 Information: "
             << endl << setw(17) << " " << "[ ";
            
        ((BSSAP_L3Info *)ie)->GetL3Info(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]," << endl << setw(17) << " " <<"Message's length: "<<len; 
        break;

    case BSSAP_IEI_DLCI:
        cout << "DLCI: " << endl << setw(17) << " "
             << "Control channel: [ " 
             << OctetToHex(((BSSAP_dlci *)ie)->GetCtrlChan()) << "]" 
             << "SAPI: [ " 
             << OctetToHex(((BSSAP_dlci *)ie)->GetSAPI()) << "]";              
        break;  

    case BSSAP_IEI_DOWNLINK_DTX_FLAG:
        cout << "DTXFlag: " << endl << setw(17) << " " << "[ "
             << OctetToHex(((BSSAP_DLDTXFlag *)ie)->GetDTXFlag()) << "]";
        break; 
      
    case BSSAP_IEI_CELL_IDENTIFIER_LIST:
        cout << "Cell ID List: " << endl << setw(17) << " " 
             << "Number of cells is: [";
        len = ((BSSAP_CellIDList *)ie)->GetCellIDCount();
        cout << len  << "]" << endl;
        octet = ((BSSAP_CellIDList *)ie)->GetCellIDListDisc();
        cout << setw(17) << " " << "cidDisc:[ " << OctetToHex(octet) << "]" << endl;
        for(i = 0; i < len; i++)
        {
            ((BSSAP_CellIDList *)ie)->GetCellID(cid1[i], i);            
            DumpCellIDList(octet, cid1[i]);            
        }        
        break;


    case BSSAP_IEI_RESPONSE_REQUEST:
        cout << "Response Request: " << endl << setw(17) << " "
             << "No data.";
        break;      

      
    case BSSAP_IEI_RESOURCE_INDICATION_METHOD:
        cout << "Resource Indication Method: " << endl << setw(17) << " "<<"[ "
             << OctetToHex(((BSSAP_ResIndMethod *)ie)->GetResIndMethod())<<"]";
        break;

                
    case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1: 
        cout << "Classmark Information Type 1: " << endl 
             << setw(17) << " " << "RF Power Capability: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo1 *)ie)->GetRFPowerCap()) << "]"
             << endl << setw(17) << " " << "A5/1: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo1 *)ie)->GetA51()) << "]"
             << endl << setw(17) << " " << "ES Indicator: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo1 *)ie)->GetESIND()) << "]"
             << endl << setw(17) << " " << "Revision Level: [ "
             << OctetToHex(((BSSAP_ClassmarkInfo1 *)ie)->GetRevLevel()) << "]";             
        break;
        

    case BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST:
        int bitn;
        cout << "Circuit Id Code List: " 
             << endl << setw(17) << " " << "Range: " << "[ "
             << OctetToHex(((BSSAP_CktIDCodeList *)ie)->GetRange()) << "]"
             << endl << setw(17) << " " << "Input bitn to show nth bit "
             << "(0 - Range for batch Set, " << endl
             << setw(17) << " " << "or the exact bitn for individual Set) "
             << endl;
        cout << endl << setw(17) << " " << "--> ";
        cin  >> bitn;
        cout << endl << setw(17) << " " << "Status Bit " << bitn <<": " << "[ "
             << OctetToHex(((BSSAP_CktIDCodeList *)ie)->GetStatusBit(bitn)) << "]";  
        cout << endl << setw(17) << " " << "Status Bits: [ "; 
        ((BSSAP_CktIDCodeList *)ie)->GetStatus(status, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(status[i]);
        }
        cout << "]," << "  Status's byte number: " << len; 
        break;

 
    case BSSAP_IEI_DIAGNOSTICS:
        cout << "Diagnostics: " << endl
             << setw(17) << " " << "Error pointer: [ "
             << OctetToHex(((BSSAP_Diagn *)ie)->GetErrPtr()) << "]"  
             << endl << setw(17) << " " << "Bit pointer: [ "
             << OctetToHex(((BSSAP_Diagn *)ie)->GetBitPtr()) << "]"  
             << endl << setw(17) << " " << "Message Received: [ "; 
        ((BSSAP_Diagn *)ie)->GetMsgRcvd(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]" << "    length:[" << len << "]";
        break;


    case BSSAP_IEI_CHOSEN_CHANNEL:
        cout << "Chosen Channel: " << endl
             << setw(17) << " " << "Channel: [ "
             << UshortToHex(((BSSAP_ChsChan *)ie)->GetChan()) << "]"  
             << endl << setw(17) << " " << "Channel Mode: [ "
             << OctetToHex(((BSSAP_ChsChan *)ie)->GetChanMode()) << "]"; 
        break;


    case BSSAP_IEI_TOTAL_RESOURCE_ACCESSIBLE:
        cout << "Total Resource Accessible: " <<endl
             << setw(17) << " " << "Full rate channel: [ "
             << UshortToHex(((BSSAP_TotResAcc *)ie)->GetFullRate()) << " ]"
             << endl << setw(17) << " " << "Half rate channel: [ "
             << UshortToHex(((BSSAP_TotResAcc *)ie)->GetHalfRate()) << " ]";
        break;


    case BSSAP_IEI_CIPHER_RESPONSE_MODE:
        cout << "Cipher Response Mode: " << endl << setw(17) << " " << "[ "
             << OctetToHex(((BSSAP_CipherRspMode *)ie)->GetCipherRspMode()) 
             << "]";
        break;     

    case BSSAP_IEI_LAYER3_MESSAGE_CONTENT:
        cout << "Layer 3 Message Contents: "
             << endl << setw(17) << " " << "[ ";
            
        ((BSSAP_L3MsgCnt *)ie)->GetL3MsgCnt(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]," << endl << setw(17) << " " <<"Message's length: "<<len; 
        break;
        
    case BSSAP_IEI_CHANNEL_NEEDED:
        cout << "Channel Needed: " << endl << setw(17) << " " << "[ "
             << OctetToHex(((BSSAP_ChanNeeded *)ie)->GetChan()) << "]";
        break;    

            
    case BSSAP_IEI_TRACE_TYPE:
        cout << "Trace Type: " << endl 
             << setw(17) << " " << "Invokeing Events: " << "[ "
             << OctetToHex(((BSSAP_TraceTyp *)ie)->GetInvEvnt()) << "]"
             << endl << setw(17) << " " << "MSC Record Type: "<< "[ "
             << OctetToHex(((BSSAP_TraceTyp *)ie)->GetMSCRecType()) << "]"
             << endl << setw(17) << " " << "BSS Record Type: "<< "[ "
             << OctetToHex(((BSSAP_TraceTyp *)ie)->GetBSSRecType()) << "]"
             << endl << setw(17) << " " << "Priority Indication: "<< "[ "
             << OctetToHex(((BSSAP_TraceTyp *)ie)->GetPrioInd()) << "]";
        break;        
 
           
    case BSSAP_IEI_TRIGGER_ID:
         cout << "Trigger ID: " << endl << setw(17) << " " << "[ ";
             (((BSSAP_TrigID *)ie)->GetEntityID(key, len));

        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]," << "  EntityID's length: " << len;
        break;

           
    case BSSAP_IEI_TRACE_REFERENCE:
        cout << "Trace Reference: " << endl << setw(17) <<" "<< "[ "
             << UshortToHex(((BSSAP_TraceRef *)ie)->GetTraceRef()) << "]";
        break;        
 
 
    case BSSAP_IEI_TRANSACTION_ID:
        cout << "TransactionID: " << endl << setw(17) << " " << "[ "
             << UshortToHex(((BSSAP_TransactionID *)ie)->GetTransNo()) << "]";
        break;    
  
     
    /*case BSSAP_IEI_MOBILE_IDENTITY: 
        cout << "Mobile Identity: " << endl << setw(17) << " " 
             << "Type of Identity: [ " 
             << OctetToHex(((BSSAP_MobileID *)ie)->GetTypeIdentity())<<"]"<<endl
             << setw(17) << " " << "Odd or Even: [ "
             << OctetToHex(((BSSAP_MobileID *)ie)->GetOddEvenInd()) << "]";
            
            ((BSSAP_MobileID *)ie)->GetIdenCDig(chardig, len1);
            cout << endl << setw(17)<<" "<<"character digits:[ "<<chardig<<" ]"
                 << " length: [ " << len1 << " ]";    
        break;*/ 
        

    case BSSAP_IEI_OMC_ID: 
        cout << "OMCID: " << endl << setw(17) << " " << "[ ";
             (((BSSAP_OMCID *)ie)->GetOMCID(key, len));

        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]," << "  OMCID's length: " << len;
        break;

     
    case BSSAP_IEI_FORWARD_INDICATOR:
        cout << "Forward Indicator: " << endl << setw(17) << " " << "[ "
             << OctetToHex(((BSSAP_FwdInd *)ie)->GetFwdInd()) << "]";
        break; 
    
 
    case BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM:
        cout << "Chosen Encryption Algorithm: " << endl << setw(17) << " "
             << "AlgorithmID: [ "
             << OctetToHex(((BSSAP_ChsEncAlg *)ie)->GetAlgorithmID()) << "]";
        break;
 
    case BSSAP_IEI_CIRCUIT_POOL:
        cout << "Circuit Pool: " << endl << setw(17) << " "
             << "Circuit Pool Number: [ "
             << OctetToHex(((BSSAP_CktPool *)ie)->GetCircuitPoolNo()) << "]";
        break;

    case BSSAP_IEI_CIRCUIT_POOL_LIST:      
        cout << "Circuit Pool List: " << endl << setw(17) << " " << endl;          
        for(i = 0; i < 2; i++)
        {
            ((BSSAP_CktPoolList *)ie)->GetCircuitPoolNo(cpn[i], i);  

            cout << setw(17) << " " << "Circuit Pool Number: [ "
                 << OctetToHex(CP_GET_CIRCUIT_POOL_NUM(cpn[i])) << "] "
                 << endl;             
        }     
        break;

    case BSSAP_IEI_TIME_INDICATION:
        cout << "Time Indication: " << endl << setw(17) << " "
             << "Time: [ "
             << OctetToHex(((BSSAP_TimeInd *)ie)->GetTime()) << "]";
        break;


    case BSSAP_IEI_RESOURCE_SITUATION:
        cout << "Resource Situation: ";
        for(i = 0; i < 5; i++)
        {           
            ((BSSAP_ResSituation *)ie)->GetResSitnElmnt(rse[i], i); 
            
            cout << setw(17) << " " << endl
                 << "Channel type:[ " << OctetToHex(RS_GET_CHANNEL_TYPE(rse[i]))
                 << "] "
                 << "Res & Interf Band Ind:[ " 
                 << OctetToHex(RS_GET_RADIO_INT_BAND_IND(rse[i])) << "] "
                 << "isExt: [ " << OctetToHex(RS_GET_EXTENSION_BIT(rse[i])) << "]"
                 << "Bsase Channel:[ " 
                 << OctetToHex(RS_GET_NUMBER_OF_CHANNEL_BASE_VALUE(rse[i])) 
                 << "] ";

             if (RS_GET_EXTENSION_BIT(rse[i])) //two Octets
             {
                 cout << "Bsase Channel:[ " 
                      << OctetToHex(RS_GET_NUMBER_OF_CHANNEL_EXT_VALUE(rse[i])) 
                      << "] " << endl;
             }                        
        }        
        break;


    case BSSAP_IEI_CURRENT_CHANNEL_TYPE_1:
        cout << "Current Channel Type 1: " << endl << setw(17) << " "
             << "Channel: [ "
             << OctetToHex(((BSSAP_CrtChan *)ie)->GetChan()) << "]"
             << endl << setw(17) << " " << "Channel mode: [ "
             << OctetToHex(((BSSAP_CrtChan *)ie)->GetChanMode()) << "]";
        break;


    case BSSAP_IEI_QUEUING_INDICATOR:
        cout << "Queuing Indicator: " << endl << setw(17) << " "
             << "Queuing recommendation indicator: [ "
             << OctetToHex(((BSSAP_QueuingInd *)ie)->GetQRI()) << "]";
        break;


    case BSSAP_IEI_SPEECH_VERSION:
        cout << "Speech Version: " << endl << setw(17) << " "
             << "Speech Version Identifier: [ "
             << OctetToHex(((BSSAP_SpchVer *)ie)->GetSpchVerID()) << "]";
        break;


    case BSSAP_IEI_ASSIGNMENT_REQUIREMENT:
        cout << "Assignment Requirement: " << endl << setw(17) << " " << "[ "
             << OctetToHex(((BSSAP_AssReq *)ie)->GetAssReq()) << "]";
        break;


    case BSSAP_IEI_TALKER_FLAG:
        cout << "Talker Flag: " << endl << setw(17) 
             << setw(17) << " " << "No data";
        break;


    case BSSAP_IEI_CONNECTION_RELEASE_REQUESTED:
        cout << "Connection Release Requested: " << endl
             << setw(17) << " " << "No data.";
        break;


    case BSSAP_IEI_GROUP_CALL_REFERENCE:
        cout << "Group Call Reference: " << endl 
             << setw(17) << " " << "Call refercnce: [ "
             << UintToHex(((BSSAP_GrpClRef *)ie)->GetCallRef()) << "]"
             << endl << setw(17) << " " << "Call priority: [ "
             << OctetToHex(((BSSAP_GrpClRef *)ie)->GetClPrio()) << "]"
             << endl << setw(17) << " " << "Acknowledge flag: [ "
             << OctetToHex(((BSSAP_GrpClRef *)ie)->GetAF()) << "]"
             << endl << setw(17) << " " << "Service flag: [ "
             << OctetToHex(((BSSAP_GrpClRef *)ie)->GetSF()) << "]"
             << endl << setw(17) << " " << "Ciphering information: [ "
             << OctetToHex(((BSSAP_GrpClRef *)ie)->GetCiphInfo()) << "]";
        break;


    case BSSAP_IEI_eMLPP_PRIORITY:
        cout << "eMML Priority: " << endl << setw(17) << " "
             << "Call priority: [ "
             << OctetToHex(((BSSAP_eMMLPrio *)ie)->GetClPrio()) << "]";
        break;

    case BSSAP_IEI_CONFIGURATION_EVOLUTION_IND:
        cout << "Configuration Evolution Indication: " << endl << setw(17)<<" "
             << "Subsequent modification indication: [ "
             << OctetToHex(((BSSAP_ConfigEvlInd *)ie)->GetSMI()) << "]";
        break;

    case BSSAP_IEI_RETURN_ERROR_REQUEST:
        cout << "Return Error Request: ";
        cout<< endl << setw(17) <<" " << "Error Type: [ ";
        cout<<OctetToHex(((BSSAP_ReturnErrReq *)ie)->GetErrorType()) << "]";
        break;

    case BSSAP_IEI_RETURN_ERROR_CAUSE:
        cout << "Return Error Cause: "
             << endl << setw(17) <<" " << "Cause Value: [ "
             << OctetToHex(((BSSAP_ReturnErrCse *)ie)->GetCauseValue()) << "]";
        break;

    case BSSAP_IEI_SEGMENTATION:
        cout << "Segmentation: " << endl << setw(17)<<" "
             << "Segment Number: [ "
             << OctetToHex(((BSSAP_Segment *)ie)->GetSegmentNum()) << "] "
             << "Segment Bit: [ "
             << OctetToHex(((BSSAP_Segment *)ie)->GetSegmentBit()) << "]"
             << endl << setw(17)<<" " << "Messge ID: [ "             
             << UshortToHex(((BSSAP_Segment *)ie)->GetMessageID()) << "]";
        break;

    case BSSAP_IEI_SERVICE_HANDOVER:
        cout << "Serivce Handover: " << endl << setw(17)<<" "
             << "Serivce Handover Information: [ "
             << OctetToHex(((BSSAP_ServHandover *)ie)->GetServHandoverInfo()) << "]";
        break;

     case BSSAP_IEI_APDU:
        cout << "APDU: " << endl
             << setw(17) << " " << "Protocol ID: [ "
             << OctetToHex(((BSSAP_Apdu *)ie)->GetProtocolID())
             << "]" << endl            
             << setw(17) << " " << "Embeded Msg: [ "; 
        ((BSSAP_Apdu *)ie)->GetEmbededMsg(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]," << "  Msg's length: " << len;
        break; 

    case BSSAP_IEI_LCS_CAUSE:
        cout << "LCS Cause: " << endl << setw(17)<<" "
             << "Cause Value: [ "
             << OctetToHex(((BSSAP_LCSCse *)ie)->GetCauseValue()) << "]"
             << endl << setw(17)<<" " << "Diagnostic Value: [ "
             << OctetToHex(((BSSAP_LCSCse *)ie)->GetDiagValue()) << "]";
        break;


    ITS_OCTET mthd;
    ITS_OCTET usg;
    case BSSAP_IEI_POSITIONING_DATA:
        cout << "Positioning Data: " << endl
             << setw(17) << " " << "Position Data Discr: [ "
             << OctetToHex(((BSSAP_PositionData *)ie)->GetPosDataDiscr())
             << "]" << endl           
             << setw(17) << " " << "Embeded Msg: " << endl;        
        for(i =0 ; i < 2; i++)
        {
            ((BSSAP_PositionData *)ie)->GetPosMthd_Usage(mthd, usg, i);

            cout << setw(17) << " " << "Method: [ ";
            cout << OctetToHex(mthd)
                 << " ]" << endl;
            cout << setw(17) << " " << "Usage: [ ";
            cout << OctetToHex(usg)
                 << " ]" << endl;         
        }
        cout << setw(17) << " " << "Position Method's number: "
             <<((BSSAP_PositionData *)ie)->GetPosMthd_UsageCount();
        break; 


    case BSSAP_IEI_DECIPHERING_KEYS:
        cout << "Deciphering Keys: " << endl
             << setw(17) << " " << "Key Flag: [ "
             << OctetToHex(((BSSAP_DecipherKeys *)ie)->GetKeyFlag())
             << "]" << endl            
             << setw(17) << " " << "Current Value: [ "; 
        ((BSSAP_DecipherKeys *)ie)->GetCurrentValue(key);
        for(i =0 ; i < 7; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]";

        cout << endl << setw(17) << " " << "Next Value: [ ";
        ((BSSAP_DecipherKeys *)ie)->GetCurrentValue(key);
        for(i =0 ; i < 7; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]";
        break; 

    case BSSAP_IEI_LOCATION_ESTIMATE:
        cout << "Location Estimate: " << endl
             << setw(17) << " " << "[ "; 
        ((BSSAP_LocEstimate *)ie)->GetLocEstimate(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]," << "  Msg's length: " << len;
        break; 

    case BSSAP_IEI_LOCATION_TYPE:
        cout << "Location Type: " << endl << setw(17)<<" "
             << "Location Information: [ "
             << OctetToHex(((BSSAP_LocType *)ie)->GetLocInfo()) << "]"
             << endl << setw(17)<<" " << "Position Method: [ "
             << OctetToHex(((BSSAP_LocType *)ie)->GetPosMethod()) << "]";
        break;

     case BSSAP_IEI_LCS_PRIORITY:
        cout << "LCS Priority: " << endl
             << setw(17) << " " << "[ "; 
        ((BSSAP_LCSPrio *)ie)->GetPriority(key);
        for(i =0 ; i < 1; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]";
        break; 

    
    case BSSAP_IEI_GPS_ASSISTANCE_DATA:
        cout << "GPS Assistance Data: " << endl
             << setw(17) << " " << "Almanc: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetAlmanc())
             << "]" << endl           
             << setw(17) << " " << "UTC Model: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetUTCModel())
             << "]" << endl 
             << setw(17) << " " << "Ionospheric Model: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetIonosphericModel())
             << "]" << endl 
             << setw(17) << " " << "Navigation Model: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetNavigationModel())
             << "]" << endl 
             << setw(17) << " " << "DGPS Corrections: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetDGPSCorrections())
             << "]" << endl 
             << setw(17) << " " << "Ref Location: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetRefLocation())
             << "]" << endl 
             << setw(17) << " " << "RefTime: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetRefTime())
             << "]" << endl 
             << setw(17) << " " << "Acquition Assistance: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetAcquitionAssistance())
             << "]" << endl 
             << setw(17) << " " << "Real Time Integrity: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetRealTimeIntegrity())
             << "]" << endl
             << setw(17) << " " << "GPSWeek: [ "
             << UshortToHex(((BSSAP_GPSAssistData *)ie)->GetGPSWeek())
             << "]" << endl
             << setw(17) << " " << "GPS Toe: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetGPSToe())
             << "]" << endl
             << setw(17) << " " << "ToeLimit: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetToeLimit())
             << "]" << endl
             << setw(17) << " " << "NSAT: [ "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetNSAT())
             << "]" << endl;

             cout << endl << setw(17) << " " << "Max Index = "
             << OctetToHex(((BSSAP_GPSAssistData *)ie)->GetSatid_IodeCount())<<endl;
        for (i = 0; i < 2; i++)
        {
            ((BSSAP_GPSAssistData *)ie)->GetSatid_Iode(sid, i);
            cout << endl << setw(17) << " " << "Satid_Iode - " << i 
                 << endl << setw(17) << " " 
            << "SAT ID: [" << OctetToHex(GAD_GET_SAT_ID(sid)) << "]"
            << endl << setw(17) << " " 
            << "IODE: [" << OctetToHex(GAD_GET_IODE(sid)) << "]"<<endl;
        }       
        break; 

    case BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR:
        cout << "LSA Access Control Suppress: " << endl
             << setw(17) << " " << "Emergency: [ "
             << OctetToHex(((BSSAP_LsaAccCtrlSuppr *)ie)->GetEmergency())
             << "]"; 
        
    case BSSAP_IEI_LSA_IDENTIFIER:
        cout << "LSA Identifier: " << endl << setw(17) << " " 
             << "LSA ID Bit 1: [ "
             << OctetToHex(((BSSAP_LsaId *)ie)->GetLSAIDBit1()) << " ]"
             << endl << setw(17) << " " << "LSA ID: [ "
             << UintToHex(((BSSAP_LsaId *)ie)->GetLSAID()) << " ]";
        break;

    case BSSAP_IEI_LSA_IDENTIFIER_LIST:
        cout << "LSA Identifier List: " << endl << setw(17) << " " 
             << "Escape PLMN: [ "
             << OctetToHex(((BSSAP_LsaIdList *)ie)->GetEscapePLMN()) << " ]";
        cout << endl << setw(17) << " " << "LSA ID: ";

        cout << endl << setw(17) << " " <<"Max Index = "
             << OctetToHex(((BSSAP_LsaIdList *)ie)->GetLSAIDCount()) << endl;
        for (i = 0; i < 2; i++)
        {
            ((BSSAP_LsaIdList *)ie)->GetLSAID(lid, i);
            cout << endl << setw(17) << " " << "LSID - " << i 
                 << endl << setw(17) << " " 
            << "Bit 1: [" << OctetToHex(LSAID_GET_LSA_ID_BIT_1(lid)) << "]"
            << endl << setw(17) << " " 
            << "LSA ID: [" << UintToHex(LSAID_GET_LSA_ID(lid)) << "]"<<endl;
        }           
        break;

    case BSSAP_IEI_LSA_INFORMATION:
        cout << "LSA Information: " << endl << setw(17) << " " 
             << "LSA Only Access Indicator: [ "
             << OctetToHex(((BSSAP_LsaInfo *)ie)->GetLSAIndicator()) << " ]";
        cout << endl << setw(17) << " " << "LSA ID: ";
        cout << endl << setw(17) << " "<< "Max Index = "
             << OctetToHex(((BSSAP_LsaInfo *)ie)->GetLSAIDCount()) << endl;

        for (i = 0; i < 3; i++)
        {
            ((BSSAP_LsaInfo *)ie)->GetLSAID(lsa, i);
            cout << endl << setw(17) << " " << "LSID - " << i 
                 << endl << setw(17) << " " 
                 << "Priority: [" <<OctetToHex(LSAI_GET_LSA_ID_PRIORITY(lsa))<<"]"
                 << endl << setw(17) << " " 
                 << "PREF: [" << OctetToHex(LSAI_GET_LSA_ID_PREF(lsa))<<"]"
                 << endl << setw(17) << " " 
                 << "ACT: [" << OctetToHex(LSAI_GET_LSA_ID_ACT(lsa))<<"]"
                 << endl << setw(17) << " " 
                 << "Bit 1: [" << OctetToHex(LSAID_GET_LSA_ID_BIT_1(lsa))<<"]"
                 << endl << setw(17) << " " 
                 << "LSA ID:[" << UintToHex(LSAID_GET_LSA_ID(lsa)) << "]"<<endl;
        }           
        break;

     case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS:
        cout << "Soruce RNC to Target RNC Transparent Information (UMTS): " << endl
             << setw(17) << " " << "[ "; 
        ((BSSAP_SrcRNCtoTgtRNCInfoUMTS *)ie)->GetSrcRNCtoTgtRNCInfoUMTS(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]";
        break; 

    case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA:
        cout << "Soruce RNC to Target RNC Transparent Information (CDMA): " << endl
             << setw(17) << " " << "[ "; 
        ((BSSAP_SrcRNCtoTgtRNCInfoCDMA *)ie)->GetSrcRNCtoTgtRNCInfoCDMA(key, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(key[i]);
        }
        cout << "]";
        break; 

    case BSSAP_IEI_NETWORK_ELEMENT_IDENTITY:
        cout << "Network Identifier: " << endl;
        octet = ((BSSAP_NetElementID *)ie)->GetIDDisc();        
        ((BSSAP_NetElementID *)ie)->GetNetElementID(nid);
        cout << setw(17) << " " << "nidDisc:[ " << OctetToHex(octet) << "]" 
             << endl;
        DumpNetID(octet, nid);
        break;
    
    default:
        break;
    }
    cout << endl << endl;
    cout << resetiosflags(ios::left);
}

void
DumpIEMM(ITS_OCTET id, const BSSAP_Element* ie)
{  
    //var2
    ITS_INT           i; 

    //DTAP
    ITS_OCTET         mcc[2];
    ITS_OCTET         mnc[2];
    ITS_OCTET         lac[2];
    ITS_OCTET         lai[5];
    ITS_OCTET         pararand[16];
    ITS_OCTET         flPara[14];
    ITS_OCTET         parasres[4];
    ITS_OCTET         octet;
    ITS_OCTET         rc_value;
    char              chardig[64];
    ITS_INT           len1; 
    ITS_INT           len = 14; 
    BSSAP_NetID       nid;
    //END DTAP

    if (ie == NULL)
    {
        return;
    }
    
    cout << setw(30) << "BSSAP IE --> ";
    cout << setiosflags(ios::left);

    switch (id)
    { 
        case BSSAP_IEI_NETWORK_ELEMENT_IDENTITY:
            cout << "Network Identifier: " << endl;
            octet = ((BSSAP_NetElementID *)ie)->GetIDDisc();
            ((BSSAP_NetElementID *)ie)->GetNetElementID(nid);
            cout << setw(17) << " " << "nidDisc:[" << OctetToHex(octet) << "]"
            << endl;
            DumpNetID(octet, nid);
            break;      
 
        case BSSAP_IEI_MOBILE_IDENTITY:
            cout <<"Mobile Identity\n "; 
            cout << "Type of Identity: [ "
            << OctetToHex(((BSSAP_MobileID *)ie)->GetTypeIdentity())<<"]"<<endl;
            break;    

	case BSSAP_IEI_FOLLOW_ON_PROCEED:
            cout << "Follow On Proceed: " << endl
            << setw(17) << " " << "No data.";
            break;

	case BSSAP_IEI_CTS_PERMISSION:
            cout << "CTS Permission: " << endl
            << setw(17) << " " << "No data.";
            break;

	case BSSAP_IEI_LOCATION_UPDATING_TYPE:
            octet = ((BSSAP_LocationUpdatingType *)ie)->
                                          GetLocationUpdatingType();
            cout << "Location Updating Type:  " << endl
            << setw(17) << " " << "type:[" << OctetToHex(octet) << "]" << endl;
            break;
	
        // Changed to fix Bug no. 3279
	case BSSAP_IEI_CYPHERING_KEY_SEQUENCE:
            octet = ((BSSAP_CypheringKeySequence *)ie)->
                                          GetCypheringKeySequence();
            cout << "Cyphering Key Sequence:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet)
            << "]" << endl;
            break;

	case BSSAP_IEI_LOCATION_AREA_IDENTIFIER:
            cout << "Location Area Identifier :  " << endl;

/*	    ((BSSAP_LocationAreaID *)ie)->GetLocationAreaID(lai);
            for(i = 0 ; i < 5; i++)
            {
                cout << OctetToHex(lai[i]);
            }
*/
            ((BSSAP_LocationAreaID *)ie)->GetLocationAreaIDMCC(mcc);
            for(i = 0 ; i <= 1; i++)
            {
                cout << OctetToHex(mcc[i]);
            }

            ((BSSAP_LocationAreaID *)ie)->GetLocationAreaIDMNC(mnc);
            cout << OctetToHex(*mnc);

            ((BSSAP_LocationAreaID *)ie)->GetLocationAreaIDLAC(lac);
            for(i = 0 ; i <= 1; i++)
            {
                cout << OctetToHex(lac[i]);
            }
            break; 

	case BSSAP_IEI_PARAMETER_RAND:
            ((BSSAP_ParameterRand *)ie)->GetParameterRand(pararand);
            cout <<"Parameter RAND:   ";		 

            for(i =0 ; i < 16; i++)
            {
                cout <<  OctetToHex(pararand[i]);
            }
            cout << "]";
            break;

    
	case BSSAP_IEI_PARAMETER_SRES:
            ((BSSAP_ParameterSres *)ie)->GetParameterSres(parasres);
            cout <<"Parameter SRES:   ";
            
            for(i = 0 ; i < 4; i++)
            {
                cout << OctetToHex(parasres[i]);
            }
            cout << "]";
            break;

        case BSSAP_IEI_REJECT_CAUSE:
            ((BSSAP_RejectCause *)ie)->GetRejectCause(rc_value);
            cout <<"Reject Cause:   ";
            cout << OctetToHex(rc_value);
            break;

        case BSSAP_IEI_AUTH_FAILURE_PARAMETER:
            ((BSSAP_AuthFailParameter *)ie)->GetAuthFailParameter(flPara, len);
            cout <<"Authentication Failure Parameter: ";

            for(i = 0 ; i < 14; i++)
            {
                cout << OctetToHex(flPara[i]);
            }
            break;

	case BSSAP_IEI_IDENTITY_TYPE:
            octet = ((BSSAP_IdentityType *)ie)->GetIdentityType();
            cout << "Identity Type:  " << endl
            << setw(17) << " " << "type:[" << OctetToHex(octet) << "]" << endl;
            break;

	case BSSAP_IEI_CM_SERVICE_TYPE:
            octet = ((BSSAP_CMServiceType *)ie)->GetCMServiceType();
            cout << "CM Service Type:  " << endl
            << setw(17) << " " << "type:[" << OctetToHex(octet) << "]" << endl;
            break;

	case BSSAP_IEI_TIME_ZONE:
            octet = ((BSSAP_TimeZone *)ie)->GetTimeZone();
            cout << "Time Zone:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet) << "]" << endl;
            break;

	case BSSAP_IEI_TIME_ZONE_TIME:
            octet = ((BSSAP_TimeZoneTime *)ie)->GetTimeZoneYear();
            cout << "Time Zone Year:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet) << "]" << endl;

            octet = ((BSSAP_TimeZoneTime *)ie)->GetTimeZoneMonth();
            cout << "Time Zone Month:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet) << "]" << endl;

            octet = ((BSSAP_TimeZoneTime *)ie)->GetTimeZoneDay();
            cout << "Time Zone Day:  " << endl
            << setw(17) << " " << "type:[" << OctetToHex(octet) << "]" << endl;

            octet = ((BSSAP_TimeZoneTime *)ie)->GetTimeZoneHour();
            cout << "Time Zone Hour:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet) << "]" << endl;

            octet = ((BSSAP_TimeZoneTime *)ie)->GetTimeZoneMinute();
            cout << "Time Zone Minute:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet) << "]" << endl;

            octet = ((BSSAP_TimeZoneTime *)ie)->GetTimeZoneSecond();
            cout << "Time Zone Second:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet) << "]" << endl;

            octet = ((BSSAP_TimeZoneTime *)ie)->GetTimeZoneZone();
            cout << "Time Zone Zone:  " << endl
            << setw(17) << " " << "type:[ " << OctetToHex(octet) << "]" << endl;

            break;

        default:
            break;
    }
    cout << endl << endl;
    cout << resetiosflags(ios::left);
}

void
DumpCCIE(ITS_OCTET id, const BSSAP_Element* ie)
{  
    //var2
    int                     i; 
    ITS_OCTET               key[32];
    ITS_OCTET               status[32];
    int                     len = 5;
    int                     len1;
    bool                    isExt;
    bool                    isNat;
    ITS_OCTET               classORcause1;
    ITS_OCTET               cause2, octet;
    BSSAP_CellIDType        cid;
    BSSAP_CellIDT           cid1[10];
    BSSAP_CircuitPool       cpn[10];
    char                    chardig[64];
    ITS_OCTET               octetdig[64];
    BSSAP_ResSitnElmnt      rse[5];

    BSSAP_LSAIdentifier     lid;
    BSSAP_LSA               lsa;
    BSSAP_SATID_IODE        sid;
    BSSAP_NetID             nid;
    ITS_OCTET               buf[50];
    ITS_OCTET               dlen = 0;
    ITS_OCTET capab, rc,  tm;
    ITS_OCTET type, numPlan;
    ITS_OCTET prs, scr;
    ITS_BOOLEAN isOdd;

    if (ie == NULL)
    {
        return;
    }
    
    cout << setw(30) << "BSSAP IE --> ";
    cout << setiosflags(ios::left);

    switch (id)
    { 
    case BSSAP_IEI_CC_FACILITY :
        cout << "Facility: ";
        ((BSSAP_Facility *)ie)->GetFacilityData(buf, dlen);
        for(i =0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }
        cout << "]";
         
    break;
    
    case BSSAP_IEI_CC_PROGRESS_INDICATOR :
        cout << "Progress Indicator: ";
        ITS_OCTET coding, location, desc;
        ((BSSAP_ProgressIndicator *)ie)->
                        GetCodingLocationDesc(coding, location, desc);

        cout << setw(17) << " " <<  "Coding " << OctetToHex(coding) << endl;
        cout << setw(17) << " "  << "location " << OctetToHex(location) << endl;
        cout << "                  " << "Description " << OctetToHex(desc);
        cout << "]";
         
        break;

    case BSSAP_IEI_CC_USER_USER :
        cout << "User To User Info : " << endl;
        ITS_OCTET disc;
        ((BSSAP_UserToUser *)ie)->GetProtocolDiscriminator(disc);

        cout <<  setw(17) << " " << "Protocol Disc" << OctetToHex(disc) << endl;
        ((BSSAP_UserToUser *)ie)->GetUserInfo(buf, dlen);
        cout << setw(17) << " " << "User Info ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

        break;

    case BSSAP_IEI_CC_PRIORITY_LEVEL :
        ITS_OCTET prio;
        
        cout << "Priority Level :" << endl;

        ((BSSAP_PriorityLevel *)ie)->GetPriority(prio);

        cout << setw(17) << " " << "Priority " << OctetToHex(prio);

        break;
        
    case BSSAP_IEI_CC_BEARER_CAPABILITY :
        cout << "Bearer Data: " << endl;
        ((BSSAP_BearerData *)ie)->
               GetInfoTransferCapabAndRadioChannelType(capab, rc);

        cout << setw(17) << " " <<  "Info Transfer Capab " 
                                << OctetToHex(capab) << endl;
        cout << setw(17) << " " <<  "Radio Channel " << OctetToHex(rc) << endl;

        ((BSSAP_BearerData *)ie)->GetCoding(coding);
        ((BSSAP_BearerData *)ie)->GetTransferMode(tm);
        cout << setw(17) << " " <<  "Coding " << OctetToHex(coding) << endl;
        cout << setw(17) <<  " " << "Transfer Mode " << OctetToHex(tm) << endl;

        break;
        
    case BSSAP_IEI_CC_REPEAT_INDICATOR :
        cout << "Repeat Indicator: " << endl;
        ((BSSAP_RepeatIndicator *)ie)->GetRepeatType(rc);

        cout <<   setw(17) << " " <<  "Repeat Type  " << OctetToHex(rc) << endl;

        break;
        
    case BSSAP_IEI_CC_CONGESTION_LEVEL_INTERNAL :
        cout << "Congestion Level: " << endl;
        ((BSSAP_CongestionLevel *)ie)->GetCongestionLevel(rc);

        cout <<   setw(17) << " " <<  "Congestion Level  " << OctetToHex(rc) << endl;

        break;
        
    case BSSAP_IEI_CC_NOTIFICATION_INDICATOR_INTERNAL :
        cout << "Notification Indicator Level: " << endl;
        ((BSSAP_NotificationIndicator *)ie)->GetNotifyIndicator(rc);

        cout <<   setw(17) << " " <<  "Notify Indicator  " << OctetToHex(rc) << endl;

        break;
        
    case BSSAP_IEI_CC_MORE_DATA :
        cout <<  "More Data : " << endl;

        break;
        
    case BSSAP_IEI_CC_CLIR_SUPPRESSION :
        cout << "CLIR Indicator: " << endl;

        break;
        
    case BSSAP_IEI_CC_CLIR_INVOCATION :
        cout << "CLIR Invocation: " << endl;

        break;
        
    case BSSAP_IEI_CC_REVERSE_CALL_SETUP_DIRECTION :
        cout << "Reverse Call Setup Indicator: " << endl;

        break;
        
    case BSSAP_IEI_CC_CAUSE :
        ITS_OCTET cause;
        cout << "Cause : " << endl;
        ((BSSAP_CCCause *)ie)->GetCodingLocationCause(coding, location, cause);

        cout << setw(17) << " " << "location  " << OctetToHex(location) << endl;
        cout << setw(17) <<  " " << "coding  " << OctetToHex(coding) << endl;
        cout << setw(17) <<  " " << "cause  " << OctetToHex(cause) << endl;

        if (((BSSAP_CCCause *)ie)->IsRecommendationPresent())
        {
            ((BSSAP_CCCause  *)ie)->GetRecommendation(rc);
            cout << setw(17) << " " << "recommendation  " 
                             << OctetToHex(rc) << endl;
        }
        ((BSSAP_CCCause *)ie)->GetDiagnostics(buf, dlen);
        cout <<  setw(17) <<  " " <<  "User Info ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

        break;
        
    case BSSAP_IEI_CC_CAPABILITIES :
        cout << "CC Capabilities : " << endl;

        if(((BSSAP_CCCapabilities *)ie)->IsDTMFSet())
        {
            cout <<   setw(17) << " " <<  "DTMF SET" << endl;
        }
        else
        {
            cout <<   setw(17) << " " <<  "DTMF NOT SET" << endl;
        }

        if(((BSSAP_CCCapabilities *)ie)->IsPCPSet())
        {
            cout <<   setw(17) << " " <<  "PCP SET" << endl;
        }
        else
        {
            cout <<   setw(17) << " " <<  "PCP NOT SET" << endl;
        }

    break;
        
    case BSSAP_IEI_CC_SIGNAL :
        cout << "Signal : " << endl;
        ((BSSAP_Signal *)ie)->GetSignal(rc);

        cout <<   setw(17) << " " <<  "Signal " << OctetToHex(rc) << endl;


    break;
        
        
    case BSSAP_IEI_CC_CONNECTED_NUMBER :
        cout << "Connected Number: " << endl;
        ((BSSAP_ConnectedNumber *)ie)->GetTypeAndNumPlan(type, numPlan);

        cout <<   setw(17) << " " <<  "Type  " << OctetToHex(type) << endl;
        cout <<   setw(17) << " " <<  "NumPlan  " << OctetToHex(numPlan) << endl;

        if (((BSSAP_ConnectedNumber *)ie)->IsPresntationScreeningPresent())
        {
            ((BSSAP_ConnectedNumber *)ie)->GetPresentationAndScreening(prs, scr);
            cout <<  "Presentation  " << OctetToHex(prs) << endl;
            cout <<  "Screening  " << OctetToHex(scr) << endl;
        }
        ((BSSAP_ConnectedNumber *)ie)->GetDigits(buf, dlen);
        cout <<  setw(17) << " " <<  "Digits ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

    break;
        
    case BSSAP_IEI_CC_CALLING_PARTY_BCD_NUMBER :

        cout << "Calling Party Number: " << endl;
        ((BSSAP_CallingPartyBCDNumber *)ie)->GetTypeAndNumPlan(type, numPlan);

        cout <<   setw(17) << " " <<  "Type  " << OctetToHex(type) << endl;
        cout <<   setw(17) << " " <<  "NumPlan  " << OctetToHex(numPlan) << endl;

        if (((BSSAP_CallingPartyBCDNumber *)ie)->IsPresntationScreeningPresent())
        {
            ((BSSAP_ConnectedNumber *)ie)->GetPresentationAndScreening(prs, scr);
            cout <<   setw(17) << " " <<  "Presentation  " << OctetToHex(prs) << endl;
            cout <<   setw(17) << " " <<  "Screening  " << OctetToHex(scr) << endl;
        }
        ((BSSAP_CallingPartyBCDNumber *)ie)->GetDigits(buf, dlen);
        cout <<   setw(17) << " " << "Digits ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }


    break;
        
        
    case BSSAP_IEI_CC_CONNECTED_SUB_ADDRESS :
        cout << "Connected SubAddress: " << endl;
        ((BSSAP_ConnectedSubAddress *)ie)->GetSubAddressType(type, isOdd);

        if (isOdd)
        {
            cout <<    setw(17) << " " << "Type " << OctetToHex(type) << "odd" << endl;
        }
        else
        {
            cout <<   setw(17) << " " <<  "Type " << OctetToHex(type) << "not odd" << endl;
        }

        ((BSSAP_ConnectedSubAddress *)ie)->GetSubAddressInfo(buf, dlen);
        cout <<  setw(17) << " " <<  "SubAddressInfo ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }


    break;
        
    case BSSAP_IEI_CC_CALLING_PARTY_SUB_ADDRESS :

        cout << "Calling SubAddress: " << endl;
        ((BSSAP_CallingPartySubAddress *)ie)->GetSubAddressType(type, isOdd);

        if (isOdd)
        {
            cout <<    setw(17) << " " << "Type " << OctetToHex(type) << "odd" << endl;
        }
        else
        {
            cout <<    setw(17) << " " << "Type " << OctetToHex(type) << "not odd" << endl;
        }

        ((BSSAP_CallingPartySubAddress *)ie)->GetSubAddressInfo(buf, dlen);
        cout <<  setw(17) << " " <<  "SubAddressInfo ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

    break;
        
        
    case BSSAP_IEI_CC_CALLED_PARTY_BCD_NUMBER :


        cout << "Called Party Number: " << endl;
        ((BSSAP_CalledPartyBCDNumber *)ie)->GetTypeAndNumPlan(type, numPlan);

        cout <<    setw(17) << " " << "Type  " << OctetToHex(type) << endl;
        cout <<    setw(17) << " " << "NumPlan  " << OctetToHex(numPlan) << endl;

        ((BSSAP_CalledPartyBCDNumber *)ie)->GetDigits(buf, dlen);
        cout <<   setw(17) << " " << "Digits ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }


    break;
        
    case BSSAP_IEI_CC_CALLED_PARTY_SUB_ADDRESS :

        cout << "Called SubAddress: " << endl;
        ((BSSAP_CalledPartySubAddress *)ie)->GetSubAddressType(type, isOdd);

        if (isOdd)
        {
            cout <<    setw(17) << " " << "Type " << OctetToHex(type) << "odd" << endl;
        }
        else
        {
            cout <<    setw(17) << " " << "Type " << OctetToHex(type) << "not odd" << endl;
        }

        ((BSSAP_CalledPartySubAddress *)ie)->GetSubAddressInfo(buf, dlen);
        cout <<   setw(17) << " " << "SubAddressInfo ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }


    break;
        
        
    case BSSAP_IEI_CC_REDIRECTING_PARTY_BCD_NUMBER :


        cout << "Redirecting Party Number: " << endl;
        ((BSSAP_RedirectingPartyBCDNumber *)ie)->GetTypeAndNumPlan(type, numPlan);

        cout <<    setw(17) << " " << "Type  " << OctetToHex(type) << endl;
        cout <<   setw(17) << " " <<  "NumPlan  " << OctetToHex(numPlan) << endl;

        if (((BSSAP_RedirectingPartyBCDNumber *)ie)->IsPresntationScreeningPresent())
        {
            ((BSSAP_RedirectingPartyBCDNumber *)ie)->GetPresentationAndScreening(prs, scr);
            cout <<    setw(17) << " " << "Presentation  " << OctetToHex(prs) << endl;
            cout <<    setw(17) << " " << "Screening  " << OctetToHex(scr) << endl;
        }
        ((BSSAP_RedirectingPartyBCDNumber *)ie)->GetDigits(buf, dlen);
        cout <<   setw(17) << " " << "Digits ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

    break;
        
    case BSSAP_IEI_CC_REDIRECTING_PARTY_SUB_ADDRESS :

        cout <<   setw(17) << " " << "Redirecting SubAddress: " << endl;
        ((BSSAP_RedirectingPartySubAddress *)ie)->GetSubAddressType(type, isOdd);

        if (isOdd)
        {
            cout <<    setw(17) << " " << "Type " << OctetToHex(type) << "odd" << endl;
        }
        else
        {
            cout <<    setw(17) << " " << "Type " << OctetToHex(type) << "not odd" << endl;
        }

        ((BSSAP_RedirectingPartySubAddress *)ie)->GetSubAddressInfo(buf, dlen);
        cout <<   setw(17) << " " << "SubAddressInfo ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }


    break;
        
    case BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY :
        cout << "Low Level Compatibility : " << endl;

        ((BSSAP_LowLevelCompInfo *)ie)->GetLowLevelCompInfo(buf, dlen);
        cout <<   setw(17) << " " << "LowLevel Compatibility Info ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

    break;
        
    case BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY :
        cout << "High Level Compatibility : " << endl; 
        ITS_OCTET cpi, chrs, xchrs;
        ((BSSAP_HighLevelCompInfo *)ie)->GetCodingPrsInterpretAndCharacterstics(cpi, chrs);
        ((BSSAP_HighLevelCompInfo *)ie)->GetExtendedCharacterstics(xchrs);

        cout <<    setw(17) << " " << "Coding Presentation Charcaterstics " << OctetToHex(cpi) << endl;
        cout <<    setw(17) << " " << "Extended chracterstics " << OctetToHex(xchrs) << endl;

    break;
        
        
    case BSSAP_IEI_CC_SS_VERSION_IND :
        cout << "SS Version Indicator : " << endl;

        ((BSSAP_SSVersion *)ie)->GetSSVersion(buf, dlen);
        cout <<   setw(17) << " " << "SS Version Info ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

    break;
        
    case BSSAP_IEI_CC_SETUP_CONTAINER_INTERNAL :

        cout << "Setup Container : " << endl;

        ((BSSAP_SetupContainer *)ie)->GetSetupData(buf, dlen);
        cout <<   setw(17) << " " << "Setup Container Data ";
        for(i = 0 ; i < dlen; i++)
        {
            cout << OctetToHex(buf[i]);
        }

    break;
        
    case BSSAP_IEI_CC_KEYPAD_FACILITY :

        cout << "Keypad Facility : " << endl;

        ((BSSAP_KeyPadFacility *)ie)->GetKeyValue(rc);
        cout <<   setw(17) << " " <<  "Key Value " << OctetToHex(rc) << endl;

    break;
        
    case BSSAP_IEI_CC_CALL_STATE_INTERNAL :

        cout << "Call State : " << endl;

        ITS_OCTET value;

        ((BSSAP_CallState *)ie)->GetCodingAndState(value, rc);
        cout <<   setw(17) << " " <<  "State " << OctetToHex(rc) << endl;

    break;
        
    case BSSAP_IEI_CC_AUXILLARY_STATES :

        cout << "Auxillary Call State : " << endl;

        ((BSSAP_AuxState *)ie)->GetAuxState(rc);
        cout <<   setw(17) << " " <<  "State  " << OctetToHex(rc) << endl;

    break;

    case BSSAP_IEI_CC_ALLOWED_ACTIONS:
        cout << "Allowed Actions :" << endl;

        ITS_OCTET  ccbs; 

        ((BSSAP_AllowedAction *)ie)->GetCCBS(ccbs);
        cout <<   setw(17) << " " <<  "CCBS  " << OctetToHex(ccbs) << endl;
      
        break;

    case BSSAP_IEI_CC_STREAM_IDENTIFIER:
        cout << "Stream Identifier :" << endl;
                                                                                
        ITS_OCTET  sivalue;
                                                                                
        ((BSSAP_StreamIdentifier *)ie)->GetStrmIdentVal(sivalue);
        cout <<   setw(17) << " " <<  "Stream Identifier Value  " 
                                  << OctetToHex(sivalue) << endl;
                                                                                
        break;

    case BSSAP_IEI_CC_EMERGENCY_CATEGORY:
        cout << "Emergency Category :" << endl;

        ITS_OCTET  esValue;

        ((BSSAP_EmergencyCategory *)ie)->GetEmergencyVal(esValue);
        cout <<  setw(17) << " " << "Emergency Category Value  "
                                 << OctetToHex(esValue) << endl;
        break;

    case BSSAP_IEI_CC_SUPPORTED_CODECS:
        cout << "Supported Codecs :" << endl;

/*        ((BSSAP_SupportedCodecs *)ie)->GetSystemID(key, len1);
        cout <<  setw(17) << " " << "System Identification "
                                 << OctetToHex(key[0]);
        cout <<  setw(17) << " " << "Codec Bitmap "
             << OctetToHex(key[2]) << "," << OctetToHex(key[3]);
*/
    default:

        break;
    }
    cout << endl << endl;
    cout << resetiosflags(ios::left);
}

// Print Field IE in Old BSS To New BSS Informaiton
void
DumpIEBSS(ITS_OCTET id, const BSSAP_Element* ie)
{  
    //var2
    int            i; 
    int            len;
    ITS_OCTET      gprs[32];
    ITS_OCTET      cdma[32];
    ITS_OCTET      usinfo[32];
    ITS_OCTET      uecap[32];
   

    if (ie == NULL)
    {
        return;
    }
    
    cout << setw(30) << "Old BSS To New BSS Informaiton --> ";
    cout << setiosflags(ios::left);

    switch (id)
    { 
    // Extra Information
    case BSSAP_IEI_EXTRA_INFORMATION:
        cout <<"Extra Information: " << endl;
        cout << setw(17) << " "
             << "Pre-emption Recommendation: [ " 
             << OctetToHex(((BSSAP_ExtraInfo *)ie)->GetPREC()) << "]" 
             << endl << setw(17) << " " << "Location Service: [ "
             << OctetToHex(((BSSAP_ExtraInfo *)ie)->GetLCS()) << "]" << endl;
        break;

    // Current Channel Type 2
    case BSSAP_IEI_CURRENT_CHANNEL_TYPE_2:
        cout <<"Current Channel Type 2: " << endl;
        cout << setw(17) << " " << "Channel: [ " 
             << OctetToHex(((BSSAP_CrtChan2 *)ie)->GetChan()) << "]" 
             << endl << setw(17) << " " << "Channel Mode: [ "
             << OctetToHex(((BSSAP_CrtChan2 *)ie)->GetChanMode()) << "]" << endl;
        break;

    // Target Cell Radio Information
    case BSSAP_IEI_TARGET_CELL_RADIO_INFO:
        cout <<"Target Cell Radio Information: " << endl;
        cout << setw(17) << " " << "RXLEV_NCELL: [ " 
             << OctetToHex(((BSSAP_TargetCellRadioInfo *)ie)->GetRXLEV_NCELL()) 
             << "]" << endl;
        break;

      // GPRS Suspend Information
     case BSSAP_IEI_GPRS_SUSPEND_INFO:
        cout << "GPRS Suspend Information: " << endl;
        cout << setw(17) << " " << "TLLI: [ ";
        ((BSSAP_GPRSSuspendInfo *)ie)->GetTLLI(gprs, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(gprs[i]);
        }
        cout << "]," << "  TLLI's length: " << len <<endl << endl;

        cout << setw(17) << " " << "RAI: [ ";

        ((BSSAP_GPRSSuspendInfo *)ie)->GetRAI(gprs, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(gprs[i]);
        }
        cout << "]," << "  RAI's length: " << len <<endl << endl;

        cout << setw(17) << " " << "SRN: [ ";
        ((BSSAP_GPRSSuspendInfo *)ie)->GetSRN(gprs, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(gprs[i]);
        }
        cout << "]," << "  SRN's length: " << len <<endl;
        break;


        // Multirate Configuration Information
        case BSSAP_IEI_MULTIRATE_CONFIG_INFO:
        cout <<"Multirate Configuration Information: "<<endl;
        cout << setw(17) << " " << "Satrt Mode: [ " 
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetStartMode())<<"]" 
             << endl << setw(17) << " " << "ICMI: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetICMI()) << "]"
             << endl << setw(17) << " "<<"MRVersion: [ " 
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetMRVersion()) << "]" 
             << endl << setw(17) << " " << "ARM Codec Mode 1: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode1()) << "]"
             << endl << setw(17) << " "<<"ARM Codec Mode 2: [ " 
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode2()) << "]" 
             << endl << setw(17) << " " << "ARM Codec Mode 3: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode3()) << "]" 
             << endl << setw(17) << " "<<"ARM Codec Mode 4: [ " 
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode4()) << "]" 
             << endl << setw(17) << " " << "ARM Codec Mode 5: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode5()) << "]"
             << endl << setw(17) << " " << "ARM Codec Mode 6: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode6()) << "]" 
             << endl << setw(17) << " "<<"ARM Codec Mode 7: [ " 
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode7()) << "]" 
             << endl << setw(17) << " " << "ARM Codec Mode 8: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetARMCodecMode8()) << "]"
             << endl << setw(17) << " " << "Threshold 1: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetThreshold1()) << "]"
             << endl << setw(17) << " " << "Threshold 2: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetThreshold2()) << "]"
             << endl << setw(17) << " " << "Threshold 3: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetThreshold3()) << "]"
             << endl << setw(17) << " " << "Hysteresis 1: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetHysteresis1()) << "]"
             << endl << setw(17) << " " << "Hysteresis 2: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetHysteresis2()) << "]"
             << endl << setw(17) << " " << "Hysteresis 3: [ "
             << OctetToHex(((BSSAP_MultirateConfigInfo *)ie)->GetHysteresis3()) << "]" 
             <<endl;
        break;

        // Dual Transfer Mode Information
        case BSSAP_IEI_DUAL_TRANSFER_MODE_INFO:
        cout <<"Dual Transfer Mode Information: " << endl;
        cout << setw(17) << " "
             << "DTM Indicator: [ " 
             << OctetToHex(((BSSAP_DualTransferModeInfo *)ie)->GetDTMInd()) << "]" 
             << endl << setw(17) << " " << "STO Indicator: [ "
             << OctetToHex(((BSSAP_DualTransferModeInfo *)ie)->GetSTOInd()) << "]"
             << endl << setw(17) << " " << "EGPRS Indicator: [ "
             << OctetToHex(((BSSAP_DualTransferModeInfo *)ie)->GetEGPRSInd()) << "]" 
             << endl;
        break;

     // UE Capability Information
    case BSSAP_IEI_UE_CAP_INFO:
        cout << "UE Capability Information: " << endl;
        cout << setw(17) << " " << "[ ";
        ((BSSAP_UECapInfo *)ie)->GetUECapInfo(uecap, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(uecap[i]);
        }
        cout << "]," << " UECAP's length: " << len <<endl;
    break;

    // cdma2000 Capability Information
    case BSSAP_IEI_CDMA_2000_CAP_INFO:
        cout << "cdma2000 Capability Information: " << endl;
        cout << setw(17) << " " << "[ ";
        ((BSSAP_cdma2000CapInfo *)ie)->GetcdmaCapInfo(cdma, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(cdma[i]);
        }
        cout << "]," << " CDMA's length: " << len <<endl;
    break;


        // UTRAN Pre-configuration Indication Set
        case BSSAP_IEI_UTRAN_PRECONFIG_IND_SET_INFO:
        cout <<"UTRAN Pre-configuration Indication Set: "<< endl;
        for (i = 0; i < 3; i++)
        {
            ITS_OCTET id;
            ITS_OCTET tag; 
                                
            (((BSSAP_UTRANIndicationSet *)ie)->GetPre_Config_Id_Tag(id, tag, i)); 
            cout << endl << setw(17) << " " << "Predefined id("<< i << "): [ "
                 << OctetToHex(id) <<"]"
                 << endl << setw(17) << " " << "Predefined value tag("<< i << "): [ "
                 << OctetToHex(tag) << "]" << endl << endl; 
        }
        break;

    // UE Security Information
    case BSSAP_IEI_UE_SECURITY_INFO:
        cout << "UE Security Information: " << endl;
        cout << setw(17) << " " << "[ ";
        ((BSSAP_UESecurityInfo *)ie)->GetUESecurityInfo(usinfo, len);
        for(i =0 ; i < len; i++)
        {
            cout << OctetToHex(usinfo[i]);
        }
        cout << "]," << "  USI's length: " << len <<endl;
    break;

    default:
        break;
    }
    cout << endl << endl;
    cout << resetiosflags(ios::left);
}



void DumpCellID(ITS_OCTET cidDisc, BSSAP_CellIDType cid)
{
    switch (cidDisc)
    {
    case CI_CID_CGI:
        cout << setw(17) << " " 
             << "MCC:[ " << UshortToHex(CI_CGI_GET_MCC_PCS(cid)) << "] "
             << "MNC:[ " << UshortToHex(CI_CGI_GET_MNC_PCS(cid)) << "] "
             << "LAC:[ " << UshortToHex(CI_CGI_GET_LAC(cid)) << "] "
             << "CI: [ " << UshortToHex(CI_CGI_GET_CI(cid)) << "] "
             << endl;
        break;

    case CI_CID_LAC:
        cout << setw(17) << " "
             << "LAC:[ " << UshortToHex(CI_LACCI_GET_LAC(cid)) << "] "
             << "CI:[ " << UshortToHex(CI_LACCI_GET_CI(cid)) << "] "
             << endl;            
        break;

    case CI_CID_CI:
        cout << setw(17) << " "
             << "CI:[ " << UshortToHex(CI_CI_GET_CI(cid)) << "] "
             << endl;                        
        break;

    case CI_CID_NONE:
        cout << setw(17) << " "
             << "No cell is associated with the transaction." << endl;
        break;

    case CI_CID_PLMN_LAC_RNC:
        cout << setw(17) << " " 
             << "MCC:[ " << UshortToHex(CI_PLR_GET_MCC(cid)) << "] "
             << "MNC:[ " << OctetToHex(CI_PLR_GET_MNC(cid)) << "] "
             << "LAC:[ " << UshortToHex(CI_PLR_GET_LAC(cid)) << "] "
             << "RNC-ID:[ " << UshortToHex(CI_PLR_GET_RNC_ID(cid)) << "] "
             << endl;
        break;

    case CI_CID_RNC:
        cout << setw(17) << " " 
             << "RNC-ID: [ " << UshortToHex(CI_RNC_GET_RNC_ID(cid)) << "] "
             << endl;
        break;

    case CI_CID_LAC_RNC:
        cout << setw(17) << " " 
             << "LAC:[ " << UshortToHex(CI_LR_GET_LAC(cid)) << "] "
             << "RNC-ID: [ " << UshortToHex(CI_LR_GET_RNC_ID(cid)) << "] "
             << endl;
        break;

    case CI_CID_SAI:
        cout << setw(17) << " " 
             << "MCC:[ " << UshortToHex(CI_SAI_GET_MCC(cid)) << "] "
             << "MNC:[ " << UshortToHex(CI_SAI_GET_MNC(cid)) << "] "
             << "LAC:[ " << UshortToHex(CI_SAI_GET_LAC(cid)) << "] "
             << "SAC:[ " << UshortToHex(CI_SAI_GET_SAC(cid)) << "] "
             << endl;
        break;

    default:
        cout << setw(17) << " "
             << "Invalid Cell Identifier." << endl;
        break;
    }   
}


void DumpCellIDList(ITS_OCTET cidDisc, BSSAP_CellIDT cid)
{
    switch (cidDisc)
    {
    case CIL_CID_CGI:
        cout << setw(17) << " " 
             << "MCC:[ " << UshortToHex(CIL_CGI_GET_MCC_GSM_DCS(cid)) << "] "
             << "MNC:[ " << UshortToHex(CIL_CGI_GET_MNC_GSM_DCS(cid)) << "] "
             << "LAC:[ " << UshortToHex(CIL_CGI_GET_LAC(cid)) << "] "
             << "CI: [ " << UshortToHex(CIL_CGI_GET_CI(cid)) << "] "
             << endl;
        break;

    case CIL_CID_LAC_CI:
        cout << setw(17) << " "
             << "LAC:[ " << UshortToHex(CIL_LACCI_GET_LAC(cid)) << "] "
             << "CI:[ " << UshortToHex(CIL_LACCI_GET_CI(cid)) << "] "
             << endl;            
        break;

    case CIL_CID_CI:
        cout << setw(17) << " "
             << "CI:[ " << UshortToHex(CIL_CI_GET_CI(cid)) << "] "
             << endl;                        
        break;

    case CIL_CID_NONE:
        cout << setw(17) << " "
             << "No cell is associated with the transaction." << endl;
        break;

    case CIL_CID_LAI:
        cout << setw(17) << " "
             << "MCC:[ " << UshortToHex(CIL_LAI_GET_MCC_PCS(cid)) << "] "
             << "MNC:[ " << UshortToHex(CIL_LAI_GET_MNC_PCS(cid)) << "] "
             << "LAC:[ " << UshortToHex(CIL_LAI_GET_LAC(cid)) << "] "                
             << endl;
        break;

    case CIL_CID_LAC:
        cout << setw(17) << " " 
             << "LAC:[ " << UshortToHex(CIL_LAC_GET_LAC(cid)) << "] "
             << endl;
        break;

    case CIL_CID_ALL_CELLS:
        cout << setw(17) << " " 
             << "All the cells on the BS are identified." << endl;
        break;

    case CI_CID_PLMN_LAC_RNC:
        cout << setw(17) << " " 
             << "MCC:[ " << UshortToHex(CI_PLR_GET_MCC(cid)) << "] "
             << "MNC:[ " << OctetToHex(CI_PLR_GET_MNC(cid)) << "] "
             << "LAC:[ " << UshortToHex(CI_PLR_GET_LAC(cid)) << "] "
             << "RNC-ID:[ " << UshortToHex(CI_PLR_GET_RNC_ID(cid)) << "] "
             << endl;
        break;

    case CI_CID_RNC:
        cout << setw(17) << " " 
             << "RNC-ID: [ " << UshortToHex(CI_RNC_GET_RNC_ID(cid)) << "] "
             << endl;
        break;

    case CI_CID_LAC_RNC:
        cout << setw(17) << " " 
             << "LAC:[ " << UshortToHex(CI_LR_GET_LAC(cid)) << "] "
             << "RNC-ID: [ " << UshortToHex(CI_LR_GET_RNC_ID(cid)) << "] "
             << endl;
        break;

    default:
        cout << setw(17) << " "
             << "Invalid Cell Identifier." << endl;
        break;
    }   
}


void DumpNetID(ITS_OCTET nidDisc, BSSAP_NetID nid)
{
    switch (nidDisc)
    {
    case NEI_ID_CGI:
        cout << setw(17) << " " 
             << "MCC:[ " << UshortToHex(NEI_CGI_GET_MCC(nid)) << "] "
             << "MNC:[ " << OctetToHex(NEI_CGI_GET_MNC(nid)) << "] "
             << "LAC:[ " << UshortToHex(NEI_CGI_GET_LAC(nid)) << "] "
             << "CI: [ " << UshortToHex(NEI_CGI_GET_CI(nid)) << "] "
             << endl;
        break;

    case NEI_ID_LAC_CI:
        cout << setw(17) << " "
             << "LAC:[ " << UshortToHex(NEI_LACCI_GET_LAC(nid)) << "] "
             << "CI:[ " << UshortToHex(NEI_LACCI_GET_CI(nid)) << "] "
             << endl;            
        break;

    case NEI_ID_LAI:
        cout << setw(17) << " "
             << "MCC:[ " << UshortToHex(NEI_LAI_GET_MCC(nid)) << "] "
             << "MNC:[ " << OctetToHex(NEI_LAI_GET_MNC(nid)) << "] "
             << "LAC:[ " << UshortToHex(NEI_LAI_GET_LAC(nid)) << "] "
             << endl;                        
        break;

    case NEI_ID_LAC:
        cout << setw(17) << " " 
             << "LAC:[ " << UshortToHex(NEI_LAC_GET_LAC(nid)) << "] "
             << endl;
        break;

    default:
        cout << setw(17) << " "
             << "Invalid Network Identifier." << endl;
        break;
    }   
}


string OctetToHex(ITS_OCTET b)
{
    char     strBuf[2 + 1 + 1];

    sprintf(strBuf, "%02X ", b);

    return strBuf;
}


string UshortToHex(ITS_USHORT b)
{
    char     strBuf[4 + 1 + 1];

    sprintf(strBuf, "%04X ", b);

    return strBuf;
}


string UintToHex(ITS_UINT b)
{
    char     strBuf[8 + 1 + 1];

    sprintf(strBuf, "%08X ", b);

    return strBuf;
}


#if defined(ITS_NAMESPACE)
}
#endif


