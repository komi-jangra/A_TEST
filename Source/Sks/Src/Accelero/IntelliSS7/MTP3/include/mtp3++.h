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
 *  ID: $Id: mtp3++.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:46  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 02:02:57  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/08 23:36:45  randresol
 * LOG: Start Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/08/20 16:36:51  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/27 22:57:41  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.2  2001/06/26 17:27:19  mmiers
 * LOG: Link time resolution.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:10  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:01:54  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/06/13 20:02:10  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws by default.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:27  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.16  1999/08/30 15:53:26  mmiers
 * LOG:
 * LOG:
 * LOG: Essentially satisfies Hubert's objections to the OO model.
 * LOG:
 * LOG: Revision 1.15  1999/08/30 01:14:40  mmiers
 * LOG:
 * LOG:
 * LOG: Commit fixes
 * LOG:
 * LOG: Revision 1.14  1999/08/30 01:08:44  mmiers
 * LOG:
 * LOG:
 * LOG: Add overload for operator=
 * LOG:
 * LOG: Revision 1.13  1999/08/30 01:03:19  mmiers
 * LOG:
 * LOG:
 * LOG: Add point code class
 * LOG:
 * LOG: Revision 1.12  1999/07/29 15:52:26  mmiers
 * LOG:
 * LOG:
 * LOG: Document these interfaces.
 * LOG:
 * LOG: Revision 1.11  1999/06/30 21:02:55  mmiers
 * LOG:
 * LOG:
 * LOG: Portability fix
 * LOG:
 * LOG: Revision 1.10  1999/06/28 17:00:50  mmiers
 * LOG:
 * LOG:
 * LOG: Move the generic dispatchers out of here.
 * LOG:
 * LOG: Revision 1.9  1999/06/25 19:29:19  labuser
 * LOG:
 * LOG:
 * LOG: Fix a bunch of brain farts with generic thread dispatchers.
 * LOG: This needs revisiting, as the argument type will screw up
 * LOG: C++ code expecting a true thread function signature.
 * LOG:
 * LOG: Revision 1.8  1999/06/23 19:55:01  mmiers
 * LOG:
 * LOG:
 * LOG: Rework header files for dual protocol more intelligently.
 * LOG:
 * LOG: Revision 1.7  1999/02/12 23:40:22  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for simultaneous protocol families.
 * LOG:
 * LOG: Revision 1.6  1998/11/19 03:50:54  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 1.5  1998/11/11 15:57:43  mmiers
 * LOG: I had to tweak this for successful compilation, without any good
 * LOG: reason WHY.  This needs investigation.
 * LOG:
 * LOG: Revision 1.4  1998/10/27 21:53:03  mmiers
 * LOG: Oops, forgot SLS.
 * LOG:
 * LOG: Revision 1.3  1998/10/23 17:15:17  jrao
 * LOG: Fix HPUX compiler warning
 * LOG:
 * LOG: Revision 1.2  1998/10/15 23:15:26  mmiers
 * LOG: Add C++ for MTP3.  Add routing label to SCCP.
 * LOG:
 * LOG: Revision 1.1  1998/10/15 17:26:49  mmiers
 * LOG: Add C++ API for MTP3.
 * LOG:
 *
 *****************************************************************************/

#ifndef _MTP3_PP_H_
#define _MTP3_PP_H_

#include <its++.h>

#include <string.h>

#if defined(CCITT)
#include <itu/mtp3.h>

#define MTP3_PointCode  MTP3_PointCode_CCITT
#define MTP3_Header     MTP3_Header_CCITT
#define MTP3_Message    MTP3_Message_CCITT
#define MTP3_UserData   MTP3_UserData_CCITT
#define MTP3_Pause      MTP3_Pause_CCITT
#define MTP3_Resume     MTP3_Resume_CCITT
#define MTP3_Status     MTP3_Status_CCITT

#elif defined(ANSI)
#include <ansi/mtp3.h>

