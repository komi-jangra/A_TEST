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
 * LOG: Revision 9.2.8.1  2006/07/04 12:43:35  gdevanand
 * LOG: Fix for MTP3 Emergency Alignment (Magesh)
 * LOG:
 * LOG: Revision 9.2  2005/04/01 12:01:25  ssingh
 * LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:40  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.10  2005/03/21 13:52:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.11.2.8.16.3  2005/02/25 11:10:49  dsatish
 * LOG: LINK_RemLink(), dsm commit was missing.
 * LOG:
 * LOG: Revision 7.11.2.8.16.2  2005/01/13 15:16:57  ssingh
 * LOG: fixing of ASP core dump after several INIT/ABRT exchange.
 * LOG: Ported from SMIMBASEPR6_3 (revision 7.11.2.7.6.1.2.1).
 * LOG: Trouble Ticket Number : 598
 * LOG:
 * LOG: Revision 7.11.2.8.16.1  2005/01/05 07:21:27  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.11.2.8  2003/10/15 21:22:56  lbana
 * LOG: Call Unfind on transport to balance ref count.
 * LOG:
 * LOG: Revision 7.11.2.7  2003/04/10 19:46:43  randresol
 * LOG: Fix procddure RemOneLink
 * LOG:
 * LOG: Revision 7.11.2.6  2003/04/07 19:49:05  randresol
 * LOG: remove ITS_TRACE_ERROR in LINK_FindLink
 * LOG:
 * LOG: Revision 7.11.2.5  2003/04/07 19:42:33  randresol
 * LOG: Fix bugs in LINK_RemLink and LINKSET_RemLinkSet
 * LOG:
 * LOG: Revision 7.11.2.4  2003/04/07 07:28:52  randresol
 * LOG: Fix bug in LINK_RemLink
 * LOG:
 * LOG: Revision 7.11.2.3  2003/04/07 05:34:05  randresol
 * LOG: Remove link from transport list when link is removed
 * LOG:
 * LOG: Revision 7.11.2.2  2003/02/18 07:13:47  ttipatre
 * LOG: Rectify Core problem with pegs when application initializes.
 * LOG:
 * LOG: Revision 7.11.2.1  2003/02/14 07:13:50  randresol
 * LOG: Add LINK_DumpLinkInfo and Enhance dump display
 * LOG:
 * LOG: Revision 7.11  2003/01/28 23:17:09  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.10  2002/12/30 17:29:45  lbana
 * LOG: propagating bug fixes in PR6.1 to current
 * LOG:
 * LOG: Revision 7.9  2002/12/20 21:10:02  randresol
 * LOG: Include the function LINK_GetTransportId
 * LOG:
 * LOG: Revision 7.8  2002/12/06 23:08:05  randresol
 * LOG: Include the function LINK_GetTransportId
 * LOG:
 * LOG: Revision 7.7  2002/11/14 21:55:06  randresol
 * LOG: Remove warnings
 * LOG:
 * LOG: Revision 7.6  2002/11/09 21:35:23  randresol
 * LOG: Create ROUTE_RWLock and use ROUTE_RWLock API for lookups
 * LOG:
 * LOG: Revision 7.5  2002/10/28 18:42:51  mmiers
 * LOG: Warning removal for 64 bit platforms.
 * LOG:
 * LOG: Revision 7.4  2002/09/26 22:59:29  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.3  2002/09/20 15:44:08  mmiers
 * LOG: Fix the licensing binaries
 * LOG:
 * LOG: Revision 7.2  2002/09/20 00:10:50  randresol
 * LOG: Add LINK_FindLinkNoLock, LINK_SetLinkQPut and modify DumpEntryDataLinkSets
 * LOG: to print proper value of link ids.
 * LOG:
 * LOG: Revision 6.17  2002/08/22 01:04:35  randresol
 * LOG: fix pointer problem seen in 64bit mode. replace
 * LOG: rinfo = *(ROUTE_InfoPtr *)(tmp->data); by the safer
 * LOG: memcpy(&rinfo, tmp->data, sizeof(rinfo));
 * LOG:
 * LOG: Revision 6.16  2002/07/24 17:47:33  randresol
 * LOG: Fix bugs found during MTP3 redundant functionality testing
 * LOG:
 * LOG: Revision 6.15  2002/07/10 20:12:12  mmiers
 * LOG: Don't error here, the parser does a presence check
 * LOG:
 * LOG: Revision 6.14  2002/07/05 19:33:59  yranade
 * LOG: Fix flag handling for IP transports.  Warning removal.
 * LOG:
 * LOG: Revision 6.13  2002/06/27 22:19:23  ssharma
 * LOG: Add family to dumps
 * LOG:
 * LOG: Revision 6.12  2002/06/23 18:12:49  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.11  2002/06/21 22:49:10  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.10  2002/06/21 20:26:26  randresol
 * LOG: Add function LINKSET_ParseRoutes and modify LINK_ParseLinkInfo
 * LOG:
 * LOG: Revision 6.9  2002/05/29 15:48:03  mmiers
 * LOG: Bit twiddling bugs noticed by Ricardo
 * LOG:
 * LOG: Revision 6.8  2002/05/21 21:07:43  randresol
 * LOG: Save link local transport ID in LINK_AddLink
 * LOG:
 * LOG: Revision 6.7  2002/05/14 18:50:54  omayor
 * LOG: Add LINK_AddLinkInfoToTransport function for the UAL.
 * LOG:
 * LOG: Revision 6.6  2002/05/14 17:29:31  randresol
 * LOG: Various bug fixes for MTP3
 * LOG:
 * LOG: Revision 6.5  2002/04/29 22:00:31  randresol
 * LOG: Various bug fixes in links and routes in DSM
 * LOG:
 * LOG: Revision 6.4  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.3  2002/03/26 18:08:43  randresol
 * LOG: The queues crBuf, cocbBuf, rtrvBuf and routes are now in DSM
 * LOG:
 * LOG: Revision 6.2  2002/03/08 22:55:06  mmiers
 * LOG: first pass of routing in DSM
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.35  2002/02/27 19:25:05  mmiers
 * LOG: A blivet bug that only showed on Solaris Forte when optimized.
 * LOG:
 * LOG: Revision 5.34  2002/02/15 23:13:28  ssharma
 * LOG: Forgot to build the list of links associated with a transport.
 * LOG:
 * LOG: Revision 5.33  2002/02/04 20:44:25  mmiers
 * LOG: A few more adjustments.
 * LOG:
 * LOG: Revision 5.32  2002/02/04 20:19:14  mmiers
 * LOG: Fix fencepost error.
 * LOG:
 * LOG: Revision 5.31  2002/02/04 18:16:00  mmiers
 * LOG: Dump function
 * LOG:
 * LOG: Revision 5.30  2002/01/18 22:31:23  mmiers
 * LOG: A couple of warnings pointed out by the sun compiler.
 * LOG:
 * LOG: Revision 5.29  2002/01/10 20:30:37  mmiers
 * LOG: Add SAAL capability
 * LOG:
 * LOG: Revision 5.28  2001/11/16 23:37:03  mmiers
 * LOG: Today's round of testing.
 * LOG:
 * LOG: Revision 5.27  2001/11/15 23:53:55  mmiers
 * LOG: Today's testing of MTP3.
 * LOG:
 * LOG: Revision 5.26  2001/11/12 22:33:31  mmiers
 * LOG: Clean up on exit.
 * LOG:
 * LOG: Revision 5.25  2001/11/12 22:02:45  mmiers
 * LOG: Delete link when removing.
 * LOG:
 * LOG: Revision 5.24  2001/11/06 22:07:19  mmiers
 * LOG: Missing cast.
 * LOG:
 * LOG: Revision 5.23  2001/11/01 01:40:29  mmiers
 * LOG: Debugging changeback.
 * LOG:
 * LOG: Revision 5.22  2001/10/31 01:57:17  mmiers
 * LOG: Add rtrvBuf creation
 * LOG:
 * LOG: Revision 5.21  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.20  2001/10/18 19:01:09  mmiers
 * LOG: Rework the link/route division.  It's easier if they're in
 * LOG: a single table.
 * LOG:
 * LOG: Revision 5.19  2001/10/18 00:14:16  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.18  2001/10/17 18:20:58  mmiers
 * LOG: Convert routing to use link information.
 * LOG:
 * LOG: Revision 5.17  2001/10/16 16:29:20  mmiers
 * LOG: Add code maps
 * LOG:
 * LOG: Revision 5.16  2001/10/15 22:18:39  mmiers
 * LOG: Initialize the link test pattern.
 * LOG:
 * LOG: Revision 5.15  2001/10/05 00:51:24  mmiers
 * LOG: Add fields for CO/CB/CR.
 * LOG:
 * LOG: Revision 5.14  2001/10/04 21:30:10  mmiers
 * LOG: More bug fixing.
 * LOG:
 * LOG: Revision 5.13  2001/10/03 18:54:16  mmiers
 * LOG: A couple of thinko fixes.
 * LOG:
 * LOG: Revision 5.12  2001/09/28 21:32:32  mmiers
 * LOG: Debugging caught some errors.
 * LOG:
 * LOG: Revision 5.11  2001/09/24 22:51:21  mmiers
 * LOG: Work on MTP3 integration.
 * LOG:
 * LOG: Revision 5.10  2001/09/11 23:48:36  mmiers
 * LOG: Remove old functions (their use would be undefined).
 * LOG:
 * LOG: Revision 5.9  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.8  2001/09/11 22:08:03  mmiers
 * LOG: Additional fields.
 * LOG:
 * LOG: Revision 5.7  2001/09/06 20:04:33  mmiers
 * LOG: Update.
 * LOG:
 * LOG: Revision 5.6  2001/08/31 22:13:22  mmiers
 * LOG: IsUp/IsAllowed handling.
 * LOG:
 * LOG: Revision 5.5  2001/08/30 20:04:06  vnitin
 * LOG: May have some extra routines.
 * LOG:
 * LOG: Revision 5.4  2001/08/29 22:37:07  mmiers
 * LOG: Add local point code to link set.
 * LOG:
 * LOG: Revision 5.3  2001/08/24 22:17:20  vnitin
 * LOG: More Link flags and data functions
 * LOG:
 * LOG: Revision 5.2  2001/08/17 21:08:56  mmiers
 * LOG: Add LINKSET class record.
 * LOG:
 * LOG: Revision 5.1  2001/08/17 20:21:15  mmiers
 * LOG: New routing subsystem for MTP3.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_app.h>
#include <its_dsm.h>
#include <its_trace.h>
#include <its_assertion.h>
#include <its_link.h>
#include <its_route.h>
#include <its_transports.h>
#include <its_route_rwlock.h>

#ident "$Id: its_ss7_link.c,v 1.1.1.1 2006-12-22 13:34:45 cvsadmin Exp $"

/*
 * growth factor
 */
#define LINK_SET_GROWTH_FACTOR  8

/*
 * map types
 */
#define MAP_TYPE_CODE       0x0001
#define MAP_TYPE_DEFAULT    0x0002
#define MAP_TYPE_DOWNS      0x0003
#define MAP_TYPE_LINKS      0x0004

/*
 * key types
 */
