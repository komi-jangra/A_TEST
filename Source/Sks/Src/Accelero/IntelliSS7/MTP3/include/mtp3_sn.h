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
 *  ID: $Id: mtp3_sn.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
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
 * LOG: Revision 7.1.46.2  2005/01/31 11:33:20  snagesh
 * LOG: MTP3 OSS APIs short names added
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
 * LOG: Revision 6.2  2002/07/03 15:29:30  mmiers
 * LOG: Update for china
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4  2002/01/02 19:55:46  mmiers
 * LOG: Convert to long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.3  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_MTP3_SN_H_
#define _ITS_MTP3_SN_H_

#ident "$Id: mtp3_sn.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $"

#if defined(CCITT)

#define MTP3_POINT_CODE             MTP3_POINT_CODE_CCITT

#define MTP3_PC_SPID_MASK           MTP3_PC_SPID_MASK_CCITT
#define MTP3_PC_SET_MEMBER          MTP3_PC_SET_MEMBER_CCITT
#define MTP3_PC_GET_MEMBER          MTP3_PC_GET_MEMBER_CCITT
#define MTP3_PC_SET_CLUSTER         MTP3_PC_SET_CLUSTER_CCITT
#define MTP3_PC_GET_CLUSTER         MTP3_PC_GET_CLUSTER_CCITT
#define MTP3_PC_SET_NETWORK         MTP3_PC_SET_NETWORK_CCITT
#define MTP3_PC_GET_NETWORK         MTP3_PC_GET_NETWORK_CCITT
#define MTP3_PC_SET_VALUE           MTP3_PC_SET_VALUE_CCITT
#define MTP3_PC_GET_VALUE           MTP3_PC_GET_VALUE_CCITT

#define MTP3_ROUTING_LABEL          MTP3_ROUTING_LABEL_CCITT
#define MTP3_RL_SET_DPC             MTP3_RL_SET_DPC_CCITT
#define MTP3_RL_GET_DPC             MTP3_RL_GET_DPC_CCITT
#define MTP3_RL_SET_OPC             MTP3_RL_SET_OPC_CCITT
#define MTP3_RL_GET_OPC             MTP3_RL_GET_OPC_CCITT
#define MTP3_RL_SET_SLS             MTP3_RL_SET_SLS_CCITT
#define MTP3_RL_GET_SLS             MTP3_RL_GET_SLS_CCITT
#define MTP3_RL_SET_DPC_VALUE       MTP3_RL_SET_DPC_VALUE_CCITT
#define MTP3_RL_GET_DPC_VALUE       MTP3_RL_GET_DPC_VALUE_CCITT
#define MTP3_RL_SET_OPC_VALUE       MTP3_RL_SET_OPC_VALUE_CCITT
#define MTP3_RL_GET_OPC_VALUE       MTP3_RL_GET_OPC_VALUE_CCITT

#define MTP3_HEADER                 MTP3_HEADER_CCITT
#define MTP3_HDR_SET_SIO            MTP3_HDR_SET_SIO_CCITT
#define MTP3_HDR_GET_SIO            MTP3_HDR_GET_SIO_CCITT

#define MTP3_USER_DATA              MTP3_USER_DATA_CCITT

#define MTP3_PAUSE_RESUME           MTP3_PAUSE_RESUME_CCITT

#define MTP3_STATUS                 MTP3_STATUS_CCITT

#define MTP3_Encode                 MTP3_Encode_CCITT
#define MTP3_Decode                 MTP3_Decode_CCITT

#define MTP3_ManagementCallbacks    MTP3_CCITT_ManagementCallbacks

/*
 * get the right definitions for the protocol layers themselves
 */
#define ITS_MTP3                    ITS_MTP3_CCITT
#define ITS_MTP3_SRC                ITS_MTP3_CCITT_SRC

#elif defined(ANSI)

#define MTP3_POINT_CODE             MTP3_POINT_CODE_ANSI