#define MTP3_PointCode  MTP3_PointCode_ANSI
#define MTP3_Header     MTP3_Header_ANSI
#define MTP3_Message    MTP3_Message_ANSI
#define MTP3_UserData   MTP3_UserData_ANSI
#define MTP3_Pause      MTP3_Pause_ANSI
#define MTP3_Resume     MTP3_Resume_ANSI
#define MTP3_Status     MTP3_Status_ANSI

#elif defined(PRC)
#include <china/mtp3.h>

#define MTP3_PointCode  MTP3_PointCode_PRC
#define MTP3_Header     MTP3_Header_PRC
#define MTP3_Message    MTP3_Message_PRC
#define MTP3_UserData   MTP3_UserData_PRC
#define MTP3_Pause      MTP3_Pause_PRC
#define MTP3_Resume     MTP3_Resume_PRC
#define MTP3_Status     MTP3_Status_PRC

#elif defined(TTC)
#include <japan/mtp3.h>

#define MTP3_PointCode  MTP3_PointCode_TTC
#define MTP3_Header     MTP3_Header_TTC
#define MTP3_Message    MTP3_Message_TTC
#define MTP3_UserData   MTP3_UserData_TTC
#define MTP3_Pause      MTP3_Pause_TTC
#define MTP3_Resume     MTP3_Resume_TTC
#define MTP3_Status     MTP3_Status_TTC

#else
#error "Protocol family not defined."
#endif

#include <its_exception.h>

#if defined(WIN32)
#pragma warning(disable : 4786)
#endif

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:MTP3PointCode
 *****************************************************************************
 *  Interface:
 *      MTP3_Header
 *
 *  Purpose:
 *      This interface provides the user access to "MTP3" like functions
 *      (or direct MTP3, as the case may be) to the user.
 *
 *  Usage:
 *
 *****************************************************************************/
