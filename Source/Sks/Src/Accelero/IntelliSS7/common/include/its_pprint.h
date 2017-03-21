/********************************-*-C-*-************************************
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.1  2006/02/23 06:30:44  sjaddu
 * LOG: making va_arg list compatable to mvlppc.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.5  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.4.2.1  2004/09/21 05:37:11  mmanikandan
 * LOG: Propagating PPrint from current.
 * LOG:
 * LOG: Revision 1.4  2003/10/01 14:36:56  mmiers
 * LOG: Add types for SS7, add binary printer
 * LOG:
 * LOG: Revision 1.3  2003/03/05 23:24:40  mmiers
 * LOG: Add user data field, vprint analogue
 * LOG:
 * LOG: Revision 1.2  2003/03/03 21:58:12  mmiers
 * LOG: Add extensible printf() for pretty printing.
 * LOG:
 * LOG: Revision 1.1  2003/02/28 22:55:44  mmiers
 * LOG: Add printer, prep for pretty print of SS7
 * LOG:
 *
 ****************************************************************************/

#if !defined(ITS_PPRINT_H)
#define ITS_PPRINT_H

#include <stdarg.h>

#include <its.h>
#include <its_ring_buf.h>

#ident "$Id: its_pprint.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * printing flags
 */
#define FLAG_SIGN           0x0001  /* put plus or minus in front */
#define FLAG_SIGN_SPACE     0x0002  /* put space or minus in front */
#define FLAG_LEFT           0x0004  /* left justify */
#define FLAG_LEAD_ZERO      0x0008  /* pad with leading zeros */
#define FLAG_LONG           0x0010  /* long value given */
#define FLAG_SHORT          0x0020  /* short value given */
#define FLAG_SIGNED         0x0040  /* signed data given */
#define FLAG_ALTERNATE      0x0080  /* alternate form requested */
#define FLAG_NEGATIVE       0x0100  /* value is negative */
#define FLAG_FORCE_OCTAL    0x0200  /* force leading '0' for octals */
#define FLAG_LONG_DOUBLE    0x0400  /* long double value given */
#define FLAG_OUTPUT_DONE    0x0800  /* extension needs auto output */
#define FLAG_FAMILY_ANSI    0x1000  /* output extension type is ANSI */
#define FLAG_FAMILY_ITU     0x2000  /* output extension type is ITU */
#define FLAG_FAMILY_PRC     0x4000  /* output extension type is China */

/*.interface:PPRINT_
 *****************************************************************************
 *  Interface:
 *      PPRINT_*
 *
 *  Purpose:
 *      Extensible facility for printing to buffers
 *
 *  Usage:
 *
 *****************************************************************************/

typedef char * (*PPrint_Proc)(RINGBUF_Manager *ring,
                              char type, va_list alist,
                              char *text, int textLen,
                              ITS_USHORT *flags,
                              char *prefix, int *prefixLen,
                              int *fieldWidth, int *precision);

/*
 * API
 */
ITSDLLAPI int   PPrint(RINGBUF_Manager *obj, const char *format, ...);
ITSDLLAPI int   PPrintN(RINGBUF_Manager *obj, ITS_UINT maxSize,
                        const char *format, ...);
ITSDLLAPI int   PPrintV(RINGBUF_Manager *obj,
                        const char *format, va_list alist);
ITSDLLAPI int   PPrintNV(RINGBUF_Manager *obj, ITS_UINT maxSize,
                         const char *format, va_list alist);

/*
 * Extender
 */
ITSDLLAPI int   PPrint_AddProc(char type, PPrint_Proc formatter);

/*
 * extension types already defined
 */
#define PPRINT_TYPE_MTP2_LAYER  'D' /* 'D'ata link      */
#define PPRINT_TYPE_MTP3_LAYER  'N' /* 'N'etwork layer  */
#define PPRINT_TYPE_SNMM_LAYER  'M' /* 'M'anagement     */
#define PPRINT_TYPE_SLTM_LAYER  'L' /* 'L'ink test      */
#define PPRINT_TYPE_SCCP_LAYER  'S' /* 'S'CCP           */
#define PPRINT_TYPE_ISUP_LAYER  'I' /* 'I'SUP           */
#define PPRINT_TYPE_TCAP_LAYER  'T' /* 'T'CAP           */

/*
 * output a simple type (string, int, or char) with flags
 * This is intended to do printf() style output, after the type has
 * been written into the format buffer.  It is affected by the following
 * flags (or lack thereof, as the case may be).
 *          FLAG_LEFT
 *          FLAG_SIGNED
 *          FLAG_NEGATIVE
 *          FLAG_SIGN_SPACE
 *          FLAG_LEAD_ZERO
 */
ITSDLLAPI int   PPrint_SimpleOutput(RINGBUF_Manager *ring,
                                    char *output, int outputLen,
                                    ITS_USHORT flags,
                                    char *prefix, int prefixLen,
                                    int fieldWidth, int precision);

/*
 * Sample extension (we never use floats, so we leave the printf()
 * float output types unallocated).
 */
ITSDLLAPI char *PPrint_Float(RINGBUF_Manager *ring, char type, va_list *alist,
                             char *text, int textLen, ITS_USHORT *flags,
                             char *prefix, int *prefixLen,
                             int *fieldWidth, int *precision);

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

#if defined(ITS_NAMESPACE)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* ITS_PPRINT_H */
