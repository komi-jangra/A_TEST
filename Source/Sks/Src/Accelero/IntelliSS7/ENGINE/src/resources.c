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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:44  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/24 05:46:47  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.4  2007/08/02 06:08:15  ashutosh.singh
 * LOG: change for concerned route addition (rt_add command )
 * LOG:
 * LOG: Revision 1.3  2007/07/20 06:03:15  ashutosh.singh
 * LOG: change for run time configuration at mtp2
 * LOG:
 * LOG: Revision 1.2  2007/04/20 08:36:50  ashutosh.singh
 * LOG: ln_add command chg due to time slot
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:33:43  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2.2.1  2005/08/29 09:21:53  adutta
 * LOG: BSSAP configuration
 * LOG:
 * LOG: Revision 9.2  2005/05/13 11:11:37  adutta
 * LOG: Fixed Bug# 1776/1792
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:49:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.9  2005/01/19 11:01:50  adutta
 * LOG: Retreiving M2UA data from xml
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.8  2005/01/17 09:52:08  mkrishna
 * LOG: separate traces for SIP
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.7  2005/01/11 13:16:19  craghavendra
 * LOG: Finish Up Syslog Enhancements.
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.6  2005/01/05 07:21:23  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.5  2005/01/04 13:46:45  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.4  2005/01/03 14:53:41  snagesh
 * LOG: Modifications for MTP2 vendor traces
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.3  2004/12/28 13:12:10  mkrishna
 * LOG: SIP code propagated from Current Branch
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.2  2004/12/16 01:48:59  randresol
 * LOG: Add JAPAN variant Implementation
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.12.1  2004/12/15 12:55:32  asingh
 * LOG: separate traces for SCTP/UAL/M3UA
 * LOG:
 * LOG: Revision 7.3.2.5.6.1.8.1  2004/10/25 20:39:56  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.3.2.5.6.1  2004/07/09 07:29:08  dsatish
 * LOG: Merging activity for timeslot & 56kbsps changes
 * LOG:
 * LOG: Revision 7.3.2.5  2003/05/07 08:28:14  ssingh
 * LOG: ISUP related changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 7.3.2.4  2003/04/10 16:05:07  randresol
 * LOG: Verify the existence of the Linkset before adding/delete the route
 * LOG:
 * LOG: Revision 7.3.2.3  2003/04/07 19:44:39  randresol
 * LOG: fix bug in ln_add
 * LOG:
 * LOG: Revision 7.3.2.2  2003/04/07 08:11:38  randresol
 * LOG: Add MML Commands for LINK/LINKSET subsystem
 * LOG:
 * LOG: Revision 7.3.2.1  2003/03/28 15:50:10  randresol
 * LOG: Add Debug Console command for the ROUTE System
 * LOG:
 * LOG: Revision 7.3  2003/01/09 11:28:19  yranade
 * LOG: Avoid a core dump, which otherwise happening if the variables are not
 * LOG: defined in the XML file
 * LOG:
 * LOG: Revision 7.2  2002/12/31 09:04:53  akumar
 * LOG: Code to Parse the XML file and dump it in DMP file for variables
 * LOG: exchange_type and segmentation_supported
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:41  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.26  2002/08/26 21:13:29  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.25  2002/08/22 20:49:11  ngoel
 * LOG: Add default case while populating stack trace levels
 * LOG:
 * LOG: Revision 6.24  2002/08/22 14:32:43  mmiers
 * LOG: Add china dispatchers
 * LOG:
 * LOG: Revision 6.23  2002/08/16 16:08:10  mmiers
 * LOG: Get the section name for ISUP attrs right
 * LOG:
 * LOG: Revision 6.22  2002/08/01 19:16:08  mmiers
 * LOG: Get the pool in there
 * LOG:
 * LOG: Revision 6.21  2002/07/31 16:10:10  ngoel
 * LOG: add b_getborders MML command
 * LOG:
 * LOG: Revision 6.20  2002/07/30 18:56:39  mmiers
 * LOG: Fixup
 * LOG:
 * LOG: Revision 6.19  2002/07/30 18:29:47  mmiers
 * LOG: Set instance number, add resources
 * LOG:
 * LOG: Revision 6.18  2002/07/30 16:52:56  mmiers
 * LOG: Avoid a core dump
 * LOG:
 * LOG: Revision 6.17  2002/07/30 16:11:22  ngoel
 * LOG: correct sscanf call in console function
 * LOG:
 * LOG: Revision 6.16  2002/07/23 20:27:25  mmiers
 * LOG: Rename the commands for consistency
 * LOG:
 * LOG: Revision 6.15  2002/07/23 16:56:33  mmiers
 * LOG: Complete addborder framework
 * LOG:
 * LOG: Revision 6.14  2002/07/10 20:11:14  mmiers
 * LOG: Don't delay create for task queues as borders
 * LOG:
 * LOG: Revision 6.13  2002/07/05 22:24:12  yranade
 * LOG: Fix flag bug.
 * LOG:
 * LOG: Revision 6.12  2002/07/05 14:47:59  yranade
 * LOG: Missing cast in malloc.
 * LOG:
 * LOG: Revision 6.11  2002/07/02 21:26:36  mmiers
 * LOG: Work on getting debug console interface added to engine.
 * LOG:
 * LOG: Revision 6.10  2002/06/21 22:49:20  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.9  2002/06/14 21:52:15  sjaddu
 * LOG: Commited with correct version of file.
 * LOG:
 * LOG: Revision 6.7  2002/06/05 19:19:14  mmiers
 * LOG: Duplicated have the same issues as concerned
 * LOG:
 * LOG: Revision 6.6  2002/06/03 16:44:14  mmiers
 * LOG: Get the prefix right.
 * LOG:
 * LOG: Revision 6.5  2002/05/31 20:42:05  mmiers
 * LOG: Fixes for concerned routes
 * LOG:
 * LOG: Revision 6.4  2002/05/20 15:24:39  sjaddu
 * LOG: Merge from PR6 to current.
 * LOG:
 * LOG: Revision 6.3  2002/05/07 14:51:14  wweng
 * LOG: Add output for missing features.
 * LOG:
 * LOG: Revision 6.2  2002/04/29 21:39:20  randresol
 * LOG: Add isInterNode flag in Border Transports definition
 * LOG:
 * LOG: Revision 6.1.2.1  2002/04/18 19:05:04  randresol
 * LOG: Add "isInterNode" field in Border Transports configuration
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.20.2.1  2002/03/22 17:29:58  ssharma
 * LOG: Fix the ISUP Attributes section.
 * LOG:
 * LOG: Revision 5.20  2002/02/14 15:58:21  mmiers
 * LOG: Correct ISUP attrs
 * LOG:
 * LOG: Revision 5.19  2002/02/12 23:30:08  mmiers
 * LOG: ISUP parser in place
 * LOG:
 * LOG: Revision 5.18  2002/01/21 20:27:21  mmiers
 * LOG: Add distribution awareness.
 * LOG:
 * LOG: Revision 5.17  2002/01/10 20:30:36  mmiers
 * LOG: Add SAAL capability
 * LOG:
 * LOG: Revision 5.16  2001/11/09 16:54:35  mmiers
 * LOG: Mark mempool init as potentially removable.
 * LOG:
 * LOG: Revision 5.15  2001/11/08 01:16:21  mmiers
 * LOG: Add PC/NI strings
 * LOG:
 * LOG: Revision 5.14  2001/10/19 22:45:12  mmiers
 * LOG: Use strings for variant names.
 * LOG:
 * LOG: Revision 5.13  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.12  2001/10/18 21:33:40  mmiers
 * LOG: Update engine to use destinations.
 * LOG:
 * LOG: Revision 5.11  2001/10/17 00:56:57  mmiers
 * LOG: Remove SLS stuff from engine.
 * LOG:
 * LOG: Revision 5.10  2001/10/02 21:44:10  mmiers
 * LOG: Dead route style removal.
 * LOG:
 * LOG: Revision 5.9  2001/09/24 21:37:17  mmiers
 * LOG: ENGINE link, linkSet, C++ API.
 * LOG:
 * LOG: Revision 5.8  2001/09/05 00:03:56  mmiers
 * LOG: Add new case values.
 * LOG:
 * LOG: Revision 5.7  2001/08/31 14:23:10  mmiers
 * LOG: Brainstorming on MTP3, routing fixes.
 * LOG:
 * LOG: Revision 5.6  2001/08/29 17:26:54  mmiers
 * LOG: Add maskable routing.  Bug fix for SCTP clients.  Abort if
 * LOG: timer context too large.
 * LOG:
 * LOG: Revision 5.5  2001/08/24 17:10:25  mmiers
 * LOG: Routing, take three.
 * LOG:
 * LOG: Revision 5.4  2001/08/20 23:28:40  mmiers
 * LOG: Finish route work.
 * LOG:
 * LOG: Revision 5.3  2001/08/20 22:50:54  mmiers
 * LOG: Get this in line with new routing scheme.
 * LOG:
 * LOG: Revision 5.2  2001/08/20 19:08:56  mmiers
 * LOG: Initialize mempool
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.9  2001/08/13 21:04:42  mmiers
 * LOG: Fix type bug.
 * LOG:
 * LOG: Revision 4.8  2001/08/13 20:42:00  mmiers
 * LOG: Add routing key.
 * LOG:
 * LOG: Revision 4.7  2001/08/10 18:54:18  pkelly
 * LOG: Add routes even if we don't have transport specifics
 * LOG:
 * LOG: Revision 4.6  2001/07/26 18:10:32  mmiers
 * LOG: Diff, version 1.
 * LOG:
 * LOG: Revision 4.5  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.4  2001/07/19 22:02:40  mmiers
 * LOG: Continue adding equality checks.
 * LOG:
 * LOG: Revision 4.3  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 16:51:44  mmiers
 * LOG: User requested stuff (user intervention).
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.1  2001/04/28 23:38:20  mmiers
 * LOG: Rearrange this to standard form.
 * LOG:
 * LOG: Revision 1.2  2001/04/19 19:21:51  labuser
 * LOG: Debug.  Need to supply resources even for ITER
 * LOG:
 * LOG: Revision 1.1  2001/04/12 20:10:26  salaoui
 * LOG: Move to a more logical location.
 * LOG:
 * LOG: Revision 1.10  2001/04/12 19:13:41  labuser
 * LOG: Debugging with Yogesh.
 * LOG:
 * LOG: Revision 1.9  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 1.8  2001/04/04 01:30:07  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.7  2001/04/04 01:15:23  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.6  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.5  2001/04/03 17:45:42  mmiers
 * LOG: Fix some major engine bugs.
 * LOG:
 * LOG: Revision 1.4  2001/03/28 23:37:42  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.3  2001/03/28 22:38:29  mmiers
 * LOG: It is coded.
 * LOG:
 * LOG: Revision 1.2  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 1.1  2001/03/16 23:18:46  mmiers
 * LOG: Ok, everything done but the parser.
 * LOG:
 *
 ****************************************************************************/

/*
 * this is defined in a stack header file.  Oh, well.
 */
#define VARIANT_STRING  "variant"

/*
 * so are these.
 */
#define ISUP_CIC_RULE_STR       "cicRule"
#define ISUP_START_CIC_STR      "startCic"
#define ISUP_NUM_CICS_STR       "numberCics"

/*change due to inform the ln_add or ln_del commamd to mtp2*/

#define ln_add_cmd  0x1a;
#define ln_del_cmd  0x1b;
extern ITS_OCTET ENTRYDONE;
extern ITS_OCTET ENTRYDELETE;

/*end */


/*
 * assigning numbers
 */
static ITS_USHORT       currentInstance = ITS_FIRST_USER_SRC;
static ITS_USHORT       lastWorker, lastWorkItem, lastBorder;


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      process one link.
 *
 ****************************************************************************/
static void
ProcessOneLink(ITS_Object link, char *section)
{
    char tmp[ITS_PATH_MAX];
    int ret;

    ret = RESFILE_AddKeyValue(appRes, section,
                              LINK_INFO_STRING,
                              LINK_BEGIN_STRING);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_LN_SET(link));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LINKSET_SET_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_LN_CODE(link));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LINK_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_LN_FAMILY(link) == FAMILY_ANSI)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_ANSI_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_LN_FAMILY(link) == FAMILY_ITU)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CCITT_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_LN_FAMILY(link) == FAMILY_CHINA)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CHINA_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_LN_FAMILY(link) == FAMILY_JAPAN)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_JAPAN_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    sprintf(tmp, "%d", ENGINE_LN_PRI(link));
    ret = RESFILE_AddKeyValue(appRes, section,
                              PRIORITY_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_LN_INIT_ACTIVE(link))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_INIT_ACTIVE_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_INIT_ACTIVE_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (ENGINE_LN_TERM_FIXED(link))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_TERMINAL_FIXED_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_TERMINAL_FIXED_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (ENGINE_LN_LINK_FIXED(link))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_FIXED_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_FIXED_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (ENGINE_LN_IS_SAAL(link))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_SAAL_LINK_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_SAAL_LINK_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    if (ENGINE_LN_IS_LOCAL(link))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_LOCAL_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINK_LOCAL_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }


    sprintf(tmp, "%d", ENGINE_LN_TERMINAL(link));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LINK_TERMINAL_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_LN_CIRCUIT(link));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LINK_DATA_LINK_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(appRes, section,
                              LINK_INFO_STRING,
                              LINK_END_STRING);
    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      process one route.
 *
 ****************************************************************************/
static void
ProcessOneLinkSet(ITS_Object linkSet)
{
    char *section = NULL;   /* global section info */
    char tmp[ITS_PATH_MAX];
    int ret;

    ret = RESFILE_AddKeyValue(appRes, section,
                              LINKSET_INFO_STRING,
                              LINKSET_BEGIN_STRING);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "0x%08x", ENGINE_LS_ADJ(linkSet));
    ret = RESFILE_AddKeyValue(appRes, section,
                              ADJ_POINT_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "0x%08x", ENGINE_LS_LOC(linkSet));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LOCAL_POINT_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_LS_ID(linkSet));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LINKSET_SET_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "0x%02x", ENGINE_LS_NI(linkSet));
    ret = RESFILE_AddKeyValue(appRes, section,
                              NI_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_LS_FAMILY(linkSet) == FAMILY_ANSI)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_ANSI_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_LS_FAMILY(linkSet) == FAMILY_ITU)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CCITT_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_LS_FAMILY(linkSet) == FAMILY_CHINA)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CHINA_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_LS_FAMILY(linkSet) == FAMILY_JAPAN)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_JAPAN_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    sprintf(tmp, "%d", ENGINE_LS_NUM_TO_START(linkSet));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LINKSET_NUM_TO_START_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_LS_ADJACENT_STP(linkSet))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINKSET_ADJ_STP_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINKSET_ADJ_STP_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (ENGINE_LS_IS_C(linkSet))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINKSET_IS_CLINK_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINKSET_IS_CLINK_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (ENGINE_LS_IS_5BIT(linkSet))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINKSET_IS_5BIT_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  LINKSET_IS_5BIT_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    ret = RESFILE_AddKeyValue(appRes, section,
                              LINKSET_INFO_STRING,
                              LINKSET_END_STRING);
    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      process one destination.
 *
 ****************************************************************************/
