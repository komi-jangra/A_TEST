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
 *  ID: $Id: sccp.c,v 1.2 2008-02-22 03:55:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:25  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:53  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.4  2005/05/30 10:07:05  adutta
 * LOG: XUDT implementation in ANSI
 * LOG:
 * LOG: Revision 9.3  2005/05/26 10:19:47  adutta
 * LOG: Re-declaration of variable
 * LOG:
 * LOG: Revision 9.2  2005/05/25 06:24:47  adutta
 * LOG: XUD/LUDT implementation
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:22  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:50:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.10.2.6.4  2005/02/21 09:05:54  mmanikandan
 * LOG: PrintAddr commented for TTC is removed.
 * LOG:
 * LOG: Revision 7.5.10.2.6.3  2005/01/05 05:18:12  dsatish
 * LOG: Changes done for TTC compilation
 * LOG:
 * LOG: Revision 7.5.10.2.6.2  2004/12/17 03:34:49  randresol
 * LOG: Comment out Ppint function due to compilation errors
 * LOG:
 * LOG: Revision 7.5.10.2.6.1  2004/12/16 02:22:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.10.2  2004/09/21 06:58:24  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.5.10.1  2004/07/09 11:34:15  mmanikandan
 * LOG: Decoding of Variable Length Optional parameter is modified.
 * LOG:
 * LOG: Revision 7.5  2003/02/04 22:48:36  vnitin
 * LOG: Replacing SOCK_HToNS for Long unit data with byte shift operation
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.3  2003/01/06 22:27:42  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/10/01 15:42:23  yranade
 * LOG: Enable stack tracing
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/22 20:36:29  omayor
 * LOG: Point code offset for PRC is 3.
 * LOG:
 * LOG: Revision 6.2  2002/07/03 15:51:01  mmiers
 * LOG: Add china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:02  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.9  2002/01/02 20:57:52  mmiers
 * LOG: Get rid of the shortname conversion for the routing label.
 * LOG: It breaks hybrid stack building.
 * LOG:
 * LOG: Revision 5.8  2002/01/02 19:55:46  mmiers
 * LOG: Convert to long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.7  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.6  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.5  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.4  2001/10/04 21:30:10  mmiers
 * LOG: More bug fixing.
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/08/28 21:18:32  labuser
 * LOG: Add changes to SCCP codec (LUDT, LUDTS, DT1) to current.
 * LOG:
 * LOG: Revision 3.5.2.2  2001/08/28 15:06:11  labuser
 * LOG: removed left over from debuging codec modifications...
 * LOG:
 * LOG: Revision 3.5.2.1  2001/08/28 14:45:42  labuser
 * LOG: The encode function now computes the lenght of the message in a first pass,
 * LOG: then init the exact length in the ITS_EVENT, then copy the params in.
 * LOG: Also DT1 can now take LONG_DATA. Rule if data < 256 the user MUST use
 * LOG: DATA else MUST use LONG_DATA.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.4  2000/10/04 17:24:04  omayor
 * LOG: Added LUDT and LUDTS messages. The codec had to be modified as these
 * LOG: messages have 2 byte long pointers. For now they are handled as
 * LOG: a special case until we can change the structue of SCCP_IES to have
 * LOG: a 2 byte lenght and type.
 * LOG:
 * LOG: Revision 3.3  2000/09/01 20:56:29  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:32  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:06  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/03/18 21:03:27  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.2  2000/02/01 23:44:58  mmiers
 * LOG:
 * LOG:
 * LOG: Fix an encoding bug Fred found.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:40:30  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is very unforgiving.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:41  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.23  1999/08/30 15:53:29  mmiers
 * LOG:
 * LOG:
 * LOG: Essentially satisfies Hubert's objections to the OO model.
 * LOG:
 * LOG: Revision 1.22  1999/08/16 20:14:30  mmiers
 * LOG:
 * LOG:
 * LOG: Turn off tracing by default.
 * LOG:
 * LOG: Revision 1.21  1999/06/21 22:56:24  mmiers
 * LOG:
 * LOG:
 * LOG: Fix some GTT bugs in the C++.  Update the tests.
 * LOG:
 * LOG: Revision 1.20  1999/03/12 23:24:45  mmiers
 * LOG:
 * LOG:
 * LOG: Finish dual protocol family support.
 * LOG:
 * LOG: Revision 1.19  1998/12/16 16:35:06  rsonak
 * LOG: Bug fixes for trace, crash detection in sccp, remove extra console
 * LOG: print in DBC.
 * LOG:
 * LOG: Revision 1.18  1998/11/13 23:14:13  mmiers
 * LOG: Sanitize the NT build environment.
 * LOG:
 * LOG: Revision 1.17  1998/11/10 00:26:27  mmiers
 * LOG: Add ITU only parameter.
 * LOG:
 * LOG: Revision 1.16  1998/11/02 17:12:25  mmiers
 * LOG: Find routing label in all args, not just numOptionalArgs.
 * LOG:
 * LOG: Revision 1.15  1998/10/27 17:05:45  mmiers
 * LOG: Move some functions/signatures around so that we can share code.
 * LOG:
 * LOG: Revision 1.14  1998/09/26 22:37:12  mmiers
 * LOG: Convert to using message format descriptors.  ISUP needs something like
 * LOG: this as well, for many of the same reasons.
 * LOG:
 * LOG: Revision 1.13  1998/09/15 19:09:16  whu
 * LOG: Limit address encode/decode to one location for simplification.
 * LOG:
 * LOG: Revision 1.12  1998/06/18 16:44:59  mmiers
 * LOG: Forgot to add these.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:31  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.10  1998/06/01 22:31:59  mmiers
 * LOG: Raw documentation for SCCP.
 * LOG:
 * LOG: Revision 1.9  1998/05/14 20:41:43  mmiers
 * LOG: Update SCCP (read implement).  The rest are modifications to get
 * LOG: further the implementation of worker threads.
 * LOG:
 * LOG: Revision 1.8  1998/05/14 02:45:27  mmiers
 * LOG: More work on SCCP.  I think I have the encode done OK, still have to
 * LOG: write the decode.  The PTR table in SCCP messages is a bit of a bitch.
 * LOG: If we ever do the same for ISUP, the IEToEvent code could be reused.
 * LOG: That would give us (minus the ever important *PROCEDURES*) the requirement
 * LOG: of MTP3 and below ONLY.  However, ther are a *LOT* of procedures we
 * LOG: don't do (e.g., SST).
 * LOG:
 * LOG: Revision 1.7  1998/05/06 21:26:50  mmiers
 * LOG: Continue working on IS634 and SCCP.  Add C++ bindings for IS634
 * LOG: SCCP, and TCAP.
 * LOG:
 * LOG: Revision 1.6  1998/05/06 01:19:12  mmiers
 * LOG: Start writing encode for SCCP.
 * LOG:
 * LOG: Revision 1.5  1998/05/04 22:57:37  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.4  1998/05/01 14:22:14  mmiers
 * LOG: Clean up existing workspaces, add IS634 workspace.
 * LOG:
 * LOG: Revision 1.3  1998/05/01 14:04:21  mmiers
 * LOG: Update with interface routines.  Need to fill in checks for mandatory
 * LOG: parms, and call ifc routines.
 * LOG:
 * LOG: Revision 1.2  1998/04/07 15:51:54  mmiers
 * LOG: Update library to reflect vendor changes.
 * LOG:
 * LOG: Revision 1.1  1998/02/25 21:42:28  mmiers
 * LOG: Add in initial implementation of SCCP interface.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <its.h>
#include <its_license.h>
#include <its_trace.h>

#ident "$Id: sccp.c,v 1.2 2008-02-22 03:55:20 bsccs2 Exp $"

#if defined(ANSI)
#include <ansi/sccp.h>
#elif defined(CCITT)
#include <itu/sccp.h>
#elif defined(PRC)
#include <china/sccp.h>
#elif defined(TTC)
#include <japan/sccp.h>
#else
#error Protocol version not defined
#endif

/* #define LOCAL_DEBUG */

#if defined(ANSI)
#define SCCP_DT_MAX_SIZE       (261 + sizeof(ITS_OCTET)  +      \
                                      sizeof(ITS_CTXT) +        \
                                      sizeof(MTP3_HEADER_ANSI))
#elif defined(CCITT)
#define SCCP_DT_MAX_SIZE       (261 + sizeof(ITS_OCTET)  +      \
                                      sizeof(ITS_CTXT) +        \
                                      sizeof(MTP3_HEADER_CCITT))
#elif defined(PRC)
#define SCCP_DT_MAX_SIZE       (261 + sizeof(ITS_OCTET)  +      \
                                      sizeof(ITS_CTXT) +        \
                                      sizeof(MTP3_HEADER_PRC))
#elif defined(TTC)
#define SCCP_DT_MAX_SIZE       (261 + sizeof(ITS_OCTET)  +      \
                                      sizeof(ITS_CTXT) +        \
                                      sizeof(MTP3_HEADER_TTC))
#endif

/*
 * print header
 */
#define SCCP_PHDR   "-------------- SCCP ----------------\n"
#define CHECK_RETURN(r, cnt)    \
    if ((r) < 0)                \
    {                           \
        return (cnt);           \
    }                           \
    else                        \
    {                           \
        (cnt) += (r);           \
    }

/*
 * convert the called party address to SSN (function because we
 * may eventually do global title)
 */
SS7DLLAPI int
SCCP_DecodeAddr(const SCCP_ADDR *addr, ITS_OCTET* addrInd,
                ITS_UINT* pc, ITS_OCTET *ssn,
                ITS_OCTET* gttInfo, ITS_USHORT *gttLen)
{
    int offset = 1;

#if defined(CCITT)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SCCP))
    {
        return (ITS_ENOLICENSE);
    }  
#elif defined(ANSI)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(PRC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(TTC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#endif

    if (addr == NULL || addr->len == 0)
    {
        return (ITS_EMISSMAND);
    }

    if (addrInd)
    {
        *addrInd = addr->data[0];
    }

#if defined(ANSI)

    if (addr->data[0] & SCCP_CPA_HAS_SSN)
    {
        if (ssn)
        {
            *ssn = addr->data[offset];
        }

        offset++;
    }
    else if (ssn)
    {
        *ssn = SCCP_SSN_NONE;
    }

    if (addr->data[0] & SCCP_CPA_HAS_PC)
    {
        if (pc)
        {
            *pc = SCCP_ANSI_GET_PC(&addr->data[offset]);
        }
        offset += 3;
    }
    else if (pc)
    {
        *pc = 0;
    }

#elif defined(CCITT) 

    if (addr->data[0] & SCCP_CPA_HAS_PC)
    {
        if (pc)
        {
            *pc = SCCP_ITU_GET_PC(&addr->data[offset]);
        }
        offset += 2;
    }
    else if (pc)
    {
        *pc = 0;
    }

    if (addr->data[0] & SCCP_CPA_HAS_SSN)
    {
        if (ssn)
        {
            *ssn = addr->data[offset];
        }

        offset++;
    }
    else if (ssn)
    {
        *ssn = SCCP_SSN_NONE;
    }

#elif defined(PRC)

    if (addr->data[0] & SCCP_CPA_HAS_PC)
    {
        if (pc)
        {
            *pc = SCCP_PRC_GET_PC(&addr->data[offset]);
        }
        offset += 3;
    }
    else if (pc)
    {
        *pc = 0;
    }

    if (addr->data[0] & SCCP_CPA_HAS_SSN)
    {
        if (ssn)
        {
            *ssn = addr->data[offset];
        }

        offset++;
    }
    else if (ssn)
    {
        *ssn = SCCP_SSN_NONE;
    }

#elif defined(TTC) 

    if (addr->data[0] & SCCP_CPA_HAS_PC)
    {
        if (pc)
        {
            *pc = SCCP_TTC_GET_PC(&addr->data[offset]);
        }
        offset += 2;
    }
    else if (pc)
    {
        *pc = 0;
    }

    if (addr->data[0] & SCCP_CPA_HAS_SSN)
    {
        if (ssn)
        {
            *ssn = addr->data[offset];
        }

        offset++;
    }
    else if (ssn)
    {
        *ssn = SCCP_SSN_NONE;
    }


#endif

    if (gttLen)
    {
        *gttLen = 0;
    }

    if (gttInfo && addr->len > offset)
    {
        memcpy(gttInfo, &addr->data[offset], addr->len - offset);
        *gttLen = (ITS_USHORT)(addr->len - offset);
    }

    return (ITS_SUCCESS);
}

