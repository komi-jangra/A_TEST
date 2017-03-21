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
 *  ID: $Id: tcap++.h,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:55  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:53  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:29  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/08 07:42:26  adutta
 * LOG: FIx for BCGI Helpdesk# 640
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:36  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.1.30.3  2005/01/31 09:28:58  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged
 * LOG:
 * LOG: Revision 7.4.2.1.30.2  2004/12/16 02:56:41  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.4.2.1.30.1  2004/12/15 15:50:46  ssingh
 * LOG: changes in Reject param; ported from SHIM branch.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/09/09 10:32:23  vjatti
 * LOG: Intialized the len to zero in SetOrigAddr() & SetDestAddr(),
 * LOG: which else causes core dump, if SetRouteByPCSSN not set &  GTT
 * LOG: also not set in OrigParty addr.
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.3  2002/10/28 19:58:03  ngoel
 * LOG: add tc-notice interface for ansi tcap
 * LOG:
 * LOG: Revision 7.2  2002/09/16 18:37:49  mmiers
 * LOG: Add U-ABORT for ANSI
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:33  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/08/20 16:52:28  mmiers
 * LOG: Second try.
 * LOG:
 * LOG: Revision 6.5  2002/08/20 16:37:15  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.4  2002/07/09 14:29:46  omayor
 * LOG: ANSI-96 changes tested in PR5 ported to current. Now to be tested.
 * LOG:
 * LOG: Revision 6.3  2002/07/03 22:40:23  yranade
 * LOG: Missing trailing comma.
 * LOG:
 * LOG: Revision 6.2  2002/05/08 16:27:29  mmiers
 * LOG: Add network indicator setting.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/12/18 17:51:06  mmiers
 * LOG: Add has methods.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:52  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/06/27 22:57:41  mmiers
 * LOG: Continue getting rid of the need for bc.h
 * LOG:
 * LOG: Revision 4.3  2001/06/26 17:39:29  mmiers
 * LOG: Work around link problems.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/03/15 21:02:45  omayor
 * LOG: Fix a few typos made during the inline conversion.
 * LOG:
 * LOG: Revision 3.2  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:39  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/07/14 17:24:30  fhasle
 * LOG:
 * LOG: updated TCAP to support ITU 97 and Timer Reset.
 * LOG:
 * LOG: Revision 2.3  2000/06/13 20:02:13  mmiers
 * LOG:
 * LOG: C++ assertion no longer throws by default.
 * LOG:
 * LOG: Revision 2.2  2000/04/24 15:27:08  mmiers
 * LOG:
 * LOG:
 * LOG: Type bug fix.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 17:39:09  rsonak
 * LOG:
 * LOG: Added constructors for TCAP_Component and its subclasses that
 * LOG: take in TCAP_CPT as input.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:02  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.33  1999/08/30 16:03:34  skarmakar
 * LOG:
 * LOG:
 * LOG: Add in missing const modifiers
 * LOG:
 * LOG: Revision 1.32  1999/08/30 15:53:29  mmiers
 * LOG:
 * LOG:
 * LOG: Essentially satisfies Hubert's objections to the OO model.
 * LOG:
 * LOG: Revision 1.31  1999/08/26 17:18:15  labuser
 * LOG:
 * LOG:
 * LOG: Remove "nonstandard" warnings.
 * LOG:
 * LOG: Revision 1.30  1999/08/24 22:33:31  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a long standing bug based on the size of a dialogue.
 * LOG:
 * LOG: Revision 1.29  1999/08/13 20:12:25  mmiers
 * LOG:
 * LOG:
 * LOG: operation code is not mandatory in ITU TCAP results
 * LOG:
 * LOG: Revision 1.28  1999/08/09 20:24:07  ssharma
 * LOG: Added Print() methods to the Component and Dialogue classes.
 * LOG:
 * LOG: Revision 1.27  1999/08/06 14:50:55  mmiers
 * LOG:
 * LOG:
 * LOG: Remove SetComponentPresent().  This member is always populated
 * LOG: by the stack, and should be read-only to the user.
 * LOG:
 * LOG: Revision 1.26  1999/08/03 16:19:51  mmiers
 * LOG:
 * LOG:
 * LOG: Adjustments for using ANSI SCCP with ITU TCAP.
 * LOG:
 * LOG: Revision 1.25  1999/07/30 16:13:05  mmiers
 * LOG:
 * LOG:
 * LOG: Add old signature back in, make new one explicit.  Compilation couldn't
 * LOG: tell the difference between the two.
 * LOG:
 * LOG: Revision 1.24  1999/07/29 17:36:12  mmiers
 * LOG:
 * LOG:
 * LOG: Vectorize these things.
 * LOG:
 * LOG: Revision 1.23  1999/07/27 23:25:00  mmiers
 * LOG:
 * LOG:
 * LOG: Add some more generic dispatchers, this time for an integrated stack
 * LOG: in the application.  Add a method to determine if this is the last
 * LOG: component in a C++ TCAP_Component.
 * LOG:
 * LOG: Revision 1.22  1999/07/16 23:11:18  mmiers
 * LOG:
 * LOG:
 * LOG: Operation code is INTEGER type for ITU TCAP.
 * LOG:
 * LOG: Revision 1.21  1999/06/23 22:58:55  mmiers
 * LOG:
 * LOG:
 * LOG: Have to watch where we define extern "C".
 * LOG:
 * LOG: Revision 1.20  1999/06/18 22:53:11  mmiers
 * LOG:
 * LOG:
 * LOG: Oops, fix get and set for problem
 * LOG:
 * LOG: Revision 1.19  1999/06/18 22:50:54  mmiers
 * LOG:
 * LOG:
 * LOG: Update ITU definitions for sanity.
 * LOG:
 * LOG: Revision 1.18  1999/02/12 23:40:23  mmiers
 * LOG:
 * LOG:
 * LOG: Start preparing for simultaneous protocol families.
 * LOG:
 * LOG: Revision 1.17  1999/01/27 17:59:26  mmiers
 * LOG:
 * LOG:
 * LOG: Add DPC/OPC fields to TCAP structure.
 * LOG:
 * LOG: Revision 1.16  1998/11/13 23:14:15  mmiers
 * LOG: Sanitize the NT build environment.
 * LOG:
 * LOG: Revision 1.15  1998/10/02 17:18:08  mmiers
 * LOG: Add a LinkInvoke() method for linking operations.
 * LOG:
 * LOG: Revision 1.14  1998/09/22 23:56:30  jrao
 * LOG: Changes made to accomodate HPUX code
 * LOG:
 * LOG: Revision 1.13  1998/07/07 21:12:30  mmiers
 * LOG: Fixes for timers and TCAP cancels.
 * LOG:
 * LOG: Revision 1.12  1998/07/02 22:28:43  ahanda
 * LOG: Added Get Header to expose the Dialogue's Header
 * LOG:
 * LOG: Revision 1.11  1998/06/03 17:14:34  mmiers
 * LOG: Guess what's left.  IS634.
 * LOG:
 * LOG: Revision 1.10  1998/06/02 01:18:01  mmiers
 * LOG: More documentation for TCAP++.
 * LOG:
 * LOG: Revision 1.9  1998/06/01 23:18:14  mmiers
 * LOG: More documentation.  Custom build steps for TCAP, SCCP.
 * LOG:
 * LOG: Revision 1.8  1998/05/19 22:41:06  mmiers
 * LOG: Coding of TCAP++ is finished.
 * LOG:
 * LOG: Revision 1.7  1998/05/19 21:27:41  mmiers
 * LOG: Almost finished with TCAP++.
 * LOG:
 * LOG: Revision 1.6  1998/05/19 18:04:50  mmiers
 * LOG: More on TCAP++.
 * LOG:
 * LOG: Revision 1.5  1998/05/19 17:11:42  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 15:49:27  mmiers
 * LOG: Fix the namespace problems.
 * LOG:
 * LOG: Revision 1.3  1998/05/19 02:38:48  mmiers
 * LOG: Modify itu/tcap.h to remove the redundant structures (such as rrl/rrnl,
 * LOG: uerror/lerror, etc.).  If you have problems with this, update tcap.h
 * LOG: using "cvs update -r 1.11 tcap.h (for itu/tcap.h).
 * LOG:
 * LOG: Revision 1.2  1998/05/15 20:17:55  mmiers
 * LOG: More work on TCAP++.
 * LOG:
 * LOG: Revision 1.1  1998/05/06 21:26:51  mmiers
 * LOG: Continue working on IS634 and SCCP.  Add C++ bindings for IS634
 * LOG: SCCP, and TCAP.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_TCAP_PP_H
#define ITS_TCAP_PP_H

#include <its++.h>

#if defined(PRC)
#include <china/tcap.h>

#define TCAP_Component          TCAP_Component_PRC
#define TCAP_Dialogue           TCAP_Dialogue_PRC

#define TCAP_Invoke             TCAP_Invoke_PRC
#define TCAP_Result             TCAP_Result_PRC
#define TCAP_Error              TCAP_Error_PRC
#define TCAP_Reject             TCAP_Reject_PRC
#define TCAP_Cancel             TCAP_Cancel_PRC

#define TCAP_Unidirectional     TCAP_Unidirectional_PRC
#define TCAP_Begin              TCAP_Begin_PRC
#define TCAP_Continue           TCAP_Continue_PRC
#define TCAP_End                TCAP_End_PRC
#define TCAP_Abort              TCAP_Abort_PRC
#define TCAP_Notice             TCAP_Notice_PRC

#include <sccp++.h>

#elif defined(TTC)
#include <japan/tcap.h>

#define TCAP_Component          TCAP_Component_TTC
#define TCAP_Dialogue           TCAP_Dialogue_TTC

#define TCAP_Invoke             TCAP_Invoke_TTC
#define TCAP_Result             TCAP_Result_TTC
#define TCAP_Error              TCAP_Error_TTC
#define TCAP_Reject             TCAP_Reject_TTC
#define TCAP_Cancel             TCAP_Cancel_TTC

#define TCAP_Unidirectional     TCAP_Unidirectional_TTC
#define TCAP_Begin              TCAP_Begin_TTC
#define TCAP_Continue           TCAP_Continue_TTC
#define TCAP_End                TCAP_End_TTC
#define TCAP_Abort              TCAP_Abort_TTC
#define TCAP_Notice             TCAP_Notice_TTC

#include <sccp++.h>

#elif defined(CCITT)
#include <itu/tcap.h>

#define TCAP_Component          TCAP_Component_CCITT
#define TCAP_Dialogue           TCAP_Dialogue_CCITT

#define TCAP_Invoke             TCAP_Invoke_CCITT
#define TCAP_Result             TCAP_Result_CCITT
#define TCAP_Error              TCAP_Error_CCITT
#define TCAP_Reject             TCAP_Reject_CCITT
#define TCAP_Cancel             TCAP_Cancel_CCITT

#define TCAP_Unidirectional     TCAP_Unidirectional_CCITT
#define TCAP_Begin              TCAP_Begin_CCITT
#define TCAP_Continue           TCAP_Continue_CCITT
#define TCAP_End                TCAP_End_CCITT
#define TCAP_Abort              TCAP_Abort_CCITT
#define TCAP_Notice             TCAP_Notice_CCITT

#if defined(USE_ANSI_SCCP)

#undef CCITT
#if !defined(ANSI)
#define ANSI 1
#endif

#include <sccp++.h>

#undef ANSI
#define CCITT 1

#else /* !USE_ANSI_SCCP */

#include <sccp++.h>

#endif /* !USE_ANSI_SCCP */

#elif defined(ANSI)

#include <ansi/tcap.h>

#define TCAP_Component          TCAP_Component_ANSI
#define TCAP_Dialogue           TCAP_Dialogue_ANSI

#define TCAP_Invoke             TCAP_Invoke_ANSI
#define TCAP_Result             TCAP_Result_ANSI
#define TCAP_Error              TCAP_Error_ANSI
#define TCAP_Reject             TCAP_Reject_ANSI
#define TCAP_Cancel             TCAP_Cancel_ANSI

#define TCAP_Unidirectional     TCAP_Unidirectional_ANSI
#define TCAP_Begin              TCAP_Begin_ANSI
#define TCAP_Continue           TCAP_Continue_ANSI
#define TCAP_End                TCAP_End_ANSI
#define TCAP_Abort              TCAP_Abort_ANSI
#define TCAP_Notice             TCAP_Notice_ANSI

#if defined(USE_ITU_SCCP)

#undef ANSI
#if !defined(CCITT)
#define CCITT 1
#endif

#include <sccp++.h>

#undef CCITT
#define ANSI 1

#elif defined(USE_TTC_SCCP)

#undef ANSI
#if !defined(TTC)
#define TTC 1
#endif

#include <sccp++.h>

#undef TTC
#define ANSI 1
#elif defined(USE_PRC_SCCP)

#undef ANSI
#if !defined(PRC)
#define PRC 1
#endif

#include <sccp++.h>

#undef PRC
#define ANSI 1

#else /* !USE_ITU_SCCP/!USE_TTC_SCCP/!USE_PRC_SCCP */

#include <sccp++.h>

#endif/* !USE_ITU_SCCP/!USE_TTC_SCCP/!USE_PRC_SCCP */

#else
#error Protocol family not defined
#endif

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

// forward
class TCAP_Dialogue;

/*
 * TCAP component base class
 */
