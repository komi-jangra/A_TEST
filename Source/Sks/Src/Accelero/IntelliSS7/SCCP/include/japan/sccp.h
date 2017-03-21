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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:53  bsccs2
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
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1  2004/12/16 02:22:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 1.1.2.1  2004/10/08 23:39:46  randresol
 * LOG: Start Japan SS7
 * LOG:
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_SCCP_TTC_H_
#define _ITS_SCCP_TTC_H_

#ident "$Id: sccp.h,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>
#include <its_route.h>

#include <japan/mtp3.h>

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
 * TTC message descriptors
 */
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CR_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CC_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CREF_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLSD_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLC_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT1_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT2_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_AK_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDT_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDT_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDTS_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDTS_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ED_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_EA_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSR_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSC_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ERR_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_IT_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDT_Desc_TTC;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDTS_Desc_TTC;

/*
 * Management callbacks
 * GTT callbacks and routing callbacks are only available
 * with our stack.
 */
SS7DLLAPI extern CALLBACK_Manager*    SCCP_TTC_ManagementCallbacks;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_TTC_GlobalTitleTranslator;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_TTC_SSNRoutingCallbacks;

/*
 * function interface
 */
SS7DLLAPI int  SCCP_GetNextLocalRef_TTC(ITS_HANDLE handle,
                                        ITS_CTXT* cref);

SS7DLLAPI int  SCCP_GetSharedLocalRef_TTC(void *ctxtData,
                                         int len);

/*
 * address helpers
 */
SS7DLLAPI int SCCP_EncodeAddr_TTC(SCCP_ADDR *addr, ITS_OCTET addrInd,
                                  ITS_UINT pc, ITS_OCTET ssn,
                                  const ITS_OCTET* gttInfo, ITS_USHORT gttLen);
SS7DLLAPI int SCCP_DecodeAddr_TTC(const SCCP_ADDR *addr, ITS_OCTET* addrInd,
                                  ITS_UINT* pc, ITS_OCTET *ssn,
                                  ITS_OCTET* gttInfo, ITS_USHORT* gttLen);

SS7DLLAPI int SCCP_ComputeMSize_TTC(ITS_OCTET which);

/*
 * Application status requests.
 */
SS7DLLAPI int SCCP_SendUserInService_TTC(ITS_HANDLE handle, ITS_OCTET ni,
                                         ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendUserOutOfService_TTC(ITS_HANDLE handle, ITS_OCTET ni,
                                            ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendSetCongestion_TTC(ITS_HANDLE handle, ITS_OCTET ni,
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
SS7DLLAPI int SCCP_SendConnectionRequest_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRequest_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** CC ***/
SS7DLLAPI int SCCP_SendConnectionConfirm_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionConfirm_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** CREF ***/
SS7DLLAPI int SCCP_SendConnectionRefused_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRefused_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** RLSD ***/
SS7DLLAPI int SCCP_SendReleased_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleased_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                       ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int *ieCount);

/*** RLC ***/
SS7DLLAPI int SCCP_SendReleaseComplete_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleaseComplete_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm1_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm1_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                        ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm2_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                     ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm2_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                        ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int *ieCount);

/*** AK ***/
SS7DLLAPI int SCCP_SendAcknowledgement_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveAcknowledgement_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/*** UDT ***/
SS7DLLAPI int SCCP_SendUnitData_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitData_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                       ITS_HDR *hdr,
                                       ITS_SCCP_IE *ies, int *ieCount);

/*** XUDT ***/
SS7DLLAPI int SCCP_SendExtendedUnitData_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitData_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/*** LUDT ***/
SS7DLLAPI int SCCP_SendLongUnitData_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitData_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                           ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int *ieCount);

/*** UDTS ***/
SS7DLLAPI int SCCP_SendUnitDataService_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitDataService_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/*** XUDTS ***/
SS7DLLAPI int SCCP_SendExtendedUnitDataService_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                                   ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitDataService_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                      ITS_HDR *hdr,
                                                      ITS_SCCP_IE *ies, int *ieCount);

/*** LUDTS ***/
SS7DLLAPI int SCCP_SendLongUnitDataService_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitDataService_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                  ITS_HDR *hdr,
                                                  ITS_SCCP_IE *ies, int *ieCount);

/*** ED ***/
SS7DLLAPI int SCCP_SendExpeditedData_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedData_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                            ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int *ieCount);

/*** EA ***/
SS7DLLAPI int SCCP_SendExpeditedDataAck_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedDataAck_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/*** RSR ***/
SS7DLLAPI int SCCP_SendResetRequest_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetRequest_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                           ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int *ieCount);

/*** RSC ***/
SS7DLLAPI int SCCP_SendResetConfirmation_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetConfirmation_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** ERR ***/
SS7DLLAPI int SCCP_SendError_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                 ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveError_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                    ITS_HDR *hdr,
                                    ITS_SCCP_IE *ies, int *ieCount);

/*** IT ***/
SS7DLLAPI int SCCP_SendInactivityTest_TTC(ITS_HANDLE handle, ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveInactivityTest_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                             ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int *ieCount);

/******************************** SCCP PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/

/*
 * implementation functions.  Users should not invoke these.
 */
SS7DLLAPI int SCCP_Encode_TTC(ITS_SCCP_IE *ies, int ieCount,
                              ITS_OCTET msgType, ITS_EVENT *event,
                              ITS_HDR *hdr, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_Decode_TTC(ITS_SCCP_IE *ies, int *ieCount,
                              ITS_EVENT *ev, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_EncodeMTP3_TTC(ITS_OCTET* data, ITS_USHORT* len,
                                  ITS_OCTET mType, ITS_SCCP_IE *ies,
                                  int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_DecodeMTP3_TTC(ITS_OCTET *data, ITS_USHORT len,
                                  ITS_OCTET* mType, ITS_SCCP_IE *ies,
                                  int *ieCount, SCCP_MSG_DESC* desc);

SS7DLLAPI int SCCP_SendEvent_TTC(ITS_HANDLE handle, ITS_OCTET type,
                                 ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                 int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_ReceiveEvent_TTC(ITS_HANDLE handle, ITS_EVENT *ev,
                                    ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                    int *ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI SCCP_MSG_DESC *SCCP_GetDescriptor_TTC(ITS_OCTET which);

ITS_BOOLEAN SCCP_IsSSNEquipped_TTC(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_BOOLEAN SCCP_IsSSNAllowed_TTC(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_OCTET   SCCP_IsSSNCongested_TTC(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);

/*
 * management interface
 */
ITSSS7DLLAPI int SCCP_AddConcernedSubSystem_TTC(ROUTE_Info *linfo,
                                                ROUTE_Info *cinfo);
ITSSS7DLLAPI int SCCP_RemConcernedSubSystem_TTC(ROUTE_Info *linfo,
                                                ROUTE_Info *cinfo);
ITSSS7DLLAPI int SCCP_AddDuplicatedSubSystem_TTC(ROUTE_Info *rinfo);
ITSSS7DLLAPI int SCCP_RemDuplicatedSubSystem_TTC(ROUTE_Info *rinfo);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SCCP_TTC_H_ */
