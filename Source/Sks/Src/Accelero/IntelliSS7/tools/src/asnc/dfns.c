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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:39  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:18  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:07  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:17  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:30  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:19  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:22  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.2  2001/03/06 15:59:50  mmiers
 * LOG: Versioning.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:07:18  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:30:00  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.2  1999/04/09 21:30:41  mmiers
 * LOG:
 * LOG:
 * LOG: Remove all 218 warnings.
 * LOG:
 * LOG: Revision 1.1  1998/10/16 22:36:57  jpakrasi
 * LOG: Build pepsy on NT.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:20  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

/*.implementation:extern (or static)
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "asncomp.h"
#include "table.h"
#include "pass2.h"

#ident "$Id: dfns.c,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $"

id_entry *id_table[TABLESIZE];

#define my_error(mesg)        (fprintf(stderr, "%s\n",mesg),exit(1))

extern char *notidtoid(char *s);
extern char *my_new_str(char *s);
extern char *my_strcat(char *s1, char *s2);
extern char *proc_name(char *t, int flag);

extern void ferr(int, char *);
extern void ferrs(int, char *, char *);

extern char *mymodule;

int hash_val(char *s);

/*
 * Lookup the hash table (id_table) for the string t and insert it at
 * the start of the appropriate chain if it is not already there.
 * The argument flag indicates whether t is being defined (1) or used
 * (0).
 */
char*
proc_name(char *t, int flag)
{
    int i;
    static int curr = 0;
    id_entry *ptr;

    i = hash_val(t);
    for (ptr = id_table[i];
	 ptr != NULL && strcmp(t, ptr->h_value);
	 ptr = ptr->next)
    {
    }

    if (ptr == NULL)
    {
	if ((ptr = (id_entry *) malloc(sizeof(id_entry))) == NULL)
	{
	    my_error("proc_name: Out of memory");
	}

	ptr->h_value = t;
	ptr->r_value = my_strcat(notidtoid(t), notidtoid(mymodule));
	ptr->count = 1;

	if (flag)
	{
	    ptr->def_bit = flag;
	    ptr->def_value = curr++;
	}

	ptr->next = id_table[i];
	id_table[i] = ptr;
    }
    else if (!ptr->def_bit)
    {
	ptr->def_bit = flag;
    }

    return ptr->r_value;
}

/*
 * output a sequence of #define statements (one for each value stored
 * in the hash table) to the file specified by fp
 */
void
out_final_defs(FILE * fp)
{
    int j;
    id_entry *ptr;

    for (j = 0; j < TABLESIZE; j++)
    {
	for (ptr = id_table[j]; ptr != NULL; ptr = ptr->next)
	{
	    if (ptr->def_bit)
	    {
		fprintf(fp, "#define %s%s\t%d\n", PREFIX,
			ptr->r_value, ptr->def_value);
	    }
	    else
	    {
		ferrs(0, "the identifier %s is used but not defined\n",
		      ptr->h_value);
	    }
	    if (ptr->count > 1)	/* not used */
	    {
		printf("The id %s has a count of %d\n",
		       ptr->r_value, ptr->count);
	    }
	}
    }
}

/*
 * return a copy of the string s with '-' replaced by '_'
 */
char *
notidtoid(char *s)
{

    char *t, *r;

    t = my_new_str(s);
    for (r = t; *r != '\0'; r++)
    {
	if (*r == '-')
	{
	    *r = '_';
	}
    }
    return t;
}

/*
 * return a copy of the string s
 */
char *
my_new_str(char *s)
{

    char *t;

    if ((t = (char *)malloc((unsigned)strlen(s) + 1)) == NULL)
    {
	my_error("my_new_str: Out of memory");
    }

    strcpy(t, s);
    return t;
}

/*
 * return the concatenation of the strings s1 and s2
 */
char *
my_strcat(char *s1, char *s2)
{
    char *s3, *s, *t;

    if (s1 == NULL || *s1 == '\0')
    {
	return my_new_str(s2);
    }

    if ((s3 = (char *)malloc((unsigned)(strlen(s1) + strlen(s2) + 1))) == NULL)
    {
	my_error("my_strcat: Out of memory");
    }

    for (s = s1, t = s3; *s != '\0'; s++, t++)
    {
	*t = *s;
    }
    strcpy(t, s2);
    return s3;
}

/*
 * a simple hash function
 */
int
hash_val(char *s)
{
    int i, sum;
    char *t;

    sum = 0;
    for (i = 1, t = s; *t != '\0'; i++, t++)
    {
	sum = sum + *t * i;
    }
    return (sum % TABLESIZE);
}

/*
 * initialize the table id_table
 */
void
init(void)
{
    int i;

    for (i = 0; i <= TABLESIZE; i++)
    {
	id_table[i] = NULL;
    }
}

#define BUFSIZE                128
#define MAX(a, b)        ((a) > (b) ? (a) : (b))

static char *buf = NULL;
static unsigned int len = 0;

/*
 * Return in a static buffer the two strings concatenated
 */
char *
concat(char *s1, char *s2)
{
    unsigned int tot;

    tot = strlen(s1) + strlen(s2) + 1;

    if (tot > len)
    {
	len = MAX(BUFSIZE, tot);
	if (buf == NULL)
	{
	    if ((buf = malloc(len)) == NULL)
	    {
		ferr(1, "concat:malloc failed\n");
	    }
	}
	else if ((buf = realloc(buf, len)) == NULL)
	{
	    ferr(1, "concat:realloc failed\n");
	}
    }
    strcpy(buf, s1);
    strcat(buf, s2);

    return (buf);
}

/*
 * Generate a free call given the name of the parameter, the module
 * name, and the name of the type
 */
char *
gfree(char *module, char *id, char *parm)
				  /* name of module we are in (usually
				     * mymodule) */
				      /* name of type we want to free */
				/* name of the pointer to the data */
{
    char *p1 = notidtoid(module);
    char *p2 = notidtoid(id);
    unsigned int tot;

    tot = 3 * strlen(p1) + 2 * strlen(p2) + BUFSIZE;

    if (tot > len)
    {
	len = MAX(BUFSIZE, tot);
	if (buf == NULL)
	{
	    if ((buf = malloc(len)) == NULL)
	    {
		ferr(1, "concat:malloc failed\n");
	    }
	}
	else if ((buf = realloc(buf, len)) == NULL)
	{
	    ferr(1, "concat:realloc failed\n");
	}
    }
    sprintf(buf, "(void) fre_obj((char *) %s, %s%s%s.md_dtab[%s%s%s], &%s%s%s, 1)",
	    parm,
	    PREFIX, p1, MODTYP_SUFFIX,
	    PREFIX, p2, p1,
	    PREFIX, p1, MODTYP_SUFFIX);
    free(p1);
    free(p2);

    return (buf);
}
