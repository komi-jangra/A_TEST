/*********************************-*-C-*-************************************
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
 *  ID: $Id: test2.cpp,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:53  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:25  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:24  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:02  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:49  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:10  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/06/13 20:02:13  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws by default.
 * LOG:
 * LOG: Revision 2.1  2000/02/02 16:14:22  mmiers
 * LOG:
 * LOG:
 * LOG: Update test with new stack mechanism.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:47  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.13  1999/10/26 14:45:20  mmiers
 * LOG:
 * LOG:
 * LOG: Commit testing changes.
 * LOG:
 * LOG: Revision 1.12  1999/07/01 15:16:45  mmiers
 * LOG:
 * LOG:
 * LOG: Use generic define for std namespace
 * LOG:
 * LOG: Revision 1.11  1998/11/13 16:56:01  mmiers
 * LOG: Add in SS7 stubs.
 * LOG:
 * LOG: Revision 1.10  1998/11/12 01:41:52  mmiers
 * LOG: Trying to straighten out SSP/SSA.
 * LOG:
 * LOG: Revision 1.17  1998/10/23 00:19:16  mmiers
 * LOG: Working on pepsy.
 * LOG:
 * LOG: Revision 1.16  1998/10/16 20:46:53  mmiers
 * LOG: Integrate in part of the MTP3 setup.  Update SCCP connection test
 * LOG: for new library.
 * LOG:
 * LOG: Revision 1.15  1998/10/15 03:30:48  mmiers
 * LOG: Add INI files for the basic tests.
 * LOG:
 * LOG: Revision 1.14  1998/07/22 15:55:25  mmiers
 * LOG: Clean this up a little.
 * LOG:
 * LOG: Revision 1.6  1998/07/21 21:29:11  mmiers
 * LOG: Update tests.
 * LOG:
 * LOG: Revision 1.5  1998/07/20 20:05:52  mmiers
 * LOG: Update to get BSC/MSC interactions working.
 * LOG:
 * LOG: Revision 1.2  1998/07/20 15:41:55  mmiers
 * LOG: Get ready to test.
 * LOG:
 * LOG: Revision 1.1  1998/07/20 15:01:07  mmiers
 * LOG: Location update test.
 * LOG:
 * LOG: Revision 1.11  1998/07/07 16:14:25  mmiers
 * LOG: Add some comments to the test prog.  This will help HNS figure out
 * LOG: what they need to modify.
 * LOG:
 * LOG: Revision 1.2  1998/07/03 19:41:40  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.1  1998/07/03 16:09:36  mmiers
 * LOG: SCCP as a thread.
 * LOG:
 * LOG: Revision 1.8  1998/06/26 15:27:33  mmiers
 * LOG: Finish up conversion to C-style transports.
 * LOG:
 * LOG: Revision 1.7  1998/06/24 16:12:28  mmiers
 * LOG: Straighten out the tranport vs. worker issues.
 * LOG:
 * LOG: Revision 1.6  1998/06/23 22:57:39  mmiers
 * LOG: SCCP debugging.
 * LOG:
 * LOG: Revision 1.5  1998/06/23 00:36:11  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/06/22 23:01:09  gkosasi
 * LOG: sccp++.h: Formatting.
 * LOG:
 * LOG: test.cpp: Gotten to the point where it runs, send CR, but IntelliSS7
 * LOG: routing isn't up to it.
 * LOG:
 * LOG: test.dsp: Add in missing libraries.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 20:40:08  gkosasi
 * LOG: All table is done
 * LOG:
 * LOG: Revision 1.2  1998/06/17 23:28:43  gkosasi
 * LOG: SCCP First table
 * LOG:
 * LOG: Revision 1.1  1998/06/15 18:39:01  gkosasi
 * LOG: Add SCCP unit test.
 * LOG:
 * LOG: Revision 1.3  1998/06/15 17:19:42  gkosasi
 * LOG: My first-modification on unit test.
 * LOG:
 * LOG: Revision 1.2  1998/06/08 20:13:53  hxing
 * LOG: Sample command.
 * LOG:
 * LOG: Revision 1.1  1998/06/08 19:50:14  mmiers
 * LOG: Add a unit tester.
 * LOG:
 *
 *****************************************************************************/

#include <its++.h>
#include <sccp++.h>

#include <UnitTest.h>
#include <its_app.h>
#include <its_transports.h>
#include <its_exception.h>
#include <its_thread.h>
#include <its_trace.h>
#include <its_semaphore.h>
#include <its_ss7_trans.h>
#include <its_ss7_stubs.h>

#define LOCAL_SSN   4
#define REMOTE_SSN  3

#define BORDER_INSTANCE 2

#if defined(ITS_NAMESPACE)
using namespace its;
#endif

#if defined(ITS_STD_NAMESPACE)
using namespace std;
#endif

class SCCP_UnitTest : public UnitTest
{
public:
    SCCP_UnitTest() : UnitTest("SCCP_UnitTest")
    {
    }

private:
    void DoCommand(istream& cmdLine);
};


