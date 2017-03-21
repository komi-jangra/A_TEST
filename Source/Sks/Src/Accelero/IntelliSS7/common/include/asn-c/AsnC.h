/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:05  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:57  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:39  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:51  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:50:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 21:05:15  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:36  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:13  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:58  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/24 20:37:56  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.4  2001/02/14 20:44:54  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.3  2001/01/04 17:57:39  hdivoux
 * LOG: Cleanup
 * LOG:
 * LOG: Revision 3.2  2000/08/16 19:21:10  mmiers
 * LOG: Widen tag type to 30 bits.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/03/18 21:03:34  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 18:12:59  mmiers
 * LOG:
 * LOG: More platform cleanup.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:25:52  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.20  1999/07/22 00:34:34  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.19  1999/06/11 15:59:07  fhasle
 * LOG:
 * LOG:
 * LOG: Change newbuf() to not try to cache memory.  Memleaks were present; fix
 * LOG: caused corruption.
 * LOG:
 * LOG: Revision 1.18  1999/06/03 15:01:16  mmiers
 * LOG:
 * LOG:
 * LOG: Add a function for computing the length of a qbuf list.
 * LOG:
 * LOG: Revision 1.17  1999/06/01 17:21:13  labuser
 * LOG:
 * LOG:
 * LOG: Try again.
 * LOG:
 * LOG: Revision 1.16  1999/06/01 17:16:20  labuser
 * LOG:
 * LOG:
 * LOG: Remove berkeley byte function prototypes.
 * LOG:
 * LOG: Revision 1.15  1999/05/11 01:27:36  mmiers
 * LOG:
 * LOG:
 * LOG: Start on dual debug/release build rules.
 * LOG:
 * LOG: Revision 1.14  1999/02/26 15:41:07  mmiers
 * LOG:
 * LOG:
 * LOG: Fixes for Solaris C++ build.
 * LOG:
 * LOG: Revision 1.13  1999/02/26 02:07:36  mmiers
 * LOG:
 * LOG:
 * LOG: Make the banner a const char.  Add protos for ssdu2pe and pe2ssdu
 * LOG:
 * LOG: Revision 1.12  1999/02/26 00:48:19  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.  Remove dead file.
 * LOG:
 * LOG: Revision 1.11  1999/02/25 23:53:35  mmiers
 * LOG:
 * LOG:
 * LOG: Fix bad extern "C" position.
 * LOG:
 * LOG: Revision 1.10  1998/11/10 23:35:42  ite
 * LOG: Fix vprint() bug.
 * LOG:
 * LOG: Revision 1.9  1998/10/23 18:00:00  jrao
 * LOG: Fix prnt bugs (missing pointers, etc).
 * LOG:
 * LOG: Revision 1.8  1998/10/23 16:05:32  mmiers
 * LOG: AsnC is now threadsafe, except for ODE.
 * LOG:
 * LOG: Revision 1.7  1998/10/22 20:29:25  mmiers
 * LOG: Finish reentrancy fixes, round one.
 * LOG:
 * LOG: Revision 1.6  1998/10/22 19:28:05  mmiers
 * LOG: Continue making PSAP threadsafe.
 * LOG:
 * LOG: Revision 1.5  1998/10/22 16:28:30  mmiers
 * LOG: Getting pepsy thread-safe.
 * LOG:
 * LOG: Revision 1.4  1998/10/22 14:51:11  jrao
 * LOG: Add min/max macros back into this file.
 * LOG:
 * LOG: Revision 1.3  1998/10/21 19:43:50  mmiers
 * LOG: HPUX update for autobuild.
 * LOG:
 * LOG: Revision 1.2  1998/10/21 19:20:17  mmiers
 * LOG: Update for ALPHA build.
 * LOG:
 * LOG: Revision 1.1  1998/10/21 18:59:57  mmiers
 * LOG: New file containing most of the old ISODE info.
 * LOG:
 * LOG: Revision 1.9  1998/10/21 04:30:06  mmiers
 * LOG: Cleaning up pepsy.
 * LOG:
 * LOG: Revision 1.8  1998/10/21 02:40:33  mmiers
 * LOG: More cleanup.  Eliminated most of the extra pollution headers.
 * LOG:
 * LOG: Revision 1.7  1998/10/21 00:37:21  mmiers
 * LOG: More work on reentrancy.
 * LOG:
 * LOG: Revision 1.6  1998/10/20 23:37:32  mmiers
 * LOG: Minor tweaks, getting the C-API up to reentrant standards.
 * LOG:
 *
 *****************************************************************************/

