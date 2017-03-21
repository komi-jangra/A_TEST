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
 *     FILE: sccp.h                                                         *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: sccp++.h,v 1.2 2008-02-05 21:35:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:24  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:52  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/24 05:50:36  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.3  2007/06/04 04:07:54  ashutosh.singh
 * LOG: for IMPORTANCE PARM in RLSD
 * LOG:
 * LOG: Revision 1.2  2007/05/28 10:19:13  ashutosh.singh
 * LOG: Change for IMPORTANCE Handling in RLSD
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:33:55  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:20  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.44.1  2004/12/16 02:22:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.40.1  2004/10/08 23:39:46  randresol
 * LOG: Start Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/20 16:52:39  mmiers
 * LOG: Second try
 * LOG:
 * LOG: Revision 6.2  2002/08/20 16:37:05  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2001/09/28 21:57:37  labuser
 * LOG: Fixed typo introduced when adding LongData to C++ API.
 * LOG:
 * LOG: Revision 5.3  2001/08/30 15:09:38  labuser
 * LOG: More changes to the cpp API to fit LONG_DATA.
 * LOG:
 * LOG: Revision 5.2  2001/08/28 21:52:29  labuser
 * LOG: Add LUDT, LUDTS, LONG_DATA classes to current.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:47  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/27 22:57:41  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.2  2001/06/26 17:29:40  mmiers
 * LOG: Link time workarounds.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:01  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/06/13 20:02:11  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws by default.
 * LOG:
 * LOG: Revision 2.1  1999/12/30 18:33:19  mmiers
 * LOG:
 * LOG:
 * LOG: Set the booleans on decode.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:35  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.23  1999/08/30 15:53:27  mmiers
 * LOG:
 * LOG:
 * LOG: Essentially satisfies Hubert's objections to the OO model.
 * LOG:
 * LOG: Revision 1.22  1999/08/30 14:20:14  mmiers
 * LOG:
 * LOG:
 * LOG: Add method.
 * LOG:
 * LOG: Revision 1.21  1999/08/30 14:15:45  mmiers
 * LOG:
 * LOG:
 * LOG: Initializer value correction.
 * LOG:
 * LOG: Revision 1.20  1999/08/30 02:22:02  mmiers
 * LOG:
 * LOG:
 * LOG: Bullet proofing round 2.
 * LOG:
 * LOG: Revision 1.19  1999/08/30 02:10:07  mmiers
 * LOG:
 * LOG:
 * LOG: Bullet proofing.
 * LOG:
 * LOG: Revision 1.18  1999/07/29 16:27:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add basic type ITS_ByteArray (template vector<ITS_OCTET>).
 * LOG:
 * LOG: Revision 1.17  1999/02/12 23:40:22  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for simultaneous protocol families.
 * LOG:
 * LOG: Revision 1.16  1998/11/12 00:55:34  mmiers
 * LOG: Add GTT to C++.
 * LOG:
 * LOG: Revision 1.15  1998/10/15 23:15:27  mmiers
 * LOG: Add C++ for MTP3.  Add routing label to SCCP.
 * LOG:
 * LOG: Revision 1.14  1998/09/28 23:16:23  mmiers
 * LOG: Add assignment operators for SourceLocalRef/DestinationLocalRef,
 * LOG: CalledPartyAddr/CallingPartyAddr for convenience.
 * LOG:
 * LOG: Revision 1.13  1998/09/26 22:36:56  mmiers
 * LOG: Convert to using message format descriptors.  ISUP needs something like
 * LOG: this as well, for many of the same reasons.
 * LOG:
 * LOG: Revision 1.12  1998/09/22 23:56:28  jrao
 * LOG: Changes made to accomodate HPUX code
 * LOG:
 * LOG: Revision 1.11  1998/08/11 14:56:21  mmiers
 * LOG: Add const modifiers so people know not to delete what they get from
 * LOG: FindIE.
 * LOG:
 * LOG: Revision 1.10  1998/06/23 00:36:10  mmiers
 * LOG: Debugging SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/06/22 23:01:08  gkosasi
 * LOG: sccp++.h: Formatting.
 * LOG:
 * LOG: test.cpp: Gotten to the point where it runs, send CR, but IntelliSS7
 * LOG: routing isn't up to it.
 * LOG:
 * LOG: test.dsp: Add in missing libraries.
 * LOG:
 * LOG: Revision 1.8  1998/06/03 17:14:32  mmiers
 * LOG: Guess what's left.  IS634.
 * LOG:
 * LOG: Revision 1.7  1998/06/01 22:31:57  mmiers
 * LOG: Raw documentation for SCCP.
 * LOG:
 * LOG: Revision 1.6  1998/06/01 17:01:55  mmiers
 * LOG: Show formatting.  Start Hongling on this for IS634.
 * LOG:
 * LOG: Revision 1.5  1998/06/01 16:35:11  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 17:11:41  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.3  1998/05/15 17:24:36  mmiers
 * LOG: Finish SCCP++.  More work on TCAP++.
 * LOG:
 * LOG: Revision 1.2  1998/05/14 23:55:15  mmiers
 * LOG: C++ binding for SCCP is *almost* complete.  Hope to knock off the
 * LOG: same for TCAP tonight.
 * LOG:
 * LOG: Revision 1.1  1998/05/06 21:26:49  mmiers
 * LOG: Continue working on IS634 and SCCP.  Add C++ bindings for IS634
 * LOG: SCCP, and TCAP.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_SCCP_PP_H
#define ITS_SCCP_PP_H

#include <its++.h>

#if defined(CCITT)
#include <itu/sccp.h>

#define SCCP_IEClass                    SCCP_IEClass_CCITT
#define SCCP_MessageClass               SCCP_MessageClass_CCITT

#define SCCP_RefNum                     SCCP_RefNum_CCITT
#define SCCP_SourceLocalRef             SCCP_SourceLocalRef_CCITT
#define SCCP_DestinationLocalRef        SCCP_DestinationLocalRef_CCITT
#define SCCP_Credit                     SCCP_Credit_CCITT
#define SCCP_Address                    SCCP_Address_CCITT
#define SCCP_CallingPartyAddress        SCCP_CallingPartyAddress_CCITT
#define SCCP_CalledPartyAddress         SCCP_CalledPartyAddress_CCITT
#define SCCP_ProtocolClass              SCCP_ProtocolClass_CCITT
#define SCCP_SegmentReassem             SCCP_SegmentReassem_CCITT
#define SCCP_SequenceSegment            SCCP_SequenceSegment_CCITT
#define SCCP_ReceiveSequenceNum         SCCP_ReceiveSequenceNum_CCITT
#define SCCP_Cause                      SCCP_Cause_CCITT
#define SCCP_ReleaseCause               SCCP_ReleaseCause_CCITT
#define SCCP_ReturnCause                SCCP_ReturnCause_CCITT
#define SCCP_ResetCause                 SCCP_ResetCause_CCITT
#define SCCP_ErrorCause                 SCCP_ErrorCause_CCITT
#define SCCP_RefusalCause               SCCP_RefusalCause_CCITT
#define SCCP_UserData                   SCCP_UserData_CCITT
#define SCCP_HopCount                   SCCP_HopCount_CCITT

#define SCCP_ConnectionRequest          SCCP_ConnectionRequest_CCITT
#define SCCP_ConnectionConfirmed        SCCP_ConnectionConfirmed_CCITT
#define SCCP_ConnectionRefused          SCCP_ConnectionRefused_CCITT
#define SCCP_Released                   SCCP_Released_CCITT
#define SCCP_ReleaseComplete            SCCP_ReleaseComplete_CCITT
#define SCCP_DataForm1                  SCCP_DataForm1_CCITT
#define SCCP_DataForm2                  SCCP_DataForm2_CCITT
#define SCCP_Acknowledge                SCCP_Acknowledge_CCITT
#define SCCP_UnitData                   SCCP_UnitData_CCITT
#define SCCP_ExtendedUnitData           SCCP_ExtendedUnitData_CCITT
#define SCCP_UnitDataService            SCCP_UnitDataService_CCITT
#define SCCP_ExtendedUnitDataService    SCCP_ExtendedUnitDataService_CCITT
#define SCCP_ExpeditedData              SCCP_ExpeditedData_CCITT
#define SCCP_ExpeditedDataAcknowledge   SCCP_ExpeditedDataAcknowledge_CCITT
#define SCCP_ResetRequest               SCCP_ResetRequest_CCITT
#define SCCP_ResetConfirm               SCCP_ResetConfirm_CCITT
#define SCCP_Error                      SCCP_Error_CCITT
#define SCCP_InactivityTest             SCCP_InactivityTest_CCITT
#define SCCP_LongUnitData               SCCP_LongUnitData_CCITT
#define SCCP_LongUnitDataService        SCCP_LongUnitDataService_CCITT

#elif defined(ANSI)
#include <ansi/sccp.h>

#define SCCP_IEClass                    SCCP_IEClass_ANSI
#define SCCP_MessageClass               SCCP_MessageClass_ANSI

#define SCCP_RefNum                     SCCP_RefNum_ANSI
#define SCCP_SourceLocalRef             SCCP_SourceLocalRef_ANSI
#define SCCP_DestinationLocalRef        SCCP_DestinationLocalRef_ANSI
#define SCCP_Credit                     SCCP_Credit_ANSI
#define SCCP_Address                    SCCP_Address_ANSI
#define SCCP_CallingPartyAddress        SCCP_CallingPartyAddress_ANSI
#define SCCP_CalledPartyAddress         SCCP_CalledPartyAddress_ANSI
#define SCCP_ProtocolClass              SCCP_ProtocolClass_ANSI
#define SCCP_SegmentReassem             SCCP_SegmentReassem_ANSI
#define SCCP_SequenceSegment            SCCP_SequenceSegment_ANSI
#define SCCP_ReceiveSequenceNum         SCCP_ReceiveSequenceNum_ANSI
#define SCCP_Cause                      SCCP_Cause_ANSI
#define SCCP_ReleaseCause               SCCP_ReleaseCause_ANSI
#define SCCP_ReturnCause                SCCP_ReturnCause_ANSI
#define SCCP_ResetCause                 SCCP_ResetCause_ANSI
#define SCCP_ErrorCause                 SCCP_ErrorCause_ANSI
#define SCCP_RefusalCause               SCCP_RefusalCause_ANSI
#define SCCP_UserData                   SCCP_UserData_ANSI
#define SCCP_HopCount                   SCCP_HopCount_ANSI

#define SCCP_ConnectionRequest          SCCP_ConnectionRequest_ANSI
#define SCCP_ConnectionConfirmed        SCCP_ConnectionConfirmed_ANSI
#define SCCP_ConnectionRefused          SCCP_ConnectionRefused_ANSI
#define SCCP_Released                   SCCP_Released_ANSI
#define SCCP_ReleaseComplete            SCCP_ReleaseComplete_ANSI
#define SCCP_DataForm1                  SCCP_DataForm1_ANSI
#define SCCP_DataForm2                  SCCP_DataForm2_ANSI
#define SCCP_Acknowledge                SCCP_Acknowledge_ANSI
#define SCCP_UnitData                   SCCP_UnitData_ANSI
#define SCCP_ExtendedUnitData           SCCP_ExtendedUnitData_ANSI
#define SCCP_UnitDataService            SCCP_UnitDataService_ANSI
#define SCCP_ExtendedUnitDataService    SCCP_ExtendedUnitDataService_ANSI
#define SCCP_ExpeditedData              SCCP_ExpeditedData_ANSI
#define SCCP_ExpeditedDataAcknowledge   SCCP_ExpeditedDataAcknowledge_ANSI
#define SCCP_ResetRequest               SCCP_ResetRequest_ANSI
#define SCCP_ResetConfirm               SCCP_ResetConfirm_ANSI
#define SCCP_Error                      SCCP_Error_ANSI
#define SCCP_InactivityTest             SCCP_InactivityTest_ANSI
#define SCCP_LongUnitData               SCCP_LongUnitData_ANSI
#define SCCP_LongUnitDataService        SCCP_LongUnitDataService_ANSI

#elif defined(PRC)
#include <china/sccp.h>

#define SCCP_IEClass                    SCCP_IEClass_PRC
#define SCCP_MessageClass               SCCP_MessageClass_PRC

#define SCCP_RefNum                     SCCP_RefNum_PRC
#define SCCP_SourceLocalRef             SCCP_SourceLocalRef_PRC
#define SCCP_DestinationLocalRef        SCCP_DestinationLocalRef_PRC
#define SCCP_Credit                     SCCP_Credit_PRC
#define SCCP_Address                    SCCP_Address_PRC
#define SCCP_CallingPartyAddress        SCCP_CallingPartyAddress_PRC
#define SCCP_CalledPartyAddress         SCCP_CalledPartyAddress_PRC
#define SCCP_ProtocolClass              SCCP_ProtocolClass_PRC
#define SCCP_SegmentReassem             SCCP_SegmentReassem_PRC
#define SCCP_SequenceSegment            SCCP_SequenceSegment_PRC
#define SCCP_ReceiveSequenceNum         SCCP_ReceiveSequenceNum_PRC
#define SCCP_Cause                      SCCP_Cause_PRC
#define SCCP_ReleaseCause               SCCP_ReleaseCause_PRC
#define SCCP_ReturnCause                SCCP_ReturnCause_PRC
#define SCCP_ResetCause                 SCCP_ResetCause_PRC
#define SCCP_ErrorCause                 SCCP_ErrorCause_PRC
#define SCCP_RefusalCause               SCCP_RefusalCause_PRC
#define SCCP_UserData                   SCCP_UserData_PRC
#define SCCP_HopCount                   SCCP_HopCount_PRC