SS7DLLAPI int
SCCP_EncodeAddr(SCCP_ADDR *addr, ITS_OCTET addrInd,
                ITS_UINT pc, ITS_OCTET ssn,
                const ITS_OCTET* gttInfo, ITS_USHORT gttLen)
{
    int offset = 1;

#if defined(CCITT)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(ANSI)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(PRC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(TTC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#endif

    if (addr == NULL)
    {
        return (ITS_EMISSMAND);
    }

    addr->data[0] = addrInd;

#if defined(ANSI)

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        addr->data[offset] = ssn;
        offset++;
    }

    if (addrInd & SCCP_CPA_HAS_PC)
    {
        SCCP_ANSI_SET_PC(&addr->data[offset], pc);
        offset += 3;
    }

#elif defined(CCITT)

    if (addrInd & SCCP_CPA_HAS_PC)
    {
        SCCP_ITU_SET_PC(&addr->data[offset], pc);
        offset += 2;
    }

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        addr->data[offset] = ssn;
        offset++;
    }

#elif defined(PRC)

    if (addrInd & SCCP_CPA_HAS_PC)
    {
        SCCP_PRC_SET_PC(&addr->data[offset], pc);
        offset += 3;
    }

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        addr->data[offset] = ssn;
        offset++;
    }

#elif defined(TTC)

    if (addrInd & SCCP_CPA_HAS_PC)
    {
        SCCP_TTC_SET_PC(&addr->data[offset], pc);
        offset += 2;
    }

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        addr->data[offset] = ssn;
        offset++;
    }

#endif

    addr->len = (ITS_USHORT)offset;

    if (gttLen)
    {
        memcpy(&addr->data[offset], gttInfo, gttLen);
        addr->len += gttLen;
    }

    return (ITS_SUCCESS);
}

/*
 * compute the size of any fixed sized mandatory IE
 */
SS7DLLAPI int
SCCP_ComputeMSize(ITS_OCTET which)
{
    switch (which)
    {
    case SCCP_PRM_EOP:
        return (0);

    case SCCP_PRM_DEST_LOCAL_REF:
    case SCCP_PRM_SRC_LOCAL_REF:
        return sizeof(SCCP_REF_NUM);

    case SCCP_PRM_PROTOCOL_CLASS:
        return sizeof(SCCP_PROT_CLASS);

    case SCCP_PRM_REFUSAL_CAUSE:
        return sizeof(SCCP_REF_CAUSE);

    case SCCP_PRM_RELEASE_CAUSE:
        return sizeof(SCCP_REL_CAUSE);

    case SCCP_PRM_SEGMENT_REASSEM:
        return sizeof(SCCP_SEG_RES);

    case SCCP_PRM_SEQUENCE_SEGMENT:
        return sizeof(SCCP_SEQ_SEG);

    case SCCP_PRM_RCV_SEQ_NUM:
        return sizeof(SCCP_RSN);

    case SCCP_PRM_CREDIT:
        return sizeof(SCCP_CREDIT);

    case SCCP_PRM_HOP_COUNTER:
        return sizeof(SCCP_HOP_COUNT);

    case SCCP_PRM_RETURN_CAUSE:
        return sizeof(SCCP_RET_CAUSE);

    case SCCP_PRM_RESET_CAUSE:
        return sizeof(SCCP_RES_CAUSE);

    case SCCP_PRM_ERROR_CAUSE:
        return sizeof(SCCP_ERR_CAUSE);

    default:
        /*
         * leave this as an assertion.  It is indicative of a bad
         * message descriptor (we made a mistake), not a data error
         */
        assert(ITS_FALSE);
        return (ITS_EPROTERR);
    }
}

/*
 * return the message descriptor associated with a message type.
 */
SS7DLLAPI SCCP_MSG_DESC *
SCCP_GetDescriptor(ITS_OCTET which)
{
    switch (which)
    {
    case SCCP_MSG_CR:
        return (&SCCP_CR_Desc);

    case SCCP_MSG_CC:
        return (&SCCP_CC_Desc);

    case SCCP_MSG_CREF:
        return (&SCCP_CREF_Desc);

    case SCCP_MSG_RLSD:
        return (&SCCP_RLSD_Desc);

    case SCCP_MSG_RLC:
        return (&SCCP_RLC_Desc);

    case SCCP_MSG_DT1:
        return (&SCCP_DT1_Desc);

    case SCCP_MSG_DT2:
        return (&SCCP_DT2_Desc);

    case SCCP_MSG_AK:
        return (&SCCP_AK_Desc);

    case SCCP_MSG_UDT:
        return (&SCCP_UDT_Desc);

    case SCCP_MSG_XUDT:
        return (&SCCP_XUDT_Desc);

    case SCCP_MSG_UDTS:
        return (&SCCP_UDTS_Desc);

    case SCCP_MSG_XUDTS:
        return (&SCCP_XUDTS_Desc);

    case SCCP_MSG_ED:
        return (&SCCP_ED_Desc);

    case SCCP_MSG_EA:
        return (&SCCP_EA_Desc);

    case SCCP_MSG_RSR:
        return (&SCCP_RSR_Desc);

    case SCCP_MSG_RSC:
        return (&SCCP_RSC_Desc);

    case SCCP_MSG_ERR:
        return (&SCCP_ERR_Desc);

    case SCCP_MSG_IT:
        return (&SCCP_IT_Desc);

    default:
        return (NULL);
    }
}

/*
 * convert an array of IEs to an ITS_EVENT for (MTP3).  Note: as according to
 * the spec, the routing label is NOT part of the SCCP message.
 * margs contains an array of mandatory args, nmargs len
 * vargs contains an array of variable args, nvargs len
 * oargs contains an array of optional args, noargs len
 */