#define MTP3_PC_SPID_MASK           MTP3_PC_SPID_MASK_ANSI
#define MTP3_PC_SET_MEMBER          MTP3_PC_SET_MEMBER_ANSI
#define MTP3_PC_GET_MEMBER          MTP3_PC_GET_MEMBER_ANSI
#define MTP3_PC_SET_CLUSTER         MTP3_PC_SET_CLUSTER_ANSI
#define MTP3_PC_GET_CLUSTER         MTP3_PC_GET_CLUSTER_ANSI
#define MTP3_PC_SET_NETWORK         MTP3_PC_SET_NETWORK_ANSI
#define MTP3_PC_GET_NETWORK         MTP3_PC_GET_NETWORK_ANSI
#define MTP3_PC_SET_VALUE           MTP3_PC_SET_VALUE_ANSI
#define MTP3_PC_GET_VALUE           MTP3_PC_GET_VALUE_ANSI

#define MTP3_ROUTING_LABEL          MTP3_ROUTING_LABEL_ANSI
#define MTP3_RL_SET_DPC             MTP3_RL_SET_DPC_ANSI
#define MTP3_RL_GET_DPC             MTP3_RL_GET_DPC_ANSI
#define MTP3_RL_SET_OPC             MTP3_RL_SET_OPC_ANSI
#define MTP3_RL_GET_OPC             MTP3_RL_GET_OPC_ANSI
#define MTP3_RL_SET_SLS             MTP3_RL_SET_SLS_ANSI
#define MTP3_RL_GET_SLS             MTP3_RL_GET_SLS_ANSI
#define MTP3_RL_SET_DPC_VALUE       MTP3_RL_SET_DPC_VALUE_ANSI
#define MTP3_RL_GET_DPC_VALUE       MTP3_RL_GET_DPC_VALUE_ANSI
#define MTP3_RL_SET_OPC_VALUE       MTP3_RL_SET_OPC_VALUE_ANSI
#define MTP3_RL_GET_OPC_VALUE       MTP3_RL_GET_OPC_VALUE_ANSI

#define MTP3_HEADER                 MTP3_HEADER_ANSI
#define MTP3_HDR_SET_SIO            MTP3_HDR_SET_SIO_ANSI
#define MTP3_HDR_GET_SIO            MTP3_HDR_GET_SIO_ANSI

#define MTP3_USER_DATA              MTP3_USER_DATA_ANSI

#define MTP3_PAUSE_RESUME           MTP3_PAUSE_RESUME_ANSI

#define MTP3_STATUS                 MTP3_STATUS_ANSI

#define MTP3_Encode             MTP3_Encode_ANSI
#define MTP3_Decode             MTP3_Decode_ANSI

#define MTP3_ManagementCallbacks    MTP3_ANSI_ManagementCallbacks

#define ITS_MTP3                    ITS_MTP3_ANSI
#define ITS_MTP3_SRC                ITS_MTP3_ANSI_SRC

#elif defined(PRC)

#define MTP3_POINT_CODE             MTP3_POINT_CODE_PRC

#define MTP3_PC_SPID_MASK           MTP3_PC_SPID_MASK_PRC
#define MTP3_PC_SET_MEMBER          MTP3_PC_SET_MEMBER_PRC
#define MTP3_PC_GET_MEMBER          MTP3_PC_GET_MEMBER_PRC
#define MTP3_PC_SET_CLUSTER         MTP3_PC_SET_CLUSTER_PRC
#define MTP3_PC_GET_CLUSTER         MTP3_PC_GET_CLUSTER_PRC
#define MTP3_PC_SET_NETWORK         MTP3_PC_SET_NETWORK_PRC
#define MTP3_PC_GET_NETWORK         MTP3_PC_GET_NETWORK_PRC
#define MTP3_PC_SET_VALUE           MTP3_PC_SET_VALUE_PRC
#define MTP3_PC_GET_VALUE           MTP3_PC_GET_VALUE_PRC