/*.interface:TCAP_Component
 *****************************************************************************
 *  Interface:
 *      TCAP_Component
 *
 *  Purpose:
 *      The TCAP_Component interface defines the base class for all TCAP
 *      components.  The class, while not abstract, should be considered
 *      as such; it is not intended that a user ever create a naked
 *      TCAP_Component object.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Component
{
public:
    /*.implementation:public,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method creates a TCAP_Component.  All derived classes
     *      use this constructor, and set the component type appropriately.
     *
     *  Input Parameters:
     *      type - the component type.  One of TCPPT_TC_INVOKE,
     *          TCPPT_TC_INVOKE_NL, TCPPT_TC_RESULT, TCPPT_TC_RESULT_L,
     *          TCPPT_TC_ERROR, TCPPT_TC_REJECT, or TCPPT_TC_CANCEL.
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
     *      ~TCAP_Component()
     ************************************************************************/
    TCAP_Component(const ITS_USHORT type)
        : hasInvokeID(false)
    {
        memset(&cpt, 0, sizeof(TCAP_CPT));
        cpt.ptype = type;
    }

    virtual ~TCAP_Component()
    {
    }

    // type
    /*.implementation:public,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method returns the type of this component.
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
     *      The type of this component.    One of TCPPT_TC_INVOKE,
     *          TCPPT_TC_INVOKE_NL, TCPPT_TC_RESULT, TCPPT_TC_RESULT_L,
     *          TCPPT_TC_ERROR, TCPPT_TC_REJECT, or TCPPT_TC_CANCEL.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_USHORT
    GetComponentType() const
    {
        return (cpt.ptype);
    }

    /*.implementation:public,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method returns a boolean indicating if this is the last
     *      component in this PDU.
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
     *      true if this is the last component in this PDU
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_USHORT
    GetLast() const
    {
        return (cpt.last_component);
    }

    // invoke id
    /*.implementation:public,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method takes an invoke id from the user and converts it into
     *      the form expected by TCAP.
     *
     *  Input Parameters:
     *      val - the invoke id value.  Range is 0-255.
     *
     *  Notes:
     *      As invoke ids are common to all TCAP components, this method is
     *      defined in the TCAP_Component base class.
     *
     ************************************************************************/
    void
    SetInvokeID(const ITS_OCTET val)
    {
        cpt.u.invoke.invoke_id.len = 3;
        cpt.u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.invoke.invoke_id.data[1] = 1;
        cpt.u.invoke.invoke_id.data[2] = val;

        hasInvokeID = true;
    }
    /*.implementation:public,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method returns the invoke id of a component.
     *
     *  Return Value:
     *      The invoke id as an unsigned char.
     *
     *  Notes:
     *      As invoke ids are common to all TCAP components, this method is
     *      defined in the TCAP_Component base class.  If no invoke id
     *      has been set (either by the user or when an invoke is Receive()'d)
     *      an exception is thrown.
     *
     ************************************************************************/
    ITS_OCTET
    GetInvokeID() const
    {
        ITS_THROW_ASSERT(hasInvokeID);

        return cpt.u.invoke.invoke_id.data[2];
    }

    static int Send(ITS_HANDLE handle,
                    TCAP_Dialogue* dlg, TCAP_Component* cpt);
    static int Receive(ITS_HANDLE handle, its::Event&,
                       TCAP_Dialogue* dlg, TCAP_Component**);
    
    /*.implementation:public,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method prints the contents of the component to the output
     *      stream that is passed in to the method.
     *
     *  Input Parameters:
     *      os - the output stream to print the contents to.
     *
     *  See Also:
     *      TCAP_Dialogue::Print
     ************************************************************************/
    virtual void 
    Print(std::ostream& os) const
    {
        std::string strBuf;

        char buf[1024];

        int i = 0;

        os << "@@@@@ Begin Print Contents of Component @@@@@" << '\n';

        os << "last_component = " << cpt.last_component << '\n';

        switch (cpt.ptype)
        {
        case TCPPT_TC_INVOKE:
    #if defined(ANSI)
        case TCPPT_TC_INVOKE_NL:
    #endif
        
            os << "ptype = Invoke" << '\n';

            // invoke_id
            strBuf = "";
            for (i = 0; i < cpt.u.invoke.invoke_id.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.invoke.invoke_id.data[i]);

                strBuf = strBuf + buf;
            }
            os << "invoke_id: len = " << cpt.u.invoke.invoke_id.len 
               << ", data = " << strBuf << '\n';

            // operation
            strBuf = "";
            for (i = 0; i < cpt.u.invoke.operation.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.invoke.operation.data[i]);

                strBuf = strBuf + buf;
            }
            os << "operation: len = " << cpt.u.invoke.operation.len 
               << ", data = " << strBuf << '\n';

            // param
            strBuf = "";
            for (i = 0; i < cpt.u.invoke.param.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.invoke.param.data[i]);

                strBuf = strBuf + buf;
            }
            os << "param: len = " << cpt.u.invoke.param.len 
               << ", data = " << strBuf << '\n';

            // opClass
    #if defined(CCITT) || defined(PRC) || defined(TTC)
            os << "opClass = " << cpt.u.invoke.opClass << '\n';
    #endif

            // timeout
            os << "timeout = " << cpt.u.invoke.timeout << '\n';

            // linked_id
            strBuf = "";
            for (i = 0; i < cpt.u.invoke.linked_id.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.invoke.linked_id.data[i]);

                strBuf = strBuf + buf;
            }
            os << "linked_id: len = " << cpt.u.invoke.linked_id.len 
               << ", data = " << strBuf << '\n';

            break;

        case TCPPT_TC_RESULT_L:
        case TCPPT_TC_RESULT_NL:
            os << "ptype = Result" << '\n';

            // invoke_id
            strBuf = "";
            for (i = 0; i < cpt.u.result.invoke_id.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.result.invoke_id.data[i]);

                strBuf = strBuf + buf;
            }
            os << "invoke_id: len = " << cpt.u.result.invoke_id.len 
               << ", data = " << strBuf << '\n';

            // operation
    #if defined(CCITT) || defined(PRC) || defined(TTC)
            strBuf = "";
            for (i = 0; i < cpt.u.result.operation.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.result.operation.data[i]);

                strBuf = strBuf + buf;
            }
            os << "operation: len = " << cpt.u.result.operation.len 
               << ", data = " << strBuf << '\n';
    #endif

            // param
            strBuf = "";
            for (i = 0; i < cpt.u.result.param.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.result.param.data[i]);

                strBuf = strBuf + buf;
            }
            os << "param: len = " << cpt.u.result.param.len 
               << ", data = " << strBuf << '\n';

            break;


    #if defined(CCITT) || defined(PRC) || defined(TTC)
        case TCPPT_TC_U_ERROR:
    #elif defined(ANSI)
        case TCPPT_TC_ERROR:
    #endif
            os << "ptype = Error" << '\n';

            // invoke_id
            strBuf = "";
            for (i = 0; i < cpt.u.error.invoke_id.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.error.invoke_id.data[i]);

                strBuf = strBuf + buf;
            }
            os << "invoke_id: len = " << cpt.u.error.invoke_id.len 
               << ", data = " << strBuf << '\n';

            // error code
            strBuf = "";
            for (i = 0; i < cpt.u.error.error.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.error.error.data[i]);

                strBuf = strBuf + buf;
            }
            os << "error: len = " << cpt.u.error.error.len 
               << ", data = " << strBuf << '\n';
        
            // param
            strBuf = "";
            for (i = 0; i < cpt.u.error.param.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.error.param.data[i]);

                strBuf = strBuf + buf;
            }

            os << "param: len = " << cpt.u.error.param.len 
               << ", data = " << strBuf << '\n';

            break;

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        case TCPPT_TC_L_REJECT:
        case TCPPT_TC_U_REJECT:
        case TCPPT_TC_R_REJECT:
    #elif defined(ANSI)
        case TCPPT_TC_REJECT:
    #endif
            os << "ptype = Reject" << '\n';

            // invoke_id
            strBuf = "";
            for (i = 0; i < cpt.u.reject.invoke_id.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.reject.invoke_id.data[i]);

                strBuf = strBuf + buf;
            }
            os << "invoke_id: len = " << cpt.u.reject.invoke_id.len 
               << ", data = " << strBuf << '\n';

            // problem code
            strBuf = "";
            for (i = 0; i < cpt.u.reject.problem.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.reject.problem.data[i]);

                strBuf = strBuf + buf;
            }
            os << "problem: len = " << cpt.u.reject.problem.len 
               << ", data = " << strBuf << '\n';
        
    #if defined(ANSI)
            // param
            strBuf = "";
            for (i = 0; i < cpt.u.reject.param.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.reject.param.data[i]);

                strBuf = strBuf + buf;
            }
            os << "param: len = " << cpt.u.reject.param.len 
               << ", data = " << strBuf << '\n';
    #endif

            break;

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        case TCPPT_TC_L_CANCEL:
        case TCPPT_TC_U_CANCEL:
    #elif defined(ANSI)
        case TCPPT_TC_CANCEL:
    #endif
            os << "ptype = Cancel" << '\n';

            // invoke_id
            strBuf = "";
            for (i = 0; i < cpt.u.cancel.invoke_id.len; i++)
            {
                sprintf(buf, "0x%02X ", cpt.u.cancel.invoke_id.data[i]);

                strBuf = strBuf + buf;
            }
            os << "invoke_id: len = " << cpt.u.cancel.invoke_id.len 
               << ", data = " << strBuf << '\n';

            break;

    #if defined(CCITT) 
        case TCAP_PT_TC_TIMER_RESET:
            if (CCITT_TCAP_Variant != CCITT_TCAP_WHITE_BOOK_97)
            {
                os << "ptype = Timer Reset. Variant is NOT ITU White Book 97" 
                   << '\n';
            }
            else
            {
                os << "ptype = Timer Reset" << '\n';

                // invoke_id
                strBuf = "";
                for (i = 0; i < cpt.u.timerReset.invoke_id.len; i++)
                {
                    sprintf(buf, "0x%02X ", cpt.u.timerReset.invoke_id.data[i]);

                    strBuf = strBuf + buf;
                }
                os << "invoke_id: len = " << cpt.u.timerReset.invoke_id.len 
                   << ", data = " << strBuf << '\n';
            }
            break;
    #elif defined(PRC)
        case TCAP_PT_TC_TIMER_RESET:
            if (PRC_TCAP_Variant != PRC_TCAP_WHITE_BOOK_97)
            {
                os << "ptype = Timer Reset. Variant is NOT ITU White Book 97" 
                   << '\n';
            }
            else
            {
                os << "ptype = Timer Reset" << '\n';

                // invoke_id
                strBuf = "";
                for (i = 0; i < cpt.u.timerReset.invoke_id.len; i++)
                {
                    sprintf(buf, "0x%02X ", cpt.u.timerReset.invoke_id.data[i]);

                    strBuf = strBuf + buf;
                }
                os << "invoke_id: len = " << cpt.u.timerReset.invoke_id.len 
                   << ", data = " << strBuf << '\n';
            }
            break;
    #endif
    
    
        default:
            ITS_THROW_ASSERT(false);
            break;
        }

        os << "@@@@@ End Print Contents of Component @@@@@" << '\n';

        return;
    }

protected:

    TCAP_Component(TCAP_CPT& cptParam)
    {
        cpt = cptParam;        
    }

    // xcvr
    /*.implementation:protected,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method defines how individual components are to be sent.
     *      Generically (i.e., in this base class), we just call
     *      TCAP_SendComponent.  Derived classes do more than this (e.g.,
     *      validity checks on the component).
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    SendThis(ITS_HANDLE handle, ITS_HDR* hdr)
    {
        return TCAP_SendComponent(handle, hdr, &cpt);
    }
    /*.implementation:protected,inline,TCAP_Component
     ************************************************************************
     *  Purpose:
     *      This method receives a TCAP component from an event structure.
     *      Generically (i.e., in this base class) this means calling
     *      TCAP_ReceiveComponent().  Derived classes perform more work
     *      (e.g., validity checks on the component).
     *
     *  Input Parameters:
     *      handle - the transport that received this event
     *      ev - the its::Event containing the component
     *
     *  Output Parameters:
     *      hdr - a pointer to an area to copy the transaction context to
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     **************************************************************************/
    virtual int
    ReceiveThis(ITS_HANDLE handle, ITS_HDR* hdr, its::Event& ev)
    {
        int ret;

        ret = TCAP_ReceiveComponent(handle, &ev.GetEvent(), hdr, &cpt);

        if (ret == ITS_SUCCESS && cpt.u.invoke.invoke_id.len >= 3)
        {
            hasInvokeID = true;
        }

        return (ret);
    }

protected:
    TCAP_CPT cpt;

private:
    bool hasInvokeID;
};

/*
 * TCAP dialogue base class
 */

#if defined(CCITT) || defined(PRC) || defined(TTC)
#define TCAP_OID_TAG     0x06
#elif defined(ANSI)
#define TCAP_OID_TAG     0xDC
#define TCAP_UI_TAG      0xFD
#endif