/****************************************************************************
 *
 * This code is a derivative work of the ISODE consortium, and appears with
 * the following license:
 *
 * The ISODE is openly available but is NOT in the public domain.  You
 * are allowed and encouraged to take this software and build commercial
 * products.  However, as a condition of use, you are required to ``hold
 * harmless'' all contributors.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that this notice and the reference to this notice appearing in each
 * software module be retained unaltered, and that the name of any
 * contributors shall not be used in advertising or publicity pertaining
 * to distribution of the software without specific written prior permission.
 * No contributor makes any representations about the suitability of this
 * software for any purpose.  It is provided ``as is'' without express or
 * implied warranty.
 * 
 *      ALL CONTRIBUTORS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 *      SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 *      AND FITNESS FOR THE PARTICULAR PURPOSE, TITLE, AND NON-INFRINGEMENT.
 *
 *      IN NO EVENT SHALL ANY CONTRIBUTOR BE LIABLE FOR ANY SPECIAL,
 *      INDIRECT OR CONSEQUENTIAL DAMAGES, WHETHER IN CONTRACT, TORT, OR
 *      OTHER FORM OF ACTION, ARISING OUT OF OR IN CONNECTION WITH, THE
 *      USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 ***************************************************************************/

#ifndef _ASN_C_H_
#define _ASN_C_H_

#include <its.h>

#ident "$Id: AsnC.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#if defined(WIN32)
#include <io.h>
#endif

#ifdef  __cplusplus
extern "C"
{
#endif

/*
 * handle some libcompat holdouts
 */

void    (*set_smalloc_handler()) ();

char    *smalloc (int);

#define NELEM   100
#define NVEC    100
#define NSLACK  10

void    _asprintf ();

#define str2vec(s,v)    str2vecX((s), (v), 0, NULL, 0, 1)

int str2elem(char *s, unsigned int elements[]);
int str2vecX(char *s, char **vec, int nmask, int *mask,
             char brk, int docomma);

/*
 * types and return values
 */
#ifndef NOTOK
#define NOTOK           (-1)
#define OK              0
#define DONE            1
#endif

#ifndef INTDEF
#define INTDEF  ITS_LONG
#endif

typedef ITS_LONG integer;

typedef ITS_OCTET byte;

typedef int     *IP;
typedef void   (*VFP) ();

/*
 * looks like a BSD iovec...
 */
struct udvec
{
    ITS_POINTER uv_base;
    int         uv_len;
    int         uv_inline;
};

/***************************************************************************/

/*
 * major ASN-C data structure
 */
struct qbuf
{
    struct qbuf *qb_forw;       /* doubly-linked list */
    struct qbuf *qb_back;       /*   .. */

    int     qb_len;             /* length of data */
    char   *qb_data;            /* current pointer into data */
    char    qb_base[1];         /* extensible... */
};

#define QBFREE(qb)                                    \
{                                                     \
    struct qbuf *QB, *QP;                             \
                                                      \
    for (QB = (qb) -> qb_forw; QB != (qb); QB = QP)   \
    {                                                 \
        QP = QB -> qb_forw;                           \
        dequeue(QB);                                  \
        free ((char *) QB);                           \
    }                                                 \
}

void enqueue(struct qbuf* elem, struct qbuf* pred);
void dequeue(struct qbuf* elem);

/*
 * Some OS's don't define this in math.h
 */
#ifndef min
#define min(a, b)       ((a) < (b) ? (a) : (b))
#define max(a, b)       ((a) > (b) ? (a) : (b))
#endif

/***************************************************************************
 * OID base type
 */
#ifndef USE_BUILTIN_OIDS
#define USE_BUILTIN_OIDS        1
#endif

typedef struct OIDentifier
{
    int     oid_nelem;          /* number of sub-identifiers */

    unsigned int* oid_elements; /* the (ordered) list of sub-identifiers */
}
OIDentifier, *OID;

/*
 * OID functions and macros
 */
#define oid2ode(i,b,l)      oid2ode_aux ((i), 1, b, l)

OID     ode2oid (char*);
int     oid_cmp (OID, OID);
int     elem_cmp (unsigned int*, int, unsigned int*, int);
OID     oid_cpy (OID);
void    oid_free (OID);
int     oid2ode_aux (OID, int, char *buf, int len);
int     sprintoid (OID, char *buf, int len);
OID     str2oid (char*);

/*
 * OID base type
 ***************************************************************************/

/***************************************************************************
 * Presentation Element base type
 */
typedef ITS_OCTET  PElementClass;
typedef ITS_OCTET  PElementForm;
typedef ITS_UINT   PElementID;  /* 0..2^30th-1 are meaningful (30 bits) */

#define PE_ID_BITS      30

#define PE_ID(class,code) \
        ((int) ((((code) & 0x3fffffff) << 2) | ((class) & 0x0003)))

typedef int        PElementLen;
typedef ITS_OCTET *PElementData;

#define PEDalloc(s)             ((PElementData) malloc ((unsigned int) (s)))
#define PEDrealloc(p, s)        ((PElementData) \
                                    realloc ((char *) (p), (unsigned int) (s)))
