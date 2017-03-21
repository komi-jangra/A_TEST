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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:57  hbalimid
 * LOG: Got here for demo isup
 * LOG:
 * LOG: Revision 5.10  2002/02/19 16:49:40  ngoel
 * LOG: add sbe vendor library class defines
 * LOG:
 * LOG: Revision 5.9  2001/12/18 21:56:43  mmiers
 * LOG: Vendor lib clues
 * LOG:
 * LOG: Revision 5.8  2001/12/17 21:11:06  mmiers
 * LOG: Finish off the vendor framework.
 * LOG:
 * LOG: Revision 5.7  2001/12/17 00:17:17  mmiers
 * LOG: Clean up the build.
 * LOG:
 * LOG: Revision 5.6  2001/12/15 01:18:53  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.5  2001/12/14 00:04:29  mmiers
 * LOG: Getting it working...
 * LOG:
 * LOG: Revision 5.4  2001/12/13 23:23:41  mmiers
 * LOG: Add the inheritance classes.
 * LOG:
 * LOG: Revision 5.3  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.2  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:57  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/07/16 15:34:05  mmiers
 * LOG: Add extern to the class decl.
 * LOG:
 * LOG: Revision 4.3  2001/06/22 18:34:10  mmiers
 * LOG: Add RM.
 * LOG:
 * LOG: Revision 4.2  2001/06/22 01:58:21  mmiers
 * LOG: Add in the SS7 RM class.  This will give the ADP team a starting
 * LOG: point.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.8  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 3.7  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.6  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.3  2001/01/30 18:11:34  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.2  2001/01/09 23:54:54  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:23  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/07/27 22:29:47  mmiers
 * LOG: Remove space.
 * LOG:
 * LOG: Revision 2.5  2000/07/27 22:27:55  mmiers
 * LOG: Simplify this a bit.
 * LOG:
 * LOG: Revision 2.4  2000/07/27 22:03:23  mmiers
 * LOG: Last of the core changes for PR3.  Removed last stubs, stack
 * LOG: binding is now dynamic.
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:03:33  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  2000/02/02 15:52:58  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO conversion.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 00:52:36  mmiers
 * LOG:
 * LOG:
 * LOG: Continue the OO trip.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:45  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.19  1999/10/25 18:28:09  mmiers
 * LOG:
 * LOG:
 * LOG: Convert transport to hush the whiners.
 * LOG:
 * LOG: Revision 1.18  1999/09/01 00:53:29  mmiers
 * LOG:
 * LOG:
 * LOG: This work makes the transport system a little more sane.  What I
 * LOG: did was make the Transport class implement the default behavior
 * LOG: for transports, which should make things like:
 * LOG:     Transport tc = transport->GetTC();
 * LOG: work when you say
 * LOG:     tc.GetNextEvent(ev);
 * LOG:
 * LOG: Revision 1.17  1999/07/29 01:58:18  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up the first round of addressing Hubert's review comments.
 * LOG:
 * LOG: Revision 1.16  1998/11/19 00:36:20  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.15  1998/09/22 16:01:25  jrao
 * LOG: Port to HPUX.  Some work still needs to be done with threading -- using
 * LOG: condition variables to support Suspend()/Resume().
 * LOG:
 * LOG: Revision 1.14  1998/06/26 14:30:40  mmiers
 * LOG: Convert C++ transports to use C types.
 * LOG:
 * LOG: Revision 1.13  1998/06/18 23:39:32  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.12  1998/06/18 19:21:24  mmiers
 * LOG: SS7 transport type.
 * LOG:
 * LOG: Revision 1.11  1998/06/18 17:16:29  mmiers
 * LOG: Finish up the C transports and the SS7 transports.
 * LOG:
 * LOG: Revision 1.10  1998/06/02 19:43:14  mmiers
 * LOG: Correct some embedded URL's.
 * LOG:
 * LOG: Revision 1.9  1998/06/01 16:35:19  mmiers
 * LOG: Documentation changes, library subystem naming changes, bug-fixes,
 * LOG: project settings changes, etc.
 * LOG:
 * LOG: Revision 1.8  1998/05/31 02:59:39  mmiers
 * LOG: More documenation, stabilizing the interfaces.
 * LOG:
 * LOG: Revision 1.7  1998/05/29 22:35:36  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.6  1998/05/29 15:08:57  mmiers
 * LOG: More documentation.
 * LOG:
 * LOG: Revision 1.5  1998/05/29 03:31:32  mmiers
 * LOG: More work on documentation.  Most of this is just adding interface
 * LOG: description boxes without actually adding text.  Some of this is
 * LOG: genuine bug fixing.
 * LOG:
 * LOG: Revision 1.4  1998/05/19 17:11:48  mmiers
 * LOG: Put everything in the its namespace, if namespaces are available.
 * LOG: This seems to be the path of least resistance.
 * LOG:
 * LOG: Revision 1.3  1998/05/14 20:41:45  mmiers
 * LOG: Update SCCP (read implement).  The rest are modifications to get
 * LOG: further the implementation of worker threads.
 * LOG:
 * LOG: Revision 1.2  1998/05/01 00:24:34  mmiers
 * LOG: Update routing functions.
 * LOG:
 * LOG: Revision 1.1  1998/04/22 22:20:05  mmiers
 * LOG: Clean up transport implementations.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_SS7_TRANS_H
