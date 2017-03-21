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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:25  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:27  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:48  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4  2003/01/16 16:18:34  mmiers
 * LOG: Code reorganization.
 * LOG:
 * LOG: Revision 7.3  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.2  2002/09/26 22:18:59  yranade
 * LOG: 64 bit fixes
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:54  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/02/14 19:48:38  mmiers
 * LOG: Spurious printf
 * LOG:
 * LOG: Revision 5.4  2002/02/14 19:43:22  mmiers
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 5.3  2002/02/08 21:50:50  mmiers
 * LOG: ISUP integration.
 * LOG:
 * LOG: Revision 5.2  2002/02/06 23:44:58  mmiers
 * LOG: Continued ISUP integration
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:06  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.19  2001/04/11 20:10:08  mmiers
 * LOG:
 * LOG: Minor tweaks.
 * LOG:
 * LOG: Revision 3.18  2001/04/05 23:07:00  mmiers
 * LOG: Debugging C++ API.
 * LOG:
 * LOG: Revision 3.17  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.16  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.15  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.14  2001/02/14 20:44:54  mmiers
 * LOG: Ident
 * LOG:
 * LOG: Revision 3.13  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.12  2001/01/31 20:55:59  mmiers
 * LOG: More cleanup.  Socket fix.
 * LOG:
 * LOG: Revision 3.11  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.10  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.9  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.8  2001/01/17 20:17:47  mmiers
 * LOG: Get the global section added even if we don't have a backing store.
 * LOG:
 * LOG: Revision 3.7  2001/01/17 01:01:34  mmiers
 * LOG: Convert event log to C.  Add dispatch project.
 * LOG:
 * LOG: Revision 3.6  2001/01/16 15:20:21  mmiers
 * LOG: Defines for an OS without a filesystem
 * LOG:
 * LOG: Revision 3.5  2000/12/21 20:37:00  mmiers
 * LOG: Old bug parsing.
 * LOG:
 * LOG: Revision 3.4  2000/11/13 19:28:29  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.4  2000/11/10 23:07:54  mmiers
 * LOG: Some work on bugs, help Laksha out with condvar.
 * LOG:
 * LOG: Revision 3.3  2000/09/25 19:56:51  mmiers
 * LOG: Set up for new route style.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:06:39  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:04  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/03/28 22:23:17  mmiers
 * LOG:
 * LOG:
 * LOG: Fix Nick's bug report.
 * LOG:
 * LOG: Revision 2.5  2000/03/18 21:03:49  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.4  2000/02/15 16:37:19  mmiers
 * LOG:
 * LOG: Good enough for a working version.  I have some ideas about cleaning
 * LOG: up the leaks (use ITS_RegisterFeature for the ClassInit).
 * LOG:
 * LOG: Revision 2.3  2000/02/14 19:17:38  mmiers
 * LOG:
 * LOG: Distinguish between classInit and classPartInit.
 * LOG:
 * LOG: Revision 2.2  2000/02/14 17:52:50  mmiers
 * LOG:
 * LOG: Integrate TRACE and RESFILE into CORE.  Change RESFILE so that it
 * LOG: sets levels on/off from control strings in the globals segment of the
 * LOG: trace file.  Always include the TRACE and RESFILE classes.
 * LOG:
 * LOG: Revision 2.1  2000/02/12 00:08:41  mmiers
 * LOG:
 * LOG: Move RESFILE to core library.  Convert RESFILE and TRACE to OO footing.
 * LOG:
 * LOG: Revision 2.2  2000/02/02 02:20:50  mmiers
 * LOG:
 * LOG:
 * LOG: *Pretty much* finish up the first round of OO conversion.  TODO is
 * LOG: to figure out how to init the factories, and to split out the stack
 * LOG: initialization part (I know how to do that, I just gotta do it).
 * LOG:
 * LOG: Revision 2.1  2000/01/24 22:19:21  mmiers
 * LOG:
 * LOG:
 * LOG: Add UDP style transports.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:42  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.32  1999/11/22 19:23:31  mmiers
 * LOG:
 * LOG:
 * LOG: Cleanup from Linux build.  Removed nested comment in iniparse,
 * LOG: cleaned up decls in gdi_trans.
 * LOG:
 * LOG: Revision 1.31  1999/11/18 23:34:13  mmiers
 * LOG:
 * LOG:
 * LOG: Alias NULL and "" for the global section name.
 * LOG:
 * LOG: Revision 1.30  1999/11/18 18:54:04  mmiers
 * LOG:
 * LOG:
 * LOG: Remove the fileValid check in Reload.
 * LOG:
 * LOG: Revision 1.29  1999/08/27 22:49:20  rsonak
 * LOG:
 * LOG: Bug introduced in the earlier fix
 * LOG:
 * LOG: Revision 1.28  1999/08/27 22:35:09  rsonak
 * LOG:
 * LOG: Removed the check for duplicate keys
 * LOG:
 * LOG: Revision 1.27  1999/08/25 02:54:55  mmiers
 * LOG:
 * LOG:
 * LOG: It occurs to me that midline comments should be handled on a per-line
 * LOG: basis when the file is read, not when the joined string is being parsed.
 * LOG: Order should be:
 * LOG:    do
 * LOG:       while read-line == empty line or comment in column 1
 * LOG:       do
 * LOG:           discard line
 * LOG:       done
 * LOG:       set null at comment if comment not escaped, non column1 comments ok
 * LOG:       copy line
 * LOG:       while line ends in '\'
 * LOG:       do
 * LOG:          while read-line == emtpy line or comment in column 1
 * LOG:          do
 * LOG:             discard line
 * LOG:          done
 * LOG:          set null at comment if comment not escaped, non column1 comments ok
 * LOG:          append line
 * LOG:       done
 * LOG:       format string
 * LOG:    while strlen(formatted string) == 0
 * LOG:
 * LOG: But backslashes are actually removed in format string.
 * LOG:
 * LOG: Revision 1.25  1999/08/25 01:48:06  mmiers
 * LOG:
 * LOG:
 * LOG: Control for comment char only in column 1, and how to escape comment
 * LOG: characters.
 * LOG:
 * LOG: Revision 1.24  1999/08/23 02:03:24  mmiers
 * LOG:
 * LOG:
 * LOG: Add const modifiers.
 * LOG:
 * LOG: Revision 1.23  1999/08/20 20:01:01  mmiers
 * LOG:
 * LOG:
 * LOG: Add a findnext function.
 * LOG:
 * LOG: Revision 1.22  1999/08/20 00:10:38  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a free twice bug in the resource manager.
 * LOG:
 * LOG: Revision 1.21  1999/08/11 17:37:35  mmiers
 * LOG:
 * LOG:
 * LOG: Make reload impossible for file-less databases.
 * LOG:
 * LOG: Revision 1.20  1999/08/11 17:30:58  mmiers
 * LOG:
 * LOG:
 * LOG: More customer requests.
 * LOG:
 * LOG: Revision 1.19  1999/08/10 23:44:02  labuser
 * LOG:
 * LOG:
 * LOG: Fix the bugs I just introduced.
 * LOG:
 * LOG: Revision 1.18  1999/08/10 21:10:02  mmiers
 * LOG:
 * LOG:
 * LOG: Commonize the command line handling for services.  Make spaces
 * LOG: between the variable and the value (in resource files) the same
 * LOG: as an equal sign.  Let the user specify an alternate comment
 * LOG: character in a resource file.  Let the user add to his own environment
 * LOG: via the command line.
 * LOG:
 * LOG: Revision 1.17  1999/08/09 17:19:18  labuser
 * LOG:
 * LOG:
 * LOG: Check for naked carriage returns, not just newlines.
 * LOG:
 * LOG: Revision 1.16  1999/08/02 23:11:55  rsonak
 * LOG:
 * LOG: Fixed bugs!
 * LOG: 1)GetKeyValue: In the global section lookup, second param in strcpy was NULL!!!
 * LOG: 2)GetKeyName: In the global section lookup, second param in strcpy was NULL!!!
 * LOG:
 * LOG: Revision 1.15  1999/06/24 00:59:10  mmiers
 * LOG:
 * LOG:
 * LOG: Add an IPC type semaphore
 * LOG:
 * LOG: Revision 1.14  1999/06/22 22:53:12  mmiers
 * LOG:
 * LOG:
 * LOG: Add key insertion/deletion to this interface.
 * LOG:
 * LOG: Revision 1.13  1999/06/18 21:31:35  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a couple of minor bugs with the resource file parsing.
 * LOG:
 * LOG: Revision 1.12  1999/03/24 22:45:27  mmiers
 * LOG:
 * LOG:
 * LOG: Fix a number of bugs with the new infrastructure.  Provide an
 * LOG: example for the new format INI files.  Add duration to licensing
 * LOG: scheme.  Fix memory leak in timer subsystem.  Fix initialization
 * LOG: bug in thread lib.
 * LOG:
 * LOG: Revision 1.11  1999/03/12 00:06:12  mmiers
 * LOG:
 * LOG:
 * LOG: Move away from the "INI file per instance" philosphy to a single
 * LOG: file per application, divided into sections.
 * LOG:
 * LOG: Revision 1.10  1999/02/25 22:57:10  mmiers
 * LOG:
 * LOG:
 * LOG: Update for C++ compilation.
 * LOG:
 * LOG: Revision 1.9  1998/11/05 21:20:27  mmiers
 * LOG: Small tweaks for DEC compile.
 * LOG:
 * LOG: Revision 1.8  1998/10/07 17:24:07  whu
 * LOG: Fix a couple of bugs in windows threading, add debug to iniparse.
 * LOG:
 * LOG: Revision 1.7  1998/10/01 00:01:45  mmiers
 * LOG: Port to digital unix
 * LOG:
 * LOG: Revision 1.6  1998/09/23 22:04:29  jrao
 * LOG: Updates from HPUX.
 * LOG:
 * LOG: Revision 1.5  1998/09/22 17:24:17  mmiers
 * LOG: Continue adding C-trace into the library.
 * LOG:
 * LOG: Revision 1.4  1998/09/08 20:52:48  mmiers
 * LOG: Bug fix in SetIdenBDig for IS634.
 * LOG:
 * LOG: Iniparse needs to use "rt" only for WIN32.
 * LOG:
 * LOG: Revision 1.3  1998/07/03 19:41:42  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.2  1998/06/24 17:45:11  mmiers
 * LOG: Convert over to using the generated exceptions.
 * LOG:
 * LOG: Revision 1.1  1998/06/18 00:24:59  mmiers
 * LOG: Documentation update, C versions of some transports, C version of
 * LOG: resource file manager.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <its.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <its_trace.h>
