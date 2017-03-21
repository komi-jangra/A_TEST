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
 *  ID: $Id: BSSAP++.h,v 1.2 2008-02-01 04:16:38 amaresh.prasad Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:12  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.2.4  2005/11/30 07:33:55  adutta
 * LOG: Added Authentication Failue message
 * LOG:
 * LOG: Revision 9.1.2.3  2005/11/18 05:03:35  adutta
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 9.1.2.2  2005/10/19 11:57:54  adutta
 * LOG: Skip parameter added for DTAP
 * LOG:
 * LOG: Revision 9.1.2.1  2005/09/29 07:10:27  adutta
 * LOG: Implemented Paging Response
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:06  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.4.1  2003/11/07 20:39:25  hcho
 * LOG: Added BSSAP unknown msg type and unknown ies return.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:34  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/10 16:57:36  ngoel
 * LOG: DTAP merge
 * LOG:
 * LOG: Revision 1.1.2.35  2002/05/24 20:37:24  ngoel
 * LOG: after MM fixes
 * LOG:
 * LOG: Revision 1.1.2.34  2002/05/21 14:49:54  ngoel
 * LOG: add comments
 * LOG:
 * LOG: Revision 1.1.2.33  2002/05/20 15:03:20  ngoel
 * LOG: correct class headers for CC
 * LOG:
 * LOG: Revision 1.1.2.32  2002/05/20 13:21:50  ngoel
 * LOG: add isExt to bearer data
 * LOG:
 * LOG: Revision 1.1.2.31  2002/05/17 19:46:22  ngoel
 * LOG: update cc message headers
 * LOG:
 * LOG: Revision 1.1.2.30  2002/05/17 13:21:15  ngoel
 * LOG: remove hard tabs
 * LOG:
 * LOG: Revision 1.1.2.29  2002/05/16 15:41:39  ngoel
 * LOG: add priority level ie
 * LOG:
 * LOG: Revision 1.1.2.28  2002/05/15 20:49:18  ngoel
 * LOG: after merge with MM
 * LOG:
 * LOG: Revision 1.1.2.27  2002/05/15 18:21:13  ngoel
 * LOG: add set t1flag
 * LOG:
 * LOG: Revision 1.1.2.26  2002/05/13 18:02:14  ngoel
 * LOG: add status messages
 * LOG:
 * LOG: Revision 1.1.2.25  2002/05/13 14:16:14  ngoel
 * LOG: ad call state
 * LOG:
 * LOG: Revision 1.1.2.24  2002/05/13 12:59:41  ngoel
 * LOG: complete bearer data ie
 * LOG:
 * LOG: Revision 1.1.2.23  2002/05/10 21:58:33  ngoel
 * LOG: add dtmf messages
 * LOG:
 * LOG: Revision 1.1.2.22  2002/05/09 20:56:12  ngoel
 * LOG: add key pad facility ie
 * LOG:
 * LOG: Revision 1.1.2.21  2002/05/09 20:40:59  ngoel
 * LOG: add auxillary state ie
 * LOG:
 * LOG: Revision 1.1.2.20  2002/05/09 20:11:34  ngoel
 * LOG: add clir ies
 * LOG:
 * LOG: Revision 1.1.2.19  2002/05/09 18:03:50  ngoel
 * LOG: add layer info in BSSAP_Message
 * LOG:
 * LOG: Revision 1.1.2.18  2002/05/08 20:27:33  ngoel
 * LOG: add cc capabilities ie
 * LOG:
 * LOG: Revision 1.1.2.17  2002/05/08 19:45:34  ngoel
 * LOG: add code
 * LOG:
 * LOG: Revision 1.1.2.16  2002/05/08 15:49:59  ngoel
 * LOG: add message
 * LOG:
 * LOG: Revision 1.1.2.15  2002/05/08 15:41:40  ngoel
 * LOG: define more ies
 * LOG:
 * LOG: Revision 1.1.2.14  2002/05/07 19:54:03  ngoel
 * LOG: dd ss version ie
 * LOG:
 * LOG: Revision 1.1.2.13  2002/05/07 19:34:07  ngoel
 * LOG: add message defs
 * LOG:
 * LOG: Revision 1.1.2.12  2002/05/07 18:57:12  ngoel
 * LOG: defone bearer data
 * LOG:
 * LOG: Revision 1.1.2.11  2002/05/07 16:03:05  ngoel
 * LOG: add redirecting address and sub address
 * LOG:
 * LOG: Revision 1.1.2.10  2002/05/07 14:31:30  ngoel
 * LOG: add cd and cg addresses
 * LOG:
 * LOG: Revision 1.1.2.9  2002/05/07 13:05:50  ngoel
 * LOG: add signal ie
 * LOG:
 * LOG: Revision 1.1.2.8  2002/05/07 00:29:19  ngoel
 * LOG: add low level comp info ie
 * LOG:
 * LOG: Revision 1.1.2.7  2002/05/06 21:53:32  ngoel
 * LOG: add high level compatibility
 * LOG:
 * LOG: Revision 1.1.2.6  2002/05/06 20:19:37  ngoel
 * LOG: connected subaddress
 * LOG:
 * LOG: Revision 1.1.2.5  2002/05/06 19:01:57  ngoel
 * LOG: add connected number ie
 * LOG:
 * LOG: Revision 1.1.2.4  2002/05/06 16:18:47  ngoel
 * LOG: add cc cause ie
 * LOG:
 * LOG: Revision 1.1.2.3  2002/05/06 14:30:52  ngoel
 * LOG: code repeat indicator
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/05 19:24:10  ngoel
 * LOG: merge
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/05 15:41:22  ngoel
 * LOG: start adding gsm 4.08
 * LOG:
 * LOG: Revision 6.1.4.2  2002/04/26 20:43:28  hxing
 * LOG: Build on Solaris.
 * LOG:
 * LOG: Revision 6.1.4.1  2002/04/24 22:20:54  hxing
 * LOG: Back port to PR5.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.5  2001/11/26 15:23:23  dzhang
 * LOG: mionr modification
 * LOG:
 * LOG: Revision 1.4  2001/11/19 17:08:04  dzhang
 * LOG: Move Classmark 1 and 2 in HandoverReq from Mandtory to optional
 * LOG:
 * LOG: Revision 1.3  2001/11/12 14:42:52  dzhang
 * LOG: update to latest spec version8.9.0
 * LOG:
 * LOG: Revision 1.2  2001/10/05 19:45:30  dzhang
 * LOG: Mionr modification on CircuitIdCodeList IE
 * LOG:
 * LOG: Revision 1.1  2001/10/02 21:51:58  dzhang
 * LOG: Initially check in after unit test
 * LOG:
 *
 ****************************************************************************/

#include <assert.h>

#ifndef ITS_BSSAP_PP_H
#define ITS_BSSAP_PP_H

#include <its++.h>

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#include <BSSAP.h>

#include <map>

/*
 * BSSAP error codes
 */
#define ITS_EBSSAP_UNKNOWN_MSG_TYPE       -1
#define ITS_EBSSAP_UNKNOWN_IE             -2

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:BSSAP_Element
 *****************************************************************************
 *  Interface:
 *      BSSAP_Element
 *
 *  Purpose:
 *      This class describes the basic interface to BSSAP information
 *      elements; all IE(s) are derived from this class.
 *
 *  Usage:
 *
 *****************************************************************************/
class BSSAP_Element
{
public:
    friend class BSSAP_Message;
    friend class BSSAP_OldBSStoNewBSSInfo;  // This IE's struct is the same 
                                            // as a msg.
    friend class BSSAP_NewBSStoOldBSSInfo;  // This IE's struct is the same 
                                            // as a msg.

    /*.implementation:public,inline,BSSAP_Element
     ************************************************************************
     *  Purpose:
     *      This method constructs a BSSAP_Element.  It requires that the
     *      IE identifier be set.  This is the only public constructor
     *      for the base class, which forces all derived classes to set
     *      the IE identifier when they are constructed.
     *
     *  Input Parameters:
     *      id - the parameter identifier for this parameter
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *        None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    BSSAP_Element(ITS_OCTET id)
    {
        memset(&ie, 0, sizeof(ITS_BSSAP_IE));

        ie.param_id = id;
        ie.param_length = 0;
    }
    /*.implementation:public,inline,BSSAP_Element
     ************************************************************************
     *  Purpose:
     *      This method destroys an BSSAP_Element.
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
     *        None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    virtual
    ~BSSAP_Element()
    {
    }

    /*.implementation:public,inline,BSSAP_Element
     ************************************************************************
     *  Purpose:
     *
     *  Input Parameters:
     *      None
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *        Information Element Identifier
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET GetID() const
    {
        return ie.param_id;
    }

protected:
    /*.implementation:public,abstract,BSSAP_Element
     ************************************************************************
     *  Purpose:
     *      This method encodes a single IE.  All IE types must implement
     *      this method.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded buffer
     *
     *  Return Value:
     *        None.
     *
     *  Notes:
     *      The "len" arguement should be an in/out parameter.  On the way
     *      in, it should contain the maximum size of the "buf" argument.
     *      This will change in a subsequent release, so it is recommended
     *      that you initialize the "len" parameter appropriately *now*.
     *
     *  See Also:
     ************************************************************************/
    virtual ITS_INT
    Encode(ITS_OCTET* buf, ITS_INT& len) = 0;

    /*.implementation:public,abstract,BSSAP_Element
     ************************************************************************
     *  Purpose:
     *      This method decodes a single IE.  All IE types must implement
     *      this method.
     *
     *  Input Parameters:
     *      buf - a pointer to the buffer to encode into
     *      len - the length of the encoded buffer
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *        None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    virtual ITS_INT 
    Decode(ITS_OCTET* buf, ITS_INT& len) = 0;

    /*.implementation:public,abstract,BSSAP_Element
     ************************************************************************
     *  Purpose:
     *      This method "clones" an BSSAP IE.  When IEs are added to a
     *      message, they are cloned into the map.
     *
     *  Input Parameters:
     *      id - the parameter identifier for this parameter
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
     *
     *  See Also:
     ************************************************************************/
    virtual BSSAP_Element*
    Clone() = 0;

    ITS_BSSAP_IE    ie;

private:
    BSSAP_Element() {}
};