#define ITS_SS7_TRANS_H

#if !defined(TANDEM)

#include <its.h>
#include <its_transports.h>
#include <its_mlist.h>

#else /* TANDEM */

#include <itsh>
#include <itstrans>
#include <itsmlist>

#endif /* TANDEM */

#ident "$Id: its_ss7_trans.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $"

#if !defined(ITS_SS7_TRANS_ONESHOT)
#define ITS_SS7_TRANS_ONESHOT

/*
 * vendors must define these functions
 */
#if defined(__cplusplus)
extern "C"
{
#endif

typedef struct _SS7TRAN_ManagerRec *SS7_Transport;

/*
 * The SS7STACK instance record has some commonality.  Vendor libs
 * are encouraged to inherit from this record.
 */
typedef struct
{
    SS7_Transport   owner;
    MQUEUE_MsgQueue *sndQueue;
    MQUEUE_MsgQueue *rcvQueue;
}
VENDOR_Part;

/*
 * This is the important part of the inheritance.  Vendor instances
 * should extend this structure to whatever is specific for their
 * implementation.
 */
typedef struct
{
    ITS_CoreObjectPart  core;
    VENDOR_Part         vendor;
}
VENDOR_Instance;

#define VENDOR_OWNING_TRANSPORT(x) \
    (((VENDOR_Instance *)(x))->vendor.owner)

#define VENDOR_SND_Q(x) \
    (((VENDOR_Instance *)(x))->vendor.sndQueue)

#define VENDOR_RCV_Q(x) \
    (((VENDOR_Instance *)(x))->vendor.rcvQueue)

/*
 * subordinate (vendor) class records share a common
 * event API.
 */
typedef int             (*SS7_EventProc)(VENDOR_Instance *,
                                         ITS_EVENT *);

/*
 * stack binding
 */
typedef struct
{
    SS7_EventProc   getNextEvent;
    SS7_EventProc   peekNextEvent;
    SS7_EventProc   putEvent;
}
SS7STACK_ClassPart;

/*
 * the vendor class record.
 */
typedef struct
{
    ITS_CoreClassPart       coreClass;
    SS7STACK_ClassPart      ss7Class;
}
SS7STACK_ClassRec, *SS7STACK_Class;

#define SS7STACK_CLASS_GET_NEXT_EVENT(x) \
    (((SS7STACK_Class)(x))->ss7Class.getNextEvent)

#define SS7STACK_CLASS_PEEK_NEXT_EVENT(x) \
    (((SS7STACK_Class)(x))->ss7Class.peekNextEvent)

#define SS7STACK_CLASS_PUT_EVENT(x) \
    (((SS7STACK_Class)(x))->ss7Class.putEvent)

/*
 * an SS7 transport in "C"
 */
typedef struct
{
    ITS_SS7_HANDLE          handle;
    SS7STACK_Class          subordinate;
}
SS7TRAN_ObjectPart;

typedef struct _SS7TRAN_ManagerRec
{
    ITS_CoreObjectPart      core;
    TRANSPORT_ObjectPart    transport;
    SS7TRAN_ObjectPart      ss7;
}
SS7TRAN_Manager;

#define SS7TRAN_HANDLE(x) \
    (((SS7TRAN_Manager *)(x))->ss7.handle)

#define SS7TRAN_SUBORDINATE(x) \
    (((SS7TRAN_Manager *)(x))->ss7.subordinate)

ITSDLLAPI extern TRANSPORT_ClassRec   itsSS7TRAN_ClassRec;
ITSDLLAPI extern TRANSPORT_Class      itsSS7TRAN_Class;

#define SS7TRAN_CLASS_NAME  "SS7TRAN"

ITSDLLAPI SS7TRAN_Manager* SS7TRAN_CreateTransport(const char *name,
                                                   ITS_USHORT instance,
                                                   ITS_UINT mask);
ITSDLLAPI void SS7TRAN_DeleteTransport(SS7TRAN_Manager *ft);

/*
 * special case instances.  These are for the IntelliNet stack
 * (it doesn't need transports).
 */
ITSSS7DLLAPI extern SS7TRAN_Manager* ISS7_ANSI_Stack;
ITSSS7DLLAPI extern SS7TRAN_Manager* ISS7_CCITT_Stack;

/*
 * stack bindings
 */
#define SS7_STACK_BINDING_STRING    "StackBinding"

#define INTELLISS7_CLASS_NAME       "INTELLISS7_CLASS"
#define DECSS7_CLASS_NAME           "DECSS7"
#define DATAKINETICS_CLASS_NAME     "DATAKINETICS"
#define EXCEL_CLASS_NAME            "EXCEL"
#define NEWNET_CLASS_NAME           "NEWNET"
#define NMS_CLASS_NAME              "NMS"
#define TANDEM_CLASS_NAME           "TANDEM"

/*
 * vendor classes.
 */
SS7DLLAPI extern ITS_Class          itsSS7STACK_ClassANSI;  /* for vendor inheritance */
SS7DLLAPI extern ITS_Class          itsSS7STACK_ClassCCITT;
SS7DLLAPI extern SS7STACK_ClassRec  itsSS7STACK_ClassRecANSI;
SS7DLLAPI extern SS7STACK_ClassRec  itsSS7STACK_ClassRecCCITT;

ITSSS7DLLAPI extern ITS_Class          itsINTELLISS7_Class;    /* we're weird */
ITSSS7DLLAPI extern ITS_Class          itsINTELLISS7_ClassANSI;
ITSSS7DLLAPI extern ITS_Class          itsINTELLISS7_ClassCCITT;

VSS7DLLAPI extern ITS_Class          itsNMS_ClassANSI;
VSS7DLLAPI extern ITS_Class          itsNMS_ClassCCITT;
VSS7DLLAPI extern ITS_Class          itsADAX_ClassANSI;
VSS7DLLAPI extern ITS_Class          itsADAX_ClassCCITT;
VSS7DLLAPI extern ITS_Class          itsSBE_ClassANSI;
VSS7DLLAPI extern ITS_Class          itsSBE_ClassCCITT;

/*
 * these haven't been updated in a while.
 */
VSS7DLLAPI extern ITS_Class          itsDECSS7_Class;        /* FIXME: put rev here */
VSS7DLLAPI extern ITS_Class          itsDATAKINETICS_Class;
VSS7DLLAPI extern ITS_Class          itsEXCEL_Class;
VSS7DLLAPI extern ITS_Class          itsNEWNET_Class;
VSS7DLLAPI extern ITS_Class          itsTANDEM_Class;

/*
 * standalone class (no export needed)
 */
extern SS7STACK_Class   itsSS7STANDALONE_Class;

/*
 * Redunant stacks need to help the engine out a bit.  Specifically,
 * if they have special needs, that information needs to be passed
 * the the redundancy manager for input into the cluster join state
 * machine.
 *
 * This version is adequate for NMS; as we gain experience with other
 * redundant stacks, this may grow (or shrink) as needed.
 */

/*
 * the stack may have it's own idea of who is the master node.  Let
 * them influence the state machine accordingly.
 */
typedef enum
{
    SS7_UNKNOWN_STATE,
    SS7_PRIMARY_STATE,
    SS7_SECONDARY_STATE
}
SS7_VendorState;

/*
 * exit codes.  A total failure indicates that a complete stack
 * reset needs to happen.  A partial failure indicates that the
 * monitor should look elsewhere for the root cause of the stack
 * problem.
 */
#define SS7RM_PARTIAL_FAILURE   (-10)
#define SS7RM_TOTAL_FAILURE     (-20)

/*
 * A feature needs to be added to the configuration for the engine
 * when redundant configurations are or may be deployed.  This class
 * implements that feature.  Note that two are callins into the engine,
 * while the third is a callin to the stack.
 */
typedef void (*SS7RM_StateChange)(SS7_VendorState newState);
typedef void (*SS7RM_TermEventNotify)(int exitCode);

/*
 * class specific info.  Note that the engine will patch the latter
 * two methods, but the engine is expected to provide the former.
 */
typedef struct
{
    SS7RM_StateChange       stackToEngine;
    SS7RM_StateChange       engineToStack;
    SS7RM_TermEventNotify   termNotify;
}
SS7RM_ClassPart;

/*
 * the class record
 */
typedef struct
{
    ITS_CoreClassPart   coreClass;
    SS7RM_ClassPart     ss7RMClass;
}
SS7RM_ClassRec, *SS7RM_Class;

#define SS7RM_CLASS_STACK_TO_ENGINE_NOTIFY(x) \
    (((SS7RM_ClassRec *)(x))->ss7RMClass.stackToEngine)

#define SS7RM_CLASS_ENGINE_TO_STACK_NOTIFY(x) \
    (((SS7RM_ClassRec *)(x))->ss7RMClass.engineToStack)

#define SS7RM_CLASS_TERM_EVENT_NOTIFY(x) \
    (((SS7RM_ClassRec *)(x))->ss7RMClass.termNotify)

/*
 * this is the feature name that the engine will look for when
 * locating this class
 */
#define SS7RM_CLASS_NAME "SS7-RMClass"

/*
 * class records for known stacks.  This goes in the feature record.
 */
SS7DLLAPI extern ITS_Class itsNMSRM_Class;

#if defined(__cplusplus)
}
#endif