ITS_HANDLE tr;
ITS_Transport *transport;
ITS_HDR shdr, rhdr;

void
PrintCredit(SCCP_Credit *credit)
{
    if (credit!=NULL)
    {
        cout << "Credit = "
             << (unsigned int)credit->GetCredit()
             << endl;
    }
    else
    {
        cout << "No credit" << endl;
    }
}

void
PrintReference(SCCP_RefNum* slr, char* which)
{
    if (slr != NULL)
    {
        cout << which
             << " Local Reference = "
             << slr->GetRefNum()
             << endl;
    }
    else 
    {
        cout << which << " Local Reference not found" << endl;
    }
}

void
PrintProtocolClass(SCCP_ProtocolClass *pc)
{
    if (pc != NULL)
    {
        cout << "Protocol Class = "
             << (unsigned int)pc->GetProtocolClass()
             << endl;
    }
    else 
    {
        cout << "No Protocol Class" << endl;
    }
}

void
PrintAddr(SCCP_Address* called_pa, char* which)
{
    cout << which << " Party Address:" << endl;

    if (called_pa != NULL)
    {
        if (called_pa->HasPointCode()) 
        {
            cout << "Point Code = "
                 << called_pa->GetPointCode()
                 << endl;
        }
        else 
        {
            cout << "No Point Code" << endl;
        }
        if (called_pa->HasSSN())
        {
            cout << "Subsystem Number = "
                 << (unsigned int)called_pa->GetSSN()
                 << endl;
        }
        else
        {
            cout << "No Subsystem Number" << endl;
        }
        if (called_pa->IsInternationalRouting())
        {
            cout << "International Routed" << endl;
        }
        else
        {
            cout << "National Routed" << endl;
        }
        if (called_pa->HasGlobalTitle())
        {
            cout << "nHas Global Title" << endl;
        }
        else
        {
            cout << "No Global Title" << endl;
        }
    }
    else
    {
        cout << "No address specified" << endl;
    }
}

void
PrintData(SCCP_UserData *ud)
{
    if (ud != NULL)
    {
        ITS_OCTET data[255];
        int len;

        cout << "UserData:" << endl;

        ud->GetUserData(data, len);
        if(len > 0)
        {
            for (int i = 0; i < len; i++)
            {
                printf("%02x ",data[i]);
                if (!((i+1) % 20))
                {
                    cout << endl;
                }
            }
            if ((i+1) % 20)
            {
                cout << endl;
            }
        }
        else
        {
            cout << "Length = 0" << endl;
        }
    }
    else
    {
        cout << "No UserData" << endl;
    }
}

void
PrintCause(SCCP_Cause* rc, char* which)
{
    if (rc != NULL) 
    {
        cout << which
             << " Cause = "
             << (unsigned int)rc->GetCause()
             << endl;
    }
    else
    {
        cout << which << " Cause not specified";
    }
}
void
PrintHopCount(SCCP_HopCount* hc)
{
    if (hc != NULL)
    {
        cout << "Hop Counter = "
             << (unsigned int)hc->GetHopCount()
             << endl;
    }
    else
    {
        cout << "No Hop Counter" << endl;
    }
}

void
PrintSegmentReassem(SCCP_SegmentReassem* sr)
{
    if (sr!=NULL) 
    {
        cout << "Segmenting/Reassembling = "
             << (unsigned int)sr->GetSegmentReassem()
             << endl;
    }
    else
    {
        cout << "Not exist" << endl;
    }
}

void
PrintSequenceSegment(SCCP_SequenceSegment* ss)
{
    if (ss != NULL)
    {
        cout << "Transmit Sequence = "
             << (unsigned int)ss->GetTransmitSequenceNumber()
             << endl;
        cout << "Receive Sequence  = "
             << (unsigned int)ss->GetReceiveSequenceNumber()
             << endl;
        cout << "Have more data    = "
             << (unsigned int)ss->GetHaveMore()
             << endl;
    }
    else
    {
        cout << "Sequence is not exist";
    }
}

void
PrintRSN(SCCP_ReceiveSequenceNum* ss)
{
    if (ss != NULL)
    {
        cout << "Receive Sequence  = "
             << (unsigned int)ss->GetReceiveSequenceNumber()
             << endl;
        cout << "Have more data    = "
             << (unsigned int)ss->GetHaveMore()
             << endl;
    }
    else 
    {
        cout << "RSN not included" << endl;
    }
}

