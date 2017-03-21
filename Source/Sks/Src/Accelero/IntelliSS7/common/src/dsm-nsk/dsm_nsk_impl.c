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
 *  ID: $Id: dsm_nsk_impl.c,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $
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
 * LOG: Revision 8.9  2005/03/21 13:51:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.1  2003/01/30 17:15:19  omayor
 * LOG: Fisrt shot at DSM on Tandem using MBE.
 * LOG:
 *
 *****************************************************************************/

 
#include <dsm_nsk_impl.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_timers.h>

#include "USRLIBH"


/******************************************************************************
 ******************************************************************************
 **
 ** Simple buffer pool for temporary memory allocation
 **
 */


void
DSM_InitMemPool(DSM_TableInfo *table)
{
    int i = 0;

    if (table == NULL)
    {
        return;   
    }

    table->memPool.fList = table->memPool.bList = NULL;

    for (i = 0; i < DSM_NSK_MAX_NUM_POOL_BUF; i++)
    {
        dataBuffer* node = (dataBuffer*)calloc(1, sizeof(dataBuffer));

        node->data = (ITS_OCTET*)calloc(1, table->maxRowSize);

        node->next = table->memPool.fList;

        node->prev = NULL;

        table->memPool.fList = node;
    }

    return;
}

void
FreeBufferList(dataBuffer *list)
{
    dataBuffer *node = NULL;

    while (list != NULL)
    {
        node = list;
        list = node->next;
        free(node->data);
        free(node);
    }

    return;
}

void
DSM_FreeMemPool(DSM_TableInfo *table)
{
    FreeBufferList(table->memPool.fList);
    FreeBufferList(table->memPool.bList);
}

ITS_OCTET*
DSM_GetDataBuffer(DSM_TableInfo *table)
{
    dataBuffer* node = NULL;

    if (table == NULL)
    {
        ITS_TRACE_ERROR(("TableInfo is NULL \n"));

        return NULL;
    }

#if defined(USE_MEM_POOL)
    if (table->memPool.fList)
    {
        node = table->memPool.fList;

        table->memPool.fList = table->memPool.fList->next;

        node->next = table->memPool.bList;

        if (node->next)
        {
            node->next->prev = node;
        }

        table->memPool.bList = node;

        node->prev = NULL;

        return node->data;

    }
#endif

    return calloc(1, table->maxRowSize);
}



DSM_FreeDataBuffer(DSM_TableInfo *table, ITS_OCTET* data)
{
    dataBuffer* node = NULL;

#if defined(USE_MEM_POOL)
    if (table == NULL)
    {
        ITS_TRACE_ERROR(("TableInfo is NULL \n"));

        return ITS_ENOMEM;
    }

    node = table->memPool.bList;

    while ((node->data != data) && (node->next != NULL))
    {
        node = node->next;
    }

    if (node->data == data)
    {
        if (node->next == NULL)
        {
            if (node->prev == NULL) /* only one entry */
            {
                table->memPool.bList = NULL;
            }

            node->prev->next = NULL; /* last entry */
        }
        else
        {
            node->prev->next = node->next; /* in the middle */
            node->next->prev = node->prev;
        }

        node->next = table->memPool.fList;  /* insert back to free list */
        table->memPool.fList = node;
    }
    else
    {
        free(data);
    }
#else
    free(data);
#endif

    return ITS_SUCCESS;
    
}



/******************************************************************************
 ******************************************************************************
 **
 ** DSM (NSK) Data class.
 **
 */