#define PEDfree(p)              free ((char *) (p))
#define PEDcmp(b1, b2, length)  \
                        memcmp ((char *) (b2), (char *) (b1), (int) (length))
#define PEDcpy(b1, b2, length)  \
                        memcpy ((char *) (b2), (char *) (b1), (int) (length))

typedef struct PElement
{
    int     pe_errno;           /* Error codes */
#define PE_ERR_NONE     0       /*   No error */
#define PE_ERR_OVER     1       /*   Overflow */
#define PE_ERR_NMEM     2       /*   Out of memory */
#define PE_ERR_BIT      3       /*   No such bit */
#define PE_ERR_UTCT     4       /*   Malformed universal timestring */
#define PE_ERR_GENT     5       /*   Malformed generalized timestring */
#define PE_ERR_MBER     6       /*   No such member */
#define PE_ERR_PRIM     7       /*   Not a primitive form */
#define PE_ERR_CONS     8       /*   Not a constructor form */
#define PE_ERR_TYPE     9       /*   Class/ID mismatch in constructor */
#define PE_ERR_OID      10      /*   Malformed object identifier */
#define PE_ERR_BITS     11      /*   Malformed bitstring */
#define PE_ERR_NOSUPP   12      /*   Type not supported */
#define PE_ERR_SIGNED   13      /*   Signed integer not expected */
#define PE_ERR_DUPLICATE 14     /*   duplicate member */
#define PE_ERR_SYNTAX   15      /*   syntax error */

                                /* for the PSAP */
    int     pe_context;         /* indirect reference */
#define PE_DFLT_CTX     0       /*   the default context */

#define PE_ID_XTND      0x1f    /* distinguished ID for extension bits */
#define PE_ID_MORE      0x80    /* more to come flag */
#define PE_ID_MASK      0x7f    /* value in extension byte */
#define PE_ID_SHIFT     7

#define PE_CLASS_MASK   0xc0    /* identifier class bits (8-7) */
#define PE_CLASS_SHIFT  6
#define PE_FORM_MASK    0x20    /* identifier form bit (6) */
#define PE_FORM_SHIFT   5
#define PE_CODE_MASK    0x1f    /* identifier code bits (5-1) + ... */
#define PE_CODE_SHIFT   0

    PElementClass       pe_class;
#define PE_CLASS_UNIV   0x0     /*   Universal */
#define PE_CLASS_APPL   0x1     /*   Application-wide */
#define PE_CLASS_CONT   0x2     /*   Context-specific */
#define PE_CLASS_PRIV   0x3     /*   Private-use */

    PElementForm        pe_form;
#define PE_FORM_PRIM    0x0     /*   PRIMitive */
#define PE_FORM_CONS    0x1     /*   CONStructor */
#define PE_FORM_ICONS   0x2     /*   internal: Inline CONStructor */

    PElementID pe_id;           /* should be extensible, 14 bits for now */
                                /* Pseudo Types */
#define PE_UNIV_EOC     0x000   /*   End-of-contents */

                                /* Built-in Types */
#define PE_PRIM_BOOL    0x001   /*   Boolean */
#define PE_PRIM_INT     0x002   /*   Integer */
#define PE_PRIM_BITS    0x003   /*   Bitstring */
#define PE_PRIM_OCTS    0x004   /*   Octetstring */
#define PE_PRIM_NULL    0x005   /*   Null */
#define PE_PRIM_OID     0x006   /*   Object identifier */
#define PE_PRIM_ODE     0x007   /*   Object descriptor */
#define PE_CONS_EXTN    0x008   /*   External */
#define PE_PRIM_REAL    0x009   /*   Real */
#define PE_PRIM_ENUM    0x00a   /*   Enumerated type */
#define PE_PRIM_ENCR    0x00b   /*   Encrypted */
#define PE_CONS_SEQ     0x010   /*   Sequence */
#define PE_CONS_SET     0x011   /*   Set */

                                /* Defined Types */
#define PE_DEFN_NUMS    0x012   /*   Numeric String */
#define PE_DEFN_PRTS    0x013   /*   Printable String */
#define PE_DEFN_T61S    0x014   /*   T.61 String */
#define PE_DEFN_VTXS    0x015   /*   Videotex String */
#define PE_DEFN_IA5S    0x016   /*   IA5 String */
#define PE_DEFN_UTCT    0x017   /*   UTC Time */
#define PE_DEFN_GENT    0x018   /*   Generalized Time */
#define PE_DEFN_GFXS    0x019   /*   Graphics string (ISO2375) */
#define PE_DEFN_VISS    0x01a   /*   Visible string */
#define PE_DEFN_GENS    0x01b   /*   General string */
#define PE_DEFN_CHRS    0x01c   /*   Character string */

    PElementLen pe_len;
#define PE_LEN_XTND     0x80    /* long or indefinite form */
#define PE_LEN_SMAX     127     /* largest short form */
#define PE_LEN_MASK     0x7f    /* mask to get number of bytes in length */
#define PE_LEN_INDF     (-1)    /* indefinite length */

    PElementLen pe_ilen;

    union
    {
        PElementData     un_pe_prim;    /* PRIMitive value */
        struct PElement *un_pe_cons;    /* CONStructor head */
    }
    pe_un1;
#define pe_prim pe_un1.un_pe_prim
#define pe_cons pe_un1.un_pe_cons

    union
    {
        int         un_pe_cardinal;     /* cardinality of list */
        int         un_pe_nbits;        /* number of bits in string */
    }
    pe_un2;
#define pe_cardinal     pe_un2.un_pe_cardinal
#define pe_nbits        pe_un2.un_pe_nbits

    int     pe_inline;          /* for "ultra-efficient" PElements */
    char   *pe_realbase;        /*   .. */

    int     pe_offset;          /* offset of element in sequence */

    struct PElement *pe_next;

    int     pe_refcnt;          /* hack for ANYs in pepy */

#ifdef  DEBUG
    struct PElement *pe_link;   /* malloc debugging... */
#endif
}
PElement, *PE;