/*.interface:TCAP_Dialogue
 *****************************************************************************
 *  Interface:
 *      TCAP_Dialogue
 *
 *  Purpose:
 *      The TCAP_Dialogue interface defines the base class for all TCAP
 *      dialogues.  The class, while not abstract, should be considered
 *      as such; it is not intended that a user ever create a naked
 *      TCAP_Dialogue object.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Dialogue
{
public:
    friend class TCAP_Component;

    TCAP_Dialogue(ITS_OCTET ptype)
    {
        memset(&hdr, 0, sizeof(ITS_HDR));
        memset(&dlg, 0, sizeof(TCAP_DLG));

        hdr.type = ITS_TCAP;
        dlg.ptype = ptype;
    }
    virtual ~TCAP_Dialogue()
    {
    }

    ITS_USHORT
    GetDialogueType() const
    {
        return dlg.ptype;
    }

    /* dialogue ID */
    ITS_CTXT
    GetDialogueID() const
    {
        return hdr.context.dialogue_id;
    }
    void
    SetDialogueID(const ITS_CTXT did)
    {
        hdr.context.dialogue_id = did;
    }

    /* component present */
    virtual bool
    IsComponentPresent() const
    {
        return dlg.u.uni.cpt_present != 0;
    }

    /* QOS */
    virtual void
    GetQualityOfService(ITS_OCTET& flags,
                        ITS_OCTET& slsKey,
                        ITS_OCTET& priority,
                        ITS_OCTET& networkInd) const
    {
        flags = dlg.u.uni.qos.indicator;
        slsKey = dlg.u.uni.qos.sls_key;
        priority = dlg.u.uni.qos.priority;
        networkInd = dlg.u.uni.qos.networkInd;
    }
    virtual void
    SetQualityOfService(const ITS_OCTET flags,
                        const ITS_OCTET slsKey = 0,
                        const ITS_OCTET priority = 0,
                        const ITS_OCTET networkInd = 0)
    {
        dlg.u.uni.qos.indicator = flags;
        dlg.u.uni.qos.sls_key = slsKey;
        dlg.u.uni.qos.priority = priority;
        dlg.u.uni.qos.networkInd = networkInd;
    }

    /* application context */
    virtual void
    GetApplicationContext(ITS_OCTET* buf, int& len) const
    {
        if (dlg.u.uni.ac_name.len > 2)
        {
            len = dlg.u.uni.ac_name.len - 2;
            memcpy(buf, &dlg.u.uni.ac_name.data[2], len);
        }
        else
        {
            len = 0;
        }
    }
    virtual void
    SetApplicationContext(const ITS_OCTET* buf, const int len)
    {
        /* OID Tag */
        if (len != 0)
        {
            dlg.u.uni.ac_name.data[0] = TCAP_OID_TAG;
            dlg.u.uni.ac_name.data[1] = (ITS_OCTET)len;
            memcpy(&dlg.u.uni.ac_name.data[2], buf, len);
            dlg.u.uni.ac_name.len = (len + 2);
        }
        else
        {
            dlg.u.uni.ac_name.len = 0;
        }
    }
    virtual void
    GetApplicationContext(ITS_ByteArray& buf) const
    {
        if (dlg.u.uni.ac_name.len > 2)
        {
            buf.assign(&dlg.u.uni.ac_name.data[2],
                       &dlg.u.uni.ac_name.data[2] + (dlg.u.uni.ac_name.len - 2));
        }
        else
        {
            buf.erase(buf.begin(), buf.end());
        }
    }
    virtual void
    SetApplicationContext(const ITS_ByteArray& buf)
    {
        /* OID Tag */
        if (buf.size() > 2)
        {
            dlg.u.uni.ac_name.data[0] = TCAP_OID_TAG;
            dlg.u.uni.ac_name.data[1] = (ITS_OCTET)buf.size();
            memcpy(&dlg.u.uni.ac_name.data[2], &buf[0], buf.size());
            dlg.u.uni.ac_name.len = buf.size() + 2;
        }
        else
        {
            dlg.u.uni.ac_name.len = 0;
        }
    }

    /* user info */
    virtual void
    GetUserInfo(ITS_OCTET* buf, int& len) const
    {
        len = dlg.u.uni.user_info.len;
        memcpy(buf, dlg.u.uni.user_info.data, len);
    }
    virtual void
    SetUserInfo(const ITS_OCTET* buf, const int len)
    {
#if defined(ANSI)
        dlg.u.uni.user_info.data[0] = TCAP_UI_TAG;
        dlg.u.uni.user_info.data[1] = (ITS_OCTET)len;
        memcpy(&dlg.u.uni.user_info.data[2], buf, len);
        dlg.u.uni.user_info.len = len + 2;
#elif defined(CCITT) || defined(PRC) || defined(TTC)
        memcpy(dlg.u.uni.user_info.data, buf, len);
        dlg.u.uni.user_info.len = len;
#endif
    }
    virtual void
    GetUserInfo(ITS_ByteArray& buf) const
    {
        buf.assign(dlg.u.uni.user_info.data,
                   dlg.u.uni.user_info.data + dlg.u.uni.user_info.len);
    }
    virtual void
    SetUserInfo(const ITS_ByteArray& buf)
    {
#if defined(ANSI)
        dlg.u.uni.user_info.data[0] = TCAP_UI_TAG;
        dlg.u.uni.user_info.data[1] = (ITS_OCTET)buf.size();
        memcpy(&dlg.u.uni.user_info.data[2], &buf[0], buf.size());
        dlg.u.uni.user_info.len = buf.size() + 2;
#elif defined(CCITT) || defined(PRC) || defined(TTC)
        memcpy(dlg.u.uni.user_info.data, &buf[0], buf.size());
        dlg.u.uni.user_info.len = buf.size();
#endif
    }

    // xcvr
    virtual bool
    SendCheck() const
    {
        return true;
    }
    virtual bool
    ReceiveCheck()
    {
        return true;
    }
    static inline int
    Send(ITS_HANDLE handle, TCAP_Dialogue* dlg)
    {
        bool checkOk = dlg->SendCheck();

        ITS_THROW_ASSERT(checkOk);

        return TCAP_SendDialogue(handle, &dlg->hdr, &dlg->dlg);
    }

    static int Receive(ITS_HANDLE handle, its::Event&, TCAP_Dialogue**);

    // Expose the Header
    const ITS_HDR&
    GetHeader() const
    {
        return (hdr);
    }
    
    /*.implementation:public,inline,TCAP_Dialogue
     ************************************************************************
     *  Purpose:
     *      This method prints the contents of the dialogue to the output
     *      stream that is passed in to the method.
     *
     *  Input Parameters:
     *      os - the output stream to print the contents to.
     *
     *  See Also:
     *      TCAP_Component::Print
     ************************************************************************/
    virtual void 
    Print(std::ostream& os) const
    {
        std::string strBuf;
        char buf[1024];
        unsigned int i = 0;

        os << "@@@@@ Begin Print Contents of Dialogue @@@@@" << '\n';

        switch (dlg.ptype)
        {
        case TCPPT_TC_UNI:
            os << "ptype = Unidirectional" << '\n';

            // qos
            sprintf(buf, "qos : indicator = 0x%02X, sls_key = 0x%02X, "
                         "priority = 0x%02X\n", dlg.u.uni.qos.indicator,
                         dlg.u.uni.qos.sls_key, 
                         dlg.u.uni.qos.priority);
            os << buf;

            // ac_name
            strBuf = "";
            for (i = 0; i < dlg.u.uni.ac_name.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.uni.ac_name.data[i]);

                strBuf = strBuf + buf;
            }
            os << "ac_name: len = " << dlg.u.uni.ac_name.len
                << ", data = " << strBuf << '\n';

            // user_info
            strBuf = "";
            for (i = 0; i < dlg.u.uni.user_info.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.uni.user_info.data[i]);

                strBuf = strBuf + buf;
            }
            os << "user_info: len = " << dlg.u.uni.user_info.len
               << ", data = " << strBuf << '\n';

            // orig_addr
            strBuf = "";
            for (i = 0; i < dlg.u.uni.orig_addr.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.uni.orig_addr.data[i]);

                strBuf = strBuf + buf;
            }
            os << "orig_addr: len = " << dlg.u.uni.orig_addr.len
               << ", data = " << strBuf << '\n';

            // dest_addr
            strBuf = "";
            for (i = 0; i < dlg.u.uni.dest_addr.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.uni.dest_addr.data[i]);

                strBuf = strBuf + buf;
            }
            os << "dest_addr: len = " << dlg.u.uni.dest_addr.len
               << ", data = " << strBuf << '\n';

            // opc
            strBuf = "";
            for (i = 0; i < sizeof(MTP3_POINT_CODE); i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.uni.opc.data[i]);

                strBuf = strBuf + buf;
            }
            os << "opc: len = " << sizeof(MTP3_POINT_CODE) << ", data = " << strBuf << '\n';

            // dpc
            strBuf = "";
            for (i = 0; i < sizeof(MTP3_POINT_CODE); i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.uni.dpc.data[i]);

                strBuf = strBuf + buf;
            }
            os << "dpc: len = " << sizeof(MTP3_POINT_CODE) << ", data = " << strBuf << '\n';

            break;

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        case TCPPT_TC_BEGIN:
    #elif defined(ANSI)
        case TCPPT_TC_QUERY_W_PERM:
        case TCPPT_TC_QUERY_WO_PERM:
    #endif
    
    #if defined(CCITT) || defined(PRC) || defined(TTC)
            os << "ptype = Begin" << '\n';
    #elif defined(ANSI)
            os << "ptype = Query" << '\n';
    #endif

            os << "cpt_present = " << dlg.u.begin.cpt_present << '\n';
        
            // qos
            sprintf(buf, "qos : indicator = 0x%02X, sls_key = 0x%02X, "
                         "priority = 0x%02X\n", dlg.u.begin.qos.indicator,
                         dlg.u.begin.qos.sls_key, 
                         dlg.u.begin.qos.priority);
            os << buf;

            // ac_name 
            strBuf = "";
            for (i = 0; i < dlg.u.begin.ac_name.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.begin.ac_name.data[i]);

                strBuf = strBuf + buf;
            }
            os << "ac_name: len = " << dlg.u.begin.ac_name.len
               << ", data = " << strBuf << '\n';

            // user_info
            strBuf = "";
            for (i = 0; i < dlg.u.begin.user_info.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.begin.user_info.data[i]);

                strBuf = strBuf + buf;
            }
            os << "user_info: len = " << dlg.u.begin.user_info.len
               << ", data = " << strBuf << '\n';

            // orig_addr
            strBuf = "";
            for (i = 0; i < dlg.u.begin.orig_addr.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.begin.orig_addr.data[i]);

                strBuf = strBuf + buf;
            }
            os << "orig_addr: len = " << dlg.u.begin.orig_addr.len
               << ", data = " << strBuf << '\n';

            // dest_addr
            strBuf = "";
            for (i = 0; i < dlg.u.begin.dest_addr.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.begin.dest_addr.data[i]);

                strBuf = strBuf + buf;
            }
            os << "dest_addr: len = " << dlg.u.begin.dest_addr.len
               << ", data = " << strBuf << '\n';

            // opc
            strBuf = "";
            for (i = 0; i < sizeof(MTP3_POINT_CODE); i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.begin.opc.data[i]);

                strBuf = strBuf + buf;
            }
            os << "opc: len = " << sizeof(MTP3_POINT_CODE) << ", data = " << strBuf << '\n';

            // dpc
            strBuf = "";
            for (i = 0; i < sizeof(MTP3_POINT_CODE); i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.begin.dpc.data[i]);

                strBuf = strBuf + buf;
            }
            os << "dpc: len = " << sizeof(MTP3_POINT_CODE) << ", data = " << strBuf << '\n';

            break;


    #if defined(CCITT) || defined(PRC) || defined(TTC)
        case TCPPT_TC_END:
    #elif defined(ANSI)
        case TCPPT_TC_RESP:
    #endif

    #if defined(CCITT) || defined(PRC) || defined(TTC)
            os << "ptype = End" << '\n';
    #elif defined(ANSI)
            os << "ptype = Resp" << '\n';
    #endif

            os << "cpt_present = " << dlg.u.end.cpt_present << '\n';

            // qos
            sprintf(buf, "qos : indicator = 0x%02X, sls_key = 0x%02X, "
                         "priority = 0x%02X\n", dlg.u.end.qos.indicator,
                         dlg.u.end.qos.sls_key, 
                         dlg.u.end.qos.priority);
            os << buf;

            // ac_name
            strBuf = "";
            for (i = 0; i < dlg.u.end.ac_name.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.end.ac_name.data[i]);

                strBuf = strBuf + buf;
            }
            os << "ac_name: len = " << dlg.u.end.ac_name.len
                << ", data = " << strBuf << '\n';

            // user_info
            strBuf = "";
            for (i = 0; i < dlg.u.end.user_info.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.end.user_info.data[i]);

                strBuf = strBuf + buf;
            }
            os << "user_info: len = " << dlg.u.end.user_info.len
                << ", data = " << strBuf << '\n';

            sprintf(buf, "termination = 0x%02X\n", dlg.u.end.termination);

            os << buf;

            break;

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        case TCPPT_TC_CONTINUE:
    #elif defined(ANSI)
        case TCPPT_TC_CONV_W_PERM:
        case TCPPT_TC_CONV_WO_PERM:
    #endif

    #if defined(CCITT) || defined(PRC) || defined(TTC)
            os << "ptype = Continue" << '\n';
    #elif defined(ANSI)
            os << "ptype = Conversation" << '\n';
    #endif

            os << "cpt_present = " << dlg.u.cont.cpt_present << '\n';

            // qos
            sprintf(buf, "qos : indicator = 0x%02X, sls_key = 0x%02X, "
                         "priority = 0x%02X\n", dlg.u.cont.qos.indicator,
                         dlg.u.cont.qos.sls_key, 
                         dlg.u.cont.qos.priority);
            os << buf;

            // ac_name
            strBuf = "";
            for (i = 0; i < dlg.u.cont.ac_name.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.cont.ac_name.data[i]);

                strBuf = strBuf + buf;
            }

            os << "ac_name: len = " << dlg.u.cont.ac_name.len
               << ", data = " << strBuf << '\n';

            // user_info
            strBuf = "";
            for (i = 0; i < dlg.u.cont.user_info.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.cont.user_info.data[i]);

                strBuf = strBuf + buf;
            }
            os << "user_info: len = " << dlg.u.cont.user_info.len
               << ", data = " << strBuf << '\n';

            // orig_addr
            strBuf = "";
            for (i = 0; i < dlg.u.cont.orig_addr.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.cont.orig_addr.data[i]);

                strBuf = strBuf + buf;
            }
            os << "orig_addr: len = " << dlg.u.cont.orig_addr.len
               << ", data = " << strBuf << '\n';

            // opc
            strBuf = "";
            for (i = 0; i < sizeof(MTP3_POINT_CODE); i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.cont.opc.data[i]);

                strBuf = strBuf + buf;
            }
            os << "opc: len = " << sizeof(MTP3_POINT_CODE) << ", data = " << strBuf << '\n';


            break;

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        case TCPPT_TC_P_ABORT:
        case TCPPT_TC_U_ABORT:
    #elif defined(ANSI)
        case TCPPT_TC_ABORT:
    #endif
        
    #if defined(CCITT) || defined(PRC) || defined(TTC)
            os << "ptype = P/U Abort" << '\n';
    #elif defined(ANSI)
            os << "ptype = Abort" << '\n';
    #endif

            os << "abort_reason = " << dlg.u.abort.abort_reason << '\n';

            // qos
            sprintf(buf, "qos : indicator = 0x%02X, sls_key = 0x%02X, "
                         "priority = 0x%02X\n", dlg.u.abort.qos.indicator,
                         dlg.u.abort.qos.sls_key, 
                         dlg.u.abort.qos.priority);
            os << buf;

            // ac_name
            strBuf = "";
            for (i = 0; i < dlg.u.abort.ac_name.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.abort.ac_name.data[i]);

                strBuf = strBuf + buf;
            }
            os << "ac_name: len = " << dlg.u.abort.ac_name.len
               << ", data = " << strBuf << '\n';

            // user_info
            strBuf = "";
            for (i = 0; i < dlg.u.abort.user_info.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.abort.user_info.data[i]);

                strBuf = strBuf + buf;
            }

            os << "user_info: len = " << dlg.u.abort.user_info.len
               << ", data = " << strBuf << '\n';

            break;

        case TCPPT_TC_NOTICE:
        
            os << "ptype = Notice" << '\n';
        
            os << "report_cause = " << dlg.u.notice.report_cause << '\n';

            // user_data
            strBuf = "";
            for (i = 0; i < dlg.u.notice.user_data_len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.notice.user_data.data[i]);

                strBuf = strBuf + buf;
            }
            os << "user_data: len = " << dlg.u.notice.user_data_len
               << ", data = " << strBuf << '\n';

            // orig_addr
            strBuf = "";
            for (i = 0; i < dlg.u.notice.orig_addr.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.notice.orig_addr.data[i]);

                strBuf = strBuf + buf;
            }
            os << "orig_addr: len = " << dlg.u.notice.orig_addr.len
               << ", data = " << strBuf << '\n';

            // dest_addr
            strBuf = "";
            for (i = 0; i < dlg.u.notice.dest_addr.len; i++)
            {
                sprintf(buf, "0x%02X ", dlg.u.notice.dest_addr.data[i]);

                strBuf = strBuf + buf;
            }
            os << "dest_addr: len = " << dlg.u.notice.dest_addr.len
               << ", data = " << strBuf << '\n';

            break;
        }
    
        os << "@@@@@ End Print Contents of Dialogue @@@@@" << '\n';

        return;
    }

protected:
    ITS_HDR hdr;
    TCAP_DLG dlg;
    TCAP_Dialogue(ITS_HDR& _hdr, TCAP_DLG& _dlg)
    {
        hdr = _hdr;
        dlg = _dlg;
    }
};

//////////////////////////////////////////////////////////////////
//
// All components
//
//////////////////////////////////////////////////////////////////

//
// INVOKE
//
/*.interface:TCAP_Invoke
 *****************************************************************************
 *  Interface:
 *      TCAP_Invoke
 *
 *  Purpose:
 *      The TCAP_Invoke component defines the basic interface for applications
 *      wishing to invoke remote operations.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Invoke : public TCAP_Component
{
public:
    TCAP_Invoke(bool isLast = true)
        : TCAP_Component(TCPPT_TC_INVOKE)
    {
    #if defined(ANSI)
        if (!isLast)
        {
            cpt.ptype = TCPPT_TC_INVOKE_NL;
        }
    #endif

        cpt.u.invoke.timeout = 0;

        hasOperation = false;
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        hasClass = false;
    #endif
        hasLinkedID = false;
    }

    TCAP_Invoke(TCAP_CPT cptParam)
        : TCAP_Component(cptParam)
    {

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_INVOKE);
    #endif

    #if defined(ANSI)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_INVOKE ||
                         cptParam.ptype == TCPPT_TC_INVOKE_NL);
    #endif

    }

    // operation
#if defined(CCITT) || defined(PRC) || defined(TTC)
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method sets the operation field of an invoke component.  The
     *      signature and behavior of this method is different depending on the
     *      standard used.
     *
     *  Input Parameters:
     *          code - the operation code
     *
     ************************************************************************/
    void SetOperation(const ITS_LONG code)
    {
        int opSize = sizeof(ITS_LONG);
        int i;

        /* pretty, ain't it?  It boils down to shearing off the sign
         * extension bits, except the last ITS_OCTET (if 127 > code > -128) */
        if (code < 0)
        {
            while (opSize > 1 &&
                   ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FF) == 0x0FF))
            {
                opSize--;
            }
        }
        else if (code > 0)
        {
            while (opSize > 1 &&
                   ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FFU) == 0x00))
            {
                opSize--;
            }
        }
        else
        {
            opSize = 1;
        }

        cpt.u.invoke.operation.len = 2 + opSize;
        cpt.u.invoke.operation.data[0] = TCPPN_LOCAL_OP_TAG;
        cpt.u.invoke.operation.data[1] = opSize;

        for (i = opSize; i > 0; i--)
        {
            cpt.u.invoke.operation.data[2 + opSize - i] =
                (code >> ((i - 1) * ITS_BITS_PER_BYTE)) & 0x0FF;
        }

        hasOperation = true;
    }
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method gets the operation field of an invoke component.  The
     *      signature and behavior of this method is different depending on the
     *      standard used.
     *
     *  Output Parameters:
     *          code - the operation code
     *
     *  Notes:
     *      If the operation is not present, an exception will be thrown.
     *
     ************************************************************************/
    void
    GetOperation(ITS_LONG& code) const
    {
        int size, i;

        ITS_THROW_ASSERT(hasOperation);

        ITS_THROW_ASSERT(cpt.u.invoke.operation.len <= 2 + sizeof(ITS_LONG));
        ITS_THROW_ASSERT(cpt.u.invoke.operation.len - 2 ==
                         cpt.u.invoke.operation.data[1]);

        size = (int)cpt.u.invoke.operation.data[1];

        /* figure out the sign */
        if (cpt.u.invoke.operation.data[1] & 0x80U)
        {
            code = -1;
        }
        else
        {
            code = 0;
        }

        for (i = size; i > 0; i--)
        {
            code |=
                ((ITS_LONG)(cpt.u.invoke.operation.data[2 + size - i]) & 0x0FF)
                 << ((i - 1) * ITS_BITS_PER_BYTE);
        }
    }
#elif defined(ANSI)
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method sets the operation field of an invoke component.  The
     *      signature and behavior of this method is different depending on the
     *      standard used.
     *
     *  Input Parameters:
     *          isNational - indicates if this operation is national or private.
     *          family - the operation family
     *          code - the operation code
     *
     ************************************************************************/
    void SetOperation(const bool isNational,
                      const ITS_OCTET family, const ITS_OCTET code)
    {
        cpt.u.invoke.operation.len = 4;
        if (isNational)
        {
            cpt.u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
        }
        else
        {
            cpt.u.invoke.operation.data[0] = TCPPN_OCI_PRIVATE_TCAP;
        }
        cpt.u.invoke.operation.data[1] = 2;
        cpt.u.invoke.operation.data[2] = family;
        cpt.u.invoke.operation.data[3] = code;

        hasOperation = true;
    }
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method gets the operation field of an invoke component.  The
     *      signature and behavior of this method is different depending on the
     *      standard used.
     *
     *  Output Parameters:
     *          isNational - indicates if this operation is national or private.
     *          family - the operation family
     *          code - the operation code
     *
     *  Notes:
     *      If the operation is not present, an exception will be thrown.
     *
     ************************************************************************/
    void
    GetOperation(bool& isNational,
                 ITS_OCTET& family, ITS_OCTET& code) const
    {
        ITS_THROW_ASSERT(hasOperation);

        ITS_THROW_ASSERT(cpt.u.invoke.operation.len == 4 &&
                         cpt.u.invoke.operation.data[1] == 2);

        isNational = cpt.u.invoke.operation.data[0] == TCPPN_OCI_NATIONAL_TCAP;
        family =  cpt.u.invoke.operation.data[2];
        code =  cpt.u.invoke.operation.data[3];
    }
