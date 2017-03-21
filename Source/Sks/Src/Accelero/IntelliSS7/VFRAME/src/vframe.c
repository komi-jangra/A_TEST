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
 *  ID: $Id: vframe.c,v 1.1.1.1 2007-10-08 11:11:29 bsccs2 Exp $
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:34  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.3  2006/02/23 06:34:35  sjaddu
 * LOG: Making va_args compatable to mvlppc.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.15  2005/03/21 13:50:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.1.6.1.6.1  2004/12/16 01:52:54  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.8.2.1.6.1  2004/09/21 09:43:39  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.8.2.1  2003/06/18 10:09:51  tsanthosh
 * LOG: UnReserve CIC functions are added.
 * LOG:
 * LOG: Revision 7.8  2003/02/12 18:49:45  mmiers
 * LOG: Some context size bugs (dialogues)
 * LOG:
 * LOG: Revision 7.7  2003/02/05 17:05:40  sjaddu
 * LOG: RserveCic changes for ITU ISUP.
 * LOG:
 * LOG: Revision 7.6  2003/02/05 01:19:41  sjaddu
 * LOG: Reserve Cic changes for ISUP.
 * LOG:
 * LOG: Revision 7.5  2003/02/04 22:52:06  vnitin
 * LOG: Changes to Access to TRANSPORT Exit State Variable
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.3  2003/01/07 15:59:03  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.2  2002/10/31 15:09:11  mmiers
 * LOG: Short name bug
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:34  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.11  2002/08/01 15:50:00  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.10  2002/07/11 18:18:34  mmiers
 * LOG: Audit found a few more invalid pointers
 * LOG:
 * LOG: Revision 6.9  2002/07/11 16:56:12  dalonso
 * LOG: Use the right pointer in PutEvent
 * LOG:
 * LOG: Revision 6.8  2002/07/03 17:41:16  mmiers
 * LOG: china changes
 * LOG:
 * LOG: Revision 6.7  2002/07/01 21:50:55  mmiers
 * LOG: Vframe changes to support ISUP
 * LOG:
 * LOG: Revision 6.6.2.1  2002/06/28 23:27:28  hbalimid
 * LOG: Modified ISUP_ReceiveEvent_ANSI for ISUP variant requirements.
 * LOG:
 * LOG: Revision 6.6  2002/06/28 16:28:46  hbalimid
 * LOG: Modified for ISUP variant requirements.
 * LOG:
 * LOG: Revision 6.5  2002/05/30 16:35:45  mmiers
 * LOG: Correct signatures
 * LOG:
 * LOG: Revision 6.4  2002/05/07 15:03:16  wweng
 * LOG: Reorder initialization
 * LOG:
 * LOG: Revision 6.3  2002/04/26 20:43:16  mmiers
 * LOG: Include checking mask
 * LOG:
 * LOG: Revision 6.2  2002/04/16 19:58:35  yranade
 * LOG: Name the classes uniquely
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.5  2002/02/13 18:27:44  mmiers
 * LOG: Finish off the ISUP integration.
 * LOG:
 * LOG: Revision 1.4  2002/02/08 22:40:20  ssharma
 * LOG: Use right struct member
 * LOG:
 * LOG: Revision 1.3  2002/02/01 21:19:27  mmiers
 * LOG: Integration fix.
 * LOG:
 * LOG: Revision 1.2  2002/01/10 22:59:57  mmiers
 * LOG: Change max msg size for MTP2 to allow for SAAL links.  Need to
 * LOG: start thinking about what needs to be done for MTP3
 * LOG:
 * LOG: Revision 1.1  2002/01/10 16:51:35  mmiers
 * LOG: Finish the transport refcounting effort.  Move vframe from
 * LOG: vendors to here.
 * LOG:
 * LOG: Revision 1.9  2001/12/20 20:29:11  mmiers
 * LOG: Alignment
 * LOG:
 * LOG: Revision 1.8  2001/12/19 23:54:02  mmiers
 * LOG: Get ADAX vendor lib working.
 * LOG:
 * LOG: Revision 1.7  2001/12/19 18:03:02  mmiers
 * LOG: Adax testing on Solaris revealed several build flaws.
 * LOG:
 * LOG: Revision 1.6  2001/12/18 19:17:47  mmiers
 * LOG: Build on solaris
 * LOG:
 * LOG: Revision 1.5  2001/12/17 21:09:23  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 1.4  2001/12/17 00:15:35  mmiers
 * LOG: Get this building on UNIX
 * LOG:
 * LOG: Revision 1.3  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 1.2  2001/12/14 00:05:04  mmiers
 * LOG: Generic vendor framework.
 * LOG:
 * LOG: Revision 1.1  2001/12/13 23:01:27  mmiers
 * LOG: Common vendor framework.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include <its.h>
#include <its_ss7_trans.h>
#include <its_mlist.h>
#include <its_assertion.h>
#include <its_hmi.h>
#include <its_pprint.h>

#if !defined(SPLIT_STACK) && !defined(USE_ANSI_SCCP)
#include <ansi/tcap.h>
#endif
#if !defined(SPLIT_STACK) && !defined(USE_ITU_SCCP)
#include <itu/tcap.h>
#endif
#include <itu/sccp.h>

#include <vframe.h>

/*
 * avoid header issues.  It just isn't worth it.
 */

typedef void SNMM_MESSAGE;

SS7DLLAPI int SNMM_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                               SNMM_MESSAGE *msg);
SS7DLLAPI int SNMM_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                SNMM_MESSAGE *msg);
SS7DLLAPI int SNMM_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                              SNMM_MESSAGE *msg);

typedef void SLTM_MESSAGE;

SS7DLLAPI int SLTM_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                               SLTM_MESSAGE *msg);
SS7DLLAPI int SLTM_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                SLTM_MESSAGE *msg);
SS7DLLAPI int SLTM_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                              SLTM_MESSAGE *msg);

/***************************** PRINT ROUTINES ******************************/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Pretty print MTP2 data.
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
 ****************************************************************************/