static void
ProcessISUPAttr(ITS_Object dest)
{
    ITS_Object attr = ENGINE_DE_ISUP_ATTR(dest), list, list2;
    const char *section;
    char tmp[ITS_PATH_MAX];
    int ret;

    /* we may have nothing to do */
    if (attr == NULL)
    {
        return;
    }

    if (ENGINE_DE_FAMILY(dest) == FAMILY_ANSI)
    {
        section = "ANSI-ISUP";
    }
    else if (ENGINE_DE_FAMILY(dest) == FAMILY_ITU)
    {
        section = "ITU-ISUP";
    }
    else if (ENGINE_DE_FAMILY(dest) == FAMILY_CHINA)
    {
        section = "PRC-ISUP";
    }
    else if (ENGINE_DE_FAMILY(dest) == FAMILY_JAPAN)
    {
        section = "TTC-ISUP";
    }
    else
    {
        ITS_C_ASSERT(ITS_FALSE);
    }

    /* the section might not have been added */
    RESFILE_AddSection(appRes, section);

    /* process the ISUP info */
    sprintf(tmp, "0x%08x", ENGINE_DE_PC(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              DEST_POINT_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "0x%08x", ENGINE_IA_LPC(attr));
    ret = RESFILE_AddKeyValue(appRes, section,
                              LOCAL_POINT_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "0x%02x", ENGINE_IA_SIO(attr));
    ret = RESFILE_AddKeyValue(appRes, section,
                              SIO_STRING,
                              tmp);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_DE_ISUP(dest))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  DI_ISUP_VAR_STRING,
                                  ENGINE_DE_ISUP(dest));
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (ENGINE_IA_XTYPE(attr) == NULL)
    {
        sprintf(tmp, "%s", "TYPE_A");
    }
    else
    {
        sprintf(tmp, "%s", ENGINE_IA_XTYPE(attr));
    }
    ret = RESFILE_AddKeyValue(appRes, section,
                              ISUP_XCHANGE_TYPE_STR,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_IA_SEGMENTATIONSUPPORT(attr) == NULL)
    {
        sprintf(tmp, "%s", "no");
    }
    else
    {
        sprintf(tmp, "%s", ENGINE_IA_SEGMENTATIONSUPPORT(attr));
    }
    ret = RESFILE_AddKeyValue(appRes, section,
                              ISUP_SEG_SUPPORT_STR,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    for (list = ENGINE_IA_TIMERS(attr); list; list = ENGINE_IT_NEXT(list))
    {
        if (ENGINE_IT_VALUE(list) && ENGINE_IT_HANDLER(list))
        {
            sprintf(tmp, "%s,%s", ENGINE_IT_VALUE(list), ENGINE_IT_HANDLER(list));
        }
        else if (ENGINE_IT_VALUE(list))
        {
            sprintf(tmp, "%s,DEF", ENGINE_IT_VALUE(list));
        }
        else if (ENGINE_IT_HANDLER(list))
        {
            sprintf(tmp, "-1,%s", ENGINE_IT_HANDLER(list));
        }

        ret = RESFILE_AddKeyValue(appRes, section,
                                  ENGINE_IT_ID(list),
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    for (list = ENGINE_IA_GROUPS(attr); list; list = ENGINE_CG_NEXT(list))
    {
        if (ENGINE_CG_HUNT_RULE(list))
        {
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ISUP_CIC_RULE_STR,
                                      ENGINE_CG_HUNT_RULE(list));
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        for (list2 = ENGINE_CG_CODES(list); list2; list2 = ENGINE_IC_NEXT(list2))
        {
            sprintf(tmp, "%d", ENGINE_IC_START(list2));
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ISUP_START_CIC_STR,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            sprintf(tmp, "%d", ENGINE_IC_COUNT(list2));
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ISUP_NUM_CICS_STR,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      process one destination.
 *
 ****************************************************************************/
static void
ProcessOneDest(ITS_Object dest)
{
    char *section = NULL; /* goes in global section */
    char tmp[ITS_PATH_MAX];
    int ret;

    ret = RESFILE_AddKeyValue(appRes, section,
                              DEST_INFO_STRING,
                              DI_BEGIN_STRING);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_DE_FAMILY(dest) == FAMILY_ANSI)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_ANSI_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_DE_FAMILY(dest) == FAMILY_ITU)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CCITT_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_DE_FAMILY(dest) == FAMILY_CHINA)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CHINA_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_DE_FAMILY(dest) == FAMILY_JAPAN)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_JAPAN_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    sprintf(tmp, "%d", ENGINE_DE_MTP3(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              DI_MTP3_VAR_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_DE_PC(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              DEST_POINT_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_DE_NI(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              SIO_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_DE_ISUP(dest))
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  DI_ISUP_VAR_STRING,
                                  ENGINE_DE_ISUP(dest));
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    sprintf(tmp, "%d", ENGINE_DE_SCCP(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              DI_SCCP_VAR_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_DE_TCAP(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              DI_TCAP_VAR_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_DE_TUP(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              DI_TUP_VAR_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_DE_DUP(dest));
    ret = RESFILE_AddKeyValue(appRes, section,
                              DI_DUP_VAR_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = RESFILE_AddKeyValue(appRes, section,
                              DEST_INFO_STRING,
                              DI_END_STRING);
    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      process one route.
 *
 ****************************************************************************/
static void
ProcessOneRoute(ITS_Object routes)
{
    char *section = NULL; /* goes in global section */
    char tmp[ITS_PATH_MAX];
    int ret;

    /* begin the route */
    switch (ENGINE_RT_INFO(routes).basic.type)
    {
    case LOCAL_ROUTE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_TYPE_STRING,
                                  ROUTE_TYPE_LOCAL_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case REMOTE_ROUTE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_TYPE_STRING,
                                  ROUTE_TYPE_REMOTE_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case CONCERNED_ROUTE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_TYPE_STRING,
                                  ROUTE_TYPE_CONCERNED_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case DUPLICATED_ROUTE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_TYPE_STRING,
                                  ROUTE_TYPE_DUPLICATE_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTING_KEY_ROUTE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_TYPE_STRING,
                                  ROUTE_TYPE_ROUTING_KEY_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    default:
        return;
    }

    /* set the style */
    switch (ENGINE_RT_INFO(routes).basic.style)
    {
    case ROUTE_DPC_NI:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_NI_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_NI:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_OPC_NI_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_SIO:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_SIO_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_OPC_SIO_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_SIO_SSN:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_SIO_SSN_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO_SSN:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_SIO_CIC:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_SIO_CIC_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO_CIC:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_SIO_SSN_RANGE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_SIO_CIC_RANGE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_UDEF:
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTE_STYLE_STRING,
                                  ROUTE_STYLE_DPC_UDEF_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    }

    /* add the routing key, if needed */
    if (ENGINE_RT_INFO(routes).basic.type == ROUTING_KEY_ROUTE)
    {
        sprintf(tmp, "0x%08x", ENGINE_RT_INFO(routes).rkey);

        ret = RESFILE_AddKeyValue(appRes, section,
                                  ROUTING_KEY_STRING,
                                  tmp);
    }

    /* add the point code */
    sprintf(tmp, "0x%08x", ENGINE_RT_INFO(routes).basic.dpc);
    ret = RESFILE_AddKeyValue(appRes, section,
                              DEST_POINT_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* add the mask */
    sprintf(tmp, "0x%08x", ENGINE_RT_INFO(routes).basic.mask);
    ret = RESFILE_AddKeyValue(appRes, section,
                              ROUTE_MASK_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* Add the family */
    if (ENGINE_RT_INFO(routes).basic.family == FAMILY_ANSI)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_ANSI_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_RT_INFO(routes).basic.family == FAMILY_ITU)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CCITT_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_RT_INFO(routes).basic.family == FAMILY_CHINA)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_CHINA_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else if (ENGINE_RT_INFO(routes).basic.family == FAMILY_JAPAN)
    {
        ret = RESFILE_AddKeyValue(appRes, section,
                                  FAMILY_STRING,
                                  FAMILY_JAPAN_STRING);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    /* add the specifics */
    switch (ENGINE_RT_INFO(routes).basic.style)
    {
    case ROUTE_DPC_NI:
    case ROUTE_DPC_SIO:
        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_NI:
    case ROUTE_DPC_OPC_SIO:
        /* opc */
        sprintf(tmp, "%08x", ENGINE_RT_INFO(routes).basic.criteria.opc);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ORIG_POINT_CODE_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        break;

    case ROUTE_DPC_SIO_SSN:
        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* ssn */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.ssn);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SSN_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;
    case ROUTE_DPC_OPC_SIO_SSN:
        if (ENGINE_RT_INFO(routes).basic.type != CONCERNED_ROUTE &&
            ENGINE_RT_INFO(routes).basic.type != DUPLICATED_ROUTE)
        {
            /* opc */
            sprintf(tmp, "0x%08x", ENGINE_RT_INFO(routes).basic.criteria.opc);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ORIG_POINT_CODE_STRING,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* sio */
            sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SIO_STRING,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* ssn */
            sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.ssn);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SSN_STRING,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }
        else
        {
            /* opc */
            sprintf(tmp, "0x%08x", ENGINE_RT_INFO(routes).basic.criteria.opc);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      LOCAL_POINT_CODE_STRING,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* sio */
            sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SIO_STRING,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* ssn */
            sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.ssn);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      SSN_STRING,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* lssn */
            sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.cic);
            ret = RESFILE_AddKeyValue(appRes, section,
                                      LOCAL_SSN_STRING,
                                      tmp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }
        break;

    case ROUTE_DPC_SIO_CIC:
        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* cic */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.cic);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  CIC_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO_CIC:
        /* opc */
        sprintf(tmp, "%08x", ENGINE_RT_INFO(routes).basic.criteria.opc);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ORIG_POINT_CODE_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* cic */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.cic);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  CIC_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_SIO_SSN_RANGE:
        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* begin */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.begin);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_BEGIN_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* end */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.end);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_END_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_SIO_CIC_RANGE:
        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* begin */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.begin);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_BEGIN_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* end */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.end);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_END_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
        /* opc */
        sprintf(tmp, "%08x", ENGINE_RT_INFO(routes).basic.criteria.opc);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ORIG_POINT_CODE_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* begin */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.begin);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_BEGIN_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* end */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.end);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_END_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        /* opc */
        sprintf(tmp, "%08x", ENGINE_RT_INFO(routes).basic.criteria.opc);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  ORIG_POINT_CODE_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* sio */
        sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).basic.criteria.sio);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  SIO_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* begin */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.begin);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_BEGIN_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* end */
        sprintf(tmp, "0x%04x", ENGINE_RT_INFO(routes).basic.criteria.range.end);
        ret = RESFILE_AddKeyValue(appRes, section,
                                  RANGE_END_STRING,
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ROUTE_DPC_UDEF:
        break;

    }

    /* add the link set */
    sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).linkSet);
    ret = RESFILE_AddKeyValue(appRes, section,
                              LINKSET_SET_STRING,
                              tmp);

    /* add the priority */
    sprintf(tmp, "0x%02x", ENGINE_RT_INFO(routes).priority);
    ret = RESFILE_AddKeyValue(appRes, section,
                              PRIORITY_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* end the route */
    ret = RESFILE_AddKeyValue(appRes, section,
                              ROUTE_TYPE_STRING,
                              ROUTE_TYPE_END_OF_STRING);
    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      process one transport.
 *
 ****************************************************************************/
static void
ProcessOneTransport(ITS_Object transports, ITS_Object pool)
{
    ENGINE_TransportSpecifics specs;
    ENGINE_LibCache lib;
    ITS_Class *ss7Class;
    char buf[ITS_PATH_MAX];
    int ret;
    ITS_Object links, remotes;

    /* make sure we have a section name */
    if (ENGINE_TR_NAME(transports) == NULL)
    {
        sprintf(buf, ITS_UNNAMED_TRANSPORT_FORMAT_STRING, currentInstance);
    }
    else
    {
        strcpy(buf, ENGINE_TR_NAME(transports));
    }

    /* add the section */
    ret = RESFILE_AddSection(appRes, buf);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    if (ENGINE_TR_IS_INTERNODE(transports)) 
    {        
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  INTERNODE_STRING,
                                  "yes");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
    else
    {
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  INTERNODE_STRING,
                                  "no");
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }       


    /* add the transport resources */
    if (ENGINE_TR_SPECIFICS(transports) == NULL)
    {
        /* add the routes */
        for (links = ENGINE_TR_LINKS(transports);
             links != NULL;
             links = ENGINE_LN_NEXT(links))
        {
            ProcessOneLink(links, buf);
        }

        return;
    }

    specs = (ENGINE_TransportSpecifics)ENGINE_TR_SPECIFICS(transports);
    switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(specs)))
    {
    case ITS_TRANSPORT_SS7:
        /* get the lib and add the class */
        lib = ENGINE_LibGet(application,
                            ENGINE_TS_DATA(specs).ss7Specs.vendorLib);
        ITS_C_ASSERT(lib != NULL);

        ss7Class = (ITS_Class *)
                      DLSYM_Resolve(ENGINE_LC_LIBRARY(lib),
                                    ENGINE_TS_DATA(specs).ss7Specs.vendorClass);
        ITS_C_ASSERT(ss7Class != NULL);

        if (ITS_FindFeature((*ss7Class)->coreClass.className) == NULL)
        {
            if (ITS_AddFeature(*ss7Class) != ITS_SUCCESS)
            {
                printf("Failed to add feature: '%s'\n",
                       ITS_CLASS_CLASSNAME(*ss7Class));

                abort();
            }
        }

        /* vendor class */
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  SS7_STACK_BINDING_STRING,
                                  (*ss7Class)->coreClass.className);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        /* client path */
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  FIFO_CLIENT_PATH_STRING,
                                  ENGINE_TS_DATA(specs).fifoSpecs.clientPath);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* server path */
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  FIFO_SERVER_PATH_STRING,
                                  ENGINE_TS_DATA(specs).fifoSpecs.serverPath);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        /* socket domain */
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  SOCKET_DOMAIN_STRING,
                                  ENGINE_TS_DATA(specs).tcpSpecs.socketDomain);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* server path */
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  SERVER_PATH_STRING,
                                  ENGINE_TS_DATA(specs).tcpSpecs.serverPath);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* server port */
        ret = RESFILE_AddKeyValue(appRes, buf,
                                  SERVER_PORT_STRING,
                                  ENGINE_TS_DATA(specs).tcpSpecs.serverPort);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        /* retry delay (optional) */
        if (ENGINE_TS_DATA(specs).tcpSpecs.retryDelay != NULL)
        {
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      RETRY_DELAY_STRING,
                                      ENGINE_TS_DATA(specs).tcpSpecs.retryDelay);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        /* retry count (optional) */
        if (ENGINE_TS_DATA(specs).tcpSpecs.retryCount != NULL)
        {
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      RETRY_COUNT_STRING,
                                      ENGINE_TS_DATA(specs).tcpSpecs.retryCount);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            /* local PC */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      GDI_LOCAL_PC_STRING,
                                      ENGINE_TS_DATA(specs).gdiSpecs.localPC);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* remote PC */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      GDI_REMOTE_PC_STRING,
                                      ENGINE_TS_DATA(specs).gdiSpecs.remotePC);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* remote SSN */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      GDI_REMOTE_SSN_STRING,
                                      ENGINE_TS_DATA(specs).gdiSpecs.remoteSSN);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            /* local PC */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      TALI_LOCAL_PC_STRING,
                                      ENGINE_TS_DATA(specs).taliSpecs.localPC);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* adjacent PC */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      TALI_ADJ_PC_STRING,
                                      ENGINE_TS_DATA(specs).taliSpecs.adjacentPC);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* allowed on open */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      TALI_LOCALLY_ALLOWED_ON_OPEN_STRING,
                                      ENGINE_TS_DATA(specs).taliSpecs.localAllowedOnOpen);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* user upper layer */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      TALI_USE_UPPER_LAYER_STRING,
                                      ENGINE_TS_DATA(specs).taliSpecs.useUpperLayer);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* local PC */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      IMAL_LOCAL_PC_STRING,
                                      ENGINE_TS_DATA(specs).imalSpecs.localPC);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* adjacent PC */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      IMAL_ADJ_PC_STRING,
                                      ENGINE_TS_DATA(specs).imalSpecs.adjacentPC);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        /* none */
        break;

    case ITS_TRANSPORT_DATAGRAM:
        if (ENGINE_TS_MASK(specs) & ITS_TRANSPORT_DGRAM_VIRT)
        {
            /* remote host */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      SERVER_PATH_STRING,
                                      ENGINE_TS_DATA(specs).udpSpecs.localHost);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* remote port */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      SERVER_PORT_STRING,
                                      ENGINE_TS_DATA(specs).udpSpecs.localPort);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /*
             * kludge.  All preconfigured remotes are by definition clients.
             * However, this tag has no meaning to IMAL or RUDP transports.
             */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      IS_CLIENT_STRING,
                                      "yes");
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }
        else
        {
            /* local host */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      LOCAL_HOST_NAME_STRING,
                                      ENGINE_TS_DATA(specs).udpSpecs.localHost);
            ITS_C_ASSERT(ret == ITS_SUCCESS);

            /* local port */
            ret = RESFILE_AddKeyValue(appRes, buf,
                                      LOCAL_PORT_STRING,
                                      ENGINE_TS_DATA(specs).udpSpecs.localPort);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        /* associates */
        if (ENGINE_TS_DATA(specs).udpSpecs.numAssociates)
        {
            int i;
            char tmp[ITS_PATH_MAX];

            ITS_C_ASSERT(pool != NULL);

            for (i = 0; i < ENGINE_TS_DATA(specs).udpSpecs.numAssociates; i++)
            {
                /* find the instance */
                for (remotes = ENGINE_TP_TRANSPORTS(pool);
                     remotes != NULL;
                     remotes = ENGINE_TR_NEXT(remotes))
                {
                    if (strcmp(ENGINE_TS_DATA(specs).udpSpecs.associates[i],
                               ENGINE_TR_NAME(remotes)) == 0)
                    {
                        sprintf(tmp, "%d", ENGINE_TR_INST(remotes));

                        break;
                    }
                }

                /* make sure we did find one */
                ITS_C_ASSERT(remotes != NULL);

                ret = RESFILE_AddKeyValue(appRes, buf,
                                          ASSOC_TRID_NAME_STRING,
                                          ENGINE_TS_DATA(specs).udpSpecs.associates[i]);
                ITS_C_ASSERT(ret == ITS_SUCCESS);

                ret = RESFILE_AddKeyValue(appRes, buf,
                                          ASSOC_TRID_INST_STRING,
                                          tmp);
                ITS_C_ASSERT(ret == ITS_SUCCESS);

                /* copy the mask */
                sprintf(tmp, "0x%08x", ENGINE_TS_MASK(specs));

                ret = RESFILE_AddKeyValue(appRes, buf,
                                          ASSOC_TRID_MASK_STRING,
                                          tmp);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }
        }

        /* handle SCTP, RUDP */
        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            if (ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes)
            {
                int i;

                for (i = 0; i < ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes; i++)
                {
                    ret = RESFILE_AddKeyValue(appRes, buf,
                                              LOCAL_HOST_NAME_STRING,
                                              ENGINE_TS_DATA(specs).sctpSpecs.extraHomes[i]);
                    ITS_C_ASSERT(ret == ITS_SUCCESS);
                }
            }

            /* max in streams */
            if (ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          MAX_IN_STREAMS_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* num out streams */
            if (ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          NUM_OUT_STREAMS_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* max attempts */
            if (ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          MAX_ATTEMPTS_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* cookie life */
            if (ENGINE_TS_DATA(specs).sctpSpecs.cookieLife)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          INIT_COOKIE_LIFE_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.cookieLife);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* hb on */
            if (ENGINE_TS_DATA(specs).sctpSpecs.hbOn != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          INIT_HB_ON_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.hbOn);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* init time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          INIT_TIMEOUT_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* send time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          SEND_TIMEOUT_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* recv time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          RECV_TIMEOUT_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* hb time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          HB_TIMEOUT_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* shutdown time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          SHUT_TIMEOUT_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* pmtu time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          PMTU_TIMEOUT_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* is client */
            if (ENGINE_TS_DATA(specs).sctpSpecs.isClient != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          IS_CLIENT_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.isClient);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }

            /* payload type */
            if (ENGINE_TS_DATA(specs).sctpSpecs.payloadType != NULL)
            {
                ret = RESFILE_AddKeyValue(appRes, buf,
                                          PAYLOAD_TYPE_STRING,
                                          ENGINE_TS_DATA(specs).sctpSpecs.payloadType);
                ITS_C_ASSERT(ret == ITS_SUCCESS);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    /* add the routes */
    for (links = ENGINE_TR_LINKS(transports);
         links != NULL;
         links = ENGINE_RT_NEXT(links))
    {
        ProcessOneLink(links, buf);
    }
}

/*.implementation:static
 ****************************************************************************
 * Purpose:
 *      process one stack layer
 *
 * Revision History:
 *  ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ----------------------------------------------------------------------------
 * Raghavendra CE  13-05-2005   BUG# 1776     Process trace handles syslog      
 *                               & 1792     
 *
 ****************************************************************************/
static void
ProcessOneLayer(ITS_Object layer)
{
    int ret;
    ITS_Object links, traces;
    char *tmp;
    int i;
    char buf[ITS_PATH_MAX];

    ret = RESFILE_AddSection(appRes, ENGINE_ISS7_NAME(layer));
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* set the variant */
    if (ENGINE_ISS7_VARIANT(layer))
    {
        sprintf(buf, "%d", ENGINE_ISS7_VARIANT(layer));
        ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                  VARIANT_STRING,
                                  buf);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    if (ENGINE_ISS7_NUM_THREADS(layer) > 0)
    {
        sprintf(buf, "%d", ENGINE_ISS7_NUM_THREADS(layer));
        ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                  NUM_THREADS_STRING,
                                  buf);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    /* process the trace */
    for (traces = ENGINE_ISS7_TRACE(layer);
         traces != NULL;
         traces = ENGINE_TL_NEXT(traces))
    {
        switch (ENGINE_TL_LEVEL_MASK(traces))
        {
            case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                         ITS_FILE_STRING,
                                         ITS_SYSLOG_STRING);
                break;

            case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_FILE_STRING);
                 break;

            case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_FILE_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_DISPLAY:
                 sprintf(buf, "%s", ITS_STDOUT_STRING);
                 break;

            case TRACE_TO_FILE:
                 sprintf(buf, "%s", ITS_FILE_STRING);
                 break;

            case TRACE_TO_SYSLOG:
                 sprintf(buf, "%s", ITS_SYSLOG_STRING);
                 break;

            default:
                 sprintf(buf, "%s", "");
                 break;
        }
    
        if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                   ITS_CRITICAL_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                      ITS_TRACE_CRITICAL_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_ERROR_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                      ITS_TRACE_ERROR_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_WARNING_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                      ITS_TRACE_WARNING_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_DEBUG_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                      ITS_TRACE_DEBUG_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_EVENT_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                      ITS_TRACE_EVENT_STRING,
                                      buf);
        }
    }

    /* process the timers */
    for (i = 0; i < ENGINE_ISS7_NUM_TIMERS(layer); i++)
    {
        strcpy(buf, ENGINE_ISS7_TIMERS(layer)[i]);

        tmp = strchr(buf, '=');
        ITS_C_ASSERT(tmp != NULL);

        *tmp = 0;
        tmp++;

        ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                  buf, tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    /* process the behaviors */
    for (i = 0; i < ENGINE_ISS7_NUM_MODIFIERS(layer); i++)
    {
        strcpy(buf, ENGINE_ISS7_MODIFIERS(layer)[i]);

        tmp = strchr(buf, '=');
        ITS_C_ASSERT(tmp != NULL);

        *tmp = 0;
        tmp++;

        ret = RESFILE_AddKeyValue(appRes, ENGINE_ISS7_NAME(layer),
                                  buf, tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    /* add the link */
    for (links = ENGINE_ISS7_LINKS(layer);
         links != NULL;
         links = ENGINE_LN_NEXT(links))
    {
        ProcessOneLink(links, ENGINE_ISS7_NAME(layer));
    }
}

/*.implementation:static
 ****************************************************************************
 * Purpose:
 *      process one destination.
 *
 * Revision History:
 *  ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ----------------------------------------------------------------------------
 * Raghavendra CE  13-05-2005   BUG# 1776     Process trace handles syslog
 *                               & 1792
 *
 ****************************************************************************/
static void
ProcessSIPAttr(ITS_Object attr)
{
    ITS_Object list, traces;
    const char *section;
    char tmp[ITS_PATH_MAX];
    int ret;
    char buf[ITS_PATH_MAX];

    /* we may have nothing to do */
    if (attr == NULL)
    {
        return;
    }

    /* include section */
    section = "ITS-SIP";

    /* the section might not have been added */
    RESFILE_AddSection(appRes, section);

    /* process the SIP info */
    sprintf(tmp, "%d", ENGINE_SIP_UDPPORT(attr));
    ret = RESFILE_AddKeyValue(appRes, section,
                              SIP_UDPPORTNO_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%d", ENGINE_SIP_TCPPORT(attr));
    ret = RESFILE_AddKeyValue(appRes, section,
                              SIP_TCPPORTNO_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%s", ENGINE_SIP_IPADDR(attr));
    ret = RESFILE_AddKeyValue(appRes, section,
                              SIP_IPADDR_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    for (list = ENGINE_SIP_TIMERS(attr); list; list = ENGINE_ST_NEXT(list))
    {
        sprintf(tmp, "%s", ENGINE_ST_VALUE(list));

        ret = RESFILE_AddKeyValue(appRes, section,
                                  ENGINE_ST_ID(list),
                                  tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }

    /* process the trace */
    for (traces = ENGINE_SIP_TRACE(attr);
         traces != NULL;
         traces = ENGINE_TL_NEXT(traces))
    {
        switch (ENGINE_TL_LEVEL_MASK(traces))
        {
            case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                         ITS_FILE_STRING,
                                         ITS_SYSLOG_STRING);
                break;

            case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_FILE_STRING);
                 break;

            case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_FILE_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_DISPLAY:
                 sprintf(buf, "%s", ITS_STDOUT_STRING);
                 break;

            case TRACE_TO_FILE:
                 sprintf(buf, "%s", ITS_FILE_STRING);
                 break;

            case TRACE_TO_SYSLOG:
                 sprintf(buf, "%s", ITS_SYSLOG_STRING);
                 break;

            default:
                 sprintf(buf, "%s", "");
                 break;
        }

        if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                   ITS_CRITICAL_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ITS_TRACE_CRITICAL_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_ERROR_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ITS_TRACE_ERROR_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_WARNING_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ITS_TRACE_WARNING_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_DEBUG_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, section,
                                      ITS_TRACE_DEBUG_STRING,
                                      buf);
        }
    }
}

/****************************************************************************/
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      process one iid.
 *
 ****************************************************************************/
static void
ProcessOneIid(ITS_Object iid, char *section)
{
    char tmp[ITS_PATH_MAX];
    int ret;

    ret = RESFILE_AddKeyValue(appRes, section,
                              IID_INFO_STRING,
                              IID_BEGIN_STRING);
                                                                                
    sprintf(tmp, "%d", ENGINE_M2UA_IID_LINKSET(iid));
    ret = RESFILE_AddKeyValue(appRes, section,
                              M2UA_LINK_SET_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);
                                                                                
    sprintf(tmp, "%d", ENGINE_M2UA_IID_LINKCODE(iid));
    ret = RESFILE_AddKeyValue(appRes, section,
                              M2UA_LINK_CODE_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%s", ENGINE_M2UA_IID_IID(iid));
    ret = RESFILE_AddKeyValue(appRes, section,
                              M2UA_IID_STRING,
                              tmp);
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    sprintf(tmp, "%s", ENGINE_M2UA_IID_ASSONAME(iid));
    ret = RESFILE_AddKeyValue(appRes, section,
                              M2UA_ASSO_NAME_STRING,
                              tmp);

    ret = RESFILE_AddKeyValue(appRes, section,
                              IID_INFO_STRING,
                              IID_END_STRING);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

}
/****************************************************************************/
/*.implementation:static
 ****************************************************************************
 * Purpose:
 *      process one sigtran stack layer
 *
 * Revision History:
 *  ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ----------------------------------------------------------------------------
 * Raghavendra CE  13-05-2005   BUG# 1776     Process trace handles syslog
 *                               & 1792
 ****************************************************************************/
static void
ProcessOneSigtranLayer(ITS_Object layer)
{
    ITS_INT ret;
    ITS_Object links, traces, iid;
    ITS_CHAR buf[ITS_PATH_MAX];
    ITS_CHAR *tmp;
    ITS_INT i;

    ret = RESFILE_AddSection(appRes, ENGINE_SIGTRAN_NAME(layer));

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* process the trace */
    for (traces = ENGINE_SIGTRAN_TRACE(layer);
         traces != NULL;
         traces = ENGINE_TL_NEXT(traces))
    {
        switch (ENGINE_TL_LEVEL_MASK(traces))
        {
            case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                         ITS_FILE_STRING,
                                         ITS_SYSLOG_STRING);
                break;

            case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_FILE_STRING);
                 break;

            case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_FILE_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_DISPLAY:
                 sprintf(buf, "%s", ITS_STDOUT_STRING);
                 break;

            case TRACE_TO_FILE:
                 sprintf(buf, "%s", ITS_FILE_STRING);
                 break;

            case TRACE_TO_SYSLOG:
                 sprintf(buf, "%s", ITS_SYSLOG_STRING);
                 break;

            default:
                 sprintf(buf, "%s", "");
                 break;
        }
 
        if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                   ITS_CRITICAL_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_SIGTRAN_NAME(layer),
                                      ITS_TRACE_CRITICAL_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_ERROR_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_SIGTRAN_NAME(layer),
                                      ITS_TRACE_ERROR_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_WARNING_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_SIGTRAN_NAME(layer),
                                      ITS_TRACE_WARNING_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_DEBUG_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_SIGTRAN_NAME(layer),
                                      ITS_TRACE_DEBUG_STRING,
                                      buf);
        }
    }

    /* add M2UA IID(s) */
    for (iid= ENGINE_SIGTRAN_IID(layer);
         iid != NULL;
         iid = ENGINE_M2UA_IID_NEXT(iid))
    {
        ProcessOneIid(iid, ENGINE_SIGTRAN_NAME(layer)); 
    }    

}