#define pe_seterr(pe, e, v)     ((pe) -> pe_errno = (e), (v))

PE      pe_alloc (PElementClass, PElementForm, PElementID);
void    pe_free (PE);
int     pe_cmp (PE, PE);
PE      pe_cpy (PE);
int     pe_pullup (PE);
PE      pe_expunge (PE, PE);
int     pe_extract (PE, PE);

PE      str2pe (char*, int, int*, int*);
PE      qb2pe (struct qbuf *, int, int, int*);

/*
 * Presentation Element base type
 ***************************************************************************/

/***************************************************************************
 * Time base type
 */
typedef struct UTCtime
{
    int     ut_year;
    int     ut_mon;
    int     ut_mday;
    int     ut_hour;
    int     ut_min;
    int     ut_sec;
    int     ut_usec;
    int     ut_zone;

    int     ut_flags;
#define UT_NULL         0x00
#define UT_ZONE         0x01
#define UT_SEC          0x02
#define UT_USEC         0x04
}
UTCtime, *UTC;

void    tm2ut (struct tm *, UTC);
long    gtime (struct tm *);
struct tm ut2tm (UTC);

/*
 * Time base type
 ***************************************************************************/

/***************************************************************************
 * BOOLEAN, INTEGER operations
 */
int     prim2flag (PE);
int     prim2num (PE);
PE      flag2prim (int, PElementClass, PElementID);
PE      num2prim (integer, PElementClass, PElementID);

#define bool2prim(b)            flag2prim ((b), PE_CLASS_UNIV, PE_PRIM_BOOL)
#define int2prim(i)             num2prim ((integer) (i), PE_CLASS_UNIV, PE_PRIM_INT)


/***************************************************************************
 * ENUMERATION operations
 */
#define prim2enum(i)            prim2num((i))
#define enum2prim(a,b,c)        num2prim((a), (b), (c))
#define enumint2prim(i)         enum2prim ((i), PE_CLASS_UNIV, PE_PRIM_ENUM)


/***************************************************************************
 * REAL operations
 */
#define PE_REAL_FLAGS   0300    /* flag bits of real */
#define         PE_REAL_BINENC  0200    /* binary encoding */
#define         PE_REAL_DECENC  0000    /* decimal encoding */
#define         PE_REAL_SPECENC 0100    /* special encoding */

#define PE_REAL_B_S     0100    /* sign bit */
#define PE_REAL_B_BASE  0060    /* base bits */
#define         PE_REAL_B_B2    0000
#define         PE_REAL_B_B8    0020
#define         PE_REAL_B_B16   0040

#define PE_REAL_B_F     0014    /* factor bits */
#define PE_REAL_B_EXP   0003    /* exponent type bits */
#define         PE_REAL_B_EF1   0000
#define         PE_REAL_B_EF2   0001
#define         PE_REAL_B_EF3   0002
#define         PE_REAL_B_EF4   0003

#define PE_REAL_PLUSINF         0200
#define PE_REAL_MINUSINF        0201

#ifndef HUGE_VAL
#ifdef MAXFLOAT
#define PE_REAL_INFINITY        MAXFLOAT
#else
#define PE_REAL_INFINITY        99.e99
#endif
#else
#define PE_REAL_INFINITY        HUGE_VAL
#endif

double  prim2real (PE);
PE      real2prim (double, PElementClass, PElementID);