typedef struct
{
    ITS_OCTET   type;
    ITS_OCTET   linkSet;
}
LINKSET_MapKey;

typedef struct
{
    ITS_OCTET   type;
    ITS_OCTET   linkSet;
    ITS_UINT    maxLinks;
}
LINKSET_LinkKey;

typedef struct
{
    ITS_OCTET   linkSet;
    ITS_OCTET   linkCode;
}
LINK_Key;

/*
 *  This table holds local mapping of linkset/link to  a transport id.
 */
ITS_USHORT linkTransportMapDB[MAX_LINKSETS][MAX_LINKS_PER_LINKSET];

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINKSET_ParseLinkSetInfo(RESFILE_Manager *res, const char *section)
{
    char var[ITS_PATH_MAX], val[ITS_PATH_MAX];
    ITS_BOOLEAN haveAPC, haveLS, haveLPC, haveNI, haveFamily;
    ITS_BOOLEAN inSet;
    SS7_LinkSet set;
    SS7_LinkSetPtr ls;
    int ret;

    ITS_C_ASSERT(res != NULL);

    ITS_TRACE_DEBUG(("ParseLinkSetInfo: processing link set information\n"));

    inSet = ITS_FALSE;

    haveAPC = ITS_FALSE;
    haveLPC = ITS_FALSE;
    haveLS = ITS_FALSE;
    haveNI = ITS_FALSE;
    haveFamily = ITS_FALSE;

    memset(&set, 0, sizeof(SS7_LinkSet));

    RESFILE_Lock(res);
    RESFILE_Rewind(res, section);

    while (RESFILE_GetKeyName(res, section,
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section,
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        /* get the type */
        if (strcmp(var, LINKSET_INFO_STRING) == 0)
        {
            /* local */
            if (strcmp(val, LINKSET_BEGIN_STRING) == 0)
            {
                if (inSet)
                {
                    ITS_TRACE_ERROR(("ParseLinkSetInfo: nested set!\n"));

                    continue;
                }

                inSet = ITS_TRUE;
            }
            /* end of link set.  Add it if it's good */
            else if (strcmp(val, LINKSET_END_STRING) == 0)
            {
                if (!inSet)
                {
                    ITS_TRACE_ERROR(("ParseLinkSetInfo: end of no set!\n"));

                    continue;
                }

                inSet = ITS_FALSE;

                if (!haveAPC || !haveLS || !haveLPC || !haveNI || !haveFamily)
                {
                    ITS_TRACE_WARNING(("ParseLinkSetInfo: Missing set data\n"));

                    /* RESET */
                    haveAPC = ITS_FALSE;
                    haveLS = ITS_FALSE;

                    memset(&set, 0, sizeof(SS7_LinkSet));

                    continue;
                }

                /* add the link set */
                ls = LINKSET_FindLinkSet(set.linkSet);
                if (ls != NULL)
                {
                    /* This link set already exist, this is common 
                     * in a multi-node redundant configration.
                     */
                    ITS_TRACE_ERROR(("ParseLinkSetInfo: duplicate linkSet!\n"));

                    RESFILE_Unlock(res);

                    return (ITS_SUCCESS);
                }

                set.isUp = ITS_FALSE;
		set.firstLink = ITS_TRUE;   /* Magesh 28-June-06 */

                if ((ret = LINKSET_AddLinkSet(&set)) != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR(("ParseLinkSetInfo: Can't add set\n"));

                    RESFILE_Unlock(res);

                    return (ret);
                }

                /* RESET */
                haveAPC = ITS_FALSE;
                haveLPC = ITS_FALSE;
                haveLS = ITS_FALSE;
                haveNI = ITS_FALSE;
                haveFamily = ITS_FALSE;

                memset(&set, 0, sizeof(SS7_LinkSet));
            }
            else
            {
                ITS_TRACE_ERROR(("ParseLinkSetInfo: unknown link type\n"));

                continue;
            }
        }
        else if (!inSet)
        {
            /* don't know what it is */
            continue;
        }
        else if (strcmp(var, LINKSET_SET_STRING) == 0)
        {
            set.linkSet = (ITS_OCTET)RESFILE_ParseNum(val);

            haveLS = ITS_TRUE;
        }
        else if (strcmp(var, ADJ_POINT_CODE_STRING) == 0)
        {
            haveAPC = ITS_TRUE;

            set.adjacent = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, LOCAL_POINT_CODE_STRING) == 0)
        {
            haveLPC = ITS_TRUE;

            set.lpc = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, NI_STRING) == 0)
        {
            haveNI = ITS_TRUE;

            set.ni = RESFILE_ParseNum(val) & ROUTE_NI_MASK;
        }
        else if (strcmp(var, LINKSET_NUM_TO_START_STRING) == 0)
        {
            set.numToStart = RESFILE_ParseNum(val);
        }
        else if (strcmp(var, LINKSET_ADJ_STP_STRING) == 0)
        {
            set.adjSTP = strstr(val, "yes") != NULL ||
                            strstr(val, "YES") != NULL;
        }
        else if (strcmp(var, LINKSET_IS_CLINK_STRING) == 0)
        {
            set.isC = strstr(val, "yes") != NULL ||
                            strstr(val, "YES") != NULL;
        }
        else if (strcmp(var, LINKSET_IS_5BIT_STRING) == 0)
        {
            set.is5Bit = strstr(val, "yes") != NULL ||
                            strstr(val, "YES") != NULL;
        }
        else if (strcmp(var, FAMILY_STRING) == 0)
        {
            haveFamily = ITS_TRUE;

            if (strcmp(val, FAMILY_ANSI_STRING) == 0)
            {
                set.family = FAMILY_ANSI;
            }
            else if (strcmp(val, FAMILY_CCITT_STRING) == 0)
            {
                set.family = FAMILY_ITU;
            }
            else if (strcmp(val, FAMILY_CHINA_STRING) == 0)
            {
                set.family = FAMILY_CHINA;
            }
            else if (strcmp(val, FAMILY_JAPAN_STRING) == 0)
            {
                set.family = FAMILY_JAPAN;
            }
        }
    }

    RESFILE_Unlock(res);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
