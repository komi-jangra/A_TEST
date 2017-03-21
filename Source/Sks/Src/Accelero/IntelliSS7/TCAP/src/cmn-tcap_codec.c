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
 *  ID: $Id: cmn-tcap_codec.c,v 1.1.1.1 2007-10-08 11:11:27 bsccs2 Exp $
 *
 *  LOG: $Log: not supported by cvs2svn $
 *  LOG: Revision 1.1.1.1  2007/10/04 13:23:56  bsccs2
 *  LOG: init tree
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/08/03 06:48:54  cvsadmin
 *  LOG: BscCs2
 *  LOG:
 *  LOG: Revision 1.1.1.1  2007/03/08 15:13:30  cvsadmin
 *  LOG: BSC project
 *  LOG:
 *  LOG: Revision 9.3  2005/05/25 05:20:38  adutta
 *  LOG: XUDT Changes
 *  LOG:
 *  LOG: Revision 9.2  2005/05/11 13:46:41  yranade
 *  LOG: Indeterminate Length Fixes. Help Desk ID 742.
 *  LOG:
 *  LOG: Revision 9.1  2005/03/23 12:52:37  cvsadmin
 *  LOG: Begin PR6.5
 *  LOG:
 *  LOG: Revision 8.6  2005/03/21 13:50:36  cvsadmin
 *  LOG: PR6.4.2 Source Propagated to Current
 *  LOG:
 *  LOG: Revision 1.2.2.1.6.1.6.1  2004/12/16 03:03:03  randresol
 *  LOG: Add JAPAN variant implementation
 *  LOG:
 *  LOG: Revision 1.2.2.1.6.1  2004/08/20 11:28:44  yranade
 *  LOG: Port Length Fix.
 *  LOG:
 *  LOG: Revision 1.2.2.1  2003/07/14 09:22:38  yranade
 *  LOG: Length fix for indeterminate form.
 *  LOG:
 *  LOG: Revision 1.2  2003/02/05 12:58:24  yranade
 *  LOG: Proper identation.
 *  LOG:
 *  LOG: Revision 1.1  2003/02/04 07:19:40  yranade
 *  LOG: Manual Tcap Codec.
 *  LOG:
 *
 ****************************************************************************/
#if !defined(TANDEM)

#if defined(CCITT)
#include <itu/tcap.h>
#elif defined(ANSI)
#include <ansi/tcap.h>
#elif defined(PRC)
#include <china/tcap.h>
#elif defined(TTC)
#include <japan/tcap.h>
#endif

#else /* TANDEM */

#if defined(CCITT)
#include <itutcap>
#elif defined(ANSI)
#include <ansitcap>
#elif defined(PRC)
#include <chinatca>
#elif defined(TTC)
#include <japantca>
#endif

#endif /* TANDEM */

/*****************************************************************************
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
 *
 *  Revision History:
 * ---------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * ---------------------------------------------------------------------------
 *
 * sbabu   04-11-2005  HelpDesk ID#742         Indeterminate Length Decode 
 ****************************************************************************/
SS7DLLAPI int
TCAP_GetSub(ITS_OCTET *data, ITS_OCTET *stop)
{
    ITS_UINT tag;
    ITS_UINT len;
    ITS_BOOLEAN isConstructed = ITS_FALSE;
    ITS_OCTET* start;

    start = data;

    if (IS_CONSTRUCTED(*data))
    {
        isConstructed = ITS_TRUE;
    }

    data += TCAP_GetTag(data, &tag, stop);
    if (data >= stop)
    {
        return (stop - start);
    }

    data += TCAP_GetLength(data, &len, stop, isConstructed);
    data += len;

    if (data >= stop)
    {
        return (stop - start);
    }

    return (data - start);
}

/*****************************************************************************
 *  Purpose:
 *      This funtion returns the Tag from data passed.
 *
 *  Input Parameters:
 *     data and stop.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      retTag.
 *
 *  Return Value:
 *      This returns the length of the tag.
 ****************************************************************************/
SS7DLLAPI int
TCAP_GetTag(ITS_OCTET *data, ITS_UINT *retTag, ITS_OCTET *stop)
{
    int len = 1;

    *retTag = 0;
    if ((*data & TAG_MASK) == TAG_MASK) /* long form */
    {
        do
        {
            data++;
            len++;

            *retTag <<= 7;
            *retTag |= *data & 0x7F;
        }
        while ((*data & 0x80) && data < stop);
    }
    else
    {
        /*
         * Note that I don't mask off the context or constructed bits.
         * We want to know them in this code (for equality checks),
         * and if long form tags appear, we don't care about their value.
         */
        *retTag = *data;
    }

    return len;
}

