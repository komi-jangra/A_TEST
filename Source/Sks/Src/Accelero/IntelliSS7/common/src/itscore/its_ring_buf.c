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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1  2004/09/21 05:39:41  mmanikandan
 * LOG: Propagating PPrint from current.
 * LOG:
 * LOG: Revision 8.6  2003/03/06 00:00:10  mmiers
 * LOG: More ring work.  Count newlines as record separators.
 * LOG:
 * LOG: Revision 8.5  2003/03/05 23:25:16  mmiers
 * LOG: Add vprint analogue, addition ringbuf fields
 * LOG:
 * LOG: Revision 8.4  2003/02/28 22:55:44  mmiers
 * LOG: Add printer, prep for pretty print of SS7
 * LOG:
 * LOG: Revision 8.3  2003/02/25 19:32:51  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 8.2  2003/02/19 16:52:11  mmiers
 * LOG: Inheritance bug fixes.  Move class method invocation out of
 * LOG: hash constructor.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:43:57  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.1  2003/01/29 17:20:26  mmiers
 * LOG: Put the ring buffer in the right place, test it out.
 * LOG:
 * LOG: Revision 7.3  2003/01/28 23:25:44  mmiers
 * LOG: Finish ring buffer API.
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:02  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/11/15 02:02:57  mmiers
 * LOG: Note some things to do.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#ident "$Id: its_ring_buf.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

#include <its.h>
#include <its_ring_buf.h>

/*
 * assumption:
 * Post-flush, CUR_BASE == CUR_TOP
 * CUR_TOP points at first free.
 * CUR_BASE points at base of current ring.
 */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