#define MTP3_ROUTING_LABEL          MTP3_ROUTING_LABEL_PRC
#define MTP3_RL_SET_DPC             MTP3_RL_SET_DPC_PRC
#define MTP3_RL_GET_DPC             MTP3_RL_GET_DPC_PRC
#define MTP3_RL_SET_OPC             MTP3_RL_SET_OPC_PRC
#define MTP3_RL_GET_OPC             MTP3_RL_GET_OPC_PRC
#define MTP3_RL_SET_SLS             MTP3_RL_SET_SLS_PRC
#define MTP3_RL_GET_SLS             MTP3_RL_GET_SLS_PRC
#define MTP3_RL_SET_DPC_VALUE       MTP3_RL_SET_DPC_VALUE_PRC
#define MTP3_RL_GET_DPC_VALUE       MTP3_RL_GET_DPC_VALUE_PRC
#define MTP3_RL_SET_OPC_VALUE       MTP3_RL_SET_OPC_VALUE_PRC
#define MTP3_RL_GET_OPC_VALUE       MTP3_RL_GET_OPC_VALUE_PRC

#define MTP3_HEADER                 MTP3_HEADER_PRC
#define MTP3_HDR_SET_SIO            MTP3_HDR_SET_SIO_PRC
#define MTP3_HDR_GET_SIO            MTP3_HDR_GET_SIO_PRC

#define MTP3_USER_DATA              MTP3_USER_DATA_PRC

#define MTP3_PAUSE_RESUME           MTP3_PAUSE_RESUME_PRC

#define MTP3_STATUS                 MTP3_STATUS_PRC

#define MTP3_Encode             MTP3_Encode_PRC
#define MTP3_Decode             MTP3_Decode_PRC

#define MTP3_ManagementCallbacks    MTP3_PRC_ManagementCallbacks

#define ITS_MTP3                    ITS_MTP3_PRC
#define ITS_MTP3_SRC                ITS_MTP3_PRC_SRC

#elif defined(TTC)

#define MTP3_POINT_CODE             MTP3_POINT_CODE_TTC

#define MTP3_PC_SPID_MASK           MTP3_PC_SPID_MASK_TTC
#define MTP3_PC_SET_MEMBER          MTP3_PC_SET_MEMBER_TTC
#define MTP3_PC_GET_MEMBER          MTP3_PC_GET_MEMBER_TTC
#define MTP3_PC_SET_CLUSTER         MTP3_PC_SET_CLUSTER_TTC
#define MTP3_PC_GET_CLUSTER         MTP3_PC_GET_CLUSTER_TTC
#define MTP3_PC_SET_NETWORK         MTP3_PC_SET_NETWORK_TTC
#define MTP3_PC_GET_NETWORK         MTP3_PC_GET_NETWORK_TTC
#define MTP3_PC_SET_VALUE           MTP3_PC_SET_VALUE_TTC
#define MTP3_PC_GET_VALUE           MTP3_PC_GET_VALUE_TTC

#define MTP3_ROUTING_LABEL          MTP3_ROUTING_LABEL_TTC
#define MTP3_RL_SET_DPC             MTP3_RL_SET_DPC_TTC
#define MTP3_RL_GET_DPC             MTP3_RL_GET_DPC_TTC
#define MTP3_RL_SET_OPC             MTP3_RL_SET_OPC_TTC
#define MTP3_RL_GET_OPC             MTP3_RL_GET_OPC_TTC
#define MTP3_RL_SET_SLS             MTP3_RL_SET_SLS_TTC
#define MTP3_RL_GET_SLS             MTP3_RL_GET_SLS_TTC
#define MTP3_RL_SET_DPC_VALUE       MTP3_RL_SET_DPC_VALUE_TTC
#define MTP3_RL_GET_DPC_VALUE       MTP3_RL_GET_DPC_VALUE_TTC
#define MTP3_RL_SET_OPC_VALUE       MTP3_RL_SET_OPC_VALUE_TTC
#define MTP3_RL_GET_OPC_VALUE       MTP3_RL_GET_OPC_VALUE_TTC

#define MTP3_HEADER                 MTP3_HEADER_TTC
#define MTP3_HDR_SET_SIO            MTP3_HDR_SET_SIO_TTC
#define MTP3_HDR_GET_SIO            MTP3_HDR_GET_SIO_TTC