static void
LINKSET_DeleteLinkSetInfo()
{
    ITS_UINT i, count, msgCount;
    SS7_LinkSetPtr ls;
    DSMQUEUE_Entry *tmp;
    
    for (i = 0; i < ITS_SS7_DEFAULT_LINK_SET; i++)
    {
        ls = LINKSET_FindLinkSet((ITS_OCTET)i);

        if (ls)
        {
            msgCount = DSMQUEUE_COUNT(ls->routes);

            for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes);
                 tmp != NULL && count < msgCount ;
                 count++)
            {
                ROUTE_InfoPtr ri ;
                ROUTE_MatchInfo mi;

                memcpy(&ri, tmp->data, sizeof(ri));

                mi.basic = ri->basic;
                mi.linkSet = ls->linkSet;
                mi.priority = ri->priority;

                ROUTE_DeleteRouteContextInfo(&mi);

                /* move to the next entry */
                tmp = DSMQUEUE_NEXT(ls->routes, tmp);

            }

            LINKSET_RemLinkSet(ls);
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINKSET_AddLinkSet(SS7_LinkSetPtr linkSet)
{
    SS7_LinkSetPtr ls;
    LINKSET_MapKey key;
    int error;

    ITS_TRACE_DEBUG(("AddLinkSet\n"));

    /* lock the table */
    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS) != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EBADMUTEX);
    }

    /* sanity check 1: make sure it doesn't exist */
    ls = (SS7_LinkSetPtr)DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                        DSM_TABLE_LINK_SETS,
                                        (ITS_OCTET *)&linkSet->linkSet,
                                        sizeof(ITS_OCTET),
                                        &error);

    if (error == ITS_SUCCESS && ls != NULL)
    {
        ITS_TRACE_DEBUG(("Duplicate link set: %d\n", linkSet->linkSet));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EINVALIDARGS);
    }

    ls = (SS7_LinkSetPtr)DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                                         DSM_TABLE_LINK_SETS,
                                         (ITS_OCTET *)&linkSet->linkSet,
                                         sizeof(ITS_OCTET),
                                         sizeof(SS7_LinkSet),
                                         &error);

    if (error != ITS_SUCCESS || ls == NULL)
    {
        ITS_TRACE_DEBUG(("Can't allocate linkSet: %d\n", linkSet->linkSet));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_ENOMEM);
    }

    *ls = *linkSet;

    ls->routes = DSMQUEUE_Create(ENT_TYPE_LINKSET_ROUTES, linkSet->linkSet);

    if (ls->routes == NULL)
    {
        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_SETS,
                       &linkSet->linkSet,
                       sizeof(ITS_OCTET),
                       ls);

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_ENOMEM);
    }

    /* other allocations */
    key.type = MAP_TYPE_CODE;
    key.linkSet = ls->linkSet;

    ls->codeMap = DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                                  DSM_TABLE_LINK_MAPS,
                                  (ITS_OCTET *)&key,
                                  sizeof(LINKSET_MapKey),
                                  SLS_8BIT_ARRAY_SIZE * sizeof(ITS_OCTET),
                                  &error);

    if (error != ITS_SUCCESS || ls->codeMap == NULL)
    {
        ITS_TRACE_ERROR(("ParseLinkSetInfo: Out of memory!\n"));

        DSMQUEUE_Delete(ls->routes);

        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_SETS,
                       &linkSet->linkSet,
                       sizeof(ITS_OCTET),
                       ls);

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_ENOMEM);
    }

    key.type = MAP_TYPE_DEFAULT;
    ls->defaultMap = DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                                     DSM_TABLE_LINK_MAPS,
                                     (ITS_OCTET *)&key,
                                     sizeof(LINKSET_MapKey),
                                     SLS_8BIT_ARRAY_SIZE * sizeof(ITS_OCTET),
                                     &error);
    if (error != ITS_SUCCESS || ls->defaultMap == NULL)
    {
        ITS_TRACE_ERROR(("ParseLinkSetInfo: Out of memory!\n"));

        key.type = MAP_TYPE_CODE;
        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_MAPS,
                       (ITS_OCTET *)&key,
                       sizeof(LINKSET_MapKey),
                       ls->codeMap);

        DSMQUEUE_Delete(ls->routes);

        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_SETS,
                       &linkSet->linkSet,
                       sizeof(ITS_OCTET),
                       ls);

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_ENOMEM);
    }

    /*
     * go ahead and allocate 256 entries.  IP side might use
     * more than 16 links
     */
    key.type = MAP_TYPE_DOWNS;
    ls->lastDown = DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                             DSM_TABLE_LINK_MAPS,
                             (ITS_OCTET *)&key,
                             sizeof(LINKSET_MapKey),
                             MAX_LINKS * 16 * sizeof(ITS_OCTET),
                             &error);
    if (error != ITS_SUCCESS || ls->lastDown == NULL)
    {
        ITS_TRACE_ERROR(("ParseLinkSetInfo: Out of memory!\n"));

        key.type = MAP_TYPE_DEFAULT;
        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_MAPS,
                       (ITS_OCTET *)&key,
                       sizeof(LINKSET_MapKey),
                       ls->defaultMap);

        key.type = MAP_TYPE_CODE;
        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_MAPS,
                       (ITS_OCTET *)&key,
                       sizeof(LINKSET_MapKey),
                       ls->codeMap);

        DSMQUEUE_Delete(ls->routes);

        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_SETS,
                       &linkSet->linkSet,
                       sizeof(ITS_OCTET),
                       ls);

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_ENOMEM);
    }

    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_MAPS,
                     (ITS_OCTET *)&key,
                     sizeof(LINKSET_MapKey),
                     ls->lastDown);

    key.type = MAP_TYPE_DEFAULT;
    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_MAPS,
                     (ITS_OCTET *)&key,
                     sizeof(LINKSET_MapKey),
                     ls->defaultMap);

    key.type = MAP_TYPE_CODE;
    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_MAPS,
                     (ITS_OCTET *)&key,
                     sizeof(LINKSET_MapKey),
                     ls->codeMap);

    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_SETS,
                     &ls->linkSet,
                     sizeof(ITS_OCTET),
                     ls);

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI SS7_LinkSetPtr
LINKSET_FindLinkSet(ITS_OCTET linkSet)
{
    SS7_LinkSetPtr ls;

    ITS_TRACE_DEBUG(("FindLinkSet\n"));

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS) != ITS_SUCCESS)
    {
        return (NULL);
    }

    ls = LINKSET_FindLinkSetNoLock(linkSet); 

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    return (ls);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI SS7_LinkSetPtr
LINKSET_FindLinkSetNoLock(ITS_OCTET linkSet)
{

    SS7_LinkSetPtr ls;
    int error;

    ITS_TRACE_DEBUG(("FindLinkSet\n"));

    ls = DSM_FindNoLock(DSM_Mtp3FtGroupId,
                        DSM_TABLE_LINK_SETS,
                        &linkSet,
                        sizeof(ITS_OCTET),
                        &error);

    if (error != ITS_SUCCESS || ls == NULL)
    {
        return (NULL);
    }

    return (ls);

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINKSET_RemLinkSet(SS7_LinkSetPtr linkSet)
{
    LINKSET_MapKey key ;
    LINKSET_LinkKey lKey;

    ITS_TRACE_DEBUG(("RemLinkSet\n"));

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS) != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EBADMUTEX);
    }

    key.type = MAP_TYPE_DEFAULT;
    key.linkSet = linkSet->linkSet;
    DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                   DSM_TABLE_LINK_MAPS,
                   (ITS_OCTET *)&key,
                   sizeof(LINKSET_MapKey),
                   linkSet->defaultMap);

    key.type = MAP_TYPE_CODE;
    key.linkSet = linkSet->linkSet;
    DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                   DSM_TABLE_LINK_MAPS,
                   (ITS_OCTET *)&key,
                   sizeof(LINKSET_MapKey),
                   linkSet->codeMap);

    key.type = MAP_TYPE_DOWNS;
    key.linkSet = linkSet->linkSet;
    DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                   DSM_TABLE_LINK_MAPS,
                   (ITS_OCTET *)&key,
                   sizeof(LINKSET_MapKey),
                   linkSet->lastDown);

    if (linkSet->numLinks != 0 && linkSet->links != NULL)
    {
        lKey.type = MAP_TYPE_LINKS;
        lKey.linkSet  = linkSet->linkSet;
        lKey.maxLinks = linkSet->maxLinks;
        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINK_MAPS,
                       (ITS_OCTET *) &lKey,
                       sizeof(LINKSET_LinkKey),
                       linkSet->links);
    }

    DSMQUEUE_Delete(linkSet->routes);

    DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                   DSM_TABLE_LINK_SETS,
                   &linkSet->linkSet,
                   sizeof(ITS_OCTET),
                   linkSet);

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINKSET_CommitLinkSet(SS7_LinkSetPtr ls)
{
    ITS_UINT i;
    LINKSET_MapKey key;
    LINKSET_LinkKey linksKey; 

    if (ls == NULL)
    {
        return ITS_ENOMEM;
    }


    memset(&key, 0, sizeof(key));
    memset(&linksKey, 0, sizeof(linksKey));

    if (DSM_LockTable(
            DSM_Mtp3FtGroupId,
            DSM_TABLE_LINK_SETS) == ITS_EBADMUTEX)
    {
        ITS_TRACE_ERROR(("LINKSET_CommitLinkSet: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(
            DSM_Mtp3FtGroupId,
            DSM_TABLE_LINK_MAPS) == ITS_EBADMUTEX)
    {
        ITS_TRACE_ERROR(("LINKSET_CommitLinkSet: couldn't acquire mutex\n"));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EBADMUTEX);
    }


    key.linkSet = ls->linkSet;

    key.type = MAP_TYPE_DOWNS;
    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_MAPS,
                     (ITS_OCTET *)&key,
                     sizeof(LINKSET_MapKey),
                     ls->lastDown);


    key.type = MAP_TYPE_DEFAULT;
    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_MAPS,
                     (ITS_OCTET *)&key,
                     sizeof(LINKSET_MapKey),
                     ls->defaultMap);

    key.type = MAP_TYPE_CODE;
    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_MAPS,
                     (ITS_OCTET *)&key,
                     sizeof(LINKSET_MapKey),
                     ls->codeMap);

    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_SETS,
                     &ls->linkSet,
                     sizeof(ITS_OCTET),
                     ls); 

    if (ls->linkSet != 0 && ls->numLinks != 0)
    {
        linksKey.type = MAP_TYPE_LINKS;
        linksKey.linkSet = ls->linkSet;
        linksKey.maxLinks = ls->maxLinks;

        DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                         DSM_TABLE_LINK_MAPS,
                         (ITS_OCTET *)&linksKey,
                         sizeof(LINKSET_LinkKey),
                         ls->links);

        /* Commit all links */
        for (i = 0; i < ls->numLinks; i++)
        {
            LINK_CommitLink(ls->links[i]);
        }
    }

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      THE CALLER MUST HAVE EXCLUSIVELY LOCKED THE ROUTING TABLE
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LINKSET_AddRoute(SS7_LinkSetPtr linkSet, ROUTE_InfoPtr rinfo)
{
    ITS_EVENT ev;
    
    if (linkSet->family != rinfo->basic.family)
    {
        return (ITS_EINVCONFIG);
    }

    ITS_EVENT_INIT(&ev, ITS_NO_SRC, sizeof(rinfo));
    memcpy(ev.data, &rinfo, sizeof(rinfo) );

    return DSMQUEUE_Enqueue(linkSet->routes, ev);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      THE CALLER MUST HAVE EXCLUSIVELY LOCKED THE ROUTING TABLE
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LINKSET_RemRoute(SS7_LinkSetPtr ls, ROUTE_InfoPtr rinfo)
{
    ITS_UINT count, msgCount;
    DSMQUEUE_Entry *tmp;
    ROUTE_InfoPtr ri;
    
    msgCount = DSMQUEUE_COUNT(ls->routes);

    for (count = 0, tmp = DSMQUEUE_HEAD(ls->routes);
         tmp != NULL && count < msgCount ;
         count++) 
    {
        memcpy(&ri, tmp->data, sizeof(ri));

        if (ri == rinfo) 
        {
            break;
        }

       /* move to the next entry */
       tmp = DSMQUEUE_NEXT(ls->routes, tmp);
    }

    if ( tmp && (count <  msgCount) )
    {
        DSMQUEUE_Unlink(ls->routes, tmp);

        return (ITS_SUCCESS);
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function scans all the routes associated with the linkset,
 *      and invoked the user provided function for each route entry.
 *  Input Parameters:
 *      ls  :    the linkset  
 *      func:    function pointer invoked for each entry. The parameter
 *               to this function is ROUTE_InfoPtr. If this function returns
 *               other then ITS_SUCCESS, LINKSET_ParseRoutes stops parsing 
 *               the list exits. 
 *
 *  Input/Output Parameters:
 *       
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS
 *
 *  Notes:
 *    func signature: int (*LINKSET_ParseFunc) (ROUTE_InfoPtr rinfo);
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LINKSET_ParseRoutes(SS7_LinkSetPtr ls, LINKSET_ParseFunc func)
{
    ITS_UINT i, nCount;
    DSMQUEUE_Entry *tmp;
    ROUTE_InfoPtr rinfo;

    nCount = DSMQUEUE_COUNT(ls->routes);

    DSM_LockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES);

    for (i = 0, tmp = DSMQUEUE_HEAD(ls->routes);
         tmp != NULL && i < nCount ;
         i++)
    {
        memcpy(&rinfo, tmp->data, sizeof(rinfo));

        if (func(rinfo) != ITS_SUCCESS)
        {
            break;
        }

       /* move to the next entry */
       tmp = DSMQUEUE_NEXT(ls->routes, tmp);
    }

    DSM_UnlockTable(DSM_RoutingFtGroupId, DSM_TABLE_ROUTES); 

    return ITS_SUCCESS;

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINKSET_SetLinkSetState(SS7_LinkSetPtr linkSet, ITS_BOOLEAN isUp)
{
    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (isUp && !linkSet->isUp)
    {
        linkSet->isUp = ITS_TRUE;
    }
    else if (!isUp && linkSet->isUp)
    {
        linkSet->isUp = ITS_FALSE;
    }

     /* Magesh If the Linkset state is OOS, then set the firstLink to TRUE, so
       that when the linkset or link in the linkset is activated,
       EMERGENCY Proving will be carried for the first link */

    if(linkSet->isUp == ITS_FALSE)
    {
        linkSet->firstLink = ITS_TRUE;
    }

/* End Magesh 28-June-06 */

    LINKSET_CommitLinkSet(linkSet);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}

/* Magesh 28-June-06 */
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *
 *  Input/Output Parameters:
 *
 *  Input Parameters:
 *      Linkset, FirstLink flag
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
LINKSET_SetLinkSetFirstLink(SS7_LinkSetPtr linkSet, ITS_BOOLEAN firstLink)
{
    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    linkSet->firstLink = firstLink;

    LINKSET_CommitLinkSet(linkSet);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}

/* End Magesh 28-June-06 */
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINKSET_GetLinkSetState(SS7_LinkSetPtr linkSet, ITS_BOOLEAN *isUp)
{
    ITS_C_ASSERT(linkSet != NULL);

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (isUp)
    {
        *isUp = linkSet->isUp;
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    return (ITS_SUCCESS);
}

/*.implementation:extern
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
ITSDLLAPI void
LINKSET_PrintCodeMap(SS7_LinkSetPtr ls)
{
    ITS_UINT i, j;
    int printComma = 0;
    ITS_OCTET *map = ls->codeMap;

    ITS_TRACE_DEBUG(("PrintCodeMap:\n"));

    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return;
    }

    for (i = 0; i < ls->numLinks; i++)
    {
        TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                  ("Link %2d: ", i));
        for (j = 0; j < SLS_8BIT_ARRAY_SIZE; j++)
        {
            if (map[j] == i)
            {
                if (printComma)
                {
                    TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                              (","));
                }

                TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                          ("%3d", j));

                printComma = 1;
            }
        }

        TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
                  ("\n"));

        printComma = 0;
    }

    TRACE_RAW(ITS_InternalTrace, ITS_TRACE_LEVEL_DEBUG,
              ("\n"));

    ROUTE_UnlockRead(routeRWLock, NULL);
}

/*.implementation:static
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
static void
InitSLSMap(SS7_LinkSetPtr ls)
{
    ITS_UINT i;

    for (i = 0; i < SLS_8BIT_ARRAY_SIZE; i++)
    {
        ls->defaultMap[i] = i % ls->numLinks;
    }

    /* this is dangerous, but required, I think */
    memcpy(ls->codeMap, ls->defaultMap, SLS_8BIT_ARRAY_SIZE);
}

/*.implementation:static
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
 *
 *  Notes:
 *      NOTE: The caller MUST have translated a linkCode into an offset
 *      in the link array.
 *
 ****************************************************************************/
static void
BalanceSLS(SS7_LinkSetPtr ls, ITS_OCTET link)
{
    ITS_OCTET tmpMap[SLS_8BIT_ARRAY_SIZE];
    ITS_OCTET num5Bit[MAX_LINKS];
    ITS_OCTET num8Bit[MAX_LINKS];
    ITS_USHORT i, j;
    ITS_USHORT min5Bits = SLS_5BIT_ARRAY_SIZE;
    ITS_USHORT min8Bits = SLS_8BIT_ARRAY_SIZE;
    ITS_OCTET cur5Bits;
    ITS_OCTET cur8Bits;

    memset(num5Bit, 0, MAX_LINKS);

    /* find active links */
    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->active)
        {
            break;
        }
    }

    /* if none active, we're doomed */
    if (i >= ls->numLinks)
    {
        return;
    }

    /* find number of 5 bit entries */
    for (i = 0; i < SLS_5BIT_ARRAY_SIZE; i++)
    {
        if (ls->links[ls->codeMap[i]]->active)
        {
            num5Bit[ls->codeMap[i]]++;
        }
    }

    /* reassign the 5 bit entries */
    for (i = 0; i < SLS_5BIT_ARRAY_SIZE; i++)
    {
        if (ls->codeMap[i] == link)
        {
            /* find smallest 5 bit bucket */
            min5Bits = SLS_5BIT_ARRAY_SIZE;
            cur5Bits = 0;
            for (j = 0; j < ls->numLinks; j++)
            {
                if (ls->links[j]->active && num5Bit[j] < min5Bits)
                {
                    min5Bits = num5Bit[j];
                    cur5Bits = (ITS_OCTET)j;
                }
            }

            tmpMap[i] = cur5Bits;
            num5Bit[cur5Bits]++;
        }
        else
        {
            tmpMap[i] = ls->codeMap[i];
        }
    }
    
    /* initialize 8 bit entries */
    for (i = 0; i < ls->numLinks; i++)
    {
        num8Bit[i] = num5Bit[i];
    }

    /* update 8 bit counts */
    for (i = SLS_5BIT_ARRAY_SIZE; i < SLS_8BIT_ARRAY_SIZE; i++)
    {
        if (ls->links[ls->codeMap[i]]->active)
        {
            num8Bit[ls->codeMap[i]]++;
        }
    }

    /* do 8 bit spread */
    for (i = SLS_5BIT_ARRAY_SIZE; i < SLS_8BIT_ARRAY_SIZE; i++)
    {
        if (ls->codeMap[i] == link)
        {
            /* find smallest 8 bit bucket */
            min8Bits = SLS_8BIT_ARRAY_SIZE;
            cur8Bits = 0;
            for (j = 0; j < ls->numLinks; j++)
            {
                if (ls->links[j]->active && num8Bit[j] < min8Bits)
                {
                    min8Bits = num8Bit[j];
                    cur8Bits = (ITS_OCTET)j;
                }
            }

            tmpMap[i] = cur8Bits;
            num8Bit[cur8Bits]++;
        }
        else
        {
            tmpMap[i] = ls->codeMap[i];
        }
    }

    memcpy(ls->codeMap, tmpMap, SLS_8BIT_ARRAY_SIZE);
}

/*.implementation:static
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
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI void
LINKSET_RemoveActiveLink(SS7_LinkSetPtr ls, ITS_OCTET linkCode)
{
    ITS_OCTET ln;

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return;
    }

    /*
     * NOTE: We MUST translate a linkCode into an offset
     * in the link array.
     */
    for (ln = 0; ln < ls->numLinks; ln++)
    {
        if (ls->links[ln]->linkCode == linkCode)
        {
            break;
        }
    }

    if (ln >= ls->numLinks)
    {
        ROUTE_UnlockWrite(routeRWLock);

        return;
    }

    ls->links[ln]->active = ITS_FALSE;

    if (ls->ldIdx < (MAX_LINKS * 16 * sizeof(ITS_OCTET)))
    {
        ls->lastDown[ls->ldIdx] = ln;
        ls->ldIdx++;

        BalanceSLS(ls, ln);

        LINKSET_CommitLinkSet(ls);
    }

    ROUTE_UnlockWrite(routeRWLock);
}