#endif /* ITS_SS7_TRANS_ONESHOT */

#if defined (USE_CPLUSPLUS)

#include <string>

#include <its_exception.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

/*.interface:SS7Transport
 *****************************************************************************
 *  Interface:
 *      SS7Transport
 *
 *  Purpose:
 *      The SS7Transport is simply a transport implemented via
 *      SS7 messaging.  It implements no additional functionality beyond
 *      that of the Transport class.  See:
 *      <A HREF=its_transport.html>Transport</A>
 *      for additional information.
 *
 *  Usage:
 *      See Transport for usage.
 *
 *      The resource file specifies a large number of initialization parameters
 *      for SS7.  The parameters are vendor specific, however; refer to the
 *      documentation for the SS7 vendor supplied with your implementation
 *      for details.
 *
 *****************************************************************************/
class SS7Transport : public Transport
{
public:
    /*.implementation:public,inline,SS7Transport
     ************************************************************************
     *  Purpose:
     *      This method creates an SS7 based transport.  The details of the
     *      transport implementation are vendor specific.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for many vendor specific variables,
     *      depending on the SS7 vendor used.
     *
     *  See Also:
     *      ~SS7Transport
     ************************************************************************/
    SS7Transport(const char *name,
                 ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (SS7TRAN_CreateTransport(const_cast<char *>(name),
                                      instance,
                                      mask));

        if (tc == NULL)
        {
            throw Error(ITS_EINVALIDARGS, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,SS7Transport
     ************************************************************************
     *  Purpose:
     *      This method creates an SS7 based transport.  The details of the
     *      transport implementation are vendor specific.
     *
     *  Input Parameters:
     *      name - the name of this transport
     *      instance - the instance id of this transport
     *      mask - transport modifiers for the base class
     *
     *  Notes:
     *      The resource file is consulted for many vendor specific variables,
     *      depending on the SS7 vendor used.
     *
     *  See Also:
     *      ~SS7Transport
     ************************************************************************/
    SS7Transport(const std::string& name,
                 ITS_USHORT instance, ITS_UINT mask)
       : Transport(NULL)
    {
        tc = reinterpret_cast<TRANSPORT_Control *>
             (SS7TRAN_CreateTransport(const_cast<char *>(name.c_str()),
                                      instance,
                                      mask));

        if (tc == NULL)
        {
            throw Error(ITS_EINVALIDARGS, __FILE__, __LINE__);
        }
    }
    /*.implementation:public,inline,SS7Transport
     ************************************************************************
     *  Purpose:
     *      This method destroys an SS7 transport.
     *
     *  See Also:
     *      SS7Transport()
     ************************************************************************/
    virtual ~SS7Transport()
    {
        if (tc)
        {
            SS7TRAN_DeleteTransport(reinterpret_cast<SS7TRAN_Manager *>(tc));
        }
    }

private:
    /* sorry, no copying */
    SS7Transport& operator=(Transport&) { return *this; }
};

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_SS7_TRANS_H */