Write(RINGBUF_Manager *rb, char *text, ITS_UINT len)
{
    return RINGBUF_WRITE(rb)(rb, text, len);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
Flush(RINGBUF_Manager *rb)
{
    int ret, ret2;

    /* wrapped state or not. */
    if (RINGBUF_CUR_BASE(rb) > RINGBUF_CUR_TOP(rb))
    {
        ret = RINGBUF_CLASS_WRITE(ITS_OBJ_CLASS(rb))(rb, RINGBUF_CUR_BASE(rb),
                                                     RINGBUF_TOP(rb) -
                                                        RINGBUF_CUR_BASE(rb));

        if (ret > 0)
        {
            ret2= RINGBUF_CLASS_WRITE(ITS_OBJ_CLASS(rb))(rb, RINGBUF_BASE(rb),
                                                         RINGBUF_CUR_TOP(rb) -
                                                            RINGBUF_BASE(rb));

            if (ret2 > 0)
            {
                ret += ret2;
            }
            else
            {
                ret = ret2;
            }
        }
    }
    else if (RINGBUF_CUR_BASE(rb) < RINGBUF_CUR_TOP(rb))
    {
        ret = RINGBUF_CLASS_WRITE(ITS_OBJ_CLASS(rb))(rb, RINGBUF_CUR_BASE(rb),
                                                     RINGBUF_CUR_TOP(rb) -
                                                        RINGBUF_CUR_BASE(rb));
    }
    else
    {
        ret = 0;
    }

    RINGBUF_CUR_BASE(rb) = RINGBUF_CUR_TOP(rb);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
Append(RINGBUF_Manager *rb, char *text, ITS_UINT len)
{
    ITS_UINT curSize;
    ITS_UINT hiPart, lowPart;
    int ret;

    /* see if the string is just too big */
    if (len >= RINGBUF_SIZE(rb))
    {
        ret = RINGBUF_CLASS_FLUSH(ITS_OBJ_CLASS(rb))(rb);

        /*
         * if the flush fails, there's not much we can do about it.
         * But bail out in any case, if it failed there's no point
         * in proceeding.
         */

        if (ret < 0)
        {
            return (ret);
        }

        ret = RINGBUF_CLASS_WRITE(ITS_OBJ_CLASS(rb))(rb, text, len);

        return (ret);
    }

    /* current size? */
    if (RINGBUF_CUR_BASE(rb) > RINGBUF_CUR_TOP(rb))
    {
        curSize = (RINGBUF_CUR_TOP(rb) - RINGBUF_BASE(rb)) +
                    (RINGBUF_TOP(rb) - RINGBUF_CUR_BASE(rb));
    }
    else
    {
        curSize = RINGBUF_CUR_TOP(rb) - RINGBUF_CUR_BASE(rb);
    }

    /* see if the string would cause overflow */
    if (curSize + len >= RINGBUF_SIZE(rb))
    {
        ret = RINGBUF_CLASS_FLUSH(ITS_OBJ_CLASS(rb))(rb);

        /*
         * if the flush fails, there's not much we can do about it.
         * But bail out in any case, if it failed there's no point
         * in proceeding.
         */

        if (ret < 0)
        {
            return (ret);
        }
    }

    /* we've wrapped or not: wrapped means the top is less than base */
    if (RINGBUF_CUR_TOP(rb) >= RINGBUF_CUR_BASE(rb))
    {
        /* wraparound? */
        if (RINGBUF_CUR_TOP(rb) + len >= RINGBUF_TOP(rb))
        {
            hiPart = RINGBUF_TOP(rb) - RINGBUF_CUR_TOP(rb);
            lowPart = len - hiPart;

            if (hiPart)
            {
                memcpy(RINGBUF_CUR_TOP(rb), text, hiPart);
            }

            if (lowPart)
            {
                memcpy(RINGBUF_BASE(rb), text + hiPart, lowPart);
            }

            RINGBUF_CUR_TOP(rb) = RINGBUF_BASE(rb) + lowPart;
        }
        /* not wrapped */
        else
        {
            if (len)
            {
                memcpy(RINGBUF_CUR_TOP(rb), text, len);
            }

            RINGBUF_CUR_TOP(rb) += len;
        }
    }
    /*
     * the other case is cur top < cur base.  We don't have to worry
     * about overunning cur base, as that would be an overflow case
     * and is already handled
     */
    else
    {
        if (len)
        {
            memcpy(RINGBUF_CUR_TOP(rb), text, len);
        }

        RINGBUF_CUR_TOP(rb) += len;
    }

    /* see if the current size is over high water */
    if (curSize >= RINGBUF_HI_WATER(rb))
    {
        ret = RINGBUF_CLASS_FLUSH(ITS_OBJ_CLASS(rb))(rb);

        /*
         * if the flush fails, there's not much we can do about it.
         * But bail out in any case, if it failed there's no point
         * in proceeding (and we need to let the caller no we're toast.
         */

        return (ret);
    }

    return ((int)len);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
Initialize(ITS_Object obj, va_list alist)
{
    RINGBUF_Manager *rb = (RINGBUF_Manager *)obj;
    ITS_UINT size;
    ITS_UINT hiWater;
    RINGBUF_WriteProc write;
    void *userData;

    size = va_arg(alist, ITS_UINT);
    if (size < RING_BUF_MIN_SIZE)
    {
        size = RING_BUF_MIN_SIZE;
    }

    hiWater = va_arg(alist, ITS_UINT);
    write = va_arg(alist, RINGBUF_WriteProc);
    userData = va_arg(alist, void *);

    RINGBUF_SIZE(rb) = size;

    RINGBUF_BASE(rb) = malloc(size);
    if (RINGBUF_BASE(rb) == NULL)
    {
        return (ITS_ENOMEM);
    }

    RINGBUF_TOP(rb) = RINGBUF_BASE(rb) + size;

    RINGBUF_CUR_BASE(rb) = RINGBUF_CUR_TOP(rb) = RINGBUF_BASE(rb);

    RINGBUF_HI_WATER(rb) = (size * hiWater) / 100;  /* hiWater is expressed
                                                     * as a percentage */

    RINGBUF_WRITE(rb) = write;
    RINGBUF_USER_DATA(rb) = userData;
    RINGBUF_REC_COUNT(rb) = 0;
    
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
Terminate(ITS_Object obj)
{
    RINGBUF_Manager *rb = (RINGBUF_Manager *)obj;

    free(RINGBUF_BASE(rb));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassPartInit(ITS_Class objClass)
{
    ITS_Class superClass = ITS_CLASS_SUPERCLASS(objClass);

    if (RINGBUF_CLASS_WRITE(objClass) == NULL)
    {
        RINGBUF_CLASS_WRITE(objClass) = RINGBUF_CLASS_WRITE(superClass);
    }

    if (RINGBUF_CLASS_FLUSH(objClass) == NULL)
    {
        RINGBUF_CLASS_FLUSH(objClass) = RINGBUF_CLASS_FLUSH(superClass);
    }

    if (RINGBUF_CLASS_APPEND(objClass) == NULL)
    {
        RINGBUF_CLASS_APPEND(objClass) = RINGBUF_CLASS_APPEND(superClass);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassPartDest(ITS_Class objClass)
{
}

/*
 * the class record
 */
ITSDLLAPI RINGBUF_ClassRec itsRINGBUF_ClassRec =
{
    /* core part */
    {
        (ITS_Class)&itsCORE_ClassRec,   /* CORE is superclass */
        sizeof(RINGBUF_Manager),        /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        RINGBUF_CLASS_NAME,             /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ClassPartInit,                  /* class part init */
        ClassPartDest,                  /* class part destroy */
        Initialize,                     /* instance create */
        Terminate,                      /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* ringbuf part */
    {
        Flush,
        Append,
        Write
    }
};

ITSDLLAPI ITS_Class itsRINGBUF_Class = (ITS_Class)&itsRINGBUF_ClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI RINGBUF_Manager *
RINGBUF_InitManager(ITS_UINT size, ITS_UINT hiWater,
                    RINGBUF_WriteProc write, void *userData)
{
    return (RINGBUF_Manager *)ITS_ConstructObject(itsRINGBUF_Class,
                                                  size, hiWater,
                                                  write, userData);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
RINGBUF_FreeManager(RINGBUF_Manager *rb)
{
    RINGBUF_CLASS_FLUSH(ITS_OBJ_CLASS(rb))(rb);

    ITS_DestructObject((ITS_Object)rb);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RINGBUF_Append(RINGBUF_Manager *rb, char *text, ITS_UINT size)
{
    return RINGBUF_CLASS_APPEND(ITS_OBJ_CLASS(rb))(rb, text, size);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RINGBUF_Flush(RINGBUF_Manager *rb)
{
    return RINGBUF_CLASS_FLUSH(ITS_OBJ_CLASS(rb))(rb);
}