/*****************************************************************************
 *  Purpose:
 *      This function returns the length.
 *
 *  Input Parameters:
 *      data,stop,isConstructed.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      retLen.
 *
 *  Return Value:
 *      This returns the length of the Length Tag.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  20-05-2005  ID::R0170 to R0210    XUDT/XUDTS Implementation
 *
 ****************************************************************************/
SS7DLLAPI int
TCAP_GetLength(ITS_OCTET *data, ITS_UINT *retLen,
               ITS_OCTET *stop, ITS_BOOLEAN isConstructed)
{
    int len;
    int rlen = 1;
    ITS_OCTET *start;

    len = *data;
    if (len > EXT_LEN_FLAG) /* long form */
    {
        int tlen = len & ~EXT_LEN_FLAG;

        rlen += tlen;
        len = 0;
        if (tlen > 4)
        {
            return 0;
        }
        data++;
        while (tlen > 0)
        {
            len <<= 8;
            len |= *data;
            tlen--;
            data++;
        }

        *retLen = len;
    }
    else if (len < EXT_LEN_FLAG) /* short form */
    {
        *retLen = len;
    }
    else /* indeterminate */
    {
        data++;

        start = data;

        if (isConstructed)
        {
            while (data[0] != 0 && data[1] != 0 && data < stop)
            {
                data += TCAP_GetSub(data, stop);
            }
        }
        else
        {
            while (data[0] != 0 && data[1] != 0 && data < stop)
            {
                data++;
            }
        }

        if (data[0] == 0 && data[1] == 0)
        {
            data += 2;
        }
        else
        {
            data = stop;
        }

        *retLen = data - start;
    }

    return rlen;
}

/*****************************************************************************
 *  Purpose:
 *      Sets the data in the right form based on the len and the flag.
 *
 *  Input Parameters:
 *      The data to set. The len and a flag to set.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The length of the length value set
 ****************************************************************************/
SS7DLLAPI int
TCAP_SetLength(ITS_OCTET *data, ITS_UINT len, ITS_BOOLEAN toSet)
{
    int i = 0;
    int rlen = 1;

    if (len >= EXT_LEN_FLAG) /* long form */
    {
        while (len >> (8*i) > 0)
        {
            i++;
        }
        rlen = i + 1;

        if (toSet && data != NULL)
        {
            *data = (EXT_LEN_FLAG | i);

            while (i > 0)
            {
                data++;
                *data = (len >> (8*(i-1))) & 0xFFU;
                i--;
            }
        }
    }
    else if (len < EXT_LEN_FLAG) /* short and indeterminate form */
    {
        if (toSet && data != NULL)
        {
           *data = len;
        }
    }

    return rlen;
}

/*****************************************************************************
 *  Purpose:
 *      This function returns the tid and tidLen from the buf
 *
 *  Input Parameters:
 *      buf
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      tid, tidLen.
 *
 *  Return Value:
 *      ITS_NO or ITS_YES
 ****************************************************************************/
SS7DLLAPI ITS_BOOLEAN
TCAP_GetTID(ITS_OCTET** buf, ITS_UINT *tid, ITS_UINT *tidLen)
{
    ITS_BOOLEAN firstTime = ITS_TRUE;
    ITS_OCTET *data = *buf;
    ITS_UINT len = *data;

    *tid = 0;
    data += TCAP_GetLength(data, &len, data + 7, ITS_FALSE);

    if (data == *buf || data == (data + 7))
    {
        /* TCAP_ERROR(("TCAP_GetTID: Error parsing length\n")); */

        return (ITS_NO);
    }

    *tidLen = len;

    if (len > 4)
    {
        /* TCAP_ERROR(("TCAP_GetTID: TID too large.\n")); */

        return (ITS_NO);
    }
    if (len == 0)
    {
        /* TCAP_ERROR(("TCAP_GetTID: TID too small.\n")); */

        return (ITS_NO);
    }

    /* backup for the ++ that happens in the while loop */
    data--;

    /* get TID2 */
    while (len > 0)
    {
        *tid <<= 8;
        data++;
        if (firstTime)
        {
            /* sign extend first byte */
            *tid |= (char)*data;
            firstTime = ITS_FALSE;
        }
        else
        {
            *tid |= *data;
        }len--;
    }

    *buf = data + 1;

    return (ITS_YES);
}
