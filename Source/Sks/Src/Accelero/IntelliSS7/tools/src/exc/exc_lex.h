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
 *  ID: $Id: exc_lex.h,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:43  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:21  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:53:08  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:25  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:08:38  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:30:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1998/10/01 01:38:35  mmiers
 * LOG: Watch out for // after preprocessor directives; OSF1 doesn't like them.
 * LOG:
 * LOG: Revision 1.2  1998/05/19 23:43:52  mmiers
 * LOG: Fix for UNIX builds.
 * LOG:
 * LOG: Revision 1.1  1998/05/19 22:39:55  hdivoux
 * LOG: Creation.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_EXC_LEX_H_)
#define _EXC_LEX_H_

#if defined(WIN32)
#include <io.h>
#elif defined(unix)
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* yytext;
extern unsigned long int lexLineNumber;


#if !defined(TRUE)
#define TRUE 1
#endif

#if !defined(FALSE)
#define FALSE 1
#endif



/* Irrelevant encapsulation. */

#define Malloc(size)        malloc(size)
#define Realloc(ptr, size)  realloc(ptr, size)
#define Free(ptr)           free(ptr)


/* Dummy C types for YYSTYPE union (defined in file exc_yacc.tab.h). */

typedef void* string;
typedef void* Subsystem;
typedef void* Exception;
typedef void* ExceptionList;
typedef void* Option;
typedef void* OptionList;
typedef void* Attribute;
typedef void* AttributeList;
typedef void* Argument;
typedef void* ArgumentList;
typedef void* Description;
typedef void* DescriptionList;


#include <exc_yacc.tab.h> 

#endif    /* !defined(_EXC_LEX_H_) */