#define MTP3_USER_DATA              MTP3_USER_DATA_TTC

#define MTP3_PAUSE_RESUME           MTP3_PAUSE_RESUME_TTC

#define MTP3_STATUS                 MTP3_STATUS_TTC

#define MTP3_Encode                 MTP3_Encode_TTC
#define MTP3_Decode                 MTP3_Decode_TTC

#define MTP3_ManagementCallbacks    MTP3_TTC_ManagementCallbacks

/*
 * get the right definitions for the protocol layers themselves
 */
#define ITS_MTP3                    ITS_MTP3_TTC
#define ITS_MTP3_SRC                ITS_MTP3_TTC_SRC

#endif

/******************************** MTP3 PRIVATE *******************************/
/******************************* USERS STAY OUT ******************************/

#if defined(CCITT)

#define MTP3_EnableUserPart     MTP3_EnableUserPart_CCITT
#define MTP3_DisableUserPart    MTP3_DisableUserPart_CCITT
#define MTP3_UserPartOwner      MTP3_UserPartOwner_CCITT
#define MTP3_SendEvent          MTP3_SendEvent_CCITT
#define MTP3_ReceiveEvent       MTP3_ReceiveEvent_CCITT

#elif defined(ANSI)

#define MTP3_EnableUserPart     MTP3_EnableUserPart_ANSI
#define MTP3_DisableUserPart    MTP3_DisableUserPart_ANSI
#define MTP3_UserPartOwner      MTP3_UserPartOwner_ANSI
#define MTP3_SendEvent          MTP3_SendEvent_ANSI
#define MTP3_ReceiveEvent       MTP3_ReceiveEvent_ANSI

#elif defined(PRC)

#define MTP3_EnableUserPart     MTP3_EnableUserPart_PRC
#define MTP3_DisableUserPart    MTP3_DisableUserPart_PRC
#define MTP3_UserPartOwner      MTP3_UserPartOwner_PRC
#define MTP3_SendEvent          MTP3_SendEvent_PRC
#define MTP3_ReceiveEvent       MTP3_ReceiveEvent_PRC

#elif defined(TTC)

#define MTP3_EnableUserPart     MTP3_EnableUserPart_TTC
#define MTP3_DisableUserPart    MTP3_DisableUserPart_TTC
#define MTP3_UserPartOwner      MTP3_UserPartOwner_TTC
#define MTP3_SendEvent          MTP3_SendEvent_TTC
#define MTP3_ReceiveEvent       MTP3_ReceiveEvent_TTC

#endif


/*
 * * * OSS APIs short names * * *
 */   
#if defined(ANSI)

#define MTP3_OSS_Start              MTP3_OSS_Start_ANSI
#define MTP3_OSS_Shutdown           MTP3_OSS_Shutdown_ANSI
#define MTP3_OSS_GetGeneralCfg      MTP3_OSS_GetGeneralCfg_ANSI
#define MTP3_OSS_SetGeneralCfg      MTP3_OSS_SetGeneralCfg_ANSI
#define MTP3_OSS_SetBehavior        MTP3_OSS_SetBehavior_ANSI
#define MTP3_OSS_GetBehavior        MTP3_OSS_GetBehavior_ANSI
#define MTP3_OSS_InhibitLink        MTP3_OSS_InhibitLink_ANSI
#define MTP3_OSS_UninhibitLink      MTP3_OSS_UninhibitLink_ANSI
#define MTP3_OSS_DeactivateLink     MTP3_OSS_DeactivateLink_ANSI
#define MTP3_OSS_ActivateLink       MTP3_OSS_ActivateLink_ANSI
#define MTP3_OSS_DeactivateLinkset  MTP3_OSS_DeactivateLinkset_ANSI
#define MTP3_OSS_ActivateLinkset    MTP3_OSS_ActivateLinkset_ANSI
#define MTP3_OSS_GetLinkset         MTP3_OSS_GetLinkset_ANSI
#define MTP3_OSS_GetLink            MTP3_OSS_GetLink_ANSI
#define MTP3_OSS_AddRemotePC        MTP3_OSS_AddRemotePC_ANSI
#define MTP3_OSS_RemoveRemotePC     MTP3_OSS_RemoveRemotePC_ANSI
#define MTP3_OSS_GetRemotePC        MTP3_OSS_GetRemotePC_ANSI
#define MTP3_OSS_GetLocalPC         MTP3_OSS_GetLocalPC_ANSI
#define MTP3_OSS_AddLinkset         MTP3_OSS_AddLinkset_ANSI
#define MTP3_OSS_RemoveLinkset      MTP3_OSS_RemoveLinkset_ANSI
#define MTP3_OSS_AddLink            MTP3_OSS_AddLink_ANSI
#define MTP3_OSS_RemoveLink         MTP3_OSS_RemoveLink_ANSI
#define MTP3_OSS_GetGeneralPegs     MTP3_OSS_GetGeneralPegs_ANSI
#define MTP3_OSS_ClearGeneralPeg    MTP3_OSS_ClearGeneralPeg_ANSI
#define MTP3_OSS_GetLinkPegs        MTP3_OSS_GetLinkPegs_ANSI
#define MTP3_OSS_ClearLinkPeg       MTP3_OSS_ClearLinkPeg_ANSI