#define double2prim(i)          real2prim ((i), PE_CLASS_UNIV, PE_PRIM_REAL)


/***************************************************************************
 * Various STRING operations
 */
char   *prim2str (PE, int*);
PE      str2prim (char*, int, PElementClass, PElementID);
struct qbuf   *prim2qb (PE);
PE      qb2prim_aux (struct qbuf* qb, PElementClass classOf,
                     PElementID id, int in_line);

#define qb2prim(q,c,i)          qb2prim_aux ((q), (c), (i), 0)
#define oct2prim(s,len)         str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_PRIM_OCTS)
#define ia5s2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_IA5S)
#define nums2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_NUMS)
#define prts2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_PRTS)
#define t61s2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_T61S)
#define vtxs2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_VTXS)
#define gfxs2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_GFXS)
#define viss2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_VISS)
#define gens2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_GENS)
#define chrs2prim(s,len)        str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_DEFN_CHRS)
#define ode2prim(s,len)         str2prim ((s), (len), \
                                            PE_CLASS_UNIV, PE_PRIM_ODE)

/***************************************************************************
 * BIT STRING operations
 */
PE      prim2bit (PE);
PE      bit2prim (PE);

int     pbit_on (PE, int);
int     pbit_off (PE, int);
int     pbit_test (PE, int);

/***************************************************************************
 * OID operations
 */
OID     prim2oid (PE);
PE      obj2prim (OID, PElementClass, PElementID);

#define oid2prim(o)             obj2prim ((o), PE_CLASS_UNIV, PE_PRIM_OID)

/***************************************************************************
 * TIME operations
 */
UTC     prim2time (PE, int);
PE      time2prim (UTC, int, PElementClass, PElementID);
int     time2str (UTC, int, char *buffer, int len);
int     str2utct (UTC, char*, int);
int     str2gent (UTC, char*, int);

#define prim2utct(pe)           prim2time ((pe), 0)
#define prim2gent(pe)           prim2time ((pe), 1)
#define utct2prim(u)            time2prim ((u), 0, PE_CLASS_UNIV, PE_DEFN_UTCT)
#define gent2prim(u)            time2prim ((u), 1, PE_CLASS_UNIV, PE_DEFN_GENT)
#define utct2str(u)             time2str ((u), 0)
#define gent2str(u)             time2str ((u), 1)

/***************************************************************************
 * SET, SEQUENCE operations
 */
PE      prim2set (PE);
int     set_add (PE, PE), set_addon ();
int     set_del (PE, PElementClass, PElementID);
PE      set_find (PE, PElementClass, PElementID);
int     seq_add (PE, PE, int), seq_addon ();
int     seq_del (PE, int);
PE      seq_find (PE, int);

#define set2prim(pe)            (pe)
#define first_member(pe)        ((pe) -> pe_cons)
#define next_member(pe,p)       ((p) -> pe_next)

#define prim2seq(pe)            (prim2set (pe))
#define seq2prim(pe)            (pe)


/***************************************************************************
 * error codes
 */
char   *pe_error (int);

/***************************************************************************
 * PRESENTATION STREAMS.  This stuff may go
 */
struct _PStream;

typedef int (*PRIMEFP)(struct _PStream *, int);
typedef int (*RWFP)(struct _PStream *, PElementData data, PElementLen n, int in_line);
typedef int (*FLUSHFP)(struct _PStream *);
typedef int (*CLOSEFP)(struct _PStream *);
typedef int (*OPENFP)(struct _PStream *);

