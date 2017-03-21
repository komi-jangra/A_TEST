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
 *  ID: $Id: vframe.h,v 1.1.1.1 2007-10-08 11:11:33 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:38  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/05/06 09:09:19  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:50:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.1.6.1.6.1  2004/12/16 03:26:18  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.2.1.6.1  2004/09/15 05:30:16  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/05/07 08:21:35  ssingh
 * LOG: ISUP related changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:18:33  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/07/03 17:41:07  mmiers
 * LOG: china changes
 * LOG:
 * LOG: Revision 6.4  2002/07/01 21:50:34  mmiers
 * LOG: VFrame changes to support ISUP
 * LOG:
 * LOG: Revision 6.3  2002/06/28 16:29:53  hbalimid
 * LOG: Modified for ISUP vendor specific requirements.
 * LOG:
 * LOG: Revision 6.2  2002/05/29 22:40:05  mmiers
 * LOG: Change signature
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.4  2002/02/13 21:21:26  mmiers
 * LOG: Finish up ISUP integration
 * LOG:
 * LOG: Revision 1.3  2002/02/13 18:27:44  mmiers
 * LOG: Finish off the ISUP integration.
 * LOG:
 * LOG: Revision 1.2  2002/02/01 21:05:19  mmiers
 * LOG: Fix up for ISUP
 * LOG:
 * LOG: Revision 1.1  2002/01/10 16:52:30  mmiers
 * LOG: Move vframe from vendors to here.  Update ignore list.
 * LOG:
 * LOG: Revision 1.10  2002/01/02 19:56:09  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 1.9  2001/12/20 23:46:48  mmiers
 * LOG: Trying for consistency
 * LOG:
 * LOG: Revision 1.8  2001/12/20 20:26:14  mmiers
 * LOG: Fix CCITT build.
 * LOG:
 * LOG: Revision 1.7  2001/12/18 23:20:13  mmiers
 * LOG: Get the right symbols included
 * LOG:
 * LOG: Revision 1.6  2001/12/18 21:02:16  mmiers
 * LOG: Typo.
 * LOG:
 * LOG: Revision 1.5  2001/12/18 21:00:24  mmiers
 * LOG: Try this out.
 * LOG:
 * LOG: Revision 1.4  2001/12/17 21:09:23  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 1.3  2001/12/17 00:15:35  mmiers
 * LOG: Get this building on UNIX
 * LOG:
 * LOG: Revision 1.2  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 1.1  2001/12/13 23:01:27  mmiers
 * LOG: Common vendor framework.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_ITS_VENDOR_H_)
#define _ITS_VENDOR_H_

#include <its_mlist.h>
#include <its_ss7_trans.h>

#include <ansi/tcap.h>
#include <itu/tcap.h>
#include <china/tcap.h>
#include <japan/tcap.h>
#include <ansi/isup.h>
#include <itu/isup.h>
#include <ansi/sccp.h>
#include <itu/sccp.h>
#include <china/sccp.h>
#include <japan/sccp.h>
#include <ansi/mtp3.h>
#include <itu/mtp3.h>
#include <china/mtp3.h>
#include <japan/mtp3.h>

/*
 * indication sources
 */
#define EVENT_FROM_TCAP     0x01
#define EVENT_FROM_SCCP     0x02
#define EVENT_FROM_ISUP     0x04
#define EVENT_FROM_MTP3     0x08
#define EVENT_FROM_MTP2     0x10

/*
 * XML position for ISUP
 */
#define ISUP_STACK            0x01
#define ISUP_CONFIG           0x02
#define ISUP_DESTINATION      0x03
#define ISUP_PARSER_EXTENSION 0x04

/*
 * stack implementation methods.
 */
typedef int (*VENDOR_LayerInitTermProc)(ITS_SS7_HANDLE handle);
typedef int (*VENDOR_LayerRetrieveProc)(ITS_SS7_HANDLE handle);
typedef int (*VENDOR_LoadResourcesProc)(ITS_SS7_HANDLE handle,
                                        ITS_USHORT instance);
typedef int (*VENDOR_AwaitIndicationProc)(ITS_SS7_HANDLE handle,
                                          int *indications, int millisecs);

