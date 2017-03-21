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
 *  ID: $Id: sccp.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:52  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:50  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:22  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:22  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.10.2  2004/09/21 06:56:54  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.3.10.1  2004/01/27 05:56:51  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.3  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.2  2003/01/07 15:32:16  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:23  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.1  2002/07/03 15:51:01  mmiers
 * LOG: Add china family
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_SCCP_PRC_H_
#define _ITS_SCCP_PRC_H_

#ident "$Id: sccp.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>
#include <its_route.h>

#include <china/mtp3.h>

/*
 * get the common data
 */
#include <sccp_cmn.h>

/*
 * use of the short names is deprecated and may be removed in a future
 * release
 */
#include <sccp_sn.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * PRC message descriptors
 */
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CR_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CC_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CREF_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLSD_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLC_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT1_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT2_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_AK_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDT_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDT_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDTS_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDTS_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ED_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_EA_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSR_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSC_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ERR_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_IT_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDT_Desc_PRC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDTS_Desc_PRC;

/*
 * Management callbacks
 * GTT callbacks and routing callbacks are only available
 * with our stack.
 */
SS7DLLAPI extern CALLBACK_Manager*    SCCP_PRC_ManagementCallbacks;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_PRC_GlobalTitleTranslator;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_PRC_SSNRoutingCallbacks;

/*
 * function interface
 */
SS7DLLAPI int  SCCP_GetNextLocalRef_PRC(ITS_HANDLE handle,
                                        ITS_CTXT* cref);

SS7DLLAPI int  SCCP_GetSharedLocalRef_PRC(void *ctxtData,
                                         int len);

/*
 * address helpers
 */
SS7DLLAPI int SCCP_EncodeAddr_PRC(SCCP_ADDR *addr, ITS_OCTET addrInd,
                                  ITS_UINT pc, ITS_OCTET ssn,
                                  const ITS_OCTET* gttInfo, ITS_USHORT gttLen);
SS7DLLAPI int SCCP_DecodeAddr_PRC(const SCCP_ADDR *addr, ITS_OCTET* addrInd,
                                  ITS_UINT* pc, ITS_OCTET *ssn,
                                  ITS_OCTET* gttInfo, ITS_USHORT* gttLen);

SS7DLLAPI int SCCP_ComputeMSize_PRC(ITS_OCTET which);

SS7DLLAPI int SCCP_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                                ITS_OCTET mType,
                                ITS_SCCP_IE *ies, ITS_UINT ieCount,
                                ITS_BOOLEAN printUserData);

/*
 * Application status requests.
 */
SS7DLLAPI int SCCP_SendUserInService_PRC(ITS_HANDLE handle, ITS_OCTET ni,
                                         ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendUserOutOfService_PRC(ITS_HANDLE handle, ITS_OCTET ni,
                                            ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendSetCongestion_PRC(ITS_HANDLE handle, ITS_OCTET ni,
                                         ITS_UINT pc, ITS_OCTET ssn,
                                         ITS_OCTET cong);

/*.interface:SCCP
 *****************************************************************************
 *  Interface:
 *      SCCP_*
 *
 *  Purpose:
 *      This interface defines the user's C programming model for SCCP.
 *
 *  Usage:
 *
 *****************************************************************************/
/*
 * primitives
 */
/*** CR ***/
SS7DLLAPI int SCCP_SendConnectionRequest_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRequest_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** CC ***/
SS7DLLAPI int SCCP_SendConnectionConfirm_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionConfirm_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** CREF ***/
SS7DLLAPI int SCCP_SendConnectionRefused_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRefused_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** RLSD ***/
SS7DLLAPI int SCCP_SendReleased_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleased_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                       ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int *ieCount);

/*** RLC ***/
SS7DLLAPI int SCCP_SendReleaseComplete_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleaseComplete_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm1_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm1_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                        ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm2_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                     ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm2_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                        ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int *ieCount);