#endif
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method determines if an operation is present.
     *
     *  Output Parameters:
     *      None.
     *
     *  Notes:
     *
     ************************************************************************/
    bool
    HasOperation(void) const
    {
        return (hasOperation);
    }

    // parameter
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method copies a user-defined paramter into the invoke
     *      component.
     *
     *  Input Parameters:
     *      buf - a buffer containing the parameter to copy into this component
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      If an invoke does not have a parameter, the user need not call this
     *      method; the parameter is assumed to not be present unless this method
     *      is called with a non-zero length.
     *
     *      If the parameter is too large for TCAP to handle, an exception will
     *      be thrown.
     *
     ************************************************************************/
    void
    SetParameter(const ITS_OCTET* buf, const int len)
    {
        ITS_THROW_ASSERT(len <= PR_SIZE);

        cpt.u.invoke.param.len = len;
        memcpy(cpt.u.invoke.param.data, buf, len);
    }
    void
    SetParameter(const ITS_ByteArray& buf)
    {
        ITS_THROW_ASSERT(buf.size() <= PR_SIZE);

        cpt.u.invoke.param.len = buf.size();
        memcpy(cpt.u.invoke.param.data, &buf[0], buf.size());
    }
    /*.implementation:public
     ************************************************************************
     *  Purpose:
     *      This method copies the parameter in an invoke component into a
     *      user supplied buffer.
     *
     *  Input Parameters:
     *      buf - a buffer to copy the parameter into
     *
     *  Output Parameters:
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      At some point, the "len" parameter will become an in/out parameter.
     *      It should be set to the maximum size of the buffer to copy to;
     *      this method will then check to make sure the parameter to copy is
     *      smaller than the buffer supplied.  Users should therefore set
     *      the length *now* to avoid problems in the future.
     *
     *      Also note that returning a length of zero indicates that no
     *      parameter is present.
     *
     *  See Also:
     ************************************************************************/
    void
    GetParameter(ITS_OCTET* buf, int& len) const
    {
        len = cpt.u.invoke.param.len;
        memcpy(buf, cpt.u.invoke.param.data, len);
    }
    void
    GetParameter(ITS_ByteArray& buf) const
    {
        buf.assign(cpt.u.invoke.param.data,
                   cpt.u.invoke.param.data + cpt.u.invoke.param.len);
    }

    // timeout
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method sets the timeout value for TCAP invokes.
     *
     *  Input Parameters:
     *      val - the timeout value.  Range is 1-500.
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
    void
    SetTimeOut(const ITS_USHORT val)
    {
        cpt.u.invoke.timeout = val;
    }
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method retrieves the timeout value for TCAP invokes.
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
     *      The timeout value.  Range is 1-500.
     *
     *  Notes:
     *
     *  See Also:
     ************************************************************************/
    ITS_USHORT
    GetTimeOut() const
    {
        return (cpt.u.invoke.timeout);
    }

#if defined(CCITT) || defined(PRC) || defined(TTC)
    // operation class
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method sets the operation class for TCAP components
     *
     *  Input Parameters:
     *      val - a number from 1 to 4 indicating the class
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
     *      This method is for ITU TCAP only.
     *
     *  See Also:
     ************************************************************************/
    void
    SetClass(const ITS_USHORT val)
    {
        cpt.u.invoke.opClass = val;
        hasClass = true;
    }
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method retrieves the operation class for TCAP invokes.
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
     *      A number from 1 to 4 indicating the operation class.
     *
     *  Notes:
     *      This method is for ITU TCAP only.
     *
     *  See Also:
     ************************************************************************/
    ITS_USHORT
    GetClass() const
    {
        ITS_THROW_ASSERT(hasClass);

        return (cpt.u.invoke.opClass);
    }
#endif

    // linked id (aka "correlation id")
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method sets the linked-id (ITU) or correlation-id (ANSI) to
     *      the value supplied.
     *
     *  Input Parameters:
     *      val - the linked id value.  Range is 0-255.
     *
     *  Notes:
     *      The user need not call this method if the linked-id is not relevant.
     *      It is assumed that no linked id is present unless this method is
     *      called.
     *
     ************************************************************************/
    void
    SetLinkedID(const ITS_OCTET val)
    {
        cpt.u.invoke.linked_id.len = 3;
        cpt.u.invoke.linked_id.data[0] = TCPPN_INVOKE_TAG;
        cpt.u.invoke.linked_id.data[1] = 1;
        cpt.u.invoke.linked_id.data[2] = val;

        hasLinkedID = true;
    }

    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method gets the linked-id (ITU) or correlation-id (ANSI) of an
     *      invoke, if supplied.
     *
     *  Return Value:
     *      The linked id as an unsigned char.
     *
     *  Notes:
     *      If the invoke does not have a linked id, an exception will be
     *      thrown.
     *
     ************************************************************************/
    ITS_OCTET
    GetLinkedID() const
    {
        ITS_THROW_ASSERT(hasLinkedID);

        return cpt.u.invoke.linked_id.data[2];
    }

    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method sets the linked-id (ITU) or correlation-id (ANSI) to
     *      the invoke id from the invoke component supplied.
     *
     *  Input Parameters:
     *      linkTo - the invoke component to correlate to
     *
     *  Notes:
     *      The user need not call this method if the linked-id is not relevant.
     *      It is assumed that no linked id is present unless this method is
     *      called.
     *
     *  See Also:
     *      SetLinkedID()
     ************************************************************************/
    void
    LinkInvoke(const TCAP_Invoke* linkTo)
    {
        cpt.u.invoke.linked_id.len = linkTo->cpt.u.invoke.invoke_id.len;

        memcpy(cpt.u.invoke.linked_id.data,
               linkTo->cpt.u.invoke.invoke_id.data,
               linkTo->cpt.u.invoke.invoke_id.len);

        hasLinkedID = true;
    }

    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method determines if the linked ID is set.
     *
     *  Input Parameters:
     *      None.
     *
     *  Notes:
     *
     ************************************************************************/
    bool
    HasLinkedID(void) const
    {
        return (hasLinkedID);
    }

protected:
    /*.implementation:protected
     ************************************************************************
     *  Purpose:
     *      This method sends an invoke component to TCAP.  Sanity checks are
     *      performed to ensure that a valid component is sent.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     *  Notes:
     *      Sanity checks include the following:
     *          o the operation code must be set
     *          o for ITU operation, the invoke class must be set
     *
     *      If the sanity checks fail, an exception is thrown.
     *
     ************************************************************************/
    virtual int
    SendThis(ITS_HANDLE handle, ITS_HDR* hdr)
    {
        ITS_THROW_ASSERT(hasOperation);
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        ITS_THROW_ASSERT(hasClass);
    #endif

        return TCAP_Component::SendThis(handle, hdr);
    }

    /*.implementation:protected,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method receives an invoke component.  Member variables in
     *      this class are populated with data about the component received.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      ev - the event to receive this component from
     *
     *  Output Parameters:
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully received, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    ReceiveThis(ITS_HANDLE handle, ITS_HDR* hdr, its::Event& ev)
    {
        int ret;

        ret = TCAP_Component::ReceiveThis(handle, hdr, ev);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        if (cpt.u.invoke.operation.len >= 3)
        {
            hasOperation = true;
        }

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        hasClass = true;
    #endif

        if (cpt.u.invoke.linked_id.len > 0)
        {
            hasLinkedID = true;
        }

        return ret;
    }

private:
    bool hasOperation;
#if defined(CCITT) || defined(PRC) || defined(TTC)
    bool hasClass;
#endif
    bool hasLinkedID;
};

//
// RESULT
//
/*.interface:TCAP_Result
 *****************************************************************************
 *  Interface:
 *      TCAP_Result
 *
 *  Purpose:
 *      The TCAP_Result component defines the basic interface to remote
 *      operation return results.  This class is used to reply to successful
 *      invoke operations.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Result : public TCAP_Component
{
public:
    TCAP_Result(bool isLast = true)
        : TCAP_Component(TCPPT_TC_RESULT_L)
    {
        if (!isLast)
        {
            cpt.ptype = TCPPT_TC_RESULT_NL;
        }

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        hasOperation = false;
        hasParameter = false;
    #endif
    }

    TCAP_Result(TCAP_CPT cptParam)
        : TCAP_Component(cptParam)
    {
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_RESULT_L ||
                         cptParam.ptype == TCPPT_TC_RESULT_NL);
    }

    // operation
#if defined(CCITT) || defined(PRC) || defined(TTC)
    /*.implementation:public,inline,TCAP_Result
     ************************************************************************
     *  Purpose:
     *      This method sets the operation field of a result component.
     *
     *  Input Parameters:
     *      code - the operation code
     *
     *  Notes:
     *      This method is relevant only to ITU TCAP.
     *
     ************************************************************************/
    void
    TCAP_Result::SetOperation(const ITS_LONG code)
    {
        int opSize = sizeof(ITS_LONG);
        int i;

        /* pretty, ain't it?  It boils down to shearing off the sign
         * extension bits, except the last ITS_OCTET (if 127 > code > -128) */
        if (code < 0)
        {
            while (opSize > 1 &&
                   ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FF) == 0x0FF))
            {
                opSize--;
            }
        }
        else if (code > 0)
        {
            while (opSize > 1 &&
                   ((code >> ((opSize - 1) * ITS_BITS_PER_BYTE) & 0x0FFU) == 0x00))
            {
                opSize--;
            }
        }
        else
        {
            opSize = 1;
        }

        cpt.u.result.operation.len = 2 + opSize;
        cpt.u.result.operation.data[0] = TCPPN_LOCAL_OP_TAG;
        cpt.u.result.operation.data[1] = opSize;

        for (i = opSize; i > 0; i--)
        {
            cpt.u.result.operation.data[2 + opSize - i] =
                (code >> ((i - 1) * ITS_BITS_PER_BYTE)) & 0x0FF;
        }

        hasOperation = true;
    }
    /*.implementation:public,inline,TCAP_Result
     ************************************************************************
     *  Purpose:
     *      This method gets the operation field of a result component.
     *
     *  Output Parameters:
     *      code - the operation code
     *
     *  Notes:
     *      This method is relevant only to ITU TCAP.  This method can throw
     *      exceptions.
     *
     ************************************************************************/
    void
    TCAP_Result::GetOperation(ITS_LONG& code) const
    {
        ITS_THROW_ASSERT(hasOperation);

        int size, i;

        ITS_THROW_ASSERT(hasOperation);

        ITS_THROW_ASSERT(cpt.u.invoke.operation.len <= 2 + sizeof(ITS_LONG));
        ITS_THROW_ASSERT(cpt.u.invoke.operation.len - 2 ==
                         cpt.u.invoke.operation.data[1]);

        size = (int)cpt.u.invoke.operation.data[1];

        /* figure out the sign */
        if (cpt.u.invoke.operation.data[1] & 0x80U)
        {
            code = -1;
        }
        else
        {
            code = 0;
        }

        for (i = size; i > 0; i--)
        {
            code |=
                ((ITS_LONG)(cpt.u.invoke.operation.data[2 + size - i]) & 0x0FF)
                 << ((i - 1) * ITS_BITS_PER_BYTE);
        }
    }

    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method determines if an operation is present.
     *
     *  Output Parameters:
     *      None.
     *
     *  Notes:
     *
     ************************************************************************/
    bool
    HasOperation(void) const
    {
        return (hasOperation);
    }
#endif

    // parameter
    /*.implementation:public,inline,TCAP_Result
     ************************************************************************
     *  Purpose:
     *      This method copies a user-defined paramter into the result
     *      component.
     *
     *  Input Parameters:
     *      buf - a buffer containing the parameter to copy into this component
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      If a result does not have a parameter, the user need not call this
     *      method;the parameter is assumed to not be present unless this method
     *      is called with a non-zero length.
     *
     *      If the parameter is too large for TCAP to handle, an exception will
     *      be thrown.
     *
     ************************************************************************/
    void
    SetParameter(const ITS_OCTET* buf, const int len)
    {
        ITS_THROW_ASSERT(len <= PR_SIZE);

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        hasParameter = true;
    #endif

        cpt.u.result.param.len = len;
        memcpy(cpt.u.result.param.data, buf, len);
    }
    void
    SetParameter(const ITS_ByteArray& buf)
    {
        ITS_THROW_ASSERT(buf.size() <= PR_SIZE);

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        hasParameter = true;
    #endif

        cpt.u.result.param.len = buf.size();
        memcpy(cpt.u.result.param.data, &buf[0], buf.size());
    }

    /*.implementation:public,inline,TCAP_Result
     ************************************************************************
     *  Purpose:
     *      This method copies the parameter in an result component into a
     *      user supplied buffer.
     *
     *  Input Parameters:
     *      buf - a buffer to copy the parameter into
     *
     *  Output Parameters:
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      At some point, the "len" parameter will become an in/out parameter.
     *      It should be set to the maximum size of the buffer to copy to;
     *      this method will then check to make sure the parameter to copy is
     *      smaller than the buffer supplied.  Users should therefore set
     *      the length *now* to avoid problems in the future.
     *
     *      Also note that returning a length of zero indicates that no
     *      parameter is present.
     *
     **************************************************************************/
    void
    GetParameter(ITS_OCTET* buf, int& len) const
    {
        len = cpt.u.result.param.len;
        memcpy(buf, cpt.u.result.param.data, len);
    }
    void
    GetParameter(ITS_ByteArray& buf) const
    {
        buf.assign(cpt.u.result.param.data,
                   cpt.u.result.param.data + cpt.u.result.param.len);
    }

protected:
    // Send and receive
    /*.implementation:protected,inline,TCAP_Result
     ***************************************************************************
     *  Purpose:
     *      This method sends a result component to TCAP.  Sanity checks are
     *      performed to ensure that a valid component is sent.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     *  Notes:
     *      Sanity checks include the following:
     *          o for ITU, the operation code must be set
     *
     *      If the sanity checks fail, an exception is thrown.
     *
     **************************************************************************/
    int
    SendThis(ITS_HANDLE handle, ITS_HDR* hdr)
    {
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        if (hasParameter)
        {
            ITS_THROW_ASSERT(hasOperation);
        }
    #endif

        return TCAP_Component::SendThis(handle, hdr);
    }

    /*.implementation:protected,inline,TCAP_Result
     ***************************************************************************
     *  Purpose:
     *      This method receives a result component.  Member variables in
     *      this class are populated with data about the component received.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      ev - the event to receive this component from
     *
     *  Output Parameters:
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully received, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     **************************************************************************/
    virtual int
    ReceiveThis(ITS_HANDLE handle, ITS_HDR* hdr, its::Event& ev)
    {
        int ret;

        ret = TCAP_Component::ReceiveThis(handle, hdr, ev);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

    #if defined(CCITT) || defined(PRC) || defined(TTC)
        if (cpt.u.result.operation.len >= 3)
        {
            hasOperation = true;
        }

        if (cpt.u.result.param.len > 0)
        {
            hasParameter = true;
        }
    #endif

        return ret;
    }

private:
#if defined(CCITT) || defined(PRC) || defined(TTC)
    bool hasOperation;
    bool hasParameter;
#endif
};

//
// ERROR
//
/*.interface:TCAP_Error
 *****************************************************************************
 *  Interface:
 *      TCAP_Error
 *
 *  Purpose:
 *      The TCAP_Error component defines the basic interface to remote
 *      remote operation error codes.  This class is used to reply to
 *      unsuccessful invoke operations.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Error : public TCAP_Component
{
public:
    TCAP_Error()
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        : TCAP_Component(TCPPT_TC_U_ERROR)
    #elif defined(ANSI)
        : TCAP_Component(TCPPT_TC_ERROR)
    #endif
    {
        hasError = false;
    }

    TCAP_Error(TCAP_CPT cptParam)
        : TCAP_Component(cptParam)
    {
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_U_ERROR);
    #endif

    #if defined(ANSI)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_ERROR);
    #endif
    }

    // error
#if defined(CCITT) || defined(PRC) || defined(TTC)
    /*.implementation:public,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *     This method sets the error code in an error component.  The signature
     *      of this method varies depending on the standard used.
     *
     *  Input Parameters:
     *          code - the error code
     *
     ************************************************************************/
    void
    TCAP_Error::SetError(const ITS_OCTET code)
    {
        cpt.u.error.error.len = 3;
        cpt.u.error.error.data[0] = TCPPN_LOCAL_ERR_TAG;
        cpt.u.error.error.data[1] = 1;
        cpt.u.error.error.data[2] = code;

        hasError = true;
    }
    /*.implementation:public,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *     This method gets the error code in an error component.  The signature
     *      of this method varies depending on the standard used.
     *
     *  Output Parameters:
     *          code - the error code
     *
     ************************************************************************/
    void
    TCAP_Error::GetError(ITS_OCTET& code) const
    {
        ITS_THROW_ASSERT(hasError);

        ITS_THROW_ASSERT(cpt.u.error.error.len == 3 &&
                         cpt.u.error.error.data[1] == 1);

        code = cpt.u.error.error.data[2];
    }
