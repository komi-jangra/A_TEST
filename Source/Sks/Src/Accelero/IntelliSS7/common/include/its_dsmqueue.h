/****************************************************************************
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:45  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/09 00:52:53  sjaddu
 * LOG: Type added for ISUP_CKGP_LIST.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/04/29 21:33:04  randresol
 * LOG: fix assignment bug in DSMQUEUE_NEXT
 * LOG:
 * LOG: Revision 1.2  2002/03/28 01:47:12  mmiers
 * LOG: Warning removal (dsmqueue on linux).
 * LOG: License optimizations when capability checking is not desired.
 * LOG:
 * LOG: Revision 1.1  2002/03/26 18:00:09  randresol
 * LOG: Add interface to create and manipulate queues in DSM.
 * LOG:
 * LOG: 
 *
 ****************************************************************************/

#ifndef ITS_DSMQUEUE_H
#define ITS_DSMQUEUE_H

#include <its_types.h>

#define ENT_TYPE_COCBBUF            0x0001
#define ENT_TYPE_RTRVBUF            0x0002
#define ENT_TYPE_CRBUF              0x0003
#define ENT_TYPE_LINKSET_ROUTES     0x0004
#define ENT_TYPE_ISUP_CKGP_LIST     0x0005


#define SIF_MAX_SIZE 272

#define QUEUE_INITIAL_SIZE  8
#define QUEUE_GROWTH_FACTOR 2

typedef struct
{
    ITS_UINT type;
    ITS_UINT value;
    ITS_UINT maxQueueSize;
}
DSMQUEUE_EntryKey;

typedef struct
{
    ITS_USHORT len;
    ITS_USHORT src;
    ITS_OCTET  data[SIF_MAX_SIZE];
} 
DSMQUEUE_Entry;

typedef struct
{
    DSMQUEUE_EntryKey key; 
    ITS_UINT numEntries;
    ITS_INT firstEntry;
    ITS_INT lastEntry;
    DSMQUEUE_Entry *entries; 
}
DSM_Queue;

typedef struct
{
    ITS_EVENT data;
}
QUEUE_Entry;

#define DSMQUEUE_KEY_SIZE (sizeof(DSMQUEUE_EntryKey) - sizeof(ITS_UINT))

#define DSMQUEUE_HEAD(q) \
    (&((DSM_Queue *)(q))->entries[q->firstEntry])
#define DSMQUEUE_TAIL(q) \
    (&((DSM_Queue *)(q))->entries[q->lastEntry])
#define DSMQUEUE_COUNT(q) \
    (((DSM_Queue *)(q))->numEntries)
#define DSMQUEUE_MAXSIZE(q) \
    (((DSM_Queue *)(q))->key.maxQueueSize)

#define DSMQUEUE_NEXT(q, e) \
    ( e == &q->entries[DSMQUEUE_MAXSIZE(q) - 1] ? \
      q->entries                                : \
      (e+1)                                       )


typedef int    (*DSMQUEUE_InsertFunc)(QUEUE_Entry *prev, 
                                      QUEUE_Entry *next,
                                      QUEUE_Entry *item);


ITSDLLAPI DSM_Queue *
DSMQUEUE_Create(ITS_UINT keyType, ITS_UINT keyValue);

ITSDLLAPI int
DSMQUEUE_Enqueue(DSM_Queue *queue, ITS_EVENT ev);

ITSDLLAPI int
DSMQUEUE_Dequeue(DSM_Queue *queue, ITS_EVENT **data);


ITSDLLAPI int
DSMQUEUE_Delete(DSM_Queue *queue);

ITSDLLAPI int
DSMQUEUE_Insert(DSM_Queue *queue, DSMQUEUE_InsertFunc func, ITS_EVENT ev);


ITSDLLAPI int
DSMQUEUE_Unlink(DSM_Queue *queue, DSMQUEUE_Entry *ent);


ITSDLLAPI DSM_Queue *
DSMQUEUE_FindQueue(ITS_UINT keyType, ITS_UINT keyValue);



#endif /* ITS_DSMQUEUE_H */