static int
TablesCreate(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    int ret = ITS_SUCCESS;
    RESFILE_Manager *resdb = NULL;
    char var[1024], val[1024];
    DSM_TableInfo* tableInfo = NULL;
    ITS_UINT numFiles = 0, numTables = 0;
    ITS_BOOLEAN inFile = ITS_FALSE;
    ITS_SHORT fileNumber = 0;

    /* get the tables configuration */
    resdb = DSM_CORE_CONFIG_DB(coreObj);
    if (resdb == NULL)
    {
        return ITS_EIMPLINITFAIL;
    }

    /* allocate array of table records - file number matching */
    DSM_DATA_TABLES(dataObj) =
        calloc(DSM_INST_MAX_NUM_TABLES(instObj), sizeof(DSM_Table));
    if (DSM_DATA_TABLES(dataObj) == NULL)
    {
        ITS_TRACE_ERROR(("TablesCreate failed to allocate memory\n"));

        return ITS_ENOMEM;
    }

    DSM_DATA_MBE_FILE_INFO(dataObj).files =
        calloc(DSM_NSK_MAX_NUM_MBE_FILES, sizeof(DSM_TableInfo));
    if (DSM_DATA_MBE_FILE_INFO(dataObj).files == NULL)
    {
        ITS_TRACE_ERROR(("TablesCreate: failed to create Hashtable\n"));

        /* free memory allocated */

        free(DSM_DATA_TABLES(dataObj));

        return ITS_ENOMEM;
    }

    /* lock resource manager */
    if (RESFILE_Lock(resdb) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TablesCreate: Couldn't lock resource file\n"));

        return (ITS_EBADMUTEX);
    }

    ret = RESFILE_Rewind(resdb, DSM_FAULT_TOLERANCE_STRING);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TableCreate: Could not rewind section !!!\n"));

        THREAD_NORMAL_EXIT;
    }

    /* now traverse the section and populate the DSM table information */
    while (RESFILE_GetKeyName(resdb, DSM_FAULT_TOLERANCE_STRING,
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(resdb, DSM_FAULT_TOLERANCE_STRING,
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        if (strcmp(var, DSM_NSK_FILE_NAME_STRING) == 0)
        {
            if (strcmp(val, "endOfFile") == 0)
            {
                DSM_InitMemPool(tableInfo);

                inFile = ITS_FALSE;
                tableInfo = NULL;
            }
            else
            {
                inFile = ITS_TRUE;

                if (numFiles > DSM_NSK_MAX_NUM_MBE_FILES)
                {
                    ITS_TRACE_WARNING(("TablesCreate: Reach max number of MBE"
                                        " file allowed to open \n"));

                    inFile = ITS_FALSE;

                    break;
                }

                tableInfo = &DSM_DATA_MBE_FILE_INFO(dataObj).files[numFiles];

                /* open the MBE file and get the file number */
                ret = MBE_FILE_OPEN_(val, (short)strlen(val), &fileNumber);
                if ((ret != ITS_SUCCESS) ||
                    (fileNumber != DSM_NSK_BAD_FILE_NUM))
                {
                    inFile = ITS_FALSE;

                    ITS_TRACE_CRITICAL(("TablesCreate: failes to open file %s\n",
                                        val));
                    free(tableInfo);
                }

                tableInfo->fileName = strdup(val);
                tableInfo->fileNum  = fileNumber;

                numFiles++;
            }
        }
        else if (strcmp(var, DSM_NSK_MAX_ROW_SIZE_STRING) == 0)
        {
            if (inFile && tableInfo)
            {
                tableInfo->maxRowSize = (short)RESFILE_ParseNum(val);
            }
            else
            {
                ITS_TRACE_WARNING(("Not In File Config\n"));
            }
        }
        else if (strcmp(var, DSM_NSK_TABLE_ID_STRING) == 0)
        {
            char *tmp = NULL;
            ITS_UINT tableId = 0;

            if (!inFile)
            {
                continue;
            }

            numTables++;
            
            /* to many tables don't want to overide memory */
            if (numTables > DSM_INST_MAX_NUM_TABLES(instObj))
            {
                ITS_TRACE_WARNING(("TablesCreate: Too many tables \n"));

                inFile = ITS_FALSE;

                break;
            }
            
            if ((tmp = strstr(val, ",")) == NULL)
            {
                ITS_TRACE_WARNING(("TablesCreate: Value must be two"
                                   " numbers comma separated\n"));

                numTables--;

                continue;
            }

            *tmp = 0;
            tmp++;

            tableId = RESFILE_ParseNum(val);
            
            DSM_DATA_TABLES(dataObj)[tableId].keySpec =
                                             (short)RESFILE_ParseNum(tmp);
            DSM_DATA_TABLES(dataObj)[tableId].tableInfo = tableInfo;
        } 
        else
        {
            ITS_TRACE_WARNING(("TablesCreate: unexpected string, ignore\n"));
        }
    }

    DSM_DATA_MBE_FILE_INFO(dataObj).numFiles = numFiles;
    DSM_DATA_NUM_TABLES(dataObj) = numTables;

    /* unlock the resource manager */
    ret = RESFILE_Unlock(resdb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("TablesCreate: Couldn't unlock resource file\n"));

        return (ITS_EBADMUTEX);
    }

    return ITS_SUCCESS;
}