/*.implementation:static
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
 *
 *  Notes:
 *
 ****************************************************************************/
ITSDLLAPI void
LINKSET_AddActiveLink(SS7_LinkSetPtr ls, ITS_OCTET linkCode)
{
    ITS_UINT i;
    ITS_BOOLEAN cp;
    ITS_OCTET ln;

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return;
    }

    /*
     * NOTE: We MUST translate a linkCode into an offset
     * in the link array.
     */
    for (ln = 0; ln < ls->numLinks; ln++)
    {
        if (ls->links[ln]->linkCode == linkCode)
        {
            break;
        }
    }

    if (ln >= ls->numLinks)
    {
        ROUTE_UnlockWrite(routeRWLock);

        return;
    }

    ls->links[ln]->active = (ITS_OCTET)ITS_TRUE;

    memcpy(ls->codeMap, ls->defaultMap, SLS_8BIT_ARRAY_SIZE);
    
    cp = ITS_FALSE;
    for (i = 0; i < ls->ldIdx; i++)
    {
        if (ls->lastDown[i] != ln)
        {
            BalanceSLS(ls, ls->lastDown[i]);

            if (cp && i > 0)
            {
                ls->lastDown[i-1] = ls->lastDown[i];
            }
        }
        else
        {
            cp = ITS_TRUE;
        }
    }

    if (ls->ldIdx > 0)
    {
        ls->ldIdx--;
    }

    LINKSET_CommitLinkSet(ls);

    ROUTE_UnlockWrite(routeRWLock);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *    Add link to the list of links fro that transport.
 *
 *  Input Parameters:
 *      tc:  pointer to the TRANSPORT_Control for that transport.
 *      lp:  pointer to the Link
 *      isInterNode: ITS_TRUE or ITS_FALSE if internode
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
void
LINK_AddLinkInfoToTransport(void *trans, SS7_LinkPtr lp)
                            
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)trans;

    lp->next = TRANSPORT_SS7_INFO(tc).linkInfo;
    
    if (TRANSPORT_SS7_INFO(tc).linkInfo)
    {
        TRANSPORT_SS7_INFO(tc).linkInfo->prev = lp;
    }

    TRANSPORT_SS7_INFO(tc).linkInfo = lp;

    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *    Remove a link from a transport link list
 *
 *  Input Parameters:
 *      lp:  pointer to the Link
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
LINK_RemLinkInfoFromTransport(SS7_LinkPtr lp)
{
    TRANSPORT_Control *tc = NULL;
    ITS_UINT trId = LINK_GetTransportId(lp);

    if (trId == ITS_NO_SRC)
    {
        return;
    }

    tc = TRANSPORT_FindTransport(trId);

    if (tc == NULL)
    {
        return;
    }

    TRANSPORT_UnfindTransport(tc);

    if (TRANSPORT_SS7_INFO(tc).linkInfo == NULL)
    {
        return;
    }

    /* removing fisrt element in list */
    if(TRANSPORT_SS7_INFO(tc).linkInfo == lp)
    {
        TRANSPORT_SS7_INFO(tc).linkInfo = lp->next;
    }

    if (lp->prev)
    {
        lp->prev->next = lp->next;
    }

    if (lp->next)
    {
        lp->next->prev = lp->prev;
    }

    lp->next = lp->prev = NULL;

    return;
}



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_ParseLinkInfo(void *trans)
{
    char var[ITS_PATH_MAX], val[ITS_PATH_MAX];
    ITS_BOOLEAN haveLC, haveLS, haveLP, haveFamily;
    ITS_BOOLEAN inLink;
    ITS_BOOLEAN isInterNode;
    ITS_OCTET linkSet = ITS_SS7_DEFAULT_LINK_SET; /* illegal value */
    SS7_Link link;
    int ret;
    TRANSPORT_Control *tc = (TRANSPORT_Control *)trans;
    ITS_USHORT instance = TRANSPORT_INSTANCE(tc);
    RESFILE_Manager *res = TRANSPORT_RES(tc);
    const char *section = TRANSPORT_NAME(tc);

    ITS_C_ASSERT(res != NULL);
    ITS_C_ASSERT(tc != NULL);

    ITS_TRACE_DEBUG(("ParseLinkInfo: processing link information\n"));

    inLink = ITS_FALSE;
    isInterNode = ITS_FALSE;

    haveLC = ITS_FALSE;
    haveLS = ITS_FALSE;
    haveLP = ITS_FALSE;
    haveFamily = ITS_FALSE;

    memset(&link, 0, sizeof(SS7_Link));
    link.initActive = ITS_TRUE;
    link.termFixed = ITS_TRUE;
    link.linkFixed = ITS_TRUE;
    link.isSAAL = ITS_FALSE;
    link.next = NULL;
    link.prev = NULL;

    RESFILE_Lock(res);
    RESFILE_Rewind(res, section);

    while (RESFILE_GetKeyName(res, section,
                              var, sizeof(var)) == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section,
                               val, sizeof(val)) == ITS_SUCCESS)
    {
        /* get the type */
        if (strcmp(var, LINK_INFO_STRING) == 0)
        {
            /* local */
            if (strcmp(val, LINK_BEGIN_STRING) == 0)
            {
                if (inLink)
                {
                    ITS_TRACE_ERROR(("ParseLinkInfo: nested link!\n"));

                    continue;
                }

                inLink = ITS_TRUE;
            }
            /* end of route.  Add it if it's good */
            else if (strcmp(val, LINK_END_STRING) == 0)
            {
                SS7_LinkPtr lp;

                if (!inLink)
                {
                    ITS_TRACE_ERROR(("ParseLinkInfo: end of no link!\n"));

                    continue;
                }

                inLink = ITS_FALSE;

                if (!haveLS || !haveLC || !haveLP || !haveFamily)
                {
                    ITS_TRACE_WARNING(("ParseLinkInfo: Missing link data\n"));

                    /* RESET */
                    haveLC = ITS_FALSE;
                    haveLS = ITS_FALSE;
                    haveLP = ITS_FALSE;

                    memset(&link, 0, sizeof(SS7_Link));
                    link.initActive = ITS_TRUE;
                    link.termFixed = ITS_TRUE;
                    link.linkFixed = ITS_TRUE;

                    continue;
                }

                lp = LINK_FindLink(linkSet, link.linkCode);  
                if (lp != NULL)
                {
                    ITS_TRACE_WARNING(("ParseLinkInfo: LinkSet: %d, LinkCode: %d "
                                     "is already Configured; isInterNode %d\n", 
                                     linkSet, link.linkCode, isInterNode));

                    if (!isInterNode)
                    {
                        lp->dsmNodeId = DSM_GetNodeId();
                        lp->id = instance;
                        LINK_AddLinkInfoToTransport(trans, lp);
                        LINK_CommitLink(lp);
                    }

                   /* save local transport ID, for the duplicated link  */
                    linkTransportMapDB[linkSet][link.linkCode] = instance;  
                }
                else
                {
              
                    /* add the link */
                    link.isUp = ITS_FALSE;
                    link.isAllowed = ITS_TRUE;
                    link.id = instance;
                    link.dsmNodeId = DSM_GetNodeId();
 
                    ITS_TRACE_DEBUG(("ParseLinkInfo: Adding Link LinkSet: %d, "
                                     "LinkCode: %d ; isInterNode %d\n", 
                                      linkSet, link.linkCode, isInterNode));
                    ret = LINK_AddLink(linkSet, &link);
                    if ( (ret != ITS_SUCCESS)  && (ret != ITS_EDUPLENTRY) )
                    {
                        ITS_TRACE_ERROR(("ParseLinkInfo: Can't add link\n"));

                        RESFILE_Unlock(res);

                        return (ret);
                    }

                    lp = LINK_FindLink(linkSet, link.linkCode);  
                    if (lp == NULL)
                    {
                        ITS_TRACE_CRITICAL(("LINK_ParseLinkInfo: Can't find link\n"));
                        RESFILE_Unlock(res);
                        abort();

                        return (ITS_ENOMEM);
                    }

                    /*
                     * InterNode transports MUST NOT build this list
                     * Only build in the case of LOCAL transports
                     */
                    if (!isInterNode)
                    { 
                        LINK_AddLinkInfoToTransport(trans, lp);
                    }
                } 
 
                /* RESET */
                haveLC = ITS_FALSE;
                haveLS = ITS_FALSE;
                haveLP = ITS_FALSE;
                haveFamily = ITS_FALSE;

                memset(&link, 0, sizeof(SS7_Link));
                link.initActive = ITS_TRUE;
                link.termFixed = ITS_TRUE;
                link.linkFixed = ITS_TRUE;
            }
            else
            {
                ITS_TRACE_ERROR(("ParseLinkInfo: unknown link type\n"));

                continue;
            }
        }
        /* check for InterNode transport */
        else if (strcmp(var, INTERNODE_STRING) == 0)
        {
            if (strstr(val, "yes") || strstr(val, "YES"))
            {
                isInterNode = ITS_TRUE;
            }
            else
            {
                isInterNode = ITS_FALSE;
            }
 
        }
        else if (!inLink)
        {
            /* don't know what it is */
            continue;
        }
        else if (strcmp(var, LINKSET_SET_STRING) == 0)
        {
            linkSet = (ITS_OCTET)RESFILE_ParseNum(val);

            haveLS = ITS_TRUE;
        }
        else if (strcmp(var, LINK_CODE_STRING) == 0)
        {
            haveLC = ITS_TRUE;

            link.linkCode = (ITS_OCTET)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, PRIORITY_STRING) == 0)
        {
            haveLP = ITS_TRUE;

            link.priority = (ITS_OCTET)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, LINK_INIT_ACTIVE_STRING) == 0)
        {
            if (strstr(val, "yes") || strstr(val, "YES"))
            {
                link.initActive = ITS_TRUE;
            }
            else
            {
                link.initActive = ITS_FALSE;
            }
        }
        else if (strcmp(var, LINK_TERMINAL_FIXED_STRING) == 0)
        {
            if (strstr(val, "yes") || strstr(val, "YES"))
            {
                link.termFixed = ITS_TRUE;
            }
            else
            {
                link.termFixed = ITS_FALSE;
            }
        }
        else if (strcmp(var, LINK_FIXED_STRING) == 0)
        {
            if (strstr(val, "yes") || strstr(val, "YES"))
            {
                link.linkFixed = ITS_TRUE;
            }
            else
            {
                link.linkFixed = ITS_FALSE;
            }
        }
        else if (strcmp(var, LINK_SAAL_LINK_STRING) == 0)
        {
            if (strstr(val, "yes") || strstr(val, "YES"))
            {
                link.isSAAL = ITS_TRUE;
            }
            else
            {
                link.isSAAL = ITS_FALSE;
            }
        }
        else if (strcmp(var, LINK_LOCAL_STRING) == 0)
        {
            if (strstr(val, "yes") || strstr(val, "YES"))
            {
                link.localLink = ITS_TRUE;
            }
            else
            {
                link.localLink = ITS_FALSE;
            }
        }
        else if (strcmp(var, LINK_TERMINAL_STRING) == 0)
        {
            link.terminal = (ITS_USHORT)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, LINK_DATA_LINK_STRING) == 0)
        {
            link.dataLink = (ITS_USHORT)RESFILE_ParseNum(val);
        }
        else if (strcmp(var, FAMILY_STRING) == 0)
        {
            haveFamily = ITS_TRUE;

            if (strcmp(val, FAMILY_ANSI_STRING) == 0)
            {
                link.family = FAMILY_ANSI;
            }
            else if (strcmp(val, FAMILY_CCITT_STRING) == 0)
            {
                link.family = FAMILY_ITU;
            }
            else if (strcmp(val, FAMILY_CHINA_STRING) == 0)
            {
                link.family = FAMILY_CHINA;
            }
            else if (strcmp(val, FAMILY_JAPAN_STRING) == 0)
            {
                link.family = FAMILY_JAPAN;
            }
        }
    }

    RESFILE_Unlock(res);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Sort the links by priority order
 *
 *  Input Parameters:
 *      l1, l2 - pointers to link information.
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
PriorityOrder(const void *l1, const void *l2)
{
    SS7_LinkPtr *a = (SS7_LinkPtr *)l1;
    SS7_LinkPtr *b = (SS7_LinkPtr *)l2;

    if ((*a)->priority == (*b)->priority)
    {
        return ((int)(*a)->linkCode - (int)(*b)->linkCode);
    }

    return ((int)(*a)->priority - (int)(*b)->priority);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Add a link
 *
 *  Input Parameters:
 *      ls - link set to add to
 *      link - link info to add
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static SS7_LinkPtr
AddOneLink(SS7_LinkSetPtr ls, SS7_LinkPtr link)
{
    SS7_LinkPtr old, lp;
    LINKSET_LinkKey key;
    LINK_Key lkey;
    int error,i;

    memset(&key, 0, sizeof(key));
    memset(&lkey, 0, sizeof(lkey));

    if (ls->family != link->family)
    {
        return (NULL);
    }

    if (ls->numLinks >= ls->maxLinks)
    {
        if (ls->numLinks == 0)
        {
            ls->maxLinks += LINK_SET_GROWTH_FACTOR;

            key.type = MAP_TYPE_LINKS;
            key.linkSet = ls->linkSet;
            key.maxLinks = ls->maxLinks;

            ls->links = (SS7_LinkPtr *)DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                                                       DSM_TABLE_LINK_MAPS,
                                                       (ITS_OCTET *)&key,
                                                       sizeof(LINKSET_LinkKey),
                                                       ls->maxLinks *
                                                        sizeof(SS7_LinkPtr),
                                                       &error);

            if (error != ITS_SUCCESS || ls->links == NULL)
            {
                ITS_TRACE_ERROR(("Alloc error\n"));

                return (NULL);
            }
        }
        else
        {
            ITS_UINT oc;

            key.type = MAP_TYPE_LINKS;
            key.linkSet = ls->linkSet;
            key.maxLinks = ls->maxLinks;
            oc = ls->maxLinks;

            old = (SS7_LinkPtr)DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                              DSM_TABLE_LINK_MAPS,
                                              (ITS_OCTET *)&key,
                                              sizeof(LINKSET_LinkKey),
                                              &error);

            if (error != ITS_SUCCESS || old == NULL)
            {
                ITS_TRACE_ERROR(("Find error\n"));

                return (NULL);
            }

            ls->maxLinks += LINK_SET_GROWTH_FACTOR;
            key.maxLinks = ls->maxLinks;

            ls->links = (SS7_LinkPtr *)DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                                                       DSM_TABLE_LINK_MAPS,
                                                       (ITS_OCTET *)&key,
                                                       sizeof(LINKSET_LinkKey),
                                                       ls->maxLinks *
                                                        sizeof(SS7_LinkPtr),
                                                       &error);

            if (error != ITS_SUCCESS || ls->links == NULL)
            {
                ITS_TRACE_ERROR(("Alloc error\n"));

                return (NULL);
            }

            memcpy(ls->links, old, oc * sizeof(SS7_LinkPtr));

            key.maxLinks = oc;
            DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                           DSM_TABLE_LINK_MAPS,
                           (ITS_OCTET *)&key,
                           sizeof(LINKSET_LinkKey),
                           old);
        }
    }

    lkey.linkSet = ls->linkSet;
    lkey.linkCode = link->linkCode;

    lp = (SS7_LinkPtr)DSM_AllocNoLock(DSM_Mtp3FtGroupId,
                                      DSM_TABLE_LINKS,
                                      (ITS_OCTET *)&lkey,
                                      sizeof(LINK_Key),
                                      sizeof(SS7_Link),
                                      &error);

    if (error != ITS_SUCCESS || lp == NULL)
    {
        ITS_TRACE_ERROR(("ParseLinkInfo: Out of memory!\n"));

        key.type = MAP_TYPE_LINKS;
        key.linkSet = ls->linkSet;
        key.maxLinks = ls->maxLinks;

        DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                         DSM_TABLE_LINK_MAPS,
                         (ITS_OCTET *)&key,
                         sizeof(LINKSET_LinkKey),
                         ls->links);

        return (NULL);
    }

    *lp = *link;

    lp->cocbBuf = DSMQUEUE_Create(ENT_TYPE_COCBBUF, 
                                  ls->linkSet << 4 | link->linkCode);

    if (lp->cocbBuf == NULL)
    {
        ITS_TRACE_ERROR(("ParseLinkInfo: Out of memory!\n"));

        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINKS,
                       (ITS_OCTET *)&lkey,
                       sizeof(LINK_Key),
                       lp);

        DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                         DSM_TABLE_LINK_MAPS,
                         (ITS_OCTET *)&key,
                         sizeof(LINKSET_LinkKey),
                         ls->links);

        return (NULL);
    }

    lp->rtrvBuf = DSMQUEUE_Create(ENT_TYPE_RTRVBUF, 
                                  ls->linkSet << 4 | link->linkCode );

    if (lp->rtrvBuf == NULL)
    {
        ITS_TRACE_ERROR(("ParseLinkInfo: Out of memory!\n"));

        DSMQUEUE_Delete(lp->cocbBuf);

        DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                       DSM_TABLE_LINKS,
                       (ITS_OCTET *)&lkey,
                       sizeof(LINK_Key),
                       lp);

        DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                         DSM_TABLE_LINK_MAPS,
                         (ITS_OCTET *)&key,
                         sizeof(LINKSET_LinkKey),
                         ls->links);

        return (NULL);
    }

    /* Now Initialise Pegs for this Link */
    for (i = 0; i < PEG_MTP3_LINK_NUM_PEGS; i++)
    {
        lp->pegs[i] = 0;
    }
    lp->MTP3_LINK_PEGS.name = "MTP3";
    lp->MTP3_LINK_PEGS.numPegs =
                            sizeof(lp->pegs) / sizeof(ITS_UINT);
    lp->MTP3_LINK_PEGS.pegs = lp->pegs;

    lp->linkSet = ls;
    ls->links[ls->numLinks] = lp;
    ls->lastDown[ls->ldIdx] = ls->numLinks;
    ls->ldIdx++;
    ls->numLinks++;

    sprintf((char *)lp->testPattern, "%cTST", '0' + lp->linkCode);

    if (ls->numLinks > 1)
    {
        qsort(ls->links, ls->numLinks,
              sizeof(SS7_LinkPtr),
              PriorityOrder);
    }

    return (lp);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Add a link
 *
 *  Input Parameters:
 *      ls - link set to add to
 *      link - link info to add
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
RemOneLink(SS7_LinkSetPtr ls, SS7_LinkPtr link)
{
    LINKSET_LinkKey key;
    ITS_UINT i;
    LINK_Key lkey;

    memset(&key, 0, sizeof(key));
    memset(&lkey, 0, sizeof(lkey));

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->linkCode == link->linkCode)
        {
            SS7_LinkPtr ln;

            ITS_C_ASSERT(ls->links[i] == link);

            ln = ls->links[i];

            if (i < (ls->numLinks - 1))
            {
                memmove(&ls->links[i],
                        &ls->links[i + 1],
                        (ls->numLinks - i - 1) * sizeof(SS7_LinkPtr));
            }

            ls->numLinks--;

            ITS_TRACE_DEBUG(("Deleting queue for link %d\n", ln->linkCode));

            if (DSMQUEUE_Delete(ln->cocbBuf) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Fail to delete cocbBuf queue for link %d\n",
                        ln->linkCode));
            }
            if (DSMQUEUE_Delete(ln->rtrvBuf) != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR(("Fail to delete rtrvBuf queue for link %d\n",
                        ln->linkCode));
            }


            lkey.linkSet = ls->linkSet;
            lkey.linkCode = link->linkCode;

            DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                           DSM_TABLE_LINKS,
                           (ITS_OCTET *)&lkey,
                           sizeof(LINK_Key),
                           ln);

            key.type = MAP_TYPE_LINKS;
            key.linkSet = ls->linkSet;
            key.maxLinks = ls->maxLinks;

            if (ls->numLinks == 0)
            {
                ls->maxLinks = 0;
                DSM_FreeNoLock(DSM_Mtp3FtGroupId,
                               DSM_TABLE_LINK_MAPS,
                               (ITS_OCTET *)&key, 
                               sizeof(LINKSET_LinkKey),
                               ls->links);
            }
            else
            {
                DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                                 DSM_TABLE_LINK_MAPS,
                                 (ITS_OCTET *)&key,
                                 sizeof(LINKSET_LinkKey),
                                 ls->links);
            }

            return (ITS_SUCCESS);
        }
    }

    return (ITS_ENOTFOUND);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_AddLink(ITS_OCTET linkSet, SS7_LinkPtr link)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr lp;
    LINKSET_LinkKey key;
    LINK_Key lkey;
    ITS_UINT i;
    int error;

    ITS_TRACE_DEBUG(("AddLink\n"));

    memset(&key, 0, sizeof(key));
    memset(&lkey, 0, sizeof(lkey));

    if (DSM_LockTable(
            DSM_Mtp3FtGroupId, 
            DSM_TABLE_LINK_SETS) == ITS_EBADMUTEX)
    {
        ITS_TRACE_ERROR(("AddRoutingKeyInfo: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(
            DSM_Mtp3FtGroupId, 
            DSM_TABLE_LINK_MAPS) == ITS_EBADMUTEX)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS) == ITS_EBADMUTEX)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EBADMUTEX);
    }

    ls = (SS7_LinkSetPtr)DSM_FindNoLock(DSM_Mtp3FtGroupId, 
                                        DSM_TABLE_LINK_SETS,
                                        &linkSet,
                                        sizeof(ITS_OCTET),
                                        &error);


    if (error != ITS_SUCCESS || ls == NULL)
    {
        ITS_TRACE_WARNING(("AddLink: link set not found\n"));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_ENOTFOUND);
    }

    for (i = 0; i < ls->numLinks; i++)
    {
        /* The first element can be null for
         * dynamically added links.
         */
        if (ls->links[i])
        {
            if (ls->links[i]->linkCode == link->linkCode)
            {
                ITS_TRACE_ERROR(("AddLink: Duplicate link code\n"));

                /* save local transport ID, for the duplicated link  */      
                linkTransportMapDB[ls->linkSet][link->linkCode] = link->id;

                DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
                DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
                DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

                return (ITS_EDUPLENTRY);
        }
        }
    }

    lp = AddOneLink(ls, link);
    if (lp == NULL)
    {
        ITS_TRACE_ERROR(("AddLink: Failed to add link\n"));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EINVALIDARGS);
    }


    InitSLSMap(ls);

    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_SETS,
                     &ls->linkSet,
                     sizeof(ITS_OCTET),
                     ls);

    key.type = MAP_TYPE_LINKS;
    key.linkSet = ls->linkSet;
    key.maxLinks = ls->maxLinks;

    DSM_CommitNoLock(DSM_Mtp3FtGroupId, 
                     DSM_TABLE_LINK_MAPS,
                     (ITS_OCTET *)&key,
                     sizeof(LINKSET_LinkKey),
                     ls->links);

    lkey.linkSet = ls->linkSet;
    lkey.linkCode = lp->linkCode;

    /* save local transport ID  */      
    linkTransportMapDB[ls->linkSet][link->linkCode] = link->id;

    DSM_CommitNoLock(DSM_Mtp3FtGroupId, 
                     DSM_TABLE_LINKS,
                     (ITS_OCTET *)&lkey,
                     sizeof(LINK_Key),
                     lp);
                     
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI SS7_LinkPtr
LINK_FindLink(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    LINKSET_LinkKey key;
    ITS_UINT i;
    int error;

    memset(&key, 0, sizeof(key));

    ITS_TRACE_DEBUG(("FindLink\n"));

    if (DSM_LockTable(
            DSM_Mtp3FtGroupId,
            DSM_TABLE_LINK_SETS) == ITS_EBADMUTEX)
    {
        ITS_TRACE_ERROR(("AddRoutingKeyInfo: couldn't acquire mutex\n"));

        return (NULL);
    }
    if (DSM_LockTable(
            DSM_Mtp3FtGroupId,
            DSM_TABLE_LINK_MAPS) == ITS_EBADMUTEX)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);
        return (NULL);
    }


    ls = DSM_FindNoLock(DSM_Mtp3FtGroupId, 
                        DSM_TABLE_LINK_SETS,
                        &linkSet,
                        sizeof(ITS_OCTET),
                        &error);
    
    if (error != ITS_SUCCESS || ls == NULL)
    {
        ITS_TRACE_WARNING(("FindLink: link set not found\n"));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (NULL);
    }

    key.type = MAP_TYPE_LINKS;
    key.linkSet = ls->linkSet;
    key.maxLinks = ls->maxLinks;

    ls->links =  DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                DSM_TABLE_LINK_MAPS,
                                (ITS_OCTET *)&key,
                                sizeof(LINKSET_LinkKey),
                                &error);

    if (error != ITS_SUCCESS || ls->links == NULL)
    {
        ITS_TRACE_DEBUG(("LINK_FindLink: Find error; cannot find links\n"));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (NULL);
    }

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i])
        { 
            if (ls->links[i]->linkCode == linkCode)
            {
                ln = ls->links[i];

                if( linkTransportMapDB[linkSet][linkCode] == 0)
                {    

                      linkTransportMapDB[linkSet][linkCode]=20002;
                }
                /* populate local data */
                ln->id = linkTransportMapDB[linkSet][linkCode];

                DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
                DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

                return (ln);
            }
        }
    }

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI SS7_LinkPtr
LINK_FindLinkNoLock(ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    SS7_LinkSetPtr ls;
    SS7_LinkPtr ln;
    LINKSET_LinkKey key;
    ITS_UINT i;
    int error;

    memset(&key, 0, sizeof(key));

    ITS_TRACE_DEBUG(("FindLinkNoLock\n"));

    ls = DSM_FindNoLock(DSM_Mtp3FtGroupId, 
                        DSM_TABLE_LINK_SETS,
                        &linkSet,
                        sizeof(ITS_OCTET),
                        &error);
    
    if (error != ITS_SUCCESS || ls == NULL)
    {
        ITS_TRACE_WARNING(("FindLink: link set not found\n"));


        return (NULL);
    }

    key.type = MAP_TYPE_LINKS;
    key.linkSet = ls->linkSet;
    key.maxLinks = ls->maxLinks;

    ls->links =  DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                DSM_TABLE_LINK_MAPS,
                                (ITS_OCTET *)&key,
                                sizeof(LINKSET_LinkKey),
                                &error);

    if (error != ITS_SUCCESS || ls->links == NULL)
    {
        ITS_TRACE_DEBUG(("LINK_FindLink: Find error; cannot find links\n"));


        return (NULL);
    }

    for (i = 0; i < ls->numLinks; i++)
    {
        if (ls->links[i]->linkCode == linkCode)
        {
            ln = ls->links[i];

            /* populate local data */
            ln->id = linkTransportMapDB[linkSet][linkCode];


            return (ln);
        }
    }


    return (NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI ITS_USHORT
LINK_GetTransportId(SS7_LinkPtr link)
{
    if (link == NULL)
    {
        return ITS_NO_SRC;
    }

    if (link->linkSet == NULL)
    {
        return ITS_NO_SRC;
    }

    return linkTransportMapDB[link->linkSet->linkSet][link->linkCode];

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_RemLink(ITS_OCTET linkSet, SS7_LinkPtr link)
{
    SS7_LinkSetPtr ls;
    int error;

    ITS_TRACE_DEBUG(("FindLink\n"));

    if (DSM_LockTable(
            DSM_Mtp3FtGroupId, 
            DSM_TABLE_LINK_SETS) == ITS_EBADMUTEX)
    {
        ITS_TRACE_ERROR(("AddRoutingKeyInfo: couldn't acquire mutex\n"));

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(
            DSM_Mtp3FtGroupId, 
            DSM_TABLE_LINK_MAPS) == ITS_EBADMUTEX)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EBADMUTEX);
    }
    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS) == ITS_EBADMUTEX)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_EBADMUTEX);
    }

    ls = (SS7_LinkSetPtr)DSM_FindNoLock(DSM_Mtp3FtGroupId,
                                        DSM_TABLE_LINK_SETS,
                                        &linkSet,
                                        sizeof(ITS_OCTET),
                                        &error);


    if (error != ITS_SUCCESS || ls == NULL)
    {
        ITS_TRACE_WARNING(("AddLink: link set not found\n"));

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return (ITS_ENOTFOUND);
    }

    /* update the transport's linkInfo list */
    LINK_RemLinkInfoFromTransport(link);

    RemOneLink(ls, link);

    DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                     DSM_TABLE_LINK_SETS,
                     &ls->linkSet,
                     sizeof(ITS_OCTET),
                     ls);


    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_CommitLink(SS7_LinkPtr link)
{
    LINK_Key lkey;

    memset(&lkey, 0, sizeof(lkey));

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS) == ITS_EBADMUTEX)
    {
        return (ITS_EBADMUTEX);
    }
 

    lkey.linkSet = link->linkSet->linkSet;
    lkey.linkCode = link->linkCode;

    DSM_CommitNoLock(DSM_Mtp3FtGroupId, 
                     DSM_TABLE_LINKS,
                     (ITS_OCTET *)&lkey,
                     sizeof(LINK_Key),
                     link);

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Added changes along with code change
 *                                       propagated in UAL to fix removal of
 *                                       link when Inactive ASP goes down but
 *                                       Active ASP is still up (ASP in red) 
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LINK_CommitLinkNoLock(SS7_LinkPtr link)
{
    LINK_Key lkey;
    int ret;

    memset(&lkey, 0, sizeof(lkey));

    lkey.linkSet = link->linkSet->linkSet;
    lkey.linkCode = link->linkCode;

    ret =  DSM_CommitNoLock(DSM_Mtp3FtGroupId,
                            DSM_TABLE_LINKS,
                            (ITS_OCTET *)&lkey,
                            sizeof(LINK_Key),
                            link);

    return ret;

}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Added changes along with code change
 *                                       propagated in UAL to fix removal of
 *                                       link when Inactive ASP goes down but
 *                                       Active ASP is still up (ASP in red)
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LINK_LockTables()
{
    int ret;

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

#if 0

    ret = DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);

    if (ret != ITS_SUCCESS)
    {
        return ret;
    }


    ret = DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);
    if (ret != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
        return ret;
    }

    ret = DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    if (ret != ITS_SUCCESS)
    {
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);
        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
    }
