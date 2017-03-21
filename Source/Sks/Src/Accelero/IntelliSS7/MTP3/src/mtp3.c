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
 *  ID: $Id: mtp3.c,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:47  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:13  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:50:18  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1.6.3  2005/02/24 11:56:42  mmanikandan
 * LOG: PPrint is modified.
 * LOG:
 * LOG: Revision 7.2.10.1.6.2  2004/12/17 03:34:28  randresol
 * LOG: Comment out Pprint function due to compilation errors
 * LOG:
 * LOG: Revision 7.2.10.1.6.1  2004/12/16 02:15:06  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.2.10.1  2004/09/21 06:55:50  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.2  2003/01/06 22:11:41  mmiers
 * LOG: Tandem port.
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
 * LOG: Revision 5.4  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:21:35  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:47  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:11  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/03/28 23:25:00  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.4  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 3.3  2000/09/01 20:56:28  mmiers
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:32  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:01:58  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:26  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:24:31  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.7  1999/12/01 00:11:17  mmiers
 * LOG:
 * LOG:
 * LOG: Get GDI working.
 * LOG:
 * LOG: Revision 1.6  1999/06/23 19:56:39  mmiers
 * LOG:
 * LOG:
 * LOG: Rework MTP3 for saner implementation of dual protocols.
 * LOG:
 * LOG: Revision 1.5  1999/03/12 23:24:44  mmiers
 * LOG:
 * LOG:
 * LOG: Finish dual protocol family support.
 * LOG:
 * LOG: Revision 1.4  1998/10/15 17:26:50  mmiers
 * LOG: Add C++ API for MTP3.
 * LOG:
 * LOG: Revision 1.3  1998/09/25 20:29:46  mmiers
 * LOG: Build MTP3 library (all 2 functions).
 * LOG:
 * LOG: Revision 1.2  1998/09/25 20:12:22  mmiers
 * LOG: Build MTP3 project.
 * LOG:
 *
 *****************************************************************************/

#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include <its.h>
#include <its_license.h>

#ident "$Id: mtp3.c,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $"

#if defined(CCITT)
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(PRC)
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/mtp3.h>
#else
#error "Protocol not defined."
#endif

/*
 * header
 */
#define MTP3_PHDR   "-------------- MTP3 ----------------\n"
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
 * User Parts
 */
static char *userParts[] =
{
    "SNMM",
    "MTN  Signalling network test/maint. message",
    "",
    "SCCP",
    "TUP",
    "ISUP",
    "DUP_CIRC",
    "DUP_FAC",
    "MTP_TEST",
    "BROAD_ISUP",
    "SAT_ISUP",
    "SPARE3",
    "SPARE4",
    "ECIS6",
    "PRIVATE",
    "SPARE5"
};

#if defined(CCITT)

SS7DLLAPI int  CCITT_MTP3_Variant = CCITT_MTP3_WHITE_BOOK;

/*.implementation:extern
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
SS7DLLAPI int
MTP3_SetVariant_CCITT(int variant)
{
    switch (variant)
    {
    case CCITT_MTP3_BLUE_BOOK:
    case CCITT_MTP3_WHITE_BOOK:
    case CCITT_MTP3_WHITE_BOOK_97:
        CCITT_MTP3_Variant = variant;
    }

    return (ITS_EINVALIDARGS);
}

/*.implementation:extern
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
SS7DLLAPI int
MTP3_GetVariant_CCITT()
{
    return (CCITT_MTP3_Variant);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Encode an ITS_EVENT with an ITU MTP message
 *
 *  Input Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 *      MTP3_Decode_CCITT
 ************************************************************************/