static int
TablesDestroy(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    ITS_UINT i;

    for (i = 0; i < DSM_NSK_MAX_NUM_MBE_FILES; i++)
    {
        /* close the MBE file for that process */
        MBE_FILE_CLOSE_((short)DSM_DATA_MBE_FILE_INFO(dataObj).files[i].fileNum);

        DSM_FreeMemPool(&(DSM_DATA_MBE_FILE_INFO(dataObj).files[i]));
    }

    /* free the housekeeping table */
    free(DSM_DATA_TABLES(dataObj));
    free(DSM_DATA_MBE_FILE_INFO(dataObj).files);

    DSM_DATA_NUM_TABLES(dataObj) = 0;
    DSM_DATA_MBE_FILE_INFO(dataObj).numFiles = 0;

    return ITS_SUCCESS;
}





/*
 * DataClassInitialize.
 */
static int
DataClassInitialize(
    ITS_Class objClass)
{
    /* Nothing to do. */
    return ITS_SUCCESS;
}

/*
 * DataClassTerminate.
 */
static void
DataClassTerminate(
    ITS_Class objClass)
{
    /* Nothing to do. */
    return;
}

/*
 * DataCreateInstance.
 */
static int
DataCreateInstance(
    ITS_Object obj, 
    va_list args)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    coreObj     = va_arg(args, DSM_CoreObject*);
    instObj     = va_arg(args, DSM_InstObject*);
    dataObj     = (DSM_DataObject*)obj;

    /* Access within destroy instance only. */
    DSM_DATA_CORE_OBJECT(dataObj) = coreObj;
    DSM_DATA_INST_OBJECT(dataObj) = instObj;

    ret = TablesCreate(coreObj, instObj, dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance: TablesCreate failed: %d\n", ret));
        return ret;
    }

    return ITS_SUCCESS;
}

/*
 * DataDestroyInstance.
 */
static void
DataDestroyInstance(
    ITS_Object obj)
{
    TablesDestroy(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    DSM_DATA_CORE_OBJECT(obj) = NULL;
    DSM_DATA_INST_OBJECT(obj) = NULL;
}

static DSM_DataClassRec itsDSM_DataClassRec =
{
    /* core part */
    {
        NULL,                               /* no super class in DLL    */
        sizeof(DSM_DataObject),             /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_DATA_CLASS_NAME,                /* class name               */
        DataClassInitialize,                /* class init               */
        DataClassTerminate,                 /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        DataCreateInstance,                 /* instance create          */
        DataDestroyInstance,                /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* data part */
    {
        NULL,
        NULL
    }
};

static ITS_Class itsDSM_DataClass = (ITS_Class)&itsDSM_DataClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (NSK) Impl (implementation) class.
 **
 */


static void
CallMembershipChangeCallbacks(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    ITS_USHORT ftGroupId,
    DSM_MembershipChangeType membershipChangeType)
{
    /* nothing to do */
    return;
}

static int 
DSM_ImplDataCreateInstanceImpl(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    ITS_USHORT ftGroupId)
{
    DSM_DataObject* dataObj;
    
    dataObj = (DSM_DataObject*)ITS_ConstructObject(
                                        itsDSM_DataClass,
                                        coreObj,
                                        instObj,
                                        (int)ftGroupId);
    if (dataObj == NULL)
    {
        /* TODO: add trace. */
        return ITS_EIMPLINITFAIL;
    }

    DSM_INST_IMPL_DATA(instObj) = (ITS_Object)dataObj;

    return ITS_SUCCESS;
}

static int 
DSM_ImplDataDestroyInstanceImpl(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    ITS_USHORT  ftGroupId)
{
    DSM_DataObject* dataObj;

    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_DestructObject((ITS_Object)dataObj);

    return ITS_SUCCESS;
}

static int 
DSM_JoinFtGroupImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_TRUE;

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_ALIVE);

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_JOIN);

    return ITS_SUCCESS;
}