/*.implementation:static
 ****************************************************************************
 * Purpose:
 *      Process vendor traces
 *
 * Revision History:
 *  ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ----------------------------------------------------------------------------
 * Raghavendra CE  13-05-2005   BUG# 1776     Process trace handles syslog
 *                               & 1792
 *
 ****************************************************************************/
static void
ProcessVendorTrace(ENGINE_Application application)
{
    ITS_Object traces;
    char buf[ITS_PATH_MAX];
    int ret = ITS_SUCCESS;

    /* process the trace */
    if (traces = ENGINE_APP_VENDOR_ONE_LEVELS(application))
    {
        ret = RESFILE_AddSection(appRes, ADAX_INI_SECTION_NAME);

        for (; traces != NULL; traces = ENGINE_TL_NEXT(traces))
        {
            switch (ENGINE_TL_LEVEL_MASK(traces))
            {
                case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                    sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                             ITS_FILE_STRING,
                                             ITS_SYSLOG_STRING);
                    break;

                case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                     sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_FILE_STRING);
                     break;

                case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                     sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_SYSLOG_STRING);
                     break;

                case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                     sprintf(buf, "%s,%s", ITS_FILE_STRING, ITS_SYSLOG_STRING);
                     break;

                case TRACE_TO_DISPLAY:
                     sprintf(buf, "%s", ITS_STDOUT_STRING);
                     break;

                case TRACE_TO_FILE:
                     sprintf(buf, "%s", ITS_FILE_STRING);
                     break;

                case TRACE_TO_SYSLOG:
                     sprintf(buf, "%s", ITS_SYSLOG_STRING);
                     break;

                default:
                     sprintf(buf, "%s", "");
                     break;
            }

            if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_CRITICAL_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, ADAX_INI_SECTION_NAME,
                                                  ITS_TRACE_CRITICAL_STRING,
                                                  buf); 
            }
            else if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_ERROR_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, ADAX_INI_SECTION_NAME,
                                              ITS_TRACE_ERROR_STRING,
                                              buf);
            }
            else if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_WARNING_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, ADAX_INI_SECTION_NAME,
                                              ITS_TRACE_WARNING_STRING,
                                              buf);
            }
            else if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_DEBUG_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, ADAX_INI_SECTION_NAME,
                                              ITS_TRACE_DEBUG_STRING,
                                              buf);
            }
        }
    }

    if (traces = ENGINE_APP_VENDOR_TWO_LEVELS(application))
    {
        ret = RESFILE_AddSection(appRes, NMS_INI_SECTION_NAME);

        for (; traces != NULL; traces = ENGINE_TL_NEXT(traces))
        {
            switch (ENGINE_TL_LEVEL_MASK(traces))
            {
                case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                    sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                             ITS_FILE_STRING,
                                             ITS_SYSLOG_STRING);
                    break;

                case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                     sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_FILE_STRING);
                     break;

                case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                     sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_SYSLOG_STRING);
                     break;

                case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                     sprintf(buf, "%s,%s", ITS_FILE_STRING, ITS_SYSLOG_STRING);
                     break;

                case TRACE_TO_DISPLAY:
                     sprintf(buf, "%s", ITS_STDOUT_STRING);
                     break;

                case TRACE_TO_FILE:
                     sprintf(buf, "%s", ITS_FILE_STRING);
                     break;

                case TRACE_TO_SYSLOG:
                     sprintf(buf, "%s", ITS_SYSLOG_STRING);
                     break;

                default:
                     sprintf(buf, "%s", "");
                     break;
            }

            if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_CRITICAL_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, NMS_INI_SECTION_NAME,
                                          ITS_TRACE_CRITICAL_STRING,
                                          buf);
            }
            else if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_ERROR_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, NMS_INI_SECTION_NAME,
                                          ITS_TRACE_ERROR_STRING,
                                          buf);
            }
            else if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_WARNING_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, NMS_INI_SECTION_NAME,
                                          ITS_TRACE_WARNING_STRING,
                                          buf);
            }
            else if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_DEBUG_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, NMS_INI_SECTION_NAME,
                                          ITS_TRACE_DEBUG_STRING,
                                          buf);
            }
            else if (strcmp(ENGINE_TL_LEVEL_NAME(traces), ITS_EVENT_STRING) == 0)
            {
                ret = RESFILE_AddKeyValue(appRes, NMS_INI_SECTION_NAME,
                                          ITS_TRACE_EVENT_STRING,
                                          buf);
            }
        }
    }
}