/*.interface:BSSAP_Message
 *****************************************************************************
 *  Interface:
 *      BSSAP_Message
 *
 *  Purpose:
 *      This class defines the basic interface for BSSAP messages.  All BSSAP
 *      message types are derived from this class.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Message
{
public:
  
    typedef std::multimap<ITS_OCTET, BSSAP_Element*> BSSAP_ElementMap;

    BSSAP_Message(ITS_OCTET msgType);
    virtual ~BSSAP_Message();

    /*.implementation:public,inline,BSSAP_Message
     ************************************************************************
     *  Purpose:
     *      This method returns the message type for this message object.
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
     *      The message type identifier as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    const ITS_OCTET
    GetMsgType() const
    {
        return msgType;
    }

    /*.implementation:public,inline,BSSAP_Message
     ************************************************************************
     *  Purpose:
     *      This method returns the protocol discriminator 
     *      for this message object.
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
     *      The protocol discriminator as an unsigned char.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    const ITS_OCTET
    GetMDisc() const
    {
        return mDisc;
    }

    void            SetProtDiscr(ITS_OCTET type);
    ITS_OCTET       GetProtDiscr();
    void            SetTIVal(ITS_OCTET type);
    void            SetSkipVal(ITS_OCTET type);
    ITS_OCTET       GetTIVal();
    ITS_OCTET       GetSkipVal();
    void            SetTIFlag(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetTIFlag();


    static ITS_INT Encode(ITS_OCTET* data, ITS_INT& length, BSSAP_Message* msg);
    static ITS_INT Decode(ITS_OCTET* data, ITS_INT length, BSSAP_Message** msg);

    void  AddIE(ITS_OCTET ieID, BSSAP_Element* ie);
    const BSSAP_Element* FindIE(ITS_OCTET id);
    // Find out duplicate IE
    const BSSAP_Element* FindNextIE(ITS_OCTET id, const BSSAP_Element*);

protected:
    /*.implementation:public,abstract,BSSAP_Message
     ************************************************************************
     *  Purpose:
     *      This method, which is specific for ever message, checks to
     *      see if all mandatory parameters have been included.  This
     *      method is called as part of the Encode() procedure.
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
     *      If all mandatory IE(s) are included in this message, ITS_TRUE
     *      is returned.  Otherwise, ITS_FALSE is returned.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    virtual ITS_BOOLEAN
    CheckForMandatoryParams() = 0;

    BSSAP_ElementMap    ies;

    // Args needed for this message
    ITS_OCTET*  mArgs;
    ITS_INT     nmArgs;    
    ITS_OCTET*  oArgs;
    ITS_INT     noArgs;

    // discriminators
    ITS_OCTET   mDisc;
    ITS_OCTET   dlci;
    ITS_OCTET   l3h;

private:
    BSSAP_Message() {}
    BSSAP_Message(BSSAP_Message&) {}
    BSSAP_Message& operator=(BSSAP_Message&) { return *this; }

    ITS_OCTET msgType;
};

///////////////////////
// IEs
///////////////////////

/* --------------- 3.2.2.2 Circuit Identity Code -------------- */
/*.interface:BSSAP_CktIDCode
 *****************************************************************************
 *  Interface:
 *      BSSAP_CktIDCode
 *
 *  Purpose:
 *      This class implements the CIC IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CktIDCode : public BSSAP_Element
{
public:
    // Constructor and destructor
    BSSAP_CktIDCode();
    ~BSSAP_CktIDCode();

     // access methods
    void            SetPCMID(ITS_USHORT type);
    ITS_USHORT      GetPCMID();
    void            SetTimeslot(ITS_OCTET type);
    ITS_OCTET       GetTimeslot();

protected:
    // local encode/decode methods
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.3 Connection Release Requested -------------- */
/*.interface:BSSAP_ConRlsReq
 *****************************************************************************
 *  Interface:
 *      BSSAP_ConRlsReq
 *
 *  Purpose:
 *      This class implements the CRR IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ConRlsReq : public BSSAP_Element
{
public:
    BSSAP_ConRlsReq();
    ~BSSAP_ConRlsReq();

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.4 Resource Available -------------- */
/*.interface:BSSAP_ResAvail
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResAvaiL
 *
 *  Purpose:
 *      This class implements the ResourceAvailable IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResAvail : public BSSAP_Element
{
public:
    BSSAP_ResAvail();
    ~BSSAP_ResAvail();

    void          SetNumFullHalf(ITS_USHORT full, ITS_USHORT half, 
                                 const ITS_INT index);
    ITS_USHORT    GetNumFull(const ITS_INT index);
    ITS_USHORT    GetNumHalf(const ITS_INT index);  

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.5 Cause -------------- */
/*.interface:BSSAP_Cause
 *****************************************************************************
 *  Interface:
 *      BSSAP_Cause
 *
 *  Purpose:
 *        This class implements the Cause IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Cse : public BSSAP_Element
{
public:
    BSSAP_Cse();
    ~BSSAP_Cse();

    ITS_INT  SetCause(bool isExt, ITS_OCTET cause1, ITS_OCTET cause2);
    void     SetNationalCause(ITS_OCTET natClass, ITS_OCTET cause);
    void     GetCause(bool& isExt, bool& isNat, ITS_OCTET& classORcause1,
                               ITS_OCTET& cause2);

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.6 IMSI -------------- */
/*.interface:BSSAP_IMSI
 *****************************************************************************
 *  Interface:
 *      BSSAP_IMSI
 *
 *  Purpose:
 *        This class implements the IMSI IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_IMSI : public BSSAP_Element
{
public:
    BSSAP_IMSI();
    ~BSSAP_IMSI();

    void  SetDigits(char* digit, ITS_INT len);
    void  ClearDigits(ITS_INT len);
    void  GetDigits(char* digit, ITS_INT& len);
    void  SetDigitsB(ITS_OCTET* digit, ITS_INT len);   
    void  GetDigitsB(ITS_OCTET* digit, ITS_INT& len);

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*  Clone();

private:
    bool            havedigits;
};

/* ------------- 3.2.2.7 TMSI -------------- */
/*.interface:BSSAP_IMSI
 *****************************************************************************
 *  Interface:
 *      BSSAP_TMSI
 *
 *  Purpose:
 *        This class implements the TMSI IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TMSI : public BSSAP_Element
{
public:
    BSSAP_TMSI();
    ~BSSAP_TMSI();

    void      SetTMSI(ITS_UINT data);
    ITS_UINT  GetTMSI();

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.8  Number of MSs --------- */
/*.interface:BSSAP_NumMSs
 *****************************************************************************
 *  Interface:
 *      BSSAP_NumMSs
 *
 *  Purpose:
 *      This class implements the NumberOfMSs IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_NumMSs : public BSSAP_Element
{
public:
    BSSAP_NumMSs();
    ~BSSAP_NumMSs();

    void          SetNumHand(ITS_OCTET data);
    ITS_OCTET     GetNumHand();

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 3.2.2.9  Layer 3 Header Information.------- */
/*.interface:BSSAP_L3HeaderInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_L3HeaderInfo
 *
 *  Purpose:
 *      This class implements the Layer3HeaderInformation IE.  Normally this
 *      class is only used as an IE for those messages that require Layer3
 *      Header information.  However, OBJECTS OF THIS CLASS ARE USED FOR THOSE
 *      MESSAGES THAT ARE SENT AS LAYER 3 INFORMATION. There are but three
 *      messages that fall in the latter category:CMServiceRequest,PageResponse,
 *      and LocationUpdating.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_L3HeaderInfo : public BSSAP_Element
{
public:
    BSSAP_L3HeaderInfo();
    ~BSSAP_L3HeaderInfo();

    void            SetProtDiscr(ITS_OCTET type);
    ITS_OCTET       GetProtDiscr();
    void            SetTIVal(ITS_OCTET type);
    ITS_OCTET       GetTIVal();
    void            SetTIFlag(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetTIFlag();

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.10 Encryption Information -------------- */
/*.interface:BSSAP_EncryptionInformation
 *****************************************************************************
 *  Interface:
 *      BSSAP_EncryptionInformation
 *
 *  Purpose:
 *      This class implements the EncryptionInformation IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_EncryptionInformation : public BSSAP_Element
{
public:
    BSSAP_EncryptionInformation();
    ~BSSAP_EncryptionInformation();

    void          SetNoEncryption(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetNoEncryption();
    void          SetA5_1(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetA5_1();
    void          SetA5_2(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetA5_2();
    void          SetA5_3(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetA5_3();
    void          SetA5_4(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetA5_4();    
    void          SetA5_5(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetA5_5();
    void          SetA5_6(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetA5_6();
    void          SetA5_7(ITS_BOOLEAN type);
    ITS_BOOLEAN   GetA5_7();
    void          SetKey(ITS_OCTET* key, ITS_INT len);
    void          ClearKey(ITS_INT len);
    void          GetKey(ITS_OCTET* buf, ITS_INT& len);

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool            haveKey;
};

/* -------------- 3.2.2.11 Channel Type -------------- */
/*.interface:BSSAP_ChanType
 *****************************************************************************
 *  Interface:
 *      BSSAP_ChanType
 *
 *  Purpose:
 *      This class implements the ChannelType IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ChanType : public BSSAP_Element
{
public:
    BSSAP_ChanType();
    ~BSSAP_ChanType();

    void         SetSpeechDataID(ITS_OCTET id);
    ITS_OCTET    GetSpeechDataID();
    void         SetChanRateType(ITS_OCTET type);
    ITS_OCTET    GetChanRateType();
    void         SetExtForSpeech(ITS_BOOLEAN ixExt, ITS_INT n);
    ITS_BOOLEAN  GetExtForSpeech(ITS_INT n);
    void         SetExtForData(ITS_BOOLEAN ixExt, ITS_INT n);
    ITS_BOOLEAN  GetExtForData(ITS_INT n);
    void         SetPermitSpch(ITS_BOOLEAN isExt, ITS_OCTET id, ITS_INT n);
    void         GetPermitSpch(ITS_BOOLEAN &isExt, ITS_OCTET &id, ITS_INT n);
    void         SetTransparent(ITS_BOOLEAN transp);
    ITS_BOOLEAN  GetTransparent();
    void         SetDataTransp(ITS_BOOLEAN isExt, ITS_OCTET rate, 
                               ITS_BOOLEAN transp);
    void         GetDataTransp(ITS_BOOLEAN &ixExt, ITS_OCTET &rate, 
                               ITS_BOOLEAN &transp);
    void         SetIFDateRate(ITS_BOOLEAN isExt, ITS_OCTET rate);
    void         GetIFDateRate(ITS_BOOLEAN &ixExt, ITS_OCTET &rate);
    void         SetAsymInd(ITS_BOOLEAN isExt, ITS_OCTET rate);
    void         GetAsymInd(ITS_BOOLEAN &ixExt, ITS_OCTET &rate);

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*  Clone();
};

/* -------------- 3.2.2.12 Periodicity -------------- */
/*.interface:BSSAP_Period
 *****************************************************************************
 *  Interface:
 *      BSSAP_Period
 *
 *  Purpose:
 *      This class implements the Periodicity IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Period : public BSSAP_Element
{
public:
    BSSAP_Period();
    ~BSSAP_Period();

    void            SetPeriod(ITS_OCTET period);
    ITS_OCTET       GetPeriod();
    
protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* -------------- 3.2.2.13 Extended Resource Indicator -------------- */
/*.interface:BSSAP_ExtResInd
 *****************************************************************************
 *  Interface:
 *      BSSAP_ExtResInd
 *
 *  Purpose:
 *      This class implements the ExtendedResourceIndicator IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ExtResInd : public BSSAP_Element
{
public:
    BSSAP_ExtResInd();
    ~BSSAP_ExtResInd();

    void         SetTARR(ITS_BOOLEAN tarr);
    ITS_BOOLEAN  GetTARR();
    void         SetSM(ITS_BOOLEAN sm);
    ITS_BOOLEAN  GetSM();
    
protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* -------------- 3.2.2.14 Total Resource Accessible -------------- */
/*.interface:BSSAP_TotResAcc
 *****************************************************************************
 *  Interface:
 *      BSSAP_TotResAcc
 *
 *  Purpose:
 *      This class implements the TotalResourceAccessible IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TotResAcc : public BSSAP_Element
{
public:
    BSSAP_TotResAcc();
    ~BSSAP_TotResAcc();

    void            SetFullRate(ITS_USHORT type);
    ITS_USHORT      GetFullRate();
    void            SetHalfRate(ITS_USHORT type);
    ITS_USHORT      GetHalfRate();
    
protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.15 LSA Identifier --------------*/
/*.interface:BSSAP_LsaId
 *****************************************************************************
 *  Interface:
 *      BSSAP_LsaId
 *
 *  Purpose:
 *      This class implements the LSA Identifier IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LsaId : public BSSAP_Element
{
public:
    BSSAP_LsaId();
    ~BSSAP_LsaId();

    void            SetLSAIDBit1(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetLSAIDBit1();
    void            SetLSAID(ITS_UINT id);
    ITS_UINT        GetLSAID();

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.16 LSA Identifier List --------------*/
/*.interface:BSSAP_LsaIdList
 *****************************************************************************
 *  Interface:
 *      BSSAP_LsaIdList
 *
 *  Purpose:
 *      This class implements the LSA Identifier List IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LsaIdList : public BSSAP_Element
{
public:
    BSSAP_LsaIdList();
    ~BSSAP_LsaIdList();

    void            SetEscapePLMN(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetEscapePLMN();
    void            SetLSAID(BSSAP_LSAIdentifier id, const ITS_INT index);
    void            GetLSAID(BSSAP_LSAIdentifier& id, const ITS_INT index);
    ITS_INT         GetLSAIDCount();

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT          maxIndex;
};

/* ----------------- 3.2.2.17 Cell Identifier --------------------*/
/*.interface:BSSAP_CellID
 *****************************************************************************
 *  Interface:
 *      BSSAP_CellID
 *
 *  Purpose:
 *      This class implements the CellIdentifier IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CellID : public BSSAP_Element
{
public:
    BSSAP_CellID();
    ~BSSAP_CellID();

    // Set_ and Get_ using designed Macro, treat MNC and MCC as USHORT
    void       SetCellIDDisc(ITS_OCTET type);
    ITS_OCTET  GetCellIDDisc();
    ITS_INT    SetCellID(BSSAP_CellIDType& cellID);
    ITS_INT    GetCellID(BSSAP_CellIDType& cellID);
    ITS_INT    SetCellID(BSSAP_CellIdentifier& cellID);
    ITS_INT    GetCellID(BSSAP_CellIdentifier& cellID);
    
protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------------- 3.2.2.18 Priority ----------------- */
/*.interface:BSSAP_Pri
 *****************************************************************************
 *  Interface:
 *      BSSAP_Prio
 *
 *  Purpose:
 *      This class implements the Priority IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Prio : public BSSAP_Element
{
public:
    BSSAP_Prio();
    ~BSSAP_Prio();

    void            SetPriority(ITS_OCTET type);
    ITS_OCTET       GetPriority();
    void            SetQA(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetQA();
    void            SetPVI(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetPVI();
    void            SetPCI(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetPCI();

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.19 Classmark Information Type 2 ------------ */
/*.interface:BSSAP_ClassmarkInfo2
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClassmarkInfo2
 *
 *  Purpose:
 *      This class implements the ClassmarkInformationType2 IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClassmarkInfo2 : public BSSAP_Element
{
public:
    BSSAP_ClassmarkInfo2();
    ~BSSAP_ClassmarkInfo2();

    void            SetRFPowerCap(ITS_OCTET type);
    ITS_OCTET       GetRFPowerCap();
    void            SetA51(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA51();
    void            SetESIND(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetESIND();
    void            SetRevLevel(ITS_OCTET type);
    ITS_OCTET       GetRevLevel();
    void            SetFC(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetFC();
    void            SetVGCS(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetVGCS();
    void            SetVBS(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetVBS();
    void            SetSMCap(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetSMCap();
    void            SetSSSInd(ITS_OCTET type);
    ITS_OCTET       GetSSSInd();
    void            SetPSCap(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetPSCap();
    void            SetA52(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA52();
    void            SetA53(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA53();
    void            SetCMSP(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetCMSP();
    void            SetSoLSA(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetSoLSA();
    void            SetLCSVACap(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetLCSVACap();
    void            SetCM3(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetCM3();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.20 Classmark Information Type 3 ------------ */
/*.interface:BSSAP_ClassmarkInfo3
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClassmarkInfo3
 *
 *  Purpose:
 *      This class implements the ClassmarkInformationType3 IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClassmarkInfo3 : public BSSAP_Element
{
public:
    BSSAP_ClassmarkInfo3();
    ~BSSAP_ClassmarkInfo3();


    void            SetMultiBand(ITS_OCTET type);
    ITS_OCTET       GetMultiBand();
    void            SetMultiBand1(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMultiBand1();
    void            SetMultiBand2(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMultiBand2();
    void            SetMultiBand3(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMultiBand3();
    void            SetA54(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA54();
    void            SetA55(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA55();
    void            SetA56(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA56();
    void            SetA57(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA57();
    void            SetRadioCap1(ITS_OCTET type);
    ITS_OCTET       GetRadioCap1();
    void            SetRadioCap2(ITS_OCTET type);
    ITS_OCTET       GetRadioCap2();
    void            SetRGSMCap(ITS_OCTET type);
    ITS_OCTET       GetRGSMCap();
    void            SetMultiSlotClass(ITS_OCTET type);
    ITS_OCTET       GetMultiSlotClass();
    void            SetUCS2Treat(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetUCS2Treat();
    void            SetExtMeasCap(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetExtMeasCap();
    void            SetSMSValue(ITS_OCTET type);
    ITS_OCTET       GetSMSValue();
    void            SetSMValue(ITS_OCTET type);
    ITS_OCTET       GetSMValue();
    void            SetMSConGPS(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMSConGPS();
    void            SetMSBasedGPS(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMSBasedGPS();
    void            SetMSAssistedGPS(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMSAssistedGPS();
    void            SetMSBasedEOTD(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMSBasedEOTD();
    void            SetMSAssistedEOTD(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetMSAssistedEOTD();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.21 Interference Band To Be Used ------------ */
/*.interface:BSSAP_InterBandToBeUsed
 *****************************************************************************
 *  Interface:
 *      BSSAP_InterBandToBeUsed
 *
 *  Purpose:
 *      This class implements the InterferenceBandToBeUsed IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_InterBandToBeUsed : public BSSAP_Element
{
public:
    BSSAP_InterBandToBeUsed();
    ~BSSAP_InterBandToBeUsed();

    void            SetBandToBeUsed(ITS_OCTET type);
    ITS_OCTET       GetBandToBeUsed();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.22 RR Cause ------------ */
/*.interface:BSSAP_RRcause
 *****************************************************************************
 *  Interface:
 *      BSSAP_RRcause
 *
 *  Purpose:
 *      This class implements the RRCause IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RRcause : public BSSAP_Element
{
public:
    BSSAP_RRcause();
    ~BSSAP_RRcause();

    void            SetRRCause(ITS_OCTET type);
    ITS_OCTET       GetRRCause();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.23 LSA Information --------------*/
/*.interface:BSSAP_LsaInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_LsaInfo
 *
 *  Purpose:
 *      This class implements the LSA Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LsaInfo : public BSSAP_Element
{
public:
    BSSAP_LsaInfo();
    ~BSSAP_LsaInfo();

    void            SetLSAIndicator(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetLSAIndicator();
    void            SetLSAID(BSSAP_LSA lsa, const ITS_INT index);
    void            GetLSAID(BSSAP_LSA& lsa, const ITS_INT index);
    ITS_INT         GetLSAIDCount();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT             maxIndex;
};

/* --------------- 3.2.2.24 Layer 3 Information ------------ */
/*.interface:BSSAP_L3Info
 *****************************************************************************
 *  Interface:
 *      BSSAP_L3Info
 *
 *  Purpose:
 *      This class implements the Layer 3 Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_L3Info : public BSSAP_Element
{
public:
    BSSAP_L3Info();
    ~BSSAP_L3Info();

    void          SetL3Info(ITS_OCTET* buf, ITS_INT len);
    void          GetL3Info(ITS_OCTET* buf, ITS_INT &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool          haveL3Info;
};

/* --------------- 3.2.2.25 DLCI ------------ */
/*.interface:BSSAP_DLCI
 *****************************************************************************
 *  Interface:
 *      BSSAP_dlci
 *
 *  Purpose:
 *      This class implements the DLCI IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_dlci : public BSSAP_Element
{
public:
    BSSAP_dlci();
    ~BSSAP_dlci();

    void               SetCtrlChan(ITS_OCTET type);
    ITS_OCTET          GetCtrlChan();
    void               SetSAPI(ITS_OCTET type);
    ITS_OCTET          GetSAPI();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 3.2.2.26 Downlink DTX Flag -------- */
/*.interface:BSSAP_DLDTXFlag
 *****************************************************************************
 *  Interface:
 *      BSSAP_DLDTXFlag
 *
 *  Purpose:
 *      This class implements the DownlinkDTXFlag IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_DLDTXFlag : public BSSAP_Element
{
public:
    BSSAP_DLDTXFlag();
    ~BSSAP_DLDTXFlag();

    void            SetDTXFlag(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetDTXFlag();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.27 Cell Identifier List --------------*/
/*.interface:BSSAP_CellIDList
 *****************************************************************************
 *  Interface:
 *      BSSAP_CellIDList
 *
 *  Purpose:
 *      This class implements the CellIdentifierList IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CellIDList : public BSSAP_Element
{
public:
    BSSAP_CellIDList();
    ~BSSAP_CellIDList();

    void            SetCellIDListDisc(ITS_OCTET type);
    ITS_OCTET       GetCellIDListDisc();
    void            AddCellID(BSSAP_CellIDT cid);
    void            SetCellID(BSSAP_CellIDT cid, const ITS_INT n);
    void            GetCellID(BSSAP_CellIDT& cid, const ITS_INT n);
    ITS_INT         GetCellIDCount();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT             maxIndex;
};

/* ---------- 3.2.2.28 Response Request --------- */
/*.interface:BSSAP_RspReq
 *****************************************************************************
 *  Interface:
 *      BSSAP_RspReq
 *
 *  Purpose:
 *      This class implements the ResposeRequest IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RspReq : public BSSAP_Element
{
public:
    BSSAP_RspReq();
    ~BSSAP_RspReq();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};


/* ---------- 3.2.2.29 Resource Indication Method --------- */
/*.interface:BSSAP_ResIndMethod
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResIndMethod
 *
 *  Purpose:
 *      This class implements the ResourceIndicationMethod IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResIndMethod : public BSSAP_Element
{
public:
    BSSAP_ResIndMethod();
    ~BSSAP_ResIndMethod();

    void        SetResIndMethod(ITS_OCTET type);
    ITS_OCTET   GetResIndMethod();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 3.2.2.30 Classmark Information Type 1 -------- */
/*.interface:BSSAP_ClassmarkInfo1
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClassmarkInfo1
 *
 *  Purpose:
 *      This class implements the ClassmarkInformationType1 IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClassmarkInfo1 : public BSSAP_Element
{
public:
    BSSAP_ClassmarkInfo1();
    ~BSSAP_ClassmarkInfo1();

    void            SetRFPowerCap(ITS_OCTET type);
    ITS_OCTET       GetRFPowerCap();
    void            SetA51(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetA51();
    void            SetESIND(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetESIND();
    void            SetRevLevel(ITS_OCTET type);
    ITS_OCTET       GetRevLevel();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.31 Circuit Identity Code List ----------- */
/*.interface:BSSAP_CktIDCodeList
 *****************************************************************************
 *  Interface:
 *      BSSAP_CktIDCodeList
 *
 *  Purpose:
 *      This class implements the CktIDCodeList IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CktIDCodeList : public BSSAP_Element
{
public:
    BSSAP_CktIDCodeList();
    ~BSSAP_CktIDCodeList();

    void            SetRange(ITS_OCTET range);
    ITS_OCTET       GetRange();
    void            SetStatusBit(ITS_BOOLEAN type, ITS_INT bitn);
/* Added by Amaresh for set status bit & get status bit pos */
    void            SetStatusBitPos(ITS_BOOLEAN type, ITS_INT bitn, ITS_OCTET StartTs, ITS_OCTET range);
    ITS_BOOLEAN     GetStatusBitPos(ITS_INT bitn, ITS_OCTET StartTs);
/* Added by Amaresh for set status bit & get status bit pos */
    ITS_BOOLEAN     GetStatusBit(ITS_INT bitn);
    void            SetStatus(ITS_OCTET* buf, ITS_INT len);
    void            GetStatus(ITS_OCTET *buf, ITS_INT &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool            haveRange;
};

/* ------------ 3.2.2.32 Diagnostics ----------- */
/*.interface:BSSAP_Diagn
 *****************************************************************************
 *  Interface:
 *      BSSAP_Diagn
 *
 *  Purpose:
 *      This class implements the Diagnostics IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Diagn : public BSSAP_Element
{
public:
    BSSAP_Diagn();
    ~BSSAP_Diagn();

    void            SetErrPtr(ITS_OCTET err);
    ITS_OCTET       GetErrPtr();
    void            SetBitPtr(ITS_OCTET bit);
    ITS_OCTET       GetBitPtr();
    void            SetMsgRcvd(ITS_OCTET* buf, ITS_INT len);
    void            GetMsgRcvd(ITS_OCTET* buf, ITS_INT &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool            haveMsgRcvd;
};

/* ------------ 3.2.2.33 Chosen Channel ----------- */
/*.interface:BSSAP_ChsChan
 *****************************************************************************
 *  Interface:
 *      BSSAP_ChsChan
 *
 *  Purpose:
 *      This class implements the ChosenChannel IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ChsChan : public BSSAP_Element
{
public:
    BSSAP_ChsChan();
    ~BSSAP_ChsChan();

    void            SetChan(ITS_USHORT type);
    ITS_USHORT      GetChan();
    void            SetChanMode(ITS_OCTET type);
    ITS_OCTET       GetChanMode();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.34 Cipher Response Mode ------------- */