#define SCCP_ConnectionRequest          SCCP_ConnectionRequest_PRC
#define SCCP_ConnectionConfirmed        SCCP_ConnectionConfirmed_PRC
#define SCCP_ConnectionRefused          SCCP_ConnectionRefused_PRC
#define SCCP_Released                   SCCP_Released_PRC
#define SCCP_ReleaseComplete            SCCP_ReleaseComplete_PRC
#define SCCP_DataForm1                  SCCP_DataForm1_PRC
#define SCCP_DataForm2                  SCCP_DataForm2_PRC
#define SCCP_Acknowledge                SCCP_Acknowledge_PRC
#define SCCP_UnitData                   SCCP_UnitData_PRC
#define SCCP_ExtendedUnitData           SCCP_ExtendedUnitData_PRC
#define SCCP_UnitDataService            SCCP_UnitDataService_PRC
#define SCCP_ExtendedUnitDataService    SCCP_ExtendedUnitDataService_PRC
#define SCCP_ExpeditedData              SCCP_ExpeditedData_PRC
#define SCCP_ExpeditedDataAcknowledge   SCCP_ExpeditedDataAcknowledge_PRC
#define SCCP_ResetRequest               SCCP_ResetRequest_PRC
#define SCCP_ResetConfirm               SCCP_ResetConfirm_PRC
#define SCCP_Error                      SCCP_Error_PRC
#define SCCP_InactivityTest             SCCP_InactivityTest_PRC
#define SCCP_LongUnitData               SCCP_LongUnitData_PRC
#define SCCP_LongUnitDataService        SCCP_LongUnitDataService_PRC

#elif defined(TTC)
#include <japan/sccp.h>

#define SCCP_IEClass                    SCCP_IEClass_TTC
#define SCCP_MessageClass               SCCP_MessageClass_TTC

#define SCCP_RefNum                     SCCP_RefNum_TTC
#define SCCP_SourceLocalRef             SCCP_SourceLocalRef_TTC
#define SCCP_DestinationLocalRef        SCCP_DestinationLocalRef_TTC
#define SCCP_Credit                     SCCP_Credit_TTC
#define SCCP_Address                    SCCP_Address_TTC
#define SCCP_CallingPartyAddress        SCCP_CallingPartyAddress_TTC
#define SCCP_CalledPartyAddress         SCCP_CalledPartyAddress_TTC
#define SCCP_ProtocolClass              SCCP_ProtocolClass_TTC
#define SCCP_SegmentReassem             SCCP_SegmentReassem_TTC
#define SCCP_SequenceSegment            SCCP_SequenceSegment_TTC
#define SCCP_ReceiveSequenceNum         SCCP_ReceiveSequenceNum_TTC
#define SCCP_Cause                      SCCP_Cause_TTC
#define SCCP_ReleaseCause               SCCP_ReleaseCause_TTC
#define SCCP_ReturnCause                SCCP_ReturnCause_TTC
#define SCCP_ResetCause                 SCCP_ResetCause_TTC
#define SCCP_ErrorCause                 SCCP_ErrorCause_TTC
#define SCCP_RefusalCause               SCCP_RefusalCause_TTC
#define SCCP_UserData                   SCCP_UserData_TTC
#define SCCP_HopCount                   SCCP_HopCount_TTC

#define SCCP_ConnectionRequest          SCCP_ConnectionRequest_TTC
#define SCCP_ConnectionConfirmed        SCCP_ConnectionConfirmed_TTC
#define SCCP_ConnectionRefused          SCCP_ConnectionRefused_TTC
#define SCCP_Released                   SCCP_Released_TTC
#define SCCP_ReleaseComplete            SCCP_ReleaseComplete_TTC
#define SCCP_DataForm1                  SCCP_DataForm1_TTC
#define SCCP_DataForm2                  SCCP_DataForm2_TTC
#define SCCP_Acknowledge                SCCP_Acknowledge_TTC
#define SCCP_UnitData                   SCCP_UnitData_TTC
#define SCCP_ExtendedUnitData           SCCP_ExtendedUnitData_TTC
#define SCCP_UnitDataService            SCCP_UnitDataService_TTC
#define SCCP_ExtendedUnitDataService    SCCP_ExtendedUnitDataService_TTC
#define SCCP_ExpeditedData              SCCP_ExpeditedData_TTC
#define SCCP_ExpeditedDataAcknowledge   SCCP_ExpeditedDataAcknowledge_TTC
#define SCCP_ResetRequest               SCCP_ResetRequest_TTC
#define SCCP_ResetConfirm               SCCP_ResetConfirm_TTC
#define SCCP_Error                      SCCP_Error_TTC
#define SCCP_InactivityTest             SCCP_InactivityTest_TTC
#define SCCP_LongUnitData               SCCP_LongUnitData_TTC
#define SCCP_LongUnitDataService        SCCP_LongUnitDataService_TTC


#else
#error Protocol family not defined
#endif

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#include <mtp3++.h>

#include <map>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:SCCP_IEClass
 *****************************************************************************
 *  Interface:
 *      SCCP_IEClass
 *
 *  Purpose:
 *      This class defines the basic interface for all IE(s).  All SCCP IE
 *      concrete classes are derived from this base class.
 *
 *  Usage:
 *      This class is abstract (cannot be instantiated).
 *
 *****************************************************************************/
  class SCCP_IEClass
  {
  public:
    friend class SCCP_MessageClass;

    /*.implementation:public,inline,SCCP_IEClass
     ************************************************************************
     *  Purpose:
     *      This method constructs an SCCP_IEClass object.
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
     *  Notes:
     *      This is the default constructor.
     *
     *  See Also:
     *      ~SCCP_IEClass()
     ************************************************************************/
    SCCP_IEClass ()
    {
    }
    /*.implementation:public,inline,SCCP_IEClass
     ************************************************************************
     *  Purpose:
     *      This method constructs an SCCP_IEClass object, copying an
     *      ITS_SCCP_IE into the "ie" member variable.
     *
     *  Input Parameters:
     *      ie - the ITS_SCCP_IE to copy
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
     *  Notes:
     *
     *  See Also:
     *      ~SCCP_IEClass()
     ************************************************************************/
    SCCP_IEClass (const ITS_SCCP_IE _ie)
    {
      ie = _ie;
    }
    /*.implementation:public,inline,SCCP_IEClass
     ************************************************************************
     *  Purpose:
     *      This method destroys an instance of an SCCP_IEClass
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
     *  Notes:
     *
     *  See Also:
     *      SCCP_IEClass()
     ************************************************************************/
    virtual ~ SCCP_IEClass ()
    {
    }

    /*.implementation:public,inline,SCCP_IEClass
     ************************************************************************
     *  Purpose:
     *      This method returns the information element identifer for
     *      derivative class instances.
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
     *      The information element identifer for this SCCP_IEClass derivative.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetID ()const
    {
      return ie.param_id;
    }

  protected:
    /*.implementation:protected,abstract,SCCP_IEClass
     ************************************************************************
     *  Purpose:
     *      This abstract method defines the interface for encoding an
     *      SCCP_IEClass derivative into an OCTET buffer.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - the buffer to construct into
     *      len - the length of the constructed buffer
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
      virtual int Encode (ITS_OCTET * buf, int &len) const = 0;
    /*.implementation:protected,abstract,SCCP_IEClass
     ************************************************************************
     *  Purpose:
     *      This method defines the interface for decoding an octet buffer
     *      into an SCCP_IEClass object.
     *
     *  Input Parameters:
     *      buf - the ITE_OCTET buffer to decode.
     *
     *  Input/Output Parameters:
     *      len - the length of the buffer.  The value returned is the
     *          actual decode length.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET *, int &len) = 0;

    /*.implementation:protected,inline,SCCP_IEClass
     ************************************************************************
     *  Purpose:
     *      This method defines the interface for cloning an SCCP_IEClass
     *      object.
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
     *      A pointer to an allocated region containing a clone of this
     *          object.
     *
     *  Notes:
     *      Implementations of this method may throw exceptions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone () = 0;

    /* data member */
    ITS_SCCP_IE ie;
  };