SS7DLLAPI int
SCCP_Encode(ITS_SCCP_IE *ies, int ieCount, ITS_OCTET msgType,
            ITS_EVENT *event, ITS_HDR *hdr, SCCP_MSG_DESC* desc)
{
    int i, j, offset, evoffset, lastVarOffset;
    ITS_SCCP_IE* ieRef[ITS_MAX_SCCP_IES];
    ITS_BOOLEAN haveOpts = ITS_FALSE, sawOpts = ITS_FALSE;
    int optPtr = 0;
    int ptrTableSize = 0;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
    ITS_OCTET *oargs = desc->oArgs;
    int noargs = desc->noArgs;
    MTP3_HEADER *mtp3 = NULL;

    int sccpMsgLen = sizeof(ITS_OCTET)  + 
                     sizeof(ITS_CTXT) + 
                     sizeof(MTP3_HEADER);

    assert(event != NULL);

#if defined(CCITT)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SCCP))
    {
        return (ITS_ENOLICENSE);
    } 
#elif defined(ANSI)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(PRC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(TTC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#endif

    /* sanity */
    if (ieCount > ITS_MAX_SCCP_IES)
    {
        return (ITS_EOVERFLOW);
    }

    /* start at zero */
    offset = 0;

    /* find the fixed mandatory */
    for (i = 0; i < nmargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the variable mandatory. Special case for DT1 a little ugly. */
    for (i = 0; i < nvargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if ((ies[j].param_id == vargs[i]) || 
                (ies[j].param_id == SCCP_PRM_LONG_DATA && msgType == SCCP_MSG_DT1))
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extras */
    while (offset < ieCount)
    {
        ieRef[offset] = NULL;
        offset++;
    }

    /* find the routing label, if present */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
        {
            mtp3 = &ies[i].param_data.routingLabel;
            break;
        }
    }


/*
 * ------- Begin first PASS we compute the msg length "sccpMsgLen" -------
 */

    /* 1 - fixed mandatory */
    for (i = 0; i < nmargs; i++)
    {
        sccpMsgLen += ieRef[i]->param_length;
    }

    /* do we have any optionals? */
    if (noargs > 0)
    {
        haveOpts = ITS_TRUE;  
    }

    /* 2 - size of the pointer table */
    if ((msgType == SCCP_MSG_LUDT) || (msgType == SCCP_MSG_LUDTS))
    {
        /* in this case the pointer sizes are 2 bytes !! */
        ptrTableSize = 2 * (nvargs + (haveOpts ? 1 : 0));
    }
    else
    {
        /* compute the size of the ptr table */
    	ptrTableSize = nvargs + (haveOpts ? 1 : 0);
    }

    sccpMsgLen = sccpMsgLen + ptrTableSize;

    /* variable mandatories */
    for (i = 0; i < nvargs; i++)
    {
        if (ieRef[nmargs + i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[nmargs + i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            sccpMsgLen += ieRef[nmargs + i]->param_data.calledPartyAddr.len + 1;
        }
        else if(ieRef[nmargs + i]->param_id == SCCP_PRM_LONG_DATA)
        {
            ITS_USHORT len = ieRef[nmargs + i]->param_data.longData.len;

            sccpMsgLen += len + 2;
        }
        else
        {
            sccpMsgLen += ieRef[nmargs + i]->param_length + 1;
        }
    }

    /* then optionals */
    for (i = nmargs + nvargs; i < ieCount; i++)
    {
        if (ieRef[i] == NULL)
        {
            continue;
        }

        sawOpts = ITS_TRUE;

        sccpMsgLen ++;  /* param Id */

        if (ieRef[i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            sccpMsgLen += ieRef[i]->param_data.calledPartyAddr.len + 1;
        }
        else if(ieRef[i]->param_id == SCCP_PRM_LONG_DATA)
        {
            ITS_USHORT len = ieRef[i]->param_data.longData.len;

            sccpMsgLen += len + 2;
        }
        else
        {
            sccpMsgLen += ieRef[i]->param_length + 1;
        }
    }

    /* finally end of optional parameters if any */
    if (noargs != 0)
    {
        sccpMsgLen++;
    }

/*
 * ------- End of first PASS we got the msg length -------
 */

    /* copy them in.  evoffset starts at msgtype + context */

    /* set the event source */
    ITS_EVENT_INIT(event, ITS_SCCP_SRC, (ITS_USHORT)sccpMsgLen);

    event->len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(MTP3_HEADER);

    /* set the message type */
    event->data[0] = msgType;
    /* context is either ssn or connref */
    evoffset = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(MTP3_HEADER);
    /* set the context */
    ITS_SET_CTXT(&event->data[1], hdr->context.conref);

    /* copy the routing label */
    if (mtp3 != NULL)
    {
        memcpy(&event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
               mtp3, sizeof(MTP3_HEADER));
    }
    else
    {
        memset(&event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
               0, sizeof(MTP3_HEADER));
    }

    /* copy in the mandatories */
    for (i = 0; i < nmargs; i++)
    {
        if (ieRef[i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            memcpy(&event->data[evoffset],
                   ieRef[i]->param_data.calledPartyAddr.data,
                   ieRef[i]->param_data.calledPartyAddr.len);
        }
        else
        {
            memcpy(&event->data[evoffset], &ieRef[i]->param_data,
                   ieRef[i]->param_length);
        }
        evoffset += ieRef[i]->param_length;
    }


    lastVarOffset = 0;

    /* special case for LUDT and LUDTS */
    if ((msgType == SCCP_MSG_LUDT) || (msgType == SCCP_MSG_LUDTS))
    {
        ITS_USHORT tmpPtr;

        /* build the ptr table for mandatory variable args */
        for (i = 0; i < nvargs; i++)
        {
            tmpPtr = (ITS_USHORT)(ptrTableSize + lastVarOffset - (2 * i) - 1);
            /* must be transmitted little Endian */
            event->data[evoffset] = (ITS_OCTET)(tmpPtr);
            evoffset++;
            event->data[evoffset] = (ITS_OCTET)(tmpPtr >> 8);
            if (ieRef[nmargs + i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
                 ieRef[nmargs + i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                lastVarOffset +=
                    ieRef[nmargs + i]->param_data.calledPartyAddr.len + 1;
            }
            else if(ieRef[nmargs + i]->param_id == SCCP_PRM_LONG_DATA)
            {
                lastVarOffset += 
                    ieRef[nmargs + i]->param_data.longData.len + 2;
            }
            else
            {
                lastVarOffset += ieRef[nmargs + i]->param_length + 1;
            }
            evoffset++;
        }

        /* if we have *any* optionals, build pointer to that */
        if (haveOpts)
        {
            tmpPtr = (ITS_USHORT)(ptrTableSize + lastVarOffset - (2 * i) - 1);
            optPtr = evoffset;
            /* must be transmitted little Endian */
            event->data[evoffset] = (ITS_OCTET)(tmpPtr);
            evoffset++;
            event->data[evoffset] = (ITS_OCTET)(tmpPtr >> 8);
            evoffset++;
        }
    }
    else
    {
        /* build the ptr table for mandatory variable args */
        for (i = 0; i < nvargs; i++)
        {
            event->data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
            if (ieRef[nmargs + i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
                 ieRef[nmargs + i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                lastVarOffset +=
                    ieRef[nmargs + i]->param_data.calledPartyAddr.len + 1;
            }
            else
            {
                lastVarOffset += ieRef[nmargs + i]->param_length + 1;
            }
            evoffset++;
        }

        /* if we have *any* optionals, build pointer to that */
        if (haveOpts)
        {
            event->data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
            optPtr = evoffset;
            evoffset++;
        }
    }

    /* copy in the variable mandatories */
    for (i = 0; i < nvargs; i++)
    {
        if (ieRef[nmargs + i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[nmargs + i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            /* Almost common with code below. */
            event->data[evoffset] =
                (ITS_OCTET)ieRef[nmargs + i]->param_data.calledPartyAddr.len;
            evoffset++;

            memcpy(&event->data[evoffset],
                   ieRef[nmargs + i]->param_data.calledPartyAddr.data,
                   ieRef[nmargs + i]->param_data.calledPartyAddr.len);

            evoffset += ieRef[nmargs + i]->param_data.calledPartyAddr.len;
        }
        else if(ieRef[nmargs + i]->param_id == SCCP_PRM_LONG_DATA)
        {
            ITS_USHORT len = ieRef[nmargs + i]->param_data.longData.len;

            /* the long unit data has a length param 2 bytes long
               so we have to treat it as a separate case */
            event->data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len >> 8);
            evoffset++;
            event->data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len & 0xFFU);
            evoffset++;
            memcpy(&event->data[evoffset],
                   ieRef[nmargs + i]->param_data.longData.data, len);
            evoffset += len;
        }
        else
        {
            event->data[evoffset] = ieRef[nmargs + i]->param_length;
            evoffset++;

            memcpy(&event->data[evoffset], &ieRef[nmargs + i]->param_data,
                   ieRef[nmargs + i]->param_length);

            evoffset += ieRef[nmargs + i]->param_length;
        }
    }

    /* copy in the optionals */
    for (i = nmargs + nvargs; i < ieCount; i++)
    {
        if (ieRef[i] == NULL)
        {
            continue;
        }

        sawOpts = ITS_TRUE;

        event->data[evoffset] = ieRef[i]->param_id;
        evoffset++;
        if (ieRef[i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            event->data[evoffset] =
                (ITS_OCTET)ieRef[i]->param_data.calledPartyAddr.len;
            evoffset++;

            memcpy(&event->data[evoffset],
                   &ieRef[i]->param_data.calledPartyAddr.data,
                   ieRef[i]->param_data.calledPartyAddr.len);

            evoffset += ieRef[i]->param_data.calledPartyAddr.len;
        }
        else if(ieRef[i]->param_id == SCCP_PRM_LONG_DATA)
        {
            ITS_USHORT len = ieRef[i]->param_data.longData.len;

            /* the long unit data has a length param 2 bytes long
               so we have to treat it as a separate case */
            event->data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len >> 8);
            evoffset++;
            event->data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len & 0xFFU);
            evoffset++;
            memcpy(&event->data[evoffset], 
                   ieRef[i]->param_data.longData.data, len);
            evoffset += len;
        }
        else
        {
            event->data[evoffset] = ieRef[i]->param_length;
            evoffset++;

            memcpy(&event->data[evoffset], &ieRef[i]->param_data,
                   ieRef[i]->param_length);

            evoffset += ieRef[i]->param_length;
        }
    }

    /* terminate variable list */
    if (noargs != 0)
    {
        event->data[evoffset] = SCCP_PRM_EOP;
        evoffset++;
    }

    /* set final length */
    event->len = (ITS_USHORT)evoffset;

    assert(sccpMsgLen == event->len);

    /* if no optional have been copied then the pointer must be set to 0 */
    if (haveOpts && !sawOpts)
    {
        event->data[optPtr] = 0;
        if ((msgType == SCCP_MSG_LUDT) || (msgType == SCCP_MSG_LUDTS))
        {
            event->data[optPtr + 1] = 0;
        }
    }

#if defined(LOCAL_DEBUG)
    {
        int q;

        ITS_TRACE_DEBUG(("SCCP_Encode DUMP:\n"));
        for (q = 0; q < event->len; q++)
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                      ("%02x ", event->data[q]));

            if (!((q+1) % 25))
            {
                TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                          ("\n"));
            }
        }
        if ((q+1) % 25)
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                      ("\n"));
        }
    }
#endif

    return (ITS_SUCCESS);
}

/*
 * Now go the other way.  Convert an event into an array of IEs
 */

/*****************************************************************************
 *  Purpose:
 *      This function Decodes SCCP event.
 *
 *  Input Parameters:
 *      ITS_EVENT *ev
 *      SCCP_MSG_DESC* desc 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_SCCP_IE *ies
 *      int *ieCount
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  ID::R0070 to R0130      Segmentation  Implementation
 *
 ****************************************************************************/
SS7DLLAPI int
SCCP_Decode(ITS_SCCP_IE *ies, int *ieCount, ITS_EVENT *ev,
            SCCP_MSG_DESC* desc)
{
    int evoffset = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) +
                   sizeof(MTP3_HEADER);
    ITS_OCTET *ptr;
    int i;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
#if 0 /* this is a placholder */
    ITS_OCTET *oargs = desc->oArgs;
#endif
    int noargs = desc->noArgs;
    ITS_OCTET msgType;

#if defined(CCITT)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_SCCP))
    {
        return (ITS_ENOLICENSE);
    } 
#elif defined(ANSI)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(PRC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(TTC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_SCCP))
    {
        return (ITS_ENOLICENSE);
    }
#endif

#if defined(LOCAL_DEBUG)
    {
        int q;

        ITS_TRACE_DEBUG(("SCCP_Decode DUMP:\n"));
        for (q = 0; q < ev->len; q++)
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                      ("%02x ", ev->data[q]));

            if (!((q+1) % 25))
            {
                TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                          ("\n"));
            }
        }

        if ((q+1) % 25)
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                      ("\n"));
        }
    }
#endif

    msgType = ev->data[0]; /* need to know the msg type in case it is LUDT(S) */

    /* copy the MTP3 header over */
    ies[0].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(MTP3_HEADER));

    /* avoid adding +1 everywhere */
    ies++;

    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        ies[i].param_id = margs[i];
        ies[i].param_length = (ITS_OCTET)SCCP_ComputeMSize(margs[i]);

        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            memcpy(&ies[i].param_data.calledPartyAddr.data,
                   &ev->data[evoffset], ies[i].param_length);
            ies[i].param_data.calledPartyAddr.len =
                ies[i].param_length;
        }
        else
        {
            memcpy(&ies[i].param_data.userData.data,
                   &ev->data[evoffset], ies[i].param_length);
        }

        evoffset += ies[i].param_length;
    }

    /* get the variable mandatories */
    ptr = &ev->data[evoffset];

    for (i = 0; i < nvargs; i++)
    {
        ITS_OCTET *tmp;

        ies[i + nmargs].param_id = vargs[i];

        if((msgType == SCCP_MSG_LUDT) || (msgType == SCCP_MSG_LUDTS))
        {
            ITS_USHORT pointer = 0;
            pointer |= (*(ptr + 1) << 8) + *ptr;
            tmp = ptr + pointer + 1;   /* +1 because we point to the byte before 
                                          see SCCP ITU Specs */
            if (ies[i + nmargs].param_id == SCCP_PRM_LONG_DATA)
            {
                ies[i + nmargs].param_data.longData.len =
                    (ITS_USHORT)((tmp[0] << 8) | tmp[1]);
                tmp += sizeof(ITS_USHORT);
            }
            else
            {
                ies[i + nmargs].param_length = *tmp;
                tmp++; /* to point to the param_data */
            }
            ptr += sizeof(ITS_USHORT);
        }
        else
        {
            /* compute the pointer */
            tmp = ptr + *ptr;

            /* special case for DT1, kind of ugly */

            if ((msgType == SCCP_MSG_DT1) && (ev->len > SCCP_DT_MAX_SIZE))
            {
                ies[i + nmargs].param_data.longData.len =
                    (ITS_USHORT)((tmp[0] << 8) | tmp[1]);

                tmp = tmp + 2;
            }
            else
            {
                ies[i + nmargs].param_length = *tmp;
                tmp++;
            }
            ptr++;
        }

        if (ies[i + nmargs].param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ies[i + nmargs].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            memcpy(&ies[i + nmargs].param_data.calledPartyAddr.data,
                   tmp, ies[i + nmargs].param_length);
            ies[i + nmargs].param_data.calledPartyAddr.len =
                ies[i + nmargs].param_length;
        }
        else if (ies[i + nmargs].param_id == SCCP_PRM_LONG_DATA)
        {
            memcpy(&ies[i + nmargs].param_data.longData.data, tmp,
                   ies[i + nmargs].param_data.longData.len);
        }
        else if ((msgType == SCCP_MSG_DT1) && (ev->len > SCCP_DT_MAX_SIZE))
        {

            ies[i + nmargs].param_id = SCCP_PRM_LONG_DATA;

            memcpy(&ies[i + nmargs].param_data.longData.data, tmp,
                   ies[i + nmargs].param_data.longData.len);
        }
        else
        {
            memcpy(&ies[i + nmargs].param_data.userData.data,
                   tmp, ies[i + nmargs].param_length);
        }
    }

    /* get the optionals, if any */
    i = 0;
    if (noargs && *ptr)
    {
        if((msgType == SCCP_MSG_LUDT) || (msgType == SCCP_MSG_LUDTS))
        {
            ITS_USHORT pointer = 0;
            pointer |= (*(ptr + 1) << 8) + *ptr;
            ptr = ptr + pointer + 1; /* +1 because we point to the byte before 
                                          see SCCP ITU Specs */
        }
        else
        {
            ptr += *ptr;
        }

        if ((ptr - ev->data) > ev->len)
        {
            return (ITS_EPROTERR);
        }

        while (*ptr != SCCP_PRM_EOP)
        {
            ies[i + nmargs + nvargs].param_id = *ptr;
            ptr++;
            ies[i + nmargs + nvargs].param_length = *ptr;
            ptr++;

            if (ies[i + nmargs + nvargs].param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
                ies[i + nmargs + nvargs].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                memcpy(&ies[i + nmargs + nvargs].param_data.calledPartyAddr.data,
                       ptr, ies[i + nmargs + nvargs].param_length);
                ies[i + nmargs + nvargs].param_data.calledPartyAddr.len =
                    ies[i + nmargs + nvargs].param_length;
            }
            else
            {
                memcpy(&ies[i + nmargs + nvargs].param_data.userData.data,
                       ptr, ies[i + nmargs + nvargs].param_length);
            }

            ptr += ies[i + nmargs + nvargs].param_length;
            i++;

            if ((ptr - ev->data) > ev->len)
            {
                return (ITS_EPROTERR);
            }
        }
    }

    /* set the return ieCount.  The '1' is for the MTP3 header */
    *ieCount = nmargs + nvargs + i + 1;

    return (ITS_SUCCESS);
}