static int 
DSM_LeaveFtGroupImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_FALSE;

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_LEAVE);

    CallMembershipChangeCallbacks(
        coreObj,
        instObj,
        ftGroupId,
        DSM_FT_GROUP_MEMBER_DEAD);

    return ITS_SUCCESS;
}

static int 
DSM_SynchronizeDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT msecs)
{
    /* Nothing to do for NSK implementation. */
    return ITS_SUCCESS;
}

static int 
DSM_LockDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    /* 
     * do we need to lock the DSM on TANDEM ? 
     * I don't think so at the moment
     */

    ITS_TRACE_WARNING(("Not actually implemented\n"));
    
    return ITS_SUCCESS;
}

static int 
DSM_UnlockDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    /* 
     * do we need to lock the DSM on TANDEM ? 
     * I don't think so at the moment
     */

    ITS_TRACE_WARNING(("Not actually implemented\n"));

    return ITS_SUCCESS;
}

static int 
DSM_LockTableImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    /*
     * we can use one record in the MBE file as a flag
     */
    ITS_TRACE_WARNING(("Not actually implemented\n"));

    return ITS_SUCCESS;
}

static int 
DSM_UnlockTableImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    /*
     * we can use one record in the MBE file as a flag
     */
    ITS_TRACE_WARNING(("Not actually implemented\n"));

    return ITS_SUCCESS;
}

static void* 
DSM_AllocNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    DSM_TableInfo* tableInfo = NULL;
    ITS_OCTET* allocPtr = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;

    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_AllocNoLock: Unable to retrieve table Info\n"));

        *error = ITS_ENOTFOUND;

        return NULL;
    }

    /* allocate some local memory (memPool or not) */
    allocPtr = DSM_GetDataBuffer(tableInfo);
    if (allocPtr == NULL)
    {
        ITS_TRACE_ERROR(("DSM_AllocNoLock: unable to allocate memory\n"));

        *error = ITS_ENOMEM;

        return NULL;
    }

    /* the PKey is set a the first bytes of the record */
    memcpy(allocPtr, key, klen);

    /*
     * we need to make sure that the row does not already exist. By calling
     * MBE_WRITEX we create the record is not exist or get an error if
     * there is already an entry.
     */
    ret =  MBE_WRITEX(tableInfo->fileNum, (char*)allocPtr, tableInfo->maxRowSize);
    if (ret != ITS_SUCCESS)
    {
        if (ret == DSM_NSK_MBE_REC_EXIST)
        {
            ITS_TRACE_ERROR(("DSM_AllocNoLock: attempt to add "
                             "duplicate row\n"));
        }

        DSM_FreeDataBuffer(tableInfo, allocPtr);

        return NULL;
    } 

    /* we return a ptr to the buffer offset by the key */
    return (void*)(allocPtr + klen);
}

static void*
DSM_FindNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    DSM_TableInfo* tableInfo = NULL;
    ITS_OCTET* allocPtr = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;
    
    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_FindNoLock: Unable find table info \n"));

        *error = ITS_ENOTFOUND;

        return NULL;
    }

    /* allocate a local buffer to copy data in */
    allocPtr = DSM_GetDataBuffer(tableInfo);
    if (allocPtr == NULL)
    {
        ITS_TRACE_ERROR(("DSM_FindNoLock: unable to allocate memory\n"));

        *error = ITS_ENOMEM;

        return NULL;
    }

    /* position within the MBE file */
    ret = MBE_FILE_SETKEY_(tableInfo->fileNum, (char*)key, (short)klen,
                           DSM_DATA_TABLES(dataObj)[tableId].keySpec,
                           DSM_NSK_MBE_KPOS_EXACT);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_FindNoLock: Unable to locate record in "
                         "the MBE database\n"));

        DSM_FreeDataBuffer(tableInfo, allocPtr);

        *error = ITS_ENOTFOUND;

        return NULL;
    }

    /* get the data into the local buffer */
    ret = MBE_READUPDATEX(tableInfo->fileNum, (char*)allocPtr, 
                          tableInfo->maxRowSize);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_FindNoLock: MBE_READUPDATEX failed\n"));

        DSM_FreeDataBuffer(tableInfo, allocPtr);

        *error = ITS_ENOTFOUND;
        
        return NULL;
    }
        
    return (void*)(allocPtr + klen);
}