/*.interface:BSSAP_CipherRspMode
 *****************************************************************************
 *  Interface:
 *      BSSAP_CipherRspMode
 *
 *  Purpose:
 *      This class implements the CipherResponseMode IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CipherRspMode : public BSSAP_Element
{
public:
    BSSAP_CipherRspMode();
    ~BSSAP_CipherRspMode();

    void            SetCipherRspMode(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetCipherRspMode();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.35 Layer 3 Messge Contents ------------- */
/*.interface:BSSAP_L3MsgCnt
 *****************************************************************************
 *  Interface:
 *      BSSAP_L3MsgCnt
 *
 *  Purpose:
 *      This class implements the L3MsgCnt IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_L3MsgCnt : public BSSAP_Element
{
public:
    BSSAP_L3MsgCnt();
    ~BSSAP_L3MsgCnt();

    void            SetL3MsgCnt(ITS_OCTET* buf, ITS_INT len);
    void            GetL3MsgCnt(ITS_OCTET* buf, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual         BSSAP_Element*    Clone();

private:
    bool            haveMsgCnt;
};

/* ---------- 3.2.2.36 Channel Needed ------------- */
/*.interface:BSSAP_ChanNeeded
 *****************************************************************************
 *  Interface:
 *      BSSAP_ChanNeeded
 *
 *  Purpose:
 *      This class implements the ChannelNeeded IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ChanNeeded : public BSSAP_Element
{
public:
    BSSAP_ChanNeeded();
    ~BSSAP_ChanNeeded();

    void            SetChan(ITS_OCTET type);
    ITS_OCTET       GetChan();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.37 Trace Type ------------- */
/*.interface:BSSAP_TraceTyp
 *****************************************************************************
 *  Interface:
 *      BSSAP_TraceTyp
 *
 *  Purpose:
 *      This class implements the TraceType IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TraceTyp : public BSSAP_Element
{
public:
    BSSAP_TraceTyp();
    ~BSSAP_TraceTyp();

    void            SetInvEvnt(ITS_OCTET type);
    ITS_OCTET       GetInvEvnt();
    void            SetMSCRecType(ITS_OCTET type);
    ITS_OCTET       GetMSCRecType();
    void            SetBSSRecType(ITS_OCTET type);
    ITS_OCTET       GetBSSRecType();
    void            SetPrioInd(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetPrioInd();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.38 TriggerID ------------- */
/*.interface:BSSAP_TrigID
 *****************************************************************************
 *  Interface:
 *      BSSAP_TrigID
 *
 *  Purpose:
 *      This class implements the TriggerID IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TrigID : public BSSAP_Element
{
public:
    BSSAP_TrigID();
    ~BSSAP_TrigID();

    void            SetEntityID(ITS_OCTET* buff, ITS_INT len);
    void            GetEntityID(ITS_OCTET* buff, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.39 Trace Reference ------------- */
/*.interface:BSSAP_TraceRef
 *****************************************************************************
 *  Interface:
 *      BSSAP_TraceRef
 *
 *  Purpose:
 *      This class implements the TraceRef IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TraceRef : public BSSAP_Element
{
public:
    BSSAP_TraceRef();
    ~BSSAP_TraceRef();

    void            SetTraceRef(ITS_USHORT type);
    ITS_USHORT      GetTraceRef();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------ 3.2.2.40 TransactionID ------------- */
/*.interface:BSSAP_TransactionID
 *****************************************************************************
 *  Interface:
 *      BSSAP_TransactionID
 *
 *  Purpose:
 *      This class implements the TransactionID IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TransactionID : public BSSAP_Element
{
public:
    BSSAP_TransactionID();
    ~BSSAP_TransactionID();

    void            SetTransNo(ITS_USHORT type);
    ITS_USHORT      GetTransNo();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.41 Mobile Identity -------------- */
/*.interface:BSSAP_MobileID
 *****************************************************************************
 *  Interface:
 *      BSSAP_MobileID
 *
 *  Purpose:
 *      This class implements the MobileID IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_MobileID : public BSSAP_Element
{
public:
    BSSAP_MobileID();
    ~BSSAP_MobileID();

    void            SetOddEvenInd(ITS_OCTET type);
    ITS_OCTET       GetOddEvenInd();
    void            SetTypeIdentity(ITS_OCTET type);
    ITS_OCTET       GetTypeIdentity();
    void            SetIdenCDig(char* setdig, ITS_INT len);    
    void            ClearIdenDigits(ITS_INT len);
    void            GetIdenCDig(char* getdig, ITS_INT& len);
    void            GetIdenBDig(ITS_OCTET* getdig, ITS_INT& nDigits);
    void            SetIdenBDig(ITS_OCTET* setdig, ITS_INT nDigits);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool            haveIdDgts;
};

/* ------------- 3.2.2.42 OMCID -------------- */
/*.interface:BSSAP_omcid
 *****************************************************************************
 *  Interface:
 *      BSSAP_omcid
 *
 *  Purpose:
 *      This class implements the OMCID IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_OMCID : public BSSAP_Element
{
public:
    BSSAP_OMCID();
    ~BSSAP_OMCID();

    void            SetOMCID(ITS_OCTET* buff, ITS_INT len);
    void            GetOMCID(ITS_OCTET* buff, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.43 Forward Indicator -------------- */
/*.interface:BSSAP_FwdInd
 *****************************************************************************
 *  Interface:
 *      BSSAP_FwdInd
 *
 *  Purpose:
 *      This class implements the ForwardIndicator IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_FwdInd : public BSSAP_Element
{
public:
    BSSAP_FwdInd();
    ~BSSAP_FwdInd();

    void            SetFwdInd(ITS_OCTET type);
    ITS_OCTET       GetFwdInd();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.44 Chosen Encryption Algorithm -------------- */
/*.interface:BSSAP_ChsEncAlg
 *****************************************************************************
 *  Interface:
 *      BSSAP_ChsEncAlg
 *
 *  Purpose:
 *      This class implements the ChosenEncryptionAlgorithm IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ChsEncAlg : public BSSAP_Element
{
public:
    BSSAP_ChsEncAlg();
    ~BSSAP_ChsEncAlg();

    void            SetAlgorithmID(ITS_OCTET type);
    ITS_OCTET       GetAlgorithmID();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.45 Circuit Pool -------------- */
/*.interface:BSSAP_CktPool
 *****************************************************************************
 *  Interface:
 *      BSSAP_CktPool
 *
 *  Purpose:
 *      This class implements the CircuitPool IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CktPool : public BSSAP_Element
{
public:
    BSSAP_CktPool();
    ~BSSAP_CktPool();

    void            SetCircuitPoolNo(ITS_OCTET type);
    ITS_OCTET       GetCircuitPoolNo();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.46 Circuit Pool List -------------- */
/*.interface:BSSAP_BSSAP_CktPoolList
 *****************************************************************************
 *  Interface:
 *      BSSAP_CktPoolList
 *
 *  Purpose:
 *      This class implements the CircuitPool List IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CktPoolList : public BSSAP_Element
{
public:
    BSSAP_CktPoolList();
    ~BSSAP_CktPoolList();

    void     AddCircuitPoolNo(BSSAP_CircuitPool cpn);
    void     SetCircuitPoolNo(BSSAP_CircuitPool cpn, const ITS_INT n);
    void     GetCircuitPoolNo(BSSAP_CircuitPool& cpn, const ITS_INT n);
    ITS_INT  GetCktPlNoCount();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT             maxIndex;
};

/* ------------- 3.2.2.47 Time Indication -------------- */
/*.interface:BSSAP_TimeInd
 *****************************************************************************
 *  Interface:
 *      BSSAP_TimeInd
 *
 *  Purpose:
 *      This class implements the TimeIndication IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TimeInd : public BSSAP_Element
{
public:
    BSSAP_TimeInd();
    ~BSSAP_TimeInd();

    void            SetTime(ITS_OCTET time);
    ITS_OCTET       GetTime();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.48 Resource Situation -------------- */
/*.interface:BSSAP_ResSituation
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResSituation
 *
 *  Purpose:
 *      This class implements the Resource Situation IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResSituation : public BSSAP_Element
{
public:
    BSSAP_ResSituation();
    ~BSSAP_ResSituation();

    void            AddResSitnElmnt(BSSAP_ResSitnElmnt rse);
    void            SetResSitnElmnt(BSSAP_ResSitnElmnt rse, const ITS_INT n);
    void            GetResSitnElmnt(BSSAP_ResSitnElmnt& rse, const ITS_INT n);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT             maxIndex;       
};

/* ------------- 3.2.2.49 Current Channel Type 1-------------- */
/*.interface:BSSAP_CrttChan
 *****************************************************************************
 *  Interface:
 *      BSSAP_CrtChan
 *
 *  Purpose:
 *      This class implements the Current Channel Type 1 IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CrtChan : public BSSAP_Element
{
public:
    BSSAP_CrtChan();
    ~BSSAP_CrtChan();

    void            SetChan(ITS_OCTET type);
    ITS_OCTET       GetChan();
    void            SetChanMode(ITS_OCTET type);
    ITS_OCTET       GetChanMode();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.50 Queuing Indicator -------------- */
/*.interface:BSSAP_QueuingInd
 *****************************************************************************
 *  Interface:
 *      BSSAP_QueuingInd
 *
 *  Purpose:
 *      This class implements the QueuingIndicator IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_QueuingInd : public BSSAP_Element
{
public:
    BSSAP_QueuingInd();
    ~BSSAP_QueuingInd();

    void            SetQRI(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetQRI();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.51 Speech Version -------------- */
/*.interface:BSSAP_SpchVer
 *****************************************************************************
 *  Interface:
 *      BSSAP_SpchVer
 *
 *  Purpose:
 *      This class implements the SpeechVersion IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_SpchVer : public BSSAP_Element
{
public:
    BSSAP_SpchVer();
    ~BSSAP_SpchVer();

    void            SetSpchVerID(ITS_OCTET type);
    ITS_OCTET       GetSpchVerID();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.52 Assignment Requirement -------------- */
/*.interface:BSSAP_AssReq
 *****************************************************************************
 *  Interface:
 *      BSSAP_AssReq
 *
 *  Purpose:
 *      This class implements the AssignmentRequirement IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AssReq : public BSSAP_Element
{
public:
    BSSAP_AssReq();
    ~BSSAP_AssReq();

    void            SetAssReq(ITS_OCTET type);
    ITS_OCTET       GetAssReq();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.54 Talker Flag -------------- */
/*.interface:BSSAP_TalkerFlag
 *****************************************************************************
 *  Interface:
 *      BSSAP_TalkerFlag
 *
 *  Purpose:
 *      This class implements the TalkerFlag IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TalkerFlag : public BSSAP_Element
{
public:
    BSSAP_TalkerFlag();
    ~BSSAP_TalkerFlag();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.55 Group Call Reference -------------- */
/*.interface:BSSAP_GrpClRef
 *****************************************************************************
 *  Interface:
 *      BSSAP_GrpClRef
 *
 *  Purpose:
 *      This class implements the GrpClRef IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_GrpClRef : public BSSAP_Element
{
public:
    BSSAP_GrpClRef();
    ~BSSAP_GrpClRef();

    void            SetCallRef(ITS_UINT type);
    ITS_UINT        GetCallRef();
    void            SetClPrio(ITS_OCTET type);
    ITS_OCTET       GetClPrio();
    void            SetAF(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetAF();
    void            SetSF(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetSF();
    void            SetCiphInfo(ITS_OCTET type);
    ITS_OCTET       GetCiphInfo();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.56 eMML Priority -------------- */
/*.interface:BSSAP_eMMLPrio
 *****************************************************************************
 *  Interface:
 *      BSSAP_GrpeMMLPrio
 *
 *  Purpose:
 *      This class implements the eMMLPriority IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_eMMLPrio : public BSSAP_Element
{
public:
    BSSAP_eMMLPrio();
    ~BSSAP_eMMLPrio();

    void            SetClPrio(ITS_OCTET type);
    ITS_OCTET       GetClPrio();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 3.2.2.57 Configuration Evolution Indication ------------ */
/*.interface:BSSAP_ConfigEvlInd
 *****************************************************************************
 *  Interface:
 *      BSSAP_ConfigEvlInd
 *
 *  Purpose:
 *      This class implements the ConfigurationEvolutionIndication IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ConfigEvlInd : public BSSAP_Element
{
public:
    BSSAP_ConfigEvlInd();
    ~BSSAP_ConfigEvlInd();

    void            SetSMI(ITS_OCTET type);
    ITS_OCTET       GetSMI();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 3.2.2.58 Old BSS to New BSS Information ------------ */
/*.interface:BSSAP_OldBSStoNewBSSInfo
 *****************************************************************************
 *  Interface:
 *     
 *
 *  Purpose:
 *      This class implements the Old BSS to New BSS Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_OldBSStoNewBSSInfo : public BSSAP_Element
{
public:
    BSSAP_OldBSStoNewBSSInfo();
    ~BSSAP_OldBSStoNewBSSInfo();

    typedef std::map<ITS_OCTET, BSSAP_Element*> BSSAP_ElementMap;

    void  AddIE(ITS_OCTET ieID, BSSAP_Element* ie);
    const BSSAP_Element* FindIE(ITS_OCTET id);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* data, ITS_INT& length);
    virtual ITS_INT     Decode(ITS_OCTET* data, ITS_INT& length);

    virtual BSSAP_Element*  Clone();

    BSSAP_ElementMap  map;

    ITS_OCTET*  ieArgs;
    ITS_INT     noArgs;
};

/* ----------- 3.2.2.80 New BSS to Old BSS Information ------------ */
/*.interface:BSSAP_NewBSStoOldBSSInfo
 *****************************************************************************
 *  Interface:
 *    
 *
 *  Purpose:
 *      This class implements the Old BSS to New BSS Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_NewBSStoOldBSSInfo : public BSSAP_Element
{
public:
    BSSAP_NewBSStoOldBSSInfo();
    ~BSSAP_NewBSStoOldBSSInfo();
    
    typedef std::map<ITS_OCTET, BSSAP_Element*> BSSAP_ElementMap;

    void  AddIE(ITS_OCTET ieID, BSSAP_Element* ie);
    const BSSAP_Element* FindIE(ITS_OCTET id);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* data, ITS_INT& length);
    virtual ITS_INT     Decode(ITS_OCTET* data, ITS_INT& length);

    virtual BSSAP_Element*  Clone();

    BSSAP_ElementMap  map;

    ITS_OCTET*  ieArgs;
    ITS_INT     noArgs;
};

/* --------------- 3.2.2.60 LCS QoS -------------- */
/*.interface:BSSAP_LcsQoS
 *****************************************************************************
 *  Interface:
 *      BSSAP_LcsQoS
 *
 *  Purpose:
 *      This class implements the Return LCS QoS IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LcsQoS : public BSSAP_Element
{
public:
    BSSAP_LcsQoS();
    ~BSSAP_LcsQoS();


    void          SetVERT(ITS_BOOLEAN ind);
    ITS_BOOLEAN   GetVERT();
    void          SetHA(ITS_BOOLEAN ind);
    ITS_BOOLEAN   GetHA();
    void          SetHorizAccuracy(ITS_OCTET acc);
    ITS_OCTET     GetHorizAccuracy();
    void          SetVA(ITS_BOOLEAN ind);
    ITS_BOOLEAN   GetVA();
    void          SetVertAccuracy(ITS_OCTET acc);
    ITS_OCTET     GetVertAccuracy();
    void          SetRspTime(ITS_OCTET time);
    ITS_OCTET     GetRspTime();
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.61 LSA Access Control Suppression -------------- */
/*.interface:BSSAP_LsaAccCtrlSuppr
 *****************************************************************************
 *  Interface:
 *      BSSAP_LsaAccCtrlSuppr
 *
 *  Purpose:
 *      This class implements the Return LSA Access Control Suppression IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LsaAccCtrlSuppr : public BSSAP_Element
{
public:
    BSSAP_LsaAccCtrlSuppr();
    ~BSSAP_LsaAccCtrlSuppr();

    void          SetEmergency(ITS_BOOLEAN em);
    ITS_BOOLEAN   GetEmergency();
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.62 LCS Priority -------------- */
/*.interface:BSSAP_LCSPrio
 *****************************************************************************
 *  Interface:
 *      BSSAP_LsaAccCtrlSuppr
 *
 *  Purpose:
 *      This class implements the Return LCS Priority IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LCSPrio : public BSSAP_Element
{
public:
    BSSAP_LCSPrio();
    ~BSSAP_LCSPrio();

    void          SetPriority(ITS_OCTET *buf);
    void          GetPriority(ITS_OCTET *buf);
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.63 Location Type -------------- */
/*.interface:BSSAP_LocType
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocType
 *
 *  Purpose:
 *      This class implements the Return Location Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LocType : public BSSAP_Element
{
public:
    BSSAP_LocType();
    ~BSSAP_LocType();

    void          SetLocInfo(ITS_OCTET info);
    ITS_OCTET     GetLocInfo();
    void          SetPosMethod(ITS_OCTET mthd);
    ITS_OCTET     GetPosMethod();
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.64 Location Estimate -------------- */
/*.interface:BSSAP_LocEstimate
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocEstimate
 *
 *  Purpose:
 *      This class implements the Location Estimate IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LocEstimate : public BSSAP_Element
{
public:
    BSSAP_LocEstimate();
    ~BSSAP_LocEstimate();

    void            SetLocEstimate(ITS_OCTET* buf, ITS_INT len);
    void            GetLocEstimate(ITS_OCTET* buf, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool haveLoc;
};

/* --------------- 3.2.2.65 Positioning Data -------------- */
/*.interface:BSSAP_PositionData
 *****************************************************************************
 *  Interface:
 *      BSSAP_PositionData
 *
 *  Purpose:
 *      This class implements the Return Positioning Data IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_PositionData : public BSSAP_Element
{
public:
    BSSAP_PositionData();
    ~BSSAP_PositionData();

    void        SetPosDataDiscr(ITS_OCTET discr);
    ITS_OCTET   GetPosDataDiscr();
    void        SetPosMthd_Usage(ITS_OCTET mthd, ITS_OCTET usage,
                                 ITS_INT index);
    void        GetPosMthd_Usage(ITS_OCTET &mthd, ITS_OCTET &usage,
                                 ITS_INT index);
    ITS_INT     GetPosMthd_UsageCount();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT   maxIndex;
};

/* --------------- 3.2.2.66 LCS Cause -------------- */
/*.interface:BSSAP_LCSCse
 *****************************************************************************
 *  Interface:
 *      BSSAP_LCSCse
 *
 *  Purpose:
 *      This class implements the Return LCS Casuse IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LCSCse : public BSSAP_Element
{
public:
    BSSAP_LCSCse();
    ~BSSAP_LCSCse();

    void          SetCauseValue(ITS_OCTET val);
    ITS_OCTET     GetCauseValue();
    void          SetDiagValue(ITS_OCTET val);
    ITS_OCTET     GetDiagValue();
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.67 LCS Client Type -------------- */
/*.interface:BSSAP_ClientType
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClientType
 *
 *  Purpose:
 *      This class implements the Return LCS Client Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClientType : public BSSAP_Element
{
public:
    BSSAP_ClientType();
    ~BSSAP_ClientType();

    void          SetClientSubtype(ITS_OCTET type);
    ITS_OCTET     GetClientSubtype();
    void          SetClientCategory(ITS_OCTET cat);
    ITS_OCTET     GetClientCategory();
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.68 APDU -------------- */
/*.interface:BSSAP_Apdu
 *****************************************************************************
 *  Interface:
 *      BSSAP_Apdu
 *
 *  Purpose:
 *      This class implements the APDU IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Apdu : public BSSAP_Element
{
public:
    BSSAP_Apdu();
    ~BSSAP_Apdu();

    void          SetProtocolID(ITS_OCTET id);
    ITS_OCTET     GetProtocolID();
    void          SetEmbededMsg(ITS_OCTET* buf, ITS_INT len);
    void          GetEmbededMsg(ITS_OCTET* buf, ITS_INT &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone(); 

private:
    ITS_USHORT      paramLen;
};

/* ----------------- 3.2.2.69 Network Element Identity --------------------*/
/*.interface:BSSAP_NetElementID
 *****************************************************************************
 *  Interface:
 *      BSSAP_NetElementID
 *
 *  Purpose:
 *      This class implements the Network Element Identity IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_NetElementID : public BSSAP_Element
{
public:
    BSSAP_NetElementID();
    ~BSSAP_NetElementID();

    void            SetIDDisc(ITS_OCTET type);
    ITS_OCTET       GetIDDisc();
    ITS_INT         SetNetElementID(BSSAP_NetID& neID);
    ITS_INT         GetNetElementID(BSSAP_NetID& neID);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.2.70 GPS Assistance Data --------------*/
