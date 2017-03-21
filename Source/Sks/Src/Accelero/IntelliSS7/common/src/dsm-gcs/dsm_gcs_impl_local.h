
#if !defined(_DSM_GCS_IMPL_LOCAL_H_)
#define _DSM_GCS_IMPL_LOCAL_H_


#define DSM_DATA_TABLES(x) \
    (((DSM_DataObject*)(x))->dataObject.tables)



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

#endif /* _DSM_GCS_IMPL_LOCAL_H_ */