SS7DLLAPI int
MTP3_Encode_CCITT(ITS_EVENT* ev, ITS_OCTET type, MTP3_HEADER* hdr,
                  ITS_OCTET* data, ITS_USHORT len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    ITS_EVENT_INIT(ev, ITS_MTP3_CCITT_SRC,
                   (ITS_USHORT)(sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + len));

    ev->data[0] = type;
    memcpy(&ev->data[1], hdr, sizeof(MTP3_HEADER));
    memcpy(&ev->data[1 + sizeof(MTP3_HEADER)], data, len);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Decode an ITS_EVENT with an ITU MTP message
 *
 *  Input Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_Decode_CCITT(ITS_EVENT* ev, ITS_OCTET* type, MTP3_HEADER* hdr,
                  ITS_OCTET* data, ITS_USHORT* len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    if (ev->len < (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)))
    {
        return (ITS_ENOMSG);
    }

    *type = ev->data[0];
    *len = (ITS_USHORT)(ev->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)));
    memcpy(hdr, &ev->data[1], sizeof(MTP3_HEADER));
    memcpy(data, &ev->data[1 + sizeof(MTP3_HEADER)], *len);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Pretty print an MTP3 header
 *
 *  Input Parameters:
 *      rb - ring buffer to print into
 *      bCount - the current byte count into the SS7 message
 *      hdr - the MTP3 header to print
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
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_PPrint_CCITT(RINGBUF_Manager *rb, ITS_UINT *bCount,
                  MTP3_HEADER_CCITT *hdr)
{
    int tmp, ret = 0;
    ITS_OCTET ni, pri, up;
    MTP3_POINT_CODE_CCITT pc;
    ITS_UINT pcVal;

    /* header */
    ret = PPrint(rb, MTP3_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* SIO */
    up = hdr->sio & MTP3_SIO_UP_MASK;
    pri = (hdr->sio & MTP3_MPC_MASK) >> 4;
    ni = (hdr->sio & MTP3_NIC_MASK) >> 6;
    tmp = PPrint(rb, " %3d.  %02x  %02b|%02b|%04b  "
                     "NI = %d | PRI = %d | User Part = %d (%s)\n",
                 *bCount, hdr->sio,
                 ni, pri, up, ni, pri, up, userParts[up]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* DPC */
    MTP3_RL_GET_DPC_CCITT(hdr->label, pc);
    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                     "DPC = %d-%d-%d\n",
                 *bCount, hdr->label.data[0],
                 hdr->label.data[0],
                 MTP3_PC_GET_NETWORK_CCITT(pc),
                 MTP3_PC_GET_CLUSTER_CCITT(pc),
                 MTP3_PC_GET_MEMBER_CCITT(pc));
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
    tmp = PPrint(rb, " %3d.  %02x   %02b|%06b  OPC low/DPC hi : DPC Value 0x%04x\n",
                 *bCount, hdr->label.data[1],
                 (hdr->label.data[1] & MTP3_RL_OPC_LOW_MASK_CCITT) >> 6,
                 hdr->label.data[1] & MTP3_RL_DPC_HI_MASK_CCITT,
                 pcVal);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* OPC */
    MTP3_RL_GET_OPC_CCITT(hdr->label, pc);
    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                     "OPC = %d-%d-%d\n",
                 *bCount, hdr->label.data[2],
                 hdr->label.data[2],
                 MTP3_PC_GET_NETWORK_CCITT(pc),
                 MTP3_PC_GET_CLUSTER_CCITT(pc),
                 MTP3_PC_GET_MEMBER_CCITT(pc));
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    pcVal = MTP3_PC_GET_VALUE_CCITT(pc);
    tmp = PPrint(rb, " %3d.  %02x   %04b|%04b  SLS =%d, OPC hi, OPC Value 0x%04x\n",
                 *bCount, hdr->label.data[3],
                 hdr->label.data[3],
                 MTP3_RL_GET_SLS_CCITT(hdr->label),
                 hdr->label.data[3] & MTP3_RL_OPC_HI_MASK_CCITT,
                 pcVal);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    return (ret);
}

#elif defined(ANSI)

SS7DLLAPI int  ANSI_MTP3_Variant = ANSI_MTP3_1996;

