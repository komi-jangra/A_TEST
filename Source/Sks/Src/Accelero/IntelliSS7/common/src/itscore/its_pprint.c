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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1.8.1  2006/02/23 06:33:06  sjaddu
 * LOG: Making va_args compatable to mvlppc.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.13  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 8.12.2.1  2004/09/21 05:40:17  mmanikandan
 * LOG: Propagating PPrint from current.
 * LOG:
 * LOG: Revision 8.12  2003/11/21 16:45:39  mmiers
 * LOG: Fix flag
 * LOG:
 * LOG: Revision 8.11  2003/10/22 21:07:59  mmiers
 * LOG: Change flag byte for ITU family
 * LOG:
 * LOG: Revision 8.10  2003/10/17 21:47:59  mmiers
 * LOG: Debug the pretty printers.  Need to finish TCAP.
 * LOG:
 * LOG: Revision 8.9  2003/10/01 14:36:56  mmiers
 * LOG: Add types for SS7, add binary printer
 * LOG:
 * LOG: Revision 8.8  2003/06/09 17:24:47  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 8.7  2003/05/19 09:15:21  yranade
 * LOG: Fix the problem with tracing. For all layers of stack, hex values were being
 * LOG: printed as 0. FIX: In PPrint_SimpleOutput initialize tmp to 0.
 * LOG:
 * LOG: Revision 8.6  2003/03/17 14:36:25  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 8.5  2003/03/06 20:44:03  mmiers
 * LOG: Trace tuning.
 * LOG:
 * LOG: Revision 8.4  2003/03/06 00:00:10  mmiers
 * LOG: More ring work.  Count newlines as record separators.
 * LOG:
 * LOG: Revision 8.3  2003/03/05 23:25:16  mmiers
 * LOG: Add vprint analogue, addition ringbuf fields
 * LOG:
 * LOG: Revision 8.2  2003/03/03 21:58:12  mmiers
 * LOG: Add extensible printf() for pretty printing.
 * LOG:
 * LOG: Revision 8.1  2003/02/28 22:55:44  mmiers
 * LOG: Add printer, prep for pretty print of SS7
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include <its.h>
#include <its_pprint.h>

#ident "$Id: its_pprint.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

#define PRINT_MAX   ((ITS_UINT)-1)

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      print to context, unbounded, variable args
 *
 *  Input Parameters:
 *      ring - the ring buffer to add to
 *      format - the printf() style format
 *      ... - variable args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI int