/*
 * convert an array of IEs to a ITS_OCTET buf for MTP3.
 */

/*****************************************************************************
 *  Purpose:
 *      This function Encodes the SCCP data.
 *
 *  Input Parameters:
 *      ITS_SCCP_IE *ies
 *      int *ieCount
 *      SCCP_MSG_DESC* desc 
 *      ITS_OCTET mType 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_OCTET* data      
 *
 *  Return Value:
 *      If the Encode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  ID::R0220-R0250         LUDT/LUDTS Implementation
 *
 ****************************************************************************/
int
SCCP_EncodeMTP3(ITS_OCTET* data, ITS_USHORT* len, ITS_OCTET mType,
                ITS_SCCP_IE *ies, int ieCount, SCCP_MSG_DESC* desc)
{
    int i, j, offset, evoffset, lastVarOffset = 0;
    ITS_SCCP_IE* ieRef[ITS_MAX_SCCP_IES];
    ITS_BOOLEAN haveOpts = ITS_FALSE, sawOpts = ITS_FALSE;
    int optPtr = 0;
    int ptrTableSize = 0;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
    ITS_OCTET *oargs = desc->oArgs;
    int noargs = desc->noArgs;
    ITS_USHORT tmpPtr;
#if defined(LOCAL_DEBUG)
    int q;
#endif

    ITS_TRACE_DEBUG(("SCCP_EncodeMTP3:\n"));

    /* sanity */
    *len = 0;
    if (ieCount > ITS_MAX_SCCP_IES)
    {
        return (ITS_EOVERFLOW);
    }

    /* start at zero */
    offset = 0;

    /* find the fixed mandatory */
    for (i = 0; i < nmargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            ITS_TRACE_ERROR(("SCCP_Encode: Mandatory fixed parameter missing.\n"));

            return (ITS_EMISSMAND);
        }
    }

    /* find the variable mandatory */
    for (i = 0; i < nvargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == vargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            ITS_TRACE_ERROR(("SCCP_Encode: Mandatory var parameter missing.\n"));

            return (ITS_EMISSMAND);
        }
    }

    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extra params */
    while (offset < ieCount)
    {
        ieRef[offset] = NULL;
        offset++;
    }

    /* set the SCCP message type */
    data[0] = mType;

    evoffset = sizeof(ITS_OCTET);

    /* copy in the mandatories */
    for (i = 0; i < nmargs; i++)
    {
        if (ieRef[i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            memcpy(&data[evoffset],
                   ieRef[i]->param_data.calledPartyAddr.data,
                   ieRef[i]->param_data.calledPartyAddr.len);
        }
        else
        {
            memcpy(&data[evoffset], &ieRef[i]->param_data,
                   ieRef[i]->param_length);
        }
        evoffset += ieRef[i]->param_length;
    }

    /* do we have any optionals? */
    if (noargs > 0)
    {
        haveOpts = ITS_TRUE;
    }

    /* compute the size of the ptr table */

    if ((mType == SCCP_MSG_LUDT) || (mType == SCCP_MSG_LUDTS))
    {
        /* in this case the pointer sizes are 2 bytes !! */
        ptrTableSize = 2 * (nvargs + (haveOpts ? 1 : 0));
    }
    else
    {
        /* compute the size of the ptr table */
        ptrTableSize = nvargs + (haveOpts ? 1 : 0);
    }

    /* build the ptr table for mandatory variable args */
    if ((mType == SCCP_MSG_LUDT) || (mType == SCCP_MSG_LUDTS))
    {
        /* build the ptr table for mandatory variable args */
        for (i = 0; i < nvargs; i++)
        {
            tmpPtr = (ITS_USHORT)(ptrTableSize + lastVarOffset - (2 * i) -1 );
            /* must be transmitted little Endian */
            data[evoffset] = (ITS_OCTET)(tmpPtr);
            evoffset++;
            data[evoffset] = (ITS_OCTET)(tmpPtr >> 8);

            if (ieRef[nmargs + i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
                 ieRef[nmargs + i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                lastVarOffset +=
                    ieRef[nmargs + i]->param_data.calledPartyAddr.len + 1;
            }
            else if(ieRef[nmargs + i]->param_id == SCCP_PRM_LONG_DATA)
            {
                lastVarOffset += 
                    ieRef[nmargs + i]->param_data.longData.len + 2;
            }
            else
            {
                lastVarOffset += ieRef[nmargs + i]->param_length + 1;
            }
            evoffset++;
        }

        /* if we have *any* optionals, build pointer to that */
        if (haveOpts)
        {
            tmpPtr = (ITS_USHORT)(ptrTableSize + lastVarOffset - (2 * i) -1 );
            optPtr = evoffset;
            /* must be transmitted little Endian */
            data[evoffset] = (ITS_OCTET)(tmpPtr);
            evoffset++;
            data[evoffset] = (ITS_OCTET)(tmpPtr >> 8);
            evoffset++;
        }
    }
    else
    {
        for (i = 0; i < nvargs; i++)
        {
            data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
            if (ieRef[nmargs + i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
                ieRef[nmargs + i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                lastVarOffset +=
                    ieRef[nmargs + i]->param_data.calledPartyAddr.len + 1;
            }
            else
            {
                lastVarOffset += ieRef[nmargs + i]->param_length + 1;
            }
            evoffset++;
        }

        /* if we have *any* optionals, build pointer to that */
        if (haveOpts)
        {
            data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
            optPtr = evoffset;
            evoffset++;
        }
    }

    /* copy in the variable mandatories */
    for (i = 0; i < nvargs; i++)
    {
        if (ieRef[nmargs + i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[nmargs + i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            /* Almost common with code below. */
            data[evoffset] =
                (ITS_OCTET)ieRef[nmargs + i]->param_data.calledPartyAddr.len;
            evoffset++;

            memcpy(&data[evoffset],
                   ieRef[nmargs + i]->param_data.calledPartyAddr.data,
                   ieRef[nmargs + i]->param_data.calledPartyAddr.len);

            evoffset += ieRef[nmargs + i]->param_data.calledPartyAddr.len;
        }
        else if(ieRef[nmargs + i]->param_id == SCCP_PRM_LONG_DATA)
        {
            ITS_USHORT len = ieRef[nmargs + i]->param_data.longData.len;

            /* the long unit data has a length param 2 bytes long
               so we have to treat it as a separate case */
            data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len >> 8);
            evoffset++;
            data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len & 0xFFU);
            evoffset++;
            memcpy(&data[evoffset],
                   ieRef[nmargs + i]->param_data.longData.data, len);
            evoffset += len;
        }
        else
        {
            data[evoffset] = ieRef[nmargs + i]->param_length;
            evoffset++;

            memcpy(&data[evoffset], &ieRef[nmargs + i]->param_data,
                   ieRef[nmargs + i]->param_length);

            evoffset += ieRef[nmargs + i]->param_length;
        }
    }

    /* copy in the optionals */
    for (i = nmargs + nvargs; i < ieCount; i++)
    {
        if (ieRef[i] == NULL)
        {
            continue;
        }

        sawOpts = ITS_TRUE;

        data[evoffset] = ieRef[i]->param_id;
        evoffset++;
        if (ieRef[i]->param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ieRef[i]->param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            data[evoffset] =
                (ITS_OCTET)ieRef[i]->param_data.calledPartyAddr.len;
            evoffset++;

            memcpy(&data[evoffset],
                   &ieRef[i]->param_data.calledPartyAddr.data,
                   ieRef[i]->param_data.calledPartyAddr.len);

            evoffset += ieRef[i]->param_data.calledPartyAddr.len;
        }
        else if(ieRef[i]->param_id == SCCP_PRM_LONG_DATA)
        {
            ITS_USHORT len = ieRef[i]->param_data.longData.len;

            /* the long unit data has a length param 2 bytes long
               so we have to treat it as a separate case */
            data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len >> 8);
            evoffset++;
            data[evoffset] =
                (ITS_OCTET)(ieRef[nmargs + i]->param_data.longData.len & 0xFFU);
            evoffset++;
            memcpy(&data[evoffset], 
                   ieRef[i]->param_data.longData.data, len);
            evoffset += len;
        }
        else
        {
            data[evoffset] = ieRef[i]->param_length;
            evoffset++;

            memcpy(&data[evoffset], &ieRef[i]->param_data,
                   ieRef[i]->param_length);

            evoffset += ieRef[i]->param_length;
        }
    }

    /* terminate variable list */
    if (noargs != 0)
    {
        data[evoffset] = SCCP_PRM_EOP;
        evoffset++;
    }

    /* set final length */
    *len = (ITS_USHORT)evoffset;

    /* if no optional have been copied then the pointer must be set to 0 */
    if (haveOpts && !sawOpts)
    {
        data[optPtr] = 0;
        if ((mType == SCCP_MSG_LUDT) || (mType == SCCP_MSG_LUDTS))
        {
            data[optPtr + 1] = 0;
        }
    }

#if defined(LOCAL_DEBUG)
    ITS_TRACE_DEBUG(("SCCP->MTP3 DUMP:\n"));
    for (q = 0; q < *len; q++)
    {
        TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                  ("%02x ", data[q]));

        if (!((q+1) % 25))
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG, ("\n"));
        }
    }
    if ((q+1) % 25)
    {
        TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG, ("\n"));
    }
#endif

    return (ITS_SUCCESS);
}

/*
 * Now go the other way.  Convert an event into an array of IEs
 */
/*****************************************************************************
 *  Purpose:
 *      This function Decodes the data received from MTP3.
 *
 *  Input Parameters:
 *      ITS_OCTET* data
 *      SCCP_MSG_DESC* desc
 *      ITS_OCTET mType
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_SCCP_IE *ies
 *      int *ieCount
 *
 *  Return Value:
 *      If the decode is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  ID::R0070 to R0130      LUDT/LUDTS Implementation
 *
 ****************************************************************************/
int
SCCP_DecodeMTP3(ITS_OCTET *data, ITS_USHORT len, ITS_OCTET* mType,
                ITS_SCCP_IE *ies, int *ieCount, SCCP_MSG_DESC* desc)
{
    int evoffset = sizeof(ITS_OCTET);
    int i;
    ITS_OCTET *ptr;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
    int noargs = desc->noArgs;
#if defined(LOCAL_DEBUG)
    int q;
#endif

    ITS_TRACE_DEBUG(("SCCP_Decode:\n"));

#if defined(LOCAL_DEBUG)
    ITS_TRACE_DEBUG(("MTP3->SCCP DUMP:\n"));
    for (q = 0; q < len; q++)
    {
        TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                  ("%02x ", data[q]));

        if (!((q+1) % 25))
        {
            TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG, ("\n"));
        }
    }

    if ((q+1) % 25)
    {
        TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG, ("\n"));
    }