/*.implementation:extern
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
SS7DLLAPI int
MTP3_SetVariant_ANSI(int variant)
{
    switch (variant)
    {
    case ANSI_MTP3_1988:
    case ANSI_MTP3_1992:
    case ANSI_MTP3_1996:
        ANSI_MTP3_Variant = variant;
    }

    return (ITS_EINVALIDARGS);
}

/*.implementation:extern
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
SS7DLLAPI int
MTP3_GetVariant_ANSI()
{
    return (ANSI_MTP3_Variant);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Encode an ITS_EVENT with an ANSI MTP message
 *
 *  Input Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_Encode_ANSI(ITS_EVENT* ev, ITS_OCTET type, MTP3_HEADER* hdr,
                 ITS_OCTET* data, ITS_USHORT len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    ITS_EVENT_INIT(ev, ITS_MTP3_ANSI_SRC,
                   (ITS_USHORT)(sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + len));

    if (ev->data == NULL)
    {
        return (ITS_ENOMEM);
    }

    ev->data[0] = type;

    memcpy(&ev->data[1], hdr, sizeof(MTP3_HEADER));
    memcpy(&ev->data[1 + sizeof(MTP3_HEADER)], data, len);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Decode an ITS_EVENT with an ANSI MTP message
 *
 *  Input Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_Decode_ANSI(ITS_EVENT* ev, ITS_OCTET* type, MTP3_HEADER* hdr,
                 ITS_OCTET* data, ITS_USHORT* len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    if (ev->len < (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)))
    {
        return (ITS_ENOMSG);
    }

    *type = ev->data[0];
    *len = (ITS_USHORT)(ev->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)));
    memcpy(hdr, &ev->data[1], sizeof(MTP3_HEADER));
    memcpy(data, &ev->data[1 + sizeof(MTP3_HEADER)], *len);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Pretty print an MTP3 header
 *
 *  Input Parameters:
 *      rb - ring buffer to print into
 *      bCount - the current byte count into the SS7 message
 *      hdr - the MTP3 header to print
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
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_PPrint_ANSI(RINGBUF_Manager *rb, ITS_UINT *bCount,
                 MTP3_HEADER_ANSI *hdr)
{
    int tmp, ret = 0;
    ITS_OCTET ni, pri, up;
    MTP3_POINT_CODE_ANSI pc;
    ITS_UINT pcVal;

    /* header */
    ret = PPrint(rb, MTP3_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* SIO */
    up = hdr->sio & MTP3_SIO_UP_MASK;
    pri = (hdr->sio & MTP3_MPC_MASK) >> 4;
    ni = (hdr->sio & MTP3_NIC_MASK) >> 6;
    tmp = PPrint(rb, " %3d.  %02x  %02b|%02b|%04b  "
                     "NI = %d | PRI = %d | User Part = %d (%s)\n",
                 *bCount, hdr->sio,
                 ni, pri, up, ni, pri, up, userParts[up]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* DPC */
    MTP3_RL_GET_DPC_ANSI(hdr->label, pc);
    pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                     "(member) DPC = %d-%d-%d : 0x%06x\n",
                 *bCount, hdr->label.dpc.data[0],
                 hdr->label.dpc.data[0],
                 MTP3_PC_GET_NETWORK_ANSI(pc),
                 MTP3_PC_GET_CLUSTER_ANSI(pc),
                 MTP3_PC_GET_MEMBER_ANSI(pc),
                 pcVal);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* cluster */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (cluster)\n",
                 *bCount, hdr->label.dpc.data[1],
                 hdr->label.dpc.data[1]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* network */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (network)\n",
                 *bCount, hdr->label.dpc.data[2],
                 hdr->label.dpc.data[2]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* OPC */
    MTP3_RL_GET_OPC_ANSI(hdr->label, pc);
    pcVal = MTP3_PC_GET_VALUE_ANSI(pc);
    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                     "(member) OPC = %d-%d-%d : 0x%06x\n",
                 *bCount, hdr->label.opc.data[0],
                 hdr->label.opc.data[0],
                 MTP3_PC_GET_NETWORK_ANSI(pc),
                 MTP3_PC_GET_CLUSTER_ANSI(pc),
                 MTP3_PC_GET_MEMBER_ANSI(pc),
                 pcVal);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* cluster */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (cluster)\n",
                 *bCount, hdr->label.opc.data[1],
                 hdr->label.opc.data[1]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* network */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (network)\n",
                 *bCount, hdr->label.opc.data[2],
                 hdr->label.opc.data[2]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* SLS */
    tmp = PPrint(rb, " %3d.  %02x    %08b  SLS = %d\n",
                 *bCount, hdr->label.sls,
                 hdr->label.sls, hdr->label.sls);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    return (ret);
}