#else
    /*.implementation:public,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *     This method sets the error code in an error component.  The signature
     *      of this method varies depending on the standard used.
     *
     *  Input Parameters:
     *          code - the error code
     *          isNational - an indicator that this code is national or private
     *
     ************************************************************************/
    void
    TCAP_Error::SetError(const bool isNational, const ITS_OCTET code)
    {
        cpt.u.error.error.len = 3;
        if (isNational)
        {
            cpt.u.error.error.data[0] = TCPPN_ECI_NATIONAL_TCAP;
        }
        else
        {
            cpt.u.error.error.data[0] = TCPPN_ECI_PRIVATE_TCAP;
        }
        cpt.u.error.error.data[1] = 1;
        cpt.u.error.error.data[2] = code;

        hasError = true;
    }
    /*.implementation:public,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *     This method gets the error code in an error component.  The signature
     *      of this method varies depending on the standard used.
     *
     *  Output Parameters:
     *          code - the error code
     *          isNational - an indicator that this code is national or private
     *
     ************************************************************************/
    void
    TCAP_Error::GetError(bool& isNational, ITS_OCTET& code) const
    {
        ITS_THROW_ASSERT(hasError);

        ITS_THROW_ASSERT(cpt.u.error.error.len == 3 &&
                         cpt.u.error.error.data[1] == 1);

        isNational = cpt.u.error.error.data[0] == TCPPN_ECI_NATIONAL_TCAP;

        code = cpt.u.error.error.data[2];
    }
#endif
    /*.implementation:public,inline,TCAP_Invoke
     ************************************************************************
     *  Purpose:
     *      This method determines if an operation is present.
     *
     *  Output Parameters:
     *      None.
     *
     *  Notes:
     *
     ************************************************************************/
    bool
    HasError(void) const
    {
        return (hasError);
    }


    // parameter
    /*.implementation:public,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *      This method copies a user-defined paramter into the error
     *      component.
     *
     *  Input Parameters:
     *      buf - a buffer containing the parameter to copy into this component
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      If an error does not have a parameter, the user need not call this
     *      method;the parameter is assumed to not be present unless this method
     *      is called with a non-zero length.
     *
     *      If the parameter is too large for TCAP to handle, an exception will
     *      be thrown.
     *
     ************************************************************************/
    void
    SetParameter(const ITS_OCTET* buf, const int len)
    {
        ITS_THROW_ASSERT(len <= PR_SIZE);

        cpt.u.error.param.len = len;
        memcpy(cpt.u.error.param.data, buf, len);
    }
    void
    SetParameter(const ITS_ByteArray& buf)
    {
        ITS_THROW_ASSERT(buf.size() <= PR_SIZE);

        cpt.u.error.param.len = buf.size();
        memcpy(cpt.u.error.param.data, &buf[0], buf.size());
    }

    /*.implementation:public,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *      This method copies the parameter in an error component into a
     *      user supplied buffer.
     *
     *  Input Parameters:
     *      buf - a buffer to copy the parameter into
     *
     *  Output Parameters:
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      At some point, the "len" parameter will become an in/out parameter.
     *      It should be set to the maximum size of the buffer to copy to;
     *      this method will then check to make sure the parameter to copy is
     *      smaller than the buffer supplied.  Users should therefore set
     *      the length *now* to avoid problems in the future.
     *
     *      Also note that returning a length of zero indicates that no
     *      parameter is present.
     *
     **************************************************************************/
    void
    GetParameter(ITS_OCTET* buf, int& len) const
    {
        len = cpt.u.error.param.len;
        memcpy(buf, cpt.u.error.param.data, len);
    }
    void
    GetParameter(ITS_ByteArray& buf) const
    {
        buf.assign(cpt.u.error.param.data,
                   cpt.u.error.param.data + cpt.u.error.param.len);
    }

protected:
    /*.implementation:protected,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *      This method sends an error component to TCAP.  Sanity checks are
     *      performed to ensure that a valid component is sent.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     *  Notes:
     *      Sanity checks include the following:
     *          o the error code must be set
     *
     *      If the sanity checks fail, an exception is thrown.
     *
     ************************************************************************/
    virtual int
    SendThis(ITS_HANDLE handle, ITS_HDR* hdr)
    {
        ITS_THROW_ASSERT(hasError);

        return TCAP_Component::SendThis(handle, hdr);
    }

    /*.implementation:protected,inline,TCAP_Error
     ************************************************************************
     *  Purpose:
     *      This method receives an error component.  Member variables in
     *      this class are populated with data about the component received.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      ev - the event to receive this component from
     *
     *  Output Parameters:
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully received, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    ReceiveThis(ITS_HANDLE handle, ITS_HDR* hdr, its::Event& ev)
    {
        int ret;

        ret = TCAP_Component::ReceiveThis(handle, hdr, ev);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        if (cpt.u.error.error.len > 0)
        {
            hasError = true;
        }

        return ret;
    }

private:
    bool hasError;
};

//
// REJECT
//
/*.interface:TCAP_Reject
 *****************************************************************************
 *  Interface:
 *      TCAP_Reject
 *
 *  Purpose:
 *      The TCAP_Reject component defines the basic interface to invalid
 *      remote operation invokes.  If an application sends a malformed
 *      component, the remote stack will respond with a TCAP_Reject.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Reject : public TCAP_Component
{
public:
    TCAP_Reject(bool isLocal = true,
                bool fromUser = true)
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        : TCAP_Component(TCPPT_TC_U_REJECT)
    #elif defined(ANSI)
        : TCAP_Component(TCPPT_TC_REJECT)
    #endif
    {
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        if (isLocal)
        {
            if (fromUser)
            {
                cpt.ptype = TCPPT_TC_U_REJECT;
            }
            else
            {
                cpt.ptype = TCPPT_TC_L_REJECT;
            }
        }
        else
        {
            cpt.ptype = TCPPT_TC_R_REJECT;
        }
    #endif

        hasProblem = false;
    }

    TCAP_Reject(TCAP_CPT cptParam)
        : TCAP_Component(cptParam)
    {
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_U_REJECT ||
                         cptParam.ptype == TCPPT_TC_L_REJECT ||
                         cptParam.ptype == TCPPT_TC_R_REJECT );
    #endif

    #if defined(ANSI)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_REJECT);
    #endif
    }

    // operation
#if defined(CCITT) || defined(PRC) || defined(TTC)
    /*.implementation:public,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method sets the problem code for a reject component.  The
     *      signature of this method depends on the standard used.
     *
     *  Input Parameters:
     *          code - the problem code
     *
     ************************************************************************/
    void
    TCAP_Reject::SetProblem(const ITS_OCTET type, const ITS_OCTET code)
    {
        cpt.u.reject.problem.len = 3;
        cpt.u.reject.problem.data[0] = type;
        cpt.u.reject.problem.data[1] = 1;
        cpt.u.reject.problem.data[2] = code;

        hasProblem = true;
    }
    /*.implementation:public,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method gets the problem code for a reject component.  The
     *      signature of this method depends on the standard used.
     *
     *  Output Parameters:
     *          code - the problem code
     *
     ************************************************************************/
    void
    TCAP_Reject::GetProblem(ITS_OCTET& type, ITS_OCTET& code) const
    {
        ITS_THROW_ASSERT(hasProblem);

        ITS_THROW_ASSERT(cpt.u.reject.problem.len >= 3 &&
                         cpt.u.reject.problem.data[1] >= 1);

        type = cpt.u.reject.problem.data[0];
        code = cpt.u.reject.problem.data[2];
    }
#elif defined(ANSI)
    /*.implementation:public,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method sets the problem code for a reject component.  The
     *      signature of this method depends on the standard used.
     *
     *  Input Parameters:
     *          family - the problem family
     *          code - the problem code
     *
     ************************************************************************/
    void
    TCAP_Reject::SetProblem(const ITS_OCTET family, const ITS_OCTET code)
    {
        cpt.u.reject.problem.len = 4;
        cpt.u.reject.problem.data[0] = TCPPROB_IDENT;
        cpt.u.reject.problem.data[1] = 2;
        cpt.u.reject.problem.data[2] = family;
        cpt.u.reject.problem.data[3] = code;

        hasProblem = true;
    }
    /*.implementation:public,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method gets the problem code for a reject component.  The
     *      signature of this method depends on the standard used.
     *
     *  Output Parameters:
     *          family - the problem family
     *          code - the problem code
     *
     ************************************************************************/
    void
    TCAP_Reject::GetProblem(ITS_OCTET& family, ITS_OCTET& code) const
    {
        ITS_THROW_ASSERT(hasProblem);

        ITS_THROW_ASSERT(cpt.u.reject.problem.len >= 3 &&
                         cpt.u.reject.problem.data[1] >= 1);

        family = cpt.u.reject.problem.data[2];
        code = cpt.u.reject.problem.data[3];
    }

#endif

    // parameter
#if defined(ANSI)
    /*.implementation:public,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method copies a user-defined paramter into the reject
     *      component.
     *
     *  Input Parameters:
     *      buf - a buffer containing the parameter to copy into this component
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      If a reject does not have a parameter, the user need not call this
     *      method;the parameter is assumed to not be present unless this method
     *      is called with a non-zero length.
     *
     *      If the parameter is too large for TCAP to handle, an exception will
     *      be thrown.
     *
     *      This method is relevent to ANSI TCAP only.
     *
     *  See Also:
     ************************************************************************/
    void
    SetParameter(const ITS_OCTET* buf, const int len)
    {
        ITS_THROW_ASSERT(len <= PR_SIZE);

        cpt.u.reject.param.len = len;
        memcpy(cpt.u.reject.param.data, buf, len);
    }
    void
    SetParameter(const ITS_ByteArray& buf)
    {
        ITS_THROW_ASSERT(buf.size() <= PR_SIZE);

        cpt.u.reject.param.len = buf.size();
        memcpy(cpt.u.reject.param.data, &buf[0], buf.size());
    }

    /*.implementation:public,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method copies the parameter in a reject component into a
     *      user supplied buffer.
     *
     *  Input Parameters:
     *      buf - a buffer to copy the parameter into
     *
     *  Output Parameters:
     *      len - the length of the parameter in the buffer
     *
     *  Notes:
     *      At some point, the "len" parameter will become an in/out parameter.
     *      It should be set to the maximum size of the buffer to copy to;
     *      this method will then check to make sure the parameter to copy is
     *      smaller than the buffer supplied.  Users should therefore set
     *      the length *now* to avoid problems in the future.
     *
     *      Also note that returning a length of zero indicates that no
     *      parameter is present.
     *
     *      This method is relevent to ANSI TCAP only.
     *  Revision History:
     *
     *
     *
     ************************************************************************/
    void
    GetParameter(ITS_OCTET* buf, int& len) const
    {
        len = cpt.u.reject.param.len;
        memcpy(buf, cpt.u.reject.param.data, len);
    }
    void
    GetParameter(ITS_ByteArray& buf) const
    {
        buf.assign(cpt.u.reject.param.data,
                   cpt.u.reject.param.data + cpt.u.reject.param.len);
    }
#endif
   /*.implementation:public,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method gets the dialogue id for the TCAP Reject
     *
     *  Input Parameters:
     *      None
     *
     *  Output Parameters:
     *      None
     *
     *  Return Value:
     *      Returns the dialogie id
     *
     *  Notes:
     *
     *  Revision History:
     *----------------------------------------------------------------------
     * Name      Date        Reference               Description
     *----------------------------------------------------------------------
     * sbabu     04-06-2005  BCGI Helpdesk# 640      Fix for no dialogue ID
     *                                               assoicated with the
     *                                               L_REJECT event from TCAP
     *                                               stack.
     *
     ************************************************************************/
   ITS_CTXT
    GetDialogueID() const
    {
        return localHdr.context.dialogue_id;
    }

protected:
    /*.implementation:protected,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method sends a reject component to TCAP.  Sanity checks are
     *      performed to ensure that a valid component is sent.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     *  Notes:
     *      Sanity checks include the following:
     *          o the problem code must be set
     *
     *      If the sanity checks fail, an exception is thrown.
     *
     ************************************************************************/
    virtual int
    SendThis(ITS_HANDLE handle, ITS_HDR* hdr)
    {
        ITS_THROW_ASSERT(hasProblem);

        return TCAP_Component::SendThis(handle, hdr);
    }

    /*.implementation:protected,inline,TCAP_Reject
     ************************************************************************
     *  Purpose:
     *      This method receives a reject component.  Member variables in
     *      this class are populated with data about the component received.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      ev - the event to receive this component from
     *
     *  Output Parameters:
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully received, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    ReceiveThis(ITS_HANDLE handle, ITS_HDR* hdr, its::Event& ev)
    {
        int ret;

        ret = TCAP_Component::ReceiveThis(handle, &localHdr, ev);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        if (cpt.u.reject.problem.len > 0)
        {
            hasProblem = true;
        }

        return ret;
    }

private:
    bool hasProblem;
    
   ITS_HDR localHdr; //This is because L_Reject are received without a DLG
                      //we need to let user know what DID is it relates to.
                      //see GetDialogueID above.

};

//
// CANCEL
//
/*.interface:TCAP_Cancel
 *****************************************************************************
 *  Interface:
 *      TCAP_Cancel
 *
 *  Purpose:
 *      The TCAP_Cancel component is an artificial (at least for ANSI)
 *      component that is generated when an invoke operation times out.
 *      Note that ANSI does not have this component; IntelliSS7 generates
 *      this component for the user.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Cancel : public TCAP_Component
{
public:
    TCAP_Cancel(bool fromUser = true)
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        : TCAP_Component(TCPPT_TC_U_CANCEL)
    #elif defined(ANSI)
        : TCAP_Component(TCPPT_TC_CANCEL)
    #endif
    {
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        if (fromUser)
        {
            cpt.ptype = TCPPT_TC_U_CANCEL;
        }
        else
        {
            cpt.ptype = TCPPT_TC_L_CANCEL;
        }
    #endif
    }

    TCAP_Cancel(TCAP_CPT cptParam)
        : TCAP_Component(cptParam)
    {
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_U_CANCEL ||
                         cptParam.ptype == TCPPT_TC_L_CANCEL );
    #endif

    #if defined(ANSI)
        ITS_THROW_ASSERT(cptParam.ptype == TCPPT_TC_CANCEL);
    #endif

    }

    ITS_CTXT
    GetDialogueID() const
    {
        return hdr.context.dialogue_id;
    }

protected:
    /*.implementation:protected,inline,TCAP_Cancel
     ************************************************************************
     *  Purpose:
     *      This method sends a cancel component to TCAP.  Sanity checks are
     *      performed to ensure that a valid component is sent.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     *  Notes:
     *      Sanity checks include the following:
     *          o the problem code must be set
     *
     *      If the sanity checks fail, an exception is thrown.
     *
     ************************************************************************/
    virtual int
    SendThis(ITS_HANDLE handle, ITS_HDR* shdr)
    {
    #if defined(CCITT) || defined(PRC) || defined(TTC)
        return TCAP_Component::SendThis(handle, shdr);
    #else
        return (ITS_EINVALIDARGS);
    #endif
    }


    /*.implementation:protected,inline,TCAP_Cancel
     ************************************************************************
     *  Purpose:
     *      This method receives a reject component.  Member variables in
     *      this class are populated with data about the component received.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      ev - the event to receive this component from
     *
     *  Output Parameters:
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully received, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     ************************************************************************/
    virtual int
    ReceiveThis(ITS_HANDLE handle, ITS_HDR* lhdr, its::Event& ev)
    {
        int ret;

        ret = TCAP_Component::ReceiveThis(handle, &hdr, ev);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }

        return ret;
    }