/*.interface:BSSAP_GPSAssistData
 *****************************************************************************
 *  Interface:
 *      BSSAP_GPSAssistData
 *
 *  Purpose:
 *      This class implements the GPS Assistance Data IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_GPSAssistData : public BSSAP_Element
{
public:
    BSSAP_GPSAssistData();
    ~BSSAP_GPSAssistData();

    void            SetAlmanc(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetAlmanc();
    void            SetUTCModel(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetUTCModel();
    void            SetIonosphericModel(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetIonosphericModel();
    void            SetNavigationModel(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetNavigationModel();
    void            SetDGPSCorrections(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetDGPSCorrections();
    void            SetRefLocation(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetRefLocation();
    void            SetRefTime(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetRefTime();
    void            SetAcquitionAssistance(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetAcquitionAssistance();
    void            SetRealTimeIntegrity(ITS_BOOLEAN  data);
    ITS_BOOLEAN     GetRealTimeIntegrity();
    void            SetGPSWeek(ITS_USHORT data);
    ITS_USHORT      GetGPSWeek();
    void            SetGPSToe(ITS_OCTET data);
    ITS_OCTET       GetGPSToe();
    void            SetToeLimit(ITS_OCTET data);
    ITS_OCTET       GetToeLimit();
    void            SetNSAT(ITS_OCTET data);
    ITS_OCTET       GetNSAT();
    void            SetSatid_Iode(BSSAP_SATID_IODE id, const ITS_INT n);
    void            GetSatid_Iode(BSSAP_SATID_IODE& id, const ITS_INT n);
    ITS_INT         GetSatid_IodeCount();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT             maxIndex;
};

/* --------------- 3.2.2.71 Deciphering Keys -------------- */
/*.interface:BSSAP_DecipherKeys
 *****************************************************************************
 *  Interface:
 *      BSSAP_DecipherKeys
 *
 *  Purpose:
 *      This class implements the Deciphering Keys IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_DecipherKeys : public BSSAP_Element
{
public:
    BSSAP_DecipherKeys();
    ~BSSAP_DecipherKeys();

    void          SetKeyFlag(ITS_BOOLEAN flag);
    ITS_BOOLEAN   GetKeyFlag();
    void          SetCurrentValue(ITS_OCTET* buf);
    void          GetCurrentValue(ITS_OCTET* buf);
    void          SetNextValue(ITS_OCTET* buf);
    void          GetNextValue(ITS_OCTET* buf);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone(); 
};

/* --------------- 3.2.2.72 Return Error Request -------------- */
/*.interface:BSSAP_ReturnErrReq
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResAvaiL
 *
 *  Purpose:
 *      This class implements the Return Error Request IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ReturnErrReq : public BSSAP_Element
{
public:
    BSSAP_ReturnErrReq();
    ~BSSAP_ReturnErrReq();

    void          SetErrorType(ITS_OCTET val);
    ITS_OCTET     GetErrorType();
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 3.2.2.73 Return Error Cause -------------- */
/*.interface:BSSAP_ReturnErrCse
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResAvaiL
 *
 *  Purpose:
 *      This class implements the Return Error Cause IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ReturnErrCse : public BSSAP_Element
{
public:
    BSSAP_ReturnErrCse();
    ~BSSAP_ReturnErrCse();

    void          SetCauseValue(ITS_OCTET val);
    ITS_OCTET     GetCauseValue();
 
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 3.2.2.74 Segmentation ------------ */
/*.interface:BSSAP_Segment
 *****************************************************************************
 *  Interface:
 *      BSSAP_Segment
 *
 *  Purpose:
 *      This class implements the Segmentation IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Segment : public BSSAP_Element
{
public:
    BSSAP_Segment();
    ~BSSAP_Segment();

    void         SetSegmentNum(ITS_OCTET num);
    ITS_OCTET    GetSegmentNum();
    void         SetSegmentBit(ITS_OCTET bit);
    ITS_OCTET    GetSegmentBit();

    void         SetMessageID(ITS_USHORT mid); 
    ITS_USHORT   GetMessageID();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool          option;
};

/* ----------- 3.2.2.75 Service Handover ------------ */
/*.interface:BSSAP_ServHandover
 *****************************************************************************
 *  Interface:
 *      BSSAP_ServHandover
 *
 *  Purpose:
 *      This class implements the Service Handover IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ServHandover : public BSSAP_Element
{
public:
    BSSAP_ServHandover();
    ~BSSAP_ServHandover();

    void            SetServHandoverInfo(ITS_OCTET type);
    ITS_OCTET       GetServHandoverInfo();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --- 3.2.2.76 Soruce RNC to Target RNC Transparent Information (UMTS) --- */
/*.interface:BSSAP_SrcRNCtoTgtRNCInfoUMTS
 *****************************************************************************
 *  Interface:
 *      BSSAP_SrcRNCtoTgtRNCInfoUMTS
 *
 *  Purpose:
 *      This class implements the Soruce RNC to Target RNC Transparent 
 *      Information (UMTS) IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_SrcRNCtoTgtRNCInfoUMTS : public BSSAP_Element
{
public:
    BSSAP_SrcRNCtoTgtRNCInfoUMTS();
    ~BSSAP_SrcRNCtoTgtRNCInfoUMTS();

    void       SetSrcRNCtoTgtRNCInfoUMTS(ITS_OCTET *buf, ITS_INT len);
    void       GetSrcRNCtoTgtRNCInfoUMTS(ITS_OCTET *buf, ITS_INT &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool haveUmts;
};

/* --- 3.2.2.77 Soruce RNC to Target RNC Transparent Information (CDMA) --- */
/*.interface:BSSAP_SrcRNCtoTgtRNCInfoCDMA
 *****************************************************************************
 *  Interface:
 *      BSSAP_SrcRNCtoTgtRNCInfoCDMA
 *
 *  Purpose:
 *      This class implements the Soruce RNC to Target RNC Transparent 
 *      Information (CDMA) IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_SrcRNCtoTgtRNCInfoCDMA : public BSSAP_Element
{
public:
    BSSAP_SrcRNCtoTgtRNCInfoCDMA();
    ~BSSAP_SrcRNCtoTgtRNCInfoCDMA();

    void       SetSrcRNCtoTgtRNCInfoCDMA(ITS_OCTET *buf, ITS_INT len);
    void       GetSrcRNCtoTgtRNCInfoCDMA(ITS_OCTET *buf, ITS_INT &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool haveCdma;
};

/* --- 3.2.2.81 Inter System Information  --- */
/*.interface:BSSAP_InterSystemInformation
 *****************************************************************************
 *  Interface:
 *      BSSAP_InterSystemInformation
 *
 *  Purpose:
 *      This class implements the Inter System Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_InterSystemInformation : public BSSAP_Element
{
public:
    BSSAP_InterSystemInformation();
    ~BSSAP_InterSystemInformation();
                                                                                
    void       SetTransparentContainer(ITS_OCTET *buf, ITS_INT len);
    void       GetTransparentContainer(ITS_OCTET *buf, ITS_INT &len);
                                                                                
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*    Clone();

private:
    bool          haveInterSysInfo;
};

/////////////////////////////////////////////////////////////////////////////
//
// Field Element -- section 3.2.3
//
/////////////////////////////////////////////////////////////////////////////

/* ----------- 3.2.3.1 Extra Information ------------ */
/*.interface:BSSAP_ExtraInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_ExtraInfo
 *
 *  Purpose:
 *      This class implements the Extra Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ExtraInfo : public BSSAP_Element
{
public:
    BSSAP_ExtraInfo();
    ~BSSAP_ExtraInfo();

    void            SetPREC(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetPREC();
    void            SetLCS(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetLCS();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.3.2 Current Channel Type 2-------------- */
/*.interface:BSSAP_CrttChan2
 *****************************************************************************
 *  Interface:
 *      BSSAP_CrtChan2
 *
 *  Purpose:
 *      This class implements the Current Channel Type 2 IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CrtChan2 : public BSSAP_Element
{
public:
    BSSAP_CrtChan2();
    ~BSSAP_CrtChan2();

    void            SetChan(ITS_OCTET type);
    ITS_OCTET       GetChan();
    void            SetChanMode(ITS_OCTET type);
    ITS_OCTET       GetChanMode();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.3.3 Target Cell Radio Information-------------- */
/*.interface:BSSAP_TargetCellRadioInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_TargetCellRadioInfo
 *
 *  Purpose:
 *      This class implements the Target Cell Radio Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TargetCellRadioInfo : public BSSAP_Element
{
public:
    BSSAP_TargetCellRadioInfo();
    ~BSSAP_TargetCellRadioInfo();

    void            SetRXLEV_NCELL(ITS_OCTET type);
    ITS_OCTET       GetRXLEV_NCELL();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.3.4 GPRS Suspend Information -------------- */
/*.interface:BSSAP_GPRSSuspendInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_GPRSSuspendInfo
 *
 *  Purpose:
 *      This class implements the GPRS Suspend Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_GPRSSuspendInfo : public BSSAP_Element
{
public:
    BSSAP_GPRSSuspendInfo();
    ~BSSAP_GPRSSuspendInfo();

    // Set_ Get_ TLLI, RAI, and SRN seperately
    void            SetTLLI(ITS_OCTET* data, ITS_INT len);
    void            GetTLLI(ITS_OCTET* data, ITS_INT& len);
    void            SetRAI(ITS_OCTET* data, ITS_INT len);
    void            GetRAI(ITS_OCTET* data, ITS_INT& len);
    void            SetSRN(ITS_OCTET* data, ITS_INT len);
    void            GetSRN(ITS_OCTET* data, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT  tlliLen;
    ITS_INT  raiLen;
    ITS_INT  srnLen;
    ITS_INT  iePos;
    ITS_INT  rlenPos;
    ITS_INT  slenPos;
};

/* ------------- 3.2.3.5 Multirate Configuration Information-------------- */
/*.interface:BSSAP_MultirateConfigInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_MultirateConfigInfo
 *
 *  Purpose:
 *      This class implements the Multirate Configuration Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_MultirateConfigInfo : public BSSAP_Element
{
public:
    BSSAP_MultirateConfigInfo();
    ~BSSAP_MultirateConfigInfo();

    void            SetStartMode(ITS_OCTET type);
    ITS_OCTET       GetStartMode();
    void            SetICMI(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetICMI();
    void            SetMRVersion(ITS_OCTET type);
    ITS_OCTET       GetMRVersion();
    void            SetARMCodecMode1(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode1();
    void            SetARMCodecMode2(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode2();
    void            SetARMCodecMode3(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode3();
    void            SetARMCodecMode4(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode4();
    void            SetARMCodecMode5(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode5();
    void            SetARMCodecMode6(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode6();
    void            SetARMCodecMode7(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode7();
    void            SetARMCodecMode8(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetARMCodecMode8();
    void            SetThreshold1(ITS_OCTET type);
    ITS_OCTET       GetThreshold1();
    void            SetThreshold2(ITS_OCTET type);
    ITS_OCTET       GetThreshold2();
    void            SetThreshold3(ITS_OCTET type);
    ITS_OCTET       GetThreshold3();  
    void            SetHysteresis1(ITS_OCTET type);
    ITS_OCTET       GetHysteresis1(); 
    void            SetHysteresis2(ITS_OCTET type);
    ITS_OCTET       GetHysteresis2();
    void            SetHysteresis3(ITS_OCTET type);
    ITS_OCTET       GetHysteresis3();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.3.6 Dual Transfer Mode Information-------------- */
/*.interface:BSSAP_DualTransferModeInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_DualTransferModeInfo
 *
 *  Purpose:
 *      This class implements the Dual Transfer Mode Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_DualTransferModeInfo : public BSSAP_Element
{
public:
    BSSAP_DualTransferModeInfo();
    ~BSSAP_DualTransferModeInfo();

    void            SetDTMInd(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetDTMInd();
    void            SetSTOInd(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetSTOInd();
    void            SetEGPRSInd(ITS_BOOLEAN type);
    ITS_BOOLEAN     GetEGPRSInd();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.3.7 UE Capability Information-------------- */