typedef struct _PStream
{
    int     ps_errno;           /* Error codes */
#define PS_ERR_NONE      0      /*   No error */
#define PS_ERR_OVERID    1      /*   Overflow in ID */
#define PS_ERR_OVERLEN   2      /*   Overflow in length */
#define PS_ERR_NMEM      3      /*   Out of memory */
#define PS_ERR_EOF       4      /*   End of file */
#define PS_ERR_EOFID     5      /*   End of file reading extended ID */
#define PS_ERR_EOFLEN    6      /*   End of file reading extended length */
#define PS_ERR_LEN       7      /*   Length mismatch */
#define PS_ERR_TRNC      8      /*   Truncated */
#define PS_ERR_INDF      9      /*   Indefinite length in primitive form */
#define PS_ERR_IO       10      /*   I/O error */
#define PS_ERR_EXTRA    11      /*   Extraneous octets */
#define PS_ERR_XXX      12      /*   XXX */

    union
    {
        ITS_POINTER un_ps_addr;
        struct
        {
            char   *st_ps_base;
            int     st_ps_cnt;
            char   *st_ps_ptr;
            int     st_ps_bufsiz;
        }
        un_ps_st;
        struct
        {
            struct udvec *uv_ps_head;
            struct udvec *uv_ps_cur;
            struct udvec *uv_ps_end;
            int     uv_ps_elems;
            int     uv_ps_slop;
            int     uv_ps_cc;
        }
        un_ps_uv;
    }
    ps_un;
#define ps_addr ps_un.un_ps_addr
#define ps_base ps_un.un_ps_st.st_ps_base
#define ps_cnt  ps_un.un_ps_st.st_ps_cnt
#define ps_ptr  ps_un.un_ps_st.st_ps_ptr
#define ps_bufsiz       ps_un.un_ps_st.st_ps_bufsiz
#define ps_head ps_un.un_ps_uv.uv_ps_head
#define ps_cur  ps_un.un_ps_uv.uv_ps_cur
#define ps_end  ps_un.un_ps_uv.uv_ps_end
#define ps_elems        ps_un.un_ps_uv.uv_ps_elems
#define ps_slop ps_un.un_ps_uv.uv_ps_slop
#define ps_cc   ps_un.un_ps_uv.uv_ps_cc

    ITS_POINTER ps_extra;               /* for George's recursive PStreams */

    int     ps_inline;          /* for "ultra-efficient" PStreams */

    int     ps_scratch;         /* XXX */

    int     ps_byteno;          /* byte position */

    PRIMEFP ps_primeP;
    RWFP    ps_readP;
    RWFP    ps_writeP;
    FLUSHFP ps_flushP;
    CLOSEFP ps_closeP;
}
PStream, *PS;

#define ps_seterr(ps, e, v)     ((ps) -> ps_errno = (e), (v))

/***************************************************************************
 * PS operations
 */
PS      ps_alloc (OPENFP);
void    ps_free (PS);
int     ps_io (PS, RWFP, PElementData, PElementLen, int);
int     ps_flush (PS);
int     std_open (PS);
int     ps_printf (PS, const char*, ...);

#define ps_read(ps, data, cc)   ps_io ((ps), (ps) -> ps_readP, (data), (cc), 0)
#define ps_write(ps, data, cc)  ps_write_aux ((ps), (data), (cc), 0)
#define ps_write_aux(ps, data, cc, in_line) \
        ps_io ((ps), (ps) -> ps_writeP, (data), (cc), (in_line))


/***************************************************************************
 * PS implementations
 */
#define std_setup(ps, fp)       ((ps) -> ps_addr = (ITS_POINTER) (fp), OK)
#define qbuf_setup(ps, qb)      ((ps) -> ps_addr = (ITS_POINTER) (qb), OK)

int     str_open (PS);
int     str_setup (PS, char*, int, int);
int     qbuf_open (PS);

/***************************************************************************
 * PS/PE interop
 */
#define ps2pe(ps)               ps2pe_aux ((ps), 1, 1)
#define pe2ps(ps, pe)           pe2ps_aux ((ps), (pe), 1)

int     ps_prime (PS, int);

PE      ps2pe_aux (PS, int, int);
int     pe2ps_aux (PS, PE, int);

/*
 * length management (ASN encode default for length
 */
extern int    ps_len_strategy;
#define PS_LEN_SPAG     0
#define PS_LEN_INDF     1
#define PS_LEN_LONG     2

int     ps_get_abs (PE);
char   *ps_error (int);

/***************************************************************************
 * MISCELLANEOUS
 */
struct isobject
{
    char   *io_descriptor;

    OIDentifier io_identity;
};

int     setisobject (int),      endisobject ();
struct isobject *getisobject ();

struct isobject *getisobjectbyname (char*);
struct isobject *getisobjectbyoid (OID);

/***************************************************************************
 * QB implementations
 */
int     pe2qb_f (PE, char **, char*, int*);
PE      qbuf2pe (struct qbuf *qb, int len, int *result);
char   *qb2str (struct qbuf*);
int     qb2len (struct qbuf* q);

struct qbuf *str2qb (char*, int, int);
struct qbuf *qb_cpy (struct qbuf*);
void    qb_free (struct qbuf*);

void    int2strb (int n, int len, char* buf, int buflen);
int     strb2int ();

PE strb2bitstr (char *cp, int len, PElementClass classOf, PElementID id);

char   *bitstr2strb (PE, int *);

/***************************************************************************
 * The biggies
 */
int     pe2ssdu (PE, char **, int *);
PE      ssdu2pe (char *, int, char *, int *);

/***************************************************************************
 * ASN output stuff
 */
typedef int (*PRNTFP)(FILE *, const char *, ...);

typedef struct _vstruct
{
    PRNTFP          vfnx;
    FILE*           vfp;
    int             vlevel;
    int             vnamelock;
    int             didvpush;
    int             didvpop;
    int             didname;
    int             docomma;
    char *          vbp;
    char *          vsp;
    PS              vps;
}
VSTRUCT;

int     testdebug ();

