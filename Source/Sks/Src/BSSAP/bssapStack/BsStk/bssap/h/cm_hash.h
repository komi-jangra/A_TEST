/********************************************************************20**
  
     Name:     common hash functions
  
     Type:     C include file
  
     Desc:     Defines required by common functions.
               (Newer version of functions in cm_bdy1)
  
     File:     cm_hash.h

     Sid:      cm_hash.h@@/main/15 - Thu Jul 10 17:27:41 2008
  
     Prg:      rg
  
*********************************************************************21*/
  
#ifndef __CMHASHH__
#define __CMHASHH__ 

  
/* defines */
typedef unsigned char   Bool;     /* boolean */
typedef char            S8;       /* signed - 8 bits */
typedef unsigned char   U8;       /* unsigned - 8 bits */

typedef short           S16;      /* signed - 16 bits */
typedef unsigned short  U16;      /* unsigned - 16 bits */

typedef int             S32;      /* signed - 32 bits */
typedef unsigned int    U32;      /* unsigned - 32 bits */
#define FALSE          0
#define TRUE           1
#define ROK         0                 /* ok */
#define RFAILED     1                 /* failed, general */
#define ROKDNA      2                 /* ok, data not available */
#define ROKDUP      12                /* ok, duplicate entry found */


#define PutHiByte(w,b) (U16) (((U16)(b) << 8) | ((U16)(w) & 0x00ff))      /* put hi byte to word */
#define PutLoByte(w,b) (U16) (((U16)(b) & 0xff) | ((U16)(w) & 0xff00))             /* put lo byte to word */
#define PutHiWord(l,w) (U32) (((U32)(w) << 16) | ((U32)(l) & (U32)0x0000ffff)) /* put hi word to long */
#define PutLoWord(l,w) (U32) (((U32)(w) & 0xffff) | ((U32)(l) & (U32)0xffff0000))         /* put lo word to long */

#define CM_HASH_KEYTYPE_DEF         0
#define CM_HASH_KEYTYPE_MULT24      1  /* key type which uses multiplication 
                                          method to compute hash list index 
                                          - function supplied by Trillium */
#define CM_HASH_KEYTYPE_DIRIDX      2  /* direct indexing of hash tables */

#define CM_HASH_KEYTYPE_STR         3  /* Hash Function for Strings */

#define CM_HASH_KEYTYPE_U32MOD      4  /* Mods the key with number of bins
                                        * useful if key is U32 numeric */

#define CM_HASH_KEYTYPE_CONID       5  /* Uses diff computation for keylen
                                         < U32. Ideal fo conId type params */

#define CM_HASH_KEYTYPE_BCD8        6  /* Converts the 8 BCD coded octets 
                                        * into 2 U32s and then adds 2 
                                        * U32s to get one U32. Then applies the 
                                        * U32Mod technique to get the index */
#define CM_HASH_KEYTYPE_ANY         7  /* Converts a variable length key into
                                        * a U32 which is then mapped to number
                                        * of hash bins
                                        */

/* Constants */
#define CM_STR_HASHFUNC_CONSTANT    31 /* Constant for CM_HASH_KEYTYPE_STR */

/* CONSTANTS for CmHashFuncConId */
/* cm_hash_h_001.main_13 : Fixed for 64 Bit */
#define CM_HASHKEYLEN_U32              sizeof(U32)  /* size of U32 */
#define CM_HASHKEYLEN_U16              sizeof(U16)  /* size of U16 */
#define CM_HASHKEYLEN_U8               sizeof(U8)  /* size of U8 */

/* query types */

#define CM_HASH_QUERYTYPE_BINS     1  /* number of bins */
#define CM_HASH_QUERYTYPE_BINSIZE  2  /* storage for each bin */
#define CM_HASH_QUERYTYPE_ENTRIES  3  /* current number of entries */
#define CM_HASH_QUERYTYPE_OFFSET   4  /* offset of CmHashListEnt in entries */
#define CM_HASH_QUERYTYPE_DUPFLG   5  /* allow duplicate keys */
#define CM_HASH_QUERYTYPE_KEYTYPE  6  /* key type for selecting hash functions */

#define CM_HASH_VALUE(entry)       (entry)->hashVal  /* computed hash value */
#define CM_HASH_SIZE(tbl)          (tbl)->nmbBins    /* hash table size */

#ifndef CM_MT_HASH_BIN
#define CM_HASH_NMBENT(tbl)        (tbl)->nmbEnt     /* number of entries in
                                                      * table
                                                      */
#endif

#define CM_HASH_DUPFLG(tbl)        (tbl)->dupFlg     /* allow duplicate keys */

#define CM_HASH_OFFSET(tbl)        (tbl)->offset     /* offset of CmHashListEnt
                                                      * structure in hash list
                                                      * entry
                                                      */

#define CM_HASH_KEYTYPE(tbl)       (tbl)->keyType    /* key type for selecting
                                                      * hash function
                                                      */

#define CM_HASH_BINSIZE       sizeof(CmListEnt) /* size of a single bin
                                                 */
/* bin bit mask */

#define CM_HASH_NOBITMASK          0x8000  /* illegal bin bit mask */

/* constant multiplier for multiplication method of computing hash index */
#define CM_HASH_MULT24_CONST       10368890   /* when key is of max 24 bits */

/* bit position where the hash index is extracted in multiplication method */
#define CM_HASH_MULT24_BITPOS        24       /* when key is of max 24 bits */

/*
 *  delete an entry from the hash table with open addressing
 */
#define cmHashListOADelete(hashListCp, entry) cmHashListDelete(hashListCp, (PTR)entry)


/* 
 * CM_HASH_MIX -- mix 3 32-bit values reversibly.
 * For every delta with one or two bits set, and the deltas of all three
 * high bits or all three low bits, whether the original value of a,b,c
 * is almost all zero or is uniformly distributed,
 * If CM_HASH_MIX() is run forward or backward, at least 32 bits in a,b,c
 * have at least 1/4 probability of changing.
 * If CM_HASH_MIX() is run forward, every bit of c will change between 1/3 and
 * 2/3 of the time.  (Well, 22/100 and 78/100 for some 2-bit deltas.)
 * CM_HASH_MIX() was built out of 36 single-cycle latency instructions in a 
 * structure that could supported 2x parallelism, like so:
 *     a -= b; 
 *     a -= c; x = (c>>13);
 *     b -= c; a ^= x;
 *     b -= a; x = (a<<8);
 *     c -= a; b ^= x;
 *     c -= b; x = (b>>13);
 *     ...
 */
#define CM_HASH_MIX(a,b,c) \
{ \
  a -= b; a -= c; a ^= (c>>13); \
  b -= c; b -= a; b ^= (a<<8);  \
  c -= a; c -= b; c ^= (b>>13); \
  a -= b; a -= c; a ^= (c>>12); \
  b -= c; b -= a; b ^= (a<<16); \
  c -= a; c -= b; c ^= (b>>5);  \
  a -= b; a -= c; a ^= (c>>3);  \
  b -= c; b -= a; b ^= (a<<10); \
  c -= a; c -= b; c ^= (b>>15); \
}

#endif /* __CMHASHH__ */

  
/********************************************************************30**
  
         End of file:     cm_hash.h@@/main/15 - Thu Jul 10 17:27:41 2008
  
*********************************************************************31*/