private:
    ITS_HDR hdr;
};

//
// TIMER_RESET
//
/*.interface:TCAP_ResetTimer
 *****************************************************************************
 *  Interface:
 *      TCAP_ResetTimer
 *
 *  Purpose:
 *      The TCAP_ResetTimer component defines the basic interface to reset
 *      a timer. This class is used to reset the timer of an invoked
 *      operation. This component is only valid with ITU White Book 97.
 *
 *  Usage:
 *
 *****************************************************************************/
#if defined(CCITT) || defined(PRC) || defined(TTC)
class TCAP_ResetTimer : public TCAP_Component
{
public:
    /*.implementation:public, inline, TCAP_ResetTimer
     ************************************************************************
     *  Purpose:
     *      This method constructs a Reset Timer component.
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
     *      The variant used must be ITU White Book 97.
     *
     *  See Also:
     *************************************************************************/
    TCAP_ResetTimer::TCAP_ResetTimer() 
        : TCAP_Component(TCAP_PT_TC_TIMER_RESET)
    {
    }

    TCAP_ResetTimer(TCAP_CPT cptParam)
        : TCAP_Component(cptParam)
    {
        ITS_THROW_ASSERT(cptParam.ptype == TCAP_PT_TC_TIMER_RESET);
    }

    ITS_CTXT
    GetDialogueID() const
    {
        return hdr.context.dialogue_id;
    }

protected:
    /*.implementation:protected,inline,TCAP_ResetTimer
     ************************************************************************
     *  Purpose:
     *      This method sends a Reset Timer component to TCAP. Sanity checks are
     *      performed to ensure that a valid component is sent.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      If the component is successfully sent, ITS_SUCCESS is returned.
     *      Any other return code indicates an IntelliSS7 error.
     *
     *  Notes:
     *      Sanity checks include the following:
     *          o the invoke id must be set
     *          o The variant used must be ITU White Book 97
     *
     *      If the sanity checks fail, an exception is thrown.
     *
     ************************************************************************/
    virtual int
    SendThis(ITS_HANDLE handle, ITS_HDR* shdr)
    {
        return TCAP_Component::SendThis(handle, shdr);
    }

    /*.implementation:protected,inline,TCAP_ResetTimer
     ************************************************************************
     *  Purpose:
     *      This method receives a Reset_Timer component.
     *
     *  Input Parameters:
     *      handle - the transport we are sending from
     *      ev - the event to receive this component from
     *
     *  Output Parameters:
     *      hdr - a pointer to the context for this dialogue
     *
     *  Return Value:
     *      ITS_EPROTERR: The Reset Timer is not an indication.
     *
     *  Notes:
     *      The ResetTimer component is a request only, hence TC_User
     *      will never receive this component.
     *
     ************************************************************************/
    virtual int
    ReceiveThis(ITS_HANDLE handle, ITS_HDR* lhdr, its::Event& ev)
    {
        /* The ResetTimer is a request only. */
        return (ITS_EPROTERR);
    }

private:
    ITS_HDR hdr;
};
#endif

/*.implementation:public,inline,TCAP_Component
 ************************************************************************
 *  Purpose:
 *      This method invokes the SendThis() virtual method, as appropriate
 *      for the derived class, for a component.
 *
 *  Input Parameters:
 *      handle - the transport we are sending from
 *      dlg - the TCAP dialogue primitive this component is part of
 *
 *  Return Value:
 *      If the component is successfully sent, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This method is static.
 *
 ************************************************************************/
inline int
TCAP_Component::Send(ITS_HANDLE handle,
                     TCAP_Dialogue* dlg, TCAP_Component* cpt)
{
    return cpt->SendThis(handle, &dlg->hdr);
}

/*.implementation:static,inline,TCAP_Component
 ****************************************************************************
 *  Purpose:
 *      This method receives a TCAP component from an event and builds the
 *      appropriate component derived class, based on the component type.
 *      Note that this means this method functions as a constructor for
 *      TCAP components.
 *
 *  Input Parameters:
 *      handle - the transport that received this event
 *      ev - the its::Event containing the component
 *      dlg - the dialogue primitive this component is associated with
 *
 *  Output Parameters:
 *      cpt - the constructed component.
 *
 *  Return Value:
 *      If the component is successfully sent, ITS_SUCCESS is returned.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This method is static.
 *      This method can throw exceptions.
 *
 ****************************************************************************/
inline int
TCAP_Component::Receive(ITS_HANDLE handle, its::Event& ev,
                        TCAP_Dialogue* dlg, TCAP_Component** cpt)
{
    int ret;
    ITS_HDR hdr;

    *cpt = NULL;
    TCAP_CPT c;

    ITS_THROW_ASSERT(TCAP_MSG_TYPE((&ev.GetEvent())) == ITS_TCAP_CPT);

    if (dlg != NULL)
    {
        hdr = dlg->hdr;
    }
    else
    {
        hdr.type = ITS_TCAP;
        hdr.context.dialogue_id = 0;
    }

    ret = TCAP_ReceiveComponent(handle, &ev.GetEvent(),
                                &hdr, &c);

    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    switch (c.ptype)
    {
    case TCPPT_TC_INVOKE:
        *cpt = new TCAP_Invoke(true);
        break;

#if defined(ANSI)
    case TCPPT_TC_INVOKE_NL:
        *cpt = new TCAP_Invoke(false);
        break;
#endif

    case TCPPT_TC_RESULT_L:
        *cpt = new TCAP_Result(true);
        break;

    case TCPPT_TC_RESULT_NL:
        *cpt = new TCAP_Result(false);
        break;

#if defined(CCITT) || defined(PRC) || defined(TTC)
    case TCPPT_TC_U_ERROR:
#elif defined(ANSI)
    case TCPPT_TC_ERROR:
#endif
        *cpt = new TCAP_Error();
        break;

#if defined(CCITT) || defined(PRC) || defined(TTC)
    case TCPPT_TC_L_REJECT:
        *cpt = new TCAP_Reject(true, false);
        break;

    case TCPPT_TC_U_REJECT:
        *cpt = new TCAP_Reject(true, true);
        break;

    case TCPPT_TC_R_REJECT:
        *cpt = new TCAP_Reject(false, false);
        break;

#elif defined(ANSI)
    case TCPPT_TC_REJECT:
        *cpt = new TCAP_Reject();
        break;
#endif

#if defined(CCITT) || defined(PRC) || defined(TTC)
    case TCPPT_TC_L_CANCEL:
        *cpt = new TCAP_Cancel(false);
        break;

    case TCPPT_TC_U_CANCEL:
        *cpt = new TCAP_Cancel(true);
        break;

#elif defined(ANSI)
    case TCPPT_TC_CANCEL:
        *cpt = new TCAP_Cancel();
        break;
#endif

    default:
        ITS_THROW_ASSERT(false);
        break;
    }

    return (*cpt)->ReceiveThis(handle, &hdr, ev);
}

///////////////////////////////////////////////////////////////////////
//
// ALL DIALOGUES
//
///////////////////////////////////////////////////////////////////////

//
// UNI
//
/*.interface:TCAP_Unidirectional
 *****************************************************************************
 *  Interface:
 *      TCAP_Unidirectional
 *
 *  Purpose:
 *      The TCAP_Unidirectional message class defines the interface for one-way
 *      transactions.  Unidirectional messages are never replied to.
 *      This message represents the TCPPT_TC_UNI dialogue type.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Unidirectional : public TCAP_Dialogue
{
public:
    friend class TCAP_Dialogue;

    TCAP_Unidirectional()
        : TCAP_Dialogue(TCPPT_TC_UNI),
          haveOPC(false),
          haveDPC(false)
    {
    }

    // XCVR checks
    virtual bool
    SendCheck() const
    {
        return (haveOPC && haveDPC);
    }
    // stack MUST ensure this
    virtual bool
    ReceiveCheck()
    {
        haveOPC = true;
        haveDPC = true;
        return true;
    }

    // Point codes
    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method sets the origination point code for this dialogue
     *      primitive.
     *
     *  Notes:
     *      If the point code is not included in the origination address portion
     *      of the dialogue object, this method MUST be called with the
     *      originating point code.
     *
     ************************************************************************/
    void
    SetOPC(const ITS_UINT pointCode)
    {
        MTP3_PC_SET_VALUE(dlg.u.uni.opc, pointCode);
        haveOPC = true;
    }
    void
    SetOPC(const MTP3_POINT_CODE& pointCode)
    {
        dlg.u.uni.opc = pointCode;
        haveOPC = true;
    }
    void
    SetOPC(const MTP3_PointCode& pointCode)
    {
        ITS_THROW_ASSERT(pointCode.HasValue());

        MTP3_PC_SET_VALUE(dlg.u.uni.opc, pointCode.GetValue());
        haveOPC = true;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method gets the origination point code for this dialogue
     *      primitive from discrete information.
     *
     *  Output Parameters:
     *      pointCode - the point code of this address
     *
     ************************************************************************/
    void
    GetOPC(ITS_UINT& pointCode) const
    {
        pointCode = MTP3_PC_GET_VALUE(dlg.u.uni.opc);
    }
    void
    GetOPC(MTP3_POINT_CODE& pointCode) const
    {
        pointCode = dlg.u.uni.opc;
    }
    void
    GetOPC(MTP3_PointCode& pointCode) const
    {
        pointCode = dlg.u.uni.opc;
    }
    bool
    HaveOPC() const
    {
        return haveOPC;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method sets the destination point code for this dialogue
     *      primitive.
     *
     *  Input Parameters:
     *      pointCode - the point code of this address
     *
     *  Notes:
     *      If the point code is not included in the destination address portion
     *      of the dialogue object, this method MUST be called with the
     *      destination point code.
     *
     *  See Also:
     ************************************************************************/
    void
    SetDPC(const ITS_UINT pointCode)
    {
        MTP3_PC_SET_VALUE(dlg.u.uni.dpc, pointCode);
        haveDPC = true;
    }
    void
    SetDPC(const MTP3_POINT_CODE& pointCode)
    {
        dlg.u.uni.dpc = pointCode;
        haveDPC = true;
    }
    void
    SetDPC(const MTP3_PointCode& pointCode)
    {
        MTP3_PC_SET_VALUE(dlg.u.uni.dpc, pointCode.GetValue());
        haveDPC = true;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method gets the destination point code for this dialogue
     *      primitive from discrete information.
     *
     *  Output Parameters:
     *      pointCode - the point code of this address
     *
     ************************************************************************/
    void
    GetDPC(ITS_UINT& pointCode) const
    {
        pointCode = MTP3_PC_GET_VALUE(dlg.u.uni.dpc);
    }
    void
    GetDPC(MTP3_POINT_CODE& pointCode) const
    {
        pointCode = dlg.u.uni.dpc;
    }
    void
    GetDPC(MTP3_PointCode& pointCode) const
    {
        pointCode = dlg.u.uni.dpc;
    }
    bool
    HaveDPC() const
    {
        return haveDPC;
    }

    // Full SCCP Address (orig)
    /*.implementation:public,inline,TCAP_Unidirectional
     ***************************************************************************
     *  Purpose:
     *     These methods set the origination address for this dialogue primitive
     *      from discrete information.
     *
     **************************************************************************/
    void
    SetOrigAddr(const bool isNational,
                const ITS_UINT pointCode, const ITS_OCTET ssn)
    {
        ITS_OCTET addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_ROUTE_SSN;

        SetOPC(pointCode);

        if (isNational)
        {
            addrInd |= SCCP_CPA_ROUTE_NAT;
        }
        else
        {
            addrInd |= SCCP_CPA_ROUTE_INT;
        }

        SCCP_EncodeAddr(&dlg.u.uni.orig_addr, addrInd,
                        pointCode, ssn, NULL, 0);
    }
    void
    SetOrigAddr(const ITS_OCTET addrInd,
                const ITS_UINT pointCode, const ITS_OCTET ssn,
                const ITS_OCTET *gttInfo, const ITS_USHORT gttLen)
    {
        SetOPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.uni.orig_addr,
                        addrInd, pointCode, ssn,
                        gttInfo, gttLen);
    }
    void
    SetOrigAddr(const ITS_OCTET addrInd,
                const MTP3_PointCode& pointCode, const ITS_OCTET ssn,
                const ITS_ByteArray& buf)
    {
        SetOPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.uni.orig_addr,
                        addrInd, pointCode.GetValue(), ssn,
                        &buf[0], buf.size());
    }
    void
    SetOrigAddr(const SCCP_ADDR& addr)
    {
        ITS_OCTET addrInd;
        ITS_UINT pc;
        int ret;

        ret = SCCP_DecodeAddr(&addr, &addrInd,
                              &pc, NULL, NULL, NULL);
    
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        if (addrInd & SCCP_CPA_HAS_PC)
        {
            SetOPC(pc);
        }

        memcpy(&dlg.u.uni.orig_addr, &addr, sizeof(SCCP_ADDR));
    }
    void
    SetOrigAddr(const SCCP_Address& addr)
    {
        int len = 0;

        if (addr.HasPointCode())
        {
            SetOPC(addr.GetPointCode());
        }

        addr.Build(dlg.u.uni.orig_addr.data, len);
        dlg.u.uni.orig_addr.len = len;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      These methods decode the origination address for this dialogue
     *      primitive into discrete information.
     *
     ************************************************************************/
    void
    GetOrigAddr(bool& isNational, ITS_UINT& pointCode, ITS_OCTET& ssn) const
    {
        ITS_OCTET addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.uni.orig_addr,
                        &addrInd, &pointCode, &ssn, NULL, NULL);

        if (addrInd & SCCP_CPA_ROUTE_INT)
        {
            isNational = false;
        }
        else if (addrInd & SCCP_CPA_ROUTE_NAT)
        {
            isNational = true;
        }
    }
    void
    GetOrigAddr(ITS_OCTET& addrInd,
                ITS_UINT& pointCode, ITS_OCTET& ssn,
                ITS_OCTET* gttInfo, ITS_USHORT* gttLen) const
    {
        addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.uni.orig_addr,
                        &addrInd, &pointCode, &ssn,
                        gttInfo, gttLen);
    }
    void
    GetOrigAddr(ITS_OCTET& addrInd,
                MTP3_PointCode& pointCode, ITS_OCTET& ssn,
                ITS_ByteArray& gttInfo) const
    {
        addrInd = 0;
        ITS_OCTET gtt[SCCP_MAX_ADDR_LEN];
        ITS_USHORT gttLen;
        ITS_UINT pc;

        SCCP_DecodeAddr(&dlg.u.uni.orig_addr,
                        &addrInd, &pc, &ssn,
                        gtt, &gttLen);

        pointCode.SetValue(pc);
        gttInfo.assign(gtt, gtt + gttLen);
    }
    void
    GetOrigAddr(SCCP_ADDR& addr) const
    {
        memcpy(&addr, &dlg.u.uni.orig_addr, sizeof(SCCP_ADDR));
    }
    void
    GetOrigAddr(SCCP_Address& addr) const
    {
        int len = dlg.u.uni.orig_addr.len;

        addr.Parse(dlg.u.uni.orig_addr.data, len);

        ITS_THROW_ASSERT(dlg.u.uni.orig_addr.len == len);
    }


    // Full SCCP Address (dest)
    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method sets the destination address for this dialogue
     *      primitive from discrete information.
     *
     ************************************************************************/
    void
    SetDestAddr(const bool isNational,
                const ITS_UINT pointCode, const ITS_OCTET ssn)
    {
        ITS_OCTET addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_ROUTE_SSN;

        SetDPC(pointCode);

        if (isNational)
        {
            addrInd |= SCCP_CPA_ROUTE_NAT;
        }
        else
        {
            addrInd |= SCCP_CPA_ROUTE_INT;
        }

        SCCP_EncodeAddr(&dlg.u.uni.dest_addr, addrInd,
                        pointCode, ssn, NULL, 0);
    }
    void
    SetDestAddr(const ITS_OCTET addrInd,
                const ITS_UINT pointCode, const ITS_OCTET ssn,
                const ITS_OCTET* gttInfo, const ITS_USHORT gttLen)
    {
        SetDPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.uni.dest_addr,
                        addrInd, pointCode, ssn,
                        gttInfo, gttLen);
    }
    void
    SetDestAddr(const ITS_OCTET addrInd,
                const MTP3_PointCode& pointCode, const ITS_OCTET ssn,
                const ITS_ByteArray& buf)
    {
        SetDPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.uni.dest_addr,
                        addrInd, pointCode.GetValue(), ssn,
                        &buf[0], buf.size());
    }
    void
    SetDestAddr(const SCCP_ADDR& addr)
    {
        ITS_OCTET addrInd;
        ITS_UINT pc;
        int ret;

        ret = SCCP_DecodeAddr(&addr, &addrInd,
                              &pc, NULL, NULL, NULL);
    
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        if (addrInd & SCCP_CPA_HAS_PC)
        {
            SetDPC(pc);
        }

        memcpy(&dlg.u.uni.dest_addr, &addr, sizeof(SCCP_ADDR));
    }
    void
    SetDestAddr(const SCCP_Address& addr)
    {
        int len = 0;

        if (addr.HasPointCode())
        {
            SetDPC(addr.GetPointCode());
        }

        addr.Build(dlg.u.uni.dest_addr.data, len);
        dlg.u.uni.dest_addr.len = len;
    }


    /*.implementation:public
     ************************************************************************
     *  Purpose:
     *      This method decodes the destination address for this dialogue
     *      primitive into discrete information.
     *
     ****************************************************************************/
    void
    GetDestAddr(bool& isNational,
                ITS_UINT& pointCode, ITS_OCTET& ssn) const
    {
        ITS_OCTET addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.uni.dest_addr,
                        &addrInd, &pointCode, &ssn, NULL, NULL);

        if (addrInd & SCCP_CPA_ROUTE_INT)
        {
            isNational = false;
        }
        else if (addrInd & SCCP_CPA_ROUTE_NAT)
        {
            isNational = true;
        }
    }
    void
    GetDestAddr(ITS_OCTET& addrInd,
                ITS_UINT& pointCode, ITS_OCTET& ssn,
                ITS_OCTET* gttInfo, ITS_USHORT* gttLen) const
    {
        addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.uni.dest_addr,
                        &addrInd, &pointCode, &ssn,
                        gttInfo, gttLen);
    }
    void
    GetDestAddr(ITS_OCTET& addrInd,
                MTP3_PointCode& pointCode, ITS_OCTET& ssn,
                ITS_ByteArray& gttInfo) const
    {
        addrInd = 0;
        ITS_OCTET gtt[SCCP_MAX_ADDR_LEN];
        ITS_USHORT gttLen;
        ITS_UINT pc;

        SCCP_DecodeAddr(&dlg.u.uni.orig_addr,
                        &addrInd, &pc, &ssn,
                        gtt, &gttLen);

        pointCode.SetValue(pc);
        gttInfo.assign(gtt, gtt + gttLen);
    }
    void
    GetDestAddr(SCCP_ADDR& addr) const
    {
        memcpy(&addr, &dlg.u.uni.dest_addr, sizeof(SCCP_ADDR));
    }
    void
    GetDestAddr(SCCP_Address& addr) const
    {
        int len = dlg.u.uni.dest_addr.len;

        addr.Parse(dlg.u.uni.dest_addr.data, len);

        ITS_THROW_ASSERT(dlg.u.uni.dest_addr.len == len);
    }