/* Special function for ISUP */
typedef int (*VENDOR_ANSIISUPReceiveProc)(ITS_SS7_HANDLE handle, ITS_EVENT *ev,
                                          ITS_HDR *hdr,
                                          ITS_ISUP_IE_ANSI *ies, int *ieCount,
                                          ISUP_MSG_DESC *desc);
typedef int (*VENDOR_CCITTISUPReceiveProc)(ITS_SS7_HANDLE handle, ITS_EVENT *ev,
                                           ITS_HDR *hdr,
                                           ITS_ISUP_IE_CCITT *ies, int *ieCount,
                                           ISUP_MSG_DESC *desc);

/*
 * layer implementation methods.
 */
typedef int (*VENDOR_LayerGetNextContextProc)(ITS_SS7_HANDLE handle,
                                              ITS_CTXT *ctxt);
typedef int (*VENDOR_MTP2SendEventProc)(ITS_SS7_HANDLE handle,
                                        ITS_OCTET *data, ITS_USHORT len);
typedef int (*VENDOR_ANSIMTP3SendEventProc)(ITS_SS7_HANDLE handle,
                                        ITS_OCTET type, MTP3_HEADER_ANSI *mtp3,
                                        ITS_OCTET *data, ITS_USHORT dlen);
typedef int (*VENDOR_CCITTMTP3SendEventProc)(ITS_SS7_HANDLE handle,
                                             ITS_OCTET type, MTP3_HEADER_CCITT *mtp3,
                                             ITS_OCTET *data, ITS_USHORT dlen);
typedef int (*VENDOR_PRCMTP3SendEventProc)(ITS_SS7_HANDLE handle,
                                           ITS_OCTET type, MTP3_HEADER_PRC *mtp3,
                                           ITS_OCTET *data, ITS_USHORT dlen);
typedef int (*VENDOR_TTCMTP3SendEventProc)(ITS_SS7_HANDLE handle,
                                           ITS_OCTET type, MTP3_HEADER_TTC *mtp3,
                                           ITS_OCTET *data, ITS_USHORT dlen);
typedef int (*VENDOR_ANSIISUPSendEventProc)(ITS_SS7_HANDLE handle,
                                            ITS_OCTET type,
                                            ITS_HDR* hdr,
                                            ITS_ISUP_IE_ANSI* ies, int ieCount,
                                            ISUP_MSG_DESC* desc);
typedef int (*VENDOR_CCITTISUPSendEventProc)(ITS_SS7_HANDLE handle,
                                             ITS_OCTET type,
                                             ITS_HDR* hdr,
                                             ITS_ISUP_IE_CCITT* ies, int ieCount,
                                             ISUP_MSG_DESC* desc);
typedef int (*VENDOR_SCCPSendEventProc)(ITS_SS7_HANDLE handle, ITS_OCTET type,
                                        ITS_HDR* hdr,
                                        ITS_SCCP_IE *ies, int ieCount,
                                        SCCP_MSG_DESC *desc);
typedef int (*VENDOR_ISUPValidateCICProc)(ITS_SS7_HANDLE handle,
                                          ITS_OCTET sio,
                                          ITS_UINT opc, ITS_UINT dpc,
                                          ITS_USHORT cic, ITS_OCTET *status,
                                          ITS_CTXT *vcic);
typedef int (*VENDOR_ISUPUnReserveCICProc)(ITS_SS7_HANDLE handle,
                                          ITS_OCTET sio,
                                          ITS_UINT opc, ITS_UINT dpc,
                                          ITS_USHORT cic);
typedef int (*VENDOR_SCCPServiceStateProc)(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                                           ITS_UINT pc, ITS_OCTET ssn);
typedef int (*VENDOR_SCCPCongestionProc)(ITS_SS7_HANDLE handle, ITS_OCTET ni,
                                         ITS_UINT pc, ITS_OCTET ssn,
                                         ITS_OCTET congLevel);
typedef int (*VENDOR_TCAPSendComponentProc)(ITS_SS7_HANDLE handle,
                                            ITS_HDR *hdr, TCAP_CPT *cpt);
typedef int (*VENDOR_TCAPSendDialogueProc)(ITS_SS7_HANDLE handle,
                                           ITS_HDR *hdr, TCAP_DLG *dlg);
