/*****************************************************************************
 *                                                                           *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *             Manufactured in the United States of America.                 *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                           *
 *   This product and related documentation is protected by copyright and    *
 *   distributed under licenses restricting its use, copying, distribution   *
 *   and decompilation.  No part of this product or related documentation    *
 *   may be reproduced in any form by any means without prior written        *
 *   authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                           *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *   government is subject to restrictions as set forth in subparagraph      *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 * CONTRACT: INTERNAL                                                        *
 *                                                                           *
 *****************************************************************************
 *
 *  ID: $Id: dsm_nsk_impl.h,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:23  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:11  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:51:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1  2003/01/30 17:15:19  omayor
 * LOG: Fisrt shot at DSM on Tandem using MBE.
 * LOG:
 *
 *****************************************************************************/
#if !defined(_DSM_NSK_IMPL_H_)
#define _DSM_NSK_IMPL_H_

#include <its.h>
#include <its_dsm.h>


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
 ** DSM (NSK) Data class.
 **
 */

/*
 * DSM (NSK) Data class definition.
 */

#define DSM_NSK_BAD_FILE_NUM       -1
#define DSM_NSK_MBE_REC_EXIST      10

#define DSM_NSK_FILE_NAME_STRING     "fileName"
#define DSM_NSK_MAX_ROW_SIZE_STRING  "maxRecordSize"
#define DSM_NSK_TABLE_ID_STRING      "dsmTableId"
#define DSM_NSK_END_OF_FILE_STRING   "endOfFile"

#define DSM_NSK_MAX_NUM_POOL_BUF      10

#define DSM_NSK_MAX_NUM_MBE_FILES    100
#define DSM_NSK_MAX_MBE_FILE_LEN      24

#define DSM_NSK_MBE_KPOS_APPROX        0
#define DSM_NSK_MBE_KPOS_GEN           1
#define DSM_NSK_MBE_KPOS_EXACT         2

typedef struct
{
    ITS_UINT rowLength;
    ITS_OCTET *data;
}
DSM_TableRow;


typedef struct
{
    void* reserved1;     /* I guess this is for future use ? */
    void* reserved2;     /* I guess this is for future use ? */
}
DSM_DataClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    DSM_DataClassPart   dataClass;

}
DSM_DataClassRec, *DSM_DataClass;

#define DSM_DATA_CLASS_NAME  "DSM Data Class - NSK"

/*
 * Definitions used by DSM (NSK) Data object.
 */ 

typedef struct _dataBuffer
{
    struct _dataBuffer*   next;
    struct _dataBuffer*   prev;
    void*          data;
}
dataBuffer;

typedef struct
{
    dataBuffer* fList;
    dataBuffer* bList;
}
DSM_BufferPool;

typedef struct
{
    short           fileNum;
    short           maxRowSize;
    char*           fileName;
    DSM_BufferPool  memPool;
}
DSM_TableInfo;

typedef struct
{
    DSM_TableInfo *files;
    ITS_UINT      numFiles;
}
DSM_MBEFileInfo;

/*
 * Table.
 */

typedef struct
{
    DSM_TableInfo* tableInfo;  /* MBE file number from MBE_FILE_OPEN_ */
    ITS_SHORT      keySpec;    /* alternate key, 0 if primary */
} 
DSM_Table;


typedef DSM_Table* DSM_Tables;


/*
 * DSM (NSK) Data object definition.
 */

typedef struct
{
    ITS_UINT         numTables;
    DSM_Tables       tables;
    DSM_MBEFileInfo  files;
    DSM_CoreObject*  coreObject; /* Access within destroy instance only. */
    DSM_InstObject*  instObject; /* Access within destroy instance only. */
}
DSM_DataObjectPart;

typedef struct
{
    ITS_CoreObjectPart  coreObject;
    DSM_DataObjectPart  dataObject;
}
DSM_DataObject;


#define DSM_DATA_MBE_FILE_INFO(x) \
    (((DSM_DataObject*)(x))->dataObject.files)

#define DSM_DATA_NUM_TABLES(x) \
    (((DSM_DataObject*)(x))->dataObject.numTables)

#define DSM_DATA_TABLES(x) \
    (((DSM_DataObject*)(x))->dataObject.tables)

#define DSM_DATA_CORE_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.coreObject)

#define DSM_DATA_INST_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.instObject)


#if defined(__cplusplus)
}
#endif

#endif /* _DSM_NSK_IMPL_H_ */


