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
 *  ID: $Id: 
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
 * LOG: Revision 9.2  2005/05/06 05:31:43  adutta
 * LOG: MTP route pegs declaration
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 07:26:07  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1.4.1.6.1  2005/01/31 11:35:27  snagesh
 * LOG: Peg structures modified
 * LOG:
 * LOG: Revision 1.1.4.1  2004/08/10 12:28:43  kannanp
 * LOG: Create Public Interface for MTP3 Pegs - propagated from TCS.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_MTP3_PEGS_H_
#define _ITS_MTP3_PEGS_H_

#ident "$Id: mtp3_pegs.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $"

/*
 *  MTP3 Peg Public interface
 *
 */

typedef struct
{
    ITS_UINT msgPause;
    ITS_UINT msgResume;
    ITS_UINT msgStatus;
    ITS_UINT initialize;
    ITS_UINT terminate;
    ITS_UINT msgReceivedInError;
    ITS_UINT changeover;
    ITS_UINT changeback;
    ITS_UINT slUnavailable;
    ITS_UINT linkInhibit;
    ITS_UINT linkUnInhibit;
    ITS_UINT linkforceUninhibit;
    ITS_UINT congestion;
    ITS_UINT slsUnavailable;
    ITS_UINT tfcReceived;
    ITS_UINT tfaReceived;
    ITS_UINT routesetUnavailable;
    ITS_UINT adjacentSpUnaccesible;
    ITS_UINT userpartEnable;
    ITS_UINT userpartDisable;
}
MTP3_GenPegs;

typedef struct
{
    ITS_UINT cooTx;
    ITS_UINT cooRx;
    ITS_UINT coaTx;
    ITS_UINT coaRx;
    ITS_UINT ecoTx;
    ITS_UINT ecoRx;
    ITS_UINT ecaTx;
    ITS_UINT ecaRx;
    ITS_UINT cbdTx;
    ITS_UINT cbdRx;
    ITS_UINT cbaTx;
    ITS_UINT cbaRx;
    ITS_UINT linTx;
    ITS_UINT linRx;
    ITS_UINT liaTx;
    ITS_UINT liaRx;
    ITS_UINT lunTx;
    ITS_UINT lunRx;
    ITS_UINT luaTx;
    ITS_UINT luaRx;
    ITS_UINT lidTx;
    ITS_UINT lidRx;
    ITS_UINT lfuTx;
    ITS_UINT lfuRx;
    ITS_UINT lliTx;
    ITS_UINT lliRx;
    ITS_UINT lriTx;
    ITS_UINT lriRx;
    ITS_UINT dlcTx;
    ITS_UINT dlcRx;
    ITS_UINT cssTx;
    ITS_UINT cssRx;
    ITS_UINT cnsTx;
    ITS_UINT cnsRx;
    ITS_UINT cnpTx;
    ITS_UINT cnpRx;
    ITS_UINT upuTx;
    ITS_UINT upuRx;
    ITS_UINT sltmTx;
    ITS_UINT sltmRx;
    ITS_UINT sltaTx;
    ITS_UINT sltaRx;
}
MTP3_LinkPegs;

typedef struct
{
    ITS_UINT tfaTx;
    ITS_UINT tfaRx;
    ITS_UINT tfpTx;
    ITS_UINT tfpRx;
    ITS_UINT rstTx;
    ITS_UINT rstRx;
    ITS_UINT tfrRx;
    ITS_UINT tfcTx;
    ITS_UINT tfcRx;
    ITS_UINT sifTx;
}
MTP3_RoutePegs;
 
    




#ifdef __cplusplus
extern "C"
{
#endif


ITSSS7DLLAPI int MTP3_GetAllGeneralPegs(MTP3_GenPegs *genPegs);

ITSSS7DLLAPI int MTP3_ClearAllGeneralPegs();

ITSSS7DLLAPI int MTP3_CleaGeneralPeg( ITS_UINT pegId);

ITSSS7DLLAPI int MTP3_GetAllLinkPegs(ITS_USHORT linkSet,
                                     ITS_USHORT linkId,
                                     MTP3_LinkPegs *linkPegs);

ITSSS7DLLAPI int MTP3_ClearAllLinkPegs(ITS_USHORT linkSet,
                                       ITS_USHORT linkCode);

ITSSS7DLLAPI int MTP3_ClearLinkPeg(ITS_USHORT linkSet,
                                   ITS_USHORT linkCode,
                                   ITS_UINT pegId);

#ifdef __cplusplus
}
#endif


#endif /*_ITS_MTP3_PEGS_H_*/
