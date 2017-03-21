/******************************************************************************
 *                                                                            *
 *  Copyright 2001 - 2002 IntelliNet Technologies, Inc. All Rights Reserved.  *
 *             Manufactured in the United States of America.                  *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.         *
 *                                                                            *
 *   This product and related documentation is protected by copyright and     *
 *   distributed under licenses restricting its use, copying, distribution    *
 *   and decompilation.  No part of this product or related documentation     *
 *   may be reproduced in any form by any means without prior written         *
 *   authorization of IntelliNet Technologies and its licensors, if any.      *
 *                                                                            *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        *
 *   government is subject to restrictions as set forth in subparagraph       *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software         *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                          *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:24  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:13  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:24  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3  2003/01/30 21:27:57  mmiers
 * LOG: Start adding table type.
 * LOG:
 * LOG: Revision 7.2  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.1  2002/04/11 20:40:48  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

#if !defined(_DSM_STUB_IMPL_H_)
#define _DSM_STUB_IMPL_H_

#include <its.h>
#include <its_dsm.h>
#include <its_hash.h>
#include <its_rb.h>
#include <its_splay.h>

#ident "$Id: dsm_stub_impl.h,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*****************************************************************************
 *                                                                           *
 * Non-public header (implementation).                                       *
 *                                                                           *
 *****************************************************************************/
    
    
/******************************************************************************
 ******************************************************************************
 **
 ** DSM (STUB) Data class.
 **
 */

/*
 * DSM (STUB) Data class definition.
 */

typedef struct
{
    void* reserved1;
    void* reserved2;
}
DSM_DataClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    DSM_DataClassPart   dataClass;

}
DSM_DataClassRec, *DSM_DataClass;

#define DSM_DATA_CLASS_NAME  "DSM Data Class - STUB"

/*
 * Definitions used by DSM (STUB) Data object.
 */ 

typedef struct
{
    DSM_TableType       type;
    union
    {
        HASH_Table      hash;
        REDBLACK_Tree   tree;
        SPLAY_Tree      splay;
    }
    table;
} 
DSM_Table;

typedef DSM_Table* DSM_Tables;

/*
 * DSM info (lock...).
 */ 

typedef struct
{
    ITS_MUTEX lock;
}
DSM_DsmInfo;

/*
 * Table info (lock, count of entries...).
 */

typedef struct
{
    ITS_MUTEX   lock;
    ITS_UINT    entries;
}
DSM_TableInfo;

typedef DSM_TableInfo* DSM_TablesInfo;

/*
 * DSM (STUB) Data object definition.
 */

typedef struct
{
    DSM_DsmInfo     dsmInfo;
    DSM_Tables      tables;
    DSM_TablesInfo  tablesInfo;
    DSM_CoreObject* coreObject; /* Access within destroy instance only. */
    DSM_InstObject* instObject; /* Access within destroy instance only. */
}
DSM_DataObjectPart;

typedef struct
{
    ITS_CoreObjectPart  coreObject;
    DSM_DataObjectPart  dataObject;
}
DSM_DataObject;


#define DSM_DATA_DSM_INFO(x) \
    (((DSM_DataObject*)(x))->dataObject.dsmInfo)

#define DSM_DATA_TABLES(x) \
    (((DSM_DataObject*)(x))->dataObject.tables)

#define DSM_DATA_TABLES_INFO(x) \
    (((DSM_DataObject*)(x))->dataObject.tablesInfo)

#define DSM_DATA_CORE_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.coreObject)

#define DSM_DATA_INST_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.instObject)


#if defined(__cplusplus)
}
#endif

#endif /* _DSM_STUB_IMPL_H_ */