/*.interface:BSSAP_UECapInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_UECapInfo
 *
 *  Purpose:
 *      This class implements the UE Capability Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UECapInfo : public BSSAP_Element
{
public:
    BSSAP_UECapInfo();
    ~BSSAP_UECapInfo();

    void            SetUECapInfo(ITS_OCTET* buf, ITS_INT len);
    void            GetUECapInfo(ITS_OCTET* buf, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool haveUeInfo;
};

/* ------------- 3.2.3.8 cdma2000 Capability Information-------------- */
/*.interface:BSSAP_cdma2000CapInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_cdma2000CapInfo
 *
 *  Purpose:
 *      This class implements the cdma2000 Capability Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_cdma2000CapInfo : public BSSAP_Element
{
public:
    BSSAP_cdma2000CapInfo();
    ~BSSAP_cdma2000CapInfo();

    void            SetcdmaCapInfo(ITS_OCTET* buf, ITS_INT len);
    void            GetcdmaCapInfo(ITS_OCTET* buf, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool haveInfo;
};

/* ------------- 3.2.3.9 Downlink Cell Load Information -------------- */
/*.interface:BSSAP_dlCellLoadInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_dlCellLoadInfo
 *
 *  Purpose:
 *      This class implements the Downlink Cell Load Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_dlCellLoadInfo : public BSSAP_Element
{
public:
    BSSAP_dlCellLoadInfo();
    ~BSSAP_dlCellLoadInfo();
                                                                                
    void            SetCellCapClassValue(ITS_OCTET value);
    ITS_OCTET       GetCellCapClassValue();
    void            SetLoadValue(ITS_OCTET value);
    ITS_OCTET       GetLoadValue();
    void            SetRTLoadValue(ITS_OCTET value);
    ITS_OCTET       GetRTLoadValue();
    void            SetNRTLoadInfo(ITS_OCTET value);
    ITS_OCTET       GetNRTLoadInfo();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*    Clone();
};

/* ----------- 3.2.3.9 UTRAN Pre-configuration Indication Set ----------- */
/*.interface:BSSAP_UTRANIndicationSet
 *****************************************************************************
 *  Interface:
 *      BSSAP_UTRANIndicationSet
 *
 *  Purpose:
 *      This class implements the UTRAN pre-configuration indication set IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UTRANIndicationSet : public BSSAP_Element
{
public:
    BSSAP_UTRANIndicationSet();
    ~BSSAP_UTRANIndicationSet();

    void  SetPre_Config_Id_Tag(ITS_OCTET id, ITS_OCTET tag, ITS_INT index);
    void  GetPre_Config_Id_Tag(ITS_OCTET &id, ITS_OCTET &tag, ITS_INT index);

protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    ITS_INT  maxIndex;
};

/* ------------- 3.2.3.10 Uplink Cell Load Information -------------- */
/*.interface:BSSAP_ulCellLoadInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_ulCellLoadInfo
 *
 *  Purpose:
 *      This class implements the Downlink Cell Load Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ulCellLoadInfo : public BSSAP_Element
{
public:
    BSSAP_ulCellLoadInfo();
    ~BSSAP_ulCellLoadInfo();
                                                                                
    void            SetCellCapClassValue(ITS_OCTET value);
    ITS_OCTET       GetCellCapClassValue();
    void            SetLoadValue(ITS_OCTET value);
    ITS_OCTET       GetLoadValue();
    void            SetRTLoadValue(ITS_OCTET value);
    ITS_OCTET       GetRTLoadValue();
    void            SetNRTLoadInfo(ITS_OCTET value);
    ITS_OCTET       GetNRTLoadInfo();
                                                                                
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*    Clone();
};

/* ------------- 3.2.3.10 UE Security Information -------------- */
/*.interface:BSSAP_UESecurityInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_UESecurityInfo
 *
 *  Purpose:
 *      This class implements the UE Security Information IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UESecurityInfo : public BSSAP_Element
{
public:
    BSSAP_UESecurityInfo();
    ~BSSAP_UESecurityInfo();

    void            SetUESecurityInfo(ITS_OCTET* buf, ITS_INT len);
    void            GetUESecurityInfo(ITS_OCTET* buf, ITS_INT& len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

private:
    bool haveSecInfo;
};

/////////////////////////////////////////////////////////////////////////////
//
// BSSAP CC related IE
//
/////////////////////////////////////////////////////////////////////////////

/* --------------- 10.5.4.15  Facility ------------ */
/*.interface:BSSAP_Facility
 *****************************************************************************
 *  Interface:
 *      BSSAP_Facility
 *
 *  Purpose:
 *      This class implements the Facility IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Facility : public BSSAP_Element
{
public:
    BSSAP_Facility();
    ~BSSAP_Facility();

    ITS_INT      SetFacilityData(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT      GetFacilityData(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 10.5.4.21  ProgressIndicator ------------ */
/*.interface:BSSAP_ProgressIndicator
 *****************************************************************************
 *  Interface:
 *      BSSAP_ProgressIndicator
 *
 *  Purpose:
 *      This class implements the ProgressIndicator IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ProgressIndicator : public BSSAP_Element
{
public:
    BSSAP_ProgressIndicator();
    ~BSSAP_ProgressIndicator();

    ITS_INT  SetCodingLocationDesc(ITS_OCTET coding, ITS_OCTET location,
                                   ITS_OCTET desc);
    ITS_INT  GetCodingLocationDesc(ITS_OCTET &coding, ITS_OCTET &location,
                                   ITS_OCTET &desc);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*________User To User Information 10.5.4.25_________*/
/*.interface:BSSAP_UserToUserInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the BSSAP_UserToUser IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UserToUser : public BSSAP_Element
{
public:
    BSSAP_UserToUser();
    ~BSSAP_UserToUser();

    ITS_INT      SetProtocolDiscriminator(ITS_OCTET disc);
    ITS_INT      GetProtocolDiscriminator(ITS_OCTET &disc);
    ITS_INT      SetUserInfo(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT      GetUserInfo(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*____________10.5.1.11 Priority Level ________*/
/*.interface:BSSAP_PriorityLevel
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the PriorityLevel IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_PriorityLevel : public BSSAP_Element
{
public:
    BSSAP_PriorityLevel();
    ~BSSAP_PriorityLevel();

    ITS_INT      SetPriority(ITS_OCTET prior);
    ITS_INT      GetPriority(ITS_OCTET &prior);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*__________________Repeat Indication 10.5.4.22____________*/
/*.interface:BSSAP_RepeatIndicator
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the RepeatIndicator IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RepeatIndicator : public BSSAP_Element
{
public:
    BSSAP_RepeatIndicator();
    ~BSSAP_RepeatIndicator();

    ITS_INT      SetRepeatType(ITS_OCTET type);
    ITS_INT      GetRepeatType(ITS_OCTET &type);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.19 More Data ---------- */
/*.interface:BSSAP_MoreData
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the MoreData IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_MoreData : public BSSAP_Element
{
public:
    BSSAP_MoreData();
    ~BSSAP_MoreData();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*____________10.5.3.6 Reject Cause ________*/
/*.interface:BSSAP_RejectCause
 *****************************************************************************
 *  Interface:
 *      BSSAP_RejectCause
 *
 *  Purpose:
 *      This class implements the Reject Cause IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RejectCause : public BSSAP_Element
{
public:
    BSSAP_RejectCause();
    ~BSSAP_RejectCause();
                                                                                
    ITS_INT  SetRejectCause(ITS_OCTET value);
    ITS_INT  GetRejectCause(ITS_OCTET &value);
                                                                                
protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*  Clone();
};

/*____________10.5.3.2.2 Authentication Failure Parameter ________*/
/*.interface:BSSAP_AuthFailParameter
 *****************************************************************************
 *  Interface:
 *      BSSAP_AuthFailParameter
 *
 *  Purpose:
 *      This class implements the Authentication Failure Parameter IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AuthFailParameter : public BSSAP_Element
{
public:
    BSSAP_AuthFailParameter();
    ~BSSAP_AuthFailParameter();
                                                                                
    ITS_INT  SetAuthFailParameter(ITS_OCTET *data, ITS_INT len);
    ITS_INT  GetAuthFailParameter(ITS_OCTET *data, ITS_INT &len);
                                                                                
protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*  Clone();
};

/*__________________Call Control Cause 10.5.4.11______________*/
/*.interface:BSSAP_CCCause
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the CCCause IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CCCause : public BSSAP_Element
{
public:
    BSSAP_CCCause();
    ~BSSAP_CCCause();

    ITS_INT SetCodingLocationCause(ITS_OCTET coding, ITS_OCTET location, 
                                   ITS_OCTET cause);
    ITS_INT GetCodingLocationCause(ITS_OCTET &coding, ITS_OCTET &location, 
                                   ITS_OCTET &cause);
    ITS_INT SetRecommendation(ITS_OCTET rec);
    ITS_INT GetRecommendation(ITS_OCTET &rec);
    ITS_INT IsRecommendationPresent();
    ITS_INT SetDiagnostics(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT GetDiagnostics(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*_________Reverse Call Setup Direction 10.5.4.22a__________*/
/*.interface:BSSAP_ReverseCallSetupDirection
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the ReverseCallSetupDirection IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ReverseCallSetupDirection : public BSSAP_Element
{
public:
    BSSAP_ReverseCallSetupDirection();
    ~BSSAP_ReverseCallSetupDirection();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*.interface:BSSAP_CLIRSuppression
 *****************************************************************************
 *  Interface:
 *      BSSAP_CLIRSuppression
 *
 *  Purpose:
 *      This class implements the CLIRSuppression IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CLIRSuppression : public BSSAP_Element
{
public:
    BSSAP_CLIRSuppression();
    ~BSSAP_CLIRSuppression();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*.interface:BSSAP_CLIRInvocation
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the CLIRInvocation IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CLIRInvocation : public BSSAP_Element
{
public:
    BSSAP_CLIRInvocation();
    ~BSSAP_CLIRInvocation();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*.interface:BSSAP_CongestionLevel
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the CongestionLevel IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CongestionLevel : public BSSAP_Element
{
public:
    BSSAP_CongestionLevel();
    ~BSSAP_CongestionLevel();

    ITS_INT      SetCongestionLevel(ITS_OCTET level);
    ITS_INT      GetCongestionLevel(ITS_OCTET &level);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*_______________Congestion Level 10.5.4.12__________*/
/*.interface:BSSAP_NotificationIndicator
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the NotificationIndicator IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_NotificationIndicator : public BSSAP_Element
{
public:
    BSSAP_NotificationIndicator();
    ~BSSAP_NotificationIndicator();

    ITS_INT      SetNotifyIndicator(ITS_OCTET value);
    ITS_INT      GetNotifyIndicator(ITS_OCTET &value);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*_____________________Connected Number 10.5.4.13________*/
/*.interface:BSSAP_ConnectedNumber
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the ConnectedNumbe IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ConnectedNumber : public BSSAP_Element
{
public:
    BSSAP_ConnectedNumber();
    ~BSSAP_ConnectedNumber();

    ITS_INT SetTypeAndNumPlan(ITS_OCTET type, ITS_OCTET numPlan);
    ITS_INT GetTypeAndNumPlan(ITS_OCTET &type, ITS_OCTET &numPlan);
    ITS_INT SetPresentationAndScreening(ITS_OCTET pres, ITS_OCTET screening);
    ITS_INT GetPresentationAndScreening(ITS_OCTET &pres, ITS_OCTET &screening);
    ITS_INT IsPresntationScreeningPresent();
    ITS_INT SetDigits(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT GetDigits(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*_____________________Connected Sub address 10.5.4.14_______*/
/*.interface:BSSAP_ConnectedSubAddress
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the ConnectedSubAddress IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ConnectedSubAddress : public BSSAP_Element
{
public:
    BSSAP_ConnectedSubAddress();
    ~BSSAP_ConnectedSubAddress();

    ITS_INT  SetSubAddressType(ITS_OCTET type, ITS_BOOLEAN isOdd);
    ITS_INT  GetSubAddressType(ITS_OCTET &type, ITS_BOOLEAN &isOdd);
    ITS_INT  IsSubAddressTypePresent();
    ITS_INT  SetSubAddressInfo(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetSubAddressInfo(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* --------------- 10.5.4.26  Alerting Pattern ------------ */
/*.interface:BSSAP_AlertingPattern
 *****************************************************************************
 *  Interface:
 *      BSSAP_AlertingPattern
 *
 *  Purpose:
 *      This class implements the Alerting Pattern IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AlertingPattern : public BSSAP_Element
{
public:
    BSSAP_AlertingPattern();
    ~BSSAP_AlertingPattern();
                                                                                
    ITS_INT  SetPattern(ITS_OCTET value);
    ITS_INT  GetPattern(ITS_OCTET &value);
                                                                                
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*    Clone();
};

/*_____________________Allowed Actions 10.5.4.27_______*/
/*.interface:BSSAP_AllowedAction
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserToUser
 *
 *  Purpose:
 *      This class implements the AllowedAction IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AllowedAction : public BSSAP_Element
{
public:
    BSSAP_AllowedAction();
    ~BSSAP_AllowedAction();

    ITS_INT  SetCCBS(ITS_OCTET ccbs);
    ITS_INT  GetCCBS(ITS_OCTET &ccbs);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*____________________ Stream Identifier  10.5.4.28_______*/
/*.interface:BSSAP_StreamIdentifier
 *****************************************************************************
 *  Interface:
 *      BSSAP_StreamIdentifier
 *
 *  Purpose:
 *      This class implements the Stream Identifier IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StreamIdentifier : public BSSAP_Element
{
public:
    BSSAP_StreamIdentifier();
    ~BSSAP_StreamIdentifier();
                                                                                
    ITS_INT  SetStrmIdentVal(ITS_OCTET value);
    ITS_INT  GetStrmIdentVal(ITS_OCTET &value);
                                                                                
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*    Clone();
};

/* --------------- 10.5.4.32  Supported Codecs ------------ */
/*.interface:BSSAP_SupportedCodecs
 *****************************************************************************
 *  Interface:
 *      BSSAP_SupportedCodecs
 *
 *  Purpose:
 *      This class implements the Supported Codecs IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_SupportedCodecs : public BSSAP_Element
{
public:
    BSSAP_SupportedCodecs();
    ~BSSAP_SupportedCodecs();
                                                                                
    ITS_INT  SetSystemID(ITS_OCTET *data, ITS_INT len);
    ITS_INT  GetSystemID(ITS_OCTET *data, ITS_INT &len);
                                                                                
protected:
    virtual ITS_INT  Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT  Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*    Clone();

private:
    bool  haveKey;
};

/*________Emergency Category/Service Category 10.5.4.33_______*/
/*.interface:BSSAP_EmergencyCategory
 *****************************************************************************
 *  Interface:
 *      BSSAP_EmergencyCategory
 *
 *  Purpose:
 *      This class implements the Emergency Category IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_EmergencyCategory : public BSSAP_Element
{
public:
    BSSAP_EmergencyCategory();
    ~BSSAP_EmergencyCategory();
                                                                                
    ITS_INT  SetEmergencyVal(ITS_OCTET value);
    ITS_INT  GetEmergencyVal(ITS_OCTET &value);
                                                                                
protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);
                                                                                
    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.16 High Level Compatibility ---------- */
/*.interface:BSSAP_HighLevelCompInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_HighLevelCompInfo
 *
 *  Purpose:
 *      This class implements the High Level Compatibility IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HighLevelCompInfo : public BSSAP_Element
{
public:
    BSSAP_HighLevelCompInfo();
    ~BSSAP_HighLevelCompInfo();

    ITS_INT  SetCodingPrsInterpretAndCharacterstics(ITS_OCTET cpi,
                                                    ITS_OCTET chrs);
    ITS_INT  GetCodingPrsInterpretAndCharacterstics(ITS_OCTET &cpi,
                                                    ITS_OCTET &chrs);
    ITS_INT  SetExtendedCharacterstics(ITS_OCTET xchrs);
    ITS_INT  GetExtendedCharacterstics(ITS_OCTET &xchrs);
    ITS_INT  IsCodingPrsInterpretAndCharactersticsPresent();
    ITS_INT  IsExtendedCharactersticsPresent();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.17 Low Level Compatibility ---------- */
/*.interface:BSSAP_LowLevelCompInfo
 *****************************************************************************
 *  Interface:
 *      BSSAP_LowLevelCompInfo
 *
 *  Purpose:
 *      This class implements the Low Level Compatibility IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LowLevelCompInfo : public BSSAP_Element
{
public:
    BSSAP_LowLevelCompInfo();
    ~BSSAP_LowLevelCompInfo();

    ITS_INT  SetLowLevelCompInfo(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetLowLevelCompInfo(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.24 SS Version ---------- */
/*.interface:BSSAP_SSVersion
 *****************************************************************************
 *  Interface:
 *      BSSAP_SSVersion
 *
 *  Purpose:
 *      This class implements the SS Version IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_SSVersion : public BSSAP_Element
{
public:
    BSSAP_SSVersion();
    ~BSSAP_SSVersion();

    ITS_INT  SetSSVersion(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetSSVersion(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.17 Setup Container ---------- */
/*.interface:BSSAP_SetupContainer
 *****************************************************************************
 *  Interface:
 *      BSSAP_SetupContainer
 *
 *  Purpose:
 *      This class implements the Setup Container IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_SetupContainer : public BSSAP_Element
{
public:
    BSSAP_SetupContainer();
    ~BSSAP_SetupContainer();

    ITS_INT  SetSetupData(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetSetupData(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.6 Call State ---------- */
/*.interface:BSSAP_CallState
 *****************************************************************************
 *  Interface:
 *      BSSAP_CallState
 *
 *  Purpose:
 *      This class implements the Call State IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CallState : public BSSAP_Element
{
public:
    BSSAP_CallState();
    ~BSSAP_CallState();

    ITS_INT  SetCodingAndState(ITS_OCTET coding, ITS_OCTET state);
    ITS_INT  GetCodingAndState(ITS_OCTET &coding, ITS_OCTET &state);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.23 Signal ---------- */
/*.interface:BSSAP_Signal
 *****************************************************************************
 *  Interface:
 *      BSSAP_Signal
 *
 *  Purpose:
 *      This class implements the Signal IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Signal : public BSSAP_Element
{
public:
    BSSAP_Signal();
    ~BSSAP_Signal();

    ITS_INT  SetSignal(ITS_OCTET signal);
    ITS_INT  GetSignal(ITS_OCTET &signal);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.17 Key pad facility ---------- */
/*.interface:BSSAP_KeyPadFacility
 *****************************************************************************
 *  Interface:
 *      BSSAP_KeyPadFacility
 *
 *  Purpose:
 *      This class implements the Keypad Facility IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_KeyPadFacility : public BSSAP_Element
{
public:
    BSSAP_KeyPadFacility();
    ~BSSAP_KeyPadFacility();

    ITS_INT  SetKeyValue(ITS_OCTET signal);
    ITS_INT  GetKeyValue(ITS_OCTET &signal);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.4 AuxState ---------- */
/*.interface:BSSAP_AuxState
 *****************************************************************************
 *  Interface:
 *      BSSAP_AuxState
 *
 *  Purpose:
 *      This class implements the Auxillary State IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AuxState : public BSSAP_Element
{
public:
    BSSAP_AuxState();
    ~BSSAP_AuxState();

    ITS_INT  SetAuxState(ITS_OCTET state);
    ITS_INT  GetAuxState(ITS_OCTET &state);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.5a CC Capabilities ---------- */
/*.interface:BSSAP_CCCapabilities
 *****************************************************************************
 *  Interface:
 *      BSSAP_CCCapabilities
 *
 *  Purpose:
 *      This class implements the CC Capabilities IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CCCapabilities : public BSSAP_Element
{
public:
    BSSAP_CCCapabilities();
    ~BSSAP_CCCapabilities();

    ITS_INT  SetDTMF();
    ITS_INT  SetPCP();
    ITS_INT  IsDTMFSet();
    ITS_INT  IsPCPSet();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.7 Called Party BCD Number ---------- */