/*.interface:SCCP_MessageClass
 *****************************************************************************
 *  Interface:
 *      SCCP_MessageClass
 *
 *  Purpose:
 *      This class defines the basic interface for all SCCP messages.  All
 *      SCCP message concrete classes are derived from this base class.
 *
 *  Usage:
 *      This class is not abstract, but has little use standalone except
 *      for decoded messages.  Objects of this class cannot be copied.
 *
 *****************************************************************************/
  class SCCP_MessageClass:public MTP3_Header
  {
  public:
    typedef std::map < ITS_OCTET, SCCP_IEClass * >SCCP_IEMap;

      SCCP_MessageClass (const ITS_OCTET msgType,
			 const SCCP_MSG_DESC & d):mType (msgType),
      haveMsgType (true), desc (d)
    {
      SetNetworkIndicator (true);
      SetPriority (0);
      SetUserPart (MTP3_SIO_SCCP);
      SetSLS (0);
    }

    virtual ~ SCCP_MessageClass ()
    {
      SCCP_IEMap::iterator i;

      for (i = ies.begin (); i != ies.end (); ++i)
	{
	  delete i->second;
	}
    }

    /*.implementation:public,inline,SCCP_MessageClass
     ************************************************************************
     *  Purpose:
     *      This method sends an SCCP_MessageClass object to SCCP.
     *
     *  Input Parameters:
     *      handle - the transport handle to send on
     *      hdr - the context for this message
     *      msg - a pointer to the SCCP_MessageClass object to send
     *
     *  Return Value:
     *      If the message is successfully transmitted, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      This method is static.
     *
     *  See Also:
     *      Receive()
     ************************************************************************/
    static inline int
      Send (ITS_HANDLE handle, ITS_HDR * hdr, SCCP_MessageClass * msg)
    {
      SCCP_IEMap::iterator i;
      ITS_SCCP_IE ies[ITS_MAX_SCCP_IES];
      int count = 0;
      int len = 0;

      for (i = msg->ies.begin (); i != msg->ies.end (); ++i)
	{
	  if (count > ITS_MAX_SCCP_IES)
	    {
	      return (ITS_EOVERFLOW);
	    }

	  ies[count].param_id = i->second->GetID ();

	  if (ies[count].param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
	      ies[count].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
	    {
	      ITS_THROW_ASSERT (i->second->Encode ((ITS_OCTET *) & ies[count].
						   param_data.
						   callingPartyAddr.data,
						   len) == ITS_SUCCESS);

	      ies[count].param_data.callingPartyAddr.len = len;
	    }
	  else if (ies[count].param_id == SCCP_PRM_LONG_DATA)
	    {
	      ITS_THROW_ASSERT (i->second->Encode ((ITS_OCTET *) & ies[count].
						   param_data.longData.data,
						   len) == ITS_SUCCESS);

	      ies[count].param_data.longData.len = len;
	    }
	  else
	    {
	      ITS_THROW_ASSERT (i->second->
				Encode ((ITS_OCTET *) & ies[count].param_data,
					len) == ITS_SUCCESS);
	    }

	  ies[count].param_length = len;

	  count++;
	}

      ies[count].param_id = SCCP_PRM_ROUTING_LABEL;
      ies[count].param_length = sizeof (MTP3_HEADER);
      ies[count].param_data.routingLabel = msg->GetHeader ();
      count++;

      return SCCP_SendEvent (handle, msg->GetMsgType (), hdr,
			     ies, count,
			     &const_cast < SCCP_MSG_DESC & >(msg->desc));
    }

    static int Receive (ITS_HANDLE handle, ITS_HDR * hdr,
			its::Event &, SCCP_MessageClass **);

    /*.implementation:public,inline,SCCP_MessageClass
     ************************************************************************
     *  Purpose:
     *      This method provides the user a way to add information elements
     *      to an SCCP_MessageClass derivative.
     *
     *  Input Parameters:
     *      ie - a pointer to the SCCP_IE to clone into the IE list.
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
     *  Notes:
     *      If an element of this type is already in the list, the pointer
     *      to that element will be overwritten.  In such circumstances,
     *      this will leak memory.  You are advised to call FindIE() and
     *      delete the result (if non-NULL) before overwriting an entry.
     *
     *  See Also:
     *      FindIE()
     ************************************************************************/
    virtual void AddIE (SCCP_IEClass * ie)
    {
      ies[ie->GetID ()] = ie->Clone ();
    }

    /*.implementation:public,inline,SCCP_MessageClass
     ************************************************************************
     *  Purpose:
     *      This method provides the user with a way to fetch individual
     *      information elements from an SCCP_MessageClass derivative.
     *
     *  Input Parameters:
     *      id - the information element identifer to look for.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      A pointer to an SCCP_IEClass derivative, if present.
     *      NULL if no such IE id is found in the list.
     *
     *  Notes:
     *      Do NOT delete the returned object.  The destructor for this
     *      class will free objects in the list; if the user has already
     *      deleted an object returned by this method, the destructor
     *      will attempt to free the object a second time.
     *
     *  See Also:
     *      AddIE()
     ************************************************************************/
    const SCCP_IEClass *FindIE (ITS_OCTET id)
    {
      return ies[id];
    }

    /*.implementation:public,inline,SCCP_MessageClass
     ************************************************************************
     *  Purpose:
     *      This method provides the user with a way to determine the
     *      if the SCCP message type for derivatives of this class has
     *      been set.
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
     *      true - the type has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     *      SetMsgType()
     ************************************************************************/
    bool HasMsgType ()const
    {
      return haveMsgType;
    }
    /*.implementation:public,inline,SCCP_MessageClass
     ************************************************************************
     *  Purpose:
     *      This method provides the user with a way to determine the
     *      SCCP message type for derivatives of this class.
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
     *      An ITS_OCTET value containing the message type for this object.
     *
     *  Notes:
     *
     *  See Also:
     *      SetMsgType()
     ************************************************************************/
    ITS_OCTET GetMsgType () const
    {
      ITS_THROW_ASSERT (haveMsgType);

      return mType;
    }
    /*.implementation:public,inline,SCCP_MessageClass
     ************************************************************************
     *  Purpose:
     *      This method provides the user with a way to set the message type
     *      for a derivative of this class.
     *
     *  Input Parameters:
     *      msgType - the value to set the message type of this object to.
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
     *  Notes:
     *      This method is provided for completeness only.  When creating
     *      messages for sending, the derivatives of this class automatically
     *      set the message type.  When receiving derivatives, the message
     *      type is again automatically set.
     *
     *  See Also:
     ************************************************************************/
    void SetMsgType (const ITS_OCTET msgType)
    {
      mType = msgType;
      haveMsgType = true;
    }

  protected:
    SCCP_IEMap ies;
    ITS_OCTET mType;
    bool haveMsgType;

    const SCCP_MSG_DESC & desc;

  private:
  SCCP_MessageClass ():mType (0), desc (SCCP_MSG_DESC ())
    {
    }
  SCCP_MessageClass (SCCP_MessageClass &):mType (0),
      desc (SCCP_MSG_DESC ())
    {
    }
    SCCP_MessageClass & operator= (SCCP_MessageClass &)
    {
      return *this;
    }
  };

///////////////////////////////////////////////////////////////////////
//
// All IEs
//
///////////////////////////////////////////////////////////////////////

/*.interface:SCCP_RefNum
 *****************************************************************************
 *  Interface:
 *      SCCP_RefNum
 *
 *  Purpose:
 *      This class represents an intermediate form for reference numbers.
 *
 *  Usage:
 *      The true reference number classes (source and destination) are
 *      derived from this class.  This class is not intended for general
 *      use.
 *
 *****************************************************************************/
  class SCCP_RefNum:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_RefNum
     ************************************************************************
     *  Purpose:
     *      This method constructs a reference number object.
     *
     *  Input Parameters:
     *      id - the reference number type.  One of SCCP__PRM_SOURCE_LOCAL_REF
     *          or SCCP_PRM_DEST_LOCAL_REF.
     *      ref - the reference number itself
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    /* SCCP_RefNum(const ITS_OCTET id, const ITS_UINT ref)
       : haveRef(true)
       {
       ie.param_id = id;
       ie.param_length = sizeof(SCCP_REF_NUM);
       ie.param_data.sourceLocalReference.refno[0] = (ref >> 16) & 0xFFU;
       ie.param_data.sourceLocalReference.refno[1] = (ref >> 8) & 0xFFU;
       ie.param_data.sourceLocalReference.refno[2] = ref & 0xFFU;
       }
     */
    SCCP_RefNum (const ITS_OCTET id, const ITS_UINT ref):haveRef (true)
    {
      ie.param_id = id;
      ie.param_length = sizeof (SCCP_REF_NUM);
      ie.param_data.sourceLocalReference.refno[2] = (ref >> 16) & 0xFFU;
      ie.param_data.sourceLocalReference.refno[1] = (ref >> 8) & 0xFFU;
      ie.param_data.sourceLocalReference.refno[0] = ref & 0xFFU;
    }
    /*.implementation:public,inline,SCCP_RefNum
     ************************************************************************
     *  Purpose:
     *      This method determines if the reference number value from a
     *      SCCP_RefNum object has been set.
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
     *      true - the reference number has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasRefNum () const
    {
      return (haveRef);
    }
    /*.implementation:public,inline,SCCP_RefNum
     ************************************************************************
     *  Purpose:
     *      This method retrieves the reference number value from a
     *      SCCP_RefNum object.
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
     *      The reference number value as an unsigned int.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    /* ITS_UINT
       GetRefNum() const
       {
       ITS_THROW_ASSERT(haveRef);

       return (ie.param_data.sourceLocalReference.refno[0] << 16) +
       (ie.param_data.sourceLocalReference.refno[1] << 8) +
       ie.param_data.sourceLocalReference.refno[2];
       } */

    ITS_UINT GetRefNum () const
    {
      ITS_THROW_ASSERT (haveRef);

      return (ie.param_data.sourceLocalReference.refno[2] << 16) +
	(ie.param_data.sourceLocalReference.refno[1] << 8) +
	ie.param_data.sourceLocalReference.refno[0];
    }
    /*.implementation:public,inline,SCCP_RefNum
     ************************************************************************
     *  Purpose:
     *      This method sets the reference number value for an SCCP_RefNum
     *      object.
     *
     *  Input Parameters:
     *      ref - the value to store for reference number
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
/*    void
    SetRefNum(const ITS_UINT ref)
    {
        ie.param_data.sourceLocalReference.refno[0] = (ref >> 16) & 0xFFU;
        ie.param_data.sourceLocalReference.refno[1] = (ref >> 8) & 0xFFU;
        ie.param_data.sourceLocalReference.refno[2] = ref & 0xFFU;

        haveRef = true;
    }
*/

    void SetRefNum (const ITS_UINT ref)
    {
      ie.param_data.sourceLocalReference.refno[2] = (ref >> 16) & 0xFFU;
      ie.param_data.sourceLocalReference.refno[1] = (ref >> 8) & 0xFFU;
      ie.param_data.sourceLocalReference.refno[0] = ref & 0xFFU;

      haveRef = true;
    }
  protected:
    bool haveRef;

    /*.implementation:protected,inline,SCCP_RefNum
     ************************************************************************
     *  Purpose:
     *      This method encodes a reference number into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_REF_NUM);
      memcpy (buf, &ie.param_data.sourceLocalReference,
	      sizeof (SCCP_REF_NUM));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_RefNum
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a reference number object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_REF_NUM);
      memcpy (&ie.param_data.sourceLocalReference, buf,
	      sizeof (SCCP_REF_NUM));

      haveRef = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_RefNum
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_RefNum object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_RefNum *ret = new SCCP_RefNum (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    SCCP_RefNum ()
    {
    }
  };

/*
 * forward
 */
  class SCCP_SourceLocalRef;
  class SCCP_DestinationLocalRef;

/*.interface:SCCP_SourceLocalRef
 *****************************************************************************
 *  Interface:
 *      SCCP_SourceLocalRef
 *
 *  Purpose:
 *      This class implements the source local reference IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_SourceLocalRef:public SCCP_RefNum
  {
  public:
    /*.implementation:public,inline,SCCP_SourceLocalRef
     ************************************************************************
     *  Purpose:
     *      This method constructs a source local reference number object.
     *
     *  Input Parameters:
     *      ref - the reference number
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_SourceLocalRef (ITS_UINT ref):SCCP_RefNum (SCCP_PRM_SRC_LOCAL_REF,
						    ref)
    {
    }
    /*.implementation:public,inline,SCCP_SourceLocalRef
     ************************************************************************
     *  Purpose:
     *      This method constructs a source local reference number object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_SourceLocalRef ():SCCP_RefNum (SCCP_PRM_SRC_LOCAL_REF, 0)
    {
      haveRef = false;
    }

    SCCP_SourceLocalRef & operator= (SCCP_DestinationLocalRef & copy);
  };

/*.interface:SCCP_DestinationLocalRef
 *****************************************************************************
 *  Interface:
 *      SCCP_DestinationLocalRef
 *
 *  Purpose:
 *      This class implements the destination local reference IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_DestinationLocalRef:public SCCP_RefNum
  {
  public:
    /*.implementation:public,inline,SCCP_DestinationLocalRef
     ************************************************************************
     *  Purpose:
     *      This method constructs a source local reference number object.
     *
     *  Input Parameters:
     *      ref - the reference number
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_DestinationLocalRef (ITS_UINT
			      ref):SCCP_RefNum (SCCP_PRM_DEST_LOCAL_REF, ref)
    {
    }
    /*.implementation:public,inline,SCCP_DestinationLocalRef
     ************************************************************************
     *  Purpose:
     *      This method constructs a source local reference number object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_DestinationLocalRef ():SCCP_RefNum (SCCP_PRM_DEST_LOCAL_REF, 0)
    {
      haveRef = false;
    }

    /*.implementation:public,inline,SCCP_DestinationLocalRef
     ************************************************************************
     *  Purpose:
     *      This method allows the user to copy a source local reference into
     *      a destination local reference.
     *
     *  Input Parameters:
     *      copy - the called party to copy
     *
     *  Return Value:
     *      A reference to the modified destination local reference
     *
     ************************************************************************/
/*    SCCP_DestinationLocalRef&
    SCCP_DestinationLocalRef::operator=(SCCP_SourceLocalRef& copy)  kernel 2.6*/
    SCCP_DestinationLocalRef&
    operator=(SCCP_SourceLocalRef& copy)  
    {
      SetRefNum (copy.GetRefNum ());

      return *this;
    }
  };

/*.implementation:public,inline,SCCP_SourceLocalRef
 ************************************************************************
 *  Purpose:
 *      This method allows the user to copy a destination local reference into
 *      a source local reference.
 *
 *  Input Parameters:
 *      copy - the called party to copy
 *
 *  Return Value:
 *      A reference to the modified source local reference
 *
 ************************************************************************/
  inline SCCP_SourceLocalRef &
    SCCP_SourceLocalRef::operator= (SCCP_DestinationLocalRef & copy)
  {
    SetRefNum (copy.GetRefNum ());

    return *this;
  }