static void
ProcessOneCodecLayer(ITS_Object layer)
{
    ITS_INT ret;
    ITS_Object links, traces, iid;
    ITS_CHAR buf[ITS_PATH_MAX];
    ITS_CHAR *tmp;
    ITS_INT i;

    printf("******\n");

    ret = RESFILE_AddSection(appRes, ENGINE_CODEC_NAME(layer));

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* process the trace */
    for (traces = ENGINE_CODEC_TRACE(layer);
         traces != NULL;
         traces = ENGINE_TL_NEXT(traces))
    {
        switch (ENGINE_TL_LEVEL_MASK(traces))
        {
            case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                         ITS_FILE_STRING,
                                         ITS_SYSLOG_STRING);
                break;

            case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_FILE_STRING);
                 break;

            case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_STDOUT_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                 sprintf(buf, "%s,%s", ITS_FILE_STRING, ITS_SYSLOG_STRING);
                 break;

            case TRACE_TO_DISPLAY:
                 sprintf(buf, "%s", ITS_STDOUT_STRING);
                 break;

            case TRACE_TO_FILE:
                 sprintf(buf, "%s", ITS_FILE_STRING);
                 break;

            case TRACE_TO_SYSLOG:
                 sprintf(buf, "%s", ITS_SYSLOG_STRING);
                 break;

            default:
                 sprintf(buf, "%s", "");
                 break;
        }

        if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                   ITS_CRITICAL_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_CODEC_NAME(layer),
                                      ITS_TRACE_CRITICAL_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_ERROR_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_CODEC_NAME(layer),
                                      ITS_TRACE_ERROR_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_WARNING_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_CODEC_NAME(layer),
                                      ITS_TRACE_WARNING_STRING,
                                      buf);
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(traces),
                        ITS_DEBUG_STRING) == 0)
        {
            ret = RESFILE_AddKeyValue(appRes, ENGINE_CODEC_NAME(layer),
                                      ITS_TRACE_DEBUG_STRING,
                                      buf);
        }
    }

    /* process the timers */
    for (i = 0; i < ENGINE_CODEC_NUM_TIMERS(layer); i++)
    {
        strcpy(buf, ENGINE_CODEC_TIMERS(layer)[i]);

        tmp = strchr(buf, '=');
        ITS_C_ASSERT(tmp != NULL);

        *tmp = 0;
        tmp++;

        ret = RESFILE_AddKeyValue(appRes, ENGINE_CODEC_NAME(layer),
                                  buf, tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      use current transports pointer to populate the RESDB
 *
 *  Notes:
 *      The pools are spread by 10000 (instance count)
 *
 ****************************************************************************/
static void
PopulateResources()
{
    ITS_Object tps, trs, layers, exts, routes, linkSets, dests;

    /* link sets */
    for (linkSets = ENGINE_APP_LINK_SETS(application);
         linkSets != NULL;
         linkSets = ENGINE_LS_NEXT(linkSets))
    {
        ProcessOneLinkSet(linkSets);
    }

    /* routes */
    for (routes = ENGINE_APP_ROUTES(application);
         routes != NULL;
         routes = ENGINE_RT_NEXT(routes))
    {
        ProcessOneRoute(routes);
    }

    /* destinations */
    for (dests = ENGINE_APP_DESTS(application);
         dests != NULL;
         dests = ENGINE_DE_NEXT(dests))
    {
        ProcessOneDest(dests);
    }

    /* worker pools */
    currentInstance = ITS_FIRST_USER_SRC;
    for (tps = ENGINE_APP_POOLS(application);
         tps != NULL;
         tps = ENGINE_TP_NEXT(tps))
    {
        if (ENGINE_TP_TYPE(tps) == TP_WORKERS)
        {
            for (trs = ENGINE_TP_TRANSPORTS(tps);
                 trs != NULL;
                 trs = ENGINE_TR_NEXT(trs))
            {
                ENGINE_TR_INST(trs) = currentInstance;

                ProcessOneTransport(trs, NULL);

                currentInstance++;

                if (ENGINE_TR_NUM_ASSOCIATES(trs))
                {
                    ITS_USHORT baseInstance = ENGINE_TR_INST(trs);
                    ITS_UINT i;

                    for (i = 0;
                         i < ENGINE_TR_NUM_ASSOCIATES(trs) - 1;
                         i++)
                    {
                        ENGINE_TR_INST(trs) = currentInstance;

                        ProcessOneTransport(trs, NULL);

                        currentInstance++;
                    }

                    /*
                     * note the reset.  This is because CreateWorkers
                     * needs the base number.
                     */
                    ENGINE_TR_INST(trs) = baseInstance;
                }
            }

            /* only get the first one */
            break;
        }
    }
    lastWorker = currentInstance + 1;

    /* workitem pools */
    currentInstance = ITS_FIRST_USER_SRC + 10000;
    for (tps = ENGINE_APP_POOLS(application);
         tps != NULL;
         tps = ENGINE_TP_NEXT(tps))
    {
        if (ENGINE_TP_TYPE(tps) == TP_WORK_ITEMS)
        {
            for (trs = ENGINE_TP_TRANSPORTS(tps);
                 trs != NULL;
                 trs = ENGINE_TR_NEXT(trs))
            {
                ENGINE_TR_INST(trs) = currentInstance;

                ProcessOneTransport(trs, NULL);

                currentInstance++;
            }

            /* only get one */
            break;
        }
    }
    lastWorkItem = currentInstance + 1;

    /* border pools */
    currentInstance = ITS_FIRST_USER_SRC + 20000;
    for (tps = ENGINE_APP_POOLS(application);
         tps != NULL;
         tps = ENGINE_TP_NEXT(tps))
    {
        if (ENGINE_TP_TYPE(tps) == TP_BORDERS)
        {
            /* set the instance numbers */
            for (trs = ENGINE_TP_TRANSPORTS(tps);
                 trs != NULL;
                 trs = ENGINE_TR_NEXT(trs))
            {
                ENGINE_TR_INST(trs) = currentInstance;

                currentInstance++;

                /* handle acceptors */
                if (ENGINE_TR_NUM_ASSOCIATES(trs))
                {
                    currentInstance += ENGINE_TR_NUM_ASSOCIATES(trs);
                }
            }

            /* now set the resources */
            for (trs = ENGINE_TP_TRANSPORTS(tps);
                 trs != NULL;
                 trs = ENGINE_TR_NEXT(trs))
            {
                ProcessOneTransport(trs, tps);
            }

            /* only one pool */
            break;
        }
    }
    lastBorder = currentInstance + 1;

    /* do the stack */
    for (layers = ENGINE_APP_ISS7_STACK_CTRL(application);
         layers != NULL;
         layers = ENGINE_ISS7_NEXT(layers))
    {
        ProcessOneLayer(layers);
    }

    /* destinations (ISUP) */
    for (dests = ENGINE_APP_DESTS(application);
         dests != NULL;
         dests = ENGINE_DE_NEXT(dests))
    {
        ProcessISUPAttr(dests);
    }

    /* Process SIP attributes */
    ProcessSIPAttr(ENGINE_APP_SIP(application));

    /* do the extensions */
    for (exts = ENGINE_APP_PARSER_EXTENSIONS(application);
         exts != NULL;
         exts = ENGINE_PE_NEXT(exts))
    {
        if (ENGINE_PE_XLATE_FUNC(exts))
        {
            ENGINE_PE_XLATE_FUNC(exts)(appRes, (ENGINE_ParserExtension)exts);
        }
    }

    /* do the sigtran stack */
    for (layers = ENGINE_APP_SIGTRAN_STACK_CTRL(application);
         layers != NULL;
         layers = ENGINE_SIGTRAN_NEXT(layers))
    {
        ProcessOneSigtranLayer(layers);
    }

    /* do the codec stack */
    for (layers = ENGINE_APP_CODEC_STACK_CTRL(application);
         layers != NULL;
         layers = ENGINE_CODEC_NEXT(layers))
    {
        ProcessOneCodecLayer(layers);
    }


    /* do the vendor trace */
    ProcessVendorTrace(application);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Set support trace
 *
 *  Notes:
 *      This isn't resource related, but this is a common function.
 *
 * Revision History:
 *  ----------------------------------------------------------------------------
 *   Name          Date        Reference               Description
 *  ----------------------------------------------------------------------------
 * Raghavendra CE  13-05-2005   BUG# 1776     Support trace handles syslog
 *                               & 1792
 *
 ****************************************************************************/
static void
SetSupportTrace(ENGINE_Application application)
{
    ITS_Object list;
    char buf[ITS_PATH_MAX];
    int ret = ITS_SUCCESS;

    /* set SUPPORT trace */
    for (list = ENGINE_APP_SUPPORT_LEVELS(application);
         list != NULL;
         list = ENGINE_TL_NEXT(list))
    {
        if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_CRITICAL_STRING) == 0)
        {
            switch (ENGINE_TL_LEVEL_MASK(list))
            {
                case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                    TRACE_TurnCriticalTraceOnOff(ITS_TRUE); 
          
                    sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                             ITS_FILE_STRING,
                                             ITS_SYSLOG_STRING);
   
                    if (!TRACE_IsInitialized())
                    {
                        ret = RESFILE_AddKeyValue(appRes, NULL,
                                                  ITS_TRACE_CRITICAL_STRING,
                                                  buf);
                    }
                    else
                    {
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_CRITICAL_STRING,
                                                   ITS_FILE_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_CRITICAL_STRING,
                                                   ITS_STDOUT_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_CRITICAL_STRING,
                                                   ITS_SYSLOG_STRING,
                                                   ITS_TRUE);
                    }
                    break;

               case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                   TRACE_TurnCriticalTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_CRITICAL_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                   TRACE_TurnCriticalTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_CRITICAL_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                   TRACE_TurnCriticalTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_FILE_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_CRITICAL_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY:
                   TRACE_TurnCriticalTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_STDOUT_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_CRITICAL_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE:
                   TRACE_TurnCriticalTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_CRITICAL_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_SYSLOG:
                   TRACE_TurnCriticalTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_CRITICAL_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_CRITICAL_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_NONE: 
                   TRACE_TurnCriticalTraceOnOff(ITS_FALSE);
                   break;
            } 
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_ERROR_STRING) == 0)
        {
            switch (ENGINE_TL_LEVEL_MASK(list))
            {
                case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                    TRACE_TurnErrorTraceOnOff(ITS_TRUE);

                    sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                             ITS_FILE_STRING,
                                             ITS_SYSLOG_STRING);

                    if (!TRACE_IsInitialized())
                    {
                        ret = RESFILE_AddKeyValue(appRes, NULL,
                                                  ITS_TRACE_ERROR_STRING,
                                                  buf);
                    }
                    else
                    {
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_ERROR_STRING,
                                                   ITS_FILE_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_ERROR_STRING,
                                                   ITS_STDOUT_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_ERROR_STRING,
                                                   ITS_SYSLOG_STRING,
                                                   ITS_TRUE);
                    }
                    break;

               case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                   TRACE_TurnErrorTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_ERROR_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                   TRACE_TurnErrorTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_ERROR_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                   TRACE_TurnErrorTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_FILE_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_ERROR_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY:
                   TRACE_TurnErrorTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_STDOUT_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_ERROR_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE:
                   TRACE_TurnErrorTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_ERROR_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_SYSLOG:
                   TRACE_TurnErrorTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_ERROR_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_ERROR_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_NONE:
                   TRACE_TurnErrorTraceOnOff(ITS_FALSE);
                   break;
            }
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_WARNING_STRING) == 0)
        {
            switch (ENGINE_TL_LEVEL_MASK(list))
            {
                case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                    TRACE_TurnWarningTraceOnOff(ITS_TRUE);

                    sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                             ITS_FILE_STRING,
                                             ITS_SYSLOG_STRING);

                    if (!TRACE_IsInitialized())
                    {
                        ret = RESFILE_AddKeyValue(appRes, NULL,
                                                  ITS_TRACE_WARNING_STRING,
                                                  buf);
                    }
                    else
                    {
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_WARNING_STRING,
                                                   ITS_FILE_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_WARNING_STRING,
                                                   ITS_STDOUT_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_WARNING_STRING,
                                                   ITS_SYSLOG_STRING,
                                                   ITS_TRUE);
                    }
                    break;

               case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                   TRACE_TurnWarningTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_WARNING_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                   TRACE_TurnWarningTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_WARNING_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                   TRACE_TurnWarningTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_FILE_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_WARNING_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY:
                   TRACE_TurnWarningTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_STDOUT_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_WARNING_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE:
                   TRACE_TurnWarningTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_WARNING_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_SYSLOG:
                   TRACE_TurnWarningTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_WARNING_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_WARNING_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_NONE:
                   TRACE_TurnWarningTraceOnOff(ITS_FALSE);
                   break;
            }
        }
        else if (strcmp(ENGINE_TL_LEVEL_NAME(list), ITS_DEBUG_STRING) == 0)
        {
            switch (ENGINE_TL_LEVEL_MASK(list))
            {
                case TRACE_TO_DISPLAY|TRACE_TO_FILE|TRACE_TO_SYSLOG:
                    TRACE_TurnDebugTraceOnOff(ITS_TRUE);

                    sprintf(buf, "%s,%s,%s", ITS_STDOUT_STRING,
                                             ITS_FILE_STRING,
                                             ITS_SYSLOG_STRING);

                    if (!TRACE_IsInitialized())
                    {
                        ret = RESFILE_AddKeyValue(appRes, NULL,
                                                  ITS_TRACE_DEBUG_STRING,
                                                  buf);
                    }
                    else
                    {
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_DEBUG_STRING,
                                                   ITS_FILE_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_DEBUG_STRING,
                                                   ITS_STDOUT_STRING,
                                                   ITS_TRUE);
                        TRACE_SetOutputOnOffByName(TRACE_Current,
                                                   ITS_DEBUG_STRING,
                                                   ITS_SYSLOG_STRING,
                                                   ITS_TRUE);
                    }
                    break;

               case TRACE_TO_DISPLAY|TRACE_TO_FILE:
                   TRACE_TurnDebugTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_DEBUG_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY|TRACE_TO_SYSLOG:
                   TRACE_TurnDebugTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_STDOUT_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_DEBUG_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE|TRACE_TO_SYSLOG:
                   TRACE_TurnDebugTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s,%s", ITS_FILE_STRING,
                                          ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_DEBUG_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_DISPLAY:
                   TRACE_TurnDebugTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_STDOUT_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_DEBUG_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_STDOUT_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_FILE:
                   TRACE_TurnDebugTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_FILE_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_DEBUG_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_FILE_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_SYSLOG:
                   TRACE_TurnDebugTraceOnOff(ITS_TRUE);

                   sprintf(buf, "%s", ITS_SYSLOG_STRING);

                   if (!TRACE_IsInitialized())
                   {
                       ret = RESFILE_AddKeyValue(appRes, NULL,
                                                 ITS_TRACE_DEBUG_STRING,
                                                 buf);
                   }
                   else
                   {
                       TRACE_SetOutputOnOffByName(TRACE_Current,
                                                  ITS_DEBUG_STRING,
                                                  ITS_SYSLOG_STRING,
                                                  ITS_TRUE);
                   }
                   break;

               case TRACE_TO_NONE:
                   TRACE_TurnDebugTraceOnOff(ITS_FALSE);
                   break;
            }
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Add new features.
 *
 *  Notes:
 *      This isn't resource related, but this is a common function.
 *
 ****************************************************************************/