static int 
DSM_FreeNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,           
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    ITS_OCTET* allocPtr = NULL;
    DSM_TableInfo* tableInfo = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;

    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_FreeNoLock: Unable find table info \n"));

        return ITS_ENOTFOUND;
    }

    /* okay now we need to remove the record from the table.  FIXME  */
    /* !!!! What user passes a different lenght... we will blow !!!! */
    /* We could store the key length in the tableInfo at config time */
    /* Note: I hope the ptr arithmetic is right !!! */
    allocPtr = ((ITS_OCTET*)object - klen);

    memcpy(allocPtr, key, klen);

    ret =  MBE_WRITEX(tableInfo->fileNum, (char*)allocPtr, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_FreeNoLock: MBE_WRITEX failed, err code %d\n",
                          ret));
        return ret;
    }

    /* release the local buffer allocated in Alloc or Find */
    DSM_FreeDataBuffer(tableInfo, allocPtr);


    return ITS_SUCCESS;
}

static int
DSM_CommitNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    ITS_OCTET* allocPtr = NULL;
    DSM_TableInfo* tableInfo = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;
    
    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_CommitNoLock: Unable find table info \n"));

        return ITS_ENOTFOUND;
    }

    allocPtr = ((ITS_OCTET*)object - klen);

    /* now position within the MBE file */
    ret = MBE_FILE_SETKEY_(tableInfo->fileNum, (char*)key, (short)klen,
                           DSM_DATA_TABLES(dataObj)[tableId].keySpec,
                           DSM_NSK_MBE_KPOS_EXACT);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_CommitNoLock: Unable to locate record in "
                         "the MBE database\n"));

        DSM_FreeDataBuffer(tableInfo, (allocPtr));

        return ITS_ENOTFOUND;
    }

    /* now update the MBE record */
    ret = MBE_WRITEUPDATEX(tableInfo->fileNum, (char*)allocPtr,
                           tableInfo->maxRowSize);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_CommitNoLock: MBE_WRITEUPDATEX failed, error"
                         " code: %d\n", ret));
    }

    DSM_FreeDataBuffer(tableInfo, allocPtr);

    return ITS_SUCCESS;
}

static int 
DSM_LockRowNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object)
{
    DSM_RowHeader* row;

    ITS_C_REQUIRE(object != NULL);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    row->locked = ITS_TRUE;
    row->lockTime = TIMERS_Time();

    return ITS_SUCCESS;
}

static int 
DSM_UnlockRowNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object)
{
    DSM_RowHeader* row;

    ITS_C_REQUIRE(object != NULL);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    row->locked = ITS_FALSE;
    row->lockTime = 0;

    return ITS_SUCCESS;
}