#endif
    /*ROUTE_UnlockWrite(routeRWLock);*/

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 807      Added changes along with code change
 *                                       propagated in UAL to fix removal of
 *                                       link when Inactive ASP goes down but
 *                                       Active ASP is still up (ASP in red)
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
LINK_UnlockTables()
{
    int ret;
#if 0
    ret = DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_MAPS);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("UnlockTables: Fail to unlock LINK MAPS Table\n"));
    }
    ret = DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("UnlockTables: Fail to unlock LINK SETS Table\n"));
    }
    ret = DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINKS);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("UnlockTables: Fail to unlock LINK  Table\n"));
    }

#endif

    ROUTE_UnlockWrite(routeRWLock);

    return ITS_SUCCESS;

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_SetLinkState(SS7_LinkPtr link, ITS_BOOLEAN isUp)
{
    ITS_UINT i;
    LINKSET_LinkKey key;
    ITS_BOOLEAN up = ITS_FALSE;

    memset(&key, 0, sizeof(key));
    key.type = MAP_TYPE_LINKS;
    key.linkSet = link->linkSet->linkSet;
    key.maxLinks = link->linkSet->maxLinks;

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    link->isUp = isUp;

    up = ITS_FALSE;

    for (i = 0; i < link->linkSet->numLinks; i++)
    {
        if (link->linkSet->links[i]->isUp)
        {
            up = ITS_TRUE;
        }
    }

    LINK_CommitLink(link);

    LINKSET_SetLinkSetState(link->linkSet, up);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_SetLinkQPut(SS7_LinkPtr link, ITS_BOOLEAN isQ)
{
    LINKSET_LinkKey key;

    memset(&key, 0, sizeof(key));
    key.type = MAP_TYPE_LINKS;
    key.linkSet = link->linkSet->linkSet;
    key.maxLinks = link->linkSet->maxLinks;

    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    link->qPut = isQ;

    LINK_CommitLink(link);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_GetLinkState(SS7_LinkPtr link, ITS_BOOLEAN *isUp)
{
    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (isUp)
    {
        *isUp = link->isUp;
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_SetLinkStatus(SS7_LinkPtr link, ITS_BOOLEAN isAllowed)
{
    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    link->isAllowed = isAllowed;

    LINK_CommitLink(link);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_GetLinkStatus(SS7_LinkPtr link, ITS_BOOLEAN *isAllowed)
{
    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (isAllowed)
    {
        *isAllowed = link->isAllowed;
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_SetLinkCongestion(SS7_LinkPtr link, ITS_OCTET congLevel)
{
    if (ROUTE_LockForWrite(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    link->congLevel = congLevel;

    LINK_CommitLink(link);

    ROUTE_UnlockWrite(routeRWLock);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
ITSDLLAPI int
LINK_GetLinkCongestion(SS7_LinkPtr link, ITS_OCTET *congLevel)
{
    if (ROUTE_LockForRead(routeRWLock) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    if (congLevel)
    {
        *congLevel = link->congLevel;
    }

    ROUTE_UnlockRead(routeRWLock, NULL);

    return (ITS_SUCCESS);
}

/****************************************************************************
 *
 * Link hashtable dump.
 *
 ****************************************************************************/

/* Local contants. */

#define PRINT_DATA_MAX_SIZE     16384
#define HEADER_MAX_SIZE         512
#define FOOTER_MAX_SIZE         256
#define PRINT_BUF_MAX_SIZE      128 

#define YES_NO(x) (x ? "yes" : "no")

#define FAMILY_STR(x) ( (x==FAMILY_ANSI) ? "ANSI"  :   \
                          ((x==FAMILY_ITU)  ? "ITU" : \
                            ((x==FAMILY_CHINA)  ? "CHINA" : \
                              ((x==FAMILY_JAPAN)  ? "JAPAN" : "UNKNOWN") )))

#define AVAILABLE_STR(x) ( (x==LINK_UNAVAILABLE) ? "LINK_UNAVAILABLE" : \
                             ((x==LINK_AVAILABLE) ? "LINK_AVAILABLE" : \
                               "UNKNOWN"))

static void
PrintMap(SS7_LinkSetPtr ls, char *pStrDump, ITS_OCTET *map)
{
    char printBuf[PRINT_BUF_MAX_SIZE];
    ITS_UINT i, j;
    int printComma = 0;

    for (i = 0; i < ls->numLinks; i++)
    {
        sprintf(printBuf, "Link %2d: ", i);
        strcat(pStrDump, printBuf);

        for (j = 0; j < SLS_8BIT_ARRAY_SIZE; j++)
        {
            if (map[j] == i)
            {
                if (printComma)
                {
                    strcat(pStrDump, ",");
                }

                sprintf(printBuf, "%3d", j);
                strcat(pStrDump, printBuf);

                printComma = 1;
            }
        }

        strcat(pStrDump, "\n");

        printComma = 0;
    }

    strcat(pStrDump, "\n");
}

/* Hashtable entries dump functions. */
static int
DumpEntryDataLinkSets(ITS_POINTER data, char** pStrDump)
{
    char printBuf[PRINT_BUF_MAX_SIZE];
    ITS_UINT i;
    SS7_LinkSetPtr ss7Context = (SS7_LinkSetPtr)data;

    *pStrDump = (char *)malloc(PRINT_DATA_MAX_SIZE);
    **pStrDump = 0;

    if (*pStrDump == NULL)
    {
        return ITS_ENOMEM;
    }

    if (ss7Context)
    {
        strcat(*pStrDump, "------------------------------\n");

        /* linkSet */
        sprintf(printBuf, "linkSet   :   %d\n", ss7Context->linkSet);
        strcat(*pStrDump, printBuf);

        /* family */
        sprintf(printBuf, "family   :   %s\n", FAMILY_STR(ss7Context->family));
        strcat(*pStrDump, printBuf);

        /* adjacent */
        sprintf(printBuf, "adjPC     :   %d\n", ss7Context->adjacent);
        strcat(*pStrDump, printBuf);

        /* local */
        sprintf(printBuf, "localPC   :   %d\n", ss7Context->lpc);
        strcat(*pStrDump, printBuf);

        /* numLinks */
        sprintf(printBuf, "numLinks  :   %d\n", ss7Context->numLinks);
        strcat(*pStrDump, printBuf);

        /* numToStart */
        sprintf(printBuf, "numToStart:   %d\n", ss7Context->numToStart);
        strcat(*pStrDump, printBuf);

        /* adjSTP */
        sprintf(printBuf, "adjSTP    :   %s\n", YES_NO(ss7Context->adjSTP));
        strcat(*pStrDump, printBuf);

        /* isC */
/*
        sprintf(printBuf, "bit rotate:   %d\n", YES_NO(ss7Context->isC));
        strcat(*pStrDump, printBuf);
*/

        /* is5Bit */
        sprintf(printBuf, "is5Bit    :   %s\n", YES_NO(ss7Context->is5Bit));
        strcat(*pStrDump, printBuf);

        /* NI */
        sprintf(printBuf, "NI        :   0x%02x\n", ss7Context->ni);
        strcat(*pStrDump, printBuf);

        /* isUp */
        sprintf(printBuf, "isUp      :   %s\n", YES_NO(ss7Context->isUp));
        strcat(*pStrDump, printBuf);

        for (i = 0; i < ss7Context->numLinks; i++)
        {

            SS7_LinkPtr  link = NULL ;

            link = LINK_FindLinkNoLock(ss7Context->linkSet, ss7Context->links[i]
->linkCode);

            if (link == NULL)
            {
                continue;
            }
            strcat(*pStrDump, "------------------------------\n");

            /* linkCode */
            sprintf(printBuf, "linkCode  :   %08x\n", link->linkCode);
            strcat(*pStrDump, printBuf);

            /* family */
            sprintf(printBuf, "family  :   %s\n", FAMILY_STR(link->family));
            strcat(*pStrDump, printBuf);

            /* initActive */
            sprintf(printBuf, "initActive:   %s\n", YES_NO(link->initActive));
            strcat(*pStrDump, printBuf);

            /* termFixed */
            sprintf(printBuf, "termFixed :   %s\n", YES_NO(link->termFixed));
            strcat(*pStrDump, printBuf);

            /* linkFixed */
            sprintf(printBuf, "linkFixed :   %s\n", YES_NO(link->linkFixed));
            strcat(*pStrDump, printBuf);

            /* isSAAL */
            sprintf(printBuf, "isSAAL    :   %s\n", YES_NO(link->isSAAL));
            strcat(*pStrDump, printBuf);

            /* localLink */
            sprintf(printBuf, "localLink :   %s\n", YES_NO(link->localLink));
            strcat(*pStrDump, printBuf);

            /* priority */
            sprintf(printBuf, "priority  :   %d\n", link->priority);
            strcat(*pStrDump, printBuf);

            /* id */
            sprintf(printBuf, "trans id  :   %d\n", link->id);
            strcat(*pStrDump, printBuf);

            /* terminal */
            sprintf(printBuf, "terminal  :   %d\n", link->terminal);
            strcat(*pStrDump, printBuf);

            /* dataLink */
            sprintf(printBuf, "dataLink  :   %d\n", link->dataLink);
            strcat(*pStrDump, printBuf);

            /* isUp */
            sprintf(printBuf, "isUp      :   %s\n", YES_NO(link->isUp));
            strcat(*pStrDump, printBuf);

            /* isAllowed */
            sprintf(printBuf, "isAllowed :   %s\n", YES_NO(link->isAllowed));
            strcat(*pStrDump, printBuf);

            /* active */
            sprintf(printBuf, "active    :   %s\n", YES_NO(link->active));
            strcat(*pStrDump, printBuf);

            /* congLevel */
            sprintf(printBuf, "congLevel :   %d\n", link->congLevel);
            strcat(*pStrDump, printBuf);

            strcat(*pStrDump, "--------- MTP3 STATUS --------\n");

            /* availableState */
            sprintf(printBuf, "state     :   %s\n",
                    AVAILABLE_STR(link->availableState));
            strcat(*pStrDump, printBuf);

            /* local inhibited */
            sprintf(printBuf, "loc inh   :   %s\n",
                    YES_NO(link->stFlags & LINK_LOC_INHIBITED));
            strcat(*pStrDump, printBuf);

            /* remote inhibited */
            sprintf(printBuf, "rem inh   :   %s\n",
                    YES_NO(link->stFlags & LINK_REM_INHIBITED));
            strcat(*pStrDump, printBuf);

            /* link failed */
            sprintf(printBuf, "failed    :   %s\n",
                    YES_NO(link->stFlags & LINK_FAILED));
            strcat(*pStrDump, printBuf);

            /* link locally blocked */
            sprintf(printBuf, "LPO       :   %s\n",
                    YES_NO(link->stFlags & LINK_LOC_BLOCKED));
            strcat(*pStrDump, printBuf);

            /* link remotely blocked */
            sprintf(printBuf, "RPO       :   %s\n",
                    YES_NO(link->stFlags & LINK_REM_BLOCKED));
            strcat(*pStrDump, printBuf);

            /* test passed */
            sprintf(printBuf, "SLT Passed:   %s\n", YES_NO(link->testPassed));
            strcat(*pStrDump, printBuf);

            strcat(*pStrDump, "------------------------------\n");
        }
    }

    PrintMap(ss7Context, *pStrDump, ss7Context->codeMap);
    PrintMap(ss7Context, *pStrDump, ss7Context->defaultMap);

    return ITS_SUCCESS;
}


/*****************************
 * LINKSET_DumpLinkSetHashtable.
 *****************************/
ITSDLLAPI int 
LINKSET_DumpLinkSetHashtable(char** pStrDump)
{
    char header[HEADER_MAX_SIZE];
    char footer[FOOTER_MAX_SIZE];
    char printBuf[PRINT_BUF_MAX_SIZE];
    ITS_UINT vtableSize = 0;
    char* strDumpEntries = NULL;
    int sigma;
    int res;

    ITS_TRACE_DEBUG(("ROUTE_DumpSS7ToId:\n"));

    memset(header, 0, HEADER_MAX_SIZE);
    memset(footer, 0, FOOTER_MAX_SIZE);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    *pStrDump = NULL;

    if (DSM_LockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("ROUTE_DumpSS7ToId: couldn't acquire lock\n"));

        return (ITS_EBADMUTEX);
    }

    strcat(header, "--------------------------------------------------\n");
    strcat(header, "-- LinkSet Hashtable Begin --\n");
    strcat(header, "--------------------------------------------------\n");
    strcat(header, "Size: <");

    DSM_TableGetSize(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS, &vtableSize);
    sprintf(printBuf, "%u", vtableSize);
    strcat(header, printBuf);
    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    strcat(header, ">\n");
    strcat(header, "--------------------------------------------------\n");

    res = DSM_TableDump(DSM_Mtp3FtGroupId,
                        DSM_TABLE_LINK_SETS,
                        &strDumpEntries,
                        DumpEntryDataLinkSets);

    if (res != ITS_SUCCESS)
    {
        if (strDumpEntries != NULL)
        {
            free(strDumpEntries);
        }

        DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

        return res;
    }

    DSM_UnlockTable(DSM_Mtp3FtGroupId, DSM_TABLE_LINK_SETS);

    strcat(footer, "--------------------------------------------------\n");
    strcat(footer, "-- LinkSet Hashtable End --\n");
    strcat(footer, "--------------------------------------------------\n");

    sigma = strlen(header) + strlen(strDumpEntries) + strlen(footer);

    *pStrDump = (char *)calloc(sigma + 1, sizeof(char));

    if (*pStrDump == NULL)
    {
        free(strDumpEntries);

        return ITS_ENOMEM;
    }

    strcat(*pStrDump, header);
    strcat(*pStrDump, strDumpEntries);
    strcat(*pStrDump, footer);

    free(strDumpEntries);

    return ITS_SUCCESS;
}

/*****************************
 * LINK_DumpLinkInfo
 *****************************/
ITSDLLAPI int
LINK_DumpLinkInfo(char **pStrDump, ITS_OCTET linkSet, ITS_OCTET linkCode)
{
    char printBuf[PRINT_BUF_MAX_SIZE];
    ITS_UINT vtableSize = 0;
    SS7_LinkPtr  link = NULL ;
    int res;


    memset(printBuf, 0, PRINT_BUF_MAX_SIZE);

    *pStrDump = (char *)malloc(PRINT_DATA_MAX_SIZE);
    **pStrDump = 0;



    link = LINK_FindLinkNoLock(linkSet, linkCode);

    if (link == NULL)
    {
        sprintf(printBuf, "link %d on link set %d is not configured\n",
                           linkCode, linkSet);
        strcat(*pStrDump, printBuf);
        return ITS_ENOMEM;
    }

    strcat(*pStrDump, "--------- LINK INFO ----------\n");

    /* linkCode */
    sprintf(printBuf, "linkCode  :   %08x\n", link->linkCode);
    strcat(*pStrDump, printBuf);

    /* family */
    sprintf(printBuf, "family  :   %s\n", FAMILY_STR(link->family));
    strcat(*pStrDump, printBuf);

    /* initActive */
    sprintf(printBuf, "initActive:   %s\n", YES_NO(link->initActive));
    strcat(*pStrDump, printBuf);

    /* termFixed */
    sprintf(printBuf, "termFixed :   %s\n", YES_NO(link->termFixed));
    strcat(*pStrDump, printBuf);

    /* linkFixed */
    sprintf(printBuf, "linkFixed :   %s\n", YES_NO(link->linkFixed));
    strcat(*pStrDump, printBuf);

    /* isSAAL */
    sprintf(printBuf, "isSAAL    :   %s\n", YES_NO(link->isSAAL));
    strcat(*pStrDump, printBuf);
    /* localLink */
    sprintf(printBuf, "localLink :   %s\n", YES_NO(link->localLink));
    strcat(*pStrDump, printBuf);

    /* priority */
    sprintf(printBuf, "priority  :   %d\n", link->priority);
    strcat(*pStrDump, printBuf);

    /* id */
    sprintf(printBuf, "trans id  :   %d\n", link->id);
    strcat(*pStrDump, printBuf);

    /* terminal */
    sprintf(printBuf, "terminal  :   %d\n", link->terminal);
    strcat(*pStrDump, printBuf);

    /* dataLink */
    sprintf(printBuf, "dataLink  :   %d\n", link->dataLink);
    strcat(*pStrDump, printBuf);

    /* isUp */
    sprintf(printBuf, "isUp      :   %s\n", YES_NO(link->isUp));
    strcat(*pStrDump, printBuf);

    /* isAllowed */
    sprintf(printBuf, "isAllowed :   %s\n", YES_NO(link->isAllowed));
    strcat(*pStrDump, printBuf);

    /* active */
    sprintf(printBuf, "active    :   %s\n", YES_NO(link->active));
    strcat(*pStrDump, printBuf);

    /* congLevel */
    sprintf(printBuf, "congLevel :   %d\n", link->congLevel);
    strcat(*pStrDump, printBuf);

    strcat(*pStrDump, "--------- MTP3 STATUS --------\n");

    /* availableState */
    sprintf(printBuf, "state     :   %s\n",
            AVAILABLE_STR(link->availableState));
    strcat(*pStrDump, printBuf);

    /* local inhibited */
    sprintf(printBuf, "loc inh   :   %s\n",
            YES_NO(link->stFlags & LINK_LOC_INHIBITED));
    strcat(*pStrDump, printBuf);

    /* remote inhibited */
    sprintf(printBuf, "rem inh   :   %s\n",
            YES_NO(link->stFlags & LINK_REM_INHIBITED));
    strcat(*pStrDump, printBuf);
    /* link failed */
    sprintf(printBuf, "failed    :   %s\n",
            YES_NO(link->stFlags & LINK_FAILED));
    strcat(*pStrDump, printBuf);

    /* link locally blocked */
    sprintf(printBuf, "LPO       :   %s\n",
            YES_NO(link->stFlags & LINK_LOC_BLOCKED));

    /* link remotely blocked */
    sprintf(printBuf, "RPO       :   %s\n",
            YES_NO(link->stFlags & LINK_REM_BLOCKED));
    strcat(*pStrDump, printBuf);

    /* test passed */
    sprintf(printBuf, "SLT Passed:   %s\n", YES_NO(link->testPassed));
    strcat(*pStrDump, printBuf);

    strcat(*pStrDump, "------------------------------\n");


    return ITS_SUCCESS;

}



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function initializes the linkset subsystem to a ready state.
 *      The routing subsystem will not work correctly if this funtion is
 *      not invoked first.
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
 *      If the routing subsystem is initialized correctly, ITS_SUCCESS is
 *          returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      LINKSET_Terminate()
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    RESFILE_Manager *globalRes = NULL;
    const char *name = APPL_GetConfigFileName();

    ITS_TRACE_DEBUG(("LINKSET_Initialize:\n"));

    /* get resources */
    globalRes = RESFILE_CreateResourceManager(name);

    /* Initialize ROUTE Reader/Writer lock */
    if ( (routeRWLock = ROUTE_RWLockCreate() ) == NULL)
    {
        ITS_TRACE_ERROR(("Cannot Create ROUTE Reader/Writer Lock."));
        return ITS_ENOMEM;
    }

    return LINKSET_ParseLinkSetInfo(globalRes, NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function terminates the routing subystem.  It frees all resources
 *      that have been allocated for routing.
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
 *      This function must NOT be called until all link entities have
 *      terminated.
 *
 *  See Also:
 *      LINKSET_Initialize()
 ****************************************************************************/
static void
ClassTerminate(ITS_Class objClass)
{
    ITS_TRACE_DEBUG(("LINKSET_Terminate:\n"));

    /* this gets rid of routes and link sets. */
    LINKSET_DeleteLinkSetInfo();
}

/*
 * the class record
 */
ITSDLLAPI LINKSET_ClassRec itsLINKSET_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        LINKSET_CLASS_NAME,               /* class name */
        ClassInitialize,                /* class init */
        ClassTerminate,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};
 
ITSDLLAPI ITS_Class itsLINKSET_Class = (ITS_Class)&itsLINKSET_ClassRec;