SS7DLLAPI char *
MTP2_TypePrint(RINGBUF_Manager *ring,
               char type, va_list alist,
               char *text, int textLen,
               ITS_USHORT *flags,
               char *prefix, int *prefixLen,
               int *fieldWidth, int *precision)
{
    void *hdr;
    ITS_UINT *lineCount;

    /* step 1. Get the argument */
    lineCount = va_arg(alist, ITS_UINT *);
    hdr = va_arg(alist, void *);

    /* depending on the flags let's see what to do */
    if (*flags & FLAG_FAMILY_ANSI)
    {
        MTP2_PPrint_ANSI(ring, lineCount, (MTP2_HEADER_ANSI *)hdr);
    }
    else if (*flags & FLAG_FAMILY_ITU)
    {
        MTP2_PPrint_CCITT(ring, lineCount, (MTP2_HEADER_CCITT *)hdr);
    }
#if !defined(SPLIT_STACK)
    else if (*flags & FLAG_FAMILY_PRC)
    {
        MTP2_PPrint_PRC(ring, lineCount, (MTP2_HEADER_PRC *)hdr);
    }
#endif

    /* we return NULL because we did the output. */
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Pretty print MTP3 data.
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
 ****************************************************************************/
SS7DLLAPI char *
MTP3_TypePrint(RINGBUF_Manager *ring,
               char type, va_list alist,
               char *text, int textLen,
               ITS_USHORT *flags,
               char *prefix, int *prefixLen,
               int *fieldWidth, int *precision)
{
    void *hdr;
    ITS_UINT *lineCount;

    /* step 1. Get the argument */
    lineCount = va_arg(alist, ITS_UINT *);
    hdr = va_arg(alist, void *);

    /* depending on the flags let's see what to do */
    if (*flags & FLAG_FAMILY_ANSI)
    {
        MTP3_PPrint_ANSI(ring, lineCount, (MTP3_HEADER_ANSI *)hdr);
    }
    else if (*flags & FLAG_FAMILY_ITU)
    {
        MTP3_PPrint_CCITT(ring, lineCount, (MTP3_HEADER_CCITT *)hdr);
    }
#if !defined(SPLIT_STACK)
    else if (*flags & FLAG_FAMILY_PRC)
    {
        MTP3_PPrint_PRC(ring, lineCount, (MTP3_HEADER_PRC *)hdr);
    }
#endif

    /* we return NULL because we did the output. */
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Pretty print SNMM data.
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
 ****************************************************************************/
SS7DLLAPI char *
SNMM_TypePrint(RINGBUF_Manager *ring,
               char type, va_list alist,
               char *text, int textLen,
               ITS_USHORT *flags,
               char *prefix, int *prefixLen,
               int *fieldWidth, int *precision)
{
    void *msg;
    ITS_UINT *lineCount;

    /* step 1. Get the argument */
    lineCount = va_arg(alist, ITS_UINT *);
    msg = va_arg(alist, void *);

    /* depending on the flags let's see what to do */
    if (*flags & FLAG_FAMILY_ANSI)
    {
        SNMM_PPrint_ANSI(ring, lineCount, (SNMM_MESSAGE *)msg);
    }
    else if (*flags & FLAG_FAMILY_ITU)
    {
        SNMM_PPrint_CCITT(ring, lineCount, (SNMM_MESSAGE *)msg);
    }
#if !defined(SPLIT_STACK)
    else if (*flags & FLAG_FAMILY_PRC)
    {
        SNMM_PPrint_PRC(ring, lineCount, (SNMM_MESSAGE *)msg);
    }
#endif

    /* we return NULL because we did the output. */
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Pretty print SLTM data.
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
 ****************************************************************************/
SS7DLLAPI char *
SLTM_TypePrint(RINGBUF_Manager *ring,
               char type, va_list alist,
               char *text, int textLen,
               ITS_USHORT *flags,
               char *prefix, int *prefixLen,
               int *fieldWidth, int *precision)
{
    void *msg;
    ITS_UINT *lineCount;

    /* step 1. Get the argument */
    lineCount = va_arg(alist, ITS_UINT *);
    msg = va_arg(alist, void *);

    /* depending on the flags let's see what to do */
    if (*flags & FLAG_FAMILY_ANSI)
    {
        SLTM_PPrint_ANSI(ring, lineCount, (SLTM_MESSAGE *)msg);
    }
    else if (*flags & FLAG_FAMILY_ITU)
    {
        SLTM_PPrint_CCITT(ring, lineCount, (SLTM_MESSAGE *)msg);
    }
#if !defined(SPLIT_STACK)
    else if (*flags & FLAG_FAMILY_PRC)
    {
        SLTM_PPrint_PRC(ring, lineCount, (SLTM_MESSAGE *)msg);
    }
#endif

    /* we return NULL because we did the output. */
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Pretty print SCCP data.
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
 ****************************************************************************/
SS7DLLAPI char *
SCCP_TypePrint(RINGBUF_Manager *ring,
               char type, va_list alist,
               char *text, int textLen,
               ITS_USHORT *flags,
               char *prefix, int *prefixLen,
               int *fieldWidth, int *precision)
{
    ITS_OCTET mType;
    void *ies;
    ITS_UINT ieCount;
    ITS_BOOLEAN printData;
    ITS_UINT *lineCount;

    /* step 1. Get the arguments */
    lineCount = va_arg(alist, ITS_UINT *);
    mType = (ITS_OCTET)va_arg(alist, ITS_UINT);
    ies = va_arg(alist, void *);
    ieCount = va_arg(alist, ITS_UINT);
    printData = va_arg(alist, ITS_BOOLEAN);

    /* depending on the flags let's see what to do */
    if (*flags & FLAG_FAMILY_ANSI)
    {
        SCCP_PPrint_ANSI(ring, lineCount,
                         mType, ies, ieCount, printData);
    }
    else if (*flags & FLAG_FAMILY_ITU)
    {
        SCCP_PPrint_CCITT(ring, lineCount,
                          mType, ies, ieCount, printData);
    }
#if !defined(SPLIT_STACK)
    else if (*flags & FLAG_FAMILY_PRC)
    {
        SCCP_PPrint_PRC(ring, lineCount,
                        mType, ies, ieCount, printData);
    }
#endif

    /* we return NULL because we did the output. */
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Pretty print ISUP data.
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
 ****************************************************************************/
SS7DLLAPI char *
ISUP_TypePrint(RINGBUF_Manager *ring,
               char type, va_list alist,
               char *text, int textLen,
               ITS_USHORT *flags,
               char *prefix, int *prefixLen,
               int *fieldWidth, int *precision)
{
    return (NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Pretty print TCAP data.
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
 ****************************************************************************/
SS7DLLAPI char *
TCAP_TypePrint(RINGBUF_Manager *ring,
               char type, va_list alist,
               char *text, int textLen,
               ITS_USHORT *flags,
               char *prefix, int *prefixLen,
               int *fieldWidth, int *precision)
{
    void *data;
    ITS_USHORT dlen;
    ITS_UINT *lineCount;
    TCAP_PPrintProc paramPrint;

    /* step 1. Get the arguments */
    lineCount = va_arg(alist, ITS_UINT *);
    data = va_arg(alist, void *);
    dlen = (ITS_USHORT)va_arg(alist, ITS_UINT);
    paramPrint = va_arg(alist, TCAP_PPrintProc);

    /* depending on the flags let's see what to do */
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(ANSI))
    if (*flags & FLAG_FAMILY_ANSI)
    {
        TCAP_PPrint_ANSI(ring, lineCount,
                         data, dlen, paramPrint);
    }
#endif
#if !defined(SPLIT_STACK) || (defined(SPLIT_STACK) && defined(CCITT))
    if (*flags & FLAG_FAMILY_ITU)
    {
        TCAP_PPrint_CCITT(ring, lineCount,
                          data, dlen, paramPrint);
    }
#endif
#if !defined(SPLIT_STACK)
    if (*flags & FLAG_FAMILY_PRC)
    {
        TCAP_PPrint_PRC(ring, lineCount,
                        data, dlen, paramPrint);
    }
#endif

    /* we return NULL because we did the output. */
    return (NULL);
}

/****************************** COMMON CODE ********************************/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize some class methods.
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
 ****************************************************************************/
static int
ClassPartInit(ITS_Class objClass)
{
    ITS_Class super;

    if (ITS_CLASS_SUPERCLASS(objClass) == NULL)
    {
        return (ITS_SUCCESS);
    }

    super = ITS_CLASS_SUPERCLASS(objClass);

    if (SS7STACK_CLASS_GET_NEXT_EVENT(objClass) == NULL)
    {
        SS7STACK_CLASS_GET_NEXT_EVENT(objClass) =
            SS7STACK_CLASS_GET_NEXT_EVENT(super);
    }

    if (SS7STACK_CLASS_PEEK_NEXT_EVENT(objClass) == NULL)
    {
        SS7STACK_CLASS_PEEK_NEXT_EVENT(objClass) =
            SS7STACK_CLASS_PEEK_NEXT_EVENT(super);
    }

    if (SS7STACK_CLASS_PUT_EVENT(objClass) == NULL)
    {
        SS7STACK_CLASS_PUT_EVENT(objClass) =
            SS7STACK_CLASS_PUT_EVENT(super);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize some class methods.
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
 ****************************************************************************/
static void
ClassPartDest(ITS_Class objClass)
{
    /* Nothing to do */
}

/****************************** PUBLIC API *********************************/

SS7DLLAPI CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_PRC_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_PRC_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_PRC_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_PRC_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_PRC_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_TTC_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_TTC_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_TTC_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_TTC_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_TTC_SSNRoutingCallbacks = NULL;

/****************************** ANSI VERSION *******************************/

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_SendEvent_ANSI(ITS_HANDLE handl,
                    ITS_OCTET type, MTP3_HEADER_ANSI *mtp3,
                    ITS_OCTET *buf, ITS_USHORT len)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendANSI == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendANSI)(inst,
                                                            type, mtp3,
                                                            buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_ReceiveEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                       ITS_OCTET *mType, MTP3_HEADER_ANSI *mtp3,
                       ITS_OCTET *buf, ITS_USHORT *len)
{
    return MTP3_Decode_ANSI(ev, mType, mtp3, buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_SendEvent_ANSI(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                    ITS_ISUP_IE_ANSI *ies, int ieCount,
                    ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendANSI == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendANSI)(inst,
                                                           type, hdr,
                                                           ies, ieCount,
                                                           desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an ISUP message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReceiveEvent_ANSI(ITS_HANDLE handl, ITS_EVENT *ev, ITS_HDR *hdr,
                       ITS_ISUP_IE_ANSI *ies, int *ieCount,
                       ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveANSI == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveANSI)(inst,
                                                              ev, hdr,
                                                              ies, ieCount,
                                                              desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a CIC.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReserveCIC_ANSI(ITS_HANDLE handl,
                      ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                      ITS_USHORT cic, ITS_OCTET *status, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic, status, ctxt);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Un Reserve the reserve CIC
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_UnReserveCIC_ANSI(ITS_HANDLE handl,
                      ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                      ITS_USHORT cic)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an SCCP message.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendEvent_ANSI(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                    ITS_SCCP_IE *ies, int ieCount,
                    SCCP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send)(inst,
                                                       type, hdr,
                                                       ies, ieCount,
                                                       desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an SCCP message
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                       ITS_SCCP_IE *ies, int *ieCount,
                       SCCP_MSG_DESC *desc)
{
    int ret;

    if ((ret = SCCP_Decode_ANSI(ies, ieCount, ev, desc)) != ITS_SUCCESS)
    {
        return (ret);
    }

    hdr->type = ITS_SCCP;
    hdr->context.conref = ITS_GET_CTXT(&ev->data[1]);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a local reference number.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
SCCP_GetNextLocalRef_ANSI(ITS_HANDLE handl, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef)(inst, ctxt);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem in service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserOutOfService_ANSI(ITS_HANDLE handl, ITS_OCTET ni,
                               ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem out of service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserInService_ANSI(ITS_HANDLE handl, ITS_OCTET ni,
                            ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set the congestion level of a subsystem.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendSetCongestion_ANSI(ITS_HANDLE handl, ITS_OCTET ni,
                            ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong)(inst, ni,
                                                       pc, ssn, cong);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendComponent_ANSI(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_ComponentSanityCheck_ANSI(cpt)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp)(inst, hdr, cpt);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP dialogue.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendDialogue_ANSI(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_DialogueSanityCheck_ANSI(dlg)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg)(inst, hdr, dlg);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveComponent_ANSI(ITS_HANDLE handle, ITS_EVENT *event,
                           ITS_HDR *hdr, TCAP_CPT *cpt)
{
    hdr->type = ITS_TCAP_ANSI;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP dialogue
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveDialogue_ANSI(ITS_HANDLE handle, ITS_EVENT *event,
                          ITS_HDR *hdr, TCAP_DLG *dlg)
{
    hdr->type = ITS_TCAP_ANSI;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(dlg, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_DLG));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_AllocateDialogueId_ANSI(ITS_HANDLE handl, ITS_CTXT* did)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID)(inst, did);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchAddrs_ANSI(ITS_HANDLE handl, ITS_CTXT did,
                     SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs)(inst, did,
                                                             oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetAddrs_ANSI(ITS_HANDLE handl, ITS_CTXT did,
                   SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs)(inst, did,
                                                           oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchQOS_ANSI(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS)(inst, did, qos);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetQOS_ANSI(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS)(inst, did, qos);
}

/******************************* IMPLEMENTATION *****************************/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize some class methods.
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
 ****************************************************************************/
static int
ClassInit_ANSI(ITS_Class objClass)
{
    /* add some formatters */
    PPrint_AddProc(PPRINT_TYPE_MTP2_LAYER, MTP2_TypePrint);
    PPrint_AddProc(PPRINT_TYPE_MTP3_LAYER, MTP3_TypePrint);
    PPrint_AddProc(PPRINT_TYPE_SNMM_LAYER, SNMM_TypePrint);
    PPrint_AddProc(PPRINT_TYPE_SLTM_LAYER, SLTM_TypePrint);
    PPrint_AddProc(PPRINT_TYPE_SCCP_LAYER, SCCP_TypePrint);
    PPrint_AddProc(PPRINT_TYPE_ISUP_LAYER, ISUP_TypePrint);
    PPrint_AddProc(PPRINT_TYPE_TCAP_LAYER, TCAP_TypePrint);

    /* Initialize SCCP and MTP3 callback Management */
    SCCP_ANSI_ManagementCallbacks = CALLBACK_InitManager();

    if (SCCP_ANSI_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        return (ITS_ENOMEM);
    }

    /* Initialize SCCP and MTP3 callback Management */
    ISUP_ANSI_ManagementCallbacks = CALLBACK_InitManager();

    if (ISUP_ANSI_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_ANSI_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    MTP3_ANSI_ManagementCallbacks = CALLBACK_InitManager();

    if (MTP3_ANSI_ManagementCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(ISUP_ANSI_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_ANSI_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_ANSI_GlobalTitleTranslator = CALLBACK_InitManager();

    if (SCCP_ANSI_GlobalTitleTranslator == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(MTP3_ANSI_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_ANSI_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_ANSI_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_ANSI_SSNRoutingCallbacks = CALLBACK_InitManager();

    if (SCCP_ANSI_SSNRoutingCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_ANSI_GlobalTitleTranslator);
        CALLBACK_DestroyManager(MTP3_ANSI_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_ANSI_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_ANSI_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the callback structs (if configuration applies)
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
 ****************************************************************************/
static void
ClassDestroy_ANSI(ITS_Class objClass)
{
    CALLBACK_DestroyManager(ISUP_ANSI_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_ANSI_ManagementCallbacks);
    CALLBACK_DestroyManager(MTP3_ANSI_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_ANSI_GlobalTitleTranslator);
    CALLBACK_DestroyManager(SCCP_ANSI_SSNRoutingCallbacks);

    PPrint_AddProc(PPRINT_TYPE_TCAP_LAYER, NULL);
    PPrint_AddProc(PPRINT_TYPE_ISUP_LAYER, NULL);
    PPrint_AddProc(PPRINT_TYPE_SCCP_LAYER, NULL);
    PPrint_AddProc(PPRINT_TYPE_SLTM_LAYER, NULL);
    PPrint_AddProc(PPRINT_TYPE_SNMM_LAYER, NULL);
    PPrint_AddProc(PPRINT_TYPE_MTP3_LAYER, NULL);
    PPrint_AddProc(PPRINT_TYPE_MTP2_LAYER, NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the TCAP layer, if applicable.
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
 ****************************************************************************/
static int
TCAP_Initialize_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_ANSI) == ITS_TCAP_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the TCAP layer, if applicable.
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
 ****************************************************************************/
static void
TCAP_Terminate_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_ANSI) == ITS_TCAP_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the SCCP layer, if applicable.
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
 ****************************************************************************/
static int
SCCP_Initialize_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_ANSI) == ITS_SCCP_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the SCCP layer, if applicable.
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
 ****************************************************************************/
static void
SCCP_Terminate_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_ANSI) == ITS_SCCP_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ISUP layer, if applicable.
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
 ****************************************************************************/
static int
ISUP_Initialize_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_ANSI) == ITS_ISUP_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the ISUP layer, if applicable.
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
 ****************************************************************************/
static void
ISUP_Terminate_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_ANSI) == ITS_ISUP_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP3 layer, if applicable.
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
 ****************************************************************************/
static int
MTP3_Initialize_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_ANSI) == ITS_MTP3_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP3 layer, if applicable.
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
 ****************************************************************************/
static void
MTP3_Terminate_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_ANSI) == ITS_MTP3_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP2 layer, if applicable.
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
 ****************************************************************************/
static int
MTP2_Initialize_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_ANSI) == ITS_MTP2_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP2 layer, if applicable.
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
 ****************************************************************************/
static void
MTP2_Terminate_ANSI(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_ANSI) == ITS_MTP2_ANSI)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      initialize the connections to both boards (if required)
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
 ****************************************************************************/
static int
SS7_Initialize_ANSI(ITS_Object obj, va_list args)
{
    SS7TRAN_Manager *ss7;
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;

    ss7 = va_arg(args, SS7TRAN_Manager *);

    VENDOR_OWNING_TRANSPORT(handle) = ss7;

    ITS_C_ASSERT(ss7 != NULL);

    if (TRANSPORT_MASK(ss7) & ITS_SS7_MASK)
    {
        int ret;

        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)(handle,
                                                        TRANSPORT_INSTANCE(ss7));
        }

        if ((ret = MTP2_Initialize_ANSI(ss7, handle)) != ITS_SUCCESS)
        {
            return (ret);
        }

        if ((ret = MTP3_Initialize_ANSI(ss7, handle)) != ITS_SUCCESS)
        {
            MTP2_Terminate_ANSI(ss7, handle);

            return (ret);
        }

        if ((ret = SCCP_Initialize_ANSI(ss7, handle)) != ITS_SUCCESS)
        {
            MTP3_Terminate_ANSI(ss7, handle);
            MTP2_Terminate_ANSI(ss7, handle);

            return (ret);
        }

        if ((ret = ISUP_Initialize_ANSI(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_ANSI(ss7, handle);
            MTP3_Terminate_ANSI(ss7, handle);
            MTP2_Terminate_ANSI(ss7, handle);

            return (ret);
        }

        if ((ret = TCAP_Initialize_ANSI(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_ANSI(ss7, handle);
            ISUP_Terminate_ANSI(ss7, handle);
            MTP3_Terminate_ANSI(ss7, handle);
            MTP2_Terminate_ANSI(ss7, handle);

            return (ret);
        }
    }

    if ((VENDOR_RCV_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_ANSI(ss7, handle);
        SCCP_Terminate_ANSI(ss7, handle);
        ISUP_Terminate_ANSI(ss7, handle);
        MTP3_Terminate_ANSI(ss7, handle);
        MTP2_Terminate_ANSI(ss7, handle);

        return (ITS_ENOMEM);
    }

    if ((VENDOR_SND_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_ANSI(ss7, handle);
        SCCP_Terminate_ANSI(ss7, handle);
        ISUP_Terminate_ANSI(ss7, handle);
        MTP3_Terminate_ANSI(ss7, handle);
        MTP2_Terminate_ANSI(ss7, handle);

        MQUEUE_Delete(VENDOR_RCV_Q(handle));

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the application
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
 ****************************************************************************/
static void
SS7_Terminate_ANSI(ITS_Object obj)
{
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;
    SS7TRAN_Manager *ss7 = VENDOR_OWNING_TRANSPORT(handle);

    MQUEUE_Delete(VENDOR_RCV_Q(ss7));
    MQUEUE_Delete(VENDOR_SND_Q(ss7));

    TCAP_Terminate_ANSI(ss7, handle);
    SCCP_Terminate_ANSI(ss7, handle);
    ISUP_Terminate_ANSI(ss7, handle);
    MTP3_Terminate_ANSI(ss7, handle);
    MTP2_Terminate_ANSI(ss7, handle);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the vendor.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static ITS_BOOLEAN
RetrieveMessage_ANSI(VENDOR_Instance *handle, ITS_EVENT *event,
                     int indic_flag)
{
    int len;
    ITS_EVENT *msg;

    if (indic_flag & EVENT_FROM_TCAP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_SCCP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_ISUP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP3)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP2)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)(handle);
        }
    }

    while (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                          (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);
                    
        if (event->src == ITS_MTP3_ANSI_SRC &&
            (MTP3_MSG_TYPE(event) == MTP3_MSG_PAUSE ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_RESUME ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_STATUS))
        {
            CALLBACK_CallCallbackList(MTP3_ANSI_ManagementCallbacks,
                                      NULL,    
                                      (ITS_POINTER)event);   
        }
        /*
         * there should be a clause here for handling SCCP management
         * messages as well.
         */
        else
        {
            return (ITS_FALSE);
        }
    }

    /*
     * if we get here there wasn't anything put on the queue that wasn't
     * managment related.
     */
    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the NMS board.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
SS7_GetNextEvent_ANSI(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_BOOLEAN cont = ITS_TRUE;
    ITS_EVENT *msg;
    int indic_flag, ret, len;
 
    if (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                       (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    while (cont &&
           !TRANSPORT_EXIT_NOW(((TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(handle))))
    {
        ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

        ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                           &indic_flag,
                                                           (int)HMI_GetTimeOutInterval());
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ENOMSG)
            {
                continue;
            }

            return (ret);
        }

        cont = RetrieveMessage_ANSI(handle, event, indic_flag);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
SS7_PeekNextEvent_ANSI(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_EVENT *msg;
    int len, ret;
    int indic_flag;

    if (!MQUEUE_EmptyP(VENDOR_RCV_Q(handle)))
    {
        MQUEUE_Dequeue(VENDOR_RCV_Q(handle), (void **)&msg, &len);

        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

    ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                       &indic_flag,
                                                       0);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    if (RetrieveMessage_ANSI(handle, event, indic_flag))
    {
        return (ITS_ENOMSG);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Put an event onto the transport.
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
 *      Depending on the configuration for this transport, this may mean
 *      that a synthetic event is put on the receive queue, or that an
 *      actual SS7 event is sent.
 *
 ****************************************************************************/
static int
SS7_PutEvent_ANSI(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_HDR hdr;
    ITS_OCTET mType = 0;
    int ieCount = 0;
    SS7_Transport tc;

    tc = VENDOR_OWNING_TRANSPORT(handle);

    /*
     * handle a TCAP message?
     */
    if (event->src == ITS_TCAP_ANSI_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_TCAP_ANSI) != ITS_TCAP_ANSI ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg == NULL ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp == NULL)
        {
            if ((TRANSPORT_MASK(tc) & ITS_SCCP_ANSI) != ITS_SCCP_ANSI ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }
            else
            {
                ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
                ITS_USHORT len;
                int ret;
                MTP3_HEADER_ANSI mtp3;
                ITS_SCCP_IE ies[10];
                SCCP_MSG_DESC* desc;

                if ((ret = MTP3_Decode_ANSI(event, &mType, &mtp3,
                                            buf, &len)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                if (mType != MTP3_MSG_USER_DATA)
                {
                    return (ITS_EINVALIDARGS);
                }

                mType = buf[0];
                desc = SCCP_GetDescriptor_ANSI(mType);

                if ((ret = SCCP_DecodeMTP3_ANSI(buf, len, &mType,
                                                ies, &ieCount, desc)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                hdr.type = ITS_SCCP_ANSI;
                hdr.context.ssn = 0;
                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                     &hdr,
                                                                     ies, ieCount,
                                                                     desc);
            }
        }
        else
        {
            hdr.type = ITS_TCAP_ANSI;
            hdr.context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

            if (TCAP_MSG_TYPE(event) == ITS_TCAP_DLG)
            {
                TCAP_DLG dlg;

                memcpy(&dlg,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_DLG));


                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg)(handle,
                                                                        &hdr,
                                                                        &dlg);
            }
            else if (TCAP_MSG_TYPE(event) == ITS_TCAP_CPT)
            {
                TCAP_CPT cpt;

                memcpy(&cpt,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_CPT));

                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp)(handle,
                                                                        &hdr,
                                                                        &cpt);
            }
        }
    }
    /*
     * handle and SCCP message?
     */
    else if (event->src == ITS_SCCP_ANSI_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_SCCP_ANSI) != ITS_SCCP_ANSI ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_ANSI mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_ANSI) != ITS_MTP3_ANSI ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendANSI == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_ANSI(event, &mType, &mtp3,
                                        buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendANSI)(handle,
                                                                     MTP3_MSG_USER_DATA,
                                                                     &mtp3,
                                                                     buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len;
            int ret;
            MTP3_HEADER_ANSI mtp3;
            ITS_SCCP_IE ies[10];
            SCCP_MSG_DESC* desc;

            if ((ret = MTP3_Decode_ANSI(event, &mType, &mtp3,
                                        buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];
            desc = SCCP_GetDescriptor_ANSI(mType);

            if ((ret = SCCP_DecodeMTP3_ANSI(buf, len, &mType,
                                            ies, &ieCount, desc)) != ITS_SUCCESS)
            {
                return (ret);
            }

            hdr.type = ITS_SCCP_ANSI;
            hdr.context.ssn = 0;

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                 &hdr,
                                                                 ies, ieCount,
                                                                 desc);
        }
    }
    /*
     * handle ISUP message?
     */
    else if (event->src == ITS_ISUP_ANSI_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_ISUP_ANSI) != ITS_ISUP_ANSI ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendANSI == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_ANSI mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_ANSI) != ITS_MTP3_ANSI ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendANSI == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_ANSI(event, &mType, &mtp3,
                                        buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendANSI)(handle,
                                                                     MTP3_MSG_USER_DATA,
                                                                     &mtp3,
                                                                     buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            int ret = 0;
            MTP3_HEADER_ANSI mtp3;
            ITS_ISUP_IE_ANSI ies[32];
            ISUP_MSG_DESC* desc = NULL;

            if ((ret = MTP3_Decode_ANSI(event, &mType, &mtp3,
                                        buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];

            hdr.type = ITS_ISUP;
            hdr.context.cic = ITS_GET_CTXT(&buf[1]);

            desc = ISUP_GetDescriptor_ANSI(mType);

            if ((ret = ISUP_DecodeMTP3_ANSI(ies, &ieCount, event, desc)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendANSI)(handle,
                                                                     mType,
                                                                     &hdr,
                                                                     ies,
                                                                     ieCount,
                                                                     desc);
        }
    }
    /*
     * handle MTP3 event?
     */
    else if (event->src == ITS_MTP3_ANSI_SRC)
    {
        ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
        ITS_USHORT len = 0;
        MTP3_HEADER_ANSI mtp3;
        int ret;

        if ((TRANSPORT_MASK(tc) & ITS_MTP3_ANSI) != ITS_MTP3_ANSI ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendANSI == NULL)
        {
            if ((TRANSPORT_MASK(tc) & ITS_MTP2_ANSI) != ITS_MTP2_ANSI ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                                 event->data,
                                                                 event->len);
        }
        else
        {
            if ((ret = MTP3_Decode_ANSI(event, &mType, &mtp3,
                                        buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendANSI)(handle,
                                                                     MTP3_MSG_USER_DATA,
                                                                     &mtp3,
                                                                     buf, len);
        }
    }
    /*
     * handle MTP2 event?
     */
    else if (event->src == ITS_MTP2_ANSI_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_MTP2_ANSI) != ITS_MTP2_ANSI ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                             event->data,
                                                             event->len);
    }

    return (ITS_SUCCESS);
}

SS7DLLAPI SS7STACK_ClassRec itsSS7STACK_ClassRecANSI =
{
    /* core */
    {
        NULL,                       /* superclass */
        0,                          /* instance size */
        ITS_FALSE,                  /* not initted */
        sizeof(VENDOR_Instance),    /* initial ref count */
        "SS7 Stack ANSI",           /* class name: replace with your vendor */
        ClassInit_ANSI,             /* no class init */
        ClassDestroy_ANSI,          /* no class dest */
        ClassPartInit,              /* class part init */
        ClassPartDest,              /* class part destroy */
        SS7_Initialize_ANSI,        /* instantiate */
        SS7_Terminate_ANSI,         /* destroy */
        NULL                        /* extension */
    },
    /* stack */
    {
        SS7_GetNextEvent_ANSI,      /* getNextEvent */
        SS7_PeekNextEvent_ANSI,     /* peekNextEvent */
        SS7_PutEvent_ANSI           /* putEvent */
    }
};

SS7DLLAPI ITS_Class itsSS7STACK_ClassANSI =
    (ITS_Class)&itsSS7STACK_ClassRecANSI;

/******************************* ITU VERSION *******************************/

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_SendEvent_CCITT(ITS_HANDLE handl,
                     ITS_OCTET type, MTP3_HEADER_CCITT *mtp3,
                     ITS_OCTET *buf, ITS_USHORT len)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendCCITT == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendCCITT)(inst,
                                                            type, mtp3,
                                                            buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_ReceiveEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                        ITS_OCTET *mType, MTP3_HEADER_CCITT *mtp3,
                        ITS_OCTET *buf, ITS_USHORT *len)
{
    return MTP3_Decode_CCITT(ev, mType, mtp3, buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_SendEvent_CCITT(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                     ITS_ISUP_IE_CCITT *ies, int ieCount,
                     ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendCCITT == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendCCITT)(inst,
                                                            type, hdr,
                                                            ies, ieCount,
                                                            desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an ISUP message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReceiveEvent_CCITT(ITS_HANDLE handl, ITS_EVENT *ev, ITS_HDR *hdr,
                        ITS_ISUP_IE_CCITT *ies, int *ieCount,
                        ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveCCITT == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveCCITT)(inst,
                                                               ev, hdr,
                                                               ies, ieCount,
                                                               desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a CIC.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReserveCIC_CCITT(ITS_HANDLE handl,
                       ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                       ITS_USHORT cic, ITS_OCTET *status, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic, status, ctxt);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Un Reserve the reserve CIC
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_UnReserveCIC_CCITT(ITS_HANDLE handl,
                      ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                      ITS_USHORT cic)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an SCCP message.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendEvent_CCITT(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                     ITS_SCCP_IE *ies, int ieCount,
                     SCCP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send)(inst,
                                                       type, hdr,
                                                       ies, ieCount,
                                                       desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an SCCP message
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                        ITS_SCCP_IE *ies, int *ieCount,
                        SCCP_MSG_DESC *desc)
{
    int ret;

    if ((ret = SCCP_Decode_CCITT(ies, ieCount, ev, desc)) != ITS_SUCCESS)
    {
        return (ret);
    }

    hdr->type = ITS_SCCP;
    hdr->context.conref = ITS_GET_CTXT(&ev->data[1]);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a local reference number.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
SCCP_GetNextLocalRef_CCITT(ITS_HANDLE handl, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef)(inst, ctxt);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem in service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserOutOfService_CCITT(ITS_HANDLE handl, ITS_OCTET ni,
                                ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem out of service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserInService_CCITT(ITS_HANDLE handl, ITS_OCTET ni,
                             ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set the congestion level of a subsystem.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendSetCongestion_CCITT(ITS_HANDLE handl, ITS_OCTET ni,
                             ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong)(inst, ni,
                                                       pc, ssn, cong);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendComponent_CCITT(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_ComponentSanityCheck_CCITT(cpt)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp)(inst, hdr, cpt);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP dialogue.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendDialogue_CCITT(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_DialogueSanityCheck_CCITT(dlg)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg)(inst, hdr, dlg);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveComponent_CCITT(ITS_HANDLE handle, ITS_EVENT *event,
                            ITS_HDR *hdr, TCAP_CPT *cpt)
{
    hdr->type = ITS_TCAP_CCITT;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP dialogue
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveDialogue_CCITT(ITS_HANDLE handle, ITS_EVENT *event,
                           ITS_HDR *hdr, TCAP_DLG *dlg)
{
    hdr->type = ITS_TCAP_CCITT;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(dlg, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_DLG));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_AllocateDialogueId_CCITT(ITS_HANDLE handl, ITS_CTXT* did)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID)(inst, did);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchAddrs_CCITT(ITS_HANDLE handl, ITS_CTXT did,
                      SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs)(inst, did,
                                                             oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetAddrs_CCITT(ITS_HANDLE handl, ITS_CTXT did,
                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs)(inst, did,
                                                           oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchQOS_CCITT(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS)(inst, did, qos);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetQOS_CCITT(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS)(inst, did, qos);
}

/******************************* IMPLEMENTATION *****************************/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize some class methods.
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
 ****************************************************************************/
static int
ClassInit_CCITT(ITS_Class objClass)
{
    /* Initialize SCCP and MTP3 callback Management */
    SCCP_CCITT_ManagementCallbacks = CALLBACK_InitManager();

    if (SCCP_CCITT_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        return (ITS_ENOMEM);
    }

    /* Initialize SCCP and MTP3 callback Management */
    ISUP_CCITT_ManagementCallbacks = CALLBACK_InitManager();

    if (ISUP_CCITT_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_CCITT_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    MTP3_CCITT_ManagementCallbacks = CALLBACK_InitManager();

    if (MTP3_CCITT_ManagementCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(ISUP_CCITT_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_CCITT_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_CCITT_GlobalTitleTranslator = CALLBACK_InitManager();

    if (SCCP_CCITT_GlobalTitleTranslator == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(MTP3_CCITT_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_CCITT_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_CCITT_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_CCITT_SSNRoutingCallbacks = CALLBACK_InitManager();

    if (SCCP_CCITT_SSNRoutingCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_CCITT_GlobalTitleTranslator);
        CALLBACK_DestroyManager(MTP3_CCITT_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_CCITT_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_CCITT_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the callback structs (if configuration applies)
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
 ****************************************************************************/
static void
ClassDestroy_CCITT(ITS_Class objClass)
{
    CALLBACK_DestroyManager(ISUP_CCITT_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_CCITT_ManagementCallbacks);
    CALLBACK_DestroyManager(MTP3_CCITT_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_CCITT_GlobalTitleTranslator);
    CALLBACK_DestroyManager(SCCP_CCITT_SSNRoutingCallbacks);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the TCAP layer, if applicable.
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
 ****************************************************************************/
static int
TCAP_Initialize_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_CCITT) == ITS_TCAP_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the TCAP layer, if applicable.
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
 ****************************************************************************/
static void
TCAP_Terminate_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_CCITT) == ITS_TCAP_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the SCCP layer, if applicable.
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
 ****************************************************************************/
static int
SCCP_Initialize_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_CCITT) == ITS_SCCP_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the SCCP layer, if applicable.
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
 ****************************************************************************/
static void
SCCP_Terminate_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_CCITT) == ITS_SCCP_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ISUP layer, if applicable.
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
 ****************************************************************************/
static int
ISUP_Initialize_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_CCITT) == ITS_ISUP_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the ISUP layer, if applicable.
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
 ****************************************************************************/
static void
ISUP_Terminate_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_CCITT) == ITS_ISUP_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP3 layer, if applicable.
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
 ****************************************************************************/
static int
MTP3_Initialize_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_CCITT) == ITS_MTP3_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP3 layer, if applicable.
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
 ****************************************************************************/
static void
MTP3_Terminate_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_CCITT) == ITS_MTP3_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP2 layer, if applicable.
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
 ****************************************************************************/
static int
MTP2_Initialize_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_CCITT) == ITS_MTP2_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP2 layer, if applicable.
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
 ****************************************************************************/
static void
MTP2_Terminate_CCITT(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_CCITT) == ITS_MTP2_CCITT)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      initialize the connections to both boards (if required)
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
 ****************************************************************************/
static int
SS7_Initialize_CCITT(ITS_Object obj, va_list args)
{
    SS7TRAN_Manager *ss7;
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;

    ss7 = va_arg(args, SS7TRAN_Manager *);

    VENDOR_OWNING_TRANSPORT(handle) = ss7;

    ITS_C_ASSERT(ss7 != NULL);

    /* initialize the NMS software */
    if (TRANSPORT_MASK(ss7) & ITS_SS7_MASK)
    {
        int ret;

        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)(handle,
                                                        TRANSPORT_INSTANCE(ss7));
        }

        if ((ret = MTP2_Initialize_CCITT(ss7, handle)) != ITS_SUCCESS)
        {
            return (ret);
        }

        if ((ret = MTP3_Initialize_CCITT(ss7, handle)) != ITS_SUCCESS)
        {
            MTP2_Terminate_CCITT(ss7, handle);

            return (ret);
        }

        if ((ret = SCCP_Initialize_CCITT(ss7, handle)) != ITS_SUCCESS)
        {
            MTP3_Terminate_CCITT(ss7, handle);
            MTP2_Terminate_CCITT(ss7, handle);

            return (ret);
        }

        if ((ret = ISUP_Initialize_CCITT(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_CCITT(ss7, handle);
            MTP3_Terminate_CCITT(ss7, handle);
            MTP2_Terminate_CCITT(ss7, handle);

            return (ret);
        }

        if ((ret = TCAP_Initialize_CCITT(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_CCITT(ss7, handle);
            ISUP_Terminate_CCITT(ss7, handle);
            MTP3_Terminate_CCITT(ss7, handle);
            MTP2_Terminate_CCITT(ss7, handle);

            return (ret);
        }
    }

    if ((VENDOR_RCV_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_CCITT(ss7, handle);
        SCCP_Terminate_CCITT(ss7, handle);
        ISUP_Terminate_CCITT(ss7, handle);
        MTP3_Terminate_CCITT(ss7, handle);
        MTP2_Terminate_CCITT(ss7, handle);

        return (ITS_ENOMEM);
    }

    if ((VENDOR_SND_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_CCITT(ss7, handle);
        SCCP_Terminate_CCITT(ss7, handle);
        ISUP_Terminate_CCITT(ss7, handle);
        MTP3_Terminate_CCITT(ss7, handle);
        MTP2_Terminate_CCITT(ss7, handle);

        MQUEUE_Delete(VENDOR_RCV_Q(handle));

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the application
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
 ****************************************************************************/
static void
SS7_Terminate_CCITT(ITS_Object obj)
{
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;
    SS7TRAN_Manager *ss7 = VENDOR_OWNING_TRANSPORT(handle);

    MQUEUE_Delete(VENDOR_RCV_Q(ss7));
    MQUEUE_Delete(VENDOR_SND_Q(ss7));

    TCAP_Terminate_CCITT(ss7, handle);
    SCCP_Terminate_CCITT(ss7, handle);
    ISUP_Terminate_CCITT(ss7, handle);
    MTP3_Terminate_CCITT(ss7, handle);
    MTP2_Terminate_CCITT(ss7, handle);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the vendor.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static ITS_BOOLEAN
RetrieveMessage_CCITT(VENDOR_Instance *handle, ITS_EVENT *event,
                     int indic_flag)
{
    int len;
    ITS_EVENT *msg;

    if (indic_flag & EVENT_FROM_TCAP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_SCCP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_ISUP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP3)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP2)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)(handle);
        }
    }

    while (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                          (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);
                    
        if (event->src == ITS_MTP3_CCITT_SRC &&
            (MTP3_MSG_TYPE(event) == MTP3_MSG_PAUSE ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_RESUME ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_STATUS))
        {
            CALLBACK_CallCallbackList(MTP3_CCITT_ManagementCallbacks,
                                      NULL,    
                                      (ITS_POINTER)event);   
        }
        /*
         * there should be a clause here for handling SCCP management
         * messages as well.
         */
        else
        {
            return (ITS_FALSE);
        }
    }

    /*
     * if we get here there wasn't anything put on the queue that wasn't
     * managment related.
     */
    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the NMS board.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
SS7_GetNextEvent_CCITT(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_BOOLEAN cont = ITS_TRUE;
    ITS_EVENT *msg;
    int indic_flag, ret, len;
 
    if (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                       (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    while (cont &&
           !TRANSPORT_EXIT_NOW(((TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(handle))))
    {
        ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

        ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                           &indic_flag,
                                                           (int)HMI_GetTimeOutInterval());
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ENOMSG)
            {
                continue;
            }

            return (ret);
        }

        cont = RetrieveMessage_CCITT(handle, event, indic_flag);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
SS7_PeekNextEvent_CCITT(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_EVENT *msg;
    int len, ret;
    int indic_flag;

    if (!MQUEUE_EmptyP(VENDOR_RCV_Q(handle)))
    {
        MQUEUE_Dequeue(VENDOR_RCV_Q(handle), (void **)&msg, &len);

        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

    ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                       &indic_flag,
                                                       0);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    if (RetrieveMessage_CCITT(handle, event, indic_flag))
    {
        return (ITS_ENOMSG);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Put an event onto the transport.
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
 *      Depending on the configuration for this transport, this may mean
 *      that a synthetic event is put on the receive queue, or that an
 *      actual SS7 event is sent.
 *
 ****************************************************************************/
static int
SS7_PutEvent_CCITT(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_HDR hdr;
    ITS_OCTET mType = 0;
    int ieCount = 0;
    SS7_Transport tc;

    tc = VENDOR_OWNING_TRANSPORT(handle);

    /*
     * handle a TCAP message?
     */
    if (event->src == ITS_TCAP_CCITT_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_TCAP_CCITT) != ITS_TCAP_CCITT ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg == NULL ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp == NULL)
        {
            if ((TRANSPORT_MASK(tc) & ITS_SCCP_CCITT) != ITS_SCCP_CCITT ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }
            else
            {
                ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
                ITS_USHORT len;
                int ret;
                MTP3_HEADER_CCITT mtp3;
                ITS_SCCP_IE ies[10];
                SCCP_MSG_DESC* desc;

                if ((ret = MTP3_Decode_CCITT(event, &mType, &mtp3,
                                             buf, &len)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                if (mType != MTP3_MSG_USER_DATA)
                {
                    return (ITS_EINVALIDARGS);
                }

                mType = buf[0];
                desc = SCCP_GetDescriptor_CCITT(mType);

                if ((ret = SCCP_DecodeMTP3_CCITT(buf, len, &mType,
                                                 ies, &ieCount, desc)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                hdr.type = ITS_SCCP_CCITT;
                hdr.context.ssn = 0;
                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                     &hdr,
                                                                     ies, ieCount,
                                                                     desc);
            }
        }
        else
        {
            hdr.type = ITS_TCAP_CCITT;
            hdr.context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

            if (TCAP_MSG_TYPE(event) == ITS_TCAP_DLG)
            {
                TCAP_DLG dlg;

                memcpy(&dlg,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_DLG));


                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg)(handle,
                                                                        &hdr,
                                                                        &dlg);
            }
            else if (TCAP_MSG_TYPE(event) == ITS_TCAP_CPT)
            {
                TCAP_CPT cpt;

                memcpy(&cpt,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_CPT));

                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp)(handle,
                                                                        &hdr,
                                                                        &cpt);
            }
        }
    }
    /*
     * handle and SCCP message?
     */
    else if (event->src == ITS_SCCP_CCITT_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_SCCP_CCITT) != ITS_SCCP_CCITT ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_CCITT mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_CCITT) != ITS_MTP3_CCITT ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendCCITT == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_CCITT(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendCCITT)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len;
            int ret;
            MTP3_HEADER_CCITT mtp3;
            ITS_SCCP_IE ies[10];
            SCCP_MSG_DESC* desc;

            if ((ret = MTP3_Decode_CCITT(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];
            desc = SCCP_GetDescriptor_CCITT(mType);

            if ((ret = SCCP_DecodeMTP3_CCITT(buf, len, &mType,
                                            ies, &ieCount, desc)) != ITS_SUCCESS)
            {
                return (ret);
            }

            hdr.type = ITS_SCCP_CCITT;
            hdr.context.ssn = 0;

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                 &hdr,
                                                                 ies, ieCount,
                                                                 desc);
        }
    }
    /*
     * handle ISUP message?
     */
    else if (event->src == ITS_ISUP_CCITT_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_ISUP_CCITT) != ITS_ISUP_CCITT ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendCCITT == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_CCITT mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_CCITT) != ITS_MTP3_CCITT ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendCCITT == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_CCITT(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendCCITT)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            int ret = 0;
            MTP3_HEADER_CCITT mtp3;
            ITS_ISUP_IE_CCITT ies[32];
            ISUP_MSG_DESC* desc = NULL;

            if ((ret = MTP3_Decode_CCITT(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];

            hdr.type = ITS_ISUP;
            hdr.context.cic = ITS_GET_CTXT(&buf[1]);

            desc = ISUP_GetDescriptor_CCITT(mType);

            if ((ret = ISUP_DecodeMTP3_CCITT(ies, &ieCount, event, desc)) !=
                ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendCCITT)(handle,
                                                                      mType,
                                                                      &hdr,
                                                                      ies,
                                                                      ieCount,
                                                                      desc);
        }
    }
    /*
     * handle MTP3 event?
     */
    else if (event->src == ITS_MTP3_CCITT_SRC)
    {
        ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
        ITS_USHORT len = 0;
        MTP3_HEADER_CCITT mtp3;
        int ret;

        if ((TRANSPORT_MASK(tc) & ITS_MTP3_CCITT) != ITS_MTP3_CCITT ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendCCITT == NULL)
        {
            if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                                 event->data,
                                                                 event->len);
        }
        else
        {
            if ((ret = MTP3_Decode_CCITT(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendCCITT)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
    }
    /*
     * handle MTP2 event?
     */
    else if (event->src == ITS_MTP2_CCITT_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_MTP2_CCITT) != ITS_MTP2_CCITT ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                             event->data,
                                                             event->len);
    }

    return (ITS_SUCCESS);
}

SS7DLLAPI SS7STACK_ClassRec itsSS7STACK_ClassRecCCITT =
{
    /* core */
    {
        NULL,                       /* superclass */
        0,                          /* instance size */
        ITS_FALSE,                  /* not initted */
        sizeof(VENDOR_Instance),    /* initial ref count */
        "SS7 Stack CCITT",          /* class name: replace with your vendor */
        ClassInit_CCITT,            /* no class init */
        ClassDestroy_CCITT,         /* no class dest */
        ClassPartInit,              /* class part init */
        ClassPartDest,              /* class part destroy */
        SS7_Initialize_CCITT,       /* instantiate */
        SS7_Terminate_CCITT,        /* destroy */
        NULL                        /* extension */
    },
    /* stack */
    {
        SS7_GetNextEvent_CCITT,     /* getNextEvent */
        SS7_PeekNextEvent_CCITT,    /* peekNextEvent */
        SS7_PutEvent_CCITT          /* putEvent */
    }
};

SS7DLLAPI ITS_Class itsSS7STACK_ClassCCITT =
    (ITS_Class)&itsSS7STACK_ClassRecCCITT;

/******************************* PRC VERSION *******************************/

#if !defined(SPLIT_STACK)

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_SendEvent_PRC(ITS_HANDLE handl,
                   ITS_OCTET type, MTP3_HEADER_PRC *mtp3,
                   ITS_OCTET *buf, ITS_USHORT len)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendPRC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendPRC)(inst,
                                                          type, mtp3,
                                                          buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_ReceiveEvent_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                      ITS_OCTET *mType, MTP3_HEADER_PRC *mtp3,
                      ITS_OCTET *buf, ITS_USHORT *len)
{
    return MTP3_Decode_PRC(ev, mType, mtp3, buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_SendEvent_PRC(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                   ITS_ISUP_IE_CCITT *ies, int ieCount,
                   ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendCCITT == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendCCITT)(inst,
                                                            type, hdr,
                                                            ies, ieCount,
                                                            desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an ISUP message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReceiveEvent_PRC(ITS_HANDLE handl, ITS_EVENT *ev, ITS_HDR *hdr,
                      ITS_ISUP_IE_CCITT *ies, int *ieCount,
                      ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveCCITT == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveCCITT)(inst,
                                                               ev, hdr,
                                                               ies, ieCount,
                                                               desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a CIC.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReserveCIC_PRC(ITS_HANDLE handl,
                     ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                     ITS_USHORT cic, ITS_OCTET *status, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic, status, ctxt);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Un Reserve CIC
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_UnReserveCIC_PRC(ITS_HANDLE handl,
                     ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                     ITS_USHORT cic)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an SCCP message.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendEvent_PRC(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                   ITS_SCCP_IE *ies, int ieCount,
                   SCCP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send)(inst,
                                                       type, hdr,
                                                       ies, ieCount,
                                                       desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an SCCP message
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveEvent_PRC(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                      ITS_SCCP_IE *ies, int *ieCount,
                      SCCP_MSG_DESC *desc)
{
    int ret;

    if ((ret = SCCP_Decode_PRC(ies, ieCount, ev, desc)) != ITS_SUCCESS)
    {
        return (ret);
    }

    hdr->type = ITS_SCCP;
    hdr->context.conref = ITS_GET_CTXT(&ev->data[1]);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a local reference number.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
SCCP_GetNextLocalRef_PRC(ITS_HANDLE handl, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef)(inst, ctxt);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem in service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserOutOfService_PRC(ITS_HANDLE handl, ITS_OCTET ni,
                              ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem out of service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserInService_PRC(ITS_HANDLE handl, ITS_OCTET ni,
                           ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set the congestion level of a subsystem.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendSetCongestion_PRC(ITS_HANDLE handl, ITS_OCTET ni,
                           ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong)(inst, ni,
                                                       pc, ssn, cong);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendComponent_PRC(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_ComponentSanityCheck_PRC(cpt)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp)(inst, hdr, cpt);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP dialogue.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendDialogue_PRC(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_DialogueSanityCheck_PRC(dlg)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg)(inst, hdr, dlg);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveComponent_PRC(ITS_HANDLE handle, ITS_EVENT *event,
                          ITS_HDR *hdr, TCAP_CPT *cpt)
{
    hdr->type = ITS_TCAP_PRC;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP dialogue
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveDialogue_PRC(ITS_HANDLE handle, ITS_EVENT *event,
                         ITS_HDR *hdr, TCAP_DLG *dlg)
{
    hdr->type = ITS_TCAP_PRC;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(dlg, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_DLG));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_AllocateDialogueId_PRC(ITS_HANDLE handl, ITS_CTXT* did)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID)(inst, did);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchAddrs_PRC(ITS_HANDLE handl, ITS_CTXT did,
                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs)(inst, did,
                                                             oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetAddrs_PRC(ITS_HANDLE handl, ITS_CTXT did,
                  SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs)(inst, did,
                                                           oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchQOS_PRC(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS)(inst, did, qos);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetQOS_PRC(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS)(inst, did, qos);
}

/******************************* IMPLEMENTATION *****************************/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize some class methods.
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
 ****************************************************************************/
static int
ClassInit_PRC(ITS_Class objClass)
{
    /* Initialize SCCP and MTP3 callback Management */
    SCCP_PRC_ManagementCallbacks = CALLBACK_InitManager();

    if (SCCP_PRC_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        return (ITS_ENOMEM);
    }

    /* Initialize SCCP and MTP3 callback Management */
    ISUP_PRC_ManagementCallbacks = CALLBACK_InitManager();

    if (ISUP_PRC_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_PRC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    MTP3_PRC_ManagementCallbacks = CALLBACK_InitManager();

    if (MTP3_PRC_ManagementCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(ISUP_PRC_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_PRC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_PRC_GlobalTitleTranslator = CALLBACK_InitManager();

    if (SCCP_PRC_GlobalTitleTranslator == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(MTP3_PRC_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_PRC_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_PRC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_PRC_SSNRoutingCallbacks = CALLBACK_InitManager();

    if (SCCP_PRC_SSNRoutingCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_PRC_GlobalTitleTranslator);
        CALLBACK_DestroyManager(MTP3_PRC_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_PRC_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_PRC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the callback structs (if configuration applies)
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
 ****************************************************************************/
static void
ClassDestroy_PRC(ITS_Class objClass)
{
    CALLBACK_DestroyManager(ISUP_PRC_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_PRC_ManagementCallbacks);
    CALLBACK_DestroyManager(MTP3_PRC_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_PRC_GlobalTitleTranslator);
    CALLBACK_DestroyManager(SCCP_PRC_SSNRoutingCallbacks);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the TCAP layer, if applicable.
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
 ****************************************************************************/
static int
TCAP_Initialize_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_PRC) == ITS_TCAP_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the TCAP layer, if applicable.
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
 ****************************************************************************/
static void
TCAP_Terminate_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_PRC) == ITS_TCAP_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the SCCP layer, if applicable.
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
 ****************************************************************************/
static int
SCCP_Initialize_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_PRC) == ITS_SCCP_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the SCCP layer, if applicable.
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
 ****************************************************************************/
static void
SCCP_Terminate_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_PRC) == ITS_SCCP_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ISUP layer, if applicable.
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
 ****************************************************************************/
static int
ISUP_Initialize_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_PRC) == ITS_ISUP_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the ISUP layer, if applicable.
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
 ****************************************************************************/
static void
ISUP_Terminate_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_PRC) == ITS_ISUP_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP3 layer, if applicable.
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
 ****************************************************************************/
static int
MTP3_Initialize_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_PRC) == ITS_MTP3_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP3 layer, if applicable.
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
 ****************************************************************************/
static void
MTP3_Terminate_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_PRC) == ITS_MTP3_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP2 layer, if applicable.
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
 ****************************************************************************/
static int
MTP2_Initialize_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_PRC) == ITS_MTP2_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP2 layer, if applicable.
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
 ****************************************************************************/
static void
MTP2_Terminate_PRC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_PRC) == ITS_MTP2_PRC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      initialize the connections to both boards (if required)
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
 ****************************************************************************/
static int
SS7_Initialize_PRC(ITS_Object obj, va_list args)
{
    SS7TRAN_Manager *ss7;
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;

    ss7 = va_arg(args, SS7TRAN_Manager *);

    VENDOR_OWNING_TRANSPORT(handle) = ss7;

    ITS_C_ASSERT(ss7 != NULL);

    /* initialize the NMS software */
    if (TRANSPORT_MASK(ss7) & ITS_SS7_MASK)
    {
        int ret;

        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)(handle,
                                                        TRANSPORT_INSTANCE(ss7));
        }

        if ((ret = MTP2_Initialize_PRC(ss7, handle)) != ITS_SUCCESS)
        {
            return (ret);
        }

        if ((ret = MTP3_Initialize_PRC(ss7, handle)) != ITS_SUCCESS)
        {
            MTP2_Terminate_PRC(ss7, handle);

            return (ret);
        }

        if ((ret = SCCP_Initialize_PRC(ss7, handle)) != ITS_SUCCESS)
        {
            MTP3_Terminate_PRC(ss7, handle);
            MTP2_Terminate_PRC(ss7, handle);

            return (ret);
        }

        if ((ret = ISUP_Initialize_PRC(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_PRC(ss7, handle);
            MTP3_Terminate_PRC(ss7, handle);
            MTP2_Terminate_PRC(ss7, handle);

            return (ret);
        }

        if ((ret = TCAP_Initialize_PRC(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_PRC(ss7, handle);
            ISUP_Terminate_PRC(ss7, handle);
            MTP3_Terminate_PRC(ss7, handle);
            MTP2_Terminate_PRC(ss7, handle);

            return (ret);
        }
    }

    if ((VENDOR_RCV_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_PRC(ss7, handle);
        SCCP_Terminate_PRC(ss7, handle);
        ISUP_Terminate_PRC(ss7, handle);
        MTP3_Terminate_PRC(ss7, handle);
        MTP2_Terminate_PRC(ss7, handle);

        return (ITS_ENOMEM);
    }

    if ((VENDOR_SND_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_PRC(ss7, handle);
        SCCP_Terminate_PRC(ss7, handle);
        ISUP_Terminate_PRC(ss7, handle);
        MTP3_Terminate_PRC(ss7, handle);
        MTP2_Terminate_PRC(ss7, handle);

        MQUEUE_Delete(VENDOR_RCV_Q(handle));

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the application
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
 ****************************************************************************/
static void
SS7_Terminate_PRC(ITS_Object obj)
{
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;
    SS7TRAN_Manager *ss7 = VENDOR_OWNING_TRANSPORT(handle);

    MQUEUE_Delete(VENDOR_RCV_Q(ss7));
    MQUEUE_Delete(VENDOR_SND_Q(ss7));

    TCAP_Terminate_PRC(ss7, handle);
    SCCP_Terminate_PRC(ss7, handle);
    ISUP_Terminate_PRC(ss7, handle);
    MTP3_Terminate_PRC(ss7, handle);
    MTP2_Terminate_PRC(ss7, handle);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the vendor.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static ITS_BOOLEAN
RetrieveMessage_PRC(VENDOR_Instance *handle, ITS_EVENT *event,
                     int indic_flag)
{
    int len;
    ITS_EVENT *msg;

    if (indic_flag & EVENT_FROM_TCAP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_SCCP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_ISUP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP3)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP2)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)(handle);
        }
    }

    while (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                          (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);
                    
        if (event->src == ITS_MTP3_PRC_SRC &&
            (MTP3_MSG_TYPE(event) == MTP3_MSG_PAUSE ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_RESUME ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_STATUS))
        {
            CALLBACK_CallCallbackList(MTP3_PRC_ManagementCallbacks,
                                      NULL,    
                                      (ITS_POINTER)event);   
        }
        /*
         * there should be a clause here for handling SCCP management
         * messages as well.
         */
        else
        {
            return (ITS_FALSE);
        }
    }

    /*
     * if we get here there wasn't anything put on the queue that wasn't
     * managment related.
     */
    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the NMS board.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
SS7_GetNextEvent_PRC(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_BOOLEAN cont = ITS_TRUE;
    ITS_EVENT *msg;
    int indic_flag, ret, len;
 
    if (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                       (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    while (cont &&
           !TRANSPORT_EXIT_NOW(((TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(handle))))
    {
        ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

        ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                           &indic_flag,
                                                           (int)HMI_GetTimeOutInterval());
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ENOMSG)
            {
                continue;
            }

            return (ret);
        }

        cont = RetrieveMessage_PRC(handle, event, indic_flag);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
SS7_PeekNextEvent_PRC(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_EVENT *msg;
    int len, ret;
    int indic_flag;

    if (!MQUEUE_EmptyP(VENDOR_RCV_Q(handle)))
    {
        MQUEUE_Dequeue(VENDOR_RCV_Q(handle), (void **)&msg, &len);

        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

    ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                       &indic_flag,
                                                       0);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    if (RetrieveMessage_PRC(handle, event, indic_flag))
    {
        return (ITS_ENOMSG);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Put an event onto the transport.
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
 *      Depending on the configuration for this transport, this may mean
 *      that a synthetic event is put on the receive queue, or that an
 *      actual SS7 event is sent.
 *
 ****************************************************************************/
static int
SS7_PutEvent_PRC(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_HDR hdr;
    ITS_OCTET mType = 0;
    int ieCount = 0;
    SS7_Transport tc;

    tc = VENDOR_OWNING_TRANSPORT(handle);

    /*
     * handle a TCAP message?
     */
    if (event->src == ITS_TCAP_PRC_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_TCAP_PRC) != ITS_TCAP_PRC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg == NULL ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp == NULL)
        {
            if ((TRANSPORT_MASK(tc) & ITS_SCCP_PRC) != ITS_SCCP_PRC ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }
            else
            {
                ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
                ITS_USHORT len;
                int ret;
                MTP3_HEADER_PRC mtp3;
                ITS_SCCP_IE ies[10];
                SCCP_MSG_DESC* desc;

                if ((ret = MTP3_Decode_PRC(event, &mType, &mtp3,
                                             buf, &len)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                if (mType != MTP3_MSG_USER_DATA)
                {
                    return (ITS_EINVALIDARGS);
                }

                mType = buf[0];
                desc = SCCP_GetDescriptor_PRC(mType);

                if ((ret = SCCP_DecodeMTP3_PRC(buf, len, &mType,
                                                 ies, &ieCount, desc)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                hdr.type = ITS_SCCP_PRC;
                hdr.context.ssn = 0;
                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                     &hdr,
                                                                     ies, ieCount,
                                                                     desc);
            }
        }
        else
        {
            hdr.type = ITS_TCAP_PRC;
            hdr.context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

            if (TCAP_MSG_TYPE(event) == ITS_TCAP_DLG)
            {
                TCAP_DLG dlg;

                memcpy(&dlg,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_DLG));


                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg)(handle,
                                                                        &hdr,
                                                                        &dlg);
            }
            else if (TCAP_MSG_TYPE(event) == ITS_TCAP_CPT)
            {
                TCAP_CPT cpt;

                memcpy(&cpt,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_CPT));

                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp)(handle,
                                                                        &hdr,
                                                                        &cpt);
            }
        }
    }
    /*
     * handle and SCCP message?
     */
    else if (event->src == ITS_SCCP_PRC_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_SCCP_PRC) != ITS_SCCP_PRC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_PRC mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_PRC) != ITS_MTP3_PRC ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendPRC == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_PRC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendPRC)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len;
            int ret;
            MTP3_HEADER_PRC mtp3;
            ITS_SCCP_IE ies[10];
            SCCP_MSG_DESC* desc;

            if ((ret = MTP3_Decode_PRC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];
            desc = SCCP_GetDescriptor_PRC(mType);

            if ((ret = SCCP_DecodeMTP3_PRC(buf, len, &mType,
                                            ies, &ieCount, desc)) != ITS_SUCCESS)
            {
                return (ret);
            }

            hdr.type = ITS_SCCP_PRC;
            hdr.context.ssn = 0;

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                 &hdr,
                                                                 ies, ieCount,
                                                                 desc);
        }
    }
    /*
     * handle ISUP message?
     */
    else if (event->src == ITS_ISUP_PRC_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_ISUP_PRC) != ITS_ISUP_PRC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendCCITT == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_PRC mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_PRC) != ITS_MTP3_PRC ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendPRC == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_PRC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendPRC)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            int ret = 0;
            MTP3_HEADER_PRC mtp3;
            ITS_ISUP_IE_CCITT ies[32];
            ISUP_MSG_DESC* desc = NULL;

            if ((ret = MTP3_Decode_PRC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];

            hdr.type = ITS_ISUP;
            hdr.context.cic = ITS_GET_CTXT(&buf[1]);

            desc = ISUP_GetDescriptor_CCITT(mType);

            if ((ret = ISUP_DecodeMTP3_CCITT(ies, &ieCount, event, desc)) !=
                ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendCCITT)(handle,
                                                                      mType,
                                                                      &hdr,
                                                                      ies,
                                                                      ieCount,
                                                                      desc);
        }
    }
    /*
     * handle MTP3 event?
     */
    else if (event->src == ITS_MTP3_PRC_SRC)
    {
        ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
        ITS_USHORT len = 0;
        MTP3_HEADER_PRC mtp3;
        int ret;

        if ((TRANSPORT_MASK(tc) & ITS_MTP3_PRC) != ITS_MTP3_PRC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendPRC == NULL)
        {
            if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                                 event->data,
                                                                 event->len);
        }
        else
        {
            if ((ret = MTP3_Decode_PRC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendPRC)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
    }
    /*
     * handle MTP2 event?
     */
    else if (event->src == ITS_MTP2_PRC_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_MTP2_PRC) != ITS_MTP2_PRC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                             event->data,
                                                             event->len);
    }

    return (ITS_SUCCESS);
}

SS7DLLAPI SS7STACK_ClassRec itsSS7STACK_ClassRecPRC =
{
    /* core */
    {
        NULL,                       /* superclass */
        0,                          /* instance size */
        ITS_FALSE,                  /* not initted */
        sizeof(VENDOR_Instance),    /* initial ref count */
        "SS7 Stack PRC",          /* class name: replace with your vendor */
        ClassInit_PRC,            /* no class init */
        ClassDestroy_PRC,         /* no class dest */
        ClassPartInit,              /* class part init */
        ClassPartDest,              /* class part destroy */
        SS7_Initialize_PRC,       /* instantiate */
        SS7_Terminate_PRC,        /* destroy */
        NULL                        /* extension */
    },
    /* stack */
    {
        SS7_GetNextEvent_PRC,     /* getNextEvent */
        SS7_PeekNextEvent_PRC,    /* peekNextEvent */
        SS7_PutEvent_PRC          /* putEvent */
    }
};

SS7DLLAPI ITS_Class itsSS7STACK_ClassPRC =
    (ITS_Class)&itsSS7STACK_ClassRecPRC;


/******************************* TTC VERSION *******************************/


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_SendEvent_TTC(ITS_HANDLE handl,
                   ITS_OCTET type, MTP3_HEADER_TTC *mtp3,
                   ITS_OCTET *buf, ITS_USHORT len)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendTTC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).mtp3.sendTTC)(inst,
                                                          type, mtp3,
                                                          buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
MTP3_ReceiveEvent_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                      ITS_OCTET *mType, MTP3_HEADER_TTC *mtp3,
                      ITS_OCTET *buf, ITS_USHORT *len)
{
    return MTP3_Decode_TTC(ev, mType, mtp3, buf, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an MTP3 message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_SendEvent_TTC(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                   ITS_ISUP_IE_CCITT *ies, int ieCount,
                   ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendCCITT == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.sendCCITT)(inst,
                                                            type, hdr,
                                                            ies, ieCount,
                                                            desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an ISUP message
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
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReceiveEvent_TTC(ITS_HANDLE handl, ITS_EVENT *ev, ITS_HDR *hdr,
                      ITS_ISUP_IE_CCITT *ies, int *ieCount,
                      ISUP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveCCITT == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.receiveCCITT)(inst,
                                                               ev, hdr,
                                                               ies, ieCount,
                                                               desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a CIC.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReserveCIC_TTC(ITS_HANDLE handl,
                     ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                     ITS_USHORT cic, ITS_OCTET *status, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.getCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic, status, ctxt);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Un Reserve CIC
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_UnReserveCIC_TTC(ITS_HANDLE handl,
                     ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                     ITS_USHORT cic)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).isup.unreserveCIC)(inst,
                                                         sio, opc, dpc,
                                                         cic);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send an SCCP message.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendEvent_TTC(ITS_HANDLE handl, ITS_OCTET type, ITS_HDR *hdr,
                   ITS_SCCP_IE *ies, int ieCount,
                   SCCP_MSG_DESC *desc)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.send)(inst,
                                                       type, hdr,
                                                       ies, ieCount,
                                                       desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive an SCCP message
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_ReceiveEvent_TTC(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                      ITS_SCCP_IE *ies, int *ieCount,
                      SCCP_MSG_DESC *desc)
{
    int ret;

    if ((ret = SCCP_Decode_TTC(ies, ieCount, ev, desc)) != ITS_SUCCESS)
    {
        return (ret);
    }

    hdr->type = ITS_SCCP;
    hdr->context.conref = ITS_GET_CTXT(&ev->data[1]);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a local reference number.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
SCCP_GetNextLocalRef_TTC(ITS_HANDLE handl, ITS_CTXT* ctxt)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.getRef)(inst, ctxt);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem in service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserOutOfService_TTC(ITS_HANDLE handl, ITS_OCTET ni,
                              ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.oos)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set a subsystem out of service.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendUserInService_TTC(ITS_HANDLE handl, ITS_OCTET ni,
                           ITS_UINT pc, ITS_OCTET ssn)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.is)(inst, ni, pc, ssn);
}

/*.implementation:external
 ****************************************************************************
 *  Purpose:
 *      Set the congestion level of a subsystem.
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
 ****************************************************************************/
SS7DLLAPI int
SCCP_SendSetCongestion_TTC(ITS_HANDLE handl, ITS_OCTET ni,
                           ITS_UINT pc, ITS_OCTET ssn, ITS_OCTET cong)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).sccp.cong)(inst, ni,
                                                       pc, ssn, cong);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendComponent_TTC(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_CPT *cpt)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_ComponentSanityCheck_TTC(cpt)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendCmp)(inst, hdr, cpt);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send a TCAP dialogue.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SendDialogue_TTC(ITS_HANDLE handl, ITS_HDR *hdr, TCAP_DLG *dlg)
{
    int ret;
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    if ((ret = TCAP_DialogueSanityCheck_TTC(dlg)) != ITS_SUCCESS)
    {
        return ret;
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.sendDlg)(inst, hdr, dlg);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP component.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveComponent_TTC(ITS_HANDLE handle, ITS_EVENT *event,
                          ITS_HDR *hdr, TCAP_CPT *cpt)
{
    hdr->type = ITS_TCAP_TTC;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive a TCAP dialogue
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_ReceiveDialogue_TTC(ITS_HANDLE handle, ITS_EVENT *event,
                         ITS_HDR *hdr, TCAP_DLG *dlg)
{
    hdr->type = ITS_TCAP_TTC;
    hdr->context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

    memcpy(dlg, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_DLG));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_AllocateDialogueId_TTC(ITS_HANDLE handl, ITS_CTXT* did)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.getDID)(inst, did);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchAddrs_TTC(ITS_HANDLE handl, ITS_CTXT did,
                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchAddrs)(inst, did,
                                                             oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetAddrs_TTC(ITS_HANDLE handl, ITS_CTXT did,
                  SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setAddrs)(inst, did,
                                                           oaddr, daddr);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_FetchQOS_TTC(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.fetchQOS)(inst, did, qos);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate a dialogue ID.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetQOS_TTC(ITS_HANDLE handl, ITS_CTXT did, DLG_QOS *qos)
{
    SS7TRAN_Manager *ss7 = (SS7TRAN_Manager *)handl;
    VENDOR_Instance *inst = (VENDOR_Instance *)SS7TRAN_HANDLE(ss7);

    ITS_C_ASSERT(inst != NULL);

    if (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS == NULL)
    {
        return (ITS_ENOTFOUND);
    }

    return (VCLASS_REC(ITS_OBJ_CLASS(inst)).tcap.setQOS)(inst, did, qos);
}

/******************************* IMPLEMENTATION *****************************/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize some class methods.
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
 ****************************************************************************/
static int
ClassInit_TTC(ITS_Class objClass)
{
    /* Initialize SCCP and MTP3 callback Management */
    SCCP_TTC_ManagementCallbacks = CALLBACK_InitManager();

    if (SCCP_TTC_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        return (ITS_ENOMEM);
    }

    /* Initialize SCCP and MTP3 callback Management */
    ISUP_TTC_ManagementCallbacks = CALLBACK_InitManager();

    if (ISUP_TTC_ManagementCallbacks == NULL)
    {
        printf("\n Could not create SCCP Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_TTC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    MTP3_TTC_ManagementCallbacks = CALLBACK_InitManager();

    if (MTP3_TTC_ManagementCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(ISUP_TTC_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_TTC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_TTC_GlobalTitleTranslator = CALLBACK_InitManager();

    if (SCCP_TTC_GlobalTitleTranslator == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(MTP3_TTC_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_TTC_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_TTC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    SCCP_TTC_SSNRoutingCallbacks = CALLBACK_InitManager();

    if (SCCP_TTC_SSNRoutingCallbacks == NULL)
    {
        printf("\n Could not create MTP3 Callback structure, quitting...");

        CALLBACK_DestroyManager(SCCP_TTC_GlobalTitleTranslator);
        CALLBACK_DestroyManager(MTP3_TTC_ManagementCallbacks);
        CALLBACK_DestroyManager(ISUP_TTC_ManagementCallbacks);
        CALLBACK_DestroyManager(SCCP_TTC_ManagementCallbacks);

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy the callback structs (if configuration applies)
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
 ****************************************************************************/
static void
ClassDestroy_TTC(ITS_Class objClass)
{
    CALLBACK_DestroyManager(ISUP_TTC_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_TTC_ManagementCallbacks);
    CALLBACK_DestroyManager(MTP3_TTC_ManagementCallbacks);
    CALLBACK_DestroyManager(SCCP_TTC_GlobalTitleTranslator);
    CALLBACK_DestroyManager(SCCP_TTC_SSNRoutingCallbacks);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the TCAP layer, if applicable.
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
 ****************************************************************************/
static int
TCAP_Initialize_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_TTC) == ITS_TCAP_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the TCAP layer, if applicable.
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
 ****************************************************************************/
static void
TCAP_Terminate_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_TCAP_TTC) == ITS_TCAP_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the SCCP layer, if applicable.
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
 ****************************************************************************/
static int
SCCP_Initialize_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_TTC) == ITS_SCCP_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the SCCP layer, if applicable.
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
 ****************************************************************************/
static void
SCCP_Terminate_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_SCCP_TTC) == ITS_SCCP_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the ISUP layer, if applicable.
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
 ****************************************************************************/
static int
ISUP_Initialize_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_TTC) == ITS_ISUP_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the ISUP layer, if applicable.
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
 ****************************************************************************/
static void
ISUP_Terminate_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_ISUP_TTC) == ITS_ISUP_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP3 layer, if applicable.
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
 ****************************************************************************/
static int
MTP3_Initialize_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_TTC) == ITS_MTP3_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP3 layer, if applicable.
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
 ****************************************************************************/
static void
MTP3_Terminate_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP3_TTC) == ITS_MTP3_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the MTP2 layer, if applicable.
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
 ****************************************************************************/
static int
MTP2_Initialize_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_TTC) == ITS_MTP2_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        if ((VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.init)(handle) !=
            ITS_SUCCESS)
        {
            return (ITS_EPROTERR);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the MTP2 layer, if applicable.
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
 ****************************************************************************/
static void
MTP2_Terminate_TTC(SS7TRAN_Manager *ss7, VENDOR_Instance *handle)
{
    if ((TRANSPORT_MASK(ss7) & ITS_MTP2_TTC) == ITS_MTP2_TTC)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.term)(handle);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      initialize the connections to both boards (if required)
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
 ****************************************************************************/
static int
SS7_Initialize_TTC(ITS_Object obj, va_list args)
{
    SS7TRAN_Manager *ss7;
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;

    ss7 = va_arg(args, SS7TRAN_Manager *);

    VENDOR_OWNING_TRANSPORT(handle) = ss7;

    ITS_C_ASSERT(ss7 != NULL);

    /* initialize the NMS software */
    if (TRANSPORT_MASK(ss7) & ITS_SS7_MASK)
    {
        int ret;

        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).loadRes)(handle,
                                                        TRANSPORT_INSTANCE(ss7));
        }

        if ((ret = MTP2_Initialize_TTC(ss7, handle)) != ITS_SUCCESS)
        {
            return (ret);
        }

        if ((ret = MTP3_Initialize_TTC(ss7, handle)) != ITS_SUCCESS)
        {
            MTP2_Terminate_TTC(ss7, handle);

            return (ret);
        }

        if ((ret = SCCP_Initialize_TTC(ss7, handle)) != ITS_SUCCESS)
        {
            MTP3_Terminate_TTC(ss7, handle);
            MTP2_Terminate_TTC(ss7, handle);

            return (ret);
        }

        if ((ret = ISUP_Initialize_TTC(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_TTC(ss7, handle);
            MTP3_Terminate_TTC(ss7, handle);
            MTP2_Terminate_TTC(ss7, handle);

            return (ret);
        }

        if ((ret = TCAP_Initialize_TTC(ss7, handle)) != ITS_SUCCESS)
        {
            SCCP_Terminate_TTC(ss7, handle);
            ISUP_Terminate_TTC(ss7, handle);
            MTP3_Terminate_TTC(ss7, handle);
            MTP2_Terminate_TTC(ss7, handle);

            return (ret);
        }
    }

    if ((VENDOR_RCV_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_TTC(ss7, handle);
        SCCP_Terminate_TTC(ss7, handle);
        ISUP_Terminate_TTC(ss7, handle);
        MTP3_Terminate_TTC(ss7, handle);
        MTP2_Terminate_TTC(ss7, handle);

        return (ITS_ENOMEM);
    }

    if ((VENDOR_SND_Q(handle) = MQUEUE_Create()) == NULL)
    {
        TCAP_Terminate_TTC(ss7, handle);
        SCCP_Terminate_TTC(ss7, handle);
        ISUP_Terminate_TTC(ss7, handle);
        MTP3_Terminate_TTC(ss7, handle);
        MTP2_Terminate_TTC(ss7, handle);

        MQUEUE_Delete(VENDOR_RCV_Q(handle));

        return (ITS_ENOMEM);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the application
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
 ****************************************************************************/
static void
SS7_Terminate_TTC(ITS_Object obj)
{
    VENDOR_Instance *handle = (VENDOR_Instance *)obj;
    SS7TRAN_Manager *ss7 = VENDOR_OWNING_TRANSPORT(handle);

    MQUEUE_Delete(VENDOR_RCV_Q(ss7));
    MQUEUE_Delete(VENDOR_SND_Q(ss7));

    TCAP_Terminate_TTC(ss7, handle);
    SCCP_Terminate_TTC(ss7, handle);
    ISUP_Terminate_TTC(ss7, handle);
    MTP3_Terminate_TTC(ss7, handle);
    MTP2_Terminate_TTC(ss7, handle);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the vendor.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static ITS_BOOLEAN
RetrieveMessage_TTC(VENDOR_Instance *handle, ITS_EVENT *event,
                     int indic_flag)
{
    int len;
    ITS_EVENT *msg;

    if (indic_flag & EVENT_FROM_TCAP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_SCCP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_ISUP)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP3)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.retrieve)(handle);
        }
    }

    if (indic_flag & EVENT_FROM_MTP2)
    {
        if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)
        {
            (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.retrieve)(handle);
        }
    }

    while (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                          (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);
                    
        if (event->src == ITS_MTP3_TTC_SRC &&
            (MTP3_MSG_TYPE(event) == MTP3_MSG_PAUSE ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_RESUME ||
             MTP3_MSG_TYPE(event) == MTP3_MSG_STATUS))
        {
            CALLBACK_CallCallbackList(MTP3_TTC_ManagementCallbacks,
                                      NULL,    
                                      (ITS_POINTER)event);   
        }
        /*
         * there should be a clause here for handling SCCP management
         * messages as well.
         */
        else
        {
            return (ITS_FALSE);
        }
    }

    /*
     * if we get here there wasn't anything put on the queue that wasn't
     * managment related.
     */
    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Retrieve an event from the NMS board.
 *
 *  Input Parameters:
 *      handle - the context.
 *      event - the return event.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
SS7_GetNextEvent_TTC(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_BOOLEAN cont = ITS_TRUE;
    ITS_EVENT *msg;
    int indic_flag, ret, len;
 
    if (MQUEUE_Dequeue(VENDOR_RCV_Q(handle),
                       (void **)&msg, &len) == ITS_SUCCESS)
    {
        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    while (cont &&
           !TRANSPORT_EXIT_NOW(((TRANSPORT_Control *)VENDOR_OWNING_TRANSPORT(handle))))
    {
        ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

        ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                           &indic_flag,
                                                           (int)HMI_GetTimeOutInterval());
        if (ret != ITS_SUCCESS)
        {
            if (ret == ITS_ENOMSG)
            {
                continue;
            }

            return (ret);
        }

        cont = RetrieveMessage_TTC(handle, event, indic_flag);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
SS7_PeekNextEvent_TTC(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_EVENT *msg;
    int len, ret;
    int indic_flag;

    if (!MQUEUE_EmptyP(VENDOR_RCV_Q(handle)))
    {
        MQUEUE_Dequeue(VENDOR_RCV_Q(handle), (void **)&msg, &len);

        ITS_C_ASSERT(len == sizeof(ITS_EVENT));

        memcpy(event, msg, len);

        ITS_Free(msg);

        return ITS_SUCCESS;
    }

    ITS_C_ASSERT(VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd != NULL);

    ret = (VCLASS_REC(ITS_OBJ_CLASS(handle)).awaitInd)(handle,
                                                       &indic_flag,
                                                       0);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    if (RetrieveMessage_TTC(handle, event, indic_flag))
    {
        return (ITS_ENOMSG);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Put an event onto the transport.
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
 *      Depending on the configuration for this transport, this may mean
 *      that a synthetic event is put on the receive queue, or that an
 *      actual SS7 event is sent.
 *
 ****************************************************************************/
static int
SS7_PutEvent_TTC(VENDOR_Instance *handle, ITS_EVENT *event)
{
    ITS_HDR hdr;
    ITS_OCTET mType = 0;
    int ieCount = 0;
    SS7_Transport tc;

    tc = VENDOR_OWNING_TRANSPORT(handle);

    /*
     * handle a TCAP message?
     */
    if (event->src == ITS_TCAP_TTC_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_TCAP_TTC) != ITS_TCAP_TTC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg == NULL ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp == NULL)
        {
            if ((TRANSPORT_MASK(tc) & ITS_SCCP_TTC) != ITS_SCCP_TTC ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }
            else
            {
                ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
                ITS_USHORT len;
                int ret;
                MTP3_HEADER_TTC mtp3;
                ITS_SCCP_IE ies[10];
                SCCP_MSG_DESC* desc;

                if ((ret = MTP3_Decode_TTC(event, &mType, &mtp3,
                                             buf, &len)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                if (mType != MTP3_MSG_USER_DATA)
                {
                    return (ITS_EINVALIDARGS);
                }

                mType = buf[0];
                desc = SCCP_GetDescriptor_TTC(mType);

                if ((ret = SCCP_DecodeMTP3_TTC(buf, len, &mType,
                                                 ies, &ieCount, desc)) != ITS_SUCCESS)
                {
                    return (ret);
                }

                hdr.type = ITS_SCCP_TTC;
                hdr.context.ssn = 0;
                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                     &hdr,
                                                                     ies, ieCount,
                                                                     desc);
            }
        }
        else
        {
            hdr.type = ITS_TCAP_TTC;
            hdr.context.dialogue_id = ITS_GET_CTXT(&event->data[1]);

            if (TCAP_MSG_TYPE(event) == ITS_TCAP_DLG)
            {
                TCAP_DLG dlg;

                memcpy(&dlg,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_DLG));


                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendDlg)(handle,
                                                                        &hdr,
                                                                        &dlg);
            }
            else if (TCAP_MSG_TYPE(event) == ITS_TCAP_CPT)
            {
                TCAP_CPT cpt;

                memcpy(&cpt,
                       &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
                       sizeof(TCAP_CPT));

                return (VCLASS_REC(ITS_OBJ_CLASS(handle)).tcap.sendCmp)(handle,
                                                                        &hdr,
                                                                        &cpt);
            }
        }
    }
    /*
     * handle and SCCP message?
     */
    else if (event->src == ITS_SCCP_TTC_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_SCCP_TTC) != ITS_SCCP_TTC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_TTC mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_TTC) != ITS_MTP3_TTC ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendTTC == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_TTC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendTTC)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len;
            int ret;
            MTP3_HEADER_TTC mtp3;
            ITS_SCCP_IE ies[10];
            SCCP_MSG_DESC* desc;

            if ((ret = MTP3_Decode_TTC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];
            desc = SCCP_GetDescriptor_TTC(mType);

            if ((ret = SCCP_DecodeMTP3_TTC(buf, len, &mType,
                                            ies, &ieCount, desc)) != ITS_SUCCESS)
            {
                return (ret);
            }

            hdr.type = ITS_SCCP_TTC;
            hdr.context.ssn = 0;

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).sccp.send)(handle, mType,
                                                                 &hdr,
                                                                 ies, ieCount,
                                                                 desc);
        }
    }
    /*
     * handle ISUP message?
     */
    else if (event->src == ITS_ISUP_TTC_SRC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_ISUP_TTC) != ITS_ISUP_TTC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendCCITT == NULL)
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            MTP3_HEADER_TTC mtp3;
            int ret;

            if ((TRANSPORT_MASK(tc) & ITS_MTP3_TTC) != ITS_MTP3_TTC ||
                VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendTTC == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            if ((ret = MTP3_Decode_TTC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendTTC)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
        else
        {
            ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
            ITS_USHORT len = 0;
            int ret = 0;
            MTP3_HEADER_TTC mtp3;
            ITS_ISUP_IE_CCITT ies[32];
            ISUP_MSG_DESC* desc = NULL;

            if ((ret = MTP3_Decode_TTC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            if (mType != MTP3_MSG_USER_DATA)
            {
                return (ITS_EINVALIDARGS);
            }

            mType = buf[0];

            hdr.type = ITS_ISUP;
            hdr.context.cic = ITS_GET_CTXT(&buf[1]);

            desc = ISUP_GetDescriptor_CCITT(mType);

            if ((ret = ISUP_DecodeMTP3_CCITT(ies, &ieCount, event, desc)) !=
                ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).isup.sendCCITT)(handle,
                                                                      mType,
                                                                      &hdr,
                                                                      ies,
                                                                      ieCount,
                                                                      desc);
        }
    }
    /*
     * handle MTP3 event?
     */
    else if (event->src == ITS_MTP3_TTC_SRC)
    {
        ITS_OCTET buf[MTP3_MAX_SIF_LENGTH];
        ITS_USHORT len = 0;
        MTP3_HEADER_TTC mtp3;
        int ret;

        if ((TRANSPORT_MASK(tc) & ITS_MTP3_TTC) != ITS_MTP3_TTC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendTTC == NULL)
        {
            if (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
            {
                return (ITS_ENOTFOUND);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                                 event->data,
                                                                 event->len);
        }
        else
        {
            if ((ret = MTP3_Decode_TTC(event, &mType, &mtp3,
                                         buf, &len)) != ITS_SUCCESS)
            {
                return (ret);
            }

            return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp3.sendTTC)(handle,
                                                                      MTP3_MSG_USER_DATA,
                                                                      &mtp3,
                                                                      buf, len);
        }
    }
    /*
     * handle MTP2 event?
     */
    else if (event->src == ITS_MTP2_TTC)
    {
        if ((TRANSPORT_MASK(tc) & ITS_MTP2_TTC) != ITS_MTP2_TTC ||
            VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        return (VCLASS_REC(ITS_OBJ_CLASS(handle)).mtp2.send)(handle,
                                                             event->data,
                                                             event->len);
    }

    return (ITS_SUCCESS);
}

SS7DLLAPI SS7STACK_ClassRec itsSS7STACK_ClassRecTTC =
{
    /* core */
    {
        NULL,                       /* superclass */
        0,                          /* instance size */
        ITS_FALSE,                  /* not initted */
        sizeof(VENDOR_Instance),    /* initial ref count */
        "SS7 Stack TTC",          /* class name: replace with your vendor */
        ClassInit_TTC,            /* no class init */
        ClassDestroy_TTC,         /* no class dest */
        ClassPartInit,              /* class part init */
        ClassPartDest,              /* class part destroy */
        SS7_Initialize_TTC,       /* instantiate */
        SS7_Terminate_TTC,        /* destroy */
        NULL                        /* extension */
    },
    /* stack */
    {
        SS7_GetNextEvent_TTC,     /* getNextEvent */
        SS7_PeekNextEvent_TTC,    /* peekNextEvent */
        SS7_PutEvent_TTC          /* putEvent */
    }
};

SS7DLLAPI ITS_Class itsSS7STACK_ClassTTC =
    (ITS_Class)&itsSS7STACK_ClassRecTTC;


#endif /* !defined(SPLIT_STACK) */