/*.interface:BSSAP_CalledPartyBCDNumber
 *****************************************************************************
 *  Interface:
 *      BSSAP_CalledPartyBCDNumber
 *
 *  Purpose:
 *      This class implements the CalledPartyBCDNumber IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CalledPartyBCDNumber : public BSSAP_Element
{
public:
    BSSAP_CalledPartyBCDNumber();
    ~BSSAP_CalledPartyBCDNumber();

    ITS_INT  SetTypeAndNumPlan(ITS_OCTET type, ITS_OCTET numPlan);
    ITS_INT  GetTypeAndNumPlan(ITS_OCTET &type, ITS_OCTET &numPlan);
    ITS_INT  SetDigits(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetDigits(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.8 Called SubAddress ---------- */
/*.interface:BSSAP_CalledPartySubAddress
 *****************************************************************************
 *  Interface:
 *      BSSAP_CalledPartySubAddress
 *
 *  Purpose:
 *      This class implements the CalledPartySubAddress IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CalledPartySubAddress : public BSSAP_Element
{
public:
    BSSAP_CalledPartySubAddress();
    ~BSSAP_CalledPartySubAddress();

    ITS_INT  SetSubAddressType(ITS_OCTET type, ITS_BOOLEAN isOdd);
    ITS_INT  GetSubAddressType(ITS_OCTET &type, ITS_BOOLEAN &isOdd);
    ITS_INT  IsSubAddressTypePresent();
    ITS_INT  SetSubAddressInfo(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetSubAddressInfo(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.9 Calling Party BCD Number ---------- */
/*.interface:BSSAP_CallingPartyBCDNumber
 *****************************************************************************
 *  Interface:
 *      BSSAP_CallingPartyBCDNumber
 *
 *  Purpose:
 *      This class implements the CallingPartyBCDNumber IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CallingPartyBCDNumber : public BSSAP_Element
{
public:
    BSSAP_CallingPartyBCDNumber();
    ~BSSAP_CallingPartyBCDNumber();

    ITS_INT  SetTypeAndNumPlan(ITS_OCTET type, ITS_OCTET numPlan);
    ITS_INT  GetTypeAndNumPlan(ITS_OCTET &type, ITS_OCTET &numPlan);
    ITS_INT  SetPresentationAndScreening(ITS_OCTET pres, ITS_OCTET screening);
    ITS_INT  GetPresentationAndScreening(ITS_OCTET &pres, ITS_OCTET &screening);
    ITS_INT  IsPresntationScreeningPresent();
    ITS_INT  SetDigits(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetDigits(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.10 Calling SubAddress ---------- */
/*.interface:BSSAP_CallingPartySubAddress
 *****************************************************************************
 *  Interface:
 *      BSSAP_CallingPartySubAddress
 *
 *  Purpose:
 *      This class implements the CallingPartySubAddress IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CallingPartySubAddress : public BSSAP_Element
{
public:
    BSSAP_CallingPartySubAddress();
    ~BSSAP_CallingPartySubAddress();

    ITS_INT  SetSubAddressType(ITS_OCTET type, ITS_BOOLEAN isOdd);
    ITS_INT  GetSubAddressType(ITS_OCTET &type, ITS_BOOLEAN &isOdd);
    ITS_INT  IsSubAddressTypePresent();
    ITS_INT  SetSubAddressInfo(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetSubAddressInfo(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.21b Redirecting Number ---------- */
/*.interface:BSSAP_RedirectingPartyBCDNumber
 *****************************************************************************
 *  Interface:
 *      BSSAP_RedirectingPartyBCDNumber
 *
 *  Purpose:
 *      This class implements the RedirectingPartyBCDNumber IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RedirectingPartyBCDNumber : public BSSAP_Element
{
public:
    BSSAP_RedirectingPartyBCDNumber();
    ~BSSAP_RedirectingPartyBCDNumber();

    ITS_INT  SetTypeAndNumPlan(ITS_OCTET type, ITS_OCTET numPlan);
    ITS_INT  GetTypeAndNumPlan(ITS_OCTET &type, ITS_OCTET &numPlan);
    ITS_INT  SetPresentationAndScreening(ITS_OCTET pres, ITS_OCTET screening);
    ITS_INT  GetPresentationAndScreening(ITS_OCTET &pres, ITS_OCTET &screening);
    ITS_INT  IsPresntationScreeningPresent();
    ITS_INT  SetDigits(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetDigits(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.21c Redirecting SubAddress ---------- */
/*.interface:BSSAP_RedirectingPartySubAddress
 *****************************************************************************
 *  Interface:
 *      BSSAP_RedirectingPartySubAddress
 *
 *  Purpose:
 *      This class implements the RedirectingPartySubAddress IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RedirectingPartySubAddress : public BSSAP_Element
{
public:
    BSSAP_RedirectingPartySubAddress();
    ~BSSAP_RedirectingPartySubAddress();

    ITS_INT  SetSubAddressType(ITS_OCTET type, ITS_BOOLEAN isOdd);
    ITS_INT  GetSubAddressType(ITS_OCTET &type, ITS_BOOLEAN &isOdd);
    ITS_INT  IsSubAddressTypePresent();
    ITS_INT  SetSubAddressInfo(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetSubAddressInfo(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ---------- 10.5.4.5 Bearer Data ---------- */
/*.interface:BSSAP_BearerData
 *****************************************************************************
 *  Interface:
 *      BSSAP_BearerData
 *
 *  Purpose:
 *      This class implements the BearerData IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_BearerData : public BSSAP_Element
{
public:
    BSSAP_BearerData();
    ~BSSAP_BearerData();

    ITS_INT  SetInfoTransferCapabAndRadioChannelType(ITS_OCTET capab, 
                                                 ITS_OCTET rc);
    ITS_INT  GetInfoTransferCapabAndRadioChannelType(ITS_OCTET &capab, 
                                                 ITS_OCTET &rc);
    ITS_INT  SetCodingGsm();
    ITS_INT  SetCodingReserved();
    ITS_INT  SetTransferModeCkt();
    ITS_INT  SetTransferModePacket();
    ITS_INT  GetCoding(ITS_OCTET &coding);
    ITS_INT  GetTransferMode(ITS_OCTET &mode);
    ITS_INT  SetSpeechVersion(bool isExt, ITS_OCTET ver);
    ITS_INT  GetSpeechVersion(bool &isExt, ITS_OCTET &ver);
    ITS_INT  IsSpeechVersionPresent();
    ITS_INT  SetOptional(ITS_OCTET *data, ITS_OCTET len);
    ITS_INT  GetOptional(ITS_OCTET *data, ITS_OCTET &len);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/////////////////////////////////////////////////////////////////////////////
//
// BSSAP Messages
//
/////////////////////////////////////////////////////////////////////////////
/*.interface:BSSAP_AssignmentRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_AssignmentRequest
 *
 *  Purpose:
 *      This class implements the AssignmentRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AssignmentRequest : public BSSAP_Message
{
public:
    BSSAP_AssignmentRequest();
    ~BSSAP_AssignmentRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_AssignmentComplete
 *****************************************************************************
 *  Interface:
 *      BSSAP_AssignmentComplete
 *
 *  Purpose:
 *      This class implements the AssignmentComplete message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AssignmentComplete : public BSSAP_Message
{
public:
    BSSAP_AssignmentComplete();
    ~BSSAP_AssignmentComplete();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_AssignmentFailure
 *****************************************************************************
 *  Interface:
 *      BSSAP_AssignmentFailure
 *
 *  Purpose:
 *      This class implements the AssignmentFailure message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AssignmentFailure : public BSSAP_Message
{
public:
    BSSAP_AssignmentFailure();
    ~BSSAP_AssignmentFailure();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Block
 *****************************************************************************
 *  Interface:
 *      BSSAP_Block
 *
 *  Purpose:
 *      This class implements the Block message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Block : public BSSAP_Message
{
public:
    BSSAP_Block();
    ~BSSAP_Block();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_BlockAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_BlockAcknowledge
 *
 *  Purpose:
 *      This class implements the BlockingAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_BlockAcknowledge : public BSSAP_Message
{
public:
    BSSAP_BlockAcknowledge();
    ~BSSAP_BlockAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Unblock
 *****************************************************************************
 *  Interface:
 *      BSSAP_Unblock
 *
 *  Purpose:
 *      This class implements the Unblock message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Unblock : public BSSAP_Message
{
public:
    BSSAP_Unblock();
    ~BSSAP_Unblock();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UnblockAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_UnblockAcknowledge
 *
 *  Purpose:
 *      This class implements the UnblockingAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UnblockAcknowledge : public BSSAP_Message
{
public:
    BSSAP_UnblockAcknowledge();
    ~BSSAP_UnblockAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverRequest
 *
 *  Purpose:
 *      This class implements the HandoverRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverRequest : public BSSAP_Message
{
public:
    BSSAP_HandoverRequest();
    ~BSSAP_HandoverRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverRequired
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverRequired
 *
 *  Purpose:
 *      This class implements the HandoverRequired message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverRequired : public BSSAP_Message
{
public:
    BSSAP_HandoverRequired();
    ~BSSAP_HandoverRequired();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverRequestAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverRequestAcknowledge
 *
 *  Purpose:
 *      This class implements the HandoverRequestAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverRequestAcknowledge : public BSSAP_Message
{
public:
    BSSAP_HandoverRequestAcknowledge();
    ~BSSAP_HandoverRequestAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverCommand
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverRequestCommand
 *
 *  Purpose:
 *      This class implements the HandoverCommand message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverCommand : public BSSAP_Message
{
public:
    BSSAP_HandoverCommand();
    ~BSSAP_HandoverCommand();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverComplete
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverRequestComplete
 *
 *  Purpose:
 *      This class implements the HandoverComplete message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverComplete : public BSSAP_Message
{
public:
    BSSAP_HandoverComplete();
    ~BSSAP_HandoverComplete();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverSucceeded
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverRequestSucceeded
 *
 *  Purpose:
 *      This class implements the HandoverSuccedded message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverSucceeded : public BSSAP_Message
{
public:
    BSSAP_HandoverSucceeded();
    ~BSSAP_HandoverSucceeded();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverCandidateEnquire
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverCandidateEnquire
 *
 *  Purpose:
 *      This class implements the HandoverCandidateEnquire message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverCandidateEnquire : public BSSAP_Message
{
public:
    BSSAP_HandoverCandidateEnquire();
    ~BSSAP_HandoverCandidateEnquire();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverCandidateResponse
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverCandidateResponse
 *
 *  Purpose:
 *      This class implements the HandoverCandidateResponse message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverCandidateResponse : public BSSAP_Message
{
public:
    BSSAP_HandoverCandidateResponse();
    ~BSSAP_HandoverCandidateResponse();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverFailure
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverFailure
 *
 *  Purpose:
 *      This class implements the HandoverFailure message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverFailure : public BSSAP_Message
{
public:
    BSSAP_HandoverFailure();
    ~BSSAP_HandoverFailure();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ResourceRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResourceRequest
 *
 *  Purpose:
 *      This class implements the ResourceRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResourceRequest : public BSSAP_Message
{
public:
    BSSAP_ResourceRequest();
    ~BSSAP_ResourceRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ResourceIndication
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResourceIndication
 *
 *  Purpose:
 *      This class implements the ResourceIndication message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResourceIndication : public BSSAP_Message
{
public:
    BSSAP_ResourceIndication();
    ~BSSAP_ResourceIndication();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Paging
 *****************************************************************************
 *  Interface:
 *      BSSAP_Paging
 *
 *  Purpose:
 *      This class implements the Paging message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Paging : public BSSAP_Message
{
public:
    BSSAP_Paging();
    ~BSSAP_Paging();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_PagingResponse
 *****************************************************************************
 *  Interface:
 *      BSSAP_PagingResponse
 *
 *  Purpose:
 *      This class implements the PagingResponse message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_PagingResponse : public BSSAP_Message
{
public:
    BSSAP_PagingResponse();
    ~BSSAP_PagingResponse();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ClearRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClearRequest
 *
 *  Purpose:
 *      This class implements the ClearRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClearRequest : public BSSAP_Message
{
public:
    BSSAP_ClearRequest();
    ~BSSAP_ClearRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ClearCommand
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClearCommand
 *
 *  Purpose:
 *      This class implements the ClearCommand message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClearCommand : public BSSAP_Message
{
public:
    BSSAP_ClearCommand();
    ~BSSAP_ClearCommand();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ClearComplete
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClearComplete
 *
 *  Purpose:
 *      This class implements the ClearComplete message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClearComplete : public BSSAP_Message
{
public:
    BSSAP_ClearComplete();
    ~BSSAP_ClearComplete();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Reset
 *****************************************************************************
 *  Interface:
 *      BSSAP_Reset
 *
 *  Purpose:
 *      This class implements the Reset message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Reset : public BSSAP_Message
{
public:
    BSSAP_Reset();
    ~BSSAP_Reset();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ResetAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResetAcknowledge
 *
 *  Purpose:
 *      This class implements the ResetAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResetAcknowledge : public BSSAP_Message
{
public:
    BSSAP_ResetAcknowledge();
    ~BSSAP_ResetAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverPerformed
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverPerformed
 *
 *  Purpose:
 *      This class implements the HandoverPerformed message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverPerformed : public BSSAP_Message
{
public:
    BSSAP_HandoverPerformed();
    ~BSSAP_HandoverPerformed();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Overload
 *****************************************************************************
 *  Interface:
 *      BSSAP_Overload
 *
 *  Purpose:
 *      This class implements the Overload message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Overload : public BSSAP_Message
{
public:
    BSSAP_Overload();
    ~BSSAP_Overload();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_MSCInvokeTrace
 *****************************************************************************
 *  Interface:
 *      BSSAP_MSCInvokeTrace
 *
 *  Purpose:
 *      This class implements the MSCInvokeTrace message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_MSCInvokeTrace : public BSSAP_Message
{
public:
    BSSAP_MSCInvokeTrace();
    ~BSSAP_MSCInvokeTrace();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_BSSInvokeTrace
 *****************************************************************************
 *  Interface:
 *      BSSAP_BSSInvokeTrace
 *
 *  Purpose:
 *      This class implements the BSSInvokeTrace message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_BSSInvokeTrace : public BSSAP_Message
{
public:
    BSSAP_BSSInvokeTrace();
    ~BSSAP_BSSInvokeTrace();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ClassmarkUpdate
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClassmarkUpdate
 *
 *  Purpose:
 *      This class implements the ClassmarkUpdate message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClassmarkUpdate : public BSSAP_Message
{
public:
    BSSAP_ClassmarkUpdate();
    ~BSSAP_ClassmarkUpdate();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CipherModeCommand
 *****************************************************************************
 *  Interface:
 *      BSSAP_CipherModeCommand
 *
 *  Purpose:
 *      This class implements the CipherModeCommand message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CipherModeCommand : public BSSAP_Message
{
public:
    BSSAP_CipherModeCommand();
    ~BSSAP_CipherModeCommand();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CipherModeComplete
 *****************************************************************************
 *  Interface:
 *      BSSAP_CipherModeComplete
 *
 *  Purpose:
 *      This class implements the CipherModeComplete message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CipherModeComplete : public BSSAP_Message
{
public:
    BSSAP_CipherModeComplete();
    ~BSSAP_CipherModeComplete();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CompleteLayer3Information
 *****************************************************************************
 *  Interface:
 *      BSSAP_CompleteLayer3Information
 *
 *  Purpose:
 *      This class implements the CompleteLayer3Information message.
 *
 *  Usage:F
 *        None.
 *
 *****************************************************************************/