#endif

    /* message type, need to know the msg type in case it is LUDT(S) */
    *mType = data[0];

    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        ies[i].param_id = margs[i];
        ies[i].param_length = (ITS_OCTET)SCCP_ComputeMSize(margs[i]);

        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            memcpy(&ies[i].param_data.calledPartyAddr.data,
                   &data[evoffset], ies[i].param_length);
            ies[i].param_data.calledPartyAddr.len =
                ies[i].param_length;
        }
        else
        {
            memcpy(&ies[i].param_data.userData.data,
                   &data[evoffset], ies[i].param_length);
        }

        evoffset += ies[i].param_length;
    }

    /* get the variable mandatories */
    ptr = &data[evoffset];

    for (i = 0; i < nvargs; i++)
    {
        ITS_OCTET *tmp;

        ies[i + nmargs].param_id = vargs[i];

        if((*mType == SCCP_MSG_LUDT) || (*mType == SCCP_MSG_LUDTS))
        {
            ITS_USHORT pointer = 0;
            pointer |= (*(ptr + 1) << 8) + *ptr;
            tmp = ptr + pointer + 1;   /* +1 because we point to the byte before
                                          see SCCP ITU Specs */
            if (ies[i + nmargs].param_id == SCCP_PRM_LONG_DATA)
            {
                ies[i + nmargs].param_data.longData.len =
                    (ITS_USHORT)((tmp[0] << 8) | tmp[1]);
                tmp += sizeof(ITS_USHORT);
            }
            else
            {
                ies[i + nmargs].param_length = *tmp;
                tmp++; /* to point to the param_data */
            }
            ptr += sizeof(ITS_USHORT);
        }
        else
        {
            /* compute the pointer */
            tmp = ptr + *ptr;
            ies[i + nmargs].param_length = *tmp;

            tmp++;
            ptr++;
        }

        if (ies[i + nmargs].param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
            ies[i + nmargs].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            memcpy(&ies[i + nmargs].param_data.calledPartyAddr.data,
                   tmp, ies[i + nmargs].param_length);
            ies[i + nmargs].param_data.calledPartyAddr.len =
                ies[i + nmargs].param_length;
        }
        else if (ies[i + nmargs].param_id == SCCP_PRM_LONG_DATA)
        {
            memcpy(&ies[i + nmargs].param_data.longData.data, tmp,
                   ies[i + nmargs].param_data.longData.len);
        }
        else
        {
            memcpy(&ies[i + nmargs].param_data.userData.data,
                   tmp, ies[i + nmargs].param_length);
        }
    }

    /* get the optionals, if any */
    i = 0;
    if (noargs && *ptr)
    {
        if((*mType == SCCP_MSG_LUDT) || (*mType == SCCP_MSG_LUDTS))
        {
            ITS_USHORT pointer = 0;
            pointer |= (*(ptr + 1) << 8) + *ptr;
            ptr = ptr + pointer + 1; /* +1 because we point to the byte before
                                          see SCCP ITU Specs */
        }
        else
        {
            ptr += *ptr;
        }

        if ((ptr - data) > len)
        {
            return (ITS_EPROTERR);
        }

        while ((*ptr != SCCP_PRM_EOP) && ((ptr - data) < len))
        {
            ies[i + nmargs + nvargs].param_id = *ptr;
            ptr++;
            ies[i + nmargs + nvargs].param_length = *ptr;
            ptr++;

            if (ies[i + nmargs + nvargs].param_id == SCCP_PRM_CALLED_PARTY_ADDR ||
                ies[i + nmargs + nvargs].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                memcpy(&ies[i + nmargs + nvargs].param_data.calledPartyAddr.data,
                       ptr, ies[i + nmargs + nvargs].param_length);
                ies[i + nmargs + nvargs].param_data.calledPartyAddr.len =
                    ies[i + nmargs + nvargs].param_length;
            }
            else
            {
                memcpy(&ies[i + nmargs + nvargs].param_data.userData.data,
                       ptr, ies[i + nmargs + nvargs].param_length);
            }

            ptr += ies[i + nmargs + nvargs].param_length;
            i++;

            if ((ptr - data) > len)
            {
                return (ITS_EPROTERR);
            }
        }
    }

    /* set the return ieCount */
    *ieCount = nmargs + nvargs + i;

    return (ITS_SUCCESS);
}

/*
 * print strings
 */
static char *msgNames[] =
{
    "(unknown)",
    "CR",
    "CC",
    "CREF",
    "RLSD",
    "RLC",
    "DT1",
    "DT2",
    "AK",
    "UDT",
    "UDTS",
    "ED",
    "EA",
    "RSR",
    "RSC",
    "ERR",
    "IT",
    "XUDT",
    "XUDTS",
    "LUDT",
    "LUDTS"
};

static char *ieNames[] =
{
    "EOP",
    "DEST_LOCAL_REF",
    "SRC_LOCAL_REF",
    "CALLED_PARTY_ADDR",
    "CALLING_PARTY_ADDR",
    "PROTOCOL_CLASS",
    "SEGMENT_REASSEM",
    "RCV_SEQ_NUM",
    "SEQUENCE_SEGMENT",
    "CREDIT",
    "RELEASE_CAUSE",
    "RETURN_CAUSE",
    "RESET_CAUSE",
    "ERROR_CAUSE",
    "REFUSAL_CAUSE",
    "DATA",
    "SEGMENTATION",
    "HOP_COUNTER",
    "IMPORTANCE",
    "LONG_DATA"
};

static char *releaseStrings[] =
{
    "END_USER_ORG",
    "END_USER_BUSY",
    "END_USER_FAIL",
    "SCCP_ORG",
    "RPC_ERROR",
    "INCONSISTENT_DATA",
    "ACCESS_FAIL",
    "ACCESS_CONG",
    "SUBSYS_FAIL",
    "SUBSYS_CONG",
    "NETWORK_FAIL",
    "NETWORK_CONG",
    "RESET_EXPIRY",
    "INACT_EXPIRY",
    "NOT_OBTAINABLE",
    "UNQUAL"
};

static char *returnStrings[] =
{
    "NO_TRANS_ADDR_NAT",
    "NO_TRANS_THIS_ADDR",
    "SUBSYS_CONG",
    "SUBSYS_FAIL",
    "UNEQUIPPED_USER",
    "NETWORK_FAIL",
    "NETWORK_CONG",
    "UNQUAL",
    "HOP_COUNT_EXCEEDED",
    "ERR_IN_TRANSPORT",
    "ERR_IN_LOCAL_PROCESS"
};

static char *resetStrings[] =
{
    "END_USER_ORG",
    "SCCP_ORG",
    "OUT_OF_ORDER_S",
    "OUT_OF_ORDER_R",
    "RPC_OUT_WINDOW",
    "RPC_PS_AFTER_INIT",
    "RPC_GENERAL",
    "NETWORK_OP",
    "ACCESS_OP",
    "NETWORK_CONG",
    "NOT_OBTAINABLE",
    "UNQUAL"
};

static char *errorStrings[] =
{
    "LRN_MISS_DRN",
    "BAD_LRN",
    "PC_MISMATCH",
    "SCLASS_MIS",
    "UNQUAL"
};

static char *refusalStrings[] =
{
    "END_USER_ORG",
    "END_USER_CONG",
    "END_USER_FAIL",
    "SCCP_ORG",
    "DEST_UKNOWN",
    "DEST_UNAVAIL",
    "QOS_NEVER_AVAIL",
    "QOS_UNAVAIL_NOW",
    "ACCESS_FAIL",
    "ACCESS_CONG",
    "SUBSYS_FAIL",
    "SUBSYS_CONG",
    "CONN_EXPIRY",
    "BAD_USER_DATA",
    "NOT_OBTAINABLE",
    "UNQUAL"
};

static char *gttStrings[] =
{
#if defined(CCITT) || defined(PRC) || defined(TTC)
    "none",
    "NATURE",
    "TRANS",
    "TNE",
    "ALL"
#elif defined(ANSI)
    "none",
    "TNE",
    "TRANS_ANSI"
#endif
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function pretty prints an SCCP address.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrintAddr(RINGBUF_Manager *rb, ITS_UINT *bCount,
           const char *addrName, ITS_SCCP_IE *ie)
{
    int tmp, ret = 0;

    ITS_OCTET ai, ssn, gttInfo[SCCP_MAX_ADDR_LEN];
    ITS_USHORT gttLen, i;
    ITS_UINT pc;
    MTP3_POINT_CODE pcode;

    ret = SCCP_DecodeAddr(&ie->param_data.calledPartyAddr,
                          &ai, &pc, &ssn, gttInfo, &gttLen);

    if (ret != ITS_SUCCESS)
    {
        return (-1);
    }

    /* address indicator */
    tmp = PPrint(rb, " %3d.  %02x %b|%b|%04b|%b|%b ",
                 *bCount, ai,
                 (ai >> 7) & 1,
                 (ai >> 6) & 1,
                 (ai >> 2) & 0x0FU,
                 (ai >> 1) & 1,
                 ai & 1);
    CHECK_RETURN(tmp, ret);
    tmp = PPrint(rb, "Route: %s Route by: %s GTT mask: %s Has PC: %s Has SSN: %s\n",
                 ((ai >> 7) & 1) ? "NAT" : "INT",
                 ((ai >> 6) & 1) ? "SSN" : "GTT",
#if defined(CCITT) || defined(PRC) || defined(TTC)
                 ((ai & SCCP_CPA_GTTI_MASK) <= SCCP_CPA_GTTI_ALL)
                    ? gttStrings[(ai & SCCP_CPA_GTTI_MASK) >> 2]
                    : "unknown",
                 (ai & SCCP_CPA_HAS_PC_CCITT)
                    ? "yes"
                    : "no",
                 (ai & SCCP_CPA_HAS_SSN_CCITT)
                    ? "yes"
                    : "no");
#elif defined(ANSI)
                 ((ai & SCCP_CPA_GTTI_MASK) <= SCCP_CPA_GTTI_TRANS_ANSI)
                    ? gttStrings[(ai & SCCP_CPA_GTTI_MASK) >> 2]
                    : "unknown",
                 (ai & SCCP_CPA_HAS_PC_ANSI)
                    ? "yes"
                    : "no",
                 (ai & SCCP_CPA_HAS_SSN_ANSI)
                    ? "yes"
                    : "no");
#endif
    (*bCount)++;

/*
 * SSN and Point Code.  ITU and PRC have a different order than ANSI
 */
#if defined(CCITT) || defined(PRC)

    /* point code */
    if (ai & SCCP_CPA_HAS_PC_CCITT)
    {
#if defined(CCITT)
        /* first byte */
        SCCP_ITU_SET_PC(pcode.data, pc);
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "PC = %d-%d-%d\n",
                     *bCount, pcode.data[0],
                     pcode.data[0],
                     MTP3_PC_GET_NETWORK_CCITT(pcode),
                     MTP3_PC_GET_CLUSTER_CCITT(pcode),
                     MTP3_PC_GET_MEMBER_CCITT(pcode));
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* second byte */
        tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  spare/PC hi : PC Value 0x%04x\n",
                     *bCount, pcode.data[1],
                     pcode.data[1] & MTP3_RL_DPC_HI_MASK_CCITT,
                     (pcode.data[1] & MTP3_RL_OPC_LOW_MASK_CCITT) >> 6,
                     pc);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
#elif defined(PRC)
        SCCP_PRC_SET_PC(pcode.data, pc);
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "(member) DPC = %d-%d-%d : 0x%06x\n",
                     *bCount, pcode.data[0],
                     pcode.data[0],
                     MTP3_PC_GET_NETWORK_PRC(pcode),
                     MTP3_PC_GET_CLUSTER_PRC(pcode),
                     MTP3_PC_GET_MEMBER_PRC(pcode),
                     pc);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* cluster */
        tmp = PPrint(rb, " %3d.  %02x    %08b  (cluster)\n",
                     *bCount, pcode.data[1],
                     pcode.data[1]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* network */
        tmp = PPrint(rb, " %3d.  %02x    %08b  (network)\n",
                     *bCount, pcode.data[2],
                     pcode.data[2]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
#endif
    }

    /* SSN */
    if (ai & SCCP_CPA_HAS_SSN_CCITT)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  SSN = %d\n",
                     *bCount, ssn,
                     ssn, ssn);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
    }

/*
 * Now do ANSI's ordering
 */