/*.interface:SCCP_Credit
 *****************************************************************************
 *  Interface:
 *      SCCP_Credit
 *
 *  Purpose:
 *      This class implements the credit IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_Credit:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method constructs a credit object.
     *
     *  Input Parameters:
     *      credit - the credit value
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_Credit (const ITS_OCTET cred):haveCredit (true)
    {
      ie.param_id = SCCP_PRM_CREDIT;
      ie.param_length = sizeof (SCCP_CREDIT);
      ie.param_data.credit.win_size = cred;
    }
    /*.implementation:public,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method constructs a credit object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_Credit ():haveCredit (false)
    {
      ie.param_id = SCCP_PRM_CREDIT;
      ie.param_length = sizeof (SCCP_CREDIT);
    }

    /*.implementation:public,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method determines if the credit value from a
     *      SCCP_Credit object has been set.
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
     *      true - the number has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasCredit ()const
    {
      return (haveCredit);
    }
    /*.implementation:public,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method retrieves the credit value from a
     *      SCCP_Credit object.
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
     *      The reference number value as an unsigned int.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetCredit () const
    {
      ITS_THROW_ASSERT (haveCredit);

      return ie.param_data.credit.win_size;
    }
    /*.implementation:public,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method sets the credit value for an SCCP_Credit
     *      object.
     *
     *  Input Parameters:
     *      credit - the value to store for credit
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetCredit (const ITS_OCTET credit)
    {
      ie.param_data.credit.win_size = credit;

      haveCredit = true;
    }

  protected:
    /*.implementation:protected,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method encodes a credit value into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_CREDIT);
      memcpy (buf, &ie.param_data.credit, sizeof (SCCP_CREDIT));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a credit object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_CREDIT);
      memcpy (&ie.param_data.credit, buf, sizeof (SCCP_CREDIT));

      haveCredit = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_Credit
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_Credit object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_Credit *ret = new SCCP_Credit (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    bool haveCredit;
  };

/*.interface:SCCP_Address
 *****************************************************************************
 *  Interface:
 *      SCCP_Address
 *
 *  Purpose:
 *      SCCP address intermediate class.
 *
 *  Usage:
 *      This class is an intermediate class and should not be used directly.
 *      The SCCP_CallingPartyAddr and SCCP_CalledPartyAddre IE(s) are derived
 *      from this class.
 *
 *****************************************************************************/
  class SCCP_Address:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method constructs an address object.
     *
     *  Input Parameters:
     *      id - the address type.  One of SCCP_PRM_CALLED_PARTY_ADDR or
     *          SCCP_PRM_CALLING_PARTY_ADDR
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_Address (const ITS_OCTET id)
    {
      ie.param_id = id;

      hasPC = false;
      hasSSN = false;
      routePCSSN = false;
      internationalRoute = false;
      globalTitle = false;

      pointCode = 0;
      ssn = 0;
      gttLen = 0;
      gttType = SCCP_CPA_GTTI_NONE;
    }

    // Point code
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method determines if an SCCP_Address object had a point
     *      code given for it.
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
     *      A boolean value, true if the point code was set, false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasPointCode () const
    {
      return (hasPC);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method retrieves the point code value from a
     *      SCCP_Address object.
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
     *      The point code value as an unsigned int.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT GetPointCode () const
    {
      ITS_THROW_ASSERT (hasPC);

      return (pointCode);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets the point code value for an SCCP_Address
     *      object.
     *
     *  Input Parameters:
     *      pc - the value to store for point code
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetPointCode (const ITS_UINT pc)
    {
      hasPC = true;
      pointCode = pc;
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets the point code value for an SCCP_Address
     *      object.
     *
     *  Input Parameters:
     *      pc - the value to store for point code
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetPointCode (const MTP3_PointCode pc)
    {
      ITS_THROW_ASSERT (pc.GetValue ());

      hasPC = true;
      pointCode = pc.GetValue ();
    }

    // SSN
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method determines if an SCCP_Address object had a subsystem
     *      number given for it.
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
     *      A boolean value, true if the ssn was set, false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasSSN ()const
    {
      return (hasSSN);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method retrieves the subsystem number value from a
     *      SCCP_Address object.
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
     *      The subsystem number value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetSSN () const
    {
      ITS_THROW_ASSERT (hasSSN);

      return ssn;
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets the subsystem number value for an SCCP_Address
     *      object.
     *
     *  Input Parameters:
     *      ssn - the value to store for subsystem number
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetSSN (const ITS_OCTET sn)
    {
      hasSSN = true;
      ssn = sn;
    }

    // routing method
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method determines if the "routed by" flag value for an
     *      SCCP_Address object has been set.
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
     *      true if the value has been set.  false otherwise.
     *
     *  Notes:
     *      Setting this to false implies routing by GTT.
     *
     *  See Also:
     ************************************************************************/
    bool IsRoutedByPCSSN ()const
    {
      return (routePCSSN);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets the "routed by" flag value for an SCCP_Address
     *      object.
     *
     *  Input Parameters:
     *      which - the value to store for the "routed by" flag
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
     *  Notes:
     *      Setting this to false implies routing by GTT.
     *
     *  See Also:
     ************************************************************************/
    void SetRouteByPCSSN (const bool which)
    {
      routePCSSN = which;
    }

    // national/internation
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method determines if an SCCP_Address object had the
     *      international routing flag set.
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
     *      A boolean value, true if the flag was set, false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool IsInternationalRouting ()const
    {
      return internationalRoute;
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets the "international routing" flag value for an
     *      SCCP_Address object.
     *
     *  Input Parameters:
     *      which - the value to store for the "international routing" flag
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetInternationalRouting (const bool which)
    {
      internationalRoute = which;
    }

    // Global title
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method determines if an SCCP_Address object had global
     *      title information
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
     *      A boolean value, true if the global title was set, false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasGlobalTitle ()const
    {
      return globalTitle;
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets global title information for this address.
     *
     *  Input Parameters:
     *      type - the address indicator flag for this GTT type.
     *      gttInfo - the global title information.
     *      gttLength - the size of the GTT information.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    int
      SetGlobalTitle (const ITS_OCTET type,
		      const ITS_OCTET * gttInfo, const ITS_USHORT gttLength)
    {
      globalTitle = true;
      if (gttLen >= SCCP_MAX_ADDR_LEN)
	{
	  return (ITS_EOVERFLOW);
	}

      gttType = type;
      memcpy (globTitle, gttInfo, gttLength);
      gttLen = gttLength;

      return (ITS_SUCCESS);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets global title information for this address.
     *
     *  Input Parameters:
     *      type - the address indicator flag for this GTT type.
     *      gttInfo - the global title information.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    int SetGlobalTitle (const ITS_OCTET type, const ITS_ByteArray & gttInfo)
    {
      globalTitle = true;
      if (gttInfo.size () >= SCCP_MAX_ADDR_LEN)
	{
	  return (ITS_EOVERFLOW);
	}

      gttType = type;
      memcpy (globTitle, &gttInfo[0], gttInfo.size ());
      gttLen = gttInfo.size ();

      return (ITS_SUCCESS);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method gets global title information for this address.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      type - the address indicator flag for this GTT type.
     *      gttInfo - the global title information.
     *      gttLength - the size of the GTT information.
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *      If the size of the global title information exceeds the maximum
     *      possible size of an SCCP_ADDRESS, this routine will silently
     *      fail.
     *
     *  See Also:
     ************************************************************************/
    int
      GetGlobalTitle (ITS_OCTET & type,
		      ITS_OCTET * gttInfo, ITS_USHORT & gttLength) const
    {
      ITS_THROW_ASSERT (globalTitle);

      if (gttType == SCCP_CPA_GTTI_NONE)
	{
	  return (ITS_ENOTFOUND);
	}

      type = gttType;
      memcpy (gttInfo, globTitle, gttLen);
      gttLength = gttLen;

      return (ITS_SUCCESS);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method gets global title information for this address.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      type - the address indicator flag for this GTT type.
     *      gttInfo - the global title information.
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *      If the size of the global title information exceeds the maximum
     *      possible size of an SCCP_ADDRESS, this routine will silently
     *      fail.
     *
     *  See Also:
     ************************************************************************/
    int GetGlobalTitle (ITS_OCTET & type, ITS_ByteArray & gttInfo) const
    {
      ITS_THROW_ASSERT (globalTitle);

      gttInfo.erase (gttInfo.begin (), gttInfo.end ());

      if (gttType == SCCP_CPA_GTTI_NONE)
	{
	  return (ITS_ENOTFOUND);
	}

      type = gttType;
      gttInfo.assign (globTitle, globTitle + gttLen);

      return (ITS_SUCCESS);
    }

    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method exposes the Encode() protected method to public
     *      scope.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Parse()
     ************************************************************************/
    int Build (ITS_OCTET * buf, int &len) const
    {
      return Encode (buf, len);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method exposes the Encode() protected method to public
     *      scope.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Parse()
     ************************************************************************/
    int Build (ITS_ByteArray & buf) const
    {
      ITS_OCTET b[SCCP_MAX_ADDR_LEN];
      int len, ret;

        buf.erase (buf.begin (), buf.end ());

        ret = Encode (b, len);

      if (ret == ITS_SUCCESS)
	{
	  buf.assign (b, b + len);
	}

      return ret;
    }

    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into an SCCP_Address object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Build()
     ************************************************************************/
    int Parse (const ITS_OCTET * buf, int &len)
    {
      return Decode (buf, len);
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into an SCCP_Address object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Build()
     ************************************************************************/
    int Parse (const ITS_ByteArray & buf)
    {
      ITS_OCTET b[SCCP_MAX_ADDR_LEN];
      int len, ret;

      memcpy (b, &buf[0], buf.size ());
      len = buf.size ();

      ret = Decode (b, len);

      len = buf.size ();

      ITS_THROW_ASSERT (len > 0);

      return ret;
    }

  protected:
    /*.implementation:protected,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method encodes an address into a byte stream.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ****************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      ITS_SCCP_IE *override = const_cast < ITS_SCCP_IE * >(&ie);

        override->param_data.calledPartyAddr.data[0] = 0;
        override->param_data.calledPartyAddr.len = 1;

      ITS_OCTET addrInd = 0;

      if (HasPointCode ())
	{
	  addrInd |= SCCP_CPA_HAS_PC;
	}

      if (HasSSN ())
	{
	  addrInd |= SCCP_CPA_HAS_SSN;
	}

      if (IsRoutedByPCSSN ())
	{
	  addrInd |= SCCP_CPA_ROUTE_SSN;
	}
      else if (!HasGlobalTitle ())
	{
	  return (ITS_EINVALIDARGS);
	}

      if (HasGlobalTitle ())
	{
	  addrInd |= gttType;
	}

      if (IsInternationalRouting ())
	{
	  addrInd |= SCCP_CPA_ROUTE_INT;
	}
      else
	{
	  addrInd |= SCCP_CPA_ROUTE_NAT;
	}

      SCCP_EncodeAddr (&override->param_data.calledPartyAddr, addrInd,
		       HasPointCode ()? GetPointCode () : 0,
		       HasSSN ()? GetSSN () : 0, globTitle, gttLen);


      /* copy over */
      len = ie.param_data.calledPartyAddr.len;
      memcpy (buf, ie.param_data.calledPartyAddr.data, len);

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a reference number object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      ITS_OCTET addrInd = 0;

      memcpy (ie.param_data.calledPartyAddr.data, buf, len);
      ie.param_data.calledPartyAddr.len = len;
      ie.param_length = len;

      SCCP_DecodeAddr (&ie.param_data.calledPartyAddr, &addrInd,
		       &pointCode, &ssn, globTitle, &gttLen);

      if (ie.param_data.calledPartyAddr.len > 0)
	{
	  if (addrInd & SCCP_CPA_HAS_PC)
	    {
	      hasPC = true;
	    }
	  else
	    {
	      hasPC = false;
	    }

	  if (addrInd & SCCP_CPA_HAS_SSN)
	    {
	      hasSSN = true;
	    }
	  else
	    {
	      hasSSN = false;
	    }

	  if (addrInd & SCCP_CPA_ROUTE_SSN)
	    {
	      routePCSSN = true;
	    }
	  else
	    {
	      routePCSSN = false;
	    }

#if defined(CCITT) || defined(PRC) || defined(TTC)
	  internationalRoute = false;
#else
	  internationalRoute = true;
#endif

	  if (addrInd & SCCP_CPA_ROUTE_INT)
	    {
	      internationalRoute = true;
	    }
	  else if (addrInd & SCCP_CPA_ROUTE_NAT)
	    {
	      internationalRoute = false;
	    }

	  if ((addrInd & SCCP_CPA_GTTI_MASK) != SCCP_CPA_GTTI_NONE)
	    {
	      globalTitle = true;
	      gttType = addrInd & SCCP_CPA_GTTI_MASK;
	    }
	  else
	    {
	      globalTitle = false;
	    }
	}
      else
	{
	  hasPC = false;
	  hasSSN = false;
	  routePCSSN = false;
	  internationalRoute = false;
	  globalTitle = false;

	  pointCode = 0;
	  ssn = 0;
	}

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_Address object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_Address *ret = new SCCP_Address (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    /* can't use this one */
    SCCP_Address ()
    {
    }

    bool hasPC;
    bool hasSSN;
    bool routePCSSN;
    bool internationalRoute;
    bool globalTitle;

    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_OCTET globTitle[SCCP_MAX_ADDR_LEN];
    ITS_OCTET gttType;
    ITS_USHORT gttLen;
  };

/*
 * forward
 */
  class SCCP_CalledPartyAddr;
  class SCCP_CallingPartyAddr;

/*.interface:SCCP_CalledPartyAddr
 *****************************************************************************
 *  Interface:
 *      SCCP_CalledPartyAddr
 *
 *  Purpose:
 *      This class implements the called party address IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_CalledPartyAddr:public SCCP_Address
  {
  public:
    /*.implementation:public,inline,SCCP_CalledPartyAddr
     ************************************************************************
     *  Purpose:
     *      This method constructs a called party address object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_CalledPartyAddr ():SCCP_Address (SCCP_PRM_CALLED_PARTY_ADDR)
    {
    }

   /* SCCP_CalledPartyAddr&
    SCCP_CalledPartyAddr::operator=(SCCP_CallingPartyAddr& copy); Kernel 2.6 */
    SCCP_CalledPartyAddr&
    operator=(SCCP_CallingPartyAddr& copy);
  };

/*.interface:SCCP_CallingPartyAddr
 *****************************************************************************
 *  Interface:
 *      SCCP_CallingPartyAddr
 *
 *  Purpose:
 *      This class implements the calling party address IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_CallingPartyAddr:public SCCP_Address
  {
  public:
    /*.implementation:public,inline,SCCP_CallingPartyAddr
     ************************************************************************
     *  Purpose:
     *      This method constructs a calling party address object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_CallingPartyAddr ():SCCP_Address (SCCP_PRM_CALLING_PARTY_ADDR)
    {
    }

    /*.implementation:public,inline,SCCP_CallingPartyAddr
     ************************************************************************
     *  Purpose:
     *      This method allows the user to copy a called party address into
     *      a calling party address.
     *
     *  Input Parameters:
     *      copy - the called party to copy
     *
     *  Return Value:
     *      A reference to the modified calling party address
     *
     ************************************************************************/
/*    SCCP_CallingPartyAddr&
    SCCP_CallingPartyAddr::operator=(SCCP_CalledPartyAddr& copy)  kernel 2.6 */
    SCCP_CallingPartyAddr&
    operator=(SCCP_CalledPartyAddr& copy)  
    {
      ITS_OCTET buf[32];
      int len, ret;

      ret = copy.Build (buf, len);

      ITS_THROW_ASSERT (ret == ITS_SUCCESS);

      ret = Parse (buf, len);

      ITS_THROW_ASSERT (ret == ITS_SUCCESS);

      ie.param_id = SCCP_PRM_CALLING_PARTY_ADDR;

      return *this;
    }
  };

/*.implementation:public,inline,CalledPartyAddr
 ************************************************************************
 *  Purpose:
 *      This method allows the user to copy a calling party address into
 *      a called party address.
 *
 *  Input Parameters:
 *      copy - the called party to copy
 *
 *  Return Value:
 *      A reference to the modified called party address
 *
 ************************************************************************/
  inline SCCP_CalledPartyAddr &
    SCCP_CalledPartyAddr::operator= (SCCP_CallingPartyAddr & copy)
  {
    ITS_OCTET buf[32];
    int len, ret;

    ret = copy.Build (buf, len);

    ITS_THROW_ASSERT (ret == ITS_SUCCESS);

    ret = Parse (buf, len);

    ITS_THROW_ASSERT (ret == ITS_SUCCESS);

    ie.param_id = SCCP_PRM_CALLED_PARTY_ADDR;

    return *this;
  }

/*.interface:SCCP_ProtocolClass
 *****************************************************************************
 *  Interface:
 *      SCCP_ProtocolClass
 *
 *  Purpose:
 *      This class implements the protocol class IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ProtocolClass:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_ProtocolClass
     ************************************************************************
     *  Purpose:
     *      This method constructs a protocol class object.
     *
     *  Input Parameters:
     *      pclass - the protocol class value for this object
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ProtocolClass (const ITS_OCTET pclass):havePClass (true)
    {
      ie.param_id = SCCP_PRM_PROTOCOL_CLASS;
      ie.param_length = sizeof (SCCP_PROT_CLASS);
      ie.param_data.protocolClass.pclass = pclass;

    }
    /*.implementation:public,inline,SCCP_ProtocolClass
     ************************************************************************
     *  Purpose:
     *      This method constructs a protocol class object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ProtocolClass ():havePClass (false)
    {
      ie.param_id = SCCP_PRM_PROTOCOL_CLASS;
      ie.param_length = sizeof (SCCP_PROT_CLASS);
    }

    /*.implementation:public,inline,SCCP_ProtocolClass
     ************************************************************************
     *  Purpose:
     *      This method determines if the protocol class value from a
     *      SCCP_ProtocolClass object has been set.
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
     *      true - the protocol class has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasProtocolClass ()const
    {
      return (havePClass);
    }
    /*.implementation:public,inline,SCCP_ProtocolClass
     ************************************************************************
     *  Purpose:
     *      This method retrieves the protocol class value from a
     *      SCCP_ProtocolClass object.
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
     *      The protocol class value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetProtocolClass () const
    {
      ITS_THROW_ASSERT (havePClass);

      return ie.param_data.protocolClass.pclass;
    }
    /*.implementation:public,inline,SCCP_Address
     ************************************************************************
     *  Purpose:
     *      This method sets the protocol class value for an SCCP_Addres
     *      object.
     *
     *  Input Parameters:
     *      pclass - the value to store for protocol class
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetProtocolClass (const ITS_OCTET pclass)
    {
      ie.param_data.protocolClass.pclass = pclass;

      havePClass = true;
    }

  protected:
    /*.implementation:protected,inline,SCCP_ProtocolClass
     ************************************************************************
     *  Purpose:
     *      This method encodes a protocol class value into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_PROT_CLASS);
      memcpy (buf, &ie.param_data.protocolClass, sizeof (SCCP_PROT_CLASS));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_ProtocolClass
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a protocol class object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_PROT_CLASS);
      memcpy (&ie.param_data.protocolClass, buf, sizeof (SCCP_PROT_CLASS));

      havePClass = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_ProtocolClass
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_ProtocolClass object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_ProtocolClass *ret = new SCCP_ProtocolClass (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    bool havePClass;
  };

/*.interface:SCCP_SegmentReassem
 *****************************************************************************
 *  Interface:
 *      SCCP_SegmentReassem
 *
 *  Purpose:
 *      This class implements the segmentation/reassembly IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_SegmentReassem:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method constructs a segmentation/reassembly object.
     *
     *  Input Parameters:
     *      haveMore - the value of the "have more" flag.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_SegmentReassem (const ITS_OCTET haveMore):haveSegReassem (true)
    {
      ie.param_id = SCCP_PRM_SEGMENT_REASSEM;
      ie.param_length = sizeof (SCCP_SEG_RES);
      ie.param_data.segmentingReassembly.seg_res = haveMore;
    }
    /*.implementation:public,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method constructs a segmentation/reassembly object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_SegmentReassem ():haveSegReassem (false)
    {
      ie.param_id = SCCP_PRM_SEGMENT_REASSEM;
      ie.param_length = sizeof (SCCP_SEG_RES);
    }

    /*.implementation:public,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method determines if  the segmentation/reassembly value from
     *      a SCCP_SegmentReassem object has been set.
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
     *      true - the value has been set.  false otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasSegmentReassem ()const
    {
      return (haveSegReassem);
    }
    /*.implementation:public,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method retrieves the segmentation/reassembly value from a
     *      SCCP_SegmentReassem object.
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
     *      The segmentation/reassembly value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetSegmentReassem () const
    {
      ITS_THROW_ASSERT (haveSegReassem);

      return ie.param_data.segmentingReassembly.seg_res;
    }
    /*.implementation:public,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method sets the segmentation/reassembly value for an
     *      SCCP_SegmentReassem object.
     *
     *  Input Parameters:
     *      haveMore - the value to store for segmentation/reasembly
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetSegmentReassem (const ITS_OCTET haveMore)
    {
      haveSegReassem = true;

      ie.param_data.segmentingReassembly.seg_res = haveMore;
    }

  protected:
    /*.implementation:protected,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method encodes a segmentation/reassembly IE into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_SEG_RES);
      memcpy (buf, &ie.param_data.segmentingReassembly,
	      sizeof (SCCP_SEG_RES));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a segmentation/reassembly
     *      object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_SEG_RES);
      memcpy (&ie.param_data.segmentingReassembly, buf,
	      sizeof (SCCP_SEG_RES));

      haveSegReassem = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_SegmentReassem
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_SegmentReassem object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_SegmentReassem *ret = new SCCP_SegmentReassem (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    bool haveSegReassem;
  };

/*.interface:SCCP_SequenceSegment
 *****************************************************************************
 *  Interface:
 *      SCCP_SequenceSegment
 *
 *  Purpose:
 *      This class implements the sequencing/segmentation IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_SequenceSegment:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method constructs a sequencing/segmentation object.
     *
     *  Input Parameters:
     *      tsn - the transmit sequence number
     *      rsn - the receive sequence number
     *      haveMore - the value of the "have more" flag.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_SequenceSegment (const ITS_OCTET tsn,
			  const ITS_OCTET rsn,
			  const ITS_OCTET haveMore):haveTSN (true),
      haveRSN (true), haveHaveMore (true)
    {
      ie.param_id = SCCP_PRM_SEQUENCE_SEGMENT;
      ie.param_length = sizeof (SCCP_SEQ_SEG);
      ie.param_data.sequenceSegment.tsn = tsn << 1;
      ie.param_data.sequenceSegment.rsn = (rsn << 1) | haveMore;
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method constructs a sequencing/segmentation object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_SequenceSegment ():haveTSN (false),
      haveRSN (false), haveHaveMore (false)
    {
      ie.param_id = SCCP_PRM_SEQUENCE_SEGMENT;
      ie.param_length = sizeof (SCCP_SEQ_SEG);
    }

    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method determines if the transmit sequence number value
     *      from a SCCP_SequenceSegment object.
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
     *      true - the transmit sequence number has been set.  false otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasTransmitSequenceNumber ()const
    {
      return (haveTSN);
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method retrieves the transmit sequence number value from a
     *      SCCP_SequenceSegment object.
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
     *      The transmit sequence number value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetTransmitSequenceNumber () const
    {
      ITS_THROW_ASSERT (haveTSN);

      return ie.param_data.sequenceSegment.tsn;
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method sets the transmit sequence number value for an
     *      SCCP_SequenceSegment object.
     *
     *  Input Parameters:
     *      tsn - the value to store for transmit sequence number
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetTransmitSequenceNumber (const ITS_OCTET tsn)
    {
      ie.param_data.sequenceSegment.tsn = tsn << 1;

      haveTSN = true;
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method determines if the receive sequence number value from
     *      a SCCP_SequenceSegment object has been set.
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
     *      true - the sequence/segment has been set.  false otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasReceiveSequenceNumber ()const
    {
      return (haveRSN);
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method retrieves the receive sequence number value from a
     *      SCCP_SequenceSegment object.
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
     *      The receive sequence number value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetReceiveSequenceNumber () const
    {
      ITS_THROW_ASSERT (haveRSN);

      return ie.param_data.sequenceSegment.rsn;
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method sets the receive sequence number value for an
     *      SCCP_SequenceSegment object.
     *
     *  Input Parameters:
     *      rsn - the value to store for receive sequence number
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetReceiveSequenceNumber (const ITS_OCTET rsn)
    {
      haveRSN = true;

      ie.param_data.sequenceSegment.rsn = rsn << 1;
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method retrieves the "have more" flag value from a
     *      SCCP_SequenceSegment object.
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
     *      The "have more" flag value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasHaveMore ()const
    {
      return (haveHaveMore);
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method retrieves the "have more" flag value from a
     *      SCCP_SequenceSegment object.
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
     *      The "have more" flag value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetHaveMore () const
    {
      ITS_THROW_ASSERT (haveHaveMore);

      return ie.param_data.sequenceSegment.rsn & SCCP_SR_MORE_DATA;
    }
    /*.implementation:public,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method sets the "have more" flag value for an
     *      SCCP_SequenceSegment object.
     *
     *  Input Parameters:
     *      haveMore - the value to store for the "have more" flag.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetHaveMore (const ITS_OCTET haveMore)
    {
      haveHaveMore = true;

      ie.param_data.sequenceSegment.rsn |= haveMore;
    }

  protected:
    /*.implementation:protected,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method encodes a sequence/segmentation IE into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_SEQ_SEG);
      memcpy (buf, &ie.param_data.sequenceSegment, sizeof (SCCP_SEQ_SEG));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a sequencing/segmentation
     *      object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_SEQ_SEG);
      memcpy (&ie.param_data.sequenceSegment, buf, sizeof (SCCP_SEQ_SEG));

      haveTSN = true;
      haveRSN = true;
      haveHaveMore = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_SequenceSegment
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_SequenceSegment object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_SequenceSegment *ret = new SCCP_SequenceSegment (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    bool haveTSN;
    bool haveRSN;
    bool haveHaveMore;
  };

/*.interface:SCCP_ReceiveSequenceNum
 *****************************************************************************
 *  Interface:
 *      SCCP_ReceiveSequenceNum
 *
 *  Purpose:
 *      This class implements the received sequence number IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ReceiveSequenceNum:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method constructs a sequencing/segmentation object.
     *
     *  Input Parameters:
     *      rsn - the receive sequence number
     *      haveMore - the value of the "have more" flag.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ReceiveSequenceNum (const ITS_OCTET rsn,
			     const ITS_OCTET haveMore):haveRSN (true),
      haveHaveMore (true)
    {
      ie.param_id = SCCP_PRM_RCV_SEQ_NUM;
      ie.param_length = sizeof (SCCP_RSN);
      ie.param_data.receivedSequenceNumber.rsn = (rsn << 1) | haveMore;
    }
    /*.implementation:public,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method constructs a sequencing/segmentation object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ReceiveSequenceNum ():haveRSN (false), haveHaveMore (false)
    {
      ie.param_id = SCCP_PRM_RCV_SEQ_NUM;
      ie.param_length = sizeof (SCCP_RSN);
    }

    /*.implementation:public,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method determines if the receive sequence number value from
     *      a SCCP_ReceiveSequenceNum object has been set.
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
     *      true - the RSN has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasReceiveSequenceNumber ()const
    {
      return (haveRSN);
    }
    /*.implementation:public,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method retrieves the receive sequence number value from a
     *      SCCP_ReceiveSequenceNum object.
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
     *      The receive sequence number value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetReceiveSequenceNumber () const
    {
      ITS_THROW_ASSERT (haveRSN);

      return ie.param_data.receivedSequenceNumber.rsn;
    }
    /*.implementation:public,inline,SCCP_ReceiveSequenceNumber
     ************************************************************************
     *  Purpose:
     *      This method sets the receive sequence number value for an
     *      SCCP_ReceiveSequenceNumber object.
     *
     *  Input Parameters:
     *      rsn - the value to store for receive sequence number
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetReceiveSequenceNumber (const ITS_OCTET rsn)
    {
      haveRSN = true;

      ie.param_data.receivedSequenceNumber.rsn = rsn << 1;
    }
    /*.implementation:public,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method determines if the "have more" flag value from a
     *      SCCP_ReceiveSequenceNum object has been set.
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
     *      true - the haveMore flag has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasHaveMore ()const
    {
      return (haveHaveMore);
    }
    /*.implementation:public,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method retrieves the "have more" flag value from a
     *      SCCP_ReceiveSequenceNum object.
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
     *      The "have more" flag value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetHaveMore () const
    {
      ITS_THROW_ASSERT (haveHaveMore);

      return ie.param_data.receivedSequenceNumber.rsn & SCCP_SR_MORE_DATA;
    }
    /*.implementation:public,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method sets the "have more" flag value for an
     *      SCCP_ReceiveSequenceNum object.
     *
     *  Input Parameters:
     *      haveMore - the value to store for the "have more" flag.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetHaveMore (const ITS_OCTET haveMore)
    {
      haveHaveMore = true;

      ie.param_data.receivedSequenceNumber.rsn |= haveMore;
    }

  protected:
    /*.implementation:protected,inline,SCCP_ReceiveSequenceNumber
     ************************************************************************
     *  Purpose:
     *      This method encodes a receive sequence number into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_RSN);
      memcpy (buf, &ie.param_data.receivedSequenceNumber, sizeof (SCCP_RSN));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a receive sequence number
     *      object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_RSN);
      memcpy (&ie.param_data.receivedSequenceNumber, buf, sizeof (SCCP_RSN));

      haveRSN = true;
      haveHaveMore = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_ReceiveSequenceNum
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_ReceiveSequenceNum
     *      object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_ReceiveSequenceNum *ret = new SCCP_ReceiveSequenceNum (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    bool haveRSN;
    bool haveHaveMore;
  };

/*.interface:SCCP_Impotance
 *****************************************************************************
 *  Interface:
 *      SCCP_Importance
 *
 *  Purpose:
 *      This class implements the basic SCCP Important class.  This class is not
 *      intended for general purpose use; it is an intermediate class for
 *      all SCCP important classes.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_Importance:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_Importance
     ************************************************************************     *  Purpose:
     *      This method constructs a cause object.
     *
     *  Input Parameters:
     *      id - one of SCCP_PRM_RETURN_CAUSE, SCCP_PRM_REFUSAL_CAUSE,
     *          SCCP_PRM_ERROR_CAUSE, SCCP_PRM_RELEASE_CAUSE, or
     *          SCCP_PRM_RESET_CAUSE.
     *      importance - the  value.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_Importance (const ITS_OCTET Impvalue):haveImp (true)
    {
      ie.param_id = SCCP_PRM_IMPORTANCE;
      ie.param_length = sizeof (SCCP_IMPORTANCE);
      ie.param_data.importance.importance = Impvalue;
    }
    /*.implementation:public,inline,SCCP_Imp
     ************************************************************************     *  Purpose:
     *      This method constructs a Imp object.
     *
     *  Input Parameters:
     *      id - one of SCCP_PRM_RETURN_CAUSE, SCCP_PRM_REFUSAL_CAUSE,
     *          SCCP_PRM_ERROR_CAUSE, SCCP_PRM_RELEASE_CAUSE, or
     *          SCCP_PRM_RESET_CAUSE.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_Importance ():haveImp (false)
    {
      ie.param_id = SCCP_PRM_IMPORTANCE;
      ie.param_length = sizeof (SCCP_IMPORTANCE);
    }

    /*.implementation:public,inline,SCCP_Cause
     ************************************************************************     *  Purpose:
     *      This method determines if the imp value from an
     *      SCCP_imp object has been set.
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
     *      true - the cause value has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasImp ()const
    {
      return (haveImp);
    }
    /*.implementation:public,inline,SCCP_imp
     ************************************************************************     *  Purpose:
     *      This method retrieves the cause imp from an
     *      SCCP_imp object.
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
     *      The cause value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT GetImp () const
    {
      ITS_THROW_ASSERT (haveImp);

      return ie.param_data.importance.importance;
    }
    /*.implementation:public,inline,SCCP_imp
     ************************************************************************     *  Purpose:
     *      This method sets the cause value for an SCCP_imp
     *      object.
     *
     *  Input Parameters:
     *      cause- the value to store for cause
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetImp (const ITS_OCTET Impvalue)
    {
      haveImp = true;

      ie.param_data.importance.importance = Impvalue;

    }


  protected:
    /*.implementation:protected,inline,SCCP_imp
     ************************************************************************     *  Purpose:
     *      This method encodes a cause value into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_IMPORTANCE);
      memcpy (buf, &ie.param_data.importance.importance,
	      sizeof (SCCP_IMPORTANCE));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_imp
     ************************************************************************     *  Purpose:
     *      This method decodes a byte stream into a imp object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_IMPORTANCE);
      memcpy (&ie.param_data.importance.importance, buf,
	      sizeof (SCCP_IMPORTANCE));

      haveImp = true;

      return (ITS_SUCCESS);
    }


    /*.implementation:protected,inline,SCCP_imp
     ************************************************************************     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_imp object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_Importance *ret = new SCCP_Importance (*this);

      return (SCCP_IEClass *) ret;
    }


  private:
    bool haveImp;
  };



/*.interface:SCCP_Cause
 *****************************************************************************
 *  Interface:
 *      SCCP_Cause
 *
 *  Purpose:
 *      This class implements the basic SCCP cause class.  This class is not
 *      intended for general purpose use; it is an intermediate class for
 *      all SCCP cause classes.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_Cause:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method constructs a cause object.
     *
     *  Input Parameters:
     *      id - one of SCCP_PRM_RETURN_CAUSE, SCCP_PRM_REFUSAL_CAUSE,
     *          SCCP_PRM_ERROR_CAUSE, SCCP_PRM_RELEASE_CAUSE, or
     *          SCCP_PRM_RESET_CAUSE.
     *      cause - the cause value.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_Cause (const ITS_OCTET id, const ITS_OCTET cause):haveCause (true)
    {
      ie.param_id = id;
      ie.param_length = sizeof (SCCP_RET_CAUSE);
      ie.param_data.returnCause.cause = cause;
    }
    /*.implementation:public,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method constructs a cause object.
     *
     *  Input Parameters:
     *      id - one of SCCP_PRM_RETURN_CAUSE, SCCP_PRM_REFUSAL_CAUSE,
     *          SCCP_PRM_ERROR_CAUSE, SCCP_PRM_RELEASE_CAUSE, or
     *          SCCP_PRM_RESET_CAUSE.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_Cause (const ITS_OCTET id):haveCause (false)
    {
      ie.param_id = id;
      ie.param_length = sizeof (SCCP_RET_CAUSE);
    }

    /*.implementation:public,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method determines if the cause value from an
     *      SCCP_Cause object has been set.
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
     *      true - the cause value has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasCause ()const
    {
      return (haveCause);
    }
    /*.implementation:public,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method retrieves the cause value from an
     *      SCCP_Cause object.
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
     *      The cause value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT GetCause () const
    {
      ITS_THROW_ASSERT (haveCause);

      return ie.param_data.returnCause.cause;
    }
    /*.implementation:public,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method sets the cause value for an SCCP_Cause
     *      object.
     *
     *  Input Parameters:
     *      cause- the value to store for cause
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetCause (const ITS_OCTET cause)
    {
      haveCause = true;

      ie.param_data.returnCause.cause = cause;
    }

  protected:
    /*.implementation:protected,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method encodes a cause value into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_RET_CAUSE);
      memcpy (buf, &ie.param_data.returnCause, sizeof (SCCP_RET_CAUSE));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a cause object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_RET_CAUSE);
      memcpy (&ie.param_data.returnCause, buf, sizeof (SCCP_RET_CAUSE));

      haveCause = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_Cause
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_Cause object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_Cause *ret = new SCCP_Cause (*this);

      return (SCCP_IEClass *) ret;
    }

    bool haveCause;

  private:
    SCCP_Cause ()
    {
    }
  };

/*.interface:SCCP_ReleaseCause
 *****************************************************************************
 *  Interface:
 *      SCCP_ReleaseCause
 *
 *  Purpose:
 *      This class implements the release cause IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ReleaseCause:public SCCP_Cause
  {
  public:
    /*.implementation:public,inline,SCCP_ReleaseCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a release cause object.
     *
     *  Input Parameters:
     *      cause - the cause value.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ReleaseCause (const ITS_OCTET
		       cause):SCCP_Cause (SCCP_PRM_RELEASE_CAUSE, cause)
    {
    }
    /*.implementation:public,inline,SCCP_ReleaseCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a release cause object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ReleaseCause ():SCCP_Cause (SCCP_PRM_RELEASE_CAUSE, 0)
    {
      haveCause = false;
    }
  };

/*.interface:SCCP_ReturnCause
 *****************************************************************************
 *  Interface:
 *      SCCP_ReturnCause
 *
 *  Purpose:
 *      This class implements the return cause IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ReturnCause:public SCCP_Cause
  {
  public:
    /*.implementation:public,inline,SCCP_ReturnCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a return cause object.
     *
     *  Input Parameters:
     *      cause - the cause value.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ReturnCause (const ITS_OCTET
		      cause):SCCP_Cause (SCCP_PRM_RETURN_CAUSE, cause)
    {
    }
    /*.implementation:public,inline,SCCP_ReturnCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a return cause object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ReturnCause ():SCCP_Cause (SCCP_PRM_RETURN_CAUSE, 0)
    {
      haveCause = false;
    }
  };

/*.interface:SCCP_ResetCause
 *****************************************************************************
 *  Interface:
 *      SCCP_ResetCause
 *
 *  Purpose:
 *      This class implements the reset cause IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ResetCause:public SCCP_Cause
  {
  public:
    /*.implementation:public,inline,SCCP_ResetCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a reset cause object.
     *
     *  Input Parameters:
     *      cause - the cause value.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ResetCause (const ITS_OCTET cause):SCCP_Cause (SCCP_PRM_RESET_CAUSE,
							cause)
    {
    }
    /*.implementation:public,inline,SCCP_ReturnCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a reset cause object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ResetCause ():SCCP_Cause (SCCP_PRM_RESET_CAUSE, 0)
    {
      haveCause = false;
    }
  };

/*.interface:SCCP_ErrorCause
 *****************************************************************************
 *  Interface:
 *      SCCP_ErrorCause
 *
 *  Purpose:
 *      This class implements the error cause IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ErrorCause:public SCCP_Cause
  {
  public:
    /*.implementation:public,inline,SCCP_ErrorCause
     ************************************************************************
     *  Purpose:
     *      This method constructs an error cause object.
     *
     *  Input Parameters:
     *      cause - the cause value.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ErrorCause (const ITS_OCTET cause):SCCP_Cause (SCCP_PRM_ERROR_CAUSE,
							cause)
    {
    }
    /*.implementation:public,inline,SCCP_ErrorCause
     ************************************************************************
     *  Purpose:
     *      This method constructs an error cause object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_ErrorCause ():SCCP_Cause (SCCP_PRM_ERROR_CAUSE, 0)
    {
      haveCause = false;
    }
  };

/*.interface:SCCP_RefusalCause
 *****************************************************************************
 *  Interface:
 *      SCCP_RefusalCause
 *
 *  Purpose:
 *      This class implements the refusal cause IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_RefusalCause:public SCCP_Cause
  {
  public:
    /*.implementation:public,inline,SCCP_RefusalCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a refusal cause object.
     *
     *  Input Parameters:
     *      cause - the cause value.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_RefusalCause (const ITS_OCTET
		       cause):SCCP_Cause (SCCP_PRM_REFUSAL_CAUSE, cause)
    {
    }
    /*.implementation:public,inline,SCCP_RefusalCause
     ************************************************************************
     *  Purpose:
     *      This method constructs a refusal cause object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_RefusalCause ():SCCP_Cause (SCCP_PRM_REFUSAL_CAUSE, 0)
    {
      haveCause = false;
    }
  };

/*.interface:SCCP_UserData
 *****************************************************************************
 *  Interface:
 *      SCCP_UserData
 *
 *  Purpose:
 *      This class implements the user data IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_UserData:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method constructs a user data object.
     *
     *  Input Parameters:
     *      data - the user data buffer pointer
     *      len - the length of the user data
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_UserData (const ITS_OCTET * data, const int len)
    {
      ie.param_id = SCCP_PRM_DATA;
      ie.param_length = len;
      memcpy (ie.param_data.userData.data, data, len);
    }
    /*.implementation:public,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method constructs a user data object.
     *
     *  Input Parameters:
     *      data - the user data buffer
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_UserData (const ITS_ByteArray & data, const int len)
    {
      ie.param_id = SCCP_PRM_DATA;
      ie.param_length = data.size ();
      memcpy (ie.param_data.userData.data, &data[0], data.size ());
    }
    /*.implementation:public,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method constructs a user data object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_UserData ()
    {
      ie.param_id = SCCP_PRM_DATA;
      ie.param_length = 0;
    }

    /*.implementation:public,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method retrieves the user data from a
     *      SCCP_UserData object.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - the buffer to copy the data into
     *      len - the length of the user data
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     ************************************************************************/
    void GetUserData (ITS_OCTET * buf, int &len) const
    {
      len = ie.param_length;
      memcpy (buf, ie.param_data.userData.data, len);
    }
    /*.implementation:public,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method retrieves the user data from a
     *      SCCP_UserData object.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - the buffer to copy the data into
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     ************************************************************************/
    void GetUserData (ITS_ByteArray & buf) const
    {
      ITS_THROW_ASSERT (ie.param_length < SCCP_MAX_DATA);

      buf.assign (ie.param_data.userData.data,
		  ie.param_data.userData.data + ie.param_length);
    }

    /*.implementation:public,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method sets the user data for an SCCP_UserData
     *      object.
     *
     *  Input Parameters:
     *      buf - the buffer to copy from
     *      len - the length of the buffer
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetUserData (const ITS_OCTET * buf, int &len)
    {
      ie.param_length = len;
      memcpy (ie.param_data.userData.data, buf, len);
    }
    /*.implementation:public,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method sets the user data for an SCCP_UserData
     *      object.
     *
     *  Input Parameters:
     *      buf - the buffer to copy from
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetUserData (const ITS_ByteArray & buf)
    {
      ie.param_length = buf.size ();
      memcpy (ie.param_data.userData.data, &buf[0], buf.size ());
    }

  protected:
    /*.implementation:protected,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method encodes SCCP user data into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      GetUserData (buf, len);

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into an SCCP user data object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      SetUserData (buf, len);

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_UserData
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_UserData object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_UserData *ret = new SCCP_UserData (*this);

      return (SCCP_IEClass *) ret;
    }
  };

/*.interface:SCCP_LongUserData
 *****************************************************************************
 *  Interface:
 *      SCCP_LongUserData
 *
 *  Purpose:
 *      This class implements the user data IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_LongUserData:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method constructs a long user data object.
     *
     *  Input Parameters:
     *      data - the user data buffer pointer
     *      len - the length of the user data
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_LongUserData (const ITS_OCTET * data, const ITS_USHORT len)
    {
      ie.param_id = SCCP_PRM_LONG_DATA;
      ie.param_data.longData.len = len;
      memcpy (ie.param_data.longData.data, data, len);
    }
    /*.implementation:public,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method constructs a long user data object.
     *
     *  Input Parameters:
     *      data - the user data buffer
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_LongUserData (const ITS_ByteArray & data, const ITS_USHORT len)
    {
      ie.param_id = SCCP_PRM_LONG_DATA;
      ie.param_data.longData.len = data.size ();
      memcpy (ie.param_data.longData.data, &data[0], data.size ());
    }
    /*.implementation:public,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method constructs a long user data object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_LongUserData ()
    {
      ie.param_id = SCCP_PRM_LONG_DATA;
      ie.param_data.longData.len = 0;
    }
    /*.implementation:public,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method retrieves the user data from a
     *      SCCP_LongUserData object.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - the buffer to copy the data into
     *      len - the length of the long user data
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     ************************************************************************/
    void GetLongUserData (ITS_OCTET * buf, int &len) const
    {
      len = ie.param_data.longData.len;
      memcpy (buf, ie.param_data.longData.data, len);
    }
    /*.implementation:public,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method retrieves the user data from a
     *      SCCP_LongUserData object.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - the buffer to copy the long data into
     *
     *  Return Value:
     *      None.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     ************************************************************************/
    void GetLongUserData (ITS_ByteArray & buf) const
    {
      ITS_THROW_ASSERT (ie.param_data.longData.len < SCCP_LONG_DATA_MAX);

      buf.assign (ie.param_data.longData.data,
		  ie.param_data.longData.data + ie.param_data.longData.len);
    }

    /*.implementation:public,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method sets the user data for an SCCP_LongUserData
     *      object.
     *
     *  Input Parameters:
     *      buf - the buffer to copy from
     *      len - the length of the buffer
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetLongUserData (const ITS_OCTET * buf, int &len)
    {
      ie.param_data.longData.len = len;
      memcpy (ie.param_data.longData.data, buf, len);
    }
    /*.implementation:public,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method sets the user data for an SCCP_LongUserData
     *      object.
     *
     *  Input Parameters:
     *      buf - the buffer to copy from
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetLongUserData (const ITS_ByteArray & buf)
    {
      ie.param_data.longData.len = buf.size ();
      memcpy (ie.param_data.longData.data, &buf[0], buf.size ());
    }

  protected:
    /*.implementation:protected,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method encodes SCCP long user data into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      GetLongUserData (buf, len);

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into an SCCP long user data 
     *      object.
     *
     *  Input Parameters:
     *      buf - the long data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the long data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      SetLongUserData (buf, len);

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_LongUserData
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_LongUserData object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_LongUserData *ret = new SCCP_LongUserData (*this);

      return (SCCP_IEClass *) ret;
    }
  };


/*.interface:SCCP_HopCount
 *****************************************************************************
 *  Interface:
 *      SCCP_HopCount
 *
 *  Purpose:
 *      This class implements the hop count IE.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_HopCount:public SCCP_IEClass
  {
  public:
    /*.implementation:public,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method constructs a hop count object.
     *
     *  Input Parameters:
     *      hops - the hop count value
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_HopCount (const ITS_OCTET hops):haveHopCount (true)
    {
      ie.param_id = SCCP_PRM_HOP_COUNTER;
      ie.param_length = sizeof (SCCP_HOP_COUNT);
      ie.param_data.hopCount.count = hops;
    }
    /*.implementation:public,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method constructs a hop count object.
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    SCCP_HopCount ():haveHopCount (false)
    {
      ie.param_id = SCCP_PRM_HOP_COUNTER;
      ie.param_length = sizeof (SCCP_HOP_COUNT);
    }

    /*.implementation:public,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method determines if the hop count value from a
     *      SCCP_HopCount object has been set.
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
     *      true - the hop count has been set.  false otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool HasHopCount ()const
    {
      return (haveHopCount);
    }
    /*.implementation:public,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method retrieves the hop count value from a
     *      SCCP_HopCount object.
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
     *      The hop count value as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetHopCount () const
    {
      ITS_THROW_ASSERT (haveHopCount);

      return ie.param_data.hopCount.count;
    }
    /*.implementation:public,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method sets the hop count value for an SCCP_HopCount
     *      object.
     *
     *  Input Parameters:
     *      hops - the value to store for hop count
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
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void SetHopCount (const ITS_OCTET hops)
    {
      haveHopCount = true;

      ie.param_data.hopCount.count = hops;
    }

  protected:
    /*.implementation:protected,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method encodes a hop count value into a byte stream.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded IE.
     *
     *  Return Value:
     *      If the object encodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     *      Decode()
     ************************************************************************/
    virtual int Encode (ITS_OCTET * buf, int &len) const
    {
      len = sizeof (SCCP_HOP_COUNT);
      memcpy (buf, &ie.param_data.hopCount, sizeof (SCCP_HOP_COUNT));

      return (ITS_SUCCESS);
    }
    /*.implementation:protected,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method decodes a byte stream into a hop count object.
     *
     *  Input Parameters:
     *      buf - the data to decode
     *
     *  Input/Output Parameters:
     *      len - the length of the data to decode.  The return is the actual
     *          length of the object.  In and out should match.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      If the object decodes successfully, ITS_SUCCESS is returned.
     *      Any other return value indicates an IntelliSS7 error.
     *
     *  Notes:
     *
     *  See Also:
     *      Encode()
     ************************************************************************/
    virtual int Decode (const ITS_OCTET * buf, int &len)
    {
      len = sizeof (SCCP_HOP_COUNT);
      memcpy (&ie.param_data.hopCount, buf, sizeof (SCCP_HOP_COUNT));

      haveHopCount = true;

      return (ITS_SUCCESS);
    }

    /*.implementation:protected,inline,SCCP_HopCount
     ************************************************************************
     *  Purpose:
     *      This method "clones", or duplicates, an SCCP_HopCount object.
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
     *      A pointer to the allocated object.
     *
     *  Notes:
     *      This method can throw exceptions during low memory conditions.
     *
     *  See Also:
     ************************************************************************/
    virtual SCCP_IEClass *Clone ()
    {
      SCCP_HopCount *ret = new SCCP_HopCount (*this);

      return (SCCP_IEClass *) ret;
    }

  private:
    bool haveHopCount;
  };

///////////////////////////////////////////////////////////////////////
//
// All Messages
//
///////////////////////////////////////////////////////////////////////

/*.interface:SCCP_ConnectionRequest
 *****************************************************************************
 *  Interface:
 *      SCCP_ConnectionRequest
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ConnectionRequest messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ConnectionRequest:public SCCP_MessageClass
  {
  public:
    SCCP_ConnectionRequest ():SCCP_MessageClass (SCCP_MSG_CR, SCCP_CR_Desc)
    {
    }

    /*.implementation:public,inline,SCCP_ConnectionRequest
     ************************************************************************
     *  Purpose:
     *      This method adds an element to a ConnectionRequest object.  This
     *      is necessary to build the routing label for MTP3.
     *
     ************************************************************************/
    virtual void AddIE (SCCP_IEClass * ie)
    {
      if (ie->GetID () == SCCP_PRM_CALLED_PARTY_ADDR)
	{
	  SCCP_CalledPartyAddr *cdp = (SCCP_CalledPartyAddr *) ie;

	  if (cdp->HasPointCode ())
	    {
	      SetDPC (cdp->GetPointCode ());
	    }

	  if (cdp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}
      else if (ie->GetID () == SCCP_PRM_CALLING_PARTY_ADDR)
	{
	  SCCP_CallingPartyAddr *clp = (SCCP_CallingPartyAddr *) ie;

	  if (clp->HasPointCode ())
	    {
	      SetOPC (clp->GetPointCode ());
	    }

	  if (clp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}

      SCCP_MessageClass::AddIE (ie);
    }

  private:
    SCCP_ConnectionRequest & operator= (SCCP_ConnectionRequest &)
    {
      return *this;
    }

    bool haveDPC;
  };

/*.interface:SCCP_ConnectionConfirm
 *****************************************************************************
 *  Interface:
 *      SCCP_ConnectionConfirm
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ConnectionConfirm messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ConnectionConfirm:public SCCP_MessageClass
  {
  public:
    SCCP_ConnectionConfirm ():SCCP_MessageClass (SCCP_MSG_CC, SCCP_CC_Desc)
    {
    }

  private:
      SCCP_ConnectionConfirm & operator= (SCCP_ConnectionConfirm &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ConnectionRefused
 *****************************************************************************
 *  Interface:
 *      SCCP_ConnectionRefused
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ConnectionRefused messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ConnectionRefused:public SCCP_MessageClass
  {
  public:
    SCCP_ConnectionRefused ():SCCP_MessageClass (SCCP_MSG_CREF,
						 SCCP_CREF_Desc)
    {
    }

  private:
      SCCP_ConnectionRefused & operator= (SCCP_ConnectionRefused &)
    {
      return *this;
    }
  };

/*.interface:SCCP_Released
 *****************************************************************************
 *  Interface:
 *      SCCP_Released
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      Released messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_Released:public SCCP_MessageClass
  {
  public:
    SCCP_Released ():SCCP_MessageClass (SCCP_MSG_RLSD, SCCP_RLSD_Desc)
    {
    }

  private:
      SCCP_Released & operator= (SCCP_Released &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ReleaseComplete
 *****************************************************************************
 *  Interface:
 *      SCCP_ReleaseComplete
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ReleaseComplete messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ReleaseComplete:public SCCP_MessageClass
  {
  public:
    SCCP_ReleaseComplete ():SCCP_MessageClass (SCCP_MSG_RLC, SCCP_RLC_Desc)
    {
    }

  private:
      SCCP_ReleaseComplete & operator= (SCCP_ReleaseComplete &)
    {
      return *this;
    }
  };

/*.interface:SCCP_DataForm1
 *****************************************************************************
 *  Interface:
 *      SCCP_DataForm1
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      DataForm1 messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_DataForm1:public SCCP_MessageClass
  {
  public:
    SCCP_DataForm1 ():SCCP_MessageClass (SCCP_MSG_DT1, SCCP_DT1_Desc)
    {
    }

  private:
      SCCP_DataForm1 & operator= (SCCP_DataForm1 &)
    {
      return *this;
    }
  };

/*.interface:SCCP_DataForm2
 *****************************************************************************
 *  Interface:
 *      SCCP_DataForm2
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      DataForm2 messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_DataForm2:public SCCP_MessageClass
  {
  public:
    SCCP_DataForm2 ():SCCP_MessageClass (SCCP_MSG_DT2, SCCP_DT2_Desc)
    {
    }

  private:
      SCCP_DataForm2 & operator= (SCCP_DataForm2 &)
    {
      return *this;
    }
  };

/*.interface:SCCP_Acknowledge
 *****************************************************************************
 *  Interface:
 *      SCCP_Acknowledge
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      Acknowledge messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_Acknowledge:public SCCP_MessageClass
  {
  public:
    SCCP_Acknowledge ():SCCP_MessageClass (SCCP_MSG_AK, SCCP_AK_Desc)
    {
    }

  private:
      SCCP_Acknowledge & operator= (SCCP_Acknowledge &)
    {
      return *this;
    }
  };

/*.interface:SCCP_UnitData
 *****************************************************************************
 *  Interface:
 *      SCCP_UnitData
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      UnitData messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_UnitData:public SCCP_MessageClass
  {
  public:
    SCCP_UnitData ():SCCP_MessageClass (SCCP_MSG_UDT, SCCP_UDT_Desc)
    {
    }

    /*.implementation:public,inline,SCCP_UnitData
     ************************************************************************
     *  Purpose:
     *      This method adds an element to a UnitData object.  This
     *      is necessary to build the routing label for MTP3.
     *
     ************************************************************************/
    virtual void AddIE (SCCP_IEClass * ie)
    {
      if (ie->GetID () == SCCP_PRM_CALLED_PARTY_ADDR)
	{
	  SCCP_CalledPartyAddr *cdp = (SCCP_CalledPartyAddr *) ie;

	  if (cdp->HasPointCode ())
	    {
	      SetDPC (cdp->GetPointCode ());
	    }

	  if (cdp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}
      else if (ie->GetID () == SCCP_PRM_CALLING_PARTY_ADDR)
	{
	  SCCP_CallingPartyAddr *clp = (SCCP_CallingPartyAddr *) ie;

	  if (clp->HasPointCode ())
	    {
	      SetOPC (clp->GetPointCode ());
	    }

	  if (clp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}

      SCCP_MessageClass::AddIE (ie);
    }

  private:
    SCCP_UnitData & operator= (SCCP_UnitData &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ExtendedUnitData
 *****************************************************************************
 *  Interface:
 *      SCCP_ExtendedUnitData
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ExtendedUnitData messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ExtendedUnitData:public SCCP_MessageClass
  {
  public:
    SCCP_ExtendedUnitData ():SCCP_MessageClass (SCCP_MSG_XUDT, SCCP_XUDT_Desc)
    {
    }

    /*.implementation:public,inline,SCCP_ExtendedUnitData
     ************************************************************************
     *  Purpose:
     *      This method adds an element to an ExtendedUnitData object.  This
     *      is necessary to build the routing label for MTP3.
     *
     ************************************************************************/
    virtual void AddIE (SCCP_IEClass * ie)
    {
      if (ie->GetID () == SCCP_PRM_CALLED_PARTY_ADDR)
	{
	  SCCP_CalledPartyAddr *cdp = (SCCP_CalledPartyAddr *) ie;

	  if (cdp->HasPointCode ())
	    {
	      SetDPC (cdp->GetPointCode ());
	    }

	  if (cdp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}
      else if (ie->GetID () == SCCP_PRM_CALLING_PARTY_ADDR)
	{
	  SCCP_CallingPartyAddr *clp = (SCCP_CallingPartyAddr *) ie;

	  if (clp->HasPointCode ())
	    {
	      SetOPC (clp->GetPointCode ());
	    }

	  if (clp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}

      SCCP_MessageClass::AddIE (ie);
    }

  private:
    SCCP_ExtendedUnitData & operator= (SCCP_ExtendedUnitData &)
    {
      return *this;
    }
  };


/*.interface:SCCP_LongUnitData
 *****************************************************************************
 *  Interface:
 *     SCCP_LongUnitData 
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      SCCP_LongUnitData messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_LongUnitData:public SCCP_MessageClass
  {
  public:
    SCCP_LongUnitData ():SCCP_MessageClass (SCCP_MSG_LUDT, SCCP_LUDT_Desc)
    {
    }

  private:
      SCCP_LongUnitData & operator= (SCCP_LongUnitData &)
    {
      return *this;
    }
  };


/*.interface:SCCP_LongUnitDataService
 *****************************************************************************
 *  Interface:
 *     SCCP_LongUnitDataService 
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      SCCP_LongUnitDataService messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_LongUnitDataService:public SCCP_MessageClass
  {
  public:
    SCCP_LongUnitDataService ():SCCP_MessageClass (SCCP_MSG_LUDT,
						   SCCP_LUDT_Desc)
    {
    }

  private:
      SCCP_LongUnitDataService & operator= (SCCP_LongUnitDataService &)
    {
      return *this;
    }
  };

/*.interface:SCCP_UnitDataService
 *****************************************************************************
 *  Interface:
 *      SCCP_UnitDataService
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      UnitDataService messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_UnitDataService:public SCCP_MessageClass
  {
  public:
    SCCP_UnitDataService ():SCCP_MessageClass (SCCP_MSG_UDTS, SCCP_UDTS_Desc)
    {
    }

    /*.implementation:public,inline,SCCP_UnitDataService
     ************************************************************************
     *  Purpose:
     *      This method adds an element to a UnitDataService object.  This
     *      is necessary to build the routing label for MTP3.
     *
     ************************************************************************/
    virtual void AddIE (SCCP_IEClass * ie)
    {
      if (ie->GetID () == SCCP_PRM_CALLED_PARTY_ADDR)
	{
	  SCCP_CalledPartyAddr *cdp = (SCCP_CalledPartyAddr *) ie;

	  if (cdp->HasPointCode ())
	    {
	      SetDPC (cdp->GetPointCode ());
	    }

	  if (cdp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}
      else if (ie->GetID () == SCCP_PRM_CALLING_PARTY_ADDR)
	{
	  SCCP_CallingPartyAddr *clp = (SCCP_CallingPartyAddr *) ie;

	  if (clp->HasPointCode ())
	    {
	      SetOPC (clp->GetPointCode ());
	    }

	  if (clp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}

      SCCP_MessageClass::AddIE (ie);
    }

  private:
    SCCP_UnitDataService & operator= (SCCP_UnitDataService &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ExtendedUnitDataService
 *****************************************************************************
 *  Interface:
 *      SCCP_ExtendedUnitDataService
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ExtendedUnitDataService messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ExtendedUnitDataService:public SCCP_MessageClass
  {
  public:
    SCCP_ExtendedUnitDataService ():SCCP_MessageClass (SCCP_MSG_XUDTS,
						       SCCP_XUDTS_Desc)
    {
    }

    /*.implementation:public,inline,SCCP_ExtendedUnitDataService
     ************************************************************************
     *  Purpose:
     *      This method adds an element to an ExtendedUnitDataService object.
     *      This is necessary to build the routing label for MTP3.
     *
     ************************************************************************/
    virtual void AddIE (SCCP_IEClass * ie)
    {
      if (ie->GetID () == SCCP_PRM_CALLED_PARTY_ADDR)
	{
	  SCCP_CalledPartyAddr *cdp = (SCCP_CalledPartyAddr *) ie;

	  if (cdp->HasPointCode ())
	    {
	      SetDPC (cdp->GetPointCode ());
	    }

	  if (cdp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}
      else if (ie->GetID () == SCCP_PRM_CALLING_PARTY_ADDR)
	{
	  SCCP_CallingPartyAddr *clp = (SCCP_CallingPartyAddr *) ie;

	  if (clp->HasPointCode ())
	    {
	      SetOPC (clp->GetPointCode ());
	    }

	  if (clp->IsInternationalRouting ())
	    {
	      SetNetworkIndicator (false);
	    }
	  else
	    {
	      SetNetworkIndicator (true);
	    }
	}

      SCCP_MessageClass::AddIE (ie);
    }

  private:
    SCCP_ExtendedUnitDataService & operator= (SCCP_ExtendedUnitDataService &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ExpeditedData
 *****************************************************************************
 *  Interface:
 *      SCCP_ExpeditedData
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ExpeditedData messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ExpeditedData:public SCCP_MessageClass
  {
  public:
    SCCP_ExpeditedData ():SCCP_MessageClass (SCCP_MSG_ED, SCCP_ED_Desc)
    {
    }

  private:
      SCCP_ExpeditedData & operator= (SCCP_ExpeditedData &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ExpeditedDataAcknowledge
 *****************************************************************************
 *  Interface:
 *      SCCP_ExpeditedDataAcknowledge
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ExpeditedDataAcknowledge messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ExpeditedDataAcknowledge:public SCCP_MessageClass
  {
  public:
    SCCP_ExpeditedDataAcknowledge ():SCCP_MessageClass (SCCP_MSG_EA,
							SCCP_EA_Desc)
    {
    }

  private:
      SCCP_ExpeditedDataAcknowledge & operator= (SCCP_ExpeditedDataAcknowledge
						 &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ResetRequest
 *****************************************************************************
 *  Interface:
 *      SCCP_ResetRequest
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ResetRequest messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ResetRequest:public SCCP_MessageClass
  {
  public:
    SCCP_ResetRequest ():SCCP_MessageClass (SCCP_MSG_RSR, SCCP_RSR_Desc)
    {
    }

  private:
      SCCP_ResetRequest & operator= (SCCP_ResetRequest &)
    {
      return *this;
    }
  };

/*.interface:SCCP_ResetConfirm
 *****************************************************************************
 *  Interface:
 *      SCCP_ResetConfirm
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      ResetConfirm messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_ResetConfirm:public SCCP_MessageClass
  {
  public:
    SCCP_ResetConfirm ():SCCP_MessageClass (SCCP_MSG_RSC, SCCP_RSC_Desc)
    {
    }

  private:
      SCCP_ResetConfirm & operator= (SCCP_ResetConfirm &)
    {
      return *this;
    }
  };

/*.interface:SCCP_Error
 *****************************************************************************
 *  Interface:
 *      SCCP_Error
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      Error messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_Error:public SCCP_MessageClass
  {
  public:
    SCCP_Error ():SCCP_MessageClass (SCCP_MSG_ERR, SCCP_ERR_Desc)
    {
    }

  private:
      SCCP_Error & operator= (SCCP_Error &)
    {
      return *this;
    }
  };

/*.interface:SCCP_InactivityTest
 *****************************************************************************
 *  Interface:
 *      SCCP_InactivityTest
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      InactivityTest messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
  class SCCP_InactivityTest:public SCCP_MessageClass
  {
  public:
    SCCP_InactivityTest ():SCCP_MessageClass (SCCP_MSG_IT, SCCP_IT_Desc)
    {
    }

  private:
      SCCP_InactivityTest & operator= (SCCP_InactivityTest &)
    {
      return *this;
    }
  };

/*.implementation:static,inline,SCCP_MessageClass
 ****************************************************************************
 *  Purpose:
 *      This method receives an SCCP_MessageClass object from SCCP.
 *
 *  Input Parameters:
 *      handle - the transport handle to send on
 *      ev - the its::Event to receive
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context for this message
 *      msg - a pointer to a pointer to the SCCP_MessageClass object
 *          received.
 *
 *  Return Value:
 *      If the message is successfully transmitted, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This method is static.  It acts as a general constructor for
 *      received SCCP messages.
 *
 *  See Also:
 *      Send
 ****************************************************************************/
  inline int
    SCCP_MessageClass::Receive (ITS_HANDLE handle, ITS_HDR * hdr,
				its::Event & ev, SCCP_MessageClass ** msg)
  {
    ITS_SCCP_IE ies[ITS_MAX_SCCP_IES];
    int ieCount, ret;
    SCCP_MessageClass *rval;

    *msg = NULL;

    switch (SCCP_MSG_TYPE ((&ev.GetEvent ())))
      {
      case SCCP_MSG_CR:
	rval = new SCCP_ConnectionRequest ();
	break;

      case SCCP_MSG_CC:
	rval = new SCCP_ConnectionConfirm ();
	break;

      case SCCP_MSG_CREF:
	rval = new SCCP_ConnectionRefused ();
	break;

      case SCCP_MSG_RLSD:
	rval = new SCCP_Released ();
	break;

      case SCCP_MSG_RLC:
	rval = new SCCP_ReleaseComplete ();
	break;

      case SCCP_MSG_DT1:
	rval = new SCCP_DataForm1 ();
	break;

      case SCCP_MSG_DT2:
	rval = new SCCP_DataForm2 ();
	break;

      case SCCP_MSG_AK:
	rval = new SCCP_Acknowledge ();
	break;

      case SCCP_MSG_UDT:
	rval = new SCCP_UnitData ();
	break;

      case SCCP_MSG_XUDT:
	rval = new SCCP_ExtendedUnitData ();
	break;

      case SCCP_MSG_UDTS:
	rval = new SCCP_UnitDataService ();
	break;

      case SCCP_MSG_XUDTS:
	rval = new SCCP_ExtendedUnitDataService ();
	break;

      case SCCP_MSG_ED:
	rval = new SCCP_ExpeditedData ();
	break;

      case SCCP_MSG_EA:
	rval = new SCCP_ExpeditedDataAcknowledge ();
	break;

      case SCCP_MSG_RSR:
	rval = new SCCP_ResetRequest ();
	break;

      case SCCP_MSG_RSC:
	rval = new SCCP_ResetConfirm ();
	break;

      case SCCP_MSG_ERR:
	rval = new SCCP_Error ();
	break;

      case SCCP_MSG_IT:
	rval = new SCCP_InactivityTest ();
	break;

      case SCCP_MSG_LUDT:
	rval = new SCCP_LongUnitData ();
	break;

      case SCCP_MSG_LUDTS:
	rval = new SCCP_LongUnitDataService ();
	break;

      default:
	return (ITS_ERCVFAIL);
      }

    ret = SCCP_ReceiveEvent (handle, &ev.GetEvent (), hdr, ies, &ieCount,
			     &const_cast < SCCP_MSG_DESC & >(rval->desc));

    if (ret != ITS_SUCCESS)
      {
	return ret;
      }

    for (int i = 0; i < ieCount; i++)
      {
	SCCP_IEClass *ie;
	int len;

	switch (ies[i].param_id)
	  {
	  case SCCP_PRM_DEST_LOCAL_REF:
	    ie = new SCCP_DestinationLocalRef ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_SRC_LOCAL_REF:
	    ie = new SCCP_SourceLocalRef ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_CALLED_PARTY_ADDR:
	    ie = new SCCP_CalledPartyAddr ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data.
				    calledPartyAddr.data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_CALLING_PARTY_ADDR:
	    ie = new SCCP_CallingPartyAddr ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data.
				    callingPartyAddr.data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_PROTOCOL_CLASS:
	    ie = new SCCP_ProtocolClass ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_SEGMENT_REASSEM:
	    ie = new SCCP_SegmentReassem ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_RCV_SEQ_NUM:
	    ie = new SCCP_ReceiveSequenceNum ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_SEQUENCE_SEGMENT:
	    ie = new SCCP_SequenceSegment ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_CREDIT:
	    ie = new SCCP_Credit ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_RELEASE_CAUSE:
	    ie = new SCCP_ReleaseCause ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_RETURN_CAUSE:
	    ie = new SCCP_ReturnCause ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_RESET_CAUSE:
	    ie = new SCCP_ResetCause ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_ERROR_CAUSE:
	    ie = new SCCP_ErrorCause ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_REFUSAL_CAUSE:
	    ie = new SCCP_RefusalCause ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_DATA:
	    ie = new SCCP_UserData ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_LONG_DATA:
	    ie = new SCCP_LongUserData ();
	    len = ies[i].param_data.longData.len;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_HOP_COUNTER:
	    ie = new SCCP_HopCount ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  case SCCP_PRM_ROUTING_LABEL:
	    rval->SetHeader (ies[i].param_data.routingLabel);
	    break;

	  case SCCP_PRM_IMPORTANCE:
	    ie = new SCCP_Importance ();
	    len = ies[i].param_length;
	    ITS_ASSERT (ie->Decode ((ITS_OCTET *) & ies[i].param_data,
				    len) == ITS_SUCCESS);
	    rval->ies[ie->GetID ()] = ie;
	    break;

	  default:
	    delete rval;

	    return (ITS_EINVALIDARGS);
	  }
      }

    *msg = rval;

    return (ITS_SUCCESS);
  }

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* ITS_SCCP_PP_H */
