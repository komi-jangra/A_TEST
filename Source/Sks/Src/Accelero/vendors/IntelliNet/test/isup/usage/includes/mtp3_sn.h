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
 *  ID: $Id: mtp3_sn.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
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

#ident "$Id: mtp3_sn.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $"

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

#endif

#endif /* _ITS_MTP3_SN_H_ */