class MTP3_PointCode
{
public:
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    This method constructs an MTP3 point code.
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_PointCode()
        : haveValue(false),
          haveNetwork(false),
          haveCluster(false),
          haveMember(false)
    {
        MTP3_PC_SET_VALUE(pointCode, 0);
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    This method constructs an MTP3 point code.
     *
     *  Input Parameters:
     *      pc - the value to set the point code to.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_PointCode(const ITS_UINT pc)
    {
        MTP3_PC_SET_VALUE(pointCode, pc);

        haveValue = true;
        haveNetwork = true;
        haveCluster = true;
        haveMember = true;
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    This method constructs an MTP3 point code.
     *
     *  Input Parameters:
     *      pc - the value to set the point code to.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_PointCode(const MTP3_POINT_CODE& pc)
    {
        pointCode = pc;

        haveValue = true;
        haveNetwork = true;
        haveCluster = true;
        haveMember = true;
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    This method destructs an MTP3 point code.
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    virtual ~MTP3_PointCode()
    {
    }

    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Set the network portion of a point code.
     *
     *  Input Parameters:
     *      network - the value of the network portion of the point code.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetNetwork(const ITS_OCTET network)
    {
        MTP3_PC_SET_NETWORK(pointCode, network);

        haveNetwork = true;

        if (haveCluster && haveMember)
        {
            haveValue = true;
        }
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Check to see if the the network portion of a point code is set.
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
     *	    true - the network portion has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasNetwork() const
    {
        return (haveNetwork);
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the network portion of a point code.
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
     *	    the network portion of the point code
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetNetwork() const
    {
        ITS_THROW_ASSERT(haveNetwork);

        return MTP3_PC_GET_NETWORK(pointCode);
    }

    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Set the cluster portion of a point code.
     *
     *  Input Parameters:
     *      cluster - the value of the cluster portion of the point code.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetCluster(const ITS_OCTET cluster)
    {
        MTP3_PC_SET_NETWORK(pointCode, cluster);

        haveCluster = true;

        if (haveNetwork && haveMember)
        {
            haveValue = true;
        }
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Check to see if the the cluster portion of a point code is set.
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
     *	    true - the cluster portion has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasCluster() const
    {
        return (haveCluster);
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the cluster portion of a point code.
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
     *	    the cluster portion of the point code
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetCluster() const
    {
        ITS_THROW_ASSERT(haveCluster);

        return MTP3_PC_GET_CLUSTER(pointCode);
    }

    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Set the member portion of a point code.
     *
     *  Input Parameters:
     *      member - the value of the member portion of the point code.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetMember(const ITS_OCTET member)
    {
        MTP3_PC_SET_NETWORK(pointCode, member);

        haveMember = true;

        if (haveNetwork && haveCluster)
        {
            haveValue = true;
        }
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Check to see if the the member portion of a point code is set.
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
     *	    true - the member portion has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasMember() const
    {
        return (haveMember);
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the member portion of a point code.
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
     *	    the member portion of the point code
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetMember() const
    {
        ITS_THROW_ASSERT(haveMember);

        return MTP3_PC_GET_MEMBER(pointCode);
    }

    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Check to see if the point code is set.
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
     *	    true - the value has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetValue(const ITS_UINT value)
    {
        MTP3_PC_SET_VALUE(pointCode, value);

        haveValue = true;
        haveNetwork = true;
        haveCluster = true;
        haveMember = true;
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Check to see if the point code is set.
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
     *	    true - the value has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetValue(const MTP3_POINT_CODE& value)
    {
        pointCode = value;

        haveValue = true;
        haveNetwork = true;
        haveCluster = true;
        haveMember = true;
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Check to see if the point code is set.
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
     *	    true - the value has been set.  false otherwise.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasValue() const
    {
        return (haveValue);
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the value of a point code.
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
     *	    the value of the point code.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT
    GetValue() const
    {
        ITS_THROW_ASSERT(haveValue);

        return MTP3_PC_GET_VALUE(pointCode);
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the value of a point code.
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
     *	    the value of the point code.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    GetValue(MTP3_POINT_CODE& pc) const
    {
        ITS_THROW_ASSERT(haveValue);

        pc = pointCode;
    }

    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Set the point code in entirety.
     *
     *  Input Parameters:
     *      value - the value to set the point code to
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_PointCode&
    operator=(const ITS_UINT value)
    {
        MTP3_PC_SET_VALUE(pointCode, value);

        haveValue = true;
        haveNetwork = true;
        haveCluster = true;
        haveMember = true;

        return (*this);
    }
    /*.implementation:public,MTP3_PointCode,inline
     ************************************************************************
     *  Purpose:
     *	    Set the point code in entirety.
     *
     *  Input Parameters:
     *      value - the value to set the point code to
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_PointCode&
    operator=(const MTP3_POINT_CODE& value)
    {
        pointCode = value;

        haveValue = true;
        haveNetwork = true;
        haveCluster = true;
        haveMember = true;

        return (*this);
    }

private:
    MTP3_POINT_CODE    pointCode;

    bool haveValue;
    bool haveNetwork;
    bool haveCluster;
    bool haveMember;
};

/*.interface:MTP3_Message
 *****************************************************************************
 *  Interface:
 *      MTP3_Header
 *
 *  Purpose:
 *      This interface provides the user access to "MTP3" like functions
 *      (or direct MTP3, as the case may be) to the user.
 *
 *  Usage:
 *
 *****************************************************************************/
class MTP3_Header
{
public:
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method constructs an MTP3 message header (routing label).
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_Header()
        : haveNIC(false),
          havePri(false),
          haveUP(false),
          haveOPC(false),
          haveDPC(false),
          haveSLS(false)
    {
        memset(&label, 0, sizeof(MTP3_HEADER));
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method constructs an MTP3 message header (routing label).
     *
     *  Input Parameters:
     *      hd - an MTP3 header to copy into this object
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_Header(const MTP3_HEADER hd)
        : label(hd),
          haveNIC(true),
          havePri(true),
          haveUP(true),
          haveOPC(true),
          haveDPC(true),
          haveSLS(true)
    {
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method destroys an MTP3 message header (routing label).
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    virtual ~MTP3_Header()
    {
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method allows the caller to set the contents of the
     *      routing label after the MTP3_Header has been created.
     *
     *  Input Parameters:
     *      hd - an MTP3 header to copy into this object
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetHeader(const MTP3_HEADER& hdr)
    {
        label = hdr;
        haveNIC = true;
        havePri = true;
        haveUP = true;
        haveOPC = true;
        haveDPC = true;
        haveSLS = true;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the routing label data from the object.
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
     *	    a reference to the current contents of the routing label.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    const MTP3_HEADER&
    GetHeader() const
    {
        return label;
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method is a predicate for testing if a value for the OPC
     *      has been assigned.
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
     *	    true - the OPC has been assigned
     *      false - otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasOPC() const
    {
        return haveOPC;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the OPC for the routing label.
     *
     *  Input Parameters:
     *      opc - the value to put in the label for OPC
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetOPC(const MTP3_PointCode opc)
    {
        haveOPC = true;

        MTP3_RL_SET_OPC_VALUE(label.label, opc.GetValue());
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the OPC for the routing label.
     *
     *  Input Parameters:
     *      opc - the value to put in the label for OPC
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetOPC(const ITS_UINT opc)
    {
        haveOPC = true;

        MTP3_RL_SET_OPC_VALUE(label.label, opc);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the OPC for the routing label.  The point code
     *      is specified as member/cluster/network.
     *
     *  Input Parameters:
     *      member - the value to put in the label for OPC member
     *      cluster - the value to put in the label for OPC member
     *      network - the value to put in the label for OPC member
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetOPC(const ITS_OCTET member,
           const ITS_OCTET cluster,
           const ITS_OCTET network)
    {
        haveOPC = true;

        MTP3_POINT_CODE pc;

        memset(&pc, 0, sizeof(MTP3_POINT_CODE));

        MTP3_PC_SET_MEMBER(pc, member);
        MTP3_PC_SET_CLUSTER(pc, cluster);
        MTP3_PC_SET_NETWORK(pc, network);

        MTP3_RL_SET_OPC(label.label, pc);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the OPC for the routing label.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      opc - the value to put in the label for OPC
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT
    GetOPC() const
    {
        return MTP3_RL_GET_OPC_VALUE(label.label);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the OPC for the routing label.  The point code
     *      is specified as member/cluster/network.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      member - the value put in the label for OPC member
     *      cluster - the value put in the label for OPC member
     *      network - the value put in the label for OPC member
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    GetOPC(ITS_OCTET& member, ITS_OCTET& cluster, ITS_OCTET& network) const
    {
        MTP3_POINT_CODE pc;

        MTP3_RL_GET_OPC(label.label, pc);

        member = MTP3_PC_GET_MEMBER(pc);
        cluster = MTP3_PC_GET_CLUSTER(pc);
        network = MTP3_PC_GET_NETWORK(pc);
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method is a predicate for testing if a value for the DPC
     *      has been assigned.
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
     *	    true - the DPC has been assigned
     *      false - otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasDPC() const
    {
        return haveDPC;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the DPC for the routing label.
     *
     *  Input Parameters:
     *      dpc - the value to put in the label for DPC
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetDPC(const MTP3_PointCode dpc)
    {
        haveDPC = true;
        MTP3_RL_SET_DPC_VALUE(label.label, dpc.GetValue());
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the DPC for the routing label.
     *
     *  Input Parameters:
     *      dpc - the value to put in the label for DPC
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetDPC(const ITS_UINT dpc)
    {
        haveDPC = true;

        MTP3_RL_SET_DPC_VALUE(label.label, dpc);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the DPC for the routing label.  The point code
     *      is specified as member/cluster/network.
     *
     *  Input Parameters:
     *      member - the value to put in the label for DPC member
     *      cluster - the value to put in the label for DPC member
     *      network - the value to put in the label for DPC member
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetDPC(const ITS_OCTET member,
           const ITS_OCTET cluster,
           const ITS_OCTET network)
    {
        haveDPC = true;

        MTP3_POINT_CODE pc;

        memset(&pc, 0, sizeof(MTP3_POINT_CODE));

        MTP3_PC_SET_MEMBER(pc, member);
        MTP3_PC_SET_CLUSTER(pc, cluster);
        MTP3_PC_SET_NETWORK(pc, network);

        MTP3_RL_SET_DPC(label.label, pc);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the DPC for the routing label.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      dpc - the value to put in the label for DPC
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT
    GetDPC() const
    {
        return MTP3_RL_GET_DPC_VALUE(label.label);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the DPC for the routing label.  The point code
     *      is specified as member/cluster/network.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      member - the value put in the label for DPC member
     *      cluster - the value put in the label for DPC member
     *      network - the value put in the label for DPC member
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    GetDPC(ITS_OCTET& member, ITS_OCTET& cluster, ITS_OCTET& network) const
    {
        MTP3_POINT_CODE pc;

        MTP3_RL_GET_DPC(label.label, pc);

        member = MTP3_PC_GET_MEMBER(pc);
        cluster = MTP3_PC_GET_CLUSTER(pc);
        network = MTP3_PC_GET_NETWORK(pc);
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the SIO for the routing label.
     *
     *  Input Parameters:
     *      sio - the SIO value to put in the label.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetSIO(const ITS_OCTET sio)
    {
        haveNIC = havePri = haveUP = true;

        MTP3_HDR_SET_SIO(label, sio);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the SIO of the routing label.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *	    None.
     *
     *  Return Value:
     *      the complete SIO value.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetSIO() const
    {
        return MTP3_HDR_GET_SIO(label);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method is a predicate for testing if a value for the NI
     *      has been assigned.
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
     *	    true - the NI has been assigned
     *      false - otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasNetworkIndicator() const
    {
        return haveNIC;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the NI in the SIO of the routing label.
     *
     *  Input Parameters:
     *      isNational - if the NI is national.  If false, the
     *          NI will be set to international.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetNetworkIndicator(const bool isNational)
    {
        haveNIC = true;
       // label.sio &= ~MTP3_NIC_MASK;
        if (isNational)
        {
            if(((label.sio & MTP3_NIC_MASK ) == MTP3_NIC_NATIONAL) || ((label.sio & MTP3_NIC_MASK) == MTP3_NIC_RESERVED))
             {
             }
            else
             {
               label.sio &= ~MTP3_NIC_MASK;
               label.sio|= MTP3_NIC_NATIONAL;
             }
        }
       else
        {
            if(((label.sio & MTP3_NIC_MASK ) == MTP3_NIC_INTERNATIONAL) || ((label.sio & MTP3_NIC_MASK )== MTP3_NIC_SPARE))
             {
             }
            else
             {
               label.sio &= ~MTP3_NIC_MASK;
               label.sio|= MTP3_NIC_INTERNATIONAL;
             }


       }
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the UP from the SIO of the routing label.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *	    None.
     *
     *  Return Value:
     *      the NI value set.  Values are defined in mtp3.h
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetNetworkIndicator() const
    {
        return (label.sio & ~MTP3_NIC_MASK);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method is a predicate for testing if a value for the PRI
     *      has been assigned.
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
     *	    true - the PRI has been assigned
     *      false - otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasPriority() const
    {
        return havePri;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the PRI in the SIO of the routing label.
     *
     *  Input Parameters:
     *      priority - a value from 0 to 3.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetPriority(const ITS_OCTET priority)
    {
        havePri = true;
        label.sio &= ~MTP3_MPC_MASK;
        label.sio |= (priority << 4) & MTP3_MPC_MASK;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the PRI from the SIO of the routing label.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *	    None.
     *
     *  Return Value:
     *      the PRI value set.  Range is 0 to 3.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetPriority() const
    {
        return ((label.sio & MTP3_MPC_MASK) >> 4);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method is a predicate for testing if a value for the UP
     *      has been assigned.
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
     *	    true - the UP has been assigned
     *      false - otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasUserPart() const
    {
        return haveUP;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the UP in the SIO of the routing label.
     *
     *  Input Parameters:
     *      part - a value from 0 to 15.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetUserPart(const ITS_OCTET part)
    {
        haveUP = true;
        label.sio &= ~MTP3_SIO_UP_MASK;
        label.sio |= part & MTP3_SIO_UP_MASK;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the UP from the SIO of the routing label.
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *	    None.
     *
     *  Return Value:
     *      the UP value set.  Range is 0 to 15.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetUserPart() const
    {
        return (label.sio & MTP3_SIO_UP_MASK);
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method is a predicate for testing if a value for the SLS
     *      has been assigned.
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
     *	    true - the SLS has been assigned
     *      false - otherwise
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    bool
    HasSLS() const
    {
        return haveSLS;
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method sets the SLS of the routing label.
     *
     *  Input Parameters:
     *      sls - the sls value to use.  Range depends on protocol family
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    SetSLS(const ITS_OCTET sls)
    {
        haveSLS = true;
        MTP3_RL_SET_SLS(label.label, sls);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    This method gets the SLS of the routing label.
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
     *      the sls value set.  Range depends on protocol family
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetSLS() const
    {
        return MTP3_RL_GET_SLS(label.label);
    }

protected:
    MTP3_HEADER label;

    bool haveNIC;
    bool havePri;
    bool haveUP;
    bool haveOPC;
    bool haveDPC;
    bool haveSLS;
};

/*.interface:MTP3_Message
 *****************************************************************************
 *  Interface:
 *      MTP3_Message
 *
 *  Purpose:
 *      This interface provides the user access to "MTP3" like functions
 *      (or direct MTP3, as the case may be) to the user.
 *
 *  Usage:
 *
 *****************************************************************************/
class MTP3_Message : public MTP3_Header
{
public:
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Construct an MTP3 message.
     *
     *  Input Parameters:
     *      type - one of MTP3_PAUSE, MTP3_RESUME, MTP3_USER_DATA, or
     *          MTP3_STATUS
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_Message(const ITS_OCTET _msgType)
        : payloadSize(0),
          msgType(_msgType)
    {
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Destroy an MTP3 message
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    virtual
    ~MTP3_Message()
    {
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Set the data portion of an MTP3 message
     *
     *  Input Parameters:
     *      data - the octet vector to copy in
     *      len - the size of the vector
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      ITS_SUCCESS - value successfully set.  Any other return
     *          code indicates an IntelliSS7 processing error.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    int
    SetPayload(const ITS_OCTET* const data, const int len)
    {
        if (len > MTP3_MAX_SIF_LENGTH)
        {
            return (ITS_EOVERFLOW);
        }

        payloadSize = len;

        memcpy(payload, data, len);

        return (ITS_SUCCESS);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Set the data portion of an MTP3 message
     *
     *  Input Parameters:
     *      data - the octet vector to copy in
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      None.
     *
     *  Return Value:
     *      ITS_SUCCESS - value successfully set.  Any other return
     *          code indicates an IntelliSS7 processing error.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    int
    SetPayload(const ITS_ByteArray& data)
    {
        if (data.size() > MTP3_MAX_SIF_LENGTH)
        {
            return (ITS_EOVERFLOW);
        }

        payloadSize = data.size();

        memcpy(payload, &data[0], data.size());

        return (ITS_SUCCESS);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the data from an MTP3 message
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      data - the vector to copy the payload into
     *      len - the size of the vector
     *
     *  Return Value:
     *		None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    int
    GetPayload(ITS_OCTET* data, int& len) const
    {
        len = payloadSize;

        memcpy(data, payload, len);

        return (ITS_SUCCESS);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the data from an MTP3 message
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      data - the vector to copy the payload into
     *      len - the size of the vector
     *
     *  Return Value:
     *		None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    int
    GetPayload(ITS_ByteArray& data) const
    {
        data.assign(payload, payload + payloadSize);

        return (ITS_SUCCESS);
    }

    /*.implementation:public,inline,MTP3_Message
     ************************************************************************
     *  Purpose:
     *	Encode an MTP3 message into an its::Event
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *      event - the event to encode this object into
     *
     *  Return Value:
     *      ITS_SUCCESS - the event successfully encoded.  Any other
     *          return value indicates an IntelliSS7 processing error.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    int
    Encode(its::Event& event)
    {
        ITS_THROW_ASSERT(haveNIC && havePri && haveUP &&
                         haveDPC && haveOPC && haveSLS);

        return MTP3_Encode(&event.GetEvent(), msgType, &label,
                           payload, payloadSize);
    }

    static int Decode(its::Event& event, MTP3_Message** msg);

protected:
    ITS_OCTET   payload[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT  payloadSize;

private:
    MTP3_Message(); // must initialize message type

    ITS_OCTET   msgType;
};

/*.interface:MTP3_UserData
 *****************************************************************************
 *  Interface:
 *      MTP3_UserData
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      UserData messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
class MTP3_UserData : public MTP3_Message
{
public:
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Construct an MTP3_USER_DATA message.
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_UserData()
        : MTP3_Message(MTP3_MSG_USER_DATA)
    {
    }
};

/*.interface:MTP3_Pause
 *****************************************************************************
 *  Interface:
 *      MTP3_Pause
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      Pause messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
class MTP3_Pause : public MTP3_Message
{
public:
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Construct an MTP3_PAUSE message.
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_Pause()
        : MTP3_Message(MTP3_MSG_PAUSE)
    {
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the affected PC value from the pause message
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
     *	    the point code affected
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT
    GetAffectedPC() const
    {
        ITS_THROW_ASSERT(payloadSize == sizeof(MTP3_PAUSE_RESUME));

        MTP3_PAUSE_RESUME *pr = (MTP3_PAUSE_RESUME *)payload;

        return (MTP3_PC_GET_VALUE(pr->affected));
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the affected PC value from the pause message.  The
     *      format is retrieved as member/cluster/network
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *	    member - the member portion of the point code affected
     *	    cluster - the cluster portion of the point code affected
     *	    network - the network portion of the point code affected
     *
     *  Return Value:
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    GetAffectedPC(ITS_OCTET& member,
                  ITS_OCTET& cluster,
                  ITS_OCTET& network) const
    {
        ITS_THROW_ASSERT(payloadSize == sizeof(MTP3_PAUSE_RESUME));

        MTP3_PAUSE_RESUME *pr = (MTP3_PAUSE_RESUME *)payload;

        member = MTP3_PC_GET_MEMBER(pr->affected);
        cluster = MTP3_PC_GET_CLUSTER(pr->affected);
        network = MTP3_PC_GET_NETWORK(pr->affected);
    }
};

/*.interface:MTP3_Resume
 *****************************************************************************
 *  Interface:
 *      MTP3_Resume
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      Resume messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
class MTP3_Resume : public MTP3_Message
{
public:
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Construct an MTP3_RESUME message.
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_Resume()
        : MTP3_Message(MTP3_MSG_RESUME)
    {
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the affected PC value from the resume message
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
     *	    the point code affected
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT
    GetAffectedPC() const
    {
        ITS_THROW_ASSERT(payloadSize == sizeof(MTP3_PAUSE_RESUME));

        MTP3_PAUSE_RESUME *pr = (MTP3_PAUSE_RESUME *)payload;

        return (MTP3_PC_GET_VALUE(pr->affected));
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the affected PC value from the resume message.  The
     *      format is retrieved as member/cluster/network
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *	    member - the member portion of the point code affected
     *	    cluster - the cluster portion of the point code affected
     *	    network - the network portion of the point code affected
     *
     *  Return Value:
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    GetAffectedPC(ITS_OCTET& member,
                  ITS_OCTET& cluster,
                  ITS_OCTET& network) const
    {
        ITS_THROW_ASSERT(payloadSize == sizeof(MTP3_PAUSE_RESUME));

        MTP3_PAUSE_RESUME *pr = (MTP3_PAUSE_RESUME *)payload;

        member = MTP3_PC_GET_MEMBER(pr->affected);
        cluster = MTP3_PC_GET_CLUSTER(pr->affected);
        network = MTP3_PC_GET_NETWORK(pr->affected);
    }
};

/*.interface:MTP3_Status
 *****************************************************************************
 *  Interface:
 *      MTP3_Status
 *
 *  Purpose:
 *      This object contains the information necessary to encode/decode
 *      Status messages.
 *
 *  Usage:
 *      None.
 *
 *****************************************************************************/
class MTP3_Status : public MTP3_Message
{
public:
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Construct an MTP3_RESUME message.
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
     *	    None.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    MTP3_Status()
        : MTP3_Message(MTP3_MSG_STATUS)
    {
    }

    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the affected PC value from the status message
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
     *	    the point code affected
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_UINT
    GetAffectedPC() const
    {
        ITS_THROW_ASSERT(payloadSize == sizeof(MTP3_STATUS));

        MTP3_STATUS *st = (MTP3_STATUS *)payload;

        return (MTP3_PC_GET_VALUE(st->affected));
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the affected PC value from the status message.  The
     *      format is retrieved as member/cluster/network
     *
     *  Input Parameters:
     *      None.
     *
     *  Input/Output Parameters:
     *      None.
     *
     *  Output Parameters:
     *	    member - the member portion of the point code affected
     *	    cluster - the cluster portion of the point code affected
     *	    network - the network portion of the point code affected
     *
     *  Return Value:
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    void
    GetAffectedPC(ITS_OCTET& member,
                  ITS_OCTET& cluster,
                  ITS_OCTET& network) const
    {
        ITS_THROW_ASSERT(payloadSize == sizeof(MTP3_STATUS));

        MTP3_STATUS *st = (MTP3_STATUS *)payload;

        member = MTP3_PC_GET_MEMBER(st->affected);
        cluster = MTP3_PC_GET_CLUSTER(st->affected);
        network = MTP3_PC_GET_NETWORK(st->affected);
    }
    /*.implementation:public,MTP3_Message,inline
     ************************************************************************
     *  Purpose:
     *	    Retrieve the status (congestion level) from the status message
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
     *	    the status value
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_OCTET
    GetStatus() const
    {
        ITS_THROW_ASSERT(payloadSize == sizeof(MTP3_STATUS));

        MTP3_STATUS *st = (MTP3_STATUS *)payload;

        return st->cause;
    }
};

/*.implementation:static,inline,MTP3_Message
 ************************************************************************
 *  Purpose:
 *	Decode an its::Event and create an MTP3_Message with the data.
 *
 *  Input Parameters:
 *      event - the event to encode this object into
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      msg - contains a pointer to an allocated MTP3_Message.
 *
 *  Return Value:
 *      ITS_SUCCESS - the event successfully decoded.  Any other
 *          return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
inline int
MTP3_Message::Decode(its::Event& event, MTP3_Message** msg)
{
    ITS_OCTET type;
    ITS_OCTET load[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT loadSize = 0;
    MTP3_HEADER lab;
    int ret;

    *msg = NULL;

    if (event.GetLength() > MTP3_MAX_SIF_LENGTH)
    {
        return (ITS_EOVERFLOW);
    }

    if ((ret = MTP3_Decode(&event.GetEvent(), &type, &lab,
                           load, &loadSize)) != ITS_SUCCESS)
    {
        return (ret);
    }

    switch (type)
    {
    case MTP3_MSG_USER_DATA:
        *msg = new MTP3_UserData;
        break;

    case MTP3_MSG_PAUSE:
        *msg = new MTP3_Pause;
        break;

    case MTP3_MSG_RESUME:
        *msg = new MTP3_Resume;
        break;

    case MTP3_MSG_STATUS:
        *msg = new MTP3_Status;
        break;

    default:
        return (ITS_ENOMSG);
    }

    (*msg)->label = lab;
    (*msg)->payloadSize = loadSize;
    memcpy((*msg)->payload, load, loadSize);

    (*msg)->haveNIC = (*msg)->havePri = (*msg)->haveUP =
        (*msg)->haveOPC = (*msg)->haveDPC = (*msg)->haveSLS = true;

    return (ITS_SUCCESS);
}

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* _MTP3_PP_H_ */