void    vpush (VSTRUCT *), vpop (VSTRUCT *);
void    vname (VSTRUCT *, char *), vtag (VSTRUCT *, int, int);
void    vprint (VSTRUCT *, ...);
void    vstring (VSTRUCT *, PE), vunknown (VSTRUCT *, PE);

char   *bit2str (VSTRUCT*, PE, char *);

void    vpushstr (VSTRUCT *, char *), vpopstr (VSTRUCT *);

/* handle calls to the vunknown print routine */
#define vunknown_P      0, ((modtyp *) 0)

/***************************************************************************
 * Old pepsy stuff
 */
#ifndef ASN_COMPILER_BUILD

#ifndef	PEPYPARM
#define PEPYPARM	char *
#endif


/*
 * Definitions for pep tables
 */
typedef struct
{
	int	pe_type;	/* Type of entry */
	integer	pe_ucode;	/* index to user's code if any */
	int	pe_tag;		/* Tag of this entry if any */
	int	pe_flags;	/* Flags */
	char **pe_typename; /* User defined name of variable */
}
ptpe;
#define tpe ptpe

/* extract a pointer from the pointer table */
#define PGPTR(mod, ind, type)	  ((type )(mod)->md_ptrtab[ind])

/* tricky situation with the "type" - it must not contain the brackets of the
 * cast because we supply them here 
 */

/* macros for getting values of default flexibly */
#define IVAL(mod, x)      ((x)->pe_ucode)         /* Integer value */
#define PVAL(mod, x)      (PGPTR(mod, (x)->pe_tag, char *)) /* (char *) */
#define TVAL(mod, x)      ((x)->pe_flags)         /* Type - Integer value */
#define RVAL(mod, x)	  (*PGPTR(mod, (x)->pe_tag, double *))  /* double */

/* macros for getting other more general pointers transparently */
#define EXT2MOD(mod, x)	   (PGPTR(mod, (x)->pe_ucode, modtyp *))

/* Types */
#define PE_START	(-1)
#define	PE_END		0
#define XOBJECT		3
#define	UCODE		6
#define MEMALLOC	7
#define	SCTRL		8
#define	CH_ACT		9
#define OPTL		10	/* Optionals field offset */
#define BOPTIONAL	11 /* optional test for next */
#define FREE_ONLY       13 /* the next item is only for freeing code */

/* types that generate data */
#define TYPE_DATA	20

#define ANY		(TYPE_DATA + 0)
#define INTEGER		(TYPE_DATA + 1)
#define BOOLEAN		(TYPE_DATA + 2)
#define OBJECT		(TYPE_DATA + 3)		/* This generates data */
#define BITSTRING	(TYPE_DATA + 4)
#define OCTETSTRING	(TYPE_DATA + 5)
#define SET_START	(TYPE_DATA + 6)
#define	SEQ_START	(TYPE_DATA + 7)
#define SEQOF_START	(TYPE_DATA + 8)
#define SETOF_START	(TYPE_DATA + 9)
#define CHOICE_START	(TYPE_DATA + 10)
#define REALTYPE	(TYPE_DATA + 11)	/* ASN.1 Real */
#define ASN_NULL	(TYPE_DATA + 12)
#define ASN_OID		(TYPE_DATA + 13)
#define ETAG		(TYPE_DATA + 14) /*so set_find in pr_set is executed*/
#define IMP_OBJ		(TYPE_DATA + 15) /*so set_find in pr_set is executed*/
#define EXTOBJ		(TYPE_DATA + 16) /* External reference object */
#define EXTMOD		(TYPE_DATA + 17) /* External module for above object */
#define OBJID		(TYPE_DATA + 18) /* Object Identifier */
#define DFLT_F		(TYPE_DATA + 19)/* Default value for following entry */
#define DFLT_B		(TYPE_DATA + 20)/* default value for previous entry */
#define T_STRING	(TYPE_DATA + 21)/* [[ s ptr ]] supporting entry */
#define OCTET_PTR	(TYPE_DATA + 22)/* [[ o ptr $ len]] str entry */
#define OCTET_LEN	(TYPE_DATA + 23)/* [[ o ptr $ len]] len entry */
#define BITSTR_PTR	(TYPE_DATA + 24)/* [[ x ptr $ len]] str entry */
#define BITSTR_LEN	(TYPE_DATA + 25)/* [[ x ptr $ len]] len entry */

