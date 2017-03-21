/********************************************************************20**

     Name:     common hash functions

     Type:     C include file

     Desc:     Structures, variables and typedefs required by common
               functions.
               (Newer version of functions in cm_bdy1)

     File:     cm_hash.x

     Sid:      cm_hash.x@@/main/13 - Thu Jul 10 17:27:41 2008

     Prg:      na

*********************************************************************21*/

#ifndef __CMHASHX__
#define __CMHASHX__

/* typedefs */

/* forward definitions */

typedef struct cmHashListCp CmHashListCp;     /*  hash list control point */


/* hash function */

typedef S16 (* CmHashFunc) (CmHashListCp *hashListCp, U8 *key, 
                                  U16 keyLen, U16 *idx);

/* list entry */
typedef struct cmListEnt CmListEnt;      /* list entry */

struct cmListEnt                         /* list entry */
{
   CmListEnt *next;                /* next entry in list */
   CmListEnt *prev;                /* prev entry in list */
};

#ifdef CM_MT_HASH_BIN
typedef struct cmListBinEnt CmListBinEnt;/* Bin entry */

struct cmListBinEnt                /* Bin entry */
{
   CmListEnt *next;                /* next entry in list */
   CmListEnt *prev;                /* prev entry in list */
   U16 nmbEnt;                     /* current number of entries */
};
#endif


/* hash list entry */
   
typedef struct cmHashListEnt       /* hash list entry */
{
   CmListEnt list;                 /* list pointers */
   U8*  key;                       /* pointer to key */
   U16 keyLen;                     /* length of key */
   U16 hashVal;                    /* computed hash value */
} CmHashListEnt;

/* hash list control point */

struct cmHashListCp        /*  hash list control point */
{
#ifndef CM_MT_HASH_BIN
   CmListEnt *hl;                  /* pointer to hash list bins */
#else
   CmListBinEnt *hl;               /* pointer to hash list bins */
#endif
   U16 nmbBins;                    /* number of hash list bins */
   U16 binBitMask;                 /* number of bits if nmbBins is power of 2 */
   U8  nmbBinBits;                 /* number of bits to represent nmbBins */
#ifndef CM_MT_HASH_BIN
   U16 nmbEnt;                     /* current number of entries */
#endif
   U16 offset;                     /* offset of CmHashListEnt in entries */
   Bool dupFlg;                    /* allow duplicate keys */
   U16  keyType;                   /* key type for selecting hash functions */
   CmHashFunc hashFunc;            /* hash function for this key type */
};


/* functions prototypes */

extern S16 cmHashListInit (
              CmHashListCp *hashListCp,  /* hash list to initialize */
              U16          nmbBins,      /* number of hash list bins */
              U16          offset,       /* offset of CmHashListEnt in entries */
              Bool         dupFlg,       /* allow duplicate keys */
              U16          keyType);     /* key type for selecting hash fn */

extern S16 cmHashListDeinit (
              CmHashListCp *hashListCp);/* hash list to initialize */

extern S16 cmHashListInsert (
              CmHashListCp *hashListCp,  /* hash list to add to */
              U16          *entry,        /* entry to add */
              U8           *key,         /* pointer to key */
              U16          keyLen);     /* length of key */

extern S16 cmHashListDelete (
              CmHashListCp *hashListCp,  /* hash list to delete from */
              U16          *entry);      /* entry to delete */

extern S16 cmHashListFind (
              CmHashListCp *hashListCp,  /* hash list to search */
              U8           *key,         /* pointer to key */
              U16          keyLen,       /* length of key */
              U16          seqNmb,       /* used in case of duplicate keys */
              U16          **entry);     /* entry to be returned */

extern S16 cmHashListGetNext (
              CmHashListCp *hashListCp,    /* hash list to get from */
              U16          *prevEnt,        /* previous entry */
              U16          **entry);       /* entry to be returned */

#ifdef CM_MT_HASH_BIN
extern S16 cmHashListBinGetNextEntry (
              CmHashListCp *hashListCp,    /* hash list to get from */
              U16          binIdx,         /* Index of the bin */
              U16          *prevEnt,        /* previous entry */
              U16          *entry);       /* entry to be returned */
#endif

/* This function is obsoleted! Use macros defined in cm_hash.h instead
 */
extern S16 cmHashListQuery (
              CmHashListCp *hashListCp,    /* hash list to query */
              U8           queryType,      /* type of query */
              U16          *result);      /* result of query */

/* Hash list with open addressing
 */
extern S16 cmHashListOAInsert (
              CmHashListCp *hashListCp,  /* hash list to add to */
              U16          *entry,        /* entry to add */
              U8           *key,         /* pointer to key */
              U16          keyLen);     /* length of key */

void print_key(unsigned char *bufprt,int buflen);
#endif /* __CMHASHX__ */

  
/********************************************************************30**
  
         End of file:     cm_hash.x@@/main/13 - Thu Jul 10 17:27:41 2008
  
*********************************************************************31*/