private:
    TCAP_Unidirectional(ITS_HDR& _hdr, TCAP_DLG& _dlg)
        : TCAP_Dialogue(_hdr, _dlg)
    {
    }

    bool haveOPC;
    bool haveDPC;
};

//
// BEGIN
//
/*.interface:TCAP_Begin
 *****************************************************************************
 *  Interface:
 *      TCAP_Begin
 *
 *  Purpose:
 *      The TCAP_Begin message class defines the interface for beginning TCAP
 *      transactions.  The class implements both TCPPT_TC_BEGIN (ITU), and
 *      TCPPT_TC_QUERY_W_PERM/TCPPT_TC_QUERY_WO_PERM (ANSI) dialogues.
 *
 *      This message begins a communication session for remote operations.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Begin : public TCAP_Dialogue
{
public:
    friend class TCAP_Dialogue;

#if defined(CCITT) || defined(PRC) || defined(TTC)
    TCAP_Begin()
        : TCAP_Dialogue(TCPPT_TC_BEGIN),
          haveOPC(false),
          haveDPC(false)
#elif defined(ANSI)
    TCAP_Begin(bool withPerm = true)
        : TCAP_Dialogue(TCPPT_TC_QUERY_W_PERM),
          haveOPC(false),
          haveDPC(false)
#endif
    {
#if defined(ANSI)
        if (!withPerm)
        {
            dlg.ptype = TCPPT_TC_QUERY_WO_PERM;
        }
#endif
    }

    // XCVR checks
    virtual bool
    SendCheck() const
    {
        return (haveOPC && haveDPC);
    }
    // stack MUST ensure this
    virtual bool
    ReceiveCheck()
    {
        haveOPC = true;
        haveDPC = true;
        return true;
    }

    // Point codes
    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method sets the origination point code for this dialogue
     *      primitive.
     *
     *  Notes:
     *      If the point code is not included in the origination address portion
     *      of the dialogue object, this method MUST be called with the
     *      originating point code.
     *
     ************************************************************************/
    void
    SetOPC(const ITS_UINT pointCode)
    {
        MTP3_PC_SET_VALUE(dlg.u.begin.opc, pointCode);
        haveOPC = true;
    }
    void
    SetOPC(const MTP3_POINT_CODE& pointCode)
    {
        dlg.u.begin.opc = pointCode;
        haveOPC = true;
    }
    void
    SetOPC(const MTP3_PointCode& pointCode)
    {
        ITS_THROW_ASSERT(pointCode.HasValue());

        MTP3_PC_SET_VALUE(dlg.u.begin.opc, pointCode.GetValue());
        haveOPC = true;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method gets the origination point code for this dialogue
     *      primitive from discrete information.
     *
     *  Output Parameters:
     *      pointCode - the point code of this address
     *
     ************************************************************************/
    void
    GetOPC(ITS_UINT& pointCode) const
    {
        pointCode = MTP3_PC_GET_VALUE(dlg.u.begin.opc);
    }
    void
    GetOPC(MTP3_POINT_CODE& pointCode) const
    {
        pointCode = dlg.u.begin.opc;
    }
    void
    GetOPC(MTP3_PointCode& pointCode) const
    {
        pointCode = dlg.u.begin.opc;
    }
    bool
    HaveOPC() const
    {
        return haveOPC;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method sets the destination point code for this dialogue
     *      primitive.
     *
     *  Input Parameters:
     *      pointCode - the point code of this address
     *
     *  Notes:
     *      If the point code is not included in the destination address portion
     *      of the dialogue object, this method MUST be called with the
     *      destination point code.
     *
     *  See Also:
     ************************************************************************/
    void
    SetDPC(const ITS_UINT pointCode)
    {
        MTP3_PC_SET_VALUE(dlg.u.begin.dpc, pointCode);
        haveDPC = true;
    }
    void
    SetDPC(const MTP3_POINT_CODE& pointCode)
    {
        dlg.u.begin.dpc = pointCode;
        haveDPC = true;
    }
    void
    SetDPC(const MTP3_PointCode& pointCode)
    {
        MTP3_PC_SET_VALUE(dlg.u.begin.dpc, pointCode.GetValue());
        haveDPC = true;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method gets the destination point code for this dialogue
     *      primitive from discrete information.
     *
     *  Output Parameters:
     *      pointCode - the point code of this address
     *
     ****************************************************************************/
    void
    GetDPC(ITS_UINT& pointCode) const
    {
        pointCode = MTP3_PC_GET_VALUE(dlg.u.begin.dpc);
    }
    void
    GetDPC(MTP3_POINT_CODE& pointCode) const
    {
        pointCode = dlg.u.begin.dpc;
    }
    void
    GetDPC(MTP3_PointCode& pointCode) const
    {
        pointCode = dlg.u.begin.dpc;
    }
    bool
    HaveDPC() const
    {
        return haveDPC;
    }

    // Full SCCP Address (orig)
    /*.implementation:public,inline,TCAP_Unidirectional
     ****************************************************************************
     *  Purpose:
     *      These methods set the origination address for this dialogue primitive
     *      from discrete information.
     *
     ****************************************************************************/
    void
    SetOrigAddr(const bool isNational,
                const ITS_UINT pointCode, const ITS_OCTET ssn)
    {
        ITS_OCTET addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_ROUTE_SSN;

        SetOPC(pointCode);

        if (isNational)
        {
            addrInd |= SCCP_CPA_ROUTE_NAT;
        }
        else
        {
            addrInd |= SCCP_CPA_ROUTE_INT;
        }

        SCCP_EncodeAddr(&dlg.u.begin.orig_addr, addrInd,
                        pointCode, ssn, NULL, 0);
    }
    void
    SetOrigAddr(const ITS_OCTET addrInd,
                const ITS_UINT pointCode, const ITS_OCTET ssn,
                const ITS_OCTET *gttInfo, const ITS_USHORT gttLen)
    {
        SetOPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.begin.orig_addr,
                        addrInd, pointCode, ssn,
                        gttInfo, gttLen);
    }
    void
    SetOrigAddr(const ITS_OCTET addrInd,
                const MTP3_PointCode& pointCode, const ITS_OCTET ssn,
                const ITS_ByteArray& buf)
    {
        SetOPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.begin.orig_addr,
                        addrInd, pointCode.GetValue(), ssn,
                        &buf[0], buf.size());
    }
    void
    SetOrigAddr(const SCCP_ADDR& addr)
    {
        ITS_OCTET addrInd;
        ITS_UINT pc;
        int ret;

        ret = SCCP_DecodeAddr(&addr, &addrInd,
                              &pc, NULL, NULL, NULL);
    
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        if (addrInd & SCCP_CPA_HAS_PC)
        {
            SetOPC(pc);
        }

        memcpy(&dlg.u.begin.orig_addr, &addr, sizeof(SCCP_ADDR));
    }
    void
    SetOrigAddr(const SCCP_Address& addr)
    {
        int len = 0;

        if (addr.HasPointCode())
        {
            SetOPC(addr.GetPointCode());
        }

        addr.Build(dlg.u.begin.orig_addr.data, len);
        dlg.u.begin.orig_addr.len = len;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      These methods decode the origination address for this dialogue
     *      primitive into discrete information.
     *
     ************************************************************************/
    void
    GetOrigAddr(bool& isNational, ITS_UINT& pointCode, ITS_OCTET& ssn) const
    {
        ITS_OCTET addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.begin.orig_addr,
                        &addrInd, &pointCode, &ssn, NULL, NULL);

        if (addrInd & SCCP_CPA_ROUTE_INT)
        {
            isNational = false;
        }
        else if (addrInd & SCCP_CPA_ROUTE_NAT)
        {
            isNational = true;
        }
    }
    void
    GetOrigAddr(ITS_OCTET& addrInd,
                ITS_UINT& pointCode, ITS_OCTET& ssn,
                ITS_OCTET* gttInfo, ITS_USHORT* gttLen) const
    {
        addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.begin.orig_addr,
                        &addrInd, &pointCode, &ssn,
                        gttInfo, gttLen);
    }
    void
    GetOrigAddr(ITS_OCTET& addrInd,
                MTP3_PointCode& pointCode, ITS_OCTET& ssn,
                ITS_ByteArray& gttInfo) const
    {
        addrInd = 0;
        ITS_OCTET gtt[SCCP_MAX_ADDR_LEN];
        ITS_USHORT gttLen;
        ITS_UINT pc;

        SCCP_DecodeAddr(&dlg.u.begin.orig_addr,
                        &addrInd, &pc, &ssn,
                        gtt, &gttLen);

        pointCode.SetValue(pc);
        gttInfo.assign(gtt, gtt + gttLen);
    }
    void
    GetOrigAddr(SCCP_ADDR& addr) const
    {
        memcpy(&addr, &dlg.u.begin.orig_addr, sizeof(SCCP_ADDR));
    }
    void
    GetOrigAddr(SCCP_Address& addr) const
    {
        int len = dlg.u.begin.orig_addr.len;

        addr.Parse(dlg.u.begin.orig_addr.data, len);

        ITS_THROW_ASSERT(dlg.u.begin.orig_addr.len == len);
    }


    // Full SCCP Address (dest)
    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method sets the destination address for this dialogue
     *      primitive from discrete information.
     *
     ************************************************************************/
    void
    SetDestAddr(const bool isNational,
                const ITS_UINT pointCode, const ITS_OCTET ssn)
    {
        ITS_OCTET addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_ROUTE_SSN;

        SetDPC(pointCode);

        if (isNational)
        {
            addrInd |= SCCP_CPA_ROUTE_NAT;
        }
        else
        {
            addrInd |= SCCP_CPA_ROUTE_INT;
        }

        SCCP_EncodeAddr(&dlg.u.begin.dest_addr, addrInd,
                        pointCode, ssn, NULL, 0);
    }
    void
    SetDestAddr(const ITS_OCTET addrInd,
                const ITS_UINT pointCode, const ITS_OCTET ssn,
                const ITS_OCTET* gttInfo, const ITS_USHORT gttLen)
    {
        SetDPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.begin.dest_addr,
                        addrInd, pointCode, ssn,
                        gttInfo, gttLen);
    }
    void
    SetDestAddr(const ITS_OCTET addrInd,
                const MTP3_PointCode& pointCode, const ITS_OCTET ssn,
                const ITS_ByteArray& buf)
    {
        SetDPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.begin.dest_addr,
                        addrInd, pointCode.GetValue(), ssn,
                        &buf[0], buf.size());
    }
    void
    SetDestAddr(const SCCP_ADDR& addr)
    {
        ITS_OCTET addrInd;
        ITS_UINT pc;
        int ret;

        ret = SCCP_DecodeAddr(&addr, &addrInd,
                              &pc, NULL, NULL, NULL);
    
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        if (addrInd & SCCP_CPA_HAS_PC)
        {
            SetDPC(pc);
        }

        memcpy(&dlg.u.begin.dest_addr, &addr, sizeof(SCCP_ADDR));
    }
    void
    SetDestAddr(const SCCP_Address& addr)
    {
        int len = 0;

        if (addr.HasPointCode())
        {
            SetDPC(addr.GetPointCode());
        }

        addr.Build(dlg.u.begin.dest_addr.data, len);
        dlg.u.begin.dest_addr.len = len;
    }


    /*.implementation:public
     ************************************************************************
     *  Purpose:
     *      This method decodes the destination address for this dialogue
     *      primitive into discrete information.
     *
     ****************************************************************************/
    void
    GetDestAddr(bool& isNational,
                ITS_UINT& pointCode, ITS_OCTET& ssn) const
    {
        ITS_OCTET addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.begin.dest_addr,
                        &addrInd, &pointCode, &ssn, NULL, NULL);

        if (addrInd & SCCP_CPA_ROUTE_INT)
        {
            isNational = false;
        }
        else if (addrInd & SCCP_CPA_ROUTE_NAT)
        {
            isNational = true;
        }
    }
    void
    GetDestAddr(ITS_OCTET& addrInd,
                ITS_UINT& pointCode, ITS_OCTET& ssn,
                ITS_OCTET* gttInfo, ITS_USHORT* gttLen) const
    {
        addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.begin.dest_addr,
                        &addrInd, &pointCode, &ssn,
                        gttInfo, gttLen);
    }
    void
    GetDestAddr(ITS_OCTET& addrInd,
                MTP3_PointCode& pointCode, ITS_OCTET& ssn,
                ITS_ByteArray& gttInfo) const
    {
        addrInd = 0;
        ITS_OCTET gtt[SCCP_MAX_ADDR_LEN];
        ITS_USHORT gttLen;
        ITS_UINT pc;

        SCCP_DecodeAddr(&dlg.u.begin.orig_addr,
                        &addrInd, &pc, &ssn,
                        gtt, &gttLen);

        pointCode.SetValue(pc);
        gttInfo.assign(gtt, gtt + gttLen);
    }
    void
    GetDestAddr(SCCP_ADDR& addr) const
    {
        memcpy(&addr, &dlg.u.begin.dest_addr, sizeof(SCCP_ADDR));
    }
    void
    GetDestAddr(SCCP_Address& addr) const
    {
        int len = dlg.u.begin.dest_addr.len;

        addr.Parse(dlg.u.begin.dest_addr.data, len);

        ITS_THROW_ASSERT(dlg.u.begin.dest_addr.len == len);
    }

