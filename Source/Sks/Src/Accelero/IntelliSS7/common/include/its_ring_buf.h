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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:37  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:50  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:50:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.10.1  2004/09/21 05:36:38  mmanikandan
 * LOG: Propagating PPrint from current.
 * LOG:
 * LOG: Revision 8.4  2003/10/29 14:00:24  mmiers
 * LOG: Fixes for building on current versions of HPUX
 * LOG:
 * LOG: Revision 8.3  2003/03/06 00:00:10  mmiers
 * LOG: More ring work.  Count newlines as record separators.
 * LOG:
 * LOG: Revision 8.2  2003/03/05 23:24:40  mmiers
 * LOG: Add user data field, vprint analogue
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:43:42  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.4  2003/01/29 17:20:26  mmiers
 * LOG: Put the ring buffer in the right place, test it out.
 * LOG:
 * LOG: Revision 7.3  2003/01/28 23:25:44  mmiers
 * LOG: Finish ring buffer API.
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.1  2001/11/15 02:02:57  mmiers
 * LOG: Note some things to do.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>
#include <its_work_item.h>

#ident "$Id: its_ring_buf.h,v 1.1.1.1 2007-10-08 11:11:32 bsccs2 Exp $"

#if !defined(_ITS_RING_BUF_H_)
#define _ITS_RING_BUF_H_

/*
 * minimum size for a ring buffer
 */
#define RING_BUF_MIN_SIZE   128

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * forward
 */
typedef struct _RINGBUF_Manager *RINGBUF_ManagerPtr;

/*
 * method signatures
 */
typedef int (*RINGBUF_FlushProc)(RINGBUF_ManagerPtr);
typedef int (*RINGBUF_AppendProc)(RINGBUF_ManagerPtr, char *, ITS_UINT);
typedef int (*RINGBUF_WriteProc)(RINGBUF_ManagerPtr, char *, ITS_UINT);

/*
 * instance data
 */
typedef struct
{
    char                *base;
    char                *top;
    char                *curBase;
    char                *curTop;
    ITS_UINT            hiWater;
    ITS_UINT            size;
    RINGBUF_WriteProc   write;
    void                *userData;
    ITS_UINT            recCount;
}
RINGBUF_ObjectPart;

typedef struct _RINGBUF_Manager
{
    ITS_CoreObjectPart  core;
    RINGBUF_ObjectPart  ringbuf;
}
RINGBUF_Manager;

#define RINGBUF_BASE(x) \
    ((x)->ringbuf.base)

#define RINGBUF_TOP(x) \
    ((x)->ringbuf.top)

#define RINGBUF_CUR_BASE(x) \
    ((x)->ringbuf.curBase)

#define RINGBUF_CUR_TOP(x) \
    ((x)->ringbuf.curTop)

#define RINGBUF_HI_WATER(x) \
    ((x)->ringbuf.hiWater)

#define RINGBUF_SIZE(x) \
    ((x)->ringbuf.size)

#define RINGBUF_WRITE(x) \
    ((x)->ringbuf.write)

#define RINGBUF_USER_DATA(x) \
    ((x)->ringbuf.userData)

#define RINGBUF_REC_COUNT(x) \
    ((x)->ringbuf.recCount)

/*
 * class record
 */
typedef struct
{
    RINGBUF_FlushProc   flush;
    RINGBUF_AppendProc  append;
    RINGBUF_WriteProc   write;
}
RINGBUF_ClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    RINGBUF_ClassPart   ringbufClass;
}
RINGBUF_ClassRec;

#define RINGBUF_CLASS_APPEND(x) \
    (((RINGBUF_ClassRec *)(x))->ringbufClass.append)

#define RINGBUF_CLASS_FLUSH(x) \
    (((RINGBUF_ClassRec *)(x))->ringbufClass.flush)

#define RINGBUF_CLASS_WRITE(x) \
    (((RINGBUF_ClassRec *)(x))->ringbufClass.write)

#define RINGBUF_CLASS_NAME  "RING_BUFFER CLASS"

ITSDLLAPI extern RINGBUF_ClassRec  itsRINGBUF_ClassRec;
ITSDLLAPI extern ITS_Class         itsRINGBUF_Class;

/*.interface:RINGBUF_
 *****************************************************************************
 *  Interface:
 *      RINGBUF_*
 *
 *  Purpose:
 *
 *  Usage:
 *
 *****************************************************************************/
ITSDLLAPI RINGBUF_Manager * RINGBUF_InitManager(ITS_UINT size,
                                                ITS_UINT hiWater,
                                                RINGBUF_WriteProc,
                                                void *userData);
ITSDLLAPI void              RINGBUF_FreeManager(RINGBUF_Manager *rb);

ITSDLLAPI int               RINGBUF_Append(RINGBUF_Manager *rb,
                                           char *text, ITS_UINT size);
ITSDLLAPI int               RINGBUF_Flush(RINGBUF_Manager *rb);

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_RING_BUF_H_ */