#elif defined(ANSI)

    /* SSN */
    if (ai & SCCP_CPA_HAS_SSN_ANSI)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  SSN = %d\n",
                     *bCount, ssn,
                     ssn, ssn);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
    }

    /* point code */
    if (ai & SCCP_CPA_HAS_PC_ANSI)
    {
        SCCP_ANSI_SET_PC(pcode.data, pc);
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "(member) DPC = %d-%d-%d : 0x%06x\n",
                     *bCount, pcode.data[0],
                     pcode.data[0],
                     MTP3_PC_GET_NETWORK_ANSI(pcode),
                     MTP3_PC_GET_CLUSTER_ANSI(pcode),
                     MTP3_PC_GET_MEMBER_ANSI(pcode),
                     pc);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* cluster */
        tmp = PPrint(rb, " %3d.  %02x    %08b  (cluster)\n",
                     *bCount, pcode.data[1],
                     pcode.data[1]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* network */
        tmp = PPrint(rb, " %3d.  %02x    %08b  (network)\n",
                     *bCount, pcode.data[2],
                     pcode.data[2]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
    }

#endif

    /* global title */
    for (i = 0; i < gttLen; i++)
    {
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "GTT[%u] = 0x%02x\n",
                     *bCount, gttInfo[i],
                     gttInfo[i],
                     i,
                     gttInfo[i]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function pretty prints an SCCP IE.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PPrint_IE(RINGBUF_Manager *rb, ITS_UINT *bCount,
          ITS_SCCP_IE *ie, ITS_BOOLEAN printUserData)
{
    int tmp, ret = 0;
    ITS_UINT val;
    ITS_USHORT i;

    switch (ie->param_id)
    {
    case SCCP_PRM_EOP:
        /* nothing to do for this */
        break;

    case SCCP_PRM_DEST_LOCAL_REF:
        val = RN_GET_REF_NUM(ie->param_data.destinationLocalReference);
        /* byte  0 */
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Value = %d\n",
                     *bCount, ie->param_data.destinationLocalReference.refno[0],
                     ie->param_data.destinationLocalReference.refno[0],
                     val);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* byte  1 */
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, ie->param_data.destinationLocalReference.refno[1],
                     ie->param_data.destinationLocalReference.refno[1]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* byte  2 */
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, ie->param_data.destinationLocalReference.refno[2],
                     ie->param_data.destinationLocalReference.refno[2]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_SRC_LOCAL_REF:
        val = RN_GET_REF_NUM(ie->param_data.sourceLocalReference);
        /* byte  0 */
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Value = %d\n",
                     *bCount, ie->param_data.sourceLocalReference.refno[0],
                     ie->param_data.sourceLocalReference.refno[0],
                     val);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* byte  1 */
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, ie->param_data.sourceLocalReference.refno[1],
                     ie->param_data.sourceLocalReference.refno[1]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* byte  2 */
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, ie->param_data.sourceLocalReference.refno[2],
                     ie->param_data.sourceLocalReference.refno[2]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_CALLED_PARTY_ADDR:
        PPrintAddr(rb, bCount, "Called Party Address", ie);
        break;

    case SCCP_PRM_CALLING_PARTY_ADDR:
        PPrintAddr(rb, bCount, "Calling Party Address", ie);
        break;

    case SCCP_PRM_PROTOCOL_CLASS:
        /* byte  0 */
        tmp = PPrint(rb, " %3d.  %02x   %1b|%07b  "
                         "Return option = %d, Protocol class = %d\n",
                     *bCount, ie->param_data.protocolClass.pclass,
                     ie->param_data.protocolClass.pclass >> 7,
                     ie->param_data.protocolClass.pclass & 0x7FU,
                     ie->param_data.protocolClass.pclass & SCCP_PCLASS_RET_ON_ERR
                        ? 1
                        : 0,
                     ie->param_data.protocolClass.pclass & SCCP_PCLASS_MASK);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_SEGMENT_REASSEM:
        tmp = PPrint(rb, " %3d.  %02x   %07b|%b  "
                         "Spare = %d, More data = %s\n",
                     *bCount,ie->param_data.segmentingReassembly.seg_res,
                     ie->param_data.segmentingReassembly.seg_res >> 1,
                     ie->param_data.segmentingReassembly.seg_res & 1,
                     ie->param_data.segmentingReassembly.seg_res >> 1,
                     ie->param_data.segmentingReassembly.seg_res & 1
                        ? "yes"
                        : "no");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_RCV_SEQ_NUM:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Receive sequence number = %d\n",
                     *bCount, ie->param_data.receivedSequenceNumber.rsn,
                     ie->param_data.receivedSequenceNumber.rsn,
                     ie->param_data.receivedSequenceNumber.rsn);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_SEQUENCE_SEGMENT:
        /* TSN */
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Transmit sequence number = %d\n",
                     *bCount, ie->param_data.sequenceSegment.tsn,
                     ie->param_data.sequenceSegment.tsn,
                     ie->param_data.sequenceSegment.tsn);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* RSN */
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Receive sequence number = %d\n",
                     *bCount, ie->param_data.sequenceSegment.rsn,
                     ie->param_data.sequenceSegment.rsn,
                     ie->param_data.sequenceSegment.rsn);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_CREDIT:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Credit = %d\n",
                     *bCount, ie->param_data.credit.win_size,
                     ie->param_data.credit.win_size,
                     ie->param_data.credit.win_size);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_RELEASE_CAUSE:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Release cause = %s\n",
                     *bCount, ie->param_data.releaseCause.cause,
                     ie->param_data.releaseCause.cause,
                     ie->param_data.releaseCause.cause <= SCCP_RLC_UNQUAL
                        ? releaseStrings[ie->param_data.releaseCause.cause]
                        : "unknown");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_RETURN_CAUSE:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Return cause = %s\n",
                     *bCount, ie->param_data.returnCause.cause,
                     ie->param_data.returnCause.cause,
                     ie->param_data.returnCause.cause <= SCCP_RET_ERR_IN_LOCAL_PROCESS
                        ? returnStrings[ie->param_data.returnCause.cause]
                        : "unknown");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_RESET_CAUSE:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Reset cause = %s\n",
                     *bCount, ie->param_data.resetCause.cause,
                     ie->param_data.resetCause.cause,
                     ie->param_data.resetCause.cause <= SCCP_RES_UNQUAL
                        ? resetStrings[ie->param_data.resetCause.cause]
                        : "unknown");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_ERROR_CAUSE:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Error cause = %s\n",
                     *bCount, ie->param_data.errorCause.cause,
                     ie->param_data.errorCause.cause,
                     ie->param_data.errorCause.cause <= SCCP_ERR_UNQUAL
                        ? errorStrings[ie->param_data.errorCause.cause]
                        : "unknown");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_REFUSAL_CAUSE:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Refusal cause = %s\n",
                     *bCount, ie->param_data.refusalCause.cause,
                     ie->param_data.refusalCause.cause,
                     ie->param_data.refusalCause.cause <= SCCP_REF_UNQUAL
                        ? refusalStrings[ie->param_data.refusalCause.cause]
                        : "unknown");
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_SEGMENTATION:
        /* flags */
        tmp = PPrint(rb, " %3d.  %02x  %b|%b|%06b  "
                         "First? = %s, Retain = %s, Remaining = %d\n",
                     *bCount, ie->param_data.segmentation.flags,
                     ie->param_data.segmentation.flags >> 7,
                     (ie->param_data.segmentation.flags >> 6) & 1,
                     ie->param_data.segmentation.flags & 0x3FU,
                     ie->param_data.segmentation.flags & SCCP_SEG_IS_FIRST
                        ? "yes"
                        : "no",
                     ie->param_data.segmentation.flags & SCCP_SEG_RETAIN_SEQ
                        ? "yes"
                        : "no",
                     ie->param_data.segmentation.flags & SCCP_SEG_REMNANT_MASK);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* ref number */
        val = RN_GET_REF_NUM(ie->param_data.segmentation.localRef);
        /* byte  0 */
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Value = %d\n",
                     *bCount, ie->param_data.segmentation.localRef.refno[0],
                     ie->param_data.segmentation.localRef.refno[0],
                     val);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* byte  1 */
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, ie->param_data.segmentation.localRef.refno[1],
                     ie->param_data.segmentation.localRef.refno[1]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;

        /* byte  2 */
        tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                     *bCount, ie->param_data.segmentation.localRef.refno[2],
                     ie->param_data.segmentation.localRef.refno[2]);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_HOP_COUNTER:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Hop counter = %d\n",
                     *bCount, ie->param_data.hopCount.count,
                     ie->param_data.hopCount.count,
                     ie->param_data.hopCount.count);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_IMPORTANCE:
        tmp = PPrint(rb, " %3d.  %02x    %08b  "
                         "Importance = %d\n",
                     *bCount, ie->param_data.importance.importance,
                     ie->param_data.importance.importance,
                     ie->param_data.importance.importance);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;

    case SCCP_PRM_DATA:
        if (printUserData)
        {
            for (i = 0; i < ie->param_length; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Data[%u] = 0x%02x\n",
                             *bCount, ie->param_data.userData.data[i],
                             ie->param_data.userData.data[i],
                             i,
                             ie->param_data.userData.data[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
        }
        break;

    case SCCP_PRM_LONG_DATA:
        if (printUserData)
        {
            for (i = 0; i < ie->param_length; i++)
            {
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "Data[%u] = 0x%02x\n",
                             *bCount, ie->param_data.longData.data[i],
                             ie->param_data.longData.data[i],
                             i,
                             ie->param_data.longData.data[i]);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;
            }
        }
        break;

/* these two aren't used */
#if 0
    case SCCP_PRM_ISNI:
        break;

    case SCCP_PRM_ROUTING_LABEL:
        break;
#endif
    default:
        tmp = PPrint(rb, " %3d.  %02x    --------  "
                         "Unknown IE identifier\n",
                     *bCount, ie->param_id);
        CHECK_RETURN(tmp, ret);
        (*bCount)++;
        break;
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function pretty prints an SCCP message.
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_PPrint(RINGBUF_Manager *rb, ITS_UINT *bCount, ITS_OCTET mType,
            ITS_SCCP_IE *ies, ITS_UINT ieCount,
            ITS_BOOLEAN printUserData)
{
    SCCP_MSG_DESC *desc = SCCP_GetDescriptor(mType);
    int tmp, ret, i, cnt;
    ITS_UINT j;
    ITS_OCTET *args;

    /* header */
    ret = PPrint(rb, SCCP_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    if (desc == NULL)
    {
        ret = PPrint(rb, " SCCP Decode error!\n");
        (*bCount)++;

        return ret;
    }

    /* SCCP message type */
    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                     "SCCP Message Type = %d (%s)\n",
                 *bCount, mType,
                 mType, mType,
                 mType <= SCCP_MSG_LUDTS
                    ? msgNames[mType]
                    : msgNames[0]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* mandatory IEs */
    args = desc->mArgs;
    for (i = 0; i < desc->nmArgs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (args[i] == ies[j].param_id)
            {
                /* print the IE id */
                tmp = PPrint(rb, " ---   %02x    %08b  "
                                 "IE identifier = %d (%s, not in data)\n",
                             ies[j].param_id,
                             ies[j].param_id,
                             ies[j].param_id,
                             ies[j].param_id <= SCCP_PRM_LONG_DATA
                                ? ieNames[ies[j].param_id]
                                : "unknown");
                CHECK_RETURN(tmp, ret);

                /* print the IE length */
                tmp = PPrint(rb, " ---   %02x    %08b  "
                                 "IE length = %d (not in data)\n",
                             ies[j].param_length,
                             ies[j].param_length,
                             ies[j].param_length);
                CHECK_RETURN(tmp, ret);

                /* print the IE */
                tmp = PPrint_IE(rb, bCount, &ies[j], printUserData);
                CHECK_RETURN(tmp, ret);

                /* exit inner loop */
                break;
            }
        }
    }

    /* rebuild the pointer table */
    if (desc->nvArgs)
    {
        /* find out how many */
        cnt = 0;
        args = desc->vArgs;
        for (i = 0; i < desc->nvArgs; i++)
        {
            for (j = 0; j < ieCount; j++)
            {
                if (args[i] == ies[j].param_id)
                {
                    cnt++;
                }
            }
        }

        /* rebuild the pointer table */
        for (i = 0; i < desc->nvArgs; i++)
        {
            for (j = 0; j < ieCount; j++)
            {
                if (args[i] == ies[j].param_id)
                {
                    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                     "Pointer to IE id = %d (%s)\n",
                                 *bCount, cnt,
                                 cnt,
                                 ies[j].param_id,
                                 ies[j].param_id <= SCCP_PRM_LONG_DATA
                                    ? ieNames[ies[j].param_id]
                                    : "unknown");
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;

                    /* calculate next pointer */
                    cnt--;
                    cnt += sizeof(ITS_OCTET) + ies[j].param_length;
                    if (ies[j].param_id == SCCP_PRM_LONG_DATA)
                    {
                        cnt += sizeof(ITS_OCTET);
                    }
                }
            }
        }
    }

    /* variable IEs */
    args = desc->vArgs;
    for (i = 0; i < desc->nvArgs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (args[i] == ies[j].param_id)
            {
                /* print the IE id */
                tmp = PPrint(rb, " ---   %02x    %08b  "
                                 "IE identifier = %d (%s, not in data)\n",
                             ies[j].param_id,
                             ies[j].param_id,
                             ies[j].param_id,
                             ies[j].param_id <= SCCP_PRM_LONG_DATA
                                ? ieNames[ies[j].param_id]
                                : "unknown");
                CHECK_RETURN(tmp, ret);

                /* print the IE length */
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "IE length = %d\n",
                             *bCount, ies[j].param_length,
                             ies[j].param_length,
                             ies[j].param_length);
                CHECK_RETURN(tmp, ret);
                (*bCount)++;

                /* print the IE */
                PPrint_IE(rb, bCount, &ies[j], printUserData);
                CHECK_RETURN(tmp, ret);

                /* exit inner loop */
                break;
            }
        }
    }

    /* optional IEs */
    args = desc->oArgs;
    for (i = 0; i < desc->noArgs; i++)
    {
        for (j = 0; j < ieCount; j++)
        {
            if (args[i] == ies[j].param_id)
            {
                /* print the IE id */
                tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                 "IE identifier = %d (%s)\n",
                             *bCount, ies[i].param_id,
                             ies[j].param_id,
                             ies[j].param_id,
                             ies[j].param_id <= SCCP_PRM_LONG_DATA
                                ? ieNames[ies[j].param_id]
                                : "unknown");
                CHECK_RETURN(tmp, ret);
                (*bCount)++;

                /* don't print anything else if this is EOP */
                if (ies[j].param_id == SCCP_PRM_EOP)
                {
                    break;
                }

                /* print the IE length.  Special case long length */
                if (ies[j].param_id == SCCP_PRM_LONG_DATA)
                {
                    /* byte 0 */
                    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                     "IE length = %d\n",
                                 *bCount, ies[j].param_length >> 8,
                                 ies[j].param_length >> 8,
                                 ies[j].param_length);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;

                    /* byte 1 */
                    tmp = PPrint(rb, " %3d.  %02x    %08b\n",
                                 *bCount, ies[j].param_length & 0xFFU,
                                 ies[j].param_length & 0xFFU);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                }
                else
                {
                    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                                     "IE length = %d\n",
                                 *bCount, ies[j].param_length,
                                 ies[j].param_length,
                                 ies[j].param_length);
                    CHECK_RETURN(tmp, ret);
                    (*bCount)++;
                }

                /* print the IE */
                PPrint_IE(rb, bCount, &ies[j], printUserData);
                CHECK_RETURN(tmp, ret);

                /* exit inner loop */
                break;
            }
        }
    }

    return (ret);
}

