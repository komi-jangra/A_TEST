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
 *  ID: $Id: sccp.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:21  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:34  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:35  hbalimid
 * LOG: Get here for demo isup
 * LOG:
 * LOG: Revision 5.8  2001/12/19 17:22:16  mmiers
 * LOG: Move all callbacks to vframe
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
 * LOG: Revision 5.4  2001/10/08 20:08:02  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/06 17:24:39  mmiers
 * LOG: Closing in.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:47  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.3  2001/06/19 23:26:38  mmiers
 * LOG: Begin deprecation of short form names.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 16:51:44  mmiers
 * LOG: User requested stuff (user intervention).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:02:02  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:27  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:36  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/11/10 18:06:42  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.7  1999/06/23 19:58:34  mmiers
 * LOG:
 * LOG:
 * LOG: Slight modification to handle MTP3 modifications (include syntax).
 * LOG:
 * LOG: Revision 1.6  1999/02/13 01:05:20  mmiers
 * LOG:
 * LOG:
 * LOG: Missed an #if defined check.
 * LOG:
 * LOG: Revision 1.5  1998/10/15 23:15:28  mmiers
 * LOG: Add C++ for MTP3.  Add routing label to SCCP.
 * LOG:
 * LOG: Revision 1.4  1998/09/25 19:40:33  mmiers
 * LOG: Include MTP3 definitions.
 * LOG:
 * LOG: Revision 1.3  1998/02/26 16:28:21  rsonak
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  1998/02/06 15:29:54  ite
 * LOG: update for changes to nms header location.
 * LOG:
 * LOG: Revision 1.1  1998/02/06 14:44:07  mmiers
 * LOG: Add ANSI header, update ITU header to compensate.
 * LOG:
 * LOG: Revision 1.1  1998/02/06 14:39:47  mmiers
 * LOG: Move from common tree to here.
 * LOG:
 * LOG: Revision 1.4  1998/02/04 23:28:31  rsonak
 * LOG: formatting.
 * LOG:
 * LOG: Revision 1.3  1998/02/04 18:52:56  ite
 * LOG: sccp.h: Modify macros for correct behavior.
 * LOG: tcap.h: Correct usages, add some definitions for ANSI.
 * LOG:
 * LOG: Revision 1.2  1998/01/28 02:00:59  rsonak
 * LOG: Update from NMS integration.
 * LOG:
 * LOG: Revision 1.1  1998/01/27 15:42:49  mmiers
 * LOG: New files for NMS and ANSI
 * LOG:
 * LOG: Revision 1.2  1997/12/08 22:05:04  jpakrasi
 * LOG: Update copyright information for 1998 year.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_SCCP_ANSI_H
#define _ITS_SCCP_ANSI_H_

#ident "$Id: sccp.h,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $"

#if !defined(TANDEM)

#include <its.h>
#include <its_callback.h>

#include <ansi/mtp3.h>

#else /* TANDEM */

#include <itsh>
#include <itscallb>

#include <ansimtp3>

#endif /* TANDEM */

/*
 * get the common data
 */
#if !defined(TANDEM)
#include <sccp_cmn.h>
#else /* TANDEM */
#include <sccpcmnh>
#endif

/*
 * use of the short names is deprecated and may be removed in a future
 * release
 */
#if !defined(TANDEM)
#include <sccp_sn.h>
#else
#include <sccpsnh>
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * message descriptors
 */
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CR_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CC_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_CREF_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLSD_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RLC_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT1_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_DT2_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_AK_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDT_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDT_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_UDTS_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_XUDTS_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ED_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_EA_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSR_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_RSC_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_ERR_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_IT_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDT_Desc_ANSI;
SS7DLLAPI extern SCCP_MSG_DESC    SCCP_LUDTS_Desc_ANSI;

/*
 * Management callbacks.
 * GTT callbacks and routing callbacks are only available
 * with our stack.
 */
SS7DLLAPI extern CALLBACK_Manager*    SCCP_ANSI_ManagementCallbacks;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_ANSI_GlobalTitleTranslator;
SS7DLLAPI extern CALLBACK_Manager*    SCCP_ANSI_SSNRoutingCallbacks;

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
SS7DLLAPI int  SCCP_GetNextLocalRef_ANSI(ITS_HANDLE handle,
                                         ITS_USHORT* cref);

/*
 * address helpers
 */
SS7DLLAPI int SCCP_EncodeAddr_ANSI(SCCP_ADDR *addr, ITS_OCTET addrInd,
                                   ITS_UINT pc, ITS_OCTET ssn,
                                   const ITS_OCTET* gttInfo, ITS_USHORT gttLen);
SS7DLLAPI int SCCP_DecodeAddr_ANSI(const SCCP_ADDR *addr, ITS_OCTET* addrInd,
                                   ITS_UINT* pc, ITS_OCTET *ssn,
                                   ITS_OCTET* gttInfo, ITS_USHORT* gttLen);

SS7DLLAPI int SCCP_ComputeMSize_ANSI(ITS_OCTET which);

/*
 * Application status requests.
 */
SS7DLLAPI int SCCP_SendUserInService_ANSI(ITS_HANDLE handle,
                                          ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendUserOutOfService_ANSI(ITS_HANDLE handle,
                                             ITS_UINT pc, ITS_OCTET ssn);
SS7DLLAPI int SCCP_SendSetCongestion_ANSI(ITS_HANDLE handle,
                                          ITS_UINT pc, ITS_OCTET ssn,
                                          ITS_OCTET cong);

/*
 * primitives
 */
/*** CR ***/
SS7DLLAPI int SCCP_SendConnectionRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRequest_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                 ITS_HDR *hdr,
                                                 ITS_SCCP_IE *ies, int *ieCount);

