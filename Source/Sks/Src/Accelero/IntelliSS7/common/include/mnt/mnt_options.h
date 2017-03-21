///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:09  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:59  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:55  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:57  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:03  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:44  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:59  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.3  2001/08/09 21:03:42  hdivoux
// LOG: Port to GNU g++.
// LOG:
// LOG: Revision 1.2  2001/08/06 21:55:52  hdivoux
// LOG: Added GCS related predefined commands.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:07:15  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_options.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $"

//
//
// mnt_options.h: MNT options.
//
//


#if !defined(_MNT_OPTIONS_H_)
#define _MNT_OPTIONS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <mnt.h>

#include <gcs_client.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


///////////////////////////////////////////////////////////////////////////////
//
//  MntOptions.
//

class MntOptions
{
public:

    MntOptions()
    :   _parserDebug(false),
#if defined(WIN32)
        _gcsDaemonName("4803@localhost"),
#else /* !defined(WIN32) */
        _gcsDaemonName("4803"),
#endif /* defined(WIN32) */
        _gcsGroupName("test"),
        _gcsConnectionNameRoot("test")
    {
        _gcsConnectTimeout.sec = 10;
        _gcsConnectTimeout.usec = 0;
    }

    // Default copy constructor ok.

    // Default assignment operator ok.

    // Destructor must not be virtual (not a base class).

    ~MntOptions()
    {
        // Nothing to do.
    }

    ////////////////////////////////////////////////////////////

    // Debug.

    void
    SetDebugOn()
    {
        _debug = true;
    }

    void
    SetDebugOff()
    {
        _debug = false;
    }

    bool
    IsDebugOn() const
    {
        return _debug;
    }

    ////////////////////////////////////////////////////////////

    // Parser Debug.

    void 
    SetParserDebugOn()
    { 
        _parserDebug = true; 
    }

    void 
    SetParserDebugOff()
    { 
        _parserDebug = false; 
    }

    bool 
    IsParserDebugOn() const
    { 
        return _parserDebug; 
    }

    ////////////////////////////////////////////////////////////

    // GCS.

    void
    SetGcsDaemonName(const std::string& gcsDaemonName)
    {
        _gcsDaemonName = gcsDaemonName;
    }

    const std::string&
    GetGcsDaemonName() const
    {
        return _gcsDaemonName;
    }

    void
    SetGcsGroupName(const std::string& gcsGroupName)
    {
        _gcsGroupName = gcsGroupName;
    }

    const std::string&
    GetGcsGroupName() const
    {
        return _gcsGroupName;
    }

    void
    SetGcsConnectionNameRoot(const std::string& gcsConnectionNameRoot)
    {
        _gcsConnectionNameRoot = gcsConnectionNameRoot;
    }

    const std::string&
    GetGcsConnectionNameRoot() const
    {
        return _gcsConnectionNameRoot;
    }

    void
    SetGcsConnectTimeout(GCS_TIME gcsConnectTimeout)
    {
        _gcsConnectTimeout = gcsConnectTimeout;
    }

    const GCS_TIME&
    GetGcsConnectTimeout() const
    {
        return _gcsConnectTimeout;
    }

protected:

    static bool     _debug; // MUST be static due to usage context.

    bool            _parserDebug;

    std::string     _gcsDaemonName;
    std::string     _gcsGroupName;
    std::string     _gcsConnectionNameRoot;
    GCS_TIME        _gcsConnectTimeout;
};


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_OPTIONS_H_)