#elif defined(CCITT) 

#define MTP3_OSS_Start              MTP3_OSS_Start_CCITT
#define MTP3_OSS_Shutdown           MTP3_OSS_Shutdown_CCITT
#define MTP3_OSS_GetGeneralCfg      MTP3_OSS_GetGeneralCfg_CCITT
#define MTP3_OSS_SetGeneralCfg      MTP3_OSS_SetGeneralCfg_CCITT
#define MTP3_OSS_SetBehavior        MTP3_OSS_SetBehavior_CCITT
#define MTP3_OSS_GetBehavior        MTP3_OSS_GetBehavior_CCITT
#define MTP3_OSS_InhibitLink        MTP3_OSS_InhibitLink_CCITT
#define MTP3_OSS_UninhibitLink      MTP3_OSS_UninhibitLink_CCITT
#define MTP3_OSS_DeactivateLink     MTP3_OSS_DeactivateLink_CCITT
#define MTP3_OSS_ActivateLink       MTP3_OSS_ActivateLink_CCITT
#define MTP3_OSS_DeactivateLinkset  MTP3_OSS_DeactivateLinkset_CCITT
#define MTP3_OSS_ActivateLinkset    MTP3_OSS_ActivateLinkset_CCITT
#define MTP3_OSS_GetLinkset         MTP3_OSS_GetLinkset_CCITT
#define MTP3_OSS_GetLink            MTP3_OSS_GetLink_CCITT
#define MTP3_OSS_AddRemotePC        MTP3_OSS_AddRemotePC_CCITT
#define MTP3_OSS_RemoveRemotePC     MTP3_OSS_RemoveRemotePC_CCITT
#define MTP3_OSS_GetRemotePC        MTP3_OSS_GetRemotePC_CCITT
#define MTP3_OSS_GetLocalPC         MTP3_OSS_GetLocalPC_CCITT
#define MTP3_OSS_AddLinkset         MTP3_OSS_AddLinkset_CCITT
#define MTP3_OSS_RemoveLinkset      MTP3_OSS_RemoveLinkset_CCITT
#define MTP3_OSS_AddLink            MTP3_OSS_AddLink_CCITT
#define MTP3_OSS_RemoveLink         MTP3_OSS_RemoveLink_CCITT
#define MTP3_OSS_GetGeneralPegs     MTP3_OSS_GetGeneralPegs_CCITT
#define MTP3_OSS_ClearGeneralPeg    MTP3_OSS_ClearGeneralPeg_CCITT
#define MTP3_OSS_GetLinkPegs        MTP3_OSS_GetLinkPegs_CCITT
#define MTP3_OSS_ClearLinkPeg       MTP3_OSS_ClearLinkPeg_CCITT

#elif defined(PRC) 
/* To be defined later */
#elif defined(TTC) 
/* To be defined later */
#endif


#endif /* _ITS_MTP3_SN_H_ */