private:
    TCAP_Begin(ITS_HDR& _hdr, TCAP_DLG& _dlg)
        : TCAP_Dialogue(_hdr, _dlg)
    {
    }

    bool haveOPC;
    bool haveDPC;
};

//
// CONTINUE
//
/*.interface:TCAP_Continue
 *****************************************************************************
 *  Interface:
 *      TCAP_Continue
 *
 *  Purpose:
 *      The TCAP_Continue message class defines the basic interface for
 *      continuing TCAP transactions.  The class implements both
 *      TCPPT_TC_CONTINUE (ITU), and TCPPT_TC_CONV_W_PERM/TCPPT_TC_CONV_WO_PERM
 *      (ANSI) dialogues.
 *
 *      When the user does not wish to use simple request/response transactions,
 *      the TCAP_Continue dialogue is used to exchange components without
 *      terminating the transaction.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Continue : public TCAP_Dialogue
{
public:
    friend class TCAP_Dialogue;

#if defined(CCITT) || defined(PRC) || defined(TTC)
    TCAP_Continue()
        : TCAP_Dialogue(TCPPT_TC_CONTINUE),
          haveOPC(false)
#elif defined(ANSI)
    TCAP_Continue(bool withPerm = true)
        : TCAP_Dialogue(TCPPT_TC_CONV_W_PERM),
          haveOPC(false)
#endif
    {
#if defined(ANSI)
        if (!withPerm)
        {
            dlg.ptype = TCPPT_TC_CONV_WO_PERM;
        }
#endif
    }

    // XCVR checks
    virtual bool
    SendCheck() const
    {
        return (haveOPC);
    }
    // stack MUST ensure this
    virtual bool
    ReceiveCheck()
    {
        haveOPC = true;
        return true;
    }

    // Point codes
    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method sets the origination point code for this dialogue
     *      primitive.
     *
     *  Notes:
     *      If the point code is not included in the origination address portion
     *      of the dialogue object, this method MUST be called with the
     *      originating point code.
     *
     ************************************************************************/
    void
    SetOPC(const ITS_UINT pointCode)
    {
        MTP3_PC_SET_VALUE(dlg.u.begin.opc, pointCode);
        haveOPC = true;
    }
    void
    SetOPC(const MTP3_POINT_CODE& pointCode)
    {
        dlg.u.begin.opc = pointCode;
        haveOPC = true;
    }
    void
    SetOPC(const MTP3_PointCode& pointCode)
    {
        ITS_THROW_ASSERT(pointCode.HasValue());

        MTP3_PC_SET_VALUE(dlg.u.begin.opc, pointCode.GetValue());
        haveOPC = true;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      This method gets the origination point code for this dialogue
     *      primitive from discrete information.
     *
     *  Output Parameters:
     *      pointCode - the point code of this address
     *
     ************************************************************************/
    void
    GetOPC(ITS_UINT& pointCode) const
    {
        pointCode = MTP3_PC_GET_VALUE(dlg.u.begin.opc);
    }
    void
    GetOPC(MTP3_POINT_CODE& pointCode) const
    {
        pointCode = dlg.u.begin.opc;
    }
    void
    GetOPC(MTP3_PointCode& pointCode) const
    {
        pointCode = dlg.u.begin.opc;
    }
    bool
    HaveOPC() const
    {
        return haveOPC;
    }

    // Full SCCP Address (orig)
    /*.implementation:public,inline,TCAP_Unidirectional
     ****************************************************************************
     *  Purpose:
     *      These methods set the origination address for this dialogue primitive
     *      from discrete information.
     *
     ****************************************************************************/
    void
    SetOrigAddr(const bool isNational,
                const ITS_UINT pointCode, const ITS_OCTET ssn)
    {
        ITS_OCTET addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_ROUTE_SSN;

        SetOPC(pointCode);

        if (isNational)
        {
            addrInd |= SCCP_CPA_ROUTE_NAT;
        }
        else
        {
            addrInd |= SCCP_CPA_ROUTE_INT;
        }

        SCCP_EncodeAddr(&dlg.u.begin.orig_addr, addrInd,
                        pointCode, ssn, NULL, 0);
    }
    void
    SetOrigAddr(const ITS_OCTET addrInd,
                const ITS_UINT pointCode, const ITS_OCTET ssn,
                const ITS_OCTET *gttInfo, const ITS_USHORT gttLen)
    {
        SetOPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.begin.orig_addr,
                        addrInd, pointCode, ssn,
                        gttInfo, gttLen);
    }
    void
    SetOrigAddr(const ITS_OCTET addrInd,
                const MTP3_PointCode& pointCode, const ITS_OCTET ssn,
                const ITS_ByteArray& buf)
    {
        SetOPC(pointCode);

        SCCP_EncodeAddr(&dlg.u.begin.orig_addr,
                        addrInd, pointCode.GetValue(), ssn,
                        &buf[0], buf.size());
    }
    void
    SetOrigAddr(const SCCP_ADDR& addr)
    {
        ITS_OCTET addrInd;
        ITS_UINT pc;
        int ret;

        ret = SCCP_DecodeAddr(&addr, &addrInd,
                              &pc, NULL, NULL, NULL);
    
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        if (addrInd & SCCP_CPA_HAS_PC)
        {
            SetOPC(pc);
        }

        memcpy(&dlg.u.begin.orig_addr, &addr, sizeof(SCCP_ADDR));
    }
    void
    SetOrigAddr(const SCCP_Address& addr)
    {
        int len = 0;

        if (addr.HasPointCode())
        {
            SetOPC(addr.GetPointCode());
        }

        addr.Build(dlg.u.begin.orig_addr.data, len);
        dlg.u.begin.orig_addr.len = len;
    }

    /*.implementation:public,inline,TCAP_Unidirectional
     ************************************************************************
     *  Purpose:
     *      These methods decode the origination address for this dialogue
     *      primitive into discrete information.
     *
     ************************************************************************/
    void
    GetOrigAddr(bool& isNational, ITS_UINT& pointCode, ITS_OCTET& ssn) const
    {
        ITS_OCTET addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.begin.orig_addr,
                        &addrInd, &pointCode, &ssn, NULL, NULL);

        if (addrInd & SCCP_CPA_ROUTE_INT)
        {
            isNational = false;
        }
        else if (addrInd & SCCP_CPA_ROUTE_NAT)
        {
            isNational = true;
        }
    }
    void
    GetOrigAddr(ITS_OCTET& addrInd,
                ITS_UINT& pointCode, ITS_OCTET& ssn,
                ITS_OCTET* gttInfo, ITS_USHORT* gttLen) const
    {
        addrInd = 0;

        SCCP_DecodeAddr(&dlg.u.begin.orig_addr,
                        &addrInd, &pointCode, &ssn,
                        gttInfo, gttLen);
    }
    void
    GetOrigAddr(ITS_OCTET& addrInd,
                MTP3_PointCode& pointCode, ITS_OCTET& ssn,
                ITS_ByteArray& gttInfo) const
    {
        addrInd = 0;
        ITS_OCTET gtt[SCCP_MAX_ADDR_LEN];
        ITS_USHORT gttLen;
        ITS_UINT pc;

        SCCP_DecodeAddr(&dlg.u.begin.orig_addr,
                        &addrInd, &pc, &ssn,
                        gtt, &gttLen);

        pointCode.SetValue(pc);
        gttInfo.assign(gtt, gtt + gttLen);
    }
    void
    GetOrigAddr(SCCP_ADDR& addr) const
    {
        memcpy(&addr, &dlg.u.begin.orig_addr, sizeof(SCCP_ADDR));
    }
    void
    GetOrigAddr(SCCP_Address& addr) const
    {
        int len = dlg.u.begin.orig_addr.len;

        addr.Parse(dlg.u.begin.orig_addr.data, len);

        ITS_THROW_ASSERT(dlg.u.begin.orig_addr.len == len);
    }

private:
    TCAP_Continue(ITS_HDR& _hdr, TCAP_DLG& _dlg)
        : TCAP_Dialogue(_hdr, _dlg)
    {
    }

    bool haveOPC;
};

//
// END
//
/*.interface:TCAP_End
 *****************************************************************************
 *  Interface:
 *      TCAP_End
 *
 *  Purpose:
 *      The TCAP_End message class defines the basic interface for terminating
 *      TCAP transactions.  The class implements both TCPPT_TC_END (ITU),
 *      and TCPPT_TC_RESP (ANSI) dialogues.
 *
 *      When the user wishes to terminate a TCAP transaction, they will use
 *      the TCAP_End message.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_End : public TCAP_Dialogue
{
public:
#if defined(CCITT) || defined(PRC) || defined(TTC)
    TCAP_End()
        : TCAP_Dialogue(TCPPT_TC_END)
#elif defined(ANSI)
    TCAP_End()
        : TCAP_Dialogue(TCPPT_TC_RESP)
#endif
    {
    }

    // prearranged end
    bool
    IsPreArrangedEnd() const
    {
        return (dlg.u.end.termination == TCPEND_PREARRANGED);
    }
    void
    SetPreArrangedEnd(bool onOff)
    {
        if (onOff)
        {
            dlg.u.end.termination = TCPEND_PREARRANGED;
        }
        else
        {
            dlg.u.end.termination = TCPEND_BASIC;
        }
    }
};

//
// ABORT
//
/*.interface:TCAP_Abort
 *****************************************************************************
 *  Interface:
 *      TCAP_Abort
 *
 *  Purpose:
 *      The TCAP_Abort message class defines the basic interface for aborting
 *      TCAP transactions.  Note that this class can be user generated for
 *      ITU TCAP, but is stack-generated only with ANSI TCAP.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Abort : public TCAP_Dialogue
{
public:
#if defined(CCITT) || defined(PRC) || defined(TTC)
    TCAP_Abort(bool fromUser = true)
        : TCAP_Dialogue(TCPPT_TC_U_ABORT)
#elif defined(ANSI)
    TCAP_Abort()
        : TCAP_Dialogue(TCPPT_TC_ABORT)
#endif
    {
#if defined(CCITT) || defined(PRC) || defined(TTC)
        if (!fromUser)
        {
            dlg.ptype = TCPPT_TC_P_ABORT;
        }
#endif
    }

    /* component present */
    virtual bool
    IsComponentPresent() const
    {
        return (false);
    }
    virtual void
    SetComponentPresent(bool)
    {
    }

    // abort reason
    ITS_OCTET
    GetAbortReason() const
    {
        return dlg.u.abort.abort_reason;
    }
    void SetAbortReason(ITS_OCTET reason)
    {
        dlg.u.abort.abort_reason = reason;
    }

    /* abort info (ANSI only) */
    virtual void
    GetAbortInfo(ITS_OCTET* buf, int& len) const
    {
        len = dlg.u.abort.abort_info.len;
        memcpy(buf, dlg.u.abort.abort_info.data, len);
    }
    virtual void
    SetAbortInfo(const ITS_OCTET* buf, const int len)
    {
        dlg.u.abort.abort_info.len = len;
        memcpy(dlg.u.abort.abort_info.data, buf, len);
    }
    virtual void
    GetAbortInfo(ITS_ByteArray& buf) const
    {
        buf.assign(dlg.u.abort.abort_info.data,
                   dlg.u.abort.abort_info.data + dlg.u.abort.abort_info.len);
    }
    virtual void
    SetAbortInfo(const ITS_ByteArray& buf)
    {
        dlg.u.abort.abort_info.len = buf.size();
        memcpy(dlg.u.abort.abort_info.data, &buf[0], buf.size());
    }
};

//
// NOTICE
//
/*.interface:TCAP_Notice
 *****************************************************************************
 *  Interface:
 *      TCAP_Notice
 *
 *  Purpose:
 *      The TCAP_Notice message class defines the basic interface by which
 *      TCAP can deliver quality-of-service messages to the user.  At the
 *      present time, this is implemented only for ITU TCAP, and is never
 *      generated by the user.
 *
 *  Usage:
 *
 *****************************************************************************/
class TCAP_Notice : public TCAP_Dialogue
{
public:
    TCAP_Notice()
        : TCAP_Dialogue(TCPPT_TC_NOTICE)
    {
    }

    /* override component present */
    virtual bool
    IsComponentPresent() const
    {
        return (false);
    }
    virtual void
    SetComponentPresent(bool)
    {
    }

    // report cause
    ITS_OCTET
    GetReportCause() const
    {
        return dlg.u.notice.report_cause;
    }
    void
    SetReportCause(ITS_OCTET reason)
    {
        dlg.u.notice.report_cause = reason;
    }

    // Override everything else
    /* QOS */
    virtual void
    SetQualityOfService(const ITS_OCTET flags,
                        const ITS_OCTET slsKey = 0,
                        const ITS_OCTET priority = 0,
                        const ITS_OCTET networkInd = 0)
    {
    }
    virtual void
    GetQualityOfService(ITS_OCTET& flags,
                        ITS_OCTET& slsKey,
                        ITS_OCTET& priority,
                        ITS_OCTET& networkInd) const
    {
        flags = slsKey = priority = networkInd = 0;
    }

    /* application context */
    virtual void
    GetApplicationContext(ITS_OCTET* buf, int& len) const
    {
        len = 0;
    }
    virtual void
    SetApplicationContext(const ITS_OCTET* buf, const int len)
    {
    }
    virtual void
    GetApplicationContext(ITS_ByteArray& buf) const
    {
        buf.erase(buf.begin(), buf.end());
    }
    virtual void
    SetApplicationContext(const ITS_ByteArray& buf)
    {
    }

    /* user info */
    virtual void
    GetUserInfo(ITS_OCTET* buf, int& len) const
    {
        len = 0;
    }
    virtual void
    SetUserInfo(const ITS_OCTET* buf, const int len)
    {
    }
    virtual void
    GetUserInfo(ITS_ByteArray& buf) const
    {
        buf.erase(buf.begin(), buf.end());
    }
    virtual void
    SetUserInfo(const ITS_ByteArray& buf)
    {
    }
};

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This method is provided for the user to receive TCAP dialogues from
 *      the stack.  This is the preferred method of dialogue reception.
 *
 *  Input Parameters:
 *      handle - the transport this dialogue is sent from
 *      ev - the event to receive the dialogue from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      dlg - the address of a pointer that is populated with the received
 *          dialogue
 *
 *  Return Value:
 *      If the dialogue is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *      This method is static.
 *
 *      This method acts as a constructor for received dialogues.
 *
 *      This method can throw exceptions.
 *
 *  See Also:
 ****************************************************************************/
inline int
TCAP_Dialogue::Receive(ITS_HANDLE handle, its::Event& ev,
                       TCAP_Dialogue** dlg)
{
    int ret;
    ITS_HDR h;
    TCAP_DLG d;
    bool checkOk;

    *dlg = NULL;

    ITS_THROW_ASSERT(TCAP_MSG_TYPE((&ev.GetEvent())) == ITS_TCAP_DLG);

    ret = TCAP_ReceiveDialogue(handle, &ev.GetEvent(), &h, &d);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    switch (d.ptype)
    {
    case TCPPT_TC_UNI:
        *dlg = new TCAP_Unidirectional(h, d);
        checkOk = (*dlg)->ReceiveCheck();
        ITS_THROW_ASSERT(checkOk);
        break;
#if defined(CCITT) || defined(PRC) || defined(TTC)
    case TCPPT_TC_BEGIN:
        *dlg = new TCAP_Begin(h, d);
        checkOk = (*dlg)->ReceiveCheck();
        ITS_THROW_ASSERT(checkOk);
        break;
    case TCPPT_TC_CONTINUE:
        *dlg = new TCAP_Continue(h, d);
        checkOk = (*dlg)->ReceiveCheck();
        ITS_THROW_ASSERT(checkOk);
        break;
#elif defined(ANSI)
    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        *dlg = new TCAP_Begin(h, d);
        checkOk = (*dlg)->ReceiveCheck();
        ITS_THROW_ASSERT(checkOk);
        break;
    case TCPPT_TC_CONV_W_PERM:
    case TCPPT_TC_CONV_WO_PERM:
        *dlg = new TCAP_Continue(h, d);
        checkOk = (*dlg)->ReceiveCheck();
        ITS_THROW_ASSERT(checkOk);
        break;
#endif
    default:
        // Warning: If somebody adds data to the other derived classes
        // (e.g., ABORT, END, NOTICE), the non-public constructor below
        // needs to be added to the derived class and cases similar to
        // the ones above need to be written.
        *dlg = new TCAP_Dialogue(h, d);
        break;
    }

    return (ITS_SUCCESS);
}

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* ITS_TCAP_PP_H */