PPrint(RINGBUF_Manager *ring, const char *format, ...)
{
    va_list alist;
    int ret;

    va_start(alist, format);

    ret = PPrintNV(ring, PRINT_MAX, format, alist);

    va_end(alist);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      print to context, bounded, variable args
 *
 *  Input Parameters:
 *      ring - the ring buffer to add to
 *      size - the maximum length to write
 *      format - the printf() style format
 *      ... - variable args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI int
PPrintN(RINGBUF_Manager *ring, ITS_UINT size,
        const char *format, ...)
{
    va_list alist;
    int ret;

    va_start(alist, format);

    ret = PPrintNV(ring, size, format, alist);

    va_end(alist);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      print to context, unbounded, arg list
 *
 *  Input Parameters:
 *      ring - the ring buffer to add to
 *      format - the printf() style format
 *      ... - variable args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI int
PPrintV(RINGBUF_Manager *obj, const char *format, va_list alist)
{
    return PPrintNV(obj, PRINT_MAX, format, alist);
}

/*
 * Printing states
 */
typedef enum
{
    STATE_NORMAL,          /* 0 normal state; outputting literal chars */
    STATE_PERCENT,         /* 1 just read '%' */
    STATE_FLAG,            /* 2 just read flag character */
    STATE_WIDTH,           /* 3 just read width specifier */
    STATE_DOT,             /* 4 just read '.' */
    STATE_PRECIS,          /* 5 just read precision specifier */
    STATE_SIZE,            /* 6 just read size specifier */
    STATE_TYPE,            /* 7 just read type specifier */
    STATE_MAX              /* 8 dimension */
}
PrintState;

/*
 * Character classes
 */
typedef enum
{
    CCLASS_OTHER,           /* 0 character with no special meaning */
    CCLASS_PERCENT,         /* 1 '%' */
    CCLASS_DOT,             /* 2 '.' */
    CCLASS_STAR,            /* 3 '*' */
    CCLASS_ZERO,            /* 4 '0' */
    CCLASS_DIGIT,           /* 5 '1'..'9' */
    CCLASS_FLAG,            /* 6 ' ', '+', '-', '#' */
    CCLASS_SIZE,            /* 7 'h', 'l' */
    CCLASS_TYPE,            /* 8 type specifying character */
    CCLASS_MAX              /* 9 dimension */
}
CharClass;

/*
 * This is useful for reference here.  It helps keep the table
 * from getting mixed up.
 *  Oct   Dec   Hex   Char           Oct   Dec   Hex   Char
 * ------------------------------------------------------------
 * 000   0     00    NUL '\0'       100   64    40    @
 * 001   1     01    SOH            101   65    41    A
 * 002   2     02    STX            102   66    42    B
 * 003   3     03    ETX            103   67    43    C
 * 004   4     04    EOT            104   68    44    D
 * 005   5     05    ENQ            105   69    45    E
 * 006   6     06    ACK            106   70    46    F
 * 007   7     07    BEL '\a'       107   71    47    G
 *
 * 010   8     08    BS  '\b'       110   72    48    H
 * 011   9     09    HT  '\t'       111   73    49    I
 * 012   10    0A    LF  '\n'       112   74    4A    J
 * 013   11    0B    VT  '\v'       113   75    4B    K
 * 014   12    0C    FF  '\f'       114   76    4C    L
 * 015   13    0D    CR  '\r'       115   77    4D    M
 * 016   14    0E    SO             116   78    4E    N
 * 017   15    0F    SI             117   79    4F    O
 *
 * 020   16    10    DLE            120   80    50    P
 * 021   17    11    DC1            121   81    51    Q
 * 022   18    12    DC2            122   82    52    R
 * 023   19    13    DC3            123   83    53    S
 * 024   20    14    DC4            124   84    54    T
 * 025   21    15    NAK            125   85    55    U
 * 026   22    16    SYN            126   86    56    V
 * 027   23    17    ETB            127   87    57    W
 *
 * 030   24    18    CAN            130   88    58    X
 * 031   25    19    EM             131   89    59    Y
 * 032   26    1A    SUB            132   90    5A    Z
 * 033   27    1B    ESC            133   91    5B    [
 * 034   28    1C    FS             134   92    5C    \   '\\'
 * 035   29    1D    GS             135   93    5D    ]
 * 036   30    1E    RS             136   94    5E    ^
 * 037   31    1F    US             137   95    5F    _
 *
 * 040   32    20    SPACE          140   96    60    `
 * 041   33    21    !              141   97    61    a
 * 042   34    22    "              142   98    62    b
 * 043   35    23    #              143   99    63    c
 * 044   36    24    $              144   100   64    d
 * 045   37    25    %              145   101   65    e
 * 046   38    26    &              146   102   66    f
 * 047   39    27    '              147   103   67    g
 *
 * 050   40    28    (              150   104   68    h
 * 051   41    29    )              151   105   69    i
 * 052   42    2A    *              152   106   6A    j
 * 053   43    2B    +              153   107   6B    k
 * 054   44    2C    ,              154   108   6C    l
 * 055   45    2D    -              155   109   6D    m
 * 056   46    2E    .              156   110   6E    n
 * 057   47    2F    /              157   111   6F    o
 *
 * 060   48    30    0              160   112   70    p
 * 061   49    31    1              161   113   71    q
 * 062   50    32    2              162   114   72    r
 * 063   51    33    3              163   115   73    s
 * 064   52    34    4              164   116   74    t
 * 065   53    35    5              165   117   75    u
 * 066   54    36    6              166   118   76    v
 * 067   55    37    7              167   119   77    w
 *
 * 070   56    38    8              170   120   78    x
 * 071   57    39    9              171   121   79    y
 * 072   58    3A    :              172   122   7A    z
 * 073   59    3B    ;              173   123   7B    {
 * 074   60    3C    <              174   124   7C    |
 * 075   61    3D    =              175   125   7D    }
 * 076   62    3E    >              176   126   7E    ~
 * 077   63    3F    ?              177   127   7F    DEL
*/

/*
 * Table for controlling the printing DFA.
 */
static char
NextStateTable[CCLASS_MAX][STATE_MAX] =
{
    {   /* CCLASS_OTHER */
        STATE_NORMAL,   /* last STATE_NORMAL */
        STATE_NORMAL,   /* last STATE_PERCENT */
        STATE_NORMAL,   /* last STATE_FLAG */
        STATE_NORMAL,   /* last STATE_WIDTH */
        STATE_NORMAL,   /* last STATE_DOT */
        STATE_NORMAL,   /* last STATE_PRECIS */
        STATE_NORMAL,   /* last STATE_SIZE */
        STATE_NORMAL    /* last STATE_TYPE */
    },
    {   /* CCLASS_PERCENT */
        STATE_PERCENT,   /* last STATE_NORMAL */
        STATE_NORMAL,    /* last STATE_PERCENT */
        STATE_NORMAL,    /* last STATE_FLAG */
        STATE_NORMAL,    /* last STATE_WIDTH */
        STATE_NORMAL,    /* last STATE_DOT */
        STATE_NORMAL,    /* last STATE_PRECIS */
        STATE_NORMAL,    /* last STATE_SIZE */
        STATE_PERCENT    /* last STATE_TYPE */
    },
    {   /* CCLASS_DOT */
        STATE_NORMAL,    /* last STATE_NORMAL */
        STATE_DOT,       /* last STATE_PERCENT */
        STATE_DOT,       /* last STATE_FLAG */
        STATE_DOT,       /* last STATE_WIDTH */
        STATE_NORMAL,    /* last STATE_DOT */
        STATE_NORMAL,    /* last STATE_PRECIS */
        STATE_NORMAL,    /* last STATE_SIZE */
        STATE_NORMAL     /* last STATE_TYPE */
    },
    {   /* CCLASS_STAR */
        STATE_NORMAL,    /* last STATE_NORMAL */
        STATE_WIDTH,     /* last STATE_PERCENT */
        STATE_WIDTH,     /* last STATE_FLAG */
        STATE_NORMAL,    /* last STATE_WIDTH */
        STATE_PRECIS,    /* last STATE_DOT */
        STATE_NORMAL,    /* last STATE_PRECIS */
        STATE_NORMAL,    /* last STATE_SIZE */
        STATE_NORMAL     /* last STATE_TYPE */
    },
    {   /* CCLASS_ZERO */
        STATE_NORMAL,    /* last STATE_NORMAL */
        STATE_FLAG,      /* last STATE_PERCENT */
        STATE_FLAG,      /* last STATE_FLAG */
        STATE_WIDTH,     /* last STATE_WIDTH */
        STATE_PRECIS,    /* last STATE_DOT */
        STATE_PRECIS,    /* last STATE_PRECIS */
        STATE_NORMAL,    /* last STATE_SIZE */
        STATE_NORMAL     /* last STATE_TYPE */
    },
    {   /* CCLASS_DIGIT */
        STATE_NORMAL,    /* last STATE_NORMAL */
        STATE_WIDTH,     /* last STATE_PERCENT */
        STATE_WIDTH,     /* last STATE_FLAG */
        STATE_WIDTH,     /* last STATE_WIDTH */
        STATE_PRECIS,    /* last STATE_DOT */
        STATE_PRECIS,    /* last STATE_PRECIS */
        STATE_NORMAL,    /* last STATE_SIZE */
        STATE_NORMAL     /* last STATE_TYPE */
    },
    {   /* CCLASS_FLAG */
        STATE_NORMAL,    /* last STATE_NORMAL */
        STATE_FLAG,      /* last STATE_PERCENT */
        STATE_FLAG,      /* last STATE_FLAG */
        STATE_NORMAL,    /* last STATE_WIDTH */
        STATE_NORMAL,    /* last STATE_DOT */
        STATE_NORMAL,    /* last STATE_PRECIS */
        STATE_NORMAL,    /* last STATE_SIZE */
        STATE_NORMAL     /* last STATE_TYPE */
    },
    {   /* CCLASS_SIZE */
        STATE_NORMAL,    /* last STATE_NORMAL */
        STATE_SIZE,      /* last STATE_PERCENT */
        STATE_SIZE,      /* last STATE_FLAG */
        STATE_SIZE,      /* last STATE_WIDTH */
        STATE_SIZE,      /* last STATE_DOT */
        STATE_SIZE,      /* last STATE_PRECIS */
        STATE_SIZE,      /* last STATE_SIZE */
        STATE_NORMAL     /* last STATE_TYPE */
    },
    {   /* CCLASS_TYPE */
        STATE_NORMAL,    /* last STATE_NORMAL */
        STATE_TYPE,      /* last STATE_PERCENT */
        STATE_TYPE,      /* last STATE_FLAG */
        STATE_TYPE,      /* last STATE_WIDTH */
        STATE_TYPE,      /* last STATE_DOT */
        STATE_TYPE,      /* last STATE_PRECIS */
        STATE_TYPE,      /* last STATE_SIZE */
        STATE_NORMAL     /* last STATE_TYPE */
    }
};

static char
ClassTable[] =
{
    CCLASS_OTHER,   /* NUL 0 */
    CCLASS_OTHER,   /* SOH */
    CCLASS_OTHER,   /* STX */
    CCLASS_OTHER,   /* ETX */
    CCLASS_OTHER,   /* EOT */
    CCLASS_OTHER,   /* ENQ */
    CCLASS_OTHER,   /* ACK */
    CCLASS_OTHER,   /* BEL */

    CCLASS_OTHER,   /* BS 8 */
    CCLASS_OTHER,   /* HT */
    CCLASS_OTHER,   /* LF */
    CCLASS_OTHER,   /* VT */
    CCLASS_OTHER,   /* FF */
    CCLASS_OTHER,   /* CR */
    CCLASS_OTHER,   /* S0 */
    CCLASS_OTHER,   /* SI */

    CCLASS_OTHER,   /* DLE 16 */
    CCLASS_OTHER,   /* DC1 */
    CCLASS_OTHER,   /* DC2 */
    CCLASS_OTHER,   /* DC3 */
    CCLASS_OTHER,   /* DC4 */
    CCLASS_OTHER,   /* NAK */
    CCLASS_OTHER,   /* SYN */
    CCLASS_OTHER,   /* ETB */

    CCLASS_OTHER,   /* CAN 24 */
    CCLASS_OTHER,   /* EM */
    CCLASS_OTHER,   /* SUB */
    CCLASS_OTHER,   /* ESC */
    CCLASS_OTHER,   /* FS */
    CCLASS_OTHER,   /* GS */
    CCLASS_OTHER,   /* RS */
    CCLASS_OTHER,   /* US */

    CCLASS_FLAG,    /* ' ' 32 */
    CCLASS_OTHER,   /* '!' */
    CCLASS_OTHER,   /* '"' */
    CCLASS_FLAG,    /* '#' */
    CCLASS_OTHER,   /* '$' */
    CCLASS_PERCENT, /* '%' */
    CCLASS_OTHER,   /* '&' */
    CCLASS_OTHER,   /* ''' */

    CCLASS_OTHER,   /* '(' 40 */
    CCLASS_OTHER,   /* ')' */
    CCLASS_STAR,    /* '*' */
    CCLASS_FLAG,    /* '+' */
    CCLASS_OTHER,   /* ',' */
    CCLASS_FLAG,    /* '-' */
    CCLASS_DOT,     /* '.' */
    CCLASS_OTHER,   /* '/' */

    CCLASS_ZERO,    /* '0' 48 */
    CCLASS_DIGIT,   /* '1' */
    CCLASS_DIGIT,   /* '2' */
    CCLASS_DIGIT,   /* '3' */
    CCLASS_DIGIT,   /* '4' */
    CCLASS_DIGIT,   /* '5' */
    CCLASS_DIGIT,   /* '6' */
    CCLASS_DIGIT,   /* '7' */

    CCLASS_DIGIT,   /* '8' 56 */
    CCLASS_DIGIT,   /* '9' */
    CCLASS_OTHER,   /* ':' */
    CCLASS_OTHER,   /* ';' */
    CCLASS_OTHER,   /* '<' */
    CCLASS_OTHER,   /* '=' */
    CCLASS_OTHER,   /* '>' */
    CCLASS_OTHER,   /* '?' */

    CCLASS_OTHER,   /* '@' 64 */
    CCLASS_FLAG,    /* 'A' */
    CCLASS_OTHER,   /* 'B' */
    CCLASS_FLAG,    /* 'C' */
    CCLASS_OTHER,   /* 'D' */
    CCLASS_OTHER,   /* 'E' */
    CCLASS_OTHER,   /* 'F' */
    CCLASS_OTHER,   /* 'G' */

    CCLASS_OTHER,   /* 'H' 72 */
    CCLASS_OTHER,   /* 'I' */
    CCLASS_OTHER,   /* 'J' */
    CCLASS_OTHER,   /* 'K' */
    CCLASS_OTHER,   /* 'L' */
    CCLASS_OTHER,   /* 'M' */
    CCLASS_OTHER,   /* 'N' */
    CCLASS_OTHER,   /* 'O' */

    CCLASS_FLAG,    /* 'P' 80 */
    CCLASS_OTHER,   /* 'Q' */
    CCLASS_OTHER,   /* 'R' */
    CCLASS_OTHER,   /* 'S' */
    CCLASS_OTHER,   /* 'T' */
    CCLASS_OTHER,   /* 'U' */
    CCLASS_OTHER,   /* 'V' */
    CCLASS_OTHER,   /* 'W' */

    CCLASS_TYPE,    /* 'X' 88 */
    CCLASS_OTHER,   /* 'Y' */
    CCLASS_OTHER,   /* 'Z' (NT - TYPE) */
    CCLASS_OTHER,   /* '[' */
    CCLASS_OTHER,   /* '\' */
    CCLASS_OTHER,   /* ']' */
    CCLASS_OTHER,   /* '^' */
    CCLASS_OTHER,   /* '-' */

    CCLASS_OTHER,   /* '`' 96 */
    CCLASS_OTHER,   /* 'a' */
    CCLASS_TYPE,    /* 'b' */
    CCLASS_TYPE,    /* 'c' */
    CCLASS_TYPE,    /* 'd' */
    CCLASS_OTHER,   /* 'e' */
    CCLASS_OTHER,   /* 'f' */
    CCLASS_OTHER,   /* 'g' */

    CCLASS_SIZE,    /* 'h' 104 */
    CCLASS_TYPE,    /* 'i' */
    CCLASS_OTHER,   /* 'j' */
    CCLASS_OTHER,   /* 'k' */
    CCLASS_SIZE,    /* 'l' */
    CCLASS_OTHER,   /* 'm' */
    CCLASS_OTHER,   /* 'n' */
    CCLASS_TYPE,    /* 'o' */

    CCLASS_TYPE,    /* 'p' 112 */
    CCLASS_OTHER,   /* 'q' */
    CCLASS_OTHER,   /* 'r' */
    CCLASS_TYPE,    /* 's' */
    CCLASS_OTHER,   /* 't' */
    CCLASS_TYPE,    /* 'u' */
    CCLASS_OTHER,   /* 'v' */
    CCLASS_OTHER,   /* 'w' (NT - SIZE) */

    CCLASS_TYPE,    /* 'x' 120 */
    CCLASS_OTHER,   /* 'y' */
    CCLASS_OTHER,   /* 'z' */
    CCLASS_OTHER,   /* '{' */
    CCLASS_OTHER,   /* '|' */
    CCLASS_OTHER,   /* '}' */
    CCLASS_OTHER,   /* '~' */
    CCLASS_OTHER,   /* DEL */
};

static PPrint_Proc ProcsTable[128] = { NULL };

#define CHAR_CLASS(c)       \
    (!((c) & 0x80) ? ClassTable[((int)c)] : CCLASS_OTHER)

#define NEXT_STATE(cl, st)  \
    (NextStateTable[(cl)][(int)(st)])

#define OUTSIZE 512

static char *NullString = "(null)";

#define AppendChar(r,c,n)                   \
    do                                      \
    {                                       \
        int t;                              \
        t = RINGBUF_Append((r),(c),1U);     \
        *(n) = (t < 0) ? t : *(n) + t;      \
    }                                       \
    while (0)


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Format an integer
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
 *
 *  Notes:
 *
 ****************************************************************************/
static char *
IntOutput(va_list alist, char *text, int textLen, int *prefixLen,
          ITS_USHORT flags, int radix, int precision, int digitbase)
{
    unsigned long number;
    int digit;
    long l;
    char *output = text + textLen - 1;

    /*
     * Step 0.
     * Trailing NULL
     */
    *output = 0;

    /*
     * Step 1.
     * Get the argument
     */
    if (flags & FLAG_LONG)
    {
        l = va_arg(alist, long);
    }
    else if (flags & FLAG_SHORT)
    {
        if (flags & FLAG_SIGNED)
        {
            l = (short)va_arg(alist, int);
        }
        else
            l = (unsigned short)va_arg(alist, int);
    }
    else
    {
        if (flags & FLAG_SIGNED)
        {
            l = va_arg(alist, int);
        }
        else
        {
            l = (unsigned int)va_arg(alist, int);
        }
    }

    /*
     * Step 2.
     * check for negative; copy into number
     */
    if ((flags & FLAG_SIGNED) && l < 0)
    {
        number = -l;
        flags |= FLAG_NEGATIVE;   /* remember negative sign */
    }
    else
    {
        number = l;
    }

    /*
     * Step 3.
     * check precision value for default; non-default
     * turns off 0 flag, according to ANSI.
     */
    if (precision < 0)
    {
        precision = 1;
    }
    else
    {
        flags &= ~FLAG_LEAD_ZERO;
    }

    /*
     * Step 4.
     * Check if data is 0; if so, turn off hex prefix
     */
    if (number == 0)
    {
        *prefixLen = 0;
    }

    /*
     * Step 5.
     * Convert data to ASCII -- note if precision is zero
     * and number is zero, we get no digits at all.
     */
    while (precision-- > 0 || number != 0)
    {
        output--;

        digit = (int)(number % radix) + '0';
        number /= radix;                /* reduce number */

        if (digit > '9')
        {
            /* a hex digit, make it a letter */
            digit += digitbase;
        }
        *output = (char)digit;       /* store the digit */
    }

    /*
     * Step 6.
     * Force a leading zero if FORCEOCTAL flag set
     */
    if ((flags & FLAG_FORCE_OCTAL) && (*output != '0'))
    {
        *output = '0';
        output--;
    }

    return (output);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      format a floating point number
 *
 *  Input Parameters:
 *      ring - ring to add to
 *      ch - character to add
 *      numOut - number of characters written
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI char *
PPrint_Float(RINGBUF_Manager *ring, char type, va_list *alist,
             char *text, int textLen, ITS_USHORT *flags,
             char *prefix, int *prefixLen,
             int *fieldWidth, int *precision)
{
    int capExp = 0;
    char *output = text + textLen - 1;
    long double tmp;

    *output = 0;

    switch (type)
    {
    /* FLOAT, DOUBLE, LONG DOUBLE */
    case 'E':
    case 'G':
        capExp = 1;         /* capitalize exponent */
        type += 'a' - 'A';    /* convert format char to lower */
        /* FALLTHRU */

    case 'e':
    case 'f':
    case 'g':
        /* signed float output */
        *flags |= FLAG_SIGNED;

        /* compute the precision value */
        if (*precision < 0)
        {
            *precision = 6;
        }
        else if (*precision == 0 && type == 'g')
        {
            *precision = 1;
        }
        break;

    default:
        return (NULL);
    }

    /* do the conversion */
    if (*flags & FLAG_LONG)
    {
        tmp = va_arg(*alist, long double);
    }
    else
    {
        tmp = va_arg(*alist, double);
    }

    /* '#' and precision == 0 means force a decimal point */
    if ((*flags & FLAG_ALTERNATE) && *precision == 0)
    {
    }

    /* 'g' format means crop zero unless '#' given */
    if (type == 'g' && !(*flags & FLAG_ALTERNATE))
    {
    }

    /* check if result was negative, save '-' for later */
    /* and point to positive part (this is for '0' padding) */
    if (*output == '-')
    {
        *flags |= FLAG_NEGATIVE;
        output++;
    }

    return (output);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      append a character to the ring.
 *
 *  Input Parameters:
 *      ring - ring to add to
 *      ch - character to add
 *      numOut - number of characters written
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      The only flags affecting output from this function are
 *          FLAG_LEFT
 *          FLAG_SIGNED
 *          FLAG_NEGATIVE
 *          FLAG_SIGN_SPACE
 *          FLAG_LEAD_ZERO
 *
 ****************************************************************************/
ITSDLLAPI int
PPrint_SimpleOutput(RINGBUF_Manager *ring, char *output, int textLen,
                    ITS_USHORT flags, char *prefix, int prefixLen,
                    int fieldWidth, int precision)
{
    int numOut = 0, padding, i, tmp = 0;
    char ch;

    /*
     * At this point, we have done the specific conversion, and
     * 'output' points to text to print.  Now we justify it, put
     * on prefixes, leading zeros, and then print it.
     */
    if (flags & FLAG_SIGNED)
    {
        if (flags & FLAG_NEGATIVE)
        {
            /* prefix is a '-' */
            prefix[0] = '-';
            prefixLen = 1;
        }
        else if (flags & FLAG_SIGN)
        {
            /* prefix is '+' */
            prefix[0] = '+';
            prefixLen = 1;
        }
        else if (flags & FLAG_SIGN_SPACE)
        {
            /* prefix is ' ' */
            prefix[0] = ' ';
            prefixLen = 1;
        }
    }

    /*
     * calculate amount of padding -- might be negative,
     * but this will just mean zero
     */
    padding = fieldWidth - textLen - prefixLen;

    /* put out the padding, prefix, and text, in the correct order */
    if (!(flags & (FLAG_LEFT | FLAG_LEAD_ZERO)))
    {
        /* pad on left with blanks */
        ch = ' ';
        for (i = 0; i < padding; i++)
        {
            AppendChar(ring, &ch, &tmp);
            if (tmp < 0)
            {
                return (tmp);
            }
            numOut += tmp;
        }
    }

    /* write prefix */
    if (prefixLen)
    {
        tmp = RINGBUF_Append(ring, prefix, prefixLen);
        if (tmp < 0)
        {
            return (tmp);
        }
        numOut += tmp;
    }

    /* write leading zeros */
    if ((flags & FLAG_LEAD_ZERO) && !(flags & FLAG_LEFT))
    {
        ch = '0';
        for (i = 0; i < padding; i++)
        {
            AppendChar(ring, &ch, &tmp);
            if (tmp < 0)
            {
                return (numOut);
            }
            numOut += tmp;
        }
    }

    /* write text */
    tmp = RINGBUF_Append(ring, output, textLen);
    if (tmp < 0)
    {
        return (tmp);
    }
    numOut += tmp;

    /* pad on right with blanks */
    if (flags & FLAG_LEFT)
    {
        ch = ' ';
        for (i = 0; i < padding; i++)
        {
            AppendChar(ring, &ch, &tmp);
            if (tmp < 0)
            {
                return (tmp);
            }
            numOut += tmp;
        }
    }

    return (numOut);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      print to context, unbounded, variable args
 *
 *  Input Parameters:
 *      ring - the ring buffer to add to
 *      size - the maximum length to write
 *      format - the printf() style format
 *      alist - variable args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI int
PPrintNV(RINGBUF_Manager *ring, ITS_UINT size,
         const char *format, va_list alist)
{
    const char *ptr = format;
    char ch, prefix[8], text[OUTSIZE], *output = NULL, *p;
    CharClass charClass;
    PrintState state;    
    int numOut, i, padding, textLen = 0;
    int prefixLen, precision, fieldWidth, radix, hexBase;
    ITS_USHORT flags;

    state = STATE_NORMAL;
    numOut = 0;
    while ((ch = *ptr++) && numOut >= 0)
    {
        charClass = CHAR_CLASS(ch);
        state = NEXT_STATE(charClass, state);

        switch (state)
        {
        case STATE_NORMAL:
            if (ch == '\n')
            {
                RINGBUF_REC_COUNT(ring)++;
            }
            AppendChar(ring, &ch, &numOut);
            break;

        case STATE_PERCENT:
            prefixLen = 0;
            precision = -1;
            fieldWidth = 0;
            flags = 0;
            padding = 0;
            break;

        case STATE_FLAG:
            switch (ch)
            {
            case '-':   /* left justify */
                flags |= FLAG_LEFT;
                break;

            case '+':   /* force sign indicator */
                flags |= FLAG_SIGN;
                break;

            case ' ':   /* force sign or space */
                flags |= FLAG_SIGN_SPACE;
                break;

            case '#':   /* alternate form */
                flags |= FLAG_ALTERNATE;
                break;

            case '0':   /* pad with leading zeros */
                flags |= FLAG_LEAD_ZERO;
                break;

            case 'A':   /* output ANSI */
                flags |= FLAG_FAMILY_ANSI;
                break;

            case 'C':   /* output ITU */
                flags |= FLAG_FAMILY_ITU;
                break;

            case 'P':   /* output PRC */
                flags |= FLAG_FAMILY_PRC;
                break;

            default:    /* there shouldn't _be_ anything else */
                break;
            }
            break;

        case STATE_WIDTH:
            if (ch == '*')  /* arg specified width */
            {
                /* get width from arg list */
                fieldWidth = va_arg(alist, int);

                if (fieldWidth < 0)
                {
                    /* ANSI says neg field width means '-' flag and pos width */
                    flags |= FLAG_LEFT;
                    fieldWidth = -fieldWidth;
                }
            }
            else
            {
                /* add digit to current field width */
                fieldWidth *= 10;
                fieldWidth += ch - '0';
            }
            break;

        case STATE_DOT:
            /*
             * zero the precision, since dot with no number means 0
             * not default, according to ANSI
             */
            precision = 0;
            break;

        case STATE_PRECIS:
            if (ch == '*') /* arg specified precision */
            {
                /* get precision from arg list */
                precision = va_arg(alist, int);

                if (precision < 0)
                {
                    precision = -1; /* neg precision means default */
                }
            }
            else
            {
                /* add digit to current precision */
                precision *= 10;
                precision += ch - '0';
            }
            break;

        case STATE_SIZE:
            switch (ch)
            {
            case 'l':
                flags |= FLAG_LONG;
                break;

            case 'h':
                flags |= FLAG_SHORT;
                break;

            }
            break;

        case STATE_TYPE:
            /* Have type character.  Now figure out what to do */
            switch (ch)
            {
            /* STRING */
            case 's':
                /*
                 * ANSI rules on how much of string to print:
                 *   all if precision is default,
                 *   min(precision, length) if precision given.
                 * prints '(null)' if a null string is passed
                 */
                /*
                 * We can't use strlen: remember that the string
                 * may be unterminated.
                 */
                i = (precision == -1) ? INT_MAX : precision;
                output = va_arg(alist, char *);

                if (output == NULL)
                {
                    output = NullString;
                }

                p = output;
                while (i-- && *p)
                {
                    ++p;
                }
                textLen = p - output;
                break;

            /* CHAR */
            case 'c':
                ch = va_arg(alist, int);
                text[0] = ch;
                text[1] = 0;
                output = text;
                textLen = 1;
                break;

            /* BINARY */
            case 'b':
                flags &= ~FLAG_SIGNED;
                radix = 2;
                output = IntOutput(alist, text, OUTSIZE, &prefixLen,
                                   flags, radix, precision, 0);
                textLen = strlen(output);
                break;

            /* INT */
            case 'd':
            case 'i':
                /* signed decimal output */
                flags |= FLAG_SIGNED;
                radix = 10;
                output = IntOutput(alist, text, OUTSIZE, &prefixLen,
                                   flags, radix, precision, 0);
                textLen = strlen(output);
                break;

            /* UNSIGNED */
            case 'u':
                radix = 10;
                output = IntOutput(alist, text, OUTSIZE, &prefixLen,
                                   flags, radix, precision, 0);
                textLen = strlen(output);
                break;

            case 'p':
                precision = 2 * sizeof(void *);
                flags |= FLAG_LONG;
                hexBase = 'A' - '9' - 1;
                radix = 16;
                if (flags & FLAG_ALTERNATE)
                {
                    prefix[0] = '0';
                    prefix[1] = 'x';
                    prefixLen = 2;
                }
                output = IntOutput(alist, text, OUTSIZE, &prefixLen,
                                   flags, radix, precision, hexBase);
                textLen = strlen(output);
                break;

            case 'X':
                hexBase = 'A' - '9' - 1;
                radix = 16;
                if (flags & FLAG_ALTERNATE)
                {
                    prefix[0] = '0';
                    prefix[1] = 'X';
                    prefixLen = 2;
                }
                output = IntOutput(alist, text, OUTSIZE, &prefixLen,
                                   flags, radix, precision, hexBase);
                textLen = strlen(output);
                break;

            case 'x':
                /* unsigned lower hex output */
                hexBase = 'a' - '9' - 1;
                radix = 16;
                if (flags & FLAG_ALTERNATE)
                {
                    prefix[0] = '0';
                    prefix[1] = 'x';
                    prefixLen = 2;
                }
                output = IntOutput(alist, text, OUTSIZE, &prefixLen,
                                   flags, radix, precision, hexBase);
                textLen = strlen(output);
                break;

            case 'o':
                /* unsigned octal output */
                radix = 8;
                if (flags & FLAG_ALTERNATE)
                {
                    /* alternate form means force a leading 0 */
                    flags |= FLAG_FORCE_OCTAL;
                }
                output = IntOutput(alist, text, OUTSIZE, &prefixLen,
                                   flags, radix, precision, 0);
                textLen = strlen(output);
                break;

            default:
                ch &= 0x7F;
                if (ProcsTable[(int)ch] != NULL)
                {
                    output = (*ProcsTable[(int)ch])(ring, ch, alist,
                                                    text, OUTSIZE, &flags,
                                                    prefix, &prefixLen,
                                                    &fieldWidth, &precision);

                    if (output == NULL)
                    {
                        numOut = -1;
                        flags |= FLAG_OUTPUT_DONE;
                    }
                }
                break;
            }

            if (!(flags & FLAG_OUTPUT_DONE))
            {
                i = PPrint_SimpleOutput(ring, output, textLen, flags,
                                        prefix, prefixLen, fieldWidth, precision);
                if (i < 0)
                {
                    numOut = i;
                }
                else
                {
                    numOut += i;
                }
            }
            break;

        default:
            break;
        }
    }

    return (numOut);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Extend the printing facility
 *
 *  Input Parameters:
 *      type - the type letter to add this printer for
 *      formatter - the procedure to actually understand the type
 *          extension
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A pointer to the formatted buffer to print.
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI int
PPrint_AddProc(char type, PPrint_Proc formatter)
{
    type &= 0x7F;

    if (formatter == NULL)
    {
        if (ClassTable[(int)type] != CCLASS_TYPE)
        {
            return (ITS_EINUSE);
        }

        ProcsTable[(int)type] = NULL;
        ClassTable[(int)type] = CCLASS_OTHER;
    }
    else
    {
        if (ClassTable[(int)type] != CCLASS_OTHER)
        {
            return (ITS_EINUSE);
        }

        ProcsTable[(int)type] = formatter;
        ClassTable[(int)type] = CCLASS_TYPE;
    }

    return (ITS_SUCCESS);
}