typedef int (*VENDOR_TCAPAddrsProc)(ITS_SS7_HANDLE handle,
                                    ITS_CTXT did,
                                    SCCP_ADDR *oaddr, SCCP_ADDR *daddr);
typedef int (*VENDOR_TCAPQOSProc)(ITS_SS7_HANDLE handle,
                                  ITS_CTXT did, DLG_QOS *qos);

/* Commit methods for each layer */
typedef int (*VENDOR_LayerCommit)(FILE* fp);
typedef int (*ISUP_LayerCommit)(FILE* fp, int pos,
                                int opc, int dpc, int sio);

typedef struct
{
    VENDOR_LoadResourcesProc    loadRes;
    VENDOR_AwaitIndicationProc  awaitInd;
    struct
    {
        VENDOR_LayerInitTermProc        init;
        VENDOR_LayerInitTermProc        term;
        VENDOR_LayerRetrieveProc        retrieve;
        VENDOR_MTP2SendEventProc        send;
        VENDOR_LayerCommit              commit;
    }
    mtp2;
    struct
    {
        VENDOR_LayerInitTermProc        init;
        VENDOR_LayerInitTermProc        term;
        VENDOR_LayerRetrieveProc        retrieve;
        VENDOR_ANSIMTP3SendEventProc    sendANSI;
        VENDOR_CCITTMTP3SendEventProc   sendCCITT;
        VENDOR_PRCMTP3SendEventProc     sendPRC;
        VENDOR_TTCMTP3SendEventProc     sendTTC;
        VENDOR_LayerCommit              commit;
    }
    mtp3;
    struct
    {
        VENDOR_LayerInitTermProc        init;
        VENDOR_LayerInitTermProc        term;
        VENDOR_ISUPValidateCICProc      getCIC;
        VENDOR_ISUPUnReserveCICProc     unreserveCIC;
        VENDOR_LayerRetrieveProc        retrieve;
        VENDOR_ANSIISUPReceiveProc      receiveANSI;
        VENDOR_CCITTISUPReceiveProc     receiveCCITT;
        VENDOR_ANSIISUPSendEventProc    sendANSI;
        VENDOR_CCITTISUPSendEventProc   sendCCITT;
        ISUP_LayerCommit                commit;
    }
    isup;
    struct
    {
        VENDOR_LayerInitTermProc        init;
        VENDOR_LayerInitTermProc        term;
        VENDOR_LayerGetNextContextProc  getRef;
        VENDOR_LayerRetrieveProc        retrieve;
        VENDOR_SCCPSendEventProc        send;
        VENDOR_SCCPServiceStateProc     oos;
        VENDOR_SCCPServiceStateProc     is;
        VENDOR_SCCPCongestionProc       cong;
        VENDOR_LayerCommit              commit;
    }
    sccp;
    struct
    {
        VENDOR_LayerInitTermProc        init;
        VENDOR_LayerInitTermProc        term;
        VENDOR_LayerGetNextContextProc  getDID;
        VENDOR_LayerRetrieveProc        retrieve;
        VENDOR_TCAPSendComponentProc    sendCmp;
        VENDOR_TCAPSendDialogueProc     sendDlg;
        VENDOR_TCAPAddrsProc            fetchAddrs;
        VENDOR_TCAPAddrsProc            setAddrs;
        VENDOR_TCAPQOSProc              fetchQOS;
        VENDOR_TCAPQOSProc              setQOS;
        VENDOR_SCCPServiceStateProc     oos;
        VENDOR_SCCPServiceStateProc     is;
        VENDOR_SCCPCongestionProc       cong;
        VENDOR_LayerCommit              commit;
    }
    tcap;
}
VENDOR_ClassPart;

/*
 * we inherit (and extend) from the SS7STACK_Class
 */
typedef struct
{
    ITS_CoreClassPart   coreClass;
    SS7STACK_ClassPart  ss7stackClass;
    VENDOR_ClassPart    vendorClass;
}
VENDOR_ClassRec, *VENDOR_Class;

#define VCLASS_REC(x) \
    (((VENDOR_ClassRec *)(x))->vendorClass)

#endif /* defined(_ITS_VENDOR_H_) */