#elif defined(PRC)

SS7DLLAPI int  PRC_MTP3_Variant = PRC_MTP3_WHITE_BOOK;

/*.implementation:extern
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
SS7DLLAPI int
MTP3_SetVariant_PRC(int variant)
{
    switch (variant)
    {
    case PRC_MTP3_BLUE_BOOK:
    case PRC_MTP3_WHITE_BOOK:
    case PRC_MTP3_WHITE_BOOK_97:
        PRC_MTP3_Variant = variant;
    }

    return (ITS_EINVALIDARGS);
}

/*.implementation:extern
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
SS7DLLAPI int
MTP3_GetVariant_PRC()
{
    return (PRC_MTP3_Variant);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Encode an ITS_EVENT with an PRC MTP message
 *
 *  Input Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_Encode_PRC(ITS_EVENT* ev, ITS_OCTET type, MTP3_HEADER* hdr,
                ITS_OCTET* data, ITS_USHORT len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    ITS_EVENT_INIT(ev, ITS_MTP3_PRC_SRC,
                   sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + len);

    if (ev->data == NULL)
    {
        return (ITS_ENOMEM);
    }

    ev->data[0] = type;

    memcpy(&ev->data[1], hdr, sizeof(MTP3_HEADER));
    memcpy(&ev->data[1 + sizeof(MTP3_HEADER)], data, len);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Decode an ITS_EVENT with an PRC MTP message
 *
 *  Input Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_Decode_PRC(ITS_EVENT* ev, ITS_OCTET* type, MTP3_HEADER* hdr,
                ITS_OCTET* data, ITS_USHORT* len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_PRC_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    if (ev->len < (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)))
    {
        return (ITS_ENOMSG);
    }

    *type = ev->data[0];
    *len = ev->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER));
    memcpy(hdr, &ev->data[1], sizeof(MTP3_HEADER));
    memcpy(data, &ev->data[1 + sizeof(MTP3_HEADER)], *len);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Pretty print an MTP3 header
 *
 *  Input Parameters:
 *      rb - ring buffer to print into
 *      bCount - the current byte count into the SS7 message
 *      hdr - the MTP3 header to print
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
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_PPrint_PRC(RINGBUF_Manager *rb, ITS_UINT *bCount,
                MTP3_HEADER_PRC *hdr)
{
    int tmp, ret = 0;
    ITS_OCTET ni, pri, up;
    MTP3_POINT_CODE_PRC pc;
    ITS_UINT pcVal;

    /* header */
    ret = PPrint(rb, MTP3_PHDR);
    if (ret < 0)
    {
        return (ret);
    }

    /* SIO */
    up = hdr->sio & MTP3_SIO_UP_MASK;
    pri = (hdr->sio & MTP3_MPC_MASK) >> 4;
    ni = (hdr->sio & MTP3_NIC_MASK) >> 6;
    tmp = PPrint(rb, " %3d.  %02x  %02b|%02b|%04b  "
                     "NI = %d | PRI = %d | User Part = %d (%s)\n",
                 *bCount, hdr->sio,
                 ni, pri, up, ni, pri, up, userParts[up]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* DPC */
    MTP3_RL_GET_DPC_PRC(hdr->label, pc);
    pcVal = MTP3_PC_GET_VALUE_PRC(pc);
    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                     "(member) DPC = %d-%d-%d : 0x%06x\n",
                 *bCount, hdr->label.dpc.data[0],
                 hdr->label.dpc.data[0],
                 MTP3_PC_GET_NETWORK_PRC(pc),
                 MTP3_PC_GET_CLUSTER_PRC(pc),
                 MTP3_PC_GET_MEMBER_PRC(pc),
                 pcVal);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* cluster */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (cluster)\n",
                 *bCount, hdr->label.dpc.data[1],
                 hdr->label.dpc.data[1]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* network */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (network)\n",
                 *bCount, hdr->label.dpc.data[2],
                 hdr->label.dpc.data[2]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* OPC */
    MTP3_RL_GET_OPC_PRC(hdr->label, pc);
    pcVal = MTP3_PC_GET_VALUE_PRC(pc);
    tmp = PPrint(rb, " %3d.  %02x    %08b  "
                     "(member) OPC = %d-%d-%d : 0x%06x\n",
                 *bCount, hdr->label.opc.data[0],
                 hdr->label.opc.data[0],
                 MTP3_PC_GET_NETWORK_PRC(pc),
                 MTP3_PC_GET_CLUSTER_PRC(pc),
                 MTP3_PC_GET_MEMBER_PRC(pc),
                 pcVal);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* cluster */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (cluster)\n",
                 *bCount, hdr->label.opc.data[1],
                 hdr->label.opc.data[1]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* network */
    tmp = PPrint(rb, " %3d.  %02x    %08b  (network)\n",
                 *bCount, hdr->label.opc.data[2],
                 hdr->label.opc.data[2]);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    /* SLS */
    tmp = PPrint(rb, " %3d.  %02x    %08b  SLS = %d\n",
                 *bCount, hdr->label.sls,
                 hdr->label.sls);
    CHECK_RETURN(tmp, ret);
    (*bCount)++;

    return (ret);
}

