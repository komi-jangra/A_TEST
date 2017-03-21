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
 * LOG: Revision 1.1.1.1  2007/10/08 11:12:26  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1  2007/09/24 05:33:45  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/06/25 12:04:18  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:19:28  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.2  2006/07/05 10:17:25  gdevanand
 * LOG: Changes for combined itsmcc driver (badri)
 * LOG:
 * LOG: Revision 1.1  2006/01/25 05:33:56  yranade
 * LOG: First Cut (badri)
 * LOG:
 * LOG: Revision 1.1  2005/11/24 06:05:22  yranade
 * LOG: Create Baseline GSM-BSC Infrastructure.
 * LOG:
 *
 * ID: $Id: lapd_adaptation_layer.h,v 1.2 2007-10-23 03:01:55 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: lapd_adaptation_layer.h,v 1.2 2007-10-23 03:01:55 bsccs2 Exp $"

#ifndef LAPD_ADAPTATION_LAYER_H
#define LAPD_ADAPTATION_LAYER_H
#include <its.h>
/* config data hash defs */
#define NUM_APPTEI 128
#define MAX_TS_VAL 128
/* end here */
/**
 * Definitions used for SAPIs
 */
#define TRAFFIC_MANAGEMENT_SAPI          0
#define NETWORK_MANAGEMENT_SAPI          62


#define LAPD_SAPI_0  0x00
#define LAPD_SAPI_62 0x3E
#define LAPD_SAPI_63 0x3F
/** 
 * Definitions for DL primitives
 */
#define DL_EST_IN     20     /* DL_ESTABLISH_INDICATION */
#define DL_REL_IN     21     /* DL_RELEASE_INDICATION   */
#define DL_U_DA_IN    22     /* DL_UNIT_DATA_INDICATION */
#define DL_DA_IN      23     /* DL_DATA_INDICATION      */
#define DL_EST_CF     24     /* DL_ESTABLISH_CONFIRM    */
#define DL_REL_CF     25     /* DL_RELEASE_CONFIRM      */
#define DL_SWITCHOVER_IN   26     /* DL_SWITCHOVER_INDICATION */
#define DL_DA_RQ        13  /*
                             *  To pass layer 3 messages to and from the
                             *  data link data link layer which are to be
                             *  transmitted, or have been received, using
                             *  unacknowledged operation.
                             */
#define DL_EST_RQ       14  /*
                             *  To request the outcome of the procedures
                             *  for establishing multiple frame operation.
                             */
#define DL_REL_RQ       15  /*
                             *  To request the  terminating a previously
                             *  established multiple frame operation session.
                             *  In the case of a data link layer malfunction,
                             *  layer 3 will be notified by a RELEASE
                             *  indication.
                             */
#define DL_U_DA_RQ      16  /*
                             *  To pass L3 messages to the data link layer
                             *  which are to be transmitted using
                             *  unacknowledged operation.
                             */
#define DL_ST_RQ        17  /* FLOW ON/OFF */
/**
 * Function to be implemented by LAPD interface layer 
 * for each SAPI to receive LAPD message 
 */
#ifdef LAPD_HA
/* lapd ha hash defs */
#define CTRL_CONFIG_COMPLETE    1 
#define CTRL_CARD_STATE         2 
#define CARD_ACTIVE            1
#define STANDBY                2
#define CONFIGURED             3
#define PEER_ABSENT            4
/* end here */
#endif
typedef ITS_INT 
(*AL3_READ_PROC_FUNC)(ITS_OCTET tei, 
ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength);
/**
 * Data structure to store LAPD interface handler
 * read procedure function calbacks
 */
typedef struct 
{
	AL3_READ_PROC_FUNC al3Sapi0ReadProcPtr;
	AL3_READ_PROC_FUNC al3Sapi62ReadProcPtr;
	AL3_READ_PROC_FUNC al3Sapi63ReadProcPtr;
}
AL3_READ_PROC_DATA_STRUCTURE;
/**
 * APIs given by LAPD adaptation layer to LAPD interface layer
 */
#ifdef __cplusplus
extern "C"
{
#endif

ITS_INT 
AL3_Send_L2Req(
ITS_OCTET sapi,
ITS_OCTET tei,
ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength);

ITS_INT 
get_Lapd_Link_Sts_Req(ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength);



ITS_INT Clear_Stats();

#ifdef __cplusplus
}
#endif
/**
 * EOF
 */
#endif