/*** CC ***/
SS7DLLAPI int SCCP_SendConnectionConfirm_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionConfirm_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                 ITS_HDR *hdr,
                                                 ITS_SCCP_IE *ies, int *ieCount);

/*** CREF ***/
SS7DLLAPI int SCCP_SendConnectionRefused_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveConnectionRefused_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                 ITS_HDR *hdr,
                                                 ITS_SCCP_IE *ies, int *ieCount);

/*** RLSD ***/
SS7DLLAPI int SCCP_SendReleased_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                     ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleased_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                        ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int *ieCount);

/*** RLC ***/
SS7DLLAPI int SCCP_SendReleaseComplete_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveReleaseComplete_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm1_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                      ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm1_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                         ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int *ieCount);

/*** DT1 ***/
SS7DLLAPI int SCCP_SendDataForm2_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                      ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveDataForm2_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                         ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int *ieCount);

/*** AK ***/
SS7DLLAPI int SCCP_SendAcknowledgement_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveAcknowledgement_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/*** UDT ***/
SS7DLLAPI int SCCP_SendUnitData_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                     ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitData_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                        ITS_HDR *hdr,
                                        ITS_SCCP_IE *ies, int *ieCount);

/*** XUDT ***/
SS7DLLAPI int SCCP_SendExtendedUnitData_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitData_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** LUDT ***/
SS7DLLAPI int SCCP_SendLongUnitData_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitData_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                            ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int *ieCount);
/*** UDTS ***/
SS7DLLAPI int SCCP_SendUnitDataService_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveUnitDataService_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                               ITS_HDR *hdr,
                                               ITS_SCCP_IE *ies, int *ieCount);

/*** XUDTS ***/
SS7DLLAPI int SCCP_SendExtendedUnitDataService_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                                    ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExtendedUnitDataService_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                       ITS_HDR *hdr,
                                                       ITS_SCCP_IE *ies, int *ieCount);

/*** LUDTS ***/
SS7DLLAPI int SCCP_SendLongUnitDataService_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveLongUnitDataService_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                   ITS_HDR *hdr,
                                                   ITS_SCCP_IE *ies, int *ieCount);

/*** ED ***/
SS7DLLAPI int SCCP_SendExpeditedData_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                          ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedData_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                             ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int *ieCount);

/*** EA ***/
SS7DLLAPI int SCCP_SendExpeditedDataAck_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                             ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveExpeditedDataAck_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                ITS_HDR *hdr,
                                                ITS_SCCP_IE *ies, int *ieCount);

/*** RSR ***/
SS7DLLAPI int SCCP_SendResetRequest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetRequest_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                            ITS_HDR *hdr,
                                            ITS_SCCP_IE *ies, int *ieCount);

/*** RSC ***/
SS7DLLAPI int SCCP_SendResetConfirmation_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveResetConfirmation_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                                 ITS_HDR *hdr,
                                                 ITS_SCCP_IE *ies, int *ieCount);

/*** ERR ***/
SS7DLLAPI int SCCP_SendError_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                  ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveError_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                     ITS_HDR *hdr,
                                     ITS_SCCP_IE *ies, int *ieCount);

/*** IT ***/
SS7DLLAPI int SCCP_SendInactivityTest_ANSI(ITS_HANDLE handle, ITS_HDR *hdr,
                                           ITS_SCCP_IE *ies, int ieCount);
SS7DLLAPI int SCCP_ReceiveInactivityTest_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                              ITS_HDR *hdr,
                                              ITS_SCCP_IE *ies, int *ieCount);

/******************************** SCCP PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/

/*
 * implementation functions.  Users should not invoke these.
 */
SS7DLLAPI int SCCP_Encode_ANSI(ITS_SCCP_IE *ies, int ieCount,
                               ITS_OCTET msgType, ITS_EVENT *event,
                               ITS_HDR *hdr, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_Decode_ANSI(ITS_SCCP_IE *ies, int *ieCount,
                               ITS_EVENT *ev, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_EncodeMTP3_ANSI(ITS_OCTET* data, ITS_USHORT* len,
                                   ITS_OCTET mType, ITS_SCCP_IE *ies,
                                   int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_DecodeMTP3_ANSI(ITS_OCTET *data, ITS_USHORT len,
                                   ITS_OCTET* mType, ITS_SCCP_IE *ies,
                                   int *ieCount, SCCP_MSG_DESC* desc);

SS7DLLAPI int SCCP_SendEvent_ANSI(ITS_HANDLE handle, ITS_OCTET type,
                                  ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                  int ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI int SCCP_ReceiveEvent_ANSI(ITS_HANDLE handle, ITS_EVENT *ev,
                                     ITS_HDR *hdr, ITS_SCCP_IE *ies,
                                     int *ieCount, SCCP_MSG_DESC* desc);
SS7DLLAPI SCCP_MSG_DESC *SCCP_GetDescriptor_ANSI(ITS_OCTET which);

ITS_BOOLEAN SCCP_IsSSNEquipped_ANSI(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_BOOLEAN SCCP_IsSSNAllowed_ANSI(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);
ITS_OCTET   SCCP_IsSSNCongested_ANSI(ITS_OCTET ni, ITS_UINT pc, ITS_OCTET ssn);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_SCCP_ANSI_H_ */