class BSSAP_CompleteLayer3Information : public BSSAP_Message
{
public:
    BSSAP_CompleteLayer3Information();
    ~BSSAP_CompleteLayer3Information();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_QueueingIndication
 *****************************************************************************
 *  Interface:
 *      BSSAP_QueueingIndication
 *
 *  Purpose:
 *      This class implements the QueueingIndication message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_QueueingIndication : public BSSAP_Message
{
public:
    BSSAP_QueueingIndication();
    ~BSSAP_QueueingIndication();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_SAPInReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_SAPInReject
 *
 *  Purpose:
 *      This class implements the SAPI"n"Reject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_SAPInReject : public BSSAP_Message
{
public:
    BSSAP_SAPInReject();
    ~BSSAP_SAPInReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverRequiredReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverRequiredReject
 *
 *  Purpose:
 *      This class implements the HandoverRequiredReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverRequiredReject : public BSSAP_Message
{
public:
    BSSAP_HandoverRequiredReject();
    ~BSSAP_HandoverRequiredReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ResetCircuit
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResetCircuit
 *
 *  Purpose:
 *      This class implements the ResetCircuit message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResetCircuit : public BSSAP_Message
{
public:
    BSSAP_ResetCircuit();
    ~BSSAP_ResetCircuit();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ResetCircuitAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_ResetCircuitAcknowledge
 *
 *  Purpose:
 *      This class implements the ResetCircuitAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ResetCircuitAcknowledge : public BSSAP_Message
{
public:
    BSSAP_ResetCircuitAcknowledge();
    ~BSSAP_ResetCircuitAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HandoverDetect
 *****************************************************************************
 *  Interface:
 *      BSSAP_HandoverDetect
 *
 *  Purpose:
 *      This class implements the HandoverDetect message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HandoverDetect : public BSSAP_Message
{
public:
    BSSAP_HandoverDetect();
    ~BSSAP_HandoverDetect();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CircuitGroupBlock
 *****************************************************************************
 *  Interface:
 *      BSSAP_CircuitGroupBlock
 *
 *  Purpose:
 *      This class implements the CircuitGroupBlock message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CircuitGroupBlock : public BSSAP_Message
{
public:
    BSSAP_CircuitGroupBlock();
    ~BSSAP_CircuitGroupBlock();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CircuitGroupBlockAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_CircuitGroupBlockAcknowledge
 *
 *  Purpose:
 *      This class implements the CircuitGroupBlockingAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CircuitGroupBlockAcknowledge : public BSSAP_Message
{
public:
    BSSAP_CircuitGroupBlockAcknowledge();
    ~BSSAP_CircuitGroupBlockAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CircuitGroupUnblock
 *****************************************************************************
 *  Interface:
 *      BSSAP_CircuitGroupUnblock
 *
 *  Purpose:
 *      This class implements the CircuitGroupUnblock message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CircuitGroupUnblock : public BSSAP_Message
{
public:
    BSSAP_CircuitGroupUnblock();
    ~BSSAP_CircuitGroupUnblock();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CircuitGroupUnblockAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_CircuitGroupUnblockAcknowledge
 *
 *  Purpose:
 *      This class implements the CircuitGroupUnblockingAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CircuitGroupUnblockAck : public BSSAP_Message
{
public:
    BSSAP_CircuitGroupUnblockAck();
    ~BSSAP_CircuitGroupUnblockAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Confusion
 *****************************************************************************
 *  Interface:
 *      BSSAP_Confusion
 *
 *  Purpose:
 *      This class implements the Confusion message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Confusion : public BSSAP_Message
{
public:
    BSSAP_Confusion();
    ~BSSAP_Confusion();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ClassmarkRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_ClassmarkRequest
 *
 *  Purpose:
 *      This class implements the ClassmarkRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ClassmarkRequest : public BSSAP_Message
{
public:
    BSSAP_ClassmarkRequest();
    ~BSSAP_ClassmarkRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UnequippedCircuit
 *****************************************************************************
 *  Interface:
 *      BSSAP_UnequippedCircuit
 *
 *  Purpose:
 *      This class implements the UnequippedCircuit message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UnequippedCircuit : public BSSAP_Message
{
public:
    BSSAP_UnequippedCircuit();
    ~BSSAP_UnequippedCircuit();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CipherModeReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_CipherModeReject
 *
 *  Purpose:
 *      This class implements the CipherModeReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CipherModeReject : public BSSAP_Message
{
public:
    BSSAP_CipherModeReject();
    ~BSSAP_CipherModeReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LoadIndication
 *****************************************************************************
 *  Interface:
 *      BSSAP_LoadIndication
 *
 *  Purpose:
 *      This class implements the LoadIndication message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LoadIndication : public BSSAP_Message
{
public:
    BSSAP_LoadIndication();
    ~BSSAP_LoadIndication();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_VGCSVBSSetup
 *****************************************************************************
 *  Interface:
 *      BSSAP_VGCSVBSSetup
 *
 *  Purpose:
 *      This class implements the VGCS/VBSSetup message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_VGCSVBSSetup : public BSSAP_Message
{
public:
    BSSAP_VGCSVBSSetup();
    ~BSSAP_VGCSVBSSetup();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_VGCSVBSSetupAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_VGCSVBSSetupAck
 *
 *  Purpose:
 *      This class implements the VGCS/VBSSetupAck message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_VGCSVBSSetupAck : public BSSAP_Message
{
public:
    BSSAP_VGCSVBSSetupAck();
    ~BSSAP_VGCSVBSSetupAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_VGCSVBSSetupRefuse
 *****************************************************************************
 *  Interface:
 *      BSSAP_VGCSVBSSetupRefuse
 *
 *  Purpose:
 *      This class implements the VGCS/VBSSetupRefuse message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_VGCSVBSSetupRefuse : public BSSAP_Message
{
public:
    BSSAP_VGCSVBSSetupRefuse();
    ~BSSAP_VGCSVBSSetupRefuse();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_VGCSVBSAssignmentRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_VGCSVBSAssignmentRequest
 *
 *  Purpose:
 *      This class implements the VGCS/VBSAssignmentRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_VGCSVBSAssignmentRequest : public BSSAP_Message
{
public:
    BSSAP_VGCSVBSAssignmentRequest();
    ~BSSAP_VGCSVBSAssignmentRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_VGCSVBSAssignmentResult
 *****************************************************************************
 *  Interface:
 *      BSSAP_VGCSVBSAssignmentResult
 *
 *  Purpose:
 *      This class implements the VGCS/VBSAssignmentResult message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_VGCSVBSAssignmentResult : public BSSAP_Message
{
public:
    BSSAP_VGCSVBSAssignmentResult();
    ~BSSAP_VGCSVBSAssignmentResult();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_VGCSVBSAssignmentFailure
 *****************************************************************************
 *  Interface:
 *      BSSAP_VGCSVBSAssignmentFailure
 *
 *  Purpose:
 *      This class implements the VGCS/VBSAssignmentFailure message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_VGCSVBSAssignmentFailure : public BSSAP_Message
{
public:
    BSSAP_VGCSVBSAssignmentFailure();
    ~BSSAP_VGCSVBSAssignmentFailure();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_VGCSVBSQueuingIndication
 *****************************************************************************
 *  Interface:
 *      BSSAP_VGCSVBSQueuingIndication
 *
 *  Purpose:
 *      This class implements the VGCS/VBSQueuingIndication message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_VGCSVBSQueuingIndication : public BSSAP_Message
{
public:
    BSSAP_VGCSVBSQueuingIndication();
    ~BSSAP_VGCSVBSQueuingIndication();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UplinkRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_UplinkRequest
 *
 *  Purpose:
 *      This class implements the UplinkRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UplinkRequest : public BSSAP_Message
{
public:
    BSSAP_UplinkRequest();
    ~BSSAP_UplinkRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UplinkRequestAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_UplinkRequestAcknowledge
 *
 *  Purpose:
 *      This class implements the UplinkRequestAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UplinkRequestAcknowledge : public BSSAP_Message
{
public:
    BSSAP_UplinkRequestAcknowledge();
    ~BSSAP_UplinkRequestAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UplinkRequestConfirmation
 *****************************************************************************
 *  Interface:
 *      BSSAP_UplinkRequestConfirmation
 *
 *  Purpose:
 *      This class implements the UplinkRequestConfirmation message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UplinkRequestConfirmation : public BSSAP_Message
{
public:
    BSSAP_UplinkRequestConfirmation();
    ~BSSAP_UplinkRequestConfirmation();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UplinkReleaseIndication
 *****************************************************************************
 *  Interface:
 *      BSSAP_UplinkReleaseIndication
 *
 *  Purpose:
 *      This class implements the UplinkReleaseIndication message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UplinkReleaseIndication : public BSSAP_Message
{
public:
    BSSAP_UplinkReleaseIndication();
    ~BSSAP_UplinkReleaseIndication();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UplinkReleaseCommand
 *****************************************************************************
 *  Interface:
 *      BSSAP_UplinkReleaseCommand
 *
 *  Purpose:
 *      This class implements the UplinkReleaseCommand message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UplinkReleaseCommand : public BSSAP_Message
{
public:
    BSSAP_UplinkReleaseCommand();
    ~BSSAP_UplinkReleaseCommand();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UplinkRejectCommand
 *****************************************************************************
 *  Interface:
 *      BSSAP_UplinkRejectCommand
 *
 *  Purpose:
 *      This class implements the UplinkRejectCommand message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UplinkRejectCommand : public BSSAP_Message
{
public:
    BSSAP_UplinkRejectCommand();
    ~BSSAP_UplinkRejectCommand();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UplinkSeizedCommand
 *****************************************************************************
 *  Interface:
 *      BSSAP_UplinkSeizedCommand
 *
 *  Purpose:
 *      This class implements the UplinkSeizedCommand message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UplinkSeizedCommand : public BSSAP_Message
{
public:
    BSSAP_UplinkSeizedCommand();
    ~BSSAP_UplinkSeizedCommand();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Suspend
 *****************************************************************************
 *  Interface:
 *      BSSAP_Suspend
 *
 *  Purpose:
 *      This class implements the Suspend message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Suspend : public BSSAP_Message
{
public:
    BSSAP_Suspend();
    ~BSSAP_Suspend();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Resume
 *****************************************************************************
 *  Interface:
 *      BSSAP_Resume
 *
 *  Purpose:
 *      This class implements the Resume message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Resume : public BSSAP_Message
{
public:
    BSSAP_Resume();
    ~BSSAP_Resume();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ChangeCircuit
 *****************************************************************************
 *  Interface:
 *      BSSAP_ChangeCircuit
 *
 *  Purpose:
 *      This class implements the ChangeCircuit message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ChangeCircuit : public BSSAP_Message
{
public:
    BSSAP_ChangeCircuit();
    ~BSSAP_ChangeCircuit();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ChangeCircuitAcknowledge
 *****************************************************************************
 *  Interface:
 *      BSSAP_ChangeCircuitAcknowledge
 *
 *  Purpose:
 *      This class implements the ChangeCircuitAcknowledge message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ChangeCircuitAcknowledge : public BSSAP_Message
{
public:
    BSSAP_ChangeCircuitAcknowledge();
    ~BSSAP_ChangeCircuitAcknowledge();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CommonID
 *****************************************************************************
 *  Interface:
 *      BSSAP_CommonID
 *
 *  Purpose:
 *      This class implements the CommonID message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CommonID : public BSSAP_Message
{
public:
    BSSAP_CommonID();
    ~BSSAP_CommonID();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LSAInformation
 *****************************************************************************
 *  Interface:
 *      BSSAP_LSAInformation
 *
 *  Purpose:
 *      This class implements the LSAInformation message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LSAInformation : public BSSAP_Message
{
public:
    BSSAP_LSAInformation();
    ~BSSAP_LSAInformation();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ConnectionOrientedInformation
 *****************************************************************************
 *  Interface:
 *      BSSAP_ConnectionOrientedInformation
 *
 *  Purpose:
 *      This class implements the Connection Oriented Information message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ConnectionOrientedInformation : public BSSAP_Message
{
public:
    BSSAP_ConnectionOrientedInformation();
    ~BSSAP_ConnectionOrientedInformation();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_PerformLocationRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_PerformLocationRequest
 *
 *  Purpose:
 *      This class implements the Perform Location Request message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_PerformLocationRequest : public BSSAP_Message
{
public:
    BSSAP_PerformLocationRequest();
    ~BSSAP_PerformLocationRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_PerformLocationResponse
 *****************************************************************************
 *  Interface:
 *      BSSAP_PerformLocationResponse
 *
 *  Purpose:
 *      This class implements the Perform Location Response message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_PerformLocationResponse : public BSSAP_Message
{
public:
    BSSAP_PerformLocationResponse();
    ~BSSAP_PerformLocationResponse();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_PerformLocationAbort
 *****************************************************************************
 *  Interface:
 *      BSSAP_PerformLocationAbort
 *
 *  Purpose:
 *      This class implements the Perform Location Abort message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_PerformLocationAbort : public BSSAP_Message
{
public:
    BSSAP_PerformLocationAbort();
    ~BSSAP_PerformLocationAbort();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ConnectionlessInformation
 *****************************************************************************
 *  Interface:
 *      BSSAP_ConnectionlessInformation
 *
 *  Purpose:
 *      This class implements the Connectionless Information message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ConnectionlessInformation : public BSSAP_Message
{
public:
    BSSAP_ConnectionlessInformation();
    ~BSSAP_ConnectionlessInformation();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/////////////////////////////////////////////////////////////////////////////
//
// BSSAP CC Related Messages
//
/////////////////////////////////////////////////////////////////////////////
/*.interface:BSSAP_Alerting
 *****************************************************************************
 *  Interface:
 *      BSSAP_Alerting
 *
 *  Purpose:
 *      This class implements the Alerting message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Alerting : public BSSAP_Message
{
public:
    BSSAP_Alerting();
    ~BSSAP_Alerting();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CallConfirmed
 *****************************************************************************
 *  Interface:
 *      BSSAP_CallConfirmed
 *
 *  Purpose:
 *      This class implements the Call Confirm message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CallConfirmed : public BSSAP_Message
{
public:
    BSSAP_CallConfirmed();
    ~BSSAP_CallConfirmed();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CallProceeding
 *****************************************************************************
 *  Interface:
 *      BSSAP_CallProceeding
 *
 *  Purpose:
 *      This class implements the Call Proceeding message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CallProceeding : public BSSAP_Message
{
public:
    BSSAP_CallProceeding();
    ~BSSAP_CallProceeding();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Connect
 *****************************************************************************
 *  Interface:
 *      BSSAP_Connect
 *
 *  Purpose:
 *      This class implements the Connect message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Connect : public BSSAP_Message
{
public:
    BSSAP_Connect();
    ~BSSAP_Connect();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ConnectAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_ConnectAck
 *
 *  Purpose:
 *      This class implements the Connect Ack message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ConnectAck : public BSSAP_Message
{
public:
    BSSAP_ConnectAck();
    ~BSSAP_ConnectAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_EmergencySetup
 *****************************************************************************
 *  Interface:
 *      BSSAP_EmergencySetup
 *
 *  Purpose:
 *      This class implements the Emergency Setup message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_EmergencySetup : public BSSAP_Message
{
public:
    BSSAP_EmergencySetup();
    ~BSSAP_EmergencySetup();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Progress
 *****************************************************************************
 *  Interface:
 *      BSSAP_Progress
 *
 *  Purpose:
 *      This class implements the Progress message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Progress : public BSSAP_Message
{
public:
    BSSAP_Progress();
    ~BSSAP_Progress();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CCEstablishment
 *****************************************************************************
 *  Interface:
 *      BSSAP_CCEstablishment
 *
 *  Purpose:
 *      This class implements the CC Establishment message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CCEstablishment : public BSSAP_Message
{
public:
    BSSAP_CCEstablishment();
    ~BSSAP_CCEstablishment();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CCEstablishmentConfirm
 *****************************************************************************
 *  Interface:
 *      BSSAP_CCEstablishmentConfirm
 *
 *  Purpose:
 *      This class implements the CC Establishment Confirm message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CCEstablishmentConfirm : public BSSAP_Message
{
public:
    BSSAP_CCEstablishmentConfirm();
    ~BSSAP_CCEstablishmentConfirm();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Recall
 *****************************************************************************
 *  Interface:
 *      BSSAP_Recall
 *
 *  Purpose:
 *      This class implements the Recall message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Recall : public BSSAP_Message
{
public:
    BSSAP_Recall();
    ~BSSAP_Recall();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_StartCC
 *****************************************************************************
 *  Interface:
 *      BSSAP_StartCC
 *
 *  Purpose:
 *      This class implements the StartCC message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StartCC : public BSSAP_Message
{
public:
    BSSAP_StartCC();
    ~BSSAP_StartCC();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Setup
 *****************************************************************************
 *  Interface:
 *      BSSAP_Setup
 *
 *  Purpose:
 *      This class implements the Setup message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Setup : public BSSAP_Message
{
public:
    BSSAP_Setup();
    ~BSSAP_Setup();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Modify
 *****************************************************************************
 *  Interface:
 *      BSSAP_Modify
 *
 *  Purpose:
 *      This class implements the Modify message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Modify : public BSSAP_Message
{
public:
    BSSAP_Modify();
    ~BSSAP_Modify();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ModifyComplete
 *****************************************************************************
 *  Interface:
 *      BSSAP_ModifyComplete
 *
 *  Purpose:
 *      This class implements the ModifyComplete message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ModifyComplete : public BSSAP_Message
{
public:
    BSSAP_ModifyComplete();
    ~BSSAP_ModifyComplete();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ModifyReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_ModifyReject
 *
 *  Purpose:
 *      This class implements the ModifyReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ModifyReject : public BSSAP_Message
{
public:
    BSSAP_ModifyReject();
    ~BSSAP_ModifyReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_UserInformation
 *****************************************************************************
 *  Interface:
 *      BSSAP_UserInformation
 *
 *  Purpose:
 *      This class implements the UserInformation message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_UserInformation : public BSSAP_Message
{
public:
    BSSAP_UserInformation();
    ~BSSAP_UserInformation();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Hold
 *****************************************************************************
 *  Interface:
 *      BSSAP_Hold
 *
 *  Purpose:
 *      This class implements the Hold message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Hold : public BSSAP_Message
{
public:
    BSSAP_Hold();
    ~BSSAP_Hold();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HoldAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_HoldAck
 *
 *  Purpose:
 *      This class implements the HoldAck message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HoldAck : public BSSAP_Message
{
public:
    BSSAP_HoldAck();
    ~BSSAP_HoldAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_HoldReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_HoldReject
 *
 *  Purpose:
 *      This class implements the HoldReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_HoldReject : public BSSAP_Message
{
public:
    BSSAP_HoldReject();
    ~BSSAP_HoldReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Retrieve
 *****************************************************************************
 *  Interface:
 *      BSSAP_Retrieve
 *
 *  Purpose:
 *      This class implements the Retrieve message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Retrieve : public BSSAP_Message
{
public:
    BSSAP_Retrieve();
    ~BSSAP_Retrieve();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_RetrieveAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_RetrieveAck
 *
 *  Purpose:
 *      This class implements the RetrieveAck message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RetrieveAck : public BSSAP_Message
{
public:
    BSSAP_RetrieveAck();
    ~BSSAP_RetrieveAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_RetrieveReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_RetrieveReject
 *
 *  Purpose:
 *      This class implements the RetrieveReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_RetrieveReject : public BSSAP_Message
{
public:
    BSSAP_RetrieveReject();
    ~BSSAP_RetrieveReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Disconnect
 *****************************************************************************
 *  Interface:
 *      BSSAP_Disconnect
 *
 *  Purpose:
 *      This class implements the Disconnect message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Disconnect : public BSSAP_Message
{
public:
    BSSAP_Disconnect();
    ~BSSAP_Disconnect();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Release
 *****************************************************************************
 *  Interface:
 *      BSSAP_Release
 *
 *  Purpose:
 *      This class implements the Release message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Release : public BSSAP_Message
{
public:
    BSSAP_Release();
    ~BSSAP_Release();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_ReleaseComplete
 *****************************************************************************
 *  Interface:
 *      BSSAP_ReleaseComplete
 *
 *  Purpose:
 *      This class implements the ReleaseComplete message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ReleaseComplete : public BSSAP_Message
{
public:
    BSSAP_ReleaseComplete();
    ~BSSAP_ReleaseComplete();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CongestionControl
 *****************************************************************************
 *  Interface:
 *      BSSAP_CongestionControl
 *
 *  Purpose:
 *      This class implements the CongestionControl message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CongestionControl : public BSSAP_Message
{
public:
    BSSAP_CongestionControl();
    ~BSSAP_CongestionControl();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:WBSSAP_Notify
 *****************************************************************************
 *  Interface:
 *      BSSAP_Notify
 *
 *  Purpose:
 *      This class implements the Notify message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Notify : public BSSAP_Message
{
public:
    BSSAP_Notify();
    ~BSSAP_Notify();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_StartDTMF
 *****************************************************************************
 *  Interface:
 *      BSSAP_StartDTMF
 *
 *  Purpose:
 *      This class implements the StartDTMF message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StartDTMF : public BSSAP_Message
{
public:
    BSSAP_StartDTMF();
    ~BSSAP_StartDTMF();


protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_StartDTMFAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_StartDTMFAck
 *
 *  Purpose:
 *      This class implements the StartDTMFAck message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StartDTMFAck : public BSSAP_Message
{
public:
    BSSAP_StartDTMFAck();
    ~BSSAP_StartDTMFAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_StartDTMFReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_StartDTMFReject
 *
 *  Purpose:
 *      This class implements the StartDTMFReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StartDTMFReject : public BSSAP_Message
{
public:
    BSSAP_StartDTMFReject();
    ~BSSAP_StartDTMFReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_StopDTMF
 *****************************************************************************
 *  Interface:
 *      BSSAP_StopDTMF
 *
 *  Purpose:
 *      This class implements the StopDTMF message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StopDTMF : public BSSAP_Message
{
public:
    BSSAP_StopDTMF();
    ~BSSAP_StopDTMF();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_StopDTMFAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_StopDTMFAck
 *
 *  Purpose:
 *      This class implements the StopDTMFAck message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StopDTMFAck : public BSSAP_Message
{
public:
    BSSAP_StopDTMFAck();
    ~BSSAP_StopDTMFAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Status
 *****************************************************************************
 *  Interface:
 *      BSSAP_Status
 *
 *  Purpose:
 *      This class implements the Status message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Status : public BSSAP_Message
{
public:
    BSSAP_Status();
    ~BSSAP_Status();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_StatusEnquiry
 *****************************************************************************
 *  Interface:
 *      BSSAP_StatusEnquiry
 *
 *  Purpose:
 *      This class implements the StatusEnquiry message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_StatusEnquiry : public BSSAP_Message
{
public:
    BSSAP_StatusEnquiry();
    ~BSSAP_StatusEnquiry();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*****************************************************************************
**
** START OF DTAP
**
******************************************************************************/


/*************************************** IE **********************************/

/* ------------- 10.5.3.7 Follow On Proceed  -------------- */
/*.interface:BSSAP_FollowOnProceed
 *****************************************************************************
 *  Interface:
 *      BSSAP_FollowOnProceed
 *
 *  Purpose:
 *      This class implements the FollowOnProceed IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_FollowOnProceed : public BSSAP_Element
{
public:
    BSSAP_FollowOnProceed();
    ~BSSAP_FollowOnProceed();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();

};

/* ------------- 10.5.3.10 CTS Permission  -------------- */
/*.interface:BSSAP_CTSPermission
 *****************************************************************************
 *  Interface:
 *      BSSAP_CTSPermission
 *
 *  Purpose:
 *      This class implements the CTSPermission IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CTSPermission : public BSSAP_Element
{
public:
    BSSAP_CTSPermission();
    ~BSSAP_CTSPermission();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 3.2.2.75 Location Updating Type ------------ */
/*.interface:BSSAP_ServHandover
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocationUpdatingType
 *
 *  Purpose:
 *      This class implements the Location Updating Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LocationUpdatingType : public BSSAP_Element
{
public:
    BSSAP_LocationUpdatingType();
    ~BSSAP_LocationUpdatingType();

    void            SetLocationUpdatingType(ITS_OCTET type);
    ITS_OCTET       GetLocationUpdatingType();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 3.2.2.75 Cyphering Key Sequence ------------ */
/*.interface:BSSAP_CypheringKeySequence
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocationUpdatingType
 *
 *  Purpose:
 *      This class implements the Location Updating Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CypheringKeySequence : public BSSAP_Element
{
public:
    BSSAP_CypheringKeySequence();
    ~BSSAP_CypheringKeySequence();

    void            SetCypheringKeySequence(ITS_OCTET type);
    ITS_OCTET       GetCypheringKeySequence();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 10.5.1.3 LocationAreaID ------------ */
/*.interface:BSSAP_LocationAreaID
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocationAreaID
 *
 *  Purpose:
 *      This class implements the Location Updating Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LocationAreaID : public BSSAP_Element
{
public:
    BSSAP_LocationAreaID();
    ~BSSAP_LocationAreaID();

    ITS_INT            SetLocationAreaID(ITS_OCTET* lai);
    ITS_INT            GetLocationAreaID(ITS_OCTET* lai);
    ITS_INT            SetLocationAreaIDMCC(ITS_OCTET* MCC);
    ITS_INT            GetLocationAreaIDMCC(ITS_OCTET* MCC);
    ITS_INT            SetLocationAreaIDMNC(ITS_OCTET* MNC);
    ITS_INT            GetLocationAreaIDMNC(ITS_OCTET* MNC);
    ITS_INT            SetLocationAreaIDLAC(ITS_OCTET* LAC);
    ITS_INT            GetLocationAreaIDLAC(ITS_OCTET* LAC);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 10.5.3.1 ParameterRand ------------ */
/*.interface:BSSAP_ParameterRand
 *****************************************************************************
 *  Interface:
 *      BSSAP_ParameterRand
 *
 *  Purpose:
 *      This class implements the Location Updating Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ParameterRand : public BSSAP_Element
{
public:
    BSSAP_ParameterRand();
    ~BSSAP_ParameterRand();

    ITS_INT            SetParameterRand(ITS_OCTET* PRAND);
    ITS_INT            GetParameterRand(ITS_OCTET* PRAND);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 10.5.3.2 ParameterSres ------------ */
/*.interface:BSSAP_ParameterSres
 *****************************************************************************
 *  Interface:
 *      BSSAP_ParameterSres
 *
 *  Purpose:
 *      This class implements the Location Updating Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_ParameterSres : public BSSAP_Element
{
public:
    BSSAP_ParameterSres();
    ~BSSAP_ParameterSres();

    ITS_INT            SetParameterSres(ITS_OCTET* PSRES);
    ITS_INT            GetParameterSres(ITS_OCTET* PSRES);

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 10.5.3.1 IdentityType ------------ */
/*.interface:BSSAP_IdentityType
 *****************************************************************************
 *  Interface:
 *      BSSAP_IdentityType
 *
 *  Purpose:
 *      This class implements the Identity Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_IdentityType : public BSSAP_Element
{
public:
    BSSAP_IdentityType();
    ~BSSAP_IdentityType();

    ITS_INT              SetIdentityType(ITS_OCTET IdType);
    ITS_OCTET            GetIdentityType();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 10.5.3.3 CMServiceType ------------ */
/*.interface:BSSAP_CMServiceType
 *****************************************************************************
 *  Interface:
 *      BSSAP_CMServiceType
 *
 *  Purpose:
 *      This class implements the Identity Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CMServiceType : public BSSAP_Element
{
public:
    BSSAP_CMServiceType();
    ~BSSAP_CMServiceType();

    ITS_INT              SetCMServiceType(ITS_OCTET CMSType);
    ITS_OCTET            GetCMServiceType();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 10.5.3.8 Time Zone------------ */
/*.interface:BSSAP_TimeZone
 *****************************************************************************
 *  Interface:
 *      BSSAP_TimeZone
 *
 *  Purpose:
 *      This class implements the TimeZone Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TimeZone : public BSSAP_Element
{
public:
    BSSAP_TimeZone();
    ~BSSAP_TimeZone();

    ITS_INT              SetTimeZone(ITS_OCTET TZone);
    ITS_OCTET            GetTimeZone();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/* ----------- 10.5.3.9 Time Zone Time------------ */
/*.interface:BSSAP_TimeZoneTime
 *****************************************************************************
 *  Interface:
 *      BSSAP_TimeZoneTime
 *
 *  Purpose:
 *      This class implements the TimeZoneTime Type IE.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TimeZoneTime : public BSSAP_Element
{
public:
    BSSAP_TimeZoneTime();
    ~BSSAP_TimeZoneTime();

    ITS_INT              SetTimeZoneYear(ITS_OCTET tzyear);
    ITS_OCTET            GetTimeZoneYear();
    ITS_INT              SetTimeZoneMonth(ITS_OCTET tzmonth);
    ITS_OCTET            GetTimeZoneMonth();
    ITS_INT              SetTimeZoneDay(ITS_OCTET tzday);
    ITS_OCTET            GetTimeZoneDay();
    ITS_INT              SetTimeZoneHour(ITS_OCTET tzhour);
    ITS_OCTET            GetTimeZoneHour();
    ITS_INT              SetTimeZoneMinute(ITS_OCTET tzminute);
    ITS_OCTET            GetTimeZoneMinute();
    ITS_INT              SetTimeZoneSecond(ITS_OCTET tzsecond);
    ITS_OCTET            GetTimeZoneSecond();
    ITS_INT              SetTimeZoneZone(ITS_OCTET tzzone);
    ITS_OCTET            GetTimeZoneZone();

protected:
    virtual ITS_INT     Encode(ITS_OCTET* buf, ITS_INT& len);
    virtual ITS_INT     Decode(ITS_OCTET* buf, ITS_INT& len);

    virtual BSSAP_Element*    Clone();
};

/*.interface:BSSAP_IMSIDetachIndication
 *****************************************************************************
 *  Interface:
 *      BSSAP_IMSIDetachIndication
 *
 *  Purpose:
 *      This class implements the IMSIDetachIndication message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_IMSIDetachIndication : public BSSAP_Message
{
public:
    BSSAP_IMSIDetachIndication();
    ~BSSAP_IMSIDetachIndication();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LocationUpdatingAccept
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocationUpdatingAccept
 *
 *  Purpose:
 *      This class implements the LocationUpdatingAccepet message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LocationUpdatingAccept : public BSSAP_Message
{
public:
    BSSAP_LocationUpdatingAccept();
    ~BSSAP_LocationUpdatingAccept();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LocationUpdatingReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocationUpdatingReject
 *
 *  Purpose:
 *      This class implements the LocationUpdatingReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LocationUpdatingReject : public BSSAP_Message
{
public:
    BSSAP_LocationUpdatingReject();
    ~BSSAP_LocationUpdatingReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LocationUpdatingRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_LocationUpdatingRequest
 *
 *  Purpose:
 *      This class implements the LocationUpdatingRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LocationUpdatingRequest : public BSSAP_Message
{
public:
    BSSAP_LocationUpdatingRequest();
    ~BSSAP_LocationUpdatingRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_AuthenticationReject 
 *****************************************************************************
 *  Interface:
 *      BSSAP_AuthenticationReject 
 *
 *  Purpose:
 *      This class implements the AuthenticationReject  message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AuthenticationReject  : public BSSAP_Message
{
public:
    BSSAP_AuthenticationReject ();
    ~BSSAP_AuthenticationReject ();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_AuthenticationRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_AuthenticationRequest
 *
 *  Purpose:
 *      This class implements the AuthenticationRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AuthenticationRequest : public BSSAP_Message
{
public:
    BSSAP_AuthenticationRequest();
    ~BSSAP_AuthenticationRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_AuthenticationResponse
 *****************************************************************************
 *  Interface:
 *      BSSAP_AuthenticationResponse
 *
 *  Purpose:
 *      This class implements the AuthenticationResponse message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AuthenticationResponse : public BSSAP_Message
{
public:
    BSSAP_AuthenticationResponse();
    ~BSSAP_AuthenticationResponse();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_AuthenticationFailure
 *****************************************************************************
 *  Interface:
 *      BSSAP_AuthenticationFailure
 *
 *  Purpose:
 *      This class implements the AuthenticationFailure message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_AuthenticationFailure : public BSSAP_Message
{
public:
    BSSAP_AuthenticationFailure();
    ~BSSAP_AuthenticationFailure();
                                                                                                                            
protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_IdentityRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_IdentityRequest
 *
 *  Purpose:
 *      This class implements the IdentityRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_IdentityRequest : public BSSAP_Message
{
public:
    BSSAP_IdentityRequest();
    ~BSSAP_IdentityRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_IdentityResponse
 *****************************************************************************
 *  Interface:
 *      BSSAP_IdentityResponse
 *
 *  Purpose:
 *      This class implements the IdentityResponse message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_IdentityResponse : public BSSAP_Message
{
public:
    BSSAP_IdentityResponse();
    ~BSSAP_IdentityResponse();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_TMSIReallocCommand
 *****************************************************************************
 *  Interface:
 *      BSSAP_TMSIReallocCommand
 *
 *  Purpose:
 *      This class implements the TMSIReallocCommand message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TMSIReallocCommand : public BSSAP_Message
{
public:
    BSSAP_TMSIReallocCommand();
    ~BSSAP_TMSIReallocCommand();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_TMSIReallocComplete
 *****************************************************************************
 *  Interface:
 *      BSSAP_TMSIReallocComplete
 *
 *  Purpose:
 *      This class implements the TMSIReallocComplete message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_TMSIReallocComplete : public BSSAP_Message
{
public:
    BSSAP_TMSIReallocComplete();
    ~BSSAP_TMSIReallocComplete();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CMReestablishmentReq
 *****************************************************************************
 *  Interface:
 *      BSSAP_CMReestablishmentReq
 *
 *  Purpose:
 *      This class implements the CMReestablishmentReq message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CMReestablishmentReq : public BSSAP_Message
{
public:
    BSSAP_CMReestablishmentReq();
    ~BSSAP_CMReestablishmentReq();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CMServiceAbort
 *****************************************************************************
 *  Interface:
 *      BSSAP_CMServiceAbort
 *
 *  Purpose:
 *      This class implements the CMServiceAbort message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CMServiceAbort : public BSSAP_Message
{
public:
    BSSAP_CMServiceAbort();
    ~BSSAP_CMServiceAbort();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CMServiceAccept
 *****************************************************************************
 *  Interface:
 *      BSSAP_CMServiceAccept
 *
 *  Purpose:
 *      This class implements the CMServiceAccept message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CMServiceAccept : public BSSAP_Message
{
public:
    BSSAP_CMServiceAccept();
    ~BSSAP_CMServiceAccept();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CMServiceReject
 *****************************************************************************
 *  Interface:
 *      BSSAP_CMServiceReject
 *
 *  Purpose:
 *      This class implements the CMServiceReject message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CMServiceReject : public BSSAP_Message
{
public:
    BSSAP_CMServiceReject();
    ~BSSAP_CMServiceReject();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_CMServiceRequest
 *****************************************************************************
 *  Interface:
 *      BSSAP_CMServiceRequest
 *
 *  Purpose:
 *      This class implements the CMServiceRequest message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_CMServiceRequest : public BSSAP_Message
{
public:
    BSSAP_CMServiceRequest();
    ~BSSAP_CMServiceRequest();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_Abort
 *****************************************************************************
 *  Interface:
 *      BSSAP_Abort
 *
 *  Purpose:
 *      This class implements the Abort message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_Abort : public BSSAP_Message
{
public:
    BSSAP_Abort();
    ~BSSAP_Abort();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_MMInformation
 *****************************************************************************
 *  Interface:
 *      BSSAP_MMInformation
 *
 *  Purpose:
 *      This class implements the MMInformation message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_MMInformation : public BSSAP_Message
{
public:
    BSSAP_MMInformation();
    ~BSSAP_MMInformation();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_MMNull
 *****************************************************************************
 *  Interface:
 *      BSSAP_MMNull
 *
 *  Purpose:
 *      This class implements the MMNull message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_MMNull : public BSSAP_Message
{
public:
    BSSAP_MMNull();
    ~BSSAP_MMNull();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_MMStatus
 *****************************************************************************
 *  Interface:
 *      BSSAP_MMStatus
 *
 *  Purpose:
 *      This class implements the MMStatus message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_MMStatus : public BSSAP_Message
{
public:
    BSSAP_MMStatus();
    ~BSSAP_MMStatus();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LCLSConnectControl
 *****************************************************************************
 *  Interface:
 *      BSSAP_LCLSConnectControl
 *
 *  Purpose:
 *      This class implements the LCLS Connect Control message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LCLSConnectControl : public BSSAP_Message
{
public:
    BSSAP_LCLSConnectControl();
    ~BSSAP_LCLSConnectControl();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LCLSConnectControlAck
 *****************************************************************************
 *  Interface:
 *      BSSAP_LCLSConnectControlAck
 *
 *  Purpose:
 *      This class implements the LCLS Connect Control Ack message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LCLSConnectControlAck : public BSSAP_Message
{
public:
    BSSAP_LCLSConnectControlAck();
    ~BSSAP_LCLSConnectControlAck();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};

/*.interface:BSSAP_LCLSNotification
 *****************************************************************************
 *  Interface:
 *      BSSAP_LCLSNotification
 *
 *  Purpose:
 *      This class implements the LCLS Notification message.
 *
 *  Usage:
 *        None.
 *
 *****************************************************************************/
class BSSAP_LCLSNotification : public BSSAP_Message
{
public:
    BSSAP_LCLSNotification();
    ~BSSAP_LCLSNotification();

protected:
    virtual ITS_BOOLEAN CheckForMandatoryParams();
};


#if defined(ITS_NAMESPACE)
}
#endif

#endif /* ITS_BSSAP_PP_H */