#if PEPSY_VERSION >= 2
#define STYPE_DATA	(TYPE_DATA + 50) /* Below here are the S* items */
#else
#define STYPE_DATA	(TYPE_DATA + 30) /* Below here are the S* items */
#endif
/* Optimised - No indirection to cope with ISODE optimisation */
#define SBITSTRING	(STYPE_DATA + 0) /* No offset */
#define SOBJID		(STYPE_DATA + 1) /* Object Identifier - No offset */
#define SREALTYPE	(STYPE_DATA + 2) /* ASN.1 Real */
#define SANY		(STYPE_DATA + 3)
#define SEXTOBJ		(STYPE_DATA + 4) /* External reference object */
#define SOBJECT		(STYPE_DATA + 5)	/* This generates data */
#define SOCTETSTRING	(STYPE_DATA + 6) /* No offset */
#define SEXTERNAL	(STYPE_DATA + 7) /* External to be encoded */
#define SSEQ_START	(STYPE_DATA + 8) /* SEQUENCE don't indirect */
#define SSET_START	(STYPE_DATA + 9) /* SET don't do an indirection */
#define SSEQOF_START	(STYPE_DATA + 10) /* SEQOF - no indirection */
#define SSETOF_START	(STYPE_DATA + 11) /* SETOF - no indirection */
#define SCHOICE_START	(STYPE_DATA + 12) /* CHOICE - no indirection */

#define ISDTYPE(p)	(p->pe_type >= TYPE_DATA)

/* User code indexes */

#define NONE		0		/* No User code */
/* Standard Tags */

#define T_BOOL		1
#define T_INTEGER	2
#define T_OCTETSTRING	4
#define T_OBJIDENT	6
#define T_EXTERNAL	8
#define T_REAL		9
#define T_ENUMERATED	10
#define T_SEQ		16
#define T_SET		17
#define T_IA5		22
#define T_GRAPHIC	25

/* Flags */

/* Use values 0-3 bottom two bits at the moment */
/* This has to be changed if the values for the 4 below are changed in ISODE */
#define FL_CLASS	0xf	
/* Class specification */
#define FL_UNIVERSAL	PE_CLASS_UNIV
#define FL_APPLICATION	PE_CLASS_APPL
#define FL_CONTEXT	PE_CLASS_CONT
#define FL_PRIVATE	PE_CLASS_PRIV


#define FL_IMPLICIT	0100
#define FL_DEFAULT	0200
#define FL_OPTIONAL	0400

#define POPTIONAL(p)		((p)->pe_flags & FL_OPTIONAL)

#define DEFAULT(p)		((p)->pe_flags & FL_DEFAULT)

#define FL_PRTAG	01000	/* only for printing - print the tag */

#define PRINT_TAG(p)		((p)->pe_flags & FL_PRTAG)

#define FL_USELECT	02000	/* user code selects */

#define IF_USELECT(p)		((p) -> pe_flags & FL_USELECT)


#define CLASS(p)	((PElementClass)((p)->pe_flags & FL_CLASS))
#define TAG(p)		((PElementID)((p)->pe_tag))

/* signed version of above - needed for tag == -1 */
#define STAG(p)		((p)->pe_tag)

#define TESTBIT(p, bit)	((p) & (1 << (bit)))
#define SETBIT(p, bit)	((p) |= (1 << (bit)))
#define CLRBIT(p, bit)	((p) &= ~(1 << (bit)))

/* To support the OPTIONAL << field $ bitno >> construct */
#define BITTEST(p, bit)	(((p)[(bit)/8]) & (0x80 >> (bit) % 8))
#define BITSET(p, bit)	(((p)[(bit)/8]) |= (0x80 >> (bit) % 8))
#define BITCLR(p, bit)	(((p)[(bit)/8]) &= ~(0x80 >> (bit) % 8))

/* compute the number of char's required to support x bits */
#define NBITS2NCHARS(x)		(((x) + 7)/8)

/*
 * The module table. One per module which gives access to everything one needs
 * to know about the modules types
 */

typedef	struct
{
    char        *md_name;	/* Name of this module */
    int	        md_nentries;	/* Number of entries */
    tpe	        **md_etab;	/* Pointer to encoding tables */
    tpe	        **md_dtab;	/* Pointer to decoding tables */
    ptpe        **md_ptab;	/* Pointer to printing tables */
    int	        (*md_eucode)(PEPYPARM, PE *, ptpe *);
                             	/* User code for encoding */
    int	        (*md_ducode)(PEPYPARM *, PE, ptpe *, int);
                            	/* User code for decoding */
    int	        (*md_pucode)(PE, ptpe *);
                            	/* User code for printing */
    ITS_POINTER	*md_ptrtab;	/* pointer table */
}
modtyp;

#define	LOTSOFBITS	128

int	enc_f   (int, modtyp*, PE*, int, int, char*, char*);
int	dec_f   (int, modtyp*, PE, int, int*, char**, char**);
int	fre_obj (char*, tpe*, modtyp*, int);
int     prnt_f(int typ, modtyp *mod, PE pe, int explict, int *len, char **buf);

#endif /* ASN_COMPILER_BUILD */

#ifdef  __cplusplus
}
#endif

#endif /* _ASN_C_H_ */