#elif defined(TTC)

SS7DLLAPI int  TTC_MTP3_Variant = TTC_MTP3_WHITE_BOOK;

/*.implementation:extern
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
SS7DLLAPI int
MTP3_SetVariant_TTC(int variant)
{
    switch (variant)
    {
    case TTC_MTP3_BLUE_BOOK:
    case TTC_MTP3_WHITE_BOOK:
    case TTC_MTP3_WHITE_BOOK_97:
        TTC_MTP3_Variant = variant;
    }

    return (ITS_EINVALIDARGS);
}

/*.implementation:extern
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
SS7DLLAPI int
MTP3_GetVariant_TTC()
{
    return (TTC_MTP3_Variant);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Encode an ITS_EVENT with an PRC MTP message
 *
 *  Input Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_Encode_TTC(ITS_EVENT* ev, ITS_OCTET type, MTP3_HEADER* hdr,
                ITS_OCTET* data, ITS_USHORT len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    ITS_EVENT_INIT(ev, ITS_MTP3_TTC_SRC,
                   sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + len);

    if (ev->data == NULL)
    {
        return (ITS_ENOMEM);
    }

    ev->data[0] = type;

    memcpy(&ev->data[1], hdr, sizeof(MTP3_HEADER));
    memcpy(&ev->data[1 + sizeof(MTP3_HEADER)], data, len);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Decode an ITS_EVENT with an PRC MTP message
 *
 *  Input Parameters:
 *      ev - an ITS_EVENT containing the MTP3 message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      type - one of USER-DATA, STATUS, or PAUSE-RESUME
 *      hdr - the routing label, including SLS
 *      data - the SIF, minus SLS
 *      len - byte count of data
 *
 *  Return Value:
 *		None.
 *
 *  Notes:
 *
 *  See Also:
 ************************************************************************/
SS7DLLAPI int
MTP3_Decode_TTC(ITS_EVENT* ev, ITS_OCTET* type, MTP3_HEADER* hdr,
                ITS_OCTET* data, ITS_USHORT* len)
{
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_MTP3))
    {
        return (ITS_ENOLICENSE);
    }

    if (ev->len < (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)))
    {
        return (ITS_ENOMSG);
    }

    *type = ev->data[0];
    *len = ev->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER));
    memcpy(hdr, &ev->data[1], sizeof(MTP3_HEADER));
    memcpy(data, &ev->data[1 + sizeof(MTP3_HEADER)], *len);

    return (ITS_SUCCESS);
}


#endif