#include <its_assertion.h>

#ident "$Id: its_iniparse.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

#if defined(_WIN32)
#define RES_FILE_MODE   "rt"
#else
#define RES_FILE_MODE   "r"
#endif

typedef struct _CacheEntry
{
    struct _CacheEntry*     next;
    int                     refCount;
    RESFILE_ManagerPart*    entry;
}
CACHE_Entry;

static ITS_MUTEX cacheGuard;
static CACHE_Entry* fileCache = NULL;

static char altCommentChar = ~0;
static ITS_BOOLEAN commentOnlyInColumnOne = ITS_FALSE;

/*
 * what is a comment character?
 */
#define IS_COMMENT_CHAR(c) \
    ((c) == '#' || (c) == ';' || (c) == altCommentChar)

/*
 * point code value separator
 */
#define PC_SEPARATOR    "-"
static char altPointCodeSeparator[2] = { '-', 0 };

/*
 * forward
 */
static void Unload(RESFILE_Manager* res);

/*
 * point code helpers
 */
#define ANSI_MEMBER_SHIFT   16
#define ANSI_CLUSTER_SHIFT  8
#define ANSI_NETWORK_SHIFT  0
#define ITU_MEMBER_SHIFT    11
#define ITU_CLUSTER_SHIFT   3
#define ITU_NETWORK_SHIFT   0

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function controls whether or not comment characters are only
 *      parsed as such in column 1.
 *
 *  Input Parameters:
 *      onlyInOne - if ITS_TRUE, comment chars are only valid in column 1.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      the value of the last setting of this
 *
 *  Notes:
 *      By default, comment chars are valid everywhere.
 *      This function is not MT-safe
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
RESFILE_SetCommentCharOnlyInColumnOne(ITS_BOOLEAN onlyInColumnOne)
{
    ITS_BOOLEAN was = commentOnlyInColumnOne;

    commentOnlyInColumnOne = onlyInColumnOne;

    return (was);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function sets an alternative comment character
 *
 *  Input Parameters:
 *      nc - the new alternate comment char
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      the value of the old alternate comment char
 *
 *  Notes:
 *      This function is not MT-safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI char
RESFILE_SetAltCommentChar(char nc)
{
    char c = altCommentChar;

    altCommentChar = nc;

    return (c);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function sets an alternative comment character
 *
 *  Input Parameters:
 *      nc - the new alternate comment char
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      the value of the old alternate comment char
 *
 *  Notes:
 *      This function is not MT-safe.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI char
RESFILE_SetAltPointCodeSeparator(char nc)
{
    char c = altPointCodeSeparator[0];

    altPointCodeSeparator[0] = nc;

    return (c);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function converts a string to an integer.  It understands
 *      both decimal and hex formats.
 *
 *  Input Parameters:
 *      string - the string to convert.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      the numeric value of the parse number
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_LONG
RESFILE_ParseNum(const char *num)
{
    ITS_LONG val = 0;
    size_t len = 0;
    size_t i;

    if (num == NULL)
    {
        return (0);
    }

    len = strlen(num);
    if (len == 0)
    {
        return (0);
    }

    /* don't try to catch overflow conditions.  It's up to the user not to
     * provide strings too long */
    if (strncmp(num, "0x", 2) == 0 || strncmp(num, "0X", 2) == 0)
    {
        /* hex */
        for (i = 2; i < len; i++)
        {
            val <<= 4;

            switch (num[i])
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                val |= num[i] - '0';
                break;

            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
                val |= (num[i] - 'a') + 10;
                break;

            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                val |= (num[i] - 'A') + 10;
                break;
            }
        }
    }
    else
    {
        /* decimal */
        for (i = 0; i < len; i++)
        {
            val *= 10;
            val += num[i] - '0';
        }
    }

    return (val);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Convert a point code string to a numeric point code. 
 *
 *  Input Parameters:
 *      pcStr - point code string
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      numeric point code
 *
 *  Notes:
 *      It is assumed that the point code is well formatted.
 ****************************************************************************/
static ITS_UINT
ParsePointCode(const char *pcStr,
               ITS_UINT memShift, ITS_UINT clustShift, ITS_UINT netShift)
{
    char *pcfield = NULL, *sep;
    ITS_UINT idata, member, cluster, network;
    char pc[ITS_PATH_MAX];

    strncpy(pc, pcStr, ITS_PATH_MAX);

    sep = PC_SEPARATOR;

retry:
    pcfield = strtok(pc, sep);
    if (pcfield == NULL)
    {
        return (RESFILE_BAD_POINT_CODE);
    }

    idata = (ITS_UINT)RESFILE_ParseNum(pcfield);
    member = idata << memShift;

    pcfield = strtok(NULL, "-");
    if (pcfield == NULL)
    {
        if (sep != altPointCodeSeparator)
        {
            sep = altPointCodeSeparator;

            goto retry;
        }

        return (RESFILE_BAD_POINT_CODE);
    }

    idata = (ITS_UINT)RESFILE_ParseNum(pcfield);
    cluster = idata << clustShift;

    pcfield = strtok(NULL, "-");
    if (pcfield == NULL)
    {
        return (RESFILE_BAD_POINT_CODE);
    }

    idata = (ITS_UINT)RESFILE_ParseNum(pcfield);
    network = idata << netShift;

    return (member | cluster | network);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Convert an ANSI point code string to a numeric point code. 
 *
 *  Input Parameters:
 *      pcStr - point code string
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      numeric point code
 *
 *  Notes:
 *      It is assumed that the point code is well formatted.
 ****************************************************************************/
ITSDLLAPI ITS_UINT
RESFILE_StrToPointCode_ANSI(const char *pcStr)
{
    return ParsePointCode(pcStr,
                          ANSI_MEMBER_SHIFT,
                          ANSI_CLUSTER_SHIFT,
                          ANSI_NETWORK_SHIFT);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Convert an ITU point code string to a numeric point code. 
 *
 *  Input Parameters:
 *      pcStr - point code string
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      numeric point code
 ****************************************************************************/
ITSDLLAPI ITS_UINT
RESFILE_StrToPointCode_CCITT(const char *pcStr)
{
    return ParsePointCode(pcStr,
                          ITU_MEMBER_SHIFT,
                          ITU_CLUSTER_SHIFT,
                          ITU_NETWORK_SHIFT);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function initializes the resource file cache.
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
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
RESFILE_Dump(RESFILE_Manager *res)
{
    FILE *output;
    RESFILE_SECTION *sec;
    RESFILE_VAR_VALUE *ent;
    char buf[ITS_PATH_MAX];

#if !defined(NO_FILESYSTEM)
    sprintf(buf, "%s.dmp", APPL_GetConfigFileName());
    output = fopen(buf, "w");
#else
    output = stdout;
#endif

    if (output == NULL)
    {
        return;
    }

    RESFILE_Lock(res);

    /* dump it all */
    for (sec = RESFILE_SECTIONS(res); sec != NULL; sec = sec->next)
    {
        if (sec->name)
        {
            fprintf(output, "[%s]\n", sec->name);
        }

        for (ent = sec->entries; ent != NULL; ent = ent->next)
        {
            fprintf(output, "%s=%s\n", ent->variable, ent->value);
        }

        fprintf(output, "\n");
    }

    RESFILE_Unlock(res);

#if !defined(NO_FILESYSTEM)
    fclose(output);
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function initializes the resource file cache.
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
 *  See Also:
 *      RESFILE_Terminate()
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("RESFILE_Initialize:\n"));

    if (MUTEX_CreateMutex(&cacheGuard, ITS_FALSE) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("RESFILE_Initialize: couldn't allocate mutex\n"));

        return (ITS_EINITFAIL);
    }

    TRACE_UpdateSettings();

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function destroys the resource database file cache.
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
 *  See Also:
 *      RESFILE_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    CACHE_Entry* ptr, * tmp;

    ITS_TRACE_DEBUG(("RESFILE_Terminate:\n"));

    for (ptr = fileCache; ptr != NULL; ptr = tmp)
    {
        RESFILE_Manager res;

        tmp = ptr->next;

        ptr->refCount = 0;

        res.manager = ptr->entry;

        if (RESFILE_VALID(&res) && RESFILE_FILE(&res))
        {
#if !defined(NO_FILESYSTEM)
            fclose(RESFILE_FILE(&res));
#endif
        }

        Unload(&res);

        free(RESFILE_NAME(&res));

        MUTEX_DeleteMutex(&RESFILE_LOCK(&res));

        /* free the manager */
        free(ptr->entry);

        /* free the node */
        free(ptr);
    }

    fileCache = NULL;

    MUTEX_DeleteMutex(&cacheGuard);
}

/************************ IMPLEMENTATION ***********************/

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method rewinds the resource file.
 *
 *  Input Parameters:
 *      res - the resource database handle
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
 *  See Also:
 ****************************************************************************/
static void
RewindFile(RESFILE_Manager* res)
{
    ITS_TRACE_DEBUG(("RewindFile:\n"));

    ITS_C_REQUIRE(res->manager && RESFILE_FILE(res));

    fseek(RESFILE_FILE(res), 0L, SEEK_SET);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method is a helper function for parsing strings recovered
 *      from the resource database file.
 *
 *  Input Parameters:
 *      string - the string to parse.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - indicates that the string was formatted correctly
 *      ITS_FALSE - an error occurred formatting the string
 *
 *  Notes:
 *      This method is not visible to the user.
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FormatString(char *string)
{
    char final[MAX_STRING_LEN];
    int index = 0;
    size_t i, j, len;
    ITS_BOOLEAN inLiteral = ITS_FALSE;
    ITS_BOOLEAN equalCovered = ITS_FALSE;

    len = strlen(string);

    if (len + 1 > MAX_STRING_LEN)
    {
        return ITS_FALSE;
    }

    /*
     * eat leading space
     */
    for (i = 0; i < len; i++)
    {
        if (!isspace(string[i]))
        {
            break;
        }
    }

    /*
     * clean up the line
     */
    for (; i < len; i++)
    {
        /* comment character ? */
        if (!commentOnlyInColumnOne &&
            IS_COMMENT_CHAR(string[i]) &&
            (i > 0 && string[i-1] != '\\'))
        {
            break;
        }
        else if (!commentOnlyInColumnOne &&
                 IS_COMMENT_CHAR(string[i]) &&
                 i > 0 && string[i-1] == '\\')
        {
            index--;
        }

        /* literal start ? */
        if (string[i] == '[' && !inLiteral)
        {
            inLiteral = ITS_TRUE;
        }

        /* blindly copying letters ? */
        if (inLiteral || !isspace(string[i]))
        {
            if (string[i] == '=')
            {
                equalCovered = ITS_TRUE;
            }

            final[index++] = string[i];
        }

        /* ending a literal ? */
        if (string[i] == ']' && inLiteral)
        {
            inLiteral = ITS_FALSE;
        }

        /* replacing spaces between var and value with '=' ? */
        if (!inLiteral && isspace(string[i]) && !equalCovered)
        {
            /* see if there are non-space characters remaining */
            for (j = i + 1; j < len; j++)
            {
                if (!commentOnlyInColumnOne &&
                    IS_COMMENT_CHAR(string[j]) &&
                    j > 0 && string[j-1] != '\\')
                {
                    break;
                }

                if (!isspace(string[j]))
                {
                    if (string[j] != '=')
                    {
                        equalCovered = ITS_TRUE;
                    }

                    break;
                }
            }

            /* replace the spaces with '=' */
            if (equalCovered)
            {
                final[index++] = '=';
            }

            i++;
            while (isspace(string[i]))
            {
                i++;
            }

            if (string[i] == '=')
            {
                equalCovered = ITS_TRUE;
            }

            i--;
        }
    }
    final[index] = '\0';

    strcpy(string, final);

    return ITS_TRUE;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method returns the next valid line in the file that contains
 *      useful information.  It will skip over all comment lines, and
 *      concatenate continued lines.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      len - the maximum line length the user is willing to handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      buf - the buffer to fill with the resource line.
 *
 *  Return Value:
 *      If the next resource line was successfully fetched, ITS_SUCCESS
 *          is returned.
 *      Any other return value indicates end-of-file, or some parse error
 *          has occurred.
 *
 *  Notes:
 *      This function should be used in conjunction with GetKeyName() and
 *      GetKeyValue() to sequentially parse a resource file.
 *
 *  See Also:
 *      GetKeyName(), GetKeyValue()
 ****************************************************************************/
static int
GetSettingString(RESFILE_Manager* res, char *string, int len)
{
    char tmpstring[ MAX_LINE_LENGTH ];
    int error;
    size_t i;

    string[0] = 0;

    ITS_TRACE_DEBUG(("GetSettingString:\n"));

    error = ITS_SUCCESS;

#if !defined(NO_FILESYSTEM)
    do
    {
        if (fgets(tmpstring, MAX_LINE_LENGTH, RESFILE_FILE(res)) == NULL)
        {
            error = ITS_EINVALIDARGS;

            return error;
        }

        while (IS_COMMENT_CHAR(tmpstring[0]) ||
               tmpstring[0] == '\r' || tmpstring[0] == '\n')
        {
            if (fgets(tmpstring, MAX_LINE_LENGTH, RESFILE_FILE(res)) == NULL)
            {
                error = ITS_EINVALIDARGS;

                return error;
            }
        }

        /*
         * Get rid of the newline that fgetws appends to the tmpstring.
         */
        if (tmpstring[strlen(tmpstring) - 1] == '\n') 
        {
            tmpstring[strlen(tmpstring) - 1] = 0;
        }
        /*
         * If you dont have a newline at the end, then that line was too long!
         * scream!!
         */
        else if (strlen(tmpstring) > MAX_LINE_LENGTH)
        {
            ITS_TRACE_ERROR(("GetSettingString: line buffer overflow\n"));

            error = ITS_EINVALIDARGS;

            return error;
        }

        /* strip comments from this line */
        if (!commentOnlyInColumnOne)
        {
            for (i = strlen(tmpstring) - 1; i > 0; i--)
            {
                if (IS_COMMENT_CHAR(tmpstring[i]) && tmpstring[i-1] != '\\')
                {
                    tmpstring[i] = 0;
                }
            }
        }

        strcpy(string, tmpstring);

        while (string[strlen(string) - 1] == '\\')
        {
            string[strlen(string) - 1] = 0;
            tmpstring[0] = 0;

            if (fgets(tmpstring, MAX_LINE_LENGTH, RESFILE_FILE(res)) == NULL)
            {
                error = ITS_EINVALIDARGS;

                return error;
            }

            while (IS_COMMENT_CHAR(tmpstring[0]))
            {
                if (fgets(tmpstring, MAX_LINE_LENGTH, RESFILE_FILE(res)) == NULL)
                {
                    error = ITS_EINVALIDARGS;

                    return error;
                }
            }

            /* Get rid of the newline that fgets appends to the tmpstring. */
            if (tmpstring[strlen(tmpstring) - 1] == '\n') 
            {
                tmpstring[strlen(tmpstring) - 1] = 0;
            }

            /*
             * If you dont have a newline at the end, then that line was too
             * long! scream!!
             */
            else if (strlen(tmpstring) > MAX_LINE_LENGTH)
            {
                ITS_TRACE_ERROR(("GetSettingString: line buffer overflow\n"));

                error = ITS_EINVALIDARGS;

                return error;
            }

            if (strlen(tmpstring) + strlen(string) > (size_t)len)
            {
                ITS_TRACE_ERROR(("GetSettingString: line buffer overflow\n"));

                error = ITS_EINVALIDARGS;

                return error;
            }

            /* strip comments from this line */
            if (!commentOnlyInColumnOne)
            {
                for (i = strlen(tmpstring) - 1; i > 0; i--)
                {
                    if (IS_COMMENT_CHAR(tmpstring[i]) &&
                        tmpstring[i-1] != '\\')
                    {
                        tmpstring[i] = 0;
                    }
                }
            }

            strcat(string, tmpstring);
        }

        /*
         * Format this tring to strip off redundant spaces and back slash
         * characters
         */
        FormatString(string);
    }
    while (strlen(string) == 0);
#endif

    return error;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the keyname portion of a resource line in the resource file.
 *
 *  Input Parameters:
 *      string - the string to pull the keyname out of
 *      len - the size of the output buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      key - the output buffer
 *
 *  Return Value:
 *      ITS_SUCCESS - the key was successfully parsed out.  Any other
 *          return value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 *      GetKeyName()
 ****************************************************************************/
static int
GetKeyName(char *string, char *key, int len)
{
    int error;
    int npos = 0;

    error = ITS_SUCCESS;

    ITS_TRACE_DEBUG(("GetKeyName: line:\n  '%s'\n", string));

    key[0] = 0;

    for (npos = 0;
         string[npos] != 0 && string[npos] != '=' && npos < len;
         npos++)
    {
        key[npos] = string[npos];
    }

    if (npos >= len)
    {
        ITS_TRACE_DEBUG(("GetKeyName: line buffer overflow\n"));

        error = ITS_EINVALIDARGS;

        return error;
    }

    if (string[npos] == 0)
    {
        ITS_TRACE_WARNING(("GetKeyName: missing key name\n"));

        error = ITS_EINVALIDARGS;

        return error;
    }

    while ((key[npos - 1] == ' ' || key[npos - 1] == '\t') && npos > 0)
    {
        npos--;
    }

    key[npos] = 0;

    ITS_TRACE_DEBUG(("GetKeyName: return key name: '%s'\n", key));

    return error;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Return the value portion of a resource line in the resource file.
 *
 *  Input Parameters:
 *      string - the string to pull the value out of
 *      len - the size of the output buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      value - the output buffer
 *
 *  Return Value:
 *      ITS_SUCCESS - the value was successfully parsed out.  Any other
 *          return value indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 *      GetKeyName()
 ****************************************************************************/
static int
GetKeyValue(char *string, char *value, int len)
{
    int npos = 0;
    int error;

    error = ITS_SUCCESS;

    ITS_TRACE_DEBUG(("GetKeyValue: line:\n  '%s'\n", string));

    value[0] = 0;

    while (string[npos] != '=' && string[npos] != 0 && npos < len)
    {
        npos++;
    }

    if (npos >= len)
    {
        ITS_TRACE_DEBUG(("GetKeyValue: line buffer overflow\n"));

        error = ITS_EINVALIDARGS;

        return error;
    }

    npos++;

    while ((string[npos] == ' ' || string[ npos ] == '\t') && npos < len)
    {
        npos++;
    }

    if (npos >= len)
    {
        ITS_TRACE_DEBUG(("GetKeyValue: line buffer overflow\n"));

        error = ITS_EINVALIDARGS;

        return error;
    }

    strcpy(value, &string[npos]);

    ITS_TRACE_DEBUG(("GetKeyValue: returns '%s'\n", value));

    return error;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Delete the contents of this resource database.
 *
 *  Input Parameters:
 *      res - the resource database to empty
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
 *  See Also:
 *      Load()
 ****************************************************************************/
static void
Unload(RESFILE_Manager* res)
{
    RESFILE_SECTION* sects, *tmp;

    for (sects = RESFILE_SECTIONS(res); sects != NULL; sects = tmp)
    {
        RESFILE_VAR_VALUE* var, *tv;

        tmp = sects->next;

        for (var = sects->entries; var != NULL; var = tv)
        {
            tv = var->next;

            if (var->variable)
            {
                free(var->variable);
            }
            if (var->value)
            {
                free(var->value);
            }
            free(var);
        }

        if (sects->name)
        {
            free(sects->name);
        }

        free(sects);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      To load the contents of this resource database from backing store.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the resource file was successfully parsed.  Any other
 *          return value indicates a file or parsing error.
 *
 *  Notes:
 *
 *  See Also:
 *      Unload()
 ****************************************************************************/
static int
Load(RESFILE_Manager* res)
{
    char string[ITS_PATH_MAX], name[ITS_PATH_MAX], value[ITS_PATH_MAX];
    RESFILE_SECTION* sect = NULL, **ts;
    RESFILE_VAR_VALUE* var, **tv;

    if (RESFILE_SECTIONS(res) == NULL)
    {
        /* always create the unnamed global section, even if
         * its empty */
        if ((sect = (RESFILE_SECTION *)calloc(1, sizeof(RESFILE_SECTION)))
            == NULL)
        {
            return (ITS_EINITFAIL);
        }

        RESFILE_SECTIONS(res) = sect;
    }

    if (!RESFILE_VALID(res))
    {
#if !defined(NO_FILESYSTEM)
        return (ITS_EINITFAIL);
#else
        return (ITS_SUCCESS);
#endif
    }

    RewindFile(res);

    ts = &sect->next;

    /* get the globals */
    tv = &sect->entries;
    while (GetSettingString(res, string, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        if (string[0] == '[')
        {
            break;
        }

        if ((var = (RESFILE_VAR_VALUE *)calloc(1, sizeof(RESFILE_VAR_VALUE)))
            == NULL)
        {
            Unload(res);

            return (ITS_EINITFAIL);
        }

        *tv = var;
        tv = &var->next;

        if (GetKeyName(string, name, ITS_PATH_MAX) != ITS_SUCCESS)
        {
            Unload(res);

            return (ITS_EINITFAIL);
        }
        if (GetKeyValue(string, value, ITS_PATH_MAX) != ITS_SUCCESS)
        {
            Unload(res);

            return (ITS_EINITFAIL);
        }

        var->variable = strdup(name);
        var->value = strdup(value);

        if (var->variable == NULL || var->value == NULL)
        {
            Unload(res);

            return (ITS_EINITFAIL);
        }

        string[0] = 0;
    }
    sect->current = sect->entries;

    /* get everything else */
    if (string[0] == '[')
    {
        for (;;)
        {
            char *tmp;

            /* always create the named section */
            if ((sect = (RESFILE_SECTION *)calloc(1, sizeof(RESFILE_SECTION)))
                == NULL)
            {
                Unload(res);

                return (ITS_EINITFAIL);
            }

            *ts = sect;
            ts = &sect->next;

            tmp = strchr(string, ']');
            if (tmp == NULL)
            {
                Unload(res);

                return (ITS_EINITFAIL);
            }

            *tmp = 0;

            if (strlen(string+1) == 0)
            {
                Unload(res);

                return (ITS_EINITFAIL);
            }

            sect->name = strdup(string+1);

            if (sect->name == NULL)
            {
                Unload(res);

                return (ITS_EINITFAIL);
            }

            /* get the entries in this section */
            tv = &sect->entries;
            while (GetSettingString(res, string,
                                    ITS_PATH_MAX) == ITS_SUCCESS)
            {
                if (string[0] == '[')
                {
                    break;
                }

                if ((var = (RESFILE_VAR_VALUE *)
                                calloc(1, sizeof(RESFILE_VAR_VALUE)))
                    == NULL)
                {
                    Unload(res);

                    return (ITS_EINITFAIL);
                }

                *tv = var;
                tv = &var->next;

                if (GetKeyName(string, name, ITS_PATH_MAX) != ITS_SUCCESS)
                {
                    Unload(res);

                    return (ITS_EINITFAIL);
                }
                if (GetKeyValue(string, value, ITS_PATH_MAX) != ITS_SUCCESS)
                {
                    Unload(res);

                    return (ITS_EINITFAIL);
                }

                var->variable = strdup(name);
                var->value = strdup(value);

                if (var->variable == NULL || var->value == NULL)
                {
                    Unload(res);

                    return (ITS_EINITFAIL);
                }

                string[0] = 0;
            }
            sect->current = sect->entries;

            if (string[0] != '[')
            {
                break;
            }
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method adds a section to the resource file.  It will not
 *      add the section if the section name is a duplicate.
 *
 *  Input Parameters:
 *      res - the resource manager to add to
 *      name - the name of the section to add
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
 *      A second global (NULL) section cannot be added.
 *
 *  See Also:
 ****************************************************************************/
static int
AddSection(RESFILE_Manager *res, const char *section)
{
    RESFILE_SECTION* sect = NULL, **ts;

    if (res == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    if (RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetKeyValue: couldn't lock mutex\n"));

        return (ITS_EINVALIDARGS);
    }

    /* look to see if it is the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        /* if we have a global section, this is illegal. */
        if (RESFILE_SECTIONS(res) != NULL)
        {
            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (ITS_EINVALIDARGS);
        }
        else
        {
            /* try to create the global section. */
            if ((RESFILE_SECTIONS(res) = (RESFILE_SECTION *)
                    calloc(1, sizeof(RESFILE_SECTION))) == NULL)
            {
                RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

                return (ITS_EINITFAIL);
            }
            else
            {
                RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

                return (ITS_SUCCESS);
            }
        }
    }

    /* look in the named sections, if any */
    for (ts = &RESFILE_SECTIONS(res); *ts != NULL; ts = &((*ts)->next))
    {
        if ((*ts)->name && strcmp((*ts)->name, section) == 0)
        {
            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (ITS_EINVALIDARGS);
        }
    }

    /* always create the named section */
    if ((sect = (RESFILE_SECTION *)calloc(1, sizeof(RESFILE_SECTION)))
        == NULL)
    {
        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_EINITFAIL);
    }

    *ts = sect;

    sect->name = strdup(section);

    if (sect->name == NULL)
    {
        *ts = NULL;

        free(sect);

        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_EINITFAIL);
    }

    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method removes a section to the resource file.
 *
 *  Input Parameters:
 *      res - the resource manager to remove to
 *      name - the name of the section to remove
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
 *      The global (NULL) section cannot be deleted.
 *
 *  See Also:
 ****************************************************************************/
static int
RemSection(RESFILE_Manager *res, const char *section)
{
    RESFILE_SECTION* sect = NULL, **ts;

    if (res == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    if (RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetKeyValue: couldn't lock mutex\n"));

        return (ITS_EINVALIDARGS);
    }

    /* look to see if it is the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_EINVALIDARGS);
    }

    /* make sure we have named sections */
    if (RESFILE_SECTIONS(res) == NULL)
    {
        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_ENOTFOUND);
    }

    /* look in the named sections, if any */
    for (ts = &RESFILE_SECTIONS(res)->next; *ts != NULL; ts = &((*ts)->next))
    {
        if (strcmp((*ts)->name, section) == 0)
        {
            RESFILE_VAR_VALUE* var, *tv;

            sect = *ts;

            *ts = (*ts)->next;

            for (var = sect->entries; var != NULL; var = tv)
            {
                tv = var->next;

                if (var->variable)
                {
                    free(var->variable);
                }
                if (var->value)
                {
                    free(var->value);
                }
                free(var);
            }

            if (sect->name)
            {
                free(sect->name);
            }

            free(sect);

            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (ITS_SUCCESS);
        }
    }

    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

    return (ITS_ENOTFOUND);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method adds a key/value pair to the resource database.  It
 *      will not add the key if the keyname already exists.
 *
 *  Input Parameters:
 *      res - the resource manager to add to
 *      name - the name of the section to add to
 *      key - the key to add
 *      value - the value to associate with this key
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
 *  See Also:
 ****************************************************************************/
static int
AddKeyValue(RESFILE_Manager *res, const char *section,
            const char *key, const char *value)
{
    RESFILE_SECTION* sect = NULL;
    RESFILE_VAR_VALUE* var = NULL, **tv;

    if (res == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    if (RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetKeyValue: couldn't lock mutex\n"));

        return (ITS_EINVALIDARGS);
    }

    /* look to see if it is the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        sect = RESFILE_SECTIONS(res);
    }
    else
    {
        /* look in the named sections, if any */
        for (sect = RESFILE_SECTIONS(res)->next; sect != NULL; sect = sect->next)
        {
            if (strcmp(sect->name, section) == 0)
            {
                break;
            }
        }
    }

    /* see if we have a section to add to */
    if (sect == NULL)
    {
        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_ENOTFOUND);
    }

    
    /* look for duplicate keys in the section */     
    for (tv = &sect->entries; (*tv) != NULL; tv = &((*tv)->next))
    {
        /*
         * we allow duplicate keys (in fact, we require it), so
         * don't do anything here.
         */
    }
      

    /* no duplicates, add the entry */
    if ((var = (RESFILE_VAR_VALUE *)
                    calloc(1, sizeof(RESFILE_VAR_VALUE))) == NULL)
    {
        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_EINITFAIL);
    }

    *tv = var;

    var->variable = strdup(key);
    var->value = strdup(value);

    if (var->variable == NULL || var->value == NULL)
    {
        *tv = NULL;

        free(var);

        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_EINITFAIL);
    }

    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method removes a key/value pair from the resource database.
 *
 *  Input Parameters:
 *      res - the resource manager to add to
 *      name - the name of the section to add to
 *      key - the key to add
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
 *  See Also:
 ****************************************************************************/
static int
RemKeyValue(RESFILE_Manager *res, const char *section,
            const char *key)
{
    RESFILE_SECTION* sect = NULL;
    RESFILE_VAR_VALUE* var = NULL, **tv;

    if (res == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    if (RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetKeyValue: couldn't lock mutex\n"));

        return (ITS_EINVALIDARGS);
    }

    /* look to see if it is the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        sect = RESFILE_SECTIONS(res);
    }
    else
    {
        /* look in the named sections, if any */
        for (sect = RESFILE_SECTIONS(res)->next; sect != NULL; sect = sect->next)
        {
            if (strcmp(sect->name, section) == 0)
            {
                break;
            }
        }
    }

    /* see if we have a section to add to */
    if (sect == NULL)
    {
        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_ENOTFOUND);
    }

    /* look for duplicate keys in the section */
    for (tv = &sect->entries; (*tv) != NULL; tv = &((*tv)->next))
    {
        if (strcmp(key, (*tv)->variable) == 0)
        {
            var = *tv;

            *tv = (*tv)->next;

            if (sect->current == var)
            {
                sect->current = *tv;
            }

            free(var->variable);
            free(var->value);
            free(var);

            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (ITS_SUCCESS);
        }
    }

    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method opens the specified resource database for processing.
 *
 *  Input Parameters:
 *      file - the name of the resource file
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
 *  See Also:
 *      RESFILE_DeleteResourceManager()
 ****************************************************************************/
static int
CreateResourceManager(ITS_Object obj, va_list args)
{
    RESFILE_Manager *ret = (RESFILE_Manager *)obj;
    CACHE_Entry* ptr;
    const char *file;
    ITS_BOOLEAN usesFile;

    file = va_arg(args, const char *);
    usesFile = va_arg(args, ITS_BOOLEAN);

    ITS_C_REQUIRE(file != NULL);

    if (MUTEX_AcquireMutex(&cacheGuard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("CreateResourceManager: couldn't get cache mutex\n"));

        return (ITS_EBADMUTEX);
    }

    for (ptr = fileCache; ptr != NULL; ptr = ptr->next)
    {
        if (strcmp(ptr->entry->name, file) == 0)
        {
            ret->manager = ptr->entry;

            ptr->refCount++;

            MUTEX_ReleaseMutex(&cacheGuard);

            return (ITS_SUCCESS);
        }
    }

    if ((ret->manager =
            (RESFILE_ManagerPart *)
                calloc(1, sizeof(RESFILE_ManagerPart))) == NULL)
    {
        ITS_TRACE_ERROR(("CreateResourceManager: out of memory\n"));

        MUTEX_ReleaseMutex(&cacheGuard);

        return (ITS_ENOMEM);
    }

    RESFILE_VALID(ret) = ITS_FALSE;

    if (usesFile)
    {
#if !defined(NO_FILESYSTEM)
        if ((RESFILE_FILE(ret) = fopen(file, RES_FILE_MODE)) == NULL)
        {
            ITS_TRACE_WARNING(("CreateResourceManager: file open failed: %s\n",
                               file));

            MUTEX_ReleaseMutex(&cacheGuard);

            return (ITS_ENOTFOUND);
        }
        else
        {
            RESFILE_VALID(ret) = ITS_TRUE;
        }
#endif
    }

    if ((RESFILE_NAME(ret) = strdup(file)) == NULL)
    {
        ITS_TRACE_WARNING(("CreateResourceManager: can't copy name\n"));

        free(ret->manager);

        MUTEX_ReleaseMutex(&cacheGuard);

        return (ITS_ENOMEM);
    }

    if (MUTEX_CreateMutex(&RESFILE_LOCK(ret), 0) != ITS_SUCCESS)
    {
        ITS_TRACE_WARNING(("CreateResourceManager: can't create mutex\n"));

        free(RESFILE_NAME(ret));

        free(ret->manager);

        MUTEX_ReleaseMutex(&cacheGuard);

        return (ITS_EBADMUTEX);
    }

    if ((ptr = (CACHE_Entry *)calloc(1, sizeof(CACHE_Entry))) == NULL)
    {
        ITS_TRACE_WARNING(("CreateResourceManager: Can't alloc cache ent\n"));

        MUTEX_DeleteMutex(&RESFILE_LOCK(ret));

        free(RESFILE_NAME(ret));

        free(ret->manager);

        MUTEX_ReleaseMutex(&cacheGuard);

        return (ITS_ENOMEM);
    }

    ptr->next = fileCache;
    ptr->refCount = 1;
    ptr->entry = ret->manager;

    /*
     * lock the file before releasing the cache guard.  This ensures
     * that nobody else can get access to this resdb before loading
     * has completed.
     */
    if (RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(ret))(ret) != ITS_SUCCESS)
    {
        ITS_TRACE_WARNING(("CreateResourceManager: lock failed\n"));

        free(ptr);

        MUTEX_DeleteMutex(&RESFILE_LOCK(ret));

        free(RESFILE_NAME(ret));

        free(ret->manager);

        MUTEX_ReleaseMutex(&cacheGuard);

        return (ITS_EBADMUTEX);
    }

    if (usesFile)
    {
        if (RESFILE_MAN_CLASS_LOAD(ITS_OBJ_CLASS(ret))(ret) != ITS_SUCCESS)
        {
            ITS_TRACE_WARNING(("CreateResourceManager: load failed\n"));

            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(ret))(ret);

            free(ptr);

            MUTEX_DeleteMutex(&RESFILE_LOCK(ret));

            free(RESFILE_NAME(ret));

            free(ret->manager);

            MUTEX_ReleaseMutex(&cacheGuard);

            return (ITS_ENOTFOUND);
        }

        if (RESFILE_VALID(ret))
        {
#if !defined(NO_FILESYSTEM)
            fclose(RESFILE_FILE(ret));
#endif

            RESFILE_VALID(ret) = ITS_FALSE;
        }
    }
    else
    {
        RESFILE_SECTION *sect;

        /* always create the unnamed global section, even if
         * its empty */
        if ((sect = (RESFILE_SECTION *)calloc(1, sizeof(RESFILE_SECTION)))
            == NULL)
        {
            return (ITS_EINITFAIL);
        }

        RESFILE_SECTIONS(ret) = sect;
    }

    fileCache = ptr;

    MUTEX_ReleaseMutex(&cacheGuard);

    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(ret))(ret);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method will close the resource database, terminating further
 *      processing for this thread.  The database is not destroyed until
 *      all openers have performed a close.
 *
 *  Input Parameters:
 *      res - the resource file handle
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
 *  See Also:
 *      CreateResourceManager()
 ****************************************************************************/
static void
DeleteResourceManager(ITS_Object obj)
{
    RESFILE_Manager* res = (RESFILE_Manager *)obj;
    CACHE_Entry** ptr, *tmp;

    ITS_TRACE_DEBUG(("DeleteResourceManager:\n"));

    if (MUTEX_AcquireMutex(&cacheGuard) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("CreateResourceManager: couldn't get cache mutex\n"));

        return;
    }

    for (ptr = &fileCache; *ptr != NULL; ptr = &(*ptr)->next)
    {
        if (strcmp((*ptr)->entry->name, RESFILE_NAME(res)) == 0)
        {
            break;
        }
    }

    if (*ptr == NULL)
    {
        MUTEX_ReleaseMutex(&cacheGuard);

        return;
    }

    (*ptr)->refCount--;

    if ((*ptr)->refCount > 0)
    {
        MUTEX_ReleaseMutex(&cacheGuard);

        return;
    }

    if (RESFILE_VALID(res) && RESFILE_FILE(res))
    {
#if !defined(NO_FILESYSTEM)
        fclose(RESFILE_FILE(res));
#endif
    }

    Unload(res);

    free(RESFILE_NAME(res));

    MUTEX_DeleteMutex(&RESFILE_LOCK(res));

    /* free the manager */
    free(res->manager);

    /* unlink from cache, free cache entry */
    tmp = *ptr;
    *ptr = tmp->next;
    free(tmp);

    MUTEX_ReleaseMutex(&cacheGuard);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will return the value portion of a resource entry
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      section - the section in the database to search under.
 *      len - the maximum value length the user will tolerate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      value - a pointer to a buffer to copy the value into.
 *
 *  Return Value:
 *      If the value is successfully parsed, ITS_SUCCESS is returned.
 *      Any other return value indicates a parse error.
 *
 *  Notes:
 *      This function positions the resource database to the next variable
 *      in this section.  This function should only be called when the
 *      resource database is locked.
 *
 *  See Also:
 *      GetKeyName(), Lock(), Unlock(), Rewind()
 ****************************************************************************/
static int
RealGetKeyValue(RESFILE_Manager* res, const char *section,
                char *value, int len)
{
    RESFILE_SECTION* sect = NULL;

    if (res == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    /* look in the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        if (RESFILE_SECTIONS(res) == NULL ||
            RESFILE_SECTIONS(res)->current == NULL ||
            (int)strlen(RESFILE_SECTIONS(res)->current->value) > len)
        {
            return (ITS_EINVALIDARGS);
        }

        strcpy(value, RESFILE_SECTIONS(res)->current->value);

        RESFILE_SECTIONS(res)->current = RESFILE_SECTIONS(res)->current->next;

        return (ITS_SUCCESS);
    }

    /* make sure we have named sections */
    if (RESFILE_SECTIONS(res) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    /* look in the named sections, if any */
    for (sect = RESFILE_SECTIONS(res)->next; sect != NULL; sect = sect->next)
    {
        if (strcmp(sect->name, section) == 0)
        {
            if (sect->current == NULL ||
                (int)strlen(sect->current->value) > len)
            {
                return (ITS_EINVALIDARGS);
            }

            strcpy(value, sect->current->value);

            sect->current = sect->current->next;

            return (ITS_SUCCESS);
        }
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method will return the key portion of a resource entry.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      section - the section in the database to search under.
 *      len - the maximum key name length the user will tolerate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      key - a pointer to a buffer to copy the key name into.
 *
 *  Return Value:
 *      If the key name is parsed successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an error parsing the resource line.
 *
 *      This function positions the resource database to the next variable
 *      in this section.  This function should only be called when the
 *      resource database is locked.
 *
 *  See Also:
 *      GetKeyValue(), Lock(), Unlock(), Rewind()
 ****************************************************************************/
static int
RealGetKeyName(RESFILE_Manager* res, const char *section,
               char *key, int len)
{
    RESFILE_SECTION* sect = NULL;

    if (res == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    /* look in the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        if (RESFILE_SECTIONS(res) == NULL ||
            RESFILE_SECTIONS(res)->current == NULL ||
            RESFILE_SECTIONS(res)->current->variable == NULL ||
            (int)strlen(RESFILE_SECTIONS(res)->current->variable) > len)
        {
            return (ITS_EINVALIDARGS);
        }

        strcpy(key, RESFILE_SECTIONS(res)->current->variable);

        return (ITS_SUCCESS);
    }

    /* make sure we have named sections */
    if (RESFILE_SECTIONS(res) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    /* look in the named sections, if any */
    for (sect = RESFILE_SECTIONS(res)->next; sect != NULL; sect = sect->next)
    {
        if (strcmp(sect->name, section) == 0)
        {
            if (sect->current == NULL ||
                sect->current->variable == NULL ||
                (int)strlen(sect->current->variable) > len)
            {
                return (ITS_EINVALIDARGS);
            }

            strcpy(key, sect->current->variable);

            return (ITS_SUCCESS);
        }
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method allows the user to randomly access a resource database to
 *      find the value associated with a specific key.
 *
 *  Input Parameters:
 *      res - the resource database handle
 *      section - the section in the database to search under.
 *      search - a pointer to the key value to search for
 *      klen - the maximum value size the user will tolerate
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      keyvalue - a pointer to a buffer to copy the value into if found.
 *
 *  Return Value:
 *      If the value is found, and successfully parsed, ITS_SUCCESS
 *          is returned.
 *      Any other return value indicates that the key was not found or
 *          that a processing error has occurred.
 *
 *  Notes:
 *      This method can be called even when parsing the file sequentially.
 *      It saves the current file position before searching for the key,
 *      and restores the file position before returning to the user.  This
 *      function automatically locks the resource database.
 *
 *  See Also:
 ****************************************************************************/
static int
GetKeyValueOf(RESFILE_Manager* res, const char *section,
              const char* search, char *keyvalue, int klen)
{
    RESFILE_SECTION* sect = NULL;
    RESFILE_VAR_VALUE* var = NULL;

    if (res == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    if (RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetKeyValue: couldn't lock mutex\n"));

        return (ITS_EINVALIDARGS);
    }

    /* look in the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        if (RESFILE_SECTIONS(res) == NULL)
        {
            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (ITS_EINVALIDARGS);
        }

        for (var = RESFILE_SECTIONS(res)->entries; var != NULL; var = var->next)
        {
            if (strcmp(search, var->variable) == 0)
            {
                if ((int)strlen(var->value) > klen)
                {
                    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

                    return (ITS_EINVALIDARGS);
                }

                strcpy(keyvalue, var->value);

                RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

                return (ITS_SUCCESS);
            }
        }

        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_ENOTFOUND);
    }

    /* make sure we have named sections */
    if (RESFILE_SECTIONS(res) == NULL)
    {
        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ITS_ENOTFOUND);
    }

    /* look in the named sections, if any */
    for (sect = RESFILE_SECTIONS(res)->next; sect != NULL; sect = sect->next)
    {
        if (strcmp(sect->name, section) == 0)
        {
            for (var = sect->entries; var != NULL; var = var->next)
            {
                if (strcmp(search, var->variable) == 0)
                {
                    if ((int)strlen(var->value) > klen)
                    {
                        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

                        return (ITS_EINVALIDARGS);
                    }

                    strcpy(keyvalue, var->value);

                    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

                    return (ITS_SUCCESS);
                }
            }
        }
    }

    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

    return (ITS_ENOTFOUND);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method rewinds a section of the resource database for
 *      sequential processing.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      section - the name of the section to rewind
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - rewind successful.  Any other return code indicates
 *          an IntelliSS7 error.
 *
 *  Notes:
 *      The resource database should be locked before this operation is
 *      attempted.
 *
 *  See Also:
 *      Lock(), Unlock()
 ****************************************************************************/
static int
RewindSection(RESFILE_Manager* res, const char *section)
{
    RESFILE_SECTION* sect;

    /* check globals */
    if (section == NULL || strcmp(section, "") == 0)
    {
        if (RESFILE_SECTIONS(res) == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        RESFILE_SECTIONS(res)->current = RESFILE_SECTIONS(res)->entries;

        return (ITS_SUCCESS);
    }

    /* then named sections */
    for (sect = RESFILE_SECTIONS(res)->next; sect != NULL; sect = sect->next)
    {
        if (strcmp(sect->name, section) == 0)
        {
            sect->current = sect->entries;

            return (ITS_SUCCESS);
        }
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method will lock the resource database for sequential processing
 *      by a single thread.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - locking successful.  Any other return code indicates
 *          an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      Unlock()
 ****************************************************************************/
static int
Lock(RESFILE_Manager *res)
{
    return MUTEX_AcquireMutex(&RESFILE_LOCK(res));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method will unlock the resource database for parallel access.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - unlocking successful.  Any other return code indicates
 *          an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      RESFILE_Lock()
 ****************************************************************************/
static int
Unlock(RESFILE_Manager* res)
{
    return MUTEX_ReleaseMutex(&RESFILE_LOCK(res));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This method will reload the resource database from disk.
 *
 *  Input Parameters:
 *      res - the resource file handle
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
 *  See Also:
 ****************************************************************************/
static int
Reload(RESFILE_Manager* res)
{
    int ret;

    if (RESFILE_Lock(res) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Reload: Can't lock database\n"));

        return (ITS_EBADMUTEX);
    }

    Unload(res);

    RESFILE_VALID(res) = ITS_FALSE;

#if !defined(NO_FILESYSTEM)
    if ((RESFILE_FILE(res) = fopen(RESFILE_NAME(res), RES_FILE_MODE)) == NULL)
    {
        ITS_TRACE_WARNING(("Reload: file open failed: %s\n",
                           RESFILE_NAME(res)));

        RESFILE_Unlock(res);

        return (ITS_EINVALIDARGS);
    }
    else
    {
        RESFILE_VALID(res) = ITS_TRUE;
    }
#endif

    if ((ret = Load(res)) != ITS_SUCCESS)
    {
        ITS_TRACE_WARNING(("Reload: Load failed\n"));

        RESFILE_Unlock(res);

        return (ret);
    }

    if (RESFILE_VALID(res))
    {
#if !defined(NO_FILESYSTEM)
        fclose(RESFILE_FILE(res));
#endif

        RESFILE_VALID(res) = ITS_FALSE;
    }

    RESFILE_Unlock(res);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      find the name of the next section in the database.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      name - the section name, or NULL for the first section
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
 *  See Also:
 ****************************************************************************/
static const char *
GetNextSectionName(RESFILE_Manager *res,
                   const char *section)
{
    RESFILE_SECTION* sect = NULL;
    const char *ret = NULL;

    if (res == NULL)
    {
        return (NULL);
    }

    if (RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("GetNextSectionName: couldn't lock mutex\n"));

        return (NULL);
    }

    /* look in the global section first. */
    if (section == NULL || strcmp(section, "") == 0)
    {
        if (RESFILE_SECTIONS(res) == NULL)
        {
            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (NULL);
        }

        if (RESFILE_SECTIONS(res)->next == NULL)
        {
            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (NULL);
        }

        ret = RESFILE_SECTIONS(res)->next->name;

        RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

        return (ret);
    }

    /* look in the named sections, if any */
    for (sect = RESFILE_SECTIONS(res)->next; sect != NULL; sect = sect->next)
    {
        if (strcmp(sect->name, section) == 0)
        {
            if (sect->next == NULL)
            {
                RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

                return (NULL);
            }

            ret = sect->next->name;

            RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

            return (ret);
        }
    }

    RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);

    return (NULL);
}

/*
 * the class record
 */
ITSDLLAPI RESFILE_ClassRec itsRESFILE_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        sizeof(RESFILE_Manager),        /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        RESFILE_CLASS_NAME,             /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CreateResourceManager,          /* instance create */
        DeleteResourceManager,          /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    },
    /* resfile part */
    {
        Lock,
        Unlock,
        RealGetKeyName,
        RealGetKeyValue,
        GetKeyValueOf,
        AddSection,
        RemSection,
        RewindSection,
        GetNextSectionName,
        AddKeyValue,
        RemKeyValue,
        Load,
        Reload,
        Unload
    }
};

ITSDLLAPI ITS_Class itsRESFILE_Class = (ITS_Class)&itsRESFILE_ClassRec;


/**************************** INTERFACE ******************************/

#if !defined(ITS_FASTCALL)

#undef RESFILE_CreateResourceManager
#undef RESFILE_CreateEmptyResourceManager
#undef RESFILE_DeleteResourceManager
#undef RESFILE_Lock
#undef RESFILE_Unlock
#undef RESFILE_GetKeyValue
#undef RESFILE_GetKeyName
#undef RESFILE_GetKeyValueOf
#undef RESFILE_AddSection
#undef RESFILE_RemSection
#undef RESFILE_Rewind
#undef RESFILE_GetNextSectionName
#undef RESFILE_AddKeyValue
#undef RESFILE_RemKeyValue
#undef RESFILE_Load
#undef RESFILE_Unload
#undef RESFILE_Reload

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method adds a section to the resource file.  It will not
 *      add the section if the section name is a duplicate.
 *
 *  Input Parameters:
 *      res - the resource manager to add to
 *      name - the name of the section to add
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
 *      A second global (NULL) section cannot be added.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RESFILE_AddSection(RESFILE_Manager *res, const char *section)
{
    return RESFILE_MAN_CLASS_ADD_SECTION(ITS_OBJ_CLASS(res))(res, section);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method removes a section to the resource file.
 *
 *  Input Parameters:
 *      res - the resource manager to remove to
 *      name - the name of the section to remove
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
 *      The global (NULL) section cannot be deleted.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RESFILE_RemSection(RESFILE_Manager *res, const char *section)
{
    return RESFILE_MAN_CLASS_REM_SECTION(ITS_OBJ_CLASS(res))(res, section);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method adds a key/value pair to the resource database.  It
 *      will not add the key if the keyname already exists.
 *
 *  Input Parameters:
 *      res - the resource manager to add to
 *      name - the name of the section to add to
 *      key - the key to add
 *      value - the value to associate with this key
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
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RESFILE_AddKeyValue(RESFILE_Manager *res, const char *section,
                    const char *key, const char *value)
{
    return RESFILE_MAN_CLASS_ADD_KEY(ITS_OBJ_CLASS(res))(res, section, key, value);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method removes a key/value pair from the resource database.
 *
 *  Input Parameters:
 *      res - the resource manager to add to
 *      name - the name of the section to add to
 *      key - the key to add
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
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RESFILE_RemKeyValue(RESFILE_Manager *res, const char *section,
                    const char *key)
{
    return RESFILE_MAN_CLASS_REM_KEY(ITS_OBJ_CLASS(res))(res, section, key);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method opens the specified resource database for processing.
 *
 *  Input Parameters:
 *      file - the name of the resource file
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
 *  See Also:
 *      RESFILE_DeleteResourceManager()
 ****************************************************************************/
ITSDLLAPI RESFILE_Manager*
RESFILE_CreateResourceManager(const char *file)
{
    return (RESFILE_Manager *)ITS_ConstructObject(itsRESFILE_Class,
                                                  file, ITS_TRUE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method opens the specified resource database for processing.
 *
 *  Input Parameters:
 *      file - the name of the resource file
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
 *  See Also:
 *      RESFILE_DeleteResourceManager()
 ****************************************************************************/
ITSDLLAPI RESFILE_Manager*
RESFILE_CreateEmptyResourceManager(const char *file)
{
    return (RESFILE_Manager *)ITS_ConstructObject(itsRESFILE_Class,
                                                  file, ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will close the resource database, terminating further
 *      processing for this thread.  The database is not destroyed until
 *      all openers have performed a close.
 *
 *  Input Parameters:
 *      res - the resource file handle
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
 *  See Also:
 *      RESFILE_CreateResourceManager()
 ****************************************************************************/
ITSDLLAPI void
RESFILE_DeleteResourceManager(RESFILE_Manager* res)
{
    ITS_DestructObject((ITS_Object)res);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will return the value portion of a resource entry
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      section - the section in the database to search under.
 *      len - the maximum value length the user will tolerate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      value - a pointer to a buffer to copy the value into.
 *
 *  Return Value:
 *      If the value is successfully parsed, ITS_SUCCESS is returned.
 *      Any other return value indicates a parse error.
 *
 *  Notes:
 *      This function positions the resource database to the next variable
 *      in this section.  This function should only be called when the
 *      resource database is locked.
 *
 *  See Also:
 *      RESFILE_GetKeyName(), RESFILE_Lock(), RESFILE_Unlock(), RESFILE_Rewind()
 ****************************************************************************/
ITSDLLAPI int
RESFILE_GetKeyValue(RESFILE_Manager* res, const char *section,
                    char *value, int len)
{
    return RESFILE_MAN_CLASS_GET_KEY_VALUE(ITS_OBJ_CLASS(res))(res, section,
                                                               value, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will return the key portion of a resource entry.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      section - the section in the database to search under.
 *      len - the maximum key name length the user will tolerate.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      key - a pointer to a buffer to copy the key name into.
 *
 *  Return Value:
 *      If the key name is parsed successfully, ITS_SUCCESS is returned.
 *      Any other return code indicates an error parsing the resource line.
 *
 *      This function positions the resource database to the next variable
 *      in this section.  This function should only be called when the
 *      resource database is locked.
 *
 *  See Also:
 *      RESFILE_GetKeyValue(), RESFILE_Lock(), RESFILE_Unlock(), RESFILE_Rewind()
 ****************************************************************************/
ITSDLLAPI int
RESFILE_GetKeyName(RESFILE_Manager* res, const char *section,
                   char *key, int len)
{
    return RESFILE_MAN_CLASS_GET_KEY_NAME(ITS_OBJ_CLASS(res))(res, section,
                                                              key, len);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method allows the user to randomly access a resource database to
 *      find the value associated with a specific key.
 *
 *  Input Parameters:
 *      res - the resource database handle
 *      section - the section in the database to search under.
 *      search - a pointer to the key value to search for
 *      klen - the maximum value size the user will tolerate
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      keyvalue - a pointer to a buffer to copy the value into if found.
 *
 *  Return Value:
 *      If the value is found, and successfully parsed, ITS_SUCCESS
 *          is returned.
 *      Any other return value indicates that the key was not found or
 *          that a processing error has occurred.
 *
 *  Notes:
 *      This method can be called even when parsing the file sequentially.
 *      It saves the current file position before searching for the key,
 *      and restores the file position before returning to the user.  This
 *      function automatically locks the resource database.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RESFILE_GetKeyValueOf(RESFILE_Manager* res, const char *section,
                      const char* search, char *keyvalue, int klen)
{
    return RESFILE_MAN_CLASS_GET_VALUE_OF_KEY(ITS_OBJ_CLASS(res))(res,
                                                                  section,
                                                                  search,
                                                                  keyvalue,
                                                                  klen);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method rewinds a section of the resource database for
 *      sequential processing.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      section - the name of the section to rewind
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - rewind successful.  Any other return code indicates
 *          an IntelliSS7 error.
 *
 *  Notes:
 *      The resource database should be locked before this operation is
 *      attempted.
 *
 *  See Also:
 *      RESFILE_Lock(), RESFILE_Unlock()
 ****************************************************************************/
ITSDLLAPI int
RESFILE_Rewind(RESFILE_Manager* res, const char *section)
{
    return RESFILE_MAN_CLASS_REWIND_SECTION(ITS_OBJ_CLASS(res))(res,
                                                                section);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will lock the resource database for sequential processing
 *      by a single thread.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - locking successful.  Any other return code indicates
 *          an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      RESFILE_Unlock()
 ****************************************************************************/
ITSDLLAPI int
RESFILE_Lock(RESFILE_Manager *res)
{
    return RESFILE_MAN_CLASS_LOCK(ITS_OBJ_CLASS(res))(res);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will unlock the resource database for parallel access.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - unlocking successful.  Any other return code indicates
 *          an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      RESFILE_Lock()
 ****************************************************************************/
ITSDLLAPI int
RESFILE_Unlock(RESFILE_Manager* res)
{
    return RESFILE_MAN_CLASS_UNLOCK(ITS_OBJ_CLASS(res))(res);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will load the resource database from disk.
 *
 *  Input Parameters:
 *      res - the resource file handle
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
 *      This method does *not* lock the database first.  Users should
 *      call RESFILE_Lock() before calling this function, and
 *      RESFILE_Unlock() after.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RESFILE_Load(RESFILE_Manager* res)
{
    return RESFILE_MAN_CLASS_LOAD(ITS_OBJ_CLASS(res))(res);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will clear the resource database from memory.
 *
 *  Input Parameters:
 *      res - the resource file handle
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
 *      This method does *not* lock the database first.  Users should
 *      call RESFILE_Lock() before calling this function, and
 *      RESFILE_Unlock() after.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
RESFILE_Unload(RESFILE_Manager* res)
{
    RESFILE_MAN_CLASS_UNLOAD(ITS_OBJ_CLASS(res))(res);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method will reload the resource database from disk.
 *
 *  Input Parameters:
 *      res - the resource file handle
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
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
RESFILE_Reload(RESFILE_Manager* res)
{
    return RESFILE_MAN_CLASS_RELOAD(ITS_OBJ_CLASS(res))(res);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      find the name of the next section in the database.
 *
 *  Input Parameters:
 *      res - the resource file handle
 *      name - the section name, or NULL for the first section
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
 *  See Also:
 ****************************************************************************/
ITSDLLAPI const char *
RESFILE_GetNextSectionName(RESFILE_Manager *res,
                           const char *section)
{
    return RESFILE_MAN_CLASS_GET_NEXT_SECTION(ITS_OBJ_CLASS(res))(res,
                                                                  section);
}

#endif
