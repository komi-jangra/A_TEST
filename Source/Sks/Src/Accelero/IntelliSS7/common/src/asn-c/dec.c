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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:11  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:01  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1  2007/03/30 04:49:45  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:18  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:13  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 21:05:15  mmiers
 * LOG: Tandem port.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:45  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:17  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:01  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/07/24 20:37:56  mmiers
 * LOG: Credits.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:15  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.3  2001/02/14 20:33:12  mmiers
 * LOG: Add ident
 * LOG:
 * LOG: Revision 3.2  2001/01/04 17:21:57  hdivoux
 * LOG: symbol collision
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:04:19  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:03:36  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:26:22  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/07/22 00:34:35  mmiers
 * LOG:
 * LOG:
 * LOG: Try to be 64 bit clean.
 * LOG:
 * LOG: Revision 1.7  1999/06/30 16:15:50  mmiers
 * LOG:
 * LOG:
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.6  1999/06/01 17:15:07  labuser
 * LOG:
 * LOG:
 * LOG: Remove Berkely byte functions, replace with STDC mem functions.
 * LOG:
 * LOG: Revision 1.5  1999/03/02 18:14:51  mmiers
 * LOG:
 * LOG:
 * LOG: Watch the header file ordering (I did it again).
 * LOG:
 * LOG: Revision 1.4  1999/02/26 04:09:50  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.3  1999/02/26 00:47:56  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.2  1998/11/19 02:40:27  mmiers
 * LOG: Remove warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/27 01:15:01  mmiers
 * LOG: Make a new library, combining all the old ISODE stuff under one
 * LOG: roof.  Use one, you have to use them all.
 * LOG:
 * LOG: Revision 1.10  1998/10/23 00:19:17  mmiers
 * LOG: Working on pepsy.
 * LOG:
 * LOG: Revision 1.9  1998/10/22 16:28:31  mmiers
 * LOG: Getting pepsy thread-safe.
 * LOG:
 * LOG: Revision 1.8  1998/10/22 00:47:38  whu
 * LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 * LOG:
 * LOG: Revision 1.7  1998/10/21 17:48:18  mmiers
 * LOG: Remove last vestiges of ISODE.
 * LOG:
 *
 *****************************************************************************/

/* LOG: Oops, WATCH OUT: the PEPSY_VERSION is defined in pepsy-driver.h, so
 * LOG: make SURE this comes before AsnC.h.
 */
#include "pepsy-driver.h"
#include <asn-c/AsnC.h>

#ident "$Id: dec.c,v 1.1.1.1 2007-10-08 11:11:40 bsccs2 Exp $"

extern int pepsylose(modtyp *a, ptpe *b, PE pe, ...);
extern ptpe *next_tpe(), *fdflt_b();
extern char *pr_petype();
extern int ismatch();

#define NEXT_TPE(p)     (p = next_tpe(p))
#define CHKTAG(mod, p, pe)      ismatch(p, mod, pe->pe_class, pe->pe_id)
#define pname(t)        ((t)->pe_typename ? *(t) -> pe_typename : "???")

static char oomsg[] = "Out of memory";
#define oom(a,b)        pepsylose ((a), (b), NULL, oomsg)

static char inpmsg[] = "Illegal Null Pointer";
#define inpm(a,b)       pepsylose ((a), (b), NULL, inpmsg)

static PE setpresent(PE head, ptpe *p, modtyp *mod);

#define F_CI 0x100      /* called internally */

/* Have we got an optional object which we have allocated space for */
#define ALLOC_MEM(p, parm)      (p->pe_type == SOBJECT \
        && p[-1].pe_type == MEMALLOC)

static int pr_obj(int expl, PE pe, char **parm, ptpe *p, modtyp *mod);
static int pr_type(int expl, PE pe, char **parm, ptpe *p, modtyp *mod);
static int pr_seq(PE pe, char **parm, ptpe *p, modtyp *mod);
static int pr_set(PE pe, char **parm, ptpe *p, modtyp *mod);
static int pr_seqof(PE pe, char **parm, ptpe *p, modtyp *mod);
static int pr_setof(PE pe, char **parm, ptpe *p, modtyp *mod);
static int pr_choice(PE pe, char **parm, ptpe *p, modtyp *mod);
static int pr_etype(PE pe, char **parm, ptpe *p, modtyp *mod);

static int setdval(ptpe *typ, ptpe *dflt, char **parm, modtyp *mod);
static void fix_mem(char **parm, ptpe *p);

extern int same(ptpe *typ, ptpe *dflt, char *parm, modtyp *mod);
extern int ismatch(ptpe *p, modtyp *mod, unsigned int cl, unsigned int tag);
extern int hasdata(PEPYPARM parm, ptpe *p, modtyp *mod, int *popt, int *optcnt);
extern ptpe *fdflt_b(ptpe *p);
extern ptpe *next_tpe(ptpe *p);

/*
 * decode the specified type of the specified module into the given
 * pe
 */
int
dec_f(int typ, modtyp *mod, PE pe, int explicitly, int *len, char **buf, char **parm)
{
    ptpe    *p;
    int     iflag;      /* are we called internally ? */

    if (typ < 0 || typ >= mod->md_nentries)
    {
        return (pepsylose (mod, NULL, NULL, "dec_f: Illegal typ %d", typ));
    }

    p = mod->md_dtab[typ];
    if (p->pe_type != PE_START)
    {
        return (pepsylose (mod, NULL, NULL, "dec_f: missing PE_START"));
    }

    p++;
    iflag = explicitly & F_CI;
    explicitly &= ~F_CI;
    if (!iflag)
    {
        *parm = NULL; /* initialise this for the MALLOCs that follow */
    }

    if (pr_obj(explicitly, pe, parm, p, mod) == NOTOK)
    {
        goto bad;
    }

    return (OK);

bad:
    return (NOTOK);
}

/*
 * Parse an object. The top level of an object does not have any
 * offset field which makes it different to pr_type routine which
 * must assume that it has an offset.
 */