static void* 
DSM_AllocImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key,
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    DSM_TableInfo* tableInfo = NULL;
    ITS_OCTET* allocPtr = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;

    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_Alloc: Unable to retrieve table Info\n"));

        *error = ITS_ENOTFOUND;

        return NULL;
    }

    /* allocate some local memory (memPool or not) */
    allocPtr = DSM_GetDataBuffer(tableInfo);
    if (allocPtr == NULL)
    {
        ITS_TRACE_ERROR(("DSM_Alloc: unable to allocate memory\n"));

        *error = ITS_ENOMEM;

        return NULL;
    }

    /* the PKey is set a the first bytes of the record */
    memcpy(allocPtr, key, klen);

    /* 
     * we need to make sure that the row does not already exist. By calling
     * MBE_WRITEX we create the record if not exist or get an error if
     * there is already an entry.
     */
    ret =  MBE_WRITEX(tableInfo->fileNum, (char*)allocPtr,
                      tableInfo->maxRowSize);
    if (ret != ITS_SUCCESS)
    {
        if (ret == DSM_NSK_MBE_REC_EXIST)
        {
            ITS_TRACE_ERROR(("DSM_Alloc: attempt to add duplicate row\n"));
        }

        DSM_FreeDataBuffer(tableInfo, allocPtr);

        return NULL;
    }
    
    /* the record is created, now we need to lock it */
    ret = MBE_FILE_SETKEY_(tableInfo->fileNum, (char*)key, (short)klen,
                           DSM_DATA_TABLES(dataObj)[tableId].keySpec,
                           DSM_NSK_MBE_KPOS_EXACT);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Alloc: Unable to locate record in "
                         "the MBE database\n"));

        MBE_WRITEX(tableInfo->fileNum, (char*)allocPtr, 0);

        DSM_FreeDataBuffer(tableInfo, (void*)allocPtr);

        *error = ITS_ENOTFOUND;

        return NULL;
    }

    ret = MBE_LOCKREC(tableInfo->fileNum);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Alloc: Unable to lock record in "
                         "the MBE database\n"));

        MBE_WRITEX(tableInfo->fileNum, (char*)allocPtr, 0);

        DSM_FreeDataBuffer(tableInfo, allocPtr);

        *error = ITS_EROWNOTLOCKED;

        return NULL;
    }

    /* we return a ptr to the buffer offset by the key */
    return (void*)(allocPtr + klen);
}

static void* 
DSM_FindImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    DSM_TableInfo* tableInfo = NULL;
    ITS_OCTET* allocPtr = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;
    
    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_Find: Unable find table info \n"));

        *error = ITS_ENOTFOUND;

        return NULL;
    }

    /* allocate a local buffer to copy data in */
    allocPtr = DSM_GetDataBuffer(tableInfo);
    if (allocPtr == NULL)
    {
        ITS_TRACE_ERROR(("DSM_Find: unable to allocate memory\n"));

        *error = ITS_ENOMEM;

        return NULL;
    }

    /* position within the MBE file */
    ret = MBE_FILE_SETKEY_(tableInfo->fileNum, (char*)key, (short)klen,
                           DSM_DATA_TABLES(dataObj)[tableId].keySpec,
                           DSM_NSK_MBE_KPOS_EXACT);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Find: Unable to locate record in "
                         "the MBE database\n"));

        DSM_FreeDataBuffer(tableInfo, allocPtr);

        *error = ITS_ENOTFOUND;

        return NULL;
    }

    /* get the data into the local buffer */
    ret = MBE_READUPDATELOCKX(tableInfo->fileNum, (char*)allocPtr, 
                          tableInfo->maxRowSize);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Find: MBE_READUPDATEX failed\n"));

        DSM_FreeDataBuffer(tableInfo, allocPtr);

        *error = ITS_ENOTFOUND;
        
        return NULL;
    }
        
    return (void*)(allocPtr + klen);
}

static int 
DSM_FreeImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    ITS_OCTET* allocPtr = NULL;
    DSM_TableInfo* tableInfo = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;

    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_Free: Unable find table info \n"));

        return ITS_ENOTFOUND;
    }

    /* position and unlock the row */
    ret = MBE_FILE_SETKEY_(tableInfo->fileNum, (char*)key, (short)klen,
                           DSM_DATA_TABLES(dataObj)[tableId].keySpec,
                           DSM_NSK_MBE_KPOS_EXACT);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Free: Unable to locate record in "
                         "the MBE database\n"));

        return ITS_ENOTFOUND;
    }

    ret = MBE_UNLOCKREC(tableInfo->fileNum);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Free: Unable to unlock record in "
                         "the MBE database\n"));

        return ITS_EROWNOTLOCKED;
    }

    /* okay now we need to remove the record from the table.  FIXME  */
    /* !!!! What user passes a different lenght... we will blow !!!! */
    /* We could store the key length in the tableInfo at config time */
    /* Note: I hope the ptr arithmetic is right !!! */
    allocPtr = ((ITS_OCTET*)object - klen);

    memcpy(allocPtr, key, klen);

    ret =  MBE_WRITEUPDATEX(tableInfo->fileNum, (char*)allocPtr, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Free: MBE_WRITEUPDATEX failed, err code %d\n",
                          ret));
        return ret;
    }

    /* release the local buffer allocated in Alloc or Find */
    DSM_FreeDataBuffer(tableInfo, allocPtr);


    return ITS_SUCCESS;
}