void
SCCP_UnitTest::DoCommand(istream& cmdLine)
{
    
    if (Cmd("CR", "Connection Request Message", ""))
    {
        int ret = SCCP_GetNextLocalRef(&shdr.context.conref);
        
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        cout << "Building CR with reference number: "
             << shdr.context.conref
             << endl;

        /* Create the message */
        SCCP_ConnectionRequest cr;

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(shdr.context.conref);
        cr.AddIE(&slr);

        /* Protocol Class */
        SCCP_ProtocolClass pc(SCCP_PCLASS_2);
        cr.AddIE(&pc);

        /* Called Party Address */
        //len=3 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(0);                  //octet 3 - any
        called_pa.SetSSN(REMOTE_SSN);               //octet 2 - 0000 0001
        called_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        called_pa.SetInternationalRouting(false);   //octet 1 bit 8 
        cr.AddIE(&called_pa);

        /* Credit */                                //len=3
        SCCP_Credit credit;
        credit.SetCredit(3);
        cr.AddIE(&credit);

        /* Calling Party Address */
        SCCP_CallingPartyAddr calling_pa;           //len=4 min
        calling_pa.SetPointCode(0);
        calling_pa.SetSSN(LOCAL_SSN);
        calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        calling_pa.SetInternationalRouting(false);   //set to national
        cr.AddIE(&calling_pa);        

        /* Data */
        SCCP_UserData ud;
        int len = 100;
        ITS_OCTET data[100];
        //fill data
        for(ITS_OCTET i=0;i<len;i++)
        {
            data[i] = i;
        }
        ud.SetUserData(data, len);
        cr.AddIE(&ud);

        /* SCC hop Counter  */                      //len=3
        SCCP_HopCount hc(10);
        cr.AddIE(&hc);

        /* Send the message  */
        shdr.type = transport->GetInstance();
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &cr)
             << endl;
    }

    else if (Cmd("CC", "Connection Confirm Message", ""))
    {
        /* Create message */
        SCCP_ConnectionConfirm cc;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        cc.AddIE(&dlr);

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(shdr.context.conref);
        cc.AddIE(&slr);

        /* Protocol Class */
        SCCP_ProtocolClass pc(SCCP_PCLASS_2);
        cc.AddIE(&pc);

        /* Credit */                                //len=3
        SCCP_Credit credit;
        credit.SetCredit(20);
        cc.AddIE(&credit);
        
        /* Called Party Address */                  //len=4 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(0);                  //octet 3 - any
        called_pa.SetSSN(REMOTE_SSN);                        //octet 2 - 0000 0001
        called_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        called_pa.SetInternationalRouting(false);   //octet 1 bit 8 
        cc.AddIE(&called_pa);

        // Data                                     //len=3-130
        SCCP_UserData ud;
        int len = 100;
        ITS_OCTET data[100];
        //fill data
        for(ITS_OCTET i=0;i<len;i++)
        {
            data[i] = i;
        }
        ud.SetUserData(data, len);
        cc.AddIE(&ud);
        
        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &rhdr, &cc)
             << endl;
    }
    else if (Cmd("CREF", "Connection Refused Message", ""))
    {
        /* Build a message */
        SCCP_ConnectionRefused cr;
        cout<<"\nmsg";

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        cr.AddIE(&dlr);
        cout<<"\nslr";

        /* Refusal Cause */
        SCCP_RefusalCause rc(SCCP_REF_END_USER_ORG);
        cr.AddIE(&rc);
        cout<<"\nref cause";

        /* Called Party Address */                  //len=4 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(0);                  //1=address contains subsystem number
        called_pa.SetSSN(REMOTE_SSN);          
        called_pa.SetRouteByPCSSN(true); 
        called_pa.SetInternationalRouting(false);   //set to national
        cr.AddIE(&called_pa);
        cout<<"\ncalled pa";

        // Data 
        SCCP_UserData ud;
        int len = 100;                              //len=3-130
        ITS_OCTET data[100];
        // fill data 
        for(ITS_OCTET i=0;i<len;i++)
        {
            data[i] = i;
        }
        ud.SetUserData(data, len);
        cr.AddIE(&ud);
        cout<<"\ndata";

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &rhdr, &cr)
             << endl;
    }
        
    else if (Cmd("RLSD", "Released Message by originator", ""))
    {
        /* create a message */
        SCCP_Released rm;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        rm.AddIE(&dlr);

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(shdr.context.conref);
        rm.AddIE(&slr);

        /* Released Cause */
        SCCP_ReleaseCause rc(SCCP_RLC_END_USER_ORG);
        rm.AddIE(&rc);
        
         // Data 
        SCCP_UserData ud;
        int len = 100;                              //len=3-130
        ITS_OCTET data[100];
        // fill data 
        for(ITS_OCTET i=0;i<len;i++)
        {
            data[i] = i;
        }
        ud.SetUserData(data, len);
        rm.AddIE(&ud);
        
        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &rm)
             << endl;
    }

    else if (Cmd("RLC", "Release Complete Message", ""))
    {
        /* make a message */
        SCCP_ReleaseComplete rc;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        rc.AddIE(&dlr);

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(shdr.context.conref);
        rc.AddIE(&slr);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &rhdr, &rc)
             << endl;
    }
    
    else if (Cmd("DT1", "Data Form 1 Message", ""))
    {
        /* create a message */
        SCCP_DataForm1 df1;
        
        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        df1.AddIE(&dlr);

        /* segmenting/reassembling */
        SCCP_SegmentReassem sr(1); //more data
        /*  implementation can be changed to:
            SCCP_SegmentReassem sr();
            sr.SetSegmentReassem(1);    //0 means no data */
        df1.AddIE(&sr);
        
        /* Data */                                  //2-256
        SCCP_UserData ud;
        ITS_OCTET data[100];
        int len = 5;
        /*fill data */
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        ud.SetUserData(data, len);
        df1.AddIE(&ud);
        
        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &df1)
             << endl;
    }

    else if (Cmd("DT2", "Data Form 2 Message", ""))
    {
        /* create a message */
        SCCP_DataForm2 df2;
                
        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        df2.AddIE(&dlr);

        /* Sequencing/segmenting */
        SCCP_SequenceSegment ss(1,2,1); // tsn=1, rsn=2, haveMore=1
        df2.AddIE(&ss);

        /* Data */                                  // 2-256
        SCCP_UserData ud;
        ITS_OCTET data[150];
        int len = 5;
        /*fill data */
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        ud.SetUserData(data, len);
        df2.AddIE(&ud);
        
        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &df2)
             << endl;
    }

    else if (Cmd("AK", "Data Acknowledgement Message", ""))
    {
        /* build a message */
        SCCP_Acknowledge ack;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        ack.AddIE(&dlr);

        /* receive sequence number */
        SCCP_ReceiveSequenceNum rsn(1,0); //rsn=1, haveMore=0
        ack.AddIE(&rsn);

        /* Credit */
        SCCP_Credit credit(1);
        ack.AddIE(&credit);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &ack)
             << endl;
    }

    else if (Cmd("UDT", "Unitdata Message", ""))
    {
        ITS_HDR hdr;

        /* build a message */
        SCCP_UnitData udm;

        /* protocol class */
        SCCP_ProtocolClass pc(SCCP_PCLASS_2);
        udm.AddIE(&pc);

        /* Called Party Address */                  //len=3 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(0);                  //1=address contains subsystem number
        called_pa.SetSSN(REMOTE_SSN);          
        called_pa.SetRouteByPCSSN(false); 
        called_pa.SetInternationalRouting(false);   //set to national by default
        udm.AddIE(&called_pa);

        /* Calling Party Address */                 //len=2 min
        SCCP_CallingPartyAddr calling_pa;
        calling_pa.SetPointCode(0);
        calling_pa.SetSSN(LOCAL_SSN);
        calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        calling_pa.SetInternationalRouting(false);   //set to national
        udm.AddIE(&calling_pa);        

        /* Data */                                  //len=2-254
        SCCP_UserData ud;
        ITS_OCTET data[254];
        int len = 5;
        /*fill data */
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        ud.SetUserData(data, len);
        udm.AddIE(&ud);

        /* Send the message  */
        hdr.type = transport->GetInstance();
        hdr.context.ssn = 42;
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &hdr, &udm)
             << endl;
    }
    
    else if (Cmd("XUDT", "Extended Unitdata Message", ""))
    {
        /* build a message */
        SCCP_ExtendedUnitData eud;

        /* protocol class */
        SCCP_ProtocolClass pc(SCCP_PCLASS_3);
        eud.AddIE(&pc);

        /* SCC hop Counter  */
        SCCP_HopCount hc(15);   //initial value <16 is recommended
        eud.AddIE(&hc);

        /* Called Party Address */                  //len=3 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(0);                  //1=address contains subsystem number
        called_pa.SetSSN(REMOTE_SSN);          
        called_pa.SetRouteByPCSSN(false); 
        called_pa.SetInternationalRouting(false);   //set to national by default
        eud.AddIE(&called_pa);

        /* Calling Party Address */                 //len=2 min
        SCCP_CallingPartyAddr calling_pa;
        calling_pa.SetPointCode(0);
        calling_pa.SetSSN(LOCAL_SSN);
        calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        calling_pa.SetInternationalRouting(false);   //set to national
        eud.AddIE(&calling_pa);        

        /* Data */                                  //2-254
        SCCP_UserData ud;
        ITS_OCTET data[254];
        int len = 5;
        /*fill data */
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        ud.SetUserData(data, len);
        eud.AddIE(&ud);

        /* Send the message  */
        ITS_HDR hdr;
        hdr.type = transport->GetInstance();
        hdr.context.ssn = 42;
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &hdr, &eud)
             << endl;
    }
    
    else if (Cmd("UDTS", "Unitdata Service Message", ""))
    {
        /* build a message */
        SCCP_UnitDataService uds;

        /*return cause */
        SCCP_ReturnCause rc(SCCP_RET_NO_TRANS_ADDR_NAT);
        uds.AddIE(&rc);

        /* Called Party Address */                  //len=3 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(0);                  //1=address contains subsystem number
        called_pa.SetSSN(REMOTE_SSN);          
        called_pa.SetRouteByPCSSN(false); 
        called_pa.SetInternationalRouting(false);   //set to national by default
        uds.AddIE(&called_pa);

        /* Calling Party Address */                 //len=2 min
        SCCP_CallingPartyAddr calling_pa;
        calling_pa.SetPointCode(0);
        calling_pa.SetSSN(LOCAL_SSN);
        calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        calling_pa.SetInternationalRouting(false);   //set to national
        uds.AddIE(&calling_pa);        

        /* Data */                                  //2-254
        SCCP_UserData ud;   
        ITS_OCTET data[100];
        int len = 5;
        /*fill data */
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        ud.SetUserData(data, len);
        uds.AddIE(&ud);

        /* Send the message  */
        ITS_HDR hdr;
        hdr.type = transport->GetInstance();
        hdr.context.ssn = 42;
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &hdr, &uds)
             << endl;
    }
    
    else if (Cmd("XUDTS", "Extended Unitdata Service Message", ""))
    {
        /* build a message */
        SCCP_ExtendedUnitDataService euds;

        /*return cause */
        SCCP_ReturnCause rc(SCCP_RET_NO_TRANS_ADDR_NAT);
        euds.AddIE(&rc);

        /* SCC hop Counter  */
        SCCP_HopCount hc(15);   //initial value <16 is recommended
        euds.AddIE(&hc);

        /* Called Party Address */                  //len=3 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(0);                  //1=address contains subsystem number
        called_pa.SetSSN(REMOTE_SSN);          
        called_pa.SetRouteByPCSSN(false); 
        called_pa.SetInternationalRouting(false);   //set to national by default
        euds.AddIE(&called_pa);

        /* Calling Party Address */                 //len=2 min
        SCCP_CallingPartyAddr calling_pa;
        calling_pa.SetPointCode(0);
        calling_pa.SetSSN(LOCAL_SSN);
        calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        calling_pa.SetInternationalRouting(false);   //set to national
        euds.AddIE(&calling_pa);        

        /* Data */                                  //2-254
        SCCP_UserData ud;
        ITS_OCTET data[100];
        int len = 5;
        /*fill data */
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        ud.SetUserData(data, len);
        euds.AddIE(&ud);

        /* Send the message  */
        ITS_HDR hdr;
        hdr.type = transport->GetInstance();
        hdr.context.ssn = 42;
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &hdr, &euds)
             << endl;

    }
    
    else if (Cmd("ED", "Expedited Data Message", ""))
    {
        /* build a message */
        SCCP_ExpeditedData ed;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        ed.AddIE(&dlr);

        /* Data */                                      //2-33
        SCCP_UserData ud;
        ITS_OCTET data[20];
        int len = 5;
        /*fill data */
        data[0] = 1;
        data[1] = 2;
        data[2] = 3;
        data[3] = 4;
        data[4] = 5;
        ud.SetUserData(data, len);
        ed.AddIE(&ud);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &ed)
             << endl;
    }
    
    else if (Cmd("EA", "Expedited Data Acknowledgement Msg", ""))
    {
        /* build a message */
        SCCP_ExpeditedDataAcknowledge eda;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        eda.AddIE(&dlr);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &eda)
             << endl;
    }
    
    else if (Cmd("RSR", "Reset Request Message", ""))
    {
        /* build a message */
        SCCP_ResetRequest rr;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        rr.AddIE(&dlr);

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(shdr.context.conref);
        rr.AddIE(&slr);

        /* Reset cause */
        SCCP_ResetCause rc(SCCP_RES_END_USER_ORG);
        rr.AddIE(&rc);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &rr)
             << endl;
    }
    
    else if (Cmd("RSC", "Reset Confirm Message", ""))
    {
        /* build a message */
        SCCP_ResetConfirm rm;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(shdr.context.conref);
        rm.AddIE(&dlr);

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(rhdr.context.conref);
        rm.AddIE(&slr);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &rhdr, &rm)
             << endl;
    }
    
    else if (Cmd("ERR", "Error Message", ""))
    {
        /* build a message */
        SCCP_Error em;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        em.AddIE(&dlr);

        /* error cause */
        SCCP_ErrorCause ec(SCCP_ERR_LRN_MISS_DRN);
        em.AddIE(&ec);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &em)
             << endl;
    }
    
    else if (Cmd("IT", "Inactivity Test Message", ""))
    {
        /* build a message */
        SCCP_InactivityTest it;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(rhdr.context.conref);
        it.AddIE(&dlr);

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(shdr.context.conref);
        it.AddIE(&slr);

        /* Protocol Class */
        SCCP_ProtocolClass pc(SCCP_PCLASS_2);
        it.AddIE(&pc);
        
        /* Sequencing/segmenting */
        SCCP_SequenceSegment ss(1,2,1); // tsn=1, rsn=2, haveMore=1
        it.AddIE(&ss);

        /* Credit */
        SCCP_Credit credit(1);
        it.AddIE(&credit);

        /* Send the message  */
        cout << "Send results in: "
             << SCCP_MessageClass::Send(tr, &shdr, &it)
             << endl;
    }
    //-----------------------------------------------------------------------------------------
    else if (Cmd("RECV", "Receive Message", ""))
    {
        ITS_Event ev;
        ITS_HDR ihdr;
        SCCP_MessageClass *msg;

        if (transport->GetNextEvent(ev) != ITS_SUCCESS)
        {
            cout << endl << "An error occured!" << endl;

            return;
        }

        /* receive the message */
        int ret = SCCP_MessageClass::Receive(tr,
                                             &ihdr, ev, &msg);
                                             
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        /* dump (print) the information elements */
        switch (msg->GetMsgType())
        {
        /*------------------------------
        SCCP_Message Connection Request
        --------------------------------*/
        case SCCP_MSG_CR:
        {
            shdr = ihdr;

            // get and print source local reference
            SCCP_SourceLocalRef *slr = (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            PrintReference(slr, "Source");
            rhdr.context.conref = slr->GetRefNum();
            rhdr.type = ITS_SCCP;

            // get and print protocol class
            SCCP_ProtocolClass *pc = (SCCP_ProtocolClass *)msg->FindIE(SCCP_PRM_PROTOCOL_CLASS);
            PrintProtocolClass(pc);
            // if called party address present, print it
            SCCP_CalledPartyAddr *called_pa = (SCCP_CalledPartyAddr *)msg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
            PrintAddr(called_pa, "Called");

            // if (credit present) print credit
            SCCP_Credit *credit = (SCCP_Credit *)msg->FindIE(SCCP_PRM_CREDIT);
            PrintCredit(credit);
            
            // if calling party address present, print it
            SCCP_CallingPartyAddr *calling_pa = (SCCP_CallingPartyAddr *)msg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
            PrintAddr(calling_pa, "Calling");
            
            // Receive data
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);

            // check Hop Count
            SCCP_HopCount *hc = (SCCP_HopCount *)msg->FindIE(SCCP_PRM_HOP_COUNTER);
            PrintHopCount(hc);

        }//end case
        break;

        /*------------------------------
        SCCP_Message Connection Confirm             
        --------------------------------*/
        case SCCP_MSG_CC:
        {
            rhdr = ihdr;

            // get and print destination local reference
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");
            
            // get and print source local reference
            SCCP_SourceLocalRef *slr = (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            PrintReference(slr, "Source");

            // get and print protocol class
            SCCP_ProtocolClass *pc = (SCCP_ProtocolClass *)msg->FindIE(SCCP_PRM_PROTOCOL_CLASS);
            PrintProtocolClass(pc);

            // if (credit present) print credit
            SCCP_Credit *credit = (SCCP_Credit *)msg->FindIE(SCCP_PRM_CREDIT);
            PrintCredit(credit);
            
            // if called party address present, print it
            SCCP_CalledPartyAddr *called_pa = (SCCP_CalledPartyAddr *)msg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
            PrintAddr(called_pa, "Called");
            
            // Receive data
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;

        /*------------------------------
        Connection Refused Message
        --------------------------------*/
        case SCCP_MSG_CREF:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* refusal cause */
            SCCP_RefusalCause *rc = (SCCP_RefusalCause *)msg->FindIE(SCCP_PRM_REFUSAL_CAUSE);
            PrintCause(rc, "Refusal");

            /* if called party address present, print it */
            SCCP_CalledPartyAddr *called_pa = (SCCP_CalledPartyAddr *)msg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
            PrintAddr(called_pa, "Called");
            
            /* Receive data */
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        } //end case
        break;

        /*------------------------------
        Released Message
        --------------------------------*/
        case SCCP_MSG_RLSD:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* get and print source local reference */
            SCCP_SourceLocalRef *slr = (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            PrintReference(slr, "Source");

            /* released cause */
            SCCP_ReleaseCause *rc = (SCCP_ReleaseCause *)msg->FindIE(SCCP_PRM_RELEASE_CAUSE);
            PrintCause(rc, "Release");
            
            /* Receive data */
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        } //end case
        break;
        
        /*---------------------------
        Release Complete Messege
        -----------------------------*/
        case SCCP_MSG_RLC:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* get and print source local reference */
            SCCP_SourceLocalRef *slr = (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            PrintReference(slr, "Source");
        }
        break;

        /*---------------------------
        Data Form 1 Messege
        -----------------------------*/
        case SCCP_MSG_DT1:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* check segmenting/reassembling */
            SCCP_SegmentReassem *sr = (SCCP_SegmentReassem *)msg->FindIE(SCCP_PRM_SEGMENT_REASSEM);
            PrintSegmentReassem(sr);

            /* Receive data */
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;

        /*---------------------------
        Data Form 2 Messege
        -----------------------------*/
        case SCCP_MSG_DT2:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* sequencing/reassembling */
            SCCP_SequenceSegment *ss = (SCCP_SequenceSegment *)msg->FindIE(SCCP_PRM_SEQUENCE_SEGMENT);
            PrintSequenceSegment(ss);

            /* Receive data */
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;

        /*---------------------------
        Data Acknowledgement Messege
        -----------------------------*/
        case SCCP_MSG_AK:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");
            
            /* Receive sequence number */
            SCCP_ReceiveSequenceNum *rsn = (SCCP_ReceiveSequenceNum *)msg->FindIE(SCCP_PRM_RCV_SEQ_NUM);
            PrintRSN(rsn);

            // if (credit present) print credit
            SCCP_Credit *credit = (SCCP_Credit *)msg->FindIE(SCCP_PRM_CREDIT);
            PrintCredit(credit);
        }
        break;
        
        /*---------------------------
        Unitdata Messege
        -----------------------------*/
        case SCCP_MSG_UDT:
        {
            /* get and print protocol class */
            SCCP_ProtocolClass *pc = (SCCP_ProtocolClass *)msg->FindIE(SCCP_PRM_PROTOCOL_CLASS);
            PrintProtocolClass(pc);

            /* if called party address present, print it */
            SCCP_CalledPartyAddr *called_pa = (SCCP_CalledPartyAddr *)msg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
            PrintAddr(called_pa, "Called");

            // if calling party address present, print it
            SCCP_CallingPartyAddr *calling_pa = (SCCP_CallingPartyAddr *)msg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
            PrintAddr(calling_pa, "Calling");

            /* Receive data */
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;
        
        /*---------------------------
        Extended Unitdata Messege
        -----------------------------*/
        case SCCP_MSG_XUDT:
        {
            /* get and print protocol class */
            SCCP_ProtocolClass *pc = (SCCP_ProtocolClass *)msg->FindIE(SCCP_PRM_PROTOCOL_CLASS);
            PrintProtocolClass(pc);

            /* Hop Counter */
            SCCP_HopCount *hc = (SCCP_HopCount *)msg->FindIE(SCCP_PRM_HOP_COUNTER);
            PrintHopCount(hc);

            // if called party address present, print it
            SCCP_CalledPartyAddr *called_pa = (SCCP_CalledPartyAddr *)msg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
            PrintAddr(called_pa, "Called");
            
            // if (credit present) print credit
            SCCP_Credit *credit = (SCCP_Credit *)msg->FindIE(SCCP_PRM_CREDIT);
            PrintCredit(credit);
            
            // if calling party address present, print it
            SCCP_CallingPartyAddr *calling_pa = (SCCP_CallingPartyAddr *)msg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
            PrintAddr(calling_pa, "Calling");
            
            // Receive data
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;
        
        /*---------------------------
        Unitdata Service Messege
        -----------------------------*/
        case SCCP_MSG_UDTS:
        {
            /* check return cause */
            SCCP_ReturnCause *rc = (SCCP_ReturnCause *)msg->FindIE(SCCP_PRM_RETURN_CAUSE);
            PrintCause(rc, "Return");

            /* if called party address present, print it */
            SCCP_CalledPartyAddr *called_pa = (SCCP_CalledPartyAddr *)msg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
            PrintAddr(called_pa, "Called");
            
            // if calling party address present, print it
            SCCP_CallingPartyAddr *calling_pa = (SCCP_CallingPartyAddr *)msg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
            PrintAddr(calling_pa, "Calling");
            
            // Receive data
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;

        /*-------------------------------
        Extended Unitdata Service Messege
        ---------------------------------*/
        case SCCP_MSG_XUDTS:
        {
            /* check return cause */
            SCCP_ReturnCause *rc = (SCCP_ReturnCause *)msg->FindIE(SCCP_PRM_RETURN_CAUSE);
            PrintCause(rc, "Return");

            /* Hop Counter */
            SCCP_HopCount *hc = (SCCP_HopCount *)msg->FindIE(SCCP_PRM_HOP_COUNTER);
            PrintHopCount(hc);

            /* if called party address present, print it */
            SCCP_CalledPartyAddr *called_pa = (SCCP_CalledPartyAddr *)msg->FindIE(SCCP_PRM_CALLED_PARTY_ADDR);
            PrintAddr(called_pa, "Called");
            
            /* if calling party address present, print it */
            SCCP_CallingPartyAddr *calling_pa = (SCCP_CallingPartyAddr *)msg->FindIE(SCCP_PRM_CALLING_PARTY_ADDR);
            PrintAddr(calling_pa, "Calling");
            
            /* Receive data */
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;
        
        /*---------------------------
        Expedited Data Messege
        -----------------------------*/
        case SCCP_MSG_ED:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* Receive data */
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);
        }
        break;

        /*-------------------------------------
        Expeditede Data Acknowledgement Messege
        ---------------------------------------*/
        case SCCP_MSG_EA:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");
        }
        break;

        /*---------------------------
        Reset Request Messege
        -----------------------------*/
        case SCCP_MSG_RSR:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* get and print source local reference */
            SCCP_SourceLocalRef *slr = (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            PrintReference(slr, "Source");

            /*get reset cause */
            SCCP_ResetCause *rs = (SCCP_ResetCause *)msg->FindIE(SCCP_PRM_RESET_CAUSE);
            PrintCause(rs, "Reset");
        }
        break;

        /*---------------------------
        Reset Confirmation Messege
        -----------------------------*/
        case SCCP_MSG_RSC:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* get and print source local reference */
            SCCP_SourceLocalRef *slr = (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            PrintReference(slr, "Source");
        }
        break;

        /*---------------------------
        Error Messege
        -----------------------------*/
        case SCCP_MSG_ERR:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* get error cause */
            SCCP_ErrorCause *ec = (SCCP_ErrorCause *)msg->FindIE(SCCP_PRM_ERROR_CAUSE);
            PrintCause(ec, "Error");
        }
        break;

        /*---------------------------
        Inactivity Test Message 
        -----------------------------*/
        case SCCP_MSG_IT:
        {
            /* get and print destination local reference */
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)msg->FindIE(SCCP_PRM_DEST_LOCAL_REF);
            PrintReference(dlr, "Destination");

            /* get and print source local reference */
            SCCP_SourceLocalRef *slr = (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
            PrintReference(slr, "Source");
            
            // get and print protocol class
            SCCP_ProtocolClass *pc = (SCCP_ProtocolClass *)msg->FindIE(SCCP_PRM_PROTOCOL_CLASS);
            PrintProtocolClass(pc);

            /* sequencing/reassembling */
            SCCP_SequenceSegment *ss = (SCCP_SequenceSegment *)msg->FindIE(SCCP_PRM_SEQUENCE_SEGMENT);
            PrintSequenceSegment(ss);

            // if (credit present) print credit
            SCCP_Credit *credit = (SCCP_Credit *)msg->FindIE(SCCP_PRM_CREDIT);
            PrintCredit(credit);
        }
        break;

        
        } //end switch

        delete msg;

    } //end else if
}