static int
pr_obj(int expl, PE pe, char **parm, ptpe *p, modtyp *mod)
{
    int     cnt = 0;

    if (pe == NULL)
    {
        return pepsylose (mod, p, pe, "Empty PE structure");
    }

    while (p->pe_type != PE_END)
    {
        if (ISDTYPE(p) && expl && CHKTAG(mod, p, pe) == 0)
        {
            if (DEFAULT(p)) 
            {
                return pepsylose (mod, p, pe,
                                  "pr_obj:Default not implemented");
            }
            else if (POPTIONAL(p))
            {
                if (ALLOC_MEM(p, parm))
                {
                    fix_mem(parm, p);
                }
                goto next;
            }
            else
            {
                return pepsylose (mod, p, pe,
                                  "pr_obj:missing mandatory parameter");
            }
        }

        switch (p->pe_type)
        {
        case PE_END:
        case PE_START:
            return pepsylose (mod, p, pe, "pr_obj:illegal END/START");

        /*
         * This allows Functions to be called at the very end of the 
         * decoding -- With the decoded data - I hope - very messy
         */
        case UCODE:
            if (mod->md_ducode == NULL ||
                (*mod->md_ducode) (parm, pe, p, 0) == NOTOK)
            {
                goto bad;
            }
            break;


        default:
            if (pr_type(expl, pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;
        }

        if (ISDTYPE(p) && cnt > 0)
        {
            return pepsylose (mod, p, NULL, "pr_obj:compound type found");
        }
next:
        if (NEXT_TPE(p) == NULL)
        {
            goto bad;
        }
    }

    return (OK);

bad:
    return (NOTOK);
}

/*
 * Parse a single type. If a basic type parse it, if a compound type
 * call the appropriate parsing routine
 */
static int
pr_type(int expl, PE pe, char **parm, ptpe* p, modtyp* mod)
{
    int cnt = 0;
    int len;
    OID     oid;
    char    *nparm;

    /* there is no such pointer as &(*parm + p->pe_ucode) (ucode non zero) so
     * we fudge it by making a temporary one. As no memory needs to be
     * allocated through it this should work
     */

    if (pe == NULL)
    {
        return pepsylose (mod, p, pe, "Empty PE structure");
    }

    while (p->pe_type != PE_END)
    {
        if (ISDTYPE(p) && expl && CHKTAG(mod, p, pe) == 0)
        {
            if (DEFAULT(p))
            {
                if (setdval(p, FDFLT_B(p), parm, mod) == NOTOK)
                {
                    goto bad;
                }
                return (NO_DATA_USED);
            }
            else if (POPTIONAL(p))
            {
                if (ALLOC_MEM(p, parm))
                {
                    fix_mem(parm, p);
                }
                return (NO_DATA_USED);
            }
            else
            {
                return pepsylose (mod, p, pe,
                                  "pr_type:missing mandatory parameter");
            }
        }

        switch (p->pe_type)
        {
        case PE_END:
        case PE_START:
            return pepsylose (mod, p, pe, "pr_type:illegal END/START");

        case BOPTIONAL:
            if (CHKTAG(mod, p + 1, pe) == 0)
            {
                if (ALLOC_MEM(p, parm))
                {
                    fix_mem(parm, p);
                }
                if (IF_USELECT(p))
                {
                    if (p -> pe_ucode >= 0 &&
                        (mod -> md_ducode == NULL ||
                         (*mod->md_ducode)(parm, pe, p, 0) == NOTOK))
                    {
                        goto bad;
                    }
                }
                else
                {
                    CLR_OPT_PRESENT(p, parm);
                }
                return (NO_DATA_USED);
            }

            if (IF_USELECT(p))
            {
                if (p -> pe_ucode >= 0 &&
                    (mod -> md_ducode == NULL ||
                     (*mod->md_ducode)(parm, pe, p, 1) == NOTOK))
                {
                    goto bad;
                }
            }
            else
            {
                SET_OPT_PRESENT(p, parm);
            }
            p++;
            continue;

        case FREE_ONLY: /* the next entry(s) only for freeing routines 
                         * so skip this and next entry
                         */
            break;
        
        case UCODE:
            if (mod->md_ducode == NULL ||
                (*mod->md_ducode) (parm, pe, p, 0) == NOTOK)
            {
                goto bad;
            }
            break;

        case ETAG:
            switch (p->pe_ucode)
            {
            default:
                p++;
                if (pr_etype(pe->pe_cons, parm, p, mod) == NOTOK)
                {
                    return (NOTOK);
                }
            }
            break;

        case MEMALLOC:
            if (*parm)
            {
                break;  /* already allocated */
            }
            if ((*(parm) = (char *) calloc(1, (unsigned ) p->pe_tag)) == NULL)
            {
                return oom(mod, p);
            }
            break;

        /* The difference between here and the en_type makes me think
         * that this is never called for SEQ_START ???? 
         */
        case SSEQ_START:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_seq(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_seq(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SEQ_START:
            if (pr_seq(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SSEQOF_START:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_seqof(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_seqof(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SEQOF_START:
            if (pr_seqof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SSET_START:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_set(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_set(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SET_START:
            if (pr_set(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SSETOF_START:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_setof(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_setof(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SETOF_START:
            if (pr_setof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case IMP_OBJ:
            p++;
            if (p->pe_type == EXTOBJ)
            {
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *)0,
                      (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
                {
                      goto bad;
                }
            }
            else if (p->pe_type == SEXTOBJ)
            {
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *)0,
                          (char **) 0, (char **) &nparm) == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *)0,
                          (char **) 0, (char **) parm) == NOTOK)
                {
                    goto bad;
                }
            }
            else
            {
                if (p->pe_type == SOBJECT)
                {
                    if (p->pe_ucode > 0)
                    {
                        if (*parm == NULL)
                        {
                            return inpm(mod, p);
                        }
                        nparm = *parm + p->pe_ucode;
                        if (pr_obj(0, pe, &nparm, mod->md_dtab[p->pe_tag] + 1, mod)
                                == NOTOK)
                        {
                            goto bad;
                        }
                    }
                    else if (pr_obj(0, pe, parm, mod->md_dtab[p->pe_tag] + 1, mod)
                                == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (pr_obj(0, pe, (char **) (*parm + p->pe_ucode),
                        mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            break;

        case SOBJECT:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_obj(expl, pe, &nparm, mod->md_dtab[p->pe_tag] + 1, mod)==NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_obj(expl, pe, parm, mod->md_dtab[p->pe_tag] + 1, mod)==NOTOK)
            {
                goto bad;
            }
            break;

        case OBJECT:

            if (pr_obj(expl, pe, (char **) (*parm + p->pe_ucode),
               mod->md_dtab[p->pe_tag] + 1, mod)==NOTOK)
            {
                goto bad;
            }
            break;

        case SCHOICE_START:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_choice(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_choice(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case CHOICE_START:
            if (pr_choice(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SEXTOBJ:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                if (p[1].pe_type != EXTMOD)
                {
                    return pepsylose (mod, p, pe, "pr_type: missing EXTMOD");
                }
                nparm = *parm + p->pe_ucode;
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *)0,
                      (char **) 0, &nparm) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *)0,
                      (char **) 0, parm) == NOTOK)
            {
                goto bad;
            }
            break;

        case EXTOBJ:
            if (p[1].pe_type != EXTMOD)
            {
                return pepsylose (mod, p, pe, "pr_type: missing EXTMOD");
            }
            if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *)0,
                  (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
            {
                  goto bad;
            }
            break;

        case INTEGER:
            if (pe != NULL)
            {
                if (((*(integer *) (*parm + p->pe_ucode)) = prim2num(pe))
                    == NOTOK && pe->pe_errno != PE_ERR_NONE)
                {
                    return pepsylose (mod, p, pe, "pr_type:bad integer %s",
                                      pe_error(pe->pe_errno));
                }
            }
            break;

#ifdef  PEPSY_REALS
        case REALTYPE:
            if (pe != NULL)
            {
                if (((*(double *) (*parm + p->pe_ucode)) = prim2real(pe))
                    == NOTOK && pe->pe_errno != PE_ERR_NONE)
                {
                    return pepsylose (mod, p, pe, "pr_type:bad real %s",
                                      pe_error(pe->pe_errno));
                }
            }
            break;

#endif

        case BOOLEAN:
            if (pe != NULL)
            {
                int     i;

                if ((i = prim2flag (pe)) == NOTOK)
                {
                      return pepsylose (mod, p, pe, "pr_type:bad integer %s",
                                        pe_error(pe->pe_errno));
                }
                *(char *) (*parm + p->pe_ucode) = (char)(i & 0xff);
            }
            break;

        case ASN_NULL:
            break;

        case SANY:
            if (pe != NULL)
            {
                ((*(PE *) (parm + p->pe_ucode)) = pe)->pe_refcnt++;
                if (pe->pe_errno != PE_ERR_NONE)
                {
                    return pepsylose (mod, p, pe, "pr_type:bad ANY %s",
                                      pe_error(pe->pe_errno));
                }
            }
            break;

        case ANY:
            if (pe != NULL)
            {
                (*(PE *) (*parm + p->pe_ucode) = pe)->pe_refcnt++;
                if (pe->pe_errno != PE_ERR_NONE)
                {
                    return pepsylose(mod, p, pe, "pr_type:bad ANY %s",
                                     pe_error(pe->pe_errno));
                }
            }
            break;

        case SOCTETSTRING:
            if (pe != NULL)
            {
                if ((*((struct qbuf **) (parm + p->pe_ucode)) = prim2qb(pe)) ==
                    (struct qbuf *) NULL && pe->pe_errno != PE_ERR_NONE)
                {
                    return pepsylose(mod, p, pe, "pr_type:bad octet string %s",
                                     pe_error(pe->pe_errno));
                }
            }
            break;

        case OCTETSTRING:
            if (pe != NULL)
            {
                if ((*((struct qbuf **)(*parm + p->pe_ucode)) = prim2qb(pe)) ==
                    (struct qbuf *) NULL && pe->pe_errno != PE_ERR_NONE)
                {
                    return pepsylose (mod, p, pe,
                                      "pr_type:bad octet string %s",
                                      pe_error(pe->pe_errno));
                }
            }
            break;

        case T_STRING:
            if ((*((char **) (*parm + p->pe_ucode)) = prim2str(pe, &len))
                == NULL && pe->pe_errno != PE_ERR_NONE)
            {
                  return pepsylose (mod, p, pe, "pr_type:bad octet string %s",
                                  pe_error(pe->pe_errno));
            }
            /* undocumented feature of prim2str that it adds a NULL char
             * to the end of the string
             */
            break;

        case BITSTR_PTR:
            if (p[1].pe_type != BITSTR_LEN)
            {
                return pepsylose (mod, &p[1], NULL,
                                  "pr_type: missing BITSTR_PTR");
            }

            pe = prim2bit(pe);
            if ((*((char **) (*parm + p->pe_ucode)) =
                bitstr2strb(pe, (int *)(*parm + (p + 1)->pe_ucode)))
                == NULL && pe->pe_errno != PE_ERR_NONE)
            {
                  return pepsylose (mod, p, pe, "pr_type:bad bit string %s",
                                  pe_error(pe->pe_errno));
            }
            break;


        case OCTET_PTR:
            if (p[1].pe_type != OCTET_LEN)
            {
                return pepsylose (mod, &p[1], NULL,
                                  "pr_type: missing OCTET_PTR");
            }
            if ((*((char **) (*parm + p->pe_ucode)) =
                prim2str(pe, (int *)(*parm + (p + 1)->pe_ucode)))
                == NULL && pe->pe_errno != PE_ERR_NONE)
            {
                  return pepsylose (mod, p, pe, "pr_type:bad octet string %s",
                                    pe_error(pe->pe_errno));
            }
            break;


        case SBITSTRING:
            if (pe != NULL)
            {
                if ((*((PE *) (parm + p->pe_ucode)) =
                                  prim2bit(pe_cpy(pe))) == NULL)
                {
                    return pepsylose (mod, p, pe, "pr_type:out of memory");
                }
            }
            break;

        case BITSTRING:
            if (pe != NULL)
            {
                if ((*((PE *) (*parm + p->pe_ucode)) =
                     prim2bit(pe_cpy(pe))) == NULL)
                {
                    return pepsylose(mod, p, pe, "pr_type:out of memory");
                }
            }
            break;

        case SOBJID:
            oid = prim2oid(pe + p->pe_ucode);
            if ((*(OID *) parm = oid) == NULL)
            {
                return pepsylose (mod, p, pe,
                                  "pr_type:Object Identifier: out of memory");
            }
            break;

        case OBJID:
            oid = prim2oid(pe);
            if ((*(OID *) (*parm + p->pe_ucode) = oid) == NULL)
            {
                return pepsylose (mod, p, pe,
                                  "pr_type:Object Identifier: out of memory");
            }
            break;

        default:
            return pepsylose (mod, p, pe, "pr_type: type not implemented");
        }

        if (ISDTYPE(p) && cnt > 0)
        {
            return pepsylose (mod, p, pe, "pr_type:compound type found");
        }

        if (ISDTYPE(p) && pe != NULL)
        {
            return (OK);
        }
        if (NEXT_TPE(p) == NULL)
        {
            goto bad;
        }
    }

    return (OK);

bad:
    return (NOTOK);
}

/*
 * Parse a sequence, calling appropriate routines to parse each sub
 * type
 */
static int
pr_seq(PE head, char **parm, ptpe* p, modtyp* mod)
{
    PE      pe;
    int    *popt = NULL;        /* Pointer to optional field */
    int     optcnt = 0;         /* Number of optionals bits so far */
    char    *nparm;

    if (head == NULL)
    {
        return pepsylose (mod, p, head, "Empty PE structure");
    }

    if (p->pe_type != SEQ_START && p->pe_type != SSEQ_START)
    {
        return pepsylose (mod, p, head, "pr_seq: missing SEQ_START");
    }
    p++;

    if (p->pe_type == DFLT_B)
    {
        p++;
    }

    pe = first_member(head);
    while (p->pe_type != PE_END)
    {
        if (ISDTYPE(p) && POPTIONAL(p))
        {
            switch (p->pe_type)
            {
            case INTEGER:
            case REALTYPE:
            case BOOLEAN:
            case ASN_NULL:
            basictype:
                if (pe == NULL || CHKTAG(mod, p, pe) == 0)
                {
                    optcnt++;
                    goto next;
                }
                SETBIT(*popt, optcnt++);
                break;

            case ETAG:                  /* XXX ? optional things in seq's? */
                switch (p[1].pe_type)
                {
                case INTEGER:
                case REALTYPE:
                case BOOLEAN:
                case ASN_NULL:
                    goto basictype;
                }
                /* else fall through... */

            default:
                if (pe == NULL || CHKTAG(mod, p, pe) == 0)
                {
                    if (ALLOC_MEM(p, parm))
                        fix_mem(parm, p);
                    goto next;
                }
                break;
            }
        }
        else if (ISDTYPE(p) && (pe == NULL || CHKTAG(mod, p, pe) == 0))
        {
            if (DEFAULT(p))
            {
                if(setdval(p, FDFLT_B(p), parm, mod) == NOTOK)
                {
                    goto bad;
                }
                goto next;
            }
            else 
            {
                return pepsylose (mod, p, pe,
                                  "pr_seq:missing mandatory parameter");
            }
        }
        switch (p->pe_type)
        {
        case OPTL:
            popt = (int *) (*parm + p->pe_ucode);
            break;

        case FREE_ONLY: /* the next entry(s) only for freeing routines 
                         * so skip this and next entry
                         */
            break;
        
        case UCODE:
            if (mod->md_ducode == NULL ||
                (*mod->md_ducode) (parm, pe, p, 0) == NOTOK)
            {
                goto bad;
            }
            break;

        case BOPTIONAL:
            if (pe == NULL || CHKTAG(mod, p + 1, pe) == 0)
            {
                if (ALLOC_MEM(p, parm))
                {
                    fix_mem(parm, p);
                }
                if (IF_USELECT(p))
                {
                    if (p -> pe_ucode >= 0 &&
                        (mod -> md_ducode == NULL ||
                         (*mod->md_ducode)(parm, pe, p, 0) == NOTOK))
                    {
                        goto bad;
                    }
                }
                else
                {
                    CLR_OPT_PRESENT(p, parm);
                }
                goto next;
            }
            if (IF_USELECT(p))
            {
                if (p -> pe_ucode >= 0 &&
                    (mod -> md_ducode == NULL ||
                     (*mod->md_ducode)(parm, pe, p, 1) == NOTOK))
                {
                    goto bad;
                }
            }
            else
            {
                SET_OPT_PRESENT(p, parm);
            }
            p++;
            continue;

        case ETAG:
            if (pr_type(1, pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case MEMALLOC:
            if (*parm)
            {
                break;  /* already allocated */
            }
            if ((*(parm) = (char *) calloc(1, (unsigned ) p->pe_tag))==NULL)
            {
                return oom(mod, p);
            }
            break;

        case SEQ_START:
            if (pr_seq(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SEQOF_START:
            if (pr_seqof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SET_START:
            if (pr_set(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SETOF_START:
            if (pr_setof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case IMP_OBJ:
            p++;
            if (p->pe_type == EXTOBJ) 
            {
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *)0,
                      (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (p->pe_type == SEXTOBJ)
            {
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *)0,
                          (char **) 0, (char **) &nparm) == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *)0,
                          (char **) 0, (char **) parm) == NOTOK)
                {
                    goto bad;
                }
            }
            else
            {
                if (p->pe_type == SOBJECT)
                {
                    if (p->pe_ucode > 0)
                    {
                        if (*parm == NULL)
                        {
                            return inpm(mod, p);
                        }
                        nparm = *parm + p->pe_ucode;
                        if (pr_obj(0, pe, &nparm, mod->md_dtab[p->pe_tag] + 1, mod)
                                == NOTOK)
                        {
                            goto bad;
                        }
                    }
                    else if (pr_obj(0, pe, parm, mod->md_dtab[p->pe_tag] + 1, mod)
                             == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (pr_obj(0, pe, (char **) (*parm + p->pe_ucode),
                        mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            break;

        case SOBJECT:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_obj(1, pe, &nparm, mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_obj(1, pe, parm, mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case OBJECT:
            if (pr_obj(1, pe, (char **) (*parm + p->pe_ucode),
                    mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SCHOICE_START:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_choice(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_choice(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case CHOICE_START:
            if (pr_choice(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SEXTOBJ:
            if (p[1].pe_type != EXTMOD)
            {
                return pepsylose (mod, p, pe, "pr_seq: missing EXTMOD");
            }
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                      (char **) 0, &nparm) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                      (char **) 0, parm) == NOTOK)
            {
                goto bad;
            }
            break;

        case EXTOBJ:
            if (p[1].pe_type != EXTMOD)
            {
                return pepsylose (mod, p, pe, "pr_seq: missing EXTMOD");
            }

            if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                  (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
            {
                goto bad;
            }
            break;

        default:
            /* only called if we have a match */
            if (pr_type(1, pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;
        }

        if (ISDTYPE(p) && pe != NULL)
        {
            pe = next_member(head, pe);
        }
next:
        if (NEXT_TPE(p) == NULL)
        {
            goto bad;
        }
    }

    return (OK);

bad:
    return (NOTOK);
}


/*
 * Parse a set, calling appropriate routines to parse each sub type
 */
static int
pr_set(PE head, char **parm, ptpe* p, modtyp* mod)
{
    PE      pe = NULL;
    int    *popt = NULL;        /* Pointer to optional field */
    int     optcnt = 0;         /* Number of optionals bits so far */
    char    *nparm;

    if (p->pe_type != SET_START && p->pe_type != SSET_START)
    {
        return pepsylose (mod, p, NULL, "pr_seq: missing SET_START");
    }

    if (head == NULL)
    {
        return pepsylose (mod, p, head, "Empty PE structure");
    }
    p++;

    if (p->pe_type == DFLT_B)
    {
        p++;
    }

    while (p->pe_type != PE_END)
    {
        head -> pe_errno = PE_ERR_NONE;
        if (ISDTYPE(p) && POPTIONAL(p))
        {
            switch (p->pe_type)
            {
            case INTEGER:
            case REALTYPE:
            case BOOLEAN:
            case ASN_NULL:
                if ((pe = setpresent(head, p, mod)) != NULL)
                {
                    SETBIT(*popt, optcnt++);
                    break;
                }
                if (head -> pe_errno == PE_ERR_NONE)
                {
                    optcnt++;
                    goto next;
                }
                return pepsylose (mod, p, head, "Error in optional parameter");

            default:
                if ((pe = setpresent(head, p, mod)) != NULL)
                {
                    break;
                }

                if (head -> pe_errno == PE_ERR_NONE)
                {
                    if (ALLOC_MEM(p, parm))
                    {
                        fix_mem(parm, p);
                    }
                    goto next;
                }
                return pepsylose (mod, p, head, "Error in optional parameter");
            }
        }
        else if (ISDTYPE(p) && (pe = setpresent(head, p, mod)) == NULL)
        {
            if (head -> pe_errno == PE_ERR_NONE && DEFAULT(p))
            {
                if (setdval(p, FDFLT_B(p), parm, mod) == NOTOK)
                {
                    goto bad;
                }
                goto next;
            }
            else
            {
                return pepsylose (mod, p, head,
                                  "pr_set:missing mandatory parameter");
            }
        }
        switch (p->pe_type)
        {
        case OPTL:
            popt = (int *) (*parm + p->pe_ucode);
            break;

        case FREE_ONLY: /* the next entry(s) only for freeing routines 
                         * so skip this and next entry
                         */
            break;
        
        case UCODE:
            if (mod->md_ducode == NULL
            || (*mod->md_ducode) (parm, pe, p, 0) == NOTOK)
            {
                goto bad;
            }
            break;

        case BOPTIONAL:
            head -> pe_errno = PE_ERR_NONE;
            pe = setpresent(head, p + 1, mod);
            if (pe == NULL && head -> pe_errno != PE_ERR_NONE)
            {
                return pepsylose (mod, p, head, "error in optional");
            }
            if (pe == NULL)
            {
                if (ALLOC_MEM(p, parm))
                {
                    fix_mem(parm, p);
                }
                if (IF_USELECT(p))
                {
                    if (p -> pe_ucode >= 0 &&
                        (mod -> md_ducode == NULL ||
                        (*mod->md_ducode)(parm, pe, p, 0) == NOTOK))
                    {
                        goto bad;
                    }
                }
                else
                {
                    CLR_OPT_PRESENT(p, parm);
                }
                goto next;
            }
            if (IF_USELECT(p))
            {
                if (p -> pe_ucode >= 0 &&
                    (mod -> md_ducode == NULL ||
                     (*mod->md_ducode)(parm, pe, p, 1) == NOTOK))
                {
                    goto bad;
                }
            }
            else
            {
                SET_OPT_PRESENT(p, parm);
            }
            p++;
            continue;

        case ETAG:
            if (pr_type(1, pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case MEMALLOC:
            if (*parm)
            {
                break;  /* already allocated */
            }
            if ((*(parm) = (char *) calloc(1, (unsigned ) p->pe_tag))==NULL)
            {
                return oom(mod, p);
            }
            break;

        case SEQ_START:
            if (pr_seq(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SEQOF_START:
            if (pr_seqof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SET_START:
            if (pr_set(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SETOF_START:
            if (pr_setof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
                goto bad;
            break;

        case IMP_OBJ:
            p++;
            if (p->pe_type == EXTOBJ)
            {
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *) 0,
                      (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (p->pe_type == SEXTOBJ)
            {
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *) 0,
                          (char **) 0, (char **) &nparm) == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *) 0,
                          (char **) 0, (char **) parm) == NOTOK)
                {
                    goto bad;
                }
            }
            else
            {
                if (p->pe_type == SOBJECT)
                {
                    if (p->pe_ucode > 0)
                    {
                        if (*parm == NULL)
                        {
                            return inpm(mod, p);
                        }
                        nparm = *parm + p->pe_ucode;
                        if (pr_obj(0, pe, &nparm, mod->md_dtab[p->pe_tag] + 1, mod)
                                == NOTOK)
                        {
                            goto bad;
                        }
                    }
                    else if (pr_obj(0, pe, parm, mod->md_dtab[p->pe_tag] + 1, mod)
                                == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (pr_obj(0, pe, (char **) (*parm + p->pe_ucode),
                        mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            break;

        case SOBJECT:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_obj(1, pe, &nparm, mod->md_dtab[p->pe_tag] + 1, mod)== NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_obj(1, pe, parm, mod->md_dtab[p->pe_tag] + 1, mod)== NOTOK)
            {
                goto bad;
            }
            break;

        case OBJECT:
            if (pr_obj(1, pe, (char **) (*parm + p->pe_ucode),
                    mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SCHOICE_START:
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_choice(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (pr_choice(pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case CHOICE_START:
            if (pr_choice(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            {
                goto bad;
            }
            break;

        case SEXTOBJ:
            if (p[1].pe_type != EXTMOD)
            {
                return pepsylose (mod, p, pe, "pr_set: missing EXTMOD");
            }
            if (p->pe_ucode > 0)
            {
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                      (char **) 0, &nparm) == NOTOK)
                {
                    goto bad;
                }
            }
            else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                      (char **) 0, parm) == NOTOK)
            {
                goto bad;
            }
            break;

        case EXTOBJ:
            if (p[1].pe_type != EXTMOD) 
            {
                return pepsylose (mod, p, pe, "pr_set: missing EXTMOD");
            }

            if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                  (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
            {
                goto bad;
            }
            break;

        default:
            if (pr_type(1, pe, parm, p, mod) == NOTOK)
            {
                goto bad;
            }
            break;
        }

next:
        if (NEXT_TPE(p) == NULL)
        {
            goto bad;
        }
    }

    return (OK);

bad:
    return (NOTOK);

}


/*
 * Parse a sequence of calling appropriate routines to parse each sub
 * type
 */
static int
pr_seqof(PE head, char **parm, ptpe* p, modtyp* mod)
{
    PE      pe;
    ptpe    *start;             /* first entry in list */
    int     dflt = 0;
    char    *nparm;

    if (p->pe_type != SEQOF_START && p->pe_type != SSEQOF_START)
    {
        return pepsylose (mod, p, head, "pr_seqof:missing SEQOF_START");
    }

    if (head == NULL)
    {
        return pepsylose (mod, p, head, "Empty PE structure");
    }
    p++;

    if (p->pe_type == DFLT_B)
    {
        p++;
    }

    start = p;

    pe = first_member(head);
    while (pe != NULL)
    {
        while (p->pe_type != PE_END)
        {
            if (ISDTYPE(p) && CHKTAG(mod, p, pe) == 0)
            {
                if (DEFAULT(p))
                {
                    if (setdval(p, FDFLT_B(p), parm, mod) == NOTOK)
                    {
                        goto bad;
                    }
                    goto next;
                }
                else if (POPTIONAL(p))
                {
                    if (ALLOC_MEM(p, parm))
                    {
                        fix_mem(parm, p);
                    }
                    goto next;
                }
                else
                {
                    return pepsylose (mod, p, pe,
                                      "pr_seqof:missing mandatory parameter");
                }
            }
            switch (p->pe_type)
            {
            case FREE_ONLY:     /* the next entry(s) only for freeing routines 
                             * so skip this and next entry
                             */
                break;
            
            case UCODE:
                if (mod->md_ducode == NULL ||
                    (*mod->md_ducode) (parm, pe, p, 0) == NOTOK)
                {
                    goto bad;
                }
                break;

            case BOPTIONAL:
                if (pe == NULL || CHKTAG(mod, p + 1, pe) == 0)
                {
                    if (ALLOC_MEM(p, parm))
                    {
                        fix_mem(parm, p);
                    }
                    if (IF_USELECT(p))
                    {
                        if (p -> pe_ucode >= 0 &&
                            (mod -> md_ducode == NULL ||
                             (*mod->md_ducode)(parm, pe, p, 0) == NOTOK))
                        {
                            goto bad;
                        }
                    }
                    else
                    {
                        CLR_OPT_PRESENT(p, parm);
                    }
                    goto next;
                }
                if (IF_USELECT(p))
                {
                    if (p -> pe_ucode >= 0 &&
                        (mod -> md_ducode == NULL ||
                         (*mod->md_ducode)(parm, pe, p, 1) == NOTOK))
                    {
                        goto bad;
                    }
                }
                else
                {
                    SET_OPT_PRESENT(p, parm);
                }
                p++;
                continue;

            case ETAG:
                if (pr_type(1, pe, parm, p, mod) == NOTOK)
                {
                    goto bad;
                }
                break;

            case MEMALLOC:
                if (*parm)
                {
                    break;      /* already allocated */
                }
                if ((*(parm) = (char *) calloc(1, (unsigned ) p->pe_tag))
                        == NULL)
                {
                    return oom(mod, p);
                }
                break;

            case SCTRL:
                parm = (char **) ((char *) *parm + p->pe_ucode);
                break;

            case SEQ_START:
                if (pr_seq(pe, (char **) (*parm + p->pe_ucode), p, mod) ==NOTOK)
                {
                    goto bad;
                }
                break;

            case SEQOF_START:
                if (pr_seqof(pe, (char **) (*parm + p->pe_ucode), p,mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case SET_START:
                if (pr_set(pe, (char **) (*parm + p->pe_ucode), p, mod) ==NOTOK)
                {
                    goto bad;
                }
                break;

            case SETOF_START:
                if (pr_setof(pe, (char **)(*parm + p->pe_ucode), p, mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case SOBJECT:
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (pr_obj(1,pe, &nparm, mod->md_dtab[p->pe_tag]+1, mod)==NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (pr_obj(1,pe, parm, mod->md_dtab[p->pe_tag]+1, mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case OBJECT:
                if (pr_obj(1, pe, (char **) (*parm + p->pe_ucode),
                        mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                {
                    goto bad;
                }
                break;

            case SCHOICE_START:
                if (*parm == NULL)
                {
                    return inpm(mod, p);
                }
                nparm = *parm + p->pe_ucode;
                if (pr_choice(pe, &nparm, p, mod) == NOTOK)
                {
                    goto bad;
                }
                break;

            case CHOICE_START:
                if (pr_choice(pe, (char **)(*parm + p->pe_ucode), p,mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case SEXTOBJ:
                if (p[1].pe_type != EXTMOD)
                {
                    return pepsylose (mod, p, pe, "pr_seqof: missing EXTMOD");
                }
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                          (char **) 0, &nparm) == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                          (char **) 0, parm) == NOTOK)
                {
                    goto bad;
                }
                break;

            case EXTOBJ:
                if (p[1].pe_type != EXTMOD) 
                {
                    return pepsylose (mod, p, pe, "pr_seqof: missing EXTMOD");
                }

                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                      (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
                {
                    goto bad;
                }
                break;

            default:
                if (pr_type(1, pe, parm, p, mod) == NOTOK)
                {
                    goto bad;
                }
                break;
            }

            if (ISDTYPE(p) && dflt == 0)
            {
                pe = next_member(head, pe);
            }
next:
            if (NEXT_TPE(p) == NULL)
            {
                goto bad;
            }
        }
        parm = (char **) (*parm + p->pe_ucode);
        p = start;
    }

    return (OK);

bad:
    return (NOTOK);
}

/*
 * Parse a setof, calling appropriate routines to parse each sub type
 */
static int
pr_setof(PE head, char **parm, ptpe* p, modtyp* mod)
{
    PE      pe;
    ptpe    *start;
    char    *nparm;

    if (p->pe_type != SETOF_START && p->pe_type != SSETOF_START)
    {
        return pepsylose(mod, p, head, "pr_setof: missing SETOF_START");
    }
    if (head == NULL)
    {
        return pepsylose (mod, p, head, "Empty PE structure");
    }
    p++;

    if (p->pe_type == DFLT_B)
    {
        p++;
    }

    start = p;
    pe = first_member(head);

    for (pe = first_member(head); pe; pe = next_member(head, pe))
    {
        while (p->pe_type != PE_END)
        {
            if (pe == NULL || CHKTAG(mod, p, pe) == 0)
            {
                if (DEFAULT(p))
                {
                    if (setdval(p, FDFLT_B(p), parm, mod) == NOTOK)
                    {
                        goto bad;
                    }
                    goto next;
                }
                else
                {
                    return pepsylose (mod, p, pe,
                                      "pr_setof:missing mandatory parameter");
                }
            }

            switch (p->pe_type)
            {
            case FREE_ONLY:     /* the next entry(s) only for freeing routines 
                             * so skip this and next entry
                             */
                break;
            
            case UCODE:
                if (mod->md_ducode == NULL
                || (*mod->md_ducode) (parm, pe, p, 0) == NOTOK)
                {
                    goto bad;
                }
                break;

            case BOPTIONAL:
                if ((pe = setpresent(head, p + 1, mod)) == NULL)
                {
                    if (ALLOC_MEM(p, parm))
                    {
                        fix_mem(parm, p);
                    }
                    if (IF_USELECT(p))
                    {
                        if (p -> pe_ucode >= 0 &&
                            (mod -> md_ducode == NULL ||
                             (*mod->md_ducode)(parm, pe, p, 0) == NOTOK))
                        {
                            goto bad;
                        }
                    }
                    else
                    {
                        CLR_OPT_PRESENT(p, parm);
                    }
                    goto next;
                }
                if (IF_USELECT(p))
                {
                    if (p -> pe_ucode >= 0 &&
                        (mod -> md_ducode == NULL ||
                         (*mod->md_ducode)(parm, pe, p, 1) == NOTOK))
                    {
                        goto bad;
                    }
                }
                else
                {
                    SET_OPT_PRESENT(p, parm);
                }
                p++;
                continue;

            case ETAG:
                if (pr_type(1, pe->pe_cons, parm, p, mod) == NOTOK)
                {
                    goto bad;
                }
                break;

            case MEMALLOC:
                if (*parm)
                {
                    break;      /* already allocated */
                }
                if ((*(parm) = (char *) calloc(1, (unsigned )p->pe_tag))
                        == NULL)
                {
                    return oom(mod, p);
                }
                break;

            case SCTRL:
                parm = (char **) (*parm + p->pe_ucode);
                break;

            case SEQ_START:
                if (pr_seq(pe, (char **) (*parm + p->pe_ucode), p, mod) ==NOTOK)
                {
                    goto bad;
                }
                break;

            case SEQOF_START:
                if (pr_seqof(pe, (char **)(*parm + p->pe_ucode), p, mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case SET_START:
                if (pr_set(pe, (char **) (*parm + p->pe_ucode), p, mod) ==NOTOK)
                {
                    goto bad;
                }
                break;

            case SETOF_START:
                if (pr_setof(pe, (char **)(*parm + p->pe_ucode), p, mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case SOBJECT:
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (pr_obj(1, pe, &nparm, mod->md_dtab[p->pe_tag]+1, mod)==NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (pr_obj(1, pe, parm, mod->md_dtab[p->pe_tag]+1, mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case OBJECT:
                if (pr_obj(1, pe, (char **) (*parm + p->pe_ucode),
                        mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                {
                    goto bad;
                }
                break;

            case SCHOICE_START:
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (pr_choice(pe, &nparm, p, mod) == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (pr_choice(pe, parm, p, mod) == NOTOK)
                {
                    goto bad;
                }
                break;

            case CHOICE_START:
                if (pr_choice(pe, (char **)(*parm + p->pe_ucode), p,mod)==NOTOK)
                {
                    goto bad;
                }
                break;

            case SEXTOBJ:
                if (p[1].pe_type != EXTMOD)
                {
                    return pepsylose (mod, p, pe, "pr_setof: missing EXTMOD");
                }
                if (p->pe_ucode > 0)
                {
                    if (*parm == NULL)
                    {
                        return inpm(mod, p);
                    }
                    nparm = *parm + p->pe_ucode;
                    if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI,
                          (int *) 0, (char **) 0, &nparm) == NOTOK)
                    {
                        goto bad;
                    }
                }
                else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI,
                          (int *) 0, (char **) 0, parm) == NOTOK)
                {
                    goto bad;
                }
                break;

            case EXTOBJ:
                if (p[1].pe_type != EXTMOD)
                {
                    return pepsylose (mod, p, pe, "pr_setof: missing EXTMOD");
                }
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI,
                      (int *) 0, (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
                {
                    goto bad;
                }
                break;

            default:
                if (pr_type(1, pe, parm, p, mod) == NOTOK)
                {
                    goto bad;
                }
                break;
            }

    next:
            if (NEXT_TPE(p) == NULL)
            {
                goto bad;
            }
        }
        parm = (char **) (*parm + p->pe_ucode);
        p = start;
    }

    return (OK);

bad:
    return (NOTOK);
}

/*
 * parse a choice field. This means find which choice is taken
 */
static int
pr_choice(PE head, char **parm, ptpe *p, modtyp *mod)
{
    int    *poffset = NULL;
    int     cnt;
    ptpe    *savep = NULL;

    if (p->pe_type != CHOICE_START && p->pe_type != SCHOICE_START)
        return pepsylose (mod, p, head, "pr_choice:missing CHOICE_START");

    if (head == NULL)
        return pepsylose (mod, p, head, "Empty PE structure");
    p++;

    if (p->pe_type == DFLT_B)
        p++;

    if (p->pe_type == MEMALLOC) {
            if (*parm == NULL) {
                /* not already allocated */
                if ((*(parm) = (char *) calloc(1,(unsigned )p->pe_tag))==NULL)
                    return oom(mod, p);
            }
        p++;
    }
    if (p->pe_type == SCTRL) {
        if (IF_USELECT(p)) {
            savep = p;
        } else if ((poffset = (int *) (*parm + p->pe_ucode)) == NULL)
            goto bad;
        p++;
    }
    for (cnt = 1; p->pe_type != PE_END; NEXT_TPE(p)) {
        if (ISDTYPE(p)) {
            if (ismatch(p, mod, head->pe_class, head->pe_id)) {
                if (!savep && poffset)
                    *poffset = cnt;
                if (pr_etype(head, parm, p, mod) == NOTOK)
                    goto bad;
                if (savep) {
                    if (savep -> pe_ucode >= 0  &&
                        (mod -> md_ducode == NULL ||
                         (*mod -> md_ducode)(parm, head, savep, cnt) == NOTOK))
                        goto bad;
                }
                NEXT_TPE(p);
                if (p->pe_type == UCODE) {
                    if (mod->md_ducode == NULL
                    || (*mod->md_ducode) (parm, head, p, 0) == NOTOK)
                        return (NOTOK);
                }
                return (OK);
            }
            cnt++;
        }
    }
    (void) pepsylose(mod, p, head, "pr_choice: no choice taken");
bad:
    return (NOTOK);
}

/*
 * Parse a single type for explicit tag If a basic type parse it, if
 * a compound type call the appropriate parsing routine
 */
static int
pr_etype(PE pe, char **parm, ptpe *p, modtyp *mod)
{
    int cnt;
    char    *nparm;

    if (pe == NULL)
        return pepsylose (mod, p, pe, "Empty PE structure");
    switch (p->pe_type) {
    case PE_END:
    case PE_START:
        return pepsylose (mod, p, pe, "pr_etype:illegal END/START");

    case FREE_ONLY:     /* the next entry(s) only for freeing routines 
                     * so skip this and next entry
                     */
        break;
    
    case UCODE:
        if (mod->md_ducode == NULL
            || (*mod->md_ducode) (parm, pe, p, 0) == NOTOK)
            goto bad;
        break;

    case BOPTIONAL:
        return pepsylose (mod, p, pe, "pr_etype:illegal BOPTIONAL");
        
    case ETAG:
        switch (p->pe_ucode) {

        default:
            p++;
            if (pr_etype(pe->pe_cons, parm, p, mod) == NOTOK)
                goto bad;
        }
        break;

    case MEMALLOC:
        if (*parm)
            break;      /* already allocated */
        if ((*(parm) = (char *) calloc(1, (unsigned ) p->pe_tag)) == NULL)
            return oom(mod, p);
        break;

    case SEQ_START:
        if (pr_seq(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            goto bad;
        break;

    case SSEQOF_START:
        if (p->pe_ucode > 0) {
            if (*parm == NULL)
                return inpm(mod, p);
            nparm = *parm + p->pe_ucode;
            if (pr_seqof(pe, &nparm, p, mod) == NOTOK)
                goto bad;
        } else if (pr_seqof(pe, parm, p, mod) == NOTOK)
                goto bad;
        break;

    case SEQOF_START:
        if (pr_seqof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            goto bad;
        break;

    case SSEQ_START:
        if (p->pe_ucode > 0) {
            if (*parm == NULL)
                return inpm(mod, p);
            nparm = *parm + p->pe_ucode;
            if (pr_seq(pe, &nparm, p, mod) == NOTOK)
                goto bad;
        } else if (pr_seq(pe, parm, p, mod) == NOTOK)
                goto bad;
        break;

    case SET_START:
        if (pr_set(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            goto bad;
        break;

    case SSET_START:
        if (p->pe_ucode > 0) {
            if (*parm == NULL)
                return inpm(mod, p);
            nparm = *parm + p->pe_ucode;
            if (pr_set(pe, &nparm, p, mod) == NOTOK)
                goto bad;
        } else if (pr_set(pe, parm, p, mod) == NOTOK)
            goto bad;
        break;

    case SETOF_START:
        if (pr_setof(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            goto bad;
        break;

    case SSETOF_START:
        if (p->pe_ucode > 0) {
            if (*parm == NULL)
                return inpm(mod, p);
            nparm = *parm + p->pe_ucode;
            if (pr_setof(pe, &nparm, p, mod) == NOTOK)
                goto bad;
        } else if (pr_setof(pe, parm, p, mod) == NOTOK)
            goto bad;
        break;

    case IMP_OBJ:
        p++;
        if (p->pe_type == EXTOBJ) {
            if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *) 0,
                  (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
                  goto bad;
        } else if (p->pe_type == SEXTOBJ) {
            if (p->pe_ucode > 0) {
                if (*parm == NULL)
                    return inpm(mod, p);
                nparm = *parm + p->pe_ucode;
                if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *) 0,
                      (char **) 0, (char **) &nparm) == NOTOK)
                      goto bad;
            } else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 0|F_CI, (int *) 0,
                      (char **) 0, (char **) parm) == NOTOK)
                      goto bad;
        } else {
            if (p->pe_type == SOBJECT) {
                if (p->pe_ucode > 0) {
                    if (*parm == NULL)
                        return inpm(mod, p);
                    nparm = *parm + p->pe_ucode;
                    if (pr_obj(0, pe, (char **)&nparm, mod->md_dtab[p->pe_tag]+1, mod)==NOTOK)
                        goto bad;
                } else if (pr_obj(0, pe, (char **)parm, mod->md_dtab[p->pe_tag]+1, mod)==NOTOK)
                        goto bad;
            } else if (pr_obj(0, pe, (char **) (*parm + p->pe_ucode),
                    mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                goto bad;
        }
        break;

    case SOBJECT:
        if (p->pe_ucode > 0) {
            if (*parm == NULL)
                return inpm(mod, p);
            nparm = *parm + p->pe_ucode;
            if (pr_obj(1, pe, &nparm, mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
                goto bad;
        } else if (pr_obj(1, pe, parm, mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
            goto bad;
        break;

    case OBJECT:
        if (pr_obj(1, pe, (char **) (*parm + p->pe_ucode),
                mod->md_dtab[p->pe_tag] + 1, mod) == NOTOK)
            goto bad;
        break;

    case SCHOICE_START:
        if (p->pe_ucode > 0) {
            if (*parm == NULL)
                return inpm(mod, p);
            nparm = *parm + p->pe_ucode;
            if (pr_choice(pe, &nparm, p, mod) == NOTOK)
                goto bad;
        } else if (pr_choice(pe, parm, p, mod) == NOTOK)
            goto bad;
        break;

    case CHOICE_START:
        if (pr_choice(pe, (char **) (*parm + p->pe_ucode), p, mod) == NOTOK)
            goto bad;
        break;

    case SEXTOBJ:
        if (p[1].pe_type != EXTMOD)
            return pepsylose (mod, p, pe, "pr_etype: missing EXTMOD");
        if (p->pe_ucode > 0) {
            if (*parm == NULL)
                return inpm(mod, p);
            nparm = *parm + p->pe_ucode;
            if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                  (char **) 0, &nparm) == NOTOK)
                  goto bad;
        } else if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
                  (char **) 0, parm) == NOTOK)
              goto bad;
        break;

    case EXTOBJ:
        if (p[1].pe_type != EXTMOD)
            return pepsylose (mod, p, pe, "pr_etype: missing EXTMOD");

        if (dec_f(p->pe_tag, EXT2MOD(mod, (p + 1)), pe, 1|F_CI, (int *) 0,
              (char **) 0, (char **) (*parm + p->pe_ucode)) == NOTOK)
              goto bad;
        break;

    case INTEGER:
        if (pe != NULL)
        {
            if (((*(integer *)(*parm + p->pe_ucode)) = prim2num(pe)) == NOTOK &&
                pe->pe_errno != PE_ERR_NONE) 
                return pepsylose (mod, p, pe, "pr_etype:bad integer %s",
                                  pe_error(pe->pe_errno));
        }
        break;

#ifdef  PEPSY_REALS
    case REALTYPE:
        if (pe != NULL) {
            if (((*(double *) (*parm + p->pe_ucode)) = prim2real(pe))
                == NOTOK && pe->pe_errno != PE_ERR_NONE) 
                  return pepsylose (mod, p, pe, "pr_etype:bad real %s",
                                    pe_error(pe->pe_errno));
        }
        break;

#endif

    case BOOLEAN:
        if (pe != NULL) {
            int     i;

            if ((i = prim2flag (pe)) == NOTOK)
                return pepsylose (mod, p, pe, "pr_etype:bad integer %s",
                                  pe_error(pe->pe_errno));
            (*(char *) (*parm + p->pe_ucode)) = (char)(i & 0xff);
        }
        break;

    case ASN_NULL:
        break;

    case ANY:
        if (pe != NULL) {
            (*(PE *) (*parm + p->pe_ucode) = pe)->pe_refcnt++;
            if (pe->pe_errno != PE_ERR_NONE)
                return pepsylose (mod, p, pe, "pr_etype:bad ANY %s",
                                  pe_error(pe->pe_errno));
        }
        break;

    case SANY:
        if (pe != NULL) {
            (*(PE *) (parm + p->pe_ucode) = pe) -> pe_refcnt++;
            if (pe->pe_errno != PE_ERR_NONE)
                return pepsylose (mod, p, pe, "pr_etype:bad ANY %s",
                                  pe_error(pe->pe_errno));
        }
        break;

    case SOCTETSTRING:
        if (pe != NULL) {
            if ((*((struct qbuf **) (parm + p->pe_ucode))
                 = prim2qb(pe)) == (struct qbuf *) NULL
                && pe->pe_errno != PE_ERR_NONE)
                return pepsylose (mod, p, pe, "pr_etype:bad octet string %s",
                                  pe_error(pe->pe_errno));
        }
        break;

    case OCTETSTRING:
        if (pe != NULL) {
            if ((*((struct qbuf **) (*parm + p->pe_ucode))
                 = prim2qb(pe)) == (struct qbuf *) NULL
                && pe->pe_errno != PE_ERR_NONE)
                return pepsylose (mod, p, pe, "pr_etype:bad octet string %s",
                                  pe_error(pe->pe_errno));
        }
        break;

    case T_STRING:
        if ((*((char **) (*parm + p->pe_ucode)) = prim2str(pe, &cnt))
            == NULL && pe->pe_errno != PE_ERR_NONE)
              return pepsylose (mod, p, pe, "pr_type:bad octet string %s",
                              pe_error(pe->pe_errno));
        /* undocumented feature of prim2str that it adds a NULL char
         * to the end of the string
         */
        break;

    case OCTET_PTR:
        if (p[1].pe_type != OCTET_LEN)
            return pepsylose (mod, &p[1], NULL, "pr_etype: missing OCTET_PTR");
        if ((*((char **) (*parm + p->pe_ucode)) =
            prim2str(pe, (int *)(*parm + (p + 1)->pe_ucode)))
            == NULL && pe->pe_errno != PE_ERR_NONE)
              return pepsylose (mod, p, pe, "pr_etype:bad octet string %s",
                              pe_error(pe->pe_errno));
        break;

        case BITSTR_PTR:
            if (p[1].pe_type != BITSTR_LEN)
                return pepsylose (mod, &p[1], NULL,
                                  "pr_etype: missing BITSTR_PTR");
            pe = prim2bit(pe);
            if ((*((char **) (*parm + p->pe_ucode)) =
                bitstr2strb(pe, (int *)(*parm + (p + 1)->pe_ucode)))
                == NULL && pe->pe_errno != PE_ERR_NONE)
                  return pepsylose (mod, p, pe, "pr_etype:bad bit string %s",
                                  pe_error(pe->pe_errno));
            break;

    case SBITSTRING:
        if (pe != NULL) {
            if (((*(PE *) (parm + p->pe_ucode)) = prim2bit(pe_cpy(pe))) == NULL)
                return pepsylose (mod, p, pe, "pr_etype:out of memory");
        }
        break;

    case BITSTRING:
        if (pe != NULL) {
            if ((*((PE *) (*parm + p->pe_ucode)) = prim2bit(pe_cpy(pe))) == NULL)
                return pepsylose (mod, p, pe, "pr_etype:out of memory");
        }
        break;

    case SOBJID:
        if ((*(OID *) (parm + p->pe_ucode) = prim2oid(pe)) == NULL)
            return pepsylose (mod, p, pe, "pr_etype:OID: out of memory");
        break;

    case OBJID:
        if ((*(OID *) (*parm + p->pe_ucode) = prim2oid(pe)) == NULL)
            return pepsylose (mod, p, pe, "en_etype:OID: out of memory");
        break;

    default:
        return pepsylose(mod, p, pe,
                         "pr_etype: %d not implemented", p->pe_type);
    }

    return (OK);
bad:
    return (NOTOK);
}


/*
 * determine if the given field is present in the data This is simple
 * if the field is a simple type with an obvious tag but in the case
 * of an object or a CHOICE type the tag is not obvious. If the
 * object is a CHOICE there are more than one possible tag that could
 * match and in this case we must try to match each one of them.
 */
static PE
setpresent(PE head, ptpe *p, modtyp *mod)
{
    PE      pe;
    modtyp      *nmod;

    while (!ISDTYPE(p) && p->pe_type != PE_END) {
        p++;
    }
    if (!ISDTYPE(p) || p->pe_type == PE_END)
        return (NULL);

    switch (p->pe_type) {
    case EXTOBJ:
    case SEXTOBJ:
        /* Needs to be changed for optional and default */
        nmod = EXT2MOD(mod, (p + 1));
        return (setpresent(head, p = nmod->md_dtab[p->pe_tag] + 1, nmod));

    case OBJECT:
    case SOBJECT:
        /* Needs to be changed for optional and default */
        return (setpresent(head, p = mod->md_dtab[p->pe_tag] + 1, mod));

    case SCHOICE_START:
    case CHOICE_START:
        for (p++; p && p->pe_type != PE_END; NEXT_TPE(p)) {
            if (!ISDTYPE(p))
                continue;
            if ((pe = setpresent(head, p, mod)))
                return (pe);
        }
        return (NULL);

    default:
        return (set_find(head, CLASS(p), TAG(p)));
    }
}

/*
 * set the default value to that value in the structure
 */
static int
setdval(ptpe *typ, ptpe *dflt, char **parm, modtyp *mod)
{
    char        *p;
    integer     i;
    int         no;     /* number of octets */
    char        *nparm;

again:
    switch (typ->pe_type) {
    case MEMALLOC:
        if (*parm)
            break;      /* already allocated */

        if ((*(parm) = (char *) calloc(1, (unsigned ) typ->pe_tag)) == NULL) {
            (void) pepsylose (mod, typ, NULL,
                              "setdval:calloc failed on %d", typ->pe_tag);
            return NOTOK;
        }
        /* fall through and do the same stuff as for ETAG */
        
    case ETAG:
        typ++;
        goto again;

    case INTEGER:
        *(integer *) (*parm + typ->pe_ucode) = IVAL(mod, dflt);
        break;

#ifdef  PEPSY_REALS
    case REALTYPE:
        *(double *) (*parm + typ->pe_ucode) = RVAL(mod, dflt);
        break;
#endif

    case BOOLEAN:
        *(char *) (*parm + typ->pe_ucode) = (char)IVAL(mod, dflt);
        break;

    case ASN_NULL:
        /* Only one value */
        break;

    case SBITSTRING:
        *(PE *) (parm + typ->pe_ucode) = strb2bitstr(PVAL(mod, dflt), (int )IVAL(mod, dflt), 0, 0);
        break;

    case BITSTRING:
        *(PE *) (*parm + typ->pe_ucode) =
           strb2bitstr(PVAL(mod, dflt), (int )IVAL(mod, dflt), 0, 0);
        break;

    case SOCTETSTRING:
        *(struct qbuf **) (parm + typ->pe_ucode) = str2qb(PVAL(mod, dflt),
            (int )IVAL(mod, dflt), 1);
        break;

    case OCTETSTRING:
        *(struct qbuf **) (*parm + typ->pe_ucode) =
           str2qb(PVAL(mod, dflt), (int )IVAL(mod, dflt), 1);
        break;

    case T_STRING:
        *(char **) (*parm + typ->pe_ucode) = strdup(PVAL(mod, dflt));
        break;

    case OCTET_PTR:
        if (typ[1].pe_type != OCTET_LEN)
            return pepsylose (mod, typ, NULL, "setdval:missing OCTET_LEN");
        i = IVAL(mod, dflt);
        p = smalloc((int )i + 1);
        memcpy(p, PVAL(mod, dflt), (int )i);
        p[i] = '\0';
        *(char **) (*parm + typ->pe_ucode) = p;
        *(int *) (*parm + (typ + 1)->pe_ucode) = i;
        break;

    case BITSTR_PTR:
        if (typ[1].pe_type != BITSTR_LEN)
            return pepsylose (mod, typ, NULL, "setdval:missing BITSTR_LEN");
        i = IVAL(mod, dflt);
        no = (i + 7)/8; /* round up */
        p = smalloc(no + 1);
        memcpy(p, PVAL(mod, dflt), no);
        p[no] = '\0';
        *(char **) (*parm + typ->pe_ucode) = p;
        *(int *) (*parm + (typ + 1)->pe_ucode) = i;
        break;

    case OBJECT:
        if (setdval(mod->md_dtab[typ->pe_tag] + 1, dflt,
                    (char **) (*parm + typ->pe_ucode), mod) == NOTOK)
            return NOTOK;
        break;

    case SOBJECT:
        if (typ->pe_ucode > 0) {
            nparm = *parm + typ->pe_ucode;
            if (setdval(mod->md_dtab[typ->pe_tag] + 1, dflt, &nparm, mod) == NOTOK)
                return NOTOK;
        } else if (setdval(mod->md_dtab[typ->pe_tag] + 1, dflt, parm, mod) == NOTOK)
                return NOTOK;
        break;

    case IMP_OBJ:
        typ++;

    case ANY:
    case SANY:
    case SEXTOBJ:
    case EXTOBJ:
    case OBJID:
    case SOBJID:
    case SEQ_START:
    case SET_START:
    case -1:                    /* Just use the pepy method of null
                                 * pointers */
        /*
         * This is the posy/pepy hack way of doing things at the
         * moment
         */
        *(char **) (*parm + typ->pe_ucode) = NULL;
        break;

    default:
        /*
         * dmp_tpe("setdval: type not implemented", typ, mod); - need
         * mod
         */
        (void) pepsylose(mod, typ, NULL,
                         "setdval: %d not implemented", typ->pe_type);
        return NOTOK;
    }
    return OK;
}
/*
 * fix up the allocation of memory. We have allocated memory for an
 * optional object that is not present. ISODE routines get upset if
 * this is present because it then believes the object is present and
 * tries to process it ...
 */
static void
fix_mem(char **parm, ptpe *p)
{
    if (p->pe_type != SOBJECT || p[-1].pe_type != MEMALLOC
        || p[1].pe_type != PE_END)
    {
    }
    else if (*parm)
    {
        free(*parm);
    }
    *parm = NULL;
}

/****************************************************************************
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