static int 
DSM_CommitImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;
    ITS_OCTET* allocPtr = NULL;
    DSM_TableInfo* tableInfo = NULL;
    
    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);


    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* get the table information */
    tableInfo = DSM_DATA_TABLES(dataObj)[tableId].tableInfo;

    if (tableInfo == NULL)
    {
        ITS_TRACE_ERROR(("DSM_Commit: Unable find table info \n"));

        return ITS_ENOTFOUND;
    }

    allocPtr = ((ITS_OCTET*)object - klen);

    /* now position within the MBE file */
    ret = MBE_FILE_SETKEY_(tableInfo->fileNum, (char*)key, (short)klen,
                           DSM_DATA_TABLES(dataObj)[tableId].keySpec,
                           DSM_NSK_MBE_KPOS_EXACT);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Commit: Unable to locate record in "
                         "the MBE database\n"));

        DSM_FreeDataBuffer(tableInfo, (allocPtr));

        return ITS_ENOTFOUND;
    }

    /* now update the MBE record */
    ret = MBE_WRITEUPDATEUNLOCKX(tableInfo->fileNum, (char*)allocPtr,
                                 tableInfo->maxRowSize);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_Commit: MBE_WRITEUPDATELOCKX failed, error"
                         " code: %d\n", ret));
    }

    DSM_FreeDataBuffer(tableInfo, allocPtr);

    return ITS_SUCCESS;
}

static int 
DSM_LockRowImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
        
    return ITS_SUCCESS;
}

static int 
DSM_UnlockRowImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
        
    return ITS_SUCCESS;
}

static int 
DSM_TableIterateImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    void* in, 
    void* out,
    DSM_IterateEntryProc iterateEntryFn)
{

    return ITS_SUCCESS;
}

static int 
DSM_TableDumpImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    char** pStrDump,                            
    DSM_DumpEntryProc dumpEntryFn)
{
    return ITS_SUCCESS;
}

static int 
DSM_TableGetSizeImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_UINT* size)
{
    return ITS_SUCCESS;
}

static int 
DSM_MulticastEventToFtGroupMembersImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    const ITS_EVENT* event)
{
    return ITS_SUCCESS;
}


#define DSM_NSK_IMPL_CLASS_NAME "DSM Implementation Class - NSK"

DSM_ImplClassRec itsDSM_StubImplClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        0,                                  /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_NSK_IMPL_CLASS_NAME,            /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        ITS_INST_NO_CONST,                  /* instance create          */
        ITS_INST_NO_DEST,                   /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* impl part */
    {
        "NSK",
        DSM_ImplDataCreateInstanceImpl,
        DSM_ImplDataDestroyInstanceImpl,
        DSM_JoinFtGroupImpl,
        DSM_LeaveFtGroupImpl,
        DSM_SynchronizeDsmImpl,
        DSM_AllocImpl,
        DSM_FindImpl,
        DSM_FreeImpl,
        DSM_CommitImpl,
        DSM_LockRowImpl,
        DSM_UnlockRowImpl,
        DSM_LockDsmImpl,
        DSM_UnlockDsmImpl,
        DSM_LockTableImpl,
        DSM_UnlockTableImpl,
        DSM_AllocNoLockImpl,
        DSM_FindNoLockImpl,
        DSM_FreeNoLockImpl,
        DSM_CommitNoLockImpl,
        DSM_LockRowNoLockImpl,
        DSM_UnlockRowNoLockImpl,
        DSM_TableIterateImpl,
        DSM_TableDumpImpl,
        DSM_TableGetSizeImpl,
        DSM_MulticastEventToFtGroupMembersImpl
    }
};

DSMDLLAPI ITS_Class itsDSM_StubImplClass = (ITS_Class)&itsDSM_StubImplClassRec;