ITS_Semaphore   sem(0);

#if defined(WIN32)
static unsigned __stdcall
#else
static void *
#endif
Dispatch(void *arg)
{
    ITS_Transport* tr;
    ITS_Event ev;
    ITS_HANDLE hd;

    // Build our border transport.  All extra-process messages will
    // come in on this transport.
    if ((hd = (ITS_Transport *)ITS_Initialize(ITS_TRANSPORT_FIFO|ITS_SCCP|
                                              ITS_TRANSPORT_SINGLE_USER,
                                              BORDER_INSTANCE)) == NULL)
    {
        exit(0);
    }

    // tell the main loop that execution can proceed.
    sem.Post();

    // convert the handle to a transport.
    tr = ITS_HANDLE_TO_ITS_TRANSPORT(hd);

    while (tr->GetNextEvent(ev) == ITS_SUCCESS)
    {
        // if the event source is marked as our source,
        // somebody is telling us to terminate our message loop.
        if (ev.GetSource() == BORDER_INSTANCE)
        {
            ev.SetSource(BORDER_INSTANCE);
            ev.SetLength(0);
            ITS_Transport::PutEvent(BORDER_INSTANCE, ev);

            break;
        }

        // mark the event source as self in order to satisfy
        // the automatic routing subsystem.
        ev.SetSource(ITS_MTP3_SRC);

        // Send the message to SCCP for context management.
        // SCCP will then use the automatic routing system
        // to send the message to our application queue.
        ITS_Transport::PutEvent(ITS_SCCP_SRC, ev);
    }

    ITS_Terminate(hd);

#if defined(WIN32)
    return (0);
#else
    return (NULL);
#endif
}