/*** CR ***/
static ITS_OCTET    crMArgs[] =
{
    SCCP_PRM_SRC_LOCAL_REF,
    SCCP_PRM_PROTOCOL_CLASS
};
static ITS_OCTET    crVArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR
};
static ITS_OCTET    crOArgs[] =
{
    SCCP_PRM_CREDIT,
    SCCP_PRM_CALLING_PARTY_ADDR,
    SCCP_PRM_DATA,
    SCCP_PRM_HOP_COUNTER,
};

SS7DLLAPI SCCP_MSG_DESC SCCP_CR_Desc =
{
    crMArgs, sizeof(crMArgs),
    crVArgs, sizeof(crVArgs),
    crOArgs, sizeof(crOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ConnectionRequest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendConnectionRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                           ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_CR, hdr, ies, ieCount,
                          &SCCP_CR_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ConnectionRequest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveConnectionRequest(ITS_HANDLE handle, ITS_EVENT *ev,
                              ITS_HDR *hdr,
                              ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_CR_Desc);
}

/*** CC ***/
static ITS_OCTET    ccMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SRC_LOCAL_REF,
    SCCP_PRM_PROTOCOL_CLASS
};
static ITS_OCTET    ccOArgs[] =
{
    SCCP_PRM_CREDIT,
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_DATA
};

SS7DLLAPI SCCP_MSG_DESC SCCP_CC_Desc =
{
    ccMArgs, sizeof(ccMArgs),
    NULL, 0,
    ccOArgs, sizeof(ccOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ConnectionConfirm
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendConnectionConfirm(ITS_HANDLE handle, ITS_HDR *hdr,
                           ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_CC, hdr, ies, ieCount,
                          &SCCP_CC_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ConnectionConfirm
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveConnectionConfirm(ITS_HANDLE handle, ITS_EVENT *ev,
                              ITS_HDR *hdr,
                              ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_CC_Desc);
}


/*** CREF ***/
static ITS_OCTET    cfMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_REFUSAL_CAUSE
};
static ITS_OCTET    cfOArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_DATA
};