/*** AK ***/
SS7DLLAPI int SCCP_SendAcknowledgement_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveAcknowledgement_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/*** UDT ***/
SS7DLLAPI int SCCP_SendUnitData_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitData_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                       ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int *ieCount);

/*** XUDT ***/
SS7DLLAPI int SCCP_SendExtendedUnitData_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitData_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/*** LUDT ***/
SS7DLLAPI int SCCP_SendLongUnitData_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitData_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                           ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int *ieCount);

/*** UDTS ***/
SS7DLLAPI int SCCP_SendUnitDataService_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitDataService_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/*** XUDTS ***/
SS7DLLAPI int SCCP_SendExtendedUnitDataService_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                                   ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitDataService_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                      ITS_HDR *hdr,
                                                      ITS_SCCP_IE *ies, int *ieCount);

/*** LUDTS ***/
SS7DLLAPI int SCCP_SendLongUnitDataService_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitDataService_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                  ITS_HDR *hdr,
                                                  ITS_SCCP_IE *ies, int *ieCount);

/*** ED ***/
SS7DLLAPI int SCCP_SendExpeditedData_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedData_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                            ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int *ieCount);

/*** EA ***/
SS7DLLAPI int SCCP_SendExpeditedDataAck_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedDataAck_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/*** RSR ***/
SS7DLLAPI int SCCP_SendResetRequest_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetRequest_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                           ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int *ieCount);

/*** RSC ***/
SS7DLLAPI int SCCP_SendResetConfirmation_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetConfirmation_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** ERR ***/
SS7DLLAPI int SCCP_SendError_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                 ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveError_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                    ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int *ieCount);

/*** IT ***/
SS7DLLAPI int SCCP_SendInactivityTest_PRC(ITS_HANDLE handle, ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveInactivityTest_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                             ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int *ieCount);

/******************************** SCCP PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/

/*
 * implementation functions.  Users should not invoke these.
 */
SS7DLLAPI int SCCP_Encode_PRC(ITS_SCCP_IE *ies, int ieCount,
                              ITS_OCTET msgType, ITS_EVENT *event,
                              ITS_HDR *hdr, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_Decode_PRC(ITS_SCCP_IE *ies, int *ieCount,
                              ITS_EVENT *ev, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_EncodeMTP3_PRC(ITS_OCTET* data, ITS_USHORT* len,
                                  ITS_OCTET mType, ITS_SCCP_IE *ies,
                                  int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_DecodeMTP3_PRC(ITS_OCTET *data, ITS_USHORT len,
                                  ITS_OCTET* mType, ITS_SCCP_IE *ies,
                                  int *ieCount, SCCP_MSG_DESC* desc);

SS7DLLAPI int SCCP_SendEvent_PRC(ITS_HANDLE handle, ITS_OCTET type,
                                 ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                 int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_ReceiveEvent_PRC(ITS_HANDLE handle, ITS_EVENT *ev,
                                    ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                    int *ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI SCCP_MSG_DESC *SCCP_GetDescriptor_PRC(ITS_OCTET which);

ITS_BOOLEAN SCCP_IsSSNEquipped_PRC(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_BOOLEAN SCCP_IsSSNAllowed_PRC(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_OCTET   SCCP_IsSSNCongested_PRC(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);

/*
 * management interface
 */
ITSSS7DLLAPI int SCCP_AddConcernedSubSystem_PRC(ROUTE_Info *linfo,
                                                ROUTE_Info *cinfo);
ITSSS7DLLAPI int SCCP_RemConcernedSubSystem_PRC(ROUTE_Info *linfo,
                                                ROUTE_Info *cinfo);
ITSSS7DLLAPI int SCCP_AddDuplicatedSubSystem_PRC(ROUTE_Info *rinfo);
ITSSS7DLLAPI int SCCP_RemDuplicatedSubSystem_PRC(ROUTE_Info *rinfo);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SCCP_PRC_H_ */