static void
AddNewFeatures(ENGINE_Application newTree)
{
    ITS_Object list;
    int i;

    for (list = ENGINE_APP_FEATURES(newTree);
         list != NULL;
         list = ENGINE_FEAT_NEXT(list))
    {
        ITS_C_ASSERT(ENGINE_FEAT_CLASS_REC(list) != NULL);

        if (ITS_FindFeature(ITS_CLASS_CLASSNAME(
                                ENGINE_FEAT_CLASS_REC(list))) == NULL)
        {
            if (ITS_AddFeature(ENGINE_FEAT_CLASS_REC(list)) != ITS_SUCCESS)
            {
                printf("Failed to add feature: '%s'\n",
                       ITS_CLASS_CLASSNAME(ENGINE_FEAT_CLASS_REC(list)));

                abort();
            }

            for (i = 0; i < ENGINE_FEAT_NUM_OPTIONS(list); i++)
            {
                char buf[ITS_PATH_MAX], *tmp;

                strcpy(buf, ENGINE_FEAT_OPTIONS(list)[i]);
                tmp = strchr(buf, '=');

                ITS_C_ASSERT(tmp != NULL);

                *tmp = 0;
                tmp++;

                RESFILE_AddKeyValue(appRes, NULL, buf, tmp);
            }

            ITS_InitializeClass(ENGINE_FEAT_CLASS_REC(list));
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse a transport type.
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_BOOLEAN
ParseType(DBC_Server *dbc, char *type, ITS_UINT *mask)
{
    *mask = 0;

    if (strcmp(type, T_SS7_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_SS7 | ITS_TRANSPORT_DELAY_CREATE;
    }
    else if (strcmp(type, T_FIFO_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_FIFO | ITS_TRANSPORT_DELAY_CREATE;
    }
    else if (strcmp(type, T_GFIFO_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_GFIFO | ITS_TRANSPORT_DELAY_CREATE;
    }
    else if (strcmp(type, T_CSOCK_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_CSOCKET | ITS_TRANSPORT_DELAY_CREATE;
    }
    else if (strcmp(type, T_SSOCK_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_SSOCKET | ITS_TRANSPORT_DELAY_CREATE;
    }
    else if (strcmp(type, T_ISOCK_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_SSOCKET |
                ITS_TRANSPORT_SSOCKET_ITER |
                ITS_TRANSPORT_DELAY_CREATE;
    }
    else if (strcmp(type, T_DSOCK_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_DATAGRAM | ITS_TRANSPORT_DELAY_CREATE;
    }
    else if (strcmp(type, T_VIRT_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_DATAGRAM | ITS_TRANSPORT_DGRAM_VIRT;
    }
    else if (strcmp(type, T_TQ_STRING) == 0)
    {
        *mask = ITS_TRANSPORT_TQUEUE;
    }
    else
    {
        DBC_AppendText(dbc, "Invalid transport type ");
        DBC_AppendText(dbc, type);
        DBC_AppendText(dbc, "\n");

        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse a transport type.
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_BOOLEAN
ParseModifiers(DBC_Server *dbc, char *modifier, ITS_UINT *mask,
               ITS_BOOLEAN isANSI, ITS_BOOLEAN isITU)
{
    if (strstr(modifier, MOD_DATA_STRING))
    {
        if (!(*mask & (ITS_TRANSPORT_CSOCKET | ITS_TRANSPORT_SSOCKET)))
        {
            DBC_AppendText(dbc, "Invalid modifier for type\n");

            return (ITS_FALSE);
        }

        *mask |= ITS_TRANSPORT_DATA_SOCKET;
    }

    if (strstr(modifier, MOD_GDI_STRING))
    {
        if (!(*mask & (ITS_TRANSPORT_CSOCKET | ITS_TRANSPORT_SSOCKET)))
        {
            DBC_AppendText(dbc, "Invalid modifier for type\n");

            return (ITS_FALSE);
        }

        *mask |= ITS_TRANSPORT_GDI_SOCKET;
    }

    if (strstr(modifier, MOD_RUDP_STRING))
    {
        if (!(*mask & ITS_TRANSPORT_DATAGRAM))
        {
            DBC_AppendText(dbc, "Invalid modifier for type\n");

            return (ITS_FALSE);
        }

        *mask |= ITS_TRANSPORT_RUDP_SOCKET;
    }

    if (strstr(modifier, MOD_TALI_STRING))
    {
        if (!(*mask & (ITS_TRANSPORT_CSOCKET | ITS_TRANSPORT_SSOCKET)))
        {
            DBC_AppendText(dbc, "Invalid modifier for type\n");

            return (ITS_FALSE);
        }

        *mask |= ITS_TRANSPORT_TALI_SOCKET;
    }

    if (strstr(modifier, MOD_IMAL_STRING))
    {
        if (!(*mask & (ITS_TRANSPORT_CSOCKET |
                       ITS_TRANSPORT_SSOCKET |
                       ITS_TRANSPORT_DATAGRAM)))
        {
            DBC_AppendText(dbc, "Invalid modifier for type\n");

            return (ITS_FALSE);
        }

        *mask |= ITS_TRANSPORT_IMAL_SOCKET;
    }

    if (strstr(modifier, MOD_SCTP_STRING))
    {
        if (!(*mask & ITS_TRANSPORT_DATAGRAM))
        {
            DBC_AppendText(dbc, "Invalid modifier for type\n");

            return (ITS_FALSE);
        }

        *mask |= ITS_TRANSPORT_SCTP_SOCKET;
    }

    if (strstr(modifier, MOD_MTP2_STRING))
    {
        if (isITU)
        {
            *mask |= ITS_MTP2_CCITT;
        }
        if (isANSI)
        {
            *mask |= ITS_MTP2_ANSI;
        }
    }
    if (strstr(modifier, MOD_MTP3_STRING))
    {
        if (isITU)
        {
            *mask |= ITS_MTP3_CCITT;
        }
        if (isANSI)
        {
            *mask |= ITS_MTP3_ANSI;
        }
    }
    if (strstr(modifier, MOD_ISUP_STRING))
    {
        if (isITU)
        {
            *mask |= ITS_ISUP_CCITT;
        }
        if (isANSI)
        {
            *mask |= ITS_ISUP_ANSI;
        }
    }
    if (strstr(modifier, MOD_SCCP_STRING))
    {
        if (isITU)
        {
            *mask |= ITS_SCCP_CCITT;
        }
        if (isANSI)
        {
            *mask |= ITS_SCCP_ANSI;
        }
    }
    if (strstr(modifier, MOD_TCAP_STRING))
    {
        if (isITU)
        {
            *mask |= ITS_TCAP_CCITT;
        }
        if (isANSI)
        {
            *mask |= ITS_TCAP_ANSI;
        }
    }

    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse a transport specifics.
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_BOOLEAN
ParseTransportSpecifics(DBC_Server *dbc, const char *specifics, ITS_UINT mask,
                        ENGINE_TransportSpecificsPart *specs)
{
    int ret;
    char buf[ITS_PATH_MAX], buf2[ITS_PATH_MAX], *ptr, *tmp, *end;
    char cmd[ITS_PATH_MAX];

    memset(specs, 0, sizeof(*specs));

    switch (ITS_GET_TRANSPORT_TYPE(mask))
    {
    case ITS_TRANSPORT_SS7:
        specs->data.ss7Specs.vendorLib = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.ss7Specs.vendorLib == NULL)
        {
            DBC_AppendText(dbc, "Out of memory for SS7 transport\n");

            return (ITS_FALSE);
        }

        specs->data.ss7Specs.vendorClass = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.ss7Specs.vendorLib == NULL)
        {
            free(specs->data.ss7Specs.vendorLib);

            DBC_AppendText(dbc, "Out of memory for SS7 transport\n");

            return (ITS_FALSE);
        }

        ret = sscanf(specifics, "%s %s %s", cmd,  
                     specs->data.ss7Specs.vendorLib,
                     specs->data.ss7Specs.vendorClass);
        if (ret != 3)
        {
            free(specs->data.ss7Specs.vendorLib);
            free(specs->data.ss7Specs.vendorClass);

            DBC_AppendText(dbc, "Bad specifics for SS7 transport\n");

            return (ITS_FALSE);
        }
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        specs->data.fifoSpecs.clientPath = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.fifoSpecs.clientPath == NULL)
        {
            DBC_AppendText(dbc, "Out of memory for FIFO transport\n");

            return (ITS_FALSE);
        }

        specs->data.fifoSpecs.serverPath = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.fifoSpecs.serverPath == NULL)
        {
            free(specs->data.fifoSpecs.clientPath);

            DBC_AppendText(dbc, "Out of memory for FIFO transport\n");

            return (ITS_FALSE);
        }

        ret = sscanf(specifics, "%s %s %s", cmd, 
                     specs->data.fifoSpecs.clientPath,
                     specs->data.fifoSpecs.serverPath);
        if (ret != 3)
        {
            free(specs->data.fifoSpecs.clientPath);
            free(specs->data.fifoSpecs.serverPath);

            DBC_AppendText(dbc, "Bad specifics for FIFO transport\n");

            return (ITS_FALSE);
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        specs->data.tcpSpecs.socketDomain = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.tcpSpecs.socketDomain == NULL)
        {
            DBC_AppendText(dbc, "Out of memory for socket transport\n");

            return (ITS_FALSE);
        }

        specs->data.tcpSpecs.serverPath = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.tcpSpecs.serverPath == NULL)
        {
            free(specs->data.tcpSpecs.socketDomain);

            DBC_AppendText(dbc, "Out of memory for socket transport\n");

            return (ITS_FALSE);
        }

        specs->data.tcpSpecs.serverPort = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.tcpSpecs.serverPort == NULL)
        {
            free(specs->data.tcpSpecs.socketDomain);
            free(specs->data.tcpSpecs.serverPath);

            DBC_AppendText(dbc, "Out of memory for socket transport\n");

            return (ITS_FALSE);
        }

        specs->data.tcpSpecs.retryDelay = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.tcpSpecs.retryDelay == NULL)
        {
            free(specs->data.tcpSpecs.socketDomain);
            free(specs->data.tcpSpecs.serverPath);
            free(specs->data.tcpSpecs.serverPort);

            DBC_AppendText(dbc, "Out of memory for socket transport\n");

            return (ITS_FALSE);
        }

        specs->data.tcpSpecs.retryCount = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.tcpSpecs.retryCount == NULL)
        {
            free(specs->data.tcpSpecs.socketDomain);
            free(specs->data.tcpSpecs.serverPath);
            free(specs->data.tcpSpecs.serverPort);
            free(specs->data.tcpSpecs.retryDelay);

            DBC_AppendText(dbc, "Out of memory for socket transport\n");

            return (ITS_FALSE);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            ret = sscanf(specifics, "%s %s %s %s %s %s", cmd, 
                         specs->data.tcpSpecs.socketDomain,
                         specs->data.tcpSpecs.serverPath,
                         specs->data.tcpSpecs.serverPort,
                         specs->data.tcpSpecs.retryDelay,
                         specs->data.tcpSpecs.retryCount);
            if (ret != 6)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);

                DBC_AppendText(dbc, "Bad specifics for socket transport\n");

                return (ITS_FALSE);
            }
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            specs->data.gdiSpecs.localPC = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.gdiSpecs.localPC == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);

                DBC_AppendText(dbc, "Out of memory for GDI transport\n");

                return (ITS_FALSE);
            }

            specs->data.gdiSpecs.remotePC = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.gdiSpecs.remotePC == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.gdiSpecs.localPC);

                DBC_AppendText(dbc, "Out of memory for GDI transport\n");

                return (ITS_FALSE);
            }

            specs->data.gdiSpecs.remoteSSN = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.gdiSpecs.remoteSSN == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.gdiSpecs.localPC);
                free(specs->data.gdiSpecs.remotePC);

                DBC_AppendText(dbc, "Out of memory for GDI transport\n");

                return (ITS_FALSE);
            }

            ret = sscanf(specifics, "%s %s %s %s %s %s %s %s %s", cmd, 
                         specs->data.tcpSpecs.socketDomain,
                         specs->data.tcpSpecs.serverPath,
                         specs->data.tcpSpecs.serverPort,
                         specs->data.tcpSpecs.retryDelay,
                         specs->data.tcpSpecs.retryCount,
                         specs->data.gdiSpecs.localPC,
                         specs->data.gdiSpecs.remotePC,
                         specs->data.gdiSpecs.remoteSSN);
            if (ret != 9)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.gdiSpecs.localPC);
                free(specs->data.gdiSpecs.remotePC);
                free(specs->data.gdiSpecs.remoteSSN);

                DBC_AppendText(dbc, "Bad specifics for GDI transport\n");

                return (ITS_FALSE);
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            specs->data.taliSpecs.localPC = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.taliSpecs.localPC == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);

                DBC_AppendText(dbc, "Out of memory for TALI transport\n");

                return (ITS_FALSE);
            }

            specs->data.taliSpecs.adjacentPC = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.taliSpecs.adjacentPC == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.taliSpecs.localPC);

                DBC_AppendText(dbc, "Out of memory for TALI transport\n");

                return (ITS_FALSE);
            }

            specs->data.taliSpecs.localAllowedOnOpen = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.taliSpecs.localAllowedOnOpen == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.taliSpecs.localPC);
                free(specs->data.taliSpecs.adjacentPC);

                DBC_AppendText(dbc, "Out of memory for TALI transport\n");

                return (ITS_FALSE);
            }

            specs->data.taliSpecs.useUpperLayer = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.taliSpecs.useUpperLayer == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.taliSpecs.localPC);
                free(specs->data.taliSpecs.adjacentPC);
                free(specs->data.taliSpecs.localAllowedOnOpen);

                DBC_AppendText(dbc, "Out of memory for TALI transport\n");

                return (ITS_FALSE);
            }

            ret = sscanf(specifics, "%s %s %s %s %s %s %s %s %s %s", cmd, 
                         specs->data.tcpSpecs.socketDomain,
                         specs->data.tcpSpecs.serverPath,
                         specs->data.tcpSpecs.serverPort,
                         specs->data.tcpSpecs.retryDelay,
                         specs->data.tcpSpecs.retryCount,
                         specs->data.taliSpecs.localPC,
                         specs->data.taliSpecs.adjacentPC,
                         specs->data.taliSpecs.localAllowedOnOpen,
                         specs->data.taliSpecs.useUpperLayer);
            if (ret != 10)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.taliSpecs.localPC);
                free(specs->data.taliSpecs.adjacentPC);
                free(specs->data.taliSpecs.localAllowedOnOpen);
                free(specs->data.taliSpecs.useUpperLayer);

                DBC_AppendText(dbc, "Bad specifics for TALI transport\n");

                return (ITS_FALSE);
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            specs->data.imalSpecs.localPC = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.imalSpecs.localPC == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);

                DBC_AppendText(dbc, "Out of memory for IMAL transport\n");

                return (ITS_FALSE);
            }

            specs->data.imalSpecs.adjacentPC = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.imalSpecs.adjacentPC == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.imalSpecs.localPC);

                DBC_AppendText(dbc, "Out of memory for IMAL transport\n");

                return (ITS_FALSE);
            }

            specs->data.imalSpecs.keepAliveTimeOut = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.imalSpecs.keepAliveTimeOut == NULL)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.imalSpecs.localPC);
                free(specs->data.imalSpecs.adjacentPC);

                DBC_AppendText(dbc, "Out of memory for IMAL transport\n");

                return (ITS_FALSE);
            }

            ret = sscanf(specifics, "%s %s %s %s %s %s %s %s %s", cmd, 
                         specs->data.tcpSpecs.socketDomain,
                         specs->data.tcpSpecs.serverPath,
                         specs->data.tcpSpecs.serverPort,
                         specs->data.tcpSpecs.retryDelay,
                         specs->data.tcpSpecs.retryCount,
                         specs->data.imalSpecs.localPC,
                         specs->data.imalSpecs.adjacentPC,
                         specs->data.imalSpecs.keepAliveTimeOut);
            if (ret != 9)
            {
                free(specs->data.tcpSpecs.socketDomain);
                free(specs->data.tcpSpecs.serverPath);
                free(specs->data.tcpSpecs.serverPort);
                free(specs->data.tcpSpecs.retryDelay);
                free(specs->data.tcpSpecs.retryCount);
                free(specs->data.imalSpecs.localPC);
                free(specs->data.imalSpecs.adjacentPC);
                free(specs->data.imalSpecs.keepAliveTimeOut);

                DBC_AppendText(dbc, "Bad specifics for IMAL transport\n");

                return (ITS_FALSE);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        break;

    case ITS_TRANSPORT_DATAGRAM:
        specs->data.udpSpecs.localHost = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.udpSpecs.localHost == NULL)
        {
            DBC_AppendText(dbc, "Out of memory for socket transport\n");

            return (ITS_FALSE);
        }

        specs->data.udpSpecs.localPort = (char *)malloc(ITS_PATH_MAX);
        if (specs->data.udpSpecs.localPort == NULL)
        {
            free(specs->data.udpSpecs.localHost);

            DBC_AppendText(dbc, "Out of memory for socket transport\n");

            return (ITS_FALSE);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            buf[0] = 0;
            ret = sscanf(specifics, "%s %s %s %s", cmd, 
                         specs->data.udpSpecs.localHost,
                         specs->data.udpSpecs.localPort,
                         buf);
            if (ret != 4)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);

                DBC_AppendText(dbc, "Bad specifics for socket transport\n");

                return (ITS_FALSE);
            }

            if (strcmp(buf, "none") == 0)
            {
                return (ITS_TRUE);
            }

            /* associates */
            ptr = buf;
            end = buf + strlen(buf);

            while (ptr < end)
            {
                tmp = strstr(ptr, ",");

                if (tmp)
                {
                    *tmp = 0;
                    tmp++;
                }

                specs->data.udpSpecs.numAssociates++;

                specs->data.udpSpecs.associates = (char **)
                                        realloc(specs->data.udpSpecs.associates,
                                                specs->data.udpSpecs.numAssociates *
                                                    sizeof(char *));
                if (specs->data.udpSpecs.associates == NULL)
                {
                    free(specs->data.udpSpecs.localHost);
                    free(specs->data.udpSpecs.localPort);

                    return (ITS_FALSE);
                }

                specs->data.udpSpecs.associates[specs->data.udpSpecs.numAssociates - 1] =
                    (char *)malloc(strlen(ptr) + 1);

                if (specs->data.udpSpecs.associates[specs->data.udpSpecs.numAssociates - 1] ==
                    NULL)
                {
                    int i;

                    for (i = 0; i < specs->data.udpSpecs.numAssociates - 1; i++)
                    {
                        free(specs->data.udpSpecs.associates[i]);
                    }

                    free(specs->data.udpSpecs.localHost);
                    free(specs->data.udpSpecs.localPort);

                    return (ITS_FALSE);
                }

                strcpy(specs->data.udpSpecs.associates
                        [specs->data.udpSpecs.numAssociates - 1],
                       ptr);

                if (tmp)
                {
                    ptr = tmp;
                }
                else
                {
                    ptr = end;
                }
            }
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            specs->data.sctpSpecs.maxInStreams = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.maxInStreams == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.numOutStreams = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.numOutStreams == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.maxAttempts = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.maxAttempts == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.cookieLife = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.cookieLife == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.hbOn = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.hbOn == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.initTimeOut = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.initTimeOut == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.sendTimeOut = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.sendTimeOut == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.recvTimeOut = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.recvTimeOut == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);
                free(specs->data.sctpSpecs.sendTimeOut);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.hbTimeOut = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.hbTimeOut == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);
                free(specs->data.sctpSpecs.sendTimeOut);
                free(specs->data.sctpSpecs.recvTimeOut);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.shutdownTimeOut = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.shutdownTimeOut == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);
                free(specs->data.sctpSpecs.sendTimeOut);
                free(specs->data.sctpSpecs.recvTimeOut);
                free(specs->data.sctpSpecs.hbTimeOut);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.pmtuTimeOut = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.pmtuTimeOut == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);
                free(specs->data.sctpSpecs.sendTimeOut);
                free(specs->data.sctpSpecs.recvTimeOut);
                free(specs->data.sctpSpecs.hbTimeOut);
                free(specs->data.sctpSpecs.shutdownTimeOut);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.isClient = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.isClient == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);
                free(specs->data.sctpSpecs.sendTimeOut);
                free(specs->data.sctpSpecs.recvTimeOut);
                free(specs->data.sctpSpecs.hbTimeOut);
                free(specs->data.sctpSpecs.shutdownTimeOut);
                free(specs->data.sctpSpecs.pmtuTimeOut);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            specs->data.sctpSpecs.payloadType = (char *)malloc(ITS_PATH_MAX);
            if (specs->data.sctpSpecs.payloadType == NULL)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);
                free(specs->data.sctpSpecs.sendTimeOut);
                free(specs->data.sctpSpecs.recvTimeOut);
                free(specs->data.sctpSpecs.hbTimeOut);
                free(specs->data.sctpSpecs.shutdownTimeOut);
                free(specs->data.sctpSpecs.pmtuTimeOut);
                free(specs->data.sctpSpecs.isClient);

                DBC_AppendText(dbc, "Out of memory for SCTP transport\n");

                return (ITS_FALSE);
            }

            buf[0] = 0;
            buf2[0] = 0;
            ret = sscanf(specifics, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", cmd, 
                         specs->data.udpSpecs.localHost,
                         specs->data.udpSpecs.localPort,
                         buf,
                         buf2,
                         specs->data.sctpSpecs.maxInStreams,
                         specs->data.sctpSpecs.numOutStreams,
                         specs->data.sctpSpecs.maxAttempts,
                         specs->data.sctpSpecs.cookieLife,
                         specs->data.sctpSpecs.hbOn,
                         specs->data.sctpSpecs.initTimeOut,
                         specs->data.sctpSpecs.sendTimeOut,
                         specs->data.sctpSpecs.recvTimeOut,
                         specs->data.sctpSpecs.hbTimeOut,
                         specs->data.sctpSpecs.shutdownTimeOut,
                         specs->data.sctpSpecs.pmtuTimeOut,
                         specs->data.sctpSpecs.isClient,
                         specs->data.sctpSpecs.payloadType);
            if (ret != 18)
            {
                free(specs->data.udpSpecs.localHost);
                free(specs->data.udpSpecs.localPort);
                free(specs->data.sctpSpecs.maxInStreams);
                free(specs->data.sctpSpecs.numOutStreams);
                free(specs->data.sctpSpecs.maxAttempts);
                free(specs->data.sctpSpecs.cookieLife);
                free(specs->data.sctpSpecs.hbOn);
                free(specs->data.sctpSpecs.initTimeOut);
                free(specs->data.sctpSpecs.sendTimeOut);
                free(specs->data.sctpSpecs.recvTimeOut);
                free(specs->data.sctpSpecs.hbTimeOut);
                free(specs->data.sctpSpecs.shutdownTimeOut);
                free(specs->data.sctpSpecs.pmtuTimeOut);
                free(specs->data.sctpSpecs.isClient);
                free(specs->data.sctpSpecs.payloadType);

                DBC_AppendText(dbc, "Bad specifics for socket transport\n");

                return (ITS_FALSE);
            }

            if (strcmp(buf, "none") == 0)
            {
                return (ITS_TRUE);
            }

            /* associates */
            ptr = buf;
            end = buf + strlen(buf);

            while (ptr < end)
            {
                tmp = strstr(ptr, ",");

                if (tmp)
                {
                    *tmp = 0;
                    tmp++;
                }

                specs->data.udpSpecs.numAssociates++;

                specs->data.udpSpecs.associates = (char **)
                                        realloc(specs->data.udpSpecs.associates,
                                                specs->data.udpSpecs.numAssociates *
                                                    sizeof(char *));
                if (specs->data.udpSpecs.associates == NULL)
                {
                    free(specs->data.udpSpecs.localHost);
                    free(specs->data.udpSpecs.localPort);
                    free(specs->data.sctpSpecs.maxInStreams);
                    free(specs->data.sctpSpecs.numOutStreams);
                    free(specs->data.sctpSpecs.maxAttempts);
                    free(specs->data.sctpSpecs.cookieLife);
                    free(specs->data.sctpSpecs.hbOn);
                    free(specs->data.sctpSpecs.initTimeOut);
                    free(specs->data.sctpSpecs.sendTimeOut);
                    free(specs->data.sctpSpecs.recvTimeOut);
                    free(specs->data.sctpSpecs.hbTimeOut);
                    free(specs->data.sctpSpecs.shutdownTimeOut);
                    free(specs->data.sctpSpecs.pmtuTimeOut);
                    free(specs->data.sctpSpecs.isClient);
                    free(specs->data.sctpSpecs.payloadType);

                    return (ITS_FALSE);
                }

                specs->data.udpSpecs.associates[specs->data.udpSpecs.numAssociates - 1] =
                    (char *)malloc(strlen(ptr) + 1);

                if (specs->data.udpSpecs.associates[specs->data.udpSpecs.numAssociates - 1] ==
                    NULL)
                {
                    int i;

                    for (i = 0; i < specs->data.udpSpecs.numAssociates; i++)
                    {
                        free(specs->data.udpSpecs.associates[i]);
                    }

                    free(specs->data.udpSpecs.localHost);
                    free(specs->data.udpSpecs.localPort);
                    free(specs->data.sctpSpecs.maxInStreams);
                    free(specs->data.sctpSpecs.numOutStreams);
                    free(specs->data.sctpSpecs.maxAttempts);
                    free(specs->data.sctpSpecs.cookieLife);
                    free(specs->data.sctpSpecs.hbOn);
                    free(specs->data.sctpSpecs.initTimeOut);
                    free(specs->data.sctpSpecs.sendTimeOut);
                    free(specs->data.sctpSpecs.recvTimeOut);
                    free(specs->data.sctpSpecs.hbTimeOut);
                    free(specs->data.sctpSpecs.shutdownTimeOut);
                    free(specs->data.sctpSpecs.pmtuTimeOut);
                    free(specs->data.sctpSpecs.isClient);
                    free(specs->data.sctpSpecs.payloadType);

                    return (ITS_FALSE);
                }

                strcpy(specs->data.udpSpecs.associates
                        [specs->data.udpSpecs.numAssociates - 1],
                       ptr);

                if (tmp)
                {
                    ptr = tmp;
                }
                else
                {
                    ptr = end;
                }
            }

            /* other homes */
            ptr = buf2;
            end = buf2 + strlen(buf);

            while (ptr < end)
            {
                tmp = strstr(ptr, ",");

                if (tmp)
                {
                    *tmp = 0;
                    tmp++;
                }

                specs->data.sctpSpecs.numExtraHomes++;

                specs->data.sctpSpecs.extraHomes = (char **)
                                        realloc(specs->data.sctpSpecs.extraHomes,
                                                specs->data.sctpSpecs.numExtraHomes *
                                                    sizeof(char *));
                if (specs->data.sctpSpecs.extraHomes == NULL)
                {
                    int i;

                    for (i = 0; i < specs->data.udpSpecs.numAssociates - 1; i++)
                    {
                        free(specs->data.udpSpecs.associates[i]);
                    }

                    free(specs->data.udpSpecs.localHost);
                    free(specs->data.udpSpecs.localPort);
                    free(specs->data.sctpSpecs.maxInStreams);
                    free(specs->data.sctpSpecs.numOutStreams);
                    free(specs->data.sctpSpecs.maxAttempts);
                    free(specs->data.sctpSpecs.cookieLife);
                    free(specs->data.sctpSpecs.hbOn);
                    free(specs->data.sctpSpecs.initTimeOut);
                    free(specs->data.sctpSpecs.sendTimeOut);
                    free(specs->data.sctpSpecs.recvTimeOut);
                    free(specs->data.sctpSpecs.hbTimeOut);
                    free(specs->data.sctpSpecs.shutdownTimeOut);
                    free(specs->data.sctpSpecs.pmtuTimeOut);
                    free(specs->data.sctpSpecs.isClient);
                    free(specs->data.sctpSpecs.payloadType);

                    return (ITS_FALSE);
                }

                specs->data.sctpSpecs.extraHomes
                    [specs->data.sctpSpecs.numExtraHomes - 1] = (char *)malloc(strlen(ptr) + 1);
                if (specs->data.sctpSpecs.extraHomes[specs->data.sctpSpecs.numExtraHomes - 1] ==
                    NULL)
                {
                    int i;

                    for (i = 0; i < specs->data.sctpSpecs.numExtraHomes - 1; i++)
                    {
                        free(specs->data.sctpSpecs.extraHomes[i]);
                    }

                    for (i = 0; i < specs->data.udpSpecs.numAssociates - 1; i++)
                    {
                        free(specs->data.udpSpecs.associates[i]);
                    }

                    free(specs->data.udpSpecs.localHost);
                    free(specs->data.udpSpecs.localPort);
                    free(specs->data.sctpSpecs.maxInStreams);
                    free(specs->data.sctpSpecs.numOutStreams);
                    free(specs->data.sctpSpecs.maxAttempts);
                    free(specs->data.sctpSpecs.cookieLife);
                    free(specs->data.sctpSpecs.hbOn);
                    free(specs->data.sctpSpecs.initTimeOut);
                    free(specs->data.sctpSpecs.sendTimeOut);
                    free(specs->data.sctpSpecs.recvTimeOut);
                    free(specs->data.sctpSpecs.hbTimeOut);
                    free(specs->data.sctpSpecs.shutdownTimeOut);
                    free(specs->data.sctpSpecs.pmtuTimeOut);
                    free(specs->data.sctpSpecs.isClient);
                    free(specs->data.sctpSpecs.payloadType);

                    return (ITS_FALSE);
                }

                strcpy(specs->data.sctpSpecs.extraHomes
                        [specs->data.sctpSpecs.numExtraHomes - 1],
                       ptr);

                if (tmp)
                {
                    ptr = tmp;
                }
                else
                {
                    ptr = end;
                }
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;
    }

    return (ITS_TRUE);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse a transport callbacks.
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_Object
ParseCallbacks(DBC_Server *dbc, const char *callbacks, ITS_UINT mask)
{
    ITS_BOOLEAN realSS7 = ITS_FALSE;
    ITS_BOOLEAN blocking = ITS_TRUE;
    DISP_HandlerType htype, atype = DISP_PROT_USER;
    char libName[ITS_PATH_MAX], preInit[ITS_PATH_MAX], postInit[ITS_PATH_MAX];
    char preNext[ITS_PATH_MAX], nextFailed[ITS_PATH_MAX], postNext[ITS_PATH_MAX];
    char dispUser[ITS_PATH_MAX], dispISUP[ITS_PATH_MAX], dispSCCP[ITS_PATH_MAX];
    char preAccept[ITS_PATH_MAX], onAccept[ITS_PATH_MAX];
    char preTerm[ITS_PATH_MAX], postTerm[ITS_PATH_MAX];
    char type[ITS_PATH_MAX];
    ITS_Object cbs;
    char cmd[ITS_PATH_MAX];
    int ret;

    if (mask & ITS_TRANSPORT_SS7)
    {
        realSS7 = ITS_TRUE;
    }

    if (mask & ITS_TRANSPORT_SSOCKET_ITER)
    {
        htype = DISP_PROT_ITERATIVE;

        if ((mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            atype = DISP_PROT_ANSI;
        }
        else if ((mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            atype = DISP_PROT_CCITT;
        }
        else if ((mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            atype = DISP_PROT_PRC;
        }
        else if ((mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            atype = DISP_PROT_TTC;
        }
        else
        {
            atype = DISP_PROT_USER;
        }
    }
    else if ((mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
    {
        htype = DISP_PROT_ANSI;
    }
    else if ((mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
    {
        htype = DISP_PROT_CCITT;
    }
    else if ((mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
    {
        htype = DISP_PROT_PRC;
    }
    else if ((mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
    {
        htype = DISP_PROT_TTC;
    }
    else
    {
        htype = DISP_PROT_USER;
    }

    ret = sscanf(callbacks, "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s", cmd, 
                 type, libName,
                 preInit, postInit,
                 preNext, nextFailed, postNext,
                 dispUser, dispISUP, dispSCCP,
                 preAccept, onAccept,
                 preTerm, postTerm);
    if (ret != 15)
    {
        DBC_AppendText(dbc, "Bad callback data\n");

        return (NULL);
    }

    /* pull the type information out */
    if (strcmp(type, NBLOCK_STRING) == 0)
    {
        blocking = ITS_FALSE;
    }
    else if (strcmp(type, TYPE_DBC_STRING) == 0)
    {
        if (mask & ITS_TRANSPORT_SSOCKET_ITER)
        {
            atype = DISP_PROT_DBC;
        }
        else
        {
            htype = DISP_PROT_DBC;
        }
    }

    cbs = ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                              application, libName, realSS7,
                              htype, (blocking ? DISP_BLOCKING
                                               : DISP_NON_BLOCKING),
                              preInit, postInit,
                              preNext, nextFailed, postNext,
                              dispUser, dispISUP, dispSCCP,
                              preAccept, onAccept,
                              preTerm, postTerm, atype);

    return (cbs);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse a transport callbacks.
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_Object
BuildTransport(DBC_Server *dbc, char *name,
               ITS_UINT mask, ITS_Object callbacks, ITS_BOOLEAN isInterNode,
               ENGINE_TransportSpecificsPart *specs, ITS_Object links)
{
    ITS_Object specialization = NULL;
    ITS_Object ret;

    /* deal with undefined callbacks */
    if (callbacks == NULL)
    {
        DISP_HandlerType htype, atype = DISP_PROT_USER;
        ITS_BOOLEAN realSS7 = ITS_FALSE;

        if (mask & ITS_TRANSPORT_SS7)
        {
            realSS7 = ITS_TRUE;
        }

        if (mask & ITS_TRANSPORT_SSOCKET_ITER)
        {
            htype = DISP_PROT_ITERATIVE;

            if ((mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
            {
                atype = DISP_PROT_ANSI;
            }
            else if ((mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
            {
                atype = DISP_PROT_CCITT;
            }
            else if ((mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
            {
                atype = DISP_PROT_PRC;
            }
            else if ((mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
            {
                atype = DISP_PROT_TTC;
            }
            else
            {
                atype = DISP_PROT_USER;
            }
        }
        else if ((mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            htype = DISP_PROT_ANSI;
        }
        else if ((mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            htype = DISP_PROT_CCITT;
        }
        else if ((mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            htype = DISP_PROT_PRC;
        }
        else if ((mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            htype = DISP_PROT_TTC;
        }
        else
        {
            htype = DISP_PROT_USER;
        }

        callbacks =
                  ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                      application, NULL, realSS7,
                                      htype, DISP_BLOCKING,
                                      NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL,
                                      NULL, NULL, atype);
        ITS_C_ASSERT(callbacks != NULL);
    }

    /* create the specifics */
    switch (ITS_GET_TRANSPORT_TYPE(mask))
    {
    case ITS_TRANSPORT_SS7:
        specialization =
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                mask,
                                specs->data.ss7Specs.vendorLib,
                                specs->data.ss7Specs.vendorClass);
        ITS_C_ASSERT(specialization != NULL);


        if (specs->data.ss7Specs.vendorLib)
        {
            free(specs->data.ss7Specs.vendorLib);
        }
        if (specs->data.ss7Specs.vendorClass)
        {
            free(specs->data.ss7Specs.vendorClass);
        }
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        specialization =
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                mask,
                                specs->data.fifoSpecs.clientPath,
                                specs->data.fifoSpecs.serverPath);

        if (specs->data.fifoSpecs.clientPath)
        {
            free(specs->data.fifoSpecs.clientPath);
        }
        if (specs->data.fifoSpecs.serverPath)
        {
            free(specs->data.fifoSpecs.serverPath);
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        switch (ITS_GET_TRANSPORT_FLAGS(mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    mask,
                                    specs->data.tcpSpecs.socketDomain,
                                    specs->data.tcpSpecs.serverPath,
                                    specs->data.tcpSpecs.serverPort,
                                    specs->data.tcpSpecs.retryDelay,
                                    specs->data.tcpSpecs.retryCount);
            ITS_C_ASSERT(specialization != NULL);

            if (specs->data.tcpSpecs.socketDomain)
            {
                free(specs->data.tcpSpecs.socketDomain);
            }
            if (specs->data.tcpSpecs.serverPath)
            {
                free(specs->data.tcpSpecs.serverPath);
            }
            if (specs->data.tcpSpecs.serverPort)
            {
                free(specs->data.tcpSpecs.serverPort);
            }
            if (specs->data.tcpSpecs.retryDelay)
            {
                free(specs->data.tcpSpecs.retryDelay);
            }
            if (specs->data.tcpSpecs.retryCount)
            {
                free(specs->data.tcpSpecs.retryCount);
            }
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    mask,
                                    specs->data.tcpSpecs.socketDomain,
                                    specs->data.tcpSpecs.serverPath,
                                    specs->data.tcpSpecs.serverPort,
                                    specs->data.tcpSpecs.retryDelay,
                                    specs->data.tcpSpecs.retryCount,
                                    specs->data.gdiSpecs.localPC,
                                    specs->data.gdiSpecs.remotePC,
                                    specs->data.gdiSpecs.remoteSSN);
            ITS_C_ASSERT(specialization != NULL);

            if (specs->data.tcpSpecs.socketDomain)
            {
                free(specs->data.tcpSpecs.socketDomain);
            }
            if (specs->data.tcpSpecs.serverPath)
            {
                free(specs->data.tcpSpecs.serverPath);
            }
            if (specs->data.tcpSpecs.serverPort)
            {
                free(specs->data.tcpSpecs.serverPort);
            }
            if (specs->data.tcpSpecs.retryDelay)
            {
                free(specs->data.tcpSpecs.retryDelay);
            }
            if (specs->data.tcpSpecs.retryCount)
            {
                free(specs->data.tcpSpecs.retryCount);
            }
            if (specs->data.gdiSpecs.localPC)
            {
                free(specs->data.gdiSpecs.localPC);
            }
            if (specs->data.gdiSpecs.remotePC)
            {
                free(specs->data.gdiSpecs.remotePC);
            }
            if (specs->data.gdiSpecs.remoteSSN)
            {
                free(specs->data.gdiSpecs.remoteSSN);
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    mask,
                                    specs->data.tcpSpecs.socketDomain,
                                    specs->data.tcpSpecs.serverPath,
                                    specs->data.tcpSpecs.serverPort,
                                    specs->data.tcpSpecs.retryDelay,
                                    specs->data.tcpSpecs.retryCount,
                                    specs->data.taliSpecs.localPC,
                                    specs->data.taliSpecs.adjacentPC,
                                    specs->data.taliSpecs.localAllowedOnOpen,
                                    specs->data.taliSpecs.useUpperLayer);
            ITS_C_ASSERT(specialization != NULL);

            if (specs->data.tcpSpecs.socketDomain)
            {
                free(specs->data.tcpSpecs.socketDomain);
            }
            if (specs->data.tcpSpecs.serverPath)
            {
                free(specs->data.tcpSpecs.serverPath);
            }
            if (specs->data.tcpSpecs.serverPort)
            {
                free(specs->data.tcpSpecs.serverPort);
            }
            if (specs->data.tcpSpecs.retryDelay)
            {
                free(specs->data.tcpSpecs.retryDelay);
            }
            if (specs->data.tcpSpecs.retryCount)
            {
                free(specs->data.tcpSpecs.retryCount);
            }
            if (specs->data.taliSpecs.localPC)
            {
                free(specs->data.taliSpecs.localPC);
            }
            if (specs->data.taliSpecs.adjacentPC)
            {
                free(specs->data.taliSpecs.adjacentPC);
            }
            if (specs->data.taliSpecs.localAllowedOnOpen)
            {
                free(specs->data.taliSpecs.localAllowedOnOpen);
            }
            if (specs->data.taliSpecs.useUpperLayer)
            {
                free(specs->data.taliSpecs.useUpperLayer);
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    mask,
                                    specs->data.tcpSpecs.socketDomain,
                                    specs->data.tcpSpecs.serverPath,
                                    specs->data.tcpSpecs.serverPort,
                                    specs->data.tcpSpecs.retryDelay,
                                    specs->data.tcpSpecs.retryCount,
                                    specs->data.imalSpecs.localPC,
                                    specs->data.imalSpecs.adjacentPC,
                                    specs->data.imalSpecs.keepAliveTimeOut);
            ITS_C_ASSERT(specialization != NULL);

            if (specs->data.tcpSpecs.socketDomain)
            {
                free(specs->data.tcpSpecs.socketDomain);
            }
            if (specs->data.tcpSpecs.serverPath)
            {
                free(specs->data.tcpSpecs.serverPath);
            }
            if (specs->data.tcpSpecs.serverPort)
            {
                free(specs->data.tcpSpecs.serverPort);
            }
            if (specs->data.tcpSpecs.retryDelay)
            {
                free(specs->data.tcpSpecs.retryDelay);
            }
            if (specs->data.tcpSpecs.retryCount)
            {
                free(specs->data.tcpSpecs.retryCount);
            }
            if (specs->data.imalSpecs.localPC)
            {
                free(specs->data.imalSpecs.localPC);
            }
            if (specs->data.imalSpecs.adjacentPC)
            {
                free(specs->data.imalSpecs.adjacentPC);
            }
            if (specs->data.imalSpecs.keepAliveTimeOut)
            {
                free(specs->data.imalSpecs.keepAliveTimeOut);
            }
            break;

        default:
            specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    mask,
                                    specs->data.tcpSpecs.socketDomain,
                                    specs->data.tcpSpecs.serverPath,
                                    specs->data.tcpSpecs.serverPort,
                                    specs->data.tcpSpecs.retryDelay,
                                    specs->data.tcpSpecs.retryCount);
            ITS_C_ASSERT(specialization != NULL);

            if (specs->data.tcpSpecs.socketDomain)
            {
                free(specs->data.tcpSpecs.socketDomain);
            }
            if (specs->data.tcpSpecs.serverPath)
            {
                free(specs->data.tcpSpecs.serverPath);
            }
            if (specs->data.tcpSpecs.serverPort)
            {
                free(specs->data.tcpSpecs.serverPort);
            }
            if (specs->data.tcpSpecs.retryDelay)
            {
                free(specs->data.tcpSpecs.retryDelay);
            }
            if (specs->data.tcpSpecs.retryCount)
            {
                free(specs->data.tcpSpecs.retryCount);
            }
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        break;

    case ITS_TRANSPORT_DATAGRAM:

        switch (ITS_GET_TRANSPORT_FLAGS(mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_SCTP_SOCKET:
            specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    mask,
                                    specs->data.udpSpecs.localHost,
                                    specs->data.udpSpecs.localPort,
                                    specs->data.udpSpecs.associates,
                                    specs->data.udpSpecs.numAssociates,
                                    specs->data.sctpSpecs.extraHomes,
                                    specs->data.sctpSpecs.numExtraHomes,
                                    specs->data.sctpSpecs.maxInStreams,
                                    specs->data.sctpSpecs.numOutStreams,
                                    specs->data.sctpSpecs.maxAttempts,
                                    specs->data.sctpSpecs.cookieLife,
                                    specs->data.sctpSpecs.hbOn,
                                    specs->data.sctpSpecs.initTimeOut,
                                    specs->data.sctpSpecs.sendTimeOut,
                                    specs->data.sctpSpecs.recvTimeOut,
                                    specs->data.sctpSpecs.hbTimeOut,
                                    specs->data.sctpSpecs.shutdownTimeOut,
                                    specs->data.sctpSpecs.pmtuTimeOut,
                                    specs->data.sctpSpecs.isClient,
                                    specs->data.sctpSpecs.payloadType);
            ITS_C_ASSERT(specialization != NULL);

            if (specs->data.udpSpecs.localHost)
            {
                free(specs->data.udpSpecs.localHost);
            }
            if (specs->data.udpSpecs.localPort)
            {
                free(specs->data.udpSpecs.localPort);
            }
            if (specs->data.sctpSpecs.maxInStreams)
            {
                free(specs->data.sctpSpecs.maxInStreams);
            }
            if (specs->data.sctpSpecs.numOutStreams)
            {
                free(specs->data.sctpSpecs.numOutStreams);
            }
            if (specs->data.sctpSpecs.maxAttempts)
            {
                free(specs->data.sctpSpecs.maxAttempts);
            }
            if (specs->data.sctpSpecs.cookieLife)
            {
                free(specs->data.sctpSpecs.cookieLife);
            }
            if (specs->data.sctpSpecs.hbOn)
            {
                free(specs->data.sctpSpecs.hbOn);
            }
            if (specs->data.sctpSpecs.initTimeOut)
            {
                free(specs->data.sctpSpecs.initTimeOut);
            }
            if (specs->data.sctpSpecs.sendTimeOut)
            {
                free(specs->data.sctpSpecs.sendTimeOut);
            }
            if (specs->data.sctpSpecs.recvTimeOut)
            {
                free(specs->data.sctpSpecs.recvTimeOut);
            }
            if (specs->data.sctpSpecs.hbTimeOut)
            {
                free(specs->data.sctpSpecs.hbTimeOut);
            }
            if (specs->data.sctpSpecs.shutdownTimeOut)
            {
                free(specs->data.sctpSpecs.shutdownTimeOut);
            }
            if (specs->data.sctpSpecs.pmtuTimeOut)
            {
                free(specs->data.sctpSpecs.pmtuTimeOut);
            }
            if (specs->data.sctpSpecs.isClient)
            {
                free(specs->data.sctpSpecs.isClient);
            }
            if (specs->data.sctpSpecs.payloadType)
            {
                free(specs->data.sctpSpecs.payloadType);
            }
            break;

        case ITS_TRANSPORT_DATA_SOCKET:
        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing yet */

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */

        default:
            specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    mask,
                                    specs->data.udpSpecs.localHost,
                                    specs->data.udpSpecs.localPort,
                                    specs->data.udpSpecs.associates,
                                    specs->data.udpSpecs.numAssociates);
            ITS_C_ASSERT(specialization != NULL);

            if (specs->data.udpSpecs.localHost)
            {
                free(specs->data.udpSpecs.localHost);
            }
            if (specs->data.udpSpecs.localPort)
            {
                free(specs->data.udpSpecs.localPort);
            }
            break;
        }
        break;
    }

    /* create the transport */
    ret = ITS_ConstructObject(itsENGINE_TransportClass, NULL,
                              name, mask, 
                              isInterNode,
                              specialization, callbacks,
                              links, NULL);

    /* FIXME: ENGINE_TR_NUM_ASSOCIATES(ret) = trCount; */

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse a transport callbacks.
 *
 *  Notes:
 *
 ****************************************************************************/
static ITS_BOOLEAN
ParseLinks(DBC_Server *dbc, const char *linkInfo, ITS_Object *alist)
{
    ENGINE_LinkPart link;
    char active[ITS_PATH_MAX], termf[ITS_PATH_MAX], linkf[ITS_PATH_MAX];
    char saal[ITS_PATH_MAX], local[ITS_PATH_MAX], family[ITS_PATH_MAX];
    int ret, ls, lc, lp;
    ITS_Object obj;
    char cmd[ITS_PATH_MAX];

    memset(&link, 0, sizeof(ENGINE_LinkPart));

    link.initActive = ITS_TRUE;
    link.termFixed = ITS_TRUE;
    link.linkFixed = ITS_TRUE;

    ret = sscanf(linkInfo, "%s %d %d %d %s %s %s %hd %hd %s %s %s",
                 cmd,
                 &ls, &lc, &lp,
                 active,
                 termf,
                 linkf,
                 &link.terminal,
                 &link.circuit,
                 saal,
                 local,
                 family);

    link.linkSet = (ITS_OCTET)ls;
    link.linkCode = (ITS_OCTET)lc;
    link.linkPri = (ITS_OCTET)lp;

    link.initActive = strstr(active, "yes") != NULL ||
                        strstr(active, "YES") != NULL;
    link.termFixed = strstr(termf, "yes") != NULL ||
                        strstr(termf, "YES") != NULL;
    link.linkFixed = strstr(linkf, "yes") != NULL ||
                        strstr(linkf, "YES") != NULL;
    link.isSAAL = strstr(saal, "yes") != NULL ||
                        strstr(saal, "YES") != NULL;
    link.isLocal = strstr(local, "yes") != NULL ||
                        strstr(local, "YES") != NULL;

    if (strcmp(family, FAMILY_ANSI_STRING) == 0)
    {
        link.family = FAMILY_ANSI;
    }
    else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
    {
        link.family = FAMILY_ITU;
    }
    else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
    {
        link.family = FAMILY_CHINA;
    }
    else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
    {
        link.family = FAMILY_JAPAN;
    }

    obj = ITS_ConstructObject(itsENGINE_LinkClass, alist,
                              link.linkSet, link.linkCode, link.linkPri,
                              link.initActive, link.termFixed, link.linkFixed,
                              link.terminal, link.circuit,
                              link.isSAAL, link.isLocal, link.family);

    if (obj == NULL)
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

static ITS_UINT bMask = 0;
static ENGINE_TransportSpecificsPart bSpecs;
static ITS_Object bCBS, bLinkList;
static ITS_BOOLEAN isITU = ITS_FALSE, isANSI = ITS_FALSE;
static ITS_BOOLEAN hasType = ITS_FALSE;
static ITS_BOOLEAN hasFamily = ITS_FALSE;
static ITS_BOOLEAN hasMods = ITS_FALSE;
static ITS_BOOLEAN hasSpecs = ITS_FALSE;
static ITS_BOOLEAN hasCallbacks = ITS_FALSE;

static int AddBorder(DBC_Server *dbc, ITS_Object tr, ITS_Object pool);

static void
ResetContext()
{
    /* flags reset */
    hasType = ITS_FALSE;
    hasFamily = ITS_FALSE;
    hasMods = ITS_FALSE;
    hasSpecs = ITS_FALSE;

    /* mask & mods reset */
    bMask = 0;

    /* family reset */
    isANSI = ITS_FALSE;
    isITU = ITS_FALSE;

    /* clear objects */
    if (bCBS)
    {
        ITS_DestructObject(bCBS);
        bCBS = NULL;
    }
    if (bLinkList)
    {
        while (bLinkList)
        {
            ITS_Object tmp;

            tmp = ENGINE_LN_NEXT(bLinkList);
            ITS_DestructObject(bLinkList);
            bLinkList = tmp;
        }
        bLinkList = NULL;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      DBC command proc for the engine.
 *
 *  Notes:
 *
 ****************************************************************************/
void
ENGINE_Console(DBC_Server *dbc, const char *cmdLine)
{
    int ret;
    char buf[ITS_PATH_MAX];

    ITS_C_ASSERT(dbc != NULL);

    /* reset params */
    if (DBC_Cmd(dbc, "b_reset", "Reset border transport data",
                     "<>", "<reset all border transport add fields>"))
    {
        ResetContext();
    }
    /* set type */
    else if (DBC_Cmd(dbc, "b_settype", "Set border transport type",
                     "<type>",
                     "<SS7|FIFO|GatedFIFO|ClientSocket|ServerSocket|"
                      "IterativeServerSocket|Virtual|TaskQueue>"))
    {
        char type[ITS_PATH_MAX];

        bMask = 0;
        ret = sscanf(cmdLine, "%s %s", buf, type);
        if (ret != 2)
        {
            DBC_AppendText(dbc, "Invalid input to command\n");

            return;
        }

        /* decide the type */
        if (!ParseType(dbc, type, &bMask))
        {
            return;
        }

        hasType = ITS_TRUE;
    }
    /* set family */
    else if (DBC_Cmd(dbc, "b_setfamily", "Set border transport family",
                          "<family>", "<ANSI|ITU|PRC|TTC>"))
    {
        char family[ITS_PATH_MAX];

        if (!hasType)
        {
            DBC_AppendText(dbc, "You must set the border type first\n");

            return;
        }

        ret = sscanf(cmdLine, "%s %s", buf, family);
        if (ret != 2)
        {
            DBC_AppendText(dbc, "Invalid input to command\n");

            return;
        }

        isITU = ITS_FALSE;
        isANSI = ITS_FALSE;

        /* get the family */
        if (strcmp(family, ITU_STRING) == 0)
        {
            isITU = ITS_TRUE;
        }
        else if (strcmp(family, ANSI_STRING) == 0)
        {
            isANSI = ITS_TRUE;
        }

        hasFamily = ITS_TRUE;
    }
    /* set modifiers */
    else if (DBC_Cmd(dbc, "b_setmods", "Set border transport modifiers",
                          "<modifiers>",
                          "<DATA|RUDP|IMAL|TALI|GDI|SCTP|MTP2|MTP3|ISUP|SCCP|TCAP>"))
    {
        char modifiers[ITS_PATH_MAX];

        if (!hasType || !hasFamily)
        {
            DBC_AppendText(dbc, "You must set the border type and family first\n");

            return;
        }

        ret = sscanf(cmdLine, "%s %s", buf, modifiers);
        if (ret != 2)
        {
            DBC_AppendText(dbc, "Invalid command line\n");

            return;
        }

        /* get the modifiers */
        if (!ParseModifiers(dbc, modifiers, &bMask, isANSI, isITU))
        {
            return;
        }

        hasMods = ITS_TRUE;
    }
    /* set transport specifics */
    else if (DBC_Cmd(dbc, "b_setspecs", "Set border transport specifics",
                     "<transport specifics>", "(see help text)"))
    {
        if (!hasType || !hasFamily || !hasMods)
        {
            DBC_AppendText(dbc, "You must set the border type, family, and mods first\n");

            return;
        }

        /* get the transport specifics */
        if (!ParseTransportSpecifics(dbc, cmdLine, bMask, &bSpecs))
        {
            return;
        }

        hasSpecs = ITS_TRUE;
    }
    /* set callbacks */
    else if (DBC_Cmd(dbc, "b_setcallbacks", "Set border transport callbacks",
                     "<list of callbacks>", "(see help text)"))
    {
        if (!hasType || !hasFamily || !hasMods)
        {
            DBC_AppendText(dbc, "You must set the border type, family, and mods first\n");

            return;
        }

        /* get the callbacks */
        if ((bCBS = ParseCallbacks(dbc, cmdLine, bMask)) == NULL)
        {
            return;
        }

        hasCallbacks = ITS_TRUE;
    }
    /* add links */
    else if (DBC_Cmd(dbc, "b_addlink", "Add a link to the border transport",
                     "<link info>", "(see help text)"))
    {
        if (!hasType || !hasFamily || !hasMods)
        {
            DBC_AppendText(dbc, "You must set the border type, family, and mods first\n");

            return;
        }

        /* parse link information */
        if (!ParseLinks(dbc, cmdLine, &bLinkList))
        {
            return;
        }
    }
    /* add the border transport */
    else if (DBC_Cmd(dbc, "b_addborder", "Add Border Transport",
                     "<name> <internode>", "<text> <yes|no>"))
    {
        char name[ITS_PATH_MAX];
        char internode[ITS_PATH_MAX];
        ITS_BOOLEAN isInterNode;
        ITS_Object tr, list, pool;

        if (!hasType || !hasFamily || !hasMods || !hasSpecs)
        {
            DBC_AppendText(dbc, "You must set the border type, family, mods, and specs first\n");

            return;
        }

        ret = sscanf(cmdLine, "%s %s %s",
                     buf, name, internode);
        if (ret != 3)
        {
            DBC_AppendText(dbc, "Invalid command line\n");

            return;
        }

        /* is internode? */
        isInterNode = strstr(internode, "yes") != NULL ||
                        strstr(internode, "YES") != NULL;

        /* get the border pool */
        pool = NULL;
        for (list = ENGINE_APP_POOLS(application);
             list != NULL;
             list = ENGINE_TP_NEXT(list))
        {
            if (ENGINE_TP_TYPE(list) == TP_BORDERS)
            {
                pool = list;

                break;
            }
        }
        if (pool == NULL)
        {
            DBC_AppendText(dbc, "Application lacks border pool\n");

            return;
        }

        /* construct the transport object */
        if ((tr = BuildTransport(dbc, name, bMask, bCBS, isInterNode,
                                 &bSpecs, bLinkList)) == NULL)
        {
            ResetContext();

            return;
        }

        /* set the instance */
        currentInstance = lastBorder;
        ENGINE_TR_INST(tr) = currentInstance;

        /* populate resources */
        ProcessOneTransport(tr, pool);

        /* update lastBorder */
        currentInstance++;
        lastBorder = currentInstance;

        /* add it via the driver function */
        if (AddBorder(dbc, tr, pool) != ITS_SUCCESS)
        {
            DBC_AppendText(dbc, "Failed to add border transport, deleting data\n");

            ITS_DestructObject(tr);

            bLinkList = NULL;
            bCBS = NULL;
            ResetContext();

            return;
        }

        DBC_AppendText(dbc, "Border transport added\n");
    }
    else if (DBC_Cmd(dbc, "b_getborders", "Get All Border Transport",
                     "", ""))
    {
        TRANSPORT_Manager *tm;
        TRANSPORT_Control *ent;
        ITS_UINT mask;

        tm = TRANSPORT_GetManager();

        if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
        {
             return;
        }

        for ( ent = tm->listHead;
              ent != NULL; ent = TRANSPORT_HMI_NEXT(ent))
        {
            mask = TRANSPORT_MASK(ent);

            switch (ITS_GET_TRANSPORT_TYPE(mask))
            {
                case ITS_TRANSPORT_SS7 :
                {
                    SS7_Transport m = (SS7_Transport)ent;

                    sprintf(buf, "________________________________________\n");
                    DBC_AppendText(dbc, buf);
                       
                    sprintf(buf,"    Transport Name         <%s>\n", 
                                TRANSPORT_NAME(m));
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Transport Type         <ClientSocket>\n");
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Mask                   <%x>\n", 
                            mask);
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Instance               <%x>\n", 
                            TRANSPORT_INSTANCE(m));
                    DBC_AppendText(dbc, buf);

                    if (TRANSPORT_IS_ACTIVE(m))
                    {
                        sprintf(buf,"    isActive               <yes>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    isActive               <no>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                }
                break;

                case ITS_TRANSPORT_FIFO :
                {
                    FIFOTRAN_Manager *m = (FIFOTRAN_Manager *)ent;

                    sprintf(buf, "________________________________________\n");
                    DBC_AppendText(dbc, buf);
                       
                    sprintf(buf,"    Transport Name         <%s>\n", 
                                TRANSPORT_NAME(m));
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Transport Type         <ClientSocket>\n");
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Mask                   <%x>\n", 
                            mask);
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Instance               <%x>\n", 
                            TRANSPORT_INSTANCE(m));
                    DBC_AppendText(dbc, buf);

                    if (TRANSPORT_IS_ACTIVE(m))
                    {
                        sprintf(buf,"    isActive               <yes>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    isActive               <no>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                }
                break;

                case ITS_TRANSPORT_GFIFO :
                {
                    GFIFOTRAN_Manager *m = (GFIFOTRAN_Manager *)ent;

                    sprintf(buf, "________________________________________\n");
                    DBC_AppendText(dbc, buf);
                       
                    sprintf(buf,"    Transport Name         <%s>\n", 
                                TRANSPORT_NAME(m));
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Transport Type         <ClientSocket>\n");
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Mask                   <%x>\n", 
                            mask);
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Instance               <%x>\n", 
                            TRANSPORT_INSTANCE(m));
                    DBC_AppendText(dbc, buf);

                    if (TRANSPORT_IS_ACTIVE(m))
                    {
                        sprintf(buf,"    isActive               <yes>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    isActive               <no>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                }
                break;

                case ITS_TRANSPORT_CSOCKET :
                {
                    SOCKTRAN_Manager *m = (SOCKTRAN_Manager *)ent;

                    sprintf(buf, "________________________________________\n");
                    DBC_AppendText(dbc, buf);
                       
                    sprintf(buf,"    Transport Name         <%s>\n", 
                                TRANSPORT_NAME(m));
                    DBC_AppendText(dbc, buf);

                    if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK)
                          == ITS_TRANSPORT_IMAL_SOCKET)
                    {
                        sprintf(buf,"    Transport Type         <IMALClientSocket>\n");
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    Transport Type         <ClientSocket>\n");
                        DBC_AppendText(dbc, buf);
                    }

                    sprintf(buf,"    Mask                   <%x>\n", 
                            mask);
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Instance               <%x>\n", 
                            TRANSPORT_INSTANCE(m));
                    DBC_AppendText(dbc, buf);

                    if (TRANSPORT_IS_ACTIVE(m))
                    {
                        sprintf(buf,"    isActive               <yes>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    isActive               <no>\n"); 
                        DBC_AppendText(dbc, buf);
                    }

                    sprintf(buf,"    Host                   <%s>\n", 
                            SOCKTRAN_HOST_PATH(m));
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Port                   <%d>\n", 
                            SOCKTRAN_PORT(m));
                    DBC_AppendText(dbc, buf);

                }
                break;

                case ITS_TRANSPORT_SSOCKET :
                {
                    SOCKTRAN_Manager *m = (SOCKTRAN_Manager *)ent;

                    sprintf(buf, "________________________________________\n");
                    DBC_AppendText(dbc, buf);
                       
                    sprintf(buf,"    Transport Name         <%s>\n", 
                                TRANSPORT_NAME(m));
                    DBC_AppendText(dbc, buf);

                    if ((ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SOCKP_MASK)
                          == ITS_TRANSPORT_IMAL_SOCKET)
                    {
                        sprintf(buf,"    Transport Type         <IMALServerSocket>\n");
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    Transport Type         <ServerSocket>\n");
                        DBC_AppendText(dbc, buf);
                    }

                    if (ITS_GET_TRANSPORT_FLAGS(mask) & ITS_TRANSPORT_SSOCKET_ITER)
                    {
                        sprintf(buf,"    isIterative            <yes>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    isIterative            <no>\n"); 
                        DBC_AppendText(dbc, buf);
                    }

                    sprintf(buf,"    Mask                   <%x>\n", 
                            mask);
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Instance               <%x>\n", 
                            TRANSPORT_INSTANCE(m));
                    DBC_AppendText(dbc, buf);

                    if (TRANSPORT_IS_ACTIVE(m))
                    {
                        sprintf(buf,"    isActive               <yes>\n"); 
                        DBC_AppendText(dbc, buf);
                    }
                    else
                    {
                        sprintf(buf,"    isActive               <no>\n"); 
                        DBC_AppendText(dbc, buf);
                    }

                    sprintf(buf,"    Host                   <%s>\n", 
                            SOCKTRAN_HOST_PATH(m));
                    DBC_AppendText(dbc, buf);

                    sprintf(buf,"    Port                   <%d>\n", 
                            SOCKTRAN_PORT(m));
                    DBC_AppendText(dbc, buf);
                }
                break;

                case ITS_TRANSPORT_DATAGRAM :
                {
                    if ((mask & ITS_TRANSPORT_SOCKP_MASK) == 
                         ITS_TRANSPORT_SCTP_SOCKET)
                    {
                        SCTPTRAN_ManagerPtr m = (SCTPTRAN_ManagerPtr)ent;

                        sprintf(buf, "________________________________________\n");
                        DBC_AppendText(dbc, buf);
                       
                        sprintf(buf,"    Transport Name         <%s>\n", 
                                TRANSPORT_NAME(m));
                        DBC_AppendText(dbc, buf);

                        sprintf(buf,"    Transport Type         <SCTP>\n");
                        DBC_AppendText(dbc, buf);

                        sprintf(buf,"    Mask                   <%x>\n", 
                                mask);
                        DBC_AppendText(dbc, buf);

                        sprintf(buf,"    Instance               <%x>\n", 
                                TRANSPORT_INSTANCE(m));
                        DBC_AppendText(dbc, buf);

                        if (TRANSPORT_IS_ACTIVE(m))
                        {
                            sprintf(buf,"    isActive               <yes>\n"); 
                            DBC_AppendText(dbc, buf);
                        }
                        else
                        {
                            sprintf(buf,"    isActive               <no>\n"); 
                            DBC_AppendText(dbc, buf);
                        }

                        sprintf(buf,"    Host                   <%s>\n", 
                                SOCKTRAN_HOST_PATH(m));
                        DBC_AppendText(dbc, buf);

                        sprintf(buf,"    Port                   <%d>\n", 
                                SOCKTRAN_PORT(m));
                        DBC_AppendText(dbc, buf);

                        if (SCTPTRAN_PAYLOAD(m) == SCTP_PAYLOAD_M3UA)
                        {
                            sprintf(buf,"    Payload                <M3UA>\n"); 
                            DBC_AppendText(dbc, buf);
                        }
                        else if (SCTPTRAN_PAYLOAD(m) == SCTP_PAYLOAD_SUA)
                        {
                            sprintf(buf,"    Payload                <SUA>\n"); 
                            DBC_AppendText(dbc, buf);
                        }
                        
                        if (SCTPTRAN_PAYLOAD(m) == SCTP_PAYLOAD_M2UA)
                        {
                            if (isITU)
                            {
                                sprintf(buf,"    Payload                <CCITT-M2UA>\n");
                                DBC_AppendText(dbc, buf);
                            }
                            if (isANSI)
                            {
                                sprintf(buf,"    Payload                <ANSI-M2UA>\n");
                                DBC_AppendText(dbc, buf);
                            }
                        }


                        if (SCTPTRAN_IS_CLIENT(m))
                        {
                            sprintf(buf,"    isClient               <yes>\n"); 
                            DBC_AppendText(dbc, buf);
                        }
                        else
                        {
                            sprintf(buf,"    isClient               <no>\n"); 
                            DBC_AppendText(dbc, buf);
                        }
                    }

                    
                }
                break;

                case ITS_TRANSPORT_TQUEUE :
                {
                }
                break;

                default :

                    break;
            }
        }

        sprintf(buf, "________End Of Borders__________________\n");
        DBC_AppendText(dbc, buf);

        RWLOCK_UnlockShared(&tm->transportGate);

    }
    
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      DBC command proc for the Routing subsystem.
 *
 *  Notes:
 *
 ****************************************************************************/
void
ROUTE_Console(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;

    if (DBC_Cmd(dbc, "rt_add", "add a Route", "", ""))
    {
        char direction[20];
        char style[20];
        char family[10];
        char parameters[50];
        ROUTE_MatchInfo rinfo;
        ITS_UINT dpc, opc;
        ITS_UINT sio;
        ITS_UINT ssn, beginSSN, endSSN;
        ITS_UINT cic, beginCIC, endCIC;
        SS7_LinkSetPtr ls; 
        ITS_UINT linkSet;

        memset(&rinfo, 0, sizeof(rinfo));

        /* addRoute dirrection style paremeters */
        ret = sscanf(cmdLine, "%s %s %s %d %s %[^\n]",
                     buf, direction, family, &linkSet, style, parameters);

        sprintf(buf, "*********** Adding a Route *************\n");

        DBC_AppendText(dbc, buf);

        if (ret != 6)
        {
            sprintf(buf, "*** Error: Invalid parameters, try help rt_add \n");
            DBC_AppendText(dbc, buf);
            return;

        }


        sprintf(buf, "         direction:  %s \n"
               "         family:     %s \n"
               "         linkSet:    %d \n"
               "         style:      %s \n"
               "         parameters: %s \n",
               direction, family, linkSet, style, parameters);

        DBC_AppendText(dbc, buf);

        ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet);
        if (ls == NULL)
        {
            sprintf(buf, "ERROR Linkset: %d does not exist\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        /*** process direction ***/

        if (strcmp(direction, ROUTE_TYPE_LOCAL_STRING) == 0)
        {
            rinfo.basic.type = LOCAL_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_REMOTE_STRING) == 0)
        {
            rinfo.basic.type = REMOTE_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_CONCERNED_STRING) == 0)
        {
            rinfo.basic.type =CONCERNED_ROUTE;
        }
        else
        {
            sprintf(buf,"Error: direction must be concerned,remoteRoute or localRoute\n");
            DBC_AppendText(dbc, buf);
            return;
        }
       /*** process family ***/

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
           DBC_AppendText(dbc, buf);
           return;
       }


       /*** process route style ****/

        if (strcmp(style, ROUTE_STYLE_DPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_NI;

            ret = sscanf(parameters,"%d %d", &dpc, &sio);
            if (ret != 2)
            {
                sprintf(buf, "Error: Missing dpc or ni value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_NI;

            ret = sscanf(parameters,"%d %d %d", &dpc, &opc,  &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or ni value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO;

            ret = sscanf(parameters,"%d %d", &dpc, &sio);
            if (ret != 2)
            {
                sprintf(buf, "Error: Missing dpc or sio value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO;

            ret = sscanf(parameters,"%d %d %d", &dpc, &opc, &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or sio value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &ssn);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &ssn);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d",
                         &dpc, &sio, &beginSSN, &endSSN);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginSSN, &endSSN);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &cic);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &cic);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d",
                         &dpc, &sio, &beginCIC, &endCIC);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginCIC, &endCIC);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else
        {
            sprintf(buf, "Error: Invalid routing style\n");
            DBC_AppendText(dbc,buf);
            return;
        }

        rinfo.linkSet = (ITS_OCTET) linkSet;
        rinfo.linkCode = 0;
        rinfo.priority = 0;
        rinfo.sls  = 0;
        rinfo.rkey = 0;
        rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;
        if ( (ret = ROUTE_AddRouteContextInfo(&rinfo)) != ITS_SUCCESS)
          {
              sprintf(buf, "Error %d: Route cannot be added\n", ret);
              DBC_AppendText(dbc,buf);
              return;
          }
       

    }
    else if (DBC_Cmd(dbc, "rt_del", "delete a Route", "", ""))
    {
        char direction[20];
        char style[20];
        char family[10];
        char parameters[50];
        ROUTE_MatchInfo rinfo;
        ITS_UINT opc, dpc;
        ITS_UINT sio;
        ITS_UINT ssn, beginSSN, endSSN;
        ITS_UINT cic, beginCIC, endCIC;
        SS7_LinkSetPtr ls; 
        ITS_UINT linkSet;

        /* dirrection style paremeters */

        ret = sscanf(cmdLine, "%s %s %s %d %s %[^\n]",
                     buf, direction, family, &linkSet, style, parameters);

        sprintf(buf, "*********** Deleting a Route *************\n");

        DBC_AppendText(dbc, buf);

        if (ret != 6)
        {
            sprintf(buf,"*** Error: Invalid parameters, try help rt_del\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "         direction:  %s \n"
               "         family:     %s \n"
               "         linkSet:    %d \n"
               "         style:      %s \n"
               "         parameters: %s \n",
               direction, family, linkSet, style, parameters);

        DBC_AppendText(dbc, buf);

        ls = LINKSET_FindLinkSet((ITS_OCTET)linkSet);
        if (ls == NULL)
        {
            sprintf(buf, "ERROR Linkset: %d does not exist\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        /*** process direction ***/

        if (strcmp(direction, ROUTE_TYPE_LOCAL_STRING) == 0)
        {
            rinfo.basic.type = LOCAL_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_REMOTE_STRING) == 0)
        {
            rinfo.basic.type = REMOTE_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_CONCERNED_STRING) == 0)
        {
            rinfo.basic.type =CONCERNED_ROUTE;
        }
        else
        {
            sprintf(buf,"Error: direction must be remoteRoute or localRoute\n");
            DBC_AppendText(dbc, buf);
            return;
        }

       /*** process family ***/

       if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI;
       }
       else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU;
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA;
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN;
       }
       else
       {
           sprintf(buf, "Error invalid family...\n");
           DBC_AppendText(dbc, buf);
           return;
       }


       /*** process route style ****/

        if (strcmp(style, ROUTE_STYLE_DPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_NI;

            sscanf(parameters,"%d %d", &dpc, &sio);
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_NI;
            ret = sscanf(parameters,"%d %d %d", &dpc, &opc,  &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or ni value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO;

            ret = sscanf(parameters,"%d %d", &dpc, &sio);
            if (ret != 2)
            {
                sprintf(buf, "Error: Missing dpc or sio value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO;

            ret = sscanf(parameters,"%d %d %d", &dpc, &opc, &sio);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, opc or ni value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &ssn);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &ssn);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or ssn value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.ssn = (ITS_OCTET)ssn;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d",
                         &dpc, &sio, &beginSSN, &endSSN);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginSSN, &endSSN);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginSSN or endSSN value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginSSN;
            rinfo.basic.criteria.range.end = endSSN;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d", &dpc, &sio, &cic);
            if (ret != 3)
            {
                sprintf(buf, "Error: Missing dpc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;


        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;

            ret = sscanf(parameters,"%d %d %d %d", &dpc, &opc, &sio, &cic);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio or cic value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.cic = cic;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d",
                         &dpc, &sio, &beginCIC, &endCIC);
            if (ret != 4)
            {
                sprintf(buf, "Error: Missing dpc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;

            ret = sscanf(parameters,"%d %d %d %d %d",
                         &dpc, &opc, &sio, &beginCIC, &endCIC);
            if (ret != 5)
            {
                sprintf(buf, "Error: Missing dpc, opc, sio, beginCIC or endCIC value\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            rinfo.basic.dpc = dpc;
            rinfo.basic.criteria.opc = opc;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio;
            rinfo.basic.criteria.range.begin = beginCIC;
            rinfo.basic.criteria.range.end = endCIC;

        }
        else
        {
            sprintf(buf, "Error: Invalid routing style\n");
            DBC_AppendText(dbc,buf);
            return;
        }

        rinfo.linkSet = (ITS_OCTET) linkSet;
        rinfo.linkCode = 0;
        rinfo.priority = 0;
        rinfo.sls  = 0;
        rinfo.rkey = 0;
        rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

        if (ROUTE_DeleteRouteContextInfo(&rinfo) != ITS_SUCCESS)
        {
            sprintf(buf, "Error %d: Route cannot be deleted\n", ret);
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "rt_dump", "Dump Routes Info", "<>", "<>"))
    {
        char *dump = NULL;

        ROUTE_LockForWrite(routeRWLock);

        ROUTE_DumpSS7ToIdHashtable(&dump);

        ROUTE_UnlockWrite(routeRWLock);

        if (dump)
        {
            DBC_AppendText(dbc, dump);
            free(dump);
         }
    }

}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      DBC command proc for the Linkset/Link subsystem.
 *
 *  Notes:
 *
 ****************************************************************************/
void
LINK_Console(DBC_Server *dbc, const char *cmdLine)
{
    char buf[ITS_PATH_MAX];
    int ret;

    if (DBC_Cmd(dbc, "ls_add", "Add a Linkset", "<id>", "<family> <lpc> <apc> <ni>"))
    {

        ITS_UINT linkSet;
        char family[10];
        ITS_UINT lpc, apc;
        ITS_UINT ni;
        SS7_LinkSetPtr ls;
        SS7_LinkSet set;

        memset(&set, 0, sizeof(SS7_LinkSet));

        set.isUp = ITS_FALSE;


        ret = sscanf(cmdLine, "%s %d %s %d %d %d", buf, &linkSet, family,
                     &lpc, &apc, &ni);
        if (ret != 6)
        {
            sprintf(buf, "ERROR Missing <linkSet>, <family> , <lpc>, <apc> "
                    " or <ni>\n") ;

            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet(linkSet);

        if (ls != NULL)
        {
            sprintf(buf, "ERROR Linkset: %d already exist\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        set.linkSet  = linkSet;
        set.adjacent = apc;
        set.lpc      = lpc;
        set.ni       = ni & ROUTE_NI_MASK;
        set.numToStart = 0;

        if (strcmp(family, FAMILY_ANSI_STRING) == 0)
        {
            set.family = FAMILY_ANSI;
        }
        else if (strcmp(family, FAMILY_CCITT_STRING) == 0)
        {
            set.family = FAMILY_ITU;
        }
        else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
        {
            set.family = FAMILY_CHINA;
        }
        else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
        {
            set.family = FAMILY_JAPAN;
        }
        else
        {
            sprintf(buf, "ERROR Invalid Family. Try ITU, ANSI, CHINA or JAPAN\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        /* now add the linkset */

        ret = LINKSET_AddLinkSet(&set);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "ERROR LINKSET_AddLinkSet Fails\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Linket %d added successfully...\n", set.linkSet);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ls_del", "Delete a Linkset", "<id>", "<>"))
    {
        ITS_UINT linkSet;
        SS7_LinkSetPtr ls;
        int ret;

        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            sprintf(buf, "ERROR Missing <linkSet> parameter\n") ;

            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet(linkSet);

        if (ls == NULL)
        {
            sprintf(buf, "ERROR Linkset: %d does not exist\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        if (ls->numLinks != 0)
        {
            sprintf(buf, "ERROR Linkset: %d has %d links. Delete them first\n",
                          linkSet, ls->numLinks);
            DBC_AppendText(dbc, buf);
            return;
        }

        ret = LINKSET_RemLinkSet(ls);

        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "ERROR LINKSET_RemLinkSet Fails\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        sprintf(buf, "Linket %d deleted successfully...\n", ls->linkSet);
        DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ln_add", "Add a Link", "<inst>", "<linkset> <linkcode> <timeslot>"))
    {
        TRANSPORT_Control *tc;
        ITS_UINT instance;
        SS7_Link ln;
        SS7_LinkPtr    lp;
        SS7_LinkSetPtr ls;
        ITS_UINT linkCode, linkSet,timeslot;
        ITS_BOOLEAN isInterNode = ITS_FALSE;
        int ret;
        ITS_EVENT ev;

        memset(&ln, 0, sizeof(SS7_Link));
        ln.initActive = ITS_TRUE;
        ln.termFixed = ITS_TRUE;
        ln.linkFixed = ITS_TRUE;
        ln.isSAAL = ITS_FALSE;
        ln.next = NULL;
        ln.prev = NULL;

        ret = sscanf(cmdLine, "%s %d %d %d %d", buf, &instance, &linkSet, &linkCode,&timeslot);
        if (ret != 5)
        {
            sprintf(buf, "ERROR Missing transport instance, Linkset or link info ret=%d\n", ret);
            DBC_AppendText(dbc, buf);
            return;
        }

        tc = TRANSPORT_FindTransport(instance);

        if (tc == NULL)
        {
            sprintf(buf, "Invalid Instance specified\n");
            DBC_AppendText(dbc, buf);
            return;

        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls == NULL)
        {
            sprintf(buf, "Error LinkSet %d does not exist\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        ln.isUp = ITS_FALSE;
        ln.isAllowed = ITS_TRUE;
        ln.linkCode = (ITS_OCTET) linkCode;
        ln.id = instance;
        ln.dsmNodeId = DSM_GetNodeId();
        ln.family = ls->family;
        if (instance==ITS_MTP2_SRC)
          {            

            ln.dataLink=timeslot;
          }

        lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
        if (lp != NULL)
        {
            sprintf(buf, "Error ls:%d lc:%d already exist\n", linkSet, linkCode) ;
            DBC_AppendText(dbc, buf);
            return;

        }

        ret = LINK_AddLink(linkSet, &ln);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "ERROR: Fail to add link %d\n", linkCode);
            DBC_AppendText(dbc, buf);
            return;
        }

       lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
       if (lp == NULL)
       {
            sprintf(buf, "ERROR: Fail to find link after adding %d\n", linkCode);
            DBC_AppendText(dbc, buf);
            return;
       }

       LINK_AddLinkInfoToTransport(tc, lp);

         
           /*message for mtp2 link addtion */       
          ITS_EVENT_INIT(&ev,ITS_MTP3_SRC,3*sizeof(ITS_OCTET));
          ev.data[0]=ln_add_cmd;
          ev.data[1]=linkSet;
          ev.data[2]=linkCode;
          ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, &ev);
          if (ret!=ITS_SUCCESS)
           {
             ITS_EVENT_TERM(&ev);
           }
       usleep(500);/*due to ENTYRNODE flag will update at MTP2*/

        if (ENTRYDONE==1)
          {
            ENTRYDONE=0;
            sprintf(buf, "ls:%d lc:%d Added successfully\n", linkSet, linkCode);
            DBC_AppendText(dbc, buf);
          } 
        else
         {         
          ITS_EVENT_INIT(&ev,ITS_MTP3_SRC,3*sizeof(ITS_OCTET));
          ev.data[0]=ln_del_cmd;
          ev.data[1]=linkSet;
          ev.data[2]=linkCode;
          ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, &ev);
          if (ret!=ITS_SUCCESS)
           {
             ITS_EVENT_TERM(&ev);
             sprintf(buf, "ERROR: Fail to remote link %d\n", linkCode);
             return;
           }
           /*also delete the entry at mtp3 database*/
          ret = LINK_RemLink(linkSet, lp);
          if (ret != ITS_SUCCESS)
            {
             sprintf(buf, "ERROR: Fail to remote link %d\n", linkCode);
             DBC_AppendText(dbc, buf);
             return;
            }
            sprintf(buf, "ls:%d lc:%d Added fail\n", linkSet, linkCode);
            DBC_AppendText(dbc, buf);
         }/*end of else*/
        
      
      

    }
    else if (DBC_Cmd(dbc, "ln_del", "Delete a Link", "<id>", "<>"))
    {
        TRANSPORT_Control *tc;
        SS7_LinkPtr    lp;
        SS7_LinkSetPtr ls;
        ITS_UINT linkCode, linkSet;
        int ret;
        ITS_EVENT ev;

        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);

        if (ret != 3)
        {
            sprintf(buf, "ERROR Missing Linkset or link info\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ls = LINKSET_FindLinkSet((ITS_OCTET) linkSet);
        if (ls == NULL)
        {
            sprintf(buf, "Error LinkSet %d does not exist\n", linkSet);
            DBC_AppendText(dbc, buf);
            return;
        }

        lp = LINK_FindLink((ITS_OCTET) linkSet, (ITS_OCTET) linkCode);
        if (lp == NULL)
        {
            sprintf(buf, "Error ls:%d lc:%d does not exist\n",
                    linkSet, linkCode);
            DBC_AppendText(dbc, buf);
            return;

        }

          ITS_EVENT_INIT(&ev,ITS_MTP3_SRC,3*sizeof(ITS_OCTET));
          ev.data[0]=ln_del_cmd;
          ev.data[1]=linkSet;
          ev.data[2]=linkCode;
          ret=TRANSPORT_PutEvent(ITS_MTP2_SRC, &ev);
          if (ret!=ITS_SUCCESS)
           {
             ITS_EVENT_TERM(&ev);
             sprintf(buf, "ERROR: Fail to remote link %d\n", linkCode);
             return;
           }
       usleep(500);
       if(ENTRYDELETE==1)
        {
          ENTRYDELETE=0;
          ret = LINK_RemLink(linkSet, lp);
          if (ret != ITS_SUCCESS)
          {
            sprintf(buf, "ERROR: Fail to remote link %d\n", linkCode);
            DBC_AppendText(dbc, buf);
            return;
          }
          sprintf(buf, "ls:%d lc:%d Deleted successfully\n", linkSet, linkCode);
          DBC_AppendText(dbc, buf);
       }
      else
       {
          sprintf(buf, "ls:%d lc:%d Deleted unsuccessfully\n", linkSet, linkCode);
          DBC_AppendText(dbc, buf);
       }
    }

}