SS7DLLAPI SCCP_MSG_DESC SCCP_CREF_Desc =
{
    cfMArgs, sizeof(cfMArgs),
    NULL, 0,
    cfOArgs, sizeof(cfOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ConnectionRefused
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendConnectionRefused(ITS_HANDLE handle, ITS_HDR *hdr,
                           ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_CREF, hdr, ies, ieCount,
                          &SCCP_CREF_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ConnectionRefused
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveConnectionRefused(ITS_HANDLE handle, ITS_EVENT *ev,
                              ITS_HDR *hdr,
                              ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_CREF_Desc);
}


/*** RLSD ***/
static ITS_OCTET    rlMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SRC_LOCAL_REF,
    SCCP_PRM_RELEASE_CAUSE
};
static ITS_OCTET    rlOArgs[] =
{
    SCCP_PRM_DATA,
    SCCP_PRM_IMPORTANCE		// RLSD ISSUE (Issue Id - 2210)
};

SS7DLLAPI SCCP_MSG_DESC SCCP_RLSD_Desc =
{
    rlMArgs, sizeof(rlMArgs),
    NULL, 0,
    rlOArgs, sizeof(rlOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a Released
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendReleased(ITS_HANDLE handle, ITS_HDR *hdr,
                  ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_RLSD, hdr, ies, ieCount,
                          &SCCP_RLSD_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a Released
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveReleased(ITS_HANDLE handle, ITS_EVENT *ev,
                     ITS_HDR *hdr,
                     ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_RLSD_Desc);
}


/*** RLC ***/
static ITS_OCTET    rcMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SRC_LOCAL_REF,
};

SS7DLLAPI SCCP_MSG_DESC SCCP_RLC_Desc =
{
    rcMArgs, sizeof(rcMArgs),
    NULL, 0,
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ReleaseComplete
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendReleaseComplete(ITS_HANDLE handle, ITS_HDR *hdr,
                         ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_RLC, hdr, ies, ieCount,
                          &SCCP_RLC_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ReleaseComplete
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveReleaseComplete(ITS_HANDLE handle, ITS_EVENT *ev,
                            ITS_HDR *hdr,
                            ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_RLC_Desc);
}


/*** DT1 ***/
static ITS_OCTET    d1MArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SEGMENT_REASSEM
};
static ITS_OCTET    d1VArgs[] =
{
    SCCP_PRM_DATA
};

SS7DLLAPI SCCP_MSG_DESC SCCP_DT1_Desc =
{
    d1MArgs, sizeof(d1MArgs),
    d1VArgs, sizeof(d1VArgs),
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a DataForm1
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendDataForm1(ITS_HANDLE handle, ITS_HDR *hdr,
                   ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_DT1, hdr, ies, ieCount,
                          &SCCP_DT1_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function DataForm1
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveDataForm1(ITS_HANDLE handle, ITS_EVENT *ev,
                      ITS_HDR *hdr,
                      ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_DT1_Desc);
}


/*** DT2 ***/
static ITS_OCTET    d2MArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SEQUENCE_SEGMENT
};
static ITS_OCTET    d2VArgs[] =
{
    SCCP_PRM_DATA
};

SS7DLLAPI SCCP_MSG_DESC SCCP_DT2_Desc =
{
    d2MArgs, sizeof(d2MArgs),
    d2VArgs, sizeof(d2VArgs),
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a DataForm2
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendDataForm2(ITS_HANDLE handle, ITS_HDR *hdr,
                   ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_DT2, hdr, ies, ieCount,
                          &SCCP_DT2_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a DataForm2
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveDataForm2(ITS_HANDLE handle, ITS_EVENT *ev,
                      ITS_HDR *hdr,
                      ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_DT2_Desc);
}


/*** AK ***/
static ITS_OCTET    akMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_RCV_SEQ_NUM,
    SCCP_PRM_CREDIT
};

SS7DLLAPI SCCP_MSG_DESC SCCP_AK_Desc =
{
    akMArgs, sizeof(akMArgs),
    NULL, 0,
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends an Acknowledge
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendAcknowledgement(ITS_HANDLE handle, ITS_HDR *hdr,
                         ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_AK, hdr, ies, ieCount,
                          &SCCP_AK_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes an Acknowledgement
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveAcknowledgement(ITS_HANDLE handle, ITS_EVENT *ev,
                            ITS_HDR *hdr,
                            ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_AK_Desc);
}


/*** UDT ***/
static ITS_OCTET    udMArgs[] =
{
    SCCP_PRM_PROTOCOL_CLASS
};
static ITS_OCTET    udVArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_CALLING_PARTY_ADDR,
    SCCP_PRM_DATA
};

SS7DLLAPI SCCP_MSG_DESC SCCP_UDT_Desc =
{
    udMArgs, sizeof(udMArgs),
    udVArgs, sizeof(udVArgs),
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a UnitData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  ID::R0170 - R210     XUDT/XUDTS Implementation
 *
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUnitData(ITS_HANDLE handle, ITS_HDR *hdr,
                  ITS_SCCP_IE *ies, int ieCount)
{
    ITS_INT longDataPos = 0; 
    ITS_INT i = 0;

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_LONG_DATA) 
        {
            longDataPos = i + 1;
        }
    }

    if(!longDataPos)
    {
        return SCCP_SendEvent(handle, SCCP_MSG_UDT, hdr,
                               ies, ieCount, &SCCP_UDT_Desc);
    }
    else
    {
        ITS_OCTET    data[SCCP_LONG_DATA_MAX];
        ITS_INT          dataLen = 0, a;
        static ITS_INT localRefNum = 0;
        ITS_OCTET    tmpSeg = 0;
        ITS_OCTET    totalSegment = 0;
        ITS_INT          ret = ITS_SUCCESS;

        memset(data, 0 , SCCP_LONG_DATA_MAX);

        dataLen = ies[longDataPos - 1].param_data.longData.len;
        memcpy(data, ies[longDataPos - 1].param_data.longData.data, dataLen);

        /* Add segmentation IE */
        ies[ieCount].param_id = SCCP_PRM_SEGMENTATION;
        ies[ieCount].param_length = sizeof(SCCP_SEGMENTATION);

        localRefNum++;

        if(localRefNum >= SCCP_MAX_SEG_REF)
        {
            localRefNum = 0;
        }

        RN_SET_REF_NUM(ies[ieCount].param_data.segmentation.localRef,
                       localRefNum);

        ieCount++;
        totalSegment = dataLen / SCCP_MAX_SEG_DATA;
        tmpSeg = totalSegment;

        if (dataLen % SCCP_MAX_SEG_DATA)
        {
            totalSegment++;
        }

        if (totalSegment > SCCP_MAX_ALLOWED_SEGMENT)
        {
            return (ITS_EPROTERR);
        }

        memset(&ies[longDataPos - 1].param_data.longData.data, 0, 
               SCCP_LONG_DATA_MAX);

        ies[longDataPos - 1].param_id = SCCP_PRM_DATA;
        ies[longDataPos - 1].param_length = SCCP_MAX_SEG_DATA;
        memcpy (ies[longDataPos - 1].param_data.userData.data, data, 
                SCCP_MAX_SEG_DATA);

        ies[ieCount - 1].param_data.segmentation.flags =
                                        SCCP_SEG_IS_FIRST|SCCP_SEG_RETAIN_SEQ;
        ies[ieCount - 1].param_data.segmentation.flags |= (totalSegment - 1);

        ret = SCCP_SendExtendedUnitData(handle, hdr, ies, ieCount);

        if (ret != ITS_SUCCESS) return ret;

        totalSegment--;

        ies[ieCount - 1].param_data.segmentation.flags =
                                                      SCCP_SEG_RETAIN_SEQ;

        for (i = 1; i < tmpSeg; i++)
        {
            memcpy (ies[longDataPos - 1].param_data.userData.data, 
                    data + (i * SCCP_MAX_SEG_DATA), SCCP_MAX_SEG_DATA); 
            ies[ieCount - 1].param_data.segmentation.flags &= 0xf0;
            ies[ieCount - 1].param_data.segmentation.flags |= (totalSegment - 1);

            ret = SCCP_SendExtendedUnitData(handle, hdr, ies, ieCount);
            totalSegment--;
            if (ret != ITS_SUCCESS) break;
        }

        if (ret != ITS_SUCCESS) return ret;

        if (totalSegment) 
        {
            memset (&ies[longDataPos - 1].param_data.userData.data, 0, 
                    SCCP_MAX_SEG_DATA);
            memcpy (ies[longDataPos - 1].param_data.userData.data,
                    data + (tmpSeg * SCCP_MAX_SEG_DATA), 
                    dataLen % SCCP_MAX_SEG_DATA);
            ies[longDataPos - 1].param_length = dataLen % SCCP_MAX_SEG_DATA;
            ies[ieCount - 1].param_data.segmentation.flags &= 0xf0;
            ies[ieCount - 1].param_data.segmentation.flags |= (totalSegment - 1);

            ret = SCCP_SendExtendedUnitData(handle, hdr, ies, ieCount);
        }

        return ret;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a UnitData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveUnitData(ITS_HANDLE handle, ITS_EVENT *ev,
                     ITS_HDR *hdr,
                     ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_UDT_Desc);
}


/*** XUDT ***/
static ITS_OCTET    xdMArgs[] =
{
    SCCP_PRM_PROTOCOL_CLASS,
    SCCP_PRM_HOP_COUNTER
};
static ITS_OCTET    xdVArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_CALLING_PARTY_ADDR,
    SCCP_PRM_DATA
};
static ITS_OCTET    xdOArgs[] =
{
    SCCP_PRM_SEGMENTATION,
#if defined(CCITT) || defined(PRC) || defined(TTC)
    SCCP_PRM_IMPORTANCE   
#else
    SCCP_PRM_ISNI
#endif
};

SS7DLLAPI SCCP_MSG_DESC SCCP_XUDT_Desc =
{
    xdMArgs, sizeof(xdMArgs),
    xdVArgs, sizeof(xdVArgs),
    xdOArgs, sizeof(xdOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ExtendedUnitData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendExtendedUnitData(ITS_HANDLE handle, ITS_HDR *hdr,
                          ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_XUDT, hdr, ies, ieCount,
                          &SCCP_XUDT_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ExtendedUnitData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveExtendedUnitData(ITS_HANDLE handle, ITS_EVENT *ev,
                             ITS_HDR *hdr,
                             ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_XUDT_Desc);
}


/*** UDTS ***/
static ITS_OCTET    usMArgs[] =
{
    SCCP_PRM_RETURN_CAUSE
};
static ITS_OCTET    usVArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_CALLING_PARTY_ADDR,
    SCCP_PRM_DATA
};

SS7DLLAPI SCCP_MSG_DESC SCCP_UDTS_Desc =
{
    usMArgs, sizeof(usMArgs),
    usVArgs, sizeof(usVArgs),
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a UnitDataService
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUnitDataService(ITS_HANDLE handle, ITS_HDR *hdr,
                         ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_UDTS, hdr, ies, ieCount,
                          &SCCP_UDTS_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a UnitDataService
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveUnitDataService(ITS_HANDLE handle, ITS_EVENT *ev,
                            ITS_HDR *hdr,
                            ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_UDTS_Desc);
}


/*** XUDTS ***/
static ITS_OCTET    xsMArgs[] =
{
    SCCP_PRM_RETURN_CAUSE,
    SCCP_PRM_HOP_COUNTER
};
static ITS_OCTET    xsVArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_CALLING_PARTY_ADDR,
    SCCP_PRM_DATA
};
static ITS_OCTET    xsOArgs[] =
{
#if defined(CCITT) || defined(PRC) || defined(TTC)
    SCCP_PRM_IMPORTANCE,   
#else
    SCCP_PRM_ISNI,
#endif
    SCCP_PRM_SEGMENTATION
};

SS7DLLAPI SCCP_MSG_DESC SCCP_XUDTS_Desc =
{
    xsMArgs, sizeof(xsMArgs),
    xsVArgs, sizeof(xsVArgs),
    xdOArgs, sizeof(xsOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends an ExtendedUnitDataService
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendExtendedUnitDataService(ITS_HANDLE handle, ITS_HDR *hdr,
                                 ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_XUDTS, hdr, ies, ieCount,
                          &SCCP_XUDTS_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes an ExtendedUnitDataService
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveExtendedUnitDataService(ITS_HANDLE handle, ITS_EVENT *ev,
                                    ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_XUDTS_Desc);
}


/*** ED ***/
static ITS_OCTET    edMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
};
static ITS_OCTET    edVArgs[] =
{
    SCCP_PRM_DATA
};

SS7DLLAPI SCCP_MSG_DESC SCCP_ED_Desc =
{
    edMArgs, sizeof(edMArgs),
    edVArgs, sizeof(edVArgs),
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends an ExpeditedData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendExpeditedData(ITS_HANDLE handle, ITS_HDR *hdr,
                       ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_ED, hdr, ies, ieCount,
                          &SCCP_ED_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes an ExpeditedData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveExpeditedData(ITS_HANDLE handle, ITS_EVENT *ev,
                          ITS_HDR *hdr,
                          ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_ED_Desc);
}


/*** EA ***/
static ITS_OCTET    eaMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF
};

SS7DLLAPI SCCP_MSG_DESC SCCP_EA_Desc =
{
    eaMArgs, sizeof(eaMArgs),
    NULL, 0,
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends an ExpeditedDataAcknowledge
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendExpeditedDataAck(ITS_HANDLE handle, ITS_HDR *hdr,
                          ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_EA, hdr, ies, ieCount,
                          &SCCP_EA_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes an ExpeditedDataAcknowledge
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveExpeditedDataAck(ITS_HANDLE handle, ITS_EVENT *ev,
                             ITS_HDR *hdr,
                             ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_EA_Desc);
}


/*** RSR ***/
static ITS_OCTET    rrMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SRC_LOCAL_REF,
    SCCP_PRM_RESET_CAUSE
};

SS7DLLAPI SCCP_MSG_DESC SCCP_RSR_Desc =
{
    rrMArgs, sizeof(rrMArgs),
    NULL, 0,
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ResetRequest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendResetRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                      ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_RSR, hdr, ies, ieCount,
                          &SCCP_RSR_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ResetRequest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveResetRequest(ITS_HANDLE handle, ITS_EVENT *ev,
                         ITS_HDR *hdr,
                         ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_RSR_Desc);
}


/*** RSC ***/
static ITS_OCTET    rfMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SRC_LOCAL_REF
};

SS7DLLAPI SCCP_MSG_DESC SCCP_RSC_Desc =
{
    rfMArgs, sizeof(rfMArgs),
    NULL, 0,
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ResetConfirm
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendResetConfirmation(ITS_HANDLE handle, ITS_HDR *hdr,
                           ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_RSC, hdr, ies, ieCount,
                          &SCCP_RSC_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ResetConfirm
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveResetConfirmation(ITS_HANDLE handle, ITS_EVENT *ev,
                              ITS_HDR *hdr,
                              ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_RSC_Desc);
}


/*** ERR ***/
static ITS_OCTET    erMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_ERROR_CAUSE
};

SS7DLLAPI SCCP_MSG_DESC SCCP_ERR_Desc =
{
    erMArgs, sizeof(erMArgs),
    NULL, 0,
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends an Error
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendError(ITS_HANDLE handle, ITS_HDR *hdr,
               ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_ERR, hdr, ies, ieCount,
                          &SCCP_ERR_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes an Error
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveError(ITS_HANDLE handle, ITS_EVENT *ev,
                  ITS_HDR *hdr,
                  ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_ERR_Desc);
}


/*** IT ***/
static ITS_OCTET    itMArgs[] =
{
    SCCP_PRM_DEST_LOCAL_REF,
    SCCP_PRM_SRC_LOCAL_REF,
    SCCP_PRM_PROTOCOL_CLASS,
    SCCP_PRM_SEQUENCE_SEGMENT,
    SCCP_PRM_CREDIT
};

SS7DLLAPI SCCP_MSG_DESC SCCP_IT_Desc =
{
    itMArgs, sizeof(itMArgs),
    NULL, 0,
    NULL, 0
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends an InactivityTest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendInactivityTest(ITS_HANDLE handle, ITS_HDR *hdr,
                        ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_IT, hdr, ies, ieCount,
                          &SCCP_IT_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes an InactivityTest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveInactivityTest(ITS_HANDLE handle, ITS_EVENT *ev,
                           ITS_HDR *hdr,
                           ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_IT_Desc);
}




/*** LUDT ***/
static ITS_OCTET    ldMArgs[] =
{
    SCCP_PRM_PROTOCOL_CLASS,
    SCCP_PRM_HOP_COUNTER
};
static ITS_OCTET    ldVArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_CALLING_PARTY_ADDR,
    SCCP_PRM_LONG_DATA
};
#if defined(CCITT) || defined(PRC) || defined(TTC)
static ITS_OCTET    ldOArgs[] =
{
    SCCP_PRM_SEGMENTATION,
    SCCP_PRM_IMPORTANCE
};
#endif

SS7DLLAPI SCCP_MSG_DESC SCCP_LUDT_Desc =
{
    ldMArgs, sizeof(ldMArgs),
    ldVArgs, sizeof(ldVArgs),
#if defined(ANSI)
    NULL, 0
#elif defined(CCITT) || defined(PRC) || defined(TTC)
    ldOArgs, sizeof(ldOArgs)
#endif
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a LongUnitData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendLongUnitData(ITS_HANDLE handle, ITS_HDR *hdr,
                          ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_LUDT, hdr, ies, ieCount,
                          &SCCP_LUDT_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a LongUnitData
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveLongUnitData(ITS_HANDLE handle, ITS_EVENT *ev,
                             ITS_HDR *hdr,
                             ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_LUDT_Desc);
}


/*** LUDTS ***/
static ITS_OCTET    lsMArgs[] =
{
    SCCP_PRM_RETURN_CAUSE,
    SCCP_PRM_HOP_COUNTER
};
static ITS_OCTET    lsVArgs[] =
{
    SCCP_PRM_CALLED_PARTY_ADDR,
    SCCP_PRM_CALLING_PARTY_ADDR,
    SCCP_PRM_LONG_DATA
};
#if defined(CCITT) || defined(PRC) || defined(TTC)
static ITS_OCTET    lsOArgs[] =
{
    SCCP_PRM_SEGMENTATION,
    SCCP_PRM_IMPORTANCE
};
#endif

SS7DLLAPI SCCP_MSG_DESC SCCP_LUDTS_Desc =
{
    lsMArgs, sizeof(lsMArgs),
    lsVArgs, sizeof(lsVArgs),
#if defined(ANSI)
    NULL, 0
#elif defined(CCITT) || defined(PRC) || defined(TTC)
    ldOArgs, sizeof(lsOArgs)
#endif
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends an LongUnitDataService
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendLongUnitDataService(ITS_HANDLE handle, ITS_HDR *hdr,
                                 ITS_SCCP_IE *ies, int ieCount)
{
    return SCCP_SendEvent(handle, SCCP_MSG_LUDTS, hdr, ies, ieCount,
                          &SCCP_LUDTS_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes an LongUnitDataService
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveLongUnitDataService(ITS_HANDLE handle, ITS_EVENT *ev,
                                    ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return SCCP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &SCCP_LUDTS_Desc);
}