int
main()
{
    SCCP_UnitTest test;
    ITS_HANDLE hd;
    ITS_Thread* thr = new ITS_Thread(0, Dispatch); // border transport thread
    ITS_Event ev;

    // TRACE_TurnDebugTraceOnOff(ITS_FALSE);

    ITS_Application::SetName("Test2");

    // using our stack, so add that feature
    if (ITS_AddFeature(itsINTELLISS7_Class) != ITS_SUCCESS)
    {
        printf("Failed to add stack feature.\n");
        exit(0);
    }

    // build the application queue.
    if (ITS_GlobalStart(ITS_SCCP) != ITS_SUCCESS)
    {
        printf("Global start failed.\n");
        exit(0);
    }

    if ((hd = (ITS_Transport *)ITS_Initialize(ITS_SCCP|ITS_TRANSPORT_TQUEUE|
                                              ITS_TRANSPORT_SINGLE_USER, 1)) == NULL)
    {
        cerr << "Couldn't create the transport." << endl;

        return 0;
    }

    // start the border transport thread
    thr->Enter(NULL);

    // wait for it to tell us it is started.
    sem.Wait();

    // recover our transport handle from the ITS_HANDLE
    tr = hd;
    transport = ITS_HANDLE_TO_ITS_TRANSPORT(hd);

    ITS_THROW_ASSERT(transport != NULL);

    SCCP_SendUserInService(hd, 0, 3);

    // enter test loop
    test.ExecuteCommandsFromStream();

    // build/send the termination message for the border transport thread.
    ev.SetSource(BORDER_INSTANCE);
    ev.SetLength(0);
    ITS_Transport::PutEvent(BORDER_INSTANCE, ev);

    // wait for the border transport thread to exit.
    void *status;
    thr->WaitFor(&status);

    // cleanup the thread
    delete thr;

    // cleanup our task queue.
    ITS_Terminate(hd);

    ITS_GlobalStop();

    return 0;
}

